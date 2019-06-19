#pragma once

#include <type_traits>

namespace autocxxpy
{
    template <class element, size_t size>
    using literal_array = element[size];
    

    // specialization for char[]
    template <size_t size>
    using string_literal = literal_array<char, size>;

    template <size_t size>
    using const_string_literal = literal_array<const char, size>;

    template <auto method>
    using function_constant = std::integral_constant<decltype(method), method>;
}