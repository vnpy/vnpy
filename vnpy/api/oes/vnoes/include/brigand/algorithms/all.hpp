/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_ALL_HPP
#define BOOST_BRIGAND_ALGORITHMS_ALL_HPP

#include <brigand/algorithms/detail/non_null.hpp>
#include <brigand/config.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <initializer_list>
#include <type_traits>

namespace brigand
{
#if defined(BRIGAND_COMP_MSVC_2013) || defined(BRIGAND_COMP_CUDA) || defined(BRIGAND_COMP_INTEL)
namespace detail
{
    template <class P, class T>
    struct all_helper : ::brigand::apply<P, T>
    {
    };

    template <bool...>
    struct bools_
    {
    };
    template <typename Sequence, typename Predicate, typename... Ts>
    struct all_impl;

    template <template <class...> class Sequence, typename Predicate, typename... Ts>
    struct all_impl<Sequence<Ts...>, Predicate>
        : std::is_same<bools_<true, all_helper<Predicate, Ts>::value...>,
                       bools_<all_helper<Predicate, Ts>::value..., true>>
    {
    };
}
#else
namespace detail
{
    struct all_same
    {
        const bool value = false;
        constexpr all_same(...) {}
        template <typename T>
        constexpr all_same(std::initializer_list<T *>) : value{true}
        {
        }
    };

    template <typename Sequence, typename Predicate>
    struct all_impl : bool_<true>
    {
    };

    template <template <class...> class Sequence, typename Predicate, typename T, typename... Ts>
    struct all_impl<Sequence<T, Ts...>, Predicate>
    {
        static constexpr all_same tester{
            static_cast< ::brigand::apply<Predicate, T> *>(nullptr),
            static_cast< ::brigand::apply<Predicate, Ts> *>(nullptr)...};
        using type = bool_<(::brigand::apply<Predicate, T>::value != 0 && tester.value)>;
    };

    template <template <class...> class Sequence, template <typename...> class F, typename T,
              typename... Ts>
    struct all_impl<Sequence<T, Ts...>, bind<F, _1>>
    {
        static constexpr all_same tester{static_cast<F<T> *>(nullptr),
                                         static_cast<F<Ts> *>(nullptr)...};
        using type = bool_<(F<T>::value != 0 && tester.value)>;
    };

    template <template <class...> class Sequence, template <typename...> class F, typename T,
              typename... Ts>
    struct all_impl<Sequence<T, Ts...>, F<_1>>
    {
        static constexpr all_same tester{static_cast<typename F<T>::type *>(nullptr),
                                         static_cast<typename F<Ts>::type *>(nullptr)...};
        using type = bool_<(F<T>::type::value != 0 && tester.value)>;
    };
}
#endif

// Is a predicate true for every type ?
template <typename Sequence, typename Predicate = detail::non_null>
using all = typename detail::all_impl<Sequence, Predicate>::type;
}
#endif
