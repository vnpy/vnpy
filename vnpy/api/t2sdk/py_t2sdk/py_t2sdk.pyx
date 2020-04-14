# coding=utf-8
# distutils: language = c++

cimport py_t2sdk
from cpython.pycapsule cimport *
from  ctypes  import  *
from libcpp.string cimport string
from libc.stdlib cimport *

cdef class pyIF2UnPacker

cdef class pyIF2Packer:
  cdef c_IF2Packer* lpPacker
  def __cinit__(self):
    self.lpPacker = new c_IF2Packer()
  def __dealloc__(self):
    del self.lpPacker
  def BeginPack(self):
    self.lpPacker.BeginPack()
  def NewDataset(self,str szDatasetName, int iReturnCode):
    sName = bytes(szDatasetName,encoding='utf-8')
    return self.lpPacker.NewDataset(sName,iReturnCode)
  def AddField(self,str szFieldName,str cFieldType='S',int iFieldWidth=255,int iFieldScale=4):
    sName = bytes(szFieldName,encoding='utf-8')
    sType = bytes(cFieldType,encoding='utf-8')
    return self.lpPacker.AddField(sName,sType[0],iFieldWidth,iFieldScale)
  def AddStr(self,str szValue):
    sValue = bytes(szValue,encoding='utf-8')
    return self.lpPacker.AddStr(sValue)
  def AddInt(self,int iValue):
    return self.lpPacker.AddInt(iValue)
  def AddDouble(self,double fValue):
    return self.lpPacker.AddDouble(fValue)
  def AddChar(self,str cValue):
    sValue = bytes(cValue,encoding='utf-8')
    return self.lpPacker.AddChar(sValue[0])
  def AddRaw(self,list lpBuff,int iLen):
    cdef char* sBuff = <char*>malloc(iLen)
    cdef int iIndex = 0
    while iIndex < iLen:
      sBuff[iIndex] = lpBuff[iIndex]
      iIndex+=1
    iRet = self.lpPacker.AddRaw(sBuff,iLen)
    free(sBuff)
    return iRet
  def EndPack(self):
    return self.lpPacker.EndPack()
  def GetPackBuf(self):
    cdef int iLength = self.lpPacker.GetPackLen()
    cdef int* sBuff = self.lpPacker.GetPackBuf()
    lpBuff = []
    cdef int iIndex = 0
    while iIndex < iLength:
      lpBuff.append(sBuff[iIndex])
      iIndex +=1
    return lpBuff
  def GetPackLen(self):
    return self.lpPacker.GetPackLen()
  def GetPackBufSize(self):
    return self.lpPacker.GetPackBufSize()
  def GetVersion(self):
    return self.lpPacker.GetVersion()
  def SetReturnCode(self,long dwRetCode):
    self.lpPacker.SetReturnCode(dwRetCode)
  def UnPack(self):
    cdef c_IF2UnPacker* lpUnpacker = self.lpPacker.UnPack()
    lpPyUnpacker = pyIF2UnPacker()
    lpPyUnpacker.lpUnpacker = lpUnpacker
    return lpPyUnpacker
  def FreeMem(self):
    self.lpPacker.FreeMem()
  def ClearValue(self):
    self.lpPacker.ClearValue()
  def BeginPackEx(self,str szName):
    sName = bytes(szName,encoding='utf-8')
    self.lpPacker.BeginPackEx(sName)
  def ClearDataSet(self):
    self.lpPacker.ClearDataSet()
  def Release(self):
    self.lpPacker.Release()

cdef class pyIF2UnPacker:
  cdef c_IF2UnPacker* lpUnpacker
  def __cinit__(self):
    self.lpUnpacker = NULL
  def __dealloc__(self):
    if self.lpUnpacker != NULL:
        del self.lpUnpacker
        self.lpUnpacker = NULL
  def GetVersion(self):
    return self.lpUnpacker.GetVersion()
  def Open(self,list lpBuff,int iLen):
    cdef char* sBuff = <char*>malloc(iLen)
    cdef int iIndex = 0
    while iIndex < iLen:
      sBuff[iIndex] = lpBuff[iIndex]
      iIndex+=1
    if self.lpUnpacker == NULL:
        self.lpUnpacker = new c_IF2UnPacker(sBuff,iLen)
        iRet = 0
    else:
        iRet = self.lpUnpacker.Open(sBuff,iLen)
    free(sBuff)
    return iRet
  def GetDatasetCount(self):
    if self.lpUnpacker == NULL:
      return -1;
    return self.lpUnpacker.GetDatasetCount()
  def SetCurrentDatasetByIndex(self,int nIndex):
    self.lpUnpacker.SetCurrentDatasetByIndex(nIndex)
  def SetCurrentDataset(self,str szDatasetName):
    sName = bytes(szDatasetName,encoding='utf-8')
    self.lpUnpacker.SetCurrentDataset(sName)
  def  GetPackBuf(self):
    cdef char* lpBuff = self.lpUnpacker.GetPackBuf()
    return lpBuff
  def  GetPackLen(self):
    return self.lpUnpacker.GetPackLen()
  def GetRowCount(self):
    return self.lpUnpacker.GetRowCount()
  def First(self):
    self.lpUnpacker.First()
  def Last(self):
    self.lpUnpacker.Last()
  def Go(self,int nRow):
    self.lpUnpacker.Go(nRow)
  def GetDatasetName(self):
    cdef char* sName = self.lpUnpacker.GetDatasetName()
    return sName
  def GetColTypeByName(self,str columnName):
    sName = bytes(columnName,encoding='utf-8')
    cdef char* sType = self.lpUnpacker.GetColTypeByName(sName)
    return sType.decode('gbk')
  def GetColScaleByName(self,str columnName):
    sName = bytes(columnName,encoding='utf-8')
    return self.lpUnpacker.GetColScaleByName(sName)
  def GetColWidthByName(self,str columnName):
    sName = bytes(columnName,encoding='utf-8')
    return self.lpUnpacker.GetColWidthByName(sName)
  def GetColCount(self):
    return self.lpUnpacker.GetColCount()
  def GetColName(self,int column):
    return self.lpUnpacker.GetColName(column).decode('gbk')
  def GetColType(self,int column):
    cdef char* sType = self.lpUnpacker.GetColType(column)
    return sType.decode('gbk')
  def GetColScale(self,int column):
    return self.lpUnpacker.GetColScale(column)
  def GetColWidth(self,int column):
    return self.lpUnpacker.GetColWidth(column)
  def  FindColIndex(self,str columnName):
    sName = bytes(columnName,encoding='utf-8')
    return self.lpUnpacker.FindColIndex(sName)
  def  GetStrByIndex(self,int column):
    return self.lpUnpacker.GetStrByIndex(column).decode('GBK')
  def GetStr(self,str columnName):
    sName = bytes(columnName,encoding='UTF-8')
    return self.lpUnpacker.GetStr(sName).decode('GBK')
  def GetCharByIndex(self,int column):
    return self.lpUnpacker.GetCharByIndex(column).decode('UTF-8')
  def GetChar(self,str columnName):
    sName = bytes(columnName,encoding='UTF-8')
    return self.lpUnpacker.GetChar(sName).decode('UTF-8')
  def GetDoubleByIndex(self, int column):
    return self.lpUnpacker.GetDoubleByIndex(column)
  def GetDouble(self,str columnName):
    sName = bytes(columnName,encoding='utf-8')
    return self.lpUnpacker.GetDouble(sName)
  def  GetIntByIndex(self,int column):
    return self.lpUnpacker.GetIntByIndex(column)
  def GetInt(self,str columnName):
    sName = bytes(columnName,encoding='utf-8')
    if self.lpUnpacker == NULL:
      return -1
    return self.lpUnpacker.GetInt(sName)
  def  GetRawByIndex(self,int column):
    cdef int ilength = 0
    cdef char* sBuff = self.lpUnpacker.GetRawByIndex(column,&ilength)
    lpBuff = []
    cdef int iIndex = 0
    while iIndex < iLength:
      lpBuff.append(sBuff[iIndex])
      iIndex +=1
    return lpBuff,ilength
  def  GetRaw(self,str columnName):
    sName = bytes(columnName,encoding='utf-8')
    cdef int ilength = 0
    cdef char* sBuff = self.lpUnpacker.GetRaw(sName,&ilength)
    lpBuff = []
    cdef int iIndex = 0
    while iIndex < iLength:
      lpBuff.append(sBuff[iIndex])
      iIndex +=1
    return lpBuff,ilength
  def  WasNull(self):
    return self.lpUnpacker.WasNull()
  def  Next(self):
    self.lpUnpacker.Next()
  def  IsEOF(self):
    return self.lpUnpacker.IsEOF()
  def  IsEmpty(self):
    return self.lpUnpacker.IsEmpty()
  def  Destroy(self):
    self.lpUnpacker.Destroy()
  def Release(self):
    if self.lpUnpacker != NULL:
        self.lpUnpacker.Release()

cdef class pyCConfigInterface:
  cdef C_CConfigInterface* lpConfig
  def __cinit__(self):
    self.lpConfig = new C_CConfigInterface()
  def __dealloc__(self):
    del self.lpConfig
  def Load(self,str szFileName):
    sName = bytes(szFileName,encoding='utf-8')
    return self.lpConfig.Load(sName)
  def Save(self,str szFileName):
    sName = bytes(szFileName,encoding='utf-8')
    return self.lpConfig.Save(sName)
  def GetString(self,str szSection,str szEntry,str szDefault):
    sSection = bytes(szSection,encoding='utf-8')
    sEntry = bytes(szEntry,encoding='utf-8')
    sDefault = bytes(szDefault,encoding='utf-8')
    cdef char* sValue = self.lpConfig.GetString(sSection,sEntry,sDefault)
    return sValue
  def GetInt(self,str szSection,str szEntry, int iDefault):
    sSection = bytes(szSection,encoding='utf-8')
    sEntry = bytes(szEntry,encoding='utf-8')
    return self.lpConfig.GetInt(sSection,sEntry,iDefault)
  def SetString(self,str szSection,str szEntry,str szValue):
    sSection = bytes(szSection,encoding='utf-8')
    sEntry = bytes(szEntry,encoding='utf-8')
    sValue = bytes(szValue,encoding='utf-8')
    return self.lpConfig.SetString(sSection,sEntry,sValue)
  def SetInt(self,str szSection,str szEntry, int iValue):
    sSection = bytes(szSection,encoding='utf-8')
    sEntry = bytes(szEntry,encoding='utf-8')
    return self.lpConfig.SetInt(sSection,sEntry,iValue)
  def Release(self):
    self.lpConfig.Release()

cdef class pyIBizMessage:
  cdef c_IBizMessage* lpBizMessage
  def __cinit__(self):
    self.lpBizMessage = new c_IBizMessage()
  def __dealloc__(self):
    del self.lpBizMessage
  def SetFunction(self,int nFUnctionNo):
    self.lpBizMessage.SetFunction(nFUnctionNo)
  def GetFunction(self):
    return self.lpBizMessage.GetFunction()
  def SetPacketType(self,int nPacketType):
    self.lpBizMessage.SetPacketType(nPacketType)
  def GetPacketType(self):
    return self.lpBizMessage.GetPacketType()
  def SetBranchNo(self,int nBranchNo):
    self.lpBizMessage.SetBranchNo(nBranchNo)
  def GetBranchNo(self):
    return self.lpBizMessage.GetBranchNo()
  def SetSystemNo(self,int nSystemNo):
    self.lpBizMessage.SetSystemNo(nSystemNo)
  def GetSystemNo(self):
    return self.lpBizMessage.GetSystemNo()
  def SetSubSystemNo(self,int nSubSystemNo):
    self.lpBizMessage.SetSubSystemNo(nSubSystemNo)
  def GetSubSystemNo(self):
    return self.lpBizMessage.GetSubSystemNo()
  def SetSenderId(self,int nSenderId):
    self.lpBizMessage.SetSenderId(nSenderId)
  def GetSenderId(self):
    return self.lpBizMessage.GetSenderId()
  def SetPacketId(self,int nPacketId):
    self.lpBizMessage.SetPacketId(nPacketId)
  def GetPacketId(self):
    return self.lpBizMessage.GetPacketId()
  def SetErrorNo(self,int nErrorNo):
    self.lpBizMessage.SetErrorNo(nErrorNo)
  def GetErrorNo(self):
    return self.lpBizMessage.GetErrorNo()
  def SetErrorInfo(self,str strErrorInfo):
    sErrorInfo = bytes(strErrorInfo,encoding='utf-8')
    self.lpBizMessage.SetErrorInfo(sErrorInfo)
  def GetErrorInfo(self):
    cdef char* sErrInfo = self.lpBizMessage.GetErrorInfo()
    return sErrInfo
  def SetReturnCode(self,int nReturnCode):
    self.lpBizMessage.SetReturnCode(nReturnCode)
  def GetReturnCode(self):
    return self.lpBizMessage.GetReturnCode()
  def SetContent(self,list lpContent,int iLen):
    cdef char* sBuff = <char*>malloc(iLen)
    cdef int iIndex = 0
    while iIndex < iLen:
      sBuff[iIndex] = lpContent[iIndex]
      iIndex+=1
    self.lpBizMessage.SetContent(sBuff,iLen)
    free(sBuff)
  def GetContent(self):
    cdef int iLen = 0
    cdef char* sBuff = self.lpBizMessage.GetContent(iLen)
    lpBuff = []
    cdef iTemp = 0
    cdef int iIndex = 0
    while iIndex < iLen:
      iTemp = sBuff[iIndex]
      lpBuff.append(iTemp)
      iIndex +=1
    return lpBuff,iLen
  def SetIssueType(self,int nIssueType):
    self.lpBizMessage.SetIssueType(nIssueType)
  def GetIssueType(self):
    return self.lpBizMessage.GetIssueType()
  def SetSequeceNo(self,int nSequeceNo):
    self.lpBizMessage.SetSequeceNo(nSequeceNo)
  def GetSequeceNo(self):
    return self.lpBizMessage.GetSequeceNo()
  def SetKeyInfo(self,list lpKeyData,int iLen):
    cdef char* sBuff = <char*>malloc(iLen)
    cdef int iIndex = 0
    while iIndex < iLen:
      sBuff[iIndex] = lpKeyData[iIndex]
      iIndex+=1
    self.lpBizMessage.SetKeyInfo(sBuff,iLen)
  def GetKeyInfo(self):
    cdef int iLen = 0
    cdef int itemp = 0
    cdef char* sBuff = self.lpBizMessage.GetKeyInfo(iLen)
    lpBuff = []
    cdef int iIndex = 0
    while iIndex < iLen:
      lpBuff.append(sBuff[iIndex])
      iIndex +=1
    return lpBuff,iLen
  def SetAppData(self,str lpAppdata,int nAppLen):
    sAppData = bytes(lpAppdata,encoding='utf-8')
    self.lpBizMessage.SetAppData(sAppData,nAppLen)
  def GetAppData(self):
    cdef int iLen = 0
    cdef char* sAppData = self.lpBizMessage.GetAppData(iLen)
    return sAppData,iLen
  def ChangeReq2AnsMessage(self):
    self.lpBizMessage.ChangeReq2AnsMessage()
  def GetBuff(self):
    cdef int iLen = 0
    cdef iTemp = 0
    cdef char* sBuff = self.lpBizMessage.GetBuff(iLen)
    lpBuff = []
    cdef int iIndex = 0
    while iIndex < iLen:
      iTemp = sBuff[iIndex]
      lpBuff.append(iTemp)
      iIndex +=1
    return lpBuff,iLen
  def SetBuff(self,list lpBuff,int nBuffLen):
    cdef char* sBuff = <char*>malloc(nBuffLen)
    cdef int iIndex = 0
    while iIndex < nBuffLen:
      sBuff[iIndex] = lpBuff[iIndex]
      iIndex+=1
    self.lpBizMessage.SetBuff(sBuff,nBuffLen)
  def ReSet(self):
    self.lpBizMessage.ReSet()
  def Release(self):
    self.lpBizMessage.Release()

cdef class pySubscribeParamInterface:
  cdef c_CSubscribeParamInterface* lpSubscribeParam
  def __cinit__(self):
    self.lpSubscribeParam = new c_CSubscribeParamInterface()
  def __dealloc__(self):
    del self.lpSubscribeParam
  def SetTopicName(self,str szName):
    sName = bytes(szName,encoding='utf-8')
    self.lpSubscribeParam.SetTopicName(sName)
  def SetAppData(self,str lpData,int iLen):
    sData = bytes(lpData,encoding='utf-8')
    self.lpSubscribeParam.SetAppData(sData,iLen)
  def SetFilter(self,str filterName,str filterValue):
    sName = bytes(filterName,encoding='utf-8')
    sValue = bytes(filterValue,encoding='utf-8')
    self.lpSubscribeParam.SetFilter(sName,sValue)
  def SetReturnFiled(self,str filedName):
    sName = bytes(filedName,encoding='utf-8')
    self.lpSubscribeParam.SetReturnFiled(sName)
  def SetFromNow(self,int bFromNow):
    self.lpSubscribeParam.SetFromNow(bFromNow)
  def SetReplace(self,int bReplace):
    self.lpSubscribeParam.SetReplace(bReplace)
  def SetSendInterval(self,int nSendInterval):
    self.lpSubscribeParam.SetSendInterval(nSendInterval)
  def GetTopicName(self):
    cdef char* sName = self.lpSubscribeParam.GetTopicName()
    return sName
  def GetAppData(self):
    cdef int iLen = 0
    cdef char* sAppData = self.lpSubscribeParam.GetAppData(&iLen)
    return sAppData,iLen
  def GetFilterNameByIndex(self,int index):
    cdef char* sName = self.lpSubscribeParam.GetFilterNameByIndex(index)
    return sName
  def GetFilterValueByIndex(self,int index):
    cdef char* sName = self.lpSubscribeParam.GetFilterValueByIndex(index)
    return sName
  def GetFilterValue(self,str fileName):
    sName = bytes(fileName,encoding='utf-8')
    sValus = self.lpSubscribeParam.GetFilterValue(sName)
    return sValus
  def GetFilterCount(self):
    return self.lpSubscribeParam.GetFilterCount()
  def GetReturnFiled(self):
    cdef char* sFields = self.lpSubscribeParam.GetReturnFiled()
    return sFields
  def GetFromNow(self):
    cdef int bFromNow = self.lpSubscribeParam.GetFromNow()
    return bFromNow
  def GetReplace(self):
    cdef int bRep = self.lpSubscribeParam.GetReplace()
    return bRep
  def GetSendInterval(self):
    return self.lpSubscribeParam.GetSendInterval()
  def Release(self):
    return self.lpSubscribeParam.Release()

cdef class pySubCallBack:
  cdef c_SubCallBack* lpSubCallBack
  def __cinit__(self,str lpMould,str lpClass):
    sMould = bytes(lpMould,encoding='utf-8')
    sClass = bytes(lpClass,encoding='utf-8')
    self.lpSubCallBack = new c_SubCallBack(sMould,sClass)
  def initInstance(self):
    return self.lpSubCallBack.initInstance()

cdef class pySubscribeInterface:
  cdef c_CSubscribeInterface* lpSubcribe
  def __cinit__(self):
    self.lpSubcribe = NULL
  def __dealloc__(self):
    if self.lpSubcribe != NULL:
        del self.lpSubcribe
        self.lpSubcribe = NULL
  def SubscribeTopic(self,pySubscribeParamInterface lpSubParam,int uiTimeout,pyIF2UnPacker lpUnPack = None,pyIF2Packer lpPack = None):
    cdef c_IF2UnPacker** lppBizUnPack = NULL
    cdef c_IF2Packer* lpBizPack = NULL
    if lpUnPack != None and lpPack != None:
        lppBizUnPack = &(lpUnPack.lpUnpacker)
        lpBizPack = lpPack.lpPacker
    cdef int ret = self.lpSubcribe.SubscribeTopic(lpSubParam.lpSubscribeParam,uiTimeout,lppBizUnPack,lpBizPack)
    return ret   
  def CancelSubscribeTopic(self,int subscribeIndex):
    return self.lpSubcribe.CancelSubscribeTopic(subscribeIndex)
  def GetSubcribeTopic(self,pyIF2Packer lpPack):
    return self.lpSubcribe.GetSubcribeTopic(lpPack.lpPacker)
  def Release(self):
    return self.lpSubcribe.Release()
cdef class pyCallbackInterface:
  cdef c_CCallbackInterface* lpCallBack
  def __cinit__(self,str lpMould,str lpClass):
    sMould = bytes(lpMould,encoding='utf-8')
    sClass = bytes(lpClass,encoding='utf-8')
    self.lpCallBack = new c_CCallbackInterface(sMould,sClass)
  def InitInstance(self):
    return self.lpCallBack.InitInstance()
    
cdef class pyConnectionInterface:
  cdef c_CConnectionInterface* lpConnect
  def __cinit__(self,pyCConfigInterface pConfig):
    self.lpConnect = new c_CConnectionInterface(pConfig.lpConfig)
  def Connect(self,int uiTimeout):
    return self.lpConnect.Connect(uiTimeout)
  def Close(self):
    return self.lpConnect.Close()
  def GetServerAddress(self):
    cdef int iPort = 0
    cdef char* sAddress = self.lpConnect.GetServerAddress(&iPort)
    return sAddress,iPort
  def GetStatus(self):
    return self.lpConnect.GetStatus()
  def GetServerLoad(self):
    return self.lpConnect.GetServerLoad()
  def GetErrorMsg(self,int nErrorCode):
    cdef char* sErrMsg = self.lpConnect.GetErrorMsg(nErrorCode)
    return sErrMsg.decode('GBK')
  def GetConnectError(self):
    return self.lpConnect.GetConnectError()
  def GetRealAddress(self):
    cdef char* sAddress = self.lpConnect.GetRealAddress()
    return sAddress
  def GetSelfAddress(self):
    cdef char* sAddress = self.lpConnect.GetSelfAddress()
    return sAddress
  def GetSelfMac(self):
    cdef char* sMac = self.lpConnect.GetSelfMac()
    return sMac
  def NewSubscriber(self,pySubCallBack lppCallback,str SubScribeName,int iTimeOut):
    sName = bytes(SubScribeName,encoding='utf-8')
    cdef c_CSubscribeInterface* lpSub = self.lpConnect.NewSubscriber(lppCallback.lpSubCallBack,sName,iTimeOut)
    pSub = pySubscribeInterface()
    pSub.lpSubcribe = lpSub
    if lpSub == NULL:
        return -1,pSub
    else:
        return 0,pSub
  def GetMCLastError(self):
    cdef char* lpMcErr = self.lpConnect.GetMCLastError()
    return lpMcErr
  def Create2BizMsg(self,pyCallbackInterface lppCallback):
    return self.lpConnect.Create2BizMsg(lppCallback.lpCallBack)
  def SendBizMsg(self,pyIBizMessage lpMsg,int nAsy=0):
    return self.lpConnect.SendBizMsg(lpMsg.lpBizMessage,nAsy)
  def RecvBizMsg(self,int hSend, int uiTimeout=1000, int uiFlag=0):
    lpMsg = pyIBizMessage()
    ret = self.lpConnect.RecvBizMsg(hSend,lpMsg.lpBizMessage,uiTimeout,uiFlag)
    return ret,lpMsg
  def GetLastAnsError(self,int bAsyError=0):
    return self.lpConnect.GetLastAnsError(bAsyError)
    
  
  