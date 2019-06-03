#pragma once

#include <autocxxpy/callback_wrapper.hpp>

#include "iTapTradeAPI.h"

namespace autocxxpy
{
    // this method seems complicated and needs more code. Useful for code generator but not for human.
    //using namespace ITapTrade;
    //namespace arg_helper
    //{
    //    struct FixedTapAPIOrderInfoNotice : TapAPIOrderInfoNotice
    //    {
    //        TapAPIOrderInfo order_info;

    //        // copy from original structure
    //        FixedTapAPIOrderInfoNotice(const TapAPIOrderInfoNotice* info)
    //            : TapAPIOrderInfoNotice(*info), order_info(*info->OrderInfo)
    //        {
    //            this->OrderInfo = &this->order_info;
    //        }

    //        // copy constructor
    //        FixedTapAPIOrderInfoNotice(const FixedTapAPIOrderInfoNotice& fixed)
    //            : TapAPIOrderInfoNotice(fixed), order_info(fixed.order_info)
    //        {
    //            this->OrderInfo = &this->order_info;
    //        }
    //    };
    //    inline auto save(const TapAPIOrderInfoNotice* info)
    //    { // match char []
    //        return FixedTapAPIOrderInfoNotice(info);
    //    }

    //    template <>
    //    struct loader<TapAPIOrderInfoNotice>
    //    {
    //        inline FixedTapAPIOrderInfoNotice operator ()(FixedTapAPIOrderInfoNotice& val)
    //        {
    //            return val;
    //        }
    //    };
    //}

    template<>
    struct callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspOrderAction>
    {
        inline static void call(ITapTrade::ITapTradeAPINotify* instance, const char*py_func_name, ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderActionRsp* info)
        {
            ITapTrade::TapAPIOrderInfo orderInfo = *info->OrderInfo;
            ITapTrade::TapAPIOrderActionRsp copied_info = *info;
            auto task = [=]() mutable
            {
                copied_info.OrderInfo = &orderInfo;  // ensure pointer is pointer to the correct address(address changes after constructed lambda)
                return default_callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspOrderAction>::sync(instance, py_func_name, sessionID, errorCode, &copied_info);
            };
            dispatcher::instance().add(std::move(task));
        }
    };
    template<>
    struct callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnOrder>
    {
        inline static void call(ITapTrade::ITapTradeAPINotify* instance, const char*py_func_name, const ITapTrade::TapAPIOrderInfoNotice* info)
        {
            ITapTrade::TapAPIOrderInfo orderInfo = *info->OrderInfo;
            ITapTrade::TapAPIOrderInfoNotice copied_info = *info;
            auto task = [=]() mutable
            {
                copied_info.OrderInfo = &orderInfo;  // ensure pointer is pointer to the correct address(address changes after constructed lambda)
                return default_callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnOrder>::sync(instance, py_func_name, &copied_info);
            };
            dispatcher::instance().add(std::move(task));
        }
    };

    template<>
    struct callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnPositionProfit>
    {
        inline static void call(ITapTrade::ITapTradeAPINotify* instance, const char*py_func_name, const ITapTrade::TapAPIPositionProfitNotice* info)
        {
            ITapTrade::TapAPIPositionProfit profit = *info->Data;
            ITapTrade::TapAPIPositionProfitNotice copied_info = *info;
            auto task = [=]() mutable
            {
                copied_info.Data = &profit;  // ensure pointer is pointer to the correct address(address changes after constructed lambda)
                return default_callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnPositionProfit>::sync(instance, py_func_name, &copied_info);
            };
            dispatcher::instance().add(std::move(task));
        }
    };
}
