#ifndef HW4_LIB_H
#define HW4_LIB_H

#include "util.h"

#include <string_view>

namespace rd {
	using hash_t = int64_t;
	namespace detail {
		using constexpr_hash_t = std::make_unsigned<uint64_t>::type;
		constexpr constexpr_hash_t DEFAULT_HASH = 19;
		constexpr constexpr_hash_t HASH_FACTOR = 31;
	}

	//only inline
	constexpr hash_t hashImpl(rd::detail::constexpr_hash_t initial, char const *begin, char const *end) noexcept {
		return (begin == end) ? initial : hashImpl(initial * detail::HASH_FACTOR + *begin, begin + 1, end);
	}

	//only inline
	constexpr hash_t
	getPlatformIndependentHash(std::string_view that,
							   detail::constexpr_hash_t initial = detail::DEFAULT_HASH) noexcept {
		return static_cast<hash_t>(hashImpl(initial, &that[0], &that[that.length()]));
	}

	extern "C"
	DLL_LOCAL
	hash_t mixImpl(hash_t x, hash_t y) noexcept;

	extern "C"
	DLL_PUBLIC
	hash_t mix(std::string_view x, std::string_view y) noexcept;
}

#endif //HW4_LIB_H