#pragma once

#include <tuple>
#include <type_traits>
#include <optional>
#include <iostream>

#include "./brigand.hpp"

#include "./utils/functional.hpp"
#include "./dispatcher.hpp"
#include "./config/config.hpp"
#include "./wrappers/string_array.hpp"

namespace c2py
{

    /*
    example to change the callback method:

    @startcode cpp
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
        inline static void call(A *instance, const char *py_func_name, float)
        {
            constexpr auto method = static_cast<int(A::*)(int)>(&A::func2);
            default_callback_wrapper<method>::call(instance, 1);
            (instance->*method)(1);
            std::cout << "wrapped!" << std::endl;
        }
    };
    @endcode

    example to change the calling method:

    @startcode pp
    template <>
    struct calling_wrapper<&A::func2>
    {
        static constexpr auto value = [](){return 1;};
    };
    @endcode

    */
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

#ifdef AUTOCXXPY_INCLUDED_PYBIND11
    template <class ret_type>
    struct pybind11_static_caster {
        using type = pybind11::detail::overload_caster_t<ret_type>;
        static inline type &get_caster()
        {
            static type _caster;
            return _caster;
        }
    };

    struct async_dispatch_exception : public std::exception
    {
        async_dispatch_exception(const char *what, const pybind11::object &instance, std::string function_name)
            : _what(what), instance(instance), function_name(function_name)
        {}
		std::string _what;
        pybind11::object instance;
        std::string function_name;

        // mutable version of what() for pybind11 to make it happy
        inline const char* what_mutable() noexcept
        {
            return what();
        }

		virtual char const* what() const noexcept override
		{
			return _what.c_str();
		}
	};

    struct async_callback_exception_handler
    {
        using handler_type = std::function<bool(const async_dispatch_exception&)>;

        inline static void handle_excepiton(const async_dispatch_exception&e)
        {
            if (get_custom_handler())
            {
                try
                {
                    get_custom_handler()(e);
                }
                catch (pybind11::error_already_set & e2)
                {
                   std::cerr << "error while calling custom async callback exception handler:" << std::endl;
                    std::cerr << e2.what() << std::endl;
                    std::cerr << "while handling following exception:" << std::endl;
                    std::cerr << e.what() << std::endl;
                }
            }
            else
            {
                std::cerr << e.what() << std::endl;
                std::cerr << "custom async callback exception handler not set." << std::endl;
                std::cerr << "Call set_async_callback_exception_handler() to set it. " << std::endl;
            }
        }

        inline static void set_handler(const handler_type& handler)
        {
            get_custom_handler() = handler;
        }
    private:
        inline static handler_type &get_custom_handler()
        {
            static handler_type _handler;
            return _handler;
        }

    };
#endif

    namespace arg_helper
    {
        //////////////////////////////////////////////////////////////////////////
        // stores
        //////////////////////////////////////////////////////////////////////////

        // # todo: char8, char16, char32, wchar_t, etc...
        // # todo: shall i copy only const type, treating non-const type as output pointer?
        inline std::optional<std::string> save(const char* val)
        { // match const char *
            if (nullptr == val) AUTOCXXPY_UNLIKELY
                return std::nullopt;  // maybe empty string is also a choice?
            return std::string(val);
        }
        inline std::optional<std::string> save(char* val)
        { // match char *
            if (nullptr == val) AUTOCXXPY_UNLIKELY
                return std::nullopt;  // maybe empty string is also a choice?
            return std::string(val);
        }
        template<size_t size>
        inline auto save(const string_array<size> val)
        { // match const char []
            return std::string(val);
        }
        template<size_t size>
        inline auto save(string_array<size> val)
        { // match char []
            return std::string(val);
        }

        template <class T>
        inline std::optional<T> save(T * val)
        { // match pointer
            if (nullptr == val) AUTOCXXPY_UNLIKELY
            {
                return std::nullopt;
            }
            return *val;
        }

        template <class T>
        inline std::optional<T> save(const T * val)
        { // match const pointer
            if (nullptr == val) AUTOCXXPY_UNLIKELY
            {
                return std::nullopt;
            }
            return *val;
        }

        template <class T>
        inline T save(const T & val)
        { // match everything else : just use original type
            return val;
        }


        //////////////////////////////////////////////////////////////////////////
        // loads
        //////////////////////////////////////////////////////////////////////////

        template <class to_type>
        struct loader
        { // match default(everyting besides pointer)
            template <class src_type>
            inline to_type operator ()(src_type& val)
            {
                return val;
            }
        };

        template <size_t size>
        struct loader<const string_array<size>>
        { // match const char []
            using to_type = const char*;
            inline to_type operator ()(const std::string& val)
            {
                return const_cast<char*>(val.data());
            }
        };

        template <size_t size>
        struct loader<string_array<size>>
        { // match char []
            using to_type = char*;
            inline to_type operator ()(const std::string& val)
            {
                return const_cast<char*>(val.data());
            }
        };

        template <>
        struct loader<const char*>
        { // match const char *
            using to_type = const char*;
            inline to_type operator ()(const std::optional<std::string>& val)
            {
                if (val) AUTOCXXPY_LIKELY
                    return const_cast<char*>(val->data());
                return nullptr;
            }
        };

        template <>
        struct loader<char*>
        { // match char *
            using to_type = char*;
            inline to_type operator ()(const std::optional<std::string>& val)
            {
                if (val) AUTOCXXPY_LIKELY
                    return const_cast<char*>(val->data());
                return nullptr;
            }
        };

        template <class to_type>
        struct loader<to_type*>
        { // match pointer
            template <class src_type>
            inline to_type* operator ()(const std::optional<src_type>& val)
            { // val to poiner
                if (val) AUTOCXXPY_LIKELY
                    return const_cast<to_type*>(&(*val));
                return nullptr;
            }
        };

    };


    template <auto method>
    struct default_callback_wrapper
    {
        using ret_type = value_invoke_result_t<method>;
        using class_type = class_of_member_method_t<method>;
    public:
        template <class ... arg_types>
        inline static ret_type call(class_type* instance, const char* py_func_name, arg_types ... args)
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
        inline static void async(class_type* instance, const char* py_func_name, arg_types ... args)
        {
            return async_impl(instance, py_func_name, std::index_sequence_for<arg_types ...>{}, args ...);
        }

        template <class ... arg_types>
        inline static ret_type sync(class_type * instance, const char* py_func_name, arg_types ... args)
        {
            // if this code is under test environment, we don't need pybind11
            // since header of pybind11 use #pragma once, no macros is defined, we use a public macro to check if pybind11 is included or not
#ifdef PYBIND11_OVERLOAD_NAME
            pybind11::gil_scoped_acquire gil;
            pybind11::function overload = pybind11::get_overload(static_cast<const class_type*>(instance), py_func_name);
            if (overload) AUTOCXXPY_LIKELY{
                try
                {
                    auto result = overload(args ...);
                    if (pybind11::detail::cast_is_temporary_value_reference<ret_type>::value)
                    {
                        auto& caster = pybind11_static_caster<ret_type>::get_caster();
                        return pybind11::detail::cast_ref<ret_type>(std::move(result), caster);
                    }
                    else 
                    {
                        return pybind11::detail::cast_safe<ret_type>(std::move(result));
                    }
                }
                catch (const pybind11::error_already_set & e)
                {
                    // todo: option to not to throw when sync is called directly
                    throw async_dispatch_exception(e.what(), pybind11::cast(instance), py_func_name);
                }
            }
#endif
            return (instance->*method)(args ...);
        }
    private:
        template <class ... arg_types, size_t ... idx>
        inline static void async_impl(class_type * instance, const char* py_func_name, std::index_sequence<idx ...>, arg_types ... args)
        {
            // wrap for ctp like function calls:
            // all the pointer might be unavailable after this call, so copy its value into a tuple
            auto arg_tuple = std::make_tuple(arg_helper::save(args) ...);
            auto task = [instance, py_func_name, arg_tuple = std::move(arg_tuple)]()
            {
#ifdef AUTOCXXPY_INCLUDED_PYBIND11
                try
                {
#endif
                    // resolve all value:
                    // if it was originally a pointer, then use pointer type.
                    // if it was originally a value, just keep a reference to that value.
                    sync<arg_types ...>(
                        instance, py_func_name,
                        arg_helper::loader<brigand::at<brigand::list<arg_types ...>, brigand::integral_constant<int, idx> > >{}
                    (std::get<idx>(arg_tuple)) ...
                        );
#ifdef AUTOCXXPY_INCLUDED_PYBIND11
                }
                catch (const async_dispatch_exception &e)
                {
                    async_callback_exception_handler::handle_excepiton(e);
                }
#endif
            };
            dispatcher::instance().add(std::move(task));
        }
    };

    template <auto method>
    struct callback_wrapper : default_callback_wrapper<method>
    {};
}
