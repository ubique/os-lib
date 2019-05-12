#include <iostream>
#include "birb.hpp"
#include "bee.hpp"
#include <dlfcn.h>
using namespace std;

int main() {
    birb();
    bee();
    void* handle = dlopen("libflower.so", RTLD_LAZY);
    if (!handle) {
       cerr << "Can't open library: " << dlerror() << endl;
       return EXIT_FAILURE;
    }
    
    typedef void (*void_func)();
    void_func flower = (void_func) dlsym(handle, "_Z6flowerv");
    if (!flower) {
       cerr << "Can't find symbol 'flower': " << dlerror() << std::endl;
    } else {
       flower();
    }
    if (dlclose(handle))  {
       cerr << "Can't close library: " << dlerror() << endl;
    	return EXIT_FAILURE;
    }
    return 0;
}
