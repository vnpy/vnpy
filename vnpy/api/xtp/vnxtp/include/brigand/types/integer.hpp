/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_TYPES_INTEGER_HPP
#define BOOST_BRIGAND_TYPES_INTEGER_HPP
#include <brigand/types/integral_constant.hpp>
#include <cstddef>
#include <cstdint>

namespace brigand
{
template <std::int8_t V>
using int8_t = brigand::integral_constant<std::int8_t, V>;

template <std::uint8_t V>
using uint8_t = brigand::integral_constant<std::uint8_t, V>;

template <std::int16_t V>
using int16_t = brigand::integral_constant<std::int16_t, V>;

template <std::uint16_t V>
using uint16_t = brigand::integral_constant<std::uint16_t, V>;

template <std::int32_t V>
using int32_t = brigand::integral_constant<std::int32_t, V>;

template <std::uint32_t V>
using uint32_t = brigand::integral_constant<std::uint32_t, V>;

template <std::int64_t V>
using int64_t = brigand::integral_constant<std::int64_t, V>;

template <std::uint64_t V>
using uint64_t = brigand::integral_constant<std::uint64_t, V>;

template <std::size_t V>
using size_t = brigand::integral_constant<std::size_t, V>;

template <std::ptrdiff_t V>
using ptrdiff_t = brigand::integral_constant<std::ptrdiff_t, V>;
}
#endif
