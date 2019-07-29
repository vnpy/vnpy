/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_FUNCTIONS_COMPARISON_LESS_EQUAL_HPP
#define BOOST_BRIGAND_FUNCTIONS_COMPARISON_LESS_EQUAL_HPP
#include <brigand/types/bool.hpp>

namespace brigand
{
  template <typename A, typename B>
  struct less_equal : bool_ < (A::value <= B::value) > {};
}
#endif
