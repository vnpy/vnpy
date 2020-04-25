/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ADAPTED_VARIANT_HPP
#define BOOST_BRIGAND_ADAPTED_VARIANT_HPP

#include <brigand/algorithms/wrap.hpp>
#include <boost/variant.hpp>

namespace brigand
{
  template <typename... T>
  using variant_wrapper = typename boost::variant<T...>;

  template <typename L>
  using as_variant = wrap<L, variant_wrapper>;
}
#endif
