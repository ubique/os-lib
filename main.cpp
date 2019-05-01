#include <iostream>
#include <dlfcn.h>

#include "libs/static/get_day.h"
#include "libs/dynamic1/get_month.h"

//int get_day();
//int get_month();

int main() {
    void* handle = dlopen("libget_year.so", RTLD_LAZY);
    if (handle == nullptr) {
        std::cerr << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }

    int (*get_year)() = reinterpret_cast<int (*)()>(dlsym(handle, "get_year"));
    if (get_year == nullptr) {
        std::cerr << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }

    printf("Today is %d/%d/%d", get_day(), get_month(), get_year());

    if (dlclose(handle) != 0) {
	std::cerr << dlerror() << std::endl;
    }

    return 0;
}
