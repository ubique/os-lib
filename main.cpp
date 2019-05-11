#include "libs/include/dyn1.h"
#include "libs/include/static.h"

#include <cassert>
#include <cstdio>
#include <dlfcn.h>

int main()
{
    assert(generate_public_key(0) == 0);
    assert(generate_secret_key(0) == 0);

    auto dl_handle = dlopen("libdyn2_lb.so", RTLD_LAZY);

    if (!dl_handle)
    {
        fprintf(stderr, "Error loading lib: %s\n", dlerror());
        return -1;
    }

    dlerror();

    using generator_t = uint64_t const (*) (int seed);
    using tester_t = void(*)(generator_t generator);

    auto tester = (tester_t) dlsym(dl_handle, "test_generators");
    auto error = dlerror();
    if (error != nullptr)
    {
        fprintf(stderr, "Error symbol lookup %s\n", error);
        return -1;
    }

    tester(generate_public_key);
    tester(generate_secret_key);

    printf("Hooray!");

    dlclose(dl_handle);
    return 0;
}
