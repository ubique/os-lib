#include <iostream>
#include <dlfcn.h>
#include "static/multiplication.h"
#include "firstDynamic/logarithm.h"
#include "secondDynamic/exponentiation.h"

using namespace std;

int main() {
    int a, b;
    void *lib;
    cout << "Введите 2 числа: " << endl;
    cin >> a >> b;
    cout << "a * b = " << getMult(a, b) << endl;
    cout << "log(a) / log(b) = " << getLog(a, b) << endl;
    lib = dlopen("secondDynamic.so", RTLD_LAZY);
    if (lib == nullptr) {
        cout << dlerror() << endl;
        exit(1);
    }
    auto exp = (int (*)(int, int)) dlsym(lib, "getExp");
    if (exp == nullptr) {
        cout << dlerror() << endl;
        exit(1);
    }
    cout << "a ** b = " << exp(a, b) << endl;
    dlclose(lib);
}