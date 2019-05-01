#include <iostream>
#include "static.h"
#include "first_dynamic.h"
#include <dlfcn.h>
#include <cstring>

using namespace std;

typedef const char*(*func)();

int main() {
    cout << getStatic() << endl;
    cout << getFirstDynamic() << endl;

    void *second = dlopen("libsecond_dynamic.so", RTLD_LAZY);
    if (second == nullptr) {
        cout << dlerror() << endl;
        return EXIT_FAILURE;
    }

    func result = func(dlsym(second, "getSecondDynamic"));
    if (result == nullptr) {
        cout << dlerror() << endl;
        return EXIT_FAILURE;
    } else {
        cout << result() << endl;
    }

    if (dlclose(second)) {
        cout << dlerror() << endl;
        return EXIT_FAILURE;
    }
}