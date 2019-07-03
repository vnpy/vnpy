/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_TYPES_VOIDP_HPP
#define BOOST_BRIGAND_TYPES_VOIDP_HPP

namespace brigand
{
  template<typename T> struct voidp { using type = void const *; };
}
#endif
