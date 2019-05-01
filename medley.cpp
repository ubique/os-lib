#include <iostream>
#include <string>

#include <dlfcn.h>

#include "hello.hpp"
#include "bottles.hpp"
#include "file.hpp"

const std::string HELP_STRING = R"(medley - program to do absolutely useless things.

Available commands:
    hello       Prints "Hello, world!".
    bottles     Prints lyrics of "99 Bottles of Beer".
    file        Prints file with given path.
    help        Prints help message.
    exit        Quits.
)";

int main() {
    std::cerr << HELP_STRING;
    
    while (true) {
        std::string command;
        std::cout << "medley> ";
        std::cout.flush();

        if (!std::getline(std::cin, command)) {
            std::cerr << "medley: Can't read command, exiting" << std::endl;
            return EXIT_FAILURE;
        }
        
        if (command == "hello") {
            print_hello();
        } else if (command == "bottles") {
            print_bottles();
        } else if (command == "file") {
            std::string path;
            do {
                std::cerr << "Provide a path to file: ";
            } while (!(std::getline(std::cin, path)));
            void* library_handle = dlopen("libfile.so", RTLD_LAZY);
            if (!library_handle) {
                std::cerr << "medley: Can't open library: " << dlerror() << std::endl;
                continue;
            }

            typedef void (*print_t)(std::string);

            print_t print = (print_t)dlsym(library_handle, "_Z10print_fileRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE");

            if (!print) {
                std::cerr << "medley: Can't find symbol 'void print(const std::string&)': " << dlerror() << std::endl;
            } else {
                print(path);
            }
            
            if (dlclose(library_handle)) {
                std::cerr << "medley: Can't close library: " << dlerror() << std::endl;
            }
        } else if (command == "help") {
            std::cerr << HELP_STRING;
        } else if (command == "exit") {
            break;
        } else {
            std::cerr << "Invalid command, try 'help'." << std::endl;
        }
    }
    
    return EXIT_SUCCESS;
}
