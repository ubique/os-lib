#include <dlfcn.h>

#include <cerrno>
#include <cmath>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <functional>
#include <string>

#include "fermat.h"

using ll = long long;

bool trial_division(const ll n);                 /* static linking */
bool miller_rabin(const ll n, int rounds = 0);   /* dynamic linking */
std::function<bool(ll)> fermat_func;             /* runtime dynamic linking */

void test(std::string msg, const std::function<bool()> &func)
{
    using namespace std::chrono;
    const high_resolution_clock::time_point t1 = high_resolution_clock::now();
    const auto res = func();
    const high_resolution_clock::time_point t2 = high_resolution_clock::now();
    const auto dur = duration_cast<microseconds>(t2 - t1).count();
    std::cout << msg << std::boolalpha << res << ". " << dur << std::endl;
}

int main()
{
    char * error;
    void * handle = dlopen("./libfermat.so", RTLD_LAZY | RTLD_GLOBAL);
    if (handle == nullptr)
    {
        std::cerr << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
    auto fermat = (bool(*)(ll))(dlsym(handle, "fermat"));
    if ((error = dlerror()) != nullptr)
    {
        std::cerr << error << std::endl;
        dlclose(handle); // need?
        exit(EXIT_FAILURE);
    }
    fermat_func = std::function<bool(ll)>(fermat);

    std::cout << "Enter number for primality test with 3 algorithms" << std::endl;
    ll num = 1;
    while (num != 0)
    {
        std::cin >> num;
        test("Simple: ", std::bind(&trial_division, num));
        test("Rabin:  ", std::bind(&miller_rabin, num, 0));
        test("Fermat: ", std::bind(fermat_func, num));
    }

    if (dlclose(handle) != 0)
    {
        std::cerr << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
