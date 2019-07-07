/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_TYPES_INHERIT_HPP
#define BOOST_BRIGAND_TYPES_INHERIT_HPP

#include <brigand/types/empty_base.hpp>

namespace brigand
{
  template<typename... Ts> struct inherit;

  template<typename T> struct inherit<T>
  {
    struct type : public T {};
  };

  template<> struct inherit<>
  {
    using type = empty_base;
  };

  template<> struct inherit<empty_base>
  {
    using type = empty_base;
  };

  template<typename T1, typename T2> struct inherit<T1,T2>
  {
    struct type : public T1, T2 {};
  };

  template<typename T1> struct inherit<T1,empty_base>
  {
    using type = T1;
  };

  template<typename T2> struct inherit<empty_base,T2>
  {
    using type = T2;
  };

  template<> struct inherit<empty_base,empty_base>
  {
    using type = empty_base;
  };

  template<typename T1, typename T2, typename T3, typename... Ts>
  struct  inherit<T1, T2, T3, Ts...>
        : inherit<T1, typename inherit<T2,typename inherit<T3, Ts...>::type>::type>
  {};
}
#endif
