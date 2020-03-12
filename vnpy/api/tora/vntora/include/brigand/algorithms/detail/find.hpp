/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_DETAIL_FIND_HPP
#define BOOST_BRIGAND_ALGORITHMS_DETAIL_FIND_HPP

#include <brigand/functions/lambda/apply.hpp>
#include <brigand/types/bool.hpp>

namespace brigand
{
namespace detail
{

    template <template <typename...> class S, template <typename...> class F, typename... Ts>
    struct finder
    {
        template <typename T>
        using P = F<Ts..., T>;

        template <bool InNext8, bool Match, typename... Ls>
        struct find
        {
            using type = S<>; // not found case because none left
        };

        template <typename L>
        struct find<true, false, L>
        {
            using type = S<>; // not found case because only one left and not true
        };

        template <typename L, typename... Ls> // match case
        struct find<true, true, L, Ls...>
        {
            using type = S<L, Ls...>;
        };

        template <typename L1, typename L2, typename... Ls> // not match case
        struct find<true, false, L1, L2, Ls...> : find<true, F<Ts..., L2>::value, L2, Ls...>
        {
        };

        template <typename L0, typename L1, typename L2, typename L3, typename L4, typename L5,
                  typename L6, typename L7, typename L8,
                  typename... Ls> // not match no longer fast track case
        struct find<false, false, L0, L1, L2, L3, L4, L5, L6, L7, L8, Ls...>
            : find<true, F<Ts..., L8>::value, L8, Ls...>
        {
        };

        template <typename L1, typename L2, typename L3, typename L4, typename L5, typename L6,
                  typename L7, typename L8, typename L9, typename L10, typename L11, typename L12,
                  typename L13, typename L14, typename L15, typename L16,
                  typename... Ls> // not match can fast track again case
        struct find<false, false, L1, L2, L3, L4, L5, L6, L7, L8, L9, L10, L11, L12, L13, L14, L15,
                    L16, Ls...>
            : find<(P<L9>::value || P<L10>::value || P<L11>::value || P<L12>::value ||
                    P<L13>::value || P<L14>::value || P<L15>::value || P<L16>::value),
                   P<L9>::value, L9, L10, L11, L12, L13, L14, L15, L16, Ls...>
        {
        };
    };
}
}
#endif
