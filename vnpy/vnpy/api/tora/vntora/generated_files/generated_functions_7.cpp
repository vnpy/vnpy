#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "TORATstpMdApi.h"
#include "TORATstpTraderApi.h"
#include "TORATstpUserApiDataType.h"
#include "TORATstpUserApiStruct.h"


void generate_class_CTORATstpTraderApi(pybind11::object & parent)
{
    pybind11::class_<
        CTORATstpTraderApi,
        std::unique_ptr<CTORATstpTraderApi, pybind11::nodelete>,
        PyCTORATstpTraderApi
    > c(parent, "CTORATstpTraderApi");
    if constexpr (std::is_default_constructible_v<PyCTORATstpTraderApi>)
        c.def(pybind11::init<>());
    c.def_static("CreateTstpTraderApi",
        &CTORATstpTraderApi::CreateTstpTraderApi,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def_static("GetApiVersion",
        &CTORATstpTraderApi::GetApiVersion,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Release",
        &CTORATstpTraderApi::Release,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Init",
        &CTORATstpTraderApi::Init,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("Join",
        &CTORATstpTraderApi::Join,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("RegisterFront",
        &CTORATstpTraderApi::RegisterFront,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("RegisterNameServer",
        &CTORATstpTraderApi::RegisterNameServer,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("RegisterDeriveServer",
        &CTORATstpTraderApi::RegisterDeriveServer,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("RegisterSpi",
        &CTORATstpTraderApi::RegisterSpi,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribePrivateTopic",
        &CTORATstpTraderApi::SubscribePrivateTopic,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("SubscribePublicTopic",
        &CTORATstpTraderApi::SubscribePublicTopic,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqUserLogin",
        &CTORATstpTraderApi::ReqUserLogin,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqUserLogout",
        &CTORATstpTraderApi::ReqUserLogout,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqUserPasswordUpdate",
        &CTORATstpTraderApi::ReqUserPasswordUpdate,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqInputDeviceSerial",
        &CTORATstpTraderApi::ReqInputDeviceSerial,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqOrderInsert",
        &CTORATstpTraderApi::ReqOrderInsert,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqOrderAction",
        &CTORATstpTraderApi::ReqOrderAction,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqCondOrderInsert",
        &CTORATstpTraderApi::ReqCondOrderInsert,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqCondOrderAction",
        &CTORATstpTraderApi::ReqCondOrderAction,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqInquiryJZFund",
        &CTORATstpTraderApi::ReqInquiryJZFund,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqTransferFund",
        &CTORATstpTraderApi::ReqTransferFund,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqTransferCollateral",
        &CTORATstpTraderApi::ReqTransferCollateral,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqInquiryBankAccountFund",
        &CTORATstpTraderApi::ReqInquiryBankAccountFund,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqInquiryTradeConcentration",
        &CTORATstpTraderApi::ReqInquiryTradeConcentration,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqInquiryMaxOrderVolume",
        &CTORATstpTraderApi::ReqInquiryMaxOrderVolume,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqInquiryHistoryOrder",
        &CTORATstpTraderApi::ReqInquiryHistoryOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqInquiryHistoryTrade",
        &CTORATstpTraderApi::ReqInquiryHistoryTrade,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryExchange",
        &CTORATstpTraderApi::ReqQryExchange,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryMarketData",
        &CTORATstpTraderApi::ReqQryMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQrySecurity",
        &CTORATstpTraderApi::ReqQrySecurity,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryETFFile",
        &CTORATstpTraderApi::ReqQryETFFile,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryETFBasket",
        &CTORATstpTraderApi::ReqQryETFBasket,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryIPOInfo",
        &CTORATstpTraderApi::ReqQryIPOInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryBUProxy",
        &CTORATstpTraderApi::ReqQryBUProxy,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryUser",
        &CTORATstpTraderApi::ReqQryUser,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryInvestor",
        &CTORATstpTraderApi::ReqQryInvestor,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryShareholderAccount",
        &CTORATstpTraderApi::ReqQryShareholderAccount,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryOrder",
        &CTORATstpTraderApi::ReqQryOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryOrderAction",
        &CTORATstpTraderApi::ReqQryOrderAction,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryTrade",
        &CTORATstpTraderApi::ReqQryTrade,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryTradingAccount",
        &CTORATstpTraderApi::ReqQryTradingAccount,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryPosition",
        &CTORATstpTraderApi::ReqQryPosition,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryTradingFee",
        &CTORATstpTraderApi::ReqQryTradingFee,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryInvestorTradingFee",
        &CTORATstpTraderApi::ReqQryInvestorTradingFee,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryIPOQuota",
        &CTORATstpTraderApi::ReqQryIPOQuota,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryMarket",
        &CTORATstpTraderApi::ReqQryMarket,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryOrderFundDetail",
        &CTORATstpTraderApi::ReqQryOrderFundDetail,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryFundTransferDetail",
        &CTORATstpTraderApi::ReqQryFundTransferDetail,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryPositionTransferDetail",
        &CTORATstpTraderApi::ReqQryPositionTransferDetail,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryPledgePosition",
        &CTORATstpTraderApi::ReqQryPledgePosition,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryPledgeInfo",
        &CTORATstpTraderApi::ReqQryPledgeInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryConversionBondInfo",
        &CTORATstpTraderApi::ReqQryConversionBondInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryBondPutbackInfo",
        &CTORATstpTraderApi::ReqQryBondPutbackInfo,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryStandardBondPosition",
        &CTORATstpTraderApi::ReqQryStandardBondPosition,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQrySpecialMarketData",
        &CTORATstpTraderApi::ReqQrySpecialMarketData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryPrematurityRepoOrder",
        &CTORATstpTraderApi::ReqQryPrematurityRepoOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryShareholderParam",
        &CTORATstpTraderApi::ReqQryShareholderParam,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryPeripheryPositionTransferDetail",
        &CTORATstpTraderApi::ReqQryPeripheryPositionTransferDetail,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryInvestorCondOrderLimitParam",
        &CTORATstpTraderApi::ReqQryInvestorCondOrderLimitParam,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryCondOrder",
        &CTORATstpTraderApi::ReqQryCondOrder,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryCondOrderAction",
        &CTORATstpTraderApi::ReqQryCondOrderAction,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryTradingNotice",
        &CTORATstpTraderApi::ReqQryTradingNotice,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryIPONumberResult",
        &CTORATstpTraderApi::ReqQryIPONumberResult,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    c.def("ReqQryIPOMatchNumberResult",
        &CTORATstpTraderApi::ReqQryIPOMatchNumberResult,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    AUTOCXXPY_POST_REGISTER_CLASS(tag_vntora, CTORATstpTraderApi, c);
    module_vntora::objects.emplace("CTORATstpTraderApi", c);
}
void generate_enum_TORA_TE_RESUME_TYPE(pybind11::object & parent)
{
    pybind11::enum_<TORA_TE_RESUME_TYPE> e(parent, "TORA_TE_RESUME_TYPE", pybind11::arithmetic());
    e.value("TORA_TERT_RESTART", TORA_TE_RESUME_TYPE::TORA_TERT_RESTART);
    e.value("TORA_TERT_RESUME", TORA_TE_RESUME_TYPE::TORA_TERT_RESUME);
    e.value("TORA_TERT_QUICK", TORA_TE_RESUME_TYPE::TORA_TERT_QUICK);
    e.export_values();
    module_vntora::objects.emplace("TORA_TE_RESUME_TYPE", e);
}
void generate_caster_(pybind11::object & parent)
{
    struct caster: autocxxpy::caster{};
    auto c = autocxxpy::caster::bind<caster>(parent, "caster"); 
    autocxxpy::caster::try_generate<CTORATstpFensUserInfoField>(c, "toCTORATstpFensUserInfoField)");
    autocxxpy::caster::try_generate<CTORATstpEffectPriceMarketDataField>(c, "toCTORATstpEffectPriceMarketDataField)");
    autocxxpy::caster::try_generate<CTORATstpEffectVolumeMarketDataField>(c, "toCTORATstpEffectVolumeMarketDataField)");
    autocxxpy::caster::try_generate<CTORATstpFundsFlowMarketDataField>(c, "toCTORATstpFundsFlowMarketDataField)");
    autocxxpy::caster::try_generate<CTORATstpReqUserLoginField>(c, "toCTORATstpReqUserLoginField)");
    autocxxpy::caster::try_generate<CTORATstpRspUserLoginField>(c, "toCTORATstpRspUserLoginField)");
    autocxxpy::caster::try_generate<CTORATstpRspInfoField>(c, "toCTORATstpRspInfoField)");
    autocxxpy::caster::try_generate<CTORATstpUserLogoutField>(c, "toCTORATstpUserLogoutField)");
    autocxxpy::caster::try_generate<CTORATstpForceUserLogoutField>(c, "toCTORATstpForceUserLogoutField)");
    autocxxpy::caster::try_generate<CTORATstpUserPasswordUpdateField>(c, "toCTORATstpUserPasswordUpdateField)");
    autocxxpy::caster::try_generate<CTORATstpReqInputDeviceSerialField>(c, "toCTORATstpReqInputDeviceSerialField)");
    autocxxpy::caster::try_generate<CTORATstpRspInputDeviceSerialField>(c, "toCTORATstpRspInputDeviceSerialField)");
    autocxxpy::caster::try_generate<CTORATstpActivateUserField>(c, "toCTORATstpActivateUserField)");
    autocxxpy::caster::try_generate<CTORATstpVerifyUserPasswordField>(c, "toCTORATstpVerifyUserPasswordField)");
    autocxxpy::caster::try_generate<CTORATstpInputOrderField>(c, "toCTORATstpInputOrderField)");
    autocxxpy::caster::try_generate<CTORATstpOrderField>(c, "toCTORATstpOrderField)");
    autocxxpy::caster::try_generate<CTORATstpUserRefField>(c, "toCTORATstpUserRefField)");
    autocxxpy::caster::try_generate<CTORATstpInputOrderActionField>(c, "toCTORATstpInputOrderActionField)");
    autocxxpy::caster::try_generate<CTORATstpOrderActionField>(c, "toCTORATstpOrderActionField)");
    autocxxpy::caster::try_generate<CTORATstpTradeField>(c, "toCTORATstpTradeField)");
    autocxxpy::caster::try_generate<CTORATstpMarketStatusField>(c, "toCTORATstpMarketStatusField)");
    autocxxpy::caster::try_generate<CTORATstpInputCondOrderField>(c, "toCTORATstpInputCondOrderField)");
    autocxxpy::caster::try_generate<CTORATstpConditionOrderField>(c, "toCTORATstpConditionOrderField)");
    autocxxpy::caster::try_generate<CTORATstpInputCondOrderActionField>(c, "toCTORATstpInputCondOrderActionField)");
    autocxxpy::caster::try_generate<CTORATstpReqInquiryJZFundField>(c, "toCTORATstpReqInquiryJZFundField)");
    autocxxpy::caster::try_generate<CTORATstpRspInquiryJZFundField>(c, "toCTORATstpRspInquiryJZFundField)");
    autocxxpy::caster::try_generate<CTORATstpInputTransferFundField>(c, "toCTORATstpInputTransferFundField)");
    autocxxpy::caster::try_generate<CTORATstpInputTransferPositionField>(c, "toCTORATstpInputTransferPositionField)");
    autocxxpy::caster::try_generate<CTORATstpTransferFundField>(c, "toCTORATstpTransferFundField)");
    autocxxpy::caster::try_generate<CTORATstpTransferPositionField>(c, "toCTORATstpTransferPositionField)");
    autocxxpy::caster::try_generate<CTORATstpSpecificSecurityField>(c, "toCTORATstpSpecificSecurityField)");
    autocxxpy::caster::try_generate<CTORATstpInputTransferCollateralField>(c, "toCTORATstpInputTransferCollateralField)");
    autocxxpy::caster::try_generate<CTORATstpReqInquiryBankAccountFundField>(c, "toCTORATstpReqInquiryBankAccountFundField)");
    autocxxpy::caster::try_generate<CTORATstpRspInquiryBankAccountFundField>(c, "toCTORATstpRspInquiryBankAccountFundField)");
    autocxxpy::caster::try_generate<CTORATstpLev2MarketDataField>(c, "toCTORATstpLev2MarketDataField)");
    autocxxpy::caster::try_generate<CTORATstpLev2IndexField>(c, "toCTORATstpLev2IndexField)");
    autocxxpy::caster::try_generate<CTORATstpLev2TransactionField>(c, "toCTORATstpLev2TransactionField)");
    autocxxpy::caster::try_generate<CTORATstpLev2OrderDetailField>(c, "toCTORATstpLev2OrderDetailField)");
    autocxxpy::caster::try_generate<CTORATstpUploadTradeDataField>(c, "toCTORATstpUploadTradeDataField)");
    autocxxpy::caster::try_generate<CTORATstpInputDesignationRegistrationField>(c, "toCTORATstpInputDesignationRegistrationField)");
    autocxxpy::caster::try_generate<CTORATstpInputCustodyTransferField>(c, "toCTORATstpInputCustodyTransferField)");
    autocxxpy::caster::try_generate<CTORATstpInquiryTradeConcentrationField>(c, "toCTORATstpInquiryTradeConcentrationField)");
    autocxxpy::caster::try_generate<CTORATstpInquiryFileOrderField>(c, "toCTORATstpInquiryFileOrderField)");
    autocxxpy::caster::try_generate<CTORATstpFileOrderField>(c, "toCTORATstpFileOrderField)");
    autocxxpy::caster::try_generate<CTORATstpQryRspInfoField>(c, "toCTORATstpQryRspInfoField)");
    autocxxpy::caster::try_generate<CTORATstpReviewFileOrderField>(c, "toCTORATstpReviewFileOrderField)");
    autocxxpy::caster::try_generate<CTORATstpCommitInfoField>(c, "toCTORATstpCommitInfoField)");
    autocxxpy::caster::try_generate<CTORATstpReqInsTradingNoticeField>(c, "toCTORATstpReqInsTradingNoticeField)");
    autocxxpy::caster::try_generate<CTORATstpTradingNoticeField>(c, "toCTORATstpTradingNoticeField)");
    autocxxpy::caster::try_generate<CTORATstpLoadFileOrderField>(c, "toCTORATstpLoadFileOrderField)");
    autocxxpy::caster::try_generate<CTORATstpFileOrderInfoField>(c, "toCTORATstpFileOrderInfoField)");
    autocxxpy::caster::try_generate<CTORATstpReqInquiryMaxOrderVolumeField>(c, "toCTORATstpReqInquiryMaxOrderVolumeField)");
    autocxxpy::caster::try_generate<CTORATstpRspInquiryMaxOrderVolumeField>(c, "toCTORATstpRspInquiryMaxOrderVolumeField)");
    autocxxpy::caster::try_generate<CTORATstpPeripheryPositionTransferDetailField>(c, "toCTORATstpPeripheryPositionTransferDetailField)");
    autocxxpy::caster::try_generate<CTORATstpQryHistoryOrderField>(c, "toCTORATstpQryHistoryOrderField)");
    autocxxpy::caster::try_generate<CTORATstpQryHistoryRspInfoField>(c, "toCTORATstpQryHistoryRspInfoField)");
    autocxxpy::caster::try_generate<CTORATstpHistoryOrderField>(c, "toCTORATstpHistoryOrderField)");
    autocxxpy::caster::try_generate<CTORATstpQryHistoryTradeField>(c, "toCTORATstpQryHistoryTradeField)");
    autocxxpy::caster::try_generate<CTORATstpHistoryTradeField>(c, "toCTORATstpHistoryTradeField)");
    autocxxpy::caster::try_generate<CTORATstpQryExchangeField>(c, "toCTORATstpQryExchangeField)");
    autocxxpy::caster::try_generate<CTORATstpExchangeField>(c, "toCTORATstpExchangeField)");
    autocxxpy::caster::try_generate<CTORATstpQryPBUField>(c, "toCTORATstpQryPBUField)");
    autocxxpy::caster::try_generate<CTORATstpPBUField>(c, "toCTORATstpPBUField)");
    autocxxpy::caster::try_generate<CTORATstpQryMarketDataField>(c, "toCTORATstpQryMarketDataField)");
    autocxxpy::caster::try_generate<CTORATstpMarketDataField>(c, "toCTORATstpMarketDataField)");
    autocxxpy::caster::try_generate<CTORATstpQrySecurityField>(c, "toCTORATstpQrySecurityField)");
    autocxxpy::caster::try_generate<CTORATstpSecurityField>(c, "toCTORATstpSecurityField)");
    autocxxpy::caster::try_generate<CTORATstpQryETFFileField>(c, "toCTORATstpQryETFFileField)");
    autocxxpy::caster::try_generate<CTORATstpETFFileField>(c, "toCTORATstpETFFileField)");
    autocxxpy::caster::try_generate<CTORATstpQryETFBasketField>(c, "toCTORATstpQryETFBasketField)");
    autocxxpy::caster::try_generate<CTORATstpETFBasketField>(c, "toCTORATstpETFBasketField)");
    autocxxpy::caster::try_generate<CTORATstpQryDepartmentInfoField>(c, "toCTORATstpQryDepartmentInfoField)");
    autocxxpy::caster::try_generate<CTORATstpDepartmentInfoField>(c, "toCTORATstpDepartmentInfoField)");
    autocxxpy::caster::try_generate<CTORATstpQryIPOInfoField>(c, "toCTORATstpQryIPOInfoField)");
    autocxxpy::caster::try_generate<CTORATstpIPOInfoField>(c, "toCTORATstpIPOInfoField)");
    autocxxpy::caster::try_generate<CTORATstpQryBrokerUserFunctionField>(c, "toCTORATstpQryBrokerUserFunctionField)");
    autocxxpy::caster::try_generate<CTORATstpBrokerUserFunctionField>(c, "toCTORATstpBrokerUserFunctionField)");
    autocxxpy::caster::try_generate<CTORATstpQryBUProxyField>(c, "toCTORATstpQryBUProxyField)");
    autocxxpy::caster::try_generate<CTORATstpBUProxyField>(c, "toCTORATstpBUProxyField)");
    autocxxpy::caster::try_generate<CTORATstpQryUserField>(c, "toCTORATstpQryUserField)");
    autocxxpy::caster::try_generate<CTORATstpUserField>(c, "toCTORATstpUserField)");
    autocxxpy::caster::try_generate<CTORATstpQryInvestorField>(c, "toCTORATstpQryInvestorField)");
    autocxxpy::caster::try_generate<CTORATstpInvestorField>(c, "toCTORATstpInvestorField)");
    autocxxpy::caster::try_generate<CTORATstpQryShareholderAccountField>(c, "toCTORATstpQryShareholderAccountField)");
    autocxxpy::caster::try_generate<CTORATstpShareholderAccountField>(c, "toCTORATstpShareholderAccountField)");
    autocxxpy::caster::try_generate<CTORATstpQryBusinessUnitField>(c, "toCTORATstpQryBusinessUnitField)");
    autocxxpy::caster::try_generate<CTORATstpBusinessUnitField>(c, "toCTORATstpBusinessUnitField)");
    autocxxpy::caster::try_generate<CTORATstpQryBusinessUnitAndTradingAcctField>(c, "toCTORATstpQryBusinessUnitAndTradingAcctField)");
    autocxxpy::caster::try_generate<CTORATstpBusinessUnitAndTradingAcctField>(c, "toCTORATstpBusinessUnitAndTradingAcctField)");
    autocxxpy::caster::try_generate<CTORATstpQryOrderField>(c, "toCTORATstpQryOrderField)");
    autocxxpy::caster::try_generate<CTORATstpQryOrderActionField>(c, "toCTORATstpQryOrderActionField)");
    autocxxpy::caster::try_generate<CTORATstpQryTradeField>(c, "toCTORATstpQryTradeField)");
    autocxxpy::caster::try_generate<CTORATstpQryTradingAccountField>(c, "toCTORATstpQryTradingAccountField)");
    autocxxpy::caster::try_generate<CTORATstpTradingAccountField>(c, "toCTORATstpTradingAccountField)");
    autocxxpy::caster::try_generate<CTORATstpQryPositionField>(c, "toCTORATstpQryPositionField)");
    autocxxpy::caster::try_generate<CTORATstpPositionField>(c, "toCTORATstpPositionField)");
    autocxxpy::caster::try_generate<CTORATstpQryTradingFeeField>(c, "toCTORATstpQryTradingFeeField)");
    autocxxpy::caster::try_generate<CTORATstpTradingFeeField>(c, "toCTORATstpTradingFeeField)");
    autocxxpy::caster::try_generate<CTORATstpQryInvestorTradingFeeField>(c, "toCTORATstpQryInvestorTradingFeeField)");
    autocxxpy::caster::try_generate<CTORATstpInvestorTradingFeeField>(c, "toCTORATstpInvestorTradingFeeField)");
    autocxxpy::caster::try_generate<CTORATstpQryIPOQuotaField>(c, "toCTORATstpQryIPOQuotaField)");
    autocxxpy::caster::try_generate<CTORATstpIPOQuotaField>(c, "toCTORATstpIPOQuotaField)");
    autocxxpy::caster::try_generate<CTORATstpQryMarketField>(c, "toCTORATstpQryMarketField)");
    autocxxpy::caster::try_generate<CTORATstpMarketField>(c, "toCTORATstpMarketField)");
    autocxxpy::caster::try_generate<CTORATstpQryOrderFundDetailField>(c, "toCTORATstpQryOrderFundDetailField)");
    autocxxpy::caster::try_generate<CTORATstpOrderFundDetailField>(c, "toCTORATstpOrderFundDetailField)");
    autocxxpy::caster::try_generate<CTORATstpQryFundTransferDetailField>(c, "toCTORATstpQryFundTransferDetailField)");
    autocxxpy::caster::try_generate<CTORATstpFundTransferDetailField>(c, "toCTORATstpFundTransferDetailField)");
    autocxxpy::caster::try_generate<CTORATstpQryPositionTransferDetailField>(c, "toCTORATstpQryPositionTransferDetailField)");
    autocxxpy::caster::try_generate<CTORATstpPositionTransferDetailField>(c, "toCTORATstpPositionTransferDetailField)");
    autocxxpy::caster::try_generate<CTORATstpQryPledgePositionField>(c, "toCTORATstpQryPledgePositionField)");
    autocxxpy::caster::try_generate<CTORATstpPledgePositionField>(c, "toCTORATstpPledgePositionField)");
    autocxxpy::caster::try_generate<CTORATstpQryPledgeInfoField>(c, "toCTORATstpQryPledgeInfoField)");
    autocxxpy::caster::try_generate<CTORATstpPledgeInfoField>(c, "toCTORATstpPledgeInfoField)");
    autocxxpy::caster::try_generate<CTORATstpQryConversionBondInfoField>(c, "toCTORATstpQryConversionBondInfoField)");
    autocxxpy::caster::try_generate<CTORATstpConversionBondInfoField>(c, "toCTORATstpConversionBondInfoField)");
    autocxxpy::caster::try_generate<CTORATstpQryBondPutbackInfoField>(c, "toCTORATstpQryBondPutbackInfoField)");
    autocxxpy::caster::try_generate<CTORATstpBondPutbackInfoField>(c, "toCTORATstpBondPutbackInfoField)");
    autocxxpy::caster::try_generate<CTORATstpQryStandardBondPositionField>(c, "toCTORATstpQryStandardBondPositionField)");
    autocxxpy::caster::try_generate<CTORATstpStandardBondPositionField>(c, "toCTORATstpStandardBondPositionField)");
    autocxxpy::caster::try_generate<CTORATstpQryDesignationRegistrationField>(c, "toCTORATstpQryDesignationRegistrationField)");
    autocxxpy::caster::try_generate<CTORATstpDesignationRegistrationField>(c, "toCTORATstpDesignationRegistrationField)");
    autocxxpy::caster::try_generate<CTORATstpQryCustodyTransferField>(c, "toCTORATstpQryCustodyTransferField)");
    autocxxpy::caster::try_generate<CTORATstpCustodyTransferField>(c, "toCTORATstpCustodyTransferField)");
    autocxxpy::caster::try_generate<CTORATstpQrySpecialMarketDataField>(c, "toCTORATstpQrySpecialMarketDataField)");
    autocxxpy::caster::try_generate<CTORATstpSpecialMarketDataField>(c, "toCTORATstpSpecialMarketDataField)");
    autocxxpy::caster::try_generate<CTORATstpQryPrematurityRepoOrderField>(c, "toCTORATstpQryPrematurityRepoOrderField)");
    autocxxpy::caster::try_generate<CTORATstpPrematurityRepoOrderField>(c, "toCTORATstpPrematurityRepoOrderField)");
    autocxxpy::caster::try_generate<CTORATstpQryShareholderParamField>(c, "toCTORATstpQryShareholderParamField)");
    autocxxpy::caster::try_generate<CTORATstpShareholderParamField>(c, "toCTORATstpShareholderParamField)");
    autocxxpy::caster::try_generate<CTORATstpQryPeripheryPositionTransferDetailField>(c, "toCTORATstpQryPeripheryPositionTransferDetailField)");
    autocxxpy::caster::try_generate<CTORATstpQryInvestorCondOrderLimitParamField>(c, "toCTORATstpQryInvestorCondOrderLimitParamField)");
    autocxxpy::caster::try_generate<CTORATstpInvestorCondOrderLimitParamField>(c, "toCTORATstpInvestorCondOrderLimitParamField)");
    autocxxpy::caster::try_generate<CTORATstpQryCondOrderField>(c, "toCTORATstpQryCondOrderField)");
    autocxxpy::caster::try_generate<CTORATstpCondOrderField>(c, "toCTORATstpCondOrderField)");
    autocxxpy::caster::try_generate<CTORATstpQryCondOrderActionField>(c, "toCTORATstpQryCondOrderActionField)");
    autocxxpy::caster::try_generate<CTORATstpCondOrderActionField>(c, "toCTORATstpCondOrderActionField)");
    autocxxpy::caster::try_generate<CTORATstpQryBrokerUserRoleField>(c, "toCTORATstpQryBrokerUserRoleField)");
    autocxxpy::caster::try_generate<CTORATstpBrokerUserRoleField>(c, "toCTORATstpBrokerUserRoleField)");
    autocxxpy::caster::try_generate<CTORATstpQryBrokerUserRoleAssignmentField>(c, "toCTORATstpQryBrokerUserRoleAssignmentField)");
    autocxxpy::caster::try_generate<CTORATstpBrokerUserRoleAssignmentField>(c, "toCTORATstpBrokerUserRoleAssignmentField)");
    autocxxpy::caster::try_generate<CTORATstpQryTradingNoticeField>(c, "toCTORATstpQryTradingNoticeField)");
    autocxxpy::caster::try_generate<CTORATstpQryIPONumberResultField>(c, "toCTORATstpQryIPONumberResultField)");
    autocxxpy::caster::try_generate<CTORATstpIPONumberResultField>(c, "toCTORATstpIPONumberResultField)");
    autocxxpy::caster::try_generate<CTORATstpQryIPOMatchNumberResultField>(c, "toCTORATstpQryIPOMatchNumberResultField)");
    autocxxpy::caster::try_generate<CTORATstpIPOMatchNumberResultField>(c, "toCTORATstpIPOMatchNumberResultField)");
    autocxxpy::caster::try_generate<CTORATstpMdSpi>(c, "toCTORATstpMdSpi)");
    autocxxpy::caster::try_generate<CTORATstpMdApi>(c, "toCTORATstpMdApi)");
    autocxxpy::caster::try_generate<CTORATstpTraderSpi>(c, "toCTORATstpTraderSpi)");
    autocxxpy::caster::try_generate<CTORATstpTraderApi>(c, "toCTORATstpTraderApi)");
    autocxxpy::caster::try_generate<TTORATstpDateType>(c, "toTTORATstpDateType)");
    autocxxpy::caster::try_generate<TTORATstpTimeType>(c, "toTTORATstpTimeType)");
    autocxxpy::caster::try_generate<TTORATstpMillisecType>(c, "toTTORATstpMillisecType)");
    autocxxpy::caster::try_generate<TTORATstpPriceType>(c, "toTTORATstpPriceType)");
    autocxxpy::caster::try_generate<TTORATstpRatioType>(c, "toTTORATstpRatioType)");
    autocxxpy::caster::try_generate<TTORATstpMoneyType>(c, "toTTORATstpMoneyType)");
    autocxxpy::caster::try_generate<TTORATstpVolumeType>(c, "toTTORATstpVolumeType)");
    autocxxpy::caster::try_generate<TTORATstpLargeVolumeType>(c, "toTTORATstpLargeVolumeType)");
    autocxxpy::caster::try_generate<TTORATstpBoolType>(c, "toTTORATstpBoolType)");
    autocxxpy::caster::try_generate<TTORATstpSequenceNoType>(c, "toTTORATstpSequenceNoType)");
    autocxxpy::caster::try_generate<TTORATstpSerialType>(c, "toTTORATstpSerialType)");
    autocxxpy::caster::try_generate<TTORATstpCommFluxType>(c, "toTTORATstpCommFluxType)");
    autocxxpy::caster::try_generate<TTORATstpRoleIDType>(c, "toTTORATstpRoleIDType)");
    autocxxpy::caster::try_generate<TTORATstpRoleDescriptionType>(c, "toTTORATstpRoleDescriptionType)");
    autocxxpy::caster::try_generate<TTORATstpFunctionsType>(c, "toTTORATstpFunctionsType)");
    autocxxpy::caster::try_generate<TTORATstpDeviceIDType>(c, "toTTORATstpDeviceIDType)");
    autocxxpy::caster::try_generate<TTORATstpDeviceSerialType>(c, "toTTORATstpDeviceSerialType)");
    autocxxpy::caster::try_generate<TTORATstpExchangeIDType>(c, "toTTORATstpExchangeIDType)");
    autocxxpy::caster::try_generate<TTORATstpAuthModeType>(c, "toTTORATstpAuthModeType)");
    autocxxpy::caster::try_generate<TTORATstpVolumeMultipleType>(c, "toTTORATstpVolumeMultipleType)");
    autocxxpy::caster::try_generate<TTORATstpIdCardNoType>(c, "toTTORATstpIdCardNoType)");
    autocxxpy::caster::try_generate<TTORATstpUserIDType>(c, "toTTORATstpUserIDType)");
    autocxxpy::caster::try_generate<TTORATstpTradeIDType>(c, "toTTORATstpTradeIDType)");
    autocxxpy::caster::try_generate<TTORATstpOrderSysIDType>(c, "toTTORATstpOrderSysIDType)");
    autocxxpy::caster::try_generate<TTORATstpCondOrderIDType>(c, "toTTORATstpCondOrderIDType)");
    autocxxpy::caster::try_generate<TTORATstpPasswordType>(c, "toTTORATstpPasswordType)");
    autocxxpy::caster::try_generate<TTORATstpFrontIDType>(c, "toTTORATstpFrontIDType)");
    autocxxpy::caster::try_generate<TTORATstpSessionIDType>(c, "toTTORATstpSessionIDType)");
    autocxxpy::caster::try_generate<TTORATstpProductInfoType>(c, "toTTORATstpProductInfoType)");
    autocxxpy::caster::try_generate<TTORATstpProtocolInfoType>(c, "toTTORATstpProtocolInfoType)");
    autocxxpy::caster::try_generate<TTORATstpErrorIDType>(c, "toTTORATstpErrorIDType)");
    autocxxpy::caster::try_generate<TTORATstpErrorMsgType>(c, "toTTORATstpErrorMsgType)");
    autocxxpy::caster::try_generate<TTORATstpPositionTypeType>(c, "toTTORATstpPositionTypeType)");
    autocxxpy::caster::try_generate<TTORATstpParameterCharValType>(c, "toTTORATstpParameterCharValType)");
    autocxxpy::caster::try_generate<TTORATstpNameType>(c, "toTTORATstpNameType)");
    autocxxpy::caster::try_generate<TTORATstpListingMarketType>(c, "toTTORATstpListingMarketType)");
    autocxxpy::caster::try_generate<TTORATstpProductIDType>(c, "toTTORATstpProductIDType)");
    autocxxpy::caster::try_generate<TTORATstpSecurityIDType>(c, "toTTORATstpSecurityIDType)");
    autocxxpy::caster::try_generate<TTORATstpParValueType>(c, "toTTORATstpParValueType)");
    autocxxpy::caster::try_generate<TTORATstpPriceTickType>(c, "toTTORATstpPriceTickType)");
    autocxxpy::caster::try_generate<TTORATstpTradingUnitType>(c, "toTTORATstpTradingUnitType)");
    autocxxpy::caster::try_generate<TTORATstpSecurityStatusType>(c, "toTTORATstpSecurityStatusType)");
    autocxxpy::caster::try_generate<TTORATstpAccountIDType>(c, "toTTORATstpAccountIDType)");
    autocxxpy::caster::try_generate<TTORATstpInvestorIDType>(c, "toTTORATstpInvestorIDType)");
    autocxxpy::caster::try_generate<TTORATstpAddressType>(c, "toTTORATstpAddressType)");
    autocxxpy::caster::try_generate<TTORATstpDepartmentIDType>(c, "toTTORATstpDepartmentIDType)");
    autocxxpy::caster::try_generate<TTORATstpTerminalInfoType>(c, "toTTORATstpTerminalInfoType)");
    autocxxpy::caster::try_generate<TTORATstpShareholderIDType>(c, "toTTORATstpShareholderIDType)");
    autocxxpy::caster::try_generate<TTORATstpPbuIDType>(c, "toTTORATstpPbuIDType)");
    autocxxpy::caster::try_generate<TTORATstpIPAddressType>(c, "toTTORATstpIPAddressType)");
    autocxxpy::caster::try_generate<TTORATstpMacAddressType>(c, "toTTORATstpMacAddressType)");
    autocxxpy::caster::try_generate<TTORATstpLangType>(c, "toTTORATstpLangType)");
    autocxxpy::caster::try_generate<TTORATstpInterestType>(c, "toTTORATstpInterestType)");
    autocxxpy::caster::try_generate<TTORATstpOrderLocalIDType>(c, "toTTORATstpOrderLocalIDType)");
    autocxxpy::caster::try_generate<TTORATstpPositionVolumeType>(c, "toTTORATstpPositionVolumeType)");
    autocxxpy::caster::try_generate<TTORATstpBusinessUnitIDType>(c, "toTTORATstpBusinessUnitIDType)");
    autocxxpy::caster::try_generate<TTORATstpBusinessUnitNameType>(c, "toTTORATstpBusinessUnitNameType)");
    autocxxpy::caster::try_generate<TTORATstpTimeStampType>(c, "toTTORATstpTimeStampType)");
    autocxxpy::caster::try_generate<TTORATstpBigTimeStampType>(c, "toTTORATstpBigTimeStampType)");
    autocxxpy::caster::try_generate<TTORATstpSecurityNameType>(c, "toTTORATstpSecurityNameType)");
    autocxxpy::caster::try_generate<TTORATstpExternalSerialType>(c, "toTTORATstpExternalSerialType)");
    autocxxpy::caster::try_generate<TTORATstpOrderRefType>(c, "toTTORATstpOrderRefType)");
    autocxxpy::caster::try_generate<TTORATstpRequestIDType>(c, "toTTORATstpRequestIDType)");
    autocxxpy::caster::try_generate<TTORATstpIntSerialType>(c, "toTTORATstpIntSerialType)");
    autocxxpy::caster::try_generate<TTORATstpInvestorNameType>(c, "toTTORATstpInvestorNameType)");
    autocxxpy::caster::try_generate<TTORATstpUserNameType>(c, "toTTORATstpUserNameType)");
    autocxxpy::caster::try_generate<TTORATstpLoginLimitType>(c, "toTTORATstpLoginLimitType)");
    autocxxpy::caster::try_generate<TTORATstpCurrencyIDType>(c, "toTTORATstpCurrencyIDType)");
    autocxxpy::caster::try_generate<TTORATstpBankIDType>(c, "toTTORATstpBankIDType)");
    autocxxpy::caster::try_generate<TTORATstpBankAccountIDType>(c, "toTTORATstpBankAccountIDType)");
    autocxxpy::caster::try_generate<TTORATstpTransferReasonType>(c, "toTTORATstpTransferReasonType)");
    autocxxpy::caster::try_generate<TTORATstpCombOffsetFlagType>(c, "toTTORATstpCombOffsetFlagType)");
    autocxxpy::caster::try_generate<TTORATstpCombHedgeFlagType>(c, "toTTORATstpCombHedgeFlagType)");
    autocxxpy::caster::try_generate<TTORATstpExchangeInstIDType>(c, "toTTORATstpExchangeInstIDType)");
    autocxxpy::caster::try_generate<TTORATstpTelephoneType>(c, "toTTORATstpTelephoneType)");
    autocxxpy::caster::try_generate<TTORATstpMobileType>(c, "toTTORATstpMobileType)");
    autocxxpy::caster::try_generate<TTORATstpTraderIDType>(c, "toTTORATstpTraderIDType)");
    autocxxpy::caster::try_generate<TTORATstpLongVolumeType>(c, "toTTORATstpLongVolumeType)");
    autocxxpy::caster::try_generate<TTORATstpLongSequenceType>(c, "toTTORATstpLongSequenceType)");
    autocxxpy::caster::try_generate<TTORATstpOrderUnitType>(c, "toTTORATstpOrderUnitType)");
    autocxxpy::caster::try_generate<TTORATstpIdCardTypeType>(c, "toTTORATstpIdCardTypeType)");
    autocxxpy::caster::try_generate<TTORATstpAccountTypeType>(c, "toTTORATstpAccountTypeType)");
    autocxxpy::caster::try_generate<TTORATstpDirectionType>(c, "toTTORATstpDirectionType)");
    autocxxpy::caster::try_generate<TTORATstpBrokerageTypeType>(c, "toTTORATstpBrokerageTypeType)");
    autocxxpy::caster::try_generate<TTORATstpUserTypeType>(c, "toTTORATstpUserTypeType)");
    autocxxpy::caster::try_generate<TTORATstpContingentConditionType>(c, "toTTORATstpContingentConditionType)");
    autocxxpy::caster::try_generate<TTORATstpETFCurrenceReplaceStatusType>(c, "toTTORATstpETFCurrenceReplaceStatusType)");
    autocxxpy::caster::try_generate<TTORATstpOperateSourceType>(c, "toTTORATstpOperateSourceType)");
    autocxxpy::caster::try_generate<TTORATstpOperwayType>(c, "toTTORATstpOperwayType)");
    autocxxpy::caster::try_generate<TTORATstpOperwaysType>(c, "toTTORATstpOperwaysType)");
    autocxxpy::caster::try_generate<TTORATstpOrderPriceTypeType>(c, "toTTORATstpOrderPriceTypeType)");
    autocxxpy::caster::try_generate<TTORATstpOrderVolumeTypeType>(c, "toTTORATstpOrderVolumeTypeType)");
    autocxxpy::caster::try_generate<TTORATstpTimeConditionType>(c, "toTTORATstpTimeConditionType)");
    autocxxpy::caster::try_generate<TTORATstpVolumeConditionType>(c, "toTTORATstpVolumeConditionType)");
    autocxxpy::caster::try_generate<TTORATstpForceCloseReasonType>(c, "toTTORATstpForceCloseReasonType)");
    autocxxpy::caster::try_generate<TTORATstpFileOrderTypeType>(c, "toTTORATstpFileOrderTypeType)");
    autocxxpy::caster::try_generate<TTORATstpTransferDirectionType>(c, "toTTORATstpTransferDirectionType)");
    autocxxpy::caster::try_generate<TTORATstpCollateralDirectionType>(c, "toTTORATstpCollateralDirectionType)");
    autocxxpy::caster::try_generate<TTORATstpTransferStatusType>(c, "toTTORATstpTransferStatusType)");
    autocxxpy::caster::try_generate<TTORATstpTransferPositionTypeType>(c, "toTTORATstpTransferPositionTypeType)");
    autocxxpy::caster::try_generate<TTORATstpSystemNameType>(c, "toTTORATstpSystemNameType)");
    autocxxpy::caster::try_generate<TTORATstpRelativeCondParamType>(c, "toTTORATstpRelativeCondParamType)");
    autocxxpy::caster::try_generate<TTORATstpOrderStatusType>(c, "toTTORATstpOrderStatusType)");
    autocxxpy::caster::try_generate<TTORATstpCondOrderStatusType>(c, "toTTORATstpCondOrderStatusType)");
    autocxxpy::caster::try_generate<TTORATstpOrderSubmitStatusType>(c, "toTTORATstpOrderSubmitStatusType)");
    autocxxpy::caster::try_generate<TTORATstpOrderTypeType>(c, "toTTORATstpOrderTypeType)");
    autocxxpy::caster::try_generate<TTORATstpOffsetFlagType>(c, "toTTORATstpOffsetFlagType)");
    autocxxpy::caster::try_generate<TTORATstpHedgeFlagType>(c, "toTTORATstpHedgeFlagType)");
    autocxxpy::caster::try_generate<TTORATstpActionFlagType>(c, "toTTORATstpActionFlagType)");
    autocxxpy::caster::try_generate<TTORATstpOrderActionStatusType>(c, "toTTORATstpOrderActionStatusType)");
    autocxxpy::caster::try_generate<TTORATstpClientIDTypeType>(c, "toTTORATstpClientIDTypeType)");
    autocxxpy::caster::try_generate<TTORATstpBizClassType>(c, "toTTORATstpBizClassType)");
    autocxxpy::caster::try_generate<TTORATstpCreditPositionTypeType>(c, "toTTORATstpCreditPositionTypeType)");
    autocxxpy::caster::try_generate<TTORATstpFunctionIDType>(c, "toTTORATstpFunctionIDType)");
    autocxxpy::caster::try_generate<TTORATstpSecurityTypeType>(c, "toTTORATstpSecurityTypeType)");
    autocxxpy::caster::try_generate<TTORATstpEndFlagType>(c, "toTTORATstpEndFlagType)");
    autocxxpy::caster::try_generate<TTORATstpMarketIDType>(c, "toTTORATstpMarketIDType)");
    autocxxpy::caster::try_generate<TTORATstpLogInAccountType>(c, "toTTORATstpLogInAccountType)");
    autocxxpy::caster::try_generate<TTORATstpLogInAccountTypeType>(c, "toTTORATstpLogInAccountTypeType)");
    autocxxpy::caster::try_generate<TTORATstpMarketStatusType>(c, "toTTORATstpMarketStatusType)");
    autocxxpy::caster::try_generate<TTORATstpBigsInfoType>(c, "toTTORATstpBigsInfoType)");
    autocxxpy::caster::try_generate<TTORATstpShortsInfoType>(c, "toTTORATstpShortsInfoType)");
    autocxxpy::caster::try_generate<TTORATstpIntInfoType>(c, "toTTORATstpIntInfoType)");
    autocxxpy::caster::try_generate<TTORATstpFloatInfoType>(c, "toTTORATstpFloatInfoType)");
    autocxxpy::caster::try_generate<TTORATstpApiGroupIDType>(c, "toTTORATstpApiGroupIDType)");
    autocxxpy::caster::try_generate<TTORATstpApiRunModeType>(c, "toTTORATstpApiRunModeType)");
    autocxxpy::caster::try_generate<TTORATstpDesignationTypeType>(c, "toTTORATstpDesignationTypeType)");
    autocxxpy::caster::try_generate<TTORATstpCustodyTransferTypeType>(c, "toTTORATstpCustodyTransferTypeType)");
    autocxxpy::caster::try_generate<TTORATstpProperCtrlBusinessTypeType>(c, "toTTORATstpProperCtrlBusinessTypeType)");
    autocxxpy::caster::try_generate<TTORATstpProperCtrlPassFlagType>(c, "toTTORATstpProperCtrlPassFlagType)");
    autocxxpy::caster::try_generate<TTORATstpCRiskLevelType>(c, "toTTORATstpCRiskLevelType)");
    autocxxpy::caster::try_generate<TTORATstpProfInvestorTypeType>(c, "toTTORATstpProfInvestorTypeType)");
    autocxxpy::caster::try_generate<TTORATstpLOrderTypeType>(c, "toTTORATstpLOrderTypeType)");
    autocxxpy::caster::try_generate<TTORATstpLSideType>(c, "toTTORATstpLSideType)");
    autocxxpy::caster::try_generate<TTORATstpExecTypeType>(c, "toTTORATstpExecTypeType)");
    autocxxpy::caster::try_generate<TTORATstpCondCheckType>(c, "toTTORATstpCondCheckType)");
    autocxxpy::caster::try_generate<TTORATstpHDSerialType>(c, "toTTORATstpHDSerialType)");
    autocxxpy::caster::try_generate<TTORATstpMDSubModeType>(c, "toTTORATstpMDSubModeType)");
    autocxxpy::caster::try_generate<TTORATstpMDSecurityStatType>(c, "toTTORATstpMDSecurityStatType)");
    autocxxpy::caster::try_generate<TTORATstpCommitStatusType>(c, "toTTORATstpCommitStatusType)");
    autocxxpy::caster::try_generate<TTORATstpParamTypeType>(c, "toTTORATstpParamTypeType)");
    autocxxpy::caster::try_generate<TTORATstpContentType>(c, "toTTORATstpContentType)");
    autocxxpy::caster::try_generate<TTORATstpStatusMsgType>(c, "toTTORATstpStatusMsgType)");
    autocxxpy::caster::try_generate<TTORATstpIPONumberIDType>(c, "toTTORATstpIPONumberIDType)");
    autocxxpy::caster::try_generate<TTORATstpPageLocateType>(c, "toTTORATstpPageLocateType)");
}
