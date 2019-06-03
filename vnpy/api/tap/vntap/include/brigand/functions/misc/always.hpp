/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_FUNCTIONS_MISC_ALWAYS_HPP
#define BOOST_BRIGAND_FUNCTIONS_MISC_ALWAYS_HPP

namespace brigand
{
  template<class T>
  struct always
  {
     using type = T; 
  };
}
#endif
