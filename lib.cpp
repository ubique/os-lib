#include <iostream>
#include <dlfcn.h>

extern bool is_prime(int);
extern int bin_pow(int, int);

int main() {
	const int MAGIC_MOD = 15, MAGIC_MAIN_MOD = 1346;
	int a = rand() % MAGIC_MAIN_MOD, b = rand() % MAGIC_MAIN_MOD;
	std::cout << "We have two numbers:\n\t" << a << " is" << (is_prime(a) ? " " : " not ") << "prime\n\t" << b << " is" << (is_prime(b) ? " " : " not ") << "prime\n";
		
	int c = a % MAGIC_MOD, d = b % MAGIC_MOD;

	std::cout << c << " to degree " << d << " equals " << bin_pow(c, d) << "\n";

	void *handle = dlopen("./libdyn_loaded_gcd.so", RTLD_LAZY | RTLD_GLOBAL);
	if (!handle) {
		std::cerr << "Can't open shared object.\n" << dlerror() << "\n";
		exit(EXIT_FAILURE);
	}	

        int (*ptr_gcd)(int, int) = reinterpret_cast<int(*)(int, int)>(dlsym(handle, "gcd"));

        if (ptr_gcd == nullptr) {
                std::cerr << dlerror() << "\n";
                exit(EXIT_FAILURE);
        }

        std::cout << "GCD(" << a << ", " << b << ") = " << ptr_gcd(a,b) << "\n";
        if (dlclose(handle) != 0) {
                std::cerr << "Can't close shared object.\n" << dlerror();
                exit(EXIT_FAILURE);
        }

	return 0;
}
