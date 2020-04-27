//系统
#ifdef WIN32
#include "pch.h"
#endif

#include "vnksgold.h"
#include "pybind11/pybind11.h"
#include "ksgold/KSGoldQuotMarketDataApi.h"


using namespace pybind11;
using namespace KSGoldTradeAPI;

//常量
#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONRSPUSERLOGIN 2
#define ONRSPUSERLOGOUT 3
#define ONRSPERROR 4
#define ONRSPSUBMARKETDATA 5
#define ONRSPUNSUBMARKETDATA 6
#define ONRTNDEPTHMARKETDATA 7



///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class MdApi : public CKSGoldQuoSpi
{
private:
	CKSGoldQuotApi* api;				//API对象
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

	///当客户端与交易后台建立起通信连接时，该方法被调用。
	///出现断线重连时，也会调用此方法
	///@param nResult 返回结果
	///        0x1001 建立连接
	///        0x1002 断线重连成功
	virtual void OnFrontConnected(int nResult);

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);

	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);


	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task *task);

	void processFrontDisconnected(Task *task);

	void processRspUserLogin(Task *task);

	void processRspUserLogout(Task *task);

	void processRspError(Task *task);

	void processRspSubMarketData(Task *task);

	void processRspUnSubMarketData(Task *task);

	void processRtnDepthMarketData(Task *task);
	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------
	virtual void onFrontConnected(int nResult) {};

	virtual void onFrontDisconnected(int nResult) {};

	virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspError(const dict &error, int reqid, bool last) {};

	virtual void onRspSubMarketData(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspUnSubMarketData(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRtnDepthMarketData(const dict &data) {};

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void release();

	bool init();

	int exit();

	int join();

	void registerFront(string pszFrontAddress);

	void createGoldQutoApi(string pszFlowPath = " ");

	int subscribeMarketData(string ppInstrumentID, int reqid);

	int unSubscribeMarketData(string ppInstrumentID, int reqid);

	int reqUserLogin(const dict &req, int reqid);

	int reqUserLogout(const dict &req, int reqid);
};
