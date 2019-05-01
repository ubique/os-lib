#include <iostream>
#include "inc.h"
#include "mul.h"
#include <dlfcn.h>


typedef const int(*func)(int const &, int const &);

void error(){
    std::cout << dlerror() << std::endl;
}

int main(){
    int a = 3, b = 5;
    std::cout << inc(a) << ' ' << a << std::endl;
    std::cout << "mul: " << ' ' << mul(a, b) << std::endl;

    void *second = dlopen("libsum.so", RTLD_NOW);

    if (!second){
        error();
        return 0;
    }

    func sum = reinterpret_cast<func>(dlsym(second, "sum"));

    if (!sum) {
        error();
        return 0;
    }

    std::cout << "sum: " << sum(a, b) << std::endl;

    if (dlclose(second)) {
        error();
    }
    return 0;
}