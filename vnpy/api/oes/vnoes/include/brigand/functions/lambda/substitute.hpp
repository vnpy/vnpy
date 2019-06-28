/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_FUNCTIONS_LAMBDA_SUBSTITUTE_HPP
#define BOOST_BRIGAND_FUNCTIONS_LAMBDA_SUBSTITUTE_HPP

#include <brigand/sequences/at.hpp>

namespace brigand
{
  template<unsigned int Index> struct args;

  namespace detail
  {
    template<typename T, typename List>
    struct substitute_impl
    {
      using type = T;
    };

    template<template<class...> class T, typename... Ts, typename List>
    struct substitute_impl<T<Ts...>,List>
    {
      using type = T<typename substitute_impl<Ts,List>::type...>;
    };

    template<unsigned int Index, typename List>
    struct substitute_impl<args<Index>,List>
    {
      using type = brigand::at_c<List,Index>;
    };
  }

  template<typename T, typename List>
  using substitute = typename detail::substitute_impl<T,List>::type;
}
#endif
