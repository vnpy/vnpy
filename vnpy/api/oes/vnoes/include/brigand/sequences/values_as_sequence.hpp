#ifndef BOOST_BRIGAND_SEQUENCES_VALUES_AS_SEQUENCE_HPP
#define BOOST_BRIGAND_SEQUENCES_VALUES_AS_SEQUENCE_HPP

#include <brigand/adapted/list.hpp>
#include <brigand/algorithms/transform.hpp>

namespace brigand
{
namespace detail
{
    template <typename Pair>
  struct get_second {
    using type = typename Pair::second_type;
  };
} // namespace detail

template <typename Map, template <class...> class Sequence = brigand::list>
using values_as_sequence = transform<as_sequence<Map, Sequence>, detail::get_second<_1>>;

} // namespace brigand
#endif
