//系统
#ifdef WIN32
#include "pch.h"
#endif




#include "vnihq.h"
#include "pybind11/pybind11.h"
#include "ihq/IStoneMdApi.h"

using namespace pybind11;
using namespace istone::mdapi;

//常量
#define ONFRONTCONNECTED 0
#define ONFRONTDISCONNECTED 1
#define ONHEARTBEATWARNING 2
#define ONRSPERROR 3
#define ONRSPUSERLOGIN 4
#define ONRSPUSERLOGOUT 5
#define ONRSPSUBALLMARKETDATA 6
#define ONRSPUNSUBALLMARKETDATA 7
#define ONRSPSUBALLTICKBYTICK 8
#define ONRSPUNSUBALLTICKBYTICK 9
#define ONRSPSUBMARKETDATA 10
#define ONRSPUNSUBMARKETDATA 11
#define ONRSPSUBTICKBYTICK 12
#define ONRSPUNSUBTICKBYTICK 13
#define ONRTNDEPTHMARKETDATA 14
#define ONRTNTICKBYTICK 15
#define ONRTNORDERBOOK 16
#define ONRSPSUBORDERBOOK 17
#define ONRSPUNSUBORDERBOOK 18



///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class MdApi : public IStoneMdSpi
{
private:
    IStoneMdApi* api;				//API对象
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
    virtual void OnFrontConnected() ;

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    ///@param nReason 错误原因
    ///        0x1001 网络读失败
    ///        0x1002 网络写失败
    ///        0x2001 接收心跳超时
    ///        0x2002 发送心跳失败
    ///        0x2003 收到错误报文
    virtual void OnFrontDisconnected(int nReason) ;

    ///心跳超时警告。当长时间未收到报文时，该方法被调用。
    ///@param nTimeLapse 距离上次接收报文的时间
    virtual void OnHeartBeatWarning(int nTimeLapse) ;

    ///错误应答
    virtual void OnRspError(CIStoneRspInfo* pRspInfo, int nRequestID, bool bIsLast) ;

    ///用户登录应答
    ///@param pRspUserLogout	登录成功时，返回该信息
    ///@param pRspInfo			登录成功时，pRspInfo为空；登录失败时，pRspInfo返回错误代码与信息
    virtual void OnRspUserLogin(CIStoneRspUserLogin* pRspUserLogin, CIStoneRspInfo* pRspInfo, int nRequestID, bool bIsLast) ;

    ///用户退出应答
    ///@param pRspUserLogout	退出成功时，返回该信息
    ///@param pRspInfo			退出成功时，pRspInfo为空；退出失败时，pRspInfo返回错误代码与信息
    virtual void OnRspUserLogout(CIStoneRspUserLogout* pRspUserLogout, CIStoneRspInfo* pRspInfo, int nRequestID, bool bIsLast) ;

    ///用户深度行情全订阅应答
    ///@param tickType						股票类型, 多类型订阅可使用 ISTONE_TICKER_TYPE_SPOT | ISTONE_TICKER_TYPE_INDEX 方式订阅。
    ///        ISTONE_TICKER_TYPE_SPOT		<普通股票<债券<基金
    ///        ISTONE_TICKER_TYPE_INDEX		<指数
    ///        ISTONE_TICKER_TYPE_OPTION	<期权
    ///@param exchangeType					交易所类型， 多交易所可使用 ISTONE_EXCHANGE_SH | ISTONE_EXCHANGE_SZ 方式订阅。
    ///        ISTONE_EXCHANGE_SH			<上证
    ///        ISTONE_EXCHANGE_SZ			<深证
    virtual void OnRspSubAllMarketData(int tickType, int exchangeID, int nRequestID, bool isSuccess) ;

    ///用户深度行情全退订应答
    ///@param tickType						股票类型, 多类型订阅可使用 ISTONE_TICKER_TYPE_SPOT | ISTONE_TICKER_TYPE_INDEX 方式订阅。
    ///        ISTONE_TICKER_TYPE_SPOT		<普通股票<债券<基金
    ///        ISTONE_TICKER_TYPE_INDEX		<指数
    ///        ISTONE_TICKER_TYPE_OPTION	<期权
    ///@param exchangeType					交易所类型， 多交易所可使用 ISTONE_EXCHANGE_SH | ISTONE_EXCHANGE_SZ 方式订阅。
    ///        ISTONE_EXCHANGE_SH			<上证
    ///        ISTONE_EXCHANGE_SZ			<深证
    virtual void OnRspUnSubAllMarketData(int tickType, int exchangeID, int nRequestID, bool isSuccess) ;

    ///用户逐笔行情全订阅应答
    ///@param tickType						股票类型, 多类型订阅可使用 ISTONE_TICKER_TYPE_SPOT | ISTONE_TICKER_TYPE_INDEX 方式订阅。
    ///        ISTONE_TICKER_TYPE_SPOT		<普通股票<债券<基金
    ///        ISTONE_TICKER_TYPE_INDEX		<指数
    ///        ISTONE_TICKER_TYPE_OPTION	<期权
    ///@param exchangeType					交易所类型， 多交易所可使用 ISTONE_EXCHANGE_SH | ISTONE_EXCHANGE_SZ 方式订阅。
    ///        ISTONE_EXCHANGE_SH			<上证
    ///        ISTONE_EXCHANGE_SZ			<深证
    virtual void OnRspSubAllTickByTick(int exchangeID, int nRequestID, bool isSuccess) ;

    ///用户逐笔行情全退订应答
    ///@param tickType						股票类型, 多类型订阅可使用 ISTONE_TICKER_TYPE_SPOT | ISTONE_TICKER_TYPE_INDEX 方式订阅。
    ///        ISTONE_TICKER_TYPE_SPOT		<普通股票<债券<基金
    ///        ISTONE_TICKER_TYPE_INDEX		<指数
    ///        ISTONE_TICKER_TYPE_OPTION	<期权
    ///@param exchangeType					交易所类型， 多交易所可使用 ISTONE_EXCHANGE_SH | ISTONE_EXCHANGE_SZ 方式订阅。
    ///        ISTONE_EXCHANGE_SH			<上证
    ///        ISTONE_EXCHANGE_SZ			<深证
    virtual void OnRspUnSubAllTickByTick(int exchangeID, int nRequestID, bool isSuccess) ;

    ///用户深度行情订阅应答
    ///@param ppInstrumentID	股票代码
    ///@param nCount			股票数量
    virtual void OnRspSubMarketData(char* tickers[], int count, int nRequestID, bool bIsSuccess) ;

    ///用户深度行情退订应答
    ///@param ppInstrumentID	股票代码
    ///@param nCount			股票数量
    virtual void OnRspUnSubMarketData(char* tickers[], int count, int nRequestID, bool bIsSuccess) ;

    ///用户逐笔行情订阅应答
    ///@param ppInstrumentID	股票代码
    ///@param nCount			股票数量
    virtual void OnRspSubTickByTick(char* tickers[], int count, int nRequestID, bool bIsSuccess) ;

    ///用户逐笔行情退订应答
    ///@param ppInstrumentID	股票代码
    ///@param nCount			股票数量
    virtual void OnRspUnSubTickByTick(char* tickers[], int count, int nRequestID, bool bIsSuccess) ;

    ///深度行情通知
    virtual void OnRtnDepthMarketData(CIStoneDepthMarketData* data) ;

    ///逐笔行情通知
    virtual void OnRtnTickByTick(CIStoneTickByTick* data) ;

    ///订单簿通知
    virtual void OnRtnOrderBook(CIStoneOrderBook* data) ;

    ///用户订单簿订阅应答
    ///@param ppInstrumentID	股票代码
    ///@param nCount			股票数量
    virtual void OnRspSubOrderBook(char* tickers[], int count, int nRequestID, bool bIsSuccess) ;

    ///用户订单簿退订应答
    ///@param ppInstrumentID	股票代码
    ///@param nCount			股票数量
    virtual void OnRspUnSubOrderBook(char* tickers[], int count, int nRequestID, bool bIsSuccess) ;

    //-------------------------------------------------------------------------------------
    //task：任务
    //-------------------------------------------------------------------------------------

    void processTask();

    void processFrontConnected(Task *task);

    void processFrontDisconnected(Task *task);

    void processHeartBeatWarning(Task *task);

    void processRspError(Task *task);

    void processRspUserLogin(Task *task);

    void processRspUserLogout(Task *task);

    void processRspSubAllMarketData(Task *task);

    void processRspUnSubAllMarketData(Task *task);

    void processRspSubAllTickByTick(Task *task);

    void processRspUnSubAllTickByTick(Task *task);

    void processRspSubMarketData(Task *task);

    void processRspUnSubMarketData(Task *task);

    void processRspSubTickByTick(Task *task);

    void processRspUnSubTickByTick(Task *task);

    void processRtnDepthMarketData(Task *task);

    void processRtnTickByTick(Task *task);

    void processRtnOrderBook(Task *task);

    void processRspSubOrderBook(Task *task);

    void processRspUnSubOrderBook(Task *task);


    //-------------------------------------------------------------------------------------
    //data：回调函数的数据字典
    //error：回调函数的错误字典
    //id：请求id
    //last：是否为最后返回
    //i：整数
    //-------------------------------------------------------------------------------------

    virtual void onFrontConnected() {};

    virtual void onFrontDisconnected(int nReason) {};

    virtual void onHeartBeatWarning(int nTimeLapse) {};

    virtual void onRspError(const dict &error, int nRequestID, bool bIsLast) {};

    virtual void onRspUserLogin(const dict &data, const dict &error, int nRequestID, bool bIsLast) {};

    virtual void onRspUserLogout(const dict &data, const dict &error, int nRequestID, bool bIsLast) {};

    virtual void onRspSubAllMarketData(int tickType, int exchangeID, int nRequestID, bool isSuccess) {};

    virtual void onRspUnSubAllMarketData(int tickType, int exchangeID, int nRequestID, bool isSuccess) {};

    virtual void onRspSubAllTickByTick(int exchangeID, int nRequestID, bool isSuccess) {};

    virtual void onRspUnSubAllTickByTick(int exchangeID, int nRequestID, bool isSuccess) {};

    virtual void onRspSubMarketData(string tickers, int count, int nRequestID, bool bIsSuccess) {};

    virtual void onRspUnSubMarketData(string tickers, int count, int nRequestID, bool bIsSuccess) {};

    virtual void onRspSubTickByTick(string tickers, int count, int nRequestID, bool bIsSuccess) {};

    virtual void onRspUnSubTickByTick(string tickers, int count, int nRequestID, bool bIsSuccess) {};

    virtual void onRtnDepthMarketData(const dict &data) {};

    virtual void onRtnTickByTick(const dict &data) {};

    virtual void onRtnOrderBook(const dict &data) {};

    virtual void onRspSubOrderBook(string tickers, int count, int nRequestID, bool bIsSuccess) {};

    virtual void onRspUnSubOrderBook(string tickers, int count, int nRequestID, bool bIsSuccess) {};



    //-------------------------------------------------------------------------------------
    //req:主动函数的请求字典
    //-------------------------------------------------------------------------------------

    void createMdUserApi(string pszFlowPath = "");

    void release();

    void init();

    int join();

    int exit();

    string getTradingDay();

    void registerFront(string pszFrontAddress);

    void registerFpgaFront(string pMutilcastAddr);

    void registerTcpLocalAddr(string localTcpAddr);

    void registerUdpLocalAddr(string localAddr);

    void registerEfviDevice(string device);

    void setHeartbeatTimeout(uint32_t timeout);

    int reqUserLogin(const dict &req, int reqid);

    int reqUserLogout(const dict &req, int reqid);


    int subAllMarketData(int tickType, int exchangeID, int nRequestID);

    int unSubAllMarketData(int tickType, int exchangeID, int nRequestID);

    int subAllTickByTick(int exchangeID, int nRequestID);

    int unSubAllTickByTick(int exchangeID, int nRequestID);

    int subMarketData(string ppInstrumentID,int nRequestID);

    int unSubMarketData(string ppInstrumentID, int nRequestID);

    int subTickByTick(string ppInstrumentID, int nRequestID);

    int unSubTickByTick(string ppInstrumentID,int nRequestID);

    int subAllOrderBook(int exchangeID, int nRequestID);

    int unSubAllOrderBook(int exchangeID, int nRequestID);

    int subOrderBook(string ppInstrumentID, int nRequestID);

    int unSubOrderBook(string ppInstrumentID, int nRequestID);
};
