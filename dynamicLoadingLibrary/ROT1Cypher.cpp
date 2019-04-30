#include "ROT1Cypher.h"

std::string ROT1(std::string& s) {
    std::string result;

    for (char i : s) {
        result += ((i != 'z') ? i + 1 : i);
    }

    return result;
}