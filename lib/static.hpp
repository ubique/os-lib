#ifndef STATIC_HPP
#define STATIC_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

inline void print_ascii_number(unsigned int value) {
    typedef std::vector<std::string> digit;
    static std::vector<digit> digits{
        {
            "  ___  ",
            " / _ \\ ",
            "| | | |",
            "| | | |",
            "| |_| |",
            " \\___/ ",
        },
        {
            " __ ",
            "/_ |",
            " | |",
            " | |",
            " | |",
            " |_|",
        },
        {
            " ___  ",
            "|__ \\ ",
            "   ) |",
            "  / / ",
            " / /_ ",
            "|____|"
        },
        {
            " ____  ",
            "|___ \\ ",
            "  __) |",
            " |__ < ",
            " ___) |",
            "|____/"
        },
        {
            " _  _ ",
            "| || |",
            "| || |",
            "|__  |",
            "   | |",
            "   |_|"
        },
        {
            " _____ ",
            "|  ___|",
            "| |__  ",
            "|___ \\ ",
            " ___) |",
            "|____/ "
        },
        {
            "   _   ",
            "  / /  ",
            " / /_  ",
            "|  _ \\ ",
            "| ( ) |",
            " \\___/ "
        },
        {
            " ______ ",
            "|____  |",
            "    / / ",
            "   / /  ",
            "  / /   ",
            " /_/    "
        },
        {
            "  ___  ",
            " / _ \\ ",
            "| (_) |",
            " > _ < ",
            "| (_) |",
            " \\___/ "
        },
        {
            "  ___  ",
            " / _ \\ ",
            "| (_) |",
            " \\__  |",
            "   / / ",
            "  /_/  "
        }
    };
    static unsigned int nrow = 6;

    static std::string BLUE = "\033[34m";
    static std::string WHITE = "\033[0m";

    std::vector<int> decompose;
    while (value > 0) {
        decompose.push_back(value % 10);
        value /= 10;
    }
    std::reverse(decompose.begin(), decompose.end());

    std::cout << BLUE;
    for (unsigned int i = 0; i < nrow; i++) {
        for (int d : decompose) {
            std::cout << digits[d][i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << WHITE;
}

#endif // STATIC_HPP
