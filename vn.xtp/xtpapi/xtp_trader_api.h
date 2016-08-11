/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file xtp_trader_api.h
///@brief 定义客户端交易接口
/////////////////////////////////////////////////////////////////////////

#ifndef _XTP_TRADER_API_H_
#define _XTP_TRADER_API_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xtp_api_struct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#define TRADER_API_EXPORT 
#endif

/*!
* \class XTP::API::TraderSpi
*
* \brief 交易接口响应类
*
* \author 中泰证券股份有限公司
* \date 十月 2015
*/
namespace XTP {
	namespace API {

		class TraderSpi
		{
		public:

			///当客户端与交易后台通信连接断开时，该方法被调用。
			///@remark 保留函数，暂未支持
			///@param reason 错误原因
			virtual void OnDisconnected(int reason) {};

			///错误应答
			///@param error_info 具体的错误代码和错误信息
			virtual void OnError(XTPRI *error_info) {};

			///报单通知
			///@param order_info 订单响应具体信息
			///@param error_info 订单被拒绝或者发生错误时错误代码和错误信息
			///@remark 每次订单状态更新时，都会被调用
			virtual void OnOrderEvent(XTPOrderInfo *order_info, XTPRI *error_info) {};

			///成交通知
			///@param trade_info 成交回报的具体信息
			///@remark 订单有成交发生的时候，会被调用
			virtual void OnTradeEvent(XTPTradeReport *trade_info) {};

			///撤单出错响应
			///@param cancel_info 撤单具体信息，包括撤单单和待撤单的order_xtp_id
			///@param error_info 撤单被拒绝或者发生错误时错误代码和错误信息
			virtual void OnCancelOrderError(XTPOrderCancelInfo *cancel_info, XTPRI *error_info) {};

			///请求查询报单响应
			///@param order_info 查询到的报单
			///@param error_info 错误信息
			///@param request_id 此消息响应函数对应的请求ID
			///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应
			///@remark 由于支持分时段查询，一个查询请求可能对应多个响应
			virtual void OnQueryOrder(XTPQueryOrderRsp *order_info, XTPRI *error_info, int request_id, bool is_last) {};

			///请求查询成交响应
			///@param trade_info 查询到的成交回报
			///@param error_info 错误信息
			///@param request_id 此消息响应函数对应的请求ID
			///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应
			///@remark 由于支持分时段查询，一个查询请求可能对应多个响应
			virtual void OnQueryTrade(XTPQueryTradeRsp *trade_info, XTPRI *error_info, int request_id, bool is_last) {};

			///请求查询投资者持仓响应
			///@param position 查询到的持仓情况
			///@param error_info 错误信息
			///@param request_id 此消息响应函数对应的请求ID
			///@param is_last 此消息响应函数是否为request_id这条请求所对应的最后一个响应
			///@remark 由于用户可能持有多个股票，一个查询请求可能对应多个响应
			virtual void OnQueryPosition(XTPQueryStkPositionRsp *position, XTPRI *error_info, int request_id, bool is_last) {};

			///请求查询资金账户响应
			virtual void OnQueryAsset(XTPQueryAssetRsp *asset, XTPRI *error_info, int request_id, bool is_last) {};


		};
	}
}


/*!
* \class XTP::API::TraderApi
*
* \brief 交易接口类
*
* \author 中泰证券股份有限公司
* \date 十月 2015
*/
namespace XTP {
	namespace API {

		class TRADER_API_EXPORT TraderApi
		{
		public:
			///创建TraderApi
			///@param save_file_path （保留字段）存贮订阅信息文件的目录，默认为当前目录
			///@return 创建出的UserApi
			static TraderApi *CreateTraderApi(const char *save_file_path = "");

			///删除接口对象本身
			///@remark 不再使用本接口对象时,调用该函数删除接口对象
			virtual void Release() = 0;

			///获取当前交易日
			///@return 获取到的交易日
			///@remark 只有登录成功后,才能得到正确的交易日
			virtual const char *GetTradingDay() = 0;

			///注册回调接口
			///@param spi 派生自回调接口类的实例
			virtual void RegisterSpi(TraderSpi *spi) = 0;

			///用户登录请求
			///@return 登录是否成功，“0”表示登录成功，“-1”表示连接服务器出错，“-2”表示已存在连接，不允许重复登录，如果需要重连，请先logout
			///@param ip 服务器地址
			///@param port 服务器端口号
			///@param user 登录用户名
			///@param password 登录密码
			///@param sock_type “1”代表TCP，“2”代表UDP，目前暂时只支持TCP
			///@param client_id （保留字段）客户端id，用于区分同一用户的不同连接
			///@remark 此函数为同步阻塞式，不需要异步等待登录成功，当函数返回即可进行后续操作
			virtual int Login(const char* ip, int port, const char* user, const char* password, XTP_PROTOCOL_TYPE sock_type, int client_id = 0) = 0;


			///登出请求
			///@return 登出是否成功，“0”表示登出成功，“-1”表示登出失败
			virtual int Logout() = 0;

			///报单录入请求
			///@return 报单在XTP系统中的ID,如果为‘0’表示报单失败，用户需要记录下返回的order_xtp_id
			///@param order 报单录入信息
			virtual uint64_t InsertOrder(XTPOrderInsertInfo *order) = 0;

			///报单操作请求
			///@return 撤单单在XTP系统中的ID,如果为‘0’表示撤单失败，用户需要记录下返回的order_cancel_xtp_id
			///@param order_xtp_id 需要撤销的委托单在XTP系统中的ID
			virtual uint64_t CancelOrder(const uint64_t order_xtp_id) = 0;

			///根据报单ID请求查询报单
			///@return 查询是否成功，“0”表示成功，非“0”表示出错
			///@param order_xtp_id 需要查询的报单在xtp系统中的ID
			///@param request_id 用于用户定位查询响应的ID，由用户自定义
			virtual int QueryOrderByXTPID(const uint64_t order_xtp_id, int request_id) = 0;

			///请求查询报单
			///@return 查询是否成功，“0”表示成功，非“0”表示出错
			///@param query_param 需要查询的订单相关筛选条件
			///@param request_id 用于用户定位查询响应的ID，由用户自定义
			///@remark 该方法支持分时段查询，如果股票代码为空，则默认查询时间段内的所有报单，否则查询时间段内所有跟股票代码相关的报单
			virtual int QueryOrders(const XTPQueryOrderReq *query_param, int request_id) = 0;

			///根据委托编号请求查询相关成交
			///@return 查询是否成功，“0”表示成功，非“0”表示出错
			///@param order_xtp_id 需要查询的委托编号
			///@param request_id 用于用户定位查询响应的ID，由用户自定义
			///@remark 此函数查询出的结果可能对应多个响应
			virtual int QueryTradesByXTPID(const uint64_t order_xtp_id, int request_id) = 0;

			///请求查询已成交
			///@return 查询是否成功，“0”表示成功，非“0”表示出错
			///@param query_param 需要查询的成交回报筛选条件
			///@param request_id 用于用户定位查询响应的ID，由用户自定义
			///@remark 该方法支持分时段查询，如果股票代码为空，则默认查询时间段内的所有成交回报，否则查询时间段内所有跟股票代码相关的成交回报
			virtual int QueryTrades(XTPQueryTraderReq *query_param, int request_id) = 0;

			///请求查询投资者持仓
			///@return 查询是否成功，“0”表示成功，非“0”表示出错
			///@param ticker 需要查询的持仓股票，可以为空
			///@param request_id 用于用户定位查询响应的ID，由用户自定义
			///@remark 该方法如果用户提供了股票代码，则会查询此股票的持仓信息，如果股票代码为空，则默认查询所有持仓信息
			virtual int QueryPosition(const char *ticker, int request_id) = 0;

			///请求查询资产
			///@return 查询是否成功，“0”表示成功，非“0”表示出错
			///@param request_id 用于用户定位查询响应的ID，由用户自定义
			virtual int QueryAsset(int request_id) = 0;

		protected:
			~TraderApi() {};
		};

			}
}




#endif
