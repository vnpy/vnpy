/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_FILLED_LIST_HPP
#define BOOST_BRIGAND_SEQUENCES_FILLED_LIST_HPP

#include <brigand/sequences/list.hpp>

namespace brigand
{
namespace detail
{
    template <class, class>
    struct dup_append_list;

    template <template <class...> class List, class... Ts, class... Us>
    struct dup_append_list<List<Ts...>, List<Us...>>
    {
        using type = List<Ts..., Ts..., Us...>;
    };

    template <class T, template <class...> class List, unsigned int N>
    struct filled_list_impl
        : dup_append_list<typename filled_list_impl<T, List, N / 2>::type,
                          typename filled_list_impl<T, List, N - N / 2 * 2>::type>
    {
    };

    template <class T, template <class...> class List>
    struct filled_list_impl<T, List, 1>
    {
        using type = List<T>;
    };

    template <class T, template <class...> class List>
    struct filled_list_impl<T, List, 0>
    {
        using type = List<>;
    };
}

template <class T, unsigned int N, template <class...> class List = list>
using filled_list = typename detail::filled_list_impl<T, List, N>::type;
}
#endif
