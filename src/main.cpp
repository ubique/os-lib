#include <cstring>
#include <dlfcn.h>
#include <iostream>

std::string get_data_from_first_supplier();
std::string get_data_from_second_supplier();

struct dlhandler {
    void *handle;

    dlhandler(char const *name) { handle = dlopen(name, RTLD_LAZY); }

    void *get(char const *symbol) { return dlsym(handle, symbol); }

    dlhandler(dlhandler const &) = delete;

    ~dlhandler()
    {
        if (handle != nullptr) {
            if (dlclose(handle) != 0) {
                std::cerr << dlerror() << std::endl;
            }
        }
    }
};

int main()
{
    dlhandler handler("libthird_supplier.so");
    if (handler.handle == nullptr) {
        std::cerr << dlerror() << std::endl;
        return 1;
    }
    std::string (*get_data_from_third_supplier)() =
        reinterpret_cast<std::string (*)()>(
            handler.get("get_data_from_third_supplier"));
    if (get_data_from_third_supplier == nullptr) {
        std::cerr << dlerror() << std::endl;
        return 1;
    }
    std::cout << get_data_from_first_supplier() << " "
              << get_data_from_second_supplier() << " "
              << get_data_from_third_supplier() << std::endl;
    return 0;
}
