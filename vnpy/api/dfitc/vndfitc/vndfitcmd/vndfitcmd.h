#pragma once

#include "vndfitc.h"
#include "pybind11/pybind11.h"
#include "DFITCSECMdApi.h"

using namespace pybind11;
using namespace std;


//常量
#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONRTNNOTICE 2
#define ONRSPERROR 3
#define ONRSPSTOCKUSERLOGIN 4
#define ONRSPSTOCKUSERLOGOUT 5
#define ONRSPSOPUSERLOGIN 6
#define ONRSPSOPUSERLOGOUT 7
#define ONRSPFASLUSERLOGIN 8
#define ONRSPFASLUSERLOGOUT 9
#define ONRSPSTOCKSUBMARKETDATA 10
#define ONRSPSTOCKUNSUBMARKETDATA 11
#define ONRSPSOPSUBMARKETDATA 12
#define ONRSPSOPUNSUBMARKETDATA 13
#define ONSTOCKMARKETDATA 14
#define ONSOPMARKETDATA 15
#define ONRSPSTOCKAVAILABLEQUOT 16
#define ONRSPSOPAVAILABLEQUOT 17
#define ONRSPUSERMDPASSWORDUPDATE 18

///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现

class MdApi : public DFITCSECMdSpi
{
private:
	DFITCSECMdApi* api;				//API对象
	thread task_thread;					//工作线程指针（向python中推送数据）
	TaskQueue task_queue;			    //任务队列
	bool active = false;				//工作状态

public:
	MdApi()
	{
	};
	~MdApi()
	{
		if (this->active)
		{
			this->exit();
		}
	};


	//-------------------------------------------------------------------------------------
	//API回调函数
	//-------------------------------------------------------------------------------------

		/**
		 * 网络连接正常响应
		 */
	virtual void OnFrontConnected();

	/**
 * 网络连接不正常响应
 */
	virtual void OnFrontDisconnected(int nReason);

	/**
	 * SEC-消息通知
	 */
	virtual void OnRtnNotice(DFITCSECRspNoticeField *pNotice);

	/**
	 * ERR-错误应答
	 * @param pRspInfo:若请求失败，返回错误信息地址
	 */
	virtual void OnRspError(struct DFITCSECRspInfoField *pRspInfo);

	/**
	 * STOCK-登录响应
	 * @param pRspUserLogin:指针若非空,返回用户登录响应信息结构地址,表明登录请求成功
	 * @param pRspInfo::指针若非空，返回错误信息地址，表明登录请求失败
	 */
	virtual void OnRspStockUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo);

	/**
	 * STOCK-登出响应
	 * @param pRspUsrLogout:指针若非空,返回用户登出响应信息结构地址,表明登出请求成功
	 * @param pRspInfo:指针若非空，返回错误信息地址，表明登出请求失败
	 */
	virtual void OnRspStockUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo);

		/**
		 * SOP-登录响应
		 * @param pRspUserLogin:指针若非空,返回用户登录响应信息结构地址,表明登录请求成功
		 * @param pRspInfo:指针若非空，返回错误信息地址，表明登录请求失败
		 */
		virtual void OnRspSOPUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo);

	/**
	 * SOP-登出响应
	 * @param pRspUsrLogout:指针若非空,返回用户登出响应信息结构地址,表明登出请求成功
	 * @param pRspInfo:指针若非空，返回错误信息地址，表明登出请求失败
	 */
		virtual void OnRspSOPUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo);

	/**
	 * FASL-登录响应
	 * @param pRspUserLogin:指针若非空,返回用户登录响应信息结构地址,表明登录请求成功
	 * @param pRspInfo:指针若非空，返回错误信息地址，表明登录请求失败
	 */
		virtual void OnRspFASLUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo);

	/**
	 * FASL-登出响应
	 * @param pRspUsrLogout:指针若非空,返回用户登出响应信息结构地址,表明登出请求成功
	 * @param pRspInfo:指针若非空，返回错误信息地址，表明登出请求失败
	 */
		virtual void OnRspFASLUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo);

	/**
	 * STOCK-行情订阅响应
	 * @param pSpecificInstrument:指针若非空,返回用户指定合约行情订阅响应结构地址,表明指定合约行情订阅成功
	 * @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情订阅失败
	 */
		virtual void OnRspStockSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo);

	/**
	 * STOCK-取消订阅行情响应
	 * @param pSpecificInstrument:指针若非空,返回用户指定合约行情取消订阅响应结构地址,表明指定合约行情取消订阅成功
	 * @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情取消订阅失败
	 */
		virtual void OnRspStockUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo);

	/**
	 * SOP-行情订阅响应
	 * @param pSpecificInstrument:指针若非空,返回用户指定合约行情订阅响应结构地址,表明指定合约行情订阅成功
	 * @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情订阅失败
	 */
		virtual void OnRspSOPSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo);

	/**
	 * SOP-取消订阅行情响应
	 * @param pSpecificInstrument:指针若非空,返回用户指定合约行情取消订阅响应结构地址,表明指定合约行情取消订阅成功
	 * @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情取消订阅失败
	 */
		virtual void OnRspSOPUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo);

	/**
	 * STOCK-行情推送响应
	 * @param pMarketDataField:指针若非空,返回行情推送响应结构地址
	 */
		virtual void OnStockMarketData(struct DFITCStockDepthMarketDataField * pMarketDataField);

	/**
	 * SOP-行情推送响应
	 * @param pMarketDataField:指针若非空,返回行情推送响应结构地址
	 */
		virtual void OnSOPMarketData(struct DFITCSOPDepthMarketDataField * pMarketDataField);

	/**
	 * STOCK-可用行情响应
	 * @param pAvailableQuotInfo:指针若非空,返回可用的行情信息
	 * @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情取消订阅失败
	 * @param flag  为真是标示最后一条，为假时表示还有后续。
	 */
		virtual void OnRspStockAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo, bool flag);

	/**
	 * SOP-可用行情响应
	 * @param pAvailableQuotInfo:指针若非空,返回可用的行情信息
	 * @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情取消订阅失败
	 * @param flag  为真是标示最后一条，为假时表示还有后续。
	 */
		virtual void OnRspSopAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo, bool flag);

	/**
	 * 密码更新请求响应
	 * @param pMDPasswordUpdate:指针若非空,返回用户行情密码响应信息结构地址,表明密码修改成功。
	 * @param pRspInfo:指针若非空，返回错误信息地址，表明密码修改失败。
	 */
		virtual void OnRspUserMDPasswordUpdate(struct DFITCSECRspMDPasswordUpdateField *pMDPasswordUpdate, struct DFITCSECRspInfoField * pRspInfo);

	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task *task);

	void processFrontDisconnected(Task *task);

	void processRtnNotice(Task *task);

	void processRspError(Task *task);

	void processRspStockUserLogin(Task *task);

	void processRspStockUserLogout(Task *task);

	void processRspSOPUserLogin(Task *task);

	void processRspSOPUserLogout(Task *task);

	void processRspFASLUserLogin(Task *task);

	void processRspFASLUserLogout(Task *task);

	void processRspStockSubMarketData(Task *task);

	void processRspStockUnSubMarketData(Task *task);

	void processRspSOPSubMarketData(Task *task);

	void processRspSOPUnSubMarketData(Task *task);

	void processStockMarketData(Task *task);

	void processSOPMarketData(Task *task);

	void processRspStockAvailableQuot(Task *task);

	void processRspSopAvailableQuot(Task *task);

	void processRspUserMDPasswordUpdate(Task *task);

	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------

	virtual void onFrontConnected() {};

	virtual void onFrontDisconnected(int reqid) {};

	virtual void onRtnNotice(const dict &data) {};

	virtual void onRspError(const dict &data) {};

	virtual void onRspStockUserLogin(const dict &data, const dict &error) {};

	virtual void onRspStockUserLogout(const dict &data, const dict &error) {};

	virtual void onRspSOPUserLogin(const dict &data, const dict &error) {};

	virtual void onRspSOPUserLogout(const dict &data, const dict &error) {};

	virtual void onRspFASLUserLogin(const dict &data, const dict &error) {};

	virtual void onRspFASLUserLogout(const dict &data, const dict &error) {};

	virtual void onRspStockSubMarketData(const dict &data, const dict &error) {};

	virtual void onRspStockUnSubMarketData(const dict &data, const dict &error) {};

	virtual void onRspSOPSubMarketData(const dict &data, const dict &error) {};

	virtual void onRspSOPUnSubMarketData(const dict &data, const dict &error) {};

	virtual void onStockMarketData(const dict &data) {};

	virtual void onSOPMarketData(const dict &data) {};

	virtual void onRspStockAvailableQuot(const dict &data, const dict &error, bool last) {};

	virtual void onRspSopAvailableQuot(const dict &data, const dict &error, bool last) {};

	virtual void onRspUserMDPasswordUpdate(const dict &data, const dict &error) {};

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	int createDFITCMdApi(string pszFlowPath, string protocol);

	void release();

	//const char* pszFlowPath
	int init();

	int exit();

	int reqStockUserLogin(const dict &req);

	int reqStockUserLogout(const dict &req);

	int reqSOPUserLogin(const dict &req);

	int reqFASLUserLogin(const dict &req);

	int reqSOPUserLogout(const dict &req);

	int reqFASLUserLogout(const dict &req);

	int reqStockAvailableQuotQry(const dict &req);

	int reqSopAvailableQuotQry(const dict &req);

	int reqUserMDPasswordUpdate(const dict &req);


};

