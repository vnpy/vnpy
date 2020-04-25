/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_TRANSFORM_HPP
#define BOOST_BRIGAND_ALGORITHMS_TRANSFORM_HPP

#include <brigand/functions/lambda/apply.hpp>
#include <brigand/sequences/back.hpp>
#include <brigand/sequences/filled_list.hpp>
#include <brigand/sequences/size.hpp>

namespace brigand
{
namespace detail
{
    template <class L1, class L2>
    struct rot90;

    template <class... L1, template <class...> class S1, class... T1, template <class...> class S2,
              class... T2, template <class...> class S3, class... T3, template <class...> class S4,
              class... T4, template <class...> class S5, class... T5, template <class...> class S6,
              class... T6, template <class...> class S7, class... T7, template <class...> class S8,
              class... T8, class... L2>
    struct rot90<list<L1...>, list<S1<T1...>, S2<T2...>, S3<T3...>, S4<T4...>, S5<T5...>, S6<T6...>,
                                   S7<T7...>, S8<T8...>, L2...>>
        : rot90<list<push_back<L1, T1, T2, T3, T4, T5, T6, T7, T8>...>, list<L2...>>
    {
    };

    template <class... L1, template <class...> class S, class... T, class... L2>
    struct rot90<list<L1...>, list<S<T...>, L2...>> : rot90<list<push_back<L1, T>...>, list<L2...>>
    {
    };

    template <class L1>
    struct rot90<L1, list<>>
    {
        using type = L1;
    };

    template <class Func, class Seq1, class Seq2, class Seqs>
    struct transform_impl;

    template <class F, class T1, class T2, class Seq>
    struct transform_apply;

    template <class F, class T1, class T2, class... Ts>
    struct transform_apply<F, T1, T2, list<Ts...>>
    {
        using type = brigand::apply<F, T1, T2, Ts...>;
    };

    template <class Func, template <class...> class Seq1, class... T1,
              template <class...> class Seq2, class... T2, class... Seqs>
    struct transform_impl<Func, Seq1<T1...>, Seq2<T2...>, list<Seqs...>>
    {
        using type = Seq1<typename transform_apply<Func, T1, T2, Seqs>::type...>;
    };

    template <unsigned int N, class Seq1, class Seq2, class... FuncOrSeqs>
    struct transform : transform_impl<back<list<FuncOrSeqs...>>, Seq1, Seq2,
                                      typename rot90<filled_list<list<>, size<Seq1>::value>,
                                                     pop_back<list<FuncOrSeqs...>>>::type>
    {
    };

    template <template <class...> class Seq, class... T, class Func>
    struct transform<0, Seq<T...>, Func>
    {
        using type = Seq<brigand::apply<Func, T>...>;
    };

    // fast track for eager
    template <template <class...> class Seq, class... T, template <typename...> class Func>
    struct transform<0, Seq<T...>, bind<Func, _1>>
    {
        using type = Seq<Func<T>...>;
    };

    // fast track for lazy
    template <template <class...> class Seq, class... T, template <typename...> class Func>
    struct transform<0, Seq<T...>, Func<_1>>
    {
        using type = Seq<typename Func<T>::type...>;
    };

    template <template <class...> class Seq1, class... T1, template <class...> class Seq2,
              class... T2, class Func>
    struct transform<1, Seq1<T1...>, Seq2<T2...>, Func>
    {
        using type = Seq1<brigand::apply<Func, T1, T2>...>;
    };
}

namespace lazy
{
    template <typename Sequence1, typename OpSeq1, typename... OpSeq2>
    struct transform : detail::transform<sizeof...(OpSeq2), Sequence1, OpSeq1, OpSeq2...>
    {
    };
}

// Main transform entry point
template <typename Sequence1, typename OpSeq1, typename... OpSeq2>
using transform = typename detail::transform<sizeof...(OpSeq2), Sequence1, OpSeq1, OpSeq2...>::type;
}
#endif
