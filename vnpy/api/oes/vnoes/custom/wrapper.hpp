#pragma once

#include <autocxxpy/autocxxpy.hpp>
#include <autocxxpy/utils/type_traits.hpp>

#include <pybind11/pybind11.h>

#include <oes_api/oes_api.h>
#include <mds_api/mds_api.h>

#include "../generated_files/module.hpp"

namespace autocxxpy
{
    //////////////////////////////////////////////////////////////////////////
    // special output variable

    //////////////////////////////////////////////////////////////////////////
    // set/get of userInfo.u64
    CREATE_MEMBER_DETECTOR(u64);

    template <class tag, class MemberConstant>
    struct my_getter_helper
    {
        static constexpr auto get()
        {
            constexpr auto member = MemberConstant::value;
            using ty = result_of_member_pointer_t<member>;
            using cls = class_of_member_pointer_t<member>;
            if constexpr (has_member_u64<ty>() && sizeof(ty) == sizeof(uint64_t))
            {
                return [](cls &instance)
                {
                    constexpr auto member = MemberConstant::value;
                    auto &u = instance.*member;
                    return u.u64;
                };
            }
            else
            {
                return default_getter_wrap<tag>(member);
            }
        }
    };

    template <class MemberConstant>
    struct getter_wrap<module_tag, MemberConstant>
    {
        using value_type = decltype(my_getter_helper<module_tag, MemberConstant>::get());
        static constexpr value_type value = my_getter_helper<module_tag, MemberConstant>::get();
    };


    template <class tag, class MemberConstant>
    struct my_setter_helper
    {
        static constexpr auto set()
        {
            constexpr auto member = MemberConstant::value;
            using ty = result_of_member_pointer_t<member>;
            using cls = class_of_member_pointer_t<member>;
            if constexpr (has_member_u64<ty>() && sizeof(ty) == sizeof(uint64_t))
            {
                return [](cls &instance, uint64_t val)
                {
                    constexpr auto member = MemberConstant::value;
                    auto &u = instance.*member;
                    u.u64 = val;
                };
            }
            else
            {
                return default_setter_wrap<tag>(member);
            }
        }
    };

    template <class MemberConstant>
    struct setter_wrap<module_tag, MemberConstant>
    {
        using value_type = decltype(my_setter_helper<module_tag, MemberConstant>::set());
        static constexpr value_type value = my_setter_helper<module_tag, MemberConstant>::set();
    };
    //////////////////////////////////////////////////////////////////////////
}
