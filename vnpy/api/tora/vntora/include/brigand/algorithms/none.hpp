/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_NONE_HPP
#define BOOST_BRIGAND_ALGORITHMS_NONE_HPP

#include <brigand/algorithms/all.hpp>
#include <brigand/algorithms/detail/non_null.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/types/bool.hpp>

namespace brigand
{
#if defined(BRIGAND_COMP_MSVC_2013) || defined(BRIGAND_COMP_CUDA) || defined(BRIGAND_COMP_INTEL)
namespace detail
{
    template <typename Sequence, typename Pred>
    struct none_impl
    {
        template <typename T>
        struct nope
        {
            using that = brigand::apply<Pred, T>;
            using type = bool_<!that::value>;
        };
        using type = all<Sequence, nope<_1>>;
    };
}
#else
namespace detail
{

    template <typename Sequence, typename Predicate>
    struct none_impl : bool_<true>
    {
    };

    template <template <class...> class Sequence, typename Predicate, typename T, typename... Ts>
    struct none_impl<Sequence<T, Ts...>, Predicate>
    {
        static constexpr all_same tester{
            static_cast< ::brigand::apply<Predicate, T> *>(nullptr),
            static_cast< ::brigand::apply<Predicate, Ts> *>(nullptr)...};
        using type = bool_<(::brigand::apply<Predicate, T>::value == 0 && tester.value)>;
    };

    template <template <class...> class Sequence, template <typename...> class F, typename T,
              typename... Ts>
    struct none_impl<Sequence<T, Ts...>, bind<F, _1>>
    {
        static constexpr all_same tester{static_cast<F<T> *>(nullptr),
                                         static_cast<F<Ts> *>(nullptr)...};
        using type = bool_<(F<T>::value == 0 && tester.value)>;
    };

    template <template <class...> class Sequence, template <typename...> class F, typename T,
              typename... Ts>
    struct none_impl<Sequence<T, Ts...>, F<_1>>
    {
        static constexpr all_same tester{static_cast<typename F<T>::type *>(nullptr),
                                         static_cast<typename F<Ts>::type *>(nullptr)...};
        using type = bool_<(F<T>::type::value == 0 && tester.value)>;
    };
}
#endif

// Is a predicate true for no type ?
template <typename Sequence, typename Predicate = detail::non_null>
using none = typename detail::none_impl<Sequence, Predicate>::type;
}
#endif
