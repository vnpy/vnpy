#pragma once

#include "../base/type.h"
#include "../base/check.h"

#include <boost/callable_traits.hpp>
#include "../brigand.hpp"

#ifdef AUTOCXXPY_INCLUDED_PYBIND11
#include <pybind11/stl.h>
#endif

#include <iostream>
#include <type_traits>

#include "./utils.hpp"

namespace autocxxpy
{
    template <class method_constant, class ret_t, class base_t, class ... Ls, class ... Rs>
    inline constexpr auto wrap_pointer_argument_as_output_impl(brigand::list<Ls...>, brigand::list <Rs...>)
    {
        namespace ct = boost::callable_traits;
        return [](Ls ... ls, Rs ... rs)
        {
            base_t arg;
            constexpr auto method = method_constant::value;
            auto stdmethod = std::function<ct::function_type_t<decltype(method)>>(method);
            if constexpr (std::is_void_v<ret_t>)
            {
                stdmethod(std::forward<Ls>(ls)..., &arg, std::forward<Rs>(rs)...);
                return std::move(arg);
            }
            else
            {
                return append_as_tuple(stdmethod(
                    std::forward<Ls>(ls)...,
                    &arg,
                    std::forward<Rs>(rs)...
                ), std::move(arg));

            }
        };
    }
    template <class method_constant, class ret_t, class base_t, class ... Ls, class ... Rs>
    inline constexpr auto wrap_reference_argument_as_output_impl(brigand::list<Ls...>, brigand::list <Rs...>)
    {
        namespace ct = boost::callable_traits;
        return [](Ls ... ls, Rs ... rs)
        {
            base_t arg;
            constexpr auto method = method_constant::value;
            auto stdmethod = std::function<ct::function_type_t<decltype(method)>>(method);
            if constexpr (std::is_void_v<ret_t>)
            {
                stdmethod(std::forward<Ls>(ls)..., arg, std::forward<Rs>(rs)...);
                return arg;
            }
            else
            {
                return append_as_tuple(stdmethod(
                    std::forward<Ls>(ls)...,
                    arg,
                    std::forward<Rs>(rs)...
                ), arg);

            }
        };
    }

    template <class method_constant, size_t index>
    inline constexpr auto wrap_argument_as_output()
    {
        using namespace brigand;
        namespace ct = boost::callable_traits;

        constexpr auto method = method_constant::value;
        using func_t = ct::function_type_t<decltype(method)>;
        using args_t = wrap<ct::args_t<func_t>, list>;

        if constexpr (check_not_out_of_bound<index, size<args_t>::value>())
        {
            using s = split_at<args_t, std::integral_constant<int, index>>;
            using ls = front<s>;
            using rs = pop_front<back<s>>;
            using arg_t = at<args_t, std::integral_constant<int, index>>;
            using ret_t = ct::return_type_t<func_t>;
            if constexpr (std::is_pointer_v<arg_t>)
            {
                using base_t = std::remove_pointer_t<arg_t>;
                return wrap_pointer_argument_as_output_impl<method_constant, ret_t, base_t>(ls{}, rs{});
            }
            else
            {
                using base_t = std::remove_reference_t<arg_t>;
                return wrap_reference_argument_as_output_impl<method_constant, ret_t, base_t>(ls{}, rs{});
            }
        }
    }

    template <class method_constant, class integral_constant>
    struct output_argument_transform
    {
        using type = output_argument_transform;
        using value_type = decltype(wrap_argument_as_output<method_constant, integral_constant::value>());
        static constexpr value_type value = wrap_argument_as_output<method_constant, integral_constant::value>();
    };
}
