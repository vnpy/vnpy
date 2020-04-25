#ifndef _UFX_INTERFACE_H_
#define _UFX_INTERFACE_H_
#include "t2sdk_interface.h"
#include "python.h"
#include <thread>
#include <Windows.h> 
#include <queue>
#include <process.h>


class c_IF2Packer;
class c_IF2UnPacker;

struct CCallBackParam{
	int hSend;
	int iResult;
	int iCallFuncType; //回调方法
	IF2UnPacker* lpUnPacker;
	IBizMessage* lpBizMsg;
	char* sValue;
	CCallBackParam()
	{
		memset(this , 0, sizeof(CCallBackParam));
	}
	~CCallBackParam()
	{
		if (lpUnPacker)
		{
			lpUnPacker->Release();
			lpUnPacker = NULL;
		}
		if (lpBizMsg)
		{
			lpBizMsg->Release();
			lpBizMsg = NULL;
		}
		if (sValue)
		{
			free(sValue);
			sValue = NULL;
		}
	}
};
struct CSubCalBackPara
{
	char szTopicName[256];
	IBizMessage* lpBizMsg;
	CSubCalBackPara()
	{
		memset(this, 0, sizeof(CSubCalBackPara));
	}
	~CSubCalBackPara()
	{
		if (lpBizMsg)
		{
			lpBizMsg->Release();
			lpBizMsg = NULL;
		}
	}
	
};
class c_IF2Packer
{
private:
	IF2Packer* lpPacker;
public:
	c_IF2Packer();
	~c_IF2Packer();
	void SetBuffer(char* pBuf,int iBufSize,int iDataLen);
	void BeginPack();
	int NewDataset(char *szDatasetName, int iReturnCode );
	int AddField(char *szFieldName,char cFieldType='S',int iFieldWidth=255,int iFieldScale=4);
	int AddStr(char *szValue);
	int AddInt(int iValue);
	int AddDouble(double fValue);
	int AddChar(char* cValue);
	int AddRaw(char* lpBuff,int iLen);
	void EndPack();
	int* GetPackBuf();
	int GetPackLen();
	int GetPackBufSize();
	int GetVersion();
	void SetReturnCode(long dwRetCode);
    c_IF2UnPacker* UnPack();
	void FreeMem();
	void ClearValue();
	void BeginPackEx(char* szName = NULL);
	void ClearDataSet();
	IF2Packer* GetInstance();
	void Release();
};

class c_IF2UnPacker
{
private:
	IF2UnPacker* lpUnPacker;
	void * lpBuf;
	bool bRelease;
public:
	c_IF2UnPacker(char* lpBuffer,int iLen);
	c_IF2UnPacker(IF2UnPacker* lpUnPack);
	~c_IF2UnPacker();
	int GetVersion(void);
	int Open(char* lpBuffer,int iLen);
    int GetDatasetCount();
    int SetCurrentDatasetByIndex(int nIndex);
    int SetCurrentDataset(char *szDatasetName);
	char* GetPackBuf();
	int GetPackLen();
	int  GetRowCount();
    void  First();
    void  Last();
    void  Go(int nRow);
	char*  GetDatasetName();
	int  OpenAndCopy(char* lpBuffer,int iLen);
    char*  GetColTypeByName(char * columnName);
    int  GetColScaleByName(char * columnName);
    int  GetColWidthByName(char * columnName);
	IF2UnPacker* GetInstance();
	int GetColCount();
    char* GetColName(int column);
    char* GetColType(int column);
    int GetColScale(int column);
    int GetColWidth(int column);
    int  FindColIndex(char * columnName);
    char*  GetStrByIndex(int column);
    char* GetStr(char * columnName);
    char* GetCharByIndex(int column);
    char* GetChar(char * columnName);
    double GetDoubleByIndex( int column);
    double GetDouble(char * columnName);
    int  GetIntByIndex(int column);
    int GetInt(char * columnName);
    char*  GetRawByIndex(int column,int * lpRawLen);
    char*  GetRaw(char * columnName,int * lpRawLen);
    int  WasNull();
    void  Next();
    int  IsEOF();
    int  IsEmpty();
    void  Destroy();
	void Release();
};

class C_CConfigInterface
{
private:
	CConfigInterface* lpConfig;
public:
	C_CConfigInterface();
	~C_CConfigInterface();
    int Load( char *szFileName);
    int Save( char *szFileName);
    char * GetString( char *szSection,  char *szEntry,  char *szDefault);
    int GetInt( char *szSection,  char *szEntry, int iDefault);
    int SetString( char *szSection,  char *szEntry,  char *szValue);
    int SetInt( char *szSection,  char *szEntry, int iValue);
	CConfigInterface* GetInstance();
	void Release();
};

class c_IBizMessage
{
private:
	IBizMessage* lpBizMessage;
public:
	c_IBizMessage();
	~c_IBizMessage();
	void SetFunction(int nFUnctionNo);
	int GetFunction();
	void SetPacketType(int nPacketType);
	int GetPacketType();
	void SetBranchNo(int nBranchNo);
	int GetBranchNo();
	void SetSystemNo(int nSystemNo);
	int GetSystemNo();
	void SetSubSystemNo(int nSubSystemNo);
	int GetSubSystemNo();
	void SetSenderId(int nSenderId);
	int GetSenderId();
	void SetPacketId(int nPacketId);
	int GetPacketId();
	void SetErrorNo(int nErrorNo);
	int GetErrorNo();
	void SetErrorInfo(char* strErrorInfo);
	char* GetErrorInfo();
	void SetReturnCode(int nReturnCode);
	int GetReturnCode();
	void SetContent(char* lpContent,int iLen);
	char* GetContent(int& iLen);
	void SetIssueType(int nIssueType);
	int GetIssueType();
	void SetSequeceNo(int nSequeceNo);
	int GetSequeceNo();
	void SetKeyInfo(char* lpKeyData,int iLen);
	char* GetKeyInfo(int& iLen);
	void SetAppData(char* lpAppdata,int nAppLen);
	char* GetAppData(int& nAppLen);
	int	ChangeReq2AnsMessage();
	char* GetBuff(int& nBuffLen);
	int	SetBuff(char* lpBuff,int nBuffLen);
	void ReSet();
	IBizMessage* GetInstance();
	void Release();
};

class c_CSubscribeParamInterface
{
private:
	CSubscribeParamInterface* lpSubParam;
public:
	c_CSubscribeParamInterface();
	~c_CSubscribeParamInterface();
    void  SetTopicName(char* szName);
    void  SetAppData(char* lpData,int iLen);
    void  SetFilter(char* filterName,char* filterValue);
    void  SetReturnFiled(char* filedName);
    void  SetFromNow(int bFromNow);
    void  SetReplace(int bReplace);
    void  SetSendInterval(int nSendInterval);
    char*  GetTopicName();
    char*  GetAppData(int *iLen);
    char*  GetFilterNameByIndex(int index);
    char*  GetFilterValueByIndex(int index);
    char*  GetFilterValue(char*  fileName);
    int    GetFilterCount();
    char*  GetReturnFiled();
    int   GetFromNow();
    int   GetReplace();
    int    GetSendInterval();
	CSubscribeParamInterface* GetInstance();
	void Release();
};

class c_SubCallBack: public CSubCallbackInterface
{
private:
	PyObject* pModule;
	PyObject* pDict;
	PyObject* pClass;
	PyObject* pObject;
	PyObject* pOnReceiveFunc;
	char lpCallMould[50];
	char lpCallClass[50];
	PyGILState_STATE state;
	HANDLE EventHandle[2];
	std::thread* Thread;
	std::queue<CSubCalBackPara*>* DealMsgQueue;
	CRITICAL_SECTION* gMsgQueueSection;
	bool IsRun;
	void operator()() {
        run();
    }
	void run();
public:
	c_SubCallBack(char *lpMould,char *lpClass);
	c_SubCallBack();
	~c_SubCallBack();

	int initInstance();
	unsigned long FUNCTION_CALL_MODE QueryInterface(const char *iid, IKnown **ppv)
	{
		return 0;
	}

    unsigned long  FUNCTION_CALL_MODE AddRef()
	{
		return 0;
	}

    unsigned long  FUNCTION_CALL_MODE Release()
	{
		return 0;
	}
    void FUNCTION_CALL_MODE OnReceived(CSubscribeInterface *lpSub,int subscribeIndex, const void *lpData, int nLength,LPSUBSCRIBE_RECVDATA lpRecvData);
    void FUNCTION_CALL_MODE OnRecvTickMsg(CSubscribeInterface *lpSub,int subscribeIndex,const char* TickMsgInfo);
};

class c_CSubscribeInterface
{
private:
	CSubscribeInterface* lpSubscribe;
public:
	c_CSubscribeInterface(CSubscribeInterface* lpSub);
	~c_CSubscribeInterface();
    int SubscribeTopic(c_CSubscribeParamInterface* lpSubscribeParamInter ,unsigned int uiTimeout,c_IF2UnPacker** lppBizUnPack=NULL,c_IF2Packer* lpBizPack=NULL);
    int CancelSubscribeTopic(int subscribeIndex);
    int CancelSubscribeTopicEx(char* topicName,CFilterInterface* lpFilterInterface);
    void GetSubcribeTopic(c_IF2Packer* lpPack);
	void Release();
};

class c_CCallbackInterface: public CCallbackInterface
{
private:
	PyObject* pModuleT2;
	PyObject* pT2Class;
	PyObject* pModule;
	PyObject* pDict;
	PyObject* pClass;
	PyObject* pObject;
	//PyObject* pConnectFunc;
	//PyObject* pSafeConnectFunc;
	PyObject* pRegisterFunc;
	PyObject* pCloseFunc;
	//PyObject* pSendFunc;
	//PyObject* pReceivedBizFunc;
	//PyObject* pReceivedBizExFunc;
	PyObject* pReceivedBizMsgFunc;
	PyGILState_STATE state;
	char sMouldName[50];
	char sClassName[50];
	HANDLE EventHandle[2];
	std::thread* Thread;
	std::queue<CCallBackParam*>* DealMsgQueue;
	CRITICAL_SECTION* gMsgQueueSection;
	bool IsRun;
	void operator()() {
        run();
    }
	void run();
public:
	c_CCallbackInterface(char* sMould,char* sClass);
	c_CCallbackInterface();
	~c_CCallbackInterface();
	int InitInstance();
	unsigned long FUNCTION_CALL_MODE QueryInterface(const char *iid, IKnown **ppv)
	{
		return 0;
	}

    unsigned long  FUNCTION_CALL_MODE AddRef()
	{
		return 0;
	}

    unsigned long  FUNCTION_CALL_MODE Release()
	{
		return 0;
	}
    void FUNCTION_CALL_MODE OnConnect(CConnectionInterface *lpConnection);
    void FUNCTION_CALL_MODE OnSafeConnect(CConnectionInterface *lpConnection);
    void FUNCTION_CALL_MODE OnRegister(CConnectionInterface *lpConnection);
    void FUNCTION_CALL_MODE OnClose(CConnectionInterface *lpConnection);
    void FUNCTION_CALL_MODE OnSent(CConnectionInterface *lpConnection, int hSend, void *reserved1, void *reserved2, int nQueuingData);
    void FUNCTION_CALL_MODE Reserved1(void *a, void *b, void *c, void *d);
    void FUNCTION_CALL_MODE Reserved2(void *a, void *b, void *c, void *d);
    int FUNCTION_CALL_MODE  Reserved3();
    void FUNCTION_CALL_MODE Reserved4();
    void FUNCTION_CALL_MODE Reserved5();
    void FUNCTION_CALL_MODE Reserved6();
    void FUNCTION_CALL_MODE Reserved7();
    void FUNCTION_CALL_MODE OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnPackerOrStr, int nResult);
    void FUNCTION_CALL_MODE OnReceivedBizEx(CConnectionInterface *lpConnection, int hSend, LPRET_DATA lpRetData, const void *lpUnpackerOrStr, int nResult);
	void FUNCTION_CALL_MODE OnReceivedBizMsg(CConnectionInterface *lpConnection, int hSend, IBizMessage* lpMsg);
};

class c_CConnectionInterface
{
private:
	CConnectionInterface* lpConnect;
public:
	c_CConnectionInterface(C_CConfigInterface* lpConfig);
	~c_CConnectionInterface();
    int Connect(unsigned int uiTimeout);
    int Close();
    char * GetServerAddress(int *lpPort);
    int GetStatus();
    int GetServerLoad();
    char * GetErrorMsg(int nErrorCode);
    int GetConnectError();
	char* GetRealAddress();
	char* GetSelfAddress();
	char* GetSelfMac();
    c_CSubscribeInterface* NewSubscriber(c_SubCallBack *lpCallback,char* SubScribeName,int iTimeOut,
        int iInitRecvQLen=INIT_RECVQ_LEN,int iStepRecvQLen=STEP_RECVQ_LEN);
    c_IF2UnPacker* GetTopic(int byForce,int iTimeOut);
	char* GetMCLastError();
	int Create2BizMsg(c_CCallbackInterface *lpCallback);
	int SendBizMsg(c_IBizMessage* lpMsg,int nAsy = 0);
	int RecvBizMsg(int hSend, c_IBizMessage* lpMsg, unsigned uiTimeout = 1000, unsigned uiFlag = 0);
	char * GetLastAnsError(int bAsyError = 0);
	void Release();
};




#endif