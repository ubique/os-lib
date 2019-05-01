//
// Created by roman on 01.05.19.
//

#include <iostream>
#include <dlfcn.h>
#include "st.h"
#include "dyn1.h"
#include <stdio.h>
#include <stdlib.h>

using std::cout;
using std::cin;

int main() {
    int a, b;
    cin >> a >> b;
    cout << "Sum from static lib: " << sum(a, b) << std::endl;
    cout << "Multiplication from first dynamic lib: " << multiplication(a, b) << std::endl;

    void *handle = dlopen("./tmp/libdyn2.so", RTLD_NOW);
    if (!handle) {
        cout << "Error occurred: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
    auto func = ((int (*)(int, int)) dlsym(handle, "division"));
    if (func == nullptr) {
        cout << "Error occurred: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
    cout << "Division from second dynamic lib: " << func(a, b) << std::endl;
    if (dlclose(handle)) {
        cout << "Error occurred: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}