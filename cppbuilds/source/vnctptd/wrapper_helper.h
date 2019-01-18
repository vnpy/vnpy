#pragma once

#include <tuple>
#include <type_traits>

#include "dispatcher.h"

/*
example to change the calling method:

// switch async/direct
template <>
struct callback_type_of<static_cast<int(A::*)()>(&A::func2)>
{
    const static callback_type value = callback_type::Direct;
};


// rewrite the whole function
template<>
struct callback_wrapper<static_cast<int(A::*)(int)>(&A::func2)>
{
    inline static void call(A *instance, float)
    {
        constexpr auto method = static_cast<int(A::*)(int)>(&A::func2);
        default_callback_wrapper<method>::call(instance, 1);
        (instance->*method)(1);
        std::cout << "wrapped!" << std::endl;
    }
};

*/

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
    using type = decltype(get_type(method));
};

template <auto method>
using value_invoke_result_t = typename value_invoke_result<method>::type;

template <auto method>
using class_of_member_method_t = typename class_of_member_method<method>::type;


enum class callback_type
{
    Direct = 0,
    Async = 1
};


template <auto method>
struct default_callback_type_of
{
    const static callback_type value = callback_type::Async;
};
template <auto method>
struct callback_type_of : default_callback_type_of<method> {};

template <auto method>
constexpr callback_type callback_type_of_v = callback_type_of<method>::value;


template <auto method>
struct default_callback_wrapper
{
    using ret_type = value_invoke_result_t<method>;
    using class_type = class_of_member_method_t<method>;
public:
    template <class ... arg_types>
    inline static ret_type call(class_type *instance, const char *py_func_name, arg_types ... args)
    {
        if constexpr (callback_type_of_v<method> == callback_type::Direct)
        {
            return sync(instance, args ...);
        }
        else
        {
            async(instance, py_func_name, args ...);
            static_assert(std::is_void_v<ret_type> || std::is_default_constructible_v<ret_type>,
            "type is not default_constructiblev, you should use sync call instead.");
            return ret_type(); // if ret_type() is not constructable, this will make compiler unhappy
        }
    }

    template <class ... arg_types>
    inline static void async(class_type *instance, const char *py_func_name, arg_types ... args)
    {
        return async_impl(instance, py_func_name, std::index_sequence_for<arg_types ...>{}, args ...);
    }

    template <class ... arg_types>
    inline static ret_type sync(class_type *instance, const char * py_func_name, arg_types ... args)
    {
// if this code is under test environment, we don't need pybind11
// since header of pybind11 use #pragma once, no macros is defined, we use a public macro to check if pybind11 is included or not
#ifdef PYBIND11_OVERLOAD_NAME
        pybind11::gil_scoped_acquire gil;
        pybind11::function overload = pybind11::get_overload(static_cast<const class_type *>(instance), py_func_name);
        if (overload) {
            auto o = overload(args ...);
            if (pybind11::detail::cast_is_temporary_value_reference<ret_type>::value) {
                static pybind11::detail::overload_caster_t<ret_type> caster;
                return pybind11::detail::cast_ref<ret_type>(std::move(o), caster);
            }
            else return pybind11::detail::cast_safe<ret_type>(std::move(o));
        }
#endif
        return (instance->*method)(args ...);
    }
private:
    template <class T>
    inline static T &deref(T *val)
    { // match pointer
        return *val;
    }

    template <class T>
    inline static T &deref(const T *val)
    { // match const pointer
        return const_cast<T&>(*val);
    }

    template <class T>
    inline static T &deref(const T &val)
    { // match everything else : just use original type
        return const_cast<T&>(val);
    }


    template <class to_type>
    struct resolve
    { // match default(everyting besides pointer)
        template <class src_type>
        inline to_type operator ()(src_type &val)
        {
            return val;
        }
    };

    template <class to_type>
    struct resolve<to_type *>
    { // match pointer
        template <class src_type>
        inline to_type *operator ()(src_type &val)
        { // val to poiner
            return const_cast<to_type *>(&val);
        }

        template <class src_type>
        inline to_type *operator ()(src_type *val)
        { // pointer to pointer
            return val;
        }
    };

    template<size_t i, class ... types>
    struct get_type
    {};
    template<class first_type, class ... types>
    struct get_type<0, first_type, types ...>
    {
        using type = first_type;
    };
    template<size_t i, class first_type, class ... types>
    struct get_type<i, first_type, types ...>
    {
        using type = typename get_type<i - 1, types ...>::type;
    };

    template<size_t i, class ... types>
    using get_type_t = typename get_type<i, types ...>::type;

    template <class ... arg_types, size_t ... idx>
    inline static void async_impl(class_type *instance, const char *py_func_name, std::index_sequence<idx ...>, arg_types ... args)
    {
        // wrap for ctp like function calls:
        // all the pointer might be unavailable after this call, so copy its value into a tuple
        auto arg_tuple = std::make_tuple(deref(args) ...);
        auto task = [instance, py_func_name, arg_tuple = std::move(arg_tuple)]()
        {
            // resolve all value:
            // if it was originally a pointer, then use pointer type.
            // if it was originally a value, just keep a reference to that value.
            sync<arg_types ...>(
                instance, py_func_name,
                resolve<get_type_t<idx, arg_types ...>>{}
            (std::get<idx>(arg_tuple)) ...
                );
        };
        dispatcher::instance().add(std::move(task));
    }

};
template <auto method>
struct callback_wrapper : default_callback_wrapper<method> {};

