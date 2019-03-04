#pragma once

#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>

#include "config/config.hpp"

namespace autocxxpy
{
    template <class class_type, class value_type>
    inline constexpr auto default_getter_wrap(value_type class_type::*member)
    { // match normal case
        return [member](const class_type &instance)->const value_type & {
            return instance.*member;
        };
    }

    template <class class_type, class value_type>
    inline constexpr auto default_setter_wrap(value_type class_type::*member)
    { // match normal case
        return [member](class_type &instance, const value_type &value) {
            instance.*member = value;
        };
    }

    // specialization for const setter
    template <class class_type, class value_type>
    inline constexpr auto default_setter_wrap(const value_type class_type::*member)
    { // match const
        return nullptr;
    }

    // specialization for any []
    template <class element_t, size_t size>
    using array_literal = element_t[size];

    template <class class_type, class element_t, size_t size>
    inline constexpr auto default_getter_wrap(array_literal<element_t, size> class_type::*member)
    { // match get any []
        return [member](const class_type &instance) {
            return std::vector<element_t>(instance.*member, instance.*member + size);
        };
    }

    template <class class_type, class element_t, size_t size>
    inline constexpr auto default_setter_wrap(array_literal<element_t, size> class_type::*member)
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
    template <class class_type, class element_t, size_t size>
    inline constexpr auto default_getter_wrap(array_literal<element_t *, size> class_type::*member)
    { // match get (any *)[]
        return [member](const class_type &instance) {
            std::vector<element_t *> arr;
            for (auto &v : instance.*member)
            {
                arr.push_back(v);
            }
            return arr;
        };
    }

    // specialization for char[]
    template <size_t size>
    using string_literal = array_literal<char, size>;

    template <class class_type, size_t size>
    inline constexpr auto default_getter_wrap(string_literal<size> class_type::*member)
    { // match get char []
        return [member](const class_type &instance) {
            return instance.*member;
        };
    }

    template <class class_type, size_t size>
    inline constexpr auto default_setter_wrap(string_literal<size> class_type::*member)
    { // match set char []
        return [member](class_type &instance, const std::string_view &value) {
#ifdef _MSC_VER
            strcpy_s(instance.*member, value.data());
#else
            strcpy(instance.*member, value.data());
#endif
        };
    }

    template <class tag, class MemberConstant>
    struct getter_wrap
    {
        using value_type = decltype(default_getter_wrap(MemberConstant::value));
        static constexpr value_type value = default_getter_wrap(MemberConstant::value);
    };


    template <class tag, class MemberConstant>
    struct setter_wrap
    {
        using value_type = decltype(default_setter_wrap(MemberConstant::value));
        static constexpr value_type value = default_setter_wrap(MemberConstant::value);
    };
}
#define AUTOCXXPY_DEF_PROPERTY(cls, name, member) \
    def_property(name, autocxxpy::getter_wrap<module_tag, std::integral_constant<decltype(&cls::member), &cls::member>>::value,\
        autocxxpy::setter_wrap<module_tag, std::integral_constant<decltype(&cls::member), &cls::member>>::value)
