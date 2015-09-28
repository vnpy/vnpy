# encoding: UTF-8

structDict = {}

#//////////////////////////////////////////////////////////////////////
#@company shanghai liber information Technology Co.,Ltd
#@file SecurityFtdcUserApiStruct.h
#@brief 定义业务数据结构
#//////////////////////////////////////////////////////////////////////












#响应信息
CSecurityFtdcRspInfoField = {}
#错误代码
CSecurityFtdcRspInfoField["ErrorID"] = "int"
#错误信息
CSecurityFtdcRspInfoField["ErrorMsg"] = "string"
structDict['CSecurityFtdcRspInfoField'] = CSecurityFtdcRspInfoField


#交易所
CSecurityFtdcExchangeField = {}
#交易所代码
CSecurityFtdcExchangeField["ExchangeID"] = "string"
#交易所名称
CSecurityFtdcExchangeField["ExchangeName"] = "string"
#交易所属性
CSecurityFtdcExchangeField["ExchangeProperty"] = "string"
structDict['CSecurityFtdcExchangeField'] = CSecurityFtdcExchangeField


#产品
CSecurityFtdcProductField = {}
#产品代码
CSecurityFtdcProductField["ProductID"] = "string"
#产品名称
CSecurityFtdcProductField["ProductName"] = "string"
#交易所代码
CSecurityFtdcProductField["ExchangeID"] = "string"
#产品类型
CSecurityFtdcProductField["ProductClass"] = "string"
#合约数量乘数
CSecurityFtdcProductField["VolumeMultiple"] = "int"
#最小变动价位
CSecurityFtdcProductField["PriceTick"] = "float"
#市价单最大下单量
CSecurityFtdcProductField["MaxMarketOrderVolume"] = "int"
#市价单最小下单量
CSecurityFtdcProductField["MinMarketOrderVolume"] = "int"
#限价单最大下单量
CSecurityFtdcProductField["MaxLimitOrderVolume"] = "int"
#限价单最小下单量
CSecurityFtdcProductField["MinLimitOrderVolume"] = "int"
#持仓类型
CSecurityFtdcProductField["PositionType"] = "string"
#持仓日期类型
CSecurityFtdcProductField["PositionDateType"] = "string"
#ETF最小交易单位
CSecurityFtdcProductField["EFTMinTradeVolume"] = "int"
structDict['CSecurityFtdcProductField'] = CSecurityFtdcProductField


#合约
CSecurityFtdcInstrumentField = {}
#合约代码
CSecurityFtdcInstrumentField["InstrumentID"] = "string"
#交易所代码
CSecurityFtdcInstrumentField["ExchangeID"] = "string"
#合约名称
CSecurityFtdcInstrumentField["InstrumentName"] = "string"
#合约在交易所的代码
CSecurityFtdcInstrumentField["ExchangeInstID"] = "string"
#产品代码
CSecurityFtdcInstrumentField["ProductID"] = "string"
#产品类型
CSecurityFtdcInstrumentField["ProductClass"] = "string"
#交割年份
CSecurityFtdcInstrumentField["DeliveryYear"] = "int"
#交割月
CSecurityFtdcInstrumentField["DeliveryMonth"] = "int"
#市价单最大下单量
CSecurityFtdcInstrumentField["MaxMarketOrderVolume"] = "int"
#市价单最小下单量
CSecurityFtdcInstrumentField["MinMarketOrderVolume"] = "int"
#限价单最大下单量
CSecurityFtdcInstrumentField["MaxLimitOrderVolume"] = "int"
#限价单最小下单量
CSecurityFtdcInstrumentField["MinLimitOrderVolume"] = "int"
#合约数量乘数
CSecurityFtdcInstrumentField["VolumeMultiple"] = "int"
#最小变动价位
CSecurityFtdcInstrumentField["PriceTick"] = "float"
#创建日
CSecurityFtdcInstrumentField["CreateDate"] = "string"
#上市日
CSecurityFtdcInstrumentField["OpenDate"] = "string"
#到期日
CSecurityFtdcInstrumentField["ExpireDate"] = "string"
#开始交割日
CSecurityFtdcInstrumentField["StartDelivDate"] = "string"
#结束交割日
CSecurityFtdcInstrumentField["EndDelivDate"] = "string"
#合约生命周期状态
CSecurityFtdcInstrumentField["InstLifePhase"] = "string"
#当前是否交易
CSecurityFtdcInstrumentField["IsTrading"] = "int"
#持仓类型
CSecurityFtdcInstrumentField["PositionType"] = "string"
#报单能否撤单
CSecurityFtdcInstrumentField["OrderCanBeWithdraw"] = "int"
#最小买下单单位
CSecurityFtdcInstrumentField["MinBuyVolume"] = "int"
#最小卖下单单位
CSecurityFtdcInstrumentField["MinSellVolume"] = "int"
#股票权限模版代码
CSecurityFtdcInstrumentField["RightModelID"] = "string"
#持仓交易类型
CSecurityFtdcInstrumentField["PosTradeType"] = "string"
#市场代码
CSecurityFtdcInstrumentField["MarketID"] = "string"
#期权执行价格
CSecurityFtdcInstrumentField["ExecPrice"] = "float"
#期权单手保证金
CSecurityFtdcInstrumentField["UnitMargin"] = "float"
#合约类型
CSecurityFtdcInstrumentField["InstrumentType"] = "string"
#期权保证金参数1
CSecurityFtdcInstrumentField["OptionsMarginParam1"] = "float"
#期权保证金参数2
CSecurityFtdcInstrumentField["OptionsMarginParam2"] = "float"
structDict['CSecurityFtdcInstrumentField'] = CSecurityFtdcInstrumentField


#经纪公司
CSecurityFtdcBrokerField = {}
#经纪公司代码
CSecurityFtdcBrokerField["BrokerID"] = "string"
#经纪公司简称
CSecurityFtdcBrokerField["BrokerAbbr"] = "string"
#经纪公司名称
CSecurityFtdcBrokerField["BrokerName"] = "string"
#是否活跃
CSecurityFtdcBrokerField["IsActive"] = "int"
structDict['CSecurityFtdcBrokerField'] = CSecurityFtdcBrokerField


#会员编码和经纪公司编码对照表
CSecurityFtdcPartBrokerField = {}
#经纪公司代码
CSecurityFtdcPartBrokerField["BrokerID"] = "string"
#交易所代码
CSecurityFtdcPartBrokerField["ExchangeID"] = "string"
#会员代码
CSecurityFtdcPartBrokerField["ParticipantID"] = "string"
#是否活跃
CSecurityFtdcPartBrokerField["IsActive"] = "int"
structDict['CSecurityFtdcPartBrokerField'] = CSecurityFtdcPartBrokerField


#投资者
CSecurityFtdcInvestorField = {}
#投资者代码
CSecurityFtdcInvestorField["InvestorID"] = "string"
#经纪公司代码
CSecurityFtdcInvestorField["BrokerID"] = "string"
#投资者分组代码
CSecurityFtdcInvestorField["InvestorGroupID"] = "string"
#投资者名称
CSecurityFtdcInvestorField["InvestorName"] = "string"
#证件类型
CSecurityFtdcInvestorField["IdentifiedCardType"] = "string"
#证件号码
CSecurityFtdcInvestorField["IdentifiedCardNo"] = "string"
#是否活跃
CSecurityFtdcInvestorField["IsActive"] = "int"
#上海营业部编号
CSecurityFtdcInvestorField["SHBranchID"] = "string"
#深圳营业部编号
CSecurityFtdcInvestorField["SZBranchID"] = "string"
#所属结算系统类型
CSecurityFtdcInvestorField["SettleSystemType"] = "string"
#投资者期权交易等级
CSecurityFtdcInvestorField["InvestorLevel"] = "string"
structDict['CSecurityFtdcInvestorField'] = CSecurityFtdcInvestorField


#交易编码
CSecurityFtdcTradingCodeField = {}
#投资者代码
CSecurityFtdcTradingCodeField["InvestorID"] = "string"
#经纪公司代码
CSecurityFtdcTradingCodeField["BrokerID"] = "string"
#交易所代码
CSecurityFtdcTradingCodeField["ExchangeID"] = "string"
#客户代码
CSecurityFtdcTradingCodeField["ClientID"] = "string"
#是否活跃
CSecurityFtdcTradingCodeField["IsActive"] = "int"
#AccountID
CSecurityFtdcTradingCodeField["AccountID"] = "string"
#交易单元号
CSecurityFtdcTradingCodeField["PBU"] = "string"
#ClientType
CSecurityFtdcTradingCodeField["ClientType"] = "string"
structDict['CSecurityFtdcTradingCodeField'] = CSecurityFtdcTradingCodeField


#管理用户
CSecurityFtdcSuperUserField = {}
#用户代码
CSecurityFtdcSuperUserField["UserID"] = "string"
#用户名称
CSecurityFtdcSuperUserField["UserName"] = "string"
#密码
CSecurityFtdcSuperUserField["Password"] = "string"
#是否活跃
CSecurityFtdcSuperUserField["IsActive"] = "int"
structDict['CSecurityFtdcSuperUserField'] = CSecurityFtdcSuperUserField


#管理用户功能权限
CSecurityFtdcSuperUserFunctionField = {}
#用户代码
CSecurityFtdcSuperUserFunctionField["UserID"] = "string"
#功能代码
CSecurityFtdcSuperUserFunctionField["FunctionCode"] = "string"
structDict['CSecurityFtdcSuperUserFunctionField'] = CSecurityFtdcSuperUserFunctionField


#经纪公司用户
CSecurityFtdcBrokerUserField = {}
#经纪公司代码
CSecurityFtdcBrokerUserField["BrokerID"] = "string"
#用户代码
CSecurityFtdcBrokerUserField["UserID"] = "string"
#用户名称
CSecurityFtdcBrokerUserField["UserName"] = "string"
#用户类型
CSecurityFtdcBrokerUserField["UserType"] = "string"
#是否活跃
CSecurityFtdcBrokerUserField["IsActive"] = "int"
#是否使用令牌
CSecurityFtdcBrokerUserField["IsUsingOTP"] = "int"
structDict['CSecurityFtdcBrokerUserField'] = CSecurityFtdcBrokerUserField


#经纪公司用户功能权限
CSecurityFtdcBrokerUserFunctionField = {}
#经纪公司代码
CSecurityFtdcBrokerUserFunctionField["BrokerID"] = "string"
#用户代码
CSecurityFtdcBrokerUserFunctionField["UserID"] = "string"
#经纪公司功能代码
CSecurityFtdcBrokerUserFunctionField["BrokerFunctionCode"] = "string"
structDict['CSecurityFtdcBrokerUserFunctionField'] = CSecurityFtdcBrokerUserFunctionField


#资金账户
CSecurityFtdcTradingAccountField = {}
#经纪公司代码
CSecurityFtdcTradingAccountField["BrokerID"] = "string"
#投资者帐号
CSecurityFtdcTradingAccountField["AccountID"] = "string"
#上次质押金额
CSecurityFtdcTradingAccountField["PreMortgage"] = "float"
#上次信用额度
CSecurityFtdcTradingAccountField["PreCredit"] = "float"
#上次存款额
CSecurityFtdcTradingAccountField["PreDeposit"] = "float"
#上次结算准备金
CSecurityFtdcTradingAccountField["PreBalance"] = "float"
#上次占用的保证金
CSecurityFtdcTradingAccountField["PreMargin"] = "float"
#利息基数
CSecurityFtdcTradingAccountField["InterestBase"] = "float"
#利息收入
CSecurityFtdcTradingAccountField["Interest"] = "float"
#入金金额
CSecurityFtdcTradingAccountField["Deposit"] = "float"
#出金金额
CSecurityFtdcTradingAccountField["Withdraw"] = "float"
#冻结的保证金
CSecurityFtdcTradingAccountField["FrozenMargin"] = "float"
#冻结的资金
CSecurityFtdcTradingAccountField["FrozenCash"] = "float"
#冻结的手续费
CSecurityFtdcTradingAccountField["FrozenCommission"] = "float"
#当前保证金总额
CSecurityFtdcTradingAccountField["CurrMargin"] = "float"
#资金差额
CSecurityFtdcTradingAccountField["CashIn"] = "float"
#手续费
CSecurityFtdcTradingAccountField["Commission"] = "float"
#结算准备金
CSecurityFtdcTradingAccountField["Balance"] = "float"
#现金
CSecurityFtdcTradingAccountField["Available"] = "float"
#可取资金
CSecurityFtdcTradingAccountField["WithdrawQuota"] = "float"
#基本准备金
CSecurityFtdcTradingAccountField["Reserve"] = "float"
#交易日
CSecurityFtdcTradingAccountField["TradingDay"] = "string"
#保证金可用余额
CSecurityFtdcTradingAccountField["Credit"] = "float"
#质押金额
CSecurityFtdcTradingAccountField["Mortgage"] = "float"
#交易所保证金
CSecurityFtdcTradingAccountField["ExchangeMargin"] = "float"
#投资者交割保证金
CSecurityFtdcTradingAccountField["DeliveryMargin"] = "float"
#交易所交割保证金
CSecurityFtdcTradingAccountField["ExchangeDeliveryMargin"] = "float"
#冻结的过户费
CSecurityFtdcTradingAccountField["FrozenTransferFee"] = "float"
#冻结的印花税
CSecurityFtdcTradingAccountField["FrozenStampTax"] = "float"
#过户费
CSecurityFtdcTradingAccountField["TransferFee"] = "float"
#印花税
CSecurityFtdcTradingAccountField["StampTax"] = "float"
#折算金额
CSecurityFtdcTradingAccountField["ConversionAmount"] = "float"
#授信额度
CSecurityFtdcTradingAccountField["CreditAmount"] = "float"
#证券总价值
CSecurityFtdcTradingAccountField["StockValue"] = "float"
#国债回购占用资金
CSecurityFtdcTradingAccountField["BondRepurchaseAmount"] = "float"
#国债逆回购占用资金
CSecurityFtdcTradingAccountField["ReverseRepurchaseAmount"] = "float"
#币种
CSecurityFtdcTradingAccountField["CurrencyCode"] = "string"
#账户类型
CSecurityFtdcTradingAccountField["AccountType"] = "string"
#融资买入金额
CSecurityFtdcTradingAccountField["MarginTradeAmount"] = "float"
#融券卖出金额
CSecurityFtdcTradingAccountField["ShortSellAmount"] = "float"
#融资持仓盈亏
CSecurityFtdcTradingAccountField["MarginTradeProfit"] = "float"
#融券持仓盈亏
CSecurityFtdcTradingAccountField["ShortSellProfit"] = "float"
#融券总市值
CSecurityFtdcTradingAccountField["SSStockValue"] = "float"
#维持担保比例
CSecurityFtdcTradingAccountField["CreditRatio"] = "float"
#行权冻结资金
CSecurityFtdcTradingAccountField["FrozenExecCash"] = "float"
#期权买入资金(SSE)
CSecurityFtdcTradingAccountField["SSEOptionsBuyAmount"] = "float"
#期权买入冻结资金(SSE)
CSecurityFtdcTradingAccountField["SSEOptionsBuyFrozenAmount"] = "float"
#结算保证金总额
CSecurityFtdcTradingAccountField["SettleMargin"] = "float"
structDict['CSecurityFtdcTradingAccountField'] = CSecurityFtdcTradingAccountField


#禁止登录用户
CSecurityFtdcLoginForbiddenUserField = {}
#经纪公司代码
CSecurityFtdcLoginForbiddenUserField["BrokerID"] = "string"
#用户代码
CSecurityFtdcLoginForbiddenUserField["UserID"] = "string"
structDict['CSecurityFtdcLoginForbiddenUserField'] = CSecurityFtdcLoginForbiddenUserField


#深度行情
CSecurityFtdcDepthMarketDataField = {}
#交易日
CSecurityFtdcDepthMarketDataField["TradingDay"] = "string"
#合约代码
CSecurityFtdcDepthMarketDataField["InstrumentID"] = "string"
#交易所代码
CSecurityFtdcDepthMarketDataField["ExchangeID"] = "string"
#合约在交易所的代码
CSecurityFtdcDepthMarketDataField["ExchangeInstID"] = "string"
#最新价
CSecurityFtdcDepthMarketDataField["LastPrice"] = "float"
#上次结算价
CSecurityFtdcDepthMarketDataField["PreSettlementPrice"] = "float"
#昨收盘
CSecurityFtdcDepthMarketDataField["PreClosePrice"] = "float"
#昨持仓量
CSecurityFtdcDepthMarketDataField["PreOpenInterest"] = "float"
#今开盘
CSecurityFtdcDepthMarketDataField["OpenPrice"] = "float"
#最高价
CSecurityFtdcDepthMarketDataField["HighestPrice"] = "float"
#最低价
CSecurityFtdcDepthMarketDataField["LowestPrice"] = "float"
#数量
CSecurityFtdcDepthMarketDataField["Volume"] = "float"
#成交金额
CSecurityFtdcDepthMarketDataField["Turnover"] = "float"
#持仓量
CSecurityFtdcDepthMarketDataField["OpenInterest"] = "float"
#今收盘
CSecurityFtdcDepthMarketDataField["ClosePrice"] = "float"
#本次结算价
CSecurityFtdcDepthMarketDataField["SettlementPrice"] = "float"
#涨停板价
CSecurityFtdcDepthMarketDataField["UpperLimitPrice"] = "float"
#跌停板价
CSecurityFtdcDepthMarketDataField["LowerLimitPrice"] = "float"
#昨虚实度
CSecurityFtdcDepthMarketDataField["PreDelta"] = "float"
#今虚实度
CSecurityFtdcDepthMarketDataField["CurrDelta"] = "float"
#昨日基金净值
CSecurityFtdcDepthMarketDataField["PreIOPV"] = "float"
#基金净值
CSecurityFtdcDepthMarketDataField["IOPV"] = "float"
#动态参考价格
CSecurityFtdcDepthMarketDataField["AuctionPrice"] = "float"
#最后修改时间
CSecurityFtdcDepthMarketDataField["UpdateTime"] = "string"
#最后修改毫秒
CSecurityFtdcDepthMarketDataField["UpdateMillisec"] = "int"
#申买价一
CSecurityFtdcDepthMarketDataField["BidPrice1"] = "float"
#申买量一
CSecurityFtdcDepthMarketDataField["BidVolume1"] = "float"
#申卖价一
CSecurityFtdcDepthMarketDataField["AskPrice1"] = "float"
#申卖量一
CSecurityFtdcDepthMarketDataField["AskVolume1"] = "float"
#申买价二
CSecurityFtdcDepthMarketDataField["BidPrice2"] = "float"
#申买量二
CSecurityFtdcDepthMarketDataField["BidVolume2"] = "float"
#申卖价二
CSecurityFtdcDepthMarketDataField["AskPrice2"] = "float"
#申卖量二
CSecurityFtdcDepthMarketDataField["AskVolume2"] = "float"
#申买价三
CSecurityFtdcDepthMarketDataField["BidPrice3"] = "float"
#申买量三
CSecurityFtdcDepthMarketDataField["BidVolume3"] = "float"
#申卖价三
CSecurityFtdcDepthMarketDataField["AskPrice3"] = "float"
#申卖量三
CSecurityFtdcDepthMarketDataField["AskVolume3"] = "float"
#申买价四
CSecurityFtdcDepthMarketDataField["BidPrice4"] = "float"
#申买量四
CSecurityFtdcDepthMarketDataField["BidVolume4"] = "float"
#申卖价四
CSecurityFtdcDepthMarketDataField["AskPrice4"] = "float"
#申卖量四
CSecurityFtdcDepthMarketDataField["AskVolume4"] = "float"
#申买价五
CSecurityFtdcDepthMarketDataField["BidPrice5"] = "float"
#申买量五
CSecurityFtdcDepthMarketDataField["BidVolume5"] = "float"
#申卖价五
CSecurityFtdcDepthMarketDataField["AskPrice5"] = "float"
#申卖量五
CSecurityFtdcDepthMarketDataField["AskVolume5"] = "float"
#当日均价
CSecurityFtdcDepthMarketDataField["AveragePrice"] = "float"
#业务日期
CSecurityFtdcDepthMarketDataField["ActionDay"] = "string"
#交易阶段
CSecurityFtdcDepthMarketDataField["TradingPhase"] = "string"
#开仓限制
CSecurityFtdcDepthMarketDataField["OpenRestriction"] = "string"
structDict['CSecurityFtdcDepthMarketDataField'] = CSecurityFtdcDepthMarketDataField


#投资者合约交易权限
CSecurityFtdcInstrumentTradingRightField = {}
#合约代码
CSecurityFtdcInstrumentTradingRightField["InstrumentID"] = "string"
#投资者范围
CSecurityFtdcInstrumentTradingRightField["InvestorRange"] = "string"
#经纪公司代码
CSecurityFtdcInstrumentTradingRightField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcInstrumentTradingRightField["InvestorID"] = "string"
#买卖
CSecurityFtdcInstrumentTradingRightField["Direction"] = "string"
#交易权限
CSecurityFtdcInstrumentTradingRightField["TradingRight"] = "string"
#交易所代码
CSecurityFtdcInstrumentTradingRightField["ExchangeID"] = "string"
#股票权限分类
CSecurityFtdcInstrumentTradingRightField["InstrumentRange"] = "string"
structDict['CSecurityFtdcInstrumentTradingRightField'] = CSecurityFtdcInstrumentTradingRightField


#投资者持仓明细
CSecurityFtdcInvestorPositionDetailField = {}
#合约代码
CSecurityFtdcInvestorPositionDetailField["InstrumentID"] = "string"
#经纪公司代码
CSecurityFtdcInvestorPositionDetailField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcInvestorPositionDetailField["InvestorID"] = "string"
#投机套保标志
CSecurityFtdcInvestorPositionDetailField["HedgeFlag"] = "string"
#买卖
CSecurityFtdcInvestorPositionDetailField["Direction"] = "string"
#开仓日期
CSecurityFtdcInvestorPositionDetailField["OpenDate"] = "string"
#成交编号
CSecurityFtdcInvestorPositionDetailField["TradeID"] = "string"
#数量
CSecurityFtdcInvestorPositionDetailField["Volume"] = "float"
#开仓价
CSecurityFtdcInvestorPositionDetailField["OpenPrice"] = "float"
#交易日
CSecurityFtdcInvestorPositionDetailField["TradingDay"] = "string"
#成交类型
CSecurityFtdcInvestorPositionDetailField["TradeType"] = "string"
#交易所代码
CSecurityFtdcInvestorPositionDetailField["ExchangeID"] = "string"
#投资者保证金
CSecurityFtdcInvestorPositionDetailField["Margin"] = "float"
#交易所保证金
CSecurityFtdcInvestorPositionDetailField["ExchMargin"] = "float"
#昨结算价
CSecurityFtdcInvestorPositionDetailField["LastSettlementPrice"] = "float"
#结算价
CSecurityFtdcInvestorPositionDetailField["SettlementPrice"] = "float"
#平仓量
CSecurityFtdcInvestorPositionDetailField["CloseVolume"] = "float"
#平仓金额
CSecurityFtdcInvestorPositionDetailField["CloseAmount"] = "float"
#过户费
CSecurityFtdcInvestorPositionDetailField["TransferFee"] = "float"
#印花税
CSecurityFtdcInvestorPositionDetailField["StampTax"] = "float"
#手续费
CSecurityFtdcInvestorPositionDetailField["Commission"] = "float"
#AccountID
CSecurityFtdcInvestorPositionDetailField["AccountID"] = "string"
#质押入库数量
CSecurityFtdcInvestorPositionDetailField["PledgeInPosition"] = "float"
#质押入库冻结数量
CSecurityFtdcInvestorPositionDetailField["PledgeInFrozenPosition"] = "float"
#正回购使用的标准券数量
CSecurityFtdcInvestorPositionDetailField["RepurchasePosition"] = "float"
#融资融券金额
CSecurityFtdcInvestorPositionDetailField["Amount"] = "float"
#标的合约代码
CSecurityFtdcInvestorPositionDetailField["UnderlyingInstrumentID"] = "string"
structDict['CSecurityFtdcInvestorPositionDetailField'] = CSecurityFtdcInvestorPositionDetailField


#债券利息
CSecurityFtdcBondInterestField = {}
#交易日
CSecurityFtdcBondInterestField["TradingDay"] = "string"
#交易所代码
CSecurityFtdcBondInterestField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcBondInterestField["InstrumentID"] = "string"
#利息
CSecurityFtdcBondInterestField["Interest"] = "float"
structDict['CSecurityFtdcBondInterestField'] = CSecurityFtdcBondInterestField


#市值配售信息
CSecurityFtdcMarketRationInfoField = {}
#经纪公司代码
CSecurityFtdcMarketRationInfoField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcMarketRationInfoField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcMarketRationInfoField["ExchangeID"] = "string"
#可配售数量
CSecurityFtdcMarketRationInfoField["RationVolume"] = "float"
structDict['CSecurityFtdcMarketRationInfoField'] = CSecurityFtdcMarketRationInfoField


#合约手续费率
CSecurityFtdcInstrumentCommissionRateField = {}
#交易所代码
CSecurityFtdcInstrumentCommissionRateField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcInstrumentCommissionRateField["InstrumentID"] = "string"
#投资者范围
CSecurityFtdcInstrumentCommissionRateField["InvestorRange"] = "string"
#经纪公司代码
CSecurityFtdcInstrumentCommissionRateField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcInstrumentCommissionRateField["InvestorID"] = "string"
#买卖方向
CSecurityFtdcInstrumentCommissionRateField["Direction"] = "string"
#印花税率
CSecurityFtdcInstrumentCommissionRateField["StampTaxRateByMoney"] = "float"
#印花税率(按手数)
CSecurityFtdcInstrumentCommissionRateField["StampTaxRateByVolume"] = "float"
#过户费率
CSecurityFtdcInstrumentCommissionRateField["TransferFeeRateByMoney"] = "float"
#过户费率(按手数)
CSecurityFtdcInstrumentCommissionRateField["TransferFeeRateByVolume"] = "float"
#交易费
CSecurityFtdcInstrumentCommissionRateField["TradeFeeByMoney"] = "float"
#交易费(按手数)
CSecurityFtdcInstrumentCommissionRateField["TradeFeeByVolume"] = "float"
#交易附加费率
CSecurityFtdcInstrumentCommissionRateField["MarginByMoney"] = "float"
#最小交易费
CSecurityFtdcInstrumentCommissionRateField["MinTradeFee"] = "float"
#最小过户费
CSecurityFtdcInstrumentCommissionRateField["MinTransferFee"] = "float"
structDict['CSecurityFtdcInstrumentCommissionRateField'] = CSecurityFtdcInstrumentCommissionRateField


#余券信息
CSecurityFtdcExcessStockInfoField = {}
#经纪公司代码
CSecurityFtdcExcessStockInfoField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcExcessStockInfoField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcExcessStockInfoField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcExcessStockInfoField["InstrumentID"] = "string"
#余券数量
CSecurityFtdcExcessStockInfoField["ExcessVolume"] = "float"
#余券冻结数量
CSecurityFtdcExcessStockInfoField["ExcessFrozenVolume"] = "float"
structDict['CSecurityFtdcExcessStockInfoField'] = CSecurityFtdcExcessStockInfoField


#ETF合约
CSecurityFtdcETFInstrumentField = {}
#交易所代码
CSecurityFtdcETFInstrumentField["ExchangeID"] = "string"
#ETF证券代码
CSecurityFtdcETFInstrumentField["ETFInstrumentID"] = "string"
#ETF对应申赎代码
CSecurityFtdcETFInstrumentField["ETFPurRedInstrumentID"] = "string"
#最小申购赎回单位对应的ETF份数
CSecurityFtdcETFInstrumentField["CreationRedemptionUnit"] = "int"
#最大现金替代比例
CSecurityFtdcETFInstrumentField["Maxcashratio"] = "float"
#基金当天申购赎回状态
CSecurityFtdcETFInstrumentField["Creationredemption"] = "string"
#预估金额
CSecurityFtdcETFInstrumentField["EstimateCashComponent"] = "float"
#基金申赎单位净值
CSecurityFtdcETFInstrumentField["ETFNetValue"] = "float"
#基金类别
CSecurityFtdcETFInstrumentField["FundClass"] = "string"
structDict['CSecurityFtdcETFInstrumentField'] = CSecurityFtdcETFInstrumentField


#ETF股票篮
CSecurityFtdcETFBasketField = {}
#交易所代码
CSecurityFtdcETFBasketField["ExchangeID"] = "string"
#ETF证券代码
CSecurityFtdcETFBasketField["ETFInstrumentID"] = "string"
#股票证券代码
CSecurityFtdcETFBasketField["StockInstrumentID"] = "string"
#股票证券名称
CSecurityFtdcETFBasketField["StockInstrumentName"] = "string"
#股票数量
CSecurityFtdcETFBasketField["Volume"] = "int"
#替代标志
CSecurityFtdcETFBasketField["CurrenceReplaceStatus"] = "string"
#溢价比例
CSecurityFtdcETFBasketField["Premium"] = "float"
#总金额
CSecurityFtdcETFBasketField["Amount"] = "float"
structDict['CSecurityFtdcETFBasketField'] = CSecurityFtdcETFBasketField


#OF合约
CSecurityFtdcOFInstrumentField = {}
#交易所代码
CSecurityFtdcOFInstrumentField["ExchangeID"] = "string"
#OF基金代码
CSecurityFtdcOFInstrumentField["InstrumentID"] = "string"
#基金当天申购赎回状态
CSecurityFtdcOFInstrumentField["Creationredemption"] = "string"
#基金净值
CSecurityFtdcOFInstrumentField["NetPrice"] = "float"
#基金类别
CSecurityFtdcOFInstrumentField["FundClass"] = "string"
structDict['CSecurityFtdcOFInstrumentField'] = CSecurityFtdcOFInstrumentField


#SF合约
CSecurityFtdcSFInstrumentField = {}
#交易所代码
CSecurityFtdcSFInstrumentField["ExchangeID"] = "string"
#基金代码
CSecurityFtdcSFInstrumentField["InstrumentID"] = "string"
#SF基金代码
CSecurityFtdcSFInstrumentField["SFInstrumentID"] = "string"
#基金当天拆分合并状态
CSecurityFtdcSFInstrumentField["SplitMergeStatus"] = "string"
#最小拆分数量
CSecurityFtdcSFInstrumentField["MinSplitVolume"] = "int"
#最小合并数量
CSecurityFtdcSFInstrumentField["MinMergeVolume"] = "int"
#拆分/合并比例
CSecurityFtdcSFInstrumentField["VolumeRatio"] = "int"
#基金净值
CSecurityFtdcSFInstrumentField["NetPrice"] = "float"
structDict['CSecurityFtdcSFInstrumentField'] = CSecurityFtdcSFInstrumentField


#合约单手保证金
CSecurityFtdcInstrumentUnitMarginField = {}
#经纪公司代码
CSecurityFtdcInstrumentUnitMarginField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcInstrumentUnitMarginField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcInstrumentUnitMarginField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcInstrumentUnitMarginField["InstrumentID"] = "string"
#合约单手保证金
CSecurityFtdcInstrumentUnitMarginField["UnitMargin"] = "float"
structDict['CSecurityFtdcInstrumentUnitMarginField'] = CSecurityFtdcInstrumentUnitMarginField


#期权资金限制参数
CSecurityFtdcOptionsFundLimitParamField = {}
#经纪公司代码
CSecurityFtdcOptionsFundLimitParamField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcOptionsFundLimitParamField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcOptionsFundLimitParamField["ExchangeID"] = "string"
#最大可买金额
CSecurityFtdcOptionsFundLimitParamField["MaxBuyAmount"] = "float"
structDict['CSecurityFtdcOptionsFundLimitParamField'] = CSecurityFtdcOptionsFundLimitParamField


#投资者期权持仓
CSecurityFtdcInvestorOptionsPositionField = {}
#经纪公司代码
CSecurityFtdcInvestorOptionsPositionField["BrokerID"] = "string"
#投资者范围
CSecurityFtdcInvestorOptionsPositionField["InvestorRange"] = "string"
#投资者代码
CSecurityFtdcInvestorOptionsPositionField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcInvestorOptionsPositionField["ExchangeID"] = "string"
#InstrumentID
CSecurityFtdcInvestorOptionsPositionField["InstrumentID"] = "string"
#最大多头仓位限制
CSecurityFtdcInvestorOptionsPositionField["MaxLongPositionLimit"] = "float"
#最大买开量限制
CSecurityFtdcInvestorOptionsPositionField["MaxBuyVolLimit"] = "float"
#最大总仓位限制
CSecurityFtdcInvestorOptionsPositionField["MaxPositionLimit"] = "float"
#多头持仓
CSecurityFtdcInvestorOptionsPositionField["LongPosition"] = "float"
#空头持仓
CSecurityFtdcInvestorOptionsPositionField["ShortPosition"] = "float"
#买开量
CSecurityFtdcInvestorOptionsPositionField["BuyVolume"] = "float"
#买开冻结量
CSecurityFtdcInvestorOptionsPositionField["BuyFrozenVolume"] = "float"
#多头冻结持仓
CSecurityFtdcInvestorOptionsPositionField["LongFrozenPosition"] = "float"
#空头冻结持仓
CSecurityFtdcInvestorOptionsPositionField["ShortFrozenPosition"] = "float"
structDict['CSecurityFtdcInvestorOptionsPositionField'] = CSecurityFtdcInvestorOptionsPositionField


#预交割信息
CSecurityFtdcPreDelivInfoField = {}
#经纪公司代码
CSecurityFtdcPreDelivInfoField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcPreDelivInfoField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcPreDelivInfoField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcPreDelivInfoField["InstrumentID"] = "string"
#交割类型
CSecurityFtdcPreDelivInfoField["DelivType"] = "string"
#标的合约代码
CSecurityFtdcPreDelivInfoField["UnderlyingInstrumentID"] = "string"
#交割数量
CSecurityFtdcPreDelivInfoField["DelivVolume"] = "float"
#交割金额
CSecurityFtdcPreDelivInfoField["DelivAmount"] = "float"
#期权执行数量
CSecurityFtdcPreDelivInfoField["ExecVolume"] = "float"
#买卖方向
CSecurityFtdcPreDelivInfoField["Direction"] = "string"
structDict['CSecurityFtdcPreDelivInfoField'] = CSecurityFtdcPreDelivInfoField


#可融券分配信息
CSecurityFtdcCreditStockAssignInfoField = {}
#经纪公司代码
CSecurityFtdcCreditStockAssignInfoField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcCreditStockAssignInfoField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcCreditStockAssignInfoField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcCreditStockAssignInfoField["InstrumentID"] = "string"
#融券限量
CSecurityFtdcCreditStockAssignInfoField["LimitVolume"] = "float"
#上日融券数量
CSecurityFtdcCreditStockAssignInfoField["YDVolume"] = "float"
#剩余可融券数量
CSecurityFtdcCreditStockAssignInfoField["LeftVolume"] = "float"
#冻结融券数量
CSecurityFtdcCreditStockAssignInfoField["FrozenVolume"] = "float"
structDict['CSecurityFtdcCreditStockAssignInfoField'] = CSecurityFtdcCreditStockAssignInfoField


#可融资分配信息
CSecurityFtdcCreditCashAssignInfoField = {}
#经纪公司代码
CSecurityFtdcCreditCashAssignInfoField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcCreditCashAssignInfoField["InvestorID"] = "string"
#融资限额
CSecurityFtdcCreditCashAssignInfoField["LimitAmount"] = "float"
#上日融资金额
CSecurityFtdcCreditCashAssignInfoField["YDAmount"] = "float"
structDict['CSecurityFtdcCreditCashAssignInfoField'] = CSecurityFtdcCreditCashAssignInfoField


#证券折算率
CSecurityFtdcConversionRateField = {}
#交易所代码
CSecurityFtdcConversionRateField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcConversionRateField["InstrumentID"] = "string"
#折算比率
CSecurityFtdcConversionRateField["ConversionRate"] = "float"
#当前是否支持融资交易
CSecurityFtdcConversionRateField["IsTradingForMargin"] = "int"
#当前是否支持融券交易
CSecurityFtdcConversionRateField["IsTradingForShort"] = "int"
structDict['CSecurityFtdcConversionRateField'] = CSecurityFtdcConversionRateField


#历史信用负债信息
CSecurityFtdcHisCreditDebtInfoField = {}
#经纪公司代码
CSecurityFtdcHisCreditDebtInfoField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcHisCreditDebtInfoField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcHisCreditDebtInfoField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcHisCreditDebtInfoField["InstrumentID"] = "string"
#开仓日期
CSecurityFtdcHisCreditDebtInfoField["OpenDate"] = "string"
#负债类型
CSecurityFtdcHisCreditDebtInfoField["Direction"] = "string"
#开仓价
CSecurityFtdcHisCreditDebtInfoField["OpenPrice"] = "float"
#数量
CSecurityFtdcHisCreditDebtInfoField["Volume"] = "float"
#融资融券金额
CSecurityFtdcHisCreditDebtInfoField["Amount"] = "float"
structDict['CSecurityFtdcHisCreditDebtInfoField'] = CSecurityFtdcHisCreditDebtInfoField


#行情静态信息
CSecurityFtdcMarketDataStaticInfoField = {}
#交易所代码
CSecurityFtdcMarketDataStaticInfoField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcMarketDataStaticInfoField["InstrumentID"] = "string"
#涨停板价
CSecurityFtdcMarketDataStaticInfoField["UpperLimitPrice"] = "float"
#跌停板价
CSecurityFtdcMarketDataStaticInfoField["LowerLimitPrice"] = "float"
#昨结算
CSecurityFtdcMarketDataStaticInfoField["PreSettlementPrice"] = "float"
#昨收盘
CSecurityFtdcMarketDataStaticInfoField["PreClosePrice"] = "float"
#昨日基金净值
CSecurityFtdcMarketDataStaticInfoField["PreIOPV"] = "float"
#是否非交易业务
CSecurityFtdcMarketDataStaticInfoField["IsNotTrade"] = "int"
structDict['CSecurityFtdcMarketDataStaticInfoField'] = CSecurityFtdcMarketDataStaticInfoField


#到期回购信息
CSecurityFtdcExpireRepurchInfoField = {}
#经纪公司代码
CSecurityFtdcExpireRepurchInfoField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcExpireRepurchInfoField["InvestorID"] = "string"
#资金账户代码
CSecurityFtdcExpireRepurchInfoField["AccountID"] = "string"
#到期类型
CSecurityFtdcExpireRepurchInfoField["ExpireType"] = "string"
#交易所代码
CSecurityFtdcExpireRepurchInfoField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcExpireRepurchInfoField["InstrumentID"] = "string"
#数量
CSecurityFtdcExpireRepurchInfoField["Volume"] = "float"
#金额
CSecurityFtdcExpireRepurchInfoField["Amount"] = "float"
#利息
CSecurityFtdcExpireRepurchInfoField["Interest"] = "float"
structDict['CSecurityFtdcExpireRepurchInfoField'] = CSecurityFtdcExpireRepurchInfoField


#债券质押为标准券比例
CSecurityFtdcBondPledgeRateField = {}
#交易所代码
CSecurityFtdcBondPledgeRateField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcBondPledgeRateField["InstrumentID"] = "string"
#折算比率
CSecurityFtdcBondPledgeRateField["Ratio"] = "float"
structDict['CSecurityFtdcBondPledgeRateField'] = CSecurityFtdcBondPledgeRateField


#债券质押代码对照关系
CSecurityFtdcPledgeBondField = {}
#交易所代码
CSecurityFtdcPledgeBondField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcPledgeBondField["InstrumentID"] = "string"
#质押代码
CSecurityFtdcPledgeBondField["PledgeID"] = "string"
structDict['CSecurityFtdcPledgeBondField'] = CSecurityFtdcPledgeBondField


#交易所交易员报盘机
CSecurityFtdcTraderOfferField = {}
#交易所代码
CSecurityFtdcTraderOfferField["ExchangeID"] = "string"
#交易所交易员代码
CSecurityFtdcTraderOfferField["BranchPBU"] = "string"
#会员代码
CSecurityFtdcTraderOfferField["ParticipantID"] = "string"
#密码
CSecurityFtdcTraderOfferField["Password"] = "string"
#报盘类型
CSecurityFtdcTraderOfferField["OfferType"] = "string"
#安装编号
CSecurityFtdcTraderOfferField["InstallID"] = "int"
#本地报单编号
CSecurityFtdcTraderOfferField["OrderLocalID"] = "string"
#交易所交易员连接状态
CSecurityFtdcTraderOfferField["TraderConnectStatus"] = "string"
#发出连接请求的日期
CSecurityFtdcTraderOfferField["ConnectRequestDate"] = "string"
#发出连接请求的时间
CSecurityFtdcTraderOfferField["ConnectRequestTime"] = "string"
#上次报告日期
CSecurityFtdcTraderOfferField["LastReportDate"] = "string"
#上次报告时间
CSecurityFtdcTraderOfferField["LastReportTime"] = "string"
#完成连接日期
CSecurityFtdcTraderOfferField["ConnectDate"] = "string"
#完成连接时间
CSecurityFtdcTraderOfferField["ConnectTime"] = "string"
#启动日期
CSecurityFtdcTraderOfferField["StartDate"] = "string"
#启动时间
CSecurityFtdcTraderOfferField["StartTime"] = "string"
#交易日
CSecurityFtdcTraderOfferField["TradingDay"] = "string"
#经纪公司代码
CSecurityFtdcTraderOfferField["BrokerID"] = "string"
structDict['CSecurityFtdcTraderOfferField'] = CSecurityFtdcTraderOfferField


#交易所行情报盘机
CSecurityFtdcMDTraderOfferField = {}
#交易所代码
CSecurityFtdcMDTraderOfferField["ExchangeID"] = "string"
#交易所交易员代码
CSecurityFtdcMDTraderOfferField["BranchPBU"] = "string"
#会员代码
CSecurityFtdcMDTraderOfferField["ParticipantID"] = "string"
#密码
CSecurityFtdcMDTraderOfferField["Password"] = "string"
#报盘类型
CSecurityFtdcMDTraderOfferField["OfferType"] = "string"
#安装编号
CSecurityFtdcMDTraderOfferField["InstallID"] = "int"
#本地报单编号
CSecurityFtdcMDTraderOfferField["OrderLocalID"] = "string"
#交易所交易员连接状态
CSecurityFtdcMDTraderOfferField["TraderConnectStatus"] = "string"
#发出连接请求的日期
CSecurityFtdcMDTraderOfferField["ConnectRequestDate"] = "string"
#发出连接请求的时间
CSecurityFtdcMDTraderOfferField["ConnectRequestTime"] = "string"
#上次报告日期
CSecurityFtdcMDTraderOfferField["LastReportDate"] = "string"
#上次报告时间
CSecurityFtdcMDTraderOfferField["LastReportTime"] = "string"
#完成连接日期
CSecurityFtdcMDTraderOfferField["ConnectDate"] = "string"
#完成连接时间
CSecurityFtdcMDTraderOfferField["ConnectTime"] = "string"
#启动日期
CSecurityFtdcMDTraderOfferField["StartDate"] = "string"
#启动时间
CSecurityFtdcMDTraderOfferField["StartTime"] = "string"
#交易日
CSecurityFtdcMDTraderOfferField["TradingDay"] = "string"
#经纪公司代码
CSecurityFtdcMDTraderOfferField["BrokerID"] = "string"
structDict['CSecurityFtdcMDTraderOfferField'] = CSecurityFtdcMDTraderOfferField


#前置状态
CSecurityFtdcFrontStatusField = {}
#前置编号
CSecurityFtdcFrontStatusField["FrontID"] = "int"
#上次报告日期
CSecurityFtdcFrontStatusField["LastReportDate"] = "string"
#上次报告时间
CSecurityFtdcFrontStatusField["LastReportTime"] = "string"
#是否活跃
CSecurityFtdcFrontStatusField["IsActive"] = "int"
structDict['CSecurityFtdcFrontStatusField'] = CSecurityFtdcFrontStatusField


#用户会话
CSecurityFtdcUserSessionField = {}
#前置编号
CSecurityFtdcUserSessionField["FrontID"] = "int"
#会话编号
CSecurityFtdcUserSessionField["SessionID"] = "int"
#经纪公司代码
CSecurityFtdcUserSessionField["BrokerID"] = "string"
#用户代码
CSecurityFtdcUserSessionField["UserID"] = "string"
#登录日期
CSecurityFtdcUserSessionField["LoginDate"] = "string"
#登录时间
CSecurityFtdcUserSessionField["LoginTime"] = "string"
#IP地址
CSecurityFtdcUserSessionField["IPAddress"] = "string"
#用户端产品信息
CSecurityFtdcUserSessionField["UserProductInfo"] = "string"
#接口端产品信息
CSecurityFtdcUserSessionField["InterfaceProductInfo"] = "string"
#协议信息
CSecurityFtdcUserSessionField["ProtocolInfo"] = "string"
#Mac地址
CSecurityFtdcUserSessionField["MacAddress"] = "string"
structDict['CSecurityFtdcUserSessionField'] = CSecurityFtdcUserSessionField


#报单
CSecurityFtdcOrderField = {}
#经纪公司代码
CSecurityFtdcOrderField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcOrderField["InvestorID"] = "string"
#合约代码
CSecurityFtdcOrderField["InstrumentID"] = "string"
#报单引用
CSecurityFtdcOrderField["OrderRef"] = "string"
#用户代码
CSecurityFtdcOrderField["UserID"] = "string"
#交易所代码
CSecurityFtdcOrderField["ExchangeID"] = "string"
#报单价格条件
CSecurityFtdcOrderField["OrderPriceType"] = "string"
#买卖方向
CSecurityFtdcOrderField["Direction"] = "string"
#组合开平标志
CSecurityFtdcOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CSecurityFtdcOrderField["CombHedgeFlag"] = "string"
#价格
CSecurityFtdcOrderField["LimitPrice"] = "string"
#数量
CSecurityFtdcOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CSecurityFtdcOrderField["TimeCondition"] = "string"
#GTD日期
CSecurityFtdcOrderField["GTDDate"] = "string"
#成交量类型
CSecurityFtdcOrderField["VolumeCondition"] = "string"
#最小成交量
CSecurityFtdcOrderField["MinVolume"] = "int"
#触发条件
CSecurityFtdcOrderField["ContingentCondition"] = "string"
#止损价
CSecurityFtdcOrderField["StopPrice"] = "float"
#强平原因
CSecurityFtdcOrderField["ForceCloseReason"] = "string"
#自动挂起标志
CSecurityFtdcOrderField["IsAutoSuspend"] = "int"
#业务单元
CSecurityFtdcOrderField["BusinessUnit"] = "string"
#请求编号
CSecurityFtdcOrderField["RequestID"] = "int"
#本地报单编号
CSecurityFtdcOrderField["OrderLocalID"] = "string"
#会员代码
CSecurityFtdcOrderField["ParticipantID"] = "string"
#客户代码
CSecurityFtdcOrderField["ClientID"] = "string"
#合约在交易所的代码
CSecurityFtdcOrderField["ExchangeInstID"] = "string"
#交易所交易员代码
CSecurityFtdcOrderField["BranchPBU"] = "string"
#安装编号
CSecurityFtdcOrderField["InstallID"] = "int"
#报单提交状态
CSecurityFtdcOrderField["OrderSubmitStatus"] = "string"
#账户代码
CSecurityFtdcOrderField["AccountID"] = "string"
#报单提示序号
CSecurityFtdcOrderField["NotifySequence"] = "int"
#交易日
CSecurityFtdcOrderField["TradingDay"] = "string"
#报单编号
CSecurityFtdcOrderField["OrderSysID"] = "string"
#报单来源
CSecurityFtdcOrderField["OrderSource"] = "string"
#报单状态
CSecurityFtdcOrderField["OrderStatus"] = "string"
#报单类型
CSecurityFtdcOrderField["OrderType"] = "string"
#今成交数量
CSecurityFtdcOrderField["VolumeTraded"] = "int"
#剩余数量
CSecurityFtdcOrderField["VolumeTotal"] = "int"
#报单日期
CSecurityFtdcOrderField["InsertDate"] = "string"
#委托时间
CSecurityFtdcOrderField["InsertTime"] = "string"
#激活时间
CSecurityFtdcOrderField["ActiveTime"] = "string"
#挂起时间
CSecurityFtdcOrderField["SuspendTime"] = "string"
#最后修改时间
CSecurityFtdcOrderField["UpdateTime"] = "string"
#撤销时间
CSecurityFtdcOrderField["CancelTime"] = "string"
#最后修改交易所交易员代码
CSecurityFtdcOrderField["ActiveTraderID"] = "string"
#结算会员编号
CSecurityFtdcOrderField["ClearingPartID"] = "string"
#序号
CSecurityFtdcOrderField["SequenceNo"] = "int"
#前置编号
CSecurityFtdcOrderField["FrontID"] = "int"
#会话编号
CSecurityFtdcOrderField["SessionID"] = "int"
#用户端产品信息
CSecurityFtdcOrderField["UserProductInfo"] = "string"
#状态信息
CSecurityFtdcOrderField["StatusMsg"] = "string"
#用户强评标志
CSecurityFtdcOrderField["UserForceClose"] = "int"
#操作用户代码
CSecurityFtdcOrderField["ActiveUserID"] = "string"
#经纪公司报单编号
CSecurityFtdcOrderField["BrokerOrderSeq"] = "int"
#相关报单
CSecurityFtdcOrderField["RelativeOrderSysID"] = "string"
#营业部编号
CSecurityFtdcOrderField["BranchID"] = "string"
#成交金额
CSecurityFtdcOrderField["TradeAmount"] = "float"
#是否ETF
CSecurityFtdcOrderField["IsETF"] = "int"
#合约类型
CSecurityFtdcOrderField["InstrumentType"] = "string"
structDict['CSecurityFtdcOrderField'] = CSecurityFtdcOrderField


#报单操作
CSecurityFtdcOrderActionField = {}
#经纪公司代码
CSecurityFtdcOrderActionField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcOrderActionField["InvestorID"] = "string"
#报单操作引用
CSecurityFtdcOrderActionField["OrderActionRef"] = "int"
#报单引用
CSecurityFtdcOrderActionField["OrderRef"] = "string"
#请求编号
CSecurityFtdcOrderActionField["RequestID"] = "int"
#前置编号
CSecurityFtdcOrderActionField["FrontID"] = "int"
#会话编号
CSecurityFtdcOrderActionField["SessionID"] = "int"
#交易所代码
CSecurityFtdcOrderActionField["ExchangeID"] = "string"
#操作标志
CSecurityFtdcOrderActionField["ActionFlag"] = "string"
#价格
CSecurityFtdcOrderActionField["LimitPrice"] = "float"
#数量变化
CSecurityFtdcOrderActionField["VolumeChange"] = "int"
#操作日期
CSecurityFtdcOrderActionField["ActionDate"] = "string"
#操作时间
CSecurityFtdcOrderActionField["ActionTime"] = "string"
#交易所交易员代码
CSecurityFtdcOrderActionField["BranchPBU"] = "string"
#安装编号
CSecurityFtdcOrderActionField["InstallID"] = "int"
#本地报单编号
CSecurityFtdcOrderActionField["OrderLocalID"] = "string"
#操作本地编号
CSecurityFtdcOrderActionField["ActionLocalID"] = "string"
#会员代码
CSecurityFtdcOrderActionField["ParticipantID"] = "string"
#客户代码
CSecurityFtdcOrderActionField["ClientID"] = "string"
#业务单元
CSecurityFtdcOrderActionField["BusinessUnit"] = "string"
#报单操作状态
CSecurityFtdcOrderActionField["OrderActionStatus"] = "string"
#用户代码
CSecurityFtdcOrderActionField["UserID"] = "string"
#营业部编号
CSecurityFtdcOrderActionField["BranchID"] = "string"
#状态信息
CSecurityFtdcOrderActionField["StatusMsg"] = "string"
#合约代码
CSecurityFtdcOrderActionField["InstrumentID"] = "string"
#合约类型
CSecurityFtdcOrderActionField["InstrumentType"] = "string"
structDict['CSecurityFtdcOrderActionField'] = CSecurityFtdcOrderActionField


#错误报单
CSecurityFtdcErrOrderField = {}
#经纪公司代码
CSecurityFtdcErrOrderField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcErrOrderField["InvestorID"] = "string"
#合约代码
CSecurityFtdcErrOrderField["InstrumentID"] = "string"
#报单引用
CSecurityFtdcErrOrderField["OrderRef"] = "string"
#用户代码
CSecurityFtdcErrOrderField["UserID"] = "string"
#交易所代码
CSecurityFtdcErrOrderField["ExchangeID"] = "string"
#报单价格条件
CSecurityFtdcErrOrderField["OrderPriceType"] = "string"
#买卖方向
CSecurityFtdcErrOrderField["Direction"] = "string"
#组合开平标志
CSecurityFtdcErrOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CSecurityFtdcErrOrderField["CombHedgeFlag"] = "string"
#价格
CSecurityFtdcErrOrderField["LimitPrice"] = "string"
#数量
CSecurityFtdcErrOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CSecurityFtdcErrOrderField["TimeCondition"] = "string"
#GTD日期
CSecurityFtdcErrOrderField["GTDDate"] = "string"
#成交量类型
CSecurityFtdcErrOrderField["VolumeCondition"] = "string"
#最小成交量
CSecurityFtdcErrOrderField["MinVolume"] = "int"
#触发条件
CSecurityFtdcErrOrderField["ContingentCondition"] = "string"
#止损价
CSecurityFtdcErrOrderField["StopPrice"] = "float"
#强平原因
CSecurityFtdcErrOrderField["ForceCloseReason"] = "string"
#自动挂起标志
CSecurityFtdcErrOrderField["IsAutoSuspend"] = "int"
#业务单元
CSecurityFtdcErrOrderField["BusinessUnit"] = "string"
#请求编号
CSecurityFtdcErrOrderField["RequestID"] = "int"
#用户强评标志
CSecurityFtdcErrOrderField["UserForceClose"] = "int"
#错误代码
CSecurityFtdcErrOrderField["ErrorID"] = "int"
#错误信息
CSecurityFtdcErrOrderField["ErrorMsg"] = "string"
structDict['CSecurityFtdcErrOrderField'] = CSecurityFtdcErrOrderField


#错误报单操作
CSecurityFtdcErrOrderActionField = {}
#经纪公司代码
CSecurityFtdcErrOrderActionField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcErrOrderActionField["InvestorID"] = "string"
#报单操作引用
CSecurityFtdcErrOrderActionField["OrderActionRef"] = "int"
#报单引用
CSecurityFtdcErrOrderActionField["OrderRef"] = "string"
#请求编号
CSecurityFtdcErrOrderActionField["RequestID"] = "int"
#前置编号
CSecurityFtdcErrOrderActionField["FrontID"] = "int"
#会话编号
CSecurityFtdcErrOrderActionField["SessionID"] = "int"
#交易所代码
CSecurityFtdcErrOrderActionField["ExchangeID"] = "string"
#操作标志
CSecurityFtdcErrOrderActionField["ActionFlag"] = "string"
#价格
CSecurityFtdcErrOrderActionField["LimitPrice"] = "float"
#数量变化
CSecurityFtdcErrOrderActionField["VolumeChange"] = "int"
#操作日期
CSecurityFtdcErrOrderActionField["ActionDate"] = "string"
#操作时间
CSecurityFtdcErrOrderActionField["ActionTime"] = "string"
#交易所交易员代码
CSecurityFtdcErrOrderActionField["BranchPBU"] = "string"
#安装编号
CSecurityFtdcErrOrderActionField["InstallID"] = "int"
#本地报单编号
CSecurityFtdcErrOrderActionField["OrderLocalID"] = "string"
#操作本地编号
CSecurityFtdcErrOrderActionField["ActionLocalID"] = "string"
#会员代码
CSecurityFtdcErrOrderActionField["ParticipantID"] = "string"
#客户代码
CSecurityFtdcErrOrderActionField["ClientID"] = "string"
#业务单元
CSecurityFtdcErrOrderActionField["BusinessUnit"] = "string"
#报单操作状态
CSecurityFtdcErrOrderActionField["OrderActionStatus"] = "string"
#用户代码
CSecurityFtdcErrOrderActionField["UserID"] = "string"
#营业部编号
CSecurityFtdcErrOrderActionField["BranchID"] = "string"
#状态信息
CSecurityFtdcErrOrderActionField["StatusMsg"] = "string"
#合约代码
CSecurityFtdcErrOrderActionField["InstrumentID"] = "string"
#错误代码
CSecurityFtdcErrOrderActionField["ErrorID"] = "int"
#错误信息
CSecurityFtdcErrOrderActionField["ErrorMsg"] = "string"
#合约类型
CSecurityFtdcErrOrderActionField["InstrumentType"] = "string"
structDict['CSecurityFtdcErrOrderActionField'] = CSecurityFtdcErrOrderActionField


#成交
CSecurityFtdcTradeField = {}
#经纪公司代码
CSecurityFtdcTradeField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcTradeField["InvestorID"] = "string"
#合约代码
CSecurityFtdcTradeField["InstrumentID"] = "string"
#报单引用
CSecurityFtdcTradeField["OrderRef"] = "string"
#用户代码
CSecurityFtdcTradeField["UserID"] = "string"
#交易所代码
CSecurityFtdcTradeField["ExchangeID"] = "string"
#成交编号
CSecurityFtdcTradeField["TradeID"] = "string"
#买卖方向
CSecurityFtdcTradeField["Direction"] = "string"
#报单编号
CSecurityFtdcTradeField["OrderSysID"] = "string"
#会员代码
CSecurityFtdcTradeField["ParticipantID"] = "string"
#客户代码
CSecurityFtdcTradeField["ClientID"] = "string"
#交易角色
CSecurityFtdcTradeField["TradingRole"] = "string"
#合约在交易所的代码
CSecurityFtdcTradeField["ExchangeInstID"] = "string"
#开平标志
CSecurityFtdcTradeField["OffsetFlag"] = "string"
#投机套保标志
CSecurityFtdcTradeField["HedgeFlag"] = "string"
#价格
CSecurityFtdcTradeField["Price"] = "string"
#数量
CSecurityFtdcTradeField["Volume"] = "int"
#成交时期
CSecurityFtdcTradeField["TradeDate"] = "string"
#成交时间
CSecurityFtdcTradeField["TradeTime"] = "string"
#成交类型
CSecurityFtdcTradeField["TradeType"] = "string"
#成交价来源
CSecurityFtdcTradeField["PriceSource"] = "string"
#交易所交易员代码
CSecurityFtdcTradeField["BranchPBU"] = "string"
#本地报单编号
CSecurityFtdcTradeField["OrderLocalID"] = "string"
#结算会员编号
CSecurityFtdcTradeField["ClearingPartID"] = "string"
#业务单元
CSecurityFtdcTradeField["BusinessUnit"] = "string"
#序号
CSecurityFtdcTradeField["SequenceNo"] = "int"
#成交来源
CSecurityFtdcTradeField["TradeSource"] = "string"
#交易日
CSecurityFtdcTradeField["TradingDay"] = "string"
#经纪公司报单编号
CSecurityFtdcTradeField["BrokerOrderSeq"] = "int"
#成交金额
CSecurityFtdcTradeField["TradeAmount"] = "float"
#成交序号
CSecurityFtdcTradeField["TradeIndex"] = "int"
structDict['CSecurityFtdcTradeField'] = CSecurityFtdcTradeField


#投资者持仓
CSecurityFtdcInvestorPositionField = {}
#合约代码
CSecurityFtdcInvestorPositionField["InstrumentID"] = "string"
#经纪公司代码
CSecurityFtdcInvestorPositionField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcInvestorPositionField["InvestorID"] = "string"
#持仓多空方向
CSecurityFtdcInvestorPositionField["PosiDirection"] = "string"
#投机套保标志
CSecurityFtdcInvestorPositionField["HedgeFlag"] = "string"
#持仓日期
CSecurityFtdcInvestorPositionField["PositionDate"] = "string"
#上日持仓
CSecurityFtdcInvestorPositionField["YdPosition"] = "float"
#总持仓
CSecurityFtdcInvestorPositionField["Position"] = "float"
#多头冻结
CSecurityFtdcInvestorPositionField["LongFrozen"] = "float"
#空头冻结
CSecurityFtdcInvestorPositionField["ShortFrozen"] = "float"
#开仓冻结金额
CSecurityFtdcInvestorPositionField["LongFrozenAmount"] = "float"
#开仓冻结金额
CSecurityFtdcInvestorPositionField["ShortFrozenAmount"] = "float"
#开仓量
CSecurityFtdcInvestorPositionField["OpenVolume"] = "float"
#平仓量
CSecurityFtdcInvestorPositionField["CloseVolume"] = "float"
#开仓金额
CSecurityFtdcInvestorPositionField["OpenAmount"] = "float"
#平仓金额
CSecurityFtdcInvestorPositionField["CloseAmount"] = "float"
#持仓成本
CSecurityFtdcInvestorPositionField["PositionCost"] = "float"
#冻结的资金
CSecurityFtdcInvestorPositionField["FrozenCash"] = "float"
#资金差额
CSecurityFtdcInvestorPositionField["CashIn"] = "float"
#手续费
CSecurityFtdcInvestorPositionField["Commission"] = "float"
#上次结算价
CSecurityFtdcInvestorPositionField["PreSettlementPrice"] = "float"
#本次结算价
CSecurityFtdcInvestorPositionField["SettlementPrice"] = "float"
#交易日
CSecurityFtdcInvestorPositionField["TradingDay"] = "string"
#开仓成本
CSecurityFtdcInvestorPositionField["OpenCost"] = "float"
#交易所保证金
CSecurityFtdcInvestorPositionField["ExchangeMargin"] = "float"
#今日持仓
CSecurityFtdcInvestorPositionField["TodayPosition"] = "float"
#过户费
CSecurityFtdcInvestorPositionField["TransferFee"] = "float"
#印花税
CSecurityFtdcInvestorPositionField["StampTax"] = "float"
#今日申购赎回数量
CSecurityFtdcInvestorPositionField["TodayPurRedVolume"] = "float"
#折算率
CSecurityFtdcInvestorPositionField["ConversionRate"] = "float"
#折算金额
CSecurityFtdcInvestorPositionField["ConversionAmount"] = "float"
#证券价值
CSecurityFtdcInvestorPositionField["StockValue"] = "float"
#交易所代码
CSecurityFtdcInvestorPositionField["ExchangeID"] = "string"
#AccountID
CSecurityFtdcInvestorPositionField["AccountID"] = "string"
#质押入库数量
CSecurityFtdcInvestorPositionField["PledgeInPosition"] = "float"
#正回购使用的标准券数量
CSecurityFtdcInvestorPositionField["RepurchasePosition"] = "float"
#ETF申赎空头冻结
CSecurityFtdcInvestorPositionField["PurRedShortFrozen"] = "float"
#融资买入数量
CSecurityFtdcInvestorPositionField["MarginTradeVolume"] = "float"
#融资买入金额
CSecurityFtdcInvestorPositionField["MarginTradeAmount"] = "float"
#融资买入冻结数量
CSecurityFtdcInvestorPositionField["MarginTradeFrozenVolume"] = "float"
#融资买入冻结金额
CSecurityFtdcInvestorPositionField["MarginTradeFrozenAmount"] = "float"
#融资买入盈亏
CSecurityFtdcInvestorPositionField["MarginTradeConversionProfit"] = "float"
#融券卖出数量
CSecurityFtdcInvestorPositionField["ShortSellVolume"] = "float"
#融券卖出金额
CSecurityFtdcInvestorPositionField["ShortSellAmount"] = "float"
#融券卖出冻结数量
CSecurityFtdcInvestorPositionField["ShortSellFrozenVolume"] = "float"
#融券卖出冻结金额
CSecurityFtdcInvestorPositionField["ShortSellFrozenAmount"] = "float"
#融券卖出盈亏
CSecurityFtdcInvestorPositionField["ShortSellConversionProfit"] = "float"
#融券总市值
CSecurityFtdcInvestorPositionField["SSStockValue"] = "float"
#今日融资持仓
CSecurityFtdcInvestorPositionField["TodayMTPosition"] = "float"
#今日融券持仓
CSecurityFtdcInvestorPositionField["TodaySSPosition"] = "float"
#历史持仓开仓成本
CSecurityFtdcInvestorPositionField["YdOpenCost"] = "float"
#锁定仓位
CSecurityFtdcInvestorPositionField["LockPosition"] = "float"
#备兑仓位
CSecurityFtdcInvestorPositionField["CoverPosition"] = "float"
#锁定冻结仓位
CSecurityFtdcInvestorPositionField["LockFrozenPosition"] = "float"
#解锁冻结仓位
CSecurityFtdcInvestorPositionField["UnlockFrozenPosition"] = "float"
#备兑冻结仓位
CSecurityFtdcInvestorPositionField["CoverFrozenPosition"] = "float"
#行权冻结仓位
CSecurityFtdcInvestorPositionField["ExecFrozenPosition"] = "float"
#上日备兑仓位
CSecurityFtdcInvestorPositionField["YDCoverPosition"] = "float"
structDict['CSecurityFtdcInvestorPositionField'] = CSecurityFtdcInvestorPositionField


#出入金同步
CSecurityFtdcSyncDepositField = {}
#出入金流水号
CSecurityFtdcSyncDepositField["DepositSeqNo"] = "string"
#经纪公司代码
CSecurityFtdcSyncDepositField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcSyncDepositField["InvestorID"] = "string"
#入金金额
CSecurityFtdcSyncDepositField["Deposit"] = "float"
#是否强制进行
CSecurityFtdcSyncDepositField["IsForce"] = "int"
#账户代码
CSecurityFtdcSyncDepositField["AccountID"] = "string"
structDict['CSecurityFtdcSyncDepositField'] = CSecurityFtdcSyncDepositField


#查询交易所
CSecurityFtdcQryExchangeField = {}
#交易所代码
CSecurityFtdcQryExchangeField["ExchangeID"] = "string"
structDict['CSecurityFtdcQryExchangeField'] = CSecurityFtdcQryExchangeField


#查询产品
CSecurityFtdcQryProductField = {}
#产品代码
CSecurityFtdcQryProductField["ProductID"] = "string"
structDict['CSecurityFtdcQryProductField'] = CSecurityFtdcQryProductField


#查询合约
CSecurityFtdcQryInstrumentField = {}
#合约代码
CSecurityFtdcQryInstrumentField["InstrumentID"] = "string"
#交易所代码
CSecurityFtdcQryInstrumentField["ExchangeID"] = "string"
#合约在交易所的代码
CSecurityFtdcQryInstrumentField["ExchangeInstID"] = "string"
#产品代码
CSecurityFtdcQryInstrumentField["ProductID"] = "string"
structDict['CSecurityFtdcQryInstrumentField'] = CSecurityFtdcQryInstrumentField


#查询经纪公司
CSecurityFtdcQryBrokerField = {}
#经纪公司代码
CSecurityFtdcQryBrokerField["BrokerID"] = "string"
structDict['CSecurityFtdcQryBrokerField'] = CSecurityFtdcQryBrokerField


#查询经纪公司会员代码
CSecurityFtdcQryPartBrokerField = {}
#交易所代码
CSecurityFtdcQryPartBrokerField["ExchangeID"] = "string"
#经纪公司代码
CSecurityFtdcQryPartBrokerField["BrokerID"] = "string"
#会员代码
CSecurityFtdcQryPartBrokerField["ParticipantID"] = "string"
structDict['CSecurityFtdcQryPartBrokerField'] = CSecurityFtdcQryPartBrokerField


#查询投资者
CSecurityFtdcQryInvestorField = {}
#经纪公司代码
CSecurityFtdcQryInvestorField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryInvestorField["InvestorID"] = "string"
structDict['CSecurityFtdcQryInvestorField'] = CSecurityFtdcQryInvestorField


#查询交易编码
CSecurityFtdcQryTradingCodeField = {}
#经纪公司代码
CSecurityFtdcQryTradingCodeField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryTradingCodeField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcQryTradingCodeField["ExchangeID"] = "string"
#客户代码
CSecurityFtdcQryTradingCodeField["ClientID"] = "string"
structDict['CSecurityFtdcQryTradingCodeField'] = CSecurityFtdcQryTradingCodeField


#查询管理用户
CSecurityFtdcQrySuperUserField = {}
#用户代码
CSecurityFtdcQrySuperUserField["UserID"] = "string"
structDict['CSecurityFtdcQrySuperUserField'] = CSecurityFtdcQrySuperUserField


#查询管理用户功能权限
CSecurityFtdcQrySuperUserFunctionField = {}
#用户代码
CSecurityFtdcQrySuperUserFunctionField["UserID"] = "string"
structDict['CSecurityFtdcQrySuperUserFunctionField'] = CSecurityFtdcQrySuperUserFunctionField


#查询经纪公司用户
CSecurityFtdcQryBrokerUserField = {}
#经纪公司代码
CSecurityFtdcQryBrokerUserField["BrokerID"] = "string"
#用户代码
CSecurityFtdcQryBrokerUserField["UserID"] = "string"
structDict['CSecurityFtdcQryBrokerUserField'] = CSecurityFtdcQryBrokerUserField


#查询经纪公司用户权限
CSecurityFtdcQryBrokerUserFunctionField = {}
#经纪公司代码
CSecurityFtdcQryBrokerUserFunctionField["BrokerID"] = "string"
#用户代码
CSecurityFtdcQryBrokerUserFunctionField["UserID"] = "string"
structDict['CSecurityFtdcQryBrokerUserFunctionField'] = CSecurityFtdcQryBrokerUserFunctionField


#查询资金账户
CSecurityFtdcQryTradingAccountField = {}
#经纪公司代码
CSecurityFtdcQryTradingAccountField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryTradingAccountField["InvestorID"] = "string"
structDict['CSecurityFtdcQryTradingAccountField'] = CSecurityFtdcQryTradingAccountField


#查询禁止登录用户
CSecurityFtdcQryLoginForbiddenUserField = {}
#经纪公司代码
CSecurityFtdcQryLoginForbiddenUserField["BrokerID"] = "string"
#用户代码
CSecurityFtdcQryLoginForbiddenUserField["UserID"] = "string"
structDict['CSecurityFtdcQryLoginForbiddenUserField'] = CSecurityFtdcQryLoginForbiddenUserField


#查询行情
CSecurityFtdcQryDepthMarketDataField = {}
#合约代码
CSecurityFtdcQryDepthMarketDataField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryDepthMarketDataField'] = CSecurityFtdcQryDepthMarketDataField


#查询合约交易权限
CSecurityFtdcQryInstrumentTradingRightField = {}
#交易所代码
CSecurityFtdcQryInstrumentTradingRightField["ExchangeID"] = "string"
#经纪公司代码
CSecurityFtdcQryInstrumentTradingRightField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryInstrumentTradingRightField["InvestorID"] = "string"
#合约代码
CSecurityFtdcQryInstrumentTradingRightField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryInstrumentTradingRightField'] = CSecurityFtdcQryInstrumentTradingRightField


#查询投资者持仓明细
CSecurityFtdcQryInvestorPositionDetailField = {}
#经纪公司代码
CSecurityFtdcQryInvestorPositionDetailField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryInvestorPositionDetailField["InvestorID"] = "string"
#合约代码
CSecurityFtdcQryInvestorPositionDetailField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryInvestorPositionDetailField'] = CSecurityFtdcQryInvestorPositionDetailField


#查询债券利息
CSecurityFtdcQryBondInterestField = {}
#交易所代码
CSecurityFtdcQryBondInterestField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcQryBondInterestField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryBondInterestField'] = CSecurityFtdcQryBondInterestField


#查询市值配售信息
CSecurityFtdcQryMarketRationInfoField = {}
#经纪公司代码
CSecurityFtdcQryMarketRationInfoField["BrokerID"] = "string"
#投资者帐号
CSecurityFtdcQryMarketRationInfoField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcQryMarketRationInfoField["ExchangeID"] = "string"
structDict['CSecurityFtdcQryMarketRationInfoField'] = CSecurityFtdcQryMarketRationInfoField


#查询合约手续费率
CSecurityFtdcQryInstrumentCommissionRateField = {}
#交易所代码
CSecurityFtdcQryInstrumentCommissionRateField["ExchangeID"] = "string"
#经纪公司代码
CSecurityFtdcQryInstrumentCommissionRateField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryInstrumentCommissionRateField["InvestorID"] = "string"
#合约代码
CSecurityFtdcQryInstrumentCommissionRateField["InstrumentID"] = "string"
#买卖方向
CSecurityFtdcQryInstrumentCommissionRateField["Direction"] = "string"
#开平标志
CSecurityFtdcQryInstrumentCommissionRateField["OffsetFlag"] = "string"
structDict['CSecurityFtdcQryInstrumentCommissionRateField'] = CSecurityFtdcQryInstrumentCommissionRateField


#查询余券信息
CSecurityFtdcQryExcessStockInfoField = {}
#经纪公司代码
CSecurityFtdcQryExcessStockInfoField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryExcessStockInfoField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcQryExcessStockInfoField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcQryExcessStockInfoField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryExcessStockInfoField'] = CSecurityFtdcQryExcessStockInfoField


#查询投资者帐户关系
CSecurityFtdcQryInvestorAccountField = {}
#经纪公司代码
CSecurityFtdcQryInvestorAccountField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryInvestorAccountField["InvestorID"] = "string"
structDict['CSecurityFtdcQryInvestorAccountField'] = CSecurityFtdcQryInvestorAccountField


#查询ETF合约
CSecurityFtdcQryETFInstrumentField = {}
#交易所代码
CSecurityFtdcQryETFInstrumentField["ExchangeID"] = "string"
#ETF证券代码
CSecurityFtdcQryETFInstrumentField["ETFInstrumentID"] = "string"
structDict['CSecurityFtdcQryETFInstrumentField'] = CSecurityFtdcQryETFInstrumentField


#查询ETF股票篮
CSecurityFtdcQryETFBasketField = {}
#交易所代码
CSecurityFtdcQryETFBasketField["ExchangeID"] = "string"
#ETF证券代码
CSecurityFtdcQryETFBasketField["ETFInstrumentID"] = "string"
structDict['CSecurityFtdcQryETFBasketField'] = CSecurityFtdcQryETFBasketField


#查询OF合约
CSecurityFtdcQryOFInstrumentField = {}
#交易所代码
CSecurityFtdcQryOFInstrumentField["ExchangeID"] = "string"
#ETF证券代码
CSecurityFtdcQryOFInstrumentField["OFInstrumentID"] = "string"
structDict['CSecurityFtdcQryOFInstrumentField'] = CSecurityFtdcQryOFInstrumentField


#查询SF合约
CSecurityFtdcQrySFInstrumentField = {}
#交易所代码
CSecurityFtdcQrySFInstrumentField["ExchangeID"] = "string"
#ETF证券代码
CSecurityFtdcQrySFInstrumentField["SFInstrumentID"] = "string"
structDict['CSecurityFtdcQrySFInstrumentField'] = CSecurityFtdcQrySFInstrumentField


#查询合约单手保证金
CSecurityFtdcQryInstrumentUnitMarginField = {}
#经纪公司代码
CSecurityFtdcQryInstrumentUnitMarginField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryInstrumentUnitMarginField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcQryInstrumentUnitMarginField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcQryInstrumentUnitMarginField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryInstrumentUnitMarginField'] = CSecurityFtdcQryInstrumentUnitMarginField


#查询期权资金限制参数
CSecurityFtdcQryOptionsFundLimitParamField = {}
#经纪公司代码
CSecurityFtdcQryOptionsFundLimitParamField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryOptionsFundLimitParamField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcQryOptionsFundLimitParamField["ExchangeID"] = "string"
structDict['CSecurityFtdcQryOptionsFundLimitParamField'] = CSecurityFtdcQryOptionsFundLimitParamField


#查询投资者期权持仓
CSecurityFtdcQryInvestorOptionsPositionField = {}
#经纪公司代码
CSecurityFtdcQryInvestorOptionsPositionField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryInvestorOptionsPositionField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcQryInvestorOptionsPositionField["ExchangeID"] = "string"
#标的合约代码
CSecurityFtdcQryInvestorOptionsPositionField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryInvestorOptionsPositionField'] = CSecurityFtdcQryInvestorOptionsPositionField


#查询预交割信息
CSecurityFtdcQryPreDelivInfoField = {}
#经纪公司代码
CSecurityFtdcQryPreDelivInfoField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryPreDelivInfoField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcQryPreDelivInfoField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcQryPreDelivInfoField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryPreDelivInfoField'] = CSecurityFtdcQryPreDelivInfoField


#查询可融券分配信息
CSecurityFtdcQryCreditStockAssignInfoField = {}
#经纪公司代码
CSecurityFtdcQryCreditStockAssignInfoField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryCreditStockAssignInfoField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcQryCreditStockAssignInfoField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcQryCreditStockAssignInfoField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryCreditStockAssignInfoField'] = CSecurityFtdcQryCreditStockAssignInfoField


#查询可融资分配信息
CSecurityFtdcQryCreditCashAssignInfoField = {}
#经纪公司代码
CSecurityFtdcQryCreditCashAssignInfoField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryCreditCashAssignInfoField["InvestorID"] = "string"
structDict['CSecurityFtdcQryCreditCashAssignInfoField'] = CSecurityFtdcQryCreditCashAssignInfoField


#查询证券折算率
CSecurityFtdcQryConversionRateField = {}
#交易所代码
CSecurityFtdcQryConversionRateField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcQryConversionRateField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryConversionRateField'] = CSecurityFtdcQryConversionRateField


#查询历史信用负债信息
CSecurityFtdcQryHisCreditDebtInfoField = {}
#经纪公司代码
CSecurityFtdcQryHisCreditDebtInfoField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryHisCreditDebtInfoField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcQryHisCreditDebtInfoField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcQryHisCreditDebtInfoField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryHisCreditDebtInfoField'] = CSecurityFtdcQryHisCreditDebtInfoField


#查询行情静态信息
CSecurityFtdcQryMarketDataStaticInfoField = {}
#交易所代码
CSecurityFtdcQryMarketDataStaticInfoField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcQryMarketDataStaticInfoField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryMarketDataStaticInfoField'] = CSecurityFtdcQryMarketDataStaticInfoField


#查询到期回购信息
CSecurityFtdcQryExpireRepurchInfoField = {}
#经纪公司代码
CSecurityFtdcQryExpireRepurchInfoField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryExpireRepurchInfoField["InvestorID"] = "string"
structDict['CSecurityFtdcQryExpireRepurchInfoField'] = CSecurityFtdcQryExpireRepurchInfoField


#查询债券质押为标准券比例
CSecurityFtdcQryBondPledgeRateField = {}
#交易所代码
CSecurityFtdcQryBondPledgeRateField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcQryBondPledgeRateField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryBondPledgeRateField'] = CSecurityFtdcQryBondPledgeRateField


#查询债券质押代码对照关系
CSecurityFtdcQryPledgeBondField = {}
#交易所代码
CSecurityFtdcQryPledgeBondField["ExchangeID"] = "string"
#合约代码
CSecurityFtdcQryPledgeBondField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryPledgeBondField'] = CSecurityFtdcQryPledgeBondField


#查询交易员报盘机
CSecurityFtdcQryTraderOfferField = {}
#交易所代码
CSecurityFtdcQryTraderOfferField["ExchangeID"] = "string"
#会员代码
CSecurityFtdcQryTraderOfferField["ParticipantID"] = "string"
#交易所交易员代码
CSecurityFtdcQryTraderOfferField["BranchPBU"] = "string"
structDict['CSecurityFtdcQryTraderOfferField'] = CSecurityFtdcQryTraderOfferField


#查询行情报盘机
CSecurityFtdcQryMDTraderOfferField = {}
#交易所代码
CSecurityFtdcQryMDTraderOfferField["ExchangeID"] = "string"
#会员代码
CSecurityFtdcQryMDTraderOfferField["ParticipantID"] = "string"
#交易所交易员代码
CSecurityFtdcQryMDTraderOfferField["BranchPBU"] = "string"
structDict['CSecurityFtdcQryMDTraderOfferField'] = CSecurityFtdcQryMDTraderOfferField


#查询前置状态
CSecurityFtdcQryFrontStatusField = {}
#前置编号
CSecurityFtdcQryFrontStatusField["FrontID"] = "int"
structDict['CSecurityFtdcQryFrontStatusField'] = CSecurityFtdcQryFrontStatusField


#查询用户会话
CSecurityFtdcQryUserSessionField = {}
#前置编号
CSecurityFtdcQryUserSessionField["FrontID"] = "int"
#会话编号
CSecurityFtdcQryUserSessionField["SessionID"] = "int"
#经纪公司代码
CSecurityFtdcQryUserSessionField["BrokerID"] = "string"
#用户代码
CSecurityFtdcQryUserSessionField["UserID"] = "string"
structDict['CSecurityFtdcQryUserSessionField'] = CSecurityFtdcQryUserSessionField


#查询报单
CSecurityFtdcQryOrderField = {}
#经纪公司代码
CSecurityFtdcQryOrderField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryOrderField["InvestorID"] = "string"
#合约代码
CSecurityFtdcQryOrderField["InstrumentID"] = "string"
#交易所代码
CSecurityFtdcQryOrderField["ExchangeID"] = "string"
#报单编号
CSecurityFtdcQryOrderField["OrderSysID"] = "string"
#开始时间
CSecurityFtdcQryOrderField["InsertTimeStart"] = "string"
#结束时间
CSecurityFtdcQryOrderField["InsertTimeEnd"] = "string"
structDict['CSecurityFtdcQryOrderField'] = CSecurityFtdcQryOrderField


#查询报单操作
CSecurityFtdcQryOrderActionField = {}
#经纪公司代码
CSecurityFtdcQryOrderActionField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryOrderActionField["InvestorID"] = "string"
#交易所代码
CSecurityFtdcQryOrderActionField["ExchangeID"] = "string"
structDict['CSecurityFtdcQryOrderActionField'] = CSecurityFtdcQryOrderActionField


#查询错误报单
CSecurityFtdcQryErrOrderField = {}
#经纪公司代码
CSecurityFtdcQryErrOrderField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryErrOrderField["InvestorID"] = "string"
structDict['CSecurityFtdcQryErrOrderField'] = CSecurityFtdcQryErrOrderField


#查询错误报单操作
CSecurityFtdcQryErrOrderActionField = {}
#经纪公司代码
CSecurityFtdcQryErrOrderActionField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryErrOrderActionField["InvestorID"] = "string"
structDict['CSecurityFtdcQryErrOrderActionField'] = CSecurityFtdcQryErrOrderActionField


#查询成交
CSecurityFtdcQryTradeField = {}
#经纪公司代码
CSecurityFtdcQryTradeField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryTradeField["InvestorID"] = "string"
#合约代码
CSecurityFtdcQryTradeField["InstrumentID"] = "string"
#交易所代码
CSecurityFtdcQryTradeField["ExchangeID"] = "string"
#成交编号
CSecurityFtdcQryTradeField["TradeID"] = "string"
#开始时间
CSecurityFtdcQryTradeField["TradeTimeStart"] = "string"
#结束时间
CSecurityFtdcQryTradeField["TradeTimeEnd"] = "string"
structDict['CSecurityFtdcQryTradeField'] = CSecurityFtdcQryTradeField


#查询投资者持仓
CSecurityFtdcQryInvestorPositionField = {}
#经纪公司代码
CSecurityFtdcQryInvestorPositionField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryInvestorPositionField["InvestorID"] = "string"
#合约代码
CSecurityFtdcQryInvestorPositionField["InstrumentID"] = "string"
structDict['CSecurityFtdcQryInvestorPositionField'] = CSecurityFtdcQryInvestorPositionField


#查询出入金流水
CSecurityFtdcQrySyncDepositField = {}
#经纪公司代码
CSecurityFtdcQrySyncDepositField["BrokerID"] = "string"
#出入金流水号
CSecurityFtdcQrySyncDepositField["DepositSeqNo"] = "string"
structDict['CSecurityFtdcQrySyncDepositField'] = CSecurityFtdcQrySyncDepositField


#用户口令变更
CSecurityFtdcUserPasswordUpdateField = {}
#经纪公司代码
CSecurityFtdcUserPasswordUpdateField["BrokerID"] = "string"
#用户代码
CSecurityFtdcUserPasswordUpdateField["UserID"] = "string"
#原来的口令
CSecurityFtdcUserPasswordUpdateField["OldPassword"] = "string"
#新的口令
CSecurityFtdcUserPasswordUpdateField["NewPassword"] = "string"
structDict['CSecurityFtdcUserPasswordUpdateField'] = CSecurityFtdcUserPasswordUpdateField


#资金账户口令变更域
CSecurityFtdcTradingAccountPasswordUpdateField = {}
#经纪公司代码
CSecurityFtdcTradingAccountPasswordUpdateField["BrokerID"] = "string"
#投资者帐号
CSecurityFtdcTradingAccountPasswordUpdateField["AccountID"] = "string"
#原来的口令
CSecurityFtdcTradingAccountPasswordUpdateField["OldPassword"] = "string"
#新的口令
CSecurityFtdcTradingAccountPasswordUpdateField["NewPassword"] = "string"
structDict['CSecurityFtdcTradingAccountPasswordUpdateField'] = CSecurityFtdcTradingAccountPasswordUpdateField


#手工同步用户动态令牌
CSecurityFtdcManualSyncBrokerUserOTPField = {}
#经纪公司代码
CSecurityFtdcManualSyncBrokerUserOTPField["BrokerID"] = "string"
#用户代码
CSecurityFtdcManualSyncBrokerUserOTPField["UserID"] = "string"
#动态令牌类型
CSecurityFtdcManualSyncBrokerUserOTPField["OTPType"] = "string"
#第一个动态密码
CSecurityFtdcManualSyncBrokerUserOTPField["FirstOTP"] = "string"
#第二个动态密码
CSecurityFtdcManualSyncBrokerUserOTPField["SecondOTP"] = "string"
structDict['CSecurityFtdcManualSyncBrokerUserOTPField'] = CSecurityFtdcManualSyncBrokerUserOTPField


#经纪公司用户口令
CSecurityFtdcBrokerUserPasswordField = {}
#经纪公司代码
CSecurityFtdcBrokerUserPasswordField["BrokerID"] = "string"
#用户代码
CSecurityFtdcBrokerUserPasswordField["UserID"] = "string"
#密码
CSecurityFtdcBrokerUserPasswordField["Password"] = "string"
structDict['CSecurityFtdcBrokerUserPasswordField'] = CSecurityFtdcBrokerUserPasswordField


#资金账户口令域
CSecurityFtdcTradingAccountPasswordField = {}
#经纪公司代码
CSecurityFtdcTradingAccountPasswordField["BrokerID"] = "string"
#投资者帐号
CSecurityFtdcTradingAccountPasswordField["AccountID"] = "string"
#密码
CSecurityFtdcTradingAccountPasswordField["Password"] = "string"
structDict['CSecurityFtdcTradingAccountPasswordField'] = CSecurityFtdcTradingAccountPasswordField


#用户权限
CSecurityFtdcUserRightField = {}
#经纪公司代码
CSecurityFtdcUserRightField["BrokerID"] = "string"
#用户代码
CSecurityFtdcUserRightField["UserID"] = "string"
#客户权限类型
CSecurityFtdcUserRightField["UserRightType"] = "string"
#是否禁止
CSecurityFtdcUserRightField["IsForbidden"] = "int"
structDict['CSecurityFtdcUserRightField'] = CSecurityFtdcUserRightField


#投资者账户
CSecurityFtdcInvestorAccountField = {}
#经纪公司代码
CSecurityFtdcInvestorAccountField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcInvestorAccountField["InvestorID"] = "string"
#投资者帐号
CSecurityFtdcInvestorAccountField["AccountID"] = "string"
#是否主账户
CSecurityFtdcInvestorAccountField["IsDefault"] = "int"
#账户类型
CSecurityFtdcInvestorAccountField["AccountType"] = "string"
#是否活跃
CSecurityFtdcInvestorAccountField["IsActive"] = "int"
#上交所交易单元号
CSecurityFtdcInvestorAccountField["SHBranchPBU"] = "string"
#深交所交易单元号
CSecurityFtdcInvestorAccountField["SZBranchPBU"] = "string"
structDict['CSecurityFtdcInvestorAccountField'] = CSecurityFtdcInvestorAccountField


#用户IP
CSecurityFtdcUserIPField = {}
#经纪公司代码
CSecurityFtdcUserIPField["BrokerID"] = "string"
#用户代码
CSecurityFtdcUserIPField["UserID"] = "string"
#IP地址
CSecurityFtdcUserIPField["IPAddress"] = "string"
#IP地址掩码
CSecurityFtdcUserIPField["IPMask"] = "string"
#Mac地址
CSecurityFtdcUserIPField["MacAddress"] = "string"
structDict['CSecurityFtdcUserIPField'] = CSecurityFtdcUserIPField


#用户动态令牌参数
CSecurityFtdcBrokerUserOTPParamField = {}
#经纪公司代码
CSecurityFtdcBrokerUserOTPParamField["BrokerID"] = "string"
#用户代码
CSecurityFtdcBrokerUserOTPParamField["UserID"] = "string"
#动态令牌提供商
CSecurityFtdcBrokerUserOTPParamField["OTPVendorsID"] = "string"
#动态令牌序列号
CSecurityFtdcBrokerUserOTPParamField["SerialNumber"] = "string"
#令牌密钥
CSecurityFtdcBrokerUserOTPParamField["AuthKey"] = "string"
#漂移值
CSecurityFtdcBrokerUserOTPParamField["LastDrift"] = "int"
#成功值
CSecurityFtdcBrokerUserOTPParamField["LastSuccess"] = "int"
#动态令牌类型
CSecurityFtdcBrokerUserOTPParamField["OTPType"] = "string"
structDict['CSecurityFtdcBrokerUserOTPParamField'] = CSecurityFtdcBrokerUserOTPParamField


#用户登录请求
CSecurityFtdcReqUserLoginField = {}
#交易日
CSecurityFtdcReqUserLoginField["TradingDay"] = "string"
#经纪公司代码
CSecurityFtdcReqUserLoginField["BrokerID"] = "string"
#用户代码
CSecurityFtdcReqUserLoginField["UserID"] = "string"
#密码
CSecurityFtdcReqUserLoginField["Password"] = "string"
#用户端产品信息
CSecurityFtdcReqUserLoginField["UserProductInfo"] = "string"
#接口端产品信息
CSecurityFtdcReqUserLoginField["InterfaceProductInfo"] = "string"
#协议信息
CSecurityFtdcReqUserLoginField["ProtocolInfo"] = "string"
#Mac地址
CSecurityFtdcReqUserLoginField["MacAddress"] = "string"
#动态密码
CSecurityFtdcReqUserLoginField["OneTimePassword"] = "string"
#终端IP地址
CSecurityFtdcReqUserLoginField["ClientIPAddress"] = "string"
#客户端认证码
CSecurityFtdcReqUserLoginField["AuthCode"] = "string"
#随机码
CSecurityFtdcReqUserLoginField["RandCode"] = "string"
#硬盘序列号
CSecurityFtdcReqUserLoginField["HDSerialNumber"] = "string"
structDict['CSecurityFtdcReqUserLoginField'] = CSecurityFtdcReqUserLoginField


#用户登录应答
CSecurityFtdcRspUserLoginField = {}
#交易日
CSecurityFtdcRspUserLoginField["TradingDay"] = "string"
#登录成功时间
CSecurityFtdcRspUserLoginField["LoginTime"] = "string"
#经纪公司代码
CSecurityFtdcRspUserLoginField["BrokerID"] = "string"
#用户代码
CSecurityFtdcRspUserLoginField["UserID"] = "string"
#交易系统名称
CSecurityFtdcRspUserLoginField["SystemName"] = "string"
#前置编号
CSecurityFtdcRspUserLoginField["FrontID"] = "int"
#会话编号
CSecurityFtdcRspUserLoginField["SessionID"] = "int"
#最大报单引用
CSecurityFtdcRspUserLoginField["MaxOrderRef"] = "string"
structDict['CSecurityFtdcRspUserLoginField'] = CSecurityFtdcRspUserLoginField


#用户登出请求
CSecurityFtdcUserLogoutField = {}
#经纪公司代码
CSecurityFtdcUserLogoutField["BrokerID"] = "string"
#用户代码
CSecurityFtdcUserLogoutField["UserID"] = "string"
structDict['CSecurityFtdcUserLogoutField'] = CSecurityFtdcUserLogoutField


#全部登出信息
CSecurityFtdcLogoutAllField = {}
#前置编号
CSecurityFtdcLogoutAllField["FrontID"] = "int"
#会话编号
CSecurityFtdcLogoutAllField["SessionID"] = "int"
#系统名称
CSecurityFtdcLogoutAllField["SystemName"] = "string"
structDict['CSecurityFtdcLogoutAllField'] = CSecurityFtdcLogoutAllField


#强制交易员退出
CSecurityFtdcForceUserLogoutField = {}
#经纪公司代码
CSecurityFtdcForceUserLogoutField["BrokerID"] = "string"
#用户代码
CSecurityFtdcForceUserLogoutField["UserID"] = "string"
structDict['CSecurityFtdcForceUserLogoutField'] = CSecurityFtdcForceUserLogoutField


#经纪公司用户激活
CSecurityFtdcActivateBrokerUserField = {}
#经纪公司代码
CSecurityFtdcActivateBrokerUserField["BrokerID"] = "string"
#用户代码
CSecurityFtdcActivateBrokerUserField["UserID"] = "string"
structDict['CSecurityFtdcActivateBrokerUserField'] = CSecurityFtdcActivateBrokerUserField


#认证随机码
CSecurityFtdcAuthRandCodeField = {}
#随机码
CSecurityFtdcAuthRandCodeField["RandCode"] = "string"
structDict['CSecurityFtdcAuthRandCodeField'] = CSecurityFtdcAuthRandCodeField


#输入报单
CSecurityFtdcInputOrderField = {}
#经纪公司代码
CSecurityFtdcInputOrderField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcInputOrderField["InvestorID"] = "string"
#合约代码
CSecurityFtdcInputOrderField["InstrumentID"] = "string"
#报单引用
CSecurityFtdcInputOrderField["OrderRef"] = "string"
#用户代码
CSecurityFtdcInputOrderField["UserID"] = "string"
#交易所代码
CSecurityFtdcInputOrderField["ExchangeID"] = "string"
#报单价格条件
CSecurityFtdcInputOrderField["OrderPriceType"] = "string"
#买卖方向
CSecurityFtdcInputOrderField["Direction"] = "string"
#组合开平标志
CSecurityFtdcInputOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CSecurityFtdcInputOrderField["CombHedgeFlag"] = "string"
#价格
CSecurityFtdcInputOrderField["LimitPrice"] = "string"
#数量
CSecurityFtdcInputOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CSecurityFtdcInputOrderField["TimeCondition"] = "string"
#GTD日期
CSecurityFtdcInputOrderField["GTDDate"] = "string"
#成交量类型
CSecurityFtdcInputOrderField["VolumeCondition"] = "string"
#最小成交量
CSecurityFtdcInputOrderField["MinVolume"] = "int"
#触发条件
CSecurityFtdcInputOrderField["ContingentCondition"] = "string"
#止损价
CSecurityFtdcInputOrderField["StopPrice"] = "float"
#强平原因
CSecurityFtdcInputOrderField["ForceCloseReason"] = "string"
#自动挂起标志
CSecurityFtdcInputOrderField["IsAutoSuspend"] = "int"
#业务单元
CSecurityFtdcInputOrderField["BusinessUnit"] = "string"
#请求编号
CSecurityFtdcInputOrderField["RequestID"] = "int"
#用户强评标志
CSecurityFtdcInputOrderField["UserForceClose"] = "int"
structDict['CSecurityFtdcInputOrderField'] = CSecurityFtdcInputOrderField


#输入报单操作
CSecurityFtdcInputOrderActionField = {}
#经纪公司代码
CSecurityFtdcInputOrderActionField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcInputOrderActionField["InvestorID"] = "string"
#报单操作引用
CSecurityFtdcInputOrderActionField["OrderActionRef"] = "int"
#报单引用
CSecurityFtdcInputOrderActionField["OrderRef"] = "string"
#请求编号
CSecurityFtdcInputOrderActionField["RequestID"] = "int"
#前置编号
CSecurityFtdcInputOrderActionField["FrontID"] = "int"
#会话编号
CSecurityFtdcInputOrderActionField["SessionID"] = "int"
#交易所代码
CSecurityFtdcInputOrderActionField["ExchangeID"] = "string"
#操作标志
CSecurityFtdcInputOrderActionField["ActionFlag"] = "string"
#价格
CSecurityFtdcInputOrderActionField["LimitPrice"] = "float"
#数量变化
CSecurityFtdcInputOrderActionField["VolumeChange"] = "int"
#用户代码
CSecurityFtdcInputOrderActionField["UserID"] = "string"
#合约代码
CSecurityFtdcInputOrderActionField["InstrumentID"] = "string"
#交易所交易员代码
CSecurityFtdcInputOrderActionField["BranchPBU"] = "string"
#本地报单编号
CSecurityFtdcInputOrderActionField["OrderLocalID"] = "string"
structDict['CSecurityFtdcInputOrderActionField'] = CSecurityFtdcInputOrderActionField


#指定的合约
CSecurityFtdcSpecificInstrumentField = {}
#合约代码
CSecurityFtdcSpecificInstrumentField["InstrumentID"] = "string"
#交易所代码
CSecurityFtdcSpecificInstrumentField["ExchangeID"] = "string"
structDict['CSecurityFtdcSpecificInstrumentField'] = CSecurityFtdcSpecificInstrumentField


#指定的交易所
CSecurityFtdcSpecificExchangeField = {}
#交易所代码
CSecurityFtdcSpecificExchangeField["ExchangeID"] = "string"
structDict['CSecurityFtdcSpecificExchangeField'] = CSecurityFtdcSpecificExchangeField


#行情基础属性
CSecurityFtdcMarketDataBaseField = {}
#交易日
CSecurityFtdcMarketDataBaseField["TradingDay"] = "string"
#上次结算价
CSecurityFtdcMarketDataBaseField["PreSettlementPrice"] = "float"
#昨收盘
CSecurityFtdcMarketDataBaseField["PreClosePrice"] = "float"
#昨持仓量
CSecurityFtdcMarketDataBaseField["PreOpenInterest"] = "float"
#昨虚实度
CSecurityFtdcMarketDataBaseField["PreDelta"] = "float"
#昨日基金净值
CSecurityFtdcMarketDataBaseField["PreIOPV"] = "float"
structDict['CSecurityFtdcMarketDataBaseField'] = CSecurityFtdcMarketDataBaseField


#行情静态属性
CSecurityFtdcMarketDataStaticField = {}
#今开盘
CSecurityFtdcMarketDataStaticField["OpenPrice"] = "float"
#最高价
CSecurityFtdcMarketDataStaticField["HighestPrice"] = "float"
#最低价
CSecurityFtdcMarketDataStaticField["LowestPrice"] = "float"
#今收盘
CSecurityFtdcMarketDataStaticField["ClosePrice"] = "float"
#涨停板价
CSecurityFtdcMarketDataStaticField["UpperLimitPrice"] = "float"
#跌停板价
CSecurityFtdcMarketDataStaticField["LowerLimitPrice"] = "float"
#本次结算价
CSecurityFtdcMarketDataStaticField["SettlementPrice"] = "float"
#今虚实度
CSecurityFtdcMarketDataStaticField["CurrDelta"] = "float"
#基金净值
CSecurityFtdcMarketDataStaticField["IOPV"] = "float"
#动态参考价格
CSecurityFtdcMarketDataStaticField["AuctionPrice"] = "float"
structDict['CSecurityFtdcMarketDataStaticField'] = CSecurityFtdcMarketDataStaticField


#行情最新成交属性
CSecurityFtdcMarketDataLastMatchField = {}
#最新价
CSecurityFtdcMarketDataLastMatchField["LastPrice"] = "float"
#数量
CSecurityFtdcMarketDataLastMatchField["Volume"] = "float"
#成交金额
CSecurityFtdcMarketDataLastMatchField["Turnover"] = "float"
#持仓量
CSecurityFtdcMarketDataLastMatchField["OpenInterest"] = "float"
structDict['CSecurityFtdcMarketDataLastMatchField'] = CSecurityFtdcMarketDataLastMatchField


#行情最优价属性
CSecurityFtdcMarketDataBestPriceField = {}
#申买价一
CSecurityFtdcMarketDataBestPriceField["BidPrice1"] = "float"
#申买量一
CSecurityFtdcMarketDataBestPriceField["BidVolume1"] = "float"
#申卖价一
CSecurityFtdcMarketDataBestPriceField["AskPrice1"] = "float"
#申卖量一
CSecurityFtdcMarketDataBestPriceField["AskVolume1"] = "float"
structDict['CSecurityFtdcMarketDataBestPriceField'] = CSecurityFtdcMarketDataBestPriceField


#行情申买二、三属性
CSecurityFtdcMarketDataBid23Field = {}
#申买价二
CSecurityFtdcMarketDataBid23Field["BidPrice2"] = "float"
#申买量二
CSecurityFtdcMarketDataBid23Field["BidVolume2"] = "float"
#申买价三
CSecurityFtdcMarketDataBid23Field["BidPrice3"] = "float"
#申买量三
CSecurityFtdcMarketDataBid23Field["BidVolume3"] = "float"
structDict['CSecurityFtdcMarketDataBid23Field'] = CSecurityFtdcMarketDataBid23Field


#行情申卖二、三属性
CSecurityFtdcMarketDataAsk23Field = {}
#申卖价二
CSecurityFtdcMarketDataAsk23Field["AskPrice2"] = "float"
#申卖量二
CSecurityFtdcMarketDataAsk23Field["AskVolume2"] = "float"
#申卖价三
CSecurityFtdcMarketDataAsk23Field["AskPrice3"] = "float"
#申卖量三
CSecurityFtdcMarketDataAsk23Field["AskVolume3"] = "float"
structDict['CSecurityFtdcMarketDataAsk23Field'] = CSecurityFtdcMarketDataAsk23Field


#行情申买四、五属性
CSecurityFtdcMarketDataBid45Field = {}
#申买价四
CSecurityFtdcMarketDataBid45Field["BidPrice4"] = "float"
#申买量四
CSecurityFtdcMarketDataBid45Field["BidVolume4"] = "float"
#申买价五
CSecurityFtdcMarketDataBid45Field["BidPrice5"] = "float"
#申买量五
CSecurityFtdcMarketDataBid45Field["BidVolume5"] = "float"
structDict['CSecurityFtdcMarketDataBid45Field'] = CSecurityFtdcMarketDataBid45Field


#行情申卖四、五属性
CSecurityFtdcMarketDataAsk45Field = {}
#申卖价四
CSecurityFtdcMarketDataAsk45Field["AskPrice4"] = "float"
#申卖量四
CSecurityFtdcMarketDataAsk45Field["AskVolume4"] = "float"
#申卖价五
CSecurityFtdcMarketDataAsk45Field["AskPrice5"] = "float"
#申卖量五
CSecurityFtdcMarketDataAsk45Field["AskVolume5"] = "float"
structDict['CSecurityFtdcMarketDataAsk45Field'] = CSecurityFtdcMarketDataAsk45Field


#行情更新时间属性
CSecurityFtdcMarketDataUpdateTimeField = {}
#合约代码
CSecurityFtdcMarketDataUpdateTimeField["InstrumentID"] = "string"
#最后修改时间
CSecurityFtdcMarketDataUpdateTimeField["UpdateTime"] = "string"
#最后修改毫秒
CSecurityFtdcMarketDataUpdateTimeField["UpdateMillisec"] = "int"
#业务日期
CSecurityFtdcMarketDataUpdateTimeField["ActionDay"] = "string"
#交易阶段
CSecurityFtdcMarketDataUpdateTimeField["TradingPhase"] = "string"
#开仓限制
CSecurityFtdcMarketDataUpdateTimeField["OpenRestriction"] = "string"
structDict['CSecurityFtdcMarketDataUpdateTimeField'] = CSecurityFtdcMarketDataUpdateTimeField


#成交均价
CSecurityFtdcMarketDataAveragePriceField = {}
#当日均价
CSecurityFtdcMarketDataAveragePriceField["AveragePrice"] = "float"
structDict['CSecurityFtdcMarketDataAveragePriceField'] = CSecurityFtdcMarketDataAveragePriceField


#行情交易所代码属性
CSecurityFtdcMarketDataExchangeField = {}
#交易所代码
CSecurityFtdcMarketDataExchangeField["ExchangeID"] = "string"
structDict['CSecurityFtdcMarketDataExchangeField'] = CSecurityFtdcMarketDataExchangeField


#信息分发
CSecurityFtdcDisseminationField = {}
#序列系列号
CSecurityFtdcDisseminationField["SequenceSeries"] = "int"
#序列号
CSecurityFtdcDisseminationField["SequenceNo"] = "int"
structDict['CSecurityFtdcDisseminationField'] = CSecurityFtdcDisseminationField


#资金转账输入
CSecurityFtdcInputFundTransferField = {}
#经纪公司代码
CSecurityFtdcInputFundTransferField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcInputFundTransferField["InvestorID"] = "string"
#投资者资金帐号
CSecurityFtdcInputFundTransferField["AccountID"] = "string"
#资金帐户密码
CSecurityFtdcInputFundTransferField["Password"] = "string"
#用户代码
CSecurityFtdcInputFundTransferField["UserID"] = "string"
#交易金额
CSecurityFtdcInputFundTransferField["TradeAmount"] = "float"
#摘要
CSecurityFtdcInputFundTransferField["Digest"] = "string"
#账户类型
CSecurityFtdcInputFundTransferField["AccountType"] = "string"
structDict['CSecurityFtdcInputFundTransferField'] = CSecurityFtdcInputFundTransferField


#资金转账
CSecurityFtdcFundTransferField = {}
#经纪公司代码
CSecurityFtdcFundTransferField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcFundTransferField["InvestorID"] = "string"
#投资者资金帐号
CSecurityFtdcFundTransferField["AccountID"] = "string"
#资金帐户密码
CSecurityFtdcFundTransferField["Password"] = "string"
#用户代码
CSecurityFtdcFundTransferField["UserID"] = "string"
#交易金额
CSecurityFtdcFundTransferField["TradeAmount"] = "float"
#摘要
CSecurityFtdcFundTransferField["Digest"] = "string"
#会话编号
CSecurityFtdcFundTransferField["SessionID"] = "int"
#Liber核心流水号
CSecurityFtdcFundTransferField["LiberSerial"] = "int"
#转账平台流水号
CSecurityFtdcFundTransferField["PlateSerial"] = "int"
#第三方流水号
CSecurityFtdcFundTransferField["TransferSerial"] = "string"
#交易日
CSecurityFtdcFundTransferField["TradingDay"] = "string"
#转账时间
CSecurityFtdcFundTransferField["TradeTime"] = "string"
#出入金方向
CSecurityFtdcFundTransferField["FundDirection"] = "string"
#错误代码
CSecurityFtdcFundTransferField["ErrorID"] = "int"
#错误信息
CSecurityFtdcFundTransferField["ErrorMsg"] = "string"
structDict['CSecurityFtdcFundTransferField'] = CSecurityFtdcFundTransferField


#资金转账查询请求
CSecurityFtdcQryFundTransferSerialField = {}
#经纪公司代码
CSecurityFtdcQryFundTransferSerialField["BrokerID"] = "string"
#投资者资金帐号
CSecurityFtdcQryFundTransferSerialField["AccountID"] = "string"
#账户类型
CSecurityFtdcQryFundTransferSerialField["AccountType"] = "string"
structDict['CSecurityFtdcQryFundTransferSerialField'] = CSecurityFtdcQryFundTransferSerialField


#资金内转
CSecurityFtdcFundInterTransferField = {}
#经纪公司代码
CSecurityFtdcFundInterTransferField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcFundInterTransferField["InvestorID"] = "string"
#用户代码
CSecurityFtdcFundInterTransferField["UserID"] = "string"
#资金账户代码
CSecurityFtdcFundInterTransferField["AccountID"] = "string"
#资金账户密码
CSecurityFtdcFundInterTransferField["Password"] = "string"
#金额
CSecurityFtdcFundInterTransferField["TradeAmount"] = "float"
#内转类型
CSecurityFtdcFundInterTransferField["TransferType"] = "string"
#资金内转编号
CSecurityFtdcFundInterTransferField["SerialID"] = "int"
structDict['CSecurityFtdcFundInterTransferField'] = CSecurityFtdcFundInterTransferField


#资金内转流水
CSecurityFtdcFundInterTransferSerialField = {}
#经纪公司代码
CSecurityFtdcFundInterTransferSerialField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcFundInterTransferSerialField["InvestorID"] = "string"
#用户代码
CSecurityFtdcFundInterTransferSerialField["UserID"] = "string"
#资金账户代码
CSecurityFtdcFundInterTransferSerialField["AccountID"] = "string"
#资金账户密码
CSecurityFtdcFundInterTransferSerialField["Password"] = "string"
#金额
CSecurityFtdcFundInterTransferSerialField["TradeAmount"] = "float"
#内转类型
CSecurityFtdcFundInterTransferSerialField["TransferType"] = "string"
#资金内转编号
CSecurityFtdcFundInterTransferSerialField["SerialID"] = "int"
#转账时间
CSecurityFtdcFundInterTransferSerialField["TransferTime"] = "string"
#错误代码
CSecurityFtdcFundInterTransferSerialField["ErrorID"] = "int"
#错误信息
CSecurityFtdcFundInterTransferSerialField["ErrorMsg"] = "string"
structDict['CSecurityFtdcFundInterTransferSerialField'] = CSecurityFtdcFundInterTransferSerialField


#资金内转流水查询请求
CSecurityFtdcQryFundInterTransferSerialField = {}
#经纪公司代码
CSecurityFtdcQryFundInterTransferSerialField["BrokerID"] = "string"
#投资者代码
CSecurityFtdcQryFundInterTransferSerialField["InvestorID"] = "string"
structDict['CSecurityFtdcQryFundInterTransferSerialField'] = CSecurityFtdcQryFundInterTransferSerialField


#获取数据库信息
CSecurityFtdcFetchDBInfoField = {}
#用户代码
CSecurityFtdcFetchDBInfoField["UserID"] = "string"
#密码
CSecurityFtdcFetchDBInfoField["Password"] = "string"
#数据库索引
CSecurityFtdcFetchDBInfoField["DBIndex"] = "string"
#数据库IP地址
CSecurityFtdcFetchDBInfoField["IPAddress"] = "string"
#数据库IP端口
CSecurityFtdcFetchDBInfoField["IPPort"] = "int"
#数据库名称
CSecurityFtdcFetchDBInfoField["DBName"] = "string"
#数据库用户名
CSecurityFtdcFetchDBInfoField["DBUserID"] = "string"
#数据库密码
CSecurityFtdcFetchDBInfoField["DBPassword"] = "string"
structDict['CSecurityFtdcFetchDBInfoField'] = CSecurityFtdcFetchDBInfoField


#MD用户信息
CSecurityFtdcMDUserInfoField = {}
#经纪公司代码
CSecurityFtdcMDUserInfoField["BrokerID"] = "string"
#用户代码
CSecurityFtdcMDUserInfoField["UserID"] = "string"
#用户名称
CSecurityFtdcMDUserInfoField["UserName"] = "string"
#密码
CSecurityFtdcMDUserInfoField["Password"] = "string"
#行情系统编号
CSecurityFtdcMDUserInfoField["MDSysID"] = "int"
#股票最大订阅数量
CSecurityFtdcMDUserInfoField["MaxStockCount"] = "int"
#期权最大订阅数量
CSecurityFtdcMDUserInfoField["MaxOptionsCount"] = "int"
structDict['CSecurityFtdcMDUserInfoField'] = CSecurityFtdcMDUserInfoField





