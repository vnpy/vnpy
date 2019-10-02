/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_INSERT_HPP
#define BOOST_BRIGAND_SEQUENCES_INSERT_HPP

#include <brigand/types/type.hpp>

namespace brigand
{
namespace detail
{
    template <class C, class T>
    struct insert_impl
    {
        using type = decltype(C::insert(type_<T>{}));
    };
}

    template<class L, class T>
    using insert = typename detail::insert_impl<L, T>::type;
}
#endif
