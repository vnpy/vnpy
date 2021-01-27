/*************************
*摘要：南华期货交易系统
*文件：NhUserApiStruct.h
*      定义了客户端接口数据结构
*作者：南华期货软件部
*时间：20100220
**************************/

#ifndef __NH_USERAPI_STRUCT_H__
#define __NH_USERAPI_STRUCT_H__

#include "NHUserApiDataType.h"

#include <iostream>

using namespace std;


struct STKMarketData_t //即时数据结构
{
	TDateType trading_day;							//交易日，内盘有数据、外盘无
	TTimeType update_time;							//最后更新时间
	TMillisecType	update_millisec;					//最后修改毫秒
	TSequenceIDType	update_sequence;					//今日更新序号

	TContractNoType instrument_id;					//合约代码
	TExchangeNoType exchange_id;						//交易所代码
	TContractNoType exchange_inst_id;					//合约在交易所的代码
	TContractTradeStateType instrument_status;			//合约交易状态

	TPriceType last_price;							//最新价
	TVolumeType volume;								//成交量，期货全是整数，股票有小数
	TVolumeType last_volume;							//最新成交量
	TMoneyType turnover;								//成交金额
	TVolumeType open_interest;						//持仓量
	TPriceType open_price;							//今日开盘价
	TPriceType highest_price;						//当日最高价
	TPriceType lowest_price;							//当日最低价
	TPriceType close_price;							//今日收盘价
	TPriceType settlement_price;						//今日结算价
	TPriceType average_price;						//今日均价

	TPriceType change_price;							//涨跌
	TRangeType change_markup;						//涨跌幅
	TRangeType change_swing;							//振幅

	TPriceType upper_limit_price;						//涨停板价
	TPriceType lower_limit_price;						//跌停板价

	TPriceType pre_settlement_price;					//昨日结算价
	TPriceType pre_close_price;						//昨日收盘价
	TVolumeType pre_open_interest;					//昨日持仓量

	TDeltaType pre_delta;							//昨虚实度
	TDeltaType curr_delta;							//今虚实度

	TPriceType	best_ask_price;							//最优卖价
	TVolumeType	best_ask_volume;					//最优卖量
	TPriceType	best_bid_price;							//最优买价
	TVolumeType	best_bid_volume;				//最优买量

	TPriceType	ask_price1;								//申卖价1
	TVolumeType	ask_volume1;						//申卖量1
	TPriceType	bid_price1;								//申买价1
	TVolumeType	bid_volume1;						//申买量1
	TPriceType	ask_price2;								//申卖价2
	TVolumeType	ask_volume2;						//申卖量2
	TPriceType	bid_price2;								//申买价2
	TVolumeType	bid_volume2;						//申买量2
	TPriceType	ask_price3;								//申卖价3
	TVolumeType	ask_volume3;						//申卖量3
	TPriceType	bid_price3;								//申买价3
	TVolumeType	bid_volume3;						//申买量3
	TPriceType	ask_price4;								//申卖价4
	TVolumeType	ask_volume4;						//申卖量4
	TPriceType	bid_price4;								//申买价4
	TVolumeType	bid_volume4;						//申买量4
	TPriceType	ask_price5;								//申卖价5
	TVolumeType	ask_volume5;						//申卖量5
	TPriceType	bid_price5;								//申买价5
	TVolumeType	bid_volume5;						//申买量5
	TPriceType	ask_price6;								//申卖价6
	TVolumeType	ask_volume6;						//申卖量6
	TPriceType	bid_price6;								//申买价6
	TVolumeType	bid_volume6;						//申买量6
	TPriceType	ask_price7;								//申卖价7
	TVolumeType	ask_volume7;						//申卖量7
	TPriceType	bid_price7;								//申买价7
	TVolumeType	bid_volume7;						//申买量7
	TPriceType	ask_price8;								//申卖价8
	TVolumeType	ask_volume8;						//申卖量8
	TPriceType	bid_price8;								//申买价8
	TVolumeType	bid_volume8;						//申买量8
	TPriceType	ask_price9;								//申卖价9
	TVolumeType	ask_volume9;						//申卖量9
	TPriceType	bid_price9;								//申买价9
	TVolumeType	bid_volume9;						//申买量9
	TPriceType	ask_price10;								//申卖价10
	TVolumeType	ask_volume10;						//申卖量10
	TPriceType	bid_price10;								//申买价10
	TVolumeType	bid_volume10;						//申买量10
	TMdSourceType	md_source;						//行情来源
};


//错误消息结构
typedef struct ERRORMSGINFO
{
	TErrorCodeType error_code;			//错误代码
	TErrorMessageType error_message;		//错误消息
	/*如果该错误是由服务器消息引起的，则以下字段对应服务器返回消息*/
	TRspCodeType response_code;			//响应代码, 0为成功，负数为各类错误，1为最后一条
	TRspStringType response_string;		//响应文本信息
	TServerIDType utp_server_id;			    //处理请求的UTP服务器信息
	TServerIDType oms_server_id;			//处理请求的OMS服务器信息
}ERRORMSGINFO_t;

//登录南华统一交易平台UTP请求结构
typedef struct ReqUtpLoginField
{
	TDevelopCodeType developer_code;				//开发者编码(必填)
	TDevelopLicenseType developer_license;			//开发者授权(必填)
	TUserIDType user_id;							//登录用户(必填)
	TPassWordType user_password;					//登录静态密码，使用静态publickey加密
	TOneTimePassWordType user_one_time_password;	//动态口令
	TCAInfoType	user_ca_info;						//ca验证信息
}ReqUtpLoginField_t;

//登录南华统一交易平台UTP应答结构
typedef struct RspUtpLoginField 
{
	TRspCodeType response_code;				//响应代码, 0为成功，-1静态口令错误，-2动态口令错误，-3ca验证错误，-4必须是OTP登录，-5必须是CA登录，-6回调消息Q不存在，-7服务器故障，-8绑定失败
	TRspStringType response_string;			//响应信息
	TPublicKeyType session_public_key;		//服务器分配的会话加密公钥，交易密码信息需要加密后传输
	TServerCDKeyType utp_checking_server_id;	//验证服务器识别码
	TLongTimeType	utp_checking_server_time;	//验证服务器时间，long格式
	TIpType last_login_ip_address;		//上次登录来源IP
	TLongTimeType last_login_time;			//上次登录时间
	TIsEncryptType session_encrypted;			//是否加密传输通道
}RspUtpLoginField_t;


//登出南华统一交易平台UTP应答结构
typedef struct RspUtpLogoutField
{
	TRspCodeType response_code;		//响应代码, 0为成功，负数为各类错误，1为最后一条
	TRspStringType response_string;	//响应文本信息
	TServerIDType utp_server_id;		//处理请求的UTP服务器信息
}RspUtpLogoutField_t;


/* 订阅行情数据请求结构
	*	routing_key:订阅规则,具体规则如下：
	*			 交易所.品种代码.合约代码
	*			 交易所代码为：B:上期所;G:中金所;D:大商所;C:郑商所
	*						 如：G.IF.1203:为中金所12年3月股指期货行情数据
	*			 商品代码为该期货对应的期货合约代码，大小写敏感，其中：
	*						上期所和大商所品种代码需小写;
	*						中金所和郑商所品种代码需大写
	*			如果用户省略某一部分，则系统默认订阅全部，
	*						 如：G.IF.则订阅中金所品种代码为IF的所有股指期货行情数据
	*						 如：B.则订阅上期所所有行情数据
	*			如果用户通过省略的方式来订阅某一个部分全部合约，则必须以"."结束，且交易所不能省略。
	*			即，用户不能通过"."来订阅所有交易所的合约数据。
	*/
typedef struct ReqSubscribeField
{
	TRouteKeyType  routing_key;		//订阅规则，每次最多订阅100条
}ReqSubscribeField_t;

//订阅行情数据应答结构
typedef struct RspSubscribeField 
{
	TRspCodeType	response_code;	//响应代码, 0为成功，负数为各类错误
	TRspStringType	response_string;	//成功订阅的消息
	TServerIDType	utp_server_id;
	TRouteKeyType	routing_key;		//订阅成功的信息
}RspSubscribeField_t;

//取消订阅行情数据请求结构
typedef struct ReqUnSubscribeField
{
	TRouteKeyType  routing_key;			//订阅规则，每次最多取消100条
}ReqUnSubscribeField_t;

//取消订阅行情数据应答结构
typedef struct RspUnSubscribeField 
{
	TRspCodeType	response_code;		//响应代码, 0为成功，负数为各类错误
	TRspStringType	response_string;		//响应文本信息
	TServerIDType	utp_server_id;
	TRouteKeyType	routing_key;			//取消成功的订阅信息
}RspUnSubscribeField_t;

//用户验证数据请求结构
typedef struct ReqAuthUserPassworField
{
	TUserIDType user_id;							//用户名
	TPassWordType password;				//密码
	TSaveIntType save_int;						//保留字段
	TSaveDoubleType save_double;		//保留字段
	TSaveStringType save_string;			//保留字段
}ReqAuthUserPassworField_t;

//用户验证数据应答结构
typedef struct RspAuthUserPassworField 
{
	TRspCodeType response_code;		//响应代码, 0为成功，负数为各类错误
	TRspStringType response_string;	//响应文本信息
}RspAuthUserPassworField_t;

//报单数据
typedef struct ReqOrderInsertData 
{
	TClientNoType client_id;							//客户号
	TCommodityNoType commodity_id;		//商品代码
	TContractNoType instrument_id;				//合约代码
	TOrderTypeType order_type;					//委托类型
	TOrderModeType order_mode;				//委托模式
	TOrderWayType order_way;					//委托方式
	TDateType valid_datetime;						//有效日期(GTD情况下使用)
	TIsRiskOrderType is_riskorder;				//风险报单
	TDirectType direct;									//买入卖出
	TOffsetType offset;									//开仓平仓:N:无,O:开仓,C:平仓,T:平今,
	THedgeType hedge;									//投机保值:N:无,T:投机,B:保值
	TPriceType order_price;							//委托价格
	TPriceType trigger_price;							//触发价格
	TVolumeType order_vol;						//委托数量
	TVolumeType min_matchvol;				//最小成交量
	TSaveIntType save_int;								//客户保留字段1
	TSaveDoubleType save_double;				//客户保留字段2
	TSaveStringType save_string;					//客户保留字段3
}ReqOrderInsertData_t;

//报单请求
typedef struct ReqOrderInsertField 
{
	TServerIDType oms_server_id;			//OMS编码
	TExchangeNoType exchange_id;			//交易所代码
	ReqOrderInsertData req_data;				    //报单数据
}ReqOrderInsertField_t;

//报单应答
typedef struct RspOrderInsertField 
{
	TRspCodeType response_code;			//响应代码, 0为成功，1为最后一条
	TRspStringType response_string;		//响应文本信息
	TServerIDType utp_server_id;				//处理请求的UTP服务器信息
	TServerIDType oms_server_id;			//处理请求的OMS服务器信息
	TStreamIdType order_stream_id;		//委托流号
	TOrderIdType order_id;						//委托号
	TLocalNoType local_id;							//本地号
	TClientNoType trade_id;							//交易账号
	TClientNoType insert_id;						//下单人
	TDateTimeType insert_datetime;		//下单时间
	TOrderStateType order_state;				//委托状态
	ReqOrderInsertData req_data;					//报单数据
}RspOrderInsertField_t;

//查询交易所请求结构
typedef struct ReqQryExchangeField
{
	TServerIDType oms_server_id;		//OMS编码
}ReqQryExchangeField_t;

//查询交易所应答结构
typedef struct RspQryExchangeField 
{
	TRspCodeType response_code;			//响应代码, 0为成功，负数为各类错误
	TRspStringType response_string;		//响应文本信息
	TServerIDType utp_server_id;			//处理请求的UTP服务器信息
	TServerIDType oms_server_id;			//处理请求的OMS服务器信息
	TExchangeNoType exchange_id;			//交易所代码
	TExchangeNameType exchange_name;		//交易所名称
	TExchangeStateType exchange_status;	//交易所状态
}RspQryExchangeField_t;

//查询合约请求结构
typedef struct ReqQryInstrumentField 
{
	TServerIDType oms_server_id;		//OMS编码
	TExchangeNoType exchange_id;		//交易所代码
	TCommodityNoType product_id;		//商品代码
	TContractNoType instrument_id;	//合约代码
	TCommodityTypeType product_class;	//商品类型:(默认为F:COMMODITY_TYPE_FUTURE)
}ReqQryInstrumentField_t;

//查询合约应答结构
typedef struct RspQryInstrumentField 
{
	TRspCodeType response_code;		//响应代码, 0为成功，负数为各类错误
	TRspStringType response_string;	//响应文本信息
	TServerIDType utp_server_id;			//处理请求的UTP服务器信息
	TServerIDType oms_server_id;			//处理请求的OMS服务器信息
	TCommodityNoType product_id;			//商品代码
	TCommodityNameType product_name;			//商品名称
	TExchangeNoType exchange_id;			//交易所代码
	TCommodityTypeType product_class;			//商品类型
	TContractNoType instrument_id;			//合约代码
	TContractNameType instrument_name;		//合约名称
	TContractTypeType instrument_class;		//合约类别
	TContractStateType instrument_status;		//合约状态
	TYearType	delivery_year;			//交割年份
	TMonthType	delivery_month;			//交割月份
	TProductDotType volume_multiple;		//合约乘数
	TUpperTickType price_tick;			//最小变动价位
	TLowerTickType price_tick_dividend;	//最小变动价位分母，一般为1，分数报价时不为1
	TVolumeType max_marketorder_volume;	//市价单最大下单量
	TVolumeType min_marketorder_volume;	//市价单最小下单量
	TVolumeType max_limitorder_volume;	//限价单最大下单量
	TVolumeType min_limitorder_volume;	//限价单最小下单量
	TDateType create_date;			//创建日
	TDateType open_date;				//上市日
	TDateType expire_date;			//到期日
	TDateType last_trading_date;		//最后交易日
	TDateType start_delivery_date;	//开始交割日
	TDateType end_delivery_date;		//结束交割日
	TDateType first_notice_date;		//首次通知日
}RspQryInstrumentField_t;

#endif
