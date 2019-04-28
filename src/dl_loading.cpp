#include <dlfcn.h>
#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <error.h>
#include <cxxabi.h>
#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		error(EXIT_FAILURE, errno, "Wrong number of args: %d", argc);
	}
	auto lib_path = argv[1];
	void *lib = dlopen(lib_path, RTLD_LAZY);
	if (!lib) {
		error(EXIT_FAILURE, errno, "%s", dlerror());
	}
	void *fun = dlsym(lib, "mix");
	if (!fun) {
		error(EXIT_FAILURE, errno, "public dll's function isn't available outside: %s", dlerror());
	}
	void *private_fun = dlsym(lib, "mixImpl");
	if (private_fun) {
		dlclose(private_fun);
		error(EXIT_FAILURE, errno, "private dll's function is available outside: %s", dlerror());
	}

	auto mix = (int64_t (*)(std::string_view, std::string_view)) (fun);
	int64_t mix1 = mix("abcd", "efg");
	int64_t mix2 = mix(std::string("abcd"), std::string("efg"));
	std::cout << mix1 << std::endl;
	std::cout << mix2 << std::endl;

	if (dlclose(lib) != 0) {
		error(EXIT_FAILURE, errno, "%s", dlerror());
	}
	return 0;
}