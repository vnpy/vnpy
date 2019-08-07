#pragma once

namespace c2py
{
    template <size_t index, size_t size, class ... extra_info>
    constexpr bool check_not_out_of_bound()
    {
        static_assert(index < size, "out of bound!");
        return index < size;
    }
}