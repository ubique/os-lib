//
// Created by daniil on 01.05.19.
//

#include "hello.h"
#include "module.h"
#include <iostream>
#include <dlfcn.h>

int main() {
    std::cout << "Test static library\n" <<
              "Type string" << std::endl;
    std::string str;
    std::cin >> str;
    hello(str);
    std::cout << "Test first dynamic library\n" <<
              "Type one number" << std::endl;
    int num;
    std::cin >> num;
    std::cout << module(num) << "\n";
    std::cout << "Test second dynamic library\n" <<
              "Type two numbers" << std::endl;
    int a, b;
    std::cin >> a >> b;
    void *function = dlopen("libpow.so", RTLD_NOW);
    if (!function) {
        std::cout << "Can't open library: " << dlerror() << std::endl;
        return 1;
    }
    void* ans = dlsym(function, "my_pow");
    if (!ans) {
        std::cout << "Can't load 'my_pow'" << dlerror() << std::endl;
    } else {
        std::cout << (int (*)(int, int)) (ans) << std::endl;
    }
    if (dlclose(function) != 0) {
        std::cout << "Can't close library" << dlerror() << std::endl;
    }
    return 0;
}