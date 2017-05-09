# encoding: UTF-8

structDict = {}

















#心跳包
DFITCTimeOutField = {}
DFITCTimeOutField["lRequestID"] = "long"
structDict['DFITCTimeOutField'] = DFITCTimeOutField



#请求报单数据类型(基本报单)
DFITCInsertOrderField = {}
DFITCInsertOrderField["accountID"] = "string"
DFITCInsertOrderField["localOrderID"] = "long"
DFITCInsertOrderField["instrumentID"] = "string"
DFITCInsertOrderField["insertPrice"] = "float"
DFITCInsertOrderField["orderAmount"] = "long"
DFITCInsertOrderField["buySellType"] = "short"
DFITCInsertOrderField["openCloseType"] = "int"
DFITCInsertOrderField["speculator"] = "int"
DFITCInsertOrderField["insertType"] = "int"
DFITCInsertOrderField["orderType"] = "int"
DFITCInsertOrderField["orderProperty"] = "char"
DFITCInsertOrderField["instrumentType"] = "int"
DFITCInsertOrderField["minMatchAmount"] = "long"
DFITCInsertOrderField["reservedType2"] = "int"
DFITCInsertOrderField["lRequestID"] = "long"
DFITCInsertOrderField["customCategory"] = "string"
DFITCInsertOrderField["profitLossPrice"] = "float"
structDict['DFITCInsertOrderField'] = DFITCInsertOrderField



#撤单数据类型
DFITCCancelOrderField = {}
DFITCCancelOrderField["accountID"] = "string"
DFITCCancelOrderField["spdOrderID"] = "long"
DFITCCancelOrderField["localOrderID"] = "long"
DFITCCancelOrderField["instrumentID"] = "string"
DFITCCancelOrderField["lRequestID"] = "long"
structDict['DFITCCancelOrderField'] = DFITCCancelOrderField



#委托响应类型
DFITCOrderRspDataRtnField = {}
DFITCOrderRspDataRtnField["localOrderID"] = "long"
DFITCOrderRspDataRtnField["spdOrderID"] = "long"
DFITCOrderRspDataRtnField["orderStatus"] = "short"
DFITCOrderRspDataRtnField["lRequestID"] = "long"
DFITCOrderRspDataRtnField["fee"] = "float"
DFITCOrderRspDataRtnField["margin"] = "float"
DFITCOrderRspDataRtnField["customCategory"] = "string"
DFITCOrderRspDataRtnField["accountID"] = "string"
DFITCOrderRspDataRtnField["instrumentID"] = "string"
DFITCOrderRspDataRtnField["sessionID"] = "long"
DFITCOrderRspDataRtnField["exchangeID"] = "string"
DFITCOrderRspDataRtnField["buySellType"] = "short"
DFITCOrderRspDataRtnField["openCloseType"] = "int"
DFITCOrderRspDataRtnField["instrumentType"] = "int"
DFITCOrderRspDataRtnField["speculator"] = "int"
DFITCOrderRspDataRtnField["insertPrice"] = "float"
DFITCOrderRspDataRtnField["profitLossPrice"] = "float"
DFITCOrderRspDataRtnField["minMatchAmount"] = "long"
DFITCOrderRspDataRtnField["orderAmount"] = "long"
DFITCOrderRspDataRtnField["insertType"] = "int"
DFITCOrderRspDataRtnField["orderType"] = "int"
DFITCOrderRspDataRtnField["orderProperty"] = "char"
DFITCOrderRspDataRtnField["clientID"] = "string"
structDict['DFITCOrderRspDataRtnField'] = DFITCOrderRspDataRtnField




#查询资金数据类型
DFITCCapitalField = {}
DFITCCapitalField["lRequestID"] = "long"
DFITCCapitalField["accountID"] = "string"
structDict['DFITCCapitalField'] = DFITCCapitalField



#查询持仓数据类型
DFITCPositionField = {}
DFITCPositionField["lRequestID"] = "long"
DFITCPositionField["accountID"] = "string"
DFITCPositionField["instrumentID"] = "string"
DFITCPositionField["instrumentType"] = "int"
structDict['DFITCPositionField'] = DFITCPositionField



#交易所合约
DFITCExchangeInstrumentField = {}
DFITCExchangeInstrumentField["lRequestID"] = "long"
DFITCExchangeInstrumentField["accountID"] = "string"
DFITCExchangeInstrumentField["exchangeID"] = "string"
DFITCExchangeInstrumentField["instrumentType"] = "int"
structDict['DFITCExchangeInstrumentField'] = DFITCExchangeInstrumentField



#用户登录数据类型
DFITCUserLoginField = {}
DFITCUserLoginField["lRequestID"] = "long"
DFITCUserLoginField["accountID"] = "string"
DFITCUserLoginField["passwd"] = "string"
DFITCUserLoginField["companyID"] = "short"
structDict['DFITCUserLoginField'] = DFITCUserLoginField



#用户退出类型
DFITCUserLogoutField = {}
DFITCUserLogoutField["lRequestID"] = "long"
DFITCUserLogoutField["accountID"] = "string"
DFITCUserLogoutField["sessionID"] = "long"
structDict['DFITCUserLogoutField'] = DFITCUserLogoutField



#委托回报
DFITCOrderRtnField = {}
DFITCOrderRtnField["localOrderID"] = "long"
DFITCOrderRtnField["spdOrderID"] = "long"
DFITCOrderRtnField["OrderSysID"] = "string"
DFITCOrderRtnField["orderStatus"] = "short"
DFITCOrderRtnField["sessionID"] = "long"
DFITCOrderRtnField["SuspendTime"] = "string"
DFITCOrderRtnField["instrumentID"] = "string"
DFITCOrderRtnField["exchangeID"] = "string"
DFITCOrderRtnField["buySellType"] = "short"
DFITCOrderRtnField["openCloseType"] = "int"
DFITCOrderRtnField["instrumentType"] = "int"
DFITCOrderRtnField["speculator"] = "int"
DFITCOrderRtnField["insertPrice"] = "float"
DFITCOrderRtnField["profitLossPrice"] = "float"
DFITCOrderRtnField["accountID"] = "string"
DFITCOrderRtnField["cancelAmount"] = "long"
DFITCOrderRtnField["orderAmount"] = "long"
DFITCOrderRtnField["insertType"] = "int"
DFITCOrderRtnField["orderType"] = "int"
DFITCOrderRtnField["extSpdOrderID"] = "long"
DFITCOrderRtnField["reservedType2"] = "int"
DFITCOrderRtnField["customCategory"] = "string"
DFITCOrderRtnField["orderProperty"] = "char"
DFITCOrderRtnField["minMatchAmount"] = "long"
DFITCOrderRtnField["clientID"] = "string"
DFITCOrderRtnField["statusMsg"] = "string"
structDict['DFITCOrderRtnField'] = DFITCOrderRtnField



#成交回报
DFITCMatchRtnField = {}
DFITCMatchRtnField["localOrderID"] = "long"
DFITCMatchRtnField["OrderSysID"] = "string"
DFITCMatchRtnField["matchID"] = "string"
DFITCMatchRtnField["instrumentID"] = "string"
DFITCMatchRtnField["buySellType"] = "short"
DFITCMatchRtnField["openCloseType"] = "int"
DFITCMatchRtnField["matchedPrice"] = "float"
DFITCMatchRtnField["orderAmount"] = "long"
DFITCMatchRtnField["matchedAmount"] = "long"
DFITCMatchRtnField["matchedTime"] = "string"
DFITCMatchRtnField["insertPrice"] = "float"
DFITCMatchRtnField["spdOrderID"] = "long"
DFITCMatchRtnField["matchType"] = "long"
DFITCMatchRtnField["speculator"] = "int"
DFITCMatchRtnField["exchangeID"] = "string"
DFITCMatchRtnField["fee"] = "float"
DFITCMatchRtnField["sessionID"] = "long"
DFITCMatchRtnField["instrumentType"] = "int"
DFITCMatchRtnField["accountID"] = "string"
DFITCMatchRtnField["orderStatus"] = "short"
DFITCMatchRtnField["margin"] = "float"
DFITCMatchRtnField["frozenCapita"] = "float"
DFITCMatchRtnField["adjustmentInfo"] = "string"
DFITCMatchRtnField["customCategory"] = "string"
DFITCMatchRtnField["turnover"] = "float"
DFITCMatchRtnField["orderType"] = "int"
DFITCMatchRtnField["insertType"] = "int"
DFITCMatchRtnField["clientID"] = "string"
structDict['DFITCMatchRtnField'] = DFITCMatchRtnField



#撤单回报
DFITCOrderCanceledRtnField = {}
DFITCOrderCanceledRtnField["localOrderID"] = "long"
DFITCOrderCanceledRtnField["OrderSysID"] = "string"
DFITCOrderCanceledRtnField["instrumentID"] = "string"
DFITCOrderCanceledRtnField["insertPrice"] = "float"
DFITCOrderCanceledRtnField["buySellType"] = "short"
DFITCOrderCanceledRtnField["openCloseType"] = "int"
DFITCOrderCanceledRtnField["cancelAmount"] = "long"
DFITCOrderCanceledRtnField["spdOrderID"] = "long"
DFITCOrderCanceledRtnField["speculator"] = "int"
DFITCOrderCanceledRtnField["exchangeID"] = "string"
DFITCOrderCanceledRtnField["canceledTime"] = "string"
DFITCOrderCanceledRtnField["sessionID"] = "long"
DFITCOrderCanceledRtnField["orderStatus"] = "short"
DFITCOrderCanceledRtnField["instrumentType"] = "int"
DFITCOrderCanceledRtnField["accountID"] = "string"
DFITCOrderCanceledRtnField["orderAmount"] = "long"
DFITCOrderCanceledRtnField["margin"] = "float"
DFITCOrderCanceledRtnField["fee"] = "float"
DFITCOrderCanceledRtnField["customCategory"] = "string"
DFITCOrderCanceledRtnField["profitLossPrice"] = "float"
DFITCOrderCanceledRtnField["minMatchAmount"] = "long"
DFITCOrderCanceledRtnField["insertType"] = "int"
DFITCOrderCanceledRtnField["clientID"] = "string"
DFITCOrderCanceledRtnField["statusMsg"] = "string"
DFITCOrderCanceledRtnField["orderProperty"] = "char"
structDict['DFITCOrderCanceledRtnField'] = DFITCOrderCanceledRtnField



#错误信息
DFITCErrorRtnField = {}
DFITCErrorRtnField["requestID"] = "long"
DFITCErrorRtnField["sessionID"] = "long"
DFITCErrorRtnField["accountID"] = "string"
DFITCErrorRtnField["nErrorID"] = "int"
DFITCErrorRtnField["spdOrderID"] = "long"
DFITCErrorRtnField["localOrderID"] = "long"
DFITCErrorRtnField["errorMsg"] = "string"
DFITCErrorRtnField["instrumentID"] = "string"
structDict['DFITCErrorRtnField'] = DFITCErrorRtnField



#返回资金信息
DFITCCapitalInfoRtnField = {}
DFITCCapitalInfoRtnField["requestID"] = "long"
DFITCCapitalInfoRtnField["accountID"] = "string"
DFITCCapitalInfoRtnField["preEquity"] = "float"
DFITCCapitalInfoRtnField["todayEquity"] = "float"
DFITCCapitalInfoRtnField["closeProfitLoss"] = "float"
DFITCCapitalInfoRtnField["positionProfitLoss"] = "float"
DFITCCapitalInfoRtnField["frozenMargin"] = "float"
DFITCCapitalInfoRtnField["margin"] = "float"
DFITCCapitalInfoRtnField["fee"] = "float"
DFITCCapitalInfoRtnField["available"] = "float"
DFITCCapitalInfoRtnField["withdraw"] = "float"
DFITCCapitalInfoRtnField["riskDegree"] = "float"
DFITCCapitalInfoRtnField["todayPremiumIncome"] = "float"
DFITCCapitalInfoRtnField["todayPremiumPay"] = "float"
DFITCCapitalInfoRtnField["yesterdayPremium"] = "float"
DFITCCapitalInfoRtnField["optMarketValue"] = "float"
DFITCCapitalInfoRtnField["floatProfitLoss"] = "float"
DFITCCapitalInfoRtnField["totFundOut"] = "float"
DFITCCapitalInfoRtnField["totFundIn"] = "float"
structDict['DFITCCapitalInfoRtnField'] = DFITCCapitalInfoRtnField



#返回持仓信息
DFITCPositionInfoRtnField = {}
DFITCPositionInfoRtnField["lRequestID"] = "long"
DFITCPositionInfoRtnField["accountID"] = "string"
DFITCPositionInfoRtnField["exchangeID"] = "string"
DFITCPositionInfoRtnField["instrumentID"] = "string"
DFITCPositionInfoRtnField["buySellType"] = "short"
DFITCPositionInfoRtnField["openAvgPrice"] = "float"
DFITCPositionInfoRtnField["positionAvgPrice"] = "float"
DFITCPositionInfoRtnField["positionAmount"] = "long"
DFITCPositionInfoRtnField["totalAvaiAmount"] = "long"
DFITCPositionInfoRtnField["todayAvaiAmount"] = "long"
DFITCPositionInfoRtnField["lastAvaiAmount"] = "long"
DFITCPositionInfoRtnField["todayAmount"] = "long"
DFITCPositionInfoRtnField["lastAmount"] = "long"
DFITCPositionInfoRtnField["tradingAmount"] = "long"
DFITCPositionInfoRtnField["datePositionProfitLoss"] = "float"
DFITCPositionInfoRtnField["dateCloseProfitLoss"] = "float"
DFITCPositionInfoRtnField["dPremium"] = "float"
DFITCPositionInfoRtnField["floatProfitLoss"] = "float"
DFITCPositionInfoRtnField["dMargin"] = "float"
DFITCPositionInfoRtnField["speculator"] = "int"
DFITCPositionInfoRtnField["clientID"] = "string"
DFITCPositionInfoRtnField["preSettlementPrice"] = "float"
DFITCPositionInfoRtnField["instrumentType"] = "int"
DFITCPositionInfoRtnField["yesterdayTradingAmount"] = "long"
structDict['DFITCPositionInfoRtnField'] = DFITCPositionInfoRtnField



#用户登录返回信息
DFITCUserLoginInfoRtnField = {}
DFITCUserLoginInfoRtnField["lRequestID"] = "long"
DFITCUserLoginInfoRtnField["accountID"] = "string"
DFITCUserLoginInfoRtnField["loginResult"] = "int"
DFITCUserLoginInfoRtnField["initLocalOrderID"] = "long"
DFITCUserLoginInfoRtnField["sessionID"] = "long"
DFITCUserLoginInfoRtnField["nErrorID"] = "int"
DFITCUserLoginInfoRtnField["errorMsg"] = "string"
DFITCUserLoginInfoRtnField["DCEtime"] = "string"
DFITCUserLoginInfoRtnField["SHFETime"] = "string"
DFITCUserLoginInfoRtnField["CFFEXTime"] = "string"
DFITCUserLoginInfoRtnField["CZCETime"] = "string"
DFITCUserLoginInfoRtnField["INETime"] = "string"
structDict['DFITCUserLoginInfoRtnField'] = DFITCUserLoginInfoRtnField



#用户退出返回信息
DFITCUserLogoutInfoRtnField = {}
DFITCUserLogoutInfoRtnField["lRequestID"] = "long"
DFITCUserLogoutInfoRtnField["accountID"] = "string"
DFITCUserLogoutInfoRtnField["logoutResult"] = "int"
DFITCUserLogoutInfoRtnField["nErrorID"] = "int"
DFITCUserLogoutInfoRtnField["errorMsg"] = "string"
structDict['DFITCUserLogoutInfoRtnField'] = DFITCUserLogoutInfoRtnField



#套利合约查询
DFITCAbiInstrumentField = {}
DFITCAbiInstrumentField["lRequestID"] = "long"
DFITCAbiInstrumentField["accountID"] = "string"
DFITCAbiInstrumentField["exchangeID"] = "string"
structDict['DFITCAbiInstrumentField'] = DFITCAbiInstrumentField



#套利合约返回信息
DFITCAbiInstrumentRtnField = {}
DFITCAbiInstrumentRtnField["lRequestID"] = "long"
DFITCAbiInstrumentRtnField["exchangeID"] = "string"
DFITCAbiInstrumentRtnField["InstrumentID"] = "string"
DFITCAbiInstrumentRtnField["instrumentName"] = "string"
structDict['DFITCAbiInstrumentRtnField'] = DFITCAbiInstrumentRtnField



#指定的合约
DFITCSpecificInstrumentField = {}
DFITCSpecificInstrumentField["lRequestID"] = "long"
DFITCSpecificInstrumentField["accountID"] = "string"
DFITCSpecificInstrumentField["InstrumentID"] = "string"
DFITCSpecificInstrumentField["exchangeID"] = "string"
DFITCSpecificInstrumentField["instrumentType"] = "int"
structDict['DFITCSpecificInstrumentField'] = DFITCSpecificInstrumentField




#指定的合约信息
DFITCSpecificInstrumentFieldEX = {}
DFITCSpecificInstrumentFieldEX["lRequestID"] = "long"
DFITCSpecificInstrumentFieldEX["accountID"] = "string"
DFITCSpecificInstrumentFieldEX["FunctionID"] = "string"
DFITCSpecificInstrumentFieldEX["InstrumentID"] = "string"
DFITCSpecificInstrumentFieldEX["exchangeID"] = "string"
DFITCSpecificInstrumentFieldEX["instrumentType"] = "int"
structDict['DFITCSpecificInstrumentFieldEX'] = DFITCSpecificInstrumentFieldEX



#行情订阅返回信息
DFITCActiveContractField = {}
DFITCActiveContractField["lRequestID"] = "long"
DFITCActiveContractField["activeContract"] = "string"
structDict['DFITCActiveContractField'] = DFITCActiveContractField



#交易所合约返回信息
DFITCExchangeInstrumentRtnField = {}
DFITCExchangeInstrumentRtnField["lRequestID"] = "long"
DFITCExchangeInstrumentRtnField["exchangeID"] = "string"
DFITCExchangeInstrumentRtnField["instrumentID"] = "string"
DFITCExchangeInstrumentRtnField["VarietyName"] = "string"
DFITCExchangeInstrumentRtnField["instrumentType"] = "int"
DFITCExchangeInstrumentRtnField["orderTopLimit"] = "long"
DFITCExchangeInstrumentRtnField["mktOrderTopLimit"] = "long"
DFITCExchangeInstrumentRtnField["contractMultiplier"] = "float"
DFITCExchangeInstrumentRtnField["minPriceFluctuation"] = "float"
DFITCExchangeInstrumentRtnField["instrumentMaturity"] = "string"
DFITCExchangeInstrumentRtnField["upperLimitPrice"] = "float"
DFITCExchangeInstrumentRtnField["lowerLimitPrice"] = "float"
DFITCExchangeInstrumentRtnField["preClosePrice"] = "float"
DFITCExchangeInstrumentRtnField["preSettlementPrice"] = "float"
DFITCExchangeInstrumentRtnField["settlementPrice"] = "float"
DFITCExchangeInstrumentRtnField["preOpenInterest"] = "long"
DFITCExchangeInstrumentRtnField["instrumentPrefix"] = "string"
DFITCExchangeInstrumentRtnField["instrumentExpiration"] = "string"
DFITCExchangeInstrumentRtnField["underlying"] = "string"
DFITCExchangeInstrumentRtnField["optionType"] = "int"
DFITCExchangeInstrumentRtnField["strikePrice"] = "float"
DFITCExchangeInstrumentRtnField["exchangeRiskDegree"] = "float"
DFITCExchangeInstrumentRtnField["minMargin"] = "float"
DFITCExchangeInstrumentRtnField["tradeSize"] = "long"
structDict['DFITCExchangeInstrumentRtnField'] = DFITCExchangeInstrumentRtnField



#委托查询数据结构
DFITCOrderField = {}
DFITCOrderField["lRequestID"] = "long"
DFITCOrderField["accountID"] = "string"
DFITCOrderField["instrumentType"] = "int"
DFITCOrderField["customCategory"] = "string"
DFITCOrderField["orderStatus"] = "short"
DFITCOrderField["orderType"] = "int"
DFITCOrderField["spdOrderID"] = "long"
DFITCOrderField["localOrderID"] = "long"
DFITCOrderField["instrumentID"] = "string"
structDict['DFITCOrderField'] = DFITCOrderField



#成交查询数据结构
DFITCMatchField = {}
DFITCMatchField["lRequestID"] = "long"
DFITCMatchField["accountID"] = "string"
DFITCMatchField["instrumentType"] = "int"
DFITCMatchField["customCategory"] = "string"
DFITCMatchField["orderType"] = "int"
DFITCMatchField["spdOrderID"] = "long"
DFITCMatchField["instrumentID"] = "string"
structDict['DFITCMatchField'] = DFITCMatchField



#委托查询响应数据结构
DFITCOrderCommRtnField = {}
DFITCOrderCommRtnField["lRequestID"] = "long"
DFITCOrderCommRtnField["spdOrderID"] = "long"
DFITCOrderCommRtnField["orderStatus"] = "short"
DFITCOrderCommRtnField["instrumentID"] = "string"
DFITCOrderCommRtnField["buySellType"] = "short"
DFITCOrderCommRtnField["openClose"] = "int"
DFITCOrderCommRtnField["insertPrice"] = "float"
DFITCOrderCommRtnField["orderAmount"] = "long"
DFITCOrderCommRtnField["matchedPrice"] = "float"
DFITCOrderCommRtnField["matchedAmount"] = "long"
DFITCOrderCommRtnField["cancelAmount"] = "long"
DFITCOrderCommRtnField["insertType"] = "int"
DFITCOrderCommRtnField["speculator"] = "int"
DFITCOrderCommRtnField["commTime"] = "string"
DFITCOrderCommRtnField["submitTime"] = "string"
DFITCOrderCommRtnField["clientID"] = "string"
DFITCOrderCommRtnField["exchangeID"] = "string"
DFITCOrderCommRtnField["operStation"] = "string"
DFITCOrderCommRtnField["accountID"] = "string"
DFITCOrderCommRtnField["instrumentType"] = "int"
DFITCOrderCommRtnField["sessionId"] = "long"
DFITCOrderCommRtnField["reservedType2"] = "int"
DFITCOrderCommRtnField["OrderSysID"] = "string"
DFITCOrderCommRtnField["customCategory"] = "string"
DFITCOrderCommRtnField["margin"] = "float"
DFITCOrderCommRtnField["fee"] = "float"
DFITCOrderCommRtnField["localOrderID"] = "long"
DFITCOrderCommRtnField["profitLossPrice"] = "float"
DFITCOrderCommRtnField["orderType"] = "int"
DFITCOrderCommRtnField["orderProperty"] = "char"
structDict['DFITCOrderCommRtnField'] = DFITCOrderCommRtnField



#成交查询数据响应
DFITCMatchedRtnField = {}
DFITCMatchedRtnField["lRequestID"] = "long"
DFITCMatchedRtnField["spdOrderID"] = "long"
DFITCMatchedRtnField["accountID"] = "string"
DFITCMatchedRtnField["exchangeID"] = "string"
DFITCMatchedRtnField["instrumentID"] = "string"
DFITCMatchedRtnField["buySellType"] = "short"
DFITCMatchedRtnField["openClose"] = "int"
DFITCMatchedRtnField["matchedPrice"] = "float"
DFITCMatchedRtnField["matchedAmount"] = "long"
DFITCMatchedRtnField["matchedMort"] = "float"
DFITCMatchedRtnField["speculator"] = "int"
DFITCMatchedRtnField["matchedTime"] = "string"
DFITCMatchedRtnField["matchedID"] = "string"
DFITCMatchedRtnField["localOrderID"] = "long"
DFITCMatchedRtnField["clientID"] = "string"
DFITCMatchedRtnField["matchType"] = "long"
DFITCMatchedRtnField["instrumentType"] = "int"
DFITCMatchedRtnField["sessionId"] = "long"
DFITCMatchedRtnField["reservedType2"] = "int"
DFITCMatchedRtnField["customCategory"] = "string"
DFITCMatchedRtnField["fee"] = "float"
DFITCMatchedRtnField["orderType"] = "int"
DFITCMatchedRtnField["OrderSysID"] = "string"
structDict['DFITCMatchedRtnField'] = DFITCMatchedRtnField



#返回合约信息数据结构
DFITCInstrumentRtnField = {}
DFITCInstrumentRtnField["lRequestID"] = "long"
DFITCInstrumentRtnField["instrumentID"] = "string"
DFITCInstrumentRtnField["longMarginRatio"] = "float"
DFITCInstrumentRtnField["shortMarginRatio"] = "float"
DFITCInstrumentRtnField["longMarginRatioByVolume"] = "float"
DFITCInstrumentRtnField["shortMarginRatioByVolume"] = "float"
DFITCInstrumentRtnField["openFeeVolRatio"] = "float"
DFITCInstrumentRtnField["closeFeeVolRatio"] = "float"
DFITCInstrumentRtnField["closeTodayFeeVolRatio"] = "float"
DFITCInstrumentRtnField["openFeeAmtRatio"] = "float"
DFITCInstrumentRtnField["closeFeeAmtRatio"] = "float"
DFITCInstrumentRtnField["closeTodayFeeAmtRatio"] = "float"
DFITCInstrumentRtnField["orderTopLimit"] = "long"
DFITCInstrumentRtnField["contractMultiplier"] = "float"
DFITCInstrumentRtnField["minimumPriceChange"] = "float"
DFITCInstrumentRtnField["instrumentType"] = "int"
DFITCInstrumentRtnField["instrumentMaturity"] = "string"
DFITCInstrumentRtnField["computeMode"] = "int"
DFITCInstrumentRtnField["atMoneyNorm"] = "float"
DFITCInstrumentRtnField["upperLimitPrice"] = "float"
DFITCInstrumentRtnField["lowerLimitPrice"] = "float"
DFITCInstrumentRtnField["preClosePrice"] = "float"
DFITCInstrumentRtnField["preSettlementPrice"] = "float"
DFITCInstrumentRtnField["settlementPrice"] = "float"
DFITCInstrumentRtnField["preOpenInterest"] = "long"
DFITCInstrumentRtnField["optExecRatio"] = "float"
DFITCInstrumentRtnField["optExecRatioPerVol"] = "float"
structDict['DFITCInstrumentRtnField'] = DFITCInstrumentRtnField



#深度行情
DFITCDepthMarketDataField = {}
DFITCDepthMarketDataField["tradingDay"] = "string"
DFITCDepthMarketDataField["instrumentID"] = "string"
DFITCDepthMarketDataField["exchangeID"] = "string"
DFITCDepthMarketDataField["exchangeInstID"] = "string"
DFITCDepthMarketDataField["lastPrice"] = "float"
DFITCDepthMarketDataField["preSettlementPrice"] = "float"
DFITCDepthMarketDataField["preClosePrice"] = "float"
DFITCDepthMarketDataField["preOpenInterest"] = "long"
DFITCDepthMarketDataField["openPrice"] = "float"
DFITCDepthMarketDataField["highestPrice"] = "float"
DFITCDepthMarketDataField["lowestPrice"] = "float"
DFITCDepthMarketDataField["Volume"] = "long"
DFITCDepthMarketDataField["turnover"] = "float"
DFITCDepthMarketDataField["openInterest"] = "long"
DFITCDepthMarketDataField["closePrice"] = "float"
DFITCDepthMarketDataField["settlementPrice"] = "float"
DFITCDepthMarketDataField["upperLimitPrice"] = "float"
DFITCDepthMarketDataField["lowerLimitPrice"] = "float"
DFITCDepthMarketDataField["preDelta"] = "float"
DFITCDepthMarketDataField["currDelta"] = "float"
DFITCDepthMarketDataField["UpdateTime"] = "string"
DFITCDepthMarketDataField["UpdateMillisec"] = "int"
DFITCDepthMarketDataField["BidPrice1"] = "float"
DFITCDepthMarketDataField["BidVolume1"] = "int"
DFITCDepthMarketDataField["AskPrice1"] = "float"
DFITCDepthMarketDataField["AskVolume1"] = "int"
DFITCDepthMarketDataField["BidPrice2"] = "float"
DFITCDepthMarketDataField["BidVolume2"] = "int"
DFITCDepthMarketDataField["AskPrice2"] = "float"
DFITCDepthMarketDataField["AskVolume2"] = "int"
DFITCDepthMarketDataField["BidPrice3"] = "float"
DFITCDepthMarketDataField["BidVolume3"] = "int"
DFITCDepthMarketDataField["AskPrice3"] = "float"
DFITCDepthMarketDataField["AskVolume3"] = "int"
DFITCDepthMarketDataField["BidPrice4"] = "float"
DFITCDepthMarketDataField["BidVolume4"] = "int"
DFITCDepthMarketDataField["AskPrice4"] = "float"
DFITCDepthMarketDataField["AskVolume4"] = "int"
DFITCDepthMarketDataField["BidPrice5"] = "float"
DFITCDepthMarketDataField["BidVolume5"] = "int"
DFITCDepthMarketDataField["AskPrice5"] = "float"
DFITCDepthMarketDataField["AskVolume5"] = "int"
DFITCDepthMarketDataField["AveragePrice"] = "float"
DFITCDepthMarketDataField["XSpeedTime"] = "string"
structDict['DFITCDepthMarketDataField'] = DFITCDepthMarketDataField


#********************************期权扩展行情************************************


DFITCMarketDataFieldEx = {}
DFITCMarketDataFieldEx["FunctionID"] = "string"
DFITCMarketDataFieldEx["tradingDay"] = "string"
DFITCMarketDataFieldEx["UpdateTime"] = "string"
DFITCMarketDataFieldEx["UpdateMillisec"] = "int"
DFITCMarketDataFieldEx["instrumentID"] = "string"
DFITCMarketDataFieldEx["ExtMarketData"] = "string"
structDict['DFITCMarketDataFieldEx'] = DFITCMarketDataFieldEx

#********************************************************************************



DFITCCustomMarketDataField = {}
DFITCCustomMarketDataField["instrumentID"] = "string"
DFITCCustomMarketDataField["exchangeID"] = "string"
DFITCCustomMarketDataField["bidVolume1"] = "int"
DFITCCustomMarketDataField["bidPrice1"] = "float"
DFITCCustomMarketDataField["askVolume1"] = "int"
DFITCCustomMarketDataField["askPrice1"] = "float"
DFITCCustomMarketDataField["lastPrice"] = "float"
structDict['DFITCCustomMarketDataField'] = DFITCCustomMarketDataField


#查询持仓明细
DFITCPositionDetailField = {}
DFITCPositionDetailField["lRequestID"] = "long"
DFITCPositionDetailField["accountID"] = "string"
DFITCPositionDetailField["instrumentID"] = "string"
DFITCPositionDetailField["instrumentType"] = "int"
structDict['DFITCPositionDetailField'] = DFITCPositionDetailField



#查询持仓明细响应
DFITCPositionDetailRtnField = {}
DFITCPositionDetailRtnField["lRequestID"] = "long"
DFITCPositionDetailRtnField["accountID"] = "string"
DFITCPositionDetailRtnField["exchangeID"] = "string"
DFITCPositionDetailRtnField["instrumentID"] = "string"
DFITCPositionDetailRtnField["buySellType"] = "short"
DFITCPositionDetailRtnField["openPrice"] = "float"
DFITCPositionDetailRtnField["volume"] = "long"
DFITCPositionDetailRtnField["matchID"] = "string"
DFITCPositionDetailRtnField["matchedDate"] = "string"
DFITCPositionDetailRtnField["datePositionProfitLoss"] = "float"
DFITCPositionDetailRtnField["dateCloseProfitLoss"] = "float"
DFITCPositionDetailRtnField["floatProfitLoss"] = "float"
DFITCPositionDetailRtnField["dMargin"] = "float"
DFITCPositionDetailRtnField["speculator"] = "int"
DFITCPositionDetailRtnField["clientID"] = "string"
DFITCPositionDetailRtnField["preSettlementPrice"] = "float"
DFITCPositionDetailRtnField["instrumentType"] = "int"
DFITCPositionDetailRtnField["spdOrderID"] = "long"
DFITCPositionDetailRtnField["customCategory"] = "string"
DFITCPositionDetailRtnField["closeOrderVol"] = "long"
DFITCPositionDetailRtnField["closeMatchVol"] = "long"
DFITCPositionDetailRtnField["positionDateType"] = "int"
structDict['DFITCPositionDetailRtnField'] = DFITCPositionDetailRtnField



#用户事件通知信息
DFITCTradingNoticeInfoField = {}
DFITCTradingNoticeInfoField["accountID"] = "string"
DFITCTradingNoticeInfoField["SendTime"] = "string"
DFITCTradingNoticeInfoField["FieldContent"] = "string"
DFITCTradingNoticeInfoField["noticeType"] = "short"
structDict['DFITCTradingNoticeInfoField'] = DFITCTradingNoticeInfoField



#合约交易状态通知信息
DFITCInstrumentStatusField = {}
DFITCInstrumentStatusField["ExchangeID"] = "string"
DFITCInstrumentStatusField["InstrumentID"] = "string"
DFITCInstrumentStatusField["InstrumentStatus"] = "int"
DFITCInstrumentStatusField["TradingSegmentSN"] = "int"
DFITCInstrumentStatusField["EnterTime"] = "string"
DFITCInstrumentStatusField["EnterReason"] = "short"
structDict['DFITCInstrumentStatusField'] = DFITCInstrumentStatusField



#用户密码修改
DFITCResetPwdField = {}
DFITCResetPwdField["lRequestID"] = "long"
DFITCResetPwdField["accountID"] = "string"
DFITCResetPwdField["oldpasswd"] = "string"
DFITCResetPwdField["newpasswd"] = "string"
structDict['DFITCResetPwdField'] = DFITCResetPwdField



#用户密码修改返回信息
DFITCResetPwdRspField = {}
DFITCResetPwdRspField["lRequestID"] = "long"
DFITCResetPwdRspField["accountID"] = "string"
DFITCResetPwdRspField["execState"] = "int"
structDict['DFITCResetPwdRspField'] = DFITCResetPwdRspField



#账单确认
DFITCBillConfirmField = {}
DFITCBillConfirmField["lRequestID"] = "long"
DFITCBillConfirmField["accountID"] = "string"
DFITCBillConfirmField["date"] = "string"
DFITCBillConfirmField["confirmFlag"] = "int"
structDict['DFITCBillConfirmField'] = DFITCBillConfirmField



#账单确认响应
DFITCBillConfirmRspField = {}
DFITCBillConfirmRspField["lRequestID"] = "long"
DFITCBillConfirmRspField["accountID"] = "string"
DFITCBillConfirmRspField["execState"] = "int"
structDict['DFITCBillConfirmRspField'] = DFITCBillConfirmRspField



#交易编码查询
DFITCQryTradeCodeField = {}
DFITCQryTradeCodeField["lRequestID"] = "long"
DFITCQryTradeCodeField["accountID"] = "string"
structDict['DFITCQryTradeCodeField'] = DFITCQryTradeCodeField



#交易编码查询响应
DFITCQryTradeCodeRtnField = {}
DFITCQryTradeCodeRtnField["lRequestID"] = "long"
DFITCQryTradeCodeRtnField["accountID"] = "string"
DFITCQryTradeCodeRtnField["exchangeCode"] = "string"
DFITCQryTradeCodeRtnField["clientID"] = "string"
DFITCQryTradeCodeRtnField["clientStatus"] = "int"
DFITCQryTradeCodeRtnField["clientIDType"] = "int"
structDict['DFITCQryTradeCodeRtnField'] = DFITCQryTradeCodeRtnField



#浮盈浮亏是否计算到权益中
DFITCEquityComputModeRtnField = {}
DFITCEquityComputModeRtnField["capConMode"] = "long"
DFITCEquityComputModeRtnField["priceNote"] = "int"
structDict['DFITCEquityComputModeRtnField'] = DFITCEquityComputModeRtnField



#查询账单
DFITCQryBillField = {}
DFITCQryBillField["lRequestID"] = "long"
DFITCQryBillField["accountID"] = "string"
DFITCQryBillField["date"] = "string"
structDict['DFITCQryBillField'] = DFITCQryBillField



#查询账单响应
DFITCQryBillRtnField = {}
DFITCQryBillRtnField["lRequestID"] = "long"
DFITCQryBillRtnField["accountID"] = "string"
DFITCQryBillRtnField["message"] = "string"
structDict['DFITCQryBillRtnField'] = DFITCQryBillRtnField



#厂商ID确认请求
DFITCProductField = {}
DFITCProductField["productID"] = "string"
DFITCProductField["vendorID"] = "string"
structDict['DFITCProductField'] = DFITCProductField



#厂商ID确认响应
DFITCProductRtnField = {}
DFITCProductRtnField["productID"] = "string"
DFITCProductRtnField["vendorID"] = "string"
DFITCProductRtnField["productOnlineCount"] = "long"
DFITCProductRtnField["brokerInfoName"] = "string"
DFITCProductRtnField["frontID"] = "int"
structDict['DFITCProductRtnField'] = DFITCProductRtnField


#查询交易日请求
DFITCTradingDayField = {}
DFITCTradingDayField["lRequestID"] = "long"
structDict['DFITCTradingDayField'] = DFITCTradingDayField



#交易日请求响应
DFITCTradingDayRtnField = {}
DFITCTradingDayRtnField["lRequestID"] = "long"
DFITCTradingDayRtnField["date"] = "string"
structDict['DFITCTradingDayRtnField'] = DFITCTradingDayRtnField



#询价通知订阅请求
DFITCQuoteSubscribeField = {}
DFITCQuoteSubscribeField["lRequestID"] = "long"
DFITCQuoteSubscribeField["accountID"] = "string"
DFITCQuoteSubscribeField["exchangeID"] = "string"
structDict['DFITCQuoteSubscribeField'] = DFITCQuoteSubscribeField


#询价通知订阅响应
DFITCQuoteSubscribeRspField = {}
DFITCQuoteSubscribeRspField["lRequestID"] = "long"
DFITCQuoteSubscribeRspField["subscribeFlag"] = "int"
DFITCQuoteSubscribeRspField["exchangeID"] = "string"
structDict['DFITCQuoteSubscribeRspField'] = DFITCQuoteSubscribeRspField


#询价通知退订请求
DFITCQuoteUnSubscribeField = {}
DFITCQuoteUnSubscribeField["lRequestID"] = "long"
DFITCQuoteUnSubscribeField["accountID"] = "string"
DFITCQuoteUnSubscribeField["exchangeID"] = "string"
structDict['DFITCQuoteUnSubscribeField'] = DFITCQuoteUnSubscribeField


#询价通知退订响应
DFITCQuoteUnSubscribeRspField = {}
DFITCQuoteUnSubscribeRspField["lRequestID"] = "long"
DFITCQuoteUnSubscribeRspField["subscribeFlag"] = "int"
DFITCQuoteUnSubscribeRspField["exchangeID"] = "string"
structDict['DFITCQuoteUnSubscribeRspField'] = DFITCQuoteUnSubscribeRspField


#询价通知订阅回报
DFITCQuoteSubscribeRtnField = {}
DFITCQuoteSubscribeRtnField["quoteID"] = "string"
DFITCQuoteSubscribeRtnField["exchangeID"] = "string"
DFITCQuoteSubscribeRtnField["instrumentID"] = "string"
DFITCQuoteSubscribeRtnField["source"] = "short"
DFITCQuoteSubscribeRtnField["quoteTime"] = "string"
structDict['DFITCQuoteSubscribeRtnField'] = DFITCQuoteSubscribeRtnField


#询价通知查询请求
DFITCQryQuoteNoticeField = {}
DFITCQryQuoteNoticeField["accountID"] = "string"
DFITCQryQuoteNoticeField["lRequestID"] = "long"
DFITCQryQuoteNoticeField["exchangeID"] = "string"
DFITCQryQuoteNoticeField["instrumentID"] = "string"
structDict['DFITCQryQuoteNoticeField'] = DFITCQryQuoteNoticeField


#询价通知查询响应
DFITCQryQuoteNoticeRtnField = {}
DFITCQryQuoteNoticeRtnField["lRequestID"] = "long"
DFITCQryQuoteNoticeRtnField["quoteID"] = "string"
DFITCQryQuoteNoticeRtnField["exchangeID"] = "string"
DFITCQryQuoteNoticeRtnField["instrumentID"] = "string"
DFITCQryQuoteNoticeRtnField["source"] = "short"
DFITCQryQuoteNoticeRtnField["quoteTime"] = "string"
structDict['DFITCQryQuoteNoticeRtnField'] = DFITCQryQuoteNoticeRtnField


#做市商报单请求
DFITCQuoteInsertField = {}
DFITCQuoteInsertField["accountID"] = "string"
DFITCQuoteInsertField["lRequestID"] = "long"
DFITCQuoteInsertField["localOrderID"] = "long"
DFITCQuoteInsertField["insertType"] = "int"
DFITCQuoteInsertField["instrumentID"] = "string"
DFITCQuoteInsertField["quoteID"] = "string"
DFITCQuoteInsertField["instrumentType"] = "int"
DFITCQuoteInsertField["bOrderAmount"] = "long"
DFITCQuoteInsertField["sOrderAmount"] = "long"
DFITCQuoteInsertField["bInsertPrice"] = "float"
DFITCQuoteInsertField["sInsertPrice"] = "float"
DFITCQuoteInsertField["bOpenCloseType"] = "int"
DFITCQuoteInsertField["sOpenCloseType"] = "int"
DFITCQuoteInsertField["bSpeculator"] = "int"
DFITCQuoteInsertField["sSpeculator"] = "int"
DFITCQuoteInsertField["stayTime"] = "int"
DFITCQuoteInsertField["customCategory"] = "string"
structDict['DFITCQuoteInsertField'] = DFITCQuoteInsertField




#做市商报单响应
DFITCQuoteRspField = {}
DFITCQuoteRspField["localOrderID"] = "long"
DFITCQuoteRspField["spdOrderID"] = "long"
DFITCQuoteRspField["lRequestID"] = "long"
DFITCQuoteRspField["fee"] = "float"
DFITCQuoteRspField["margin"] = "float"
DFITCQuoteRspField["orderTime"] = "string"
DFITCQuoteRspField["orderStatus"] = "short"
DFITCQuoteRspField["customCategory"] = "string"
DFITCQuoteRspField["instrumentID"] = "string"
DFITCQuoteRspField["accountID"] = "string"
DFITCQuoteRspField["quoteID"] = "string"
DFITCQuoteRspField["sessionID"] = "long"
DFITCQuoteRspField["clientID"] = "string"
structDict['DFITCQuoteRspField'] = DFITCQuoteRspField



#做市商报单回报
DFITCQuoteRtnField = {}
DFITCQuoteRtnField["exchangeID"] = "string"
DFITCQuoteRtnField["clientID"] = "string"
DFITCQuoteRtnField["orderSysID"] = "string"
DFITCQuoteRtnField["instrumentID"] = "string"
DFITCQuoteRtnField["localOrderID"] = "long"
DFITCQuoteRtnField["seatCode"] = "string"
DFITCQuoteRtnField["bOpenCloseType"] = "int"
DFITCQuoteRtnField["sOpenCloseType"] = "int"
DFITCQuoteRtnField["speculator"] = "int"
DFITCQuoteRtnField["bOrderAmount"] = "long"
DFITCQuoteRtnField["sOrderAmount"] = "long"
DFITCQuoteRtnField["bInsertPrice"] = "float"
DFITCQuoteRtnField["sInsertPrice"] = "float"
DFITCQuoteRtnField["spdOrderID"] = "long"
DFITCQuoteRtnField["accountID"] = "string"
DFITCQuoteRtnField["instrumentType"] = "int"
DFITCQuoteRtnField["suspendTime"] = "string"
DFITCQuoteRtnField["entrusTeller"] = "string"
DFITCQuoteRtnField["orderStatus"] = "short"
DFITCQuoteRtnField["sessionID"] = "long"
DFITCQuoteRtnField["quoteID"] = "string"
DFITCQuoteRtnField["errorMsg"] = "string"
DFITCQuoteRtnField["customCategory"] = "string"
structDict['DFITCQuoteRtnField'] = DFITCQuoteRtnField




#做市商撤单回报
DFITCQuoteCanceledRtnField = {}
DFITCQuoteCanceledRtnField["exchangeID"] = "string"
DFITCQuoteCanceledRtnField["clientID"] = "string"
DFITCQuoteCanceledRtnField["orderSysID"] = "string"
DFITCQuoteCanceledRtnField["instrumentID"] = "string"
DFITCQuoteCanceledRtnField["localOrderID"] = "long"
DFITCQuoteCanceledRtnField["seatCode"] = "string"
DFITCQuoteCanceledRtnField["bOpenCloseType"] = "int"
DFITCQuoteCanceledRtnField["sOpenCloseType"] = "int"
DFITCQuoteCanceledRtnField["speculator"] = "int"
DFITCQuoteCanceledRtnField["spdOrderID"] = "long"
DFITCQuoteCanceledRtnField["accountID"] = "string"
DFITCQuoteCanceledRtnField["entrusTeller"] = "string"
DFITCQuoteCanceledRtnField["orderStatus"] = "short"
DFITCQuoteCanceledRtnField["cancelAmount"] = "long"
DFITCQuoteCanceledRtnField["fee"] = "float"
DFITCQuoteCanceledRtnField["margin"] = "float"
DFITCQuoteCanceledRtnField["sessionID"] = "long"
DFITCQuoteCanceledRtnField["buySellType"] = "short"
DFITCQuoteCanceledRtnField["quoteID"] = "string"
DFITCQuoteCanceledRtnField["canceledTime"] = "string"
DFITCQuoteCanceledRtnField["customCategory"] = "string"
structDict['DFITCQuoteCanceledRtnField'] = DFITCQuoteCanceledRtnField




#做市商成交回报
DFITCQuoteMatchRtnField = {}
DFITCQuoteMatchRtnField["exchangeID"] = "string"
DFITCQuoteMatchRtnField["clientID"] = "string"
DFITCQuoteMatchRtnField["instrumentID"] = "string"
DFITCQuoteMatchRtnField["seatCode"] = "string"
DFITCQuoteMatchRtnField["localOrderID"] = "long"
DFITCQuoteMatchRtnField["openCloseType"] = "int"
DFITCQuoteMatchRtnField["speculator"] = "int"
DFITCQuoteMatchRtnField["spdOrderID"] = "long"
DFITCQuoteMatchRtnField["OrderSysID"] = "string"
DFITCQuoteMatchRtnField["matchID"] = "string"
DFITCQuoteMatchRtnField["matchedAmount"] = "long"
DFITCQuoteMatchRtnField["matchedPrice"] = "float"
DFITCQuoteMatchRtnField["accountID"] = "string"
DFITCQuoteMatchRtnField["turnover"] = "float"
DFITCQuoteMatchRtnField["entrusTeller"] = "string"
DFITCQuoteMatchRtnField["matchedTime"] = "string"
DFITCQuoteMatchRtnField["fee"] = "float"
DFITCQuoteMatchRtnField["insertPrice"] = "float"
DFITCQuoteMatchRtnField["orderAmount"] = "long"
DFITCQuoteMatchRtnField["orderStatus"] = "short"
DFITCQuoteMatchRtnField["margin"] = "float"
DFITCQuoteMatchRtnField["buySellType"] = "short"
DFITCQuoteMatchRtnField["closeTodayAmount"] = "long"
DFITCQuoteMatchRtnField["closePrice"] = "float"
DFITCQuoteMatchRtnField["closeTodayPrice"] = "float"
DFITCQuoteMatchRtnField["adjustmentInfo"] = "string"
DFITCQuoteMatchRtnField["frozenCapita"] = "float"
DFITCQuoteMatchRtnField["dateCloseProfitLoss"] = "float"
DFITCQuoteMatchRtnField["instrumentType"] = "int"
DFITCQuoteMatchRtnField["sessionID"] = "long"
DFITCQuoteMatchRtnField["largeMarginDirect"] = "string"
DFITCQuoteMatchRtnField["quoteID"] = "string"
DFITCQuoteMatchRtnField["customCategory"] = "string"
structDict['DFITCQuoteMatchRtnField'] = DFITCQuoteMatchRtnField



#批量撤单请求
DFITCCancelAllOrderField = {}
DFITCCancelAllOrderField["lRequestID"] = "long"
DFITCCancelAllOrderField["accountID"] = "string"
DFITCCancelAllOrderField["exchangeID"] = "string"
structDict['DFITCCancelAllOrderField'] = DFITCCancelAllOrderField


#批量撤单响应
DFITCCancelAllOrderRspField = {}
DFITCCancelAllOrderRspField["lRequestID"] = "long"
DFITCCancelAllOrderRspField["accountID"] = "string"
DFITCCancelAllOrderRspField["orderStatus"] = "short"
structDict['DFITCCancelAllOrderRspField'] = DFITCCancelAllOrderRspField


#询价请求
DFITCForQuoteField = {}
DFITCForQuoteField["lRequestID"] = "long"
DFITCForQuoteField["accountID"] = "string"
DFITCForQuoteField["instrumentID"] = "string"
structDict['DFITCForQuoteField'] = DFITCForQuoteField


#询价请求响应
DFITCForQuoteRspField = {}
DFITCForQuoteRspField["lRequestID"] = "long"
DFITCForQuoteRspField["spdOrderID"] = "long"
DFITCForQuoteRspField["commTime"] = "string"
structDict['DFITCForQuoteRspField'] = DFITCForQuoteRspField


#询价回报
DFITCForQuoteRtnField = {}
DFITCForQuoteRtnField["spdOrderID"] = "long"
DFITCForQuoteRtnField["sessionID"] = "long"
DFITCForQuoteRtnField["instrumentID"] = "string"
DFITCForQuoteRtnField["exchangeID"] = "string"
DFITCForQuoteRtnField["accountID"] = "string"
DFITCForQuoteRtnField["orderStatus"] = "short"
structDict['DFITCForQuoteRtnField'] = DFITCForQuoteRtnField


#做市商报价委托查询
DFITCQuoteOrderField = {}
DFITCQuoteOrderField["lRequestID"] = "long"
DFITCQuoteOrderField["exchangeID"] = "string"
DFITCQuoteOrderField["accountID"] = "string"
DFITCQuoteOrderField["instrumentID"] = "string"
DFITCQuoteOrderField["localOrderID"] = "long"
DFITCQuoteOrderField["spdOrderID"] = "long"
DFITCQuoteOrderField["orderStatus"] = "short"
structDict['DFITCQuoteOrderField'] = DFITCQuoteOrderField


#做市商报价查询响应
DFITCQuoteOrderRtnField = {}
DFITCQuoteOrderRtnField["lRequestID"] = "long"
DFITCQuoteOrderRtnField["spdOrderID"] = "long"
DFITCQuoteOrderRtnField["orderStatus"] = "short"
DFITCQuoteOrderRtnField["instrumentID"] = "string"
DFITCQuoteOrderRtnField["margin"] = "float"
DFITCQuoteOrderRtnField["fee"] = "float"
DFITCQuoteOrderRtnField["localOrderID"] = "long"
DFITCQuoteOrderRtnField["accountID"] = "string"
DFITCQuoteOrderRtnField["commTime"] = "string"
DFITCQuoteOrderRtnField["submitTime"] = "string"
DFITCQuoteOrderRtnField["exchangeID"] = "string"
DFITCQuoteOrderRtnField["bOrderAmount"] = "long"
DFITCQuoteOrderRtnField["bMatchedAmount"] = "long"
DFITCQuoteOrderRtnField["bCancelAmount"] = "long"
DFITCQuoteOrderRtnField["bInsertPrice"] = "float"
DFITCQuoteOrderRtnField["bMatchedPrice"] = "float"
DFITCQuoteOrderRtnField["bOpenCloseType"] = "int"
DFITCQuoteOrderRtnField["sOrderAmount"] = "long"
DFITCQuoteOrderRtnField["sMatchedAmount"] = "long"
DFITCQuoteOrderRtnField["sCancelAmount"] = "long"
DFITCQuoteOrderRtnField["sInsertPrice"] = "float"
DFITCQuoteOrderRtnField["sMatchedPrice"] = "float"
DFITCQuoteOrderRtnField["sOpenCloseType"] = "int"
DFITCQuoteOrderRtnField["operStation"] = "string"
DFITCQuoteOrderRtnField["sessionID"] = "long"
DFITCQuoteOrderRtnField["quoteID"] = "string"
DFITCQuoteOrderRtnField["customCategory"] = "string"
structDict['DFITCQuoteOrderRtnField'] = DFITCQuoteOrderRtnField


#查询转账银行
DFITCQryTransferBankField = {}
DFITCQryTransferBankField["accountID"] = "string"
DFITCQryTransferBankField["bankID"] = "string"
DFITCQryTransferBankField["lRequestID"] = "long"
structDict['DFITCQryTransferBankField'] = DFITCQryTransferBankField


#转帐银行响应
DFITCTransferBankRspField = {}
DFITCTransferBankRspField["accountID"] = "string"
DFITCTransferBankRspField["bankID"] = "string"
DFITCTransferBankRspField["bankAccount"] = "string"
DFITCTransferBankRspField["currency"] = "string"
DFITCTransferBankRspField["registDate"] = "string"
DFITCTransferBankRspField["lRequestID"] = "long"
structDict['DFITCTransferBankRspField'] = DFITCTransferBankRspField


#查询转账流水
DFITCQryTransferSerialField = {}
DFITCQryTransferSerialField["accountID"] = "string"
DFITCQryTransferSerialField["bankID"] = "string"
DFITCQryTransferSerialField["bankAccount"] = "string"
DFITCQryTransferSerialField["lRequestID"] = "long"
structDict['DFITCQryTransferSerialField'] = DFITCQryTransferSerialField


#转账流水响应
DFITCTransferSerialRspField = {}
DFITCTransferSerialRspField["accountID"] = "string"
DFITCTransferSerialRspField["bankID"] = "string"
DFITCTransferSerialRspField["bankAccount"] = "string"
DFITCTransferSerialRspField["currency"] = "string"
DFITCTransferSerialRspField["applyNum"] = "int"
DFITCTransferSerialRspField["type"] = "int"
DFITCTransferSerialRspField["tradeAmount"] = "float"
DFITCTransferSerialRspField["curFutAccountFund"] = "float"
DFITCTransferSerialRspField["bankSerialNum"] = "int"
DFITCTransferSerialRspField["reqTransferTime"] = "string"
DFITCTransferSerialRspField["dealTransferTime"] = "string"
DFITCTransferSerialRspField["procResult"] = "int"
DFITCTransferSerialRspField["lRequestID"] = "long"
structDict['DFITCTransferSerialRspField'] = DFITCTransferSerialRspField


#资金转账请求信息
DFITCReqTransferField = {}
DFITCReqTransferField["bankID"] = "string"
DFITCReqTransferField["bankAccount"] = "string"
DFITCReqTransferField["bankPassword"] = "string"
DFITCReqTransferField["accountID"] = "string"
DFITCReqTransferField["password"] = "string"
DFITCReqTransferField["currency"] = "string"
DFITCReqTransferField["tradeAmount"] = "float"
DFITCReqTransferField["lRequestID"] = "long"
structDict['DFITCReqTransferField'] = DFITCReqTransferField


#资金转账响应信息
DFITCTransferRspField = {}
DFITCTransferRspField["bankID"] = "string"
DFITCTransferRspField["bankAccount"] = "string"
DFITCTransferRspField["accountID"] = "string"
DFITCTransferRspField["tradeAmount"] = "float"
DFITCTransferRspField["applyNumber"] = "int"
DFITCTransferRspField["lRequestID"] = "long"
structDict['DFITCTransferRspField'] = DFITCTransferRspField


#资金转账通知信息
DFITCTransferRtnField = {}
DFITCTransferRtnField["accountID"] = "string"
DFITCTransferRtnField["bankID"] = "string"
DFITCTransferRtnField["bankAccount"] = "string"
DFITCTransferRtnField["type"] = "int"
DFITCTransferRtnField["tradeAmount"] = "float"
DFITCTransferRtnField["bankSerialNum"] = "int"
DFITCTransferRtnField["applyNumber"] = "int"
DFITCTransferRtnField["sessionID"] = "long"
structDict['DFITCTransferRtnField'] = DFITCTransferRtnField


#银行或主席发起出金冲正通知
DFITCRepealRtnField = {}
DFITCRepealRtnField["accountID"] = "string"
DFITCRepealRtnField["bankID"] = "string"
DFITCRepealRtnField["bankAccount"] = "string"
DFITCRepealRtnField["type"] = "int"
DFITCRepealRtnField["tradeAmount"] = "float"
DFITCRepealRtnField["bankSerialNum"] = "int"
DFITCRepealRtnField["repealSerial"] = "int"
structDict['DFITCRepealRtnField'] = DFITCRepealRtnField


#交易状态查询请求
DFITCQryExchangeStatusField = {}
DFITCQryExchangeStatusField["lRequestID"] = "long"
DFITCQryExchangeStatusField["exchangeID"] = "string"
structDict['DFITCQryExchangeStatusField'] = DFITCQryExchangeStatusField


#交易所状态查询响应
DFITCExchangeStatusRspField = {}
DFITCExchangeStatusRspField["lRequestID"] = "long"
DFITCExchangeStatusRspField["exchangeStatus"] = "int"
DFITCExchangeStatusRspField["exchangeID"] = "string"
structDict['DFITCExchangeStatusRspField'] = DFITCExchangeStatusRspField


#交易所状态通知
DFITCExchangeStatusRtnField = {}
DFITCExchangeStatusRtnField["exchangeID"] = "string"
DFITCExchangeStatusRtnField["instrumentID"] = "string"
DFITCExchangeStatusRtnField["exchangeStatus"] = "int"
structDict['DFITCExchangeStatusRtnField'] = DFITCExchangeStatusRtnField


#行情查询请求
DFITCQryDepthMarketDataField = {}
DFITCQryDepthMarketDataField["lRequestID"] = "long"
DFITCQryDepthMarketDataField["instrumentID"] = "string"
DFITCQryDepthMarketDataField["exchangeID"] = "string"
structDict['DFITCQryDepthMarketDataField'] = DFITCQryDepthMarketDataField


#查询询价请求
DFITCQryForQuoteField = {}
DFITCQryForQuoteField["lRequestID"] = "long"
DFITCQryForQuoteField["accountID"] = "string"
DFITCQryForQuoteField["instrumentID"] = "string"
DFITCQryForQuoteField["exchangeID"] = "string"
structDict['DFITCQryForQuoteField'] = DFITCQryForQuoteField


#查询询价响应
DFITCQryForQuoteRtnField = {}
DFITCQryForQuoteRtnField["lRequestID"] = "long"
DFITCQryForQuoteRtnField["accountID"] = "string"
DFITCQryForQuoteRtnField["spdOrderID"] = "long"
DFITCQryForQuoteRtnField["instrumentID"] = "string"
DFITCQryForQuoteRtnField["exchangeID"] = "string"
DFITCQryForQuoteRtnField["SuspendTime"] = "string"
DFITCQryForQuoteRtnField["orderStatus"] = "short"
structDict['DFITCQryForQuoteRtnField'] = DFITCQryForQuoteRtnField



