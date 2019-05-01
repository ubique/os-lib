#include "static.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

typedef std::vector<std::string> digit;

static std::vector<digit> DIGITS{
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
        "|____/ "
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
static unsigned int NROW = 6;

void print_ascii_number(unsigned int value) {
    static std::string BLUE = "\033[34;1m";
    static std::string WHITE = "\033[0m";

    std::vector<int> decompose;
    while (value > 0) {
        decompose.push_back(value % 10);
        value /= 10;
    }
    std::reverse(decompose.begin(), decompose.end());

    std::cout << BLUE;
    for (unsigned int i = 0; i < NROW; i++) {
        for (int d : decompose) {
            std::cout << DIGITS[d][i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << WHITE;
}