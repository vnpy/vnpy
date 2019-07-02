/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_MAKE_SEQUENCE_HPP
#define BOOST_BRIGAND_SEQUENCES_MAKE_SEQUENCE_HPP

#include <brigand/functions/arithmetic/next.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/sequences/append.hpp>
#include <brigand/sequences/list.hpp>

namespace brigand
{
namespace detail
{
    template<class Start, unsigned N, class Next, class... E>
    struct mksq8
    : mksq8<brigand::apply<Next, Start>, N-1, Next, E..., Start>
    {};

    template<class Start, class Next, class... E>
    struct mksq8<Start, 0, Next, E...>
    {
        using type = list<E...>;
    };

    template<class Start, class Next, class... E>
    struct mksq8<Start, 1, Next, E...>
    {
        using type = list<E..., Start>;
    };

    template<class Start, class Next>
    struct mksq8<Start, 8, Next>
    {
        using t1 = brigand::apply<Next, Start>;
        using t2 = brigand::apply<Next, t1>;
        using t3 = brigand::apply<Next, t2>;
        using t4 = brigand::apply<Next, t3>;
        using t5 = brigand::apply<Next, t4>;
        using t6 = brigand::apply<Next, t5>;
        using t7 = brigand::apply<Next, t6>;
        using type = list<Start, t1, t2, t3, t4, t5, t6, t7>;
    };

    template<template<class...> class List, class Start, unsigned N, class Next, bool, class... L>
    struct make_sequence_impl
    : make_sequence_impl<
        List,
        brigand::apply<Next, typename mksq8<Start, 8, Next>::t7>,
        N-8,
        Next,
        (N-8<=8),
        L...,
        typename mksq8<Start, 8, Next>::type
    >
    {};

    template<template<class...> class List, class Start, unsigned N, class Next, class... L>
    struct make_sequence_impl<List, Start, N, Next, true, L...>
    {
        using type = append<List<>, L..., typename mksq8<Start, N, Next>::type>;
    };
}

    template<class Start, unsigned N, class Next = next<_1>, template<class...> class List = list>
    using make_sequence = typename detail::make_sequence_impl<List, Start, N, Next, (N<=8)>::type;
}
#endif
