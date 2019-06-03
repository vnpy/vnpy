#pragma once

#include "../utils/type_traits.hpp"

namespace autocxxpy
{
    template <class T, class T2>
    auto append_as_tuple(T&& v1, T2&& v2)
    {
        return std::make_tuple<T, remove_cvref_t<T2>>(std::move(v1), std::move(v2));
    }

    template <class ... Ts, class T2, size_t ... idx>
    auto append_as_tuple_impl(std::tuple<Ts...> tv, T2&& v2, std::index_sequence<idx...>)
    {
        return std::make_tuple<Ts ..., T2>(std::move(std::get<idx>(tv)) ..., std::move(v2));
    }

    template <class ... Ts, class T2>
    auto append_as_tuple(std::tuple<Ts ...>&& tv, T2&& v2)
    {
        return append_as_tuple_impl(std::move(tv), std::move(v2), std::index_sequence_for<Ts...>{});
    }
}
