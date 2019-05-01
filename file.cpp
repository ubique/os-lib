#include "file.hpp"
#include <cstring>
#include <fstream>
#include <iostream>

const size_t BUFFER_SIZE = 2048;

void print_file(const std::string& path) {
    std::ifstream in(path);
    
    if (in.fail()) {
        std::cerr << "medley/cat: Can't open file: " << std::strerror(errno) << std::endl;
        return;
    }
    
    char* buffer = new char[BUFFER_SIZE];
    while (in) {
        in.read(buffer, BUFFER_SIZE);
        std::cout << buffer;
    }
    delete[] buffer;
    
    if (in.bad()) {
        std::cerr << "medley/cat: Can't read file: " << std::strerror(errno) << std::endl;
    }
    
    in.close();
}
