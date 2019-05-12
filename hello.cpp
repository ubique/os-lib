//
// Created by Yaroslav on 12/05/2019.
//

#include "hello.h"

char* say_hello() {
    return const_cast<char *>("Hello, world!\nWhat is 245 - 6?\n");
}