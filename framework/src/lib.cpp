#include "lib.h"

#include <iostream>

namespace rd {

	hash_t mixImpl(hash_t x, hash_t y) noexcept {
		return static_cast<hash_t>(x * detail::HASH_FACTOR + static_cast<detail::constexpr_hash_t>(y + 1));
	}

	[[maybe_unused]] hash_t mix(std::string_view x, std::string_view y) noexcept {
		return mixImpl(
				getPlatformIndependentHash(y),
				getPlatformIndependentHash(x)
		);
	}
}