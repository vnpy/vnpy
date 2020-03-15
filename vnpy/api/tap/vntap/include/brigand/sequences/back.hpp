/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_BACK_HPP
#define BOOST_BRIGAND_SEQUENCES_BACK_HPP

#include <brigand/algorithms/split_at.hpp>
#include <brigand/sequences/at.hpp>
#include <brigand/sequences/front.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/sequences/size.hpp>
#include <brigand/types/integral_constant.hpp>

namespace brigand
{
// push_back
namespace detail
{
    template <class L, class... T>
    struct push_back_impl;

    template <template <class...> class L, class... U, class... T>
    struct push_back_impl<L<U...>, T...>
    {
        using type = L<U..., T...>;
    };
}

template <class L, class... T>
using push_back = typename detail::push_back_impl<L, T...>::type;

template <class L>
using back = at_c<L, size<L>::value - 1>;

template <class L, class N = brigand::integral_constant<unsigned int, 1>>
using pop_back =
    front<split_at<L, brigand::integral_constant<unsigned int, size<L>::value - N::value>>>;
}
#endif
