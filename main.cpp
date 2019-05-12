#include <iostream>
#include "hello.h"
#include "answer.h"
#include <dlfcn.h>

using namespace std;

int main() {
    int input;
    typedef char *(*my_comparator)(int);
    my_comparator comparator = nullptr;
    void *lib_handle = nullptr;

    cout << say_hello(); // static library
    cin >> input;

    lib_handle = dlopen("libcompare.so", RTLD_LAZY); //second_dynamic
    if (!lib_handle) {
        cout << "Error occurred during opening: " << dlerror() << '\n';
        return 1;
    }
    comparator = (my_comparator) dlsym(lib_handle, "comparotor");
    if (!comparator) {
        cout << "Error occurred during loading library: " << dlerror() << '\n';
    } else {
        if (comparator(input)) {
            cout << "Absolutely!\n";
        } else {
            cout << "You're wrong!\n";
            cout << answer(); //first_dynamic
        }
    }
    if (dlclose(lib_handle) != 0) {
        cout << "Error occurred during closing library: " << dlerror() << '\n';
    }



    return 0;
}
