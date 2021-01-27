//系统
#ifdef WIN32
#include "pch.h"
#endif

#include "vnoes.h"
#include "pybind11/pybind11.h"
#include    <mds_api/mds_async_api.h>


using namespace pybind11;
//using namespace Quant360;

//常量
#define ONCONNECTED 0
#define ONDISCONNECTED 1
#define ONRTNSTOCKDATA 2
#define ONRTNINDEXDATA 3
#define ONRTNOPTIONDATA 4


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

    /* API类的前置声明 */
class MdsClientApi;


/**
 * 交易接口响应类
 */




class MdApi
{

private:
    MdApi* api;            //API对象
    thread task_thread;                    //工作线程指针（向python中推送数据）
    TaskQueue task_queue;                //任务队列
    bool active = false;                //工作状态
    MdsAsyncApiChannelT *channel;

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
    int32       OnConnected(MdsAsyncApiChannelT *pAsyncChannel);
    /* 连接断开后的回调函数 */
    int32       OnDisConnected(MdsAsyncApiChannelT *pAsyncChannel) ;

    int32		OnData(MdsApiSessionInfoT *pSessionInfo, SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams);

    void		OnRtnStockData(const MdsMktDataSnapshotHeadT *head, const MdsStockSnapshotBodyT *stock);
    void		OnRtnIndexData(const MdsMktDataSnapshotHeadT *head, const MdsIndexSnapshotBodyT *index);
    void		OnRtnOptionData(const MdsMktDataSnapshotHeadT *head, const MdsStockSnapshotBodyT *option);
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

    virtual void onDisConnected(int channelType, const dict &data) {};

    virtual void onRtnStockData(const dict &error, const dict &data) {};
    virtual void onRtnIndexData(const dict &error, const dict &data) {};
    virtual void onRtnOptionData(const dict &error, const dict &data) {};

    //-------------------------------------------------------------------------------------
    //req:主动函数的请求字典
    //-------------------------------------------------------------------------------------

    bool createMdApi(string pCfgFile, string username, string password);

    bool init();

    int exit();
    bool subscribeMarketData(string symbol, int exchange, int product_type);


    private:
        /* 禁止拷贝构造函数 */
        MdApi(const MdApi&);
        /* 禁止赋值函数 */
        MdApi&      operator=(const MdApi&);

    public:
        /* 为了方便客户端使用而内置的流水号计数器, 可以基于该字段来递增维护客户端委托流水号 */
        int32               defaultClSeqNo;

    protected:
        MdsApiClientCfgT    _apiCfg;
        MdsApiSessionInfoT  _qryChannel;
        BOOL                _isInitialized;
        BOOL                _isRunning;

        //MdSpi *_pSpi;
        MdsAsyncApiContextT *_pAsyncContext;
        MdsAsyncApiChannelT *_pDefaultTcpChannel;
        MdsApiSessionInfoT  *_pQryChannel;
};


MdApi *md_api;

int32 MdOnConnected(MdsAsyncApiChannelT *pAsyncChannel,void *pCallbackParam);
int32 MdOnDisConnected(MdsAsyncApiChannelT *pAsyncChannel, void *pCallbackParam);

int32 MdOnData(MdsApiSessionInfoT *pSessionInfo, SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams);