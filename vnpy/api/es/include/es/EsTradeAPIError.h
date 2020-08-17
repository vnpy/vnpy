/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EsTradeAPIError.h
 * Author: guoxg
 *
 * Created on 2018年5月24日, 下午2:50
 */

#ifndef ESTRADEAPIERROR_H
#define ESTRADEAPIERROR_H

namespace EsTradeAPI
{

	//=============================================================================
	/**
	 *	\addtogroup G_ERR_INNER_API		TapAPI内部返回的错误码定义。
	 *	@{
	 */
	 //=============================================================================
	 //! 成功
	const int TAPIERROR_SUCCEED = 0;
	//! 连接服务失败
	const int TAPIERROR_ConnectFail = -1;
	//! 链路认证失败
	const int TAPIERROR_LinkAuthFail = -2;
	//! 主机地址不可用
	const int TAPIERROR_HostUnavailable = -3;
	//! 发送数据错误
	const int TAPIERROR_SendDataError = -4;
	//! 测试编号不合法
	const int TAPIERROR_TestIDError = -5;
	//! 没准备好测试网络
	const int TAPIERROR_NotReadyTestNetwork = -6;
	//! 当前网络测试还没结束
	const int TAPIERROR_CurTestNotOver = -7;
	//! 没用可用的接入前置
	const int TAPIERROR_NOFrontAvailable = -8;
	//! 日志文件路径不可用
	const int TAPIERROR_DataPathAvaiable = -9;
	//! 重复登录
	const int TAPIERROR_RepeatLogin = -10;
	//! 内部错误	
	const int TAPIERROR_InnerError = -11;
	//! 上一次请求还没有结束	
	const int TAPIERROR_LastReqNotFinish = -12;
	//! 输入参数非法	
	const int TAPIERROR_InputValueError = -13;
	//! 授权码不合法	
	const int TAPIERROR_AuthCode_Invalid = -14;
	//! 授权码超期	
	const int TAPIERROR_AuthCode_Expired = -15;
	//! 授权码类型不匹配	
	const int TAPIERROR_AuthCode_TypeNotMatch = -16;
	//! API还没有准备好
	const int TAPIERROR_API_NotReady = -17;
	//! UDP端口监听失败
	const int TAPIERROR_UDP_LISTEN_FAILED = -18;
	//! UDP正在监听
	const int TAPIERROR_UDP_LISTENING = -19;
	//! 接口未实现
	const int TAPIERROR_NotImplemented = -20;
	//! 只允许调用一次
	const int TAPIERROR_CallOneTimeOnly = -21;
	//! 操作频率太高
	const int TAPIERROR_Frequently = -22;
	//! 用户编号重复
	const int TAPIERROR_UserNoDuplicate = -23;
	//! 用户编号错误
	const int TAPIERROR_UserNoError = -24;
	//! 没有所需要查询的数据
	const int TAPIERROR_HaveNoData = -25;
	//! 用户已经就绪不需要再次启动
	const int TAPIERROR_UserReady = -26;
	//! 不支持的操作类型
	const int TAPIERROR_NotSupportType = -27;
	//! 当前用户对应的系统暂不支持的功能
	const int TAPIERROR_NotSupportFunction = -28;
	//! 用户登录信息不完整
	const int TAPIERROR_LoginInfoIncompletion = -29;
	//! 非中继用户不能主动上报登录信息
	const int TAPIERROR_NotAllowSubmit = -30;
	//! 加载下层API动态库失败
	const int TAPIERROR_LoadDll = -31;
	//! 日志文件已经打开
	const int TAPIERROR_LogFileReady = -32;
	//! 打开日志文件错误
	const int TAPIERROR_LogFile_OpenError = -33;
	//! 创建TCPClient失败
	const int TAPIERROR_CreateTcpClient_Error = -34;
    //! 错误的系统类型
    const int TAPIERROR_SystemType_Error = -35;
	//! 登录成功后不允许调用
	const int TAPIERROR_NotAllowAfterLogin = -36;
	//! 验证码有效期内不允许第二次请求
	const int TAPIERROR_NotAllowRequestAgain = -37;
	/** @}*/


	//=============================================================================
	/**
	 *	\addtogroup G_ERR_INPUT_CHECK		输入参数检查错误
	 *	@{
	 */
	 //=============================================================================
	 //! 输入数据为NULL
	const int TAPIERROR_INPUTERROR_NULL = -10000;
	//! 输入错误的:TAPIYNFLAG
	const int TAPIERROR_INPUTERROR_TAPIYNFLAG = -10001;
	//! 输入错误的:TAPILOGLEVEL
	const int TAPIERROR_INPUTERROR_TAPILOGLEVEL = -10002;
	//! 输入错误的:TAPICommodityType
	const int TAPIERROR_INPUTERROR_TAPICommodityType = -10003;
	//! 输入错误的:TAPICallOrPutFlagType
	const int TAPIERROR_INPUTERROR_TAPICallOrPutFlagType = -10004;
	//! 输入错误的:TAPISystemTypeType
	const int TAPIERROR_INPUTERROR_TAPISystemTypeType = -10005;
	//! 输入错误的:TAPILoginTypeType
	const int TAPIERROR_INPUTERROR_TAPILoginTypeType = -10006;
	//! 输入错误的:TAPIAccountType
	const int TAPIERROR_INPUTERROR_TAPIAccountType = -12001;
	//! 输入错误的:TAPIAccountState
	const int TAPIERROR_INPUTERROR_TAPIAccountState = -12003;
	//! 输入错误的:TAPIAccountFamilyType
	const int TAPIERROR_INPUTERROR_TAPIAccountFamilyType = -12004;
	//! 输入错误的:TAPIOrderTypeType
	const int TAPIERROR_INPUTERROR_TAPIOrderTypeType = -12005;
	//! 输入错误的:TAPIOrderSourceType
	const int TAPIERROR_INPUTERROR_TAPIOrderSourceType = -12006;
	//! 输入错误的:TAPITimeInForceType
	const int TAPIERROR_INPUTERROR_TAPITimeInForceType = -12007;
	//! 输入错误的:TAPISideType
	const int TAPIERROR_INPUTERROR_TAPISideType = -12008;
	//! 输入错误的:TAPIPositionEffectType
	const int TAPIERROR_INPUTERROR_TAPIPositionEffectType = -12009;
	//! 输入错误的:TAPIHedgeFlagType
	const int TAPIERROR_INPUTERROR_TAPIHedgeFlagType = -12010;
	//! 输入错误的:TAPIOrderStateType
	const int TAPIERROR_INPUTERROR_TAPIOrderStateType = -12011;
	//! 输入错误的:TAPICalculateModeType
	const int TAPIERROR_INPUTERROR_TAPICalculateModeType = -12012;
	//! 输入错误的:TAPIMatchSourceType
	const int TAPIERROR_INPUTERROR_TAPIMatchSourceType = -12013;
	//! 输入错误的:TAPIOpenCloseModeType
	const int TAPIERROR_INPUTERROR_TAPIOpenCloseModeType = -12014;
	//! 输入错误的:TAPIFutureAlgType
	const int TAPIERROR_INPUTERROR_TAPIFutureAlgType = -12015;
	//! 输入错误的:TAPIOptionAlgType
	const int TAPIERROR_INPUTERROR_TAPIOptionAlgType = -12016;
	//! 输入错误的:TAPIBankAccountLWFlagType
	const int TAPIERROR_INPUTERROR_TAPIBankAccountLWFlagType = -12017;
	//! 输入错误的:TAPIMarginCalculateModeType
	const int TAPIERROR_INPUTERROR_TAPIMarginCalculateModeType = -12021;
	//! 输入错误的:TAPIOptionMarginCalculateModeType
	const int TAPIERROR_INPUTERROR_TAPIOptionMarginCalculateModeType = -12022;
	//! 输入错误的:TAPICmbDirectType
	const int TAPIERROR_INPUTERROR_TAPICmbDirectType = -12023;
	//! 输入错误的:TAPIDeliveryModeType
	const int TAPIERROR_INPUTERROR_TAPIDeliveryModeType = -12024;
	//! 输入错误的:TAPIContractTypeType
	const int TAPIERROR_INPUTERROR_TAPIContractTypeType = -12025;
	//! 输入错误的:TAPITacticsTypeType
	const int TAPIERROR_INPUTERROR_TAPITacticsTypeType = -12035;
	//! 输入错误的:TAPIORDERACT
	const int TAPIERROR_INPUTERROR_TAPIORDERACT = -12036;
	//! 输入错误的:TAPITriggerConditionType
	const int TAPIERROR_INPUTERROR_TAPITriggerConditionType = -12041;
	//! 输入错误的:TAPITriggerPriceTypeType
	const int TAPIERROR_INPUTERROR_TAPITriggerPriceTypeType = -12042;
	//! 输入错误的:TAPITradingStateType 
	const int TAPIERROR_INPUTERROR_TAPITradingStateType = -12043;
	//! 输入错误的:TAPIMarketLevelType 
	const int TAPIERROR_INPUTERROR_TAPIMarketLevelType = -12044;
	//! 输入错误的:TAPIOrderQryTypeType 
	const int TAPIERROR_INPUTERROR_TAPIOrderQryTypeType = -12045;
	//! 输入错误的：TapAPICommodity
	const int TAPIERROR_INPUTERROR_TAPICommodity = -12046;
	//! 输入错误的：TAPIContract
	const int TAPIERROR_INPUTERROR_TAPIContract = -12047;
	//! 输入错误的:TAPIOrderPriceTypeType 
	const int TAPIERROR_INPUTERROR_TAPIOrderPriceTypeType = -12048;
	//! 输入错误的TAPIExpireTime
	const int TAPIERROR_INPUTERROR_TAPIExpireTime = -12049;
	//! 输入错误的二次认证信息
	const int TAPIERROR_INPUTERROR_VertificateCode = -12050;
	//! 输入错误的AddOneIsValid
	const int TAPIERROR_INPUTERROR_TAPIAddOneIsValid = -12051;

	/** @}*/

	//=============================================================================
	/**
	 *	\addtogroup G_ERR_DISCONNECT_REASON	网络断开错误代码定义
	 *	@{
	 */
	 //=============================================================================
	 //! 主动断开
	const int TAPIERROR_DISCONNECT_CLOSE_INIT = 1;
	//! 被动断开
	const int TAPIERROR_DISCONNECT_CLOSE_PASS = 2;
	//! 读错误
	const int TAPIERROR_DISCONNECT_READ_ERROR = 3;
	//! 写错误
	const int TAPIERROR_DISCONNECT_WRITE_ERROR = 4;
	//! 缓冲区满
	const int TAPIERROR_DISCONNECT_BUF_FULL = 5;
	//! 异步操作错误
	const int TAPIERROR_DISCONNECT_IOCP_ERROR = 6;
	//! 解析数据错误
	const int TAPIERROR_DISCONNECT_PARSE_ERROR = 7;
	//! 连接超时
	const int TAPIERROR_DISCONNECT_CONNECT_TIMEOUT = 8;
	//! 初始化失败
	const int TAPIERROR_DISCONNECT_INIT_ERROR = 9;
	//! 已经连接
	const int TAPIERROR_DISCONNECT_HAS_CONNECTED = 10;
	//! 工作线程已结束
	const int TAPIERROR_DISCONNECT_HAS_EXIT = 11;
	//! 操作正在进行，请稍后重试
	const int TAPIERROR_DISCONNECT_TRY_LATER = 12;
	//! 心跳检测失败
	const int TAPIERROR_DISCONNECT_HEARTBEAT_FAILED = 13;
	//! Socket处理错误
	const int TAPIERROR_DISCONNECT_SOCKETSELECT_ERROR = 14;
	//! 被动登出
	const int TAPIERROR_DISCONNECT_LOGOUT = 15;
	/** @}*/

	//=============================================================================
	/**
	 *	\addtogroup G_ERR_LOGIN	登陆过程返回的错误代码定义
	 *	@{
	 */
	 //=============================================================================
	 //! 登录过程执行错误
	const int TAPIERROR_LOGIN = 10001;
	//! 登录用户不存在
	const int TAPIERROR_LOGIN_USER = 10002;
	//! 需要进行动态认证
	const int TAPIERROR_LOGIN_DDA = 10003;
	//! 登录用户未授权
	const int TAPIERROR_LOGIN_LICENSE = 10004;
	//! 登录模块不正确
	const int TAPIERROR_LOGIN_MODULE = 10005;
	//! 需要强制修改密码
	const int TAPIERROR_LOGIN_FORCE = 10006;
	//! 登录状态禁止登陆
	const int TAPIERROR_LOGIN_STATE = 10007;
	//! 登录密码不正确
	const int TAPIERROR_LOGIN_PASS = 10008;
	//! 没有该模块登录权限
	const int TAPIERROR_LOGIN_RIGHT = 10009;
	//! 登录数量超限
	const int TAPIERROR_LOGIN_COUNT = 10010;
	//! 登录用户不在服务器标识下可登录用户列表中
	const int TAPIERROR_LOGIN_NOTIN_SERVERFLAGUSRES = 10011;
	//! 登陆用户交易日验证出错
	const int TAPIERROR_LOGIN_USER_EXPIRED = 10012;
	//! 登陆用户无下属客户
	const int TAPIERROR_LOGIN_NO_ACCOUNT = 10013;
	//! 登录用户是子帐号且授权中未包含机构通标记
	const int TAPIERROR_LOGIN_NO_JGT = 10014;
	//! 登录用户密码错误次数超限，禁止登陆
	const int TAPIERROR_LOGIN_ERROR_TIMES = 10015;
	//! 登录用户授权类型错误
	const int TAPIERROR_LOGIN_SECONDCERTIFICATION = 10016;
	//! 登录用户授权到期或到期日错误
	const int TAPIERROR_LOGIN_ERROR_AUTHEXPIRED = 10017;
	//! 登录用户密码超过有效天数
	const int TAPIERROR_LOGIN_ERROR_PASSWDEXPIRED = 10018;
	//! 登录用户未授权的登录IP和MAC
	const int TAPIERROR_LOGIN_ERROR_USERTRUST = 10019;
    //! 8.2客户端禁止登录请升级8.3
    const int TAPIERROR_LOGIN_ERROR_CLIENTVERSION = 10020;
    //! 用户授权信息错误
    const int TAPIERROR_LOGIN_ERROR_AUTHCODEINFO = 10021;

	//! 登录用户已被冻结
	const int TAPIERROR_LOGIN_FREEZE = 10050;
	//! 密码错误，用户冻结
	const int TAPIERROR_LOGIN_TOFREEZE = 10052;
	//! 客户状态不允许登录
	const int TAPIERROR_LOGIN_ACCOUNTSTATE = 10053;
	//! 需要进行二次认证
	const int TAPIERROR_LOGIN_SECCERTIFI = 10054;
	//! 未绑定二次认证信息
	const int TAPIERROR_LOGIN_NOSECONDSET = 10055;
	//! 不受信任的计算机登录
	const int TAPIERROR_LOGIN_NOTURSTHOST = 10056;
	//! 请求二维码失败
	const int TAPIERROR_LOGIN_GETQRCODE = 10057;
	//! 非本交易中心客户
	const int TAPIERROR_LOGIN_NOTINTRADECENTER = 10058;
	//! 版本和后台版本不不一致
	const int TAPIERROR_LOGIN_INCONSISTENT = 10059;
	//! 客户所属交易中心前置地址未配置
	const int TAPIERROR_LOGIN_NOCENTERFRONTADDRESS = 10060;
	//! 不允许此账号类型登录
	const int TAPIERROR_LOGIN_PROHIBITACCOUNTTYPE = 10061;
	//! 不允许增加此类型账号
	const int TAPIERROR_LOGIN_PROHIBITADDACCOUNTTYPE = 10062;

	//! 二次验证失败
	const int TAPIERROR_SECONDCERTIFICATION_FAIL = 14001;
	//! 二次验证超时
	const int TAPIERROR_SECONDCERTIFICATION_TIMEOVER = 14002;
	/** @}*/

	//=============================================================================
	/**
	 *	\addtogroup G_ERR_MANAGE 管理业务处理返回错误码
	 *	@{
	 */
	 //==============================================================================
	//! 登录用户信息查询失败
	const int TAPIERROR_USERINFO_QRY = 10101;
	//! 登录用户下属所有权限查询失败
	const int TAPIERROR_USERALLRIGHT_QRY = 11001;
	//! 登录用户下属所有资金账号查询失败
	const int TAPIERROR_USERALLACCOUNT_QRY = 11501;
	//! 登录用户密码修改失败
	const int TAPIERROR_USERPASSWORD_MOD = 11701;
	//! 登录用户密码修改失败??原始密码错误
	const int TAPIERROR_USERPASSWORD_MOD_SOURCE = 11702;
	//! 登录用户密码修改失败??不能与前n次密码相同
	const int TAPIERROR_USERPASSWORD_MOD_SAME = 11703;
	//! 新密码不符合密码复杂度要求
	const int TAPIERROR_USERPASSWORD_MOD_COMPLEXITY = 11704;
	//! 资金账号信息查询失败
	const int TAPIERROR_ACCOUNTINFO_QRY = 20201;
	//! 客户交易编码查询失败
	const int TAPIERROR_TRADENO_QRY = 20701;
	//! 合约信息查询失败
	const int TAPIERROR_CONTRACTINFO_QRY = 22801;
	//! 特殊期权标的查询失败
	const int TAPIERROR_SPECIALOPTIONFUTURE_QRY = 22901;
	//! 用户下单频率查询失败
	const int TAPIERROR_USER_ORDER_FREQUENCE_QRY = 28901;
    //! 提交信息用户授权类型错误
    const int TAPIERROR_USERSUBMITAUTHTYPE_ERROR = 29591;
   //! 用户采集终端数据为空
    const int TAPIERROR_USERSUBMITINFO_EMPTY = 29592;
    //! 用户密钥版本错误
    const int TAPIERROR_USERAUTHKEYVERSION_ERROR = 29593;
    //! 用户采集信息不全，权限不够
    const int TAPIERROR_USERSUBMITINFO_PARTY = 29594;
 
	/** @}*/

	//=============================================================================
	/**
	 *	\addtogroup G_ERR_TRADE 交易业务处理返回错误码
	 *	@{
	 */
	 //==============================================================================
	 //! 资金账号不存在
	const int TAPIERROR_ORDERINSERT_ACCOUNT = 60001;
	//! 资金账号状态不正确
	const int TAPIERROR_ORDERINSERT_ACCOUNT_STATE = 60002;
	//! 资金账号无委托方向交易权限
	const int TAPIERROR_ORDERINSERT_SIDE_TRADE = 60003;
	//! 资金账号无期权交易权限
	const int TAPIERROR_ORDERINSERT_OPTIONS_TRADE = 60004;
	//! 资金账号无品种交易权限
	const int TAPIERROR_ORDERINSERT_COMMODITY_TRADE = 60005;
	//! 资金账号无开仓权限
	const int TAPIERROR_ORDERINSERT_OPEN_RIGHT = 60006;
	//! 资金账号风控项检查失败
	const int TAPIERROR_ORDERINSERT_RISK_CHECK = 60007;
	//! 下单无效的合约
	const int TAPIERROR_ORDERINSERT_CONTRACT = 60011;
	//! 下单合约无交易路由
	const int TAPIERROR_ORDERINSERT_TRADEROUTE = 60021;
	//! 持仓量超过最大限制
	const int TAPIERROR_ORDERINSERT_POSITIONMAX = 60022;
	//! 禁止交易
	const int TAPIERROR_ORDER_NOTRADE = 60023;
	//! 只可平仓
	const int TAPIERROR_ORDER_CLOSE = 60024;
	//! 下单资金不足
	const int TAPIERROR_ORDERINSERT_NOTENOUGHFUND = 60031;
	//! 不支持的订单类型
	const int TAPIERROR_ORDERINSERT_ORDERTYPE = 60032;
	//! 不支持的时间有效类型
	const int TAPIERROR_ORDERINSERT_TIMEINFORCE = 60033;
	//! 不支持的策略单类型
	const int TAPIERROR_ORDERINSERT_NO_TACTICS = 60034;
	//! 平仓数量超过已有持仓量
	const int TAPIERROR_ORDERINSERT_POSITION_CANNOT_CLOSE = 60035;
	//! 下单自动审核失败
	const int TAPIERROR_ORDERINSERT_AUTOCHECK_FAIL = 60036;
	//! LME未准备就绪
	const int TAPIERROR_ORDERINSERT_LME_NOTREADY = 60037;
	//! 平仓方式错误
	const int TAPIERROR_ORDERINSERT_CLOSEMODE = 60038;
	//! 下单对应的父账号资金不足
	const int TAPIERROR_ORDERINSERT_PARENTNOTENOUGHFUND = 60039;
	//! 互换单的合约格式错误
	const int TAPIERROR_SWAP_CONTRACT = 60040;
	//! 当前客户不能使用此账号交易
	const int TAPIERROR_USERNO_NOTHAS_ACCOUNT = 60051;
	//! 上手通道状态不正常
	const int TAPIERROR_UPPERCHANNEL_BROKEN = 60052;
	//! 上手通道未开通EXIST
	const int TAPIERROR_UPPERCHANNEL_NOT_EXIST = 60053;
	//! 撤单无此系统号
	const int TAPIERROR_ORDERDELETE_NOT_SYSNO = 60061;
	//! 此状态不允许撤单
	const int TAPIERROR_ORDERDELETE_NOT_STATE = 60062;
	//! 此状态不允许激活
	const int TAPIERROR_ORDERACTIVE_NOT_STATE = 60063;
	//! 此状态禁止审核
	const int TAPIERROR_ORDERCHECK_NOT_STATE = 60071;
	//! 订单审核失败
	const int TAPIERROR_ORDERCHECK_FAIL = 60072;
	//! 此状态不允许改单
	const int TAPIERROR_ORDERMODIFY_NOT_STATE = 60081;
	//! 人工单不允许改单
	const int TAPIERROR_ORDERMODIFY_BACK_INPUT = 60082;
	//! 手续费参数错误
	const int TAPIERROR_ORDERINSERT_FEE = 60091;
	//! 保证金参数错误
	const int TAPIERROR_ORDERINSERT_MARGIN = 60092;
	//! 操作账号只可查询
	const int TAPIERROR_ORDER_NO_PERMIT = 60100;
	//! 非做市商不能应价
	const int TAPIERROR_RSPQUOTE_NO_PERMIT = 60101;
	//! 即使子帐号又是做市商不能应价
	const int TAPIERROR_RSPQUOTE_CHILD_NO_PERMIT = 60102;
	//! 下单找不到交易编码
	const int TAPIERROR_TRADENO_NOT_FIND = 60103;
	//! 操作账号只可开仓
	const int TAPIERROR_ORDER_NO_CLOSE = 60104;
	//! 操作账号没有上期挂单查询权限
	const int TAPIERROR_QRY_QUOTE_NO_PERMIT = 60105;
	//! 限期有效单不能小于当前交易日
	const int TAPIERROR_EXPIREDATE_NO_PERMIT = 60106;
	//! 该编码不允许申请或拆分组合
	const int TAPIERROR_CMB_NO_PERMIT = 60107;
	//! 非本服务器标记下的账号不允许操作
	const int TAPIERROR_ORDERSERVER_NO_PERMIT = 60108;
	//! 行权或弃权量超过可用量
	const int TAPIERROR_POSITION_CANNOT_EXEC_OR_ABANDON = 60109;
	//! 没有订单审核权限
	const int TAPIERROR_ORDERCHECK_NO_PERMIT = 60110;
	//! 超过当日最大开仓量
	const int TAPIERROR_ORDERMAXOPENVOL_NO_PERMIT = 60111;
	//! 涨跌停附近禁止反向开仓
	const int TAPIERROR_ORDERLIMIT_OPEN_NO_PERMIT = 60112;
	//! 超过单笔最大下单量
	const int TAPIERROR_ORDER_SINGLEVOL_NO_PERMIT = 60113;
	//! 超过最大持仓量
	const int TAPIERROR_ORDER_POSITIONVOL_NO_PERMIT = 60114;
	//! 非大连应价单不允许两笔委托量不一致
	const int TAPIERROR_ORDER_QTY_NO_PERMIT = 60115;
	//! 子帐号不允许套利申请
	const int TAPIERROR_ORDER_CMB_CHILD_NO_PERMIT = 60116;
	//! 申请不允许重复提交
	const int TAPIERROR_ORDER_APPLY_NO_PERMIT = 60117;
	//! 超过账号下单频率限制
	const int TAPIERROR_ORDER_FREQ_OVERRUN = 60118;
	//! 组合表不存在的组合方向或投保标志
	const int TAPIERROR_COMB_NO_SIDEORHEDGE = 60119;
	//! 当前期权存在合理价差不需要询价
	const int TAPIERROR_REQQUOTE_EXITREASONABLPRICE = 60120;
    //! 应价委托价格不合理
    const int TAPIERROR_RSPQUOTE_PRICE = 60121;
    //! 普通客户不允许撤销强平单
    const int TAPIERROR_RISKORDER_CANCEL = 60122;
    //! 应价委托开平标志不正确
    const int TAPIERROR_RSPQUOTE_EFFECT = 60123;


	//! 资金账号交易中心不一致
	const int TAPIERROR_ORDERINT_ACC_TRADECENT_ERROR = 60503;
	//! 主账号不允许下单
	const int TAPIERROR_ORDERINT_MAINACCOUNT_ERROR = 60504;
	//! 主账号信息错误
	const int TAPIERROR_ORDERINT_MAINACCINFO_ERROR = 60505;
	//! 账号禁止期权市价下单
	const int TAPIERROR_ORDERINT_NO_OPTMARKET_ERROR = 60506;
	//! 下单无效的合约(外盘)
	const int TAPIERROR_IORDERINSERT_CONTRACT = 60511;
	//! LME未准备就绪(外盘)
	const int TAPIERROR_IORDERINSERT_LME_NOTREADY = 60512;
	//! 不支持的下单类型
	const int TAPIERROR_ORDERINSERT_ERROR_ORDER_TYPE = 60513;
	//! 错误的埋单类型
	const int TAPIERROR_ORDERINSERT_READY_TYPE_ERROR = 60514;
	//! 不合法的委托类型
	const int TAPIERROR_ORDERINSERT_ORDER_TYPE_ERROR = 60515;
    //! 下单合约标的合约不存在
    const int TAPIERROR_ORDERINSERT_SUBCONTRACT = 60516;
    //! 现货下单买入数量错误
    const int TAPIERROR_ORDERINSERT_SPOTBUYQTY = 60517;
    //! 非认购期权不允许备兑
    const int TAPIERROR_ORDERINSERT_RESERVE_PUT = 60518;
    //! 买入开仓不允许备兑
    const int TAPIERROR_ORDERINSERT_RESERVE_B_OPEN = 60519;
    //! 卖出平仓不允许备兑
    const int TAPIERROR_ORDERINSERT_RESERVE_S_COVER	= 60520;
	//! 客户权限禁止交易
	const int TAPIERROR_ORDER_NOTRADE_ACCOUNT = 60521;
	//! 客户品种分组禁止交易
	const int TAPIERROR_ORDER_NOTRADE_COM_GROUP = 60522;
	//! 客户合约特设禁止交易
	const int TAPIERROR_ORDER_NOTRADE_ACC_CONTRACT = 60523;
	//! 系统权限禁止交易
	const int TAPIERROR_ORDER_NOTRADE_SYSTEM = 60524;
	//! 客户权限只可平仓
	const int TAPIERROR_ORDER_CLOSE_ACCOUNT = 60525;
	//! 客户合约特设只可平仓
	const int TAPIERROR_ORDER_CLOSE_ACC_CONTRACT = 60526;
	//! 系统权限只可平仓
	const int TAPIERROR_ORDER_CLOSE_SYSTEM = 60527;
	//! 只可平仓提前天数限制只可平仓
	const int TAPIERROR_ORDER_CLOSE_DAYS = 60528;
	//! 客户品种风控权限禁止交易
	const int TAPIERROR_ORDER_NOTRADE_RISK = 60529;
	//! 客户品种风控权限只可平仓
	const int TAPIERROR_ORDER_CLOSE_RISK = 60530;
	//! 持仓量超过最大限制(外盘)
	const int TAPIERROR_IORDERINSERT_POSITIONMAX = 60531;
	//! 下单超过单笔最大量
	const int TAPIERROR_ORDERINSERT_ONCEMAX = 60532;
	//! 下单合约无交易路由(外盘)
	const int TAPIERROR_IORDERINSERT_TRADEROUTE = 60533;
	//! 委托价格超出偏离范围
	const int TAPIERROR_ORDER_IN_MOD_PRICE_ERROR = 60534;
	//! 超过GiveUp最大持仓量
	const int TAPIERROR_ORDER_IN_GIVEUP_POS_MAX = 60535;
    //! 持仓量超过ETF总持仓限制
    const int TAPIERROR_ORDER_ETF_POSITIONMAX = 60536;
    //! 持仓量超过ETF权利仓限制
    const int TAPIERROR_ORDER_ETF_BUYPOSITIONMAX = 60537;
    //! 持仓量超过ETF单日买入开仓限制
    const int TAPIERROR_ORDER_ETF_BUYONEDAYPOSITIONMAX = 60538;
    //! 可用锁定现货不足
    const int TAPIERROR_ORDERINSERT_NOTENOUGHSPOT = 60539;
    //! 现货不支持备兑
    const int TAPIERROR_ORDERINSERT_RESERVE_SPOT = 60540;
	//! 未登录网关
	const int TAPIERROR_UPPERCHANNEL_NOT_LOGIN = 60541;
	//! 未找到网关信息
	const int TAPIERROR_UPPERCHANNEL_NOT_FOUND = 60542;
    //! 此品种不支持解锁或锁定
    const int TAPIERROR_COMMODITY_LOCK = 60543;
    //! 现货未设置对应期权品种
    const int TAPIERROR_SPOT_ROOT_COMMODITY = 60544;
    //! 现货对应期权无交易路由
    const int TAPIERROR_SPOT_ROOTCOM_TRADEROUTE = 60545;
	//! 下单资金不足(外盘)
	const int TAPIERROR_IORDERINSERT_NOTENOUGHFUND = 60551;
	//! 手续费参数错误(外盘)
	const int TAPIERROR_IORDERINSERT_FEE = 60552;
	//! 保证金参数错误(外盘)
	const int TAPIERROR_IORDERINSERT_MARGIN = 60553;
	//! 总基币资金不足
	const int TAPIERROR_ORDERINSERT_BASENOFUND = 60554;
	//! 超过保证金额度
	const int TAPIERROR_ORDERINSERT_MARGINAMOUNT = 60555;
	//! 总基币超过开仓比例限制
	const int TAPIERROR_ORDERINSERT_OPENRATIO = 60556;
	//! 独立币种组超过开仓比例限制
	const int TAPIERROR_ORDERINSERT_GROUP_OPENRATIO = 60557;
	//! 风险阵列参数错误
	const int TAPIERROR_ORDERINSERT_RISKARRAY = 60558;
    //! 总基币超过限购额度限制
    const int TAPIERROR_ORDERINSERT_BUYLIMITE = 60559;
    //! 独立币种组超过限购额度限制
    const int TAPIERROR_ORDERINSERT_GROUP_BUYLIMITE = 60560;

	//! 撤单无此系统号(外盘)
	const int TAPIERROR_IORDERDELETE_NOT_SYSNO = 60561;
	//! 此状态不允许撤单(外盘)
	const int TAPIERROR_IORDERDELETE_NOT_STATE = 60562;
	//! 录单不允许撤单
	const int TAPIERROR_ORDERDELETE_NO_INPUT = 60563;
    //! 不允许撤销锁定/解锁指令
    const int TAPIERROR_ORDERDELETE_NO_TRADE = 60564;
	//! 此状态不允许改单(外盘)
	const int TAPIERROR_IORDERMODIFY_NOT_STATE = 60571;
	//! 人工单不允许改单(外盘)
	const int TAPIERROR_IORDERMODIFY_BACK_INPUT = 60572;
	//! 风险报单不允许改单
	const int TAPIERROR_ORDERMODIFY_RISK_ORDER = 60573;
	//! 成交量大于改单量
	const int TAPIERROR_ORDERMODIFY_ERROR_QTY = 60574;
	//! 预埋单不允许改单
	const int TAPIERROR_ORDERMODIFY_ERROR_READY = 60575;
	//! 已删除报单不能转移
	const int TAPIERROR_ORDERINPUT_CANNOTMOVE = 60581;
	//! 录单重复
	const int TAPIERROR_ORDERINPUT_REPEAT = 60591;
	//! 合约行情价格修改失败
	const int TAPIERROR_CONTRACT_QUOTE = 60601;
	//! 下单超过上手单笔最大量
	const int TAPIERROR_UPPER_ONCEMAX = 60611;
	//! 下单超过上手最大持仓量
	const int TAPIERROR_UPPER_POSITIONMAX = 60612;
	//! 开平方式错误
	const int TAPIERROR_IORDERINSERT_CLOSEMODE = 60621;
	//! 委托平仓持仓不足
	const int TAPIERROR_CLOSE_ORDER = 60622;
	//! 成交平仓失败
	const int TAPIERROR_CLOSE_MATCH = 60623;
	//! 未找到本地委托
	const int TAPIERROR_MOD_DEL_NO_ORDER = 60631;
	//! 与网关断开连接
	const int TAPIERROR_MOD_DEL_GATEWAY_DISCON = 60632;
	//! 录单成交重复
	const int TAPIERROR_MATCHINPUT_REPEAT = 60641;
	//! 录单成交未找到对应委托
	const int TAPIERROR_MATCHINPUT_NO_ORDER = 60642;
	//! 录单成交合约不存在
	const int TAPIERROR_MATCHINPUT_NO_CONTRACT = 60643;
	//! 录单成交参数错误
	const int TAPIERROR_MATCHINPUT_PARM_ERROR = 60644;
	//! 录单成交委托状态错误
	const int TAPIERROR_MATCHINPUT_OSTATE_ERROR = 60645;
	//! 成交删除未找到成交
	const int TAPIERROR_MATCHREMOVE_NO_MATCH = 60651;
	//! 此状态成交不可删
	const int TAPIERROR_MATCHREMOVE_STATE_ERROR = 60652;
	//! 不允许录入此状态订单
	const int TAPIERROR_ORDERINPUT_STATE_ERROR = 60661;
	//! 错误的修改订单请求
	const int TAPIERROR_ORDERINPUT_MOD_ERROR = 60662;
	//! 订单不可删，存在对应成交
	const int TAPIERROR_ORDERREMOVE_ERROR = 60663;
	//! 不合法的委托状态
	const int TAPIERROR_ORDERINPUT_MOD_STATE_ERROR = 60664;
	//! 此状态不允许订单转移
	const int TAPIERROR_ORDEREXCHANGE_STATE_ERROR = 60665;
	//! 订单不允许删除
	const int TAPIERROR_ORDERREMOVE_NOT_ERROR = 60666;
	//! 做市商双边撤单未找到委托
	const int TAPIERROR_ORDERMARKET_DELETE_NOTFOUND = 60671;
	//! 做市商双边撤单客户不一致
	const int TAPIERROR_ORDERMARKET_DEL_ACCOUNT_NE = 60672;
	//! 做市商双边撤单品种不一致
	const int TAPIERROR_ORDERMARKET_DEL_COMMODITY_NE = 60673;
	//! 做市商双边撤单合约不一致
	const int TAPIERROR_ORDERMARKET_DEL_CONTRACT_NE = 60674;
	//! 做市商双边撤单买卖方向相同
	const int TAPIERROR_ORDERMARKET_DEL_SIDE_EQ = 60675;
	//! 做市商双边撤单买卖方向错误
	const int TAPIERROR_ORDERMARKET_DEL_SIDE_ERROR = 60676;
	//! 做市商单边检查未通过
	const int TAPIERROR_ORDERMARKET_OTHER_SIDE_ERROR = 60677;
	//! 埋单激活失败，订单未找到
	const int TAPIERROR_ORDERACTIVATE_NOTFOUND_ERROR = 60681;
	//! 埋单激活失败，非有效状态
	const int TAPIERROR_ORDERACTIVATE_STATE_ERROR = 60682;


	//! 订单操作频率过高
	const int TAPIERROR_ORDER_FREQUENCY = 61001;
	//! 委托查询返回前不能进行下次查询
	const int TAPIERROR_ORDER_QUERYING = 61002;
	/** @}*/

	//=============================================================================
	/**
	 *	\addtogroup G_ERR_CELPHONE 手机仿真返回错误码
	 *	@{
	 */
	//==============================================================================
	//! 会员系统地址信息不存在
	const int TAPIERROR_AddressLoss = 990001;
	//! 系统尚未登录
	const int TAPIERROR_UnLogin = 990002;
	//! 认证信息加密失败
	const int TAPIERROR_AuthEncryptFail = 990003;
	//! 网关未连或无效的后台
	const int TAPIERROR_ChannelCreateFail = 990004;
	//! 网关未就绪
	const int TAPIERROR_ChannelUnready = 990005;
	//! 协议格式错误
	const int TAPIERROR_PtlFmtError = 990006;
	//! 策略单服务未启用
	const int TAPIERROR_StrategyInactive = 990007;
	//! 策略单数据正在初始化中
	const int TAPIERROR_StrategyIniting = 990008;
	//! 密码错误
	const int TAPIERROR_PwdFail = 990009;
	//! 未找到原有连接
	const int TAPIERROR_NoUser = 990010;
	//! 登录数超限
	const int TAPIERROR_OnlineCountFail = 990011;
	//! 策略单已登录
	const int TAPIERROR_StrategyLogined = 990012;
	//! 请重新登录
	const int TAPIERROR_ReLogin = 990013;
	//! 触发时无法找到合适委托价
	const int TAPIERROR_NoPrice = 990101;
	//! 无法识别的策略单
	const int TAPIERROR_NoStrategy = 990102;
	//! 无法找到父单号
	const int TAPIERROR_NoParentOrder = 990103;
	//! 父单触发失败子单失效
	const int TAPIERROR_ParentOrderFail = 990104;
	//! 策略单未填写交易日
	const int TAPIERROR_NoTradeDate = 990105;
	//! 策略单操作未找到原定单
	const int TAPIERROR_NoOrderNo = 990106;
	//! 可平量不足
	const int TAPIERROR_CannotClose = 990107;
	//! 策略单立即触发
	const int TAPIERROR_ImmediateTrigger = 990108;
	//! 策略单立即触发
	const int TAPIERROR_OrderUnusual = 990109;
	//! 没有行情的合约
	const int TAPIERROR_NoQuote = 990110;
	//! 不支持的操作
	const int TAPIERROR_UnsupportedAction = 990201;
	//! 期货公司地址无法连接
	const int TAPIERROR_InvalidAddress = 990202;
	//! 不支持交易员登录
	const int TAPIERROR_UnsupportedLoginNo = 990203;
	//! 密码错误
	const int TAPIERROR_GwPwdFail = 990204;
	//! 密码错误次数超限
	const int TAPIERROR_PwdFailLimit = 990205;
	//! 非正常交易时段
	const int TAPIERROR_InvalidMarketState = 990206;
	//! 强制修改密码
	const int TAPIERROR_ForceChangePwd = 990207;
	//! 登录数超限
	const int TAPIERROR_LoginCount = 990208;
	//! 不支持的合约
	const int TAPIERROR_UnsupportedContract = 990301;
	//! 不支持的订单类型
	const int TAPIERROR_UnsupportedOrderType = 990302;
	//! 持仓不足平
	const int TAPIERROR_InadequatePosiQty = 990303;
	//! 资金不足
	const int TAPIERROR_InadequateMoney = 990304;
	//! 价格不在涨跌停范围
	const int TAPIERROR_UnsupportedPrice = 990305;
	//! 价格订单操作类型
	const int TAPIERROR_UnsupportedActType = 990306;
	//! 该委托状态无法撤单
	const int TAPIERROR_CancelState = 990307;
	//! 报单字段有误
	const int TAPIERROR_OrderFieldErr = 990308;
	//! 下单账号与登录账号不一致
	const int TAPIERROR_UnsupportedAcc = 990309;
	//! 委托不存在
	const int TAPIERROR_UnsupportedOrder = 990310;
	//! 不支持的币种
	const int TAPIERROR_UnsupportedCurrency = 990311;
	//! 发送登录请求失败
	const int TAPIERROR_SendLoginFail = 990312;
	//! 非交易时间
	const int TAPIERROR_InvalidTime = 990313;
	//! 行权/弃权可用量不足
	const int TAPIERROR_InadequateExecQty = 990314;
	
	/** @}*/
}

#endif /* ESTRADEAPIERROR_H */

