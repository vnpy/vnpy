/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_INDEX_OF_HPP
#define BOOST_BRIGAND_ALGORITHMS_INDEX_OF_HPP

#include <brigand/algorithms/find.hpp>
#include <brigand/sequences/size.hpp>
#include <brigand/types/integer.hpp>
#include <brigand/types/no_such_type.hpp>
#include <brigand/functions/lambda/apply.hpp>

namespace brigand
{

namespace detail
{
    template <bool Found, class Sequence, typename Predicate, typename NotFoundType>
    struct index_if_impl
    {
        using type = ::brigand::size_t<size<Sequence>::value -
                                       size< ::brigand::find<Sequence, Predicate>>::value>;
    };

    template <class Sequence, typename Predicate, typename NotFoundType>
    struct index_if_impl<false, Sequence, Predicate, NotFoundType>
    {
        using type = NotFoundType;
    };
} // namespace detail

template <class Sequence, class Predicate, class NotFoundType = no_such_type_>
using index_if = typename detail::index_if_impl< ::brigand::found<Sequence, Predicate>::value,
                                                Sequence, Predicate, NotFoundType>::type;

template <class Sequence, typename T>
using index_of = index_if<Sequence, std::is_same<typename brigand::pin<T>, ::brigand::_1>>;

} // namespace brigand
#endif
