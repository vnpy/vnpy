/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_IS_SET_HPP
#define BOOST_BRIGAND_ALGORITHMS_IS_SET_HPP

#include <brigand/sequences/range.hpp>
#include <brigand/types/bool.hpp>
#include <brigand/types/type.hpp>

namespace brigand
{

#ifdef BRIGAND_COMP_MSVC

namespace detail
{
    template <class, class T>
    struct unique_x_t
    {
        operator T();
    };

    template <class Ints, class... Ts>
    struct is_set_impl;

    template <>
    struct is_set_impl<list<>>
    {
        using type = brigand::true_type;
    };

    inline brigand::true_type true_fn(...);

    template <class... Ints, class... Ts>
    struct is_set_impl<list<Ints...>, Ts...>
    {
        struct Pack : unique_x_t<Ints, Ts>...
        {
        };

        template <class... Us>
        static auto is_set(Us...) -> decltype(true_fn(static_cast<Us>(Pack())...));
        static brigand::false_type is_set(...);

        using type = decltype(is_set(Ts()...));
    };

    template <class>
    struct qrref
    {
    };
    template <class>
    struct qref
    {
    };
    template <class>
    struct qnoref
    {
    };

    template <class T>
    struct msvc_quali_ref
    {
        using type = qnoref<T>;
    };

    template <class T>
    struct msvc_quali_ref<T &>
    {
        using type = qref<T>;
    };

    template <class T>
    struct msvc_quali_ref<T &&>
    {
        using type = qrref<T>;
    };
}

template <class... Ts>
using is_set = typename detail::is_set_impl<range<unsigned int, 0, sizeof...(Ts)>,
                                            detail::msvc_quali_ref<Ts>...>::type;

#else

namespace detail
{
    template <class, class T>
    struct unique_x_t : type_<T>
    {
    };

    template <class Ints, class... Ts>
    struct is_set_cont;

    template <class... Ints, class... Ts>
    struct is_set_cont<list<Ints...>, Ts...> : unique_x_t<Ints, Ts>...
    {
    };
}

template <class... Ts>
using is_set = bool_<sizeof(detail::is_set_cont<range<unsigned int, 0, sizeof...(Ts)>, Ts...>) == 1>;

#endif
}
#endif
