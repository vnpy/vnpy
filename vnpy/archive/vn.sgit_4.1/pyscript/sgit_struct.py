# encoding: UTF-8

structDict = {}

#//////////////////////////////////////////////////////////////////////

#//////////////////////////////////////////////////////////////////////










#信息分发
CSgitFtdcDisseminationField = {}
#序列系列号
CSgitFtdcDisseminationField["SequenceSeries"] = "short"
#序列号
CSgitFtdcDisseminationField["SequenceNo"] = "int"
structDict['CSgitFtdcDisseminationField'] = CSgitFtdcDisseminationField


#用户登录请求
CSgitFtdcReqUserLoginField = {}
#交易日
CSgitFtdcReqUserLoginField["TradingDay"] = "string"
#经纪公司代码
CSgitFtdcReqUserLoginField["BrokerID"] = "string"
#用户代码
CSgitFtdcReqUserLoginField["UserID"] = "string"
#密码
CSgitFtdcReqUserLoginField["Password"] = "string"
#用户端产品信息
CSgitFtdcReqUserLoginField["UserProductInfo"] = "string"
#接口端产品信息
CSgitFtdcReqUserLoginField["InterfaceProductInfo"] = "string"
#协议信息
CSgitFtdcReqUserLoginField["ProtocolInfo"] = "string"
#Mac地址
CSgitFtdcReqUserLoginField["MacAddress"] = "string"
#动态密码
CSgitFtdcReqUserLoginField["OneTimePassword"] = "string"
#终端IP地址
CSgitFtdcReqUserLoginField["ClientIPAddress"] = "string"
structDict['CSgitFtdcReqUserLoginField'] = CSgitFtdcReqUserLoginField


#用户登录应答
CSgitFtdcRspUserLoginField = {}
#交易日
CSgitFtdcRspUserLoginField["TradingDay"] = "string"
#登录成功时间
CSgitFtdcRspUserLoginField["LoginTime"] = "string"
#经纪公司代码
CSgitFtdcRspUserLoginField["BrokerID"] = "string"
#用户代码
CSgitFtdcRspUserLoginField["UserID"] = "string"
#交易系统名称
CSgitFtdcRspUserLoginField["SystemName"] = "string"
#前置编号
CSgitFtdcRspUserLoginField["FrontID"] = "int"
#会话编号
CSgitFtdcRspUserLoginField["SessionID"] = "int"
#最大报单引用
CSgitFtdcRspUserLoginField["MaxOrderRef"] = "string"
#上期所时间
CSgitFtdcRspUserLoginField["SHFETime"] = "string"
#大商所时间
CSgitFtdcRspUserLoginField["DCETime"] = "string"
#郑商所时间
CSgitFtdcRspUserLoginField["CZCETime"] = "string"
#中金所时间
CSgitFtdcRspUserLoginField["FFEXTime"] = "string"
structDict['CSgitFtdcRspUserLoginField'] = CSgitFtdcRspUserLoginField


#用户登出请求
CSgitFtdcUserLogoutField = {}
#经纪公司代码
CSgitFtdcUserLogoutField["BrokerID"] = "string"
#用户代码
CSgitFtdcUserLogoutField["UserID"] = "string"
structDict['CSgitFtdcUserLogoutField'] = CSgitFtdcUserLogoutField


#强制交易员退出
CSgitFtdcForceUserLogoutField = {}
#经纪公司代码
CSgitFtdcForceUserLogoutField["BrokerID"] = "string"
#用户代码
CSgitFtdcForceUserLogoutField["UserID"] = "string"
structDict['CSgitFtdcForceUserLogoutField'] = CSgitFtdcForceUserLogoutField


#客户端认证请求
CSgitFtdcReqAuthenticateField = {}
#经纪公司代码
CSgitFtdcReqAuthenticateField["BrokerID"] = "string"
#用户代码
CSgitFtdcReqAuthenticateField["UserID"] = "string"
#用户端产品信息
CSgitFtdcReqAuthenticateField["UserProductInfo"] = "string"
#认证码
CSgitFtdcReqAuthenticateField["AuthCode"] = "string"
structDict['CSgitFtdcReqAuthenticateField'] = CSgitFtdcReqAuthenticateField


#客户端认证响应
CSgitFtdcRspAuthenticateField = {}
#经纪公司代码
CSgitFtdcRspAuthenticateField["BrokerID"] = "string"
#用户代码
CSgitFtdcRspAuthenticateField["UserID"] = "string"
#用户端产品信息
CSgitFtdcRspAuthenticateField["UserProductInfo"] = "string"
structDict['CSgitFtdcRspAuthenticateField'] = CSgitFtdcRspAuthenticateField


#客户端认证信息
CSgitFtdcAuthenticationInfoField = {}
#经纪公司代码
CSgitFtdcAuthenticationInfoField["BrokerID"] = "string"
#用户代码
CSgitFtdcAuthenticationInfoField["UserID"] = "string"
#用户端产品信息
CSgitFtdcAuthenticationInfoField["UserProductInfo"] = "string"
#认证信息
CSgitFtdcAuthenticationInfoField["AuthInfo"] = "string"
#是否为认证结果
CSgitFtdcAuthenticationInfoField["IsResult"] = "int"
structDict['CSgitFtdcAuthenticationInfoField'] = CSgitFtdcAuthenticationInfoField


#银期转帐报文头
CSgitFtdcTransferHeaderField = {}
#版本号，常量，1.0
CSgitFtdcTransferHeaderField["Version"] = "string"
#交易代码，必填
CSgitFtdcTransferHeaderField["TradeCode"] = "string"
#交易日期，必填，格式：yyyymmdd
CSgitFtdcTransferHeaderField["TradeDate"] = "string"
#交易时间，必填，格式：hhmmss
CSgitFtdcTransferHeaderField["TradeTime"] = "string"
#发起方流水号，N/A
CSgitFtdcTransferHeaderField["TradeSerial"] = "string"
#期货公司代码，必填
CSgitFtdcTransferHeaderField["FutureID"] = "string"
#银行代码，根据查询银行得到，必填
CSgitFtdcTransferHeaderField["BankID"] = "string"
#银行分中心代码，根据查询银行得到，必填
CSgitFtdcTransferHeaderField["BankBrchID"] = "string"
#操作员，N/A
CSgitFtdcTransferHeaderField["OperNo"] = "string"
#交易设备类型，N/A
CSgitFtdcTransferHeaderField["DeviceID"] = "string"
#记录数，N/A
CSgitFtdcTransferHeaderField["RecordNum"] = "string"
#会话编号，N/A
CSgitFtdcTransferHeaderField["SessionID"] = "int"
#请求编号，N/A
CSgitFtdcTransferHeaderField["RequestID"] = "int"
structDict['CSgitFtdcTransferHeaderField'] = CSgitFtdcTransferHeaderField


#银行资金转期货请求，TradeCode=202001
CSgitFtdcTransferBankToFutureReqField = {}
#期货资金账户
CSgitFtdcTransferBankToFutureReqField["FutureAccount"] = "string"
#密码标志
CSgitFtdcTransferBankToFutureReqField["FuturePwdFlag"] = "char"
#密码
CSgitFtdcTransferBankToFutureReqField["FutureAccPwd"] = "string"
#转账金额
CSgitFtdcTransferBankToFutureReqField["TradeAmt"] = "float"
#客户手续费
CSgitFtdcTransferBankToFutureReqField["CustFee"] = "float"
#币种：RMB-人民币 USD-美圆 HKD-港元
CSgitFtdcTransferBankToFutureReqField["CurrencyCode"] = "string"
structDict['CSgitFtdcTransferBankToFutureReqField'] = CSgitFtdcTransferBankToFutureReqField


#银行资金转期货请求响应
CSgitFtdcTransferBankToFutureRspField = {}
#响应代码
CSgitFtdcTransferBankToFutureRspField["RetCode"] = "string"
#响应信息
CSgitFtdcTransferBankToFutureRspField["RetInfo"] = "string"
#资金账户
CSgitFtdcTransferBankToFutureRspField["FutureAccount"] = "string"
#转帐金额
CSgitFtdcTransferBankToFutureRspField["TradeAmt"] = "float"
#应收客户手续费
CSgitFtdcTransferBankToFutureRspField["CustFee"] = "float"
#币种
CSgitFtdcTransferBankToFutureRspField["CurrencyCode"] = "string"
structDict['CSgitFtdcTransferBankToFutureRspField'] = CSgitFtdcTransferBankToFutureRspField


#期货资金转银行请求，TradeCode=202002
CSgitFtdcTransferFutureToBankReqField = {}
#期货资金账户
CSgitFtdcTransferFutureToBankReqField["FutureAccount"] = "string"
#密码标志
CSgitFtdcTransferFutureToBankReqField["FuturePwdFlag"] = "char"
#密码
CSgitFtdcTransferFutureToBankReqField["FutureAccPwd"] = "string"
#转账金额
CSgitFtdcTransferFutureToBankReqField["TradeAmt"] = "float"
#客户手续费
CSgitFtdcTransferFutureToBankReqField["CustFee"] = "float"
#币种：RMB-人民币 USD-美圆 HKD-港元
CSgitFtdcTransferFutureToBankReqField["CurrencyCode"] = "string"
structDict['CSgitFtdcTransferFutureToBankReqField'] = CSgitFtdcTransferFutureToBankReqField


#期货资金转银行请求响应
CSgitFtdcTransferFutureToBankRspField = {}
#响应代码
CSgitFtdcTransferFutureToBankRspField["RetCode"] = "string"
#响应信息
CSgitFtdcTransferFutureToBankRspField["RetInfo"] = "string"
#资金账户
CSgitFtdcTransferFutureToBankRspField["FutureAccount"] = "string"
#转帐金额
CSgitFtdcTransferFutureToBankRspField["TradeAmt"] = "float"
#应收客户手续费
CSgitFtdcTransferFutureToBankRspField["CustFee"] = "float"
#币种
CSgitFtdcTransferFutureToBankRspField["CurrencyCode"] = "string"
structDict['CSgitFtdcTransferFutureToBankRspField'] = CSgitFtdcTransferFutureToBankRspField


#查询银行资金请求，TradeCode=204002
CSgitFtdcTransferQryBankReqField = {}
#期货资金账户
CSgitFtdcTransferQryBankReqField["FutureAccount"] = "string"
#密码标志
CSgitFtdcTransferQryBankReqField["FuturePwdFlag"] = "char"
#密码
CSgitFtdcTransferQryBankReqField["FutureAccPwd"] = "string"
#币种：RMB-人民币 USD-美圆 HKD-港元
CSgitFtdcTransferQryBankReqField["CurrencyCode"] = "string"
structDict['CSgitFtdcTransferQryBankReqField'] = CSgitFtdcTransferQryBankReqField


#查询银行资金请求响应
CSgitFtdcTransferQryBankRspField = {}
#响应代码
CSgitFtdcTransferQryBankRspField["RetCode"] = "string"
#响应信息
CSgitFtdcTransferQryBankRspField["RetInfo"] = "string"
#资金账户
CSgitFtdcTransferQryBankRspField["FutureAccount"] = "string"
#银行余额
CSgitFtdcTransferQryBankRspField["TradeAmt"] = "float"
#银行可用余额
CSgitFtdcTransferQryBankRspField["UseAmt"] = "float"
#银行可取余额
CSgitFtdcTransferQryBankRspField["FetchAmt"] = "float"
#币种
CSgitFtdcTransferQryBankRspField["CurrencyCode"] = "string"
structDict['CSgitFtdcTransferQryBankRspField'] = CSgitFtdcTransferQryBankRspField


#查询银行交易明细请求，TradeCode=204999
CSgitFtdcTransferQryDetailReqField = {}
#期货资金账户
CSgitFtdcTransferQryDetailReqField["FutureAccount"] = "string"
structDict['CSgitFtdcTransferQryDetailReqField'] = CSgitFtdcTransferQryDetailReqField


#查询银行交易明细请求响应
CSgitFtdcTransferQryDetailRspField = {}
#交易日期
CSgitFtdcTransferQryDetailRspField["TradeDate"] = "string"
#交易时间
CSgitFtdcTransferQryDetailRspField["TradeTime"] = "string"
#交易代码
CSgitFtdcTransferQryDetailRspField["TradeCode"] = "string"
#期货流水号
CSgitFtdcTransferQryDetailRspField["FutureSerial"] = "int"
#期货公司代码
CSgitFtdcTransferQryDetailRspField["FutureID"] = "string"
#资金帐号
CSgitFtdcTransferQryDetailRspField["FutureAccount"] = "string"
#银行流水号
CSgitFtdcTransferQryDetailRspField["BankSerial"] = "int"
#银行代码
CSgitFtdcTransferQryDetailRspField["BankID"] = "string"
#银行分中心代码
CSgitFtdcTransferQryDetailRspField["BankBrchID"] = "string"
#银行账号
CSgitFtdcTransferQryDetailRspField["BankAccount"] = "string"
#证件号码
CSgitFtdcTransferQryDetailRspField["CertCode"] = "string"
#货币代码
CSgitFtdcTransferQryDetailRspField["CurrencyCode"] = "string"
#发生金额
CSgitFtdcTransferQryDetailRspField["TxAmount"] = "float"
#有效标志
CSgitFtdcTransferQryDetailRspField["Flag"] = "char"
structDict['CSgitFtdcTransferQryDetailRspField'] = CSgitFtdcTransferQryDetailRspField


#响应信息
CSgitFtdcRspInfoField = {}
#错误代码
CSgitFtdcRspInfoField["ErrorID"] = "int"
#错误信息
CSgitFtdcRspInfoField["ErrorMsg"] = "string"
structDict['CSgitFtdcRspInfoField'] = CSgitFtdcRspInfoField


#交易所
CSgitFtdcExchangeField = {}
#交易所代码
CSgitFtdcExchangeField["ExchangeID"] = "string"
#交易所名称
CSgitFtdcExchangeField["ExchangeName"] = "string"
#交易所属性
CSgitFtdcExchangeField["ExchangeProperty"] = "char"
structDict['CSgitFtdcExchangeField'] = CSgitFtdcExchangeField


#产品
CSgitFtdcProductField = {}
#产品代码
CSgitFtdcProductField["ProductID"] = "string"
#产品名称
CSgitFtdcProductField["ProductName"] = "string"
#交易所代码
CSgitFtdcProductField["ExchangeID"] = "string"
#产品类型
CSgitFtdcProductField["ProductClass"] = "char"
#合约数量乘数
CSgitFtdcProductField["VolumeMultiple"] = "int"
#最小变动价位
CSgitFtdcProductField["PriceTick"] = "float"
#市价单最大下单量
CSgitFtdcProductField["MaxMarketOrderVolume"] = "int"
#市价单最小下单量
CSgitFtdcProductField["MinMarketOrderVolume"] = "int"
#限价单最大下单量
CSgitFtdcProductField["MaxLimitOrderVolume"] = "int"
#限价单最小下单量
CSgitFtdcProductField["MinLimitOrderVolume"] = "int"
#持仓类型
CSgitFtdcProductField["PositionType"] = "char"
#持仓日期类型
CSgitFtdcProductField["PositionDateType"] = "char"
structDict['CSgitFtdcProductField'] = CSgitFtdcProductField


#合约
CSgitFtdcInstrumentField = {}
#合约代码
CSgitFtdcInstrumentField["InstrumentID"] = "string"
#交易所代码
CSgitFtdcInstrumentField["ExchangeID"] = "string"
#合约名称
CSgitFtdcInstrumentField["InstrumentName"] = "string"
#合约在交易所的代码
CSgitFtdcInstrumentField["ExchangeInstID"] = "string"
#产品代码
CSgitFtdcInstrumentField["ProductID"] = "string"
#产品类型
CSgitFtdcInstrumentField["ProductClass"] = "char"
#交割年份
CSgitFtdcInstrumentField["DeliveryYear"] = "int"
#交割月
CSgitFtdcInstrumentField["DeliveryMonth"] = "int"
#市价单最大下单量
CSgitFtdcInstrumentField["MaxMarketOrderVolume"] = "int"
#市价单最小下单量
CSgitFtdcInstrumentField["MinMarketOrderVolume"] = "int"
#限价单最大下单量
CSgitFtdcInstrumentField["MaxLimitOrderVolume"] = "int"
#限价单最小下单量
CSgitFtdcInstrumentField["MinLimitOrderVolume"] = "int"
#合约数量乘数
CSgitFtdcInstrumentField["VolumeMultiple"] = "int"
#最小变动价位
CSgitFtdcInstrumentField["PriceTick"] = "float"
#创建日
CSgitFtdcInstrumentField["CreateDate"] = "string"
#上市日
CSgitFtdcInstrumentField["OpenDate"] = "string"
#到期日
CSgitFtdcInstrumentField["ExpireDate"] = "string"
#开始交割日
CSgitFtdcInstrumentField["StartDelivDate"] = "string"
#结束交割日
CSgitFtdcInstrumentField["EndDelivDate"] = "string"
#合约生命周期状态
CSgitFtdcInstrumentField["InstLifePhase"] = "char"
#当前是否交易
CSgitFtdcInstrumentField["IsTrading"] = "int"
#持仓类型
CSgitFtdcInstrumentField["PositionType"] = "char"
#持仓日期类型
CSgitFtdcInstrumentField["PositionDateType"] = "char"
#多头保证金率
CSgitFtdcInstrumentField["LongMarginRatio"] = "float"
#空头保证金率
CSgitFtdcInstrumentField["ShortMarginRatio"] = "float"
structDict['CSgitFtdcInstrumentField'] = CSgitFtdcInstrumentField


#经纪公司
CSgitFtdcBrokerField = {}
#经纪公司代码
CSgitFtdcBrokerField["BrokerID"] = "string"
#经纪公司简称
CSgitFtdcBrokerField["BrokerAbbr"] = "string"
#经纪公司名称
CSgitFtdcBrokerField["BrokerName"] = "string"
#是否活跃
CSgitFtdcBrokerField["IsActive"] = "int"
structDict['CSgitFtdcBrokerField'] = CSgitFtdcBrokerField


#交易所交易员
CSgitFtdcTraderField = {}
#交易所代码
CSgitFtdcTraderField["ExchangeID"] = "string"
#交易所交易员代码
CSgitFtdcTraderField["TraderID"] = "string"
#会员代码
CSgitFtdcTraderField["ParticipantID"] = "string"
#密码
CSgitFtdcTraderField["Password"] = "string"
#安装数量
CSgitFtdcTraderField["InstallCount"] = "int"
#经纪公司代码
CSgitFtdcTraderField["BrokerID"] = "string"
structDict['CSgitFtdcTraderField'] = CSgitFtdcTraderField


#投资者
CSgitFtdcInvestorField = {}
#投资者代码
CSgitFtdcInvestorField["InvestorID"] = "string"
#经纪公司代码
CSgitFtdcInvestorField["BrokerID"] = "string"
#投资者分组代码
CSgitFtdcInvestorField["InvestorGroupID"] = "string"
#投资者名称
CSgitFtdcInvestorField["InvestorName"] = "string"
#证件类型
CSgitFtdcInvestorField["IdentifiedCardType"] = "char"
#证件号码
CSgitFtdcInvestorField["IdentifiedCardNo"] = "string"
#是否活跃
CSgitFtdcInvestorField["IsActive"] = "int"
#联系电话
CSgitFtdcInvestorField["Telephone"] = "string"
#通讯地址
CSgitFtdcInvestorField["Address"] = "string"
#开户日期
CSgitFtdcInvestorField["OpenDate"] = "string"
#手机
CSgitFtdcInvestorField["Mobile"] = "string"
#手续费率模板代码
CSgitFtdcInvestorField["CommModelID"] = "string"
structDict['CSgitFtdcInvestorField'] = CSgitFtdcInvestorField


#交易编码
CSgitFtdcTradingCodeField = {}
#投资者代码
CSgitFtdcTradingCodeField["InvestorID"] = "string"
#经纪公司代码
CSgitFtdcTradingCodeField["BrokerID"] = "string"
#交易所代码
CSgitFtdcTradingCodeField["ExchangeID"] = "string"
#客户代码
CSgitFtdcTradingCodeField["ClientID"] = "string"
#是否活跃
CSgitFtdcTradingCodeField["IsActive"] = "int"
#交易编码类型
CSgitFtdcTradingCodeField["ClientIDType"] = "char"
structDict['CSgitFtdcTradingCodeField'] = CSgitFtdcTradingCodeField


#会员编码和经纪公司编码对照表
CSgitFtdcPartBrokerField = {}
#经纪公司代码
CSgitFtdcPartBrokerField["BrokerID"] = "string"
#交易所代码
CSgitFtdcPartBrokerField["ExchangeID"] = "string"
#会员代码
CSgitFtdcPartBrokerField["ParticipantID"] = "string"
#是否活跃
CSgitFtdcPartBrokerField["IsActive"] = "int"
structDict['CSgitFtdcPartBrokerField'] = CSgitFtdcPartBrokerField


#管理用户
CSgitFtdcSuperUserField = {}
#用户代码
CSgitFtdcSuperUserField["UserID"] = "string"
#用户名称
CSgitFtdcSuperUserField["UserName"] = "string"
#密码
CSgitFtdcSuperUserField["Password"] = "string"
#是否活跃
CSgitFtdcSuperUserField["IsActive"] = "int"
structDict['CSgitFtdcSuperUserField'] = CSgitFtdcSuperUserField


#管理用户功能权限
CSgitFtdcSuperUserFunctionField = {}
#用户代码
CSgitFtdcSuperUserFunctionField["UserID"] = "string"
#功能代码
CSgitFtdcSuperUserFunctionField["FunctionCode"] = "char"
structDict['CSgitFtdcSuperUserFunctionField'] = CSgitFtdcSuperUserFunctionField


#投资者组
CSgitFtdcInvestorGroupField = {}
#经纪公司代码
CSgitFtdcInvestorGroupField["BrokerID"] = "string"
#投资者分组代码
CSgitFtdcInvestorGroupField["InvestorGroupID"] = "string"
#投资者分组名称
CSgitFtdcInvestorGroupField["InvestorGroupName"] = "string"
structDict['CSgitFtdcInvestorGroupField'] = CSgitFtdcInvestorGroupField


#资金账户
CSgitFtdcTradingAccountField = {}
#经纪公司代码
CSgitFtdcTradingAccountField["BrokerID"] = "string"
#投资者帐号
CSgitFtdcTradingAccountField["AccountID"] = "string"
#上次质押金额
CSgitFtdcTradingAccountField["PreMortgage"] = "float"
#上次信用额度
CSgitFtdcTradingAccountField["PreCredit"] = "float"
#上次存款额
CSgitFtdcTradingAccountField["PreDeposit"] = "float"
#上次结算准备金
CSgitFtdcTradingAccountField["PreBalance"] = "float"
#上次占用的保证金
CSgitFtdcTradingAccountField["PreMargin"] = "float"
#利息基数
CSgitFtdcTradingAccountField["InterestBase"] = "float"
#利息收入
CSgitFtdcTradingAccountField["Interest"] = "float"
#入金金额
CSgitFtdcTradingAccountField["Deposit"] = "float"
#出金金额
CSgitFtdcTradingAccountField["Withdraw"] = "float"
#冻结的保证金
CSgitFtdcTradingAccountField["FrozenMargin"] = "float"
#冻结的资金
CSgitFtdcTradingAccountField["FrozenCash"] = "float"
#冻结的手续费
CSgitFtdcTradingAccountField["FrozenCommission"] = "float"
#当前保证金总额
CSgitFtdcTradingAccountField["CurrMargin"] = "float"
#资金差额
CSgitFtdcTradingAccountField["CashIn"] = "float"
#手续费
CSgitFtdcTradingAccountField["Commission"] = "float"
#平仓盈亏
CSgitFtdcTradingAccountField["CloseProfit"] = "float"
#持仓盈亏
CSgitFtdcTradingAccountField["PositionProfit"] = "float"
#期货结算准备金
CSgitFtdcTradingAccountField["Balance"] = "float"
#可用资金
CSgitFtdcTradingAccountField["Available"] = "float"
#可取资金
CSgitFtdcTradingAccountField["WithdrawQuota"] = "float"
#基本准备金
CSgitFtdcTradingAccountField["Reserve"] = "float"
#交易日
CSgitFtdcTradingAccountField["TradingDay"] = "string"
#结算编号
CSgitFtdcTradingAccountField["SettlementID"] = "int"
#信用额度
CSgitFtdcTradingAccountField["Credit"] = "float"
#质押金额
CSgitFtdcTradingAccountField["Mortgage"] = "float"
#交易所保证金
CSgitFtdcTradingAccountField["ExchangeMargin"] = "float"
#投资者交割保证金
CSgitFtdcTradingAccountField["DeliveryMargin"] = "float"
#交易所交割保证金
CSgitFtdcTradingAccountField["ExchangeDeliveryMargin"] = "float"
structDict['CSgitFtdcTradingAccountField'] = CSgitFtdcTradingAccountField


#投资者持仓
CSgitFtdcInvestorPositionField = {}
#合约代码
CSgitFtdcInvestorPositionField["InstrumentID"] = "string"
#经纪公司代码
CSgitFtdcInvestorPositionField["BrokerID"] = "string"
#投资者代码
CSgitFtdcInvestorPositionField["InvestorID"] = "string"
#持仓多空方向
CSgitFtdcInvestorPositionField["PosiDirection"] = "char"
#投机套保标志
CSgitFtdcInvestorPositionField["HedgeFlag"] = "char"
#持仓日期
CSgitFtdcInvestorPositionField["PositionDate"] = "char"
#上日持仓
CSgitFtdcInvestorPositionField["YdPosition"] = "int"
#今日持仓
CSgitFtdcInvestorPositionField["Position"] = "int"
#多头冻结
CSgitFtdcInvestorPositionField["LongFrozen"] = "int"
#空头冻结
CSgitFtdcInvestorPositionField["ShortFrozen"] = "int"
#开仓冻结金额
CSgitFtdcInvestorPositionField["LongFrozenAmount"] = "float"
#开仓冻结金额
CSgitFtdcInvestorPositionField["ShortFrozenAmount"] = "float"
#开仓量
CSgitFtdcInvestorPositionField["OpenVolume"] = "int"
#平仓量
CSgitFtdcInvestorPositionField["CloseVolume"] = "int"
#开仓金额
CSgitFtdcInvestorPositionField["OpenAmount"] = "float"
#平仓金额
CSgitFtdcInvestorPositionField["CloseAmount"] = "float"
#持仓成本
CSgitFtdcInvestorPositionField["PositionCost"] = "float"
#上次占用的保证金
CSgitFtdcInvestorPositionField["PreMargin"] = "float"
#占用的保证金
CSgitFtdcInvestorPositionField["UseMargin"] = "float"
#冻结的保证金
CSgitFtdcInvestorPositionField["FrozenMargin"] = "float"
#冻结的资金
CSgitFtdcInvestorPositionField["FrozenCash"] = "float"
#冻结的手续费
CSgitFtdcInvestorPositionField["FrozenCommission"] = "float"
#资金差额
CSgitFtdcInvestorPositionField["CashIn"] = "float"
#手续费
CSgitFtdcInvestorPositionField["Commission"] = "float"
#平仓盈亏
CSgitFtdcInvestorPositionField["CloseProfit"] = "float"
#持仓盈亏
CSgitFtdcInvestorPositionField["PositionProfit"] = "float"
#上次结算价
CSgitFtdcInvestorPositionField["PreSettlementPrice"] = "float"
#本次结算价
CSgitFtdcInvestorPositionField["SettlementPrice"] = "float"
#交易日
CSgitFtdcInvestorPositionField["TradingDay"] = "string"
#结算编号
CSgitFtdcInvestorPositionField["SettlementID"] = "int"
#开仓成本
CSgitFtdcInvestorPositionField["OpenCost"] = "float"
#交易所保证金
CSgitFtdcInvestorPositionField["ExchangeMargin"] = "float"
#组合成交形成的持仓
CSgitFtdcInvestorPositionField["CombPosition"] = "int"
#组合多头冻结
CSgitFtdcInvestorPositionField["CombLongFrozen"] = "int"
#组合空头冻结
CSgitFtdcInvestorPositionField["CombShortFrozen"] = "int"
#逐日盯市平仓盈亏
CSgitFtdcInvestorPositionField["CloseProfitByDate"] = "float"
#逐笔对冲平仓盈亏
CSgitFtdcInvestorPositionField["CloseProfitByTrade"] = "float"
#今日持仓
CSgitFtdcInvestorPositionField["TodayPosition"] = "int"
#保证金率
CSgitFtdcInvestorPositionField["MarginRateByMoney"] = "float"
#保证金率(按手数)
CSgitFtdcInvestorPositionField["MarginRateByVolume"] = "float"
structDict['CSgitFtdcInvestorPositionField'] = CSgitFtdcInvestorPositionField


#合约保证金率
CSgitFtdcInstrumentMarginRateField = {}
#合约代码
CSgitFtdcInstrumentMarginRateField["InstrumentID"] = "string"
#投资者范围
CSgitFtdcInstrumentMarginRateField["InvestorRange"] = "char"
#经纪公司代码
CSgitFtdcInstrumentMarginRateField["BrokerID"] = "string"
#投资者代码
CSgitFtdcInstrumentMarginRateField["InvestorID"] = "string"
#投机套保标志
CSgitFtdcInstrumentMarginRateField["HedgeFlag"] = "char"
#多头保证金率
CSgitFtdcInstrumentMarginRateField["LongMarginRatioByMoney"] = "float"
#多头保证金费
CSgitFtdcInstrumentMarginRateField["LongMarginRatioByVolume"] = "float"
#空头保证金率
CSgitFtdcInstrumentMarginRateField["ShortMarginRatioByMoney"] = "float"
#空头保证金费
CSgitFtdcInstrumentMarginRateField["ShortMarginRatioByVolume"] = "float"
#是否相对交易所收取
CSgitFtdcInstrumentMarginRateField["IsRelative"] = "int"
structDict['CSgitFtdcInstrumentMarginRateField'] = CSgitFtdcInstrumentMarginRateField


#合约手续费率
CSgitFtdcInstrumentCommissionRateField = {}
#合约代码
CSgitFtdcInstrumentCommissionRateField["InstrumentID"] = "string"
#投资者范围
CSgitFtdcInstrumentCommissionRateField["InvestorRange"] = "char"
#经纪公司代码
CSgitFtdcInstrumentCommissionRateField["BrokerID"] = "string"
#投资者代码
CSgitFtdcInstrumentCommissionRateField["InvestorID"] = "string"
#开仓手续费率
CSgitFtdcInstrumentCommissionRateField["OpenRatioByMoney"] = "float"
#开仓手续费
CSgitFtdcInstrumentCommissionRateField["OpenRatioByVolume"] = "float"
#平仓手续费率
CSgitFtdcInstrumentCommissionRateField["CloseRatioByMoney"] = "float"
#平仓手续费
CSgitFtdcInstrumentCommissionRateField["CloseRatioByVolume"] = "float"
#平今手续费率
CSgitFtdcInstrumentCommissionRateField["CloseTodayRatioByMoney"] = "float"
#平今手续费
CSgitFtdcInstrumentCommissionRateField["CloseTodayRatioByVolume"] = "float"
structDict['CSgitFtdcInstrumentCommissionRateField'] = CSgitFtdcInstrumentCommissionRateField


#深度行情
CSgitFtdcDepthMarketDataField = {}
#交易日
CSgitFtdcDepthMarketDataField["TradingDay"] = "string"
#合约代码
CSgitFtdcDepthMarketDataField["InstrumentID"] = "string"
#交易所代码
CSgitFtdcDepthMarketDataField["ExchangeID"] = "string"
#合约在交易所的代码
CSgitFtdcDepthMarketDataField["ExchangeInstID"] = "string"
#最新价
CSgitFtdcDepthMarketDataField["LastPrice"] = "float"
#上次结算价
CSgitFtdcDepthMarketDataField["PreSettlementPrice"] = "float"
#昨收盘
CSgitFtdcDepthMarketDataField["PreClosePrice"] = "float"
#昨持仓量
CSgitFtdcDepthMarketDataField["PreOpenInterest"] = "float"
#今开盘
CSgitFtdcDepthMarketDataField["OpenPrice"] = "float"
#最高价
CSgitFtdcDepthMarketDataField["HighestPrice"] = "float"
#最低价
CSgitFtdcDepthMarketDataField["LowestPrice"] = "float"
#数量
CSgitFtdcDepthMarketDataField["Volume"] = "int"
#成交金额
CSgitFtdcDepthMarketDataField["Turnover"] = "float"
#持仓量
CSgitFtdcDepthMarketDataField["OpenInterest"] = "float"
#今收盘
CSgitFtdcDepthMarketDataField["ClosePrice"] = "float"
#本次结算价
CSgitFtdcDepthMarketDataField["SettlementPrice"] = "float"
#涨停板价
CSgitFtdcDepthMarketDataField["UpperLimitPrice"] = "float"
#跌停板价
CSgitFtdcDepthMarketDataField["LowerLimitPrice"] = "float"
#昨虚实度
CSgitFtdcDepthMarketDataField["PreDelta"] = "float"
#今虚实度
CSgitFtdcDepthMarketDataField["CurrDelta"] = "float"
#最后修改时间
CSgitFtdcDepthMarketDataField["UpdateTime"] = "string"
#最后修改毫秒
CSgitFtdcDepthMarketDataField["UpdateMillisec"] = "int"
#申买价一
CSgitFtdcDepthMarketDataField["BidPrice1"] = "float"
#申买量一
CSgitFtdcDepthMarketDataField["BidVolume1"] = "int"
#申卖价一
CSgitFtdcDepthMarketDataField["AskPrice1"] = "float"
#申卖量一
CSgitFtdcDepthMarketDataField["AskVolume1"] = "int"
#申买价二
CSgitFtdcDepthMarketDataField["BidPrice2"] = "float"
#申买量二
CSgitFtdcDepthMarketDataField["BidVolume2"] = "int"
#申卖价二
CSgitFtdcDepthMarketDataField["AskPrice2"] = "float"
#申卖量二
CSgitFtdcDepthMarketDataField["AskVolume2"] = "int"
#申买价三
CSgitFtdcDepthMarketDataField["BidPrice3"] = "float"
#申买量三
CSgitFtdcDepthMarketDataField["BidVolume3"] = "int"
#申卖价三
CSgitFtdcDepthMarketDataField["AskPrice3"] = "float"
#申卖量三
CSgitFtdcDepthMarketDataField["AskVolume3"] = "int"
#申买价四
CSgitFtdcDepthMarketDataField["BidPrice4"] = "float"
#申买量四
CSgitFtdcDepthMarketDataField["BidVolume4"] = "int"
#申卖价四
CSgitFtdcDepthMarketDataField["AskPrice4"] = "float"
#申卖量四
CSgitFtdcDepthMarketDataField["AskVolume4"] = "int"
#申买价五
CSgitFtdcDepthMarketDataField["BidPrice5"] = "float"
#申买量五
CSgitFtdcDepthMarketDataField["BidVolume5"] = "int"
#申卖价五
CSgitFtdcDepthMarketDataField["AskPrice5"] = "float"
#申卖量五
CSgitFtdcDepthMarketDataField["AskVolume5"] = "int"
#当日均价
CSgitFtdcDepthMarketDataField["AveragePrice"] = "float"
structDict['CSgitFtdcDepthMarketDataField'] = CSgitFtdcDepthMarketDataField


#投资者合约交易权限
CSgitFtdcInstrumentTradingRightField = {}
#合约代码
CSgitFtdcInstrumentTradingRightField["InstrumentID"] = "string"
#投资者范围
CSgitFtdcInstrumentTradingRightField["InvestorRange"] = "char"
#经纪公司代码
CSgitFtdcInstrumentTradingRightField["BrokerID"] = "string"
#投资者代码
CSgitFtdcInstrumentTradingRightField["InvestorID"] = "string"
#交易权限
CSgitFtdcInstrumentTradingRightField["TradingRight"] = "char"
structDict['CSgitFtdcInstrumentTradingRightField'] = CSgitFtdcInstrumentTradingRightField


#经纪公司用户
CSgitFtdcBrokerUserField = {}
#经纪公司代码
CSgitFtdcBrokerUserField["BrokerID"] = "string"
#用户代码
CSgitFtdcBrokerUserField["UserID"] = "string"
#用户名称
CSgitFtdcBrokerUserField["UserName"] = "string"
#用户类型
CSgitFtdcBrokerUserField["UserType"] = "char"
#是否活跃
CSgitFtdcBrokerUserField["IsActive"] = "int"
#是否使用令牌
CSgitFtdcBrokerUserField["IsUsingOTP"] = "int"
structDict['CSgitFtdcBrokerUserField'] = CSgitFtdcBrokerUserField


#经纪公司用户口令
CSgitFtdcBrokerUserPasswordField = {}
#经纪公司代码
CSgitFtdcBrokerUserPasswordField["BrokerID"] = "string"
#用户代码
CSgitFtdcBrokerUserPasswordField["UserID"] = "string"
#密码
CSgitFtdcBrokerUserPasswordField["Password"] = "string"
structDict['CSgitFtdcBrokerUserPasswordField'] = CSgitFtdcBrokerUserPasswordField


#经纪公司用户功能权限
CSgitFtdcBrokerUserFunctionField = {}
#经纪公司代码
CSgitFtdcBrokerUserFunctionField["BrokerID"] = "string"
#用户代码
CSgitFtdcBrokerUserFunctionField["UserID"] = "string"
#经纪公司功能代码
CSgitFtdcBrokerUserFunctionField["BrokerFunctionCode"] = "char"
structDict['CSgitFtdcBrokerUserFunctionField'] = CSgitFtdcBrokerUserFunctionField


#交易所交易员报盘机
CSgitFtdcTraderOfferField = {}
#交易所代码
CSgitFtdcTraderOfferField["ExchangeID"] = "string"
#交易所交易员代码
CSgitFtdcTraderOfferField["TraderID"] = "string"
#会员代码
CSgitFtdcTraderOfferField["ParticipantID"] = "string"
#密码
CSgitFtdcTraderOfferField["Password"] = "string"
#安装编号
CSgitFtdcTraderOfferField["InstallID"] = "int"
#本地报单编号
CSgitFtdcTraderOfferField["OrderLocalID"] = "string"
#交易所交易员连接状态
CSgitFtdcTraderOfferField["TraderConnectStatus"] = "char"
#发出连接请求的日期
CSgitFtdcTraderOfferField["ConnectRequestDate"] = "string"
#发出连接请求的时间
CSgitFtdcTraderOfferField["ConnectRequestTime"] = "string"
#上次报告日期
CSgitFtdcTraderOfferField["LastReportDate"] = "string"
#上次报告时间
CSgitFtdcTraderOfferField["LastReportTime"] = "string"
#完成连接日期
CSgitFtdcTraderOfferField["ConnectDate"] = "string"
#完成连接时间
CSgitFtdcTraderOfferField["ConnectTime"] = "string"
#启动日期
CSgitFtdcTraderOfferField["StartDate"] = "string"
#启动时间
CSgitFtdcTraderOfferField["StartTime"] = "string"
#交易日
CSgitFtdcTraderOfferField["TradingDay"] = "string"
#经纪公司代码
CSgitFtdcTraderOfferField["BrokerID"] = "string"
#本席位最大成交编号
CSgitFtdcTraderOfferField["MaxTradeID"] = "string"
#本席位最大报单备拷
CSgitFtdcTraderOfferField["MaxOrderMessageReference"] = "string"
structDict['CSgitFtdcTraderOfferField'] = CSgitFtdcTraderOfferField


#投资者结算结果
CSgitFtdcSettlementInfoField = {}
#交易日
CSgitFtdcSettlementInfoField["TradingDay"] = "string"
#结算编号
CSgitFtdcSettlementInfoField["SettlementID"] = "int"
#经纪公司代码
CSgitFtdcSettlementInfoField["BrokerID"] = "string"
#投资者代码
CSgitFtdcSettlementInfoField["InvestorID"] = "string"
#序号
CSgitFtdcSettlementInfoField["SequenceNo"] = "int"
#消息正文
CSgitFtdcSettlementInfoField["Content"] = "string"
structDict['CSgitFtdcSettlementInfoField'] = CSgitFtdcSettlementInfoField


#合约保证金率调整
CSgitFtdcInstrumentMarginRateAdjustField = {}
#合约代码
CSgitFtdcInstrumentMarginRateAdjustField["InstrumentID"] = "string"
#投资者范围
CSgitFtdcInstrumentMarginRateAdjustField["InvestorRange"] = "char"
#经纪公司代码
CSgitFtdcInstrumentMarginRateAdjustField["BrokerID"] = "string"
#投资者代码
CSgitFtdcInstrumentMarginRateAdjustField["InvestorID"] = "string"
#投机套保标志
CSgitFtdcInstrumentMarginRateAdjustField["HedgeFlag"] = "char"
#多头保证金率
CSgitFtdcInstrumentMarginRateAdjustField["LongMarginRatioByMoney"] = "float"
#多头保证金费
CSgitFtdcInstrumentMarginRateAdjustField["LongMarginRatioByVolume"] = "float"
#空头保证金率
CSgitFtdcInstrumentMarginRateAdjustField["ShortMarginRatioByMoney"] = "float"
#空头保证金费
CSgitFtdcInstrumentMarginRateAdjustField["ShortMarginRatioByVolume"] = "float"
#是否相对交易所收取
CSgitFtdcInstrumentMarginRateAdjustField["IsRelative"] = "int"
structDict['CSgitFtdcInstrumentMarginRateAdjustField'] = CSgitFtdcInstrumentMarginRateAdjustField


#交易所保证金率
CSgitFtdcExchangeMarginRateField = {}
#经纪公司代码
CSgitFtdcExchangeMarginRateField["BrokerID"] = "string"
#合约代码
CSgitFtdcExchangeMarginRateField["InstrumentID"] = "string"
#投机套保标志
CSgitFtdcExchangeMarginRateField["HedgeFlag"] = "char"
#多头保证金率
CSgitFtdcExchangeMarginRateField["LongMarginRatioByMoney"] = "float"
#多头保证金费
CSgitFtdcExchangeMarginRateField["LongMarginRatioByVolume"] = "float"
#空头保证金率
CSgitFtdcExchangeMarginRateField["ShortMarginRatioByMoney"] = "float"
#空头保证金费
CSgitFtdcExchangeMarginRateField["ShortMarginRatioByVolume"] = "float"
structDict['CSgitFtdcExchangeMarginRateField'] = CSgitFtdcExchangeMarginRateField


#交易所保证金率调整
CSgitFtdcExchangeMarginRateAdjustField = {}
#经纪公司代码
CSgitFtdcExchangeMarginRateAdjustField["BrokerID"] = "string"
#合约代码
CSgitFtdcExchangeMarginRateAdjustField["InstrumentID"] = "string"
#投机套保标志
CSgitFtdcExchangeMarginRateAdjustField["HedgeFlag"] = "char"
#跟随交易所投资者多头保证金率
CSgitFtdcExchangeMarginRateAdjustField["LongMarginRatioByMoney"] = "float"
#跟随交易所投资者多头保证金费
CSgitFtdcExchangeMarginRateAdjustField["LongMarginRatioByVolume"] = "float"
#跟随交易所投资者空头保证金率
CSgitFtdcExchangeMarginRateAdjustField["ShortMarginRatioByMoney"] = "float"
#跟随交易所投资者空头保证金费
CSgitFtdcExchangeMarginRateAdjustField["ShortMarginRatioByVolume"] = "float"
#交易所多头保证金率
CSgitFtdcExchangeMarginRateAdjustField["ExchLongMarginRatioByMoney"] = "float"
#交易所多头保证金费
CSgitFtdcExchangeMarginRateAdjustField["ExchLongMarginRatioByVolume"] = "float"
#交易所空头保证金率
CSgitFtdcExchangeMarginRateAdjustField["ExchShortMarginRatioByMoney"] = "float"
#交易所空头保证金费
CSgitFtdcExchangeMarginRateAdjustField["ExchShortMarginRatioByVolume"] = "float"
#不跟随交易所投资者多头保证金率
CSgitFtdcExchangeMarginRateAdjustField["NoLongMarginRatioByMoney"] = "float"
#不跟随交易所投资者多头保证金费
CSgitFtdcExchangeMarginRateAdjustField["NoLongMarginRatioByVolume"] = "float"
#不跟随交易所投资者空头保证金率
CSgitFtdcExchangeMarginRateAdjustField["NoShortMarginRatioByMoney"] = "float"
#不跟随交易所投资者空头保证金费
CSgitFtdcExchangeMarginRateAdjustField["NoShortMarginRatioByVolume"] = "float"
structDict['CSgitFtdcExchangeMarginRateAdjustField'] = CSgitFtdcExchangeMarginRateAdjustField


#结算引用
CSgitFtdcSettlementRefField = {}
#交易日
CSgitFtdcSettlementRefField["TradingDay"] = "string"
#结算编号
CSgitFtdcSettlementRefField["SettlementID"] = "int"
structDict['CSgitFtdcSettlementRefField'] = CSgitFtdcSettlementRefField


#当前时间
CSgitFtdcCurrentTimeField = {}
#当前日期
CSgitFtdcCurrentTimeField["CurrDate"] = "string"
#当前时间
CSgitFtdcCurrentTimeField["CurrTime"] = "string"
#当前时间（毫秒）
CSgitFtdcCurrentTimeField["CurrMillisec"] = "int"
structDict['CSgitFtdcCurrentTimeField'] = CSgitFtdcCurrentTimeField


#通讯阶段
CSgitFtdcCommPhaseField = {}
#交易日
CSgitFtdcCommPhaseField["TradingDay"] = "string"
#通讯时段编号
CSgitFtdcCommPhaseField["CommPhaseNo"] = "short"
structDict['CSgitFtdcCommPhaseField'] = CSgitFtdcCommPhaseField


#登录信息
CSgitFtdcLoginInfoField = {}
#前置编号
CSgitFtdcLoginInfoField["FrontID"] = "int"
#会话编号
CSgitFtdcLoginInfoField["SessionID"] = "int"
#经纪公司代码
CSgitFtdcLoginInfoField["BrokerID"] = "string"
#用户代码
CSgitFtdcLoginInfoField["UserID"] = "string"
#登录日期
CSgitFtdcLoginInfoField["LoginDate"] = "string"
#登录时间
CSgitFtdcLoginInfoField["LoginTime"] = "string"
#IP地址
CSgitFtdcLoginInfoField["IPAddress"] = "string"
#用户端产品信息
CSgitFtdcLoginInfoField["UserProductInfo"] = "string"
#接口端产品信息
CSgitFtdcLoginInfoField["InterfaceProductInfo"] = "string"
#协议信息
CSgitFtdcLoginInfoField["ProtocolInfo"] = "string"
#系统名称
CSgitFtdcLoginInfoField["SystemName"] = "string"
#密码
CSgitFtdcLoginInfoField["Password"] = "string"
#最大报单引用
CSgitFtdcLoginInfoField["MaxOrderRef"] = "string"
#上期所时间
CSgitFtdcLoginInfoField["SHFETime"] = "string"
#大商所时间
CSgitFtdcLoginInfoField["DCETime"] = "string"
#郑商所时间
CSgitFtdcLoginInfoField["CZCETime"] = "string"
#中金所时间
CSgitFtdcLoginInfoField["FFEXTime"] = "string"
#Mac地址
CSgitFtdcLoginInfoField["MacAddress"] = "string"
#动态密码
CSgitFtdcLoginInfoField["OneTimePassword"] = "string"
structDict['CSgitFtdcLoginInfoField'] = CSgitFtdcLoginInfoField


#登录信息
CSgitFtdcLogoutAllField = {}
#前置编号
CSgitFtdcLogoutAllField["FrontID"] = "int"
#会话编号
CSgitFtdcLogoutAllField["SessionID"] = "int"
#系统名称
CSgitFtdcLogoutAllField["SystemName"] = "string"
structDict['CSgitFtdcLogoutAllField'] = CSgitFtdcLogoutAllField


#前置状态
CSgitFtdcFrontStatusField = {}
#前置编号
CSgitFtdcFrontStatusField["FrontID"] = "int"
#上次报告日期
CSgitFtdcFrontStatusField["LastReportDate"] = "string"
#上次报告时间
CSgitFtdcFrontStatusField["LastReportTime"] = "string"
#是否活跃
CSgitFtdcFrontStatusField["IsActive"] = "int"
structDict['CSgitFtdcFrontStatusField'] = CSgitFtdcFrontStatusField


#用户口令变更
CSgitFtdcUserPasswordUpdateField = {}
#经纪公司代码
CSgitFtdcUserPasswordUpdateField["BrokerID"] = "string"
#用户代码
CSgitFtdcUserPasswordUpdateField["UserID"] = "string"
#原来的口令
CSgitFtdcUserPasswordUpdateField["OldPassword"] = "string"
#新的口令
CSgitFtdcUserPasswordUpdateField["NewPassword"] = "string"
structDict['CSgitFtdcUserPasswordUpdateField'] = CSgitFtdcUserPasswordUpdateField


#输入报单
CSgitFtdcInputOrderField = {}
#经纪公司代码
CSgitFtdcInputOrderField["BrokerID"] = "string"
#投资者代码
CSgitFtdcInputOrderField["InvestorID"] = "string"
#合约代码
CSgitFtdcInputOrderField["InstrumentID"] = "string"
#报单引用
CSgitFtdcInputOrderField["OrderRef"] = "string"
#用户代码
CSgitFtdcInputOrderField["UserID"] = "string"
#报单价格条件
CSgitFtdcInputOrderField["OrderPriceType"] = "char"
#买卖方向
CSgitFtdcInputOrderField["Direction"] = "char"
#组合开平标志
CSgitFtdcInputOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CSgitFtdcInputOrderField["CombHedgeFlag"] = "string"
#价格
CSgitFtdcInputOrderField["LimitPrice"] = "float"
#数量
CSgitFtdcInputOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CSgitFtdcInputOrderField["TimeCondition"] = "char"
#GTD日期
CSgitFtdcInputOrderField["GTDDate"] = "string"
#成交量类型
CSgitFtdcInputOrderField["VolumeCondition"] = "char"
#最小成交量
CSgitFtdcInputOrderField["MinVolume"] = "int"
#触发条件
CSgitFtdcInputOrderField["ContingentCondition"] = "char"
#止损价
CSgitFtdcInputOrderField["StopPrice"] = "float"
#强平原因
CSgitFtdcInputOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CSgitFtdcInputOrderField["IsAutoSuspend"] = "int"
#业务单元
CSgitFtdcInputOrderField["BusinessUnit"] = "string"
#请求编号
CSgitFtdcInputOrderField["RequestID"] = "int"
#用户强评标志
CSgitFtdcInputOrderField["UserForceClose"] = "int"
structDict['CSgitFtdcInputOrderField'] = CSgitFtdcInputOrderField


#报单
CSgitFtdcOrderField = {}
#经纪公司代码
CSgitFtdcOrderField["BrokerID"] = "string"
#投资者代码
CSgitFtdcOrderField["InvestorID"] = "string"
#合约代码
CSgitFtdcOrderField["InstrumentID"] = "string"
#报单引用
CSgitFtdcOrderField["OrderRef"] = "string"
#用户代码
CSgitFtdcOrderField["UserID"] = "string"
#报单价格条件
CSgitFtdcOrderField["OrderPriceType"] = "char"
#买卖方向
CSgitFtdcOrderField["Direction"] = "char"
#组合开平标志
CSgitFtdcOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CSgitFtdcOrderField["CombHedgeFlag"] = "string"
#价格
CSgitFtdcOrderField["LimitPrice"] = "float"
#数量
CSgitFtdcOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CSgitFtdcOrderField["TimeCondition"] = "char"
#GTD日期
CSgitFtdcOrderField["GTDDate"] = "string"
#成交量类型
CSgitFtdcOrderField["VolumeCondition"] = "char"
#最小成交量
CSgitFtdcOrderField["MinVolume"] = "int"
#触发条件
CSgitFtdcOrderField["ContingentCondition"] = "char"
#止损价
CSgitFtdcOrderField["StopPrice"] = "float"
#强平原因
CSgitFtdcOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CSgitFtdcOrderField["IsAutoSuspend"] = "int"
#业务单元
CSgitFtdcOrderField["BusinessUnit"] = "string"
#请求编号
CSgitFtdcOrderField["RequestID"] = "int"
#本地报单编号
CSgitFtdcOrderField["OrderLocalID"] = "string"
#交易所代码
CSgitFtdcOrderField["ExchangeID"] = "string"
#会员代码
CSgitFtdcOrderField["ParticipantID"] = "string"
#客户代码
CSgitFtdcOrderField["ClientID"] = "string"
#合约在交易所的代码
CSgitFtdcOrderField["ExchangeInstID"] = "string"
#交易所交易员代码
CSgitFtdcOrderField["TraderID"] = "string"
#安装编号
CSgitFtdcOrderField["InstallID"] = "int"
#报单提交状态
CSgitFtdcOrderField["OrderSubmitStatus"] = "char"
#报单提示序号
CSgitFtdcOrderField["NotifySequence"] = "int"
#交易日
CSgitFtdcOrderField["TradingDay"] = "string"
#结算编号
CSgitFtdcOrderField["SettlementID"] = "int"
#报单编号
CSgitFtdcOrderField["OrderSysID"] = "string"
#报单来源
CSgitFtdcOrderField["OrderSource"] = "char"
#报单状态
CSgitFtdcOrderField["OrderStatus"] = "char"
#报单类型
CSgitFtdcOrderField["OrderType"] = "char"
#今成交数量
CSgitFtdcOrderField["VolumeTraded"] = "int"
#剩余数量
CSgitFtdcOrderField["VolumeTotal"] = "int"
#报单日期
CSgitFtdcOrderField["InsertDate"] = "string"
#委托时间
CSgitFtdcOrderField["InsertTime"] = "string"
#激活时间
CSgitFtdcOrderField["ActiveTime"] = "string"
#挂起时间
CSgitFtdcOrderField["SuspendTime"] = "string"
#最后修改时间
CSgitFtdcOrderField["UpdateTime"] = "string"
#撤销时间
CSgitFtdcOrderField["CancelTime"] = "string"
#最后修改交易所交易员代码
CSgitFtdcOrderField["ActiveTraderID"] = "string"
#结算会员编号
CSgitFtdcOrderField["ClearingPartID"] = "string"
#序号
CSgitFtdcOrderField["SequenceNo"] = "int"
#前置编号
CSgitFtdcOrderField["FrontID"] = "int"
#会话编号
CSgitFtdcOrderField["SessionID"] = "int"
#用户端产品信息
CSgitFtdcOrderField["UserProductInfo"] = "string"
#状态信息
CSgitFtdcOrderField["StatusMsg"] = "string"
#用户强评标志
CSgitFtdcOrderField["UserForceClose"] = "int"
#操作用户代码
CSgitFtdcOrderField["ActiveUserID"] = "string"
#经纪公司报单编号
CSgitFtdcOrderField["BrokerOrderSeq"] = "int"
#相关报单
CSgitFtdcOrderField["RelativeOrderSysID"] = "string"
structDict['CSgitFtdcOrderField'] = CSgitFtdcOrderField


#交易所报单
CSgitFtdcExchangeOrderField = {}
#报单价格条件
CSgitFtdcExchangeOrderField["OrderPriceType"] = "char"
#买卖方向
CSgitFtdcExchangeOrderField["Direction"] = "char"
#组合开平标志
CSgitFtdcExchangeOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CSgitFtdcExchangeOrderField["CombHedgeFlag"] = "string"
#价格
CSgitFtdcExchangeOrderField["LimitPrice"] = "float"
#数量
CSgitFtdcExchangeOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CSgitFtdcExchangeOrderField["TimeCondition"] = "char"
#GTD日期
CSgitFtdcExchangeOrderField["GTDDate"] = "string"
#成交量类型
CSgitFtdcExchangeOrderField["VolumeCondition"] = "char"
#最小成交量
CSgitFtdcExchangeOrderField["MinVolume"] = "int"
#触发条件
CSgitFtdcExchangeOrderField["ContingentCondition"] = "char"
#止损价
CSgitFtdcExchangeOrderField["StopPrice"] = "float"
#强平原因
CSgitFtdcExchangeOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CSgitFtdcExchangeOrderField["IsAutoSuspend"] = "int"
#业务单元
CSgitFtdcExchangeOrderField["BusinessUnit"] = "string"
#请求编号
CSgitFtdcExchangeOrderField["RequestID"] = "int"
#本地报单编号
CSgitFtdcExchangeOrderField["OrderLocalID"] = "string"
#交易所代码
CSgitFtdcExchangeOrderField["ExchangeID"] = "string"
#会员代码
CSgitFtdcExchangeOrderField["ParticipantID"] = "string"
#客户代码
CSgitFtdcExchangeOrderField["ClientID"] = "string"
#合约在交易所的代码
CSgitFtdcExchangeOrderField["ExchangeInstID"] = "string"
#交易所交易员代码
CSgitFtdcExchangeOrderField["TraderID"] = "string"
#安装编号
CSgitFtdcExchangeOrderField["InstallID"] = "int"
#报单提交状态
CSgitFtdcExchangeOrderField["OrderSubmitStatus"] = "char"
#报单提示序号
CSgitFtdcExchangeOrderField["NotifySequence"] = "int"
#交易日
CSgitFtdcExchangeOrderField["TradingDay"] = "string"
#结算编号
CSgitFtdcExchangeOrderField["SettlementID"] = "int"
#报单编号
CSgitFtdcExchangeOrderField["OrderSysID"] = "string"
#报单来源
CSgitFtdcExchangeOrderField["OrderSource"] = "char"
#报单状态
CSgitFtdcExchangeOrderField["OrderStatus"] = "char"
#报单类型
CSgitFtdcExchangeOrderField["OrderType"] = "char"
#今成交数量
CSgitFtdcExchangeOrderField["VolumeTraded"] = "int"
#剩余数量
CSgitFtdcExchangeOrderField["VolumeTotal"] = "int"
#报单日期
CSgitFtdcExchangeOrderField["InsertDate"] = "string"
#委托时间
CSgitFtdcExchangeOrderField["InsertTime"] = "string"
#激活时间
CSgitFtdcExchangeOrderField["ActiveTime"] = "string"
#挂起时间
CSgitFtdcExchangeOrderField["SuspendTime"] = "string"
#最后修改时间
CSgitFtdcExchangeOrderField["UpdateTime"] = "string"
#撤销时间
CSgitFtdcExchangeOrderField["CancelTime"] = "string"
#最后修改交易所交易员代码
CSgitFtdcExchangeOrderField["ActiveTraderID"] = "string"
#结算会员编号
CSgitFtdcExchangeOrderField["ClearingPartID"] = "string"
#序号
CSgitFtdcExchangeOrderField["SequenceNo"] = "int"
structDict['CSgitFtdcExchangeOrderField'] = CSgitFtdcExchangeOrderField


#交易所报单插入失败
CSgitFtdcExchangeOrderInsertErrorField = {}
#交易所代码
CSgitFtdcExchangeOrderInsertErrorField["ExchangeID"] = "string"
#会员代码
CSgitFtdcExchangeOrderInsertErrorField["ParticipantID"] = "string"
#交易所交易员代码
CSgitFtdcExchangeOrderInsertErrorField["TraderID"] = "string"
#安装编号
CSgitFtdcExchangeOrderInsertErrorField["InstallID"] = "int"
#本地报单编号
CSgitFtdcExchangeOrderInsertErrorField["OrderLocalID"] = "string"
#错误代码
CSgitFtdcExchangeOrderInsertErrorField["ErrorID"] = "int"
#错误信息
CSgitFtdcExchangeOrderInsertErrorField["ErrorMsg"] = "string"
structDict['CSgitFtdcExchangeOrderInsertErrorField'] = CSgitFtdcExchangeOrderInsertErrorField


#输入报单操作
CSgitFtdcInputOrderActionField = {}
#经纪公司代码
CSgitFtdcInputOrderActionField["BrokerID"] = "string"
#投资者代码
CSgitFtdcInputOrderActionField["InvestorID"] = "string"
#报单操作引用
CSgitFtdcInputOrderActionField["OrderActionRef"] = "int"
#报单引用
CSgitFtdcInputOrderActionField["OrderRef"] = "string"
#请求编号
CSgitFtdcInputOrderActionField["RequestID"] = "int"
#前置编号
CSgitFtdcInputOrderActionField["FrontID"] = "int"
#会话编号
CSgitFtdcInputOrderActionField["SessionID"] = "int"
#交易所代码
CSgitFtdcInputOrderActionField["ExchangeID"] = "string"
#报单编号
CSgitFtdcInputOrderActionField["OrderSysID"] = "string"
#操作标志
CSgitFtdcInputOrderActionField["ActionFlag"] = "char"
#价格
CSgitFtdcInputOrderActionField["LimitPrice"] = "float"
#数量变化
CSgitFtdcInputOrderActionField["VolumeChange"] = "int"
#用户代码
CSgitFtdcInputOrderActionField["UserID"] = "string"
#合约代码
CSgitFtdcInputOrderActionField["InstrumentID"] = "string"
structDict['CSgitFtdcInputOrderActionField'] = CSgitFtdcInputOrderActionField


#报单操作
CSgitFtdcOrderActionField = {}
#经纪公司代码
CSgitFtdcOrderActionField["BrokerID"] = "string"
#投资者代码
CSgitFtdcOrderActionField["InvestorID"] = "string"
#报单操作引用
CSgitFtdcOrderActionField["OrderActionRef"] = "int"
#报单引用
CSgitFtdcOrderActionField["OrderRef"] = "string"
#请求编号
CSgitFtdcOrderActionField["RequestID"] = "int"
#前置编号
CSgitFtdcOrderActionField["FrontID"] = "int"
#会话编号
CSgitFtdcOrderActionField["SessionID"] = "int"
#交易所代码
CSgitFtdcOrderActionField["ExchangeID"] = "string"
#报单编号
CSgitFtdcOrderActionField["OrderSysID"] = "string"
#操作标志
CSgitFtdcOrderActionField["ActionFlag"] = "char"
#价格
CSgitFtdcOrderActionField["LimitPrice"] = "float"
#数量变化
CSgitFtdcOrderActionField["VolumeChange"] = "int"
#操作日期
CSgitFtdcOrderActionField["ActionDate"] = "string"
#操作时间
CSgitFtdcOrderActionField["ActionTime"] = "string"
#交易所交易员代码
CSgitFtdcOrderActionField["TraderID"] = "string"
#安装编号
CSgitFtdcOrderActionField["InstallID"] = "int"
#本地报单编号
CSgitFtdcOrderActionField["OrderLocalID"] = "string"
#操作本地编号
CSgitFtdcOrderActionField["ActionLocalID"] = "string"
#会员代码
CSgitFtdcOrderActionField["ParticipantID"] = "string"
#客户代码
CSgitFtdcOrderActionField["ClientID"] = "string"
#业务单元
CSgitFtdcOrderActionField["BusinessUnit"] = "string"
#报单操作状态
CSgitFtdcOrderActionField["OrderActionStatus"] = "char"
#用户代码
CSgitFtdcOrderActionField["UserID"] = "string"
#状态信息
CSgitFtdcOrderActionField["StatusMsg"] = "string"
#合约代码
CSgitFtdcOrderActionField["InstrumentID"] = "string"
structDict['CSgitFtdcOrderActionField'] = CSgitFtdcOrderActionField


#交易所报单操作
CSgitFtdcExchangeOrderActionField = {}
#交易所代码
CSgitFtdcExchangeOrderActionField["ExchangeID"] = "string"
#报单编号
CSgitFtdcExchangeOrderActionField["OrderSysID"] = "string"
#操作标志
CSgitFtdcExchangeOrderActionField["ActionFlag"] = "char"
#价格
CSgitFtdcExchangeOrderActionField["LimitPrice"] = "float"
#数量变化
CSgitFtdcExchangeOrderActionField["VolumeChange"] = "int"
#操作日期
CSgitFtdcExchangeOrderActionField["ActionDate"] = "string"
#操作时间
CSgitFtdcExchangeOrderActionField["ActionTime"] = "string"
#交易所交易员代码
CSgitFtdcExchangeOrderActionField["TraderID"] = "string"
#安装编号
CSgitFtdcExchangeOrderActionField["InstallID"] = "int"
#本地报单编号
CSgitFtdcExchangeOrderActionField["OrderLocalID"] = "string"
#操作本地编号
CSgitFtdcExchangeOrderActionField["ActionLocalID"] = "string"
#会员代码
CSgitFtdcExchangeOrderActionField["ParticipantID"] = "string"
#客户代码
CSgitFtdcExchangeOrderActionField["ClientID"] = "string"
#业务单元
CSgitFtdcExchangeOrderActionField["BusinessUnit"] = "string"
#报单操作状态
CSgitFtdcExchangeOrderActionField["OrderActionStatus"] = "char"
#用户代码
CSgitFtdcExchangeOrderActionField["UserID"] = "string"
structDict['CSgitFtdcExchangeOrderActionField'] = CSgitFtdcExchangeOrderActionField


#交易所报单操作失败
CSgitFtdcExchangeOrderActionErrorField = {}
#交易所代码
CSgitFtdcExchangeOrderActionErrorField["ExchangeID"] = "string"
#报单编号
CSgitFtdcExchangeOrderActionErrorField["OrderSysID"] = "string"
#交易所交易员代码
CSgitFtdcExchangeOrderActionErrorField["TraderID"] = "string"
#安装编号
CSgitFtdcExchangeOrderActionErrorField["InstallID"] = "int"
#本地报单编号
CSgitFtdcExchangeOrderActionErrorField["OrderLocalID"] = "string"
#操作本地编号
CSgitFtdcExchangeOrderActionErrorField["ActionLocalID"] = "string"
#错误代码
CSgitFtdcExchangeOrderActionErrorField["ErrorID"] = "int"
#错误信息
CSgitFtdcExchangeOrderActionErrorField["ErrorMsg"] = "string"
structDict['CSgitFtdcExchangeOrderActionErrorField'] = CSgitFtdcExchangeOrderActionErrorField


#交易所成交
CSgitFtdcExchangeTradeField = {}
#交易所代码
CSgitFtdcExchangeTradeField["ExchangeID"] = "string"
#成交编号
CSgitFtdcExchangeTradeField["TradeID"] = "string"
#买卖方向
CSgitFtdcExchangeTradeField["Direction"] = "char"
#报单编号
CSgitFtdcExchangeTradeField["OrderSysID"] = "string"
#会员代码
CSgitFtdcExchangeTradeField["ParticipantID"] = "string"
#客户代码
CSgitFtdcExchangeTradeField["ClientID"] = "string"
#交易角色
CSgitFtdcExchangeTradeField["TradingRole"] = "char"
#合约在交易所的代码
CSgitFtdcExchangeTradeField["ExchangeInstID"] = "string"
#开平标志
CSgitFtdcExchangeTradeField["OffsetFlag"] = "char"
#投机套保标志
CSgitFtdcExchangeTradeField["HedgeFlag"] = "char"
#价格
CSgitFtdcExchangeTradeField["Price"] = "float"
#数量
CSgitFtdcExchangeTradeField["Volume"] = "int"
#成交时期
CSgitFtdcExchangeTradeField["TradeDate"] = "string"
#成交时间
CSgitFtdcExchangeTradeField["TradeTime"] = "string"
#成交类型
CSgitFtdcExchangeTradeField["TradeType"] = "char"
#成交价来源
CSgitFtdcExchangeTradeField["PriceSource"] = "char"
#交易所交易员代码
CSgitFtdcExchangeTradeField["TraderID"] = "string"
#本地报单编号
CSgitFtdcExchangeTradeField["OrderLocalID"] = "string"
#结算会员编号
CSgitFtdcExchangeTradeField["ClearingPartID"] = "string"
#业务单元
CSgitFtdcExchangeTradeField["BusinessUnit"] = "string"
#序号
CSgitFtdcExchangeTradeField["SequenceNo"] = "int"
#成交来源
CSgitFtdcExchangeTradeField["TradeSource"] = "char"
structDict['CSgitFtdcExchangeTradeField'] = CSgitFtdcExchangeTradeField


#成交
CSgitFtdcTradeField = {}
#经纪公司代码
CSgitFtdcTradeField["BrokerID"] = "string"
#投资者代码
CSgitFtdcTradeField["InvestorID"] = "string"
#合约代码
CSgitFtdcTradeField["InstrumentID"] = "string"
#报单引用
CSgitFtdcTradeField["OrderRef"] = "string"
#用户代码
CSgitFtdcTradeField["UserID"] = "string"
#交易所代码
CSgitFtdcTradeField["ExchangeID"] = "string"
#成交编号
CSgitFtdcTradeField["TradeID"] = "string"
#买卖方向
CSgitFtdcTradeField["Direction"] = "char"
#报单编号
CSgitFtdcTradeField["OrderSysID"] = "string"
#会员代码
CSgitFtdcTradeField["ParticipantID"] = "string"
#客户代码
CSgitFtdcTradeField["ClientID"] = "string"
#交易角色
CSgitFtdcTradeField["TradingRole"] = "char"
#合约在交易所的代码
CSgitFtdcTradeField["ExchangeInstID"] = "string"
#开平标志
CSgitFtdcTradeField["OffsetFlag"] = "char"
#投机套保标志
CSgitFtdcTradeField["HedgeFlag"] = "char"
#价格
CSgitFtdcTradeField["Price"] = "float"
#数量
CSgitFtdcTradeField["Volume"] = "int"
#成交时期
CSgitFtdcTradeField["TradeDate"] = "string"
#成交时间
CSgitFtdcTradeField["TradeTime"] = "string"
#成交类型
CSgitFtdcTradeField["TradeType"] = "char"
#成交价来源
CSgitFtdcTradeField["PriceSource"] = "char"
#交易所交易员代码
CSgitFtdcTradeField["TraderID"] = "string"
#本地报单编号
CSgitFtdcTradeField["OrderLocalID"] = "string"
#结算会员编号
CSgitFtdcTradeField["ClearingPartID"] = "string"
#业务单元
CSgitFtdcTradeField["BusinessUnit"] = "string"
#序号
CSgitFtdcTradeField["SequenceNo"] = "int"
#交易日
CSgitFtdcTradeField["TradingDay"] = "string"
#结算编号
CSgitFtdcTradeField["SettlementID"] = "int"
#经纪公司报单编号
CSgitFtdcTradeField["BrokerOrderSeq"] = "int"
#成交来源
CSgitFtdcTradeField["TradeSource"] = "char"
structDict['CSgitFtdcTradeField'] = CSgitFtdcTradeField


#用户会话
CSgitFtdcUserSessionField = {}
#前置编号
CSgitFtdcUserSessionField["FrontID"] = "int"
#会话编号
CSgitFtdcUserSessionField["SessionID"] = "int"
#经纪公司代码
CSgitFtdcUserSessionField["BrokerID"] = "string"
#用户代码
CSgitFtdcUserSessionField["UserID"] = "string"
#登录日期
CSgitFtdcUserSessionField["LoginDate"] = "string"
#登录时间
CSgitFtdcUserSessionField["LoginTime"] = "string"
#IP地址
CSgitFtdcUserSessionField["IPAddress"] = "string"
#用户端产品信息
CSgitFtdcUserSessionField["UserProductInfo"] = "string"
#接口端产品信息
CSgitFtdcUserSessionField["InterfaceProductInfo"] = "string"
#协议信息
CSgitFtdcUserSessionField["ProtocolInfo"] = "string"
#Mac地址
CSgitFtdcUserSessionField["MacAddress"] = "string"
structDict['CSgitFtdcUserSessionField'] = CSgitFtdcUserSessionField


#查询最大报单数量
CSgitFtdcQueryMaxOrderVolumeField = {}
#经纪公司代码
CSgitFtdcQueryMaxOrderVolumeField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQueryMaxOrderVolumeField["InvestorID"] = "string"
#合约代码
CSgitFtdcQueryMaxOrderVolumeField["InstrumentID"] = "string"
#买卖方向
CSgitFtdcQueryMaxOrderVolumeField["Direction"] = "char"
#开平标志
CSgitFtdcQueryMaxOrderVolumeField["OffsetFlag"] = "char"
#投机套保标志
CSgitFtdcQueryMaxOrderVolumeField["HedgeFlag"] = "char"
#最大允许报单数量
CSgitFtdcQueryMaxOrderVolumeField["MaxVolume"] = "int"
structDict['CSgitFtdcQueryMaxOrderVolumeField'] = CSgitFtdcQueryMaxOrderVolumeField


#投资者结算结果确认信息
CSgitFtdcSettlementInfoConfirmField = {}
#经纪公司代码
CSgitFtdcSettlementInfoConfirmField["BrokerID"] = "string"
#投资者代码
CSgitFtdcSettlementInfoConfirmField["InvestorID"] = "string"
#确认日期
CSgitFtdcSettlementInfoConfirmField["ConfirmDate"] = "string"
#确认时间
CSgitFtdcSettlementInfoConfirmField["ConfirmTime"] = "string"
structDict['CSgitFtdcSettlementInfoConfirmField'] = CSgitFtdcSettlementInfoConfirmField


#出入金同步
CSgitFtdcSyncDepositField = {}
#出入金流水号
CSgitFtdcSyncDepositField["DepositSeqNo"] = "string"
#经纪公司代码
CSgitFtdcSyncDepositField["BrokerID"] = "string"
#投资者代码
CSgitFtdcSyncDepositField["InvestorID"] = "string"
#入金金额
CSgitFtdcSyncDepositField["Deposit"] = "float"
#是否强制进行
CSgitFtdcSyncDepositField["IsForce"] = "int"
structDict['CSgitFtdcSyncDepositField'] = CSgitFtdcSyncDepositField


#经纪公司同步
CSgitFtdcBrokerSyncField = {}
#经纪公司代码
CSgitFtdcBrokerSyncField["BrokerID"] = "string"
structDict['CSgitFtdcBrokerSyncField'] = CSgitFtdcBrokerSyncField


#正在同步中的投资者
CSgitFtdcSyncingInvestorField = {}
#投资者代码
CSgitFtdcSyncingInvestorField["InvestorID"] = "string"
#经纪公司代码
CSgitFtdcSyncingInvestorField["BrokerID"] = "string"
#投资者分组代码
CSgitFtdcSyncingInvestorField["InvestorGroupID"] = "string"
#投资者名称
CSgitFtdcSyncingInvestorField["InvestorName"] = "string"
#证件类型
CSgitFtdcSyncingInvestorField["IdentifiedCardType"] = "char"
#证件号码
CSgitFtdcSyncingInvestorField["IdentifiedCardNo"] = "string"
#是否活跃
CSgitFtdcSyncingInvestorField["IsActive"] = "int"
#联系电话
CSgitFtdcSyncingInvestorField["Telephone"] = "string"
#通讯地址
CSgitFtdcSyncingInvestorField["Address"] = "string"
#开户日期
CSgitFtdcSyncingInvestorField["OpenDate"] = "string"
#手机
CSgitFtdcSyncingInvestorField["Mobile"] = "string"
#手续费率模板代码
CSgitFtdcSyncingInvestorField["CommModelID"] = "string"
structDict['CSgitFtdcSyncingInvestorField'] = CSgitFtdcSyncingInvestorField


#正在同步中的交易代码
CSgitFtdcSyncingTradingCodeField = {}
#投资者代码
CSgitFtdcSyncingTradingCodeField["InvestorID"] = "string"
#经纪公司代码
CSgitFtdcSyncingTradingCodeField["BrokerID"] = "string"
#交易所代码
CSgitFtdcSyncingTradingCodeField["ExchangeID"] = "string"
#客户代码
CSgitFtdcSyncingTradingCodeField["ClientID"] = "string"
#是否活跃
CSgitFtdcSyncingTradingCodeField["IsActive"] = "int"
#交易编码类型
CSgitFtdcSyncingTradingCodeField["ClientIDType"] = "char"
structDict['CSgitFtdcSyncingTradingCodeField'] = CSgitFtdcSyncingTradingCodeField


#正在同步中的投资者分组
CSgitFtdcSyncingInvestorGroupField = {}
#经纪公司代码
CSgitFtdcSyncingInvestorGroupField["BrokerID"] = "string"
#投资者分组代码
CSgitFtdcSyncingInvestorGroupField["InvestorGroupID"] = "string"
#投资者分组名称
CSgitFtdcSyncingInvestorGroupField["InvestorGroupName"] = "string"
structDict['CSgitFtdcSyncingInvestorGroupField'] = CSgitFtdcSyncingInvestorGroupField


#正在同步中的交易账号
CSgitFtdcSyncingTradingAccountField = {}
#经纪公司代码
CSgitFtdcSyncingTradingAccountField["BrokerID"] = "string"
#投资者帐号
CSgitFtdcSyncingTradingAccountField["AccountID"] = "string"
#上次质押金额
CSgitFtdcSyncingTradingAccountField["PreMortgage"] = "float"
#上次信用额度
CSgitFtdcSyncingTradingAccountField["PreCredit"] = "float"
#上次存款额
CSgitFtdcSyncingTradingAccountField["PreDeposit"] = "float"
#上次结算准备金
CSgitFtdcSyncingTradingAccountField["PreBalance"] = "float"
#上次占用的保证金
CSgitFtdcSyncingTradingAccountField["PreMargin"] = "float"
#利息基数
CSgitFtdcSyncingTradingAccountField["InterestBase"] = "float"
#利息收入
CSgitFtdcSyncingTradingAccountField["Interest"] = "float"
#入金金额
CSgitFtdcSyncingTradingAccountField["Deposit"] = "float"
#出金金额
CSgitFtdcSyncingTradingAccountField["Withdraw"] = "float"
#冻结的保证金
CSgitFtdcSyncingTradingAccountField["FrozenMargin"] = "float"
#冻结的资金
CSgitFtdcSyncingTradingAccountField["FrozenCash"] = "float"
#冻结的手续费
CSgitFtdcSyncingTradingAccountField["FrozenCommission"] = "float"
#当前保证金总额
CSgitFtdcSyncingTradingAccountField["CurrMargin"] = "float"
#资金差额
CSgitFtdcSyncingTradingAccountField["CashIn"] = "float"
#手续费
CSgitFtdcSyncingTradingAccountField["Commission"] = "float"
#平仓盈亏
CSgitFtdcSyncingTradingAccountField["CloseProfit"] = "float"
#持仓盈亏
CSgitFtdcSyncingTradingAccountField["PositionProfit"] = "float"
#期货结算准备金
CSgitFtdcSyncingTradingAccountField["Balance"] = "float"
#可用资金
CSgitFtdcSyncingTradingAccountField["Available"] = "float"
#可取资金
CSgitFtdcSyncingTradingAccountField["WithdrawQuota"] = "float"
#基本准备金
CSgitFtdcSyncingTradingAccountField["Reserve"] = "float"
#交易日
CSgitFtdcSyncingTradingAccountField["TradingDay"] = "string"
#结算编号
CSgitFtdcSyncingTradingAccountField["SettlementID"] = "int"
#信用额度
CSgitFtdcSyncingTradingAccountField["Credit"] = "float"
#质押金额
CSgitFtdcSyncingTradingAccountField["Mortgage"] = "float"
#交易所保证金
CSgitFtdcSyncingTradingAccountField["ExchangeMargin"] = "float"
#投资者交割保证金
CSgitFtdcSyncingTradingAccountField["DeliveryMargin"] = "float"
#交易所交割保证金
CSgitFtdcSyncingTradingAccountField["ExchangeDeliveryMargin"] = "float"
structDict['CSgitFtdcSyncingTradingAccountField'] = CSgitFtdcSyncingTradingAccountField


#正在同步中的投资者持仓
CSgitFtdcSyncingInvestorPositionField = {}
#合约代码
CSgitFtdcSyncingInvestorPositionField["InstrumentID"] = "string"
#经纪公司代码
CSgitFtdcSyncingInvestorPositionField["BrokerID"] = "string"
#投资者代码
CSgitFtdcSyncingInvestorPositionField["InvestorID"] = "string"
#持仓多空方向
CSgitFtdcSyncingInvestorPositionField["PosiDirection"] = "char"
#投机套保标志
CSgitFtdcSyncingInvestorPositionField["HedgeFlag"] = "char"
#持仓日期
CSgitFtdcSyncingInvestorPositionField["PositionDate"] = "char"
#上日持仓
CSgitFtdcSyncingInvestorPositionField["YdPosition"] = "int"
#今日持仓
CSgitFtdcSyncingInvestorPositionField["Position"] = "int"
#多头冻结
CSgitFtdcSyncingInvestorPositionField["LongFrozen"] = "int"
#空头冻结
CSgitFtdcSyncingInvestorPositionField["ShortFrozen"] = "int"
#开仓冻结金额
CSgitFtdcSyncingInvestorPositionField["LongFrozenAmount"] = "float"
#开仓冻结金额
CSgitFtdcSyncingInvestorPositionField["ShortFrozenAmount"] = "float"
#开仓量
CSgitFtdcSyncingInvestorPositionField["OpenVolume"] = "int"
#平仓量
CSgitFtdcSyncingInvestorPositionField["CloseVolume"] = "int"
#开仓金额
CSgitFtdcSyncingInvestorPositionField["OpenAmount"] = "float"
#平仓金额
CSgitFtdcSyncingInvestorPositionField["CloseAmount"] = "float"
#持仓成本
CSgitFtdcSyncingInvestorPositionField["PositionCost"] = "float"
#上次占用的保证金
CSgitFtdcSyncingInvestorPositionField["PreMargin"] = "float"
#占用的保证金
CSgitFtdcSyncingInvestorPositionField["UseMargin"] = "float"
#冻结的保证金
CSgitFtdcSyncingInvestorPositionField["FrozenMargin"] = "float"
#冻结的资金
CSgitFtdcSyncingInvestorPositionField["FrozenCash"] = "float"
#冻结的手续费
CSgitFtdcSyncingInvestorPositionField["FrozenCommission"] = "float"
#资金差额
CSgitFtdcSyncingInvestorPositionField["CashIn"] = "float"
#手续费
CSgitFtdcSyncingInvestorPositionField["Commission"] = "float"
#平仓盈亏
CSgitFtdcSyncingInvestorPositionField["CloseProfit"] = "float"
#持仓盈亏
CSgitFtdcSyncingInvestorPositionField["PositionProfit"] = "float"
#上次结算价
CSgitFtdcSyncingInvestorPositionField["PreSettlementPrice"] = "float"
#本次结算价
CSgitFtdcSyncingInvestorPositionField["SettlementPrice"] = "float"
#交易日
CSgitFtdcSyncingInvestorPositionField["TradingDay"] = "string"
#结算编号
CSgitFtdcSyncingInvestorPositionField["SettlementID"] = "int"
#开仓成本
CSgitFtdcSyncingInvestorPositionField["OpenCost"] = "float"
#交易所保证金
CSgitFtdcSyncingInvestorPositionField["ExchangeMargin"] = "float"
#组合成交形成的持仓
CSgitFtdcSyncingInvestorPositionField["CombPosition"] = "int"
#组合多头冻结
CSgitFtdcSyncingInvestorPositionField["CombLongFrozen"] = "int"
#组合空头冻结
CSgitFtdcSyncingInvestorPositionField["CombShortFrozen"] = "int"
#逐日盯市平仓盈亏
CSgitFtdcSyncingInvestorPositionField["CloseProfitByDate"] = "float"
#逐笔对冲平仓盈亏
CSgitFtdcSyncingInvestorPositionField["CloseProfitByTrade"] = "float"
#今日持仓
CSgitFtdcSyncingInvestorPositionField["TodayPosition"] = "int"
#保证金率
CSgitFtdcSyncingInvestorPositionField["MarginRateByMoney"] = "float"
#保证金率(按手数)
CSgitFtdcSyncingInvestorPositionField["MarginRateByVolume"] = "float"
structDict['CSgitFtdcSyncingInvestorPositionField'] = CSgitFtdcSyncingInvestorPositionField


#正在同步中的合约保证金率
CSgitFtdcSyncingInstrumentMarginRateField = {}
#合约代码
CSgitFtdcSyncingInstrumentMarginRateField["InstrumentID"] = "string"
#投资者范围
CSgitFtdcSyncingInstrumentMarginRateField["InvestorRange"] = "char"
#经纪公司代码
CSgitFtdcSyncingInstrumentMarginRateField["BrokerID"] = "string"
#投资者代码
CSgitFtdcSyncingInstrumentMarginRateField["InvestorID"] = "string"
#投机套保标志
CSgitFtdcSyncingInstrumentMarginRateField["HedgeFlag"] = "char"
#多头保证金率
CSgitFtdcSyncingInstrumentMarginRateField["LongMarginRatioByMoney"] = "float"
#多头保证金费
CSgitFtdcSyncingInstrumentMarginRateField["LongMarginRatioByVolume"] = "float"
#空头保证金率
CSgitFtdcSyncingInstrumentMarginRateField["ShortMarginRatioByMoney"] = "float"
#空头保证金费
CSgitFtdcSyncingInstrumentMarginRateField["ShortMarginRatioByVolume"] = "float"
#是否相对交易所收取
CSgitFtdcSyncingInstrumentMarginRateField["IsRelative"] = "int"
structDict['CSgitFtdcSyncingInstrumentMarginRateField'] = CSgitFtdcSyncingInstrumentMarginRateField


#正在同步中的合约手续费率
CSgitFtdcSyncingInstrumentCommissionRateField = {}
#合约代码
CSgitFtdcSyncingInstrumentCommissionRateField["InstrumentID"] = "string"
#投资者范围
CSgitFtdcSyncingInstrumentCommissionRateField["InvestorRange"] = "char"
#经纪公司代码
CSgitFtdcSyncingInstrumentCommissionRateField["BrokerID"] = "string"
#投资者代码
CSgitFtdcSyncingInstrumentCommissionRateField["InvestorID"] = "string"
#开仓手续费率
CSgitFtdcSyncingInstrumentCommissionRateField["OpenRatioByMoney"] = "float"
#开仓手续费
CSgitFtdcSyncingInstrumentCommissionRateField["OpenRatioByVolume"] = "float"
#平仓手续费率
CSgitFtdcSyncingInstrumentCommissionRateField["CloseRatioByMoney"] = "float"
#平仓手续费
CSgitFtdcSyncingInstrumentCommissionRateField["CloseRatioByVolume"] = "float"
#平今手续费率
CSgitFtdcSyncingInstrumentCommissionRateField["CloseTodayRatioByMoney"] = "float"
#平今手续费
CSgitFtdcSyncingInstrumentCommissionRateField["CloseTodayRatioByVolume"] = "float"
structDict['CSgitFtdcSyncingInstrumentCommissionRateField'] = CSgitFtdcSyncingInstrumentCommissionRateField


#正在同步中的合约交易权限
CSgitFtdcSyncingInstrumentTradingRightField = {}
#合约代码
CSgitFtdcSyncingInstrumentTradingRightField["InstrumentID"] = "string"
#投资者范围
CSgitFtdcSyncingInstrumentTradingRightField["InvestorRange"] = "char"
#经纪公司代码
CSgitFtdcSyncingInstrumentTradingRightField["BrokerID"] = "string"
#投资者代码
CSgitFtdcSyncingInstrumentTradingRightField["InvestorID"] = "string"
#交易权限
CSgitFtdcSyncingInstrumentTradingRightField["TradingRight"] = "char"
structDict['CSgitFtdcSyncingInstrumentTradingRightField'] = CSgitFtdcSyncingInstrumentTradingRightField


#查询报单
CSgitFtdcQryOrderField = {}
#经纪公司代码
CSgitFtdcQryOrderField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryOrderField["InvestorID"] = "string"
#合约代码
CSgitFtdcQryOrderField["InstrumentID"] = "string"
#交易所代码
CSgitFtdcQryOrderField["ExchangeID"] = "string"
#报单编号
CSgitFtdcQryOrderField["OrderSysID"] = "string"
#开始时间
CSgitFtdcQryOrderField["InsertTimeStart"] = "string"
#结束时间
CSgitFtdcQryOrderField["InsertTimeEnd"] = "string"
structDict['CSgitFtdcQryOrderField'] = CSgitFtdcQryOrderField


#查询成交
CSgitFtdcQryTradeField = {}
#经纪公司代码
CSgitFtdcQryTradeField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryTradeField["InvestorID"] = "string"
#合约代码
CSgitFtdcQryTradeField["InstrumentID"] = "string"
#交易所代码
CSgitFtdcQryTradeField["ExchangeID"] = "string"
#成交编号
CSgitFtdcQryTradeField["TradeID"] = "string"
#开始时间
CSgitFtdcQryTradeField["TradeTimeStart"] = "string"
#结束时间
CSgitFtdcQryTradeField["TradeTimeEnd"] = "string"
structDict['CSgitFtdcQryTradeField'] = CSgitFtdcQryTradeField


#查询投资者持仓
CSgitFtdcQryInvestorPositionField = {}
#经纪公司代码
CSgitFtdcQryInvestorPositionField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryInvestorPositionField["InvestorID"] = "string"
#合约代码
CSgitFtdcQryInvestorPositionField["InstrumentID"] = "string"
structDict['CSgitFtdcQryInvestorPositionField'] = CSgitFtdcQryInvestorPositionField


#查询资金账户
CSgitFtdcQryTradingAccountField = {}
#经纪公司代码
CSgitFtdcQryTradingAccountField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryTradingAccountField["InvestorID"] = "string"
structDict['CSgitFtdcQryTradingAccountField'] = CSgitFtdcQryTradingAccountField


#查询投资者
CSgitFtdcQryInvestorField = {}
#经纪公司代码
CSgitFtdcQryInvestorField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryInvestorField["InvestorID"] = "string"
structDict['CSgitFtdcQryInvestorField'] = CSgitFtdcQryInvestorField


#查询交易编码
CSgitFtdcQryTradingCodeField = {}
#经纪公司代码
CSgitFtdcQryTradingCodeField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryTradingCodeField["InvestorID"] = "string"
#交易所代码
CSgitFtdcQryTradingCodeField["ExchangeID"] = "string"
#客户代码
CSgitFtdcQryTradingCodeField["ClientID"] = "string"
#交易编码类型
CSgitFtdcQryTradingCodeField["ClientIDType"] = "char"
structDict['CSgitFtdcQryTradingCodeField'] = CSgitFtdcQryTradingCodeField


#查询交易编码
CSgitFtdcQryInvestorGroupField = {}
#经纪公司代码
CSgitFtdcQryInvestorGroupField["BrokerID"] = "string"
structDict['CSgitFtdcQryInvestorGroupField'] = CSgitFtdcQryInvestorGroupField


#查询交易编码
CSgitFtdcQryInstrumentMarginRateField = {}
#经纪公司代码
CSgitFtdcQryInstrumentMarginRateField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryInstrumentMarginRateField["InvestorID"] = "string"
#合约代码
CSgitFtdcQryInstrumentMarginRateField["InstrumentID"] = "string"
#投机套保标志
CSgitFtdcQryInstrumentMarginRateField["HedgeFlag"] = "char"
structDict['CSgitFtdcQryInstrumentMarginRateField'] = CSgitFtdcQryInstrumentMarginRateField


#查询交易编码
CSgitFtdcQryInstrumentCommissionRateField = {}
#经纪公司代码
CSgitFtdcQryInstrumentCommissionRateField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryInstrumentCommissionRateField["InvestorID"] = "string"
#合约代码
CSgitFtdcQryInstrumentCommissionRateField["InstrumentID"] = "string"
structDict['CSgitFtdcQryInstrumentCommissionRateField'] = CSgitFtdcQryInstrumentCommissionRateField


#查询交易编码
CSgitFtdcQryInstrumentTradingRightField = {}
#经纪公司代码
CSgitFtdcQryInstrumentTradingRightField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryInstrumentTradingRightField["InvestorID"] = "string"
#合约代码
CSgitFtdcQryInstrumentTradingRightField["InstrumentID"] = "string"
structDict['CSgitFtdcQryInstrumentTradingRightField'] = CSgitFtdcQryInstrumentTradingRightField


#查询经纪公司
CSgitFtdcQryBrokerField = {}
#经纪公司代码
CSgitFtdcQryBrokerField["BrokerID"] = "string"
structDict['CSgitFtdcQryBrokerField'] = CSgitFtdcQryBrokerField


#查询交易员
CSgitFtdcQryTraderField = {}
#交易所代码
CSgitFtdcQryTraderField["ExchangeID"] = "string"
#会员代码
CSgitFtdcQryTraderField["ParticipantID"] = "string"
#交易所交易员代码
CSgitFtdcQryTraderField["TraderID"] = "string"
structDict['CSgitFtdcQryTraderField'] = CSgitFtdcQryTraderField


#查询经纪公司会员代码
CSgitFtdcQryPartBrokerField = {}
#交易所代码
CSgitFtdcQryPartBrokerField["ExchangeID"] = "string"
#经纪公司代码
CSgitFtdcQryPartBrokerField["BrokerID"] = "string"
#会员代码
CSgitFtdcQryPartBrokerField["ParticipantID"] = "string"
structDict['CSgitFtdcQryPartBrokerField'] = CSgitFtdcQryPartBrokerField


#查询管理用户功能权限
CSgitFtdcQrySuperUserFunctionField = {}
#用户代码
CSgitFtdcQrySuperUserFunctionField["UserID"] = "string"
structDict['CSgitFtdcQrySuperUserFunctionField'] = CSgitFtdcQrySuperUserFunctionField


#查询用户会话
CSgitFtdcQryUserSessionField = {}
#前置编号
CSgitFtdcQryUserSessionField["FrontID"] = "int"
#会话编号
CSgitFtdcQryUserSessionField["SessionID"] = "int"
#经纪公司代码
CSgitFtdcQryUserSessionField["BrokerID"] = "string"
#用户代码
CSgitFtdcQryUserSessionField["UserID"] = "string"
structDict['CSgitFtdcQryUserSessionField'] = CSgitFtdcQryUserSessionField


#查询前置状态
CSgitFtdcQryFrontStatusField = {}
#前置编号
CSgitFtdcQryFrontStatusField["FrontID"] = "int"
structDict['CSgitFtdcQryFrontStatusField'] = CSgitFtdcQryFrontStatusField


#查询交易所报单
CSgitFtdcQryExchangeOrderField = {}
#会员代码
CSgitFtdcQryExchangeOrderField["ParticipantID"] = "string"
#客户代码
CSgitFtdcQryExchangeOrderField["ClientID"] = "string"
#合约在交易所的代码
CSgitFtdcQryExchangeOrderField["ExchangeInstID"] = "string"
#交易所代码
CSgitFtdcQryExchangeOrderField["ExchangeID"] = "string"
#交易所交易员代码
CSgitFtdcQryExchangeOrderField["TraderID"] = "string"
structDict['CSgitFtdcQryExchangeOrderField'] = CSgitFtdcQryExchangeOrderField


#查询报单操作
CSgitFtdcQryOrderActionField = {}
#经纪公司代码
CSgitFtdcQryOrderActionField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryOrderActionField["InvestorID"] = "string"
#交易所代码
CSgitFtdcQryOrderActionField["ExchangeID"] = "string"
structDict['CSgitFtdcQryOrderActionField'] = CSgitFtdcQryOrderActionField


#查询交易所报单操作
CSgitFtdcQryExchangeOrderActionField = {}
#会员代码
CSgitFtdcQryExchangeOrderActionField["ParticipantID"] = "string"
#客户代码
CSgitFtdcQryExchangeOrderActionField["ClientID"] = "string"
#交易所代码
CSgitFtdcQryExchangeOrderActionField["ExchangeID"] = "string"
#交易所交易员代码
CSgitFtdcQryExchangeOrderActionField["TraderID"] = "string"
structDict['CSgitFtdcQryExchangeOrderActionField'] = CSgitFtdcQryExchangeOrderActionField


#查询管理用户
CSgitFtdcQrySuperUserField = {}
#用户代码
CSgitFtdcQrySuperUserField["UserID"] = "string"
structDict['CSgitFtdcQrySuperUserField'] = CSgitFtdcQrySuperUserField


#查询交易所
CSgitFtdcQryExchangeField = {}
#交易所代码
CSgitFtdcQryExchangeField["ExchangeID"] = "string"
structDict['CSgitFtdcQryExchangeField'] = CSgitFtdcQryExchangeField


#查询产品
CSgitFtdcQryProductField = {}
#产品代码
CSgitFtdcQryProductField["ProductID"] = "string"
structDict['CSgitFtdcQryProductField'] = CSgitFtdcQryProductField


#查询合约
CSgitFtdcQryInstrumentField = {}
#合约代码
CSgitFtdcQryInstrumentField["InstrumentID"] = "string"
#交易所代码
CSgitFtdcQryInstrumentField["ExchangeID"] = "string"
#合约在交易所的代码
CSgitFtdcQryInstrumentField["ExchangeInstID"] = "string"
#产品代码
CSgitFtdcQryInstrumentField["ProductID"] = "string"
structDict['CSgitFtdcQryInstrumentField'] = CSgitFtdcQryInstrumentField


#查询行情
CSgitFtdcQryDepthMarketDataField = {}
#合约代码
CSgitFtdcQryDepthMarketDataField["InstrumentID"] = "string"
structDict['CSgitFtdcQryDepthMarketDataField'] = CSgitFtdcQryDepthMarketDataField


#查询经纪公司用户
CSgitFtdcQryBrokerUserField = {}
#经纪公司代码
CSgitFtdcQryBrokerUserField["BrokerID"] = "string"
#用户代码
CSgitFtdcQryBrokerUserField["UserID"] = "string"
structDict['CSgitFtdcQryBrokerUserField'] = CSgitFtdcQryBrokerUserField


#查询经纪公司用户权限
CSgitFtdcQryBrokerUserFunctionField = {}
#经纪公司代码
CSgitFtdcQryBrokerUserFunctionField["BrokerID"] = "string"
#用户代码
CSgitFtdcQryBrokerUserFunctionField["UserID"] = "string"
structDict['CSgitFtdcQryBrokerUserFunctionField'] = CSgitFtdcQryBrokerUserFunctionField


#查询交易员报盘机
CSgitFtdcQryTraderOfferField = {}
#交易所代码
CSgitFtdcQryTraderOfferField["ExchangeID"] = "string"
#会员代码
CSgitFtdcQryTraderOfferField["ParticipantID"] = "string"
#交易所交易员代码
CSgitFtdcQryTraderOfferField["TraderID"] = "string"
structDict['CSgitFtdcQryTraderOfferField'] = CSgitFtdcQryTraderOfferField


#查询出入金流水
CSgitFtdcQrySyncDepositField = {}
#经纪公司代码
CSgitFtdcQrySyncDepositField["BrokerID"] = "string"
#出入金流水号
CSgitFtdcQrySyncDepositField["DepositSeqNo"] = "string"
structDict['CSgitFtdcQrySyncDepositField'] = CSgitFtdcQrySyncDepositField


#查询投资者结算结果
CSgitFtdcQrySettlementInfoField = {}
#经纪公司代码
CSgitFtdcQrySettlementInfoField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQrySettlementInfoField["InvestorID"] = "string"
#交易日
CSgitFtdcQrySettlementInfoField["TradingDay"] = "string"
structDict['CSgitFtdcQrySettlementInfoField'] = CSgitFtdcQrySettlementInfoField


#查询报单
CSgitFtdcQryHisOrderField = {}
#经纪公司代码
CSgitFtdcQryHisOrderField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryHisOrderField["InvestorID"] = "string"
#合约代码
CSgitFtdcQryHisOrderField["InstrumentID"] = "string"
#交易所代码
CSgitFtdcQryHisOrderField["ExchangeID"] = "string"
#报单编号
CSgitFtdcQryHisOrderField["OrderSysID"] = "string"
#开始时间
CSgitFtdcQryHisOrderField["InsertTimeStart"] = "string"
#结束时间
CSgitFtdcQryHisOrderField["InsertTimeEnd"] = "string"
#交易日
CSgitFtdcQryHisOrderField["TradingDay"] = "string"
#结算编号
CSgitFtdcQryHisOrderField["SettlementID"] = "int"
structDict['CSgitFtdcQryHisOrderField'] = CSgitFtdcQryHisOrderField


#市场行情
CSgitFtdcMarketDataField = {}
#交易日
CSgitFtdcMarketDataField["TradingDay"] = "string"
#合约代码
CSgitFtdcMarketDataField["InstrumentID"] = "string"
#交易所代码
CSgitFtdcMarketDataField["ExchangeID"] = "string"
#合约在交易所的代码
CSgitFtdcMarketDataField["ExchangeInstID"] = "string"
#最新价
CSgitFtdcMarketDataField["LastPrice"] = "float"
#上次结算价
CSgitFtdcMarketDataField["PreSettlementPrice"] = "float"
#昨收盘
CSgitFtdcMarketDataField["PreClosePrice"] = "float"
#昨持仓量
CSgitFtdcMarketDataField["PreOpenInterest"] = "float"
#今开盘
CSgitFtdcMarketDataField["OpenPrice"] = "float"
#最高价
CSgitFtdcMarketDataField["HighestPrice"] = "float"
#最低价
CSgitFtdcMarketDataField["LowestPrice"] = "float"
#数量
CSgitFtdcMarketDataField["Volume"] = "int"
#成交金额
CSgitFtdcMarketDataField["Turnover"] = "float"
#持仓量
CSgitFtdcMarketDataField["OpenInterest"] = "float"
#今收盘
CSgitFtdcMarketDataField["ClosePrice"] = "float"
#本次结算价
CSgitFtdcMarketDataField["SettlementPrice"] = "float"
#涨停板价
CSgitFtdcMarketDataField["UpperLimitPrice"] = "float"
#跌停板价
CSgitFtdcMarketDataField["LowerLimitPrice"] = "float"
#昨虚实度
CSgitFtdcMarketDataField["PreDelta"] = "float"
#今虚实度
CSgitFtdcMarketDataField["CurrDelta"] = "float"
#最后修改时间
CSgitFtdcMarketDataField["UpdateTime"] = "string"
#最后修改毫秒
CSgitFtdcMarketDataField["UpdateMillisec"] = "int"
structDict['CSgitFtdcMarketDataField'] = CSgitFtdcMarketDataField


#行情基础属性
CSgitFtdcMarketDataBaseField = {}
#交易日
CSgitFtdcMarketDataBaseField["TradingDay"] = "string"
#上次结算价
CSgitFtdcMarketDataBaseField["PreSettlementPrice"] = "float"
#昨收盘
CSgitFtdcMarketDataBaseField["PreClosePrice"] = "float"
#昨持仓量
CSgitFtdcMarketDataBaseField["PreOpenInterest"] = "float"
#昨虚实度
CSgitFtdcMarketDataBaseField["PreDelta"] = "float"
structDict['CSgitFtdcMarketDataBaseField'] = CSgitFtdcMarketDataBaseField


#行情静态属性
CSgitFtdcMarketDataStaticField = {}
#今开盘
CSgitFtdcMarketDataStaticField["OpenPrice"] = "float"
#最高价
CSgitFtdcMarketDataStaticField["HighestPrice"] = "float"
#最低价
CSgitFtdcMarketDataStaticField["LowestPrice"] = "float"
#今收盘
CSgitFtdcMarketDataStaticField["ClosePrice"] = "float"
#涨停板价
CSgitFtdcMarketDataStaticField["UpperLimitPrice"] = "float"
#跌停板价
CSgitFtdcMarketDataStaticField["LowerLimitPrice"] = "float"
#本次结算价
CSgitFtdcMarketDataStaticField["SettlementPrice"] = "float"
#今虚实度
CSgitFtdcMarketDataStaticField["CurrDelta"] = "float"
structDict['CSgitFtdcMarketDataStaticField'] = CSgitFtdcMarketDataStaticField


#行情最新成交属性
CSgitFtdcMarketDataLastMatchField = {}
#最新价
CSgitFtdcMarketDataLastMatchField["LastPrice"] = "float"
#数量
CSgitFtdcMarketDataLastMatchField["Volume"] = "int"
#成交金额
CSgitFtdcMarketDataLastMatchField["Turnover"] = "float"
#持仓量
CSgitFtdcMarketDataLastMatchField["OpenInterest"] = "float"
structDict['CSgitFtdcMarketDataLastMatchField'] = CSgitFtdcMarketDataLastMatchField


#行情最优价属性
CSgitFtdcMarketDataBestPriceField = {}
#申买价一
CSgitFtdcMarketDataBestPriceField["BidPrice1"] = "float"
#申买量一
CSgitFtdcMarketDataBestPriceField["BidVolume1"] = "int"
#申卖价一
CSgitFtdcMarketDataBestPriceField["AskPrice1"] = "float"
#申卖量一
CSgitFtdcMarketDataBestPriceField["AskVolume1"] = "int"
structDict['CSgitFtdcMarketDataBestPriceField'] = CSgitFtdcMarketDataBestPriceField


#行情申买二、三属性
CSgitFtdcMarketDataBid23Field = {}
#申买价二
CSgitFtdcMarketDataBid23Field["BidPrice2"] = "float"
#申买量二
CSgitFtdcMarketDataBid23Field["BidVolume2"] = "int"
#申买价三
CSgitFtdcMarketDataBid23Field["BidPrice3"] = "float"
#申买量三
CSgitFtdcMarketDataBid23Field["BidVolume3"] = "int"
structDict['CSgitFtdcMarketDataBid23Field'] = CSgitFtdcMarketDataBid23Field


#行情申卖二、三属性
CSgitFtdcMarketDataAsk23Field = {}
#申卖价二
CSgitFtdcMarketDataAsk23Field["AskPrice2"] = "float"
#申卖量二
CSgitFtdcMarketDataAsk23Field["AskVolume2"] = "int"
#申卖价三
CSgitFtdcMarketDataAsk23Field["AskPrice3"] = "float"
#申卖量三
CSgitFtdcMarketDataAsk23Field["AskVolume3"] = "int"
structDict['CSgitFtdcMarketDataAsk23Field'] = CSgitFtdcMarketDataAsk23Field


#行情申买四、五属性
CSgitFtdcMarketDataBid45Field = {}
#申买价四
CSgitFtdcMarketDataBid45Field["BidPrice4"] = "float"
#申买量四
CSgitFtdcMarketDataBid45Field["BidVolume4"] = "int"
#申买价五
CSgitFtdcMarketDataBid45Field["BidPrice5"] = "float"
#申买量五
CSgitFtdcMarketDataBid45Field["BidVolume5"] = "int"
structDict['CSgitFtdcMarketDataBid45Field'] = CSgitFtdcMarketDataBid45Field


#行情申卖四、五属性
CSgitFtdcMarketDataAsk45Field = {}
#申卖价四
CSgitFtdcMarketDataAsk45Field["AskPrice4"] = "float"
#申卖量四
CSgitFtdcMarketDataAsk45Field["AskVolume4"] = "int"
#申卖价五
CSgitFtdcMarketDataAsk45Field["AskPrice5"] = "float"
#申卖量五
CSgitFtdcMarketDataAsk45Field["AskVolume5"] = "int"
structDict['CSgitFtdcMarketDataAsk45Field'] = CSgitFtdcMarketDataAsk45Field


#行情更新时间属性
CSgitFtdcMarketDataUpdateTimeField = {}
#合约代码
CSgitFtdcMarketDataUpdateTimeField["InstrumentID"] = "string"
#最后修改时间
CSgitFtdcMarketDataUpdateTimeField["UpdateTime"] = "string"
#最后修改毫秒
CSgitFtdcMarketDataUpdateTimeField["UpdateMillisec"] = "int"
structDict['CSgitFtdcMarketDataUpdateTimeField'] = CSgitFtdcMarketDataUpdateTimeField


#行情交易所代码属性
CSgitFtdcMarketDataExchangeField = {}
#交易所代码
CSgitFtdcMarketDataExchangeField["ExchangeID"] = "float"
structDict['CSgitFtdcMarketDataExchangeField'] = CSgitFtdcMarketDataExchangeField


#指定的合约
CSgitFtdcSpecificInstrumentField = {}
#合约代码
CSgitFtdcSpecificInstrumentField["InstrumentID"] = "string"
structDict['CSgitFtdcSpecificInstrumentField'] = CSgitFtdcSpecificInstrumentField


#合约状态
CSgitFtdcInstrumentStatusField = {}
#交易所代码
CSgitFtdcInstrumentStatusField["ExchangeID"] = "string"
#合约在交易所的代码
CSgitFtdcInstrumentStatusField["ExchangeInstID"] = "string"
#结算组代码
CSgitFtdcInstrumentStatusField["SettlementGroupID"] = "string"
#合约代码
CSgitFtdcInstrumentStatusField["InstrumentID"] = "string"
#合约交易状态
CSgitFtdcInstrumentStatusField["InstrumentStatus"] = "char"
#交易阶段编号
CSgitFtdcInstrumentStatusField["TradingSegmentSN"] = "int"
#进入本状态时间
CSgitFtdcInstrumentStatusField["EnterTime"] = "string"
#进入本状态原因
CSgitFtdcInstrumentStatusField["EnterReason"] = "char"
structDict['CSgitFtdcInstrumentStatusField'] = CSgitFtdcInstrumentStatusField


#查询合约状态
CSgitFtdcQryInstrumentStatusField = {}
#交易所代码
CSgitFtdcQryInstrumentStatusField["ExchangeID"] = "string"
#合约在交易所的代码
CSgitFtdcQryInstrumentStatusField["ExchangeInstID"] = "string"
structDict['CSgitFtdcQryInstrumentStatusField'] = CSgitFtdcQryInstrumentStatusField


#投资者账户
CSgitFtdcInvestorAccountField = {}
#经纪公司代码
CSgitFtdcInvestorAccountField["BrokerID"] = "string"
#投资者代码
CSgitFtdcInvestorAccountField["InvestorID"] = "string"
#投资者帐号
CSgitFtdcInvestorAccountField["AccountID"] = "string"
structDict['CSgitFtdcInvestorAccountField'] = CSgitFtdcInvestorAccountField


#浮动盈亏算法
CSgitFtdcPositionProfitAlgorithmField = {}
#经纪公司代码
CSgitFtdcPositionProfitAlgorithmField["BrokerID"] = "string"
#投资者帐号
CSgitFtdcPositionProfitAlgorithmField["AccountID"] = "string"
#盈亏算法
CSgitFtdcPositionProfitAlgorithmField["Algorithm"] = "char"
#备注
CSgitFtdcPositionProfitAlgorithmField["Memo"] = "string"
structDict['CSgitFtdcPositionProfitAlgorithmField'] = CSgitFtdcPositionProfitAlgorithmField


#会员资金折扣
CSgitFtdcDiscountField = {}
#经纪公司代码
CSgitFtdcDiscountField["BrokerID"] = "string"
#投资者范围
CSgitFtdcDiscountField["InvestorRange"] = "char"
#投资者代码
CSgitFtdcDiscountField["InvestorID"] = "string"
#资金折扣比例
CSgitFtdcDiscountField["Discount"] = "float"
structDict['CSgitFtdcDiscountField'] = CSgitFtdcDiscountField


#查询转帐银行
CSgitFtdcQryTransferBankField = {}
#银行代码
CSgitFtdcQryTransferBankField["BankID"] = "string"
#银行分中心代码
CSgitFtdcQryTransferBankField["BankBrchID"] = "string"
structDict['CSgitFtdcQryTransferBankField'] = CSgitFtdcQryTransferBankField


#转帐银行
CSgitFtdcTransferBankField = {}
#银行代码
CSgitFtdcTransferBankField["BankID"] = "string"
#银行分中心代码
CSgitFtdcTransferBankField["BankBrchID"] = "string"
#银行名称
CSgitFtdcTransferBankField["BankName"] = "string"
#是否活跃
CSgitFtdcTransferBankField["IsActive"] = "int"
structDict['CSgitFtdcTransferBankField'] = CSgitFtdcTransferBankField


#查询投资者持仓明细
CSgitFtdcQryInvestorPositionDetailField = {}
#经纪公司代码
CSgitFtdcQryInvestorPositionDetailField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryInvestorPositionDetailField["InvestorID"] = "string"
#合约代码
CSgitFtdcQryInvestorPositionDetailField["InstrumentID"] = "string"
structDict['CSgitFtdcQryInvestorPositionDetailField'] = CSgitFtdcQryInvestorPositionDetailField


#投资者持仓明细
CSgitFtdcInvestorPositionDetailField = {}
#合约代码
CSgitFtdcInvestorPositionDetailField["InstrumentID"] = "string"
#经纪公司代码
CSgitFtdcInvestorPositionDetailField["BrokerID"] = "string"
#投资者代码
CSgitFtdcInvestorPositionDetailField["InvestorID"] = "string"
#投机套保标志
CSgitFtdcInvestorPositionDetailField["HedgeFlag"] = "char"
#买卖
CSgitFtdcInvestorPositionDetailField["Direction"] = "char"
#开仓日期
CSgitFtdcInvestorPositionDetailField["OpenDate"] = "string"
#成交编号
CSgitFtdcInvestorPositionDetailField["TradeID"] = "string"
#数量
CSgitFtdcInvestorPositionDetailField["Volume"] = "int"
#开仓价
CSgitFtdcInvestorPositionDetailField["OpenPrice"] = "float"
#交易日
CSgitFtdcInvestorPositionDetailField["TradingDay"] = "string"
#结算编号
CSgitFtdcInvestorPositionDetailField["SettlementID"] = "int"
#成交类型
CSgitFtdcInvestorPositionDetailField["TradeType"] = "char"
#组合合约代码
CSgitFtdcInvestorPositionDetailField["CombInstrumentID"] = "string"
#交易所代码
CSgitFtdcInvestorPositionDetailField["ExchangeID"] = "string"
#逐日盯市平仓盈亏
CSgitFtdcInvestorPositionDetailField["CloseProfitByDate"] = "float"
#逐笔对冲平仓盈亏
CSgitFtdcInvestorPositionDetailField["CloseProfitByTrade"] = "float"
#逐日盯市持仓盈亏
CSgitFtdcInvestorPositionDetailField["PositionProfitByDate"] = "float"
#逐笔对冲持仓盈亏
CSgitFtdcInvestorPositionDetailField["PositionProfitByTrade"] = "float"
#投资者保证金
CSgitFtdcInvestorPositionDetailField["Margin"] = "float"
#交易所保证金
CSgitFtdcInvestorPositionDetailField["ExchMargin"] = "float"
#保证金率
CSgitFtdcInvestorPositionDetailField["MarginRateByMoney"] = "float"
#保证金率(按手数)
CSgitFtdcInvestorPositionDetailField["MarginRateByVolume"] = "float"
#昨结算价
CSgitFtdcInvestorPositionDetailField["LastSettlementPrice"] = "float"
#结算价
CSgitFtdcInvestorPositionDetailField["SettlementPrice"] = "float"
#平仓量
CSgitFtdcInvestorPositionDetailField["CloseVolume"] = "int"
#平仓金额
CSgitFtdcInvestorPositionDetailField["CloseAmount"] = "float"
structDict['CSgitFtdcInvestorPositionDetailField'] = CSgitFtdcInvestorPositionDetailField


#资金账户口令域
CSgitFtdcTradingAccountPasswordField = {}
#经纪公司代码
CSgitFtdcTradingAccountPasswordField["BrokerID"] = "string"
#投资者帐号
CSgitFtdcTradingAccountPasswordField["AccountID"] = "string"
#密码
CSgitFtdcTradingAccountPasswordField["Password"] = "string"
structDict['CSgitFtdcTradingAccountPasswordField'] = CSgitFtdcTradingAccountPasswordField


#交易所行情报盘机
CSgitFtdcMDTraderOfferField = {}
#交易所代码
CSgitFtdcMDTraderOfferField["ExchangeID"] = "string"
#交易所交易员代码
CSgitFtdcMDTraderOfferField["TraderID"] = "string"
#会员代码
CSgitFtdcMDTraderOfferField["ParticipantID"] = "string"
#密码
CSgitFtdcMDTraderOfferField["Password"] = "string"
#安装编号
CSgitFtdcMDTraderOfferField["InstallID"] = "int"
#本地报单编号
CSgitFtdcMDTraderOfferField["OrderLocalID"] = "string"
#交易所交易员连接状态
CSgitFtdcMDTraderOfferField["TraderConnectStatus"] = "char"
#发出连接请求的日期
CSgitFtdcMDTraderOfferField["ConnectRequestDate"] = "string"
#发出连接请求的时间
CSgitFtdcMDTraderOfferField["ConnectRequestTime"] = "string"
#上次报告日期
CSgitFtdcMDTraderOfferField["LastReportDate"] = "string"
#上次报告时间
CSgitFtdcMDTraderOfferField["LastReportTime"] = "string"
#完成连接日期
CSgitFtdcMDTraderOfferField["ConnectDate"] = "string"
#完成连接时间
CSgitFtdcMDTraderOfferField["ConnectTime"] = "string"
#启动日期
CSgitFtdcMDTraderOfferField["StartDate"] = "string"
#启动时间
CSgitFtdcMDTraderOfferField["StartTime"] = "string"
#交易日
CSgitFtdcMDTraderOfferField["TradingDay"] = "string"
#经纪公司代码
CSgitFtdcMDTraderOfferField["BrokerID"] = "string"
#本席位最大成交编号
CSgitFtdcMDTraderOfferField["MaxTradeID"] = "string"
#本席位最大报单备拷
CSgitFtdcMDTraderOfferField["MaxOrderMessageReference"] = "string"
structDict['CSgitFtdcMDTraderOfferField'] = CSgitFtdcMDTraderOfferField


#查询行情报盘机
CSgitFtdcQryMDTraderOfferField = {}
#交易所代码
CSgitFtdcQryMDTraderOfferField["ExchangeID"] = "string"
#会员代码
CSgitFtdcQryMDTraderOfferField["ParticipantID"] = "string"
#交易所交易员代码
CSgitFtdcQryMDTraderOfferField["TraderID"] = "string"
structDict['CSgitFtdcQryMDTraderOfferField'] = CSgitFtdcQryMDTraderOfferField


#查询客户通知
CSgitFtdcQryNoticeField = {}
#经纪公司代码
CSgitFtdcQryNoticeField["BrokerID"] = "string"
structDict['CSgitFtdcQryNoticeField'] = CSgitFtdcQryNoticeField


#客户通知
CSgitFtdcNoticeField = {}
#经纪公司代码
CSgitFtdcNoticeField["BrokerID"] = "string"
#消息正文
CSgitFtdcNoticeField["Content"] = "string"
#经纪公司通知内容序列号
CSgitFtdcNoticeField["SequenceLabel"] = "string"
structDict['CSgitFtdcNoticeField'] = CSgitFtdcNoticeField


#用户权限
CSgitFtdcUserRightField = {}
#经纪公司代码
CSgitFtdcUserRightField["BrokerID"] = "string"
#用户代码
CSgitFtdcUserRightField["UserID"] = "string"
#客户权限类型
CSgitFtdcUserRightField["UserRightType"] = "char"
#是否禁止
CSgitFtdcUserRightField["IsForbidden"] = "int"
structDict['CSgitFtdcUserRightField'] = CSgitFtdcUserRightField


#查询结算信息确认域
CSgitFtdcQrySettlementInfoConfirmField = {}
#经纪公司代码
CSgitFtdcQrySettlementInfoConfirmField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQrySettlementInfoConfirmField["InvestorID"] = "string"
structDict['CSgitFtdcQrySettlementInfoConfirmField'] = CSgitFtdcQrySettlementInfoConfirmField


#装载结算信息
CSgitFtdcLoadSettlementInfoField = {}
#经纪公司代码
CSgitFtdcLoadSettlementInfoField["BrokerID"] = "string"
structDict['CSgitFtdcLoadSettlementInfoField'] = CSgitFtdcLoadSettlementInfoField


#经纪公司可提资金算法表
CSgitFtdcBrokerWithdrawAlgorithmField = {}
#经纪公司代码
CSgitFtdcBrokerWithdrawAlgorithmField["BrokerID"] = "string"
#可提资金算法
CSgitFtdcBrokerWithdrawAlgorithmField["WithdrawAlgorithm"] = "char"
#资金使用率
CSgitFtdcBrokerWithdrawAlgorithmField["UsingRatio"] = "float"
#可提是否包含平仓盈利
CSgitFtdcBrokerWithdrawAlgorithmField["IncludeCloseProfit"] = "char"
#本日无仓且无成交客户是否受可提比例限制
CSgitFtdcBrokerWithdrawAlgorithmField["AllWithoutTrade"] = "char"
#可用是否包含平仓盈利
CSgitFtdcBrokerWithdrawAlgorithmField["AvailIncludeCloseProfit"] = "char"
#是否启用用户事件
CSgitFtdcBrokerWithdrawAlgorithmField["IsBrokerUserEvent"] = "int"
structDict['CSgitFtdcBrokerWithdrawAlgorithmField'] = CSgitFtdcBrokerWithdrawAlgorithmField


#资金账户口令变更域
CSgitFtdcTradingAccountPasswordUpdateV1Field = {}
#经纪公司代码
CSgitFtdcTradingAccountPasswordUpdateV1Field["BrokerID"] = "string"
#投资者代码
CSgitFtdcTradingAccountPasswordUpdateV1Field["InvestorID"] = "string"
#原来的口令
CSgitFtdcTradingAccountPasswordUpdateV1Field["OldPassword"] = "string"
#新的口令
CSgitFtdcTradingAccountPasswordUpdateV1Field["NewPassword"] = "string"
structDict['CSgitFtdcTradingAccountPasswordUpdateV1Field'] = CSgitFtdcTradingAccountPasswordUpdateV1Field


#资金账户口令变更域
CSgitFtdcTradingAccountPasswordUpdateField = {}
#经纪公司代码
CSgitFtdcTradingAccountPasswordUpdateField["BrokerID"] = "string"
#投资者帐号
CSgitFtdcTradingAccountPasswordUpdateField["AccountID"] = "string"
#原来的口令
CSgitFtdcTradingAccountPasswordUpdateField["OldPassword"] = "string"
#新的口令
CSgitFtdcTradingAccountPasswordUpdateField["NewPassword"] = "string"
structDict['CSgitFtdcTradingAccountPasswordUpdateField'] = CSgitFtdcTradingAccountPasswordUpdateField


#查询组合合约分腿
CSgitFtdcQryCombinationLegField = {}
#组合合约代码
CSgitFtdcQryCombinationLegField["CombInstrumentID"] = "string"
#单腿编号
CSgitFtdcQryCombinationLegField["LegID"] = "int"
#单腿合约代码
CSgitFtdcQryCombinationLegField["LegInstrumentID"] = "string"
structDict['CSgitFtdcQryCombinationLegField'] = CSgitFtdcQryCombinationLegField


#查询组合合约分腿
CSgitFtdcQrySyncStatusField = {}
#交易日
CSgitFtdcQrySyncStatusField["TradingDay"] = "string"
structDict['CSgitFtdcQrySyncStatusField'] = CSgitFtdcQrySyncStatusField


#组合交易合约的单腿
CSgitFtdcCombinationLegField = {}
#组合合约代码
CSgitFtdcCombinationLegField["CombInstrumentID"] = "string"
#单腿编号
CSgitFtdcCombinationLegField["LegID"] = "int"
#单腿合约代码
CSgitFtdcCombinationLegField["LegInstrumentID"] = "string"
#买卖方向
CSgitFtdcCombinationLegField["Direction"] = "char"
#单腿乘数
CSgitFtdcCombinationLegField["LegMultiple"] = "int"
#派生层数
CSgitFtdcCombinationLegField["ImplyLevel"] = "int"
structDict['CSgitFtdcCombinationLegField'] = CSgitFtdcCombinationLegField


#数据同步状态
CSgitFtdcSyncStatusField = {}
#交易日
CSgitFtdcSyncStatusField["TradingDay"] = "string"
#数据同步状态
CSgitFtdcSyncStatusField["DataSyncStatus"] = "char"
structDict['CSgitFtdcSyncStatusField'] = CSgitFtdcSyncStatusField


#查询联系人
CSgitFtdcQryLinkManField = {}
#经纪公司代码
CSgitFtdcQryLinkManField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryLinkManField["InvestorID"] = "string"
structDict['CSgitFtdcQryLinkManField'] = CSgitFtdcQryLinkManField


#联系人
CSgitFtdcLinkManField = {}
#经纪公司代码
CSgitFtdcLinkManField["BrokerID"] = "string"
#投资者代码
CSgitFtdcLinkManField["InvestorID"] = "string"
#联系人类型
CSgitFtdcLinkManField["PersonType"] = "char"
#证件类型
CSgitFtdcLinkManField["IdentifiedCardType"] = "char"
#证件号码
CSgitFtdcLinkManField["IdentifiedCardNo"] = "string"
#名称
CSgitFtdcLinkManField["PersonName"] = "string"
#联系电话
CSgitFtdcLinkManField["Telephone"] = "string"
#通讯地址
CSgitFtdcLinkManField["Address"] = "string"
#邮政编码
CSgitFtdcLinkManField["ZipCode"] = "string"
#优先级
CSgitFtdcLinkManField["Priority"] = "int"
structDict['CSgitFtdcLinkManField'] = CSgitFtdcLinkManField


#查询经纪公司用户事件
CSgitFtdcQryBrokerUserEventField = {}
#经纪公司代码
CSgitFtdcQryBrokerUserEventField["BrokerID"] = "string"
#用户代码
CSgitFtdcQryBrokerUserEventField["UserID"] = "string"
#用户事件类型
CSgitFtdcQryBrokerUserEventField["UserEventType"] = "char"
structDict['CSgitFtdcQryBrokerUserEventField'] = CSgitFtdcQryBrokerUserEventField


#查询经纪公司用户事件
CSgitFtdcBrokerUserEventField = {}
#经纪公司代码
CSgitFtdcBrokerUserEventField["BrokerID"] = "string"
#用户代码
CSgitFtdcBrokerUserEventField["UserID"] = "string"
#用户事件类型
CSgitFtdcBrokerUserEventField["UserEventType"] = "char"
#用户事件序号
CSgitFtdcBrokerUserEventField["EventSequenceNo"] = "int"
#事件发生日期
CSgitFtdcBrokerUserEventField["EventDate"] = "string"
#事件发生时间
CSgitFtdcBrokerUserEventField["EventTime"] = "string"
#用户事件信息
CSgitFtdcBrokerUserEventField["UserEventInfo"] = "string"
#投资者代码
CSgitFtdcBrokerUserEventField["InvestorID"] = "string"
#合约代码
CSgitFtdcBrokerUserEventField["InstrumentID"] = "string"
structDict['CSgitFtdcBrokerUserEventField'] = CSgitFtdcBrokerUserEventField


#查询签约银行请求
CSgitFtdcQryContractBankField = {}
#经纪公司代码
CSgitFtdcQryContractBankField["BrokerID"] = "string"
#银行代码
CSgitFtdcQryContractBankField["BankID"] = "string"
#银行分中心代码
CSgitFtdcQryContractBankField["BankBrchID"] = "string"
structDict['CSgitFtdcQryContractBankField'] = CSgitFtdcQryContractBankField


#查询签约银行响应
CSgitFtdcContractBankField = {}
#经纪公司代码
CSgitFtdcContractBankField["BrokerID"] = "string"
#银行代码
CSgitFtdcContractBankField["BankID"] = "string"
#银行分中心代码
CSgitFtdcContractBankField["BankBrchID"] = "string"
#银行名称
CSgitFtdcContractBankField["BankName"] = "string"
structDict['CSgitFtdcContractBankField'] = CSgitFtdcContractBankField


#投资者组合持仓明细
CSgitFtdcInvestorPositionCombineDetailField = {}
#交易日
CSgitFtdcInvestorPositionCombineDetailField["TradingDay"] = "string"
#开仓日期
CSgitFtdcInvestorPositionCombineDetailField["OpenDate"] = "string"
#交易所代码
CSgitFtdcInvestorPositionCombineDetailField["ExchangeID"] = "string"
#结算编号
CSgitFtdcInvestorPositionCombineDetailField["SettlementID"] = "int"
#经纪公司代码
CSgitFtdcInvestorPositionCombineDetailField["BrokerID"] = "string"
#投资者代码
CSgitFtdcInvestorPositionCombineDetailField["InvestorID"] = "string"
#组合编号
CSgitFtdcInvestorPositionCombineDetailField["ComTradeID"] = "string"
#撮合编号
CSgitFtdcInvestorPositionCombineDetailField["TradeID"] = "string"
#合约代码
CSgitFtdcInvestorPositionCombineDetailField["InstrumentID"] = "string"
#投机套保标志
CSgitFtdcInvestorPositionCombineDetailField["HedgeFlag"] = "char"
#买卖
CSgitFtdcInvestorPositionCombineDetailField["Direction"] = "char"
#持仓量
CSgitFtdcInvestorPositionCombineDetailField["TotalAmt"] = "int"
#投资者保证金
CSgitFtdcInvestorPositionCombineDetailField["Margin"] = "float"
#交易所保证金
CSgitFtdcInvestorPositionCombineDetailField["ExchMargin"] = "float"
#保证金率
CSgitFtdcInvestorPositionCombineDetailField["MarginRateByMoney"] = "float"
#保证金率(按手数)
CSgitFtdcInvestorPositionCombineDetailField["MarginRateByVolume"] = "float"
#单腿编号
CSgitFtdcInvestorPositionCombineDetailField["LegID"] = "int"
#单腿乘数
CSgitFtdcInvestorPositionCombineDetailField["LegMultiple"] = "int"
#组合持仓合约编码
CSgitFtdcInvestorPositionCombineDetailField["CombInstrumentID"] = "string"
structDict['CSgitFtdcInvestorPositionCombineDetailField'] = CSgitFtdcInvestorPositionCombineDetailField


#预埋单
CSgitFtdcParkedOrderField = {}
#经纪公司代码
CSgitFtdcParkedOrderField["BrokerID"] = "string"
#投资者代码
CSgitFtdcParkedOrderField["InvestorID"] = "string"
#合约代码
CSgitFtdcParkedOrderField["InstrumentID"] = "string"
#报单引用
CSgitFtdcParkedOrderField["OrderRef"] = "string"
#用户代码
CSgitFtdcParkedOrderField["UserID"] = "string"
#报单价格条件
CSgitFtdcParkedOrderField["OrderPriceType"] = "char"
#买卖方向
CSgitFtdcParkedOrderField["Direction"] = "char"
#组合开平标志
CSgitFtdcParkedOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CSgitFtdcParkedOrderField["CombHedgeFlag"] = "string"
#价格
CSgitFtdcParkedOrderField["LimitPrice"] = "float"
#数量
CSgitFtdcParkedOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CSgitFtdcParkedOrderField["TimeCondition"] = "char"
#GTD日期
CSgitFtdcParkedOrderField["GTDDate"] = "string"
#成交量类型
CSgitFtdcParkedOrderField["VolumeCondition"] = "char"
#最小成交量
CSgitFtdcParkedOrderField["MinVolume"] = "int"
#触发条件
CSgitFtdcParkedOrderField["ContingentCondition"] = "char"
#止损价
CSgitFtdcParkedOrderField["StopPrice"] = "float"
#强平原因
CSgitFtdcParkedOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CSgitFtdcParkedOrderField["IsAutoSuspend"] = "int"
#业务单元
CSgitFtdcParkedOrderField["BusinessUnit"] = "string"
#请求编号
CSgitFtdcParkedOrderField["RequestID"] = "int"
#用户强评标志
CSgitFtdcParkedOrderField["UserForceClose"] = "int"
#交易所代码
CSgitFtdcParkedOrderField["ExchangeID"] = "string"
#预埋报单编号
CSgitFtdcParkedOrderField["ParkedOrderID"] = "string"
#用户类型
CSgitFtdcParkedOrderField["UserType"] = "char"
#预埋单状态
CSgitFtdcParkedOrderField["Status"] = "char"
#错误代码
CSgitFtdcParkedOrderField["ErrorID"] = "int"
#错误信息
CSgitFtdcParkedOrderField["ErrorMsg"] = "string"
structDict['CSgitFtdcParkedOrderField'] = CSgitFtdcParkedOrderField


#输入预埋单操作
CSgitFtdcParkedOrderActionField = {}
#经纪公司代码
CSgitFtdcParkedOrderActionField["BrokerID"] = "string"
#投资者代码
CSgitFtdcParkedOrderActionField["InvestorID"] = "string"
#报单操作引用
CSgitFtdcParkedOrderActionField["OrderActionRef"] = "int"
#报单引用
CSgitFtdcParkedOrderActionField["OrderRef"] = "string"
#请求编号
CSgitFtdcParkedOrderActionField["RequestID"] = "int"
#前置编号
CSgitFtdcParkedOrderActionField["FrontID"] = "int"
#会话编号
CSgitFtdcParkedOrderActionField["SessionID"] = "int"
#交易所代码
CSgitFtdcParkedOrderActionField["ExchangeID"] = "string"
#报单编号
CSgitFtdcParkedOrderActionField["OrderSysID"] = "string"
#操作标志
CSgitFtdcParkedOrderActionField["ActionFlag"] = "char"
#价格
CSgitFtdcParkedOrderActionField["LimitPrice"] = "float"
#数量变化
CSgitFtdcParkedOrderActionField["VolumeChange"] = "int"
#用户代码
CSgitFtdcParkedOrderActionField["UserID"] = "string"
#合约代码
CSgitFtdcParkedOrderActionField["InstrumentID"] = "string"
#预埋撤单单编号
CSgitFtdcParkedOrderActionField["ParkedOrderActionID"] = "string"
#用户类型
CSgitFtdcParkedOrderActionField["UserType"] = "char"
#预埋撤单状态
CSgitFtdcParkedOrderActionField["Status"] = "char"
#错误代码
CSgitFtdcParkedOrderActionField["ErrorID"] = "int"
#错误信息
CSgitFtdcParkedOrderActionField["ErrorMsg"] = "string"
structDict['CSgitFtdcParkedOrderActionField'] = CSgitFtdcParkedOrderActionField


#查询预埋单
CSgitFtdcQryParkedOrderField = {}
#经纪公司代码
CSgitFtdcQryParkedOrderField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryParkedOrderField["InvestorID"] = "string"
#合约代码
CSgitFtdcQryParkedOrderField["InstrumentID"] = "string"
#交易所代码
CSgitFtdcQryParkedOrderField["ExchangeID"] = "string"
structDict['CSgitFtdcQryParkedOrderField'] = CSgitFtdcQryParkedOrderField


#查询预埋撤单
CSgitFtdcQryParkedOrderActionField = {}
#经纪公司代码
CSgitFtdcQryParkedOrderActionField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryParkedOrderActionField["InvestorID"] = "string"
#合约代码
CSgitFtdcQryParkedOrderActionField["InstrumentID"] = "string"
#交易所代码
CSgitFtdcQryParkedOrderActionField["ExchangeID"] = "string"
structDict['CSgitFtdcQryParkedOrderActionField'] = CSgitFtdcQryParkedOrderActionField


#删除预埋单
CSgitFtdcRemoveParkedOrderField = {}
#经纪公司代码
CSgitFtdcRemoveParkedOrderField["BrokerID"] = "string"
#投资者代码
CSgitFtdcRemoveParkedOrderField["InvestorID"] = "string"
#预埋报单编号
CSgitFtdcRemoveParkedOrderField["ParkedOrderID"] = "string"
structDict['CSgitFtdcRemoveParkedOrderField'] = CSgitFtdcRemoveParkedOrderField


#删除预埋撤单
CSgitFtdcRemoveParkedOrderActionField = {}
#经纪公司代码
CSgitFtdcRemoveParkedOrderActionField["BrokerID"] = "string"
#投资者代码
CSgitFtdcRemoveParkedOrderActionField["InvestorID"] = "string"
#预埋撤单编号
CSgitFtdcRemoveParkedOrderActionField["ParkedOrderActionID"] = "string"
structDict['CSgitFtdcRemoveParkedOrderActionField'] = CSgitFtdcRemoveParkedOrderActionField


#经纪公司可提资金算法表
CSgitFtdcInvestorWithdrawAlgorithmField = {}
#经纪公司代码
CSgitFtdcInvestorWithdrawAlgorithmField["BrokerID"] = "string"
#投资者范围
CSgitFtdcInvestorWithdrawAlgorithmField["InvestorRange"] = "char"
#投资者代码
CSgitFtdcInvestorWithdrawAlgorithmField["InvestorID"] = "string"
#可提资金比例
CSgitFtdcInvestorWithdrawAlgorithmField["UsingRatio"] = "float"
structDict['CSgitFtdcInvestorWithdrawAlgorithmField'] = CSgitFtdcInvestorWithdrawAlgorithmField


#查询组合持仓明细
CSgitFtdcQryInvestorPositionCombineDetailField = {}
#经纪公司代码
CSgitFtdcQryInvestorPositionCombineDetailField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryInvestorPositionCombineDetailField["InvestorID"] = "string"
#组合持仓合约编码
CSgitFtdcQryInvestorPositionCombineDetailField["CombInstrumentID"] = "string"
structDict['CSgitFtdcQryInvestorPositionCombineDetailField'] = CSgitFtdcQryInvestorPositionCombineDetailField


#成交均价
CSgitFtdcMarketDataAveragePriceField = {}
#当日均价
CSgitFtdcMarketDataAveragePriceField["AveragePrice"] = "float"
structDict['CSgitFtdcMarketDataAveragePriceField'] = CSgitFtdcMarketDataAveragePriceField


#校验投资者密码
CSgitFtdcVerifyInvestorPasswordField = {}
#经纪公司代码
CSgitFtdcVerifyInvestorPasswordField["BrokerID"] = "string"
#投资者代码
CSgitFtdcVerifyInvestorPasswordField["InvestorID"] = "string"
#密码
CSgitFtdcVerifyInvestorPasswordField["Password"] = "string"
structDict['CSgitFtdcVerifyInvestorPasswordField'] = CSgitFtdcVerifyInvestorPasswordField


#用户IP
CSgitFtdcUserIPField = {}
#经纪公司代码
CSgitFtdcUserIPField["BrokerID"] = "string"
#用户代码
CSgitFtdcUserIPField["UserID"] = "string"
#IP地址
CSgitFtdcUserIPField["IPAddress"] = "string"
#IP地址掩码
CSgitFtdcUserIPField["IPMask"] = "string"
#Mac地址
CSgitFtdcUserIPField["MacAddress"] = "string"
structDict['CSgitFtdcUserIPField'] = CSgitFtdcUserIPField


#用户事件通知信息
CSgitFtdcTradingNoticeInfoField = {}
#经纪公司代码
CSgitFtdcTradingNoticeInfoField["BrokerID"] = "string"
#投资者代码
CSgitFtdcTradingNoticeInfoField["InvestorID"] = "string"
#发送时间
CSgitFtdcTradingNoticeInfoField["SendTime"] = "string"
#消息正文
CSgitFtdcTradingNoticeInfoField["FieldContent"] = "string"
#序列系列号
CSgitFtdcTradingNoticeInfoField["SequenceSeries"] = "short"
#序列号
CSgitFtdcTradingNoticeInfoField["SequenceNo"] = "int"
structDict['CSgitFtdcTradingNoticeInfoField'] = CSgitFtdcTradingNoticeInfoField


#用户事件通知
CSgitFtdcTradingNoticeField = {}
#经纪公司代码
CSgitFtdcTradingNoticeField["BrokerID"] = "string"
#投资者范围
CSgitFtdcTradingNoticeField["InvestorRange"] = "char"
#投资者代码
CSgitFtdcTradingNoticeField["InvestorID"] = "string"
#序列系列号
CSgitFtdcTradingNoticeField["SequenceSeries"] = "short"
#用户代码
CSgitFtdcTradingNoticeField["UserID"] = "string"
#发送时间
CSgitFtdcTradingNoticeField["SendTime"] = "string"
#序列号
CSgitFtdcTradingNoticeField["SequenceNo"] = "int"
#消息正文
CSgitFtdcTradingNoticeField["FieldContent"] = "string"
structDict['CSgitFtdcTradingNoticeField'] = CSgitFtdcTradingNoticeField


#查询交易事件通知
CSgitFtdcQryTradingNoticeField = {}
#经纪公司代码
CSgitFtdcQryTradingNoticeField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryTradingNoticeField["InvestorID"] = "string"
structDict['CSgitFtdcQryTradingNoticeField'] = CSgitFtdcQryTradingNoticeField


#查询错误报单
CSgitFtdcQryErrOrderField = {}
#经纪公司代码
CSgitFtdcQryErrOrderField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryErrOrderField["InvestorID"] = "string"
structDict['CSgitFtdcQryErrOrderField'] = CSgitFtdcQryErrOrderField


#错误报单
CSgitFtdcErrOrderField = {}
#经纪公司代码
CSgitFtdcErrOrderField["BrokerID"] = "string"
#投资者代码
CSgitFtdcErrOrderField["InvestorID"] = "string"
#合约代码
CSgitFtdcErrOrderField["InstrumentID"] = "string"
#报单引用
CSgitFtdcErrOrderField["OrderRef"] = "string"
#用户代码
CSgitFtdcErrOrderField["UserID"] = "string"
#报单价格条件
CSgitFtdcErrOrderField["OrderPriceType"] = "char"
#买卖方向
CSgitFtdcErrOrderField["Direction"] = "char"
#组合开平标志
CSgitFtdcErrOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CSgitFtdcErrOrderField["CombHedgeFlag"] = "string"
#价格
CSgitFtdcErrOrderField["LimitPrice"] = "float"
#数量
CSgitFtdcErrOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CSgitFtdcErrOrderField["TimeCondition"] = "char"
#GTD日期
CSgitFtdcErrOrderField["GTDDate"] = "string"
#成交量类型
CSgitFtdcErrOrderField["VolumeCondition"] = "char"
#最小成交量
CSgitFtdcErrOrderField["MinVolume"] = "int"
#触发条件
CSgitFtdcErrOrderField["ContingentCondition"] = "char"
#止损价
CSgitFtdcErrOrderField["StopPrice"] = "float"
#强平原因
CSgitFtdcErrOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CSgitFtdcErrOrderField["IsAutoSuspend"] = "int"
#业务单元
CSgitFtdcErrOrderField["BusinessUnit"] = "string"
#请求编号
CSgitFtdcErrOrderField["RequestID"] = "int"
#用户强评标志
CSgitFtdcErrOrderField["UserForceClose"] = "int"
#错误代码
CSgitFtdcErrOrderField["ErrorID"] = "int"
#错误信息
CSgitFtdcErrOrderField["ErrorMsg"] = "string"
structDict['CSgitFtdcErrOrderField'] = CSgitFtdcErrOrderField


#查询错误报单操作
CSgitFtdcErrorConditionalOrderField = {}
#经纪公司代码
CSgitFtdcErrorConditionalOrderField["BrokerID"] = "string"
#投资者代码
CSgitFtdcErrorConditionalOrderField["InvestorID"] = "string"
#合约代码
CSgitFtdcErrorConditionalOrderField["InstrumentID"] = "string"
#报单引用
CSgitFtdcErrorConditionalOrderField["OrderRef"] = "string"
#用户代码
CSgitFtdcErrorConditionalOrderField["UserID"] = "string"
#报单价格条件
CSgitFtdcErrorConditionalOrderField["OrderPriceType"] = "char"
#买卖方向
CSgitFtdcErrorConditionalOrderField["Direction"] = "char"
#组合开平标志
CSgitFtdcErrorConditionalOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CSgitFtdcErrorConditionalOrderField["CombHedgeFlag"] = "string"
#价格
CSgitFtdcErrorConditionalOrderField["LimitPrice"] = "float"
#数量
CSgitFtdcErrorConditionalOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CSgitFtdcErrorConditionalOrderField["TimeCondition"] = "char"
#GTD日期
CSgitFtdcErrorConditionalOrderField["GTDDate"] = "string"
#成交量类型
CSgitFtdcErrorConditionalOrderField["VolumeCondition"] = "char"
#最小成交量
CSgitFtdcErrorConditionalOrderField["MinVolume"] = "int"
#触发条件
CSgitFtdcErrorConditionalOrderField["ContingentCondition"] = "char"
#止损价
CSgitFtdcErrorConditionalOrderField["StopPrice"] = "float"
#强平原因
CSgitFtdcErrorConditionalOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CSgitFtdcErrorConditionalOrderField["IsAutoSuspend"] = "int"
#业务单元
CSgitFtdcErrorConditionalOrderField["BusinessUnit"] = "string"
#请求编号
CSgitFtdcErrorConditionalOrderField["RequestID"] = "int"
#本地报单编号
CSgitFtdcErrorConditionalOrderField["OrderLocalID"] = "string"
#交易所代码
CSgitFtdcErrorConditionalOrderField["ExchangeID"] = "string"
#会员代码
CSgitFtdcErrorConditionalOrderField["ParticipantID"] = "string"
#客户代码
CSgitFtdcErrorConditionalOrderField["ClientID"] = "string"
#合约在交易所的代码
CSgitFtdcErrorConditionalOrderField["ExchangeInstID"] = "string"
#交易所交易员代码
CSgitFtdcErrorConditionalOrderField["TraderID"] = "string"
#安装编号
CSgitFtdcErrorConditionalOrderField["InstallID"] = "int"
#报单提交状态
CSgitFtdcErrorConditionalOrderField["OrderSubmitStatus"] = "char"
#报单提示序号
CSgitFtdcErrorConditionalOrderField["NotifySequence"] = "int"
#交易日
CSgitFtdcErrorConditionalOrderField["TradingDay"] = "string"
#结算编号
CSgitFtdcErrorConditionalOrderField["SettlementID"] = "int"
#报单编号
CSgitFtdcErrorConditionalOrderField["OrderSysID"] = "string"
#报单来源
CSgitFtdcErrorConditionalOrderField["OrderSource"] = "char"
#报单状态
CSgitFtdcErrorConditionalOrderField["OrderStatus"] = "char"
#报单类型
CSgitFtdcErrorConditionalOrderField["OrderType"] = "char"
#今成交数量
CSgitFtdcErrorConditionalOrderField["VolumeTraded"] = "int"
#剩余数量
CSgitFtdcErrorConditionalOrderField["VolumeTotal"] = "int"
#报单日期
CSgitFtdcErrorConditionalOrderField["InsertDate"] = "string"
#委托时间
CSgitFtdcErrorConditionalOrderField["InsertTime"] = "string"
#激活时间
CSgitFtdcErrorConditionalOrderField["ActiveTime"] = "string"
#挂起时间
CSgitFtdcErrorConditionalOrderField["SuspendTime"] = "string"
#最后修改时间
CSgitFtdcErrorConditionalOrderField["UpdateTime"] = "string"
#撤销时间
CSgitFtdcErrorConditionalOrderField["CancelTime"] = "string"
#最后修改交易所交易员代码
CSgitFtdcErrorConditionalOrderField["ActiveTraderID"] = "string"
#结算会员编号
CSgitFtdcErrorConditionalOrderField["ClearingPartID"] = "string"
#序号
CSgitFtdcErrorConditionalOrderField["SequenceNo"] = "int"
#前置编号
CSgitFtdcErrorConditionalOrderField["FrontID"] = "int"
#会话编号
CSgitFtdcErrorConditionalOrderField["SessionID"] = "int"
#用户端产品信息
CSgitFtdcErrorConditionalOrderField["UserProductInfo"] = "string"
#状态信息
CSgitFtdcErrorConditionalOrderField["StatusMsg"] = "string"
#用户强评标志
CSgitFtdcErrorConditionalOrderField["UserForceClose"] = "int"
#操作用户代码
CSgitFtdcErrorConditionalOrderField["ActiveUserID"] = "string"
#经纪公司报单编号
CSgitFtdcErrorConditionalOrderField["BrokerOrderSeq"] = "int"
#相关报单
CSgitFtdcErrorConditionalOrderField["RelativeOrderSysID"] = "string"
#错误代码
CSgitFtdcErrorConditionalOrderField["ErrorID"] = "int"
#错误信息
CSgitFtdcErrorConditionalOrderField["ErrorMsg"] = "string"
structDict['CSgitFtdcErrorConditionalOrderField'] = CSgitFtdcErrorConditionalOrderField


#查询错误报单操作
CSgitFtdcQryErrOrderActionField = {}
#经纪公司代码
CSgitFtdcQryErrOrderActionField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryErrOrderActionField["InvestorID"] = "string"
structDict['CSgitFtdcQryErrOrderActionField'] = CSgitFtdcQryErrOrderActionField


#错误报单操作
CSgitFtdcErrOrderActionField = {}
#经纪公司代码
CSgitFtdcErrOrderActionField["BrokerID"] = "string"
#投资者代码
CSgitFtdcErrOrderActionField["InvestorID"] = "string"
#报单操作引用
CSgitFtdcErrOrderActionField["OrderActionRef"] = "int"
#报单引用
CSgitFtdcErrOrderActionField["OrderRef"] = "string"
#请求编号
CSgitFtdcErrOrderActionField["RequestID"] = "int"
#前置编号
CSgitFtdcErrOrderActionField["FrontID"] = "int"
#会话编号
CSgitFtdcErrOrderActionField["SessionID"] = "int"
#交易所代码
CSgitFtdcErrOrderActionField["ExchangeID"] = "string"
#报单编号
CSgitFtdcErrOrderActionField["OrderSysID"] = "string"
#操作标志
CSgitFtdcErrOrderActionField["ActionFlag"] = "char"
#价格
CSgitFtdcErrOrderActionField["LimitPrice"] = "float"
#数量变化
CSgitFtdcErrOrderActionField["VolumeChange"] = "int"
#操作日期
CSgitFtdcErrOrderActionField["ActionDate"] = "string"
#操作时间
CSgitFtdcErrOrderActionField["ActionTime"] = "string"
#交易所交易员代码
CSgitFtdcErrOrderActionField["TraderID"] = "string"
#安装编号
CSgitFtdcErrOrderActionField["InstallID"] = "int"
#本地报单编号
CSgitFtdcErrOrderActionField["OrderLocalID"] = "string"
#操作本地编号
CSgitFtdcErrOrderActionField["ActionLocalID"] = "string"
#会员代码
CSgitFtdcErrOrderActionField["ParticipantID"] = "string"
#客户代码
CSgitFtdcErrOrderActionField["ClientID"] = "string"
#业务单元
CSgitFtdcErrOrderActionField["BusinessUnit"] = "string"
#报单操作状态
CSgitFtdcErrOrderActionField["OrderActionStatus"] = "char"
#用户代码
CSgitFtdcErrOrderActionField["UserID"] = "string"
#状态信息
CSgitFtdcErrOrderActionField["StatusMsg"] = "string"
#合约代码
CSgitFtdcErrOrderActionField["InstrumentID"] = "string"
#错误代码
CSgitFtdcErrOrderActionField["ErrorID"] = "int"
#错误信息
CSgitFtdcErrOrderActionField["ErrorMsg"] = "string"
structDict['CSgitFtdcErrOrderActionField'] = CSgitFtdcErrOrderActionField


#查询交易所状态
CSgitFtdcQryExchangeSequenceField = {}
#交易所代码
CSgitFtdcQryExchangeSequenceField["ExchangeID"] = "string"
structDict['CSgitFtdcQryExchangeSequenceField'] = CSgitFtdcQryExchangeSequenceField


#交易所状态
CSgitFtdcExchangeSequenceField = {}
#交易所代码
CSgitFtdcExchangeSequenceField["ExchangeID"] = "string"
#序号
CSgitFtdcExchangeSequenceField["SequenceNo"] = "int"
#合约交易状态
CSgitFtdcExchangeSequenceField["MarketStatus"] = "char"
structDict['CSgitFtdcExchangeSequenceField'] = CSgitFtdcExchangeSequenceField


#根据价格查询最大报单数量
CSgitFtdcQueryMaxOrderVolumeWithPriceField = {}
#经纪公司代码
CSgitFtdcQueryMaxOrderVolumeWithPriceField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQueryMaxOrderVolumeWithPriceField["InvestorID"] = "string"
#合约代码
CSgitFtdcQueryMaxOrderVolumeWithPriceField["InstrumentID"] = "string"
#买卖方向
CSgitFtdcQueryMaxOrderVolumeWithPriceField["Direction"] = "char"
#开平标志
CSgitFtdcQueryMaxOrderVolumeWithPriceField["OffsetFlag"] = "char"
#投机套保标志
CSgitFtdcQueryMaxOrderVolumeWithPriceField["HedgeFlag"] = "char"
#最大允许报单数量
CSgitFtdcQueryMaxOrderVolumeWithPriceField["MaxVolume"] = "int"
#报单价格
CSgitFtdcQueryMaxOrderVolumeWithPriceField["Price"] = "float"
structDict['CSgitFtdcQueryMaxOrderVolumeWithPriceField'] = CSgitFtdcQueryMaxOrderVolumeWithPriceField


#查询经纪公司交易参数
CSgitFtdcQryBrokerTradingParamsField = {}
#经纪公司代码
CSgitFtdcQryBrokerTradingParamsField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryBrokerTradingParamsField["InvestorID"] = "string"
structDict['CSgitFtdcQryBrokerTradingParamsField'] = CSgitFtdcQryBrokerTradingParamsField


#经纪公司交易参数
CSgitFtdcBrokerTradingParamsField = {}
#经纪公司代码
CSgitFtdcBrokerTradingParamsField["BrokerID"] = "string"
#投资者代码
CSgitFtdcBrokerTradingParamsField["InvestorID"] = "string"
#保证金价格类型
CSgitFtdcBrokerTradingParamsField["MarginPriceType"] = "char"
#盈亏算法
CSgitFtdcBrokerTradingParamsField["Algorithm"] = "char"
#可用是否包含平仓盈利
CSgitFtdcBrokerTradingParamsField["AvailIncludeCloseProfit"] = "char"
structDict['CSgitFtdcBrokerTradingParamsField'] = CSgitFtdcBrokerTradingParamsField


#查询经纪公司交易算法
CSgitFtdcQryBrokerTradingAlgosField = {}
#经纪公司代码
CSgitFtdcQryBrokerTradingAlgosField["BrokerID"] = "string"
#交易所代码
CSgitFtdcQryBrokerTradingAlgosField["ExchangeID"] = "string"
#合约代码
CSgitFtdcQryBrokerTradingAlgosField["InstrumentID"] = "string"
structDict['CSgitFtdcQryBrokerTradingAlgosField'] = CSgitFtdcQryBrokerTradingAlgosField


#经纪公司交易算法
CSgitFtdcBrokerTradingAlgosField = {}
#经纪公司代码
CSgitFtdcBrokerTradingAlgosField["BrokerID"] = "string"
#交易所代码
CSgitFtdcBrokerTradingAlgosField["ExchangeID"] = "string"
#合约代码
CSgitFtdcBrokerTradingAlgosField["InstrumentID"] = "string"
#持仓处理算法编号
CSgitFtdcBrokerTradingAlgosField["HandlePositionAlgoID"] = "char"
#寻找保证金率算法编号
CSgitFtdcBrokerTradingAlgosField["FindMarginRateAlgoID"] = "char"
#资金处理算法编号
CSgitFtdcBrokerTradingAlgosField["HandleTradingAccountAlgoID"] = "char"
structDict['CSgitFtdcBrokerTradingAlgosField'] = CSgitFtdcBrokerTradingAlgosField


#查询经纪公司资金
CSgitFtdcQueryBrokerDepositField = {}
#经纪公司代码
CSgitFtdcQueryBrokerDepositField["BrokerID"] = "string"
#交易所代码
CSgitFtdcQueryBrokerDepositField["ExchangeID"] = "string"
structDict['CSgitFtdcQueryBrokerDepositField'] = CSgitFtdcQueryBrokerDepositField


#经纪公司资金
CSgitFtdcBrokerDepositField = {}
#交易日期
CSgitFtdcBrokerDepositField["TradingDay"] = "string"
#经纪公司代码
CSgitFtdcBrokerDepositField["BrokerID"] = "string"
#会员代码
CSgitFtdcBrokerDepositField["ParticipantID"] = "string"
#交易所代码
CSgitFtdcBrokerDepositField["ExchangeID"] = "string"
#上次结算准备金
CSgitFtdcBrokerDepositField["PreBalance"] = "float"
#当前保证金总额
CSgitFtdcBrokerDepositField["CurrMargin"] = "float"
#平仓盈亏
CSgitFtdcBrokerDepositField["CloseProfit"] = "float"
#期货结算准备金
CSgitFtdcBrokerDepositField["Balance"] = "float"
#入金金额
CSgitFtdcBrokerDepositField["Deposit"] = "float"
#出金金额
CSgitFtdcBrokerDepositField["Withdraw"] = "float"
#可提资金
CSgitFtdcBrokerDepositField["Available"] = "float"
#基本准备金
CSgitFtdcBrokerDepositField["Reserve"] = "float"
#冻结的保证金
CSgitFtdcBrokerDepositField["FrozenMargin"] = "float"
structDict['CSgitFtdcBrokerDepositField'] = CSgitFtdcBrokerDepositField


#查询保证金监管系统经纪公司密钥
CSgitFtdcQryCFMMCBrokerKeyField = {}
#经纪公司代码
CSgitFtdcQryCFMMCBrokerKeyField["BrokerID"] = "string"
structDict['CSgitFtdcQryCFMMCBrokerKeyField'] = CSgitFtdcQryCFMMCBrokerKeyField


#保证金监管系统经纪公司密钥
CSgitFtdcCFMMCBrokerKeyField = {}
#经纪公司代码
CSgitFtdcCFMMCBrokerKeyField["BrokerID"] = "string"
#经纪公司统一编码
CSgitFtdcCFMMCBrokerKeyField["ParticipantID"] = "string"
#密钥生成日期
CSgitFtdcCFMMCBrokerKeyField["CreateDate"] = "string"
#密钥生成时间
CSgitFtdcCFMMCBrokerKeyField["CreateTime"] = "string"
#密钥编号
CSgitFtdcCFMMCBrokerKeyField["KeyID"] = "int"
#动态密钥
CSgitFtdcCFMMCBrokerKeyField["CurrentKey"] = "string"
#动态密钥类型
CSgitFtdcCFMMCBrokerKeyField["KeyKind"] = "char"
structDict['CSgitFtdcCFMMCBrokerKeyField'] = CSgitFtdcCFMMCBrokerKeyField


#保证金监管系统经纪公司资金账户密钥
CSgitFtdcCFMMCTradingAccountKeyField = {}
#经纪公司代码
CSgitFtdcCFMMCTradingAccountKeyField["BrokerID"] = "string"
#经纪公司统一编码
CSgitFtdcCFMMCTradingAccountKeyField["ParticipantID"] = "string"
#投资者帐号
CSgitFtdcCFMMCTradingAccountKeyField["AccountID"] = "string"
#密钥编号
CSgitFtdcCFMMCTradingAccountKeyField["KeyID"] = "int"
#动态密钥
CSgitFtdcCFMMCTradingAccountKeyField["CurrentKey"] = "string"
structDict['CSgitFtdcCFMMCTradingAccountKeyField'] = CSgitFtdcCFMMCTradingAccountKeyField


#请求查询保证金监管系统经纪公司资金账户密钥
CSgitFtdcQryCFMMCTradingAccountKeyField = {}
#经纪公司代码
CSgitFtdcQryCFMMCTradingAccountKeyField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryCFMMCTradingAccountKeyField["InvestorID"] = "string"
structDict['CSgitFtdcQryCFMMCTradingAccountKeyField'] = CSgitFtdcQryCFMMCTradingAccountKeyField


#用户动态令牌参数
CSgitFtdcBrokerUserOTPParamField = {}
#经纪公司代码
CSgitFtdcBrokerUserOTPParamField["BrokerID"] = "string"
#用户代码
CSgitFtdcBrokerUserOTPParamField["UserID"] = "string"
#动态令牌提供商
CSgitFtdcBrokerUserOTPParamField["OTPVendorsID"] = "string"
#动态令牌序列号
CSgitFtdcBrokerUserOTPParamField["SerialNumber"] = "string"
#令牌密钥
CSgitFtdcBrokerUserOTPParamField["AuthKey"] = "string"
#漂移值
CSgitFtdcBrokerUserOTPParamField["LastDrift"] = "int"
#成功值
CSgitFtdcBrokerUserOTPParamField["LastSuccess"] = "int"
#动态令牌类型
CSgitFtdcBrokerUserOTPParamField["OTPType"] = "char"
structDict['CSgitFtdcBrokerUserOTPParamField'] = CSgitFtdcBrokerUserOTPParamField


#手工同步用户动态令牌
CSgitFtdcManualSyncBrokerUserOTPField = {}
#经纪公司代码
CSgitFtdcManualSyncBrokerUserOTPField["BrokerID"] = "string"
#用户代码
CSgitFtdcManualSyncBrokerUserOTPField["UserID"] = "string"
#动态令牌类型
CSgitFtdcManualSyncBrokerUserOTPField["OTPType"] = "char"
#第一个动态密码
CSgitFtdcManualSyncBrokerUserOTPField["FirstOTP"] = "string"
#第二个动态密码
CSgitFtdcManualSyncBrokerUserOTPField["SecondOTP"] = "string"
structDict['CSgitFtdcManualSyncBrokerUserOTPField'] = CSgitFtdcManualSyncBrokerUserOTPField


#投资者手续费率模板
CSgitFtdcCommRateModelField = {}
#经纪公司代码
CSgitFtdcCommRateModelField["BrokerID"] = "string"
#手续费率模板代码
CSgitFtdcCommRateModelField["CommModelID"] = "string"
#模板名称
CSgitFtdcCommRateModelField["CommModelName"] = "string"
structDict['CSgitFtdcCommRateModelField'] = CSgitFtdcCommRateModelField


#请求查询投资者手续费率模板
CSgitFtdcQryCommRateModelField = {}
#经纪公司代码
CSgitFtdcQryCommRateModelField["BrokerID"] = "string"
#手续费率模板代码
CSgitFtdcQryCommRateModelField["CommModelID"] = "string"
structDict['CSgitFtdcQryCommRateModelField'] = CSgitFtdcQryCommRateModelField


#仓单折抵信息
CSgitFtdcEWarrantOffsetField = {}
#交易日期
CSgitFtdcEWarrantOffsetField["TradingDay"] = "string"
#经纪公司代码
CSgitFtdcEWarrantOffsetField["BrokerID"] = "string"
#投资者代码
CSgitFtdcEWarrantOffsetField["InvestorID"] = "string"
#交易所代码
CSgitFtdcEWarrantOffsetField["ExchangeID"] = "string"
#合约代码
CSgitFtdcEWarrantOffsetField["InstrumentID"] = "string"
#买卖方向
CSgitFtdcEWarrantOffsetField["Direction"] = "char"
#投机套保标志
CSgitFtdcEWarrantOffsetField["HedgeFlag"] = "char"
#数量
CSgitFtdcEWarrantOffsetField["Volume"] = "int"
structDict['CSgitFtdcEWarrantOffsetField'] = CSgitFtdcEWarrantOffsetField


#查询仓单折抵信息
CSgitFtdcQryEWarrantOffsetField = {}
#经纪公司代码
CSgitFtdcQryEWarrantOffsetField["BrokerID"] = "string"
#投资者代码
CSgitFtdcQryEWarrantOffsetField["InvestorID"] = "string"
#交易所代码
CSgitFtdcQryEWarrantOffsetField["ExchangeID"] = "string"
#合约代码
CSgitFtdcQryEWarrantOffsetField["InstrumentID"] = "string"
structDict['CSgitFtdcQryEWarrantOffsetField'] = CSgitFtdcQryEWarrantOffsetField


#转帐开户请求
CSgitFtdcReqOpenAccountField = {}
#业务功能码
CSgitFtdcReqOpenAccountField["TradeCode"] = "string"
#银行代码
CSgitFtdcReqOpenAccountField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcReqOpenAccountField["BankBranchID"] = "string"
#期商代码
CSgitFtdcReqOpenAccountField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcReqOpenAccountField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcReqOpenAccountField["TradeDate"] = "string"
#交易时间
CSgitFtdcReqOpenAccountField["TradeTime"] = "string"
#银行流水号
CSgitFtdcReqOpenAccountField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcReqOpenAccountField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcReqOpenAccountField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcReqOpenAccountField["LastFragment"] = "char"
#会话号
CSgitFtdcReqOpenAccountField["SessionID"] = "int"
#客户姓名
CSgitFtdcReqOpenAccountField["CustomerName"] = "string"
#证件类型
CSgitFtdcReqOpenAccountField["IdCardType"] = "char"
#证件号码
CSgitFtdcReqOpenAccountField["IdentifiedCardNo"] = "string"
#性别
CSgitFtdcReqOpenAccountField["Gender"] = "char"
#国家代码
CSgitFtdcReqOpenAccountField["CountryCode"] = "string"
#客户类型
CSgitFtdcReqOpenAccountField["CustType"] = "char"
#地址
CSgitFtdcReqOpenAccountField["Address"] = "string"
#邮编
CSgitFtdcReqOpenAccountField["ZipCode"] = "string"
#电话号码
CSgitFtdcReqOpenAccountField["Telephone"] = "string"
#手机
CSgitFtdcReqOpenAccountField["MobilePhone"] = "string"
#传真
CSgitFtdcReqOpenAccountField["Fax"] = "string"
#电子邮件
CSgitFtdcReqOpenAccountField["EMail"] = "string"
#资金账户状态
CSgitFtdcReqOpenAccountField["MoneyAccountStatus"] = "char"
#银行帐号
CSgitFtdcReqOpenAccountField["BankAccount"] = "string"
#银行密码
CSgitFtdcReqOpenAccountField["BankPassWord"] = "string"
#投资者帐号
CSgitFtdcReqOpenAccountField["AccountID"] = "string"
#期货密码
CSgitFtdcReqOpenAccountField["Password"] = "string"
#安装编号
CSgitFtdcReqOpenAccountField["InstallID"] = "int"
#验证客户证件号码标志
CSgitFtdcReqOpenAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CSgitFtdcReqOpenAccountField["CurrencyID"] = "string"
#汇钞标志
CSgitFtdcReqOpenAccountField["CashExchangeCode"] = "char"
#摘要
CSgitFtdcReqOpenAccountField["Digest"] = "string"
#银行帐号类型
CSgitFtdcReqOpenAccountField["BankAccType"] = "char"
#渠道标志
CSgitFtdcReqOpenAccountField["DeviceID"] = "string"
#期货单位帐号类型
CSgitFtdcReqOpenAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CSgitFtdcReqOpenAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CSgitFtdcReqOpenAccountField["BankSecuAcc"] = "string"
#银行密码标志
CSgitFtdcReqOpenAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CSgitFtdcReqOpenAccountField["SecuPwdFlag"] = "char"
#交易柜员
CSgitFtdcReqOpenAccountField["OperNo"] = "string"
#交易ID
CSgitFtdcReqOpenAccountField["TID"] = "int"
structDict['CSgitFtdcReqOpenAccountField'] = CSgitFtdcReqOpenAccountField


#转帐销户请求
CSgitFtdcReqCancelAccountField = {}
#业务功能码
CSgitFtdcReqCancelAccountField["TradeCode"] = "string"
#银行代码
CSgitFtdcReqCancelAccountField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcReqCancelAccountField["BankBranchID"] = "string"
#期商代码
CSgitFtdcReqCancelAccountField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcReqCancelAccountField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcReqCancelAccountField["TradeDate"] = "string"
#交易时间
CSgitFtdcReqCancelAccountField["TradeTime"] = "string"
#银行流水号
CSgitFtdcReqCancelAccountField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcReqCancelAccountField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcReqCancelAccountField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcReqCancelAccountField["LastFragment"] = "char"
#会话号
CSgitFtdcReqCancelAccountField["SessionID"] = "int"
#客户姓名
CSgitFtdcReqCancelAccountField["CustomerName"] = "string"
#证件类型
CSgitFtdcReqCancelAccountField["IdCardType"] = "char"
#证件号码
CSgitFtdcReqCancelAccountField["IdentifiedCardNo"] = "string"
#性别
CSgitFtdcReqCancelAccountField["Gender"] = "char"
#国家代码
CSgitFtdcReqCancelAccountField["CountryCode"] = "string"
#客户类型
CSgitFtdcReqCancelAccountField["CustType"] = "char"
#地址
CSgitFtdcReqCancelAccountField["Address"] = "string"
#邮编
CSgitFtdcReqCancelAccountField["ZipCode"] = "string"
#电话号码
CSgitFtdcReqCancelAccountField["Telephone"] = "string"
#手机
CSgitFtdcReqCancelAccountField["MobilePhone"] = "string"
#传真
CSgitFtdcReqCancelAccountField["Fax"] = "string"
#电子邮件
CSgitFtdcReqCancelAccountField["EMail"] = "string"
#资金账户状态
CSgitFtdcReqCancelAccountField["MoneyAccountStatus"] = "char"
#银行帐号
CSgitFtdcReqCancelAccountField["BankAccount"] = "string"
#银行密码
CSgitFtdcReqCancelAccountField["BankPassWord"] = "string"
#投资者帐号
CSgitFtdcReqCancelAccountField["AccountID"] = "string"
#期货密码
CSgitFtdcReqCancelAccountField["Password"] = "string"
#安装编号
CSgitFtdcReqCancelAccountField["InstallID"] = "int"
#验证客户证件号码标志
CSgitFtdcReqCancelAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CSgitFtdcReqCancelAccountField["CurrencyID"] = "string"
#汇钞标志
CSgitFtdcReqCancelAccountField["CashExchangeCode"] = "char"
#摘要
CSgitFtdcReqCancelAccountField["Digest"] = "string"
#银行帐号类型
CSgitFtdcReqCancelAccountField["BankAccType"] = "char"
#渠道标志
CSgitFtdcReqCancelAccountField["DeviceID"] = "string"
#期货单位帐号类型
CSgitFtdcReqCancelAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CSgitFtdcReqCancelAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CSgitFtdcReqCancelAccountField["BankSecuAcc"] = "string"
#银行密码标志
CSgitFtdcReqCancelAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CSgitFtdcReqCancelAccountField["SecuPwdFlag"] = "char"
#交易柜员
CSgitFtdcReqCancelAccountField["OperNo"] = "string"
#交易ID
CSgitFtdcReqCancelAccountField["TID"] = "int"
structDict['CSgitFtdcReqCancelAccountField'] = CSgitFtdcReqCancelAccountField


#变更银行账户请求
CSgitFtdcReqChangeAccountField = {}
#业务功能码
CSgitFtdcReqChangeAccountField["TradeCode"] = "string"
#银行代码
CSgitFtdcReqChangeAccountField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcReqChangeAccountField["BankBranchID"] = "string"
#期商代码
CSgitFtdcReqChangeAccountField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcReqChangeAccountField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcReqChangeAccountField["TradeDate"] = "string"
#交易时间
CSgitFtdcReqChangeAccountField["TradeTime"] = "string"
#银行流水号
CSgitFtdcReqChangeAccountField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcReqChangeAccountField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcReqChangeAccountField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcReqChangeAccountField["LastFragment"] = "char"
#会话号
CSgitFtdcReqChangeAccountField["SessionID"] = "int"
#客户姓名
CSgitFtdcReqChangeAccountField["CustomerName"] = "string"
#证件类型
CSgitFtdcReqChangeAccountField["IdCardType"] = "char"
#证件号码
CSgitFtdcReqChangeAccountField["IdentifiedCardNo"] = "string"
#性别
CSgitFtdcReqChangeAccountField["Gender"] = "char"
#国家代码
CSgitFtdcReqChangeAccountField["CountryCode"] = "string"
#客户类型
CSgitFtdcReqChangeAccountField["CustType"] = "char"
#地址
CSgitFtdcReqChangeAccountField["Address"] = "string"
#邮编
CSgitFtdcReqChangeAccountField["ZipCode"] = "string"
#电话号码
CSgitFtdcReqChangeAccountField["Telephone"] = "string"
#手机
CSgitFtdcReqChangeAccountField["MobilePhone"] = "string"
#传真
CSgitFtdcReqChangeAccountField["Fax"] = "string"
#电子邮件
CSgitFtdcReqChangeAccountField["EMail"] = "string"
#资金账户状态
CSgitFtdcReqChangeAccountField["MoneyAccountStatus"] = "char"
#银行帐号
CSgitFtdcReqChangeAccountField["BankAccount"] = "string"
#银行密码
CSgitFtdcReqChangeAccountField["BankPassWord"] = "string"
#新银行帐号
CSgitFtdcReqChangeAccountField["NewBankAccount"] = "string"
#新银行密码
CSgitFtdcReqChangeAccountField["NewBankPassWord"] = "string"
#投资者帐号
CSgitFtdcReqChangeAccountField["AccountID"] = "string"
#期货密码
CSgitFtdcReqChangeAccountField["Password"] = "string"
#银行帐号类型
CSgitFtdcReqChangeAccountField["BankAccType"] = "char"
#安装编号
CSgitFtdcReqChangeAccountField["InstallID"] = "int"
#验证客户证件号码标志
CSgitFtdcReqChangeAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CSgitFtdcReqChangeAccountField["CurrencyID"] = "string"
#期货公司银行编码
CSgitFtdcReqChangeAccountField["BrokerIDByBank"] = "string"
#银行密码标志
CSgitFtdcReqChangeAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CSgitFtdcReqChangeAccountField["SecuPwdFlag"] = "char"
#交易ID
CSgitFtdcReqChangeAccountField["TID"] = "int"
#摘要
CSgitFtdcReqChangeAccountField["Digest"] = "string"
structDict['CSgitFtdcReqChangeAccountField'] = CSgitFtdcReqChangeAccountField


#转账请求
CSgitFtdcReqTransferField = {}
#业务功能码
CSgitFtdcReqTransferField["TradeCode"] = "string"
#银行代码
CSgitFtdcReqTransferField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcReqTransferField["BankBranchID"] = "string"
#期商代码
CSgitFtdcReqTransferField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcReqTransferField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcReqTransferField["TradeDate"] = "string"
#交易时间
CSgitFtdcReqTransferField["TradeTime"] = "string"
#银行流水号
CSgitFtdcReqTransferField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcReqTransferField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcReqTransferField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcReqTransferField["LastFragment"] = "char"
#会话号
CSgitFtdcReqTransferField["SessionID"] = "int"
#客户姓名
CSgitFtdcReqTransferField["CustomerName"] = "string"
#证件类型
CSgitFtdcReqTransferField["IdCardType"] = "char"
#证件号码
CSgitFtdcReqTransferField["IdentifiedCardNo"] = "string"
#客户类型
CSgitFtdcReqTransferField["CustType"] = "char"
#银行帐号
CSgitFtdcReqTransferField["BankAccount"] = "string"
#银行密码
CSgitFtdcReqTransferField["BankPassWord"] = "string"
#投资者帐号
CSgitFtdcReqTransferField["AccountID"] = "string"
#期货密码
CSgitFtdcReqTransferField["Password"] = "string"
#安装编号
CSgitFtdcReqTransferField["InstallID"] = "int"
#期货公司流水号
CSgitFtdcReqTransferField["FutureSerial"] = "int"
#用户标识
CSgitFtdcReqTransferField["UserID"] = "string"
#验证客户证件号码标志
CSgitFtdcReqTransferField["VerifyCertNoFlag"] = "char"
#币种代码
CSgitFtdcReqTransferField["CurrencyID"] = "string"
#转帐金额
CSgitFtdcReqTransferField["TradeAmount"] = "float"
#期货可取金额
CSgitFtdcReqTransferField["FutureFetchAmount"] = "float"
#费用支付标志
CSgitFtdcReqTransferField["FeePayFlag"] = "char"
#应收客户费用
CSgitFtdcReqTransferField["CustFee"] = "float"
#应收期货公司费用
CSgitFtdcReqTransferField["BrokerFee"] = "float"
#发送方给接收方的消息
CSgitFtdcReqTransferField["Message"] = "string"
#摘要
CSgitFtdcReqTransferField["Digest"] = "string"
#银行帐号类型
CSgitFtdcReqTransferField["BankAccType"] = "char"
#渠道标志
CSgitFtdcReqTransferField["DeviceID"] = "string"
#期货单位帐号类型
CSgitFtdcReqTransferField["BankSecuAccType"] = "char"
#期货公司银行编码
CSgitFtdcReqTransferField["BrokerIDByBank"] = "string"
#期货单位帐号
CSgitFtdcReqTransferField["BankSecuAcc"] = "string"
#银行密码标志
CSgitFtdcReqTransferField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CSgitFtdcReqTransferField["SecuPwdFlag"] = "char"
#交易柜员
CSgitFtdcReqTransferField["OperNo"] = "string"
#请求编号
CSgitFtdcReqTransferField["RequestID"] = "int"
#交易ID
CSgitFtdcReqTransferField["TID"] = "int"
#转账交易状态
CSgitFtdcReqTransferField["TransferStatus"] = "char"
structDict['CSgitFtdcReqTransferField'] = CSgitFtdcReqTransferField


#银行发起银行资金转期货响应
CSgitFtdcRspTransferField = {}
#业务功能码
CSgitFtdcRspTransferField["TradeCode"] = "string"
#银行代码
CSgitFtdcRspTransferField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcRspTransferField["BankBranchID"] = "string"
#期商代码
CSgitFtdcRspTransferField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcRspTransferField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcRspTransferField["TradeDate"] = "string"
#交易时间
CSgitFtdcRspTransferField["TradeTime"] = "string"
#银行流水号
CSgitFtdcRspTransferField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcRspTransferField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcRspTransferField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcRspTransferField["LastFragment"] = "char"
#会话号
CSgitFtdcRspTransferField["SessionID"] = "int"
#客户姓名
CSgitFtdcRspTransferField["CustomerName"] = "string"
#证件类型
CSgitFtdcRspTransferField["IdCardType"] = "char"
#证件号码
CSgitFtdcRspTransferField["IdentifiedCardNo"] = "string"
#客户类型
CSgitFtdcRspTransferField["CustType"] = "char"
#银行帐号
CSgitFtdcRspTransferField["BankAccount"] = "string"
#银行密码
CSgitFtdcRspTransferField["BankPassWord"] = "string"
#投资者帐号
CSgitFtdcRspTransferField["AccountID"] = "string"
#期货密码
CSgitFtdcRspTransferField["Password"] = "string"
#安装编号
CSgitFtdcRspTransferField["InstallID"] = "int"
#期货公司流水号
CSgitFtdcRspTransferField["FutureSerial"] = "int"
#用户标识
CSgitFtdcRspTransferField["UserID"] = "string"
#验证客户证件号码标志
CSgitFtdcRspTransferField["VerifyCertNoFlag"] = "char"
#币种代码
CSgitFtdcRspTransferField["CurrencyID"] = "string"
#转帐金额
CSgitFtdcRspTransferField["TradeAmount"] = "float"
#期货可取金额
CSgitFtdcRspTransferField["FutureFetchAmount"] = "float"
#费用支付标志
CSgitFtdcRspTransferField["FeePayFlag"] = "char"
#应收客户费用
CSgitFtdcRspTransferField["CustFee"] = "float"
#应收期货公司费用
CSgitFtdcRspTransferField["BrokerFee"] = "float"
#发送方给接收方的消息
CSgitFtdcRspTransferField["Message"] = "string"
#摘要
CSgitFtdcRspTransferField["Digest"] = "string"
#银行帐号类型
CSgitFtdcRspTransferField["BankAccType"] = "char"
#渠道标志
CSgitFtdcRspTransferField["DeviceID"] = "string"
#期货单位帐号类型
CSgitFtdcRspTransferField["BankSecuAccType"] = "char"
#期货公司银行编码
CSgitFtdcRspTransferField["BrokerIDByBank"] = "string"
#期货单位帐号
CSgitFtdcRspTransferField["BankSecuAcc"] = "string"
#银行密码标志
CSgitFtdcRspTransferField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CSgitFtdcRspTransferField["SecuPwdFlag"] = "char"
#交易柜员
CSgitFtdcRspTransferField["OperNo"] = "string"
#请求编号
CSgitFtdcRspTransferField["RequestID"] = "int"
#交易ID
CSgitFtdcRspTransferField["TID"] = "int"
#转账交易状态
CSgitFtdcRspTransferField["TransferStatus"] = "char"
#错误代码
CSgitFtdcRspTransferField["ErrorID"] = "int"
#错误信息
CSgitFtdcRspTransferField["ErrorMsg"] = "string"
structDict['CSgitFtdcRspTransferField'] = CSgitFtdcRspTransferField


#冲正请求
CSgitFtdcReqRepealField = {}
#冲正时间间隔
CSgitFtdcReqRepealField["RepealTimeInterval"] = "int"
#已经冲正次数
CSgitFtdcReqRepealField["RepealedTimes"] = "int"
#银行冲正标志
CSgitFtdcReqRepealField["BankRepealFlag"] = "char"
#期商冲正标志
CSgitFtdcReqRepealField["BrokerRepealFlag"] = "char"
#被冲正平台流水号
CSgitFtdcReqRepealField["PlateRepealSerial"] = "int"
#被冲正银行流水号
CSgitFtdcReqRepealField["BankRepealSerial"] = "string"
#被冲正期货流水号
CSgitFtdcReqRepealField["FutureRepealSerial"] = "int"
#业务功能码
CSgitFtdcReqRepealField["TradeCode"] = "string"
#银行代码
CSgitFtdcReqRepealField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcReqRepealField["BankBranchID"] = "string"
#期商代码
CSgitFtdcReqRepealField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcReqRepealField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcReqRepealField["TradeDate"] = "string"
#交易时间
CSgitFtdcReqRepealField["TradeTime"] = "string"
#银行流水号
CSgitFtdcReqRepealField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcReqRepealField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcReqRepealField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcReqRepealField["LastFragment"] = "char"
#会话号
CSgitFtdcReqRepealField["SessionID"] = "int"
#客户姓名
CSgitFtdcReqRepealField["CustomerName"] = "string"
#证件类型
CSgitFtdcReqRepealField["IdCardType"] = "char"
#证件号码
CSgitFtdcReqRepealField["IdentifiedCardNo"] = "string"
#客户类型
CSgitFtdcReqRepealField["CustType"] = "char"
#银行帐号
CSgitFtdcReqRepealField["BankAccount"] = "string"
#银行密码
CSgitFtdcReqRepealField["BankPassWord"] = "string"
#投资者帐号
CSgitFtdcReqRepealField["AccountID"] = "string"
#期货密码
CSgitFtdcReqRepealField["Password"] = "string"
#安装编号
CSgitFtdcReqRepealField["InstallID"] = "int"
#期货公司流水号
CSgitFtdcReqRepealField["FutureSerial"] = "int"
#用户标识
CSgitFtdcReqRepealField["UserID"] = "string"
#验证客户证件号码标志
CSgitFtdcReqRepealField["VerifyCertNoFlag"] = "char"
#币种代码
CSgitFtdcReqRepealField["CurrencyID"] = "string"
#转帐金额
CSgitFtdcReqRepealField["TradeAmount"] = "float"
#期货可取金额
CSgitFtdcReqRepealField["FutureFetchAmount"] = "float"
#费用支付标志
CSgitFtdcReqRepealField["FeePayFlag"] = "char"
#应收客户费用
CSgitFtdcReqRepealField["CustFee"] = "float"
#应收期货公司费用
CSgitFtdcReqRepealField["BrokerFee"] = "float"
#发送方给接收方的消息
CSgitFtdcReqRepealField["Message"] = "string"
#摘要
CSgitFtdcReqRepealField["Digest"] = "string"
#银行帐号类型
CSgitFtdcReqRepealField["BankAccType"] = "char"
#渠道标志
CSgitFtdcReqRepealField["DeviceID"] = "string"
#期货单位帐号类型
CSgitFtdcReqRepealField["BankSecuAccType"] = "char"
#期货公司银行编码
CSgitFtdcReqRepealField["BrokerIDByBank"] = "string"
#期货单位帐号
CSgitFtdcReqRepealField["BankSecuAcc"] = "string"
#银行密码标志
CSgitFtdcReqRepealField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CSgitFtdcReqRepealField["SecuPwdFlag"] = "char"
#交易柜员
CSgitFtdcReqRepealField["OperNo"] = "string"
#请求编号
CSgitFtdcReqRepealField["RequestID"] = "int"
#交易ID
CSgitFtdcReqRepealField["TID"] = "int"
#转账交易状态
CSgitFtdcReqRepealField["TransferStatus"] = "char"
structDict['CSgitFtdcReqRepealField'] = CSgitFtdcReqRepealField


#冲正响应
CSgitFtdcRspRepealField = {}
#冲正时间间隔
CSgitFtdcRspRepealField["RepealTimeInterval"] = "int"
#已经冲正次数
CSgitFtdcRspRepealField["RepealedTimes"] = "int"
#银行冲正标志
CSgitFtdcRspRepealField["BankRepealFlag"] = "char"
#期商冲正标志
CSgitFtdcRspRepealField["BrokerRepealFlag"] = "char"
#被冲正平台流水号
CSgitFtdcRspRepealField["PlateRepealSerial"] = "int"
#被冲正银行流水号
CSgitFtdcRspRepealField["BankRepealSerial"] = "string"
#被冲正期货流水号
CSgitFtdcRspRepealField["FutureRepealSerial"] = "int"
#业务功能码
CSgitFtdcRspRepealField["TradeCode"] = "string"
#银行代码
CSgitFtdcRspRepealField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcRspRepealField["BankBranchID"] = "string"
#期商代码
CSgitFtdcRspRepealField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcRspRepealField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcRspRepealField["TradeDate"] = "string"
#交易时间
CSgitFtdcRspRepealField["TradeTime"] = "string"
#银行流水号
CSgitFtdcRspRepealField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcRspRepealField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcRspRepealField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcRspRepealField["LastFragment"] = "char"
#会话号
CSgitFtdcRspRepealField["SessionID"] = "int"
#客户姓名
CSgitFtdcRspRepealField["CustomerName"] = "string"
#证件类型
CSgitFtdcRspRepealField["IdCardType"] = "char"
#证件号码
CSgitFtdcRspRepealField["IdentifiedCardNo"] = "string"
#客户类型
CSgitFtdcRspRepealField["CustType"] = "char"
#银行帐号
CSgitFtdcRspRepealField["BankAccount"] = "string"
#银行密码
CSgitFtdcRspRepealField["BankPassWord"] = "string"
#投资者帐号
CSgitFtdcRspRepealField["AccountID"] = "string"
#期货密码
CSgitFtdcRspRepealField["Password"] = "string"
#安装编号
CSgitFtdcRspRepealField["InstallID"] = "int"
#期货公司流水号
CSgitFtdcRspRepealField["FutureSerial"] = "int"
#用户标识
CSgitFtdcRspRepealField["UserID"] = "string"
#验证客户证件号码标志
CSgitFtdcRspRepealField["VerifyCertNoFlag"] = "char"
#币种代码
CSgitFtdcRspRepealField["CurrencyID"] = "string"
#转帐金额
CSgitFtdcRspRepealField["TradeAmount"] = "float"
#期货可取金额
CSgitFtdcRspRepealField["FutureFetchAmount"] = "float"
#费用支付标志
CSgitFtdcRspRepealField["FeePayFlag"] = "char"
#应收客户费用
CSgitFtdcRspRepealField["CustFee"] = "float"
#应收期货公司费用
CSgitFtdcRspRepealField["BrokerFee"] = "float"
#发送方给接收方的消息
CSgitFtdcRspRepealField["Message"] = "string"
#摘要
CSgitFtdcRspRepealField["Digest"] = "string"
#银行帐号类型
CSgitFtdcRspRepealField["BankAccType"] = "char"
#渠道标志
CSgitFtdcRspRepealField["DeviceID"] = "string"
#期货单位帐号类型
CSgitFtdcRspRepealField["BankSecuAccType"] = "char"
#期货公司银行编码
CSgitFtdcRspRepealField["BrokerIDByBank"] = "string"
#期货单位帐号
CSgitFtdcRspRepealField["BankSecuAcc"] = "string"
#银行密码标志
CSgitFtdcRspRepealField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CSgitFtdcRspRepealField["SecuPwdFlag"] = "char"
#交易柜员
CSgitFtdcRspRepealField["OperNo"] = "string"
#请求编号
CSgitFtdcRspRepealField["RequestID"] = "int"
#交易ID
CSgitFtdcRspRepealField["TID"] = "int"
#转账交易状态
CSgitFtdcRspRepealField["TransferStatus"] = "char"
#错误代码
CSgitFtdcRspRepealField["ErrorID"] = "int"
#错误信息
CSgitFtdcRspRepealField["ErrorMsg"] = "string"
structDict['CSgitFtdcRspRepealField'] = CSgitFtdcRspRepealField


#查询账户信息请求
CSgitFtdcReqQueryAccountField = {}
#业务功能码
CSgitFtdcReqQueryAccountField["TradeCode"] = "string"
#银行代码
CSgitFtdcReqQueryAccountField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcReqQueryAccountField["BankBranchID"] = "string"
#期商代码
CSgitFtdcReqQueryAccountField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcReqQueryAccountField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcReqQueryAccountField["TradeDate"] = "string"
#交易时间
CSgitFtdcReqQueryAccountField["TradeTime"] = "string"
#银行流水号
CSgitFtdcReqQueryAccountField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcReqQueryAccountField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcReqQueryAccountField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcReqQueryAccountField["LastFragment"] = "char"
#会话号
CSgitFtdcReqQueryAccountField["SessionID"] = "int"
#客户姓名
CSgitFtdcReqQueryAccountField["CustomerName"] = "string"
#证件类型
CSgitFtdcReqQueryAccountField["IdCardType"] = "char"
#证件号码
CSgitFtdcReqQueryAccountField["IdentifiedCardNo"] = "string"
#客户类型
CSgitFtdcReqQueryAccountField["CustType"] = "char"
#银行帐号
CSgitFtdcReqQueryAccountField["BankAccount"] = "string"
#银行密码
CSgitFtdcReqQueryAccountField["BankPassWord"] = "string"
#投资者帐号
CSgitFtdcReqQueryAccountField["AccountID"] = "string"
#期货密码
CSgitFtdcReqQueryAccountField["Password"] = "string"
#期货公司流水号
CSgitFtdcReqQueryAccountField["FutureSerial"] = "int"
#安装编号
CSgitFtdcReqQueryAccountField["InstallID"] = "int"
#用户标识
CSgitFtdcReqQueryAccountField["UserID"] = "string"
#验证客户证件号码标志
CSgitFtdcReqQueryAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CSgitFtdcReqQueryAccountField["CurrencyID"] = "string"
#摘要
CSgitFtdcReqQueryAccountField["Digest"] = "string"
#银行帐号类型
CSgitFtdcReqQueryAccountField["BankAccType"] = "char"
#渠道标志
CSgitFtdcReqQueryAccountField["DeviceID"] = "string"
#期货单位帐号类型
CSgitFtdcReqQueryAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CSgitFtdcReqQueryAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CSgitFtdcReqQueryAccountField["BankSecuAcc"] = "string"
#银行密码标志
CSgitFtdcReqQueryAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CSgitFtdcReqQueryAccountField["SecuPwdFlag"] = "char"
#交易柜员
CSgitFtdcReqQueryAccountField["OperNo"] = "string"
#请求编号
CSgitFtdcReqQueryAccountField["RequestID"] = "int"
#交易ID
CSgitFtdcReqQueryAccountField["TID"] = "int"
structDict['CSgitFtdcReqQueryAccountField'] = CSgitFtdcReqQueryAccountField


#查询账户信息响应
CSgitFtdcRspQueryAccountField = {}
#业务功能码
CSgitFtdcRspQueryAccountField["TradeCode"] = "string"
#银行代码
CSgitFtdcRspQueryAccountField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcRspQueryAccountField["BankBranchID"] = "string"
#期商代码
CSgitFtdcRspQueryAccountField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcRspQueryAccountField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcRspQueryAccountField["TradeDate"] = "string"
#交易时间
CSgitFtdcRspQueryAccountField["TradeTime"] = "string"
#银行流水号
CSgitFtdcRspQueryAccountField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcRspQueryAccountField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcRspQueryAccountField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcRspQueryAccountField["LastFragment"] = "char"
#会话号
CSgitFtdcRspQueryAccountField["SessionID"] = "int"
#客户姓名
CSgitFtdcRspQueryAccountField["CustomerName"] = "string"
#证件类型
CSgitFtdcRspQueryAccountField["IdCardType"] = "char"
#证件号码
CSgitFtdcRspQueryAccountField["IdentifiedCardNo"] = "string"
#客户类型
CSgitFtdcRspQueryAccountField["CustType"] = "char"
#银行帐号
CSgitFtdcRspQueryAccountField["BankAccount"] = "string"
#银行密码
CSgitFtdcRspQueryAccountField["BankPassWord"] = "string"
#投资者帐号
CSgitFtdcRspQueryAccountField["AccountID"] = "string"
#期货密码
CSgitFtdcRspQueryAccountField["Password"] = "string"
#期货公司流水号
CSgitFtdcRspQueryAccountField["FutureSerial"] = "int"
#安装编号
CSgitFtdcRspQueryAccountField["InstallID"] = "int"
#用户标识
CSgitFtdcRspQueryAccountField["UserID"] = "string"
#验证客户证件号码标志
CSgitFtdcRspQueryAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CSgitFtdcRspQueryAccountField["CurrencyID"] = "string"
#摘要
CSgitFtdcRspQueryAccountField["Digest"] = "string"
#银行帐号类型
CSgitFtdcRspQueryAccountField["BankAccType"] = "char"
#渠道标志
CSgitFtdcRspQueryAccountField["DeviceID"] = "string"
#期货单位帐号类型
CSgitFtdcRspQueryAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CSgitFtdcRspQueryAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CSgitFtdcRspQueryAccountField["BankSecuAcc"] = "string"
#银行密码标志
CSgitFtdcRspQueryAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CSgitFtdcRspQueryAccountField["SecuPwdFlag"] = "char"
#交易柜员
CSgitFtdcRspQueryAccountField["OperNo"] = "string"
#请求编号
CSgitFtdcRspQueryAccountField["RequestID"] = "int"
#交易ID
CSgitFtdcRspQueryAccountField["TID"] = "int"
#银行可用金额
CSgitFtdcRspQueryAccountField["BankUseAmount"] = "float"
#银行可取金额
CSgitFtdcRspQueryAccountField["BankFetchAmount"] = "float"
structDict['CSgitFtdcRspQueryAccountField'] = CSgitFtdcRspQueryAccountField


#期商签到签退
CSgitFtdcFutureSignIOField = {}
#业务功能码
CSgitFtdcFutureSignIOField["TradeCode"] = "string"
#银行代码
CSgitFtdcFutureSignIOField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcFutureSignIOField["BankBranchID"] = "string"
#期商代码
CSgitFtdcFutureSignIOField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcFutureSignIOField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcFutureSignIOField["TradeDate"] = "string"
#交易时间
CSgitFtdcFutureSignIOField["TradeTime"] = "string"
#银行流水号
CSgitFtdcFutureSignIOField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcFutureSignIOField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcFutureSignIOField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcFutureSignIOField["LastFragment"] = "char"
#会话号
CSgitFtdcFutureSignIOField["SessionID"] = "int"
#安装编号
CSgitFtdcFutureSignIOField["InstallID"] = "int"
#用户标识
CSgitFtdcFutureSignIOField["UserID"] = "string"
#摘要
CSgitFtdcFutureSignIOField["Digest"] = "string"
#币种代码
CSgitFtdcFutureSignIOField["CurrencyID"] = "string"
#渠道标志
CSgitFtdcFutureSignIOField["DeviceID"] = "string"
#期货公司银行编码
CSgitFtdcFutureSignIOField["BrokerIDByBank"] = "string"
#交易柜员
CSgitFtdcFutureSignIOField["OperNo"] = "string"
#请求编号
CSgitFtdcFutureSignIOField["RequestID"] = "int"
#交易ID
CSgitFtdcFutureSignIOField["TID"] = "int"
structDict['CSgitFtdcFutureSignIOField'] = CSgitFtdcFutureSignIOField


#期商签到响应
CSgitFtdcRspFutureSignInField = {}
#业务功能码
CSgitFtdcRspFutureSignInField["TradeCode"] = "string"
#银行代码
CSgitFtdcRspFutureSignInField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcRspFutureSignInField["BankBranchID"] = "string"
#期商代码
CSgitFtdcRspFutureSignInField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcRspFutureSignInField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcRspFutureSignInField["TradeDate"] = "string"
#交易时间
CSgitFtdcRspFutureSignInField["TradeTime"] = "string"
#银行流水号
CSgitFtdcRspFutureSignInField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcRspFutureSignInField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcRspFutureSignInField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcRspFutureSignInField["LastFragment"] = "char"
#会话号
CSgitFtdcRspFutureSignInField["SessionID"] = "int"
#安装编号
CSgitFtdcRspFutureSignInField["InstallID"] = "int"
#用户标识
CSgitFtdcRspFutureSignInField["UserID"] = "string"
#摘要
CSgitFtdcRspFutureSignInField["Digest"] = "string"
#币种代码
CSgitFtdcRspFutureSignInField["CurrencyID"] = "string"
#渠道标志
CSgitFtdcRspFutureSignInField["DeviceID"] = "string"
#期货公司银行编码
CSgitFtdcRspFutureSignInField["BrokerIDByBank"] = "string"
#交易柜员
CSgitFtdcRspFutureSignInField["OperNo"] = "string"
#请求编号
CSgitFtdcRspFutureSignInField["RequestID"] = "int"
#交易ID
CSgitFtdcRspFutureSignInField["TID"] = "int"
#错误代码
CSgitFtdcRspFutureSignInField["ErrorID"] = "int"
#错误信息
CSgitFtdcRspFutureSignInField["ErrorMsg"] = "string"
#PIN密钥
CSgitFtdcRspFutureSignInField["PinKey"] = "string"
#MAC密钥
CSgitFtdcRspFutureSignInField["MacKey"] = "string"
structDict['CSgitFtdcRspFutureSignInField'] = CSgitFtdcRspFutureSignInField


#期商签退请求
CSgitFtdcReqFutureSignOutField = {}
#业务功能码
CSgitFtdcReqFutureSignOutField["TradeCode"] = "string"
#银行代码
CSgitFtdcReqFutureSignOutField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcReqFutureSignOutField["BankBranchID"] = "string"
#期商代码
CSgitFtdcReqFutureSignOutField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcReqFutureSignOutField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcReqFutureSignOutField["TradeDate"] = "string"
#交易时间
CSgitFtdcReqFutureSignOutField["TradeTime"] = "string"
#银行流水号
CSgitFtdcReqFutureSignOutField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcReqFutureSignOutField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcReqFutureSignOutField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcReqFutureSignOutField["LastFragment"] = "char"
#会话号
CSgitFtdcReqFutureSignOutField["SessionID"] = "int"
#安装编号
CSgitFtdcReqFutureSignOutField["InstallID"] = "int"
#用户标识
CSgitFtdcReqFutureSignOutField["UserID"] = "string"
#摘要
CSgitFtdcReqFutureSignOutField["Digest"] = "string"
#币种代码
CSgitFtdcReqFutureSignOutField["CurrencyID"] = "string"
#渠道标志
CSgitFtdcReqFutureSignOutField["DeviceID"] = "string"
#期货公司银行编码
CSgitFtdcReqFutureSignOutField["BrokerIDByBank"] = "string"
#交易柜员
CSgitFtdcReqFutureSignOutField["OperNo"] = "string"
#请求编号
CSgitFtdcReqFutureSignOutField["RequestID"] = "int"
#交易ID
CSgitFtdcReqFutureSignOutField["TID"] = "int"
structDict['CSgitFtdcReqFutureSignOutField'] = CSgitFtdcReqFutureSignOutField


#期商签退响应
CSgitFtdcRspFutureSignOutField = {}
#业务功能码
CSgitFtdcRspFutureSignOutField["TradeCode"] = "string"
#银行代码
CSgitFtdcRspFutureSignOutField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcRspFutureSignOutField["BankBranchID"] = "string"
#期商代码
CSgitFtdcRspFutureSignOutField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcRspFutureSignOutField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcRspFutureSignOutField["TradeDate"] = "string"
#交易时间
CSgitFtdcRspFutureSignOutField["TradeTime"] = "string"
#银行流水号
CSgitFtdcRspFutureSignOutField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcRspFutureSignOutField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcRspFutureSignOutField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcRspFutureSignOutField["LastFragment"] = "char"
#会话号
CSgitFtdcRspFutureSignOutField["SessionID"] = "int"
#安装编号
CSgitFtdcRspFutureSignOutField["InstallID"] = "int"
#用户标识
CSgitFtdcRspFutureSignOutField["UserID"] = "string"
#摘要
CSgitFtdcRspFutureSignOutField["Digest"] = "string"
#币种代码
CSgitFtdcRspFutureSignOutField["CurrencyID"] = "string"
#渠道标志
CSgitFtdcRspFutureSignOutField["DeviceID"] = "string"
#期货公司银行编码
CSgitFtdcRspFutureSignOutField["BrokerIDByBank"] = "string"
#交易柜员
CSgitFtdcRspFutureSignOutField["OperNo"] = "string"
#请求编号
CSgitFtdcRspFutureSignOutField["RequestID"] = "int"
#交易ID
CSgitFtdcRspFutureSignOutField["TID"] = "int"
#错误代码
CSgitFtdcRspFutureSignOutField["ErrorID"] = "int"
#错误信息
CSgitFtdcRspFutureSignOutField["ErrorMsg"] = "string"
structDict['CSgitFtdcRspFutureSignOutField'] = CSgitFtdcRspFutureSignOutField


#查询指定流水号的交易结果请求
CSgitFtdcReqQueryTradeResultBySerialField = {}
#业务功能码
CSgitFtdcReqQueryTradeResultBySerialField["TradeCode"] = "string"
#银行代码
CSgitFtdcReqQueryTradeResultBySerialField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcReqQueryTradeResultBySerialField["BankBranchID"] = "string"
#期商代码
CSgitFtdcReqQueryTradeResultBySerialField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcReqQueryTradeResultBySerialField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcReqQueryTradeResultBySerialField["TradeDate"] = "string"
#交易时间
CSgitFtdcReqQueryTradeResultBySerialField["TradeTime"] = "string"
#银行流水号
CSgitFtdcReqQueryTradeResultBySerialField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcReqQueryTradeResultBySerialField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcReqQueryTradeResultBySerialField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcReqQueryTradeResultBySerialField["LastFragment"] = "char"
#会话号
CSgitFtdcReqQueryTradeResultBySerialField["SessionID"] = "int"
#流水号
CSgitFtdcReqQueryTradeResultBySerialField["Reference"] = "int"
#本流水号发布者的机构类型
CSgitFtdcReqQueryTradeResultBySerialField["RefrenceIssureType"] = "char"
#本流水号发布者机构编码
CSgitFtdcReqQueryTradeResultBySerialField["RefrenceIssure"] = "string"
#客户姓名
CSgitFtdcReqQueryTradeResultBySerialField["CustomerName"] = "string"
#证件类型
CSgitFtdcReqQueryTradeResultBySerialField["IdCardType"] = "char"
#证件号码
CSgitFtdcReqQueryTradeResultBySerialField["IdentifiedCardNo"] = "string"
#客户类型
CSgitFtdcReqQueryTradeResultBySerialField["CustType"] = "char"
#银行帐号
CSgitFtdcReqQueryTradeResultBySerialField["BankAccount"] = "string"
#银行密码
CSgitFtdcReqQueryTradeResultBySerialField["BankPassWord"] = "string"
#投资者帐号
CSgitFtdcReqQueryTradeResultBySerialField["AccountID"] = "string"
#期货密码
CSgitFtdcReqQueryTradeResultBySerialField["Password"] = "string"
#币种代码
CSgitFtdcReqQueryTradeResultBySerialField["CurrencyID"] = "string"
#转帐金额
CSgitFtdcReqQueryTradeResultBySerialField["TradeAmount"] = "float"
#摘要
CSgitFtdcReqQueryTradeResultBySerialField["Digest"] = "string"
structDict['CSgitFtdcReqQueryTradeResultBySerialField'] = CSgitFtdcReqQueryTradeResultBySerialField


#查询指定流水号的交易结果响应
CSgitFtdcRspQueryTradeResultBySerialField = {}
#业务功能码
CSgitFtdcRspQueryTradeResultBySerialField["TradeCode"] = "string"
#银行代码
CSgitFtdcRspQueryTradeResultBySerialField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcRspQueryTradeResultBySerialField["BankBranchID"] = "string"
#期商代码
CSgitFtdcRspQueryTradeResultBySerialField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcRspQueryTradeResultBySerialField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcRspQueryTradeResultBySerialField["TradeDate"] = "string"
#交易时间
CSgitFtdcRspQueryTradeResultBySerialField["TradeTime"] = "string"
#银行流水号
CSgitFtdcRspQueryTradeResultBySerialField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcRspQueryTradeResultBySerialField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcRspQueryTradeResultBySerialField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcRspQueryTradeResultBySerialField["LastFragment"] = "char"
#会话号
CSgitFtdcRspQueryTradeResultBySerialField["SessionID"] = "int"
#错误代码
CSgitFtdcRspQueryTradeResultBySerialField["ErrorID"] = "int"
#错误信息
CSgitFtdcRspQueryTradeResultBySerialField["ErrorMsg"] = "string"
#流水号
CSgitFtdcRspQueryTradeResultBySerialField["Reference"] = "int"
#本流水号发布者的机构类型
CSgitFtdcRspQueryTradeResultBySerialField["RefrenceIssureType"] = "char"
#本流水号发布者机构编码
CSgitFtdcRspQueryTradeResultBySerialField["RefrenceIssure"] = "string"
#原始返回代码
CSgitFtdcRspQueryTradeResultBySerialField["OriginReturnCode"] = "string"
#原始返回码描述
CSgitFtdcRspQueryTradeResultBySerialField["OriginDescrInfoForReturnCode"] = "string"
#银行帐号
CSgitFtdcRspQueryTradeResultBySerialField["BankAccount"] = "string"
#银行密码
CSgitFtdcRspQueryTradeResultBySerialField["BankPassWord"] = "string"
#投资者帐号
CSgitFtdcRspQueryTradeResultBySerialField["AccountID"] = "string"
#期货密码
CSgitFtdcRspQueryTradeResultBySerialField["Password"] = "string"
#币种代码
CSgitFtdcRspQueryTradeResultBySerialField["CurrencyID"] = "string"
#转帐金额
CSgitFtdcRspQueryTradeResultBySerialField["TradeAmount"] = "float"
#摘要
CSgitFtdcRspQueryTradeResultBySerialField["Digest"] = "string"
structDict['CSgitFtdcRspQueryTradeResultBySerialField'] = CSgitFtdcRspQueryTradeResultBySerialField


#日终文件就绪请求
CSgitFtdcReqDayEndFileReadyField = {}
#业务功能码
CSgitFtdcReqDayEndFileReadyField["TradeCode"] = "string"
#银行代码
CSgitFtdcReqDayEndFileReadyField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcReqDayEndFileReadyField["BankBranchID"] = "string"
#期商代码
CSgitFtdcReqDayEndFileReadyField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcReqDayEndFileReadyField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcReqDayEndFileReadyField["TradeDate"] = "string"
#交易时间
CSgitFtdcReqDayEndFileReadyField["TradeTime"] = "string"
#银行流水号
CSgitFtdcReqDayEndFileReadyField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcReqDayEndFileReadyField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcReqDayEndFileReadyField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcReqDayEndFileReadyField["LastFragment"] = "char"
#会话号
CSgitFtdcReqDayEndFileReadyField["SessionID"] = "int"
#文件业务功能
CSgitFtdcReqDayEndFileReadyField["FileBusinessCode"] = "char"
#摘要
CSgitFtdcReqDayEndFileReadyField["Digest"] = "string"
structDict['CSgitFtdcReqDayEndFileReadyField'] = CSgitFtdcReqDayEndFileReadyField


#返回结果
CSgitFtdcReturnResultField = {}
#返回代码
CSgitFtdcReturnResultField["ReturnCode"] = "string"
#返回码描述
CSgitFtdcReturnResultField["DescrInfoForReturnCode"] = "string"
structDict['CSgitFtdcReturnResultField'] = CSgitFtdcReturnResultField


#验证期货资金密码
CSgitFtdcVerifyFuturePasswordField = {}
#业务功能码
CSgitFtdcVerifyFuturePasswordField["TradeCode"] = "string"
#银行代码
CSgitFtdcVerifyFuturePasswordField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcVerifyFuturePasswordField["BankBranchID"] = "string"
#期商代码
CSgitFtdcVerifyFuturePasswordField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcVerifyFuturePasswordField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcVerifyFuturePasswordField["TradeDate"] = "string"
#交易时间
CSgitFtdcVerifyFuturePasswordField["TradeTime"] = "string"
#银行流水号
CSgitFtdcVerifyFuturePasswordField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcVerifyFuturePasswordField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcVerifyFuturePasswordField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcVerifyFuturePasswordField["LastFragment"] = "char"
#会话号
CSgitFtdcVerifyFuturePasswordField["SessionID"] = "int"
#投资者帐号
CSgitFtdcVerifyFuturePasswordField["AccountID"] = "string"
#期货密码
CSgitFtdcVerifyFuturePasswordField["Password"] = "string"
#银行帐号
CSgitFtdcVerifyFuturePasswordField["BankAccount"] = "string"
#银行密码
CSgitFtdcVerifyFuturePasswordField["BankPassWord"] = "string"
#安装编号
CSgitFtdcVerifyFuturePasswordField["InstallID"] = "int"
#交易ID
CSgitFtdcVerifyFuturePasswordField["TID"] = "int"
structDict['CSgitFtdcVerifyFuturePasswordField'] = CSgitFtdcVerifyFuturePasswordField


#验证客户信息
CSgitFtdcVerifyCustInfoField = {}
#客户姓名
CSgitFtdcVerifyCustInfoField["CustomerName"] = "string"
#证件类型
CSgitFtdcVerifyCustInfoField["IdCardType"] = "char"
#证件号码
CSgitFtdcVerifyCustInfoField["IdentifiedCardNo"] = "string"
#客户类型
CSgitFtdcVerifyCustInfoField["CustType"] = "char"
structDict['CSgitFtdcVerifyCustInfoField'] = CSgitFtdcVerifyCustInfoField


#验证期货资金密码和客户信息
CSgitFtdcVerifyFuturePasswordAndCustInfoField = {}
#客户姓名
CSgitFtdcVerifyFuturePasswordAndCustInfoField["CustomerName"] = "string"
#证件类型
CSgitFtdcVerifyFuturePasswordAndCustInfoField["IdCardType"] = "char"
#证件号码
CSgitFtdcVerifyFuturePasswordAndCustInfoField["IdentifiedCardNo"] = "string"
#客户类型
CSgitFtdcVerifyFuturePasswordAndCustInfoField["CustType"] = "char"
#投资者帐号
CSgitFtdcVerifyFuturePasswordAndCustInfoField["AccountID"] = "string"
#期货密码
CSgitFtdcVerifyFuturePasswordAndCustInfoField["Password"] = "string"
structDict['CSgitFtdcVerifyFuturePasswordAndCustInfoField'] = CSgitFtdcVerifyFuturePasswordAndCustInfoField


#验证期货资金密码和客户信息
CSgitFtdcDepositResultInformField = {}
#出入金流水号，该流水号为银期报盘返回的流水号
CSgitFtdcDepositResultInformField["DepositSeqNo"] = "string"
#经纪公司代码
CSgitFtdcDepositResultInformField["BrokerID"] = "string"
#投资者代码
CSgitFtdcDepositResultInformField["InvestorID"] = "string"
#入金金额
CSgitFtdcDepositResultInformField["Deposit"] = "float"
#请求编号
CSgitFtdcDepositResultInformField["RequestID"] = "int"
#返回代码
CSgitFtdcDepositResultInformField["ReturnCode"] = "string"
#返回码描述
CSgitFtdcDepositResultInformField["DescrInfoForReturnCode"] = "string"
structDict['CSgitFtdcDepositResultInformField'] = CSgitFtdcDepositResultInformField


#交易核心向银期报盘发出密钥同步请求
CSgitFtdcReqSyncKeyField = {}
#业务功能码
CSgitFtdcReqSyncKeyField["TradeCode"] = "string"
#银行代码
CSgitFtdcReqSyncKeyField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcReqSyncKeyField["BankBranchID"] = "string"
#期商代码
CSgitFtdcReqSyncKeyField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcReqSyncKeyField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcReqSyncKeyField["TradeDate"] = "string"
#交易时间
CSgitFtdcReqSyncKeyField["TradeTime"] = "string"
#银行流水号
CSgitFtdcReqSyncKeyField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcReqSyncKeyField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcReqSyncKeyField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcReqSyncKeyField["LastFragment"] = "char"
#会话号
CSgitFtdcReqSyncKeyField["SessionID"] = "int"
#安装编号
CSgitFtdcReqSyncKeyField["InstallID"] = "int"
#用户标识
CSgitFtdcReqSyncKeyField["UserID"] = "string"
#交易核心给银期报盘的消息
CSgitFtdcReqSyncKeyField["Message"] = "string"
#渠道标志
CSgitFtdcReqSyncKeyField["DeviceID"] = "string"
#期货公司银行编码
CSgitFtdcReqSyncKeyField["BrokerIDByBank"] = "string"
#交易柜员
CSgitFtdcReqSyncKeyField["OperNo"] = "string"
#请求编号
CSgitFtdcReqSyncKeyField["RequestID"] = "int"
#交易ID
CSgitFtdcReqSyncKeyField["TID"] = "int"
structDict['CSgitFtdcReqSyncKeyField'] = CSgitFtdcReqSyncKeyField


#交易核心向银期报盘发出密钥同步响应
CSgitFtdcRspSyncKeyField = {}
#业务功能码
CSgitFtdcRspSyncKeyField["TradeCode"] = "string"
#银行代码
CSgitFtdcRspSyncKeyField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcRspSyncKeyField["BankBranchID"] = "string"
#期商代码
CSgitFtdcRspSyncKeyField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcRspSyncKeyField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcRspSyncKeyField["TradeDate"] = "string"
#交易时间
CSgitFtdcRspSyncKeyField["TradeTime"] = "string"
#银行流水号
CSgitFtdcRspSyncKeyField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcRspSyncKeyField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcRspSyncKeyField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcRspSyncKeyField["LastFragment"] = "char"
#会话号
CSgitFtdcRspSyncKeyField["SessionID"] = "int"
#安装编号
CSgitFtdcRspSyncKeyField["InstallID"] = "int"
#用户标识
CSgitFtdcRspSyncKeyField["UserID"] = "string"
#交易核心给银期报盘的消息
CSgitFtdcRspSyncKeyField["Message"] = "string"
#渠道标志
CSgitFtdcRspSyncKeyField["DeviceID"] = "string"
#期货公司银行编码
CSgitFtdcRspSyncKeyField["BrokerIDByBank"] = "string"
#交易柜员
CSgitFtdcRspSyncKeyField["OperNo"] = "string"
#请求编号
CSgitFtdcRspSyncKeyField["RequestID"] = "int"
#交易ID
CSgitFtdcRspSyncKeyField["TID"] = "int"
#错误代码
CSgitFtdcRspSyncKeyField["ErrorID"] = "int"
#错误信息
CSgitFtdcRspSyncKeyField["ErrorMsg"] = "string"
structDict['CSgitFtdcRspSyncKeyField'] = CSgitFtdcRspSyncKeyField


#查询账户信息通知
CSgitFtdcNotifyQueryAccountField = {}
#业务功能码
CSgitFtdcNotifyQueryAccountField["TradeCode"] = "string"
#银行代码
CSgitFtdcNotifyQueryAccountField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcNotifyQueryAccountField["BankBranchID"] = "string"
#期商代码
CSgitFtdcNotifyQueryAccountField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcNotifyQueryAccountField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcNotifyQueryAccountField["TradeDate"] = "string"
#交易时间
CSgitFtdcNotifyQueryAccountField["TradeTime"] = "string"
#银行流水号
CSgitFtdcNotifyQueryAccountField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcNotifyQueryAccountField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcNotifyQueryAccountField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcNotifyQueryAccountField["LastFragment"] = "char"
#会话号
CSgitFtdcNotifyQueryAccountField["SessionID"] = "int"
#客户姓名
CSgitFtdcNotifyQueryAccountField["CustomerName"] = "string"
#证件类型
CSgitFtdcNotifyQueryAccountField["IdCardType"] = "char"
#证件号码
CSgitFtdcNotifyQueryAccountField["IdentifiedCardNo"] = "string"
#客户类型
CSgitFtdcNotifyQueryAccountField["CustType"] = "char"
#银行帐号
CSgitFtdcNotifyQueryAccountField["BankAccount"] = "string"
#银行密码
CSgitFtdcNotifyQueryAccountField["BankPassWord"] = "string"
#投资者帐号
CSgitFtdcNotifyQueryAccountField["AccountID"] = "string"
#期货密码
CSgitFtdcNotifyQueryAccountField["Password"] = "string"
#期货公司流水号
CSgitFtdcNotifyQueryAccountField["FutureSerial"] = "int"
#安装编号
CSgitFtdcNotifyQueryAccountField["InstallID"] = "int"
#用户标识
CSgitFtdcNotifyQueryAccountField["UserID"] = "string"
#验证客户证件号码标志
CSgitFtdcNotifyQueryAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CSgitFtdcNotifyQueryAccountField["CurrencyID"] = "string"
#摘要
CSgitFtdcNotifyQueryAccountField["Digest"] = "string"
#银行帐号类型
CSgitFtdcNotifyQueryAccountField["BankAccType"] = "char"
#渠道标志
CSgitFtdcNotifyQueryAccountField["DeviceID"] = "string"
#期货单位帐号类型
CSgitFtdcNotifyQueryAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CSgitFtdcNotifyQueryAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CSgitFtdcNotifyQueryAccountField["BankSecuAcc"] = "string"
#银行密码标志
CSgitFtdcNotifyQueryAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CSgitFtdcNotifyQueryAccountField["SecuPwdFlag"] = "char"
#交易柜员
CSgitFtdcNotifyQueryAccountField["OperNo"] = "string"
#请求编号
CSgitFtdcNotifyQueryAccountField["RequestID"] = "int"
#交易ID
CSgitFtdcNotifyQueryAccountField["TID"] = "int"
#银行可用金额
CSgitFtdcNotifyQueryAccountField["BankUseAmount"] = "float"
#银行可取金额
CSgitFtdcNotifyQueryAccountField["BankFetchAmount"] = "float"
#错误代码
CSgitFtdcNotifyQueryAccountField["ErrorID"] = "int"
#错误信息
CSgitFtdcNotifyQueryAccountField["ErrorMsg"] = "string"
structDict['CSgitFtdcNotifyQueryAccountField'] = CSgitFtdcNotifyQueryAccountField


#银期转账交易流水表
CSgitFtdcTransferSerialField = {}
#平台流水号
CSgitFtdcTransferSerialField["PlateSerial"] = "int"
#交易发起方日期
CSgitFtdcTransferSerialField["TradeDate"] = "string"
#交易日期
CSgitFtdcTransferSerialField["TradingDay"] = "string"
#交易时间
CSgitFtdcTransferSerialField["TradeTime"] = "string"
#交易代码
CSgitFtdcTransferSerialField["TradeCode"] = "string"
#会话编号
CSgitFtdcTransferSerialField["SessionID"] = "int"
#银行编码
CSgitFtdcTransferSerialField["BankID"] = "string"
#银行分支机构编码
CSgitFtdcTransferSerialField["BankBranchID"] = "string"
#银行帐号类型
CSgitFtdcTransferSerialField["BankAccType"] = "char"
#银行帐号
CSgitFtdcTransferSerialField["BankAccount"] = "string"
#银行流水号
CSgitFtdcTransferSerialField["BankSerial"] = "string"
#期货公司编码
CSgitFtdcTransferSerialField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcTransferSerialField["BrokerBranchID"] = "string"
#期货公司帐号类型
CSgitFtdcTransferSerialField["FutureAccType"] = "char"
#投资者帐号
CSgitFtdcTransferSerialField["AccountID"] = "string"
#投资者代码
CSgitFtdcTransferSerialField["InvestorID"] = "string"
#期货公司流水号
CSgitFtdcTransferSerialField["FutureSerial"] = "int"
#证件类型
CSgitFtdcTransferSerialField["IdCardType"] = "char"
#证件号码
CSgitFtdcTransferSerialField["IdentifiedCardNo"] = "string"
#币种代码
CSgitFtdcTransferSerialField["CurrencyID"] = "string"
#交易金额
CSgitFtdcTransferSerialField["TradeAmount"] = "float"
#应收客户费用
CSgitFtdcTransferSerialField["CustFee"] = "float"
#应收期货公司费用
CSgitFtdcTransferSerialField["BrokerFee"] = "float"
#有效标志
CSgitFtdcTransferSerialField["AvailabilityFlag"] = "char"
#操作员
CSgitFtdcTransferSerialField["OperatorCode"] = "string"
#新银行帐号
CSgitFtdcTransferSerialField["BankNewAccount"] = "string"
#错误代码
CSgitFtdcTransferSerialField["ErrorID"] = "int"
#错误信息
CSgitFtdcTransferSerialField["ErrorMsg"] = "string"
structDict['CSgitFtdcTransferSerialField'] = CSgitFtdcTransferSerialField


#请求查询转帐流水
CSgitFtdcQryTransferSerialField = {}
#经纪公司代码
CSgitFtdcQryTransferSerialField["BrokerID"] = "string"
#投资者帐号
CSgitFtdcQryTransferSerialField["AccountID"] = "string"
#银行编码
CSgitFtdcQryTransferSerialField["BankID"] = "string"
structDict['CSgitFtdcQryTransferSerialField'] = CSgitFtdcQryTransferSerialField


#期商签到通知
CSgitFtdcNotifyFutureSignInField = {}
#业务功能码
CSgitFtdcNotifyFutureSignInField["TradeCode"] = "string"
#银行代码
CSgitFtdcNotifyFutureSignInField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcNotifyFutureSignInField["BankBranchID"] = "string"
#期商代码
CSgitFtdcNotifyFutureSignInField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcNotifyFutureSignInField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcNotifyFutureSignInField["TradeDate"] = "string"
#交易时间
CSgitFtdcNotifyFutureSignInField["TradeTime"] = "string"
#银行流水号
CSgitFtdcNotifyFutureSignInField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcNotifyFutureSignInField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcNotifyFutureSignInField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcNotifyFutureSignInField["LastFragment"] = "char"
#会话号
CSgitFtdcNotifyFutureSignInField["SessionID"] = "int"
#安装编号
CSgitFtdcNotifyFutureSignInField["InstallID"] = "int"
#用户标识
CSgitFtdcNotifyFutureSignInField["UserID"] = "string"
#摘要
CSgitFtdcNotifyFutureSignInField["Digest"] = "string"
#币种代码
CSgitFtdcNotifyFutureSignInField["CurrencyID"] = "string"
#渠道标志
CSgitFtdcNotifyFutureSignInField["DeviceID"] = "string"
#期货公司银行编码
CSgitFtdcNotifyFutureSignInField["BrokerIDByBank"] = "string"
#交易柜员
CSgitFtdcNotifyFutureSignInField["OperNo"] = "string"
#请求编号
CSgitFtdcNotifyFutureSignInField["RequestID"] = "int"
#交易ID
CSgitFtdcNotifyFutureSignInField["TID"] = "int"
#错误代码
CSgitFtdcNotifyFutureSignInField["ErrorID"] = "int"
#错误信息
CSgitFtdcNotifyFutureSignInField["ErrorMsg"] = "string"
#PIN密钥
CSgitFtdcNotifyFutureSignInField["PinKey"] = "string"
#MAC密钥
CSgitFtdcNotifyFutureSignInField["MacKey"] = "string"
structDict['CSgitFtdcNotifyFutureSignInField'] = CSgitFtdcNotifyFutureSignInField


#期商签退通知
CSgitFtdcNotifyFutureSignOutField = {}
#业务功能码
CSgitFtdcNotifyFutureSignOutField["TradeCode"] = "string"
#银行代码
CSgitFtdcNotifyFutureSignOutField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcNotifyFutureSignOutField["BankBranchID"] = "string"
#期商代码
CSgitFtdcNotifyFutureSignOutField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcNotifyFutureSignOutField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcNotifyFutureSignOutField["TradeDate"] = "string"
#交易时间
CSgitFtdcNotifyFutureSignOutField["TradeTime"] = "string"
#银行流水号
CSgitFtdcNotifyFutureSignOutField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcNotifyFutureSignOutField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcNotifyFutureSignOutField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcNotifyFutureSignOutField["LastFragment"] = "char"
#会话号
CSgitFtdcNotifyFutureSignOutField["SessionID"] = "int"
#安装编号
CSgitFtdcNotifyFutureSignOutField["InstallID"] = "int"
#用户标识
CSgitFtdcNotifyFutureSignOutField["UserID"] = "string"
#摘要
CSgitFtdcNotifyFutureSignOutField["Digest"] = "string"
#币种代码
CSgitFtdcNotifyFutureSignOutField["CurrencyID"] = "string"
#渠道标志
CSgitFtdcNotifyFutureSignOutField["DeviceID"] = "string"
#期货公司银行编码
CSgitFtdcNotifyFutureSignOutField["BrokerIDByBank"] = "string"
#交易柜员
CSgitFtdcNotifyFutureSignOutField["OperNo"] = "string"
#请求编号
CSgitFtdcNotifyFutureSignOutField["RequestID"] = "int"
#交易ID
CSgitFtdcNotifyFutureSignOutField["TID"] = "int"
#错误代码
CSgitFtdcNotifyFutureSignOutField["ErrorID"] = "int"
#错误信息
CSgitFtdcNotifyFutureSignOutField["ErrorMsg"] = "string"
structDict['CSgitFtdcNotifyFutureSignOutField'] = CSgitFtdcNotifyFutureSignOutField


#交易核心向银期报盘发出密钥同步处理结果的通知
CSgitFtdcNotifySyncKeyField = {}
#业务功能码
CSgitFtdcNotifySyncKeyField["TradeCode"] = "string"
#银行代码
CSgitFtdcNotifySyncKeyField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcNotifySyncKeyField["BankBranchID"] = "string"
#期商代码
CSgitFtdcNotifySyncKeyField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcNotifySyncKeyField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcNotifySyncKeyField["TradeDate"] = "string"
#交易时间
CSgitFtdcNotifySyncKeyField["TradeTime"] = "string"
#银行流水号
CSgitFtdcNotifySyncKeyField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcNotifySyncKeyField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcNotifySyncKeyField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcNotifySyncKeyField["LastFragment"] = "char"
#会话号
CSgitFtdcNotifySyncKeyField["SessionID"] = "int"
#安装编号
CSgitFtdcNotifySyncKeyField["InstallID"] = "int"
#用户标识
CSgitFtdcNotifySyncKeyField["UserID"] = "string"
#交易核心给银期报盘的消息
CSgitFtdcNotifySyncKeyField["Message"] = "string"
#渠道标志
CSgitFtdcNotifySyncKeyField["DeviceID"] = "string"
#期货公司银行编码
CSgitFtdcNotifySyncKeyField["BrokerIDByBank"] = "string"
#交易柜员
CSgitFtdcNotifySyncKeyField["OperNo"] = "string"
#请求编号
CSgitFtdcNotifySyncKeyField["RequestID"] = "int"
#交易ID
CSgitFtdcNotifySyncKeyField["TID"] = "int"
#错误代码
CSgitFtdcNotifySyncKeyField["ErrorID"] = "int"
#错误信息
CSgitFtdcNotifySyncKeyField["ErrorMsg"] = "string"
structDict['CSgitFtdcNotifySyncKeyField'] = CSgitFtdcNotifySyncKeyField


#请求查询银期签约关系
CSgitFtdcQryAccountregisterField = {}
#经纪公司代码
CSgitFtdcQryAccountregisterField["BrokerID"] = "string"
#投资者帐号
CSgitFtdcQryAccountregisterField["AccountID"] = "string"
#银行编码
CSgitFtdcQryAccountregisterField["BankID"] = "string"
structDict['CSgitFtdcQryAccountregisterField'] = CSgitFtdcQryAccountregisterField


#客户开销户信息表
CSgitFtdcAccountregisterField = {}
#交易日期
CSgitFtdcAccountregisterField["TradeDay"] = "string"
#银行编码
CSgitFtdcAccountregisterField["BankID"] = "string"
#银行分支机构编码
CSgitFtdcAccountregisterField["BankBranchID"] = "string"
#银行帐号
CSgitFtdcAccountregisterField["BankAccount"] = "string"
#期货公司编码
CSgitFtdcAccountregisterField["BrokerID"] = "string"
#期货公司分支机构编码
CSgitFtdcAccountregisterField["BrokerBranchID"] = "string"
#投资者帐号
CSgitFtdcAccountregisterField["AccountID"] = "string"
#证件类型
CSgitFtdcAccountregisterField["IdCardType"] = "char"
#证件号码
CSgitFtdcAccountregisterField["IdentifiedCardNo"] = "string"
#客户姓名
CSgitFtdcAccountregisterField["CustomerName"] = "string"
#币种代码
CSgitFtdcAccountregisterField["CurrencyID"] = "string"
#开销户类别
CSgitFtdcAccountregisterField["OpenOrDestroy"] = "char"
#签约日期
CSgitFtdcAccountregisterField["RegDate"] = "string"
#解约日期
CSgitFtdcAccountregisterField["OutDate"] = "string"
#交易ID
CSgitFtdcAccountregisterField["TID"] = "int"
#客户类型
CSgitFtdcAccountregisterField["CustType"] = "char"
#银行帐号类型
CSgitFtdcAccountregisterField["BankAccType"] = "char"
structDict['CSgitFtdcAccountregisterField'] = CSgitFtdcAccountregisterField


#银期开户信息
CSgitFtdcOpenAccountField = {}
#业务功能码
CSgitFtdcOpenAccountField["TradeCode"] = "string"
#银行代码
CSgitFtdcOpenAccountField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcOpenAccountField["BankBranchID"] = "string"
#期商代码
CSgitFtdcOpenAccountField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcOpenAccountField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcOpenAccountField["TradeDate"] = "string"
#交易时间
CSgitFtdcOpenAccountField["TradeTime"] = "string"
#银行流水号
CSgitFtdcOpenAccountField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcOpenAccountField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcOpenAccountField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcOpenAccountField["LastFragment"] = "char"
#会话号
CSgitFtdcOpenAccountField["SessionID"] = "int"
#客户姓名
CSgitFtdcOpenAccountField["CustomerName"] = "string"
#证件类型
CSgitFtdcOpenAccountField["IdCardType"] = "char"
#证件号码
CSgitFtdcOpenAccountField["IdentifiedCardNo"] = "string"
#性别
CSgitFtdcOpenAccountField["Gender"] = "char"
#国家代码
CSgitFtdcOpenAccountField["CountryCode"] = "string"
#客户类型
CSgitFtdcOpenAccountField["CustType"] = "char"
#地址
CSgitFtdcOpenAccountField["Address"] = "string"
#邮编
CSgitFtdcOpenAccountField["ZipCode"] = "string"
#电话号码
CSgitFtdcOpenAccountField["Telephone"] = "string"
#手机
CSgitFtdcOpenAccountField["MobilePhone"] = "string"
#传真
CSgitFtdcOpenAccountField["Fax"] = "string"
#电子邮件
CSgitFtdcOpenAccountField["EMail"] = "string"
#资金账户状态
CSgitFtdcOpenAccountField["MoneyAccountStatus"] = "char"
#银行帐号
CSgitFtdcOpenAccountField["BankAccount"] = "string"
#银行密码
CSgitFtdcOpenAccountField["BankPassWord"] = "string"
#投资者帐号
CSgitFtdcOpenAccountField["AccountID"] = "string"
#期货密码
CSgitFtdcOpenAccountField["Password"] = "string"
#安装编号
CSgitFtdcOpenAccountField["InstallID"] = "int"
#验证客户证件号码标志
CSgitFtdcOpenAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CSgitFtdcOpenAccountField["CurrencyID"] = "string"
#汇钞标志
CSgitFtdcOpenAccountField["CashExchangeCode"] = "char"
#摘要
CSgitFtdcOpenAccountField["Digest"] = "string"
#银行帐号类型
CSgitFtdcOpenAccountField["BankAccType"] = "char"
#渠道标志
CSgitFtdcOpenAccountField["DeviceID"] = "string"
#期货单位帐号类型
CSgitFtdcOpenAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CSgitFtdcOpenAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CSgitFtdcOpenAccountField["BankSecuAcc"] = "string"
#银行密码标志
CSgitFtdcOpenAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CSgitFtdcOpenAccountField["SecuPwdFlag"] = "char"
#交易柜员
CSgitFtdcOpenAccountField["OperNo"] = "string"
#交易ID
CSgitFtdcOpenAccountField["TID"] = "int"
#错误代码
CSgitFtdcOpenAccountField["ErrorID"] = "int"
#错误信息
CSgitFtdcOpenAccountField["ErrorMsg"] = "string"
structDict['CSgitFtdcOpenAccountField'] = CSgitFtdcOpenAccountField


#银期销户信息
CSgitFtdcCancelAccountField = {}
#业务功能码
CSgitFtdcCancelAccountField["TradeCode"] = "string"
#银行代码
CSgitFtdcCancelAccountField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcCancelAccountField["BankBranchID"] = "string"
#期商代码
CSgitFtdcCancelAccountField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcCancelAccountField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcCancelAccountField["TradeDate"] = "string"
#交易时间
CSgitFtdcCancelAccountField["TradeTime"] = "string"
#银行流水号
CSgitFtdcCancelAccountField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcCancelAccountField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcCancelAccountField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcCancelAccountField["LastFragment"] = "char"
#会话号
CSgitFtdcCancelAccountField["SessionID"] = "int"
#客户姓名
CSgitFtdcCancelAccountField["CustomerName"] = "string"
#证件类型
CSgitFtdcCancelAccountField["IdCardType"] = "char"
#证件号码
CSgitFtdcCancelAccountField["IdentifiedCardNo"] = "string"
#性别
CSgitFtdcCancelAccountField["Gender"] = "char"
#国家代码
CSgitFtdcCancelAccountField["CountryCode"] = "string"
#客户类型
CSgitFtdcCancelAccountField["CustType"] = "char"
#地址
CSgitFtdcCancelAccountField["Address"] = "string"
#邮编
CSgitFtdcCancelAccountField["ZipCode"] = "string"
#电话号码
CSgitFtdcCancelAccountField["Telephone"] = "string"
#手机
CSgitFtdcCancelAccountField["MobilePhone"] = "string"
#传真
CSgitFtdcCancelAccountField["Fax"] = "string"
#电子邮件
CSgitFtdcCancelAccountField["EMail"] = "string"
#资金账户状态
CSgitFtdcCancelAccountField["MoneyAccountStatus"] = "char"
#银行帐号
CSgitFtdcCancelAccountField["BankAccount"] = "string"
#银行密码
CSgitFtdcCancelAccountField["BankPassWord"] = "string"
#投资者帐号
CSgitFtdcCancelAccountField["AccountID"] = "string"
#期货密码
CSgitFtdcCancelAccountField["Password"] = "string"
#安装编号
CSgitFtdcCancelAccountField["InstallID"] = "int"
#验证客户证件号码标志
CSgitFtdcCancelAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CSgitFtdcCancelAccountField["CurrencyID"] = "string"
#汇钞标志
CSgitFtdcCancelAccountField["CashExchangeCode"] = "char"
#摘要
CSgitFtdcCancelAccountField["Digest"] = "string"
#银行帐号类型
CSgitFtdcCancelAccountField["BankAccType"] = "char"
#渠道标志
CSgitFtdcCancelAccountField["DeviceID"] = "string"
#期货单位帐号类型
CSgitFtdcCancelAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CSgitFtdcCancelAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CSgitFtdcCancelAccountField["BankSecuAcc"] = "string"
#银行密码标志
CSgitFtdcCancelAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CSgitFtdcCancelAccountField["SecuPwdFlag"] = "char"
#交易柜员
CSgitFtdcCancelAccountField["OperNo"] = "string"
#交易ID
CSgitFtdcCancelAccountField["TID"] = "int"
#错误代码
CSgitFtdcCancelAccountField["ErrorID"] = "int"
#错误信息
CSgitFtdcCancelAccountField["ErrorMsg"] = "string"
structDict['CSgitFtdcCancelAccountField'] = CSgitFtdcCancelAccountField


#银期变更银行账号信息
CSgitFtdcChangeAccountField = {}
#业务功能码
CSgitFtdcChangeAccountField["TradeCode"] = "string"
#银行代码
CSgitFtdcChangeAccountField["BankID"] = "string"
#银行分支机构代码
CSgitFtdcChangeAccountField["BankBranchID"] = "string"
#期商代码
CSgitFtdcChangeAccountField["BrokerID"] = "string"
#期商分支机构代码
CSgitFtdcChangeAccountField["BrokerBranchID"] = "string"
#交易日期
CSgitFtdcChangeAccountField["TradeDate"] = "string"
#交易时间
CSgitFtdcChangeAccountField["TradeTime"] = "string"
#银行流水号
CSgitFtdcChangeAccountField["BankSerial"] = "string"
#交易系统日期 
CSgitFtdcChangeAccountField["TradingDay"] = "string"
#银期平台消息流水号
CSgitFtdcChangeAccountField["PlateSerial"] = "int"
#最后分片标志
CSgitFtdcChangeAccountField["LastFragment"] = "char"
#会话号
CSgitFtdcChangeAccountField["SessionID"] = "int"
#客户姓名
CSgitFtdcChangeAccountField["CustomerName"] = "string"
#证件类型
CSgitFtdcChangeAccountField["IdCardType"] = "char"
#证件号码
CSgitFtdcChangeAccountField["IdentifiedCardNo"] = "string"
#性别
CSgitFtdcChangeAccountField["Gender"] = "char"
#国家代码
CSgitFtdcChangeAccountField["CountryCode"] = "string"
#客户类型
CSgitFtdcChangeAccountField["CustType"] = "char"
#地址
CSgitFtdcChangeAccountField["Address"] = "string"
#邮编
CSgitFtdcChangeAccountField["ZipCode"] = "string"
#电话号码
CSgitFtdcChangeAccountField["Telephone"] = "string"
#手机
CSgitFtdcChangeAccountField["MobilePhone"] = "string"
#传真
CSgitFtdcChangeAccountField["Fax"] = "string"
#电子邮件
CSgitFtdcChangeAccountField["EMail"] = "string"
#资金账户状态
CSgitFtdcChangeAccountField["MoneyAccountStatus"] = "char"
#银行帐号
CSgitFtdcChangeAccountField["BankAccount"] = "string"
#银行密码
CSgitFtdcChangeAccountField["BankPassWord"] = "string"
#新银行帐号
CSgitFtdcChangeAccountField["NewBankAccount"] = "string"
#新银行密码
CSgitFtdcChangeAccountField["NewBankPassWord"] = "string"
#投资者帐号
CSgitFtdcChangeAccountField["AccountID"] = "string"
#期货密码
CSgitFtdcChangeAccountField["Password"] = "string"
#银行帐号类型
CSgitFtdcChangeAccountField["BankAccType"] = "char"
#安装编号
CSgitFtdcChangeAccountField["InstallID"] = "int"
#验证客户证件号码标志
CSgitFtdcChangeAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CSgitFtdcChangeAccountField["CurrencyID"] = "string"
#期货公司银行编码
CSgitFtdcChangeAccountField["BrokerIDByBank"] = "string"
#银行密码标志
CSgitFtdcChangeAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CSgitFtdcChangeAccountField["SecuPwdFlag"] = "char"
#交易ID
CSgitFtdcChangeAccountField["TID"] = "int"
#摘要
CSgitFtdcChangeAccountField["Digest"] = "string"
#错误代码
CSgitFtdcChangeAccountField["ErrorID"] = "int"
#错误信息
CSgitFtdcChangeAccountField["ErrorMsg"] = "string"
structDict['CSgitFtdcChangeAccountField'] = CSgitFtdcChangeAccountField


#灾备中心交易权限
CSgitFtdcUserRightsAssignField = {}
#应用单元代码
CSgitFtdcUserRightsAssignField["BrokerID"] = "string"
#用户代码
CSgitFtdcUserRightsAssignField["UserID"] = "string"
#交易中心代码
CSgitFtdcUserRightsAssignField["DRIdentityID"] = "int"
structDict['CSgitFtdcUserRightsAssignField'] = CSgitFtdcUserRightsAssignField


#经济公司是否有在本标示的交易权限
CSgitFtdcBrokerUserRightAssignField = {}
#应用单元代码
CSgitFtdcBrokerUserRightAssignField["BrokerID"] = "string"
#交易中心代码
CSgitFtdcBrokerUserRightAssignField["DRIdentityID"] = "int"
#能否交易
CSgitFtdcBrokerUserRightAssignField["Tradeable"] = "int"
structDict['CSgitFtdcBrokerUserRightAssignField'] = CSgitFtdcBrokerUserRightAssignField


#灾备交易转换报文
CSgitFtdcDRTransferField = {}
#原交易中心代码
CSgitFtdcDRTransferField["OrigDRIdentityID"] = "int"
#目标交易中心代码
CSgitFtdcDRTransferField["DestDRIdentityID"] = "int"
#原应用单元代码
CSgitFtdcDRTransferField["OrigBrokerID"] = "string"
#目标易用单元代码
CSgitFtdcDRTransferField["DestBrokerID"] = "string"
structDict['CSgitFtdcDRTransferField'] = CSgitFtdcDRTransferField



CSgitMBLQuotReq = {}
CSgitMBLQuotReq["StartContractID"] = "string"
CSgitMBLQuotReq["EndContractID"] = "string"
CSgitMBLQuotReq["BsFlag"] = "char"
structDict['CSgitMBLQuotReq'] = CSgitMBLQuotReq



CSgitMBLQuotData = {}
CSgitMBLQuotData["ContractID"] = "string"
CSgitMBLQuotData["BsFlag"] = "char"
CSgitMBLQuotData["Price"] = "float"
CSgitMBLQuotData["Qty"] = "int"
structDict['CSgitMBLQuotData'] = CSgitMBLQuotData



CSgitSubQuotField = {}
CSgitSubQuotField["ContractID"] = "string"
structDict['CSgitSubQuotField'] = CSgitSubQuotField



