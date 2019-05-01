#include <string>
#include <algorithm>

using namespace std;


char *getCharPtr(string s) {
    char *res = new char[s.size() + 1];
    copy(s.begin(), s.end(), res);
    res[s.size()] = 0;

    return res;
}


extern "C" char const *reverse(char const *arg) {
    string s = arg;
    reverse(s.begin(), s.end());
    return getCharPtr(s);
}

