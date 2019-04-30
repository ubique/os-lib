#include <iostream>
#include "helper.h"

void printColorText(const char *color, const char *text) {
    printf("%s%s%s", color, text, END);
}

void printError(const char *text, const char *moreText) {
    printColorText(RED, text);
    printf("%s\n", moreText);
}
