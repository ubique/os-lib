#include "lib.h"

#include <iostream>

static_assert(rd::getPlatformIndependentHash("InternScopeInExt") == -4122988489618686035L);

int main() {
	constexpr const char *string = "Hello world";
	constexpr auto h = rd::getPlatformIndependentHash(string);
	std::cout << "Hash of string: " << string << "=" << h << std::endl;

	int64_t mix1 = rd::mix("Hello ", "world");
	int64_t mix2 = rd::mix(std::string("Hello "), std::string("world"));
	std::cout << mix1 << std::endl;
	std::cout << mix2 << std::endl;

	return 0;
}