#ifndef HW4_LIB_H
#define HW4_LIB_H

#include <string_view>

namespace rd {
	using hash_t = int64_t;
	using constexpr_hash_t = uint64_t;

	constexpr constexpr_hash_t DEFAULT_HASH = 19;
	constexpr constexpr_hash_t HASH_FACTOR = 31;

	constexpr hash_t hashImpl(rd::constexpr_hash_t initial, char const *begin, char const *end) {
		return (begin == end) ? initial : hashImpl(initial * HASH_FACTOR + *begin, begin + 1, end);
	}

	constexpr hash_t getPlatformIndependentHash(std::string_view that, constexpr_hash_t initial = DEFAULT_HASH) {
		return static_cast<hash_t>(hashImpl(initial, &that[0], &that[that.length()]));
	}

	std::string to_string(hash_t val);
}

#endif //HW4_LIB_H