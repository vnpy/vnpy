# encoding: UTF-8

typedefDict = {}

#########################################################################
###@author 中泰证券股份有限公司
###@file xtp_api_data_type.h
###@brief 定义兼容数据基本类型
#########################################################################

#########################################################################
###@enum XTP_PROTOCOL_TYPE 是一个通讯传输协议方式
#########################################################################
typedefDict["XTP_PROTOCOL_TYPE"] = "int"

### 存放证券代码的字符串长度
XTP_TICKER_LEN = 16

#########################################################################
###@enum XTP_EXCHANGE_TYPE 是交易所类型
#########################################################################
typedefDict["XTP_EXCHANGE_TYPE"] = "int"

##########################################################################
###市场类型
##########################################################################
typedefDict["XTP_MARKET_TYPE"] = "int"


#########################################################################
###@enum XTP_PRICE_TYPE 是一个价格类型
#########################################################################
typedefDict["XTP_PRICE_TYPE"] = "int"



#########################################################################
###@enum XTP_SIDE_TYPE 是一个买卖方向类型
#########################################################################
typedefDict["XTP_SIDE_TYPE"] = "int"

#########################################################################
###@enum XTP_ORDER_ACTION_STATUS_TYPE 是一个报单操作状态类型
#########################################################################
typedefDict["XTP_ORDER_ACTION_STATUS_TYPE"] = "int"

#########################################################################
###XTP_ORDER_STATUS_TYPE是一个报单状态类型
#########################################################################
typedefDict["XTP_ORDER_STATUS_TYPE"] = "int"

#########################################################################
###XTP_ORDER_SUBMIT_STATUS_TYPE是一个报单提交状态类型
#########################################################################
typedefDict["XTP_ORDER_SUBMIT_STATUS_TYPE"] = "int"


#########################################################################
###@enum XTP_TE_RESUME_TYPE 是一个私有流重传方式
#########################################################################
typedefDict["XTP_TE_RESUME_TYPE"] = "int"



#########################################################################
###TXTPErrorIDType是一个错误代码类型
#########################################################################
typedefDict["TXTPErrorIDType"] = "int"

#########################################################################
###TXTPErrorMsgType是一个错误信息类型
#########################################################################
typedefDict["TXTPErrorMsgType"] = "string"

#########################################################################
###TXTPExchangeIDType是一个交易所代码类型
#########################################################################
typedefDict["TXTPExchangeIDType"] = "int"

#########################################################################
###TXTPExchangeNameType是一个交易所名称类型
#########################################################################
typedefDict["TXTPExchangeNameType"] = "string"

#########################################################################
###TXTPExchangePropertyType是一个交易所属性类型
#########################################################################
typedefDict["TXTPExchangePropertyType"] = "char"

###正常
XTP_EXP_Normal = '0'
###根据成交生成报单
XTP_EXP_GenOrderByTrade = '1'

#########################################################################
###TXTPExchangeConnectStatusType是一个交易所连接状态类型
#########################################################################
typedefDict["TXTPExchangeConnectStatusType"] = "char"

###没有任何连接
XTP_ECS_NoConnection = '1'
###已经发出合约查询请求
XTP_ECS_QryInstrumentSent = '2'
###已经获取信息
XTP_ECS_GotInformation = '9'



#########################################################################
###TXTPDateType是一个日期类型
#########################################################################
typedefDict["TXTPDateType"] = "string"

#########################################################################
###TXTPTimeType是一个时间类型
#########################################################################
typedefDict["TXTPTimeType"] = "string"

#########################################################################
###TXTPInstrumentIDType是一个合约代码类型
#########################################################################
typedefDict["TXTPInstrumentIDType"] = "string"

#########################################################################
###TXTPProductNameType是一个产品名称类型
#########################################################################
typedefDict["TXTPProductNameType"] = "string"

#########################################################################
###TXTPProductClassType是一个产品类型类型
#########################################################################
typedefDict["TXTPProductClassType"] = "char"

###期货
XTP_PC_Futures = '1'
###期权
XTP_PC_Options = '2'
###组合
XTP_PC_Combination = '3'
###即期
XTP_PC_Spot = '4'
###期转现
XTP_PC_EFP = '5'
###证券A股
XTP_PC_StockA = '6'
###证券B股
XTP_PC_StockB = '7'
###ETF
XTP_PC_ETF = '8'
###ETF申赎
XTP_PC_ETFPurRed = '9'



#########################################################################
###TXTPVolumeMultipleType是一个合约数量乘数类型
#########################################################################
typedefDict["TXTPVolumeMultipleType"] = "int"

#########################################################################
###TXTPPriceType是一个价格类型
#########################################################################
typedefDict["TXTPPriceType"] = "float"

#########################################################################
###TXTPVolumeType是一个数量类型
#########################################################################
typedefDict["TXTPVolumeType"] = "int"

#########################################################################
###TXTPPositionTypeType是一个持仓类型类型
#########################################################################
typedefDict["TXTPPositionTypeType"] = "char"

###净持仓
XTP_PT_Net = '1'
###综合持仓
XTP_PT_Gross = '2'



#########################################################################
###TXTPPositionDateTypeType是一个持仓日期类型类型
#########################################################################
typedefDict["TXTPPositionDateTypeType"] = "char"

###使用历史持仓
XTP_PDT_UseHistory = '1'
###不使用历史持仓
XTP_PDT_NoUseHistory = '2'



#########################################################################
###TXTPExchangeInstIDType是一个合约在交易所的代码类型
#########################################################################
typedefDict["TXTPExchangeInstIDType"] = "string"

#########################################################################
###TXTPYearType是一个年份类型
#########################################################################
typedefDict["TXTPYearType"] = "int"

#########################################################################
###TXTPMonthType是一个月份类型
#########################################################################
typedefDict["TXTPMonthType"] = "int"

#########################################################################
###TXTPInstLifePhaseType是一个合约生命周期状态类型
#########################################################################
typedefDict["TXTPInstLifePhaseType"] = "char"

###未上市
XTP_IP_NotStart = '0'
###上市
XTP_IP_Started = '1'
###停牌
XTP_IP_Pause = '2'
###到期
XTP_IP_Expired = '3'



#########################################################################
###TXTPBoolType是一个布尔型类型
#########################################################################
typedefDict["TXTPBoolType"] = "int"

#########################################################################
###TXTPRightModelIDType是一个股票权限模版代码类型
#########################################################################
typedefDict["TXTPRightModelIDType"] = "string"

#########################################################################
###TXTPRightModelNameType是一个股票权限模版名称类型
#########################################################################
typedefDict["TXTPRightModelNameType"] = "string"

#########################################################################
###TXTPPosTradeTypeType是一个持仓交易类型类型
#########################################################################
typedefDict["TXTPPosTradeTypeType"] = "char"

###今日新增持仓能卖出
XTP_PTT_CanSelTodayPos = '1'
###今日新增持仓不能卖出
XTP_PTT_CannotSellTodayPos = '2'



#########################################################################
###TXTPTraderIDType是一个交易所交易员代码类型
#########################################################################
typedefDict["TXTPTraderIDType"] = "string"

#########################################################################
###TXTPParticipantIDType是一个会员代码类型
#########################################################################
typedefDict["TXTPParticipantIDType"] = "string"

#########################################################################
###TXTPPasswordType是一个密码类型
#########################################################################
typedefDict["TXTPPasswordType"] = "string"

#########################################################################
###TXTPBrokerIDType是一个经纪公司代码类型
#########################################################################
typedefDict["TXTPBrokerIDType"] = "string"

#########################################################################
###TXTPOrderLocalIDType是一个本地报单编号类型
#########################################################################
typedefDict["TXTPOrderLocalIDType"] = "string"

#########################################################################
###TXTPBrokerAbbrType是一个经纪公司简称类型
#########################################################################
typedefDict["TXTPBrokerAbbrType"] = "string"

#########################################################################
###TXTPBrokerNameType是一个经纪公司名称类型
#########################################################################
typedefDict["TXTPBrokerNameType"] = "string"

#########################################################################
###TXTPInvestorIDType是一个投资者代码类型
#########################################################################
typedefDict["TXTPInvestorIDType"] = "string"

#########################################################################
###TXTPPartyNameType是一个参与人名称类型
#########################################################################
typedefDict["TXTPPartyNameType"] = "string"

#########################################################################
###TXTPIdCardTypeType是一个证件类型类型
#########################################################################
typedefDict["TXTPIdCardTypeType"] = "char"

###组织机构代码
XTP_ICT_EID = '0'
###身份证
XTP_ICT_IDCard = '1'
###军官证
XTP_ICT_OfficerIDCard = '2'
###警官证
XTP_ICT_PoliceIDCard = '3'
###士兵证
XTP_ICT_SoldierIDCard = '4'
###户口簿
XTP_ICT_HouseholdRegister = '5'
###护照
XTP_ICT_Passport = '6'
###台胞证
XTP_ICT_TaiwanCompatriotIDCard = '7'
###回乡证
XTP_ICT_HomeComingCard = '8'
###营业执照号
XTP_ICT_LicenseNo = '9'
###税务登记号
XTP_ICT_TaxNo = 'A'
###其他证件
XTP_ICT_OtherCard = 'x'



#########################################################################
###TXTPIdentifiedCardNoType是一个证件号码类型
#########################################################################
typedefDict["TXTPIdentifiedCardNoType"] = "string"

#########################################################################
###TXTPClientIDType是一个交易编码类型
#########################################################################
typedefDict["TXTPClientIDType"] = "string"

#########################################################################
###TXTPAccountIDType是一个投资者帐号类型
#########################################################################
typedefDict["TXTPAccountIDType"] = "string"

#########################################################################
###TXTPClientTypeType是一个交易编码类型类型
#########################################################################
typedefDict["TXTPClientTypeType"] = "char"

###普通
XTP_CLT_Normal = '1'
###信用交易
XTP_CLT_Credit = '2'
###衍生品账户
XTP_CLT_Derive = '3'
###其他类型
XTP_CLT_Other = '4'



#########################################################################
###TXTPInvestorGroupNameType是一个投资者分组名称类型
#########################################################################
typedefDict["TXTPInvestorGroupNameType"] = "string"

#########################################################################
###TXTPUserIDType是一个用户代码类型
#########################################################################
typedefDict["TXTPUserIDType"] = "string"

#########################################################################
###TXTPUserNameType是一个用户名称类型
#########################################################################
typedefDict["TXTPUserNameType"] = "string"

#########################################################################
###TXTPFunctionCodeType是一个功能代码类型
#########################################################################
typedefDict["TXTPFunctionCodeType"] = "char"

###强制用户登出
XTP_FC_ForceUserLogout = '2'
###变更管理用户口令
XTP_FC_UserPasswordUpdate = '3'
###变更经纪公司口令
XTP_FC_BrokerPasswordUpdate = '4'
###变更投资者口令
XTP_FC_InvestorPasswordUpdate = '5'
###报单插入
XTP_FC_OrderInsert = '6'
###报单操作
XTP_FC_OrderAction = '7'
###同步系统数据
XTP_FC_SyncSystemData = '8'
###同步经纪公司数据
XTP_FC_SyncBrokerData = '9'
###超级查询
XTP_FC_SuperQuery = 'B'
###报单插入
XTP_FC_ParkedOrderInsert = 'C'
###报单操作
XTP_FC_ParkedOrderAction = 'D'
###同步动态令牌
XTP_FC_SyncOTP = 'E'
###未知单操作
XTP_FC_UnkownOrderAction = 'F'
###转托管
XTP_FC_DepositoryTransfer = 'G'
###余券划转
XTP_FC_ExcessStockTransfer = 'H'



#########################################################################
###TXTPUserTypeType是一个用户类型类型
#########################################################################
typedefDict["TXTPUserTypeType"] = "char"

###投资者
XTP_UT_Investor = '0'
###操作员
XTP_UT_Operator = '1'
###管理员
XTP_UT_SuperUser = '2'



#########################################################################
###TXTPBrokerFunctionCodeType是一个经纪公司功能代码类型
#########################################################################
typedefDict["TXTPBrokerFunctionCodeType"] = "char"

###强制用户登出
XTP_BFC_ForceUserLogout = '1'
###变更用户口令
XTP_BFC_UserPasswordUpdate = '2'
###同步经纪公司数据
XTP_BFC_SyncBrokerData = '3'
###报单插入
XTP_BFC_OrderInsert = '5'
###报单操作
XTP_BFC_OrderAction = '6'
###全部查询
XTP_BFC_AllQuery = '7'
###未知单操作
XTP_BFC_UnkownOrderAction = '8'
###转托管
XTP_BFC_DepositoryTransfer = '9'
###余券划转
XTP_BFC_ExcessStockTransfer = 'A'
###资金内转
XTP_BFC_FundInterTransfer = 'B'
###系统功能：登入#登出#修改密码等
XTP_BFC_log = 'a'
###基本查询：查询基础数据，如合约，交易所等常量
XTP_BFC_BaseQry = 'b'
###交易查询：如查成交，委托
XTP_BFC_TradeQry = 'c'
###交易功能：报单，撤单
XTP_BFC_Trade = 'd'
###转账
XTP_BFC_Virement = 'e'
###查询#管理：查询会话，踢人等
XTP_BFC_Session = 'g'
###同步动态令牌
XTP_BFC_SyncOTP = 'E'



#########################################################################
###TXTPCurrencyCodeType是一个币种类型
#########################################################################
typedefDict["TXTPCurrencyCodeType"] = "string"

#########################################################################
###TXTPMoneyType是一个资金类型
#########################################################################
typedefDict["TXTPMoneyType"] = "float"

#########################################################################
###TXTPRatioType是一个比率类型
#########################################################################
typedefDict["TXTPRatioType"] = "float"

#########################################################################
###TXTPAccountTypeType是一个账户类型类型
#########################################################################
typedefDict["TXTPAccountTypeType"] = "char"

###普通账户
XTP_AcT_Normal = '1'
###信用账户
XTP_AcT_Credit = '2'
###衍生品账户
XTP_AcT_Derive = '3'
###其他类型
XTP_AcT_Other = '4'



#########################################################################
###TXTPDepartmentRangeType是一个投资者范围类型
#########################################################################
typedefDict["TXTPDepartmentRangeType"] = "char"

###所有
XTP_DR_All = '1'
###组织架构
XTP_DR_Group = '2'
###单一投资者
XTP_DR_Single = '3'



#########################################################################
###TXTPUserRightTypeType是一个客户权限类型类型
#########################################################################
typedefDict["TXTPUserRightTypeType"] = "char"

###登录
XTP_URT_Logon = '1'
###银期转帐
XTP_URT_Transfer = '2'
###邮寄结算单
XTP_URT_EMail = '3'
###传真结算单
XTP_URT_Fax = '4'
###条件单
XTP_URT_ConditionOrder = '5'



#########################################################################
###TXTPProductInfoType是一个产品信息类型
#########################################################################
typedefDict["TXTPProductInfoType"] = "string"

#########################################################################
###TXTPAuthCodeType是一个客户端认证码类型
#########################################################################
typedefDict["TXTPAuthCodeType"] = "string"

#########################################################################
###TXTPLargeVolumeType是一个大额数量类型
#########################################################################
typedefDict["TXTPLargeVolumeType"] = "float"

#########################################################################
###TXTPMillisecType是一个时间（毫秒）类型
#########################################################################
typedefDict["TXTPMillisecType"] = "int"

#########################################################################
###TXTPHedgeFlagType是一个投机套保标志类型
#########################################################################
typedefDict["TXTPHedgeFlagType"] = "char"

###投机
XTP_HF_Speculation = '1'
###套保
XTP_HF_Hedge = '3'



#########################################################################
###TXTPDirectionType是一个买卖方向类型
#########################################################################
typedefDict["TXTPDirectionType"] = "char"

###买
XTP_D_Buy = '0'
###卖
XTP_D_Sell = '1'


###ETF申购
XTP_D_ETFPur = '2'
###ETF赎回
XTP_D_ETFRed = '3'
###现金替代，只用作回报
XTP_D_CashIn = '4'
###债券入库
XTP_D_PledgeBondIn = '5'
###债券出库
XTP_D_PledgeBondOut = '6'
###配股
XTP_D_Rationed = '7'
###转托管
XTP_D_DepositoryTransfer = '8'
###信用账户配股
XTP_D_CreditRationed = '9'
###担保品买入
XTP_D_BuyCollateral = 'A'
###担保品卖出
XTP_D_SellCollateral = 'B'
###担保品转入
XTP_D_CollateralTransferIn = 'C'
###担保品转出
XTP_D_CollateralTransferOut = 'D'
###融资买入
XTP_D_MarginTrade = 'E'
###融券卖出
XTP_D_ShortSell = 'F'
###卖券还款
XTP_D_RepayMargin = 'G'
###买券还券

XTP_D_RepayStock = 'H'
###直接还款
XTP_D_DirectRepayMargin = 'I'
###直接还券
XTP_D_DirectRepayStock = 'J'
###余券划转
XTP_D_ExcessStockTransfer = 'K'
###OF申购
XTP_D_OFPur = 'L'
###OF赎回
XTP_D_OFRed = 'M'
###SF拆分
XTP_D_SFSplit = 'N'
###SF合并
XTP_D_SFMerge = 'O'
###备兑
XTP_D_Covered = 'P'
###证券冻结(开)#解冻(平)
XTP_D_Freeze = 'Q'
###行权
XTP_D_Execute = 'R'
###CB回售
XTP_D_CBRed = 'S'
###CB转股
XTP_D_CBConv = 'T'*/



#########################################################################
###TXTPTradeIDType是一个成交编号类型
#########################################################################
typedefDict["TXTPTradeIDType"] = "string"

#########################################################################
###TXTPTradeTypeType是一个成交类型类型
#########################################################################
typedefDict["TXTPTradeTypeType"] = "char"

###普通成交
XTP_TRDT_Common = '0'
###期权执行
XTP_TRDT_OptionsExecution = '1'
###OTC成交
XTP_TRDT_OTC = '2'
###期转现衍生成交
XTP_TRDT_EFPDerived = '3'
###组合衍生成交
XTP_TRDT_CombinationDerived = '4'
###ETF申购
XTP_TRDT_EFTPurchase = '5'
###ETF赎回
XTP_TRDT_EFTRedem = '6'



#########################################################################
###TXTPCreationredemptionStatusType是一个基金当天申购赎回状态类型
#########################################################################
typedefDict["TXTPCreationredemptionStatusType"] = "char"

###不允许申购赎回
XTP_CDS_Forbidden = '0'
###表示允许申购和赎回
XTP_CDS_Allow = '1'
###允许申购、不允许赎回
XTP_CDS_OnlyPurchase = '2'
###不允许申购、允许赎回
XTP_CDS_OnlyRedeem = '3'



#########################################################################
###TXTPETFCurrenceReplaceStatusType是一个ETF现金替代标志类型
#########################################################################
typedefDict["TXTPETFCurrenceReplaceStatusType"] = "char"

###禁止现金替代
XTP_ETFCRS_Forbidden = '0'
###可以现金替代
XTP_ETFCRS_Allow = '1'
###必须现金替代
XTP_ETFCRS_Force = '2'
###跨市场股票退补现金替代
XTP_ETFCRS_CrossMarketComp = '3'
###跨市场必须现金替代
XTP_ETFCRS_CrossMarketFroce = '4'



#########################################################################
###TXTPInterestType是一个利息类型
#########################################################################
typedefDict["TXTPInterestType"] = "float"

#########################################################################
###TXTPRepurchaseMaxTimesType是一个正回购放大倍数类型
#########################################################################
typedefDict["TXTPRepurchaseMaxTimesType"] = "float"

#########################################################################
###TXTPCapitalStockTypeType是一个股本类型类型
#########################################################################
typedefDict["TXTPCapitalStockTypeType"] = "char"

###总通股本
XTP_CPTSTOCK_TOTALSTOCK = '1'
###流通股本
XTP_CPTSTOCK_CIRCULATION = '2'



#########################################################################
###TXTPMarginPriceTypeType是一个保证金价格类型类型
#########################################################################
typedefDict["TXTPMarginPriceTypeType"] = "char"

###昨结算价
XTP_MPT_PreSettlementPrice = '1'
###最新价
XTP_MPT_SettlementPrice = '2'
###成交均价
XTP_MPT_AveragePrice = '3'
###开仓价
XTP_MPT_OpenPrice = '4'



#########################################################################
###TXTPAlgorithmType是一个盈亏算法类型
#########################################################################
typedefDict["TXTPAlgorithmType"] = "char"

###浮盈浮亏都计算
XTP_AG_All = '1'
###浮盈不计，浮亏计
XTP_AG_OnlyLost = '2'
###浮盈计，浮亏不计
XTP_AG_OnlyGain = '3'
###浮盈浮亏都不计算
XTP_AG_None = '4'



#########################################################################
###TXTPIncludeCloseProfitType是一个是否包含平仓盈利类型
#########################################################################
typedefDict["TXTPIncludeCloseProfitType"] = "char"

###包含平仓盈利
XTP_ICP_Include = '0'
###不包含平仓盈利
XTP_ICP_NotInclude = '2'



#########################################################################
###TXTPAllWithoutTradeType是一个是否受可提比例限制类型
#########################################################################
typedefDict["TXTPAllWithoutTradeType"] = "char"

###不受可提比例限制
XTP_AWT_Enable = '0'
###受可提比例限制
XTP_AWT_Disable = '2'
###无仓不受可提比例限制
XTP_AWT_NoHoldEnable = '3'



#########################################################################
###TXTPHandlePositionAlgoIDType是一个持仓处理算法编号类型
#########################################################################
typedefDict["TXTPHandlePositionAlgoIDType"] = "char"

###基本
XTP_HPA_Base = '1'
###非交易
XTP_HPA_NoneTrade = '4'
###证券
XTP_HPA_Stock = '5'



#########################################################################
###TXTPTradeParamIDType是一个交易系统参数代码类型
#########################################################################
typedefDict["TXTPTradeParamIDType"] = "char"

###系统加密算法
XTP_TPID_EncryptionStandard = 'E'
###用户最大会话数
XTP_TPID_SingleUserSessionMaxNum = 'S'
###最大连续登录失败数
XTP_TPID_LoginFailMaxNum = 'L'
###是否强制认证
XTP_TPID_IsAuthForce = 'A'
###是否生成用户事件
XTP_TPID_GenUserEvent = 'G'
###起始报单本地编号
XTP_TPID_StartOrderLocalID = 'O'
###融资融券买券还券算法
XTP_TPID_RepayStockAlgo = 'R'
###衍生品账户资金提取线
XTP_TPID_DeriveWithdrawRatio = 'D'



#########################################################################
###TXTPSettlementParamValueType是一个参数代码值类型
#########################################################################
typedefDict["TXTPSettlementParamValueType"] = "string"

#########################################################################
###TXTPMemoType是一个备注类型
#########################################################################
typedefDict["TXTPMemoType"] = "string"

#########################################################################
###TXTPPriorityType是一个优先级类型
#########################################################################
typedefDict["TXTPPriorityType"] = "int"

#########################################################################
###TXTPOrderRefType是一个报单引用类型
#########################################################################
typedefDict["TXTPOrderRefType"] = "string"

#########################################################################
###TXTPMarketIDType是一个市场代码类型
#########################################################################
typedefDict["TXTPMarketIDType"] = "string"

#########################################################################
###TXTPMacAddressType是一个Mac地址类型
#########################################################################
typedefDict["TXTPMacAddressType"] = "string"

#########################################################################
###TXTPInstrumentNameType是一个合约名称类型
#########################################################################
typedefDict["TXTPInstrumentNameType"] = "string"

#########################################################################
###TXTPOrderSysIDType是一个报单编号类型
#########################################################################
typedefDict["TXTPOrderSysIDType"] = "string"

#########################################################################
###TXTPIPAddressType是一个IP地址类型
#########################################################################
typedefDict["TXTPIPAddressType"] = "string"

#########################################################################
###TXTPIPPortType是一个IP端口类型
#########################################################################
typedefDict["TXTPIPPortType"] = "int"

#########################################################################
###TXTPProtocolInfoType是一个协议信息类型
#########################################################################
typedefDict["TXTPProtocolInfoType"] = "string"

#########################################################################
###TXTPDepositSeqNoType是一个出入金流水号类型
#########################################################################
typedefDict["TXTPDepositSeqNoType"] = "string"

#########################################################################
###TXTPSystemNameType是一个系统名称类型
#########################################################################
typedefDict["TXTPSystemNameType"] = "string"

#########################################################################
###TXTPInvestorRangeType是一个投资者范围类型
#########################################################################
typedefDict["TXTPInvestorRangeType"] = "char"

###所有
XTP_IR_All = '1'
###投资者组
XTP_IR_Group = '2'
###单一投资者
XTP_IR_Single = '3'



#########################################################################
###TXTPDataSyncStatusType是一个数据同步状态类型
#########################################################################
typedefDict["TXTPDataSyncStatusType"] = "char"

###未同步
XTP_DS_Asynchronous = '1'
###同步中
XTP_DS_Synchronizing = '2'
###已同步
XTP_DS_Synchronized = '3'



#########################################################################
###TXTPTraderConnectStatusType是一个交易所交易员连接状态类型
#########################################################################
typedefDict["TXTPTraderConnectStatusType"] = "char"

###没有任何连接
XTP_TCS_NotConnected = '1'
###已经连接
XTP_TCS_Connected = '2'
###已经发出合约查询请求
XTP_TCS_QryInstrumentSent = '3'
###订阅私有流
XTP_TCS_SubPrivateFlow = '4'



#########################################################################
###TXTPOrderActionStatusType是一个报单操作状态类型
#########################################################################
typedefDict["TXTPOrderActionStatusType"] = "char"

###已经提交
XTP_OAS_Submitted = 'a'
###已经接受
XTP_OAS_Accepted = 'b'
###已经被拒绝
XTP_OAS_Rejected = 'c'



#########################################################################
###TXTPOrderStatusType是一个报单状态类型
#########################################################################
typedefDict["TXTPOrderStatusType"] = "char"

###全部成交
XTP_OST_AllTraded = '0'
###部分成交还在队列中
XTP_OST_PartTradedQueueing = '1'
###部分成交不在队列中
XTP_OST_PartTradedNotQueueing = '2'
###未成交还在队列中
XTP_OST_NoTradeQueueing = '3'
###未成交不在队列中
XTP_OST_NoTradeNotQueueing = '4'
###撤单
XTP_OST_Canceled = '5'
###未知
XTP_OST_Unknown = 'a'
###尚未触发
XTP_OST_NotTouched = 'b'
###已触发
XTP_OST_Touched = 'c'



#########################################################################
###TXTPOrderSubmitStatusType是一个报单提交状态类型
#########################################################################
typedefDict["TXTPOrderSubmitStatusType"] = "char"

###已经提交
XTP_OSS_InsertSubmitted = '0'
###撤单已经提交
XTP_OSS_CancelSubmitted = '1'
###修改已经提交
XTP_OSS_ModifySubmitted = '2'
###已经接受
XTP_OSS_Accepted = '3'
###报单已经被拒绝
XTP_OSS_InsertRejected = '4'
###撤单已经被拒绝
XTP_OSS_CancelRejected = '5'
###改单已经被拒绝
XTP_OSS_ModifyRejected = '6'



#########################################################################
###TXTPPositionDateType是一个持仓日期类型
#########################################################################
typedefDict["TXTPPositionDateType"] = "char"

###今日持仓
XTP_PSD_Today = '1'
###历史持仓
XTP_PSD_History = '2'



#########################################################################
###TXTPTradingRoleType是一个交易角色类型
#########################################################################
typedefDict["TXTPTradingRoleType"] = "char"

###代理
XTP_ER_Broker = '1'
###自营
XTP_ER_Host = '2'
###做市商
XTP_ER_Maker = '3'



#########################################################################
###TXTPPosiDirectionType是一个持仓多空方向类型
#########################################################################
typedefDict["TXTPPosiDirectionType"] = "char"

###净
XTP_PD_Net = '1'
###多头
XTP_PD_Long = '2'
###空头
XTP_PD_Short = '3'
###备兑
XTP_PD_Covered = '4'



#########################################################################
###TXTPOrderPriceTypeType是一个报单价格条件类型
#########################################################################
typedefDict["TXTPOrderPriceTypeType"] = "char"

###即时成交剩余撤销市价单
XTP_OPT_AnyPrice = '1'
###限价
XTP_OPT_LimitPrice = '2'
###最优五档即时成交剩余撤销市价单
XTP_OPT_BestPrice = '3'
###最优五档即时成交剩余转限价市价单
XTP_OPT_BestLimitPrice = '4'
###全部成交或撤销市价单
XTP_OPT_AllPrice = '5'
###本方最优价格市价单
XTP_OPT_ForwardBestPrice = '6'
###对方最优价格市价单
XTP_OPT_ReverseBestPrice = '7'
###即时成交剩余转限价市价单
XTP_OPT_Any2LimitPrice = '8'
###全部成交或撤销限价单
XTP_OPT_AllLimitPrice = '9'

###激活A股网络密码服务代码
XTP_OPT_ActiveANetPassSvrCode = 'G'
###注销A股网络密码服务代码
XTP_OPT_InactiveANetPassSvrCode = 'H'
###激活B股网络密码服务代码
XTP_OPT_ActiveBNetPassSvrCode = 'I'
###注销B股网络密码服务代码
XTP_OPT_InactiveBNetPassSvrCode = 'J'
###回购注销
XTP_OPT_Repurchase = 'K'
###指定撤销
XTP_OPT_DesignatedCancel = 'L'
###指定登记
XTP_OPT_Designated = 'M'
###证券参与申购
XTP_OPT_SubscribingShares = 'N'
###证券参与配股
XTP_OPT_Split = 'O'
###要约收购登记
XTP_OPT_TenderOffer = 'P'
###要约收购撤销
XTP_OPT_TenderOfferCancel = 'Q'
###证券投票
XTP_OPT_Ballot = 'R'
###可转债转换登记
XTP_OPT_ConvertibleBondsConvet = 'S'
###可转债回售登记
XTP_OPT_ConvertibleBondsRepurchase = 'T'
###权证行权
XTP_OPT_Exercise = 'U'
###开放式基金申购
XTP_OPT_PurchasingFunds = 'V'
###开放式基金赎回
XTP_OPT_RedemingFunds = 'W'
###开放式基金认购
XTP_OPT_SubscribingFunds = 'X'
###开放式基金转托管转出
XTP_OPT_LOFIssue = 'Y'
###开放式基金设置分红方式
XTP_OPT_LOFSetBonusType = 'Z'
###开放式基金转换为其他基金
XTP_OPT_LOFConvert = 'a'
###债券入库
XTP_OPT_DebentureStockIn = 'b'
###债券出库
XTP_OPT_DebentureStockOut = 'c'
###ETF申购
XTP_OPT_PurchasesETF = 'd'
###ETF赎回
XTP_OPT_RedeemETF = 'e'*/



#########################################################################
###TXTPOffsetFlagType是一个开平标志类型
#########################################################################
typedefDict["TXTPOffsetFlagType"] = "char"

###开仓
XTP_OF_Open = '0'
###平仓
XTP_OF_Close = '1'
###强平
XTP_OF_ForceClose = '2'
###平今
XTP_OF_CloseToday = '3'
###平昨
XTP_OF_CloseYesterday = '4'
###强减
XTP_OF_ForceOff = '5'
###本地强平
XTP_OF_LocalForceClose = '6'



#########################################################################
###TXTPForceCloseReasonType是一个强平原因类型
#########################################################################
typedefDict["TXTPForceCloseReasonType"] = "char"

###非强平
XTP_FCC_NotForceClose = '0'
###资金不足
XTP_FCC_LackDeposit = '1'
###客户超仓
XTP_FCC_ClientOverPositionLimit = '2'
###会员超仓
XTP_FCC_MemberOverPositionLimit = '3'
###持仓非整数倍
XTP_FCC_NotMultiple = '4'
###违规
XTP_FCC_Violation = '5'
###其它
XTP_FCC_Other = '6'
###自然人临近交割
XTP_FCC_PersonDeliv = '7'



#########################################################################
###TXTPOrderTypeType是一个报单类型类型
#########################################################################
typedefDict["TXTPOrderTypeType"] = "char"

###正常
XTP_ORDT_Normal = '0'
###报价衍生
XTP_ORDT_DeriveFromQuote = '1'
###组合衍生
XTP_ORDT_DeriveFromCombination = '2'
###组合报单
XTP_ORDT_Combination = '3'
###条件单
XTP_ORDT_ConditionalOrder = '4'
###互换单
XTP_ORDT_Swap = '5'



#########################################################################
###TXTPTimeConditionType是一个有效期类型类型
#########################################################################
typedefDict["TXTPTimeConditionType"] = "char"

###立即完成，否则撤销
XTP_TC_IOC = '1'
###本节有效
XTP_TC_GFS = '2'
###当日有效
XTP_TC_GFD = '3'
###指定日期前有效
XTP_TC_GTD = '4'
###撤销前有效
XTP_TC_GTC = '5'
###集合竞价有效
XTP_TC_GFA = '6'



#########################################################################
###TXTPVolumeConditionType是一个成交量类型类型
#########################################################################
typedefDict["TXTPVolumeConditionType"] = "char"

###任何数量
XTP_VC_AV = '1'
###最小数量
XTP_VC_MV = '2'
###全部数量
XTP_VC_CV = '3'



#########################################################################
###TXTPContingentConditionType是一个触发条件类型
#########################################################################
typedefDict["TXTPContingentConditionType"] = "char"

###立即
XTP_CC_Immediately = '1'
###止损
XTP_CC_Touch = '2'
###止赢
XTP_CC_TouchProfit = '3'
###预埋单
XTP_CC_ParkedOrder = '4'
###最新价大于条件价
XTP_CC_LastPriceGreaterThanStopPrice = '5'
###最新价大于等于条件价
XTP_CC_LastPriceGreaterEqualStopPrice = '6'
###最新价小于条件价
XTP_CC_LastPriceLesserThanStopPrice = '7'
###最新价小于等于条件价
XTP_CC_LastPriceLesserEqualStopPrice = '8'
###卖一价大于条件价
XTP_CC_AskPriceGreaterThanStopPrice = '9'
###卖一价大于等于条件价
XTP_CC_AskPriceGreaterEqualStopPrice = 'A'
###卖一价小于条件价
XTP_CC_AskPriceLesserThanStopPrice = 'B'
###卖一价小于等于条件价
XTP_CC_AskPriceLesserEqualStopPrice = 'C'
###买一价大于条件价
XTP_CC_BidPriceGreaterThanStopPrice = 'D'
###买一价大于等于条件价
XTP_CC_BidPriceGreaterEqualStopPrice = 'E'
###买一价小于条件价
XTP_CC_BidPriceLesserThanStopPrice = 'F'
###买一价小于等于条件价
XTP_CC_BidPriceLesserEqualStopPrice = 'H'



#########################################################################
###TXTPActionFlagType是一个操作标志类型
#########################################################################
typedefDict["TXTPActionFlagType"] = "char"

###删除
XTP_AF_Delete = '0'
###修改
XTP_AF_Modify = '3'



#########################################################################
###TXTPTradingRightType是一个交易权限类型
#########################################################################
typedefDict["TXTPTradingRightType"] = "char"

###可以交易
XTP_TR_Allow = '0'
###不能交易
XTP_TR_Forbidden = '2'



#########################################################################
###TXTPOrderSourceType是一个报单来源类型
#########################################################################
typedefDict["TXTPOrderSourceType"] = "char"

###来自参与者
XTP_OSRC_Participant = '0'
###来自管理员
XTP_OSRC_Administrator = '1'



#########################################################################
###TXTPPriceSourceType是一个成交价来源类型
#########################################################################
typedefDict["TXTPPriceSourceType"] = "char"

###前成交价
XTP_PSRC_LastPrice = '0'
###买委托价
XTP_PSRC_Buy = '1'
###卖委托价
XTP_PSRC_Sell = '2'



#########################################################################
###TXTPOrderActionRefType是一个报单操作引用类型
#########################################################################
typedefDict["TXTPOrderActionRefType"] = "int"

#########################################################################
###TXTPFrontIDType是一个前置编号类型
#########################################################################
typedefDict["TXTPFrontIDType"] = "int"

#########################################################################
###TXTPSessionIDType是一个会话编号类型
#########################################################################
typedefDict["TXTPSessionIDType"] = "int"

#########################################################################
###TXTPInstallIDType是一个安装编号类型
#########################################################################
typedefDict["TXTPInstallIDType"] = "int"

#########################################################################
###TXTPSequenceNoType是一个序号类型
#########################################################################
typedefDict["TXTPSequenceNoType"] = "int"

#########################################################################
###TXTPRequestIDType是一个请求编号类型
#########################################################################
typedefDict["TXTPRequestIDType"] = "int"

#########################################################################
###TXTPCombOffsetFlagType是一个组合开平标志类型
#########################################################################
typedefDict["TXTPCombOffsetFlagType"] = "string"

#########################################################################
###TXTPCombHedgeFlagType是一个组合投机套保标志类型
#########################################################################
typedefDict["TXTPCombHedgeFlagType"] = "string"

#########################################################################
###TXTPSequenceSeriesType是一个序列系列号类型
#########################################################################
typedefDict["TXTPSequenceSeriesType"] = "int"

#########################################################################
###TXTPCommPhaseNoType是一个通讯时段编号类型
#########################################################################
typedefDict["TXTPCommPhaseNoType"] = "int"

#########################################################################
###TXTPUserEventTypeType是一个用户事件类型类型
#########################################################################
typedefDict["TXTPUserEventTypeType"] = "char"

###登录
XTP_UET_Login = '1'
###登出
XTP_UET_Logout = '2'
###交易成功
XTP_UET_Trading = '3'
###交易失败
XTP_UET_TradingError = '4'
###修改密码
XTP_UET_UpdatePassword = '5'
###客户端认证
XTP_UET_Authenticate = '6'
###其他
XTP_UET_Other = '9'



#########################################################################
###TXTPUserEventInfoType是一个用户事件信息类型
#########################################################################
typedefDict["TXTPUserEventInfoType"] = "string"

#########################################################################
###TXTPOTPTypeType是一个动态令牌类型类型
#########################################################################
typedefDict["TXTPOTPTypeType"] = "char"

###无动态令牌
XTP_OTP_NONE = '0'
###时间令牌
XTP_OTP_TOTP = '1'



#########################################################################
###TXTPTradeSourceType是一个成交来源类型
#########################################################################
typedefDict["TXTPTradeSourceType"] = "char"

###来自交易所普通回报
XTP_TSRC_NORMAL = '0'
###来自查询
XTP_TSRC_QUERY = '1'



#########################################################################
###TXTPBranchIDType是一个营业部编号类型
#########################################################################
typedefDict["TXTPBranchIDType"] = "string"

#########################################################################
###TXTPStockPriceType是一个证券交易价格类型
#########################################################################
typedefDict["TXTPStockPriceType"] = "string"

#########################################################################
###TXTPRightModelIDType是一个股票权限模版代码类型
#########################################################################
typedefDict["TXTPRightModelIDType"] = "string"

#########################################################################
###TXTPSerialNumberType是一个序列号类型
#########################################################################
typedefDict["TXTPSerialNumberType"] = "string"

#########################################################################
###TXTPInstrumentRangeType是一个股票权限分类类型
#########################################################################
typedefDict["TXTPInstrumentRangeType"] = "char"

###所有
XTP_INR_All = '1'
###产品
XTP_INR_Product = '2'
###股票权限模版
XTP_INR_Model = '3'
###股票
XTP_INR_Stock = '4'
###市场
XTP_INR_Market = '5'



#########################################################################
###TXTPBusinessUnitType是一个业务单元类型
#########################################################################
typedefDict["TXTPBusinessUnitType"] = "string"

#########################################################################
###TXTPOTPVendorsIDType是一个动态令牌提供商类型
#########################################################################
typedefDict["TXTPOTPVendorsIDType"] = "string"

#########################################################################
###TXTPLastDriftType是一个上次OTP漂移值类型
#########################################################################
typedefDict["TXTPLastDriftType"] = "int"

#########################################################################
###TXTPLastSuccessType是一个上次OTP成功值类型
#########################################################################
typedefDict["TXTPLastSuccessType"] = "int"

#########################################################################
###TXTPAuthKeyType是一个令牌密钥类型
#########################################################################
typedefDict["TXTPAuthKeyType"] = "string"

#########################################################################
###TXTPUserSessionHashType是一个用户会话Hash值类型
#########################################################################
typedefDict["TXTPUserSessionHashType"] = "int"

#########################################################################
###TXTPStockTradeTypeType是一个证券交易类型类型
#########################################################################
typedefDict["TXTPStockTradeTypeType"] = "char"

###可交易证券
XTP_STT_Stock = '0'
###买入网络密码服务
XTP_STT_BuyNetService = '1'
###回购注销
XTP_STT_CancelRepurchase = '2'
###指定撤销
XTP_STT_CancelRegister = '3'
###指定登记
XTP_STT_Register = '4'
###买入发行申购
XTP_STT_PurchaseIssue = '5'
###卖出配股
XTP_STT_Allotment = '6'
###卖出要约收购
XTP_STT_SellTender = '7'
###买入要约收购
XTP_STT_BuyTender = '8'
###网上投票
XTP_STT_NetVote = '9'
###卖出可转债回售
XTP_STT_SellConvertibleBonds = 'a'
###权证行权代码
XTP_STT_OptionExecute = 'b'
###开放式基金申购
XTP_STT_PurchaseOF = 'c'
###开放式基金赎回
XTP_STT_RedeemOF = 'd'
###开放式基金认购
XTP_STT_SubscribeOF = 'e'
###开放式基金转托管转出
XTP_STT_OFCustodianTranfer = 'f'
###开放式基金分红设置
XTP_STT_OFDividendConfig = 'g'
###开放式基金转成其他基金
XTP_STT_OFTransfer = 'h'
###债券入库
XTP_STT_BondsIn = 'i'
###债券出库
XTP_STT_BondsOut = 'j'
###EFT申购
XTP_STT_PurchaseETF = 'k'
###EFT赎回
XTP_STT_RedeemETF = 'l'
###可转债回售登记
XTP_STT_ConvertibleRegister = 'm'



#########################################################################
###TXTPHandleTradingAccountAlgoIDType是一个资金处理算法编号类型
#########################################################################
typedefDict["TXTPHandleTradingAccountAlgoIDType"] = "char"

###基本
XTP_HTAA_Base = '1'



#########################################################################
###TXTPStockWthType是一个股票使用流水号类型
#########################################################################
typedefDict["TXTPStockWthType"] = "int"

#########################################################################
###TXTPStockSeqType是一个股票使用流水号类型
#########################################################################
typedefDict["TXTPStockSeqType"] = "string"

#########################################################################
###TXTPWTFSType是一个委托方式类型
#########################################################################
typedefDict["TXTPWTFSType"] = "int"

#########################################################################
###TXTPWTLBType是一个委托类别类型
#########################################################################
typedefDict["TXTPWTLBType"] = "int"

#########################################################################
###TXTPWTRQType是一个委托日期类型
#########################################################################
typedefDict["TXTPWTRQType"] = "int"

#########################################################################
###TXTPINTEGERType是一个一般整型类型
#########################################################################
typedefDict["TXTPINTEGERType"] = "int"

#########################################################################
###TXTPINT3Type是一个三位数整型类型
#########################################################################
typedefDict["TXTPINT3Type"] = "int"

#########################################################################
###TXTPINT6Type是一个六位数整型类型
#########################################################################
typedefDict["TXTPINT6Type"] = "int"

#########################################################################
###TXTPINT12Type是一个十二位数整型类型
#########################################################################
typedefDict["TXTPINT12Type"] = "int"

#########################################################################
###TXTPCHAR1Type是一个一字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR1Type"] = "string"

#########################################################################
###TXTPCHAR2Type是一个二字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR2Type"] = "string"

#########################################################################
###TXTPCHAR3Type是一个三字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR3Type"] = "string"

#########################################################################
###TXTPCHAR4Type是一个四字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR4Type"] = "string"

#########################################################################
###TXTPCHAR5Type是一个五字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR5Type"] = "string"

#########################################################################
###TXTPCHAR6Type是一个六字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR6Type"] = "string"

#########################################################################
###TXTPCHAR8Type是一个八字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR8Type"] = "string"

#########################################################################
###TXTPCHAR10Type是一个十字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR10Type"] = "string"

#########################################################################
###TXTPCHAR11Type是一个十一字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR11Type"] = "string"

#########################################################################
###TXTPCHAR12Type是一个十二字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR12Type"] = "string"

#########################################################################
###TXTPCHAR13Type是一个十三字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR13Type"] = "string"

#########################################################################
###TXTPCHAR14Type是一个十四字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR14Type"] = "string"

#########################################################################
###TXTPCHAR16Type是一个十六字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR16Type"] = "string"

#########################################################################
###TXTPCHAR19Type是一个十九字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR19Type"] = "string"

#########################################################################
###TXTPCHAR20Type是一个二十字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR20Type"] = "string"

#########################################################################
###TXTPCHAR21Type是一个二十一字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR21Type"] = "string"

#########################################################################
###TXTPCHAR23Type是一个二十三字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR23Type"] = "string"

#########################################################################
###TXTPCHAR30Type是一个三十字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR30Type"] = "string"

#########################################################################
###TXTPCHAR32Type是一个三十二字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR32Type"] = "string"

#########################################################################
###TXTPCHAR50Type是一个五十字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR50Type"] = "string"

#########################################################################
###TXTPCHAR64Type是一个六十四字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR64Type"] = "string"

#########################################################################
###TXTPCHAR65Type是一个六十五字节CHAR类型
#########################################################################
typedefDict["TXTPCHAR65Type"] = "string"

#########################################################################
###TXTPVCHAR4Type是一个四字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR4Type"] = "string"

#########################################################################
###TXTPVCHAR6Type是一个六字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR6Type"] = "string"

#########################################################################
###TXTPVCHAR8Type是一个八字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR8Type"] = "string"

#########################################################################
###TXTPVCHAR10Type是一个十字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR10Type"] = "string"

#########################################################################
###TXTPVCHAR12Type是一个十二字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR12Type"] = "string"

#########################################################################
###TXTPVCHAR16Type是一个十六字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR16Type"] = "string"

#########################################################################
###TXTPVCHAR20Type是一个二十字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR20Type"] = "string"

#########################################################################
###TXTPVCHAR30Type是一个三十字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR30Type"] = "string"

#########################################################################
###TXTPVCHAR50Type是一个五十字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR50Type"] = "string"

#########################################################################
###TXTPVCHAR60Type是一个六十字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR60Type"] = "string"

#########################################################################
###TXTPVCHAR65Type是一个六十五字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR65Type"] = "string"

#########################################################################
###TXTPVCHAR80Type是一个八十字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR80Type"] = "string"

#########################################################################
###TXTPVCHAR84Type是一个八十四字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR84Type"] = "string"

#########################################################################
###TXTPVCHAR255Type是一个二五五字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR255Type"] = "string"

#########################################################################
###TXTPVCHAR1024Type是一个一零二四字节VCHAR类型
#########################################################################
typedefDict["TXTPVCHAR1024Type"] = "string"

#########################################################################
###TXTPREAL8P3Type是一个八点三实型类型
#########################################################################
typedefDict["TXTPREAL8P3Type"] = "float"

#########################################################################
###TXTPREAL9P3Type是一个九点三实型类型
#########################################################################
typedefDict["TXTPREAL9P3Type"] = "float"

#########################################################################
###TXTPREAL9P6Type是一个九点六实型类型
#########################################################################
typedefDict["TXTPREAL9P6Type"] = "float"

#########################################################################
###TXTPREAL10P4Type是一个十点四实型类型
#########################################################################
typedefDict["TXTPREAL10P4Type"] = "float"

#########################################################################
###TXTPREAL16P2Type是一个十六点二实型类型
#########################################################################
typedefDict["TXTPREAL16P2Type"] = "float"

#########################################################################
###TXTPREAL16P8Type是一个十六点八实型类型
#########################################################################
typedefDict["TXTPREAL16P8Type"] = "float"

#########################################################################
###TXTPREAL22P2Type是一个二十二点二实型类型
#########################################################################
typedefDict["TXTPREAL22P2Type"] = "float"

#########################################################################
###TXTPCommandNoType是一个DB命令序号类型
#########################################################################
typedefDict["TXTPCommandNoType"] = "int"

#########################################################################
###TXTPCommandTypeType是一个DB命令类型类型
#########################################################################
typedefDict["TXTPCommandTypeType"] = "string"

#########################################################################
###TXTPSettlementGroupIDType是一个结算组代码类型
#########################################################################
typedefDict["TXTPSettlementGroupIDType"] = "string"

#########################################################################
###TXTPFieldNameType是一个字段名类型
#########################################################################
typedefDict["TXTPFieldNameType"] = "string"

#########################################################################
###TXTPFieldContentType是一个字段内容类型
#########################################################################
typedefDict["TXTPFieldContentType"] = "string"

#########################################################################
###TXTPBankIDType是一个银行代码类型
#########################################################################
typedefDict["TXTPBankIDType"] = "string"

#########################################################################
###TXTPBankNameType是一个银行名称类型
#########################################################################
typedefDict["TXTPBankNameType"] = "string"

#########################################################################
###TXTPBankBrchIDType是一个银行分中心代码类型
#########################################################################
typedefDict["TXTPBankBrchIDType"] = "string"

#########################################################################
###TXTPLiberSerialType是一个Liber系统流水号类型
#########################################################################
typedefDict["TXTPLiberSerialType"] = "int"

#########################################################################
###TXTPRoleIDType是一个角色编号类型
#########################################################################
typedefDict["TXTPRoleIDType"] = "string"

#########################################################################
###TXTPRoleNameType是一个角色名称类型
#########################################################################
typedefDict["TXTPRoleNameType"] = "string"

#########################################################################
###TXTPDescriptionType是一个描述类型
#########################################################################
typedefDict["TXTPDescriptionType"] = "string"

#########################################################################
###TXTPFunctionIDType是一个功能代码类型
#########################################################################
typedefDict["TXTPFunctionIDType"] = "string"

#########################################################################
###TXTPBillNoType是一个票据号类型
#########################################################################
typedefDict["TXTPBillNoType"] = "string"

#########################################################################
###TXTPFundIOTypeType是一个出入金类型类型
#########################################################################
typedefDict["TXTPFundIOTypeType"] = "char"

###出入金
XTP_FIOT_FundIO = '1'
###银期转帐
XTP_FIOT_Transfer = '2'



#########################################################################
###TXTPFundTypeType是一个资金类型类型
#########################################################################
typedefDict["TXTPFundTypeType"] = "char"

###银行存款
XTP_FT_Deposite = '1'
###分项资金
XTP_FT_ItemFund = '2'
###公司调整
XTP_FT_Company = '3'



#########################################################################
###TXTPFundDirectionType是一个出入金方向类型
#########################################################################
typedefDict["TXTPFundDirectionType"] = "char"

###入金
XTP_FD_In = '1'
###出金
XTP_FD_Out = '2'



#########################################################################
###TXTPBankFlagType是一个银行统一标识类型类型
#########################################################################
typedefDict["TXTPBankFlagType"] = "char"

###工商银行
XTP_BF_ICBC = '1'
###农业银行
XTP_BF_ABC = '2'
###中国银行
XTP_BF_BC = '3'
###建设银行
XTP_BF_CBC = '4'
###交通银行
XTP_BF_BOC = '5'
###其他银行
XTP_BF_Other = 'Z'



#########################################################################
###TXTPOperationMemoType是一个操作摘要类型
#########################################################################
typedefDict["TXTPOperationMemoType"] = "string"

#########################################################################
###TXTPFundStatusType是一个资金状态类型
#########################################################################
typedefDict["TXTPFundStatusType"] = "char"

###已录入
XTP_FS_Record = '1'
###已复核
XTP_FS_Check = '2'
###已冲销
XTP_FS_Charge = '3'



#########################################################################
###TXTPFundProjectIDType是一个资金项目编号类型
#########################################################################
typedefDict["TXTPFundProjectIDType"] = "string"

#########################################################################
###TXTPOperatorIDType是一个操作员代码类型
#########################################################################
typedefDict["TXTPOperatorIDType"] = "string"

#########################################################################
###TXTPCounterIDType是一个计数器代码类型
#########################################################################
typedefDict["TXTPCounterIDType"] = "string"

#########################################################################
###TXTPFunctionNameType是一个功能名称类型
#########################################################################
typedefDict["TXTPFunctionNameType"] = "string"

#########################################################################
###TXTPTradeCodeType是一个交易代码类型
#########################################################################
typedefDict["TXTPTradeCodeType"] = "string"

#########################################################################
###TXTPBrokerBranchIDType是一个经纪公司分支机构代码类型
#########################################################################
typedefDict["TXTPBrokerBranchIDType"] = "string"

#########################################################################
###TXTPTradeDateType是一个交易日期类型
#########################################################################
typedefDict["TXTPTradeDateType"] = "string"

#########################################################################
###TXTPTradeTimeType是一个交易时间类型
#########################################################################
typedefDict["TXTPTradeTimeType"] = "string"

#########################################################################
###TXTPBankSerialType是一个银行流水号类型
#########################################################################
typedefDict["TXTPBankSerialType"] = "string"

#########################################################################
###TXTPSerialType是一个流水号类型
#########################################################################
typedefDict["TXTPSerialType"] = "int"

#########################################################################
###TXTPLastFragmentType是一个最后分片标志类型
#########################################################################
typedefDict["TXTPLastFragmentType"] = "char"

###是最后分片
XTP_LF_Yes = '0'
###不是最后分片
XTP_LF_No = '1'



#########################################################################
###TXTPIndividualNameType是一个个人姓名类型
#########################################################################
typedefDict["TXTPIndividualNameType"] = "string"

#########################################################################
###TXTPCustTypeType是一个客户类型类型
#########################################################################
typedefDict["TXTPCustTypeType"] = "char"

###自然人
XTP_CUSTT_Person = '0'
###机构户
XTP_CUSTT_Institution = '1'



#########################################################################
###TXTPBankAccountType是一个银行账户类型
#########################################################################
typedefDict["TXTPBankAccountType"] = "string"

#########################################################################
###TXTPYesNoIndicatorType是一个是或否标识类型
#########################################################################
typedefDict["TXTPYesNoIndicatorType"] = "char"

###是
XTP_YNI_Yes = '0'
###否
XTP_YNI_No = '1'



#########################################################################
###TXTPTradeAmountType是一个交易金额（元）类型
#########################################################################
typedefDict["TXTPTradeAmountType"] = "float"

#########################################################################
###TXTPCustFeeType是一个应收客户费用（元）类型
#########################################################################
typedefDict["TXTPCustFeeType"] = "float"

#########################################################################
###TXTPBrokerFeeType是一个应收经纪公司费用（元）类型
#########################################################################
typedefDict["TXTPBrokerFeeType"] = "float"

#########################################################################
###TXTPFeePayFlagType是一个费用支付标志类型
#########################################################################
typedefDict["TXTPFeePayFlagType"] = "char"

###由受益方支付费用
XTP_FPF_BEN = '0'
###由发送方支付费用
XTP_FPF_OUR = '1'
###由发送方支付发起的费用，受益方支付接受的费用
XTP_FPF_SHA = '2'



#########################################################################
###TXTPAddInfoType是一个附加信息类型
#########################################################################
typedefDict["TXTPAddInfoType"] = "string"

#########################################################################
###TXTPDigestType是一个摘要类型
#########################################################################
typedefDict["TXTPDigestType"] = "string"

#########################################################################
###TXTPBankAccTypeType是一个银行帐号类型类型
#########################################################################
typedefDict["TXTPBankAccTypeType"] = "char"

###银行存折
XTP_BAT_BankBook = '1'
###储蓄卡
XTP_BAT_SavingCard = '2'
###信用卡
XTP_BAT_CreditCard = '3'



#########################################################################
###TXTPDeviceIDType是一个渠道标志类型
#########################################################################
typedefDict["TXTPDeviceIDType"] = "string"

#########################################################################
###TXTPPwdFlagType是一个密码核对标志类型
#########################################################################
typedefDict["TXTPPwdFlagType"] = "char"

###不核对
XTP_BPWDF_NoCheck = '0'
###明文核对
XTP_BPWDF_BlankCheck = '1'
###密文核对
XTP_BPWDF_EncryptCheck = '2'



#########################################################################
###TXTPBankCodingForBrokerType是一个银行对经纪公司的编码类型
#########################################################################
typedefDict["TXTPBankCodingForBrokerType"] = "string"

#########################################################################
###TXTPOperNoType是一个交易柜员类型
#########################################################################
typedefDict["TXTPOperNoType"] = "string"

#########################################################################
###TXTPTIDType是一个交易ID类型
#########################################################################
typedefDict["TXTPTIDType"] = "int"

#########################################################################
###TXTPTransferStatusType是一个转账交易状态类型
#########################################################################
typedefDict["TXTPTransferStatusType"] = "char"

###正常
XTP_TRFS_Normal = '0'
###被冲正
XTP_TRFS_Repealed = '1'



#########################################################################
###TXTPPlateSerialType是一个平台流水号类型
#########################################################################
typedefDict["TXTPPlateSerialType"] = "int"

#########################################################################
###TXTPAvailabilityFlagType是一个有效标志类型
#########################################################################
typedefDict["TXTPAvailabilityFlagType"] = "char"

###未确认
XTP_AVAF_Invalid = '0'
###有效
XTP_AVAF_Valid = '1'
###冲正
XTP_AVAF_Repeal = '2'



#########################################################################
###TXTPOperatorCodeType是一个操作员类型
#########################################################################
typedefDict["TXTPOperatorCodeType"] = "string"

#########################################################################
###TXTPRepayStockAlgoType是一个买券还券算法类型
#########################################################################
typedefDict["TXTPRepayStockAlgoType"] = "char"

###默认算法
XTP_RSA_Original = '0'
###按还券比例计算
XTP_RSA_Ratio = '1'
###Min[1,2]
XTP_RSA_Min = '2'



#########################################################################
###TXTPTradeSpanType是一个交易时间段类型类型
#########################################################################
typedefDict["TXTPTradeSpanType"] = "char"

###普通业务
XTP_TS_Common = '1'
###个股期权
XTP_TS_Options = '2'



#########################################################################
###TXTPSettleSystemTypeType是一个所属结算系统类型类型
#########################################################################
typedefDict["TXTPSettleSystemTypeType"] = "char"

###顶点系统
XTP_SST_Aboss = '1'
###恒生系统
XTP_SST_HS = '2'



#########################################################################
###TXTPLogLevelType是一个日志级别类型
#########################################################################
typedefDict["TXTPLogLevelType"] = "string"

#########################################################################
###TXTPProcessNameType是一个存储过程名称类型
#########################################################################
typedefDict["TXTPProcessNameType"] = "string"

#########################################################################
###TXTPTemplateIDType是一个模板代码类型
#########################################################################
typedefDict["TXTPTemplateIDType"] = "string"

#########################################################################
###TXTPTradeIndexType是一个成交序号类型
#########################################################################
typedefDict["TXTPTradeIndexType"] = "int"

#########################################################################
###TXTPSplitMergeStatusType是一个基金当天拆分合并状态类型
#########################################################################
typedefDict["TXTPSplitMergeStatusType"] = "char"

###表示允许拆分和合并
XTP_SMS_Allow = '0'
###允许拆分、不允许合并
XTP_SMS_OnlySplit = '1'
###不允许拆分、允许合并
XTP_SMS_OnlyMerge = '2'
###不允许拆分和合并
XTP_SMS_Forbidden = '3'



#########################################################################
###TXTPFundInterTransferTypeType是一个资金内转类型类型
#########################################################################
typedefDict["TXTPFundInterTransferTypeType"] = "char"

###转入
XTP_FITT_TransferIn = '0'
###转出
XTP_FITT_TransferOut = '1'



#########################################################################
###TXTPInstrumentTypeType是一个合约类型类型
#########################################################################
typedefDict["TXTPInstrumentTypeType"] = "char"

###普通
XTP_IT_Normal = '0'
###看涨期权
XTP_IT_CallOptions = '1'
###看跌期权
XTP_IT_PutOptions = '2'
###普通(STEP)
XTP_IT_Normal_STEP = '3'



#########################################################################
###TXTPInvestorLevelType是一个投资者期权交易等级类型
#########################################################################
typedefDict["TXTPInvestorLevelType"] = "char"

###一级
XTP_IL_Level_1 = '0'
###二级
XTP_IL_Level_2 = '1'
###三级
XTP_IL_Level_3 = '2'



#########################################################################
###TXTPCloseDirectionType是一个平仓方向类型
#########################################################################
typedefDict["TXTPCloseDirectionType"] = "char"

###买平仓
XTP_CD_CloseBuy = '!'
###卖平仓
XTP_CD_CloseSell = '@'
###备兑平仓
XTP_CD_CloseCover = '#'



#########################################################################
###TXTPDelivTypeType是一个交割类型类型
#########################################################################
typedefDict["TXTPDelivTypeType"] = "char"

###看涨期权执行
XTP_DT_ExecCallOptions = '0'
###看跌期权执行
XTP_DT_ExecPutOptions = '1'
###在途证券
XTP_DT_UnavailStock = '2'



