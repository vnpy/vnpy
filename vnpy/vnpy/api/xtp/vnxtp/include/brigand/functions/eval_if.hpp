/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_FUNCTIONS_EVAL_IF_HPP
#define BOOST_BRIGAND_FUNCTIONS_EVAL_IF_HPP

#include <type_traits>

namespace brigand
{

  template <typename Condition, typename A, typename B>
  struct eval_if
  {
    using type = typename std::conditional<Condition::value, A, B>::type::type;
  };

  template <bool Condition, typename A, typename B>
  struct eval_if_c
  {
    using type = typename std::conditional<Condition, A, B>::type::type;
  };

}
#endif
