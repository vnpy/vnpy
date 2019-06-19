#pragma once

#include <boost/callable_traits.hpp>

#include "../brigand.hpp"
#include "../base/check.h"

namespace autocxxpy
{

    template <class T>
    struct is_c_function_callback : std::false_type {};

    template <class Ret, class ... Args>
    struct is_c_function_callback<Ret(*)(Args...)> :std::true_type {};

    template <class method_constant, class Func, class ... binding_args, class ... Ls, class ... Rs>
    inline constexpr auto _wrap_c_function_callback_impl(brigand::list<binding_args...>, brigand::list<Ls...>, brigand::list<Rs...>)
    {
        return [](Ls ...ls, Func & func, Rs ... rs)
        {
            constexpr auto wrapped_callback =
                [](binding_args ... largs, void* pf)
            {
                Func* binding_function = (Func*)pf;
#ifdef PYBIND11_OVERLOAD
                pybind11::gil_scoped_acquire gil;
#endif
                return (*binding_function)(largs...);
            };
            constexpr auto method = method_constant::value;
            return method(
                ls...,
                std::move(wrapped_callback),
                (void*)new Func(func),
                rs...
            );
        };
    }

    template <class T>
    constexpr bool check_is_c_function_callback()
    {
        constexpr bool is = is_c_function_callback<T>::value;
        return is;
    }


    template <class T>
    using pop_back_args = typename brigand::pop_back<boost::callable_traits::args_t<T>>;

    template <class T>
    using binding_function_t = typename std::function<boost::callable_traits::apply_return_t<pop_back_args<T>, boost::callable_traits::return_type_t<T> >>;

    template <class method_constant, size_t index>
    inline constexpr auto wrap_c_function_callback()
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
            using rs = pop_front<pop_front<back<s>>>;
            using arg_t = at<args_t, std::integral_constant<int, index>>;
            if constexpr (check_is_c_function_callback<arg_t>())
            {
                using mid = binding_function_t<arg_t>;
                using binding_args = wrap<ct::args_t<mid>, list>;
                return _wrap_c_function_callback_impl<method_constant, mid>(binding_args{}, ls{}, rs{});
            }
        }
    }

    template <class method_constant, class integral_constant>
    struct c_function_callback_transform
    {
        using type = c_function_callback_transform;
        using value_type = decltype(wrap_c_function_callback<method_constant, integral_constant::value>());
        static constexpr value_type value = wrap_c_function_callback<method_constant, integral_constant::value>();
    };
}
