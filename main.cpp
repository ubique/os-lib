#include <iostream>
#include <string>
#include <dlfcn.h>
#include "combination.h"
#include "printer.h"

const char LOADED_LIB_NAME [] = "./libfibonacci.so";

void printErrorMessage(std::string const& message) {
    std::cerr << message <<": " << dlerror() << std::endl;
}

int main() {
    int number = 0;
    unsigned long long mask = 0;
    int numberNth = 0;

    std::cout << "Type in integer number" << std::endl;
    std::cin >> number;
    printInteger(number);

    std::cout << "Type in unsigned long long (combination bit mask)" << std::endl;
    std::cin >> mask;
    unsigned long long nextMask = nextCombinationMask(mask);
    std::cout << "Next combination mask = " << nextMask << std::endl;

    std::cout << "Type in Fibonacci number you want to calculate" << std::endl;
    void* loadedLibrary = dlopen(LOADED_LIB_NAME, RTLD_LAZY);
    if (loadedLibrary == nullptr) {
        printErrorMessage("Failed to load library");
        exit(EXIT_FAILURE);
    }
    auto fibNumberFunction = (int (*)(int)) dlsym(loadedLibrary, "calculateNthFibonacci");
    if (fibNumberFunction == nullptr) {
        printErrorMessage("Failed lo load symbol");
        if (dlclose(loadedLibrary) != 0) {
            printErrorMessage("Failed to close library");
        }
        exit(EXIT_FAILURE);
    }
    int fibNumber = fibNumberFunction(numberNth);
    std::cout << fibNumber << std::endl;
    if (dlclose(loadedLibrary) != 0) {
        printErrorMessage("Failed to close library");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}