# noinspection PyUnresolvedReferences
from typing import *
# noinspection PyUnresolvedReferences
from enum import Enum


class OesOrdReqT:
    clSeqNo: int
    mktId: int
    ordType: int
    bsType: int
    __ORD_BASE_INFO_filler: int
    invAcctId: str
    securityId: str
    ordQty: int
    ordPrice: int
    origClOrdId: int
    userInfo: int
    __ordReqOrigSendTime: STimeval32T  # unknown what to wrap in py
    ...
_OesOrdReq = OesOrdReqT


class OesOrdCancelReqT:
    clSeqNo: int
    mktId: int
    __ORD_CANCEL_BASE_INFO_filler1: Sequence[int]
    invAcctId: str
    securityId: str
    origClSeqNo: int
    origClEnvId: int
    __ORD_CANCEL_BASE_INFO_filler2: Sequence[int]
    origClOrdId: int
    userInfo: int
    __ordReqOrigSendTime: STimeval32T  # unknown what to wrap in py
    ...
_OesOrdCancelReq = OesOrdCancelReqT


class OesOrdRejectT:
    clSeqNo: int
    mktId: int
    ordType: int
    bsType: int
    __ORD_BASE_INFO_filler: int
    invAcctId: str
    securityId: str
    ordQty: int
    ordPrice: int
    origClOrdId: int
    userInfo: int
    __ordReqOrigSendTime: STimeval32T  # unknown what to wrap in py
    origClSeqNo: int
    origClEnvId: int
    clEnvId: int
    clientId: int
    ordDate: int
    ordTime: int
    ordRejReason: int
    __filler: int
    ...
_OesOrdReject = OesOrdRejectT


class OesOrdCnfmT:
    clSeqNo: int
    mktId: int
    ordType: int
    bsType: int
    __ORD_BASE_INFO_filler: int
    invAcctId: str
    securityId: str
    ordQty: int
    ordPrice: int
    origClOrdId: int
    userInfo: int
    __ordReqOrigSendTime: STimeval32T  # unknown what to wrap in py
    clOrdId: int
    clientId: int
    clEnvId: int
    origClEnvId: int
    origClSeqNo: int
    ordDate: int
    ordTime: int
    ordCnfmTime: int
    ordStatus: int
    ordCnfmSts: int
    securityType: int
    subSecurityType: int
    __platformId: int
    __tgwGrpNo: int
    __declareFlag: int
    __ORD_CNFM_BASE_INFO_filler: int
    exchOrdId: str
    frzAmt: int
    frzInterest: int
    frzFee: int
    cumAmt: int
    cumInterest: int
    cumFee: int
    cumQty: int
    canceledQty: int
    ordRejReason: int
    exchErrCode: int
    pbuId: int
    branchId: int
    __rowNum: int
    __recNum: int
    __ordReqOrigRecvTime: STimeval32T  # unknown what to wrap in py
    __ordReqCollectedTime: STimeval32T  # unknown what to wrap in py
    __ordReqActualDealTime: STimeval32T  # unknown what to wrap in py
    __ordReqProcessedTime: STimeval32T  # unknown what to wrap in py
    __ordCnfmOrigRecvTime: STimeval32T  # unknown what to wrap in py
    __ordCnfmCollectedTime: STimeval32T  # unknown what to wrap in py
    __ordCnfmActualDealTime: STimeval32T  # unknown what to wrap in py
    __ordCnfmProcessedTime: STimeval32T  # unknown what to wrap in py
    __ordDeclareTime: STimeval32T  # unknown what to wrap in py
    __ordDeclareDoneTime: STimeval32T  # unknown what to wrap in py
    __pushingTime: STimeval32T  # unknown what to wrap in py
    ...
OesOrdItemT = OesOrdCnfmT
_OesOrdCnfm = OesOrdCnfmT


class OesTrdBaseInfoT:
    exchTrdNum: int
    mktId: int
    trdSide: int
    __platformId: int
    __trdCnfmType: int
    __etfTrdCnfmSeq: int
    invAcctId: str
    securityId: str
    trdDate: int
    trdTime: int
    trdQty: int
    trdPrice: int
    trdAmt: int
    clOrdId: int
    cumQty: int
    __rowNum: int
    __tgwGrpNo: int
    __TRD_BASE_INFO_filler: Sequence[int]
    origOrdQty: int
    pbuId: int
    branchId: int
    ...
_OesTrdBaseInfo = OesTrdBaseInfoT


class OesTrdCnfmT:
    exchTrdNum: int
    mktId: int
    trdSide: int
    __platformId: int
    __trdCnfmType: int
    __etfTrdCnfmSeq: int
    invAcctId: str
    securityId: str
    trdDate: int
    trdTime: int
    trdQty: int
    trdPrice: int
    trdAmt: int
    clOrdId: int
    cumQty: int
    __rowNum: int
    __tgwGrpNo: int
    __TRD_BASE_INFO_filler: Sequence[int]
    origOrdQty: int
    pbuId: int
    branchId: int
    clSeqNo: int
    clientId: int
    clEnvId: int
    subSecurityType: int
    ordStatus: int
    ordType: int
    ordBuySellType: int
    securityType: int
    origOrdPrice: int
    cumAmt: int
    cumInterest: int
    cumFee: int
    userInfo: int
    __trdCnfmOrigRecvTime: STimeval32T  # unknown what to wrap in py
    __trdCnfmCollectedTime: STimeval32T  # unknown what to wrap in py
    __trdCnfmActualDealTime: STimeval32T  # unknown what to wrap in py
    __trdCnfmProcessedTime: STimeval32T  # unknown what to wrap in py
    __pushingTime: STimeval32T  # unknown what to wrap in py
    ...
OesTrdItemT = OesTrdCnfmT
_OesTrdCnfm = OesTrdCnfmT


class OesLotWinningBaseInfoT:
    invAcctId: str
    securityId: str
    mktId: int
    lotType: int
    rejReason: int
    __LOT_WINNING_BASE_INFO_filler: int
    lotDate: int
    securityName: str
    assignNum: int
    lotQty: int
    lotPrice: int
    lotAmt: int
    ...
_OesLotWinningBaseInfo = OesLotWinningBaseInfoT
OesLotWinningItemT = OesLotWinningBaseInfoT


class OesFundTrsfBaseInfoT:
    clSeqNo: int
    direct: int
    isAllotOnly: int
    __FUND_TRSF_BASE_filler: Sequence[int]
    cashAcctId: str
    trdPasswd: str
    trsfPasswd: str
    occurAmt: int
    userInfo: int
    ...
_OesFundTrsfBaseInfo = OesFundTrsfBaseInfoT


class OesFundTrsfReqT:
    clSeqNo: int
    direct: int
    isAllotOnly: int
    __FUND_TRSF_BASE_filler: Sequence[int]
    cashAcctId: str
    trdPasswd: str
    trsfPasswd: str
    occurAmt: int
    userInfo: int
    ...
_OesFundTrsfReq = OesFundTrsfReqT


class OesFundTrsfRejectT:
    clSeqNo: int
    direct: int
    isAllotOnly: int
    __FUND_TRSF_BASE_filler: Sequence[int]
    cashAcctId: str
    trdPasswd: str
    trsfPasswd: str
    occurAmt: int
    userInfo: int
    ordDate: int
    ordTime: int
    clientId: int
    clEnvId: int
    __filler: int
    rejReason: int
    errorInfo: str
    ...
_OesFundTrsfReject = OesFundTrsfRejectT


class OesFundTrsfReportT:
    clSeqNo: int
    clientId: int
    clEnvId: int
    direct: int
    cashAcctId: str
    occurAmt: int
    userInfo: int
    fundTrsfId: int
    counterEntrustNo: int
    operDate: int
    operTime: int
    dclrTime: int
    doneTime: int
    isAllotOnly: int
    trsfStatus: int
    __hasCounterTransfered: int
    __filler: int
    rejReason: int
    counterErrCode: int
    __filler2: int
    allotSerialNo: str
    errorInfo: str
    ...
_OesFundTrsfReport = OesFundTrsfReportT
OesFundTransferSerialItemT = OesFundTrsfReportT


class OesIssueBaseInfoT:
    securityId: str
    mktId: int
    securityType: int
    subSecurityType: int
    isCancelAble: int
    isReApplyAble: int
    __ISSUE_BASE_filler: Sequence[int]
    securityName: str
    underlyingSecurityId: str
    startDate: int
    endDate: int
    issueQty: int
    qtyUnit: int
    ordMaxQty: int
    ordMinQty: int
    issuePrice: int
    ceilPrice: int
    floorPrice: int
    ...
_OesIssueBaseInfo = OesIssueBaseInfoT
OesIssueItemT = OesIssueBaseInfoT


class OesPriceLimitT:
    ceilPrice: int
    floorPrice: int
    ...
_OesPriceLimit = OesPriceLimitT


class OesStockBaseInfoT:
    securityId: str
    mktId: int
    securityType: int
    subSecurityType: int
    securityLevel: int
    securityRiskLevel: int
    currType: int
    qualificationClass: int
    isDayTrading: int
    suspFlag: int
    temporarySuspFlag: int
    __filter: Sequence[int]
    buyQtyUnit: int
    sellQtyUnit: int
    buyOrdMaxQty: int
    buyOrdMinQty: int
    sellOrdMaxQty: int
    sellOrdMinQty: int
    priceUnit: int
    prevClose: int
    parPrice: int
    bondInterest: int
    repoExpirationDays: int
    cashHoldDays: int
    priceLimit: Sequence[OesPriceLimitT]
    securityName: str
    fundId: str
    ...
OesStockItemT = OesStockBaseInfoT
_OesStockBaseInfo = OesStockBaseInfoT


class OesEtfBaseInfoT:
    fundId: str
    securityId: str
    mktId: int
    securityType: int
    subSecurityType: int
    isPublishIOPV: int
    isCreationAble: int
    isRedemptionAble: int
    isDisabled: int
    __ETF_BASE_filler: int
    componentCnt: int
    creRdmUnit: int
    maxCashRatio: int
    nav: int
    navPerCU: int
    dividendPerCU: int
    tradingDay: int
    preTradingDay: int
    estiCashCmpoent: int
    cashCmpoent: int
    creationLimit: int
    redemLimit: int
    netCreationLimit: int
    netRedemLimit: int
    ...
_OesEtfBaseInfo = OesEtfBaseInfoT
OesEtfItemT = OesEtfBaseInfoT


class OesEtfComponentBaseInfoT:
    fundId: str
    securityId: str
    mktId: int
    subFlag: int
    securityType: int
    subSecurityType: int
    prevClose: int
    qty: int
    premiumRate: int
    creationSubCash: int
    redemptionCashSub: int
    ...
_OesEtfComponentBaseInfo = OesEtfComponentBaseInfoT


class OesOptionBaseInfoT:
    securityId: str
    mktId: int
    securityType: int
    subSecurityType: int
    contractType: int
    openFlag: int
    optionType: int
    suspFlag: int
    temporarySuspFlag: int
    contractMultiplierUnit: int
    excPrice: int
    startDate: int
    endDate: int
    execDate: int
    expDate: int
    closePrice: int
    settlPrice: int
    roundLot: int
    tickSize: int
    ceilPrice: int
    floorPrice: int
    marginUnit: int
    leavesQty: int
    lmtOrdMaxQty: int
    lmtOrdMinQty: int
    mktOrdMaxQty: int
    mktOrdMinQty: int
    underlyingSecurityId: str
    underlyingMktId: int
    underlyingSecuType: int
    closeEndDateFlag: int
    __OPTION_BASE_filler1: int
    underlyingClosePrice: int
    securityName: str
    ...
_OesOptionBaseInfo = OesOptionBaseInfoT
OesOptionItemT = OesOptionBaseInfoT


class OesCashAssetBaseInfoT:
    cashAcctId: str
    custId: str
    currType: int
    cashType: int
    cashAcctStatus: int
    isFundTrsfDisabled: int
    __CASH_ASSET_BASE_filler: Sequence[int]
    beginningBal: int
    beginningAvailableBal: int
    beginningDrawableBal: int
    disableBal: int
    reversalAmt: int
    manualFrzAmt: int
    totalDepositAmt: int
    totalWithdrawAmt: int
    withdrawFrzAmt: int
    totalSellAmt: int
    totalBuyAmt: int
    buyFrzAmt: int
    totalFeeAmt: int
    feeFrzAmt: int
    marginAmt: int
    marginFrzAmt: int
    ...
_OesCashAssetBaseInfo = OesCashAssetBaseInfoT


class OesCustBaseInfoT:
    custId: str
    custType: int
    status: int
    riskLevel: int
    originRiskLevel: int
    institutionFlag: int
    investorClass: int
    __CUST_BASE_filler1: Sequence[int]
    branchId: int
    __CUST_BASE_filler2: int
    ...
OesCustItemT = OesCustBaseInfoT
_OesCustBaseInfo = OesCustBaseInfoT


class OesInvAcctBaseInfoT:
    invAcctId: str
    mktId: int
    acctType: int
    status: int
    ownerType: int
    optInvLevel: int
    isTradeDisabled: int
    __INV_ACCT_BASE_filler: Sequence[int]
    limits: int
    permissions: int
    pbuId: int
    subscriptionQuota: int
    ...
_OesInvAcctBaseInfo = OesInvAcctBaseInfoT


class OesStkHoldingBaseInfoT:
    invAcctId: str
    securityId: str
    mktId: int
    securityType: int
    subSecurityType: int
    __HOLD_BASE_filler: Sequence[int]
    originalHld: int
    originalCostAmt: int
    totalBuyHld: int
    totalSellHld: int
    sellFrzHld: int
    manualFrzHld: int
    totalBuyAmt: int
    totalSellAmt: int
    totalBuyFee: int
    totalSellFee: int
    totalTrsfInHld: int
    totalTrsfOutHld: int
    trsfOutFrzHld: int
    lockHld: int
    lockFrzHld: int
    unlockFrzHld: int
    coveredFrzHld: int
    coveredHld: int
    ...
_OesStkHoldingBaseInfo = OesStkHoldingBaseInfoT


class OesOptHoldingBaseInfoT:
    invAcctId: str
    securityId: str
    mktId: int
    __HOLD_BASE_filler: Sequence[int]
    hldA: int
    hldB: int
    hldC: int
    hldC2: int
    hldRA: int
    hldRB: int
    hldRC: int
    ...
_OesOptHoldingBaseInfo = OesOptHoldingBaseInfoT


class OesMarketStateInfoT:
    exchId: int
    platformId: int
    mktId: int
    mktState: int
    __filler: Sequence[int]
    ...
OesMarketStateItemT = OesMarketStateInfoT
_OesMarketStateInfo = OesMarketStateInfoT


class OesTradingPermissionEntryT:
    permissionNo: int
    isDisabled: int
    counterAlias: int
    __filler: Sequence[int]
    permissionCode: int
    applicableMarkets: Sequence[int]
    permissionMemo: str
    ...
_OesTradingPermissionEntry = OesTradingPermissionEntryT


class OesInputSourceInfoT:
    sourceIp: str
    sourceMac: str
    sourceType: int
    __filler: Sequence[int]
    sourceDriverId: str
    ...
_OesInputSourceInfo = OesInputSourceInfoT


class SMsgHeadT:
    msgFlag: int
    msgId: int
    status: int
    detailStatus: int
    msgSize: int
    ...
_SMsgHead = SMsgHeadT


class OesQryCursorT:
    seqNo: int
    isEnd: int
    __filler: Sequence[int]
    userInfo: int
    ...
_OesQryCursor = OesQryCursorT


class OesQryReqHeadT:
    maxPageSize: int
    lastPosition: int
    ...
_OesQryReqHead = OesQryReqHeadT


class OesQryRspHeadT:
    itemCount: int
    lastPosition: int
    isEnd: int
    __filler: Sequence[int]
    userInfo: int
    ...
_OesQryRspHead = OesQryRspHeadT


class OesQryOrdFilterT:
    custId: str
    invAcctId: str
    mktId: int
    isUnclosedOnly: int
    clEnvId: int
    securityType: int
    bsType: int
    __filler: Sequence[int]
    clOrdId: int
    clSeqNo: int
    startTime: int
    endTime: int
    userInfo: int
    ...
_OesQryOrdFilter = OesQryOrdFilterT


class OesQryOrdReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryOrdFilterT
    ...
_OesQryOrdReq = OesQryOrdReqT


class OesQryOrdRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesOrdCnfmT]
    ...
_OesQryOrdRsp = OesQryOrdRspT


class OesQryTrdFilterT:
    custId: str
    invAcctId: str
    mktId: int
    clEnvId: int
    securityType: int
    bsType: int
    __filler: int
    clOrdId: int
    clSeqNo: int
    startTime: int
    endTime: int
    userInfo: int
    ...
_OesQryTrdFilter = OesQryTrdFilterT


class OesQryTrdReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryTrdFilterT
    ...
_OesQryTrdReq = OesQryTrdReqT


class OesQryTrdRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesTrdCnfmT]
    ...
_OesQryTrdRsp = OesQryTrdRspT


class OesQryCashAssetFilterT:
    custId: str
    cashAcctId: str
    userInfo: int
    ...
_OesQryCashAssetFilter = OesQryCashAssetFilterT


class OesCashAssetItemT:
    cashAcctId: str
    custId: str
    currType: int
    cashType: int
    cashAcctStatus: int
    isFundTrsfDisabled: int
    __CASH_ASSET_BASE_filler: Sequence[int]
    beginningBal: int
    beginningAvailableBal: int
    beginningDrawableBal: int
    disableBal: int
    reversalAmt: int
    manualFrzAmt: int
    totalDepositAmt: int
    totalWithdrawAmt: int
    withdrawFrzAmt: int
    totalSellAmt: int
    totalBuyAmt: int
    buyFrzAmt: int
    totalFeeAmt: int
    feeFrzAmt: int
    marginAmt: int
    marginFrzAmt: int
    currentTotalBal: int
    currentAvailableBal: int
    currentDrawableBal: int
    ...
_OesCashAssetItem = OesCashAssetItemT


class OesQryCashAssetReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryCashAssetFilterT
    ...
_OesQryCashAssetReq = OesQryCashAssetReqT


class OesQryCashAssetRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesCashAssetItemT]
    ...
_OesQryCashAssetRsp = OesQryCashAssetRspT


class OesCounterCashItemT:
    cashAcctId: str
    custId: str
    custName: str
    bankId: str
    cashType: int
    cashAcctStatus: int
    currType: int
    isFundTrsfDisabled: int
    __filler: Sequence[int]
    counterAvailableBal: int
    counterDrawableBal: int
    counterCashUpdateTime: int
    __reserve: Sequence[int]
    ...
_OesCounterCashItem = OesCounterCashItemT


class OesQryCounterCashReqT:
    cashAcctId: str
    ...
_OesQryCounterCashReq = OesQryCounterCashReqT


class OesQryCounterCashRspT:
    counterCashItem: OesCounterCashItemT
    ...
_OesQryCounterCashRsp = OesQryCounterCashRspT


class OesQryStkHoldingFilterT:
    custId: str
    invAcctId: str
    securityId: str
    mktId: int
    securityType: int
    __filler: Sequence[int]
    userInfo: int
    ...
OesQryOptHoldingFilterT = OesQryStkHoldingFilterT
_OesQryStkHoldingFilter = OesQryStkHoldingFilterT


class OesStkHoldingItemT:
    invAcctId: str
    securityId: str
    mktId: int
    securityType: int
    subSecurityType: int
    __HOLD_BASE_filler: Sequence[int]
    originalHld: int
    originalCostAmt: int
    totalBuyHld: int
    totalSellHld: int
    sellFrzHld: int
    manualFrzHld: int
    totalBuyAmt: int
    totalSellAmt: int
    totalBuyFee: int
    totalSellFee: int
    totalTrsfInHld: int
    totalTrsfOutHld: int
    trsfOutFrzHld: int
    lockHld: int
    lockFrzHld: int
    unlockFrzHld: int
    coveredFrzHld: int
    coveredHld: int
    sellAvlHld: int
    trsfOutAvlHld: int
    lockAvlHld: int
    coveredAvlHld: int
    sumHld: int
    costPrice: int
    ...
_OesStkHoldingItem = OesStkHoldingItemT


class OesQryStkHoldingReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryStkHoldingFilterT
    ...
_OesQryStkHoldingReq = OesQryStkHoldingReqT


class OesQryStkHoldingRspT:
    qryHead: OesQryRspHeadT
    qryItems: Sequence[OesStkHoldingItemT]
    ...
_OesQryStkHoldingRsp = OesQryStkHoldingRspT


class OesOptHoldingItemT:
    invAcctId: str
    securityId: str
    mktId: int
    __HOLD_BASE_filler: Sequence[int]
    hldA: int
    hldB: int
    hldC: int
    hldC2: int
    hldRA: int
    hldRB: int
    hldRC: int
    ...
_OesOptHoldingItem = OesOptHoldingItemT


class OesQryOptHoldingReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryStkHoldingFilterT
    ...
_OesQryOptHoldingReq = OesQryOptHoldingReqT


class OesQryOptHoldingRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesOptHoldingItemT]
    ...
_OesQryHoldRsp = OesQryOptHoldingRspT


class OesQryCustFilterT:
    custId: str
    userInfo: int
    ...
_OesQryCustFilter = OesQryCustFilterT


class OesQryCustReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryCustFilterT
    ...
_OesQryCustReq = OesQryCustReqT


class OesQryCustRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesCustBaseInfoT]
    ...
_OesQryCustRsp = OesQryCustRspT


class OesQryInvAcctFilterT:
    custId: str
    invAcctId: str
    mktId: int
    __filler: Sequence[int]
    userInfo: int
    ...
_OesQryInvAcctFilter = OesQryInvAcctFilterT


class OesInvAcctItemT:
    invAcctId: str
    mktId: int
    acctType: int
    status: int
    ownerType: int
    optInvLevel: int
    isTradeDisabled: int
    __INV_ACCT_BASE_filler: Sequence[int]
    limits: int
    permissions: int
    pbuId: int
    subscriptionQuota: int
    custId: str
    ...
_OesInvAcctItem = OesInvAcctItemT


class OesQryInvAcctReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryInvAcctFilterT
    ...
_OesQryInvAcctReq = OesQryInvAcctReqT


class OesQryInvAcctRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesInvAcctItemT]
    ...
_OesQryInvAcctRsp = OesQryInvAcctRspT


class OesInvAcctOverviewT:
    invAcctId: str
    mktId: int
    acctType: int
    status: int
    ownerType: int
    optInvLevel: int
    isTradeDisabled: int
    __INV_ACCT_BASE_filler: Sequence[int]
    limits: int
    permissions: int
    pbuId: int
    subscriptionQuota: int
    custId: str
    isValid: int
    __filler: Sequence[int]
    trdOrdCnt: int
    nonTrdOrdCnt: int
    cancelOrdCnt: int
    oesRejectOrdCnt: int
    exchRejectOrdCnt: int
    trdCnt: int
    __reserve: int
    ...
_OesInvAcctOverview = OesInvAcctOverviewT


class OesCashAcctOverviewT:
    cashAcctId: str
    custId: str
    bankId: str
    isValid: int
    cashType: int
    cashAcctStatus: int
    currType: int
    isFundTrsfDisabled: int
    __filler: Sequence[int]
    __reserve: int
    ...
_OesCashAcctOverview = OesCashAcctOverviewT


class OesCustOverviewT:
    custId: str
    custType: int
    status: int
    riskLevel: int
    originRiskLevel: int
    institutionFlag: int
    investorClass: int
    __CUST_BASE_filler1: Sequence[int]
    branchId: int
    __CUST_BASE_filler2: int
    custName: str
    spotCashAcct: OesCashAcctOverviewT
    creditCashAcct: OesCashAcctOverviewT
    optionCashAcct: OesCashAcctOverviewT
    shSpotInvAcct: OesInvAcctOverviewT
    shOptionInvAcct: OesInvAcctOverviewT
    szSpotInvAcct: OesInvAcctOverviewT
    szOptionInvAcct: OesInvAcctOverviewT
    __reserve: int
    ...
_OesCustOverview = OesCustOverviewT


class OesClientOverviewT:
    clientId: int
    clientType: int
    clientStatus: int
    isApiForbidden: int
    isBlockTrader: int
    __filler: Sequence[int]
    logonTime: int
    clientName: str
    clientMemo: str
    sseStkPbuId: int
    sseOptPbuId: int
    sseQualificationClass: int
    __filler2: Sequence[int]
    szseStkPbuId: int
    szseOptPbuId: int
    szseQualificationClass: int
    __filler3: Sequence[int]
    currOrdConnected: int
    currRptConnected: int
    currQryConnected: int
    maxOrdConnect: int
    maxRptConnect: int
    maxQryConnect: int
    ordTrafficLimit: int
    qryTrafficLimit: int
    __reserve: int
    associatedCustCnt: int
    __filler4: int
    custItems: Sequence[OesCustOverviewT]
    ...
_OesClientOverview = OesClientOverviewT


class OesQryCommissionRateFilterT:
    custId: str
    mktId: int
    securityType: int
    bsType: int
    __filler: Sequence[int]
    userInfo: int
    ...
_OesQryCommissionRateFilter = OesQryCommissionRateFilterT


class OesCommissionRateItemT:
    custId: str
    securityId: str
    mktId: int
    securityType: int
    subSecurityType: int
    bsType: int
    feeType: int
    currType: int
    calcFeeMode: int
    __filler: int
    feeRate: int
    minFee: int
    maxFee: int
    ...
_OesCommissionRateItem = OesCommissionRateItemT


class OesQryCommissionRateReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryCommissionRateFilterT
    ...
_OesQryCommissionRateReq = OesQryCommissionRateReqT


class OesQryCommissionRateRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesCommissionRateItemT]
    ...
_OesQryCommissionRateRsp = OesQryCommissionRateRspT


class OesQryFundTransferSerialFilterT:
    custId: str
    cashAcctId: str
    clSeqNo: int
    clEnvId: int
    __filler: Sequence[int]
    userInfo: int
    ...
_OesQryFundTransferSerialFilter = OesQryFundTransferSerialFilterT


class OesQryFundTransferSerialReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryFundTransferSerialFilterT
    ...
_OesQryFundTransferSerialReq = OesQryFundTransferSerialReqT


class OesQryFundTransferSerialRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesFundTrsfReportT]
    ...
_OesQryFundTransferSerialRsp = OesQryFundTransferSerialRspT


class OesQryLotWinningFilterT:
    custId: str
    invAcctId: str
    mktId: int
    lotType: int
    __filler: Sequence[int]
    startDate: int
    endDate: int
    userInfo: int
    ...
_OesQryLotWinningFilter = OesQryLotWinningFilterT


class OesQryLotWinningReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryLotWinningFilterT
    ...
_OesQryLotWinningReq = OesQryLotWinningReqT


class OesQryLotWinningRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesLotWinningBaseInfoT]
    ...
_OesQryLotWinningRsp = OesQryLotWinningRspT


class OesQryIssueFilterT:
    securityId: str
    mktId: int
    __filler: Sequence[int]
    userInfo: int
    ...
_OesQryIssueFilter = OesQryIssueFilterT


class OesQryIssueReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryIssueFilterT
    ...
_OesQryIssueReq = OesQryIssueReqT


class OesQryIssueRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesIssueBaseInfoT]
    ...
_OesQryIssueRsp = OesQryIssueRspT


class OesQryStockFilterT:
    securityId: str
    mktId: int
    securityType: int
    subSecurityType: int
    __filler: Sequence[int]
    userInfo: int
    ...
_OesQryStockFilter = OesQryStockFilterT


class OesQryStockReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryStockFilterT
    ...
_OesQryStockReq = OesQryStockReqT


class OesQryStockRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesStockBaseInfoT]
    ...
_OesQryStockRsp = OesQryStockRspT


class OesQryEtfFilterT:
    fundId: str
    mktId: int
    __filler: Sequence[int]
    userInfo: int
    ...
_OesQryEtfFilter = OesQryEtfFilterT


class OesQryEtfReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryEtfFilterT
    ...
_OesQryEtfReq = OesQryEtfReqT


class OesQryEtfRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesEtfBaseInfoT]
    ...
_OesQryEtfRsp = OesQryEtfRspT


class OesQryEtfComponentFilterT:
    fundId: str
    userInfo: int
    ...
_OesQryEtfComponentFilter = OesQryEtfComponentFilterT


class OesEtfComponentItemT:
    securityId: str
    mktId: int
    subFlag: int
    securityType: int
    subSecurityType: int
    prevClose: int
    qty: int
    premiumRate: int
    creationSubCash: int
    redemptionCashSub: int
    fundId: str
    ...
_OesEtfComponentItem = OesEtfComponentItemT


class OesQryEtfComponentReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryEtfComponentFilterT
    ...
_OesQryEtfComponentReq = OesQryEtfComponentReqT


class OesQryEtfComponentRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesEtfComponentItemT]
    ...
_OesQryEtfComponentRsp = OesQryEtfComponentRspT


class OesQryOptionFilterT:
    securityId: str
    mktId: int
    __filler: Sequence[int]
    userInfo: int
    ...
_OesQryOptionFilter = OesQryOptionFilterT


class OesQryOptionReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryOptionFilterT
    ...
_OesQryOptionReq = OesQryOptionReqT


class OesQryOptionRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesOptionBaseInfoT]
    ...
_OesQryOptionRsp = OesQryOptionRspT


class OesQryTradingDayRspT:
    tradingDay: int
    __filler: int
    ...
_OesQryTradingDayRsp = OesQryTradingDayRspT


class OesQryMarketStateFilterT:
    exchId: int
    platformId: int
    __filler: Sequence[int]
    userInfo: int
    ...
_OesQryMarketStateFilter = OesQryMarketStateFilterT


class OesQryMarketStateReqT:
    reqHead: OesQryReqHeadT
    qryFilter: OesQryMarketStateFilterT
    ...
_OesQryMarketStateReq = OesQryMarketStateReqT


class OesQryMarketStateRspT:
    rspHead: OesQryRspHeadT
    qryItems: Sequence[OesMarketStateInfoT]
    ...
_OesQryMarketStateRsp = OesQryMarketStateRspT


class OesQryReqMsgT:
    qryOrd: OesQryOrdReqT
    qryTrd: OesQryTrdReqT
    qryCashAsset: OesQryCashAssetReqT
    qryStkHolding: OesQryStkHoldingReqT
    qryOptHolding: OesQryOptHoldingReqT
    qryCust: OesQryCustReqT
    qryInvAcct: OesQryInvAcctReqT
    qryComms: OesQryCommissionRateReqT
    qryFundTrsf: OesQryFundTransferSerialReqT
    qryLotWinning: OesQryLotWinningReqT
    qryIssue: OesQryIssueReqT
    qryStock: OesQryStockReqT
    qryEtf: OesQryEtfReqT
    qryEtfComponent: OesQryEtfComponentReqT
    qryOption: OesQryOptionReqT
    qryMktState: OesQryMarketStateReqT
    qryCounterCash: OesQryCounterCashReqT
    ...
_OesQryReqMsg = OesQryReqMsgT


class OesQryRspMsgT:
    ordRsp: OesQryOrdRspT
    trdRsp: OesQryTrdRspT
    cashAssetRsp: OesQryCashAssetRspT
    stkHoldingRsp: OesQryStkHoldingRspT
    optHoldingRsp: OesQryOptHoldingRspT
    custRsp: OesQryCustRspT
    invAcctRsp: OesQryInvAcctRspT
    commsRateRsp: OesQryCommissionRateRspT
    fundTrsfRsp: OesQryFundTransferSerialRspT
    lotWinningRsp: OesQryLotWinningRspT
    issueRsp: OesQryIssueRspT
    stockRsp: OesQryStockRspT
    etfRsp: OesQryEtfRspT
    etfComponentRsp: OesQryEtfComponentRspT
    optionRsp: OesQryOptionRspT
    tradingDay: OesQryTradingDayRspT
    mktStateRsp: OesQryMarketStateRspT
    clientOverview: OesClientOverviewT
    counterCashRsp: OesQryCounterCashRspT
    ...
_OesQryRspMsg = OesQryRspMsgT


class OesLogonReqT:
    encryptMethod: int
    heartBtInt: int
    username: str
    password: str
    applVerId: str
    clientIp: str
    clientMac: str
    clEnvId: int
    sourceType: int
    __protocolHints: int
    __filler: Sequence[int]
    lastInMsgSeq: int
    lastOutMsgSeq: int
    clientDriverId: str
    ...
_OesLogonReq = OesLogonReqT


class OesLogonRspT:
    encryptMethod: int
    heartBtInt: int
    username: str
    applVerId: str
    minVerId: str
    hostNum: int
    isLeader: int
    leaderHostNum: int
    clEnvId: int
    clientType: int
    clientStatus: int
    __protocolHints: int
    __filler: int
    lastInMsgSeq: int
    lastOutMsgSeq: int
    ...
_OesLogonRsp = OesLogonRspT


class OesReportSynchronizationReqT:
    lastRptSeqNum: int
    subscribeEnvId: int
    __filler: Sequence[int]
    subscribeRptTypes: int
    ...
_OesReportSynchronizationReq = OesReportSynchronizationReqT


class OesReportSynchronizationRspT:
    lastRptSeqNum: int
    subscribeEnvId: int
    __filler: Sequence[int]
    subscribeRptTypes: int
    ...
_OesReportSynchronizationRsp = OesReportSynchronizationRspT


class OesTestRequestReqT:
    testReqId: str
    sendTime: str
    __filler: str
    ...
_OesTestRequestReq = OesTestRequestReqT


class OesTestRequestRspT:
    testReqId: str
    origSendTime: str
    __filler1: str
    respTime: str
    __filler2: str
    __recvTime: STimeval32T  # unknown what to wrap in py
    __collectedTime: STimeval32T  # unknown what to wrap in py
    __pushingTime: STimeval32T  # unknown what to wrap in py
    ...
_OesTestRequestRsp = OesTestRequestRspT


class OesChangePasswordReqT:
    encryptMethod: int
    __filler: int
    username: str
    userInfo: int
    oldPassword: str
    newPassword: str
    ...
_OesChangePasswordReq = OesChangePasswordReqT


class OesChangePasswordRspT:
    encryptMethod: int
    __filler: int
    username: str
    userInfo: int
    clientId: int
    clEnvId: int
    __filler2: int
    transDate: int
    transTime: int
    rejReason: int
    ...
_OesChangePasswordRsp = OesChangePasswordRspT


class OesBatchOrdersHeadT:
    itemCount: int
    __filler: int
    ...
_OesBatchOrdersHead = OesBatchOrdersHeadT


class OesBatchOrdersReqT:
    batchHead: OesBatchOrdersHeadT
    items: Sequence[OesOrdReqT]
    ...
_OesBatchOrdersReq = OesBatchOrdersReqT


class OesRptMsgHeadT:
    rptSeqNum: int
    rptMsgType: int
    execType: int
    bodyLength: int
    ordRejReason: int
    ...
_OesRptMsgHead = OesRptMsgHeadT


class OesRptMsgBodyT:
    ordInsertRsp: OesOrdCnfmT
    ordRejectRsp: OesOrdRejectT
    ordCnfm: OesOrdCnfmT
    trdCnfm: OesTrdCnfmT
    fundTrsfRejectRsp: OesFundTrsfRejectT
    fundTrsfCnfm: OesFundTrsfReportT
    cashAssetRpt: OesCashAssetItemT
    stkHoldingRpt: OesStkHoldingItemT
    optHoldingRpt: OesOptHoldingItemT
    ...
_OesRptMsgBody = OesRptMsgBodyT


class OesRptMsgT:
    rptHead: OesRptMsgHeadT
    rptBody: OesRptMsgBodyT
    ...
_OesRptMsg = OesRptMsgT


class OesReqMsgBodyT:
    ordReq: OesOrdReqT
    ordCancelReq: OesOrdCancelReqT
    batchOrdersReq: OesBatchOrdersReqT
    fundTrsfReq: OesFundTrsfReqT
    changePasswordReq: OesChangePasswordReqT
    testRequestReq: OesTestRequestReqT
    rptSyncReq: OesReportSynchronizationReqT
    logonReq: OesLogonReqT
    ...
_OesReqMsgBody = OesReqMsgBodyT


class OesRspMsgBodyT:
    rptMsg: OesRptMsgT
    mktStateRpt: OesMarketStateInfoT
    changePasswordRsp: OesChangePasswordRspT
    testRequestRsp: OesTestRequestRspT
    reportSynchronizationRsp: OesReportSynchronizationRspT
    logonRsp: OesLogonRspT
    ...
_OesRspMsgBody = OesRspMsgBodyT


class SErrMsgT:
    __index: int
    MODULE: int
    CODE: int
    __errCode: int
    __msgSize: int
    MSG: str
    ...
_SErrMsg = SErrMsgT


class SDataBufferT:
    dataSize: int
    bufSize: int
    buffer: char *const  # unknown what to wrap in py
    __ref: Any
    ...
_SDataBuffer = SDataBufferT


class _SDataBufferVar:
    dataSize: int
    bufSize: int
    buffer: str
    __ref: Any
    ...


class SSocketUriInfoT:
    uri: str
    ...
_SSocketUriInfo = SSocketUriInfoT


class SSocketIpPortInfoT:
    port: int
    ip: str
    ...
_SSocketIpPortInfo = SSocketIpPortInfoT


class SSocketChannelInfoT:
    remotePort: int
    protocolType: int
    _isNetByteOrder: int
    _isBroken: int
    _isSendBroken: int
    remoteAddr: str
    ...
_SSocketChannelInfo = SSocketChannelInfoT


class SSocketOptionConfigT:
    soRcvbuf: int
    soSndbuf: int
    tcpNodelay: int
    quickAck: int
    mcastTtlNum: int
    mcastLoopbackDisabled: int
    soBacklog: int
    connTimeoutMs: int
    keepIdle: int
    keepIntvl: int
    keepalive: int
    keepCnt: int
    __filler: Sequence[int]
    localSendingPort: int
    localSendingIp: str
    mcastInterfaceIp: str
    ...
_SSocketOptionConfig = SSocketOptionConfigT


class SGeneralClientChannelT:
    heartBtInt: int
    testReqInt: int
    protocolType: int
    remoteHostNum: int
    remoteIsLeader: int
    leaderHostNum: int
    __filler1: Sequence[int]
    __codecBuf: _SDataBufferVar
    __recvBuf: _SDataBufferVar
    __pDataStartPoint: str
    __customPtr: Any
    __reavedSize: int
    __customFlag: int
    __totalInMsgSize: int
    __totalCompressedSize: int
    __totalDecompressSize: int
    firstInMsgSeq: int
    lastInMsgSeq: int
    nextInMsgSeq: int
    lastRecvTime: struct timeval  # unknown what to wrap in py
    channel: SSocketChannelInfoT
    nextOutMsgSeq: int
    lastOutMsgSeq: int
    lastSendTime: struct timeval  # unknown what to wrap in py
    senderCompId: str
    targetCompId: str
    __magicNumber: int
    __magicSize: int
    __channelType: int
    __clEnvId: int
    __groupFlag: int
    __protocolHints: int
    __filler: Sequence[int]
    __reserveData: union (anonymous union at vnoes/include\sutil/net/spk_general_client_define.h:181:5)  # unknown what to wrap in py
    __extData: union (anonymous union at vnoes/include\sutil/net/spk_general_client_define.h:197:5)  # unknown what to wrap in py
    ...
MdsApiSessionInfoT = SGeneralClientChannelT
_SGeneralClientChannel = SGeneralClientChannelT
OesApiSessionInfoT = SGeneralClientChannelT


class SGeneralClientChannelGroupT:
    channelCount: int
    __customFlag: int
    channelList: Sequence[SGeneralClientChannelT]
    __maxFd: int
    __groupFlag: int
    __filler: Sequence[int]
    __fdSet: fd_set  # unknown what to wrap in py
    ...
_SGeneralClientChannelGroup = SGeneralClientChannelGroupT
OesApiChannelGroupT = SGeneralClientChannelGroupT
MdsApiChannelGroupT = SGeneralClientChannelGroupT


class SGeneralClientAddrInfoT:
    uri: str
    targetCompId: str
    username: str
    password: str
    hostNum: int
    __filler: Sequence[int]
    ...
MdsApiAddrInfoT = SGeneralClientAddrInfoT
OesApiAddrInfoT = SGeneralClientAddrInfoT
_SGeneralClientAddrInfo = SGeneralClientAddrInfoT


class SGeneralClientRemoteCfgT:
    addrCnt: int
    heartBtInt: int
    clusterType: int
    clEnvId: int
    __filler: Sequence[int]
    senderCompId: str
    targetCompId: str
    username: str
    password: str
    addrList: Sequence[SGeneralClientAddrInfoT]
    socketOpt: SSocketOptionConfigT
    ...
_SGeneralClientRemoteCfg = SGeneralClientRemoteCfgT
MdsApiRemoteCfgT = SGeneralClientRemoteCfgT
OesApiRemoteCfgT = SGeneralClientRemoteCfgT


class OesApiSubscribeInfoT:
    clEnvId: int
    __filler: Sequence[int]
    rptTypes: int
    ...
_OesApiSubscribeInfo = OesApiSubscribeInfoT


class OesApiClientCfgT:
    ordChannelCfg: SGeneralClientRemoteCfgT
    rptChannelCfg: SGeneralClientRemoteCfgT
    qryChannelCfg: SGeneralClientRemoteCfgT
    subscribeInfo: OesApiSubscribeInfoT
    ...
_OesApiClientCfg = OesApiClientCfgT


class OesApiClientEnvT:
    ordChannel: SGeneralClientChannelT
    rptChannel: SGeneralClientChannelT
    qryChannel: SGeneralClientChannelT
    ...
_OesApiClientEnv = OesApiClientEnvT


class MdsTradingSessionStatusMsgT:
    exchId: int
    securityType: int
    __isRepeated: int
    __filler1: int
    tradeDate: int
    updateTime: int
    __exchSendingTime: int
    __mdsRecvTime: int
    TotNoRelatedSym: int
    TradingSessionID: str
    __filler3: Sequence[int]
    __dataVersion: int
    __origTickSeq: int
    __origNetTime: STimeval32T  # unknown what to wrap in py
    __recvTime: STimeval32T  # unknown what to wrap in py
    __collectedTime: STimeval32T  # unknown what to wrap in py
    __processedTime: STimeval32T  # unknown what to wrap in py
    __pushingTime: STimeval32T  # unknown what to wrap in py
    ...
_MdsTradingSessionStatusMsg = MdsTradingSessionStatusMsgT


class MdsSecurityStatusMsgT:
    exchId: int
    securityType: int
    __isRepeated: int
    __filler1: int
    tradeDate: int
    updateTime: int
    __exchSendingTime: int
    __mdsRecvTime: int
    instrId: int
    SecurityID: str
    FinancialStatus: str
    __filler2: int
    __channelNo: int
    __dataVersion: int
    __origTickSeq: int
    NoSwitch: int
    __filler4: int
    switches: Sequence[None]
    __origNetTime: STimeval32T  # unknown what to wrap in py
    __recvTime: STimeval32T  # unknown what to wrap in py
    __collectedTime: STimeval32T  # unknown what to wrap in py
    __processedTime: STimeval32T  # unknown what to wrap in py
    __pushingTime: STimeval32T  # unknown what to wrap in py
    ...
_MdsSecurityStatusMsg = MdsSecurityStatusMsgT


class MdsPriceLevelEntryT:
    Price: int
    NumberOfOrders: int
    OrderQty: int
    ...
_MdsPriceLevelEntry = MdsPriceLevelEntryT


class MdsMktDataSnapshotHeadT:
    exchId: int
    securityType: int
    __isRepeated: int
    __origMdSource: int
    tradeDate: int
    updateTime: int
    instrId: int
    bodyLength: int
    mdStreamType: int
    __channelNo: int
    __dataVersion: int
    __origTickSeq: int
    __origNetTime: STimeval32T  # unknown what to wrap in py
    __recvTime: STimeval32T  # unknown what to wrap in py
    __collectedTime: STimeval32T  # unknown what to wrap in py
    __processedTime: STimeval32T  # unknown what to wrap in py
    __pushingTime: STimeval32T  # unknown what to wrap in py
    ...
_MdsMktDataSnapshotHead = MdsMktDataSnapshotHeadT


class MdsIndexSnapshotBodyT:
    SecurityID: str
    TradingPhaseCode: str
    __filler: str
    NumTrades: int
    TotalVolumeTraded: int
    TotalValueTraded: int
    PrevCloseIdx: int
    OpenIdx: int
    HighIdx: int
    LowIdx: int
    LastIdx: int
    CloseIdx: int
    StockNum: int
    __filler1: int
    ...
_MdsIndexSnapshotBody = MdsIndexSnapshotBodyT


class MdsStockSnapshotBodyT:
    SecurityID: str
    TradingPhaseCode: str
    __filler: str
    NumTrades: int
    TotalVolumeTraded: int
    TotalValueTraded: int
    PrevClosePx: int
    OpenPx: int
    HighPx: int
    LowPx: int
    TradePx: int
    ClosePx: int
    IOPV: int
    NAV: int
    TotalLongPosition: int
    BidLevels: Sequence[MdsPriceLevelEntryT]
    OfferLevels: Sequence[MdsPriceLevelEntryT]
    ...
_MdsStockSnapshotBody = MdsStockSnapshotBodyT


class MdsL1SnapshotBodyT:
    stock: MdsStockSnapshotBodyT
    option: MdsStockSnapshotBodyT
    index: MdsIndexSnapshotBodyT
    ...
_MdsL1SnapshotBody = MdsL1SnapshotBodyT


class MdsL2StockSnapshotBodyT:
    SecurityID: str
    TradingPhaseCode: str
    __filler: str
    NumTrades: int
    TotalVolumeTraded: int
    TotalValueTraded: int
    PrevClosePx: int
    OpenPx: int
    HighPx: int
    LowPx: int
    TradePx: int
    ClosePx: int
    IOPV: int
    NAV: int
    TotalLongPosition: int
    TotalBidQty: int
    TotalOfferQty: int
    WeightedAvgBidPx: int
    WeightedAvgOfferPx: int
    BidPriceLevel: int
    OfferPriceLevel: int
    BidLevels: Sequence[MdsPriceLevelEntryT]
    OfferLevels: Sequence[MdsPriceLevelEntryT]
    ...
_MdsL2StockSnapshotBody = MdsL2StockSnapshotBodyT


class MdsL2StockSnapshotIncrementalT:
    NumTrades: int
    TotalVolumeTraded: int
    TotalValueTraded: int
    OpenPx: int
    TradePx: int
    ClosePx: int
    IOPV: int
    TotalBidQty: int
    TotalOfferQty: int
    WeightedAvgBidPx: int
    WeightedAvgOfferPx: int
    BidPriceLevel: int
    OfferPriceLevel: int
    BestBidPrice: int
    HasContainedBestBidLevel: int
    NoBidLevel: int
    __filler1: Sequence[int]
    BestOfferPrice: int
    HasContainedBestOfferLevel: int
    NoOfferLevel: int
    __filler2: Sequence[int]
    PriceLevelOperator: Sequence[int]
    PriceLevels: Sequence[MdsPriceLevelEntryT]
    ...
_MdsL2StockSnapshotIncremental = MdsL2StockSnapshotIncrementalT


class MdsL2BestOrdersSnapshotBodyT:
    SecurityID: str
    __filler: Sequence[int]
    NoBidOrders: int
    NoOfferOrders: int
    TotalVolumeTraded: int
    BestBidPrice: int
    BestOfferPrice: int
    BidOrderQty: Sequence[int]
    OfferOrderQty: Sequence[int]
    ...
_MdsL2BestOrdersSnapshotBody = MdsL2BestOrdersSnapshotBodyT


class MdsL2BestOrdersSnapshotIncrementalT:
    TotalVolumeTraded: int
    BestBidPrice: int
    HasContainedBestBidLevel: int
    ContinualDeletedBidOrders: int
    NoBidOrders: int
    __filler1: int
    BestOfferPrice: int
    HasContainedBestOfferLevel: int
    ContinualDeletedOfferOrders: int
    NoOfferOrders: int
    __filler2: int
    OperatorEntryID: Sequence[int]
    OrderQty: Sequence[int]
    ...
_MdsL2BestOrdersSnapshotIncremental = MdsL2BestOrdersSnapshotIncrementalT


class MdsL2VirtualAuctionPriceT:
    SecurityID: str
    LeavesSide: int
    __filler: Sequence[int]
    Price: int
    VirtualAuctionQty: int
    LeavesQty: int
    ...
_MdsL2VirtualAuctionPrice = MdsL2VirtualAuctionPriceT


class MdsL2MarketOverviewT:
    OrigDate: int
    OrigTime: int
    __exchSendingTime: int
    __mdsRecvTime: int
    ...
_MdsL2MarketOverview = MdsL2MarketOverviewT


class MdsL2SnapshotBodyT:
    l2Stock: MdsL2StockSnapshotBodyT
    l2StockIncremental: MdsL2StockSnapshotIncrementalT
    l2BestOrders: MdsL2BestOrdersSnapshotBodyT
    l2BestOrdersIncremental: MdsL2BestOrdersSnapshotIncrementalT
    index: MdsIndexSnapshotBodyT
    l2VirtualAuctionPrice: MdsL2VirtualAuctionPriceT
    l2MarketOverview: MdsL2MarketOverviewT
    ...
_MdsL2SnapshotBody = MdsL2SnapshotBodyT


class MdsMktDataSnapshotT:
    head: MdsMktDataSnapshotHeadT
    l2Stock: MdsL2StockSnapshotBodyT
    l2StockIncremental: MdsL2StockSnapshotIncrementalT
    l2BestOrders: MdsL2BestOrdersSnapshotBodyT
    l2BestOrdersIncremental: MdsL2BestOrdersSnapshotIncrementalT
    stock: MdsStockSnapshotBodyT
    option: MdsStockSnapshotBodyT
    index: MdsIndexSnapshotBodyT
    l2VirtualAuctionPrice: MdsL2VirtualAuctionPriceT
    l2MarketOverview: MdsL2MarketOverviewT
    ...
_MdsMktDataSnapshot = MdsMktDataSnapshotT


class MdsL2TradeT:
    exchId: int
    securityType: int
    __isRepeated: int
    __filler1: int
    tradeDate: int
    TransactTime: int
    instrId: int
    ChannelNo: int
    ApplSeqNum: int
    SecurityID: str
    ExecType: int
    TradeBSFlag: int
    __filler3: Sequence[int]
    __channelNo: int
    __origTickSeq: int
    TradePrice: int
    TradeQty: int
    TradeMoney: int
    BidApplSeqNum: int
    OfferApplSeqNum: int
    __origNetTime: STimeval32T  # unknown what to wrap in py
    __recvTime: STimeval32T  # unknown what to wrap in py
    __collectedTime: STimeval32T  # unknown what to wrap in py
    __processedTime: STimeval32T  # unknown what to wrap in py
    __pushingTime: STimeval32T  # unknown what to wrap in py
    ...
_MdsL2Trade = MdsL2TradeT


class MdsL2OrderT:
    exchId: int
    securityType: int
    __isRepeated: int
    __filler1: int
    tradeDate: int
    TransactTime: int
    instrId: int
    ChannelNo: int
    ApplSeqNum: int
    SecurityID: str
    Side: int
    OrderType: int
    __filler3: Sequence[int]
    __channelNo: int
    __origTickSeq: int
    Price: int
    OrderQty: int
    __origNetTime: STimeval32T  # unknown what to wrap in py
    __recvTime: STimeval32T  # unknown what to wrap in py
    __collectedTime: STimeval32T  # unknown what to wrap in py
    __processedTime: STimeval32T  # unknown what to wrap in py
    __pushingTime: STimeval32T  # unknown what to wrap in py
    ...
_MdsL2Order = MdsL2OrderT


class MdsL2TickLostT:
    exchId: int
    __filler3: Sequence[int]
    tradeDate: int
    lostTime: int
    channelNo: int
    beginApplSeqNum: int
    endApplSeqNum: int
    __origTickSeq: int
    ...
_MdsL2TickLost = MdsL2TickLostT


class MdsQryMktDataSnapshotReqT:
    exchId: int
    securityType: int
    __filler: Sequence[int]
    instrId: int
    ...
MdsQrySecurityStatusReqT = MdsQryMktDataSnapshotReqT
_MdsQryMktDataSnapshotReq = MdsQryMktDataSnapshotReqT


class MdsQryTrdSessionStatusReqT:
    exchId: int
    securityType: int
    __filler: Sequence[int]
    ...
_MdsQryTrdSessionStatusReq = MdsQryTrdSessionStatusReqT


class MdsLogonReqT:
    encryptMethod: int
    heartBtInt: int
    username: str
    password: str
    applVerId: str
    ...
_MdsLogonReq = MdsLogonReqT


class MdsLogonRspT:
    encryptMethod: int
    heartBtInt: int
    username: str
    applVerId: str
    minVerId: str
    hostNum: int
    isLeader: int
    leaderHostNum: int
    __filler: Sequence[int]
    ...
_MdsLogonRsp = MdsLogonRspT


class MdsMktDataRequestEntryT:
    exchId: int
    securityType: int
    __filler: Sequence[int]
    instrId: int
    ...
_MdsMktDataRequestEntry = MdsMktDataRequestEntryT


class MdsMktDataRequestReqT:
    subMode: int
    tickType: int
    sseStockFlag: int
    sseIndexFlag: int
    sseOptionFlag: int
    szseStockFlag: int
    szseIndexFlag: int
    szseOptionFlag: int
    isRequireInitialMktData: int
    __channelNos: int
    tickExpireType: int
    __filler: int
    dataTypes: int
    beginTime: int
    subSecurityCnt: int
    ...
_MdsMktDataRequestReq = MdsMktDataRequestReqT


class MdsMktDataRequestReqBufT:
    mktDataRequestReq: MdsMktDataRequestReqT
    entries: Sequence[MdsMktDataRequestEntryT]
    ...
MdsApiSubscribeInfoT = MdsMktDataRequestReqBufT
_MdsMktDataRequestReqBuf = MdsMktDataRequestReqBufT


class MdsMktDataRequestRspT:
    subMode: int
    tickType: int
    isRequireInitialMktData: int
    __channelNos: int
    tickExpireType: int
    __filler: Sequence[int]
    dataTypes: int
    beginTime: int
    sseStockSubscribed: int
    sseIndexSubscribed: int
    sseOptionSubscribed: int
    szseStockSubscribed: int
    szseIndexSubscribed: int
    szseOptionSubscribed: int
    ...
_MdsMktDataRequestRsp = MdsMktDataRequestRspT


class MdsTestRequestReqT:
    testReqId: str
    sendTime: str
    __filler: str
    ...
_MdsTestRequestReq = MdsTestRequestReqT


class MdsTestRequestRspT:
    testReqId: str
    origSendTime: str
    __filler1: str
    respTime: str
    __filler2: str
    __recvTime: STimeval32T  # unknown what to wrap in py
    __collectedTime: STimeval32T  # unknown what to wrap in py
    __pushingTime: STimeval32T  # unknown what to wrap in py
    ...
_MdsTestRequestRsp = MdsTestRequestRspT


class MdsMktReqMsgBodyT:
    wholeMktDataReqBuf: MdsMktDataRequestReqBufT
    mktDataRequestReq: MdsMktDataRequestReqT
    testRequestReq: MdsTestRequestReqT
    logonReq: MdsLogonReqT
    qryMktDataSnapshotReq: MdsQryMktDataSnapshotReqT
    qrySecurityStatusReq: MdsQryMktDataSnapshotReqT
    qryTrdSessionStatusReq: MdsQryTrdSessionStatusReqT
    ...
_MdsMktReqMsgBody = MdsMktReqMsgBodyT


class MdsMktRspMsgBodyT:
    mktDataRequestRsp: MdsMktDataRequestRspT
    testRequestRsp: MdsTestRequestRspT
    logonRsp: MdsLogonRspT
    mktDataSnapshot: MdsMktDataSnapshotT
    trade: MdsL2TradeT
    order: MdsL2OrderT
    tickLost: MdsL2TickLostT
    trdSessionStatus: MdsTradingSessionStatusMsgT
    securityStatus: MdsSecurityStatusMsgT
    ...
_MdsMktRspMsgBody = MdsMktRspMsgBodyT


class MdsUdpPktHeadT:
    msgCnt: int
    pktSiz: int
    pktSeq: int
    ...
_MdsUdpPktHead = MdsUdpPktHeadT


class MdsApiClientCfgT:
    tcpChannelCfg: SGeneralClientRemoteCfgT
    qryChannelCfg: SGeneralClientRemoteCfgT
    udpL1ChannelCfg: SGeneralClientRemoteCfgT
    udpL2ChannelCfg: SGeneralClientRemoteCfgT
    udpTradeChannelCfg: SGeneralClientRemoteCfgT
    udpOrderChannelCfg: SGeneralClientRemoteCfgT
    subscribeInfo: MdsMktDataRequestReqBufT
    ...
_MdsApiClientCfg = MdsApiClientCfgT


class MdsApiClientEnvT:
    tcpChannel: SGeneralClientChannelT
    qryChannel: SGeneralClientChannelT
    udpL1Channel: SGeneralClientChannelT
    udpL2Channel: SGeneralClientChannelT
    udpTradeChannel: SGeneralClientChannelT
    udpOrderChannel: SGeneralClientChannelT
    udpChannelGroup: SGeneralClientChannelGroupT
    ...
_MdsApiClientEnv = MdsApiClientEnvT


class cast:
    
    def toOesOrdReqT(self, 
            v: Any,
        ) -> OesOrdReqT:
        ...
    
    
    def to_OesOrdReq(self, 
            v: Any,
        ) -> OesOrdReqT:
        ...
    
    
    def to(self, 
            v: Any,
        ) -> :
        ...
    
    
    def toOesOrdCancelReqT(self, 
            v: Any,
        ) -> OesOrdCancelReqT:
        ...
    
    
    def to_OesOrdCancelReq(self, 
            v: Any,
        ) -> OesOrdCancelReqT:
        ...
    
    
    def toOesOrdRejectT(self, 
            v: Any,
        ) -> OesOrdRejectT:
        ...
    
    
    def to_OesOrdReject(self, 
            v: Any,
        ) -> OesOrdRejectT:
        ...
    
    
    def toOesOrdCnfmT(self, 
            v: Any,
        ) -> OesOrdCnfmT:
        ...
    
    
    def toOesOrdItemT(self, 
            v: Any,
        ) -> OesOrdCnfmT:
        ...
    
    
    def to_OesOrdCnfm(self, 
            v: Any,
        ) -> OesOrdCnfmT:
        ...
    
    
    def toOesTrdBaseInfoT(self, 
            v: Any,
        ) -> OesTrdBaseInfoT:
        ...
    
    
    def to_OesTrdBaseInfo(self, 
            v: Any,
        ) -> OesTrdBaseInfoT:
        ...
    
    
    def toOesTrdCnfmT(self, 
            v: Any,
        ) -> OesTrdCnfmT:
        ...
    
    
    def toOesTrdItemT(self, 
            v: Any,
        ) -> OesTrdCnfmT:
        ...
    
    
    def to_OesTrdCnfm(self, 
            v: Any,
        ) -> OesTrdCnfmT:
        ...
    
    
    def toOesLotWinningBaseInfoT(self, 
            v: Any,
        ) -> OesLotWinningBaseInfoT:
        ...
    
    
    def to_OesLotWinningBaseInfo(self, 
            v: Any,
        ) -> OesLotWinningBaseInfoT:
        ...
    
    
    def toOesLotWinningItemT(self, 
            v: Any,
        ) -> OesLotWinningBaseInfoT:
        ...
    
    
    def toOesFundTrsfBaseInfoT(self, 
            v: Any,
        ) -> OesFundTrsfBaseInfoT:
        ...
    
    
    def to_OesFundTrsfBaseInfo(self, 
            v: Any,
        ) -> OesFundTrsfBaseInfoT:
        ...
    
    
    def toOesFundTrsfReqT(self, 
            v: Any,
        ) -> OesFundTrsfReqT:
        ...
    
    
    def to_OesFundTrsfReq(self, 
            v: Any,
        ) -> OesFundTrsfReqT:
        ...
    
    
    def toOesFundTrsfRejectT(self, 
            v: Any,
        ) -> OesFundTrsfRejectT:
        ...
    
    
    def to_OesFundTrsfReject(self, 
            v: Any,
        ) -> OesFundTrsfRejectT:
        ...
    
    
    def toOesFundTrsfReportT(self, 
            v: Any,
        ) -> OesFundTrsfReportT:
        ...
    
    
    def to_OesFundTrsfReport(self, 
            v: Any,
        ) -> OesFundTrsfReportT:
        ...
    
    
    def toOesFundTransferSerialItemT(self, 
            v: Any,
        ) -> OesFundTrsfReportT:
        ...
    
    
    def toOesIssueBaseInfoT(self, 
            v: Any,
        ) -> OesIssueBaseInfoT:
        ...
    
    
    def to_OesIssueBaseInfo(self, 
            v: Any,
        ) -> OesIssueBaseInfoT:
        ...
    
    
    def toOesIssueItemT(self, 
            v: Any,
        ) -> OesIssueBaseInfoT:
        ...
    
    
    def toOesPriceLimitT(self, 
            v: Any,
        ) -> OesPriceLimitT:
        ...
    
    
    def to_OesPriceLimit(self, 
            v: Any,
        ) -> OesPriceLimitT:
        ...
    
    
    def toOesStockBaseInfoT(self, 
            v: Any,
        ) -> OesStockBaseInfoT:
        ...
    
    
    def toOesStockItemT(self, 
            v: Any,
        ) -> OesStockBaseInfoT:
        ...
    
    
    def to_OesStockBaseInfo(self, 
            v: Any,
        ) -> OesStockBaseInfoT:
        ...
    
    
    def toOesEtfBaseInfoT(self, 
            v: Any,
        ) -> OesEtfBaseInfoT:
        ...
    
    
    def to_OesEtfBaseInfo(self, 
            v: Any,
        ) -> OesEtfBaseInfoT:
        ...
    
    
    def toOesEtfItemT(self, 
            v: Any,
        ) -> OesEtfBaseInfoT:
        ...
    
    
    def toOesEtfComponentBaseInfoT(self, 
            v: Any,
        ) -> OesEtfComponentBaseInfoT:
        ...
    
    
    def to_OesEtfComponentBaseInfo(self, 
            v: Any,
        ) -> OesEtfComponentBaseInfoT:
        ...
    
    
    def toOesOptionBaseInfoT(self, 
            v: Any,
        ) -> OesOptionBaseInfoT:
        ...
    
    
    def to_OesOptionBaseInfo(self, 
            v: Any,
        ) -> OesOptionBaseInfoT:
        ...
    
    
    def toOesOptionItemT(self, 
            v: Any,
        ) -> OesOptionBaseInfoT:
        ...
    
    
    def toOesCashAssetBaseInfoT(self, 
            v: Any,
        ) -> OesCashAssetBaseInfoT:
        ...
    
    
    def to_OesCashAssetBaseInfo(self, 
            v: Any,
        ) -> OesCashAssetBaseInfoT:
        ...
    
    
    def toOesCustBaseInfoT(self, 
            v: Any,
        ) -> OesCustBaseInfoT:
        ...
    
    
    def toOesCustItemT(self, 
            v: Any,
        ) -> OesCustBaseInfoT:
        ...
    
    
    def to_OesCustBaseInfo(self, 
            v: Any,
        ) -> OesCustBaseInfoT:
        ...
    
    
    def toOesInvAcctBaseInfoT(self, 
            v: Any,
        ) -> OesInvAcctBaseInfoT:
        ...
    
    
    def to_OesInvAcctBaseInfo(self, 
            v: Any,
        ) -> OesInvAcctBaseInfoT:
        ...
    
    
    def toOesStkHoldingBaseInfoT(self, 
            v: Any,
        ) -> OesStkHoldingBaseInfoT:
        ...
    
    
    def to_OesStkHoldingBaseInfo(self, 
            v: Any,
        ) -> OesStkHoldingBaseInfoT:
        ...
    
    
    def toOesOptHoldingBaseInfoT(self, 
            v: Any,
        ) -> OesOptHoldingBaseInfoT:
        ...
    
    
    def to_OesOptHoldingBaseInfo(self, 
            v: Any,
        ) -> OesOptHoldingBaseInfoT:
        ...
    
    
    def toOesMarketStateInfoT(self, 
            v: Any,
        ) -> OesMarketStateInfoT:
        ...
    
    
    def toOesMarketStateItemT(self, 
            v: Any,
        ) -> OesMarketStateInfoT:
        ...
    
    
    def to_OesMarketStateInfo(self, 
            v: Any,
        ) -> OesMarketStateInfoT:
        ...
    
    
    def toOesTradingPermissionEntryT(self, 
            v: Any,
        ) -> OesTradingPermissionEntryT:
        ...
    
    
    def to_OesTradingPermissionEntry(self, 
            v: Any,
        ) -> OesTradingPermissionEntryT:
        ...
    
    
    def toOesInputSourceInfoT(self, 
            v: Any,
        ) -> OesInputSourceInfoT:
        ...
    
    
    def to_OesInputSourceInfo(self, 
            v: Any,
        ) -> OesInputSourceInfoT:
        ...
    
    
    def toSMsgHeadT(self, 
            v: Any,
        ) -> SMsgHeadT:
        ...
    
    
    def to_SMsgHead(self, 
            v: Any,
        ) -> SMsgHeadT:
        ...
    
    
    def toOesQryCursorT(self, 
            v: Any,
        ) -> OesQryCursorT:
        ...
    
    
    def to_OesQryCursor(self, 
            v: Any,
        ) -> OesQryCursorT:
        ...
    
    
    def toOesQryReqHeadT(self, 
            v: Any,
        ) -> OesQryReqHeadT:
        ...
    
    
    def to_OesQryReqHead(self, 
            v: Any,
        ) -> OesQryReqHeadT:
        ...
    
    
    def toOesQryRspHeadT(self, 
            v: Any,
        ) -> OesQryRspHeadT:
        ...
    
    
    def to_OesQryRspHead(self, 
            v: Any,
        ) -> OesQryRspHeadT:
        ...
    
    
    def toOesQryOrdFilterT(self, 
            v: Any,
        ) -> OesQryOrdFilterT:
        ...
    
    
    def to_OesQryOrdFilter(self, 
            v: Any,
        ) -> OesQryOrdFilterT:
        ...
    
    
    def toOesQryOrdReqT(self, 
            v: Any,
        ) -> OesQryOrdReqT:
        ...
    
    
    def to_OesQryOrdReq(self, 
            v: Any,
        ) -> OesQryOrdReqT:
        ...
    
    
    def toOesQryOrdRspT(self, 
            v: Any,
        ) -> OesQryOrdRspT:
        ...
    
    
    def to_OesQryOrdRsp(self, 
            v: Any,
        ) -> OesQryOrdRspT:
        ...
    
    
    def toOesQryTrdFilterT(self, 
            v: Any,
        ) -> OesQryTrdFilterT:
        ...
    
    
    def to_OesQryTrdFilter(self, 
            v: Any,
        ) -> OesQryTrdFilterT:
        ...
    
    
    def toOesQryTrdReqT(self, 
            v: Any,
        ) -> OesQryTrdReqT:
        ...
    
    
    def to_OesQryTrdReq(self, 
            v: Any,
        ) -> OesQryTrdReqT:
        ...
    
    
    def toOesQryTrdRspT(self, 
            v: Any,
        ) -> OesQryTrdRspT:
        ...
    
    
    def to_OesQryTrdRsp(self, 
            v: Any,
        ) -> OesQryTrdRspT:
        ...
    
    
    def toOesQryCashAssetFilterT(self, 
            v: Any,
        ) -> OesQryCashAssetFilterT:
        ...
    
    
    def to_OesQryCashAssetFilter(self, 
            v: Any,
        ) -> OesQryCashAssetFilterT:
        ...
    
    
    def toOesCashAssetItemT(self, 
            v: Any,
        ) -> OesCashAssetItemT:
        ...
    
    
    def to_OesCashAssetItem(self, 
            v: Any,
        ) -> OesCashAssetItemT:
        ...
    
    
    def toOesQryCashAssetReqT(self, 
            v: Any,
        ) -> OesQryCashAssetReqT:
        ...
    
    
    def to_OesQryCashAssetReq(self, 
            v: Any,
        ) -> OesQryCashAssetReqT:
        ...
    
    
    def toOesQryCashAssetRspT(self, 
            v: Any,
        ) -> OesQryCashAssetRspT:
        ...
    
    
    def to_OesQryCashAssetRsp(self, 
            v: Any,
        ) -> OesQryCashAssetRspT:
        ...
    
    
    def toOesCounterCashItemT(self, 
            v: Any,
        ) -> OesCounterCashItemT:
        ...
    
    
    def to_OesCounterCashItem(self, 
            v: Any,
        ) -> OesCounterCashItemT:
        ...
    
    
    def toOesQryCounterCashReqT(self, 
            v: Any,
        ) -> OesQryCounterCashReqT:
        ...
    
    
    def to_OesQryCounterCashReq(self, 
            v: Any,
        ) -> OesQryCounterCashReqT:
        ...
    
    
    def toOesQryCounterCashRspT(self, 
            v: Any,
        ) -> OesQryCounterCashRspT:
        ...
    
    
    def to_OesQryCounterCashRsp(self, 
            v: Any,
        ) -> OesQryCounterCashRspT:
        ...
    
    
    def toOesQryStkHoldingFilterT(self, 
            v: Any,
        ) -> OesQryStkHoldingFilterT:
        ...
    
    
    def toOesQryOptHoldingFilterT(self, 
            v: Any,
        ) -> OesQryStkHoldingFilterT:
        ...
    
    
    def to_OesQryStkHoldingFilter(self, 
            v: Any,
        ) -> OesQryStkHoldingFilterT:
        ...
    
    
    def toOesStkHoldingItemT(self, 
            v: Any,
        ) -> OesStkHoldingItemT:
        ...
    
    
    def to_OesStkHoldingItem(self, 
            v: Any,
        ) -> OesStkHoldingItemT:
        ...
    
    
    def toOesQryStkHoldingReqT(self, 
            v: Any,
        ) -> OesQryStkHoldingReqT:
        ...
    
    
    def to_OesQryStkHoldingReq(self, 
            v: Any,
        ) -> OesQryStkHoldingReqT:
        ...
    
    
    def toOesQryStkHoldingRspT(self, 
            v: Any,
        ) -> OesQryStkHoldingRspT:
        ...
    
    
    def to_OesQryStkHoldingRsp(self, 
            v: Any,
        ) -> OesQryStkHoldingRspT:
        ...
    
    
    def toOesOptHoldingItemT(self, 
            v: Any,
        ) -> OesOptHoldingItemT:
        ...
    
    
    def to_OesOptHoldingItem(self, 
            v: Any,
        ) -> OesOptHoldingItemT:
        ...
    
    
    def toOesQryOptHoldingReqT(self, 
            v: Any,
        ) -> OesQryOptHoldingReqT:
        ...
    
    
    def to_OesQryOptHoldingReq(self, 
            v: Any,
        ) -> OesQryOptHoldingReqT:
        ...
    
    
    def toOesQryOptHoldingRspT(self, 
            v: Any,
        ) -> OesQryOptHoldingRspT:
        ...
    
    
    def to_OesQryHoldRsp(self, 
            v: Any,
        ) -> OesQryOptHoldingRspT:
        ...
    
    
    def toOesQryCustFilterT(self, 
            v: Any,
        ) -> OesQryCustFilterT:
        ...
    
    
    def to_OesQryCustFilter(self, 
            v: Any,
        ) -> OesQryCustFilterT:
        ...
    
    
    def toOesQryCustReqT(self, 
            v: Any,
        ) -> OesQryCustReqT:
        ...
    
    
    def to_OesQryCustReq(self, 
            v: Any,
        ) -> OesQryCustReqT:
        ...
    
    
    def toOesQryCustRspT(self, 
            v: Any,
        ) -> OesQryCustRspT:
        ...
    
    
    def to_OesQryCustRsp(self, 
            v: Any,
        ) -> OesQryCustRspT:
        ...
    
    
    def toOesQryInvAcctFilterT(self, 
            v: Any,
        ) -> OesQryInvAcctFilterT:
        ...
    
    
    def to_OesQryInvAcctFilter(self, 
            v: Any,
        ) -> OesQryInvAcctFilterT:
        ...
    
    
    def toOesInvAcctItemT(self, 
            v: Any,
        ) -> OesInvAcctItemT:
        ...
    
    
    def to_OesInvAcctItem(self, 
            v: Any,
        ) -> OesInvAcctItemT:
        ...
    
    
    def toOesQryInvAcctReqT(self, 
            v: Any,
        ) -> OesQryInvAcctReqT:
        ...
    
    
    def to_OesQryInvAcctReq(self, 
            v: Any,
        ) -> OesQryInvAcctReqT:
        ...
    
    
    def toOesQryInvAcctRspT(self, 
            v: Any,
        ) -> OesQryInvAcctRspT:
        ...
    
    
    def to_OesQryInvAcctRsp(self, 
            v: Any,
        ) -> OesQryInvAcctRspT:
        ...
    
    
    def toOesInvAcctOverviewT(self, 
            v: Any,
        ) -> OesInvAcctOverviewT:
        ...
    
    
    def to_OesInvAcctOverview(self, 
            v: Any,
        ) -> OesInvAcctOverviewT:
        ...
    
    
    def toOesCashAcctOverviewT(self, 
            v: Any,
        ) -> OesCashAcctOverviewT:
        ...
    
    
    def to_OesCashAcctOverview(self, 
            v: Any,
        ) -> OesCashAcctOverviewT:
        ...
    
    
    def toOesCustOverviewT(self, 
            v: Any,
        ) -> OesCustOverviewT:
        ...
    
    
    def to_OesCustOverview(self, 
            v: Any,
        ) -> OesCustOverviewT:
        ...
    
    
    def toOesClientOverviewT(self, 
            v: Any,
        ) -> OesClientOverviewT:
        ...
    
    
    def to_OesClientOverview(self, 
            v: Any,
        ) -> OesClientOverviewT:
        ...
    
    
    def toOesQryCommissionRateFilterT(self, 
            v: Any,
        ) -> OesQryCommissionRateFilterT:
        ...
    
    
    def to_OesQryCommissionRateFilter(self, 
            v: Any,
        ) -> OesQryCommissionRateFilterT:
        ...
    
    
    def toOesCommissionRateItemT(self, 
            v: Any,
        ) -> OesCommissionRateItemT:
        ...
    
    
    def to_OesCommissionRateItem(self, 
            v: Any,
        ) -> OesCommissionRateItemT:
        ...
    
    
    def toOesQryCommissionRateReqT(self, 
            v: Any,
        ) -> OesQryCommissionRateReqT:
        ...
    
    
    def to_OesQryCommissionRateReq(self, 
            v: Any,
        ) -> OesQryCommissionRateReqT:
        ...
    
    
    def toOesQryCommissionRateRspT(self, 
            v: Any,
        ) -> OesQryCommissionRateRspT:
        ...
    
    
    def to_OesQryCommissionRateRsp(self, 
            v: Any,
        ) -> OesQryCommissionRateRspT:
        ...
    
    
    def toOesQryFundTransferSerialFilterT(self, 
            v: Any,
        ) -> OesQryFundTransferSerialFilterT:
        ...
    
    
    def to_OesQryFundTransferSerialFilter(self, 
            v: Any,
        ) -> OesQryFundTransferSerialFilterT:
        ...
    
    
    def toOesQryFundTransferSerialReqT(self, 
            v: Any,
        ) -> OesQryFundTransferSerialReqT:
        ...
    
    
    def to_OesQryFundTransferSerialReq(self, 
            v: Any,
        ) -> OesQryFundTransferSerialReqT:
        ...
    
    
    def toOesQryFundTransferSerialRspT(self, 
            v: Any,
        ) -> OesQryFundTransferSerialRspT:
        ...
    
    
    def to_OesQryFundTransferSerialRsp(self, 
            v: Any,
        ) -> OesQryFundTransferSerialRspT:
        ...
    
    
    def toOesQryLotWinningFilterT(self, 
            v: Any,
        ) -> OesQryLotWinningFilterT:
        ...
    
    
    def to_OesQryLotWinningFilter(self, 
            v: Any,
        ) -> OesQryLotWinningFilterT:
        ...
    
    
    def toOesQryLotWinningReqT(self, 
            v: Any,
        ) -> OesQryLotWinningReqT:
        ...
    
    
    def to_OesQryLotWinningReq(self, 
            v: Any,
        ) -> OesQryLotWinningReqT:
        ...
    
    
    def toOesQryLotWinningRspT(self, 
            v: Any,
        ) -> OesQryLotWinningRspT:
        ...
    
    
    def to_OesQryLotWinningRsp(self, 
            v: Any,
        ) -> OesQryLotWinningRspT:
        ...
    
    
    def toOesQryIssueFilterT(self, 
            v: Any,
        ) -> OesQryIssueFilterT:
        ...
    
    
    def to_OesQryIssueFilter(self, 
            v: Any,
        ) -> OesQryIssueFilterT:
        ...
    
    
    def toOesQryIssueReqT(self, 
            v: Any,
        ) -> OesQryIssueReqT:
        ...
    
    
    def to_OesQryIssueReq(self, 
            v: Any,
        ) -> OesQryIssueReqT:
        ...
    
    
    def toOesQryIssueRspT(self, 
            v: Any,
        ) -> OesQryIssueRspT:
        ...
    
    
    def to_OesQryIssueRsp(self, 
            v: Any,
        ) -> OesQryIssueRspT:
        ...
    
    
    def toOesQryStockFilterT(self, 
            v: Any,
        ) -> OesQryStockFilterT:
        ...
    
    
    def to_OesQryStockFilter(self, 
            v: Any,
        ) -> OesQryStockFilterT:
        ...
    
    
    def toOesQryStockReqT(self, 
            v: Any,
        ) -> OesQryStockReqT:
        ...
    
    
    def to_OesQryStockReq(self, 
            v: Any,
        ) -> OesQryStockReqT:
        ...
    
    
    def toOesQryStockRspT(self, 
            v: Any,
        ) -> OesQryStockRspT:
        ...
    
    
    def to_OesQryStockRsp(self, 
            v: Any,
        ) -> OesQryStockRspT:
        ...
    
    
    def toOesQryEtfFilterT(self, 
            v: Any,
        ) -> OesQryEtfFilterT:
        ...
    
    
    def to_OesQryEtfFilter(self, 
            v: Any,
        ) -> OesQryEtfFilterT:
        ...
    
    
    def toOesQryEtfReqT(self, 
            v: Any,
        ) -> OesQryEtfReqT:
        ...
    
    
    def to_OesQryEtfReq(self, 
            v: Any,
        ) -> OesQryEtfReqT:
        ...
    
    
    def toOesQryEtfRspT(self, 
            v: Any,
        ) -> OesQryEtfRspT:
        ...
    
    
    def to_OesQryEtfRsp(self, 
            v: Any,
        ) -> OesQryEtfRspT:
        ...
    
    
    def toOesQryEtfComponentFilterT(self, 
            v: Any,
        ) -> OesQryEtfComponentFilterT:
        ...
    
    
    def to_OesQryEtfComponentFilter(self, 
            v: Any,
        ) -> OesQryEtfComponentFilterT:
        ...
    
    
    def toOesEtfComponentItemT(self, 
            v: Any,
        ) -> OesEtfComponentItemT:
        ...
    
    
    def to_OesEtfComponentItem(self, 
            v: Any,
        ) -> OesEtfComponentItemT:
        ...
    
    
    def toOesQryEtfComponentReqT(self, 
            v: Any,
        ) -> OesQryEtfComponentReqT:
        ...
    
    
    def to_OesQryEtfComponentReq(self, 
            v: Any,
        ) -> OesQryEtfComponentReqT:
        ...
    
    
    def toOesQryEtfComponentRspT(self, 
            v: Any,
        ) -> OesQryEtfComponentRspT:
        ...
    
    
    def to_OesQryEtfComponentRsp(self, 
            v: Any,
        ) -> OesQryEtfComponentRspT:
        ...
    
    
    def toOesQryOptionFilterT(self, 
            v: Any,
        ) -> OesQryOptionFilterT:
        ...
    
    
    def to_OesQryOptionFilter(self, 
            v: Any,
        ) -> OesQryOptionFilterT:
        ...
    
    
    def toOesQryOptionReqT(self, 
            v: Any,
        ) -> OesQryOptionReqT:
        ...
    
    
    def to_OesQryOptionReq(self, 
            v: Any,
        ) -> OesQryOptionReqT:
        ...
    
    
    def toOesQryOptionRspT(self, 
            v: Any,
        ) -> OesQryOptionRspT:
        ...
    
    
    def to_OesQryOptionRsp(self, 
            v: Any,
        ) -> OesQryOptionRspT:
        ...
    
    
    def toOesQryTradingDayRspT(self, 
            v: Any,
        ) -> OesQryTradingDayRspT:
        ...
    
    
    def to_OesQryTradingDayRsp(self, 
            v: Any,
        ) -> OesQryTradingDayRspT:
        ...
    
    
    def toOesQryMarketStateFilterT(self, 
            v: Any,
        ) -> OesQryMarketStateFilterT:
        ...
    
    
    def to_OesQryMarketStateFilter(self, 
            v: Any,
        ) -> OesQryMarketStateFilterT:
        ...
    
    
    def toOesQryMarketStateReqT(self, 
            v: Any,
        ) -> OesQryMarketStateReqT:
        ...
    
    
    def to_OesQryMarketStateReq(self, 
            v: Any,
        ) -> OesQryMarketStateReqT:
        ...
    
    
    def toOesQryMarketStateRspT(self, 
            v: Any,
        ) -> OesQryMarketStateRspT:
        ...
    
    
    def to_OesQryMarketStateRsp(self, 
            v: Any,
        ) -> OesQryMarketStateRspT:
        ...
    
    
    def toOesQryReqMsgT(self, 
            v: Any,
        ) -> OesQryReqMsgT:
        ...
    
    
    def to_OesQryReqMsg(self, 
            v: Any,
        ) -> OesQryReqMsgT:
        ...
    
    
    def toOesQryRspMsgT(self, 
            v: Any,
        ) -> OesQryRspMsgT:
        ...
    
    
    def to_OesQryRspMsg(self, 
            v: Any,
        ) -> OesQryRspMsgT:
        ...
    
    
    def toOesLogonReqT(self, 
            v: Any,
        ) -> OesLogonReqT:
        ...
    
    
    def to_OesLogonReq(self, 
            v: Any,
        ) -> OesLogonReqT:
        ...
    
    
    def toOesLogonRspT(self, 
            v: Any,
        ) -> OesLogonRspT:
        ...
    
    
    def to_OesLogonRsp(self, 
            v: Any,
        ) -> OesLogonRspT:
        ...
    
    
    def toOesReportSynchronizationReqT(self, 
            v: Any,
        ) -> OesReportSynchronizationReqT:
        ...
    
    
    def to_OesReportSynchronizationReq(self, 
            v: Any,
        ) -> OesReportSynchronizationReqT:
        ...
    
    
    def toOesReportSynchronizationRspT(self, 
            v: Any,
        ) -> OesReportSynchronizationRspT:
        ...
    
    
    def to_OesReportSynchronizationRsp(self, 
            v: Any,
        ) -> OesReportSynchronizationRspT:
        ...
    
    
    def toOesTestRequestReqT(self, 
            v: Any,
        ) -> OesTestRequestReqT:
        ...
    
    
    def to_OesTestRequestReq(self, 
            v: Any,
        ) -> OesTestRequestReqT:
        ...
    
    
    def toOesTestRequestRspT(self, 
            v: Any,
        ) -> OesTestRequestRspT:
        ...
    
    
    def to_OesTestRequestRsp(self, 
            v: Any,
        ) -> OesTestRequestRspT:
        ...
    
    
    def toOesChangePasswordReqT(self, 
            v: Any,
        ) -> OesChangePasswordReqT:
        ...
    
    
    def to_OesChangePasswordReq(self, 
            v: Any,
        ) -> OesChangePasswordReqT:
        ...
    
    
    def toOesChangePasswordRspT(self, 
            v: Any,
        ) -> OesChangePasswordRspT:
        ...
    
    
    def to_OesChangePasswordRsp(self, 
            v: Any,
        ) -> OesChangePasswordRspT:
        ...
    
    
    def toOesBatchOrdersHeadT(self, 
            v: Any,
        ) -> OesBatchOrdersHeadT:
        ...
    
    
    def to_OesBatchOrdersHead(self, 
            v: Any,
        ) -> OesBatchOrdersHeadT:
        ...
    
    
    def toOesBatchOrdersReqT(self, 
            v: Any,
        ) -> OesBatchOrdersReqT:
        ...
    
    
    def to_OesBatchOrdersReq(self, 
            v: Any,
        ) -> OesBatchOrdersReqT:
        ...
    
    
    def toOesRptMsgHeadT(self, 
            v: Any,
        ) -> OesRptMsgHeadT:
        ...
    
    
    def to_OesRptMsgHead(self, 
            v: Any,
        ) -> OesRptMsgHeadT:
        ...
    
    
    def toOesRptMsgBodyT(self, 
            v: Any,
        ) -> OesRptMsgBodyT:
        ...
    
    
    def to_OesRptMsgBody(self, 
            v: Any,
        ) -> OesRptMsgBodyT:
        ...
    
    
    def toOesRptMsgT(self, 
            v: Any,
        ) -> OesRptMsgT:
        ...
    
    
    def to_OesRptMsg(self, 
            v: Any,
        ) -> OesRptMsgT:
        ...
    
    
    def toOesReqMsgBodyT(self, 
            v: Any,
        ) -> OesReqMsgBodyT:
        ...
    
    
    def to_OesReqMsgBody(self, 
            v: Any,
        ) -> OesReqMsgBodyT:
        ...
    
    
    def toOesRspMsgBodyT(self, 
            v: Any,
        ) -> OesRspMsgBodyT:
        ...
    
    
    def to_OesRspMsgBody(self, 
            v: Any,
        ) -> OesRspMsgBodyT:
        ...
    
    
    def toSErrMsgT(self, 
            v: Any,
        ) -> SErrMsgT:
        ...
    
    
    def to_SErrMsg(self, 
            v: Any,
        ) -> SErrMsgT:
        ...
    
    
    def toSDataBufferT(self, 
            v: Any,
        ) -> SDataBufferT:
        ...
    
    
    def to_SDataBuffer(self, 
            v: Any,
        ) -> SDataBufferT:
        ...
    
    
    def to_SDataBufferVar(self, 
            v: Any,
        ) -> _SDataBufferVar:
        ...
    
    
    def toSSocketUriInfoT(self, 
            v: Any,
        ) -> SSocketUriInfoT:
        ...
    
    
    def to_SSocketUriInfo(self, 
            v: Any,
        ) -> SSocketUriInfoT:
        ...
    
    
    def toSSocketIpPortInfoT(self, 
            v: Any,
        ) -> SSocketIpPortInfoT:
        ...
    
    
    def to_SSocketIpPortInfo(self, 
            v: Any,
        ) -> SSocketIpPortInfoT:
        ...
    
    
    def toSSocketChannelInfoT(self, 
            v: Any,
        ) -> SSocketChannelInfoT:
        ...
    
    
    def to_SSocketChannelInfo(self, 
            v: Any,
        ) -> SSocketChannelInfoT:
        ...
    
    
    def toSSocketOptionConfigT(self, 
            v: Any,
        ) -> SSocketOptionConfigT:
        ...
    
    
    def to_SSocketOptionConfig(self, 
            v: Any,
        ) -> SSocketOptionConfigT:
        ...
    
    
    def toSGeneralClientChannelT(self, 
            v: Any,
        ) -> SGeneralClientChannelT:
        ...
    
    
    def toMdsApiSessionInfoT(self, 
            v: Any,
        ) -> SGeneralClientChannelT:
        ...
    
    
    def to_SGeneralClientChannel(self, 
            v: Any,
        ) -> SGeneralClientChannelT:
        ...
    
    
    def toOesApiSessionInfoT(self, 
            v: Any,
        ) -> SGeneralClientChannelT:
        ...
    
    
    def toSGeneralClientChannelGroupT(self, 
            v: Any,
        ) -> SGeneralClientChannelGroupT:
        ...
    
    
    def to_SGeneralClientChannelGroup(self, 
            v: Any,
        ) -> SGeneralClientChannelGroupT:
        ...
    
    
    def toOesApiChannelGroupT(self, 
            v: Any,
        ) -> SGeneralClientChannelGroupT:
        ...
    
    
    def toMdsApiChannelGroupT(self, 
            v: Any,
        ) -> SGeneralClientChannelGroupT:
        ...
    
    
    def toSGeneralClientAddrInfoT(self, 
            v: Any,
        ) -> SGeneralClientAddrInfoT:
        ...
    
    
    def toMdsApiAddrInfoT(self, 
            v: Any,
        ) -> SGeneralClientAddrInfoT:
        ...
    
    
    def toOesApiAddrInfoT(self, 
            v: Any,
        ) -> SGeneralClientAddrInfoT:
        ...
    
    
    def to_SGeneralClientAddrInfo(self, 
            v: Any,
        ) -> SGeneralClientAddrInfoT:
        ...
    
    
    def toSGeneralClientRemoteCfgT(self, 
            v: Any,
        ) -> SGeneralClientRemoteCfgT:
        ...
    
    
    def to_SGeneralClientRemoteCfg(self, 
            v: Any,
        ) -> SGeneralClientRemoteCfgT:
        ...
    
    
    def toMdsApiRemoteCfgT(self, 
            v: Any,
        ) -> SGeneralClientRemoteCfgT:
        ...
    
    
    def toOesApiRemoteCfgT(self, 
            v: Any,
        ) -> SGeneralClientRemoteCfgT:
        ...
    
    
    def toOesApiSubscribeInfoT(self, 
            v: Any,
        ) -> OesApiSubscribeInfoT:
        ...
    
    
    def to_OesApiSubscribeInfo(self, 
            v: Any,
        ) -> OesApiSubscribeInfoT:
        ...
    
    
    def toOesApiClientCfgT(self, 
            v: Any,
        ) -> OesApiClientCfgT:
        ...
    
    
    def to_OesApiClientCfg(self, 
            v: Any,
        ) -> OesApiClientCfgT:
        ...
    
    
    def toOesApiClientEnvT(self, 
            v: Any,
        ) -> OesApiClientEnvT:
        ...
    
    
    def to_OesApiClientEnv(self, 
            v: Any,
        ) -> OesApiClientEnvT:
        ...
    
    
    def toMdsTradingSessionStatusMsgT(self, 
            v: Any,
        ) -> MdsTradingSessionStatusMsgT:
        ...
    
    
    def to_MdsTradingSessionStatusMsg(self, 
            v: Any,
        ) -> MdsTradingSessionStatusMsgT:
        ...
    
    
    def toMdsSecurityStatusMsgT(self, 
            v: Any,
        ) -> MdsSecurityStatusMsgT:
        ...
    
    
    def to_MdsSecurityStatusMsg(self, 
            v: Any,
        ) -> MdsSecurityStatusMsgT:
        ...
    
    
    def toMdsPriceLevelEntryT(self, 
            v: Any,
        ) -> MdsPriceLevelEntryT:
        ...
    
    
    def to_MdsPriceLevelEntry(self, 
            v: Any,
        ) -> MdsPriceLevelEntryT:
        ...
    
    
    def toMdsMktDataSnapshotHeadT(self, 
            v: Any,
        ) -> MdsMktDataSnapshotHeadT:
        ...
    
    
    def to_MdsMktDataSnapshotHead(self, 
            v: Any,
        ) -> MdsMktDataSnapshotHeadT:
        ...
    
    
    def toMdsIndexSnapshotBodyT(self, 
            v: Any,
        ) -> MdsIndexSnapshotBodyT:
        ...
    
    
    def to_MdsIndexSnapshotBody(self, 
            v: Any,
        ) -> MdsIndexSnapshotBodyT:
        ...
    
    
    def toMdsStockSnapshotBodyT(self, 
            v: Any,
        ) -> MdsStockSnapshotBodyT:
        ...
    
    
    def to_MdsStockSnapshotBody(self, 
            v: Any,
        ) -> MdsStockSnapshotBodyT:
        ...
    
    
    def toMdsL1SnapshotBodyT(self, 
            v: Any,
        ) -> MdsL1SnapshotBodyT:
        ...
    
    
    def to_MdsL1SnapshotBody(self, 
            v: Any,
        ) -> MdsL1SnapshotBodyT:
        ...
    
    
    def toMdsL2StockSnapshotBodyT(self, 
            v: Any,
        ) -> MdsL2StockSnapshotBodyT:
        ...
    
    
    def to_MdsL2StockSnapshotBody(self, 
            v: Any,
        ) -> MdsL2StockSnapshotBodyT:
        ...
    
    
    def toMdsL2StockSnapshotIncrementalT(self, 
            v: Any,
        ) -> MdsL2StockSnapshotIncrementalT:
        ...
    
    
    def to_MdsL2StockSnapshotIncremental(self, 
            v: Any,
        ) -> MdsL2StockSnapshotIncrementalT:
        ...
    
    
    def toMdsL2BestOrdersSnapshotBodyT(self, 
            v: Any,
        ) -> MdsL2BestOrdersSnapshotBodyT:
        ...
    
    
    def to_MdsL2BestOrdersSnapshotBody(self, 
            v: Any,
        ) -> MdsL2BestOrdersSnapshotBodyT:
        ...
    
    
    def toMdsL2BestOrdersSnapshotIncrementalT(self, 
            v: Any,
        ) -> MdsL2BestOrdersSnapshotIncrementalT:
        ...
    
    
    def to_MdsL2BestOrdersSnapshotIncremental(self, 
            v: Any,
        ) -> MdsL2BestOrdersSnapshotIncrementalT:
        ...
    
    
    def toMdsL2VirtualAuctionPriceT(self, 
            v: Any,
        ) -> MdsL2VirtualAuctionPriceT:
        ...
    
    
    def to_MdsL2VirtualAuctionPrice(self, 
            v: Any,
        ) -> MdsL2VirtualAuctionPriceT:
        ...
    
    
    def toMdsL2MarketOverviewT(self, 
            v: Any,
        ) -> MdsL2MarketOverviewT:
        ...
    
    
    def to_MdsL2MarketOverview(self, 
            v: Any,
        ) -> MdsL2MarketOverviewT:
        ...
    
    
    def toMdsL2SnapshotBodyT(self, 
            v: Any,
        ) -> MdsL2SnapshotBodyT:
        ...
    
    
    def to_MdsL2SnapshotBody(self, 
            v: Any,
        ) -> MdsL2SnapshotBodyT:
        ...
    
    
    def toMdsMktDataSnapshotT(self, 
            v: Any,
        ) -> MdsMktDataSnapshotT:
        ...
    
    
    def to_MdsMktDataSnapshot(self, 
            v: Any,
        ) -> MdsMktDataSnapshotT:
        ...
    
    
    def toMdsL2TradeT(self, 
            v: Any,
        ) -> MdsL2TradeT:
        ...
    
    
    def to_MdsL2Trade(self, 
            v: Any,
        ) -> MdsL2TradeT:
        ...
    
    
    def toMdsL2OrderT(self, 
            v: Any,
        ) -> MdsL2OrderT:
        ...
    
    
    def to_MdsL2Order(self, 
            v: Any,
        ) -> MdsL2OrderT:
        ...
    
    
    def toMdsL2TickLostT(self, 
            v: Any,
        ) -> MdsL2TickLostT:
        ...
    
    
    def to_MdsL2TickLost(self, 
            v: Any,
        ) -> MdsL2TickLostT:
        ...
    
    
    def toMdsQryMktDataSnapshotReqT(self, 
            v: Any,
        ) -> MdsQryMktDataSnapshotReqT:
        ...
    
    
    def toMdsQrySecurityStatusReqT(self, 
            v: Any,
        ) -> MdsQryMktDataSnapshotReqT:
        ...
    
    
    def to_MdsQryMktDataSnapshotReq(self, 
            v: Any,
        ) -> MdsQryMktDataSnapshotReqT:
        ...
    
    
    def toMdsQryTrdSessionStatusReqT(self, 
            v: Any,
        ) -> MdsQryTrdSessionStatusReqT:
        ...
    
    
    def to_MdsQryTrdSessionStatusReq(self, 
            v: Any,
        ) -> MdsQryTrdSessionStatusReqT:
        ...
    
    
    def toMdsLogonReqT(self, 
            v: Any,
        ) -> MdsLogonReqT:
        ...
    
    
    def to_MdsLogonReq(self, 
            v: Any,
        ) -> MdsLogonReqT:
        ...
    
    
    def toMdsLogonRspT(self, 
            v: Any,
        ) -> MdsLogonRspT:
        ...
    
    
    def to_MdsLogonRsp(self, 
            v: Any,
        ) -> MdsLogonRspT:
        ...
    
    
    def toMdsMktDataRequestEntryT(self, 
            v: Any,
        ) -> MdsMktDataRequestEntryT:
        ...
    
    
    def to_MdsMktDataRequestEntry(self, 
            v: Any,
        ) -> MdsMktDataRequestEntryT:
        ...
    
    
    def toMdsMktDataRequestReqT(self, 
            v: Any,
        ) -> MdsMktDataRequestReqT:
        ...
    
    
    def to_MdsMktDataRequestReq(self, 
            v: Any,
        ) -> MdsMktDataRequestReqT:
        ...
    
    
    def toMdsMktDataRequestReqBufT(self, 
            v: Any,
        ) -> MdsMktDataRequestReqBufT:
        ...
    
    
    def toMdsApiSubscribeInfoT(self, 
            v: Any,
        ) -> MdsMktDataRequestReqBufT:
        ...
    
    
    def to_MdsMktDataRequestReqBuf(self, 
            v: Any,
        ) -> MdsMktDataRequestReqBufT:
        ...
    
    
    def toMdsMktDataRequestRspT(self, 
            v: Any,
        ) -> MdsMktDataRequestRspT:
        ...
    
    
    def to_MdsMktDataRequestRsp(self, 
            v: Any,
        ) -> MdsMktDataRequestRspT:
        ...
    
    
    def toMdsTestRequestReqT(self, 
            v: Any,
        ) -> MdsTestRequestReqT:
        ...
    
    
    def to_MdsTestRequestReq(self, 
            v: Any,
        ) -> MdsTestRequestReqT:
        ...
    
    
    def toMdsTestRequestRspT(self, 
            v: Any,
        ) -> MdsTestRequestRspT:
        ...
    
    
    def to_MdsTestRequestRsp(self, 
            v: Any,
        ) -> MdsTestRequestRspT:
        ...
    
    
    def toMdsMktReqMsgBodyT(self, 
            v: Any,
        ) -> MdsMktReqMsgBodyT:
        ...
    
    
    def to_MdsMktReqMsgBody(self, 
            v: Any,
        ) -> MdsMktReqMsgBodyT:
        ...
    
    
    def toMdsMktRspMsgBodyT(self, 
            v: Any,
        ) -> MdsMktRspMsgBodyT:
        ...
    
    
    def to_MdsMktRspMsgBody(self, 
            v: Any,
        ) -> MdsMktRspMsgBodyT:
        ...
    
    
    def toMdsUdpPktHeadT(self, 
            v: Any,
        ) -> MdsUdpPktHeadT:
        ...
    
    
    def to_MdsUdpPktHead(self, 
            v: Any,
        ) -> MdsUdpPktHeadT:
        ...
    
    
    def toMdsApiClientCfgT(self, 
            v: Any,
        ) -> MdsApiClientCfgT:
        ...
    
    
    def to_MdsApiClientCfg(self, 
            v: Any,
        ) -> MdsApiClientCfgT:
        ...
    
    
    def toMdsApiClientEnvT(self, 
            v: Any,
        ) -> MdsApiClientEnvT:
        ...
    
    
    def to_MdsApiClientEnv(self, 
            v: Any,
        ) -> MdsApiClientEnvT:
        ...
    
    ...


def SPlatform_GetErrno(
    )->int:
    ...

def SPlatform_GetNegErrno(
    )->int:
    ...

def SPlatform_SetErrno(
        err: int,
    )->Any:
    ...

def SPlatform_IsErrEagain(
        err: int,
    )->int:
    ...

def SPlatform_IsErrEconnaborted(
        err: int,
    )->int:
    ...

def SPlatform_IsErrEtimeout(
        err: int,
    )->int:
    ...

def SPlatform_IsErrEpipe(
        err: int,
    )->int:
    ...

def SPlatform_IsErrEintr(
        err: int,
    )->int:
    ...

def SPlatform_IsErrEbadmsg(
        err: int,
    )->int:
    ...

def SPlatform_IsNegEagain(
        err: int,
    )->int:
    ...

def SPlatform_IsNegEconnaborted(
        err: int,
    )->int:
    ...

def SPlatform_IsNegEtimeout(
        err: int,
    )->int:
    ...

def SPlatform_IsNegEpipe(
        err: int,
    )->int:
    ...

def SPlatform_IsNegEintr(
        err: int,
    )->int:
    ...

def SPlatform_IsNegEbadmsg(
        err: int,
    )->int:
    ...

def OesApi_SendOrderReq(
        pOrdChannel: SGeneralClientChannelT,
        pOrdReq: OesOrdReqT,
    )->int:
    ...

def OesApi_SendOrderCancelReq(
        pOrdChannel: SGeneralClientChannelT,
        pCancelReq: OesOrdCancelReqT,
    )->int:
    ...

def OesApi_SendBatchOrdersReq2(
        pOrdChannel: SGeneralClientChannelT,
        pOrdReqArray: OesOrdReqT,
        ordCount: int,
    )->int:
    ...

def OesApi_SendFundTransferReq(
        pOrdChannel: SGeneralClientChannelT,
        pFundTrsfReq: OesFundTrsfReqT,
    )->int:
    ...

def OesApi_SendChangePasswordReq(
        pOrdChannel: SGeneralClientChannelT,
        pChangePasswordReq: OesChangePasswordReqT,
        pOutChangePasswordRsp: OesChangePasswordRspT,
    )->int:
    ...

def OesApi_WaitReportMsg(
        pRptChannel: SGeneralClientChannelT,
        timeoutMs: int,
        pRptMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,Any], int],
    )->int:
    ...

def OesApi_GetApiVersion(
    )->str:
    ...

def OesApi_GetTradingDay(
        pQryChannel: SGeneralClientChannelT,
    )->int:
    ...

def OesApi_GetClientOverview(
        pQryChannel: SGeneralClientChannelT,
        pClientOverview: OesClientOverviewT,
    )->int:
    ...

def OesApi_QuerySingleOrder(
        pQryChannel: SGeneralClientChannelT,
        clSeqNo: int,
        pOrdItem: OesOrdCnfmT,
    )->int:
    ...

def OesApi_QuerySingleCashAsset(
        pQryChannel: SGeneralClientChannelT,
        pCashAcctId: str,
        pCashAssetItem: OesCashAssetItemT,
    )->int:
    ...

def OesApi_QuerySingleStkHolding(
        pQryChannel: SGeneralClientChannelT,
        pInvAcctId: str,
        pSecurityId: str,
        pHoldingItem: OesStkHoldingItemT,
    )->int:
    ...

def OesApi_QuerySingleOptHolding(
        pQryChannel: SGeneralClientChannelT,
        pInvAcctId: str,
        pSecurityId: str,
        pHoldingItem: OesOptHoldingItemT,
    )->int:
    ...

def OesApi_QueryOrder(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryOrdFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryTrade(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryTrdFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryCashAsset(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryCashAssetFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryStkHolding(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryStkHoldingFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryOptHolding(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryStkHoldingFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryLotWinning(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryLotWinningFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryCustInfo(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryCustFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryInvAcct(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryInvAcctFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryCommissionRate(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryCommissionRateFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryFundTransferSerial(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryFundTransferSerialFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryIssue(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryIssueFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryStock(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryStockFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryEtf(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryEtfFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryEtfComponent(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryEtfComponentFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryOption(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryOptionFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryMarketState(
        pQryChannel: SGeneralClientChannelT,
        pQryFilter: OesQryMarketStateFilterT,
        pQryMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,OesQryCursorT,Any], int],
    )->int:
    ...

def OesApi_QueryCounterCash(
        pQryChannel: SGeneralClientChannelT,
        pCashAcctId: str,
        pCounterCashItem: OesCounterCashItemT,
    )->int:
    ...

def OesApi_Logon(
        pOutSessionInfo: SGeneralClientChannelT,
        channelType: eOesApiChannelTypeT,
        pUri: str,
        pUsername: str,
        pPassword: str,
        clEnvId: int,
        heartBtInt: int,
        pSocketOptions: SSocketOptionConfigT,
    )->int:
    ...

def OesApi_LogonReplicaSet(
        pOutSessionInfo: SGeneralClientChannelT,
        channelType: eOesApiChannelTypeT,
        pUriList: str,
        pUsername: str,
        pPassword: str,
        clEnvId: int,
        heartBtInt: int,
        pSocketOptions: SSocketOptionConfigT,
    )->int:
    ...

def OesApi_LogonPeerNodes(
        pOutSessionInfo: SGeneralClientChannelT,
        channelType: eOesApiChannelTypeT,
        pUriList: str,
        pUsername: str,
        pPassword: str,
        clEnvId: int,
        heartBtInt: int,
        pSocketOptions: SSocketOptionConfigT,
    )->int:
    ...

def OesApi_SendReportSynchronization(
        pRptChannel: SGeneralClientChannelT,
        subscribeEnvId: int,
        subscribeRptTypes: int,
        lastRptSeqNum: int,
    )->int:
    ...

def OesApi_SendHeartbeat(
        pSessionInfo: SGeneralClientChannelT,
    )->int:
    ...

def OesApi_TestOrdChannel(
        pOrdChannel: SGeneralClientChannelT,
        pTestReqId: str,
        testReqIdSize: int,
    )->int:
    ...

def OesApi_TestOrdChannel2(
        pOrdChannel: SGeneralClientChannelT,
        pTestReq: OesTestRequestReqT,
        pOutTestRsp: OesTestRequestRspT,
    )->int:
    ...

def OesApi_TestRptChannel(
        pRptChannel: SGeneralClientChannelT,
        pTestReqId: str,
        testReqIdSize: int,
    )->int:
    ...

def OesApi_TestRptChannel2(
        pRptChannel: SGeneralClientChannelT,
        pTestReq: OesTestRequestReqT,
    )->int:
    ...

def OesApi_Logout(
        pSessionInfo: SGeneralClientChannelT,
        isDestory: int,
    )->int:
    ...

def OesApi_Destory(
        pSessionInfo: SGeneralClientChannelT,
    )->Any:
    ...

def OesApi_InitAll(
        pOutCliEnv: OesApiClientEnvT,
        pCfgFile: str,
        pLoggerSection: str,
        pCfgSection: str,
        pOrdAddrKey: str,
        pRptAddrKey: str,
        pQryAddrKey: str,
        lastRptSeqNum: int,
        pLastClSeqNo: int,
    )->int:
    ...

def OesApi_InitAllByConvention(
        pOutCliEnv: OesApiClientEnvT,
        pCfgFile: str,
        lastRptSeqNum: int,
        pLastClSeqNo: int,
    )->int:
    ...

def OesApi_LogoutAll(
        pCliEnv: OesApiClientEnvT,
        isDestory: int,
    )->Any:
    ...

def OesApi_DestoryAll(
        pCliEnv: OesApiClientEnvT,
    )->Any:
    ...

def OesApi_InitLogger(
        pCfgFile: str,
        pLoggerSection: str,
    )->int:
    ...

def OesApi_ResetThreadLoggerName(
        pLogSystemName: str,
    )->int:
    ...

def OesApi_InitOrdChannel(
        pOrdChannel: SGeneralClientChannelT,
        pCfgFile: str,
        pCfgSection: str,
        pAddrKey: str,
        pLastClSeqNo: int,
    )->int:
    ...

def OesApi_InitOrdChannel2(
        pOrdChannel: SGeneralClientChannelT,
        pRemoteCfg: SGeneralClientRemoteCfgT,
        pLastClSeqNo: int,
    )->int:
    ...

def OesApi_InitRptChannel(
        pRptChannel: SGeneralClientChannelT,
        pCfgFile: str,
        pCfgSection: str,
        pAddrKey: str,
        lastRptSeqNum: int,
    )->int:
    ...

def OesApi_InitRptChannel2(
        pRptChannel: SGeneralClientChannelT,
        pRemoteCfg: SGeneralClientRemoteCfgT,
        pSubscribeInfo: OesApiSubscribeInfoT,
        lastRptSeqNum: int,
    )->int:
    ...

def OesApi_InitQryChannel(
        pQryChannel: SGeneralClientChannelT,
        pCfgFile: str,
        pCfgSection: str,
        pAddrKey: str,
    )->int:
    ...

def OesApi_InitQryChannel2(
        pQryChannel: SGeneralClientChannelT,
        pRemoteCfg: SGeneralClientRemoteCfgT,
    )->int:
    ...

def OesApi_ParseAddrListString(
        pUriList: str,
        pOutAddrList: SGeneralClientAddrInfoT,
        addrListLength: int,
    )->int:
    ...

def OesApi_ParseConfigFromFile(
        pCfgFile: str,
        pSection: str,
        pAddrKey: str,
        pOutRemoteCfg: SGeneralClientRemoteCfgT,
        pOutSubscribeInfo: OesApiSubscribeInfoT,
    )->int:
    ...

def OesApi_ParseAllConfig(
        pCfgFile: str,
        pOutApiCfg: OesApiClientCfgT,
    )->int:
    ...

def OesApi_InitChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
    )->int:
    ...

def OesApi_DestoryChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
    )->int:
    ...

def OesApi_AddToChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
        pChannel: SGeneralClientChannelT,
    )->int:
    ...

def OesApi_DeleteFromChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
        pTargetChanne: SGeneralClientChannelT,
    )->int:
    ...

def OesApi_GetFromChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
        index: int,
    )->SGeneralClientChannelT:
    ...

def OesApi_GetFromChannelGroupBySocket(
        pChannelGroup: SGeneralClientChannelGroupT,
        socketFd: int,
    )->SGeneralClientChannelT:
    ...

def OesApi_ForeachInChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
        fnCallback: Callable[[SGeneralClientChannelT], int],
    )->int:
    ...

def OesApi_SetThreadUsername(
        pUsername: str,
    )->Any:
    ...

def OesApi_GetThreadUsername(
    )->str:
    ...

def OesApi_SetThreadPassword(
        pPassword: str,
    )->Any:
    ...

def OesApi_SetThreadEnvId(
        clEnvId: int,
    )->Any:
    ...

def OesApi_GetThreadEnvId(
    )->int:
    ...

def OesApi_SetCustomizedIpAndMac(
        pIpStr: str,
        pMacStr: str,
    )->int:
    ...

def OesApi_GetCustomizedIp(
    )->str:
    ...

def OesApi_GetCustomizedMac(
    )->str:
    ...

def OesApi_SetCustomizedDriverId(
        pDriverId: str,
    )->int:
    ...

def OesApi_GetCustomizedDriverId(
    )->str:
    ...

def OesApi_GetClEnvId(
        pChannel: SGeneralClientChannelT,
    )->int:
    ...

def OesApi_GetLastRecvTime(
        pChannel: SGeneralClientChannelT,
    )->int:
    ...

def OesApi_GetLastSendTime(
        pChannel: SGeneralClientChannelT,
    )->int:
    ...

def OesApi_HasMoreCachedData(
        pRptChannel: SGeneralClientChannelT,
    )->int:
    ...

def OesApi_IsValidOrdChannel(
        pOrdChannel: SGeneralClientChannelT,
    )->int:
    ...

def OesApi_IsValidRptChannel(
        pRptChannel: SGeneralClientChannelT,
    )->int:
    ...

def OesApi_IsValidQryChannel(
        pQryChannel: SGeneralClientChannelT,
    )->int:
    ...

def OesApi_IsValidChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
    )->int:
    ...

def OesApi_GetLastError(
    )->int:
    ...

def OesApi_SetLastError(
        errCode: int,
    )->Any:
    ...

def OesApi_GetErrorMsg(
        errCode: int,
    )->str:
    ...

def OesApi_GetErrorMsg2(
        status: int,
        detailStatus: int,
    )->str:
    ...

def MdsApi_Logon(
        pOutSessionInfo: SGeneralClientChannelT,
        channelType: eMdsApiChannelTypeT,
        pUri: str,
        pUsername: str,
        pPassword: str,
        heartBtInt: int,
        pSocketOptions: SSocketOptionConfigT,
    )->int:
    ...

def MdsApi_LogonReplicaSet(
        pOutSessionInfo: SGeneralClientChannelT,
        channelType: eMdsApiChannelTypeT,
        pUriList: str,
        pUsername: str,
        pPassword: str,
        heartBtInt: int,
        pSocketOptions: SSocketOptionConfigT,
    )->int:
    ...

def MdsApi_LogonPeerNodes(
        pOutSessionInfo: SGeneralClientChannelT,
        channelType: eMdsApiChannelTypeT,
        pUriList: str,
        pUsername: str,
        pPassword: str,
        heartBtInt: int,
        pSocketOptions: SSocketOptionConfigT,
    )->int:
    ...

def MdsApi_SyncSubscribeOnLogon(
        pSessionInfo: SGeneralClientChannelT,
        pMktDataRequestReq: MdsMktDataRequestReqT,
        pEntries: MdsMktDataRequestEntryT,
    )->int:
    ...

def MdsApi_SubscribeMarketData(
        pSessionInfo: SGeneralClientChannelT,
        pMktDataRequestReq: MdsMktDataRequestReqT,
        pEntries: MdsMktDataRequestEntryT,
    )->int:
    ...

def MdsApi_SendHeartbeat(
        pSessionInfo: SGeneralClientChannelT,
    )->int:
    ...

def MdsApi_SendTestRequest(
        pSessionInfo: SGeneralClientChannelT,
        pTestReqId: str,
        testReqIdSize: int,
    )->int:
    ...

def MdsApi_Logout(
        pSessionInfo: SGeneralClientChannelT,
        isDestory: int,
    )->int:
    ...

def MdsApi_Destory(
        pSessionInfo: SGeneralClientChannelT,
    )->Any:
    ...

def MdsApi_WaitOnMsg(
        pTcpChannel: SGeneralClientChannelT,
        timeoutMs: int,
        pOnMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,Any], int],
    )->int:
    ...

def MdsApi_WaitOnMsgCompressible(
        pTcpChannel: SGeneralClientChannelT,
        timeoutMs: int,
        pOnMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,Any], int],
    )->int:
    ...

def MdsApi_GetApiVersion(
    )->str:
    ...

def MdsApi_QueryMktDataSnapshot(
        pQryChannel: SGeneralClientChannelT,
        exchangeId: eMdsExchangeIdT,
        securityType: eMdsSecurityTypeT,
        instrId: int,
        pRspBuf: MdsMktDataSnapshotT,
    )->int:
    ...

def MdsApi_QuerySecurityStatus(
        pQryChannel: SGeneralClientChannelT,
        exchangeId: eMdsExchangeIdT,
        securityType: eMdsSecurityTypeT,
        instrId: int,
        pRspBuf: MdsSecurityStatusMsgT,
    )->int:
    ...

def MdsApi_QueryTrdSessionStatus(
        pQryChannel: SGeneralClientChannelT,
        exchangeId: eMdsExchangeIdT,
        securityType: eMdsSecurityTypeT,
        pRspBuf: MdsTradingSessionStatusMsgT,
    )->int:
    ...

def MdsApi_ConnectToUdpMcast(
        pOutSessionInfo: SGeneralClientChannelT,
        pUri: str,
        pSocketOptions: SSocketOptionConfigT,
    )->int:
    ...

def MdsApi_WaitOnUdpMsg(
        pUdpChannel: SGeneralClientChannelT,
        timeoutMs: int,
        pOnMsgCallback: Callable[[SGeneralClientChannelT,SMsgHeadT,Any,Any], int],
    )->int:
    ...

def MdsApi_InitAll(
        pOutCliEnv: MdsApiClientEnvT,
        pCfgFile: str,
        pLoggerSection: str,
        pCfgSection: str,
        pTcpAddrKey: str,
        pQryAddrKey: str,
        pUdpL1AddrKey: str,
        pUdpL2AddrKey: str,
        pUdpTickTradeAddrKey: str,
        pUdpTickOrderAddrKey: str,
    )->int:
    ...

def MdsApi_InitAllByConvention(
        pOutCliEnv: MdsApiClientEnvT,
        pCfgFile: str,
    )->int:
    ...

def MdsApi_LogoutAll(
        pCliEnv: MdsApiClientEnvT,
        isDestory: int,
    )->Any:
    ...

def MdsApi_DestoryAll(
        pCliEnv: MdsApiClientEnvT,
    )->Any:
    ...

def MdsApi_InitLogger(
        pCfgFile: str,
        pLoggerSection: str,
    )->int:
    ...

def MdsApi_ResetThreadLoggerName(
        pLogSystemName: str,
    )->int:
    ...

def MdsApi_InitTcpChannel(
        pTcpChannel: SGeneralClientChannelT,
        pCfgFile: str,
        pCfgSection: str,
        pAddrKey: str,
    )->int:
    ...

def MdsApi_InitTcpChannel2(
        pTcpChannel: SGeneralClientChannelT,
        pRemoteCfg: SGeneralClientRemoteCfgT,
        pSubscribeInfo: MdsMktDataRequestReqBufT,
    )->int:
    ...

def MdsApi_InitQryChannel(
        pQryChannel: SGeneralClientChannelT,
        pCfgFile: str,
        pCfgSection: str,
        pAddrKey: str,
    )->int:
    ...

def MdsApi_InitQryChannel2(
        pQryChannel: SGeneralClientChannelT,
        pRemoteCfg: SGeneralClientRemoteCfgT,
    )->int:
    ...

def MdsApi_InitUdpChannel(
        pUdpChannel: SGeneralClientChannelT,
        pCfgFile: str,
        pCfgSection: str,
        pAddrKey: str,
    )->int:
    ...

def MdsApi_InitUdpChannel2(
        pUdpChannel: SGeneralClientChannelT,
        pRemoteCfg: SGeneralClientRemoteCfgT,
    )->int:
    ...

def MdsApi_ParseAddrListString(
        pUriList: str,
        pOutAddrList: SGeneralClientAddrInfoT,
        addrListLength: int,
    )->int:
    ...

def MdsApi_ParseConfigFromFile(
        pCfgFile: str,
        pSection: str,
        pAddrKey: str,
        pOutRemoteCfg: SGeneralClientRemoteCfgT,
        pOutSubscribeInfo: MdsMktDataRequestReqBufT,
    )->int:
    ...

def MdsApi_ParseAllConfig(
        pCfgFile: str,
        pOutApiCfg: MdsApiClientCfgT,
    )->int:
    ...

def MdsApi_InitChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
    )->int:
    ...

def MdsApi_DestoryChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
    )->int:
    ...

def MdsApi_AddToChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
        pChannel: SGeneralClientChannelT,
    )->int:
    ...

def MdsApi_DeleteFromChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
        pTargetChanne: SGeneralClientChannelT,
    )->int:
    ...

def MdsApi_GetFromChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
        index: int,
    )->SGeneralClientChannelT:
    ...

def MdsApi_GetFromChannelGroupBySocket(
        pChannelGroup: SGeneralClientChannelGroupT,
        socketFd: int,
    )->SGeneralClientChannelT:
    ...

def MdsApi_ForeachInChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
        fnCallback: Callable[[SGeneralClientChannelT], int],
    )->int:
    ...

def MdsApi_SetThreadUsername(
        pUsername: str,
    )->Any:
    ...

def MdsApi_GetThreadUsername(
    )->str:
    ...

def MdsApi_SetThreadPassword(
        pPassword: str,
    )->Any:
    ...

def MdsApi_GetLastRecvTime(
        pSessionInfo: SGeneralClientChannelT,
    )->int:
    ...

def MdsApi_GetLastSendTime(
        pSessionInfo: SGeneralClientChannelT,
    )->int:
    ...

def MdsApi_HasMoreCachedData(
        pTcpChannel: SGeneralClientChannelT,
    )->int:
    ...

def MdsApi_IsValidTcpChannel(
        pTcpChannel: SGeneralClientChannelT,
    )->int:
    ...

def MdsApi_IsValidQryChannel(
        pQryChannel: SGeneralClientChannelT,
    )->int:
    ...

def MdsApi_IsValidUdpChannel(
        pUdpChannel: SGeneralClientChannelT,
    )->int:
    ...

def MdsApi_IsValidChannelGroup(
        pChannelGroup: SGeneralClientChannelGroupT,
    )->int:
    ...

def MdsApi_GetLastError(
    )->int:
    ...

def MdsApi_SetLastError(
        errCode: int,
    )->Any:
    ...

def MdsApi_GetErrorMsg(
        errCode: int,
    )->str:
    ...

def MdsApi_GetErrorMsg2(
        status: int,
        detailStatus: int,
    )->str:
    ...

def MdsHelper_SetTickTypeOnSubscribeByString(
        tickType: eMdsSubscribedTickTypeT,
    )->Any:
    ...

def MdsHelper_ClearSubscribeRequestEntries(
        pSubscribeInfo: MdsMktDataRequestReqBufT,
    )->Any:
    ...

def MdsHelper_SetSubscribeRequestMode(
        pSubscribeInfo: MdsMktDataRequestReqBufT,
        subMode: eMdsSubscribeModeT,
    )->Any:
    ...

def MdsHelper_SetSubscribeRequestTickType(
        pSubscribeInfo: MdsMktDataRequestReqBufT,
        tickType: eMdsSubscribedTickTypeT,
    )->Any:
    ...

def MdsHelper_SetSubscribeRequestDataTypes(
        pSubscribeInfo: MdsMktDataRequestReqBufT,
        dataTypes: int,
    )->Any:
    ...

def MdsHelper_SetSubscribeRequestSubFlag(
        pSubscribeInfo: MdsMktDataRequestReqBufT,
        exchangeId: eMdsExchangeIdT,
        securityType: eMdsSecurityTypeT,
        subFlag: eMdsMktSubscribeFlagT,
    )->Any:
    ...

def MdsHelper_AddSubscribeRequestEntry(
        pSubscribeInfo: MdsMktDataRequestReqBufT,
        exchangeId: eMdsExchangeIdT,
        securityType: eMdsSecurityTypeT,
        securityId: int,
    )->int:
    ...

def MdsJsonParser_EncodeReq(
        pReqHead: SMsgHeadT,
        pReqBody: MdsMktReqMsgBodyT,
        pBuf: str,
        bufSize: int,
        pRemoteInfo: str,
    )->Any:
    ...

def MdsJsonParser_DecodeReq(
        pReqHead: SMsgHeadT,
        pMsgBody: Any,
        pReqMsgBuf: MdsMktReqMsgBodyT,
        pRemoteInfo: str,
    )->MdsMktReqMsgBodyT:
    ...

def MdsJsonParser_EncodeRsp(
        pRspHead: SMsgHeadT,
        pRspBody: MdsMktRspMsgBodyT,
        pBuf: str,
        bufSize: int,
        pRemoteInfo: str,
    )->Any:
    ...

def MdsJsonParser_EncodeRspSimplify(
        pRspHead: SMsgHeadT,
        pRspBody: MdsMktRspMsgBodyT,
        pBuf: str,
        bufSize: int,
        pRemoteInfo: str,
    )->Any:
    ...

def MdsJsonParser_DecodeRsp(
        pRspHead: SMsgHeadT,
        pMsgBody: Any,
        pRspMsgBuf: MdsMktRspMsgBodyT,
        pRemoteInfo: str,
    )->MdsMktRspMsgBodyT:
    ...

OES_APPL_VER_ID: str = """0.15.7.4"""
OES_MIN_APPL_VER_ID: str = """0.15.5"""
OESAPI_CFG_DEFAULT_SECTION: str = """oes_client"""
OESAPI_CFG_DEFAULT_SECTION_LOGGER: str = """log"""
OESAPI_CFG_DEFAULT_KEY_ORD_ADDR: str = """ordServer"""
OESAPI_CFG_DEFAULT_KEY_RPT_ADDR: str = """rptServer"""
OESAPI_CFG_DEFAULT_KEY_QRY_ADDR: str = """qryServer"""
OESAPI_DEFAULT_STRING_DELIM: str = """,;| 	
"""
MDS_APPL_VER_ID: str = """0.15.7.4"""
MDS_MIN_APPL_VER_ID: str = """0.15.5"""
MDSAPI_CFG_DEFAULT_SECTION: str = """mds_client"""
MDSAPI_CFG_DEFAULT_SECTION_LOGGER: str = """log"""
MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR: str = """tcpServer"""
MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR: str = """qryServer"""
MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1: str = """udpServer.L1"""
MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2: str = """udpServer.L2"""
MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE: str = """udpServer.TickTrade"""
MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER: str = """udpServer.TickOrder"""
MDSAPI_DEFAULT_STRING_DELIM: str = """,;| 	
"""


class constants:
    OES_APPL_VER_ID: str = """0.15.7.4"""
    OES_MIN_APPL_VER_ID: str = """0.15.5"""
    OESAPI_CFG_DEFAULT_SECTION: str = """oes_client"""
    OESAPI_CFG_DEFAULT_SECTION_LOGGER: str = """log"""
    OESAPI_CFG_DEFAULT_KEY_ORD_ADDR: str = """ordServer"""
    OESAPI_CFG_DEFAULT_KEY_RPT_ADDR: str = """rptServer"""
    OESAPI_CFG_DEFAULT_KEY_QRY_ADDR: str = """qryServer"""
    OESAPI_DEFAULT_STRING_DELIM: str = """,;| 	
"""
    MDS_APPL_VER_ID: str = """0.15.7.4"""
    MDS_MIN_APPL_VER_ID: str = """0.15.5"""
    MDSAPI_CFG_DEFAULT_SECTION: str = """mds_client"""
    MDSAPI_CFG_DEFAULT_SECTION_LOGGER: str = """log"""
    MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR: str = """tcpServer"""
    MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR: str = """qryServer"""
    MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1: str = """udpServer.L1"""
    MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2: str = """udpServer.L2"""
    MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE: str = """udpServer.TickTrade"""
    MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER: str = """udpServer.TickOrder"""
    MDSAPI_DEFAULT_STRING_DELIM: str = """,;| 	
"""
    ...

class eOesExchangeIdT(Enum):
    OES_EXCH_UNDEFINE: eOesExchangeIdT
    OES_EXCH_SSE: eOesExchangeIdT = 1
    OES_EXCH_SZSE: eOesExchangeIdT = 2
    __MAX_OES_EXCH: eOesExchangeIdT = 3
    OES_EXCHANGE_TYPE_SSE: eOesExchangeIdT = 1
    OES_EXCHANGE_TYPE_SZSE: eOesExchangeIdT = 2
    ...

class eOesMarketIdT(Enum):
    OES_MKT_UNDEFINE: eOesMarketIdT
    OES_MKT_SH_ASHARE: eOesMarketIdT = 1
    OES_MKT_SZ_ASHARE: eOesMarketIdT = 2
    OES_MKT_SH_OPTION: eOesMarketIdT = 3
    __OES_MKT_ID_MAX: eOesMarketIdT = 4
    OES_MKT_ID_UNDEFINE: eOesMarketIdT
    OES_MKT_ID_SH_A: eOesMarketIdT = 1
    OES_MKT_ID_SZ_A: eOesMarketIdT = 2
    OES_MKT_ID_SH_OPT: eOesMarketIdT = 3
    __OES_MKT_ID_MAX_ALIGNED4: eOesMarketIdT = 4
    __OES_MKT_ID_MAX_ALIGNED8: eOesMarketIdT = 8
    ...

class eOesPlatformIdT(Enum):
    OES_PLATFORM_UNDEFINE: eOesPlatformIdT
    OES_PLATFORM_CASH_AUCTION: eOesPlatformIdT = 1
    OES_PLATFORM_FINANCIAL_SERVICES: eOesPlatformIdT = 2
    OES_PLATFORM_NON_TRADE: eOesPlatformIdT = 3
    OES_PLATFORM_DERIVATIVE_AUCTION: eOesPlatformIdT = 4
    __OES_PLATFORM_ID_MAX: eOesPlatformIdT = 5
    __OES_PLATFORM_ACTIVE_MAX: eOesPlatformIdT = 4
    ...

class eOesMarketStatusT(Enum):
    OES_MKT_STATE_UNDEFINE: eOesMarketStatusT
    OES_MKT_STATE_PRE_OPEN: eOesMarketStatusT = 1
    OES_MKT_STATE_OPEN_UP_COMING: eOesMarketStatusT = 2
    OES_MKT_STATE_OPEN: eOesMarketStatusT = 3
    OES_MKT_STATE_HALT: eOesMarketStatusT = 4
    OES_MKT_STATE_CLOSE: eOesMarketStatusT = 5
    __OES_MKT_STATE_MAX: eOesMarketStatusT = 6
    ...

class eOesTrdSessTypeT(Enum):
    OES_TRD_SESS_TYPE_O: eOesTrdSessTypeT
    OES_TRD_SESS_TYPE_T: eOesTrdSessTypeT = 1
    OES_TRD_SESS_TYPE_C: eOesTrdSessTypeT = 2
    __OES_TRD_SESS_TYPE_MAX: eOesTrdSessTypeT = 3
    ...

class eOesSecurityTypeT(Enum):
    OES_SECURITY_TYPE_UNDEFINE: eOesSecurityTypeT
    OES_SECURITY_TYPE_STOCK: eOesSecurityTypeT = 1
    OES_SECURITY_TYPE_BOND: eOesSecurityTypeT = 2
    OES_SECURITY_TYPE_ETF: eOesSecurityTypeT = 3
    OES_SECURITY_TYPE_FUND: eOesSecurityTypeT = 4
    OES_SECURITY_TYPE_OPTION: eOesSecurityTypeT = 5
    __OES_SECURITY_TYPE_MAX: eOesSecurityTypeT = 6
    __OES_SECURITY_TYPE_NOT_SUPPORT: eOesSecurityTypeT = 100
    ...

class eOesSubSecurityTypeT(Enum):
    OES_SUB_SECURITY_TYPE_UNDEFINE: eOesSubSecurityTypeT
    __OES_SUB_SECURITY_TYPE_STOCK_MIN: eOesSubSecurityTypeT = 10
    OES_SUB_SECURITY_TYPE_STOCK_ASH: eOesSubSecurityTypeT = 11
    OES_SUB_SECURITY_TYPE_STOCK_SME: eOesSubSecurityTypeT = 12
    OES_SUB_SECURITY_TYPE_STOCK_GEM: eOesSubSecurityTypeT = 13
    OES_SUB_SECURITY_TYPE_STOCK_CDR: eOesSubSecurityTypeT = 14
    __OES_SUB_SECURITY_TYPE_STOCK_MAX: eOesSubSecurityTypeT = 15
    __OES_SUB_SECURITY_TYPE_BOND_MIN: eOesSubSecurityTypeT = 20
    OES_SUB_SECURITY_TYPE_BOND_GBF: eOesSubSecurityTypeT = 21
    OES_SUB_SECURITY_TYPE_BOND_CBF: eOesSubSecurityTypeT = 22
    OES_SUB_SECURITY_TYPE_BOND_CPF: eOesSubSecurityTypeT = 23
    OES_SUB_SECURITY_TYPE_BOND_CCF: eOesSubSecurityTypeT = 24
    OES_SUB_SECURITY_TYPE_BOND_FBF: eOesSubSecurityTypeT = 25
    OES_SUB_SECURITY_TYPE_BOND_PRP: eOesSubSecurityTypeT = 26
    OES_SUB_SECURITY_TYPE_BOND_STD: eOesSubSecurityTypeT = 27
    __OES_SUB_SECURITY_TYPE_BOND_MAX: eOesSubSecurityTypeT = 28
    __OES_SUB_SECURITY_TYPE_ETF_MIN: eOesSubSecurityTypeT = 30
    OES_SUB_SECURITY_TYPE_ETF_SINGLE_MKT: eOesSubSecurityTypeT = 31
    OES_SUB_SECURITY_TYPE_ETF_CROSS_MKT: eOesSubSecurityTypeT = 32
    OES_SUB_SECURITY_TYPE_ETF_BOND: eOesSubSecurityTypeT = 33
    OES_SUB_SECURITY_TYPE_ETF_CURRENCY: eOesSubSecurityTypeT = 34
    OES_SUB_SECURITY_TYPE_ETF_CROSS_BORDER: eOesSubSecurityTypeT = 35
    OES_SUB_SECURITY_TYPE_ETF_GOLD: eOesSubSecurityTypeT = 36
    __OES_SUB_SECURITY_TYPE_ETF_MAX: eOesSubSecurityTypeT = 37
    __OES_SUB_SECURITY_TYPE_FUND_MIN: eOesSubSecurityTypeT = 40
    OES_SUB_SECURITY_TYPE_FUND_LOF: eOesSubSecurityTypeT = 41
    OES_SUB_SECURITY_TYPE_FUND_CEF: eOesSubSecurityTypeT = 42
    OES_SUB_SECURITY_TYPE_FUND_OEF: eOesSubSecurityTypeT = 43
    OES_SUB_SECURITY_TYPE_FUND_GRADED: eOesSubSecurityTypeT = 44
    __OES_SUB_SECURITY_TYPE_FUND_MAX: eOesSubSecurityTypeT = 45
    __OES_SUB_SECURITY_TYPE_OPTION_MIN: eOesSubSecurityTypeT = 50
    OES_SUB_SECURITY_TYPE_OPTION_STOCK: eOesSubSecurityTypeT = 51
    OES_SUB_SECURITY_TYPE_OPTION_ETF: eOesSubSecurityTypeT = 52
    __OES_SUB_SECURITY_TYPE_OPTION_MAX: eOesSubSecurityTypeT = 53
    __OES_SUB_SECURITY_TYPE_MAX: eOesSubSecurityTypeT = 53
    ...

class eOesSecurityLevelT(Enum):
    OES_SECURITY_LEVEL_UNDEFINE: eOesSecurityLevelT
    OES_SECURITY_LEVEL_N: eOesSecurityLevelT = 1
    OES_SECURITY_LEVEL_XST: eOesSecurityLevelT = 2
    OES_SECURITY_LEVEL_ST: eOesSecurityLevelT = 3
    OES_SECURITY_LEVEL_P: eOesSecurityLevelT = 4
    OES_SECURITY_LEVEL_T: eOesSecurityLevelT = 5
    OES_SECURITY_LEVEL_U: eOesSecurityLevelT = 6
    OES_SECURITY_LEVEL_B: eOesSecurityLevelT = 7
    __OES_SECURITY_LEVEL_MAX: eOesSecurityLevelT = 8
    ...

class eOesSecurityRiskLevelT(Enum):
    OES_RISK_LEVEL_VERY_LOW: eOesSecurityRiskLevelT
    OES_RISK_LEVEL_LOW: eOesSecurityRiskLevelT = 1
    OES_RISK_LEVEL_MEDIUM_LOW: eOesSecurityRiskLevelT = 2
    OES_RISK_LEVEL_MEDIUM: eOesSecurityRiskLevelT = 3
    OES_RISK_LEVEL_MEDIUM_HIGH: eOesSecurityRiskLevelT = 4
    OES_RISK_LEVEL_HIGH: eOesSecurityRiskLevelT = 5
    OES_RISK_LEVEL_VERY_HIGH: eOesSecurityRiskLevelT = 6
    __OES_RISK_LEVEL_MAX: eOesSecurityRiskLevelT = 7
    ...

class eOesSecuritySuspFlagT(Enum):
    OES_SUSPFLAG_NONE: eOesSecuritySuspFlagT
    OES_SUSPFLAG_EXCHANGE: eOesSecuritySuspFlagT = 1
    OES_SUSPFLAG_BROKER: eOesSecuritySuspFlagT = 2
    __OES_SUSPFLAG_OTHER: eOesSecuritySuspFlagT = 3
    ...

class eOesOrdStatusT(Enum):
    OES_ORD_STATUS_UNDEFINE: eOesOrdStatusT
    OES_ORD_STATUS_NEW: eOesOrdStatusT = 1
    OES_ORD_STATUS_DECLARED: eOesOrdStatusT = 2
    OES_ORD_STATUS_PARTIALLY_FILLED: eOesOrdStatusT = 3
    __OES_ORD_STATUS_FINAL_MIN: eOesOrdStatusT = 4
    OES_ORD_STATUS_CANCEL_DONE: eOesOrdStatusT = 5
    OES_ORD_STATUS_PARTIALLY_CANCELED: eOesOrdStatusT = 6
    OES_ORD_STATUS_CANCELED: eOesOrdStatusT = 7
    OES_ORD_STATUS_FILLED: eOesOrdStatusT = 8
    __OES_ORD_STATUS_VALID_MAX: eOesOrdStatusT = 9
    __OES_ORD_STATUS_INVALID_MIN: eOesOrdStatusT = 10
    OES_ORD_STATUS_INVALID_OES: eOesOrdStatusT = 11
    OES_ORD_STATUS_INVALID_SH_F: eOesOrdStatusT = 12
    OES_ORD_STATUS_INVALID_SH_E: eOesOrdStatusT = 13
    OES_ORD_STATUS_INVALID_SH_COMM: eOesOrdStatusT = 14
    OES_ORD_STATUS_INVALID_SZ_F: eOesOrdStatusT = 15
    OES_ORD_STATUS_INVALID_SZ_E: eOesOrdStatusT = 16
    OES_ORD_STATUS_INVALID_SZ_REJECT: eOesOrdStatusT = 17
    OES_ORD_STATUS_INVALID_SZ_TRY_AGAIN: eOesOrdStatusT = 18
    __OES_ORD_STATUS_INVALID_MAX: eOesOrdStatusT = 19
    OES_ORD_STATUS_NORMAL: eOesOrdStatusT = 1
    OES_ORD_STATUS_DECLARING: eOesOrdStatusT = 1
    __OES_ORD_STATUS_INVALID_OES: eOesOrdStatusT = 11
    ...

class eOesOrdTypeT(Enum):
    OES_ORD_TYPE_LMT: eOesOrdTypeT
    OES_ORD_TYPE_LMT_FOK: eOesOrdTypeT = 1
    __OES_ORD_TYPE_LMT_MAX: eOesOrdTypeT = 2
    OES_ORD_TYPE_MTL_BEST_5: eOesOrdTypeT = 10
    OES_ORD_TYPE_MTL_BEST: eOesOrdTypeT = 11
    OES_ORD_TYPE_MTL_SAMEPARTY_BEST: eOesOrdTypeT = 12
    __OES_ORD_TYPE_MTL_MAX: eOesOrdTypeT = 13
    OES_ORD_TYPE_FAK_BEST_5: eOesOrdTypeT = 20
    OES_ORD_TYPE_FAK: eOesOrdTypeT = 21
    __OES_ORD_TYPE_FAK_MAX: eOesOrdTypeT = 22
    OES_ORD_TYPE_FOK: eOesOrdTypeT = 30
    __OES_ORD_TYPE_FOK_MAX: eOesOrdTypeT = 31
    __OES_ORD_TYPE_MAX: eOesOrdTypeT = 32
    ...

class eOesOrdTypeShT(Enum):
    OES_ORD_TYPE_SH_LMT: eOesOrdTypeShT
    OES_ORD_TYPE_SH_MTL_BEST_5: eOesOrdTypeShT = 10
    OES_ORD_TYPE_SH_FAK_BEST_5: eOesOrdTypeShT = 20
    OES_ORD_TYPE_SH_LMT_FOK: eOesOrdTypeShT = 1
    OES_ORD_TYPE_SH_FOK: eOesOrdTypeShT = 30
    ...

class eOesOrdTypeSzT(Enum):
    OES_ORD_TYPE_SZ_LMT: eOesOrdTypeSzT
    OES_ORD_TYPE_SZ_MTL_BEST: eOesOrdTypeSzT = 11
    OES_ORD_TYPE_SZ_MTL_SAMEPARTY_BEST: eOesOrdTypeSzT = 12
    OES_ORD_TYPE_SZ_FAK_BEST_5: eOesOrdTypeSzT = 20
    OES_ORD_TYPE_SZ_FAK: eOesOrdTypeSzT = 21
    OES_ORD_TYPE_SZ_FOK: eOesOrdTypeSzT = 30
    OES_ORD_TYPE_SZ_LMT_FOK: eOesOrdTypeSzT = 1
    ...

class eOesBuySellTypeT(Enum):
    OES_BS_TYPE_UNDEFINE: eOesBuySellTypeT
    OES_BS_TYPE_BUY: eOesBuySellTypeT = 1
    OES_BS_TYPE_SELL: eOesBuySellTypeT = 2
    OES_BS_TYPE_CREATION: eOesBuySellTypeT = 3
    OES_BS_TYPE_REDEMPTION: eOesBuySellTypeT = 4
    OES_BS_TYPE_CREDIT_BUY: eOesBuySellTypeT = 5
    OES_BS_TYPE_CREDIT_SELL: eOesBuySellTypeT = 6
    OES_BS_TYPE_SUBSCRIPTION: eOesBuySellTypeT = 7
    OES_BS_TYPE_BUY_OPEN: eOesBuySellTypeT = 11
    OES_BS_TYPE_BUY_CLOSE: eOesBuySellTypeT = 12
    OES_BS_TYPE_SELL_OPEN: eOesBuySellTypeT = 13
    OES_BS_TYPE_SELL_CLOSE: eOesBuySellTypeT = 14
    OES_BS_TYPE_COVERED_OPEN: eOesBuySellTypeT = 15
    OES_BS_TYPE_COVERED_CLOSE: eOesBuySellTypeT = 16
    OES_BS_TYPE_OPTION_EXERCISE: eOesBuySellTypeT = 17
    OES_BS_TYPE_UNDERLYING_FREEZE: eOesBuySellTypeT = 18
    OES_BS_TYPE_UNDERLYING_UNFREEZE: eOesBuySellTypeT = 19
    OES_BS_TYPE_CANCEL: eOesBuySellTypeT = 30
    __OES_BS_TYPE_MAX_TRADING: eOesBuySellTypeT = 31
    OES_BS_TYPE_SSE_DESIGNATION: eOesBuySellTypeT = 41
    OES_BS_TYPE_SSE_RECALL_DESIGNATION: eOesBuySellTypeT = 42
    OES_BS_TYPE_SZSE_DESIGNATION: eOesBuySellTypeT = 43
    OES_BS_TYPE_SZSE_CANCEL_DESIGNATION: eOesBuySellTypeT = 44
    __OES_BS_TYPE_MAX: eOesBuySellTypeT = 45
    OES_BS_TYPE_B: eOesBuySellTypeT = 1
    OES_BS_TYPE_S: eOesBuySellTypeT = 2
    OES_BS_TYPE_KB: eOesBuySellTypeT = 3
    OES_BS_TYPE_KS: eOesBuySellTypeT = 4
    OES_BS_TYPE_CB: eOesBuySellTypeT = 5
    OES_BS_TYPE_CS: eOesBuySellTypeT = 6
    OES_BS_TYPE_BO: eOesBuySellTypeT = 11
    OES_BS_TYPE_BC: eOesBuySellTypeT = 12
    OES_BS_TYPE_SO: eOesBuySellTypeT = 13
    OES_BS_TYPE_SC: eOesBuySellTypeT = 14
    OES_BS_TYPE_CO: eOesBuySellTypeT = 15
    OES_BS_TYPE_CC: eOesBuySellTypeT = 16
    OES_BS_TYPE_TE: eOesBuySellTypeT = 17
    OES_BS_TYPE_UF: eOesBuySellTypeT = 18
    OES_BS_TYPE_UU: eOesBuySellTypeT = 19
    ...

class eOesOrdDirT(Enum):
    OES_ORD_DIR_BUY: eOesOrdDirT
    OES_ORD_DIR_SELL: eOesOrdDirT = 1
    __OES_ORD_DIR_MAX: eOesOrdDirT = 2
    ...

class eOesEtfTrdCnfmTypeT(Enum):
    OES_ETF_TRDCNFM_TYPE_NONE: eOesEtfTrdCnfmTypeT
    OES_ETF_TRDCNFM_TYPE_ETF_FIRST: eOesEtfTrdCnfmTypeT = 1
    OES_ETF_TRDCNFM_TYPE_CMPOENT: eOesEtfTrdCnfmTypeT = 2
    OES_ETF_TRDCNFM_TYPE_CASH: eOesEtfTrdCnfmTypeT = 3
    OES_ETF_TRDCNFM_TYPE_ETF_LAST: eOesEtfTrdCnfmTypeT = 4
    __OES_ETF_TRDCNFM_TYPE_MAX: eOesEtfTrdCnfmTypeT = 5
    ...

class eOesEtfSubFlagT(Enum):
    OES_ETF_SUBFLAG_FORBID_SUB: eOesEtfSubFlagT
    OES_ETF_SUBFLAG_ALLOW_SUB: eOesEtfSubFlagT = 1
    OES_ETF_SUBFLAG_MUST_SUB: eOesEtfSubFlagT = 2
    OES_ETF_SUBFLAG_SZ_REFUND_SUB: eOesEtfSubFlagT = 3
    OES_ETF_SUBFLAG_SZ_MUST_SUB: eOesEtfSubFlagT = 4
    OES_ETF_SUBFLAG_OTHER_REFUND_SUB: eOesEtfSubFlagT = 5
    OES_ETF_SUBFLAG_OTHER_MUST_SUB: eOesEtfSubFlagT = 6
    ...

class eOesLotTypeT(Enum):
    OES_LOT_TYPE_UNDEFINE: eOesLotTypeT
    OES_LOT_TYPE_FAILED: eOesLotTypeT = 1
    OES_LOT_TYPE_ASSIGNMENT: eOesLotTypeT = 2
    OES_LOT_TYPE_LOTTERY: eOesLotTypeT = 3
    __OES_LOT_TYPE_MAX: eOesLotTypeT = 4
    ...

class eOesLotRejReasonT(Enum):
    OES_LOT_REJ_REASON_DUPLICATE: eOesLotRejReasonT = 1
    OES_LOT_REJ_REASON_INVALID_DUPLICATE: eOesLotRejReasonT = 2
    OES_LOT_REJ_REASON_OFFLINE_FIRST: eOesLotRejReasonT = 3
    OES_LOT_REJ_REASON_BAD_RECORD: eOesLotRejReasonT = 4
    OES_LOT_REJ_REASON_UNKNOW: eOesLotRejReasonT = 5
    ...

class eOesExecTypeT(Enum):
    OES_EXECTYPE_UNDEFINE: eOesExecTypeT
    OES_EXECTYPE_INSERT: eOesExecTypeT = 1
    OES_EXECTYPE_CONFIRMED: eOesExecTypeT = 2
    OES_EXECTYPE_CANCELLED: eOesExecTypeT = 3
    OES_EXECTYPE_AUTO_CANCELLED: eOesExecTypeT = 4
    OES_EXECTYPE_REJECT: eOesExecTypeT = 5
    OES_EXECTYPE_TRADE: eOesExecTypeT = 6
    __OES_EXECTYPE_MAX: eOesExecTypeT = 7
    ...

class eOesCurrTypeT(Enum):
    OES_CURR_TYPE_RMB: eOesCurrTypeT
    OES_CURR_TYPE_HKD: eOesCurrTypeT = 1
    OES_CURR_TYPE_USD: eOesCurrTypeT = 2
    __OES_CURR_TYPE_MAX: eOesCurrTypeT = 3
    ...

class eOesFeeTypeT(Enum):
    OES_FEE_TYPE_EXCHANGE_STAMP: eOesFeeTypeT = 1
    OES_FEE_TYPE_EXCHANGE_TRANSFER: eOesFeeTypeT = 2
    OES_FEE_TYPE_EXCHANGE_SETTLEMENT: eOesFeeTypeT = 3
    OES_FEE_TYPE_EXCHANGE_TRADE_RULE: eOesFeeTypeT = 4
    OES_FEE_TYPE_EXCHANGE_EXCHANGE: eOesFeeTypeT = 5
    OES_FEE_TYPE_EXCHANGE_ADMINFER: eOesFeeTypeT = 6
    OES_FEE_TYPE_EXCHANGE_OTHER: eOesFeeTypeT = 7
    __OES_FEE_TYPE_EXCHANGE_MAX: eOesFeeTypeT = 8
    OES_FEE_TYPE_BROKER_BACK_END: eOesFeeTypeT = 17
    ...

class eOesCalcFeeModeT(Enum):
    OES_CALC_FEE_MODE_AMOUNT: eOesCalcFeeModeT
    OES_CALC_FEE_MODE_QTY: eOesCalcFeeModeT = 1
    OES_CALC_FEE_MODE_ORD: eOesCalcFeeModeT = 2
    ...

class eOesFundTrsfDirectT(Enum):
    OES_FUND_TRSF_DIRECT_IN: eOesFundTrsfDirectT
    OES_FUND_TRSF_DIRECT_OUT: eOesFundTrsfDirectT = 1
    ...

class eOesFundTrsfTypeT(Enum):
    OES_FUND_TRSF_TYPE_OES_BANK: eOesFundTrsfTypeT
    OES_FUND_TRSF_TYPE_OES_COUNTER: eOesFundTrsfTypeT = 1
    OES_FUND_TRSF_TYPE_COUNTER_BANK: eOesFundTrsfTypeT = 2
    __OES_FUND_TRSF_TYPE_MAX: eOesFundTrsfTypeT = 3
    ...

class eOesFundTrsfStatusT(Enum):
    OES_FUND_TRSF_STS_UNDECLARED: eOesFundTrsfStatusT
    OES_FUND_TRSF_STS_DECLARED: eOesFundTrsfStatusT = 1
    OES_FUND_TRSF_STS_WAIT_DONE: eOesFundTrsfStatusT = 2
    OES_FUND_TRSF_STS_DONE: eOesFundTrsfStatusT = 3
    __OES_FUND_TRSF_STS_ROLLBACK_MIN: eOesFundTrsfStatusT = 5
    OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK: eOesFundTrsfStatusT = 6
    OES_FUND_TRSF_STS_DECLARED_ROLLBACK: eOesFundTrsfStatusT = 7
    __OES_FUND_TRSF_STS_INVALID_MIN: eOesFundTrsfStatusT = 10
    OES_FUND_TRSF_STS_INVALID_OES: eOesFundTrsfStatusT = 11
    OES_FUND_TRSF_STS_INVALID_COUNTER: eOesFundTrsfStatusT = 12
    OES_FUND_TRSF_STS_SUSPENDED: eOesFundTrsfStatusT = 13
    ...

class eOesAcctTypeT(Enum):
    OES_ACCT_TYPE_NORMAL: eOesAcctTypeT
    OES_ACCT_TYPE_CREDIT: eOesAcctTypeT = 1
    OES_ACCT_TYPE_OPTION: eOesAcctTypeT = 2
    __OES_ACCT_TYPE_MAX: eOesAcctTypeT = 3
    ...

class eOesCashTypeT(Enum):
    OES_CASH_TYPE_SPOT: eOesCashTypeT
    OES_CASH_TYPE_CREDIT: eOesCashTypeT = 1
    OES_CASH_TYPE_OPTION: eOesCashTypeT = 2
    __OES_CASH_TYPE_MAX: eOesCashTypeT = 3
    OES_CASH_TYPE_CRE: eOesCashTypeT = 1
    OES_CASH_TYPE_OPT: eOesCashTypeT = 2
    ...

class eOesAcctStatusT(Enum):
    OES_ACCT_STATUS_NORMAL: eOesAcctStatusT
    OES_ACCT_STATUS_DISABLED: eOesAcctStatusT = 1
    OES_ACCT_STATUS_LOCKED: eOesAcctStatusT = 2
    ...

class eOesTradingPermissionT(Enum):
    OES_PERMIS_MARKET_ORDER: eOesTradingPermissionT = 2
    OES_PERMIS_STRUCTURED_FUND: eOesTradingPermissionT = 4
    OES_PERMIS_BOND_QUALIFIED_INVESTOR: eOesTradingPermissionT = 8
    OES_PERMIS_XXX4: eOesTradingPermissionT = 16
    OES_PERMIS_DELISTING: eOesTradingPermissionT = 32
    OES_PERMIS_RISK_WARNING: eOesTradingPermissionT = 64
    OES_PERMIS_SINGLE_MARKET_ETF: eOesTradingPermissionT = 128
    OES_PERMIS_CROSS_BORDER_ETF: eOesTradingPermissionT = 256
    OES_PERMIS_CROSS_MARKET_ETF: eOesTradingPermissionT = 512
    OES_PERMIS_CURRENCY_ETF: eOesTradingPermissionT = 1024
    OES_PERMIS_STOCK_PLEDGE_REPURCHASE: eOesTradingPermissionT = 2048
    OES_PERMIS_PLEDGE_REPURCHASE: eOesTradingPermissionT = 4096
    OES_PERMIS_GEM: eOesTradingPermissionT = 8192
    OES_PERMIS_SH_HK_STOCK_CONNECT: eOesTradingPermissionT = 16384
    OES_PERMIS_SZ_HK_STOCK_CONNECT: eOesTradingPermissionT = 32768
    OES_PERMIS_CDR: eOesTradingPermissionT = 65536
    OES_PERMIS_INNOVATION: eOesTradingPermissionT = 131072
    __OES_PERMIS_ALL: eOesTradingPermissionT = -1
    ...

class eOesTradingLimitT(Enum):
    OES_LIMIT_BUY: eOesTradingLimitT = 2
    OES_LIMIT_SELL: eOesTradingLimitT = 4
    OES_LIMIT_RECALL_DESIGNATION: eOesTradingLimitT = 8
    OES_LIMIT_DESIGNATION: eOesTradingLimitT = 16
    OES_LIMIT_REPO: eOesTradingLimitT = 32
    OES_LIMIT_REVERSE_REPO: eOesTradingLimitT = 64
    OES_LIMIT_SUBSCRIPTION: eOesTradingLimitT = 128
    OES_LIMIT_CREDIT_BUY: eOesTradingLimitT = 256
    OES_LIMIT_CREDIT_SELL: eOesTradingLimitT = 512
    __OES_LIMIT_ALL: eOesTradingLimitT = -1
    ...

class eOesQualificationClassT(Enum):
    OES_QUALIFICATION_PUBLIC_INVESTOR: eOesQualificationClassT
    OES_QUALIFICATION_QUALIFIED_INVESTOR: eOesQualificationClassT = 1
    OES_QUALIFICATION_QUALIFIED_INSTITUTIONAL: eOesQualificationClassT = 2
    ...

class eOesInvestorClassT(Enum):
    OES_INVESTOR_CLASS_NORMAL: eOesInvestorClassT
    OES_INVESTOR_CLASS_PROFESSIONAL_A: eOesInvestorClassT = 1
    OES_INVESTOR_CLASS_PROFESSIONAL_B: eOesInvestorClassT = 2
    OES_INVESTOR_CLASS_PROFESSIONAL_C: eOesInvestorClassT = 3
    ...

class eOesOwnerTypeT(Enum):
    OES_OWNER_TYPE_PERSONAL: eOesOwnerTypeT = 1
    OES_OWNER_TYPE_EXCHANGE: eOesOwnerTypeT = 101
    OES_OWNER_TYPE_MEMBER: eOesOwnerTypeT = 102
    OES_OWNER_TYPE_INSTITUTION: eOesOwnerTypeT = 103
    OES_OWNER_TYPE_PROPRIETARY: eOesOwnerTypeT = 104
    OES_OWNER_TYPE_MKT_MAKER: eOesOwnerTypeT = 105
    OES_OWNER_TYPE_SETTLEMENT: eOesOwnerTypeT = 106
    __OES_OWNER_TYPE_MAX: eOesOwnerTypeT = 107
    ...

class eOesClientTypeT(Enum):
    OES_CLIENT_TYPE_UNDEFINED: eOesClientTypeT
    OES_CLIENT_TYPE_INVESTOR: eOesClientTypeT = 1
    OES_CLIENT_TYPE_VIRTUAL: eOesClientTypeT = 2
    ...

class eOesClientStatusT(Enum):
    OES_CLIENT_STATUS_UNACTIVATED: eOesClientStatusT
    OES_CLIENT_STATUS_ACTIVATED: eOesClientStatusT = 1
    OES_CLIENT_STATUS_PAUSE: eOesClientStatusT = 2
    OES_CLIENT_STATUS_SUSPENDED: eOesClientStatusT = 3
    OES_CLIENT_STATUS_CANCELLED: eOesClientStatusT = 4
    ...

class eOesOptContractTypeT(Enum):
    OES_OPT_CONTRACT_TYPE_CALL: eOesOptContractTypeT
    OES_OPT_CONTRACT_TYPE_PUT: eOesOptContractTypeT = 1
    __OES_OPT_CONTRACT_TYPE_MAX: eOesOptContractTypeT = 2
    ...

class eOesOptInvLevelT(Enum):
    OES_OPT_INV_LEVEL_B: eOesOptInvLevelT
    OES_OPT_INV_LEVEL_L: eOesOptInvLevelT = 1
    OES_OPT_INV_LEVEL_A: eOesOptInvLevelT = 2
    __OES_OPT_INV_LEVEL_MAX: eOesOptInvLevelT = 3
    ...

class eOpenFlagTypeT(Enum):
    OPEN_FLAG_TYPE_ALLOW: eOpenFlagTypeT
    OPEN_FLAG_TYPE_FORBID: eOpenFlagTypeT = 1
    __OPEN_FLAG_TYPE_MAX: eOpenFlagTypeT = 2
    ...

class eOesOptionOpenFlagT(Enum):
    OES_OPTION_OPEN_FLAG_ALLOW: eOesOptionOpenFlagT
    OES_OPTION_OPEN_FLAG_FORBID: eOesOptionOpenFlagT = 1
    ...

class eOesPositionEffT(Enum):
    OES_POSITION_INVALID: eOesPositionEffT
    OES_POSITION_OPEN: eOesPositionEffT = 1
    OES_POSITION_CLOSE: eOesPositionEffT = 2
    ...

class eOesOptionTypeT(Enum):
    OES_OPTION_TYPE_E: eOesOptionTypeT
    OES_OPTION_TYPE_A: eOesOptionTypeT = 1
    __OES_OPTION_TYPE_MAX: eOesOptionTypeT = 2
    ...

class eSMsgProtocolTypeT(Enum):
    SMSG_PROTO_BINARY: eSMsgProtocolTypeT
    SMSG_PROTO_JSON: eSMsgProtocolTypeT = 1
    SMSG_PROTO_FIX: eSMsgProtocolTypeT = 2
    SMSG_PROTO_PROTOBUF: eSMsgProtocolTypeT = 3
    __MAX_SMSG_PROTO_TYPE: eSMsgProtocolTypeT = 4
    ...

class eSMsgFlagT(Enum):
    SMSG_MSGFLAG_NONE: eSMsgFlagT
    SMSG_MSGFLAG_REQ: eSMsgFlagT
    SMSG_MSGFLAG_RSP: eSMsgFlagT = 80
    SMSG_MSGFLAG_NESTED: eSMsgFlagT = 32
    SMSG_MSGFLAG_COMPRESSED: eSMsgFlagT = 128
    SMSG_MSGFLAG_MASK_RSPFLAG: eSMsgFlagT = 240
    SMSG_MSGFLAG_MASK_PROTOCOL: eSMsgFlagT = 15
    ...

class eOesMsgTypeT(Enum):
    OESMSG_ORD_NEW_ORDER: eOesMsgTypeT = 1
    OESMSG_ORD_CANCEL_REQUEST: eOesMsgTypeT = 2
    OESMSG_ORD_BATCH_ORDERS: eOesMsgTypeT = 3
    __OESMSG_ORD_MAX: eOesMsgTypeT = 4
    __OESMSG_RPT_MIN: eOesMsgTypeT = 15
    OESMSG_RPT_MARKET_STATE: eOesMsgTypeT = 16
    OESMSG_RPT_REPORT_SYNCHRONIZATION: eOesMsgTypeT = 17
    OESMSG_RPT_BUSINESS_REJECT: eOesMsgTypeT = 18
    OESMSG_RPT_ORDER_INSERT: eOesMsgTypeT = 19
    OESMSG_RPT_ORDER_REPORT: eOesMsgTypeT = 20
    OESMSG_RPT_TRADE_REPORT: eOesMsgTypeT = 21
    OESMSG_RPT_FUND_TRSF_REJECT: eOesMsgTypeT = 22
    OESMSG_RPT_FUND_TRSF_REPORT: eOesMsgTypeT = 23
    OESMSG_RPT_CASH_ASSET_VARIATION: eOesMsgTypeT = 24
    OESMSG_RPT_STOCK_HOLDING_VARIATION: eOesMsgTypeT = 25
    OESMSG_RPT_OPTION_HOLDING_VARIATION: eOesMsgTypeT = 26
    __OESMSG_RPT_MAX: eOesMsgTypeT = 27
    __OESMSG_NONTRD_MIN: eOesMsgTypeT = 32
    OESMSG_NONTRD_FUND_TRSF_REQ: eOesMsgTypeT = 33
    OESMSG_NONTRD_CHANGE_PASSWORD: eOesMsgTypeT = 34
    __OESMSG_NONTRD_MAX: eOesMsgTypeT = 35
    __OESMSG_QRYMSG_MIN: eOesMsgTypeT = 47
    OESMSG_QRYMSG_CLIENT_OVERVIEW: eOesMsgTypeT = 48
    OESMSG_QRYMSG_ORD: eOesMsgTypeT = 49
    OESMSG_QRYMSG_TRD: eOesMsgTypeT = 50
    OESMSG_QRYMSG_CASH_ASSET: eOesMsgTypeT = 51
    OESMSG_QRYMSG_STK_HLD: eOesMsgTypeT = 52
    OESMSG_QRYMSG_OPT_HLD: eOesMsgTypeT = 53
    OESMSG_QRYMSG_CUST: eOesMsgTypeT = 54
    OESMSG_QRYMSG_INV_ACCT: eOesMsgTypeT = 55
    OESMSG_QRYMSG_COMMISSION_RATE: eOesMsgTypeT = 56
    OESMSG_QRYMSG_FUND_TRSF: eOesMsgTypeT = 57
    OESMSG_QRYMSG_STOCK: eOesMsgTypeT = 58
    OESMSG_QRYMSG_ETF: eOesMsgTypeT = 59
    OESMSG_QRYMSG_ETF_COMPONENT: eOesMsgTypeT = 60
    OESMSG_QRYMSG_OPTION: eOesMsgTypeT = 61
    OESMSG_QRYMSG_ISSUE: eOesMsgTypeT = 62
    OESMSG_QRYMSG_LOT_WINNING: eOesMsgTypeT = 63
    OESMSG_QRYMSG_TRADING_DAY: eOesMsgTypeT = 64
    OESMSG_QRYMSG_MARKET_STATE: eOesMsgTypeT = 65
    OESMSG_QRYMSG_COUNTER_CASH: eOesMsgTypeT = 66
    __OESMSG_QRYMSG_MAX: eOesMsgTypeT = 67
    OESMSG_SESS_TRD_LOGIN: eOesMsgTypeT = 241
    OESMSG_SESS_RPT_LOGIN: eOesMsgTypeT = 243
    OESMSG_SESS_QRY_LOGIN: eOesMsgTypeT = 244
    OESMSG_SESS_HEARTBEAT: eOesMsgTypeT = 250
    OESMSG_SESS_TEST_REQUEST: eOesMsgTypeT = 251
    OESMSG_SESS_LOGOUT: eOesMsgTypeT = 254
    OESMSG_RPT_ORDER_REJECT: eOesMsgTypeT = 18
    ...

class eOesSubscribeReportTypeT(Enum):
    OES_SUB_RPT_TYPE_DEFAULT: eOesSubscribeReportTypeT
    OES_SUB_RPT_TYPE_BUSINESS_REJECT: eOesSubscribeReportTypeT = 1
    OES_SUB_RPT_TYPE_ORDER_INSERT: eOesSubscribeReportTypeT = 2
    OES_SUB_RPT_TYPE_ORDER_REPORT: eOesSubscribeReportTypeT = 4
    OES_SUB_RPT_TYPE_TRADE_REPORT: eOesSubscribeReportTypeT = 8
    OES_SUB_RPT_TYPE_FUND_TRSF_REPORT: eOesSubscribeReportTypeT = 16
    OES_SUB_RPT_TYPE_CASH_ASSET_VARIATION: eOesSubscribeReportTypeT = 32
    OES_SUB_RPT_TYPE_HOLDING_VARIATION: eOesSubscribeReportTypeT = 64
    OES_SUB_RPT_TYPE_MARKET_STATE: eOesSubscribeReportTypeT = 128
    OES_SUB_RPT_TYPE_ALL: eOesSubscribeReportTypeT = 65535
    __MAX_OES_SUB_RPT_TYPE: eOesSubscribeReportTypeT = 2147483647
    ...

class eSSocketProtocolTypeT(Enum):
    SPK_SOCKET_PROTOCOL_TCP: eSSocketProtocolTypeT
    SPK_SOCKET_PROTOCOL_IPC: eSSocketProtocolTypeT = 1
    SPK_SOCKET_PROTOCOL_UDP_UCAST: eSSocketProtocolTypeT = 2
    SPK_SOCKET_PROTOCOL_UDP_MCAST: eSSocketProtocolTypeT = 3
    SPK_SOCKET_PROTOCOL_PGM: eSSocketProtocolTypeT = 4
    SPK_SOCKET_PROTOCOL_EPGM: eSSocketProtocolTypeT = 5
    __MAX_SPK_SOCKET_PROTOCOL: eSSocketProtocolTypeT = 6
    ...

class eGeneralClientClusterTypeT(Enum):
    GENERAL_CLI_CLUSTER_UNDEFINED: eGeneralClientClusterTypeT
    GENERAL_CLI_CLUSTER_REPLICA_SET: eGeneralClientClusterTypeT = 1
    GENERAL_CLI_CLUSTER_PEER_NODES: eGeneralClientClusterTypeT = 2
    __MAX_GENERAL_CLI_CLUSTER_TYPE: eGeneralClientClusterTypeT = 3
    ...

class eGeneralClientEncryptTypeT(Enum):
    GENERAL_CLI_ENCRYPT_NONE: eGeneralClientEncryptTypeT
    GENERAL_CLI_ENCRYPT_MD5: eGeneralClientEncryptTypeT = 1
    GENERAL_CLI_ENCRYPT_SHA: eGeneralClientEncryptTypeT = 2
    GENERAL_CLI_ENCRYPT_DES: eGeneralClientEncryptTypeT = 16
    GENERAL_CLI_ENCRYPT_AES: eGeneralClientEncryptTypeT = 32
    GENERAL_CLI_ENCRYPT_RSA: eGeneralClientEncryptTypeT = 64
    ...

class eOesApiChannelTypeT(Enum):
    OESAPI_CHANNEL_TYPE_ORDER: eOesApiChannelTypeT = 1
    OESAPI_CHANNEL_TYPE_REPORT: eOesApiChannelTypeT = 2
    OESAPI_CHANNEL_TYPE_QUERY: eOesApiChannelTypeT = 3
    ...

class eMdsExchangeIdT(Enum):
    MDS_EXCH_SSE: eMdsExchangeIdT = 1
    MDS_EXCH_SZSE: eMdsExchangeIdT = 2
    __MAX_MDS_EXCH: eMdsExchangeIdT = 3
    __MAX_MDS_EXCH_ALIGNED4: eMdsExchangeIdT = 4
    __MAX_MDS_EXCH_ALIGNED8: eMdsExchangeIdT = 8
    ...

class eMdsMsgSourceT(Enum):
    MDS_MSGSRC_UNDEFINED: eMdsMsgSourceT
    MDS_MSGSRC_EZEI_TCP: eMdsMsgSourceT = 1
    MDS_MSGSRC_EZEI_UDP: eMdsMsgSourceT = 2
    MDS_MSGSRC_VDE_LEVEL2: eMdsMsgSourceT = 3
    MDS_MSGSRC_VDE_LEVEL1: eMdsMsgSourceT = 4
    MDS_MSGSRC_SZSE_MDGW_BINARY: eMdsMsgSourceT = 5
    MDS_MSGSRC_SZSE_MDGW_STEP: eMdsMsgSourceT = 6
    MDS_MSGSRC_MDS_TCP: eMdsMsgSourceT = 7
    MDS_MSGSRC_MDS_UDP: eMdsMsgSourceT = 8
    MDS_MSGSRC_FILE_MKTDT: eMdsMsgSourceT = 9
    MDS_MSGSRC_SSE_MDGW_BINARY: eMdsMsgSourceT = 10
    MDS_MSGSRC_SSE_MDGW_STEP: eMdsMsgSourceT = 11
    __MAX_MDS_MSGSRC: eMdsMsgSourceT = 12
    MDS_MSGSRC_MDGW_BINARY: eMdsMsgSourceT = 5
    MDS_MSGSRC_MDGW_STEP: eMdsMsgSourceT = 6
    ...

class eMdsSecurityTypeT(Enum):
    MDS_SECURITY_TYPE_STOCK: eMdsSecurityTypeT = 1
    MDS_SECURITY_TYPE_INDEX: eMdsSecurityTypeT = 2
    MDS_SECURITY_TYPE_OPTION: eMdsSecurityTypeT = 3
    __MAX_MDS_SECURITY_TYPE: eMdsSecurityTypeT = 4
    ...

class eMdsMdStreamTypeT(Enum):
    MDS_MD_STREAM_TYPE_INDEX: eMdsMdStreamTypeT = 1
    MDS_MD_STREAM_TYPE_STOCK: eMdsMdStreamTypeT = 2
    MDS_MD_STREAM_TYPE_BOND: eMdsMdStreamTypeT = 3
    MDS_MD_STREAM_TYPE_FUND: eMdsMdStreamTypeT = 4
    MDS_MD_STREAM_TYPE_SZSE_STOCK: eMdsMdStreamTypeT = 5
    MDS_MD_STREAM_TYPE_SZSE_REPO: eMdsMdStreamTypeT = 6
    MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS: eMdsMdStreamTypeT = 7
    MDS_MD_STREAM_TYPE_OPTION: eMdsMdStreamTypeT = 8
    MDS_MD_STREAM_TYPE_OTHERS: eMdsMdStreamTypeT = 9
    __MAX_MDS_MD_STREAM_TYPE: eMdsMdStreamTypeT = 10
    ...

class eMdsMdLevelT(Enum):
    MDS_MD_LEVEL_0: eMdsMdLevelT
    MDS_MD_LEVEL_1: eMdsMdLevelT = 1
    MDS_MD_LEVEL_2: eMdsMdLevelT = 2
    __MAX_MDS_MD_LEVEL: eMdsMdLevelT = 3
    ...

class eMdsL2PriceLevelOperatorT(Enum):
    MDS_L2_PX_OPERATOR_ADD: eMdsL2PriceLevelOperatorT = 1
    MDS_L2_PX_OPERATOR_UPDATE: eMdsL2PriceLevelOperatorT = 2
    MDS_L2_PX_OPERATOR_DELETE: eMdsL2PriceLevelOperatorT = 3
    __MAX_MDS_L2_PX_OPERATOR: eMdsL2PriceLevelOperatorT = 4
    ...

class eMdsL2VirtualAuctionSideT(Enum):
    MDS_L2_VIRTUAL_AUCTION_SIDE_NONE: eMdsL2VirtualAuctionSideT
    MDS_L2_VIRTUAL_AUCTION_SIDE_BID: eMdsL2VirtualAuctionSideT = 1
    MDS_L2_VIRTUAL_AUCTION_SIDE_OFFER: eMdsL2VirtualAuctionSideT = 2
    ...

class eMdsL2TradeExecTypeT(Enum):
    MDS_L2_TRADE_EXECTYPE_CANCELED: eMdsL2TradeExecTypeT = 52
    MDS_L2_TRADE_EXECTYPE_TRADE: eMdsL2TradeExecTypeT = 70
    ...

class eMdsL2TradeBSFlagT(Enum):
    MDS_L2_TRADE_BSFLAG_BUY: eMdsL2TradeBSFlagT = 66
    MDS_L2_TRADE_BSFLAG_SELL: eMdsL2TradeBSFlagT = 83
    MDS_L2_TRADE_BSFLAG_UNKNOWN: eMdsL2TradeBSFlagT = 78
    ...

class eMdsL2OrderSideT(Enum):
    MDS_L2_ORDER_SIDE_BUY: eMdsL2OrderSideT = 49
    MDS_L2_ORDER_SIDE_SELL: eMdsL2OrderSideT = 50
    MDS_L2_ORDER_SIDE_BORROW: eMdsL2OrderSideT = 71
    MDS_L2_ORDER_SIDE_LEND: eMdsL2OrderSideT = 70
    ...

class eMdsL2OrderTypeT(Enum):
    MDS_L2_ORDER_TYPE_MKT: eMdsL2OrderTypeT = 49
    MDS_L2_ORDER_TYPE_LMT: eMdsL2OrderTypeT = 50
    MDS_L2_ORDER_TYPE_SAMEPARTY_BEST: eMdsL2OrderTypeT = 85
    ...

class eMdsClientTypeT(Enum):
    MDS_CLIENT_TYPE_UNDEFINED: eMdsClientTypeT
    MDS_CLIENT_TYPE_INVESTOR: eMdsClientTypeT = 1
    MDS_CLIENT_TYPE_VIRTUAL: eMdsClientTypeT = 2
    ...

class eMdsClientStatusT(Enum):
    MDS_CLIENT_STATUS_UNACTIVATED: eMdsClientStatusT
    MDS_CLIENT_STATUS_ACTIVATED: eMdsClientStatusT = 1
    MDS_CLIENT_STATUS_PAUSE: eMdsClientStatusT = 2
    MDS_CLIENT_STATUS_SUSPENDED: eMdsClientStatusT = 3
    MDS_CLIENT_STATUS_CANCELLED: eMdsClientStatusT = 4
    ...

class eMdsMsgTypeT(Enum):
    MDS_MSGTYPE_HEARTBEAT: eMdsMsgTypeT = 1
    MDS_MSGTYPE_TEST_REQUEST: eMdsMsgTypeT = 2
    MDS_MSGTYPE_LOGON: eMdsMsgTypeT = 3
    MDS_MSGTYPE_LOGOUT: eMdsMsgTypeT = 4
    MDS_MSGTYPE_MARKET_DATA_REQUEST: eMdsMsgTypeT = 5
    MDS_MSGTYPE_COMPRESSED_PACKETS: eMdsMsgTypeT = 6
    __MDS_MSGTYPE_SESSION_MAX: eMdsMsgTypeT = 7
    MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH: eMdsMsgTypeT = 10
    MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH: eMdsMsgTypeT = 11
    MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH: eMdsMsgTypeT = 12
    MDS_MSGTYPE_TRADING_SESSION_STATUS: eMdsMsgTypeT = 13
    MDS_MSGTYPE_SECURITY_STATUS: eMdsMsgTypeT = 14
    __MDS_MSGTYPE_L1_MAX: eMdsMsgTypeT = 15
    MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT: eMdsMsgTypeT = 20
    MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT: eMdsMsgTypeT = 21
    MDS_MSGTYPE_L2_TRADE: eMdsMsgTypeT = 22
    MDS_MSGTYPE_L2_ORDER: eMdsMsgTypeT = 23
    MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL: eMdsMsgTypeT = 24
    MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL: eMdsMsgTypeT = 25
    MDS_MSGTYPE_L2_MARKET_OVERVIEW: eMdsMsgTypeT = 26
    MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE: eMdsMsgTypeT = 27
    __MDS_MSGTYPE_L2_MAX: eMdsMsgTypeT = 28
    MDS_MSGTYPE_QRY_MARKET_DATA_SNAPSHOT: eMdsMsgTypeT = 80
    MDS_MSGTYPE_QRY_SECURITY_STATUS: eMdsMsgTypeT = 81
    MDS_MSGTYPE_QRY_TRADING_SESSION_STATUS: eMdsMsgTypeT = 82
    __MDS_MSGTYPE_QRY_MAX: eMdsMsgTypeT = 83
    ...

class eMdsSubscribeModeT(Enum):
    MDS_SUB_MODE_SET: eMdsSubscribeModeT
    MDS_SUB_MODE_APPEND: eMdsSubscribeModeT = 1
    MDS_SUB_MODE_DELETE: eMdsSubscribeModeT = 2
    __MAX_MDS_SUB_MODE: eMdsSubscribeModeT = 3
    ...

class eMdsMktSubscribeFlagT(Enum):
    MDS_MKT_SUB_FLAG_DEFAULT: eMdsMktSubscribeFlagT
    MDS_MKT_SUB_FLAG_ALL: eMdsMktSubscribeFlagT = 1
    MDS_MKT_SUB_FLAG_DISABLE: eMdsMktSubscribeFlagT = 2
    __MAX_MDS_MKT_SUB_FLAG: eMdsMktSubscribeFlagT = 3
    ...

class eMdsSubscribedTickTypeT(Enum):
    MDS_TICK_TYPE_LATEST_SIMPLIFIED: eMdsSubscribedTickTypeT
    MDS_TICK_TYPE_LATEST_TIMELY: eMdsSubscribedTickTypeT = 1
    MDS_TICK_TYPE_ALL_INCREMENTS: eMdsSubscribedTickTypeT = 2
    __MAX_MDS_TICK_TYPE: eMdsSubscribedTickTypeT = 3
    ...

class eMdsSubscribedTickExpireTypeT(Enum):
    MDS_TICK_EXPIRE_TYPE_NONE: eMdsSubscribedTickExpireTypeT
    MDS_TICK_EXPIRE_TYPE_IMMEDIATE: eMdsSubscribedTickExpireTypeT = 1
    MDS_TICK_EXPIRE_TYPE_TIMELY: eMdsSubscribedTickExpireTypeT = 2
    MDS_TICK_EXPIRE_TYPE_TIMEOUT: eMdsSubscribedTickExpireTypeT = 3
    __MAX_MDS_TICK_EXPIRE_TYPE: eMdsSubscribedTickExpireTypeT = 4
    ...

class eMdsSubscribeDataTypeT(Enum):
    MDS_SUB_DATA_TYPE_DEFAULT: eMdsSubscribeDataTypeT
    MDS_SUB_DATA_TYPE_L1_SNAPSHOT: eMdsSubscribeDataTypeT = 1
    MDS_SUB_DATA_TYPE_L2_SNAPSHOT: eMdsSubscribeDataTypeT = 2
    MDS_SUB_DATA_TYPE_L2_BEST_ORDERS: eMdsSubscribeDataTypeT = 4
    MDS_SUB_DATA_TYPE_L2_TRADE: eMdsSubscribeDataTypeT = 8
    MDS_SUB_DATA_TYPE_L2_ORDER: eMdsSubscribeDataTypeT = 16
    MDS_SUB_DATA_TYPE_L2_VIRTUAL_AUCTION_PRICE: eMdsSubscribeDataTypeT = 32
    MDS_SUB_DATA_TYPE_L2_MARKET_OVERVIEW: eMdsSubscribeDataTypeT = 64
    MDS_SUB_DATA_TYPE_TRADING_SESSION_STATUS: eMdsSubscribeDataTypeT = 256
    MDS_SUB_DATA_TYPE_SECURITY_STATUS: eMdsSubscribeDataTypeT = 512
    MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT: eMdsSubscribeDataTypeT = 1024
    MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT: eMdsSubscribeDataTypeT = 2048
    MDS_SUB_DATA_TYPE_NONE: eMdsSubscribeDataTypeT = 32768
    MDS_SUB_DATA_TYPE_ALL: eMdsSubscribeDataTypeT = 65535
    __MAX_MDS_SUB_DATA_TYPE: eMdsSubscribeDataTypeT = 2147483647
    ...

class eMdsTickChannelNoT(Enum):
    MDS_CHANNEL_NO_DEFAULT: eMdsTickChannelNoT
    MDS_CHANNEL_NO_ONE: eMdsTickChannelNoT = 1
    MDS_CHANNEL_NO_TWO: eMdsTickChannelNoT = 2
    MDS_CHANNEL_NO_THREE: eMdsTickChannelNoT = 4
    MDS_CHANNEL_NO_FOUR: eMdsTickChannelNoT = 8
    MDS_CHANNEL_NO_ALL: eMdsTickChannelNoT = 15
    MDS_CHANNEL_NO_NONE: eMdsTickChannelNoT = 128
    ...

class eMdsApiChannelTypeT(Enum):
    MDSAPI_CHANNEL_TYPE_TCP: eMdsApiChannelTypeT = 1
    MDSAPI_CHANNEL_TYPE_UDP: eMdsApiChannelTypeT = 2
    MDSAPI_CHANNEL_TYPE_QUERY: eMdsApiChannelTypeT = 3
    ...

OES_EXCH_UNDEFINE: eOesExchangeIdT
OES_EXCH_SSE: eOesExchangeIdT = 1
OES_EXCH_SZSE: eOesExchangeIdT = 2
__MAX_OES_EXCH: eOesExchangeIdT = 3
OES_EXCHANGE_TYPE_SSE: eOesExchangeIdT = 1
OES_EXCHANGE_TYPE_SZSE: eOesExchangeIdT = 2
OES_MKT_UNDEFINE: eOesMarketIdT
OES_MKT_SH_ASHARE: eOesMarketIdT = 1
OES_MKT_SZ_ASHARE: eOesMarketIdT = 2
OES_MKT_SH_OPTION: eOesMarketIdT = 3
__OES_MKT_ID_MAX: eOesMarketIdT = 4
OES_MKT_ID_UNDEFINE: eOesMarketIdT
OES_MKT_ID_SH_A: eOesMarketIdT = 1
OES_MKT_ID_SZ_A: eOesMarketIdT = 2
OES_MKT_ID_SH_OPT: eOesMarketIdT = 3
__OES_MKT_ID_MAX_ALIGNED4: eOesMarketIdT = 4
__OES_MKT_ID_MAX_ALIGNED8: eOesMarketIdT = 8
OES_PLATFORM_UNDEFINE: eOesPlatformIdT
OES_PLATFORM_CASH_AUCTION: eOesPlatformIdT = 1
OES_PLATFORM_FINANCIAL_SERVICES: eOesPlatformIdT = 2
OES_PLATFORM_NON_TRADE: eOesPlatformIdT = 3
OES_PLATFORM_DERIVATIVE_AUCTION: eOesPlatformIdT = 4
__OES_PLATFORM_ID_MAX: eOesPlatformIdT = 5
__OES_PLATFORM_ACTIVE_MAX: eOesPlatformIdT = 4
OES_MKT_STATE_UNDEFINE: eOesMarketStatusT
OES_MKT_STATE_PRE_OPEN: eOesMarketStatusT = 1
OES_MKT_STATE_OPEN_UP_COMING: eOesMarketStatusT = 2
OES_MKT_STATE_OPEN: eOesMarketStatusT = 3
OES_MKT_STATE_HALT: eOesMarketStatusT = 4
OES_MKT_STATE_CLOSE: eOesMarketStatusT = 5
__OES_MKT_STATE_MAX: eOesMarketStatusT = 6
OES_TRD_SESS_TYPE_O: eOesTrdSessTypeT
OES_TRD_SESS_TYPE_T: eOesTrdSessTypeT = 1
OES_TRD_SESS_TYPE_C: eOesTrdSessTypeT = 2
__OES_TRD_SESS_TYPE_MAX: eOesTrdSessTypeT = 3
OES_SECURITY_TYPE_UNDEFINE: eOesSecurityTypeT
OES_SECURITY_TYPE_STOCK: eOesSecurityTypeT = 1
OES_SECURITY_TYPE_BOND: eOesSecurityTypeT = 2
OES_SECURITY_TYPE_ETF: eOesSecurityTypeT = 3
OES_SECURITY_TYPE_FUND: eOesSecurityTypeT = 4
OES_SECURITY_TYPE_OPTION: eOesSecurityTypeT = 5
__OES_SECURITY_TYPE_MAX: eOesSecurityTypeT = 6
__OES_SECURITY_TYPE_NOT_SUPPORT: eOesSecurityTypeT = 100
OES_SUB_SECURITY_TYPE_UNDEFINE: eOesSubSecurityTypeT
__OES_SUB_SECURITY_TYPE_STOCK_MIN: eOesSubSecurityTypeT = 10
OES_SUB_SECURITY_TYPE_STOCK_ASH: eOesSubSecurityTypeT = 11
OES_SUB_SECURITY_TYPE_STOCK_SME: eOesSubSecurityTypeT = 12
OES_SUB_SECURITY_TYPE_STOCK_GEM: eOesSubSecurityTypeT = 13
OES_SUB_SECURITY_TYPE_STOCK_CDR: eOesSubSecurityTypeT = 14
__OES_SUB_SECURITY_TYPE_STOCK_MAX: eOesSubSecurityTypeT = 15
__OES_SUB_SECURITY_TYPE_BOND_MIN: eOesSubSecurityTypeT = 20
OES_SUB_SECURITY_TYPE_BOND_GBF: eOesSubSecurityTypeT = 21
OES_SUB_SECURITY_TYPE_BOND_CBF: eOesSubSecurityTypeT = 22
OES_SUB_SECURITY_TYPE_BOND_CPF: eOesSubSecurityTypeT = 23
OES_SUB_SECURITY_TYPE_BOND_CCF: eOesSubSecurityTypeT = 24
OES_SUB_SECURITY_TYPE_BOND_FBF: eOesSubSecurityTypeT = 25
OES_SUB_SECURITY_TYPE_BOND_PRP: eOesSubSecurityTypeT = 26
OES_SUB_SECURITY_TYPE_BOND_STD: eOesSubSecurityTypeT = 27
__OES_SUB_SECURITY_TYPE_BOND_MAX: eOesSubSecurityTypeT = 28
__OES_SUB_SECURITY_TYPE_ETF_MIN: eOesSubSecurityTypeT = 30
OES_SUB_SECURITY_TYPE_ETF_SINGLE_MKT: eOesSubSecurityTypeT = 31
OES_SUB_SECURITY_TYPE_ETF_CROSS_MKT: eOesSubSecurityTypeT = 32
OES_SUB_SECURITY_TYPE_ETF_BOND: eOesSubSecurityTypeT = 33
OES_SUB_SECURITY_TYPE_ETF_CURRENCY: eOesSubSecurityTypeT = 34
OES_SUB_SECURITY_TYPE_ETF_CROSS_BORDER: eOesSubSecurityTypeT = 35
OES_SUB_SECURITY_TYPE_ETF_GOLD: eOesSubSecurityTypeT = 36
__OES_SUB_SECURITY_TYPE_ETF_MAX: eOesSubSecurityTypeT = 37
__OES_SUB_SECURITY_TYPE_FUND_MIN: eOesSubSecurityTypeT = 40
OES_SUB_SECURITY_TYPE_FUND_LOF: eOesSubSecurityTypeT = 41
OES_SUB_SECURITY_TYPE_FUND_CEF: eOesSubSecurityTypeT = 42
OES_SUB_SECURITY_TYPE_FUND_OEF: eOesSubSecurityTypeT = 43
OES_SUB_SECURITY_TYPE_FUND_GRADED: eOesSubSecurityTypeT = 44
__OES_SUB_SECURITY_TYPE_FUND_MAX: eOesSubSecurityTypeT = 45
__OES_SUB_SECURITY_TYPE_OPTION_MIN: eOesSubSecurityTypeT = 50
OES_SUB_SECURITY_TYPE_OPTION_STOCK: eOesSubSecurityTypeT = 51
OES_SUB_SECURITY_TYPE_OPTION_ETF: eOesSubSecurityTypeT = 52
__OES_SUB_SECURITY_TYPE_OPTION_MAX: eOesSubSecurityTypeT = 53
__OES_SUB_SECURITY_TYPE_MAX: eOesSubSecurityTypeT = 53
OES_SECURITY_LEVEL_UNDEFINE: eOesSecurityLevelT
OES_SECURITY_LEVEL_N: eOesSecurityLevelT = 1
OES_SECURITY_LEVEL_XST: eOesSecurityLevelT = 2
OES_SECURITY_LEVEL_ST: eOesSecurityLevelT = 3
OES_SECURITY_LEVEL_P: eOesSecurityLevelT = 4
OES_SECURITY_LEVEL_T: eOesSecurityLevelT = 5
OES_SECURITY_LEVEL_U: eOesSecurityLevelT = 6
OES_SECURITY_LEVEL_B: eOesSecurityLevelT = 7
__OES_SECURITY_LEVEL_MAX: eOesSecurityLevelT = 8
OES_RISK_LEVEL_VERY_LOW: eOesSecurityRiskLevelT
OES_RISK_LEVEL_LOW: eOesSecurityRiskLevelT = 1
OES_RISK_LEVEL_MEDIUM_LOW: eOesSecurityRiskLevelT = 2
OES_RISK_LEVEL_MEDIUM: eOesSecurityRiskLevelT = 3
OES_RISK_LEVEL_MEDIUM_HIGH: eOesSecurityRiskLevelT = 4
OES_RISK_LEVEL_HIGH: eOesSecurityRiskLevelT = 5
OES_RISK_LEVEL_VERY_HIGH: eOesSecurityRiskLevelT = 6
__OES_RISK_LEVEL_MAX: eOesSecurityRiskLevelT = 7
OES_SUSPFLAG_NONE: eOesSecuritySuspFlagT
OES_SUSPFLAG_EXCHANGE: eOesSecuritySuspFlagT = 1
OES_SUSPFLAG_BROKER: eOesSecuritySuspFlagT = 2
__OES_SUSPFLAG_OTHER: eOesSecuritySuspFlagT = 3
OES_ORD_STATUS_UNDEFINE: eOesOrdStatusT
OES_ORD_STATUS_NEW: eOesOrdStatusT = 1
OES_ORD_STATUS_DECLARED: eOesOrdStatusT = 2
OES_ORD_STATUS_PARTIALLY_FILLED: eOesOrdStatusT = 3
__OES_ORD_STATUS_FINAL_MIN: eOesOrdStatusT = 4
OES_ORD_STATUS_CANCEL_DONE: eOesOrdStatusT = 5
OES_ORD_STATUS_PARTIALLY_CANCELED: eOesOrdStatusT = 6
OES_ORD_STATUS_CANCELED: eOesOrdStatusT = 7
OES_ORD_STATUS_FILLED: eOesOrdStatusT = 8
__OES_ORD_STATUS_VALID_MAX: eOesOrdStatusT = 9
__OES_ORD_STATUS_INVALID_MIN: eOesOrdStatusT = 10
OES_ORD_STATUS_INVALID_OES: eOesOrdStatusT = 11
OES_ORD_STATUS_INVALID_SH_F: eOesOrdStatusT = 12
OES_ORD_STATUS_INVALID_SH_E: eOesOrdStatusT = 13
OES_ORD_STATUS_INVALID_SH_COMM: eOesOrdStatusT = 14
OES_ORD_STATUS_INVALID_SZ_F: eOesOrdStatusT = 15
OES_ORD_STATUS_INVALID_SZ_E: eOesOrdStatusT = 16
OES_ORD_STATUS_INVALID_SZ_REJECT: eOesOrdStatusT = 17
OES_ORD_STATUS_INVALID_SZ_TRY_AGAIN: eOesOrdStatusT = 18
__OES_ORD_STATUS_INVALID_MAX: eOesOrdStatusT = 19
OES_ORD_STATUS_NORMAL: eOesOrdStatusT = 1
OES_ORD_STATUS_DECLARING: eOesOrdStatusT = 1
__OES_ORD_STATUS_INVALID_OES: eOesOrdStatusT = 11
OES_ORD_TYPE_LMT: eOesOrdTypeT
OES_ORD_TYPE_LMT_FOK: eOesOrdTypeT = 1
__OES_ORD_TYPE_LMT_MAX: eOesOrdTypeT = 2
OES_ORD_TYPE_MTL_BEST_5: eOesOrdTypeT = 10
OES_ORD_TYPE_MTL_BEST: eOesOrdTypeT = 11
OES_ORD_TYPE_MTL_SAMEPARTY_BEST: eOesOrdTypeT = 12
__OES_ORD_TYPE_MTL_MAX: eOesOrdTypeT = 13
OES_ORD_TYPE_FAK_BEST_5: eOesOrdTypeT = 20
OES_ORD_TYPE_FAK: eOesOrdTypeT = 21
__OES_ORD_TYPE_FAK_MAX: eOesOrdTypeT = 22
OES_ORD_TYPE_FOK: eOesOrdTypeT = 30
__OES_ORD_TYPE_FOK_MAX: eOesOrdTypeT = 31
__OES_ORD_TYPE_MAX: eOesOrdTypeT = 32
OES_ORD_TYPE_SH_LMT: eOesOrdTypeShT
OES_ORD_TYPE_SH_MTL_BEST_5: eOesOrdTypeShT = 10
OES_ORD_TYPE_SH_FAK_BEST_5: eOesOrdTypeShT = 20
OES_ORD_TYPE_SH_LMT_FOK: eOesOrdTypeShT = 1
OES_ORD_TYPE_SH_FOK: eOesOrdTypeShT = 30
OES_ORD_TYPE_SZ_LMT: eOesOrdTypeSzT
OES_ORD_TYPE_SZ_MTL_BEST: eOesOrdTypeSzT = 11
OES_ORD_TYPE_SZ_MTL_SAMEPARTY_BEST: eOesOrdTypeSzT = 12
OES_ORD_TYPE_SZ_FAK_BEST_5: eOesOrdTypeSzT = 20
OES_ORD_TYPE_SZ_FAK: eOesOrdTypeSzT = 21
OES_ORD_TYPE_SZ_FOK: eOesOrdTypeSzT = 30
OES_ORD_TYPE_SZ_LMT_FOK: eOesOrdTypeSzT = 1
OES_BS_TYPE_UNDEFINE: eOesBuySellTypeT
OES_BS_TYPE_BUY: eOesBuySellTypeT = 1
OES_BS_TYPE_SELL: eOesBuySellTypeT = 2
OES_BS_TYPE_CREATION: eOesBuySellTypeT = 3
OES_BS_TYPE_REDEMPTION: eOesBuySellTypeT = 4
OES_BS_TYPE_CREDIT_BUY: eOesBuySellTypeT = 5
OES_BS_TYPE_CREDIT_SELL: eOesBuySellTypeT = 6
OES_BS_TYPE_SUBSCRIPTION: eOesBuySellTypeT = 7
OES_BS_TYPE_BUY_OPEN: eOesBuySellTypeT = 11
OES_BS_TYPE_BUY_CLOSE: eOesBuySellTypeT = 12
OES_BS_TYPE_SELL_OPEN: eOesBuySellTypeT = 13
OES_BS_TYPE_SELL_CLOSE: eOesBuySellTypeT = 14
OES_BS_TYPE_COVERED_OPEN: eOesBuySellTypeT = 15
OES_BS_TYPE_COVERED_CLOSE: eOesBuySellTypeT = 16
OES_BS_TYPE_OPTION_EXERCISE: eOesBuySellTypeT = 17
OES_BS_TYPE_UNDERLYING_FREEZE: eOesBuySellTypeT = 18
OES_BS_TYPE_UNDERLYING_UNFREEZE: eOesBuySellTypeT = 19
OES_BS_TYPE_CANCEL: eOesBuySellTypeT = 30
__OES_BS_TYPE_MAX_TRADING: eOesBuySellTypeT = 31
OES_BS_TYPE_SSE_DESIGNATION: eOesBuySellTypeT = 41
OES_BS_TYPE_SSE_RECALL_DESIGNATION: eOesBuySellTypeT = 42
OES_BS_TYPE_SZSE_DESIGNATION: eOesBuySellTypeT = 43
OES_BS_TYPE_SZSE_CANCEL_DESIGNATION: eOesBuySellTypeT = 44
__OES_BS_TYPE_MAX: eOesBuySellTypeT = 45
OES_BS_TYPE_B: eOesBuySellTypeT = 1
OES_BS_TYPE_S: eOesBuySellTypeT = 2
OES_BS_TYPE_KB: eOesBuySellTypeT = 3
OES_BS_TYPE_KS: eOesBuySellTypeT = 4
OES_BS_TYPE_CB: eOesBuySellTypeT = 5
OES_BS_TYPE_CS: eOesBuySellTypeT = 6
OES_BS_TYPE_BO: eOesBuySellTypeT = 11
OES_BS_TYPE_BC: eOesBuySellTypeT = 12
OES_BS_TYPE_SO: eOesBuySellTypeT = 13
OES_BS_TYPE_SC: eOesBuySellTypeT = 14
OES_BS_TYPE_CO: eOesBuySellTypeT = 15
OES_BS_TYPE_CC: eOesBuySellTypeT = 16
OES_BS_TYPE_TE: eOesBuySellTypeT = 17
OES_BS_TYPE_UF: eOesBuySellTypeT = 18
OES_BS_TYPE_UU: eOesBuySellTypeT = 19
OES_ORD_DIR_BUY: eOesOrdDirT
OES_ORD_DIR_SELL: eOesOrdDirT = 1
__OES_ORD_DIR_MAX: eOesOrdDirT = 2
OES_ETF_TRDCNFM_TYPE_NONE: eOesEtfTrdCnfmTypeT
OES_ETF_TRDCNFM_TYPE_ETF_FIRST: eOesEtfTrdCnfmTypeT = 1
OES_ETF_TRDCNFM_TYPE_CMPOENT: eOesEtfTrdCnfmTypeT = 2
OES_ETF_TRDCNFM_TYPE_CASH: eOesEtfTrdCnfmTypeT = 3
OES_ETF_TRDCNFM_TYPE_ETF_LAST: eOesEtfTrdCnfmTypeT = 4
__OES_ETF_TRDCNFM_TYPE_MAX: eOesEtfTrdCnfmTypeT = 5
OES_ETF_SUBFLAG_FORBID_SUB: eOesEtfSubFlagT
OES_ETF_SUBFLAG_ALLOW_SUB: eOesEtfSubFlagT = 1
OES_ETF_SUBFLAG_MUST_SUB: eOesEtfSubFlagT = 2
OES_ETF_SUBFLAG_SZ_REFUND_SUB: eOesEtfSubFlagT = 3
OES_ETF_SUBFLAG_SZ_MUST_SUB: eOesEtfSubFlagT = 4
OES_ETF_SUBFLAG_OTHER_REFUND_SUB: eOesEtfSubFlagT = 5
OES_ETF_SUBFLAG_OTHER_MUST_SUB: eOesEtfSubFlagT = 6
OES_LOT_TYPE_UNDEFINE: eOesLotTypeT
OES_LOT_TYPE_FAILED: eOesLotTypeT = 1
OES_LOT_TYPE_ASSIGNMENT: eOesLotTypeT = 2
OES_LOT_TYPE_LOTTERY: eOesLotTypeT = 3
__OES_LOT_TYPE_MAX: eOesLotTypeT = 4
OES_LOT_REJ_REASON_DUPLICATE: eOesLotRejReasonT = 1
OES_LOT_REJ_REASON_INVALID_DUPLICATE: eOesLotRejReasonT = 2
OES_LOT_REJ_REASON_OFFLINE_FIRST: eOesLotRejReasonT = 3
OES_LOT_REJ_REASON_BAD_RECORD: eOesLotRejReasonT = 4
OES_LOT_REJ_REASON_UNKNOW: eOesLotRejReasonT = 5
OES_EXECTYPE_UNDEFINE: eOesExecTypeT
OES_EXECTYPE_INSERT: eOesExecTypeT = 1
OES_EXECTYPE_CONFIRMED: eOesExecTypeT = 2
OES_EXECTYPE_CANCELLED: eOesExecTypeT = 3
OES_EXECTYPE_AUTO_CANCELLED: eOesExecTypeT = 4
OES_EXECTYPE_REJECT: eOesExecTypeT = 5
OES_EXECTYPE_TRADE: eOesExecTypeT = 6
__OES_EXECTYPE_MAX: eOesExecTypeT = 7
OES_CURR_TYPE_RMB: eOesCurrTypeT
OES_CURR_TYPE_HKD: eOesCurrTypeT = 1
OES_CURR_TYPE_USD: eOesCurrTypeT = 2
__OES_CURR_TYPE_MAX: eOesCurrTypeT = 3
OES_FEE_TYPE_EXCHANGE_STAMP: eOesFeeTypeT = 1
OES_FEE_TYPE_EXCHANGE_TRANSFER: eOesFeeTypeT = 2
OES_FEE_TYPE_EXCHANGE_SETTLEMENT: eOesFeeTypeT = 3
OES_FEE_TYPE_EXCHANGE_TRADE_RULE: eOesFeeTypeT = 4
OES_FEE_TYPE_EXCHANGE_EXCHANGE: eOesFeeTypeT = 5
OES_FEE_TYPE_EXCHANGE_ADMINFER: eOesFeeTypeT = 6
OES_FEE_TYPE_EXCHANGE_OTHER: eOesFeeTypeT = 7
__OES_FEE_TYPE_EXCHANGE_MAX: eOesFeeTypeT = 8
OES_FEE_TYPE_BROKER_BACK_END: eOesFeeTypeT = 17
OES_CALC_FEE_MODE_AMOUNT: eOesCalcFeeModeT
OES_CALC_FEE_MODE_QTY: eOesCalcFeeModeT = 1
OES_CALC_FEE_MODE_ORD: eOesCalcFeeModeT = 2
OES_FUND_TRSF_DIRECT_IN: eOesFundTrsfDirectT
OES_FUND_TRSF_DIRECT_OUT: eOesFundTrsfDirectT = 1
OES_FUND_TRSF_TYPE_OES_BANK: eOesFundTrsfTypeT
OES_FUND_TRSF_TYPE_OES_COUNTER: eOesFundTrsfTypeT = 1
OES_FUND_TRSF_TYPE_COUNTER_BANK: eOesFundTrsfTypeT = 2
__OES_FUND_TRSF_TYPE_MAX: eOesFundTrsfTypeT = 3
OES_FUND_TRSF_STS_UNDECLARED: eOesFundTrsfStatusT
OES_FUND_TRSF_STS_DECLARED: eOesFundTrsfStatusT = 1
OES_FUND_TRSF_STS_WAIT_DONE: eOesFundTrsfStatusT = 2
OES_FUND_TRSF_STS_DONE: eOesFundTrsfStatusT = 3
__OES_FUND_TRSF_STS_ROLLBACK_MIN: eOesFundTrsfStatusT = 5
OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK: eOesFundTrsfStatusT = 6
OES_FUND_TRSF_STS_DECLARED_ROLLBACK: eOesFundTrsfStatusT = 7
__OES_FUND_TRSF_STS_INVALID_MIN: eOesFundTrsfStatusT = 10
OES_FUND_TRSF_STS_INVALID_OES: eOesFundTrsfStatusT = 11
OES_FUND_TRSF_STS_INVALID_COUNTER: eOesFundTrsfStatusT = 12
OES_FUND_TRSF_STS_SUSPENDED: eOesFundTrsfStatusT = 13
OES_ACCT_TYPE_NORMAL: eOesAcctTypeT
OES_ACCT_TYPE_CREDIT: eOesAcctTypeT = 1
OES_ACCT_TYPE_OPTION: eOesAcctTypeT = 2
__OES_ACCT_TYPE_MAX: eOesAcctTypeT = 3
OES_CASH_TYPE_SPOT: eOesCashTypeT
OES_CASH_TYPE_CREDIT: eOesCashTypeT = 1
OES_CASH_TYPE_OPTION: eOesCashTypeT = 2
__OES_CASH_TYPE_MAX: eOesCashTypeT = 3
OES_CASH_TYPE_CRE: eOesCashTypeT = 1
OES_CASH_TYPE_OPT: eOesCashTypeT = 2
OES_ACCT_STATUS_NORMAL: eOesAcctStatusT
OES_ACCT_STATUS_DISABLED: eOesAcctStatusT = 1
OES_ACCT_STATUS_LOCKED: eOesAcctStatusT = 2
OES_PERMIS_MARKET_ORDER: eOesTradingPermissionT = 2
OES_PERMIS_STRUCTURED_FUND: eOesTradingPermissionT = 4
OES_PERMIS_BOND_QUALIFIED_INVESTOR: eOesTradingPermissionT = 8
OES_PERMIS_XXX4: eOesTradingPermissionT = 16
OES_PERMIS_DELISTING: eOesTradingPermissionT = 32
OES_PERMIS_RISK_WARNING: eOesTradingPermissionT = 64
OES_PERMIS_SINGLE_MARKET_ETF: eOesTradingPermissionT = 128
OES_PERMIS_CROSS_BORDER_ETF: eOesTradingPermissionT = 256
OES_PERMIS_CROSS_MARKET_ETF: eOesTradingPermissionT = 512
OES_PERMIS_CURRENCY_ETF: eOesTradingPermissionT = 1024
OES_PERMIS_STOCK_PLEDGE_REPURCHASE: eOesTradingPermissionT = 2048
OES_PERMIS_PLEDGE_REPURCHASE: eOesTradingPermissionT = 4096
OES_PERMIS_GEM: eOesTradingPermissionT = 8192
OES_PERMIS_SH_HK_STOCK_CONNECT: eOesTradingPermissionT = 16384
OES_PERMIS_SZ_HK_STOCK_CONNECT: eOesTradingPermissionT = 32768
OES_PERMIS_CDR: eOesTradingPermissionT = 65536
OES_PERMIS_INNOVATION: eOesTradingPermissionT = 131072
__OES_PERMIS_ALL: eOesTradingPermissionT = -1
OES_LIMIT_BUY: eOesTradingLimitT = 2
OES_LIMIT_SELL: eOesTradingLimitT = 4
OES_LIMIT_RECALL_DESIGNATION: eOesTradingLimitT = 8
OES_LIMIT_DESIGNATION: eOesTradingLimitT = 16
OES_LIMIT_REPO: eOesTradingLimitT = 32
OES_LIMIT_REVERSE_REPO: eOesTradingLimitT = 64
OES_LIMIT_SUBSCRIPTION: eOesTradingLimitT = 128
OES_LIMIT_CREDIT_BUY: eOesTradingLimitT = 256
OES_LIMIT_CREDIT_SELL: eOesTradingLimitT = 512
__OES_LIMIT_ALL: eOesTradingLimitT = -1
OES_QUALIFICATION_PUBLIC_INVESTOR: eOesQualificationClassT
OES_QUALIFICATION_QUALIFIED_INVESTOR: eOesQualificationClassT = 1
OES_QUALIFICATION_QUALIFIED_INSTITUTIONAL: eOesQualificationClassT = 2
OES_INVESTOR_CLASS_NORMAL: eOesInvestorClassT
OES_INVESTOR_CLASS_PROFESSIONAL_A: eOesInvestorClassT = 1
OES_INVESTOR_CLASS_PROFESSIONAL_B: eOesInvestorClassT = 2
OES_INVESTOR_CLASS_PROFESSIONAL_C: eOesInvestorClassT = 3
OES_OWNER_TYPE_PERSONAL: eOesOwnerTypeT = 1
OES_OWNER_TYPE_EXCHANGE: eOesOwnerTypeT = 101
OES_OWNER_TYPE_MEMBER: eOesOwnerTypeT = 102
OES_OWNER_TYPE_INSTITUTION: eOesOwnerTypeT = 103
OES_OWNER_TYPE_PROPRIETARY: eOesOwnerTypeT = 104
OES_OWNER_TYPE_MKT_MAKER: eOesOwnerTypeT = 105
OES_OWNER_TYPE_SETTLEMENT: eOesOwnerTypeT = 106
__OES_OWNER_TYPE_MAX: eOesOwnerTypeT = 107
OES_CLIENT_TYPE_UNDEFINED: eOesClientTypeT
OES_CLIENT_TYPE_INVESTOR: eOesClientTypeT = 1
OES_CLIENT_TYPE_VIRTUAL: eOesClientTypeT = 2
OES_CLIENT_STATUS_UNACTIVATED: eOesClientStatusT
OES_CLIENT_STATUS_ACTIVATED: eOesClientStatusT = 1
OES_CLIENT_STATUS_PAUSE: eOesClientStatusT = 2
OES_CLIENT_STATUS_SUSPENDED: eOesClientStatusT = 3
OES_CLIENT_STATUS_CANCELLED: eOesClientStatusT = 4
OES_OPT_CONTRACT_TYPE_CALL: eOesOptContractTypeT
OES_OPT_CONTRACT_TYPE_PUT: eOesOptContractTypeT = 1
__OES_OPT_CONTRACT_TYPE_MAX: eOesOptContractTypeT = 2
OES_OPT_INV_LEVEL_B: eOesOptInvLevelT
OES_OPT_INV_LEVEL_L: eOesOptInvLevelT = 1
OES_OPT_INV_LEVEL_A: eOesOptInvLevelT = 2
__OES_OPT_INV_LEVEL_MAX: eOesOptInvLevelT = 3
OPEN_FLAG_TYPE_ALLOW: eOpenFlagTypeT
OPEN_FLAG_TYPE_FORBID: eOpenFlagTypeT = 1
__OPEN_FLAG_TYPE_MAX: eOpenFlagTypeT = 2
OES_OPTION_OPEN_FLAG_ALLOW: eOesOptionOpenFlagT
OES_OPTION_OPEN_FLAG_FORBID: eOesOptionOpenFlagT = 1
OES_POSITION_INVALID: eOesPositionEffT
OES_POSITION_OPEN: eOesPositionEffT = 1
OES_POSITION_CLOSE: eOesPositionEffT = 2
OES_OPTION_TYPE_E: eOesOptionTypeT
OES_OPTION_TYPE_A: eOesOptionTypeT = 1
__OES_OPTION_TYPE_MAX: eOesOptionTypeT = 2
SMSG_PROTO_BINARY: eSMsgProtocolTypeT
SMSG_PROTO_JSON: eSMsgProtocolTypeT = 1
SMSG_PROTO_FIX: eSMsgProtocolTypeT = 2
SMSG_PROTO_PROTOBUF: eSMsgProtocolTypeT = 3
__MAX_SMSG_PROTO_TYPE: eSMsgProtocolTypeT = 4
SMSG_MSGFLAG_NONE: eSMsgFlagT
SMSG_MSGFLAG_REQ: eSMsgFlagT
SMSG_MSGFLAG_RSP: eSMsgFlagT = 80
SMSG_MSGFLAG_NESTED: eSMsgFlagT = 32
SMSG_MSGFLAG_COMPRESSED: eSMsgFlagT = 128
SMSG_MSGFLAG_MASK_RSPFLAG: eSMsgFlagT = 240
SMSG_MSGFLAG_MASK_PROTOCOL: eSMsgFlagT = 15
OESMSG_ORD_NEW_ORDER: eOesMsgTypeT = 1
OESMSG_ORD_CANCEL_REQUEST: eOesMsgTypeT = 2
OESMSG_ORD_BATCH_ORDERS: eOesMsgTypeT = 3
__OESMSG_ORD_MAX: eOesMsgTypeT = 4
__OESMSG_RPT_MIN: eOesMsgTypeT = 15
OESMSG_RPT_MARKET_STATE: eOesMsgTypeT = 16
OESMSG_RPT_REPORT_SYNCHRONIZATION: eOesMsgTypeT = 17
OESMSG_RPT_BUSINESS_REJECT: eOesMsgTypeT = 18
OESMSG_RPT_ORDER_INSERT: eOesMsgTypeT = 19
OESMSG_RPT_ORDER_REPORT: eOesMsgTypeT = 20
OESMSG_RPT_TRADE_REPORT: eOesMsgTypeT = 21
OESMSG_RPT_FUND_TRSF_REJECT: eOesMsgTypeT = 22
OESMSG_RPT_FUND_TRSF_REPORT: eOesMsgTypeT = 23
OESMSG_RPT_CASH_ASSET_VARIATION: eOesMsgTypeT = 24
OESMSG_RPT_STOCK_HOLDING_VARIATION: eOesMsgTypeT = 25
OESMSG_RPT_OPTION_HOLDING_VARIATION: eOesMsgTypeT = 26
__OESMSG_RPT_MAX: eOesMsgTypeT = 27
__OESMSG_NONTRD_MIN: eOesMsgTypeT = 32
OESMSG_NONTRD_FUND_TRSF_REQ: eOesMsgTypeT = 33
OESMSG_NONTRD_CHANGE_PASSWORD: eOesMsgTypeT = 34
__OESMSG_NONTRD_MAX: eOesMsgTypeT = 35
__OESMSG_QRYMSG_MIN: eOesMsgTypeT = 47
OESMSG_QRYMSG_CLIENT_OVERVIEW: eOesMsgTypeT = 48
OESMSG_QRYMSG_ORD: eOesMsgTypeT = 49
OESMSG_QRYMSG_TRD: eOesMsgTypeT = 50
OESMSG_QRYMSG_CASH_ASSET: eOesMsgTypeT = 51
OESMSG_QRYMSG_STK_HLD: eOesMsgTypeT = 52
OESMSG_QRYMSG_OPT_HLD: eOesMsgTypeT = 53
OESMSG_QRYMSG_CUST: eOesMsgTypeT = 54
OESMSG_QRYMSG_INV_ACCT: eOesMsgTypeT = 55
OESMSG_QRYMSG_COMMISSION_RATE: eOesMsgTypeT = 56
OESMSG_QRYMSG_FUND_TRSF: eOesMsgTypeT = 57
OESMSG_QRYMSG_STOCK: eOesMsgTypeT = 58
OESMSG_QRYMSG_ETF: eOesMsgTypeT = 59
OESMSG_QRYMSG_ETF_COMPONENT: eOesMsgTypeT = 60
OESMSG_QRYMSG_OPTION: eOesMsgTypeT = 61
OESMSG_QRYMSG_ISSUE: eOesMsgTypeT = 62
OESMSG_QRYMSG_LOT_WINNING: eOesMsgTypeT = 63
OESMSG_QRYMSG_TRADING_DAY: eOesMsgTypeT = 64
OESMSG_QRYMSG_MARKET_STATE: eOesMsgTypeT = 65
OESMSG_QRYMSG_COUNTER_CASH: eOesMsgTypeT = 66
__OESMSG_QRYMSG_MAX: eOesMsgTypeT = 67
OESMSG_SESS_TRD_LOGIN: eOesMsgTypeT = 241
OESMSG_SESS_RPT_LOGIN: eOesMsgTypeT = 243
OESMSG_SESS_QRY_LOGIN: eOesMsgTypeT = 244
OESMSG_SESS_HEARTBEAT: eOesMsgTypeT = 250
OESMSG_SESS_TEST_REQUEST: eOesMsgTypeT = 251
OESMSG_SESS_LOGOUT: eOesMsgTypeT = 254
OESMSG_RPT_ORDER_REJECT: eOesMsgTypeT = 18
OES_SUB_RPT_TYPE_DEFAULT: eOesSubscribeReportTypeT
OES_SUB_RPT_TYPE_BUSINESS_REJECT: eOesSubscribeReportTypeT = 1
OES_SUB_RPT_TYPE_ORDER_INSERT: eOesSubscribeReportTypeT = 2
OES_SUB_RPT_TYPE_ORDER_REPORT: eOesSubscribeReportTypeT = 4
OES_SUB_RPT_TYPE_TRADE_REPORT: eOesSubscribeReportTypeT = 8
OES_SUB_RPT_TYPE_FUND_TRSF_REPORT: eOesSubscribeReportTypeT = 16
OES_SUB_RPT_TYPE_CASH_ASSET_VARIATION: eOesSubscribeReportTypeT = 32
OES_SUB_RPT_TYPE_HOLDING_VARIATION: eOesSubscribeReportTypeT = 64
OES_SUB_RPT_TYPE_MARKET_STATE: eOesSubscribeReportTypeT = 128
OES_SUB_RPT_TYPE_ALL: eOesSubscribeReportTypeT = 65535
__MAX_OES_SUB_RPT_TYPE: eOesSubscribeReportTypeT = 2147483647
SPK_SOCKET_PROTOCOL_TCP: eSSocketProtocolTypeT
SPK_SOCKET_PROTOCOL_IPC: eSSocketProtocolTypeT = 1
SPK_SOCKET_PROTOCOL_UDP_UCAST: eSSocketProtocolTypeT = 2
SPK_SOCKET_PROTOCOL_UDP_MCAST: eSSocketProtocolTypeT = 3
SPK_SOCKET_PROTOCOL_PGM: eSSocketProtocolTypeT = 4
SPK_SOCKET_PROTOCOL_EPGM: eSSocketProtocolTypeT = 5
__MAX_SPK_SOCKET_PROTOCOL: eSSocketProtocolTypeT = 6
GENERAL_CLI_CLUSTER_UNDEFINED: eGeneralClientClusterTypeT
GENERAL_CLI_CLUSTER_REPLICA_SET: eGeneralClientClusterTypeT = 1
GENERAL_CLI_CLUSTER_PEER_NODES: eGeneralClientClusterTypeT = 2
__MAX_GENERAL_CLI_CLUSTER_TYPE: eGeneralClientClusterTypeT = 3
GENERAL_CLI_ENCRYPT_NONE: eGeneralClientEncryptTypeT
GENERAL_CLI_ENCRYPT_MD5: eGeneralClientEncryptTypeT = 1
GENERAL_CLI_ENCRYPT_SHA: eGeneralClientEncryptTypeT = 2
GENERAL_CLI_ENCRYPT_DES: eGeneralClientEncryptTypeT = 16
GENERAL_CLI_ENCRYPT_AES: eGeneralClientEncryptTypeT = 32
GENERAL_CLI_ENCRYPT_RSA: eGeneralClientEncryptTypeT = 64
OESAPI_CHANNEL_TYPE_ORDER: eOesApiChannelTypeT = 1
OESAPI_CHANNEL_TYPE_REPORT: eOesApiChannelTypeT = 2
OESAPI_CHANNEL_TYPE_QUERY: eOesApiChannelTypeT = 3
MDS_EXCH_SSE: eMdsExchangeIdT = 1
MDS_EXCH_SZSE: eMdsExchangeIdT = 2
__MAX_MDS_EXCH: eMdsExchangeIdT = 3
__MAX_MDS_EXCH_ALIGNED4: eMdsExchangeIdT = 4
__MAX_MDS_EXCH_ALIGNED8: eMdsExchangeIdT = 8
MDS_MSGSRC_UNDEFINED: eMdsMsgSourceT
MDS_MSGSRC_EZEI_TCP: eMdsMsgSourceT = 1
MDS_MSGSRC_EZEI_UDP: eMdsMsgSourceT = 2
MDS_MSGSRC_VDE_LEVEL2: eMdsMsgSourceT = 3
MDS_MSGSRC_VDE_LEVEL1: eMdsMsgSourceT = 4
MDS_MSGSRC_SZSE_MDGW_BINARY: eMdsMsgSourceT = 5
MDS_MSGSRC_SZSE_MDGW_STEP: eMdsMsgSourceT = 6
MDS_MSGSRC_MDS_TCP: eMdsMsgSourceT = 7
MDS_MSGSRC_MDS_UDP: eMdsMsgSourceT = 8
MDS_MSGSRC_FILE_MKTDT: eMdsMsgSourceT = 9
MDS_MSGSRC_SSE_MDGW_BINARY: eMdsMsgSourceT = 10
MDS_MSGSRC_SSE_MDGW_STEP: eMdsMsgSourceT = 11
__MAX_MDS_MSGSRC: eMdsMsgSourceT = 12
MDS_MSGSRC_MDGW_BINARY: eMdsMsgSourceT = 5
MDS_MSGSRC_MDGW_STEP: eMdsMsgSourceT = 6
MDS_SECURITY_TYPE_STOCK: eMdsSecurityTypeT = 1
MDS_SECURITY_TYPE_INDEX: eMdsSecurityTypeT = 2
MDS_SECURITY_TYPE_OPTION: eMdsSecurityTypeT = 3
__MAX_MDS_SECURITY_TYPE: eMdsSecurityTypeT = 4
MDS_MD_STREAM_TYPE_INDEX: eMdsMdStreamTypeT = 1
MDS_MD_STREAM_TYPE_STOCK: eMdsMdStreamTypeT = 2
MDS_MD_STREAM_TYPE_BOND: eMdsMdStreamTypeT = 3
MDS_MD_STREAM_TYPE_FUND: eMdsMdStreamTypeT = 4
MDS_MD_STREAM_TYPE_SZSE_STOCK: eMdsMdStreamTypeT = 5
MDS_MD_STREAM_TYPE_SZSE_REPO: eMdsMdStreamTypeT = 6
MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS: eMdsMdStreamTypeT = 7
MDS_MD_STREAM_TYPE_OPTION: eMdsMdStreamTypeT = 8
MDS_MD_STREAM_TYPE_OTHERS: eMdsMdStreamTypeT = 9
__MAX_MDS_MD_STREAM_TYPE: eMdsMdStreamTypeT = 10
MDS_MD_LEVEL_0: eMdsMdLevelT
MDS_MD_LEVEL_1: eMdsMdLevelT = 1
MDS_MD_LEVEL_2: eMdsMdLevelT = 2
__MAX_MDS_MD_LEVEL: eMdsMdLevelT = 3
MDS_L2_PX_OPERATOR_ADD: eMdsL2PriceLevelOperatorT = 1
MDS_L2_PX_OPERATOR_UPDATE: eMdsL2PriceLevelOperatorT = 2
MDS_L2_PX_OPERATOR_DELETE: eMdsL2PriceLevelOperatorT = 3
__MAX_MDS_L2_PX_OPERATOR: eMdsL2PriceLevelOperatorT = 4
MDS_L2_VIRTUAL_AUCTION_SIDE_NONE: eMdsL2VirtualAuctionSideT
MDS_L2_VIRTUAL_AUCTION_SIDE_BID: eMdsL2VirtualAuctionSideT = 1
MDS_L2_VIRTUAL_AUCTION_SIDE_OFFER: eMdsL2VirtualAuctionSideT = 2
MDS_L2_TRADE_EXECTYPE_CANCELED: eMdsL2TradeExecTypeT = 52
MDS_L2_TRADE_EXECTYPE_TRADE: eMdsL2TradeExecTypeT = 70
MDS_L2_TRADE_BSFLAG_BUY: eMdsL2TradeBSFlagT = 66
MDS_L2_TRADE_BSFLAG_SELL: eMdsL2TradeBSFlagT = 83
MDS_L2_TRADE_BSFLAG_UNKNOWN: eMdsL2TradeBSFlagT = 78
MDS_L2_ORDER_SIDE_BUY: eMdsL2OrderSideT = 49
MDS_L2_ORDER_SIDE_SELL: eMdsL2OrderSideT = 50
MDS_L2_ORDER_SIDE_BORROW: eMdsL2OrderSideT = 71
MDS_L2_ORDER_SIDE_LEND: eMdsL2OrderSideT = 70
MDS_L2_ORDER_TYPE_MKT: eMdsL2OrderTypeT = 49
MDS_L2_ORDER_TYPE_LMT: eMdsL2OrderTypeT = 50
MDS_L2_ORDER_TYPE_SAMEPARTY_BEST: eMdsL2OrderTypeT = 85
MDS_CLIENT_TYPE_UNDEFINED: eMdsClientTypeT
MDS_CLIENT_TYPE_INVESTOR: eMdsClientTypeT = 1
MDS_CLIENT_TYPE_VIRTUAL: eMdsClientTypeT = 2
MDS_CLIENT_STATUS_UNACTIVATED: eMdsClientStatusT
MDS_CLIENT_STATUS_ACTIVATED: eMdsClientStatusT = 1
MDS_CLIENT_STATUS_PAUSE: eMdsClientStatusT = 2
MDS_CLIENT_STATUS_SUSPENDED: eMdsClientStatusT = 3
MDS_CLIENT_STATUS_CANCELLED: eMdsClientStatusT = 4
MDS_MSGTYPE_HEARTBEAT: eMdsMsgTypeT = 1
MDS_MSGTYPE_TEST_REQUEST: eMdsMsgTypeT = 2
MDS_MSGTYPE_LOGON: eMdsMsgTypeT = 3
MDS_MSGTYPE_LOGOUT: eMdsMsgTypeT = 4
MDS_MSGTYPE_MARKET_DATA_REQUEST: eMdsMsgTypeT = 5
MDS_MSGTYPE_COMPRESSED_PACKETS: eMdsMsgTypeT = 6
__MDS_MSGTYPE_SESSION_MAX: eMdsMsgTypeT = 7
MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH: eMdsMsgTypeT = 10
MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH: eMdsMsgTypeT = 11
MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH: eMdsMsgTypeT = 12
MDS_MSGTYPE_TRADING_SESSION_STATUS: eMdsMsgTypeT = 13
MDS_MSGTYPE_SECURITY_STATUS: eMdsMsgTypeT = 14
__MDS_MSGTYPE_L1_MAX: eMdsMsgTypeT = 15
MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT: eMdsMsgTypeT = 20
MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT: eMdsMsgTypeT = 21
MDS_MSGTYPE_L2_TRADE: eMdsMsgTypeT = 22
MDS_MSGTYPE_L2_ORDER: eMdsMsgTypeT = 23
MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL: eMdsMsgTypeT = 24
MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL: eMdsMsgTypeT = 25
MDS_MSGTYPE_L2_MARKET_OVERVIEW: eMdsMsgTypeT = 26
MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE: eMdsMsgTypeT = 27
__MDS_MSGTYPE_L2_MAX: eMdsMsgTypeT = 28
MDS_MSGTYPE_QRY_MARKET_DATA_SNAPSHOT: eMdsMsgTypeT = 80
MDS_MSGTYPE_QRY_SECURITY_STATUS: eMdsMsgTypeT = 81
MDS_MSGTYPE_QRY_TRADING_SESSION_STATUS: eMdsMsgTypeT = 82
__MDS_MSGTYPE_QRY_MAX: eMdsMsgTypeT = 83
MDS_SUB_MODE_SET: eMdsSubscribeModeT
MDS_SUB_MODE_APPEND: eMdsSubscribeModeT = 1
MDS_SUB_MODE_DELETE: eMdsSubscribeModeT = 2
__MAX_MDS_SUB_MODE: eMdsSubscribeModeT = 3
MDS_MKT_SUB_FLAG_DEFAULT: eMdsMktSubscribeFlagT
MDS_MKT_SUB_FLAG_ALL: eMdsMktSubscribeFlagT = 1
MDS_MKT_SUB_FLAG_DISABLE: eMdsMktSubscribeFlagT = 2
__MAX_MDS_MKT_SUB_FLAG: eMdsMktSubscribeFlagT = 3
MDS_TICK_TYPE_LATEST_SIMPLIFIED: eMdsSubscribedTickTypeT
MDS_TICK_TYPE_LATEST_TIMELY: eMdsSubscribedTickTypeT = 1
MDS_TICK_TYPE_ALL_INCREMENTS: eMdsSubscribedTickTypeT = 2
__MAX_MDS_TICK_TYPE: eMdsSubscribedTickTypeT = 3
MDS_TICK_EXPIRE_TYPE_NONE: eMdsSubscribedTickExpireTypeT
MDS_TICK_EXPIRE_TYPE_IMMEDIATE: eMdsSubscribedTickExpireTypeT = 1
MDS_TICK_EXPIRE_TYPE_TIMELY: eMdsSubscribedTickExpireTypeT = 2
MDS_TICK_EXPIRE_TYPE_TIMEOUT: eMdsSubscribedTickExpireTypeT = 3
__MAX_MDS_TICK_EXPIRE_TYPE: eMdsSubscribedTickExpireTypeT = 4
MDS_SUB_DATA_TYPE_DEFAULT: eMdsSubscribeDataTypeT
MDS_SUB_DATA_TYPE_L1_SNAPSHOT: eMdsSubscribeDataTypeT = 1
MDS_SUB_DATA_TYPE_L2_SNAPSHOT: eMdsSubscribeDataTypeT = 2
MDS_SUB_DATA_TYPE_L2_BEST_ORDERS: eMdsSubscribeDataTypeT = 4
MDS_SUB_DATA_TYPE_L2_TRADE: eMdsSubscribeDataTypeT = 8
MDS_SUB_DATA_TYPE_L2_ORDER: eMdsSubscribeDataTypeT = 16
MDS_SUB_DATA_TYPE_L2_VIRTUAL_AUCTION_PRICE: eMdsSubscribeDataTypeT = 32
MDS_SUB_DATA_TYPE_L2_MARKET_OVERVIEW: eMdsSubscribeDataTypeT = 64
MDS_SUB_DATA_TYPE_TRADING_SESSION_STATUS: eMdsSubscribeDataTypeT = 256
MDS_SUB_DATA_TYPE_SECURITY_STATUS: eMdsSubscribeDataTypeT = 512
MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT: eMdsSubscribeDataTypeT = 1024
MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT: eMdsSubscribeDataTypeT = 2048
MDS_SUB_DATA_TYPE_NONE: eMdsSubscribeDataTypeT = 32768
MDS_SUB_DATA_TYPE_ALL: eMdsSubscribeDataTypeT = 65535
__MAX_MDS_SUB_DATA_TYPE: eMdsSubscribeDataTypeT = 2147483647
MDS_CHANNEL_NO_DEFAULT: eMdsTickChannelNoT
MDS_CHANNEL_NO_ONE: eMdsTickChannelNoT = 1
MDS_CHANNEL_NO_TWO: eMdsTickChannelNoT = 2
MDS_CHANNEL_NO_THREE: eMdsTickChannelNoT = 4
MDS_CHANNEL_NO_FOUR: eMdsTickChannelNoT = 8
MDS_CHANNEL_NO_ALL: eMdsTickChannelNoT = 15
MDS_CHANNEL_NO_NONE: eMdsTickChannelNoT = 128
MDSAPI_CHANNEL_TYPE_TCP: eMdsApiChannelTypeT = 1
MDSAPI_CHANNEL_TYPE_UDP: eMdsApiChannelTypeT = 2
MDSAPI_CHANNEL_TYPE_QUERY: eMdsApiChannelTypeT = 3

