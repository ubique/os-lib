#include <iostream>
#include "inc.h"
#include "mul.h"
#include <dlfcn.h>


typedef const int(*func)();

void error(){
    std::cout << dlerror() << std::endl;
}

int main(){
    int a = 3, b = 5;
    std::cout << a << ' ' << inc(a) << std::endl;
    std::cout << a << ' ' << mul(a, b) << std::endl;

    void *second = dlopen("libsecond_dynamic.so", RTLD_LAZY);

    if (!second){
        error();
        return 0;
    }

    func result = func(dlsym(second, "mul"));

    if (!result) {
        error();
        return 0;
    }

    std::cout << a * b << std::endl;

    if (dlclose(second)) {
        error();
    }
    return 0;
}