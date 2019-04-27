#include "lib.h"

#include <iostream>

static_assert(rd::getPlatformIndependentHash("InternScopeInExt") == -4122988489618686035L);

int main() {
	constexpr auto h = rd::getPlatformIndependentHash("Hello world");
	std::cout << rd::to_string(h) << std::endl;
}