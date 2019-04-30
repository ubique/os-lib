#include <dlfcn.h>
#include "helper.h"
#include "dynamic1.h"
#include "dynamic2.h"

int main() {
    //static
    std::cout << "Enter string\n";
    std::string str;
    std::cin >> str;
    std::cout << "Your string: ";
    printColorText(BLUE, str.c_str());
    std::cout << "\n";

    //dinamic1
    int a, b;
    std::cout << "Enter two number\n";
    std::cin >> a >> b;
    std::cout << a << "^" << b << " = " << pow(a, b) << "\n";

    //dinamic2
    void *dynamic2 = dlopen("libdynamic2.so", RTLD_NOW);

    if (dynamic2 == nullptr) {
        printError("Error loading library", "");
        return -1;
    }

    int (*sum)(int a, int b) = (int(*)(int a, int b))dlsym(dynamic2, "sum");
    if (!sum) {
        printError("Error loading function", "");
        return -1;
    }
    std::cout << a << " + " << b << " = " << sum(a, b) << "\n";
    if (dlclose(dynamic2) != 0) {
        printError("Error closing library", "");
        return -1;
    }


    return 0;
}