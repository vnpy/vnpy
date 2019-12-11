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
