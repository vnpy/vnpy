#pragma once

#include <boost/callable_traits.hpp>
#include "../brigand.hpp"

namespace autocxxpy
{
    template <class MethodConstant, class ... Args>
    inline constexpr auto wrap_no_gil_impl(brigand::list<Args...>)
    {
        return [](Args ... args)
        {
            //constexpr auto method = T::value;
            printf("no gil!\n");
#ifdef PYBIND11_OVERLOAD
            printf("free gil\n");
            pybind11::gil_scoped_release gil;
#endif
            constexpr auto method = MethodConstant::value;
            return method(args ...);
        };
    }

    template <class MethodConstant>
    inline constexpr auto wrap_no_gil()
    {
        using namespace brigand;
        namespace ct = boost::callable_traits;

        using func_t = ct::function_type_t<decltype(MethodConstant::value)>;
        using args_t = wrap<ct::args_t<func_t>, list>;
        return wrap_no_gil_impl<MethodConstant>(args_t{});
    }

    template <class T>
    struct no_gil_transform
    {
        using type = no_gil_transform;
        using value_type = decltype(wrap_no_gil<T>());
        static constexpr value_type value = wrap_no_gil<T>();
    };
}
