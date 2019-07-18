/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_CONTAINS_HPP
#define BOOST_BRIGAND_SEQUENCES_CONTAINS_HPP

#include <brigand/types/type.hpp>

namespace brigand
{
namespace detail
{
    template <class L, class K>
    struct contains_impl
    {
        using type = decltype(L::contains(type_<K>{}));
    };
}
    template <class L, class K>
    using contains = typename detail::contains_impl<L, K>::type;
}
#endif
