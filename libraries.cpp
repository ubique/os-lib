#include <dlfcn.h>
#include <iostream>
#include "shared/fibonacci.h"
#include "static/power.h"
#include "loadable/factorial.h"

using namespace std;

typedef int(*loaded_function_type)(int);

int main() {
	cout << "5^3 = " << power(5, 3) << endl; //static

	cout << "5th fibonacci number = " << fibonacci(5) << endl; //dynamic

	void* lib = dlopen("./loadable/loadable_library.so", RTLD_LAZY);

	if (lib == nullptr) {
		cout << dlerror() << endl;
		return 1;
	}

	loaded_function_type factorial = (loaded_function_type)dlsym(lib, "factorial");
     
	if (factorial == nullptr) {
		cout << dlerror() << endl;
		dlclose(lib);
		return 1;
	}

	cout << "5! = " << factorial(5) << endl; //loaded

	dlclose(lib);

	return 0;
}

