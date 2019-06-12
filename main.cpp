#include <iostream>
#include <dlfcn.h>


void printBinary(unsigned int);


unsigned int setBit(unsigned int, unsigned int);


using ui = unsigned int;

int main() {
    unsigned int base = 4;
    std::cout << "Static:\n";
    printBinary(base);
    std::cout << "Dynamic:\n" << setBit(base, 1) << std::endl;

    void* lib = dlopen("libdynlink.so", RTLD_LAZY);
    if (lib) {
        auto rShift = (ui (*)(ui)) (dlsym(lib, "myShiftFunction"));
        char* error;
        if ((error = dlerror()) == nullptr) {
            std::cout << "Dynamic linking:\n";
            std::cout << rShift(base) << std::endl;


            if (dlclose(lib) != 0) {
                std::cerr << "Couldn't close lib 'libDynLink.so' " << dlerror() << std::endl;
            }

        } else {
            std::cerr << "Couldn't load function 'unsigned int (*)(unsigned int)' from lib " << error << std::endl;
        }
    } else {
        std::cerr << "Couldn't open lib 'libDynLink.so' " << dlerror() << std::endl;
    }

    return 0;
}