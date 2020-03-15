/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_FUNCTIONS_BITWISE_BITXOR_HPP
#define BOOST_BRIGAND_FUNCTIONS_BITWISE_BITXOR_HPP

#include <brigand/types/integral_constant.hpp>

namespace brigand
{
template <typename A, typename B>
struct bitxor_ : brigand::integral_constant<typename A::value_type, A::value ^ B::value>
{
};
}
#endif
