/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_WRAP_HPP
#define BOOST_BRIGAND_ALGORITHMS_WRAP_HPP

namespace brigand
{
  namespace lazy
  {
    template <class A, template<class...> class B> struct wrap;

    template<template<class...> class A, class... T, template<class...> class B>
    struct wrap<A<T...>, B>
    {
      using type = B<T...>;
    };
  }

  template<class A, template<class...> class B>
  using wrap = typename lazy::wrap<A, B>::type;
}
#endif
