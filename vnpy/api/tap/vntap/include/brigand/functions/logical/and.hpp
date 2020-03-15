/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_FUNCTIONS_LOGICAL_AND_HPP
#define BOOST_BRIGAND_FUNCTIONS_LOGICAL_AND_HPP
#include <brigand/types/bool.hpp>

namespace brigand
{
namespace detail
{
    template <unsigned N>
    struct and_impl;

    template <>
    struct and_impl<0>
    {
        template <typename T0=bool_<true>, typename T1 = bool_<true>, typename T2 = bool_<true>,
                  typename T3=bool_<true>, typename T4 = bool_<true>, typename T5 = bool_<true>,
                  typename T6=bool_<true>, typename T7 = bool_<true>, typename T8 = bool_<true>>
        using f = bool_<T0::value && T1::value && T2::value && T3::value && T4::value &&
                        T5::value && T6::value && T7::value && T8::value>;
    };

    template<>
    struct and_impl<1>
    {
        template <typename T0=bool_<true>, typename T1 = bool_<true>, typename T2 = bool_<true>,
                  typename T3=bool_<true>, typename T4 = bool_<true>, typename T5 = bool_<true>,
                  typename T6=bool_<true>, typename T7 = bool_<true>, typename T8 = bool_<true>,
                  typename T9=bool_<true>, typename T10 = bool_<true>, typename T11 = bool_<true>,
                  typename T12=bool_<true>, typename T13 = bool_<true>, typename T14 = bool_<true>,
                  typename T15=bool_<true>, typename T16 = bool_<true>, typename T17 = bool_<true>,
                  typename T18=bool_<true>, typename T19 = bool_<true>, typename... Ts>
        using f = bool_<T0::value && T1::value && T2::value && T3::value && T4::value &&
                        T5::value && T6::value && T7::value && T8::value && T9::value &&
                        T10::value && T11::value && T12::value && T13::value && T14::value &&
                        T15::value && T16::value && T17::value && T18::value && T19::value &&
                        and_impl<(sizeof...(Ts) / 9) != 0>::template f<Ts...>::value>;
    };
}

template<typename...Ts>
struct and_: detail::and_impl<(sizeof...(Ts) / 9) != 0>::template f<Ts...>
{};

}
#endif
