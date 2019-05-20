#include <iostream>
#include "answer.hpp"
#include "dynamic.hpp"
#include <dlfcn.h>
void* getFunctionPointer(void* lib,const char* function){
    auto ptr = dlsym(lib,function);
    if(!ptr){
        std::cerr<<"Could not get the function pointer for "<<function<<"\n"<<dlerror();
        exit(EXIT_FAILURE);
    }
    return ptr;
}
int main() {
    std::cout<<"This is function from static lib(add 50 to 100):"<<answer()<<"\n";
    std::cout<<"This is message from dynamic lib:"<<"\n";
    saySmth();
    void* dynamic_lib = dlopen("libdynamic_second.so",RTLD_LAZY);
    if(!dynamic_lib){
        std::cerr<<"Could not open the dynamic lib"<<"\n";
        exit(EXIT_FAILURE);
    }
    
    auto func = reinterpret_cast<void(*)()>(getFunctionPointer(dynamic_lib,"hello"));
    func();
    dlclose(dynamic_lib);
    return 0;
}
