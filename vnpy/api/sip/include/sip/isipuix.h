/*!
\file isipuix.h
SIP实时行情业务层接口定义。
\update 2019/12/24
\author zork.com.cn
*/
#pragma once
#include"tshmarket.h"
#include"tshopmarket.h"
#include"tszmarket.h"
#include"tszopmarket.h"
#include"tcffexmarket.h"
#include"tczcemarket.h"
#include"tdcemarket.h"
#include"tshfemarket.h"
#include <stdint.h>
#ifdef _WIN32
#	pragma warning (disable : 4996)
#	pragma warning (disable : 4200)
#	ifdef LIB_ISIPUIX_EXPORT
#		define ISIPUIX_EXPORT __declspec(dllexport)
#	else
#		define ISIPUIX_EXPORT 
#	endif
#else
#	define ISIPUIX_EXPORT
#endif

///\brief 市场类型
///
///用于全市场订阅函数中指定市场类型。
enum MKtype {
    MKtype_SH_SZ = 0,				//沪深
    MKtype_SH = 1,					//沪市
    MKtype_SZ = 2,					//深市
    MKtype_CFE = 3,					//期货市场：中金所
    MKtype_CZCE = 4,				//期货市场：郑商所
    MKtype_DCE = 5,					//期货市场：大商所
    MKtype_SHFE = 6,				//期货市场：上期所
    MKtype_CFE_CZCE_DCE_SHFE = 7,	//期货市场：中金所,郑商所,大商所,上期所
    MKtype_SHOP = 8,				//上交所期权
    MKtype_SZOP = 11,				//深交所期权
    MKtype_All = 20					//全部市场
};

///\brief 数据类型
///
///用于订阅/退订回调函数中识别数据类型。
enum DATAtype {
    UnKnownData = -1,
    DepthMarketData = 0,	//L2快照行情
    MarketData = 1,			//L1快照行情
    IndexData = 2,			//指数快照行情
    StepTrade = 3,			//逐笔成交行情
    OrderQueue = 4,			//委托队列行情
    Kline = 5,				//分钟K线
    BaseInfo = 6,			//基础信息
    StepOrder = 7,			//逐笔委托行情
    Futures = 8,			//期货行情
    EtfExts = 9             //Etf扩展行情
};

#define MAXSSCTAGS 1000
///\brief 订阅标签错误信息通知
///
///用于订阅/退订回调函数中传递标签错误信息。
struct ErrMsg {
    int				channel;				//通道号,一个通道时为0,其他为1开始。
    int				errcode;				//错误码，为0代表成功，不为0则代表错误
    char			errstr[100];			//错误信息，错误码errcode对应的错误信息
    MKtype			mktype[MAXSSCTAGS];		//市场类型
    DATAtype		datatype[MAXSSCTAGS];	//订阅的数据类型
    unsigned int	usize;					//codes数组大小，代表订阅失败的标签数
    char			codes[MAXSSCTAGS][24];	//证券代码数组，用于存储订阅失败的证券代码
};

#ifndef _SIPV2_H
#define SIPE_ERRHANDLE			(-1)	///<内部句柄错误
#define SIPE_OK 				0 		///<成功 
#define SIPE_ERR 				1     	///<未知或一般错误 
#define SIPE_DISCONNECT			5		///<连接断开
#define SIPE_CONSVRFAIL			7		///<连接服务器失败，此时接口会执行自动重连
#define SIPE_NOTAG				124		///<订阅代码错误，无此编码
#endif
#define SIPE_NOCONFIG			18		///<无配置信息
#define SIPE_SOCKETINITERR		19		///<套接字初始化失败
#define SIPE_NOLOGININFO		20		///<没有登录相关信息或缺失某信息：IP地址、端口、登录账号、帐号密码
#define SIPE_NOMKTYPE			21		///<订阅市场类型错误，订阅代码无此市场类型

#define LOG_LEV_ERR 10
#define LOG_LEV_WRN 20
#define LOG_LEV_MSG 30
#define LOG_LEV_DBG 40

namespace api
{
    class CSipMdSpi//回调类,应用层实现
    {
    public:
        /*!
        \brief 日志回调
        \param level 日志级别; ERR=10, WRN=20,MSG=30, DBG=40
        \param source 来源，utf8编码
        \param slog 日志内容，utf8编码
        */
        virtual void OnLog(int32_t level, const char* source, const char* slog) {};
        /*!
        \brief 登录成功后回调，可在里面订阅
        \param chn 通道号,一个通道时为0,其他为1开始。
        */
        //virtual void OnLogin(int32_t chn, void* mdapi) {};

        /*!
        \brief 断开时回调
        \param chn 通道号。
        */
        virtual void OnDisconnect(int32_t chn) {};

        /*
        \brief 行情订阅回调
        \param errmsg 存储错误码errcode与错误信息errstr的结构体，errcode值为0代表成功，其余值为错误码，错误信息会存储在errstr字符串中
        \param errmsg 结构体中的channel、mktype与datatype则是用于识别证券代码codes订阅失败的对应通道、市场类型与数据类型。
        */
        virtual void OnSubscribe(ErrMsg* errmsg) {};

        /*
        \brief 行情退订回调
        \param errmsg 存储错误码errcode与错误信息errstr的结构体，errcode值为0代表成功，其余值为错误码，错误信息会存储在errstr字符串中
        \param errmsg 结构体中的channel、mktype与datatype则是用于识别证券代码codes退订失败的对应通道、市场类型与数据类型。
        */
        virtual void OnUnSubscribe(ErrMsg* errmsg) {};

        /*!
        \brief L2行情数据回调
        \param mktype 代表订阅的市场类型
        \param code 订阅的证券代码
        \param dataL2 L2行情结构体
        */
        virtual void OnDepthMarketData(MKtype mk_type, char* code, Stock_MarketData* dataL2) {};

        /*!
        \brief LF行情数据回调
        \param mktype 代表订阅的市场类型
        \param code 订阅的证券代码
        \param dataLF LF行情结构体
        */
        virtual void OnFastDepthMarketData(MKtype mk_type, char* code, T_SZ_StockMarketDataLF* dataLF) {};

        /*!
        \brief L1行情数据回调
        \param mktype 代表订阅的市场类型
        \param code 订阅的证券代码
        \param dataL1 L1行情结构体
        */
        virtual void OnMarketData(MKtype mk_type, char* code, StockMarketDataL1* dataL1) {};

        /*!
        \brief 指数行情回调
        \param mktype 代表订阅的市场类型
        \param code 订阅的证券代码
        \param stockindex 指数行情结构体
        */
        virtual void OnIndexData(MKtype mk_type, char* code, Stock_IndexData* stockindex) {};

        /*!
        \brief 上交所期权快照行情数据回调
        \param code 订阅的证券代码
        \param optiondata 上交所期权快照行情数据结构体
        */
        virtual void OnSHOption(char* code, t_SHOP_MarketData* optiondata) {};

        /*!
        \brief 深交所期权快照行情数据回调
        \param code 订阅的证券代码
        \param optiondata 深交所期权快照行情数据结构体
        */
        virtual void OnSZOption(char* code, t_SZOP_MarketData* optiondata) {};

        /*!
        \brief 委托队列行情数据回调
        \param mktype 代表订阅的市场类型
        \param code 订阅的证券代码
        \param orderqueue 委托队列行情数据结构体
        */
        virtual void OnOrderQueue(MKtype mk_type, char* code, StockOrderQueue* orderqueue) {};

        /*!
        \brief 上交所逐笔成交行情数据回调
        \param code 订阅的证券代码
        \param steptrade 上交所逐笔行情数据结构体
        */
        virtual void OnSHTrade(char* code, t_SH_StockStepTrade* steptrade) {};

        /*!
        \brief 深交所逐笔成交行情数据回调
        \param code 订阅的证券代码
        \param steptrade 深交所逐笔行情数据结构体
        */
        virtual void OnSZTrade(char* code, T_SZ_STEPTRADE* steptrade) {};

        /*!
        \brief 深交所逐笔委托行情数据回调
        \param code 订阅的证券代码
        \param steptrade 深交所逐笔行情数据结构体
        */
        virtual void OnSZOrder(char* code, T_SZ_STEPORDER* steporder) {};

        /*!
        \brief 上交所基础信息回调
        \param code 订阅的证券代码
        \param baseinfodata 上交所基础信息数据结构体
        */
        virtual void OnSHBaseInfo(char* code, T_SH_BaseInfo* baseinfodata) {};

        /*!
        \brief 深交所基础信息回调
        \param code 订阅的证券代码
        \param baseinfodata 深交所基础信息数据结构体
        */
        virtual void OnSZBaseInfo(char* code, t_SZ_BaseInfo* baseinfodata) {};

        /*!
        \brief 上交所期权基础信息回调
        \param code 订阅的证券代码
        \param baseinfodata 上交所基础信息数据结构体
        */
        virtual void OnSHOptionBaseInfo(char* code, t_SHOP_BaseInfo* baseinfodata) {};

        /*!
        \brief 深交所期权基础信息回调
        \param code 订阅的证券代码
        \param baseinfodata 深交所基础信息数据结构体
        */
        virtual void OnSZOptionBaseInfo(char* code, t_SZOP_BaseInfo* baseinfodata) {};

        /*!
        \brief 期货基础信息回调
        \param mktype 代表订阅的市场类型
        \param code 订阅的证券代码
        \param baseinfodata 期货基础信息数据结构体
        */
        virtual void OnFuturesBaseInfo(MKtype mk_type, char* code, T_Instrument_BaseInfo* baseinfodata) {};

        /*!
        \brief 分钟K线回调
        \param mktype 代表订阅的市场类型
        \param code 订阅的证券代码
        \param kline 分钟K线数据结构体
        */
        virtual void OnKline(MKtype mk_type, char* code, T_Kline* kline) {};

        /*!
        \brief 期货行情数据回调
        \param mktype 代表订阅的市场类型
        \param code 订阅的证券代码
        \param optiondata 期货行情数据结构体
        */
        virtual void OnFuturesData(MKtype mk_type, char* code, Futures_MarketData* futuresdata) {};

        /*!
        \brief ETF扩展行情数据回调
        \param mktype 代表订阅的市场类型
        \param code 订阅的证券代码
        \param optiondata ETF扩展行情数据结构体
        */
        virtual void OnEtfExtData(MKtype mk_type, char* code, T_ETFEXTENDS* etfextdata) {};
    public:

        //析构函数
        virtual ~CSipMdSpi() {};
    };
}

#ifndef _WIN32
#pragma GCC visibility push(default)
#endif
namespace api
{
    class ISIPUIX_EXPORT CSipMdApi //接口类, 接口层实现
    {
    public:
        /*!
        \brief 创建并返回由sipuix实现接口对象
        \param pdomsg 应用层实现的回调接口对象
        */
        static CSipMdApi* Register(CSipMdSpi* pdomsg);

        /*!
        \brief 初始化
        \param sjson, 用utf8字符串 json对象表达初始化参数。方便扩展
        \return 0表示成功，其他为错误码
        \remark Start之前调用设置所有参数。
        */
        virtual int32_t Initialize(const char* sjson) = 0;

        /*!
        \brief 启动
        \return 0表示成功，其他为错误码
        \remark Initialize成功后启动接口运行时。启动各种线程.
        */
        virtual int32_t Login() = 0;

        /*!
        \brief 停止
        \return 0表示成功，其他为错误码
        \remark Release之前调用,停止各种线程。
        */
        virtual int32_t Stop() = 0;

        /*!
        \brief 释放接口，删除接口对象。
        \remark Release会删除接口对象本身, Release之后接口就不能再用了。
        */
        virtual void Release() = 0; //释放接口

        /*!
        \brief 返回接口版本
        \return 返回0结束的字符串,格式"x.x.x"
        */
        virtual const char* GetVersion() = 0; //返回版本格式"x.x.x"

        /*!
        \brief 订阅指定L2快照行情
        \param mktype 代表订阅的市场类型
        \param tags, 需要订阅的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeDepthMarketData(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 订阅指定L1快照行情，包括期权
        \param mktype 代表订阅的市场类型
        \param tags, 需要订阅的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeMarketData(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 订阅指定指数快照行情
        \param mktype 代表订阅的市场类型
        \param tags, 需要订阅的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeIndexData(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 退订指定L2快照行情
        \param mktype 代表退订的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeDepthMarketData(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 退订指定L1快照行情，包括期权
        \param mktype 代表退订的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeMarketData(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 退订指定指数快照行情
        \param mktype 代表退订的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeIndexData(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 订阅指定委托队列行情
        \param mktype 代表订阅的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeOrderQueue(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 退订指定委托队列行情
        \param mktype 代表退订的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeOrderQueue(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 订阅指定逐笔成交行情
        \param mktype 代表订阅的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeStepTrade(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 退订指定逐笔成交行情
        \param mktype 代表退订的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeStepTrade(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 订阅指定逐笔委托行情
        \param mktype 代表订阅的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeStepOrder(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 退订指定逐笔委托行情
        \param mktype 代表退订的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeStepOrder(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 订阅指定基础信息
        \param mktype 代表订阅的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeBaseInfo(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 退订指定基础信息
        \param mktype 代表退订的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeBaseInfo(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 订阅指定分钟K线
        \param mktype 代表订阅的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeKline(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 退订指定分钟K线
        \param mktype 代表退订的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeKline(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 订阅指定期货行情数据
        \param mktype 代表订阅的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeFutures(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 退订指定期货行情数据
        \param mktype 代表退订的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeFutures(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 订阅指定ETF扩展行情数据
        \param mktype 代表订阅的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeEtfExt(MKtype mk_type, char* code[], unsigned int usize) = 0;

        /*!
        \brief 退订指定ETF扩展行情数据
        \param mktype 代表退订的市场类型
        \param tags, 需要退订的证券代码数组，数组每个元素以'\0'结尾
        \param usize, code数组中元素的个数
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeEtfExt(MKtype mk_type, char* code[], unsigned int usize) = 0;


        /*!
        \brief 订阅全市场L2快照行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeDepthMarketData(MKtype mk_type) = 0;

        /*!
        \brief 订阅全市场L1快照行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeMarketData(MKtype mk_type) = 0;

        /*!
        \brief 订阅全市场指数快照行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeIndexData(MKtype mk_type) = 0;

        /*!
        \brief 退订全市场L2快照行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeDepthMarketData(MKtype mk_type) = 0;

        /*!
        \brief 退订全市场L1快照行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeMarketData(MKtype mk_type) = 0;

        /*!
        \brief 退订全市场指数快照行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeIndexData(MKtype mk_type) = 0;

        /*!
        \brief 订阅全市场委托队列行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeOrderQueue(MKtype mk_type) = 0;

        /*!
        \brief 退订全市场委托队列行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeOrderQueue(MKtype mk_type) = 0;

        /*!
        \brief 订阅全市场逐笔成交行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeStepTrade(MKtype mk_type) = 0;

        /*!
        \brief 退订全市场逐笔成交行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeStepTrade(MKtype mk_type) = 0;

        /*!
        \brief 订阅全市场逐笔委托行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeStepOrder(MKtype mk_type) = 0;

        /*!
        \brief 退订全市场逐笔委托行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeStepOrder(MKtype mk_type) = 0;

        /*!
        \brief 订阅全市场基础信息
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeBaseInfo(MKtype mk_type) = 0;

        /*!
        \brief 退订全市场基础信息
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeBaseInfo(MKtype mk_type) = 0;

        /*!
        \brief 订阅全市场分钟K线
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeKline(MKtype mk_type) = 0;

        /*!
        \brief 退订全市场分钟K线
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeKline(MKtype mk_type) = 0;

        /*!
        \brief 订阅全市场期货行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeFutures(MKtype mk_type) = 0;

        /*!
        \brief 退订全市场期货行情
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeFutures(MKtype mk_type) = 0;

        /*!
        \brief 订阅全市场ETF扩展消息
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t SubscribeEtfExt(MKtype mk_type) = 0;

        /*!
        \brief 退订全市场ETF扩展消息
        \param mk_type, enum类型， 用于指定市场类型
        \return 0表示成功，其他为错误码
        */
        virtual int32_t UnSubscribeEtfExt(MKtype mk_type) = 0;
    };
}

#ifndef _WIN32
#pragma GCC visibility pop
#endif