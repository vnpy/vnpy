/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_SELECT_HPP
#define BOOST_BRIGAND_ALGORITHMS_SELECT_HPP

#include <type_traits>
#include <utility>

namespace brigand
{
  template<typename C, typename T, typename F>
  inline typename std::enable_if<C::value,T&&>::type select(T&& t, F&&)
  {
    return std::forward<T>(t);
  }

  template<typename C, typename T, typename F>
  inline typename std::enable_if<!C::value,F&&>::type select(T&&, F&& f)
  {
    return std::forward<F>(f);
  }
}
#endif
