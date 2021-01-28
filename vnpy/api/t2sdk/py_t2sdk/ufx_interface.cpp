#include "ufx_interface.h"

CRITICAL_SECTION* g_MsgQueueSection = NULL;
int iTreadNum = 0;
int GetThreadNum()
{
	if(g_MsgQueueSection == NULL)
	{
      g_MsgQueueSection = new CRITICAL_SECTION;
	  InitializeCriticalSection(g_MsgQueueSection);
	}
	EnterCriticalSection(g_MsgQueueSection);
	iTreadNum++;
	LeaveCriticalSection(g_MsgQueueSection);
	return iTreadNum;
}

c_IF2Packer::c_IF2Packer()
{
	lpPacker = NewPacker(2);
	lpPacker->AddRef();
}

c_IF2Packer::~c_IF2Packer()
{
	
}

void c_IF2Packer::SetBuffer(char* pBuf,int iBufSize,int iDataLen)
{
	lpPacker->SetBuffer(pBuf,iBufSize,iDataLen);
}

void c_IF2Packer::BeginPack(void)
{
	lpPacker->BeginPack();
}

int c_IF2Packer::NewDataset(char *szDatasetName, int iReturnCode )
{
	return lpPacker->NewDataset(szDatasetName,iReturnCode);
}

int c_IF2Packer::AddField(char *szFieldName,char cFieldType,int iFieldWidth,int iFieldScale)
{
	return lpPacker->AddField(szFieldName,cFieldType,iFieldWidth,iFieldScale);
}

int c_IF2Packer::AddStr(char *szValue)
{
	return lpPacker->AddStr(szValue);
}

int c_IF2Packer::AddInt(int iValue)
{
	return lpPacker->AddInt(iValue);
}

int c_IF2Packer::AddDouble(double fValue)
{
	return lpPacker->AddDouble(fValue);
}

int c_IF2Packer::AddChar(char* cValue)
{
	return lpPacker->AddDouble(cValue[0]);
}

int c_IF2Packer::AddRaw(char* lpBuff,int iLen)
{
	return lpPacker->AddRaw(lpBuff,iLen);
}

void c_IF2Packer::EndPack()
{
	lpPacker->EndPack();
}

int* c_IF2Packer::GetPackBuf(void)
{
	char* lpBuff = (char*)(lpPacker->GetPackBuf());
	int iLength = lpPacker->GetPackLen();
	int* sValue = new int[iLength];
	for(int i=0;i<iLength;i++)
		sValue[i] =lpBuff[i]; 
	return sValue;
}

int c_IF2Packer::GetPackLen(void)
{
	return lpPacker->GetPackLen();
}

int c_IF2Packer::GetPackBufSize(void)
{
	return lpPacker->GetPackBufSize();
}

int c_IF2Packer::GetVersion(void)
{
	return lpPacker->GetVersion();
}

void c_IF2Packer::SetReturnCode(long dwRetCode)
{
	return lpPacker->SetReturnCode(dwRetCode);
}

c_IF2UnPacker* c_IF2Packer::UnPack(void)
{
	IF2UnPacker* lpUnpacker = lpPacker->UnPack();
	c_IF2UnPacker* lpcUnpacker = new c_IF2UnPacker(lpUnpacker);
	return lpcUnpacker;

}

void c_IF2Packer::FreeMem()
{
	void* lpBuff = lpPacker->GetPackBuf();
	return lpPacker->FreeMem(lpBuff);
}

void c_IF2Packer::ClearValue()
{
	return lpPacker->ClearValue();
}

void c_IF2Packer::BeginPackEx(char* szName)
{
	return lpPacker->BeginPackEx(szName);
}

void c_IF2Packer::ClearDataSet()
{
	return lpPacker->ClearDataSet();
}

IF2Packer* c_IF2Packer::GetInstance()
{
	return lpPacker;
}

void c_IF2Packer::Release()
{
	lpPacker->Release();
}

c_IF2UnPacker::c_IF2UnPacker(char* lpBuffer,int iLen)
{
	//printf("初始化,%d\n",iLen);
	lpBuf = malloc(iLen);
	memcpy(lpBuf,(void*)lpBuffer,iLen);
	lpUnPacker = NewUnPacker(lpBuf,iLen);
	if(lpUnPacker == NULL)
		printf("初始化失败,%d\n",iLen);
	lpUnPacker->AddRef();
	bRelease = true;
}

c_IF2UnPacker::c_IF2UnPacker(IF2UnPacker* lpUnPack)
{
	lpBuf = NULL;
	lpUnPacker = lpUnPack;
	bRelease = false;
}

c_IF2UnPacker::~c_IF2UnPacker()
{

}

int c_IF2UnPacker::GetVersion(void)
{
	return lpUnPacker->GetVersion();
}

int c_IF2UnPacker::Open(char* lpBuffer,int iLen)
{
	return lpUnPacker->OpenAndCopy(lpBuffer,iLen);
}

int c_IF2UnPacker::GetDatasetCount()
{
	return lpUnPacker->GetDatasetCount();
}

int c_IF2UnPacker::SetCurrentDatasetByIndex(int nIndex)
{
	return lpUnPacker->SetCurrentDatasetByIndex(nIndex);
}

int c_IF2UnPacker::SetCurrentDataset(char *szDatasetName)
{
	return lpUnPacker->SetCurrentDataset(szDatasetName);
}

char* c_IF2UnPacker::GetPackBuf(void)
{
	return (char*)(lpUnPacker->GetPackBuf());
}


int c_IF2UnPacker::GetPackLen()
{
	return lpUnPacker->GetPackLen();
}

int c_IF2UnPacker::GetRowCount(void)
{
	return lpUnPacker->GetRowCount();
}

void c_IF2UnPacker::First()
{
	lpUnPacker->First();
}

void  c_IF2UnPacker::Last()
{
	lpUnPacker->Last();
}

void c_IF2UnPacker::Go(int nRow)
{
	lpUnPacker->Go(nRow);
}

char* c_IF2UnPacker::GetDatasetName()
{
	return (char*)(lpUnPacker->GetDatasetName());
}

int  c_IF2UnPacker::OpenAndCopy(char* lpBuffer,int iLen)
{
	return lpUnPacker->OpenAndCopy(lpBuffer,iLen);
}

char*  c_IF2UnPacker::GetColTypeByName(char * columnName)
{
	char cType = lpUnPacker->GetColTypeByName(columnName);
	char* sType=new char[2];
    sType[0]=cType; 
	sType[1]='\0';
	return sType;
}

int  c_IF2UnPacker::GetColScaleByName(char * columnName)
{
	return lpUnPacker->GetColScaleByName(columnName);
}

int  c_IF2UnPacker::GetColWidthByName(char * columnName)
{
	return lpUnPacker->GetColWidthByName(columnName);
}

IF2UnPacker* c_IF2UnPacker::GetInstance()
{
	return lpUnPacker;
}

int c_IF2UnPacker::GetColCount()
{
	return lpUnPacker->GetColCount();
}

char* c_IF2UnPacker::GetColName(int column)
{
	return (char*)lpUnPacker->GetColName(column);
}
char* c_IF2UnPacker::GetColType(int column)
{
	char cType = lpUnPacker->GetColType(column);
	char* sType=new char[2];
    sType[0]=cType; 
	sType[1]='\0';
	return sType;
}
int c_IF2UnPacker::GetColScale(int column)
{
	return lpUnPacker->GetColScale(column);
}
int c_IF2UnPacker::GetColWidth(int column)
{
	return lpUnPacker->GetColWidth(column);
}
int c_IF2UnPacker::FindColIndex(char * columnName)
{
	return lpUnPacker->FindColIndex(columnName);
}
char*  c_IF2UnPacker::GetStrByIndex(int column)
{
	return (char*)lpUnPacker->GetStrByIndex(column);
}
char* c_IF2UnPacker::GetStr(char * columnName)
{
	return (char*)lpUnPacker->GetStr(columnName);
}
char* c_IF2UnPacker::GetCharByIndex(int column)
{
	char cType = lpUnPacker->GetCharByIndex(column);
	char* sType=new char[2];
    sType[0]=cType; 
	sType[1]='\0';
	return sType;
}
char* c_IF2UnPacker::GetChar(char * columnName)
{
	char cType = lpUnPacker->GetChar(columnName);
	char* sType=new char[2];
    sType[0]=cType; 
	sType[1]='\0';
	return sType;
}
double c_IF2UnPacker::GetDoubleByIndex(int column)
{
	return lpUnPacker->GetDoubleByIndex(column);
}
double c_IF2UnPacker::GetDouble(char * columnName)
{
	return lpUnPacker->GetDouble(columnName);
}
int  c_IF2UnPacker::GetIntByIndex(int column)
{
	return lpUnPacker->GetIntByIndex(column);
}
int c_IF2UnPacker::GetInt(char* columnName)
{
	return lpUnPacker->GetInt(columnName);
}
char*  c_IF2UnPacker::GetRawByIndex(int column,int* lpRawLen)
{
	return (char*)lpUnPacker->GetRawByIndex(column,lpRawLen);
}
char*  c_IF2UnPacker::GetRaw(char* columnName,int* lpRawLen)
{
	return (char*)lpUnPacker->GetRaw(columnName,lpRawLen);
}
int  c_IF2UnPacker::WasNull()
{
	return lpUnPacker->WasNull();
}
void c_IF2UnPacker::Next()
{
	lpUnPacker->Next();
}
int  c_IF2UnPacker::IsEOF()
{
	return lpUnPacker->IsEOF();
}
int  c_IF2UnPacker::IsEmpty()
{
	return lpUnPacker->IsEmpty();
}
void  c_IF2UnPacker::Destroy()
{
	lpUnPacker->Destroy();
}

void c_IF2UnPacker::Release()
{
	if (lpUnPacker && bRelease)
	{
		lpUnPacker->Release();
		lpUnPacker = NULL;
	}
	if (lpBuf)
	{
		free(lpBuf);
		lpBuf = NULL;
	}
}

C_CConfigInterface::C_CConfigInterface()
{
	lpConfig = NewConfig();
	lpConfig->AddRef();
}

C_CConfigInterface::~C_CConfigInterface()
{
	
}

int C_CConfigInterface::Load( char *szFileName)
{
	return lpConfig->Load(szFileName);
}

int C_CConfigInterface::Save( char *szFileName)
{
	return lpConfig->Save(szFileName);
}

char* C_CConfigInterface::GetString(char *szSection,char *szEntry,char *szDefault)
{
	return (char*)lpConfig->GetString(szSection,szEntry,szDefault);
}

int C_CConfigInterface::GetInt(char *szSection,char *szEntry, int iDefault)
{
	return lpConfig->GetInt(szSection,szEntry,iDefault);
}

int C_CConfigInterface::SetString( char *szSection,  char *szEntry,  char *szValue)
{
	return lpConfig->SetString(szSection,szEntry,szValue);
}

int C_CConfigInterface::SetInt( char *szSection,  char *szEntry, int iValue)
{
  return lpConfig->SetInt(szSection,szEntry,iValue);
}

CConfigInterface* C_CConfigInterface::GetInstance()
{
	return lpConfig;
}

void C_CConfigInterface::Release()
{
	lpConfig->Release();
}

c_IBizMessage::c_IBizMessage()
{
	lpBizMessage = NewBizMessage();
	lpBizMessage->AddRef();
}

c_IBizMessage::~c_IBizMessage()
{

}

void c_IBizMessage::SetFunction(int nFUnctionNo)
{
	lpBizMessage->SetFunction(nFUnctionNo);
}

int c_IBizMessage::GetFunction()
{
	return lpBizMessage->GetFunction();
}

void c_IBizMessage::SetPacketType(int nPacketType)
{
	lpBizMessage->SetPacketType(nPacketType);
}

int c_IBizMessage::GetPacketType()
{
	return lpBizMessage->GetPacketType();
}

void c_IBizMessage::SetBranchNo(int nBranchNo)
{
	return lpBizMessage->SetBranchNo(nBranchNo);
}

int c_IBizMessage::GetBranchNo()
{
	return lpBizMessage->GetBranchNo();
}

void c_IBizMessage::SetSystemNo(int nSystemNo)
{
	lpBizMessage->SetSystemNo(nSystemNo);
}

int c_IBizMessage::GetSystemNo()
{
	return lpBizMessage->GetSystemNo();
}

void c_IBizMessage::SetSubSystemNo(int nSubSystemNo)
{
	return lpBizMessage->SetSubSystemNo(nSubSystemNo);
}

int c_IBizMessage::GetSubSystemNo()
{
	return lpBizMessage->GetSubSystemNo();
}

void c_IBizMessage::SetSenderId(int nSenderId)
{
	lpBizMessage->SetSenderId(nSenderId);
}

int c_IBizMessage::GetSenderId()
{
	return lpBizMessage->GetSenderId();
}

void c_IBizMessage::SetPacketId(int nPacketId)
{
	lpBizMessage->SetPacketId(nPacketId);
}

int c_IBizMessage::GetPacketId()
{
	return lpBizMessage->GetPacketId();
}

void c_IBizMessage::SetErrorNo(int nErrorNo)
{
	lpBizMessage->SetErrorNo(nErrorNo);
}

int c_IBizMessage::GetErrorNo()
{
	return lpBizMessage->GetErrorNo();
}

void c_IBizMessage::SetErrorInfo(char* strErrorInfo)
{
	lpBizMessage->SetErrorInfo(strErrorInfo);
}

char* c_IBizMessage::GetErrorInfo()
{
	return (char*)(lpBizMessage->GetErrorInfo());
}

void c_IBizMessage::SetReturnCode(int nReturnCode)
{
	lpBizMessage->SetReturnCode(nReturnCode);
}

int c_IBizMessage::GetReturnCode()
{
	return lpBizMessage->GetReturnCode();
}

void c_IBizMessage::SetContent(char* lpContent,int iLen)
{
	lpBizMessage->SetContent(lpContent,iLen);
}

char* c_IBizMessage::GetContent(int& iLen)
{
	return (char*)(lpBizMessage->GetContent(iLen));
}

void c_IBizMessage::SetIssueType(int nIssueType)
{
	lpBizMessage->SetIssueType(nIssueType);
}

int c_IBizMessage::GetIssueType()
{
	return lpBizMessage->GetIssueType();
}

void c_IBizMessage::SetSequeceNo(int nSequeceNo)
{
	return lpBizMessage->SetSequeceNo(nSequeceNo);
}

int c_IBizMessage::GetSequeceNo()
{
	return lpBizMessage->GetSequeceNo();
}

void c_IBizMessage::SetKeyInfo(char* lpKeyData,int iLen)
{
	lpBizMessage->SetKeyInfo(lpKeyData,iLen);
}

char* c_IBizMessage::GetKeyInfo(int& iLen)
{
	return (char*)lpBizMessage->GetKeyInfo(iLen);
}

void c_IBizMessage::SetAppData(char* lpAppdata,int nAppLen)
{
	lpBizMessage->SetAppData(lpAppdata,nAppLen);
}

char* c_IBizMessage::GetAppData(int& nAppLen)
{
	return (char*)lpBizMessage->GetAppData(nAppLen);
}

int	c_IBizMessage::ChangeReq2AnsMessage()
{
	return lpBizMessage->ChangeReq2AnsMessage();
}

char* c_IBizMessage::GetBuff(int& nBuffLen)
{
	return (char*)lpBizMessage->GetBuff(nBuffLen);
}

int	c_IBizMessage::SetBuff(char* lpBuff,int nBuffLen)
{
	return lpBizMessage->SetBuff(lpBuff,nBuffLen);
}

void c_IBizMessage::ReSet()
{
	lpBizMessage->ReSet();
}

IBizMessage* c_IBizMessage::GetInstance()
{
	return lpBizMessage;
}

void c_IBizMessage::Release()
{
	lpBizMessage->Release();
}

c_CSubscribeParamInterface::c_CSubscribeParamInterface()
{
	lpSubParam = NewSubscribeParam();
	lpSubParam->AddRef();
}

c_CSubscribeParamInterface::~c_CSubscribeParamInterface()
{

}

void  c_CSubscribeParamInterface::SetTopicName(char* szName)
{
	lpSubParam->SetTopicName(szName);
}

void  c_CSubscribeParamInterface::SetAppData(char* lpData,int iLen)
{
	lpSubParam->SetAppData(lpData,iLen);
}

void  c_CSubscribeParamInterface::SetFilter(char* filterName,char* filterValue)
{
	lpSubParam->SetFilter(filterName,filterValue);
}

void  c_CSubscribeParamInterface::SetReturnFiled(char* filedName)
{
	lpSubParam->SetReturnFiled(filedName);
}

void  c_CSubscribeParamInterface::SetFromNow(int bFromNow)
{
	bool bFN = false;
	if(bFromNow > 0)
		bFN = true;
	lpSubParam->SetFromNow(bFN);
}

void  c_CSubscribeParamInterface::SetReplace(int bReplace)
{
	bool bRe = false;
	if(bReplace > 0)
		bRe = true;
	lpSubParam->SetFromNow(bRe);
}

void  c_CSubscribeParamInterface::SetSendInterval(int nSendInterval)
{
	lpSubParam->SetSendInterval(nSendInterval);
}

char* c_CSubscribeParamInterface::GetTopicName()
{
	return (char*)lpSubParam->GetTopicName();
}

char*  c_CSubscribeParamInterface::GetAppData(int *iLen)
{
	return (char*)lpSubParam->GetAppData(iLen);
}

char*  c_CSubscribeParamInterface::GetFilterNameByIndex(int index)
{
	return (char*)lpSubParam->GetFilterNameByIndex(index);
}

char*  c_CSubscribeParamInterface::GetFilterValueByIndex(int index)
{
	return (char*)lpSubParam->GetFilterValueByIndex(index);
}

char*  c_CSubscribeParamInterface::GetFilterValue(char*  fileName)
{
	return (char*)lpSubParam->GetFilterValue(fileName);
}

int c_CSubscribeParamInterface::GetFilterCount()
{
	return lpSubParam->GetFilterCount();
}

char* c_CSubscribeParamInterface::GetReturnFiled()
{
	return (char*)lpSubParam->GetReturnFiled();
}

int  c_CSubscribeParamInterface::GetFromNow()
{
	return lpSubParam->GetFromNow();
}

int  c_CSubscribeParamInterface::GetReplace()
{
	return lpSubParam->GetReplace();
}

int c_CSubscribeParamInterface::GetSendInterval()
{
	return lpSubParam->GetSendInterval();
}

CSubscribeParamInterface* c_CSubscribeParamInterface::GetInstance()
{
	return lpSubParam;
}

void c_CSubscribeParamInterface::Release()
{
	lpSubParam->Release();
}

c_SubCallBack::c_SubCallBack(char *lpMould,char *lpClass)
{
	strcpy_s(lpCallMould,lpMould);
	strcpy_s(lpCallClass,lpClass);
	DealMsgQueue = new std::queue<CSubCalBackPara*>();
	IsRun=true;
	for (int i = 0; i < 2; i++)
    {
	  char threadName[12] = {0};
	  sprintf_s(threadName,"sub_thread%d",GetThreadNum());
	  EventHandle[i] = CreateEvent(NULL, FALSE, FALSE, (LPCTSTR)threadName);
    }
	gMsgQueueSection = new CRITICAL_SECTION;
	InitializeCriticalSection(gMsgQueueSection);
}

c_SubCallBack::~c_SubCallBack()
{
	IsRun=false;
	SetEvent(EventHandle[1]);
	Py_Finalize();
}

c_SubCallBack::c_SubCallBack()
{
	if (!Py_IsInitialized())
	{
		Py_Initialize();
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('./')");
	}
}

int c_SubCallBack::initInstance()
{
	pModule =  NULL;
	if (!Py_IsInitialized())
	{
		Py_Initialize();
		PyEval_InitThreads();
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('./')");
	}
	pModule = PyImport_ImportModule(lpCallMould);
	if (!pModule) 
	{
		printf("Can`t open python file!\n");
		return -1;
	}
	pDict = PyModule_GetDict(pModule);
	if(!pDict)
	{
		printf("Can`t open Get Dict!\n");
  		return -1;
	}
	pClass  = PyObject_GetAttrString(pModule, lpCallClass);
	if(!pClass)
	{
		printf("Can`t open Get Class!\n");
		return -1;
	}
	pObject = PyEval_CallObject(pClass, NULL);
	if(!pObject)
	{
		printf("%s Class init failed!\n",lpCallClass);
		return -1;
	}
	pOnReceiveFunc=PyObject_GetAttrString(pObject, "OnReceived");
	if(!pOnReceiveFunc)
	{
		printf("OnReceived function init failed!\n");
		return -1;
	}
	Thread = new std::thread(&c_SubCallBack::run,this);
	return 0;
}

void c_SubCallBack::run()
{
	while(IsRun)
	{
		CSubCalBackPara* lpMsg;
		int index = WaitForMultipleObjects(2, EventHandle, FALSE, INFINITE);
		PyObject* list = NULL;
		state = PyGILState_Ensure();
		Py_INCREF(pClass);
		switch(index)
		{
			case WAIT_OBJECT_0:
				EnterCriticalSection(gMsgQueueSection);
				while( DealMsgQueue->size() > 0)
				{
					lpMsg = DealMsgQueue->front();
					DealMsgQueue->pop();
					LeaveCriticalSection(gMsgQueueSection);
					int iLenght;
					char* lpBuff = (char*)(lpMsg->lpBizMsg->GetBuff(iLenght));
					list = PyList_New(0);
					for (int i = 0; i < iLenght; i++)
					{
						int iTemp = lpBuff[i];
						PyList_Append(list, Py_BuildValue("i", iTemp));
					}
					char * lpTopic = lpMsg->szTopicName;
					PyObject* call = PyObject_CallFunction(pOnReceiveFunc,"sOi",lpTopic,list,iLenght);
					Py_CLEAR(call);
					Py_DECREF(list);
					delete lpMsg;
					EnterCriticalSection(gMsgQueueSection);
				}
				LeaveCriticalSection(gMsgQueueSection);
				break;
			case WAIT_OBJECT_0 + 1:
				IsRun = false;
				break;
		}
		PyGILState_Release(state);
	}
}

void c_SubCallBack::OnReceived(CSubscribeInterface *lpSub,int subscribeIndex, const void *lpData, int nLength,LPSUBSCRIBE_RECVDATA lpRecvData)
{
	if (lpData == NULL || nLength <= 0)
	{
		printf("主推数据指针为空\n");
		return;
	}
	CSubCalBackPara * lpPara = new CSubCalBackPara();
	lpPara->lpBizMsg = NewBizMessage();
	lpPara->lpBizMsg->AddRef();
	strncpy_s(lpPara->szTopicName,lpRecvData->szTopicName,sizeof(lpPara->szTopicName)-1);
	lpPara->lpBizMsg->SetContent((void*)lpData,nLength);
	lpPara->lpBizMsg->SetKeyInfo(lpRecvData->lpFilterData,lpRecvData->iFilterDataLen);
	lpPara->lpBizMsg->SetAppData(lpRecvData->lpAppData,lpRecvData->iAppDataLen);

	EnterCriticalSection(gMsgQueueSection);
    DealMsgQueue->push(lpPara);
    LeaveCriticalSection(gMsgQueueSection);
	SetEvent(EventHandle[0]);
}

void c_SubCallBack::OnRecvTickMsg(CSubscribeInterface *lpSub,int subscribeIndex,const char* TickMsgInfo)
{
	printf("OnRecvTickMsg");
}

c_CSubscribeInterface::c_CSubscribeInterface(CSubscribeInterface* lpSub)
{
	lpSubscribe = lpSub;
	lpSubscribe->AddRef();
}

c_CSubscribeInterface::~c_CSubscribeInterface()
{

}

int c_CSubscribeInterface::SubscribeTopic(c_CSubscribeParamInterface* lpSubscribeParamInter ,unsigned int uiTimeout,c_IF2UnPacker** lppBizUnPack,c_IF2Packer* lpBizPack)
{
	CSubscribeParamInterface* lpParam = lpSubscribeParamInter->GetInstance();
	IF2UnPacker* lpUnpack = NULL;
	IF2Packer* lpPack = NULL;
	int ret = -1;
	if(lpBizPack != NULL)
	{
		lpPack = lpBizPack->GetInstance();
		IF2UnPacker* lpTempUnPacker = NULL;
		ret = lpSubscribe->SubscribeTopic(lpParam,uiTimeout,&lpTempUnPacker,lpPack);
		if(lpTempUnPacker != NULL)
		  *lppBizUnPack = new c_IF2UnPacker(lpTempUnPacker);
	}
	else
	{
		ret = lpSubscribe->SubscribeTopic(lpParam,uiTimeout);
	}
	return ret;
}


int c_CSubscribeInterface::CancelSubscribeTopic(int subscribeIndex)
{
	return lpSubscribe->CancelSubscribeTopic(subscribeIndex);
}

int c_CSubscribeInterface::CancelSubscribeTopicEx(char* topicName,CFilterInterface* lpFilterInterface)
{
	return lpSubscribe->CancelSubscribeTopicEx(topicName,lpFilterInterface);
}

void c_CSubscribeInterface::GetSubcribeTopic(c_IF2Packer* lpPack)
{
	lpSubscribe->GetSubcribeTopic(lpPack->GetInstance());
}
void c_CSubscribeInterface::Release()
{
	if (lpSubscribe)
	{
		lpSubscribe->Release();
	}
}

c_CCallbackInterface::c_CCallbackInterface()
{
	if (!Py_IsInitialized())
	{
		Py_Initialize();
		PyEval_InitThreads();
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('./')");
	}
}

c_CCallbackInterface::c_CCallbackInterface(char* sMould,char* sClass)
{
	strcpy_s(sMouldName, sMould);
	strcpy_s(sClassName, sClass);
	DealMsgQueue = new std::queue<CCallBackParam*>();
	IsRun=true;
	for (int i = 0; i < 2; i++)  
    {
	  char threadName[12] = {0};
	  sprintf_s(threadName,"thread%d",GetThreadNum());
	  EventHandle[i] = CreateEvent(NULL, FALSE, FALSE, (LPCTSTR)threadName);
    }
	gMsgQueueSection = new CRITICAL_SECTION;
	InitializeCriticalSection(gMsgQueueSection);
}

c_CCallbackInterface::~c_CCallbackInterface()
{
	IsRun=false;
	SetEvent(EventHandle[1]);
	Py_Finalize();
}

void c_CCallbackInterface::run()
{
	while(IsRun)
	{
		CCallBackParam* lpMsg;
		int index = WaitForMultipleObjects(2, EventHandle, FALSE, INFINITE);
		PyObject* list = NULL;
		PyObject* call;
		state = PyGILState_Ensure();
		Py_INCREF(pClass);
		switch(index)
		{
			case WAIT_OBJECT_0:
				EnterCriticalSection(gMsgQueueSection);
				while( DealMsgQueue->size() > 0)
				{
					lpMsg = DealMsgQueue->front();
					DealMsgQueue->pop();
					LeaveCriticalSection(gMsgQueueSection);

					switch(lpMsg->iCallFuncType)
					{
					case 0:
						//PyObject_CallFunction(pConnectFunc,NULL);
						break;
					case 1:
						//PyObject_CallFunction(pSafeConnectFunc,NULL);
						break;
					case 2:
						call = PyObject_CallFunction(pRegisterFunc,NULL);
						Py_CLEAR(call);
						break;
					case 3:
						call = PyObject_CallFunction(pCloseFunc,NULL);
						Py_CLEAR(call);
						break;
					case 4:
						//PyObject_CallFunction(pSendFunc,NULL);
						break;
					case 5:
						if(lpMsg->iResult == 0 || lpMsg->iResult == 1)
						{
							char* lpBuff = (char*)(lpMsg->lpUnPacker->GetPackBuf());
							int iLenght = lpMsg->lpUnPacker->GetPackLen();
							list = PyList_New(0);
							for (int i = 0; i < iLenght; i++)
							{
								int iTemp = lpBuff[i];
								PyList_Append(list, Py_BuildValue("i", iTemp));
							}
							//PyObject_CallFunction(pReceivedBizFunc,"iOi",lpMsg->hSend,list,iLenght);
						}
						else
						{
							//PyObject_CallFunction(pReceivedBizFunc,"isi",lpMsg->hSend,lpMsg->sValue,strlen(lpMsg->sValue));
						}
						break;
					case 6:
						if(lpMsg->iResult == 0 || lpMsg->iResult == 1)
						{
							char* lpBuff = (char*)(lpMsg->lpUnPacker->GetPackBuf());
							int iLenght = lpMsg->lpUnPacker->GetPackLen();
							list = PyList_New(0);
							for (int i = 0; i < iLenght; i++)
							{
								int iTemp = lpBuff[i];
								PyList_Append(list, Py_BuildValue("i", iTemp));
							}
							//PyObject_CallFunction(pReceivedBizExFunc,"iOi",lpMsg->hSend,list,iLenght);
						}
						else
						{
							//PyObject_CallFunction(pReceivedBizExFunc,"isi",lpMsg->hSend,lpMsg->sValue,strlen(lpMsg->sValue));
						}
						break;
					case 7:
						{
							//if(lpMsg->iResult == 0 || lpMsg->iResult == 1)
							//{

							int iLenght = 0;
							//char* lpBuff = (char*)(lpMsg->lpBizMsg->GetContent(iLenght));
							char* lpBuff = (char*)lpMsg->lpBizMsg->GetBuff(iLenght);
							list = PyList_New(0);
							for (int i = 0; i < iLenght; i++)
							{
								int iTemp = lpBuff[i];
								PyList_Append(list, Py_BuildValue("i", iTemp));
							}
							//PyObject_CallFunction(pReceivedBizExFunc,"iOi",lpMsg->hSend,list,iLenght);
							//}
							//else
							//{
							//	PyObject_CallFunction(pReceivedBizExFunc,"isi",lpMsg->hSend,lpMsg->sValue,strlen(lpMsg->sValue));
							//}
							//PyObject_CallFunction(pReceivedBizMsgFunc,NULL);
							call = PyObject_CallFunction(pReceivedBizMsgFunc,"iOi",lpMsg->hSend,list,iLenght);
							Py_CLEAR(call);
							Py_DECREF(list);
						}
						break;
					default:
						printf("unkown event\n");
					}
					delete(lpMsg);
					EnterCriticalSection(gMsgQueueSection);
				}
				LeaveCriticalSection(gMsgQueueSection);
				break;
			case WAIT_OBJECT_0 + 1:
				IsRun = false;
				break;
			default:
				printf("unkown wait\n");
		}
		PyGILState_Release(state);
	}
}

int c_CCallbackInterface::InitInstance()
{
	pModule =  NULL;
	if (!Py_IsInitialized())
	{
		Py_Initialize();
		PyEval_InitThreads();
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('./')");
	}
	pModule = PyImport_ImportModule(sMouldName);
	if (!pModule) 
	{
		printf("Cant open python file!\n");
		return -1;
	}
	pDict = PyModule_GetDict(pModule);
	if(!pDict)
	{
		printf("Cant open Get Dict!\n");
  		return -1;
	}
	pClass  = PyObject_GetAttrString(pModule, sClassName);
	if(!pClass)
	{
		printf("Cant open Get Class!\n");
		return -1;
	}
	pObject = PyEval_CallObject(pClass, NULL);
	if(!pObject)
	{
		printf("Class install failed!\n");
		return -1;
	}

 //   pConnectFunc=PyObject_GetAttrString(pObject, "OnConnect");
	//if(!pConnectFunc)
	//{
	//	printf("OnConnect function init failed!\n");
	//	return -1;
	//}

	//pSafeConnectFunc=PyObject_GetAttrString(pObject, "OnSafeConnect");
	//if(!pSafeConnectFunc)
	//{
	//	printf("OnSafeConnect function init failed!\n");
	//	return -1;
	//}

	pRegisterFunc=PyObject_GetAttrString(pObject, "OnRegister");
	if(!pRegisterFunc)
	{
		printf("OnRegister function init failed!\n");
		return -1;
	}

	//pSendFunc=PyObject_GetAttrString(pObject, "OnSent");
	//if(!pSendFunc)
	//{
	//	printf("OnSent function init failed!\n");
	//	return -1;
	//}

	pCloseFunc=PyObject_GetAttrString(pObject, "OnClose");
	if(!pCloseFunc)
	{
		printf("OnClose function init failed!\n");
		return -1;
	}

	//pReceivedBizFunc=PyObject_GetAttrString(pObject, "OnReceivedBiz");
	//if(!pReceivedBizFunc)
	//{
	//	printf("OnReceivedBiz function init failed!\n");
	//	return -1;
	//}

	//pReceivedBizExFunc=PyObject_GetAttrString(pObject, "OnReceivedBizEx");
	//if(!pReceivedBizExFunc)
	//{
	//	printf("OnReceivedBizEx function init failed!\n");
	//	return -1;
	//}

	pReceivedBizMsgFunc=PyObject_GetAttrString(pObject, "OnReceivedBizMsg");
	if(!pReceivedBizMsgFunc)
	{
		printf("OnReceivedBizMsg function init failed!\n");
		return -1;
	}
	Thread = new std::thread(&c_CCallbackInterface::run,this);
	return 0;
}

void c_CCallbackInterface::OnConnect(CConnectionInterface *lpConnection)
{
	//CCallBackParam* lpMsg = new CCallBackParam();
	//lpMsg->iResult = 0;
	//lpMsg->iCallFuncType = 0;
	//lpMsg->lpBizMsg = NULL;
	//lpMsg->lpUnPacker = NULL;
	//EnterCriticalSection(gMsgQueueSection);
 //   DealMsgQueue->push(lpMsg);
 //   LeaveCriticalSection(gMsgQueueSection);
	//SetEvent(EventHandle[0]);
}

void c_CCallbackInterface::OnSafeConnect(CConnectionInterface *lpConnection)
{
	//printf("OnSafeConnect!\n");
	//CCallBackParam* lpMsg = new CCallBackParam();
	//lpMsg->iResult = 0;
	//lpMsg->iCallFuncType = 1;
	//lpMsg->lpBizMsg = NULL;
	//lpMsg->lpUnPacker = NULL;
	//EnterCriticalSection(gMsgQueueSection);
 //   DealMsgQueue->push(lpMsg);
 //   LeaveCriticalSection(gMsgQueueSection);
	////state = PyGILState_Ensure();
	//SetEvent(EventHandle[0]);
	////PyObject_CallFunction(pSafeConnectFunc,NULL);
	////PyGILState_Release(state);
}

void c_CCallbackInterface::OnRegister(CConnectionInterface *lpConnection)
{
	CCallBackParam* lpMsg = new CCallBackParam();
	lpMsg->iResult = 0;
	lpMsg->iCallFuncType = 2;
	lpMsg->lpBizMsg = NULL;
	lpMsg->lpUnPacker = NULL;
	EnterCriticalSection(gMsgQueueSection);
    DealMsgQueue->push(lpMsg);
    LeaveCriticalSection(gMsgQueueSection);
	//state = PyGILState_Ensure();
	SetEvent(EventHandle[0]);
	//PyObject_CallFunction(pRegisterFunc,NULL);
	//PyGILState_Release(state);
}

void c_CCallbackInterface::OnClose(CConnectionInterface *lpConnection)
{
	CCallBackParam* lpMsg = new CCallBackParam();
	lpMsg->iResult = 0;
	lpMsg->iCallFuncType = 3;
	lpMsg->lpBizMsg = NULL;
	lpMsg->lpUnPacker = NULL;
	EnterCriticalSection(gMsgQueueSection);
    DealMsgQueue->push(lpMsg);
    LeaveCriticalSection(gMsgQueueSection);
	//state = PyGILState_Ensure();
	SetEvent(EventHandle[0]);
	//PyObject_CallFunction(pCloseFunc,NULL);
	//PyGILState_Release(state);
}

void c_CCallbackInterface::OnSent(CConnectionInterface *lpConnection, int hSend, void *reserved1, void *reserved2, int nQueuingData)
{
	//printf("OnSent!\n");
	//CCallBackParam* lpMsg = new CCallBackParam();
	//lpMsg->iResult = 0;
	//lpMsg->iCallFuncType = 4;
	//lpMsg->lpBizMsg = NULL;
	//lpMsg->lpUnPacker = NULL;
	//EnterCriticalSection(gMsgQueueSection);
 //   DealMsgQueue->push(lpMsg);
 //   LeaveCriticalSection(gMsgQueueSection);
	////state = PyGILState_Ensure();
	//SetEvent(EventHandle[0]);
	////PyObject_CallFunction(pSendFunc,NULL);
	////PyGILState_Release(state);
}

void c_CCallbackInterface::Reserved1(void *a, void *b, void *c, void *d)
{
}

void c_CCallbackInterface::Reserved2(void *a, void *b, void *c, void *d)
{
}

int  c_CCallbackInterface::Reserved3()
{
	return 0;
}

void c_CCallbackInterface::Reserved4()
{
}

void c_CCallbackInterface::Reserved5()
{
}

void c_CCallbackInterface::Reserved6()
{
}

void c_CCallbackInterface::Reserved7()
{
}

void c_CCallbackInterface::OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnPackerOrStr, int nResult)
{
	//printf("OnReceivedBiz!\n");
	//CCallBackParam* lpMsg = new CCallBackParam();
	//lpMsg->hSend = hSend;
	//lpMsg->iResult = nResult;
	//lpMsg->iCallFuncType = 5;
	//lpMsg->lpBizMsg = NULL;
	//if(nResult == 0 || nResult == 1)
	//{
	//	void* lpBuff = ((IF2UnPacker*)lpUnPackerOrStr)->GetPackBuf();
	//	int iLen = ((IF2UnPacker*)lpUnPackerOrStr)->GetPackLen();
	//	lpMsg->lpUnPacker = NewUnPacker(lpBuff,iLen);
	//}
	//else
	//{
	//	char* sInfo = (char*)lpUnPackerOrStr;
	//	lpMsg->sValue = (char*)malloc(sizeof(char)*strlen(sInfo));
	//	strcpy_s(lpMsg->sValue,strlen(sInfo),sInfo);
	//}
	//EnterCriticalSection(gMsgQueueSection);
 //   DealMsgQueue->push(lpMsg);
 //   LeaveCriticalSection(gMsgQueueSection);
	//SetEvent(EventHandle[0]);
}

void c_CCallbackInterface::OnReceivedBizEx(CConnectionInterface *lpConnection, int hSend, LPRET_DATA lpRetData, const void *lpUnpackerOrStr, int nResult)
{
	//printf("OnReceivedBizEx!\n");
	//CCallBackParam* lpMsg = new CCallBackParam();
	//lpMsg->hSend = hSend;
	//lpMsg->iResult = nResult;
	//lpMsg->iCallFuncType = 6;
	//lpMsg->lpBizMsg = NULL;
	//if(nResult == 0 || nResult == 1)
	//{
	//	void* lpBuff = ((IF2UnPacker*)lpUnpackerOrStr)->GetPackBuf();
	//	int iLen = ((IF2UnPacker*)lpUnpackerOrStr)->GetPackLen();
	//	lpMsg->lpUnPacker = NewUnPacker(lpBuff,iLen);
	//}
	//else
	//{
	//	char* sInfo = (char*)lpUnpackerOrStr;
	//	lpMsg->sValue = (char*)malloc(sizeof(char)*strlen(sInfo));
	//	strcpy_s(lpMsg->sValue,strlen(sInfo),sInfo);
	//}
	//EnterCriticalSection(gMsgQueueSection);
	//DealMsgQueue->push(lpMsg);
	//LeaveCriticalSection(gMsgQueueSection);
	//state = PyGILState_Ensure();
	//SetEvent(EventHandle[0]);
	//PyGILState_Release(state);
}

void c_CCallbackInterface::OnReceivedBizMsg(CConnectionInterface *lpConnection, int hSend, IBizMessage* lpMsg)
{
	//printf("OnReceivedBizMsg!\n");
	CCallBackParam* lpCallMsg = new CCallBackParam();
	lpCallMsg->hSend = hSend;
	lpCallMsg->iResult = 0;
	lpCallMsg->iCallFuncType = 7;
	lpCallMsg->lpUnPacker = NULL;
	int iLen = 0;
	const void* lpBuff = lpMsg->GetBuff(iLen);
	lpCallMsg->lpBizMsg = NewBizMessage();
	lpCallMsg->lpBizMsg->AddRef();
	lpCallMsg->lpBizMsg->SetBuff((void*)lpBuff,iLen);
	EnterCriticalSection(gMsgQueueSection);
    DealMsgQueue->push(lpCallMsg);
    LeaveCriticalSection(gMsgQueueSection);
	state = PyGILState_Ensure();
	SetEvent(EventHandle[0]);
	PyGILState_Release(state);
}

c_CConnectionInterface::c_CConnectionInterface(C_CConfigInterface* lpConfig)
{
	lpConnect = NewConnection(lpConfig->GetInstance());
	lpConnect->AddRef();
}

c_CConnectionInterface::~c_CConnectionInterface()
{
}

int c_CConnectionInterface::Connect(unsigned int uiTimeout)
{
	return lpConnect->Connect(uiTimeout);
}

int c_CConnectionInterface::Close()
{
	return lpConnect->Close();
}

char* c_CConnectionInterface::GetServerAddress(int* lpPort)
{
	return (char*)lpConnect->GetServerAddress(lpPort);
}

int c_CConnectionInterface::GetStatus()
{
	return lpConnect->GetStatus();
}

int c_CConnectionInterface::GetServerLoad()
{
	return lpConnect->GetServerLoad();
}

char* c_CConnectionInterface::GetErrorMsg(int nErrorCode)
{
	return (char*)lpConnect->GetErrorMsg(nErrorCode);
}

int c_CConnectionInterface::GetConnectError()
{
	return lpConnect->GetConnectError();
}

char* c_CConnectionInterface::GetRealAddress()
{
	return (char*)lpConnect->GetRealAddress();
}
char* c_CConnectionInterface::GetSelfAddress()
{
	return (char*)lpConnect->GetSelfAddress();
}

char* c_CConnectionInterface::GetSelfMac()
{
	return (char*)lpConnect->GetSelfMac();
}

c_CSubscribeInterface* c_CConnectionInterface::NewSubscriber(c_SubCallBack *lpCallback,char* SubScribeName,int iTimeOut,
    int iInitRecvQLen,int iStepRecvQLen)
{
	CSubscribeInterface* lpSub = lpConnect->NewSubscriber(lpCallback, SubScribeName,iTimeOut,iInitRecvQLen,iStepRecvQLen);
	c_CSubscribeInterface* lp  = NULL;
	if (lpSub != NULL)
	{
		lp= new c_CSubscribeInterface(lpSub);
	}
	return lp;
}

c_IF2UnPacker* c_CConnectionInterface::GetTopic(int byForce,int iTimeOut)
{
	bool bForce = false;
	if(byForce > 0)
		bForce = true;
	IF2UnPacker* lpUnpack = lpConnect->GetTopic(bForce,iTimeOut);
	c_IF2UnPacker* lpUnpacker = new c_IF2UnPacker(lpUnpack);
	return lpUnpacker;
}

char* c_CConnectionInterface::GetMCLastError()
{
	return (char*)lpConnect->GetMCLastError();
}

int c_CConnectionInterface::Create2BizMsg(c_CCallbackInterface *lpCallback)
{
	return lpConnect->Create2BizMsg(lpCallback);
}

int c_CConnectionInterface::SendBizMsg(c_IBizMessage* lpMsg,int nAsy)
{
	return lpConnect->SendBizMsg(lpMsg->GetInstance(),nAsy);
}

int c_CConnectionInterface::RecvBizMsg(int hSend, c_IBizMessage* lpMsg, unsigned uiTimeout, unsigned uiFlag)
{
	IBizMessage* lpBizMsg = lpMsg->GetInstance();
	IBizMessage* lpRecv = NULL;
	int iRet = lpConnect->RecvBizMsg(hSend,&lpRecv,uiTimeout,uiFlag);
	if (iRet == 0 && lpRecv != NULL) //如果接收成功
	{
		int iLen = 0;
		void * lpBuf = lpRecv->GetBuff(iLen);
		lpBizMsg->SetBuff(lpBuf,iLen);
	}
	return iRet;
}
char* c_CConnectionInterface::GetLastAnsError(int bAsyError)
{
	bool bAs = false;
	if(bAsyError > 0)
		bAs = true;
	return (char*)lpConnect->GetLastAnsError(bAs);
}
void c_CConnectionInterface::Release()
{
	lpConnect->Release();
}

