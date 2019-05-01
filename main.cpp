//
// Created by Кирилл Чулков on 2019-05-01.
//

#include <iostream>

#include "fibonacci.h"
#include "palindrome.h"
#include "greeting.h"

int main() {
    greeting("Kirill");
    std::cout << calculateFibonacci(100) << std::endl;
    std::cout << isPalindrome("kek") << std::endl;
    std::cout << isPalindrome("keek") << std::endl;
}