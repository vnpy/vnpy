#pragma once

#include <tuple>
#include <type_traits>

namespace autocxxpy
{
    // since std::invoke_result cann't get result type for class member pointer, we wrote those
    template <auto method>
    struct value_invoke_result {
        template <class class_type, class ret_type, class ... arg_types>
        inline static ret_type get_type(ret_type(class_type::* m)(arg_types ...))
        {
        }
        template <class ret_type, class ... arg_types>
        inline static ret_type get_type(ret_type(*m)(arg_types ...))
        {
        }
        using type = decltype(get_type(method));
    };

    template <auto method>
    using value_invoke_result_t = typename value_invoke_result<method>::type;

    template <auto method>
    struct class_of_member_method {
        template <class class_type, class ret_type, class ... arg_types>
        inline static class_type get_type(ret_type(class_type::* m)(arg_types ...))
        {
        }
        template <class ret_type, class ... arg_types>
        inline static void get_type(ret_type(*m)(arg_types ...))
        {
            // # todo: try to use class template to make gcc happy
            //static_assert(false, "Don't pass a static method or a global function here!");
        }
        using type = decltype(get_type(method));
    };

    template <auto method>
    using value_invoke_result_t = typename value_invoke_result<method>::type;

    template <auto method>
    using class_of_member_method_t = typename class_of_member_method<method>::type;


}