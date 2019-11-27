#pragma once

#include "../base/type.h"

#include <boost/callable_traits.hpp>
#include "../brigand.hpp"

#ifdef AUTOCXXPY_INCLUDED_PYBIND11
#include <pybind11/stl.h>
#endif
#include <functional>
#include "../base/check.h"

namespace c2py
{
    template <size_t size>
    using string_array = literal_array<char*, size>;
    template <size_t size>
    using const_string_array = literal_array<const char*, size>;

    template <class T>
    struct is_string_array : std::false_type {};

    template <>
    struct is_string_array<char**> :std::true_type {};

    template <>
    struct is_string_array<const char**> :std::true_type {};

    template <size_t size>
    struct is_string_array<string_array<size>> :std::true_type {};

    template <size_t size>
    struct is_string_array<const_string_array<size>> :std::true_type {};

    template <class T>
    constexpr bool check_is_string_array()
    {
        constexpr bool is = is_string_array<T>::value;
        static_assert(is, "type is not string array!");
        return is;
    }

    template <class T>
    constexpr bool check_is_integral()
    {
        constexpr bool is = std::is_integral_v<T>;
        static_assert(is, "type is not a integral!");
        return is;
    }

    template <class method_constant, class array_type, class size_type, class ... Ls, class ... Rs>
    inline constexpr auto _wrap_string_array_impl(brigand::list<Ls...>, brigand::list<Rs...>)
    {
        return [](Ls ...ls, std::vector<std::string> & vals, Rs ... rs)
        {
            constexpr auto method = method_constant::value;
            namespace ct = boost::callable_traits;
            using func_t = typename ct::function_type_t<decltype(method)>;

            std::vector<char*> arr;
            arr.reserve(vals.size());
            for (auto& s : vals)
            {
                arr.push_back(const_cast<char*>(s.data()));
            }
            return std::function<func_t>(method)(
                ls...,
                (array_type)&arr[0],
                (size_type)vals.size(),
                rs...
                );
        };
    }

    template <class method_constant, size_t index>
    inline constexpr auto wrap_string_array()
    {
        using namespace brigand;
        namespace ct = boost::callable_traits;

        constexpr auto method = method_constant::value;
        using func_t = ct::function_type_t<decltype(method)>;
        using args_t = ct::args_t<func_t, list>;

        if constexpr (check_not_out_of_bound<index + 1, size<args_t>::value>())
        {
            using array_type = at<args_t, integral_constant<int, index>>;
            using size_type = at<args_t, integral_constant<int, index + 1>>;

            using s = split_at<args_t, integral_constant<int, index>>;
            using ls = front<s>;
            using rs = pop_front<pop_front<back<s>>>;
            if constexpr (check_is_string_array<array_type>())
            {
                if constexpr (check_is_integral<size_type>())
                {
                    return _wrap_string_array_impl<method_constant, array_type, size_type>(ls{}, rs{});
                }
            }
        }
    }

    template <class method_constant, class integral_constant>
    struct string_array_transform
    {
        using type = string_array_transform;
        using value_type = decltype(wrap_string_array<method_constant, integral_constant::value>());
        static constexpr value_type value = wrap_string_array<method_constant, integral_constant::value>();
    };
}
