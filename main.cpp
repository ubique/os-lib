#include <iostream>
#include <dlfcn.h>

#include "and_static.h"
#include "or_dynamic.h"

using namespace std;

void printInfo() {
    cout << "Program calculates and prints: " << endl;
    cout << "bit and of two numbers using static lib" << endl;
    cout << "bit or of two numbers using dynamic lib" << endl;
    cout << "bit xor of two numbers using loaded lib" << endl;
    cout << "Enter two integers" << endl;
}

const char* GENERATED_LOADED_LIB_NAME = "libxor_loaded.so";

int main() {
    printInfo();
    int num1, num2;
    cin >> num1 >> num2;
    cout << andStatic(num1, num2) << endl;
    cout << orDynamic(num1, num2) << endl;

    void *libLoaded = dlopen(GENERATED_LOADED_LIB_NAME, RTLD_LAZY);
    if (libLoaded == nullptr) {
        cerr << "Cannot load lib: " << dlerror() << endl;
        return EXIT_FAILURE;
    }
    auto xorLoaded = (int (*)(int, int)) dlsym(libLoaded, "xorLoaded");
    if (xorLoaded == nullptr) {
        cerr << "Cannot load function from lib: " << dlerror() << endl;
        return EXIT_FAILURE;
    }
    cout << xorLoaded(num1, num2) << endl;
    if (dlclose(libLoaded) != 0) {
        cerr << "Cannot close lib: " << dlerror() << endl;
        return EXIT_FAILURE;
    }
    return 0;
}