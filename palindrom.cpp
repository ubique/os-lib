//
// Created by Кирилл Чулков on 2019-05-01.
//

#include <cstddef>

#include "palindrom.h"

bool isPalindrom(const std::string& word) {
    size_t n = word.size();
    for (int i = 0; i < n / 2; ++i) {
        if (word[i] != word[n - i - 1]) {
            return false;
        }
    }
    return true;
}
