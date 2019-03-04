/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_DETAIL_NON_NULL_HPP
#define BOOST_BRIGAND_ALGORITHMS_DETAIL_NON_NULL_HPP

#include <brigand/types/bool.hpp>
#include <brigand/types/args.hpp>

namespace brigand
{
namespace detail
{
    // Default find-like predicate

    template <typename Args>
  struct non_null_impl : bool_<Args::value != 0>{};
    using non_null = non_null_impl<_1>;
}
}
#endif
