/**
 * 版权所有(C)2012-2016, 大连飞创信息技术有限公司
 * 文件名称：DFITCSECMdApi.h
 * 文件说明：定义XSpeed行情API接口
 * 当前版本：1.6.40
 * 作者：XSpeed证券项目组
 * 发布日期：2016年10月
 */

#ifndef DFITCSECMDAPI_H_
#define DFITCSECMDAPI_H_


#include "DFITCSECApiStruct.h"


#ifdef WIN32
    #ifdef DFITCSECAPI_EXPORTS
        #define DFITCSEC_MD_API __declspec(dllexport)
    #else
        #define DFITCSEC_MD_API __declspec(dllimport)
    #endif//DFITCAPI_EXPORTS
#else
    #define DFITCSEC_MD_API
#endif//WIN32

    class DFITCSECMdSpi
    {
    public:
        DFITCSECMdSpi(){}

        /**
         * 网络连接正常响应
         */
        virtual void OnFrontConnected(){};

        /**
         * 网络连接不正常响应
         */
        virtual void OnFrontDisconnected(int nReason){};

        /**
         * SEC-消息通知
         */
        virtual void OnRtnNotice(DFITCSECRspNoticeField *pNotice) {};

        /**
         * ERR-错误应答
         * @param pRspInfo:若请求失败，返回错误信息地址
         */
        virtual void OnRspError(struct DFITCSECRspInfoField *pRspInfo) {}

        /**
         * STOCK-登录响应
         * @param pRspUserLogin:指针若非空,返回用户登录响应信息结构地址,表明登录请求成功
         * @param pRspInfo::指针若非空，返回错误信息地址，表明登录请求失败
         */
        virtual void OnRspStockUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo) {}

        /**
         * STOCK-登出响应
         * @param pRspUsrLogout:指针若非空,返回用户登出响应信息结构地址,表明登出请求成功
         * @param pRspInfo:指针若非空，返回错误信息地址，表明登出请求失败
         */
        virtual void OnRspStockUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo) {}

        /**
         * SOP-登录响应
         * @param pRspUserLogin:指针若非空,返回用户登录响应信息结构地址,表明登录请求成功
         * @param pRspInfo:指针若非空，返回错误信息地址，表明登录请求失败
         */
        virtual void OnRspSOPUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo) {}

        /**
         * SOP-登出响应
         * @param pRspUsrLogout:指针若非空,返回用户登出响应信息结构地址,表明登出请求成功
         * @param pRspInfo:指针若非空，返回错误信息地址，表明登出请求失败
         */
        virtual void OnRspSOPUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo) {}

        /**
         * FASL-登录响应
         * @param pRspUserLogin:指针若非空,返回用户登录响应信息结构地址,表明登录请求成功
         * @param pRspInfo:指针若非空，返回错误信息地址，表明登录请求失败
         */
        virtual void OnRspFASLUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo) {}

        /**
         * FASL-登出响应
         * @param pRspUsrLogout:指针若非空,返回用户登出响应信息结构地址,表明登出请求成功
         * @param pRspInfo:指针若非空，返回错误信息地址，表明登出请求失败
         */
        virtual void OnRspFASLUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo) {}

        /**
         * STOCK-行情订阅响应
         * @param pSpecificInstrument:指针若非空,返回用户指定合约行情订阅响应结构地址,表明指定合约行情订阅成功
         * @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情订阅失败
         */
        virtual void OnRspStockSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo) {}

        /**
         * STOCK-取消订阅行情响应
         * @param pSpecificInstrument:指针若非空,返回用户指定合约行情取消订阅响应结构地址,表明指定合约行情取消订阅成功
         * @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情取消订阅失败
         */
        virtual void OnRspStockUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo) {}

        /**
         * SOP-行情订阅响应
         * @param pSpecificInstrument:指针若非空,返回用户指定合约行情订阅响应结构地址,表明指定合约行情订阅成功
         * @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情订阅失败
         */
        virtual void OnRspSOPSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo) {}

        /**
         * SOP-取消订阅行情响应
         * @param pSpecificInstrument:指针若非空,返回用户指定合约行情取消订阅响应结构地址,表明指定合约行情取消订阅成功
         * @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情取消订阅失败
         */
        virtual void OnRspSOPUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo) {}

        /**
         * STOCK-行情推送响应
         * @param pMarketDataField:指针若非空,返回行情推送响应结构地址
         */
        virtual void OnStockMarketData(struct DFITCStockDepthMarketDataField * pMarketDataField) {}

        /**
         * SOP-行情推送响应
         * @param pMarketDataField:指针若非空,返回行情推送响应结构地址
         */
        virtual void OnSOPMarketData(struct DFITCSOPDepthMarketDataField * pMarketDataField) {}

        /**
         * STOCK-可用行情响应
         * @param pAvailableQuotInfo:指针若非空,返回可用的行情信息
         * @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情取消订阅失败
         * @param flag  为真是标示最后一条，为假时表示还有后续。
         */
        virtual void OnRspStockAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo,bool flag) {}

        /**
         * SOP-可用行情响应
         * @param pAvailableQuotInfo:指针若非空,返回可用的行情信息
         * @param pRspInfo:指针若非空，返回错误信息地址，表明指定合约行情取消订阅失败
         * @param flag  为真是标示最后一条，为假时表示还有后续。
         */
        virtual void OnRspSopAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo,bool flag) {}

        /**
         * 密码更新请求响应
         * @param pMDPasswordUpdate:指针若非空,返回用户行情密码响应信息结构地址,表明密码修改成功。
         * @param pRspInfo:指针若非空，返回错误信息地址，表明密码修改失败。
         */
        virtual void OnRspUserMDPasswordUpdate(struct DFITCSECRspMDPasswordUpdateField *pMDPasswordUpdate, struct DFITCSECRspInfoField * pRspInfo){}

    };//end of DFITCSECMdSpi

    class DFITCSEC_MD_API DFITCSECMdApi
    {
    public:
        /**
         * 创建行情API实例
         * @pszLogAddr: log所在的路径。如果pszLogAddr为NULL，则不生成log。
         * @return 创建出的UserApi
         */
        static DFITCSECMdApi * CreateDFITCMdApi(const char* pszLogAddr = "");

        /**
         * 进行一系列初始化工作:注册回调函数接口,连接行情前置。
         * @param pszSvrAddr:行情前置网络地址。
         *                  网络地址的格式为:"protocol://ipaddress:port",如"tcp://127.0.0.1:10915"
         *                  其中protocol的值为tcp或者udp,表示接收行情的方式;如果是udp接收行情数据,udp的端口将由API自行确定。
         *                  ipaddress表示行情前置的IP,port表示行情前置的端口
         * @param *pSpi:类DFITCMdSpi对象实例
         * @return 0 - 成功;-1 - 失败。
         */
        virtual int Init(const char * pszSvrAddr, DFITCSECMdSpi * pSpi) = 0;

        /**
         * 删除接口对象
         */
        virtual void Release() = 0;

        /**
         * STOCK-订阅行情请求
         * @param ppInstrumentID[]:指针数组，每个指针指向一个合约
         * @param nCount:合约个数
         * @return 0表示成功，-1表示失败
         */
        virtual int SubscribeStockMarketData(char * ppInstrumentID[], int nCount, int nRequestID) = 0;

        /**
         * STOCK-取消订阅行情请求
         * @param ppInstrumentID[]:指针数组，每个指针指向一个合约
         * @param nCount:合约个数
         * @return 0表示成功，-1表示失败
         */
        virtual int UnSubscribeStockMarketData(char * ppInstrumentID[], int nCount, int nRequestID) = 0;

        /**
         * SOP-订阅行情请求
         * @param ppInstrumentID[]:指针数组，每个指针指向一个合约
         * @param nCount:合约个数
         * @return 0表示成功，-1表示失败
         */
        virtual int SubscribeSOPMarketData(char * ppInstrumentID[], int nCount, int nRequestID) = 0;

        /**
         * SOP-取消订阅行情请求
         * @param ppInstrumentID[]:指针数组，每个指针指向一个合约
         * @param nCount:合约个数
         * @return 0表示成功，-1表示失败
         */
        virtual int UnSubscribeSOPMarketData(char * ppInstrumentID[], int nCount, int nRequestID) = 0;

        /**
         * STOCK-登录请求
         * @param pReqUserLoginField:指向用户登录请求结构的地址
         * @return 0表示成功，-1表示失败
         */
        virtual int ReqStockUserLogin(struct DFITCSECReqUserLoginField * pReqUserLoginField) = 0;

        /**
         * STOCK-登出请求
         * @param pReqUserLogoutField指向用户登录请求结构的地址
         * @return 0表示成功，-1表示失败
         */
        virtual int ReqStockUserLogout(struct DFITCSECReqUserLogoutField * pReqUserLogoutField) = 0;

        /**
         * SOP-登录请求
         * @param ReqStockUserLogin:指向用户登录请求结构的地址
         * @return 0表示成功，-1表示失败
         */
        virtual int ReqSOPUserLogin(struct DFITCSECReqUserLoginField * pReqUserLoginField) = 0;

        /**
         * FASL-登录请求
         * @param ReqStockUserLogin:指向用户登录请求结构的地址
         * @return 0表示成功，-1表示失败
         */
        virtual int ReqFASLUserLogin(struct DFITCSECReqUserLoginField * pReqUserLoginField) = 0;

        /**
         * SOP-登出请求
         * @param pReqUserLogoutField:指向用户登录请出结构的地址
         * @return 0表示成功，-1表示失败
         */
        virtual int ReqSOPUserLogout(struct DFITCSECReqUserLogoutField * pReqUserLogoutField) = 0;

        /**
         * FASL-登出请求
         * @param pReqUserLogoutField:指向用户登录请出结构的地址
         * @return 0表示成功，-1表示失败
         */
        virtual int ReqFASLUserLogout(struct DFITCSECReqUserLogoutField * pReqUserLogoutField) = 0;

        /**
         * STOCK-可用行情信息查询请求
         * @param pReqQuotQryField:可用行情请求请求结构的地址
         * @return 0表示成功，-1表示失败
         */
        virtual int ReqStockAvailableQuotQry(struct  APISTRUCT DFITCReqQuotQryField * pReqQuotQryField) = 0;

        /**
         * SOP-可用行情信息查询请求
         * @param pReqQuotQryField:可用行情请求请求结构的地址
         * @return 0表示成功，-1表示失败
         */
        virtual int ReqSopAvailableQuotQry(struct  APISTRUCT DFITCReqQuotQryField * pReqQuotQryField) = 0;

        /**
         * 密码更新请求
         * @param pReqMDPasswordUpdate:指向用户密码更新请求结构的地址
         * @return 0表示请求发送成功，其他值表示请求发送失败，具体错误请对照error.xml
         */
        virtual int ReqUserMDPasswordUpdate(struct DFITCSECReqMDPasswordUpdateField *pReqMDPasswordUpdate) = 0;

    protected:
        virtual ~DFITCSECMdApi() = 0;

    };//end of DFITCSECMdApi

#endif//DFITCSECMDAPI_H_
