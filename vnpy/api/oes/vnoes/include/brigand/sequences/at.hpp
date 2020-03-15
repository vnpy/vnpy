/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_AT_HPP
#define BOOST_BRIGAND_SEQUENCES_AT_HPP
#include <brigand/sequences/filled_list.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/sequences/map.hpp>
#include <brigand/types/type.hpp>

namespace brigand
{
namespace detail
{
    template <class T>
    struct element_at;

    template <class... Ts>
    struct element_at<list<Ts...>>
    {
        template <class T>
        type_<T> static at(Ts..., type_<T> *, ...);
    };

    template <unsigned int N, typename Seq>
    struct at_impl;

    template <unsigned int N, template <typename...> class L, class... Ts>
    struct at_impl<N, L<Ts...>> : decltype(element_at<brigand::filled_list<void const *, N>>::at(
                                      static_cast<type_<Ts> *>(nullptr)...))
    {
    };
}

template <class L, unsigned int Index>
using at_c = typename detail::at_impl<Index, L>::type;

namespace detail
{
    template <typename T>
    struct has_at_method
    {
        struct dummy
        {
        };
        template <typename C, typename P>
        static auto test(P * p) -> decltype(C::at(*p), brigand::true_type());

        template <typename, typename>
        static brigand::false_type test(...);

        static const bool value =
            std::is_same<brigand::true_type, decltype(test<T, dummy>(nullptr))>::value;
    };

    template <class L, typename Index, bool>
    struct at_dispatch
    {
        using type = at_c<L, Index::value>;
    };

    template <class L, typename Index>
    struct at_dispatch<L, Index, true>
    {
        using type = lookup<L, Index>;
    };
}

template <class Seq, typename K>
using at = typename detail::at_dispatch<Seq, K, detail::has_at_method<Seq>::value>::type;
}
#endif
