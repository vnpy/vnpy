#pragma once

#include <vector>

#include "../api/ThostFtdcMdApi.h"
#include "../wrapper_helper.hpp"

namespace autocxxpy
{

    template <auto method>
    struct spi_vector_wrapper
    {
        static constexpr auto value = [](CThostFtdcMdApi *instance, std::vector<char *> &arg)
        {
            return (instance->*method)(&arg.at(0), static_cast<int>(arg.size()));
        };
    };

#define DEF_SPI_VECTOR_CALLING_WRAPPER(method) \
    template <>\
    struct calling_wrapper<method> \
        : spi_vector_wrapper<method>\
    {};

    DEF_SPI_VECTOR_CALLING_WRAPPER(&CThostFtdcMdApi::SubscribeMarketData)
    DEF_SPI_VECTOR_CALLING_WRAPPER(&CThostFtdcMdApi::UnSubscribeMarketData)
    DEF_SPI_VECTOR_CALLING_WRAPPER(&CThostFtdcMdApi::SubscribeForQuoteRsp)
    DEF_SPI_VECTOR_CALLING_WRAPPER(&CThostFtdcMdApi::UnSubscribeForQuoteRsp)
    //template <>
    //struct calling_wrapper<&CThostFtdcMdApi::SubscribeMarketData> 
    //    : spi_vector_wrapper<&CThostFtdcMdApi::SubscribeMarketData>
    //{};
}
