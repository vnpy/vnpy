/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ADAPTED_TUPLE_HPP
#define BOOST_BRIGAND_ADAPTED_TUPLE_HPP

#include <brigand/algorithms/wrap.hpp>
#include <tuple>

namespace brigand
{
  template <typename... T>
  using tuple_wrapper = typename std::tuple<T...>;

  template <typename L>
  using as_tuple = wrap<L, tuple_wrapper>;
}
#endif
