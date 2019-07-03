/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_APPEND_HPP
#define BOOST_BRIGAND_SEQUENCES_APPEND_HPP

#include <brigand/algorithms/wrap.hpp>
#include <brigand/sequences/list.hpp>

namespace brigand
{
namespace detail
{
    template <typename... Ts>
    struct append_impl
    {
        using type = brigand::empty_sequence;
    };

    template <typename T>
    struct append_impl<T>
    {
        using type = T;
    };

    template <template <typename...> class L1, template <typename...> class L2, typename... T1s,
              typename... T2s, typename... Ts>
    struct append_impl<L1<T1s...>, L2<T2s...>, Ts...> : append_impl<L1<T1s..., T2s...>, Ts...>
    {
    };
    // fast track
    template <template <typename...> class L, template <typename...> class L1,
              template <typename...> class L2, template <typename...> class L3,
              template <typename...> class L4, template <typename...> class L5,
              template <typename...> class L6, template <typename...> class L7,
              template <typename...> class L8, template <typename...> class L9,
              template <typename...> class L10, template <typename...> class L11,
              template <typename...> class L12, template <typename...> class L13,
              template <typename...> class L14, template <typename...> class L15,
              template <typename...> class L16, typename... Ts, typename... T1s, typename... T2s,
              typename... T3s, typename... T4s, typename... T5s, typename... T6s, typename... T7s,
              typename... T8s, typename... T9s, typename... T10s, typename... T11s,
              typename... T12s, typename... T13s, typename... T14s, typename... T15s,
              typename... T16s, typename... Us>
    struct append_impl<L<Ts...>, L1<T1s...>, L2<T2s...>, L3<T3s...>, L4<T4s...>, L5<T5s...>,
                       L6<T6s...>, L7<T7s...>, L8<T8s...>, L9<T9s...>, L10<T10s...>, L11<T11s...>,
                       L12<T12s...>, L13<T13s...>, L14<T14s...>, L15<T15s...>, L16<T16s...>, Us...>
        : append_impl<L<Ts..., T1s..., T2s..., T3s..., T4s..., T5s..., T6s..., T7s..., T8s...,
                        T9s..., T10s..., T11s..., T12s..., T13s..., T14s..., T15s..., T16s...>,
                      Us...>
    {
    };
}
namespace lazy
{
    /*!
     * \ingroup Sequences
     * \ingroup List
     * \brief Lazily combine N lists into a single list
     *
     * Similar to brigand::append except that it is a lazy metafunction
     * instead of an eager metafunction.
     *
     * \example
     * Below is an example of how to use `brigand::lazy::append`. The
     * `static_assert` is used to show the returned list from `lazy::append`
     * \snippet append.cpp append_lazy_example
     *
     * \see brigand::append
     */
    template <typename... Ts>
    using append = detail::append_impl<Ts...>;
}
/*!
 * \ingroup Sequences
 * \ingroup List
 * \brief Combine N lists into a single list
 *
 * Merges the elements in N lists into a single list with the elements in
 * the resulting list being in the same order as the elements in the
 * individual lists, with the elements of the first list before the elements
 * of the second list, etc.
 *
 * \example
 * Below is an example of how to use `brigand::append`. The `static_assert`
 * is used to show the returned list from `append`
 * \snippet append.cpp append_simple_example
 *
 * \see brigand::join
 */
template <typename... Ts>
using append = typename detail::append_impl<Ts...>::type;

namespace lazy
{
    /*!
     * \ingroup Sequences
     * \ingroup List
     * \brief Lazily combine a list of N lists into a single list
     *
     * Similar to brigand::join except that it is a lazy metafunction
     * instead of an eager metafunction.
     *
     * \example
     * Below is an example of how to use `brigand::lazy::join`. The
     * `static_assert` is used to show the returned list from `lazy::join`
     * \snippet join.cpp join_lazy_example
     *
     * \see brigand::join
     */
    template <typename T>
    struct join;
    /// \cond
    template <template <typename...> class L, typename... Ts>
    struct join<L<Ts...>> : ::brigand::detail::append_impl<L<>, Ts...>
    {
    };
    /// \endcond
}

/*!
 * \ingroup Sequences
 * \ingroup List
 * \brief Combine a list of N lists into a single list
 *
 * For `T` being a list, brigand::join merges the elements in the N sub-lists
 * into a single list with the elements in the resulting list being in the
 * same order as the elements in the individual lists, with the elements of
 * the first list before the elements of the second list, etc.
 *
 * \example
 * Below is an example of how to use `brigand::join`. The `static_assert`
 * is used to show the returned list from `join`
 * \snippet join.cpp join_simple_example
 *
 * \see brigand::append
 */
template <typename T>
using join = wrap<T, append>;
}
#endif
