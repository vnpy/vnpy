/*!
@file

@copyright Edouard Alligand and Joel Falcou 2015-2017
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_BRIGAND_FUNCTIONS_LAMBDA_APPLY_HPP
#define BOOST_BRIGAND_FUNCTIONS_LAMBDA_APPLY_HPP

#include <brigand/functions/lambda/bind.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/types/args.hpp>

namespace brigand
{

template <typename T>
struct defer
{
};
//mark a parameter as a type (as in not a lambda)
template <typename T>
struct pin
{
};
//select args from one layer higher in cascading lambdas
template <typename T>
struct parent
{
};
namespace detail
{

    template <typename T, typename... Ts>
    struct packaged_lcall    //this is used in ourder to propagate args from super lambdas to sub lambdas
    {
    };
    template <typename T, typename... Ls>
  struct apply {
    using type = T;  //default is interpreted as if it were a pin<T>
  };

  //eager call case
  template <template<typename...> class F, typename...Ts, typename... Args>
  struct apply<bind<F,Ts...>, Args...>
  {
    using type = F<typename apply<Ts, Args...>::type...>;
  };

  //lazy call cases
  template <template <typename...> class F, typename... Ts, typename L, typename... Ls>
  struct apply<F<Ts...>, L, Ls...> : F<typename apply<Ts, L, Ls...>::type...>
  {
  };

    //pin case
  template <typename T, typename... Args, typename...Ls>
  struct apply<pin<T>, list<Args...>, Ls...>
  {
    using type = T;
  };
  //arg case
  template <unsigned int N, typename L, typename...Ls>
  struct apply<args<N>, L, Ls...>
  {
    using type = at_c<L, N>;
  };
  //arg fast track
  template <typename T, typename...Ts, typename...Ls>
  struct apply<_1, list<T, Ts...>, Ls...>
  {
    using type = T;
  };
  //arg fast track
  template <typename T, typename U, typename...Ts, typename...Ls>
  struct apply<_2, list<T, U, Ts...>, Ls...>
  {
    using type = U;
  };
  //parent case
  template <typename T, typename L, typename...Ls>
  struct apply<parent<T>, L, Ls...> : apply<T,Ls...>
  {
  };
  //defer case
  template <typename Lambda, typename L, typename...Ls>
  struct apply<defer<Lambda>, L, Ls...>
  {
    using type = packaged_lcall<Lambda, L, Ls...>;
  };
  //packaged_lcall lazy case
  template <template <typename...> class Lambda, typename... Ts, typename... PLs, typename L, typename...Ls>
  struct apply<packaged_lcall<Lambda<Ts...>, PLs...>, L, Ls...> : Lambda<typename apply<Ts, L, Ls..., PLs...>::type...>
  {
  };
  //packaged_lcall eager case
  template <template <typename...> class Lambda, typename... Ts, typename... PLs, typename L, typename...Ls>
  struct apply<packaged_lcall<bind<Lambda,Ts...>, PLs...>, L, Ls...>
  {
    using type = Lambda<typename apply<Ts, L, Ls..., PLs...>::type...>;
  };

  template<typename T, typename...Ts>
  using bound_apply = typename apply<T, brigand::list<Ts...>>::type;

}

template <typename Lambda, typename... Args>
using apply = typename detail::apply<Lambda, brigand::list<Args...>>::type;
}
#endif
