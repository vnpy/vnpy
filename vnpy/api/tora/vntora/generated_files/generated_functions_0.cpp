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


void generate_vntora(pybind11::module & parent)
{
    generate_class_CTORATstpFensUserInfoField(parent);
    generate_class_CTORATstpEffectPriceMarketDataField(parent);
    generate_class_CTORATstpEffectVolumeMarketDataField(parent);
    generate_class_CTORATstpFundsFlowMarketDataField(parent);
    generate_class_CTORATstpReqUserLoginField(parent);
    generate_class_CTORATstpRspUserLoginField(parent);
    generate_class_CTORATstpRspInfoField(parent);
    generate_class_CTORATstpUserLogoutField(parent);
    generate_class_CTORATstpForceUserLogoutField(parent);
    generate_class_CTORATstpUserPasswordUpdateField(parent);
    generate_class_CTORATstpReqInputDeviceSerialField(parent);
    generate_class_CTORATstpRspInputDeviceSerialField(parent);
    generate_class_CTORATstpActivateUserField(parent);
    generate_class_CTORATstpVerifyUserPasswordField(parent);
    generate_class_CTORATstpInputOrderField(parent);
    generate_class_CTORATstpOrderField(parent);
    generate_class_CTORATstpUserRefField(parent);
    generate_class_CTORATstpInputOrderActionField(parent);
    generate_class_CTORATstpOrderActionField(parent);
    generate_class_CTORATstpTradeField(parent);
    generate_class_CTORATstpMarketStatusField(parent);
    generate_class_CTORATstpInputCondOrderField(parent);
    generate_class_CTORATstpConditionOrderField(parent);
    generate_class_CTORATstpInputCondOrderActionField(parent);
    generate_class_CTORATstpReqInquiryJZFundField(parent);
    generate_class_CTORATstpRspInquiryJZFundField(parent);
    generate_class_CTORATstpInputTransferFundField(parent);
    generate_class_CTORATstpInputTransferPositionField(parent);
    generate_class_CTORATstpTransferFundField(parent);
    generate_class_CTORATstpTransferPositionField(parent);
    generate_class_CTORATstpSpecificSecurityField(parent);
    generate_class_CTORATstpInputTransferCollateralField(parent);
    generate_class_CTORATstpReqInquiryBankAccountFundField(parent);
    generate_class_CTORATstpRspInquiryBankAccountFundField(parent);
    generate_class_CTORATstpLev2MarketDataField(parent);
    generate_class_CTORATstpLev2IndexField(parent);
    generate_class_CTORATstpLev2TransactionField(parent);
    generate_class_CTORATstpLev2OrderDetailField(parent);
    generate_class_CTORATstpUploadTradeDataField(parent);
    generate_class_CTORATstpInputDesignationRegistrationField(parent);
    generate_class_CTORATstpInputCustodyTransferField(parent);
    generate_class_CTORATstpInquiryTradeConcentrationField(parent);
    generate_class_CTORATstpInquiryFileOrderField(parent);
    generate_class_CTORATstpFileOrderField(parent);
    generate_class_CTORATstpQryRspInfoField(parent);
    generate_class_CTORATstpReviewFileOrderField(parent);
    generate_class_CTORATstpCommitInfoField(parent);
    generate_class_CTORATstpReqInsTradingNoticeField(parent);
    generate_class_CTORATstpTradingNoticeField(parent);
    generate_class_CTORATstpLoadFileOrderField(parent);
    generate_class_CTORATstpFileOrderInfoField(parent);
    generate_class_CTORATstpReqInquiryMaxOrderVolumeField(parent);
    generate_class_CTORATstpRspInquiryMaxOrderVolumeField(parent);
    generate_class_CTORATstpPeripheryPositionTransferDetailField(parent);
    generate_class_CTORATstpQryHistoryOrderField(parent);
    generate_class_CTORATstpQryHistoryRspInfoField(parent);
    generate_class_CTORATstpHistoryOrderField(parent);
    generate_class_CTORATstpQryHistoryTradeField(parent);
    generate_class_CTORATstpHistoryTradeField(parent);
    generate_class_CTORATstpQryExchangeField(parent);
    generate_class_CTORATstpExchangeField(parent);
    generate_class_CTORATstpQryPBUField(parent);
    generate_class_CTORATstpPBUField(parent);
    generate_class_CTORATstpQryMarketDataField(parent);
    generate_class_CTORATstpMarketDataField(parent);
    generate_class_CTORATstpQrySecurityField(parent);
    generate_class_CTORATstpSecurityField(parent);
    generate_class_CTORATstpQryETFFileField(parent);
    generate_class_CTORATstpETFFileField(parent);
    generate_class_CTORATstpQryETFBasketField(parent);
    generate_class_CTORATstpETFBasketField(parent);
    generate_class_CTORATstpQryDepartmentInfoField(parent);
    generate_class_CTORATstpDepartmentInfoField(parent);
    generate_class_CTORATstpQryIPOInfoField(parent);
    generate_class_CTORATstpIPOInfoField(parent);
    generate_class_CTORATstpQryBrokerUserFunctionField(parent);
    generate_class_CTORATstpBrokerUserFunctionField(parent);
    generate_class_CTORATstpQryBUProxyField(parent);
    generate_class_CTORATstpBUProxyField(parent);
    generate_class_CTORATstpQryUserField(parent);
    generate_class_CTORATstpUserField(parent);
    generate_class_CTORATstpQryInvestorField(parent);
    generate_class_CTORATstpInvestorField(parent);
    generate_class_CTORATstpQryShareholderAccountField(parent);
    generate_class_CTORATstpShareholderAccountField(parent);
    generate_class_CTORATstpQryBusinessUnitField(parent);
    generate_class_CTORATstpBusinessUnitField(parent);
    generate_class_CTORATstpQryBusinessUnitAndTradingAcctField(parent);
    generate_class_CTORATstpBusinessUnitAndTradingAcctField(parent);
    generate_class_CTORATstpQryOrderField(parent);
    generate_class_CTORATstpQryOrderActionField(parent);
    generate_class_CTORATstpQryTradeField(parent);
    generate_class_CTORATstpQryTradingAccountField(parent);
    generate_class_CTORATstpTradingAccountField(parent);
    generate_class_CTORATstpQryPositionField(parent);
    generate_class_CTORATstpPositionField(parent);
    generate_class_CTORATstpQryTradingFeeField(parent);
    generate_class_CTORATstpTradingFeeField(parent);
    generate_class_CTORATstpQryInvestorTradingFeeField(parent);
    generate_class_CTORATstpInvestorTradingFeeField(parent);
    generate_class_CTORATstpQryIPOQuotaField(parent);
    generate_class_CTORATstpIPOQuotaField(parent);
    generate_class_CTORATstpQryMarketField(parent);
    generate_class_CTORATstpMarketField(parent);
    generate_class_CTORATstpQryOrderFundDetailField(parent);
    generate_class_CTORATstpOrderFundDetailField(parent);
    generate_class_CTORATstpQryFundTransferDetailField(parent);
    generate_class_CTORATstpFundTransferDetailField(parent);
    generate_class_CTORATstpQryPositionTransferDetailField(parent);
    generate_class_CTORATstpPositionTransferDetailField(parent);
    generate_class_CTORATstpQryPledgePositionField(parent);
    generate_class_CTORATstpPledgePositionField(parent);
    generate_class_CTORATstpQryPledgeInfoField(parent);
    generate_class_CTORATstpPledgeInfoField(parent);
    generate_class_CTORATstpQryConversionBondInfoField(parent);
    generate_class_CTORATstpConversionBondInfoField(parent);
    generate_class_CTORATstpQryBondPutbackInfoField(parent);
    generate_class_CTORATstpBondPutbackInfoField(parent);
    generate_class_CTORATstpQryStandardBondPositionField(parent);
    generate_class_CTORATstpStandardBondPositionField(parent);
    generate_class_CTORATstpQryDesignationRegistrationField(parent);
    generate_class_CTORATstpDesignationRegistrationField(parent);
    generate_class_CTORATstpQryCustodyTransferField(parent);
    generate_class_CTORATstpCustodyTransferField(parent);
    generate_class_CTORATstpQrySpecialMarketDataField(parent);
    generate_class_CTORATstpSpecialMarketDataField(parent);
    generate_class_CTORATstpQryPrematurityRepoOrderField(parent);
    generate_class_CTORATstpPrematurityRepoOrderField(parent);
    generate_class_CTORATstpQryShareholderParamField(parent);
    generate_class_CTORATstpShareholderParamField(parent);
    generate_class_CTORATstpQryPeripheryPositionTransferDetailField(parent);
    generate_class_CTORATstpQryInvestorCondOrderLimitParamField(parent);
    generate_class_CTORATstpInvestorCondOrderLimitParamField(parent);
    generate_class_CTORATstpQryCondOrderField(parent);
    generate_class_CTORATstpCondOrderField(parent);
    generate_class_CTORATstpQryCondOrderActionField(parent);
    generate_class_CTORATstpCondOrderActionField(parent);
    generate_class_CTORATstpQryBrokerUserRoleField(parent);
    generate_class_CTORATstpBrokerUserRoleField(parent);
    generate_class_CTORATstpQryBrokerUserRoleAssignmentField(parent);
    generate_class_CTORATstpBrokerUserRoleAssignmentField(parent);
    generate_class_CTORATstpQryTradingNoticeField(parent);
    generate_class_CTORATstpQryIPONumberResultField(parent);
    generate_class_CTORATstpIPONumberResultField(parent);
    generate_class_CTORATstpQryIPOMatchNumberResultField(parent);
    generate_class_CTORATstpIPOMatchNumberResultField(parent);
    generate_class_CTORATstpMdSpi(parent);
    generate_class_CTORATstpMdApi(parent);
    generate_class_CTORATstpTraderSpi(parent);
    generate_class_CTORATstpTraderApi(parent);
    generate_enum_TORA_TE_RESUME_TYPE(parent);
    parent.def("set_null",
        static_cast<void( *)(int &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(int &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(int &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(int &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(int &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(int &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(double &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(double &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(double &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(double &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(double &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(double &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(char &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(char &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(char &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(char &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(char &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(char &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(short &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(short &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(short &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(short &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(short &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(short &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(long long &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(long long &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(long long &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(long long &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(long long &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(long long &)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(char *)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(char *)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(char *)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(char *)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(char *)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("set_null",
        static_cast<void( *)(char *)>(
            &set_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(int)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(int)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(int)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(int)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(int)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(int)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(double)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(double)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(double)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(double)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(double)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(double)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(char)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(char)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(char)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(char)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(char)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(char)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(short)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(short)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(short)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(short)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(short)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(short)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(long long)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(long long)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(long long)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(long long)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(long long)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(long long)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(const char *)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(const char *)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(const char *)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(const char *)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(const char *)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("is_null",
        static_cast<bool( *)(const char *)>(
            &is_null
            ),
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.attr("CHAR_NULL_VAL") = CHAR_NULL_VAL;
    parent.attr("TORA_TSTP_EXD_SSE_FO") = TORA_TSTP_EXD_SSE_FO;
    parent.attr("TORA_TSTP_EXD_SZSE_FO") = TORA_TSTP_EXD_SZSE_FO;
    parent.attr("TORA_TSTP_EXD_COMM") = TORA_TSTP_EXD_COMM;
    parent.attr("TORA_TSTP_EXD_SSE") = TORA_TSTP_EXD_SSE;
    parent.attr("TORA_TSTP_EXD_SZSE") = TORA_TSTP_EXD_SZSE;
    parent.attr("TORA_TSTP_EXD_HK") = TORA_TSTP_EXD_HK;
    parent.attr("TORA_TSTP_AM_Password") = TORA_TSTP_AM_Password;
    parent.attr("TORA_TSTP_AM_FingerPrint") = TORA_TSTP_AM_FingerPrint;
    parent.attr("TORA_TSTP_PT_Net") = TORA_TSTP_PT_Net;
    parent.attr("TORA_TSTP_PT_Gross") = TORA_TSTP_PT_Gross;
    parent.attr("TORA_TSTP_PID_COMMON") = TORA_TSTP_PID_COMMON;
    parent.attr("TORA_TSTP_PID_SHStock") = TORA_TSTP_PID_SHStock;
    parent.attr("TORA_TSTP_PID_SHWarrant") = TORA_TSTP_PID_SHWarrant;
    parent.attr("TORA_TSTP_PID_SHFund") = TORA_TSTP_PID_SHFund;
    parent.attr("TORA_TSTP_PID_SHBond") = TORA_TSTP_PID_SHBond;
    parent.attr("TORA_TSTP_PID_SHStandard") = TORA_TSTP_PID_SHStandard;
    parent.attr("TORA_TSTP_PID_SHRepurchase") = TORA_TSTP_PID_SHRepurchase;
    parent.attr("TORA_TSTP_PID_SZStock") = TORA_TSTP_PID_SZStock;
    parent.attr("TORA_TSTP_PID_SZWarrant") = TORA_TSTP_PID_SZWarrant;
    parent.attr("TORA_TSTP_PID_SZFund") = TORA_TSTP_PID_SZFund;
    parent.attr("TORA_TSTP_PID_SZBond") = TORA_TSTP_PID_SZBond;
    parent.attr("TORA_TSTP_PID_SZStandard") = TORA_TSTP_PID_SZStandard;
    parent.attr("TORA_TSTP_PID_SZRepurchase") = TORA_TSTP_PID_SZRepurchase;
    parent.attr("TORA_TSTP_BKID_CCB") = TORA_TSTP_BKID_CCB;
    parent.attr("TORA_TSTP_BKID_ABC") = TORA_TSTP_BKID_ABC;
    parent.attr("TORA_TSTP_BKID_ICBC") = TORA_TSTP_BKID_ICBC;
    parent.attr("TORA_TSTP_BKID_BOC") = TORA_TSTP_BKID_BOC;
    parent.attr("TORA_TSTP_BKID_CMB") = TORA_TSTP_BKID_CMB;
    parent.attr("TORA_TSTP_BKID_BC") = TORA_TSTP_BKID_BC;
    parent.attr("TORA_TSTP_BKID_SPDB") = TORA_TSTP_BKID_SPDB;
    parent.attr("TORA_TSTP_BKID_CIB") = TORA_TSTP_BKID_CIB;
    parent.attr("TORA_TSTP_BKID_CEB") = TORA_TSTP_BKID_CEB;
    parent.attr("TORA_TSTP_BKID_GDB") = TORA_TSTP_BKID_GDB;
    parent.attr("TORA_TSTP_BKID_NJCB") = TORA_TSTP_BKID_NJCB;
    parent.attr("TORA_TSTP_BKID_SHCB") = TORA_TSTP_BKID_SHCB;
    parent.attr("TORA_TSTP_BKID_CITICB") = TORA_TSTP_BKID_CITICB;
    parent.attr("TORA_TSTP_BKID_HXB") = TORA_TSTP_BKID_HXB;
    parent.attr("TORA_TSTP_BKID_CMBC") = TORA_TSTP_BKID_CMBC;
    parent.attr("TORA_TSTP_BKID_PACB") = TORA_TSTP_BKID_PACB;
    parent.attr("TORA_TSTP_BKID_NBCB") = TORA_TSTP_BKID_NBCB;
    parent.attr("TORA_TSTP_OUT_Shou") = TORA_TSTP_OUT_Shou;
    parent.attr("TORA_TSTP_OUT_Gu") = TORA_TSTP_OUT_Gu;
    parent.attr("TORA_TSTP_OUT_Fen") = TORA_TSTP_OUT_Fen;
    parent.attr("TORA_TSTP_OUT_Zhang") = TORA_TSTP_OUT_Zhang;
    parent.attr("TORA_TSTP_ICT_EID") = TORA_TSTP_ICT_EID;
    parent.attr("TORA_TSTP_ICT_IDCard") = TORA_TSTP_ICT_IDCard;
    parent.attr("TORA_TSTP_ICT_OfficerIDCard") = TORA_TSTP_ICT_OfficerIDCard;
    parent.attr("TORA_TSTP_ICT_PoliceIDCard") = TORA_TSTP_ICT_PoliceIDCard;
    parent.attr("TORA_TSTP_ICT_SoldierIDCard") = TORA_TSTP_ICT_SoldierIDCard;
    parent.attr("TORA_TSTP_ICT_HouseholdRegister") = TORA_TSTP_ICT_HouseholdRegister;
    parent.attr("TORA_TSTP_ICT_Passport") = TORA_TSTP_ICT_Passport;
    parent.attr("TORA_TSTP_ICT_TaiwanCompatriotIDCard") = TORA_TSTP_ICT_TaiwanCompatriotIDCard;
    parent.attr("TORA_TSTP_ICT_HomeComingCard") = TORA_TSTP_ICT_HomeComingCard;
    parent.attr("TORA_TSTP_ICT_LicenseNo") = TORA_TSTP_ICT_LicenseNo;
    parent.attr("TORA_TSTP_ICT_TaxNo") = TORA_TSTP_ICT_TaxNo;
    parent.attr("TORA_TSTP_ICT_HMMainlandTravelPermit") = TORA_TSTP_ICT_HMMainlandTravelPermit;
    parent.attr("TORA_TSTP_ICT_TwMainlandTravelPermit") = TORA_TSTP_ICT_TwMainlandTravelPermit;
    parent.attr("TORA_TSTP_ICT_DrivingLicense") = TORA_TSTP_ICT_DrivingLicense;
    parent.attr("TORA_TSTP_ICT_SocialID") = TORA_TSTP_ICT_SocialID;
    parent.attr("TORA_TSTP_ICT_LocalID") = TORA_TSTP_ICT_LocalID;
    parent.attr("TORA_TSTP_ICT_BusinessRegistration") = TORA_TSTP_ICT_BusinessRegistration;
    parent.attr("TORA_TSTP_ICT_HKMCIDCard") = TORA_TSTP_ICT_HKMCIDCard;
    parent.attr("TORA_TSTP_ICT_AccountsPermits") = TORA_TSTP_ICT_AccountsPermits;
    parent.attr("TORA_TSTP_ICT_OtherCard") = TORA_TSTP_ICT_OtherCard;
    parent.attr("TORA_TSTP_FAT_Normal") = TORA_TSTP_FAT_Normal;
    parent.attr("TORA_TSTP_FAT_Credit") = TORA_TSTP_FAT_Credit;
    parent.attr("TORA_TSTP_FAT_Derivatives") = TORA_TSTP_FAT_Derivatives;
    parent.attr("TORA_TSTP_D_Buy") = TORA_TSTP_D_Buy;
    parent.attr("TORA_TSTP_D_Sell") = TORA_TSTP_D_Sell;
    parent.attr("TORA_TSTP_D_ETFPur") = TORA_TSTP_D_ETFPur;
    parent.attr("TORA_TSTP_D_ETFRed") = TORA_TSTP_D_ETFRed;
    parent.attr("TORA_TSTP_D_IPO") = TORA_TSTP_D_IPO;
    parent.attr("TORA_TSTP_D_Repurchase") = TORA_TSTP_D_Repurchase;
    parent.attr("TORA_TSTP_D_ReverseRepur") = TORA_TSTP_D_ReverseRepur;
    parent.attr("TORA_TSTP_D_OeFundPur") = TORA_TSTP_D_OeFundPur;
    parent.attr("TORA_TSTP_D_OeFundRed") = TORA_TSTP_D_OeFundRed;
    parent.attr("TORA_TSTP_D_CollateralIn") = TORA_TSTP_D_CollateralIn;
    parent.attr("TORA_TSTP_D_CollateralOut") = TORA_TSTP_D_CollateralOut;
    parent.attr("TORA_TSTP_D_PledgeIn") = TORA_TSTP_D_PledgeIn;
    parent.attr("TORA_TSTP_D_PledgeOut") = TORA_TSTP_D_PledgeOut;
    parent.attr("TORA_TSTP_D_Rationed") = TORA_TSTP_D_Rationed;
    parent.attr("TORA_TSTP_D_Split") = TORA_TSTP_D_Split;
    parent.attr("TORA_TSTP_D_Merge") = TORA_TSTP_D_Merge;
    parent.attr("TORA_TSTP_D_MarginBuy") = TORA_TSTP_D_MarginBuy;
    parent.attr("TORA_TSTP_D_ShortSell") = TORA_TSTP_D_ShortSell;
    parent.attr("TORA_TSTP_D_SellRepayment") = TORA_TSTP_D_SellRepayment;
    parent.attr("TORA_TSTP_D_BuyRepayment") = TORA_TSTP_D_BuyRepayment;
    parent.attr("TORA_TSTP_D_SecurityRepay") = TORA_TSTP_D_SecurityRepay;
    parent.attr("TORA_TSTP_D_RemainTransfer") = TORA_TSTP_D_RemainTransfer;
    parent.attr("TORA_TSTP_D_BondConvertStock") = TORA_TSTP_D_BondConvertStock;
    parent.attr("TORA_TSTP_D_BondPutback") = TORA_TSTP_D_BondPutback;
    parent.attr("TORA_TSTP_BT_Gross") = TORA_TSTP_BT_Gross;
    parent.attr("TORA_TSTP_BT_Net") = TORA_TSTP_BT_Net;
    parent.attr("TORA_TSTP_UTYPE_BrokerUser") = TORA_TSTP_UTYPE_BrokerUser;
    parent.attr("TORA_TSTP_UTYPE_SuperUser") = TORA_TSTP_UTYPE_SuperUser;
    parent.attr("TORA_TSTP_UTYPE_Investor") = TORA_TSTP_UTYPE_Investor;
    parent.attr("TORA_TSTP_CC_TradeTouch") = TORA_TSTP_CC_TradeTouch;
    parent.attr("TORA_TSTP_CC_CancelTouch") = TORA_TSTP_CC_CancelTouch;
    parent.attr("TORA_TSTP_CC_TimeTouch") = TORA_TSTP_CC_TimeTouch;
    parent.attr("TORA_TSTP_CC_SegmentTouch") = TORA_TSTP_CC_SegmentTouch;
    parent.attr("TORA_TSTP_CC_LastPriceGreaterThanStopPrice") = TORA_TSTP_CC_LastPriceGreaterThanStopPrice;
    parent.attr("TORA_TSTP_CC_LastPriceLesserThanStopPrice") = TORA_TSTP_CC_LastPriceLesserThanStopPrice;
    parent.attr("TORA_TSTP_CC_AskPriceGreaterEqualStopPrice") = TORA_TSTP_CC_AskPriceGreaterEqualStopPrice;
    parent.attr("TORA_TSTP_CC_AskPriceLesserEqualStopPrice") = TORA_TSTP_CC_AskPriceLesserEqualStopPrice;
    parent.attr("TORA_TSTP_CC_BidPriceGreaterEqualStopPrice") = TORA_TSTP_CC_BidPriceGreaterEqualStopPrice;
    parent.attr("TORA_TSTP_CC_BidPriceLesserEqualStopPrice") = TORA_TSTP_CC_BidPriceLesserEqualStopPrice;
    parent.attr("TORA_TSTP_ETFCTSTAT_Forbidden") = TORA_TSTP_ETFCTSTAT_Forbidden;
    parent.attr("TORA_TSTP_ETFCTSTAT_Allow") = TORA_TSTP_ETFCTSTAT_Allow;
    parent.attr("TORA_TSTP_ETFCTSTAT_Force") = TORA_TSTP_ETFCTSTAT_Force;
    parent.attr("TORA_TSTP_ETFCTSTAT_CBAllow") = TORA_TSTP_ETFCTSTAT_CBAllow;
    parent.attr("TORA_TSTP_ETFCTSTAT_CBForce") = TORA_TSTP_ETFCTSTAT_CBForce;
    parent.attr("TORA_TSTP_OPRTSRC_DBCommand") = TORA_TSTP_OPRTSRC_DBCommand;
    parent.attr("TORA_TSTP_OPRTSRC_SyncAPI") = TORA_TSTP_OPRTSRC_SyncAPI;
    parent.attr("TORA_TSTP_OPERW_Telephone") = TORA_TSTP_OPERW_Telephone;
    parent.attr("TORA_TSTP_OPERW_OTC") = TORA_TSTP_OPERW_OTC;
    parent.attr("TORA_TSTP_OPERW_MobileClient") = TORA_TSTP_OPERW_MobileClient;
    parent.attr("TORA_TSTP_OPERW_PCClient") = TORA_TSTP_OPERW_PCClient;
    parent.attr("TORA_TSTP_OPERW_TY") = TORA_TSTP_OPERW_TY;
    parent.attr("TORA_TSTP_OPT_AnyPrice") = TORA_TSTP_OPT_AnyPrice;
    parent.attr("TORA_TSTP_OPT_LimitPrice") = TORA_TSTP_OPT_LimitPrice;
    parent.attr("TORA_TSTP_OPT_BestPrice") = TORA_TSTP_OPT_BestPrice;
    parent.attr("TORA_TSTP_OPT_LastPrice") = TORA_TSTP_OPT_LastPrice;
    parent.attr("TORA_TSTP_OPT_AskPrice1") = TORA_TSTP_OPT_AskPrice1;
    parent.attr("TORA_TSTP_OPT_BidPrice1") = TORA_TSTP_OPT_BidPrice1;
    parent.attr("TORA_TSTP_OPT_Relative") = TORA_TSTP_OPT_Relative;
    parent.attr("TORA_TSTP_OPT_FiveLevelPrice") = TORA_TSTP_OPT_FiveLevelPrice;
    parent.attr("TORA_TSTP_OPT_HomeBestPrice") = TORA_TSTP_OPT_HomeBestPrice;
    parent.attr("TORA_TSTP_OVT_CustomVol") = TORA_TSTP_OVT_CustomVol;
    parent.attr("TORA_TSTP_OVT_RelativeVol") = TORA_TSTP_OVT_RelativeVol;
    parent.attr("TORA_TSTP_TC_IOC") = TORA_TSTP_TC_IOC;
    parent.attr("TORA_TSTP_TC_GFS") = TORA_TSTP_TC_GFS;
    parent.attr("TORA_TSTP_TC_GFD") = TORA_TSTP_TC_GFD;
    parent.attr("TORA_TSTP_TC_GTD") = TORA_TSTP_TC_GTD;
    parent.attr("TORA_TSTP_TC_GTC") = TORA_TSTP_TC_GTC;
    parent.attr("TORA_TSTP_TC_GFA") = TORA_TSTP_TC_GFA;
    parent.attr("TORA_TSTP_VC_AV") = TORA_TSTP_VC_AV;
    parent.attr("TORA_TSTP_VC_MV") = TORA_TSTP_VC_MV;
    parent.attr("TORA_TSTP_VC_CV") = TORA_TSTP_VC_CV;
    parent.attr("TORA_TSTP_FCC_NotForceClose") = TORA_TSTP_FCC_NotForceClose;
    parent.attr("TORA_TSTP_FCC_LackDeposit") = TORA_TSTP_FCC_LackDeposit;
    parent.attr("TORA_TSTP_FCC_ClientOverPositionLimit") = TORA_TSTP_FCC_ClientOverPositionLimit;
    parent.attr("TORA_TSTP_FCC_MemberOverPositionLimit") = TORA_TSTP_FCC_MemberOverPositionLimit;
    parent.attr("TORA_TSTP_FCC_NotMultiple") = TORA_TSTP_FCC_NotMultiple;
    parent.attr("TORA_TSTP_FCC_Violation") = TORA_TSTP_FCC_Violation;
    parent.attr("TORA_TSTP_FCC_Other") = TORA_TSTP_FCC_Other;
    parent.attr("TORA_TSTP_EOT_Review") = TORA_TSTP_EOT_Review;
    parent.attr("TORA_TSTP_EOT_Cancel") = TORA_TSTP_EOT_Cancel;
    parent.attr("TORA_TSTP_EOT_Limit") = TORA_TSTP_EOT_Limit;
    parent.attr("TORA_TSTP_EOT_FRC") = TORA_TSTP_EOT_FRC;
    parent.attr("TORA_TSTP_EOT_FRL") = TORA_TSTP_EOT_FRL;
    parent.attr("TORA_TSTP_EOT_BP") = TORA_TSTP_EOT_BP;
    parent.attr("TORA_TSTP_EOT_HP") = TORA_TSTP_EOT_HP;
    parent.attr("TORA_TSTP_EOT_FAK") = TORA_TSTP_EOT_FAK;
    parent.attr("TORA_TSTP_EOT_FOK") = TORA_TSTP_EOT_FOK;
    parent.attr("TORA_TSTP_TRNSD_In") = TORA_TSTP_TRNSD_In;
    parent.attr("TORA_TSTP_TRNSD_Out") = TORA_TSTP_TRNSD_Out;
    parent.attr("TORA_TSTP_TRNSD_MoveIn") = TORA_TSTP_TRNSD_MoveIn;
    parent.attr("TORA_TSTP_TRNSD_MoveOut") = TORA_TSTP_TRNSD_MoveOut;
    parent.attr("TORA_TSTP_TRNSD_Freeze") = TORA_TSTP_TRNSD_Freeze;
    parent.attr("TORA_TSTP_TRNSD_UnFreeze") = TORA_TSTP_TRNSD_UnFreeze;
    parent.attr("TORA_TSTP_TRNSD_StockToBank") = TORA_TSTP_TRNSD_StockToBank;
    parent.attr("TORA_TSTP_TRNSD_BankToStock") = TORA_TSTP_TRNSD_BankToStock;
    parent.attr("TORA_TSTP_CLTD_CollateralIn") = TORA_TSTP_CLTD_CollateralIn;
    parent.attr("TORA_TSTP_CLTD_CollateralOut") = TORA_TSTP_CLTD_CollateralOut;
    parent.attr("TORA_TSTP_TRANST_TranferHandling") = TORA_TSTP_TRANST_TranferHandling;
    parent.attr("TORA_TSTP_TRANST_TransferSuccess") = TORA_TSTP_TRANST_TransferSuccess;
    parent.attr("TORA_TSTP_TRANST_TransferFail") = TORA_TSTP_TRANST_TransferFail;
    parent.attr("TORA_TSTP_TRANST_RepealHandling") = TORA_TSTP_TRANST_RepealHandling;
    parent.attr("TORA_TSTP_TRANST_RepealSuccess") = TORA_TSTP_TRANST_RepealSuccess;
    parent.attr("TORA_TSTP_TRANST_RepealFail") = TORA_TSTP_TRANST_RepealFail;
    parent.attr("TORA_TSTP_TRANST_ExternalAccepted") = TORA_TSTP_TRANST_ExternalAccepted;
    parent.attr("TORA_TSTP_TPT_ALL") = TORA_TSTP_TPT_ALL;
    parent.attr("TORA_TSTP_TPT_History") = TORA_TSTP_TPT_History;
    parent.attr("TORA_TSTP_TPT_TodayBS") = TORA_TSTP_TPT_TodayBS;
    parent.attr("TORA_TSTP_TPT_TodayPR") = TORA_TSTP_TPT_TodayPR;
    parent.attr("TORA_TSTP_OST_AllTraded") = TORA_TSTP_OST_AllTraded;
    parent.attr("TORA_TSTP_OST_PartTradedQueueing") = TORA_TSTP_OST_PartTradedQueueing;
    parent.attr("TORA_TSTP_OST_PartTradedNotQueueing") = TORA_TSTP_OST_PartTradedNotQueueing;
    parent.attr("TORA_TSTP_OST_NoTradeQueueing") = TORA_TSTP_OST_NoTradeQueueing;
    parent.attr("TORA_TSTP_OST_NoTradeNotQueueing") = TORA_TSTP_OST_NoTradeNotQueueing;
    parent.attr("TORA_TSTP_OST_Canceled") = TORA_TSTP_OST_Canceled;
    parent.attr("TORA_TSTP_OST_Unknown") = TORA_TSTP_OST_Unknown;
    parent.attr("TORA_TSTP_OST_NotTouched") = TORA_TSTP_OST_NotTouched;
    parent.attr("TORA_TSTP_OST_Touched") = TORA_TSTP_OST_Touched;
    parent.attr("TORA_TSTP_OST_Cached") = TORA_TSTP_OST_Cached;
    parent.attr("TORA_TSTP_COST_Initial") = TORA_TSTP_COST_Initial;
    parent.attr("TORA_TSTP_COST_NotTouched") = TORA_TSTP_COST_NotTouched;
    parent.attr("TORA_TSTP_COST_Touched") = TORA_TSTP_COST_Touched;
    parent.attr("TORA_TSTP_COST_Finished") = TORA_TSTP_COST_Finished;
    parent.attr("TORA_TSTP_COST_Cancel") = TORA_TSTP_COST_Cancel;
    parent.attr("TORA_TSTP_COST_Failed") = TORA_TSTP_COST_Failed;
    parent.attr("TORA_TSTP_OSS_UnSubmit") = TORA_TSTP_OSS_UnSubmit;
    parent.attr("TORA_TSTP_OSS_InsertSubmitted") = TORA_TSTP_OSS_InsertSubmitted;
    parent.attr("TORA_TSTP_OSS_CancelSubmitted") = TORA_TSTP_OSS_CancelSubmitted;
    parent.attr("TORA_TSTP_OSS_ModifySubmitted") = TORA_TSTP_OSS_ModifySubmitted;
    parent.attr("TORA_TSTP_OSS_Accepted") = TORA_TSTP_OSS_Accepted;
    parent.attr("TORA_TSTP_OSS_InsertRejected") = TORA_TSTP_OSS_InsertRejected;
    parent.attr("TORA_TSTP_OSS_CancelRejected") = TORA_TSTP_OSS_CancelRejected;
    parent.attr("TORA_TSTP_OSS_ModifyRejected") = TORA_TSTP_OSS_ModifyRejected;
    parent.attr("TORA_TSTP_ORDT_Normal") = TORA_TSTP_ORDT_Normal;
    parent.attr("TORA_TSTP_ORDT_DeriveFromQuote") = TORA_TSTP_ORDT_DeriveFromQuote;
    parent.attr("TORA_TSTP_ORDT_DeriveFromCombination") = TORA_TSTP_ORDT_DeriveFromCombination;
    parent.attr("TORA_TSTP_ORDT_Combination") = TORA_TSTP_ORDT_Combination;
    parent.attr("TORA_TSTP_ORDT_ConditionalOrder") = TORA_TSTP_ORDT_ConditionalOrder;
    parent.attr("TORA_TSTP_ORDT_Swap") = TORA_TSTP_ORDT_Swap;
    parent.attr("TORA_TSTP_OF_Open") = TORA_TSTP_OF_Open;
    parent.attr("TORA_TSTP_OF_Close") = TORA_TSTP_OF_Close;
    parent.attr("TORA_TSTP_OF_ForceClose") = TORA_TSTP_OF_ForceClose;
    parent.attr("TORA_TSTP_OF_CloseToday") = TORA_TSTP_OF_CloseToday;
    parent.attr("TORA_TSTP_OF_CloseYesterday") = TORA_TSTP_OF_CloseYesterday;
    parent.attr("TORA_TSTP_OF_ForceOff") = TORA_TSTP_OF_ForceOff;
    parent.attr("TORA_TSTP_OF_LocalForceClose") = TORA_TSTP_OF_LocalForceClose;
    parent.attr("TORA_TSTP_HF_Speculation") = TORA_TSTP_HF_Speculation;
    parent.attr("TORA_TSTP_HF_Arbitrage") = TORA_TSTP_HF_Arbitrage;
    parent.attr("TORA_TSTP_HF_Hedge") = TORA_TSTP_HF_Hedge;
    parent.attr("TORA_TSTP_HF_Covered") = TORA_TSTP_HF_Covered;
    parent.attr("TORA_TSTP_AF_Delete") = TORA_TSTP_AF_Delete;
    parent.attr("TORA_TSTP_AF_Modify") = TORA_TSTP_AF_Modify;
    parent.attr("TORA_TSTP_AF_ForceDelete") = TORA_TSTP_AF_ForceDelete;
    parent.attr("TORA_TSTP_OAS_Submitted") = TORA_TSTP_OAS_Submitted;
    parent.attr("TORA_TSTP_OAS_Accepted") = TORA_TSTP_OAS_Accepted;
    parent.attr("TORA_TSTP_OAS_Rejected") = TORA_TSTP_OAS_Rejected;
    parent.attr("TORA_TSTP_OAS_Cached") = TORA_TSTP_OAS_Cached;
    parent.attr("TORA_TSTP_CIDT_Unknown") = TORA_TSTP_CIDT_Unknown;
    parent.attr("TORA_TSTP_CIDT_Speculation") = TORA_TSTP_CIDT_Speculation;
    parent.attr("TORA_TSTP_CIDT_Arbitrage") = TORA_TSTP_CIDT_Arbitrage;
    parent.attr("TORA_TSTP_CIDT_Hedge") = TORA_TSTP_CIDT_Hedge;
    parent.attr("TORA_TSTP_CIDT_Normal") = TORA_TSTP_CIDT_Normal;
    parent.attr("TORA_TSTP_CIDT_Credit") = TORA_TSTP_CIDT_Credit;
    parent.attr("TORA_TSTP_CIDT_Derivatives") = TORA_TSTP_CIDT_Derivatives;
    parent.attr("TORA_TSTP_BC_Buy") = TORA_TSTP_BC_Buy;
    parent.attr("TORA_TSTP_BC_Sell") = TORA_TSTP_BC_Sell;
    parent.attr("TORA_TSTP_BC_ETFPur") = TORA_TSTP_BC_ETFPur;
    parent.attr("TORA_TSTP_BC_ETFRed") = TORA_TSTP_BC_ETFRed;
    parent.attr("TORA_TSTP_BC_Repurchase") = TORA_TSTP_BC_Repurchase;
    parent.attr("TORA_TSTP_BC_ReverseRepur") = TORA_TSTP_BC_ReverseRepur;
    parent.attr("TORA_TSTP_BC_Rationed") = TORA_TSTP_BC_Rationed;
    parent.attr("TORA_TSTP_BC_CustodyTransfer") = TORA_TSTP_BC_CustodyTransfer;
    parent.attr("TORA_TSTP_BC_BuyOpen") = TORA_TSTP_BC_BuyOpen;
    parent.attr("TORA_TSTP_BC_BuyClose") = TORA_TSTP_BC_BuyClose;
    parent.attr("TORA_TSTP_BC_SellOpen") = TORA_TSTP_BC_SellOpen;
    parent.attr("TORA_TSTP_BC_SellClose") = TORA_TSTP_BC_SellClose;
    parent.attr("TORA_TSTP_BC_CoveredOpen") = TORA_TSTP_BC_CoveredOpen;
    parent.attr("TORA_TSTP_BC_CoveredClose") = TORA_TSTP_BC_CoveredClose;
    parent.attr("TORA_TSTP_BC_ExecOrder") = TORA_TSTP_BC_ExecOrder;
    parent.attr("TORA_TSTP_BC_AutoExecOrder") = TORA_TSTP_BC_AutoExecOrder;
    parent.attr("TORA_TSTP_CPT_Normal") = TORA_TSTP_CPT_Normal;
    parent.attr("TORA_TSTP_CPT_Special") = TORA_TSTP_CPT_Special;
    parent.attr("TORA_TSTP_FID_NAN") = TORA_TSTP_FID_NAN;
    parent.attr("TORA_TSTP_FID_SessionManager") = TORA_TSTP_FID_SessionManager;
    parent.attr("TORA_TSTP_FID_UserManager") = TORA_TSTP_FID_UserManager;
    parent.attr("TORA_TSTP_FID_OrderInsert") = TORA_TSTP_FID_OrderInsert;
    parent.attr("TORA_TSTP_FID_OrderAction") = TORA_TSTP_FID_OrderAction;
    parent.attr("TORA_TSTP_FID_AdjustTradingRight") = TORA_TSTP_FID_AdjustTradingRight;
    parent.attr("TORA_TSTP_FID_MoveFund") = TORA_TSTP_FID_MoveFund;
    parent.attr("TORA_TSTP_FID_AddFund") = TORA_TSTP_FID_AddFund;
    parent.attr("TORA_TSTP_FID_SubFund") = TORA_TSTP_FID_SubFund;
    parent.attr("TORA_TSTP_FID_ForceFreezeFund") = TORA_TSTP_FID_ForceFreezeFund;
    parent.attr("TORA_TSTP_FID_ForceUnFreezeFund") = TORA_TSTP_FID_ForceUnFreezeFund;
    parent.attr("TORA_TSTP_FID_AddPosition") = TORA_TSTP_FID_AddPosition;
    parent.attr("TORA_TSTP_FID_SubPosition") = TORA_TSTP_FID_SubPosition;
    parent.attr("TORA_TSTP_FID_RepealFund") = TORA_TSTP_FID_RepealFund;
    parent.attr("TORA_TSTP_FID_RepealPosition") = TORA_TSTP_FID_RepealPosition;
    parent.attr("TORA_TSTP_FID_CollateralInJZ") = TORA_TSTP_FID_CollateralInJZ;
    parent.attr("TORA_TSTP_FID_AdjustTradingFee") = TORA_TSTP_FID_AdjustTradingFee;
    parent.attr("TORA_TSTP_FID_AdjustSpecPrivilege") = TORA_TSTP_FID_AdjustSpecPrivilege;
    parent.attr("TORA_TSTP_FID_AdjustShareholderAssociation") = TORA_TSTP_FID_AdjustShareholderAssociation;
    parent.attr("TORA_TSTP_FID_AdjustSecurity") = TORA_TSTP_FID_AdjustSecurity;
    parent.attr("TORA_TSTP_FID_MovePosition") = TORA_TSTP_FID_MovePosition;
    parent.attr("TORA_TSTP_FID_AdjustShareholderParam") = TORA_TSTP_FID_AdjustShareholderParam;
    parent.attr("TORA_TSTP_FID_CondOrderInsert") = TORA_TSTP_FID_CondOrderInsert;
    parent.attr("TORA_TSTP_FID_CondOrderAction") = TORA_TSTP_FID_CondOrderAction;
    parent.attr("TORA_TSTP_FID_QryCondOrder") = TORA_TSTP_FID_QryCondOrder;
    parent.attr("TORA_TSTP_FID_CondParamAdjust") = TORA_TSTP_FID_CondParamAdjust;
    parent.attr("TORA_TSTP_FID_UserRoleManage") = TORA_TSTP_FID_UserRoleManage;
    parent.attr("TORA_TSTP_FID_TradingFeeTemplateManage") = TORA_TSTP_FID_TradingFeeTemplateManage;
    parent.attr("TORA_TSTP_FID_TradingRightTemplateManage") = TORA_TSTP_FID_TradingRightTemplateManage;
    parent.attr("TORA_TSTP_FID_SecurityPriorAuthManage") = TORA_TSTP_FID_SecurityPriorAuthManage;
    parent.attr("TORA_TSTP_FID_PosiParamManage") = TORA_TSTP_FID_PosiParamManage;
    parent.attr("TORA_TSTP_FID_OrderLocalSeqPrefixAdjust") = TORA_TSTP_FID_OrderLocalSeqPrefixAdjust;
    parent.attr("TORA_TSTP_FID_TraderManage") = TORA_TSTP_FID_TraderManage;
    parent.attr("TORA_TSTP_FID_IPOManage") = TORA_TSTP_FID_IPOManage;
    parent.attr("TORA_TSTP_FID_AppRunManage") = TORA_TSTP_FID_AppRunManage;
    parent.attr("TORA_TSTP_FID_MarketStatusManage") = TORA_TSTP_FID_MarketStatusManage;
    parent.attr("TORA_TSTP_FID_PlatformStatusManage") = TORA_TSTP_FID_PlatformStatusManage;
    parent.attr("TORA_TSTP_FID_QryTradingAccount") = TORA_TSTP_FID_QryTradingAccount;
    parent.attr("TORA_TSTP_FID_QryPositon") = TORA_TSTP_FID_QryPositon;
    parent.attr("TORA_TSTP_FID_QryShareholderAccount") = TORA_TSTP_FID_QryShareholderAccount;
    parent.attr("TORA_TSTP_FID_QryOrder") = TORA_TSTP_FID_QryOrder;
    parent.attr("TORA_TSTP_FID_QryTrade") = TORA_TSTP_FID_QryTrade;
    parent.attr("TORA_TSTP_FID_QryFundSerial") = TORA_TSTP_FID_QryFundSerial;
    parent.attr("TORA_TSTP_FID_QryPositionSerial") = TORA_TSTP_FID_QryPositionSerial;
    parent.attr("TORA_TSTP_FID_DumpTradingAccount") = TORA_TSTP_FID_DumpTradingAccount;
    parent.attr("TORA_TSTP_FID_DumpPositon") = TORA_TSTP_FID_DumpPositon;
    parent.attr("TORA_TSTP_FID_DumpShareholderAccount") = TORA_TSTP_FID_DumpShareholderAccount;
    parent.attr("TORA_TSTP_FID_DumpOrder") = TORA_TSTP_FID_DumpOrder;
    parent.attr("TORA_TSTP_FID_DumpTrade") = TORA_TSTP_FID_DumpTrade;
    parent.attr("TORA_TSTP_FID_DumpFundSerial") = TORA_TSTP_FID_DumpFundSerial;
    parent.attr("TORA_TSTP_FID_DumpPositionSerial") = TORA_TSTP_FID_DumpPositionSerial;
    parent.attr("TORA_TSTP_FID_UploadTradeData") = TORA_TSTP_FID_UploadTradeData;
    parent.attr("TORA_TSTP_FID_ReviewFundAdjust") = TORA_TSTP_FID_ReviewFundAdjust;
    parent.attr("TORA_TSTP_FID_ReviewPositionAdjust") = TORA_TSTP_FID_ReviewPositionAdjust;
    parent.attr("TORA_TSTP_FID_RecordOperateLog") = TORA_TSTP_FID_RecordOperateLog;
    parent.attr("TORA_TSTP_FID_TerminalInfoManage") = TORA_TSTP_FID_TerminalInfoManage;
    parent.attr("TORA_TSTP_FID_QryTradingRight") = TORA_TSTP_FID_QryTradingRight;
    parent.attr("TORA_TSTP_FID_DesignationRegistration") = TORA_TSTP_FID_DesignationRegistration;
    parent.attr("TORA_TSTP_FID_CustodyTransfer") = TORA_TSTP_FID_CustodyTransfer;
    parent.attr("TORA_TSTP_FID_ForceDelete") = TORA_TSTP_FID_ForceDelete;
    parent.attr("TORA_TSTP_FID_RiskMgr") = TORA_TSTP_FID_RiskMgr;
    parent.attr("TORA_TSTP_FID_ReviewUserIPLimitAdjust") = TORA_TSTP_FID_ReviewUserIPLimitAdjust;
    parent.attr("TORA_TSTP_FID_AdjustUserIPLimit") = TORA_TSTP_FID_AdjustUserIPLimit;
    parent.attr("TORA_TSTP_FID_AdjustSystemParam") = TORA_TSTP_FID_AdjustSystemParam;
    parent.attr("TORA_TSTP_FID_DepartmentInfoManage") = TORA_TSTP_FID_DepartmentInfoManage;
    parent.attr("TORA_TSTP_FID_IPONumberMatchManage") = TORA_TSTP_FID_IPONumberMatchManage;
    parent.attr("TORA_TSTP_FID_CustomerInfoManage") = TORA_TSTP_FID_CustomerInfoManage;
    parent.attr("TORA_TSTP_FID_QryTradeEvent") = TORA_TSTP_FID_QryTradeEvent;
    parent.attr("TORA_TSTP_FID_ExchRtnSeqManage") = TORA_TSTP_FID_ExchRtnSeqManage;
    parent.attr("TORA_TSTP_FID_TransferFund") = TORA_TSTP_FID_TransferFund;
    parent.attr("TORA_TSTP_STP_COMMON") = TORA_TSTP_STP_COMMON;
    parent.attr("TORA_TSTP_STP_SHAShares") = TORA_TSTP_STP_SHAShares;
    parent.attr("TORA_TSTP_STP_SHSingleMarketStockETF") = TORA_TSTP_STP_SHSingleMarketStockETF;
    parent.attr("TORA_TSTP_STP_SHSingleMarketBondETF") = TORA_TSTP_STP_SHSingleMarketBondETF;
    parent.attr("TORA_TSTP_STP_SHGoldETF") = TORA_TSTP_STP_SHGoldETF;
    parent.attr("TORA_TSTP_STP_SHTradableMonetaryFund") = TORA_TSTP_STP_SHTradableMonetaryFund;
    parent.attr("TORA_TSTP_STP_SHBondNation") = TORA_TSTP_STP_SHBondNation;
    parent.attr("TORA_TSTP_STP_SHBondCorporation") = TORA_TSTP_STP_SHBondCorporation;
    parent.attr("TORA_TSTP_STP_SHBondCompany") = TORA_TSTP_STP_SHBondCompany;
    parent.attr("TORA_TSTP_STP_SHBondConversion") = TORA_TSTP_STP_SHBondConversion;
    parent.attr("TORA_TSTP_STP_SHBondSeparation") = TORA_TSTP_STP_SHBondSeparation;
    parent.attr("TORA_TSTP_STP_SHASharesOption") = TORA_TSTP_STP_SHASharesOption;
    parent.attr("TORA_TSTP_STP_SHETFOption") = TORA_TSTP_STP_SHETFOption;
    parent.attr("TORA_TSTP_STP_SHAllotment") = TORA_TSTP_STP_SHAllotment;
    parent.attr("TORA_TSTP_STP_SHDistributeDebt") = TORA_TSTP_STP_SHDistributeDebt;
    parent.attr("TORA_TSTP_STP_SHStandard") = TORA_TSTP_STP_SHStandard;
    parent.attr("TORA_TSTP_STP_SHRepo") = TORA_TSTP_STP_SHRepo;
    parent.attr("TORA_TSTP_STP_SHCEFund") = TORA_TSTP_STP_SHCEFund;
    parent.attr("TORA_TSTP_STP_SHOEFund") = TORA_TSTP_STP_SHOEFund;
    parent.attr("TORA_TSTP_STP_SHCrossMarketStockETF") = TORA_TSTP_STP_SHCrossMarketStockETF;
    parent.attr("TORA_TSTP_STP_SHCrossBorderETF") = TORA_TSTP_STP_SHCrossBorderETF;
    parent.attr("TORA_TSTP_STP_SHMontherStructFund") = TORA_TSTP_STP_SHMontherStructFund;
    parent.attr("TORA_TSTP_STP_SHSubStructFund") = TORA_TSTP_STP_SHSubStructFund;
    parent.attr("TORA_TSTP_STP_SHRealTimeMonetaryFund") = TORA_TSTP_STP_SHRealTimeMonetaryFund;
    parent.attr("TORA_TSTP_STP_SHExchangeableBond") = TORA_TSTP_STP_SHExchangeableBond;
    parent.attr("TORA_TSTP_STP_SHLOF") = TORA_TSTP_STP_SHLOF;
    parent.attr("TORA_TSTP_STP_SZMainAShares") = TORA_TSTP_STP_SZMainAShares;
    parent.attr("TORA_TSTP_STP_SZSME") = TORA_TSTP_STP_SZSME;
    parent.attr("TORA_TSTP_STP_SZBondNation") = TORA_TSTP_STP_SZBondNation;
    parent.attr("TORA_TSTP_STP_SZBondCorporation") = TORA_TSTP_STP_SZBondCorporation;
    parent.attr("TORA_TSTP_STP_SZBondCompany") = TORA_TSTP_STP_SZBondCompany;
    parent.attr("TORA_TSTP_STP_SZBondConversion") = TORA_TSTP_STP_SZBondConversion;
    parent.attr("TORA_TSTP_STP_SZBondSeparation") = TORA_TSTP_STP_SZBondSeparation;
    parent.attr("TORA_TSTP_STP_SZASharesOption") = TORA_TSTP_STP_SZASharesOption;
    parent.attr("TORA_TSTP_STP_SZETFOption") = TORA_TSTP_STP_SZETFOption;
    parent.attr("TORA_TSTP_STP_SZCrossBorderETF") = TORA_TSTP_STP_SZCrossBorderETF;
    parent.attr("TORA_TSTP_STP_SZGoldETF") = TORA_TSTP_STP_SZGoldETF;
    parent.attr("TORA_TSTP_STP_SZCashBondETF") = TORA_TSTP_STP_SZCashBondETF;
    parent.attr("TORA_TSTP_STP_SZSingleMarketStockETF") = TORA_TSTP_STP_SZSingleMarketStockETF;
    parent.attr("TORA_TSTP_STP_SZSingleMarketBondETF") = TORA_TSTP_STP_SZSingleMarketBondETF;
    parent.attr("TORA_TSTP_STP_SZMonetaryFundETF") = TORA_TSTP_STP_SZMonetaryFundETF;
    parent.attr("TORA_TSTP_STP_SZGEM") = TORA_TSTP_STP_SZGEM;
    parent.attr("TORA_TSTP_STP_SZAllotment") = TORA_TSTP_STP_SZAllotment;
    parent.attr("TORA_TSTP_STP_SZDistributeDebt") = TORA_TSTP_STP_SZDistributeDebt;
    parent.attr("TORA_TSTP_STP_SZStandard") = TORA_TSTP_STP_SZStandard;
    parent.attr("TORA_TSTP_STP_SZRepo") = TORA_TSTP_STP_SZRepo;
    parent.attr("TORA_TSTP_STP_SZCEFund") = TORA_TSTP_STP_SZCEFund;
    parent.attr("TORA_TSTP_STP_SZOEFund") = TORA_TSTP_STP_SZOEFund;
    parent.attr("TORA_TSTP_STP_SZCrossBorderOEFund") = TORA_TSTP_STP_SZCrossBorderOEFund;
    parent.attr("TORA_TSTP_STP_SZCrossMarketStockETF") = TORA_TSTP_STP_SZCrossMarketStockETF;
    parent.attr("TORA_TSTP_STP_SZLOF") = TORA_TSTP_STP_SZLOF;
    parent.attr("TORA_TSTP_STP_SZCrossBorderLOF") = TORA_TSTP_STP_SZCrossBorderLOF;
    parent.attr("TORA_TSTP_STP_SZMontherStructFund") = TORA_TSTP_STP_SZMontherStructFund;
    parent.attr("TORA_TSTP_STP_SZSubStructFund") = TORA_TSTP_STP_SZSubStructFund;
    parent.attr("TORA_TSTP_STP_SZMontherCrossBorderStructFund") = TORA_TSTP_STP_SZMontherCrossBorderStructFund;
    parent.attr("TORA_TSTP_STP_SZSubCrossBorderStructFund") = TORA_TSTP_STP_SZSubCrossBorderStructFund;
    parent.attr("TORA_TSTP_STP_SZExchangeableBond") = TORA_TSTP_STP_SZExchangeableBond;
    parent.attr("TORA_TSTP_STP_SZGEMConversionBond") = TORA_TSTP_STP_SZGEMConversionBond;
    parent.attr("TORA_TSTP_EF_ToBeContinued") = TORA_TSTP_EF_ToBeContinued;
    parent.attr("TORA_TSTP_EF_BatchEnd") = TORA_TSTP_EF_BatchEnd;
    parent.attr("TORA_TSTP_EF_Completed") = TORA_TSTP_EF_Completed;
    parent.attr("TORA_TSTP_EF_NOP") = TORA_TSTP_EF_NOP;
    parent.attr("TORA_TSTP_MKD_COMMON") = TORA_TSTP_MKD_COMMON;
    parent.attr("TORA_TSTP_MKD_SHA") = TORA_TSTP_MKD_SHA;
    parent.attr("TORA_TSTP_MKD_SZA") = TORA_TSTP_MKD_SZA;
    parent.attr("TORA_TSTP_MKD_SHB") = TORA_TSTP_MKD_SHB;
    parent.attr("TORA_TSTP_MKD_SZB") = TORA_TSTP_MKD_SZB;
    parent.attr("TORA_TSTP_MKD_SZThreeA") = TORA_TSTP_MKD_SZThreeA;
    parent.attr("TORA_TSTP_MKD_SZThreeB") = TORA_TSTP_MKD_SZThreeB;
    parent.attr("TORA_TSTP_MKD_Foreign") = TORA_TSTP_MKD_Foreign;
    parent.attr("TORA_TSTP_LACT_UserID") = TORA_TSTP_LACT_UserID;
    parent.attr("TORA_TSTP_LACT_AccountID") = TORA_TSTP_LACT_AccountID;
    parent.attr("TORA_TSTP_LACT_SHAStock") = TORA_TSTP_LACT_SHAStock;
    parent.attr("TORA_TSTP_LACT_SZAStock") = TORA_TSTP_LACT_SZAStock;
    parent.attr("TORA_TSTP_LACT_SHBStock") = TORA_TSTP_LACT_SHBStock;
    parent.attr("TORA_TSTP_LACT_SZBStock") = TORA_TSTP_LACT_SZBStock;
    parent.attr("TORA_TSTP_LACT_ThreeNewBoardA") = TORA_TSTP_LACT_ThreeNewBoardA;
    parent.attr("TORA_TSTP_LACT_ThreeNewBoardB") = TORA_TSTP_LACT_ThreeNewBoardB;
    parent.attr("TORA_TSTP_LACT_HKStock") = TORA_TSTP_LACT_HKStock;
    parent.attr("TORA_TSTP_MST_UnKnown") = TORA_TSTP_MST_UnKnown;
    parent.attr("TORA_TSTP_MST_BeforeTrading") = TORA_TSTP_MST_BeforeTrading;
    parent.attr("TORA_TSTP_MST_Continous") = TORA_TSTP_MST_Continous;
    parent.attr("TORA_TSTP_MST_Closed") = TORA_TSTP_MST_Closed;
    parent.attr("TORA_TSTP_MST_OpenCallAuction") = TORA_TSTP_MST_OpenCallAuction;
    parent.attr("TORA_TSTP_ARM_Single") = TORA_TSTP_ARM_Single;
    parent.attr("TORA_TSTP_ARM_Group") = TORA_TSTP_ARM_Group;
    parent.attr("TORA_TSTP_DT_Register") = TORA_TSTP_DT_Register;
    parent.attr("TORA_TSTP_DT_Cancel") = TORA_TSTP_DT_Cancel;
    parent.attr("TORA_TSTP_CT_Register") = TORA_TSTP_CT_Register;
    parent.attr("TORA_TSTP_CT_Cancel") = TORA_TSTP_CT_Cancel;
    parent.attr("TORA_TSTP_PCBT_None") = TORA_TSTP_PCBT_None;
    parent.attr("TORA_TSTP_PCBT_Other") = TORA_TSTP_PCBT_Other;
    parent.attr("TORA_TSTP_PCBT_SHDelisting") = TORA_TSTP_PCBT_SHDelisting;
    parent.attr("TORA_TSTP_PCBT_ST") = TORA_TSTP_PCBT_ST;
    parent.attr("TORA_TSTP_PCBT_GEM") = TORA_TSTP_PCBT_GEM;
    parent.attr("TORA_TSTP_PCBT_StructFund") = TORA_TSTP_PCBT_StructFund;
    parent.attr("TORA_TSTP_PCBT_BondQualified") = TORA_TSTP_PCBT_BondQualified;
    parent.attr("TORA_TSTP_PCBT_SuspendBond") = TORA_TSTP_PCBT_SuspendBond;
    parent.attr("TORA_TSTP_PCBT_Repurchase") = TORA_TSTP_PCBT_Repurchase;
    parent.attr("TORA_TSTP_PCBT_ReverseRepur") = TORA_TSTP_PCBT_ReverseRepur;
    parent.attr("TORA_TSTP_PCBT_SZDelisting") = TORA_TSTP_PCBT_SZDelisting;
    parent.attr("TORA_TSTP_PCBT_Stock") = TORA_TSTP_PCBT_Stock;
    parent.attr("TORA_TSTP_PCBT_CreditStock") = TORA_TSTP_PCBT_CreditStock;
    parent.attr("TORA_TSTP_PCPF_None") = TORA_TSTP_PCPF_None;
    parent.attr("TORA_TSTP_PCPF_AnywayPass") = TORA_TSTP_PCPF_AnywayPass;
    parent.attr("TORA_TSTP_PCPF_MatchPass") = TORA_TSTP_PCPF_MatchPass;
    parent.attr("TORA_TSTP_PCPF_SelectPass") = TORA_TSTP_PCPF_SelectPass;
    parent.attr("TORA_TSTP_PCPF_ProfInvestorPass") = TORA_TSTP_PCPF_ProfInvestorPass;
    parent.attr("TORA_TSTP_RLV_Lowest") = TORA_TSTP_RLV_Lowest;
    parent.attr("TORA_TSTP_RLV_Conservative") = TORA_TSTP_RLV_Conservative;
    parent.attr("TORA_TSTP_RLV_Cautious") = TORA_TSTP_RLV_Cautious;
    parent.attr("TORA_TSTP_RLV_Steady") = TORA_TSTP_RLV_Steady;
    parent.attr("TORA_TSTP_RLV_Positive") = TORA_TSTP_RLV_Positive;
    parent.attr("TORA_TSTP_RLV_Aggressive") = TORA_TSTP_RLV_Aggressive;
    parent.attr("TORA_TSTP_PIT_NotProf") = TORA_TSTP_PIT_NotProf;
    parent.attr("TORA_TSTP_PIT_OCInstiPro") = TORA_TSTP_PIT_OCInstiPro;
    parent.attr("TORA_TSTP_PIT_InstiPro") = TORA_TSTP_PIT_InstiPro;
    parent.attr("TORA_TSTP_PIT_PersonPro") = TORA_TSTP_PIT_PersonPro;
    parent.attr("TORA_TSTP_PIT_ConfirmInstiPro") = TORA_TSTP_PIT_ConfirmInstiPro;
    parent.attr("TORA_TSTP_PIT_ConfirmPersonPro") = TORA_TSTP_PIT_ConfirmPersonPro;
    parent.attr("TORA_TSTP_LOT_Market") = TORA_TSTP_LOT_Market;
    parent.attr("TORA_TSTP_LOT_Limit") = TORA_TSTP_LOT_Limit;
    parent.attr("TORA_TSTP_LOT_HomeBest") = TORA_TSTP_LOT_HomeBest;
    parent.attr("TORA_TSTP_LSD_Buy") = TORA_TSTP_LSD_Buy;
    parent.attr("TORA_TSTP_LSD_Sell") = TORA_TSTP_LSD_Sell;
    parent.attr("TORA_TSTP_LSD_Borrow") = TORA_TSTP_LSD_Borrow;
    parent.attr("TORA_TSTP_LSD_Lend") = TORA_TSTP_LSD_Lend;
    parent.attr("TORA_TSTP_ECT_Fill") = TORA_TSTP_ECT_Fill;
    parent.attr("TORA_TSTP_ECT_Cancel") = TORA_TSTP_ECT_Cancel;
    parent.attr("TORA_TSTP_CCT_None") = TORA_TSTP_CCT_None;
    parent.attr("TORA_TSTP_CCT_SelfDeal") = TORA_TSTP_CCT_SelfDeal;
    parent.attr("TORA_TSTP_MST_TCP") = TORA_TSTP_MST_TCP;
    parent.attr("TORA_TSTP_MST_UDP") = TORA_TSTP_MST_UDP;
    parent.attr("TORA_TSTP_MST_MCAST") = TORA_TSTP_MST_MCAST;
    parent.attr("TORA_TSTP_MSST_PreOpen") = TORA_TSTP_MSST_PreOpen;
    parent.attr("TORA_TSTP_MSST_CallAuction") = TORA_TSTP_MSST_CallAuction;
    parent.attr("TORA_TSTP_MSST_Continous") = TORA_TSTP_MSST_Continous;
    parent.attr("TORA_TSTP_MSST_Pause") = TORA_TSTP_MSST_Pause;
    parent.attr("TORA_TSTP_MSST_Suspend") = TORA_TSTP_MSST_Suspend;
    parent.attr("TORA_TSTP_MSST_LongSuspend") = TORA_TSTP_MSST_LongSuspend;
    parent.attr("TORA_TSTP_MSST_UndulationInt") = TORA_TSTP_MSST_UndulationInt;
    parent.attr("TORA_TSTP_MSST_CircuitBreak") = TORA_TSTP_MSST_CircuitBreak;
    parent.attr("TORA_TSTP_MSST_CircuitBreakU") = TORA_TSTP_MSST_CircuitBreakU;
    parent.attr("TORA_TSTP_MSST_Close") = TORA_TSTP_MSST_Close;
    parent.attr("TORA_TSTP_MSST_Other") = TORA_TSTP_MSST_Other;
    parent.attr("TORA_TSTP_MSST_CloseCallAuction") = TORA_TSTP_MSST_CloseCallAuction;
    parent.attr("TORA_TSTP_FOCS_Init") = TORA_TSTP_FOCS_Init;
    parent.attr("TORA_TSTP_FOCS_Reviewed") = TORA_TSTP_FOCS_Reviewed;
    parent.attr("TORA_TSTP_FOCS_Failed") = TORA_TSTP_FOCS_Failed;
    parent.attr("TORA_TSTP_SPT_MaxBuyLimit") = TORA_TSTP_SPT_MaxBuyLimit;
    parent.attr("TORA_TSTP_SPT_MaxSellLimit") = TORA_TSTP_SPT_MaxSellLimit;
    parent.attr("TORA_TSTP_SPT_LargeBuyLimitRatio") = TORA_TSTP_SPT_LargeBuyLimitRatio;
    parent.attr("TORA_TSTP_SPT_LargeSelLimitRatio") = TORA_TSTP_SPT_LargeSelLimitRatio;
    parent.attr("TORA_TSTP_SPT_RiskWarnBoardLimitVol") = TORA_TSTP_SPT_RiskWarnBoardLimitVol;
    parent.attr("TORA_TSTP_SPT_SeriesDecInterval") = TORA_TSTP_SPT_SeriesDecInterval;
    parent.attr("TORA_TSTP_SPT_SeriesLimitPerUnit") = TORA_TSTP_SPT_SeriesLimitPerUnit;
    parent.attr("TORA_TSTP_SPT_ClosePriceScopeRatio") = TORA_TSTP_SPT_ClosePriceScopeRatio;
    parent.attr("TORA_TSTP_SPT_OpenDateLimit") = TORA_TSTP_SPT_OpenDateLimit;
    parent.attr("TORA_TSTP_SPT_LimitBoardShamRatio") = TORA_TSTP_SPT_LimitBoardShamRatio;
    parent.attr("TORA_TSTP_SPT_CancelOrderRatio") = TORA_TSTP_SPT_CancelOrderRatio;
    generate_caster_(parent);
}
