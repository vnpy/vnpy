#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <c2py/c2py.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "oes_api/oes_api.h"
#include "mds_api/mds_api.h"


void generate_class_OesQryFundTransferSerialFilter(pybind11::object & parent)
{
    // _OesQryFundTransferSerialFilter
    pybind11::class_<_OesQryFundTransferSerialFilter> c(parent, "_OesQryFundTransferSerialFilter");
    if constexpr (std::is_default_constructible_v<_OesQryFundTransferSerialFilter>)
        c.def(pybind11::init<>());
    // _OesQryFundTransferSerialFilter::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "custId", custId);
    // _OesQryFundTransferSerialFilter::cashAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "cashAcctId", cashAcctId);
    // _OesQryFundTransferSerialFilter::clSeqNo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "clSeqNo", clSeqNo);
    // _OesQryFundTransferSerialFilter::clEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "clEnvId", clEnvId);
    // _OesQryFundTransferSerialFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "__filler", __filler);
    // _OesQryFundTransferSerialFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryFundTransferSerialFilter, c);
    module_vnoes::objects.emplace("_OesQryFundTransferSerialFilter", c);
}
void generate_class_OesQryFundTransferSerialReq(pybind11::object & parent)
{
    // _OesQryFundTransferSerialReq
    pybind11::class_<_OesQryFundTransferSerialReq> c(parent, "_OesQryFundTransferSerialReq");
    if constexpr (std::is_default_constructible_v<_OesQryFundTransferSerialReq>)
        c.def(pybind11::init<>());
    // _OesQryFundTransferSerialReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialReq, "reqHead", reqHead);
    // _OesQryFundTransferSerialReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryFundTransferSerialReq, c);
    module_vnoes::objects.emplace("_OesQryFundTransferSerialReq", c);
}
void generate_class_OesQryFundTransferSerialRsp(pybind11::object & parent)
{
    // _OesQryFundTransferSerialRsp
    pybind11::class_<_OesQryFundTransferSerialRsp> c(parent, "_OesQryFundTransferSerialRsp");
    if constexpr (std::is_default_constructible_v<_OesQryFundTransferSerialRsp>)
        c.def(pybind11::init<>());
    // _OesQryFundTransferSerialRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialRsp, "rspHead", rspHead);
    // _OesQryFundTransferSerialRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryFundTransferSerialRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryFundTransferSerialRsp, c);
    module_vnoes::objects.emplace("_OesQryFundTransferSerialRsp", c);
}
void generate_class_OesQryLotWinningFilter(pybind11::object & parent)
{
    // _OesQryLotWinningFilter
    pybind11::class_<_OesQryLotWinningFilter> c(parent, "_OesQryLotWinningFilter");
    if constexpr (std::is_default_constructible_v<_OesQryLotWinningFilter>)
        c.def(pybind11::init<>());
    // _OesQryLotWinningFilter::custId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "custId", custId);
    // _OesQryLotWinningFilter::invAcctId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "invAcctId", invAcctId);
    // _OesQryLotWinningFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "mktId", mktId);
    // _OesQryLotWinningFilter::lotType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "lotType", lotType);
    // _OesQryLotWinningFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "__filler", __filler);
    // _OesQryLotWinningFilter::startDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "startDate", startDate);
    // _OesQryLotWinningFilter::endDate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "endDate", endDate);
    // _OesQryLotWinningFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryLotWinningFilter, c);
    module_vnoes::objects.emplace("_OesQryLotWinningFilter", c);
}
void generate_class_OesQryLotWinningReq(pybind11::object & parent)
{
    // _OesQryLotWinningReq
    pybind11::class_<_OesQryLotWinningReq> c(parent, "_OesQryLotWinningReq");
    if constexpr (std::is_default_constructible_v<_OesQryLotWinningReq>)
        c.def(pybind11::init<>());
    // _OesQryLotWinningReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningReq, "reqHead", reqHead);
    // _OesQryLotWinningReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryLotWinningReq, c);
    module_vnoes::objects.emplace("_OesQryLotWinningReq", c);
}
void generate_class_OesQryLotWinningRsp(pybind11::object & parent)
{
    // _OesQryLotWinningRsp
    pybind11::class_<_OesQryLotWinningRsp> c(parent, "_OesQryLotWinningRsp");
    if constexpr (std::is_default_constructible_v<_OesQryLotWinningRsp>)
        c.def(pybind11::init<>());
    // _OesQryLotWinningRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningRsp, "rspHead", rspHead);
    // _OesQryLotWinningRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryLotWinningRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryLotWinningRsp, c);
    module_vnoes::objects.emplace("_OesQryLotWinningRsp", c);
}
void generate_class_OesQryIssueFilter(pybind11::object & parent)
{
    // _OesQryIssueFilter
    pybind11::class_<_OesQryIssueFilter> c(parent, "_OesQryIssueFilter");
    if constexpr (std::is_default_constructible_v<_OesQryIssueFilter>)
        c.def(pybind11::init<>());
    // _OesQryIssueFilter::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "securityId", securityId);
    // _OesQryIssueFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "mktId", mktId);
    // _OesQryIssueFilter::productType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "productType", productType);
    // _OesQryIssueFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "__filler", __filler);
    // _OesQryIssueFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryIssueFilter, c);
    module_vnoes::objects.emplace("_OesQryIssueFilter", c);
}
void generate_class_OesQryIssueReq(pybind11::object & parent)
{
    // _OesQryIssueReq
    pybind11::class_<_OesQryIssueReq> c(parent, "_OesQryIssueReq");
    if constexpr (std::is_default_constructible_v<_OesQryIssueReq>)
        c.def(pybind11::init<>());
    // _OesQryIssueReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueReq, "reqHead", reqHead);
    // _OesQryIssueReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryIssueReq, c);
    module_vnoes::objects.emplace("_OesQryIssueReq", c);
}
void generate_class_OesQryIssueRsp(pybind11::object & parent)
{
    // _OesQryIssueRsp
    pybind11::class_<_OesQryIssueRsp> c(parent, "_OesQryIssueRsp");
    if constexpr (std::is_default_constructible_v<_OesQryIssueRsp>)
        c.def(pybind11::init<>());
    // _OesQryIssueRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueRsp, "rspHead", rspHead);
    // _OesQryIssueRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryIssueRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryIssueRsp, c);
    module_vnoes::objects.emplace("_OesQryIssueRsp", c);
}
void generate_class_OesQryStockFilter(pybind11::object & parent)
{
    // _OesQryStockFilter
    pybind11::class_<_OesQryStockFilter> c(parent, "_OesQryStockFilter");
    if constexpr (std::is_default_constructible_v<_OesQryStockFilter>)
        c.def(pybind11::init<>());
    // _OesQryStockFilter::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "securityId", securityId);
    // _OesQryStockFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "mktId", mktId);
    // _OesQryStockFilter::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "securityType", securityType);
    // _OesQryStockFilter::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "subSecurityType", subSecurityType);
    // _OesQryStockFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "__filler", __filler);
    // _OesQryStockFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStockFilter, c);
    module_vnoes::objects.emplace("_OesQryStockFilter", c);
}
void generate_class_OesQryStockReq(pybind11::object & parent)
{
    // _OesQryStockReq
    pybind11::class_<_OesQryStockReq> c(parent, "_OesQryStockReq");
    if constexpr (std::is_default_constructible_v<_OesQryStockReq>)
        c.def(pybind11::init<>());
    // _OesQryStockReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockReq, "reqHead", reqHead);
    // _OesQryStockReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStockReq, c);
    module_vnoes::objects.emplace("_OesQryStockReq", c);
}
void generate_class_OesQryStockRsp(pybind11::object & parent)
{
    // _OesQryStockRsp
    pybind11::class_<_OesQryStockRsp> c(parent, "_OesQryStockRsp");
    if constexpr (std::is_default_constructible_v<_OesQryStockRsp>)
        c.def(pybind11::init<>());
    // _OesQryStockRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockRsp, "rspHead", rspHead);
    // _OesQryStockRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryStockRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryStockRsp, c);
    module_vnoes::objects.emplace("_OesQryStockRsp", c);
}
void generate_class_OesQryEtfFilter(pybind11::object & parent)
{
    // _OesQryEtfFilter
    pybind11::class_<_OesQryEtfFilter> c(parent, "_OesQryEtfFilter");
    if constexpr (std::is_default_constructible_v<_OesQryEtfFilter>)
        c.def(pybind11::init<>());
    // _OesQryEtfFilter::fundId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfFilter, "fundId", fundId);
    // _OesQryEtfFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfFilter, "mktId", mktId);
    // _OesQryEtfFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfFilter, "__filler", __filler);
    // _OesQryEtfFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfFilter, c);
    module_vnoes::objects.emplace("_OesQryEtfFilter", c);
}
void generate_class_OesQryEtfReq(pybind11::object & parent)
{
    // _OesQryEtfReq
    pybind11::class_<_OesQryEtfReq> c(parent, "_OesQryEtfReq");
    if constexpr (std::is_default_constructible_v<_OesQryEtfReq>)
        c.def(pybind11::init<>());
    // _OesQryEtfReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfReq, "reqHead", reqHead);
    // _OesQryEtfReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfReq, c);
    module_vnoes::objects.emplace("_OesQryEtfReq", c);
}
void generate_class_OesQryEtfRsp(pybind11::object & parent)
{
    // _OesQryEtfRsp
    pybind11::class_<_OesQryEtfRsp> c(parent, "_OesQryEtfRsp");
    if constexpr (std::is_default_constructible_v<_OesQryEtfRsp>)
        c.def(pybind11::init<>());
    // _OesQryEtfRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfRsp, "rspHead", rspHead);
    // _OesQryEtfRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfRsp, c);
    module_vnoes::objects.emplace("_OesQryEtfRsp", c);
}
void generate_class_OesQryEtfComponentFilter(pybind11::object & parent)
{
    // _OesQryEtfComponentFilter
    pybind11::class_<_OesQryEtfComponentFilter> c(parent, "_OesQryEtfComponentFilter");
    if constexpr (std::is_default_constructible_v<_OesQryEtfComponentFilter>)
        c.def(pybind11::init<>());
    // _OesQryEtfComponentFilter::fundId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentFilter, "fundId", fundId);
    // _OesQryEtfComponentFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfComponentFilter, c);
    module_vnoes::objects.emplace("_OesQryEtfComponentFilter", c);
}
void generate_class_OesEtfComponentItem(pybind11::object & parent)
{
    // _OesEtfComponentItem
    pybind11::class_<_OesEtfComponentItem> c(parent, "_OesEtfComponentItem");
    if constexpr (std::is_default_constructible_v<_OesEtfComponentItem>)
        c.def(pybind11::init<>());
    // _OesEtfComponentItem::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "securityId", securityId);
    // _OesEtfComponentItem::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "mktId", mktId);
    // _OesEtfComponentItem::subFlag
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "subFlag", subFlag);
    // _OesEtfComponentItem::securityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "securityType", securityType);
    // _OesEtfComponentItem::subSecurityType
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "subSecurityType", subSecurityType);
    // _OesEtfComponentItem::prevClose
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "prevClose", prevClose);
    // _OesEtfComponentItem::qty
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "qty", qty);
    // _OesEtfComponentItem::premiumRate
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "premiumRate", premiumRate);
    // _OesEtfComponentItem::creationSubCash
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "creationSubCash", creationSubCash);
    // _OesEtfComponentItem::redemptionCashSub
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "redemptionCashSub", redemptionCashSub);
    // _OesEtfComponentItem::fundId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesEtfComponentItem, "fundId", fundId);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesEtfComponentItem, c);
    module_vnoes::objects.emplace("_OesEtfComponentItem", c);
}
void generate_class_OesQryEtfComponentReq(pybind11::object & parent)
{
    // _OesQryEtfComponentReq
    pybind11::class_<_OesQryEtfComponentReq> c(parent, "_OesQryEtfComponentReq");
    if constexpr (std::is_default_constructible_v<_OesQryEtfComponentReq>)
        c.def(pybind11::init<>());
    // _OesQryEtfComponentReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentReq, "reqHead", reqHead);
    // _OesQryEtfComponentReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfComponentReq, c);
    module_vnoes::objects.emplace("_OesQryEtfComponentReq", c);
}
void generate_class_OesQryEtfComponentRsp(pybind11::object & parent)
{
    // _OesQryEtfComponentRsp
    pybind11::class_<_OesQryEtfComponentRsp> c(parent, "_OesQryEtfComponentRsp");
    if constexpr (std::is_default_constructible_v<_OesQryEtfComponentRsp>)
        c.def(pybind11::init<>());
    // _OesQryEtfComponentRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentRsp, "rspHead", rspHead);
    // _OesQryEtfComponentRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryEtfComponentRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryEtfComponentRsp, c);
    module_vnoes::objects.emplace("_OesQryEtfComponentRsp", c);
}
void generate_class_OesQryOptionFilter(pybind11::object & parent)
{
    // _OesQryOptionFilter
    pybind11::class_<_OesQryOptionFilter> c(parent, "_OesQryOptionFilter");
    if constexpr (std::is_default_constructible_v<_OesQryOptionFilter>)
        c.def(pybind11::init<>());
    // _OesQryOptionFilter::securityId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionFilter, "securityId", securityId);
    // _OesQryOptionFilter::mktId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionFilter, "mktId", mktId);
    // _OesQryOptionFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionFilter, "__filler", __filler);
    // _OesQryOptionFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOptionFilter, c);
    module_vnoes::objects.emplace("_OesQryOptionFilter", c);
}
void generate_class_OesQryOptionReq(pybind11::object & parent)
{
    // _OesQryOptionReq
    pybind11::class_<_OesQryOptionReq> c(parent, "_OesQryOptionReq");
    if constexpr (std::is_default_constructible_v<_OesQryOptionReq>)
        c.def(pybind11::init<>());
    // _OesQryOptionReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionReq, "reqHead", reqHead);
    // _OesQryOptionReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOptionReq, c);
    module_vnoes::objects.emplace("_OesQryOptionReq", c);
}
void generate_class_OesQryOptionRsp(pybind11::object & parent)
{
    // _OesQryOptionRsp
    pybind11::class_<_OesQryOptionRsp> c(parent, "_OesQryOptionRsp");
    if constexpr (std::is_default_constructible_v<_OesQryOptionRsp>)
        c.def(pybind11::init<>());
    // _OesQryOptionRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionRsp, "rspHead", rspHead);
    // _OesQryOptionRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryOptionRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryOptionRsp, c);
    module_vnoes::objects.emplace("_OesQryOptionRsp", c);
}
void generate_class_OesQryTradingDayRsp(pybind11::object & parent)
{
    // _OesQryTradingDayRsp
    pybind11::class_<_OesQryTradingDayRsp> c(parent, "_OesQryTradingDayRsp");
    if constexpr (std::is_default_constructible_v<_OesQryTradingDayRsp>)
        c.def(pybind11::init<>());
    // _OesQryTradingDayRsp::tradingDay
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTradingDayRsp, "tradingDay", tradingDay);
    // _OesQryTradingDayRsp::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryTradingDayRsp, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryTradingDayRsp, c);
    module_vnoes::objects.emplace("_OesQryTradingDayRsp", c);
}
void generate_class_OesQryMarketStateFilter(pybind11::object & parent)
{
    // _OesQryMarketStateFilter
    pybind11::class_<_OesQryMarketStateFilter> c(parent, "_OesQryMarketStateFilter");
    if constexpr (std::is_default_constructible_v<_OesQryMarketStateFilter>)
        c.def(pybind11::init<>());
    // _OesQryMarketStateFilter::exchId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateFilter, "exchId", exchId);
    // _OesQryMarketStateFilter::platformId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateFilter, "platformId", platformId);
    // _OesQryMarketStateFilter::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateFilter, "__filler", __filler);
    // _OesQryMarketStateFilter::userInfo
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateFilter, "userInfo", userInfo);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryMarketStateFilter, c);
    module_vnoes::objects.emplace("_OesQryMarketStateFilter", c);
}
void generate_class_OesQryMarketStateReq(pybind11::object & parent)
{
    // _OesQryMarketStateReq
    pybind11::class_<_OesQryMarketStateReq> c(parent, "_OesQryMarketStateReq");
    if constexpr (std::is_default_constructible_v<_OesQryMarketStateReq>)
        c.def(pybind11::init<>());
    // _OesQryMarketStateReq::reqHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateReq, "reqHead", reqHead);
    // _OesQryMarketStateReq::qryFilter
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateReq, "qryFilter", qryFilter);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryMarketStateReq, c);
    module_vnoes::objects.emplace("_OesQryMarketStateReq", c);
}
void generate_class_OesQryMarketStateRsp(pybind11::object & parent)
{
    // _OesQryMarketStateRsp
    pybind11::class_<_OesQryMarketStateRsp> c(parent, "_OesQryMarketStateRsp");
    if constexpr (std::is_default_constructible_v<_OesQryMarketStateRsp>)
        c.def(pybind11::init<>());
    // _OesQryMarketStateRsp::rspHead
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateRsp, "rspHead", rspHead);
    // _OesQryMarketStateRsp::qryItems
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryMarketStateRsp, "qryItems", qryItems);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryMarketStateRsp, c);
    module_vnoes::objects.emplace("_OesQryMarketStateRsp", c);
}
void generate_class_OesQryReqMsg(pybind11::object & parent)
{
    // _OesQryReqMsg
    pybind11::class_<_OesQryReqMsg> c(parent, "_OesQryReqMsg");
    if constexpr (std::is_default_constructible_v<_OesQryReqMsg>)
        c.def(pybind11::init<>());
    // _OesQryReqMsg::qryOrd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryOrd", qryOrd);
    // _OesQryReqMsg::qryTrd
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryTrd", qryTrd);
    // _OesQryReqMsg::qryCashAsset
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryCashAsset", qryCashAsset);
    // _OesQryReqMsg::qryStkHolding
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryStkHolding", qryStkHolding);
    // _OesQryReqMsg::qryOptHolding
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryOptHolding", qryOptHolding);
    // _OesQryReqMsg::qryCust
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryCust", qryCust);
    // _OesQryReqMsg::qryInvAcct
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryInvAcct", qryInvAcct);
    // _OesQryReqMsg::qryComms
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryComms", qryComms);
    // _OesQryReqMsg::qryFundTrsf
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryFundTrsf", qryFundTrsf);
    // _OesQryReqMsg::qryLotWinning
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryLotWinning", qryLotWinning);
    // _OesQryReqMsg::qryIssue
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryIssue", qryIssue);
    // _OesQryReqMsg::qryStock
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryStock", qryStock);
    // _OesQryReqMsg::qryEtf
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryEtf", qryEtf);
    // _OesQryReqMsg::qryEtfComponent
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryEtfComponent", qryEtfComponent);
    // _OesQryReqMsg::qryOption
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryOption", qryOption);
    // _OesQryReqMsg::qryMktState
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryMktState", qryMktState);
    // _OesQryReqMsg::qryCounterCash
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryReqMsg, "qryCounterCash", qryCounterCash);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryReqMsg, c);
    module_vnoes::objects.emplace("_OesQryReqMsg", c);
}
void generate_class_OesQryRspMsg(pybind11::object & parent)
{
    // _OesQryRspMsg
    pybind11::class_<_OesQryRspMsg> c(parent, "_OesQryRspMsg");
    if constexpr (std::is_default_constructible_v<_OesQryRspMsg>)
        c.def(pybind11::init<>());
    // _OesQryRspMsg::ordRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "ordRsp", ordRsp);
    // _OesQryRspMsg::trdRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "trdRsp", trdRsp);
    // _OesQryRspMsg::cashAssetRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "cashAssetRsp", cashAssetRsp);
    // _OesQryRspMsg::stkHoldingRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "stkHoldingRsp", stkHoldingRsp);
    // _OesQryRspMsg::optHoldingRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "optHoldingRsp", optHoldingRsp);
    // _OesQryRspMsg::custRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "custRsp", custRsp);
    // _OesQryRspMsg::invAcctRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "invAcctRsp", invAcctRsp);
    // _OesQryRspMsg::commsRateRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "commsRateRsp", commsRateRsp);
    // _OesQryRspMsg::fundTrsfRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "fundTrsfRsp", fundTrsfRsp);
    // _OesQryRspMsg::lotWinningRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "lotWinningRsp", lotWinningRsp);
    // _OesQryRspMsg::issueRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "issueRsp", issueRsp);
    // _OesQryRspMsg::stockRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "stockRsp", stockRsp);
    // _OesQryRspMsg::etfRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "etfRsp", etfRsp);
    // _OesQryRspMsg::etfComponentRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "etfComponentRsp", etfComponentRsp);
    // _OesQryRspMsg::optionRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "optionRsp", optionRsp);
    // _OesQryRspMsg::tradingDay
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "tradingDay", tradingDay);
    // _OesQryRspMsg::mktStateRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "mktStateRsp", mktStateRsp);
    // _OesQryRspMsg::clientOverview
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "clientOverview", clientOverview);
    // _OesQryRspMsg::counterCashRsp
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesQryRspMsg, "counterCashRsp", counterCashRsp);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesQryRspMsg, c);
    module_vnoes::objects.emplace("_OesQryRspMsg", c);
}
void generate_class_OesReportSynchronizationReq(pybind11::object & parent)
{
    // _OesReportSynchronizationReq
    pybind11::class_<_OesReportSynchronizationReq> c(parent, "_OesReportSynchronizationReq");
    if constexpr (std::is_default_constructible_v<_OesReportSynchronizationReq>)
        c.def(pybind11::init<>());
    // _OesReportSynchronizationReq::lastRptSeqNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationReq, "lastRptSeqNum", lastRptSeqNum);
    // _OesReportSynchronizationReq::subscribeEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationReq, "subscribeEnvId", subscribeEnvId);
    // _OesReportSynchronizationReq::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationReq, "__filler", __filler);
    // _OesReportSynchronizationReq::subscribeRptTypes
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationReq, "subscribeRptTypes", subscribeRptTypes);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesReportSynchronizationReq, c);
    module_vnoes::objects.emplace("_OesReportSynchronizationReq", c);
}
void generate_class_OesReportSynchronizationRsp(pybind11::object & parent)
{
    // _OesReportSynchronizationRsp
    pybind11::class_<_OesReportSynchronizationRsp> c(parent, "_OesReportSynchronizationRsp");
    if constexpr (std::is_default_constructible_v<_OesReportSynchronizationRsp>)
        c.def(pybind11::init<>());
    // _OesReportSynchronizationRsp::lastRptSeqNum
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationRsp, "lastRptSeqNum", lastRptSeqNum);
    // _OesReportSynchronizationRsp::subscribeEnvId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationRsp, "subscribeEnvId", subscribeEnvId);
    // _OesReportSynchronizationRsp::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationRsp, "__filler", __filler);
    // _OesReportSynchronizationRsp::subscribeRptTypes
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesReportSynchronizationRsp, "subscribeRptTypes", subscribeRptTypes);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesReportSynchronizationRsp, c);
    module_vnoes::objects.emplace("_OesReportSynchronizationRsp", c);
}
void generate_class_OesTestRequestReq(pybind11::object & parent)
{
    // _OesTestRequestReq
    pybind11::class_<_OesTestRequestReq> c(parent, "_OesTestRequestReq");
    if constexpr (std::is_default_constructible_v<_OesTestRequestReq>)
        c.def(pybind11::init<>());
    // _OesTestRequestReq::testReqId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestReq, "testReqId", testReqId);
    // _OesTestRequestReq::sendTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestReq, "sendTime", sendTime);
    // _OesTestRequestReq::__filler
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestReq, "__filler", __filler);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesTestRequestReq, c);
    module_vnoes::objects.emplace("_OesTestRequestReq", c);
}
void generate_class_OesTestRequestRsp(pybind11::object & parent)
{
    // _OesTestRequestRsp
    pybind11::class_<_OesTestRequestRsp> c(parent, "_OesTestRequestRsp");
    if constexpr (std::is_default_constructible_v<_OesTestRequestRsp>)
        c.def(pybind11::init<>());
    // _OesTestRequestRsp::testReqId
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "testReqId", testReqId);
    // _OesTestRequestRsp::origSendTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "origSendTime", origSendTime);
    // _OesTestRequestRsp::__filler1
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__filler1", __filler1);
    // _OesTestRequestRsp::respTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "respTime", respTime);
    // _OesTestRequestRsp::__filler2
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__filler2", __filler2);
    // _OesTestRequestRsp::__recvTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__recvTime", __recvTime);
    // _OesTestRequestRsp::__collectedTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__collectedTime", __collectedTime);
    // _OesTestRequestRsp::__pushingTime
    c.AUTOCXXPY_DEF_PROPERTY(tag_vnoes, _OesTestRequestRsp, "__pushingTime", __pushingTime);
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vnoes, _OesTestRequestRsp, c);
    module_vnoes::objects.emplace("_OesTestRequestRsp", c);
}
