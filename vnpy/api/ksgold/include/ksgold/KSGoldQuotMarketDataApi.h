#ifndef __KSGOLDQUOTMARKETDATAAPI__H__
#define __KSGOLDQUOTMARKETDATAAPI__H__

#ifdef KSGOLDQUOTMARKETDATAAPI_EXPORTS
#define KSGOLDQUOTMARKETDATAAPI_API __declspec(dllexport)
#else
#ifdef WIN32
#define KSGOLDQUOTMARKETDATAAPI_API __declspec(dllimport)
#else 
#define KSGOLDQUOTMARKETDATAAPI_API
#endif
#endif

#include "KSGoldUserApiStructEx.h"

namespace KSGoldTradeAPI
{
class CKSGoldQuoSpi
{
public:
    ///当客户端与交易后台建立起通信连接时，该方法被调用。
    ///出现断线重连时，也会调用此方法
    ///@param nResult 返回结果
    ///        0x1001 建立连接
    ///        0x1002 断线重连成功
    virtual void OnFrontConnected(int nResult){};
    
    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    ///@param nReason 错误原因
    ///        0x1001 网络读失败
    ///        0x1002 网络写失败
    ///        0x2001 接收心跳超时
    ///        0x2002 发送心跳失败
    ///        0x2003 收到错误报文
    virtual void OnFrontDisconnected(int nReason){};
    
    ///登录请求响应
    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    
    ///登出请求响应
    virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    
    ///错误应答
    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    
    ///订阅行情应答
    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    
    ///取消订阅行情应答
    virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
    
    ///深度行情通知
    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {};

};

class KSGOLDQUOTMARKETDATAAPI_API CKSGoldQuotApi
{
public:
    ///创建QutoApi
    ///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
    ///@param bIsKlg 默认打开KLG日志开关
    ///@return 创建出的UserApi    
    static CKSGoldQuotApi *CreateGoldQutoApi(const char *pszFlowPath = "");
    
    ///删除接口对象本身
    ///@remark 不再使用本接口对象时,调用该函数删除接口对象
    virtual void Release() = 0;
    
    ///初始化
    ///@remark 初始化运行环境,只有调用后,接口才开始工作
    virtual bool Init() = 0;
    
    ///等待接口线程结束运行
    ///@return 线程退出代码
    virtual int Join() = 0;
    
    ///注册前置机网络地址
    ///@param pszFrontAddress：前置机网络地址。
    ///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
    ///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
    virtual void RegisterFront(char *pszFrontAddress) = 0;
    
    ///注册回调接口
    ///@param pSpi 派生自回调接口类的实例
    virtual void RegisterSpi(CKSGoldQuoSpi *pSpi) = 0;
    
    ///订阅行情。
    ///@param ppInstrumentID 合约ID  
    ///@param nCount 要订阅/退订行情的合约个数
    ///@remark 
    virtual int SubscribeMarketData(char *ppInstrumentID[], int nCount, int nRequestID) = 0;
    
    ///退订行情。
    ///@param ppInstrumentID 合约ID  
    ///@param nCount 要订阅/退订行情的合约个数
    ///@remark 
    virtual int UnSubscribeMarketData(char *ppInstrumentID[], int nCount, int nRequestID) = 0;
    
    ///用户登录请求
    virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
    
    ///登出请求
    virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID) = 0;
protected:
    ~CKSGoldQuotApi(){};
}; 

}  //end of KSGoldTradeAPI

#endif  //__KSGOLDQUOTMARKETDATAAPI__H__

