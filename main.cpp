//
// Created by Кирилл Чулков on 2019-05-01.
//

#include <iostream>
#include <string>
#include <dlfcn.h>

#include "greeting.h"
#include "fibonacci.h"

const char LOADED_LIB_NAME [] = "./libpalindrome.so";

void printErrorMessage(std::string const& message) {
    std::cerr << message <<": " << dlerror() << std::endl;
}

int main() {

    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    greeting(name);

    int n;
    std::cout << "Enter the number of the Fibonacci number you want to calculate: ";
    std::cin >> n;
    std::cout << calculateFibonacci(n) << "\n";

    std::string word;
    std::cout << "Enter a string to check if it is a palindrome: ";
    std::cin >> word;

    void* loadedLibrary = dlopen(LOADED_LIB_NAME, RTLD_LAZY);
    if (loadedLibrary == nullptr) {
        printErrorMessage("Failed to load library");
        exit(EXIT_FAILURE);
    }
    auto isPalindrome = (bool (*)(const std::string&)) dlsym(loadedLibrary, "isPalindrome");
    if (isPalindrome == nullptr) {
        printErrorMessage("Failed lo load function");
        if (dlclose(loadedLibrary) != 0) {
            printErrorMessage("Failed to close library");
        }
        exit(EXIT_FAILURE);
    }

    if (isPalindrome(word)) {
        std::cout << "This is a palindrome" << std::endl;
    } else {
        std::cout << "This is not a palindrome" << std::endl;
    }

    if (dlclose(loadedLibrary) != 0) {
        printErrorMessage("Failed to close library");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}