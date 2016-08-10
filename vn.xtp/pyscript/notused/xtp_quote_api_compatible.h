/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file xtp_quote_api_compatible.h
///@brief 定义行情订阅客户端兼容接口
/////////////////////////////////////////////////////////////////////////

#ifndef _XTP_QUOTE_API_COMPATIBLE_H_
#define _XTP_QUOTE_API_COMPATIBLE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xtp_api_struct.h"
#include "xtp_api_struct_compatible.h"

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
 * \class XTP::API::QuoteCompatibleSpi
 *
 * \brief 行情回调兼容类
 *
 * \author 中泰证券股份有限公司
 * \date 十月 2015
 */
namespace XTP {
	namespace API {
		class QuoteCompatibleSpi
		{
		public:
			///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
			///@param nReason 错误原因
			///        0x1001 网络读失败
			///        0x1002 网络写失败
			///        0x2001 接收心跳超时
			///        0x2002 发送心跳失败
			///        0x2003 收到错误报文
			virtual void OnFrontDisconnected(int nReason) {};


			///错误应答
			///@param pRspInfo 错误信息
			///@param nRequestID 请求的ID
			///@param bIsLast 是否最后一个
			virtual void OnRspError(CXTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

			///登出请求响应
			///@param pUserLogout 用户登出的参数
			///@param pRspInfo 错误信息
			///@param nRequestID 请求的ID
			///@param bIsLast 是否最后一个
			virtual void OnRspUserLogout(CXTPUserLogoutField *pUserLogout, CXTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

			///订阅行情应答
			///@param pSpecificInstrument 详细的合约订阅情况
			///@param pRspInfo 错误信息
			///@param nRequestID 请求的ID
			///@param bIsLast 是否最后一个
			virtual void OnRspSubMarketData(CXTPSpecificInstrumentField *pSpecificInstrument, CXTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

			///取消订阅行情应答
			///@param pSpecificInstrument 详细的合约取消订阅情况
			///@param pRspInfo 错误信息
			///@param nRequestID 请求的ID
			///@param bIsLast 是否最后一个
			virtual void OnRspUnSubMarketData(CXTPSpecificInstrumentField *pSpecificInstrument, CXTPRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

			///深度行情通知
			///@param pDepthMarketData 行情数据
			virtual void OnRtnDepthMarketData(CXTPDepthMarketDataField *pDepthMarketData) {};
		};
	}
}


/*!
* \class XTP::API::QuoteCompatibleApi
*
* \brief 行情订阅兼容接口类
*
* \author 中泰证券股份有限公司
* \date 十月 2015
*/
namespace XTP {
	namespace API {
		class MD_API_EXPORT QuoteCompatibleApi
		{
		public:
			///创建QuoteApi
			///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
			///@return 创建出的UserApi
			///modify for udp marketdata
			static QuoteCompatibleApi *CreateQuoteApi(const char *pszFlowPath = "");

			///删除接口对象本身
			///@remark 不再使用本接口对象时,调用该函数删除接口对象
			virtual void Release() = 0;

			 	
			///等待接口线程结束运行
			///@return 线程退出代码
			virtual int Join() = 0;

			///获取当前交易日
			///@return 获取到的交易日
			///@remark 只有登录成功后,才能得到正确的交易日
			virtual const char *GetTradingDay() = 0;

			///注册前置机网络地址
			///@param pszFrontAddress 前置机网络地址。
			///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
			///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
			virtual void RegisterFront(char *pszFrontAddress) = 0;

			///注册回调接口
			///@param pSpi 派生自回调接口类的实例
			virtual void RegisterSpi(QuoteCompatibleSpi *pSpi) = 0;

			///订阅行情。
			///@param ppInstrumentID 合约ID  
			///@param nCount 要订阅/退订行情的合约个数
			///@param pExchageID 交易所代码
			///@remark 可以一次性订阅同一证券交易所的多个合约
			virtual int SubscribeMarketData(char *ppInstrumentID[], int nCount, XTP_EXCHANGE_TYPE pExchageID) = 0;

			///退订行情。
			///@param ppInstrumentID 合约ID  
			///@param nCount 要订阅/退订行情的合约个数
			///@param pExchageID 交易所代码
			///@remark 可以一次性取消订阅同一证券交易所的多个合约
			virtual int UnSubscribeMarketData(char *ppInstrumentID[], int nCount, XTP_EXCHANGE_TYPE pExchageID) = 0;

			///用户登录请求
			///@return 登录是否成功，“0”表示登录成功，非“0”表示登录出错
			///@remark 此函数为同步阻塞式，不需要异步等待登录成功，当函数返回即可进行后续操作
			virtual int ReqUserLogin(CXTPReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;


			///登出请求
			///@return 登出是否成功，“0”表示登出成功，非“0”表示登出出错
			virtual int ReqUserLogout(CXTPUserLogoutField *pUserLogout, int nRequestID) = 0;

		protected:
			~QuoteCompatibleApi() {};
		};
	}
}




#endif
