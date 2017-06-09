 /**
 * 版权所有(C)2012-2016, 大连飞创信息技术有限公司
 * 文件名称：DFITCTraderApi.h
 * 文件说明：定义XSpeed交易接口
 * 当前版本：1.0.14.91
 * 作者：XSpeed项目组
 * 发布日期：2015年5月6日
 */

#ifndef DFITCTRADERAPI_H_
#define DFITCTRADERAPI_H_

#include "DFITCApiStruct.h"


#ifdef WIN32
     #ifdef DFITCAPI_EXPORTS
          #define DFITCTRADERAPI_API __declspec(dllexport)
     #else
          #define DFITCTRADERAPI_API __declspec(dllimport)
     #endif//DFITCAPI_EXPORTS
#else
     #define DFITCTRADERAPI_API
#endif//WIN32

namespace DFITCXSPEEDAPI
{
     class DFITCTraderSpi
     {
     public:

         /* 网络连接正常响应:当客户端与交易后台需建立起通信连接时（还未登录前），客户端API会自动检测与前置机之间的连接，
          * 当网络可用，将自动建立连接，并调用该方法通知客户端， 客户端可以在实现该方法时，重新使用资金账号进行登录。
          *（该方法是在Api和前置机建立连接后被调用，该调用仅仅是说明tcp连接已经建立成功。用户需要自行登录才能进行后续的业务操作。
          *  登录失败则此方法不会被调用。）
          */
         virtual void OnFrontConnected(){};

         /**
          * 网络连接不正常响应：当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
          * @param  nReason:错误原因。
          *        0x1001 网络读失败
          *        0x1002 网络写失败
          *        0x2001 接收心跳超时
          *        0x2002 发送心跳失败 
          *        0x2003 收到错误报文  
          */
         virtual void OnFrontDisconnected(int nReason){};
         /**
          * 登陆请求响应:当用户发出登录请求后，前置机返回响应时此方法会被调用，通知用户登录是否成功。
          * @param pUserLoginInfoRtn:用户登录信息结构地址。
          * @param pErrorInfo:若登录失败，返回错误信息地址，该结构含有错误信息。
          */
         virtual void OnRspUserLogin(struct DFITCUserLoginInfoRtnField * pUserLoginInfoRtn, struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * 登出请求响应:当用户发出退出请求后，前置机返回响应此方法会被调用，通知用户退出状态。
          * @param pUserLogoutInfoRtn:返回用户退出信息结构地址。
          * @param pErrorInfo:若登出失败，返回错误信息地址，该结构含有错误信息。
          */
         virtual void OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pUserLogoutInfoRtn, struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * 期货委托报单响应:当用户录入报单后，前置返回响应时该方法会被调用。
          * @param pOrderRtn:返回用户下单信息结构地址。
          * @param pErrorInfo:若报单失败，返回错误信息地址，该结构含有错误信息。
          */
         virtual void OnRspInsertOrder(struct DFITCOrderRspDataRtnField * pOrderRtn, struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * 期货委托撤单响应:当用户撤单后，前置返回响应是该方法会被调用。
          * @param pOrderCanceledRtn:返回撤单响应信息结构地址。
          * @param pErrorInfo:若撤单失败，返回错误信息地址，该结构含有错误信息。
          */
         virtual void OnRspCancelOrder(struct DFITCOrderRspDataRtnField * pOrderCanceledRtn, struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * 错误回报
          * @param pErrorInfo:错误信息的结构地址。
          */
         virtual void OnRtnErrorMsg(struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * 成交回报:当委托成功交易后次方法会被调用。
          * @param pRtnMatchData:指向成交回报的结构的指针。
          */
         virtual void OnRtnMatchedInfo(struct DFITCMatchRtnField * pRtnMatchData){};

         /**
          * 委托回报:下单委托成功后，此方法会被调用。
          * @param pRtnOrderData:指向委托回报地址的指针。
          */
         virtual void OnRtnOrder(struct DFITCOrderRtnField * pRtnOrderData){};

         /**
          * 撤单回报:当撤单成功后该方法会被调用。
          * @param pCancelOrderData:指向撤单回报结构的地址，该结构体包含被撤单合约的相关信息。
          */
         virtual void OnRtnCancelOrder(struct DFITCOrderCanceledRtnField * pCancelOrderData){};

         /**
          * 查询当日委托响应:当用户发出委托查询后，该方法会被调用。
          * @param pRtnOrderData:指向委托回报结构的地址。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
          * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspQryOrderInfo(struct DFITCOrderCommRtnField * pRtnOrderData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * 查询当日成交响应:当用户发出成交查询后该方法会被调用。
          * @param pRtnMatchData:指向成交回报结构的地址。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
          * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspQryMatchInfo(struct DFITCMatchedRtnField * pRtnMatchData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * 持仓查询响应:当用户发出持仓查询指令后，前置返回响应时该方法会被调用。
          * @param pPositionInfoRtn:返回持仓信息结构的地址。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
          * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspQryPosition(struct DFITCPositionInfoRtnField * pPositionInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * 客户资金查询响应:当用户发出资金查询指令后，前置返回响应时该方法会被调用。
          * @param pCapitalInfoRtn:返回资金信息结构的地址。
          * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
		  * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspCustomerCapital(struct DFITCCapitalInfoRtnField * pCapitalInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * 交易所合约查询响应:当用户发出合约查询指令后，前置返回响应时该方法会被调用。
          * @param pInstrumentData:返回合约信息结构的地址。
          * @param pErrorInfo:错误信息结构，如果查询发生错误，则返回错误信息。
          * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspQryExchangeInstrument(struct DFITCExchangeInstrumentRtnField * pInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * 套利合约查询响应:当用户发出套利合约查询指令后，前置返回响应时该方法会被调用。
          * @param pAbiInstrumentData:返回套利合约信息结构的地址。
          * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
          * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspArbitrageInstrument(struct DFITCAbiInstrumentRtnField * pAbiInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * 查询指定合约响应:当用户发出指定合约查询指令后，前置返回响应时该方法会被调用。
          * @param pInstrument:返回指定合约信息结构的地址。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
		  * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspQrySpecifyInstrument(struct DFITCInstrumentRtnField * pInstrument, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * 查询持仓明细响应:当用户发出查询持仓明细后，前置返回响应时该方法会被调用。
          * @param pPositionDetailRtn:返回持仓明细结构的地址。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
		  * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspQryPositionDetail(struct DFITCPositionDetailRtnField * pPositionDetailRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * 交易通知响应:用于接收XSPEED柜台手动发送通知，即支持指定客户，也支持系统广播。
          * @param pTradingNoticeInfo: 返回用户事件通知结构的地址。
          */
         virtual void OnRtnTradingNotice(struct DFITCTradingNoticeInfoField * pTradingNoticeInfo){};

         /**
          * 密码修改响应:用于修改资金账户登录密码。
          * @param pResetPassword: 返回密码修改结构的地址。
		  * @param pErrorInfo:若修改密码失败，返回错误信息地址，该结构含有错误信息。
          */ 
         virtual void OnRspResetPassword(struct DFITCResetPwdRspField * pResetPassword, struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * 交易编码查询响应:返回交易编码信息
          * @param pTradeCode: 返回交易编码查询结构的地址。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
		  * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
          virtual void OnRspQryTradeCode(struct DFITCQryTradeCodeRtnField * pTradeCode, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * 账单确认响应:用于接收客户账单确认状态。
          * @param pBillConfirm: 返回账单确认结构的地址。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
          */
         virtual void OnRspBillConfirm(struct DFITCBillConfirmRspField * pBillConfirm, struct DFITCErrorRtnField * pErrorInfo){};
 
         /**
          * 查询客户权益计算方式响应:返回客户权益计算的方式
          * @param pEquityComputMode: 返回客户权益计算方式结构的地址。
          */
          virtual void OnRspEquityComputMode(struct DFITCEquityComputModeRtnField * pEquityComputMode){};

         /**
          * 客户结算账单查询响应:返回账单信息
          * @param pQryBill: 返回客户结算账单查询结构的地址。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
          * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspQryBill(struct DFITCQryBillRtnField *pQryBill, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * 厂商ID确认响应:用于接收厂商信息。
          * @param pProductRtnData: 返回厂商ID确认响应结构的地址。
          */
         virtual void OnRspConfirmProductInfo(struct DFITCProductRtnField * pProductRtnData){};


         /**
          * 交易日确认响应:用于接收交易日信息。
          * @param DFITCTradingDayRtnField: 返回交易日请求确认响应结构的地址。
          */
         virtual void OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData){};

         /**
          * 做市商报单响应
          * @param pRspQuoteData:指向做市商报单响应地址的指针。
		  * @param pErrorInfo:若报价失败，返回错误信息地址，该结构含有错误信息。
          */
         virtual void OnRspQuoteInsert(struct DFITCQuoteRspField * pRspQuoteData, struct DFITCErrorRtnField * pErrorInfo) {};

         /**
          * 做市商报单回报
          * @param pRtnQuoteData:指向做市商报单回报地址的指针。
          */
         virtual void OnRtnQuoteInsert(struct DFITCQuoteRtnField * pRtnQuoteData){};

         /**
          * 做市商撤单响应
          * @param pRspQuoteCanceledData:指向做市商撤单响应地址的指针。
		  * @param pErrorInfo:若撤单失败，返回错误信息地址，该结构含有错误信息。
          */
         virtual void OnRspQuoteCancel( struct DFITCQuoteRspField * pRspQuoteCanceledData,struct DFITCErrorRtnField * pErrorInfo)  {};

         /**
          * 做市商撤单回报
          * @param pRtnQuoteCanceledData:指向做市商撤单回报地址的指针。
          */
         virtual void OnRtnQuoteCancel(struct DFITCQuoteCanceledRtnField * pRtnQuoteCanceledData) {};   

		 /**
          * 做市商成交回报
          * @param pRtnQuoteMatchedData:指向做市商成交回报地址的指针。
          */
         virtual void OnRtnQuoteMatchedInfo(struct DFITCQuoteMatchRtnField * pRtnQuoteMatchedData) {};

		 /**
          * 批量撤单响应
          * @param pRspStripCancelOrderData:指向批量撤单响应地址的指针。
		  * @param pErrorInfo:若批量撤单失败，返回错误信息地址，该结构含有错误信息。
          */
         virtual void OnRspCancelAllOrder(struct DFITCCancelAllOrderRspField *pRspCancelAllOrderData,struct DFITCErrorRtnField * pErrorInfo){};

		 /**
          * 询价通知查询响应
          * @param pRtnQryQuoteNoticeData:查询询价通知回报结构地址。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
          * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspQryQuoteNotice(struct DFITCQryQuoteNoticeRtnField * pRtnQryQuoteNoticeData,struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};
		 
         /**
          * 询价响应
          * @param pRspForQuoteData:询价请求响应结构地址。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
          */
         virtual void OnRspForQuote(struct DFITCForQuoteRspField * pRspForQuoteData,struct DFITCErrorRtnField * pErrorInfo){};

         /**
          * 询价回报
          * @param pRtnForQuoteData:询价回报结构地址。
          */
         virtual void OnRtnForQuote(struct DFITCForQuoteRtnField * pRtnForQuoteData){};

         /**
          * 查询当日报价委托响应
          * @param pRtnQuoteOrderData:指向报价查询回报结构的地址。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
          * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspQryQuoteOrderInfo(struct DFITCQuoteOrderRtnField * pRtnQuoteOrderData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * 询价委托查询响应
          * @param pRtnQryForQuoteData:指向询价委托查询响应地址的指针。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
          * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspQryForQuote(struct DFITCQryForQuoteRtnField * pRtnQryForQuoteData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

         /**
          * 查询转帐银行响应
          * @param pTransferBank:指向查询转帐银行回报地址的指针。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
          * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspQryTransferBank(struct DFITCTransferBankRspField * pTransferBank, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast) {};
		 
         /**
          * 查询转帐流水响应
          * @param pTransferSerial:指向查询转帐流水回报地址的指针。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
          * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspQryTransferSerial(struct DFITCTransferSerialRspField * pTransferSerial, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast) {};
		 
         /**
          * 期货发起银行资金转期货应答
          * @param pRspTransfer:指向期货发起银行资金转期货应答地址的指针。
		  * @param pErrorInfo:若转账失败，返回错误信息地址，该结构含有错误信息。
          */
         virtual void OnRspFromBankToFutureByFuture(struct DFITCTransferRspField * pRspTransfer, struct DFITCErrorRtnField * pErrorInfo) {};
		 
         /**
          * 期货发起期货资金转银行应答
          * @param pRspTransfer:指向期货发起期货资金转银行应答地址的指针。
		  * @param pErrorInfo:若转账失败，返回错误信息地址，该结构含有错误信息。
          */
         virtual void OnRspFromFutureToBankByFuture(struct DFITCTransferRspField * pRspTransfer, struct DFITCErrorRtnField * pErrorInfo) {};

         /**
          * 期货发起银行资金转期货通知
          * @param pRtnTransfer:指向期货发起银行资金转期货通知地址的指针。
		  * @param pErrorInfo:若转账失败，返回错误信息地址，该结构含有错误信息。
          */
         virtual void OnRtnFromBankToFutureByFuture(DFITCTransferRtnField * pRtnTransfer, struct DFITCErrorRtnField * pErrorInfo) {};
		 
         /**
          * 期货发起期货资金转银行通知
          * @param pRtnTransfer:指向期货发起期货资金转银行通知地址的指针。
		  * @param pErrorInfo:若转账失败，返回错误信息地址，该结构含有错误信息。
          */
         virtual void OnRtnFromFutureToBankByFuture(DFITCTransferRtnField * pRtnTransfer, struct DFITCErrorRtnField * pErrorInfo) {};

         /**
          * 银行发起冲正期货转银行通知
          * @param pRspRepeal:指向期货发起期货资金转银行冲正通知地址的指针。
          */
         virtual void OnRtnRepealFromFutureToBankByBank(DFITCRepealRtnField * pRspRepeal) {};

         /**
          * 交易所状态查询响应
          * @param pRspExchangeStatusData:指向交易所状态查询响应地址的指针。
          */
         virtual void OnRspQryExchangeStatus(struct DFITCExchangeStatusRspField * pRspExchangeStatusData){};

         /**
          * 交易所状态通知
          * @param pRtnExchangeStatusData:指向交易所状态通知地址的指针。
          */
         virtual void OnRtnExchangeStatus(struct DFITCExchangeStatusRtnField * pRtnExchangeStatusData){};
		
         /**
          * 行情查询响应
          * @param pDepthMarketData:指向行情查询响应地址的指针。
		  * @param pErrorInfo:若查询失败，返回错误信息地址，该结构含有错误信息。
          * @param bIsLast:表明是否是最后一条响应信息（0 -否   1 -是）。
          */
         virtual void OnRspQryDepthMarketData(struct DFITCDepthMarketDataField * pDepthMarketData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast){};

	};//end of DFITCTraderSpi

     class DFITCTRADERAPI_API DFITCTraderApi
     {
     public:
         DFITCTraderApi();
         virtual ~DFITCTraderApi();
     public:
         /**
          * 静态函数，产生一个api实例
          * @return 创建出的UserApi
          */
         static DFITCTraderApi * CreateDFITCTraderApi(void);

         /**
          * 删除接口对象本身，不再使用本接口对象时,调用该函数删除接口对象。
          */
         virtual void Release(void) = 0;

         /**
          * 和服务器建立socket连接，并启动一个接收线程， 同时该方法注册一个回调函数集
          * @param pszFrontAddr:交易前置网络地址。
          *                     网络地址的格式为:"protocol://ipaddress:port",如"tcp://172.21.200.103:10910"
          *                     其中protocol的值为tcp格式。
          *                     ipaddress表示交易前置的IP,port表示交易前置的端口     
          * @param *pSpi:类DFITCMdSpi对象实例
          * @return 0 - 初始化成功; -1 - 初始化失败。
          */
         virtual int Init(char * pszFrontAddr, DFITCTraderSpi * pSpi) = 0;

         /**
          * 等待接口线程结束运行。
          * @return 线程退出代码。
          */
         virtual int Join(void) = 0;

         /**
          * 用户发出登录请求
          * @param pUserLoginData:指向用户登录请求结构的地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */ 
         virtual int ReqUserLogin(struct DFITCUserLoginField * pUserLoginData) = 0;

         /**
          * 用户发出登出请求
          * @param pUserLogoutData:指向用户登录请出结构的地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */ 
         virtual int ReqUserLogout(struct DFITCUserLogoutField * pUserLogoutData) = 0;

         /**
          * 期货委托报单请求。
          * @param pInsertOrderData:用户请求报单信息结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqInsertOrder(struct DFITCInsertOrderField * pInsertOrderData) = 0;

         /**
          * 期货撤单请求。
          * @param pCancelOrderData:用户请求撤单信息结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          * (如果提供柜台委托号(柜台委托号大于-1)，则只使用柜台委托号处理；只有当柜台委托号小于0时，才使用本地委托号进行撤单)
          */
         virtual int ReqCancelOrder(struct DFITCCancelOrderField * pCancelOrderData) = 0;

         /**
          * 持仓查询请求。
		  * @param pPositionData:用户请求持仓信息结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
		  *（如果没有提供合约代码，则查询全部持仓信息。）
          */
         virtual int ReqQryPosition(struct DFITCPositionField * pPositionData) = 0;

         /**
          * 客户资金查询请求。
          * @param pCapitalData:请求资金查询结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。(用户需要填充该结构的各个字段。)
          */
         virtual int ReqQryCustomerCapital(struct DFITCCapitalField * pCapitalData) = 0;

         /**
          * 查询交易所合约列表（非套利）。
          * @param pExchangeInstrumentData:交易所合约查询结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryExchangeInstrument(struct DFITCExchangeInstrumentField * pExchangeInstrumentData) = 0;

         /**
          * 查询交易所套利合约列表。
          * @param pAbtriInstrumentData:交易所套利合约查询结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryArbitrageInstrument(struct DFITCAbiInstrumentField * pAbtriInstrumentData) = 0;

         /**
          * 当日委托查询请求。
          * @param pOrderData:当日委托查询结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryOrderInfo(struct DFITCOrderField * pOrderData) = 0;

         /**
          * 当日成交查询请求。
          * @param pMatchData:当日成交查询结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryMatchInfo(struct DFITCMatchField * pMatchData) = 0;

         /**
          * 指定合约信息查询请求。
          * @param pInstrument:指定合约查询结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQrySpecifyInstrument(struct DFITCSpecificInstrumentField * pInstrument) = 0;

         /**
          * 持仓明细查询请求。
          * @param pPositionDetailData:持仓明细查询结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryPositionDetail(struct DFITCPositionDetailField * pPositionDetailData) = 0;

         /**
          * 厂商ID确认请求。
		  * @param pConfirmProductData:厂商ID确认结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败 -其它 -检测异常。
          */
         virtual int ReqConfirmProductInfo(struct DFITCProductField * pConfirmProductData) = 0;

         /**
          * 密码修改请求
          * @param pResetPasswordData:密码修改结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqResetPassword (struct DFITCResetPwdField * pResetPasswordData) =0;

         /**
          * 账单确认请求。
          * @param pBillConfirmData:账单确认结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqBillConfirm(struct DFITCBillConfirmField * pBillConfirmData) = 0;

         /**
          * 交易编码查询请求。
          * @param pTradeCodeData:交易编码查询请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryTradeCode(struct DFITCQryTradeCodeField * pTradeCodeData) = 0;

         /**
          * 查询客户权益计算方式请求。
          * @return 0 - 请求发送成功; -1 - 请求发送失败 -其它 -检测异常。
          */
         virtual int ReqEquityComputMode() = 0;

         /**
          * 客户账单结算查询请求。
          * @param pQryBillData:客户账单结算请求结构地址。 
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryBill(struct DFITCQryBillField * pQryBillData) = 0;

         /**
          * 交易日查询请求
          * @param pTradingDay:交易日查询请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败 -其它 -检测异常。
          */
         virtual int ReqTradingDay(struct DFITCTradingDayField * pTradingDay) = 0;

		 /**
          * 询价通知查询请求
          * @param pQryQuoteNoticeData:查询询价通知请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryQuoteNotice(struct DFITCQryQuoteNoticeField * pQryQuoteNoticeData) = 0;

         /**
          * 做市商报单请求
          * @param pQuoteInsertOrderData:做市商报单请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQuoteInsert(struct DFITCQuoteInsertField * pQuoteInsertOrderData)  = 0;

         /**
          * 做市商撤单请求
          * @param pQuoteCancelOrderData:做市商撤单请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQuoteCancel(struct DFITCCancelOrderField * pQuoteCancelOrderData) = 0;  
		 
         /**
          * 批量撤单
          * @param pCancelAllOrderData:批量撤单请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqCancelAllOrder(struct DFITCCancelAllOrderField * pCancelAllOrderData) = 0;

         /**
          * 询价请求
          * @param pForQuoteData:询价请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqForQuote(struct DFITCForQuoteField * pForQuoteData) =0;

         /**
          * 询价委托查询请求
          * @param pQryForQuoteData:询价委托查询请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryForQuote(struct DFITCQryForQuoteField * pQryForQuoteData) =0;

         /**
          * 做市商报价委托查询
          * @param pQuoteOrderData:做市商报价委托查询结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryQuoteOrderInfo(struct DFITCQuoteOrderField * pQuoteOrderData) =0;

         /**
          * 查询转账银行
          * @param pQryTransferBank:查询转账银行请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryTransferBank(struct DFITCQryTransferBankField * pQryTransferBank) = 0;

         /**
          * 查询转帐流水
          * @param pQryTransferSerial:查询转帐流水请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryTransferSerial(struct DFITCQryTransferSerialField * pQryTransferSerial) = 0;

         /**
          * 期货发起银行资金转期货
          * @param pReqTransfer:银行资金转期货请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqFromBankToFutureByFuture(struct DFITCReqTransferField * pReqTransfer) = 0;

         /**
          * 期货发起期货资金转银行
          * @param pReqTransfer:期货资金转银行请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqFromFutureToBankByFuture(struct DFITCReqTransferField * pReqTransfer) = 0;

         /**
          * 交易所状态查询
          * @param pQryExchangeStatusData:交易所状态查询请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryExchangeStatus(struct DFITCQryExchangeStatusField *pQryExchangeStatusData) = 0;

         /**
          * 行情查询请求
          * @param pQryDepthMarketData:行情查询请求结构地址。
          * @return 0 - 请求发送成功 -1 - 请求发送失败  -其它 -检测异常。
          */
         virtual int ReqQryDepthMarketData(struct DFITCQryDepthMarketDataField *pQryDepthMarketData) = 0;
     };//end of DFITCTraderSpi
}
//end of namespace


#endif//DFITCTRADERAPI_H_

