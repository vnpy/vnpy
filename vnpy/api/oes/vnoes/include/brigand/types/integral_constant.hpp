/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_TYPES_INTEGRAL_CONSTANT_HPP
#define BOOST_BRIGAND_TYPES_INTEGRAL_CONSTANT_HPP

// having our own integral constant fixes brigand on systems with broken std::integral_constant
// implementations

namespace brigand
{

template <typename T, T Value>
struct integral_constant
{
    // no constexpr for maximum C++ 11 compatibility
    static const T value = Value;

    using value_type = T;
    using type = integral_constant<T, Value>;

    operator value_type() const { return (value); }

    value_type operator()() const { return (value); }
};

template <typename T, T Value>
const T integral_constant<T, Value>::value;

using true_type = ::brigand::integral_constant<bool, true>;
using false_type = ::brigand::integral_constant<bool, false>;
}
#endif
