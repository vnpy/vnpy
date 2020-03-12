/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_FLATTEN_HPP
#define BOOST_BRIGAND_ALGORITHMS_FLATTEN_HPP

#include <brigand/sequences/list.hpp>
#include <brigand/sequences/append.hpp>

namespace brigand
{
namespace detail
{

    template <class L>
    struct flatten_impl
    {
        using type = L;
    };

    template <template<class...> class L, class T>
    struct flatten_element_impl
    {
        using type = L<T>;
    };

    template <template<class...> class L, class... Ts>
    struct flatten_element_impl<L, L<Ts...>>
    : append_impl<typename flatten_element_impl<L, Ts>::type...>
    {
    };

    template <template<class...> class L, class... Ts>
    struct flatten_impl<L<Ts...>>
    : flatten_element_impl<L, L<Ts...>>
    {
    };

}

namespace lazy
{
    template <typename Sequence>
    using flatten = typename detail::flatten_impl<Sequence>;
}

/*!
 * \ingroup Algorithms
 * \ingroup List
 * \brief Merge the contents of several lists into one list
 *
 * Given a list of lists and types, returns a new list with the contents of the lists and the types.
 *
 * \example
 * Below is an example of how to use brigand::flatten. The `static_assert` is used to show the
 * returned list from flatten
 * \snippet flatten.cpp flatten_simple_example
 */
template <typename Sequence>
using flatten = typename lazy::flatten<Sequence>::type;

}
#endif
