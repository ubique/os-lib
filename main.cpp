#include <iostream>
#include <dlfcn.h>

#include "hello_name.h"
#include "dynamic1.h"
#include "dynamic2.h"

void error(std::string message) {
	std::cerr << message << std::endl;
	exit(EXIT_FAILURE);
}

int main() {
    //static
    std::cout << "Enter your name, please." << std::endl;
    std::string name;
    std::cin >> name;
    std::cout << hello_name(name) << std::endl;


    //first dynamic
    std::cout << "How old are you?" << std::endl;
    int age;
    std::cin >> age;
    if (age < 0) {
        std::cout << "You lie to me!\n";
        return EXIT_FAILURE;
    }
    std::cout << about_age(age) << std::endl;


    //second dynamic
    void *dynamic2 = dlopen("libdynamic2.so", RTLD_LAZY);

    if (dynamic2 == nullptr) {
    	error(dlerror());
    }

	std::string (*sweet)(std::string name) = (std::string(*)(std::string name))dlsym(dynamic2, "sweet");
	if (sweet == nullptr) {
		error(dlerror());
	}
	std::cout << sweet(name) << std::endl;

	int status = dlclose(dynamic2);

	if (status != 0) {
		error(dlerror());
	}
}

