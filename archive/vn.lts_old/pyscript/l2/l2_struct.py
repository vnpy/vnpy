# encoding: UTF-8

structDict = {}

#//////////////////////////////////////////////////////////////////////
#@company shanghai liber information Technology Co.,Ltd
#@file SecurityFtdcL2MDUserApiStruct.h
#@brief 定义业务数据结构
#//////////////////////////////////////////////////////////////////////












#响应信息
CSecurityFtdcRspInfoField = {}
#错误代码
CSecurityFtdcRspInfoField["ErrorID"] = "int"
#错误信息
CSecurityFtdcRspInfoField["ErrorMsg"] = "string"
structDict['CSecurityFtdcRspInfoField'] = CSecurityFtdcRspInfoField


#用户登录信息
CSecurityFtdcUserLoginField = {}
#交易日
CSecurityFtdcUserLoginField["TradingDay"] = "string"
#经纪公司代码
CSecurityFtdcUserLoginField["BrokerID"] = "string"
#用户代码
CSecurityFtdcUserLoginField["UserID"] = "string"
#密码
CSecurityFtdcUserLoginField["Password"] = "string"
#行情数据等级
CSecurityFtdcUserLoginField["DataLevel"] = "string"
structDict['CSecurityFtdcUserLoginField'] = CSecurityFtdcUserLoginField


#用户登出信息
CSecurityFtdcUserLogoutField = {}
#经纪公司代码
CSecurityFtdcUserLogoutField["BrokerID"] = "string"
#用户代码
CSecurityFtdcUserLogoutField["UserID"] = "string"
structDict['CSecurityFtdcUserLogoutField'] = CSecurityFtdcUserLogoutField


#指定的合约
CSecurityFtdcSpecificInstrumentField = {}
#合约代码
CSecurityFtdcSpecificInstrumentField["InstrumentID"] = "string"
#交易所代码
CSecurityFtdcSpecificInstrumentField["ExchangeID"] = "string"
structDict['CSecurityFtdcSpecificInstrumentField'] = CSecurityFtdcSpecificInstrumentField


#Level2行情
CSecurityFtdcL2MarketDataField = {}
#交易日
CSecurityFtdcL2MarketDataField["TradingDay"] = "string"
#时间戳
CSecurityFtdcL2MarketDataField["TimeStamp"] = "string"
#交易所代码
CSecurityFtdcL2MarketDataField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcL2MarketDataField["InstrumentID"] = "string"
#昨收盘价
CSecurityFtdcL2MarketDataField["PreClosePrice"] = "float"
#今开盘价
CSecurityFtdcL2MarketDataField["OpenPrice"] = "float"
#收盘价
CSecurityFtdcL2MarketDataField["ClosePrice"] = "float"
#净值估值
CSecurityFtdcL2MarketDataField["IOPV"] = "float"
#到期收益率
CSecurityFtdcL2MarketDataField["YieldToMaturity"] = "float"
#最高价
CSecurityFtdcL2MarketDataField["HighPrice"] = "float"
#最低价
CSecurityFtdcL2MarketDataField["LowPrice"] = "float"
#最新价
CSecurityFtdcL2MarketDataField["LastPrice"] = "float"
#成交笔数
CSecurityFtdcL2MarketDataField["TradeCount"] = "int"
#成交总量
CSecurityFtdcL2MarketDataField["TotalTradeVolume"] = "float"
#成交总金额
CSecurityFtdcL2MarketDataField["TotalTradeValue"] = "float"
#委托买入总量
CSecurityFtdcL2MarketDataField["TotalBidVolume"] = "float"
#加权平均委买价
CSecurityFtdcL2MarketDataField["WeightedAvgBidPrice"] = "float"
#债券加权平均委买价
CSecurityFtdcL2MarketDataField["AltWeightedAvgBidPrice"] = "float"
#委托卖出总量
CSecurityFtdcL2MarketDataField["TotalOfferVolume"] = "float"
#加权平均委卖价
CSecurityFtdcL2MarketDataField["WeightedAvgOfferPrice"] = "float"
#债券加权平均委卖价格
CSecurityFtdcL2MarketDataField["AltWeightedAvgOfferPrice"] = "float"
#买价深度
CSecurityFtdcL2MarketDataField["BidPriceLevel"] = "int"
#卖价深度
CSecurityFtdcL2MarketDataField["OfferPriceLevel"] = "int"
#申买价一
CSecurityFtdcL2MarketDataField["BidPrice1"] = "float"
#申买量一
CSecurityFtdcL2MarketDataField["BidVolume1"] = "int"
#实际买总委托笔数一
CSecurityFtdcL2MarketDataField["BidCount1"] = "int"
#申买价二
CSecurityFtdcL2MarketDataField["BidPrice2"] = "float"
#申买量二
CSecurityFtdcL2MarketDataField["BidVolume2"] = "int"
#实际买总委托笔数二
CSecurityFtdcL2MarketDataField["BidCount2"] = "int"
#申买价三
CSecurityFtdcL2MarketDataField["BidPrice3"] = "float"
#申买量三
CSecurityFtdcL2MarketDataField["BidVolume3"] = "int"
#实际买总委托笔数三
CSecurityFtdcL2MarketDataField["BidCount3"] = "int"
#申买价四
CSecurityFtdcL2MarketDataField["BidPrice4"] = "float"
#申买量四
CSecurityFtdcL2MarketDataField["BidVolume4"] = "int"
#实际买总委托笔数四
CSecurityFtdcL2MarketDataField["BidCount4"] = "int"
#申买价五
CSecurityFtdcL2MarketDataField["BidPrice5"] = "float"
#申买量五
CSecurityFtdcL2MarketDataField["BidVolume5"] = "int"
#实际买总委托笔数五
CSecurityFtdcL2MarketDataField["BidCount5"] = "int"
#申买价六
CSecurityFtdcL2MarketDataField["BidPrice6"] = "float"
#申买量六
CSecurityFtdcL2MarketDataField["BidVolume6"] = "int"
#实际买总委托笔数六
CSecurityFtdcL2MarketDataField["BidCount6"] = "int"
#申买价七
CSecurityFtdcL2MarketDataField["BidPrice7"] = "float"
#申买量七
CSecurityFtdcL2MarketDataField["BidVolume7"] = "int"
#实际买总委托笔数七
CSecurityFtdcL2MarketDataField["BidCount7"] = "int"
#申买价八
CSecurityFtdcL2MarketDataField["BidPrice8"] = "float"
#申买量八
CSecurityFtdcL2MarketDataField["BidVolume8"] = "int"
#实际买总委托笔数八
CSecurityFtdcL2MarketDataField["BidCount8"] = "int"
#申买价九
CSecurityFtdcL2MarketDataField["BidPrice9"] = "float"
#申买量九
CSecurityFtdcL2MarketDataField["BidVolume9"] = "int"
#实际买总委托笔数九
CSecurityFtdcL2MarketDataField["BidCount9"] = "int"
#申买价十
CSecurityFtdcL2MarketDataField["BidPriceA"] = "float"
#申买量十
CSecurityFtdcL2MarketDataField["BidVolumeA"] = "int"
#实际买总委托笔数十
CSecurityFtdcL2MarketDataField["BidCountA"] = "int"
#申卖价一
CSecurityFtdcL2MarketDataField["OfferPrice1"] = "float"
#申卖量一
CSecurityFtdcL2MarketDataField["OfferVolume1"] = "int"
#实际卖总委托笔数一
CSecurityFtdcL2MarketDataField["OfferCount1"] = "int"
#申卖价二
CSecurityFtdcL2MarketDataField["OfferPrice2"] = "float"
#申卖量二
CSecurityFtdcL2MarketDataField["OfferVolume2"] = "int"
#实际卖总委托笔数二
CSecurityFtdcL2MarketDataField["OfferCount2"] = "int"
#申卖价三
CSecurityFtdcL2MarketDataField["OfferPrice3"] = "float"
#申卖量三
CSecurityFtdcL2MarketDataField["OfferVolume3"] = "int"
#实际卖总委托笔数三
CSecurityFtdcL2MarketDataField["OfferCount3"] = "int"
#申卖价四
CSecurityFtdcL2MarketDataField["OfferPrice4"] = "float"
#申卖量四
CSecurityFtdcL2MarketDataField["OfferVolume4"] = "int"
#实际卖总委托笔数四
CSecurityFtdcL2MarketDataField["OfferCount4"] = "int"
#申卖价五
CSecurityFtdcL2MarketDataField["OfferPrice5"] = "float"
#申卖量五
CSecurityFtdcL2MarketDataField["OfferVolume5"] = "int"
#实际卖总委托笔数五
CSecurityFtdcL2MarketDataField["OfferCount5"] = "int"
#申卖价六
CSecurityFtdcL2MarketDataField["OfferPrice6"] = "float"
#申卖量六
CSecurityFtdcL2MarketDataField["OfferVolume6"] = "int"
#实际卖总委托笔数六
CSecurityFtdcL2MarketDataField["OfferCount6"] = "int"
#申卖价七
CSecurityFtdcL2MarketDataField["OfferPrice7"] = "float"
#申卖量七
CSecurityFtdcL2MarketDataField["OfferVolume7"] = "int"
#实际卖总委托笔数七
CSecurityFtdcL2MarketDataField["OfferCount7"] = "int"
#申卖价八
CSecurityFtdcL2MarketDataField["OfferPrice8"] = "float"
#申卖量八
CSecurityFtdcL2MarketDataField["OfferVolume8"] = "int"
#实际卖总委托笔数八
CSecurityFtdcL2MarketDataField["OfferCount8"] = "int"
#申卖价九
CSecurityFtdcL2MarketDataField["OfferPrice9"] = "float"
#申卖量九
CSecurityFtdcL2MarketDataField["OfferVolume9"] = "int"
#实际卖总委托笔数九
CSecurityFtdcL2MarketDataField["OfferCount9"] = "int"
#申卖价十
CSecurityFtdcL2MarketDataField["OfferPriceA"] = "float"
#申卖量十
CSecurityFtdcL2MarketDataField["OfferVolumeA"] = "int"
#实际卖总委托笔数十
CSecurityFtdcL2MarketDataField["OfferCountA"] = "int"
structDict['CSecurityFtdcL2MarketDataField'] = CSecurityFtdcL2MarketDataField


#Level2行情更新时间属性
CSecurityFtdcL2UpdateTimeField = {}
#交易日
CSecurityFtdcL2UpdateTimeField["TradingDay"] = "string"
#时间戳
CSecurityFtdcL2UpdateTimeField["TimeStamp"] = "string"
#交易所代码
CSecurityFtdcL2UpdateTimeField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcL2UpdateTimeField["InstrumentID"] = "string"
structDict['CSecurityFtdcL2UpdateTimeField'] = CSecurityFtdcL2UpdateTimeField


#Level2行情静态属性
CSecurityFtdcL2StaticField = {}
#昨收盘价
CSecurityFtdcL2StaticField["PreClosePrice"] = "float"
#今开盘价
CSecurityFtdcL2StaticField["OpenPrice"] = "float"
#收盘价
CSecurityFtdcL2StaticField["ClosePrice"] = "float"
#净值估值
CSecurityFtdcL2StaticField["IOPV"] = "float"
#到期收益率
CSecurityFtdcL2StaticField["YieldToMaturity"] = "float"
structDict['CSecurityFtdcL2StaticField'] = CSecurityFtdcL2StaticField


#Level2行情价格区间属性
CSecurityFtdcL2PriceIntervalField = {}
#最高价
CSecurityFtdcL2PriceIntervalField["HighPrice"] = "float"
#最低价
CSecurityFtdcL2PriceIntervalField["LowPrice"] = "float"
structDict['CSecurityFtdcL2PriceIntervalField'] = CSecurityFtdcL2PriceIntervalField


#Level2行情基本信息
CSecurityFtdcL2BaseField = {}
#最新价
CSecurityFtdcL2BaseField["LastPrice"] = "float"
structDict['CSecurityFtdcL2BaseField'] = CSecurityFtdcL2BaseField


#Level2成交信息
CSecurityFtdcL2TradedField = {}
#成交笔数
CSecurityFtdcL2TradedField["TradeCount"] = "int"
#成交总量
CSecurityFtdcL2TradedField["TotalTradeVolume"] = "float"
#成交总金额
CSecurityFtdcL2TradedField["TotalTradeValue"] = "float"
structDict['CSecurityFtdcL2TradedField'] = CSecurityFtdcL2TradedField


#Level2行情数据属性
CSecurityFtdcL2DataLevelField = {}
#价格
CSecurityFtdcL2DataLevelField["Price"] = "float"
#数量
CSecurityFtdcL2DataLevelField["Volume"] = "int"
#实际总委托笔数
CSecurityFtdcL2DataLevelField["Count"] = "int"
structDict['CSecurityFtdcL2DataLevelField'] = CSecurityFtdcL2DataLevelField


#Level2委买信息
CSecurityFtdcL2BidOrderField = {}
#委托买入总量
CSecurityFtdcL2BidOrderField["TotalBidVolume"] = "float"
#加权平均委买价
CSecurityFtdcL2BidOrderField["WeightedAvgBidPrice"] = "float"
#债券加权平均委买价
CSecurityFtdcL2BidOrderField["AltWeightedAvgBidPrice"] = "float"
structDict['CSecurityFtdcL2BidOrderField'] = CSecurityFtdcL2BidOrderField


#Level2委卖信息
CSecurityFtdcL2OfferOrderField = {}
#委托卖出总量
CSecurityFtdcL2OfferOrderField["TotalOfferVolume"] = "float"
#加权平均委卖价
CSecurityFtdcL2OfferOrderField["WeightedAvgOfferPrice"] = "float"
#债券加权平均委卖价格
CSecurityFtdcL2OfferOrderField["AltWeightedAvgOfferPrice"] = "float"
structDict['CSecurityFtdcL2OfferOrderField'] = CSecurityFtdcL2OfferOrderField


#Level2价格深度属性
CSecurityFtdcL2PriceLevelField = {}
#买价深度
CSecurityFtdcL2PriceLevelField["BidPriceLevel"] = "int"
#卖价深度
CSecurityFtdcL2PriceLevelField["OfferPriceLevel"] = "int"
structDict['CSecurityFtdcL2PriceLevelField'] = CSecurityFtdcL2PriceLevelField


#Level2行情申买一属性
CSecurityFtdcL2Bid1Field = {}
#申买价一
CSecurityFtdcL2Bid1Field["BidPrice1"] = "float"
#申买量一
CSecurityFtdcL2Bid1Field["BidVolume1"] = "int"
#实际买总委托笔数一
CSecurityFtdcL2Bid1Field["BidCount1"] = "int"
structDict['CSecurityFtdcL2Bid1Field'] = CSecurityFtdcL2Bid1Field


#Level2行情申卖一属性
CSecurityFtdcL2Offer1Field = {}
#申卖价一
CSecurityFtdcL2Offer1Field["OfferPrice1"] = "float"
#申卖量一
CSecurityFtdcL2Offer1Field["OfferVolume1"] = "int"
#实际卖总委托笔数一
CSecurityFtdcL2Offer1Field["OfferCount1"] = "int"
structDict['CSecurityFtdcL2Offer1Field'] = CSecurityFtdcL2Offer1Field


#Level2行情申买二属性
CSecurityFtdcL2Bid2Field = {}
#申买价二
CSecurityFtdcL2Bid2Field["BidPrice2"] = "float"
#申买量二
CSecurityFtdcL2Bid2Field["BidVolume2"] = "int"
#实际买总委托笔数二
CSecurityFtdcL2Bid2Field["BidCount2"] = "int"
structDict['CSecurityFtdcL2Bid2Field'] = CSecurityFtdcL2Bid2Field


#Level2行情申卖二属性
CSecurityFtdcL2Offer2Field = {}
#申卖价二
CSecurityFtdcL2Offer2Field["OfferPrice2"] = "float"
#申卖量二
CSecurityFtdcL2Offer2Field["OfferVolume2"] = "int"
#实际卖总委托笔数二
CSecurityFtdcL2Offer2Field["OfferCount2"] = "int"
structDict['CSecurityFtdcL2Offer2Field'] = CSecurityFtdcL2Offer2Field


#Level2行情申买三属性
CSecurityFtdcL2Bid3Field = {}
#申买价三
CSecurityFtdcL2Bid3Field["BidPrice3"] = "float"
#申买量三
CSecurityFtdcL2Bid3Field["BidVolume3"] = "int"
#实际买总委托笔数三
CSecurityFtdcL2Bid3Field["BidCount3"] = "int"
structDict['CSecurityFtdcL2Bid3Field'] = CSecurityFtdcL2Bid3Field


#Level2行情申卖三属性
CSecurityFtdcL2Offer3Field = {}
#申卖价三
CSecurityFtdcL2Offer3Field["OfferPrice3"] = "float"
#申卖量三
CSecurityFtdcL2Offer3Field["OfferVolume3"] = "int"
#实际卖总委托笔数三
CSecurityFtdcL2Offer3Field["OfferCount3"] = "int"
structDict['CSecurityFtdcL2Offer3Field'] = CSecurityFtdcL2Offer3Field


#Level2行情申买四属性
CSecurityFtdcL2Bid4Field = {}
#申买价四
CSecurityFtdcL2Bid4Field["BidPrice4"] = "float"
#申买量四
CSecurityFtdcL2Bid4Field["BidVolume4"] = "int"
#实际买总委托笔数四
CSecurityFtdcL2Bid4Field["BidCount4"] = "int"
structDict['CSecurityFtdcL2Bid4Field'] = CSecurityFtdcL2Bid4Field


#Level2行情申卖四属性
CSecurityFtdcL2Offer4Field = {}
#申卖价四
CSecurityFtdcL2Offer4Field["OfferPrice4"] = "float"
#申卖量四
CSecurityFtdcL2Offer4Field["OfferVolume4"] = "int"
#实际卖总委托笔数四
CSecurityFtdcL2Offer4Field["OfferCount4"] = "int"
structDict['CSecurityFtdcL2Offer4Field'] = CSecurityFtdcL2Offer4Field


#Level2行情申买五属性
CSecurityFtdcL2Bid5Field = {}
#申买价五
CSecurityFtdcL2Bid5Field["BidPrice5"] = "float"
#申买量五
CSecurityFtdcL2Bid5Field["BidVolume5"] = "int"
#实际买总委托笔数五
CSecurityFtdcL2Bid5Field["BidCount5"] = "int"
structDict['CSecurityFtdcL2Bid5Field'] = CSecurityFtdcL2Bid5Field


#Level2行情申卖五属性
CSecurityFtdcL2Offer5Field = {}
#申卖价五
CSecurityFtdcL2Offer5Field["OfferPrice5"] = "float"
#申卖量五
CSecurityFtdcL2Offer5Field["OfferVolume5"] = "int"
#实际卖总委托笔数五
CSecurityFtdcL2Offer5Field["OfferCount5"] = "int"
structDict['CSecurityFtdcL2Offer5Field'] = CSecurityFtdcL2Offer5Field


#Level2行情申买六属性
CSecurityFtdcL2Bid6Field = {}
#申买价六
CSecurityFtdcL2Bid6Field["BidPrice6"] = "float"
#申买量六
CSecurityFtdcL2Bid6Field["BidVolume6"] = "int"
#实际买总委托笔数六
CSecurityFtdcL2Bid6Field["BidCount6"] = "int"
structDict['CSecurityFtdcL2Bid6Field'] = CSecurityFtdcL2Bid6Field


#Level2行情申卖六属性
CSecurityFtdcL2Offer6Field = {}
#申卖价六
CSecurityFtdcL2Offer6Field["OfferPrice6"] = "float"
#申卖量六
CSecurityFtdcL2Offer6Field["OfferVolume6"] = "int"
#实际卖总委托笔数六
CSecurityFtdcL2Offer6Field["OfferCount6"] = "int"
structDict['CSecurityFtdcL2Offer6Field'] = CSecurityFtdcL2Offer6Field


#Level2行情申买七属性
CSecurityFtdcL2Bid7Field = {}
#申买价七
CSecurityFtdcL2Bid7Field["BidPrice7"] = "float"
#申买量七
CSecurityFtdcL2Bid7Field["BidVolume7"] = "int"
#实际买总委托笔数七
CSecurityFtdcL2Bid7Field["BidCount7"] = "int"
structDict['CSecurityFtdcL2Bid7Field'] = CSecurityFtdcL2Bid7Field


#Level2行情申卖七属性
CSecurityFtdcL2Offer7Field = {}
#申卖价七
CSecurityFtdcL2Offer7Field["OfferPrice7"] = "float"
#申卖量七
CSecurityFtdcL2Offer7Field["OfferVolume7"] = "int"
#实际卖总委托笔数七
CSecurityFtdcL2Offer7Field["OfferCount7"] = "int"
structDict['CSecurityFtdcL2Offer7Field'] = CSecurityFtdcL2Offer7Field


#Level2行情申买八属性
CSecurityFtdcL2Bid8Field = {}
#申买价八
CSecurityFtdcL2Bid8Field["BidPrice8"] = "float"
#申买量八
CSecurityFtdcL2Bid8Field["BidVolume8"] = "int"
#实际买总委托笔数八
CSecurityFtdcL2Bid8Field["BidCount8"] = "int"
structDict['CSecurityFtdcL2Bid8Field'] = CSecurityFtdcL2Bid8Field


#Level2行情申卖八属性
CSecurityFtdcL2Offer8Field = {}
#申卖价八
CSecurityFtdcL2Offer8Field["OfferPrice8"] = "float"
#申卖量八
CSecurityFtdcL2Offer8Field["OfferVolume8"] = "int"
#实际卖总委托笔数八
CSecurityFtdcL2Offer8Field["OfferCount8"] = "int"
structDict['CSecurityFtdcL2Offer8Field'] = CSecurityFtdcL2Offer8Field


#Level2行情申买九属性
CSecurityFtdcL2Bid9Field = {}
#申买价九
CSecurityFtdcL2Bid9Field["BidPrice9"] = "float"
#申买量九
CSecurityFtdcL2Bid9Field["BidVolume9"] = "int"
#实际买总委托笔数九
CSecurityFtdcL2Bid9Field["BidCount9"] = "int"
structDict['CSecurityFtdcL2Bid9Field'] = CSecurityFtdcL2Bid9Field


#Level2行情申卖九属性
CSecurityFtdcL2Offer9Field = {}
#申卖价九
CSecurityFtdcL2Offer9Field["OfferPrice9"] = "float"
#申卖量九
CSecurityFtdcL2Offer9Field["OfferVolume9"] = "int"
#实际卖总委托笔数九
CSecurityFtdcL2Offer9Field["OfferCount9"] = "int"
structDict['CSecurityFtdcL2Offer9Field'] = CSecurityFtdcL2Offer9Field


#Level2行情申买十属性
CSecurityFtdcL2BidAField = {}
#申买价十
CSecurityFtdcL2BidAField["BidPriceA"] = "float"
#申买量十
CSecurityFtdcL2BidAField["BidVolumeA"] = "int"
#实际买总委托笔数十
CSecurityFtdcL2BidAField["BidCountA"] = "int"
structDict['CSecurityFtdcL2BidAField'] = CSecurityFtdcL2BidAField


#Level2行情申卖十属性
CSecurityFtdcL2OfferAField = {}
#申卖价十
CSecurityFtdcL2OfferAField["OfferPriceA"] = "float"
#申卖量十
CSecurityFtdcL2OfferAField["OfferVolumeA"] = "int"
#实际卖总委托笔数十
CSecurityFtdcL2OfferAField["OfferCountA"] = "int"
structDict['CSecurityFtdcL2OfferAField'] = CSecurityFtdcL2OfferAField


#Level2行情申买属性
CSecurityFtdcL2BidField = {}
#申买价一
CSecurityFtdcL2BidField["BidPrice1"] = "float"
#申买量一
CSecurityFtdcL2BidField["BidVolume1"] = "int"
#实际买总委托笔数一
CSecurityFtdcL2BidField["BidCount1"] = "int"
#申买价二
CSecurityFtdcL2BidField["BidPrice2"] = "float"
#申买量二
CSecurityFtdcL2BidField["BidVolume2"] = "int"
#实际买总委托笔数二
CSecurityFtdcL2BidField["BidCount2"] = "int"
#申买价三
CSecurityFtdcL2BidField["BidPrice3"] = "float"
#申买量三
CSecurityFtdcL2BidField["BidVolume3"] = "int"
#实际买总委托笔数三
CSecurityFtdcL2BidField["BidCount3"] = "int"
#申买价四
CSecurityFtdcL2BidField["BidPrice4"] = "float"
#申买量四
CSecurityFtdcL2BidField["BidVolume4"] = "int"
#实际买总委托笔数四
CSecurityFtdcL2BidField["BidCount4"] = "int"
#申买价五
CSecurityFtdcL2BidField["BidPrice5"] = "float"
#申买量五
CSecurityFtdcL2BidField["BidVolume5"] = "int"
#实际买总委托笔数五
CSecurityFtdcL2BidField["BidCount5"] = "int"
#申买价六
CSecurityFtdcL2BidField["BidPrice6"] = "float"
#申买量六
CSecurityFtdcL2BidField["BidVolume6"] = "int"
#实际买总委托笔数六
CSecurityFtdcL2BidField["BidCount6"] = "int"
#申买价七
CSecurityFtdcL2BidField["BidPrice7"] = "float"
#申买量七
CSecurityFtdcL2BidField["BidVolume7"] = "int"
#实际买总委托笔数七
CSecurityFtdcL2BidField["BidCount7"] = "int"
#申买价八
CSecurityFtdcL2BidField["BidPrice8"] = "float"
#申买量八
CSecurityFtdcL2BidField["BidVolume8"] = "int"
#实际买总委托笔数八
CSecurityFtdcL2BidField["BidCount8"] = "int"
#申买价九
CSecurityFtdcL2BidField["BidPrice9"] = "float"
#申买量九
CSecurityFtdcL2BidField["BidVolume9"] = "int"
#实际买总委托笔数九
CSecurityFtdcL2BidField["BidCount9"] = "int"
#申买价十
CSecurityFtdcL2BidField["BidPriceA"] = "float"
#申买量十
CSecurityFtdcL2BidField["BidVolumeA"] = "int"
#实际买总委托笔数十
CSecurityFtdcL2BidField["BidCountA"] = "int"
structDict['CSecurityFtdcL2BidField'] = CSecurityFtdcL2BidField


#Level2行情申卖属性
CSecurityFtdcL2OfferField = {}
#申卖价一
CSecurityFtdcL2OfferField["OfferPrice1"] = "float"
#申卖量一
CSecurityFtdcL2OfferField["OfferVolume1"] = "int"
#实际卖总委托笔数一
CSecurityFtdcL2OfferField["OfferCount1"] = "int"
#申卖价二
CSecurityFtdcL2OfferField["OfferPrice2"] = "float"
#申卖量二
CSecurityFtdcL2OfferField["OfferVolume2"] = "int"
#实际卖总委托笔数二
CSecurityFtdcL2OfferField["OfferCount2"] = "int"
#申卖价三
CSecurityFtdcL2OfferField["OfferPrice3"] = "float"
#申卖量三
CSecurityFtdcL2OfferField["OfferVolume3"] = "int"
#实际卖总委托笔数三
CSecurityFtdcL2OfferField["OfferCount3"] = "int"
#申卖价四
CSecurityFtdcL2OfferField["OfferPrice4"] = "float"
#申卖量四
CSecurityFtdcL2OfferField["OfferVolume4"] = "int"
#实际卖总委托笔数四
CSecurityFtdcL2OfferField["OfferCount4"] = "int"
#申卖价五
CSecurityFtdcL2OfferField["OfferPrice5"] = "float"
#申卖量五
CSecurityFtdcL2OfferField["OfferVolume5"] = "int"
#实际卖总委托笔数五
CSecurityFtdcL2OfferField["OfferCount5"] = "int"
#申卖价六
CSecurityFtdcL2OfferField["OfferPrice6"] = "float"
#申卖量六
CSecurityFtdcL2OfferField["OfferVolume6"] = "int"
#实际卖总委托笔数六
CSecurityFtdcL2OfferField["OfferCount6"] = "int"
#申卖价七
CSecurityFtdcL2OfferField["OfferPrice7"] = "float"
#申卖量七
CSecurityFtdcL2OfferField["OfferVolume7"] = "int"
#实际卖总委托笔数七
CSecurityFtdcL2OfferField["OfferCount7"] = "int"
#申卖价八
CSecurityFtdcL2OfferField["OfferPrice8"] = "float"
#申卖量八
CSecurityFtdcL2OfferField["OfferVolume8"] = "int"
#实际卖总委托笔数八
CSecurityFtdcL2OfferField["OfferCount8"] = "int"
#申卖价九
CSecurityFtdcL2OfferField["OfferPrice9"] = "float"
#申卖量九
CSecurityFtdcL2OfferField["OfferVolume9"] = "int"
#实际卖总委托笔数九
CSecurityFtdcL2OfferField["OfferCount9"] = "int"
#申卖价十
CSecurityFtdcL2OfferField["OfferPriceA"] = "float"
#申卖量十
CSecurityFtdcL2OfferField["OfferVolumeA"] = "int"
#实际卖总委托笔数十
CSecurityFtdcL2OfferField["OfferCountA"] = "int"
structDict['CSecurityFtdcL2OfferField'] = CSecurityFtdcL2OfferField


#Level2指数行情
CSecurityFtdcL2IndexField = {}
#交易日
CSecurityFtdcL2IndexField["TradingDay"] = "string"
#行情时间（秒）
CSecurityFtdcL2IndexField["TimeStamp"] = "string"
#交易所代码
CSecurityFtdcL2IndexField["ExchangeID"] = "string"
#指数代码
CSecurityFtdcL2IndexField["InstrumentID"] = "string"
#前收盘指数
CSecurityFtdcL2IndexField["PreCloseIndex"] = "float"
#今开盘指数
CSecurityFtdcL2IndexField["OpenIndex"] = "float"
#今日收盘指数
CSecurityFtdcL2IndexField["CloseIndex"] = "float"
#最高指数
CSecurityFtdcL2IndexField["HighIndex"] = "float"
#最低指数
CSecurityFtdcL2IndexField["LowIndex"] = "float"
#最新指数
CSecurityFtdcL2IndexField["LastIndex"] = "float"
#参与计算相应指数的成交金额（元）
CSecurityFtdcL2IndexField["TurnOver"] = "float"
#参与计算相应指数的交易数量（手）
CSecurityFtdcL2IndexField["TotalVolume"] = "float"
structDict['CSecurityFtdcL2IndexField'] = CSecurityFtdcL2IndexField


#Level2行情用户信息
CSecurityFtdcL2UserInfoField = {}
#经纪公司代码
CSecurityFtdcL2UserInfoField["BrokerID"] = "string"
#用户代码
CSecurityFtdcL2UserInfoField["UserID"] = "string"
#用户名称
CSecurityFtdcL2UserInfoField["UserName"] = "string"
#密码
CSecurityFtdcL2UserInfoField["Password"] = "string"
#行情数据等级
CSecurityFtdcL2UserInfoField["DataLevel"] = "string"
structDict['CSecurityFtdcL2UserInfoField'] = CSecurityFtdcL2UserInfoField


#UDP组播组信息
CSecurityFtdcMulticastGroupInfoField = {}
#组播组IP地址
CSecurityFtdcMulticastGroupInfoField["GroupIP"] = "string"
#组播组IP端口
CSecurityFtdcMulticastGroupInfoField["GroupPort"] = "int"
#源地址
CSecurityFtdcMulticastGroupInfoField["SourceIP"] = "string"
structDict['CSecurityFtdcMulticastGroupInfoField'] = CSecurityFtdcMulticastGroupInfoField


#Level2逐笔委托
CSecurityFtdcL2OrderField = {}
#委托组
CSecurityFtdcL2OrderField["OrderGroupID"] = "int"
#委托序号
CSecurityFtdcL2OrderField["OrderIndex"] = "int"
#委托时间（秒）
CSecurityFtdcL2OrderField["OrderTime"] = "string"
#交易所代码
CSecurityFtdcL2OrderField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcL2OrderField["InstrumentID"] = "string"
#委托价格
CSecurityFtdcL2OrderField["Price"] = "float"
#委托数量
CSecurityFtdcL2OrderField["Volume"] = "int"
#报单类型
CSecurityFtdcL2OrderField["OrderKind"] = "string"
#功能码
CSecurityFtdcL2OrderField["FunctionCode"] = "string"
structDict['CSecurityFtdcL2OrderField'] = CSecurityFtdcL2OrderField


#Level2逐笔成交
CSecurityFtdcL2TradeField = {}
#成交组
CSecurityFtdcL2TradeField["TradeGroupID"] = "int"
#成交序号
CSecurityFtdcL2TradeField["TradeIndex"] = "int"
#买方委托序号
CSecurityFtdcL2TradeField["BuyIndex"] = "int"
#卖方委托序号
CSecurityFtdcL2TradeField["SellIndex"] = "int"
#成交时间（秒）
CSecurityFtdcL2TradeField["TradeTime"] = "string"
#交易所代码
CSecurityFtdcL2TradeField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcL2TradeField["InstrumentID"] = "string"
#成交价格
CSecurityFtdcL2TradeField["Price"] = "float"
#成交数量
CSecurityFtdcL2TradeField["Volume"] = "int"
#报单类型
CSecurityFtdcL2TradeField["OrderKind"] = "string"
#功能码
CSecurityFtdcL2TradeField["FunctionCode"] = "string"
structDict['CSecurityFtdcL2TradeField'] = CSecurityFtdcL2TradeField






