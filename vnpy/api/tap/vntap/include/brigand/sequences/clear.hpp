/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_CLEAR_HPP
#define BOOST_BRIGAND_SEQUENCES_CLEAR_HPP

namespace brigand
{
namespace detail
{
  template<class L>
  struct clear_impl;

  template<template<class...> class L, class... Ts>
  struct clear_impl<L<Ts...>>
  {
    using type = L<>;
  };
}

  template<class L>
  using clear = typename detail::clear_impl<L>::type;
}
#endif
