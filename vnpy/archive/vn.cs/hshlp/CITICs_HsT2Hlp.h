#ifndef __CITICS_HSHLP_H__
#define __CITICS_HSHLP_H__

#ifdef WIN32
#ifdef CITICS_HSHLP_EXPORTS
#define CITICS_HSHLP_API __declspec(dllexport)
#else
#define CITICS_HSHLP_API __declspec(dllimport)
#endif

#define CITICSSTDCALL	__stdcall		/* ensure stcall calling convention on NT */
#else
#define CITICS_HSHLP_API
#define CITICSSTDCALL				    /* leave blank for other systems */
#endif

#define ERROR_MSG_SIZE 512
//////////////////////////////////////////////////////////////////////////

/**
* 同步业务调用
* 使用该标识调用业务时，系统处于阻塞状态直到返回应答信息或超时
*/
#define BIZCALL_SYNC  0

/**
* 异步业务调用
* 使用该标识调用业务时，系统立即返回而不等待应答信息。
* 需要调用QueueGetMsg获取应答结果信息 
*/
#define BIZCALL_ASYNC 1

/**
* 订阅消息中心发布的消息信息
* 标识该业务为消息订阅请求。如订阅成交推送数据、系统通知消息等
* 需要调用QueueGetMsg获取订阅的信息
*/
#define BIZCALL_SUBSCRIBE 3

typedef void *HSHLPCFGHANDLE;
typedef void *HSHLPHANDLE;
typedef void *HSHLPASYNCMSG;

#pragma pack(1)

/* 异步和订阅消息控制信息*/
typedef struct
{
	int nFlags;           // 位标识信息，0x0:正常消息, >0:系统状态消息
	int nFuncID;          // 异步请求功能号
	int nReqNo;           // 异步请求接受序号，根据该序号和功能号对请求和应答数据匹配
	int nIssueType;       // 发布消息类别
	int nErrorNo;         // 错误代码 
	HSHLPASYNCMSG HAsyncMsg;      // 消息句柄
	char szErrorInfo[ERROR_MSG_SIZE+1];     // 错误信息
}MSG_CTRL, *LPMSG_CTRL;

#pragma pack()


#ifdef __cplusplus
extern "C"
{
#endif
	
	// 初始化配置项，szConfigFile为空时则按系统默认值初始化，hConfig为出参
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_InitConfig(HSHLPCFGHANDLE* hConfig, const char* szConfigFile=NULL);

	// 加载配置文件项，可以加载多个不同的配置文件，返回不同的配置句柄。等同于InitConfig
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_LoadConfig(HSHLPCFGHANDLE* hConfig, const char* szConfigFile);
	
	// 重置服务器连接地址。格式：ip1:port1;ip2:port2;
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_ResetServer(HSHLPCFGHANDLE hConfig, const char* szAddr);

	// 根据配置句柄，初始化一个连接对象。
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_Init(HSHLPHANDLE* HlpHandle, HSHLPCFGHANDLE hConfig);
	// 释放连接句柄系统资源
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_Exit(HSHLPHANDLE HlpHandle);

	// 与服务器建立连接
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_ConnectServer(HSHLPHANDLE HlpHandle);
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_DisConnect(HSHLPHANDLE HlpHandle);

	// 提交业务请求，如果szParam参数为NULL，则认为是通过SetValue函数设置的请求参数 
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_BizCallAndCommit(HSHLPHANDLE HlpHandle, int iFuncID, const char* szParam=NULL, int nBizCallType=BIZCALL_SYNC, LPMSG_CTRL lpMsgCtrl=NULL);

	// 获取记录行、列数，返回值为行、列数
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_GetRowCount(HSHLPHANDLE HlpHandle, LPMSG_CTRL lpMsgCtrl=NULL);
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_GetColCount(HSHLPHANDLE HlpHandle, LPMSG_CTRL lpMsgCtrl=NULL);

	// 获取字段名称，序号以0为基数
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_GetColName(HSHLPHANDLE HlpHandle, int iColumn, char* szColName, LPMSG_CTRL lpMsgCtrl=NULL);

	// 获取下一行记录，第一次调用则首先打开结果集，并把第0行作为当前记录行
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_GetNextRow(HSHLPHANDLE HlpHandle, LPMSG_CTRL lpMsgCtrl=NULL);

	// 根据字段名称，获取字段值
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_GetValue(HSHLPHANDLE HlpHandle, const char* szKeyName, char* szValue, LPMSG_CTRL lpMsgCtrl=NULL);

	// 根据字段序号获取字段值，序号以0为基数
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_GetValueByIndex(HSHLPHANDLE HlpHandle, int iColumn, char* szValue, LPMSG_CTRL lpMsgCtrl=NULL);

	// 获取当前错误代码和信息
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_GetErrorMsg(HSHLPHANDLE HlpHandle, int* piErrorCode, char* szErrorMsg);


	/************************************************************************/
	// 另一种请求参数设置的方法，一个一个的设置。
	// 初始化请求参数
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_BeginParam(HSHLPHANDLE HlpHandle);
	// 设置每个请求参数字段名称和值
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_SetValue(HSHLPHANDLE HlpHandle, const char* szKeyName, const char* szValue);
	
	
	/************************************************************************/
	// 异步请求和消息订阅相关函数
	
	// 获取异步消息队列中的消息数量
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_QueueMsgCount(HSHLPHANDLE HlpHandle);
	
	// 从队列中读取一条消息，如果队列中没有数据，该函数会一直阻塞不返回，直到nWaitTime超时时间后才返回。
	// nWaitTime: 单位毫秒
	//       = 0: 立即返回；如果队列中有数据则返回Msg，且return值为 0，否则return值为-5(超时错误)
	//       =-1: 阻塞，直到队列中有数据获取到Msg 才返回。否则将永久阻塞等待。return值为 0，
	//       = 其它值：超时时间，如果队列中有数据则立即返回，否则等待time时间后返回。return值为 -5(超时错误)。
	// Return:  0: 队列中有数据且获取消息成功；
	//         -5: 超时错误，在设定的时间内队列中没有数据。
	// 	其它错误:	
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_QueueGetMsg(HSHLPHANDLE HlpHandle, LPMSG_CTRL lpMsgCtrl /*Out*/, int nWaitTime=0);
	
	// 处理完成或者不需要该消息时，应及时删除该消息，否则消息将占用大量内存。
	// 如果不删除有可能每次都Get到同一条消息
	CITICS_HSHLP_API int CITICSSTDCALL CITICs_HsHlp_QueueEraseMsg(HSHLPHANDLE HlpHandle, LPMSG_CTRL lpMsgCtrl /*In*/);
	

#ifdef __cplusplus
}
#endif


#endif 
