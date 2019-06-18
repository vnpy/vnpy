/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_FUNCTIONS_MISC_REPEAT_HPP
#define BOOST_BRIGAND_FUNCTIONS_MISC_REPEAT_HPP

namespace brigand
{
namespace detail
{
    template<template<class> class F, unsigned N, class T>
    struct repeat_impl
    : repeat_impl<F, N-7, F<F<F<F<F<F<F<T>>>>>>>>
    {};

    template<template<class> class F, class T>
    struct repeat_impl<F, 7, T>
    {
        using type = F<F<F<F<F<F<F<T>>>>>>>;
    };

    template<template<class> class F, class T>
    struct repeat_impl<F, 6, T>
    {
        using type = F<F<F<F<F<F<T>>>>>>;
    };

    template<template<class> class F, class T>
    struct repeat_impl<F, 5, T>
    {
        using type = F<F<F<F<F<T>>>>>;
    };

    template<template<class> class F, class T>
    struct repeat_impl<F, 4, T>
    {
        using type = F<F<F<F<T>>>>;
    };

    template<template<class> class F, class T>
    struct repeat_impl<F, 3, T>
    {
        using type = F<F<F<T>>>;
    };

    template<template<class> class F, class T>
    struct repeat_impl<F, 2, T>
    {
        using type = F<F<T>>;
    };

    template<template<class> class F, class T>
    struct repeat_impl<F, 1, T>
    {
        using type = F<T>;
    };

    template<template<class> class F, class T>
    struct repeat_impl<F, 0, T>
    {
        using type = T;
    };
}

namespace lazy
{
    template<template<class> class F, class N, class T>
    using repeat = typename detail::repeat_impl<F, N::value, T>;
}

    template<template<class> class F, class N, class T>
    using repeat = typename ::brigand::lazy::repeat<F, N, T>::type;
}
#endif
