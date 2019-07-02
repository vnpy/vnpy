/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_REVERSE_HPP
#define BOOST_BRIGAND_ALGORITHMS_REVERSE_HPP

#include <brigand/sequences/append.hpp>

namespace brigand
{
namespace detail
{

    template <template<class...> class L, class...>
    struct reverse_elements;

    template <template <class...> class L>
    struct reverse_elements<L>
    {
        using type = L<>;
    };

    template <template <class...> class L, class T0, class... Ts>
    struct reverse_elements<L, T0, Ts...>
    : append_impl<typename reverse_elements<L, Ts...>::type, L<T0>>
    {
    };

    template <template <class...> class L, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15, class... Ts>
    struct reverse_elements<L, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, Ts...>
    : append_impl<typename reverse_elements<L, Ts...>::type, L<T15, T14, T13, T12, T11, T10, T9, T8, T7, T6, T5, T4, T3, T2, T1, T0>>
    {
    };

    template<class L>
    struct reverse_impl;

    template<template<class...> class L, class... U>
    struct reverse_impl<L<U...>>
    : reverse_elements<L, U...>
    {
    };

}

namespace lazy
{

    template <typename L>
    using reverse = typename detail::reverse_impl<L>;

}

    template <typename L>
    using reverse = typename detail::reverse_impl<L>::type;

}
#endif
