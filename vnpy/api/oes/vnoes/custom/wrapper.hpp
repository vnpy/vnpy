#pragma once

#include <autocxxpy/autocxxpy.hpp>
#include <autocxxpy/utils/type_traits.hpp>

#include <pybind11/pybind11.h>

#include <oes_api/oes_api.h>
#include <mds_api/mds_api.h>

#include "../generated_files/module.hpp"

namespace autocxxpy
{
    //template <>
    //struct calling_wrapper<&::OesApi_WaitReportMsg>
    //{
    //    static constexpr auto value = [](
    //        OesApiSessionInfoT *pRptChannel,
    //        int32 timeoutMs,
    //        F_OESAPI_ON_RPT_MSG_T pRptMsgCallback,
    //        void *pCallbackParams
    //        )
    //    {
    //        return ::OesApi_WaitReportMsg(pRptChannel, timeoutMs, pRptMsgCallback, pCallbackParams);
    //    };
    //};

    template <>
    struct calling_wrapper<&::OesApi_WaitOnChannelGroup>
    {
        static constexpr auto value = [](
            OesApiChannelGroupT *pChannelGroup,
            int32 timeoutMs,
            F_OESAPI_ON_RPT_MSG_T pOnMsgCallback,
            void *pCallbackParams
            )
        {
            return ::OesApi_WaitOnChannelGroup(pChannelGroup, timeoutMs, pOnMsgCallback, pCallbackParams, nullptr);
        };
    };

    template <>
    struct calling_wrapper<&::MdsApi_WaitOnTcpChannelGroup>
    {
        static constexpr auto value = [](
            MdsApiChannelGroupT *pChannelGroup,
            int32 timeoutMs,
            F_MDSAPI_ONMSG_T pOnMsgCallback,
            void *pCallbackParams
            )
        {
            return ::MdsApi_WaitOnTcpChannelGroup(pChannelGroup, timeoutMs, pOnMsgCallback, pCallbackParams, nullptr);
        };
    };

    template <>
    struct calling_wrapper<&::MdsApi_WaitOnTcpChannelGroupCompressible>
    {
        static constexpr auto value = [](
            MdsApiChannelGroupT *pChannelGroup,
            int32 timeoutMs,
            F_MDSAPI_ONMSG_T pOnMsgCallback,
            void *pCallbackParams
            )
        {
            return ::MdsApi_WaitOnTcpChannelGroupCompressible(pChannelGroup, timeoutMs, pOnMsgCallback, pCallbackParams, nullptr);
        };
    };

    template <>
    struct calling_wrapper<&::MdsApi_WaitOnUdpChannelGroup>
    {
        static constexpr auto value = [](
            MdsApiChannelGroupT *pChannelGroup,
            int32 timeoutMs,
            F_MDSAPI_ONMSG_T pOnMsgCallback,
            void *pCallbackParams
            )
        {
            return ::MdsApi_WaitOnUdpChannelGroup(pChannelGroup, timeoutMs, pOnMsgCallback, pCallbackParams, nullptr);
        };
    };

    template <class T>
    struct ssss
    {
        using type = int;
    };

    CREATE_MEMBER_DETECTOR(u64);


    template <class MemberConstant>
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
                return default_getter_wrap(member);
            }
        }
    };

    template <class MemberConstant>
    struct getter_wrap<module_tag, MemberConstant>
    {
        using value_type = decltype(my_getter_helper<MemberConstant>::get());
        static constexpr value_type value = my_getter_helper< MemberConstant>::get();
    };


    template <class MemberConstant>
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
                return default_setter_wrap(member);
            }
        }
    };

    template <class MemberConstant>
    struct setter_wrap<module_tag, MemberConstant>
    {
        using value_type = decltype(my_setter_helper<MemberConstant>::set());
        static constexpr value_type value = my_setter_helper< MemberConstant>::set();
    };



    //template <>
    //struct post_register_class<tag_vnoes, MdsMktDataSnapshotT>
    //{
    //    template <class T>
    //    static constexpr void post_register(T &c)
    //    {
    //        c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "l2Stock", l2Stock);
    //        c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "l2StockIncremental", l2StockIncremental);
    //        c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "l2BestOrders", l2BestOrders);
    //        c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "l2BestOrdersIncremental", l2BestOrdersIncremental);
    //        c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "stock", stock);
    //        c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "option", option);
    //        c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "index", index);
    //        c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "l2VirtualAuctionPrice", l2VirtualAuctionPrice);
    //        c.AUTOCXXPY_DEF_PROPERTY(MdsMktDataSnapshotT, "l2MarketOverview", l2MarketOverview);
    //    }
    //};

}
