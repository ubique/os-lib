#include "common.h"
#include <algorithm>
#include <vector>
#include <numeric>


vector<int> readVector(stringstream &in) {
    vector<int> arr;
    int c;
    while (in >> c) {
        arr.push_back(c);
    }
    return arr;
}


extern "C" char const *sort(char const *arg) {
    auto in = getStream(arg);
    stringstream out;
    auto arr = readVector(in);

    sort(arr.begin(), arr.end());

    for (int q : arr) {
        out << q << ' ';
    }

    return getCharPtr(out.str());
}


extern "C" char const *sum(char const* arg){
    auto in = getStream(arg);
    stringstream out;
    auto arr = readVector(in);

    out << accumulate(arr.begin(), arr.end(), 0);

    return getCharPtr(out.str());
}

