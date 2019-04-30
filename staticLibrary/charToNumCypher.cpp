#include "charToNumCypher.h"

std::string charToNum(std::string& s) {
    std::string result;

    for (char i : s) {
        result += std::to_string(i);
    }

    return result;
}