//
// Created by Кирилл Чулков on 2019-05-01.
//

#include <iostream>

#include "fibonacci.h"
#include "palindrom.h"
#include "greeting.h"

int main() {
    greeting("Kirill");
    std::cout << calculateFibonacci(100) << std::endl;
    std::cout << isPalindrom("kek") << std::endl;
    std::cout << isPalindrom("keek") << std::endl;
}