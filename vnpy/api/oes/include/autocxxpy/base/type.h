#pragma once

namespace autocxxpy
{
    template <class element, size_t size>
    using literal_array = element[size];
    

    // specialization for char[]
    template <size_t size>
    using string_literal = literal_array<char, size>;
}