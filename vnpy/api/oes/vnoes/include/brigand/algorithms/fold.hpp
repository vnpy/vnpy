/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_FOLD_HPP
#define BOOST_BRIGAND_ALGORITHMS_FOLD_HPP

#include <brigand/algorithms/detail/fold.hpp>

namespace brigand
{
namespace lazy
{
    template <class Sequence, class State, class Functor>
    using fold = typename detail::fold_impl<Functor, State, Sequence>;
    template <class Sequence, class State, class Functor>
    using reverse_fold = typename detail::reverse_fold_impl<Functor, State, Sequence>;
}

// Main fold entry point
template <class Sequence, class State, class Functor>
using fold = typename ::brigand::lazy::fold<Sequence, State, Functor>::type;
template <class Sequence, class State, class Functor>
using reverse_fold = typename ::brigand::lazy::reverse_fold<Sequence, State, Functor>::type;
}
#endif
