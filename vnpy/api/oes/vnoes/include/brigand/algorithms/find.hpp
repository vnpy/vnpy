/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_FIND_HPP
#define BOOST_BRIGAND_ALGORITHMS_FIND_HPP

#include <brigand/algorithms/detail/find.hpp>
#include <brigand/algorithms/detail/non_null.hpp>
#include <brigand/algorithms/reverse.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/sequences/size.hpp>
#include <brigand/types/bool.hpp>

namespace brigand
{

namespace lazy
{

    // find uses Predicate, it's very effective
    template <typename Sequence, typename Predicate = ::brigand::detail::non_null>
    struct find;
    template <template <typename...> class Sequence, typename... Ls, typename Pred>
    struct find<Sequence<Ls...>, Pred>
        : detail::finder<Sequence, detail::bound_apply, Pred>::template find<
              false, false, void, void, void, void, void, void, void, void, Ls...>
    {
    };
    template <template <typename...> class Sequence, typename... Ls, template <typename...> class F>
    struct find<Sequence<Ls...>, bind<F, _1>>
        : detail::finder<Sequence, F>::template find<false, false, void, void, void, void, void,
                                                     void, void, void, Ls...>
    {
    };
}

// find uses Predicate, it's very effective
template <typename Sequence, typename Predicate = brigand::detail::non_null>
using find = typename lazy::find<Sequence, Predicate>::type;

namespace lazy
{

    // reverse_find uses reverse and find :o
    template <typename Sequence, typename Predicate = detail::non_null>
    using reverse_find =
        ::brigand::lazy::reverse< ::brigand::find<brigand::reverse<Sequence>, Predicate>>;
}

template <typename Sequence, typename Predicate = detail::non_null>
using reverse_find = typename ::brigand::lazy::reverse_find<Sequence, Predicate>::type;

namespace detail
{
    template <typename Sequence, typename Predicate>
    using find_size = size<brigand::find<Sequence, Predicate>>;

    template <typename Sequence, typename Predicate>
    using empty_find = bool_<find_size<Sequence, Predicate>::value == 0>;

    template <typename Sequence, typename Predicate>
    using non_empty_find = bool_<find_size<Sequence, Predicate>::value != 0>;
}

// Utility meta-function to check if nothing was found
template <typename Sequence, typename Predicate = detail::non_null>
using not_found = typename detail::empty_find<Sequence, Predicate>;

// Utility meta-function to check if something was found
template <typename Sequence, typename Predicate = detail::non_null>
using found = typename detail::non_empty_find<Sequence, Predicate>;
}
#endif
