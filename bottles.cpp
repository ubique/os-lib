#include "bottles.hpp"
#include <iostream>

n_bottles::n_bottles(size_t n): n(n) {}

n_bottles::operator int() const {
    return n;
}

std::ostream& operator<<(std::ostream& out, n_bottles b) {
    if (b == 0) {
        return out << "no more bottles";
    } else if (b == 1) {
        return out << "1 bottle";
    } else {
        return out << int(b) << " bottles";
    }
}

void print_bottles() {
    for (int i = 99; i > 0; i--) {
        std::cout << n_bottles(i) << " of beer on the wall, " << n_bottles(i) << " of beer.\n"
                  << "Take one down and pass it around, " << n_bottles(i - 1) << " of beer on the wall.\n\n";
    }
    std::cout << "No more bottles of beer on the wall, no more bottles of beer.\n" 
              << "Go to the store and buy some more, 99 bottles of beer on the wall." << std::endl;
}
