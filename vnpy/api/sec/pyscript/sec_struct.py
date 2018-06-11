# encoding: UTF-8
from collections import OrderedDict























#重传方式
RESUME_TYPE = OrderedDict()






#ERR-错误信息
DFITCSECRspInfoField = OrderedDict()

DFITCSECRspInfoField['requestID'] = 'long'
DFITCSECRspInfoField['sessionID'] = 'long'
DFITCSECRspInfoField['accountID'] = 'string'
DFITCSECRspInfoField['errorID'] = 'long'
DFITCSECRspInfoField['localOrderID'] = 'long'
DFITCSECRspInfoField['spdOrderID'] = 'int'
DFITCSECRspInfoField['errorMsg'] = 'string'


#ERR-消息通知
DFITCSECRspNoticeField = OrderedDict()

DFITCSECRspNoticeField['noticeMsg'] = 'string'


#SEC-登录请求
DFITCSECReqUserLoginField = OrderedDict()

DFITCSECReqUserLoginField['requestID'] = 'long'
DFITCSECReqUserLoginField['accountID'] = 'string'
DFITCSECReqUserLoginField['password'] = 'string'
DFITCSECReqUserLoginField['compressflag'] = 'int'


#SEC-登录响应
DFITCSECRspUserLoginField = OrderedDict()

DFITCSECRspUserLoginField['requestID'] = 'long'
DFITCSECRspUserLoginField['accountID'] = 'string'
DFITCSECRspUserLoginField['sessionID'] = 'long'
DFITCSECRspUserLoginField['frontID'] = 'long'
DFITCSECRspUserLoginField['localOrderID'] = 'long'
DFITCSECRspUserLoginField['loginTime'] = 'string'
DFITCSECRspUserLoginField['tradingDay'] = 'int'
DFITCSECRspUserLoginField['result'] = 'long'
DFITCSECRspUserLoginField['rtnMsg'] = 'string'


#SEC-登出请求
DFITCSECReqUserLogoutField = OrderedDict()

DFITCSECReqUserLogoutField['requestID'] = 'long'
DFITCSECReqUserLogoutField['accountID'] = 'string'


#SEC-登出响应 
DFITCSECRspUserLogoutField = OrderedDict()

DFITCSECRspUserLogoutField['requestID'] = 'long'
DFITCSECRspUserLogoutField['accountID'] = 'string'
DFITCSECRspUserLogoutField['result'] = 'long'
DFITCSECRspUserLogoutField['rtnMsg'] = 'string'


#SEC-更新用户密码请求
DFITCSECReqPasswordUpdateField = OrderedDict()

DFITCSECReqPasswordUpdateField['requestID'] = 'long'
DFITCSECReqPasswordUpdateField['accountID'] = 'string'
DFITCSECReqPasswordUpdateField['oldPassword'] = 'string'
DFITCSECReqPasswordUpdateField['newPassword'] = 'string'
DFITCSECReqPasswordUpdateField['passwordType'] = 'int'


#SEC-更新用户密码响应
DFITCSECRspPasswordUpdateField = OrderedDict()

DFITCSECRspPasswordUpdateField['requestID'] = 'long'
DFITCSECRspPasswordUpdateField['accountID'] = 'string'
DFITCSECRspPasswordUpdateField['passwordType'] = 'int'
DFITCSECRspPasswordUpdateField['result'] = 'long'
DFITCSECRspPasswordUpdateField['rtnMsg'] = 'string'


#SEC-更新行情账户密码请求
DFITCSECReqMDPasswordUpdateField = OrderedDict()

DFITCSECReqMDPasswordUpdateField['requestID'] = 'long'
DFITCSECReqMDPasswordUpdateField['accountID'] = 'string'
DFITCSECReqMDPasswordUpdateField['oldPassword'] = 'string'
DFITCSECReqMDPasswordUpdateField['newPassword'] = 'string'


#SEC-更新行情账户密码响应
DFITCSECRspMDPasswordUpdateField = OrderedDict()

DFITCSECRspMDPasswordUpdateField['requestID'] = 'long'
DFITCSECRspMDPasswordUpdateField['accountID'] = 'string'
DFITCSECRspMDPasswordUpdateField['result'] = 'long'
DFITCSECRspMDPasswordUpdateField['rtnMsg'] = 'string'


#SEC-撤单请求
DFITCSECReqWithdrawOrderField = OrderedDict()

DFITCSECReqWithdrawOrderField['requestID'] = 'long'
DFITCSECReqWithdrawOrderField['accountID'] = 'string'
DFITCSECReqWithdrawOrderField['spdOrderID'] = 'int'
DFITCSECReqWithdrawOrderField['localOrderID'] = 'long'


#SEC-撤单响应
DFITCSECRspWithdrawOrderField = OrderedDict()

DFITCSECRspWithdrawOrderField['requestID'] = 'long'
DFITCSECRspWithdrawOrderField['accountID'] = 'string'
DFITCSECRspWithdrawOrderField['localOrderID'] = 'long'
DFITCSECRspWithdrawOrderField['spdOrderID'] = 'int'
DFITCSECRspWithdrawOrderField['entrustTime'] = 'string'
DFITCSECRspWithdrawOrderField['cancelMsg'] = 'string'


#STOCK-委托请求
DFITCStockReqEntrustOrderField = OrderedDict()

DFITCStockReqEntrustOrderField['requestID'] = 'long'
DFITCStockReqEntrustOrderField['localOrderID'] = 'long'
DFITCStockReqEntrustOrderField['exchangeID'] = 'string'
DFITCStockReqEntrustOrderField['accountID'] = 'string'
DFITCStockReqEntrustOrderField['entrustPrice'] = 'float'
DFITCStockReqEntrustOrderField['entrustDirection'] = 'int'
DFITCStockReqEntrustOrderField['entrustQty'] = 'int'
DFITCStockReqEntrustOrderField['securityID'] = 'string'
DFITCStockReqEntrustOrderField['orderType'] = 'int'
DFITCStockReqEntrustOrderField['entrustBatchID'] = 'int'
DFITCStockReqEntrustOrderField['eachSeatID'] = 'string'
DFITCStockReqEntrustOrderField['hkEntrustLimit'] = 'int'
DFITCStockReqEntrustOrderField['hkOrderType'] = 'int'


#STOCK-委托响应
DFITCStockRspEntrustOrderField = OrderedDict()

DFITCStockRspEntrustOrderField['requestID'] = 'long'
DFITCStockRspEntrustOrderField['accountID'] = 'string'
DFITCStockRspEntrustOrderField['localOrderID'] = 'long'
DFITCStockRspEntrustOrderField['spdOrderID'] = 'int'
DFITCStockRspEntrustOrderField['entrustBatchID'] = 'int'
DFITCStockRspEntrustOrderField['entrustMsg'] = 'string'


#STOCK-委托查询请求
DFITCStockReqQryEntrustOrderField = OrderedDict()

DFITCStockReqQryEntrustOrderField['requestID'] = 'long'
DFITCStockReqQryEntrustOrderField['exchangeID'] = 'string'
DFITCStockReqQryEntrustOrderField['accountID'] = 'string'
DFITCStockReqQryEntrustOrderField['spdOrderID'] = 'int'
DFITCStockReqQryEntrustOrderField['entrustDirection'] = 'int'
DFITCStockReqQryEntrustOrderField['securityID'] = 'string'
DFITCStockReqQryEntrustOrderField['entrustBatchID'] = 'int'
DFITCStockReqQryEntrustOrderField['entrustQryFlag'] = 'int'
DFITCStockReqQryEntrustOrderField['withdrawFlag'] = 'string'
DFITCStockReqQryEntrustOrderField['incQryIndex'] = 'string'


#STOCK-委托查询响应
DFITCStockRspQryEntrustOrderField = OrderedDict()

DFITCStockRspQryEntrustOrderField['requestID'] = 'long'
DFITCStockRspQryEntrustOrderField['offerShareholderID'] = 'string'
DFITCStockRspQryEntrustOrderField['currency'] = 'string'
DFITCStockRspQryEntrustOrderField['turnover'] = 'float'
DFITCStockRspQryEntrustOrderField['tradePrice'] = 'float'
DFITCStockRspQryEntrustOrderField['tradeTime'] = 'string'
DFITCStockRspQryEntrustOrderField['tradeQty'] = 'int'
DFITCStockRspQryEntrustOrderField['shareholderID'] = 'string'
DFITCStockRspQryEntrustOrderField['exchangeID'] = 'string'
DFITCStockRspQryEntrustOrderField['clearFunds'] = 'float'
DFITCStockRspQryEntrustOrderField['entrustType'] = 'int'
DFITCStockRspQryEntrustOrderField['spdOrderID'] = 'int'
DFITCStockRspQryEntrustOrderField['entrustPrice'] = 'float'
DFITCStockRspQryEntrustOrderField['entrustDirection'] = 'int'
DFITCStockRspQryEntrustOrderField['entrustQty'] = 'int'
DFITCStockRspQryEntrustOrderField['securityID'] = 'string'
DFITCStockRspQryEntrustOrderField['securityType'] = 'string'
DFITCStockRspQryEntrustOrderField['securityName'] = 'string'
DFITCStockRspQryEntrustOrderField['entrustTime'] = 'string'
DFITCStockRspQryEntrustOrderField['declareTime'] = 'string'
DFITCStockRspQryEntrustOrderField['declareResult'] = 'int'
DFITCStockRspQryEntrustOrderField['withdrawFlag'] = 'string'
DFITCStockRspQryEntrustOrderField['freezeFunds'] = 'float'
DFITCStockRspQryEntrustOrderField['accountID'] = 'string'
DFITCStockRspQryEntrustOrderField['noteMsg'] = 'string'
DFITCStockRspQryEntrustOrderField['withdrawQty'] = 'int'
DFITCStockRspQryEntrustOrderField['declareOrderID'] = 'string'
DFITCStockRspQryEntrustOrderField['orderType'] = 'int'
DFITCStockRspQryEntrustOrderField['entrustBatchID'] = 'int'
DFITCStockRspQryEntrustOrderField['freezeFundsSerialID'] = 'int'
DFITCStockRspQryEntrustOrderField['freezeStockSerialID'] = 'int'
DFITCStockRspQryEntrustOrderField['declareDate'] = 'int'
DFITCStockRspQryEntrustOrderField['declareSerialID'] = 'int'
DFITCStockRspQryEntrustOrderField['entrustDate'] = 'int'
DFITCStockRspQryEntrustOrderField['incQryIndex'] = 'string'
DFITCStockRspQryEntrustOrderField['ipAddr'] = 'string'
DFITCStockRspQryEntrustOrderField['macAddr'] = 'string'


#STOCK-实时成交查询请求
DFITCStockReqQryRealTimeTradeField = OrderedDict()

DFITCStockReqQryRealTimeTradeField['requestID'] = 'long'
DFITCStockReqQryRealTimeTradeField['exchangeID'] = 'string'
DFITCStockReqQryRealTimeTradeField['accountID'] = 'string'
DFITCStockReqQryRealTimeTradeField['securityID'] = 'string'
DFITCStockReqQryRealTimeTradeField['entrustBatchID'] = 'int'
DFITCStockReqQryRealTimeTradeField['entrustDirection'] = 'int'
DFITCStockReqQryRealTimeTradeField['spdOrderID'] = 'int'
DFITCStockReqQryRealTimeTradeField['queryFlag'] = 'int'


#STOCK-实时成交查询响应
DFITCStockRspQryRealTimeTradeField = OrderedDict()

DFITCStockRspQryRealTimeTradeField['requestID'] = 'long'
DFITCStockRspQryRealTimeTradeField['accountID'] = 'string'
DFITCStockRspQryRealTimeTradeField['spdOrderID'] = 'int'
DFITCStockRspQryRealTimeTradeField['declareOrderID'] = 'string'
DFITCStockRspQryRealTimeTradeField['exchangeID'] = 'string'
DFITCStockRspQryRealTimeTradeField['shareholderID'] = 'string'
DFITCStockRspQryRealTimeTradeField['entrustDirection'] = 'int'
DFITCStockRspQryRealTimeTradeField['withdrawFlag'] = 'string'
DFITCStockRspQryRealTimeTradeField['securityID'] = 'string'
DFITCStockRspQryRealTimeTradeField['securityName'] = 'string'
DFITCStockRspQryRealTimeTradeField['entrustQty'] = 'int'
DFITCStockRspQryRealTimeTradeField['entrustPrice'] = 'float'
DFITCStockRspQryRealTimeTradeField['withdrawQty'] = 'int'
DFITCStockRspQryRealTimeTradeField['tradeQty'] = 'int'
DFITCStockRspQryRealTimeTradeField['turnover'] = 'float'
DFITCStockRspQryRealTimeTradeField['tradePrice'] = 'float'
DFITCStockRspQryRealTimeTradeField['tradeTime'] = 'string'
DFITCStockRspQryRealTimeTradeField['currency'] = 'string'
DFITCStockRspQryRealTimeTradeField['clearFunds'] = 'float'
DFITCStockRspQryRealTimeTradeField['entrustBatchID'] = 'int'
DFITCStockRspQryRealTimeTradeField['orderType'] = 'int'


#STOCK-分笔成交查询请求
DFITCStockReqQrySerialTradeField = OrderedDict()

DFITCStockReqQrySerialTradeField['requestID'] = 'long'
DFITCStockReqQrySerialTradeField['exchangeID'] = 'string'
DFITCStockReqQrySerialTradeField['accountID'] = 'string'
DFITCStockReqQrySerialTradeField['spdOrderID'] = 'int'
DFITCStockReqQrySerialTradeField['entrustDirection'] = 'int'
DFITCStockReqQrySerialTradeField['securityID'] = 'string'
DFITCStockReqQrySerialTradeField['entrustBatchID'] = 'int'
DFITCStockReqQrySerialTradeField['tradeQryFlag'] = 'int'
DFITCStockReqQrySerialTradeField['incQryIndex'] = 'string'


#STOCK-分笔成交查询响应
DFITCStockRspQrySerialTradeField = OrderedDict()

DFITCStockRspQrySerialTradeField['requestID'] = 'long'
DFITCStockRspQrySerialTradeField['accountID'] = 'string'
DFITCStockRspQrySerialTradeField['currency'] = 'string'
DFITCStockRspQrySerialTradeField['tradeID'] = 'string'
DFITCStockRspQrySerialTradeField['turnover'] = 'float'
DFITCStockRspQrySerialTradeField['tradePrice'] = 'float'
DFITCStockRspQrySerialTradeField['tradeQty'] = 'int'
DFITCStockRspQrySerialTradeField['shareholderID'] = 'string'
DFITCStockRspQrySerialTradeField['exchangeID'] = 'string'
DFITCStockRspQrySerialTradeField['clearFunds'] = 'float'
DFITCStockRspQrySerialTradeField['spdOrderID'] = 'int'
DFITCStockRspQrySerialTradeField['entrustDirection'] = 'int'
DFITCStockRspQrySerialTradeField['securityID'] = 'string'
DFITCStockRspQrySerialTradeField['securityType'] = 'string'
DFITCStockRspQrySerialTradeField['securityName'] = 'string'
DFITCStockRspQrySerialTradeField['withdrawFlag'] = 'string'
DFITCStockRspQrySerialTradeField['commission'] = 'float'
DFITCStockRspQrySerialTradeField['rtnSerialID'] = 'int'
DFITCStockRspQrySerialTradeField['interestQuote'] = 'float'
DFITCStockRspQrySerialTradeField['declareOrderID'] = 'string'
DFITCStockRspQrySerialTradeField['incQryIndex'] = 'string'
DFITCStockRspQrySerialTradeField['interest'] = 'float'
DFITCStockRspQrySerialTradeField['tradeTime'] = 'string'


#STOCK-持仓查询请求
DFITCStockReqQryPositionField = OrderedDict()

DFITCStockReqQryPositionField['requestID'] = 'long'
DFITCStockReqQryPositionField['exchangeID'] = 'string'
DFITCStockReqQryPositionField['accountID'] = 'string'
DFITCStockReqQryPositionField['securityID'] = 'string'
DFITCStockReqQryPositionField['posiQryFlag'] = 'int'


#STOCK-持仓查询响应
DFITCStockRspQryPositionField = OrderedDict()

DFITCStockRspQryPositionField['requestID'] = 'long'
DFITCStockRspQryPositionField['accountID'] = 'string'
DFITCStockRspQryPositionField['currency'] = 'string'
DFITCStockRspQryPositionField['sellTurnover'] = 'float'
DFITCStockRspQryPositionField['sellTradeQty'] = 'int'
DFITCStockRspQryPositionField['sellEntrustQty'] = 'int'
DFITCStockRspQryPositionField['buyTurnover'] = 'float'
DFITCStockRspQryPositionField['buyTradeQty'] = 'int'
DFITCStockRspQryPositionField['buyEntrustQty'] = 'int'
DFITCStockRspQryPositionField['nonCirculateQty'] = 'int'
DFITCStockRspQryPositionField['shareholderID'] = 'string'
DFITCStockRspQryPositionField['exchangeID'] = 'string'
DFITCStockRspQryPositionField['openDate'] = 'int'
DFITCStockRspQryPositionField['ableSellQty'] = 'int'
DFITCStockRspQryPositionField['securityID'] = 'string'
DFITCStockRspQryPositionField['securityType'] = 'string'
DFITCStockRspQryPositionField['securityName'] = 'string'
DFITCStockRspQryPositionField['securityQty'] = 'int'
DFITCStockRspQryPositionField['position'] = 'int'
DFITCStockRspQryPositionField['unSettleQty'] = 'int'
DFITCStockRspQryPositionField['changeDate'] = 'int'
DFITCStockRspQryPositionField['ablePurchaseQty'] = 'int'
DFITCStockRspQryPositionField['ableRedemptionQty'] = 'int'
DFITCStockRspQryPositionField['freezeQty'] = 'int'
DFITCStockRspQryPositionField['offsetSQty'] = 'int'
DFITCStockRspQryPositionField['offsetBQty'] = 'int'
DFITCStockRspQryPositionField['purchaseTradeQty'] = 'int'
DFITCStockRspQryPositionField['redemptionTradeQty'] = 'int'
DFITCStockRspQryPositionField['tradeUnit'] = 'int'
DFITCStockRspQryPositionField['totalSellQty'] = 'int'
DFITCStockRspQryPositionField['totalBuyQty'] = 'int'
DFITCStockRspQryPositionField['rationedSharesQty'] = 'int'
DFITCStockRspQryPositionField['purchaseQty'] = 'int'
DFITCStockRspQryPositionField['dilutedFloatProfitLoss'] = 'float'
DFITCStockRspQryPositionField['dilutedBreakevenPrice'] = 'float'
DFITCStockRspQryPositionField['dilutedCost'] = 'float'
DFITCStockRspQryPositionField['avgPositionPrice'] = 'float'
DFITCStockRspQryPositionField['floatProfitLoss'] = 'float'
DFITCStockRspQryPositionField['dividend'] = 'float'
DFITCStockRspQryPositionField['totalFloatProfitLoss'] = 'float'
DFITCStockRspQryPositionField['sellAmount'] = 'float'
DFITCStockRspQryPositionField['buyAmount'] = 'float'
DFITCStockRspQryPositionField['buyAvgPrice'] = 'float'
DFITCStockRspQryPositionField['rationedSharesAmount'] = 'float'
DFITCStockRspQryPositionField['latestMarket'] = 'float'
DFITCStockRspQryPositionField['breakevenPrice'] = 'float'
DFITCStockRspQryPositionField['latestPrice'] = 'float'
DFITCStockRspQryPositionField['nonCirculateMarket'] = 'float'
DFITCStockRspQryPositionField['interestQuote'] = 'float'
DFITCStockRspQryPositionField['preClosePrice'] = 'float'


#STOCK-客户资金查询请求
DFITCStockReqQryCapitalAccountField = OrderedDict()

DFITCStockReqQryCapitalAccountField['requestID'] = 'long'
DFITCStockReqQryCapitalAccountField['accountID'] = 'string'
DFITCStockReqQryCapitalAccountField['FundsQryFlag'] = 'int'


#STOCK-客户资金查询响应
DFITCStockRspQryCapitalAccountField = OrderedDict()

DFITCStockRspQryCapitalAccountField['requestID'] = 'long'
DFITCStockRspQryCapitalAccountField['currency'] = 'string'
DFITCStockRspQryCapitalAccountField['availableFunds'] = 'float'
DFITCStockRspQryCapitalAccountField['t2AvailableFunds'] = 'float'
DFITCStockRspQryCapitalAccountField['anticipatedInterest'] = 'float'
DFITCStockRspQryCapitalAccountField['accountBalance'] = 'float'
DFITCStockRspQryCapitalAccountField['accountStatus'] = 'int'
DFITCStockRspQryCapitalAccountField['accountID'] = 'string'
DFITCStockRspQryCapitalAccountField['freezeFunds'] = 'float'
DFITCStockRspQryCapitalAccountField['t2FreezeFunds'] = 'float'
DFITCStockRspQryCapitalAccountField['branchID'] = 'string'
DFITCStockRspQryCapitalAccountField['totalFunds'] = 'float'
DFITCStockRspQryCapitalAccountField['totalMarket'] = 'float'


#STOCK-客户信息查询请求
DFITCStockReqQryAccountField = OrderedDict()

DFITCStockReqQryAccountField['requestID'] = 'long'
DFITCStockReqQryAccountField['accountID'] = 'string'


#STOCK-客户信息查询响应
DFITCStockRspQryAccountField = OrderedDict()

DFITCStockRspQryAccountField['requestID'] = 'long'
DFITCStockRspQryAccountField['tel'] = 'string'
DFITCStockRspQryAccountField['accountID'] = 'string'
DFITCStockRspQryAccountField['accountName'] = 'string'
DFITCStockRspQryAccountField['accountIdentityID'] = 'string'
DFITCStockRspQryAccountField['accountIdentityType'] = 'int'
DFITCStockRspQryAccountField['branchID'] = 'string'
DFITCStockRspQryAccountField['branchType'] = 'int'
DFITCStockRspQryAccountField['mobile'] = 'string'
DFITCStockRspQryAccountField['entrustType'] = 'int'
DFITCStockRspQryAccountField['accountStatus'] = 'int'
DFITCStockRspQryAccountField['pwdSynFlag'] = 'int'


#STOCK-股东信息查询请求
DFITCStockReqQryShareholderField = OrderedDict()

DFITCStockReqQryShareholderField['requestID'] = 'long'
DFITCStockReqQryShareholderField['accountID'] = 'string'
DFITCStockReqQryShareholderField['exchangeID'] = 'string'


#STOCK-股东信息查询响应
DFITCStockRspQryShareholderField = OrderedDict()

DFITCStockRspQryShareholderField['requestID'] = 'long'
DFITCStockRspQryShareholderField['account'] = 'string'
DFITCStockRspQryShareholderField['shareholderID'] = 'string'
DFITCStockRspQryShareholderField['shareholderSpecProp'] = 'int'
DFITCStockRspQryShareholderField['tradePermissions'] = 'int'
DFITCStockRspQryShareholderField['exchangeID'] = 'string'
DFITCStockRspQryShareholderField['shareholderStatus'] = 'int'
DFITCStockRspQryShareholderField['mainAccountFlag'] = 'int'
DFITCStockRspQryShareholderField['shareholderCtlProp'] = 'int'
DFITCStockRspQryShareholderField['branchID'] = 'string'
DFITCStockRspQryShareholderField['shareholderType'] = 'int'


#STOCK-资金调转请求
DFITCStockReqTransferFundsField = OrderedDict()

DFITCStockReqTransferFundsField['requestID'] = 'long'
DFITCStockReqTransferFundsField['accountID'] = 'string'
DFITCStockReqTransferFundsField['currency'] = 'string'
DFITCStockReqTransferFundsField['summaryMsg'] = 'string'
DFITCStockReqTransferFundsField['operateFunds'] = 'float'
DFITCStockReqTransferFundsField['fundsTransFlag'] = 'int'


#STOCK-资金调转响应
DFITCStockRspTransferFundsField = OrderedDict()

DFITCStockRspTransferFundsField['requestID'] = 'long'
DFITCStockRspTransferFundsField['accountID'] = 'string'
DFITCStockRspTransferFundsField['serialID'] = 'int'
DFITCStockRspTransferFundsField['accountBanlance'] = 'float'
DFITCStockRspTransferFundsField['availableFunds'] = 'float'
DFITCStockRspTransferFundsField['t2AvailableFunds'] = 'float'
DFITCStockRspTransferFundsField['fundsTransFlag'] = 'int'


#STOCK-批量委托请求
DFITCStockReqEntrustBatchOrderField = OrderedDict()

DFITCStockReqEntrustBatchOrderField['requestID'] = 'long'
DFITCStockReqEntrustBatchOrderField['localOrderID'] = 'long'
DFITCStockReqEntrustBatchOrderField['accountID'] = 'string'
DFITCStockReqEntrustBatchOrderField['entrustCount'] = 'int'
DFITCStockReqEntrustBatchOrderField['entrustDetail'] = 'string'
DFITCStockReqEntrustBatchOrderField['entrustBatchID'] = 'int'


#STOCK-批量委托响应
DFITCStockRspEntrustBatchOrderField = OrderedDict()

DFITCStockRspEntrustBatchOrderField['requestID'] = 'long'
DFITCStockRspEntrustBatchOrderField['accountID'] = 'string'
DFITCStockRspEntrustBatchOrderField['localOrderID'] = 'long'
DFITCStockRspEntrustBatchOrderField['orderRangeID'] = 'string'
DFITCStockRspEntrustBatchOrderField['entrustBatchID'] = 'int'
DFITCStockRspEntrustBatchOrderField['sucEntrustCount'] = 'int'


#STOCK-批量撤单请求
DFITCStockReqWithdrawBatchOrderField = OrderedDict()

DFITCStockReqWithdrawBatchOrderField['requestID'] = 'long'
DFITCStockReqWithdrawBatchOrderField['accountID'] = 'string'
DFITCStockReqWithdrawBatchOrderField['orderRangeID'] = 'string'
DFITCStockReqWithdrawBatchOrderField['entrustBatchID'] = 'int'


#STOCK-批量撤单响应
DFITCStockRspWithdrawBatchOrderField = OrderedDict()

DFITCStockRspWithdrawBatchOrderField['requestID'] = 'long'
DFITCStockRspWithdrawBatchOrderField['accountID'] = 'string'
DFITCStockRspWithdrawBatchOrderField['result'] = 'int'


#STOCK-计算可委托数量请求
DFITCStockReqCalcAbleEntrustQtyField = OrderedDict()

DFITCStockReqCalcAbleEntrustQtyField['requestID'] = 'long'
DFITCStockReqCalcAbleEntrustQtyField['exchangeID'] = 'string'
DFITCStockReqCalcAbleEntrustQtyField['accountID'] = 'string'
DFITCStockReqCalcAbleEntrustQtyField['entrustPrice'] = 'float'
DFITCStockReqCalcAbleEntrustQtyField['entrustDirection'] = 'int'
DFITCStockReqCalcAbleEntrustQtyField['securityID'] = 'string'
DFITCStockReqCalcAbleEntrustQtyField['orderType'] = 'int'


#STOCK-计算可委托数量响应
DFITCStockRspCalcAbleEntrustQtyField = OrderedDict()

DFITCStockRspCalcAbleEntrustQtyField['requestID'] = 'long'
DFITCStockRspCalcAbleEntrustQtyField['accountID'] = 'string'
DFITCStockRspCalcAbleEntrustQtyField['exchangeID'] = 'string'
DFITCStockRspCalcAbleEntrustQtyField['securityID'] = 'string'
DFITCStockRspCalcAbleEntrustQtyField['ableEntrustQty'] = 'int'


#STOCK-计算可买入ETF股票篮数请求
DFITCStockReqCalcAblePurchaseETFQtyField = OrderedDict()

DFITCStockReqCalcAblePurchaseETFQtyField['requestID'] = 'long'
DFITCStockReqCalcAblePurchaseETFQtyField['exchangeID'] = 'string'
DFITCStockReqCalcAblePurchaseETFQtyField['accountID'] = 'string'
DFITCStockReqCalcAblePurchaseETFQtyField['securityID'] = 'string'


#STOCK-计算可买入ETF股票篮数响应
DFITCStockRspCalcAblePurchaseETFQtyField = OrderedDict()

DFITCStockRspCalcAblePurchaseETFQtyField['requestID'] = 'long'
DFITCStockRspCalcAblePurchaseETFQtyField['accountID'] = 'string'
DFITCStockRspCalcAblePurchaseETFQtyField['exchangeID'] = 'string'
DFITCStockRspCalcAblePurchaseETFQtyField['securityID'] = 'string'
DFITCStockRspCalcAblePurchaseETFQtyField['ablePurchaseETFQty'] = 'int'


#STOCK-资金冻结明细查询请求
DFITCStockReqQryFreezeFundsDetailField = OrderedDict()

DFITCStockReqQryFreezeFundsDetailField['requestID'] = 'long'
DFITCStockReqQryFreezeFundsDetailField['currency'] = 'string'
DFITCStockReqQryFreezeFundsDetailField['fundsFreezeType'] = 'int'
DFITCStockReqQryFreezeFundsDetailField['accountID'] = 'string'
DFITCStockReqQryFreezeFundsDetailField['serialID'] = 'int'


#STOCK-资金冻结明细查询响应
DFITCStockRspQryFreezeFundsDetailField = OrderedDict()

DFITCStockRspQryFreezeFundsDetailField['requestID'] = 'long'
DFITCStockRspQryFreezeFundsDetailField['accountID'] = 'string'
DFITCStockRspQryFreezeFundsDetailField['currency'] = 'string'
DFITCStockRspQryFreezeFundsDetailField['fundsFreezeType'] = 'int'
DFITCStockRspQryFreezeFundsDetailField['accountName'] = 'string'
DFITCStockRspQryFreezeFundsDetailField['summaryMsg'] = 'string'
DFITCStockRspQryFreezeFundsDetailField['serialID'] = 'int'
DFITCStockRspQryFreezeFundsDetailField['operatorFunds'] = 'float'
DFITCStockRspQryFreezeFundsDetailField['operatorTime'] = 'string'
DFITCStockRspQryFreezeFundsDetailField['branchID'] = 'string'
DFITCStockRspQryFreezeFundsDetailField['operatorDate'] = 'int'


#STOCK-证券冻结明细查询请求
DFITCStockReqQryFreezeStockDetailField = OrderedDict()

DFITCStockReqQryFreezeStockDetailField['requestID'] = 'long'
DFITCStockReqQryFreezeStockDetailField['stockFreezeType'] = 'int'
DFITCStockReqQryFreezeStockDetailField['exchangeID'] = 'string'
DFITCStockReqQryFreezeStockDetailField['accountID'] = 'string'
DFITCStockReqQryFreezeStockDetailField['securityID'] = 'string'
DFITCStockReqQryFreezeStockDetailField['serialID'] = 'int'


#STOCK-证券冻结明细查询响应
DFITCStockRspQryFreezeStockDetailField = OrderedDict()

DFITCStockRspQryFreezeStockDetailField['requestID'] = 'long'
DFITCStockRspQryFreezeStockDetailField['accountID'] = 'string'
DFITCStockRspQryFreezeStockDetailField['stockFreezeType'] = 'int'
DFITCStockRspQryFreezeStockDetailField['shareholderID'] = 'string'
DFITCStockRspQryFreezeStockDetailField['exchangeID'] = 'string'
DFITCStockRspQryFreezeStockDetailField['accountName'] = 'string'
DFITCStockRspQryFreezeStockDetailField['securityID'] = 'string'
DFITCStockRspQryFreezeStockDetailField['securityType'] = 'string'
DFITCStockRspQryFreezeStockDetailField['securityName'] = 'string'
DFITCStockRspQryFreezeStockDetailField['summaryMsg'] = 'string'
DFITCStockRspQryFreezeStockDetailField['serialID'] = 'int'
DFITCStockRspQryFreezeStockDetailField['operatorTime'] = 'string'
DFITCStockRspQryFreezeStockDetailField['branchID'] = 'string'
DFITCStockRspQryFreezeStockDetailField['operatorDate'] = 'int'
DFITCStockRspQryFreezeStockDetailField['operatorQty'] = 'int'


#STOCK-查询资金调拨明细请求
DFITCStockReqQryTransferFundsDetailField = OrderedDict()

DFITCStockReqQryTransferFundsDetailField['requestID'] = 'long'
DFITCStockReqQryTransferFundsDetailField['currency'] = 'string'
DFITCStockReqQryTransferFundsDetailField['fundsFreezeType'] = 'int'
DFITCStockReqQryTransferFundsDetailField['accountID'] = 'string'
DFITCStockReqQryTransferFundsDetailField['serialID'] = 'int'


#STOCK-资金调拨明细查询响应
DFITCStockRspQryTransferFundsDetailField = OrderedDict()

DFITCStockRspQryTransferFundsDetailField['requestID'] = 'long'
DFITCStockRspQryTransferFundsDetailField['accountID'] = 'string'
DFITCStockRspQryTransferFundsDetailField['currency'] = 'string'
DFITCStockRspQryTransferFundsDetailField['fundsFreezeType'] = 'int'
DFITCStockRspQryTransferFundsDetailField['accountName'] = 'string'
DFITCStockRspQryTransferFundsDetailField['summaryMsg'] = 'string'
DFITCStockRspQryTransferFundsDetailField['serialID'] = 'int'
DFITCStockRspQryTransferFundsDetailField['operatorFunds'] = 'float'
DFITCStockRspQryTransferFundsDetailField['operatorTime'] = 'string'
DFITCStockRspQryTransferFundsDetailField['branchID'] = 'string'
DFITCStockRspQryTransferFundsDetailField['operatorDate'] = 'int'


#STOCK-查询客户证券调拨明细请求
DFITCStockReqQryTransferStockDetailField = OrderedDict()

DFITCStockReqQryTransferStockDetailField['requestID'] = 'long'
DFITCStockReqQryTransferStockDetailField['accountID'] = 'string'
DFITCStockReqQryTransferStockDetailField['exchangeID'] = 'string'
DFITCStockReqQryTransferStockDetailField['stockFreezeType'] = 'int'
DFITCStockReqQryTransferStockDetailField['incQryIndex'] = 'string'
DFITCStockReqQryTransferStockDetailField['serialID'] = 'int'


#STOCK-查询客户证券调拨明细响应
DFITCStockRspQryTransferStockDetailField = OrderedDict()

DFITCStockRspQryTransferStockDetailField['requestID'] = 'long'
DFITCStockRspQryTransferStockDetailField['accountID'] = 'string'
DFITCStockRspQryTransferStockDetailField['accountName'] = 'string'
DFITCStockRspQryTransferStockDetailField['branchID'] = 'string'
DFITCStockRspQryTransferStockDetailField['operatorDate'] = 'int'
DFITCStockRspQryTransferStockDetailField['exchangeID'] = 'string'
DFITCStockRspQryTransferStockDetailField['stockFreezeType'] = 'int'
DFITCStockRspQryTransferStockDetailField['securityID'] = 'string'
DFITCStockRspQryTransferStockDetailField['serialID'] = 'int'
DFITCStockRspQryTransferStockDetailField['shareholderID'] = 'string'
DFITCStockRspQryTransferStockDetailField['summaryMsg'] = 'string'
DFITCStockRspQryTransferStockDetailField['operatorTime'] = 'string'
DFITCStockRspQryTransferStockDetailField['operatorQty'] = 'int'


#STOCK-证券信息查询请求
DFITCStockReqQryStockField = OrderedDict()

DFITCStockReqQryStockField['requestID'] = 'long'
DFITCStockReqQryStockField['accountID'] = 'string'
DFITCStockReqQryStockField['exchangeID'] = 'string'
DFITCStockReqQryStockField['securityID'] = 'string'


#STOCK-证券信息查询响应
DFITCStockRspQryStockField = OrderedDict()

DFITCStockRspQryStockField['requestID'] = 'long'
DFITCStockRspQryStockField['accountID'] = 'string'
DFITCStockRspQryStockField['stopFlag'] = 'int'
DFITCStockRspQryStockField['latestPrice'] = 'float'
DFITCStockRspQryStockField['preClosePrice'] = 'float'
DFITCStockRspQryStockField['openPrice'] = 'float'
DFITCStockRspQryStockField['tradeQty'] = 'long'
DFITCStockRspQryStockField['turnover'] = 'float'
DFITCStockRspQryStockField['priceHigher'] = 'float'
DFITCStockRspQryStockField['priceLower'] = 'float'
DFITCStockRspQryStockField['bidPrice1'] = 'float'
DFITCStockRspQryStockField['bidQty1'] = 'int'
DFITCStockRspQryStockField['askPrice1'] = 'float'
DFITCStockRspQryStockField['askQty1'] = 'int'
DFITCStockRspQryStockField['bidPrice2'] = 'float'
DFITCStockRspQryStockField['bidQty2'] = 'int'
DFITCStockRspQryStockField['askPrice2'] = 'float'
DFITCStockRspQryStockField['askQty2'] = 'int'
DFITCStockRspQryStockField['bidPrice3'] = 'float'
DFITCStockRspQryStockField['bidQty3'] = 'int'
DFITCStockRspQryStockField['askPrice3'] = 'float'
DFITCStockRspQryStockField['askQty3'] = 'int'
DFITCStockRspQryStockField['bidPrice4'] = 'float'
DFITCStockRspQryStockField['bidQty4'] = 'int'
DFITCStockRspQryStockField['askPrice4'] = 'float'
DFITCStockRspQryStockField['askQty4'] = 'int'
DFITCStockRspQryStockField['bidPrice5'] = 'float'
DFITCStockRspQryStockField['bidQty5'] = 'int'
DFITCStockRspQryStockField['askPrice5'] = 'float'
DFITCStockRspQryStockField['askQty5'] = 'int'
DFITCStockRspQryStockField['exchangeID'] = 'string'
DFITCStockRspQryStockField['securityID'] = 'string'
DFITCStockRspQryStockField['interestQuote'] = 'float'
DFITCStockRspQryStockField['securityFaceValue'] = 'float'
DFITCStockRspQryStockField['bidTradeFlag'] = 'int'
DFITCStockRspQryStockField['tradeUnit'] = 'int'
DFITCStockRspQryStockField['businessLimit'] = 'int'
DFITCStockRspQryStockField['securityType'] = 'string'
DFITCStockRspQryStockField['securityName'] = 'string'
DFITCStockRspQryStockField['upperLimitPrice'] = 'float'
DFITCStockRspQryStockField['lowerLimitPrice'] = 'float'
DFITCStockRspQryStockField['currency'] = 'string'
DFITCStockRspQryStockField['orderLimits'] = 'string'


#STOCK-查询交易时间请求
DFITCStockReqQryTradeTimeField = OrderedDict()

DFITCStockReqQryTradeTimeField['requestID'] = 'long'
DFITCStockReqQryTradeTimeField['accountID'] = 'string'


#STOCK-查询交易时间响应
DFITCStockRspQryTradeTimeField = OrderedDict()

DFITCStockRspQryTradeTimeField['requestID'] = 'long'
DFITCStockRspQryTradeTimeField['accountID'] = 'string'
DFITCStockRspQryTradeTimeField['sysTradingDay'] = 'int'
DFITCStockRspQryTradeTimeField['sysTime'] = 'string'


#STOCK-委托回报
DFITCStockEntrustOrderRtnField = OrderedDict()

DFITCStockEntrustOrderRtnField['localOrderID'] = 'long'
DFITCStockEntrustOrderRtnField['accountID'] = 'string'
DFITCStockEntrustOrderRtnField['sessionID'] = 'long'
DFITCStockEntrustOrderRtnField['shareholderID'] = 'string'
DFITCStockEntrustOrderRtnField['exchangeID'] = 'string'
DFITCStockEntrustOrderRtnField['currency'] = 'string'
DFITCStockEntrustOrderRtnField['securityID'] = 'string'
DFITCStockEntrustOrderRtnField['securityType'] = 'string'
DFITCStockEntrustOrderRtnField['withdrawQty'] = 'int'
DFITCStockEntrustOrderRtnField['withdrawFlag'] = 'string'
DFITCStockEntrustOrderRtnField['freezeFunds'] = 'float'
DFITCStockEntrustOrderRtnField['spdOrderID'] = 'int'
DFITCStockEntrustOrderRtnField['entrustDirection'] = 'int'
DFITCStockEntrustOrderRtnField['declareResult'] = 'int'
DFITCStockEntrustOrderRtnField['noteMsg'] = 'string'
DFITCStockEntrustOrderRtnField['entrustQty'] = 'int'
DFITCStockEntrustOrderRtnField['orderConfirmFlag'] = 'int'
DFITCStockEntrustOrderRtnField['entrustTime'] = 'string'
DFITCStockEntrustOrderRtnField['entrustPrice'] = 'float'
DFITCStockEntrustOrderRtnField['orderType'] = 'int'


#STOCK-成交回报
DFITCStockTradeRtnField = OrderedDict()

DFITCStockTradeRtnField['localOrderID'] = 'long'
DFITCStockTradeRtnField['accountID'] = 'string'
DFITCStockTradeRtnField['sessionID'] = 'long'
DFITCStockTradeRtnField['shareholderID'] = 'string'
DFITCStockTradeRtnField['exchangeID'] = 'string'
DFITCStockTradeRtnField['currency'] = 'string'
DFITCStockTradeRtnField['securityID'] = 'string'
DFITCStockTradeRtnField['securityType'] = 'string'
DFITCStockTradeRtnField['withdrawFlag'] = 'string'
DFITCStockTradeRtnField['tradeID'] = 'string'
DFITCStockTradeRtnField['tradeTime'] = 'string'
DFITCStockTradeRtnField['withdrawQty'] = 'int'
DFITCStockTradeRtnField['spdOrderID'] = 'int'
DFITCStockTradeRtnField['entrustDirection'] = 'int'
DFITCStockTradeRtnField['clearFunds'] = 'float'
DFITCStockTradeRtnField['totalTradeQty'] = 'int'
DFITCStockTradeRtnField['totalTurnover'] = 'float'
DFITCStockTradeRtnField['tradeQty'] = 'int'
DFITCStockTradeRtnField['tradePrice'] = 'float'
DFITCStockTradeRtnField['turnover'] = 'float'
DFITCStockTradeRtnField['entrustQty'] = 'int'
DFITCStockTradeRtnField['declareResult'] = 'int'
DFITCStockTradeRtnField['noteMsg'] = 'string'


#STOCK-撤单回报
DFITCStockWithdrawOrderRtnField = OrderedDict()

DFITCStockWithdrawOrderRtnField['localOrderID'] = 'long'
DFITCStockWithdrawOrderRtnField['accountID'] = 'string'
DFITCStockWithdrawOrderRtnField['sessionID'] = 'long'
DFITCStockWithdrawOrderRtnField['shareholderID'] = 'string'
DFITCStockWithdrawOrderRtnField['exchangeID'] = 'string'
DFITCStockWithdrawOrderRtnField['currency'] = 'string'
DFITCStockWithdrawOrderRtnField['securityID'] = 'string'
DFITCStockWithdrawOrderRtnField['securityType'] = 'string'
DFITCStockWithdrawOrderRtnField['withdrawQty'] = 'int'
DFITCStockWithdrawOrderRtnField['tradeQty'] = 'int'
DFITCStockWithdrawOrderRtnField['withdrawFlag'] = 'string'
DFITCStockWithdrawOrderRtnField['freezeFunds'] = 'float'
DFITCStockWithdrawOrderRtnField['spdOrderID'] = 'int'
DFITCStockWithdrawOrderRtnField['entrustDirection'] = 'int'
DFITCStockWithdrawOrderRtnField['entrustQty'] = 'int'
DFITCStockWithdrawOrderRtnField['declareResult'] = 'int'
DFITCStockWithdrawOrderRtnField['noteMsg'] = 'string'


#SOP-委托请求
DFITCSOPReqEntrustOrderField = OrderedDict()

DFITCSOPReqEntrustOrderField['requestID'] = 'long'
DFITCSOPReqEntrustOrderField['localOrderID'] = 'long'
DFITCSOPReqEntrustOrderField['accountID'] = 'string'
DFITCSOPReqEntrustOrderField['exchangeID'] = 'string'
DFITCSOPReqEntrustOrderField['securityID'] = 'string'
DFITCSOPReqEntrustOrderField['subAccountID'] = 'string'
DFITCSOPReqEntrustOrderField['entrustQty'] = 'int'
DFITCSOPReqEntrustOrderField['entrustPrice'] = 'float'
DFITCSOPReqEntrustOrderField['entrustDirection'] = 'int'
DFITCSOPReqEntrustOrderField['openCloseFlag'] = 'int'
DFITCSOPReqEntrustOrderField['coveredFlag'] = 'int'
DFITCSOPReqEntrustOrderField['orderType'] = 'int'
DFITCSOPReqEntrustOrderField['orderExpiryDate'] = 'int'
DFITCSOPReqEntrustOrderField['orderCategory'] = 'int'
DFITCSOPReqEntrustOrderField['serialID'] = 'int'
DFITCSOPReqEntrustOrderField['devID'] = 'string'
DFITCSOPReqEntrustOrderField['devDecInfo'] = 'string'


#SOP-委托响应
DFITCSOPRspEntrustOrderField = OrderedDict()

DFITCSOPRspEntrustOrderField['requestID'] = 'long'
DFITCSOPRspEntrustOrderField['accountID'] = 'string'
DFITCSOPRspEntrustOrderField['localOrderID'] = 'long'
DFITCSOPRspEntrustOrderField['spdOrderID'] = 'int'
DFITCSOPRspEntrustOrderField['entrustTime'] = 'string'
DFITCSOPRspEntrustOrderField['freezeFunds'] = 'float'


#SOP-委托回报
DFITCSOPEntrustOrderRtnField = OrderedDict()

DFITCSOPEntrustOrderRtnField['localOrderID'] = 'long'
DFITCSOPEntrustOrderRtnField['accountID'] = 'string'
DFITCSOPEntrustOrderRtnField['sessionID'] = 'long'
DFITCSOPEntrustOrderRtnField['branchID'] = 'string'
DFITCSOPEntrustOrderRtnField['shareholderID'] = 'string'
DFITCSOPEntrustOrderRtnField['exchangeID'] = 'string'
DFITCSOPEntrustOrderRtnField['securityID'] = 'string'
DFITCSOPEntrustOrderRtnField['withdrawFlag'] = 'string'
DFITCSOPEntrustOrderRtnField['currency'] = 'string'
DFITCSOPEntrustOrderRtnField['spdOrderID'] = 'int'
DFITCSOPEntrustOrderRtnField['entrustDirection'] = 'int'
DFITCSOPEntrustOrderRtnField['openCloseFlag'] = 'int'
DFITCSOPEntrustOrderRtnField['entrustPrice'] = 'float'
DFITCSOPEntrustOrderRtnField['entrustQty'] = 'int'
DFITCSOPEntrustOrderRtnField['entrustTime'] = 'string'
DFITCSOPEntrustOrderRtnField['coveredFlag'] = 'int'
DFITCSOPEntrustOrderRtnField['orderType'] = 'int'
DFITCSOPEntrustOrderRtnField['orderExpiryDate'] = 'int'
DFITCSOPEntrustOrderRtnField['orderCategory'] = 'int'
DFITCSOPEntrustOrderRtnField['declareResult'] = 'int'
DFITCSOPEntrustOrderRtnField['noteMsg'] = 'string'
DFITCSOPEntrustOrderRtnField['devID'] = 'string'
DFITCSOPEntrustOrderRtnField['devDecInfo'] = 'string'


#SOP-成交回报
DFITCSOPTradeRtnField = OrderedDict()

DFITCSOPTradeRtnField['localOrderID'] = 'long'
DFITCSOPTradeRtnField['accountID'] = 'string'
DFITCSOPTradeRtnField['sessionID'] = 'long'
DFITCSOPTradeRtnField['shareholderID'] = 'string'
DFITCSOPTradeRtnField['exchangeID'] = 'string'
DFITCSOPTradeRtnField['securityID'] = 'string'
DFITCSOPTradeRtnField['withdrawFlag'] = 'string'
DFITCSOPTradeRtnField['currency'] = 'string'
DFITCSOPTradeRtnField['spdOrderID'] = 'int'
DFITCSOPTradeRtnField['entrustDirection'] = 'int'
DFITCSOPTradeRtnField['openCloseFlag'] = 'int'
DFITCSOPTradeRtnField['coveredFlag'] = 'int'
DFITCSOPTradeRtnField['orderCategory'] = 'int'
DFITCSOPTradeRtnField['tradePrice'] = 'float'
DFITCSOPTradeRtnField['tradeQty'] = 'int'
DFITCSOPTradeRtnField['tradeID'] = 'string'
DFITCSOPTradeRtnField['rtnSerialID'] = 'int'
DFITCSOPTradeRtnField['declareOrderID'] = 'string'
DFITCSOPTradeRtnField['declareResult'] = 'int'
DFITCSOPTradeRtnField['noteMsg'] = 'string'
DFITCSOPTradeRtnField['devID'] = 'string'
DFITCSOPTradeRtnField['devDecInfo'] = 'string'
DFITCSOPTradeRtnField['tradeTime'] = 'string'


#SOP-撤单回报
DFITCSOPWithdrawOrderRtnField = OrderedDict()

DFITCSOPWithdrawOrderRtnField['localOrderID'] = 'long'
DFITCSOPWithdrawOrderRtnField['accountID'] = 'string'
DFITCSOPWithdrawOrderRtnField['sessionID'] = 'long'
DFITCSOPWithdrawOrderRtnField['shareholderID'] = 'string'
DFITCSOPWithdrawOrderRtnField['exchangeID'] = 'string'
DFITCSOPWithdrawOrderRtnField['securityID'] = 'string'
DFITCSOPWithdrawOrderRtnField['withdrawFlag'] = 'string'
DFITCSOPWithdrawOrderRtnField['currency'] = 'string'
DFITCSOPWithdrawOrderRtnField['spdOrderID'] = 'int'
DFITCSOPWithdrawOrderRtnField['entrustDirection'] = 'int'
DFITCSOPWithdrawOrderRtnField['openCloseFlag'] = 'int'
DFITCSOPWithdrawOrderRtnField['withdrawQty'] = 'int'
DFITCSOPWithdrawOrderRtnField['tradeQty'] = 'int'
DFITCSOPWithdrawOrderRtnField['declareResult'] = 'int'
DFITCSOPWithdrawOrderRtnField['noteMsg'] = 'string'
DFITCSOPWithdrawOrderRtnField['wdUnFreezeFunds'] = 'float'
DFITCSOPWithdrawOrderRtnField['devID'] = 'string'
DFITCSOPWithdrawOrderRtnField['devDecInfo'] = 'string'


#SOP-证券锁定解锁委托请求
DFITCSOPReqLockOUnLockStockField = OrderedDict()

DFITCSOPReqLockOUnLockStockField['requestID'] = 'long'
DFITCSOPReqLockOUnLockStockField['localOrderID'] = 'long'
DFITCSOPReqLockOUnLockStockField['accountID'] = 'string'
DFITCSOPReqLockOUnLockStockField['exchangeID'] = 'string'
DFITCSOPReqLockOUnLockStockField['subAccountID'] = 'string'
DFITCSOPReqLockOUnLockStockField['securityID'] = 'string'
DFITCSOPReqLockOUnLockStockField['entrustQty'] = 'int'
DFITCSOPReqLockOUnLockStockField['openCloseFlag'] = 'int'
DFITCSOPReqLockOUnLockStockField['devID'] = 'string'
DFITCSOPReqLockOUnLockStockField['devDecInfo'] = 'string'


#SOP-证券锁定解锁委托响应
DFITCSOPRspLockOUnLockStockField = OrderedDict()

DFITCSOPRspLockOUnLockStockField['requestID'] = 'long'
DFITCSOPRspLockOUnLockStockField['accountID'] = 'string'
DFITCSOPRspLockOUnLockStockField['localOrderID'] = 'long'
DFITCSOPRspLockOUnLockStockField['spdOrderID'] = 'int'
DFITCSOPRspLockOUnLockStockField['entrustTime'] = 'string'
DFITCSOPRspLockOUnLockStockField['freezeFunds'] = 'float'


#SOP-分笔成交查询请求
DFITCSOPReqQrySerialTradeField = OrderedDict()

DFITCSOPReqQrySerialTradeField['requestID'] = 'long'
DFITCSOPReqQrySerialTradeField['accountID'] = 'string'
DFITCSOPReqQrySerialTradeField['exchangeID'] = 'string'
DFITCSOPReqQrySerialTradeField['securityID'] = 'string'
DFITCSOPReqQrySerialTradeField['spdOrderID'] = 'int'
DFITCSOPReqQrySerialTradeField['incQryIndex'] = 'string'
DFITCSOPReqQrySerialTradeField['entrustDirection'] = 'int'
DFITCSOPReqQrySerialTradeField['entrustBatchID'] = 'int'
DFITCSOPReqQrySerialTradeField['tradeQryFlag'] = 'int'
DFITCSOPReqQrySerialTradeField['currency'] = 'string'
DFITCSOPReqQrySerialTradeField['rowIndex'] = 'int'
DFITCSOPReqQrySerialTradeField['rowCount'] = 'int'


#SOP-分笔成交查询响应
DFITCSOPRspQrySerialTradeField = OrderedDict()

DFITCSOPRspQrySerialTradeField['requestID'] = 'long'
DFITCSOPRspQrySerialTradeField['accountID'] = 'string'
DFITCSOPRspQrySerialTradeField['exchangeID'] = 'string'
DFITCSOPRspQrySerialTradeField['rtnSerialID'] = 'int'
DFITCSOPRspQrySerialTradeField['securityID'] = 'string'
DFITCSOPRspQrySerialTradeField['entrustDirection'] = 'int'
DFITCSOPRspQrySerialTradeField['withdrawFlag'] = 'string'
DFITCSOPRspQrySerialTradeField['declareOrderID'] = 'string'
DFITCSOPRspQrySerialTradeField['currency'] = 'string'
DFITCSOPRspQrySerialTradeField['tradeID'] = 'string'
DFITCSOPRspQrySerialTradeField['tradeTime'] = 'string'
DFITCSOPRspQrySerialTradeField['tradeQty'] = 'int'
DFITCSOPRspQrySerialTradeField['openCloseFlag'] = 'int'
DFITCSOPRspQrySerialTradeField['coveredFlag'] = 'int'
DFITCSOPRspQrySerialTradeField['spdOrderID'] = 'int'
DFITCSOPRspQrySerialTradeField['turnover'] = 'float'
DFITCSOPRspQrySerialTradeField['tradePrice'] = 'float'
DFITCSOPRspQrySerialTradeField['clearFunds'] = 'float'
DFITCSOPRspQrySerialTradeField['rotationTime'] = 'string'
DFITCSOPRspQrySerialTradeField['incQryIndex'] = 'string'
DFITCSOPRspQrySerialTradeField['shareholderID'] = 'string'
DFITCSOPRspQrySerialTradeField['capitalID'] = 'string'
DFITCSOPRspQrySerialTradeField['devID'] = 'string'
DFITCSOPRspQrySerialTradeField['devDecInfo'] = 'string'


#SOP-委托查询请求
DFITCSOPReqQryEntrustOrderField = OrderedDict()

DFITCSOPReqQryEntrustOrderField['requestID'] = 'long'
DFITCSOPReqQryEntrustOrderField['accountID'] = 'string'
DFITCSOPReqQryEntrustOrderField['exchangeID'] = 'string'
DFITCSOPReqQryEntrustOrderField['securityOptionID'] = 'string'
DFITCSOPReqQryEntrustOrderField['withdrawFlag'] = 'string'
DFITCSOPReqQryEntrustOrderField['exSerialID'] = 'int'
DFITCSOPReqQryEntrustOrderField['entrustDirection'] = 'int'
DFITCSOPReqQryEntrustOrderField['spdOrderID'] = 'int'
DFITCSOPReqQryEntrustOrderField['entrustQryFlag'] = 'int'
DFITCSOPReqQryEntrustOrderField['rowIndex'] = 'int'
DFITCSOPReqQryEntrustOrderField['rowCount'] = 'int'


#SOP-委托查询响应
DFITCSOPRspQryEntrustOrderField = OrderedDict()

DFITCSOPRspQryEntrustOrderField['requestID'] = 'long'
DFITCSOPRspQryEntrustOrderField['accountID'] = 'string'
DFITCSOPRspQryEntrustOrderField['spdOrderID'] = 'int'
DFITCSOPRspQryEntrustOrderField['withdrawOrderID'] = 'string'
DFITCSOPRspQryEntrustOrderField['declareOrderID'] = 'string'
DFITCSOPRspQryEntrustOrderField['exchangeID'] = 'string'
DFITCSOPRspQryEntrustOrderField['shareholderID'] = 'string'
DFITCSOPRspQryEntrustOrderField['entrustDirection'] = 'int'
DFITCSOPRspQryEntrustOrderField['withdrawFlag'] = 'string'
DFITCSOPRspQryEntrustOrderField['securityOptionID'] = 'string'
DFITCSOPRspQryEntrustOrderField['optType'] = 'int'
DFITCSOPRspQryEntrustOrderField['openCloseFlag'] = 'int'
DFITCSOPRspQryEntrustOrderField['coveredFlag'] = 'int'
DFITCSOPRspQryEntrustOrderField['entrustQty'] = 'int'
DFITCSOPRspQryEntrustOrderField['entrustPrice'] = 'float'
DFITCSOPRspQryEntrustOrderField['entrustDate'] = 'int'
DFITCSOPRspQryEntrustOrderField['entrustTime'] = 'string'
DFITCSOPRspQryEntrustOrderField['offerShareholderID'] = 'string'
DFITCSOPRspQryEntrustOrderField['declareDate'] = 'int'
DFITCSOPRspQryEntrustOrderField['declareTime'] = 'string'
DFITCSOPRspQryEntrustOrderField['declareSerialID'] = 'int'
DFITCSOPRspQryEntrustOrderField['declareResult'] = 'int'
DFITCSOPRspQryEntrustOrderField['noteMsg'] = 'string'
DFITCSOPRspQryEntrustOrderField['withdrawQty'] = 'int'
DFITCSOPRspQryEntrustOrderField['tradeQty'] = 'int'
DFITCSOPRspQryEntrustOrderField['turnover'] = 'float'
DFITCSOPRspQryEntrustOrderField['tradePrice'] = 'float'
DFITCSOPRspQryEntrustOrderField['currency'] = 'string'
DFITCSOPRspQryEntrustOrderField['freezeFunds'] = 'float'
DFITCSOPRspQryEntrustOrderField['clearFunds'] = 'float'
DFITCSOPRspQryEntrustOrderField['entrustType'] = 'int'
DFITCSOPRspQryEntrustOrderField['macAddr'] = 'string'
DFITCSOPRspQryEntrustOrderField['ipAddr'] = 'string'
DFITCSOPRspQryEntrustOrderField['entrustBatchID'] = 'int'
DFITCSOPRspQryEntrustOrderField['orderType'] = 'int'
DFITCSOPRspQryEntrustOrderField['incQryIndex'] = 'string'
DFITCSOPRspQryEntrustOrderField['capitalID'] = 'string'
DFITCSOPRspQryEntrustOrderField['orderExpiryDate'] = 'int'
DFITCSOPRspQryEntrustOrderField['devID'] = 'string'
DFITCSOPRspQryEntrustOrderField['devDecInfo'] = 'string'


#SOP-持仓查询请求
DFITCSOPReqQryPositionField = OrderedDict()

DFITCSOPReqQryPositionField['requestID'] = 'long'
DFITCSOPReqQryPositionField['accountID'] = 'string'
DFITCSOPReqQryPositionField['exchangeID'] = 'string'
DFITCSOPReqQryPositionField['securityOptionID'] = 'string'
DFITCSOPReqQryPositionField['rowIndex'] = 'int'
DFITCSOPReqQryPositionField['rowCount'] = 'int'


#SOP-持仓查询响应
DFITCSOPRspQryPositionField = OrderedDict()

DFITCSOPRspQryPositionField['requestID'] = 'long'
DFITCSOPRspQryPositionField['accountID'] = 'string'
DFITCSOPRspQryPositionField['exchangeID'] = 'string'
DFITCSOPRspQryPositionField['subAccountID'] = 'string'
DFITCSOPRspQryPositionField['securityOptionID'] = 'string'
DFITCSOPRspQryPositionField['contractID'] = 'string'
DFITCSOPRspQryPositionField['contractName'] = 'string'
DFITCSOPRspQryPositionField['entrustDirection'] = 'int'
DFITCSOPRspQryPositionField['coveredFlag'] = 'int'
DFITCSOPRspQryPositionField['executeDate'] = 'int'
DFITCSOPRspQryPositionField['totalQty'] = 'int'
DFITCSOPRspQryPositionField['availableQty'] = 'int'
DFITCSOPRspQryPositionField['latestPrice'] = 'float'
DFITCSOPRspQryPositionField['optionMarket'] = 'float'
DFITCSOPRspQryPositionField['freezeQty'] = 'int'
DFITCSOPRspQryPositionField['executeQty'] = 'int'
DFITCSOPRspQryPositionField['openEntrustQty'] = 'int'
DFITCSOPRspQryPositionField['openTradeQty'] = 'int'
DFITCSOPRspQryPositionField['prePosition'] = 'int'
DFITCSOPRspQryPositionField['closeEntrustQty'] = 'int'
DFITCSOPRspQryPositionField['closeTradeQty'] = 'int'
DFITCSOPRspQryPositionField['deposit'] = 'float'
DFITCSOPRspQryPositionField['openDeposit'] = 'float'
DFITCSOPRspQryPositionField['closeDeposit'] = 'float'
DFITCSOPRspQryPositionField['exchangeDeposit'] = 'float'
DFITCSOPRspQryPositionField['exchangeOpenDeposit'] = 'float'
DFITCSOPRspQryPositionField['exchangeCloseDeposit'] = 'float'
DFITCSOPRspQryPositionField['openAvgPrice'] = 'float'
DFITCSOPRspQryPositionField['optType'] = 'int'
DFITCSOPRspQryPositionField['contractObjectType'] = 'int'
DFITCSOPRspQryPositionField['contractUnit'] = 'int'
DFITCSOPRspQryPositionField['currency'] = 'string'
DFITCSOPRspQryPositionField['totalTradeCost'] = 'float'
DFITCSOPRspQryPositionField['tradeCost'] = 'float'
DFITCSOPRspQryPositionField['realizeProfitLoss'] = 'float'
DFITCSOPRspQryPositionField['profitLoss'] = 'float'
DFITCSOPRspQryPositionField['adjustRemind'] = 'int'
DFITCSOPRspQryPositionField['expireRemind'] = 'int'


#SOP-客户担保持仓查询请求
DFITCSOPReqQryCollateralPositionField = OrderedDict()

DFITCSOPReqQryCollateralPositionField['requestID'] = 'long'
DFITCSOPReqQryCollateralPositionField['accountID'] = 'string'
DFITCSOPReqQryCollateralPositionField['exchangeID'] = 'string'
DFITCSOPReqQryCollateralPositionField['securityID'] = 'string'


#SOP-客户担保持仓查询响应
DFITCSOPRspQryCollateralPositionField = OrderedDict()

DFITCSOPRspQryCollateralPositionField['requestID'] = 'long'
DFITCSOPRspQryCollateralPositionField['exchangeID'] = 'string'
DFITCSOPRspQryCollateralPositionField['accountID'] = 'string'
DFITCSOPRspQryCollateralPositionField['securityID'] = 'string'
DFITCSOPRspQryCollateralPositionField['securityName'] = 'string'
DFITCSOPRspQryCollateralPositionField['availableQty'] = 'int'


#SOP-客户资金查询请求
DFITCSOPReqQryCapitalAccountField = OrderedDict()

DFITCSOPReqQryCapitalAccountField['requestID'] = 'long'
DFITCSOPReqQryCapitalAccountField['accountID'] = 'string'
DFITCSOPReqQryCapitalAccountField['currency'] = 'string'
DFITCSOPReqQryCapitalAccountField['FundsQryFlag'] = 'int'


#SOP-客户资金查询响应
DFITCSOPRspQryCapitalAccountField = OrderedDict()

DFITCSOPRspQryCapitalAccountField['requestID'] = 'long'
DFITCSOPRspQryCapitalAccountField['accountID'] = 'string'
DFITCSOPRspQryCapitalAccountField['branchID'] = 'string'
DFITCSOPRspQryCapitalAccountField['currency'] = 'string'
DFITCSOPRspQryCapitalAccountField['accountBanlance'] = 'float'
DFITCSOPRspQryCapitalAccountField['availableFunds'] = 'float'
DFITCSOPRspQryCapitalAccountField['freezeFunds'] = 'float'
DFITCSOPRspQryCapitalAccountField['anticipatedInterest'] = 'float'
DFITCSOPRspQryCapitalAccountField['usedDeposit'] = 'float'
DFITCSOPRspQryCapitalAccountField['accountStatus'] = 'int'
DFITCSOPRspQryCapitalAccountField['totalFunds'] = 'float'
DFITCSOPRspQryCapitalAccountField['totalMarket'] = 'float'
DFITCSOPRspQryCapitalAccountField['cashAssets'] = 'float'
DFITCSOPRspQryCapitalAccountField['execGuaranteeRatio'] = 'float'
DFITCSOPRspQryCapitalAccountField['buyLimits'] = 'float'


#SOP-客户信息查询请求
DFITCSOPReqQryAccountField = OrderedDict()

DFITCSOPReqQryAccountField['requestID'] = 'long'
DFITCSOPReqQryAccountField['accountID'] = 'string'


#SOP-客户信息查询响应
DFITCSOPRspQryAccountField = OrderedDict()

DFITCSOPRspQryAccountField['requestID'] = 'long'
DFITCSOPRspQryAccountField['accountID'] = 'string'
DFITCSOPRspQryAccountField['accountName'] = 'string'
DFITCSOPRspQryAccountField['accountFullName'] = 'string'
DFITCSOPRspQryAccountField['branchID'] = 'string'
DFITCSOPRspQryAccountField['identityType'] = 'int'
DFITCSOPRspQryAccountField['accountIdentityID'] = 'string'
DFITCSOPRspQryAccountField['tel'] = 'string'
DFITCSOPRspQryAccountField['mobile'] = 'string'
DFITCSOPRspQryAccountField['accountType'] = 'int'
DFITCSOPRspQryAccountField['accountProp'] = 'int'
DFITCSOPRspQryAccountField['tradePermissions'] = 'int'
DFITCSOPRspQryAccountField['entrustType'] = 'int'
DFITCSOPRspQryAccountField['accountStatus'] = 'int'
DFITCSOPRspQryAccountField['pwdSynFlag'] = 'int'
DFITCSOPRspQryAccountField['accountNodeID'] = 'int'


#SOP-可委托数量查询请求
DFITCSOPReqCalcAbleEntrustQtyField = OrderedDict()

DFITCSOPReqCalcAbleEntrustQtyField['requestID'] = 'long'
DFITCSOPReqCalcAbleEntrustQtyField['accountID'] = 'string'
DFITCSOPReqCalcAbleEntrustQtyField['exchangeID'] = 'string'
DFITCSOPReqCalcAbleEntrustQtyField['subAccountID'] = 'string'
DFITCSOPReqCalcAbleEntrustQtyField['securityOptionID'] = 'string'
DFITCSOPReqCalcAbleEntrustQtyField['entrustDirection'] = 'int'
DFITCSOPReqCalcAbleEntrustQtyField['openCloseFlag'] = 'int'
DFITCSOPReqCalcAbleEntrustQtyField['coveredFlag'] = 'int'
DFITCSOPReqCalcAbleEntrustQtyField['entrustPrice'] = 'float'
DFITCSOPReqCalcAbleEntrustQtyField['checkUpLimit'] = 'int'
DFITCSOPReqCalcAbleEntrustQtyField['devID'] = 'string'
DFITCSOPReqCalcAbleEntrustQtyField['devDecInfo'] = 'string'


#SOP-可委托数量查询响应
DFITCSOPRspCalcAbleEntrustQtyField = OrderedDict()

DFITCSOPRspCalcAbleEntrustQtyField['requestID'] = 'long'
DFITCSOPRspCalcAbleEntrustQtyField['accountID'] = 'string'
DFITCSOPRspCalcAbleEntrustQtyField['exchangeID'] = 'string'
DFITCSOPRspCalcAbleEntrustQtyField['securityOptionID'] = 'string'
DFITCSOPRspCalcAbleEntrustQtyField['entrustQty'] = 'int'


#SOP-股东信息查询请求
DFITCSOPReqQryShareholderField = OrderedDict()

DFITCSOPReqQryShareholderField['accountID'] = 'string'
DFITCSOPReqQryShareholderField['requestID'] = 'long'
DFITCSOPReqQryShareholderField['exchangeID'] = 'string'


#SOP-股东信息查询响应
DFITCSOPRspQryShareholderField = OrderedDict()

DFITCSOPRspQryShareholderField['requestID'] = 'long'
DFITCSOPRspQryShareholderField['accountID'] = 'string'
DFITCSOPRspQryShareholderField['branchID'] = 'string'
DFITCSOPRspQryShareholderField['currency'] = 'string'
DFITCSOPRspQryShareholderField['shareholderID'] = 'string'
DFITCSOPRspQryShareholderField['tradePermissions'] = 'int'
DFITCSOPRspQryShareholderField['shareholderSpecProp'] = 'int'
DFITCSOPRspQryShareholderField['shareholderCtlProp'] = 'int'
DFITCSOPRspQryShareholderField['shareholderStatus'] = 'int'
DFITCSOPRspQryShareholderField['mainAccountFlag'] = 'int'
DFITCSOPRspQryShareholderField['exchangeID'] = 'string'


#SOP-客户可锁定证券查询请求
DFITCSOPReqQryAbleLockStockField = OrderedDict()

DFITCSOPReqQryAbleLockStockField['requestID'] = 'long'
DFITCSOPReqQryAbleLockStockField['accountID'] = 'string'
DFITCSOPReqQryAbleLockStockField['exchangeID'] = 'string'
DFITCSOPReqQryAbleLockStockField['securityID'] = 'string'


#SOP-客户可锁定证券查询响应
DFITCSOPRspQryAbleLockStockField = OrderedDict()

DFITCSOPRspQryAbleLockStockField['requestID'] = 'long'
DFITCSOPRspQryAbleLockStockField['accountID'] = 'string'
DFITCSOPRspQryAbleLockStockField['exchangeID'] = 'string'
DFITCSOPRspQryAbleLockStockField['securityID'] = 'string'
DFITCSOPRspQryAbleLockStockField['securityName'] = 'string'
DFITCSOPRspQryAbleLockStockField['securityQty'] = 'int'
DFITCSOPRspQryAbleLockStockField['position'] = 'int'
DFITCSOPRspQryAbleLockStockField['avgPositionPrice'] = 'float'
DFITCSOPRspQryAbleLockStockField['dilutedCost'] = 'float'
DFITCSOPRspQryAbleLockStockField['breakevenPrice'] = 'float'
DFITCSOPRspQryAbleLockStockField['dilutedBreakevenPrice'] = 'float'
DFITCSOPRspQryAbleLockStockField['ableSellQty'] = 'int'
DFITCSOPRspQryAbleLockStockField['latestMarket'] = 'float'
DFITCSOPRspQryAbleLockStockField['latestPrice'] = 'float'
DFITCSOPRspQryAbleLockStockField['floatProfitLoss'] = 'float'
DFITCSOPRspQryAbleLockStockField['dilutedFloatProfitLoss'] = 'float'
DFITCSOPRspQryAbleLockStockField['tradeUnit'] = 'int'
DFITCSOPRspQryAbleLockStockField['openBuyQty'] = 'int'
DFITCSOPRspQryAbleLockStockField['openSellQty'] = 'int'
DFITCSOPRspQryAbleLockStockField['buyUnSettleQty'] = 'int'
DFITCSOPRspQryAbleLockStockField['sellUnSettleQty'] = 'int'
DFITCSOPRspQryAbleLockStockField['openEntrustSellQty'] = 'int'
DFITCSOPRspQryAbleLockStockField['ableLockQty'] = 'int'


#SOP-客户行权指派信息查询请求
DFITCSOPReqQryExecAssiInfoField = OrderedDict()

DFITCSOPReqQryExecAssiInfoField['requestID'] = 'long'
DFITCSOPReqQryExecAssiInfoField['accountID'] = 'string'
DFITCSOPReqQryExecAssiInfoField['securityOptionID'] = 'string'
DFITCSOPReqQryExecAssiInfoField['tradeDate'] = 'int'


#SOP-客户行权指派信息查询响应
DFITCSOPRspQryExecAssiInfoField = OrderedDict()

DFITCSOPRspQryExecAssiInfoField['requestID'] = 'long'
DFITCSOPRspQryExecAssiInfoField['accountID'] = 'string'
DFITCSOPRspQryExecAssiInfoField['tradeDate'] = 'int'
DFITCSOPRspQryExecAssiInfoField['branchID'] = 'string'
DFITCSOPRspQryExecAssiInfoField['shareholderID'] = 'string'
DFITCSOPRspQryExecAssiInfoField['subAccountID'] = 'string'
DFITCSOPRspQryExecAssiInfoField['exchangeID'] = 'string'
DFITCSOPRspQryExecAssiInfoField['currency'] = 'string'
DFITCSOPRspQryExecAssiInfoField['optType'] = 'int'
DFITCSOPRspQryExecAssiInfoField['contractObjectType'] = 'int'
DFITCSOPRspQryExecAssiInfoField['coveredFlag'] = 'int'
DFITCSOPRspQryExecAssiInfoField['securityOptionID'] = 'string'
DFITCSOPRspQryExecAssiInfoField['entrustDirection'] = 'int'
DFITCSOPRspQryExecAssiInfoField['securityID'] = 'string'
DFITCSOPRspQryExecAssiInfoField['seatID'] = 'string'
DFITCSOPRspQryExecAssiInfoField['execPrice'] = 'float'
DFITCSOPRspQryExecAssiInfoField['execQty'] = 'int'
DFITCSOPRspQryExecAssiInfoField['tradeQty'] = 'int'
DFITCSOPRspQryExecAssiInfoField['clearFunds'] = 'float'
DFITCSOPRspQryExecAssiInfoField['settleFunds'] = 'float'
DFITCSOPRspQryExecAssiInfoField['commission'] = 'float'
DFITCSOPRspQryExecAssiInfoField['stampTax'] = 'float'
DFITCSOPRspQryExecAssiInfoField['transferFee'] = 'float'
DFITCSOPRspQryExecAssiInfoField['fee3'] = 'float'
DFITCSOPRspQryExecAssiInfoField['fee4'] = 'float'
DFITCSOPRspQryExecAssiInfoField['summaryMsg'] = 'string'


#SOP-期权合约代码查询请求
DFITCSOPReqQryContactField = OrderedDict()

DFITCSOPReqQryContactField['requestID'] = 'long'
DFITCSOPReqQryContactField['accountID'] = 'string'
DFITCSOPReqQryContactField['exchangeID'] = 'string'
DFITCSOPReqQryContactField['securityOptionID'] = 'string'
DFITCSOPReqQryContactField['securityID'] = 'string'
DFITCSOPReqQryContactField['contractObjectType'] = 'int'
DFITCSOPReqQryContactField['optType'] = 'int'
DFITCSOPReqQryContactField['rowIndex'] = 'string'
DFITCSOPReqQryContactField['rowCount'] = 'int'


#SOP-期权合约代码查询响应
DFITCSOPRspQryContactField = OrderedDict()

DFITCSOPRspQryContactField['requestID'] = 'long'
DFITCSOPRspQryContactField['accountID'] = 'string'
DFITCSOPRspQryContactField['exchangeID'] = 'string'
DFITCSOPRspQryContactField['securityOptionID'] = 'string'
DFITCSOPRspQryContactField['contractID'] = 'string'
DFITCSOPRspQryContactField['contractName'] = 'string'
DFITCSOPRspQryContactField['securityID'] = 'string'
DFITCSOPRspQryContactField['contractObjectType'] = 'int'
DFITCSOPRspQryContactField['execType'] = 'int'
DFITCSOPRspQryContactField['deliType'] = 'int'
DFITCSOPRspQryContactField['optType'] = 'int'
DFITCSOPRspQryContactField['contactUnit'] = 'int'
DFITCSOPRspQryContactField['latestPrice'] = 'float'
DFITCSOPRspQryContactField['beginTradingDay'] = 'int'
DFITCSOPRspQryContactField['endTradingDay'] = 'int'
DFITCSOPRspQryContactField['execDate'] = 'int'
DFITCSOPRspQryContactField['endDate'] = 'int'
DFITCSOPRspQryContactField['positionUpLimit'] = 'int'
DFITCSOPRspQryContactField['priceUpLimit'] = 'float'
DFITCSOPRspQryContactField['priceDownLimit'] = 'float'
DFITCSOPRspQryContactField['priceHigher'] = 'float'
DFITCSOPRspQryContactField['priceLower'] = 'float'
DFITCSOPRspQryContactField['entrustUpLimit'] = 'int'
DFITCSOPRspQryContactField['entrustDownLimit'] = 'int'
DFITCSOPRspQryContactField['entrustUpLimitMarketPri'] = 'int'
DFITCSOPRspQryContactField['entrustDownLimitMarketPri'] = 'int'
DFITCSOPRspQryContactField['openLimit'] = 'int'
DFITCSOPRspQryContactField['stockTradeFlag'] = 'int'
DFITCSOPRspQryContactField['depositUnit'] = 'float'
DFITCSOPRspQryContactField['depositRatioC'] = 'float'
DFITCSOPRspQryContactField['depositRatioE'] = 'float'
DFITCSOPRspQryContactField['preClosePrice'] = 'float'
DFITCSOPRspQryContactField['closePrice'] = 'float'
DFITCSOPRspQryContactField['preSettlePrice'] = 'float'
DFITCSOPRspQryContactField['openPrice'] = 'float'
DFITCSOPRspQryContactField['tradeQty'] = 'long'
DFITCSOPRspQryContactField['turnover'] = 'float'
DFITCSOPRspQryContactField['settlePrice'] = 'float'
DFITCSOPRspQryContactField['endCashSettlePrice'] = 'float'
DFITCSOPRspQryContactField['handQty'] = 'int'
DFITCSOPRspQryContactField['unClosePositionQty'] = 'int'
DFITCSOPRspQryContactField['approachExpireFlag'] = 'int'
DFITCSOPRspQryContactField['tempAdjustFlag'] = 'int'
DFITCSOPRspQryContactField['stockListFlag'] = 'string'
DFITCSOPRspQryContactField['execPrice'] = 'float'
DFITCSOPRspQryContactField['bidPrice1'] = 'float'
DFITCSOPRspQryContactField['bidQty1'] = 'int'
DFITCSOPRspQryContactField['bidPrice2'] = 'float'
DFITCSOPRspQryContactField['bidQty2'] = 'int'
DFITCSOPRspQryContactField['bidPrice3'] = 'float'
DFITCSOPRspQryContactField['bidQty3'] = 'int'
DFITCSOPRspQryContactField['bidPrice4'] = 'float'
DFITCSOPRspQryContactField['bidQty4'] = 'int'
DFITCSOPRspQryContactField['bidPrice5'] = 'float'
DFITCSOPRspQryContactField['bidQty5'] = 'int'
DFITCSOPRspQryContactField['askPrice1'] = 'float'
DFITCSOPRspQryContactField['askQty1'] = 'int'
DFITCSOPRspQryContactField['askPrice2'] = 'float'
DFITCSOPRspQryContactField['askQty2'] = 'int'
DFITCSOPRspQryContactField['askPrice3'] = 'float'
DFITCSOPRspQryContactField['askQty3'] = 'int'
DFITCSOPRspQryContactField['askPrice4'] = 'float'
DFITCSOPRspQryContactField['askQty4'] = 'int'
DFITCSOPRspQryContactField['askPrice5'] = 'float'
DFITCSOPRspQryContactField['askQty5'] = 'int'
DFITCSOPRspQryContactField['optionIndex'] = 'string'
DFITCSOPRspQryContactField['miniPriceChange'] = 'float'


#SOP-期权标的信息查询请求
DFITCSOPReqQryContractObjectField = OrderedDict()

DFITCSOPReqQryContractObjectField['requestID'] = 'long'
DFITCSOPReqQryContractObjectField['accountID'] = 'string'
DFITCSOPReqQryContractObjectField['exchangeID'] = 'string'
DFITCSOPReqQryContractObjectField['securityID'] = 'string'
DFITCSOPReqQryContractObjectField['securityObjectType'] = 'int'


#SOP-期权标的信息查询响应
DFITCSOPRspQryContractObjectField = OrderedDict()

DFITCSOPRspQryContractObjectField['requestID'] = 'long'
DFITCSOPRspQryContractObjectField['accountID'] = 'string'
DFITCSOPRspQryContractObjectField['exchangeID'] = 'string'
DFITCSOPRspQryContractObjectField['securityName'] = 'string'
DFITCSOPRspQryContractObjectField['securityID'] = 'string'
DFITCSOPRspQryContractObjectField['contractObjectType'] = 'int'
DFITCSOPRspQryContractObjectField['contractObjectStatus'] = 'int'


#SOP-执行委托请求
DFITCSOPReqExectueOrderField = OrderedDict()

DFITCSOPReqExectueOrderField['requestID'] = 'long'
DFITCSOPReqExectueOrderField['accountID'] = 'string'
DFITCSOPReqExectueOrderField['localOrderID'] = 'long'
DFITCSOPReqExectueOrderField['exchangeID'] = 'string'
DFITCSOPReqExectueOrderField['securityOptionID'] = 'string'
DFITCSOPReqExectueOrderField['subAccountID'] = 'string'
DFITCSOPReqExectueOrderField['entrustQty'] = 'int'
DFITCSOPReqExectueOrderField['entrustDirection'] = 'int'
DFITCSOPReqExectueOrderField['openCloseFlag'] = 'int'
DFITCSOPReqExectueOrderField['devID'] = 'string'
DFITCSOPReqExectueOrderField['devDecInfo'] = 'string'


#SOP-执行委托响应
DFITCSOPRspExectueOrderField = OrderedDict()

DFITCSOPRspExectueOrderField['requestID'] = 'long'
DFITCSOPRspExectueOrderField['accountID'] = 'string'
DFITCSOPRspExectueOrderField['localOrderID'] = 'long'
DFITCSOPRspExectueOrderField['spdOrderID'] = 'int'
DFITCSOPRspExectueOrderField['entrustTime'] = 'string'
DFITCSOPRspExectueOrderField['freezeFunds'] = 'float'


#SOP-查询交易时间请求
DFITCSOPReqQryTradeTimeField = OrderedDict()

DFITCSOPReqQryTradeTimeField['requestID'] = 'long'
DFITCSOPReqQryTradeTimeField['accountID'] = 'string'


#SOP-查询交易时间响应
DFITCSOPRspQryTradeTimeField = OrderedDict()

DFITCSOPRspQryTradeTimeField['requestID'] = 'long'
DFITCSOPRspQryTradeTimeField['accountID'] = 'string'
DFITCSOPRspQryTradeTimeField['sysTradingDay'] = 'int'
DFITCSOPRspQryTradeTimeField['sysTime'] = 'string'


#SOP-获取所有交易所参数请求
DFITCSOPReqQryExchangeInfoField = OrderedDict()

DFITCSOPReqQryExchangeInfoField['requestID'] = 'long'
DFITCSOPReqQryExchangeInfoField['accountID'] = 'string'
DFITCSOPReqQryExchangeInfoField['exchangeID'] = 'string'


#SOP-获取所有交易所参数响应
DFITCSOPRspQryExchangeInfoField = OrderedDict()

DFITCSOPRspQryExchangeInfoField['requestID'] = 'long'
DFITCSOPRspQryExchangeInfoField['exchangeID'] = 'string'
DFITCSOPRspQryExchangeInfoField['exchangeName'] = 'string'
DFITCSOPRspQryExchangeInfoField['callauctionBegining'] = 'string'
DFITCSOPRspQryExchangeInfoField['callauctionEnding'] = 'string'
DFITCSOPRspQryExchangeInfoField['morningOpening'] = 'string'
DFITCSOPRspQryExchangeInfoField['morningClosing'] = 'string'
DFITCSOPRspQryExchangeInfoField['afternoonOpening'] = 'string'
DFITCSOPRspQryExchangeInfoField['afternoonClosing'] = 'string'
DFITCSOPRspQryExchangeInfoField['execOpening'] = 'string'
DFITCSOPRspQryExchangeInfoField['execClosing'] = 'string'
DFITCSOPRspQryExchangeInfoField['nightTradeFlag'] = 'int'
DFITCSOPRspQryExchangeInfoField['nightOpening'] = 'string'
DFITCSOPRspQryExchangeInfoField['nightClosing'] = 'string'
DFITCSOPRspQryExchangeInfoField['stockTradeStatus'] = 'int'
DFITCSOPRspQryExchangeInfoField['currency'] = 'string'
DFITCSOPRspQryExchangeInfoField['tradingDayFlag'] = 'int'


#SOP-查询手续费参数请求
DFITCSOPReqQryCommissionField = OrderedDict()

DFITCSOPReqQryCommissionField['requestID'] = 'long'
DFITCSOPReqQryCommissionField['accountID'] = 'string'
DFITCSOPReqQryCommissionField['exchangeID'] = 'string'
DFITCSOPReqQryCommissionField['refType'] = 'int'
DFITCSOPReqQryCommissionField['contractObjectType'] = 'int'
DFITCSOPReqQryCommissionField['securityID'] = 'string'
DFITCSOPReqQryCommissionField['openCloseFlag'] = 'int'
DFITCSOPReqQryCommissionField['level'] = 'int'
DFITCSOPReqQryCommissionField['entrustDirection'] = 'int'


#SOP-查询手续费参数响应
DFITCSOPRspQryCommissionField = OrderedDict()

DFITCSOPRspQryCommissionField['requestID'] = 'long'
DFITCSOPRspQryCommissionField['accountID'] = 'string'
DFITCSOPRspQryCommissionField['exchangeID'] = 'string'
DFITCSOPRspQryCommissionField['refType'] = 'int'
DFITCSOPRspQryCommissionField['contractObjectType'] = 'int'
DFITCSOPRspQryCommissionField['securityID'] = 'string'
DFITCSOPRspQryCommissionField['openCloseFlag'] = 'int'
DFITCSOPRspQryCommissionField['entrustDirection'] = 'int'
DFITCSOPRspQryCommissionField['level'] = 'int'
DFITCSOPRspQryCommissionField['costRatio1'] = 'float'
DFITCSOPRspQryCommissionField['unitCost1'] = 'float'
DFITCSOPRspQryCommissionField['costUpLimit1'] = 'float'
DFITCSOPRspQryCommissionField['costDonwLimit1'] = 'float'
DFITCSOPRspQryCommissionField['costRatio2'] = 'float'
DFITCSOPRspQryCommissionField['unitCost2'] = 'float'
DFITCSOPRspQryCommissionField['costUpLimit2'] = 'float'
DFITCSOPRspQryCommissionField['costDonwLimit2'] = 'float'
DFITCSOPRspQryCommissionField['costRatio3'] = 'float'
DFITCSOPRspQryCommissionField['unitCost3'] = 'float'
DFITCSOPRspQryCommissionField['costRatio4'] = 'float'
DFITCSOPRspQryCommissionField['unitCost4'] = 'float'


#SOP-查询保证金率参数请求
DFITCSOPReqQryDepositField = OrderedDict()

DFITCSOPReqQryDepositField['requestID'] = 'long'
DFITCSOPReqQryDepositField['accountID'] = 'string'
DFITCSOPReqQryDepositField['exchangeID'] = 'string'
DFITCSOPReqQryDepositField['refType'] = 'int'
DFITCSOPReqQryDepositField['securityObjectType'] = 'int'
DFITCSOPReqQryDepositField['securityID'] = 'string'
DFITCSOPReqQryDepositField['level'] = 'int'


#SOP-查询保证金率参数响应
DFITCSOPRspQryDepositField = OrderedDict()

DFITCSOPRspQryDepositField['requestID'] = 'long'
DFITCSOPRspQryDepositField['accountID'] = 'string'
DFITCSOPRspQryDepositField['exchangeID'] = 'string'
DFITCSOPRspQryDepositField['refType'] = 'int'
DFITCSOPRspQryDepositField['securityObjectType'] = 'int'
DFITCSOPRspQryDepositField['securityID'] = 'string'
DFITCSOPRspQryDepositField['depositRateC'] = 'float'
DFITCSOPRspQryDepositField['depositRateE'] = 'float'
DFITCSOPRspQryDepositField['depositUnit'] = 'float'
DFITCSOPRspQryDepositField['calcType'] = 'int'
DFITCSOPRspQryDepositField['level'] = 'int'


#FASL-客户可融资信息请求
DFITCFASLReqAbleFinInfoField = OrderedDict()

DFITCFASLReqAbleFinInfoField['requestID'] = 'long'
DFITCFASLReqAbleFinInfoField['accountID'] = 'string'


#FASL-客户可融资信息响应
DFITCFASLRspAbleFinInfoField = OrderedDict()

DFITCFASLRspAbleFinInfoField['requestID'] = 'long'
DFITCFASLRspAbleFinInfoField['accountID'] = 'string'
DFITCFASLRspAbleFinInfoField['accountBanlance'] = 'float'
DFITCFASLRspAbleFinInfoField['ableFinFunds'] = 'float'
DFITCFASLRspAbleFinInfoField['turnover'] = 'float'
DFITCFASLRspAbleFinInfoField['entrustFreezeFunds'] = 'float'


#STOCK-可用行情信息查询请求
DFITCReqQuotQryField = OrderedDict()

DFITCReqQuotQryField['requestID'] = 'long'
DFITCReqQuotQryField['accountID'] = 'string'
DFITCReqQuotQryField['exchangeID'] = 'string'


#STOCK-可用行情信息查询响应
DFITCRspQuotQryField = OrderedDict()

DFITCRspQuotQryField['requestID'] = 'long'
DFITCRspQuotQryField['accountID'] = 'string'
DFITCRspQuotQryField['exchangeID'] = 'string'
DFITCRspQuotQryField['securityID'] = 'string'
DFITCRspQuotQryField['securityName'] = 'string'


#FASL-客户可融券信息请求
DFITCFASLReqAbleSloInfoField = OrderedDict()

DFITCFASLReqAbleSloInfoField['requestID'] = 'long'
DFITCFASLReqAbleSloInfoField['accountID'] = 'string'


#FASL-客户可融券信息响应
DFITCFASLRspAbleSloInfoField = OrderedDict()

DFITCFASLRspAbleSloInfoField['requestID'] = 'long'
DFITCFASLRspAbleSloInfoField['accountID'] = 'string'
DFITCFASLRspAbleSloInfoField['securityID'] = 'string'
DFITCFASLRspAbleSloInfoField['exchangeID'] = 'string'
DFITCFASLRspAbleSloInfoField['ableSloQty'] = 'int'
DFITCFASLRspAbleSloInfoField['securityName'] = 'string'
DFITCFASLRspAbleSloInfoField['entrustQty'] = 'int'
DFITCFASLRspAbleSloInfoField['tradeQty'] = 'int'
DFITCFASLRspAbleSloInfoField['status'] = 'int'
DFITCFASLRspAbleSloInfoField['sloDepositRatio'] = 'float'


#FASL-担保物划转请求
DFITCFASLReqTransferCollateralField = OrderedDict()

DFITCFASLReqTransferCollateralField['requestID'] = 'long'
DFITCFASLReqTransferCollateralField['accountID'] = 'string'
DFITCFASLReqTransferCollateralField['localOrderID'] = 'long'
DFITCFASLReqTransferCollateralField['entrustDirection'] = 'int'
DFITCFASLReqTransferCollateralField['exchangeID'] = 'string'
DFITCFASLReqTransferCollateralField['securityID'] = 'string'
DFITCFASLReqTransferCollateralField['transferQty'] = 'int'


#FASL-担保物划转响应
DFITCFASLRspTransferCollateralField = OrderedDict()

DFITCFASLRspTransferCollateralField['requestID'] = 'long'
DFITCFASLRspTransferCollateralField['accountID'] = 'string'
DFITCFASLRspTransferCollateralField['spdOrderID'] = 'int'
DFITCFASLRspTransferCollateralField['localOrderID'] = 'long'


#FASL-直接还款请求
DFITCFASLReqDirectRepaymentField = OrderedDict()

DFITCFASLReqDirectRepaymentField['requestID'] = 'long'
DFITCFASLReqDirectRepaymentField['accountID'] = 'string'
DFITCFASLReqDirectRepaymentField['contractNO'] = 'string'
DFITCFASLReqDirectRepaymentField['repayFunds'] = 'float'


#FASL-直接还款响应
DFITCFASLRspDirectRepaymentField = OrderedDict()

DFITCFASLRspDirectRepaymentField['requestID'] = 'long'
DFITCFASLRspDirectRepaymentField['accountID'] = 'string'
DFITCFASLRspDirectRepaymentField['realRepayFunds'] = 'float'


#FASL-还券划转请求
DFITCFASLReqRepayStockTransferField = OrderedDict()

DFITCFASLReqRepayStockTransferField['requestID'] = 'long'
DFITCFASLReqRepayStockTransferField['accountID'] = 'string'
DFITCFASLReqRepayStockTransferField['localOrderID'] = 'long'
DFITCFASLReqRepayStockTransferField['exchangeID'] = 'string'
DFITCFASLReqRepayStockTransferField['repayQty'] = 'int'
DFITCFASLReqRepayStockTransferField['securityID'] = 'string'
DFITCFASLReqRepayStockTransferField['contractNO'] = 'string'


#FASL-还券划转响应
DFITCFASLRspRepayStockTransferField = OrderedDict()

DFITCFASLRspRepayStockTransferField['requestID'] = 'long'
DFITCFASLRspRepayStockTransferField['accountID'] = 'string'
DFITCFASLRspRepayStockTransferField['spdOrderID'] = 'int'
DFITCFASLRspRepayStockTransferField['localOrderID'] = 'long'


#FASL-信用交易请求
DFITCFASLReqEntrustCrdtOrderField = OrderedDict()

DFITCFASLReqEntrustCrdtOrderField['requestID'] = 'long'
DFITCFASLReqEntrustCrdtOrderField['accountID'] = 'string'
DFITCFASLReqEntrustCrdtOrderField['localOrderID'] = 'long'
DFITCFASLReqEntrustCrdtOrderField['entrustDirection'] = 'int'
DFITCFASLReqEntrustCrdtOrderField['exchangeID'] = 'string'
DFITCFASLReqEntrustCrdtOrderField['contractNO'] = 'string'
DFITCFASLReqEntrustCrdtOrderField['securityID'] = 'string'
DFITCFASLReqEntrustCrdtOrderField['orderType'] = 'int'
DFITCFASLReqEntrustCrdtOrderField['entrustQty'] = 'int'
DFITCFASLReqEntrustCrdtOrderField['entrustPrice'] = 'float'


#FASL-信用交易响应
DFITCFASLRspEntrustCrdtOrderField = OrderedDict()

DFITCFASLRspEntrustCrdtOrderField['requestID'] = 'long'
DFITCFASLRspEntrustCrdtOrderField['accountID'] = 'string'
DFITCFASLRspEntrustCrdtOrderField['spdOrderID'] = 'int'
DFITCFASLRspEntrustCrdtOrderField['localOrderID'] = 'long'



#FASL-信用委托撤单请求
DFITCFASLReqWithdrawOrderField = OrderedDict()

DFITCFASLReqWithdrawOrderField['requestID'] = 'long'
DFITCFASLReqWithdrawOrderField['accountID'] = 'string'
DFITCFASLReqWithdrawOrderField['spdOrderID'] = 'int'
DFITCFASLReqWithdrawOrderField['localOrderID'] = 'long'


#FASL-信用委托撤单响应
DFITCFASLRspWithdrawOrderField = OrderedDict()

DFITCFASLRspWithdrawOrderField['requestID'] = 'long'
DFITCFASLRspWithdrawOrderField['accountID'] = 'string'
DFITCFASLRspWithdrawOrderField['localOrderID'] = 'long'
DFITCFASLRspWithdrawOrderField['spdOrderID'] = 'int'



#FASL-融资融券交易请求
DFITCFASLReqEntrustOrderField = OrderedDict()

DFITCFASLReqEntrustOrderField['requestID'] = 'long'
DFITCFASLReqEntrustOrderField['localOrderID'] = 'long'
DFITCFASLReqEntrustOrderField['accountID'] = 'string'
DFITCFASLReqEntrustOrderField['entrustDirection'] = 'int'
DFITCFASLReqEntrustOrderField['exchangeID'] = 'string'
DFITCFASLReqEntrustOrderField['securityID'] = 'string'
DFITCFASLReqEntrustOrderField['orderType'] = 'int'
DFITCFASLReqEntrustOrderField['entrustQty'] = 'int'
DFITCFASLReqEntrustOrderField['entrustPrice'] = 'float'
DFITCFASLReqEntrustOrderField['positionSource'] = 'int'


#FASL-融资融券交易响应
DFITCFASLRspEntrustOrderField = OrderedDict()

DFITCFASLRspEntrustOrderField['requestID'] = 'long'
DFITCFASLRspEntrustOrderField['accountID'] = 'string'
DFITCFASLRspEntrustOrderField['localOrderID'] = 'long'
DFITCFASLRspEntrustOrderField['spdOrderID'] = 'int'


#FASL-信用可委托数量查询请求
DFITCFASLReqCalcAbleEntrustCrdtQtyField = OrderedDict()

DFITCFASLReqCalcAbleEntrustCrdtQtyField['requestID'] = 'long'
DFITCFASLReqCalcAbleEntrustCrdtQtyField['accountID'] = 'string'
DFITCFASLReqCalcAbleEntrustCrdtQtyField['entrustDirection'] = 'int'
DFITCFASLReqCalcAbleEntrustCrdtQtyField['exchangeID'] = 'string'
DFITCFASLReqCalcAbleEntrustCrdtQtyField['contractNO'] = 'string'
DFITCFASLReqCalcAbleEntrustCrdtQtyField['securityID'] = 'string'
DFITCFASLReqCalcAbleEntrustCrdtQtyField['orderType'] = 'int'
DFITCFASLReqCalcAbleEntrustCrdtQtyField['entrustPrice'] = 'float'
DFITCFASLReqCalcAbleEntrustCrdtQtyField['positionSource'] = 'int'


#FASL-信用可委托数量查询响应
DFITCFASLRspCalcAbleEntrustCrdtQtyField = OrderedDict()

DFITCFASLRspCalcAbleEntrustCrdtQtyField['requestID'] = 'long'
DFITCFASLRspCalcAbleEntrustCrdtQtyField['accountID'] = 'string'
DFITCFASLRspCalcAbleEntrustCrdtQtyField['totalRepayQty'] = 'int'
DFITCFASLRspCalcAbleEntrustCrdtQtyField['entrustQty'] = 'int'


#FASL-查询信用资金请求
DFITCFASLReqQryCrdtFundsField = OrderedDict()

DFITCFASLReqQryCrdtFundsField['requestID'] = 'long'
DFITCFASLReqQryCrdtFundsField['accountID'] = 'string'


#FASL-查询信用资金响应
DFITCFASLRspQryCrdtFundsField = OrderedDict()

DFITCFASLRspQryCrdtFundsField['requestID'] = 'long'
DFITCFASLRspQryCrdtFundsField['accountID'] = 'string'
DFITCFASLRspQryCrdtFundsField['availableDeposit'] = 'float'
DFITCFASLRspQryCrdtFundsField['maintGuaranteeRatio'] = 'float'
DFITCFASLRspQryCrdtFundsField['antiMaintGuaranteeRatio'] = 'float'
DFITCFASLRspQryCrdtFundsField['accountBanlance'] = 'float'
DFITCFASLRspQryCrdtFundsField['availableFunds'] = 'float'
DFITCFASLRspQryCrdtFundsField['clearFunds'] = 'float'
DFITCFASLRspQryCrdtFundsField['stockMarket'] = 'float'
DFITCFASLRspQryCrdtFundsField['guaranteeStockSubMarket'] = 'float'
DFITCFASLRspQryCrdtFundsField['guaranteeStockMarket'] = 'float'
DFITCFASLRspQryCrdtFundsField['tradeFinLiabilities'] = 'float'
DFITCFASLRspQryCrdtFundsField['tradeSloLiabilities'] = 'float'
DFITCFASLRspQryCrdtFundsField['orderFinLiabilities'] = 'float'
DFITCFASLRspQryCrdtFundsField['orderSloLiabilities'] = 'float'
DFITCFASLRspQryCrdtFundsField['sloOrderRepay'] = 'float'
DFITCFASLRspQryCrdtFundsField['fundsBalance'] = 'float'
DFITCFASLRspQryCrdtFundsField['closeFunds'] = 'float'
DFITCFASLRspQryCrdtFundsField['activeCloseFunds'] = 'float'
DFITCFASLRspQryCrdtFundsField['ableWithdrawalAssetsStand'] = 'float'
DFITCFASLRspQryCrdtFundsField['withdrawalFunds'] = 'float'
DFITCFASLRspQryCrdtFundsField['totalAssets'] = 'float'
DFITCFASLRspQryCrdtFundsField['unTransferStockMarket'] = 'float'
DFITCFASLRspQryCrdtFundsField['totalLiabilities'] = 'float'
DFITCFASLRspQryCrdtFundsField['netAssets'] = 'float'
DFITCFASLRspQryCrdtFundsField['sellRepayFunds'] = 'float'
DFITCFASLRspQryCrdtFundsField['anticipatedInterest'] = 'float'
DFITCFASLRspQryCrdtFundsField['finProfitLoss'] = 'float'
DFITCFASLRspQryCrdtFundsField['sloProfitLoss'] = 'float'
DFITCFASLRspQryCrdtFundsField['sloFunds'] = 'float'
DFITCFASLRspQryCrdtFundsField['finCost'] = 'float'
DFITCFASLRspQryCrdtFundsField['sloCost'] = 'float'
DFITCFASLRspQryCrdtFundsField['finCurMarket'] = 'float'
DFITCFASLRspQryCrdtFundsField['finUsedDeposit'] = 'float'
DFITCFASLRspQryCrdtFundsField['sloUsedDeposit'] = 'float'
DFITCFASLRspQryCrdtFundsField['finAntiInterest'] = 'float'
DFITCFASLRspQryCrdtFundsField['sloAntiInterest'] = 'float'
DFITCFASLRspQryCrdtFundsField['shGuaranteeStockMarket'] = 'float'
DFITCFASLRspQryCrdtFundsField['szGuaranteeStockMarket'] = 'float'
DFITCFASLRspQryCrdtFundsField['finFloatProfit'] = 'float'
DFITCFASLRspQryCrdtFundsField['finFloatLoss'] = 'float'
DFITCFASLRspQryCrdtFundsField['sloFloatProfit'] = 'float'
DFITCFASLRspQryCrdtFundsField['sloFloatLoss'] = 'float'
DFITCFASLRspQryCrdtFundsField['finRatio'] = 'float'
DFITCFASLRspQryCrdtFundsField['sloRatio'] = 'float'
DFITCFASLRspQryCrdtFundsField['contractEndDate'] = 'int'
DFITCFASLRspQryCrdtFundsField['finUsedLimits'] = 'float'
DFITCFASLRspQryCrdtFundsField['sloUsedLimits'] = 'float'
DFITCFASLRspQryCrdtFundsField['finCreditLimits'] = 'float'
DFITCFASLRspQryCrdtFundsField['sloCreditLimits'] = 'float'
DFITCFASLRspQryCrdtFundsField['ableBuyCollateralFunds'] = 'float'
DFITCFASLRspQryCrdtFundsField['ableRepayFunds'] = 'float'
DFITCFASLRspQryCrdtFundsField['sloAvailableFunds'] = 'float'
DFITCFASLRspQryCrdtFundsField['cashAssets'] = 'float'
DFITCFASLRspQryCrdtFundsField['totalStockMarket'] = 'float'
DFITCFASLRspQryCrdtFundsField['finContractFunds'] = 'float'
DFITCFASLRspQryCrdtFundsField['contractObjectMarket'] = 'float'
DFITCFASLRspQryCrdtFundsField['otherCharges'] = 'float'
DFITCFASLRspQryCrdtFundsField['sloCurMarket'] = 'float'


#FASL-信用合约信息请求
DFITCFASLReqQryCrdtContractField = OrderedDict()

DFITCFASLReqQryCrdtContractField['requestID'] = 'long'
DFITCFASLReqQryCrdtContractField['accountID'] = 'string'
DFITCFASLReqQryCrdtContractField['openBeginDate'] = 'int'
DFITCFASLReqQryCrdtContractField['openEndDate'] = 'int'
DFITCFASLReqQryCrdtContractField['crdtConQryFlag'] = 'int'
DFITCFASLReqQryCrdtContractField['spdOrderID'] = 'int'
DFITCFASLReqQryCrdtContractField['entrustDirection'] = 'int'
DFITCFASLReqQryCrdtContractField['exchangeID'] = 'string'
DFITCFASLReqQryCrdtContractField['contractNO'] = 'string'
DFITCFASLReqQryCrdtContractField['securityID'] = 'string'
DFITCFASLReqQryCrdtContractField['conSerialID'] = 'int'


#FASL-信用合约信息响应
DFITCFASLRspQryCrdtContractField = OrderedDict()

DFITCFASLRspQryCrdtContractField['requestID'] = 'long'
DFITCFASLRspQryCrdtContractField['accountID'] = 'string'
DFITCFASLRspQryCrdtContractField['conSerialNO'] = 'int'
DFITCFASLRspQryCrdtContractField['contractNO'] = 'string'
DFITCFASLRspQryCrdtContractField['operatorDate'] = 'int'
DFITCFASLRspQryCrdtContractField['endDate'] = 'int'
DFITCFASLRspQryCrdtContractField['spdOrderID'] = 'int'
DFITCFASLRspQryCrdtContractField['entrustDirection'] = 'int'
DFITCFASLRspQryCrdtContractField['exchangeID'] = 'string'
DFITCFASLRspQryCrdtContractField['securityID'] = 'string'
DFITCFASLRspQryCrdtContractField['securityName'] = 'string'
DFITCFASLRspQryCrdtContractField['currency'] = 'string'
DFITCFASLRspQryCrdtContractField['finQty'] = 'int'
DFITCFASLRspQryCrdtContractField['finFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['sloQty'] = 'int'
DFITCFASLRspQryCrdtContractField['sloFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['finEntrustQty'] = 'int'
DFITCFASLRspQryCrdtContractField['finEntrustFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['sloEntrustQty'] = 'int'
DFITCFASLRspQryCrdtContractField['sloEntrustFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['finTradeQty'] = 'int'
DFITCFASLRspQryCrdtContractField['finTradeFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['sloTradeQty'] = 'int'
DFITCFASLRspQryCrdtContractField['sloTradeFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['debtPrincipal'] = 'float'
DFITCFASLRspQryCrdtContractField['repayFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['debtQty'] = 'int'
DFITCFASLRspQryCrdtContractField['repayQty'] = 'int'
DFITCFASLRspQryCrdtContractField['sellStockRepayFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['buyStockForRepayEntrustQty//当日买券还券委托数量'] = 'int'
DFITCFASLRspQryCrdtContractField['buyStockForRepayTradeQty'] = 'int'
DFITCFASLRspQryCrdtContractField['finCost'] = 'float'
DFITCFASLRspQryCrdtContractField['sloCost'] = 'float'
DFITCFASLRspQryCrdtContractField['totalInterest'] = 'float'
DFITCFASLRspQryCrdtContractField['repaidInterest'] = 'float'
DFITCFASLRspQryCrdtContractField['crdtConStatus'] = 'int'
DFITCFASLRspQryCrdtContractField['leftInterest'] = 'float'
DFITCFASLRspQryCrdtContractField['sloLeftFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['buyStockFreezeFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['buyStockClearFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['sloLeftAvaiFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['debtQtyEntrustMarket'] = 'float'
DFITCFASLRspQryCrdtContractField['debtQtyTradeMarket'] = 'float'
DFITCFASLRspQryCrdtContractField['debtFundsMarket'] = 'float'
DFITCFASLRspQryCrdtContractField['finProfitLoss'] = 'float'
DFITCFASLRspQryCrdtContractField['sloProfitLoss'] = 'float'
DFITCFASLRspQryCrdtContractField['entrustQty'] = 'int'
DFITCFASLRspQryCrdtContractField['conOpenQty'] = 'int'
DFITCFASLRspQryCrdtContractField['conOpenFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['conOpenCost'] = 'float'
DFITCFASLRspQryCrdtContractField['conInitQty'] = 'int'
DFITCFASLRspQryCrdtContractField['conInitFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['conInitCost'] = 'float'
DFITCFASLRspQryCrdtContractField['unRepayConFunds'] = 'float'
DFITCFASLRspQryCrdtContractField['unRepayConQty'] = 'int'
DFITCFASLRspQryCrdtContractField['unRepayConCost'] = 'float'
DFITCFASLRspQryCrdtContractField['positionNO'] = 'int'


#FASL-信用合约变动信息查询请求
DFITCFASLReqQryCrdtConChangeInfoField = OrderedDict()

DFITCFASLReqQryCrdtConChangeInfoField['requestID'] = 'long'
DFITCFASLReqQryCrdtConChangeInfoField['accountID'] = 'string'
DFITCFASLReqQryCrdtConChangeInfoField['withdrawFlag'] = 'string'
DFITCFASLReqQryCrdtConChangeInfoField['entrustDirection'] = 'int'
DFITCFASLReqQryCrdtConChangeInfoField['exchangeID'] = 'string'
DFITCFASLReqQryCrdtConChangeInfoField['securityID'] = 'string'
DFITCFASLReqQryCrdtConChangeInfoField['conSerialNO'] = 'int'


#FASL-信用合约变动信息查询响应
DFITCFASLRspQryCrdtConChangeInfoField = OrderedDict()

DFITCFASLRspQryCrdtConChangeInfoField['requestID'] = 'long'
DFITCFASLRspQryCrdtConChangeInfoField['accountID'] = 'string'
DFITCFASLRspQryCrdtConChangeInfoField['serialNO'] = 'int'
DFITCFASLRspQryCrdtConChangeInfoField['conChangeNO'] = 'string'
DFITCFASLRspQryCrdtConChangeInfoField['withdrawFlag'] = 'string'
DFITCFASLRspQryCrdtConChangeInfoField['securityID'] = 'string'
DFITCFASLRspQryCrdtConChangeInfoField['entrustDirection'] = 'int'
DFITCFASLRspQryCrdtConChangeInfoField['operatorFunds'] = 'float'
DFITCFASLRspQryCrdtConChangeInfoField['operatorTime'] = 'string'
DFITCFASLRspQryCrdtConChangeInfoField['operatorQty'] = 'int'
DFITCFASLRspQryCrdtConChangeInfoField['operatorDate'] = 'int'
DFITCFASLRspQryCrdtConChangeInfoField['clearFlag'] = 'int'
DFITCFASLRspQryCrdtConChangeInfoField['commission'] = 'float'
DFITCFASLRspQryCrdtConChangeInfoField['operatorFunds2'] = 'float'
DFITCFASLRspQryCrdtConChangeInfoField['postFunds'] = 'float'
DFITCFASLRspQryCrdtConChangeInfoField['postQty'] = 'int'
DFITCFASLRspQryCrdtConChangeInfoField['exchangeID'] = 'string'
DFITCFASLRspQryCrdtConChangeInfoField['operatorCost'] = 'float'
DFITCFASLRspQryCrdtConChangeInfoField['postCost'] = 'float'
DFITCFASLRspQryCrdtConChangeInfoField['operatorInterest'] = 'float'
DFITCFASLRspQryCrdtConChangeInfoField['postInterest'] = 'float'
DFITCFASLRspQryCrdtConChangeInfoField['changeNote'] = 'string'
DFITCFASLRspQryCrdtConChangeInfoField['shareholderID'] = 'string'


#FASL-查询系统时间请求
DFITCFASLReqQryTradeTimeField = OrderedDict()

DFITCFASLReqQryTradeTimeField['requestID'] = 'long'
DFITCFASLReqQryTradeTimeField['accountID'] = 'string'
DFITCFASLReqQryTradeTimeField['flag'] = 'int'


#FASL-查询系统时间响应
DFITCFASLRspQryTradeTimeField = OrderedDict()

DFITCFASLRspQryTradeTimeField['requestID'] = 'long'
DFITCFASLRspQryTradeTimeField['accountID'] = 'string'
DFITCFASLRspQryTradeTimeField['sysTradingDay'] = 'int'
DFITCFASLRspQryTradeTimeField['sysTime'] = 'string'
DFITCFASLRspQryTradeTimeField['sysWeek'] = 'int'
DFITCFASLRspQryTradeTimeField['sysMillisecond'] = 'int'


#FASL-可转入担保证券查询
DFITCFASLReqQryTransferredContractField = OrderedDict()

DFITCFASLReqQryTransferredContractField['requestID'] = 'long'
DFITCFASLReqQryTransferredContractField['accountID'] = 'string'
DFITCFASLReqQryTransferredContractField['securityID'] = 'string'
DFITCFASLReqQryTransferredContractField['exchangeID'] = 'string'


#FASL-可转入担保证券查询响应
DFITCFASLRspQryTransferredContractField = OrderedDict()

DFITCFASLRspQryTransferredContractField['requestID'] = 'long'
DFITCFASLRspQryTransferredContractField['accountID'] = 'string'
DFITCFASLRspQryTransferredContractField['capitalID'] = 'string'
DFITCFASLRspQryTransferredContractField['securityID'] = 'string'
DFITCFASLRspQryTransferredContractField['exchangeID'] = 'string'
DFITCFASLRspQryTransferredContractField['ableSellQty'] = 'int'


#FASL-客户可取资金调出
DFITCFASLReqDesirableFundsOutField = OrderedDict()

DFITCFASLReqDesirableFundsOutField['requestID'] = 'long'
DFITCFASLReqDesirableFundsOutField['accountID'] = 'string'
DFITCFASLReqDesirableFundsOutField['currency'] = 'string'
DFITCFASLReqDesirableFundsOutField['operateFunds'] = 'float'
DFITCFASLReqDesirableFundsOutField['summaryMsg'] = 'string'


#FASL-客户可取资金调出响应
DFITCFASLRspDesirableFundsOutField = OrderedDict()

DFITCFASLRspDesirableFundsOutField['requestID'] = 'long'
DFITCFASLRspDesirableFundsOutField['accountID'] = 'string'
DFITCFASLRspDesirableFundsOutField['serialID'] = 'int'
DFITCFASLRspDesirableFundsOutField['accountBanlance'] = 'float'


#FASL-担保证券查询
DFITCFASLReqQryGuaranteedContractField = OrderedDict()

DFITCFASLReqQryGuaranteedContractField['requestID'] = 'long'
DFITCFASLReqQryGuaranteedContractField['accountID'] = 'string'


#FASL-担保证券查询响应
DFITCFASLRspQryGuaranteedContractField = OrderedDict()

DFITCFASLRspQryGuaranteedContractField['requestID'] = 'long'
DFITCFASLRspQryGuaranteedContractField['accountID'] = 'string'
DFITCFASLRspQryGuaranteedContractField['exchangeID'] = 'string'
DFITCFASLRspQryGuaranteedContractField['securityID'] = 'string'
DFITCFASLRspQryGuaranteedContractField['securityName'] = 'string'
DFITCFASLRspQryGuaranteedContractField['exchangRate'] = 'float'
DFITCFASLRspQryGuaranteedContractField['status'] = 'int'
DFITCFASLRspQryGuaranteedContractField['accountType'] = 'int'


#FASL-标的证券查询
DFITCFASLReqQryUnderlyingContractField = OrderedDict()

DFITCFASLReqQryUnderlyingContractField['requestID'] = 'long'
DFITCFASLReqQryUnderlyingContractField['accountID'] = 'string'


#FASL-标的证券查询响应
DFITCFASLRspQryUnderlyingContractField = OrderedDict()

DFITCFASLRspQryUnderlyingContractField['requestID'] = 'long'
DFITCFASLRspQryUnderlyingContractField['accountID'] = 'string'
DFITCFASLRspQryUnderlyingContractField['exchangeID'] = 'string'
DFITCFASLRspQryUnderlyingContractField['securityID'] = 'string'
DFITCFASLRspQryUnderlyingContractField['securityName'] = 'string'
DFITCFASLRspQryUnderlyingContractField['financeDepositRatio'] = 'float'
DFITCFASLRspQryUnderlyingContractField['securityDepositRatio'] = 'float'
DFITCFASLRspQryUnderlyingContractField['status'] = 'int'
DFITCFASLRspQryUnderlyingContractField['accountType'] = 'int'



#QUOTE-指定的合约
DFITCSECSpecificInstrumentField = OrderedDict()

DFITCSECSpecificInstrumentField['requestID'] = 'long'
DFITCSECSpecificInstrumentField['securityID'] = 'string'
DFITCSECSpecificInstrumentField['exchangeID'] = 'string'


#sop 特有的
DFITCSOPSpecificDataField = OrderedDict()

DFITCSOPSpecificDataField['contractID'] = 'string'
DFITCSOPSpecificDataField['execPrice'] = 'float'
DFITCSOPSpecificDataField['preSettlePrice'] = 'float'
DFITCSOPSpecificDataField['settlePrice'] = 'float'
DFITCSOPSpecificDataField['positionQty'] = 'long'
DFITCSOPSpecificDataField['auctionPrice'] = 'float'
DFITCSOPSpecificDataField['latestEnquiryTime'] = 'string'


#stock 特有的
DFITCStockSpecificDataField = OrderedDict()

DFITCStockSpecificDataField['peRadio1'] = 'float'
DFITCStockSpecificDataField['peRadio2'] = 'float'


#共有静态的
DFITCStaticDataField = OrderedDict()

DFITCStaticDataField['securityID'] = 'string'
DFITCStaticDataField['securityName'] = 'string'
DFITCStaticDataField['tradingDay'] = 'int'
DFITCStaticDataField['exchangeID'] = 'string'
DFITCStaticDataField['preClosePrice'] = 'float'
DFITCStaticDataField['openPrice'] = 'float'
DFITCStaticDataField['upperLimitPrice'] = 'float'
DFITCStaticDataField['lowerLimitPrice'] = 'float'



#共有动态的
DFITCSharedDataField = OrderedDict()

DFITCSharedDataField['latestPrice'] = 'float'
DFITCSharedDataField['turnover'] = 'float'
DFITCSharedDataField['highestPrice'] = 'float'
DFITCSharedDataField['lowestPrice'] = 'float'
DFITCSharedDataField['tradeQty'] = 'long'
DFITCSharedDataField['updateTime'] = 'string'
DFITCSharedDataField['bidPrice1'] = 'float'
DFITCSharedDataField['bidQty1'] = 'long'
DFITCSharedDataField['askPrice1'] = 'float'
DFITCSharedDataField['askQty1'] = 'long'
DFITCSharedDataField['bidPrice2'] = 'float'
DFITCSharedDataField['bidQty2'] = 'long'
DFITCSharedDataField['askPrice2'] = 'float'
DFITCSharedDataField['askQty2'] = 'long'
DFITCSharedDataField['bidPrice3'] = 'float'
DFITCSharedDataField['bidQty3'] = 'long'
DFITCSharedDataField['askPrice3'] = 'float'
DFITCSharedDataField['askQty3'] = 'long'
DFITCSharedDataField['bidPrice4'] = 'float'
DFITCSharedDataField['bidQty4'] = 'long'
DFITCSharedDataField['askPrice4'] = 'float'
DFITCSharedDataField['askQty4'] = 'long'
DFITCSharedDataField['bidPrice5'] = 'float'
DFITCSharedDataField['bidQty5'] = 'long'
DFITCSharedDataField['askPrice5'] = 'float'
DFITCSharedDataField['askQty5'] = 'long'
DFITCSharedDataField['tradingPhaseCode'] = 'string'


DFITCSOPDepthMarketDataField = OrderedDict()


DFITCStockDepthMarketDataField = OrderedDict()



#STOCK-证券静态信息查询请求
DFITCStockReqQryStockStaticField = OrderedDict()

DFITCStockReqQryStockStaticField['requestID'] = 'long'
DFITCStockReqQryStockStaticField['accountID'] = 'string'
DFITCStockReqQryStockStaticField['exchangeID'] = 'string'


#STOCK-证券静态信息查询响应
DFITCStockRspQryStockStaticField = OrderedDict()

DFITCStockRspQryStockStaticField['requestID'] = 'long'
DFITCStockRspQryStockStaticField['accountID'] = 'string'
DFITCStockRspQryStockStaticField['stopFlag'] = 'int'
DFITCStockRspQryStockStaticField['preClosePrice'] = 'float'
DFITCStockRspQryStockStaticField['openPrice'] = 'float'
DFITCStockRspQryStockStaticField['exchangeID'] = 'string'
DFITCStockRspQryStockStaticField['securityID'] = 'string'
DFITCStockRspQryStockStaticField['interestQuote'] = 'float'
DFITCStockRspQryStockStaticField['securityFaceValue'] = 'float'
DFITCStockRspQryStockStaticField['bidTradeFlag'] = 'int'
DFITCStockRspQryStockStaticField['tradeUnit'] = 'int'
DFITCStockRspQryStockStaticField['businessLimit'] = 'int'
DFITCStockRspQryStockStaticField['securityType'] = 'string'
DFITCStockRspQryStockStaticField['securityName'] = 'string'
DFITCStockRspQryStockStaticField['upperLimitPrice'] = 'float'
DFITCStockRspQryStockStaticField['lowerLimitPrice'] = 'float'
DFITCStockRspQryStockStaticField['currency'] = 'string'
DFITCStockRspQryStockStaticField['orderLimits'] = 'string'


#SOP-交易所持仓组合拆分委托请求
DFITCSOPReqGroupSplitField = OrderedDict()

DFITCSOPReqGroupSplitField['requestID'] = 'long'
DFITCSOPReqGroupSplitField['accountID'] = 'string'
DFITCSOPReqGroupSplitField['localOrderID'] = 'long'
DFITCSOPReqGroupSplitField['exchangeID'] = 'string'
DFITCSOPReqGroupSplitField['securityOptionID'] = 'string'
DFITCSOPReqGroupSplitField['subAccountID'] = 'string'
DFITCSOPReqGroupSplitField['openCloseFlag'] = 'int'
DFITCSOPReqGroupSplitField['groupType'] = 'int'
DFITCSOPReqGroupSplitField['groupCode'] = 'string'
DFITCSOPReqGroupSplitField['securityOptionID1'] = 'string'
DFITCSOPReqGroupSplitField['securityOptionID2'] = 'string'
DFITCSOPReqGroupSplitField['securityOptionID3'] = 'string'
DFITCSOPReqGroupSplitField['securityOptionID4'] = 'string'
DFITCSOPReqGroupSplitField['entrustQty'] = 'int'
DFITCSOPReqGroupSplitField['devID'] = 'string'
DFITCSOPReqGroupSplitField['devDecInfo'] = 'string'


#SOP-查询客户组合持仓明细请求
DFITCSOPReqQryGroupPositionField = OrderedDict()

DFITCSOPReqQryGroupPositionField['requestID'] = 'long'
DFITCSOPReqQryGroupPositionField['accountID'] = 'string'


#SOP-查询客户组合持仓明细响应
DFITCSOPRspQryGroupPositionField = OrderedDict()

DFITCSOPRspQryGroupPositionField['requestID'] = 'long'
DFITCSOPRspQryGroupPositionField['accountID'] = 'string'
DFITCSOPRspQryGroupPositionField['exchangeID'] = 'string'
DFITCSOPRspQryGroupPositionField['shareholderID'] = 'string'
DFITCSOPRspQryGroupPositionField['subAccountID'] = 'string'
DFITCSOPRspQryGroupPositionField['currency'] = 'string'
DFITCSOPRspQryGroupPositionField['capitalID'] = 'string'
DFITCSOPRspQryGroupPositionField['groupType'] = 'int'
DFITCSOPRspQryGroupPositionField['groupCode'] = 'string'
DFITCSOPRspQryGroupPositionField['groupQty'] = 'int'
DFITCSOPRspQryGroupPositionField['enableSplitQty'] = 'int'
DFITCSOPRspQryGroupPositionField['splitEntrustQty'] = 'int'
DFITCSOPRspQryGroupPositionField['splitTradeQty'] = 'int'
DFITCSOPRspQryGroupPositionField['groupDeposit'] = 'float'
DFITCSOPRspQryGroupPositionField['securityOptionID1'] = 'string'
DFITCSOPRspQryGroupPositionField['securityOptionID2'] = 'string'
DFITCSOPRspQryGroupPositionField['securityOptionID3'] = 'string'
DFITCSOPRspQryGroupPositionField['securityOptionID4'] = 'string'



