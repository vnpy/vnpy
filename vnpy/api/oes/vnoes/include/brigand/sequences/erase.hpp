/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_ERASE_HPP
#define BOOST_BRIGAND_SEQUENCES_ERASE_HPP
#include <brigand/algorithms/split_at.hpp>

#include <brigand/sequences/append.hpp>
#include <brigand/sequences/back.hpp>
#include <brigand/sequences/front.hpp>

#include <brigand/types/integer.hpp>
#include <brigand/types/type.hpp>

namespace brigand
{

template <class L, unsigned int Index>
using erase_c =
    append<front<split_at<L, brigand::integral_constant<unsigned int, Index>>>,
           pop_front<back<split_at<L, brigand::integral_constant<unsigned int, Index>>>>>;

namespace detail
{
    template <typename T>
    struct has_erase_method
    {
        struct dummy
        {
        };

        template <typename C, typename P>
        static auto test(P * p) -> decltype(C::erase(type_<P>{}), brigand::true_type());

        template <typename, typename>
        static brigand::false_type test(...);

        static const bool value =
            std::is_same<brigand::true_type, decltype(test<T, dummy>(nullptr))>::value;
    };

    template <class L, class I, bool>
    struct erase_dispatch
    {
        using type = erase_c<L, I::value>;
    };

    template <class C, class K>
    struct erase_dispatch<C, K, true>
    {
        using type = decltype(C::erase(type_<K>{}));
    };
}

template <class L, class K>
using erase = typename detail::erase_dispatch<L, K, detail::has_erase_method<L>::value>::type;
}
#endif
