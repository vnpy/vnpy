#pragma once

#include <c2py/callback_wrapper.hpp>

#include "iTapTradeAPI.h"

namespace c2py
{
    // // TapAPIOrderInfoNotice
    // struct FixedTapAPIOrderInfoNotice : ITapTrade::TapAPIOrderInfoNotice
    // {
    //     ITapTrade::TapAPIOrderInfo order_info;
    // 
    //     // copy from original structure
    //     FixedTapAPIOrderInfoNotice(const ITapTrade::TapAPIOrderInfoNotice* info)
    //         : TapAPIOrderInfoNotice(*info), order_info(info->OrderInfo != nullptr ? *info->OrderInfo : ITapTrade::TapAPIOrderInfo{})
    //     {
    //         // fix pointer if there is one
    //         this->OrderInfo = info->OrderInfo != nullptr ? &this->order_info : nullptr;
    //     }
    // 
    //     // copy constructor
    //     FixedTapAPIOrderInfoNotice(const FixedTapAPIOrderInfoNotice& fixed)
    //         : TapAPIOrderInfoNotice(fixed), order_info(fixed.order_info)
    //     {
    //         // fix pointer if there is one
    //         this->OrderInfo = this->OrderInfo != nullptr ? &this->order_info : nullptr;
    //     }
    // };
    // // TapAPIPositionProfit
    // struct FixedTapAPIPositionProfitNotice : ITapTrade::TapAPIPositionProfitNotice
    // {
    //     ITapTrade::TapAPIPositionProfit data;
    // 
    //     // copy from original structure
    //     FixedTapAPIPositionProfitNotice(const ITapTrade::TapAPIPositionProfitNotice* info)
    //         : TapAPIPositionProfitNotice(*info), data(info->Data != nullptr ? *info->Data : ITapTrade::TapAPIPositionProfit{})
    //     {
    //         // fix pointer if there is one
    //         this->Data = info->Data != nullptr ? &this->data : nullptr;
    //     }
    // 
    //     // copy constructor
    //     FixedTapAPIPositionProfitNotice(const FixedTapAPIPositionProfitNotice& fixed)
    //         : TapAPIPositionProfitNotice(fixed), data(fixed.data)
    //     {
    //         // fix pointer if there is one
    //         this->Data = this->Data != nullptr ? &this->data : nullptr;
    //     }
    // };
    // 
    // namespace arg_helper
    // {
    //     inline auto save(const ITapTrade::TapAPIOrderInfoNotice* info)
    //     { // match char []
    //         return FixedTapAPIOrderInfoNotice(info);
    //     }
    // 
    //     template <>
    //     struct loader<ITapTrade::TapAPIOrderInfoNotice>
    //     {
    //         inline FixedTapAPIOrderInfoNotice operator ()(FixedTapAPIOrderInfoNotice& val)
    //         {
    //             return val;
    //         }
    //     };
    // 
    //     inline auto save(const ITapTrade::TapAPIPositionProfitNotice* info)
    //     { // match char []
    //         return FixedTapAPIPositionProfitNotice(info);
    //     }
    // 
    //     template <>
    //     struct loader<ITapTrade::TapAPIPositionProfitNotice>
    //     {
    //         inline FixedTapAPIPositionProfitNotice operator ()(FixedTapAPIPositionProfitNotice& val)
    //         {
    //             return val;
    //         }
    //     };
    // }

    template<>
    struct callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspOrderAction>
    {
        inline static void call(ITapTrade::ITapTradeAPINotify* instance, const char* py_func_name, ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderActionRsp* info)
        {
            ITapTrade::TapAPIOrderInfo orderInfo;
            if (info->OrderInfo != nullptr)
            {
                orderInfo = *info->OrderInfo;
            }
            ITapTrade::TapAPIOrderActionRsp copied_info = *info;
            auto task = [=]() mutable
            {
                if (copied_info.OrderInfo != nullptr)
                {
                    copied_info.OrderInfo = &orderInfo;  // ensure pointer is pointer to the correct address(address changes after constructed lambda)
                }
                try
                {
                    return default_callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRspOrderAction>::sync(instance, py_func_name, sessionID, errorCode, &copied_info);
                }
                catch (const async_dispatch_exception& e)
                {
                    async_callback_exception_handler::handle_excepiton(e);
                }

            };
            dispatcher::instance().add(std::move(task));
        }
    };
    
    template<>
    struct callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnOrder>
    {
        inline static void call(ITapTrade::ITapTradeAPINotify* instance, const char* py_func_name, const ITapTrade::TapAPIOrderInfoNotice* info)
        {
            ITapTrade::TapAPIOrderInfo orderInfo;
            if (info->OrderInfo != nullptr)
            {
                orderInfo = *info->OrderInfo;
            }
            ITapTrade::TapAPIOrderInfoNotice copied_info = *info;
            auto task = [=]() mutable
            {
                if (copied_info.OrderInfo != nullptr)
                {
                    copied_info.OrderInfo = &orderInfo;  // ensure pointer is pointer to the correct address(address changes after constructed lambda)
                }
                try
                {
                    return default_callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnOrder>::sync(instance, py_func_name, &copied_info);
                }
                catch (const async_dispatch_exception& e)
                {
                    async_callback_exception_handler::handle_excepiton(e);
                }
            };
            dispatcher::instance().add(std::move(task));
        }
    };

    template<>
    struct callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnPositionProfit>
    {
        inline static void call(ITapTrade::ITapTradeAPINotify* instance, const char* py_func_name, const ITapTrade::TapAPIPositionProfitNotice* info)
        {

            ITapTrade::TapAPIPositionProfit profit;
            if (info->Data != nullptr)
            {
                profit = *info->Data;
            }
            ITapTrade::TapAPIPositionProfitNotice copied_info = *info;
            auto task = [=]() mutable
            {
                if (copied_info.Data != nullptr)
                {
                    copied_info.Data = &profit;  // ensure pointer is pointer to the correct address(address changes after constructed lambda)
                }
                try
                {
                    return default_callback_wrapper<&ITapTrade::ITapTradeAPINotify::OnRtnPositionProfit>::sync(instance, py_func_name, &copied_info);
                }
                catch (const async_dispatch_exception& e)
                {
                    async_callback_exception_handler::handle_excepiton(e);
                }
            };
            dispatcher::instance().add(std::move(task));
        }
    };
}
