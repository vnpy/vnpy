/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_SPLIT_AT_HPP
#define BOOST_BRIGAND_ALGORITHMS_SPLIT_AT_HPP

#include <brigand/config.hpp>
#include <brigand/sequences/clear.hpp>

namespace brigand
{
namespace detail
{
    template <bool b, typename O, typename L, unsigned int I>
    struct split_at_impl; // if you get an error here your index is out of bounds

#if defined(BRIGAND_COMP_INTEL)
    template <template <typename...> class S, typename... Os>
    struct split_at_impl<false, S<Os...>, S<>, 0>
    {
        using type = S<S<Os...>, S<>>;
    };
#else
    template <template <typename...> class S, typename... Os, typename... Ts>
    struct split_at_impl<false, S<Os...>, S<Ts...>, 0>
    {
        using type = S<S<Os...>, S<Ts...>>;
    };
#endif

    template <template <typename...> class S, typename... Os, typename T, typename... Ts>
    struct split_at_impl<false, S<Os...>, S<T, Ts...>, 0>
    {
        using type = S<S<Os...>, S<T, Ts...>>;
    };
    template <template <typename...> class S, typename... Os, typename T, typename... Ts,
              unsigned int I>
    struct split_at_impl<false, S<Os...>, S<T, Ts...>, I>
        : split_at_impl<false, S<Os..., T>, S<Ts...>, (I - 1)>
    {
    };
    template <template <typename...> class S, typename... Os, typename T1, typename T2, typename T3,
              typename T4, typename T5, typename T6, typename T7, typename T8, typename T9,
              typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
              typename T16, typename... Ts, unsigned int I>
    struct split_at_impl<
        true, S<Os...>,
        S<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, Ts...>, I>
        : split_at_impl<((I - 16) > 16), S<Os..., T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
                                           T13, T14, T15, T16>,
                        S<Ts...>, (I - 16)>
    {
    };

    template <typename L, typename I>
    struct call_split_at_impl : split_at_impl<(I::value > 16), brigand::clear<L>, L, I::value>
    {
    };
}
namespace lazy
{
    template <typename L, typename I>
    using split_at = ::brigand::detail::call_split_at_impl<L, I>;
}
template <typename L, typename I>
using split_at = typename ::brigand::lazy::split_at<L, I>::type;
}
#endif
