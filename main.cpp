#include <iostream>
#include <dlfcn.h>
#include "dynamicLinkedGcd.h"
#include "staticDigitsSum.h"

int main() {
    int number;
    std::cout << "Enter one number to check static library, program will count sum of its digits:" << std::endl;
    std::cin >> number;
    std::cout << "Sum of digits of your number is: " << digitSum(number) << std::endl;
    std::cout << "Nice, let's now get to checking dynamic linked library :)" << std::endl;
    std::cout << "Enter two positive numbers in order to find their gcd" << std::endl;
    int first, second;
    std::cin >> first >> second;
    int gcdRes = gcd(first, second);
    std::cout << "Here it is: " <<  gcdRes << std::endl;
    std::cout << "Perfect, now I will prepare something in order to check dynamic loaded library" << std::endl;
    void* loadedLibrary = dlopen("./libfactorization.so", RTLD_LAZY);
    if (!loadedLibrary) {
        std::cerr << "Error while opening library: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
    auto factorize = (void (*)(int))dlsym(loadedLibrary, "factor");
    if (!factorize) {
        std::cout << "Error while loading function: " << dlerror() << std::endl;
        dlclose(loadedLibrary);
        exit(EXIT_FAILURE);
    }
    std::cout << "It's all ready now, type your number, to get it's prime factorization" << std::endl;
    std::cin >> number;
    std::cout << "Here we go:" << std::endl;
    factorize(number);
    std::cout << std::endl;
    std::cout << "That's all for now. Thanks for using my program :)" << std::endl;
    if (dlclose(loadedLibrary) != 0) {
        std::cerr << "Can't close library " << dlerror() << "\n";
        return 0;
    }
}