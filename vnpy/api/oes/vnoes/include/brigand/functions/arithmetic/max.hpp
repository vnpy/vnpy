/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_FUNCTIONS_ARITHMETIC_MAX_HPP
#define BOOST_BRIGAND_FUNCTIONS_ARITHMETIC_MAX_HPP
#include <brigand/types/integral_constant.hpp>

namespace brigand
{
template <typename A, typename B>
struct max : brigand::integral_constant<
                 typename std::decay<decltype((A::value < B::value) ? B::value : A::value)>::type,
                 (A::value < B::value) ? B::value : A::value>
{};
}
#endif
