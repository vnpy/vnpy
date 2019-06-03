/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_REMOVE_HPP
#define BOOST_BRIGAND_ALGORITHMS_REMOVE_HPP

#include <brigand/algorithms/transform.hpp>
#include <brigand/algorithms/wrap.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/sequences/append.hpp>
#include <brigand/sequences/clear.hpp>
#include <type_traits>

namespace brigand
{
#if defined(BRIGAND_COMP_GCC) || defined(BRIGAND_COMP_CLANG) // not MSVC
namespace lazy
{
    template <typename L, typename Pred>
    struct remove_if;

    template <template <class...> class L, typename... Ts, typename Pred>
    struct remove_if<L<Ts...>, Pred>
        : ::brigand::detail::append_impl<
              L<>, typename std::conditional< ::brigand::apply<Pred, Ts>::value, list<>,
                                             list<Ts>>::type...>
    {
    };

    template <template <class...> class L, typename... Ts, template <typename...> class F>
    struct remove_if<L<Ts...>, bind<F, _1>>
        : ::brigand::detail::append_impl<
              L<>, typename std::conditional<F<Ts>::value, list<>, list<Ts>>::type...>
    {
    };

    template <template <class...> class L, typename... Ts, template <typename...> class F>
    struct remove_if<L<Ts...>, F<_1>>
        : ::brigand::detail::append_impl<
              L<>, typename std::conditional<F<Ts>::type::value, list<>, list<Ts>>::type...>
    {
    };
}

namespace lazy
{
    template <typename L, typename T>
    struct remove;

    template <template <class...> class L, typename... Ts, typename T>
    struct remove<L<Ts...>, T>
        : ::brigand::detail::append_impl<
              L<>, typename std::conditional<std::is_same<Ts, T>::value, list<>, list<Ts>>::type...>
    {
    };
}

namespace lazy
{

    template <typename L, typename Pred>
    struct filter;

    template <template <class...> class L, typename... Ts, typename Pred>
    struct filter<L<Ts...>, Pred>
        : ::brigand::detail::append_impl<
              L<>, typename std::conditional< ::brigand::apply<Pred, Ts>::value, list<Ts>,
                                             list<>>::type...>
    {
    };

    template <template <class...> class L, typename... Ts, template <typename...> class F>
    struct filter<L<Ts...>, bind<F, _1>>
        : ::brigand::detail::append_impl<
              L<>, typename std::conditional<F<Ts>::value, list<Ts>, list<>>::type...>
    {
    };

    template <template <class...> class L, typename... Ts, template <typename...> class F>
    struct filter<L<Ts...>, F<_1>>
        : ::brigand::detail::append_impl<
              L<>, typename std::conditional<F<Ts>::type::value, list<Ts>, list<>>::type...>
    {
    };
}
#else
namespace detail
{
    template <class Pred, class T>
    struct empty_helper : ::brigand::apply<Pred, T>
    {
    };

    // this is essentially just a work around because MSVC can't expand variadic packs properly
    template <typename Pred, typename T, bool B>
    struct empty_if_true : std::conditional<empty_helper<Pred, T>::value == B, list<>, list<T>>
    {
    };
    template <template <typename...> class F, typename T, bool B>
    struct empty_if_true<bind<F, _1>, T, B> : std::conditional<F<T>::value == B, list<>, list<T>>
    {
    };
    template <template <typename...> class F, typename T, bool B>
    struct empty_if_true<F<_1>, T, B> : std::conditional<F<T>::type::value == B, list<>, list<T>>
    {
    };
}

namespace lazy
{

    template <typename L, typename Pred>
    struct remove_if;

    template <template <class...> class L, typename... Ts, typename Pred>
    struct remove_if<L<Ts...>, Pred>
        : ::brigand::detail::append_impl<
              L<>, typename ::brigand::detail::empty_if_true<Pred, Ts, true>::type...>
    {
    };
}

namespace lazy
{
    template <typename L, typename T>
    struct remove;

    template <template <class...> class L, typename... Ts, typename T>
    struct remove<L<Ts...>, T>
        : ::brigand::detail::append_impl<
              L<>, typename std::conditional<std::is_same<Ts, T>::value, list<>, list<Ts>>::type...>
    {
    };
}

namespace lazy
{

    template <typename L, typename Pred>
    struct filter;

    template <template <class...> class L, typename... Ts, typename Pred>
    struct filter<L<Ts...>, Pred>
        : ::brigand::detail::append_impl<
              L<>, typename ::brigand::detail::empty_if_true<Pred, Ts, false>::type...>
    {
    };
}
#endif
template <typename L, typename Pred>
using remove_if = typename lazy::remove_if<L, Pred>::type;

template <typename L, typename T>
using remove = typename lazy::remove<L, T>::type;

template <typename L, typename Pred>
using filter = typename lazy::filter<L, Pred>::type;
}
#endif
