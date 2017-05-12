//================================================================================== 
//下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 SHZDTRADELIB_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// SHZDTRADELIB_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
// 向少中 2013-03-22
//===================================================================================
#pragma once
#include "ShZdMessage.h"
#ifdef SHZDTRADELIB_EXPORTS
#define SHZDTRADELIB_API __declspec(dllexport)
#else
#define SHZDTRADELIB_API __declspec(dllimport)
#endif

#ifdef __cplusplus
//===================================================================================
// 对外导出的接口
//===================================================================================
//接收信息的虚类
class SHZDTRADELIB_API IShZdTradeOutLib
{
	public:
		virtual int OnReceiveTradeInfo(const CShZdMessage * re)=0;
		virtual int OnReceiveMarketInfo(const CShZdMessage * re)=0;
		virtual int OnReceiveErrorInfo(int errorCode,const char* re)=0;
};

typedef IShZdTradeOutLib* IShZdTradeOutLibHandler;
//发送信息的虚类
class  SHZDTRADELIB_API IShZdTradeInLib
{
	public:
		virtual void Release() = 0;	
		virtual int InitShZdServer()=0;//初始化服务器
		virtual int RegisterFront(const char *pszFrontAddress,int portNum)=0; //连接前置服务器 
		virtual int RegisterMarket(const char *pszMarketAddress,int portNum)=0;//连接行情服务器
		virtual int ShZdSendInfoToTrade(const CShZdMessage *send)=0; //向前置服务器发送交易请求	
		virtual int ShZdSendInfoToMarket(const CShZdMessage *send)=0;//向行情服务器发送行情请求
		virtual int RegisterOutLib(IShZdTradeOutLibHandler handler)=0;
};

typedef IShZdTradeInLib* ShZdTradeInLibHandle;
// 此类是从 ShZdTradeLib.dll 导出的
class SHZDTRADELIB_API CShZdTradeLib {
	public:			
};
#else  

#endif

#ifdef __cplusplus
#   define EXTERN_C     extern "C"
#else
#   define EXTERN_C
#endif

EXTERN_C SHZDTRADELIB_API ShZdTradeInLibHandle GetShZdTradeLib(void);
