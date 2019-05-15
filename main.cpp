#include <iostream>
#include <dlfcn.h>
#include "avg_static.h"
#include "min_dll.h"

using namespace std;

typedef int (*max_f)(int, int);

int main() {
    int a, b;
    cout << "Enter two numbers:" << endl;
    cin >> a >> b;
    cout << "average of numbers: " << avg(a, b) << endl;
    cout << "minimum of numbers: " << min_dll(a, b) << endl;

    void* runtime_dll = dlopen("libmax_dll.so", RTLD_LAZY);
    if (!runtime_dll) {
        cout << "Error occurred while opening the library:" << endl;
        cout << dlerror();
        return EXIT_FAILURE;
    }

    auto max_dll = max_f(dlsym(runtime_dll, "max_dll"));
    if (max_dll) {
        cout << "maximum of numbers: " << max_dll(a, b) << endl;
    }
    else {
        cout << "Error occurred while loading symbols:" << endl;
        cout << dlerror();
        return EXIT_FAILURE;
    }
    if (dlclose(runtime_dll) != 0) {
        cout << "Error occurred while closing the library:" << endl;
        cout << dlerror();
        return EXIT_FAILURE;
    }
    return 0;
}