/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_FUNCTIONS_ARITHMETIC_COMPLEMENT_HPP
#define BOOST_BRIGAND_FUNCTIONS_ARITHMETIC_COMPLEMENT_HPP
#include <brigand/types/integral_constant.hpp>

#include <brigand/types/args.hpp>

namespace brigand
{
template <typename A>
struct complement
    : brigand::integral_constant<typename A::value_type, typename A::value_type(~A::value)>
{
};
}
#endif
