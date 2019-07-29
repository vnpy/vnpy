/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_FUNCTIONS_LOGICAL_OR_HPP
#define BOOST_BRIGAND_FUNCTIONS_LOGICAL_OR_HPP
#include <brigand/types/bool.hpp>

namespace brigand
{
namespace detail
{
    template <unsigned N>
    struct or_impl;

    template <>
    struct or_impl<0>
    {
        template <typename T0=bool_<false>, typename T1 = bool_<false>, typename T2 = bool_<false>,
                  typename T3=bool_<false>, typename T4 = bool_<false>, typename T5 = bool_<false>,
                  typename T6=bool_<false>, typename T7 = bool_<false>, typename T8 = bool_<false>>
        using f = bool_<T0::value || T1::value || T2::value || T3::value || T4::value ||
                        T5::value || T6::value || T7::value || T8::value>;
    };

    template<>
    struct or_impl<1>
    {
        template <typename T0=bool_<false>, typename T1 = bool_<false>, typename T2 = bool_<false>,
                  typename T3=bool_<false>, typename T4 = bool_<false>, typename T5 = bool_<false>,
                  typename T6=bool_<false>, typename T7 = bool_<false>, typename T8 = bool_<false>,
                  typename T9=bool_<false>, typename T10 = bool_<false>, typename T11 = bool_<false>,
                  typename T12=bool_<false>, typename T13 = bool_<false>, typename T14 = bool_<false>,
                  typename T15=bool_<false>, typename T16 = bool_<false>, typename T17 = bool_<false>,
                  typename T18=bool_<false>, typename T19 = bool_<false>, typename... Ts>
        using f = bool_<T0::value || T1::value || T2::value || T3::value || T4::value ||
                        T5::value || T6::value || T7::value || T8::value || T9::value ||
                        T10::value || T11::value || T12::value || T13::value || T14::value ||
                        T15::value || T16::value || T17::value || T18::value || T19::value ||
                        or_impl<(sizeof...(Ts) / 9) != 0>::template f<Ts...>::value>;
    };
}

template<typename...Ts>
struct or_: detail::or_impl<(sizeof...(Ts) / 9) != 0>::template f<Ts...>
{};

}
#endif
