# encoding: UTF-8

structDict = {}

#//////////////////////////////////////////////////////////////////////
#@system 风控前置系统
#@company CFFEX
#@file USTPFtdcUserApiStruct.h
#@brief 定义了客户端接口使用的业务数据结构
#@history 
#//////////////////////////////////////////////////////////////////////










#系统用户登录请求
CUstpFtdcReqUserLoginField = {}
#交易日
CUstpFtdcReqUserLoginField["TradingDay"] = "string"
#交易用户代码
CUstpFtdcReqUserLoginField["UserID"] = "string"
#经纪公司编号
CUstpFtdcReqUserLoginField["BrokerID"] = "string"
#密码
CUstpFtdcReqUserLoginField["Password"] = "string"
#用户端产品信息
CUstpFtdcReqUserLoginField["UserProductInfo"] = "string"
#接口端产品信息
CUstpFtdcReqUserLoginField["InterfaceProductInfo"] = "string"
#协议信息
CUstpFtdcReqUserLoginField["ProtocolInfo"] = "string"
#IP地址
CUstpFtdcReqUserLoginField["IPAddress"] = "string"
#Mac地址
CUstpFtdcReqUserLoginField["MacAddress"] = "string"
#数据中心代码
CUstpFtdcReqUserLoginField["DataCenterID"] = "int"
structDict['CUstpFtdcReqUserLoginField'] = CUstpFtdcReqUserLoginField

#系统用户登录应答
CUstpFtdcRspUserLoginField = {}
#交易日
CUstpFtdcRspUserLoginField["TradingDay"] = "string"
#经纪公司编号
CUstpFtdcRspUserLoginField["BrokerID"] = "string"
#交易用户代码
CUstpFtdcRspUserLoginField["UserID"] = "string"
#登录成功时间
CUstpFtdcRspUserLoginField["LoginTime"] = "string"
#用户最大本地报单号
CUstpFtdcRspUserLoginField["MaxOrderLocalID"] = "string"
#交易系统名称
CUstpFtdcRspUserLoginField["TradingSystemName"] = "string"
#数据中心代码
CUstpFtdcRspUserLoginField["DataCenterID"] = "int"
#会员私有流当前长度
CUstpFtdcRspUserLoginField["PrivateFlowSize"] = "int"
#交易员私有流当前长度
CUstpFtdcRspUserLoginField["UserFlowSize"] = "int"
structDict['CUstpFtdcRspUserLoginField'] = CUstpFtdcRspUserLoginField

#用户登出请求
CUstpFtdcReqUserLogoutField = {}
#经纪公司编号
CUstpFtdcReqUserLogoutField["BrokerID"] = "string"
#交易用户代码
CUstpFtdcReqUserLogoutField["UserID"] = "string"
structDict['CUstpFtdcReqUserLogoutField'] = CUstpFtdcReqUserLogoutField

#用户登出请求
CUstpFtdcRspUserLogoutField = {}
#经纪公司编号
CUstpFtdcRspUserLogoutField["BrokerID"] = "string"
#交易用户代码
CUstpFtdcRspUserLogoutField["UserID"] = "string"
structDict['CUstpFtdcRspUserLogoutField'] = CUstpFtdcRspUserLogoutField

#强制用户退出
CUstpFtdcForceUserExitField = {}
#经纪公司编号
CUstpFtdcForceUserExitField["BrokerID"] = "string"
#交易用户代码
CUstpFtdcForceUserExitField["UserID"] = "string"
structDict['CUstpFtdcForceUserExitField'] = CUstpFtdcForceUserExitField

#用户口令修改
CUstpFtdcUserPasswordUpdateField = {}
#经纪公司编号
CUstpFtdcUserPasswordUpdateField["BrokerID"] = "string"
#交易用户代码
CUstpFtdcUserPasswordUpdateField["UserID"] = "string"
#旧密码
CUstpFtdcUserPasswordUpdateField["OldPassword"] = "string"
#新密码
CUstpFtdcUserPasswordUpdateField["NewPassword"] = "string"
structDict['CUstpFtdcUserPasswordUpdateField'] = CUstpFtdcUserPasswordUpdateField

#输入报单
CUstpFtdcInputOrderField = {}
#经纪公司编号
CUstpFtdcInputOrderField["BrokerID"] = "string"
#交易所代码
CUstpFtdcInputOrderField["ExchangeID"] = "string"
#系统报单编号
CUstpFtdcInputOrderField["OrderSysID"] = "string"
#投资者编号
CUstpFtdcInputOrderField["InvestorID"] = "string"
#用户代码
CUstpFtdcInputOrderField["UserID"] = "string"
#合约代码
CUstpFtdcInputOrderField["InstrumentID"] = "string"
#用户本地报单号
CUstpFtdcInputOrderField["UserOrderLocalID"] = "string"
#报单类型
CUstpFtdcInputOrderField["OrderPriceType"] = "string"
#买卖方向
CUstpFtdcInputOrderField["Direction"] = "string"
#开平标志
CUstpFtdcInputOrderField["OffsetFlag"] = "string"
#投机套保标志
CUstpFtdcInputOrderField["HedgeFlag"] = "string"
#价格
CUstpFtdcInputOrderField["LimitPrice"] = "float"
#数量
CUstpFtdcInputOrderField["Volume"] = "int"
#有效期类型
CUstpFtdcInputOrderField["TimeCondition"] = "string"
#GTD日期
CUstpFtdcInputOrderField["GTDDate"] = "string"
#成交量类型
CUstpFtdcInputOrderField["VolumeCondition"] = "string"
#最小成交量
CUstpFtdcInputOrderField["MinVolume"] = "int"
#止损价
CUstpFtdcInputOrderField["StopPrice"] = "float"
#强平原因
CUstpFtdcInputOrderField["ForceCloseReason"] = "string"
#自动挂起标志
CUstpFtdcInputOrderField["IsAutoSuspend"] = "int"
#业务单元
CUstpFtdcInputOrderField["BusinessUnit"] = "string"
#用户自定义域
CUstpFtdcInputOrderField["UserCustom"] = "string"
structDict['CUstpFtdcInputOrderField'] = CUstpFtdcInputOrderField

#报单操作
CUstpFtdcOrderActionField = {}
#交易所代码
CUstpFtdcOrderActionField["ExchangeID"] = "string"
#报单编号
CUstpFtdcOrderActionField["OrderSysID"] = "string"
#经纪公司编号
CUstpFtdcOrderActionField["BrokerID"] = "string"
#投资者编号
CUstpFtdcOrderActionField["InvestorID"] = "string"
#用户代码
CUstpFtdcOrderActionField["UserID"] = "string"
#本次撤单操作的本地编号
CUstpFtdcOrderActionField["UserOrderActionLocalID"] = "string"
#被撤订单的本地报单编号
CUstpFtdcOrderActionField["UserOrderLocalID"] = "string"
#报单操作标志
CUstpFtdcOrderActionField["ActionFlag"] = "string"
#价格
CUstpFtdcOrderActionField["LimitPrice"] = "float"
#数量变化
CUstpFtdcOrderActionField["VolumeChange"] = "int"
structDict['CUstpFtdcOrderActionField'] = CUstpFtdcOrderActionField

#内存表导出
CUstpFtdcMemDbField = {}
#内存表名
CUstpFtdcMemDbField["MemTableName"] = "string"
structDict['CUstpFtdcMemDbField'] = CUstpFtdcMemDbField

#响应信息
CUstpFtdcRspInfoField = {}
#错误代码
CUstpFtdcRspInfoField["ErrorID"] = "int"
#错误信息
CUstpFtdcRspInfoField["ErrorMsg"] = "string"
structDict['CUstpFtdcRspInfoField'] = CUstpFtdcRspInfoField

#报单查询
CUstpFtdcQryOrderField = {}
#经纪公司编号
CUstpFtdcQryOrderField["BrokerID"] = "string"
#用户代码
CUstpFtdcQryOrderField["UserID"] = "string"
#交易所代码
CUstpFtdcQryOrderField["ExchangeID"] = "string"
#投资者编号
CUstpFtdcQryOrderField["InvestorID"] = "string"
#报单编号
CUstpFtdcQryOrderField["OrderSysID"] = "string"
#合约代码
CUstpFtdcQryOrderField["InstrumentID"] = "string"
structDict['CUstpFtdcQryOrderField'] = CUstpFtdcQryOrderField

#成交查询
CUstpFtdcQryTradeField = {}
#经纪公司编号
CUstpFtdcQryTradeField["BrokerID"] = "string"
#用户代码
CUstpFtdcQryTradeField["UserID"] = "string"
#交易所代码
CUstpFtdcQryTradeField["ExchangeID"] = "string"
#投资者编号
CUstpFtdcQryTradeField["InvestorID"] = "string"
#成交编号
CUstpFtdcQryTradeField["TradeID"] = "string"
#合约代码
CUstpFtdcQryTradeField["InstrumentID"] = "string"
structDict['CUstpFtdcQryTradeField'] = CUstpFtdcQryTradeField

#合约查询
CUstpFtdcQryInstrumentField = {}
#交易所代码
CUstpFtdcQryInstrumentField["ExchangeID"] = "string"
#产品代码
CUstpFtdcQryInstrumentField["ProductID"] = "string"
#合约代码
CUstpFtdcQryInstrumentField["InstrumentID"] = "string"
structDict['CUstpFtdcQryInstrumentField'] = CUstpFtdcQryInstrumentField

#合约查询应答
CUstpFtdcRspInstrumentField = {}
#交易所代码
CUstpFtdcRspInstrumentField["ExchangeID"] = "string"
#品种代码
CUstpFtdcRspInstrumentField["ProductID"] = "string"
#品种名称
CUstpFtdcRspInstrumentField["ProductName"] = "string"
#合约代码
CUstpFtdcRspInstrumentField["InstrumentID"] = "string"
#合约名称
CUstpFtdcRspInstrumentField["InstrumentName"] = "string"
#交割年份
CUstpFtdcRspInstrumentField["DeliveryYear"] = "int"
#交割月
CUstpFtdcRspInstrumentField["DeliveryMonth"] = "int"
#限价单最大下单量
CUstpFtdcRspInstrumentField["MaxLimitOrderVolume"] = "int"
#限价单最小下单量
CUstpFtdcRspInstrumentField["MinLimitOrderVolume"] = "int"
#市价单最大下单量
CUstpFtdcRspInstrumentField["MaxMarketOrderVolume"] = "int"
#市价单最小下单量
CUstpFtdcRspInstrumentField["MinMarketOrderVolume"] = "int"
#数量乘数
CUstpFtdcRspInstrumentField["VolumeMultiple"] = "int"
#报价单位
CUstpFtdcRspInstrumentField["PriceTick"] = "float"
#币种
CUstpFtdcRspInstrumentField["Currency"] = "string"
#多头限仓
CUstpFtdcRspInstrumentField["LongPosLimit"] = "int"
#空头限仓
CUstpFtdcRspInstrumentField["ShortPosLimit"] = "int"
#跌停板价
CUstpFtdcRspInstrumentField["LowerLimitPrice"] = "float"
#涨停板价
CUstpFtdcRspInstrumentField["UpperLimitPrice"] = "float"
#昨结算
CUstpFtdcRspInstrumentField["PreSettlementPrice"] = "float"
#合约交易状态
CUstpFtdcRspInstrumentField["InstrumentStatus"] = "string"
#创建日
CUstpFtdcRspInstrumentField["CreateDate"] = "string"
#上市日
CUstpFtdcRspInstrumentField["OpenDate"] = "string"
#到期日
CUstpFtdcRspInstrumentField["ExpireDate"] = "string"
#开始交割日
CUstpFtdcRspInstrumentField["StartDelivDate"] = "string"
#最后交割日
CUstpFtdcRspInstrumentField["EndDelivDate"] = "string"
#挂牌基准价
CUstpFtdcRspInstrumentField["BasisPrice"] = "float"
#当前是否交易
CUstpFtdcRspInstrumentField["IsTrading"] = "int"
#基础商品代码
CUstpFtdcRspInstrumentField["UnderlyingInstrID"] = "string"
#基础商品乘数
CUstpFtdcRspInstrumentField["UnderlyingMultiple"] = "int"
#持仓类型
CUstpFtdcRspInstrumentField["PositionType"] = "string"
#执行价
CUstpFtdcRspInstrumentField["StrikePrice"] = "float"
#期权类型
CUstpFtdcRspInstrumentField["OptionsType"] = "string"
structDict['CUstpFtdcRspInstrumentField'] = CUstpFtdcRspInstrumentField

#合约状态
CUstpFtdcInstrumentStatusField = {}
#交易所代码
CUstpFtdcInstrumentStatusField["ExchangeID"] = "string"
#品种代码
CUstpFtdcInstrumentStatusField["ProductID"] = "string"
#品种名称
CUstpFtdcInstrumentStatusField["ProductName"] = "string"
#合约代码
CUstpFtdcInstrumentStatusField["InstrumentID"] = "string"
#合约名称
CUstpFtdcInstrumentStatusField["InstrumentName"] = "string"
#交割年份
CUstpFtdcInstrumentStatusField["DeliveryYear"] = "int"
#交割月
CUstpFtdcInstrumentStatusField["DeliveryMonth"] = "int"
#限价单最大下单量
CUstpFtdcInstrumentStatusField["MaxLimitOrderVolume"] = "int"
#限价单最小下单量
CUstpFtdcInstrumentStatusField["MinLimitOrderVolume"] = "int"
#市价单最大下单量
CUstpFtdcInstrumentStatusField["MaxMarketOrderVolume"] = "int"
#市价单最小下单量
CUstpFtdcInstrumentStatusField["MinMarketOrderVolume"] = "int"
#数量乘数
CUstpFtdcInstrumentStatusField["VolumeMultiple"] = "int"
#报价单位
CUstpFtdcInstrumentStatusField["PriceTick"] = "float"
#币种
CUstpFtdcInstrumentStatusField["Currency"] = "string"
#多头限仓
CUstpFtdcInstrumentStatusField["LongPosLimit"] = "int"
#空头限仓
CUstpFtdcInstrumentStatusField["ShortPosLimit"] = "int"
#跌停板价
CUstpFtdcInstrumentStatusField["LowerLimitPrice"] = "float"
#涨停板价
CUstpFtdcInstrumentStatusField["UpperLimitPrice"] = "float"
#昨结算
CUstpFtdcInstrumentStatusField["PreSettlementPrice"] = "float"
#合约交易状态
CUstpFtdcInstrumentStatusField["InstrumentStatus"] = "string"
#创建日
CUstpFtdcInstrumentStatusField["CreateDate"] = "string"
#上市日
CUstpFtdcInstrumentStatusField["OpenDate"] = "string"
#到期日
CUstpFtdcInstrumentStatusField["ExpireDate"] = "string"
#开始交割日
CUstpFtdcInstrumentStatusField["StartDelivDate"] = "string"
#最后交割日
CUstpFtdcInstrumentStatusField["EndDelivDate"] = "string"
#挂牌基准价
CUstpFtdcInstrumentStatusField["BasisPrice"] = "float"
#当前是否交易
CUstpFtdcInstrumentStatusField["IsTrading"] = "int"
#基础商品代码
CUstpFtdcInstrumentStatusField["UnderlyingInstrID"] = "string"
#基础商品乘数
CUstpFtdcInstrumentStatusField["UnderlyingMultiple"] = "int"
#持仓类型
CUstpFtdcInstrumentStatusField["PositionType"] = "string"
#执行价
CUstpFtdcInstrumentStatusField["StrikePrice"] = "float"
#期权类型
CUstpFtdcInstrumentStatusField["OptionsType"] = "string"
structDict['CUstpFtdcInstrumentStatusField'] = CUstpFtdcInstrumentStatusField

#投资者资金查询
CUstpFtdcQryInvestorAccountField = {}
#经纪公司编号
CUstpFtdcQryInvestorAccountField["BrokerID"] = "string"
#用户代码
CUstpFtdcQryInvestorAccountField["UserID"] = "string"
#投资者编号
CUstpFtdcQryInvestorAccountField["InvestorID"] = "string"
structDict['CUstpFtdcQryInvestorAccountField'] = CUstpFtdcQryInvestorAccountField

#投资者资金应答
CUstpFtdcRspInvestorAccountField = {}
#经纪公司编号
CUstpFtdcRspInvestorAccountField["BrokerID"] = "string"
#投资者编号
CUstpFtdcRspInvestorAccountField["InvestorID"] = "string"
#资金帐号
CUstpFtdcRspInvestorAccountField["AccountID"] = "string"
#上次结算准备金
CUstpFtdcRspInvestorAccountField["PreBalance"] = "float"
#入金金额
CUstpFtdcRspInvestorAccountField["Deposit"] = "float"
#出金金额
CUstpFtdcRspInvestorAccountField["Withdraw"] = "float"
#冻结的保证金
CUstpFtdcRspInvestorAccountField["FrozenMargin"] = "float"
#冻结手续费
CUstpFtdcRspInvestorAccountField["FrozenFee"] = "float"
#冻结权利金
CUstpFtdcRspInvestorAccountField["FrozenPremium"] = "float"
#手续费
CUstpFtdcRspInvestorAccountField["Fee"] = "float"
#平仓盈亏
CUstpFtdcRspInvestorAccountField["CloseProfit"] = "float"
#持仓盈亏
CUstpFtdcRspInvestorAccountField["PositionProfit"] = "float"
#可用资金
CUstpFtdcRspInvestorAccountField["Available"] = "float"
#多头冻结的保证金
CUstpFtdcRspInvestorAccountField["LongFrozenMargin"] = "float"
#空头冻结的保证金
CUstpFtdcRspInvestorAccountField["ShortFrozenMargin"] = "float"
#多头占用保证金
CUstpFtdcRspInvestorAccountField["LongMargin"] = "float"
#空头占用保证金
CUstpFtdcRspInvestorAccountField["ShortMargin"] = "float"
#当日释放保证金
CUstpFtdcRspInvestorAccountField["ReleaseMargin"] = "float"
#动态权益
CUstpFtdcRspInvestorAccountField["DynamicRights"] = "float"
#今日出入金
CUstpFtdcRspInvestorAccountField["TodayInOut"] = "float"
#占用保证金
CUstpFtdcRspInvestorAccountField["Margin"] = "float"
#期权权利金收支
CUstpFtdcRspInvestorAccountField["Premium"] = "float"
#风险度
CUstpFtdcRspInvestorAccountField["Risk"] = "float"
structDict['CUstpFtdcRspInvestorAccountField'] = CUstpFtdcRspInvestorAccountField

#可用投资者查询
CUstpFtdcQryUserInvestorField = {}
#经纪公司编号
CUstpFtdcQryUserInvestorField["BrokerID"] = "string"
#用户代码
CUstpFtdcQryUserInvestorField["UserID"] = "string"
structDict['CUstpFtdcQryUserInvestorField'] = CUstpFtdcQryUserInvestorField

#可用投资者
CUstpFtdcRspUserInvestorField = {}
#经纪公司编号
CUstpFtdcRspUserInvestorField["BrokerID"] = "string"
#交易用户代码
CUstpFtdcRspUserInvestorField["UserID"] = "string"
#投资者编号
CUstpFtdcRspUserInvestorField["InvestorID"] = "string"
structDict['CUstpFtdcRspUserInvestorField'] = CUstpFtdcRspUserInvestorField

#交易编码查询
CUstpFtdcQryTradingCodeField = {}
#经纪公司编号
CUstpFtdcQryTradingCodeField["BrokerID"] = "string"
#用户代码
CUstpFtdcQryTradingCodeField["UserID"] = "string"
#投资者编号
CUstpFtdcQryTradingCodeField["InvestorID"] = "string"
#交易所代码
CUstpFtdcQryTradingCodeField["ExchangeID"] = "string"
structDict['CUstpFtdcQryTradingCodeField'] = CUstpFtdcQryTradingCodeField

#交易编码查询
CUstpFtdcRspTradingCodeField = {}
#经纪公司编号
CUstpFtdcRspTradingCodeField["BrokerID"] = "string"
#交易所代码
CUstpFtdcRspTradingCodeField["ExchangeID"] = "string"
#投资者编号
CUstpFtdcRspTradingCodeField["InvestorID"] = "string"
#客户代码
CUstpFtdcRspTradingCodeField["ClientID"] = "string"
#客户代码权限
CUstpFtdcRspTradingCodeField["ClientRight"] = "string"
#是否活跃
CUstpFtdcRspTradingCodeField["IsActive"] = "string"
structDict['CUstpFtdcRspTradingCodeField'] = CUstpFtdcRspTradingCodeField

#交易所查询请求
CUstpFtdcQryExchangeField = {}
#交易所代码
CUstpFtdcQryExchangeField["ExchangeID"] = "string"
structDict['CUstpFtdcQryExchangeField'] = CUstpFtdcQryExchangeField

#交易所查询应答
CUstpFtdcRspExchangeField = {}
#交易所代码
CUstpFtdcRspExchangeField["ExchangeID"] = "string"
#交易所名称
CUstpFtdcRspExchangeField["ExchangeName"] = "string"
structDict['CUstpFtdcRspExchangeField'] = CUstpFtdcRspExchangeField

#投资者持仓查询请求
CUstpFtdcQryInvestorPositionField = {}
#经纪公司编号
CUstpFtdcQryInvestorPositionField["BrokerID"] = "string"
#用户代码
CUstpFtdcQryInvestorPositionField["UserID"] = "string"
#交易所代码
CUstpFtdcQryInvestorPositionField["ExchangeID"] = "string"
#投资者编号
CUstpFtdcQryInvestorPositionField["InvestorID"] = "string"
#合约代码
CUstpFtdcQryInvestorPositionField["InstrumentID"] = "string"
structDict['CUstpFtdcQryInvestorPositionField'] = CUstpFtdcQryInvestorPositionField

#投资者持仓查询应答
CUstpFtdcRspInvestorPositionField = {}
#投资者编号
CUstpFtdcRspInvestorPositionField["InvestorID"] = "string"
#经纪公司编号
CUstpFtdcRspInvestorPositionField["BrokerID"] = "string"
#交易所代码
CUstpFtdcRspInvestorPositionField["ExchangeID"] = "string"
#客户代码
CUstpFtdcRspInvestorPositionField["ClientID"] = "string"
#合约代码
CUstpFtdcRspInvestorPositionField["InstrumentID"] = "string"
#买卖方向
CUstpFtdcRspInvestorPositionField["Direction"] = "string"
#投机套保标志
CUstpFtdcRspInvestorPositionField["HedgeFlag"] = "string"
#占用保证金
CUstpFtdcRspInvestorPositionField["UsedMargin"] = "float"
#今持仓量
CUstpFtdcRspInvestorPositionField["Position"] = "int"
#今日持仓成本
CUstpFtdcRspInvestorPositionField["PositionCost"] = "float"
#昨持仓量
CUstpFtdcRspInvestorPositionField["YdPosition"] = "int"
#昨日持仓成本
CUstpFtdcRspInvestorPositionField["YdPositionCost"] = "float"
#冻结的保证金
CUstpFtdcRspInvestorPositionField["FrozenMargin"] = "float"
#开仓冻结持仓
CUstpFtdcRspInvestorPositionField["FrozenPosition"] = "int"
#平仓冻结持仓
CUstpFtdcRspInvestorPositionField["FrozenClosing"] = "int"
#冻结的权利金
CUstpFtdcRspInvestorPositionField["FrozenPremium"] = "float"
#最后一笔成交编号
CUstpFtdcRspInvestorPositionField["LastTradeID"] = "string"
#最后一笔本地报单编号
CUstpFtdcRspInvestorPositionField["LastOrderLocalID"] = "string"
#币种
CUstpFtdcRspInvestorPositionField["Currency"] = "string"
structDict['CUstpFtdcRspInvestorPositionField'] = CUstpFtdcRspInvestorPositionField

#合规参数查询请求
CUstpFtdcQryComplianceParamField = {}
#经纪公司编号
CUstpFtdcQryComplianceParamField["BrokerID"] = "string"
#用户代码
CUstpFtdcQryComplianceParamField["UserID"] = "string"
#投资者编号
CUstpFtdcQryComplianceParamField["InvestorID"] = "string"
#交易所代码
CUstpFtdcQryComplianceParamField["ExchangeID"] = "string"
structDict['CUstpFtdcQryComplianceParamField'] = CUstpFtdcQryComplianceParamField

#合规参数查询应答
CUstpFtdcRspComplianceParamField = {}
#经纪公司编号
CUstpFtdcRspComplianceParamField["BrokerID"] = "string"
#投资者编号
CUstpFtdcRspComplianceParamField["InvestorID"] = "string"
#交易所代码
CUstpFtdcRspComplianceParamField["ExchangeID"] = "string"
#客户号
CUstpFtdcRspComplianceParamField["ClientID"] = "string"
#每日最大报单笔
CUstpFtdcRspComplianceParamField["DailyMaxOrder"] = "int"
#每日最大撤单笔
CUstpFtdcRspComplianceParamField["DailyMaxOrderAction"] = "int"
#每日最大错单笔
CUstpFtdcRspComplianceParamField["DailyMaxErrorOrder"] = "int"
#每日最大报单手
CUstpFtdcRspComplianceParamField["DailyMaxOrderVolume"] = "int"
#每日最大撤单手
CUstpFtdcRspComplianceParamField["DailyMaxOrderActionVolume"] = "int"
structDict['CUstpFtdcRspComplianceParamField'] = CUstpFtdcRspComplianceParamField

#用户查询
CUstpFtdcQryUserField = {}
#交易用户代码
CUstpFtdcQryUserField["StartUserID"] = "string"
#交易用户代码
CUstpFtdcQryUserField["EndUserID"] = "string"
structDict['CUstpFtdcQryUserField'] = CUstpFtdcQryUserField

#用户
CUstpFtdcUserField = {}
#经纪公司编号
CUstpFtdcUserField["BrokerID"] = "string"
#用户代码
CUstpFtdcUserField["UserID"] = "string"
#用户登录密码
CUstpFtdcUserField["Password"] = "string"
#是否活跃
CUstpFtdcUserField["IsActive"] = "string"
#用户名称
CUstpFtdcUserField["UserName"] = "string"
#用户类型
CUstpFtdcUserField["UserType"] = "string"
#营业部
CUstpFtdcUserField["Department"] = "string"
#授权功能集
CUstpFtdcUserField["GrantFuncSet"] = "string"
#修改用户编号
CUstpFtdcUserField["SetUserID"] = "string"
#操作日期
CUstpFtdcUserField["CommandDate"] = "string"
#操作时间
CUstpFtdcUserField["CommandTime"] = "string"
structDict['CUstpFtdcUserField'] = CUstpFtdcUserField

#投资者手续费率查询
CUstpFtdcQryInvestorFeeField = {}
#经纪公司编号
CUstpFtdcQryInvestorFeeField["BrokerID"] = "string"
#用户代码
CUstpFtdcQryInvestorFeeField["UserID"] = "string"
#投资者编号
CUstpFtdcQryInvestorFeeField["InvestorID"] = "string"
#交易所代码
CUstpFtdcQryInvestorFeeField["ExchangeID"] = "string"
#合约代码
CUstpFtdcQryInvestorFeeField["InstrumentID"] = "string"
structDict['CUstpFtdcQryInvestorFeeField'] = CUstpFtdcQryInvestorFeeField

#投资者手续费率
CUstpFtdcInvestorFeeField = {}
#经纪公司编号
CUstpFtdcInvestorFeeField["BrokerID"] = "string"
#客户号
CUstpFtdcInvestorFeeField["ClientID"] = "string"
#交易所代码
CUstpFtdcInvestorFeeField["ExchangeID"] = "string"
#合约代码
CUstpFtdcInvestorFeeField["InstrumentID"] = "string"
#品种代码
CUstpFtdcInvestorFeeField["ProductID"] = "string"
#开仓手续费按比例
CUstpFtdcInvestorFeeField["OpenFeeRate"] = "float"
#开仓手续费按手数
CUstpFtdcInvestorFeeField["OpenFeeAmt"] = "float"
#平仓手续费按比例
CUstpFtdcInvestorFeeField["OffsetFeeRate"] = "float"
#平仓手续费按手数
CUstpFtdcInvestorFeeField["OffsetFeeAmt"] = "float"
#平今仓手续费按比例
CUstpFtdcInvestorFeeField["OTFeeRate"] = "float"
#平今仓手续费按手数
CUstpFtdcInvestorFeeField["OTFeeAmt"] = "float"
structDict['CUstpFtdcInvestorFeeField'] = CUstpFtdcInvestorFeeField

#投资者保证金率查询
CUstpFtdcQryInvestorMarginField = {}
#经纪公司编号
CUstpFtdcQryInvestorMarginField["BrokerID"] = "string"
#用户代码
CUstpFtdcQryInvestorMarginField["UserID"] = "string"
#投资者编号
CUstpFtdcQryInvestorMarginField["InvestorID"] = "string"
#交易所代码
CUstpFtdcQryInvestorMarginField["ExchangeID"] = "string"
#合约代码
CUstpFtdcQryInvestorMarginField["InstrumentID"] = "string"
structDict['CUstpFtdcQryInvestorMarginField'] = CUstpFtdcQryInvestorMarginField

#投资者保证金率
CUstpFtdcInvestorMarginField = {}
#经纪公司编号
CUstpFtdcInvestorMarginField["BrokerID"] = "string"
#客户号
CUstpFtdcInvestorMarginField["ClientID"] = "string"
#交易所代码
CUstpFtdcInvestorMarginField["ExchangeID"] = "string"
#合约代码
CUstpFtdcInvestorMarginField["InstrumentID"] = "string"
#品种代码
CUstpFtdcInvestorMarginField["ProductID"] = "string"
#多头占用保证金按比例
CUstpFtdcInvestorMarginField["LongMarginRate"] = "float"
#多头保证金按手数
CUstpFtdcInvestorMarginField["LongMarginAmt"] = "float"
#空头占用保证金按比例
CUstpFtdcInvestorMarginField["ShortMarginRate"] = "float"
#空头保证金按手数
CUstpFtdcInvestorMarginField["ShortMarginAmt"] = "float"
structDict['CUstpFtdcInvestorMarginField'] = CUstpFtdcInvestorMarginField

#成交
CUstpFtdcTradeField = {}
#经纪公司编号
CUstpFtdcTradeField["BrokerID"] = "string"
#交易所代码
CUstpFtdcTradeField["ExchangeID"] = "string"
#交易日
CUstpFtdcTradeField["TradingDay"] = "string"
#会员编号
CUstpFtdcTradeField["ParticipantID"] = "string"
#下单席位号
CUstpFtdcTradeField["SeatID"] = "string"
#投资者编号
CUstpFtdcTradeField["InvestorID"] = "string"
#客户号
CUstpFtdcTradeField["ClientID"] = "string"
#用户编号
CUstpFtdcTradeField["UserID"] = "string"
#成交编号
CUstpFtdcTradeField["TradeID"] = "string"
#报单编号
CUstpFtdcTradeField["OrderSysID"] = "string"
#本地报单编号
CUstpFtdcTradeField["UserOrderLocalID"] = "string"
#合约代码
CUstpFtdcTradeField["InstrumentID"] = "string"
#买卖方向
CUstpFtdcTradeField["Direction"] = "string"
#开平标志
CUstpFtdcTradeField["OffsetFlag"] = "string"
#投机套保标志
CUstpFtdcTradeField["HedgeFlag"] = "string"
#成交价格
CUstpFtdcTradeField["TradePrice"] = "float"
#成交数量
CUstpFtdcTradeField["TradeVolume"] = "int"
#成交时间
CUstpFtdcTradeField["TradeTime"] = "string"
#清算会员编号
CUstpFtdcTradeField["ClearingPartID"] = "string"
structDict['CUstpFtdcTradeField'] = CUstpFtdcTradeField

#报单
CUstpFtdcOrderField = {}
#经纪公司编号
CUstpFtdcOrderField["BrokerID"] = "string"
#交易所代码
CUstpFtdcOrderField["ExchangeID"] = "string"
#系统报单编号
CUstpFtdcOrderField["OrderSysID"] = "string"
#投资者编号
CUstpFtdcOrderField["InvestorID"] = "string"
#用户代码
CUstpFtdcOrderField["UserID"] = "string"
#合约代码
CUstpFtdcOrderField["InstrumentID"] = "string"
#用户本地报单号
CUstpFtdcOrderField["UserOrderLocalID"] = "string"
#报单类型
CUstpFtdcOrderField["OrderPriceType"] = "string"
#买卖方向
CUstpFtdcOrderField["Direction"] = "string"
#开平标志
CUstpFtdcOrderField["OffsetFlag"] = "string"
#投机套保标志
CUstpFtdcOrderField["HedgeFlag"] = "string"
#价格
CUstpFtdcOrderField["LimitPrice"] = "float"
#数量
CUstpFtdcOrderField["Volume"] = "int"
#有效期类型
CUstpFtdcOrderField["TimeCondition"] = "string"
#GTD日期
CUstpFtdcOrderField["GTDDate"] = "string"
#成交量类型
CUstpFtdcOrderField["VolumeCondition"] = "string"
#最小成交量
CUstpFtdcOrderField["MinVolume"] = "int"
#止损价
CUstpFtdcOrderField["StopPrice"] = "float"
#强平原因
CUstpFtdcOrderField["ForceCloseReason"] = "string"
#自动挂起标志
CUstpFtdcOrderField["IsAutoSuspend"] = "int"
#业务单元
CUstpFtdcOrderField["BusinessUnit"] = "string"
#用户自定义域
CUstpFtdcOrderField["UserCustom"] = "string"
#交易日
CUstpFtdcOrderField["TradingDay"] = "string"
#会员编号
CUstpFtdcOrderField["ParticipantID"] = "string"
#客户号
CUstpFtdcOrderField["ClientID"] = "string"
#下单席位号
CUstpFtdcOrderField["SeatID"] = "string"
#插入时间
CUstpFtdcOrderField["InsertTime"] = "string"
#本地报单编号
CUstpFtdcOrderField["OrderLocalID"] = "string"
#报单来源
CUstpFtdcOrderField["OrderSource"] = "string"
#报单状态
CUstpFtdcOrderField["OrderStatus"] = "string"
#撤销时间
CUstpFtdcOrderField["CancelTime"] = "string"
#撤单用户编号
CUstpFtdcOrderField["CancelUserID"] = "string"
#今成交数量
CUstpFtdcOrderField["VolumeTraded"] = "int"
#剩余数量
CUstpFtdcOrderField["VolumeRemain"] = "int"
structDict['CUstpFtdcOrderField'] = CUstpFtdcOrderField

#数据流回退
CUstpFtdcFlowMessageCancelField = {}
#序列系列号
CUstpFtdcFlowMessageCancelField["SequenceSeries"] = "int"
#交易日
CUstpFtdcFlowMessageCancelField["TradingDay"] = "string"
#数据中心代码
CUstpFtdcFlowMessageCancelField["DataCenterID"] = "int"
#回退起始序列号
CUstpFtdcFlowMessageCancelField["StartSequenceNo"] = "int"
#回退结束序列号
CUstpFtdcFlowMessageCancelField["EndSequenceNo"] = "int"
structDict['CUstpFtdcFlowMessageCancelField'] = CUstpFtdcFlowMessageCancelField

#信息分发
CUstpFtdcDisseminationField = {}
#序列系列号
CUstpFtdcDisseminationField["SequenceSeries"] = "int"
#序列号
CUstpFtdcDisseminationField["SequenceNo"] = "int"
structDict['CUstpFtdcDisseminationField'] = CUstpFtdcDisseminationField

#出入金结果
CUstpFtdcInvestorAccountDepositResField = {}
#经纪公司编号
CUstpFtdcInvestorAccountDepositResField["BrokerID"] = "string"
#用户代码
CUstpFtdcInvestorAccountDepositResField["UserID"] = "string"
#投资者编号
CUstpFtdcInvestorAccountDepositResField["InvestorID"] = "string"
#资金帐号
CUstpFtdcInvestorAccountDepositResField["AccountID"] = "string"
#资金流水号
CUstpFtdcInvestorAccountDepositResField["AccountSeqNo"] = "string"
#金额
CUstpFtdcInvestorAccountDepositResField["Amount"] = "float"
#出入金方向
CUstpFtdcInvestorAccountDepositResField["AmountDirection"] = "string"
#可用资金
CUstpFtdcInvestorAccountDepositResField["Available"] = "float"
#结算准备金
CUstpFtdcInvestorAccountDepositResField["Balance"] = "float"
structDict['CUstpFtdcInvestorAccountDepositResField'] = CUstpFtdcInvestorAccountDepositResField

#行情基础属性
CUstpFtdcMarketDataBaseField = {}
#交易日
CUstpFtdcMarketDataBaseField["TradingDay"] = "string"
#结算组代码
CUstpFtdcMarketDataBaseField["SettlementGroupID"] = "string"
#结算编号
CUstpFtdcMarketDataBaseField["SettlementID"] = "int"
#昨结算
CUstpFtdcMarketDataBaseField["PreSettlementPrice"] = "float"
#昨收盘
CUstpFtdcMarketDataBaseField["PreClosePrice"] = "float"
#昨持仓量
CUstpFtdcMarketDataBaseField["PreOpenInterest"] = "float"
#昨虚实度
CUstpFtdcMarketDataBaseField["PreDelta"] = "float"
structDict['CUstpFtdcMarketDataBaseField'] = CUstpFtdcMarketDataBaseField

#行情静态属性
CUstpFtdcMarketDataStaticField = {}
#今开盘
CUstpFtdcMarketDataStaticField["OpenPrice"] = "float"
#最高价
CUstpFtdcMarketDataStaticField["HighestPrice"] = "float"
#最低价
CUstpFtdcMarketDataStaticField["LowestPrice"] = "float"
#今收盘
CUstpFtdcMarketDataStaticField["ClosePrice"] = "float"
#涨停板价
CUstpFtdcMarketDataStaticField["UpperLimitPrice"] = "float"
#跌停板价
CUstpFtdcMarketDataStaticField["LowerLimitPrice"] = "float"
#今结算
CUstpFtdcMarketDataStaticField["SettlementPrice"] = "float"
#今虚实度
CUstpFtdcMarketDataStaticField["CurrDelta"] = "float"
structDict['CUstpFtdcMarketDataStaticField'] = CUstpFtdcMarketDataStaticField

#行情最新成交属性
CUstpFtdcMarketDataLastMatchField = {}
#最新价
CUstpFtdcMarketDataLastMatchField["LastPrice"] = "float"
#数量
CUstpFtdcMarketDataLastMatchField["Volume"] = "int"
#成交金额
CUstpFtdcMarketDataLastMatchField["Turnover"] = "float"
#持仓量
CUstpFtdcMarketDataLastMatchField["OpenInterest"] = "float"
structDict['CUstpFtdcMarketDataLastMatchField'] = CUstpFtdcMarketDataLastMatchField

#行情最优价属性
CUstpFtdcMarketDataBestPriceField = {}
#申买价一
CUstpFtdcMarketDataBestPriceField["BidPrice1"] = "float"
#申买量一
CUstpFtdcMarketDataBestPriceField["BidVolume1"] = "int"
#申卖价一
CUstpFtdcMarketDataBestPriceField["AskPrice1"] = "float"
#申卖量一
CUstpFtdcMarketDataBestPriceField["AskVolume1"] = "int"
structDict['CUstpFtdcMarketDataBestPriceField'] = CUstpFtdcMarketDataBestPriceField

#行情申买二、三属性
CUstpFtdcMarketDataBid23Field = {}
#申买价二
CUstpFtdcMarketDataBid23Field["BidPrice2"] = "float"
#申买量二
CUstpFtdcMarketDataBid23Field["BidVolume2"] = "int"
#申买价三
CUstpFtdcMarketDataBid23Field["BidPrice3"] = "float"
#申买量三
CUstpFtdcMarketDataBid23Field["BidVolume3"] = "int"
structDict['CUstpFtdcMarketDataBid23Field'] = CUstpFtdcMarketDataBid23Field

#行情申卖二、三属性
CUstpFtdcMarketDataAsk23Field = {}
#申卖价二
CUstpFtdcMarketDataAsk23Field["AskPrice2"] = "float"
#申卖量二
CUstpFtdcMarketDataAsk23Field["AskVolume2"] = "int"
#申卖价三
CUstpFtdcMarketDataAsk23Field["AskPrice3"] = "float"
#申卖量三
CUstpFtdcMarketDataAsk23Field["AskVolume3"] = "int"
structDict['CUstpFtdcMarketDataAsk23Field'] = CUstpFtdcMarketDataAsk23Field

#行情申买四、五属性
CUstpFtdcMarketDataBid45Field = {}
#申买价四
CUstpFtdcMarketDataBid45Field["BidPrice4"] = "float"
#申买量四
CUstpFtdcMarketDataBid45Field["BidVolume4"] = "int"
#申买价五
CUstpFtdcMarketDataBid45Field["BidPrice5"] = "float"
#申买量五
CUstpFtdcMarketDataBid45Field["BidVolume5"] = "int"
structDict['CUstpFtdcMarketDataBid45Field'] = CUstpFtdcMarketDataBid45Field

#行情申卖四、五属性
CUstpFtdcMarketDataAsk45Field = {}
#申卖价四
CUstpFtdcMarketDataAsk45Field["AskPrice4"] = "float"
#申卖量四
CUstpFtdcMarketDataAsk45Field["AskVolume4"] = "int"
#申卖价五
CUstpFtdcMarketDataAsk45Field["AskPrice5"] = "float"
#申卖量五
CUstpFtdcMarketDataAsk45Field["AskVolume5"] = "int"
structDict['CUstpFtdcMarketDataAsk45Field'] = CUstpFtdcMarketDataAsk45Field

#行情更新时间属性
CUstpFtdcMarketDataUpdateTimeField = {}
#合约代码
CUstpFtdcMarketDataUpdateTimeField["InstrumentID"] = "string"
#最后修改时间
CUstpFtdcMarketDataUpdateTimeField["UpdateTime"] = "string"
#最后修改毫秒
CUstpFtdcMarketDataUpdateTimeField["UpdateMillisec"] = "int"
structDict['CUstpFtdcMarketDataUpdateTimeField'] = CUstpFtdcMarketDataUpdateTimeField

#深度行情
CUstpFtdcDepthMarketDataField = {}
#交易日
CUstpFtdcDepthMarketDataField["TradingDay"] = "string"
#结算组代码
CUstpFtdcDepthMarketDataField["SettlementGroupID"] = "string"
#结算编号
CUstpFtdcDepthMarketDataField["SettlementID"] = "int"
#昨结算
CUstpFtdcDepthMarketDataField["PreSettlementPrice"] = "float"
#昨收盘
CUstpFtdcDepthMarketDataField["PreClosePrice"] = "float"
#昨持仓量
CUstpFtdcDepthMarketDataField["PreOpenInterest"] = "float"
#昨虚实度
CUstpFtdcDepthMarketDataField["PreDelta"] = "float"
#今开盘
CUstpFtdcDepthMarketDataField["OpenPrice"] = "float"
#最高价
CUstpFtdcDepthMarketDataField["HighestPrice"] = "float"
#最低价
CUstpFtdcDepthMarketDataField["LowestPrice"] = "float"
#今收盘
CUstpFtdcDepthMarketDataField["ClosePrice"] = "float"
#涨停板价
CUstpFtdcDepthMarketDataField["UpperLimitPrice"] = "float"
#跌停板价
CUstpFtdcDepthMarketDataField["LowerLimitPrice"] = "float"
#今结算
CUstpFtdcDepthMarketDataField["SettlementPrice"] = "float"
#今虚实度
CUstpFtdcDepthMarketDataField["CurrDelta"] = "float"
#最新价
CUstpFtdcDepthMarketDataField["LastPrice"] = "float"
#数量
CUstpFtdcDepthMarketDataField["Volume"] = "int"
#成交金额
CUstpFtdcDepthMarketDataField["Turnover"] = "float"
#持仓量
CUstpFtdcDepthMarketDataField["OpenInterest"] = "float"
#申买价一
CUstpFtdcDepthMarketDataField["BidPrice1"] = "float"
#申买量一
CUstpFtdcDepthMarketDataField["BidVolume1"] = "int"
#申卖价一
CUstpFtdcDepthMarketDataField["AskPrice1"] = "float"
#申卖量一
CUstpFtdcDepthMarketDataField["AskVolume1"] = "int"
#申买价二
CUstpFtdcDepthMarketDataField["BidPrice2"] = "float"
#申买量二
CUstpFtdcDepthMarketDataField["BidVolume2"] = "int"
#申买价三
CUstpFtdcDepthMarketDataField["BidPrice3"] = "float"
#申买量三
CUstpFtdcDepthMarketDataField["BidVolume3"] = "int"
#申卖价二
CUstpFtdcDepthMarketDataField["AskPrice2"] = "float"
#申卖量二
CUstpFtdcDepthMarketDataField["AskVolume2"] = "int"
#申卖价三
CUstpFtdcDepthMarketDataField["AskPrice3"] = "float"
#申卖量三
CUstpFtdcDepthMarketDataField["AskVolume3"] = "int"
#申买价四
CUstpFtdcDepthMarketDataField["BidPrice4"] = "float"
#申买量四
CUstpFtdcDepthMarketDataField["BidVolume4"] = "int"
#申买价五
CUstpFtdcDepthMarketDataField["BidPrice5"] = "float"
#申买量五
CUstpFtdcDepthMarketDataField["BidVolume5"] = "int"
#申卖价四
CUstpFtdcDepthMarketDataField["AskPrice4"] = "float"
#申卖量四
CUstpFtdcDepthMarketDataField["AskVolume4"] = "int"
#申卖价五
CUstpFtdcDepthMarketDataField["AskPrice5"] = "float"
#申卖量五
CUstpFtdcDepthMarketDataField["AskVolume5"] = "int"
#合约代码
CUstpFtdcDepthMarketDataField["InstrumentID"] = "string"
#最后修改时间
CUstpFtdcDepthMarketDataField["UpdateTime"] = "string"
#最后修改毫秒
CUstpFtdcDepthMarketDataField["UpdateMillisec"] = "int"
structDict['CUstpFtdcDepthMarketDataField'] = CUstpFtdcDepthMarketDataField

#订阅合约的相关信息
CUstpFtdcSpecificInstrumentField = {}
#合约代码
CUstpFtdcSpecificInstrumentField["InstrumentID"] = "string"
structDict['CUstpFtdcSpecificInstrumentField'] = CUstpFtdcSpecificInstrumentField




