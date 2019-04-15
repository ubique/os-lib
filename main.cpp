#include "modular_arithmetics.h"
#include "combinatorics.h"
#include <dlfcn.h>
#include <iostream>

void* get_pointer(void* lib, const char* name) {
    void* ptr = dlsym(lib, name);
    if (!ptr) {
        std::cerr << "Can't get function pointer to " << name << ": " << dlerror() << "\n";
        return NULL;
    }
    return ptr;
}

int main() {
    int a, b, mod;
    std::cout << "Type three natural numbers:\n";
    std::cin >> a >> b >> mod;
    //functions from static library
    std::cout << "Multiplication " << a << " " << b << " modulo " << mod << " result is " << mul(a, b, mod) << "\n";
    std::cout << "Addition " << a << " " << b << " modulo " << mod << " result is " << sum(a, b, mod) << "\n";
    std::cout << "Subtraction " << a << " " << b << " modulo " << mod << " result is " << sub(a, b, mod) << "\n";
    std::cout << "Type two natural numbers:\n";
    //functions from first dynamic library
    int n;
    std::cin >> n >> mod;
    std::cout << n << "-th fibonacci number modulo " << mod << " is " << nth_fibonacci(n, mod) << "\n";
    std::cout << n <<"! modulo " << mod << " is " << factorial(n, mod) << "\n";
    
    bool (*ptr_prime)(int);
    bool (*ptr_composite)(int);
    void* libprime = dlopen("./libprime.so", RTLD_LAZY | RTLD_GLOBAL);
    if (!libprime) {
        std::cerr << "Couldn't open libprime.so: " << dlerror() << "\n";
        return 0;
    }

    ptr_prime = (bool(*)(int))get_pointer(libprime, "is_prime");
    ptr_composite = (bool(*)(int))get_pointer(libprime, "is_composite");

    int p;
    std::cout << "Type one natural number:\n";
    std::cin >> p;
    
    if (ptr_prime) {
        bool prime = ptr_prime(p);
        if (prime) {
            std::cout << p << " is a prime number\n";;
        } else {
            std::cout << p << " isn't a prime number\n";;
        }
    }
    if (ptr_composite) {
        bool composite = ptr_composite(p);
        if (composite) {
            std::cout << p << " is a composite number\n";;
        } else {
            std::cout << p << " isn't a composite number\n";;
        }
    }

    int status = dlclose(libprime);
    if (status != 0) {
        std::cerr << "Can't close libprime.so " << dlerror() << "\n";
        return 0;
    }
    return 0;
}
