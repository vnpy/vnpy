//系统
#ifdef WIN32
#include "pch.h"
#endif

#include "vnoes.h"
#include "pybind11/pybind11.h"
#include "mds_client_sample.h"

using namespace pybind11;
using namespace Quant360;

//常量
#define ONCONNECTED 0
#define ONDISCONNECTED 1
#define ONRTNSTOCKDATA 2
#define ONRTNINDEXDATA 3
#define ONRTNOPTIONDATA 4


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class MdApi : public MdsClientSpi
{
private:
	MdsClientApi* api;            //API对象
	thread task_thread;                    //工作线程指针（向python中推送数据）
	TaskQueue task_queue;                //任务队列
	bool active = false;                //工作状态

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



	/* 连接或重新连接完成后的回调函数 */
	virtual int32       OnConnected(eMdsApiChannelTypeT channelType, MdsApiSessionInfoT *pSessionInfo, MdsApiSubscribeInfoT *pSubscribeInfo = NULL);
	/* 连接断开后的回调函数 */
	virtual int32       OnDisconnected(eMdsApiChannelTypeT channelType, MdsApiSessionInfoT *pSessionInfo);

	virtual void		OnRtnStockData(const MdsMktDataSnapshotHeadT *head, const MdsStockSnapshotBodyT *stock);
	virtual void		OnRtnIndexData(const MdsMktDataSnapshotHeadT *head, const MdsIndexSnapshotBodyT *index);
	virtual void		OnRtnOptionData(const MdsMktDataSnapshotHeadT *head, const MdsStockSnapshotBodyT *option);
	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------
	void processTask();

	int32 processConnected(Task *task);

	int32 processDisconnected(Task *task);

	void processRtnStockData(Task *task);
	void processRtnIndexData(Task *task);
	void processRtnOptionData(Task *task);

	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------


	virtual void onConnected(int channelType, const dict &data) {};

	virtual void onDisconnected(int channelType, const dict &data) {};

	virtual void onRtnStockData(const dict &error, const dict &data) {};
	virtual void onRtnIndexData(const dict &error, const dict &data) {};
	virtual void onRtnOptionData(const dict &error, const dict &data) {};

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createMdApi();

	bool loadCfg(string pCfgFile);

	bool setCustomizedIp(string pIpStr);

	bool setCustomizedMac(string pMacStr);

	bool setCustomizedDriverId(string pDriverStr);

	void setThreadUsername(string pUsername);

	void setThreadPassword(string pPassword);

	bool init();

	int exit();
	bool subscribeMarketData(const dict &req1, const dict &req2);

};