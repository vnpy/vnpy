/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_ALGORITHMS_DETAIL_FOLD_HPP
#define BOOST_BRIGAND_ALGORITHMS_DETAIL_FOLD_HPP

#include <brigand/functions/lambda/apply.hpp>

namespace brigand { namespace detail
{

  template<class Functor, class State, class Sequence>
  struct fold_impl
  {
      using type = State;
  };

  template<
      class Functor, class State, template <class...> class Sequence,
      class T0>
  struct fold_impl<Functor, State, Sequence<T0>>
  {
      using type = brigand::apply<Functor, State, T0>;
  };
 
  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1>
  struct fold_impl<Functor, State, Sequence<T0, T1>>
  {
      using type = brigand::apply<Functor,
          brigand::apply<Functor,State, T0>, T1
      >;
  };

  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2>>
  {
      using type = brigand::apply<Functor,
          brigand::apply<Functor,
              brigand::apply<Functor, State, T0>, T1
          >, T2
      >;
  };

  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3>>
  {
      using type = brigand::apply<Functor,
          brigand::apply<Functor, 
              brigand::apply<Functor,
                  brigand::apply<Functor, State, T0>, T1
              >, T2
          >, T3
      >;
  };

  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3, class T4>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3, T4>>
  {
      using type = brigand::apply<Functor,
          brigand::apply<Functor,
              brigand::apply<Functor,
                  brigand::apply<Functor,
                      brigand::apply<Functor, State, T0>, T1
                  >, T2
              >, T3
          >, T4
      >;
  };

  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3, class T4, class T5>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3, T4, T5>>
  {
      using type = brigand::apply<Functor,
          brigand::apply<Functor,
              brigand::apply<Functor,
                  brigand::apply<Functor,
                      brigand::apply<Functor,
                          brigand::apply<Functor, State, T0>, T1
                      >, T2
                  >, T3
              >, T4
          >, T5
      >;
  };

  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3, class T4, class T5, class T6>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3, T4, T5, T6>>
  {
      using type = brigand::apply<Functor,
          brigand::apply<Functor,
              brigand::apply<Functor,
                  brigand::apply<Functor,
                      brigand::apply<Functor,
                          brigand::apply<Functor,
                              brigand::apply<Functor, State, T0>, T1
                          >, T2
                      >, T3
                  >, T4
              >, T5
          >, T6
      >;
  };

  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3, T4, T5, T6, T7>>
  {
      using type = brigand::apply<Functor,
          brigand::apply<Functor,
              brigand::apply<Functor,
                  brigand::apply<Functor,
                      brigand::apply<Functor,
                          brigand::apply<Functor,
                              brigand::apply<Functor,
                                  brigand::apply<Functor, State, T0>, T1
                              >, T2
                          >, T3
                      >, T4
                  >, T5
              >, T6
          >, T7
      >;
  };

  template<
      class Functor, class State, template <class...> class Sequence,
      class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class... T>
  struct fold_impl<Functor, State, Sequence<T0, T1, T2, T3, T4, T5, T6, T7, T...>>
  : fold_impl<
      Functor,
      brigand::apply<Functor,
          brigand::apply<Functor,
              brigand::apply<Functor,
                  brigand::apply<Functor,
                      brigand::apply<Functor,
                          brigand::apply<Functor,
                              brigand::apply<Functor,
                                  brigand::apply<Functor,
                                      State, T0
                                  >, T1
                              >, T2
                          >, T3
                      >, T4
                  >, T5
              >, T6
          >, T7
      >,
      Sequence<T...>
  >
  {};

  template<typename Functor, typename State, typename Sequence>
  struct reverse_fold_impl
  {
    using type = State;
  };

  template <typename Functor, typename State, template <typename...> class L, typename T, typename... Ts>
  struct reverse_fold_impl<Functor, State, L<T, Ts...>>
  {
      using type =
          brigand::apply<Functor, typename reverse_fold_impl<Functor, State, L<Ts...>>::type, T>;
  };

  template<
    typename Functor, typename State, template <typename...> class L,
    typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename... Ts>
    struct reverse_fold_impl<Functor, State, L<T0, T1, T2, T3, T4, T5, T6, T7, Ts...>>{
    using type = brigand::apply<Functor,
      brigand::apply<Functor,
      brigand::apply<Functor,
      brigand::apply<Functor,
      brigand::apply<Functor,
      brigand::apply<Functor,
      brigand::apply<Functor,
      brigand::apply<Functor,
      typename reverse_fold_impl<Functor, State, L<Ts...>>::type, T7
      >, T6
      >, T5
      >, T4
      >, T3
      >, T2
      >, T1
      >, T0
      >;
  };

} }
#endif
