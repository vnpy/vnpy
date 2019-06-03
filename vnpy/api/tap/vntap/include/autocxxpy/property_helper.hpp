#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <functional>
#include <mutex>
#include <condition_variable>

#include "config/config.hpp"
#include "base/type.h"

namespace autocxxpy
{
    template <class tag, size_t size>
    struct get_string
    {
        auto &operator()(string_literal<size> &val) const noexcept
        {
            return val;
        }
        auto &operator()(const string_literal<size> &val) const noexcept
        {
            return val;
        }
    };

    template <class tag, size_t size>
    struct set_string
    {
        void operator()(string_literal<size> &val, const char *str)
        {
#ifdef _MSC_VER
            strcpy_s(val, str);
#else
            strcpy(val, str);
#endif
        }
    };


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
    def_property(name, autocxxpy::getter_wrap<module_tag, std::integral_constant<decltype(&cls::member), &cls::member>>::value,\
        autocxxpy::setter_wrap<module_tag, std::integral_constant<decltype(&cls::member), &cls::member>>::value)
