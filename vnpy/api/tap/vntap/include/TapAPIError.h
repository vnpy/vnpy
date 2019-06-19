#ifndef TAP_API_ERROR_H
#define TAP_API_ERROR_H

//=============================================================================
/**
 *	\addtogroup G_ERR_INNER_API		TapAPI内部返回的错误码定义。
 *	@{
 */
//=============================================================================
//! 成功
const int TAPIERROR_SUCCEED                                            = 0;
//! 连接服务失败
const int TAPIERROR_ConnectFail                                        = -1;
//! 链路认证失败
const int TAPIERROR_LinkAuthFail                                       = -2;
//! 主机地址不可用
const int TAPIERROR_HostUnavailable                                    = -3;
//! 发送数据错误
const int TAPIERROR_SendDataError                                      = -4;
//! 测试编号不合法
const int TAPIERROR_TestIDError                                        = -5;
//! 没准备好测试网络
const int TAPIERROR_NotReadyTestNetwork                                = -6;
//! 当前网络测试还没结束
const int TAPIERROR_CurTestNotOver                                     = -7;
//! 没用可用的接入前置
const int TAPIERROR_NOFrontAvailable                                   = -8;
//! 数据路径不可用
const int TAPIERROR_DataPathAvaiable                                   = -9;
//! 重复登录
const int TAPIERROR_RepeatLogin                                        = -10;
//! 内部错误	
const int TAPIERROR_InnerError                                         = -11;
//! 上一次请求还没有结束	
const int TAPIERROR_LastReqNotFinish                                   = -12;
//! 输入参数非法	
const int TAPIERROR_InputValueError                                    = -13;
//! 授权码不合法	
const int TAPIERROR_AuthCode_Invalid                                   = -14;
//! 授权码超期	
const int TAPIERROR_AuthCode_Expired                                   = -15;
//! 授权码类型不匹配	
const int TAPIERROR_AuthCode_TypeNotMatch                              = -16;
//! API还没有准备好
const int TAPIERROR_API_NotReady                                       = -17;
//! UDP端口监听失败
const int TAPIERROR_UDP_LISTEN_FAILED                                  = -18;
//! UDP正在监听
const int TAPIERROR_UDP_LISTENING                                      = -19;
//! 接口未实现
const int TAPIERROR_NotImplemented                                     = -20;
//! 每次登陆只允许调用一次
const int TAPIERROR_CallOneTimeOnly                                    = -21;
//! 查询频率太高
const int TAPIERROR_Frequently                                         = -22;

/** @}*/


//=============================================================================
/**
 *	\addtogroup G_ERR_INPUT_CHECK		输入参数检查错误
 *	@{
 */
//=============================================================================
//! 输入数据为NULL
const int TAPIERROR_INPUTERROR_NULL                                    = -10000;
//! 输入错误的:TAPIYNFLAG
const int TAPIERROR_INPUTERROR_TAPIYNFLAG                              = -10001;
//! 输入错误的:TAPILOGLEVEL
const int TAPIERROR_INPUTERROR_TAPILOGLEVEL                            = -10002;
//! 输入错误的:TAPICommodityType
const int TAPIERROR_INPUTERROR_TAPICommodityType                       = -10003;
//! 输入错误的:TAPICallOrPutFlagType
const int TAPIERROR_INPUTERROR_TAPICallOrPutFlagType                   = -10004;
//! 输入错误的:TAPIAccountType
const int TAPIERROR_INPUTERROR_TAPIAccountType                         = -12001;
//! 输入错误的:TAPIAccountState
const int TAPIERROR_INPUTERROR_TAPIAccountState                        = -12003;
//! 输入错误的:TAPIAccountFamilyType
const int TAPIERROR_INPUTERROR_TAPIAccountFamilyType                   = -12004;
//! 输入错误的:TAPIOrderTypeType
const int TAPIERROR_INPUTERROR_TAPIOrderTypeType                       = -12005;
//! 输入错误的:TAPIOrderSourceType
const int TAPIERROR_INPUTERROR_TAPIOrderSourceType                     = -12006;
//! 输入错误的:TAPITimeInForceType
const int TAPIERROR_INPUTERROR_TAPITimeInForceType                     = -12007;
//! 输入错误的:TAPISideType
const int TAPIERROR_INPUTERROR_TAPISideType                            = -12008;
//! 输入错误的:TAPIPositionEffectType
const int TAPIERROR_INPUTERROR_TAPIPositionEffectType                  = -12009;
//! 输入错误的:TAPIHedgeFlagType
const int TAPIERROR_INPUTERROR_TAPIHedgeFlagType                       = -12010;
//! 输入错误的:TAPIOrderStateType
const int TAPIERROR_INPUTERROR_TAPIOrderStateType                      = -12011;
//! 输入错误的:TAPICalculateModeType
const int TAPIERROR_INPUTERROR_TAPICalculateModeType                   = -12012;
//! 输入错误的:TAPIMatchSourceType
const int TAPIERROR_INPUTERROR_TAPIMatchSourceType                     = -12013;
//! 输入错误的:TAPIOpenCloseModeType
const int TAPIERROR_INPUTERROR_TAPIOpenCloseModeType                   = -12014;
//! 输入错误的:TAPIFutureAlgType
const int TAPIERROR_INPUTERROR_TAPIFutureAlgType                       = -12015;
//! 输入错误的:TAPIOptionAlgType
const int TAPIERROR_INPUTERROR_TAPIOptionAlgType                       = -12016;
//! 输入错误的:TAPIBankAccountLWFlagType
const int TAPIERROR_INPUTERROR_TAPIBankAccountLWFlagType               = -12017;
//! 输入错误的:TAPIMarginCalculateModeType
const int TAPIERROR_INPUTERROR_TAPIMarginCalculateModeType             = -12021;
//! 输入错误的:TAPIOptionMarginCalculateModeType
const int TAPIERROR_INPUTERROR_TAPIOptionMarginCalculateModeType       = -12022;
//! 输入错误的:TAPICmbDirectType
const int TAPIERROR_INPUTERROR_TAPICmbDirectType                       = -12023;
//! 输入错误的:TAPIDeliveryModeType
const int TAPIERROR_INPUTERROR_TAPIDeliveryModeType                    = -12024;
//! 输入错误的:TAPIContractTypeType
const int TAPIERROR_INPUTERROR_TAPIContractTypeType                    = -12025;
//! 输入错误的:TAPITacticsTypeType
const int TAPIERROR_INPUTERROR_TAPITacticsTypeType                     = -12035;
//! 输入错误的:TAPIORDERACT
const int TAPIERROR_INPUTERROR_TAPIORDERACT                            = -12036;
//! 输入错误的:TAPITriggerConditionType
const int TAPIERROR_INPUTERROR_TAPITriggerConditionType                = -12041;
//! 输入错误的:TAPITriggerPriceTypeType
const int TAPIERROR_INPUTERROR_TAPITriggerPriceTypeType                = -12042;
//! 输入错误的:TAPITradingStateType 
const int TAPIERROR_INPUTERROR_TAPITradingStateType                    = -12043;
//! 输入错误的:TAPIMarketLevelType 
const int TAPIERROR_INPUTERROR_TAPIMarketLevelType                     = -12044;
//! 输入错误的:TAPIOrderQryTypeType 
const int TAPIERROR_INPUTERROR_TAPIOrderQryTypeType                    = -12045;

/** @}*/

//=============================================================================
/**
 *	\addtogroup G_ERR_DISCONNECT_REASON	网络断开错误代码定义
 *	@{
 */
//=============================================================================
//! 主动断开
const int TAPIERROR_DISCONNECT_CLOSE_INIT                              = 1;
//! 被动断开
const int TAPIERROR_DISCONNECT_CLOSE_PASS                              = 2;
//! 读错误
const int TAPIERROR_DISCONNECT_READ_ERROR                              = 3;
//! 写错误
const int TAPIERROR_DISCONNECT_WRITE_ERROR                             = 4;
//! 缓冲区满
const int TAPIERROR_DISCONNECT_BUF_FULL                                = 5;
//! 异步操作错误
const int TAPIERROR_DISCONNECT_IOCP_ERROR                              = 6;
//! 解析数据错误
const int TAPIERROR_DISCONNECT_PARSE_ERROR                             = 7;
//! 连接超时
const int TAPIERROR_DISCONNECT_CONNECT_TIMEOUT                         = 8;
//! 初始化失败
const int TAPIERROR_DISCONNECT_INIT_ERROR                              = 9;
//! 已经连接
const int TAPIERROR_DISCONNECT_HAS_CONNECTED                           = 10;
//! 工作线程已结束
const int TAPIERROR_DISCONNECT_HAS_EXIT                                = 11;
//! 操作正在进行，请稍后重试
const int TAPIERROR_DISCONNECT_TRY_LATER                               = 12;
//! 心跳检测失败
const int TAPIERROR_DISCONNECT_HEARTBEAT_FAILED                        = 13;

/** @}*/

//=============================================================================
/**
 *	\addtogroup G_ERR_LOGIN	登陆过程返回的错误代码定义
 *	@{
 */
//=============================================================================
//! 登录过程执行错误
const int TAPIERROR_LOGIN                                              = 10001;
//! 登录用户不存在
const int TAPIERROR_LOGIN_USER                                         = 10002;
//! 需要进行动态认证
const int TAPIERROR_LOGIN_DDA                                          = 10003;
//! 登录用户未授权
const int TAPIERROR_LOGIN_LICENSE                                      = 10004;
//! 登录模块不正确
const int TAPIERROR_LOGIN_MODULE                                       = 10005;
//! 需要强制修改密码
const int TAPIERROR_LOGIN_FORCE                                        = 10006;
//! 登录状态禁止登陆
const int TAPIERROR_LOGIN_STATE                                        = 10007;
//! 登录密码不正确
const int TAPIERROR_LOGIN_PASS                                         = 10008;
//! 没有该模块登录权限
const int TAPIERROR_LOGIN_RIGHT                                        = 10009;
//! 登录数量超限
const int TAPIERROR_LOGIN_COUNT                                        = 10010;
//! 登录用户不在服务器标识下可登录用户列表中
const int TAPIERROR_LOGIN_NOTIN_SERVERFLAGUSRES                        = 10011;
//! 登陆用户不在有效期
const int TAPIERROR_LOGIN_USER_EXPIRED                                 = 10012;
//! 登陆用户无下属客户
const int TAPIERROR_LOGIN_NO_ACCOUNT                                   = 10013;
//! 登录用户是子帐号且授权中未包含机构通标记
const int TAPIERROR_LOGIN_NO_JGT                                       = 10014;
//! 登录用户密码错误次数超限，禁止登陆
const int TAPIERROR_LOGIN_ERROR_TIMES                                  = 10015;
//! 登录用户授权类型错误
const int TAPIERROR_LOGIN_ERROR_AUTHTYPE                               = 10016;
//! 登录用户授权到期或到期日错误
const int TAPIERROR_LOGIN_ERROR_AUTHEXPIRED                            = 10017;
//! 登录用户密码超过有效天数
const int TAPIERROR_LOGIN_ERROR_PASSWDEXPIRED                          = 10018;

/** @}*/

//=============================================================================
/**
 *	\addtogroup G_ERR_MANAGE 管理业务处理返回错误码	
 *	@{
 */
//==============================================================================
//! 登录用户信息查询失败
const int TAPIERROR_USERINFO_QRY                                       = 10101;
//! 登录用户下属所有权限查询失败
const int TAPIERROR_USERALLRIGHT_QRY                                   = 11001;
//! 登录用户下属所有资金账号查询失败
const int TAPIERROR_USERALLACCOUNT_QRY                                 = 11501;
//! 登录用户密码修改失败
const int TAPIERROR_USERPASSWORD_MOD                                   = 11701;
//! 登录用户密码修改失败——原始密码错误
const int TAPIERROR_USERPASSWORD_MOD_SOURCE                            = 11702;
//! 登录用户密码修改失败——不能与前n次密码相同
const int TAPIERROR_USERPASSWORD_MOD_SAME                              = 11703;
//! 新密码不符合密码复杂度要求
const int TAPIERROR_USERPASSWORD_MOD_COMPLEXITY                        = 11704;
//! 资金账号信息查询失败
const int TAPIERROR_ACCOUNTINFO_QRY                                    = 20201;
//! 客户交易编码查询失败
const int TAPIERROR_TRADENO_QRY                                        = 20701;
//! 合约信息查询失败
const int TAPIERROR_CONTRACTINFO_QRY                                   = 22801;
//! 特殊期权标的查询失败
const int TAPIERROR_SPECIALOPTIONFUTURE_QRY                            = 22901;
//! 品种委托类型查询失败
const int TAPIERROR_COMMODITYORDERTYPE_QRY                             = 25501;
//! 品种委托时间有效性查询失败
const int TAPIERROR_ORDERTIMEINFORCE_QRY                               = 25601;
//! 用户下单频率查询失败
const int TAPIERROR_USER_ORDER_FREQUENCE_QRY                           = 28901;

/** @}*/

//=============================================================================
/**
 *	\addtogroup G_ERR_TRADE 交易业务处理返回错误码	
 *	@{
 */
//==============================================================================
//! 资金账号不存在
const int TAPIERROR_ORDERINSERT_ACCOUNT                                = 60001;
//! 资金账号状态不正确
const int TAPIERROR_ORDERINSERT_ACCOUNT_STATE		                   = 60002;
//! 资金账号无委托方向交易权限
const int TAPIERROR_ORDERINSERT_SIDE_TRADE                             = 60003;
//! 资金账号无期权交易权限
const int TAPIERROR_ORDERINSERT_OPTIONS_TRADE                          = 60004;
//! 资金账号无品种交易权限
const int TAPIERROR_ORDERINSERT_COMMODITY_TRADE                        = 60005;
//! 资金账号无开仓权限
const int TAPIERROR_ORDERINSERT_OPEN_RIGHT                             = 60006;
//! 资金账号风控项检查失败
const int TAPIERROR_ORDERINSERT_RISK_CHECK                             = 60007;
//! 下单无效的合约
const int TAPIERROR_ORDERINSERT_CONTRACT                               = 60011;
//! 下单合约无交易路由
const int TAPIERROR_ORDERINSERT_TRADEROUTE                             = 60021;
//! 持仓量超过最大限制
const int TAPIERROR_ORDERINSERT_POSITIONMAX                            = 60022;
//! 禁止交易
const int TAPIERROR_ORDER_NOTRADE                                      = 60023;
//! 只可平仓
const int TAPIERROR_ORDER_CLOSE                                        = 60024;
//! 下单资金不足
const int TAPIERROR_ORDERINSERT_NOTENOUGHFUND                          = 60031;
//! 不支持的订单类型
const int TAPIERROR_ORDERINSERT_ORDERTYPE                              = 60032;
//! 不支持的时间有效类型
const int TAPIERROR_ORDERINSERT_TIMEINFORCE                            = 60033;
//! 不支持的策略单类型
const int TAPIERROR_ORDERINSERT_NO_TACTICS                             = 60034;
//! 平仓数量超过已有持仓量
const int TAPIERROR_ORDERINSERT_POSITION_CANNOT_CLOSE                  = 60035;
//! 下单自动审核失败
const int TAPIERROR_ORDERINSERT_AUTOCHECK_FAIL                         = 60036;
//! LME未准备就绪
const int TAPIERROR_ORDERINSERT_LME_NOTREADY                           = 60037;
//! 平仓方式错误
const int TAPIERROR_ORDERINSERT_CLOSEMODE                              = 60038;
//! 下单对应的父账号资金不足
const int TAPIERROR_ORDERINSERT_PARENTNOTENOUGHFUND                    = 60039;
//! 互换单的合约格式错误
const int TAPIERROR_SWAP_CONTRACT                                      = 60040;
//! 当前客户不能使用此账号交易
const int TAPIERROR_USERNO_NOTHAS_ACCOUNT                              = 60051;
//! 上手通道状态不正常
const int TAPIERROR_UPPERCHANNEL_BROKEN                                = 60052;
//! 上手通道未开通EXIST
const int TAPIERROR_UPPERCHANNEL_NOT_EXIST                             = 60053;
//! 撤单无此系统号
const int TAPIERROR_ORDERDELETE_NOT_SYSNO                              = 60061;
//! 此状态不允许撤单
const int TAPIERROR_ORDERDELETE_NOT_STATE                              = 60062;
//! 此状态不允许激活
const int TAPIERROR_ORDERACTIVE_NOT_STATE                              = 60063;
//! 此状态禁止审核
const int TAPIERROR_ORDERCHECK_NOT_STATE                               = 60071;
//! 订单审核失败
const int TAPIERROR_ORDERCHECK_FAIL                                    = 60072;
//! 此状态不允许改单
const int TAPIERROR_ORDERMODIFY_NOT_STATE                              = 60081;
//! 人工单不允许改单
const int TAPIERROR_ORDERMODIFY_BACK_INPUT                             = 60082;
//! 手续费参数错误
const int TAPIERROR_ORDERINSERT_FEE                                    = 60091;
//! 保证金参数错误
const int TAPIERROR_ORDERINSERT_MARGIN                                 = 60092;
//! 操作账号只可查询
const int TAPIERROR_ORDER_NO_PERMIT                                    = 60100;
//! 非做市商不能应价
const int TAPIERROR_RSPQUOTE_NO_PERMIT                                 = 60101;
//! 即使子帐号又是做市商不能应价
const int TAPIERROR_RSPQUOTE_CHILD_NO_PERMIT                           = 60102;
//! 下单找不到交易编码
const int TAPIERROR_TRADENO_NOT_FIND                                   = 60103;
//! 操作账号只可开仓
const int TAPIERROR_ORDER_NO_CLOSE                                     = 60104;
//! 操作账号没有上期挂单查询权限
const int TAPIERROR_QRY_QUOTE_NO_PERMIT                                = 60105;
//! 限期有效单不能小于当前交易日
const int TAPIERROR_EXPIREDATE_NO_PERMIT                               = 60106;
//! 该编码不允许申请或拆分组合
const int TAPIERROR_CMB_NO_PERMIT                                      = 60107;
//! 非本服务器标记下的账号不允许操作
const int TAPIERROR_ORDERSERVER_NO_PERMIT                              = 60108;
//! 行权或弃权量超过可用量
const int TAPIERROR_POSITION_CANNOT_EXEC_OR_ABANDON                    = 60109;
//! 没有订单审核权限
const int TAPIERROR_ORDERCHECK_NO_PERMIT                               = 60110;
//! 超过当日最大开仓量
const int TAPIERROR_ORDERMAXOPENVOL_NO_PERMIT                          = 60111;
//! 非大连应价单不允许两笔委托量不一致
const int TAPIERROR_ORDER_QTY_NO_PERMIT                                = 60115;
//! 申请不允许重复提交
const int TAPIERROR_ORDER_APPLY_NO_PERMIT                              = 60117;
//! 超过账号下单频率限制
const int TAPIERROR_ORDER_FREQ_OVERRUN                                 = 60118;
//! 组合表不存在的组合方向或投保标志
const int TAPIERROR_COMB_NO_SIDEORHEDGE                                = 60119;
//! 订单操作频率过高
const int TAPIERROR_ORDER_FREQUENCY                                    = 61001;
//! 委托查询返回前不能进行下次查询
const int TAPIERROR_ORDER_QUERYING                                     = 61002;

/** @}*/

//=============================================================================
/**
 *	\addtogroup G_ERR_QUOTE 行情业务处理返回错误码	
 *	@{
 */
//=============================================================================
//! 超过行情最大总订阅数
const int TAPIERROR_SUBSCRIBEQUOTE_MAX                                 = 72001;
//! 超过该交易所行情最大订阅数
const int TAPIERROR_SUBSCRIBEQUOTE_EXCHANGE_MAX                        = 72002;
//! 没有该行情的订阅权限
const int TAPIERROR_SUBSCRIBEQUOTE_NO_RIGHT                            = 72101;
//! 没有该交易所下行情的订阅权限
const int TAPIERROR_SUBSCRIBEQUOTE_NO_EXCHANGE_RIGHT                   = 72102;
//! 品种不存在
const int TAPIERROR_SUBSCRIBEQUOTE_COMMODITY_NOT_EXIST                 = 72103;
//! 合约可能不存在
const int TAPIERROR_SUBSCRIBEQUOTE_CONTRACT_MAY_NOT_EXIST              = 72104;
//! 不支持的行情协议
const int TAPIERROR_QUOTEFRONT_UNKNOWN_PROTOCOL                        = 83001;

/** @}*/


#endif //! TAP_API_ERROR_H
