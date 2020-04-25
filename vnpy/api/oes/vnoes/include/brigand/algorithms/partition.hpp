/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_PARTITION_HPP
#define BOOST_BRIGAND_ALGORITHMS_PARTITION_HPP

#include <brigand/algorithms/remove.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/sequences/pair.hpp>

namespace brigand
{
template <class Seq, class Pred>
using partition = pair<filter<Seq, Pred>, remove_if<Seq, Pred>>;
}
#endif
