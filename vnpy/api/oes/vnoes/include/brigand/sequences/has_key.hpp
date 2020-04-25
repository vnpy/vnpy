/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_HAS_KEY_HPP
#define BOOST_BRIGAND_SEQUENCES_HAS_KEY_HPP
#include <brigand/types/type.hpp>

namespace brigand
{
namespace detail
{
    template<class C, class K>
    struct has_key_impl
    {
        using type = decltype(C::has_key(type_<K>{}));
    };
}

    template<class L, class K>
    using has_key = typename detail::has_key_impl<L, K>::type;
}
#endif
