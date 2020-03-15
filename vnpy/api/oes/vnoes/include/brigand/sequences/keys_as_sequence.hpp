#ifndef BOOST_BRIGAND_SEQUENCES_KEYS_AS_SEQUENCE_HPP
#define BOOST_BRIGAND_SEQUENCES_KEYS_AS_SEQUENCE_HPP

#include <brigand/adapted/list.hpp>
#include <brigand/algorithms/transform.hpp>
#include <brigand/sequences/set.hpp>

namespace brigand
{
namespace detail
{
    template <typename Pair>
  struct get_first {
    using type = typename Pair::first_type;
  };
} // namespace detail

template <typename Map, template <class...> class Sequence = brigand::set>
using keys_as_sequence = transform<as_sequence<Map, Sequence>, detail::get_first<_1>>;

} // namespace brigand
#endif
