# encoding: UTF-8

structDict = {}

#//////////////////////////////////////////////////////////////////////
#@system QuantDo Platform
#@company 上海量投网络科技有限公司
#@file QdpFtdcUserApiStruct.h
#@brief 定义了客户端接口使用的业务数据结构
#@history 
#//////////////////////////////////////////////////////////////////////










#系统用户登录请求
CQdpFtdcReqUserLoginField = {}
#交易日
CQdpFtdcReqUserLoginField["TradingDay"] = "string"
#交易用户代码
CQdpFtdcReqUserLoginField["UserID"] = "string"
#经纪公司编号
CQdpFtdcReqUserLoginField["BrokerID"] = "string"
#密码
CQdpFtdcReqUserLoginField["Password"] = "string"
#用户端产品信息
CQdpFtdcReqUserLoginField["UserProductInfo"] = "string"
#接口端产品信息
CQdpFtdcReqUserLoginField["InterfaceProductInfo"] = "string"
#协议信息
CQdpFtdcReqUserLoginField["ProtocolInfo"] = "string"
#IP地址
CQdpFtdcReqUserLoginField["IPAddress"] = "string"
#Mac地址
CQdpFtdcReqUserLoginField["MacAddress"] = "string"
#数据中心代码
CQdpFtdcReqUserLoginField["DataCenterID"] = "int"
#动态密码
CQdpFtdcReqUserLoginField["OneTimePassword"] = "string"
#终端IP地址
CQdpFtdcReqUserLoginField["ClientIPAddress"] = "string"
structDict['CQdpFtdcReqUserLoginField'] = CQdpFtdcReqUserLoginField


#系统用户登录应答
CQdpFtdcRspUserLoginField = {}
#交易日
CQdpFtdcRspUserLoginField["TradingDay"] = "string"
#经纪公司编号
CQdpFtdcRspUserLoginField["BrokerID"] = "string"
#交易用户代码
CQdpFtdcRspUserLoginField["UserID"] = "string"
#登录成功时间
CQdpFtdcRspUserLoginField["LoginTime"] = "string"
#用户最大本地报单号
CQdpFtdcRspUserLoginField["MaxOrderLocalID"] = "string"
#交易系统名称
CQdpFtdcRspUserLoginField["TradingSystemName"] = "string"
#数据中心代码
CQdpFtdcRspUserLoginField["DataCenterID"] = "int"
#会员私有流当前长度
CQdpFtdcRspUserLoginField["PrivateFlowSize"] = "int"
#交易员私有流当前长度
CQdpFtdcRspUserLoginField["UserFlowSize"] = "int"
#会话编号
CQdpFtdcRspUserLoginField["SessionID"] = "int"
#前置编号
CQdpFtdcRspUserLoginField["FrontID"] = "int"
structDict['CQdpFtdcRspUserLoginField'] = CQdpFtdcRspUserLoginField


#用户登出请求
CQdpFtdcReqUserLogoutField = {}
#经纪公司编号
CQdpFtdcReqUserLogoutField["BrokerID"] = "string"
#交易用户代码
CQdpFtdcReqUserLogoutField["UserID"] = "string"
structDict['CQdpFtdcReqUserLogoutField'] = CQdpFtdcReqUserLogoutField


#用户登出请求
CQdpFtdcRspUserLogoutField = {}
#经纪公司编号
CQdpFtdcRspUserLogoutField["BrokerID"] = "string"
#交易用户代码
CQdpFtdcRspUserLogoutField["UserID"] = "string"
structDict['CQdpFtdcRspUserLogoutField'] = CQdpFtdcRspUserLogoutField


#强制用户退出
CQdpFtdcForceUserExitField = {}
#经纪公司编号
CQdpFtdcForceUserExitField["BrokerID"] = "string"
#交易用户代码
CQdpFtdcForceUserExitField["UserID"] = "string"
structDict['CQdpFtdcForceUserExitField'] = CQdpFtdcForceUserExitField


#用户口令修改
CQdpFtdcUserPasswordUpdateField = {}
#经纪公司编号
CQdpFtdcUserPasswordUpdateField["BrokerID"] = "string"
#交易用户代码
CQdpFtdcUserPasswordUpdateField["UserID"] = "string"
#旧密码
CQdpFtdcUserPasswordUpdateField["OldPassword"] = "string"
#新密码
CQdpFtdcUserPasswordUpdateField["NewPassword"] = "string"
structDict['CQdpFtdcUserPasswordUpdateField'] = CQdpFtdcUserPasswordUpdateField


#输入报单
CQdpFtdcInputOrderField = {}
#经纪公司编号
CQdpFtdcInputOrderField["BrokerID"] = "string"
#交易所代码
CQdpFtdcInputOrderField["ExchangeID"] = "string"
#系统报单编号
CQdpFtdcInputOrderField["OrderSysID"] = "string"
#投资者编号
CQdpFtdcInputOrderField["InvestorID"] = "string"
#用户代码
CQdpFtdcInputOrderField["UserID"] = "string"
#合约代码
CQdpFtdcInputOrderField["InstrumentID"] = "string"
#用户本地报单号
CQdpFtdcInputOrderField["UserOrderLocalID"] = "string"
#价格类型
CQdpFtdcInputOrderField["OrderPriceType"] = "char"
#买卖方向
CQdpFtdcInputOrderField["Direction"] = "char"
#开平标志
CQdpFtdcInputOrderField["OffsetFlag"] = "char"
#投机套保标志
CQdpFtdcInputOrderField["HedgeFlag"] = "char"
#价格
CQdpFtdcInputOrderField["LimitPrice"] = "float"
#数量
CQdpFtdcInputOrderField["Volume"] = "int"
#有效期类型
CQdpFtdcInputOrderField["TimeCondition"] = "char"
#GTD日期
CQdpFtdcInputOrderField["GTDDate"] = "string"
#成交量类型
CQdpFtdcInputOrderField["VolumeCondition"] = "char"
#最小成交量
CQdpFtdcInputOrderField["MinVolume"] = "int"
#止损价
CQdpFtdcInputOrderField["StopPrice"] = "float"
#强平原因
CQdpFtdcInputOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CQdpFtdcInputOrderField["IsAutoSuspend"] = "int"
#业务单元
CQdpFtdcInputOrderField["BusinessUnit"] = "string"
#用户自定义域`
CQdpFtdcInputOrderField["UserCustom"] = "string"
#营业部代码
CQdpFtdcInputOrderField["BranchID"] = "string"
#记录编号
CQdpFtdcInputOrderField["RecNum"] = "int"
#业务类别
CQdpFtdcInputOrderField["BusinessType"] = "char"
structDict['CQdpFtdcInputOrderField'] = CQdpFtdcInputOrderField


#报单操作
CQdpFtdcOrderActionField = {}
#交易所代码
CQdpFtdcOrderActionField["ExchangeID"] = "string"
#报单编号
CQdpFtdcOrderActionField["OrderSysID"] = "string"
#经纪公司编号
CQdpFtdcOrderActionField["BrokerID"] = "string"
#投资者编号
CQdpFtdcOrderActionField["InvestorID"] = "string"
#用户代码
CQdpFtdcOrderActionField["UserID"] = "string"
#合约代码
CQdpFtdcOrderActionField["InstrumentID"] = "string"
#本次撤单操作的本地编号
CQdpFtdcOrderActionField["UserOrderActionLocalID"] = "string"
#被撤订单的本地报单编号
CQdpFtdcOrderActionField["UserOrderLocalID"] = "string"
#报单操作标志
CQdpFtdcOrderActionField["ActionFlag"] = "char"
#价格
CQdpFtdcOrderActionField["LimitPrice"] = "float"
#数量变化
CQdpFtdcOrderActionField["VolumeChange"] = "int"
#记录编号
CQdpFtdcOrderActionField["RecNum"] = "int"
#前置编号
CQdpFtdcOrderActionField["FrontID"] = "int"
#会话编号
CQdpFtdcOrderActionField["SessionID"] = "int"
structDict['CQdpFtdcOrderActionField'] = CQdpFtdcOrderActionField


#内存表导出
CQdpFtdcMemDbField = {}
#内存表名
CQdpFtdcMemDbField["MemTableName"] = "string"
structDict['CQdpFtdcMemDbField'] = CQdpFtdcMemDbField


#投资者资金帐户出入金请求
CQdpFtdcReqAccountDepositField = {}
#经纪公司编号
CQdpFtdcReqAccountDepositField["BrokerID"] = "string"
#资金流水号
CQdpFtdcReqAccountDepositField["AccountSeqNo"] = "string"
#资金帐号
CQdpFtdcReqAccountDepositField["AccountID"] = "string"
#连续递增的总资金流水号
CQdpFtdcReqAccountDepositField["AccountInsideSeqNo"] = "string"
#投资者编号
CQdpFtdcReqAccountDepositField["InvestorID"] = "string"
#金额
CQdpFtdcReqAccountDepositField["Amount"] = "float"
#出入金方向
CQdpFtdcReqAccountDepositField["AmountDirection"] = "char"
#用户代码
CQdpFtdcReqAccountDepositField["UserID"] = "string"
structDict['CQdpFtdcReqAccountDepositField'] = CQdpFtdcReqAccountDepositField


#投资者资金帐户出入金应答
CQdpFtdcRspAccountDepositField = {}
#经纪公司编号
CQdpFtdcRspAccountDepositField["BrokerID"] = "string"
#投资者编号
CQdpFtdcRspAccountDepositField["InvestorID"] = "string"
#资金帐号
CQdpFtdcRspAccountDepositField["AccountID"] = "string"
#资金流水号
CQdpFtdcRspAccountDepositField["AccountSeqNo"] = "string"
#连续递增的总资金流水号
CQdpFtdcRspAccountDepositField["AccountInsideSeqNo"] = "string"
#金额
CQdpFtdcRspAccountDepositField["Amount"] = "float"
#出入金方向
CQdpFtdcRspAccountDepositField["AmountDirection"] = "char"
#可用资金
CQdpFtdcRspAccountDepositField["Available"] = "float"
#结算准备金
CQdpFtdcRspAccountDepositField["Balance"] = "float"
#用户代码
CQdpFtdcRspAccountDepositField["UserID"] = "string"
structDict['CQdpFtdcRspAccountDepositField'] = CQdpFtdcRspAccountDepositField


#期货发起转账请求
CQdpFtdcReqTransferField = {}
#业务功能码
CQdpFtdcReqTransferField["TradeCode"] = "string"
#银行代码
CQdpFtdcReqTransferField["BankID"] = "string"
#银行分支机构代码
CQdpFtdcReqTransferField["BankBrchID"] = "string"
#经纪公司编号
CQdpFtdcReqTransferField["BrokerID"] = "string"
#期商分支机构代码
CQdpFtdcReqTransferField["BrokerBranchID"] = "string"
#交易日期
CQdpFtdcReqTransferField["TradeDate"] = "string"
#交易时间
CQdpFtdcReqTransferField["TradingTime"] = "string"
#银行流水号
CQdpFtdcReqTransferField["BankSerial"] = "string"
#交易系统日期
CQdpFtdcReqTransferField["TradingDay"] = "string"
#银期平台消息流水号
CQdpFtdcReqTransferField["PlateSerial"] = "int"
#最后分片标志
CQdpFtdcReqTransferField["LastFragment"] = "char"
#会话号
CQdpFtdcReqTransferField["SessionID"] = "int"
#客户姓名
CQdpFtdcReqTransferField["CustomerName"] = "string"
#证件类型
CQdpFtdcReqTransferField["IdCardType"] = "string"
#证件号码
CQdpFtdcReqTransferField["IdentifiedCardNo"] = "string"
#客户类型
CQdpFtdcReqTransferField["CustType"] = "string"
#银行账号
CQdpFtdcReqTransferField["BankAccount"] = "string"
#银行密码
CQdpFtdcReqTransferField["BankPassWord"] = "string"
#资金账号
CQdpFtdcReqTransferField["AccountID"] = "string"
#投资者编号
CQdpFtdcReqTransferField["InvestorID"] = "string"
#期货密码
CQdpFtdcReqTransferField["Password"] = "string"
#安装编号
CQdpFtdcReqTransferField["InstallID"] = "int"
#期货公司流水号
CQdpFtdcReqTransferField["FutureSerial"] = "int"
#交易员
CQdpFtdcReqTransferField["UserID"] = "string"
#验证客户证件号码标志
CQdpFtdcReqTransferField["VerifyCertNoFlag"] = "string"
#币种代码
CQdpFtdcReqTransferField["Currency"] = "string"
#转账金额
CQdpFtdcReqTransferField["TradeAmount"] = "float"
#期货可取金额
CQdpFtdcReqTransferField["FutureFetchAmount"] = "float"
#费用支付标志
CQdpFtdcReqTransferField["FeePayFlag"] = "char"
#应收客户费用
CQdpFtdcReqTransferField["CustFee"] = "float"
#应收期货公司费用
CQdpFtdcReqTransferField["BrokerFee"] = "float"
#发送方给接收方的消息
CQdpFtdcReqTransferField["Message"] = "string"
#摘要
CQdpFtdcReqTransferField["Digest"] = "string"
#银行账号类型
CQdpFtdcReqTransferField["BankAccType"] = "char"
#渠道标志
CQdpFtdcReqTransferField["DeviceID"] = "string"
#期货单位账号类型
CQdpFtdcReqTransferField["BankSecuAccType"] = "char"
#期货公司银行编码
CQdpFtdcReqTransferField["BankCodingForFuture"] = "string"
#期货单位账号
CQdpFtdcReqTransferField["BankSecuAcc"] = "string"
#银行密码标志
CQdpFtdcReqTransferField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CQdpFtdcReqTransferField["SecuPwdFlag"] = "char"
#交易柜员
CQdpFtdcReqTransferField["OperNo"] = "string"
#请求编号
CQdpFtdcReqTransferField["RequestID"] = "int"
#交易ID
CQdpFtdcReqTransferField["TID"] = "int"
#转账交易状态
CQdpFtdcReqTransferField["TransferStatus"] = "char"
structDict['CQdpFtdcReqTransferField'] = CQdpFtdcReqTransferField


#期货发起转账通知
CQdpFtdcRspTransferField = {}
#业务功能码
CQdpFtdcRspTransferField["TradeCode"] = "string"
#银行代码
CQdpFtdcRspTransferField["BankID"] = "string"
#银行分支机构代码
CQdpFtdcRspTransferField["BankBrchID"] = "string"
#经纪公司编号
CQdpFtdcRspTransferField["BrokerID"] = "string"
#期商分支机构代码
CQdpFtdcRspTransferField["BrokerBranchID"] = "string"
#交易日期
CQdpFtdcRspTransferField["TradeDate"] = "string"
#交易时间
CQdpFtdcRspTransferField["TradingTime"] = "string"
#银行流水号
CQdpFtdcRspTransferField["BankSerial"] = "string"
#交易系统日期
CQdpFtdcRspTransferField["TradingDay"] = "string"
#银期平台消息流水号
CQdpFtdcRspTransferField["PlateSerial"] = "int"
#最后分片标志
CQdpFtdcRspTransferField["LastFragment"] = "char"
#会话号
CQdpFtdcRspTransferField["SessionID"] = "int"
#客户姓名
CQdpFtdcRspTransferField["CustomerName"] = "string"
#证件类型
CQdpFtdcRspTransferField["IdCardType"] = "string"
#证件号码
CQdpFtdcRspTransferField["IdentifiedCardNo"] = "string"
#客户类型
CQdpFtdcRspTransferField["CustType"] = "string"
#银行账号
CQdpFtdcRspTransferField["BankAccount"] = "string"
#银行密码
CQdpFtdcRspTransferField["BankPassWord"] = "string"
#资金账号
CQdpFtdcRspTransferField["AccountID"] = "string"
#投资者编号
CQdpFtdcRspTransferField["InvestorID"] = "string"
#期货密码
CQdpFtdcRspTransferField["Password"] = "string"
#安装编号
CQdpFtdcRspTransferField["InstallID"] = "int"
#期货公司流水号
CQdpFtdcRspTransferField["FutureSerial"] = "int"
#交易员
CQdpFtdcRspTransferField["UserID"] = "string"
#验证客户证件号码标志
CQdpFtdcRspTransferField["VerifyCertNoFlag"] = "string"
#币种代码
CQdpFtdcRspTransferField["Currency"] = "string"
#转账金额
CQdpFtdcRspTransferField["TradeAmount"] = "float"
#期货可取金额
CQdpFtdcRspTransferField["FutureFetchAmount"] = "float"
#费用支付标志
CQdpFtdcRspTransferField["FeePayFlag"] = "char"
#应收客户费用
CQdpFtdcRspTransferField["CustFee"] = "float"
#应收期货公司费用
CQdpFtdcRspTransferField["BrokerFee"] = "float"
#发送方给接收方的消息
CQdpFtdcRspTransferField["Message"] = "string"
#摘要
CQdpFtdcRspTransferField["Digest"] = "string"
#银行账号类型
CQdpFtdcRspTransferField["BankAccType"] = "char"
#渠道标志
CQdpFtdcRspTransferField["DeviceID"] = "string"
#期货单位账号类型
CQdpFtdcRspTransferField["BankSecuAccType"] = "char"
#期货公司银行编码
CQdpFtdcRspTransferField["BankCodingForFuture"] = "string"
#期货单位账号
CQdpFtdcRspTransferField["BankSecuAcc"] = "string"
#银行密码标志
CQdpFtdcRspTransferField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CQdpFtdcRspTransferField["SecuPwdFlag"] = "char"
#交易柜员
CQdpFtdcRspTransferField["OperNo"] = "string"
#请求编号
CQdpFtdcRspTransferField["RequestID"] = "int"
#交易ID
CQdpFtdcRspTransferField["TID"] = "int"
#转账交易状态
CQdpFtdcRspTransferField["TransferStatus"] = "char"
#错误代码
CQdpFtdcRspTransferField["ErrorID"] = "int"
#错误信息
CQdpFtdcRspTransferField["ErrorMsg"] = "string"
structDict['CQdpFtdcRspTransferField'] = CQdpFtdcRspTransferField


#期货发起查询银行余额通知
CQdpFtdcNotifyQueryAccountField = {}
#业务功能码
CQdpFtdcNotifyQueryAccountField["TradeCode"] = "string"
#银行代码
CQdpFtdcNotifyQueryAccountField["BankID"] = "string"
#银行分中心代码
CQdpFtdcNotifyQueryAccountField["BankBrchID"] = "string"
#经纪公司编号
CQdpFtdcNotifyQueryAccountField["BrokerID"] = "string"
#期商分支机构代码
CQdpFtdcNotifyQueryAccountField["BrokerBranchID"] = "string"
#交易日期
CQdpFtdcNotifyQueryAccountField["TradeDate"] = "string"
#交易时间
CQdpFtdcNotifyQueryAccountField["TradeTime"] = "string"
#银行流水号
CQdpFtdcNotifyQueryAccountField["BankSerial"] = "string"
#交易系统日期
CQdpFtdcNotifyQueryAccountField["TradingDay"] = "string"
#银期平台消息流水号
CQdpFtdcNotifyQueryAccountField["PlateSerial"] = "int"
#最后分片标志
CQdpFtdcNotifyQueryAccountField["LastFragment"] = "char"
#会话号
CQdpFtdcNotifyQueryAccountField["SessionID"] = "int"
#客户姓名
CQdpFtdcNotifyQueryAccountField["CustomerName"] = "string"
#证件类型
CQdpFtdcNotifyQueryAccountField["IdCardType"] = "string"
#证件号码
CQdpFtdcNotifyQueryAccountField["IdentifiedCardNo"] = "string"
#客户类型
CQdpFtdcNotifyQueryAccountField["CustType"] = "string"
#银行账号
CQdpFtdcNotifyQueryAccountField["BankAccount"] = "string"
#银行密码
CQdpFtdcNotifyQueryAccountField["BankPassWord"] = "string"
#资金账号
CQdpFtdcNotifyQueryAccountField["AccountID"] = "string"
#投资者编号
CQdpFtdcNotifyQueryAccountField["InvestorID"] = "string"
#期货密码
CQdpFtdcNotifyQueryAccountField["Password"] = "string"
#期货公司流水号
CQdpFtdcNotifyQueryAccountField["FutureSerial"] = "int"
#安装编号
CQdpFtdcNotifyQueryAccountField["InstallID"] = "int"
#交易员
CQdpFtdcNotifyQueryAccountField["UserID"] = "string"
#验证客户证件号码标志
CQdpFtdcNotifyQueryAccountField["VerifyCertNoFlag"] = "string"
#币种代码
CQdpFtdcNotifyQueryAccountField["Currency"] = "string"
#摘要
CQdpFtdcNotifyQueryAccountField["Digest"] = "string"
#银行账号类型
CQdpFtdcNotifyQueryAccountField["BankAccType"] = "char"
#渠道标志
CQdpFtdcNotifyQueryAccountField["DeviceID"] = "string"
#期货单位账号类型
CQdpFtdcNotifyQueryAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CQdpFtdcNotifyQueryAccountField["BankCodingForFuture"] = "string"
#期货单位账号
CQdpFtdcNotifyQueryAccountField["BankSecuAcc"] = "string"
#银行密码标志
CQdpFtdcNotifyQueryAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CQdpFtdcNotifyQueryAccountField["SecuPwdFlag"] = "char"
#交易柜员
CQdpFtdcNotifyQueryAccountField["OperNo"] = "string"
#请求编号
CQdpFtdcNotifyQueryAccountField["RequestID"] = "int"
#交易ID
CQdpFtdcNotifyQueryAccountField["TID"] = "int"
#银行可用金额
CQdpFtdcNotifyQueryAccountField["BankUseAmount"] = "float"
#银行可取金额
CQdpFtdcNotifyQueryAccountField["BankFetchAmount"] = "float"
#错误代码
CQdpFtdcNotifyQueryAccountField["ErrorID"] = "int"
#错误信息
CQdpFtdcNotifyQueryAccountField["ErrorMsg"] = "string"
structDict['CQdpFtdcNotifyQueryAccountField'] = CQdpFtdcNotifyQueryAccountField


#响应信息
CQdpFtdcRspInfoField = {}
#错误代码
CQdpFtdcRspInfoField["ErrorID"] = "int"
#错误信息
CQdpFtdcRspInfoField["ErrorMsg"] = "string"
structDict['CQdpFtdcRspInfoField'] = CQdpFtdcRspInfoField


#报单查询
CQdpFtdcQryOrderField = {}
#经纪公司编号
CQdpFtdcQryOrderField["BrokerID"] = "string"
#用户代码
CQdpFtdcQryOrderField["UserID"] = "string"
#交易所代码
CQdpFtdcQryOrderField["ExchangeID"] = "string"
#投资者编号
CQdpFtdcQryOrderField["InvestorID"] = "string"
#报单编号
CQdpFtdcQryOrderField["OrderSysID"] = "string"
#合约代码
CQdpFtdcQryOrderField["InstrumentID"] = "string"
structDict['CQdpFtdcQryOrderField'] = CQdpFtdcQryOrderField


#成交查询
CQdpFtdcQryTradeField = {}
#经纪公司编号
CQdpFtdcQryTradeField["BrokerID"] = "string"
#用户代码
CQdpFtdcQryTradeField["UserID"] = "string"
#交易所代码
CQdpFtdcQryTradeField["ExchangeID"] = "string"
#投资者编号
CQdpFtdcQryTradeField["InvestorID"] = "string"
#成交编号
CQdpFtdcQryTradeField["TradeID"] = "string"
#合约代码
CQdpFtdcQryTradeField["InstrumentID"] = "string"
structDict['CQdpFtdcQryTradeField'] = CQdpFtdcQryTradeField


#合约查询
CQdpFtdcQryInstrumentField = {}
#交易所代码
CQdpFtdcQryInstrumentField["ExchangeID"] = "string"
#产品代码
CQdpFtdcQryInstrumentField["ProductID"] = "string"
#合约代码
CQdpFtdcQryInstrumentField["InstrumentID"] = "string"
structDict['CQdpFtdcQryInstrumentField'] = CQdpFtdcQryInstrumentField


#合约查询应答
CQdpFtdcRspInstrumentField = {}
#交易所代码
CQdpFtdcRspInstrumentField["ExchangeID"] = "string"
#品种代码
CQdpFtdcRspInstrumentField["ProductID"] = "string"
#品种名称
CQdpFtdcRspInstrumentField["ProductName"] = "string"
#合约代码
CQdpFtdcRspInstrumentField["InstrumentID"] = "string"
#合约名称
CQdpFtdcRspInstrumentField["InstrumentName"] = "string"
#交割年份
CQdpFtdcRspInstrumentField["DeliveryYear"] = "int"
#交割月
CQdpFtdcRspInstrumentField["DeliveryMonth"] = "int"
#限价单最大下单量
CQdpFtdcRspInstrumentField["MaxLimitOrderVolume"] = "int"
#限价单最小下单量
CQdpFtdcRspInstrumentField["MinLimitOrderVolume"] = "int"
#市价单最大下单量
CQdpFtdcRspInstrumentField["MaxMarketOrderVolume"] = "int"
#市价单最小下单量
CQdpFtdcRspInstrumentField["MinMarketOrderVolume"] = "int"
#数量乘数
CQdpFtdcRspInstrumentField["VolumeMultiple"] = "int"
#报价单位
CQdpFtdcRspInstrumentField["PriceTick"] = "float"
#币种
CQdpFtdcRspInstrumentField["Currency"] = "char"
#多头限仓
CQdpFtdcRspInstrumentField["LongPosLimit"] = "int"
#空头限仓
CQdpFtdcRspInstrumentField["ShortPosLimit"] = "int"
#跌停板价
CQdpFtdcRspInstrumentField["LowerLimitPrice"] = "float"
#涨停板价
CQdpFtdcRspInstrumentField["UpperLimitPrice"] = "float"
#昨结算
CQdpFtdcRspInstrumentField["PreSettlementPrice"] = "float"
#合约交易状态
CQdpFtdcRspInstrumentField["InstrumentStatus"] = "char"
#创建日
CQdpFtdcRspInstrumentField["CreateDate"] = "string"
#上市日
CQdpFtdcRspInstrumentField["OpenDate"] = "string"
#到期日
CQdpFtdcRspInstrumentField["ExpireDate"] = "string"
#开始交割日
CQdpFtdcRspInstrumentField["StartDelivDate"] = "string"
#最后交割日
CQdpFtdcRspInstrumentField["EndDelivDate"] = "string"
#挂牌基准价
CQdpFtdcRspInstrumentField["BasisPrice"] = "float"
#当前是否交易
CQdpFtdcRspInstrumentField["IsTrading"] = "int"
#基础商品代码
CQdpFtdcRspInstrumentField["UnderlyingInstrID"] = "string"
#基础商品乘数
CQdpFtdcRspInstrumentField["UnderlyingMultiple"] = "int"
#持仓类型
CQdpFtdcRspInstrumentField["PositionType"] = "char"
#执行价
CQdpFtdcRspInstrumentField["StrikePrice"] = "float"
#期权类型
CQdpFtdcRspInstrumentField["OptionsType"] = "char"
#产品类型
CQdpFtdcRspInstrumentField["ProductClass"] = "char"
structDict['CQdpFtdcRspInstrumentField'] = CQdpFtdcRspInstrumentField


#合约状态
CQdpFtdcInstrumentStatusField = {}
#交易所代码
CQdpFtdcInstrumentStatusField["ExchangeID"] = "string"
#品种代码
CQdpFtdcInstrumentStatusField["ProductID"] = "string"
#品种名称
CQdpFtdcInstrumentStatusField["ProductName"] = "string"
#合约代码
CQdpFtdcInstrumentStatusField["InstrumentID"] = "string"
#合约名称
CQdpFtdcInstrumentStatusField["InstrumentName"] = "string"
#交割年份
CQdpFtdcInstrumentStatusField["DeliveryYear"] = "int"
#交割月
CQdpFtdcInstrumentStatusField["DeliveryMonth"] = "int"
#限价单最大下单量
CQdpFtdcInstrumentStatusField["MaxLimitOrderVolume"] = "int"
#限价单最小下单量
CQdpFtdcInstrumentStatusField["MinLimitOrderVolume"] = "int"
#市价单最大下单量
CQdpFtdcInstrumentStatusField["MaxMarketOrderVolume"] = "int"
#市价单最小下单量
CQdpFtdcInstrumentStatusField["MinMarketOrderVolume"] = "int"
#数量乘数
CQdpFtdcInstrumentStatusField["VolumeMultiple"] = "int"
#报价单位
CQdpFtdcInstrumentStatusField["PriceTick"] = "float"
#币种
CQdpFtdcInstrumentStatusField["Currency"] = "char"
#多头限仓
CQdpFtdcInstrumentStatusField["LongPosLimit"] = "int"
#空头限仓
CQdpFtdcInstrumentStatusField["ShortPosLimit"] = "int"
#跌停板价
CQdpFtdcInstrumentStatusField["LowerLimitPrice"] = "float"
#涨停板价
CQdpFtdcInstrumentStatusField["UpperLimitPrice"] = "float"
#昨结算
CQdpFtdcInstrumentStatusField["PreSettlementPrice"] = "float"
#合约交易状态
CQdpFtdcInstrumentStatusField["InstrumentStatus"] = "char"
#创建日
CQdpFtdcInstrumentStatusField["CreateDate"] = "string"
#上市日
CQdpFtdcInstrumentStatusField["OpenDate"] = "string"
#到期日
CQdpFtdcInstrumentStatusField["ExpireDate"] = "string"
#开始交割日
CQdpFtdcInstrumentStatusField["StartDelivDate"] = "string"
#最后交割日
CQdpFtdcInstrumentStatusField["EndDelivDate"] = "string"
#挂牌基准价
CQdpFtdcInstrumentStatusField["BasisPrice"] = "float"
#当前是否交易
CQdpFtdcInstrumentStatusField["IsTrading"] = "int"
#基础商品代码
CQdpFtdcInstrumentStatusField["UnderlyingInstrID"] = "string"
#基础商品乘数
CQdpFtdcInstrumentStatusField["UnderlyingMultiple"] = "int"
#持仓类型
CQdpFtdcInstrumentStatusField["PositionType"] = "char"
#执行价
CQdpFtdcInstrumentStatusField["StrikePrice"] = "float"
#期权类型
CQdpFtdcInstrumentStatusField["OptionsType"] = "char"
#产品类型
CQdpFtdcInstrumentStatusField["ProductClass"] = "char"
structDict['CQdpFtdcInstrumentStatusField'] = CQdpFtdcInstrumentStatusField


#投资者资金查询
CQdpFtdcQryInvestorAccountField = {}
#经纪公司编号
CQdpFtdcQryInvestorAccountField["BrokerID"] = "string"
#用户代码
CQdpFtdcQryInvestorAccountField["UserID"] = "string"
#投资者编号
CQdpFtdcQryInvestorAccountField["InvestorID"] = "string"
structDict['CQdpFtdcQryInvestorAccountField'] = CQdpFtdcQryInvestorAccountField


#投资者资金应答
CQdpFtdcRspInvestorAccountField = {}
#经纪公司编号
CQdpFtdcRspInvestorAccountField["BrokerID"] = "string"
#投资者编号
CQdpFtdcRspInvestorAccountField["InvestorID"] = "string"
#资金帐号
CQdpFtdcRspInvestorAccountField["AccountID"] = "string"
#上次结算准备金
CQdpFtdcRspInvestorAccountField["PreBalance"] = "float"
#上日可用资金
CQdpFtdcRspInvestorAccountField["PreAvailable"] = "float"
#入金金额
CQdpFtdcRspInvestorAccountField["Deposit"] = "float"
#出金金额
CQdpFtdcRspInvestorAccountField["Withdraw"] = "float"
#占用保证金
CQdpFtdcRspInvestorAccountField["Margin"] = "float"
#期权权利金收支
CQdpFtdcRspInvestorAccountField["Premium"] = "float"
#手续费
CQdpFtdcRspInvestorAccountField["Fee"] = "float"
#冻结的保证金
CQdpFtdcRspInvestorAccountField["FrozenMargin"] = "float"
#冻结权利金
CQdpFtdcRspInvestorAccountField["FrozenPremium"] = "float"
#冻结手续费
CQdpFtdcRspInvestorAccountField["FrozenFee"] = "float"
#平仓盈亏
CQdpFtdcRspInvestorAccountField["CloseProfit"] = "float"
#持仓盈亏
CQdpFtdcRspInvestorAccountField["PositionProfit"] = "float"
#可用资金
CQdpFtdcRspInvestorAccountField["Available"] = "float"
#结算准备金
CQdpFtdcRspInvestorAccountField["Balance"] = "float"
#多头占用保证金
CQdpFtdcRspInvestorAccountField["LongMargin"] = "float"
#空头占用保证金
CQdpFtdcRspInvestorAccountField["ShortMargin"] = "float"
#多头冻结的保证金
CQdpFtdcRspInvestorAccountField["LongFrozenMargin"] = "float"
#空头冻结的保证金
CQdpFtdcRspInvestorAccountField["ShortFrozenMargin"] = "float"
#动态权益
CQdpFtdcRspInvestorAccountField["DynamicRights"] = "float"
#风险度
CQdpFtdcRspInvestorAccountField["Risk"] = "float"
#其他费用
CQdpFtdcRspInvestorAccountField["OtherFee"] = "float"
#质押金额
CQdpFtdcRspInvestorAccountField["Mortgage"] = "float"
#币种
CQdpFtdcRspInvestorAccountField["Currency"] = "string"
structDict['CQdpFtdcRspInvestorAccountField'] = CQdpFtdcRspInvestorAccountField


#可用投资者查询
CQdpFtdcQryUserInvestorField = {}
#经纪公司编号
CQdpFtdcQryUserInvestorField["BrokerID"] = "string"
#用户代码
CQdpFtdcQryUserInvestorField["UserID"] = "string"
structDict['CQdpFtdcQryUserInvestorField'] = CQdpFtdcQryUserInvestorField


#可用投资者应答
CQdpFtdcRspUserInvestorField = {}
#经纪公司编号
CQdpFtdcRspUserInvestorField["BrokerID"] = "string"
#交易用户代码
CQdpFtdcRspUserInvestorField["UserID"] = "string"
#投资者编号
CQdpFtdcRspUserInvestorField["InvestorID"] = "string"
structDict['CQdpFtdcRspUserInvestorField'] = CQdpFtdcRspUserInvestorField


#交易编码查询
CQdpFtdcQryTradingCodeField = {}
#经纪公司编号
CQdpFtdcQryTradingCodeField["BrokerID"] = "string"
#用户代码
CQdpFtdcQryTradingCodeField["UserID"] = "string"
#投资者编号
CQdpFtdcQryTradingCodeField["InvestorID"] = "string"
#交易所代码
CQdpFtdcQryTradingCodeField["ExchangeID"] = "string"
structDict['CQdpFtdcQryTradingCodeField'] = CQdpFtdcQryTradingCodeField


#交易编码查询
CQdpFtdcRspTradingCodeField = {}
#经纪公司编号
CQdpFtdcRspTradingCodeField["BrokerID"] = "string"
#投资者编号
CQdpFtdcRspTradingCodeField["InvestorID"] = "string"
#资金帐号
CQdpFtdcRspTradingCodeField["AccountID"] = "string"
#交易所代码
CQdpFtdcRspTradingCodeField["ExchangeID"] = "string"
#会员编号
CQdpFtdcRspTradingCodeField["ParticipantID"] = "string"
#客户代码
CQdpFtdcRspTradingCodeField["ClientID"] = "string"
#客户代码权限
CQdpFtdcRspTradingCodeField["ClientRight"] = "char"
#客户类型
CQdpFtdcRspTradingCodeField["ClientType"] = "string"
#客户保值类型
CQdpFtdcRspTradingCodeField["ClientHedgeFlag"] = "char"
#是否活跃
CQdpFtdcRspTradingCodeField["IsActive"] = "char"
structDict['CQdpFtdcRspTradingCodeField'] = CQdpFtdcRspTradingCodeField


#交易所查询请求
CQdpFtdcQryExchangeField = {}
#交易所代码
CQdpFtdcQryExchangeField["ExchangeID"] = "string"
structDict['CQdpFtdcQryExchangeField'] = CQdpFtdcQryExchangeField


#交易所查询应答
CQdpFtdcRspExchangeField = {}
#交易日
CQdpFtdcRspExchangeField["TradingDay"] = "string"
#交易所代码
CQdpFtdcRspExchangeField["ExchangeID"] = "string"
#交易所名称
CQdpFtdcRspExchangeField["ExchangeName"] = "string"
structDict['CQdpFtdcRspExchangeField'] = CQdpFtdcRspExchangeField


#投资者持仓查询请求
CQdpFtdcQryInvestorPositionField = {}
#经纪公司编号
CQdpFtdcQryInvestorPositionField["BrokerID"] = "string"
#用户代码
CQdpFtdcQryInvestorPositionField["UserID"] = "string"
#交易所代码
CQdpFtdcQryInvestorPositionField["ExchangeID"] = "string"
#投资者编号
CQdpFtdcQryInvestorPositionField["InvestorID"] = "string"
#合约代码
CQdpFtdcQryInvestorPositionField["InstrumentID"] = "string"
structDict['CQdpFtdcQryInvestorPositionField'] = CQdpFtdcQryInvestorPositionField


#投资者持仓查询应答
CQdpFtdcRspInvestorPositionField = {}
#经纪公司编号
CQdpFtdcRspInvestorPositionField["BrokerID"] = "string"
#交易所代码
CQdpFtdcRspInvestorPositionField["ExchangeID"] = "string"
#投资者编号
CQdpFtdcRspInvestorPositionField["InvestorID"] = "string"
#会员编号
CQdpFtdcRspInvestorPositionField["ParticipantID"] = "string"
#客户代码
CQdpFtdcRspInvestorPositionField["ClientID"] = "string"
#合约代码
CQdpFtdcRspInvestorPositionField["InstrumentID"] = "string"
#买卖方向
CQdpFtdcRspInvestorPositionField["Direction"] = "char"
#投机套保标志
CQdpFtdcRspInvestorPositionField["HedgeFlag"] = "char"
#占用保证金
CQdpFtdcRspInvestorPositionField["UsedMargin"] = "float"
#总持仓量
CQdpFtdcRspInvestorPositionField["Position"] = "int"
#今日持仓成本
CQdpFtdcRspInvestorPositionField["PositionCost"] = "float"
#昨持仓量(不变值)
CQdpFtdcRspInvestorPositionField["YdPosition"] = "int"
#昨日持仓成本
CQdpFtdcRspInvestorPositionField["YdPositionCost"] = "float"
#冻结的保证金
CQdpFtdcRspInvestorPositionField["FrozenMargin"] = "float"
#开仓冻结持仓
CQdpFtdcRspInvestorPositionField["FrozenPosition"] = "int"
#平仓冻结持仓
CQdpFtdcRspInvestorPositionField["FrozenClosing"] = "int"
#冻结的权利金
CQdpFtdcRspInvestorPositionField["FrozenPremium"] = "float"
#最后一笔成交编号
CQdpFtdcRspInvestorPositionField["LastTradeID"] = "string"
#最后一笔本地报单编号
CQdpFtdcRspInvestorPositionField["LastOrderLocalID"] = "string"
#币种
CQdpFtdcRspInvestorPositionField["Currency"] = "string"
#持仓盈亏
CQdpFtdcRspInvestorPositionField["PositionProfit"] = "float"
#今持仓量
CQdpFtdcRspInvestorPositionField["TodayPosition"] = "int"
#今仓平仓冻结
CQdpFtdcRspInvestorPositionField["FrozenTodayClosing"] = "int"
structDict['CQdpFtdcRspInvestorPositionField'] = CQdpFtdcRspInvestorPositionField


#用户查询
CQdpFtdcQryUserField = {}
#交易用户代码
CQdpFtdcQryUserField["StartUserID"] = "string"
#交易用户代码
CQdpFtdcQryUserField["EndUserID"] = "string"
structDict['CQdpFtdcQryUserField'] = CQdpFtdcQryUserField


#用户
CQdpFtdcUserField = {}
#经纪公司编号
CQdpFtdcUserField["BrokerID"] = "string"
#用户代码
CQdpFtdcUserField["UserID"] = "string"
#用户登录密码
CQdpFtdcUserField["Password"] = "string"
#是否活跃
CQdpFtdcUserField["IsActive"] = "char"
#用户名称
CQdpFtdcUserField["UserName"] = "string"
#用户类型
CQdpFtdcUserField["UserType"] = "char"
#营业部
CQdpFtdcUserField["Department"] = "string"
#授权功能集
CQdpFtdcUserField["GrantFuncSet"] = "string"
structDict['CQdpFtdcUserField'] = CQdpFtdcUserField


#投资者手续费率查询
CQdpFtdcQryInvestorFeeField = {}
#经纪公司编号
CQdpFtdcQryInvestorFeeField["BrokerID"] = "string"
#用户代码
CQdpFtdcQryInvestorFeeField["UserID"] = "string"
#投资者编号
CQdpFtdcQryInvestorFeeField["InvestorID"] = "string"
#交易所代码
CQdpFtdcQryInvestorFeeField["ExchangeID"] = "string"
#合约代码
CQdpFtdcQryInvestorFeeField["InstrumentID"] = "string"
#投机套保标志
CQdpFtdcQryInvestorFeeField["HedgeFlag"] = "char"
structDict['CQdpFtdcQryInvestorFeeField'] = CQdpFtdcQryInvestorFeeField


#投资者手续费率
CQdpFtdcInvestorFeeField = {}
#经纪公司编号
CQdpFtdcInvestorFeeField["BrokerID"] = "string"
#交易所代码
CQdpFtdcInvestorFeeField["ExchangeID"] = "string"
#投资者编码
CQdpFtdcInvestorFeeField["InvestorID"] = "string"
#合约代码
CQdpFtdcInvestorFeeField["InstrumentID"] = "string"
#投机套保标志
CQdpFtdcInvestorFeeField["HedgeFlag"] = "char"
#开仓手续费按比例
CQdpFtdcInvestorFeeField["OpenFeeRate"] = "float"
#开仓手续费按手数
CQdpFtdcInvestorFeeField["OpenFeeAmt"] = "float"
#平仓手续费按比例
CQdpFtdcInvestorFeeField["OffsetFeeRate"] = "float"
#平仓手续费按手数
CQdpFtdcInvestorFeeField["OffsetFeeAmt"] = "float"
#平今仓手续费按比例
CQdpFtdcInvestorFeeField["OTFeeRate"] = "float"
#平今仓手续费按手数
CQdpFtdcInvestorFeeField["OTFeeAmt"] = "float"
structDict['CQdpFtdcInvestorFeeField'] = CQdpFtdcInvestorFeeField


#投资者保证金率查询
CQdpFtdcQryInvestorMarginField = {}
#经纪公司编号
CQdpFtdcQryInvestorMarginField["BrokerID"] = "string"
#用户代码
CQdpFtdcQryInvestorMarginField["UserID"] = "string"
#投资者编号
CQdpFtdcQryInvestorMarginField["InvestorID"] = "string"
#交易所代码
CQdpFtdcQryInvestorMarginField["ExchangeID"] = "string"
#合约代码
CQdpFtdcQryInvestorMarginField["InstrumentID"] = "string"
#投机套保标志
CQdpFtdcQryInvestorMarginField["HedgeFlag"] = "char"
structDict['CQdpFtdcQryInvestorMarginField'] = CQdpFtdcQryInvestorMarginField


#投资者保证金率
CQdpFtdcInvestorMarginField = {}
#经纪公司编号
CQdpFtdcInvestorMarginField["BrokerID"] = "string"
#交易所代码
CQdpFtdcInvestorMarginField["ExchangeID"] = "string"
#投资者编码
CQdpFtdcInvestorMarginField["InvestorID"] = "string"
#合约代码
CQdpFtdcInvestorMarginField["InstrumentID"] = "string"
#投机套保标志
CQdpFtdcInvestorMarginField["HedgeFlag"] = "char"
#多头占用保证金按比例
CQdpFtdcInvestorMarginField["LongMarginRate"] = "float"
#多头保证金按手数
CQdpFtdcInvestorMarginField["LongMarginAmt"] = "float"
#空头占用保证金按比例
CQdpFtdcInvestorMarginField["ShortMarginRate"] = "float"
#空头保证金按手数
CQdpFtdcInvestorMarginField["ShortMarginAmt"] = "float"
structDict['CQdpFtdcInvestorMarginField'] = CQdpFtdcInvestorMarginField


#交易所时间偏差查询请求
CQdpFtdcQryExchangeDiffTimeField = {}
#交易所代码
CQdpFtdcQryExchangeDiffTimeField["ExchangeID"] = "string"
structDict['CQdpFtdcQryExchangeDiffTimeField'] = CQdpFtdcQryExchangeDiffTimeField


#交易所时间偏差查询应答
CQdpFtdcRspExchangeDiffTimeField = {}
#交易日
CQdpFtdcRspExchangeDiffTimeField["TradingDay"] = "string"
#交易所代码
CQdpFtdcRspExchangeDiffTimeField["ExchangeID"] = "string"
#交易所时间
CQdpFtdcRspExchangeDiffTimeField["ExchangeTime"] = "string"
#偏差时间
CQdpFtdcRspExchangeDiffTimeField["DiffSnd"] = "int"
structDict['CQdpFtdcRspExchangeDiffTimeField'] = CQdpFtdcRspExchangeDiffTimeField


#查询签约银行请求
CQdpFtdcQryContractBankField = {}
#经纪公司编号
CQdpFtdcQryContractBankField["BrokerID"] = "string"
#交易员
CQdpFtdcQryContractBankField["UserID"] = "string"
#投资者编号
CQdpFtdcQryContractBankField["InvestorID"] = "string"
#币种
CQdpFtdcQryContractBankField["Currency"] = "string"
#银行代码
CQdpFtdcQryContractBankField["BankID"] = "string"
#银行分中心代码
CQdpFtdcQryContractBankField["BankBrchID"] = "string"
structDict['CQdpFtdcQryContractBankField'] = CQdpFtdcQryContractBankField


#查询签约银行应答
CQdpFtdcContractBankField = {}
#经纪公司编号
CQdpFtdcContractBankField["BrokerID"] = "string"
#投资者编号
CQdpFtdcContractBankField["InvestorID"] = "string"
#资金账号
CQdpFtdcContractBankField["AccountID"] = "string"
#币种
CQdpFtdcContractBankField["Currency"] = "string"
#银行代码
CQdpFtdcContractBankField["BankID"] = "string"
#银行分中心代码
CQdpFtdcContractBankField["BankBrchID"] = "string"
#银行简称
CQdpFtdcContractBankField["BankName"] = "string"
structDict['CQdpFtdcContractBankField'] = CQdpFtdcContractBankField


#期货发起查询银行余额请求
CQdpFtdcReqQueryAccountField = {}
#业务功能码
CQdpFtdcReqQueryAccountField["TradeCode"] = "string"
#银行代码
CQdpFtdcReqQueryAccountField["BankID"] = "string"
#银行分中心代码
CQdpFtdcReqQueryAccountField["BankBrchID"] = "string"
#经纪公司编号
CQdpFtdcReqQueryAccountField["BrokerID"] = "string"
#期商分支机构代码
CQdpFtdcReqQueryAccountField["BrokerBranchID"] = "string"
#交易日期
CQdpFtdcReqQueryAccountField["TradeDate"] = "string"
#交易时间
CQdpFtdcReqQueryAccountField["TradeTime"] = "string"
#银行流水号
CQdpFtdcReqQueryAccountField["BankSerial"] = "string"
#交易系统日期
CQdpFtdcReqQueryAccountField["TradingDay"] = "string"
#银期平台消息流水号
CQdpFtdcReqQueryAccountField["PlateSerial"] = "int"
#最后分片标志
CQdpFtdcReqQueryAccountField["LastFragment"] = "char"
#会话号
CQdpFtdcReqQueryAccountField["SessionID"] = "int"
#客户姓名
CQdpFtdcReqQueryAccountField["CustomerName"] = "string"
#证件类型
CQdpFtdcReqQueryAccountField["IdCardType"] = "string"
#证件号码
CQdpFtdcReqQueryAccountField["IdentifiedCardNo"] = "string"
#客户类型
CQdpFtdcReqQueryAccountField["CustType"] = "string"
#银行账号
CQdpFtdcReqQueryAccountField["BankAccount"] = "string"
#银行密码
CQdpFtdcReqQueryAccountField["BankPassWord"] = "string"
#资金账号
CQdpFtdcReqQueryAccountField["AccountID"] = "string"
#投资者编号
CQdpFtdcReqQueryAccountField["InvestorID"] = "string"
#期货密码
CQdpFtdcReqQueryAccountField["Password"] = "string"
#期货公司流水号
CQdpFtdcReqQueryAccountField["FutureSerial"] = "int"
#安装编号
CQdpFtdcReqQueryAccountField["InstallID"] = "int"
#交易员
CQdpFtdcReqQueryAccountField["UserID"] = "string"
#验证客户证件号码标志
CQdpFtdcReqQueryAccountField["VerifyCertNoFlag"] = "string"
#币种代码
CQdpFtdcReqQueryAccountField["Currency"] = "string"
#摘要
CQdpFtdcReqQueryAccountField["Digest"] = "string"
#银行账号类型
CQdpFtdcReqQueryAccountField["BankAccType"] = "char"
#渠道标志
CQdpFtdcReqQueryAccountField["DeviceID"] = "string"
#期货单位账号类型
CQdpFtdcReqQueryAccountField["BankSecuAccType"] = "char"
#期货公司银行编码
CQdpFtdcReqQueryAccountField["BankCodingForFuture"] = "string"
#期货单位账号
CQdpFtdcReqQueryAccountField["BankSecuAcc"] = "string"
#银行密码标志
CQdpFtdcReqQueryAccountField["BankPwdFlag"] = "char"
#期货资金密码核对标志
CQdpFtdcReqQueryAccountField["SecuPwdFlag"] = "char"
#交易柜员
CQdpFtdcReqQueryAccountField["OperNo"] = "string"
#请求编号
CQdpFtdcReqQueryAccountField["RequestID"] = "int"
#交易ID
CQdpFtdcReqQueryAccountField["TID"] = "int"
structDict['CQdpFtdcReqQueryAccountField'] = CQdpFtdcReqQueryAccountField


#查询转账流水请求
CQdpFtdcQryTransferSerialField = {}
#经纪公司编号
CQdpFtdcQryTransferSerialField["BrokerID"] = "string"
#交易员
CQdpFtdcQryTransferSerialField["UserID"] = "string"
#投资者编号
CQdpFtdcQryTransferSerialField["InvestorID"] = "string"
#资金账号
CQdpFtdcQryTransferSerialField["AccountID"] = "string"
#银行代码
CQdpFtdcQryTransferSerialField["BankID"] = "string"
#币种代码
CQdpFtdcQryTransferSerialField["Currency"] = "string"
structDict['CQdpFtdcQryTransferSerialField'] = CQdpFtdcQryTransferSerialField


#查询转账流水应答
CQdpFtdcTransferSerialField = {}
#银期平台消息流水号
CQdpFtdcTransferSerialField["PlateSerial"] = "int"
#交易日期
CQdpFtdcTransferSerialField["TradeDate"] = "string"
#交易系统日期
CQdpFtdcTransferSerialField["TradingDay"] = "string"
#交易时间
CQdpFtdcTransferSerialField["TradingTime"] = "string"
#业务功能码
CQdpFtdcTransferSerialField["TradeCode"] = "string"
#会话号
CQdpFtdcTransferSerialField["SessionID"] = "int"
#银行代码
CQdpFtdcTransferSerialField["BankID"] = "string"
#银行分支机构代码
CQdpFtdcTransferSerialField["BankBrchID"] = "string"
#银行账号类型
CQdpFtdcTransferSerialField["BankAccType"] = "char"
#银行账号
CQdpFtdcTransferSerialField["BankAccount"] = "string"
#币种代码
CQdpFtdcTransferSerialField["Currency"] = "string"
#银行流水号
CQdpFtdcTransferSerialField["BankSerial"] = "string"
#经纪公司编号
CQdpFtdcTransferSerialField["BrokerID"] = "string"
#期商分支机构代码
CQdpFtdcTransferSerialField["BrokerBranchID"] = "string"
#期货公司账号类型
CQdpFtdcTransferSerialField["FutureAccType"] = "char"
#资金账号
CQdpFtdcTransferSerialField["AccountID"] = "string"
#投资者编号
CQdpFtdcTransferSerialField["InvestorID"] = "string"
#期货公司流水号
CQdpFtdcTransferSerialField["FutureSerial"] = "int"
#证件类型
CQdpFtdcTransferSerialField["IdCardType"] = "string"
#证件号码
CQdpFtdcTransferSerialField["IdentifiedCardNo"] = "string"
#交易金额
CQdpFtdcTransferSerialField["TradeAmount"] = "float"
#应收客户费用
CQdpFtdcTransferSerialField["CustFee"] = "float"
#应收期货公司费用
CQdpFtdcTransferSerialField["BrokerFee"] = "float"
#有效标志
CQdpFtdcTransferSerialField["AvailabilityFlag"] = "char"
#操作员
CQdpFtdcTransferSerialField["OperatorCode"] = "string"
#新银行账号
CQdpFtdcTransferSerialField["BankNewAccount"] = "string"
#错误代码
CQdpFtdcTransferSerialField["ErrorID"] = "int"
#错误信息
CQdpFtdcTransferSerialField["ErrorMsg"] = "string"
structDict['CQdpFtdcTransferSerialField'] = CQdpFtdcTransferSerialField


#实时行情查询请求
CQdpFtdcQryMarketDataField = {}
#交易所代码
CQdpFtdcQryMarketDataField["ExchangeID"] = "string"
#合约代码
CQdpFtdcQryMarketDataField["InstrumentID"] = "string"
structDict['CQdpFtdcQryMarketDataField'] = CQdpFtdcQryMarketDataField


#实时行情查询应答
CQdpFtdcMarketDataField = {}
#交易日
CQdpFtdcMarketDataField["TradingDay"] = "string"
#交易所代码
CQdpFtdcMarketDataField["ExchangeID"] = "string"
#合约代码
CQdpFtdcMarketDataField["InstrumentID"] = "string"
#今开盘
CQdpFtdcMarketDataField["OpenPrice"] = "float"
#最高价
CQdpFtdcMarketDataField["HighestPrice"] = "float"
#最低价
CQdpFtdcMarketDataField["LowestPrice"] = "float"
#最新价
CQdpFtdcMarketDataField["LastPrice"] = "float"
#数量
CQdpFtdcMarketDataField["Volume"] = "int"
#成交金额
CQdpFtdcMarketDataField["Turnover"] = "float"
#跌停板价
CQdpFtdcMarketDataField["LowerLimitPrice"] = "float"
#涨停板价
CQdpFtdcMarketDataField["UpperLimitPrice"] = "float"
#持仓量
CQdpFtdcMarketDataField["OpenInterest"] = "int"
#昨收盘
CQdpFtdcMarketDataField["PreClosePrice"] = "float"
#昨持仓量
CQdpFtdcMarketDataField["PreOpenInterest"] = "int"
#昨结算
CQdpFtdcMarketDataField["PreSettlementPrice"] = "float"
#今结算
CQdpFtdcMarketDataField["SettlementPrice"] = "float"
#最后修改毫秒
CQdpFtdcMarketDataField["UpdateMillisec"] = "int"
#最后修改时间
CQdpFtdcMarketDataField["UpdateTime"] = "string"
structDict['CQdpFtdcMarketDataField'] = CQdpFtdcMarketDataField


#行情查询应答
CQdpFtdcRspMarketDataField = {}
#交易所代码
CQdpFtdcRspMarketDataField["ExchangeID"] = "string"
#交易日
CQdpFtdcRspMarketDataField["TradingDay"] = "string"
#结算组代码
CQdpFtdcRspMarketDataField["SettlementGroupID"] = "string"
#结算编号
CQdpFtdcRspMarketDataField["SettlementID"] = "int"
#昨结算
CQdpFtdcRspMarketDataField["PreSettlementPrice"] = "float"
#昨收盘
CQdpFtdcRspMarketDataField["PreClosePrice"] = "float"
#昨持仓量
CQdpFtdcRspMarketDataField["PreOpenInterest"] = "float"
#昨虚实度
CQdpFtdcRspMarketDataField["PreDelta"] = "float"
#今开盘
CQdpFtdcRspMarketDataField["OpenPrice"] = "float"
#最高价
CQdpFtdcRspMarketDataField["HighestPrice"] = "float"
#最低价
CQdpFtdcRspMarketDataField["LowestPrice"] = "float"
#今收盘
CQdpFtdcRspMarketDataField["ClosePrice"] = "float"
#涨停板价
CQdpFtdcRspMarketDataField["UpperLimitPrice"] = "float"
#跌停板价
CQdpFtdcRspMarketDataField["LowerLimitPrice"] = "float"
#今结算
CQdpFtdcRspMarketDataField["SettlementPrice"] = "float"
#今虚实度
CQdpFtdcRspMarketDataField["CurrDelta"] = "float"
#最新价
CQdpFtdcRspMarketDataField["LastPrice"] = "float"
#数量
CQdpFtdcRspMarketDataField["Volume"] = "int"
#成交金额
CQdpFtdcRspMarketDataField["Turnover"] = "float"
#持仓量
CQdpFtdcRspMarketDataField["OpenInterest"] = "float"
#申买价一
CQdpFtdcRspMarketDataField["BidPrice1"] = "float"
#申买量一
CQdpFtdcRspMarketDataField["BidVolume1"] = "int"
#申卖价一
CQdpFtdcRspMarketDataField["AskPrice1"] = "float"
#申卖量一
CQdpFtdcRspMarketDataField["AskVolume1"] = "int"
#合约代码
CQdpFtdcRspMarketDataField["InstrumentID"] = "string"
#最后修改时间
CQdpFtdcRspMarketDataField["UpdateTime"] = "string"
#最后修改毫秒
CQdpFtdcRspMarketDataField["UpdateMillisec"] = "int"
structDict['CQdpFtdcRspMarketDataField'] = CQdpFtdcRspMarketDataField


#客户库存查询
CQdpFtdcQryInventoryField = {}
#投资者编号
CQdpFtdcQryInventoryField["InvestorID"] = "string"
#品种代码
CQdpFtdcQryInventoryField["ProductID"] = "string"
structDict['CQdpFtdcQryInventoryField'] = CQdpFtdcQryInventoryField


#客户库存查询应答
CQdpFtdcInventoryField = {}
#经纪公司编号
CQdpFtdcInventoryField["BrokerID"] = "string"
#投资者编号
CQdpFtdcInventoryField["InvestorID"] = "string"
#交易所代码
CQdpFtdcInventoryField["ExchangeID"] = "string"
#品种代码
CQdpFtdcInventoryField["ProductID"] = "string"
#库存总量
CQdpFtdcInventoryField["TotalInventory"] = "float"
#可用库存
CQdpFtdcInventoryField["AvailInventory"] = "float"
#冻结库存
CQdpFtdcInventoryField["FrozenInventory"] = "float"
structDict['CQdpFtdcInventoryField'] = CQdpFtdcInventoryField


#金交所递延费率查询请求
CQdpFtdcQrySGEDeferRateField = {}
#合约代码
CQdpFtdcQrySGEDeferRateField["InstrumentID"] = "string"
structDict['CQdpFtdcQrySGEDeferRateField'] = CQdpFtdcQrySGEDeferRateField


#金交所递延费率查询应答
CQdpFtdcSGEDeferRateField = {}
#合约代码
CQdpFtdcSGEDeferRateField["InstrumentID"] = "string"
#交易所代码
CQdpFtdcSGEDeferRateField["ExchangeID"] = "string"
#交易日期
CQdpFtdcSGEDeferRateField["TradeDate"] = "string"
#支付方向
CQdpFtdcSGEDeferRateField["Direction"] = "char"
#递延费率
CQdpFtdcSGEDeferRateField["DeferRate"] = "float"
structDict['CQdpFtdcSGEDeferRateField'] = CQdpFtdcSGEDeferRateField


#成交
CQdpFtdcTradeField = {}
#交易日
CQdpFtdcTradeField["TradingDay"] = "string"
#经纪公司编号
CQdpFtdcTradeField["BrokerID"] = "string"
#交易所代码
CQdpFtdcTradeField["ExchangeID"] = "string"
#会员编号
CQdpFtdcTradeField["ParticipantID"] = "string"
#下单席位号
CQdpFtdcTradeField["SeatID"] = "string"
#投资者编号
CQdpFtdcTradeField["InvestorID"] = "string"
#客户号
CQdpFtdcTradeField["ClientID"] = "string"
#用户编号
CQdpFtdcTradeField["UserID"] = "string"
#成交编号
CQdpFtdcTradeField["TradeID"] = "string"
#报单编号
CQdpFtdcTradeField["OrderSysID"] = "string"
#本地报单编号
CQdpFtdcTradeField["UserOrderLocalID"] = "string"
#合约代码
CQdpFtdcTradeField["InstrumentID"] = "string"
#买卖方向
CQdpFtdcTradeField["Direction"] = "char"
#开平标志
CQdpFtdcTradeField["OffsetFlag"] = "char"
#投机套保标志
CQdpFtdcTradeField["HedgeFlag"] = "char"
#成交价格
CQdpFtdcTradeField["TradePrice"] = "float"
#成交数量
CQdpFtdcTradeField["TradeVolume"] = "int"
#成交时间
CQdpFtdcTradeField["TradeTime"] = "string"
#清算会员编号
CQdpFtdcTradeField["ClearingPartID"] = "string"
#成交金额
CQdpFtdcTradeField["TradeAmnt"] = "float"
#记录编号
CQdpFtdcTradeField["RecNum"] = "int"
structDict['CQdpFtdcTradeField'] = CQdpFtdcTradeField


#报单
CQdpFtdcOrderField = {}
#经纪公司编号
CQdpFtdcOrderField["BrokerID"] = "string"
#交易所代码
CQdpFtdcOrderField["ExchangeID"] = "string"
#系统报单编号
CQdpFtdcOrderField["OrderSysID"] = "string"
#投资者编号
CQdpFtdcOrderField["InvestorID"] = "string"
#用户代码
CQdpFtdcOrderField["UserID"] = "string"
#合约代码
CQdpFtdcOrderField["InstrumentID"] = "string"
#用户本地报单号
CQdpFtdcOrderField["UserOrderLocalID"] = "string"
#价格类型
CQdpFtdcOrderField["OrderPriceType"] = "char"
#买卖方向
CQdpFtdcOrderField["Direction"] = "char"
#开平标志
CQdpFtdcOrderField["OffsetFlag"] = "char"
#投机套保标志
CQdpFtdcOrderField["HedgeFlag"] = "char"
#价格
CQdpFtdcOrderField["LimitPrice"] = "float"
#数量
CQdpFtdcOrderField["Volume"] = "int"
#有效期类型
CQdpFtdcOrderField["TimeCondition"] = "char"
#GTD日期
CQdpFtdcOrderField["GTDDate"] = "string"
#成交量类型
CQdpFtdcOrderField["VolumeCondition"] = "char"
#最小成交量
CQdpFtdcOrderField["MinVolume"] = "int"
#止损价
CQdpFtdcOrderField["StopPrice"] = "float"
#强平原因
CQdpFtdcOrderField["ForceCloseReason"] = "char"
#自动挂起标志
CQdpFtdcOrderField["IsAutoSuspend"] = "int"
#业务单元
CQdpFtdcOrderField["BusinessUnit"] = "string"
#用户自定义域
CQdpFtdcOrderField["UserCustom"] = "string"
#营业部代码
CQdpFtdcOrderField["BranchID"] = "string"
#记录编号
CQdpFtdcOrderField["RecNum"] = "int"
#业务类别
CQdpFtdcOrderField["BusinessType"] = "char"
#交易日
CQdpFtdcOrderField["TradingDay"] = "string"
#会员编号
CQdpFtdcOrderField["ParticipantID"] = "string"
#客户号
CQdpFtdcOrderField["ClientID"] = "string"
#下单席位号
CQdpFtdcOrderField["SeatID"] = "string"
#插入时间
CQdpFtdcOrderField["InsertTime"] = "string"
#本地报单编号
CQdpFtdcOrderField["OrderLocalID"] = "string"
#报单来源
CQdpFtdcOrderField["OrderSource"] = "char"
#报单状态
CQdpFtdcOrderField["OrderStatus"] = "char"
#撤销时间
CQdpFtdcOrderField["CancelTime"] = "string"
#撤单用户编号
CQdpFtdcOrderField["CancelUserID"] = "string"
#今成交数量
CQdpFtdcOrderField["VolumeTraded"] = "int"
#剩余数量
CQdpFtdcOrderField["VolumeRemain"] = "int"
#前置编号
CQdpFtdcOrderField["FrontID"] = "int"
#会话编号
CQdpFtdcOrderField["SessionID"] = "int"
structDict['CQdpFtdcOrderField'] = CQdpFtdcOrderField


#数据流回退
CQdpFtdcFlowMessageCancelField = {}
#序列系列号
CQdpFtdcFlowMessageCancelField["SequenceSeries"] = "int"
#交易日
CQdpFtdcFlowMessageCancelField["TradingDay"] = "string"
#数据中心代码
CQdpFtdcFlowMessageCancelField["DataCenterID"] = "int"
#回退起始序列号
CQdpFtdcFlowMessageCancelField["StartSequenceNo"] = "int"
#回退结束序列号
CQdpFtdcFlowMessageCancelField["EndSequenceNo"] = "int"
structDict['CQdpFtdcFlowMessageCancelField'] = CQdpFtdcFlowMessageCancelField


#信息分发
CQdpFtdcDisseminationField = {}
#序列系列号
CQdpFtdcDisseminationField["SequenceSeries"] = "int"
#序列号
CQdpFtdcDisseminationField["SequenceNo"] = "int"
structDict['CQdpFtdcDisseminationField'] = CQdpFtdcDisseminationField


#出入金结果
CQdpFtdcInvestorAccountDepositResField = {}
#经纪公司编号
CQdpFtdcInvestorAccountDepositResField["BrokerID"] = "string"
#投资者编号
CQdpFtdcInvestorAccountDepositResField["InvestorID"] = "string"
#资金帐号
CQdpFtdcInvestorAccountDepositResField["AccountID"] = "string"
#资金流水号
CQdpFtdcInvestorAccountDepositResField["AccountSeqNo"] = "string"
#连续递增的总资金流水号
CQdpFtdcInvestorAccountDepositResField["AccountInsideSeqNo"] = "string"
#金额
CQdpFtdcInvestorAccountDepositResField["Amount"] = "float"
#出入金方向
CQdpFtdcInvestorAccountDepositResField["AmountDirection"] = "char"
#可用资金
CQdpFtdcInvestorAccountDepositResField["Available"] = "float"
#结算准备金
CQdpFtdcInvestorAccountDepositResField["Balance"] = "float"
#用户代码
CQdpFtdcInvestorAccountDepositResField["UserID"] = "string"
structDict['CQdpFtdcInvestorAccountDepositResField'] = CQdpFtdcInvestorAccountDepositResField


#QDP警告消息通知
CQdpFtdcMessageNotifyInfoField = {}
#经纪公司编号
CQdpFtdcMessageNotifyInfoField["BrokerID"] = "string"
#修改用户编号
CQdpFtdcMessageNotifyInfoField["UserID"] = "string"
#投资者编号
CQdpFtdcMessageNotifyInfoField["InvestorID"] = "string"
#交易所代码
CQdpFtdcMessageNotifyInfoField["ExchangeID"] = "string"
#累加次数
CQdpFtdcMessageNotifyInfoField["Nums"] = "int"
#业务类别
CQdpFtdcMessageNotifyInfoField["BusinessType"] = "char"
#警告信息
CQdpFtdcMessageNotifyInfoField["WarnMsg"] = "string"
structDict['CQdpFtdcMessageNotifyInfoField'] = CQdpFtdcMessageNotifyInfoField


#行情基础属性
CQdpFtdcMarketDataBaseField = {}
#交易日
CQdpFtdcMarketDataBaseField["TradingDay"] = "string"
#结算组代码
CQdpFtdcMarketDataBaseField["SettlementGroupID"] = "string"
#结算编号
CQdpFtdcMarketDataBaseField["SettlementID"] = "int"
#昨结算
CQdpFtdcMarketDataBaseField["PreSettlementPrice"] = "float"
#昨收盘
CQdpFtdcMarketDataBaseField["PreClosePrice"] = "float"
#昨持仓量
CQdpFtdcMarketDataBaseField["PreOpenInterest"] = "float"
#昨虚实度
CQdpFtdcMarketDataBaseField["PreDelta"] = "float"
structDict['CQdpFtdcMarketDataBaseField'] = CQdpFtdcMarketDataBaseField


#行情静态属性
CQdpFtdcMarketDataStaticField = {}
#今开盘
CQdpFtdcMarketDataStaticField["OpenPrice"] = "float"
#最高价
CQdpFtdcMarketDataStaticField["HighestPrice"] = "float"
#最低价
CQdpFtdcMarketDataStaticField["LowestPrice"] = "float"
#今收盘
CQdpFtdcMarketDataStaticField["ClosePrice"] = "float"
#涨停板价
CQdpFtdcMarketDataStaticField["UpperLimitPrice"] = "float"
#跌停板价
CQdpFtdcMarketDataStaticField["LowerLimitPrice"] = "float"
#今结算
CQdpFtdcMarketDataStaticField["SettlementPrice"] = "float"
#今虚实度
CQdpFtdcMarketDataStaticField["CurrDelta"] = "float"
structDict['CQdpFtdcMarketDataStaticField'] = CQdpFtdcMarketDataStaticField


#行情最新成交属性
CQdpFtdcMarketDataLastMatchField = {}
#最新价
CQdpFtdcMarketDataLastMatchField["LastPrice"] = "float"
#数量
CQdpFtdcMarketDataLastMatchField["Volume"] = "int"
#成交金额
CQdpFtdcMarketDataLastMatchField["Turnover"] = "float"
#持仓量
CQdpFtdcMarketDataLastMatchField["OpenInterest"] = "float"
structDict['CQdpFtdcMarketDataLastMatchField'] = CQdpFtdcMarketDataLastMatchField


#行情最优价属性
CQdpFtdcMarketDataBestPriceField = {}
#申买价一
CQdpFtdcMarketDataBestPriceField["BidPrice1"] = "float"
#申买量一
CQdpFtdcMarketDataBestPriceField["BidVolume1"] = "int"
#申卖价一
CQdpFtdcMarketDataBestPriceField["AskPrice1"] = "float"
#申卖量一
CQdpFtdcMarketDataBestPriceField["AskVolume1"] = "int"
structDict['CQdpFtdcMarketDataBestPriceField'] = CQdpFtdcMarketDataBestPriceField


#行情申买二、三属性
CQdpFtdcMarketDataBid23Field = {}
#申买价二
CQdpFtdcMarketDataBid23Field["BidPrice2"] = "float"
#申买量二
CQdpFtdcMarketDataBid23Field["BidVolume2"] = "int"
#申买价三
CQdpFtdcMarketDataBid23Field["BidPrice3"] = "float"
#申买量三
CQdpFtdcMarketDataBid23Field["BidVolume3"] = "int"
structDict['CQdpFtdcMarketDataBid23Field'] = CQdpFtdcMarketDataBid23Field


#行情申卖二、三属性
CQdpFtdcMarketDataAsk23Field = {}
#申卖价二
CQdpFtdcMarketDataAsk23Field["AskPrice2"] = "float"
#申卖量二
CQdpFtdcMarketDataAsk23Field["AskVolume2"] = "int"
#申卖价三
CQdpFtdcMarketDataAsk23Field["AskPrice3"] = "float"
#申卖量三
CQdpFtdcMarketDataAsk23Field["AskVolume3"] = "int"
structDict['CQdpFtdcMarketDataAsk23Field'] = CQdpFtdcMarketDataAsk23Field


#行情申买四、五属性
CQdpFtdcMarketDataBid45Field = {}
#申买价四
CQdpFtdcMarketDataBid45Field["BidPrice4"] = "float"
#申买量四
CQdpFtdcMarketDataBid45Field["BidVolume4"] = "int"
#申买价五
CQdpFtdcMarketDataBid45Field["BidPrice5"] = "float"
#申买量五
CQdpFtdcMarketDataBid45Field["BidVolume5"] = "int"
structDict['CQdpFtdcMarketDataBid45Field'] = CQdpFtdcMarketDataBid45Field


#行情申卖四、五属性
CQdpFtdcMarketDataAsk45Field = {}
#申卖价四
CQdpFtdcMarketDataAsk45Field["AskPrice4"] = "float"
#申卖量四
CQdpFtdcMarketDataAsk45Field["AskVolume4"] = "int"
#申卖价五
CQdpFtdcMarketDataAsk45Field["AskPrice5"] = "float"
#申卖量五
CQdpFtdcMarketDataAsk45Field["AskVolume5"] = "int"
structDict['CQdpFtdcMarketDataAsk45Field'] = CQdpFtdcMarketDataAsk45Field


#行情更新时间属性
CQdpFtdcMarketDataUpdateTimeField = {}
#合约代码
CQdpFtdcMarketDataUpdateTimeField["InstrumentID"] = "string"
#最后修改时间
CQdpFtdcMarketDataUpdateTimeField["UpdateTime"] = "string"
#最后修改毫秒
CQdpFtdcMarketDataUpdateTimeField["UpdateMillisec"] = "int"
structDict['CQdpFtdcMarketDataUpdateTimeField'] = CQdpFtdcMarketDataUpdateTimeField


#深度行情
CQdpFtdcDepthMarketDataField = {}
#交易日
CQdpFtdcDepthMarketDataField["TradingDay"] = "string"
#结算组代码
CQdpFtdcDepthMarketDataField["SettlementGroupID"] = "string"
#结算编号
CQdpFtdcDepthMarketDataField["SettlementID"] = "int"
#昨结算
CQdpFtdcDepthMarketDataField["PreSettlementPrice"] = "float"
#昨收盘
CQdpFtdcDepthMarketDataField["PreClosePrice"] = "float"
#昨持仓量
CQdpFtdcDepthMarketDataField["PreOpenInterest"] = "float"
#昨虚实度
CQdpFtdcDepthMarketDataField["PreDelta"] = "float"
#今开盘
CQdpFtdcDepthMarketDataField["OpenPrice"] = "float"
#最高价
CQdpFtdcDepthMarketDataField["HighestPrice"] = "float"
#最低价
CQdpFtdcDepthMarketDataField["LowestPrice"] = "float"
#今收盘
CQdpFtdcDepthMarketDataField["ClosePrice"] = "float"
#涨停板价
CQdpFtdcDepthMarketDataField["UpperLimitPrice"] = "float"
#跌停板价
CQdpFtdcDepthMarketDataField["LowerLimitPrice"] = "float"
#今结算
CQdpFtdcDepthMarketDataField["SettlementPrice"] = "float"
#今虚实度
CQdpFtdcDepthMarketDataField["CurrDelta"] = "float"
#最新价
CQdpFtdcDepthMarketDataField["LastPrice"] = "float"
#数量
CQdpFtdcDepthMarketDataField["Volume"] = "int"
#成交金额
CQdpFtdcDepthMarketDataField["Turnover"] = "float"
#持仓量
CQdpFtdcDepthMarketDataField["OpenInterest"] = "float"
#申买价一
CQdpFtdcDepthMarketDataField["BidPrice1"] = "float"
#申买量一
CQdpFtdcDepthMarketDataField["BidVolume1"] = "int"
#申卖价一
CQdpFtdcDepthMarketDataField["AskPrice1"] = "float"
#申卖量一
CQdpFtdcDepthMarketDataField["AskVolume1"] = "int"
#申买价二
CQdpFtdcDepthMarketDataField["BidPrice2"] = "float"
#申买量二
CQdpFtdcDepthMarketDataField["BidVolume2"] = "int"
#申买价三
CQdpFtdcDepthMarketDataField["BidPrice3"] = "float"
#申买量三
CQdpFtdcDepthMarketDataField["BidVolume3"] = "int"
#申卖价二
CQdpFtdcDepthMarketDataField["AskPrice2"] = "float"
#申卖量二
CQdpFtdcDepthMarketDataField["AskVolume2"] = "int"
#申卖价三
CQdpFtdcDepthMarketDataField["AskPrice3"] = "float"
#申卖量三
CQdpFtdcDepthMarketDataField["AskVolume3"] = "int"
#申买价四
CQdpFtdcDepthMarketDataField["BidPrice4"] = "float"
#申买量四
CQdpFtdcDepthMarketDataField["BidVolume4"] = "int"
#申买价五
CQdpFtdcDepthMarketDataField["BidPrice5"] = "float"
#申买量五
CQdpFtdcDepthMarketDataField["BidVolume5"] = "int"
#申卖价四
CQdpFtdcDepthMarketDataField["AskPrice4"] = "float"
#申卖量四
CQdpFtdcDepthMarketDataField["AskVolume4"] = "int"
#申卖价五
CQdpFtdcDepthMarketDataField["AskPrice5"] = "float"
#申卖量五
CQdpFtdcDepthMarketDataField["AskVolume5"] = "int"
#合约代码
CQdpFtdcDepthMarketDataField["InstrumentID"] = "string"
#最后修改时间
CQdpFtdcDepthMarketDataField["UpdateTime"] = "string"
#最后修改毫秒
CQdpFtdcDepthMarketDataField["UpdateMillisec"] = "int"
#交易所代码
CQdpFtdcDepthMarketDataField["ExchangeID"] = "string"
structDict['CQdpFtdcDepthMarketDataField'] = CQdpFtdcDepthMarketDataField


#订阅合约的相关信息
CQdpFtdcSpecificInstrumentField = {}
#合约代码
CQdpFtdcSpecificInstrumentField["InstrumentID"] = "string"
structDict['CQdpFtdcSpecificInstrumentField'] = CQdpFtdcSpecificInstrumentField


#共享内存行情查询
CQdpFtdcShmDepthMarketDataField = {}
#合约代码
CQdpFtdcShmDepthMarketDataField["InstrumentID"] = "string"
#IP地址
CQdpFtdcShmDepthMarketDataField["IPAddress"] = "string"
#订阅号
CQdpFtdcShmDepthMarketDataField["TopicID"] = "int"
structDict['CQdpFtdcShmDepthMarketDataField'] = CQdpFtdcShmDepthMarketDataField


#交易所代码
CQdpFtdcMarketDataExchangeIDField = {}
#交易所代码
CQdpFtdcMarketDataExchangeIDField["ExchangeID"] = "string"
structDict['CQdpFtdcMarketDataExchangeIDField'] = CQdpFtdcMarketDataExchangeIDField


#TOPIC查询
CQdpFtdcTopicSearchField = {}
#订阅号
CQdpFtdcTopicSearchField["TopicID"] = "int"
structDict['CQdpFtdcTopicSearchField'] = CQdpFtdcTopicSearchField


#合约状态
CQdpFtdcQmdInstrumentStateField = {}
#交易所代码
CQdpFtdcQmdInstrumentStateField["ExchangeID"] = "string"
#合约代码
CQdpFtdcQmdInstrumentStateField["InstrumentID"] = "string"
#合约交易状态
CQdpFtdcQmdInstrumentStateField["InstrumentStatus"] = "char"
structDict['CQdpFtdcQmdInstrumentStateField'] = CQdpFtdcQmdInstrumentStateField





