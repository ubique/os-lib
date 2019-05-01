#include <iostream>
#include <dlfcn.h>
#include <vector>

double average(double, double, double);

void printIntsVector(std::vector<int>&);

int main(int argc, char** argv)
{
    //testing static library
    std::cout << average(3, 2, 2) << std::endl;

    //testing dynamic library
    std::vector<int> myVec{1, 2, 3, 4, 5};
    printIntsVector(myVec);

    //loading second dynamic library
    void* ptr = dlopen("libDynamicSecond.so", RTLD_LAZY);
    if (!ptr)
    {
        std::cout << "An error has occured while opening the dynamic library.\n";
        std::cout << dlerror();
        exit(EXIT_FAILURE);
    }
    auto func = (int(*)(int))(dlsym(ptr, "square"));
    char* errorText = dlerror();
    if (errorText != NULL)
    {
        std::cout << "An error has occured while loading function from the dynamic library.\n";
        std::cout << errorText;
        exit(EXIT_FAILURE);
    }
    std::cout << func(12) << std::endl;
    if (dlclose(ptr) != 0)
    {
        std::cout << "An error has occured while closing the dynamic library.\n";
        std::cout << dlerror();
    }
    return 0;
}