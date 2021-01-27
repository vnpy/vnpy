//系统
#ifdef WIN32
#include "stdafx.h"
#endif

#include "vnnh.h"
#include "pybind11/pybind11.h"
#include "nh/md/CNhMdApi.h"


using namespace pybind11;

//常量
#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONHEARTBEATWARNING 2
#define ONRSPERROR 3
#define ONRTNMARKETDATA 4
#define ONRSPUTPLOGIN 5
#define ONRSPUTPLOGOUT 6
#define ONRSPSUBSCRIBE 7
#define ONRSPUNSUBSCRIBE 8
#define ONRSPQRYEXCHANGE 9
#define ONRSPQRYINSTRUMENT 10


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class MdApi : public CNhMdSpi
{
private:
	CNhMdApi* api;						//API对象
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

	///当客户端与行情网关建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected() ;

	///当客户端与行情网关通信连接断开时，该方法被调用。
	virtual void OnFrontDisConnected() ;

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	/* \param nTimeLapse 距离上次接收报文的时间
	****************************************/
	virtual void OnHeartBeatWarning(int nTimeLapse) ;

	/***************************************
	/* \fn    OnRspError
	/* \brief 错误应答
	/* \param ERRORMSGINFO_t & req,错误应答消息
	/* \param TSequenceIDType nRequestID，如果是由于request引起的错误，则为对应请求ID，否则，为0
	/* \return void
	****************************************/
	virtual void OnRspError(ERRORMSGINFO_t &pRspInfo, TSequenceIDType nRequestID) ;

	///行情通知
	virtual void OnRtnMarketData(STKMarketData_t &pData) ;

	/***************************************
	/* \fn    OnRspUtpLogin
	/* \brief 登录南华统一交易平台UTP请求时响应
	/* \param RspUtpLoginField_t & req
	/* \param TSequenceIDType nRequestID，
	/* \return void
	****************************************/
	virtual void OnRspUtpLogin(const RspUtpLoginField_t& rsp, TSequenceIDType nRequestID) ;

	/***************************************
	/* \fn    OnRspUtpLogout
	/* \brief 登录南华统一交易平台UTP请求时响应
	/* \param RspUtpLogoutField_t & req
	/* \param TSequenceIDType nRequestID
	/* \return void
	****************************************/
	virtual void OnRspUtpLogout(const RspUtpLogoutField_t& rsp, TSequenceIDType nRequestID) ;

	/***************************************
	/* \fn    OnRspSubscribe
	/* \brief 订阅行情数据请求时响应
	/* \param RspSubscribeField_t & req
	/* \param TSequenceIDType nRequestID
	/* \return void
	****************************************/
	virtual void OnRspSubscribe(const RspSubscribeField_t& rsp, TSequenceIDType nRequestID) ;

	/***************************************
	/* \fn    OnRspUnSubscribe
	/* \brief 取消订阅行情数据请求时响应
	/* \param RspUnSubscribeField_t & req
	/* \param TSequenceIDType nRequestID
	/* \return void
	****************************************/
	virtual void OnRspUnSubscribe(const RspUnSubscribeField_t& rsp, TSequenceIDType nRequestID) ;

	/***************************************
	* \fn    OnRspQryExchange
	* \brief 查询交易所请求时响应
	* \param RspQryExchangeField_t & rsp
	* \param TSequenceIDType nRequestID
	* \return void
	****************************************/
	virtual void OnRspQryExchange(const RspQryExchangeField_t& rsp, TSequenceIDType nRequestID) ;

	/***************************************
	* \fn    OnRspQryInstrument
	* \brief 查询合约请求时响应
	* \param RspQryInstrumentField_t & rsp
	* \param TSequenceIDType nRequestID
	* \return void
	****************************************/
	virtual void OnRspQryInstrument(const RspQryInstrumentField_t& rsp, TSequenceIDType nRequestID) ;

	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task *task);

	void processFrontDisConnected(Task *task);

	void processHeartBeatWarning(Task *task);

	void processRspError(Task *task);

	void processRtnMarketData(Task *task);

	void processRspUtpLogin(Task *task);

	void processRspUtpLogout(Task *task);

	void processRspSubscribe(Task *task);

	void processRspUnSubscribe(Task *task);

	void processRspQryExchange(Task *task);

	void processRspQryInstrument(Task *task);

	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------

	virtual void onFrontConnected() {};

	virtual void onFrontDisConnected() {};

	virtual void onHeartBeatWarning(int timeLapse) {};

	virtual void onRspError(const dict &data, int reqid) {};

	virtual void onRtnMarketData(const dict &data) {};

	virtual void onRspUtpLogin(const dict &data, int reqid) {};

	virtual void onRspUtpLogout(const dict &data, int reqid) {};

	virtual void onRspSubscribe(const dict &data, int reqid) {};

	virtual void onRspUnSubscribe(const dict &data, int reqid) {};

	virtual void onRspQryExchange(const dict &data, int reqid) {};

	virtual void onRspQryInstrument(const dict &data, int reqid) {};

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createMdApi();

	void release();

	void init();

	string getVersion();

	void registerFront(string address);

	void registerNameServer(string server);

	int exit();

	int reqUtpLogin(const dict &req, int reqid);

	int reqUtpLogout(int reqid);

	int reqSubscribe(string symbol, int reqid);

	int reqUnSubscribe(string symbol, int reqid);

	int reqAuthUserPasswor(const dict &req, int reqid);

	int reqQryExchange(const dict &req, int reqid);

	int reqQryInstrument(const dict &req, int reqid);
};
