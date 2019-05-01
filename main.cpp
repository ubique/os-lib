#include "hello.h"
#include "pow1.h"
#include <dlfcn.h>

void error(std::string const &message) {
	std::cerr << message << std::endl;
	exit(EXIT_FAILURE);
}

int main() {
	std::cout << "What's your name?" << std::endl;
	std::string name;
	std::cin >> name;
	hello(name);

	std::cout << "Now enter two positive numbers for me, and I will tell you something very interesting" << std::endl;
	int a, b;
	std::cin >> a >> b;
	std::cout << "a = " << a << ", b = " << b << std::endl;

	//something interesting
	std::cout << "(a ^ b) mod 1 = " << pow1(a, b) << std::endl;

	void *handle = dlopen("libpow2.so", RTLD_LAZY);
	if (handle == nullptr) {
		error(dlerror());
	}

	using pow_t = int (*)(int, int);
	pow_t func_pow2 = (pow_t)dlsym(handle, "pow2");
	if (func_pow2 == nullptr) {
		error(dlerror());
	}

	std::cout << "(a ^ b) mod 2 = " << func_pow2(a, b) << std::endl;
	if (dlclose(handle)) {
		error(dlerror());
	}
}