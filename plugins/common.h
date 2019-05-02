#pragma once

#include <string>
#include <sstream>

using namespace std;


char *getCharPtr(string s) {
    char *res = new char[s.size() + 1];
    copy(s.begin(), s.end(), res);
    res[s.size()] = 0;

    return res;
}


stringstream getStream(const char *s) {
    return stringstream(s);
}

