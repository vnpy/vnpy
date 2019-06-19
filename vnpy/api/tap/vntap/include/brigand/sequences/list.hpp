/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_LIST_HPP
#define BOOST_BRIGAND_SEQUENCES_LIST_HPP

#include <brigand/types/integral_constant.hpp>

namespace brigand
{
// Types list
template <class... T>
struct list
{
};

// Values list
template <typename T, T... Values>
using integral_list = brigand::list<brigand::integral_constant<T, Values>...>;

// Empty list
using empty_sequence = brigand::list<>;
}
#endif
