#include "CaesarCypher.h"

std::string caesar(std::string& s, int shift) {
    std::string result;
    int length = s.size();

    for (int i = 0; i < s.size(); ++i) {
        result += (s[(i + shift) % length]);
    }

    return result;
}
