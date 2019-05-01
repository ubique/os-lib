#include <iostream>
#include <dlfcn.h>
#include "add.h"
#include "subtract.h"

using namespace std;

int main()
{
    cout << "hello\nenter two numbers\n";
    int a, b;
    cin >> a >> b;
    cout << a << " + " << b << " = " << add(a, b) << '\n';
    cout << a << " - " << b << " = " << subtract(a, b) << '\n';


    void* handle = dlopen("libmultiply.so", RTLD_LAZY);
    if (!handle) {
        cout << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }
    typedef int (*multiply_t)(int, int);
    multiply_t multiply = (multiply_t) dlsym(handle, "multiply");
    if (!multiply) {
        cout << "Cannot load symbol 'multiply': " << dlerror() << '\n';
    } else {
        cout << a << " * " << b << " = " << multiply(a, b) << '\n';
    }
    if (dlclose(handle) != 0) {
        cout << "Cannot close library: " << dlerror() << '\n';
    }


    return 0;
}
