//系统
#ifdef WIN32
#include "pch.h"
#endif

#include "vnsip.h"
#include "pybind11/pybind11.h"
#include "isipuix.h"


using namespace pybind11;
using namespace api;



///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class MdApi : public CSipMdSpi
{
private:
	ISIPUIX_EXPORT CSipMdApi* api;            //API对象
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

	virtual void OnLog(int32_t level, const char *source, const char *slog);
	/*!
	\brief 登录成功后回调，可在里面订阅
	\param chn 通道号,一个通道时为0,其他为1开始。
	*/

	/*!
	\brief 断开时回调
	\param chn 通道号。
	*/
	virtual void OnDisconnect(int32_t chn);

	/*
	\brief 行情订阅回调
	\param errmsg 存储错误码errcode与错误信息errstr的结构体，errcode值为0代表成功，其余值为错误码，错误信息会存储在errstr字符串中
	\param errmsg 结构体中的channel、mktype与datatype则是用于识别证券代码codes订阅失败的对应通道、市场类型与数据类型。
	*/
	virtual void OnSubscribe(ErrMsg *errmsg);

	/*
	\brief 行情退订回调
	\param errmsg 存储错误码errcode与错误信息errstr的结构体，errcode值为0代表成功，其余值为错误码，错误信息会存储在errstr字符串中
	\param errmsg 结构体中的channel、mktype与datatype则是用于识别证券代码codes退订失败的对应通道、市场类型与数据类型。
	*/
	virtual void OnUnSubscribe(ErrMsg *errmsg);

	/*!
	\brief L2行情数据回调
	\param mktype 代表订阅的市场类型
	\param code 订阅的证券代码
	\param dataL2 L2行情结构体
	*/
	virtual void OnDepthMarketData(MKtype mk_type, char *code, Stock_MarketData *dataL2);

	/*!
	\brief L1行情数据回调
	\param mktype 代表订阅的市场类型
	\param code 订阅的证券代码
	\param dataL1 L1行情结构体
	*/
	virtual void OnMarketData(MKtype mk_type, char *code, StockMarketDataL1 *dataL1);

	/*!
	\brief 指数行情回调
	\param mktype 代表订阅的市场类型
	\param code 订阅的证券代码
	\param stockindex 指数行情结构体
	*/
	virtual void OnIndexData(MKtype mk_type, char *code, Stock_IndexData *stockindex);


	/*!
	\brief 委托队列行情数据回调
	\param mktype 代表订阅的市场类型
	\param code 订阅的证券代码
	\param orderqueue 委托队列行情数据结构体
	*/
	virtual void OnOrderQueue(MKtype mk_type, char *code, StockOrderQueue *orderqueue);

	/*!
	\brief 上交所逐笔成交行情数据回调
	\param code 订阅的证券代码
	\param steptrade 上交所逐笔行情数据结构体
	*/
	virtual void OnSHTrade(char *code, t_SH_StockStepTrade *steptrade);

	/*!
	\brief 深交所逐笔成交行情数据回调
	\param code 订阅的证券代码
	\param steptrade 深交所逐笔行情数据结构体
	*/
	virtual void OnSZTrade(char *code, T_SZ_STEPTRADE *steptrade);

	/*!
	\brief 深交所逐笔委托行情数据回调
	\param code 订阅的证券代码
	\param steptrade 深交所逐笔行情数据结构体
	*/
	virtual void OnSZOrder(char *code, T_SZ_STEPORDER *steporder);

	/*!
	\brief 上交所基础信息回调
	\param code 订阅的证券代码
	\param baseinfodata 上交所基础信息数据结构体
	*/
	virtual void OnSHBaseInfo(char *code, T_SH_BaseInfo *baseinfodata);

	/*!
	\brief 分钟K线回调
	\param mktype 代表订阅的市场类型
	\param code 订阅的证券代码
	\param kline 分钟K线数据结构体
	*/
	virtual void OnKline(MKtype mk_type, char *code, T_Kline *kline);


	/*!
	\brief ETF扩展行情数据回调
	\param mktype 代表订阅的市场类型
	\param code 订阅的证券代码
	\param etfextdata ETF扩展行情数据结构体
	*/
	virtual void OnEtfExtData(MKtype mk_type, char *code, T_ETFEXTENDS *etfextdata);
    //-------------------------------------------------------------------------------------
    //data：回调函数的数据字典
    //error：回调函数的错误字典
    //id：请求id
    //last：是否为最后返回
    //i：整数
    //-------------------------------------------------------------------------------------
	virtual void onLog(int level, string source, string slog) {};

	virtual void onDisconnect(int chn) {};

	virtual void onSubscribe(const dict &error) {};

	virtual void onUnSubscribe(const dict &error) {};

	virtual void onDepthMarketData(int mk_type, string code, const dict &data) {};

	virtual void onMarketData(int mk_type, string code, const dict &data) {};

	virtual void onIndexData(int mk_type, string code, const dict &data) {};

	virtual void onOrderQueue(int mk_type, string code, const dict &data) {};

	virtual void onSHTrade(string code, const dict &data) {};

	virtual void onSZTrade(string code, const dict &data) {};

	virtual void onSZOrder(string code, const dict &data) {};

	virtual void onSHBaseInfo(string code, const dict &data) {};

	virtual void onKline(int mk_type, string code, const dict &data) {};

	virtual void onEtfExtData(int mk_type, string code, const dict &data) {};


    //-------------------------------------------------------------------------------------
    //req:主动函数的请求字典
    //-------------------------------------------------------------------------------------
	int createMdApi();

	int login();

	int stop();
	void release();

	int exit();

	int subscribeDepthMarketData(int mk_type, string code);

	int subscribeMarketData(int mk_type, string code);

	int subscribeIndexData(int mk_type, string code);

	int unSubscribeDepthMarketData(int mk_type, string code);

	int unSubscribeMarketData(int mk_type, string code);

	int unSubscribeIndexData(int mk_type, string code);

	int subscribeOrderQueue(int mk_type, string code);

	int unSubscribeOrderQueue(int mk_type, string code);

	int subscribeStepTrade(int mk_type, string code);

	int unSubscribeStepTrade(int mk_type, string code);

	int subscribeStepOrder(int mk_type, string code);

	int unSubscribeStepOrder(int mk_type, string code);

	int subscribeBaseInfo(int mk_type);

	int unSubscribeBaseInfo(int mk_type, string code);

	int subscribeKline(int mk_type, string code);

	int unSubscribeKline(int mk_type, string code);

	int subscribeFutures(int mk_type, string code);

	int unSubscribeFutures(int mk_type, string code);

	int subscribeEtfExt(int mk_type, string code);

	int unSubscribeEtfExt(int mk_type, string code);


};
