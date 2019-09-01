//系统
#ifdef WIN32
#include "stdafx.h"
#endif

#include <string>

#include "vnda.h"
#include "pybind11/pybind11.h"
#include "da/DAMarketApi.h"

using namespace pybind11;
using namespace std;

///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class MarketApi : public IMarketEvent
{
private:
	CMarketApi *api; //API对象

public:
	MarketApi(){};

	~MarketApi(){};

	//-------------------------------------------------------------------------------------
	//API回调函数
	//-------------------------------------------------------------------------------------

	void OnFrontConnected();
	void OnFrontDisconnected(int iReason);
	void OnHeartBeatWarning(int iTimeLapse);

	void OnRspRawData(const char *rawData);
	void OnRspUserLogin(CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast);
	void OnRspTradeDate(CMarketRspTradeDateField *pRspTradeDate, CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast);
	void OnRspBrokerData(CMarketRspBrokerDataField *pRspBrokerData, CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast);
	void OnRspMarketData(CMarketRspMarketDataField *pRspMarketData, CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast);

	//-------------------------------------------------------------------------------------
	//Python回调函数
	//-------------------------------------------------------------------------------------

	virtual void onFrontConnected(){};

	virtual void onFrontDisconnected(int reqid){};

	virtual void onHeartBeatWarning(int reqid){};

	virtual void onRspRawData(string data){};

	virtual void onRspUserLogin(const dict &error, int reqid, bool last){};

	virtual void onRspTradeDate(const dict &data, const dict &error, int reqid, bool last){};

	virtual void onRspBrokerData(const dict &data, const dict &error, int reqid, bool last){};

	virtual void onRspMarketData(const dict &data, const dict &error, int reqid, bool last){};

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典

	//-------------------------------------------------------------------------------------

	string getVersion();

	void createMarketApi(bool recordLog, string logFileName);

	void init();

	void release();

	int exit();

	void setHeartbeatTimeout(int timeout);

	void registerNameServer(string address);

	int reqUserLogin(const dict &req, int reqid);

	int reqBrokerData(const dict &req, int reqid);

	int reqMarketData(const dict &req, int reqid);
};
