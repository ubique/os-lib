#include <iostream>
#include "staticLibrary/charToNumCypher.h"
#include "dynamicLinkingLibrary/CaesarCypher.h"
#include <dlfcn.h>


void printErr(const std::string& message) {
    fprintf(stderr, "ERROR %s: %s\n", message.c_str(), dlerror());
}

void printUsage() {
    printf("Usage:\n"
           "This program codes given string by various encryption:\n"
           "1) All chars to their number\n"
           "2) Caesar cypher by given shift\n"
           "3) ROT1 cypher\n");
}

int main() {
    printUsage();
    std::string s;

    std::cout << "Input string to code:\n";
    std::cin >> s;

    std::cout << "Simple coding by function from static library:\n";
    std::cout << s << " -> " << charToNum(s) << "\n";

    std::cout << "Input shift for Caesar cypher:\n";
    int shift;
    std::cin >> shift;
    std::cout << "Coding by Caesar cypher from dynamic linked library:\n";
    std::cout << s << " -> " << caesar(s, shift) << "\n";

    void* loadedLibrary = dlopen("./libLoading.so", RTLD_LAZY);

    if (loadedLibrary == nullptr) {
        printErr("Unable to load library");
        exit(EXIT_FAILURE);
    } else {
        auto ROT1 = (std::string (*)(std::string&)) dlsym(loadedLibrary, "ROT1");

        if (!ROT1) {
            printErr("Unable to load ROT1 function");
            dlclose(loadedLibrary);
            exit(EXIT_FAILURE);
        } else {
            std::cout << "Coding by ROT1 cypher from dynamic loaded library:\n";
            std::cout << s << " -> " << ROT1(s) << "\n";
            dlclose(loadedLibrary);
        }
    }

    exit(EXIT_SUCCESS);
}
