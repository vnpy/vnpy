//系统
#ifdef WIN32
#include "stdafx.h"
#endif


#include "vnfemas.h"
#include "pybind11/pybind11.h"
#include "femas/USTPFtdcMduserApi.h"


using namespace pybind11;

//常量
#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONHEARTBEATWARNING 2
#define ONPACKAGESTART 3
#define ONPACKAGEEND 4
#define ONRSPERROR 5
#define ONRSPUSERLOGIN 6
#define ONRSPUSERLOGOUT 7
#define ONRTNDEPTHMARKETDATA 8
#define ONRSPSUBMARKETDATA 9
#define ONRSPUNSUBMARKETDATA 10
#define ONRSPGETMARKETTOPIC 11
#define ONRSPGETMARKETDATA 12




///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class MdApi : public CUstpFtdcMduserSpi
{
private:
	CUstpFtdcMduserApi* api;				//API对象
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
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason);

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///报文回调开始通知。当API收到一个报文后，首先调用本方法，然后是各数据域的回调，最后是报文回调结束通知。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageStart(int nTopicID, int nSequenceNo);

	///报文回调结束通知。当API收到一个报文后，首先调用报文回调开始通知，然后是各数据域的回调，最后调用本方法。
	///@param nTopicID 主题代码（如私有流、公共流、行情流等）
	///@param nSequenceNo 报文序号
	virtual void OnPackageEnd(int nTopicID, int nSequenceNo);


	///错误应答
	virtual void OnRspError(CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///风控前置系统用户登录应答
	virtual void OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///用户退出应答
	virtual void OnRspUserLogout(CUstpFtdcRspUserLogoutField *pRspUserLogout, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///深度行情通知
	virtual void OnRtnDepthMarketData(CUstpFtdcDepthMarketDataField *pDepthMarketData);

	///订阅合约的相关信息
	virtual void OnRspSubMarketData(CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///退订合约的相关信息
	virtual void OnRspUnSubMarketData(CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///获取行情主题信息应答
	virtual void OnRspGetMarketTopic(CUstpFtdcRspMarketTopicField *pRspMarketTopic, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///获取行情快照应答
	virtual void OnRspGetMarketData(CUstpFtdcRspDepthMarketDataField *pRspDepthMarketData, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task *task);

	void processFrontDisconnected(Task *task);

	void processHeartBeatWarning(Task *task);

	void processPackageStart(Task *task);

	void processPackageEnd(Task *task);

	void processRspError(Task *task);

	void processRspUserLogin(Task *task);

	void processRspUserLogout(Task *task);

	void processRtnDepthMarketData(Task *task);

	void processRspSubMarketData(Task *task);

	void processRspUnSubMarketData(Task *task);

	void processRspGetMarketTopic(Task *task);

	void processRspGetMarketData(Task *task);

	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------

	virtual void onFrontConnected() {};

	virtual void onFrontDisconnected(int reqid) {};

	virtual void onHeartBeatWarning(int reqid) {};

	virtual void onPackageStart(int reqid) {};

	virtual void onPackageEnd(int reqid) {};

	virtual void onRspError(const dict &data, int reqid, bool last) {};

	virtual void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRtnDepthMarketData(const dict &data) {};


	virtual void onRspSubMarketData(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspUnSubMarketData(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspGetMarketTopic(const dict &data, const dict &error, int reqid, bool last) {};

	virtual void onRspGetMarketData(const dict &data, const dict &error, int reqid, bool last) {};

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createFtdcMdApi(string pszFlowPath = "");

	void release();

	void init();

	int join();

	int exit();

	string getTradingDay();

	void registerFront(string pszFrontAddress);

	void registerNameServer(string pszNsAddress);


	int registerCertificateFile(string pszCertFileName, string pszKeyFileName, string pszCaFileName, string pszKeyFilePassword);

	void subscribeMarketDataTopic(int topicID, int resumeType);

	int subMarketData(string instrumentID);

	int unSubMarketData(string instrumentID);

	void setHeartbeatTimeout(int timeout);

	int reqUserLogin(const dict &req, int reqid);

	int reqUserLogout(const dict &req, int reqid);

};
