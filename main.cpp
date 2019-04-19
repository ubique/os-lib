#include "roots.h"
#include "xxhash.hpp"
#include <iostream>

#include <dlfcn.h>
#include <functional>

using namespace roots;

int main() {
    std::cout << "Useless numbers made by hash";
    char word[] = {'h', 'e', 'l', 'l', 'o'};
    xxh::hash64_t hash = xxh::xxhash<64>(word, sizeof(word));
    std::cout << hash << std::endl;
    std::cout << "Now give me value: ";
    double number;
    std::cin >> number;
    std::cout << "Here is the root power 3: " << root<3>(number) << std::endl;
    double idk[] = {root<2>(number), root<3>(number), root<100>(number)};
    std::cout << "I can predict your future, so here is one meaningful hash : "
              << xxh::xxhash<64>(idk, sizeof(idk)) << std::endl;

    std::cout
        << "Now lets have some fun and link shared library to this program"
        << std::endl;
    void *lib = dlopen("./libuseless.so", RTLD_LAZY);
    if (lib == nullptr) {
        std::cerr << "Error happened: " << dlerror() << std::endl;
        return -1;
    }
    auto say_hello = (const char *(*)())(dlsym(lib, "say_hello"));
    if (say_hello == nullptr) {
        std::cerr << "Error happened: " << dlerror() << std::endl;
        return -1;
    }
    std::cout << say_hello() << std::endl;
    if (dlclose(lib)) {
        std::cerr << "Closing lib error: " << dlerror() << std::endl;
    }
    return 0;
}
