#pragma once

#include "../base/type.h"

#include <boost/callable_traits.hpp>
#include "../brigand.hpp"

#ifdef AUTOCXXPY_INCLUDED_PYBIND11
#include <pybind11/stl.h>
#endif
#include <functional>

#include <iostream>

namespace autocxxpy
{
    template <size_t size>
    using string_array = literal_array<char *, size>;
    template <size_t size>
    using const_string_array = literal_array<const char *, size>;

    template <class T>
    struct is_string_array : std::false_type {};

    template <>
    struct is_string_array<char **> :std::true_type {};

    template <>
    struct is_string_array<const char **> :std::true_type {};

    template <size_t size>
    struct is_string_array<string_array<size>> :std::true_type {};

    template <size_t size>
    struct is_string_array<const_string_array<size>> :std::true_type {};

    template <class MethodConstant, class size_type, class ... Ls, class ... Rs>
    inline constexpr auto _wrap_string_array_impl(brigand::list<Ls...>, brigand::list<Rs...>)
    {
        return [](Ls ...ls, std::vector<std::string> &vals, Rs ... rs)
        {
            constexpr auto method = MethodConstant::value;
            namespace ct = boost::callable_traits;
            using func_t = typename ct::function_type_t<decltype(method)>;

            std::vector<char *> arr;
            arr.reserve(vals.size());
            for (auto &s : vals)
            {
                arr.push_back(const_cast<char *>(s.data()));
            }
            return std::function<func_t>(method)(
                ls...,
                &arr[0],
                (size_type)vals.size(),
                rs...
            );
        };
    }


    template <class MethodConstant, class args_t, class args_from_cfp>
    inline constexpr auto _wrap_string_array_nocheck()
    {
        using namespace brigand;
        namespace ct = boost::callable_traits;

        using target_t = front<args_from_cfp>;
        using size_type = front<pop_front<args_from_cfp>>;
        if constexpr (std::is_integral_v<size_type>)
        {
            constexpr int target_idx = index_of<args_t, target_t>::value;

            using ls = front<split_at<args_t, integral_constant<int, target_idx>>>;
            using rs = pop_front<args_from_cfp, integral_constant<int, 2>>;

            return _wrap_string_array_impl <MethodConstant, size_type>(ls{}, rs{});
        }
        else
        {
            constexpr auto method = MethodConstant::value;
            return method;
        }
    }

    template <class MethodConstant>
    inline constexpr auto wrap_string_array()
    {
        using namespace brigand;
        namespace ct = boost::callable_traits;

        constexpr auto method = MethodConstant::value;
        using func_t = ct::function_type_t<decltype(method)>;
        using args_t = wrap<ct::args_t<func_t>, list>;

        constexpr bool has_string_array_pointer = found<args_t, is_string_array<_1>>::value;
        if constexpr (has_string_array_pointer)
        {
            using args_from_cfp = find<args_t, is_string_array<_1>>;
            constexpr int nargs_left = size<args_from_cfp>::value;
            if constexpr (nargs_left >= 2)
            {
                return _wrap_string_array_nocheck<MethodConstant, args_t, args_from_cfp>();
            }
            else
            {
                return method;
            }
        }
        else
        {
            return method;
        }
    }

    template <class T>
    struct string_array_transform
    {
        using type = string_array_transform;
        using value_type = decltype(wrap_string_array<T>());
        static constexpr value_type value = wrap_string_array<T>();
    };
}
