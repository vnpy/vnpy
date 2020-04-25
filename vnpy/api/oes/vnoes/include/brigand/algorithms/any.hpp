/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_ANY_HPP
#define BOOST_BRIGAND_ALGORITHMS_ANY_HPP

#include <brigand/types/bool.hpp>
#include <brigand/algorithms/detail/non_null.hpp>
#include <brigand/algorithms/none.hpp>

namespace brigand
{
  namespace detail
  {
    template< typename Sequence, typename Predicate >
    struct any_impl : bool_<!none<Sequence,Predicate>::value> {};
  }

  // Is a predicate true for at least one type ?
  template<typename Sequence, typename Predicate = detail::non_null>
  using any = typename detail::any_impl<Sequence,Predicate>::type;
}
#endif
