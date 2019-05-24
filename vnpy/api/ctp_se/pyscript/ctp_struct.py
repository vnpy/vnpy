# encoding: UTF-8

structDict = {}

#//////////////////////////////////////////////////////////////////////
#@system 新一代交易所系统
#@company 上海期货信息技术有限公司
#@file ThostFtdcUserApiStruct.h
#@brief 定义了客户端接口使用的业务数据结构
#@history 

#//////////////////////////////////////////////////////////////////////










#信息分发
CThostFtdcDisseminationField = {}
#序列系列号
CThostFtdcDisseminationField["SequenceSeries"] = "int"
#序列号
CThostFtdcDisseminationField["SequenceNo"] = "int"
structDict['CThostFtdcDisseminationField'] = CThostFtdcDisseminationField


#用户登录请求
CThostFtdcReqUserLoginField = {}
#交易日
CThostFtdcReqUserLoginField["TradingDay"] = "string"
#经纪公司代码
CThostFtdcReqUserLoginField["BrokerID"] = "string"
#用户代码
CThostFtdcReqUserLoginField["UserID"] = "string"
#密码
CThostFtdcReqUserLoginField["Password"] = "string"
#用户端产品信息
CThostFtdcReqUserLoginField["UserProductInfo"] = "string"
#接口端产品信息
CThostFtdcReqUserLoginField["InterfaceProductInfo"] = "string"
#协议信息
CThostFtdcReqUserLoginField["ProtocolInfo"] = "string"
#Mac地址
CThostFtdcReqUserLoginField["MacAddress"] = "string"
#动态密码
CThostFtdcReqUserLoginField["OneTimePassword"] = "string"
#终端IP地址
CThostFtdcReqUserLoginField["ClientIPAddress"] = "string"
#登录备注
CThostFtdcReqUserLoginField["LoginRemark"] = "string"
#终端IP端口
CThostFtdcReqUserLoginField["ClientIPPort"] = "int"
structDict['CThostFtdcReqUserLoginField'] = CThostFtdcReqUserLoginField


#用户登录应答
CThostFtdcRspUserLoginField = {}
#交易日
CThostFtdcRspUserLoginField["TradingDay"] = "string"
#登录成功时间
CThostFtdcRspUserLoginField["LoginTime"] = "string"
#经纪公司代码
CThostFtdcRspUserLoginField["BrokerID"] = "string"
#用户代码
CThostFtdcRspUserLoginField["UserID"] = "string"
#交易系统名称
CThostFtdcRspUserLoginField["SystemName"] = "string"
#前置编号
CThostFtdcRspUserLoginField["FrontID"] = "int"
#会话编号
CThostFtdcRspUserLoginField["SessionID"] = "int"
#最大报单引用
CThostFtdcRspUserLoginField["MaxOrderRef"] = "string"
#上期所时间
CThostFtdcRspUserLoginField["SHFETime"] = "string"
#大商所时间
CThostFtdcRspUserLoginField["DCETime"] = "string"
#郑商所时间
CThostFtdcRspUserLoginField["CZCETime"] = "string"
#中金所时间
CThostFtdcRspUserLoginField["FFEXTime"] = "string"
#能源中心时间
CThostFtdcRspUserLoginField["INETime"] = "string"
structDict['CThostFtdcRspUserLoginField'] = CThostFtdcRspUserLoginField


#用户登出请求
CThostFtdcUserLogoutField = {}
#经纪公司代码
CThostFtdcUserLogoutField["BrokerID"] = "string"
#用户代码
CThostFtdcUserLogoutField["UserID"] = "string"
structDict['CThostFtdcUserLogoutField'] = CThostFtdcUserLogoutField


#强制交易员退出
CThostFtdcForceUserLogoutField = {}
#经纪公司代码
CThostFtdcForceUserLogoutField["BrokerID"] = "string"
#用户代码
CThostFtdcForceUserLogoutField["UserID"] = "string"
structDict['CThostFtdcForceUserLogoutField'] = CThostFtdcForceUserLogoutField


#客户端认证请求
CThostFtdcReqAuthenticateField = {}
#经纪公司代码
CThostFtdcReqAuthenticateField["BrokerID"] = "string"
#用户代码
CThostFtdcReqAuthenticateField["UserID"] = "string"
#用户端产品信息
CThostFtdcReqAuthenticateField["UserProductInfo"] = "string"
#认证码
CThostFtdcReqAuthenticateField["AuthCode"] = "string"
#App代码
CThostFtdcReqAuthenticateField["AppID"] = "string"
structDict['CThostFtdcReqAuthenticateField'] = CThostFtdcReqAuthenticateField


#客户端认证响应
CThostFtdcRspAuthenticateField = {}
#经纪公司代码
CThostFtdcRspAuthenticateField["BrokerID"] = "string"
#用户代码
CThostFtdcRspAuthenticateField["UserID"] = "string"
#用户端产品信息
CThostFtdcRspAuthenticateField["UserProductInfo"] = "string"
#App代码
CThostFtdcRspAuthenticateField["AppID"] = "string"
#App类型
CThostFtdcRspAuthenticateField["AppType"] = "char"
structDict['CThostFtdcRspAuthenticateField'] = CThostFtdcRspAuthenticateField


#客户端认证信息
CThostFtdcAuthenticationInfoField = {}
#经纪公司代码
CThostFtdcAuthenticationInfoField["BrokerID"] = "string"
#用户代码
CThostFtdcAuthenticationInfoField["UserID"] = "string"
#用户端产品信息
CThostFtdcAuthenticationInfoField["UserProductInfo"] = "string"
#认证信息
CThostFtdcAuthenticationInfoField["AuthInfo"] = "string"
#是否为认证结果
CThostFtdcAuthenticationInfoField["IsResult"] = "int"
#App代码
CThostFtdcAuthenticationInfoField["AppID"] = "string"
#App类型
CThostFtdcAuthenticationInfoField["AppType"] = "char"
structDict['CThostFtdcAuthenticationInfoField'] = CThostFtdcAuthenticationInfoField


#用户登录应答2
CThostFtdcRspUserLogin2Field = {}
#交易日
CThostFtdcRspUserLogin2Field["TradingDay"] = "string"
#登录成功时间
CThostFtdcRspUserLogin2Field["LoginTime"] = "string"
#经纪公司代码
CThostFtdcRspUserLogin2Field["BrokerID"] = "string"
#用户代码
CThostFtdcRspUserLogin2Field["UserID"] = "string"
#交易系统名称
CThostFtdcRspUserLogin2Field["SystemName"] = "string"
#前置编号
CThostFtdcRspUserLogin2Field["FrontID"] = "int"
#会话编号
CThostFtdcRspUserLogin2Field["SessionID"] = "int"
#最大报单引用
CThostFtdcRspUserLogin2Field["MaxOrderRef"] = "string"
#上期所时间
CThostFtdcRspUserLogin2Field["SHFETime"] = "string"
#大商所时间
CThostFtdcRspUserLogin2Field["DCETime"] = "string"
#郑商所时间
CThostFtdcRspUserLogin2Field["CZCETime"] = "string"
#中金所时间
CThostFtdcRspUserLogin2Field["FFEXTime"] = "string"
#能源中心时间
CThostFtdcRspUserLogin2Field["INETime"] = "string"
#随机串
CThostFtdcRspUserLogin2Field["RandomString"] = "string"
structDict['CThostFtdcRspUserLogin2Field'] = CThostFtdcRspUserLogin2Field


#银期转帐报文头
CThostFtdcTransferHeaderField = {}
#版本号，常量，1.0
CThostFtdcTransferHeaderField["Version"] = "string"
#交易代码，必填
CThostFtdcTransferHeaderField["TradeCode"] = "string"
#交易日期，必填，格式：yyyymmdd
CThostFtdcTransferHeaderField["TradeDate"] = "string"
#交易时间，必填，格式：hhmmss
CThostFtdcTransferHeaderField["TradeTime"] = "string"
#发起方流水号，N/A
CThostFtdcTransferHeaderField["TradeSerial"] = "string"
#期货公司代码，必填
CThostFtdcTransferHeaderField["FutureID"] = "string"
#银行代码，根据查询银行得到，必填
CThostFtdcTransferHeaderField["BankID"] = "string"
#银行分中心代码，根据查询银行得到，必填
CThostFtdcTransferHeaderField["BankBrchID"] = "string"
#操作员，N/A
CThostFtdcTransferHeaderField["OperNo"] = "string"
#交易设备类型，N/A
CThostFtdcTransferHeaderField["DeviceID"] = "string"
#记录数，N/A
CThostFtdcTransferHeaderField["RecordNum"] = "string"
#会话编号，N/A
CThostFtdcTransferHeaderField["SessionID"] = "int"
#请求编号，N/A
CThostFtdcTransferHeaderField["RequestID"] = "int"
structDict['CThostFtdcTransferHeaderField'] = CThostFtdcTransferHeaderField


#银行资金转期货请求，TradeCode=202001
CThostFtdcTransferBankToFutureReqField = {}
#期货资金账户
CThostFtdcTransferBankToFutureReqField["FutureAccount"] = "string"
#密码标志
CThostFtdcTransferBankToFutureReqField["FuturePwdFlag"] = "char"
#密码
CThostFtdcTransferBankToFutureReqField["FutureAccPwd"] = "string"
#转账金额
CThostFtdcTransferBankToFutureReqField["TradeAmt"] = "float"
#客户手续费
CThostFtdcTransferBankToFutureReqField["CustFee"] = "float"
#币种：RMB-人民币 USD-美圆 HKD-港元
CThostFtdcTransferBankToFutureReqField["CurrencyCode"] = "string"
structDict['CThostFtdcTransferBankToFutureReqField'] = CThostFtdcTransferBankToFutureReqField


#银行资金转期货请求响应
CThostFtdcTransferBankToFutureRspField = {}
#响应代码
CThostFtdcTransferBankToFutureRspField["RetCode"] = "string"
#响应信息
CThostFtdcTransferBankToFutureRspField["RetInfo"] = "string"
#资金账户
CThostFtdcTransferBankToFutureRspField["FutureAccount"] = "string"
#转帐金额
CThostFtdcTransferBankToFutureRspField["TradeAmt"] = "float"
#应收客户手续费
CThostFtdcTransferBankToFutureRspField["CustFee"] = "float"
#币种
CThostFtdcTransferBankToFutureRspField["CurrencyCode"] = "string"
structDict['CThostFtdcTransferBankToFutureRspField'] = CThostFtdcTransferBankToFutureRspField


#期货资金转银行请求，TradeCode=202002
CThostFtdcTransferFutureToBankReqField = {}
#期货资金账户
CThostFtdcTransferFutureToBankReqField["FutureAccount"] = "string"
#密码标志
CThostFtdcTransferFutureToBankReqField["FuturePwdFlag"] = "char"
#密码
CThostFtdcTransferFutureToBankReqField["FutureAccPwd"] = "string"
#转账金额
CThostFtdcTransferFutureToBankReqField["TradeAmt"] = "float"
#客户手续费
CThostFtdcTransferFutureToBankReqField["CustFee"] = "float"
#币种：RMB-人民币 USD-美圆 HKD-港元
CThostFtdcTransferFutureToBankReqField["CurrencyCode"] = "string"
structDict['CThostFtdcTransferFutureToBankReqField'] = CThostFtdcTransferFutureToBankReqField


#期货资金转银行请求响应
CThostFtdcTransferFutureToBankRspField = {}
#响应代码
CThostFtdcTransferFutureToBankRspField["RetCode"] = "string"
#响应信息
CThostFtdcTransferFutureToBankRspField["RetInfo"] = "string"
#资金账户
CThostFtdcTransferFutureToBankRspField["FutureAccount"] = "string"
#转帐金额
CThostFtdcTransferFutureToBankRspField["TradeAmt"] = "float"
#应收客户手续费
CThostFtdcTransferFutureToBankRspField["CustFee"] = "float"
#币种
CThostFtdcTransferFutureToBankRspField["CurrencyCode"] = "string"
structDict['CThostFtdcTransferFutureToBankRspField'] = CThostFtdcTransferFutureToBankRspField


#查询银行资金请求，TradeCode=204002
CThostFtdcTransferQryBankReqField = {}
#期货资金账户
CThostFtdcTransferQryBankReqField["FutureAccount"] = "string"
#密码标志
CThostFtdcTransferQryBankReqField["FuturePwdFlag"] = "char"
#密码
CThostFtdcTransferQryBankReqField["FutureAccPwd"] = "string"
#币种：RMB-人民币 USD-美圆 HKD-港元
CThostFtdcTransferQryBankReqField["CurrencyCode"] = "string"
structDict['CThostFtdcTransferQryBankReqField'] = CThostFtdcTransferQryBankReqField


#查询银行资金请求响应
CThostFtdcTransferQryBankRspField = {}
#响应代码
CThostFtdcTransferQryBankRspField["RetCode"] = "string"
#响应信息
CThostFtdcTransferQryBankRspField["RetInfo"] = "string"
#资金账户
CThostFtdcTransferQryBankRspField["FutureAccount"] = "string"
#银行余额
CThostFtdcTransferQryBankRspField["TradeAmt"] = "float"
#银行可用余额
CThostFtdcTransferQryBankRspField["UseAmt"] = "float"
#银行可取余额
CThostFtdcTransferQryBankRspField["FetchAmt"] = "float"
#币种
CThostFtdcTransferQryBankRspField["CurrencyCode"] = "string"
structDict['CThostFtdcTransferQryBankRspField'] = CThostFtdcTransferQryBankRspField


#查询银行交易明细请求，TradeCode=204999
CThostFtdcTransferQryDetailReqField = {}
#期货资金账户
CThostFtdcTransferQryDetailReqField["FutureAccount"] = "string"
structDict['CThostFtdcTransferQryDetailReqField'] = CThostFtdcTransferQryDetailReqField


#查询银行交易明细请求响应
CThostFtdcTransferQryDetailRspField = {}
#交易日期
CThostFtdcTransferQryDetailRspField["TradeDate"] = "string"
#交易时间
CThostFtdcTransferQryDetailRspField["TradeTime"] = "string"
#交易代码
CThostFtdcTransferQryDetailRspField["TradeCode"] = "string"
#期货流水号
CThostFtdcTransferQryDetailRspField["FutureSerial"] = "int"
#期货公司代码
CThostFtdcTransferQryDetailRspField["FutureID"] = "string"
#资金帐号
CThostFtdcTransferQryDetailRspField["FutureAccount"] = "string"
#银行流水号
CThostFtdcTransferQryDetailRspField["BankSerial"] = "int"
#银行代码
CThostFtdcTransferQryDetailRspField["BankID"] = "string"
#银行分中心代码
CThostFtdcTransferQryDetailRspField["BankBrchID"] = "string"
#银行账号
CThostFtdcTransferQryDetailRspField["BankAccount"] = "string"
#证件号码
CThostFtdcTransferQryDetailRspField["CertCode"] = "string"
#货币代码
CThostFtdcTransferQryDetailRspField["CurrencyCode"] = "string"
#发生金额
CThostFtdcTransferQryDetailRspField["TxAmount"] = "float"
#有效标志
CThostFtdcTransferQryDetailRspField["Flag"] = "char"
structDict['CThostFtdcTransferQryDetailRspField'] = CThostFtdcTransferQryDetailRspField


#响应信息
CThostFtdcRspInfoField = {}
#错误代码
CThostFtdcRspInfoField["ErrorID"] = "int"
#错误信息
CThostFtdcRspInfoField["ErrorMsg"] = "string"
structDict['CThostFtdcRspInfoField'] = CThostFtdcRspInfoField


#交易所
CThostFtdcExchangeField = {}
#交易所代码
CThostFtdcExchangeField["ExchangeID"] = "string"
#交易所名称
CThostFtdcExchangeField["ExchangeName"] = "string"
#交易所属性
CThostFtdcExchangeField["ExchangeProperty"] = "char"
structDict['CThostFtdcExchangeField'] = CThostFtdcExchangeField


#产品
CThostFtdcProductField = {}
#产品代码
CThostFtdcProductField["ProductID"] = "string"
#产品名称
CThostFtdcProductField["ProductName"] = "string"
#交易所代码
CThostFtdcProductField["ExchangeID"] = "string"
#产品类型
CThostFtdcProductField["ProductClass"] = "char"
#合约数量乘数
CThostFtdcProductField["VolumeMultiple"] = "int"
#最小变动价位
CThostFtdcProductField["PriceTick"] = "float"
#市价单最大下单量
CThostFtdcProductField["MaxMarketOrderVolume"] = "int"
#市价单最小下单量
CThostFtdcProductField["MinMarketOrderVolume"] = "int"
#限价单最大下单量
CThostFtdcProductField["MaxLimitOrderVolume"] = "int"
#限价单最小下单量
CThostFtdcProductField["MinLimitOrderVolume"] = "int"
#持仓类型
CThostFtdcProductField["PositionType"] = "char"
#持仓日期类型
CThostFtdcProductField["PositionDateType"] = "char"
#平仓处理类型
CThostFtdcProductField["CloseDealType"] = "char"
#交易币种类型
CThostFtdcProductField["TradeCurrencyID"] = "string"
#质押资金可用范围
CThostFtdcProductField["MortgageFundUseRange"] = "char"
#交易所产品代码
CThostFtdcProductField["ExchangeProductID"] = "string"
#合约基础商品乘数
CThostFtdcProductField["UnderlyingMultiple"] = "float"
structDict['CThostFtdcProductField'] = CThostFtdcProductField


#合约
CThostFtdcInstrumentField = {}
#合约代码
CThostFtdcInstrumentField["InstrumentID"] = "string"
#交易所代码
CThostFtdcInstrumentField["ExchangeID"] = "string"
#合约名称
CThostFtdcInstrumentField["InstrumentName"] = "string"
#合约在交易所的代码
CThostFtdcInstrumentField["ExchangeInstID"] = "string"
#产品代码
CThostFtdcInstrumentField["ProductID"] = "string"
#产品类型
CThostFtdcInstrumentField["ProductClass"] = "char"
#交割年份
CThostFtdcInstrumentField["DeliveryYear"] = "int"
#交割月
CThostFtdcInstrumentField["DeliveryMonth"] = "int"
#市价单最大下单量
CThostFtdcInstrumentField["MaxMarketOrderVolume"] = "int"
#市价单最小下单量
CThostFtdcInstrumentField["MinMarketOrderVolume"] = "int"
#限价单最大下单量
CThostFtdcInstrumentField["MaxLimitOrderVolume"] = "int"
#限价单最小下单量
CThostFtdcInstrumentField["MinLimitOrderVolume"] = "int"
#合约数量乘数
CThostFtdcInstrumentField["VolumeMultiple"] = "int"
#最小变动价位
CThostFtdcInstrumentField["PriceTick"] = "float"
#创建日
CThostFtdcInstrumentField["CreateDate"] = "string"
#上市日
CThostFtdcInstrumentField["OpenDate"] = "string"
#到期日
CThostFtdcInstrumentField["ExpireDate"] = "string"
#开始交割日
CThostFtdcInstrumentField["StartDelivDate"] = "string"
#结束交割日
CThostFtdcInstrumentField["EndDelivDate"] = "string"
#合约生命周期状态
CThostFtdcInstrumentField["InstLifePhase"] = "char"
#当前是否交易
CThostFtdcInstrumentField["IsTrading"] = "int"
#持仓类型
CThostFtdcInstrumentField["PositionType"] = "char"
#持仓日期类型
CThostFtdcInstrumentField["PositionDateType"] = "char"
#多头保证金率
CThostFtdcInstrumentField["LongMarginRatio"] = "float"
#空头保证金率
CThostFtdcInstrumentField["ShortMarginRatio"] = "float"
#是否使用大额单边保证金算法
CThostFtdcInstrumentField["MaxMarginSideAlgorithm"] = "char"
#基础商品代码
CThostFtdcInstrumentField["UnderlyingInstrID"] = "string"
#执行价
CThostFtdcInstrumentField["StrikePrice"] = "float"
#期权类型
CThostFtdcInstrumentField["OptionsType"] = "char"
#合约基础商品乘数
CThostFtdcInstrumentField["UnderlyingMultiple"] = "float"
#组合类型
CThostFtdcInstrumentField["CombinationType"] = "char"
structDict['CThostFtdcInstrumentField'] = CThostFtdcInstrumentField


#经纪公司
CThostFtdcBrokerField = {}
#经纪公司代码
CThostFtdcBrokerField["BrokerID"] = "string"
#经纪公司简称
CThostFtdcBrokerField["BrokerAbbr"] = "string"
#经纪公司名称
CThostFtdcBrokerField["BrokerName"] = "string"
#是否活跃
CThostFtdcBrokerField["IsActive"] = "int"
structDict['CThostFtdcBrokerField'] = CThostFtdcBrokerField


#交易所交易员
CThostFtdcTraderField = {}
#交易所代码
CThostFtdcTraderField["ExchangeID"] = "string"
#交易所交易员代码
CThostFtdcTraderField["TraderID"] = "string"
#会员代码
CThostFtdcTraderField["ParticipantID"] = "string"
#密码
CThostFtdcTraderField["Password"] = "string"
#安装数量
CThostFtdcTraderField["InstallCount"] = "int"
#经纪公司代码
CThostFtdcTraderField["BrokerID"] = "string"
structDict['CThostFtdcTraderField'] = CThostFtdcTraderField


#投资者
CThostFtdcInvestorField = {}
#投资者代码
CThostFtdcInvestorField["InvestorID"] = "string"
#经纪公司代码
CThostFtdcInvestorField["BrokerID"] = "string"
#投资者分组代码
CThostFtdcInvestorField["InvestorGroupID"] = "string"
#投资者名称
CThostFtdcInvestorField["InvestorName"] = "string"
#证件类型
CThostFtdcInvestorField["IdentifiedCardType"] = "char"
#证件号码
CThostFtdcInvestorField["IdentifiedCardNo"] = "string"
#是否活跃
CThostFtdcInvestorField["IsActive"] = "int"
#联系电话
CThostFtdcInvestorField["Telephone"] = "string"
#通讯地址
CThostFtdcInvestorField["Address"] = "string"
#开户日期
CThostFtdcInvestorField["OpenDate"] = "string"
#手机
CThostFtdcInvestorField["Mobile"] = "string"
#手续费率模板代码
CThostFtdcInvestorField["CommModelID"] = "string"
#保证金率模板代码
CThostFtdcInvestorField["MarginModelID"] = "string"
structDict['CThostFtdcInvestorField'] = CThostFtdcInvestorField


#交易编码
CThostFtdcTradingCodeField = {}
#投资者代码
CThostFtdcTradingCodeField["InvestorID"] = "string"
#经纪公司代码
CThostFtdcTradingCodeField["BrokerID"] = "string"
#交易所代码
CThostFtdcTradingCodeField["ExchangeID"] = "string"
#客户代码
CThostFtdcTradingCodeField["ClientID"] = "string"
#是否活跃
CThostFtdcTradingCodeField["IsActive"] = "int"
#交易编码类型
CThostFtdcTradingCodeField["ClientIDType"] = "char"
#营业部编号
CThostFtdcTradingCodeField["BranchID"] = "string"
#业务类型
CThostFtdcTradingCodeField["BizType"] = "char"
#投资单元代码
CThostFtdcTradingCodeField["InvestUnitID"] = "string"
structDict['CThostFtdcTradingCodeField'] = CThostFtdcTradingCodeField


#会员编码和经纪公司编码对照表
CThostFtdcPartBrokerField = {}
#经纪公司代码
CThostFtdcPartBrokerField["BrokerID"] = "string"
#交易所代码
CThostFtdcPartBrokerField["ExchangeID"] = "string"
#会员代码
CThostFtdcPartBrokerField["ParticipantID"] = "string"
#是否活跃
CThostFtdcPartBrokerField["IsActive"] = "int"
structDict['CThostFtdcPartBrokerField'] = CThostFtdcPartBrokerField


#管理用户
CThostFtdcSuperUserField = {}
#用户代码
CThostFtdcSuperUserField["UserID"] = "string"
#用户名称
CThostFtdcSuperUserField["UserName"] = "string"
#密码
CThostFtdcSuperUserField["Password"] = "string"
#是否活跃
CThostFtdcSuperUserField["IsActive"] = "int"
structDict['CThostFtdcSuperUserField'] = CThostFtdcSuperUserField


#管理用户功能权限
CThostFtdcSuperUserFunctionField = {}
#用户代码
CThostFtdcSuperUserFunctionField["UserID"] = "string"
#功能代码
CThostFtdcSuperUserFunctionField["FunctionCode"] = "char"
structDict['CThostFtdcSuperUserFunctionField'] = CThostFtdcSuperUserFunctionField


#投资者组
CThostFtdcInvestorGroupField = {}
#经纪公司代码
CThostFtdcInvestorGroupField["BrokerID"] = "string"
#投资者分组代码
CThostFtdcInvestorGroupField["InvestorGroupID"] = "string"
#投资者分组名称
CThostFtdcInvestorGroupField["InvestorGroupName"] = "string"
structDict['CThostFtdcInvestorGroupField'] = CThostFtdcInvestorGroupField


#资金账户
CThostFtdcTradingAccountField = {}
#经纪公司代码
CThostFtdcTradingAccountField["BrokerID"] = "string"
#投资者帐号
CThostFtdcTradingAccountField["AccountID"] = "string"
#上次质押金额
CThostFtdcTradingAccountField["PreMortgage"] = "float"
#上次信用额度
CThostFtdcTradingAccountField["PreCredit"] = "float"
#上次存款额
CThostFtdcTradingAccountField["PreDeposit"] = "float"
#上次结算准备金
CThostFtdcTradingAccountField["PreBalance"] = "float"
#上次占用的保证金
CThostFtdcTradingAccountField["PreMargin"] = "float"
#利息基数
CThostFtdcTradingAccountField["InterestBase"] = "float"
#利息收入
CThostFtdcTradingAccountField["Interest"] = "float"
#入金金额
CThostFtdcTradingAccountField["Deposit"] = "float"
#出金金额
CThostFtdcTradingAccountField["Withdraw"] = "float"
#冻结的保证金
CThostFtdcTradingAccountField["FrozenMargin"] = "float"
#冻结的资金
CThostFtdcTradingAccountField["FrozenCash"] = "float"
#冻结的手续费
CThostFtdcTradingAccountField["FrozenCommission"] = "float"
#当前保证金总额
CThostFtdcTradingAccountField["CurrMargin"] = "float"
#资金差额
CThostFtdcTradingAccountField["CashIn"] = "float"
#手续费
CThostFtdcTradingAccountField["Commission"] = "float"
#平仓盈亏
CThostFtdcTradingAccountField["CloseProfit"] = "float"
#持仓盈亏
CThostFtdcTradingAccountField["PositionProfit"] = "float"
#期货结算准备金
CThostFtdcTradingAccountField["Balance"] = "float"
#可用资金
CThostFtdcTradingAccountField["Available"] = "float"
#可取资金
CThostFtdcTradingAccountField["WithdrawQuota"] = "float"
#基本准备金
CThostFtdcTradingAccountField["Reserve"] = "float"
#交易日
CThostFtdcTradingAccountField["TradingDay"] = "string"
#结算编号
CThostFtdcTradingAccountField["SettlementID"] = "int"
#信用额度
CThostFtdcTradingAccountField["Credit"] = "float"
#质押金额
CThostFtdcTradingAccountField["Mortgage"] = "float"
#交易所保证金
CThostFtdcTradingAccountField["ExchangeMargin"] = "float"
#投资者交割保证金
CThostFtdcTradingAccountField["DeliveryMargin"] = "float"
#交易所交割保证金
CThostFtdcTradingAccountField["ExchangeDeliveryMargin"] = "float"
#保底期货结算准备金
CThostFtdcTradingAccountField["ReserveBalance"] = "float"
#币种代码
CThostFtdcTradingAccountField["CurrencyID"] = "string"
#上次货币质入金额
CThostFtdcTradingAccountField["PreFundMortgageIn"] = "float"
#上次货币质出金额
CThostFtdcTradingAccountField["PreFundMortgageOut"] = "float"
#货币质入金额
CThostFtdcTradingAccountField["FundMortgageIn"] = "float"
#货币质出金额
CThostFtdcTradingAccountField["FundMortgageOut"] = "float"
#货币质押余额
CThostFtdcTradingAccountField["FundMortgageAvailable"] = "float"
#可质押货币金额
CThostFtdcTradingAccountField["MortgageableFund"] = "float"
#特殊产品占用保证金
CThostFtdcTradingAccountField["SpecProductMargin"] = "float"
#特殊产品冻结保证金
CThostFtdcTradingAccountField["SpecProductFrozenMargin"] = "float"
#特殊产品手续费
CThostFtdcTradingAccountField["SpecProductCommission"] = "float"
#特殊产品冻结手续费
CThostFtdcTradingAccountField["SpecProductFrozenCommission"] = "float"
#特殊产品持仓盈亏
CThostFtdcTradingAccountField["SpecProductPositionProfit"] = "float"
#特殊产品平仓盈亏
CThostFtdcTradingAccountField["SpecProductCloseProfit"] = "float"
#根据持仓盈亏算法计算的特殊产品持仓盈亏
CThostFtdcTradingAccountField["SpecProductPositionProfitByAlg"] = "float"
#特殊产品交易所保证金
CThostFtdcTradingAccountField["SpecProductExchangeMargin"] = "float"
#业务类型
CThostFtdcTradingAccountField["BizType"] = "char"
#延时换汇冻结金额
CThostFtdcTradingAccountField["FrozenSwap"] = "float"
#剩余换汇额度
CThostFtdcTradingAccountField["RemainSwap"] = "float"
structDict['CThostFtdcTradingAccountField'] = CThostFtdcTradingAccountField


#投资者持仓
CThostFtdcInvestorPositionField = {}
#合约代码
CThostFtdcInvestorPositionField["InstrumentID"] = "string"
#经纪公司代码
CThostFtdcInvestorPositionField["BrokerID"] = "string"
#投资者代码
CThostFtdcInvestorPositionField["InvestorID"] = "string"
#持仓多空方向
CThostFtdcInvestorPositionField["PosiDirection"] = "char"
#投机套保标志
CThostFtdcInvestorPositionField["HedgeFlag"] = "char"
#持仓日期
CThostFtdcInvestorPositionField["PositionDate"] = "char"
#上日持仓
CThostFtdcInvestorPositionField["YdPosition"] = "int"
#今日持仓
CThostFtdcInvestorPositionField["Position"] = "int"
#多头冻结
CThostFtdcInvestorPositionField["LongFrozen"] = "int"
#空头冻结
CThostFtdcInvestorPositionField["ShortFrozen"] = "int"
#开仓冻结金额
CThostFtdcInvestorPositionField["LongFrozenAmount"] = "float"
#开仓冻结金额
CThostFtdcInvestorPositionField["ShortFrozenAmount"] = "float"
#开仓量
CThostFtdcInvestorPositionField["OpenVolume"] = "int"
#平仓量
CThostFtdcInvestorPositionField["CloseVolume"] = "int"
#开仓金额
CThostFtdcInvestorPositionField["OpenAmount"] = "float"
#平仓金额
CThostFtdcInvestorPositionField["CloseAmount"] = "float"
#持仓成本
CThostFtdcInvestorPositionField["PositionCost"] = "float"
#上次占用的保证金
CThostFtdcInvestorPositionField["PreMargin"] = "float"
#占用的保证金
CThostFtdcInvestorPositionField["UseMargin"] = "float"
#冻结的保证金
CThostFtdcInvestorPositionField["FrozenMargin"] = "float"
#冻结的资金
CThostFtdcInvestorPositionField["FrozenCash"] = "float"
#冻结的手续费
CThostFtdcInvestorPositionField["FrozenCommission"] = "float"
#资金差额
CThostFtdcInvestorPositionField["CashIn"] = "float"
#手续费
CThostFtdcInvestorPositionField["Commission"] = "float"
#平仓盈亏
CThostFtdcInvestorPositionField["CloseProfit"] = "float"
#持仓盈亏
CThostFtdcInvestorPositionField["PositionProfit"] = "float"
#上次结算价
CThostFtdcInvestorPositionField["PreSettlementPrice"] = "float"
#本次结算价
CThostFtdcInvestorPositionField["SettlementPrice"] = "float"
#交易日
CThostFtdcInvestorPositionField["TradingDay"] = "string"
#结算编号
CThostFtdcInvestorPositionField["SettlementID"] = "int"
#开仓成本
CThostFtdcInvestorPositionField["OpenCost"] = "float"
#交易所保证金
CThostFtdcInvestorPositionField["ExchangeMargin"] = "float"
#组合成交形成的持仓
CThostFtdcInvestorPositionField["CombPosition"] = "int"
#组合多头冻结
CThostFtdcInvestorPositionField["CombLongFrozen"] = "int"
#组合空头冻结
CThostFtdcInvestorPositionField["CombShortFrozen"] = "int"
#逐日盯市平仓盈亏
CThostFtdcInvestorPositionField["CloseProfitByDate"] = "float"
#逐笔对冲平仓盈亏
CThostFtdcInvestorPositionField["CloseProfitByTrade"] = "float"
#今日持仓
CThostFtdcInvestorPositionField["TodayPosition"] = "int"
#保证金率
CThostFtdcInvestorPositionField["MarginRateByMoney"] = "float"
#保证金率(按手数)
CThostFtdcInvestorPositionField["MarginRateByVolume"] = "float"
#执行冻结
CThostFtdcInvestorPositionField["StrikeFrozen"] = "int"
#执行冻结金额
CThostFtdcInvestorPositionField["StrikeFrozenAmount"] = "float"
#放弃执行冻结
CThostFtdcInvestorPositionField["AbandonFrozen"] = "int"
#交易所代码
CThostFtdcInvestorPositionField["ExchangeID"] = "string"
#执行冻结的昨仓
CThostFtdcInvestorPositionField["YdStrikeFrozen"] = "int"
#投资单元代码
CThostFtdcInvestorPositionField["InvestUnitID"] = "string"
structDict['CThostFtdcInvestorPositionField'] = CThostFtdcInvestorPositionField


#合约保证金率
CThostFtdcInstrumentMarginRateField = {}
#合约代码
CThostFtdcInstrumentMarginRateField["InstrumentID"] = "string"
#投资者范围
CThostFtdcInstrumentMarginRateField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcInstrumentMarginRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcInstrumentMarginRateField["InvestorID"] = "string"
#投机套保标志
CThostFtdcInstrumentMarginRateField["HedgeFlag"] = "char"
#多头保证金率
CThostFtdcInstrumentMarginRateField["LongMarginRatioByMoney"] = "float"
#多头保证金费
CThostFtdcInstrumentMarginRateField["LongMarginRatioByVolume"] = "float"
#空头保证金率
CThostFtdcInstrumentMarginRateField["ShortMarginRatioByMoney"] = "float"
#空头保证金费
CThostFtdcInstrumentMarginRateField["ShortMarginRatioByVolume"] = "float"
#是否相对交易所收取
CThostFtdcInstrumentMarginRateField["IsRelative"] = "int"
#交易所代码
CThostFtdcInstrumentMarginRateField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcInstrumentMarginRateField["InvestUnitID"] = "string"
structDict['CThostFtdcInstrumentMarginRateField'] = CThostFtdcInstrumentMarginRateField


#合约手续费率
CThostFtdcInstrumentCommissionRateField = {}
#合约代码
CThostFtdcInstrumentCommissionRateField["InstrumentID"] = "string"
#投资者范围
CThostFtdcInstrumentCommissionRateField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcInstrumentCommissionRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcInstrumentCommissionRateField["InvestorID"] = "string"
#开仓手续费率
CThostFtdcInstrumentCommissionRateField["OpenRatioByMoney"] = "float"
#开仓手续费
CThostFtdcInstrumentCommissionRateField["OpenRatioByVolume"] = "float"
#平仓手续费率
CThostFtdcInstrumentCommissionRateField["CloseRatioByMoney"] = "float"
#平仓手续费
CThostFtdcInstrumentCommissionRateField["CloseRatioByVolume"] = "float"
#平今手续费率
CThostFtdcInstrumentCommissionRateField["CloseTodayRatioByMoney"] = "float"
#平今手续费
CThostFtdcInstrumentCommissionRateField["CloseTodayRatioByVolume"] = "float"
#交易所代码
CThostFtdcInstrumentCommissionRateField["ExchangeID"] = "string"
#业务类型
CThostFtdcInstrumentCommissionRateField["BizType"] = "char"
#投资单元代码
CThostFtdcInstrumentCommissionRateField["InvestUnitID"] = "string"
structDict['CThostFtdcInstrumentCommissionRateField'] = CThostFtdcInstrumentCommissionRateField


#深度行情
CThostFtdcDepthMarketDataField = {}
#交易日
CThostFtdcDepthMarketDataField["TradingDay"] = "string"
#合约代码
CThostFtdcDepthMarketDataField["InstrumentID"] = "string"
#交易所代码
CThostFtdcDepthMarketDataField["ExchangeID"] = "string"
#合约在交易所的代码
CThostFtdcDepthMarketDataField["ExchangeInstID"] = "string"
#最新价
CThostFtdcDepthMarketDataField["LastPrice"] = "float"
#上次结算价
CThostFtdcDepthMarketDataField["PreSettlementPrice"] = "float"
#昨收盘
CThostFtdcDepthMarketDataField["PreClosePrice"] = "float"
#昨持仓量
CThostFtdcDepthMarketDataField["PreOpenInterest"] = "float"
#今开盘
CThostFtdcDepthMarketDataField["OpenPrice"] = "float"
#最高价
CThostFtdcDepthMarketDataField["HighestPrice"] = "float"
#最低价
CThostFtdcDepthMarketDataField["LowestPrice"] = "float"
#数量
CThostFtdcDepthMarketDataField["Volume"] = "int"
#成交金额
CThostFtdcDepthMarketDataField["Turnover"] = "float"
#持仓量
CThostFtdcDepthMarketDataField["OpenInterest"] = "float"
#今收盘
CThostFtdcDepthMarketDataField["ClosePrice"] = "float"
#本次结算价
CThostFtdcDepthMarketDataField["SettlementPrice"] = "float"
#涨停板价
CThostFtdcDepthMarketDataField["UpperLimitPrice"] = "float"
#跌停板价
CThostFtdcDepthMarketDataField["LowerLimitPrice"] = "float"
#昨虚实度
CThostFtdcDepthMarketDataField["PreDelta"] = "float"
#今虚实度
CThostFtdcDepthMarketDataField["CurrDelta"] = "float"
#最后修改时间
CThostFtdcDepthMarketDataField["UpdateTime"] = "string"
#最后修改毫秒
CThostFtdcDepthMarketDataField["UpdateMillisec"] = "int"
#申买价一
CThostFtdcDepthMarketDataField["BidPrice1"] = "float"
#申买量一
CThostFtdcDepthMarketDataField["BidVolume1"] = "int"
#申卖价一
CThostFtdcDepthMarketDataField["AskPrice1"] = "float"
#申卖量一
CThostFtdcDepthMarketDataField["AskVolume1"] = "int"
#申买价二
CThostFtdcDepthMarketDataField["BidPrice2"] = "float"
#申买量二
CThostFtdcDepthMarketDataField["BidVolume2"] = "int"
#申卖价二
CThostFtdcDepthMarketDataField["AskPrice2"] = "float"
#申卖量二
CThostFtdcDepthMarketDataField["AskVolume2"] = "int"
#申买价三
CThostFtdcDepthMarketDataField["BidPrice3"] = "float"
#申买量三
CThostFtdcDepthMarketDataField["BidVolume3"] = "int"
#申卖价三
CThostFtdcDepthMarketDataField["AskPrice3"] = "float"
#申卖量三
CThostFtdcDepthMarketDataField["AskVolume3"] = "int"
#申买价四
CThostFtdcDepthMarketDataField["BidPrice4"] = "float"
#申买量四
CThostFtdcDepthMarketDataField["BidVolume4"] = "int"
#申卖价四
CThostFtdcDepthMarketDataField["AskPrice4"] = "float"
#申卖量四
CThostFtdcDepthMarketDataField["AskVolume4"] = "int"
#申买价五
CThostFtdcDepthMarketDataField["BidPrice5"] = "float"
#申买量五
CThostFtdcDepthMarketDataField["BidVolume5"] = "int"
#申卖价五
CThostFtdcDepthMarketDataField["AskPrice5"] = "float"
#申卖量五
CThostFtdcDepthMarketDataField["AskVolume5"] = "int"
#当日均价
CThostFtdcDepthMarketDataField["AveragePrice"] = "float"
#业务日期
CThostFtdcDepthMarketDataField["ActionDay"] = "string"
structDict['CThostFtdcDepthMarketDataField'] = CThostFtdcDepthMarketDataField


#投资者合约交易权限
CThostFtdcInstrumentTradingRightField = {}
#合约代码
CThostFtdcInstrumentTradingRightField["InstrumentID"] = "string"
#投资者范围
CThostFtdcInstrumentTradingRightField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcInstrumentTradingRightField["BrokerID"] = "string"
#投资者代码
CThostFtdcInstrumentTradingRightField["InvestorID"] = "string"
#交易权限
CThostFtdcInstrumentTradingRightField["TradingRight"] = "char"
structDict['CThostFtdcInstrumentTradingRightField'] = CThostFtdcInstrumentTradingRightField


#经纪公司用户
CThostFtdcBrokerUserField = {}
#经纪公司代码
CThostFtdcBrokerUserField["BrokerID"] = "string"
#用户代码
CThostFtdcBrokerUserField["UserID"] = "string"
#用户名称
CThostFtdcBrokerUserField["UserName"] = "string"
#用户类型
CThostFtdcBrokerUserField["UserType"] = "char"
#是否活跃
CThostFtdcBrokerUserField["IsActive"] = "int"
#是否使用令牌
CThostFtdcBrokerUserField["IsUsingOTP"] = "int"
#是否强制终端认证
CThostFtdcBrokerUserField["IsAuthForce"] = "int"
structDict['CThostFtdcBrokerUserField'] = CThostFtdcBrokerUserField


#经纪公司用户口令
CThostFtdcBrokerUserPasswordField = {}
#经纪公司代码
CThostFtdcBrokerUserPasswordField["BrokerID"] = "string"
#用户代码
CThostFtdcBrokerUserPasswordField["UserID"] = "string"
#密码
CThostFtdcBrokerUserPasswordField["Password"] = "string"
#上次修改时间
CThostFtdcBrokerUserPasswordField["LastUpdateTime"] = "string"
#上次登陆时间
CThostFtdcBrokerUserPasswordField["LastLoginTime"] = "string"
#密码过期时间
CThostFtdcBrokerUserPasswordField["ExpireDate"] = "string"
#弱密码过期时间
CThostFtdcBrokerUserPasswordField["WeakExpireDate"] = "string"
structDict['CThostFtdcBrokerUserPasswordField'] = CThostFtdcBrokerUserPasswordField


#经纪公司用户功能权限
CThostFtdcBrokerUserFunctionField = {}
#经纪公司代码
CThostFtdcBrokerUserFunctionField["BrokerID"] = "string"
#用户代码
CThostFtdcBrokerUserFunctionField["UserID"] = "string"
#经纪公司功能代码
CThostFtdcBrokerUserFunctionField["BrokerFunctionCode"] = "char"
structDict['CThostFtdcBrokerUserFunctionField'] = CThostFtdcBrokerUserFunctionField


#交易所交易员报盘机
CThostFtdcTraderOfferField = {}
#交易所代码
CThostFtdcTraderOfferField["ExchangeID"] = "string"
#交易所交易员代码
CThostFtdcTraderOfferField["TraderID"] = "string"
#会员代码
CThostFtdcTraderOfferField["ParticipantID"] = "string"
#密码
CThostFtdcTraderOfferField["Password"] = "string"
#安装编号
CThostFtdcTraderOfferField["InstallID"] = "int"
#本地报单编号
CThostFtdcTraderOfferField["OrderLocalID"] = "string"
#交易所交易员连接状态
CThostFtdcTraderOfferField["TraderConnectStatus"] = "char"
#发出连接请求的日期
CThostFtdcTraderOfferField["ConnectRequestDate"] = "string"
#发出连接请求的时间
CThostFtdcTraderOfferField["ConnectRequestTime"] = "string"
#上次报告日期
CThostFtdcTraderOfferField["LastReportDate"] = "string"
#上次报告时间
CThostFtdcTraderOfferField["LastReportTime"] = "string"
#完成连接日期
CThostFtdcTraderOfferField["ConnectDate"] = "string"
#完成连接时间
CThostFtdcTraderOfferField["ConnectTime"] = "string"
#启动日期
CThostFtdcTraderOfferField["StartDate"] = "string"
#启动时间
CThostFtdcTraderOfferField["StartTime"] = "string"
#交易日
CThostFtdcTraderOfferField["TradingDay"] = "string"
#经纪公司代码
CThostFtdcTraderOfferField["BrokerID"] = "string"
#本席位最大成交编号
CThostFtdcTraderOfferField["MaxTradeID"] = "string"
#本席位最大报单备拷
CThostFtdcTraderOfferField["MaxOrderMessageReference"] = "string"
structDict['CThostFtdcTraderOfferField'] = CThostFtdcTraderOfferField


#投资者结算结果
CThostFtdcSettlementInfoField = {}
#交易日
CThostFtdcSettlementInfoField["TradingDay"] = "string"
#结算编号
CThostFtdcSettlementInfoField["SettlementID"] = "int"
#经纪公司代码
CThostFtdcSettlementInfoField["BrokerID"] = "string"
#投资者代码
CThostFtdcSettlementInfoField["InvestorID"] = "string"
#序号
CThostFtdcSettlementInfoField["SequenceNo"] = "int"
#消息正文
CThostFtdcSettlementInfoField["Content"] = "string"
#投资者帐号
CThostFtdcSettlementInfoField["AccountID"] = "string"
#币种代码
CThostFtdcSettlementInfoField["CurrencyID"] = "string"
structDict['CThostFtdcSettlementInfoField'] = CThostFtdcSettlementInfoField


#合约保证金率调整
CThostFtdcInstrumentMarginRateAdjustField = {}
#合约代码
CThostFtdcInstrumentMarginRateAdjustField["InstrumentID"] = "string"
#投资者范围
CThostFtdcInstrumentMarginRateAdjustField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcInstrumentMarginRateAdjustField["BrokerID"] = "string"
#投资者代码
CThostFtdcInstrumentMarginRateAdjustField["InvestorID"] = "string"
#投机套保标志
CThostFtdcInstrumentMarginRateAdjustField["HedgeFlag"] = "char"
#多头保证金率
CThostFtdcInstrumentMarginRateAdjustField["LongMarginRatioByMoney"] = "float"
#多头保证金费
CThostFtdcInstrumentMarginRateAdjustField["LongMarginRatioByVolume"] = "float"
#空头保证金率
CThostFtdcInstrumentMarginRateAdjustField["ShortMarginRatioByMoney"] = "float"
#空头保证金费
CThostFtdcInstrumentMarginRateAdjustField["ShortMarginRatioByVolume"] = "float"
#是否相对交易所收取
CThostFtdcInstrumentMarginRateAdjustField["IsRelative"] = "int"
structDict['CThostFtdcInstrumentMarginRateAdjustField'] = CThostFtdcInstrumentMarginRateAdjustField


#交易所保证金率
CThostFtdcExchangeMarginRateField = {}
#经纪公司代码
CThostFtdcExchangeMarginRateField["BrokerID"] = "string"
#合约代码
CThostFtdcExchangeMarginRateField["InstrumentID"] = "string"
#投机套保标志
CThostFtdcExchangeMarginRateField["HedgeFlag"] = "char"
#多头保证金率
CThostFtdcExchangeMarginRateField["LongMarginRatioByMoney"] = "float"
#多头保证金费
CThostFtdcExchangeMarginRateField["LongMarginRatioByVolume"] = "float"
#空头保证金率
CThostFtdcExchangeMarginRateField["ShortMarginRatioByMoney"] = "float"
#空头保证金费
CThostFtdcExchangeMarginRateField["ShortMarginRatioByVolume"] = "float"
#交易所代码
CThostFtdcExchangeMarginRateField["ExchangeID"] = "string"
structDict['CThostFtdcExchangeMarginRateField'] = CThostFtdcExchangeMarginRateField


#交易所保证金率调整
CThostFtdcExchangeMarginRateAdjustField = {}
#经纪公司代码
CThostFtdcExchangeMarginRateAdjustField["BrokerID"] = "string"
#合约代码
CThostFtdcExchangeMarginRateAdjustField["InstrumentID"] = "string"
#投机套保标志
CThostFtdcExchangeMarginRateAdjustField["HedgeFlag"] = "char"
#跟随交易所投资者多头保证金率
CThostFtdcExchangeMarginRateAdjustField["LongMarginRatioByMoney"] = "float"
#跟随交易所投资者多头保证金费
CThostFtdcExchangeMarginRateAdjustField["LongMarginRatioByVolume"] = "float"
#跟随交易所投资者空头保证金率
CThostFtdcExchangeMarginRateAdjustField["ShortMarginRatioByMoney"] = "float"
#跟随交易所投资者空头保证金费
CThostFtdcExchangeMarginRateAdjustField["ShortMarginRatioByVolume"] = "float"
#交易所多头保证金率
CThostFtdcExchangeMarginRateAdjustField["ExchLongMarginRatioByMoney"] = "float"
#交易所多头保证金费
CThostFtdcExchangeMarginRateAdjustField["ExchLongMarginRatioByVolume"] = "float"
#交易所空头保证金率
CThostFtdcExchangeMarginRateAdjustField["ExchShortMarginRatioByMoney"] = "float"
#交易所空头保证金费
CThostFtdcExchangeMarginRateAdjustField["ExchShortMarginRatioByVolume"] = "float"
#不跟随交易所投资者多头保证金率
CThostFtdcExchangeMarginRateAdjustField["NoLongMarginRatioByMoney"] = "float"
#不跟随交易所投资者多头保证金费
CThostFtdcExchangeMarginRateAdjustField["NoLongMarginRatioByVolume"] = "float"
#不跟随交易所投资者空头保证金率
CThostFtdcExchangeMarginRateAdjustField["NoShortMarginRatioByMoney"] = "float"
#不跟随交易所投资者空头保证金费
CThostFtdcExchangeMarginRateAdjustField["NoShortMarginRatioByVolume"] = "float"
structDict['CThostFtdcExchangeMarginRateAdjustField'] = CThostFtdcExchangeMarginRateAdjustField


#汇率
CThostFtdcExchangeRateField = {}
#经纪公司代码
CThostFtdcExchangeRateField["BrokerID"] = "string"
#源币种
CThostFtdcExchangeRateField["FromCurrencyID"] = "string"
#源币种单位数量
CThostFtdcExchangeRateField["FromCurrencyUnit"] = "float"
#目标币种
CThostFtdcExchangeRateField["ToCurrencyID"] = "string"
#汇率
CThostFtdcExchangeRateField["ExchangeRate"] = "float"
structDict['CThostFtdcExchangeRateField'] = CThostFtdcExchangeRateField


#结算引用
CThostFtdcSettlementRefField = {}
#交易日
CThostFtdcSettlementRefField["TradingDay"] = "string"
#结算编号
CThostFtdcSettlementRefField["SettlementID"] = "int"
structDict['CThostFtdcSettlementRefField'] = CThostFtdcSettlementRefField


#当前时间
CThostFtdcCurrentTimeField = {}
#当前日期
CThostFtdcCurrentTimeField["CurrDate"] = "string"
#当前时间
CThostFtdcCurrentTimeField["CurrTime"] = "string"
#当前时间（毫秒）
CThostFtdcCurrentTimeField["CurrMillisec"] = "int"
#业务日期
CThostFtdcCurrentTimeField["ActionDay"] = "string"
structDict['CThostFtdcCurrentTimeField'] = CThostFtdcCurrentTimeField


#通讯阶段
CThostFtdcCommPhaseField = {}
#交易日
CThostFtdcCommPhaseField["TradingDay"] = "string"
#通讯时段编号
CThostFtdcCommPhaseField["CommPhaseNo"] = "int"
#系统编号
CThostFtdcCommPhaseField["SystemID"] = "string"
structDict['CThostFtdcCommPhaseField'] = CThostFtdcCommPhaseField


#登录信息
CThostFtdcLoginInfoField = {}
#前置编号
CThostFtdcLoginInfoField["FrontID"] = "int"
#会话编号
CThostFtdcLoginInfoField["SessionID"] = "int"
#经纪公司代码
CThostFtdcLoginInfoField["BrokerID"] = "string"
#用户代码
CThostFtdcLoginInfoField["UserID"] = "string"
#登录日期
CThostFtdcLoginInfoField["LoginDate"] = "string"
#登录时间
CThostFtdcLoginInfoField["LoginTime"] = "string"
#IP地址
CThostFtdcLoginInfoField["IPAddress"] = "string"
#用户端产品信息
CThostFtdcLoginInfoField["UserProductInfo"] = "string"
#接口端产品信息
CThostFtdcLoginInfoField["InterfaceProductInfo"] = "string"
#协议信息
CThostFtdcLoginInfoField["ProtocolInfo"] = "string"
#系统名称
CThostFtdcLoginInfoField["SystemName"] = "string"
#密码,已弃用
CThostFtdcLoginInfoField["PasswordDeprecated"] = "string"
#最大报单引用
CThostFtdcLoginInfoField["MaxOrderRef"] = "string"
#上期所时间
CThostFtdcLoginInfoField["SHFETime"] = "string"
#大商所时间
CThostFtdcLoginInfoField["DCETime"] = "string"
#郑商所时间
CThostFtdcLoginInfoField["CZCETime"] = "string"
#中金所时间
CThostFtdcLoginInfoField["FFEXTime"] = "string"
#Mac地址
CThostFtdcLoginInfoField["MacAddress"] = "string"
#动态密码
CThostFtdcLoginInfoField["OneTimePassword"] = "string"
#能源中心时间
CThostFtdcLoginInfoField["INETime"] = "string"
#查询时是否需要流控
CThostFtdcLoginInfoField["IsQryControl"] = "int"
#登录备注
CThostFtdcLoginInfoField["LoginRemark"] = "string"
#密码
CThostFtdcLoginInfoField["Password"] = "string"
structDict['CThostFtdcLoginInfoField'] = CThostFtdcLoginInfoField


#登录信息
CThostFtdcLogoutAllField = {}
#前置编号
CThostFtdcLogoutAllField["FrontID"] = "int"
#会话编号
CThostFtdcLogoutAllField["SessionID"] = "int"
#系统名称
CThostFtdcLogoutAllField["SystemName"] = "string"
structDict['CThostFtdcLogoutAllField'] = CThostFtdcLogoutAllField


#前置状态
CThostFtdcFrontStatusField = {}
#前置编号
CThostFtdcFrontStatusField["FrontID"] = "int"
#上次报告日期
CThostFtdcFrontStatusField["LastReportDate"] = "string"
#上次报告时间
CThostFtdcFrontStatusField["LastReportTime"] = "string"
#是否活跃
CThostFtdcFrontStatusField["IsActive"] = "int"
structDict['CThostFtdcFrontStatusField'] = CThostFtdcFrontStatusField


#用户口令变更
CThostFtdcUserPasswordUpdateField = {}
#经纪公司代码
CThostFtdcUserPasswordUpdateField["BrokerID"] = "string"
#用户代码
CThostFtdcUserPasswordUpdateField["UserID"] = "string"
#原来的口令
CThostFtdcUserPasswordUpdateField["OldPassword"] = "string"
#新的口令
CThostFtdcUserPasswordUpdateField["NewPassword"] = "string"
structDict['CThostFtdcUserPasswordUpdateField'] = CThostFtdcUserPasswordUpdateField


#输入报单
CThostFtdcInputOrderField = {}
#经纪公司代码
CThostFtdcInputOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcInputOrderField["InvestorID"] = "string"
#合约代码
CThostFtdcInputOrderField["InstrumentID"] = "string"
#报单引用
CThostFtdcInputOrderField["OrderRef"] = "string"
#用户代码
CThostFtdcInputOrderField["UserID"] = "string"
#报单价格条件
CThostFtdcInputOrderField["OrderPriceType"] = "char"
#买卖方向
CThostFtdcInputOrderField["Direction"] = "char"
#组合开平标志
CThostFtdcInputOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CThostFtdcInputOrderField["CombHedgeFlag"] = "string"
#价格
CThostFtdcInputOrderField["LimitPrice"] = "float"
#数量
CThostFtdcInputOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CThostFtdcInputOrderField["TimeCondition"] = "char"
#GTD日期
CThostFtdcInputOrderField["GTDDate"] = "string"
#成交量类型
CThostFtdcInputOrderField["VolumeCondition"] = "char"
#最小成交量
CThostFtdcInputOrderField["MinVolume"] = "int"
#触发条件
CThostFtdcInputOrderField["ContingentCondition"] = "char"
#止损价
CThostFtdcInputOrderField["StopPrice"] = "float"
#强平原因
CThostFtdcInputOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CThostFtdcInputOrderField["IsAutoSuspend"] = "int"
#业务单元
CThostFtdcInputOrderField["BusinessUnit"] = "string"
#请求编号
CThostFtdcInputOrderField["RequestID"] = "int"
#用户强评标志
CThostFtdcInputOrderField["UserForceClose"] = "int"
#互换单标志
CThostFtdcInputOrderField["IsSwapOrder"] = "int"
#交易所代码
CThostFtdcInputOrderField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcInputOrderField["InvestUnitID"] = "string"
#资金账号
CThostFtdcInputOrderField["AccountID"] = "string"
#币种代码
CThostFtdcInputOrderField["CurrencyID"] = "string"
#交易编码
CThostFtdcInputOrderField["ClientID"] = "string"
#IP地址
CThostFtdcInputOrderField["IPAddress"] = "string"
#Mac地址
CThostFtdcInputOrderField["MacAddress"] = "string"
structDict['CThostFtdcInputOrderField'] = CThostFtdcInputOrderField


#报单
CThostFtdcOrderField = {}
#经纪公司代码
CThostFtdcOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcOrderField["InvestorID"] = "string"
#合约代码
CThostFtdcOrderField["InstrumentID"] = "string"
#报单引用
CThostFtdcOrderField["OrderRef"] = "string"
#用户代码
CThostFtdcOrderField["UserID"] = "string"
#报单价格条件
CThostFtdcOrderField["OrderPriceType"] = "char"
#买卖方向
CThostFtdcOrderField["Direction"] = "char"
#组合开平标志
CThostFtdcOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CThostFtdcOrderField["CombHedgeFlag"] = "string"
#价格
CThostFtdcOrderField["LimitPrice"] = "float"
#数量
CThostFtdcOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CThostFtdcOrderField["TimeCondition"] = "char"
#GTD日期
CThostFtdcOrderField["GTDDate"] = "string"
#成交量类型
CThostFtdcOrderField["VolumeCondition"] = "char"
#最小成交量
CThostFtdcOrderField["MinVolume"] = "int"
#触发条件
CThostFtdcOrderField["ContingentCondition"] = "char"
#止损价
CThostFtdcOrderField["StopPrice"] = "float"
#强平原因
CThostFtdcOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CThostFtdcOrderField["IsAutoSuspend"] = "int"
#业务单元
CThostFtdcOrderField["BusinessUnit"] = "string"
#请求编号
CThostFtdcOrderField["RequestID"] = "int"
#本地报单编号
CThostFtdcOrderField["OrderLocalID"] = "string"
#交易所代码
CThostFtdcOrderField["ExchangeID"] = "string"
#会员代码
CThostFtdcOrderField["ParticipantID"] = "string"
#客户代码
CThostFtdcOrderField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcOrderField["ExchangeInstID"] = "string"
#交易所交易员代码
CThostFtdcOrderField["TraderID"] = "string"
#安装编号
CThostFtdcOrderField["InstallID"] = "int"
#报单提交状态
CThostFtdcOrderField["OrderSubmitStatus"] = "char"
#报单提示序号
CThostFtdcOrderField["NotifySequence"] = "int"
#交易日
CThostFtdcOrderField["TradingDay"] = "string"
#结算编号
CThostFtdcOrderField["SettlementID"] = "int"
#报单编号
CThostFtdcOrderField["OrderSysID"] = "string"
#报单来源
CThostFtdcOrderField["OrderSource"] = "char"
#报单状态
CThostFtdcOrderField["OrderStatus"] = "char"
#报单类型
CThostFtdcOrderField["OrderType"] = "char"
#今成交数量
CThostFtdcOrderField["VolumeTraded"] = "int"
#剩余数量
CThostFtdcOrderField["VolumeTotal"] = "int"
#报单日期
CThostFtdcOrderField["InsertDate"] = "string"
#委托时间
CThostFtdcOrderField["InsertTime"] = "string"
#激活时间
CThostFtdcOrderField["ActiveTime"] = "string"
#挂起时间
CThostFtdcOrderField["SuspendTime"] = "string"
#最后修改时间
CThostFtdcOrderField["UpdateTime"] = "string"
#撤销时间
CThostFtdcOrderField["CancelTime"] = "string"
#最后修改交易所交易员代码
CThostFtdcOrderField["ActiveTraderID"] = "string"
#结算会员编号
CThostFtdcOrderField["ClearingPartID"] = "string"
#序号
CThostFtdcOrderField["SequenceNo"] = "int"
#前置编号
CThostFtdcOrderField["FrontID"] = "int"
#会话编号
CThostFtdcOrderField["SessionID"] = "int"
#用户端产品信息
CThostFtdcOrderField["UserProductInfo"] = "string"
#状态信息
CThostFtdcOrderField["StatusMsg"] = "string"
#用户强评标志
CThostFtdcOrderField["UserForceClose"] = "int"
#操作用户代码
CThostFtdcOrderField["ActiveUserID"] = "string"
#经纪公司报单编号
CThostFtdcOrderField["BrokerOrderSeq"] = "int"
#相关报单
CThostFtdcOrderField["RelativeOrderSysID"] = "string"
#郑商所成交数量
CThostFtdcOrderField["ZCETotalTradedVolume"] = "int"
#互换单标志
CThostFtdcOrderField["IsSwapOrder"] = "int"
#营业部编号
CThostFtdcOrderField["BranchID"] = "string"
#投资单元代码
CThostFtdcOrderField["InvestUnitID"] = "string"
#资金账号
CThostFtdcOrderField["AccountID"] = "string"
#币种代码
CThostFtdcOrderField["CurrencyID"] = "string"
#IP地址
CThostFtdcOrderField["IPAddress"] = "string"
#Mac地址
CThostFtdcOrderField["MacAddress"] = "string"
structDict['CThostFtdcOrderField'] = CThostFtdcOrderField


#交易所报单
CThostFtdcExchangeOrderField = {}
#报单价格条件
CThostFtdcExchangeOrderField["OrderPriceType"] = "char"
#买卖方向
CThostFtdcExchangeOrderField["Direction"] = "char"
#组合开平标志
CThostFtdcExchangeOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CThostFtdcExchangeOrderField["CombHedgeFlag"] = "string"
#价格
CThostFtdcExchangeOrderField["LimitPrice"] = "float"
#数量
CThostFtdcExchangeOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CThostFtdcExchangeOrderField["TimeCondition"] = "char"
#GTD日期
CThostFtdcExchangeOrderField["GTDDate"] = "string"
#成交量类型
CThostFtdcExchangeOrderField["VolumeCondition"] = "char"
#最小成交量
CThostFtdcExchangeOrderField["MinVolume"] = "int"
#触发条件
CThostFtdcExchangeOrderField["ContingentCondition"] = "char"
#止损价
CThostFtdcExchangeOrderField["StopPrice"] = "float"
#强平原因
CThostFtdcExchangeOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CThostFtdcExchangeOrderField["IsAutoSuspend"] = "int"
#业务单元
CThostFtdcExchangeOrderField["BusinessUnit"] = "string"
#请求编号
CThostFtdcExchangeOrderField["RequestID"] = "int"
#本地报单编号
CThostFtdcExchangeOrderField["OrderLocalID"] = "string"
#交易所代码
CThostFtdcExchangeOrderField["ExchangeID"] = "string"
#会员代码
CThostFtdcExchangeOrderField["ParticipantID"] = "string"
#客户代码
CThostFtdcExchangeOrderField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcExchangeOrderField["ExchangeInstID"] = "string"
#交易所交易员代码
CThostFtdcExchangeOrderField["TraderID"] = "string"
#安装编号
CThostFtdcExchangeOrderField["InstallID"] = "int"
#报单提交状态
CThostFtdcExchangeOrderField["OrderSubmitStatus"] = "char"
#报单提示序号
CThostFtdcExchangeOrderField["NotifySequence"] = "int"
#交易日
CThostFtdcExchangeOrderField["TradingDay"] = "string"
#结算编号
CThostFtdcExchangeOrderField["SettlementID"] = "int"
#报单编号
CThostFtdcExchangeOrderField["OrderSysID"] = "string"
#报单来源
CThostFtdcExchangeOrderField["OrderSource"] = "char"
#报单状态
CThostFtdcExchangeOrderField["OrderStatus"] = "char"
#报单类型
CThostFtdcExchangeOrderField["OrderType"] = "char"
#今成交数量
CThostFtdcExchangeOrderField["VolumeTraded"] = "int"
#剩余数量
CThostFtdcExchangeOrderField["VolumeTotal"] = "int"
#报单日期
CThostFtdcExchangeOrderField["InsertDate"] = "string"
#委托时间
CThostFtdcExchangeOrderField["InsertTime"] = "string"
#激活时间
CThostFtdcExchangeOrderField["ActiveTime"] = "string"
#挂起时间
CThostFtdcExchangeOrderField["SuspendTime"] = "string"
#最后修改时间
CThostFtdcExchangeOrderField["UpdateTime"] = "string"
#撤销时间
CThostFtdcExchangeOrderField["CancelTime"] = "string"
#最后修改交易所交易员代码
CThostFtdcExchangeOrderField["ActiveTraderID"] = "string"
#结算会员编号
CThostFtdcExchangeOrderField["ClearingPartID"] = "string"
#序号
CThostFtdcExchangeOrderField["SequenceNo"] = "int"
#营业部编号
CThostFtdcExchangeOrderField["BranchID"] = "string"
#IP地址
CThostFtdcExchangeOrderField["IPAddress"] = "string"
#Mac地址
CThostFtdcExchangeOrderField["MacAddress"] = "string"
structDict['CThostFtdcExchangeOrderField'] = CThostFtdcExchangeOrderField


#交易所报单插入失败
CThostFtdcExchangeOrderInsertErrorField = {}
#交易所代码
CThostFtdcExchangeOrderInsertErrorField["ExchangeID"] = "string"
#会员代码
CThostFtdcExchangeOrderInsertErrorField["ParticipantID"] = "string"
#交易所交易员代码
CThostFtdcExchangeOrderInsertErrorField["TraderID"] = "string"
#安装编号
CThostFtdcExchangeOrderInsertErrorField["InstallID"] = "int"
#本地报单编号
CThostFtdcExchangeOrderInsertErrorField["OrderLocalID"] = "string"
#错误代码
CThostFtdcExchangeOrderInsertErrorField["ErrorID"] = "int"
#错误信息
CThostFtdcExchangeOrderInsertErrorField["ErrorMsg"] = "string"
structDict['CThostFtdcExchangeOrderInsertErrorField'] = CThostFtdcExchangeOrderInsertErrorField


#输入报单操作
CThostFtdcInputOrderActionField = {}
#经纪公司代码
CThostFtdcInputOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcInputOrderActionField["InvestorID"] = "string"
#报单操作引用
CThostFtdcInputOrderActionField["OrderActionRef"] = "int"
#报单引用
CThostFtdcInputOrderActionField["OrderRef"] = "string"
#请求编号
CThostFtdcInputOrderActionField["RequestID"] = "int"
#前置编号
CThostFtdcInputOrderActionField["FrontID"] = "int"
#会话编号
CThostFtdcInputOrderActionField["SessionID"] = "int"
#交易所代码
CThostFtdcInputOrderActionField["ExchangeID"] = "string"
#报单编号
CThostFtdcInputOrderActionField["OrderSysID"] = "string"
#操作标志
CThostFtdcInputOrderActionField["ActionFlag"] = "char"
#价格
CThostFtdcInputOrderActionField["LimitPrice"] = "float"
#数量变化
CThostFtdcInputOrderActionField["VolumeChange"] = "int"
#用户代码
CThostFtdcInputOrderActionField["UserID"] = "string"
#合约代码
CThostFtdcInputOrderActionField["InstrumentID"] = "string"
#投资单元代码
CThostFtdcInputOrderActionField["InvestUnitID"] = "string"
#IP地址
CThostFtdcInputOrderActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcInputOrderActionField["MacAddress"] = "string"
structDict['CThostFtdcInputOrderActionField'] = CThostFtdcInputOrderActionField


#报单操作
CThostFtdcOrderActionField = {}
#经纪公司代码
CThostFtdcOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcOrderActionField["InvestorID"] = "string"
#报单操作引用
CThostFtdcOrderActionField["OrderActionRef"] = "int"
#报单引用
CThostFtdcOrderActionField["OrderRef"] = "string"
#请求编号
CThostFtdcOrderActionField["RequestID"] = "int"
#前置编号
CThostFtdcOrderActionField["FrontID"] = "int"
#会话编号
CThostFtdcOrderActionField["SessionID"] = "int"
#交易所代码
CThostFtdcOrderActionField["ExchangeID"] = "string"
#报单编号
CThostFtdcOrderActionField["OrderSysID"] = "string"
#操作标志
CThostFtdcOrderActionField["ActionFlag"] = "char"
#价格
CThostFtdcOrderActionField["LimitPrice"] = "float"
#数量变化
CThostFtdcOrderActionField["VolumeChange"] = "int"
#操作日期
CThostFtdcOrderActionField["ActionDate"] = "string"
#操作时间
CThostFtdcOrderActionField["ActionTime"] = "string"
#交易所交易员代码
CThostFtdcOrderActionField["TraderID"] = "string"
#安装编号
CThostFtdcOrderActionField["InstallID"] = "int"
#本地报单编号
CThostFtdcOrderActionField["OrderLocalID"] = "string"
#操作本地编号
CThostFtdcOrderActionField["ActionLocalID"] = "string"
#会员代码
CThostFtdcOrderActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcOrderActionField["ClientID"] = "string"
#业务单元
CThostFtdcOrderActionField["BusinessUnit"] = "string"
#报单操作状态
CThostFtdcOrderActionField["OrderActionStatus"] = "char"
#用户代码
CThostFtdcOrderActionField["UserID"] = "string"
#状态信息
CThostFtdcOrderActionField["StatusMsg"] = "string"
#合约代码
CThostFtdcOrderActionField["InstrumentID"] = "string"
#营业部编号
CThostFtdcOrderActionField["BranchID"] = "string"
#投资单元代码
CThostFtdcOrderActionField["InvestUnitID"] = "string"
#IP地址
CThostFtdcOrderActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcOrderActionField["MacAddress"] = "string"
structDict['CThostFtdcOrderActionField'] = CThostFtdcOrderActionField


#交易所报单操作
CThostFtdcExchangeOrderActionField = {}
#交易所代码
CThostFtdcExchangeOrderActionField["ExchangeID"] = "string"
#报单编号
CThostFtdcExchangeOrderActionField["OrderSysID"] = "string"
#操作标志
CThostFtdcExchangeOrderActionField["ActionFlag"] = "char"
#价格
CThostFtdcExchangeOrderActionField["LimitPrice"] = "float"
#数量变化
CThostFtdcExchangeOrderActionField["VolumeChange"] = "int"
#操作日期
CThostFtdcExchangeOrderActionField["ActionDate"] = "string"
#操作时间
CThostFtdcExchangeOrderActionField["ActionTime"] = "string"
#交易所交易员代码
CThostFtdcExchangeOrderActionField["TraderID"] = "string"
#安装编号
CThostFtdcExchangeOrderActionField["InstallID"] = "int"
#本地报单编号
CThostFtdcExchangeOrderActionField["OrderLocalID"] = "string"
#操作本地编号
CThostFtdcExchangeOrderActionField["ActionLocalID"] = "string"
#会员代码
CThostFtdcExchangeOrderActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcExchangeOrderActionField["ClientID"] = "string"
#业务单元
CThostFtdcExchangeOrderActionField["BusinessUnit"] = "string"
#报单操作状态
CThostFtdcExchangeOrderActionField["OrderActionStatus"] = "char"
#用户代码
CThostFtdcExchangeOrderActionField["UserID"] = "string"
#营业部编号
CThostFtdcExchangeOrderActionField["BranchID"] = "string"
#IP地址
CThostFtdcExchangeOrderActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcExchangeOrderActionField["MacAddress"] = "string"
structDict['CThostFtdcExchangeOrderActionField'] = CThostFtdcExchangeOrderActionField


#交易所报单操作失败
CThostFtdcExchangeOrderActionErrorField = {}
#交易所代码
CThostFtdcExchangeOrderActionErrorField["ExchangeID"] = "string"
#报单编号
CThostFtdcExchangeOrderActionErrorField["OrderSysID"] = "string"
#交易所交易员代码
CThostFtdcExchangeOrderActionErrorField["TraderID"] = "string"
#安装编号
CThostFtdcExchangeOrderActionErrorField["InstallID"] = "int"
#本地报单编号
CThostFtdcExchangeOrderActionErrorField["OrderLocalID"] = "string"
#操作本地编号
CThostFtdcExchangeOrderActionErrorField["ActionLocalID"] = "string"
#错误代码
CThostFtdcExchangeOrderActionErrorField["ErrorID"] = "int"
#错误信息
CThostFtdcExchangeOrderActionErrorField["ErrorMsg"] = "string"
structDict['CThostFtdcExchangeOrderActionErrorField'] = CThostFtdcExchangeOrderActionErrorField


#交易所成交
CThostFtdcExchangeTradeField = {}
#交易所代码
CThostFtdcExchangeTradeField["ExchangeID"] = "string"
#成交编号
CThostFtdcExchangeTradeField["TradeID"] = "string"
#买卖方向
CThostFtdcExchangeTradeField["Direction"] = "char"
#报单编号
CThostFtdcExchangeTradeField["OrderSysID"] = "string"
#会员代码
CThostFtdcExchangeTradeField["ParticipantID"] = "string"
#客户代码
CThostFtdcExchangeTradeField["ClientID"] = "string"
#交易角色
CThostFtdcExchangeTradeField["TradingRole"] = "char"
#合约在交易所的代码
CThostFtdcExchangeTradeField["ExchangeInstID"] = "string"
#开平标志
CThostFtdcExchangeTradeField["OffsetFlag"] = "char"
#投机套保标志
CThostFtdcExchangeTradeField["HedgeFlag"] = "char"
#价格
CThostFtdcExchangeTradeField["Price"] = "float"
#数量
CThostFtdcExchangeTradeField["Volume"] = "int"
#成交时期
CThostFtdcExchangeTradeField["TradeDate"] = "string"
#成交时间
CThostFtdcExchangeTradeField["TradeTime"] = "string"
#成交类型
CThostFtdcExchangeTradeField["TradeType"] = "char"
#成交价来源
CThostFtdcExchangeTradeField["PriceSource"] = "char"
#交易所交易员代码
CThostFtdcExchangeTradeField["TraderID"] = "string"
#本地报单编号
CThostFtdcExchangeTradeField["OrderLocalID"] = "string"
#结算会员编号
CThostFtdcExchangeTradeField["ClearingPartID"] = "string"
#业务单元
CThostFtdcExchangeTradeField["BusinessUnit"] = "string"
#序号
CThostFtdcExchangeTradeField["SequenceNo"] = "int"
#成交来源
CThostFtdcExchangeTradeField["TradeSource"] = "char"
structDict['CThostFtdcExchangeTradeField'] = CThostFtdcExchangeTradeField


#成交
CThostFtdcTradeField = {}
#经纪公司代码
CThostFtdcTradeField["BrokerID"] = "string"
#投资者代码
CThostFtdcTradeField["InvestorID"] = "string"
#合约代码
CThostFtdcTradeField["InstrumentID"] = "string"
#报单引用
CThostFtdcTradeField["OrderRef"] = "string"
#用户代码
CThostFtdcTradeField["UserID"] = "string"
#交易所代码
CThostFtdcTradeField["ExchangeID"] = "string"
#成交编号
CThostFtdcTradeField["TradeID"] = "string"
#买卖方向
CThostFtdcTradeField["Direction"] = "char"
#报单编号
CThostFtdcTradeField["OrderSysID"] = "string"
#会员代码
CThostFtdcTradeField["ParticipantID"] = "string"
#客户代码
CThostFtdcTradeField["ClientID"] = "string"
#交易角色
CThostFtdcTradeField["TradingRole"] = "char"
#合约在交易所的代码
CThostFtdcTradeField["ExchangeInstID"] = "string"
#开平标志
CThostFtdcTradeField["OffsetFlag"] = "char"
#投机套保标志
CThostFtdcTradeField["HedgeFlag"] = "char"
#价格
CThostFtdcTradeField["Price"] = "float"
#数量
CThostFtdcTradeField["Volume"] = "int"
#成交时期
CThostFtdcTradeField["TradeDate"] = "string"
#成交时间
CThostFtdcTradeField["TradeTime"] = "string"
#成交类型
CThostFtdcTradeField["TradeType"] = "char"
#成交价来源
CThostFtdcTradeField["PriceSource"] = "char"
#交易所交易员代码
CThostFtdcTradeField["TraderID"] = "string"
#本地报单编号
CThostFtdcTradeField["OrderLocalID"] = "string"
#结算会员编号
CThostFtdcTradeField["ClearingPartID"] = "string"
#业务单元
CThostFtdcTradeField["BusinessUnit"] = "string"
#序号
CThostFtdcTradeField["SequenceNo"] = "int"
#交易日
CThostFtdcTradeField["TradingDay"] = "string"
#结算编号
CThostFtdcTradeField["SettlementID"] = "int"
#经纪公司报单编号
CThostFtdcTradeField["BrokerOrderSeq"] = "int"
#成交来源
CThostFtdcTradeField["TradeSource"] = "char"
#投资单元代码
CThostFtdcTradeField["InvestUnitID"] = "string"
structDict['CThostFtdcTradeField'] = CThostFtdcTradeField


#用户会话
CThostFtdcUserSessionField = {}
#前置编号
CThostFtdcUserSessionField["FrontID"] = "int"
#会话编号
CThostFtdcUserSessionField["SessionID"] = "int"
#经纪公司代码
CThostFtdcUserSessionField["BrokerID"] = "string"
#用户代码
CThostFtdcUserSessionField["UserID"] = "string"
#登录日期
CThostFtdcUserSessionField["LoginDate"] = "string"
#登录时间
CThostFtdcUserSessionField["LoginTime"] = "string"
#IP地址
CThostFtdcUserSessionField["IPAddress"] = "string"
#用户端产品信息
CThostFtdcUserSessionField["UserProductInfo"] = "string"
#接口端产品信息
CThostFtdcUserSessionField["InterfaceProductInfo"] = "string"
#协议信息
CThostFtdcUserSessionField["ProtocolInfo"] = "string"
#Mac地址
CThostFtdcUserSessionField["MacAddress"] = "string"
#登录备注
CThostFtdcUserSessionField["LoginRemark"] = "string"
structDict['CThostFtdcUserSessionField'] = CThostFtdcUserSessionField


#查询最大报单数量
CThostFtdcQueryMaxOrderVolumeField = {}
#经纪公司代码
CThostFtdcQueryMaxOrderVolumeField["BrokerID"] = "string"
#投资者代码
CThostFtdcQueryMaxOrderVolumeField["InvestorID"] = "string"
#合约代码
CThostFtdcQueryMaxOrderVolumeField["InstrumentID"] = "string"
#买卖方向
CThostFtdcQueryMaxOrderVolumeField["Direction"] = "char"
#开平标志
CThostFtdcQueryMaxOrderVolumeField["OffsetFlag"] = "char"
#投机套保标志
CThostFtdcQueryMaxOrderVolumeField["HedgeFlag"] = "char"
#最大允许报单数量
CThostFtdcQueryMaxOrderVolumeField["MaxVolume"] = "int"
#交易所代码
CThostFtdcQueryMaxOrderVolumeField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcQueryMaxOrderVolumeField["InvestUnitID"] = "string"
structDict['CThostFtdcQueryMaxOrderVolumeField'] = CThostFtdcQueryMaxOrderVolumeField


#投资者结算结果确认信息
CThostFtdcSettlementInfoConfirmField = {}
#经纪公司代码
CThostFtdcSettlementInfoConfirmField["BrokerID"] = "string"
#投资者代码
CThostFtdcSettlementInfoConfirmField["InvestorID"] = "string"
#确认日期
CThostFtdcSettlementInfoConfirmField["ConfirmDate"] = "string"
#确认时间
CThostFtdcSettlementInfoConfirmField["ConfirmTime"] = "string"
#结算编号
CThostFtdcSettlementInfoConfirmField["SettlementID"] = "int"
#投资者帐号
CThostFtdcSettlementInfoConfirmField["AccountID"] = "string"
#币种代码
CThostFtdcSettlementInfoConfirmField["CurrencyID"] = "string"
structDict['CThostFtdcSettlementInfoConfirmField'] = CThostFtdcSettlementInfoConfirmField


#出入金同步
CThostFtdcSyncDepositField = {}
#出入金流水号
CThostFtdcSyncDepositField["DepositSeqNo"] = "string"
#经纪公司代码
CThostFtdcSyncDepositField["BrokerID"] = "string"
#投资者代码
CThostFtdcSyncDepositField["InvestorID"] = "string"
#入金金额
CThostFtdcSyncDepositField["Deposit"] = "float"
#是否强制进行
CThostFtdcSyncDepositField["IsForce"] = "int"
#币种代码
CThostFtdcSyncDepositField["CurrencyID"] = "string"
structDict['CThostFtdcSyncDepositField'] = CThostFtdcSyncDepositField


#货币质押同步
CThostFtdcSyncFundMortgageField = {}
#货币质押流水号
CThostFtdcSyncFundMortgageField["MortgageSeqNo"] = "string"
#经纪公司代码
CThostFtdcSyncFundMortgageField["BrokerID"] = "string"
#投资者代码
CThostFtdcSyncFundMortgageField["InvestorID"] = "string"
#源币种
CThostFtdcSyncFundMortgageField["FromCurrencyID"] = "string"
#质押金额
CThostFtdcSyncFundMortgageField["MortgageAmount"] = "float"
#目标币种
CThostFtdcSyncFundMortgageField["ToCurrencyID"] = "string"
structDict['CThostFtdcSyncFundMortgageField'] = CThostFtdcSyncFundMortgageField


#经纪公司同步
CThostFtdcBrokerSyncField = {}
#经纪公司代码
CThostFtdcBrokerSyncField["BrokerID"] = "string"
structDict['CThostFtdcBrokerSyncField'] = CThostFtdcBrokerSyncField


#正在同步中的投资者
CThostFtdcSyncingInvestorField = {}
#投资者代码
CThostFtdcSyncingInvestorField["InvestorID"] = "string"
#经纪公司代码
CThostFtdcSyncingInvestorField["BrokerID"] = "string"
#投资者分组代码
CThostFtdcSyncingInvestorField["InvestorGroupID"] = "string"
#投资者名称
CThostFtdcSyncingInvestorField["InvestorName"] = "string"
#证件类型
CThostFtdcSyncingInvestorField["IdentifiedCardType"] = "char"
#证件号码
CThostFtdcSyncingInvestorField["IdentifiedCardNo"] = "string"
#是否活跃
CThostFtdcSyncingInvestorField["IsActive"] = "int"
#联系电话
CThostFtdcSyncingInvestorField["Telephone"] = "string"
#通讯地址
CThostFtdcSyncingInvestorField["Address"] = "string"
#开户日期
CThostFtdcSyncingInvestorField["OpenDate"] = "string"
#手机
CThostFtdcSyncingInvestorField["Mobile"] = "string"
#手续费率模板代码
CThostFtdcSyncingInvestorField["CommModelID"] = "string"
#保证金率模板代码
CThostFtdcSyncingInvestorField["MarginModelID"] = "string"
structDict['CThostFtdcSyncingInvestorField'] = CThostFtdcSyncingInvestorField


#正在同步中的交易代码
CThostFtdcSyncingTradingCodeField = {}
#投资者代码
CThostFtdcSyncingTradingCodeField["InvestorID"] = "string"
#经纪公司代码
CThostFtdcSyncingTradingCodeField["BrokerID"] = "string"
#交易所代码
CThostFtdcSyncingTradingCodeField["ExchangeID"] = "string"
#客户代码
CThostFtdcSyncingTradingCodeField["ClientID"] = "string"
#是否活跃
CThostFtdcSyncingTradingCodeField["IsActive"] = "int"
#交易编码类型
CThostFtdcSyncingTradingCodeField["ClientIDType"] = "char"
structDict['CThostFtdcSyncingTradingCodeField'] = CThostFtdcSyncingTradingCodeField


#正在同步中的投资者分组
CThostFtdcSyncingInvestorGroupField = {}
#经纪公司代码
CThostFtdcSyncingInvestorGroupField["BrokerID"] = "string"
#投资者分组代码
CThostFtdcSyncingInvestorGroupField["InvestorGroupID"] = "string"
#投资者分组名称
CThostFtdcSyncingInvestorGroupField["InvestorGroupName"] = "string"
structDict['CThostFtdcSyncingInvestorGroupField'] = CThostFtdcSyncingInvestorGroupField


#正在同步中的交易账号
CThostFtdcSyncingTradingAccountField = {}
#经纪公司代码
CThostFtdcSyncingTradingAccountField["BrokerID"] = "string"
#投资者帐号
CThostFtdcSyncingTradingAccountField["AccountID"] = "string"
#上次质押金额
CThostFtdcSyncingTradingAccountField["PreMortgage"] = "float"
#上次信用额度
CThostFtdcSyncingTradingAccountField["PreCredit"] = "float"
#上次存款额
CThostFtdcSyncingTradingAccountField["PreDeposit"] = "float"
#上次结算准备金
CThostFtdcSyncingTradingAccountField["PreBalance"] = "float"
#上次占用的保证金
CThostFtdcSyncingTradingAccountField["PreMargin"] = "float"
#利息基数
CThostFtdcSyncingTradingAccountField["InterestBase"] = "float"
#利息收入
CThostFtdcSyncingTradingAccountField["Interest"] = "float"
#入金金额
CThostFtdcSyncingTradingAccountField["Deposit"] = "float"
#出金金额
CThostFtdcSyncingTradingAccountField["Withdraw"] = "float"
#冻结的保证金
CThostFtdcSyncingTradingAccountField["FrozenMargin"] = "float"
#冻结的资金
CThostFtdcSyncingTradingAccountField["FrozenCash"] = "float"
#冻结的手续费
CThostFtdcSyncingTradingAccountField["FrozenCommission"] = "float"
#当前保证金总额
CThostFtdcSyncingTradingAccountField["CurrMargin"] = "float"
#资金差额
CThostFtdcSyncingTradingAccountField["CashIn"] = "float"
#手续费
CThostFtdcSyncingTradingAccountField["Commission"] = "float"
#平仓盈亏
CThostFtdcSyncingTradingAccountField["CloseProfit"] = "float"
#持仓盈亏
CThostFtdcSyncingTradingAccountField["PositionProfit"] = "float"
#期货结算准备金
CThostFtdcSyncingTradingAccountField["Balance"] = "float"
#可用资金
CThostFtdcSyncingTradingAccountField["Available"] = "float"
#可取资金
CThostFtdcSyncingTradingAccountField["WithdrawQuota"] = "float"
#基本准备金
CThostFtdcSyncingTradingAccountField["Reserve"] = "float"
#交易日
CThostFtdcSyncingTradingAccountField["TradingDay"] = "string"
#结算编号
CThostFtdcSyncingTradingAccountField["SettlementID"] = "int"
#信用额度
CThostFtdcSyncingTradingAccountField["Credit"] = "float"
#质押金额
CThostFtdcSyncingTradingAccountField["Mortgage"] = "float"
#交易所保证金
CThostFtdcSyncingTradingAccountField["ExchangeMargin"] = "float"
#投资者交割保证金
CThostFtdcSyncingTradingAccountField["DeliveryMargin"] = "float"
#交易所交割保证金
CThostFtdcSyncingTradingAccountField["ExchangeDeliveryMargin"] = "float"
#保底期货结算准备金
CThostFtdcSyncingTradingAccountField["ReserveBalance"] = "float"
#币种代码
CThostFtdcSyncingTradingAccountField["CurrencyID"] = "string"
#上次货币质入金额
CThostFtdcSyncingTradingAccountField["PreFundMortgageIn"] = "float"
#上次货币质出金额
CThostFtdcSyncingTradingAccountField["PreFundMortgageOut"] = "float"
#货币质入金额
CThostFtdcSyncingTradingAccountField["FundMortgageIn"] = "float"
#货币质出金额
CThostFtdcSyncingTradingAccountField["FundMortgageOut"] = "float"
#货币质押余额
CThostFtdcSyncingTradingAccountField["FundMortgageAvailable"] = "float"
#可质押货币金额
CThostFtdcSyncingTradingAccountField["MortgageableFund"] = "float"
#特殊产品占用保证金
CThostFtdcSyncingTradingAccountField["SpecProductMargin"] = "float"
#特殊产品冻结保证金
CThostFtdcSyncingTradingAccountField["SpecProductFrozenMargin"] = "float"
#特殊产品手续费
CThostFtdcSyncingTradingAccountField["SpecProductCommission"] = "float"
#特殊产品冻结手续费
CThostFtdcSyncingTradingAccountField["SpecProductFrozenCommission"] = "float"
#特殊产品持仓盈亏
CThostFtdcSyncingTradingAccountField["SpecProductPositionProfit"] = "float"
#特殊产品平仓盈亏
CThostFtdcSyncingTradingAccountField["SpecProductCloseProfit"] = "float"
#根据持仓盈亏算法计算的特殊产品持仓盈亏
CThostFtdcSyncingTradingAccountField["SpecProductPositionProfitByAlg"] = "float"
#特殊产品交易所保证金
CThostFtdcSyncingTradingAccountField["SpecProductExchangeMargin"] = "float"
#延时换汇冻结金额
CThostFtdcSyncingTradingAccountField["FrozenSwap"] = "float"
#剩余换汇额度
CThostFtdcSyncingTradingAccountField["RemainSwap"] = "float"
structDict['CThostFtdcSyncingTradingAccountField'] = CThostFtdcSyncingTradingAccountField


#正在同步中的投资者持仓
CThostFtdcSyncingInvestorPositionField = {}
#合约代码
CThostFtdcSyncingInvestorPositionField["InstrumentID"] = "string"
#经纪公司代码
CThostFtdcSyncingInvestorPositionField["BrokerID"] = "string"
#投资者代码
CThostFtdcSyncingInvestorPositionField["InvestorID"] = "string"
#持仓多空方向
CThostFtdcSyncingInvestorPositionField["PosiDirection"] = "char"
#投机套保标志
CThostFtdcSyncingInvestorPositionField["HedgeFlag"] = "char"
#持仓日期
CThostFtdcSyncingInvestorPositionField["PositionDate"] = "char"
#上日持仓
CThostFtdcSyncingInvestorPositionField["YdPosition"] = "int"
#今日持仓
CThostFtdcSyncingInvestorPositionField["Position"] = "int"
#多头冻结
CThostFtdcSyncingInvestorPositionField["LongFrozen"] = "int"
#空头冻结
CThostFtdcSyncingInvestorPositionField["ShortFrozen"] = "int"
#开仓冻结金额
CThostFtdcSyncingInvestorPositionField["LongFrozenAmount"] = "float"
#开仓冻结金额
CThostFtdcSyncingInvestorPositionField["ShortFrozenAmount"] = "float"
#开仓量
CThostFtdcSyncingInvestorPositionField["OpenVolume"] = "int"
#平仓量
CThostFtdcSyncingInvestorPositionField["CloseVolume"] = "int"
#开仓金额
CThostFtdcSyncingInvestorPositionField["OpenAmount"] = "float"
#平仓金额
CThostFtdcSyncingInvestorPositionField["CloseAmount"] = "float"
#持仓成本
CThostFtdcSyncingInvestorPositionField["PositionCost"] = "float"
#上次占用的保证金
CThostFtdcSyncingInvestorPositionField["PreMargin"] = "float"
#占用的保证金
CThostFtdcSyncingInvestorPositionField["UseMargin"] = "float"
#冻结的保证金
CThostFtdcSyncingInvestorPositionField["FrozenMargin"] = "float"
#冻结的资金
CThostFtdcSyncingInvestorPositionField["FrozenCash"] = "float"
#冻结的手续费
CThostFtdcSyncingInvestorPositionField["FrozenCommission"] = "float"
#资金差额
CThostFtdcSyncingInvestorPositionField["CashIn"] = "float"
#手续费
CThostFtdcSyncingInvestorPositionField["Commission"] = "float"
#平仓盈亏
CThostFtdcSyncingInvestorPositionField["CloseProfit"] = "float"
#持仓盈亏
CThostFtdcSyncingInvestorPositionField["PositionProfit"] = "float"
#上次结算价
CThostFtdcSyncingInvestorPositionField["PreSettlementPrice"] = "float"
#本次结算价
CThostFtdcSyncingInvestorPositionField["SettlementPrice"] = "float"
#交易日
CThostFtdcSyncingInvestorPositionField["TradingDay"] = "string"
#结算编号
CThostFtdcSyncingInvestorPositionField["SettlementID"] = "int"
#开仓成本
CThostFtdcSyncingInvestorPositionField["OpenCost"] = "float"
#交易所保证金
CThostFtdcSyncingInvestorPositionField["ExchangeMargin"] = "float"
#组合成交形成的持仓
CThostFtdcSyncingInvestorPositionField["CombPosition"] = "int"
#组合多头冻结
CThostFtdcSyncingInvestorPositionField["CombLongFrozen"] = "int"
#组合空头冻结
CThostFtdcSyncingInvestorPositionField["CombShortFrozen"] = "int"
#逐日盯市平仓盈亏
CThostFtdcSyncingInvestorPositionField["CloseProfitByDate"] = "float"
#逐笔对冲平仓盈亏
CThostFtdcSyncingInvestorPositionField["CloseProfitByTrade"] = "float"
#今日持仓
CThostFtdcSyncingInvestorPositionField["TodayPosition"] = "int"
#保证金率
CThostFtdcSyncingInvestorPositionField["MarginRateByMoney"] = "float"
#保证金率(按手数)
CThostFtdcSyncingInvestorPositionField["MarginRateByVolume"] = "float"
#执行冻结
CThostFtdcSyncingInvestorPositionField["StrikeFrozen"] = "int"
#执行冻结金额
CThostFtdcSyncingInvestorPositionField["StrikeFrozenAmount"] = "float"
#放弃执行冻结
CThostFtdcSyncingInvestorPositionField["AbandonFrozen"] = "int"
#交易所代码
CThostFtdcSyncingInvestorPositionField["ExchangeID"] = "string"
#执行冻结的昨仓
CThostFtdcSyncingInvestorPositionField["YdStrikeFrozen"] = "int"
#投资单元代码
CThostFtdcSyncingInvestorPositionField["InvestUnitID"] = "string"
structDict['CThostFtdcSyncingInvestorPositionField'] = CThostFtdcSyncingInvestorPositionField


#正在同步中的合约保证金率
CThostFtdcSyncingInstrumentMarginRateField = {}
#合约代码
CThostFtdcSyncingInstrumentMarginRateField["InstrumentID"] = "string"
#投资者范围
CThostFtdcSyncingInstrumentMarginRateField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcSyncingInstrumentMarginRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcSyncingInstrumentMarginRateField["InvestorID"] = "string"
#投机套保标志
CThostFtdcSyncingInstrumentMarginRateField["HedgeFlag"] = "char"
#多头保证金率
CThostFtdcSyncingInstrumentMarginRateField["LongMarginRatioByMoney"] = "float"
#多头保证金费
CThostFtdcSyncingInstrumentMarginRateField["LongMarginRatioByVolume"] = "float"
#空头保证金率
CThostFtdcSyncingInstrumentMarginRateField["ShortMarginRatioByMoney"] = "float"
#空头保证金费
CThostFtdcSyncingInstrumentMarginRateField["ShortMarginRatioByVolume"] = "float"
#是否相对交易所收取
CThostFtdcSyncingInstrumentMarginRateField["IsRelative"] = "int"
structDict['CThostFtdcSyncingInstrumentMarginRateField'] = CThostFtdcSyncingInstrumentMarginRateField


#正在同步中的合约手续费率
CThostFtdcSyncingInstrumentCommissionRateField = {}
#合约代码
CThostFtdcSyncingInstrumentCommissionRateField["InstrumentID"] = "string"
#投资者范围
CThostFtdcSyncingInstrumentCommissionRateField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcSyncingInstrumentCommissionRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcSyncingInstrumentCommissionRateField["InvestorID"] = "string"
#开仓手续费率
CThostFtdcSyncingInstrumentCommissionRateField["OpenRatioByMoney"] = "float"
#开仓手续费
CThostFtdcSyncingInstrumentCommissionRateField["OpenRatioByVolume"] = "float"
#平仓手续费率
CThostFtdcSyncingInstrumentCommissionRateField["CloseRatioByMoney"] = "float"
#平仓手续费
CThostFtdcSyncingInstrumentCommissionRateField["CloseRatioByVolume"] = "float"
#平今手续费率
CThostFtdcSyncingInstrumentCommissionRateField["CloseTodayRatioByMoney"] = "float"
#平今手续费
CThostFtdcSyncingInstrumentCommissionRateField["CloseTodayRatioByVolume"] = "float"
structDict['CThostFtdcSyncingInstrumentCommissionRateField'] = CThostFtdcSyncingInstrumentCommissionRateField


#正在同步中的合约交易权限
CThostFtdcSyncingInstrumentTradingRightField = {}
#合约代码
CThostFtdcSyncingInstrumentTradingRightField["InstrumentID"] = "string"
#投资者范围
CThostFtdcSyncingInstrumentTradingRightField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcSyncingInstrumentTradingRightField["BrokerID"] = "string"
#投资者代码
CThostFtdcSyncingInstrumentTradingRightField["InvestorID"] = "string"
#交易权限
CThostFtdcSyncingInstrumentTradingRightField["TradingRight"] = "char"
structDict['CThostFtdcSyncingInstrumentTradingRightField'] = CThostFtdcSyncingInstrumentTradingRightField


#查询报单
CThostFtdcQryOrderField = {}
#经纪公司代码
CThostFtdcQryOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryOrderField["InvestorID"] = "string"
#合约代码
CThostFtdcQryOrderField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryOrderField["ExchangeID"] = "string"
#报单编号
CThostFtdcQryOrderField["OrderSysID"] = "string"
#开始时间
CThostFtdcQryOrderField["InsertTimeStart"] = "string"
#结束时间
CThostFtdcQryOrderField["InsertTimeEnd"] = "string"
#投资单元代码
CThostFtdcQryOrderField["InvestUnitID"] = "string"
structDict['CThostFtdcQryOrderField'] = CThostFtdcQryOrderField


#查询成交
CThostFtdcQryTradeField = {}
#经纪公司代码
CThostFtdcQryTradeField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryTradeField["InvestorID"] = "string"
#合约代码
CThostFtdcQryTradeField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryTradeField["ExchangeID"] = "string"
#成交编号
CThostFtdcQryTradeField["TradeID"] = "string"
#开始时间
CThostFtdcQryTradeField["TradeTimeStart"] = "string"
#结束时间
CThostFtdcQryTradeField["TradeTimeEnd"] = "string"
#投资单元代码
CThostFtdcQryTradeField["InvestUnitID"] = "string"
structDict['CThostFtdcQryTradeField'] = CThostFtdcQryTradeField


#查询投资者持仓
CThostFtdcQryInvestorPositionField = {}
#经纪公司代码
CThostFtdcQryInvestorPositionField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryInvestorPositionField["InvestorID"] = "string"
#合约代码
CThostFtdcQryInvestorPositionField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryInvestorPositionField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcQryInvestorPositionField["InvestUnitID"] = "string"
structDict['CThostFtdcQryInvestorPositionField'] = CThostFtdcQryInvestorPositionField


#查询资金账户
CThostFtdcQryTradingAccountField = {}
#经纪公司代码
CThostFtdcQryTradingAccountField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryTradingAccountField["InvestorID"] = "string"
#币种代码
CThostFtdcQryTradingAccountField["CurrencyID"] = "string"
#业务类型
CThostFtdcQryTradingAccountField["BizType"] = "char"
#投资者帐号
CThostFtdcQryTradingAccountField["AccountID"] = "string"
structDict['CThostFtdcQryTradingAccountField'] = CThostFtdcQryTradingAccountField


#查询投资者
CThostFtdcQryInvestorField = {}
#经纪公司代码
CThostFtdcQryInvestorField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryInvestorField["InvestorID"] = "string"
structDict['CThostFtdcQryInvestorField'] = CThostFtdcQryInvestorField


#查询交易编码
CThostFtdcQryTradingCodeField = {}
#经纪公司代码
CThostFtdcQryTradingCodeField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryTradingCodeField["InvestorID"] = "string"
#交易所代码
CThostFtdcQryTradingCodeField["ExchangeID"] = "string"
#客户代码
CThostFtdcQryTradingCodeField["ClientID"] = "string"
#交易编码类型
CThostFtdcQryTradingCodeField["ClientIDType"] = "char"
#投资单元代码
CThostFtdcQryTradingCodeField["InvestUnitID"] = "string"
structDict['CThostFtdcQryTradingCodeField'] = CThostFtdcQryTradingCodeField


#查询投资者组
CThostFtdcQryInvestorGroupField = {}
#经纪公司代码
CThostFtdcQryInvestorGroupField["BrokerID"] = "string"
structDict['CThostFtdcQryInvestorGroupField'] = CThostFtdcQryInvestorGroupField


#查询合约保证金率
CThostFtdcQryInstrumentMarginRateField = {}
#经纪公司代码
CThostFtdcQryInstrumentMarginRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryInstrumentMarginRateField["InvestorID"] = "string"
#合约代码
CThostFtdcQryInstrumentMarginRateField["InstrumentID"] = "string"
#投机套保标志
CThostFtdcQryInstrumentMarginRateField["HedgeFlag"] = "char"
#交易所代码
CThostFtdcQryInstrumentMarginRateField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcQryInstrumentMarginRateField["InvestUnitID"] = "string"
structDict['CThostFtdcQryInstrumentMarginRateField'] = CThostFtdcQryInstrumentMarginRateField


#查询手续费率
CThostFtdcQryInstrumentCommissionRateField = {}
#经纪公司代码
CThostFtdcQryInstrumentCommissionRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryInstrumentCommissionRateField["InvestorID"] = "string"
#合约代码
CThostFtdcQryInstrumentCommissionRateField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryInstrumentCommissionRateField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcQryInstrumentCommissionRateField["InvestUnitID"] = "string"
structDict['CThostFtdcQryInstrumentCommissionRateField'] = CThostFtdcQryInstrumentCommissionRateField


#查询合约交易权限
CThostFtdcQryInstrumentTradingRightField = {}
#经纪公司代码
CThostFtdcQryInstrumentTradingRightField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryInstrumentTradingRightField["InvestorID"] = "string"
#合约代码
CThostFtdcQryInstrumentTradingRightField["InstrumentID"] = "string"
structDict['CThostFtdcQryInstrumentTradingRightField'] = CThostFtdcQryInstrumentTradingRightField


#查询经纪公司
CThostFtdcQryBrokerField = {}
#经纪公司代码
CThostFtdcQryBrokerField["BrokerID"] = "string"
structDict['CThostFtdcQryBrokerField'] = CThostFtdcQryBrokerField


#查询交易员
CThostFtdcQryTraderField = {}
#交易所代码
CThostFtdcQryTraderField["ExchangeID"] = "string"
#会员代码
CThostFtdcQryTraderField["ParticipantID"] = "string"
#交易所交易员代码
CThostFtdcQryTraderField["TraderID"] = "string"
structDict['CThostFtdcQryTraderField'] = CThostFtdcQryTraderField


#查询管理用户功能权限
CThostFtdcQrySuperUserFunctionField = {}
#用户代码
CThostFtdcQrySuperUserFunctionField["UserID"] = "string"
structDict['CThostFtdcQrySuperUserFunctionField'] = CThostFtdcQrySuperUserFunctionField


#查询用户会话
CThostFtdcQryUserSessionField = {}
#前置编号
CThostFtdcQryUserSessionField["FrontID"] = "int"
#会话编号
CThostFtdcQryUserSessionField["SessionID"] = "int"
#经纪公司代码
CThostFtdcQryUserSessionField["BrokerID"] = "string"
#用户代码
CThostFtdcQryUserSessionField["UserID"] = "string"
structDict['CThostFtdcQryUserSessionField'] = CThostFtdcQryUserSessionField


#查询经纪公司会员代码
CThostFtdcQryPartBrokerField = {}
#交易所代码
CThostFtdcQryPartBrokerField["ExchangeID"] = "string"
#经纪公司代码
CThostFtdcQryPartBrokerField["BrokerID"] = "string"
#会员代码
CThostFtdcQryPartBrokerField["ParticipantID"] = "string"
structDict['CThostFtdcQryPartBrokerField'] = CThostFtdcQryPartBrokerField


#查询前置状态
CThostFtdcQryFrontStatusField = {}
#前置编号
CThostFtdcQryFrontStatusField["FrontID"] = "int"
structDict['CThostFtdcQryFrontStatusField'] = CThostFtdcQryFrontStatusField


#查询交易所报单
CThostFtdcQryExchangeOrderField = {}
#会员代码
CThostFtdcQryExchangeOrderField["ParticipantID"] = "string"
#客户代码
CThostFtdcQryExchangeOrderField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcQryExchangeOrderField["ExchangeInstID"] = "string"
#交易所代码
CThostFtdcQryExchangeOrderField["ExchangeID"] = "string"
#交易所交易员代码
CThostFtdcQryExchangeOrderField["TraderID"] = "string"
structDict['CThostFtdcQryExchangeOrderField'] = CThostFtdcQryExchangeOrderField


#查询报单操作
CThostFtdcQryOrderActionField = {}
#经纪公司代码
CThostFtdcQryOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryOrderActionField["InvestorID"] = "string"
#交易所代码
CThostFtdcQryOrderActionField["ExchangeID"] = "string"
structDict['CThostFtdcQryOrderActionField'] = CThostFtdcQryOrderActionField


#查询交易所报单操作
CThostFtdcQryExchangeOrderActionField = {}
#会员代码
CThostFtdcQryExchangeOrderActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcQryExchangeOrderActionField["ClientID"] = "string"
#交易所代码
CThostFtdcQryExchangeOrderActionField["ExchangeID"] = "string"
#交易所交易员代码
CThostFtdcQryExchangeOrderActionField["TraderID"] = "string"
structDict['CThostFtdcQryExchangeOrderActionField'] = CThostFtdcQryExchangeOrderActionField


#查询管理用户
CThostFtdcQrySuperUserField = {}
#用户代码
CThostFtdcQrySuperUserField["UserID"] = "string"
structDict['CThostFtdcQrySuperUserField'] = CThostFtdcQrySuperUserField


#查询交易所
CThostFtdcQryExchangeField = {}
#交易所代码
CThostFtdcQryExchangeField["ExchangeID"] = "string"
structDict['CThostFtdcQryExchangeField'] = CThostFtdcQryExchangeField


#查询产品
CThostFtdcQryProductField = {}
#产品代码
CThostFtdcQryProductField["ProductID"] = "string"
#产品类型
CThostFtdcQryProductField["ProductClass"] = "char"
#交易所代码
CThostFtdcQryProductField["ExchangeID"] = "string"
structDict['CThostFtdcQryProductField'] = CThostFtdcQryProductField


#查询合约
CThostFtdcQryInstrumentField = {}
#合约代码
CThostFtdcQryInstrumentField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryInstrumentField["ExchangeID"] = "string"
#合约在交易所的代码
CThostFtdcQryInstrumentField["ExchangeInstID"] = "string"
#产品代码
CThostFtdcQryInstrumentField["ProductID"] = "string"
structDict['CThostFtdcQryInstrumentField'] = CThostFtdcQryInstrumentField


#查询行情
CThostFtdcQryDepthMarketDataField = {}
#合约代码
CThostFtdcQryDepthMarketDataField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryDepthMarketDataField["ExchangeID"] = "string"
structDict['CThostFtdcQryDepthMarketDataField'] = CThostFtdcQryDepthMarketDataField


#查询经纪公司用户
CThostFtdcQryBrokerUserField = {}
#经纪公司代码
CThostFtdcQryBrokerUserField["BrokerID"] = "string"
#用户代码
CThostFtdcQryBrokerUserField["UserID"] = "string"
structDict['CThostFtdcQryBrokerUserField'] = CThostFtdcQryBrokerUserField


#查询经纪公司用户权限
CThostFtdcQryBrokerUserFunctionField = {}
#经纪公司代码
CThostFtdcQryBrokerUserFunctionField["BrokerID"] = "string"
#用户代码
CThostFtdcQryBrokerUserFunctionField["UserID"] = "string"
structDict['CThostFtdcQryBrokerUserFunctionField'] = CThostFtdcQryBrokerUserFunctionField


#查询交易员报盘机
CThostFtdcQryTraderOfferField = {}
#交易所代码
CThostFtdcQryTraderOfferField["ExchangeID"] = "string"
#会员代码
CThostFtdcQryTraderOfferField["ParticipantID"] = "string"
#交易所交易员代码
CThostFtdcQryTraderOfferField["TraderID"] = "string"
structDict['CThostFtdcQryTraderOfferField'] = CThostFtdcQryTraderOfferField


#查询出入金流水
CThostFtdcQrySyncDepositField = {}
#经纪公司代码
CThostFtdcQrySyncDepositField["BrokerID"] = "string"
#出入金流水号
CThostFtdcQrySyncDepositField["DepositSeqNo"] = "string"
structDict['CThostFtdcQrySyncDepositField'] = CThostFtdcQrySyncDepositField


#查询投资者结算结果
CThostFtdcQrySettlementInfoField = {}
#经纪公司代码
CThostFtdcQrySettlementInfoField["BrokerID"] = "string"
#投资者代码
CThostFtdcQrySettlementInfoField["InvestorID"] = "string"
#交易日
CThostFtdcQrySettlementInfoField["TradingDay"] = "string"
#投资者帐号
CThostFtdcQrySettlementInfoField["AccountID"] = "string"
#币种代码
CThostFtdcQrySettlementInfoField["CurrencyID"] = "string"
structDict['CThostFtdcQrySettlementInfoField'] = CThostFtdcQrySettlementInfoField


#查询交易所保证金率
CThostFtdcQryExchangeMarginRateField = {}
#经纪公司代码
CThostFtdcQryExchangeMarginRateField["BrokerID"] = "string"
#合约代码
CThostFtdcQryExchangeMarginRateField["InstrumentID"] = "string"
#投机套保标志
CThostFtdcQryExchangeMarginRateField["HedgeFlag"] = "char"
#交易所代码
CThostFtdcQryExchangeMarginRateField["ExchangeID"] = "string"
structDict['CThostFtdcQryExchangeMarginRateField'] = CThostFtdcQryExchangeMarginRateField


#查询交易所调整保证金率
CThostFtdcQryExchangeMarginRateAdjustField = {}
#经纪公司代码
CThostFtdcQryExchangeMarginRateAdjustField["BrokerID"] = "string"
#合约代码
CThostFtdcQryExchangeMarginRateAdjustField["InstrumentID"] = "string"
#投机套保标志
CThostFtdcQryExchangeMarginRateAdjustField["HedgeFlag"] = "char"
structDict['CThostFtdcQryExchangeMarginRateAdjustField'] = CThostFtdcQryExchangeMarginRateAdjustField


#查询汇率
CThostFtdcQryExchangeRateField = {}
#经纪公司代码
CThostFtdcQryExchangeRateField["BrokerID"] = "string"
#源币种
CThostFtdcQryExchangeRateField["FromCurrencyID"] = "string"
#目标币种
CThostFtdcQryExchangeRateField["ToCurrencyID"] = "string"
structDict['CThostFtdcQryExchangeRateField'] = CThostFtdcQryExchangeRateField


#查询货币质押流水
CThostFtdcQrySyncFundMortgageField = {}
#经纪公司代码
CThostFtdcQrySyncFundMortgageField["BrokerID"] = "string"
#货币质押流水号
CThostFtdcQrySyncFundMortgageField["MortgageSeqNo"] = "string"
structDict['CThostFtdcQrySyncFundMortgageField'] = CThostFtdcQrySyncFundMortgageField


#查询报单
CThostFtdcQryHisOrderField = {}
#经纪公司代码
CThostFtdcQryHisOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryHisOrderField["InvestorID"] = "string"
#合约代码
CThostFtdcQryHisOrderField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryHisOrderField["ExchangeID"] = "string"
#报单编号
CThostFtdcQryHisOrderField["OrderSysID"] = "string"
#开始时间
CThostFtdcQryHisOrderField["InsertTimeStart"] = "string"
#结束时间
CThostFtdcQryHisOrderField["InsertTimeEnd"] = "string"
#交易日
CThostFtdcQryHisOrderField["TradingDay"] = "string"
#结算编号
CThostFtdcQryHisOrderField["SettlementID"] = "int"
structDict['CThostFtdcQryHisOrderField'] = CThostFtdcQryHisOrderField


#当前期权合约最小保证金
CThostFtdcOptionInstrMiniMarginField = {}
#合约代码
CThostFtdcOptionInstrMiniMarginField["InstrumentID"] = "string"
#投资者范围
CThostFtdcOptionInstrMiniMarginField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcOptionInstrMiniMarginField["BrokerID"] = "string"
#投资者代码
CThostFtdcOptionInstrMiniMarginField["InvestorID"] = "string"
#单位（手）期权合约最小保证金
CThostFtdcOptionInstrMiniMarginField["MinMargin"] = "float"
#取值方式
CThostFtdcOptionInstrMiniMarginField["ValueMethod"] = "char"
#是否跟随交易所收取
CThostFtdcOptionInstrMiniMarginField["IsRelative"] = "int"
structDict['CThostFtdcOptionInstrMiniMarginField'] = CThostFtdcOptionInstrMiniMarginField


#当前期权合约保证金调整系数
CThostFtdcOptionInstrMarginAdjustField = {}
#合约代码
CThostFtdcOptionInstrMarginAdjustField["InstrumentID"] = "string"
#投资者范围
CThostFtdcOptionInstrMarginAdjustField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcOptionInstrMarginAdjustField["BrokerID"] = "string"
#投资者代码
CThostFtdcOptionInstrMarginAdjustField["InvestorID"] = "string"
#投机空头保证金调整系数
CThostFtdcOptionInstrMarginAdjustField["SShortMarginRatioByMoney"] = "float"
#投机空头保证金调整系数
CThostFtdcOptionInstrMarginAdjustField["SShortMarginRatioByVolume"] = "float"
#保值空头保证金调整系数
CThostFtdcOptionInstrMarginAdjustField["HShortMarginRatioByMoney"] = "float"
#保值空头保证金调整系数
CThostFtdcOptionInstrMarginAdjustField["HShortMarginRatioByVolume"] = "float"
#套利空头保证金调整系数
CThostFtdcOptionInstrMarginAdjustField["AShortMarginRatioByMoney"] = "float"
#套利空头保证金调整系数
CThostFtdcOptionInstrMarginAdjustField["AShortMarginRatioByVolume"] = "float"
#是否跟随交易所收取
CThostFtdcOptionInstrMarginAdjustField["IsRelative"] = "int"
#做市商空头保证金调整系数
CThostFtdcOptionInstrMarginAdjustField["MShortMarginRatioByMoney"] = "float"
#做市商空头保证金调整系数
CThostFtdcOptionInstrMarginAdjustField["MShortMarginRatioByVolume"] = "float"
structDict['CThostFtdcOptionInstrMarginAdjustField'] = CThostFtdcOptionInstrMarginAdjustField


#当前期权合约手续费的详细内容
CThostFtdcOptionInstrCommRateField = {}
#合约代码
CThostFtdcOptionInstrCommRateField["InstrumentID"] = "string"
#投资者范围
CThostFtdcOptionInstrCommRateField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcOptionInstrCommRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcOptionInstrCommRateField["InvestorID"] = "string"
#开仓手续费率
CThostFtdcOptionInstrCommRateField["OpenRatioByMoney"] = "float"
#开仓手续费
CThostFtdcOptionInstrCommRateField["OpenRatioByVolume"] = "float"
#平仓手续费率
CThostFtdcOptionInstrCommRateField["CloseRatioByMoney"] = "float"
#平仓手续费
CThostFtdcOptionInstrCommRateField["CloseRatioByVolume"] = "float"
#平今手续费率
CThostFtdcOptionInstrCommRateField["CloseTodayRatioByMoney"] = "float"
#平今手续费
CThostFtdcOptionInstrCommRateField["CloseTodayRatioByVolume"] = "float"
#执行手续费率
CThostFtdcOptionInstrCommRateField["StrikeRatioByMoney"] = "float"
#执行手续费
CThostFtdcOptionInstrCommRateField["StrikeRatioByVolume"] = "float"
#交易所代码
CThostFtdcOptionInstrCommRateField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcOptionInstrCommRateField["InvestUnitID"] = "string"
structDict['CThostFtdcOptionInstrCommRateField'] = CThostFtdcOptionInstrCommRateField


#期权交易成本
CThostFtdcOptionInstrTradeCostField = {}
#经纪公司代码
CThostFtdcOptionInstrTradeCostField["BrokerID"] = "string"
#投资者代码
CThostFtdcOptionInstrTradeCostField["InvestorID"] = "string"
#合约代码
CThostFtdcOptionInstrTradeCostField["InstrumentID"] = "string"
#投机套保标志
CThostFtdcOptionInstrTradeCostField["HedgeFlag"] = "char"
#期权合约保证金不变部分
CThostFtdcOptionInstrTradeCostField["FixedMargin"] = "float"
#期权合约最小保证金
CThostFtdcOptionInstrTradeCostField["MiniMargin"] = "float"
#期权合约权利金
CThostFtdcOptionInstrTradeCostField["Royalty"] = "float"
#交易所期权合约保证金不变部分
CThostFtdcOptionInstrTradeCostField["ExchFixedMargin"] = "float"
#交易所期权合约最小保证金
CThostFtdcOptionInstrTradeCostField["ExchMiniMargin"] = "float"
#交易所代码
CThostFtdcOptionInstrTradeCostField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcOptionInstrTradeCostField["InvestUnitID"] = "string"
structDict['CThostFtdcOptionInstrTradeCostField'] = CThostFtdcOptionInstrTradeCostField


#期权交易成本查询
CThostFtdcQryOptionInstrTradeCostField = {}
#经纪公司代码
CThostFtdcQryOptionInstrTradeCostField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryOptionInstrTradeCostField["InvestorID"] = "string"
#合约代码
CThostFtdcQryOptionInstrTradeCostField["InstrumentID"] = "string"
#投机套保标志
CThostFtdcQryOptionInstrTradeCostField["HedgeFlag"] = "char"
#期权合约报价
CThostFtdcQryOptionInstrTradeCostField["InputPrice"] = "float"
#标的价格,填0则用昨结算价
CThostFtdcQryOptionInstrTradeCostField["UnderlyingPrice"] = "float"
#交易所代码
CThostFtdcQryOptionInstrTradeCostField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcQryOptionInstrTradeCostField["InvestUnitID"] = "string"
structDict['CThostFtdcQryOptionInstrTradeCostField'] = CThostFtdcQryOptionInstrTradeCostField


#期权手续费率查询
CThostFtdcQryOptionInstrCommRateField = {}
#经纪公司代码
CThostFtdcQryOptionInstrCommRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryOptionInstrCommRateField["InvestorID"] = "string"
#合约代码
CThostFtdcQryOptionInstrCommRateField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryOptionInstrCommRateField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcQryOptionInstrCommRateField["InvestUnitID"] = "string"
structDict['CThostFtdcQryOptionInstrCommRateField'] = CThostFtdcQryOptionInstrCommRateField


#股指现货指数
CThostFtdcIndexPriceField = {}
#经纪公司代码
CThostFtdcIndexPriceField["BrokerID"] = "string"
#合约代码
CThostFtdcIndexPriceField["InstrumentID"] = "string"
#指数现货收盘价
CThostFtdcIndexPriceField["ClosePrice"] = "float"
structDict['CThostFtdcIndexPriceField'] = CThostFtdcIndexPriceField


#输入的执行宣告
CThostFtdcInputExecOrderField = {}
#经纪公司代码
CThostFtdcInputExecOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcInputExecOrderField["InvestorID"] = "string"
#合约代码
CThostFtdcInputExecOrderField["InstrumentID"] = "string"
#执行宣告引用
CThostFtdcInputExecOrderField["ExecOrderRef"] = "string"
#用户代码
CThostFtdcInputExecOrderField["UserID"] = "string"
#数量
CThostFtdcInputExecOrderField["Volume"] = "int"
#请求编号
CThostFtdcInputExecOrderField["RequestID"] = "int"
#业务单元
CThostFtdcInputExecOrderField["BusinessUnit"] = "string"
#开平标志
CThostFtdcInputExecOrderField["OffsetFlag"] = "char"
#投机套保标志
CThostFtdcInputExecOrderField["HedgeFlag"] = "char"
#执行类型
CThostFtdcInputExecOrderField["ActionType"] = "char"
#保留头寸申请的持仓方向
CThostFtdcInputExecOrderField["PosiDirection"] = "char"
#期权行权后是否保留期货头寸的标记,该字段已废弃
CThostFtdcInputExecOrderField["ReservePositionFlag"] = "char"
#期权行权后生成的头寸是否自动平仓
CThostFtdcInputExecOrderField["CloseFlag"] = "char"
#交易所代码
CThostFtdcInputExecOrderField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcInputExecOrderField["InvestUnitID"] = "string"
#资金账号
CThostFtdcInputExecOrderField["AccountID"] = "string"
#币种代码
CThostFtdcInputExecOrderField["CurrencyID"] = "string"
#交易编码
CThostFtdcInputExecOrderField["ClientID"] = "string"
#IP地址
CThostFtdcInputExecOrderField["IPAddress"] = "string"
#Mac地址
CThostFtdcInputExecOrderField["MacAddress"] = "string"
structDict['CThostFtdcInputExecOrderField'] = CThostFtdcInputExecOrderField


#输入执行宣告操作
CThostFtdcInputExecOrderActionField = {}
#经纪公司代码
CThostFtdcInputExecOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcInputExecOrderActionField["InvestorID"] = "string"
#执行宣告操作引用
CThostFtdcInputExecOrderActionField["ExecOrderActionRef"] = "int"
#执行宣告引用
CThostFtdcInputExecOrderActionField["ExecOrderRef"] = "string"
#请求编号
CThostFtdcInputExecOrderActionField["RequestID"] = "int"
#前置编号
CThostFtdcInputExecOrderActionField["FrontID"] = "int"
#会话编号
CThostFtdcInputExecOrderActionField["SessionID"] = "int"
#交易所代码
CThostFtdcInputExecOrderActionField["ExchangeID"] = "string"
#执行宣告操作编号
CThostFtdcInputExecOrderActionField["ExecOrderSysID"] = "string"
#操作标志
CThostFtdcInputExecOrderActionField["ActionFlag"] = "char"
#用户代码
CThostFtdcInputExecOrderActionField["UserID"] = "string"
#合约代码
CThostFtdcInputExecOrderActionField["InstrumentID"] = "string"
#投资单元代码
CThostFtdcInputExecOrderActionField["InvestUnitID"] = "string"
#IP地址
CThostFtdcInputExecOrderActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcInputExecOrderActionField["MacAddress"] = "string"
structDict['CThostFtdcInputExecOrderActionField'] = CThostFtdcInputExecOrderActionField


#执行宣告
CThostFtdcExecOrderField = {}
#经纪公司代码
CThostFtdcExecOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcExecOrderField["InvestorID"] = "string"
#合约代码
CThostFtdcExecOrderField["InstrumentID"] = "string"
#执行宣告引用
CThostFtdcExecOrderField["ExecOrderRef"] = "string"
#用户代码
CThostFtdcExecOrderField["UserID"] = "string"
#数量
CThostFtdcExecOrderField["Volume"] = "int"
#请求编号
CThostFtdcExecOrderField["RequestID"] = "int"
#业务单元
CThostFtdcExecOrderField["BusinessUnit"] = "string"
#开平标志
CThostFtdcExecOrderField["OffsetFlag"] = "char"
#投机套保标志
CThostFtdcExecOrderField["HedgeFlag"] = "char"
#执行类型
CThostFtdcExecOrderField["ActionType"] = "char"
#保留头寸申请的持仓方向
CThostFtdcExecOrderField["PosiDirection"] = "char"
#期权行权后是否保留期货头寸的标记,该字段已废弃
CThostFtdcExecOrderField["ReservePositionFlag"] = "char"
#期权行权后生成的头寸是否自动平仓
CThostFtdcExecOrderField["CloseFlag"] = "char"
#本地执行宣告编号
CThostFtdcExecOrderField["ExecOrderLocalID"] = "string"
#交易所代码
CThostFtdcExecOrderField["ExchangeID"] = "string"
#会员代码
CThostFtdcExecOrderField["ParticipantID"] = "string"
#客户代码
CThostFtdcExecOrderField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcExecOrderField["ExchangeInstID"] = "string"
#交易所交易员代码
CThostFtdcExecOrderField["TraderID"] = "string"
#安装编号
CThostFtdcExecOrderField["InstallID"] = "int"
#执行宣告提交状态
CThostFtdcExecOrderField["OrderSubmitStatus"] = "char"
#报单提示序号
CThostFtdcExecOrderField["NotifySequence"] = "int"
#交易日
CThostFtdcExecOrderField["TradingDay"] = "string"
#结算编号
CThostFtdcExecOrderField["SettlementID"] = "int"
#执行宣告编号
CThostFtdcExecOrderField["ExecOrderSysID"] = "string"
#报单日期
CThostFtdcExecOrderField["InsertDate"] = "string"
#插入时间
CThostFtdcExecOrderField["InsertTime"] = "string"
#撤销时间
CThostFtdcExecOrderField["CancelTime"] = "string"
#执行结果
CThostFtdcExecOrderField["ExecResult"] = "char"
#结算会员编号
CThostFtdcExecOrderField["ClearingPartID"] = "string"
#序号
CThostFtdcExecOrderField["SequenceNo"] = "int"
#前置编号
CThostFtdcExecOrderField["FrontID"] = "int"
#会话编号
CThostFtdcExecOrderField["SessionID"] = "int"
#用户端产品信息
CThostFtdcExecOrderField["UserProductInfo"] = "string"
#状态信息
CThostFtdcExecOrderField["StatusMsg"] = "string"
#操作用户代码
CThostFtdcExecOrderField["ActiveUserID"] = "string"
#经纪公司报单编号
CThostFtdcExecOrderField["BrokerExecOrderSeq"] = "int"
#营业部编号
CThostFtdcExecOrderField["BranchID"] = "string"
#投资单元代码
CThostFtdcExecOrderField["InvestUnitID"] = "string"
#资金账号
CThostFtdcExecOrderField["AccountID"] = "string"
#币种代码
CThostFtdcExecOrderField["CurrencyID"] = "string"
#IP地址
CThostFtdcExecOrderField["IPAddress"] = "string"
#Mac地址
CThostFtdcExecOrderField["MacAddress"] = "string"
structDict['CThostFtdcExecOrderField'] = CThostFtdcExecOrderField


#执行宣告操作
CThostFtdcExecOrderActionField = {}
#经纪公司代码
CThostFtdcExecOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcExecOrderActionField["InvestorID"] = "string"
#执行宣告操作引用
CThostFtdcExecOrderActionField["ExecOrderActionRef"] = "int"
#执行宣告引用
CThostFtdcExecOrderActionField["ExecOrderRef"] = "string"
#请求编号
CThostFtdcExecOrderActionField["RequestID"] = "int"
#前置编号
CThostFtdcExecOrderActionField["FrontID"] = "int"
#会话编号
CThostFtdcExecOrderActionField["SessionID"] = "int"
#交易所代码
CThostFtdcExecOrderActionField["ExchangeID"] = "string"
#执行宣告操作编号
CThostFtdcExecOrderActionField["ExecOrderSysID"] = "string"
#操作标志
CThostFtdcExecOrderActionField["ActionFlag"] = "char"
#操作日期
CThostFtdcExecOrderActionField["ActionDate"] = "string"
#操作时间
CThostFtdcExecOrderActionField["ActionTime"] = "string"
#交易所交易员代码
CThostFtdcExecOrderActionField["TraderID"] = "string"
#安装编号
CThostFtdcExecOrderActionField["InstallID"] = "int"
#本地执行宣告编号
CThostFtdcExecOrderActionField["ExecOrderLocalID"] = "string"
#操作本地编号
CThostFtdcExecOrderActionField["ActionLocalID"] = "string"
#会员代码
CThostFtdcExecOrderActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcExecOrderActionField["ClientID"] = "string"
#业务单元
CThostFtdcExecOrderActionField["BusinessUnit"] = "string"
#报单操作状态
CThostFtdcExecOrderActionField["OrderActionStatus"] = "char"
#用户代码
CThostFtdcExecOrderActionField["UserID"] = "string"
#执行类型
CThostFtdcExecOrderActionField["ActionType"] = "char"
#状态信息
CThostFtdcExecOrderActionField["StatusMsg"] = "string"
#合约代码
CThostFtdcExecOrderActionField["InstrumentID"] = "string"
#营业部编号
CThostFtdcExecOrderActionField["BranchID"] = "string"
#投资单元代码
CThostFtdcExecOrderActionField["InvestUnitID"] = "string"
#IP地址
CThostFtdcExecOrderActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcExecOrderActionField["MacAddress"] = "string"
structDict['CThostFtdcExecOrderActionField'] = CThostFtdcExecOrderActionField


#执行宣告查询
CThostFtdcQryExecOrderField = {}
#经纪公司代码
CThostFtdcQryExecOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryExecOrderField["InvestorID"] = "string"
#合约代码
CThostFtdcQryExecOrderField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryExecOrderField["ExchangeID"] = "string"
#执行宣告编号
CThostFtdcQryExecOrderField["ExecOrderSysID"] = "string"
#开始时间
CThostFtdcQryExecOrderField["InsertTimeStart"] = "string"
#结束时间
CThostFtdcQryExecOrderField["InsertTimeEnd"] = "string"
structDict['CThostFtdcQryExecOrderField'] = CThostFtdcQryExecOrderField


#交易所执行宣告信息
CThostFtdcExchangeExecOrderField = {}
#数量
CThostFtdcExchangeExecOrderField["Volume"] = "int"
#请求编号
CThostFtdcExchangeExecOrderField["RequestID"] = "int"
#业务单元
CThostFtdcExchangeExecOrderField["BusinessUnit"] = "string"
#开平标志
CThostFtdcExchangeExecOrderField["OffsetFlag"] = "char"
#投机套保标志
CThostFtdcExchangeExecOrderField["HedgeFlag"] = "char"
#执行类型
CThostFtdcExchangeExecOrderField["ActionType"] = "char"
#保留头寸申请的持仓方向
CThostFtdcExchangeExecOrderField["PosiDirection"] = "char"
#期权行权后是否保留期货头寸的标记,该字段已废弃
CThostFtdcExchangeExecOrderField["ReservePositionFlag"] = "char"
#期权行权后生成的头寸是否自动平仓
CThostFtdcExchangeExecOrderField["CloseFlag"] = "char"
#本地执行宣告编号
CThostFtdcExchangeExecOrderField["ExecOrderLocalID"] = "string"
#交易所代码
CThostFtdcExchangeExecOrderField["ExchangeID"] = "string"
#会员代码
CThostFtdcExchangeExecOrderField["ParticipantID"] = "string"
#客户代码
CThostFtdcExchangeExecOrderField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcExchangeExecOrderField["ExchangeInstID"] = "string"
#交易所交易员代码
CThostFtdcExchangeExecOrderField["TraderID"] = "string"
#安装编号
CThostFtdcExchangeExecOrderField["InstallID"] = "int"
#执行宣告提交状态
CThostFtdcExchangeExecOrderField["OrderSubmitStatus"] = "char"
#报单提示序号
CThostFtdcExchangeExecOrderField["NotifySequence"] = "int"
#交易日
CThostFtdcExchangeExecOrderField["TradingDay"] = "string"
#结算编号
CThostFtdcExchangeExecOrderField["SettlementID"] = "int"
#执行宣告编号
CThostFtdcExchangeExecOrderField["ExecOrderSysID"] = "string"
#报单日期
CThostFtdcExchangeExecOrderField["InsertDate"] = "string"
#插入时间
CThostFtdcExchangeExecOrderField["InsertTime"] = "string"
#撤销时间
CThostFtdcExchangeExecOrderField["CancelTime"] = "string"
#执行结果
CThostFtdcExchangeExecOrderField["ExecResult"] = "char"
#结算会员编号
CThostFtdcExchangeExecOrderField["ClearingPartID"] = "string"
#序号
CThostFtdcExchangeExecOrderField["SequenceNo"] = "int"
#营业部编号
CThostFtdcExchangeExecOrderField["BranchID"] = "string"
#IP地址
CThostFtdcExchangeExecOrderField["IPAddress"] = "string"
#Mac地址
CThostFtdcExchangeExecOrderField["MacAddress"] = "string"
structDict['CThostFtdcExchangeExecOrderField'] = CThostFtdcExchangeExecOrderField


#交易所执行宣告查询
CThostFtdcQryExchangeExecOrderField = {}
#会员代码
CThostFtdcQryExchangeExecOrderField["ParticipantID"] = "string"
#客户代码
CThostFtdcQryExchangeExecOrderField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcQryExchangeExecOrderField["ExchangeInstID"] = "string"
#交易所代码
CThostFtdcQryExchangeExecOrderField["ExchangeID"] = "string"
#交易所交易员代码
CThostFtdcQryExchangeExecOrderField["TraderID"] = "string"
structDict['CThostFtdcQryExchangeExecOrderField'] = CThostFtdcQryExchangeExecOrderField


#执行宣告操作查询
CThostFtdcQryExecOrderActionField = {}
#经纪公司代码
CThostFtdcQryExecOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryExecOrderActionField["InvestorID"] = "string"
#交易所代码
CThostFtdcQryExecOrderActionField["ExchangeID"] = "string"
structDict['CThostFtdcQryExecOrderActionField'] = CThostFtdcQryExecOrderActionField


#交易所执行宣告操作
CThostFtdcExchangeExecOrderActionField = {}
#交易所代码
CThostFtdcExchangeExecOrderActionField["ExchangeID"] = "string"
#执行宣告操作编号
CThostFtdcExchangeExecOrderActionField["ExecOrderSysID"] = "string"
#操作标志
CThostFtdcExchangeExecOrderActionField["ActionFlag"] = "char"
#操作日期
CThostFtdcExchangeExecOrderActionField["ActionDate"] = "string"
#操作时间
CThostFtdcExchangeExecOrderActionField["ActionTime"] = "string"
#交易所交易员代码
CThostFtdcExchangeExecOrderActionField["TraderID"] = "string"
#安装编号
CThostFtdcExchangeExecOrderActionField["InstallID"] = "int"
#本地执行宣告编号
CThostFtdcExchangeExecOrderActionField["ExecOrderLocalID"] = "string"
#操作本地编号
CThostFtdcExchangeExecOrderActionField["ActionLocalID"] = "string"
#会员代码
CThostFtdcExchangeExecOrderActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcExchangeExecOrderActionField["ClientID"] = "string"
#业务单元
CThostFtdcExchangeExecOrderActionField["BusinessUnit"] = "string"
#报单操作状态
CThostFtdcExchangeExecOrderActionField["OrderActionStatus"] = "char"
#用户代码
CThostFtdcExchangeExecOrderActionField["UserID"] = "string"
#执行类型
CThostFtdcExchangeExecOrderActionField["ActionType"] = "char"
#营业部编号
CThostFtdcExchangeExecOrderActionField["BranchID"] = "string"
#IP地址
CThostFtdcExchangeExecOrderActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcExchangeExecOrderActionField["MacAddress"] = "string"
#合约在交易所的代码
CThostFtdcExchangeExecOrderActionField["ExchangeInstID"] = "string"
#数量
CThostFtdcExchangeExecOrderActionField["Volume"] = "int"
structDict['CThostFtdcExchangeExecOrderActionField'] = CThostFtdcExchangeExecOrderActionField


#交易所执行宣告操作查询
CThostFtdcQryExchangeExecOrderActionField = {}
#会员代码
CThostFtdcQryExchangeExecOrderActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcQryExchangeExecOrderActionField["ClientID"] = "string"
#交易所代码
CThostFtdcQryExchangeExecOrderActionField["ExchangeID"] = "string"
#交易所交易员代码
CThostFtdcQryExchangeExecOrderActionField["TraderID"] = "string"
structDict['CThostFtdcQryExchangeExecOrderActionField'] = CThostFtdcQryExchangeExecOrderActionField


#错误执行宣告
CThostFtdcErrExecOrderField = {}
#经纪公司代码
CThostFtdcErrExecOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcErrExecOrderField["InvestorID"] = "string"
#合约代码
CThostFtdcErrExecOrderField["InstrumentID"] = "string"
#执行宣告引用
CThostFtdcErrExecOrderField["ExecOrderRef"] = "string"
#用户代码
CThostFtdcErrExecOrderField["UserID"] = "string"
#数量
CThostFtdcErrExecOrderField["Volume"] = "int"
#请求编号
CThostFtdcErrExecOrderField["RequestID"] = "int"
#业务单元
CThostFtdcErrExecOrderField["BusinessUnit"] = "string"
#开平标志
CThostFtdcErrExecOrderField["OffsetFlag"] = "char"
#投机套保标志
CThostFtdcErrExecOrderField["HedgeFlag"] = "char"
#执行类型
CThostFtdcErrExecOrderField["ActionType"] = "char"
#保留头寸申请的持仓方向
CThostFtdcErrExecOrderField["PosiDirection"] = "char"
#期权行权后是否保留期货头寸的标记,该字段已废弃
CThostFtdcErrExecOrderField["ReservePositionFlag"] = "char"
#期权行权后生成的头寸是否自动平仓
CThostFtdcErrExecOrderField["CloseFlag"] = "char"
#交易所代码
CThostFtdcErrExecOrderField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcErrExecOrderField["InvestUnitID"] = "string"
#资金账号
CThostFtdcErrExecOrderField["AccountID"] = "string"
#币种代码
CThostFtdcErrExecOrderField["CurrencyID"] = "string"
#交易编码
CThostFtdcErrExecOrderField["ClientID"] = "string"
#IP地址
CThostFtdcErrExecOrderField["IPAddress"] = "string"
#Mac地址
CThostFtdcErrExecOrderField["MacAddress"] = "string"
#错误代码
CThostFtdcErrExecOrderField["ErrorID"] = "int"
#错误信息
CThostFtdcErrExecOrderField["ErrorMsg"] = "string"
structDict['CThostFtdcErrExecOrderField'] = CThostFtdcErrExecOrderField


#查询错误执行宣告
CThostFtdcQryErrExecOrderField = {}
#经纪公司代码
CThostFtdcQryErrExecOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryErrExecOrderField["InvestorID"] = "string"
structDict['CThostFtdcQryErrExecOrderField'] = CThostFtdcQryErrExecOrderField


#错误执行宣告操作
CThostFtdcErrExecOrderActionField = {}
#经纪公司代码
CThostFtdcErrExecOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcErrExecOrderActionField["InvestorID"] = "string"
#执行宣告操作引用
CThostFtdcErrExecOrderActionField["ExecOrderActionRef"] = "int"
#执行宣告引用
CThostFtdcErrExecOrderActionField["ExecOrderRef"] = "string"
#请求编号
CThostFtdcErrExecOrderActionField["RequestID"] = "int"
#前置编号
CThostFtdcErrExecOrderActionField["FrontID"] = "int"
#会话编号
CThostFtdcErrExecOrderActionField["SessionID"] = "int"
#交易所代码
CThostFtdcErrExecOrderActionField["ExchangeID"] = "string"
#执行宣告操作编号
CThostFtdcErrExecOrderActionField["ExecOrderSysID"] = "string"
#操作标志
CThostFtdcErrExecOrderActionField["ActionFlag"] = "char"
#用户代码
CThostFtdcErrExecOrderActionField["UserID"] = "string"
#合约代码
CThostFtdcErrExecOrderActionField["InstrumentID"] = "string"
#投资单元代码
CThostFtdcErrExecOrderActionField["InvestUnitID"] = "string"
#IP地址
CThostFtdcErrExecOrderActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcErrExecOrderActionField["MacAddress"] = "string"
#错误代码
CThostFtdcErrExecOrderActionField["ErrorID"] = "int"
#错误信息
CThostFtdcErrExecOrderActionField["ErrorMsg"] = "string"
structDict['CThostFtdcErrExecOrderActionField'] = CThostFtdcErrExecOrderActionField


#查询错误执行宣告操作
CThostFtdcQryErrExecOrderActionField = {}
#经纪公司代码
CThostFtdcQryErrExecOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryErrExecOrderActionField["InvestorID"] = "string"
structDict['CThostFtdcQryErrExecOrderActionField'] = CThostFtdcQryErrExecOrderActionField


#投资者期权合约交易权限
CThostFtdcOptionInstrTradingRightField = {}
#合约代码
CThostFtdcOptionInstrTradingRightField["InstrumentID"] = "string"
#投资者范围
CThostFtdcOptionInstrTradingRightField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcOptionInstrTradingRightField["BrokerID"] = "string"
#投资者代码
CThostFtdcOptionInstrTradingRightField["InvestorID"] = "string"
#买卖方向
CThostFtdcOptionInstrTradingRightField["Direction"] = "char"
#交易权限
CThostFtdcOptionInstrTradingRightField["TradingRight"] = "char"
structDict['CThostFtdcOptionInstrTradingRightField'] = CThostFtdcOptionInstrTradingRightField


#查询期权合约交易权限
CThostFtdcQryOptionInstrTradingRightField = {}
#经纪公司代码
CThostFtdcQryOptionInstrTradingRightField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryOptionInstrTradingRightField["InvestorID"] = "string"
#合约代码
CThostFtdcQryOptionInstrTradingRightField["InstrumentID"] = "string"
#买卖方向
CThostFtdcQryOptionInstrTradingRightField["Direction"] = "char"
structDict['CThostFtdcQryOptionInstrTradingRightField'] = CThostFtdcQryOptionInstrTradingRightField


#输入的询价
CThostFtdcInputForQuoteField = {}
#经纪公司代码
CThostFtdcInputForQuoteField["BrokerID"] = "string"
#投资者代码
CThostFtdcInputForQuoteField["InvestorID"] = "string"
#合约代码
CThostFtdcInputForQuoteField["InstrumentID"] = "string"
#询价引用
CThostFtdcInputForQuoteField["ForQuoteRef"] = "string"
#用户代码
CThostFtdcInputForQuoteField["UserID"] = "string"
#交易所代码
CThostFtdcInputForQuoteField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcInputForQuoteField["InvestUnitID"] = "string"
#IP地址
CThostFtdcInputForQuoteField["IPAddress"] = "string"
#Mac地址
CThostFtdcInputForQuoteField["MacAddress"] = "string"
structDict['CThostFtdcInputForQuoteField'] = CThostFtdcInputForQuoteField


#询价
CThostFtdcForQuoteField = {}
#经纪公司代码
CThostFtdcForQuoteField["BrokerID"] = "string"
#投资者代码
CThostFtdcForQuoteField["InvestorID"] = "string"
#合约代码
CThostFtdcForQuoteField["InstrumentID"] = "string"
#询价引用
CThostFtdcForQuoteField["ForQuoteRef"] = "string"
#用户代码
CThostFtdcForQuoteField["UserID"] = "string"
#本地询价编号
CThostFtdcForQuoteField["ForQuoteLocalID"] = "string"
#交易所代码
CThostFtdcForQuoteField["ExchangeID"] = "string"
#会员代码
CThostFtdcForQuoteField["ParticipantID"] = "string"
#客户代码
CThostFtdcForQuoteField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcForQuoteField["ExchangeInstID"] = "string"
#交易所交易员代码
CThostFtdcForQuoteField["TraderID"] = "string"
#安装编号
CThostFtdcForQuoteField["InstallID"] = "int"
#报单日期
CThostFtdcForQuoteField["InsertDate"] = "string"
#插入时间
CThostFtdcForQuoteField["InsertTime"] = "string"
#询价状态
CThostFtdcForQuoteField["ForQuoteStatus"] = "char"
#前置编号
CThostFtdcForQuoteField["FrontID"] = "int"
#会话编号
CThostFtdcForQuoteField["SessionID"] = "int"
#状态信息
CThostFtdcForQuoteField["StatusMsg"] = "string"
#操作用户代码
CThostFtdcForQuoteField["ActiveUserID"] = "string"
#经纪公司询价编号
CThostFtdcForQuoteField["BrokerForQutoSeq"] = "int"
#投资单元代码
CThostFtdcForQuoteField["InvestUnitID"] = "string"
#IP地址
CThostFtdcForQuoteField["IPAddress"] = "string"
#Mac地址
CThostFtdcForQuoteField["MacAddress"] = "string"
structDict['CThostFtdcForQuoteField'] = CThostFtdcForQuoteField


#询价查询
CThostFtdcQryForQuoteField = {}
#经纪公司代码
CThostFtdcQryForQuoteField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryForQuoteField["InvestorID"] = "string"
#合约代码
CThostFtdcQryForQuoteField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryForQuoteField["ExchangeID"] = "string"
#开始时间
CThostFtdcQryForQuoteField["InsertTimeStart"] = "string"
#结束时间
CThostFtdcQryForQuoteField["InsertTimeEnd"] = "string"
#投资单元代码
CThostFtdcQryForQuoteField["InvestUnitID"] = "string"
structDict['CThostFtdcQryForQuoteField'] = CThostFtdcQryForQuoteField


#交易所询价信息
CThostFtdcExchangeForQuoteField = {}
#本地询价编号
CThostFtdcExchangeForQuoteField["ForQuoteLocalID"] = "string"
#交易所代码
CThostFtdcExchangeForQuoteField["ExchangeID"] = "string"
#会员代码
CThostFtdcExchangeForQuoteField["ParticipantID"] = "string"
#客户代码
CThostFtdcExchangeForQuoteField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcExchangeForQuoteField["ExchangeInstID"] = "string"
#交易所交易员代码
CThostFtdcExchangeForQuoteField["TraderID"] = "string"
#安装编号
CThostFtdcExchangeForQuoteField["InstallID"] = "int"
#报单日期
CThostFtdcExchangeForQuoteField["InsertDate"] = "string"
#插入时间
CThostFtdcExchangeForQuoteField["InsertTime"] = "string"
#询价状态
CThostFtdcExchangeForQuoteField["ForQuoteStatus"] = "char"
#IP地址
CThostFtdcExchangeForQuoteField["IPAddress"] = "string"
#Mac地址
CThostFtdcExchangeForQuoteField["MacAddress"] = "string"
structDict['CThostFtdcExchangeForQuoteField'] = CThostFtdcExchangeForQuoteField


#交易所询价查询
CThostFtdcQryExchangeForQuoteField = {}
#会员代码
CThostFtdcQryExchangeForQuoteField["ParticipantID"] = "string"
#客户代码
CThostFtdcQryExchangeForQuoteField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcQryExchangeForQuoteField["ExchangeInstID"] = "string"
#交易所代码
CThostFtdcQryExchangeForQuoteField["ExchangeID"] = "string"
#交易所交易员代码
CThostFtdcQryExchangeForQuoteField["TraderID"] = "string"
structDict['CThostFtdcQryExchangeForQuoteField'] = CThostFtdcQryExchangeForQuoteField


#输入的报价
CThostFtdcInputQuoteField = {}
#经纪公司代码
CThostFtdcInputQuoteField["BrokerID"] = "string"
#投资者代码
CThostFtdcInputQuoteField["InvestorID"] = "string"
#合约代码
CThostFtdcInputQuoteField["InstrumentID"] = "string"
#报价引用
CThostFtdcInputQuoteField["QuoteRef"] = "string"
#用户代码
CThostFtdcInputQuoteField["UserID"] = "string"
#卖价格
CThostFtdcInputQuoteField["AskPrice"] = "float"
#买价格
CThostFtdcInputQuoteField["BidPrice"] = "float"
#卖数量
CThostFtdcInputQuoteField["AskVolume"] = "int"
#买数量
CThostFtdcInputQuoteField["BidVolume"] = "int"
#请求编号
CThostFtdcInputQuoteField["RequestID"] = "int"
#业务单元
CThostFtdcInputQuoteField["BusinessUnit"] = "string"
#卖开平标志
CThostFtdcInputQuoteField["AskOffsetFlag"] = "char"
#买开平标志
CThostFtdcInputQuoteField["BidOffsetFlag"] = "char"
#卖投机套保标志
CThostFtdcInputQuoteField["AskHedgeFlag"] = "char"
#买投机套保标志
CThostFtdcInputQuoteField["BidHedgeFlag"] = "char"
#衍生卖报单引用
CThostFtdcInputQuoteField["AskOrderRef"] = "string"
#衍生买报单引用
CThostFtdcInputQuoteField["BidOrderRef"] = "string"
#应价编号
CThostFtdcInputQuoteField["ForQuoteSysID"] = "string"
#交易所代码
CThostFtdcInputQuoteField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcInputQuoteField["InvestUnitID"] = "string"
#交易编码
CThostFtdcInputQuoteField["ClientID"] = "string"
#IP地址
CThostFtdcInputQuoteField["IPAddress"] = "string"
#Mac地址
CThostFtdcInputQuoteField["MacAddress"] = "string"
structDict['CThostFtdcInputQuoteField'] = CThostFtdcInputQuoteField


#输入报价操作
CThostFtdcInputQuoteActionField = {}
#经纪公司代码
CThostFtdcInputQuoteActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcInputQuoteActionField["InvestorID"] = "string"
#报价操作引用
CThostFtdcInputQuoteActionField["QuoteActionRef"] = "int"
#报价引用
CThostFtdcInputQuoteActionField["QuoteRef"] = "string"
#请求编号
CThostFtdcInputQuoteActionField["RequestID"] = "int"
#前置编号
CThostFtdcInputQuoteActionField["FrontID"] = "int"
#会话编号
CThostFtdcInputQuoteActionField["SessionID"] = "int"
#交易所代码
CThostFtdcInputQuoteActionField["ExchangeID"] = "string"
#报价操作编号
CThostFtdcInputQuoteActionField["QuoteSysID"] = "string"
#操作标志
CThostFtdcInputQuoteActionField["ActionFlag"] = "char"
#用户代码
CThostFtdcInputQuoteActionField["UserID"] = "string"
#合约代码
CThostFtdcInputQuoteActionField["InstrumentID"] = "string"
#投资单元代码
CThostFtdcInputQuoteActionField["InvestUnitID"] = "string"
#交易编码
CThostFtdcInputQuoteActionField["ClientID"] = "string"
#IP地址
CThostFtdcInputQuoteActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcInputQuoteActionField["MacAddress"] = "string"
structDict['CThostFtdcInputQuoteActionField'] = CThostFtdcInputQuoteActionField


#报价
CThostFtdcQuoteField = {}
#经纪公司代码
CThostFtdcQuoteField["BrokerID"] = "string"
#投资者代码
CThostFtdcQuoteField["InvestorID"] = "string"
#合约代码
CThostFtdcQuoteField["InstrumentID"] = "string"
#报价引用
CThostFtdcQuoteField["QuoteRef"] = "string"
#用户代码
CThostFtdcQuoteField["UserID"] = "string"
#卖价格
CThostFtdcQuoteField["AskPrice"] = "float"
#买价格
CThostFtdcQuoteField["BidPrice"] = "float"
#卖数量
CThostFtdcQuoteField["AskVolume"] = "int"
#买数量
CThostFtdcQuoteField["BidVolume"] = "int"
#请求编号
CThostFtdcQuoteField["RequestID"] = "int"
#业务单元
CThostFtdcQuoteField["BusinessUnit"] = "string"
#卖开平标志
CThostFtdcQuoteField["AskOffsetFlag"] = "char"
#买开平标志
CThostFtdcQuoteField["BidOffsetFlag"] = "char"
#卖投机套保标志
CThostFtdcQuoteField["AskHedgeFlag"] = "char"
#买投机套保标志
CThostFtdcQuoteField["BidHedgeFlag"] = "char"
#本地报价编号
CThostFtdcQuoteField["QuoteLocalID"] = "string"
#交易所代码
CThostFtdcQuoteField["ExchangeID"] = "string"
#会员代码
CThostFtdcQuoteField["ParticipantID"] = "string"
#客户代码
CThostFtdcQuoteField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcQuoteField["ExchangeInstID"] = "string"
#交易所交易员代码
CThostFtdcQuoteField["TraderID"] = "string"
#安装编号
CThostFtdcQuoteField["InstallID"] = "int"
#报价提示序号
CThostFtdcQuoteField["NotifySequence"] = "int"
#报价提交状态
CThostFtdcQuoteField["OrderSubmitStatus"] = "char"
#交易日
CThostFtdcQuoteField["TradingDay"] = "string"
#结算编号
CThostFtdcQuoteField["SettlementID"] = "int"
#报价编号
CThostFtdcQuoteField["QuoteSysID"] = "string"
#报单日期
CThostFtdcQuoteField["InsertDate"] = "string"
#插入时间
CThostFtdcQuoteField["InsertTime"] = "string"
#撤销时间
CThostFtdcQuoteField["CancelTime"] = "string"
#报价状态
CThostFtdcQuoteField["QuoteStatus"] = "char"
#结算会员编号
CThostFtdcQuoteField["ClearingPartID"] = "string"
#序号
CThostFtdcQuoteField["SequenceNo"] = "int"
#卖方报单编号
CThostFtdcQuoteField["AskOrderSysID"] = "string"
#买方报单编号
CThostFtdcQuoteField["BidOrderSysID"] = "string"
#前置编号
CThostFtdcQuoteField["FrontID"] = "int"
#会话编号
CThostFtdcQuoteField["SessionID"] = "int"
#用户端产品信息
CThostFtdcQuoteField["UserProductInfo"] = "string"
#状态信息
CThostFtdcQuoteField["StatusMsg"] = "string"
#操作用户代码
CThostFtdcQuoteField["ActiveUserID"] = "string"
#经纪公司报价编号
CThostFtdcQuoteField["BrokerQuoteSeq"] = "int"
#衍生卖报单引用
CThostFtdcQuoteField["AskOrderRef"] = "string"
#衍生买报单引用
CThostFtdcQuoteField["BidOrderRef"] = "string"
#应价编号
CThostFtdcQuoteField["ForQuoteSysID"] = "string"
#营业部编号
CThostFtdcQuoteField["BranchID"] = "string"
#投资单元代码
CThostFtdcQuoteField["InvestUnitID"] = "string"
#资金账号
CThostFtdcQuoteField["AccountID"] = "string"
#币种代码
CThostFtdcQuoteField["CurrencyID"] = "string"
#IP地址
CThostFtdcQuoteField["IPAddress"] = "string"
#Mac地址
CThostFtdcQuoteField["MacAddress"] = "string"
structDict['CThostFtdcQuoteField'] = CThostFtdcQuoteField


#报价操作
CThostFtdcQuoteActionField = {}
#经纪公司代码
CThostFtdcQuoteActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcQuoteActionField["InvestorID"] = "string"
#报价操作引用
CThostFtdcQuoteActionField["QuoteActionRef"] = "int"
#报价引用
CThostFtdcQuoteActionField["QuoteRef"] = "string"
#请求编号
CThostFtdcQuoteActionField["RequestID"] = "int"
#前置编号
CThostFtdcQuoteActionField["FrontID"] = "int"
#会话编号
CThostFtdcQuoteActionField["SessionID"] = "int"
#交易所代码
CThostFtdcQuoteActionField["ExchangeID"] = "string"
#报价操作编号
CThostFtdcQuoteActionField["QuoteSysID"] = "string"
#操作标志
CThostFtdcQuoteActionField["ActionFlag"] = "char"
#操作日期
CThostFtdcQuoteActionField["ActionDate"] = "string"
#操作时间
CThostFtdcQuoteActionField["ActionTime"] = "string"
#交易所交易员代码
CThostFtdcQuoteActionField["TraderID"] = "string"
#安装编号
CThostFtdcQuoteActionField["InstallID"] = "int"
#本地报价编号
CThostFtdcQuoteActionField["QuoteLocalID"] = "string"
#操作本地编号
CThostFtdcQuoteActionField["ActionLocalID"] = "string"
#会员代码
CThostFtdcQuoteActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcQuoteActionField["ClientID"] = "string"
#业务单元
CThostFtdcQuoteActionField["BusinessUnit"] = "string"
#报单操作状态
CThostFtdcQuoteActionField["OrderActionStatus"] = "char"
#用户代码
CThostFtdcQuoteActionField["UserID"] = "string"
#状态信息
CThostFtdcQuoteActionField["StatusMsg"] = "string"
#合约代码
CThostFtdcQuoteActionField["InstrumentID"] = "string"
#营业部编号
CThostFtdcQuoteActionField["BranchID"] = "string"
#投资单元代码
CThostFtdcQuoteActionField["InvestUnitID"] = "string"
#IP地址
CThostFtdcQuoteActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcQuoteActionField["MacAddress"] = "string"
structDict['CThostFtdcQuoteActionField'] = CThostFtdcQuoteActionField


#报价查询
CThostFtdcQryQuoteField = {}
#经纪公司代码
CThostFtdcQryQuoteField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryQuoteField["InvestorID"] = "string"
#合约代码
CThostFtdcQryQuoteField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryQuoteField["ExchangeID"] = "string"
#报价编号
CThostFtdcQryQuoteField["QuoteSysID"] = "string"
#开始时间
CThostFtdcQryQuoteField["InsertTimeStart"] = "string"
#结束时间
CThostFtdcQryQuoteField["InsertTimeEnd"] = "string"
#投资单元代码
CThostFtdcQryQuoteField["InvestUnitID"] = "string"
structDict['CThostFtdcQryQuoteField'] = CThostFtdcQryQuoteField


#交易所报价信息
CThostFtdcExchangeQuoteField = {}
#卖价格
CThostFtdcExchangeQuoteField["AskPrice"] = "float"
#买价格
CThostFtdcExchangeQuoteField["BidPrice"] = "float"
#卖数量
CThostFtdcExchangeQuoteField["AskVolume"] = "int"
#买数量
CThostFtdcExchangeQuoteField["BidVolume"] = "int"
#请求编号
CThostFtdcExchangeQuoteField["RequestID"] = "int"
#业务单元
CThostFtdcExchangeQuoteField["BusinessUnit"] = "string"
#卖开平标志
CThostFtdcExchangeQuoteField["AskOffsetFlag"] = "char"
#买开平标志
CThostFtdcExchangeQuoteField["BidOffsetFlag"] = "char"
#卖投机套保标志
CThostFtdcExchangeQuoteField["AskHedgeFlag"] = "char"
#买投机套保标志
CThostFtdcExchangeQuoteField["BidHedgeFlag"] = "char"
#本地报价编号
CThostFtdcExchangeQuoteField["QuoteLocalID"] = "string"
#交易所代码
CThostFtdcExchangeQuoteField["ExchangeID"] = "string"
#会员代码
CThostFtdcExchangeQuoteField["ParticipantID"] = "string"
#客户代码
CThostFtdcExchangeQuoteField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcExchangeQuoteField["ExchangeInstID"] = "string"
#交易所交易员代码
CThostFtdcExchangeQuoteField["TraderID"] = "string"
#安装编号
CThostFtdcExchangeQuoteField["InstallID"] = "int"
#报价提示序号
CThostFtdcExchangeQuoteField["NotifySequence"] = "int"
#报价提交状态
CThostFtdcExchangeQuoteField["OrderSubmitStatus"] = "char"
#交易日
CThostFtdcExchangeQuoteField["TradingDay"] = "string"
#结算编号
CThostFtdcExchangeQuoteField["SettlementID"] = "int"
#报价编号
CThostFtdcExchangeQuoteField["QuoteSysID"] = "string"
#报单日期
CThostFtdcExchangeQuoteField["InsertDate"] = "string"
#插入时间
CThostFtdcExchangeQuoteField["InsertTime"] = "string"
#撤销时间
CThostFtdcExchangeQuoteField["CancelTime"] = "string"
#报价状态
CThostFtdcExchangeQuoteField["QuoteStatus"] = "char"
#结算会员编号
CThostFtdcExchangeQuoteField["ClearingPartID"] = "string"
#序号
CThostFtdcExchangeQuoteField["SequenceNo"] = "int"
#卖方报单编号
CThostFtdcExchangeQuoteField["AskOrderSysID"] = "string"
#买方报单编号
CThostFtdcExchangeQuoteField["BidOrderSysID"] = "string"
#应价编号
CThostFtdcExchangeQuoteField["ForQuoteSysID"] = "string"
#营业部编号
CThostFtdcExchangeQuoteField["BranchID"] = "string"
#IP地址
CThostFtdcExchangeQuoteField["IPAddress"] = "string"
#Mac地址
CThostFtdcExchangeQuoteField["MacAddress"] = "string"
structDict['CThostFtdcExchangeQuoteField'] = CThostFtdcExchangeQuoteField


#交易所报价查询
CThostFtdcQryExchangeQuoteField = {}
#会员代码
CThostFtdcQryExchangeQuoteField["ParticipantID"] = "string"
#客户代码
CThostFtdcQryExchangeQuoteField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcQryExchangeQuoteField["ExchangeInstID"] = "string"
#交易所代码
CThostFtdcQryExchangeQuoteField["ExchangeID"] = "string"
#交易所交易员代码
CThostFtdcQryExchangeQuoteField["TraderID"] = "string"
structDict['CThostFtdcQryExchangeQuoteField'] = CThostFtdcQryExchangeQuoteField


#报价操作查询
CThostFtdcQryQuoteActionField = {}
#经纪公司代码
CThostFtdcQryQuoteActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryQuoteActionField["InvestorID"] = "string"
#交易所代码
CThostFtdcQryQuoteActionField["ExchangeID"] = "string"
structDict['CThostFtdcQryQuoteActionField'] = CThostFtdcQryQuoteActionField


#交易所报价操作
CThostFtdcExchangeQuoteActionField = {}
#交易所代码
CThostFtdcExchangeQuoteActionField["ExchangeID"] = "string"
#报价操作编号
CThostFtdcExchangeQuoteActionField["QuoteSysID"] = "string"
#操作标志
CThostFtdcExchangeQuoteActionField["ActionFlag"] = "char"
#操作日期
CThostFtdcExchangeQuoteActionField["ActionDate"] = "string"
#操作时间
CThostFtdcExchangeQuoteActionField["ActionTime"] = "string"
#交易所交易员代码
CThostFtdcExchangeQuoteActionField["TraderID"] = "string"
#安装编号
CThostFtdcExchangeQuoteActionField["InstallID"] = "int"
#本地报价编号
CThostFtdcExchangeQuoteActionField["QuoteLocalID"] = "string"
#操作本地编号
CThostFtdcExchangeQuoteActionField["ActionLocalID"] = "string"
#会员代码
CThostFtdcExchangeQuoteActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcExchangeQuoteActionField["ClientID"] = "string"
#业务单元
CThostFtdcExchangeQuoteActionField["BusinessUnit"] = "string"
#报单操作状态
CThostFtdcExchangeQuoteActionField["OrderActionStatus"] = "char"
#用户代码
CThostFtdcExchangeQuoteActionField["UserID"] = "string"
#IP地址
CThostFtdcExchangeQuoteActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcExchangeQuoteActionField["MacAddress"] = "string"
structDict['CThostFtdcExchangeQuoteActionField'] = CThostFtdcExchangeQuoteActionField


#交易所报价操作查询
CThostFtdcQryExchangeQuoteActionField = {}
#会员代码
CThostFtdcQryExchangeQuoteActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcQryExchangeQuoteActionField["ClientID"] = "string"
#交易所代码
CThostFtdcQryExchangeQuoteActionField["ExchangeID"] = "string"
#交易所交易员代码
CThostFtdcQryExchangeQuoteActionField["TraderID"] = "string"
structDict['CThostFtdcQryExchangeQuoteActionField'] = CThostFtdcQryExchangeQuoteActionField


#期权合约delta值
CThostFtdcOptionInstrDeltaField = {}
#合约代码
CThostFtdcOptionInstrDeltaField["InstrumentID"] = "string"
#投资者范围
CThostFtdcOptionInstrDeltaField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcOptionInstrDeltaField["BrokerID"] = "string"
#投资者代码
CThostFtdcOptionInstrDeltaField["InvestorID"] = "string"
#Delta值
CThostFtdcOptionInstrDeltaField["Delta"] = "float"
structDict['CThostFtdcOptionInstrDeltaField'] = CThostFtdcOptionInstrDeltaField


#发给做市商的询价请求
CThostFtdcForQuoteRspField = {}
#交易日
CThostFtdcForQuoteRspField["TradingDay"] = "string"
#合约代码
CThostFtdcForQuoteRspField["InstrumentID"] = "string"
#询价编号
CThostFtdcForQuoteRspField["ForQuoteSysID"] = "string"
#询价时间
CThostFtdcForQuoteRspField["ForQuoteTime"] = "string"
#业务日期
CThostFtdcForQuoteRspField["ActionDay"] = "string"
#交易所代码
CThostFtdcForQuoteRspField["ExchangeID"] = "string"
structDict['CThostFtdcForQuoteRspField'] = CThostFtdcForQuoteRspField


#当前期权合约执行偏移值的详细内容
CThostFtdcStrikeOffsetField = {}
#合约代码
CThostFtdcStrikeOffsetField["InstrumentID"] = "string"
#投资者范围
CThostFtdcStrikeOffsetField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcStrikeOffsetField["BrokerID"] = "string"
#投资者代码
CThostFtdcStrikeOffsetField["InvestorID"] = "string"
#执行偏移值
CThostFtdcStrikeOffsetField["Offset"] = "float"
#执行偏移类型
CThostFtdcStrikeOffsetField["OffsetType"] = "char"
structDict['CThostFtdcStrikeOffsetField'] = CThostFtdcStrikeOffsetField


#期权执行偏移值查询
CThostFtdcQryStrikeOffsetField = {}
#经纪公司代码
CThostFtdcQryStrikeOffsetField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryStrikeOffsetField["InvestorID"] = "string"
#合约代码
CThostFtdcQryStrikeOffsetField["InstrumentID"] = "string"
structDict['CThostFtdcQryStrikeOffsetField'] = CThostFtdcQryStrikeOffsetField


#输入批量报单操作
CThostFtdcInputBatchOrderActionField = {}
#经纪公司代码
CThostFtdcInputBatchOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcInputBatchOrderActionField["InvestorID"] = "string"
#报单操作引用
CThostFtdcInputBatchOrderActionField["OrderActionRef"] = "int"
#请求编号
CThostFtdcInputBatchOrderActionField["RequestID"] = "int"
#前置编号
CThostFtdcInputBatchOrderActionField["FrontID"] = "int"
#会话编号
CThostFtdcInputBatchOrderActionField["SessionID"] = "int"
#交易所代码
CThostFtdcInputBatchOrderActionField["ExchangeID"] = "string"
#用户代码
CThostFtdcInputBatchOrderActionField["UserID"] = "string"
#投资单元代码
CThostFtdcInputBatchOrderActionField["InvestUnitID"] = "string"
#IP地址
CThostFtdcInputBatchOrderActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcInputBatchOrderActionField["MacAddress"] = "string"
structDict['CThostFtdcInputBatchOrderActionField'] = CThostFtdcInputBatchOrderActionField


#批量报单操作
CThostFtdcBatchOrderActionField = {}
#经纪公司代码
CThostFtdcBatchOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcBatchOrderActionField["InvestorID"] = "string"
#报单操作引用
CThostFtdcBatchOrderActionField["OrderActionRef"] = "int"
#请求编号
CThostFtdcBatchOrderActionField["RequestID"] = "int"
#前置编号
CThostFtdcBatchOrderActionField["FrontID"] = "int"
#会话编号
CThostFtdcBatchOrderActionField["SessionID"] = "int"
#交易所代码
CThostFtdcBatchOrderActionField["ExchangeID"] = "string"
#操作日期
CThostFtdcBatchOrderActionField["ActionDate"] = "string"
#操作时间
CThostFtdcBatchOrderActionField["ActionTime"] = "string"
#交易所交易员代码
CThostFtdcBatchOrderActionField["TraderID"] = "string"
#安装编号
CThostFtdcBatchOrderActionField["InstallID"] = "int"
#操作本地编号
CThostFtdcBatchOrderActionField["ActionLocalID"] = "string"
#会员代码
CThostFtdcBatchOrderActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcBatchOrderActionField["ClientID"] = "string"
#业务单元
CThostFtdcBatchOrderActionField["BusinessUnit"] = "string"
#报单操作状态
CThostFtdcBatchOrderActionField["OrderActionStatus"] = "char"
#用户代码
CThostFtdcBatchOrderActionField["UserID"] = "string"
#状态信息
CThostFtdcBatchOrderActionField["StatusMsg"] = "string"
#投资单元代码
CThostFtdcBatchOrderActionField["InvestUnitID"] = "string"
#IP地址
CThostFtdcBatchOrderActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcBatchOrderActionField["MacAddress"] = "string"
structDict['CThostFtdcBatchOrderActionField'] = CThostFtdcBatchOrderActionField


#交易所批量报单操作
CThostFtdcExchangeBatchOrderActionField = {}
#交易所代码
CThostFtdcExchangeBatchOrderActionField["ExchangeID"] = "string"
#操作日期
CThostFtdcExchangeBatchOrderActionField["ActionDate"] = "string"
#操作时间
CThostFtdcExchangeBatchOrderActionField["ActionTime"] = "string"
#交易所交易员代码
CThostFtdcExchangeBatchOrderActionField["TraderID"] = "string"
#安装编号
CThostFtdcExchangeBatchOrderActionField["InstallID"] = "int"
#操作本地编号
CThostFtdcExchangeBatchOrderActionField["ActionLocalID"] = "string"
#会员代码
CThostFtdcExchangeBatchOrderActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcExchangeBatchOrderActionField["ClientID"] = "string"
#业务单元
CThostFtdcExchangeBatchOrderActionField["BusinessUnit"] = "string"
#报单操作状态
CThostFtdcExchangeBatchOrderActionField["OrderActionStatus"] = "char"
#用户代码
CThostFtdcExchangeBatchOrderActionField["UserID"] = "string"
#IP地址
CThostFtdcExchangeBatchOrderActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcExchangeBatchOrderActionField["MacAddress"] = "string"
structDict['CThostFtdcExchangeBatchOrderActionField'] = CThostFtdcExchangeBatchOrderActionField


#查询批量报单操作
CThostFtdcQryBatchOrderActionField = {}
#经纪公司代码
CThostFtdcQryBatchOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryBatchOrderActionField["InvestorID"] = "string"
#交易所代码
CThostFtdcQryBatchOrderActionField["ExchangeID"] = "string"
structDict['CThostFtdcQryBatchOrderActionField'] = CThostFtdcQryBatchOrderActionField


#组合合约安全系数
CThostFtdcCombInstrumentGuardField = {}
#经纪公司代码
CThostFtdcCombInstrumentGuardField["BrokerID"] = "string"
#合约代码
CThostFtdcCombInstrumentGuardField["InstrumentID"] = "string"
#
CThostFtdcCombInstrumentGuardField["GuarantRatio"] = "float"
#交易所代码
CThostFtdcCombInstrumentGuardField["ExchangeID"] = "string"
structDict['CThostFtdcCombInstrumentGuardField'] = CThostFtdcCombInstrumentGuardField


#组合合约安全系数查询
CThostFtdcQryCombInstrumentGuardField = {}
#经纪公司代码
CThostFtdcQryCombInstrumentGuardField["BrokerID"] = "string"
#合约代码
CThostFtdcQryCombInstrumentGuardField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryCombInstrumentGuardField["ExchangeID"] = "string"
structDict['CThostFtdcQryCombInstrumentGuardField'] = CThostFtdcQryCombInstrumentGuardField


#输入的申请组合
CThostFtdcInputCombActionField = {}
#经纪公司代码
CThostFtdcInputCombActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcInputCombActionField["InvestorID"] = "string"
#合约代码
CThostFtdcInputCombActionField["InstrumentID"] = "string"
#组合引用
CThostFtdcInputCombActionField["CombActionRef"] = "string"
#用户代码
CThostFtdcInputCombActionField["UserID"] = "string"
#买卖方向
CThostFtdcInputCombActionField["Direction"] = "char"
#数量
CThostFtdcInputCombActionField["Volume"] = "int"
#组合指令方向
CThostFtdcInputCombActionField["CombDirection"] = "char"
#投机套保标志
CThostFtdcInputCombActionField["HedgeFlag"] = "char"
#交易所代码
CThostFtdcInputCombActionField["ExchangeID"] = "string"
#IP地址
CThostFtdcInputCombActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcInputCombActionField["MacAddress"] = "string"
#投资单元代码
CThostFtdcInputCombActionField["InvestUnitID"] = "string"
structDict['CThostFtdcInputCombActionField'] = CThostFtdcInputCombActionField


#申请组合
CThostFtdcCombActionField = {}
#经纪公司代码
CThostFtdcCombActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcCombActionField["InvestorID"] = "string"
#合约代码
CThostFtdcCombActionField["InstrumentID"] = "string"
#组合引用
CThostFtdcCombActionField["CombActionRef"] = "string"
#用户代码
CThostFtdcCombActionField["UserID"] = "string"
#买卖方向
CThostFtdcCombActionField["Direction"] = "char"
#数量
CThostFtdcCombActionField["Volume"] = "int"
#组合指令方向
CThostFtdcCombActionField["CombDirection"] = "char"
#投机套保标志
CThostFtdcCombActionField["HedgeFlag"] = "char"
#本地申请组合编号
CThostFtdcCombActionField["ActionLocalID"] = "string"
#交易所代码
CThostFtdcCombActionField["ExchangeID"] = "string"
#会员代码
CThostFtdcCombActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcCombActionField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcCombActionField["ExchangeInstID"] = "string"
#交易所交易员代码
CThostFtdcCombActionField["TraderID"] = "string"
#安装编号
CThostFtdcCombActionField["InstallID"] = "int"
#组合状态
CThostFtdcCombActionField["ActionStatus"] = "char"
#报单提示序号
CThostFtdcCombActionField["NotifySequence"] = "int"
#交易日
CThostFtdcCombActionField["TradingDay"] = "string"
#结算编号
CThostFtdcCombActionField["SettlementID"] = "int"
#序号
CThostFtdcCombActionField["SequenceNo"] = "int"
#前置编号
CThostFtdcCombActionField["FrontID"] = "int"
#会话编号
CThostFtdcCombActionField["SessionID"] = "int"
#用户端产品信息
CThostFtdcCombActionField["UserProductInfo"] = "string"
#状态信息
CThostFtdcCombActionField["StatusMsg"] = "string"
#IP地址
CThostFtdcCombActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcCombActionField["MacAddress"] = "string"
#组合编号
CThostFtdcCombActionField["ComTradeID"] = "string"
#营业部编号
CThostFtdcCombActionField["BranchID"] = "string"
#投资单元代码
CThostFtdcCombActionField["InvestUnitID"] = "string"
structDict['CThostFtdcCombActionField'] = CThostFtdcCombActionField


#申请组合查询
CThostFtdcQryCombActionField = {}
#经纪公司代码
CThostFtdcQryCombActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryCombActionField["InvestorID"] = "string"
#合约代码
CThostFtdcQryCombActionField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryCombActionField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcQryCombActionField["InvestUnitID"] = "string"
structDict['CThostFtdcQryCombActionField'] = CThostFtdcQryCombActionField


#交易所申请组合信息
CThostFtdcExchangeCombActionField = {}
#买卖方向
CThostFtdcExchangeCombActionField["Direction"] = "char"
#数量
CThostFtdcExchangeCombActionField["Volume"] = "int"
#组合指令方向
CThostFtdcExchangeCombActionField["CombDirection"] = "char"
#投机套保标志
CThostFtdcExchangeCombActionField["HedgeFlag"] = "char"
#本地申请组合编号
CThostFtdcExchangeCombActionField["ActionLocalID"] = "string"
#交易所代码
CThostFtdcExchangeCombActionField["ExchangeID"] = "string"
#会员代码
CThostFtdcExchangeCombActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcExchangeCombActionField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcExchangeCombActionField["ExchangeInstID"] = "string"
#交易所交易员代码
CThostFtdcExchangeCombActionField["TraderID"] = "string"
#安装编号
CThostFtdcExchangeCombActionField["InstallID"] = "int"
#组合状态
CThostFtdcExchangeCombActionField["ActionStatus"] = "char"
#报单提示序号
CThostFtdcExchangeCombActionField["NotifySequence"] = "int"
#交易日
CThostFtdcExchangeCombActionField["TradingDay"] = "string"
#结算编号
CThostFtdcExchangeCombActionField["SettlementID"] = "int"
#序号
CThostFtdcExchangeCombActionField["SequenceNo"] = "int"
#IP地址
CThostFtdcExchangeCombActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcExchangeCombActionField["MacAddress"] = "string"
#组合编号
CThostFtdcExchangeCombActionField["ComTradeID"] = "string"
#营业部编号
CThostFtdcExchangeCombActionField["BranchID"] = "string"
structDict['CThostFtdcExchangeCombActionField'] = CThostFtdcExchangeCombActionField


#交易所申请组合查询
CThostFtdcQryExchangeCombActionField = {}
#会员代码
CThostFtdcQryExchangeCombActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcQryExchangeCombActionField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcQryExchangeCombActionField["ExchangeInstID"] = "string"
#交易所代码
CThostFtdcQryExchangeCombActionField["ExchangeID"] = "string"
#交易所交易员代码
CThostFtdcQryExchangeCombActionField["TraderID"] = "string"
structDict['CThostFtdcQryExchangeCombActionField'] = CThostFtdcQryExchangeCombActionField


#产品报价汇率
CThostFtdcProductExchRateField = {}
#产品代码
CThostFtdcProductExchRateField["ProductID"] = "string"
#报价币种类型
CThostFtdcProductExchRateField["QuoteCurrencyID"] = "string"
#汇率
CThostFtdcProductExchRateField["ExchangeRate"] = "float"
#交易所代码
CThostFtdcProductExchRateField["ExchangeID"] = "string"
structDict['CThostFtdcProductExchRateField'] = CThostFtdcProductExchRateField


#产品报价汇率查询
CThostFtdcQryProductExchRateField = {}
#产品代码
CThostFtdcQryProductExchRateField["ProductID"] = "string"
#交易所代码
CThostFtdcQryProductExchRateField["ExchangeID"] = "string"
structDict['CThostFtdcQryProductExchRateField'] = CThostFtdcQryProductExchRateField


#查询询价价差参数
CThostFtdcQryForQuoteParamField = {}
#经纪公司代码
CThostFtdcQryForQuoteParamField["BrokerID"] = "string"
#合约代码
CThostFtdcQryForQuoteParamField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryForQuoteParamField["ExchangeID"] = "string"
structDict['CThostFtdcQryForQuoteParamField'] = CThostFtdcQryForQuoteParamField


#询价价差参数
CThostFtdcForQuoteParamField = {}
#经纪公司代码
CThostFtdcForQuoteParamField["BrokerID"] = "string"
#合约代码
CThostFtdcForQuoteParamField["InstrumentID"] = "string"
#交易所代码
CThostFtdcForQuoteParamField["ExchangeID"] = "string"
#最新价
CThostFtdcForQuoteParamField["LastPrice"] = "float"
#价差
CThostFtdcForQuoteParamField["PriceInterval"] = "float"
structDict['CThostFtdcForQuoteParamField'] = CThostFtdcForQuoteParamField


#当前做市商期权合约手续费的详细内容
CThostFtdcMMOptionInstrCommRateField = {}
#合约代码
CThostFtdcMMOptionInstrCommRateField["InstrumentID"] = "string"
#投资者范围
CThostFtdcMMOptionInstrCommRateField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcMMOptionInstrCommRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcMMOptionInstrCommRateField["InvestorID"] = "string"
#开仓手续费率
CThostFtdcMMOptionInstrCommRateField["OpenRatioByMoney"] = "float"
#开仓手续费
CThostFtdcMMOptionInstrCommRateField["OpenRatioByVolume"] = "float"
#平仓手续费率
CThostFtdcMMOptionInstrCommRateField["CloseRatioByMoney"] = "float"
#平仓手续费
CThostFtdcMMOptionInstrCommRateField["CloseRatioByVolume"] = "float"
#平今手续费率
CThostFtdcMMOptionInstrCommRateField["CloseTodayRatioByMoney"] = "float"
#平今手续费
CThostFtdcMMOptionInstrCommRateField["CloseTodayRatioByVolume"] = "float"
#执行手续费率
CThostFtdcMMOptionInstrCommRateField["StrikeRatioByMoney"] = "float"
#执行手续费
CThostFtdcMMOptionInstrCommRateField["StrikeRatioByVolume"] = "float"
structDict['CThostFtdcMMOptionInstrCommRateField'] = CThostFtdcMMOptionInstrCommRateField


#做市商期权手续费率查询
CThostFtdcQryMMOptionInstrCommRateField = {}
#经纪公司代码
CThostFtdcQryMMOptionInstrCommRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryMMOptionInstrCommRateField["InvestorID"] = "string"
#合约代码
CThostFtdcQryMMOptionInstrCommRateField["InstrumentID"] = "string"
structDict['CThostFtdcQryMMOptionInstrCommRateField'] = CThostFtdcQryMMOptionInstrCommRateField


#做市商合约手续费率
CThostFtdcMMInstrumentCommissionRateField = {}
#合约代码
CThostFtdcMMInstrumentCommissionRateField["InstrumentID"] = "string"
#投资者范围
CThostFtdcMMInstrumentCommissionRateField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcMMInstrumentCommissionRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcMMInstrumentCommissionRateField["InvestorID"] = "string"
#开仓手续费率
CThostFtdcMMInstrumentCommissionRateField["OpenRatioByMoney"] = "float"
#开仓手续费
CThostFtdcMMInstrumentCommissionRateField["OpenRatioByVolume"] = "float"
#平仓手续费率
CThostFtdcMMInstrumentCommissionRateField["CloseRatioByMoney"] = "float"
#平仓手续费
CThostFtdcMMInstrumentCommissionRateField["CloseRatioByVolume"] = "float"
#平今手续费率
CThostFtdcMMInstrumentCommissionRateField["CloseTodayRatioByMoney"] = "float"
#平今手续费
CThostFtdcMMInstrumentCommissionRateField["CloseTodayRatioByVolume"] = "float"
structDict['CThostFtdcMMInstrumentCommissionRateField'] = CThostFtdcMMInstrumentCommissionRateField


#查询做市商合约手续费率
CThostFtdcQryMMInstrumentCommissionRateField = {}
#经纪公司代码
CThostFtdcQryMMInstrumentCommissionRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryMMInstrumentCommissionRateField["InvestorID"] = "string"
#合约代码
CThostFtdcQryMMInstrumentCommissionRateField["InstrumentID"] = "string"
structDict['CThostFtdcQryMMInstrumentCommissionRateField'] = CThostFtdcQryMMInstrumentCommissionRateField


#当前报单手续费的详细内容
CThostFtdcInstrumentOrderCommRateField = {}
#合约代码
CThostFtdcInstrumentOrderCommRateField["InstrumentID"] = "string"
#投资者范围
CThostFtdcInstrumentOrderCommRateField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcInstrumentOrderCommRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcInstrumentOrderCommRateField["InvestorID"] = "string"
#投机套保标志
CThostFtdcInstrumentOrderCommRateField["HedgeFlag"] = "char"
#报单手续费
CThostFtdcInstrumentOrderCommRateField["OrderCommByVolume"] = "float"
#撤单手续费
CThostFtdcInstrumentOrderCommRateField["OrderActionCommByVolume"] = "float"
#交易所代码
CThostFtdcInstrumentOrderCommRateField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcInstrumentOrderCommRateField["InvestUnitID"] = "string"
structDict['CThostFtdcInstrumentOrderCommRateField'] = CThostFtdcInstrumentOrderCommRateField


#报单手续费率查询
CThostFtdcQryInstrumentOrderCommRateField = {}
#经纪公司代码
CThostFtdcQryInstrumentOrderCommRateField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryInstrumentOrderCommRateField["InvestorID"] = "string"
#合约代码
CThostFtdcQryInstrumentOrderCommRateField["InstrumentID"] = "string"
structDict['CThostFtdcQryInstrumentOrderCommRateField'] = CThostFtdcQryInstrumentOrderCommRateField


#交易参数
CThostFtdcTradeParamField = {}
#经纪公司代码
CThostFtdcTradeParamField["BrokerID"] = "string"
#参数代码
CThostFtdcTradeParamField["TradeParamID"] = "char"
#参数代码值
CThostFtdcTradeParamField["TradeParamValue"] = "string"
#备注
CThostFtdcTradeParamField["Memo"] = "string"
structDict['CThostFtdcTradeParamField'] = CThostFtdcTradeParamField


#合约保证金率调整
CThostFtdcInstrumentMarginRateULField = {}
#合约代码
CThostFtdcInstrumentMarginRateULField["InstrumentID"] = "string"
#投资者范围
CThostFtdcInstrumentMarginRateULField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcInstrumentMarginRateULField["BrokerID"] = "string"
#投资者代码
CThostFtdcInstrumentMarginRateULField["InvestorID"] = "string"
#投机套保标志
CThostFtdcInstrumentMarginRateULField["HedgeFlag"] = "char"
#多头保证金率
CThostFtdcInstrumentMarginRateULField["LongMarginRatioByMoney"] = "float"
#多头保证金费
CThostFtdcInstrumentMarginRateULField["LongMarginRatioByVolume"] = "float"
#空头保证金率
CThostFtdcInstrumentMarginRateULField["ShortMarginRatioByMoney"] = "float"
#空头保证金费
CThostFtdcInstrumentMarginRateULField["ShortMarginRatioByVolume"] = "float"
structDict['CThostFtdcInstrumentMarginRateULField'] = CThostFtdcInstrumentMarginRateULField


#期货持仓限制参数
CThostFtdcFutureLimitPosiParamField = {}
#投资者范围
CThostFtdcFutureLimitPosiParamField["InvestorRange"] = "char"
#经纪公司代码
CThostFtdcFutureLimitPosiParamField["BrokerID"] = "string"
#投资者代码
CThostFtdcFutureLimitPosiParamField["InvestorID"] = "string"
#产品代码
CThostFtdcFutureLimitPosiParamField["ProductID"] = "string"
#当日投机开仓数量限制
CThostFtdcFutureLimitPosiParamField["SpecOpenVolume"] = "int"
#当日套利开仓数量限制
CThostFtdcFutureLimitPosiParamField["ArbiOpenVolume"] = "int"
#当日投机+套利开仓数量限制
CThostFtdcFutureLimitPosiParamField["OpenVolume"] = "int"
structDict['CThostFtdcFutureLimitPosiParamField'] = CThostFtdcFutureLimitPosiParamField


#禁止登录IP
CThostFtdcLoginForbiddenIPField = {}
#IP地址
CThostFtdcLoginForbiddenIPField["IPAddress"] = "string"
structDict['CThostFtdcLoginForbiddenIPField'] = CThostFtdcLoginForbiddenIPField


#IP列表
CThostFtdcIPListField = {}
#IP地址
CThostFtdcIPListField["IPAddress"] = "string"
#是否白名单
CThostFtdcIPListField["IsWhite"] = "int"
structDict['CThostFtdcIPListField'] = CThostFtdcIPListField


#输入的期权自对冲
CThostFtdcInputOptionSelfCloseField = {}
#经纪公司代码
CThostFtdcInputOptionSelfCloseField["BrokerID"] = "string"
#投资者代码
CThostFtdcInputOptionSelfCloseField["InvestorID"] = "string"
#合约代码
CThostFtdcInputOptionSelfCloseField["InstrumentID"] = "string"
#期权自对冲引用
CThostFtdcInputOptionSelfCloseField["OptionSelfCloseRef"] = "string"
#用户代码
CThostFtdcInputOptionSelfCloseField["UserID"] = "string"
#数量
CThostFtdcInputOptionSelfCloseField["Volume"] = "int"
#请求编号
CThostFtdcInputOptionSelfCloseField["RequestID"] = "int"
#业务单元
CThostFtdcInputOptionSelfCloseField["BusinessUnit"] = "string"
#投机套保标志
CThostFtdcInputOptionSelfCloseField["HedgeFlag"] = "char"
#期权行权的头寸是否自对冲
CThostFtdcInputOptionSelfCloseField["OptSelfCloseFlag"] = "char"
#交易所代码
CThostFtdcInputOptionSelfCloseField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcInputOptionSelfCloseField["InvestUnitID"] = "string"
#资金账号
CThostFtdcInputOptionSelfCloseField["AccountID"] = "string"
#币种代码
CThostFtdcInputOptionSelfCloseField["CurrencyID"] = "string"
#交易编码
CThostFtdcInputOptionSelfCloseField["ClientID"] = "string"
#IP地址
CThostFtdcInputOptionSelfCloseField["IPAddress"] = "string"
#Mac地址
CThostFtdcInputOptionSelfCloseField["MacAddress"] = "string"
structDict['CThostFtdcInputOptionSelfCloseField'] = CThostFtdcInputOptionSelfCloseField


#输入期权自对冲操作
CThostFtdcInputOptionSelfCloseActionField = {}
#经纪公司代码
CThostFtdcInputOptionSelfCloseActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcInputOptionSelfCloseActionField["InvestorID"] = "string"
#期权自对冲操作引用
CThostFtdcInputOptionSelfCloseActionField["OptionSelfCloseActionRef"] = "int"
#期权自对冲引用
CThostFtdcInputOptionSelfCloseActionField["OptionSelfCloseRef"] = "string"
#请求编号
CThostFtdcInputOptionSelfCloseActionField["RequestID"] = "int"
#前置编号
CThostFtdcInputOptionSelfCloseActionField["FrontID"] = "int"
#会话编号
CThostFtdcInputOptionSelfCloseActionField["SessionID"] = "int"
#交易所代码
CThostFtdcInputOptionSelfCloseActionField["ExchangeID"] = "string"
#期权自对冲操作编号
CThostFtdcInputOptionSelfCloseActionField["OptionSelfCloseSysID"] = "string"
#操作标志
CThostFtdcInputOptionSelfCloseActionField["ActionFlag"] = "char"
#用户代码
CThostFtdcInputOptionSelfCloseActionField["UserID"] = "string"
#合约代码
CThostFtdcInputOptionSelfCloseActionField["InstrumentID"] = "string"
#投资单元代码
CThostFtdcInputOptionSelfCloseActionField["InvestUnitID"] = "string"
#IP地址
CThostFtdcInputOptionSelfCloseActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcInputOptionSelfCloseActionField["MacAddress"] = "string"
structDict['CThostFtdcInputOptionSelfCloseActionField'] = CThostFtdcInputOptionSelfCloseActionField


#期权自对冲
CThostFtdcOptionSelfCloseField = {}
#经纪公司代码
CThostFtdcOptionSelfCloseField["BrokerID"] = "string"
#投资者代码
CThostFtdcOptionSelfCloseField["InvestorID"] = "string"
#合约代码
CThostFtdcOptionSelfCloseField["InstrumentID"] = "string"
#期权自对冲引用
CThostFtdcOptionSelfCloseField["OptionSelfCloseRef"] = "string"
#用户代码
CThostFtdcOptionSelfCloseField["UserID"] = "string"
#数量
CThostFtdcOptionSelfCloseField["Volume"] = "int"
#请求编号
CThostFtdcOptionSelfCloseField["RequestID"] = "int"
#业务单元
CThostFtdcOptionSelfCloseField["BusinessUnit"] = "string"
#投机套保标志
CThostFtdcOptionSelfCloseField["HedgeFlag"] = "char"
#期权行权的头寸是否自对冲
CThostFtdcOptionSelfCloseField["OptSelfCloseFlag"] = "char"
#本地期权自对冲编号
CThostFtdcOptionSelfCloseField["OptionSelfCloseLocalID"] = "string"
#交易所代码
CThostFtdcOptionSelfCloseField["ExchangeID"] = "string"
#会员代码
CThostFtdcOptionSelfCloseField["ParticipantID"] = "string"
#客户代码
CThostFtdcOptionSelfCloseField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcOptionSelfCloseField["ExchangeInstID"] = "string"
#交易所交易员代码
CThostFtdcOptionSelfCloseField["TraderID"] = "string"
#安装编号
CThostFtdcOptionSelfCloseField["InstallID"] = "int"
#期权自对冲提交状态
CThostFtdcOptionSelfCloseField["OrderSubmitStatus"] = "char"
#报单提示序号
CThostFtdcOptionSelfCloseField["NotifySequence"] = "int"
#交易日
CThostFtdcOptionSelfCloseField["TradingDay"] = "string"
#结算编号
CThostFtdcOptionSelfCloseField["SettlementID"] = "int"
#期权自对冲编号
CThostFtdcOptionSelfCloseField["OptionSelfCloseSysID"] = "string"
#报单日期
CThostFtdcOptionSelfCloseField["InsertDate"] = "string"
#插入时间
CThostFtdcOptionSelfCloseField["InsertTime"] = "string"
#撤销时间
CThostFtdcOptionSelfCloseField["CancelTime"] = "string"
#自对冲结果
CThostFtdcOptionSelfCloseField["ExecResult"] = "char"
#结算会员编号
CThostFtdcOptionSelfCloseField["ClearingPartID"] = "string"
#序号
CThostFtdcOptionSelfCloseField["SequenceNo"] = "int"
#前置编号
CThostFtdcOptionSelfCloseField["FrontID"] = "int"
#会话编号
CThostFtdcOptionSelfCloseField["SessionID"] = "int"
#用户端产品信息
CThostFtdcOptionSelfCloseField["UserProductInfo"] = "string"
#状态信息
CThostFtdcOptionSelfCloseField["StatusMsg"] = "string"
#操作用户代码
CThostFtdcOptionSelfCloseField["ActiveUserID"] = "string"
#经纪公司报单编号
CThostFtdcOptionSelfCloseField["BrokerOptionSelfCloseSeq"] = "int"
#营业部编号
CThostFtdcOptionSelfCloseField["BranchID"] = "string"
#投资单元代码
CThostFtdcOptionSelfCloseField["InvestUnitID"] = "string"
#资金账号
CThostFtdcOptionSelfCloseField["AccountID"] = "string"
#币种代码
CThostFtdcOptionSelfCloseField["CurrencyID"] = "string"
#IP地址
CThostFtdcOptionSelfCloseField["IPAddress"] = "string"
#Mac地址
CThostFtdcOptionSelfCloseField["MacAddress"] = "string"
structDict['CThostFtdcOptionSelfCloseField'] = CThostFtdcOptionSelfCloseField


#期权自对冲操作
CThostFtdcOptionSelfCloseActionField = {}
#经纪公司代码
CThostFtdcOptionSelfCloseActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcOptionSelfCloseActionField["InvestorID"] = "string"
#期权自对冲操作引用
CThostFtdcOptionSelfCloseActionField["OptionSelfCloseActionRef"] = "int"
#期权自对冲引用
CThostFtdcOptionSelfCloseActionField["OptionSelfCloseRef"] = "string"
#请求编号
CThostFtdcOptionSelfCloseActionField["RequestID"] = "int"
#前置编号
CThostFtdcOptionSelfCloseActionField["FrontID"] = "int"
#会话编号
CThostFtdcOptionSelfCloseActionField["SessionID"] = "int"
#交易所代码
CThostFtdcOptionSelfCloseActionField["ExchangeID"] = "string"
#期权自对冲操作编号
CThostFtdcOptionSelfCloseActionField["OptionSelfCloseSysID"] = "string"
#操作标志
CThostFtdcOptionSelfCloseActionField["ActionFlag"] = "char"
#操作日期
CThostFtdcOptionSelfCloseActionField["ActionDate"] = "string"
#操作时间
CThostFtdcOptionSelfCloseActionField["ActionTime"] = "string"
#交易所交易员代码
CThostFtdcOptionSelfCloseActionField["TraderID"] = "string"
#安装编号
CThostFtdcOptionSelfCloseActionField["InstallID"] = "int"
#本地期权自对冲编号
CThostFtdcOptionSelfCloseActionField["OptionSelfCloseLocalID"] = "string"
#操作本地编号
CThostFtdcOptionSelfCloseActionField["ActionLocalID"] = "string"
#会员代码
CThostFtdcOptionSelfCloseActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcOptionSelfCloseActionField["ClientID"] = "string"
#业务单元
CThostFtdcOptionSelfCloseActionField["BusinessUnit"] = "string"
#报单操作状态
CThostFtdcOptionSelfCloseActionField["OrderActionStatus"] = "char"
#用户代码
CThostFtdcOptionSelfCloseActionField["UserID"] = "string"
#状态信息
CThostFtdcOptionSelfCloseActionField["StatusMsg"] = "string"
#合约代码
CThostFtdcOptionSelfCloseActionField["InstrumentID"] = "string"
#营业部编号
CThostFtdcOptionSelfCloseActionField["BranchID"] = "string"
#投资单元代码
CThostFtdcOptionSelfCloseActionField["InvestUnitID"] = "string"
#IP地址
CThostFtdcOptionSelfCloseActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcOptionSelfCloseActionField["MacAddress"] = "string"
structDict['CThostFtdcOptionSelfCloseActionField'] = CThostFtdcOptionSelfCloseActionField


#期权自对冲查询
CThostFtdcQryOptionSelfCloseField = {}
#经纪公司代码
CThostFtdcQryOptionSelfCloseField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryOptionSelfCloseField["InvestorID"] = "string"
#合约代码
CThostFtdcQryOptionSelfCloseField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryOptionSelfCloseField["ExchangeID"] = "string"
#期权自对冲编号
CThostFtdcQryOptionSelfCloseField["OptionSelfCloseSysID"] = "string"
#开始时间
CThostFtdcQryOptionSelfCloseField["InsertTimeStart"] = "string"
#结束时间
CThostFtdcQryOptionSelfCloseField["InsertTimeEnd"] = "string"
structDict['CThostFtdcQryOptionSelfCloseField'] = CThostFtdcQryOptionSelfCloseField


#交易所期权自对冲信息
CThostFtdcExchangeOptionSelfCloseField = {}
#数量
CThostFtdcExchangeOptionSelfCloseField["Volume"] = "int"
#请求编号
CThostFtdcExchangeOptionSelfCloseField["RequestID"] = "int"
#业务单元
CThostFtdcExchangeOptionSelfCloseField["BusinessUnit"] = "string"
#投机套保标志
CThostFtdcExchangeOptionSelfCloseField["HedgeFlag"] = "char"
#期权行权的头寸是否自对冲
CThostFtdcExchangeOptionSelfCloseField["OptSelfCloseFlag"] = "char"
#本地期权自对冲编号
CThostFtdcExchangeOptionSelfCloseField["OptionSelfCloseLocalID"] = "string"
#交易所代码
CThostFtdcExchangeOptionSelfCloseField["ExchangeID"] = "string"
#会员代码
CThostFtdcExchangeOptionSelfCloseField["ParticipantID"] = "string"
#客户代码
CThostFtdcExchangeOptionSelfCloseField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcExchangeOptionSelfCloseField["ExchangeInstID"] = "string"
#交易所交易员代码
CThostFtdcExchangeOptionSelfCloseField["TraderID"] = "string"
#安装编号
CThostFtdcExchangeOptionSelfCloseField["InstallID"] = "int"
#期权自对冲提交状态
CThostFtdcExchangeOptionSelfCloseField["OrderSubmitStatus"] = "char"
#报单提示序号
CThostFtdcExchangeOptionSelfCloseField["NotifySequence"] = "int"
#交易日
CThostFtdcExchangeOptionSelfCloseField["TradingDay"] = "string"
#结算编号
CThostFtdcExchangeOptionSelfCloseField["SettlementID"] = "int"
#期权自对冲编号
CThostFtdcExchangeOptionSelfCloseField["OptionSelfCloseSysID"] = "string"
#报单日期
CThostFtdcExchangeOptionSelfCloseField["InsertDate"] = "string"
#插入时间
CThostFtdcExchangeOptionSelfCloseField["InsertTime"] = "string"
#撤销时间
CThostFtdcExchangeOptionSelfCloseField["CancelTime"] = "string"
#自对冲结果
CThostFtdcExchangeOptionSelfCloseField["ExecResult"] = "char"
#结算会员编号
CThostFtdcExchangeOptionSelfCloseField["ClearingPartID"] = "string"
#序号
CThostFtdcExchangeOptionSelfCloseField["SequenceNo"] = "int"
#营业部编号
CThostFtdcExchangeOptionSelfCloseField["BranchID"] = "string"
#IP地址
CThostFtdcExchangeOptionSelfCloseField["IPAddress"] = "string"
#Mac地址
CThostFtdcExchangeOptionSelfCloseField["MacAddress"] = "string"
structDict['CThostFtdcExchangeOptionSelfCloseField'] = CThostFtdcExchangeOptionSelfCloseField


#期权自对冲操作查询
CThostFtdcQryOptionSelfCloseActionField = {}
#经纪公司代码
CThostFtdcQryOptionSelfCloseActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryOptionSelfCloseActionField["InvestorID"] = "string"
#交易所代码
CThostFtdcQryOptionSelfCloseActionField["ExchangeID"] = "string"
structDict['CThostFtdcQryOptionSelfCloseActionField'] = CThostFtdcQryOptionSelfCloseActionField


#交易所期权自对冲操作
CThostFtdcExchangeOptionSelfCloseActionField = {}
#交易所代码
CThostFtdcExchangeOptionSelfCloseActionField["ExchangeID"] = "string"
#期权自对冲操作编号
CThostFtdcExchangeOptionSelfCloseActionField["OptionSelfCloseSysID"] = "string"
#操作标志
CThostFtdcExchangeOptionSelfCloseActionField["ActionFlag"] = "char"
#操作日期
CThostFtdcExchangeOptionSelfCloseActionField["ActionDate"] = "string"
#操作时间
CThostFtdcExchangeOptionSelfCloseActionField["ActionTime"] = "string"
#交易所交易员代码
CThostFtdcExchangeOptionSelfCloseActionField["TraderID"] = "string"
#安装编号
CThostFtdcExchangeOptionSelfCloseActionField["InstallID"] = "int"
#本地期权自对冲编号
CThostFtdcExchangeOptionSelfCloseActionField["OptionSelfCloseLocalID"] = "string"
#操作本地编号
CThostFtdcExchangeOptionSelfCloseActionField["ActionLocalID"] = "string"
#会员代码
CThostFtdcExchangeOptionSelfCloseActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcExchangeOptionSelfCloseActionField["ClientID"] = "string"
#业务单元
CThostFtdcExchangeOptionSelfCloseActionField["BusinessUnit"] = "string"
#报单操作状态
CThostFtdcExchangeOptionSelfCloseActionField["OrderActionStatus"] = "char"
#用户代码
CThostFtdcExchangeOptionSelfCloseActionField["UserID"] = "string"
#营业部编号
CThostFtdcExchangeOptionSelfCloseActionField["BranchID"] = "string"
#IP地址
CThostFtdcExchangeOptionSelfCloseActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcExchangeOptionSelfCloseActionField["MacAddress"] = "string"
#合约在交易所的代码
CThostFtdcExchangeOptionSelfCloseActionField["ExchangeInstID"] = "string"
#期权行权的头寸是否自对冲
CThostFtdcExchangeOptionSelfCloseActionField["OptSelfCloseFlag"] = "char"
structDict['CThostFtdcExchangeOptionSelfCloseActionField'] = CThostFtdcExchangeOptionSelfCloseActionField


#延时换汇同步
CThostFtdcSyncDelaySwapField = {}
#换汇流水号
CThostFtdcSyncDelaySwapField["DelaySwapSeqNo"] = "string"
#经纪公司代码
CThostFtdcSyncDelaySwapField["BrokerID"] = "string"
#投资者代码
CThostFtdcSyncDelaySwapField["InvestorID"] = "string"
#源币种
CThostFtdcSyncDelaySwapField["FromCurrencyID"] = "string"
#源金额
CThostFtdcSyncDelaySwapField["FromAmount"] = "float"
#源换汇冻结金额(可用冻结)
CThostFtdcSyncDelaySwapField["FromFrozenSwap"] = "float"
#源剩余换汇额度(可提冻结)
CThostFtdcSyncDelaySwapField["FromRemainSwap"] = "float"
#目标币种
CThostFtdcSyncDelaySwapField["ToCurrencyID"] = "string"
#目标金额
CThostFtdcSyncDelaySwapField["ToAmount"] = "float"
structDict['CThostFtdcSyncDelaySwapField'] = CThostFtdcSyncDelaySwapField


#查询延时换汇同步
CThostFtdcQrySyncDelaySwapField = {}
#经纪公司代码
CThostFtdcQrySyncDelaySwapField["BrokerID"] = "string"
#延时换汇流水号
CThostFtdcQrySyncDelaySwapField["DelaySwapSeqNo"] = "string"
structDict['CThostFtdcQrySyncDelaySwapField'] = CThostFtdcQrySyncDelaySwapField


#投资单元
CThostFtdcInvestUnitField = {}
#经纪公司代码
CThostFtdcInvestUnitField["BrokerID"] = "string"
#投资者代码
CThostFtdcInvestUnitField["InvestorID"] = "string"
#投资单元代码
CThostFtdcInvestUnitField["InvestUnitID"] = "string"
#投资者单元名称
CThostFtdcInvestUnitField["InvestorUnitName"] = "string"
#投资者分组代码
CThostFtdcInvestUnitField["InvestorGroupID"] = "string"
#手续费率模板代码
CThostFtdcInvestUnitField["CommModelID"] = "string"
#保证金率模板代码
CThostFtdcInvestUnitField["MarginModelID"] = "string"
#资金账号
CThostFtdcInvestUnitField["AccountID"] = "string"
#币种代码
CThostFtdcInvestUnitField["CurrencyID"] = "string"
structDict['CThostFtdcInvestUnitField'] = CThostFtdcInvestUnitField


#查询投资单元
CThostFtdcQryInvestUnitField = {}
#经纪公司代码
CThostFtdcQryInvestUnitField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryInvestUnitField["InvestorID"] = "string"
#投资单元代码
CThostFtdcQryInvestUnitField["InvestUnitID"] = "string"
structDict['CThostFtdcQryInvestUnitField'] = CThostFtdcQryInvestUnitField


#二级代理商资金校验模式
CThostFtdcSecAgentCheckModeField = {}
#投资者代码
CThostFtdcSecAgentCheckModeField["InvestorID"] = "string"
#经纪公司代码
CThostFtdcSecAgentCheckModeField["BrokerID"] = "string"
#币种
CThostFtdcSecAgentCheckModeField["CurrencyID"] = "string"
#境外中介机构资金帐号
CThostFtdcSecAgentCheckModeField["BrokerSecAgentID"] = "string"
#是否需要校验自己的资金账户
CThostFtdcSecAgentCheckModeField["CheckSelfAccount"] = "int"
structDict['CThostFtdcSecAgentCheckModeField'] = CThostFtdcSecAgentCheckModeField


#二级代理商信息
CThostFtdcSecAgentTradeInfoField = {}
#经纪公司代码
CThostFtdcSecAgentTradeInfoField["BrokerID"] = "string"
#境外中介机构资金帐号
CThostFtdcSecAgentTradeInfoField["BrokerSecAgentID"] = "string"
#投资者代码
CThostFtdcSecAgentTradeInfoField["InvestorID"] = "string"
#二级代理商姓名
CThostFtdcSecAgentTradeInfoField["LongCustomerName"] = "string"
structDict['CThostFtdcSecAgentTradeInfoField'] = CThostFtdcSecAgentTradeInfoField


#市场行情
CThostFtdcMarketDataField = {}
#交易日
CThostFtdcMarketDataField["TradingDay"] = "string"
#合约代码
CThostFtdcMarketDataField["InstrumentID"] = "string"
#交易所代码
CThostFtdcMarketDataField["ExchangeID"] = "string"
#合约在交易所的代码
CThostFtdcMarketDataField["ExchangeInstID"] = "string"
#最新价
CThostFtdcMarketDataField["LastPrice"] = "float"
#上次结算价
CThostFtdcMarketDataField["PreSettlementPrice"] = "float"
#昨收盘
CThostFtdcMarketDataField["PreClosePrice"] = "float"
#昨持仓量
CThostFtdcMarketDataField["PreOpenInterest"] = "float"
#今开盘
CThostFtdcMarketDataField["OpenPrice"] = "float"
#最高价
CThostFtdcMarketDataField["HighestPrice"] = "float"
#最低价
CThostFtdcMarketDataField["LowestPrice"] = "float"
#数量
CThostFtdcMarketDataField["Volume"] = "int"
#成交金额
CThostFtdcMarketDataField["Turnover"] = "float"
#持仓量
CThostFtdcMarketDataField["OpenInterest"] = "float"
#今收盘
CThostFtdcMarketDataField["ClosePrice"] = "float"
#本次结算价
CThostFtdcMarketDataField["SettlementPrice"] = "float"
#涨停板价
CThostFtdcMarketDataField["UpperLimitPrice"] = "float"
#跌停板价
CThostFtdcMarketDataField["LowerLimitPrice"] = "float"
#昨虚实度
CThostFtdcMarketDataField["PreDelta"] = "float"
#今虚实度
CThostFtdcMarketDataField["CurrDelta"] = "float"
#最后修改时间
CThostFtdcMarketDataField["UpdateTime"] = "string"
#最后修改毫秒
CThostFtdcMarketDataField["UpdateMillisec"] = "int"
#业务日期
CThostFtdcMarketDataField["ActionDay"] = "string"
structDict['CThostFtdcMarketDataField'] = CThostFtdcMarketDataField


#行情基础属性
CThostFtdcMarketDataBaseField = {}
#交易日
CThostFtdcMarketDataBaseField["TradingDay"] = "string"
#上次结算价
CThostFtdcMarketDataBaseField["PreSettlementPrice"] = "float"
#昨收盘
CThostFtdcMarketDataBaseField["PreClosePrice"] = "float"
#昨持仓量
CThostFtdcMarketDataBaseField["PreOpenInterest"] = "float"
#昨虚实度
CThostFtdcMarketDataBaseField["PreDelta"] = "float"
structDict['CThostFtdcMarketDataBaseField'] = CThostFtdcMarketDataBaseField


#行情静态属性
CThostFtdcMarketDataStaticField = {}
#今开盘
CThostFtdcMarketDataStaticField["OpenPrice"] = "float"
#最高价
CThostFtdcMarketDataStaticField["HighestPrice"] = "float"
#最低价
CThostFtdcMarketDataStaticField["LowestPrice"] = "float"
#今收盘
CThostFtdcMarketDataStaticField["ClosePrice"] = "float"
#涨停板价
CThostFtdcMarketDataStaticField["UpperLimitPrice"] = "float"
#跌停板价
CThostFtdcMarketDataStaticField["LowerLimitPrice"] = "float"
#本次结算价
CThostFtdcMarketDataStaticField["SettlementPrice"] = "float"
#今虚实度
CThostFtdcMarketDataStaticField["CurrDelta"] = "float"
structDict['CThostFtdcMarketDataStaticField'] = CThostFtdcMarketDataStaticField


#行情最新成交属性
CThostFtdcMarketDataLastMatchField = {}
#最新价
CThostFtdcMarketDataLastMatchField["LastPrice"] = "float"
#数量
CThostFtdcMarketDataLastMatchField["Volume"] = "int"
#成交金额
CThostFtdcMarketDataLastMatchField["Turnover"] = "float"
#持仓量
CThostFtdcMarketDataLastMatchField["OpenInterest"] = "float"
structDict['CThostFtdcMarketDataLastMatchField'] = CThostFtdcMarketDataLastMatchField


#行情最优价属性
CThostFtdcMarketDataBestPriceField = {}
#申买价一
CThostFtdcMarketDataBestPriceField["BidPrice1"] = "float"
#申买量一
CThostFtdcMarketDataBestPriceField["BidVolume1"] = "int"
#申卖价一
CThostFtdcMarketDataBestPriceField["AskPrice1"] = "float"
#申卖量一
CThostFtdcMarketDataBestPriceField["AskVolume1"] = "int"
structDict['CThostFtdcMarketDataBestPriceField'] = CThostFtdcMarketDataBestPriceField


#行情申买二、三属性
CThostFtdcMarketDataBid23Field = {}
#申买价二
CThostFtdcMarketDataBid23Field["BidPrice2"] = "float"
#申买量二
CThostFtdcMarketDataBid23Field["BidVolume2"] = "int"
#申买价三
CThostFtdcMarketDataBid23Field["BidPrice3"] = "float"
#申买量三
CThostFtdcMarketDataBid23Field["BidVolume3"] = "int"
structDict['CThostFtdcMarketDataBid23Field'] = CThostFtdcMarketDataBid23Field


#行情申卖二、三属性
CThostFtdcMarketDataAsk23Field = {}
#申卖价二
CThostFtdcMarketDataAsk23Field["AskPrice2"] = "float"
#申卖量二
CThostFtdcMarketDataAsk23Field["AskVolume2"] = "int"
#申卖价三
CThostFtdcMarketDataAsk23Field["AskPrice3"] = "float"
#申卖量三
CThostFtdcMarketDataAsk23Field["AskVolume3"] = "int"
structDict['CThostFtdcMarketDataAsk23Field'] = CThostFtdcMarketDataAsk23Field


#行情申买四、五属性
CThostFtdcMarketDataBid45Field = {}
#申买价四
CThostFtdcMarketDataBid45Field["BidPrice4"] = "float"
#申买量四
CThostFtdcMarketDataBid45Field["BidVolume4"] = "int"
#申买价五
CThostFtdcMarketDataBid45Field["BidPrice5"] = "float"
#申买量五
CThostFtdcMarketDataBid45Field["BidVolume5"] = "int"
structDict['CThostFtdcMarketDataBid45Field'] = CThostFtdcMarketDataBid45Field


#行情申卖四、五属性
CThostFtdcMarketDataAsk45Field = {}
#申卖价四
CThostFtdcMarketDataAsk45Field["AskPrice4"] = "float"
#申卖量四
CThostFtdcMarketDataAsk45Field["AskVolume4"] = "int"
#申卖价五
CThostFtdcMarketDataAsk45Field["AskPrice5"] = "float"
#申卖量五
CThostFtdcMarketDataAsk45Field["AskVolume5"] = "int"
structDict['CThostFtdcMarketDataAsk45Field'] = CThostFtdcMarketDataAsk45Field


#行情更新时间属性
CThostFtdcMarketDataUpdateTimeField = {}
#合约代码
CThostFtdcMarketDataUpdateTimeField["InstrumentID"] = "string"
#最后修改时间
CThostFtdcMarketDataUpdateTimeField["UpdateTime"] = "string"
#最后修改毫秒
CThostFtdcMarketDataUpdateTimeField["UpdateMillisec"] = "int"
#业务日期
CThostFtdcMarketDataUpdateTimeField["ActionDay"] = "string"
structDict['CThostFtdcMarketDataUpdateTimeField'] = CThostFtdcMarketDataUpdateTimeField


#行情交易所代码属性
CThostFtdcMarketDataExchangeField = {}
#交易所代码
CThostFtdcMarketDataExchangeField["ExchangeID"] = "string"
structDict['CThostFtdcMarketDataExchangeField'] = CThostFtdcMarketDataExchangeField


#指定的合约
CThostFtdcSpecificInstrumentField = {}
#合约代码
CThostFtdcSpecificInstrumentField["InstrumentID"] = "string"
structDict['CThostFtdcSpecificInstrumentField'] = CThostFtdcSpecificInstrumentField


#合约状态
CThostFtdcInstrumentStatusField = {}
#交易所代码
CThostFtdcInstrumentStatusField["ExchangeID"] = "string"
#合约在交易所的代码
CThostFtdcInstrumentStatusField["ExchangeInstID"] = "string"
#结算组代码
CThostFtdcInstrumentStatusField["SettlementGroupID"] = "string"
#合约代码
CThostFtdcInstrumentStatusField["InstrumentID"] = "string"
#合约交易状态
CThostFtdcInstrumentStatusField["InstrumentStatus"] = "char"
#交易阶段编号
CThostFtdcInstrumentStatusField["TradingSegmentSN"] = "int"
#进入本状态时间
CThostFtdcInstrumentStatusField["EnterTime"] = "string"
#进入本状态原因
CThostFtdcInstrumentStatusField["EnterReason"] = "char"
structDict['CThostFtdcInstrumentStatusField'] = CThostFtdcInstrumentStatusField


#查询合约状态
CThostFtdcQryInstrumentStatusField = {}
#交易所代码
CThostFtdcQryInstrumentStatusField["ExchangeID"] = "string"
#合约在交易所的代码
CThostFtdcQryInstrumentStatusField["ExchangeInstID"] = "string"
structDict['CThostFtdcQryInstrumentStatusField'] = CThostFtdcQryInstrumentStatusField


#投资者账户
CThostFtdcInvestorAccountField = {}
#经纪公司代码
CThostFtdcInvestorAccountField["BrokerID"] = "string"
#投资者代码
CThostFtdcInvestorAccountField["InvestorID"] = "string"
#投资者帐号
CThostFtdcInvestorAccountField["AccountID"] = "string"
#币种代码
CThostFtdcInvestorAccountField["CurrencyID"] = "string"
structDict['CThostFtdcInvestorAccountField'] = CThostFtdcInvestorAccountField


#浮动盈亏算法
CThostFtdcPositionProfitAlgorithmField = {}
#经纪公司代码
CThostFtdcPositionProfitAlgorithmField["BrokerID"] = "string"
#投资者帐号
CThostFtdcPositionProfitAlgorithmField["AccountID"] = "string"
#盈亏算法
CThostFtdcPositionProfitAlgorithmField["Algorithm"] = "char"
#备注
CThostFtdcPositionProfitAlgorithmField["Memo"] = "string"
#币种代码
CThostFtdcPositionProfitAlgorithmField["CurrencyID"] = "string"
structDict['CThostFtdcPositionProfitAlgorithmField'] = CThostFtdcPositionProfitAlgorithmField


#会员资金折扣
CThostFtdcDiscountField = {}
#经纪公司代码
CThostFtdcDiscountField["BrokerID"] = "string"
#投资者范围
CThostFtdcDiscountField["InvestorRange"] = "char"
#投资者代码
CThostFtdcDiscountField["InvestorID"] = "string"
#资金折扣比例
CThostFtdcDiscountField["Discount"] = "float"
structDict['CThostFtdcDiscountField'] = CThostFtdcDiscountField


#查询转帐银行
CThostFtdcQryTransferBankField = {}
#银行代码
CThostFtdcQryTransferBankField["BankID"] = "string"
#银行分中心代码
CThostFtdcQryTransferBankField["BankBrchID"] = "string"
structDict['CThostFtdcQryTransferBankField'] = CThostFtdcQryTransferBankField


#转帐银行
CThostFtdcTransferBankField = {}
#银行代码
CThostFtdcTransferBankField["BankID"] = "string"
#银行分中心代码
CThostFtdcTransferBankField["BankBrchID"] = "string"
#银行名称
CThostFtdcTransferBankField["BankName"] = "string"
#是否活跃
CThostFtdcTransferBankField["IsActive"] = "int"
structDict['CThostFtdcTransferBankField'] = CThostFtdcTransferBankField


#查询投资者持仓明细
CThostFtdcQryInvestorPositionDetailField = {}
#经纪公司代码
CThostFtdcQryInvestorPositionDetailField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryInvestorPositionDetailField["InvestorID"] = "string"
#合约代码
CThostFtdcQryInvestorPositionDetailField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryInvestorPositionDetailField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcQryInvestorPositionDetailField["InvestUnitID"] = "string"
structDict['CThostFtdcQryInvestorPositionDetailField'] = CThostFtdcQryInvestorPositionDetailField


#投资者持仓明细
CThostFtdcInvestorPositionDetailField = {}
#合约代码
CThostFtdcInvestorPositionDetailField["InstrumentID"] = "string"
#经纪公司代码
CThostFtdcInvestorPositionDetailField["BrokerID"] = "string"
#投资者代码
CThostFtdcInvestorPositionDetailField["InvestorID"] = "string"
#投机套保标志
CThostFtdcInvestorPositionDetailField["HedgeFlag"] = "char"
#买卖
CThostFtdcInvestorPositionDetailField["Direction"] = "char"
#开仓日期
CThostFtdcInvestorPositionDetailField["OpenDate"] = "string"
#成交编号
CThostFtdcInvestorPositionDetailField["TradeID"] = "string"
#数量
CThostFtdcInvestorPositionDetailField["Volume"] = "int"
#开仓价
CThostFtdcInvestorPositionDetailField["OpenPrice"] = "float"
#交易日
CThostFtdcInvestorPositionDetailField["TradingDay"] = "string"
#结算编号
CThostFtdcInvestorPositionDetailField["SettlementID"] = "int"
#成交类型
CThostFtdcInvestorPositionDetailField["TradeType"] = "char"
#组合合约代码
CThostFtdcInvestorPositionDetailField["CombInstrumentID"] = "string"
#交易所代码
CThostFtdcInvestorPositionDetailField["ExchangeID"] = "string"
#逐日盯市平仓盈亏
CThostFtdcInvestorPositionDetailField["CloseProfitByDate"] = "float"
#逐笔对冲平仓盈亏
CThostFtdcInvestorPositionDetailField["CloseProfitByTrade"] = "float"
#逐日盯市持仓盈亏
CThostFtdcInvestorPositionDetailField["PositionProfitByDate"] = "float"
#逐笔对冲持仓盈亏
CThostFtdcInvestorPositionDetailField["PositionProfitByTrade"] = "float"
#投资者保证金
CThostFtdcInvestorPositionDetailField["Margin"] = "float"
#交易所保证金
CThostFtdcInvestorPositionDetailField["ExchMargin"] = "float"
#保证金率
CThostFtdcInvestorPositionDetailField["MarginRateByMoney"] = "float"
#保证金率(按手数)
CThostFtdcInvestorPositionDetailField["MarginRateByVolume"] = "float"
#昨结算价
CThostFtdcInvestorPositionDetailField["LastSettlementPrice"] = "float"
#结算价
CThostFtdcInvestorPositionDetailField["SettlementPrice"] = "float"
#平仓量
CThostFtdcInvestorPositionDetailField["CloseVolume"] = "int"
#平仓金额
CThostFtdcInvestorPositionDetailField["CloseAmount"] = "float"
#投资单元代码
CThostFtdcInvestorPositionDetailField["InvestUnitID"] = "string"
structDict['CThostFtdcInvestorPositionDetailField'] = CThostFtdcInvestorPositionDetailField


#资金账户口令域
CThostFtdcTradingAccountPasswordField = {}
#经纪公司代码
CThostFtdcTradingAccountPasswordField["BrokerID"] = "string"
#投资者帐号
CThostFtdcTradingAccountPasswordField["AccountID"] = "string"
#密码
CThostFtdcTradingAccountPasswordField["Password"] = "string"
#币种代码
CThostFtdcTradingAccountPasswordField["CurrencyID"] = "string"
structDict['CThostFtdcTradingAccountPasswordField'] = CThostFtdcTradingAccountPasswordField


#交易所行情报盘机
CThostFtdcMDTraderOfferField = {}
#交易所代码
CThostFtdcMDTraderOfferField["ExchangeID"] = "string"
#交易所交易员代码
CThostFtdcMDTraderOfferField["TraderID"] = "string"
#会员代码
CThostFtdcMDTraderOfferField["ParticipantID"] = "string"
#密码
CThostFtdcMDTraderOfferField["Password"] = "string"
#安装编号
CThostFtdcMDTraderOfferField["InstallID"] = "int"
#本地报单编号
CThostFtdcMDTraderOfferField["OrderLocalID"] = "string"
#交易所交易员连接状态
CThostFtdcMDTraderOfferField["TraderConnectStatus"] = "char"
#发出连接请求的日期
CThostFtdcMDTraderOfferField["ConnectRequestDate"] = "string"
#发出连接请求的时间
CThostFtdcMDTraderOfferField["ConnectRequestTime"] = "string"
#上次报告日期
CThostFtdcMDTraderOfferField["LastReportDate"] = "string"
#上次报告时间
CThostFtdcMDTraderOfferField["LastReportTime"] = "string"
#完成连接日期
CThostFtdcMDTraderOfferField["ConnectDate"] = "string"
#完成连接时间
CThostFtdcMDTraderOfferField["ConnectTime"] = "string"
#启动日期
CThostFtdcMDTraderOfferField["StartDate"] = "string"
#启动时间
CThostFtdcMDTraderOfferField["StartTime"] = "string"
#交易日
CThostFtdcMDTraderOfferField["TradingDay"] = "string"
#经纪公司代码
CThostFtdcMDTraderOfferField["BrokerID"] = "string"
#本席位最大成交编号
CThostFtdcMDTraderOfferField["MaxTradeID"] = "string"
#本席位最大报单备拷
CThostFtdcMDTraderOfferField["MaxOrderMessageReference"] = "string"
structDict['CThostFtdcMDTraderOfferField'] = CThostFtdcMDTraderOfferField


#查询行情报盘机
CThostFtdcQryMDTraderOfferField = {}
#交易所代码
CThostFtdcQryMDTraderOfferField["ExchangeID"] = "string"
#会员代码
CThostFtdcQryMDTraderOfferField["ParticipantID"] = "string"
#交易所交易员代码
CThostFtdcQryMDTraderOfferField["TraderID"] = "string"
structDict['CThostFtdcQryMDTraderOfferField'] = CThostFtdcQryMDTraderOfferField


#查询客户通知
CThostFtdcQryNoticeField = {}
#经纪公司代码
CThostFtdcQryNoticeField["BrokerID"] = "string"
structDict['CThostFtdcQryNoticeField'] = CThostFtdcQryNoticeField


#客户通知
CThostFtdcNoticeField = {}
#经纪公司代码
CThostFtdcNoticeField["BrokerID"] = "string"
#消息正文
CThostFtdcNoticeField["Content"] = "string"
#经纪公司通知内容序列号
CThostFtdcNoticeField["SequenceLabel"] = "string"
structDict['CThostFtdcNoticeField'] = CThostFtdcNoticeField


#用户权限
CThostFtdcUserRightField = {}
#经纪公司代码
CThostFtdcUserRightField["BrokerID"] = "string"
#用户代码
CThostFtdcUserRightField["UserID"] = "string"
#客户权限类型
CThostFtdcUserRightField["UserRightType"] = "char"
#是否禁止
CThostFtdcUserRightField["IsForbidden"] = "int"
structDict['CThostFtdcUserRightField'] = CThostFtdcUserRightField


#查询结算信息确认域
CThostFtdcQrySettlementInfoConfirmField = {}
#经纪公司代码
CThostFtdcQrySettlementInfoConfirmField["BrokerID"] = "string"
#投资者代码
CThostFtdcQrySettlementInfoConfirmField["InvestorID"] = "string"
#投资者帐号
CThostFtdcQrySettlementInfoConfirmField["AccountID"] = "string"
#币种代码
CThostFtdcQrySettlementInfoConfirmField["CurrencyID"] = "string"
structDict['CThostFtdcQrySettlementInfoConfirmField'] = CThostFtdcQrySettlementInfoConfirmField


#装载结算信息
CThostFtdcLoadSettlementInfoField = {}
#经纪公司代码
CThostFtdcLoadSettlementInfoField["BrokerID"] = "string"
structDict['CThostFtdcLoadSettlementInfoField'] = CThostFtdcLoadSettlementInfoField


#经纪公司可提资金算法表
CThostFtdcBrokerWithdrawAlgorithmField = {}
#经纪公司代码
CThostFtdcBrokerWithdrawAlgorithmField["BrokerID"] = "string"
#可提资金算法
CThostFtdcBrokerWithdrawAlgorithmField["WithdrawAlgorithm"] = "char"
#资金使用率
CThostFtdcBrokerWithdrawAlgorithmField["UsingRatio"] = "float"
#可提是否包含平仓盈利
CThostFtdcBrokerWithdrawAlgorithmField["IncludeCloseProfit"] = "char"
#本日无仓且无成交客户是否受可提比例限制
CThostFtdcBrokerWithdrawAlgorithmField["AllWithoutTrade"] = "char"
#可用是否包含平仓盈利
CThostFtdcBrokerWithdrawAlgorithmField["AvailIncludeCloseProfit"] = "char"
#是否启用用户事件
CThostFtdcBrokerWithdrawAlgorithmField["IsBrokerUserEvent"] = "int"
#币种代码
CThostFtdcBrokerWithdrawAlgorithmField["CurrencyID"] = "string"
#货币质押比率
CThostFtdcBrokerWithdrawAlgorithmField["FundMortgageRatio"] = "float"
#权益算法
CThostFtdcBrokerWithdrawAlgorithmField["BalanceAlgorithm"] = "char"
structDict['CThostFtdcBrokerWithdrawAlgorithmField'] = CThostFtdcBrokerWithdrawAlgorithmField


#资金账户口令变更域
CThostFtdcTradingAccountPasswordUpdateV1Field = {}
#经纪公司代码
CThostFtdcTradingAccountPasswordUpdateV1Field["BrokerID"] = "string"
#投资者代码
CThostFtdcTradingAccountPasswordUpdateV1Field["InvestorID"] = "string"
#原来的口令
CThostFtdcTradingAccountPasswordUpdateV1Field["OldPassword"] = "string"
#新的口令
CThostFtdcTradingAccountPasswordUpdateV1Field["NewPassword"] = "string"
structDict['CThostFtdcTradingAccountPasswordUpdateV1Field'] = CThostFtdcTradingAccountPasswordUpdateV1Field


#资金账户口令变更域
CThostFtdcTradingAccountPasswordUpdateField = {}
#经纪公司代码
CThostFtdcTradingAccountPasswordUpdateField["BrokerID"] = "string"
#投资者帐号
CThostFtdcTradingAccountPasswordUpdateField["AccountID"] = "string"
#原来的口令
CThostFtdcTradingAccountPasswordUpdateField["OldPassword"] = "string"
#新的口令
CThostFtdcTradingAccountPasswordUpdateField["NewPassword"] = "string"
#币种代码
CThostFtdcTradingAccountPasswordUpdateField["CurrencyID"] = "string"
structDict['CThostFtdcTradingAccountPasswordUpdateField'] = CThostFtdcTradingAccountPasswordUpdateField


#查询组合合约分腿
CThostFtdcQryCombinationLegField = {}
#组合合约代码
CThostFtdcQryCombinationLegField["CombInstrumentID"] = "string"
#单腿编号
CThostFtdcQryCombinationLegField["LegID"] = "int"
#单腿合约代码
CThostFtdcQryCombinationLegField["LegInstrumentID"] = "string"
structDict['CThostFtdcQryCombinationLegField'] = CThostFtdcQryCombinationLegField


#查询组合合约分腿
CThostFtdcQrySyncStatusField = {}
#交易日
CThostFtdcQrySyncStatusField["TradingDay"] = "string"
structDict['CThostFtdcQrySyncStatusField'] = CThostFtdcQrySyncStatusField


#组合交易合约的单腿
CThostFtdcCombinationLegField = {}
#组合合约代码
CThostFtdcCombinationLegField["CombInstrumentID"] = "string"
#单腿编号
CThostFtdcCombinationLegField["LegID"] = "int"
#单腿合约代码
CThostFtdcCombinationLegField["LegInstrumentID"] = "string"
#买卖方向
CThostFtdcCombinationLegField["Direction"] = "char"
#单腿乘数
CThostFtdcCombinationLegField["LegMultiple"] = "int"
#派生层数
CThostFtdcCombinationLegField["ImplyLevel"] = "int"
structDict['CThostFtdcCombinationLegField'] = CThostFtdcCombinationLegField


#数据同步状态
CThostFtdcSyncStatusField = {}
#交易日
CThostFtdcSyncStatusField["TradingDay"] = "string"
#数据同步状态
CThostFtdcSyncStatusField["DataSyncStatus"] = "char"
structDict['CThostFtdcSyncStatusField'] = CThostFtdcSyncStatusField


#查询联系人
CThostFtdcQryLinkManField = {}
#经纪公司代码
CThostFtdcQryLinkManField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryLinkManField["InvestorID"] = "string"
structDict['CThostFtdcQryLinkManField'] = CThostFtdcQryLinkManField


#联系人
CThostFtdcLinkManField = {}
#经纪公司代码
CThostFtdcLinkManField["BrokerID"] = "string"
#投资者代码
CThostFtdcLinkManField["InvestorID"] = "string"
#联系人类型
CThostFtdcLinkManField["PersonType"] = "char"
#证件类型
CThostFtdcLinkManField["IdentifiedCardType"] = "char"
#证件号码
CThostFtdcLinkManField["IdentifiedCardNo"] = "string"
#名称
CThostFtdcLinkManField["PersonName"] = "string"
#联系电话
CThostFtdcLinkManField["Telephone"] = "string"
#通讯地址
CThostFtdcLinkManField["Address"] = "string"
#邮政编码
CThostFtdcLinkManField["ZipCode"] = "string"
#优先级
CThostFtdcLinkManField["Priority"] = "int"
#开户邮政编码
CThostFtdcLinkManField["UOAZipCode"] = "string"
#全称
CThostFtdcLinkManField["PersonFullName"] = "string"
structDict['CThostFtdcLinkManField'] = CThostFtdcLinkManField


#查询经纪公司用户事件
CThostFtdcQryBrokerUserEventField = {}
#经纪公司代码
CThostFtdcQryBrokerUserEventField["BrokerID"] = "string"
#用户代码
CThostFtdcQryBrokerUserEventField["UserID"] = "string"
#用户事件类型
CThostFtdcQryBrokerUserEventField["UserEventType"] = "char"
structDict['CThostFtdcQryBrokerUserEventField'] = CThostFtdcQryBrokerUserEventField


#查询经纪公司用户事件
CThostFtdcBrokerUserEventField = {}
#经纪公司代码
CThostFtdcBrokerUserEventField["BrokerID"] = "string"
#用户代码
CThostFtdcBrokerUserEventField["UserID"] = "string"
#用户事件类型
CThostFtdcBrokerUserEventField["UserEventType"] = "char"
#用户事件序号
CThostFtdcBrokerUserEventField["EventSequenceNo"] = "int"
#事件发生日期
CThostFtdcBrokerUserEventField["EventDate"] = "string"
#事件发生时间
CThostFtdcBrokerUserEventField["EventTime"] = "string"
#用户事件信息
CThostFtdcBrokerUserEventField["UserEventInfo"] = "string"
#投资者代码
CThostFtdcBrokerUserEventField["InvestorID"] = "string"
#合约代码
CThostFtdcBrokerUserEventField["InstrumentID"] = "string"
structDict['CThostFtdcBrokerUserEventField'] = CThostFtdcBrokerUserEventField


#查询签约银行请求
CThostFtdcQryContractBankField = {}
#经纪公司代码
CThostFtdcQryContractBankField["BrokerID"] = "string"
#银行代码
CThostFtdcQryContractBankField["BankID"] = "string"
#银行分中心代码
CThostFtdcQryContractBankField["BankBrchID"] = "string"
structDict['CThostFtdcQryContractBankField'] = CThostFtdcQryContractBankField


#查询签约银行响应
CThostFtdcContractBankField = {}
#经纪公司代码
CThostFtdcContractBankField["BrokerID"] = "string"
#银行代码
CThostFtdcContractBankField["BankID"] = "string"
#银行分中心代码
CThostFtdcContractBankField["BankBrchID"] = "string"
#银行名称
CThostFtdcContractBankField["BankName"] = "string"
structDict['CThostFtdcContractBankField'] = CThostFtdcContractBankField


#投资者组合持仓明细
CThostFtdcInvestorPositionCombineDetailField = {}
#交易日
CThostFtdcInvestorPositionCombineDetailField["TradingDay"] = "string"
#开仓日期
CThostFtdcInvestorPositionCombineDetailField["OpenDate"] = "string"
#交易所代码
CThostFtdcInvestorPositionCombineDetailField["ExchangeID"] = "string"
#结算编号
CThostFtdcInvestorPositionCombineDetailField["SettlementID"] = "int"
#经纪公司代码
CThostFtdcInvestorPositionCombineDetailField["BrokerID"] = "string"
#投资者代码
CThostFtdcInvestorPositionCombineDetailField["InvestorID"] = "string"
#组合编号
CThostFtdcInvestorPositionCombineDetailField["ComTradeID"] = "string"
#撮合编号
CThostFtdcInvestorPositionCombineDetailField["TradeID"] = "string"
#合约代码
CThostFtdcInvestorPositionCombineDetailField["InstrumentID"] = "string"
#投机套保标志
CThostFtdcInvestorPositionCombineDetailField["HedgeFlag"] = "char"
#买卖
CThostFtdcInvestorPositionCombineDetailField["Direction"] = "char"
#持仓量
CThostFtdcInvestorPositionCombineDetailField["TotalAmt"] = "int"
#投资者保证金
CThostFtdcInvestorPositionCombineDetailField["Margin"] = "float"
#交易所保证金
CThostFtdcInvestorPositionCombineDetailField["ExchMargin"] = "float"
#保证金率
CThostFtdcInvestorPositionCombineDetailField["MarginRateByMoney"] = "float"
#保证金率(按手数)
CThostFtdcInvestorPositionCombineDetailField["MarginRateByVolume"] = "float"
#单腿编号
CThostFtdcInvestorPositionCombineDetailField["LegID"] = "int"
#单腿乘数
CThostFtdcInvestorPositionCombineDetailField["LegMultiple"] = "int"
#组合持仓合约编码
CThostFtdcInvestorPositionCombineDetailField["CombInstrumentID"] = "string"
#成交组号
CThostFtdcInvestorPositionCombineDetailField["TradeGroupID"] = "int"
#投资单元代码
CThostFtdcInvestorPositionCombineDetailField["InvestUnitID"] = "string"
structDict['CThostFtdcInvestorPositionCombineDetailField'] = CThostFtdcInvestorPositionCombineDetailField


#预埋单
CThostFtdcParkedOrderField = {}
#经纪公司代码
CThostFtdcParkedOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcParkedOrderField["InvestorID"] = "string"
#合约代码
CThostFtdcParkedOrderField["InstrumentID"] = "string"
#报单引用
CThostFtdcParkedOrderField["OrderRef"] = "string"
#用户代码
CThostFtdcParkedOrderField["UserID"] = "string"
#报单价格条件
CThostFtdcParkedOrderField["OrderPriceType"] = "char"
#买卖方向
CThostFtdcParkedOrderField["Direction"] = "char"
#组合开平标志
CThostFtdcParkedOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CThostFtdcParkedOrderField["CombHedgeFlag"] = "string"
#价格
CThostFtdcParkedOrderField["LimitPrice"] = "float"
#数量
CThostFtdcParkedOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CThostFtdcParkedOrderField["TimeCondition"] = "char"
#GTD日期
CThostFtdcParkedOrderField["GTDDate"] = "string"
#成交量类型
CThostFtdcParkedOrderField["VolumeCondition"] = "char"
#最小成交量
CThostFtdcParkedOrderField["MinVolume"] = "int"
#触发条件
CThostFtdcParkedOrderField["ContingentCondition"] = "char"
#止损价
CThostFtdcParkedOrderField["StopPrice"] = "float"
#强平原因
CThostFtdcParkedOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CThostFtdcParkedOrderField["IsAutoSuspend"] = "int"
#业务单元
CThostFtdcParkedOrderField["BusinessUnit"] = "string"
#请求编号
CThostFtdcParkedOrderField["RequestID"] = "int"
#用户强评标志
CThostFtdcParkedOrderField["UserForceClose"] = "int"
#交易所代码
CThostFtdcParkedOrderField["ExchangeID"] = "string"
#预埋报单编号
CThostFtdcParkedOrderField["ParkedOrderID"] = "string"
#用户类型
CThostFtdcParkedOrderField["UserType"] = "char"
#预埋单状态
CThostFtdcParkedOrderField["Status"] = "char"
#错误代码
CThostFtdcParkedOrderField["ErrorID"] = "int"
#错误信息
CThostFtdcParkedOrderField["ErrorMsg"] = "string"
#互换单标志
CThostFtdcParkedOrderField["IsSwapOrder"] = "int"
#资金账号
CThostFtdcParkedOrderField["AccountID"] = "string"
#币种代码
CThostFtdcParkedOrderField["CurrencyID"] = "string"
#交易编码
CThostFtdcParkedOrderField["ClientID"] = "string"
#投资单元代码
CThostFtdcParkedOrderField["InvestUnitID"] = "string"
#IP地址
CThostFtdcParkedOrderField["IPAddress"] = "string"
#Mac地址
CThostFtdcParkedOrderField["MacAddress"] = "string"
structDict['CThostFtdcParkedOrderField'] = CThostFtdcParkedOrderField


#输入预埋单操作
CThostFtdcParkedOrderActionField = {}
#经纪公司代码
CThostFtdcParkedOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcParkedOrderActionField["InvestorID"] = "string"
#报单操作引用
CThostFtdcParkedOrderActionField["OrderActionRef"] = "int"
#报单引用
CThostFtdcParkedOrderActionField["OrderRef"] = "string"
#请求编号
CThostFtdcParkedOrderActionField["RequestID"] = "int"
#前置编号
CThostFtdcParkedOrderActionField["FrontID"] = "int"
#会话编号
CThostFtdcParkedOrderActionField["SessionID"] = "int"
#交易所代码
CThostFtdcParkedOrderActionField["ExchangeID"] = "string"
#报单编号
CThostFtdcParkedOrderActionField["OrderSysID"] = "string"
#操作标志
CThostFtdcParkedOrderActionField["ActionFlag"] = "char"
#价格
CThostFtdcParkedOrderActionField["LimitPrice"] = "float"
#数量变化
CThostFtdcParkedOrderActionField["VolumeChange"] = "int"
#用户代码
CThostFtdcParkedOrderActionField["UserID"] = "string"
#合约代码
CThostFtdcParkedOrderActionField["InstrumentID"] = "string"
#预埋撤单单编号
CThostFtdcParkedOrderActionField["ParkedOrderActionID"] = "string"
#用户类型
CThostFtdcParkedOrderActionField["UserType"] = "char"
#预埋撤单状态
CThostFtdcParkedOrderActionField["Status"] = "char"
#错误代码
CThostFtdcParkedOrderActionField["ErrorID"] = "int"
#错误信息
CThostFtdcParkedOrderActionField["ErrorMsg"] = "string"
#投资单元代码
CThostFtdcParkedOrderActionField["InvestUnitID"] = "string"
#IP地址
CThostFtdcParkedOrderActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcParkedOrderActionField["MacAddress"] = "string"
structDict['CThostFtdcParkedOrderActionField'] = CThostFtdcParkedOrderActionField


#查询预埋单
CThostFtdcQryParkedOrderField = {}
#经纪公司代码
CThostFtdcQryParkedOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryParkedOrderField["InvestorID"] = "string"
#合约代码
CThostFtdcQryParkedOrderField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryParkedOrderField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcQryParkedOrderField["InvestUnitID"] = "string"
structDict['CThostFtdcQryParkedOrderField'] = CThostFtdcQryParkedOrderField


#查询预埋撤单
CThostFtdcQryParkedOrderActionField = {}
#经纪公司代码
CThostFtdcQryParkedOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryParkedOrderActionField["InvestorID"] = "string"
#合约代码
CThostFtdcQryParkedOrderActionField["InstrumentID"] = "string"
#交易所代码
CThostFtdcQryParkedOrderActionField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcQryParkedOrderActionField["InvestUnitID"] = "string"
structDict['CThostFtdcQryParkedOrderActionField'] = CThostFtdcQryParkedOrderActionField


#删除预埋单
CThostFtdcRemoveParkedOrderField = {}
#经纪公司代码
CThostFtdcRemoveParkedOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcRemoveParkedOrderField["InvestorID"] = "string"
#预埋报单编号
CThostFtdcRemoveParkedOrderField["ParkedOrderID"] = "string"
#投资单元代码
CThostFtdcRemoveParkedOrderField["InvestUnitID"] = "string"
structDict['CThostFtdcRemoveParkedOrderField'] = CThostFtdcRemoveParkedOrderField


#删除预埋撤单
CThostFtdcRemoveParkedOrderActionField = {}
#经纪公司代码
CThostFtdcRemoveParkedOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcRemoveParkedOrderActionField["InvestorID"] = "string"
#预埋撤单编号
CThostFtdcRemoveParkedOrderActionField["ParkedOrderActionID"] = "string"
#投资单元代码
CThostFtdcRemoveParkedOrderActionField["InvestUnitID"] = "string"
structDict['CThostFtdcRemoveParkedOrderActionField'] = CThostFtdcRemoveParkedOrderActionField


#经纪公司可提资金算法表
CThostFtdcInvestorWithdrawAlgorithmField = {}
#经纪公司代码
CThostFtdcInvestorWithdrawAlgorithmField["BrokerID"] = "string"
#投资者范围
CThostFtdcInvestorWithdrawAlgorithmField["InvestorRange"] = "char"
#投资者代码
CThostFtdcInvestorWithdrawAlgorithmField["InvestorID"] = "string"
#可提资金比例
CThostFtdcInvestorWithdrawAlgorithmField["UsingRatio"] = "float"
#币种代码
CThostFtdcInvestorWithdrawAlgorithmField["CurrencyID"] = "string"
#货币质押比率
CThostFtdcInvestorWithdrawAlgorithmField["FundMortgageRatio"] = "float"
structDict['CThostFtdcInvestorWithdrawAlgorithmField'] = CThostFtdcInvestorWithdrawAlgorithmField


#查询组合持仓明细
CThostFtdcQryInvestorPositionCombineDetailField = {}
#经纪公司代码
CThostFtdcQryInvestorPositionCombineDetailField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryInvestorPositionCombineDetailField["InvestorID"] = "string"
#组合持仓合约编码
CThostFtdcQryInvestorPositionCombineDetailField["CombInstrumentID"] = "string"
#交易所代码
CThostFtdcQryInvestorPositionCombineDetailField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcQryInvestorPositionCombineDetailField["InvestUnitID"] = "string"
structDict['CThostFtdcQryInvestorPositionCombineDetailField'] = CThostFtdcQryInvestorPositionCombineDetailField


#成交均价
CThostFtdcMarketDataAveragePriceField = {}
#当日均价
CThostFtdcMarketDataAveragePriceField["AveragePrice"] = "float"
structDict['CThostFtdcMarketDataAveragePriceField'] = CThostFtdcMarketDataAveragePriceField


#校验投资者密码
CThostFtdcVerifyInvestorPasswordField = {}
#经纪公司代码
CThostFtdcVerifyInvestorPasswordField["BrokerID"] = "string"
#投资者代码
CThostFtdcVerifyInvestorPasswordField["InvestorID"] = "string"
#密码
CThostFtdcVerifyInvestorPasswordField["Password"] = "string"
structDict['CThostFtdcVerifyInvestorPasswordField'] = CThostFtdcVerifyInvestorPasswordField


#用户IP
CThostFtdcUserIPField = {}
#经纪公司代码
CThostFtdcUserIPField["BrokerID"] = "string"
#用户代码
CThostFtdcUserIPField["UserID"] = "string"
#IP地址
CThostFtdcUserIPField["IPAddress"] = "string"
#IP地址掩码
CThostFtdcUserIPField["IPMask"] = "string"
#Mac地址
CThostFtdcUserIPField["MacAddress"] = "string"
structDict['CThostFtdcUserIPField'] = CThostFtdcUserIPField


#用户事件通知信息
CThostFtdcTradingNoticeInfoField = {}
#经纪公司代码
CThostFtdcTradingNoticeInfoField["BrokerID"] = "string"
#投资者代码
CThostFtdcTradingNoticeInfoField["InvestorID"] = "string"
#发送时间
CThostFtdcTradingNoticeInfoField["SendTime"] = "string"
#消息正文
CThostFtdcTradingNoticeInfoField["FieldContent"] = "string"
#序列系列号
CThostFtdcTradingNoticeInfoField["SequenceSeries"] = "int"
#序列号
CThostFtdcTradingNoticeInfoField["SequenceNo"] = "int"
#投资单元代码
CThostFtdcTradingNoticeInfoField["InvestUnitID"] = "string"
structDict['CThostFtdcTradingNoticeInfoField'] = CThostFtdcTradingNoticeInfoField


#用户事件通知
CThostFtdcTradingNoticeField = {}
#经纪公司代码
CThostFtdcTradingNoticeField["BrokerID"] = "string"
#投资者范围
CThostFtdcTradingNoticeField["InvestorRange"] = "char"
#投资者代码
CThostFtdcTradingNoticeField["InvestorID"] = "string"
#序列系列号
CThostFtdcTradingNoticeField["SequenceSeries"] = "int"
#用户代码
CThostFtdcTradingNoticeField["UserID"] = "string"
#发送时间
CThostFtdcTradingNoticeField["SendTime"] = "string"
#序列号
CThostFtdcTradingNoticeField["SequenceNo"] = "int"
#消息正文
CThostFtdcTradingNoticeField["FieldContent"] = "string"
#投资单元代码
CThostFtdcTradingNoticeField["InvestUnitID"] = "string"
structDict['CThostFtdcTradingNoticeField'] = CThostFtdcTradingNoticeField


#查询交易事件通知
CThostFtdcQryTradingNoticeField = {}
#经纪公司代码
CThostFtdcQryTradingNoticeField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryTradingNoticeField["InvestorID"] = "string"
#投资单元代码
CThostFtdcQryTradingNoticeField["InvestUnitID"] = "string"
structDict['CThostFtdcQryTradingNoticeField'] = CThostFtdcQryTradingNoticeField


#查询错误报单
CThostFtdcQryErrOrderField = {}
#经纪公司代码
CThostFtdcQryErrOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryErrOrderField["InvestorID"] = "string"
structDict['CThostFtdcQryErrOrderField'] = CThostFtdcQryErrOrderField


#错误报单
CThostFtdcErrOrderField = {}
#经纪公司代码
CThostFtdcErrOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcErrOrderField["InvestorID"] = "string"
#合约代码
CThostFtdcErrOrderField["InstrumentID"] = "string"
#报单引用
CThostFtdcErrOrderField["OrderRef"] = "string"
#用户代码
CThostFtdcErrOrderField["UserID"] = "string"
#报单价格条件
CThostFtdcErrOrderField["OrderPriceType"] = "char"
#买卖方向
CThostFtdcErrOrderField["Direction"] = "char"
#组合开平标志
CThostFtdcErrOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CThostFtdcErrOrderField["CombHedgeFlag"] = "string"
#价格
CThostFtdcErrOrderField["LimitPrice"] = "float"
#数量
CThostFtdcErrOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CThostFtdcErrOrderField["TimeCondition"] = "char"
#GTD日期
CThostFtdcErrOrderField["GTDDate"] = "string"
#成交量类型
CThostFtdcErrOrderField["VolumeCondition"] = "char"
#最小成交量
CThostFtdcErrOrderField["MinVolume"] = "int"
#触发条件
CThostFtdcErrOrderField["ContingentCondition"] = "char"
#止损价
CThostFtdcErrOrderField["StopPrice"] = "float"
#强平原因
CThostFtdcErrOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CThostFtdcErrOrderField["IsAutoSuspend"] = "int"
#业务单元
CThostFtdcErrOrderField["BusinessUnit"] = "string"
#请求编号
CThostFtdcErrOrderField["RequestID"] = "int"
#用户强评标志
CThostFtdcErrOrderField["UserForceClose"] = "int"
#错误代码
CThostFtdcErrOrderField["ErrorID"] = "int"
#错误信息
CThostFtdcErrOrderField["ErrorMsg"] = "string"
#互换单标志
CThostFtdcErrOrderField["IsSwapOrder"] = "int"
#交易所代码
CThostFtdcErrOrderField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcErrOrderField["InvestUnitID"] = "string"
#资金账号
CThostFtdcErrOrderField["AccountID"] = "string"
#币种代码
CThostFtdcErrOrderField["CurrencyID"] = "string"
#交易编码
CThostFtdcErrOrderField["ClientID"] = "string"
#IP地址
CThostFtdcErrOrderField["IPAddress"] = "string"
#Mac地址
CThostFtdcErrOrderField["MacAddress"] = "string"
structDict['CThostFtdcErrOrderField'] = CThostFtdcErrOrderField


#查询错误报单操作
CThostFtdcErrorConditionalOrderField = {}
#经纪公司代码
CThostFtdcErrorConditionalOrderField["BrokerID"] = "string"
#投资者代码
CThostFtdcErrorConditionalOrderField["InvestorID"] = "string"
#合约代码
CThostFtdcErrorConditionalOrderField["InstrumentID"] = "string"
#报单引用
CThostFtdcErrorConditionalOrderField["OrderRef"] = "string"
#用户代码
CThostFtdcErrorConditionalOrderField["UserID"] = "string"
#报单价格条件
CThostFtdcErrorConditionalOrderField["OrderPriceType"] = "char"
#买卖方向
CThostFtdcErrorConditionalOrderField["Direction"] = "char"
#组合开平标志
CThostFtdcErrorConditionalOrderField["CombOffsetFlag"] = "string"
#组合投机套保标志
CThostFtdcErrorConditionalOrderField["CombHedgeFlag"] = "string"
#价格
CThostFtdcErrorConditionalOrderField["LimitPrice"] = "float"
#数量
CThostFtdcErrorConditionalOrderField["VolumeTotalOriginal"] = "int"
#有效期类型
CThostFtdcErrorConditionalOrderField["TimeCondition"] = "char"
#GTD日期
CThostFtdcErrorConditionalOrderField["GTDDate"] = "string"
#成交量类型
CThostFtdcErrorConditionalOrderField["VolumeCondition"] = "char"
#最小成交量
CThostFtdcErrorConditionalOrderField["MinVolume"] = "int"
#触发条件
CThostFtdcErrorConditionalOrderField["ContingentCondition"] = "char"
#止损价
CThostFtdcErrorConditionalOrderField["StopPrice"] = "float"
#强平原因
CThostFtdcErrorConditionalOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CThostFtdcErrorConditionalOrderField["IsAutoSuspend"] = "int"
#业务单元
CThostFtdcErrorConditionalOrderField["BusinessUnit"] = "string"
#请求编号
CThostFtdcErrorConditionalOrderField["RequestID"] = "int"
#本地报单编号
CThostFtdcErrorConditionalOrderField["OrderLocalID"] = "string"
#交易所代码
CThostFtdcErrorConditionalOrderField["ExchangeID"] = "string"
#会员代码
CThostFtdcErrorConditionalOrderField["ParticipantID"] = "string"
#客户代码
CThostFtdcErrorConditionalOrderField["ClientID"] = "string"
#合约在交易所的代码
CThostFtdcErrorConditionalOrderField["ExchangeInstID"] = "string"
#交易所交易员代码
CThostFtdcErrorConditionalOrderField["TraderID"] = "string"
#安装编号
CThostFtdcErrorConditionalOrderField["InstallID"] = "int"
#报单提交状态
CThostFtdcErrorConditionalOrderField["OrderSubmitStatus"] = "char"
#报单提示序号
CThostFtdcErrorConditionalOrderField["NotifySequence"] = "int"
#交易日
CThostFtdcErrorConditionalOrderField["TradingDay"] = "string"
#结算编号
CThostFtdcErrorConditionalOrderField["SettlementID"] = "int"
#报单编号
CThostFtdcErrorConditionalOrderField["OrderSysID"] = "string"
#报单来源
CThostFtdcErrorConditionalOrderField["OrderSource"] = "char"
#报单状态
CThostFtdcErrorConditionalOrderField["OrderStatus"] = "char"
#报单类型
CThostFtdcErrorConditionalOrderField["OrderType"] = "char"
#今成交数量
CThostFtdcErrorConditionalOrderField["VolumeTraded"] = "int"
#剩余数量
CThostFtdcErrorConditionalOrderField["VolumeTotal"] = "int"
#报单日期
CThostFtdcErrorConditionalOrderField["InsertDate"] = "string"
#委托时间
CThostFtdcErrorConditionalOrderField["InsertTime"] = "string"
#激活时间
CThostFtdcErrorConditionalOrderField["ActiveTime"] = "string"
#挂起时间
CThostFtdcErrorConditionalOrderField["SuspendTime"] = "string"
#最后修改时间
CThostFtdcErrorConditionalOrderField["UpdateTime"] = "string"
#撤销时间
CThostFtdcErrorConditionalOrderField["CancelTime"] = "string"
#最后修改交易所交易员代码
CThostFtdcErrorConditionalOrderField["ActiveTraderID"] = "string"
#结算会员编号
CThostFtdcErrorConditionalOrderField["ClearingPartID"] = "string"
#序号
CThostFtdcErrorConditionalOrderField["SequenceNo"] = "int"
#前置编号
CThostFtdcErrorConditionalOrderField["FrontID"] = "int"
#会话编号
CThostFtdcErrorConditionalOrderField["SessionID"] = "int"
#用户端产品信息
CThostFtdcErrorConditionalOrderField["UserProductInfo"] = "string"
#状态信息
CThostFtdcErrorConditionalOrderField["StatusMsg"] = "string"
#用户强评标志
CThostFtdcErrorConditionalOrderField["UserForceClose"] = "int"
#操作用户代码
CThostFtdcErrorConditionalOrderField["ActiveUserID"] = "string"
#经纪公司报单编号
CThostFtdcErrorConditionalOrderField["BrokerOrderSeq"] = "int"
#相关报单
CThostFtdcErrorConditionalOrderField["RelativeOrderSysID"] = "string"
#郑商所成交数量
CThostFtdcErrorConditionalOrderField["ZCETotalTradedVolume"] = "int"
#错误代码
CThostFtdcErrorConditionalOrderField["ErrorID"] = "int"
#错误信息
CThostFtdcErrorConditionalOrderField["ErrorMsg"] = "string"
#互换单标志
CThostFtdcErrorConditionalOrderField["IsSwapOrder"] = "int"
#营业部编号
CThostFtdcErrorConditionalOrderField["BranchID"] = "string"
#投资单元代码
CThostFtdcErrorConditionalOrderField["InvestUnitID"] = "string"
#资金账号
CThostFtdcErrorConditionalOrderField["AccountID"] = "string"
#币种代码
CThostFtdcErrorConditionalOrderField["CurrencyID"] = "string"
#IP地址
CThostFtdcErrorConditionalOrderField["IPAddress"] = "string"
#Mac地址
CThostFtdcErrorConditionalOrderField["MacAddress"] = "string"
structDict['CThostFtdcErrorConditionalOrderField'] = CThostFtdcErrorConditionalOrderField


#查询错误报单操作
CThostFtdcQryErrOrderActionField = {}
#经纪公司代码
CThostFtdcQryErrOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryErrOrderActionField["InvestorID"] = "string"
structDict['CThostFtdcQryErrOrderActionField'] = CThostFtdcQryErrOrderActionField


#错误报单操作
CThostFtdcErrOrderActionField = {}
#经纪公司代码
CThostFtdcErrOrderActionField["BrokerID"] = "string"
#投资者代码
CThostFtdcErrOrderActionField["InvestorID"] = "string"
#报单操作引用
CThostFtdcErrOrderActionField["OrderActionRef"] = "int"
#报单引用
CThostFtdcErrOrderActionField["OrderRef"] = "string"
#请求编号
CThostFtdcErrOrderActionField["RequestID"] = "int"
#前置编号
CThostFtdcErrOrderActionField["FrontID"] = "int"
#会话编号
CThostFtdcErrOrderActionField["SessionID"] = "int"
#交易所代码
CThostFtdcErrOrderActionField["ExchangeID"] = "string"
#报单编号
CThostFtdcErrOrderActionField["OrderSysID"] = "string"
#操作标志
CThostFtdcErrOrderActionField["ActionFlag"] = "char"
#价格
CThostFtdcErrOrderActionField["LimitPrice"] = "float"
#数量变化
CThostFtdcErrOrderActionField["VolumeChange"] = "int"
#操作日期
CThostFtdcErrOrderActionField["ActionDate"] = "string"
#操作时间
CThostFtdcErrOrderActionField["ActionTime"] = "string"
#交易所交易员代码
CThostFtdcErrOrderActionField["TraderID"] = "string"
#安装编号
CThostFtdcErrOrderActionField["InstallID"] = "int"
#本地报单编号
CThostFtdcErrOrderActionField["OrderLocalID"] = "string"
#操作本地编号
CThostFtdcErrOrderActionField["ActionLocalID"] = "string"
#会员代码
CThostFtdcErrOrderActionField["ParticipantID"] = "string"
#客户代码
CThostFtdcErrOrderActionField["ClientID"] = "string"
#业务单元
CThostFtdcErrOrderActionField["BusinessUnit"] = "string"
#报单操作状态
CThostFtdcErrOrderActionField["OrderActionStatus"] = "char"
#用户代码
CThostFtdcErrOrderActionField["UserID"] = "string"
#状态信息
CThostFtdcErrOrderActionField["StatusMsg"] = "string"
#合约代码
CThostFtdcErrOrderActionField["InstrumentID"] = "string"
#营业部编号
CThostFtdcErrOrderActionField["BranchID"] = "string"
#投资单元代码
CThostFtdcErrOrderActionField["InvestUnitID"] = "string"
#IP地址
CThostFtdcErrOrderActionField["IPAddress"] = "string"
#Mac地址
CThostFtdcErrOrderActionField["MacAddress"] = "string"
#错误代码
CThostFtdcErrOrderActionField["ErrorID"] = "int"
#错误信息
CThostFtdcErrOrderActionField["ErrorMsg"] = "string"
structDict['CThostFtdcErrOrderActionField'] = CThostFtdcErrOrderActionField


#查询交易所状态
CThostFtdcQryExchangeSequenceField = {}
#交易所代码
CThostFtdcQryExchangeSequenceField["ExchangeID"] = "string"
structDict['CThostFtdcQryExchangeSequenceField'] = CThostFtdcQryExchangeSequenceField


#交易所状态
CThostFtdcExchangeSequenceField = {}
#交易所代码
CThostFtdcExchangeSequenceField["ExchangeID"] = "string"
#序号
CThostFtdcExchangeSequenceField["SequenceNo"] = "int"
#合约交易状态
CThostFtdcExchangeSequenceField["MarketStatus"] = "char"
structDict['CThostFtdcExchangeSequenceField'] = CThostFtdcExchangeSequenceField


#根据价格查询最大报单数量
CThostFtdcQueryMaxOrderVolumeWithPriceField = {}
#经纪公司代码
CThostFtdcQueryMaxOrderVolumeWithPriceField["BrokerID"] = "string"
#投资者代码
CThostFtdcQueryMaxOrderVolumeWithPriceField["InvestorID"] = "string"
#合约代码
CThostFtdcQueryMaxOrderVolumeWithPriceField["InstrumentID"] = "string"
#买卖方向
CThostFtdcQueryMaxOrderVolumeWithPriceField["Direction"] = "char"
#开平标志
CThostFtdcQueryMaxOrderVolumeWithPriceField["OffsetFlag"] = "char"
#投机套保标志
CThostFtdcQueryMaxOrderVolumeWithPriceField["HedgeFlag"] = "char"
#最大允许报单数量
CThostFtdcQueryMaxOrderVolumeWithPriceField["MaxVolume"] = "int"
#报单价格
CThostFtdcQueryMaxOrderVolumeWithPriceField["Price"] = "float"
#交易所代码
CThostFtdcQueryMaxOrderVolumeWithPriceField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcQueryMaxOrderVolumeWithPriceField["InvestUnitID"] = "string"
structDict['CThostFtdcQueryMaxOrderVolumeWithPriceField'] = CThostFtdcQueryMaxOrderVolumeWithPriceField


#查询经纪公司交易参数
CThostFtdcQryBrokerTradingParamsField = {}
#经纪公司代码
CThostFtdcQryBrokerTradingParamsField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryBrokerTradingParamsField["InvestorID"] = "string"
#币种代码
CThostFtdcQryBrokerTradingParamsField["CurrencyID"] = "string"
#投资者帐号
CThostFtdcQryBrokerTradingParamsField["AccountID"] = "string"
structDict['CThostFtdcQryBrokerTradingParamsField'] = CThostFtdcQryBrokerTradingParamsField


#经纪公司交易参数
CThostFtdcBrokerTradingParamsField = {}
#经纪公司代码
CThostFtdcBrokerTradingParamsField["BrokerID"] = "string"
#投资者代码
CThostFtdcBrokerTradingParamsField["InvestorID"] = "string"
#保证金价格类型
CThostFtdcBrokerTradingParamsField["MarginPriceType"] = "char"
#盈亏算法
CThostFtdcBrokerTradingParamsField["Algorithm"] = "char"
#可用是否包含平仓盈利
CThostFtdcBrokerTradingParamsField["AvailIncludeCloseProfit"] = "char"
#币种代码
CThostFtdcBrokerTradingParamsField["CurrencyID"] = "string"
#期权权利金价格类型
CThostFtdcBrokerTradingParamsField["OptionRoyaltyPriceType"] = "char"
#投资者帐号
CThostFtdcBrokerTradingParamsField["AccountID"] = "string"
structDict['CThostFtdcBrokerTradingParamsField'] = CThostFtdcBrokerTradingParamsField


#查询经纪公司交易算法
CThostFtdcQryBrokerTradingAlgosField = {}
#经纪公司代码
CThostFtdcQryBrokerTradingAlgosField["BrokerID"] = "string"
#交易所代码
CThostFtdcQryBrokerTradingAlgosField["ExchangeID"] = "string"
#合约代码
CThostFtdcQryBrokerTradingAlgosField["InstrumentID"] = "string"
structDict['CThostFtdcQryBrokerTradingAlgosField'] = CThostFtdcQryBrokerTradingAlgosField


#经纪公司交易算法
CThostFtdcBrokerTradingAlgosField = {}
#经纪公司代码
CThostFtdcBrokerTradingAlgosField["BrokerID"] = "string"
#交易所代码
CThostFtdcBrokerTradingAlgosField["ExchangeID"] = "string"
#合约代码
CThostFtdcBrokerTradingAlgosField["InstrumentID"] = "string"
#持仓处理算法编号
CThostFtdcBrokerTradingAlgosField["HandlePositionAlgoID"] = "char"
#寻找保证金率算法编号
CThostFtdcBrokerTradingAlgosField["FindMarginRateAlgoID"] = "char"
#资金处理算法编号
CThostFtdcBrokerTradingAlgosField["HandleTradingAccountAlgoID"] = "char"
structDict['CThostFtdcBrokerTradingAlgosField'] = CThostFtdcBrokerTradingAlgosField


#查询经纪公司资金
CThostFtdcQueryBrokerDepositField = {}
#经纪公司代码
CThostFtdcQueryBrokerDepositField["BrokerID"] = "string"
#交易所代码
CThostFtdcQueryBrokerDepositField["ExchangeID"] = "string"
structDict['CThostFtdcQueryBrokerDepositField'] = CThostFtdcQueryBrokerDepositField


#经纪公司资金
CThostFtdcBrokerDepositField = {}
#交易日期
CThostFtdcBrokerDepositField["TradingDay"] = "string"
#经纪公司代码
CThostFtdcBrokerDepositField["BrokerID"] = "string"
#会员代码
CThostFtdcBrokerDepositField["ParticipantID"] = "string"
#交易所代码
CThostFtdcBrokerDepositField["ExchangeID"] = "string"
#上次结算准备金
CThostFtdcBrokerDepositField["PreBalance"] = "float"
#当前保证金总额
CThostFtdcBrokerDepositField["CurrMargin"] = "float"
#平仓盈亏
CThostFtdcBrokerDepositField["CloseProfit"] = "float"
#期货结算准备金
CThostFtdcBrokerDepositField["Balance"] = "float"
#入金金额
CThostFtdcBrokerDepositField["Deposit"] = "float"
#出金金额
CThostFtdcBrokerDepositField["Withdraw"] = "float"
#可提资金
CThostFtdcBrokerDepositField["Available"] = "float"
#基本准备金
CThostFtdcBrokerDepositField["Reserve"] = "float"
#冻结的保证金
CThostFtdcBrokerDepositField["FrozenMargin"] = "float"
structDict['CThostFtdcBrokerDepositField'] = CThostFtdcBrokerDepositField


#查询保证金监管系统经纪公司密钥
CThostFtdcQryCFMMCBrokerKeyField = {}
#经纪公司代码
CThostFtdcQryCFMMCBrokerKeyField["BrokerID"] = "string"
structDict['CThostFtdcQryCFMMCBrokerKeyField'] = CThostFtdcQryCFMMCBrokerKeyField


#保证金监管系统经纪公司密钥
CThostFtdcCFMMCBrokerKeyField = {}
#经纪公司代码
CThostFtdcCFMMCBrokerKeyField["BrokerID"] = "string"
#经纪公司统一编码
CThostFtdcCFMMCBrokerKeyField["ParticipantID"] = "string"
#密钥生成日期
CThostFtdcCFMMCBrokerKeyField["CreateDate"] = "string"
#密钥生成时间
CThostFtdcCFMMCBrokerKeyField["CreateTime"] = "string"
#密钥编号
CThostFtdcCFMMCBrokerKeyField["KeyID"] = "int"
#动态密钥
CThostFtdcCFMMCBrokerKeyField["CurrentKey"] = "string"
#动态密钥类型
CThostFtdcCFMMCBrokerKeyField["KeyKind"] = "char"
structDict['CThostFtdcCFMMCBrokerKeyField'] = CThostFtdcCFMMCBrokerKeyField


#保证金监管系统经纪公司资金账户密钥
CThostFtdcCFMMCTradingAccountKeyField = {}
#经纪公司代码
CThostFtdcCFMMCTradingAccountKeyField["BrokerID"] = "string"
#经纪公司统一编码
CThostFtdcCFMMCTradingAccountKeyField["ParticipantID"] = "string"
#投资者帐号
CThostFtdcCFMMCTradingAccountKeyField["AccountID"] = "string"
#密钥编号
CThostFtdcCFMMCTradingAccountKeyField["KeyID"] = "int"
#动态密钥
CThostFtdcCFMMCTradingAccountKeyField["CurrentKey"] = "string"
structDict['CThostFtdcCFMMCTradingAccountKeyField'] = CThostFtdcCFMMCTradingAccountKeyField


#请求查询保证金监管系统经纪公司资金账户密钥
CThostFtdcQryCFMMCTradingAccountKeyField = {}
#经纪公司代码
CThostFtdcQryCFMMCTradingAccountKeyField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryCFMMCTradingAccountKeyField["InvestorID"] = "string"
structDict['CThostFtdcQryCFMMCTradingAccountKeyField'] = CThostFtdcQryCFMMCTradingAccountKeyField


#用户动态令牌参数
CThostFtdcBrokerUserOTPParamField = {}
#经纪公司代码
CThostFtdcBrokerUserOTPParamField["BrokerID"] = "string"
#用户代码
CThostFtdcBrokerUserOTPParamField["UserID"] = "string"
#动态令牌提供商
CThostFtdcBrokerUserOTPParamField["OTPVendorsID"] = "string"
#动态令牌序列号
CThostFtdcBrokerUserOTPParamField["SerialNumber"] = "string"
#令牌密钥
CThostFtdcBrokerUserOTPParamField["AuthKey"] = "string"
#漂移值
CThostFtdcBrokerUserOTPParamField["LastDrift"] = "int"
#成功值
CThostFtdcBrokerUserOTPParamField["LastSuccess"] = "int"
#动态令牌类型
CThostFtdcBrokerUserOTPParamField["OTPType"] = "char"
structDict['CThostFtdcBrokerUserOTPParamField'] = CThostFtdcBrokerUserOTPParamField


#手工同步用户动态令牌
CThostFtdcManualSyncBrokerUserOTPField = {}
#经纪公司代码
CThostFtdcManualSyncBrokerUserOTPField["BrokerID"] = "string"
#用户代码
CThostFtdcManualSyncBrokerUserOTPField["UserID"] = "string"
#动态令牌类型
CThostFtdcManualSyncBrokerUserOTPField["OTPType"] = "char"
#第一个动态密码
CThostFtdcManualSyncBrokerUserOTPField["FirstOTP"] = "string"
#第二个动态密码
CThostFtdcManualSyncBrokerUserOTPField["SecondOTP"] = "string"
structDict['CThostFtdcManualSyncBrokerUserOTPField'] = CThostFtdcManualSyncBrokerUserOTPField


#投资者手续费率模板
CThostFtdcCommRateModelField = {}
#经纪公司代码
CThostFtdcCommRateModelField["BrokerID"] = "string"
#手续费率模板代码
CThostFtdcCommRateModelField["CommModelID"] = "string"
#模板名称
CThostFtdcCommRateModelField["CommModelName"] = "string"
structDict['CThostFtdcCommRateModelField'] = CThostFtdcCommRateModelField


#请求查询投资者手续费率模板
CThostFtdcQryCommRateModelField = {}
#经纪公司代码
CThostFtdcQryCommRateModelField["BrokerID"] = "string"
#手续费率模板代码
CThostFtdcQryCommRateModelField["CommModelID"] = "string"
structDict['CThostFtdcQryCommRateModelField'] = CThostFtdcQryCommRateModelField


#投资者保证金率模板
CThostFtdcMarginModelField = {}
#经纪公司代码
CThostFtdcMarginModelField["BrokerID"] = "string"
#保证金率模板代码
CThostFtdcMarginModelField["MarginModelID"] = "string"
#模板名称
CThostFtdcMarginModelField["MarginModelName"] = "string"
structDict['CThostFtdcMarginModelField'] = CThostFtdcMarginModelField


#请求查询投资者保证金率模板
CThostFtdcQryMarginModelField = {}
#经纪公司代码
CThostFtdcQryMarginModelField["BrokerID"] = "string"
#保证金率模板代码
CThostFtdcQryMarginModelField["MarginModelID"] = "string"
structDict['CThostFtdcQryMarginModelField'] = CThostFtdcQryMarginModelField


#仓单折抵信息
CThostFtdcEWarrantOffsetField = {}
#交易日期
CThostFtdcEWarrantOffsetField["TradingDay"] = "string"
#经纪公司代码
CThostFtdcEWarrantOffsetField["BrokerID"] = "string"
#投资者代码
CThostFtdcEWarrantOffsetField["InvestorID"] = "string"
#交易所代码
CThostFtdcEWarrantOffsetField["ExchangeID"] = "string"
#合约代码
CThostFtdcEWarrantOffsetField["InstrumentID"] = "string"
#买卖方向
CThostFtdcEWarrantOffsetField["Direction"] = "char"
#投机套保标志
CThostFtdcEWarrantOffsetField["HedgeFlag"] = "char"
#数量
CThostFtdcEWarrantOffsetField["Volume"] = "int"
#投资单元代码
CThostFtdcEWarrantOffsetField["InvestUnitID"] = "string"
structDict['CThostFtdcEWarrantOffsetField'] = CThostFtdcEWarrantOffsetField


#查询仓单折抵信息
CThostFtdcQryEWarrantOffsetField = {}
#经纪公司代码
CThostFtdcQryEWarrantOffsetField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryEWarrantOffsetField["InvestorID"] = "string"
#交易所代码
CThostFtdcQryEWarrantOffsetField["ExchangeID"] = "string"
#合约代码
CThostFtdcQryEWarrantOffsetField["InstrumentID"] = "string"
#投资单元代码
CThostFtdcQryEWarrantOffsetField["InvestUnitID"] = "string"
structDict['CThostFtdcQryEWarrantOffsetField'] = CThostFtdcQryEWarrantOffsetField


#查询投资者品种/跨品种保证金
CThostFtdcQryInvestorProductGroupMarginField = {}
#经纪公司代码
CThostFtdcQryInvestorProductGroupMarginField["BrokerID"] = "string"
#投资者代码
CThostFtdcQryInvestorProductGroupMarginField["InvestorID"] = "string"
#品种/跨品种标示
CThostFtdcQryInvestorProductGroupMarginField["ProductGroupID"] = "string"
#投机套保标志
CThostFtdcQryInvestorProductGroupMarginField["HedgeFlag"] = "char"
#交易所代码
CThostFtdcQryInvestorProductGroupMarginField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcQryInvestorProductGroupMarginField["InvestUnitID"] = "string"
structDict['CThostFtdcQryInvestorProductGroupMarginField'] = CThostFtdcQryInvestorProductGroupMarginField


#投资者品种/跨品种保证金
CThostFtdcInvestorProductGroupMarginField = {}
#品种/跨品种标示
CThostFtdcInvestorProductGroupMarginField["ProductGroupID"] = "string"
#经纪公司代码
CThostFtdcInvestorProductGroupMarginField["BrokerID"] = "string"
#投资者代码
CThostFtdcInvestorProductGroupMarginField["InvestorID"] = "string"
#交易日
CThostFtdcInvestorProductGroupMarginField["TradingDay"] = "string"
#结算编号
CThostFtdcInvestorProductGroupMarginField["SettlementID"] = "int"
#冻结的保证金
CThostFtdcInvestorProductGroupMarginField["FrozenMargin"] = "float"
#多头冻结的保证金
CThostFtdcInvestorProductGroupMarginField["LongFrozenMargin"] = "float"
#空头冻结的保证金
CThostFtdcInvestorProductGroupMarginField["ShortFrozenMargin"] = "float"
#占用的保证金
CThostFtdcInvestorProductGroupMarginField["UseMargin"] = "float"
#多头保证金
CThostFtdcInvestorProductGroupMarginField["LongUseMargin"] = "float"
#空头保证金
CThostFtdcInvestorProductGroupMarginField["ShortUseMargin"] = "float"
#交易所保证金
CThostFtdcInvestorProductGroupMarginField["ExchMargin"] = "float"
#交易所多头保证金
CThostFtdcInvestorProductGroupMarginField["LongExchMargin"] = "float"
#交易所空头保证金
CThostFtdcInvestorProductGroupMarginField["ShortExchMargin"] = "float"
#平仓盈亏
CThostFtdcInvestorProductGroupMarginField["CloseProfit"] = "float"
#冻结的手续费
CThostFtdcInvestorProductGroupMarginField["FrozenCommission"] = "float"
#手续费
CThostFtdcInvestorProductGroupMarginField["Commission"] = "float"
#冻结的资金
CThostFtdcInvestorProductGroupMarginField["FrozenCash"] = "float"
#资金差额
CThostFtdcInvestorProductGroupMarginField["CashIn"] = "float"
#持仓盈亏
CThostFtdcInvestorProductGroupMarginField["PositionProfit"] = "float"
#折抵总金额
CThostFtdcInvestorProductGroupMarginField["OffsetAmount"] = "float"
#多头折抵总金额
CThostFtdcInvestorProductGroupMarginField["LongOffsetAmount"] = "float"
#空头折抵总金额
CThostFtdcInvestorProductGroupMarginField["ShortOffsetAmount"] = "float"
#交易所折抵总金额
CThostFtdcInvestorProductGroupMarginField["ExchOffsetAmount"] = "float"
#交易所多头折抵总金额
CThostFtdcInvestorProductGroupMarginField["LongExchOffsetAmount"] = "float"
#交易所空头折抵总金额
CThostFtdcInvestorProductGroupMarginField["ShortExchOffsetAmount"] = "float"
#投机套保标志
CThostFtdcInvestorProductGroupMarginField["HedgeFlag"] = "char"
#交易所代码
CThostFtdcInvestorProductGroupMarginField["ExchangeID"] = "string"
#投资单元代码
CThostFtdcInvestorProductGroupMarginField["InvestUnitID"] = "string"
structDict['CThostFtdcInvestorProductGroupMarginField'] = CThostFtdcInvestorProductGroupMarginField


#查询监控中心用户令牌
CThostFtdcQueryCFMMCTradingAccountTokenField = {}
#经纪公司代码
CThostFtdcQueryCFMMCTradingAccountTokenField["BrokerID"] = "string"
#投资者代码
CThostFtdcQueryCFMMCTradingAccountTokenField["InvestorID"] = "string"
#投资单元代码
CThostFtdcQueryCFMMCTradingAccountTokenField["InvestUnitID"] = "string"
structDict['CThostFtdcQueryCFMMCTradingAccountTokenField'] = CThostFtdcQueryCFMMCTradingAccountTokenField


#监控中心用户令牌
CThostFtdcCFMMCTradingAccountTokenField = {}
#经纪公司代码
CThostFtdcCFMMCTradingAccountTokenField["BrokerID"] = "string"
#经纪公司统一编码
CThostFtdcCFMMCTradingAccountTokenField["ParticipantID"] = "string"
#投资者帐号
CThostFtdcCFMMCTradingAccountTokenField["AccountID"] = "string"
#密钥编号
CThostFtdcCFMMCTradingAccountTokenField["KeyID"] = "int"
#动态令牌
CThostFtdcCFMMCTradingAccountTokenField["Token"] = "string"
structDict['CThostFtdcCFMMCTradingAccountTokenField'] = CThostFtdcCFMMCTradingAccountTokenField


#查询产品组
CThostFtdcQryProductGroupField = {}
#产品代码
CThostFtdcQryProductGroupField["ProductID"] = "string"
#交易所代码
CThostFtdcQryProductGroupField["ExchangeID"] = "string"
structDict['CThostFtdcQryProductGroupField'] = CThostFtdcQryProductGroupField


#投资者品种/跨品种保证金产品组
CThostFtdcProductGroupField = {}
#产品代码
CThostFtdcProductGroupField["ProductID"] = "string"
#交易所代码
CThostFtdcProductGroupField["ExchangeID"] = "string"
#产品组代码
CThostFtdcProductGroupField["ProductGroupID"] = "string"
structDict['CThostFtdcProductGroupField'] = CThostFtdcProductGroupField


#交易所公告
CThostFtdcBulletinField = {}
#交易所代码
CThostFtdcBulletinField["ExchangeID"] = "string"
#交易日
CThostFtdcBulletinField["TradingDay"] = "string"
#公告编号
CThostFtdcBulletinField["BulletinID"] = "int"
#序列号
CThostFtdcBulletinField["SequenceNo"] = "int"
#公告类型
CThostFtdcBulletinField["NewsType"] = "string"
#紧急程度
CThostFtdcBulletinField["NewsUrgency"] = "char"
#发送时间
CThostFtdcBulletinField["SendTime"] = "string"
#消息摘要
CThostFtdcBulletinField["Abstract"] = "string"
#消息来源
CThostFtdcBulletinField["ComeFrom"] = "string"
#消息正文
CThostFtdcBulletinField["Content"] = "string"
#WEB地址
CThostFtdcBulletinField["URLLink"] = "string"
#市场代码
CThostFtdcBulletinField["MarketID"] = "string"
structDict['CThostFtdcBulletinField'] = CThostFtdcBulletinField


#查询交易所公告
CThostFtdcQryBulletinField = {}
#交易所代码
CThostFtdcQryBulletinField["ExchangeID"] = "string"
#公告编号
CThostFtdcQryBulletinField["BulletinID"] = "int"
#序列号
CThostFtdcQryBulletinField["SequenceNo"] = "int"
#公告类型
CThostFtdcQryBulletinField["NewsType"] = "string"
#紧急程度
CThostFtdcQryBulletinField["NewsUrgency"] = "char"
structDict['CThostFtdcQryBulletinField'] = CThostFtdcQryBulletinField


#转帐开户请求
CThostFtdcReqOpenAccountField = {}
#业务功能码
CThostFtdcReqOpenAccountField["TradeCode"] = "string"
#银行代码
CThostFtdcReqOpenAccountField["BankID"] = "string"
#银行分支机构代码
CThostFtdcReqOpenAccountField["BankBranchID"] = "string"
#期商代码
CThostFtdcReqOpenAccountField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcReqOpenAccountField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcReqOpenAccountField["TradeDate"] = "string"
#交易时间
CThostFtdcReqOpenAccountField["TradeTime"] = "string"
#银行流水号
CThostFtdcReqOpenAccountField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcReqOpenAccountField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcReqOpenAccountField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcReqOpenAccountField["LastFragment"] = "char"
#会话号
CThostFtdcReqOpenAccountField["SessionID"] = "int"
#客户姓名
CThostFtdcReqOpenAccountField["CustomerName"] = "string"
#证件类型
CThostFtdcReqOpenAccountField["IdCardType"] = "char"
#证件号码
CThostFtdcReqOpenAccountField["IdentifiedCardNo"] = "string"
#性别
CThostFtdcReqOpenAccountField["Gender"] = "char"
#国家代码
CThostFtdcReqOpenAccountField["CountryCode"] = "string"
#客户类型
CThostFtdcReqOpenAccountField["CustType"] = "char"
#地址
CThostFtdcReqOpenAccountField["Address"] = "string"
#邮编
CThostFtdcReqOpenAccountField["ZipCode"] = "string"
#电话号码
CThostFtdcReqOpenAccountField["Telephone"] = "string"
#手机
CThostFtdcReqOpenAccountField["MobilePhone"] = "string"
#传真
CThostFtdcReqOpenAccountField["Fax"] = "string"
#电子邮件
CThostFtdcReqOpenAccountField["EMail"] = "string"
#资金账户状态
CThostFtdcReqOpenAccountField["MoneyAccountStatus"] = "char"
#银行帐号
CThostFtdcReqOpenAccountField["BankAccount"] = "string"
#银行密码
CThostFtdcReqOpenAccountField["BankPassWord"] = "string"
#投资者帐号
CThostFtdcReqOpenAccountField["AccountID"] = "string"
#期货密码
CThostFtdcReqOpenAccountField["Password"] = "string"
#安装编号
CThostFtdcReqOpenAccountField["InstallID"] = "int"
#验证客户证件号码标志
CThostFtdcReqOpenAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcReqOpenAccountField["CurrencyID"] = "string"
#汇钞标志
CThostFtdcReqOpenAccountField["CashExchangeCode"] = "char"
#摘要
CThostFtdcReqOpenAccountField["Digest"] = "string"
#银行帐号类型
CThostFtdcReqOpenAccountField["BankAccType"] = "char"
#渠道标志
CThostFtdcReqOpenAccountField["DeviceID"] = "string"
#期货单位帐号类型
CThostFtdcReqOpenAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CThostFtdcReqOpenAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CThostFtdcReqOpenAccountField["BankSecuAcc"] = "string"
#银行密码标志
CThostFtdcReqOpenAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CThostFtdcReqOpenAccountField["SecuPwdFlag"] = "char"
#交易柜员
CThostFtdcReqOpenAccountField["OperNo"] = "string"
#交易ID
CThostFtdcReqOpenAccountField["TID"] = "int"
#用户标识
CThostFtdcReqOpenAccountField["UserID"] = "string"
#长客户姓名
CThostFtdcReqOpenAccountField["LongCustomerName"] = "string"
structDict['CThostFtdcReqOpenAccountField'] = CThostFtdcReqOpenAccountField


#转帐销户请求
CThostFtdcReqCancelAccountField = {}
#业务功能码
CThostFtdcReqCancelAccountField["TradeCode"] = "string"
#银行代码
CThostFtdcReqCancelAccountField["BankID"] = "string"
#银行分支机构代码
CThostFtdcReqCancelAccountField["BankBranchID"] = "string"
#期商代码
CThostFtdcReqCancelAccountField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcReqCancelAccountField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcReqCancelAccountField["TradeDate"] = "string"
#交易时间
CThostFtdcReqCancelAccountField["TradeTime"] = "string"
#银行流水号
CThostFtdcReqCancelAccountField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcReqCancelAccountField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcReqCancelAccountField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcReqCancelAccountField["LastFragment"] = "char"
#会话号
CThostFtdcReqCancelAccountField["SessionID"] = "int"
#客户姓名
CThostFtdcReqCancelAccountField["CustomerName"] = "string"
#证件类型
CThostFtdcReqCancelAccountField["IdCardType"] = "char"
#证件号码
CThostFtdcReqCancelAccountField["IdentifiedCardNo"] = "string"
#性别
CThostFtdcReqCancelAccountField["Gender"] = "char"
#国家代码
CThostFtdcReqCancelAccountField["CountryCode"] = "string"
#客户类型
CThostFtdcReqCancelAccountField["CustType"] = "char"
#地址
CThostFtdcReqCancelAccountField["Address"] = "string"
#邮编
CThostFtdcReqCancelAccountField["ZipCode"] = "string"
#电话号码
CThostFtdcReqCancelAccountField["Telephone"] = "string"
#手机
CThostFtdcReqCancelAccountField["MobilePhone"] = "string"
#传真
CThostFtdcReqCancelAccountField["Fax"] = "string"
#电子邮件
CThostFtdcReqCancelAccountField["EMail"] = "string"
#资金账户状态
CThostFtdcReqCancelAccountField["MoneyAccountStatus"] = "char"
#银行帐号
CThostFtdcReqCancelAccountField["BankAccount"] = "string"
#银行密码
CThostFtdcReqCancelAccountField["BankPassWord"] = "string"
#投资者帐号
CThostFtdcReqCancelAccountField["AccountID"] = "string"
#期货密码
CThostFtdcReqCancelAccountField["Password"] = "string"
#安装编号
CThostFtdcReqCancelAccountField["InstallID"] = "int"
#验证客户证件号码标志
CThostFtdcReqCancelAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcReqCancelAccountField["CurrencyID"] = "string"
#汇钞标志
CThostFtdcReqCancelAccountField["CashExchangeCode"] = "char"
#摘要
CThostFtdcReqCancelAccountField["Digest"] = "string"
#银行帐号类型
CThostFtdcReqCancelAccountField["BankAccType"] = "char"
#渠道标志
CThostFtdcReqCancelAccountField["DeviceID"] = "string"
#期货单位帐号类型
CThostFtdcReqCancelAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CThostFtdcReqCancelAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CThostFtdcReqCancelAccountField["BankSecuAcc"] = "string"
#银行密码标志
CThostFtdcReqCancelAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CThostFtdcReqCancelAccountField["SecuPwdFlag"] = "char"
#交易柜员
CThostFtdcReqCancelAccountField["OperNo"] = "string"
#交易ID
CThostFtdcReqCancelAccountField["TID"] = "int"
#用户标识
CThostFtdcReqCancelAccountField["UserID"] = "string"
#长客户姓名
CThostFtdcReqCancelAccountField["LongCustomerName"] = "string"
structDict['CThostFtdcReqCancelAccountField'] = CThostFtdcReqCancelAccountField


#变更银行账户请求
CThostFtdcReqChangeAccountField = {}
#业务功能码
CThostFtdcReqChangeAccountField["TradeCode"] = "string"
#银行代码
CThostFtdcReqChangeAccountField["BankID"] = "string"
#银行分支机构代码
CThostFtdcReqChangeAccountField["BankBranchID"] = "string"
#期商代码
CThostFtdcReqChangeAccountField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcReqChangeAccountField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcReqChangeAccountField["TradeDate"] = "string"
#交易时间
CThostFtdcReqChangeAccountField["TradeTime"] = "string"
#银行流水号
CThostFtdcReqChangeAccountField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcReqChangeAccountField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcReqChangeAccountField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcReqChangeAccountField["LastFragment"] = "char"
#会话号
CThostFtdcReqChangeAccountField["SessionID"] = "int"
#客户姓名
CThostFtdcReqChangeAccountField["CustomerName"] = "string"
#证件类型
CThostFtdcReqChangeAccountField["IdCardType"] = "char"
#证件号码
CThostFtdcReqChangeAccountField["IdentifiedCardNo"] = "string"
#性别
CThostFtdcReqChangeAccountField["Gender"] = "char"
#国家代码
CThostFtdcReqChangeAccountField["CountryCode"] = "string"
#客户类型
CThostFtdcReqChangeAccountField["CustType"] = "char"
#地址
CThostFtdcReqChangeAccountField["Address"] = "string"
#邮编
CThostFtdcReqChangeAccountField["ZipCode"] = "string"
#电话号码
CThostFtdcReqChangeAccountField["Telephone"] = "string"
#手机
CThostFtdcReqChangeAccountField["MobilePhone"] = "string"
#传真
CThostFtdcReqChangeAccountField["Fax"] = "string"
#电子邮件
CThostFtdcReqChangeAccountField["EMail"] = "string"
#资金账户状态
CThostFtdcReqChangeAccountField["MoneyAccountStatus"] = "char"
#银行帐号
CThostFtdcReqChangeAccountField["BankAccount"] = "string"
#银行密码
CThostFtdcReqChangeAccountField["BankPassWord"] = "string"
#新银行帐号
CThostFtdcReqChangeAccountField["NewBankAccount"] = "string"
#新银行密码
CThostFtdcReqChangeAccountField["NewBankPassWord"] = "string"
#投资者帐号
CThostFtdcReqChangeAccountField["AccountID"] = "string"
#期货密码
CThostFtdcReqChangeAccountField["Password"] = "string"
#银行帐号类型
CThostFtdcReqChangeAccountField["BankAccType"] = "char"
#安装编号
CThostFtdcReqChangeAccountField["InstallID"] = "int"
#验证客户证件号码标志
CThostFtdcReqChangeAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcReqChangeAccountField["CurrencyID"] = "string"
#期货公司银行编码
CThostFtdcReqChangeAccountField["BrokerIDByBank"] = "string"
#银行密码标志
CThostFtdcReqChangeAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CThostFtdcReqChangeAccountField["SecuPwdFlag"] = "char"
#交易ID
CThostFtdcReqChangeAccountField["TID"] = "int"
#摘要
CThostFtdcReqChangeAccountField["Digest"] = "string"
#长客户姓名
CThostFtdcReqChangeAccountField["LongCustomerName"] = "string"
structDict['CThostFtdcReqChangeAccountField'] = CThostFtdcReqChangeAccountField


#转账请求
CThostFtdcReqTransferField = {}
#业务功能码
CThostFtdcReqTransferField["TradeCode"] = "string"
#银行代码
CThostFtdcReqTransferField["BankID"] = "string"
#银行分支机构代码
CThostFtdcReqTransferField["BankBranchID"] = "string"
#期商代码
CThostFtdcReqTransferField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcReqTransferField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcReqTransferField["TradeDate"] = "string"
#交易时间
CThostFtdcReqTransferField["TradeTime"] = "string"
#银行流水号
CThostFtdcReqTransferField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcReqTransferField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcReqTransferField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcReqTransferField["LastFragment"] = "char"
#会话号
CThostFtdcReqTransferField["SessionID"] = "int"
#客户姓名
CThostFtdcReqTransferField["CustomerName"] = "string"
#证件类型
CThostFtdcReqTransferField["IdCardType"] = "char"
#证件号码
CThostFtdcReqTransferField["IdentifiedCardNo"] = "string"
#客户类型
CThostFtdcReqTransferField["CustType"] = "char"
#银行帐号
CThostFtdcReqTransferField["BankAccount"] = "string"
#银行密码
CThostFtdcReqTransferField["BankPassWord"] = "string"
#投资者帐号
CThostFtdcReqTransferField["AccountID"] = "string"
#期货密码
CThostFtdcReqTransferField["Password"] = "string"
#安装编号
CThostFtdcReqTransferField["InstallID"] = "int"
#期货公司流水号
CThostFtdcReqTransferField["FutureSerial"] = "int"
#用户标识
CThostFtdcReqTransferField["UserID"] = "string"
#验证客户证件号码标志
CThostFtdcReqTransferField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcReqTransferField["CurrencyID"] = "string"
#转帐金额
CThostFtdcReqTransferField["TradeAmount"] = "float"
#期货可取金额
CThostFtdcReqTransferField["FutureFetchAmount"] = "float"
#费用支付标志
CThostFtdcReqTransferField["FeePayFlag"] = "char"
#应收客户费用
CThostFtdcReqTransferField["CustFee"] = "float"
#应收期货公司费用
CThostFtdcReqTransferField["BrokerFee"] = "float"
#发送方给接收方的消息
CThostFtdcReqTransferField["Message"] = "string"
#摘要
CThostFtdcReqTransferField["Digest"] = "string"
#银行帐号类型
CThostFtdcReqTransferField["BankAccType"] = "char"
#渠道标志
CThostFtdcReqTransferField["DeviceID"] = "string"
#期货单位帐号类型
CThostFtdcReqTransferField["BankSecuAccType"] = "char"
#期货公司银行编码
CThostFtdcReqTransferField["BrokerIDByBank"] = "string"
#期货单位帐号
CThostFtdcReqTransferField["BankSecuAcc"] = "string"
#银行密码标志
CThostFtdcReqTransferField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CThostFtdcReqTransferField["SecuPwdFlag"] = "char"
#交易柜员
CThostFtdcReqTransferField["OperNo"] = "string"
#请求编号
CThostFtdcReqTransferField["RequestID"] = "int"
#交易ID
CThostFtdcReqTransferField["TID"] = "int"
#转账交易状态
CThostFtdcReqTransferField["TransferStatus"] = "char"
#长客户姓名
CThostFtdcReqTransferField["LongCustomerName"] = "string"
structDict['CThostFtdcReqTransferField'] = CThostFtdcReqTransferField


#银行发起银行资金转期货响应
CThostFtdcRspTransferField = {}
#业务功能码
CThostFtdcRspTransferField["TradeCode"] = "string"
#银行代码
CThostFtdcRspTransferField["BankID"] = "string"
#银行分支机构代码
CThostFtdcRspTransferField["BankBranchID"] = "string"
#期商代码
CThostFtdcRspTransferField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcRspTransferField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcRspTransferField["TradeDate"] = "string"
#交易时间
CThostFtdcRspTransferField["TradeTime"] = "string"
#银行流水号
CThostFtdcRspTransferField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcRspTransferField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcRspTransferField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcRspTransferField["LastFragment"] = "char"
#会话号
CThostFtdcRspTransferField["SessionID"] = "int"
#客户姓名
CThostFtdcRspTransferField["CustomerName"] = "string"
#证件类型
CThostFtdcRspTransferField["IdCardType"] = "char"
#证件号码
CThostFtdcRspTransferField["IdentifiedCardNo"] = "string"
#客户类型
CThostFtdcRspTransferField["CustType"] = "char"
#银行帐号
CThostFtdcRspTransferField["BankAccount"] = "string"
#银行密码
CThostFtdcRspTransferField["BankPassWord"] = "string"
#投资者帐号
CThostFtdcRspTransferField["AccountID"] = "string"
#期货密码
CThostFtdcRspTransferField["Password"] = "string"
#安装编号
CThostFtdcRspTransferField["InstallID"] = "int"
#期货公司流水号
CThostFtdcRspTransferField["FutureSerial"] = "int"
#用户标识
CThostFtdcRspTransferField["UserID"] = "string"
#验证客户证件号码标志
CThostFtdcRspTransferField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcRspTransferField["CurrencyID"] = "string"
#转帐金额
CThostFtdcRspTransferField["TradeAmount"] = "float"
#期货可取金额
CThostFtdcRspTransferField["FutureFetchAmount"] = "float"
#费用支付标志
CThostFtdcRspTransferField["FeePayFlag"] = "char"
#应收客户费用
CThostFtdcRspTransferField["CustFee"] = "float"
#应收期货公司费用
CThostFtdcRspTransferField["BrokerFee"] = "float"
#发送方给接收方的消息
CThostFtdcRspTransferField["Message"] = "string"
#摘要
CThostFtdcRspTransferField["Digest"] = "string"
#银行帐号类型
CThostFtdcRspTransferField["BankAccType"] = "char"
#渠道标志
CThostFtdcRspTransferField["DeviceID"] = "string"
#期货单位帐号类型
CThostFtdcRspTransferField["BankSecuAccType"] = "char"
#期货公司银行编码
CThostFtdcRspTransferField["BrokerIDByBank"] = "string"
#期货单位帐号
CThostFtdcRspTransferField["BankSecuAcc"] = "string"
#银行密码标志
CThostFtdcRspTransferField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CThostFtdcRspTransferField["SecuPwdFlag"] = "char"
#交易柜员
CThostFtdcRspTransferField["OperNo"] = "string"
#请求编号
CThostFtdcRspTransferField["RequestID"] = "int"
#交易ID
CThostFtdcRspTransferField["TID"] = "int"
#转账交易状态
CThostFtdcRspTransferField["TransferStatus"] = "char"
#错误代码
CThostFtdcRspTransferField["ErrorID"] = "int"
#错误信息
CThostFtdcRspTransferField["ErrorMsg"] = "string"
#长客户姓名
CThostFtdcRspTransferField["LongCustomerName"] = "string"
structDict['CThostFtdcRspTransferField'] = CThostFtdcRspTransferField


#冲正请求
CThostFtdcReqRepealField = {}
#冲正时间间隔
CThostFtdcReqRepealField["RepealTimeInterval"] = "int"
#已经冲正次数
CThostFtdcReqRepealField["RepealedTimes"] = "int"
#银行冲正标志
CThostFtdcReqRepealField["BankRepealFlag"] = "char"
#期商冲正标志
CThostFtdcReqRepealField["BrokerRepealFlag"] = "char"
#被冲正平台流水号
CThostFtdcReqRepealField["PlateRepealSerial"] = "int"
#被冲正银行流水号
CThostFtdcReqRepealField["BankRepealSerial"] = "string"
#被冲正期货流水号
CThostFtdcReqRepealField["FutureRepealSerial"] = "int"
#业务功能码
CThostFtdcReqRepealField["TradeCode"] = "string"
#银行代码
CThostFtdcReqRepealField["BankID"] = "string"
#银行分支机构代码
CThostFtdcReqRepealField["BankBranchID"] = "string"
#期商代码
CThostFtdcReqRepealField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcReqRepealField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcReqRepealField["TradeDate"] = "string"
#交易时间
CThostFtdcReqRepealField["TradeTime"] = "string"
#银行流水号
CThostFtdcReqRepealField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcReqRepealField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcReqRepealField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcReqRepealField["LastFragment"] = "char"
#会话号
CThostFtdcReqRepealField["SessionID"] = "int"
#客户姓名
CThostFtdcReqRepealField["CustomerName"] = "string"
#证件类型
CThostFtdcReqRepealField["IdCardType"] = "char"
#证件号码
CThostFtdcReqRepealField["IdentifiedCardNo"] = "string"
#客户类型
CThostFtdcReqRepealField["CustType"] = "char"
#银行帐号
CThostFtdcReqRepealField["BankAccount"] = "string"
#银行密码
CThostFtdcReqRepealField["BankPassWord"] = "string"
#投资者帐号
CThostFtdcReqRepealField["AccountID"] = "string"
#期货密码
CThostFtdcReqRepealField["Password"] = "string"
#安装编号
CThostFtdcReqRepealField["InstallID"] = "int"
#期货公司流水号
CThostFtdcReqRepealField["FutureSerial"] = "int"
#用户标识
CThostFtdcReqRepealField["UserID"] = "string"
#验证客户证件号码标志
CThostFtdcReqRepealField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcReqRepealField["CurrencyID"] = "string"
#转帐金额
CThostFtdcReqRepealField["TradeAmount"] = "float"
#期货可取金额
CThostFtdcReqRepealField["FutureFetchAmount"] = "float"
#费用支付标志
CThostFtdcReqRepealField["FeePayFlag"] = "char"
#应收客户费用
CThostFtdcReqRepealField["CustFee"] = "float"
#应收期货公司费用
CThostFtdcReqRepealField["BrokerFee"] = "float"
#发送方给接收方的消息
CThostFtdcReqRepealField["Message"] = "string"
#摘要
CThostFtdcReqRepealField["Digest"] = "string"
#银行帐号类型
CThostFtdcReqRepealField["BankAccType"] = "char"
#渠道标志
CThostFtdcReqRepealField["DeviceID"] = "string"
#期货单位帐号类型
CThostFtdcReqRepealField["BankSecuAccType"] = "char"
#期货公司银行编码
CThostFtdcReqRepealField["BrokerIDByBank"] = "string"
#期货单位帐号
CThostFtdcReqRepealField["BankSecuAcc"] = "string"
#银行密码标志
CThostFtdcReqRepealField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CThostFtdcReqRepealField["SecuPwdFlag"] = "char"
#交易柜员
CThostFtdcReqRepealField["OperNo"] = "string"
#请求编号
CThostFtdcReqRepealField["RequestID"] = "int"
#交易ID
CThostFtdcReqRepealField["TID"] = "int"
#转账交易状态
CThostFtdcReqRepealField["TransferStatus"] = "char"
#长客户姓名
CThostFtdcReqRepealField["LongCustomerName"] = "string"
structDict['CThostFtdcReqRepealField'] = CThostFtdcReqRepealField


#冲正响应
CThostFtdcRspRepealField = {}
#冲正时间间隔
CThostFtdcRspRepealField["RepealTimeInterval"] = "int"
#已经冲正次数
CThostFtdcRspRepealField["RepealedTimes"] = "int"
#银行冲正标志
CThostFtdcRspRepealField["BankRepealFlag"] = "char"
#期商冲正标志
CThostFtdcRspRepealField["BrokerRepealFlag"] = "char"
#被冲正平台流水号
CThostFtdcRspRepealField["PlateRepealSerial"] = "int"
#被冲正银行流水号
CThostFtdcRspRepealField["BankRepealSerial"] = "string"
#被冲正期货流水号
CThostFtdcRspRepealField["FutureRepealSerial"] = "int"
#业务功能码
CThostFtdcRspRepealField["TradeCode"] = "string"
#银行代码
CThostFtdcRspRepealField["BankID"] = "string"
#银行分支机构代码
CThostFtdcRspRepealField["BankBranchID"] = "string"
#期商代码
CThostFtdcRspRepealField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcRspRepealField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcRspRepealField["TradeDate"] = "string"
#交易时间
CThostFtdcRspRepealField["TradeTime"] = "string"
#银行流水号
CThostFtdcRspRepealField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcRspRepealField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcRspRepealField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcRspRepealField["LastFragment"] = "char"
#会话号
CThostFtdcRspRepealField["SessionID"] = "int"
#客户姓名
CThostFtdcRspRepealField["CustomerName"] = "string"
#证件类型
CThostFtdcRspRepealField["IdCardType"] = "char"
#证件号码
CThostFtdcRspRepealField["IdentifiedCardNo"] = "string"
#客户类型
CThostFtdcRspRepealField["CustType"] = "char"
#银行帐号
CThostFtdcRspRepealField["BankAccount"] = "string"
#银行密码
CThostFtdcRspRepealField["BankPassWord"] = "string"
#投资者帐号
CThostFtdcRspRepealField["AccountID"] = "string"
#期货密码
CThostFtdcRspRepealField["Password"] = "string"
#安装编号
CThostFtdcRspRepealField["InstallID"] = "int"
#期货公司流水号
CThostFtdcRspRepealField["FutureSerial"] = "int"
#用户标识
CThostFtdcRspRepealField["UserID"] = "string"
#验证客户证件号码标志
CThostFtdcRspRepealField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcRspRepealField["CurrencyID"] = "string"
#转帐金额
CThostFtdcRspRepealField["TradeAmount"] = "float"
#期货可取金额
CThostFtdcRspRepealField["FutureFetchAmount"] = "float"
#费用支付标志
CThostFtdcRspRepealField["FeePayFlag"] = "char"
#应收客户费用
CThostFtdcRspRepealField["CustFee"] = "float"
#应收期货公司费用
CThostFtdcRspRepealField["BrokerFee"] = "float"
#发送方给接收方的消息
CThostFtdcRspRepealField["Message"] = "string"
#摘要
CThostFtdcRspRepealField["Digest"] = "string"
#银行帐号类型
CThostFtdcRspRepealField["BankAccType"] = "char"
#渠道标志
CThostFtdcRspRepealField["DeviceID"] = "string"
#期货单位帐号类型
CThostFtdcRspRepealField["BankSecuAccType"] = "char"
#期货公司银行编码
CThostFtdcRspRepealField["BrokerIDByBank"] = "string"
#期货单位帐号
CThostFtdcRspRepealField["BankSecuAcc"] = "string"
#银行密码标志
CThostFtdcRspRepealField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CThostFtdcRspRepealField["SecuPwdFlag"] = "char"
#交易柜员
CThostFtdcRspRepealField["OperNo"] = "string"
#请求编号
CThostFtdcRspRepealField["RequestID"] = "int"
#交易ID
CThostFtdcRspRepealField["TID"] = "int"
#转账交易状态
CThostFtdcRspRepealField["TransferStatus"] = "char"
#错误代码
CThostFtdcRspRepealField["ErrorID"] = "int"
#错误信息
CThostFtdcRspRepealField["ErrorMsg"] = "string"
#长客户姓名
CThostFtdcRspRepealField["LongCustomerName"] = "string"
structDict['CThostFtdcRspRepealField'] = CThostFtdcRspRepealField


#查询账户信息请求
CThostFtdcReqQueryAccountField = {}
#业务功能码
CThostFtdcReqQueryAccountField["TradeCode"] = "string"
#银行代码
CThostFtdcReqQueryAccountField["BankID"] = "string"
#银行分支机构代码
CThostFtdcReqQueryAccountField["BankBranchID"] = "string"
#期商代码
CThostFtdcReqQueryAccountField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcReqQueryAccountField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcReqQueryAccountField["TradeDate"] = "string"
#交易时间
CThostFtdcReqQueryAccountField["TradeTime"] = "string"
#银行流水号
CThostFtdcReqQueryAccountField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcReqQueryAccountField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcReqQueryAccountField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcReqQueryAccountField["LastFragment"] = "char"
#会话号
CThostFtdcReqQueryAccountField["SessionID"] = "int"
#客户姓名
CThostFtdcReqQueryAccountField["CustomerName"] = "string"
#证件类型
CThostFtdcReqQueryAccountField["IdCardType"] = "char"
#证件号码
CThostFtdcReqQueryAccountField["IdentifiedCardNo"] = "string"
#客户类型
CThostFtdcReqQueryAccountField["CustType"] = "char"
#银行帐号
CThostFtdcReqQueryAccountField["BankAccount"] = "string"
#银行密码
CThostFtdcReqQueryAccountField["BankPassWord"] = "string"
#投资者帐号
CThostFtdcReqQueryAccountField["AccountID"] = "string"
#期货密码
CThostFtdcReqQueryAccountField["Password"] = "string"
#期货公司流水号
CThostFtdcReqQueryAccountField["FutureSerial"] = "int"
#安装编号
CThostFtdcReqQueryAccountField["InstallID"] = "int"
#用户标识
CThostFtdcReqQueryAccountField["UserID"] = "string"
#验证客户证件号码标志
CThostFtdcReqQueryAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcReqQueryAccountField["CurrencyID"] = "string"
#摘要
CThostFtdcReqQueryAccountField["Digest"] = "string"
#银行帐号类型
CThostFtdcReqQueryAccountField["BankAccType"] = "char"
#渠道标志
CThostFtdcReqQueryAccountField["DeviceID"] = "string"
#期货单位帐号类型
CThostFtdcReqQueryAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CThostFtdcReqQueryAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CThostFtdcReqQueryAccountField["BankSecuAcc"] = "string"
#银行密码标志
CThostFtdcReqQueryAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CThostFtdcReqQueryAccountField["SecuPwdFlag"] = "char"
#交易柜员
CThostFtdcReqQueryAccountField["OperNo"] = "string"
#请求编号
CThostFtdcReqQueryAccountField["RequestID"] = "int"
#交易ID
CThostFtdcReqQueryAccountField["TID"] = "int"
#长客户姓名
CThostFtdcReqQueryAccountField["LongCustomerName"] = "string"
structDict['CThostFtdcReqQueryAccountField'] = CThostFtdcReqQueryAccountField


#查询账户信息响应
CThostFtdcRspQueryAccountField = {}
#业务功能码
CThostFtdcRspQueryAccountField["TradeCode"] = "string"
#银行代码
CThostFtdcRspQueryAccountField["BankID"] = "string"
#银行分支机构代码
CThostFtdcRspQueryAccountField["BankBranchID"] = "string"
#期商代码
CThostFtdcRspQueryAccountField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcRspQueryAccountField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcRspQueryAccountField["TradeDate"] = "string"
#交易时间
CThostFtdcRspQueryAccountField["TradeTime"] = "string"
#银行流水号
CThostFtdcRspQueryAccountField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcRspQueryAccountField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcRspQueryAccountField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcRspQueryAccountField["LastFragment"] = "char"
#会话号
CThostFtdcRspQueryAccountField["SessionID"] = "int"
#客户姓名
CThostFtdcRspQueryAccountField["CustomerName"] = "string"
#证件类型
CThostFtdcRspQueryAccountField["IdCardType"] = "char"
#证件号码
CThostFtdcRspQueryAccountField["IdentifiedCardNo"] = "string"
#客户类型
CThostFtdcRspQueryAccountField["CustType"] = "char"
#银行帐号
CThostFtdcRspQueryAccountField["BankAccount"] = "string"
#银行密码
CThostFtdcRspQueryAccountField["BankPassWord"] = "string"
#投资者帐号
CThostFtdcRspQueryAccountField["AccountID"] = "string"
#期货密码
CThostFtdcRspQueryAccountField["Password"] = "string"
#期货公司流水号
CThostFtdcRspQueryAccountField["FutureSerial"] = "int"
#安装编号
CThostFtdcRspQueryAccountField["InstallID"] = "int"
#用户标识
CThostFtdcRspQueryAccountField["UserID"] = "string"
#验证客户证件号码标志
CThostFtdcRspQueryAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcRspQueryAccountField["CurrencyID"] = "string"
#摘要
CThostFtdcRspQueryAccountField["Digest"] = "string"
#银行帐号类型
CThostFtdcRspQueryAccountField["BankAccType"] = "char"
#渠道标志
CThostFtdcRspQueryAccountField["DeviceID"] = "string"
#期货单位帐号类型
CThostFtdcRspQueryAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CThostFtdcRspQueryAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CThostFtdcRspQueryAccountField["BankSecuAcc"] = "string"
#银行密码标志
CThostFtdcRspQueryAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CThostFtdcRspQueryAccountField["SecuPwdFlag"] = "char"
#交易柜员
CThostFtdcRspQueryAccountField["OperNo"] = "string"
#请求编号
CThostFtdcRspQueryAccountField["RequestID"] = "int"
#交易ID
CThostFtdcRspQueryAccountField["TID"] = "int"
#银行可用金额
CThostFtdcRspQueryAccountField["BankUseAmount"] = "float"
#银行可取金额
CThostFtdcRspQueryAccountField["BankFetchAmount"] = "float"
#长客户姓名
CThostFtdcRspQueryAccountField["LongCustomerName"] = "string"
structDict['CThostFtdcRspQueryAccountField'] = CThostFtdcRspQueryAccountField


#期商签到签退
CThostFtdcFutureSignIOField = {}
#业务功能码
CThostFtdcFutureSignIOField["TradeCode"] = "string"
#银行代码
CThostFtdcFutureSignIOField["BankID"] = "string"
#银行分支机构代码
CThostFtdcFutureSignIOField["BankBranchID"] = "string"
#期商代码
CThostFtdcFutureSignIOField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcFutureSignIOField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcFutureSignIOField["TradeDate"] = "string"
#交易时间
CThostFtdcFutureSignIOField["TradeTime"] = "string"
#银行流水号
CThostFtdcFutureSignIOField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcFutureSignIOField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcFutureSignIOField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcFutureSignIOField["LastFragment"] = "char"
#会话号
CThostFtdcFutureSignIOField["SessionID"] = "int"
#安装编号
CThostFtdcFutureSignIOField["InstallID"] = "int"
#用户标识
CThostFtdcFutureSignIOField["UserID"] = "string"
#摘要
CThostFtdcFutureSignIOField["Digest"] = "string"
#币种代码
CThostFtdcFutureSignIOField["CurrencyID"] = "string"
#渠道标志
CThostFtdcFutureSignIOField["DeviceID"] = "string"
#期货公司银行编码
CThostFtdcFutureSignIOField["BrokerIDByBank"] = "string"
#交易柜员
CThostFtdcFutureSignIOField["OperNo"] = "string"
#请求编号
CThostFtdcFutureSignIOField["RequestID"] = "int"
#交易ID
CThostFtdcFutureSignIOField["TID"] = "int"
structDict['CThostFtdcFutureSignIOField'] = CThostFtdcFutureSignIOField


#期商签到响应
CThostFtdcRspFutureSignInField = {}
#业务功能码
CThostFtdcRspFutureSignInField["TradeCode"] = "string"
#银行代码
CThostFtdcRspFutureSignInField["BankID"] = "string"
#银行分支机构代码
CThostFtdcRspFutureSignInField["BankBranchID"] = "string"
#期商代码
CThostFtdcRspFutureSignInField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcRspFutureSignInField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcRspFutureSignInField["TradeDate"] = "string"
#交易时间
CThostFtdcRspFutureSignInField["TradeTime"] = "string"
#银行流水号
CThostFtdcRspFutureSignInField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcRspFutureSignInField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcRspFutureSignInField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcRspFutureSignInField["LastFragment"] = "char"
#会话号
CThostFtdcRspFutureSignInField["SessionID"] = "int"
#安装编号
CThostFtdcRspFutureSignInField["InstallID"] = "int"
#用户标识
CThostFtdcRspFutureSignInField["UserID"] = "string"
#摘要
CThostFtdcRspFutureSignInField["Digest"] = "string"
#币种代码
CThostFtdcRspFutureSignInField["CurrencyID"] = "string"
#渠道标志
CThostFtdcRspFutureSignInField["DeviceID"] = "string"
#期货公司银行编码
CThostFtdcRspFutureSignInField["BrokerIDByBank"] = "string"
#交易柜员
CThostFtdcRspFutureSignInField["OperNo"] = "string"
#请求编号
CThostFtdcRspFutureSignInField["RequestID"] = "int"
#交易ID
CThostFtdcRspFutureSignInField["TID"] = "int"
#错误代码
CThostFtdcRspFutureSignInField["ErrorID"] = "int"
#错误信息
CThostFtdcRspFutureSignInField["ErrorMsg"] = "string"
#PIN密钥
CThostFtdcRspFutureSignInField["PinKey"] = "string"
#MAC密钥
CThostFtdcRspFutureSignInField["MacKey"] = "string"
structDict['CThostFtdcRspFutureSignInField'] = CThostFtdcRspFutureSignInField


#期商签退请求
CThostFtdcReqFutureSignOutField = {}
#业务功能码
CThostFtdcReqFutureSignOutField["TradeCode"] = "string"
#银行代码
CThostFtdcReqFutureSignOutField["BankID"] = "string"
#银行分支机构代码
CThostFtdcReqFutureSignOutField["BankBranchID"] = "string"
#期商代码
CThostFtdcReqFutureSignOutField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcReqFutureSignOutField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcReqFutureSignOutField["TradeDate"] = "string"
#交易时间
CThostFtdcReqFutureSignOutField["TradeTime"] = "string"
#银行流水号
CThostFtdcReqFutureSignOutField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcReqFutureSignOutField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcReqFutureSignOutField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcReqFutureSignOutField["LastFragment"] = "char"
#会话号
CThostFtdcReqFutureSignOutField["SessionID"] = "int"
#安装编号
CThostFtdcReqFutureSignOutField["InstallID"] = "int"
#用户标识
CThostFtdcReqFutureSignOutField["UserID"] = "string"
#摘要
CThostFtdcReqFutureSignOutField["Digest"] = "string"
#币种代码
CThostFtdcReqFutureSignOutField["CurrencyID"] = "string"
#渠道标志
CThostFtdcReqFutureSignOutField["DeviceID"] = "string"
#期货公司银行编码
CThostFtdcReqFutureSignOutField["BrokerIDByBank"] = "string"
#交易柜员
CThostFtdcReqFutureSignOutField["OperNo"] = "string"
#请求编号
CThostFtdcReqFutureSignOutField["RequestID"] = "int"
#交易ID
CThostFtdcReqFutureSignOutField["TID"] = "int"
structDict['CThostFtdcReqFutureSignOutField'] = CThostFtdcReqFutureSignOutField


#期商签退响应
CThostFtdcRspFutureSignOutField = {}
#业务功能码
CThostFtdcRspFutureSignOutField["TradeCode"] = "string"
#银行代码
CThostFtdcRspFutureSignOutField["BankID"] = "string"
#银行分支机构代码
CThostFtdcRspFutureSignOutField["BankBranchID"] = "string"
#期商代码
CThostFtdcRspFutureSignOutField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcRspFutureSignOutField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcRspFutureSignOutField["TradeDate"] = "string"
#交易时间
CThostFtdcRspFutureSignOutField["TradeTime"] = "string"
#银行流水号
CThostFtdcRspFutureSignOutField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcRspFutureSignOutField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcRspFutureSignOutField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcRspFutureSignOutField["LastFragment"] = "char"
#会话号
CThostFtdcRspFutureSignOutField["SessionID"] = "int"
#安装编号
CThostFtdcRspFutureSignOutField["InstallID"] = "int"
#用户标识
CThostFtdcRspFutureSignOutField["UserID"] = "string"
#摘要
CThostFtdcRspFutureSignOutField["Digest"] = "string"
#币种代码
CThostFtdcRspFutureSignOutField["CurrencyID"] = "string"
#渠道标志
CThostFtdcRspFutureSignOutField["DeviceID"] = "string"
#期货公司银行编码
CThostFtdcRspFutureSignOutField["BrokerIDByBank"] = "string"
#交易柜员
CThostFtdcRspFutureSignOutField["OperNo"] = "string"
#请求编号
CThostFtdcRspFutureSignOutField["RequestID"] = "int"
#交易ID
CThostFtdcRspFutureSignOutField["TID"] = "int"
#错误代码
CThostFtdcRspFutureSignOutField["ErrorID"] = "int"
#错误信息
CThostFtdcRspFutureSignOutField["ErrorMsg"] = "string"
structDict['CThostFtdcRspFutureSignOutField'] = CThostFtdcRspFutureSignOutField


#查询指定流水号的交易结果请求
CThostFtdcReqQueryTradeResultBySerialField = {}
#业务功能码
CThostFtdcReqQueryTradeResultBySerialField["TradeCode"] = "string"
#银行代码
CThostFtdcReqQueryTradeResultBySerialField["BankID"] = "string"
#银行分支机构代码
CThostFtdcReqQueryTradeResultBySerialField["BankBranchID"] = "string"
#期商代码
CThostFtdcReqQueryTradeResultBySerialField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcReqQueryTradeResultBySerialField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcReqQueryTradeResultBySerialField["TradeDate"] = "string"
#交易时间
CThostFtdcReqQueryTradeResultBySerialField["TradeTime"] = "string"
#银行流水号
CThostFtdcReqQueryTradeResultBySerialField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcReqQueryTradeResultBySerialField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcReqQueryTradeResultBySerialField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcReqQueryTradeResultBySerialField["LastFragment"] = "char"
#会话号
CThostFtdcReqQueryTradeResultBySerialField["SessionID"] = "int"
#流水号
CThostFtdcReqQueryTradeResultBySerialField["Reference"] = "int"
#本流水号发布者的机构类型
CThostFtdcReqQueryTradeResultBySerialField["RefrenceIssureType"] = "char"
#本流水号发布者机构编码
CThostFtdcReqQueryTradeResultBySerialField["RefrenceIssure"] = "string"
#客户姓名
CThostFtdcReqQueryTradeResultBySerialField["CustomerName"] = "string"
#证件类型
CThostFtdcReqQueryTradeResultBySerialField["IdCardType"] = "char"
#证件号码
CThostFtdcReqQueryTradeResultBySerialField["IdentifiedCardNo"] = "string"
#客户类型
CThostFtdcReqQueryTradeResultBySerialField["CustType"] = "char"
#银行帐号
CThostFtdcReqQueryTradeResultBySerialField["BankAccount"] = "string"
#银行密码
CThostFtdcReqQueryTradeResultBySerialField["BankPassWord"] = "string"
#投资者帐号
CThostFtdcReqQueryTradeResultBySerialField["AccountID"] = "string"
#期货密码
CThostFtdcReqQueryTradeResultBySerialField["Password"] = "string"
#币种代码
CThostFtdcReqQueryTradeResultBySerialField["CurrencyID"] = "string"
#转帐金额
CThostFtdcReqQueryTradeResultBySerialField["TradeAmount"] = "float"
#摘要
CThostFtdcReqQueryTradeResultBySerialField["Digest"] = "string"
#长客户姓名
CThostFtdcReqQueryTradeResultBySerialField["LongCustomerName"] = "string"
structDict['CThostFtdcReqQueryTradeResultBySerialField'] = CThostFtdcReqQueryTradeResultBySerialField


#查询指定流水号的交易结果响应
CThostFtdcRspQueryTradeResultBySerialField = {}
#业务功能码
CThostFtdcRspQueryTradeResultBySerialField["TradeCode"] = "string"
#银行代码
CThostFtdcRspQueryTradeResultBySerialField["BankID"] = "string"
#银行分支机构代码
CThostFtdcRspQueryTradeResultBySerialField["BankBranchID"] = "string"
#期商代码
CThostFtdcRspQueryTradeResultBySerialField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcRspQueryTradeResultBySerialField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcRspQueryTradeResultBySerialField["TradeDate"] = "string"
#交易时间
CThostFtdcRspQueryTradeResultBySerialField["TradeTime"] = "string"
#银行流水号
CThostFtdcRspQueryTradeResultBySerialField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcRspQueryTradeResultBySerialField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcRspQueryTradeResultBySerialField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcRspQueryTradeResultBySerialField["LastFragment"] = "char"
#会话号
CThostFtdcRspQueryTradeResultBySerialField["SessionID"] = "int"
#错误代码
CThostFtdcRspQueryTradeResultBySerialField["ErrorID"] = "int"
#错误信息
CThostFtdcRspQueryTradeResultBySerialField["ErrorMsg"] = "string"
#流水号
CThostFtdcRspQueryTradeResultBySerialField["Reference"] = "int"
#本流水号发布者的机构类型
CThostFtdcRspQueryTradeResultBySerialField["RefrenceIssureType"] = "char"
#本流水号发布者机构编码
CThostFtdcRspQueryTradeResultBySerialField["RefrenceIssure"] = "string"
#原始返回代码
CThostFtdcRspQueryTradeResultBySerialField["OriginReturnCode"] = "string"
#原始返回码描述
CThostFtdcRspQueryTradeResultBySerialField["OriginDescrInfoForReturnCode"] = "string"
#银行帐号
CThostFtdcRspQueryTradeResultBySerialField["BankAccount"] = "string"
#银行密码
CThostFtdcRspQueryTradeResultBySerialField["BankPassWord"] = "string"
#投资者帐号
CThostFtdcRspQueryTradeResultBySerialField["AccountID"] = "string"
#期货密码
CThostFtdcRspQueryTradeResultBySerialField["Password"] = "string"
#币种代码
CThostFtdcRspQueryTradeResultBySerialField["CurrencyID"] = "string"
#转帐金额
CThostFtdcRspQueryTradeResultBySerialField["TradeAmount"] = "float"
#摘要
CThostFtdcRspQueryTradeResultBySerialField["Digest"] = "string"
structDict['CThostFtdcRspQueryTradeResultBySerialField'] = CThostFtdcRspQueryTradeResultBySerialField


#日终文件就绪请求
CThostFtdcReqDayEndFileReadyField = {}
#业务功能码
CThostFtdcReqDayEndFileReadyField["TradeCode"] = "string"
#银行代码
CThostFtdcReqDayEndFileReadyField["BankID"] = "string"
#银行分支机构代码
CThostFtdcReqDayEndFileReadyField["BankBranchID"] = "string"
#期商代码
CThostFtdcReqDayEndFileReadyField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcReqDayEndFileReadyField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcReqDayEndFileReadyField["TradeDate"] = "string"
#交易时间
CThostFtdcReqDayEndFileReadyField["TradeTime"] = "string"
#银行流水号
CThostFtdcReqDayEndFileReadyField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcReqDayEndFileReadyField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcReqDayEndFileReadyField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcReqDayEndFileReadyField["LastFragment"] = "char"
#会话号
CThostFtdcReqDayEndFileReadyField["SessionID"] = "int"
#文件业务功能
CThostFtdcReqDayEndFileReadyField["FileBusinessCode"] = "char"
#摘要
CThostFtdcReqDayEndFileReadyField["Digest"] = "string"
structDict['CThostFtdcReqDayEndFileReadyField'] = CThostFtdcReqDayEndFileReadyField


#返回结果
CThostFtdcReturnResultField = {}
#返回代码
CThostFtdcReturnResultField["ReturnCode"] = "string"
#返回码描述
CThostFtdcReturnResultField["DescrInfoForReturnCode"] = "string"
structDict['CThostFtdcReturnResultField'] = CThostFtdcReturnResultField


#验证期货资金密码
CThostFtdcVerifyFuturePasswordField = {}
#业务功能码
CThostFtdcVerifyFuturePasswordField["TradeCode"] = "string"
#银行代码
CThostFtdcVerifyFuturePasswordField["BankID"] = "string"
#银行分支机构代码
CThostFtdcVerifyFuturePasswordField["BankBranchID"] = "string"
#期商代码
CThostFtdcVerifyFuturePasswordField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcVerifyFuturePasswordField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcVerifyFuturePasswordField["TradeDate"] = "string"
#交易时间
CThostFtdcVerifyFuturePasswordField["TradeTime"] = "string"
#银行流水号
CThostFtdcVerifyFuturePasswordField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcVerifyFuturePasswordField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcVerifyFuturePasswordField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcVerifyFuturePasswordField["LastFragment"] = "char"
#会话号
CThostFtdcVerifyFuturePasswordField["SessionID"] = "int"
#投资者帐号
CThostFtdcVerifyFuturePasswordField["AccountID"] = "string"
#期货密码
CThostFtdcVerifyFuturePasswordField["Password"] = "string"
#银行帐号
CThostFtdcVerifyFuturePasswordField["BankAccount"] = "string"
#银行密码
CThostFtdcVerifyFuturePasswordField["BankPassWord"] = "string"
#安装编号
CThostFtdcVerifyFuturePasswordField["InstallID"] = "int"
#交易ID
CThostFtdcVerifyFuturePasswordField["TID"] = "int"
#币种代码
CThostFtdcVerifyFuturePasswordField["CurrencyID"] = "string"
structDict['CThostFtdcVerifyFuturePasswordField'] = CThostFtdcVerifyFuturePasswordField


#验证客户信息
CThostFtdcVerifyCustInfoField = {}
#客户姓名
CThostFtdcVerifyCustInfoField["CustomerName"] = "string"
#证件类型
CThostFtdcVerifyCustInfoField["IdCardType"] = "char"
#证件号码
CThostFtdcVerifyCustInfoField["IdentifiedCardNo"] = "string"
#客户类型
CThostFtdcVerifyCustInfoField["CustType"] = "char"
#长客户姓名
CThostFtdcVerifyCustInfoField["LongCustomerName"] = "string"
structDict['CThostFtdcVerifyCustInfoField'] = CThostFtdcVerifyCustInfoField


#验证期货资金密码和客户信息
CThostFtdcVerifyFuturePasswordAndCustInfoField = {}
#客户姓名
CThostFtdcVerifyFuturePasswordAndCustInfoField["CustomerName"] = "string"
#证件类型
CThostFtdcVerifyFuturePasswordAndCustInfoField["IdCardType"] = "char"
#证件号码
CThostFtdcVerifyFuturePasswordAndCustInfoField["IdentifiedCardNo"] = "string"
#客户类型
CThostFtdcVerifyFuturePasswordAndCustInfoField["CustType"] = "char"
#投资者帐号
CThostFtdcVerifyFuturePasswordAndCustInfoField["AccountID"] = "string"
#期货密码
CThostFtdcVerifyFuturePasswordAndCustInfoField["Password"] = "string"
#币种代码
CThostFtdcVerifyFuturePasswordAndCustInfoField["CurrencyID"] = "string"
#长客户姓名
CThostFtdcVerifyFuturePasswordAndCustInfoField["LongCustomerName"] = "string"
structDict['CThostFtdcVerifyFuturePasswordAndCustInfoField'] = CThostFtdcVerifyFuturePasswordAndCustInfoField


#验证期货资金密码和客户信息
CThostFtdcDepositResultInformField = {}
#出入金流水号，该流水号为银期报盘返回的流水号
CThostFtdcDepositResultInformField["DepositSeqNo"] = "string"
#经纪公司代码
CThostFtdcDepositResultInformField["BrokerID"] = "string"
#投资者代码
CThostFtdcDepositResultInformField["InvestorID"] = "string"
#入金金额
CThostFtdcDepositResultInformField["Deposit"] = "float"
#请求编号
CThostFtdcDepositResultInformField["RequestID"] = "int"
#返回代码
CThostFtdcDepositResultInformField["ReturnCode"] = "string"
#返回码描述
CThostFtdcDepositResultInformField["DescrInfoForReturnCode"] = "string"
structDict['CThostFtdcDepositResultInformField'] = CThostFtdcDepositResultInformField


#交易核心向银期报盘发出密钥同步请求
CThostFtdcReqSyncKeyField = {}
#业务功能码
CThostFtdcReqSyncKeyField["TradeCode"] = "string"
#银行代码
CThostFtdcReqSyncKeyField["BankID"] = "string"
#银行分支机构代码
CThostFtdcReqSyncKeyField["BankBranchID"] = "string"
#期商代码
CThostFtdcReqSyncKeyField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcReqSyncKeyField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcReqSyncKeyField["TradeDate"] = "string"
#交易时间
CThostFtdcReqSyncKeyField["TradeTime"] = "string"
#银行流水号
CThostFtdcReqSyncKeyField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcReqSyncKeyField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcReqSyncKeyField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcReqSyncKeyField["LastFragment"] = "char"
#会话号
CThostFtdcReqSyncKeyField["SessionID"] = "int"
#安装编号
CThostFtdcReqSyncKeyField["InstallID"] = "int"
#用户标识
CThostFtdcReqSyncKeyField["UserID"] = "string"
#交易核心给银期报盘的消息
CThostFtdcReqSyncKeyField["Message"] = "string"
#渠道标志
CThostFtdcReqSyncKeyField["DeviceID"] = "string"
#期货公司银行编码
CThostFtdcReqSyncKeyField["BrokerIDByBank"] = "string"
#交易柜员
CThostFtdcReqSyncKeyField["OperNo"] = "string"
#请求编号
CThostFtdcReqSyncKeyField["RequestID"] = "int"
#交易ID
CThostFtdcReqSyncKeyField["TID"] = "int"
structDict['CThostFtdcReqSyncKeyField'] = CThostFtdcReqSyncKeyField


#交易核心向银期报盘发出密钥同步响应
CThostFtdcRspSyncKeyField = {}
#业务功能码
CThostFtdcRspSyncKeyField["TradeCode"] = "string"
#银行代码
CThostFtdcRspSyncKeyField["BankID"] = "string"
#银行分支机构代码
CThostFtdcRspSyncKeyField["BankBranchID"] = "string"
#期商代码
CThostFtdcRspSyncKeyField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcRspSyncKeyField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcRspSyncKeyField["TradeDate"] = "string"
#交易时间
CThostFtdcRspSyncKeyField["TradeTime"] = "string"
#银行流水号
CThostFtdcRspSyncKeyField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcRspSyncKeyField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcRspSyncKeyField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcRspSyncKeyField["LastFragment"] = "char"
#会话号
CThostFtdcRspSyncKeyField["SessionID"] = "int"
#安装编号
CThostFtdcRspSyncKeyField["InstallID"] = "int"
#用户标识
CThostFtdcRspSyncKeyField["UserID"] = "string"
#交易核心给银期报盘的消息
CThostFtdcRspSyncKeyField["Message"] = "string"
#渠道标志
CThostFtdcRspSyncKeyField["DeviceID"] = "string"
#期货公司银行编码
CThostFtdcRspSyncKeyField["BrokerIDByBank"] = "string"
#交易柜员
CThostFtdcRspSyncKeyField["OperNo"] = "string"
#请求编号
CThostFtdcRspSyncKeyField["RequestID"] = "int"
#交易ID
CThostFtdcRspSyncKeyField["TID"] = "int"
#错误代码
CThostFtdcRspSyncKeyField["ErrorID"] = "int"
#错误信息
CThostFtdcRspSyncKeyField["ErrorMsg"] = "string"
structDict['CThostFtdcRspSyncKeyField'] = CThostFtdcRspSyncKeyField


#查询账户信息通知
CThostFtdcNotifyQueryAccountField = {}
#业务功能码
CThostFtdcNotifyQueryAccountField["TradeCode"] = "string"
#银行代码
CThostFtdcNotifyQueryAccountField["BankID"] = "string"
#银行分支机构代码
CThostFtdcNotifyQueryAccountField["BankBranchID"] = "string"
#期商代码
CThostFtdcNotifyQueryAccountField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcNotifyQueryAccountField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcNotifyQueryAccountField["TradeDate"] = "string"
#交易时间
CThostFtdcNotifyQueryAccountField["TradeTime"] = "string"
#银行流水号
CThostFtdcNotifyQueryAccountField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcNotifyQueryAccountField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcNotifyQueryAccountField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcNotifyQueryAccountField["LastFragment"] = "char"
#会话号
CThostFtdcNotifyQueryAccountField["SessionID"] = "int"
#客户姓名
CThostFtdcNotifyQueryAccountField["CustomerName"] = "string"
#证件类型
CThostFtdcNotifyQueryAccountField["IdCardType"] = "char"
#证件号码
CThostFtdcNotifyQueryAccountField["IdentifiedCardNo"] = "string"
#客户类型
CThostFtdcNotifyQueryAccountField["CustType"] = "char"
#银行帐号
CThostFtdcNotifyQueryAccountField["BankAccount"] = "string"
#银行密码
CThostFtdcNotifyQueryAccountField["BankPassWord"] = "string"
#投资者帐号
CThostFtdcNotifyQueryAccountField["AccountID"] = "string"
#期货密码
CThostFtdcNotifyQueryAccountField["Password"] = "string"
#期货公司流水号
CThostFtdcNotifyQueryAccountField["FutureSerial"] = "int"
#安装编号
CThostFtdcNotifyQueryAccountField["InstallID"] = "int"
#用户标识
CThostFtdcNotifyQueryAccountField["UserID"] = "string"
#验证客户证件号码标志
CThostFtdcNotifyQueryAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcNotifyQueryAccountField["CurrencyID"] = "string"
#摘要
CThostFtdcNotifyQueryAccountField["Digest"] = "string"
#银行帐号类型
CThostFtdcNotifyQueryAccountField["BankAccType"] = "char"
#渠道标志
CThostFtdcNotifyQueryAccountField["DeviceID"] = "string"
#期货单位帐号类型
CThostFtdcNotifyQueryAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CThostFtdcNotifyQueryAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CThostFtdcNotifyQueryAccountField["BankSecuAcc"] = "string"
#银行密码标志
CThostFtdcNotifyQueryAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CThostFtdcNotifyQueryAccountField["SecuPwdFlag"] = "char"
#交易柜员
CThostFtdcNotifyQueryAccountField["OperNo"] = "string"
#请求编号
CThostFtdcNotifyQueryAccountField["RequestID"] = "int"
#交易ID
CThostFtdcNotifyQueryAccountField["TID"] = "int"
#银行可用金额
CThostFtdcNotifyQueryAccountField["BankUseAmount"] = "float"
#银行可取金额
CThostFtdcNotifyQueryAccountField["BankFetchAmount"] = "float"
#错误代码
CThostFtdcNotifyQueryAccountField["ErrorID"] = "int"
#错误信息
CThostFtdcNotifyQueryAccountField["ErrorMsg"] = "string"
#长客户姓名
CThostFtdcNotifyQueryAccountField["LongCustomerName"] = "string"
structDict['CThostFtdcNotifyQueryAccountField'] = CThostFtdcNotifyQueryAccountField


#银期转账交易流水表
CThostFtdcTransferSerialField = {}
#平台流水号
CThostFtdcTransferSerialField["PlateSerial"] = "int"
#交易发起方日期
CThostFtdcTransferSerialField["TradeDate"] = "string"
#交易日期
CThostFtdcTransferSerialField["TradingDay"] = "string"
#交易时间
CThostFtdcTransferSerialField["TradeTime"] = "string"
#交易代码
CThostFtdcTransferSerialField["TradeCode"] = "string"
#会话编号
CThostFtdcTransferSerialField["SessionID"] = "int"
#银行编码
CThostFtdcTransferSerialField["BankID"] = "string"
#银行分支机构编码
CThostFtdcTransferSerialField["BankBranchID"] = "string"
#银行帐号类型
CThostFtdcTransferSerialField["BankAccType"] = "char"
#银行帐号
CThostFtdcTransferSerialField["BankAccount"] = "string"
#银行流水号
CThostFtdcTransferSerialField["BankSerial"] = "string"
#期货公司编码
CThostFtdcTransferSerialField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcTransferSerialField["BrokerBranchID"] = "string"
#期货公司帐号类型
CThostFtdcTransferSerialField["FutureAccType"] = "char"
#投资者帐号
CThostFtdcTransferSerialField["AccountID"] = "string"
#投资者代码
CThostFtdcTransferSerialField["InvestorID"] = "string"
#期货公司流水号
CThostFtdcTransferSerialField["FutureSerial"] = "int"
#证件类型
CThostFtdcTransferSerialField["IdCardType"] = "char"
#证件号码
CThostFtdcTransferSerialField["IdentifiedCardNo"] = "string"
#币种代码
CThostFtdcTransferSerialField["CurrencyID"] = "string"
#交易金额
CThostFtdcTransferSerialField["TradeAmount"] = "float"
#应收客户费用
CThostFtdcTransferSerialField["CustFee"] = "float"
#应收期货公司费用
CThostFtdcTransferSerialField["BrokerFee"] = "float"
#有效标志
CThostFtdcTransferSerialField["AvailabilityFlag"] = "char"
#操作员
CThostFtdcTransferSerialField["OperatorCode"] = "string"
#新银行帐号
CThostFtdcTransferSerialField["BankNewAccount"] = "string"
#错误代码
CThostFtdcTransferSerialField["ErrorID"] = "int"
#错误信息
CThostFtdcTransferSerialField["ErrorMsg"] = "string"
structDict['CThostFtdcTransferSerialField'] = CThostFtdcTransferSerialField


#请求查询转帐流水
CThostFtdcQryTransferSerialField = {}
#经纪公司代码
CThostFtdcQryTransferSerialField["BrokerID"] = "string"
#投资者帐号
CThostFtdcQryTransferSerialField["AccountID"] = "string"
#银行编码
CThostFtdcQryTransferSerialField["BankID"] = "string"
#币种代码
CThostFtdcQryTransferSerialField["CurrencyID"] = "string"
structDict['CThostFtdcQryTransferSerialField'] = CThostFtdcQryTransferSerialField


#期商签到通知
CThostFtdcNotifyFutureSignInField = {}
#业务功能码
CThostFtdcNotifyFutureSignInField["TradeCode"] = "string"
#银行代码
CThostFtdcNotifyFutureSignInField["BankID"] = "string"
#银行分支机构代码
CThostFtdcNotifyFutureSignInField["BankBranchID"] = "string"
#期商代码
CThostFtdcNotifyFutureSignInField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcNotifyFutureSignInField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcNotifyFutureSignInField["TradeDate"] = "string"
#交易时间
CThostFtdcNotifyFutureSignInField["TradeTime"] = "string"
#银行流水号
CThostFtdcNotifyFutureSignInField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcNotifyFutureSignInField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcNotifyFutureSignInField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcNotifyFutureSignInField["LastFragment"] = "char"
#会话号
CThostFtdcNotifyFutureSignInField["SessionID"] = "int"
#安装编号
CThostFtdcNotifyFutureSignInField["InstallID"] = "int"
#用户标识
CThostFtdcNotifyFutureSignInField["UserID"] = "string"
#摘要
CThostFtdcNotifyFutureSignInField["Digest"] = "string"
#币种代码
CThostFtdcNotifyFutureSignInField["CurrencyID"] = "string"
#渠道标志
CThostFtdcNotifyFutureSignInField["DeviceID"] = "string"
#期货公司银行编码
CThostFtdcNotifyFutureSignInField["BrokerIDByBank"] = "string"
#交易柜员
CThostFtdcNotifyFutureSignInField["OperNo"] = "string"
#请求编号
CThostFtdcNotifyFutureSignInField["RequestID"] = "int"
#交易ID
CThostFtdcNotifyFutureSignInField["TID"] = "int"
#错误代码
CThostFtdcNotifyFutureSignInField["ErrorID"] = "int"
#错误信息
CThostFtdcNotifyFutureSignInField["ErrorMsg"] = "string"
#PIN密钥
CThostFtdcNotifyFutureSignInField["PinKey"] = "string"
#MAC密钥
CThostFtdcNotifyFutureSignInField["MacKey"] = "string"
structDict['CThostFtdcNotifyFutureSignInField'] = CThostFtdcNotifyFutureSignInField


#期商签退通知
CThostFtdcNotifyFutureSignOutField = {}
#业务功能码
CThostFtdcNotifyFutureSignOutField["TradeCode"] = "string"
#银行代码
CThostFtdcNotifyFutureSignOutField["BankID"] = "string"
#银行分支机构代码
CThostFtdcNotifyFutureSignOutField["BankBranchID"] = "string"
#期商代码
CThostFtdcNotifyFutureSignOutField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcNotifyFutureSignOutField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcNotifyFutureSignOutField["TradeDate"] = "string"
#交易时间
CThostFtdcNotifyFutureSignOutField["TradeTime"] = "string"
#银行流水号
CThostFtdcNotifyFutureSignOutField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcNotifyFutureSignOutField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcNotifyFutureSignOutField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcNotifyFutureSignOutField["LastFragment"] = "char"
#会话号
CThostFtdcNotifyFutureSignOutField["SessionID"] = "int"
#安装编号
CThostFtdcNotifyFutureSignOutField["InstallID"] = "int"
#用户标识
CThostFtdcNotifyFutureSignOutField["UserID"] = "string"
#摘要
CThostFtdcNotifyFutureSignOutField["Digest"] = "string"
#币种代码
CThostFtdcNotifyFutureSignOutField["CurrencyID"] = "string"
#渠道标志
CThostFtdcNotifyFutureSignOutField["DeviceID"] = "string"
#期货公司银行编码
CThostFtdcNotifyFutureSignOutField["BrokerIDByBank"] = "string"
#交易柜员
CThostFtdcNotifyFutureSignOutField["OperNo"] = "string"
#请求编号
CThostFtdcNotifyFutureSignOutField["RequestID"] = "int"
#交易ID
CThostFtdcNotifyFutureSignOutField["TID"] = "int"
#错误代码
CThostFtdcNotifyFutureSignOutField["ErrorID"] = "int"
#错误信息
CThostFtdcNotifyFutureSignOutField["ErrorMsg"] = "string"
structDict['CThostFtdcNotifyFutureSignOutField'] = CThostFtdcNotifyFutureSignOutField


#交易核心向银期报盘发出密钥同步处理结果的通知
CThostFtdcNotifySyncKeyField = {}
#业务功能码
CThostFtdcNotifySyncKeyField["TradeCode"] = "string"
#银行代码
CThostFtdcNotifySyncKeyField["BankID"] = "string"
#银行分支机构代码
CThostFtdcNotifySyncKeyField["BankBranchID"] = "string"
#期商代码
CThostFtdcNotifySyncKeyField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcNotifySyncKeyField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcNotifySyncKeyField["TradeDate"] = "string"
#交易时间
CThostFtdcNotifySyncKeyField["TradeTime"] = "string"
#银行流水号
CThostFtdcNotifySyncKeyField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcNotifySyncKeyField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcNotifySyncKeyField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcNotifySyncKeyField["LastFragment"] = "char"
#会话号
CThostFtdcNotifySyncKeyField["SessionID"] = "int"
#安装编号
CThostFtdcNotifySyncKeyField["InstallID"] = "int"
#用户标识
CThostFtdcNotifySyncKeyField["UserID"] = "string"
#交易核心给银期报盘的消息
CThostFtdcNotifySyncKeyField["Message"] = "string"
#渠道标志
CThostFtdcNotifySyncKeyField["DeviceID"] = "string"
#期货公司银行编码
CThostFtdcNotifySyncKeyField["BrokerIDByBank"] = "string"
#交易柜员
CThostFtdcNotifySyncKeyField["OperNo"] = "string"
#请求编号
CThostFtdcNotifySyncKeyField["RequestID"] = "int"
#交易ID
CThostFtdcNotifySyncKeyField["TID"] = "int"
#错误代码
CThostFtdcNotifySyncKeyField["ErrorID"] = "int"
#错误信息
CThostFtdcNotifySyncKeyField["ErrorMsg"] = "string"
structDict['CThostFtdcNotifySyncKeyField'] = CThostFtdcNotifySyncKeyField


#请求查询银期签约关系
CThostFtdcQryAccountregisterField = {}
#经纪公司代码
CThostFtdcQryAccountregisterField["BrokerID"] = "string"
#投资者帐号
CThostFtdcQryAccountregisterField["AccountID"] = "string"
#银行编码
CThostFtdcQryAccountregisterField["BankID"] = "string"
#银行分支机构编码
CThostFtdcQryAccountregisterField["BankBranchID"] = "string"
#币种代码
CThostFtdcQryAccountregisterField["CurrencyID"] = "string"
structDict['CThostFtdcQryAccountregisterField'] = CThostFtdcQryAccountregisterField


#客户开销户信息表
CThostFtdcAccountregisterField = {}
#交易日期
CThostFtdcAccountregisterField["TradeDay"] = "string"
#银行编码
CThostFtdcAccountregisterField["BankID"] = "string"
#银行分支机构编码
CThostFtdcAccountregisterField["BankBranchID"] = "string"
#银行帐号
CThostFtdcAccountregisterField["BankAccount"] = "string"
#期货公司编码
CThostFtdcAccountregisterField["BrokerID"] = "string"
#期货公司分支机构编码
CThostFtdcAccountregisterField["BrokerBranchID"] = "string"
#投资者帐号
CThostFtdcAccountregisterField["AccountID"] = "string"
#证件类型
CThostFtdcAccountregisterField["IdCardType"] = "char"
#证件号码
CThostFtdcAccountregisterField["IdentifiedCardNo"] = "string"
#客户姓名
CThostFtdcAccountregisterField["CustomerName"] = "string"
#币种代码
CThostFtdcAccountregisterField["CurrencyID"] = "string"
#开销户类别
CThostFtdcAccountregisterField["OpenOrDestroy"] = "char"
#签约日期
CThostFtdcAccountregisterField["RegDate"] = "string"
#解约日期
CThostFtdcAccountregisterField["OutDate"] = "string"
#交易ID
CThostFtdcAccountregisterField["TID"] = "int"
#客户类型
CThostFtdcAccountregisterField["CustType"] = "char"
#银行帐号类型
CThostFtdcAccountregisterField["BankAccType"] = "char"
#长客户姓名
CThostFtdcAccountregisterField["LongCustomerName"] = "string"
structDict['CThostFtdcAccountregisterField'] = CThostFtdcAccountregisterField


#银期开户信息
CThostFtdcOpenAccountField = {}
#业务功能码
CThostFtdcOpenAccountField["TradeCode"] = "string"
#银行代码
CThostFtdcOpenAccountField["BankID"] = "string"
#银行分支机构代码
CThostFtdcOpenAccountField["BankBranchID"] = "string"
#期商代码
CThostFtdcOpenAccountField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcOpenAccountField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcOpenAccountField["TradeDate"] = "string"
#交易时间
CThostFtdcOpenAccountField["TradeTime"] = "string"
#银行流水号
CThostFtdcOpenAccountField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcOpenAccountField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcOpenAccountField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcOpenAccountField["LastFragment"] = "char"
#会话号
CThostFtdcOpenAccountField["SessionID"] = "int"
#客户姓名
CThostFtdcOpenAccountField["CustomerName"] = "string"
#证件类型
CThostFtdcOpenAccountField["IdCardType"] = "char"
#证件号码
CThostFtdcOpenAccountField["IdentifiedCardNo"] = "string"
#性别
CThostFtdcOpenAccountField["Gender"] = "char"
#国家代码
CThostFtdcOpenAccountField["CountryCode"] = "string"
#客户类型
CThostFtdcOpenAccountField["CustType"] = "char"
#地址
CThostFtdcOpenAccountField["Address"] = "string"
#邮编
CThostFtdcOpenAccountField["ZipCode"] = "string"
#电话号码
CThostFtdcOpenAccountField["Telephone"] = "string"
#手机
CThostFtdcOpenAccountField["MobilePhone"] = "string"
#传真
CThostFtdcOpenAccountField["Fax"] = "string"
#电子邮件
CThostFtdcOpenAccountField["EMail"] = "string"
#资金账户状态
CThostFtdcOpenAccountField["MoneyAccountStatus"] = "char"
#银行帐号
CThostFtdcOpenAccountField["BankAccount"] = "string"
#银行密码
CThostFtdcOpenAccountField["BankPassWord"] = "string"
#投资者帐号
CThostFtdcOpenAccountField["AccountID"] = "string"
#期货密码
CThostFtdcOpenAccountField["Password"] = "string"
#安装编号
CThostFtdcOpenAccountField["InstallID"] = "int"
#验证客户证件号码标志
CThostFtdcOpenAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcOpenAccountField["CurrencyID"] = "string"
#汇钞标志
CThostFtdcOpenAccountField["CashExchangeCode"] = "char"
#摘要
CThostFtdcOpenAccountField["Digest"] = "string"
#银行帐号类型
CThostFtdcOpenAccountField["BankAccType"] = "char"
#渠道标志
CThostFtdcOpenAccountField["DeviceID"] = "string"
#期货单位帐号类型
CThostFtdcOpenAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CThostFtdcOpenAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CThostFtdcOpenAccountField["BankSecuAcc"] = "string"
#银行密码标志
CThostFtdcOpenAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CThostFtdcOpenAccountField["SecuPwdFlag"] = "char"
#交易柜员
CThostFtdcOpenAccountField["OperNo"] = "string"
#交易ID
CThostFtdcOpenAccountField["TID"] = "int"
#用户标识
CThostFtdcOpenAccountField["UserID"] = "string"
#错误代码
CThostFtdcOpenAccountField["ErrorID"] = "int"
#错误信息
CThostFtdcOpenAccountField["ErrorMsg"] = "string"
#长客户姓名
CThostFtdcOpenAccountField["LongCustomerName"] = "string"
structDict['CThostFtdcOpenAccountField'] = CThostFtdcOpenAccountField


#银期销户信息
CThostFtdcCancelAccountField = {}
#业务功能码
CThostFtdcCancelAccountField["TradeCode"] = "string"
#银行代码
CThostFtdcCancelAccountField["BankID"] = "string"
#银行分支机构代码
CThostFtdcCancelAccountField["BankBranchID"] = "string"
#期商代码
CThostFtdcCancelAccountField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcCancelAccountField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcCancelAccountField["TradeDate"] = "string"
#交易时间
CThostFtdcCancelAccountField["TradeTime"] = "string"
#银行流水号
CThostFtdcCancelAccountField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcCancelAccountField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcCancelAccountField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcCancelAccountField["LastFragment"] = "char"
#会话号
CThostFtdcCancelAccountField["SessionID"] = "int"
#客户姓名
CThostFtdcCancelAccountField["CustomerName"] = "string"
#证件类型
CThostFtdcCancelAccountField["IdCardType"] = "char"
#证件号码
CThostFtdcCancelAccountField["IdentifiedCardNo"] = "string"
#性别
CThostFtdcCancelAccountField["Gender"] = "char"
#国家代码
CThostFtdcCancelAccountField["CountryCode"] = "string"
#客户类型
CThostFtdcCancelAccountField["CustType"] = "char"
#地址
CThostFtdcCancelAccountField["Address"] = "string"
#邮编
CThostFtdcCancelAccountField["ZipCode"] = "string"
#电话号码
CThostFtdcCancelAccountField["Telephone"] = "string"
#手机
CThostFtdcCancelAccountField["MobilePhone"] = "string"
#传真
CThostFtdcCancelAccountField["Fax"] = "string"
#电子邮件
CThostFtdcCancelAccountField["EMail"] = "string"
#资金账户状态
CThostFtdcCancelAccountField["MoneyAccountStatus"] = "char"
#银行帐号
CThostFtdcCancelAccountField["BankAccount"] = "string"
#银行密码
CThostFtdcCancelAccountField["BankPassWord"] = "string"
#投资者帐号
CThostFtdcCancelAccountField["AccountID"] = "string"
#期货密码
CThostFtdcCancelAccountField["Password"] = "string"
#安装编号
CThostFtdcCancelAccountField["InstallID"] = "int"
#验证客户证件号码标志
CThostFtdcCancelAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcCancelAccountField["CurrencyID"] = "string"
#汇钞标志
CThostFtdcCancelAccountField["CashExchangeCode"] = "char"
#摘要
CThostFtdcCancelAccountField["Digest"] = "string"
#银行帐号类型
CThostFtdcCancelAccountField["BankAccType"] = "char"
#渠道标志
CThostFtdcCancelAccountField["DeviceID"] = "string"
#期货单位帐号类型
CThostFtdcCancelAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CThostFtdcCancelAccountField["BrokerIDByBank"] = "string"
#期货单位帐号
CThostFtdcCancelAccountField["BankSecuAcc"] = "string"
#银行密码标志
CThostFtdcCancelAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CThostFtdcCancelAccountField["SecuPwdFlag"] = "char"
#交易柜员
CThostFtdcCancelAccountField["OperNo"] = "string"
#交易ID
CThostFtdcCancelAccountField["TID"] = "int"
#用户标识
CThostFtdcCancelAccountField["UserID"] = "string"
#错误代码
CThostFtdcCancelAccountField["ErrorID"] = "int"
#错误信息
CThostFtdcCancelAccountField["ErrorMsg"] = "string"
#长客户姓名
CThostFtdcCancelAccountField["LongCustomerName"] = "string"
structDict['CThostFtdcCancelAccountField'] = CThostFtdcCancelAccountField


#银期变更银行账号信息
CThostFtdcChangeAccountField = {}
#业务功能码
CThostFtdcChangeAccountField["TradeCode"] = "string"
#银行代码
CThostFtdcChangeAccountField["BankID"] = "string"
#银行分支机构代码
CThostFtdcChangeAccountField["BankBranchID"] = "string"
#期商代码
CThostFtdcChangeAccountField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcChangeAccountField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcChangeAccountField["TradeDate"] = "string"
#交易时间
CThostFtdcChangeAccountField["TradeTime"] = "string"
#银行流水号
CThostFtdcChangeAccountField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcChangeAccountField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcChangeAccountField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcChangeAccountField["LastFragment"] = "char"
#会话号
CThostFtdcChangeAccountField["SessionID"] = "int"
#客户姓名
CThostFtdcChangeAccountField["CustomerName"] = "string"
#证件类型
CThostFtdcChangeAccountField["IdCardType"] = "char"
#证件号码
CThostFtdcChangeAccountField["IdentifiedCardNo"] = "string"
#性别
CThostFtdcChangeAccountField["Gender"] = "char"
#国家代码
CThostFtdcChangeAccountField["CountryCode"] = "string"
#客户类型
CThostFtdcChangeAccountField["CustType"] = "char"
#地址
CThostFtdcChangeAccountField["Address"] = "string"
#邮编
CThostFtdcChangeAccountField["ZipCode"] = "string"
#电话号码
CThostFtdcChangeAccountField["Telephone"] = "string"
#手机
CThostFtdcChangeAccountField["MobilePhone"] = "string"
#传真
CThostFtdcChangeAccountField["Fax"] = "string"
#电子邮件
CThostFtdcChangeAccountField["EMail"] = "string"
#资金账户状态
CThostFtdcChangeAccountField["MoneyAccountStatus"] = "char"
#银行帐号
CThostFtdcChangeAccountField["BankAccount"] = "string"
#银行密码
CThostFtdcChangeAccountField["BankPassWord"] = "string"
#新银行帐号
CThostFtdcChangeAccountField["NewBankAccount"] = "string"
#新银行密码
CThostFtdcChangeAccountField["NewBankPassWord"] = "string"
#投资者帐号
CThostFtdcChangeAccountField["AccountID"] = "string"
#期货密码
CThostFtdcChangeAccountField["Password"] = "string"
#银行帐号类型
CThostFtdcChangeAccountField["BankAccType"] = "char"
#安装编号
CThostFtdcChangeAccountField["InstallID"] = "int"
#验证客户证件号码标志
CThostFtdcChangeAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcChangeAccountField["CurrencyID"] = "string"
#期货公司银行编码
CThostFtdcChangeAccountField["BrokerIDByBank"] = "string"
#银行密码标志
CThostFtdcChangeAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CThostFtdcChangeAccountField["SecuPwdFlag"] = "char"
#交易ID
CThostFtdcChangeAccountField["TID"] = "int"
#摘要
CThostFtdcChangeAccountField["Digest"] = "string"
#错误代码
CThostFtdcChangeAccountField["ErrorID"] = "int"
#错误信息
CThostFtdcChangeAccountField["ErrorMsg"] = "string"
#长客户姓名
CThostFtdcChangeAccountField["LongCustomerName"] = "string"
structDict['CThostFtdcChangeAccountField'] = CThostFtdcChangeAccountField


#二级代理操作员银期权限
CThostFtdcSecAgentACIDMapField = {}
#经纪公司代码
CThostFtdcSecAgentACIDMapField["BrokerID"] = "string"
#用户代码
CThostFtdcSecAgentACIDMapField["UserID"] = "string"
#资金账户
CThostFtdcSecAgentACIDMapField["AccountID"] = "string"
#币种
CThostFtdcSecAgentACIDMapField["CurrencyID"] = "string"
#境外中介机构资金帐号
CThostFtdcSecAgentACIDMapField["BrokerSecAgentID"] = "string"
structDict['CThostFtdcSecAgentACIDMapField'] = CThostFtdcSecAgentACIDMapField


#二级代理操作员银期权限查询
CThostFtdcQrySecAgentACIDMapField = {}
#经纪公司代码
CThostFtdcQrySecAgentACIDMapField["BrokerID"] = "string"
#用户代码
CThostFtdcQrySecAgentACIDMapField["UserID"] = "string"
#资金账户
CThostFtdcQrySecAgentACIDMapField["AccountID"] = "string"
#币种
CThostFtdcQrySecAgentACIDMapField["CurrencyID"] = "string"
structDict['CThostFtdcQrySecAgentACIDMapField'] = CThostFtdcQrySecAgentACIDMapField


#灾备中心交易权限
CThostFtdcUserRightsAssignField = {}
#应用单元代码
CThostFtdcUserRightsAssignField["BrokerID"] = "string"
#用户代码
CThostFtdcUserRightsAssignField["UserID"] = "string"
#交易中心代码
CThostFtdcUserRightsAssignField["DRIdentityID"] = "int"
structDict['CThostFtdcUserRightsAssignField'] = CThostFtdcUserRightsAssignField


#经济公司是否有在本标示的交易权限
CThostFtdcBrokerUserRightAssignField = {}
#应用单元代码
CThostFtdcBrokerUserRightAssignField["BrokerID"] = "string"
#交易中心代码
CThostFtdcBrokerUserRightAssignField["DRIdentityID"] = "int"
#能否交易
CThostFtdcBrokerUserRightAssignField["Tradeable"] = "int"
structDict['CThostFtdcBrokerUserRightAssignField'] = CThostFtdcBrokerUserRightAssignField


#灾备交易转换报文
CThostFtdcDRTransferField = {}
#原交易中心代码
CThostFtdcDRTransferField["OrigDRIdentityID"] = "int"
#目标交易中心代码
CThostFtdcDRTransferField["DestDRIdentityID"] = "int"
#原应用单元代码
CThostFtdcDRTransferField["OrigBrokerID"] = "string"
#目标易用单元代码
CThostFtdcDRTransferField["DestBrokerID"] = "string"
structDict['CThostFtdcDRTransferField'] = CThostFtdcDRTransferField


#Fens用户信息
CThostFtdcFensUserInfoField = {}
#经纪公司代码
CThostFtdcFensUserInfoField["BrokerID"] = "string"
#用户代码
CThostFtdcFensUserInfoField["UserID"] = "string"
#登录模式
CThostFtdcFensUserInfoField["LoginMode"] = "char"
structDict['CThostFtdcFensUserInfoField'] = CThostFtdcFensUserInfoField


#当前银期所属交易中心
CThostFtdcCurrTransferIdentityField = {}
#交易中心代码
CThostFtdcCurrTransferIdentityField["IdentityID"] = "int"
structDict['CThostFtdcCurrTransferIdentityField'] = CThostFtdcCurrTransferIdentityField


#禁止登录用户
CThostFtdcLoginForbiddenUserField = {}
#经纪公司代码
CThostFtdcLoginForbiddenUserField["BrokerID"] = "string"
#用户代码
CThostFtdcLoginForbiddenUserField["UserID"] = "string"
#IP地址
CThostFtdcLoginForbiddenUserField["IPAddress"] = "string"
structDict['CThostFtdcLoginForbiddenUserField'] = CThostFtdcLoginForbiddenUserField


#查询禁止登录用户
CThostFtdcQryLoginForbiddenUserField = {}
#经纪公司代码
CThostFtdcQryLoginForbiddenUserField["BrokerID"] = "string"
#用户代码
CThostFtdcQryLoginForbiddenUserField["UserID"] = "string"
structDict['CThostFtdcQryLoginForbiddenUserField'] = CThostFtdcQryLoginForbiddenUserField


#UDP组播组信息
CThostFtdcMulticastGroupInfoField = {}
#组播组IP地址
CThostFtdcMulticastGroupInfoField["GroupIP"] = "string"
#组播组IP端口
CThostFtdcMulticastGroupInfoField["GroupPort"] = "int"
#源地址
CThostFtdcMulticastGroupInfoField["SourceIP"] = "string"
structDict['CThostFtdcMulticastGroupInfoField'] = CThostFtdcMulticastGroupInfoField


#资金账户基本准备金
CThostFtdcTradingAccountReserveField = {}
#经纪公司代码
CThostFtdcTradingAccountReserveField["BrokerID"] = "string"
#投资者帐号
CThostFtdcTradingAccountReserveField["AccountID"] = "string"
#基本准备金
CThostFtdcTradingAccountReserveField["Reserve"] = "float"
#币种代码
CThostFtdcTradingAccountReserveField["CurrencyID"] = "string"
structDict['CThostFtdcTradingAccountReserveField'] = CThostFtdcTradingAccountReserveField


#查询禁止登录IP
CThostFtdcQryLoginForbiddenIPField = {}
#IP地址
CThostFtdcQryLoginForbiddenIPField["IPAddress"] = "string"
structDict['CThostFtdcQryLoginForbiddenIPField'] = CThostFtdcQryLoginForbiddenIPField


#查询IP列表
CThostFtdcQryIPListField = {}
#IP地址
CThostFtdcQryIPListField["IPAddress"] = "string"
structDict['CThostFtdcQryIPListField'] = CThostFtdcQryIPListField


#查询用户下单权限分配表
CThostFtdcQryUserRightsAssignField = {}
#应用单元代码
CThostFtdcQryUserRightsAssignField["BrokerID"] = "string"
#用户代码
CThostFtdcQryUserRightsAssignField["UserID"] = "string"
structDict['CThostFtdcQryUserRightsAssignField'] = CThostFtdcQryUserRightsAssignField


#银期预约开户确认请求
CThostFtdcReserveOpenAccountConfirmField = {}
#业务功能码
CThostFtdcReserveOpenAccountConfirmField["TradeCode"] = "string"
#银行代码
CThostFtdcReserveOpenAccountConfirmField["BankID"] = "string"
#银行分支机构代码
CThostFtdcReserveOpenAccountConfirmField["BankBranchID"] = "string"
#期商代码
CThostFtdcReserveOpenAccountConfirmField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcReserveOpenAccountConfirmField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcReserveOpenAccountConfirmField["TradeDate"] = "string"
#交易时间
CThostFtdcReserveOpenAccountConfirmField["TradeTime"] = "string"
#银行流水号
CThostFtdcReserveOpenAccountConfirmField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcReserveOpenAccountConfirmField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcReserveOpenAccountConfirmField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcReserveOpenAccountConfirmField["LastFragment"] = "char"
#会话号
CThostFtdcReserveOpenAccountConfirmField["SessionID"] = "int"
#客户姓名
CThostFtdcReserveOpenAccountConfirmField["CustomerName"] = "string"
#证件类型
CThostFtdcReserveOpenAccountConfirmField["IdCardType"] = "char"
#证件号码
CThostFtdcReserveOpenAccountConfirmField["IdentifiedCardNo"] = "string"
#性别
CThostFtdcReserveOpenAccountConfirmField["Gender"] = "char"
#国家代码
CThostFtdcReserveOpenAccountConfirmField["CountryCode"] = "string"
#客户类型
CThostFtdcReserveOpenAccountConfirmField["CustType"] = "char"
#地址
CThostFtdcReserveOpenAccountConfirmField["Address"] = "string"
#邮编
CThostFtdcReserveOpenAccountConfirmField["ZipCode"] = "string"
#电话号码
CThostFtdcReserveOpenAccountConfirmField["Telephone"] = "string"
#手机
CThostFtdcReserveOpenAccountConfirmField["MobilePhone"] = "string"
#传真
CThostFtdcReserveOpenAccountConfirmField["Fax"] = "string"
#电子邮件
CThostFtdcReserveOpenAccountConfirmField["EMail"] = "string"
#资金账户状态
CThostFtdcReserveOpenAccountConfirmField["MoneyAccountStatus"] = "char"
#银行帐号
CThostFtdcReserveOpenAccountConfirmField["BankAccount"] = "string"
#银行密码
CThostFtdcReserveOpenAccountConfirmField["BankPassWord"] = "string"
#安装编号
CThostFtdcReserveOpenAccountConfirmField["InstallID"] = "int"
#验证客户证件号码标志
CThostFtdcReserveOpenAccountConfirmField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcReserveOpenAccountConfirmField["CurrencyID"] = "string"
#摘要
CThostFtdcReserveOpenAccountConfirmField["Digest"] = "string"
#银行帐号类型
CThostFtdcReserveOpenAccountConfirmField["BankAccType"] = "char"
#期货公司银行编码
CThostFtdcReserveOpenAccountConfirmField["BrokerIDByBank"] = "string"
#交易ID
CThostFtdcReserveOpenAccountConfirmField["TID"] = "int"
#投资者帐号
CThostFtdcReserveOpenAccountConfirmField["AccountID"] = "string"
#期货密码
CThostFtdcReserveOpenAccountConfirmField["Password"] = "string"
#预约开户银行流水号
CThostFtdcReserveOpenAccountConfirmField["BankReserveOpenSeq"] = "string"
#预约开户日期
CThostFtdcReserveOpenAccountConfirmField["BookDate"] = "string"
#预约开户验证密码
CThostFtdcReserveOpenAccountConfirmField["BookPsw"] = "string"
#错误代码
CThostFtdcReserveOpenAccountConfirmField["ErrorID"] = "int"
#错误信息
CThostFtdcReserveOpenAccountConfirmField["ErrorMsg"] = "string"
structDict['CThostFtdcReserveOpenAccountConfirmField'] = CThostFtdcReserveOpenAccountConfirmField


#银期预约开户
CThostFtdcReserveOpenAccountField = {}
#业务功能码
CThostFtdcReserveOpenAccountField["TradeCode"] = "string"
#银行代码
CThostFtdcReserveOpenAccountField["BankID"] = "string"
#银行分支机构代码
CThostFtdcReserveOpenAccountField["BankBranchID"] = "string"
#期商代码
CThostFtdcReserveOpenAccountField["BrokerID"] = "string"
#期商分支机构代码
CThostFtdcReserveOpenAccountField["BrokerBranchID"] = "string"
#交易日期
CThostFtdcReserveOpenAccountField["TradeDate"] = "string"
#交易时间
CThostFtdcReserveOpenAccountField["TradeTime"] = "string"
#银行流水号
CThostFtdcReserveOpenAccountField["BankSerial"] = "string"
#交易系统日期 
CThostFtdcReserveOpenAccountField["TradingDay"] = "string"
#银期平台消息流水号
CThostFtdcReserveOpenAccountField["PlateSerial"] = "int"
#最后分片标志
CThostFtdcReserveOpenAccountField["LastFragment"] = "char"
#会话号
CThostFtdcReserveOpenAccountField["SessionID"] = "int"
#客户姓名
CThostFtdcReserveOpenAccountField["CustomerName"] = "string"
#证件类型
CThostFtdcReserveOpenAccountField["IdCardType"] = "char"
#证件号码
CThostFtdcReserveOpenAccountField["IdentifiedCardNo"] = "string"
#性别
CThostFtdcReserveOpenAccountField["Gender"] = "char"
#国家代码
CThostFtdcReserveOpenAccountField["CountryCode"] = "string"
#客户类型
CThostFtdcReserveOpenAccountField["CustType"] = "char"
#地址
CThostFtdcReserveOpenAccountField["Address"] = "string"
#邮编
CThostFtdcReserveOpenAccountField["ZipCode"] = "string"
#电话号码
CThostFtdcReserveOpenAccountField["Telephone"] = "string"
#手机
CThostFtdcReserveOpenAccountField["MobilePhone"] = "string"
#传真
CThostFtdcReserveOpenAccountField["Fax"] = "string"
#电子邮件
CThostFtdcReserveOpenAccountField["EMail"] = "string"
#资金账户状态
CThostFtdcReserveOpenAccountField["MoneyAccountStatus"] = "char"
#银行帐号
CThostFtdcReserveOpenAccountField["BankAccount"] = "string"
#银行密码
CThostFtdcReserveOpenAccountField["BankPassWord"] = "string"
#安装编号
CThostFtdcReserveOpenAccountField["InstallID"] = "int"
#验证客户证件号码标志
CThostFtdcReserveOpenAccountField["VerifyCertNoFlag"] = "char"
#币种代码
CThostFtdcReserveOpenAccountField["CurrencyID"] = "string"
#摘要
CThostFtdcReserveOpenAccountField["Digest"] = "string"
#银行帐号类型
CThostFtdcReserveOpenAccountField["BankAccType"] = "char"
#期货公司银行编码
CThostFtdcReserveOpenAccountField["BrokerIDByBank"] = "string"
#交易ID
CThostFtdcReserveOpenAccountField["TID"] = "int"
#预约开户状态
CThostFtdcReserveOpenAccountField["ReserveOpenAccStas"] = "char"
#错误代码
CThostFtdcReserveOpenAccountField["ErrorID"] = "int"
#错误信息
CThostFtdcReserveOpenAccountField["ErrorMsg"] = "string"
structDict['CThostFtdcReserveOpenAccountField'] = CThostFtdcReserveOpenAccountField


#银行账户属性
CThostFtdcAccountPropertyField = {}
#经纪公司代码
CThostFtdcAccountPropertyField["BrokerID"] = "string"
#投资者帐号
CThostFtdcAccountPropertyField["AccountID"] = "string"
#银行统一标识类型
CThostFtdcAccountPropertyField["BankID"] = "string"
#银行账户
CThostFtdcAccountPropertyField["BankAccount"] = "string"
#银行账户的开户人名称
CThostFtdcAccountPropertyField["OpenName"] = "string"
#银行账户的开户行
CThostFtdcAccountPropertyField["OpenBank"] = "string"
#是否活跃
CThostFtdcAccountPropertyField["IsActive"] = "int"
#账户来源
CThostFtdcAccountPropertyField["AccountSourceType"] = "char"
#开户日期
CThostFtdcAccountPropertyField["OpenDate"] = "string"
#注销日期
CThostFtdcAccountPropertyField["CancelDate"] = "string"
#录入员代码
CThostFtdcAccountPropertyField["OperatorID"] = "string"
#录入日期
CThostFtdcAccountPropertyField["OperateDate"] = "string"
#录入时间
CThostFtdcAccountPropertyField["OperateTime"] = "string"
#币种代码
CThostFtdcAccountPropertyField["CurrencyID"] = "string"
structDict['CThostFtdcAccountPropertyField'] = CThostFtdcAccountPropertyField


#查询当前交易中心
CThostFtdcQryCurrDRIdentityField = {}
#交易中心代码
CThostFtdcQryCurrDRIdentityField["DRIdentityID"] = "int"
structDict['CThostFtdcQryCurrDRIdentityField'] = CThostFtdcQryCurrDRIdentityField


#当前交易中心
CThostFtdcCurrDRIdentityField = {}
#交易中心代码
CThostFtdcCurrDRIdentityField["DRIdentityID"] = "int"
structDict['CThostFtdcCurrDRIdentityField'] = CThostFtdcCurrDRIdentityField


#查询二级代理商资金校验模式
CThostFtdcQrySecAgentCheckModeField = {}
#经纪公司代码
CThostFtdcQrySecAgentCheckModeField["BrokerID"] = "string"
#投资者代码
CThostFtdcQrySecAgentCheckModeField["InvestorID"] = "string"
structDict['CThostFtdcQrySecAgentCheckModeField'] = CThostFtdcQrySecAgentCheckModeField


#查询二级代理商信息
CThostFtdcQrySecAgentTradeInfoField = {}
#经纪公司代码
CThostFtdcQrySecAgentTradeInfoField["BrokerID"] = "string"
#境外中介机构资金帐号
CThostFtdcQrySecAgentTradeInfoField["BrokerSecAgentID"] = "string"
structDict['CThostFtdcQrySecAgentTradeInfoField'] = CThostFtdcQrySecAgentTradeInfoField


#用户系统信息
CThostFtdcUserSystemInfoField = {}
#经纪公司代码
CThostFtdcUserSystemInfoField["BrokerID"] = "string"
#用户代码
CThostFtdcUserSystemInfoField["UserID"] = "string"
#用户端系统内部信息长度
CThostFtdcUserSystemInfoField["ClientSystemInfoLen"] = "int"
#用户端系统内部信息
CThostFtdcUserSystemInfoField["ClientSystemInfo"] = "string"
#用户公网IP
CThostFtdcUserSystemInfoField["ClientPublicIP"] = "string"
#终端IP端口
CThostFtdcUserSystemInfoField["ClientIPPort"] = "int"
#登录成功时间
CThostFtdcUserSystemInfoField["ClientLoginTime"] = "string"
#App代码
CThostFtdcUserSystemInfoField["ClientAppID"] = "string"
structDict['CThostFtdcUserSystemInfoField'] = CThostFtdcUserSystemInfoField


#用户发出获取安全安全登陆方法请求
CThostFtdcReqUserAuthMethodField = {}
#交易日
CThostFtdcReqUserAuthMethodField["TradingDay"] = "string"
#经纪公司代码
CThostFtdcReqUserAuthMethodField["BrokerID"] = "string"
#用户代码
CThostFtdcReqUserAuthMethodField["UserID"] = "string"
structDict['CThostFtdcReqUserAuthMethodField'] = CThostFtdcReqUserAuthMethodField


#用户发出获取安全安全登陆方法回复
CThostFtdcRspUserAuthMethodField = {}
#当前可以用的认证模式
CThostFtdcRspUserAuthMethodField["UsableAuthMethod"] = "int"
structDict['CThostFtdcRspUserAuthMethodField'] = CThostFtdcRspUserAuthMethodField


#用户发出获取安全安全登陆方法请求
CThostFtdcReqGenUserCaptchaField = {}
#交易日
CThostFtdcReqGenUserCaptchaField["TradingDay"] = "string"
#经纪公司代码
CThostFtdcReqGenUserCaptchaField["BrokerID"] = "string"
#用户代码
CThostFtdcReqGenUserCaptchaField["UserID"] = "string"
structDict['CThostFtdcReqGenUserCaptchaField'] = CThostFtdcReqGenUserCaptchaField


#生成的图片验证码信息
CThostFtdcRspGenUserCaptchaField = {}
#经纪公司代码
CThostFtdcRspGenUserCaptchaField["BrokerID"] = "string"
#用户代码
CThostFtdcRspGenUserCaptchaField["UserID"] = "string"
#图片信息长度
CThostFtdcRspGenUserCaptchaField["CaptchaInfoLen"] = "int"
#图片信息
CThostFtdcRspGenUserCaptchaField["CaptchaInfo"] = "string"
structDict['CThostFtdcRspGenUserCaptchaField'] = CThostFtdcRspGenUserCaptchaField


#用户发出获取安全安全登陆方法请求
CThostFtdcReqGenUserTextField = {}
#交易日
CThostFtdcReqGenUserTextField["TradingDay"] = "string"
#经纪公司代码
CThostFtdcReqGenUserTextField["BrokerID"] = "string"
#用户代码
CThostFtdcReqGenUserTextField["UserID"] = "string"
structDict['CThostFtdcReqGenUserTextField'] = CThostFtdcReqGenUserTextField


#短信验证码生成的回复
CThostFtdcRspGenUserTextField = {}
#短信验证码序号
CThostFtdcRspGenUserTextField["UserTextSeq"] = "int"
structDict['CThostFtdcRspGenUserTextField'] = CThostFtdcRspGenUserTextField


#用户发出带图形验证码的登录请求请求
CThostFtdcReqUserLoginWithCaptchaField = {}
#交易日
CThostFtdcReqUserLoginWithCaptchaField["TradingDay"] = "string"
#经纪公司代码
CThostFtdcReqUserLoginWithCaptchaField["BrokerID"] = "string"
#用户代码
CThostFtdcReqUserLoginWithCaptchaField["UserID"] = "string"
#密码
CThostFtdcReqUserLoginWithCaptchaField["Password"] = "string"
#用户端产品信息
CThostFtdcReqUserLoginWithCaptchaField["UserProductInfo"] = "string"
#接口端产品信息
CThostFtdcReqUserLoginWithCaptchaField["InterfaceProductInfo"] = "string"
#协议信息
CThostFtdcReqUserLoginWithCaptchaField["ProtocolInfo"] = "string"
#Mac地址
CThostFtdcReqUserLoginWithCaptchaField["MacAddress"] = "string"
#终端IP地址
CThostFtdcReqUserLoginWithCaptchaField["ClientIPAddress"] = "string"
#登录备注
CThostFtdcReqUserLoginWithCaptchaField["LoginRemark"] = "string"
#图形验证码的文字内容
CThostFtdcReqUserLoginWithCaptchaField["Captcha"] = "string"
#终端IP端口
CThostFtdcReqUserLoginWithCaptchaField["ClientIPPort"] = "int"
structDict['CThostFtdcReqUserLoginWithCaptchaField'] = CThostFtdcReqUserLoginWithCaptchaField


#用户发出带短信验证码的登录请求请求
CThostFtdcReqUserLoginWithTextField = {}
#交易日
CThostFtdcReqUserLoginWithTextField["TradingDay"] = "string"
#经纪公司代码
CThostFtdcReqUserLoginWithTextField["BrokerID"] = "string"
#用户代码
CThostFtdcReqUserLoginWithTextField["UserID"] = "string"
#密码
CThostFtdcReqUserLoginWithTextField["Password"] = "string"
#用户端产品信息
CThostFtdcReqUserLoginWithTextField["UserProductInfo"] = "string"
#接口端产品信息
CThostFtdcReqUserLoginWithTextField["InterfaceProductInfo"] = "string"
#协议信息
CThostFtdcReqUserLoginWithTextField["ProtocolInfo"] = "string"
#Mac地址
CThostFtdcReqUserLoginWithTextField["MacAddress"] = "string"
#终端IP地址
CThostFtdcReqUserLoginWithTextField["ClientIPAddress"] = "string"
#登录备注
CThostFtdcReqUserLoginWithTextField["LoginRemark"] = "string"
#短信验证码文字内容
CThostFtdcReqUserLoginWithTextField["Text"] = "string"
#终端IP端口
CThostFtdcReqUserLoginWithTextField["ClientIPPort"] = "int"
structDict['CThostFtdcReqUserLoginWithTextField'] = CThostFtdcReqUserLoginWithTextField


#用户发出带动态验证码的登录请求请求
CThostFtdcReqUserLoginWithOTPField = {}
#交易日
CThostFtdcReqUserLoginWithOTPField["TradingDay"] = "string"
#经纪公司代码
CThostFtdcReqUserLoginWithOTPField["BrokerID"] = "string"
#用户代码
CThostFtdcReqUserLoginWithOTPField["UserID"] = "string"
#密码
CThostFtdcReqUserLoginWithOTPField["Password"] = "string"
#用户端产品信息
CThostFtdcReqUserLoginWithOTPField["UserProductInfo"] = "string"
#接口端产品信息
CThostFtdcReqUserLoginWithOTPField["InterfaceProductInfo"] = "string"
#协议信息
CThostFtdcReqUserLoginWithOTPField["ProtocolInfo"] = "string"
#Mac地址
CThostFtdcReqUserLoginWithOTPField["MacAddress"] = "string"
#终端IP地址
CThostFtdcReqUserLoginWithOTPField["ClientIPAddress"] = "string"
#登录备注
CThostFtdcReqUserLoginWithOTPField["LoginRemark"] = "string"
#OTP密码
CThostFtdcReqUserLoginWithOTPField["OTPPassword"] = "string"
#终端IP端口
CThostFtdcReqUserLoginWithOTPField["ClientIPPort"] = "int"
structDict['CThostFtdcReqUserLoginWithOTPField'] = CThostFtdcReqUserLoginWithOTPField


#api握手请求
CThostFtdcReqApiHandshakeField = {}
#api与front通信密钥版本号
CThostFtdcReqApiHandshakeField["CryptoKeyVersion"] = "string"
structDict['CThostFtdcReqApiHandshakeField'] = CThostFtdcReqApiHandshakeField


#front发给api的握手回复
CThostFtdcRspApiHandshakeField = {}
#握手回复数据长度
CThostFtdcRspApiHandshakeField["FrontHandshakeDataLen"] = "int"
#握手回复数据
CThostFtdcRspApiHandshakeField["FrontHandshakeData"] = "string"
#API认证是否开启
CThostFtdcRspApiHandshakeField["IsApiAuthEnabled"] = "int"
structDict['CThostFtdcRspApiHandshakeField'] = CThostFtdcRspApiHandshakeField


#api给front的验证key的请求
CThostFtdcReqVerifyApiKeyField = {}
#握手回复数据长度
CThostFtdcReqVerifyApiKeyField["ApiHandshakeDataLen"] = "int"
#握手回复数据
CThostFtdcReqVerifyApiKeyField["ApiHandshakeData"] = "string"
structDict['CThostFtdcReqVerifyApiKeyField'] = CThostFtdcReqVerifyApiKeyField


#操作员组织架构关系
CThostFtdcDepartmentUserField = {}
#经纪公司代码
CThostFtdcDepartmentUserField["BrokerID"] = "string"
#用户代码
CThostFtdcDepartmentUserField["UserID"] = "string"
#投资者范围
CThostFtdcDepartmentUserField["InvestorRange"] = "char"
#投资者代码
CThostFtdcDepartmentUserField["InvestorID"] = "string"
structDict['CThostFtdcDepartmentUserField'] = CThostFtdcDepartmentUserField


#查询频率，每秒查询比数
CThostFtdcQueryFreqField = {}
#查询频率
CThostFtdcQueryFreqField["QueryFreq"] = "int"
structDict['CThostFtdcQueryFreqField'] = CThostFtdcQueryFreqField





