#pragma once

#include <boost/callable_traits.hpp>

#include "../brigand.hpp"

namespace autocxxpy
{

    template <class T>
    struct is_c_function_pointer : std::false_type {};

    template <class Ret, class ... Args>
    struct is_c_function_pointer<Ret(*)(Args...)> :std::true_type {};

    template <class MethodConstant, class Func, class ... CArgs, class ... Ls, class ... Rs>
    inline constexpr auto _wrap_cfunc_ptr_impl(brigand::list<CArgs...>, brigand::list<Ls...>, brigand::list<Rs...>)
    {
        return [](Ls ...ls, Func &func, Rs ... rs)
        {
            constexpr auto wrapped_callback =
                [](CArgs ... largs, void *pf)
            {
                Func *binding_function = (Func *)pf;
#ifdef PYBIND11_OVERLOAD
                pybind11::gil_scoped_acquire gil;
#endif
                return (*binding_function)(largs...);
            };
            constexpr auto method = MethodConstant::value;
            return method(
                ls...,
                std::move(wrapped_callback),
                (void *)new Func(func),
                rs...
            );
        };
    }


    template <class T>
    using pop_back_args = typename brigand::pop_back<boost::callable_traits::args_t<T>>;

    template <class T>
    using binding_function_t = typename std::function<boost::callable_traits::apply_return_t<pop_back_args<T>, boost::callable_traits::return_type_t<T> >>;

    template <class MethodConstant, class args_t, class args_from_cfp>
    inline constexpr auto _wrap_cfunc_ptr_nocheck()
    {
        using namespace brigand;
        namespace ct = boost::callable_traits;

        using cfp_t = front<args_from_cfp>;
        using cfp_args_t = pop_back<wrap<ct::args_t<cfp_t>, list>>; // args without last void *
        using cfp_append_arg = front<pop_front<args_from_cfp>>;
        if constexpr (std::is_same_v <cfp_append_arg, void *>)
        {
            constexpr int cfp_idx = index_of<args_t, cfp_t>::value;

            using ls = front<split_at<args_t, integral_constant<int, cfp_idx>>>;
            using rs = pop_front<args_from_cfp, integral_constant<int, 2>>;

            using mid = binding_function_t<cfp_t>;
            return _wrap_cfunc_ptr_impl <MethodConstant, mid>(cfp_args_t{}, ls{}, rs{});
        }
        else
        {
            constexpr auto method = MethodConstant::value;
            return method;
        }
    }

    template <class MethodConstant>
    inline constexpr auto wrap_c_function_ptr()
    {
        using namespace brigand;
        namespace ct = boost::callable_traits;

        constexpr auto method = MethodConstant::value;
        using func_t = ct::function_type_t<decltype(method)>;
        using args_t = wrap<ct::args_t<func_t>, list>;

        constexpr bool has_c_function_pointer = found<args_t, is_c_function_pointer<_1>>::value;
        if constexpr (has_c_function_pointer)
        {
            using args_from_cfp = find<args_t, is_c_function_pointer<_1>>;
            constexpr int nargs_left = size<args_from_cfp>::value;
            if constexpr (nargs_left >= 2)
            {
                return _wrap_cfunc_ptr_nocheck<MethodConstant, args_t, args_from_cfp>();
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
    struct c_function_pointer_to_std_function_transform
    {
        using type = c_function_pointer_to_std_function_transform;
        using value_type = decltype(wrap_c_function_ptr<T>());
        static constexpr value_type value = wrap_c_function_ptr<T>();
    };
}
