#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

#include "test_static.h"
#include "test_dynamic.h"

#include <dlfcn.h>

namespace {

	struct dl_guard {

		dl_guard(char const *name, int flags)
		{
			handle = dlopen(name, flags);
		}

		void* get_handle() const
		{
			return handle;
		}

		~dl_guard()
		{
			if (handle != nullptr) {
				dlclose(handle);
			}
		}

		dl_guard(const dl_guard& other) = delete;
		dl_guard& operator=(const dl_guard& other) = delete;

	private:
		void* handle;

	};

}

int main(int argc, char* argv[])
{

	static constexpr char USAGE_MSG[] = "Usage: mode input output"
		"\n\tmode\t\t-c or -d to compress or decompress respectively"
		"\n\tinput\t\tinput file name"
		"\n\toutput\t\toutput file name";
	static constexpr char COULD_NOT_OPEN_INPUT[] = "Could not open input file";
	static constexpr char COULD_NOT_OPEN_OUTPUT[] = "Could not open output file";
	static constexpr char INPUT_CORRUPT[] = "Operation could not be done, input file is corrupt";
	static constexpr char SUCCESS[] = "Operation done successfully";

	test_static();
	test_dynamic();

	if (argc != 4 || (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-d") != 0)) {
		std::cerr << USAGE_MSG << std::endl;
		return EXIT_FAILURE;
	}

	auto fin = std::ifstream(argv[2], std::ios::binary);
	if (!fin) {
		std::cerr << COULD_NOT_OPEN_INPUT << std::endl;
		return EXIT_FAILURE;
	}
	auto fout = std::ofstream(argv[3], std::ios::binary);
	if (!fout) {
		std::cerr << COULD_NOT_OPEN_OUTPUT << std::endl;
		return EXIT_FAILURE;
	}

	const auto dl = dl_guard("huffman.so", RTLD_LAZY);
	if (dl.get_handle() == nullptr) {
		std::cerr << dlerror() << std::endl;
		return EXIT_FAILURE;
	}

	const auto time = clock();
	if (const auto compress = std::strcmp(argv[1], "-c") == 0; compress) {
		auto huffman_compress = reinterpret_cast<void(*)(std::istream& in, std::ostream& out)>(dlsym(dl.get_handle(), "huffman_compress"));
		if (huffman_compress == nullptr) {
			std::cerr << dlerror() << std::endl;
			return EXIT_FAILURE;
		}
		huffman_compress(fin, fout);
	}
	else {
		auto huffman_decompress = reinterpret_cast<void(*)(std::istream& in, std::ostream& out)>(dlsym(dl.get_handle(), "huffman_decompress"));
		if (huffman_decompress == nullptr) {
			std::cerr << dlerror() << std::endl;
			return EXIT_FAILURE;
		}
		try {
			huffman_decompress(fin, fout);
		}
		catch (const std::exception& ex) {
			std::cerr << INPUT_CORRUPT << std::endl << ex.what() << std::endl;
			return EXIT_FAILURE;
		}
	}
	const auto elapsed = static_cast<double>(clock() - time) / CLOCKS_PER_SEC;
	std::cerr << SUCCESS << std::endl;
	std::cerr << "Time elapsed: " << std::setprecision(3) << elapsed << " seconds" << std::endl;
	return EXIT_SUCCESS;
}