/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_MAP_HPP
#define BOOST_BRIGAND_SEQUENCES_MAP_HPP
#include <brigand/sequences/append.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/sequences/pair.hpp>
#include <brigand/types/no_such_type.hpp>
#include <brigand/types/type.hpp>
#include <type_traits>

namespace brigand
{

namespace lazy
{
    template <typename M, typename K>
    struct lookup_at
    {
        using target_t = type_<K>;
        using type = decltype(M::at(target_t{}));
    };

    template <typename M, typename K>
    struct lookup : lookup_at<M, K>::type
    {
    };
}

template <typename M, typename K>
using lookup = typename lazy::lookup<M, K>::type;

namespace detail
{
    template <class... T>
    struct map_impl;

    template <>
    struct map_impl<>
    {
        template <typename U>
        static type_<no_such_type_> at(U);

        template <class K>
        static brigand::false_type has_key(type_<K>);

        template <class K>
        static map_impl erase(type_<K>);

        template <class P>
        static map_impl<P> insert(type_<P>);
    };

    template <class... Ts>
    struct map_impl
    {
    private:
        struct Pack : pair<typename Ts::first_type, Ts>...
        {
        };

        template <class K, class P>
        static type_<typename P::second_type> at_impl(pair<K, P> *);

    public:
        template <class K>
        static decltype(at_impl<K>(static_cast<Pack *>(nullptr))) at(type_<K>);

        template <class K>
        static type_<no_such_type_> at(K);

        template <class K, class = decltype(at_impl<K>(static_cast<Pack *>(nullptr)))>
        static brigand::true_type has_key(type_<K>);

        template <class K>
        static brigand::false_type has_key(K);

        template <class K, class X>
        using erase_t = typename std::conditional<std::is_same<K, typename X::first_type>::value,
                                                  list<>, list<X>>::type;

        template <class K, typename... Xs>
        struct erase_return_t
        {
            using type = append<map_impl<>, erase_t<K, Xs>...>;
        };

        template <class K>
        static typename erase_return_t<K, Ts...>::type erase(type_<K>);

        template <class P, class = decltype(static_cast<pair<typename P::first_type, P> *>(
                               static_cast<Pack *>(nullptr)))>
        static map_impl insert(type_<P>);

        template <class P>
        static map_impl<Ts..., typename P::type> insert(P);
    };

    // if you have a "class already a base" error message, it means you have defined a map with the
    // same key present more
    // than once, which is an error
    template <class... Ts>
    struct make_map : type_<typename Ts::first_type>...
    {
        using type = map_impl<Ts...>;
    };
}
template <class... Ts>
using map = typename detail::make_map<Ts...>::type;
}
#endif
