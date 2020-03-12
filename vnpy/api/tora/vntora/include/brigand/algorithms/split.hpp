/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_SPLIT_HPP
#define BOOST_BRIGAND_ALGORITHMS_SPLIT_HPP

#include <brigand/config.hpp>
#include <brigand/sequences/list.hpp>

namespace brigand
{
namespace detail
{
    template<typename TOut, typename TCurrent, typename TDelim, typename... Ts>
    struct split_impl;
    template<template<typename...> class L, typename... Os, typename... Cs, typename TDelim, typename T, typename... Ts>
    struct split_impl<L<Os...>, L<Cs...>, TDelim, T, Ts...> : //next is not delim, we still have more
        split_impl<L<Os...>, L<Cs..., T>, TDelim, Ts...> {};
    template<template<typename...> class L, typename... Os, typename... Cs, typename TDelim, typename T>
    struct split_impl<L<Os...>, L<Cs...>, TDelim, T> {  //next is not delim, we do not have more
        using type = L<Os..., L<Cs..., T>>;
    };
    template<template<typename...> class L, typename... Os, typename... Cs, typename TDelim, typename... Ts>
    struct split_impl<L<Os...>, L<Cs...>, TDelim, TDelim, Ts...> : //next is delim, we still have more
        split_impl<L<Os..., L<Cs...>>, L<>, TDelim, Ts...> {};
    template<template<typename...> class L, typename... Os, typename... Cs, typename TDelim>
    struct split_impl<L<Os...>, L<Cs...>, TDelim, TDelim> { //next is delim, we have no more
        using type = L<Os..., L<Cs...>>;
    };
    //same cases but with empty TCurrent list
    template<template<typename...> class L, typename... Os, typename TDelim, typename... Ts>
    struct split_impl<L<Os...>, L<>, TDelim, TDelim, Ts...> : //next is delim, we still have more
        split_impl<L<Os...>, L<>, TDelim, Ts...> {};
    template<template<typename...> class L, typename... Os, typename TDelim>
    struct split_impl<L<Os...>, L<>, TDelim, TDelim> { //next is delim, we have no more
        using type = L<Os...>;
    };
    template<template<typename...> class L, typename... Os, typename TDelim>
    struct split_impl<L<Os...>, L<>, TDelim> { //done
        using type = L<Os...>;
    };



    template<typename TList, typename TDelim>
    struct split_helper;
    template<template<typename...> class L, typename T, typename... Ts, typename TDelim>
    struct split_helper<L<T,Ts...>, TDelim> : split_impl<L<>, L<>, TDelim, T, Ts...>{};
#if defined(BRIGAND_COMP_INTEL)
    template<template<typename...> class L, typename TDelim>
    struct split_helper<L<>, TDelim> { //done
        using type = L<>;
    };
#else
    template<template<typename...> class L, typename... T, typename TDelim>
    struct split_helper<L<T...>, TDelim> { //done
        using type = L<>;
    };
#endif

}

namespace lazy
{
    template<typename TList, typename TDelim>
    using split = detail::split_helper<TList, TDelim>;
}

template<typename TList, typename TDelim>
using split = typename lazy::split<TList, TDelim>::type;

}
#endif
