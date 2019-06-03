/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ADAPTED_INTEGRAL_LIST_HPP
#define BOOST_BRIGAND_ADAPTED_INTEGRAL_LIST_HPP

#include <brigand/algorithms/transform.hpp>
#include <brigand/types/integral_constant.hpp>

namespace brigand
{

template <typename T>
struct make_integral : brigand::integral_constant<typename T::value_type, T::value>
{
};

template <typename L>
using as_integral_list = transform<L, make_integral<brigand::_1>>;
}
#endif
