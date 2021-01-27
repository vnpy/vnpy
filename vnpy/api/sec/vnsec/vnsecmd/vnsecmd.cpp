
// vndfitcmd.cpp : 定义 DLL 应用程序的导出函数。
//
#include "vnsecmd.h"

///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------
void MdApi::OnFrontConnected()
{
    Task task = Task();
    task.task_name = ONFRONTCONNECTED;
    this->task_queue.push(task);
};

void MdApi::OnFrontDisconnected(int nReason)
{
    Task task = Task();
    task.task_name = ONFRONTDISCONNECTED;
    task.task_id = nReason;
    this->task_queue.push(task);
};

void MdApi::OnRtnNotice(DFITCSECRspNoticeField *pNotice)
{
    Task task = Task();
    task.task_name = ONRTNNOTICE;
    if (pNotice)
    {
        DFITCSECRspNoticeField *task_data = new DFITCSECRspNoticeField();
        *task_data = *pNotice;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};

void MdApi::OnRspError(struct DFITCSECRspInfoField *pRspInfo)
{
    Task task = Task();
    task.task_name = ONRSPERROR;
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

void MdApi::OnRspStockUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo)
{
    Task task = Task();
    task.task_name = ONRSPSTOCKUSERLOGIN;
    if (pRspUserLogin)
    {
        DFITCSECRspUserLoginField *task_data = new DFITCSECRspUserLoginField();
        *task_data = *pRspUserLogin;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

void MdApi::OnRspStockUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo)
{
    Task task = Task();
    task.task_name = ONRSPSTOCKUSERLOGOUT;
    if (pRspUsrLogout)
    {
        DFITCSECRspUserLogoutField *task_data = new DFITCSECRspUserLogoutField();
        *task_data = *pRspUsrLogout;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

void MdApi::OnRspSOPUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo)
{
    Task task = Task();
    task.task_name = ONRSPSOPUSERLOGIN;
    if (pRspUserLogin)
    {
        DFITCSECRspUserLoginField *task_data = new DFITCSECRspUserLoginField();
        *task_data = *pRspUserLogin;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

void MdApi::OnRspSOPUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo)
{
    Task task = Task();
    task.task_name = ONRSPSOPUSERLOGOUT;
    if (pRspUsrLogout)
    {
        DFITCSECRspUserLogoutField *task_data = new DFITCSECRspUserLogoutField();
        *task_data = *pRspUsrLogout;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

void MdApi::OnRspFASLUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo)
{
    Task task = Task();
    task.task_name = ONRSPFASLUSERLOGIN;
    if (pRspUserLogin)
    {
        DFITCSECRspUserLoginField *task_data = new DFITCSECRspUserLoginField();
        *task_data = *pRspUserLogin;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

void MdApi::OnRspFASLUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo)
{
    Task task = Task();
    task.task_name = ONRSPFASLUSERLOGOUT;
    if (pRspUsrLogout)
    {
        DFITCSECRspUserLogoutField *task_data = new DFITCSECRspUserLogoutField();
        *task_data = *pRspUsrLogout;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

void MdApi::OnRspStockSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo)
{
    Task task = Task();
    task.task_name = ONRSPSTOCKSUBMARKETDATA;
    if (pSpecificInstrument)
    {
        DFITCSECSpecificInstrumentField *task_data = new DFITCSECSpecificInstrumentField();
        *task_data = *pSpecificInstrument;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

void MdApi::OnRspStockUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo)
{
    Task task = Task();
    task.task_name = ONRSPSTOCKUNSUBMARKETDATA;
    if (pSpecificInstrument)
    {
        DFITCSECSpecificInstrumentField *task_data = new DFITCSECSpecificInstrumentField();
        *task_data = *pSpecificInstrument;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

void MdApi::OnRspSOPSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo)
{
    Task task = Task();
    task.task_name = ONRSPSOPSUBMARKETDATA;
    if (pSpecificInstrument)
    {
        DFITCSECSpecificInstrumentField *task_data = new DFITCSECSpecificInstrumentField();
        *task_data = *pSpecificInstrument;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

void MdApi::OnRspSOPUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo)
{
    Task task = Task();
    task.task_name = ONRSPSOPUNSUBMARKETDATA;
    if (pSpecificInstrument)
    {
        DFITCSECSpecificInstrumentField *task_data = new DFITCSECSpecificInstrumentField();
        *task_data = *pSpecificInstrument;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

void MdApi::OnStockMarketData(struct DFITCStockDepthMarketDataField * pMarketDataField)
{
    Task task = Task();
    task.task_name = ONSTOCKMARKETDATA;
    if (pMarketDataField)
    {
        DFITCStockDepthMarketDataField *task_data = new DFITCStockDepthMarketDataField();
        *task_data = *pMarketDataField;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};

void MdApi::OnSOPMarketData(struct DFITCSOPDepthMarketDataField * pMarketDataField)
{	
    Task task = Task();
    task.task_name = ONSOPMARKETDATA;
    if (pMarketDataField)
    {
        DFITCSOPDepthMarketDataField *task_data = new DFITCSOPDepthMarketDataField();
        *task_data = *pMarketDataField;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};

void MdApi::OnRspStockAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo, bool flag)
{
    Task task = Task();
    task.task_name = ONRSPSTOCKAVAILABLEQUOT;
    if (pAvailableQuotInfo)
    {
        DFITCRspQuotQryField *task_data = new DFITCRspQuotQryField();
        *task_data = *pAvailableQuotInfo;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_last = flag;
    this->task_queue.push(task);
};

void MdApi::OnRspSopAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo, bool flag)
{
    Task task = Task();
    task.task_name = ONRSPSOPAVAILABLEQUOT;
    if (pAvailableQuotInfo)
    {
        DFITCRspQuotQryField *task_data = new DFITCRspQuotQryField();
        *task_data = *pAvailableQuotInfo;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_last = flag;
    this->task_queue.push(task);
};

void MdApi::OnRspUserMDPasswordUpdate(struct DFITCSECRspMDPasswordUpdateField *pMDPasswordUpdate, struct DFITCSECRspInfoField * pRspInfo)
{
    Task task = Task();
    task.task_name = ONRSPUSERMDPASSWORDUPDATE;
    if (pMDPasswordUpdate)
    {
        DFITCSECRspMDPasswordUpdateField *task_data = new DFITCSECRspMDPasswordUpdateField();
        *task_data = *pMDPasswordUpdate;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    this->task_queue.push(task);
};

///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void MdApi::processTask()
{
    try

    {
        while (this->active)
        {
            Task task = this->task_queue.pop();
            switch (task.task_name)
            {

            case ONFRONTCONNECTED:
            {
                this->processFrontConnected(&task);
                break;
            }

            case ONFRONTDISCONNECTED:
            {
                this->processFrontDisconnected(&task);
                break;
            }

            case ONRTNNOTICE:
            {
                this->processRtnNotice(&task);
                break;
            }

            case ONRSPERROR:
            {
                this->processRspError(&task);
                break;
            }

            case ONRSPSTOCKUSERLOGIN:
            {
                this->processRspStockUserLogin(&task);
                break;
            }

            case ONRSPSTOCKUSERLOGOUT:
            {
                this->processRspStockUserLogout(&task);
                break;
            }

            case ONRSPSOPUSERLOGIN:
            {
                this->processRspSOPUserLogin(&task);
                break;
            }

            case ONRSPSOPUSERLOGOUT:
            {
                this->processRspSOPUserLogout(&task);
                break;
            }

            case ONRSPFASLUSERLOGIN:
            {
                this->processRspFASLUserLogin(&task);
                break;
            }

            case ONRSPFASLUSERLOGOUT:
            {
                this->processRspFASLUserLogout(&task);
                break;
            }

            case ONRSPSTOCKSUBMARKETDATA:
            {
                this->processRspStockSubMarketData(&task);
                break;
            }

            case ONRSPSTOCKUNSUBMARKETDATA:
            {
                this->processRspStockUnSubMarketData(&task);
                break;
            }

            case ONRSPSOPSUBMARKETDATA:
            {
                this->processRspSOPSubMarketData(&task);
                break;
            }

            case ONRSPSOPUNSUBMARKETDATA:
            {
                this->processRspSOPUnSubMarketData(&task);
                break;
            }

            case ONSTOCKMARKETDATA:
            {
                this->processStockMarketData(&task);
                break;
            }

            case ONSOPMARKETDATA:
            {
                this->processSOPMarketData(&task);
                break;
            }

            case ONRSPSTOCKAVAILABLEQUOT:
            {
                this->processRspStockAvailableQuot(&task);
                break;
            }

            case ONRSPSOPAVAILABLEQUOT:
            {
                this->processRspSopAvailableQuot(&task);
                break;
            }

            case ONRSPUSERMDPASSWORDUPDATE:
            {
                this->processRspUserMDPasswordUpdate(&task);
                break;
            }
            };
        }
    }
    catch (const TerminatedError&)
    {
    }

};

void MdApi::processFrontConnected(Task *task)
{
    gil_scoped_acquire acquire;
    this->onFrontConnected();
};

void MdApi::processFrontDisconnected(Task *task)
{
    gil_scoped_acquire acquire;
    this->onFrontDisconnected(task->task_id);
};

void MdApi::processRtnNotice(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCSECRspNoticeField *task_data = (DFITCSECRspNoticeField*)task->task_data;
        data["noticeMsg"] = toUtf(task_data->noticeMsg);
        delete task_data;
    }
    this->onRtnNotice(data);
};

void MdApi::processRspError(Task *task)
{
    gil_scoped_acquire acquire;
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspError(error);
};

void MdApi::processRspStockUserLogin(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
        data["requestID"] = task_data->requestID;
        data["accountID"] = toUtf(task_data->accountID);
        data["sessionID"] = task_data->sessionID;
        data["frontID"] = task_data->frontID;
        data["localOrderID"] = task_data->localOrderID;
        data["loginTime"] = toUtf(task_data->loginTime);
        data["tradingDay"] = task_data->tradingDay;
        data["result"] = task_data->result;
        data["rtnMsg"] = toUtf(task_data->rtnMsg);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspStockUserLogin(data, error);
};

void MdApi::processRspStockUserLogout(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
        data["requestID"] = task_data->requestID;
        data["accountID"] = toUtf(task_data->accountID);
        data["result"] = task_data->result;
        data["rtnMsg"] = toUtf(task_data->rtnMsg);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspStockUserLogout(data, error);
};

void MdApi::processRspSOPUserLogin(Task *task)
{	
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
        data["requestID"] = task_data->requestID;
        data["accountID"] = toUtf(task_data->accountID);
        data["sessionID"] = task_data->sessionID;
        data["frontID"] = task_data->frontID;
        data["localOrderID"] = task_data->localOrderID;
        data["loginTime"] = toUtf(task_data->loginTime);
        data["tradingDay"] = task_data->tradingDay;
        data["result"] = task_data->result;
        data["rtnMsg"] = toUtf(task_data->rtnMsg);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspSOPUserLogin(data, error);
    
};

void MdApi::processRspSOPUserLogout(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
        data["requestID"] = task_data->requestID;
        data["accountID"] = toUtf(task_data->accountID);
        data["result"] = task_data->result;
        data["rtnMsg"] = toUtf(task_data->rtnMsg);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspSOPUserLogout(data, error);
};

void MdApi::processRspFASLUserLogin(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
        data["requestID"] = task_data->requestID;
        data["accountID"] = toUtf(task_data->accountID);
        data["sessionID"] = task_data->sessionID;
        data["frontID"] = task_data->frontID;
        data["localOrderID"] = task_data->localOrderID;
        data["loginTime"] = toUtf(task_data->loginTime);
        data["tradingDay"] = task_data->tradingDay;
        data["result"] = task_data->result;
        data["rtnMsg"] = toUtf(task_data->rtnMsg);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspFASLUserLogin(data, error);
};

void MdApi::processRspFASLUserLogout(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
        data["requestID"] = task_data->requestID;
        data["accountID"] = toUtf(task_data->accountID);
        data["result"] = task_data->result;
        data["rtnMsg"] = toUtf(task_data->rtnMsg);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspFASLUserLogout(data, error);
};

void MdApi::processRspStockSubMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
        data["requestID"] = task_data->requestID;
        data["securityID"] = toUtf(task_data->securityID);
        data["exchangeID"] = toUtf(task_data->exchangeID);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspStockSubMarketData(data, error);
};

void MdApi::processRspStockUnSubMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
        data["requestID"] = task_data->requestID;
        data["securityID"] = toUtf(task_data->securityID);
        data["exchangeID"] = toUtf(task_data->exchangeID);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspStockUnSubMarketData(data, error);
};

void MdApi::processRspSOPSubMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
        data["requestID"] = task_data->requestID;
        data["securityID"] = toUtf(task_data->securityID);
        data["exchangeID"] = toUtf(task_data->exchangeID);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspSOPSubMarketData(data, error);
};

void MdApi::processRspSOPUnSubMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
        data["requestID"] = task_data->requestID;
        data["securityID"] = toUtf(task_data->securityID);
        data["exchangeID"] = toUtf(task_data->exchangeID);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspSOPUnSubMarketData(data, error);
};

void MdApi::processStockMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCStockDepthMarketDataField *task_data = (DFITCStockDepthMarketDataField*)task->task_data;
        data["securityID"] = task_data->staticDataField.securityID;
        data["securityName"] = toUtf(task_data->staticDataField.securityName);
        data["tradingDay"] = task_data->staticDataField.tradingDay;
        data["exchangeID"] = toUtf(task_data->staticDataField.exchangeID);
        data["preClosePrice"] = task_data->staticDataField.preClosePrice;
        data["openPrice"] = task_data->staticDataField.openPrice;
        data["upperLimitPrice"] = task_data->staticDataField.upperLimitPrice;
        data["lowerLimitPrice"] = task_data->staticDataField.lowerLimitPrice;

        data["latestPrice"] = task_data->sharedDataField.latestPrice;
        data["turnover"] = task_data->sharedDataField.turnover;
        data["highestPrice"] = task_data->sharedDataField.highestPrice;
        data["lowestPrice"] = task_data->sharedDataField.lowestPrice;
        data["tradeQty"] = task_data->sharedDataField.tradeQty;
        data["updateTime"] = task_data->sharedDataField.updateTime;
        data["bidPrice1"] = task_data->sharedDataField.bidPrice1;
        data["bidQty1"] = task_data->sharedDataField.bidQty1;
        data["askPrice1"] = task_data->sharedDataField.askPrice1;
        data["askQty1"] = task_data->sharedDataField.askQty1;

        data["bidPrice2"] = task_data->sharedDataField.bidPrice2;
        data["bidQty2"] = task_data->sharedDataField.bidQty2;
        data["askPrice2"] = task_data->sharedDataField.askPrice2;
        data["askQty2"] = task_data->sharedDataField.askQty2;

        data["bidPrice3"] = task_data->sharedDataField.bidPrice3;
        data["bidQty3"] = task_data->sharedDataField.bidQty3;
        data["askPrice3"] = task_data->sharedDataField.askPrice3;
        data["askQty3"] = task_data->sharedDataField.askQty3;

        data["bidPrice4"] = task_data->sharedDataField.bidPrice4;
        data["bidQty4"] = task_data->sharedDataField.bidQty4;
        data["askPrice4"] = task_data->sharedDataField.askPrice4;
        data["askQty4"] = task_data->sharedDataField.askQty4;

        data["bidPrice5"] = task_data->sharedDataField.bidPrice5;
        data["bidQty5"] = task_data->sharedDataField.bidQty5;
        data["askPrice5"] = task_data->sharedDataField.askPrice5;
        data["askQty5"] = task_data->sharedDataField.askQty5;

        data["tradingPhaseCode"] = task_data->sharedDataField.tradingPhaseCode;
        delete task_data;
    }
    this->onStockMarketData(data);
};

void MdApi::processSOPMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCSOPDepthMarketDataField *task_data = (DFITCSOPDepthMarketDataField*)task->task_data;

        data["contractID"] = task_data->specificDataField.contractID;
        data["execPrice"] = task_data->specificDataField.execPrice;
        data["preSettlePrice"] = task_data->specificDataField.preSettlePrice;
        data["settlePrice"] = task_data->specificDataField.settlePrice;
        data["positionQty"] = task_data->specificDataField.positionQty;
        data["auctionPrice"] = task_data->specificDataField.auctionPrice;
        data["latestEnquiryTime"] = task_data->specificDataField.latestEnquiryTime;

        data["securityID"] = task_data->staticDataField.securityID;
        data["securityName"] = toUtf(task_data->staticDataField.securityName);
        data["tradingDay"] = task_data->staticDataField.tradingDay;
        data["exchangeID"] = toUtf(task_data->staticDataField.exchangeID);
        data["preClosePrice"] = task_data->staticDataField.preClosePrice;
        data["openPrice"] = task_data->staticDataField.openPrice;
        data["upperLimitPrice"] = task_data->staticDataField.upperLimitPrice;
        data["lowerLimitPrice"] = task_data->staticDataField.lowerLimitPrice;

        data["latestPrice"] = task_data->sharedDataField.latestPrice;
        data["turnover"] = task_data->sharedDataField.turnover;
        data["highestPrice"] = task_data->sharedDataField.highestPrice;
        data["lowestPrice"] = task_data->sharedDataField.lowestPrice;
        data["tradeQty"] = task_data->sharedDataField.tradeQty;
        data["updateTime"] = task_data->sharedDataField.updateTime;
        data["bidPrice1"] = task_data->sharedDataField.bidPrice1;
        data["bidQty1"] = task_data->sharedDataField.bidQty1;
        data["askPrice1"] = task_data->sharedDataField.askPrice1;
        data["askQty1"] = task_data->sharedDataField.askQty1;

        data["bidPrice2"] = task_data->sharedDataField.bidPrice2;
        data["bidQty2"] = task_data->sharedDataField.bidQty2;
        data["askPrice2"] = task_data->sharedDataField.askPrice2;
        data["askQty2"] = task_data->sharedDataField.askQty2;

        data["bidPrice3"] = task_data->sharedDataField.bidPrice3;
        data["bidQty3"] = task_data->sharedDataField.bidQty3;
        data["askPrice3"] = task_data->sharedDataField.askPrice3;
        data["askQty3"] = task_data->sharedDataField.askQty3;

        data["bidPrice4"] = task_data->sharedDataField.bidPrice4;
        data["bidQty4"] = task_data->sharedDataField.bidQty4;
        data["askPrice4"] = task_data->sharedDataField.askPrice4;
        data["askQty4"] = task_data->sharedDataField.askQty4;

        data["bidPrice5"] = task_data->sharedDataField.bidPrice5;
        data["bidQty5"] = task_data->sharedDataField.bidQty5;
        data["askPrice5"] = task_data->sharedDataField.askPrice5;
        data["askQty5"] = task_data->sharedDataField.askQty5;

        data["tradingPhaseCode"] = task_data->sharedDataField.tradingPhaseCode;
        delete task_data;
    }
    this->onSOPMarketData(data);
};

void MdApi::processRspStockAvailableQuot(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCRspQuotQryField *task_data = (DFITCRspQuotQryField*)task->task_data;
        data["requestID"] = task_data->requestID;
        data["accountID"] = toUtf(task_data->accountID);
        data["exchangeID"] = toUtf(task_data->exchangeID);
        data["securityID"] = toUtf(task_data->securityID);
        data["securityName"] = toUtf(task_data->securityName);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspStockAvailableQuot(data, error, task->task_last);
};

void MdApi::processRspSopAvailableQuot(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCRspQuotQryField *task_data = (DFITCRspQuotQryField*)task->task_data;
        data["requestID"] = task_data->requestID;
        data["accountID"] = toUtf(task_data->accountID);
        data["exchangeID"] = toUtf(task_data->exchangeID);
        data["securityID"] = toUtf(task_data->securityID);
        data["securityName"] = toUtf(task_data->securityName);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspSopAvailableQuot(data, error, task->task_last);
};

void MdApi::processRspUserMDPasswordUpdate(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        DFITCSECRspMDPasswordUpdateField *task_data = (DFITCSECRspMDPasswordUpdateField*)task->task_data;
        data["requestID"] = task_data->requestID;
        data["accountID"] = toUtf(task_data->accountID);
        data["result"] = task_data->result;
        data["rtnMsg"] = toUtf(task_data->rtnMsg);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
        error["requestID"] = task_error->requestID;
        error["sessionID"] = task_error->sessionID;
        error["accountID"] = toUtf(task_error->accountID);
        error["errorID"] = task_error->errorID;
        error["localOrderID"] = task_error->localOrderID;
        error["spdOrderID"] = task_error->spdOrderID;
        error["errorMsg"] = toUtf(task_error->errorMsg);
        delete task_error;
    }
    this->onRspUserMDPasswordUpdate(data, error);
};

///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::createDFITCMdApi(string pszFlowPath)
{
    this->api = DFITCSECMdApi::CreateDFITCMdApi(pszFlowPath.c_str());
};

void MdApi::release()
{
    this->api->Release();
};

int MdApi::init(string protocol)
{
    this->active = true;
    this->task_thread = thread(&MdApi::processTask, this);
    int i = this->api->Init(protocol.c_str(), this);
    return i;
};


int MdApi::exit()
{
    this->active = false;
    this->task_queue.terminate();
    this->task_thread.join();
    this->api->Release();
    this->api = NULL;
    return 1;
};


int MdApi::subscribeStockMarketData(string ppInstrumentID, int reqid)
{
    char* buffer = (char*)ppInstrumentID.c_str();
    char* myreq[1] = { buffer };
    int i = this->api->SubscribeStockMarketData(myreq, 1, reqid);
    return i;
}


int MdApi::unSubscribeStockMarketData(string ppInstrumentID, int reqid)
{
    char* buffer = (char*)ppInstrumentID.c_str();
    char* myreq[1] = { buffer };
    int i = this->api->UnSubscribeStockMarketData(myreq, 1, reqid);
    return i;
}


int MdApi::subscribeSOPMarketData(string ppInstrumentID, int reqid)
{
    char* buffer = (char*)ppInstrumentID.c_str();
    char* myreq[1] = { buffer };
    int i = this->api->SubscribeSOPMarketData(myreq, 1, reqid);
    return i;
}


int MdApi::unSubscribeSOPMarketData(string ppInstrumentID, int reqid)
{
    char* buffer = (char*)ppInstrumentID.c_str();
    char* myreq[1] = { buffer };
    int i = this->api->UnSubscribeSOPMarketData(myreq, 1, reqid);
    return i;
}

int MdApi::reqStockUserLogin(const dict &req)
{
    DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
    memset(&myreq, 0, sizeof(myreq));
    getLong(req, "requestID", &myreq.requestID);
    getString(req, "accountID", myreq.accountID);
    getString(req, "password", myreq.password);
    getInt(req, "compressflag", &myreq.compressflag);
    getString(req, "authenticCode", myreq.authenticCode);
    getString(req, "appID", myreq.appID);
    getInt(req, "collectInterType", &myreq.collectInterType);
    int i = this->api->ReqStockUserLogin(&myreq);
    return i;
};

int MdApi::reqStockUserLogout(const dict &req)
{
    DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
    memset(&myreq, 0, sizeof(myreq));
    getLong(req, "requestID", &myreq.requestID);
    getString(req, "accountID", myreq.accountID);
    int i = this->api->ReqStockUserLogout(&myreq);
    return i;
};

int MdApi::reqSOPUserLogin(const dict &req)
{
    DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
    memset(&myreq, 0, sizeof(myreq));
    getLong(req, "requestID", &myreq.requestID);
    getString(req, "accountID", myreq.accountID);
    getString(req, "password", myreq.password);
    getInt(req, "compressflag", &myreq.compressflag);
    getString(req, "authenticCode", myreq.authenticCode);
    getString(req, "appID", myreq.appID);
    getInt(req, "collectInterType", &myreq.collectInterType);
    int i = this->api->ReqSOPUserLogin(&myreq);
    return i;
};

int MdApi::reqFASLUserLogin(const dict &req)
{
    DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
    memset(&myreq, 0, sizeof(myreq));
    getLong(req, "requestID", &myreq.requestID);
    getString(req, "accountID", myreq.accountID);
    getString(req, "password", myreq.password);
    getInt(req, "compressflag", &myreq.compressflag);
    getString(req, "authenticCode", myreq.authenticCode);
    getString(req, "appID", myreq.appID);
    getInt(req, "collectInterType", &myreq.collectInterType);
    int i = this->api->ReqFASLUserLogin(&myreq);
    return i;
};

int MdApi::reqSOPUserLogout(const dict &req)
{
    DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
    memset(&myreq, 0, sizeof(myreq));
    getLong(req, "requestID", &myreq.requestID);
    getString(req, "accountID", myreq.accountID);
    int i = this->api->ReqSOPUserLogout(&myreq);
    return i;
};

int MdApi::reqFASLUserLogout(const dict &req)
{
    DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
    memset(&myreq, 0, sizeof(myreq));
    getLong(req, "requestID", &myreq.requestID);
    getString(req, "accountID", myreq.accountID);
    int i = this->api->ReqFASLUserLogout(&myreq);
    return i;
};

int MdApi::reqStockAvailableQuotQry(const dict &req)
{
    DFITCReqQuotQryField myreq = DFITCReqQuotQryField();
    memset(&myreq, 0, sizeof(myreq));
    getLong(req, "requestID", &myreq.requestID);
    getString(req, "accountID", myreq.accountID);
    getString(req, "exchangeID", myreq.exchangeID);
    int i = this->api->ReqStockAvailableQuotQry(&myreq);
    return i;
};

int MdApi::reqSopAvailableQuotQry(const dict &req)
{
    DFITCReqQuotQryField myreq = DFITCReqQuotQryField();
    memset(&myreq, 0, sizeof(myreq));
    getLong(req, "requestID", &myreq.requestID);
    getString(req, "accountID", myreq.accountID);
    getString(req, "exchangeID", myreq.exchangeID);
    int i = this->api->ReqSopAvailableQuotQry(&myreq);
    return i;
};

int MdApi::reqUserMDPasswordUpdate(const dict &req)
{
    DFITCSECReqMDPasswordUpdateField myreq = DFITCSECReqMDPasswordUpdateField();
    memset(&myreq, 0, sizeof(myreq));
    getLong(req, "requestID", &myreq.requestID);
    getString(req, "accountID", myreq.accountID);
    getString(req, "oldPassword", myreq.oldPassword);
    getString(req, "newPassword", myreq.newPassword);
    int i = this->api->ReqUserMDPasswordUpdate(&myreq);
    return i;
};


///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------
class PyMdApi : public MdApi
{
    void onFrontConnected() override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onFrontConnected);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onFrontDisconnected(int reqid) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onFrontDisconnected, reqid);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnNotice(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRtnNotice, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };



    void onRspError(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspError, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspStockUserLogin(const dict &data, const dict &error) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspStockUserLogin, data, error);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspStockUserLogout(const dict &data, const dict &error) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspStockUserLogout, data, error);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspSOPUserLogin(const dict &data, const dict &error) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspSOPUserLogin, data, error);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspSOPUserLogout(const dict &data, const dict &error) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspSOPUserLogout, data, error);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspFASLUserLogin(const dict &data, const dict &error) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspFASLUserLogin, data, error);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspFASLUserLogout(const dict &data, const dict &error) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspFASLUserLogout, data, error);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspStockSubMarketData(const dict &data, const dict &error) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspStockSubMarketData, data, error);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspStockUnSubMarketData(const dict &data, const dict &error) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspStockUnSubMarketData, data, error);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspSOPSubMarketData(const dict &data, const dict &error) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspSOPSubMarketData, data, error);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspSOPUnSubMarketData(const dict &data, const dict &error) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspSOPUnSubMarketData, data, error);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onStockMarketData(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onStockMarketData, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onSOPMarketData(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onSOPMarketData, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspStockAvailableQuot(const dict &data, const dict &error, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspStockAvailableQuot, data, error, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspSopAvailableQuot(const dict &data, const dict &error, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspSopAvailableQuot, data, error, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUserMDPasswordUpdate(const dict &data, const dict &error) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspUserMDPasswordUpdate, data, error);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };
};


PYBIND11_MODULE(vnsecmd, m)
{
    class_<MdApi, PyMdApi> mdapi(m, "MdApi", module_local());
    mdapi
        .def(init<>())
        .def("createDFITCMdApi", &MdApi::createDFITCMdApi)
        .def("release", &MdApi::release)
        .def("init", &MdApi::init)
        .def("exit", &MdApi::exit)
        .def("subscribeStockMarketData", &MdApi::subscribeStockMarketData)
        .def("unSubscribeStockMarketData", &MdApi::unSubscribeStockMarketData)
        .def("subscribeSOPMarketData", &MdApi::subscribeSOPMarketData)
        .def("unSubscribeSOPMarketData", &MdApi::unSubscribeSOPMarketData)

        .def("reqStockUserLogin", &MdApi::reqStockUserLogin)
        .def("reqStockUserLogout", &MdApi::reqStockUserLogout)
        .def("reqSOPUserLogin", &MdApi::reqSOPUserLogin)
        .def("reqFASLUserLogin", &MdApi::reqFASLUserLogin)
        .def("reqSOPUserLogout", &MdApi::reqSOPUserLogout)
        .def("reqFASLUserLogout", &MdApi::reqFASLUserLogout)
        .def("reqStockAvailableQuotQry", &MdApi::reqStockAvailableQuotQry)
        .def("reqSopAvailableQuotQry", &MdApi::reqSopAvailableQuotQry)
        .def("reqUserMDPasswordUpdate", &MdApi::reqUserMDPasswordUpdate)

        .def("onFrontConnected", &MdApi::onFrontConnected)
        .def("onFrontDisconnected", &MdApi::onFrontDisconnected)
        .def("onRtnNotice", &MdApi::onRtnNotice)
        .def("onRspError", &MdApi::onRspError)
        .def("onRspStockUserLogin", &MdApi::onRspStockUserLogin)
        .def("onRspStockUserLogout", &MdApi::onRspStockUserLogout)
        .def("onRspSOPUserLogin", &MdApi::onRspSOPUserLogin)
        .def("onRspSOPUserLogout", &MdApi::onRspSOPUserLogout)
        .def("onRspFASLUserLogin", &MdApi::onRspFASLUserLogin)
        .def("onRspFASLUserLogout", &MdApi::onRspFASLUserLogout)
        .def("onRspStockSubMarketData", &MdApi::onRspStockSubMarketData)
        .def("onRspStockUnSubMarketData", &MdApi::onRspStockUnSubMarketData)
        .def("onRspSOPSubMarketData", &MdApi::onRspSOPSubMarketData)
        .def("onRspSOPUnSubMarketData", &MdApi::onRspSOPUnSubMarketData)
        .def("onStockMarketData", &MdApi::onStockMarketData)
        .def("onSOPMarketData", &MdApi::onSOPMarketData)
        .def("onRspStockAvailableQuot", &MdApi::onRspStockAvailableQuot)
        .def("onRspSopAvailableQuot", &MdApi::onRspSopAvailableQuot)
        .def("onRspUserMDPasswordUpdate", &MdApi::onRspUserMDPasswordUpdate)

        ;
}
