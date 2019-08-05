#pragma once

#include <stdint.h>

namespace c2py
{
    template <size_t ... vals>
    inline constexpr int64_t tsum() noexcept {
        if constexpr (sizeof...(vals) == 0) return 0;
        else return (vals + ...);
    }
    static_assert(tsum<1, 2, 3>() == 6);

    template <class ... T>
    inline constexpr int64_t tsum(const T& ... vals) noexcept {
        if constexpr (sizeof...(vals) == 0) return 0;
        else return (vals + ...);
    }
    static_assert(tsum(1, 2, 3) == 6);
}
