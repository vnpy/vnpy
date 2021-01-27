// vnuftmd.cpp : 定义 DLL 应用程序的导出函数。
//
#include "vnksgoldmd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void MdApi::OnFrontConnected(int nResult)
{
    Task task = Task();
    task.task_name = ONFRONTCONNECTED;
    task.task_id = nResult;
    this->task_queue.push(task);
};

void MdApi::OnFrontDisconnected(int nReason)
{
    Task task = Task();
    task.task_name = ONFRONTDISCONNECTED;
    task.task_id = nReason;
    this->task_queue.push(task);
};

void MdApi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUSERLOGIN;
    if (pRspUserLogin)
    {
        CThostFtdcRspUserLoginField *task_data = new CThostFtdcRspUserLoginField();
        *task_data = *pRspUserLogin;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void MdApi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUSERLOGOUT;
    if (pUserLogout)
    {
        CThostFtdcUserLogoutField *task_data = new CThostFtdcUserLogoutField();
        *task_data = *pUserLogout;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void MdApi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPERROR;
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void MdApi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPSUBMARKETDATA;
    if (pSpecificInstrument)
    {
        CThostFtdcSpecificInstrumentField *task_data = new CThostFtdcSpecificInstrumentField();
        *task_data = *pSpecificInstrument;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void MdApi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUNSUBMARKETDATA;
    if (pSpecificInstrument)
    {
        CThostFtdcSpecificInstrumentField *task_data = new CThostFtdcSpecificInstrumentField();
        *task_data = *pSpecificInstrument;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CThostFtdcRspInfoField *task_error = new CThostFtdcRspInfoField();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_last = bIsLast;
    this->task_queue.push(task);
};

void MdApi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    Task task = Task();
    task.task_name = ONRTNDEPTHMARKETDATA;
    if (pDepthMarketData)
    {
        CThostFtdcDepthMarketDataField *task_data = new CThostFtdcDepthMarketDataField();
        *task_data = *pDepthMarketData;
        task.task_data = task_data;
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

            case ONRSPUSERLOGIN:
            {
                this->processRspUserLogin(&task);
                break;
            }

            case ONRSPUSERLOGOUT:
            {
                this->processRspUserLogout(&task);
                break;
            }

            case ONRSPERROR:
            {
                this->processRspError(&task);
                break;
            }

            case ONRSPSUBMARKETDATA:
            {
                this->processRspSubMarketData(&task);
                break;
            }

            case ONRSPUNSUBMARKETDATA:
            {
                this->processRspUnSubMarketData(&task);
                break;
            }

            case ONRTNDEPTHMARKETDATA:
            {
                this->processRtnDepthMarketData(&task);
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
    this->onFrontConnected(task->task_id);
};

void MdApi::processFrontDisconnected(Task *task)
{
    gil_scoped_acquire acquire;
    this->onFrontDisconnected(task->task_id);
};

void MdApi::processRspUserLogin(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CThostFtdcRspUserLoginField *task_data = (CThostFtdcRspUserLoginField*)task->task_data;
        data["TradeDate"] = toUtf(task_data->TradeDate);
        data["SessionID"] = task_data->SessionID;
        data["ClientID"] = toUtf(task_data->ClientID);
        data["clientName"] = toUtf(task_data->clientName);
        data["TradeCode"] = toUtf(task_data->TradeCode);
        data["SeatNo"] = toUtf(task_data->SeatNo);
        data["lastLoginIp"] = toUtf(task_data->lastLoginIp);
        data["lastLoginDate"] = toUtf(task_data->lastLoginDate);
        data["lastLoginTime"] = toUtf(task_data->lastLoginTime);
        data["AccountID"] = toUtf(task_data->AccountID);
        data["LoginType"] = task_data->LoginType;
        data["Password"] = toUtf(task_data->Password);
        data["MacAddress"] = toUtf(task_data->MacAddress);
        data["LoginIp"] = toUtf(task_data->LoginIp);
        data["UserProductionInfo"] = toUtf(task_data->UserProductionInfo);
        data["ProtocolInfo"] = toUtf(task_data->ProtocolInfo);
        data["SystemName"] = toUtf(task_data->SystemName);
        data["FrontID"] = task_data->FrontID;
        data["MaxOrderRef"] = toUtf(task_data->MaxOrderRef);
        data["SgeTime"] = toUtf(task_data->SgeTime);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspUserLogin(data, error, task->task_id, task->task_last);
};

void MdApi::processRspUserLogout(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CThostFtdcUserLogoutField *task_data = (CThostFtdcUserLogoutField*)task->task_data;
        data["LoginIp"] = toUtf(task_data->LoginIp);
        data["MacAddress"] = toUtf(task_data->MacAddress);
        data["ClientID"] = toUtf(task_data->ClientID);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspUserLogout(data, error, task->task_id, task->task_last);
};

void MdApi::processRspError(Task *task)
{
    gil_scoped_acquire acquire;
    dict error;
    if (task->task_error)
    {
        CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspError(error, task->task_id, task->task_last);
};

void MdApi::processRspSubMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CThostFtdcSpecificInstrumentField *task_data = (CThostFtdcSpecificInstrumentField*)task->task_data;
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspSubMarketData(data, error, task->task_id, task->task_last);
};

void MdApi::processRspUnSubMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CThostFtdcSpecificInstrumentField *task_data = (CThostFtdcSpecificInstrumentField*)task->task_data;
        data["InstrumentID"] = toUtf(task_data->InstrumentID);
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
        delete task_error;
    }
    this->onRspUnSubMarketData(data, error, task->task_id, task->task_last);
};

void MdApi::processRtnDepthMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CThostFtdcDepthMarketDataField *task_data = (CThostFtdcDepthMarketDataField*)task->task_data;
        data["InstID"] = toUtf(task_data->InstID);
        data["Name"] = toUtf(task_data->Name);
        data["MarketName"] = toUtf(task_data->MarketName);
        data["PreSettle"] = task_data->PreSettle;
        data["PreClose"] = task_data->PreClose;
        data["Open"] = task_data->Open;
        data["High"] = task_data->High;
        data["Low"] = task_data->Low;
        data["Last"] = task_data->Last;
        data["Close"] = task_data->Close;
        data["Bid1"] = task_data->Bid1;
        data["BidLot1"] = task_data->BidLot1;
        data["Ask1"] = task_data->Ask1;
        data["AskLot1"] = task_data->AskLot1;
        data["Bid2"] = task_data->Bid2;
        data["BidLot2"] = task_data->BidLot2;
        data["Ask2"] = task_data->Ask2;
        data["AskLot2"] = task_data->AskLot2;
        data["Bid3"] = task_data->Bid3;
        data["BidLot3"] = task_data->BidLot3;
        data["Ask3"] = task_data->Ask3;
        data["AskLot3"] = task_data->AskLot3;
        data["Bid4"] = task_data->Bid4;
        data["BidLot4"] = task_data->BidLot4;
        data["Ask4"] = task_data->Ask4;
        data["AskLot4"] = task_data->AskLot4;
        data["Bid5"] = task_data->Bid5;
        data["BidLot5"] = task_data->BidLot5;
        data["Ask5"] = task_data->Ask5;
        data["AskLot5"] = task_data->AskLot5;
        data["Bid6"] = task_data->Bid6;
        data["BidLot6"] = task_data->BidLot6;
        data["Ask6"] = task_data->Ask6;
        data["AskLot6"] = task_data->AskLot6;
        data["Bid7"] = task_data->Bid7;
        data["BidLot7"] = task_data->BidLot7;
        data["Ask7"] = task_data->Ask7;
        data["AskLot7"] = task_data->AskLot7;
        data["Bid8"] = task_data->Bid8;
        data["BidLot8"] = task_data->BidLot8;
        data["Ask8"] = task_data->Ask8;
        data["AskLot8"] = task_data->AskLot8;
        data["Bid9"] = task_data->Bid9;
        data["BidLot9"] = task_data->BidLot9;
        data["Ask9"] = task_data->Ask9;
        data["AskLot9"] = task_data->AskLot9;
        data["Bid10"] = task_data->Bid10;
        data["BidLot10"] = task_data->BidLot10;
        data["Ask10"] = task_data->Ask10;
        data["AskLot10"] = task_data->AskLot10;
        data["Volume"] = task_data->Volume;
        data["OpenInt"] = task_data->OpenInt;
        data["UpDown"] = task_data->UpDown;
        data["Turnover"] = task_data->Turnover;
        data["Settle"] = task_data->Settle;
        data["Average"] = task_data->Average;
        data["QuoteDate"] = toUtf(task_data->QuoteDate);
        data["QuoteTime"] = toUtf(task_data->QuoteTime);
        data["weight"] = task_data->weight;
        data["highLimit"] = task_data->highLimit;
        data["lowLimit"] = task_data->lowLimit;
        data["UpDownRate"] = task_data->UpDownRate;
        delete task_data;
    }
    this->onRtnDepthMarketData(data);
};




///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::release()
{
    this->api->Release();
};

bool MdApi::init()
{
    this->active = true;
    this->task_thread = thread(&MdApi::processTask, this);
    this->api->Init();
};

int MdApi::join()
{
    int i = this->api->Join();
        return i;
};

int MdApi::exit()
{
    this->active = false;
    this->task_queue.terminate();
    this->task_thread.join();

    this->api->RegisterSpi(NULL);
    this->api->Release();
    this->api = NULL;
    return 1;
};

void MdApi::registerFront(string pszFrontAddress)
{
    this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

void MdApi::createGoldQutoApi(string pszFlowPath)
{
    this->api = CKSGoldQuotApi::CreateGoldQutoApi(pszFlowPath.c_str());
    this->api->RegisterSpi(this);
};

int MdApi::subscribeMarketData(string ppInstrumentID, int reqid)
{
    char* buffer = (char*)ppInstrumentID.c_str();
    char* myreq[1] = { buffer };
    cout << "myreq=" <<myreq <<endl;
    int i = this->api->SubscribeMarketData(myreq, 1 , reqid);
    return i;
};

int MdApi::unSubscribeMarketData(string ppInstrumentID, int reqid)
{
    char* buffer = (char*)ppInstrumentID.c_str();
    char* myreq[1] = { buffer };
    int i = this->api->UnSubscribeMarketData(myreq, 1, reqid);
    return i;
};

int MdApi::reqUserLogin(const dict &req, int reqid)
{
    CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "AccountID", myreq.AccountID);
    getInt(req, "LoginType", &myreq.LoginType);

    getString(req, "Password", myreq.Password);
    getString(req, "LoginIp", myreq.LoginIp);
    getString(req, "MacAddress", myreq.MacAddress);
    getString(req, "UserProductionInfo", myreq.UserProductionInfo);
    getString(req, "ProtocolInfo", myreq.ProtocolInfo);
    
    int i = this->api->ReqUserLogin(&myreq, reqid);
    return i;
};


int MdApi::reqUserLogout(const dict &req, int reqid)
{
    CThostFtdcUserLogoutField myreq = CThostFtdcUserLogoutField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "LoginIp", myreq.LoginIp);
    getString(req, "MacAddress", myreq.MacAddress);
    getString(req, "ClientID", myreq.ClientID);
    int i = this->api->ReqUserLogout(&myreq, reqid);
    return i;
};




///-------------------------------------------------------------------------------------
///Pybind11封装
///-------------------------------------------------------------------------------------

class PyMdApi: public MdApi
{
public:
    using MdApi::MdApi;

    void onFrontConnected(int reqid) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onFrontConnected, reqid);
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

    void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspUserLogin, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspUserLogout, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspError(const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspError, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspSubMarketData(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspSubMarketData, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUnSubMarketData(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspUnSubMarketData, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnDepthMarketData(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRtnDepthMarketData, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };


};


PYBIND11_MODULE(vnksgoldmd, m)
{
    class_<MdApi, PyMdApi> mdapi(m, "MdApi", module_local());
    mdapi
        .def(init<>())
        .def("release", &MdApi::release)
        .def("init", &MdApi::init)
        .def("join", &MdApi::join)
        .def("registerFront", &MdApi::registerFront)
        .def("exit", &MdApi::exit)
        .def("createGoldQutoApi", &MdApi::createGoldQutoApi)
        .def("subscribeMarketData", &MdApi::subscribeMarketData)
        .def("unSubscribeMarketData", &MdApi::unSubscribeMarketData)
        .def("reqUserLogin", &MdApi::reqUserLogin)
        .def("reqUserLogout", &MdApi::reqUserLogout)

        .def("onFrontConnected", &MdApi::onFrontConnected)
        .def("onFrontDisconnected", &MdApi::onFrontDisconnected)
        .def("onRspUserLogin", &MdApi::onRspUserLogin)
        .def("onRspUserLogout", &MdApi::onRspUserLogout)
        .def("onRspError", &MdApi::onRspError)
        .def("onRspSubMarketData", &MdApi::onRspSubMarketData)
        .def("onRspUnSubMarketData", &MdApi::onRspUnSubMarketData)
        .def("onRtnDepthMarketData", &MdApi::onRtnDepthMarketData)
        ;


}
