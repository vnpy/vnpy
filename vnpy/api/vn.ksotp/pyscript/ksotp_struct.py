# encoding: UTF-8

structDict = {}











#响应信息
CKSOTPRspInfoField = {}
#错误代码
CKSOTPRspInfoField["ErrorID"] = "int"
#错误信息
CKSOTPRspInfoField["ErrorMsg"] = "string"
structDict['CKSOTPRspInfoField'] = CKSOTPRspInfoField


#用户登录请求
CKSOTPReqUserLoginField = {}
#经纪公司代码
CKSOTPReqUserLoginField["BrokerID"] = "string"
#用户代码
CKSOTPReqUserLoginField["UserID"] = "string"
#密码
CKSOTPReqUserLoginField["Password"] = "string"
#用户端产品信息
CKSOTPReqUserLoginField["UserProductInfo"] = "string"
#Mac地址
CKSOTPReqUserLoginField["MacAddress"] = "string"
#终端IP地址
CKSOTPReqUserLoginField["ClientIPAddress"] = "string"
structDict['CKSOTPReqUserLoginField'] = CKSOTPReqUserLoginField


#用户登录应答
CKSOTPRspUserLoginField = {}
#经纪公司代码
CKSOTPRspUserLoginField["BrokerID"] = "string"
#交易日
CKSOTPRspUserLoginField["TradingDay"] = "string"
#登录成功时间
CKSOTPRspUserLoginField["LoginTime"] = "string"
#用户代码
CKSOTPRspUserLoginField["UserID"] = "string"
#交易系统名称
CKSOTPRspUserLoginField["SystemName"] = "string"
#前置编号
CKSOTPRspUserLoginField["FrontID"] = "int"
#会话编号
CKSOTPRspUserLoginField["SessionID"] = "int"
#最大报单引用
CKSOTPRspUserLoginField["MaxOrderRef"] = "string"
#上证所时间
CKSOTPRspUserLoginField["SSETime"] = "string"
structDict['CKSOTPRspUserLoginField'] = CKSOTPRspUserLoginField


#用户登出请求
CKSOTPUserLogoutField = {}
#经纪公司代码
CKSOTPUserLogoutField["BrokerID"] = "string"
#用户代码
CKSOTPUserLogoutField["UserID"] = "string"
structDict['CKSOTPUserLogoutField'] = CKSOTPUserLogoutField


#用户口令变更
CKSOTPUserPasswordUpdateField = {}
#经纪公司代码
CKSOTPUserPasswordUpdateField["BrokerID"] = "string"
#用户代码
CKSOTPUserPasswordUpdateField["UserID"] = "string"
#原来的口令
CKSOTPUserPasswordUpdateField["OldPassword"] = "string"
#新的口令
CKSOTPUserPasswordUpdateField["NewPassword"] = "string"
structDict['CKSOTPUserPasswordUpdateField'] = CKSOTPUserPasswordUpdateField


#资金账户口令变更域
CKSOTPTradingAccountPasswordUpdateField = {}
#经纪公司代码
CKSOTPTradingAccountPasswordUpdateField["BrokerID"] = "string"
#投资者帐号
CKSOTPTradingAccountPasswordUpdateField["AccountID"] = "string"
#原来的口令
CKSOTPTradingAccountPasswordUpdateField["OldPassword"] = "string"
#新的口令
CKSOTPTradingAccountPasswordUpdateField["NewPassword"] = "string"
structDict['CKSOTPTradingAccountPasswordUpdateField'] = CKSOTPTradingAccountPasswordUpdateField


#输入报单
CKSOTPInputOrderField = {}
#经纪公司代码
CKSOTPInputOrderField["BrokerID"] = "string"
#投资者代码
CKSOTPInputOrderField["InvestorID"] = "string"
#合约代码
CKSOTPInputOrderField["InstrumentID"] = "string"
#报单引用
CKSOTPInputOrderField["OrderRef"] = "string"
#用户代码
CKSOTPInputOrderField["UserID"] = "string"
#报单价格条件
CKSOTPInputOrderField["OrderPriceType"] = "string"
#买卖方向
CKSOTPInputOrderField["Direction"] = "string"
#开平标志
CKSOTPInputOrderField["OffsetFlag"] = "string"
#备兑标志
CKSOTPInputOrderField["HedgeFlag"] = "string"
#价格
CKSOTPInputOrderField["LimitPrice"] = "float"
#数量
CKSOTPInputOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CKSOTPInputOrderField["TimeCondition"] = "string"
#GTD日期
CKSOTPInputOrderField["GTDDate"] = "string"
#成交量类型
CKSOTPInputOrderField["VolumeCondition"] = "string"
#最小成交量
CKSOTPInputOrderField["MinVolume"] = "int"
#触发条件
CKSOTPInputOrderField["ContingentCondition"] = "string"
#止损价
CKSOTPInputOrderField["StopPrice"] = "float"
#强平原因
CKSOTPInputOrderField["ForceCloseReason"] = "string"
#自动挂起标志
CKSOTPInputOrderField["IsAutoSuspend"] = "int"
#业务单元
CKSOTPInputOrderField["BusinessUnit"] = "string"
#请求编号
CKSOTPInputOrderField["RequestID"] = "int"
#用户强评标志
CKSOTPInputOrderField["UserForceClose"] = "int"
#互换单标志
CKSOTPInputOrderField["IsSwapOrder"] = "int"
#交易所代码
CKSOTPInputOrderField["ExchangeID"] = "string"
structDict['CKSOTPInputOrderField'] = CKSOTPInputOrderField


#输入报单操作
CKSOTPInputOrderActionField = {}
#经纪公司代码
CKSOTPInputOrderActionField["BrokerID"] = "string"
#投资者代码
CKSOTPInputOrderActionField["InvestorID"] = "string"
#报单引用
CKSOTPInputOrderActionField["OrderRef"] = "string"
#请求编号
CKSOTPInputOrderActionField["RequestID"] = "int"
#前置编号
CKSOTPInputOrderActionField["FrontID"] = "int"
#会话编号
CKSOTPInputOrderActionField["SessionID"] = "int"
#交易所代码
CKSOTPInputOrderActionField["ExchangeID"] = "string"
#报单编号
CKSOTPInputOrderActionField["OrderSysID"] = "string"
#操作标志
CKSOTPInputOrderActionField["ActionFlag"] = "string"
#价格
CKSOTPInputOrderActionField["LimitPrice"] = "float"
#数量变化
CKSOTPInputOrderActionField["VolumeChange"] = "int"
#用户代码
CKSOTPInputOrderActionField["UserID"] = "string"
#合约代码
CKSOTPInputOrderActionField["InstrumentID"] = "string"
structDict['CKSOTPInputOrderActionField'] = CKSOTPInputOrderActionField


#查询报单
CKSOTPQryOrderField = {}
#经纪公司代码
CKSOTPQryOrderField["BrokerID"] = "string"
#投资者代码
CKSOTPQryOrderField["InvestorID"] = "string"
#合约代码
CKSOTPQryOrderField["InstrumentID"] = "string"
#交易所代码
CKSOTPQryOrderField["ExchangeID"] = "string"
#报单编号
CKSOTPQryOrderField["OrderSysID"] = "string"
structDict['CKSOTPQryOrderField'] = CKSOTPQryOrderField


#查询成交
CKSOTPQryTradeField = {}
#经纪公司代码
CKSOTPQryTradeField["BrokerID"] = "string"
#投资者代码
CKSOTPQryTradeField["InvestorID"] = "string"
#合约代码
CKSOTPQryTradeField["InstrumentID"] = "string"
#交易所代码
CKSOTPQryTradeField["ExchangeID"] = "string"
#开始时间
CKSOTPQryTradeField["TradeTimeStart"] = "string"
#结束时间
CKSOTPQryTradeField["TradeTimeEnd"] = "string"
structDict['CKSOTPQryTradeField'] = CKSOTPQryTradeField


#查询投资者持仓
CKSOTPQryInvestorPositionField = {}
#经纪公司代码
CKSOTPQryInvestorPositionField["BrokerID"] = "string"
#投资者代码
CKSOTPQryInvestorPositionField["InvestorID"] = "string"
#合约代码
CKSOTPQryInvestorPositionField["InstrumentID"] = "string"
#交易所代码
CKSOTPQryInvestorPositionField["ExchangeID"] = "string"
structDict['CKSOTPQryInvestorPositionField'] = CKSOTPQryInvestorPositionField


#投资者持仓
CKSOTPInvestorPositionField = {}
#合约代码
CKSOTPInvestorPositionField["InstrumentID"] = "string"
#经纪公司代码
CKSOTPInvestorPositionField["BrokerID"] = "string"
#投资者代码
CKSOTPInvestorPositionField["InvestorID"] = "string"
#持仓多空方向
CKSOTPInvestorPositionField["PosiDirection"] = "string"
#备兑标志
CKSOTPInvestorPositionField["HedgeFlag"] = "string"
#持仓日期
CKSOTPInvestorPositionField["PositionDate"] = "string"
#上日持仓
CKSOTPInvestorPositionField["YdPosition"] = "int"
#今日持仓
CKSOTPInvestorPositionField["Position"] = "int"
#多头冻结
CKSOTPInvestorPositionField["LongFrozen"] = "int"
#空头冻结
CKSOTPInvestorPositionField["ShortFrozen"] = "int"
#开仓冻结金额
CKSOTPInvestorPositionField["LongFrozenAmount"] = "float"
#开仓冻结金额
CKSOTPInvestorPositionField["ShortFrozenAmount"] = "float"
#开仓量
CKSOTPInvestorPositionField["OpenVolume"] = "int"
#开仓金额
CKSOTPInvestorPositionField["OpenAmount"] = "float"
#平仓金额
CKSOTPInvestorPositionField["CloseAmount"] = "float"
#持仓成本
CKSOTPInvestorPositionField["PositionCost"] = "float"
#占用的保证金
CKSOTPInvestorPositionField["UseMargin"] = "float"
#冻结的保证金
CKSOTPInvestorPositionField["FrozenMargin"] = "float"
#冻结的资金
CKSOTPInvestorPositionField["FrozenCash"] = "float"
#冻结的手续费
CKSOTPInvestorPositionField["FrozenCommission"] = "float"
#资金差额
CKSOTPInvestorPositionField["CashIn"] = "float"
#手续费
CKSOTPInvestorPositionField["Commission"] = "float"
#平仓盈亏
CKSOTPInvestorPositionField["CloseProfit"] = "float"
#持仓盈亏
CKSOTPInvestorPositionField["PositionProfit"] = "float"
#上次结算价
CKSOTPInvestorPositionField["PreSettlementPrice"] = "float"
#本次结算价
CKSOTPInvestorPositionField["SettlementPrice"] = "float"
#交易日
CKSOTPInvestorPositionField["TradingDay"] = "string"
#结算编号
CKSOTPInvestorPositionField["SettlementID"] = "int"
#开仓成本
CKSOTPInvestorPositionField["OpenCost"] = "float"
#交易所保证金
CKSOTPInvestorPositionField["ExchangeMargin"] = "float"
#逐日盯市平仓盈亏
CKSOTPInvestorPositionField["CloseProfitByDate"] = "float"
#逐笔对冲平仓盈亏
CKSOTPInvestorPositionField["CloseProfitByTrade"] = "float"
#今日持仓
CKSOTPInvestorPositionField["TodayPosition"] = "int"
#保证金率
CKSOTPInvestorPositionField["MarginRateByMoney"] = "float"
#保证金率(按手数)
CKSOTPInvestorPositionField["MarginRateByVolume"] = "float"
#执行冻结
CKSOTPInvestorPositionField["StrikeFrozen"] = "int"
#执行冻结金额
CKSOTPInvestorPositionField["StrikeFrozenAmount"] = "float"
#交易所代码
CKSOTPInvestorPositionField["ExchangeID"] = "string"
structDict['CKSOTPInvestorPositionField'] = CKSOTPInvestorPositionField


#查询资金账户
CKSOTPQryTradingAccountField = {}
#经纪公司代码
CKSOTPQryTradingAccountField["BrokerID"] = "string"
#投资者代码
CKSOTPQryTradingAccountField["InvestorID"] = "string"
structDict['CKSOTPQryTradingAccountField'] = CKSOTPQryTradingAccountField


#资金账户
CKSOTPTradingAccountField = {}
#经纪公司代码
CKSOTPTradingAccountField["BrokerID"] = "string"
#投资者帐号
CKSOTPTradingAccountField["AccountID"] = "string"
#上次结算准备金
CKSOTPTradingAccountField["PreBalance"] = "float"
#上次占用的保证金
CKSOTPTradingAccountField["PreMargin"] = "float"
#入金金额
CKSOTPTradingAccountField["Deposit"] = "float"
#出金金额
CKSOTPTradingAccountField["Withdraw"] = "float"
#冻结的保证金
CKSOTPTradingAccountField["FrozenMargin"] = "float"
#冻结的资金
CKSOTPTradingAccountField["FrozenCash"] = "float"
#冻结的手续费
CKSOTPTradingAccountField["FrozenCommission"] = "float"
#当前保证金总额
CKSOTPTradingAccountField["CurrMargin"] = "float"
#资金差额
CKSOTPTradingAccountField["CashIn"] = "float"
#手续费
CKSOTPTradingAccountField["Commission"] = "float"
#平仓盈亏
CKSOTPTradingAccountField["CloseProfit"] = "float"
#持仓盈亏
CKSOTPTradingAccountField["PositionProfit"] = "float"
#证券结算准备金
CKSOTPTradingAccountField["Balance"] = "float"
#可用资金
CKSOTPTradingAccountField["Available"] = "float"
#可取资金
CKSOTPTradingAccountField["WithdrawQuota"] = "float"
#基本准备金
CKSOTPTradingAccountField["Reserve"] = "float"
#交易日
CKSOTPTradingAccountField["TradingDay"] = "string"
#结算编号
CKSOTPTradingAccountField["SettlementID"] = "int"
#信用额度
CKSOTPTradingAccountField["Credit"] = "float"
#质押金额
CKSOTPTradingAccountField["Mortgage"] = "float"
#交易所保证金
CKSOTPTradingAccountField["ExchangeMargin"] = "float"
#投资者交割保证金
CKSOTPTradingAccountField["DeliveryMargin"] = "float"
#交易所交割保证金
CKSOTPTradingAccountField["ExchangeDeliveryMargin"] = "float"
structDict['CKSOTPTradingAccountField'] = CKSOTPTradingAccountField


#查询投资者
CKSOTPQryInvestorField = {}
#经纪公司代码
CKSOTPQryInvestorField["BrokerID"] = "string"
#投资者代码
CKSOTPQryInvestorField["InvestorID"] = "string"
structDict['CKSOTPQryInvestorField'] = CKSOTPQryInvestorField


#投资者
CKSOTPInvestorField = {}
#投资者代码
CKSOTPInvestorField["InvestorID"] = "string"
#经纪公司代码
CKSOTPInvestorField["BrokerID"] = "string"
#投资者名称
CKSOTPInvestorField["InvestorName"] = "string"
#证件类型
CKSOTPInvestorField["IdentifiedCardType"] = "string"
#证件号码
CKSOTPInvestorField["IdentifiedCardNo"] = "string"
#是否活跃
CKSOTPInvestorField["IsActive"] = "int"
#联系电话
CKSOTPInvestorField["Telephone"] = "string"
#通讯地址
CKSOTPInvestorField["Address"] = "string"
#开户日期
CKSOTPInvestorField["OpenDate"] = "string"
#手机
CKSOTPInvestorField["Mobile"] = "string"
structDict['CKSOTPInvestorField'] = CKSOTPInvestorField


#查询合约账号
CKSOTPQryTradingCodeField = {}
#经纪公司代码
CKSOTPQryTradingCodeField["BrokerID"] = "string"
#投资者代码
CKSOTPQryTradingCodeField["InvestorID"] = "string"
#交易所代码
CKSOTPQryTradingCodeField["ExchangeID"] = "string"
structDict['CKSOTPQryTradingCodeField'] = CKSOTPQryTradingCodeField


#交易编码
CKSOTPTradingCodeField = {}
#投资者代码
CKSOTPTradingCodeField["InvestorID"] = "string"
#经纪公司代码
CKSOTPTradingCodeField["BrokerID"] = "string"
#交易所代码
CKSOTPTradingCodeField["ExchangeID"] = "string"
#合约账号
CKSOTPTradingCodeField["ClientID"] = "string"
#是否活跃
CKSOTPTradingCodeField["IsActive"] = "int"
#交易编码类型
CKSOTPTradingCodeField["ClientIDType"] = "string"
structDict['CKSOTPTradingCodeField'] = CKSOTPTradingCodeField


#查询交易所
CKSOTPQryExchangeField = {}
#交易所代码
CKSOTPQryExchangeField["ExchangeID"] = "string"
structDict['CKSOTPQryExchangeField'] = CKSOTPQryExchangeField


#交易所
CKSOTPExchangeField = {}
#交易所代码
CKSOTPExchangeField["ExchangeID"] = "string"
#交易所名称
CKSOTPExchangeField["ExchangeName"] = "string"
structDict['CKSOTPExchangeField'] = CKSOTPExchangeField


#查询合约
CKSOTPQryInstrumentField = {}
#合约代码
CKSOTPQryInstrumentField["InstrumentID"] = "string"
#交易所代码
CKSOTPQryInstrumentField["ExchangeID"] = "string"
structDict['CKSOTPQryInstrumentField'] = CKSOTPQryInstrumentField


#合约
CKSOTPInstrumentField = {}
#合约代码
CKSOTPInstrumentField["InstrumentID"] = "string"
#交易所代码
CKSOTPInstrumentField["ExchangeID"] = "string"
#合约名称
CKSOTPInstrumentField["InstrumentName"] = "string"
#合约在交易所的代码
CKSOTPInstrumentField["ExchangeInstID"] = "string"
#品种代码
CKSOTPInstrumentField["ProductID"] = "string"
#产品类型
CKSOTPInstrumentField["ProductClass"] = "string"
#交割年份
CKSOTPInstrumentField["DeliveryYear"] = "int"
#交割月
CKSOTPInstrumentField["DeliveryMonth"] = "int"
#市价单最大下单量
CKSOTPInstrumentField["MaxMarketOrderVolume"] = "int"
#市价单最小下单量
CKSOTPInstrumentField["MinMarketOrderVolume"] = "int"
#限价单最大下单量
CKSOTPInstrumentField["MaxLimitOrderVolume"] = "int"
#限价单最小下单量
CKSOTPInstrumentField["MinLimitOrderVolume"] = "int"
#合约数量乘数
CKSOTPInstrumentField["VolumeMultiple"] = "int"
#最小变动价位
CKSOTPInstrumentField["PriceTick"] = "float"
#创建日
CKSOTPInstrumentField["CreateDate"] = "string"
#上市日
CKSOTPInstrumentField["OpenDate"] = "string"
#到期日
CKSOTPInstrumentField["ExpireDate"] = "string"
#开始交割日
CKSOTPInstrumentField["StartDelivDate"] = "string"
#结束交割日
CKSOTPInstrumentField["EndDelivDate"] = "string"
#合约生命周期状态
CKSOTPInstrumentField["InstLifePhase"] = "string"
#当前是否交易
CKSOTPInstrumentField["IsTrading"] = "int"
#持仓类型
CKSOTPInstrumentField["PositionType"] = "string"
#持仓日期类型
CKSOTPInstrumentField["PositionDateType"] = "string"
#多头保证金率
CKSOTPInstrumentField["LongMarginRatio"] = "float"
#空头保证金率
CKSOTPInstrumentField["ShortMarginRatio"] = "float"
#基础商品代码
CKSOTPInstrumentField["UnderlyingInstrID"] = "string"
#执行价
CKSOTPInstrumentField["StrikePrice"] = "float"
#期权类型
CKSOTPInstrumentField["OptionsType"] = "string"
#合约基础商品乘数
CKSOTPInstrumentField["UnderlyingMultiple"] = "float"
#合约标识码
CKSOTPInstrumentField["InstrumentCode"] = "string"
structDict['CKSOTPInstrumentField'] = CKSOTPInstrumentField


#查询投资者持仓明细
CKSOTPQryInvestorPositionDetailField = {}
#经纪公司代码
CKSOTPQryInvestorPositionDetailField["BrokerID"] = "string"
#投资者代码
CKSOTPQryInvestorPositionDetailField["InvestorID"] = "string"
#合约代码
CKSOTPQryInvestorPositionDetailField["InstrumentID"] = "string"
#交易所代码
CKSOTPQryInvestorPositionDetailField["ExchangeID"] = "string"
structDict['CKSOTPQryInvestorPositionDetailField'] = CKSOTPQryInvestorPositionDetailField


#投资者持仓明细
CKSOTPInvestorPositionDetailField = {}
#合约代码
CKSOTPInvestorPositionDetailField["InstrumentID"] = "string"
#经纪公司代码
CKSOTPInvestorPositionDetailField["BrokerID"] = "string"
#投资者代码
CKSOTPInvestorPositionDetailField["InvestorID"] = "string"
#备兑标志
CKSOTPInvestorPositionDetailField["HedgeFlag"] = "string"
#买卖
CKSOTPInvestorPositionDetailField["Direction"] = "string"
#开仓日期
CKSOTPInvestorPositionDetailField["OpenDate"] = "string"
#成交编号
CKSOTPInvestorPositionDetailField["TradeID"] = "string"
#数量
CKSOTPInvestorPositionDetailField["Volume"] = "int"
#开仓价
CKSOTPInvestorPositionDetailField["OpenPrice"] = "float"
#交易日
CKSOTPInvestorPositionDetailField["TradingDay"] = "string"
#结算编号
CKSOTPInvestorPositionDetailField["SettlementID"] = "int"
#成交类型
CKSOTPInvestorPositionDetailField["TradeType"] = "string"
#交易所代码
CKSOTPInvestorPositionDetailField["ExchangeID"] = "string"
#逐日盯市平仓盈亏
CKSOTPInvestorPositionDetailField["CloseProfitByDate"] = "float"
#逐笔对冲平仓盈亏
CKSOTPInvestorPositionDetailField["CloseProfitByTrade"] = "float"
#逐日盯市持仓盈亏
CKSOTPInvestorPositionDetailField["PositionProfitByDate"] = "float"
#逐笔对冲持仓盈亏
CKSOTPInvestorPositionDetailField["PositionProfitByTrade"] = "float"
#投资者保证金
CKSOTPInvestorPositionDetailField["Margin"] = "float"
#交易所保证金
CKSOTPInvestorPositionDetailField["ExchMargin"] = "float"
#保证金率
CKSOTPInvestorPositionDetailField["MarginRateByMoney"] = "float"
#保证金率(按手数)
CKSOTPInvestorPositionDetailField["MarginRateByVolume"] = "float"
#昨结算价
CKSOTPInvestorPositionDetailField["LastSettlementPrice"] = "float"
#结算价
CKSOTPInvestorPositionDetailField["SettlementPrice"] = "float"
structDict['CKSOTPInvestorPositionDetailField'] = CKSOTPInvestorPositionDetailField


#查询交易事件通知
CKSOTPQryTradingNoticeField = {}
#经纪公司代码
CKSOTPQryTradingNoticeField["BrokerID"] = "string"
#投资者代码
CKSOTPQryTradingNoticeField["InvestorID"] = "string"
structDict['CKSOTPQryTradingNoticeField'] = CKSOTPQryTradingNoticeField


#用户事件通知
CKSOTPTradingNoticeField = {}
#经纪公司代码
CKSOTPTradingNoticeField["BrokerID"] = "string"
#投资者代码
CKSOTPTradingNoticeField["InvestorID"] = "string"
#序列系列号
CKSOTPTradingNoticeField["SequenceSeries"] = "int"
#用户代码
CKSOTPTradingNoticeField["UserID"] = "string"
#发送时间
CKSOTPTradingNoticeField["SendTime"] = "string"
#序列号
CKSOTPTradingNoticeField["SequenceNo"] = "int"
#消息正文
CKSOTPTradingNoticeField["FieldContent"] = "string"
structDict['CKSOTPTradingNoticeField'] = CKSOTPTradingNoticeField


#用户事件通知信息
CKSOTPTradingNoticeInfoField = {}
#经纪公司代码
CKSOTPTradingNoticeInfoField["BrokerID"] = "string"
#投资者代码
CKSOTPTradingNoticeInfoField["InvestorID"] = "string"
#发送时间
CKSOTPTradingNoticeInfoField["SendTime"] = "string"
#消息正文
CKSOTPTradingNoticeInfoField["FieldContent"] = "string"
#序列系列号
CKSOTPTradingNoticeInfoField["SequenceSeries"] = "int"
#序列号
CKSOTPTradingNoticeInfoField["SequenceNo"] = "int"
structDict['CKSOTPTradingNoticeInfoField'] = CKSOTPTradingNoticeInfoField


#输入的执行宣告
CKSOTPInputExecOrderField = {}
#经纪公司代码
CKSOTPInputExecOrderField["BrokerID"] = "string"
#投资者代码
CKSOTPInputExecOrderField["InvestorID"] = "string"
#合约代码
CKSOTPInputExecOrderField["InstrumentID"] = "string"
#执行宣告引用
CKSOTPInputExecOrderField["ExecOrderRef"] = "string"
#用户代码
CKSOTPInputExecOrderField["UserID"] = "string"
#数量
CKSOTPInputExecOrderField["Volume"] = "int"
#请求编号
CKSOTPInputExecOrderField["RequestID"] = "int"
#业务单元
CKSOTPInputExecOrderField["BusinessUnit"] = "string"
#开平标志
CKSOTPInputExecOrderField["OffsetFlag"] = "string"
#投机套保标志
CKSOTPInputExecOrderField["HedgeFlag"] = "string"
#执行类型
CKSOTPInputExecOrderField["ActionType"] = "string"
#保留头寸申请的持仓方向
CKSOTPInputExecOrderField["PosiDirection"] = "string"
#期权行权后是否保留期货头寸的标记
CKSOTPInputExecOrderField["ReservePositionFlag"] = "string"
#期权行权后生成的头寸是否自动平仓
CKSOTPInputExecOrderField["CloseFlag"] = "string"
#交易所代码
CKSOTPInputExecOrderField["ExchangeID"] = "string"
structDict['CKSOTPInputExecOrderField'] = CKSOTPInputExecOrderField


#输入执行宣告操作
CKSOTPInputExecOrderActionField = {}
#经纪公司代码
CKSOTPInputExecOrderActionField["BrokerID"] = "string"
#投资者代码
CKSOTPInputExecOrderActionField["InvestorID"] = "string"
#执行宣告操作引用
CKSOTPInputExecOrderActionField["ExecOrderActionRef"] = "int"
#执行宣告引用
CKSOTPInputExecOrderActionField["ExecOrderRef"] = "string"
#请求编号
CKSOTPInputExecOrderActionField["RequestID"] = "int"
#前置编号
CKSOTPInputExecOrderActionField["FrontID"] = "int"
#会话编号
CKSOTPInputExecOrderActionField["SessionID"] = "int"
#交易所代码
CKSOTPInputExecOrderActionField["ExchangeID"] = "string"
#执行宣告操作编号
CKSOTPInputExecOrderActionField["ExecOrderSysID"] = "string"
#操作标志
CKSOTPInputExecOrderActionField["ActionFlag"] = "string"
#用户代码
CKSOTPInputExecOrderActionField["UserID"] = "string"
#合约代码
CKSOTPInputExecOrderActionField["InstrumentID"] = "string"
structDict['CKSOTPInputExecOrderActionField'] = CKSOTPInputExecOrderActionField


#录入锁定
CKSOTPInputLockField = {}
#经纪公司代码
CKSOTPInputLockField["BrokerID"] = "string"
#投资者代码
CKSOTPInputLockField["InvestorID"] = "string"
#合约代码
CKSOTPInputLockField["InstrumentID"] = "string"
#锁定引用
CKSOTPInputLockField["LockRef"] = "string"
#用户代码
CKSOTPInputLockField["UserID"] = "string"
#数量
CKSOTPInputLockField["Volume"] = "int"
#请求编号
CKSOTPInputLockField["RequestID"] = "int"
#业务单元
CKSOTPInputLockField["BusinessUnit"] = "string"
#锁定类型
CKSOTPInputLockField["LockType"] = "string"
#交易所代码
CKSOTPInputLockField["ExchangeID"] = "string"
structDict['CKSOTPInputLockField'] = CKSOTPInputLockField


#锁定
CKSOTPLockField = {}
#经纪公司代码
CKSOTPLockField["BrokerID"] = "string"
#投资者代码
CKSOTPLockField["InvestorID"] = "string"
#合约代码
CKSOTPLockField["InstrumentID"] = "string"
#锁定引用
CKSOTPLockField["LockRef"] = "string"
#用户代码
CKSOTPLockField["UserID"] = "string"
#数量
CKSOTPLockField["Volume"] = "int"
#请求编号
CKSOTPLockField["RequestID"] = "int"
#业务单元
CKSOTPLockField["BusinessUnit"] = "string"
#锁定类型
CKSOTPLockField["LockType"] = "string"
#本地锁定编号
CKSOTPLockField["LockLocalID"] = "string"
#交易所代码
CKSOTPLockField["ExchangeID"] = "string"
#会员代码
CKSOTPLockField["ParticipantID"] = "string"
#客户代码
CKSOTPLockField["ClientID"] = "string"
#合约在交易所的代码
CKSOTPLockField["ExchangeInstID"] = "string"
#交易所交易员代码
CKSOTPLockField["TraderID"] = "string"
#安装编号
CKSOTPLockField["InstallID"] = "int"
#执行宣告提交状态
CKSOTPLockField["OrderSubmitStatus"] = "string"
#报单提示序号
CKSOTPLockField["NotifySequence"] = "int"
#交易日
CKSOTPLockField["TradingDay"] = "string"
#结算编号
CKSOTPLockField["SettlementID"] = "int"
#锁定编号
CKSOTPLockField["LockSysID"] = "string"
#报单日期
CKSOTPLockField["InsertDate"] = "string"
#插入时间
CKSOTPLockField["InsertTime"] = "string"
#撤销时间
CKSOTPLockField["CancelTime"] = "string"
#锁定状态
CKSOTPLockField["LockStatus"] = "string"
#结算会员编号
CKSOTPLockField["ClearingPartID"] = "string"
#序号
CKSOTPLockField["SequenceNo"] = "int"
#前置编号
CKSOTPLockField["FrontID"] = "int"
#会话编号
CKSOTPLockField["SessionID"] = "int"
#用户端产品信息
CKSOTPLockField["UserProductInfo"] = "string"
#状态信息
CKSOTPLockField["StatusMsg"] = "string"
#操作用户代码
CKSOTPLockField["ActiveUserID"] = "string"
#经纪公司报单编号
CKSOTPLockField["BrokerLockSeq"] = "int"
#营业部编号
CKSOTPLockField["BranchID"] = "string"
structDict['CKSOTPLockField'] = CKSOTPLockField


#查询锁定
CKSOTPQryLockField = {}
#经纪公司代码
CKSOTPQryLockField["BrokerID"] = "string"
#投资者代码
CKSOTPQryLockField["InvestorID"] = "string"
#合约代码
CKSOTPQryLockField["InstrumentID"] = "string"
#交易所代码
CKSOTPQryLockField["ExchangeID"] = "string"
#锁定编号
CKSOTPQryLockField["LockSysID"] = "string"
structDict['CKSOTPQryLockField'] = CKSOTPQryLockField


#执行宣告查询
CKSOTPQryExecOrderField = {}
#经纪公司代码
CKSOTPQryExecOrderField["BrokerID"] = "string"
#投资者代码
CKSOTPQryExecOrderField["InvestorID"] = "string"
#合约代码
CKSOTPQryExecOrderField["InstrumentID"] = "string"
#交易所代码
CKSOTPQryExecOrderField["ExchangeID"] = "string"
#执行宣告编号
CKSOTPQryExecOrderField["ExecOrderSysID"] = "string"
structDict['CKSOTPQryExecOrderField'] = CKSOTPQryExecOrderField


#输入查询宣告数量
CKSOTPQryExecOrderVolumeField = {}
#经纪公司代码
CKSOTPQryExecOrderVolumeField["BrokerID"] = "string"
#投资者代码
CKSOTPQryExecOrderVolumeField["InvestorID"] = "string"
#交易所代码
CKSOTPQryExecOrderVolumeField["ExchangeID"] = "string"
#合约代码
CKSOTPQryExecOrderVolumeField["InstrumentID"] = "string"
#产品代码
CKSOTPQryExecOrderVolumeField["ProductID"] = "string"
#投机套保标志
CKSOTPQryExecOrderVolumeField["HedgeFlag"] = "string"
#买卖标志
CKSOTPQryExecOrderVolumeField["Direction"] = "string"
structDict['CKSOTPQryExecOrderVolumeField'] = CKSOTPQryExecOrderVolumeField


#输出查询宣告数量
CKSOTPExecOrderVolumeField = {}
#经纪公司代码
CKSOTPExecOrderVolumeField["BrokerID"] = "string"
#投资者代码
CKSOTPExecOrderVolumeField["InvestorID"] = "string"
#合约代码
CKSOTPExecOrderVolumeField["InstrumentID"] = "string"
#产品代码
CKSOTPExecOrderVolumeField["ProductID"] = "string"
#投机套保标志
CKSOTPExecOrderVolumeField["HedgeFlag"] = "string"
#可申请执行量
CKSOTPExecOrderVolumeField["ExecVolume"] = "int"
#可申请放弃量
CKSOTPExecOrderVolumeField["ActionVolume"] = "int"
#已申请执行量
CKSOTPExecOrderVolumeField["ExecedVolume"] = "int"
#已申请放弃量 
CKSOTPExecOrderVolumeField["ActionedVolume"] = "int"
#买卖标志
CKSOTPExecOrderVolumeField["Direction"] = "string"
structDict['CKSOTPExecOrderVolumeField'] = CKSOTPExecOrderVolumeField


#查询锁定证券仓位
CKSOTPQryLockPositionField = {}
#经纪公司代码
CKSOTPQryLockPositionField["BrokerID"] = "string"
#投资者代码
CKSOTPQryLockPositionField["InvestorID"] = "string"
#合约代码
CKSOTPQryLockPositionField["InstrumentID"] = "string"
#交易所代码
CKSOTPQryLockPositionField["ExchangeID"] = "string"
structDict['CKSOTPQryLockPositionField'] = CKSOTPQryLockPositionField


#锁定证券仓位
CKSOTPLockPositionField = {}
#经纪公司代码
CKSOTPLockPositionField["BrokerID"] = "string"
#投资者代码
CKSOTPLockPositionField["InvestorID"] = "string"
#合约代码
CKSOTPLockPositionField["InstrumentID"] = "string"
#交易所代码
CKSOTPLockPositionField["ExchangeID"] = "string"
#数量
CKSOTPLockPositionField["Volume"] = "int"
#已锁定数量
CKSOTPLockPositionField["FrozenVolume"] = "int"
structDict['CKSOTPLockPositionField'] = CKSOTPLockPositionField


#输入查询标的券信息请求
CKSOTPQryUnderlyingStockInfoField = {}
#经纪公司代码
CKSOTPQryUnderlyingStockInfoField["BrokerID"] = "string"
#交易所代码
CKSOTPQryUnderlyingStockInfoField["ExchangeID"] = "string"
#品种代码
CKSOTPQryUnderlyingStockInfoField["ProductID"] = "string"
structDict['CKSOTPQryUnderlyingStockInfoField'] = CKSOTPQryUnderlyingStockInfoField


#输出查询标的券信息请求
CKSOTPUnderlyingStockInfoField = {}
#经纪公司代码
CKSOTPUnderlyingStockInfoField["BrokerID"] = "string"
#交易所代码
CKSOTPUnderlyingStockInfoField["ExchangeID"] = "string"
#品种代码
CKSOTPUnderlyingStockInfoField["ProductID"] = "string"
#昨收盘
CKSOTPUnderlyingStockInfoField["PreClosePrice"] = "float"
#安全系数
CKSOTPUnderlyingStockInfoField["GuarantRatio"] = "float"
structDict['CKSOTPUnderlyingStockInfoField'] = CKSOTPUnderlyingStockInfoField


#输入查询个股期权手续费率请求
CKSOTPQryOTPInsCommRateField = {}
#经纪公司代码
CKSOTPQryOTPInsCommRateField["BrokerID"] = "string"
#投资者代码
CKSOTPQryOTPInsCommRateField["InvestorID"] = "string"
#合约代码
CKSOTPQryOTPInsCommRateField["InstrumentID"] = "string"
#交易所代码
CKSOTPQryOTPInsCommRateField["ExchangeID"] = "string"
structDict['CKSOTPQryOTPInsCommRateField'] = CKSOTPQryOTPInsCommRateField


#输出查询个股期权合约手续费率
CKSOTPOTPInsCommRateField = {}
#合约代码
CKSOTPOTPInsCommRateField["InstrumentID"] = "string"
#投资者范围
CKSOTPOTPInsCommRateField["InvestorRange"] = "string"
#经纪公司代码
CKSOTPOTPInsCommRateField["BrokerID"] = "string"
#投资者代码
CKSOTPOTPInsCommRateField["InvestorID"] = "string"
#开仓手续费率
CKSOTPOTPInsCommRateField["OpenRatioByMoney"] = "float"
#开仓手续费
CKSOTPOTPInsCommRateField["OpenRatioByVolume"] = "float"
#平仓手续费率
CKSOTPOTPInsCommRateField["CloseRatioByMoney"] = "float"
#平仓手续费
CKSOTPOTPInsCommRateField["CloseRatioByVolume"] = "float"
#平今手续费率
CKSOTPOTPInsCommRateField["CloseTodayRatioByMoney"] = "float"
#平今手续费
CKSOTPOTPInsCommRateField["CloseTodayRatioByVolume"] = "float"
#执行手续费率
CKSOTPOTPInsCommRateField["StrikeRatioByMoney"] = "float"
#执行手续费
CKSOTPOTPInsCommRateField["StrikeRatioByVolume"] = "float"
#交易所代码
CKSOTPOTPInsCommRateField["ExchangeID"] = "string"
structDict['CKSOTPOTPInsCommRateField'] = CKSOTPOTPInsCommRateField


#输入查询个股期权合约保证金率请求
CKSOTPQryInstrumentMarginRateField = {}
#经纪公司代码
CKSOTPQryInstrumentMarginRateField["BrokerID"] = "string"
#投资者代码
CKSOTPQryInstrumentMarginRateField["InvestorID"] = "string"
#合约代码
CKSOTPQryInstrumentMarginRateField["InstrumentID"] = "string"
#投机套保标志
CKSOTPQryInstrumentMarginRateField["HedgeFlag"] = "string"
#交易所代码
CKSOTPQryInstrumentMarginRateField["ExchangeID"] = "string"
structDict['CKSOTPQryInstrumentMarginRateField'] = CKSOTPQryInstrumentMarginRateField


#输出查询个股期权合约保证金率
CKSOTPInstrumentMarginRateField = {}
#合约代码
CKSOTPInstrumentMarginRateField["InstrumentID"] = "string"
#投资者范围
CKSOTPInstrumentMarginRateField["InvestorRange"] = "string"
#经纪公司代码
CKSOTPInstrumentMarginRateField["BrokerID"] = "string"
#投资者代码
CKSOTPInstrumentMarginRateField["InvestorID"] = "string"
#投机套保标志
CKSOTPInstrumentMarginRateField["HedgeFlag"] = "string"
#多头保证金率
CKSOTPInstrumentMarginRateField["LongMarginRatioByMoney"] = "float"
#多头保证金费
CKSOTPInstrumentMarginRateField["LongMarginRatioByVolume"] = "float"
#空头保证金率
CKSOTPInstrumentMarginRateField["ShortMarginRatioByMoney"] = "float"
#空头保证金费
CKSOTPInstrumentMarginRateField["ShortMarginRatioByVolume"] = "float"
#是否相对交易所收取
CKSOTPInstrumentMarginRateField["IsRelative"] = "int"
#交易所代码
CKSOTPInstrumentMarginRateField["ExchangeID"] = "string"
structDict['CKSOTPInstrumentMarginRateField'] = CKSOTPInstrumentMarginRateField


#输入个股行权指派信息
CKSOTPQryOTPAssignmentField = {}
#经纪公司代码
CKSOTPQryOTPAssignmentField["BrokerID"] = "string"
#投资者代码
CKSOTPQryOTPAssignmentField["InvestorID"] = "string"
#交易所代码
CKSOTPQryOTPAssignmentField["ExchangeID"] = "string"
#合约代码
CKSOTPQryOTPAssignmentField["InstrumentID"] = "string"
#买卖
CKSOTPQryOTPAssignmentField["Direction"] = "string"
structDict['CKSOTPQryOTPAssignmentField'] = CKSOTPQryOTPAssignmentField


#输出个股行权指派信息
CKSOTPOTPAssignmentField = {}
#经纪公司代码
CKSOTPOTPAssignmentField["BrokerID"] = "string"
#投资者代码
CKSOTPOTPAssignmentField["InvestorID"] = "string"
#合约代码
CKSOTPOTPAssignmentField["InstrumentID"] = "string"
#买卖
CKSOTPOTPAssignmentField["Direction"] = "string"
#交易所代码
CKSOTPOTPAssignmentField["ExchangeID"] = "string"
#合约名称
CKSOTPOTPAssignmentField["InstrumentName"] = "string"
#产品代码
CKSOTPOTPAssignmentField["ProductID"] = "string"
#投机套保标志
CKSOTPOTPAssignmentField["HedgeFlag"] = "string"
#上日持仓
CKSOTPOTPAssignmentField["YdPosition"] = "int"
#行权指派合约数量
CKSOTPOTPAssignmentField["AssInsVo"] = "int"
#行权标的证券数量
CKSOTPOTPAssignmentField["AssProVol"] = "int"
#行权指派应付金额
CKSOTPOTPAssignmentField["FeePay"] = "float"
#期权C/P标志
CKSOTPOTPAssignmentField["OptionsType"] = "string"
#行权交收日
CKSOTPOTPAssignmentField["DeliveryDay"] = "string"
#个股合约标识码
CKSOTPOTPAssignmentField["StockID"] = "string"
structDict['CKSOTPOTPAssignmentField'] = CKSOTPOTPAssignmentField


#查询行情
CKSOTPQryDepthMarketDataField = {}
#合约代码
CKSOTPQryDepthMarketDataField["InstrumentID"] = "string"
#交易所代码
CKSOTPQryDepthMarketDataField["ExchangeID"] = "string"
structDict['CKSOTPQryDepthMarketDataField'] = CKSOTPQryDepthMarketDataField


#深度行情
CKSOTPDepthMarketDataField = {}
#交易日
CKSOTPDepthMarketDataField["TradingDay"] = "string"
#合约代码
CKSOTPDepthMarketDataField["InstrumentID"] = "string"
#交易所代码
CKSOTPDepthMarketDataField["ExchangeID"] = "string"
#合约在交易所的代码
CKSOTPDepthMarketDataField["ExchangeInstID"] = "string"
#最新价
CKSOTPDepthMarketDataField["LastPrice"] = "float"
#上次结算价
CKSOTPDepthMarketDataField["PreSettlementPrice"] = "float"
#昨收盘
CKSOTPDepthMarketDataField["PreClosePrice"] = "float"
#昨持仓量
CKSOTPDepthMarketDataField["PreOpenInterest"] = "float"
#今开盘
CKSOTPDepthMarketDataField["OpenPrice"] = "float"
#最高价
CKSOTPDepthMarketDataField["HighestPrice"] = "float"
#最低价
CKSOTPDepthMarketDataField["LowestPrice"] = "float"
#数量
CKSOTPDepthMarketDataField["Volume"] = "int"
#成交金额
CKSOTPDepthMarketDataField["Turnover"] = "float"
#持仓量
CKSOTPDepthMarketDataField["OpenInterest"] = "float"
#今收盘
CKSOTPDepthMarketDataField["ClosePrice"] = "float"
#本次结算价
CKSOTPDepthMarketDataField["SettlementPrice"] = "float"
#涨停板价
CKSOTPDepthMarketDataField["UpperLimitPrice"] = "float"
#跌停板价
CKSOTPDepthMarketDataField["LowerLimitPrice"] = "float"
#昨虚实度
CKSOTPDepthMarketDataField["PreDelta"] = "float"
#今虚实度
CKSOTPDepthMarketDataField["CurrDelta"] = "float"
#最后修改时间
CKSOTPDepthMarketDataField["UpdateTime"] = "string"
#最后修改毫秒
CKSOTPDepthMarketDataField["UpdateMillisec"] = "int"
#申买价一
CKSOTPDepthMarketDataField["BidPrice1"] = "float"
#申买量一
CKSOTPDepthMarketDataField["BidVolume1"] = "int"
#申卖价一
CKSOTPDepthMarketDataField["AskPrice1"] = "float"
#申卖量一
CKSOTPDepthMarketDataField["AskVolume1"] = "int"
#申买价二
CKSOTPDepthMarketDataField["BidPrice2"] = "float"
#申买量二
CKSOTPDepthMarketDataField["BidVolume2"] = "int"
#申卖价二
CKSOTPDepthMarketDataField["AskPrice2"] = "float"
#申卖量二
CKSOTPDepthMarketDataField["AskVolume2"] = "int"
#申买价三
CKSOTPDepthMarketDataField["BidPrice3"] = "float"
#申买量三
CKSOTPDepthMarketDataField["BidVolume3"] = "int"
#申卖价三
CKSOTPDepthMarketDataField["AskPrice3"] = "float"
#申卖量三
CKSOTPDepthMarketDataField["AskVolume3"] = "int"
#申买价四
CKSOTPDepthMarketDataField["BidPrice4"] = "float"
#申买量四
CKSOTPDepthMarketDataField["BidVolume4"] = "int"
#申卖价四
CKSOTPDepthMarketDataField["AskPrice4"] = "float"
#申卖量四
CKSOTPDepthMarketDataField["AskVolume4"] = "int"
#申买价五
CKSOTPDepthMarketDataField["BidPrice5"] = "float"
#申买量五
CKSOTPDepthMarketDataField["BidVolume5"] = "int"
#申卖价五
CKSOTPDepthMarketDataField["AskPrice5"] = "float"
#申卖量五
CKSOTPDepthMarketDataField["AskVolume5"] = "int"
#当日均价
CKSOTPDepthMarketDataField["AveragePrice"] = "float"
#业务日期
CKSOTPDepthMarketDataField["ActionDay"] = "string"
structDict['CKSOTPDepthMarketDataField'] = CKSOTPDepthMarketDataField


#发给做市商的询价请求
CKSOTPForQuoteRspField = {}
#交易日
CKSOTPForQuoteRspField["TradingDay"] = "string"
#合约代码
CKSOTPForQuoteRspField["InstrumentID"] = "string"
#询价编号
CKSOTPForQuoteRspField["ForQuoteSysID"] = "string"
#询价时间
CKSOTPForQuoteRspField["ForQuoteTime"] = "string"
#业务日期
CKSOTPForQuoteRspField["ActionDay"] = "string"
#交易所代码
CKSOTPForQuoteRspField["ExchangeID"] = "string"
structDict['CKSOTPForQuoteRspField'] = CKSOTPForQuoteRspField


#报单
CKSOTPOrderField = {}
#经纪公司代码
CKSOTPOrderField["BrokerID"] = "string"
#投资者代码
CKSOTPOrderField["InvestorID"] = "string"
#合约代码
CKSOTPOrderField["InstrumentID"] = "string"
#报单引用
CKSOTPOrderField["OrderRef"] = "string"
#用户代码
CKSOTPOrderField["UserID"] = "string"
#报单价格条件
CKSOTPOrderField["OrderPriceType"] = "string"
#买卖方向
CKSOTPOrderField["Direction"] = "string"
#开平标志
CKSOTPOrderField["OffsetFlag"] = "string"
#价格
CKSOTPOrderField["LimitPrice"] = "float"
#备兑标志
CKSOTPOrderField["HedgeFlag"] = "string"
#数量
CKSOTPOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CKSOTPOrderField["TimeCondition"] = "string"
#GTD日期
CKSOTPOrderField["GTDDate"] = "string"
#成交量类型
CKSOTPOrderField["VolumeCondition"] = "string"
#最小成交量
CKSOTPOrderField["MinVolume"] = "int"
#触发条件
CKSOTPOrderField["ContingentCondition"] = "string"
#止损价
CKSOTPOrderField["StopPrice"] = "float"
#强平原因
CKSOTPOrderField["ForceCloseReason"] = "string"
#业务单元
CKSOTPOrderField["BusinessUnit"] = "string"
#请求编号
CKSOTPOrderField["RequestID"] = "int"
#本地报单编号
CKSOTPOrderField["OrderLocalID"] = "string"
#交易所代码
CKSOTPOrderField["ExchangeID"] = "string"
#会员代码
CKSOTPOrderField["ParticipantID"] = "string"
#合约账号
CKSOTPOrderField["ClientID"] = "string"
#合约在交易所的代码
CKSOTPOrderField["ExchangeInstID"] = "string"
#交易所交易员代码
CKSOTPOrderField["TraderID"] = "string"
#报单提交状态
CKSOTPOrderField["OrderSubmitStatus"] = "string"
#报单提示序号
CKSOTPOrderField["NotifySequence"] = "int"
#交易日
CKSOTPOrderField["TradingDay"] = "string"
#结算编号
CKSOTPOrderField["SettlementID"] = "int"
#报单编号
CKSOTPOrderField["OrderSysID"] = "string"
#报单来源
CKSOTPOrderField["OrderSource"] = "string"
#报单状态
CKSOTPOrderField["OrderStatus"] = "string"
#报单类型
CKSOTPOrderField["OrderType"] = "string"
#今成交数量
CKSOTPOrderField["VolumeTraded"] = "int"
#剩余数量
CKSOTPOrderField["VolumeTotal"] = "int"
#报单日期
CKSOTPOrderField["InsertDate"] = "string"
#委托时间
CKSOTPOrderField["InsertTime"] = "string"
#激活时间
CKSOTPOrderField["ActiveTime"] = "string"
#最后修改时间
CKSOTPOrderField["UpdateTime"] = "string"
#撤销时间
CKSOTPOrderField["CancelTime"] = "string"
#序号
CKSOTPOrderField["SequenceNo"] = "int"
#前置编号
CKSOTPOrderField["FrontID"] = "int"
#会话编号
CKSOTPOrderField["SessionID"] = "int"
#用户端产品信息
CKSOTPOrderField["UserProductInfo"] = "string"
#状态信息
CKSOTPOrderField["StatusMsg"] = "string"
#用户强评标志
CKSOTPOrderField["UserForceClose"] = "int"
#操作用户代码
CKSOTPOrderField["ActiveUserID"] = "string"
#经纪公司报单编号
CKSOTPOrderField["BrokerOrderSeq"] = "int"
structDict['CKSOTPOrderField'] = CKSOTPOrderField


#成交
CKSOTPTradeField = {}
#经纪公司代码
CKSOTPTradeField["BrokerID"] = "string"
#投资者代码
CKSOTPTradeField["InvestorID"] = "string"
#合约代码
CKSOTPTradeField["InstrumentID"] = "string"
#报单引用
CKSOTPTradeField["OrderRef"] = "string"
#用户代码
CKSOTPTradeField["UserID"] = "string"
#交易所代码
CKSOTPTradeField["ExchangeID"] = "string"
#成交编号
CKSOTPTradeField["TradeID"] = "string"
#买卖方向
CKSOTPTradeField["Direction"] = "string"
#报单编号
CKSOTPTradeField["OrderSysID"] = "string"
#会员代码
CKSOTPTradeField["ParticipantID"] = "string"
#合约账号
CKSOTPTradeField["ClientID"] = "string"
#交易角色
CKSOTPTradeField["TradingRole"] = "string"
#合约在交易所的代码
CKSOTPTradeField["ExchangeInstID"] = "string"
#开平标志
CKSOTPTradeField["OffsetFlag"] = "string"
#备兑标志
CKSOTPTradeField["HedgeFlag"] = "string"
#价格
CKSOTPTradeField["Price"] = "float"
#数量
CKSOTPTradeField["Volume"] = "int"
#成交时期
CKSOTPTradeField["TradeDate"] = "string"
#成交时间
CKSOTPTradeField["TradeTime"] = "string"
#成交类型
CKSOTPTradeField["TradeType"] = "string"
#成交价来源
CKSOTPTradeField["PriceSource"] = "string"
#交易所交易员代码
CKSOTPTradeField["TraderID"] = "string"
#本地报单编号
CKSOTPTradeField["OrderLocalID"] = "string"
#结算会员编号
CKSOTPTradeField["ClearingPartID"] = "string"
#业务单元
CKSOTPTradeField["BusinessUnit"] = "string"
#序号
CKSOTPTradeField["SequenceNo"] = "int"
#交易日
CKSOTPTradeField["TradingDay"] = "string"
#经纪公司报单编号
CKSOTPTradeField["BrokerOrderSeq"] = "int"
#成交来源
CKSOTPTradeField["TradeSource"] = "string"
structDict['CKSOTPTradeField'] = CKSOTPTradeField


#执行宣告
CKSOTPExecOrderField = {}
#经纪公司代码
CKSOTPExecOrderField["BrokerID"] = "string"
#投资者代码
CKSOTPExecOrderField["InvestorID"] = "string"
#合约代码
CKSOTPExecOrderField["InstrumentID"] = "string"
#执行宣告引用
CKSOTPExecOrderField["ExecOrderRef"] = "string"
#用户代码
CKSOTPExecOrderField["UserID"] = "string"
#数量
CKSOTPExecOrderField["Volume"] = "int"
#请求编号
CKSOTPExecOrderField["RequestID"] = "int"
#业务单元
CKSOTPExecOrderField["BusinessUnit"] = "string"
#开平标志
CKSOTPExecOrderField["OffsetFlag"] = "string"
#投机套保标志
CKSOTPExecOrderField["HedgeFlag"] = "string"
#执行类型
CKSOTPExecOrderField["ActionType"] = "string"
#保留头寸申请的持仓方向
CKSOTPExecOrderField["PosiDirection"] = "string"
#期权行权后是否保留期货头寸的标记
CKSOTPExecOrderField["ReservePositionFlag"] = "string"
#期权行权后生成的头寸是否自动平仓
CKSOTPExecOrderField["CloseFlag"] = "string"
#本地执行宣告编号
CKSOTPExecOrderField["ExecOrderLocalID"] = "string"
#交易所代码
CKSOTPExecOrderField["ExchangeID"] = "string"
#会员代码
CKSOTPExecOrderField["ParticipantID"] = "string"
#客户代码
CKSOTPExecOrderField["ClientID"] = "string"
#合约在交易所的代码
CKSOTPExecOrderField["ExchangeInstID"] = "string"
#交易所交易员代码
CKSOTPExecOrderField["TraderID"] = "string"
#安装编号
CKSOTPExecOrderField["InstallID"] = "int"
#执行宣告提交状态
CKSOTPExecOrderField["OrderSubmitStatus"] = "string"
#报单提示序号
CKSOTPExecOrderField["NotifySequence"] = "int"
#交易日
CKSOTPExecOrderField["TradingDay"] = "string"
#结算编号
CKSOTPExecOrderField["SettlementID"] = "int"
#执行宣告编号
CKSOTPExecOrderField["ExecOrderSysID"] = "string"
#报单日期
CKSOTPExecOrderField["InsertDate"] = "string"
#插入时间
CKSOTPExecOrderField["InsertTime"] = "string"
#撤销时间
CKSOTPExecOrderField["CancelTime"] = "string"
#执行结果
CKSOTPExecOrderField["ExecResult"] = "string"
#结算会员编号
CKSOTPExecOrderField["ClearingPartID"] = "string"
#序号
CKSOTPExecOrderField["SequenceNo"] = "int"
#前置编号
CKSOTPExecOrderField["FrontID"] = "int"
#会话编号
CKSOTPExecOrderField["SessionID"] = "int"
#用户端产品信息
CKSOTPExecOrderField["UserProductInfo"] = "string"
#状态信息
CKSOTPExecOrderField["StatusMsg"] = "string"
#操作用户代码
CKSOTPExecOrderField["ActiveUserID"] = "string"
#经纪公司报单编号
CKSOTPExecOrderField["BrokerExecOrderSeq"] = "int"
#营业部编号
CKSOTPExecOrderField["BranchID"] = "string"
structDict['CKSOTPExecOrderField'] = CKSOTPExecOrderField


#合约状态
CKSOTPInstrumentStatusField = {}
#交易所代码
CKSOTPInstrumentStatusField["ExchangeID"] = "string"
#合约在交易所的代码
CKSOTPInstrumentStatusField["ExchangeInstID"] = "string"
#合约代码
CKSOTPInstrumentStatusField["InstrumentID"] = "string"
#合约交易状态
CKSOTPInstrumentStatusField["InstrumentStatus"] = "string"
#交易阶段编号
CKSOTPInstrumentStatusField["TradingSegmentSN"] = "int"
#进入本状态时间
CKSOTPInstrumentStatusField["EnterTime"] = "string"
#进入本状态原因
CKSOTPInstrumentStatusField["EnterReason"] = "string"
structDict['CKSOTPInstrumentStatusField'] = CKSOTPInstrumentStatusField


#转账请求
CKSOTPReqTransferField = {}
#业务功能码
CKSOTPReqTransferField["TradeCode"] = "string"
#银行代码
CKSOTPReqTransferField["BankID"] = "string"
#银行分支机构代码
CKSOTPReqTransferField["BankBranchID"] = "string"
#期商代码
CKSOTPReqTransferField["BrokerID"] = "string"
#期商分支机构代码
CKSOTPReqTransferField["BrokerBranchID"] = "string"
#交易日期
CKSOTPReqTransferField["TradeDate"] = "string"
#交易时间
CKSOTPReqTransferField["TradeTime"] = "string"
#银行流水号
CKSOTPReqTransferField["BankSerial"] = "string"
#交易系统日期 
CKSOTPReqTransferField["TradingDay"] = "string"
#银期平台消息流水号
CKSOTPReqTransferField["PlateSerial"] = "int"
#最后分片标志
CKSOTPReqTransferField["LastFragment"] = "string"
#会话号
CKSOTPReqTransferField["SessionID"] = "int"
#客户姓名
CKSOTPReqTransferField["CustomerName"] = "string"
#证件类型
CKSOTPReqTransferField["IdCardType"] = "string"
#证件号码
CKSOTPReqTransferField["IdentifiedCardNo"] = "string"
#客户类型
CKSOTPReqTransferField["CustType"] = "string"
#银行帐号
CKSOTPReqTransferField["BankAccount"] = "string"
#银行密码
CKSOTPReqTransferField["BankPassWord"] = "string"
#投资者帐号
CKSOTPReqTransferField["AccountID"] = "string"
#证券密码
CKSOTPReqTransferField["Password"] = "string"
#安装编号
CKSOTPReqTransferField["InstallID"] = "int"
#证券公司流水号
CKSOTPReqTransferField["FutureSerial"] = "int"
#用户标识
CKSOTPReqTransferField["UserID"] = "string"
#验证客户证件号码标志
CKSOTPReqTransferField["VerifyCertNoFlag"] = "string"
#币种代码
CKSOTPReqTransferField["CurrencyID"] = "string"
#转帐金额
CKSOTPReqTransferField["TradeAmount"] = "float"
#证券可取金额
CKSOTPReqTransferField["FutureFetchAmount"] = "float"
#费用支付标志
CKSOTPReqTransferField["FeePayFlag"] = "string"
#应收客户费用
CKSOTPReqTransferField["CustFee"] = "float"
#应收证券公司费用
CKSOTPReqTransferField["BrokerFee"] = "float"
#发送方给接收方的消息
CKSOTPReqTransferField["Message"] = "string"
#摘要
CKSOTPReqTransferField["Digest"] = "string"
#银行帐号类型
CKSOTPReqTransferField["BankAccType"] = "string"
#渠道标志
CKSOTPReqTransferField["DeviceID"] = "string"
#证券单位帐号类型
CKSOTPReqTransferField["BankSecuAccType"] = "string"
#证券公司银行编码
CKSOTPReqTransferField["BrokerIDByBank"] = "string"
#证券单位帐号
CKSOTPReqTransferField["BankSecuAcc"] = "string"
#银行密码标志
CKSOTPReqTransferField["BankPwdFlag"] = "string"
#证券资金密码核对标志
CKSOTPReqTransferField["SecuPwdFlag"] = "string"
#交易柜员
CKSOTPReqTransferField["OperNo"] = "string"
#请求编号
CKSOTPReqTransferField["RequestID"] = "int"
#交易ID
CKSOTPReqTransferField["TID"] = "int"
#转账交易状态
CKSOTPReqTransferField["TransferStatus"] = "string"
structDict['CKSOTPReqTransferField'] = CKSOTPReqTransferField


#银行资金转证券响应
CKSOTPRspTransferField = {}
#业务功能码
CKSOTPRspTransferField["TradeCode"] = "string"
#银行代码
CKSOTPRspTransferField["BankID"] = "string"
#银行分支机构代码
CKSOTPRspTransferField["BankBranchID"] = "string"
#期商代码
CKSOTPRspTransferField["BrokerID"] = "string"
#期商分支机构代码
CKSOTPRspTransferField["BrokerBranchID"] = "string"
#交易日期
CKSOTPRspTransferField["TradeDate"] = "string"
#交易时间
CKSOTPRspTransferField["TradeTime"] = "string"
#银行流水号
CKSOTPRspTransferField["BankSerial"] = "string"
#交易系统日期 
CKSOTPRspTransferField["TradingDay"] = "string"
#银期平台消息流水号
CKSOTPRspTransferField["PlateSerial"] = "int"
#最后分片标志
CKSOTPRspTransferField["LastFragment"] = "string"
#会话号
CKSOTPRspTransferField["SessionID"] = "int"
#客户姓名
CKSOTPRspTransferField["CustomerName"] = "string"
#证件类型
CKSOTPRspTransferField["IdCardType"] = "string"
#证件号码
CKSOTPRspTransferField["IdentifiedCardNo"] = "string"
#客户类型
CKSOTPRspTransferField["CustType"] = "string"
#银行帐号
CKSOTPRspTransferField["BankAccount"] = "string"
#银行密码
CKSOTPRspTransferField["BankPassWord"] = "string"
#投资者帐号
CKSOTPRspTransferField["AccountID"] = "string"
#证券密码
CKSOTPRspTransferField["Password"] = "string"
#安装编号
CKSOTPRspTransferField["InstallID"] = "int"
#证券公司流水号
CKSOTPRspTransferField["FutureSerial"] = "int"
#用户标识
CKSOTPRspTransferField["UserID"] = "string"
#验证客户证件号码标志
CKSOTPRspTransferField["VerifyCertNoFlag"] = "string"
#币种代码
CKSOTPRspTransferField["CurrencyID"] = "string"
#转帐金额
CKSOTPRspTransferField["TradeAmount"] = "float"
#证券可取金额
CKSOTPRspTransferField["FutureFetchAmount"] = "float"
#费用支付标志
CKSOTPRspTransferField["FeePayFlag"] = "string"
#应收客户费用
CKSOTPRspTransferField["CustFee"] = "float"
#应收证券公司费用
CKSOTPRspTransferField["BrokerFee"] = "float"
#发送方给接收方的消息
CKSOTPRspTransferField["Message"] = "string"
#摘要
CKSOTPRspTransferField["Digest"] = "string"
#银行帐号类型
CKSOTPRspTransferField["BankAccType"] = "string"
#渠道标志
CKSOTPRspTransferField["DeviceID"] = "string"
#证券单位帐号类型
CKSOTPRspTransferField["BankSecuAccType"] = "string"
#证券公司银行编码
CKSOTPRspTransferField["BrokerIDByBank"] = "string"
#证券单位帐号
CKSOTPRspTransferField["BankSecuAcc"] = "string"
#银行密码标志
CKSOTPRspTransferField["BankPwdFlag"] = "string"
#证券资金密码核对标志
CKSOTPRspTransferField["SecuPwdFlag"] = "string"
#交易柜员
CKSOTPRspTransferField["OperNo"] = "string"
#请求编号
CKSOTPRspTransferField["RequestID"] = "int"
#交易ID
CKSOTPRspTransferField["TID"] = "int"
#转账交易状态
CKSOTPRspTransferField["TransferStatus"] = "string"
#错误代码
CKSOTPRspTransferField["ErrorID"] = "int"
#错误信息
CKSOTPRspTransferField["ErrorMsg"] = "string"
structDict['CKSOTPRspTransferField'] = CKSOTPRspTransferField


#查询签约银行请求
CKSOTPQryContractBankField = {}
#经纪公司代码
CKSOTPQryContractBankField["BrokerID"] = "string"
#银行代码
CKSOTPQryContractBankField["BankID"] = "string"
#银行分中心代码
CKSOTPQryContractBankField["BankBrchID"] = "string"
structDict['CKSOTPQryContractBankField'] = CKSOTPQryContractBankField


#查询签约银行响应
CKSOTPContractBankField = {}
#经纪公司代码
CKSOTPContractBankField["BrokerID"] = "string"
#银行代码
CKSOTPContractBankField["BankID"] = "string"
#银行分中心代码
CKSOTPContractBankField["BankBrchID"] = "string"
#银行名称
CKSOTPContractBankField["BankName"] = "string"
structDict['CKSOTPContractBankField'] = CKSOTPContractBankField


#查询账户信息请求
CKSOTPReqQueryAccountField = {}
#业务功能码
CKSOTPReqQueryAccountField["TradeCode"] = "string"
#银行代码
CKSOTPReqQueryAccountField["BankID"] = "string"
#银行分支机构代码
CKSOTPReqQueryAccountField["BankBranchID"] = "string"
#期商代码
CKSOTPReqQueryAccountField["BrokerID"] = "string"
#期商分支机构代码
CKSOTPReqQueryAccountField["BrokerBranchID"] = "string"
#交易日期
CKSOTPReqQueryAccountField["TradeDate"] = "string"
#交易时间
CKSOTPReqQueryAccountField["TradeTime"] = "string"
#银行流水号
CKSOTPReqQueryAccountField["BankSerial"] = "string"
#交易系统日期 
CKSOTPReqQueryAccountField["TradingDay"] = "string"
#银期平台消息流水号
CKSOTPReqQueryAccountField["PlateSerial"] = "int"
#最后分片标志
CKSOTPReqQueryAccountField["LastFragment"] = "string"
#会话号
CKSOTPReqQueryAccountField["SessionID"] = "int"
#客户姓名
CKSOTPReqQueryAccountField["CustomerName"] = "string"
#证件类型
CKSOTPReqQueryAccountField["IdCardType"] = "string"
#证件号码
CKSOTPReqQueryAccountField["IdentifiedCardNo"] = "string"
#客户类型
CKSOTPReqQueryAccountField["CustType"] = "string"
#银行帐号
CKSOTPReqQueryAccountField["BankAccount"] = "string"
#银行密码
CKSOTPReqQueryAccountField["BankPassWord"] = "string"
#投资者帐号
CKSOTPReqQueryAccountField["AccountID"] = "string"
#证券密码
CKSOTPReqQueryAccountField["Password"] = "string"
#证券公司流水号
CKSOTPReqQueryAccountField["FutureSerial"] = "int"
#安装编号
CKSOTPReqQueryAccountField["InstallID"] = "int"
#用户标识
CKSOTPReqQueryAccountField["UserID"] = "string"
#验证客户证件号码标志
CKSOTPReqQueryAccountField["VerifyCertNoFlag"] = "string"
#币种代码
CKSOTPReqQueryAccountField["CurrencyID"] = "string"
#摘要
CKSOTPReqQueryAccountField["Digest"] = "string"
#银行帐号类型
CKSOTPReqQueryAccountField["BankAccType"] = "string"
#渠道标志
CKSOTPReqQueryAccountField["DeviceID"] = "string"
#证券单位帐号类型
CKSOTPReqQueryAccountField["BankSecuAccType"] = "string"
#证券公司银行编码
CKSOTPReqQueryAccountField["BrokerIDByBank"] = "string"
#证券单位帐号
CKSOTPReqQueryAccountField["BankSecuAcc"] = "string"
#银行密码标志
CKSOTPReqQueryAccountField["BankPwdFlag"] = "string"
#证券资金密码核对标志
CKSOTPReqQueryAccountField["SecuPwdFlag"] = "string"
#交易柜员
CKSOTPReqQueryAccountField["OperNo"] = "string"
#请求编号
CKSOTPReqQueryAccountField["RequestID"] = "int"
#交易ID
CKSOTPReqQueryAccountField["TID"] = "int"
structDict['CKSOTPReqQueryAccountField'] = CKSOTPReqQueryAccountField


#查询账户信息响应
CKSOTPRspQueryAccountField = {}
#业务功能码
CKSOTPRspQueryAccountField["TradeCode"] = "string"
#银行代码
CKSOTPRspQueryAccountField["BankID"] = "string"
#银行分支机构代码
CKSOTPRspQueryAccountField["BankBranchID"] = "string"
#期商代码
CKSOTPRspQueryAccountField["BrokerID"] = "string"
#期商分支机构代码
CKSOTPRspQueryAccountField["BrokerBranchID"] = "string"
#交易日期
CKSOTPRspQueryAccountField["TradeDate"] = "string"
#交易时间
CKSOTPRspQueryAccountField["TradeTime"] = "string"
#银行流水号
CKSOTPRspQueryAccountField["BankSerial"] = "string"
#交易系统日期 
CKSOTPRspQueryAccountField["TradingDay"] = "string"
#银期平台消息流水号
CKSOTPRspQueryAccountField["PlateSerial"] = "int"
#最后分片标志
CKSOTPRspQueryAccountField["LastFragment"] = "string"
#会话号
CKSOTPRspQueryAccountField["SessionID"] = "int"
#客户姓名
CKSOTPRspQueryAccountField["CustomerName"] = "string"
#证件类型
CKSOTPRspQueryAccountField["IdCardType"] = "string"
#证件号码
CKSOTPRspQueryAccountField["IdentifiedCardNo"] = "string"
#客户类型
CKSOTPRspQueryAccountField["CustType"] = "string"
#银行帐号
CKSOTPRspQueryAccountField["BankAccount"] = "string"
#银行密码
CKSOTPRspQueryAccountField["BankPassWord"] = "string"
#投资者帐号
CKSOTPRspQueryAccountField["AccountID"] = "string"
#证券密码
CKSOTPRspQueryAccountField["Password"] = "string"
#证券公司流水号
CKSOTPRspQueryAccountField["FutureSerial"] = "int"
#安装编号
CKSOTPRspQueryAccountField["InstallID"] = "int"
#用户标识
CKSOTPRspQueryAccountField["UserID"] = "string"
#验证客户证件号码标志
CKSOTPRspQueryAccountField["VerifyCertNoFlag"] = "string"
#币种代码
CKSOTPRspQueryAccountField["CurrencyID"] = "string"
#摘要
CKSOTPRspQueryAccountField["Digest"] = "string"
#银行帐号类型
CKSOTPRspQueryAccountField["BankAccType"] = "string"
#渠道标志
CKSOTPRspQueryAccountField["DeviceID"] = "string"
#证券单位帐号类型
CKSOTPRspQueryAccountField["BankSecuAccType"] = "string"
#证券公司银行编码
CKSOTPRspQueryAccountField["BrokerIDByBank"] = "string"
#证券单位帐号
CKSOTPRspQueryAccountField["BankSecuAcc"] = "string"
#银行密码标志
CKSOTPRspQueryAccountField["BankPwdFlag"] = "string"
#证券资金密码核对标志
CKSOTPRspQueryAccountField["SecuPwdFlag"] = "string"
#交易柜员
CKSOTPRspQueryAccountField["OperNo"] = "string"
#请求编号
CKSOTPRspQueryAccountField["RequestID"] = "int"
#交易ID
CKSOTPRspQueryAccountField["TID"] = "int"
#银行可用金额
CKSOTPRspQueryAccountField["BankUseAmount"] = "float"
#银行可取金额
CKSOTPRspQueryAccountField["BankFetchAmount"] = "float"
structDict['CKSOTPRspQueryAccountField'] = CKSOTPRspQueryAccountField


#请求查询转帐流水
CKSOTPQryTransferSerialField = {}
#经纪公司代码
CKSOTPQryTransferSerialField["BrokerID"] = "string"
#投资者帐号
CKSOTPQryTransferSerialField["AccountID"] = "string"
#银行编码
CKSOTPQryTransferSerialField["BankID"] = "string"
#币种代码
CKSOTPQryTransferSerialField["CurrencyID"] = "string"
structDict['CKSOTPQryTransferSerialField'] = CKSOTPQryTransferSerialField


#查询账户信息通知
CKSOTPNotifyQueryAccountField = {}
#业务功能码
CKSOTPNotifyQueryAccountField["TradeCode"] = "string"
#银行代码
CKSOTPNotifyQueryAccountField["BankID"] = "string"
#银行分支机构代码
CKSOTPNotifyQueryAccountField["BankBranchID"] = "string"
#期商代码
CKSOTPNotifyQueryAccountField["BrokerID"] = "string"
#期商分支机构代码
CKSOTPNotifyQueryAccountField["BrokerBranchID"] = "string"
#交易日期
CKSOTPNotifyQueryAccountField["TradeDate"] = "string"
#交易时间
CKSOTPNotifyQueryAccountField["TradeTime"] = "string"
#银行流水号
CKSOTPNotifyQueryAccountField["BankSerial"] = "string"
#交易系统日期 
CKSOTPNotifyQueryAccountField["TradingDay"] = "string"
#银期平台消息流水号
CKSOTPNotifyQueryAccountField["PlateSerial"] = "int"
#最后分片标志
CKSOTPNotifyQueryAccountField["LastFragment"] = "string"
#会话号
CKSOTPNotifyQueryAccountField["SessionID"] = "int"
#客户姓名
CKSOTPNotifyQueryAccountField["CustomerName"] = "string"
#证件类型
CKSOTPNotifyQueryAccountField["IdCardType"] = "string"
#证件号码
CKSOTPNotifyQueryAccountField["IdentifiedCardNo"] = "string"
#客户类型
CKSOTPNotifyQueryAccountField["CustType"] = "string"
#银行帐号
CKSOTPNotifyQueryAccountField["BankAccount"] = "string"
#银行密码
CKSOTPNotifyQueryAccountField["BankPassWord"] = "string"
#投资者帐号
CKSOTPNotifyQueryAccountField["AccountID"] = "string"
#证券密码
CKSOTPNotifyQueryAccountField["Password"] = "string"
#证券公司流水号
CKSOTPNotifyQueryAccountField["FutureSerial"] = "int"
#安装编号
CKSOTPNotifyQueryAccountField["InstallID"] = "int"
#用户标识
CKSOTPNotifyQueryAccountField["UserID"] = "string"
#验证客户证件号码标志
CKSOTPNotifyQueryAccountField["VerifyCertNoFlag"] = "string"
#币种代码
CKSOTPNotifyQueryAccountField["CurrencyID"] = "string"
#摘要
CKSOTPNotifyQueryAccountField["Digest"] = "string"
#银行帐号类型
CKSOTPNotifyQueryAccountField["BankAccType"] = "string"
#渠道标志
CKSOTPNotifyQueryAccountField["DeviceID"] = "string"
#证券单位帐号类型
CKSOTPNotifyQueryAccountField["BankSecuAccType"] = "string"
#证券公司银行编码
CKSOTPNotifyQueryAccountField["BrokerIDByBank"] = "string"
#证券单位帐号
CKSOTPNotifyQueryAccountField["BankSecuAcc"] = "string"
#银行密码标志
CKSOTPNotifyQueryAccountField["BankPwdFlag"] = "string"
#证券资金密码核对标志
CKSOTPNotifyQueryAccountField["SecuPwdFlag"] = "string"
#交易柜员
CKSOTPNotifyQueryAccountField["OperNo"] = "string"
#请求编号
CKSOTPNotifyQueryAccountField["RequestID"] = "int"
#交易ID
CKSOTPNotifyQueryAccountField["TID"] = "int"
#银行可用金额
CKSOTPNotifyQueryAccountField["BankUseAmount"] = "float"
#银行可取金额
CKSOTPNotifyQueryAccountField["BankFetchAmount"] = "float"
#错误代码
CKSOTPNotifyQueryAccountField["ErrorID"] = "int"
#错误信息
CKSOTPNotifyQueryAccountField["ErrorMsg"] = "string"
structDict['CKSOTPNotifyQueryAccountField'] = CKSOTPNotifyQueryAccountField


#银期转账交易流水表
CKSOTPTransferSerialField = {}
#平台流水号
CKSOTPTransferSerialField["PlateSerial"] = "int"
#交易发起方日期
CKSOTPTransferSerialField["TradeDate"] = "string"
#交易日期
CKSOTPTransferSerialField["TradingDay"] = "string"
#交易时间
CKSOTPTransferSerialField["TradeTime"] = "string"
#交易代码
CKSOTPTransferSerialField["TradeCode"] = "string"
#会话编号
CKSOTPTransferSerialField["SessionID"] = "int"
#银行编码
CKSOTPTransferSerialField["BankID"] = "string"
#银行分支机构编码
CKSOTPTransferSerialField["BankBranchID"] = "string"
#银行帐号类型
CKSOTPTransferSerialField["BankAccType"] = "string"
#银行帐号
CKSOTPTransferSerialField["BankAccount"] = "string"
#银行流水号
CKSOTPTransferSerialField["BankSerial"] = "string"
#证券公司编码
CKSOTPTransferSerialField["BrokerID"] = "string"
#期商分支机构代码
CKSOTPTransferSerialField["BrokerBranchID"] = "string"
#证券公司帐号类型
CKSOTPTransferSerialField["FutureAccType"] = "string"
#投资者帐号
CKSOTPTransferSerialField["AccountID"] = "string"
#投资者代码
CKSOTPTransferSerialField["InvestorID"] = "string"
#证券公司流水号
CKSOTPTransferSerialField["FutureSerial"] = "int"
#证件类型
CKSOTPTransferSerialField["IdCardType"] = "string"
#证件号码
CKSOTPTransferSerialField["IdentifiedCardNo"] = "string"
#币种代码
CKSOTPTransferSerialField["CurrencyID"] = "string"
#交易金额
CKSOTPTransferSerialField["TradeAmount"] = "float"
#应收客户费用
CKSOTPTransferSerialField["CustFee"] = "float"
#应收证券公司费用
CKSOTPTransferSerialField["BrokerFee"] = "float"
#有效标志
CKSOTPTransferSerialField["AvailabilityFlag"] = "string"
#操作员
CKSOTPTransferSerialField["OperatorCode"] = "string"
#新银行帐号
CKSOTPTransferSerialField["BankNewAccount"] = "string"
#错误代码
CKSOTPTransferSerialField["ErrorID"] = "int"
#错误信息
CKSOTPTransferSerialField["ErrorMsg"] = "string"
structDict['CKSOTPTransferSerialField'] = CKSOTPTransferSerialField


#指定的合约
CKSOTPSpecificInstrumentField = {}
#合约代码
CKSOTPSpecificInstrumentField["InstrumentID"] = "string"
#交易所代码
CKSOTPSpecificInstrumentField["ExchangeID"] = "string"
structDict['CKSOTPSpecificInstrumentField'] = CKSOTPSpecificInstrumentField


#查询客户交易级别
CKSOTPQryInvestorTradeLevelField = {}
#经纪公司代码
CKSOTPQryInvestorTradeLevelField["BrokerID"] = "string"
#交易所代码
CKSOTPQryInvestorTradeLevelField["ExchangeID"] = "string"
#产品代码
CKSOTPQryInvestorTradeLevelField["ProductID"] = "string"
structDict['CKSOTPQryInvestorTradeLevelField'] = CKSOTPQryInvestorTradeLevelField


#客户交易级别
CKSOTPInvestorTradeLevelField = {}
#经纪公司代码
CKSOTPInvestorTradeLevelField["BrokerID"] = "string"
#投资者代码
CKSOTPInvestorTradeLevelField["InvestorID"] = "string"
#交易所代码
CKSOTPInvestorTradeLevelField["ExchangeID"] = "string"
#产品代码
CKSOTPInvestorTradeLevelField["ProductID"] = "string"
#交易级别
CKSOTPInvestorTradeLevelField["TradeLevel"] = "string"
structDict['CKSOTPInvestorTradeLevelField'] = CKSOTPInvestorTradeLevelField


#查询个股限购额度
CKSOTPQryPurchaseLimitAmtField = {}
#经纪公司代码
CKSOTPQryPurchaseLimitAmtField["BrokerID"] = "string"
#交易所代码
CKSOTPQryPurchaseLimitAmtField["ExchangeID"] = "string"
structDict['CKSOTPQryPurchaseLimitAmtField'] = CKSOTPQryPurchaseLimitAmtField


#个股限购额度
CKSOTPPurchaseLimitAmtField = {}
#经纪公司代码
CKSOTPPurchaseLimitAmtField["BrokerID"] = "string"
#投资者代码
CKSOTPPurchaseLimitAmtField["InvestorID"] = "string"
#交易所代码
CKSOTPPurchaseLimitAmtField["ExchangeID"] = "string"
#限购额度
CKSOTPPurchaseLimitAmtField["PurLimitAmt"] = "float"
structDict['CKSOTPPurchaseLimitAmtField'] = CKSOTPPurchaseLimitAmtField


#查询个股限仓额度
CKSOTPQryPositionLimitVolField = {}
#经纪公司代码
CKSOTPQryPositionLimitVolField["BrokerID"] = "string"
#交易所代码
CKSOTPQryPositionLimitVolField["ExchangeID"] = "string"
#产品代码
CKSOTPQryPositionLimitVolField["ProductID"] = "string"
#保护性标志
CKSOTPQryPositionLimitVolField["ProtectFlag"] = "string"
#期权C/P标志
CKSOTPQryPositionLimitVolField["OptionsType"] = "string"
#控制范围
CKSOTPQryPositionLimitVolField["ControlRange"] = "string"
structDict['CKSOTPQryPositionLimitVolField'] = CKSOTPQryPositionLimitVolField


#查询个股限仓额度
CKSOTPPositionLimitVolField = {}
#经纪公司代码
CKSOTPPositionLimitVolField["BrokerID"] = "string"
#投资者代码
CKSOTPPositionLimitVolField["InvestorID"] = "string"
#交易所代码
CKSOTPPositionLimitVolField["ExchangeID"] = "string"
#产品代码
CKSOTPPositionLimitVolField["ProductID"] = "string"
#保护性标志
CKSOTPPositionLimitVolField["ProtectFlag"] = "string"
#期权C/P标志
CKSOTPPositionLimitVolField["OptionsType"] = "string"
#控制范围
CKSOTPPositionLimitVolField["ControlRange"] = "string"
#限仓额度
CKSOTPPositionLimitVolField["PosiLimitVol"] = "int"
structDict['CKSOTPPositionLimitVolField'] = CKSOTPPositionLimitVolField


#查询投资者结算结果
CKSOTPQrySettlementInfoField = {}
#经纪公司代码
CKSOTPQrySettlementInfoField["BrokerID"] = "string"
#投资者代码
CKSOTPQrySettlementInfoField["InvestorID"] = "string"
#交易日
CKSOTPQrySettlementInfoField["TradingDay"] = "string"
structDict['CKSOTPQrySettlementInfoField'] = CKSOTPQrySettlementInfoField


#查询结算信息确认域
CKSOTPQrySettlementInfoConfirmField = {}
#经纪公司代码
CKSOTPQrySettlementInfoConfirmField["BrokerID"] = "string"
#投资者代码
CKSOTPQrySettlementInfoConfirmField["InvestorID"] = "string"
structDict['CKSOTPQrySettlementInfoConfirmField'] = CKSOTPQrySettlementInfoConfirmField


#投资者结算结果确认信息
CKSOTPSettlementInfoConfirmField = {}
#经纪公司代码
CKSOTPSettlementInfoConfirmField["BrokerID"] = "string"
#投资者代码
CKSOTPSettlementInfoConfirmField["InvestorID"] = "string"
#确认日期
CKSOTPSettlementInfoConfirmField["ConfirmDate"] = "string"
#确认时间
CKSOTPSettlementInfoConfirmField["ConfirmTime"] = "string"
structDict['CKSOTPSettlementInfoConfirmField'] = CKSOTPSettlementInfoConfirmField


#投资者结算结果
CKSOTPSettlementInfoField = {}
#交易日
CKSOTPSettlementInfoField["TradingDay"] = "string"
#结算编号
CKSOTPSettlementInfoField["SettlementID"] = "int"
#经纪公司代码
CKSOTPSettlementInfoField["BrokerID"] = "string"
#投资者代码
CKSOTPSettlementInfoField["InvestorID"] = "string"
#序号
CKSOTPSettlementInfoField["SequenceNo"] = "int"
#消息正文
CKSOTPSettlementInfoField["Content"] = "string"
structDict['CKSOTPSettlementInfoField'] = CKSOTPSettlementInfoField


#查询历史报单
CKSOTPQryHistoryOrderField = {}
#经纪公司代码
CKSOTPQryHistoryOrderField["BrokerID"] = "string"
#投资者代码
CKSOTPQryHistoryOrderField["InvestorID"] = "string"
#合约代码
CKSOTPQryHistoryOrderField["InstrumentID"] = "string"
#本地报单编号
CKSOTPQryHistoryOrderField["OrderLocalID"] = "string"
#品种代码
CKSOTPQryHistoryOrderField["ProductID"] = "string"
#开始日期
CKSOTPQryHistoryOrderField["OrderDataStart"] = "string"
#结束日期
CKSOTPQryHistoryOrderField["OrderDataEnd"] = "string"
structDict['CKSOTPQryHistoryOrderField'] = CKSOTPQryHistoryOrderField


#查询历史成交
CKSOTPQryHistoryTradeField = {}
#经纪公司代码
CKSOTPQryHistoryTradeField["BrokerID"] = "string"
#投资者代码
CKSOTPQryHistoryTradeField["InvestorID"] = "string"
#品种代码
CKSOTPQryHistoryTradeField["ProductID"] = "string"
#开始日期
CKSOTPQryHistoryTradeField["TradeDataStart"] = "string"
#结束日期
CKSOTPQryHistoryTradeField["TradeDataEnd"] = "string"
structDict['CKSOTPQryHistoryTradeField'] = CKSOTPQryHistoryTradeField


#查询历史行权指派明细
CKSOTPQryHistoryAssignmentField = {}
#经纪公司代码
CKSOTPQryHistoryAssignmentField["BrokerID"] = "string"
#投资者代码
CKSOTPQryHistoryAssignmentField["InvestorID"] = "string"
#交易所代码
CKSOTPQryHistoryAssignmentField["ExchangeID"] = "string"
#产品代码
CKSOTPQryHistoryAssignmentField["ProductID"] = "string"
#合约代码
CKSOTPQryHistoryAssignmentField["InstrumentID"] = "string"
#投保标记
CKSOTPQryHistoryAssignmentField["HedgeFlag"] = "string"
#期权类型
CKSOTPQryHistoryAssignmentField["OptionsType"] = "string"
#交割月
CKSOTPQryHistoryAssignmentField["DeliveryMonth"] = "string"
#持仓方向
CKSOTPQryHistoryAssignmentField["PosiDirection"] = "string"
structDict['CKSOTPQryHistoryAssignmentField'] = CKSOTPQryHistoryAssignmentField


#查询行权交割明细
CKSOTPQryDelivDetailField = {}
#经纪公司代码
CKSOTPQryDelivDetailField["BrokerID"] = "string"
#投资者代码
CKSOTPQryDelivDetailField["InvestorID"] = "string"
#交易所代码
CKSOTPQryDelivDetailField["ExchangeID"] = "string"
#产品代码
CKSOTPQryDelivDetailField["ProductID"] = "string"
#交割月
CKSOTPQryDelivDetailField["DeliveryMonth"] = "string"
#个股交收查询类型
CKSOTPQryDelivDetailField["DelivMode"] = "string"
structDict['CKSOTPQryDelivDetailField'] = CKSOTPQryDelivDetailField


#自动行权执行操作
CKSOTPAutoExecOrderActionField = {}
#经纪公司代码
CKSOTPAutoExecOrderActionField["BrokerID"] = "string"
#投资者代码
CKSOTPAutoExecOrderActionField["InvestorID"] = "string"
#自动行权阈值(0-不自动行权,非0-代表超过阀值会自动行权(20代表20%))
CKSOTPAutoExecOrderActionField["RangeVol"] = "int"
structDict['CKSOTPAutoExecOrderActionField'] = CKSOTPAutoExecOrderActionField


#历史行权指派明细
CKSOTPHistoryAssignmentField = {}
#经纪公司代码
CKSOTPHistoryAssignmentField["BrokerID"] = "string"
#投资者代码
CKSOTPHistoryAssignmentField["InvestorID"] = "string"
#交易日期
CKSOTPHistoryAssignmentField["TradingDay"] = "string"
#产品代码
CKSOTPHistoryAssignmentField["ProductID"] = "string"
#合约代码
CKSOTPHistoryAssignmentField["InstrumentID"] = "string"
#客户代码
CKSOTPHistoryAssignmentField["ClientID"] = "string"
#标的证券代码
CKSOTPHistoryAssignmentField["StockInstr"] = "string"
#投保标记
CKSOTPHistoryAssignmentField["HedgeFlag"] = "string"
#期权类型
CKSOTPHistoryAssignmentField["OptionsType"] = "string"
#持仓方向
CKSOTPHistoryAssignmentField["PosiDirection"] = "string"
#执行价
CKSOTPHistoryAssignmentField["StrikePrice"] = "float"
#行权指派数量
CKSOTPHistoryAssignmentField["ExecVol"] = "int"
#标的证券应收付数量
CKSOTPHistoryAssignmentField["IOVol"] = "int"
#应收付金额
CKSOTPHistoryAssignmentField["IOAmt"] = "float"
#行权交收日
CKSOTPHistoryAssignmentField["DelivDate"] = "string"
structDict['CKSOTPHistoryAssignmentField'] = CKSOTPHistoryAssignmentField


#行权交割明细
CKSOTPDelivDetailField = {}
#经纪公司代码
CKSOTPDelivDetailField["BrokerID"] = "string"
#投资者代码
CKSOTPDelivDetailField["InvestorID"] = "string"
#交易所代码
CKSOTPDelivDetailField["ExchangeID"] = "string"
#标的证券代码
CKSOTPDelivDetailField["StockInstr"] = "string"
#应收/应付/扣券证券数量
CKSOTPDelivDetailField["IOVol"] = "int"
#实收付数量
CKSOTPDelivDetailField["IOVolInFact"] = "int"
#结算价
CKSOTPDelivDetailField["SettlementPrice"] = "float"
#扣券面值/结算金额
CKSOTPDelivDetailField["SettlementAmt"] = "float"
#行权交收日
CKSOTPDelivDetailField["DelivDate"] = "string"
#业务类型名称
CKSOTPDelivDetailField["FunctionName"] = "string"
structDict['CKSOTPDelivDetailField'] = CKSOTPDelivDetailField


#历史报单
CKSOTPHistoryOrderField = {}
#经纪公司代码
CKSOTPHistoryOrderField["BrokerID"] = "string"
#投资者代码
CKSOTPHistoryOrderField["InvestorID"] = "string"
#客户姓名
CKSOTPHistoryOrderField["CustomerName"] = "string"
#合约代码
CKSOTPHistoryOrderField["InstrumentID"] = "string"
#本地报单编号
CKSOTPHistoryOrderField["OrderLocalID"] = "string"
#申报时间
CKSOTPHistoryOrderField["InsertTime"] = "string"
#业务单元
CKSOTPHistoryOrderField["BusinessUnit"] = "string"
#成交价格
CKSOTPHistoryOrderField["TradePrice"] = "float"
#成交金额
CKSOTPHistoryOrderField["TradeAmount"] = "float"
#成交数量
CKSOTPHistoryOrderField["VolumeTraded"] = "int"
#冻结解冻金额
CKSOTPHistoryOrderField["FrozenAmount"] = "float"
#币种代码
CKSOTPHistoryOrderField["CurrencyID"] = "string"
#序号
CKSOTPHistoryOrderField["SequenceNo"] = "int"
#买卖方向
CKSOTPHistoryOrderField["Direction"] = "string"
#交易所代码
CKSOTPHistoryOrderField["ExchangeID"] = "string"
#用户端产品信息
CKSOTPHistoryOrderField["UserProductInfo"] = "string"
#请求编号
CKSOTPHistoryOrderField["RequestID"] = "int"
#报单引用
CKSOTPHistoryOrderField["OrderRef"] = "string"
#前置编号
CKSOTPHistoryOrderField["FrontID"] = "int"
#会话编号
CKSOTPHistoryOrderField["SessionID"] = "int"
#委托价格
CKSOTPHistoryOrderField["OrderPrice"] = "float"
#委托来源
CKSOTPHistoryOrderField["OrderSource"] = "string"
#委托日期
CKSOTPHistoryOrderField["InsertDate"] = "string"
#委托时间
CKSOTPHistoryOrderField["OrderTime"] = "string"
#委托数量
CKSOTPHistoryOrderField["VolumeTotalOriginal"] = "int"
#委托状态
CKSOTPHistoryOrderField["OrderStatus"] = "string"
#产品代码
CKSOTPHistoryOrderField["ProductID"] = "string"
#产品名称
CKSOTPHistoryOrderField["ProductName"] = "string"
#产品类型
CKSOTPHistoryOrderField["ProductClass"] = "string"
#投保买卖开平标志
CKSOTPHistoryOrderField["OffsetFlag"] = "string"
#业务类型名称
CKSOTPHistoryOrderField["FunctionName"] = "string"
structDict['CKSOTPHistoryOrderField'] = CKSOTPHistoryOrderField


#历史成交
CKSOTPHistoryTradeField = {}
#经纪公司代码
CKSOTPHistoryTradeField["BrokerID"] = "string"
#投资者代码
CKSOTPHistoryTradeField["InvestorID"] = "string"
#客户姓名
CKSOTPHistoryTradeField["CustomerName"] = "string"
#本地报单编号
CKSOTPHistoryTradeField["OrderLocalID"] = "string"
#币种代码
CKSOTPHistoryTradeField["CurrencyID"] = "string"
#交易所代码
CKSOTPHistoryTradeField["ExchangeID"] = "string"
#产品代码
CKSOTPHistoryTradeField["ProductID"] = "string"
#产品名称
CKSOTPHistoryTradeField["ProductName"] = "string"
#成交数量
CKSOTPHistoryTradeField["VolumeTraded"] = "int"
#成交金额
CKSOTPHistoryTradeField["TradeAmount"] = "float"
#成交日期
CKSOTPHistoryTradeField["TradeDate"] = "string"
#成交时间
CKSOTPHistoryTradeField["TradeTime"] = "string"
#投保买卖开平标志
CKSOTPHistoryTradeField["OffsetFlag"] = "string"
#业务单元
CKSOTPHistoryTradeField["BusinessUnit"] = "string"
#手续费
CKSOTPHistoryTradeField["Commission"] = "float"
#备注
CKSOTPHistoryTradeField["Memo"] = "string"
#报盘时间
CKSOTPHistoryTradeField["TraderOfferTime"] = "string"
#成交价格
CKSOTPHistoryTradeField["TradePrice;"] = "float"
#期权交易编码
CKSOTPHistoryTradeField["ClientID"] = "string"
#期权类型
CKSOTPHistoryTradeField["OptionsType"] = "string"
#备兑标志
CKSOTPHistoryTradeField["HedgeFlag"] = "string"
#权利仓数量
CKSOTPHistoryTradeField["RoyaltyVolume"] = "int"
#义务仓数量
CKSOTPHistoryTradeField["ObligationVolume"] = "int"
#权利仓金额
CKSOTPHistoryTradeField["RoyaltyAmount"] = "float"
#义务仓金额
CKSOTPHistoryTradeField["ObligationAmount"] = "float"
#成交编号
CKSOTPHistoryTradeField["TradeID"] = "string"
#业务类型名称
CKSOTPHistoryTradeField["FunctionName"] = "string"
structDict['CKSOTPHistoryTradeField'] = CKSOTPHistoryTradeField


#个股组合拆分委托
CKSOTPInputCombActionField = {}
#经纪公司代码
CKSOTPInputCombActionField["BrokerID"] = "string"
#投资者代码
CKSOTPInputCombActionField["InvestorID"] = "string"
#策略代码
CKSOTPInputCombActionField["StrategyID"] = "string"
#合约代码1
CKSOTPInputCombActionField["InstrumentID1"] = "string"
#合约代码2
CKSOTPInputCombActionField["InstrumentID2"] = "string"
#合约代码3
CKSOTPInputCombActionField["InstrumentID3"] = "string"
#合约代码4
CKSOTPInputCombActionField["InstrumentID4"] = "string"
#组合引用
CKSOTPInputCombActionField["CombActionRef"] = "string"
#用户代码
CKSOTPInputCombActionField["UserID"] = "string"
#买卖方向1
CKSOTPInputCombActionField["Direction1"] = "string"
#买卖方向2
CKSOTPInputCombActionField["Direction2"] = "string"
#买卖方向3
CKSOTPInputCombActionField["Direction3"] = "string"
#买卖方向4
CKSOTPInputCombActionField["Direction4"] = "string"
#强拆标记
CKSOTPInputCombActionField[" CombActionFlag"] = "string"
#数量
CKSOTPInputCombActionField["Volume"] = "int"
#组合拆分标记
CKSOTPInputCombActionField["CombDirection"] = "string"
#投机套保标志
CKSOTPInputCombActionField["HedgeFlag"] = "string"
#交易所代码
CKSOTPInputCombActionField["ExchangeID"] = "string"
#交易所组合编号
CKSOTPInputCombActionField["ComTradeID"] = "string"
structDict['CKSOTPInputCombActionField'] = CKSOTPInputCombActionField


#个股组合拆分
CKSOTPCombActionField = {}
#经纪公司代码
CKSOTPCombActionField["BrokerID"] = "string"
#投资者代码
CKSOTPCombActionField["InvestorID"] = "string"
#完整合约代码
CKSOTPCombActionField["InstrumentID"] = "string"
#策略代码
CKSOTPCombActionField["StrategyID"] = "string"
#合约代码1
CKSOTPCombActionField["InstrumentID1"] = "string"
#合约代码2
CKSOTPCombActionField["InstrumentID2"] = "string"
#合约代码3
CKSOTPCombActionField["InstrumentID3"] = "string"
#合约代码4
CKSOTPCombActionField["InstrumentID4"] = "string"
#组合引用
CKSOTPCombActionField["CombActionRef"] = "string"
#用户代码
CKSOTPCombActionField["UserID"] = "string"
#买卖方向1
CKSOTPCombActionField["Direction1"] = "string"
#买卖方向2
CKSOTPCombActionField["Direction2"] = "string"
#买卖方向3
CKSOTPCombActionField["Direction3"] = "string"
#买卖方向4
CKSOTPCombActionField["Direction4"] = "string"
#强拆标记
CKSOTPCombActionField[" CombActionFlag"] = "string"
#数量
CKSOTPCombActionField["Volume"] = "int"
#组合拆分标记
CKSOTPCombActionField["CombDirection"] = "string"
#投机套保标志
CKSOTPCombActionField["HedgeFlag"] = "string"
#本地申请组合编号
CKSOTPCombActionField["ActionLocalID"] = "string"
#交易所代码
CKSOTPCombActionField["ExchangeID"] = "string"
#会员代码
CKSOTPCombActionField["ParticipantID"] = "string"
#客户代码
CKSOTPCombActionField["ClientID"] = "string"
#合约在交易所的代码
CKSOTPCombActionField["ExchangeInstID"] = "string"
#交易所交易员代码
CKSOTPCombActionField["TraderID"] = "string"
#安装编号
CKSOTPCombActionField["InstallID"] = "int"
#组合状态
CKSOTPCombActionField["ActionStatus"] = "string"
#报单提示序号
CKSOTPCombActionField["NotifySequence"] = "int"
#交易日
CKSOTPCombActionField["TradingDay"] = "string"
#结算编号
CKSOTPCombActionField["SettlementID"] = "int"
#序号
CKSOTPCombActionField["SequenceNo"] = "int"
#前置编号
CKSOTPCombActionField["FrontID"] = "int"
#会话编号
CKSOTPCombActionField["SessionID"] = "int"
#用户端产品信息
CKSOTPCombActionField["UserProductInfo"] = "string"
#状态信息
CKSOTPCombActionField["StatusMsg"] = "string"
#交易所组合编号
CKSOTPCombActionField["ComTradeID"] = "string"
#报单来源
CKSOTPCombActionField["OrderSource"] = "string"
structDict['CKSOTPCombActionField'] = CKSOTPCombActionField


#查询个股组合持仓明细
CKSOTPQryInvestorPositionCombineDetailField = {}
#经纪公司代码
CKSOTPQryInvestorPositionCombineDetailField["BrokerID"] = "string"
#投资者代码
CKSOTPQryInvestorPositionCombineDetailField["InvestorID"] = "string"
#交易所代码
CKSOTPQryInvestorPositionCombineDetailField["ExchangeID"] = "string"
#产品代码
CKSOTPQryInvestorPositionCombineDetailField["ProductID"] = "string"
#交易所组合编号
CKSOTPQryInvestorPositionCombineDetailField["ComTradeID"] = "string"
structDict['CKSOTPQryInvestorPositionCombineDetailField'] = CKSOTPQryInvestorPositionCombineDetailField


#个股组合持仓明细
CKSOTPInvestorPositionCombineDetailField = {}
#经纪公司代码
CKSOTPInvestorPositionCombineDetailField["BrokerID"] = "string"
#投资者代码
CKSOTPInvestorPositionCombineDetailField["InvestorID"] = "string"
#交易所代码
CKSOTPInvestorPositionCombineDetailField["ExchangeID"] = "string"
#交易编码
CKSOTPInvestorPositionCombineDetailField["ClientID"] = "string"
#组合编号
CKSOTPInvestorPositionCombineDetailField["ComTradeID"] = "string"
#策略代码
CKSOTPInvestorPositionCombineDetailField["StrategyID"] = "string"
#合约代码1
CKSOTPInvestorPositionCombineDetailField["InstrumentID1"] = "string"
#合约代码2
CKSOTPInvestorPositionCombineDetailField["InstrumentID2"] = "string"
#合约代码3
CKSOTPInvestorPositionCombineDetailField["InstrumentID3"] = "string"
#合约代码4
CKSOTPInvestorPositionCombineDetailField["InstrumentID4"] = "string"
#保证金
CKSOTPInvestorPositionCombineDetailField["Margin"] = "float"
#距离自动拆分日天数
CKSOTPInvestorPositionCombineDetailField["CombActionVolume"] = "int"
#投保标记
CKSOTPInvestorPositionCombineDetailField["HedgeFlag"] = "string"
#持仓量
CKSOTPInvestorPositionCombineDetailField["TotalAmt"] = "int"
#买卖方向1
CKSOTPInvestorPositionCombineDetailField["Direction1"] = "string"
#买卖方向2
CKSOTPInvestorPositionCombineDetailField["Direction2"] = "string"
#买卖方向3
CKSOTPInvestorPositionCombineDetailField["Direction3"] = "string"
#买卖方向4
CKSOTPInvestorPositionCombineDetailField["Direction4"] = "string"
#组合买卖方向
CKSOTPInvestorPositionCombineDetailField["CombDirection"] = "string"
structDict['CKSOTPInvestorPositionCombineDetailField'] = CKSOTPInvestorPositionCombineDetailField


#个股可组合可拆分手数查询请求
CKSOTPQryCombActionVolumeField = {}
#经纪公司代码
CKSOTPQryCombActionVolumeField["BrokerID"] = "string"
#投资者代码
CKSOTPQryCombActionVolumeField["InvestorID"] = "string"
#交易所代码
CKSOTPQryCombActionVolumeField["ExchangeID"] = "string"
#策略代码
CKSOTPQryCombActionVolumeField["StrategyID"] = "string"
#合约代码1
CKSOTPQryCombActionVolumeField["InstrumentID1"] = "string"
#合约代码2
CKSOTPQryCombActionVolumeField["InstrumentID2"] = "string"
#合约代码3
CKSOTPQryCombActionVolumeField["InstrumentID3"] = "string"
#合约代码4
CKSOTPQryCombActionVolumeField["InstrumentID4"] = "string"
#投保标记
CKSOTPQryCombActionVolumeField["HedgeFlag"] = "string"
#买卖方向1
CKSOTPQryCombActionVolumeField["Direction1"] = "string"
#买卖方向2
CKSOTPQryCombActionVolumeField["Direction2"] = "string"
#买卖方向3
CKSOTPQryCombActionVolumeField["Direction3"] = "string"
#买卖方向4
CKSOTPQryCombActionVolumeField["Direction4"] = "string"
#强拆标记
CKSOTPQryCombActionVolumeField[" CombActionFlag"] = "string"
#组合拆分标记
CKSOTPQryCombActionVolumeField["CombDirection"] = "string"
#组合编号
CKSOTPQryCombActionVolumeField["ComTradeID"] = "string"
structDict['CKSOTPQryCombActionVolumeField'] = CKSOTPQryCombActionVolumeField


#个股可组合可拆分手数
CKSOTPCombActionVolumeField = {}
#经纪公司代码
CKSOTPCombActionVolumeField["BrokerID"] = "string"
#投资者代码
CKSOTPCombActionVolumeField["InvestorID"] = "string"
#最大可组合数量
CKSOTPCombActionVolumeField["MaxCombVolume"] = "int"
#最大可拆分数量
CKSOTPCombActionVolumeField["MaxActionVolume"] = "int"
structDict['CKSOTPCombActionVolumeField'] = CKSOTPCombActionVolumeField


#客户每日出金额度申请请求
CKSOTPInputFundOutCreditApplyField = {}
#经纪公司代码
CKSOTPInputFundOutCreditApplyField["BrokerID"] = "string"
#投资者代码
CKSOTPInputFundOutCreditApplyField["InvestorID"] = "string"
#当日出金额度
CKSOTPInputFundOutCreditApplyField["FundOutCredit"] = "float"
#当日出金额度操作类型
CKSOTPInputFundOutCreditApplyField["CreditApplyFlag"] = "string"
#流水号
CKSOTPInputFundOutCreditApplyField["CreditSerial"] = "int"
structDict['CKSOTPInputFundOutCreditApplyField'] = CKSOTPInputFundOutCreditApplyField


#客户每日出金额度查询请求
CKSOTPQryFundOutCreditField = {}
#经纪公司代码
CKSOTPQryFundOutCreditField["BrokerID"] = "string"
#投资者代码
CKSOTPQryFundOutCreditField["InvestorID"] = "string"
structDict['CKSOTPQryFundOutCreditField'] = CKSOTPQryFundOutCreditField


#客户每日出金额度查询
CKSOTPRspQryFundOutCreditField = {}
#经纪公司代码
CKSOTPRspQryFundOutCreditField["BrokerID"] = "string"
#投资者代码
CKSOTPRspQryFundOutCreditField["InvestorID"] = "string"
#当日出金额度
CKSOTPRspQryFundOutCreditField["FundOutCredit"] = "float"
#当日已出金额度
CKSOTPRspQryFundOutCreditField["FundOutedCredit"] = "float"
#最后更新日期
CKSOTPRspQryFundOutCreditField["UpdateDate"] = "string"
#设置日期
CKSOTPRspQryFundOutCreditField["SetDate"] = "string"
#设置时间
CKSOTPRspQryFundOutCreditField["SetTime"] = "string"
structDict['CKSOTPRspQryFundOutCreditField'] = CKSOTPRspQryFundOutCreditField


#客户每日出金额度申请查询请求
CKSOTPQryFundOutCreditApplyField = {}
#经纪公司代码
CKSOTPQryFundOutCreditApplyField["BrokerID"] = "string"
#投资者代码
CKSOTPQryFundOutCreditApplyField["InvestorID"] = "string"
#查询开始日期
CKSOTPQryFundOutCreditApplyField["QryCreditStart"] = "string"
#查询结束日期
CKSOTPQryFundOutCreditApplyField["QryCreditEnd"] = "string"
#当日出金额度处理状态
CKSOTPQryFundOutCreditApplyField["DealStatus"] = "string"
structDict['CKSOTPQryFundOutCreditApplyField'] = CKSOTPQryFundOutCreditApplyField


#客户每日出金额度申请查询
CKSOTPRspQryFundOutCreditApplyField = {}
#经纪公司代码
CKSOTPRspQryFundOutCreditApplyField["BrokerID"] = "string"
#投资者代码
CKSOTPRspQryFundOutCreditApplyField["InvestorID"] = "string"
#流水号
CKSOTPRspQryFundOutCreditApplyField["CreditSerial"] = "int"
#申请出金额度
CKSOTPRspQryFundOutCreditApplyField["FundOutCredit"] = "float"
#当日出金额度处理状态
CKSOTPRspQryFundOutCreditApplyField["DealStatus"] = "string"
#申请日期
CKSOTPRspQryFundOutCreditApplyField["ApplyDate"] = "string"
#申请时间
CKSOTPRspQryFundOutCreditApplyField["ApplyTime"] = "string"
#审核日期
CKSOTPRspQryFundOutCreditApplyField["ConfirmDate"] = "string"
#审核时间
CKSOTPRspQryFundOutCreditApplyField["ConfirmTime"] = "string"
structDict['CKSOTPRspQryFundOutCreditApplyField'] = CKSOTPRspQryFundOutCreditApplyField

structDict['CKSOTPRspQryFundOutCreditApplyField'] = CKSOTPRspQryFundOutCreditApplyField



