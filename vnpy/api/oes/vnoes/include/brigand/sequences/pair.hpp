/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_SEQUENCES_PAIR_HPP
#define BOOST_BRIGAND_SEQUENCES_PAIR_HPP

namespace brigand
{
    template <typename First, typename Second>
    struct pair
    {
        using first_type = First;
        using second_type = Second;
    };

}
#endif
