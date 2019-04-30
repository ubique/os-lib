#pragma once

#include <iostream>

const static char *BLUE = "\033[1;34m";
const static char *GREEN = "\033[0;32m";
const static char *RED = "\033[1;31m";
const static char *END = "\033[0m";

void printColorText(const char *color, const char *text);

void printError(const char *text, const char *moreText);
