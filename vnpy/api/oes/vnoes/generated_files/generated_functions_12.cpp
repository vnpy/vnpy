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


void generate_vnoes_variables(pybind11::module & parent)
{
    // OES_APPL_VER_ID
    parent.attr("OES_APPL_VER_ID") = OES_APPL_VER_ID;
    // OES_MIN_APPL_VER_ID
    parent.attr("OES_MIN_APPL_VER_ID") = OES_MIN_APPL_VER_ID;
    // OESAPI_CFG_DEFAULT_SECTION
    parent.attr("OESAPI_CFG_DEFAULT_SECTION") = OESAPI_CFG_DEFAULT_SECTION;
    // OESAPI_CFG_DEFAULT_SECTION_LOGGER
    parent.attr("OESAPI_CFG_DEFAULT_SECTION_LOGGER") = OESAPI_CFG_DEFAULT_SECTION_LOGGER;
    // OESAPI_CFG_DEFAULT_KEY_ORD_ADDR
    parent.attr("OESAPI_CFG_DEFAULT_KEY_ORD_ADDR") = OESAPI_CFG_DEFAULT_KEY_ORD_ADDR;
    // OESAPI_CFG_DEFAULT_KEY_RPT_ADDR
    parent.attr("OESAPI_CFG_DEFAULT_KEY_RPT_ADDR") = OESAPI_CFG_DEFAULT_KEY_RPT_ADDR;
    // OESAPI_CFG_DEFAULT_KEY_QRY_ADDR
    parent.attr("OESAPI_CFG_DEFAULT_KEY_QRY_ADDR") = OESAPI_CFG_DEFAULT_KEY_QRY_ADDR;
    // OESAPI_DEFAULT_STRING_DELIM
    parent.attr("OESAPI_DEFAULT_STRING_DELIM") = OESAPI_DEFAULT_STRING_DELIM;
    // MDS_APPL_VER_ID
    parent.attr("MDS_APPL_VER_ID") = MDS_APPL_VER_ID;
    // MDS_MIN_APPL_VER_ID
    parent.attr("MDS_MIN_APPL_VER_ID") = MDS_MIN_APPL_VER_ID;
    // MDSAPI_CFG_DEFAULT_SECTION
    parent.attr("MDSAPI_CFG_DEFAULT_SECTION") = MDSAPI_CFG_DEFAULT_SECTION;
    // MDSAPI_CFG_DEFAULT_SECTION_LOGGER
    parent.attr("MDSAPI_CFG_DEFAULT_SECTION_LOGGER") = MDSAPI_CFG_DEFAULT_SECTION_LOGGER;
    // MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR") = MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR;
    // MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR") = MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR;
    // MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1;
    // MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2;
    // MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK1
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK1") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK1;
    // MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK2
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK2") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK2;
    // MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE;
    // MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER;
    // MDSAPI_DEFAULT_STRING_DELIM
    parent.attr("MDSAPI_DEFAULT_STRING_DELIM") = MDSAPI_DEFAULT_STRING_DELIM;
}
void generate_vnoes_typedefs(pybind11::module & parent)
{
    // eOesExchangeIdT
    module_vnoes::cross.record_assign(parent, "eOesExchangeIdT", "eOesExchangeIdT", "::_eOesExchangeId");
    // eOesMarketIdT
    module_vnoes::cross.record_assign(parent, "eOesMarketIdT", "eOesMarketIdT", "::_eOesMarketId");
    // eOesPlatformIdT
    module_vnoes::cross.record_assign(parent, "eOesPlatformIdT", "eOesPlatformIdT", "::_eOesPlatformId");
    // eOesMarketStateT
    module_vnoes::cross.record_assign(parent, "eOesMarketStateT", "eOesMarketStateT", "::_eOesMarketState");
    // eOesTrdSessTypeT
    module_vnoes::cross.record_assign(parent, "eOesTrdSessTypeT", "eOesTrdSessTypeT", "::_eOesTrdSessType");
    // eOesProductTypeT
    module_vnoes::cross.record_assign(parent, "eOesProductTypeT", "eOesProductTypeT", "::_eOesProductType");
    // eOesSecurityTypeT
    module_vnoes::cross.record_assign(parent, "eOesSecurityTypeT", "eOesSecurityTypeT", "::_eOesSecurityType");
    // eOesSubSecurityTypeT
    module_vnoes::cross.record_assign(parent, "eOesSubSecurityTypeT", "eOesSubSecurityTypeT", "::_eOesSubSecurityType");
    // eOesSecurityLevelT
    module_vnoes::cross.record_assign(parent, "eOesSecurityLevelT", "eOesSecurityLevelT", "::_eOesSecurityLevel");
    // eOesSecurityRiskLevelT
    module_vnoes::cross.record_assign(parent, "eOesSecurityRiskLevelT", "eOesSecurityRiskLevelT", "::_eOesSecurityRiskLevel");
    // eOesSecuritySuspFlagT
    module_vnoes::cross.record_assign(parent, "eOesSecuritySuspFlagT", "eOesSecuritySuspFlagT", "::_eOesSecuritySuspFlag");
    // eOesLotTypeT
    module_vnoes::cross.record_assign(parent, "eOesLotTypeT", "eOesLotTypeT", "::_eOesLotType");
    // eOesLotRejReasonT
    module_vnoes::cross.record_assign(parent, "eOesLotRejReasonT", "eOesLotRejReasonT", "::_eOesLotRejReason");
    // eOesOrdStatusT
    module_vnoes::cross.record_assign(parent, "eOesOrdStatusT", "eOesOrdStatusT", "::_eOesOrdStatus");
    // eOesOrdTypeT
    module_vnoes::cross.record_assign(parent, "eOesOrdTypeT", "eOesOrdTypeT", "::_eOesOrdType");
    // eOesOrdTypeShT
    module_vnoes::cross.record_assign(parent, "eOesOrdTypeShT", "eOesOrdTypeShT", "::_eOesOrdTypeSh");
    // eOesOrdTypeSzT
    module_vnoes::cross.record_assign(parent, "eOesOrdTypeSzT", "eOesOrdTypeSzT", "::_eOesOrdTypeSz");
    // eOesBuySellTypeT
    module_vnoes::cross.record_assign(parent, "eOesBuySellTypeT", "eOesBuySellTypeT", "::_eOesBuySellType");
    // eOesOrdDirT
    module_vnoes::cross.record_assign(parent, "eOesOrdDirT", "eOesOrdDirT", "::_eOesOrdDir");
    // eOesEtfTrdCnfmTypeT
    module_vnoes::cross.record_assign(parent, "eOesEtfTrdCnfmTypeT", "eOesEtfTrdCnfmTypeT", "::_eOesEtfTrdCnfmType");
    // eOesEtfSubFlagT
    module_vnoes::cross.record_assign(parent, "eOesEtfSubFlagT", "eOesEtfSubFlagT", "::_eOesEtfSubFlag");
    // eOesExecTypeT
    module_vnoes::cross.record_assign(parent, "eOesExecTypeT", "eOesExecTypeT", "::_eOesExecType");
    // eOesCurrTypeT
    module_vnoes::cross.record_assign(parent, "eOesCurrTypeT", "eOesCurrTypeT", "::_eOesCurrType");
    // eOesFeeTypeT
    module_vnoes::cross.record_assign(parent, "eOesFeeTypeT", "eOesFeeTypeT", "::_eOesFeeType");
    // eOesCalcFeeModeT
    module_vnoes::cross.record_assign(parent, "eOesCalcFeeModeT", "eOesCalcFeeModeT", "::_eOesCalcFeeMode");
    // eOesFundTrsfDirectT
    module_vnoes::cross.record_assign(parent, "eOesFundTrsfDirectT", "eOesFundTrsfDirectT", "::_eOesFundTrsfDirect");
    // eOesFundTrsfTypeT
    module_vnoes::cross.record_assign(parent, "eOesFundTrsfTypeT", "eOesFundTrsfTypeT", "::_eOesFundTrsfType");
    // eOesFundTrsfStatusT
    module_vnoes::cross.record_assign(parent, "eOesFundTrsfStatusT", "eOesFundTrsfStatusT", "::_eOesFundTrsfStatus");
    // eOesAcctTypeT
    module_vnoes::cross.record_assign(parent, "eOesAcctTypeT", "eOesAcctTypeT", "::_eOesAcctType");
    // eOesCashTypeT
    module_vnoes::cross.record_assign(parent, "eOesCashTypeT", "eOesCashTypeT", "::_eOesCashType");
    // eOesAcctStatusT
    module_vnoes::cross.record_assign(parent, "eOesAcctStatusT", "eOesAcctStatusT", "::_eOesAcctStatus");
    // eOesTradingPermissionT
    module_vnoes::cross.record_assign(parent, "eOesTradingPermissionT", "eOesTradingPermissionT", "::_eOesTradingPermission");
    // eOesTradingLimitT
    module_vnoes::cross.record_assign(parent, "eOesTradingLimitT", "eOesTradingLimitT", "::_eOesTradingLimit");
    // eOesQualificationClassT
    module_vnoes::cross.record_assign(parent, "eOesQualificationClassT", "eOesQualificationClassT", "::_eOesQualificationClass");
    // eOesInvestorClassT
    module_vnoes::cross.record_assign(parent, "eOesInvestorClassT", "eOesInvestorClassT", "::_eOesInvestorClass");
    // eOesCustTypeT
    module_vnoes::cross.record_assign(parent, "eOesCustTypeT", "eOesCustTypeT", "::_eOesCustType");
    // eOesOwnerTypeT
    module_vnoes::cross.record_assign(parent, "eOesOwnerTypeT", "eOesOwnerTypeT", "::_eOesOwnerType");
    // eOesClientTypeT
    module_vnoes::cross.record_assign(parent, "eOesClientTypeT", "eOesClientTypeT", "::_eOesClientType");
    // eOesClientStatusT
    module_vnoes::cross.record_assign(parent, "eOesClientStatusT", "eOesClientStatusT", "::_eOesClientStatus");
    // eOesOptContractTypeT
    module_vnoes::cross.record_assign(parent, "eOesOptContractTypeT", "eOesOptContractTypeT", "::_eOesOptContractType");
    // eOesOptInvLevelT
    module_vnoes::cross.record_assign(parent, "eOesOptInvLevelT", "eOesOptInvLevelT", "::_eOesOptInvLevel");
    // eOpenFlagTypeT
    module_vnoes::cross.record_assign(parent, "eOpenFlagTypeT", "eOpenFlagTypeT", "::_eOpenFlagType");
    // eOesOptionOpenFlagT
    module_vnoes::cross.record_assign(parent, "eOesOptionOpenFlagT", "eOesOptionOpenFlagT", "::_eOesOptionOpenFlag");
    // eOesPositionEffT
    module_vnoes::cross.record_assign(parent, "eOesPositionEffT", "eOesPositionEffT", "::_eOesPositionEff");
    // eOesOptionTypeT
    module_vnoes::cross.record_assign(parent, "eOesOptionTypeT", "eOesOptionTypeT", "::_eOesOptionType");
    // OesOrdReqT
    module_vnoes::cross.record_assign(parent, "OesOrdReqT", "OesOrdReqT", "::_OesOrdReq");
    // OesOrdCancelReqT
    module_vnoes::cross.record_assign(parent, "OesOrdCancelReqT", "OesOrdCancelReqT", "::_OesOrdCancelReq");
    // OesOrdRejectT
    module_vnoes::cross.record_assign(parent, "OesOrdRejectT", "OesOrdRejectT", "::_OesOrdReject");
    // OesOrdCnfmT
    module_vnoes::cross.record_assign(parent, "OesOrdCnfmT", "OesOrdCnfmT", "::_OesOrdCnfm");
    // OesTrdBaseInfoT
    module_vnoes::cross.record_assign(parent, "OesTrdBaseInfoT", "OesTrdBaseInfoT", "::_OesTrdBaseInfo");
    // OesTrdCnfmT
    module_vnoes::cross.record_assign(parent, "OesTrdCnfmT", "OesTrdCnfmT", "::_OesTrdCnfm");
    // OesLotWinningBaseInfoT
    module_vnoes::cross.record_assign(parent, "OesLotWinningBaseInfoT", "OesLotWinningBaseInfoT", "::_OesLotWinningBaseInfo");
    // OesFundTrsfBaseInfoT
    module_vnoes::cross.record_assign(parent, "OesFundTrsfBaseInfoT", "OesFundTrsfBaseInfoT", "::_OesFundTrsfBaseInfo");
    // OesFundTrsfReqT
    module_vnoes::cross.record_assign(parent, "OesFundTrsfReqT", "OesFundTrsfReqT", "::_OesFundTrsfReq");
    // OesFundTrsfRejectT
    module_vnoes::cross.record_assign(parent, "OesFundTrsfRejectT", "OesFundTrsfRejectT", "::_OesFundTrsfReject");
    // OesFundTrsfReportT
    module_vnoes::cross.record_assign(parent, "OesFundTrsfReportT", "OesFundTrsfReportT", "::_OesFundTrsfReport");
    // OesIssueBaseInfoT
    module_vnoes::cross.record_assign(parent, "OesIssueBaseInfoT", "OesIssueBaseInfoT", "::_OesIssueBaseInfo");
    // OesPriceLimitT
    module_vnoes::cross.record_assign(parent, "OesPriceLimitT", "OesPriceLimitT", "::_OesPriceLimit");
    // OesStockBaseInfoT
    module_vnoes::cross.record_assign(parent, "OesStockBaseInfoT", "OesStockBaseInfoT", "::_OesStockBaseInfo");
    // OesEtfBaseInfoT
    module_vnoes::cross.record_assign(parent, "OesEtfBaseInfoT", "OesEtfBaseInfoT", "::_OesEtfBaseInfo");
    // OesEtfComponentBaseInfoT
    module_vnoes::cross.record_assign(parent, "OesEtfComponentBaseInfoT", "OesEtfComponentBaseInfoT", "::_OesEtfComponentBaseInfo");
    // OesOptionBaseInfoT
    module_vnoes::cross.record_assign(parent, "OesOptionBaseInfoT", "OesOptionBaseInfoT", "::_OesOptionBaseInfo");
    // OesCashAssetBaseInfoT
    module_vnoes::cross.record_assign(parent, "OesCashAssetBaseInfoT", "OesCashAssetBaseInfoT", "::_OesCashAssetBaseInfo");
    // OesCustBaseInfoT
    module_vnoes::cross.record_assign(parent, "OesCustBaseInfoT", "OesCustBaseInfoT", "::_OesCustBaseInfo");
    // OesInvAcctBaseInfoT
    module_vnoes::cross.record_assign(parent, "OesInvAcctBaseInfoT", "OesInvAcctBaseInfoT", "::_OesInvAcctBaseInfo");
    // OesStkHoldingBaseInfoT
    module_vnoes::cross.record_assign(parent, "OesStkHoldingBaseInfoT", "OesStkHoldingBaseInfoT", "::_OesStkHoldingBaseInfo");
    // OesOptHoldingBaseInfoT
    module_vnoes::cross.record_assign(parent, "OesOptHoldingBaseInfoT", "OesOptHoldingBaseInfoT", "::_OesOptHoldingBaseInfo");
    // OesMarketStateInfoT
    module_vnoes::cross.record_assign(parent, "OesMarketStateInfoT", "OesMarketStateInfoT", "::_OesMarketStateInfo");
    // OesTradingPermissionEntryT
    module_vnoes::cross.record_assign(parent, "OesTradingPermissionEntryT", "OesTradingPermissionEntryT", "::_OesTradingPermissionEntry");
    // eSMsgProtocolTypeT
    module_vnoes::cross.record_assign(parent, "eSMsgProtocolTypeT", "eSMsgProtocolTypeT", "::_eSMsgProtocolType");
    // eSMsgFlagT
    module_vnoes::cross.record_assign(parent, "eSMsgFlagT", "eSMsgFlagT", "::_eSMsgFlag");
    // SMsgHeadT
    module_vnoes::cross.record_assign(parent, "SMsgHeadT", "SMsgHeadT", "::_SMsgHead");
    // OesQryCursorT
    module_vnoes::cross.record_assign(parent, "OesQryCursorT", "OesQryCursorT", "::_OesQryCursor");
    // OesQryReqHeadT
    module_vnoes::cross.record_assign(parent, "OesQryReqHeadT", "OesQryReqHeadT", "::_OesQryReqHead");
    // OesQryRspHeadT
    module_vnoes::cross.record_assign(parent, "OesQryRspHeadT", "OesQryRspHeadT", "::_OesQryRspHead");
    // OesQryOrdFilterT
    module_vnoes::cross.record_assign(parent, "OesQryOrdFilterT", "OesQryOrdFilterT", "::_OesQryOrdFilter");
    // OesQryOrdReqT
    module_vnoes::cross.record_assign(parent, "OesQryOrdReqT", "OesQryOrdReqT", "::_OesQryOrdReq");
    // OesQryOrdRspT
    module_vnoes::cross.record_assign(parent, "OesQryOrdRspT", "OesQryOrdRspT", "::_OesQryOrdRsp");
    // OesQryTrdFilterT
    module_vnoes::cross.record_assign(parent, "OesQryTrdFilterT", "OesQryTrdFilterT", "::_OesQryTrdFilter");
    // OesQryTrdReqT
    module_vnoes::cross.record_assign(parent, "OesQryTrdReqT", "OesQryTrdReqT", "::_OesQryTrdReq");
    // OesQryTrdRspT
    module_vnoes::cross.record_assign(parent, "OesQryTrdRspT", "OesQryTrdRspT", "::_OesQryTrdRsp");
    // OesQryCashAssetFilterT
    module_vnoes::cross.record_assign(parent, "OesQryCashAssetFilterT", "OesQryCashAssetFilterT", "::_OesQryCashAssetFilter");
    // OesCashAssetItemT
    module_vnoes::cross.record_assign(parent, "OesCashAssetItemT", "OesCashAssetItemT", "::_OesCashAssetItem");
    // OesQryCashAssetReqT
    module_vnoes::cross.record_assign(parent, "OesQryCashAssetReqT", "OesQryCashAssetReqT", "::_OesQryCashAssetReq");
    // OesQryCashAssetRspT
    module_vnoes::cross.record_assign(parent, "OesQryCashAssetRspT", "OesQryCashAssetRspT", "::_OesQryCashAssetRsp");
    // OesCounterCashItemT
    module_vnoes::cross.record_assign(parent, "OesCounterCashItemT", "OesCounterCashItemT", "::_OesCounterCashItem");
    // OesQryCounterCashReqT
    module_vnoes::cross.record_assign(parent, "OesQryCounterCashReqT", "OesQryCounterCashReqT", "::_OesQryCounterCashReq");
    // OesQryCounterCashRspT
    module_vnoes::cross.record_assign(parent, "OesQryCounterCashRspT", "OesQryCounterCashRspT", "::_OesQryCounterCashRsp");
    // OesQryStkHoldingFilterT
    module_vnoes::cross.record_assign(parent, "OesQryStkHoldingFilterT", "OesQryStkHoldingFilterT", "::_OesQryStkHoldingFilter");
    // OesStkHoldingItemT
    module_vnoes::cross.record_assign(parent, "OesStkHoldingItemT", "OesStkHoldingItemT", "::_OesStkHoldingItem");
    // OesQryStkHoldingReqT
    module_vnoes::cross.record_assign(parent, "OesQryStkHoldingReqT", "OesQryStkHoldingReqT", "::_OesQryStkHoldingReq");
    // OesQryStkHoldingRspT
    module_vnoes::cross.record_assign(parent, "OesQryStkHoldingRspT", "OesQryStkHoldingRspT", "::_OesQryStkHoldingRsp");
    // OesOptHoldingItemT
    module_vnoes::cross.record_assign(parent, "OesOptHoldingItemT", "OesOptHoldingItemT", "::_OesOptHoldingItem");
    // OesQryOptHoldingReqT
    module_vnoes::cross.record_assign(parent, "OesQryOptHoldingReqT", "OesQryOptHoldingReqT", "::_OesQryOptHoldingReq");
    // OesQryOptHoldingRspT
    module_vnoes::cross.record_assign(parent, "OesQryOptHoldingRspT", "OesQryOptHoldingRspT", "::_OesQryHoldRsp");
    // OesQryCustFilterT
    module_vnoes::cross.record_assign(parent, "OesQryCustFilterT", "OesQryCustFilterT", "::_OesQryCustFilter");
    // OesQryCustReqT
    module_vnoes::cross.record_assign(parent, "OesQryCustReqT", "OesQryCustReqT", "::_OesQryCustReq");
    // OesQryCustRspT
    module_vnoes::cross.record_assign(parent, "OesQryCustRspT", "OesQryCustRspT", "::_OesQryCustRsp");
    // OesQryInvAcctFilterT
    module_vnoes::cross.record_assign(parent, "OesQryInvAcctFilterT", "OesQryInvAcctFilterT", "::_OesQryInvAcctFilter");
    // OesInvAcctItemT
    module_vnoes::cross.record_assign(parent, "OesInvAcctItemT", "OesInvAcctItemT", "::_OesInvAcctItem");
    // OesQryInvAcctReqT
    module_vnoes::cross.record_assign(parent, "OesQryInvAcctReqT", "OesQryInvAcctReqT", "::_OesQryInvAcctReq");
    // OesQryInvAcctRspT
    module_vnoes::cross.record_assign(parent, "OesQryInvAcctRspT", "OesQryInvAcctRspT", "::_OesQryInvAcctRsp");
    // OesInvAcctOverviewT
    module_vnoes::cross.record_assign(parent, "OesInvAcctOverviewT", "OesInvAcctOverviewT", "::_OesInvAcctOverview");
    // OesCashAcctOverviewT
    module_vnoes::cross.record_assign(parent, "OesCashAcctOverviewT", "OesCashAcctOverviewT", "::_OesCashAcctOverview");
    // OesCustOverviewT
    module_vnoes::cross.record_assign(parent, "OesCustOverviewT", "OesCustOverviewT", "::_OesCustOverview");
    // OesClientOverviewT
    module_vnoes::cross.record_assign(parent, "OesClientOverviewT", "OesClientOverviewT", "::_OesClientOverview");
    // OesQryCommissionRateFilterT
    module_vnoes::cross.record_assign(parent, "OesQryCommissionRateFilterT", "OesQryCommissionRateFilterT", "::_OesQryCommissionRateFilter");
    // OesCommissionRateItemT
    module_vnoes::cross.record_assign(parent, "OesCommissionRateItemT", "OesCommissionRateItemT", "::_OesCommissionRateItem");
    // OesQryCommissionRateReqT
    module_vnoes::cross.record_assign(parent, "OesQryCommissionRateReqT", "OesQryCommissionRateReqT", "::_OesQryCommissionRateReq");
    // OesQryCommissionRateRspT
    module_vnoes::cross.record_assign(parent, "OesQryCommissionRateRspT", "OesQryCommissionRateRspT", "::_OesQryCommissionRateRsp");
    // OesQryFundTransferSerialFilterT
    module_vnoes::cross.record_assign(parent, "OesQryFundTransferSerialFilterT", "OesQryFundTransferSerialFilterT", "::_OesQryFundTransferSerialFilter");
    // OesQryFundTransferSerialReqT
    module_vnoes::cross.record_assign(parent, "OesQryFundTransferSerialReqT", "OesQryFundTransferSerialReqT", "::_OesQryFundTransferSerialReq");
    // OesQryFundTransferSerialRspT
    module_vnoes::cross.record_assign(parent, "OesQryFundTransferSerialRspT", "OesQryFundTransferSerialRspT", "::_OesQryFundTransferSerialRsp");
    // OesQryLotWinningFilterT
    module_vnoes::cross.record_assign(parent, "OesQryLotWinningFilterT", "OesQryLotWinningFilterT", "::_OesQryLotWinningFilter");
    // OesQryLotWinningReqT
    module_vnoes::cross.record_assign(parent, "OesQryLotWinningReqT", "OesQryLotWinningReqT", "::_OesQryLotWinningReq");
    // OesQryLotWinningRspT
    module_vnoes::cross.record_assign(parent, "OesQryLotWinningRspT", "OesQryLotWinningRspT", "::_OesQryLotWinningRsp");
    // OesQryIssueFilterT
    module_vnoes::cross.record_assign(parent, "OesQryIssueFilterT", "OesQryIssueFilterT", "::_OesQryIssueFilter");
    // OesQryIssueReqT
    module_vnoes::cross.record_assign(parent, "OesQryIssueReqT", "OesQryIssueReqT", "::_OesQryIssueReq");
    // OesQryIssueRspT
    module_vnoes::cross.record_assign(parent, "OesQryIssueRspT", "OesQryIssueRspT", "::_OesQryIssueRsp");
    // OesQryStockFilterT
    module_vnoes::cross.record_assign(parent, "OesQryStockFilterT", "OesQryStockFilterT", "::_OesQryStockFilter");
    // OesQryStockReqT
    module_vnoes::cross.record_assign(parent, "OesQryStockReqT", "OesQryStockReqT", "::_OesQryStockReq");
    // OesQryStockRspT
    module_vnoes::cross.record_assign(parent, "OesQryStockRspT", "OesQryStockRspT", "::_OesQryStockRsp");
    // OesQryEtfFilterT
    module_vnoes::cross.record_assign(parent, "OesQryEtfFilterT", "OesQryEtfFilterT", "::_OesQryEtfFilter");
    // OesQryEtfReqT
    module_vnoes::cross.record_assign(parent, "OesQryEtfReqT", "OesQryEtfReqT", "::_OesQryEtfReq");
    // OesQryEtfRspT
    module_vnoes::cross.record_assign(parent, "OesQryEtfRspT", "OesQryEtfRspT", "::_OesQryEtfRsp");
    // OesQryEtfComponentFilterT
    module_vnoes::cross.record_assign(parent, "OesQryEtfComponentFilterT", "OesQryEtfComponentFilterT", "::_OesQryEtfComponentFilter");
    // OesEtfComponentItemT
    module_vnoes::cross.record_assign(parent, "OesEtfComponentItemT", "OesEtfComponentItemT", "::_OesEtfComponentItem");
    // OesQryEtfComponentReqT
    module_vnoes::cross.record_assign(parent, "OesQryEtfComponentReqT", "OesQryEtfComponentReqT", "::_OesQryEtfComponentReq");
    // OesQryEtfComponentRspT
    module_vnoes::cross.record_assign(parent, "OesQryEtfComponentRspT", "OesQryEtfComponentRspT", "::_OesQryEtfComponentRsp");
    // OesQryOptionFilterT
    module_vnoes::cross.record_assign(parent, "OesQryOptionFilterT", "OesQryOptionFilterT", "::_OesQryOptionFilter");
    // OesQryOptionReqT
    module_vnoes::cross.record_assign(parent, "OesQryOptionReqT", "OesQryOptionReqT", "::_OesQryOptionReq");
    // OesQryOptionRspT
    module_vnoes::cross.record_assign(parent, "OesQryOptionRspT", "OesQryOptionRspT", "::_OesQryOptionRsp");
    // OesQryTradingDayRspT
    module_vnoes::cross.record_assign(parent, "OesQryTradingDayRspT", "OesQryTradingDayRspT", "::_OesQryTradingDayRsp");
    // OesQryMarketStateFilterT
    module_vnoes::cross.record_assign(parent, "OesQryMarketStateFilterT", "OesQryMarketStateFilterT", "::_OesQryMarketStateFilter");
    // OesQryMarketStateReqT
    module_vnoes::cross.record_assign(parent, "OesQryMarketStateReqT", "OesQryMarketStateReqT", "::_OesQryMarketStateReq");
    // OesQryMarketStateRspT
    module_vnoes::cross.record_assign(parent, "OesQryMarketStateRspT", "OesQryMarketStateRspT", "::_OesQryMarketStateRsp");
    // OesQryReqMsgT
    module_vnoes::cross.record_assign(parent, "OesQryReqMsgT", "OesQryReqMsgT", "::_OesQryReqMsg");
    // OesQryRspMsgT
    module_vnoes::cross.record_assign(parent, "OesQryRspMsgT", "OesQryRspMsgT", "::_OesQryRspMsg");
    // eOesMsgTypeT
    module_vnoes::cross.record_assign(parent, "eOesMsgTypeT", "eOesMsgTypeT", "::_eOesMsgType");
    // eOesSubscribeReportTypeT
    module_vnoes::cross.record_assign(parent, "eOesSubscribeReportTypeT", "eOesSubscribeReportTypeT", "::_eOesSubscribeReportType");
    // eOesProtocolHintsTypeT
    module_vnoes::cross.record_assign(parent, "eOesProtocolHintsTypeT", "eOesProtocolHintsTypeT", "::_eOesProtocolHintsType");
    // OesReportSynchronizationReqT
    module_vnoes::cross.record_assign(parent, "OesReportSynchronizationReqT", "OesReportSynchronizationReqT", "::_OesReportSynchronizationReq");
    // OesReportSynchronizationRspT
    module_vnoes::cross.record_assign(parent, "OesReportSynchronizationRspT", "OesReportSynchronizationRspT", "::_OesReportSynchronizationRsp");
    // OesTestRequestReqT
    module_vnoes::cross.record_assign(parent, "OesTestRequestReqT", "OesTestRequestReqT", "::_OesTestRequestReq");
    // OesTestRequestRspT
    module_vnoes::cross.record_assign(parent, "OesTestRequestRspT", "OesTestRequestRspT", "::_OesTestRequestRsp");
    // OesChangePasswordReqT
    module_vnoes::cross.record_assign(parent, "OesChangePasswordReqT", "OesChangePasswordReqT", "::_OesChangePasswordReq");
    // OesChangePasswordRspT
    module_vnoes::cross.record_assign(parent, "OesChangePasswordRspT", "OesChangePasswordRspT", "::_OesChangePasswordRsp");
    // OesBatchOrdersHeadT
    module_vnoes::cross.record_assign(parent, "OesBatchOrdersHeadT", "OesBatchOrdersHeadT", "::_OesBatchOrdersHead");
    // OesBatchOrdersReqT
    module_vnoes::cross.record_assign(parent, "OesBatchOrdersReqT", "OesBatchOrdersReqT", "::_OesBatchOrdersReq");
    // OesRptMsgHeadT
    module_vnoes::cross.record_assign(parent, "OesRptMsgHeadT", "OesRptMsgHeadT", "::_OesRptMsgHead");
    // OesRptMsgBodyT
    module_vnoes::cross.record_assign(parent, "OesRptMsgBodyT", "OesRptMsgBodyT", "::_OesRptMsgBody");
    // OesRptMsgT
    module_vnoes::cross.record_assign(parent, "OesRptMsgT", "OesRptMsgT", "::_OesRptMsg");
    // OesReqMsgBodyT
    module_vnoes::cross.record_assign(parent, "OesReqMsgBodyT", "OesReqMsgBodyT", "::_OesReqMsgBody");
    // OesRspMsgBodyT
    module_vnoes::cross.record_assign(parent, "OesRspMsgBodyT", "OesRspMsgBodyT", "::_OesRspMsgBody");
    // SErrMsgT
    module_vnoes::cross.record_assign(parent, "SErrMsgT", "SErrMsgT", "::_SErrMsg");
    // SDataBufferT
    module_vnoes::cross.record_assign(parent, "SDataBufferT", "SDataBufferT", "::_SDataBuffer");
    // eSSocketProtocolTypeT
    module_vnoes::cross.record_assign(parent, "eSSocketProtocolTypeT", "eSSocketProtocolTypeT", "::_eSSocketProtocolType");
    // SSocketUriInfoT
    module_vnoes::cross.record_assign(parent, "SSocketUriInfoT", "SSocketUriInfoT", "::_SSocketUriInfo");
    // SSocketIpPortInfoT
    module_vnoes::cross.record_assign(parent, "SSocketIpPortInfoT", "SSocketIpPortInfoT", "::_SSocketIpPortInfo");
    // SSocketChannelInfoT
    module_vnoes::cross.record_assign(parent, "SSocketChannelInfoT", "SSocketChannelInfoT", "::_SSocketChannelInfo");
    // SSocketOptionConfigT
    module_vnoes::cross.record_assign(parent, "SSocketOptionConfigT", "SSocketOptionConfigT", "::_SSocketOptionConfig");
    // eGeneralClientClusterTypeT
    module_vnoes::cross.record_assign(parent, "eGeneralClientClusterTypeT", "eGeneralClientClusterTypeT", "::_eGeneralClientClusterType");
    // eGeneralClientEncryptTypeT
    module_vnoes::cross.record_assign(parent, "eGeneralClientEncryptTypeT", "eGeneralClientEncryptTypeT", "::_eGeneralClientEncryptType");
    // SGeneralClientChannelT
    module_vnoes::cross.record_assign(parent, "SGeneralClientChannelT", "SGeneralClientChannelT", "::_SGeneralClientChannel");
    // SGeneralClientChannelGroupT
    module_vnoes::cross.record_assign(parent, "SGeneralClientChannelGroupT", "SGeneralClientChannelGroupT", "::_SGeneralClientChannelGroup");
    // SGeneralClientAddrInfoT
    module_vnoes::cross.record_assign(parent, "SGeneralClientAddrInfoT", "SGeneralClientAddrInfoT", "::_SGeneralClientAddrInfo");
    // SGeneralClientRemoteCfgT
    module_vnoes::cross.record_assign(parent, "SGeneralClientRemoteCfgT", "SGeneralClientRemoteCfgT", "::_SGeneralClientRemoteCfg");
    // eOesApiChannelTypeT
    module_vnoes::cross.record_assign(parent, "eOesApiChannelTypeT", "eOesApiChannelTypeT", "::_eOesApiChannelType");
    // OesApiSubscribeInfoT
    module_vnoes::cross.record_assign(parent, "OesApiSubscribeInfoT", "OesApiSubscribeInfoT", "::_OesApiSubscribeInfo");
    // OesApiClientCfgT
    module_vnoes::cross.record_assign(parent, "OesApiClientCfgT", "OesApiClientCfgT", "::_OesApiClientCfg");
    // OesApiClientEnvT
    module_vnoes::cross.record_assign(parent, "OesApiClientEnvT", "OesApiClientEnvT", "::_OesApiClientEnv");
    // eMdsExchangeIdT
    module_vnoes::cross.record_assign(parent, "eMdsExchangeIdT", "eMdsExchangeIdT", "::_eMdsExchangeId");
    // eMdsMsgSourceT
    module_vnoes::cross.record_assign(parent, "eMdsMsgSourceT", "eMdsMsgSourceT", "::_eMdsMsgSource");
    // eMdsMdProductTypeT
    module_vnoes::cross.record_assign(parent, "eMdsMdProductTypeT", "eMdsMdProductTypeT", "::_eMdsMdProductType");
    // eMdsMdStreamTypeT
    module_vnoes::cross.record_assign(parent, "eMdsMdStreamTypeT", "eMdsMdStreamTypeT", "::_eMdsMdStreamType");
    // eMdsMdLevelT
    module_vnoes::cross.record_assign(parent, "eMdsMdLevelT", "eMdsMdLevelT", "::_eMdsMdLevel");
    // eMdsL2PriceLevelOperatorT
    module_vnoes::cross.record_assign(parent, "eMdsL2PriceLevelOperatorT", "eMdsL2PriceLevelOperatorT", "::_eMdsL2PriceLevelOperator");
    // eMdsL2TradeExecTypeT
    module_vnoes::cross.record_assign(parent, "eMdsL2TradeExecTypeT", "eMdsL2TradeExecTypeT", "::_eMdsL2TradeExecType");
    // eMdsL2TradeBSFlagT
    module_vnoes::cross.record_assign(parent, "eMdsL2TradeBSFlagT", "eMdsL2TradeBSFlagT", "::_eMdsL2TradeBSFlag");
    // eMdsL2OrderSideT
    module_vnoes::cross.record_assign(parent, "eMdsL2OrderSideT", "eMdsL2OrderSideT", "::_eMdsL2OrderSideT");
    // eMdsL2OrderTypeT
    module_vnoes::cross.record_assign(parent, "eMdsL2OrderTypeT", "eMdsL2OrderTypeT", "::_eMdsL2OrderType");
    // eMdsClientTypeT
    module_vnoes::cross.record_assign(parent, "eMdsClientTypeT", "eMdsClientTypeT", "::_eMdsClientType");
    // eMdsClientStatusT
    module_vnoes::cross.record_assign(parent, "eMdsClientStatusT", "eMdsClientStatusT", "::_eMdsClientStatus");
    // MdsTradingSessionStatusMsgT
    module_vnoes::cross.record_assign(parent, "MdsTradingSessionStatusMsgT", "MdsTradingSessionStatusMsgT", "::_MdsTradingSessionStatusMsg");
    // MdsSecurityStatusMsgT
    module_vnoes::cross.record_assign(parent, "MdsSecurityStatusMsgT", "MdsSecurityStatusMsgT", "::_MdsSecurityStatusMsg");
    // MdsPriceLevelEntryT
    module_vnoes::cross.record_assign(parent, "MdsPriceLevelEntryT", "MdsPriceLevelEntryT", "::_MdsPriceLevelEntry");
    // MdsMktDataSnapshotHeadT
    module_vnoes::cross.record_assign(parent, "MdsMktDataSnapshotHeadT", "MdsMktDataSnapshotHeadT", "::_MdsMktDataSnapshotHead");
    // MdsIndexSnapshotBodyT
    module_vnoes::cross.record_assign(parent, "MdsIndexSnapshotBodyT", "MdsIndexSnapshotBodyT", "::_MdsIndexSnapshotBody");
    // MdsStockSnapshotBodyT
    module_vnoes::cross.record_assign(parent, "MdsStockSnapshotBodyT", "MdsStockSnapshotBodyT", "::_MdsStockSnapshotBody");
    // MdsL1SnapshotBodyT
    module_vnoes::cross.record_assign(parent, "MdsL1SnapshotBodyT", "MdsL1SnapshotBodyT", "::_MdsL1SnapshotBody");
    // MdsL1SnapshotT
    module_vnoes::cross.record_assign(parent, "MdsL1SnapshotT", "MdsL1SnapshotT", "::_MdsL1Snapshot");
    // MdsL2StockSnapshotBodyT
    module_vnoes::cross.record_assign(parent, "MdsL2StockSnapshotBodyT", "MdsL2StockSnapshotBodyT", "::_MdsL2StockSnapshotBody");
    // MdsL2StockSnapshotIncrementalT
    module_vnoes::cross.record_assign(parent, "MdsL2StockSnapshotIncrementalT", "MdsL2StockSnapshotIncrementalT", "::_MdsL2StockSnapshotIncremental");
    // MdsL2BestOrdersSnapshotBodyT
    module_vnoes::cross.record_assign(parent, "MdsL2BestOrdersSnapshotBodyT", "MdsL2BestOrdersSnapshotBodyT", "::_MdsL2BestOrdersSnapshotBody");
    // MdsL2BestOrdersSnapshotIncrementalT
    module_vnoes::cross.record_assign(parent, "MdsL2BestOrdersSnapshotIncrementalT", "MdsL2BestOrdersSnapshotIncrementalT", "::_MdsL2BestOrdersSnapshotIncremental");
    // MdsL2MarketOverviewT
    module_vnoes::cross.record_assign(parent, "MdsL2MarketOverviewT", "MdsL2MarketOverviewT", "::_MdsL2MarketOverview");
    // MdsL2SnapshotBodyT
    module_vnoes::cross.record_assign(parent, "MdsL2SnapshotBodyT", "MdsL2SnapshotBodyT", "::_MdsL2SnapshotBody");
    // MdsMktDataSnapshotT
    module_vnoes::cross.record_assign(parent, "MdsMktDataSnapshotT", "MdsMktDataSnapshotT", "::_MdsMktDataSnapshot");
    // MdsL2TradeT
    module_vnoes::cross.record_assign(parent, "MdsL2TradeT", "MdsL2TradeT", "::_MdsL2Trade");
    // MdsL2OrderT
    module_vnoes::cross.record_assign(parent, "MdsL2OrderT", "MdsL2OrderT", "::_MdsL2Order");
    // MdsWholeMktMsgBodyT
    module_vnoes::cross.record_assign(parent, "MdsWholeMktMsgBodyT", "MdsWholeMktMsgBodyT", "::_MdsWholeMktMsgBody");
    // MdsStockStaticInfoT
    module_vnoes::cross.record_assign(parent, "MdsStockStaticInfoT", "MdsStockStaticInfoT", "::_MdsStockStaticInfo");
    // MdsQryMktDataSnapshotReqT
    module_vnoes::cross.record_assign(parent, "MdsQryMktDataSnapshotReqT", "MdsQryMktDataSnapshotReqT", "::_MdsQryMktDataSnapshotReq");
    // MdsQryTrdSessionStatusReqT
    module_vnoes::cross.record_assign(parent, "MdsQryTrdSessionStatusReqT", "MdsQryTrdSessionStatusReqT", "::_MdsQryTrdSessionStatusReq");
    // MdsQryReqHeadT
    module_vnoes::cross.record_assign(parent, "MdsQryReqHeadT", "MdsQryReqHeadT", "::_MdsQryReqHeadT");
    // MdsQryRspHeadT
    module_vnoes::cross.record_assign(parent, "MdsQryRspHeadT", "MdsQryRspHeadT", "::_MdsQryRspHeadT");
    // MdsQryCursorT
    module_vnoes::cross.record_assign(parent, "MdsQryCursorT", "MdsQryCursorT", "::_MdsQryCursor");
    // MdsQrySecurityCodeEntryT
    module_vnoes::cross.record_assign(parent, "MdsQrySecurityCodeEntryT", "MdsQrySecurityCodeEntryT", "::_MdsQrySecurityCodeEntry");
    // MdsQryStockStaticInfoFilterT
    module_vnoes::cross.record_assign(parent, "MdsQryStockStaticInfoFilterT", "MdsQryStockStaticInfoFilterT", "::_MdsQryStockStaticInfoFilter");
    // MdsQryStockStaticInfoReqT
    module_vnoes::cross.record_assign(parent, "MdsQryStockStaticInfoReqT", "MdsQryStockStaticInfoReqT", "::_MdsQryStockStaticInfoReq");
    // MdsQryStockStaticInfoRspT
    module_vnoes::cross.record_assign(parent, "MdsQryStockStaticInfoRspT", "MdsQryStockStaticInfoRspT", "::_MdsQryStockStaticInfoRsp");
    // MdsQrySnapshotListFilterT
    module_vnoes::cross.record_assign(parent, "MdsQrySnapshotListFilterT", "MdsQrySnapshotListFilterT", "::_MdsQrySnapshotListFilter");
    // MdsQrySnapshotListReqT
    module_vnoes::cross.record_assign(parent, "MdsQrySnapshotListReqT", "MdsQrySnapshotListReqT", "::_MdsQrySnapshotListReq");
    // MdsQrySnapshotListRspT
    module_vnoes::cross.record_assign(parent, "MdsQrySnapshotListRspT", "MdsQrySnapshotListRspT", "::_MdsQrySnapshotListRsp");
    // eMdsMsgTypeT
    module_vnoes::cross.record_assign(parent, "eMdsMsgTypeT", "eMdsMsgTypeT", "::_eMdsMsgType");
    // eMdsSubscribeModeT
    module_vnoes::cross.record_assign(parent, "eMdsSubscribeModeT", "eMdsSubscribeModeT", "::_eMdsSubscribeMode");
    // eMdsMktSubscribeFlagT
    module_vnoes::cross.record_assign(parent, "eMdsMktSubscribeFlagT", "eMdsMktSubscribeFlagT", "::_eMdsMktSubscribeFlag");
    // eMdsSubscribedTickTypeT
    module_vnoes::cross.record_assign(parent, "eMdsSubscribedTickTypeT", "eMdsSubscribedTickTypeT", "::_eMdsSubscribedTickType");
    // eMdsSubscribedTickExpireTypeT
    module_vnoes::cross.record_assign(parent, "eMdsSubscribedTickExpireTypeT", "eMdsSubscribedTickExpireTypeT", "::_eMdsSubscribedTickExpireType");
    // eMdsSubscribeDataTypeT
    module_vnoes::cross.record_assign(parent, "eMdsSubscribeDataTypeT", "eMdsSubscribeDataTypeT", "::_eMdsSubscribeDataType");
    // eMdsTickChannelNoT
    module_vnoes::cross.record_assign(parent, "eMdsTickChannelNoT", "eMdsTickChannelNoT", "::_eMdsSubscribedChannelNo");
    // eMdsProtocolHintsTypeT
    module_vnoes::cross.record_assign(parent, "eMdsProtocolHintsTypeT", "eMdsProtocolHintsTypeT", "::_eMdsProtocolHintsType");
    // MdsMktDataRequestEntryT
    module_vnoes::cross.record_assign(parent, "MdsMktDataRequestEntryT", "MdsMktDataRequestEntryT", "::_MdsMktDataRequestEntry");
    // MdsMktDataRequestReqT
    module_vnoes::cross.record_assign(parent, "MdsMktDataRequestReqT", "MdsMktDataRequestReqT", "::_MdsMktDataRequestReq");
    // MdsMktDataRequestReqBufT
    module_vnoes::cross.record_assign(parent, "MdsMktDataRequestReqBufT", "MdsMktDataRequestReqBufT", "::_MdsMktDataRequestReqBuf");
    // MdsMktDataRequestRspT
    module_vnoes::cross.record_assign(parent, "MdsMktDataRequestRspT", "MdsMktDataRequestRspT", "::_MdsMktDataRequestRsp");
    // MdsTestRequestReqT
    module_vnoes::cross.record_assign(parent, "MdsTestRequestReqT", "MdsTestRequestReqT", "::_MdsTestRequestReq");
    // MdsTestRequestRspT
    module_vnoes::cross.record_assign(parent, "MdsTestRequestRspT", "MdsTestRequestRspT", "::_MdsTestRequestRsp");
    // MdsChangePasswordReqT
    module_vnoes::cross.record_assign(parent, "MdsChangePasswordReqT", "MdsChangePasswordReqT", "::_MdsChangePasswordReq");
    // MdsChangePasswordRspT
    module_vnoes::cross.record_assign(parent, "MdsChangePasswordRspT", "MdsChangePasswordRspT", "::_MdsChangePasswordRsp");
    // MdsMktReqMsgBodyT
    module_vnoes::cross.record_assign(parent, "MdsMktReqMsgBodyT", "MdsMktReqMsgBodyT", "::_MdsMktReqMsgBody");
    // MdsMktRspMsgBodyT
    module_vnoes::cross.record_assign(parent, "MdsMktRspMsgBodyT", "MdsMktRspMsgBodyT", "::_MdsMktRspMsgBody");
    // MdsUdpPktHeadT
    module_vnoes::cross.record_assign(parent, "MdsUdpPktHeadT", "MdsUdpPktHeadT", "::_MdsUdpPktHead");
    // eMdsApiChannelTypeT
    module_vnoes::cross.record_assign(parent, "eMdsApiChannelTypeT", "eMdsApiChannelTypeT", "::_eMdsApiChannelType");
    // MdsApiClientCfgT
    module_vnoes::cross.record_assign(parent, "MdsApiClientCfgT", "MdsApiClientCfgT", "::_MdsApiClientCfg");
    // MdsApiClientEnvT
    module_vnoes::cross.record_assign(parent, "MdsApiClientEnvT", "MdsApiClientEnvT", "::_MdsApiClientEnv");
}
void generate_caster_(pybind11::object & parent)
{
    struct caster: c2py::caster{};
    auto c = c2py::caster::bind<caster>(parent, "caster"); 
    // _OesOrdReq
    c2py::caster::try_generate<_OesOrdReq>(c, "to_OesOrdReq");
    // _OesOrdCancelReq
    c2py::caster::try_generate<_OesOrdCancelReq>(c, "to_OesOrdCancelReq");
    // _OesOrdReject
    c2py::caster::try_generate<_OesOrdReject>(c, "to_OesOrdReject");
    // _OesOrdCnfm
    c2py::caster::try_generate<_OesOrdCnfm>(c, "to_OesOrdCnfm");
    // _OesTrdBaseInfo
    c2py::caster::try_generate<_OesTrdBaseInfo>(c, "to_OesTrdBaseInfo");
    // _OesTrdCnfm
    c2py::caster::try_generate<_OesTrdCnfm>(c, "to_OesTrdCnfm");
    // _OesLotWinningBaseInfo
    c2py::caster::try_generate<_OesLotWinningBaseInfo>(c, "to_OesLotWinningBaseInfo");
    // _OesFundTrsfBaseInfo
    c2py::caster::try_generate<_OesFundTrsfBaseInfo>(c, "to_OesFundTrsfBaseInfo");
    // _OesFundTrsfReq
    c2py::caster::try_generate<_OesFundTrsfReq>(c, "to_OesFundTrsfReq");
    // _OesFundTrsfReject
    c2py::caster::try_generate<_OesFundTrsfReject>(c, "to_OesFundTrsfReject");
    // _OesFundTrsfReport
    c2py::caster::try_generate<_OesFundTrsfReport>(c, "to_OesFundTrsfReport");
    // _OesIssueBaseInfo
    c2py::caster::try_generate<_OesIssueBaseInfo>(c, "to_OesIssueBaseInfo");
    // _OesPriceLimit
    c2py::caster::try_generate<_OesPriceLimit>(c, "to_OesPriceLimit");
    // _OesStockBaseInfo
    c2py::caster::try_generate<_OesStockBaseInfo>(c, "to_OesStockBaseInfo");
    // _OesEtfBaseInfo
    c2py::caster::try_generate<_OesEtfBaseInfo>(c, "to_OesEtfBaseInfo");
    // _OesEtfComponentBaseInfo
    c2py::caster::try_generate<_OesEtfComponentBaseInfo>(c, "to_OesEtfComponentBaseInfo");
    // _OesOptionBaseInfo
    c2py::caster::try_generate<_OesOptionBaseInfo>(c, "to_OesOptionBaseInfo");
    // _OesCashAssetBaseInfo
    c2py::caster::try_generate<_OesCashAssetBaseInfo>(c, "to_OesCashAssetBaseInfo");
    // _OesCustBaseInfo
    c2py::caster::try_generate<_OesCustBaseInfo>(c, "to_OesCustBaseInfo");
    // _OesInvAcctBaseInfo
    c2py::caster::try_generate<_OesInvAcctBaseInfo>(c, "to_OesInvAcctBaseInfo");
    // _OesStkHoldingBaseInfo
    c2py::caster::try_generate<_OesStkHoldingBaseInfo>(c, "to_OesStkHoldingBaseInfo");
    // _OesOptHoldingBaseInfo
    c2py::caster::try_generate<_OesOptHoldingBaseInfo>(c, "to_OesOptHoldingBaseInfo");
    // _OesMarketStateInfo
    c2py::caster::try_generate<_OesMarketStateInfo>(c, "to_OesMarketStateInfo");
    // _OesTradingPermissionEntry
    c2py::caster::try_generate<_OesTradingPermissionEntry>(c, "to_OesTradingPermissionEntry");
    // _SMsgHead
    c2py::caster::try_generate<_SMsgHead>(c, "to_SMsgHead");
    // _OesQryCursor
    c2py::caster::try_generate<_OesQryCursor>(c, "to_OesQryCursor");
    // _OesQryReqHead
    c2py::caster::try_generate<_OesQryReqHead>(c, "to_OesQryReqHead");
    // _OesQryRspHead
    c2py::caster::try_generate<_OesQryRspHead>(c, "to_OesQryRspHead");
    // _OesQryOrdFilter
    c2py::caster::try_generate<_OesQryOrdFilter>(c, "to_OesQryOrdFilter");
    // _OesQryOrdReq
    c2py::caster::try_generate<_OesQryOrdReq>(c, "to_OesQryOrdReq");
    // _OesQryOrdRsp
    c2py::caster::try_generate<_OesQryOrdRsp>(c, "to_OesQryOrdRsp");
    // _OesQryTrdFilter
    c2py::caster::try_generate<_OesQryTrdFilter>(c, "to_OesQryTrdFilter");
    // _OesQryTrdReq
    c2py::caster::try_generate<_OesQryTrdReq>(c, "to_OesQryTrdReq");
    // _OesQryTrdRsp
    c2py::caster::try_generate<_OesQryTrdRsp>(c, "to_OesQryTrdRsp");
    // _OesQryCashAssetFilter
    c2py::caster::try_generate<_OesQryCashAssetFilter>(c, "to_OesQryCashAssetFilter");
    // _OesCashAssetItem
    c2py::caster::try_generate<_OesCashAssetItem>(c, "to_OesCashAssetItem");
    // _OesQryCashAssetReq
    c2py::caster::try_generate<_OesQryCashAssetReq>(c, "to_OesQryCashAssetReq");
    // _OesQryCashAssetRsp
    c2py::caster::try_generate<_OesQryCashAssetRsp>(c, "to_OesQryCashAssetRsp");
    // _OesCounterCashItem
    c2py::caster::try_generate<_OesCounterCashItem>(c, "to_OesCounterCashItem");
    // _OesQryCounterCashReq
    c2py::caster::try_generate<_OesQryCounterCashReq>(c, "to_OesQryCounterCashReq");
    // _OesQryCounterCashRsp
    c2py::caster::try_generate<_OesQryCounterCashRsp>(c, "to_OesQryCounterCashRsp");
    // _OesQryStkHoldingFilter
    c2py::caster::try_generate<_OesQryStkHoldingFilter>(c, "to_OesQryStkHoldingFilter");
    // _OesStkHoldingItem
    c2py::caster::try_generate<_OesStkHoldingItem>(c, "to_OesStkHoldingItem");
    // _OesQryStkHoldingReq
    c2py::caster::try_generate<_OesQryStkHoldingReq>(c, "to_OesQryStkHoldingReq");
    // _OesQryStkHoldingRsp
    c2py::caster::try_generate<_OesQryStkHoldingRsp>(c, "to_OesQryStkHoldingRsp");
    // _OesOptHoldingItem
    c2py::caster::try_generate<_OesOptHoldingItem>(c, "to_OesOptHoldingItem");
    // _OesQryOptHoldingReq
    c2py::caster::try_generate<_OesQryOptHoldingReq>(c, "to_OesQryOptHoldingReq");
    // _OesQryHoldRsp
    c2py::caster::try_generate<_OesQryHoldRsp>(c, "to_OesQryHoldRsp");
    // _OesQryCustFilter
    c2py::caster::try_generate<_OesQryCustFilter>(c, "to_OesQryCustFilter");
    // _OesQryCustReq
    c2py::caster::try_generate<_OesQryCustReq>(c, "to_OesQryCustReq");
    // _OesQryCustRsp
    c2py::caster::try_generate<_OesQryCustRsp>(c, "to_OesQryCustRsp");
    // _OesQryInvAcctFilter
    c2py::caster::try_generate<_OesQryInvAcctFilter>(c, "to_OesQryInvAcctFilter");
    // _OesInvAcctItem
    c2py::caster::try_generate<_OesInvAcctItem>(c, "to_OesInvAcctItem");
    // _OesQryInvAcctReq
    c2py::caster::try_generate<_OesQryInvAcctReq>(c, "to_OesQryInvAcctReq");
    // _OesQryInvAcctRsp
    c2py::caster::try_generate<_OesQryInvAcctRsp>(c, "to_OesQryInvAcctRsp");
    // _OesInvAcctOverview
    c2py::caster::try_generate<_OesInvAcctOverview>(c, "to_OesInvAcctOverview");
    // _OesCashAcctOverview
    c2py::caster::try_generate<_OesCashAcctOverview>(c, "to_OesCashAcctOverview");
    // _OesCustOverview
    c2py::caster::try_generate<_OesCustOverview>(c, "to_OesCustOverview");
    // _OesClientOverview
    c2py::caster::try_generate<_OesClientOverview>(c, "to_OesClientOverview");
    // _OesQryCommissionRateFilter
    c2py::caster::try_generate<_OesQryCommissionRateFilter>(c, "to_OesQryCommissionRateFilter");
    // _OesCommissionRateItem
    c2py::caster::try_generate<_OesCommissionRateItem>(c, "to_OesCommissionRateItem");
    // _OesQryCommissionRateReq
    c2py::caster::try_generate<_OesQryCommissionRateReq>(c, "to_OesQryCommissionRateReq");
    // _OesQryCommissionRateRsp
    c2py::caster::try_generate<_OesQryCommissionRateRsp>(c, "to_OesQryCommissionRateRsp");
    // _OesQryFundTransferSerialFilter
    c2py::caster::try_generate<_OesQryFundTransferSerialFilter>(c, "to_OesQryFundTransferSerialFilter");
    // _OesQryFundTransferSerialReq
    c2py::caster::try_generate<_OesQryFundTransferSerialReq>(c, "to_OesQryFundTransferSerialReq");
    // _OesQryFundTransferSerialRsp
    c2py::caster::try_generate<_OesQryFundTransferSerialRsp>(c, "to_OesQryFundTransferSerialRsp");
    // _OesQryLotWinningFilter
    c2py::caster::try_generate<_OesQryLotWinningFilter>(c, "to_OesQryLotWinningFilter");
    // _OesQryLotWinningReq
    c2py::caster::try_generate<_OesQryLotWinningReq>(c, "to_OesQryLotWinningReq");
    // _OesQryLotWinningRsp
    c2py::caster::try_generate<_OesQryLotWinningRsp>(c, "to_OesQryLotWinningRsp");
    // _OesQryIssueFilter
    c2py::caster::try_generate<_OesQryIssueFilter>(c, "to_OesQryIssueFilter");
    // _OesQryIssueReq
    c2py::caster::try_generate<_OesQryIssueReq>(c, "to_OesQryIssueReq");
    // _OesQryIssueRsp
    c2py::caster::try_generate<_OesQryIssueRsp>(c, "to_OesQryIssueRsp");
    // _OesQryStockFilter
    c2py::caster::try_generate<_OesQryStockFilter>(c, "to_OesQryStockFilter");
    // _OesQryStockReq
    c2py::caster::try_generate<_OesQryStockReq>(c, "to_OesQryStockReq");
    // _OesQryStockRsp
    c2py::caster::try_generate<_OesQryStockRsp>(c, "to_OesQryStockRsp");
    // _OesQryEtfFilter
    c2py::caster::try_generate<_OesQryEtfFilter>(c, "to_OesQryEtfFilter");
    // _OesQryEtfReq
    c2py::caster::try_generate<_OesQryEtfReq>(c, "to_OesQryEtfReq");
    // _OesQryEtfRsp
    c2py::caster::try_generate<_OesQryEtfRsp>(c, "to_OesQryEtfRsp");
    // _OesQryEtfComponentFilter
    c2py::caster::try_generate<_OesQryEtfComponentFilter>(c, "to_OesQryEtfComponentFilter");
    // _OesEtfComponentItem
    c2py::caster::try_generate<_OesEtfComponentItem>(c, "to_OesEtfComponentItem");
    // _OesQryEtfComponentReq
    c2py::caster::try_generate<_OesQryEtfComponentReq>(c, "to_OesQryEtfComponentReq");
    // _OesQryEtfComponentRsp
    c2py::caster::try_generate<_OesQryEtfComponentRsp>(c, "to_OesQryEtfComponentRsp");
    // _OesQryOptionFilter
    c2py::caster::try_generate<_OesQryOptionFilter>(c, "to_OesQryOptionFilter");
    // _OesQryOptionReq
    c2py::caster::try_generate<_OesQryOptionReq>(c, "to_OesQryOptionReq");
    // _OesQryOptionRsp
    c2py::caster::try_generate<_OesQryOptionRsp>(c, "to_OesQryOptionRsp");
    // _OesQryTradingDayRsp
    c2py::caster::try_generate<_OesQryTradingDayRsp>(c, "to_OesQryTradingDayRsp");
    // _OesQryMarketStateFilter
    c2py::caster::try_generate<_OesQryMarketStateFilter>(c, "to_OesQryMarketStateFilter");
    // _OesQryMarketStateReq
    c2py::caster::try_generate<_OesQryMarketStateReq>(c, "to_OesQryMarketStateReq");
    // _OesQryMarketStateRsp
    c2py::caster::try_generate<_OesQryMarketStateRsp>(c, "to_OesQryMarketStateRsp");
    // _OesQryReqMsg
    c2py::caster::try_generate<_OesQryReqMsg>(c, "to_OesQryReqMsg");
    // _OesQryRspMsg
    c2py::caster::try_generate<_OesQryRspMsg>(c, "to_OesQryRspMsg");
    // _OesReportSynchronizationReq
    c2py::caster::try_generate<_OesReportSynchronizationReq>(c, "to_OesReportSynchronizationReq");
    // _OesReportSynchronizationRsp
    c2py::caster::try_generate<_OesReportSynchronizationRsp>(c, "to_OesReportSynchronizationRsp");
    // _OesTestRequestReq
    c2py::caster::try_generate<_OesTestRequestReq>(c, "to_OesTestRequestReq");
    // _OesTestRequestRsp
    c2py::caster::try_generate<_OesTestRequestRsp>(c, "to_OesTestRequestRsp");
    // _OesChangePasswordReq
    c2py::caster::try_generate<_OesChangePasswordReq>(c, "to_OesChangePasswordReq");
    // _OesChangePasswordRsp
    c2py::caster::try_generate<_OesChangePasswordRsp>(c, "to_OesChangePasswordRsp");
    // _OesBatchOrdersHead
    c2py::caster::try_generate<_OesBatchOrdersHead>(c, "to_OesBatchOrdersHead");
    // _OesBatchOrdersReq
    c2py::caster::try_generate<_OesBatchOrdersReq>(c, "to_OesBatchOrdersReq");
    // _OesRptMsgHead
    c2py::caster::try_generate<_OesRptMsgHead>(c, "to_OesRptMsgHead");
    // _OesRptMsgBody
    c2py::caster::try_generate<_OesRptMsgBody>(c, "to_OesRptMsgBody");
    // _OesRptMsg
    c2py::caster::try_generate<_OesRptMsg>(c, "to_OesRptMsg");
    // _OesReqMsgBody
    c2py::caster::try_generate<_OesReqMsgBody>(c, "to_OesReqMsgBody");
    // _OesRspMsgBody
    c2py::caster::try_generate<_OesRspMsgBody>(c, "to_OesRspMsgBody");
    // _SErrMsg
    c2py::caster::try_generate<_SErrMsg>(c, "to_SErrMsg");
    // _SDataBuffer
    c2py::caster::try_generate<_SDataBuffer>(c, "to_SDataBuffer");
    // _SDataBufferVar
    c2py::caster::try_generate<_SDataBufferVar>(c, "to_SDataBufferVar");
    // _SSocketUriInfo
    c2py::caster::try_generate<_SSocketUriInfo>(c, "to_SSocketUriInfo");
    // _SSocketIpPortInfo
    c2py::caster::try_generate<_SSocketIpPortInfo>(c, "to_SSocketIpPortInfo");
    // _SSocketChannelInfo
    c2py::caster::try_generate<_SSocketChannelInfo>(c, "to_SSocketChannelInfo");
    // _SSocketOptionConfig
    c2py::caster::try_generate<_SSocketOptionConfig>(c, "to_SSocketOptionConfig");
    // _SGeneralClientChannel
    c2py::caster::try_generate<_SGeneralClientChannel>(c, "to_SGeneralClientChannel");
    // _SGeneralClientChannelGroup
    c2py::caster::try_generate<_SGeneralClientChannelGroup>(c, "to_SGeneralClientChannelGroup");
    // _SGeneralClientAddrInfo
    c2py::caster::try_generate<_SGeneralClientAddrInfo>(c, "to_SGeneralClientAddrInfo");
    // _SGeneralClientRemoteCfg
    c2py::caster::try_generate<_SGeneralClientRemoteCfg>(c, "to_SGeneralClientRemoteCfg");
    // _OesApiSubscribeInfo
    c2py::caster::try_generate<_OesApiSubscribeInfo>(c, "to_OesApiSubscribeInfo");
    // _OesApiClientCfg
    c2py::caster::try_generate<_OesApiClientCfg>(c, "to_OesApiClientCfg");
    // _OesApiClientEnv
    c2py::caster::try_generate<_OesApiClientEnv>(c, "to_OesApiClientEnv");
    // _MdsTradingSessionStatusMsg
    c2py::caster::try_generate<_MdsTradingSessionStatusMsg>(c, "to_MdsTradingSessionStatusMsg");
    // _MdsSecurityStatusMsg
    c2py::caster::try_generate<_MdsSecurityStatusMsg>(c, "to_MdsSecurityStatusMsg");
    // _MdsPriceLevelEntry
    c2py::caster::try_generate<_MdsPriceLevelEntry>(c, "to_MdsPriceLevelEntry");
    // _MdsMktDataSnapshotHead
    c2py::caster::try_generate<_MdsMktDataSnapshotHead>(c, "to_MdsMktDataSnapshotHead");
    // _MdsIndexSnapshotBody
    c2py::caster::try_generate<_MdsIndexSnapshotBody>(c, "to_MdsIndexSnapshotBody");
    // _MdsStockSnapshotBody
    c2py::caster::try_generate<_MdsStockSnapshotBody>(c, "to_MdsStockSnapshotBody");
    // _MdsL1SnapshotBody
    c2py::caster::try_generate<_MdsL1SnapshotBody>(c, "to_MdsL1SnapshotBody");
    // _MdsL1Snapshot
    c2py::caster::try_generate<_MdsL1Snapshot>(c, "to_MdsL1Snapshot");
    // _MdsL2StockSnapshotBody
    c2py::caster::try_generate<_MdsL2StockSnapshotBody>(c, "to_MdsL2StockSnapshotBody");
    // _MdsL2StockSnapshotIncremental
    c2py::caster::try_generate<_MdsL2StockSnapshotIncremental>(c, "to_MdsL2StockSnapshotIncremental");
    // _MdsL2BestOrdersSnapshotBody
    c2py::caster::try_generate<_MdsL2BestOrdersSnapshotBody>(c, "to_MdsL2BestOrdersSnapshotBody");
    // _MdsL2BestOrdersSnapshotIncremental
    c2py::caster::try_generate<_MdsL2BestOrdersSnapshotIncremental>(c, "to_MdsL2BestOrdersSnapshotIncremental");
    // _MdsL2MarketOverview
    c2py::caster::try_generate<_MdsL2MarketOverview>(c, "to_MdsL2MarketOverview");
    // _MdsL2SnapshotBody
    c2py::caster::try_generate<_MdsL2SnapshotBody>(c, "to_MdsL2SnapshotBody");
    // _MdsMktDataSnapshot
    c2py::caster::try_generate<_MdsMktDataSnapshot>(c, "to_MdsMktDataSnapshot");
    // _MdsL2Trade
    c2py::caster::try_generate<_MdsL2Trade>(c, "to_MdsL2Trade");
    // _MdsL2Order
    c2py::caster::try_generate<_MdsL2Order>(c, "to_MdsL2Order");
    // _MdsWholeMktMsgBody
    c2py::caster::try_generate<_MdsWholeMktMsgBody>(c, "to_MdsWholeMktMsgBody");
    // _MdsStockStaticInfo
    c2py::caster::try_generate<_MdsStockStaticInfo>(c, "to_MdsStockStaticInfo");
    // _MdsQryMktDataSnapshotReq
    c2py::caster::try_generate<_MdsQryMktDataSnapshotReq>(c, "to_MdsQryMktDataSnapshotReq");
    // _MdsQryTrdSessionStatusReq
    c2py::caster::try_generate<_MdsQryTrdSessionStatusReq>(c, "to_MdsQryTrdSessionStatusReq");
    // _MdsQryReqHeadT
    c2py::caster::try_generate<_MdsQryReqHeadT>(c, "to_MdsQryReqHeadT");
    // _MdsQryRspHeadT
    c2py::caster::try_generate<_MdsQryRspHeadT>(c, "to_MdsQryRspHeadT");
    // _MdsQryCursor
    c2py::caster::try_generate<_MdsQryCursor>(c, "to_MdsQryCursor");
    // _MdsQrySecurityCodeEntry
    c2py::caster::try_generate<_MdsQrySecurityCodeEntry>(c, "to_MdsQrySecurityCodeEntry");
    // _MdsQryStockStaticInfoFilter
    c2py::caster::try_generate<_MdsQryStockStaticInfoFilter>(c, "to_MdsQryStockStaticInfoFilter");
    // _MdsQryStockStaticInfoReq
    c2py::caster::try_generate<_MdsQryStockStaticInfoReq>(c, "to_MdsQryStockStaticInfoReq");
    // _MdsQryStockStaticInfoRsp
    c2py::caster::try_generate<_MdsQryStockStaticInfoRsp>(c, "to_MdsQryStockStaticInfoRsp");
    // _MdsQrySnapshotListFilter
    c2py::caster::try_generate<_MdsQrySnapshotListFilter>(c, "to_MdsQrySnapshotListFilter");
    // _MdsQrySnapshotListReq
    c2py::caster::try_generate<_MdsQrySnapshotListReq>(c, "to_MdsQrySnapshotListReq");
    // _MdsQrySnapshotListRsp
    c2py::caster::try_generate<_MdsQrySnapshotListRsp>(c, "to_MdsQrySnapshotListRsp");
    // _MdsMktDataRequestEntry
    c2py::caster::try_generate<_MdsMktDataRequestEntry>(c, "to_MdsMktDataRequestEntry");
    // _MdsMktDataRequestReq
    c2py::caster::try_generate<_MdsMktDataRequestReq>(c, "to_MdsMktDataRequestReq");
    // _MdsMktDataRequestReqBuf
    c2py::caster::try_generate<_MdsMktDataRequestReqBuf>(c, "to_MdsMktDataRequestReqBuf");
    // _MdsMktDataRequestRsp
    c2py::caster::try_generate<_MdsMktDataRequestRsp>(c, "to_MdsMktDataRequestRsp");
    // _MdsTestRequestReq
    c2py::caster::try_generate<_MdsTestRequestReq>(c, "to_MdsTestRequestReq");
    // _MdsTestRequestRsp
    c2py::caster::try_generate<_MdsTestRequestRsp>(c, "to_MdsTestRequestRsp");
    // _MdsChangePasswordReq
    c2py::caster::try_generate<_MdsChangePasswordReq>(c, "to_MdsChangePasswordReq");
    // _MdsChangePasswordRsp
    c2py::caster::try_generate<_MdsChangePasswordRsp>(c, "to_MdsChangePasswordRsp");
    // _MdsMktReqMsgBody
    c2py::caster::try_generate<_MdsMktReqMsgBody>(c, "to_MdsMktReqMsgBody");
    // _MdsMktRspMsgBody
    c2py::caster::try_generate<_MdsMktRspMsgBody>(c, "to_MdsMktRspMsgBody");
    // _MdsUdpPktHead
    c2py::caster::try_generate<_MdsUdpPktHead>(c, "to_MdsUdpPktHead");
    // _MdsApiClientCfg
    c2py::caster::try_generate<_MdsApiClientCfg>(c, "to_MdsApiClientCfg");
    // _MdsApiClientEnv
    c2py::caster::try_generate<_MdsApiClientEnv>(c, "to_MdsApiClientEnv");
    // int8
    c2py::caster::try_generate<int8>(c, "toint8");
    // uint8
    c2py::caster::try_generate<uint8>(c, "touint8");
    // int16
    c2py::caster::try_generate<int16>(c, "toint16");
    // uint16
    c2py::caster::try_generate<uint16>(c, "touint16");
    // int32
    c2py::caster::try_generate<int32>(c, "toint32");
    // uint32
    c2py::caster::try_generate<uint32>(c, "touint32");
    // int64
    c2py::caster::try_generate<int64>(c, "toint64");
    // uint64
    c2py::caster::try_generate<uint64>(c, "touint64");
    // float32
    c2py::caster::try_generate<float32>(c, "tofloat32");
    // float64
    c2py::caster::try_generate<float64>(c, "tofloat64");
    // float128
    c2py::caster::try_generate<float128>(c, "tofloat128");
    // eOesExchangeIdT
    c2py::caster::try_generate<eOesExchangeIdT>(c, "toeOesExchangeIdT");
    // eOesMarketIdT
    c2py::caster::try_generate<eOesMarketIdT>(c, "toeOesMarketIdT");
    // eOesPlatformIdT
    c2py::caster::try_generate<eOesPlatformIdT>(c, "toeOesPlatformIdT");
    // eOesMarketStateT
    c2py::caster::try_generate<eOesMarketStateT>(c, "toeOesMarketStateT");
    // eOesTrdSessTypeT
    c2py::caster::try_generate<eOesTrdSessTypeT>(c, "toeOesTrdSessTypeT");
    // eOesProductTypeT
    c2py::caster::try_generate<eOesProductTypeT>(c, "toeOesProductTypeT");
    // eOesSecurityTypeT
    c2py::caster::try_generate<eOesSecurityTypeT>(c, "toeOesSecurityTypeT");
    // eOesSubSecurityTypeT
    c2py::caster::try_generate<eOesSubSecurityTypeT>(c, "toeOesSubSecurityTypeT");
    // eOesSecurityLevelT
    c2py::caster::try_generate<eOesSecurityLevelT>(c, "toeOesSecurityLevelT");
    // eOesSecurityRiskLevelT
    c2py::caster::try_generate<eOesSecurityRiskLevelT>(c, "toeOesSecurityRiskLevelT");
    // eOesSecuritySuspFlagT
    c2py::caster::try_generate<eOesSecuritySuspFlagT>(c, "toeOesSecuritySuspFlagT");
    // eOesLotTypeT
    c2py::caster::try_generate<eOesLotTypeT>(c, "toeOesLotTypeT");
    // eOesLotRejReasonT
    c2py::caster::try_generate<eOesLotRejReasonT>(c, "toeOesLotRejReasonT");
    // eOesOrdStatusT
    c2py::caster::try_generate<eOesOrdStatusT>(c, "toeOesOrdStatusT");
    // eOesOrdTypeT
    c2py::caster::try_generate<eOesOrdTypeT>(c, "toeOesOrdTypeT");
    // eOesOrdTypeShT
    c2py::caster::try_generate<eOesOrdTypeShT>(c, "toeOesOrdTypeShT");
    // eOesOrdTypeSzT
    c2py::caster::try_generate<eOesOrdTypeSzT>(c, "toeOesOrdTypeSzT");
    // eOesBuySellTypeT
    c2py::caster::try_generate<eOesBuySellTypeT>(c, "toeOesBuySellTypeT");
    // eOesOrdDirT
    c2py::caster::try_generate<eOesOrdDirT>(c, "toeOesOrdDirT");
    // eOesEtfTrdCnfmTypeT
    c2py::caster::try_generate<eOesEtfTrdCnfmTypeT>(c, "toeOesEtfTrdCnfmTypeT");
    // eOesEtfSubFlagT
    c2py::caster::try_generate<eOesEtfSubFlagT>(c, "toeOesEtfSubFlagT");
    // eOesExecTypeT
    c2py::caster::try_generate<eOesExecTypeT>(c, "toeOesExecTypeT");
    // eOesCurrTypeT
    c2py::caster::try_generate<eOesCurrTypeT>(c, "toeOesCurrTypeT");
    // eOesFeeTypeT
    c2py::caster::try_generate<eOesFeeTypeT>(c, "toeOesFeeTypeT");
    // eOesCalcFeeModeT
    c2py::caster::try_generate<eOesCalcFeeModeT>(c, "toeOesCalcFeeModeT");
    // eOesFundTrsfDirectT
    c2py::caster::try_generate<eOesFundTrsfDirectT>(c, "toeOesFundTrsfDirectT");
    // eOesFundTrsfTypeT
    c2py::caster::try_generate<eOesFundTrsfTypeT>(c, "toeOesFundTrsfTypeT");
    // eOesFundTrsfStatusT
    c2py::caster::try_generate<eOesFundTrsfStatusT>(c, "toeOesFundTrsfStatusT");
    // eOesAcctTypeT
    c2py::caster::try_generate<eOesAcctTypeT>(c, "toeOesAcctTypeT");
    // eOesCashTypeT
    c2py::caster::try_generate<eOesCashTypeT>(c, "toeOesCashTypeT");
    // eOesAcctStatusT
    c2py::caster::try_generate<eOesAcctStatusT>(c, "toeOesAcctStatusT");
    // eOesTradingPermissionT
    c2py::caster::try_generate<eOesTradingPermissionT>(c, "toeOesTradingPermissionT");
    // eOesTradingLimitT
    c2py::caster::try_generate<eOesTradingLimitT>(c, "toeOesTradingLimitT");
    // eOesQualificationClassT
    c2py::caster::try_generate<eOesQualificationClassT>(c, "toeOesQualificationClassT");
    // eOesInvestorClassT
    c2py::caster::try_generate<eOesInvestorClassT>(c, "toeOesInvestorClassT");
    // eOesCustTypeT
    c2py::caster::try_generate<eOesCustTypeT>(c, "toeOesCustTypeT");
    // eOesOwnerTypeT
    c2py::caster::try_generate<eOesOwnerTypeT>(c, "toeOesOwnerTypeT");
    // eOesClientTypeT
    c2py::caster::try_generate<eOesClientTypeT>(c, "toeOesClientTypeT");
    // eOesClientStatusT
    c2py::caster::try_generate<eOesClientStatusT>(c, "toeOesClientStatusT");
    // eOesOptContractTypeT
    c2py::caster::try_generate<eOesOptContractTypeT>(c, "toeOesOptContractTypeT");
    // eOesOptInvLevelT
    c2py::caster::try_generate<eOesOptInvLevelT>(c, "toeOesOptInvLevelT");
    // eOpenFlagTypeT
    c2py::caster::try_generate<eOpenFlagTypeT>(c, "toeOpenFlagTypeT");
    // eOesOptionOpenFlagT
    c2py::caster::try_generate<eOesOptionOpenFlagT>(c, "toeOesOptionOpenFlagT");
    // eOesPositionEffT
    c2py::caster::try_generate<eOesPositionEffT>(c, "toeOesPositionEffT");
    // eOesOptionTypeT
    c2py::caster::try_generate<eOesOptionTypeT>(c, "toeOesOptionTypeT");
    // OesOrdReqT
    c2py::caster::try_generate<OesOrdReqT>(c, "toOesOrdReqT");
    // OesOrdCancelReqT
    c2py::caster::try_generate<OesOrdCancelReqT>(c, "toOesOrdCancelReqT");
    // OesOrdRejectT
    c2py::caster::try_generate<OesOrdRejectT>(c, "toOesOrdRejectT");
    // OesOrdCnfmT
    c2py::caster::try_generate<OesOrdCnfmT>(c, "toOesOrdCnfmT");
    // OesTrdBaseInfoT
    c2py::caster::try_generate<OesTrdBaseInfoT>(c, "toOesTrdBaseInfoT");
    // OesTrdCnfmT
    c2py::caster::try_generate<OesTrdCnfmT>(c, "toOesTrdCnfmT");
    // OesLotWinningBaseInfoT
    c2py::caster::try_generate<OesLotWinningBaseInfoT>(c, "toOesLotWinningBaseInfoT");
    // OesFundTrsfBaseInfoT
    c2py::caster::try_generate<OesFundTrsfBaseInfoT>(c, "toOesFundTrsfBaseInfoT");
    // OesFundTrsfReqT
    c2py::caster::try_generate<OesFundTrsfReqT>(c, "toOesFundTrsfReqT");
    // OesFundTrsfRejectT
    c2py::caster::try_generate<OesFundTrsfRejectT>(c, "toOesFundTrsfRejectT");
    // OesFundTrsfReportT
    c2py::caster::try_generate<OesFundTrsfReportT>(c, "toOesFundTrsfReportT");
    // OesIssueBaseInfoT
    c2py::caster::try_generate<OesIssueBaseInfoT>(c, "toOesIssueBaseInfoT");
    // OesPriceLimitT
    c2py::caster::try_generate<OesPriceLimitT>(c, "toOesPriceLimitT");
    // OesStockBaseInfoT
    c2py::caster::try_generate<OesStockBaseInfoT>(c, "toOesStockBaseInfoT");
    // OesEtfBaseInfoT
    c2py::caster::try_generate<OesEtfBaseInfoT>(c, "toOesEtfBaseInfoT");
    // OesEtfComponentBaseInfoT
    c2py::caster::try_generate<OesEtfComponentBaseInfoT>(c, "toOesEtfComponentBaseInfoT");
    // OesOptionBaseInfoT
    c2py::caster::try_generate<OesOptionBaseInfoT>(c, "toOesOptionBaseInfoT");
    // OesCashAssetBaseInfoT
    c2py::caster::try_generate<OesCashAssetBaseInfoT>(c, "toOesCashAssetBaseInfoT");
    // OesCustBaseInfoT
    c2py::caster::try_generate<OesCustBaseInfoT>(c, "toOesCustBaseInfoT");
    // OesInvAcctBaseInfoT
    c2py::caster::try_generate<OesInvAcctBaseInfoT>(c, "toOesInvAcctBaseInfoT");
    // OesStkHoldingBaseInfoT
    c2py::caster::try_generate<OesStkHoldingBaseInfoT>(c, "toOesStkHoldingBaseInfoT");
    // OesOptHoldingBaseInfoT
    c2py::caster::try_generate<OesOptHoldingBaseInfoT>(c, "toOesOptHoldingBaseInfoT");
    // OesMarketStateInfoT
    c2py::caster::try_generate<OesMarketStateInfoT>(c, "toOesMarketStateInfoT");
    // OesTradingPermissionEntryT
    c2py::caster::try_generate<OesTradingPermissionEntryT>(c, "toOesTradingPermissionEntryT");
    // eSMsgProtocolTypeT
    c2py::caster::try_generate<eSMsgProtocolTypeT>(c, "toeSMsgProtocolTypeT");
    // eSMsgFlagT
    c2py::caster::try_generate<eSMsgFlagT>(c, "toeSMsgFlagT");
    // SMsgHeadT
    c2py::caster::try_generate<SMsgHeadT>(c, "toSMsgHeadT");
    // OesQryCursorT
    c2py::caster::try_generate<OesQryCursorT>(c, "toOesQryCursorT");
    // OesQryReqHeadT
    c2py::caster::try_generate<OesQryReqHeadT>(c, "toOesQryReqHeadT");
    // OesQryRspHeadT
    c2py::caster::try_generate<OesQryRspHeadT>(c, "toOesQryRspHeadT");
    // OesQryOrdFilterT
    c2py::caster::try_generate<OesQryOrdFilterT>(c, "toOesQryOrdFilterT");
    // OesOrdItemT
    c2py::caster::try_generate<OesOrdItemT>(c, "toOesOrdItemT");
    // OesQryOrdReqT
    c2py::caster::try_generate<OesQryOrdReqT>(c, "toOesQryOrdReqT");
    // OesQryOrdRspT
    c2py::caster::try_generate<OesQryOrdRspT>(c, "toOesQryOrdRspT");
    // OesQryTrdFilterT
    c2py::caster::try_generate<OesQryTrdFilterT>(c, "toOesQryTrdFilterT");
    // OesTrdItemT
    c2py::caster::try_generate<OesTrdItemT>(c, "toOesTrdItemT");
    // OesQryTrdReqT
    c2py::caster::try_generate<OesQryTrdReqT>(c, "toOesQryTrdReqT");
    // OesQryTrdRspT
    c2py::caster::try_generate<OesQryTrdRspT>(c, "toOesQryTrdRspT");
    // OesQryCashAssetFilterT
    c2py::caster::try_generate<OesQryCashAssetFilterT>(c, "toOesQryCashAssetFilterT");
    // OesCashAssetItemT
    c2py::caster::try_generate<OesCashAssetItemT>(c, "toOesCashAssetItemT");
    // OesQryCashAssetReqT
    c2py::caster::try_generate<OesQryCashAssetReqT>(c, "toOesQryCashAssetReqT");
    // OesQryCashAssetRspT
    c2py::caster::try_generate<OesQryCashAssetRspT>(c, "toOesQryCashAssetRspT");
    // OesCounterCashItemT
    c2py::caster::try_generate<OesCounterCashItemT>(c, "toOesCounterCashItemT");
    // OesQryCounterCashReqT
    c2py::caster::try_generate<OesQryCounterCashReqT>(c, "toOesQryCounterCashReqT");
    // OesQryCounterCashRspT
    c2py::caster::try_generate<OesQryCounterCashRspT>(c, "toOesQryCounterCashRspT");
    // OesQryStkHoldingFilterT
    c2py::caster::try_generate<OesQryStkHoldingFilterT>(c, "toOesQryStkHoldingFilterT");
    // OesStkHoldingItemT
    c2py::caster::try_generate<OesStkHoldingItemT>(c, "toOesStkHoldingItemT");
    // OesQryStkHoldingReqT
    c2py::caster::try_generate<OesQryStkHoldingReqT>(c, "toOesQryStkHoldingReqT");
    // OesQryStkHoldingRspT
    c2py::caster::try_generate<OesQryStkHoldingRspT>(c, "toOesQryStkHoldingRspT");
    // OesQryOptHoldingFilterT
    c2py::caster::try_generate<OesQryOptHoldingFilterT>(c, "toOesQryOptHoldingFilterT");
    // OesOptHoldingItemT
    c2py::caster::try_generate<OesOptHoldingItemT>(c, "toOesOptHoldingItemT");
    // OesQryOptHoldingReqT
    c2py::caster::try_generate<OesQryOptHoldingReqT>(c, "toOesQryOptHoldingReqT");
    // OesQryOptHoldingRspT
    c2py::caster::try_generate<OesQryOptHoldingRspT>(c, "toOesQryOptHoldingRspT");
    // OesQryCustFilterT
    c2py::caster::try_generate<OesQryCustFilterT>(c, "toOesQryCustFilterT");
    // OesCustItemT
    c2py::caster::try_generate<OesCustItemT>(c, "toOesCustItemT");
    // OesQryCustReqT
    c2py::caster::try_generate<OesQryCustReqT>(c, "toOesQryCustReqT");
    // OesQryCustRspT
    c2py::caster::try_generate<OesQryCustRspT>(c, "toOesQryCustRspT");
    // OesQryInvAcctFilterT
    c2py::caster::try_generate<OesQryInvAcctFilterT>(c, "toOesQryInvAcctFilterT");
    // OesInvAcctItemT
    c2py::caster::try_generate<OesInvAcctItemT>(c, "toOesInvAcctItemT");
    // OesQryInvAcctReqT
    c2py::caster::try_generate<OesQryInvAcctReqT>(c, "toOesQryInvAcctReqT");
    // OesQryInvAcctRspT
    c2py::caster::try_generate<OesQryInvAcctRspT>(c, "toOesQryInvAcctRspT");
    // OesInvAcctOverviewT
    c2py::caster::try_generate<OesInvAcctOverviewT>(c, "toOesInvAcctOverviewT");
    // OesCashAcctOverviewT
    c2py::caster::try_generate<OesCashAcctOverviewT>(c, "toOesCashAcctOverviewT");
    // OesCustOverviewT
    c2py::caster::try_generate<OesCustOverviewT>(c, "toOesCustOverviewT");
    // OesClientOverviewT
    c2py::caster::try_generate<OesClientOverviewT>(c, "toOesClientOverviewT");
    // OesQryCommissionRateFilterT
    c2py::caster::try_generate<OesQryCommissionRateFilterT>(c, "toOesQryCommissionRateFilterT");
    // OesCommissionRateItemT
    c2py::caster::try_generate<OesCommissionRateItemT>(c, "toOesCommissionRateItemT");
    // OesQryCommissionRateReqT
    c2py::caster::try_generate<OesQryCommissionRateReqT>(c, "toOesQryCommissionRateReqT");
    // OesQryCommissionRateRspT
    c2py::caster::try_generate<OesQryCommissionRateRspT>(c, "toOesQryCommissionRateRspT");
    // OesQryFundTransferSerialFilterT
    c2py::caster::try_generate<OesQryFundTransferSerialFilterT>(c, "toOesQryFundTransferSerialFilterT");
    // OesFundTransferSerialItemT
    c2py::caster::try_generate<OesFundTransferSerialItemT>(c, "toOesFundTransferSerialItemT");
    // OesQryFundTransferSerialReqT
    c2py::caster::try_generate<OesQryFundTransferSerialReqT>(c, "toOesQryFundTransferSerialReqT");
    // OesQryFundTransferSerialRspT
    c2py::caster::try_generate<OesQryFundTransferSerialRspT>(c, "toOesQryFundTransferSerialRspT");
    // OesQryLotWinningFilterT
    c2py::caster::try_generate<OesQryLotWinningFilterT>(c, "toOesQryLotWinningFilterT");
    // OesLotWinningItemT
    c2py::caster::try_generate<OesLotWinningItemT>(c, "toOesLotWinningItemT");
    // OesQryLotWinningReqT
    c2py::caster::try_generate<OesQryLotWinningReqT>(c, "toOesQryLotWinningReqT");
    // OesQryLotWinningRspT
    c2py::caster::try_generate<OesQryLotWinningRspT>(c, "toOesQryLotWinningRspT");
    // OesQryIssueFilterT
    c2py::caster::try_generate<OesQryIssueFilterT>(c, "toOesQryIssueFilterT");
    // OesIssueItemT
    c2py::caster::try_generate<OesIssueItemT>(c, "toOesIssueItemT");
    // OesQryIssueReqT
    c2py::caster::try_generate<OesQryIssueReqT>(c, "toOesQryIssueReqT");
    // OesQryIssueRspT
    c2py::caster::try_generate<OesQryIssueRspT>(c, "toOesQryIssueRspT");
    // OesQryStockFilterT
    c2py::caster::try_generate<OesQryStockFilterT>(c, "toOesQryStockFilterT");
    // OesStockItemT
    c2py::caster::try_generate<OesStockItemT>(c, "toOesStockItemT");
    // OesQryStockReqT
    c2py::caster::try_generate<OesQryStockReqT>(c, "toOesQryStockReqT");
    // OesQryStockRspT
    c2py::caster::try_generate<OesQryStockRspT>(c, "toOesQryStockRspT");
    // OesQryEtfFilterT
    c2py::caster::try_generate<OesQryEtfFilterT>(c, "toOesQryEtfFilterT");
    // OesEtfItemT
    c2py::caster::try_generate<OesEtfItemT>(c, "toOesEtfItemT");
    // OesQryEtfReqT
    c2py::caster::try_generate<OesQryEtfReqT>(c, "toOesQryEtfReqT");
    // OesQryEtfRspT
    c2py::caster::try_generate<OesQryEtfRspT>(c, "toOesQryEtfRspT");
    // OesQryEtfComponentFilterT
    c2py::caster::try_generate<OesQryEtfComponentFilterT>(c, "toOesQryEtfComponentFilterT");
    // OesEtfComponentItemT
    c2py::caster::try_generate<OesEtfComponentItemT>(c, "toOesEtfComponentItemT");
    // OesQryEtfComponentReqT
    c2py::caster::try_generate<OesQryEtfComponentReqT>(c, "toOesQryEtfComponentReqT");
    // OesQryEtfComponentRspT
    c2py::caster::try_generate<OesQryEtfComponentRspT>(c, "toOesQryEtfComponentRspT");
    // OesQryOptionFilterT
    c2py::caster::try_generate<OesQryOptionFilterT>(c, "toOesQryOptionFilterT");
    // OesOptionItemT
    c2py::caster::try_generate<OesOptionItemT>(c, "toOesOptionItemT");
    // OesQryOptionReqT
    c2py::caster::try_generate<OesQryOptionReqT>(c, "toOesQryOptionReqT");
    // OesQryOptionRspT
    c2py::caster::try_generate<OesQryOptionRspT>(c, "toOesQryOptionRspT");
    // OesQryTradingDayRspT
    c2py::caster::try_generate<OesQryTradingDayRspT>(c, "toOesQryTradingDayRspT");
    // OesQryMarketStateFilterT
    c2py::caster::try_generate<OesQryMarketStateFilterT>(c, "toOesQryMarketStateFilterT");
    // OesMarketStateItemT
    c2py::caster::try_generate<OesMarketStateItemT>(c, "toOesMarketStateItemT");
    // OesQryMarketStateReqT
    c2py::caster::try_generate<OesQryMarketStateReqT>(c, "toOesQryMarketStateReqT");
    // OesQryMarketStateRspT
    c2py::caster::try_generate<OesQryMarketStateRspT>(c, "toOesQryMarketStateRspT");
    // OesQryReqMsgT
    c2py::caster::try_generate<OesQryReqMsgT>(c, "toOesQryReqMsgT");
    // OesQryRspMsgT
    c2py::caster::try_generate<OesQryRspMsgT>(c, "toOesQryRspMsgT");
    // eOesMsgTypeT
    c2py::caster::try_generate<eOesMsgTypeT>(c, "toeOesMsgTypeT");
    // eOesSubscribeReportTypeT
    c2py::caster::try_generate<eOesSubscribeReportTypeT>(c, "toeOesSubscribeReportTypeT");
    // eOesProtocolHintsTypeT
    c2py::caster::try_generate<eOesProtocolHintsTypeT>(c, "toeOesProtocolHintsTypeT");
    // OesReportSynchronizationReqT
    c2py::caster::try_generate<OesReportSynchronizationReqT>(c, "toOesReportSynchronizationReqT");
    // OesReportSynchronizationRspT
    c2py::caster::try_generate<OesReportSynchronizationRspT>(c, "toOesReportSynchronizationRspT");
    // OesTestRequestReqT
    c2py::caster::try_generate<OesTestRequestReqT>(c, "toOesTestRequestReqT");
    // OesTestRequestRspT
    c2py::caster::try_generate<OesTestRequestRspT>(c, "toOesTestRequestRspT");
    // OesChangePasswordReqT
    c2py::caster::try_generate<OesChangePasswordReqT>(c, "toOesChangePasswordReqT");
    // OesChangePasswordRspT
    c2py::caster::try_generate<OesChangePasswordRspT>(c, "toOesChangePasswordRspT");
    // OesBatchOrdersHeadT
    c2py::caster::try_generate<OesBatchOrdersHeadT>(c, "toOesBatchOrdersHeadT");
    // OesBatchOrdersReqT
    c2py::caster::try_generate<OesBatchOrdersReqT>(c, "toOesBatchOrdersReqT");
    // OesRptMsgHeadT
    c2py::caster::try_generate<OesRptMsgHeadT>(c, "toOesRptMsgHeadT");
    // OesRptMsgBodyT
    c2py::caster::try_generate<OesRptMsgBodyT>(c, "toOesRptMsgBodyT");
    // OesRptMsgT
    c2py::caster::try_generate<OesRptMsgT>(c, "toOesRptMsgT");
    // OesReqMsgBodyT
    c2py::caster::try_generate<OesReqMsgBodyT>(c, "toOesReqMsgBodyT");
    // OesRspMsgBodyT
    c2py::caster::try_generate<OesRspMsgBodyT>(c, "toOesRspMsgBodyT");
    // SErrMsgT
    c2py::caster::try_generate<SErrMsgT>(c, "toSErrMsgT");
    // SDataBufferT
    c2py::caster::try_generate<SDataBufferT>(c, "toSDataBufferT");
    // eSSocketProtocolTypeT
    c2py::caster::try_generate<eSSocketProtocolTypeT>(c, "toeSSocketProtocolTypeT");
    // SSocketUriInfoT
    c2py::caster::try_generate<SSocketUriInfoT>(c, "toSSocketUriInfoT");
    // SSocketIpPortInfoT
    c2py::caster::try_generate<SSocketIpPortInfoT>(c, "toSSocketIpPortInfoT");
    // SSocketChannelInfoT
    c2py::caster::try_generate<SSocketChannelInfoT>(c, "toSSocketChannelInfoT");
    // SSocketOptionConfigT
    c2py::caster::try_generate<SSocketOptionConfigT>(c, "toSSocketOptionConfigT");
    // eGeneralClientClusterTypeT
    c2py::caster::try_generate<eGeneralClientClusterTypeT>(c, "toeGeneralClientClusterTypeT");
    // eGeneralClientEncryptTypeT
    c2py::caster::try_generate<eGeneralClientEncryptTypeT>(c, "toeGeneralClientEncryptTypeT");
    // SGeneralClientChannelT
    c2py::caster::try_generate<SGeneralClientChannelT>(c, "toSGeneralClientChannelT");
    // SGeneralClientChannelGroupT
    c2py::caster::try_generate<SGeneralClientChannelGroupT>(c, "toSGeneralClientChannelGroupT");
    // SGeneralClientAddrInfoT
    c2py::caster::try_generate<SGeneralClientAddrInfoT>(c, "toSGeneralClientAddrInfoT");
    // SGeneralClientRemoteCfgT
    c2py::caster::try_generate<SGeneralClientRemoteCfgT>(c, "toSGeneralClientRemoteCfgT");
    // eOesApiChannelTypeT
    c2py::caster::try_generate<eOesApiChannelTypeT>(c, "toeOesApiChannelTypeT");
    // OesApiSessionInfoT
    c2py::caster::try_generate<OesApiSessionInfoT>(c, "toOesApiSessionInfoT");
    // OesApiChannelGroupT
    c2py::caster::try_generate<OesApiChannelGroupT>(c, "toOesApiChannelGroupT");
    // OesApiAddrInfoT
    c2py::caster::try_generate<OesApiAddrInfoT>(c, "toOesApiAddrInfoT");
    // OesApiRemoteCfgT
    c2py::caster::try_generate<OesApiRemoteCfgT>(c, "toOesApiRemoteCfgT");
    // OesApiSubscribeInfoT
    c2py::caster::try_generate<OesApiSubscribeInfoT>(c, "toOesApiSubscribeInfoT");
    // OesApiClientCfgT
    c2py::caster::try_generate<OesApiClientCfgT>(c, "toOesApiClientCfgT");
    // OesApiClientEnvT
    c2py::caster::try_generate<OesApiClientEnvT>(c, "toOesApiClientEnvT");
    // F_OESAPI_ON_RPT_MSG_T
    c2py::caster::try_generate<F_OESAPI_ON_RPT_MSG_T>(c, "toF_OESAPI_ON_RPT_MSG_T");
    // F_OESAPI_ON_QRY_MSG_T
    c2py::caster::try_generate<F_OESAPI_ON_QRY_MSG_T>(c, "toF_OESAPI_ON_QRY_MSG_T");
    // eMdsExchangeIdT
    c2py::caster::try_generate<eMdsExchangeIdT>(c, "toeMdsExchangeIdT");
    // eMdsMsgSourceT
    c2py::caster::try_generate<eMdsMsgSourceT>(c, "toeMdsMsgSourceT");
    // eMdsMdProductTypeT
    c2py::caster::try_generate<eMdsMdProductTypeT>(c, "toeMdsMdProductTypeT");
    // eMdsMdStreamTypeT
    c2py::caster::try_generate<eMdsMdStreamTypeT>(c, "toeMdsMdStreamTypeT");
    // eMdsMdLevelT
    c2py::caster::try_generate<eMdsMdLevelT>(c, "toeMdsMdLevelT");
    // eMdsL2PriceLevelOperatorT
    c2py::caster::try_generate<eMdsL2PriceLevelOperatorT>(c, "toeMdsL2PriceLevelOperatorT");
    // eMdsL2TradeExecTypeT
    c2py::caster::try_generate<eMdsL2TradeExecTypeT>(c, "toeMdsL2TradeExecTypeT");
    // eMdsL2TradeBSFlagT
    c2py::caster::try_generate<eMdsL2TradeBSFlagT>(c, "toeMdsL2TradeBSFlagT");
    // eMdsL2OrderSideT
    c2py::caster::try_generate<eMdsL2OrderSideT>(c, "toeMdsL2OrderSideT");
    // eMdsL2OrderTypeT
    c2py::caster::try_generate<eMdsL2OrderTypeT>(c, "toeMdsL2OrderTypeT");
    // eMdsClientTypeT
    c2py::caster::try_generate<eMdsClientTypeT>(c, "toeMdsClientTypeT");
    // eMdsClientStatusT
    c2py::caster::try_generate<eMdsClientStatusT>(c, "toeMdsClientStatusT");
    // MdsTradingSessionStatusMsgT
    c2py::caster::try_generate<MdsTradingSessionStatusMsgT>(c, "toMdsTradingSessionStatusMsgT");
    // MdsSecurityStatusMsgT
    c2py::caster::try_generate<MdsSecurityStatusMsgT>(c, "toMdsSecurityStatusMsgT");
    // MdsPriceLevelEntryT
    c2py::caster::try_generate<MdsPriceLevelEntryT>(c, "toMdsPriceLevelEntryT");
    // MdsMktDataSnapshotHeadT
    c2py::caster::try_generate<MdsMktDataSnapshotHeadT>(c, "toMdsMktDataSnapshotHeadT");
    // MdsIndexSnapshotBodyT
    c2py::caster::try_generate<MdsIndexSnapshotBodyT>(c, "toMdsIndexSnapshotBodyT");
    // MdsStockSnapshotBodyT
    c2py::caster::try_generate<MdsStockSnapshotBodyT>(c, "toMdsStockSnapshotBodyT");
    // MdsL1SnapshotBodyT
    c2py::caster::try_generate<MdsL1SnapshotBodyT>(c, "toMdsL1SnapshotBodyT");
    // MdsL1SnapshotT
    c2py::caster::try_generate<MdsL1SnapshotT>(c, "toMdsL1SnapshotT");
    // MdsL2StockSnapshotBodyT
    c2py::caster::try_generate<MdsL2StockSnapshotBodyT>(c, "toMdsL2StockSnapshotBodyT");
    // MdsL2StockSnapshotIncrementalT
    c2py::caster::try_generate<MdsL2StockSnapshotIncrementalT>(c, "toMdsL2StockSnapshotIncrementalT");
    // MdsL2BestOrdersSnapshotBodyT
    c2py::caster::try_generate<MdsL2BestOrdersSnapshotBodyT>(c, "toMdsL2BestOrdersSnapshotBodyT");
    // MdsL2BestOrdersSnapshotIncrementalT
    c2py::caster::try_generate<MdsL2BestOrdersSnapshotIncrementalT>(c, "toMdsL2BestOrdersSnapshotIncrementalT");
    // MdsL2MarketOverviewT
    c2py::caster::try_generate<MdsL2MarketOverviewT>(c, "toMdsL2MarketOverviewT");
    // MdsL2SnapshotBodyT
    c2py::caster::try_generate<MdsL2SnapshotBodyT>(c, "toMdsL2SnapshotBodyT");
    // MdsMktDataSnapshotT
    c2py::caster::try_generate<MdsMktDataSnapshotT>(c, "toMdsMktDataSnapshotT");
    // MdsL2TradeT
    c2py::caster::try_generate<MdsL2TradeT>(c, "toMdsL2TradeT");
    // MdsL2OrderT
    c2py::caster::try_generate<MdsL2OrderT>(c, "toMdsL2OrderT");
    // MdsWholeMktMsgBodyT
    c2py::caster::try_generate<MdsWholeMktMsgBodyT>(c, "toMdsWholeMktMsgBodyT");
    // MdsStockStaticInfoT
    c2py::caster::try_generate<MdsStockStaticInfoT>(c, "toMdsStockStaticInfoT");
    // MdsQryMktDataSnapshotReqT
    c2py::caster::try_generate<MdsQryMktDataSnapshotReqT>(c, "toMdsQryMktDataSnapshotReqT");
    // MdsQrySecurityStatusReqT
    c2py::caster::try_generate<MdsQrySecurityStatusReqT>(c, "toMdsQrySecurityStatusReqT");
    // MdsQryTrdSessionStatusReqT
    c2py::caster::try_generate<MdsQryTrdSessionStatusReqT>(c, "toMdsQryTrdSessionStatusReqT");
    // MdsQryReqHeadT
    c2py::caster::try_generate<MdsQryReqHeadT>(c, "toMdsQryReqHeadT");
    // MdsQryRspHeadT
    c2py::caster::try_generate<MdsQryRspHeadT>(c, "toMdsQryRspHeadT");
    // MdsQryCursorT
    c2py::caster::try_generate<MdsQryCursorT>(c, "toMdsQryCursorT");
    // MdsQrySecurityCodeEntryT
    c2py::caster::try_generate<MdsQrySecurityCodeEntryT>(c, "toMdsQrySecurityCodeEntryT");
    // MdsQryStockStaticInfoFilterT
    c2py::caster::try_generate<MdsQryStockStaticInfoFilterT>(c, "toMdsQryStockStaticInfoFilterT");
    // MdsQryStockStaticInfoReqT
    c2py::caster::try_generate<MdsQryStockStaticInfoReqT>(c, "toMdsQryStockStaticInfoReqT");
    // MdsQryStockStaticInfoRspT
    c2py::caster::try_generate<MdsQryStockStaticInfoRspT>(c, "toMdsQryStockStaticInfoRspT");
    // MdsQrySnapshotListFilterT
    c2py::caster::try_generate<MdsQrySnapshotListFilterT>(c, "toMdsQrySnapshotListFilterT");
    // MdsQrySnapshotListReqT
    c2py::caster::try_generate<MdsQrySnapshotListReqT>(c, "toMdsQrySnapshotListReqT");
    // MdsQrySnapshotListRspT
    c2py::caster::try_generate<MdsQrySnapshotListRspT>(c, "toMdsQrySnapshotListRspT");
    // eMdsMsgTypeT
    c2py::caster::try_generate<eMdsMsgTypeT>(c, "toeMdsMsgTypeT");
    // eMdsSubscribeModeT
    c2py::caster::try_generate<eMdsSubscribeModeT>(c, "toeMdsSubscribeModeT");
    // eMdsMktSubscribeFlagT
    c2py::caster::try_generate<eMdsMktSubscribeFlagT>(c, "toeMdsMktSubscribeFlagT");
    // eMdsSubscribedTickTypeT
    c2py::caster::try_generate<eMdsSubscribedTickTypeT>(c, "toeMdsSubscribedTickTypeT");
    // eMdsSubscribedTickExpireTypeT
    c2py::caster::try_generate<eMdsSubscribedTickExpireTypeT>(c, "toeMdsSubscribedTickExpireTypeT");
    // eMdsSubscribeDataTypeT
    c2py::caster::try_generate<eMdsSubscribeDataTypeT>(c, "toeMdsSubscribeDataTypeT");
    // eMdsTickChannelNoT
    c2py::caster::try_generate<eMdsTickChannelNoT>(c, "toeMdsTickChannelNoT");
    // eMdsProtocolHintsTypeT
    c2py::caster::try_generate<eMdsProtocolHintsTypeT>(c, "toeMdsProtocolHintsTypeT");
    // MdsMktDataRequestEntryT
    c2py::caster::try_generate<MdsMktDataRequestEntryT>(c, "toMdsMktDataRequestEntryT");
    // MdsMktDataRequestReqT
    c2py::caster::try_generate<MdsMktDataRequestReqT>(c, "toMdsMktDataRequestReqT");
    // MdsMktDataRequestReqBufT
    c2py::caster::try_generate<MdsMktDataRequestReqBufT>(c, "toMdsMktDataRequestReqBufT");
    // MdsMktDataRequestRspT
    c2py::caster::try_generate<MdsMktDataRequestRspT>(c, "toMdsMktDataRequestRspT");
    // MdsTestRequestReqT
    c2py::caster::try_generate<MdsTestRequestReqT>(c, "toMdsTestRequestReqT");
    // MdsTestRequestRspT
    c2py::caster::try_generate<MdsTestRequestRspT>(c, "toMdsTestRequestRspT");
    // MdsChangePasswordReqT
    c2py::caster::try_generate<MdsChangePasswordReqT>(c, "toMdsChangePasswordReqT");
    // MdsChangePasswordRspT
    c2py::caster::try_generate<MdsChangePasswordRspT>(c, "toMdsChangePasswordRspT");
    // MdsMktReqMsgBodyT
    c2py::caster::try_generate<MdsMktReqMsgBodyT>(c, "toMdsMktReqMsgBodyT");
    // MdsMktRspMsgBodyT
    c2py::caster::try_generate<MdsMktRspMsgBodyT>(c, "toMdsMktRspMsgBodyT");
    // MdsUdpPktHeadT
    c2py::caster::try_generate<MdsUdpPktHeadT>(c, "toMdsUdpPktHeadT");
    // eMdsApiChannelTypeT
    c2py::caster::try_generate<eMdsApiChannelTypeT>(c, "toeMdsApiChannelTypeT");
    // MdsApiSessionInfoT
    c2py::caster::try_generate<MdsApiSessionInfoT>(c, "toMdsApiSessionInfoT");
    // MdsApiChannelGroupT
    c2py::caster::try_generate<MdsApiChannelGroupT>(c, "toMdsApiChannelGroupT");
    // MdsApiAddrInfoT
    c2py::caster::try_generate<MdsApiAddrInfoT>(c, "toMdsApiAddrInfoT");
    // MdsApiRemoteCfgT
    c2py::caster::try_generate<MdsApiRemoteCfgT>(c, "toMdsApiRemoteCfgT");
    // MdsApiSubscribeInfoT
    c2py::caster::try_generate<MdsApiSubscribeInfoT>(c, "toMdsApiSubscribeInfoT");
    // MdsApiClientCfgT
    c2py::caster::try_generate<MdsApiClientCfgT>(c, "toMdsApiClientCfgT");
    // MdsApiClientEnvT
    c2py::caster::try_generate<MdsApiClientEnvT>(c, "toMdsApiClientEnvT");
    // F_MDSAPI_ONMSG_T
    c2py::caster::try_generate<F_MDSAPI_ONMSG_T>(c, "toF_MDSAPI_ONMSG_T");
    // F_MDSAPI_ON_QRY_MSG_T
    c2py::caster::try_generate<F_MDSAPI_ON_QRY_MSG_T>(c, "toF_MDSAPI_ON_QRY_MSG_T");
}
