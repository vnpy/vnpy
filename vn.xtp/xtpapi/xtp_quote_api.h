/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file xtp_quote_api.h
///@brief 定义行情订阅客户端接口
/////////////////////////////////////////////////////////////////////////

#ifndef _XTP_QUOTE_API_H_
#define _XTP_QUOTE_API_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xtp_api_struct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MD_API_EXPORT
#define MD_API_EXPORT __declspec(dllexport)
#else
#define MD_API_EXPORT __declspec(dllimport)
#endif
#else
#define MD_API_EXPORT 
#endif

/*!
* \class XTP::API::QuoteSpi
*
* \brief 行情回调类
*
* \author 中泰证券股份有限公司
* \date 十月 2015
*/
namespace XTP {
	namespace API {
		class QuoteSpi
		{
		public:

			///当客户端与交易后台通信连接断开时，该方法被调用。
			///@remark 保留函数，暂未支持
			///@param reason 错误原因
			virtual void OnDisconnected(int reason) {};


			///错误应答
			///@param error_info 错误信息
			virtual void OnError(XTPRI *error_info) {};

			///订阅行情应答
			///@param ticker 详细的合约订阅情况
			///@param error_info 订阅合约发生错误时的错误信息
			///@param is_last 是否此次订阅的最后一个应答
			///@remark 每条订阅的合约均对应一条订阅应答
			virtual void OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) {};

			///取消订阅行情应答
			///@param ticker 详细的合约取消订阅情况
			///@param error_info 错误信息
			///@param is_last 是否此次取消订阅的最后一个应答
			///@remark 每条取消订阅的合约均对应一条取消订阅应答
			virtual void OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) {};

			///行情通知
			///@param market_data 行情数据
			virtual void OnMarketData(XTPMD *market_data) {};


			///查询可交易合约应答
			///@remark 保留函数，此函数暂未支持
			virtual void OnQueryAllTickers() {};
		};
	}
}


/*!
* \class XTP::API::QuoteApi
*
* \brief 行情订阅接口类
*
* \author 中泰证券股份有限公司
* \date 十月 2015
*/
namespace XTP {
	namespace API {
		class MD_API_EXPORT QuoteApi
		{
		public:
			///创建QuoteApi
			///@param save_file_path （保留字段）存贮订阅信息文件的目录，默认为当前目录
			///@return 创建出的UserApi
			static QuoteApi *CreateQuoteApi(const char *save_file_path = "");

			///删除接口对象本身
			///@remark 不再使用本接口对象时,调用该函数删除接口对象
			virtual void Release() = 0;


			///获取当前交易日
			///@return 获取到的交易日
			///@remark 只有登录成功后,才能得到正确的交易日
			virtual const char *GetTradingDay() = 0;


			///注册回调接口
			///@param spi 派生自回调接口类的实例
			virtual void RegisterSpi(QuoteSpi *spi) = 0;

			///订阅行情。
			///@return 订阅接口调用是否成功，“0”表示接口调用成功，非“0”表示接口调用出错
			///@param ticker 合约ID数组  
			///@param count 要订阅/退订行情的合约个数
			///@param exchage_id 交易所代码
			///@remark 可以一次性订阅同一证券交易所的多个合约
			virtual int SubscribeMarketData(char *ticker[], int count, XTP_EXCHANGE_TYPE exchage_id) = 0;

			///退订行情。
			///@return 取消订阅接口调用是否成功，“0”表示接口调用成功，非“0”表示接口调用出错
			///@param ticker 合约ID数组  
			///@param count 要订阅/退订行情的合约个数
			///@param exchage_id 交易所代码
			///@remark 可以一次性取消订阅同一证券交易所的多个合约
			virtual int UnSubscribeMarketData(char *ticker[], int count, XTP_EXCHANGE_TYPE exchage_id) = 0;

			///用户登录请求
			///@return 登录是否成功，“0”表示登录成功，“-1”表示连接服务器出错，“-2”表示已存在连接，不允许重复登录，如果需要重连，请先logout，“-3”表示输入有错误
			///@param ip 服务器地址
			///@param port 服务器端口号
			///@param user 登陆用户名
			///@param password 登陆密码
			///@param sock_type “1”代表TCP，“2”代表UDP，目前暂时只支持TCP
			///@remark 此函数为同步阻塞式，不需要异步等待登录成功，当函数返回即可进行后续操作
			virtual int Login(const char* ip, int port, const char* user, const char* password, XTP_PROTOCOL_TYPE sock_type) = 0;


			///登出请求
			///@return 登出是否成功，“0”表示登出成功，非“0”表示登出出错
			///@remark 此函数为同步阻塞式，不需要异步等待登出，当函数返回即可进行后续操作
			virtual int Logout() = 0;

			///获取当前交易日可交易合约
			///@return 查询是否成功，“0”表示查询成功，非“0”表示查询不成功
			///@param exchage_id 交易所代码
			///@remark 此函数暂未支持
			virtual int QueryAllTickers(XTP_EXCHANGE_TYPE exchage_id) = 0;


		protected:
			~QuoteApi() {};
		};
	}
}




#endif
