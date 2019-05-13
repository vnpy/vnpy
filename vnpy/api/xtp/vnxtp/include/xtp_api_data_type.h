/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file xtp_api_data_type.h
///@brief 定义兼容数据基本类型
/////////////////////////////////////////////////////////////////////////
#ifndef _XTP_API_DATA_TYPE_H_
#define _XTP_API_DATA_TYPE_H_

#pragma pack(8)

/// 存放版本号的字符串长度
#define XTP_VERSION_LEN 16
/// 版本号类型
typedef char XTPVersionType[XTP_VERSION_LEN];
/// 可交易日字符串长度
#define XTP_TRADING_DAY_LEN 9
/// 存放证券代码的字符串长度
#define XTP_TICKER_LEN 16
/// 存放证券名称的字符串长度
#define XTP_TICKER_NAME_LEN 64
/// 本地报单编号的字符串长度
#define XTP_LOCAL_ORDER_LEN         11
/// 交易所单号的字符串长度
#define XTP_ORDER_EXCH_LEN          17
/// 成交执行编号的字符串长度
#define XTP_EXEC_ID_LEN             18
/// 交易所交易员代码字符串长度
#define XTP_BRANCH_PBU_LEN          7
/// 用户资金账户的字符串长度
#define XTP_ACCOUNT_NAME_LEN        16

/////////////////////////////////////////////////////////////////////////
///@brief XTP_LOG_LEVEL是日志输出级别类型
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_LOG_LEVEL {
	XTP_LOG_LEVEL_FATAL, ///<严重错误级别
	XTP_LOG_LEVEL_ERROR, ///<错误级别
	XTP_LOG_LEVEL_WARNING, ///<警告级别
	XTP_LOG_LEVEL_INFO,   ///<info级别
	XTP_LOG_LEVEL_DEBUG,  ///<debug级别
	XTP_LOG_LEVEL_TRACE   ///<trace级别
}XTP_LOG_LEVEL;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_PROTOCOL_TYPE是通讯传输协议方式
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_PROTOCOL_TYPE
{
	XTP_PROTOCOL_TCP = 1,	///<采用TCP方式传输
	XTP_PROTOCOL_UDP		///<采用UDP方式传输(仅行情接口支持)
}XTP_PROTOCOL_TYPE;



/////////////////////////////////////////////////////////////////////////
///@brief XTP_EXCHANGE_TYPE是交易所类型
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_EXCHANGE_TYPE
{
	XTP_EXCHANGE_SH = 1,	///<上证
	XTP_EXCHANGE_SZ,		///<深证
    XTP_EXCHANGE_UNKNOWN	///<不存在的交易所类型
}XTP_EXCHANGE_TYPE;

//////////////////////////////////////////////////////////////////////////
///@brief XTP_MARKET_TYPE市场类型
//////////////////////////////////////////////////////////////////////////
typedef enum XTP_MARKET_TYPE
{
    XTP_MKT_INIT = 0,///<初始化值或者未知
    XTP_MKT_SZ_A = 1,///<深圳A股
    XTP_MKT_SH_A,    ///<上海A股
    XTP_MKT_UNKNOWN   ///<未知交易市场类型
}XTP_MARKET_TYPE;


/////////////////////////////////////////////////////////////////////////
///@brief XTP_PRICE_TYPE是价格类型
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_PRICE_TYPE
{
	XTP_PRICE_LIMIT = 1,           ///<限价单-沪 / 深 / 沪期权（除普通股票业务外，其余业务均使用此种类型）
	XTP_PRICE_BEST_OR_CANCEL,      ///<即时成交剩余转撤销，市价单-深 / 沪期权
	XTP_PRICE_BEST5_OR_LIMIT,      ///<最优五档即时成交剩余转限价，市价单-沪
	XTP_PRICE_BEST5_OR_CANCEL,     ///<最优5档即时成交剩余转撤销，市价单-沪深
	XTP_PRICE_ALL_OR_CANCEL,       ///<全部成交或撤销,市价单-深 / 沪期权
	XTP_PRICE_FORWARD_BEST,        ///<本方最优，市价单-深
	XTP_PRICE_REVERSE_BEST_LIMIT,  ///<对方最优剩余转限价，市价单-深 / 沪期权
	XTP_PRICE_LIMIT_OR_CANCEL,	   ///<期权限价申报FOK
	XTP_PRICE_TYPE_UNKNOWN,		   ///<未知或者无效价格类型
}XTP_PRICE_TYPE;



/////////////////////////////////////////////////////////////////////////
///@brief XTP_SIDE_TYPE是买卖方向类型
/////////////////////////////////////////////////////////////////////////
typedef uint8_t XTP_SIDE_TYPE;

///买（新股申购，ETF买，配股，信用交易中担保品买）
#define XTP_SIDE_BUY            1
///卖（逆回购，ETF卖，信用交易中担保品卖）
#define XTP_SIDE_SELL           2
///申购
#define XTP_SIDE_PURCHASE       7
///赎回
#define XTP_SIDE_REDEMPTION     8
///拆分
#define XTP_SIDE_SPLIT          9
///合并
#define XTP_SIDE_MERGE          10
///改版之后的side的备兑，暂不支持
#define XTP_SIDE_COVER          11
///改版之后的side锁定（对应开平标识为开）/解锁（对应开平标识为平）
#define XTP_SIDE_FREEZE         12
/// 融资买入
#define XTP_SIDE_MARGIN_TRADE	21
/// 融券卖出
#define XTP_SIDE_SHORT_SELL		22
/// 卖券还款
#define XTP_SIDE_REPAY_MARGIN	23
/// 买券还券
#define XTP_SIDE_REPAY_STOCK	24
/// 现金还款
#define XTP_SIDE_CASH_REPAY_MARGIN	25
/// 现券还券
#define XTP_SIDE_STOCK_REPAY_STOCK	26
///未知或者无效买卖方向
#define XTP_SIDE_UNKNOWN        27



/////////////////////////////////////////////////////////////////////////
///@brief XTP_POSITION_EFFECT_TYPE是开平标识类型
/////////////////////////////////////////////////////////////////////////
typedef uint8_t XTP_POSITION_EFFECT_TYPE;

/// 初始值或未知值开平标识，现货适用
#define XTP_POSITION_EFFECT_INIT                0
/// 开
#define XTP_POSITION_EFFECT_OPEN                1
/// 平
#define XTP_POSITION_EFFECT_CLOSE               2
/// 强平
#define XTP_POSITION_EFFECT_FORCECLOSE          3
/// 平今
#define XTP_POSITION_EFFECT_CLOSETODAY          4
/// 平昨
#define XTP_POSITION_EFFECT_CLOSEYESTERDAY      5
/// 强减
#define XTP_POSITION_EFFECT_FORCEOFF            6
/// 本地强平
#define XTP_POSITION_EFFECT_LOCALFORCECLOSE     7
/// 未知的开平标识类型
#define XTP_POSITION_EFFECT_UNKNOWN             8


/////////////////////////////////////////////////////////////////////////
///@brief XTP_ORDER_ACTION_STATUS_TYPE是报单操作状态类型
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_ORDER_ACTION_STATUS_TYPE
{
	XTP_ORDER_ACTION_STATUS_SUBMITTED = 1,	///<已经提交
	XTP_ORDER_ACTION_STATUS_ACCEPTED,		///<已经接受
	XTP_ORDER_ACTION_STATUS_REJECTED		///<已经被拒绝
}XTP_ORDER_ACTION_STATUS_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_ORDER_STATUS_TYPE是报单状态类型
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_ORDER_STATUS_TYPE
{
    XTP_ORDER_STATUS_INIT = 0,///<初始化
    XTP_ORDER_STATUS_ALLTRADED = 1,           ///<全部成交
    XTP_ORDER_STATUS_PARTTRADEDQUEUEING,  ///<部分成交
    XTP_ORDER_STATUS_PARTTRADEDNOTQUEUEING, ///<部分撤单
    XTP_ORDER_STATUS_NOTRADEQUEUEING,   ///<未成交
    XTP_ORDER_STATUS_CANCELED,  ///<已撤单
    XTP_ORDER_STATUS_REJECTED,  ///<已拒绝
    XTP_ORDER_STATUS_UNKNOWN  ///<未知订单状态
}XTP_ORDER_STATUS_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_ORDER_SUBMIT_STATUS_TYPE是报单提交状态类型
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_ORDER_SUBMIT_STATUS_TYPE
{
    XTP_ORDER_SUBMIT_STATUS_INSERT_SUBMITTED = 1, ///<订单已经提交
    XTP_ORDER_SUBMIT_STATUS_INSERT_ACCEPTED,///<订单已经被接受
    XTP_ORDER_SUBMIT_STATUS_INSERT_REJECTED,///<订单已经被拒绝
    XTP_ORDER_SUBMIT_STATUS_CANCEL_SUBMITTED,///<撤单已经提交
    XTP_ORDER_SUBMIT_STATUS_CANCEL_REJECTED,///<撤单已经被拒绝
    XTP_ORDER_SUBMIT_STATUS_CANCEL_ACCEPTED ///<撤单已经被接受
}XTP_ORDER_SUBMIT_STATUS_TYPE;


/////////////////////////////////////////////////////////////////////////
///@brief XTP_TE_RESUME_TYPE是公有流（订单响应、成交回报）重传方式
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_TE_RESUME_TYPE
{
	XTP_TERT_RESTART = 0,	///<从本交易日开始重传
	XTP_TERT_RESUME,		///<从从上次收到的续传（暂未支持）
	XTP_TERT_QUICK			///<只传送登录后公有流（订单响应、成交回报）的内容
}XTP_TE_RESUME_TYPE;


//////////////////////////////////////////////////////////////////////////
///@brief ETF_REPLACE_TYPE现金替代标识定义
//////////////////////////////////////////////////////////////////////////
typedef enum ETF_REPLACE_TYPE
{
    ERT_CASH_FORBIDDEN = 0,             ///<禁止现金替代
    ERT_CASH_OPTIONAL,                  ///<可以现金替代
    ERT_CASH_MUST,                      ///<必须现金替代
    ERT_CASH_RECOMPUTE_INTER_SZ,        ///<深市退补现金替代
    ERT_CASH_MUST_INTER_SZ,             ///<深市必须现金替代
    ERT_CASH_RECOMPUTE_INTER_OTHER,     ///<非沪深市场成分证券退补现金替代
    ERT_CASH_MUST_INTER_OTHER,          ///<表示非沪深市场成份证券必须现金替代
    EPT_INVALID                         ///<无效值
}ETF_REPLACE_TYPE;


//////////////////////////////////////////////////////////////////////////
///@brief XTP_TICKER_TYPE证券类型
//////////////////////////////////////////////////////////////////////////
typedef enum XTP_TICKER_TYPE
{
	XTP_TICKER_TYPE_STOCK = 0,            ///<普通股票
	XTP_TICKER_TYPE_INDEX,                ///<指数
	XTP_TICKER_TYPE_FUND,                 ///<基金
	XTP_TICKER_TYPE_BOND,                 ///<债券
	XTP_TICKER_TYPE_OPTION,               ///<期权
	XTP_TICKER_TYPE_UNKNOWN               ///<未知类型
	
}XTP_TICKER_TYPE;

//////////////////////////////////////////////////////////////////////////
///@brief XTP_BUSINESS_TYPE证券业务类型
//////////////////////////////////////////////////////////////////////////
typedef enum XTP_BUSINESS_TYPE
{
	XTP_BUSINESS_TYPE_CASH = 0,            ///<普通股票业务（股票买卖，ETF买卖等）
	XTP_BUSINESS_TYPE_IPOS,                ///<新股申购业务（对应的price type需选择限价类型）
	XTP_BUSINESS_TYPE_REPO,                ///<回购业务 ( 对应的price type填为限价，side填为卖 )
	XTP_BUSINESS_TYPE_ETF,                 ///<ETF申赎业务
	XTP_BUSINESS_TYPE_MARGIN,              ///<融资融券业务（暂未支持）
	XTP_BUSINESS_TYPE_DESIGNATION,         ///<转托管（未支持）
	XTP_BUSINESS_TYPE_ALLOTMENT,		   ///<配股业务（对应的price type需选择限价类型,side填为买）
	XTP_BUSINESS_TYPE_STRUCTURED_FUND_PURCHASE_REDEMPTION,	   ///<分级基金申赎业务
	XTP_BUSINESS_TYPE_STRUCTURED_FUND_SPLIT_MERGE,	   ///<分级基金拆分合并业务
	XTP_BUSINESS_TYPE_MONEY_FUND,		   ///<货币基金业务（暂未支持）
    XTP_BUSINESS_TYPE_OPTION,              ///<期权业务
    XTP_BUSINESS_TYPE_EXECUTE,             ///<行权
    XTP_BUSINESS_TYPE_FREEZE,              ///<锁定解锁，暂不支持
	XTP_BUSINESS_TYPE_UNKNOWN              ///<未知类型

}XTP_BUSINESS_TYPE;

//////////////////////////////////////////////////////////////////////////
///@brief XTP_ACCOUNT_TYPE账户类型
//////////////////////////////////////////////////////////////////////////
typedef enum XTP_ACCOUNT_TYPE
{
    XTP_ACCOUNT_NORMAL = 0,	///<普通账户
    XTP_ACCOUNT_CREDIT,		///<信用账户
    XTP_ACCOUNT_DERIVE,		///<衍生品账户
    XTP_ACCOUNT_UNKNOWN		///<未知账户类型
}XTP_ACCOUNT_TYPE;


/////////////////////////////////////////////////////////////////////////
///@brief XTP_FUND_TRANSFER_TYPE是资金流转方向类型
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_FUND_TRANSFER_TYPE
{
    XTP_FUND_TRANSFER_OUT = 0,		///<转出 从XTP转出到柜台
    XTP_FUND_TRANSFER_IN,	        ///<转入 从柜台转入XTP
    XTP_FUND_TRANSFER_UNKNOWN		///<未知类型
}XTP_FUND_TRANSFER_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_FUND_OPER_STATUS柜台资金操作结果
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_FUND_OPER_STATUS {
    XTP_FUND_OPER_PROCESSING = 0,	///<XOMS已收到，正在处理中
    XTP_FUND_OPER_SUCCESS,			///<成功
    XTP_FUND_OPER_FAILED,			///<失败
    XTP_FUND_OPER_SUBMITTED,		///<已提交到集中柜台处理
    XTP_FUND_OPER_UNKNOWN			///<未知
}XTP_FUND_OPER_STATUS;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_SPLIT_MERGE_STATUS是一个基金当天拆分合并状态类型
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_SPLIT_MERGE_STATUS {
	XTP_SPLIT_MERGE_STATUS_ALLOW = 0,	///<允许拆分和合并
	XTP_SPLIT_MERGE_STATUS_ONLY_SPLIT,	///<只允许拆分，不允许合并
	XTP_SPLIT_MERGE_STATUS_ONLY_MERGE,	///<只允许合并，不允许拆分
	XTP_SPLIT_MERGE_STATUS_FORBIDDEN	///<不允许拆分合并
}XTP_SPLIT_MERGE_STATUS;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_TBT_TYPE是一个逐笔回报类型
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_TBT_TYPE {
	XTP_TBT_ENTRUST = 1,	///<逐笔委托
	XTP_TBT_TRADE = 2,		///<逐笔成交
}XTP_TBT_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_OPT_CALL_OR_PUT_TYPE是一个认沽或认购类型
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_OPT_CALL_OR_PUT_TYPE {
	XTP_OPT_CALL = 1,	    ///<认购
	XTP_OPT_PUT = 2,		///<认沽
}XTP_OPT_CALL_OR_PUT_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_OPT_EXERCISE_TYPE_TYPE是一个行权方式类型
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_OPT_EXERCISE_TYPE_TYPE {
	XTP_OPT_EXERCISE_TYPE_EUR = 1,	    ///<欧式
	XTP_OPT_EXERCISE_TYPE_AME = 2,		///<美式
}XTP_OPT_EXERCISE_TYPE_TYPE;

/////////////////////////////////////////////////////////////////////////
///@brief XTP_POSITION_DIRECTION_TYPE是一个持仓方向类型
/////////////////////////////////////////////////////////////////////////
typedef enum XTP_POSITION_DIRECTION_TYPE {
	XTP_POSITION_DIRECTION_NET = 0,	    ///<净
	XTP_POSITION_DIRECTION_LONG,		///<多（期权则为权利方）
    XTP_POSITION_DIRECTION_SHORT,       ///<空（期权则为义务方）
    XTP_POSITION_DIRECTION_COVERED,     ///<备兑（期权则为备兑义务方）
}XTP_POSITION_DIRECTION_TYPE;




/////////////////////////////////////////////////////////////////////////
///TXTPTradeTypeType是成交类型类型
/////////////////////////////////////////////////////////////////////////
typedef char TXTPTradeTypeType;

///普通成交
#define XTP_TRDT_COMMON '0'
///现金替代
#define XTP_TRDT_CASH '1'
///一级市场成交
#define XTP_TRDT_PRIMARY '2'


/////////////////////////////////////////////////////////////////////////
///TXTPOrderTypeType是报单类型类型
/////////////////////////////////////////////////////////////////////////
typedef char TXTPOrderTypeType;

///正常
#define XTP_ORDT_Normal '0'
///报价衍生
#define XTP_ORDT_DeriveFromQuote '1'
///组合衍生
#define XTP_ORDT_DeriveFromCombination '2'
///组合报单
#define XTP_ORDT_Combination '3'
///条件单
#define XTP_ORDT_ConditionalOrder '4'
///互换单
#define XTP_ORDT_Swap '5'


#pragma pack()

#endif
