/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_TYPES_REAL_HPP
#define BOOST_BRIGAND_TYPES_REAL_HPP
#include <brigand/types/integral_constant.hpp>
#include <cstdint>
#include <cstring>

namespace brigand
{
  template<typename RealType, typename Type, Type Value>
  struct real_ : brigand::integral_constant<Type,Value>
  {
    using value_type  = RealType;
    using parent      = brigand::integral_constant<Type,Value>;

    // aliasing free implementation - reinterpret_cast is bad
    inline operator value_type() const
    {
      value_type that;
      std::memcpy(&that, &parent::value, sizeof(value_type));
      return that;
    }
  };

  template<std::uint32_t Value>
  struct single_ : real_<float, std::uint32_t, Value> {};

  template<std::uint64_t Value>
  struct double_ : real_<double, std::uint64_t,Value> {};
}
#endif
