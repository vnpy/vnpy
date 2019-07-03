/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_FUNCTIONS_MISC_SIZEOF_HPP
#define BOOST_BRIGAND_FUNCTIONS_MISC_SIZEOF_HPP
#include <brigand/types/integral_constant.hpp>

namespace brigand
{
template <typename T>
struct sizeof_ : brigand::integral_constant<unsigned int, sizeof(T)>
{
};
}
#endif
