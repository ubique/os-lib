extern "C"
unsigned int myShiftFunction(unsigned int base) {
    return base >> static_cast<unsigned int>(1);
}