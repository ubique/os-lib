#include <cstdint>
#include <cassert>

using generator_t = uint64_t const (*) (int seed);


extern "C" // avoiding name mangling
{

void test_generators(generator_t gen)
{
    assert(gen(0) == 0 && "Gen(0) must be zero for backdoors");
}

}
