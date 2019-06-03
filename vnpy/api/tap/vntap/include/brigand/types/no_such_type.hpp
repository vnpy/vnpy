/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_TYPES_NO_SUCH_TYPE_HPP
#define BOOST_BRIGAND_TYPES_NO_SUCH_TYPE_HPP

namespace brigand
{
    // type to return when finding something fails
    // I wanted to call it "not sure if type" but Joel didn't want to :(
    struct no_such_type_ {};
}
#endif
