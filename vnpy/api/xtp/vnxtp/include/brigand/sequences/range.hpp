/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_RANGE_HPP
#define BOOST_BRIGAND_SEQUENCES_RANGE_HPP

#include <brigand/config.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/types/integral_constant.hpp>

namespace brigand
{
namespace detail
{
    template <class T, class, class, T>
    struct range_cat;

#ifdef BRIGAND_COMP_MSVC
    template <class T, T Start, T Int>
    struct int_plus
    {
        using type = brigand::integral_constant<T, Start + Int>;
    };
#endif

    template <class T, class... Ts, T... Ints, T Start>
    struct range_cat<T, list<Ts...>, list<brigand::integral_constant<T, Ints>...>, Start>
    {
#ifdef BRIGAND_COMP_MSVC
        using type = list<Ts..., typename int_plus<T, Start, Ints>::type...>;
#else
        using type = list<Ts..., brigand::integral_constant<T, Start + Ints>...>;
#endif
    };

    template <class T, T Start, unsigned int N>
    struct range_impl : range_cat<T, typename range_impl<T, Start, N / 2>::type,
                                  typename range_impl<T, Start, N - N / 2>::type, N / 2>
    {
    };

    template <class T, T Start>
    struct range_impl<T, Start, 1>
    {
        using type = list<brigand::integral_constant<T, Start>>;
    };

    template <class T, T Start>
    struct range_impl<T, Start, 0>
    {
        using type = list<>;
    };

    template <class T, class, class, T>
    struct reverse_range_cat;

#ifdef BRIGAND_COMP_MSVC
    template <class T, T Start, T Int>
    struct int_minus
    {
        using type = brigand::integral_constant<T, Int - Start>;
    };
#endif

    template <class T, class... Ts, T... Ints, T Start>
    struct reverse_range_cat<T, list<Ts...>, list<brigand::integral_constant<T, Ints>...>, Start>
    {
#ifdef BRIGAND_COMP_MSVC
        using type = list<Ts..., typename int_minus<T, Start, Ints>::type...>;
#else
        using type = list<Ts..., brigand::integral_constant<T, Ints - Start>...>;
#endif
    };

    template <class T, T Start, unsigned int N>
    struct reverse_range_impl
        : reverse_range_cat<T, typename reverse_range_impl<T, Start, N / 2>::type,
                            typename reverse_range_impl<T, Start, N - N / 2>::type, N / 2>
    {
    };

    template <class T, T Start>
    struct reverse_range_impl<T, Start, 1>
    {
        using type = list<brigand::integral_constant<T, Start>>;
    };

    template <class T, T Start>
    struct reverse_range_impl<T, Start, 0>
    {
        using type = list<>;
    };

    template <class T, T Start, T Stop>
    struct reverse_range_safe
    {
        static_assert(
            Start >= Stop,
            "Invalid parameters. reverse_range<> syntax is reverse_range<type, from, down_to>");
        using type = typename reverse_range_impl<T, Start, Start - Stop>::type;
    };
}

template <class T, T Start, T Stop>
using range = typename detail::range_impl<T, Start, Stop - Start>::type;

template <class T, T Start, T Stop>
using reverse_range = typename detail::reverse_range_safe<T, Start, Stop>::type;
}
#endif
