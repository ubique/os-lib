#ifndef LIB_BOTTLES
#define LIB_BOTTLES

#include <ostream>

struct n_bottles {
    size_t n;

    n_bottles(size_t n);

    operator int() const;
};

std::ostream& operator<<(std::ostream& out, n_bottles b);

void print_bottles();

#endif
