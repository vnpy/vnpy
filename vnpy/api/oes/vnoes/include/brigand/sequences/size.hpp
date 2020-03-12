/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_SIZE_HPP
#define BOOST_BRIGAND_SEQUENCES_SIZE_HPP
#include <brigand/algorithms/wrap.hpp>
#include <brigand/algorithms/count.hpp>

namespace brigand
{
  template<class L> using size = wrap<L, count>;
}
#endif
