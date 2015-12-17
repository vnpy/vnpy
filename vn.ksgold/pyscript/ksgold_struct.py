# encoding: UTF-8

structDict = {}














#用户登录请求
CThostFtdcReqUserLoginField = {}
CThostFtdcReqUserLoginField["accountID"] = "string"
CThostFtdcReqUserLoginField["loginType"] = "int"
CThostFtdcReqUserLoginField["memberID"] = "string"
CThostFtdcReqUserLoginField["password"] = "string"
CThostFtdcReqUserLoginField["tradeDate"] = "string"
CThostFtdcReqUserLoginField["ipGatewayAddress"] = "string"
CThostFtdcReqUserLoginField["portGateway"] = "int"
CThostFtdcReqUserLoginField["localOrderNo"] = "string"
CThostFtdcReqUserLoginField["machineID"] = "int"
CThostFtdcReqUserLoginField["loginbatch"] = "int"
CThostFtdcReqUserLoginField["clientName"] = "string"
CThostFtdcReqUserLoginField["lastLoginIp"] = "string"
CThostFtdcReqUserLoginField["lastLoginDate"] = "string"
CThostFtdcReqUserLoginField["lastLoginTime"] = "string"
CThostFtdcReqUserLoginField["gateWayCurLinkNum"] = "int"
CThostFtdcReqUserLoginField["gateWayYYBDB"] = "string"
CThostFtdcReqUserLoginField["obligate"] = "string"
CThostFtdcReqUserLoginField["msg"] = "string"
structDict['CThostFtdcReqUserLoginField'] = CThostFtdcReqUserLoginField


#用户登录应答
CThostFtdcRspUserLoginField = {}
CThostFtdcRspUserLoginField["traderID"] = "string"
CThostFtdcRspUserLoginField["memberID"] = "string"
CThostFtdcRspUserLoginField["password"] = "string"
CThostFtdcRspUserLoginField["tradeDate"] = "string"
CThostFtdcRspUserLoginField["ipAddress"] = "string"
CThostFtdcRspUserLoginField["localOrderNo"] = "string"
CThostFtdcRspUserLoginField["machineID"] = "int"
CThostFtdcRspUserLoginField["loginbatch"] = "int"
CThostFtdcRspUserLoginField["clientName"] = "string"
CThostFtdcRspUserLoginField["lastLoginIp"] = "string"
CThostFtdcRspUserLoginField["lastLoginDate"] = "string"
CThostFtdcRspUserLoginField["lastLoginTime"] = "string"
CThostFtdcRspUserLoginField["gateWayCurLinkNum"] = "int"
CThostFtdcRspUserLoginField["gateWayYYBDB"] = "string"
CThostFtdcRspUserLoginField["obligate"] = "string"
CThostFtdcRspUserLoginField["msg"] = "string"
CThostFtdcRspUserLoginField["SeatNo"] = "string"
CThostFtdcRspUserLoginField["tradeCode"] = "string"
CThostFtdcRspUserLoginField["clientID"] = "string"
structDict['CThostFtdcRspUserLoginField'] = CThostFtdcRspUserLoginField

#用户登出请求
CThostFtdcUserLogoutField = {}
CThostFtdcUserLogoutField["traderID"] = "string"
CThostFtdcUserLogoutField["memberID"] = "string"
CThostFtdcUserLogoutField["password"] = "string"
CThostFtdcUserLogoutField["tradeDate"] = "string"
CThostFtdcUserLogoutField["ipAddress"] = "string"
CThostFtdcUserLogoutField["localOrderNo"] = "string"
CThostFtdcUserLogoutField["machineID"] = "int"
CThostFtdcUserLogoutField["loginbatch"] = "int"
CThostFtdcUserLogoutField["clientName"] = "string"
CThostFtdcUserLogoutField["lastLoginIp"] = "string"
CThostFtdcUserLogoutField["lastLoginDate"] = "string"
CThostFtdcUserLogoutField["lastLoginTime"] = "string"
CThostFtdcUserLogoutField["gateWayCurLinkNum"] = "int"
CThostFtdcUserLogoutField["gateWayYYBDB"] = "string"
CThostFtdcUserLogoutField["obligate"] = "string"
CThostFtdcUserLogoutField["msg"] = "string"
structDict['CThostFtdcUserLogoutField'] = CThostFtdcUserLogoutField





#合约
CThostFtdcInstrumentField = {}
CThostFtdcInstrumentField["exchangeID"] = "string"
CThostFtdcInstrumentField["instID"] = "string"
CThostFtdcInstrumentField["lowerLimit"] = "float"
CThostFtdcInstrumentField["marketID"] = "string"
CThostFtdcInstrumentField["maxHand"] = "int"
CThostFtdcInstrumentField["minHand"] = "int"
CThostFtdcInstrumentField["name"] = "string"
CThostFtdcInstrumentField["openFlag"] = "string"
CThostFtdcInstrumentField["tick"] = "float"
CThostFtdcInstrumentField["tradeState"] = "string"
CThostFtdcInstrumentField["unit"] = "int"
CThostFtdcInstrumentField["upperLimit"] = "float"
CThostFtdcInstrumentField["varietyID"] = "string"
CThostFtdcInstrumentField["varietyType"] = "string"
CThostFtdcInstrumentField["marketType"] = "string"
structDict['CThostFtdcInstrumentField'] = CThostFtdcInstrumentField



CThostFtdcQryTradingAccountField = {}
CThostFtdcQryTradingAccountField["memberID"] = "string"
CThostFtdcQryTradingAccountField["accountType"] = "string"
CThostFtdcQryTradingAccountField["traderID"] = "string"
CThostFtdcQryTradingAccountField["clientID"] = "string"
CThostFtdcQryTradingAccountField["marketID"] = "string"
structDict['CThostFtdcQryTradingAccountField'] = CThostFtdcQryTradingAccountField


#资金账户
CThostFtdcTradingAccountField = {}
CThostFtdcTradingAccountField["availCap"] = "float"
CThostFtdcTradingAccountField["available"] = "float"
CThostFtdcTradingAccountField["posiMargin"] = "float"
CThostFtdcTradingAccountField["buyPosiMargin"] = "float"
CThostFtdcTradingAccountField["sellPosiMargin"] = "float"
CThostFtdcTradingAccountField["storageMargin"] = "float"
CThostFtdcTradingAccountField["totalFee"] = "float"
CThostFtdcTradingAccountField["totalFrozen"] = "float"
CThostFtdcTradingAccountField["orderFrozen"] = "float"
CThostFtdcTradingAccountField["spotSellFrozen"] = "float"
CThostFtdcTradingAccountField["todayIn"] = "float"
CThostFtdcTradingAccountField["todayOut"] = "float"
CThostFtdcTradingAccountField["lastFrozen"] = "float"
CThostFtdcTradingAccountField["totalFrozenFee"] = "float"
CThostFtdcTradingAccountField["pickUpMargin"] = "float"
CThostFtdcTradingAccountField["middleMargin"] = "float"
structDict['CThostFtdcTradingAccountField'] = CThostFtdcTradingAccountField


#投资者持仓
CThostFtdcInvestorPositionField = {}
CThostFtdcInvestorPositionField["clientID"] = "string"
CThostFtdcInvestorPositionField["instID"] = "string"
CThostFtdcInvestorPositionField["longPosi"] = "int"
CThostFtdcInvestorPositionField["longPosiAvgPrice"] = "float"
CThostFtdcInvestorPositionField["shortPosi"] = "int"
CThostFtdcInvestorPositionField["shortPosiAvgPrice"] = "float"
CThostFtdcInvestorPositionField["longOpenAvgPrice"] = "float"
CThostFtdcInvestorPositionField["shortOpenAvgPrice"] = "float"
CThostFtdcInvestorPositionField["longPosiFrozen"] = "int"
CThostFtdcInvestorPositionField["shortPosiFrozen"] = "int"
CThostFtdcInvestorPositionField["longPosiVol"] = "int"
CThostFtdcInvestorPositionField["shortPosiVol"] = "int"
CThostFtdcInvestorPositionField["todayLong"] = "int"
CThostFtdcInvestorPositionField["todayShort"] = "int"
CThostFtdcInvestorPositionField["todayOffsetShort"] = "int"
CThostFtdcInvestorPositionField["todayOffsetLong"] = "int"
CThostFtdcInvestorPositionField["lastLong"] = "int"
CThostFtdcInvestorPositionField["lastShort"] = "int"
structDict['CThostFtdcInvestorPositionField'] = CThostFtdcInvestorPositionField




#响应信息
CThostFtdcRspInfoField = {}
#错误代码
CThostFtdcRspInfoField["ErrorID"] = "int"
#错误信息
CThostFtdcRspInfoField["ErrorMsg"] = "string"
structDict['CThostFtdcRspInfoField'] = CThostFtdcRspInfoField

#深度行情
CThostFtdcDepthMarketDataField = {}
CThostFtdcDepthMarketDataField["InstID"] = "string"
CThostFtdcDepthMarketDataField["Name"] = "string"
CThostFtdcDepthMarketDataField["MarketName"] = "string"
CThostFtdcDepthMarketDataField["PreSettle"] = "float"
CThostFtdcDepthMarketDataField["PreClose"] = "float"
CThostFtdcDepthMarketDataField["Open"] = "float"
CThostFtdcDepthMarketDataField["High"] = "float"
CThostFtdcDepthMarketDataField["Low"] = "float"
CThostFtdcDepthMarketDataField["Last"] = "float"
CThostFtdcDepthMarketDataField["Close"] = "float"
CThostFtdcDepthMarketDataField["Bid1"] = "float"
CThostFtdcDepthMarketDataField["BidLot1"] = "int"
CThostFtdcDepthMarketDataField["Ask1"] = "float"
CThostFtdcDepthMarketDataField["AskLot1"] = "int"
CThostFtdcDepthMarketDataField["Bid2"] = "float"
CThostFtdcDepthMarketDataField["BidLot2"] = "int"
CThostFtdcDepthMarketDataField["Ask2"] = "float"
CThostFtdcDepthMarketDataField["AskLot2"] = "int"
CThostFtdcDepthMarketDataField["Bid3"] = "float"
CThostFtdcDepthMarketDataField["BidLot3"] = "int"
CThostFtdcDepthMarketDataField["Ask3"] = "float"
CThostFtdcDepthMarketDataField["AskLot3"] = "int"
CThostFtdcDepthMarketDataField["Bid4"] = "float"
CThostFtdcDepthMarketDataField["BidLot4"] = "int"
CThostFtdcDepthMarketDataField["Ask4"] = "float"
CThostFtdcDepthMarketDataField["AskLot4"] = "int"
CThostFtdcDepthMarketDataField["Bid5"] = "float"
CThostFtdcDepthMarketDataField["BidLot5"] = "int"
CThostFtdcDepthMarketDataField["Ask5"] = "float"
CThostFtdcDepthMarketDataField["AskLot5"] = "int"
CThostFtdcDepthMarketDataField["Volume"] = "int"
CThostFtdcDepthMarketDataField["OpenInt"] = "int"
CThostFtdcDepthMarketDataField["UpDown"] = "float"
CThostFtdcDepthMarketDataField["Turnover"] = "float"
CThostFtdcDepthMarketDataField["Settle"] = "float"
CThostFtdcDepthMarketDataField["Average"] = "float"
CThostFtdcDepthMarketDataField["QuoteDate"] = "string"
CThostFtdcDepthMarketDataField["QuoteTime"] = "string"
CThostFtdcDepthMarketDataField["weight"] = "float"
CThostFtdcDepthMarketDataField["highLimit"] = "float"
CThostFtdcDepthMarketDataField["lowLimit"] = "float"
CThostFtdcDepthMarketDataField["UpDownRate"] = "float"
structDict['CThostFtdcDepthMarketDataField'] = CThostFtdcDepthMarketDataField



#输入报单
CThostFtdcInputOrderField = {}
CThostFtdcInputOrderField["seatID"] = "string"
CThostFtdcInputOrderField["clientID"] = "string"
CThostFtdcInputOrderField["exchangeID"] = "string"
CThostFtdcInputOrderField["instID"] = "string"
CThostFtdcInputOrderField["buyOrSell"] = "string"
CThostFtdcInputOrderField["offsetFlag"] = "string"
CThostFtdcInputOrderField["amount"] = "int"
CThostFtdcInputOrderField["weight"] = "float"
CThostFtdcInputOrderField["middleFlag"] = "string"
CThostFtdcInputOrderField["orderFlag"] = "string"
CThostFtdcInputOrderField["priceFlag"] = "string"
CThostFtdcInputOrderField["price"] = "float"
CThostFtdcInputOrderField["trigPrice"] = "float"
CThostFtdcInputOrderField["marketID"] = "string"
CThostFtdcInputOrderField["validDate"] = "string"
CThostFtdcInputOrderField["orderNo"] = "string"
CThostFtdcInputOrderField["LocalOrderNo"] = "string"
CThostFtdcInputOrderField["matchQty"] = "int"
CThostFtdcInputOrderField["matchWeight"] = "float"
CThostFtdcInputOrderField["status"] = "string"
CThostFtdcInputOrderField["entrustTime"] = "string"
CThostFtdcInputOrderField["forceoffset_flag"] = "string"
CThostFtdcInputOrderField["cancelQty"] = "int"
CThostFtdcInputOrderField["cancelTime"] = "string"
CThostFtdcInputOrderField["volumnCheck"] = "int"
CThostFtdcInputOrderField["tradeWay"] = "string"
structDict['CThostFtdcInputOrderField'] = CThostFtdcInputOrderField


#报单
CThostFtdcOrderField = {}

CThostFtdcOrderField["orderNo"] = "string"
CThostFtdcOrderField["localOrderNo"] = "string"
CThostFtdcOrderField["marketID"] = "string"
CThostFtdcOrderField["instID"] = "string"
CThostFtdcOrderField["buyOrSell"] = "string"
CThostFtdcOrderField["offsetFlag"] = "string"
CThostFtdcOrderField["amount"] = "int"
CThostFtdcOrderField["weight"] = "float"
CThostFtdcOrderField["price"] = "float"
CThostFtdcOrderField["matchQty"] = "int"
CThostFtdcOrderField["matchWeight"] = "float"
CThostFtdcOrderField["status"] = "string"
CThostFtdcOrderField["entrustTime"] = "string"
CThostFtdcOrderField["forceoffset_flag"] = "string"
CThostFtdcOrderField["cancelQty"] = "int"
CThostFtdcOrderField["cancelTime"] = "string"
CThostFtdcOrderField["tradeWay"] = "string"
structDict['CThostFtdcOrderField'] = CThostFtdcOrderField



#输入报单操作(cancel order)
CThostFtdcInputOrderActionField = {}
CThostFtdcInputOrderActionField["localOrderNo"] = "string"
CThostFtdcInputOrderActionField["orderFlag"] = "string"
CThostFtdcInputOrderActionField["marketID"] = "string"
CThostFtdcInputOrderActionField["traderID"] = "string"
CThostFtdcInputOrderActionField["tradeWay"] = "string"
structDict['CThostFtdcInputOrderActionField'] = CThostFtdcInputOrderActionField


#报单操作
CThostFtdcOrderActionField = {}
CThostFtdcOrderActionField["localOrderNo"] = "string"
CThostFtdcOrderActionField["orderFlag"] = "string"
CThostFtdcOrderActionField["marketID"] = "string"
CThostFtdcOrderActionField["traderID"] = "string"
CThostFtdcOrderActionField["tradeWay"] = "string"
structDict['CThostFtdcOrderActionField'] = CThostFtdcOrderActionField

#成交
CThostFtdcTradeField = {}

CThostFtdcTradeField["orderNo"] = "string"
CThostFtdcTradeField["matchNo"] = "string"
CThostFtdcTradeField["instID"] = "string"
CThostFtdcTradeField["buyOrSell"] = "string"
CThostFtdcTradeField["offSetFlag"] = "string"
CThostFtdcTradeField["price"] = "float"
CThostFtdcTradeField["volume"] = "int"
CThostFtdcTradeField["amount"] = "float"
CThostFtdcTradeField["weight"] = "float"
CThostFtdcTradeField["order_flag"] = "string"
CThostFtdcTradeField["matchDate"] = "string"
CThostFtdcTradeField["matchTime"] = "string"
CThostFtdcTradeField["localOrderNo"] = "string"
CThostFtdcTradeField["marketID"] = "string"
CThostFtdcTradeField["trade_fee"] = "float"
CThostFtdcTradeField["forceoffset_flag"] = "string"
CThostFtdcTradeField["forcebatchnum"] = "int"
CThostFtdcTradeField["tradeWay"] = "string"
structDict['CThostFtdcTradeField'] = CThostFtdcTradeField


#查询合约
CThostFtdcQryInstrumentField = {}
CThostFtdcQryInstrumentField["ContractID"] = "string"
CThostFtdcQryInstrumentField["ProductID"] = "string"
structDict['CThostFtdcQryInstrumentField'] = CThostFtdcQryInstrumentField



#查询成交
CThostFtdcQryTradeField = {}
CThostFtdcQryTradeField["instID"] = "string"
CThostFtdcQryTradeField["marketID"] = "string"
CThostFtdcQryTradeField["orderNo"] = "string"
CThostFtdcQryTradeField["clientID"] = "string"
CThostFtdcQryTradeField["memberID"] = "string"
CThostFtdcQryTradeField["matchNo"] = "string"
CThostFtdcQryTradeField["exchangeID"] = "string"
CThostFtdcQryTradeField["localOrderNo"] = "string"
CThostFtdcQryTradeField["traderID"] = "string"
structDict['CThostFtdcQryTradeField'] = CThostFtdcQryTradeField



#查询报单
CThostFtdcQryOrderField = {}
CThostFtdcQryOrderField["instID"] = "string"
CThostFtdcQryOrderField["marketID"] = "string"
CThostFtdcQryOrderField["orderNo"] = "string"
CThostFtdcQryOrderField["clientID"] = "string"
CThostFtdcQryOrderField["memberID"] = "string"
CThostFtdcQryOrderField["offsetFlag"] = "string"
CThostFtdcQryOrderField["traderID"] = "string"
CThostFtdcQryOrderField["status"] = "string"
CThostFtdcQryOrderField["exchangeID"] = "string"
CThostFtdcQryOrderField["localOrderNo"] = "string"
structDict['CThostFtdcQryOrderField'] = CThostFtdcQryOrderField





#查询投资者持仓
CThostFtdcQryInvestorPositionField = {}
CThostFtdcQryInvestorPositionField["clientID"] = "string"
CThostFtdcQryInvestorPositionField["memberID"] = "string"
CThostFtdcQryInvestorPositionField["marketID"] = "string"
CThostFtdcQryInvestorPositionField["instID"] = "string"
CThostFtdcQryInvestorPositionField["traderID"] = "string"
structDict['CThostFtdcQryInvestorPositionField'] = CThostFtdcQryInvestorPositionField



#查询库存
CThostFtdcQryStorageField = {}
CThostFtdcQryStorageField["clientID"] = "string"
CThostFtdcQryStorageField["memberID"] = "string"
CThostFtdcQryStorageField["traderID"] = "string"
structDict['CThostFtdcQryStorageField'] = CThostFtdcQryStorageField



CThostFtdcStorageField = {}
CThostFtdcStorageField["varietyID"] = "string"
CThostFtdcStorageField["varietyName"] = "string"
CThostFtdcStorageField["totalStorage"] = "float"
CThostFtdcStorageField["availableStorage"] = "float"
CThostFtdcStorageField["frozenStorage"] = "float"
CThostFtdcStorageField["pendStorage"] = "float"
CThostFtdcStorageField["todayBuy"] = "float"
CThostFtdcStorageField["todaySell"] = "float"
CThostFtdcStorageField["todayDeposit"] = "float"
CThostFtdcStorageField["todayRealDeposit"] = "float"
CThostFtdcStorageField["todayBorrow"] = "float"
CThostFtdcStorageField["todayLend"] = "float"
CThostFtdcStorageField["impawnStorage"] = "float"
CThostFtdcStorageField["lawFrozen"] = "float"
CThostFtdcStorageField["bankFrozen"] = "float"
CThostFtdcStorageField["customType"] = "string"
CThostFtdcStorageField["storageCost"] = "float"
CThostFtdcStorageField["impawnFrozen"] = "float"
structDict['CThostFtdcStorageField'] = CThostFtdcStorageField





CThostFtdcMarketStatusField = {}
CThostFtdcMarketStatusField["MktStatus"] = "string"
CThostFtdcMarketStatusField["marketID"] = "string"
CThostFtdcMarketStatusField["ExchCode"] = "string"
CThostFtdcMarketStatusField["MktChgTime"] = "string"
structDict['CThostFtdcMarketStatusField'] = CThostFtdcMarketStatusField

#指定的合约
CThostFtdcSpecificInstrumentField = {}
#合约代码
CThostFtdcSpecificInstrumentField["InstrumentID"] = "string"
structDict['CThostFtdcSpecificInstrumentField'] = CThostFtdcSpecificInstrumentField



