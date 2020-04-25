/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_TYPES_ARGS_HPP
#define BOOST_BRIGAND_TYPES_ARGS_HPP

#include <brigand/sequences/at.hpp>
#include <brigand/sequences/list.hpp>

namespace brigand
{
  // args metafunction class
  template<unsigned int Index> struct args
  {
  };

  // Predefined placeholders
  struct _1 {};
  struct _2 {};
  using _3 = args<2>;
  using _4 = args<3>;
  using _5 = args<4>;
  using _6 = args<5>;
  using _7 = args<6>;
  using _8 = args<7>;
  using _9 = args<8>;

  using _state = _1;
  using _element = _2;
}
#endif
