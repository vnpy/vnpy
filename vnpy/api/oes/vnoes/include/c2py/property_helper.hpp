#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <functional>
#include <mutex>
#include <condition_variable>

#include <locale>
#include <codecvt>

#include "config/config.hpp"
#include "base/type.h"

namespace c2py
{

#ifdef AUTOCXXPY_ENCODING_UTF8
    template <class tag, size_t size>
    struct get_string
    {
        inline constexpr auto& operator()(string_literal<size>& val) const noexcept
        {
            return val;
        }
        inline constexpr auto& operator()(const string_literal<size>& val) const noexcept
        {
            return val;
        }
    };
    template <class tag, size_t size>
    struct set_string
    {
        inline void operator()(string_literal<size>& val, const char* str)
        {
#ifdef _MSC_VER
            strcpy_s(val, str);
#else
            strcpy(val, str);
#endif
        }
    };
#else
    // converts encoding into UTF-8
    inline std::string to_utf8(const std::string& input)
    {

#ifdef _MSC_VER
        const char* locale_name = AUTOCXXPY_ENCODING_CUSTOM_WINDOWS; // usually ".936"
#else
        const char* locale_name = AUTOCXXPY_ENCODING_CUSTOM_LINUX; // usually "zh_CN.GB18030"
#endif
        const static std::locale loc(locale_name);
        auto& code_convertor = std::use_facet<
            std::codecvt<wchar_t, char, std::mbstate_t>
        >(loc);

        std::wstring wstr(input.size(), '\0');
        wchar_t* wstr_end = nullptr;
        const char* input_end = nullptr;
        std::mbstate_t state = {};
        code_convertor.in(state,
                &input[0], &input[input.size()], input_end,
                &wstr[0], &wstr[wstr.size()], wstr_end);
        std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
        return cutf8.to_bytes(std::wstring(wstr.data(), wstr_end));
    }
    template <class tag, size_t size>
    struct get_string
    {
        inline constexpr auto operator()(string_literal<size>& val) const noexcept
        {
            return to_utf8(val);
        }
        inline constexpr auto operator()(const string_literal<size>& val) const noexcept
        {
            return to_utf8(val);
        }
    };

    template <class tag, size_t size>
    struct set_string
    {
        inline void operator()(string_literal<size> &val, const char *str)
        {
#ifdef _MSC_VER
            strcpy_s(val, to_utf8(str).c_str());
#else
            strcpy(val, to_utf8(str).c_str());
#endif
        }
    };
#endif


    template <class tag, class class_type, class value_type>
    inline constexpr auto default_getter_wrap(value_type class_type::*member)
    { // match normal case
        return [member](class_type &instance)->const value_type & {
            return instance.*member;
        };
    }

    template <class tag, class class_type, class value_type>
    inline constexpr auto default_setter_wrap(value_type class_type::*member)
    { // match normal case
        return [member](class_type &instance, const value_type &value) {
            instance.*member = value;
        };
    }

    // specialization for const setter
    template <class tag, class class_type, class value_type>
    inline constexpr auto default_setter_wrap(const value_type class_type::*member)
    { // match const
        return nullptr;
    }

    // specialization for any []
    template <class tag, class class_type, class element_t, size_t size>
    inline constexpr auto default_getter_wrap(literal_array<element_t, size> class_type::*member)
    { // match get any []
        return [member](class_type &instance) {
            auto es = std::vector<const element_t *>(size);
            for (size_t i = 0; i < size ; i++)
            {
                es[i] = instance.*member + i;
            }
            return std::move(es);
        };
    }

    template <class tag, class class_type, class element_t, size_t size>
    inline constexpr auto default_setter_wrap(literal_array<element_t, size> class_type::*member)
    { // match set any []
        return [member](class_type &instance, const std::vector<element_t> &value) {
            if (value.size() >= size)
            {
                auto s = std::string("Array too large, maximum size : ") + std::to_string(size) + " your size: " + std::to_string(value.size());
                throw std::runtime_error(s);
            }
            for (int i = 0; i < value.size(); i++)
            {
                (instance.*member)[i] = value.at(i);
            }
        };
    }

    // specialization for any *[]
    template <class tag, class class_type, class element_t, size_t size>
    inline constexpr auto default_getter_wrap(literal_array<element_t *, size> class_type::*member)
    { // match get (any *)[]
        return [member](class_type &instance) {
            std::vector<element_t *> arr;
            for (auto &v : instance.*member)
            {
                arr.push_back(v);
            }
            return arr;
        };
    }

    // specialization for char[]
    template <class tag, class class_type, size_t size>
    inline constexpr auto default_getter_wrap(string_literal<size> class_type::*member)
    { // match get char []
        return [member](class_type &instance) {
            return get_string<tag, size>{}(instance.*member);
        };
    }

    template <class tag, class class_type, size_t size>
    inline constexpr auto default_setter_wrap(string_literal<size> class_type::*member)
    { // match set char []
        return [member](class_type &instance, const std::string_view &value) {
            return set_string<tag, size>{}(instance.*member, value.data());
        };
    }

    template <class tag, class MemberConstant>
    struct getter_wrap
    {
        using value_type = decltype(default_getter_wrap<tag>(MemberConstant::value));
        static constexpr value_type value = default_getter_wrap<tag>(MemberConstant::value);
    };


    template <class tag, class MemberConstant>
    struct setter_wrap
    {
        using value_type = decltype(default_setter_wrap<tag>(MemberConstant::value));
        static constexpr value_type value = default_setter_wrap<tag>(MemberConstant::value);
    };
}
#define AUTOCXXPY_DEF_PROPERTY(module_tag, cls, name, member) \
    def_property(name, c2py::getter_wrap<module_tag, std::integral_constant<decltype(&cls::member), &cls::member>>::value,\
        c2py::setter_wrap<module_tag, std::integral_constant<decltype(&cls::member), &cls::member>>::value)
