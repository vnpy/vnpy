/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ADAPTED_PAIR_HPP
#define BOOST_BRIGAND_ADAPTED_PAIR_HPP

#include <brigand/algorithms/wrap.hpp>
#include <brigand/types/no_such_type.hpp>
#include <utility>

namespace brigand
{
  template <typename... T>
  struct pair_wrapper_
  {
    static_assert (sizeof...(T) == 2
                  , "as_pair requires a type list of exactly two types"
                  );

    // type need to be defined or the error becomes a hard, non-static assert error
    using type = no_such_type_;
  };

  template <typename T, typename U>
  struct pair_wrapper_<T,U>
  {
      using type = std::pair<T,U>;
  };

  template <typename... T>
  using pair_wrapper = typename pair_wrapper_<T...>::type;

  template <typename L>
  using as_pair = wrap<L, pair_wrapper>;
}
#endif
