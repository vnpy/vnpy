/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_SET_HPP
#define BOOST_BRIGAND_SEQUENCES_SET_HPP

#include <brigand/types/type.hpp>

#include <brigand/sequences/append.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/sequences/erase.hpp>
#include <brigand/sequences/insert.hpp>
#include <brigand/sequences/contains.hpp>

namespace brigand
{
namespace detail
{

    template<class... Ts>
    struct make_set;

    // Visual Studio helper
    template<class U, class K>
    struct set_erase_pred_impl
    {
        using type = list<U>;
    };

    template<class K>
    struct set_erase_pred_impl<K,K>
    {
        using type = list<>;
    };

    template <class... T>
    struct set_impl
    {
        template <typename K, typename = decltype(static_cast<type_<K>*>(static_cast<make_set<T...>*>(nullptr)))>
        static brigand::true_type contains(type_<K>);

        template <typename K>
        static brigand::false_type contains(K);

        template <typename K, typename = decltype(static_cast<type_<K>*>(static_cast<make_set<T...>*>(nullptr)))>
        static brigand::true_type has_key(type_<K>);

        template <typename K>
        static brigand::false_type has_key(K);

        template <class K>
        static append<set_impl<>, typename set_erase_pred_impl<T, K>::type...> erase(type_<K>);

        template<class K, class = decltype(static_cast<type_<K>*>(static_cast<make_set<T...>*>(nullptr)))>
        static set_impl insert(type_<K>);

        template<class K>
        static set_impl<T..., typename K::type> insert(K);
    };

    // if you have a "class already a base" error message, it means you have defined a set with the same key present more
    // than once, which is an error
    template<class... Ts>
    struct make_set : type_<Ts>...
    {
      using type = set_impl<Ts...>;
    };

}

    template <typename... T>
    using set_wrapper = typename detail::make_set<T...>::type;

    template <typename L>
    using as_set = wrap<L, set_wrapper>;

    template<class... Ts>
    using set = typename detail::make_set<Ts...>::type;

}
#endif
