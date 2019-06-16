#pragma once

#include "type_traits.hpp"
#include "algorithm.hpp"

namespace
{

    template <class ...>
    struct extractable {};

    template <template<class ...args> class extract_seq, class ...Ts>
    inline constexpr size_t extract_size() noexcept;

    template <template<class ...args> class extract_seq, class ...Ts>
    inline constexpr size_t extract_size_extract(extractable<Ts...>) noexcept
    {
        return extract_size<extract_seq, Ts...>();
    }

    template <template<class ...args> class extract_seq, class T>
    inline constexpr size_t extract_size_single() noexcept
    {
        using nocvref = remove_cvref_t<T>;
        if constexpr (is_specialization_of_v<nocvref, extract_seq>)
            return extract_size_extract <extract_seq>(brigand::wrap<nocvref, extractable>{});
        else
            return 1;
    }

    template <template<class ...args> class extract_seq = std::tuple, class ...Ts, int ... idx>
    inline constexpr size_t extract_size_multiple(std::index_sequence<idx ...>) noexcept
    {
        using seq = brigand::list<Ts...>;
        return tsum(
            extract_size_single<extract_seq,
            brigand::at<seq, brigand::integral_constant<int, idx> >
            >() ...
        );
    }

    template <template<class ...args> class extract_seq, class ...Ts>
    inline constexpr size_t extract_size() noexcept
    {
        return extract_size_multiple<extract_seq, Ts...>(std::index_sequence_for<Ts...>{});
    }

    template <template<class ...args> class extract_seq, class T>
    inline constexpr size_t extract_size(const T&) noexcept
    {
        return extract_size_single<extract_seq, T>();
    }

    template <class T>
    inline constexpr size_t extract_tuple_size(const T&) noexcept { return extract_size_single<std::tuple, remove_cvref<T>>(); }

    namespace _assert
    {
        using namespace std;
        static_assert(extract_size<tuple, tuple<int, int, tuple<int, int, int>, tuple<>>>() == 5);
        static_assert(extract_size<pair, int, tuple<>>() == 2);
        static_assert(extract_size<tuple>(1) == 1);
        static_assert(extract_size<tuple>(tuple<int, int, tuple<int, int, int>, tuple<> >{}) == 5);
        static_assert(extract_size<tuple>(tuple<int, int>{}) == 2);
        static_assert(extract_size<tuple, int, int>() == 2);
    }

    //////////////////////////////////////////////////////////////////////////
    template <size_t idx, size_t skip = 0, template<class ...args> class extract_seq, class ...Ts, template<class ...args> class seq>
    inline constexpr auto &extract_get_impl(const seq<Ts...> &t) noexcept
    {
        constexpr auto size = extract_size<extract_seq, decltype(t)>();
        static_assert(idx < size, "extract_get: index out of sequence bound");
        static_assert(size != 0, "trying get element of empty tuple");

        if constexpr (idx < size && size != 0)
        {
            auto &a0 = std::get<skip>(t);
            constexpr auto a0len = extract_size<extract_seq, decltype(a0)>();
            constexpr bool a0_is_seq = is_specialization_of_v<remove_cvref_t<decltype(a0)>, extract_seq>;

            if constexpr (idx == 0 && !a0_is_seq)
            {
                return a0;
            }
            else if constexpr (a0_is_seq && idx < a0len)
            { // extract and go into it
                return extract_get_impl<idx, 0, extract_seq>(a0);
            }
            else if constexpr (a0_is_seq)
            { // result is in the rest, skip this one
                return extract_get_impl<idx - a0len, skip + 1, extract_seq>(t);
            }
            else // if  constexpr(idx != 0)
            { // a0 is not a extract, just skip 1 element
                return extract_get_impl<idx - 1, skip + 1, extract_seq>(t);
            }
        }
    }


    template <size_t idx, template<class ...args> class extract_seq, class ...Ts, template<class ...args> class seq>
    inline constexpr auto &extract_get(const seq<Ts...> &t) noexcept
    {
        return extract_get_impl<idx, 0, extract_seq>(t);
    }

    namespace _assert
    {
        using namespace std;
        struct s {};
        static_assert(extract_get<0, tuple>(make_tuple(1)) == 1);
        static_assert(extract_get<1, tuple>(make_tuple(0, 1)) == 1);
        static_assert(extract_get<1, tuple>(make_tuple(0, make_tuple(1))) == 1);
        static_assert(extract_get<15, tuple>(make_tuple(make_tuple(0, 1, 2, 3, 4, 5, 6, 7), make_tuple(8), make_tuple(9), 0, 1, 2, 3, 4, 5)) == 5);
        static_assert(extract_get<1, tuple>(make_tuple(make_tuple(), make_tuple(), make_tuple(0), make_tuple(1))) == 1);
        static_assert(extract_get<1, tuple>(make_tuple(0, make_tuple(1), make_tuple(make_tuple(2)))) == 1);
        static_assert(extract_get<1, tuple>(make_tuple(0, make_tuple(1), make_tuple(), make_tuple(2))) == 1);
        static_assert(extract_get<1, tuple>(make_tuple(0, make_tuple(2), make_tuple(), make_tuple(s{}))) == 2);
        static_assert(extract_get<1, tuple>(make_tuple(0, make_tuple(1), make_tuple(), make_tuple(s{}))) != 2);
        static_assert(extract_get<1, tuple>(make_tuple(0, make_tuple(), make_tuple(1))) == 1);

        static_assert(extract_get<1, tuple>(make_tuple(s{}, pair(0, 1))).first == 0);
        static_assert(std::get<1>(extract_get<0, pair>(make_tuple(make_tuple(0, 1)))) == 1);

    }

    template <size_t idx, class ...Ts, template<class ...args> class seq>
    inline constexpr auto &extract_tuple_get(const seq<Ts...> &t)
    {
        return extract_get<idx, std::tuple>(t);
    }

}