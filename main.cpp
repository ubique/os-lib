#include <iostream>
#include <string>
#include <dlfcn.h>

#include "slow.h"
#include "fast.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

constexpr int64_t slowCutoff = 1'000'000;
constexpr int64_t fastCutoff = 1'000'000'000'000;

void print_result(const string &name, const string &result) {
    cout << "According to " << name << " test the number " << result;
}

int main() {
    cout << "Enter positive number" << endl;
    uint64_t number;
    cin >> number;

    if (number < slowCutoff) {
        cout << "Using function from static library" << endl;

        bool slow = test_slow(number);
        print_result("slow", (slow ? "is prime" : "is not prime"));
    } else {
        cout << "Slow test was not run";
    }
    cout << endl << endl;

    if (number < fastCutoff) {
        cout << "Using function from dynamic library" << endl;

        bool fast = test_fast(number);
        print_result("fast", (fast ? "is prime" : "is not prime"));
    } else {
        cout << "Fast test was not run";
    }
    cout << endl << endl;

    auto handle = dlopen("./libprime_fermat.so", RTLD_LAZY);
    if (handle == nullptr) {
        cerr << "Could not load library: " << dlerror() << endl;
        return 0;
    }

    auto test_fermat = reinterpret_cast<bool (*)(int64_t)>(dlsym(handle, "test_fermat"));
    if (test_fermat == nullptr) {
        cerr << "Could not load function: " << dlerror() << endl;
        return 0;
    }

    cout << "Using function from manually linked library" << endl;
    bool fermat = test_fermat(number);
    print_result("Fermat", (fermat ? "may be prime" : "is not prime"));
    cout << endl;

    if (dlclose(handle) != 0) {
        cerr << "Could not close library: " << dlerror() << endl;
    }

    return 0;
}