# noinspection PyUnresolvedReferences
import typing
if typing.TYPE_CHECKING:
    from typing import *
    # noinspection PyUnresolvedReferences
    from enum import Enum
    from .vnoes import *


def set_async_callback_exception_handler(handler: Callable[[AsyncDispatchException], None]):
    """
    set a customize exception handler for async callback in this module(pyd)
    \a handler should return True if it handles that exception,

    :note: If the return value of \a handler is not True, exception will be re-thrown.
    """
    ...


class AsyncDispatchException:
    what: str
    instance: object
    function_name: str


class _spk_struct_timespec():
    
    
    tv_sec: int
    tv_nsec: int
    
    
class _spk_struct_timezone():
    
    
    tz_minuteswest: int
    tz_dsttime: int
    
    
class _spk_struct_iovec():
    
    
    iov_base: Any
    iov_len: int
    
    
class _spk_struct_timeval32():
    
    
    tv_sec: int
    tv_usec: int
    
    
class _spk_struct_timeval64():
    
    
    tv_sec: int
    tv_usec: int
    
    
class _OesOrdReq():
    
    
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
    u64: int
    i64: int
    u32: List[int]
    i32: List[int]
    c8: str
    userInfo: "(anonymous union at include\oes_global/oes_base_model.h:1525:5)"
    __ordReqOrigSendTime: _spk_struct_timeval32
    
    
class _OesOrdCancelReq():
    
    
    clSeqNo: int
    mktId: int
    __ORD_CANCEL_BASE_INFO_filler1: List[int]
    invAcctId: str
    securityId: str
    origClSeqNo: int
    origClEnvId: str
    __ORD_CANCEL_BASE_INFO_filler2: List[int]
    origClOrdId: int
    u64: int
    i64: int
    u32: List[int]
    i32: List[int]
    c8: str
    userInfo: "(anonymous union at include\oes_global/oes_base_model.h:1541:5)"
    __ordReqOrigSendTime: _spk_struct_timeval32
    
    
class _OesOrdReject():
    
    
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
    u64: int
    i64: int
    u32: List[int]
    i32: List[int]
    c8: str
    userInfo: "(anonymous union at include\oes_global/oes_base_model.h:1557:5)"
    __ordReqOrigSendTime: _spk_struct_timeval32
    origClSeqNo: int
    origClEnvId: str
    clEnvId: str
    clientId: int
    ordDate: int
    ordTime: int
    ordRejReason: int
    __filler: int
    
    
class _OesOrdCnfm():
    
    
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
    u64: int
    i64: int
    u32: List[int]
    i32: List[int]
    c8: str
    userInfo: "(anonymous union at include\oes_global/oes_base_model.h:1595:5)"
    __ordReqOrigSendTime: _spk_struct_timeval32
    clOrdId: int
    clientId: int
    clEnvId: str
    origClEnvId: str
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
    __ordReqOrigRecvTime: _spk_struct_timeval32
    __ordReqCollectedTime: _spk_struct_timeval32
    __ordReqActualDealTime: _spk_struct_timeval32
    __ordReqProcessedTime: _spk_struct_timeval32
    __ordCnfmOrigRecvTime: _spk_struct_timeval32
    __ordCnfmCollectedTime: _spk_struct_timeval32
    __ordCnfmActualDealTime: _spk_struct_timeval32
    __ordCnfmProcessedTime: _spk_struct_timeval32
    __ordDeclareTime: _spk_struct_timeval32
    __ordDeclareDoneTime: _spk_struct_timeval32
    __pushingTime: _spk_struct_timeval32
    
    
class _OesTrdBaseInfo():
    
    
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
    __TRD_BASE_INFO_filler: List[int]
    origOrdQty: int
    pbuId: int
    branchId: int
    
    
class _OesTrdCnfm():
    
    
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
    __TRD_BASE_INFO_filler: List[int]
    origOrdQty: int
    pbuId: int
    branchId: int
    clSeqNo: int
    clientId: int
    clEnvId: str
    subSecurityType: int
    ordStatus: int
    ordType: int
    ordBuySellType: int
    securityType: int
    origOrdPrice: int
    cumAmt: int
    cumInterest: int
    cumFee: int
    u64: int
    i64: int
    u32: List[int]
    i32: List[int]
    c8: str
    userInfo: "(anonymous union at include\oes_global/oes_base_model.h:1795:5)"
    __trdCnfmOrigRecvTime: _spk_struct_timeval32
    __trdCnfmCollectedTime: _spk_struct_timeval32
    __trdCnfmActualDealTime: _spk_struct_timeval32
    __trdCnfmProcessedTime: _spk_struct_timeval32
    __pushingTime: _spk_struct_timeval32
    
    
class _OesLotWinningBaseInfo():
    
    
    invAcctId: str
    securityId: str
    mktId: int
    lotType: int
    rejReason: int
    __LOT_WINNING_BASE_INFO_filler: str
    lotDate: int
    securityName: str
    assignNum: int
    lotQty: int
    lotPrice: int
    lotAmt: int
    
    
class _OesFundTrsfBaseInfo():
    
    
    clSeqNo: int
    direct: int
    isAllotOnly: int
    __FUND_TRSF_BASE_filler: List[int]
    cashAcctId: str
    trdPasswd: str
    trsfPasswd: str
    occurAmt: int
    u64: int
    i64: int
    u32: List[int]
    i32: List[int]
    c8: str
    userInfo: "(anonymous union at include\oes_global/oes_base_model.h:1919:5)"
    
    
class _OesFundTrsfReq():
    
    
    clSeqNo: int
    direct: int
    isAllotOnly: int
    __FUND_TRSF_BASE_filler: List[int]
    cashAcctId: str
    trdPasswd: str
    trsfPasswd: str
    occurAmt: int
    u64: int
    i64: int
    u32: List[int]
    i32: List[int]
    c8: str
    userInfo: "(anonymous union at include\oes_global/oes_base_model.h:1933:5)"
    
    
class _OesFundTrsfReject():
    
    
    clSeqNo: int
    direct: int
    isAllotOnly: int
    __FUND_TRSF_BASE_filler: List[int]
    cashAcctId: str
    trdPasswd: str
    trsfPasswd: str
    occurAmt: int
    u64: int
    i64: int
    u32: List[int]
    i32: List[int]
    c8: str
    userInfo: "(anonymous union at include\oes_global/oes_base_model.h:1947:5)"
    ordDate: int
    ordTime: int
    clientId: int
    clEnvId: str
    __filler: str
    rejReason: int
    errorInfo: str
    
    
class _OesFundTrsfReport():
    
    
    clSeqNo: int
    clientId: int
    clEnvId: str
    direct: int
    cashAcctId: str
    occurAmt: int
    u64: int
    i64: int
    u32: List[int]
    i32: List[int]
    c8: str
    userInfo: "(anonymous union at include\oes_global/oes_base_model.h:1994:5)"
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
    
    
class _OesIssueBaseInfo():
    
    
    securityId: str
    mktId: int
    securityType: int
    subSecurityType: int
    isCancelAble: int
    isReApplyAble: int
    __ISSUE_BASE_filler: List[int]
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
    
    
class _OesPriceLimit():
    
    
    ceilPrice: int
    floorPrice: int
    
    
class _OesStockBaseInfo():
    
    
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
    __filter: List[int]
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
    priceLimit: List[_OesPriceLimit]
    securityName: str
    fundId: str
    
    
class _OesEtfBaseInfo():
    
    
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
    
    
class _OesEtfComponentBaseInfo():
    
    
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
    
    
class _OesOptionBaseInfo():
    
    
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
    
    
class _OesCashAssetBaseInfo():
    
    
    cashAcctId: str
    custId: str
    currType: int
    cashType: int
    cashAcctStatus: int
    isFundTrsfDisabled: int
    __CASH_ASSET_BASE_filler: List[int]
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
    
    
class _OesCustBaseInfo():
    
    
    custId: str
    custType: int
    status: int
    riskLevel: int
    originRiskLevel: int
    institutionFlag: int
    investorClass: int
    __CUST_BASE_filler1: List[int]
    branchId: int
    __CUST_BASE_filler2: int
    
    
class _OesInvAcctBaseInfo():
    
    
    invAcctId: str
    mktId: int
    acctType: int
    status: int
    ownerType: int
    optInvLevel: int
    isTradeDisabled: int
    __INV_ACCT_BASE_filler: List[int]
    limits: int
    permissions: int
    pbuId: int
    subscriptionQuota: int
    
    
class _OesStkHoldingBaseInfo():
    
    
    invAcctId: str
    securityId: str
    mktId: int
    securityType: int
    subSecurityType: int
    __HOLD_BASE_filler: List[int]
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
    
    
class _OesOptHoldingBaseInfo():
    
    
    invAcctId: str
    securityId: str
    mktId: int
    __HOLD_BASE_filler: List[int]
    hldA: int
    hldB: int
    hldC: int
    hldC2: int
    hldRA: int
    hldRB: int
    hldRC: int
    
    
class _OesMarketStateInfo():
    
    
    exchId: int
    platformId: int
    mktId: int
    mktState: int
    __filler: List[int]
    
    
class _OesTradingPermissionEntry():
    
    
    permissionNo: int
    isDisabled: int
    counterAlias: str
    __filler: List[int]
    permissionCode: int
    applicableMarkets: List[int]
    permissionMemo: str
    
    
class _OesInputSourceInfo():
    
    
    sourceIp: str
    sourceMac: str
    sourceType: int
    __filler: List[int]
    sourceDriverId: str
    
    
class _SMsgHead():
    
    
    msgFlag: int
    msgId: int
    status: int
    detailStatus: int
    msgSize: int
    
    
class _OesQryCursor():
    
    
    seqNo: int
    isEnd: str
    __filler: List[str]
    userInfo: int
    
    
class _OesQryReqHead():
    
    
    maxPageSize: int
    lastPosition: int
    
    
class _OesQryRspHead():
    
    
    itemCount: int
    lastPosition: int
    isEnd: str
    __filler: List[int]
    userInfo: int
    
    
class _OesQryOrdFilter():
    
    
    custId: str
    invAcctId: str
    mktId: int
    isUnclosedOnly: int
    clEnvId: str
    securityType: int
    bsType: int
    __filler: List[int]
    clOrdId: int
    clSeqNo: int
    startTime: int
    endTime: int
    userInfo: int
    
    
class _OesQryOrdReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryOrdFilter
    
    
class _OesQryOrdRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesOrdCnfm]
    
    
class _OesQryTrdFilter():
    
    
    custId: str
    invAcctId: str
    mktId: int
    clEnvId: str
    securityType: int
    bsType: int
    __filler: int
    clOrdId: int
    clSeqNo: int
    startTime: int
    endTime: int
    userInfo: int
    
    
class _OesQryTrdReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryTrdFilter
    
    
class _OesQryTrdRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesTrdCnfm]
    
    
class _OesQryCashAssetFilter():
    
    
    custId: str
    cashAcctId: str
    userInfo: int
    
    
class _OesCashAssetItem():
    
    
    cashAcctId: str
    custId: str
    currType: int
    cashType: int
    cashAcctStatus: int
    isFundTrsfDisabled: int
    __CASH_ASSET_BASE_filler: List[int]
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
    
    
class _OesQryCashAssetReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryCashAssetFilter
    
    
class _OesQryCashAssetRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesCashAssetItem]
    
    
class _OesCounterCashItem():
    
    
    cashAcctId: str
    custId: str
    custName: str
    bankId: str
    cashType: int
    cashAcctStatus: int
    currType: int
    isFundTrsfDisabled: int
    __filler: List[int]
    counterAvailableBal: int
    counterDrawableBal: int
    counterCashUpdateTime: int
    __reserve: List[int]
    
    
class _OesQryCounterCashReq():
    
    
    cashAcctId: str
    
    
class _OesQryCounterCashRsp():
    
    
    counterCashItem: _OesCounterCashItem
    
    
class _OesQryStkHoldingFilter():
    
    
    custId: str
    invAcctId: str
    securityId: str
    mktId: int
    securityType: int
    __filler: List[int]
    userInfo: int
    
    
class _OesStkHoldingItem():
    
    
    invAcctId: str
    securityId: str
    mktId: int
    securityType: int
    subSecurityType: int
    __HOLD_BASE_filler: List[int]
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
    
    
class _OesQryStkHoldingReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryStkHoldingFilter
    
    
class _OesQryStkHoldingRsp():
    
    
    qryHead: _OesQryRspHead
    qryItems: List[_OesStkHoldingItem]
    
    
class _OesOptHoldingItem():
    
    
    invAcctId: str
    securityId: str
    mktId: int
    __HOLD_BASE_filler: List[int]
    hldA: int
    hldB: int
    hldC: int
    hldC2: int
    hldRA: int
    hldRB: int
    hldRC: int
    
    
class _OesQryOptHoldingReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryStkHoldingFilter
    
    
class _OesQryHoldRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesOptHoldingItem]
    
    
class _OesQryCustFilter():
    
    
    custId: str
    userInfo: int
    
    
class _OesQryCustReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryCustFilter
    
    
class _OesQryCustRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesCustBaseInfo]
    
    
class _OesQryInvAcctFilter():
    
    
    custId: str
    invAcctId: str
    mktId: int
    __filler: List[int]
    userInfo: int
    
    
class _OesInvAcctItem():
    
    
    invAcctId: str
    mktId: int
    acctType: int
    status: int
    ownerType: int
    optInvLevel: int
    isTradeDisabled: int
    __INV_ACCT_BASE_filler: List[int]
    limits: int
    permissions: int
    pbuId: int
    subscriptionQuota: int
    custId: str
    
    
class _OesQryInvAcctReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryInvAcctFilter
    
    
class _OesQryInvAcctRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesInvAcctItem]
    
    
class _OesInvAcctOverview():
    
    
    invAcctId: str
    mktId: int
    acctType: int
    status: int
    ownerType: int
    optInvLevel: int
    isTradeDisabled: int
    __INV_ACCT_BASE_filler: List[int]
    limits: int
    permissions: int
    pbuId: int
    subscriptionQuota: int
    custId: str
    isValid: int
    __filler: List[int]
    trdOrdCnt: int
    nonTrdOrdCnt: int
    cancelOrdCnt: int
    oesRejectOrdCnt: int
    exchRejectOrdCnt: int
    trdCnt: int
    __reserve: int
    
    
class _OesCashAcctOverview():
    
    
    cashAcctId: str
    custId: str
    bankId: str
    isValid: int
    cashType: int
    cashAcctStatus: int
    currType: int
    isFundTrsfDisabled: int
    __filler: List[int]
    __reserve: int
    
    
class _OesCustOverview():
    
    
    custId: str
    custType: int
    status: int
    riskLevel: int
    originRiskLevel: int
    institutionFlag: int
    investorClass: int
    __CUST_BASE_filler1: List[int]
    branchId: int
    __CUST_BASE_filler2: int
    custName: str
    spotCashAcct: _OesCashAcctOverview
    creditCashAcct: _OesCashAcctOverview
    optionCashAcct: _OesCashAcctOverview
    shSpotInvAcct: _OesInvAcctOverview
    shOptionInvAcct: _OesInvAcctOverview
    szSpotInvAcct: _OesInvAcctOverview
    szOptionInvAcct: _OesInvAcctOverview
    __reserve: int
    
    
class _OesClientOverview():
    
    
    clientId: int
    clientType: int
    clientStatus: int
    isApiForbidden: int
    isBlockTrader: int
    __filler: List[int]
    logonTime: int
    clientName: str
    clientMemo: str
    sseStkPbuId: int
    sseOptPbuId: int
    sseQualificationClass: int
    __filler2: List[int]
    szseStkPbuId: int
    szseOptPbuId: int
    szseQualificationClass: int
    __filler3: List[int]
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
    custItems: List[_OesCustOverview]
    
    
class _OesQryCommissionRateFilter():
    
    
    custId: str
    mktId: int
    securityType: int
    bsType: int
    __filler: List[int]
    userInfo: int
    
    
class _OesCommissionRateItem():
    
    
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
    
    
class _OesQryCommissionRateReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryCommissionRateFilter
    
    
class _OesQryCommissionRateRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesCommissionRateItem]
    
    
class _OesQryFundTransferSerialFilter():
    
    
    custId: str
    cashAcctId: str
    clSeqNo: int
    clEnvId: str
    __filler: List[int]
    userInfo: int
    
    
class _OesQryFundTransferSerialReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryFundTransferSerialFilter
    
    
class _OesQryFundTransferSerialRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesFundTrsfReport]
    
    
class _OesQryLotWinningFilter():
    
    
    custId: str
    invAcctId: str
    mktId: int
    lotType: int
    __filler: List[int]
    startDate: int
    endDate: int
    userInfo: int
    
    
class _OesQryLotWinningReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryLotWinningFilter
    
    
class _OesQryLotWinningRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesLotWinningBaseInfo]
    
    
class _OesQryIssueFilter():
    
    
    securityId: str
    mktId: int
    __filler: List[int]
    userInfo: int
    
    
class _OesQryIssueReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryIssueFilter
    
    
class _OesQryIssueRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesIssueBaseInfo]
    
    
class _OesQryStockFilter():
    
    
    securityId: str
    mktId: int
    securityType: int
    subSecurityType: int
    __filler: List[int]
    userInfo: int
    
    
class _OesQryStockReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryStockFilter
    
    
class _OesQryStockRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesStockBaseInfo]
    
    
class _OesQryEtfFilter():
    
    
    fundId: str
    mktId: int
    __filler: List[int]
    userInfo: int
    
    
class _OesQryEtfReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryEtfFilter
    
    
class _OesQryEtfRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesEtfBaseInfo]
    
    
class _OesQryEtfComponentFilter():
    
    
    fundId: str
    userInfo: int
    
    
class _OesEtfComponentItem():
    
    
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
    
    
class _OesQryEtfComponentReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryEtfComponentFilter
    
    
class _OesQryEtfComponentRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesEtfComponentItem]
    
    
class _OesQryOptionFilter():
    
    
    securityId: str
    mktId: int
    __filler: List[int]
    userInfo: int
    
    
class _OesQryOptionReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryOptionFilter
    
    
class _OesQryOptionRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesOptionBaseInfo]
    
    
class _OesQryTradingDayRsp():
    
    
    tradingDay: int
    __filler: int
    
    
class _OesQryMarketStateFilter():
    
    
    exchId: int
    platformId: int
    __filler: List[int]
    userInfo: int
    
    
class _OesQryMarketStateReq():
    
    
    reqHead: _OesQryReqHead
    qryFilter: _OesQryMarketStateFilter
    
    
class _OesQryMarketStateRsp():
    
    
    rspHead: _OesQryRspHead
    qryItems: List[_OesMarketStateInfo]
    
    
class _OesQryReqMsg():
    
    
    qryOrd: _OesQryOrdReq
    qryTrd: _OesQryTrdReq
    qryCashAsset: _OesQryCashAssetReq
    qryStkHolding: _OesQryStkHoldingReq
    qryOptHolding: _OesQryOptHoldingReq
    qryCust: _OesQryCustReq
    qryInvAcct: _OesQryInvAcctReq
    qryComms: _OesQryCommissionRateReq
    qryFundTrsf: _OesQryFundTransferSerialReq
    qryLotWinning: _OesQryLotWinningReq
    qryIssue: _OesQryIssueReq
    qryStock: _OesQryStockReq
    qryEtf: _OesQryEtfReq
    qryEtfComponent: _OesQryEtfComponentReq
    qryOption: _OesQryOptionReq
    qryMktState: _OesQryMarketStateReq
    qryCounterCash: _OesQryCounterCashReq
    
    
class _OesQryRspMsg():
    
    
    ordRsp: _OesQryOrdRsp
    trdRsp: _OesQryTrdRsp
    cashAssetRsp: _OesQryCashAssetRsp
    stkHoldingRsp: _OesQryStkHoldingRsp
    optHoldingRsp: _OesQryHoldRsp
    custRsp: _OesQryCustRsp
    invAcctRsp: _OesQryInvAcctRsp
    commsRateRsp: _OesQryCommissionRateRsp
    fundTrsfRsp: _OesQryFundTransferSerialRsp
    lotWinningRsp: _OesQryLotWinningRsp
    issueRsp: _OesQryIssueRsp
    stockRsp: _OesQryStockRsp
    etfRsp: _OesQryEtfRsp
    etfComponentRsp: _OesQryEtfComponentRsp
    optionRsp: _OesQryOptionRsp
    tradingDay: _OesQryTradingDayRsp
    mktStateRsp: _OesQryMarketStateRsp
    clientOverview: _OesClientOverview
    counterCashRsp: _OesQryCounterCashRsp
    
    
class _OesLogonReq():
    
    
    encryptMethod: int
    heartBtInt: int
    username: str
    password: str
    applVerId: str
    clientIp: str
    clientMac: str
    clEnvId: str
    sourceType: int
    __protocolHints: int
    __filler: List[int]
    lastInMsgSeq: int
    lastOutMsgSeq: int
    clientDriverId: str
    
    
class _OesLogonRsp():
    
    
    encryptMethod: int
    heartBtInt: int
    username: str
    applVerId: str
    minVerId: str
    hostNum: int
    isLeader: int
    leaderHostNum: int
    clEnvId: str
    clientType: int
    clientStatus: int
    __protocolHints: int
    __filler: int
    lastInMsgSeq: int
    lastOutMsgSeq: int
    
    
class _OesReportSynchronizationReq():
    
    
    lastRptSeqNum: int
    subscribeEnvId: str
    __filler: List[int]
    subscribeRptTypes: int
    
    
class _OesReportSynchronizationRsp():
    
    
    lastRptSeqNum: int
    subscribeEnvId: str
    __filler: List[int]
    subscribeRptTypes: int
    
    
class _OesTestRequestReq():
    
    
    testReqId: str
    sendTime: str
    __filler: str
    
    
class _OesTestRequestRsp():
    
    
    testReqId: str
    origSendTime: str
    __filler1: str
    respTime: str
    __filler2: str
    __recvTime: _spk_struct_timeval32
    __collectedTime: _spk_struct_timeval32
    __pushingTime: _spk_struct_timeval32
    
    
class _OesChangePasswordReq():
    
    
    encryptMethod: int
    __filler: int
    username: str
    u64: int
    i64: int
    u32: List[int]
    i32: List[int]
    c8: str
    userInfo: "(anonymous union at include\oes_global/oes_packets.h:510:5)"
    oldPassword: str
    newPassword: str
    
    
class _OesChangePasswordRsp():
    
    
    encryptMethod: int
    __filler: int
    username: str
    u64: int
    i64: int
    u32: List[int]
    i32: List[int]
    c8: str
    userInfo: "(anonymous union at include\oes_global/oes_packets.h:547:5)"
    clientId: int
    clEnvId: str
    __filler2: str
    transDate: int
    transTime: int
    rejReason: int
    
    
class _OesBatchOrdersHead():
    
    
    itemCount: int
    __filler: int
    
    
class _OesBatchOrdersReq():
    
    
    batchHead: _OesBatchOrdersHead
    items: List[_OesOrdReq]
    
    
class _OesRptMsgHead():
    
    
    rptSeqNum: int
    rptMsgType: int
    execType: int
    bodyLength: int
    ordRejReason: int
    
    
class _OesRptMsgBody():
    
    
    ordInsertRsp: _OesOrdCnfm
    ordRejectRsp: _OesOrdReject
    ordCnfm: _OesOrdCnfm
    trdCnfm: _OesTrdCnfm
    fundTrsfRejectRsp: _OesFundTrsfReject
    fundTrsfCnfm: _OesFundTrsfReport
    cashAssetRpt: _OesCashAssetItem
    stkHoldingRpt: _OesStkHoldingItem
    optHoldingRpt: _OesOptHoldingItem
    
    
class _OesRptMsg():
    
    
    rptHead: _OesRptMsgHead
    rptBody: _OesRptMsgBody
    
    
class _OesReqMsgBody():
    
    
    ordReq: _OesOrdReq
    ordCancelReq: _OesOrdCancelReq
    batchOrdersReq: _OesBatchOrdersReq
    fundTrsfReq: _OesFundTrsfReq
    changePasswordReq: _OesChangePasswordReq
    testRequestReq: _OesTestRequestReq
    rptSyncReq: _OesReportSynchronizationReq
    logonReq: _OesLogonReq
    
    
class _OesRspMsgBody():
    
    
    rptMsg: _OesRptMsg
    mktStateRpt: _OesMarketStateInfo
    changePasswordRsp: _OesChangePasswordRsp
    testRequestRsp: _OesTestRequestRsp
    reportSynchronizationRsp: _OesReportSynchronizationRsp
    logonRsp: _OesLogonRsp
    
    
class _SErrMsg():
    
    
    __index: int
    MODULE: int
    CODE: int
    __errCode: int
    __msgSize: int
    MSG: str
    
    
class _SDataBuffer():
    
    
    dataSize: int
    bufSize: int
    buffer: str
    __ref: Any
    
    
class _SDataBufferVar():
    
    
    dataSize: int
    bufSize: int
    buffer: str
    __ref: Any
    
    
class _SSocketUriInfo():
    
    
    uri: str
    
    
class _SSocketIpPortInfo():
    
    
    port: int
    ip: str
    
    
class _SSocketChannelInfo():
    
    
    socketFd: int
    __socket_fd_filler: int
    remotePort: int
    protocolType: int
    _isNetByteOrder: int
    _isBroken: int
    _isSendBroken: int
    remoteAddr: str
    
    
class _SSocketOptionConfig():
    
    
    soRcvbuf: int
    soSndbuf: int
    tcpNodelay: str
    quickAck: str
    mcastTtlNum: str
    mcastLoopbackDisabled: str
    soBacklog: int
    connTimeoutMs: int
    keepIdle: int
    keepIntvl: int
    keepalive: str
    keepCnt: str
    __filler: List[str]
    localSendingPort: int
    localSendingIp: str
    mcastInterfaceIp: str
    
    
class _SGeneralClientChannel():
    
    
    socketFd: int
    __socket_fd_filler: int
    heartBtInt: int
    testReqInt: int
    protocolType: int
    remoteHostNum: int
    remoteIsLeader: int
    leaderHostNum: int
    __filler1: List[int]
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
    lastRecvTime: timeval
    channel: _SSocketChannelInfo
    nextOutMsgSeq: int
    lastOutMsgSeq: int
    lastSendTime: timeval
    senderCompId: str
    targetCompId: str
    __magicNumber: int
    __magicSize: int
    __channelType: int
    __clEnvId: str
    __groupFlag: int
    __protocolHints: int
    __filler: List[int]
    buf: str
    i8: List[str]
    u8: List[int]
    i16: List[int]
    u16: List[int]
    i32: List[int]
    u32: List[int]
    i64: List[int]
    u64: List[int]
    ptr: List[Any]
    __padding: str
    __reserveData: "(anonymous union at include\sutil/net/spk_general_client_define.h:181:5)"
    __extData: "(anonymous union at include\sutil/net/spk_general_client_define.h:197:5)"
    
    
class _SGeneralClientChannelGroup():
    
    
    channelCount: int
    __customFlag: int
    channelList: List[_SGeneralClientChannel]
    __maxFd: int
    __groupFlag: int
    __filler: List[int]
    __fdSet: fd_set
    
    
class _SGeneralClientAddrInfo():
    
    
    uri: str
    targetCompId: str
    username: str
    password: str
    hostNum: int
    __filler: List[int]
    
    
class _SGeneralClientRemoteCfg():
    
    
    addrCnt: int
    heartBtInt: int
    clusterType: int
    clEnvId: str
    __filler: List[int]
    senderCompId: str
    targetCompId: str
    username: str
    password: str
    addrList: List[_SGeneralClientAddrInfo]
    socketOpt: _SSocketOptionConfig
    
    
class _OesApiSubscribeInfo():
    
    
    clEnvId: str
    __filler: List[int]
    rptTypes: int
    
    
class _OesApiClientCfg():
    
    
    ordChannelCfg: _SGeneralClientRemoteCfg
    rptChannelCfg: _SGeneralClientRemoteCfg
    qryChannelCfg: _SGeneralClientRemoteCfg
    subscribeInfo: _OesApiSubscribeInfo
    
    
class _OesApiClientEnv():
    
    
    ordChannel: _SGeneralClientChannel
    rptChannel: _SGeneralClientChannel
    qryChannel: _SGeneralClientChannel
    
    
class _MdsTradingSessionStatusMsg():
    
    
    exchId: int
    securityType: int
    __isRepeated: str
    __filler1: int
    tradeDate: int
    updateTime: int
    __exchSendingTime: int
    __mdsRecvTime: int
    TotNoRelatedSym: int
    TradingSessionID: str
    __filler3: List[int]
    __dataVersion: int
    __origTickSeq: int
    __origNetTime: _spk_struct_timeval32
    __recvTime: _spk_struct_timeval32
    __collectedTime: _spk_struct_timeval32
    __processedTime: _spk_struct_timeval32
    __pushingTime: _spk_struct_timeval32
    
    
class _MdsSecurityStatusMsg():
    
    
    exchId: int
    securityType: int
    __isRepeated: str
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
    switchFlag: int
    switchStatus: int
    switches: List["(anonymous struct at include\mds_global/mds_base_model.h:512:5)"]
    __origNetTime: _spk_struct_timeval32
    __recvTime: _spk_struct_timeval32
    __collectedTime: _spk_struct_timeval32
    __processedTime: _spk_struct_timeval32
    __pushingTime: _spk_struct_timeval32
    
    
class _MdsPriceLevelEntry():
    
    
    Price: int
    NumberOfOrders: int
    OrderQty: int
    
    
class _MdsMktDataSnapshotHead():
    
    
    exchId: int
    securityType: int
    __isRepeated: str
    __origMdSource: int
    tradeDate: int
    updateTime: int
    instrId: int
    bodyLength: int
    mdStreamType: int
    __channelNo: int
    __dataVersion: int
    __origTickSeq: int
    __origNetTime: _spk_struct_timeval32
    __recvTime: _spk_struct_timeval32
    __collectedTime: _spk_struct_timeval32
    __processedTime: _spk_struct_timeval32
    __pushingTime: _spk_struct_timeval32
    
    
class _MdsIndexSnapshotBody():
    
    
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
    
    
class _MdsStockSnapshotBody():
    
    
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
    BidLevels: List[_MdsPriceLevelEntry]
    OfferLevels: List[_MdsPriceLevelEntry]
    
    
class _MdsL1SnapshotBody():
    
    
    stock: _MdsStockSnapshotBody
    option: _MdsStockSnapshotBody
    index: _MdsIndexSnapshotBody
    
    
class _MdsL2StockSnapshotBody():
    
    
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
    BidLevels: List[_MdsPriceLevelEntry]
    OfferLevels: List[_MdsPriceLevelEntry]
    
    
class _MdsL2StockSnapshotIncremental():
    
    
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
    __filler1: List[int]
    BestOfferPrice: int
    HasContainedBestOfferLevel: int
    NoOfferLevel: int
    __filler2: List[int]
    PriceLevelOperator: List[int]
    PriceLevels: List[_MdsPriceLevelEntry]
    
    
class _MdsL2BestOrdersSnapshotBody():
    
    
    SecurityID: str
    __filler: List[int]
    NoBidOrders: int
    NoOfferOrders: int
    TotalVolumeTraded: int
    BestBidPrice: int
    BestOfferPrice: int
    BidOrderQty: List[int]
    OfferOrderQty: List[int]
    
    
class _MdsL2BestOrdersSnapshotIncremental():
    
    
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
    OperatorEntryID: List[str]
    OrderQty: List[int]
    
    
class _MdsL2VirtualAuctionPrice():
    
    
    SecurityID: str
    LeavesSide: int
    __filler: List[int]
    Price: int
    VirtualAuctionQty: int
    LeavesQty: int
    
    
class _MdsL2MarketOverview():
    
    
    OrigDate: int
    OrigTime: int
    __exchSendingTime: int
    __mdsRecvTime: int
    
    
class _MdsL2SnapshotBody():
    
    
    l2Stock: _MdsL2StockSnapshotBody
    l2StockIncremental: _MdsL2StockSnapshotIncremental
    l2BestOrders: _MdsL2BestOrdersSnapshotBody
    l2BestOrdersIncremental: _MdsL2BestOrdersSnapshotIncremental
    index: _MdsIndexSnapshotBody
    l2VirtualAuctionPrice: _MdsL2VirtualAuctionPrice
    l2MarketOverview: _MdsL2MarketOverview
    
    
class _MdsMktDataSnapshot():
    
    
    head: _MdsMktDataSnapshotHead
    l2Stock: _MdsL2StockSnapshotBody
    l2StockIncremental: _MdsL2StockSnapshotIncremental
    l2BestOrders: _MdsL2BestOrdersSnapshotBody
    l2BestOrdersIncremental: _MdsL2BestOrdersSnapshotIncremental
    stock: _MdsStockSnapshotBody
    option: _MdsStockSnapshotBody
    index: _MdsIndexSnapshotBody
    l2VirtualAuctionPrice: _MdsL2VirtualAuctionPrice
    l2MarketOverview: _MdsL2MarketOverview
    
    
class _MdsL2Trade():
    
    
    exchId: int
    securityType: int
    __isRepeated: str
    __filler1: int
    tradeDate: int
    TransactTime: int
    instrId: int
    ChannelNo: int
    ApplSeqNum: int
    SecurityID: str
    ExecType: str
    TradeBSFlag: str
    __filler3: List[int]
    __channelNo: int
    __origTickSeq: int
    TradePrice: int
    TradeQty: int
    TradeMoney: int
    BidApplSeqNum: int
    OfferApplSeqNum: int
    __origNetTime: _spk_struct_timeval32
    __recvTime: _spk_struct_timeval32
    __collectedTime: _spk_struct_timeval32
    __processedTime: _spk_struct_timeval32
    __pushingTime: _spk_struct_timeval32
    
    
class _MdsL2Order():
    
    
    exchId: int
    securityType: int
    __isRepeated: str
    __filler1: int
    tradeDate: int
    TransactTime: int
    instrId: int
    ChannelNo: int
    ApplSeqNum: int
    SecurityID: str
    Side: str
    OrderType: str
    __filler3: List[int]
    __channelNo: int
    __origTickSeq: int
    Price: int
    OrderQty: int
    __origNetTime: _spk_struct_timeval32
    __recvTime: _spk_struct_timeval32
    __collectedTime: _spk_struct_timeval32
    __processedTime: _spk_struct_timeval32
    __pushingTime: _spk_struct_timeval32
    
    
class _MdsL2TickLost():
    
    
    exchId: int
    __filler3: List[int]
    tradeDate: int
    lostTime: int
    channelNo: int
    beginApplSeqNum: int
    endApplSeqNum: int
    __origTickSeq: int
    
    
class _MdsQryMktDataSnapshotReq():
    
    
    exchId: int
    securityType: int
    __filler: List[int]
    instrId: int
    
    
class _MdsQryTrdSessionStatusReq():
    
    
    exchId: int
    securityType: int
    __filler: List[int]
    
    
class _MdsLogonReq():
    
    
    encryptMethod: int
    heartBtInt: int
    username: str
    password: str
    applVerId: str
    
    
class _MdsLogonRsp():
    
    
    encryptMethod: int
    heartBtInt: int
    username: str
    applVerId: str
    minVerId: str
    hostNum: int
    isLeader: int
    leaderHostNum: int
    __filler: List[int]
    
    
class _MdsMktDataRequestEntry():
    
    
    exchId: int
    securityType: int
    __filler: List[int]
    instrId: int
    
    
class _MdsMktDataRequestReq():
    
    
    subMode: int
    tickType: int
    sseStockFlag: str
    sseIndexFlag: str
    sseOptionFlag: str
    szseStockFlag: str
    szseIndexFlag: str
    szseOptionFlag: str
    isRequireInitialMktData: int
    __channelNos: int
    tickExpireType: int
    __filler: int
    dataTypes: int
    beginTime: int
    subSecurityCnt: int
    
    
class _MdsMktDataRequestReqBuf():
    
    
    mktDataRequestReq: _MdsMktDataRequestReq
    entries: List[_MdsMktDataRequestEntry]
    
    
class _MdsMktDataRequestRsp():
    
    
    subMode: int
    tickType: int
    isRequireInitialMktData: int
    __channelNos: int
    tickExpireType: int
    __filler: List[int]
    dataTypes: int
    beginTime: int
    sseStockSubscribed: int
    sseIndexSubscribed: int
    sseOptionSubscribed: int
    szseStockSubscribed: int
    szseIndexSubscribed: int
    szseOptionSubscribed: int
    
    
class _MdsTestRequestReq():
    
    
    testReqId: str
    sendTime: str
    __filler: str
    
    
class _MdsTestRequestRsp():
    
    
    testReqId: str
    origSendTime: str
    __filler1: str
    respTime: str
    __filler2: str
    __recvTime: _spk_struct_timeval32
    __collectedTime: _spk_struct_timeval32
    __pushingTime: _spk_struct_timeval32
    
    
class _MdsMktReqMsgBody():
    
    
    wholeMktDataReqBuf: _MdsMktDataRequestReqBuf
    mktDataRequestReq: _MdsMktDataRequestReq
    testRequestReq: _MdsTestRequestReq
    logonReq: _MdsLogonReq
    qryMktDataSnapshotReq: _MdsQryMktDataSnapshotReq
    qrySecurityStatusReq: _MdsQryMktDataSnapshotReq
    qryTrdSessionStatusReq: _MdsQryTrdSessionStatusReq
    
    
class _MdsMktRspMsgBody():
    
    
    mktDataRequestRsp: _MdsMktDataRequestRsp
    testRequestRsp: _MdsTestRequestRsp
    logonRsp: _MdsLogonRsp
    mktDataSnapshot: _MdsMktDataSnapshot
    trade: _MdsL2Trade
    order: _MdsL2Order
    tickLost: _MdsL2TickLost
    trdSessionStatus: _MdsTradingSessionStatusMsg
    securityStatus: _MdsSecurityStatusMsg
    
    
class _MdsUdpPktHead():
    
    
    msgCnt: int
    pktSiz: int
    pktSeq: int
    
    
class _MdsApiClientCfg():
    
    
    tcpChannelCfg: _SGeneralClientRemoteCfg
    qryChannelCfg: _SGeneralClientRemoteCfg
    udpL1ChannelCfg: _SGeneralClientRemoteCfg
    udpL2ChannelCfg: _SGeneralClientRemoteCfg
    udpTradeChannelCfg: _SGeneralClientRemoteCfg
    udpOrderChannelCfg: _SGeneralClientRemoteCfg
    subscribeInfo: _MdsMktDataRequestReqBuf
    
    
class _MdsApiClientEnv():
    
    
    tcpChannel: _SGeneralClientChannel
    qryChannel: _SGeneralClientChannel
    udpL1Channel: _SGeneralClientChannel
    udpL2Channel: _SGeneralClientChannel
    udpTradeChannel: _SGeneralClientChannel
    udpOrderChannel: _SGeneralClientChannel
    udpChannelGroup: _SGeneralClientChannelGroup
    
    
class _eOesExchangeId(Enum):
    OES_EXCH_UNDEFINE: _eOesExchangeId
    OES_EXCH_SSE: _eOesExchangeId
    OES_EXCH_SZSE: _eOesExchangeId
    __MAX_OES_EXCH: _eOesExchangeId
    OES_EXCHANGE_TYPE_SSE: _eOesExchangeId
    OES_EXCHANGE_TYPE_SZSE: _eOesExchangeId
class _eOesMarketId(Enum):
    OES_MKT_UNDEFINE: _eOesMarketId
    OES_MKT_SH_ASHARE: _eOesMarketId
    OES_MKT_SZ_ASHARE: _eOesMarketId
    OES_MKT_SH_OPTION: _eOesMarketId
    __OES_MKT_ID_MAX: _eOesMarketId
    OES_MKT_ID_UNDEFINE: _eOesMarketId
    OES_MKT_ID_SH_A: _eOesMarketId
    OES_MKT_ID_SZ_A: _eOesMarketId
    OES_MKT_ID_SH_OPT: _eOesMarketId
    __OES_MKT_ID_MAX_ALIGNED4: _eOesMarketId
    __OES_MKT_ID_MAX_ALIGNED8: _eOesMarketId
class _eOesPlatformId(Enum):
    OES_PLATFORM_UNDEFINE: _eOesPlatformId
    OES_PLATFORM_CASH_AUCTION: _eOesPlatformId
    OES_PLATFORM_FINANCIAL_SERVICES: _eOesPlatformId
    OES_PLATFORM_NON_TRADE: _eOesPlatformId
    OES_PLATFORM_DERIVATIVE_AUCTION: _eOesPlatformId
    __OES_PLATFORM_ID_MAX: _eOesPlatformId
    __OES_PLATFORM_ACTIVE_MAX: _eOesPlatformId
class _eOesMarketStatus(Enum):
    OES_MKT_STATE_UNDEFINE: _eOesMarketStatus
    OES_MKT_STATE_PRE_OPEN: _eOesMarketStatus
    OES_MKT_STATE_OPEN_UP_COMING: _eOesMarketStatus
    OES_MKT_STATE_OPEN: _eOesMarketStatus
    OES_MKT_STATE_HALT: _eOesMarketStatus
    OES_MKT_STATE_CLOSE: _eOesMarketStatus
    __OES_MKT_STATE_MAX: _eOesMarketStatus
class _eOesTrdSessType(Enum):
    OES_TRD_SESS_TYPE_O: _eOesTrdSessType
    OES_TRD_SESS_TYPE_T: _eOesTrdSessType
    OES_TRD_SESS_TYPE_C: _eOesTrdSessType
    __OES_TRD_SESS_TYPE_MAX: _eOesTrdSessType
class _eOesSecurityType(Enum):
    OES_SECURITY_TYPE_UNDEFINE: _eOesSecurityType
    OES_SECURITY_TYPE_STOCK: _eOesSecurityType
    OES_SECURITY_TYPE_BOND: _eOesSecurityType
    OES_SECURITY_TYPE_ETF: _eOesSecurityType
    OES_SECURITY_TYPE_FUND: _eOesSecurityType
    OES_SECURITY_TYPE_OPTION: _eOesSecurityType
    __OES_SECURITY_TYPE_MAX: _eOesSecurityType
    __OES_SECURITY_TYPE_NOT_SUPPORT: _eOesSecurityType
class _eOesSubSecurityType(Enum):
    OES_SUB_SECURITY_TYPE_UNDEFINE: _eOesSubSecurityType
    __OES_SUB_SECURITY_TYPE_STOCK_MIN: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_STOCK_ASH: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_STOCK_SME: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_STOCK_GEM: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_STOCK_CDR: _eOesSubSecurityType
    __OES_SUB_SECURITY_TYPE_STOCK_MAX: _eOesSubSecurityType
    __OES_SUB_SECURITY_TYPE_BOND_MIN: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_BOND_GBF: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_BOND_CBF: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_BOND_CPF: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_BOND_CCF: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_BOND_FBF: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_BOND_PRP: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_BOND_STD: _eOesSubSecurityType
    __OES_SUB_SECURITY_TYPE_BOND_MAX: _eOesSubSecurityType
    __OES_SUB_SECURITY_TYPE_ETF_MIN: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_ETF_SINGLE_MKT: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_ETF_CROSS_MKT: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_ETF_BOND: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_ETF_CURRENCY: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_ETF_CROSS_BORDER: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_ETF_GOLD: _eOesSubSecurityType
    __OES_SUB_SECURITY_TYPE_ETF_MAX: _eOesSubSecurityType
    __OES_SUB_SECURITY_TYPE_FUND_MIN: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_FUND_LOF: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_FUND_CEF: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_FUND_OEF: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_FUND_GRADED: _eOesSubSecurityType
    __OES_SUB_SECURITY_TYPE_FUND_MAX: _eOesSubSecurityType
    __OES_SUB_SECURITY_TYPE_OPTION_MIN: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_OPTION_STOCK: _eOesSubSecurityType
    OES_SUB_SECURITY_TYPE_OPTION_ETF: _eOesSubSecurityType
    __OES_SUB_SECURITY_TYPE_OPTION_MAX: _eOesSubSecurityType
    __OES_SUB_SECURITY_TYPE_MAX: _eOesSubSecurityType
class _eOesSecurityLevel(Enum):
    OES_SECURITY_LEVEL_UNDEFINE: _eOesSecurityLevel
    OES_SECURITY_LEVEL_N: _eOesSecurityLevel
    OES_SECURITY_LEVEL_XST: _eOesSecurityLevel
    OES_SECURITY_LEVEL_ST: _eOesSecurityLevel
    OES_SECURITY_LEVEL_P: _eOesSecurityLevel
    OES_SECURITY_LEVEL_T: _eOesSecurityLevel
    OES_SECURITY_LEVEL_U: _eOesSecurityLevel
    OES_SECURITY_LEVEL_B: _eOesSecurityLevel
    __OES_SECURITY_LEVEL_MAX: _eOesSecurityLevel
class _eOesSecurityRiskLevel(Enum):
    OES_RISK_LEVEL_VERY_LOW: _eOesSecurityRiskLevel
    OES_RISK_LEVEL_LOW: _eOesSecurityRiskLevel
    OES_RISK_LEVEL_MEDIUM_LOW: _eOesSecurityRiskLevel
    OES_RISK_LEVEL_MEDIUM: _eOesSecurityRiskLevel
    OES_RISK_LEVEL_MEDIUM_HIGH: _eOesSecurityRiskLevel
    OES_RISK_LEVEL_HIGH: _eOesSecurityRiskLevel
    OES_RISK_LEVEL_VERY_HIGH: _eOesSecurityRiskLevel
    __OES_RISK_LEVEL_MAX: _eOesSecurityRiskLevel
class _eOesSecuritySuspFlag(Enum):
    OES_SUSPFLAG_NONE: _eOesSecuritySuspFlag
    OES_SUSPFLAG_EXCHANGE: _eOesSecuritySuspFlag
    OES_SUSPFLAG_BROKER: _eOesSecuritySuspFlag
    __OES_SUSPFLAG_OTHER: _eOesSecuritySuspFlag
class _eOesOrdStatus(Enum):
    OES_ORD_STATUS_UNDEFINE: _eOesOrdStatus
    OES_ORD_STATUS_NEW: _eOesOrdStatus
    OES_ORD_STATUS_DECLARED: _eOesOrdStatus
    OES_ORD_STATUS_PARTIALLY_FILLED: _eOesOrdStatus
    __OES_ORD_STATUS_FINAL_MIN: _eOesOrdStatus
    OES_ORD_STATUS_CANCEL_DONE: _eOesOrdStatus
    OES_ORD_STATUS_PARTIALLY_CANCELED: _eOesOrdStatus
    OES_ORD_STATUS_CANCELED: _eOesOrdStatus
    OES_ORD_STATUS_FILLED: _eOesOrdStatus
    __OES_ORD_STATUS_VALID_MAX: _eOesOrdStatus
    __OES_ORD_STATUS_INVALID_MIN: _eOesOrdStatus
    OES_ORD_STATUS_INVALID_OES: _eOesOrdStatus
    OES_ORD_STATUS_INVALID_SH_F: _eOesOrdStatus
    OES_ORD_STATUS_INVALID_SH_E: _eOesOrdStatus
    OES_ORD_STATUS_INVALID_SH_COMM: _eOesOrdStatus
    OES_ORD_STATUS_INVALID_SZ_F: _eOesOrdStatus
    OES_ORD_STATUS_INVALID_SZ_E: _eOesOrdStatus
    OES_ORD_STATUS_INVALID_SZ_REJECT: _eOesOrdStatus
    OES_ORD_STATUS_INVALID_SZ_TRY_AGAIN: _eOesOrdStatus
    __OES_ORD_STATUS_INVALID_MAX: _eOesOrdStatus
    OES_ORD_STATUS_NORMAL: _eOesOrdStatus
    OES_ORD_STATUS_DECLARING: _eOesOrdStatus
    __OES_ORD_STATUS_INVALID_OES: _eOesOrdStatus
class _eOesOrdType(Enum):
    OES_ORD_TYPE_LMT: _eOesOrdType
    OES_ORD_TYPE_LMT_FOK: _eOesOrdType
    __OES_ORD_TYPE_LMT_MAX: _eOesOrdType
    OES_ORD_TYPE_MTL_BEST_5: _eOesOrdType
    OES_ORD_TYPE_MTL_BEST: _eOesOrdType
    OES_ORD_TYPE_MTL_SAMEPARTY_BEST: _eOesOrdType
    __OES_ORD_TYPE_MTL_MAX: _eOesOrdType
    OES_ORD_TYPE_FAK_BEST_5: _eOesOrdType
    OES_ORD_TYPE_FAK: _eOesOrdType
    __OES_ORD_TYPE_FAK_MAX: _eOesOrdType
    OES_ORD_TYPE_FOK: _eOesOrdType
    __OES_ORD_TYPE_FOK_MAX: _eOesOrdType
    __OES_ORD_TYPE_MAX: _eOesOrdType
class _eOesOrdTypeSh(Enum):
    OES_ORD_TYPE_SH_LMT: _eOesOrdTypeSh
    OES_ORD_TYPE_SH_MTL_BEST_5: _eOesOrdTypeSh
    OES_ORD_TYPE_SH_FAK_BEST_5: _eOesOrdTypeSh
    OES_ORD_TYPE_SH_LMT_FOK: _eOesOrdTypeSh
    OES_ORD_TYPE_SH_FOK: _eOesOrdTypeSh
class _eOesOrdTypeSz(Enum):
    OES_ORD_TYPE_SZ_LMT: _eOesOrdTypeSz
    OES_ORD_TYPE_SZ_MTL_BEST: _eOesOrdTypeSz
    OES_ORD_TYPE_SZ_MTL_SAMEPARTY_BEST: _eOesOrdTypeSz
    OES_ORD_TYPE_SZ_FAK_BEST_5: _eOesOrdTypeSz
    OES_ORD_TYPE_SZ_FAK: _eOesOrdTypeSz
    OES_ORD_TYPE_SZ_FOK: _eOesOrdTypeSz
    OES_ORD_TYPE_SZ_LMT_FOK: _eOesOrdTypeSz
class _eOesBuySellType(Enum):
    OES_BS_TYPE_UNDEFINE: _eOesBuySellType
    OES_BS_TYPE_BUY: _eOesBuySellType
    OES_BS_TYPE_SELL: _eOesBuySellType
    OES_BS_TYPE_CREATION: _eOesBuySellType
    OES_BS_TYPE_REDEMPTION: _eOesBuySellType
    OES_BS_TYPE_CREDIT_BUY: _eOesBuySellType
    OES_BS_TYPE_CREDIT_SELL: _eOesBuySellType
    OES_BS_TYPE_SUBSCRIPTION: _eOesBuySellType
    OES_BS_TYPE_BUY_OPEN: _eOesBuySellType
    OES_BS_TYPE_BUY_CLOSE: _eOesBuySellType
    OES_BS_TYPE_SELL_OPEN: _eOesBuySellType
    OES_BS_TYPE_SELL_CLOSE: _eOesBuySellType
    OES_BS_TYPE_COVERED_OPEN: _eOesBuySellType
    OES_BS_TYPE_COVERED_CLOSE: _eOesBuySellType
    OES_BS_TYPE_OPTION_EXERCISE: _eOesBuySellType
    OES_BS_TYPE_UNDERLYING_FREEZE: _eOesBuySellType
    OES_BS_TYPE_UNDERLYING_UNFREEZE: _eOesBuySellType
    OES_BS_TYPE_CANCEL: _eOesBuySellType
    __OES_BS_TYPE_MAX_TRADING: _eOesBuySellType
    OES_BS_TYPE_SSE_DESIGNATION: _eOesBuySellType
    OES_BS_TYPE_SSE_RECALL_DESIGNATION: _eOesBuySellType
    OES_BS_TYPE_SZSE_DESIGNATION: _eOesBuySellType
    OES_BS_TYPE_SZSE_CANCEL_DESIGNATION: _eOesBuySellType
    __OES_BS_TYPE_MAX: _eOesBuySellType
    OES_BS_TYPE_B: _eOesBuySellType
    OES_BS_TYPE_S: _eOesBuySellType
    OES_BS_TYPE_KB: _eOesBuySellType
    OES_BS_TYPE_KS: _eOesBuySellType
    OES_BS_TYPE_CB: _eOesBuySellType
    OES_BS_TYPE_CS: _eOesBuySellType
    OES_BS_TYPE_BO: _eOesBuySellType
    OES_BS_TYPE_BC: _eOesBuySellType
    OES_BS_TYPE_SO: _eOesBuySellType
    OES_BS_TYPE_SC: _eOesBuySellType
    OES_BS_TYPE_CO: _eOesBuySellType
    OES_BS_TYPE_CC: _eOesBuySellType
    OES_BS_TYPE_TE: _eOesBuySellType
    OES_BS_TYPE_UF: _eOesBuySellType
    OES_BS_TYPE_UU: _eOesBuySellType
class _eOesOrdDir(Enum):
    OES_ORD_DIR_BUY: _eOesOrdDir
    OES_ORD_DIR_SELL: _eOesOrdDir
    __OES_ORD_DIR_MAX: _eOesOrdDir
class _eOesEtfTrdCnfmType(Enum):
    OES_ETF_TRDCNFM_TYPE_NONE: _eOesEtfTrdCnfmType
    OES_ETF_TRDCNFM_TYPE_ETF_FIRST: _eOesEtfTrdCnfmType
    OES_ETF_TRDCNFM_TYPE_CMPOENT: _eOesEtfTrdCnfmType
    OES_ETF_TRDCNFM_TYPE_CASH: _eOesEtfTrdCnfmType
    OES_ETF_TRDCNFM_TYPE_ETF_LAST: _eOesEtfTrdCnfmType
    __OES_ETF_TRDCNFM_TYPE_MAX: _eOesEtfTrdCnfmType
class _eOesEtfSubFlag(Enum):
    OES_ETF_SUBFLAG_FORBID_SUB: _eOesEtfSubFlag
    OES_ETF_SUBFLAG_ALLOW_SUB: _eOesEtfSubFlag
    OES_ETF_SUBFLAG_MUST_SUB: _eOesEtfSubFlag
    OES_ETF_SUBFLAG_SZ_REFUND_SUB: _eOesEtfSubFlag
    OES_ETF_SUBFLAG_SZ_MUST_SUB: _eOesEtfSubFlag
    OES_ETF_SUBFLAG_OTHER_REFUND_SUB: _eOesEtfSubFlag
    OES_ETF_SUBFLAG_OTHER_MUST_SUB: _eOesEtfSubFlag
class _eOesLotType(Enum):
    OES_LOT_TYPE_UNDEFINE: _eOesLotType
    OES_LOT_TYPE_FAILED: _eOesLotType
    OES_LOT_TYPE_ASSIGNMENT: _eOesLotType
    OES_LOT_TYPE_LOTTERY: _eOesLotType
    __OES_LOT_TYPE_MAX: _eOesLotType
class _eOesLotRejReason(Enum):
    OES_LOT_REJ_REASON_DUPLICATE: _eOesLotRejReason
    OES_LOT_REJ_REASON_INVALID_DUPLICATE: _eOesLotRejReason
    OES_LOT_REJ_REASON_OFFLINE_FIRST: _eOesLotRejReason
    OES_LOT_REJ_REASON_BAD_RECORD: _eOesLotRejReason
    OES_LOT_REJ_REASON_UNKNOW: _eOesLotRejReason
class _eOesExecType(Enum):
    OES_EXECTYPE_UNDEFINE: _eOesExecType
    OES_EXECTYPE_INSERT: _eOesExecType
    OES_EXECTYPE_CONFIRMED: _eOesExecType
    OES_EXECTYPE_CANCELLED: _eOesExecType
    OES_EXECTYPE_AUTO_CANCELLED: _eOesExecType
    OES_EXECTYPE_REJECT: _eOesExecType
    OES_EXECTYPE_TRADE: _eOesExecType
    __OES_EXECTYPE_MAX: _eOesExecType
class _eOesCurrType(Enum):
    OES_CURR_TYPE_RMB: _eOesCurrType
    OES_CURR_TYPE_HKD: _eOesCurrType
    OES_CURR_TYPE_USD: _eOesCurrType
    __OES_CURR_TYPE_MAX: _eOesCurrType
class _eOesFeeType(Enum):
    OES_FEE_TYPE_EXCHANGE_STAMP: _eOesFeeType
    OES_FEE_TYPE_EXCHANGE_TRANSFER: _eOesFeeType
    OES_FEE_TYPE_EXCHANGE_SETTLEMENT: _eOesFeeType
    OES_FEE_TYPE_EXCHANGE_TRADE_RULE: _eOesFeeType
    OES_FEE_TYPE_EXCHANGE_EXCHANGE: _eOesFeeType
    OES_FEE_TYPE_EXCHANGE_ADMINFER: _eOesFeeType
    OES_FEE_TYPE_EXCHANGE_OTHER: _eOesFeeType
    __OES_FEE_TYPE_EXCHANGE_MAX: _eOesFeeType
    OES_FEE_TYPE_BROKER_BACK_END: _eOesFeeType
class _eOesCalcFeeMode(Enum):
    OES_CALC_FEE_MODE_AMOUNT: _eOesCalcFeeMode
    OES_CALC_FEE_MODE_QTY: _eOesCalcFeeMode
    OES_CALC_FEE_MODE_ORD: _eOesCalcFeeMode
class _eOesFundTrsfDirect(Enum):
    OES_FUND_TRSF_DIRECT_IN: _eOesFundTrsfDirect
    OES_FUND_TRSF_DIRECT_OUT: _eOesFundTrsfDirect
class _eOesFundTrsfType(Enum):
    OES_FUND_TRSF_TYPE_OES_BANK: _eOesFundTrsfType
    OES_FUND_TRSF_TYPE_OES_COUNTER: _eOesFundTrsfType
    OES_FUND_TRSF_TYPE_COUNTER_BANK: _eOesFundTrsfType
    __OES_FUND_TRSF_TYPE_MAX: _eOesFundTrsfType
class _eOesFundTrsfStatus(Enum):
    OES_FUND_TRSF_STS_UNDECLARED: _eOesFundTrsfStatus
    OES_FUND_TRSF_STS_DECLARED: _eOesFundTrsfStatus
    OES_FUND_TRSF_STS_WAIT_DONE: _eOesFundTrsfStatus
    OES_FUND_TRSF_STS_DONE: _eOesFundTrsfStatus
    __OES_FUND_TRSF_STS_ROLLBACK_MIN: _eOesFundTrsfStatus
    OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK: _eOesFundTrsfStatus
    OES_FUND_TRSF_STS_DECLARED_ROLLBACK: _eOesFundTrsfStatus
    __OES_FUND_TRSF_STS_INVALID_MIN: _eOesFundTrsfStatus
    OES_FUND_TRSF_STS_INVALID_OES: _eOesFundTrsfStatus
    OES_FUND_TRSF_STS_INVALID_COUNTER: _eOesFundTrsfStatus
    OES_FUND_TRSF_STS_SUSPENDED: _eOesFundTrsfStatus
class _eOesAcctType(Enum):
    OES_ACCT_TYPE_NORMAL: _eOesAcctType
    OES_ACCT_TYPE_CREDIT: _eOesAcctType
    OES_ACCT_TYPE_OPTION: _eOesAcctType
    __OES_ACCT_TYPE_MAX: _eOesAcctType
class _eOesCashType(Enum):
    OES_CASH_TYPE_SPOT: _eOesCashType
    OES_CASH_TYPE_CREDIT: _eOesCashType
    OES_CASH_TYPE_OPTION: _eOesCashType
    __OES_CASH_TYPE_MAX: _eOesCashType
    OES_CASH_TYPE_CRE: _eOesCashType
    OES_CASH_TYPE_OPT: _eOesCashType
class _eOesAcctStatus(Enum):
    OES_ACCT_STATUS_NORMAL: _eOesAcctStatus
    OES_ACCT_STATUS_DISABLED: _eOesAcctStatus
    OES_ACCT_STATUS_LOCKED: _eOesAcctStatus
class _eOesTradingPermission(Enum):
    OES_PERMIS_MARKET_ORDER: _eOesTradingPermission
    OES_PERMIS_STRUCTURED_FUND: _eOesTradingPermission
    OES_PERMIS_BOND_QUALIFIED_INVESTOR: _eOesTradingPermission
    OES_PERMIS_XXX4: _eOesTradingPermission
    OES_PERMIS_DELISTING: _eOesTradingPermission
    OES_PERMIS_RISK_WARNING: _eOesTradingPermission
    OES_PERMIS_SINGLE_MARKET_ETF: _eOesTradingPermission
    OES_PERMIS_CROSS_BORDER_ETF: _eOesTradingPermission
    OES_PERMIS_CROSS_MARKET_ETF: _eOesTradingPermission
    OES_PERMIS_CURRENCY_ETF: _eOesTradingPermission
    OES_PERMIS_STOCK_PLEDGE_REPURCHASE: _eOesTradingPermission
    OES_PERMIS_PLEDGE_REPURCHASE: _eOesTradingPermission
    OES_PERMIS_GEM: _eOesTradingPermission
    OES_PERMIS_SH_HK_STOCK_CONNECT: _eOesTradingPermission
    OES_PERMIS_SZ_HK_STOCK_CONNECT: _eOesTradingPermission
    OES_PERMIS_CDR: _eOesTradingPermission
    OES_PERMIS_INNOVATION: _eOesTradingPermission
    __OES_PERMIS_ALL: _eOesTradingPermission
class _eOesTradingLimit(Enum):
    OES_LIMIT_BUY: _eOesTradingLimit
    OES_LIMIT_SELL: _eOesTradingLimit
    OES_LIMIT_RECALL_DESIGNATION: _eOesTradingLimit
    OES_LIMIT_DESIGNATION: _eOesTradingLimit
    OES_LIMIT_REPO: _eOesTradingLimit
    OES_LIMIT_REVERSE_REPO: _eOesTradingLimit
    OES_LIMIT_SUBSCRIPTION: _eOesTradingLimit
    OES_LIMIT_CREDIT_BUY: _eOesTradingLimit
    OES_LIMIT_CREDIT_SELL: _eOesTradingLimit
    __OES_LIMIT_ALL: _eOesTradingLimit
class _eOesQualificationClass(Enum):
    OES_QUALIFICATION_PUBLIC_INVESTOR: _eOesQualificationClass
    OES_QUALIFICATION_QUALIFIED_INVESTOR: _eOesQualificationClass
    OES_QUALIFICATION_QUALIFIED_INSTITUTIONAL: _eOesQualificationClass
class _eOesInvestorClass(Enum):
    OES_INVESTOR_CLASS_NORMAL: _eOesInvestorClass
    OES_INVESTOR_CLASS_PROFESSIONAL_A: _eOesInvestorClass
    OES_INVESTOR_CLASS_PROFESSIONAL_B: _eOesInvestorClass
    OES_INVESTOR_CLASS_PROFESSIONAL_C: _eOesInvestorClass
class _eOesOwnerType(Enum):
    OES_OWNER_TYPE_PERSONAL: _eOesOwnerType
    OES_OWNER_TYPE_EXCHANGE: _eOesOwnerType
    OES_OWNER_TYPE_MEMBER: _eOesOwnerType
    OES_OWNER_TYPE_INSTITUTION: _eOesOwnerType
    OES_OWNER_TYPE_PROPRIETARY: _eOesOwnerType
    OES_OWNER_TYPE_MKT_MAKER: _eOesOwnerType
    OES_OWNER_TYPE_SETTLEMENT: _eOesOwnerType
    __OES_OWNER_TYPE_MAX: _eOesOwnerType
class _eOesClientType(Enum):
    OES_CLIENT_TYPE_UNDEFINED: _eOesClientType
    OES_CLIENT_TYPE_INVESTOR: _eOesClientType
    OES_CLIENT_TYPE_VIRTUAL: _eOesClientType
class _eOesClientStatus(Enum):
    OES_CLIENT_STATUS_UNACTIVATED: _eOesClientStatus
    OES_CLIENT_STATUS_ACTIVATED: _eOesClientStatus
    OES_CLIENT_STATUS_PAUSE: _eOesClientStatus
    OES_CLIENT_STATUS_SUSPENDED: _eOesClientStatus
    OES_CLIENT_STATUS_CANCELLED: _eOesClientStatus
class _eOesOptContractType(Enum):
    OES_OPT_CONTRACT_TYPE_CALL: _eOesOptContractType
    OES_OPT_CONTRACT_TYPE_PUT: _eOesOptContractType
    __OES_OPT_CONTRACT_TYPE_MAX: _eOesOptContractType
class _eOesOptInvLevel(Enum):
    OES_OPT_INV_LEVEL_B: _eOesOptInvLevel
    OES_OPT_INV_LEVEL_L: _eOesOptInvLevel
    OES_OPT_INV_LEVEL_A: _eOesOptInvLevel
    __OES_OPT_INV_LEVEL_MAX: _eOesOptInvLevel
class _eOpenFlagType(Enum):
    OPEN_FLAG_TYPE_ALLOW: _eOpenFlagType
    OPEN_FLAG_TYPE_FORBID: _eOpenFlagType
    __OPEN_FLAG_TYPE_MAX: _eOpenFlagType
class _eOesOptionOpenFlag(Enum):
    OES_OPTION_OPEN_FLAG_ALLOW: _eOesOptionOpenFlag
    OES_OPTION_OPEN_FLAG_FORBID: _eOesOptionOpenFlag
class _eOesPositionEff(Enum):
    OES_POSITION_INVALID: _eOesPositionEff
    OES_POSITION_OPEN: _eOesPositionEff
    OES_POSITION_CLOSE: _eOesPositionEff
class _eOesOptionType(Enum):
    OES_OPTION_TYPE_E: _eOesOptionType
    OES_OPTION_TYPE_A: _eOesOptionType
    __OES_OPTION_TYPE_MAX: _eOesOptionType
class _eSMsgProtocolType(Enum):
    SMSG_PROTO_BINARY: _eSMsgProtocolType
    SMSG_PROTO_JSON: _eSMsgProtocolType
    SMSG_PROTO_FIX: _eSMsgProtocolType
    SMSG_PROTO_PROTOBUF: _eSMsgProtocolType
    __MAX_SMSG_PROTO_TYPE: _eSMsgProtocolType
class _eSMsgFlag(Enum):
    SMSG_MSGFLAG_NONE: _eSMsgFlag
    SMSG_MSGFLAG_REQ: _eSMsgFlag
    SMSG_MSGFLAG_RSP: _eSMsgFlag
    SMSG_MSGFLAG_NESTED: _eSMsgFlag
    SMSG_MSGFLAG_COMPRESSED: _eSMsgFlag
    SMSG_MSGFLAG_MASK_RSPFLAG: _eSMsgFlag
    SMSG_MSGFLAG_MASK_PROTOCOL: _eSMsgFlag
class _eOesMsgType(Enum):
    OESMSG_ORD_NEW_ORDER: _eOesMsgType
    OESMSG_ORD_CANCEL_REQUEST: _eOesMsgType
    OESMSG_ORD_BATCH_ORDERS: _eOesMsgType
    __OESMSG_ORD_MAX: _eOesMsgType
    __OESMSG_RPT_MIN: _eOesMsgType
    OESMSG_RPT_MARKET_STATE: _eOesMsgType
    OESMSG_RPT_REPORT_SYNCHRONIZATION: _eOesMsgType
    OESMSG_RPT_BUSINESS_REJECT: _eOesMsgType
    OESMSG_RPT_ORDER_INSERT: _eOesMsgType
    OESMSG_RPT_ORDER_REPORT: _eOesMsgType
    OESMSG_RPT_TRADE_REPORT: _eOesMsgType
    OESMSG_RPT_FUND_TRSF_REJECT: _eOesMsgType
    OESMSG_RPT_FUND_TRSF_REPORT: _eOesMsgType
    OESMSG_RPT_CASH_ASSET_VARIATION: _eOesMsgType
    OESMSG_RPT_STOCK_HOLDING_VARIATION: _eOesMsgType
    OESMSG_RPT_OPTION_HOLDING_VARIATION: _eOesMsgType
    __OESMSG_RPT_MAX: _eOesMsgType
    __OESMSG_NONTRD_MIN: _eOesMsgType
    OESMSG_NONTRD_FUND_TRSF_REQ: _eOesMsgType
    OESMSG_NONTRD_CHANGE_PASSWORD: _eOesMsgType
    __OESMSG_NONTRD_MAX: _eOesMsgType
    __OESMSG_QRYMSG_MIN: _eOesMsgType
    OESMSG_QRYMSG_CLIENT_OVERVIEW: _eOesMsgType
    OESMSG_QRYMSG_ORD: _eOesMsgType
    OESMSG_QRYMSG_TRD: _eOesMsgType
    OESMSG_QRYMSG_CASH_ASSET: _eOesMsgType
    OESMSG_QRYMSG_STK_HLD: _eOesMsgType
    OESMSG_QRYMSG_OPT_HLD: _eOesMsgType
    OESMSG_QRYMSG_CUST: _eOesMsgType
    OESMSG_QRYMSG_INV_ACCT: _eOesMsgType
    OESMSG_QRYMSG_COMMISSION_RATE: _eOesMsgType
    OESMSG_QRYMSG_FUND_TRSF: _eOesMsgType
    OESMSG_QRYMSG_STOCK: _eOesMsgType
    OESMSG_QRYMSG_ETF: _eOesMsgType
    OESMSG_QRYMSG_ETF_COMPONENT: _eOesMsgType
    OESMSG_QRYMSG_OPTION: _eOesMsgType
    OESMSG_QRYMSG_ISSUE: _eOesMsgType
    OESMSG_QRYMSG_LOT_WINNING: _eOesMsgType
    OESMSG_QRYMSG_TRADING_DAY: _eOesMsgType
    OESMSG_QRYMSG_MARKET_STATE: _eOesMsgType
    OESMSG_QRYMSG_COUNTER_CASH: _eOesMsgType
    __OESMSG_QRYMSG_MAX: _eOesMsgType
    OESMSG_SESS_TRD_LOGIN: _eOesMsgType
    OESMSG_SESS_RPT_LOGIN: _eOesMsgType
    OESMSG_SESS_QRY_LOGIN: _eOesMsgType
    OESMSG_SESS_HEARTBEAT: _eOesMsgType
    OESMSG_SESS_TEST_REQUEST: _eOesMsgType
    OESMSG_SESS_LOGOUT: _eOesMsgType
    OESMSG_RPT_ORDER_REJECT: _eOesMsgType
class _eOesSubscribeReportType(Enum):
    OES_SUB_RPT_TYPE_DEFAULT: _eOesSubscribeReportType
    OES_SUB_RPT_TYPE_BUSINESS_REJECT: _eOesSubscribeReportType
    OES_SUB_RPT_TYPE_ORDER_INSERT: _eOesSubscribeReportType
    OES_SUB_RPT_TYPE_ORDER_REPORT: _eOesSubscribeReportType
    OES_SUB_RPT_TYPE_TRADE_REPORT: _eOesSubscribeReportType
    OES_SUB_RPT_TYPE_FUND_TRSF_REPORT: _eOesSubscribeReportType
    OES_SUB_RPT_TYPE_CASH_ASSET_VARIATION: _eOesSubscribeReportType
    OES_SUB_RPT_TYPE_HOLDING_VARIATION: _eOesSubscribeReportType
    OES_SUB_RPT_TYPE_MARKET_STATE: _eOesSubscribeReportType
    OES_SUB_RPT_TYPE_ALL: _eOesSubscribeReportType
    __MAX_OES_SUB_RPT_TYPE: _eOesSubscribeReportType
class _eSSocketProtocolType(Enum):
    SPK_SOCKET_PROTOCOL_TCP: _eSSocketProtocolType
    SPK_SOCKET_PROTOCOL_IPC: _eSSocketProtocolType
    SPK_SOCKET_PROTOCOL_UDP_UCAST: _eSSocketProtocolType
    SPK_SOCKET_PROTOCOL_UDP_MCAST: _eSSocketProtocolType
    SPK_SOCKET_PROTOCOL_PGM: _eSSocketProtocolType
    SPK_SOCKET_PROTOCOL_EPGM: _eSSocketProtocolType
    __MAX_SPK_SOCKET_PROTOCOL: _eSSocketProtocolType
class _eGeneralClientClusterType(Enum):
    GENERAL_CLI_CLUSTER_UNDEFINED: _eGeneralClientClusterType
    GENERAL_CLI_CLUSTER_REPLICA_SET: _eGeneralClientClusterType
    GENERAL_CLI_CLUSTER_PEER_NODES: _eGeneralClientClusterType
    __MAX_GENERAL_CLI_CLUSTER_TYPE: _eGeneralClientClusterType
class _eGeneralClientEncryptType(Enum):
    GENERAL_CLI_ENCRYPT_NONE: _eGeneralClientEncryptType
    GENERAL_CLI_ENCRYPT_MD5: _eGeneralClientEncryptType
    GENERAL_CLI_ENCRYPT_SHA: _eGeneralClientEncryptType
    GENERAL_CLI_ENCRYPT_DES: _eGeneralClientEncryptType
    GENERAL_CLI_ENCRYPT_AES: _eGeneralClientEncryptType
    GENERAL_CLI_ENCRYPT_RSA: _eGeneralClientEncryptType
class _eOesApiChannelType(Enum):
    OESAPI_CHANNEL_TYPE_ORDER: _eOesApiChannelType
    OESAPI_CHANNEL_TYPE_REPORT: _eOesApiChannelType
    OESAPI_CHANNEL_TYPE_QUERY: _eOesApiChannelType
class _eMdsExchangeId(Enum):
    MDS_EXCH_SSE: _eMdsExchangeId
    MDS_EXCH_SZSE: _eMdsExchangeId
    __MAX_MDS_EXCH: _eMdsExchangeId
    __MAX_MDS_EXCH_ALIGNED4: _eMdsExchangeId
    __MAX_MDS_EXCH_ALIGNED8: _eMdsExchangeId
class _eMdsMsgSource(Enum):
    MDS_MSGSRC_UNDEFINED: _eMdsMsgSource
    MDS_MSGSRC_EZEI_TCP: _eMdsMsgSource
    MDS_MSGSRC_EZEI_UDP: _eMdsMsgSource
    MDS_MSGSRC_VDE_LEVEL2: _eMdsMsgSource
    MDS_MSGSRC_VDE_LEVEL1: _eMdsMsgSource
    MDS_MSGSRC_SZSE_MDGW_BINARY: _eMdsMsgSource
    MDS_MSGSRC_SZSE_MDGW_STEP: _eMdsMsgSource
    MDS_MSGSRC_MDS_TCP: _eMdsMsgSource
    MDS_MSGSRC_MDS_UDP: _eMdsMsgSource
    MDS_MSGSRC_FILE_MKTDT: _eMdsMsgSource
    MDS_MSGSRC_SSE_MDGW_BINARY: _eMdsMsgSource
    MDS_MSGSRC_SSE_MDGW_STEP: _eMdsMsgSource
    __MAX_MDS_MSGSRC: _eMdsMsgSource
    MDS_MSGSRC_MDGW_BINARY: _eMdsMsgSource
    MDS_MSGSRC_MDGW_STEP: _eMdsMsgSource
class _eMdsSecurityType(Enum):
    MDS_SECURITY_TYPE_STOCK: _eMdsSecurityType
    MDS_SECURITY_TYPE_INDEX: _eMdsSecurityType
    MDS_SECURITY_TYPE_OPTION: _eMdsSecurityType
    __MAX_MDS_SECURITY_TYPE: _eMdsSecurityType
class _eMdsMdStreamType(Enum):
    MDS_MD_STREAM_TYPE_INDEX: _eMdsMdStreamType
    MDS_MD_STREAM_TYPE_STOCK: _eMdsMdStreamType
    MDS_MD_STREAM_TYPE_BOND: _eMdsMdStreamType
    MDS_MD_STREAM_TYPE_FUND: _eMdsMdStreamType
    MDS_MD_STREAM_TYPE_SZSE_STOCK: _eMdsMdStreamType
    MDS_MD_STREAM_TYPE_SZSE_REPO: _eMdsMdStreamType
    MDS_MD_STREAM_TYPE_SZSE_TRADE_STATS: _eMdsMdStreamType
    MDS_MD_STREAM_TYPE_OPTION: _eMdsMdStreamType
    MDS_MD_STREAM_TYPE_OTHERS: _eMdsMdStreamType
    __MAX_MDS_MD_STREAM_TYPE: _eMdsMdStreamType
class _eMdsMdLevel(Enum):
    MDS_MD_LEVEL_0: _eMdsMdLevel
    MDS_MD_LEVEL_1: _eMdsMdLevel
    MDS_MD_LEVEL_2: _eMdsMdLevel
    __MAX_MDS_MD_LEVEL: _eMdsMdLevel
class _eMdsL2PriceLevelOperator(Enum):
    MDS_L2_PX_OPERATOR_ADD: _eMdsL2PriceLevelOperator
    MDS_L2_PX_OPERATOR_UPDATE: _eMdsL2PriceLevelOperator
    MDS_L2_PX_OPERATOR_DELETE: _eMdsL2PriceLevelOperator
    __MAX_MDS_L2_PX_OPERATOR: _eMdsL2PriceLevelOperator
class _eMdsL2VirtualAuctionSide(Enum):
    MDS_L2_VIRTUAL_AUCTION_SIDE_NONE: _eMdsL2VirtualAuctionSide
    MDS_L2_VIRTUAL_AUCTION_SIDE_BID: _eMdsL2VirtualAuctionSide
    MDS_L2_VIRTUAL_AUCTION_SIDE_OFFER: _eMdsL2VirtualAuctionSide
class _eMdsL2TradeExecType(Enum):
    MDS_L2_TRADE_EXECTYPE_CANCELED: _eMdsL2TradeExecType
    MDS_L2_TRADE_EXECTYPE_TRADE: _eMdsL2TradeExecType
class _eMdsL2TradeBSFlag(Enum):
    MDS_L2_TRADE_BSFLAG_BUY: _eMdsL2TradeBSFlag
    MDS_L2_TRADE_BSFLAG_SELL: _eMdsL2TradeBSFlag
    MDS_L2_TRADE_BSFLAG_UNKNOWN: _eMdsL2TradeBSFlag
class _eMdsL2OrderSideT(Enum):
    MDS_L2_ORDER_SIDE_BUY: _eMdsL2OrderSideT
    MDS_L2_ORDER_SIDE_SELL: _eMdsL2OrderSideT
    MDS_L2_ORDER_SIDE_BORROW: _eMdsL2OrderSideT
    MDS_L2_ORDER_SIDE_LEND: _eMdsL2OrderSideT
class _eMdsL2OrderType(Enum):
    MDS_L2_ORDER_TYPE_MKT: _eMdsL2OrderType
    MDS_L2_ORDER_TYPE_LMT: _eMdsL2OrderType
    MDS_L2_ORDER_TYPE_SAMEPARTY_BEST: _eMdsL2OrderType
class _eMdsClientType(Enum):
    MDS_CLIENT_TYPE_UNDEFINED: _eMdsClientType
    MDS_CLIENT_TYPE_INVESTOR: _eMdsClientType
    MDS_CLIENT_TYPE_VIRTUAL: _eMdsClientType
class _eMdsClientStatus(Enum):
    MDS_CLIENT_STATUS_UNACTIVATED: _eMdsClientStatus
    MDS_CLIENT_STATUS_ACTIVATED: _eMdsClientStatus
    MDS_CLIENT_STATUS_PAUSE: _eMdsClientStatus
    MDS_CLIENT_STATUS_SUSPENDED: _eMdsClientStatus
    MDS_CLIENT_STATUS_CANCELLED: _eMdsClientStatus
class _eMdsMsgType(Enum):
    MDS_MSGTYPE_HEARTBEAT: _eMdsMsgType
    MDS_MSGTYPE_TEST_REQUEST: _eMdsMsgType
    MDS_MSGTYPE_LOGON: _eMdsMsgType
    MDS_MSGTYPE_LOGOUT: _eMdsMsgType
    MDS_MSGTYPE_MARKET_DATA_REQUEST: _eMdsMsgType
    MDS_MSGTYPE_COMPRESSED_PACKETS: _eMdsMsgType
    __MDS_MSGTYPE_SESSION_MAX: _eMdsMsgType
    MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH: _eMdsMsgType
    MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH: _eMdsMsgType
    MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH: _eMdsMsgType
    MDS_MSGTYPE_TRADING_SESSION_STATUS: _eMdsMsgType
    MDS_MSGTYPE_SECURITY_STATUS: _eMdsMsgType
    __MDS_MSGTYPE_L1_MAX: _eMdsMsgType
    MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT: _eMdsMsgType
    MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT: _eMdsMsgType
    MDS_MSGTYPE_L2_TRADE: _eMdsMsgType
    MDS_MSGTYPE_L2_ORDER: _eMdsMsgType
    MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL: _eMdsMsgType
    MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL: _eMdsMsgType
    MDS_MSGTYPE_L2_MARKET_OVERVIEW: _eMdsMsgType
    MDS_MSGTYPE_L2_VIRTUAL_AUCTION_PRICE: _eMdsMsgType
    __MDS_MSGTYPE_L2_MAX: _eMdsMsgType
    MDS_MSGTYPE_QRY_MARKET_DATA_SNAPSHOT: _eMdsMsgType
    MDS_MSGTYPE_QRY_SECURITY_STATUS: _eMdsMsgType
    MDS_MSGTYPE_QRY_TRADING_SESSION_STATUS: _eMdsMsgType
    __MDS_MSGTYPE_QRY_MAX: _eMdsMsgType
class _eMdsSubscribeMode(Enum):
    MDS_SUB_MODE_SET: _eMdsSubscribeMode
    MDS_SUB_MODE_APPEND: _eMdsSubscribeMode
    MDS_SUB_MODE_DELETE: _eMdsSubscribeMode
    __MAX_MDS_SUB_MODE: _eMdsSubscribeMode
class _eMdsMktSubscribeFlag(Enum):
    MDS_MKT_SUB_FLAG_DEFAULT: _eMdsMktSubscribeFlag
    MDS_MKT_SUB_FLAG_ALL: _eMdsMktSubscribeFlag
    MDS_MKT_SUB_FLAG_DISABLE: _eMdsMktSubscribeFlag
    __MAX_MDS_MKT_SUB_FLAG: _eMdsMktSubscribeFlag
class _eMdsSubscribedTickType(Enum):
    MDS_TICK_TYPE_LATEST_SIMPLIFIED: _eMdsSubscribedTickType
    MDS_TICK_TYPE_LATEST_TIMELY: _eMdsSubscribedTickType
    MDS_TICK_TYPE_ALL_INCREMENTS: _eMdsSubscribedTickType
    __MAX_MDS_TICK_TYPE: _eMdsSubscribedTickType
class _eMdsSubscribedTickExpireType(Enum):
    MDS_TICK_EXPIRE_TYPE_NONE: _eMdsSubscribedTickExpireType
    MDS_TICK_EXPIRE_TYPE_IMMEDIATE: _eMdsSubscribedTickExpireType
    MDS_TICK_EXPIRE_TYPE_TIMELY: _eMdsSubscribedTickExpireType
    MDS_TICK_EXPIRE_TYPE_TIMEOUT: _eMdsSubscribedTickExpireType
    __MAX_MDS_TICK_EXPIRE_TYPE: _eMdsSubscribedTickExpireType
class _eMdsSubscribeDataType(Enum):
    MDS_SUB_DATA_TYPE_DEFAULT: _eMdsSubscribeDataType
    MDS_SUB_DATA_TYPE_L1_SNAPSHOT: _eMdsSubscribeDataType
    MDS_SUB_DATA_TYPE_L2_SNAPSHOT: _eMdsSubscribeDataType
    MDS_SUB_DATA_TYPE_L2_BEST_ORDERS: _eMdsSubscribeDataType
    MDS_SUB_DATA_TYPE_L2_TRADE: _eMdsSubscribeDataType
    MDS_SUB_DATA_TYPE_L2_ORDER: _eMdsSubscribeDataType
    MDS_SUB_DATA_TYPE_L2_VIRTUAL_AUCTION_PRICE: _eMdsSubscribeDataType
    MDS_SUB_DATA_TYPE_L2_MARKET_OVERVIEW: _eMdsSubscribeDataType
    MDS_SUB_DATA_TYPE_TRADING_SESSION_STATUS: _eMdsSubscribeDataType
    MDS_SUB_DATA_TYPE_SECURITY_STATUS: _eMdsSubscribeDataType
    MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT: _eMdsSubscribeDataType
    MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT: _eMdsSubscribeDataType
    MDS_SUB_DATA_TYPE_NONE: _eMdsSubscribeDataType
    MDS_SUB_DATA_TYPE_ALL: _eMdsSubscribeDataType
    __MAX_MDS_SUB_DATA_TYPE: _eMdsSubscribeDataType
class _eMdsSubscribedChannelNo(Enum):
    MDS_CHANNEL_NO_DEFAULT: _eMdsSubscribedChannelNo
    MDS_CHANNEL_NO_ONE: _eMdsSubscribedChannelNo
    MDS_CHANNEL_NO_TWO: _eMdsSubscribedChannelNo
    MDS_CHANNEL_NO_THREE: _eMdsSubscribedChannelNo
    MDS_CHANNEL_NO_FOUR: _eMdsSubscribedChannelNo
    MDS_CHANNEL_NO_ALL: _eMdsSubscribedChannelNo
    MDS_CHANNEL_NO_NONE: _eMdsSubscribedChannelNo
class _eMdsApiChannelType(Enum):
    MDSAPI_CHANNEL_TYPE_TCP: _eMdsApiChannelType
    MDSAPI_CHANNEL_TYPE_UDP: _eMdsApiChannelType
    MDSAPI_CHANNEL_TYPE_QUERY: _eMdsApiChannelType
int8 = str
uint8 = int
int16 = int
uint16 = int
int32 = int
uint32 = int
int64 = int
uint64 = int
float32 = float
float64 = float
float128 = float
STimeval32T = _spk_struct_timeval32
STimeval64T = _spk_struct_timeval64
eOesExchangeIdT = _eOesExchangeId
eOesMarketIdT = _eOesMarketId
eOesPlatformIdT = _eOesPlatformId
eOesMarketStatusT = _eOesMarketStatus
eOesTrdSessTypeT = _eOesTrdSessType
eOesSecurityTypeT = _eOesSecurityType
eOesSubSecurityTypeT = _eOesSubSecurityType
eOesSecurityLevelT = _eOesSecurityLevel
eOesSecurityRiskLevelT = _eOesSecurityRiskLevel
eOesSecuritySuspFlagT = _eOesSecuritySuspFlag
eOesOrdStatusT = _eOesOrdStatus
eOesOrdTypeT = _eOesOrdType
eOesOrdTypeShT = _eOesOrdTypeSh
eOesOrdTypeSzT = _eOesOrdTypeSz
eOesBuySellTypeT = _eOesBuySellType
eOesOrdDirT = _eOesOrdDir
eOesEtfTrdCnfmTypeT = _eOesEtfTrdCnfmType
eOesEtfSubFlagT = _eOesEtfSubFlag
eOesLotTypeT = _eOesLotType
eOesLotRejReasonT = _eOesLotRejReason
eOesExecTypeT = _eOesExecType
eOesCurrTypeT = _eOesCurrType
eOesFeeTypeT = _eOesFeeType
eOesCalcFeeModeT = _eOesCalcFeeMode
eOesFundTrsfDirectT = _eOesFundTrsfDirect
eOesFundTrsfTypeT = _eOesFundTrsfType
eOesFundTrsfStatusT = _eOesFundTrsfStatus
eOesAcctTypeT = _eOesAcctType
eOesCashTypeT = _eOesCashType
eOesAcctStatusT = _eOesAcctStatus
eOesTradingPermissionT = _eOesTradingPermission
eOesTradingLimitT = _eOesTradingLimit
eOesQualificationClassT = _eOesQualificationClass
eOesInvestorClassT = _eOesInvestorClass
eOesOwnerTypeT = _eOesOwnerType
eOesClientTypeT = _eOesClientType
eOesClientStatusT = _eOesClientStatus
eOesOptContractTypeT = _eOesOptContractType
eOesOptInvLevelT = _eOesOptInvLevel
eOpenFlagTypeT = _eOpenFlagType
eOesOptionOpenFlagT = _eOesOptionOpenFlag
eOesPositionEffT = _eOesPositionEff
eOesOptionTypeT = _eOesOptionType
OesOrdReqT = _OesOrdReq
OesOrdCancelReqT = _OesOrdCancelReq
OesOrdRejectT = _OesOrdReject
OesOrdCnfmT = _OesOrdCnfm
OesTrdBaseInfoT = _OesTrdBaseInfo
OesTrdCnfmT = _OesTrdCnfm
OesLotWinningBaseInfoT = _OesLotWinningBaseInfo
OesFundTrsfBaseInfoT = _OesFundTrsfBaseInfo
OesFundTrsfReqT = _OesFundTrsfReq
OesFundTrsfRejectT = _OesFundTrsfReject
OesFundTrsfReportT = _OesFundTrsfReport
OesIssueBaseInfoT = _OesIssueBaseInfo
OesPriceLimitT = _OesPriceLimit
OesStockBaseInfoT = _OesStockBaseInfo
OesEtfBaseInfoT = _OesEtfBaseInfo
OesEtfComponentBaseInfoT = _OesEtfComponentBaseInfo
OesOptionBaseInfoT = _OesOptionBaseInfo
OesCashAssetBaseInfoT = _OesCashAssetBaseInfo
OesCustBaseInfoT = _OesCustBaseInfo
OesInvAcctBaseInfoT = _OesInvAcctBaseInfo
OesStkHoldingBaseInfoT = _OesStkHoldingBaseInfo
OesOptHoldingBaseInfoT = _OesOptHoldingBaseInfo
OesMarketStateInfoT = _OesMarketStateInfo
OesTradingPermissionEntryT = _OesTradingPermissionEntry
OesInputSourceInfoT = _OesInputSourceInfo
eSMsgProtocolTypeT = _eSMsgProtocolType
eSMsgFlagT = _eSMsgFlag
SMsgHeadT = _SMsgHead
OesQryCursorT = _OesQryCursor
OesQryReqHeadT = _OesQryReqHead
OesQryRspHeadT = _OesQryRspHead
OesQryOrdFilterT = _OesQryOrdFilter
OesOrdItemT = _OesOrdCnfm
OesQryOrdReqT = _OesQryOrdReq
OesQryOrdRspT = _OesQryOrdRsp
OesQryTrdFilterT = _OesQryTrdFilter
OesTrdItemT = _OesTrdCnfm
OesQryTrdReqT = _OesQryTrdReq
OesQryTrdRspT = _OesQryTrdRsp
OesQryCashAssetFilterT = _OesQryCashAssetFilter
OesCashAssetItemT = _OesCashAssetItem
OesQryCashAssetReqT = _OesQryCashAssetReq
OesQryCashAssetRspT = _OesQryCashAssetRsp
OesCounterCashItemT = _OesCounterCashItem
OesQryCounterCashReqT = _OesQryCounterCashReq
OesQryCounterCashRspT = _OesQryCounterCashRsp
OesQryStkHoldingFilterT = _OesQryStkHoldingFilter
OesStkHoldingItemT = _OesStkHoldingItem
OesQryStkHoldingReqT = _OesQryStkHoldingReq
OesQryStkHoldingRspT = _OesQryStkHoldingRsp
OesQryOptHoldingFilterT = _OesQryStkHoldingFilter
OesOptHoldingItemT = _OesOptHoldingItem
OesQryOptHoldingReqT = _OesQryOptHoldingReq
OesQryOptHoldingRspT = _OesQryHoldRsp
OesQryCustFilterT = _OesQryCustFilter
OesCustItemT = _OesCustBaseInfo
OesQryCustReqT = _OesQryCustReq
OesQryCustRspT = _OesQryCustRsp
OesQryInvAcctFilterT = _OesQryInvAcctFilter
OesInvAcctItemT = _OesInvAcctItem
OesQryInvAcctReqT = _OesQryInvAcctReq
OesQryInvAcctRspT = _OesQryInvAcctRsp
OesInvAcctOverviewT = _OesInvAcctOverview
OesCashAcctOverviewT = _OesCashAcctOverview
OesCustOverviewT = _OesCustOverview
OesClientOverviewT = _OesClientOverview
OesQryCommissionRateFilterT = _OesQryCommissionRateFilter
OesCommissionRateItemT = _OesCommissionRateItem
OesQryCommissionRateReqT = _OesQryCommissionRateReq
OesQryCommissionRateRspT = _OesQryCommissionRateRsp
OesQryFundTransferSerialFilterT = _OesQryFundTransferSerialFilter
OesFundTransferSerialItemT = _OesFundTrsfReport
OesQryFundTransferSerialReqT = _OesQryFundTransferSerialReq
OesQryFundTransferSerialRspT = _OesQryFundTransferSerialRsp
OesQryLotWinningFilterT = _OesQryLotWinningFilter
OesLotWinningItemT = _OesLotWinningBaseInfo
OesQryLotWinningReqT = _OesQryLotWinningReq
OesQryLotWinningRspT = _OesQryLotWinningRsp
OesQryIssueFilterT = _OesQryIssueFilter
OesIssueItemT = _OesIssueBaseInfo
OesQryIssueReqT = _OesQryIssueReq
OesQryIssueRspT = _OesQryIssueRsp
OesQryStockFilterT = _OesQryStockFilter
OesStockItemT = _OesStockBaseInfo
OesQryStockReqT = _OesQryStockReq
OesQryStockRspT = _OesQryStockRsp
OesQryEtfFilterT = _OesQryEtfFilter
OesEtfItemT = _OesEtfBaseInfo
OesQryEtfReqT = _OesQryEtfReq
OesQryEtfRspT = _OesQryEtfRsp
OesQryEtfComponentFilterT = _OesQryEtfComponentFilter
OesEtfComponentItemT = _OesEtfComponentItem
OesQryEtfComponentReqT = _OesQryEtfComponentReq
OesQryEtfComponentRspT = _OesQryEtfComponentRsp
OesQryOptionFilterT = _OesQryOptionFilter
OesOptionItemT = _OesOptionBaseInfo
OesQryOptionReqT = _OesQryOptionReq
OesQryOptionRspT = _OesQryOptionRsp
OesQryTradingDayRspT = _OesQryTradingDayRsp
OesQryMarketStateFilterT = _OesQryMarketStateFilter
OesMarketStateItemT = _OesMarketStateInfo
OesQryMarketStateReqT = _OesQryMarketStateReq
OesQryMarketStateRspT = _OesQryMarketStateRsp
OesQryReqMsgT = _OesQryReqMsg
OesQryRspMsgT = _OesQryRspMsg
eOesMsgTypeT = _eOesMsgType
eOesSubscribeReportTypeT = _eOesSubscribeReportType
OesLogonReqT = _OesLogonReq
OesLogonRspT = _OesLogonRsp
OesReportSynchronizationReqT = _OesReportSynchronizationReq
OesReportSynchronizationRspT = _OesReportSynchronizationRsp
OesTestRequestReqT = _OesTestRequestReq
OesTestRequestRspT = _OesTestRequestRsp
OesChangePasswordReqT = _OesChangePasswordReq
OesChangePasswordRspT = _OesChangePasswordRsp
OesBatchOrdersHeadT = _OesBatchOrdersHead
OesBatchOrdersReqT = _OesBatchOrdersReq
OesRptMsgHeadT = _OesRptMsgHead
OesRptMsgBodyT = _OesRptMsgBody
OesRptMsgT = _OesRptMsg
OesReqMsgBodyT = _OesReqMsgBody
OesRspMsgBodyT = _OesRspMsgBody
SErrMsgT = _SErrMsg
SDataBufferT = _SDataBuffer
eSSocketProtocolTypeT = _eSSocketProtocolType
SSocketUriInfoT = _SSocketUriInfo
SSocketIpPortInfoT = _SSocketIpPortInfo
SSocketChannelInfoT = _SSocketChannelInfo
SSocketOptionConfigT = _SSocketOptionConfig
eGeneralClientClusterTypeT = _eGeneralClientClusterType
eGeneralClientEncryptTypeT = _eGeneralClientEncryptType
SGeneralClientChannelT = _SGeneralClientChannel
SGeneralClientChannelGroupT = _SGeneralClientChannelGroup
SGeneralClientAddrInfoT = _SGeneralClientAddrInfo
SGeneralClientRemoteCfgT = _SGeneralClientRemoteCfg
eOesApiChannelTypeT = _eOesApiChannelType
OesApiSessionInfoT = _SGeneralClientChannel
OesApiChannelGroupT = _SGeneralClientChannelGroup
OesApiAddrInfoT = _SGeneralClientAddrInfo
OesApiRemoteCfgT = _SGeneralClientRemoteCfg
OesApiSubscribeInfoT = _OesApiSubscribeInfo
OesApiClientCfgT = _OesApiClientCfg
OesApiClientEnvT = _OesApiClientEnv
F_OESAPI_ON_RPT_MSG_T = Callable[[_SGeneralClientChannel,_SMsgHead,Any,Any], int]
F_OESAPI_ON_QRY_MSG_T = Callable[[_SGeneralClientChannel,_SMsgHead,Any,_OesQryCursor,Any], int]
eMdsExchangeIdT = _eMdsExchangeId
eMdsMsgSourceT = _eMdsMsgSource
eMdsSecurityTypeT = _eMdsSecurityType
eMdsMdStreamTypeT = _eMdsMdStreamType
eMdsMdLevelT = _eMdsMdLevel
eMdsL2PriceLevelOperatorT = _eMdsL2PriceLevelOperator
eMdsL2VirtualAuctionSideT = _eMdsL2VirtualAuctionSide
eMdsL2TradeExecTypeT = _eMdsL2TradeExecType
eMdsL2TradeBSFlagT = _eMdsL2TradeBSFlag
eMdsL2OrderSideT = _eMdsL2OrderSideT
eMdsL2OrderTypeT = _eMdsL2OrderType
eMdsClientTypeT = _eMdsClientType
eMdsClientStatusT = _eMdsClientStatus
MdsTradingSessionStatusMsgT = _MdsTradingSessionStatusMsg
MdsSecurityStatusMsgT = _MdsSecurityStatusMsg
MdsPriceLevelEntryT = _MdsPriceLevelEntry
MdsMktDataSnapshotHeadT = _MdsMktDataSnapshotHead
MdsIndexSnapshotBodyT = _MdsIndexSnapshotBody
MdsStockSnapshotBodyT = _MdsStockSnapshotBody
MdsL1SnapshotBodyT = _MdsL1SnapshotBody
MdsL2StockSnapshotBodyT = _MdsL2StockSnapshotBody
MdsL2StockSnapshotIncrementalT = _MdsL2StockSnapshotIncremental
MdsL2BestOrdersSnapshotBodyT = _MdsL2BestOrdersSnapshotBody
MdsL2BestOrdersSnapshotIncrementalT = _MdsL2BestOrdersSnapshotIncremental
MdsL2VirtualAuctionPriceT = _MdsL2VirtualAuctionPrice
MdsL2MarketOverviewT = _MdsL2MarketOverview
MdsL2SnapshotBodyT = _MdsL2SnapshotBody
MdsMktDataSnapshotT = _MdsMktDataSnapshot
MdsL2TradeT = _MdsL2Trade
MdsL2OrderT = _MdsL2Order
MdsL2TickLostT = _MdsL2TickLost
MdsQryMktDataSnapshotReqT = _MdsQryMktDataSnapshotReq
MdsQrySecurityStatusReqT = _MdsQryMktDataSnapshotReq
MdsQryTrdSessionStatusReqT = _MdsQryTrdSessionStatusReq
eMdsMsgTypeT = _eMdsMsgType
eMdsSubscribeModeT = _eMdsSubscribeMode
eMdsMktSubscribeFlagT = _eMdsMktSubscribeFlag
eMdsSubscribedTickTypeT = _eMdsSubscribedTickType
eMdsSubscribedTickExpireTypeT = _eMdsSubscribedTickExpireType
eMdsSubscribeDataTypeT = _eMdsSubscribeDataType
eMdsTickChannelNoT = _eMdsSubscribedChannelNo
MdsLogonReqT = _MdsLogonReq
MdsLogonRspT = _MdsLogonRsp
MdsMktDataRequestEntryT = _MdsMktDataRequestEntry
MdsMktDataRequestReqT = _MdsMktDataRequestReq
MdsMktDataRequestReqBufT = _MdsMktDataRequestReqBuf
MdsMktDataRequestRspT = _MdsMktDataRequestRsp
MdsTestRequestReqT = _MdsTestRequestReq
MdsTestRequestRspT = _MdsTestRequestRsp
MdsMktReqMsgBodyT = _MdsMktReqMsgBody
MdsMktRspMsgBodyT = _MdsMktRspMsgBody
MdsUdpPktHeadT = _MdsUdpPktHead
eMdsApiChannelTypeT = _eMdsApiChannelType
MdsApiSessionInfoT = _SGeneralClientChannel
MdsApiChannelGroupT = _SGeneralClientChannelGroup
MdsApiAddrInfoT = _SGeneralClientAddrInfo
MdsApiRemoteCfgT = _SGeneralClientRemoteCfg
MdsApiSubscribeInfoT = _MdsMktDataRequestReqBuf
MdsApiClientCfgT = _MdsApiClientCfg
MdsApiClientEnvT = _MdsApiClientEnv
F_MDSAPI_ONMSG_T = Callable[[_SGeneralClientChannel,_SMsgHead,Any,Any], int]
OES_APPL_VER_ID: str
OES_MIN_APPL_VER_ID: str
OESAPI_CFG_DEFAULT_SECTION: str
OESAPI_CFG_DEFAULT_SECTION_LOGGER: str
OESAPI_CFG_DEFAULT_KEY_ORD_ADDR: str
OESAPI_CFG_DEFAULT_KEY_RPT_ADDR: str
OESAPI_CFG_DEFAULT_KEY_QRY_ADDR: str
OESAPI_DEFAULT_STRING_DELIM: str
MDS_APPL_VER_ID: str
MDS_MIN_APPL_VER_ID: str
MDSAPI_CFG_DEFAULT_SECTION: str
MDSAPI_CFG_DEFAULT_SECTION_LOGGER: str
MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR: str
MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR: str
MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1: str
MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2: str
MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE: str
MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER: str
MDSAPI_DEFAULT_STRING_DELIM: str
def __SPlatform_GetErrno()->int:
    ...
def __SPlatform_GetNegErrno()->int:
    ...
def __SPlatform_SetErrno(err: int)->None:
    ...
def __SPlatform_IsErrEagain(err: int)->int:
    ...
def __SPlatform_IsErrEconnaborted(err: int)->int:
    ...
def __SPlatform_IsErrEtimeout(err: int)->int:
    ...
def __SPlatform_IsErrEpipe(err: int)->int:
    ...
def __SPlatform_IsErrEintr(err: int)->int:
    ...
def __SPlatform_IsErrEbadmsg(err: int)->int:
    ...
def __SPlatform_IsNegEagain(err: int)->int:
    ...
def __SPlatform_IsNegEconnaborted(err: int)->int:
    ...
def __SPlatform_IsNegEtimeout(err: int)->int:
    ...
def __SPlatform_IsNegEpipe(err: int)->int:
    ...
def __SPlatform_IsNegEintr(err: int)->int:
    ...
def __SPlatform_IsNegEbadmsg(err: int)->int:
    ...
def OesApi_SendOrderReq(pOrdChannel: _SGeneralClientChannel, pOrdReq: _OesOrdReq)->int:
    ...
def OesApi_SendOrderCancelReq(pOrdChannel: _SGeneralClientChannel, pCancelReq: _OesOrdCancelReq)->int:
    ...
def OesApi_SendBatchOrdersReq2(pOrdChannel: _SGeneralClientChannel, pOrdReqArray: _OesOrdReq, ordCount: int)->int:
    ...
def OesApi_SendFundTransferReq(pOrdChannel: _SGeneralClientChannel, pFundTrsfReq: _OesFundTrsfReq)->int:
    ...
def OesApi_SendChangePasswordReq(pOrdChannel: _SGeneralClientChannel, pChangePasswordReq: _OesChangePasswordReq, pOutChangePasswordRsp: _OesChangePasswordRsp)->int:
    ...
def OesApi_WaitReportMsg(pRptChannel: _SGeneralClientChannel, timeoutMs: int, pRptMsgCallback: List[str])->int:
    ...
def OesApi_GetApiVersion()->str:
    ...
def OesApi_GetTradingDay(pQryChannel: _SGeneralClientChannel)->int:
    ...
def OesApi_GetClientOverview(pQryChannel: _SGeneralClientChannel, pClientOverview: _OesClientOverview)->int:
    ...
def OesApi_QuerySingleOrder(pQryChannel: _SGeneralClientChannel, clSeqNo: int, pOrdItem: _OesOrdCnfm)->int:
    ...
def OesApi_QuerySingleCashAsset(pQryChannel: _SGeneralClientChannel, pCashAcctId: str, pCashAssetItem: _OesCashAssetItem)->int:
    ...
def OesApi_QuerySingleStkHolding(pQryChannel: _SGeneralClientChannel, pInvAcctId: str, pSecurityId: str, pHoldingItem: _OesStkHoldingItem)->int:
    ...
def OesApi_QuerySingleOptHolding(pQryChannel: _SGeneralClientChannel, pInvAcctId: str, pSecurityId: str, pHoldingItem: _OesOptHoldingItem)->int:
    ...
def OesApi_QueryOrder(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryOrdFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryTrade(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryTrdFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryCashAsset(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryCashAssetFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryStkHolding(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryStkHoldingFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryOptHolding(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryStkHoldingFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryLotWinning(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryLotWinningFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryCustInfo(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryCustFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryInvAcct(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryInvAcctFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryCommissionRate(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryCommissionRateFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryFundTransferSerial(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryFundTransferSerialFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryIssue(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryIssueFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryStock(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryStockFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryEtf(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryEtfFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryEtfComponent(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryEtfComponentFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryOption(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryOptionFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryMarketState(pQryChannel: _SGeneralClientChannel, pQryFilter: _OesQryMarketStateFilter, pQryMsgCallback: List[str])->int:
    ...
def OesApi_QueryCounterCash(pQryChannel: _SGeneralClientChannel, pCashAcctId: str, pCounterCashItem: _OesCounterCashItem)->int:
    ...
def OesApi_Logon(pOutSessionInfo: _SGeneralClientChannel, channelType: _eOesApiChannelType, pUri: str, pUsername: str, pPassword: str, clEnvId: str, heartBtInt: int, pSocketOptions: _SSocketOptionConfig)->int:
    ...
def OesApi_LogonReplicaSet(pOutSessionInfo: _SGeneralClientChannel, channelType: _eOesApiChannelType, pUriList: str, pUsername: str, pPassword: str, clEnvId: str, heartBtInt: int, pSocketOptions: _SSocketOptionConfig)->int:
    ...
def OesApi_LogonPeerNodes(pOutSessionInfo: _SGeneralClientChannel, channelType: _eOesApiChannelType, pUriList: str, pUsername: str, pPassword: str, clEnvId: str, heartBtInt: int, pSocketOptions: _SSocketOptionConfig)->int:
    ...
def OesApi_SendReportSynchronization(pRptChannel: _SGeneralClientChannel, subscribeEnvId: str, subscribeRptTypes: int, lastRptSeqNum: int)->int:
    ...
def OesApi_SendHeartbeat(pSessionInfo: _SGeneralClientChannel)->int:
    ...
def OesApi_TestOrdChannel(pOrdChannel: _SGeneralClientChannel, pTestReqId: str, testReqIdSize: int)->int:
    ...
def OesApi_TestOrdChannel2(pOrdChannel: _SGeneralClientChannel, pTestReq: _OesTestRequestReq, pOutTestRsp: _OesTestRequestRsp)->int:
    ...
def OesApi_TestRptChannel(pRptChannel: _SGeneralClientChannel, pTestReqId: str, testReqIdSize: int)->int:
    ...
def OesApi_TestRptChannel2(pRptChannel: _SGeneralClientChannel, pTestReq: _OesTestRequestReq)->int:
    ...
def OesApi_Logout(pSessionInfo: _SGeneralClientChannel, isDestory: int)->int:
    ...
def OesApi_Destory(pSessionInfo: _SGeneralClientChannel)->None:
    ...
def OesApi_InitAll(pOutCliEnv: _OesApiClientEnv, pCfgFile: str, pLoggerSection: str, pCfgSection: str, pOrdAddrKey: str, pRptAddrKey: str, pQryAddrKey: str, lastRptSeqNum: int, pLastClSeqNo: int)->Tuple[int,int]:
    return "retv","pLastClSeqNo"
def OesApi_InitAllByConvention(pOutCliEnv: _OesApiClientEnv, pCfgFile: str, lastRptSeqNum: int, pLastClSeqNo: int)->Tuple[int,int]:
    return "retv","pLastClSeqNo"
def OesApi_LogoutAll(pCliEnv: _OesApiClientEnv, isDestory: int)->None:
    ...
def OesApi_DestoryAll(pCliEnv: _OesApiClientEnv)->None:
    ...
def OesApi_InitLogger(pCfgFile: str, pLoggerSection: str)->int:
    ...
def OesApi_ResetThreadLoggerName(pLogSystemName: str)->int:
    ...
def OesApi_InitOrdChannel(pOrdChannel: _SGeneralClientChannel, pCfgFile: str, pCfgSection: str, pAddrKey: str, pLastClSeqNo: int)->Tuple[int,int]:
    return "retv","pLastClSeqNo"
def OesApi_InitOrdChannel2(pOrdChannel: _SGeneralClientChannel, pRemoteCfg: _SGeneralClientRemoteCfg, pLastClSeqNo: int)->Tuple[int,int]:
    return "retv","pLastClSeqNo"
def OesApi_InitRptChannel(pRptChannel: _SGeneralClientChannel, pCfgFile: str, pCfgSection: str, pAddrKey: str, lastRptSeqNum: int)->int:
    ...
def OesApi_InitRptChannel2(pRptChannel: _SGeneralClientChannel, pRemoteCfg: _SGeneralClientRemoteCfg, pSubscribeInfo: _OesApiSubscribeInfo, lastRptSeqNum: int)->int:
    ...
def OesApi_InitQryChannel(pQryChannel: _SGeneralClientChannel, pCfgFile: str, pCfgSection: str, pAddrKey: str)->int:
    ...
def OesApi_InitQryChannel2(pQryChannel: _SGeneralClientChannel, pRemoteCfg: _SGeneralClientRemoteCfg)->int:
    ...
def OesApi_ParseAddrListString(pUriList: str, pOutAddrList: _SGeneralClientAddrInfo, addrListLength: int)->int:
    ...
def OesApi_ParseConfigFromFile(pCfgFile: str, pSection: str, pAddrKey: str, pOutRemoteCfg: _SGeneralClientRemoteCfg, pOutSubscribeInfo: _OesApiSubscribeInfo)->int:
    ...
def OesApi_ParseAllConfig(pCfgFile: str, pOutApiCfg: _OesApiClientCfg)->int:
    ...
def OesApi_InitChannelGroup(pChannelGroup: _SGeneralClientChannelGroup)->int:
    ...
def OesApi_DestoryChannelGroup(pChannelGroup: _SGeneralClientChannelGroup)->int:
    ...
def OesApi_AddToChannelGroup(pChannelGroup: _SGeneralClientChannelGroup, pChannel: _SGeneralClientChannel)->int:
    ...
def OesApi_DeleteFromChannelGroup(pChannelGroup: _SGeneralClientChannelGroup, pTargetChanne: _SGeneralClientChannel)->int:
    ...
def OesApi_GetFromChannelGroup(pChannelGroup: _SGeneralClientChannelGroup, index: int)->_SGeneralClientChannel:
    ...
def OesApi_GetFromChannelGroupBySocket(pChannelGroup: _SGeneralClientChannelGroup, socketFd: int)->_SGeneralClientChannel:
    ...
def OesApi_ForeachInChannelGroup(pChannelGroup: _SGeneralClientChannelGroup, fnCallback: List[str])->int:
    ...
def OesApi_SetThreadUsername(pUsername: str)->None:
    ...
def OesApi_GetThreadUsername()->str:
    ...
def OesApi_SetThreadPassword(pPassword: str)->None:
    ...
def OesApi_SetThreadEnvId(clEnvId: str)->None:
    ...
def OesApi_GetThreadEnvId()->str:
    ...
def OesApi_SetCustomizedIpAndMac(pIpStr: str, pMacStr: str)->int:
    ...
def OesApi_GetCustomizedIp()->str:
    ...
def OesApi_GetCustomizedMac()->str:
    ...
def OesApi_SetCustomizedDriverId(pDriverId: str)->int:
    ...
def OesApi_GetCustomizedDriverId()->str:
    ...
def OesApi_GetClEnvId(pChannel: _SGeneralClientChannel)->str:
    ...
def OesApi_GetLastRecvTime(pChannel: _SGeneralClientChannel)->int:
    ...
def OesApi_GetLastSendTime(pChannel: _SGeneralClientChannel)->int:
    ...
def OesApi_HasMoreCachedData(pRptChannel: _SGeneralClientChannel)->int:
    ...
def OesApi_IsValidOrdChannel(pOrdChannel: _SGeneralClientChannel)->int:
    ...
def OesApi_IsValidRptChannel(pRptChannel: _SGeneralClientChannel)->int:
    ...
def OesApi_IsValidQryChannel(pQryChannel: _SGeneralClientChannel)->int:
    ...
def OesApi_IsValidChannelGroup(pChannelGroup: _SGeneralClientChannelGroup)->int:
    ...
def OesApi_GetLastError()->int:
    ...
def OesApi_SetLastError(errCode: int)->None:
    ...
def OesApi_GetErrorMsg(errCode: int)->str:
    ...
def OesApi_GetErrorMsg2(status: int, detailStatus: int)->str:
    ...
def MdsApi_Logon(pOutSessionInfo: _SGeneralClientChannel, channelType: _eMdsApiChannelType, pUri: str, pUsername: str, pPassword: str, heartBtInt: int, pSocketOptions: _SSocketOptionConfig)->int:
    ...
def MdsApi_LogonReplicaSet(pOutSessionInfo: _SGeneralClientChannel, channelType: _eMdsApiChannelType, pUriList: str, pUsername: str, pPassword: str, heartBtInt: int, pSocketOptions: _SSocketOptionConfig)->int:
    ...
def MdsApi_LogonPeerNodes(pOutSessionInfo: _SGeneralClientChannel, channelType: _eMdsApiChannelType, pUriList: str, pUsername: str, pPassword: str, heartBtInt: int, pSocketOptions: _SSocketOptionConfig)->int:
    ...
def MdsApi_SyncSubscribeOnLogon(pSessionInfo: _SGeneralClientChannel, pMktDataRequestReq: _MdsMktDataRequestReq, pEntries: _MdsMktDataRequestEntry)->int:
    ...
def MdsApi_SubscribeMarketData(pSessionInfo: _SGeneralClientChannel, pMktDataRequestReq: _MdsMktDataRequestReq, pEntries: _MdsMktDataRequestEntry)->int:
    ...
def MdsApi_SubscribeByString(pTcpChannel: _SGeneralClientChannel, pSecurityListStr: str, pDelim: str, exchangeId: _eMdsExchangeId, securityType: _eMdsSecurityType, subMode: _eMdsSubscribeMode, dataTypes: int)->int:
    ...
def MdsApi_SubscribeByString2(pTcpChannel: _SGeneralClientChannel, ppSecurityArray: List[str], exchangeId: _eMdsExchangeId, securityType: _eMdsSecurityType, subMode: _eMdsSubscribeMode, dataTypes: int)->int:
    ...
def MdsApi_SubscribeByStringAndPrefixes(pTcpChannel: _SGeneralClientChannel, pSecurityListStr: str, pDelim: str, pSseCodePrefixes: str, pSzseCodePrefixes: str, securityType: _eMdsSecurityType, subMode: _eMdsSubscribeMode, dataTypes: int)->int:
    ...
def MdsApi_SubscribeByStringAndPrefixes2(pTcpChannel: _SGeneralClientChannel, ppSecurityArray: List[str], pSseCodePrefixes: str, pSzseCodePrefixes: str, securityType: _eMdsSecurityType, subMode: _eMdsSubscribeMode, dataTypes: int)->int:
    ...
def MdsApi_SendHeartbeat(pSessionInfo: _SGeneralClientChannel)->int:
    ...
def MdsApi_SendTestRequest(pSessionInfo: _SGeneralClientChannel, pTestReqId: str, testReqIdSize: int)->int:
    ...
def MdsApi_Logout(pSessionInfo: _SGeneralClientChannel, isDestory: int)->int:
    ...
def MdsApi_Destory(pSessionInfo: _SGeneralClientChannel)->None:
    ...
def MdsApi_WaitOnMsg(pTcpChannel: _SGeneralClientChannel, timeoutMs: int, pOnMsgCallback: List[str])->int:
    ...
def MdsApi_WaitOnMsgCompressible(pTcpChannel: _SGeneralClientChannel, timeoutMs: int, pOnMsgCallback: List[str])->int:
    ...
def MdsApi_GetApiVersion()->str:
    ...
def MdsApi_QueryMktDataSnapshot(pQryChannel: _SGeneralClientChannel, exchangeId: _eMdsExchangeId, securityType: _eMdsSecurityType, instrId: int, pRspBuf: _MdsMktDataSnapshot)->int:
    ...
def MdsApi_QuerySecurityStatus(pQryChannel: _SGeneralClientChannel, exchangeId: _eMdsExchangeId, securityType: _eMdsSecurityType, instrId: int, pRspBuf: _MdsSecurityStatusMsg)->int:
    ...
def MdsApi_QueryTrdSessionStatus(pQryChannel: _SGeneralClientChannel, exchangeId: _eMdsExchangeId, securityType: _eMdsSecurityType, pRspBuf: _MdsTradingSessionStatusMsg)->int:
    ...
def MdsApi_ConnectToUdpMcast(pOutSessionInfo: _SGeneralClientChannel, pUri: str, pSocketOptions: _SSocketOptionConfig)->int:
    ...
def MdsApi_WaitOnUdpMsg(pUdpChannel: _SGeneralClientChannel, timeoutMs: int, pOnMsgCallback: List[str])->int:
    ...
def MdsApi_InitAll(pOutCliEnv: _MdsApiClientEnv, pCfgFile: str, pLoggerSection: str, pCfgSection: str, pTcpAddrKey: str, pQryAddrKey: str, pUdpL1AddrKey: str, pUdpL2AddrKey: str, pUdpTickTradeAddrKey: str, pUdpTickOrderAddrKey: str)->int:
    ...
def MdsApi_InitAllByConvention(pOutCliEnv: _MdsApiClientEnv, pCfgFile: str)->int:
    ...
def MdsApi_LogoutAll(pCliEnv: _MdsApiClientEnv, isDestory: int)->None:
    ...
def MdsApi_DestoryAll(pCliEnv: _MdsApiClientEnv)->None:
    ...
def MdsApi_InitLogger(pCfgFile: str, pLoggerSection: str)->int:
    ...
def MdsApi_ResetThreadLoggerName(pLogSystemName: str)->int:
    ...
def MdsApi_InitTcpChannel(pTcpChannel: _SGeneralClientChannel, pCfgFile: str, pCfgSection: str, pAddrKey: str)->int:
    ...
def MdsApi_InitTcpChannel2(pTcpChannel: _SGeneralClientChannel, pRemoteCfg: _SGeneralClientRemoteCfg, pSubscribeInfo: _MdsMktDataRequestReqBuf)->int:
    ...
def MdsApi_InitQryChannel(pQryChannel: _SGeneralClientChannel, pCfgFile: str, pCfgSection: str, pAddrKey: str)->int:
    ...
def MdsApi_InitQryChannel2(pQryChannel: _SGeneralClientChannel, pRemoteCfg: _SGeneralClientRemoteCfg)->int:
    ...
def MdsApi_InitUdpChannel(pUdpChannel: _SGeneralClientChannel, pCfgFile: str, pCfgSection: str, pAddrKey: str)->int:
    ...
def MdsApi_InitUdpChannel2(pUdpChannel: _SGeneralClientChannel, pRemoteCfg: _SGeneralClientRemoteCfg)->int:
    ...
def MdsApi_ParseAddrListString(pUriList: str, pOutAddrList: _SGeneralClientAddrInfo, addrListLength: int)->int:
    ...
def MdsApi_ParseConfigFromFile(pCfgFile: str, pSection: str, pAddrKey: str, pOutRemoteCfg: _SGeneralClientRemoteCfg, pOutSubscribeInfo: _MdsMktDataRequestReqBuf)->int:
    ...
def MdsApi_ParseAllConfig(pCfgFile: str, pOutApiCfg: _MdsApiClientCfg)->int:
    ...
def MdsApi_InitChannelGroup(pChannelGroup: _SGeneralClientChannelGroup)->int:
    ...
def MdsApi_DestoryChannelGroup(pChannelGroup: _SGeneralClientChannelGroup)->int:
    ...
def MdsApi_AddToChannelGroup(pChannelGroup: _SGeneralClientChannelGroup, pChannel: _SGeneralClientChannel)->int:
    ...
def MdsApi_DeleteFromChannelGroup(pChannelGroup: _SGeneralClientChannelGroup, pTargetChanne: _SGeneralClientChannel)->int:
    ...
def MdsApi_GetFromChannelGroup(pChannelGroup: _SGeneralClientChannelGroup, index: int)->_SGeneralClientChannel:
    ...
def MdsApi_GetFromChannelGroupBySocket(pChannelGroup: _SGeneralClientChannelGroup, socketFd: int)->_SGeneralClientChannel:
    ...
def MdsApi_ForeachInChannelGroup(pChannelGroup: _SGeneralClientChannelGroup, fnCallback: List[str])->int:
    ...
def MdsApi_SetThreadUsername(pUsername: str)->None:
    ...
def MdsApi_GetThreadUsername()->str:
    ...
def MdsApi_SetThreadPassword(pPassword: str)->None:
    ...
def MdsApi_GetLastRecvTime(pSessionInfo: _SGeneralClientChannel)->int:
    ...
def MdsApi_GetLastSendTime(pSessionInfo: _SGeneralClientChannel)->int:
    ...
def MdsApi_HasMoreCachedData(pTcpChannel: _SGeneralClientChannel)->int:
    ...
def MdsApi_IsValidTcpChannel(pTcpChannel: _SGeneralClientChannel)->int:
    ...
def MdsApi_IsValidQryChannel(pQryChannel: _SGeneralClientChannel)->int:
    ...
def MdsApi_IsValidUdpChannel(pUdpChannel: _SGeneralClientChannel)->int:
    ...
def MdsApi_IsValidChannelGroup(pChannelGroup: _SGeneralClientChannelGroup)->int:
    ...
def MdsApi_GetLastError()->int:
    ...
def MdsApi_SetLastError(errCode: int)->None:
    ...
def MdsApi_GetErrorMsg(errCode: int)->str:
    ...
def MdsApi_GetErrorMsg2(status: int, detailStatus: int)->str:
    ...
def MdsHelper_SetTickTypeOnSubscribeByString(tickType: _eMdsSubscribedTickType)->None:
    ...
def MdsHelper_ClearSubscribeRequestEntries(pSubscribeInfo: _MdsMktDataRequestReqBuf)->None:
    ...
def MdsHelper_SetSubscribeRequestMode(pSubscribeInfo: _MdsMktDataRequestReqBuf, subMode: _eMdsSubscribeMode)->None:
    ...
def MdsHelper_SetSubscribeRequestTickType(pSubscribeInfo: _MdsMktDataRequestReqBuf, tickType: _eMdsSubscribedTickType)->None:
    ...
def MdsHelper_SetSubscribeRequestDataTypes(pSubscribeInfo: _MdsMktDataRequestReqBuf, dataTypes: int)->None:
    ...
def MdsHelper_SetSubscribeRequestSubFlag(pSubscribeInfo: _MdsMktDataRequestReqBuf, exchangeId: _eMdsExchangeId, securityType: _eMdsSecurityType, subFlag: _eMdsMktSubscribeFlag)->None:
    ...
def MdsHelper_AddSubscribeRequestEntry(pSubscribeInfo: _MdsMktDataRequestReqBuf, exchangeId: _eMdsExchangeId, securityType: _eMdsSecurityType, securityId: int)->int:
    ...

