# coding=utf-8
# distutils: language = c++

cdef extern from "ufx_interface.h":
  cdef cppclass c_IF2UnPacker

  cdef cppclass c_IF2Packer:
    c_IF2Packer() except+
    void SetBuffer(char* pBuf,int iBufSize,int iDataLen)
    void BeginPack()
    int NewDataset(char *szDatasetName, int iReturnCode)
    int AddField(char *szFieldName,char cFieldType,int iFieldWidth,int iFieldScale)
    int AddStr(char *szValue)
    int AddInt(int iValue)
    int AddDouble(double fValue)
    int AddChar(char* cValue)
    int AddRaw(char* lpBuff,int iLen)
    void EndPack()
    int* GetPackBuf()
    int GetPackLen()
    int GetPackBufSize()
    int GetVersion()
    void SetReturnCode(long dwRetCode)
    c_IF2UnPacker* UnPack()
    void FreeMem()
    void ClearValue()
    void BeginPackEx(char* szName)
    void ClearDataSet()
    void Release()

  cdef cppclass c_IF2UnPacker:
    c_IF2UnPacker(char* lpBuffer,int iLen) except+
    c_IF2UnPacker(c_IF2Packer* lpPacker) except+
    int GetVersion()
    char* GetErrorInfo()
    int Open(char* lpBuffer,int iLen)
    int GetDatasetCount()
    int SetCurrentDatasetByIndex(int nIndex)
    int SetCurrentDataset(char *szDatasetName)
    char* GetPackBuf()
    int GetPackLen()
    int GetRowCount()
    void First()
    void Last()
    void Go(int nRow)
    char* GetDatasetName()
    int OpenAndCopy(char* lpBuffer,int iLen)
    char* GetColTypeByName(char* columnName)
    int GetColScaleByName(char* columnName)
    int GetColWidthByName(char* columnName)
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
    void Release()

  cdef cppclass C_CConfigInterface:
    C_CConfigInterface() except+
    int Load(char *szFileName)
    int Save(char *szFileName)
    char * GetString(char *szSection,  char *szEntry,  char *szDefault)
    int GetInt(char *szSection,  char *szEntry, int iDefault)
    int SetString(char *szSection,  char *szEntry,  char *szValue)
    int SetInt(char *szSection,  char *szEntry, int iValue)
    void Release()

  cdef cppclass c_IBizMessage:
    c_IBizMessage() except+
    void SetFunction(int nFUnctionNo)
    int GetFunction()
    void SetPacketType(int nPacketType)
    int GetPacketType()
    void SetBranchNo(int nBranchNo)
    int GetBranchNo()
    void SetSystemNo(int nSystemNo)
    int GetSystemNo()
    void SetSubSystemNo(int nSubSystemNo)
    int GetSubSystemNo()
    void SetSenderId(int nSenderId)
    int GetSenderId()
    void SetPacketId(int nPacketId)
    int GetPacketId()
    void SetErrorNo(int nErrorNo)
    int GetErrorNo()
    void SetErrorInfo(char* strErrorInfo)
    char* GetErrorInfo()
    void SetReturnCode(int nReturnCode)
    int GetReturnCode()
    void SetContent(char* lpContent,int iLen)
    char* GetContent(int& iLen)
    void SetIssueType(int nIssueType)
    int GetIssueType()
    void SetSequeceNo(int nSequeceNo)
    int GetSequeceNo()
    void SetKeyInfo(char* lpKeyData,int iLen)
    char* GetKeyInfo(int& iLen)
    void SetAppData(char* lpAppdata,int nAppLen)
    char* GetAppData(int& nAppLen)
    int ChangeReq2AnsMessage()
    char* GetBuff(int& nBuffLen)
    int SetBuff(char* lpBuff,int nBuffLen)
    void ReSet()
    void Release()

  cdef cppclass c_CSubscribeParamInterface:
    c_CSubscribeParamInterface() except+
    void SetTopicName(char* szName)
    void SetAppData(char* lpData,int iLen)
    void SetFilter(char* filterName,char* filterValue)
    void SetReturnFiled(char* filedName)
    void SetFromNow(int bFromNow)
    void SetReplace(int bReplace)
    void SetSendInterval(int nSendInterval)
    char* GetTopicName()
    char* GetAppData(int *iLen)
    char* GetFilterNameByIndex(int index)
    char* GetFilterValueByIndex(int index)
    char* GetFilterValue(char*  fileName)
    int GetFilterCount()
    char* GetReturnFiled()
    int GetFromNow()
    int GetReplace()
    int GetSendInterval()
    void Release()

  cdef cppclass c_SubCallBack:
    c_SubCallBack(char *lpMould,char *lpClass) except+
    c_SubCallBack() except+
    int initInstance()

  cdef cppclass c_CSubscribeInterface:
    int SubscribeTopic(c_CSubscribeParamInterface* lpSubscribeParamInter ,int uiTimeout,c_IF2UnPacker** lppBizUnPack,c_IF2Packer* lpBizPack);
    int CancelSubscribeTopic(int subscribeIndex)
    void GetSubcribeTopic(c_IF2Packer* lpPack)
    void Release();

  cdef cppclass c_CCallbackInterface:
    c_CCallbackInterface(char* sMould,char* sClass) except+
    c_CCallbackInterface() except+
    int InitInstance()

  cdef cppclass c_CConnectionInterface:
    c_CConnectionInterface(C_CConfigInterface* lpConfig) except+
    int Create(c_CCallbackInterface *lpCallback)
    int Connect(unsigned int uiTimeout)
    int Close()
    char* GetServerAddress(int *lpPort)
    int GetStatus()
    int GetServerLoad()
    char* GetErrorMsg(int nErrorCode)
    int GetConnectError()
    int SendBiz(int iFunID, c_IF2Packer *lpPacker, int nAsy, int iSystemNo, int nCompressID)
    int RecvBiz(int hSend, c_IF2UnPacker **lppUnPackerOrStr, int uiTimeout, int uiFlag)
    int SendBizEx(int iFunID, c_IF2Packer *lpPacker,char* svrName, int nAsy, int iSystemNo, int nCompressID,int branchNo)
    int RecvBizEx(int hSend, c_IF2UnPacker **lppUnpackerOrStr, unsigned uiTimeout, unsigned uiFlag)
    int CreateEx(c_CCallbackInterface *lpCallback)
    char* GetRealAddress()
    int Reserved8()
    int Reserved9()
    char* GetSelfAddress()
    char* GetSelfMac()
    c_CSubscribeInterface* NewSubscriber(c_SubCallBack *lpCallback,char* SubScribeName,int iTimeOut,
        int iInitRecvQLen=INIT_RECVQ_LEN,int iStepRecvQLen=STEP_RECVQ_LEN)
    c_IF2UnPacker* GetTopic(int byForce,int iTimeOut)
    char* GetMCLastError()
    int Create2BizMsg(c_CCallbackInterface *lpCallback)
    int SendBizMsg(c_IBizMessage* lpMsg,int nAsy)
    int RecvBizMsg(int hSend, c_IBizMessage* lpMsg, unsigned uiTimeout, unsigned uiFlag)
    int Reserved10()
    int Reserved11()
    char* GetLastAnsError(int bAsyError)
