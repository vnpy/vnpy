#pragma once
#include "IStoneMdApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MD_API_EXPORT
#define MD_API_EXPORT __declspec(dllexport)
#else
#define MD_API_EXPORT __declspec(dllimport)
#endif
#else
#define MD_API_EXPORT 
#endif

using namespace istone::mdapi;
namespace istone
{
    namespace mdapi
    {
        class IStoneMdSpi
        {
        public:
            ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
            virtual void OnFrontConnected() {};

            ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
            ///@param nReason 错误原因
            ///        0x1001 网络读失败
            ///        0x1002 网络写失败
            ///        0x2001 接收心跳超时
            ///        0x2002 发送心跳失败
            ///        0x2003 收到错误报文
            virtual void OnFrontDisconnected(int nReason) {};

            ///心跳超时警告。当长时间未收到报文时，该方法被调用。
            ///@param nTimeLapse 距离上次接收报文的时间
            virtual void OnHeartBeatWarning(int nTimeLapse) {};

            ///错误应答
            virtual void OnRspError(CIStoneRspInfo* pRspInfo, int nRequestID, bool bIsLast) {};

            ///用户登录应答
            ///@param pRspUserLogout	登录成功时，返回该信息
            ///@param pRspInfo			登录成功时，pRspInfo为空；登录失败时，pRspInfo返回错误代码与信息
            virtual void OnRspUserLogin(CIStoneRspUserLogin* pRspUserLogin, CIStoneRspInfo* pRspInfo, int nRequestID, bool bIsLast) {};

            ///用户退出应答
            ///@param pRspUserLogout	退出成功时，返回该信息
            ///@param pRspInfo			退出成功时，pRspInfo为空；退出失败时，pRspInfo返回错误代码与信息
            virtual void OnRspUserLogout(CIStoneRspUserLogout* pRspUserLogout, CIStoneRspInfo* pRspInfo, int nRequestID, bool bIsLast) {};

            ///用户深度行情全订阅应答
            ///@param tickType						股票类型, 多类型订阅可使用 ISTONE_TICKER_TYPE_SPOT | ISTONE_TICKER_TYPE_INDEX 方式订阅。
            ///        ISTONE_TICKER_TYPE_SPOT		<普通股票<债券<基金
            ///        ISTONE_TICKER_TYPE_INDEX		<指数
            ///        ISTONE_TICKER_TYPE_OPTION	<期权
            ///@param exchangeType					交易所类型， 多交易所可使用 ISTONE_EXCHANGE_SH | ISTONE_EXCHANGE_SZ 方式订阅。
            ///        ISTONE_EXCHANGE_SH			<上证
            ///        ISTONE_EXCHANGE_SZ			<深证
            virtual void OnRspSubAllMarketData(int tickType, int exchangeID, int nRequestID, bool isSuccess) {};

            ///用户深度行情全退订应答
            ///@param tickType						股票类型, 多类型订阅可使用 ISTONE_TICKER_TYPE_SPOT | ISTONE_TICKER_TYPE_INDEX 方式订阅。
            ///        ISTONE_TICKER_TYPE_SPOT		<普通股票<债券<基金
            ///        ISTONE_TICKER_TYPE_INDEX		<指数
            ///        ISTONE_TICKER_TYPE_OPTION	<期权
            ///@param exchangeType					交易所类型， 多交易所可使用 ISTONE_EXCHANGE_SH | ISTONE_EXCHANGE_SZ 方式订阅。
            ///        ISTONE_EXCHANGE_SH			<上证
            ///        ISTONE_EXCHANGE_SZ			<深证
            virtual void OnRspUnSubAllMarketData(int tickType, int exchangeID, int nRequestID, bool isSuccess) {};

            ///用户逐笔行情全订阅应答
            ///@param tickType						股票类型, 多类型订阅可使用 ISTONE_TICKER_TYPE_SPOT | ISTONE_TICKER_TYPE_INDEX 方式订阅。
            ///        ISTONE_TICKER_TYPE_SPOT		<普通股票<债券<基金
            ///        ISTONE_TICKER_TYPE_INDEX		<指数
            ///        ISTONE_TICKER_TYPE_OPTION	<期权
            ///@param exchangeType					交易所类型， 多交易所可使用 ISTONE_EXCHANGE_SH | ISTONE_EXCHANGE_SZ 方式订阅。
            ///        ISTONE_EXCHANGE_SH			<上证
            ///        ISTONE_EXCHANGE_SZ			<深证
            virtual void OnRspSubAllTickByTick(int exchangeID, int nRequestID, bool isSuccess) {};

            ///用户逐笔行情全退订应答
            ///@param tickType						股票类型, 多类型订阅可使用 ISTONE_TICKER_TYPE_SPOT | ISTONE_TICKER_TYPE_INDEX 方式订阅。
            ///        ISTONE_TICKER_TYPE_SPOT		<普通股票<债券<基金
            ///        ISTONE_TICKER_TYPE_INDEX		<指数
            ///        ISTONE_TICKER_TYPE_OPTION	<期权
            ///@param exchangeType					交易所类型， 多交易所可使用 ISTONE_EXCHANGE_SH | ISTONE_EXCHANGE_SZ 方式订阅。
            ///        ISTONE_EXCHANGE_SH			<上证
            ///        ISTONE_EXCHANGE_SZ			<深证
            virtual void OnRspUnSubAllTickByTick(int exchangeID, int nRequestID, bool isSuccess) {};

            ///用户深度行情订阅应答
            ///@param ppInstrumentID	股票代码
            ///@param nCount			股票数量
            virtual void OnRspSubMarketData(char* tickers[], int count, int nRequestID, bool bIsSuccess) {};

            ///用户深度行情退订应答
            ///@param ppInstrumentID	股票代码
            ///@param nCount			股票数量
            virtual void OnRspUnSubMarketData(char* tickers[], int count, int nRequestID, bool bIsSuccess) {};

            ///用户逐笔行情订阅应答
            ///@param ppInstrumentID	股票代码
            ///@param nCount			股票数量
            virtual void OnRspSubTickByTick(char* tickers[], int count, int nRequestID, bool bIsSuccess) {};

            ///用户逐笔行情退订应答
            ///@param ppInstrumentID	股票代码
            ///@param nCount			股票数量
            virtual void OnRspUnSubTickByTick(char* tickers[], int count, int nRequestID, bool bIsSuccess) {};

            ///深度行情通知
            virtual void OnRtnDepthMarketData(CIStoneDepthMarketData* data) {};

            ///逐笔行情通知
            virtual void OnRtnTickByTick(CIStoneTickByTick* data) {};

            ///订单簿通知
            virtual void OnRtnOrderBook(CIStoneOrderBook* data) {};

            ///用户订单簿订阅应答
            ///@param ppInstrumentID	股票代码
            ///@param nCount			股票数量
            virtual void OnRspSubOrderBook(char* tickers[], int count, int nRequestID, bool bIsSuccess) {};

            ///用户订单簿退订应答
            ///@param ppInstrumentID	股票代码
            ///@param nCount			股票数量
            virtual void OnRspUnSubOrderBook(char* tickers[], int count, int nRequestID, bool bIsSuccess) {};
        };

        class MD_API_EXPORT IStoneMdApi
        {
        public:
            ///创建MduserApi
            ///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
            ///@return 创建出的UserApi
            static IStoneMdApi* CreateMdUserApi(const char* pszFlowPath = "");

            ///获取API的版本信息
            ///@retrun 获取到的版本号
            static const char* GetVersion();

            ///删除接口对象本身
            ///@remark 不再使用本接口对象时,调用该函数删除接口对象
            virtual void Release() = 0;

            ///初始化
            ///@remark 初始化运行环境,只有调用后,接口才开始工作
            virtual int Init() = 0;

            ///等待接口线程结束运行
            ///@return 线程退出代码
            virtual int Join() = 0;

            ///获取当前交易日
            ///@retrun 获取到的交易日
            ///@remark 只有登录成功后,才能得到正确的交易日
            virtual const char* GetTradingDay() = 0;

            ///注册前置机网络地址
            ///@param pszFrontAddress：前置机网络地址。
            ///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
            ///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
            virtual void RegisterFront(const char* pszFrontAddress) = 0;

            ///注册行情组播地址
            ///@param pMutilcastAddr：行情组播地址
            ///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”udp://224.0.0.1:17002” 
            ///@remark “udp”代表传输协议，“224.0.0.1”代表行情组播地址。”17001”代表组播端口号
            virtual void RegisterFpgaFront(const char* pMutilcastAddr) = 0;

            ///注册连接前置的本地地址
            ///@param localTcpAddr：连接前置的本地网卡地址，不设置时系统自动识别
            ///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
            ///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
            virtual void RegisterTcpLocalAddr(const char* localTcpAddr) = 0;

            ///注册接收组播的本地地址
            ///@param localAddr：接收组播的本地网卡地址，不设置时系统自动识别
            ///@remark 网络地址的格式为：“ipaddress”，如：”127.0.0.1” 
            ///@remark ““127.0.0.1”代表接收组播的本地网卡地址。
            virtual void RegisterUdpLocalAddr(const char* localAddr) = 0;

            ///注册使用efvi接收udp的网卡设备名字
            ///@param device：网卡设备名字 ，例如"ens1"
            virtual void RegisterEfviDevice(const char* device) = 0;

            ///注册回调接口
            ///@param pSpi 派生自回调接口类的实例
            virtual void RegisterSpi(IStoneMdSpi* pSpi) = 0;

            ///设置心跳超时时间。
            ///@param timeout 心跳超时时间(秒),最小心跳超时时间不小于10秒  
            virtual void SetHeartbeatTimeout(uint32_t timeout) = 0;

            ///用户登录请求
            ///@param pReqUserLogin 登录信息, UserID 与 Password 为必填字段，其他未选填字段 
            virtual int ReqUserLogin(CIStoneReqUserLogin* pReqUserLogin, int nRequestID) = 0;

            ///用户退出请求
            ///@param pReqUserLogin 退出信息, UserID 为必填字段，其他未选填字段 
            virtual int ReqUserLogout(CIStoneReqUserLogout* pReqUserLogout, int nRequestID) = 0;

            ///订阅股票深度行情
            ///@param tickType						股票类型, 多类型订阅可使用 ISTONE_TICKER_TYPE_SPOT | ISTONE_TICKER_TYPE_INDEX 方式订阅。
            ///        ISTONE_TICKER_TYPE_SPOT		<普通股票<债券<基金
            ///        ISTONE_TICKER_TYPE_INDEX		<指数
            ///        ISTONE_TICKER_TYPE_OPTION	<期权
            ///@param exchangeType					交易所类型， 多交易所可使用 ISTONE_EXCHANGE_SH | ISTONE_EXCHANGE_SZ 方式订阅。
            ///        ISTONE_EXCHANGE_SH			<上证
            ///        ISTONE_EXCHANGE_SZ			<深证
            virtual int SubAllMarketData(int tickType, int exchangeID, int nRequestID) = 0;

            ///退订股票深度行情
            ///@param tickType						股票类型, 多类型订阅可使用 ISTONE_TICKER_TYPE_SPOT | ISTONE_TICKER_TYPE_INDEX 方式订阅。
            ///        ISTONE_TICKER_TYPE_SPOT		<普通股票<债券<基金
            ///        ISTONE_TICKER_TYPE_INDEX		<指数
            ///        ISTONE_TICKER_TYPE_OPTION	<期权
            ///@param exchangeType					交易所类型， 多交易所可使用 ISTONE_EXCHANGE_SH | ISTONE_EXCHANGE_SZ 方式订阅。
            ///        ISTONE_EXCHANGE_SH			<上证
            ///        ISTONE_EXCHANGE_SZ			<深证
            virtual int UnSubAllMarketData(int tickType, int exchangeID, int nRequestID) = 0;

            ///订阅股票逐笔行情
            ///@param tickType						股票类型, 多类型订阅可使用 ISTONE_TICKER_TYPE_SPOT | ISTONE_TICKER_TYPE_INDEX 方式订阅。
            ///        ISTONE_TICKER_TYPE_SPOT		<普通股票<债券<基金
            ///        ISTONE_TICKER_TYPE_INDEX		<指数
            ///        ISTONE_TICKER_TYPE_OPTION	<期权
            ///@param exchangeType					交易所类型， 多交易所可使用 ISTONE_EXCHANGE_SH | ISTONE_EXCHANGE_SZ 方式订阅。
            ///        ISTONE_EXCHANGE_SH			<上证
            ///        ISTONE_EXCHANGE_SZ			<深证
            virtual int SubAllTickByTick(int exchangeID, int nRequestID) = 0;

            ///退订股票逐笔行情
            ///@param tickType						股票类型, 多类型订阅可使用 ISTONE_TICKER_TYPE_SPOT | ISTONE_TICKER_TYPE_INDEX 方式订阅。
            ///        ISTONE_TICKER_TYPE_SPOT		<普通股票<债券<基金
            ///        ISTONE_TICKER_TYPE_INDEX		<指数
            ///        ISTONE_TICKER_TYPE_OPTION	<期权
            ///@param exchangeType					交易所类型， 多交易所可使用 ISTONE_EXCHANGE_SH | ISTONE_EXCHANGE_SZ 方式订阅。
            ///        ISTONE_EXCHANGE_SH			<上证
            ///        ISTONE_EXCHANGE_SZ			<深证
            virtual int UnSubAllTickByTick(int exchangeID, int nRequestID) = 0;

            ///订阅合约行情
            ///@param ppInstrumentID	股票代码
            ///@param nCount			股票数量
            virtual int SubMarketData(char* ppInstrumentID[], int nCount, int nRequestID) = 0;

            ///退订合约行情
            ///@param ppInstrumentID	股票代码
            ///@param nCount			股票数量
            virtual int UnSubMarketData(char* ppInstrumentID[], int nCount, int nRequestID) = 0;

            ///订阅合约行情
            ///@param ppInstrumentID	股票代码
            ///@param nCount			股票数量
            virtual int SubTickByTick(char* ppInstrumentID[], int nCount, int nRequestID) = 0;

            ///退订合约行情
            ///@param ppInstrumentID	股票代码
            ///@param nCount			股票数量
            virtual int UnSubTickByTick(char* ppInstrumentID[], int nCount, int nRequestID) = 0;

            ///订阅所有股票订单簿
            ///@param exchangeID 交易所ID,目前仅支持深交所   1――上证  2――深证
            virtual int SubAllOrderBook(int exchangeID, int nRequestID) = 0;

            ///退订所有股票订单簿
            ///@param exchangeID 交易所ID,目前仅支持深交所   1――上证  2――深证
            virtual int UnSubAllOrderBook(int exchangeID, int nRequestID) = 0;

            ///订阅订单簿
            ///@param ppInstrumentID	股票代码
            ///@param nCount			股票数量
            virtual int SubOrderBook(char* ppInstrumentID[], int nCount, int nRequestID) = 0;

            ///退订订单簿
            ///@param ppInstrumentID	股票代码
            ///@param nCount			股票数量
            virtual int UnSubOrderBook(char* ppInstrumentID[], int nCount, int nRequestID) = 0;

        protected:
            ~IStoneMdApi() {};
        };
    }
}
