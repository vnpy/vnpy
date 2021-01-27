// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnihqmd.h"


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
    task.task_extra = nReason;
    this->task_queue.push(task);
};

void MdApi::OnHeartBeatWarning(int nTimeLapse)
{
    Task task = Task();
    task.task_name = ONHEARTBEATWARNING;
    task.task_extra = nTimeLapse;
    this->task_queue.push(task);
};

void MdApi::OnRspError(CIStoneRspInfo* pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPERROR;
    if (pRspInfo)
    {
        CIStoneRspInfo *task_error = new CIStoneRspInfo();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_result = bIsLast;
    this->task_queue.push(task);
};

void MdApi::OnRspUserLogin(CIStoneRspUserLogin* pRspUserLogin, CIStoneRspInfo* pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUSERLOGIN;
    if (pRspUserLogin)
    {
        CIStoneRspUserLogin *task_data = new CIStoneRspUserLogin();
        *task_data = *pRspUserLogin;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CIStoneRspInfo *task_error = new CIStoneRspInfo();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_result = bIsLast;
    this->task_queue.push(task);
};

void MdApi::OnRspUserLogout(CIStoneRspUserLogout* pRspUserLogout, CIStoneRspInfo* pRspInfo, int nRequestID, bool bIsLast)
{
    Task task = Task();
    task.task_name = ONRSPUSERLOGOUT;
    if (pRspUserLogout)
    {
        CIStoneRspUserLogout *task_data = new CIStoneRspUserLogout();
        *task_data = *pRspUserLogout;
        task.task_data = task_data;
    }
    if (pRspInfo)
    {
        CIStoneRspInfo *task_error = new CIStoneRspInfo();
        *task_error = *pRspInfo;
        task.task_error = task_error;
    }
    task.task_id = nRequestID;
    task.task_result = bIsLast;
    this->task_queue.push(task);
};

void MdApi::OnRspSubAllMarketData(int tickType, int exchangeID, int nRequestID, bool isSuccess)
{
    Task task = Task();
    task.task_name = ONRSPSUBALLMARKETDATA;
    task.task_tick = tickType;
    task.task_exchange = exchangeID;
    task.task_id = nRequestID;
    task.task_result = isSuccess;
    this->task_queue.push(task);
};

void MdApi::OnRspUnSubAllMarketData(int tickType, int exchangeID, int nRequestID, bool isSuccess)
{
    Task task = Task();
    task.task_name = ONRSPUNSUBALLMARKETDATA;
    task.task_tick = tickType;
    task.task_exchange = exchangeID;
    task.task_id = nRequestID;
    task.task_result = isSuccess;
    this->task_queue.push(task);
};

void MdApi::OnRspSubAllTickByTick(int exchangeID, int nRequestID, bool isSuccess)
{
    Task task = Task();
    task.task_name = ONRSPSUBALLTICKBYTICK;
    task.task_exchange = exchangeID;
    task.task_id = nRequestID;
    task.task_result = isSuccess;
    this->task_queue.push(task);
};

void MdApi::OnRspUnSubAllTickByTick(int exchangeID, int nRequestID, bool isSuccess)
{
    Task task = Task();
    task.task_name = ONRSPUNSUBALLTICKBYTICK;
    task.task_exchange = exchangeID;
    task.task_id = nRequestID;
    task.task_result = isSuccess;
    this->task_queue.push(task);
};

void MdApi::OnRspSubMarketData(char* tickers[], int count, int nRequestID, bool bIsSuccess)
{
    Task task = Task();
    task.task_name = ONRSPSUBMARKETDATA;
    task.task_tickers = (char*)tickers;
    task.task_count = count;
    task.task_id = nRequestID;
    task.task_result = bIsSuccess;
    this->task_queue.push(task);
};

void MdApi::OnRspUnSubMarketData(char* tickers[], int count, int nRequestID, bool bIsSuccess)
{
    Task task = Task();
    task.task_name = ONRSPUNSUBMARKETDATA;
    task.task_tickers = (char*)tickers;
    task.task_count = count;
    task.task_id = nRequestID;
    task.task_result = bIsSuccess;
    this->task_queue.push(task);
};

void MdApi::OnRspSubTickByTick(char* tickers[], int count, int nRequestID, bool bIsSuccess)
{
    Task task = Task();
    task.task_name = ONRSPSUBTICKBYTICK;
    task.task_tickers = (char*)tickers;
    task.task_count = count;
    task.task_id = nRequestID;
    task.task_result = bIsSuccess;
    this->task_queue.push(task);
};

void MdApi::OnRspUnSubTickByTick(char* tickers[], int count, int nRequestID, bool bIsSuccess)
{
    Task task = Task();
    task.task_name = ONRSPUNSUBTICKBYTICK;
    task.task_tickers = (char*)tickers;
    task.task_count = count;
    task.task_id = nRequestID;
    task.task_result = bIsSuccess;
    this->task_queue.push(task);
};

void MdApi::OnRtnDepthMarketData(CIStoneDepthMarketData* data)
{
    Task task = Task();
    task.task_name = ONRTNDEPTHMARKETDATA;
    if (data)
    {
        CIStoneDepthMarketData *task_data = new CIStoneDepthMarketData();
        *task_data = *data;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};

void MdApi::OnRtnTickByTick(CIStoneTickByTick* data)
{
    Task task = Task();
    task.task_name = ONRTNTICKBYTICK;
    if (data)
    {
        CIStoneTickByTick *task_data = new CIStoneTickByTick();
        *task_data = *data;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};

void MdApi::OnRtnOrderBook(CIStoneOrderBook* data)
{
    Task task = Task();
    task.task_name = ONRTNORDERBOOK;
    if (data)
    {
        CIStoneOrderBook *task_data = new CIStoneOrderBook();
        *task_data = *data;
        task.task_data = task_data;
    }
    this->task_queue.push(task);
};

void MdApi::OnRspSubOrderBook(char* tickers[], int count, int nRequestID, bool bIsSuccess)
{
    Task task = Task();
    task.task_name = ONRSPSUBORDERBOOK;
    task.task_tickers = (char*)tickers;
    task.task_count = count;
    task.task_id = nRequestID;
    task.task_result = bIsSuccess;
    this->task_queue.push(task);
};

void MdApi::OnRspUnSubOrderBook(char* tickers[], int count, int nRequestID, bool bIsSuccess)
{
    Task task = Task();
    task.task_name = ONRSPUNSUBORDERBOOK;
    task.task_tickers = (char*)tickers;
    task.task_count = count;
    task.task_id = nRequestID;
    task.task_result = bIsSuccess;
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

            case ONHEARTBEATWARNING:
            {
                this->processHeartBeatWarning(&task);
                break;
            }

            case ONRSPERROR:
            {
                this->processRspError(&task);
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

            case ONRSPSUBALLMARKETDATA:
            {
                this->processRspSubAllMarketData(&task);
                break;
            }

            case ONRSPUNSUBALLMARKETDATA:
            {
                this->processRspUnSubAllMarketData(&task);
                break;
            }

            case ONRSPSUBALLTICKBYTICK:
            {
                this->processRspSubAllTickByTick(&task);
                break;
            }

            case ONRSPUNSUBALLTICKBYTICK:
            {
                this->processRspUnSubAllTickByTick(&task);
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

            case ONRSPSUBTICKBYTICK:
            {
                this->processRspSubTickByTick(&task);
                break;
            }

            case ONRSPUNSUBTICKBYTICK:
            {
                this->processRspUnSubTickByTick(&task);
                break;
            }

            case ONRTNDEPTHMARKETDATA:
            {
                this->processRtnDepthMarketData(&task);
                break;
            }

            case ONRTNTICKBYTICK:
            {
                this->processRtnTickByTick(&task);
                break;
            }

            case ONRTNORDERBOOK:
            {
                this->processRtnOrderBook(&task);
                break;
            }

            case ONRSPSUBORDERBOOK:
            {
                this->processRspSubOrderBook(&task);
                break;
            }

            case ONRSPUNSUBORDERBOOK:
            {
                this->processRspUnSubOrderBook(&task);
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
    this->onFrontDisconnected(task->task_extra);
};

void MdApi::processHeartBeatWarning(Task *task)
{
    gil_scoped_acquire acquire;
    this->onHeartBeatWarning(task->task_extra);
};

void MdApi::processRspError(Task *task)
{
    gil_scoped_acquire acquire;
    dict error;
    if (task->task_error)
    {
        CIStoneRspInfo *task_error = (CIStoneRspInfo*)task->task_error;
        error["Tid"] = task_error->Tid;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = task_error->ErrorMsg;
        delete task_error;
    }
    this->onRspError(error, task->task_id, task->task_result);
};

void MdApi::processRspUserLogin(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CIStoneRspUserLogin *task_data = (CIStoneRspUserLogin*)task->task_data;
        data["TradingDay"] = task_data->TradingDay;
        data["UserID"] = task_data->UserID;
        data["MaxUserOrderLocalID"] = task_data->MaxUserOrderLocalID;
        data["LoginTime"] = task_data->LoginTime;
        data["userType"] = task_data->userType;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CIStoneRspInfo *task_error = (CIStoneRspInfo*)task->task_error;
        error["Tid"] = task_error->Tid;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = task_error->ErrorMsg;
        delete task_error;
    }
    this->onRspUserLogin(data, error, task->task_id, task->task_result);
};

void MdApi::processRspUserLogout(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CIStoneRspUserLogout *task_data = (CIStoneRspUserLogout*)task->task_data;
        data["UserID"] = task_data->UserID;
        delete task_data;
    }
    dict error;
    if (task->task_error)
    {
        CIStoneRspInfo *task_error = (CIStoneRspInfo*)task->task_error;
        error["Tid"] = task_error->Tid;
        error["ErrorID"] = task_error->ErrorID;
        error["ErrorMsg"] = task_error->ErrorMsg;
        delete task_error;
    }
    this->onRspUserLogout(data, error, task->task_id, task->task_result);
};

void MdApi::processRspSubAllMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    this->onRspSubAllMarketData(task->task_tick, task->task_exchange, task->task_id, task->task_result);
};

void MdApi::processRspUnSubAllMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    this->onRspUnSubAllMarketData(task->task_tick, task->task_exchange, task->task_id, task->task_result);
};

void MdApi::processRspSubAllTickByTick(Task *task)
{
    gil_scoped_acquire acquire;
    this->onRspSubAllTickByTick(task->task_exchange, task->task_id, task->task_result);
};

void MdApi::processRspUnSubAllTickByTick(Task *task)
{
    gil_scoped_acquire acquire;
    this->onRspUnSubAllTickByTick(task->task_exchange, task->task_id, task->task_result);
};

void MdApi::processRspSubMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    this->onRspSubMarketData(task->task_tickers, task->task_count, task->task_id, task->task_result);
};

void MdApi::processRspUnSubMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    this->onRspUnSubMarketData(task->task_tickers, task->task_count, task->task_id, task->task_result);
};

void MdApi::processRspSubTickByTick(Task *task)
{
    gil_scoped_acquire acquire;
    this->onRspSubTickByTick(task->task_tickers, task->task_count, task->task_id, task->task_result);
};

void MdApi::processRspUnSubTickByTick(Task *task)
{
    gil_scoped_acquire acquire;
    this->onRspUnSubTickByTick(task->task_tickers, task->task_count, task->task_id, task->task_result);
};

void MdApi::processRtnDepthMarketData(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CIStoneDepthMarketData *task_data = (CIStoneDepthMarketData*)task->task_data;
        data["ExchangeID"] = task_data->ExchangeID;
        data["TickerType"] = task_data->TickerType;
        data["Ticker"] = task_data->Ticker;
        data["LastPrice"] = task_data->LastPrice;
        data["PreClosePrice"] = task_data->PreClosePrice;
        data["OpenPrice"] = task_data->OpenPrice;
        data["HighestPrice"] = task_data->HighestPrice;
        data["LowestPrice"] = task_data->LowestPrice;
        data["ClosePrice"] = task_data->ClosePrice;
        data["PreOpenInterest"] = task_data->PreOpenInterest;
        data["OpenInterest"] = task_data->OpenInterest;
        data["PreSettlementPrice"] = task_data->PreSettlementPrice;
        data["SettlementPrice"] = task_data->SettlementPrice;
        data["PreDelta"] = task_data->PreDelta;
        data["CurrDelta"] = task_data->CurrDelta;
        data["UpperLimitPrice"] = task_data->UpperLimitPrice;
        data["LowerLimitPrice"] = task_data->LowerLimitPrice;
        data["DateTime"] = task_data->DateTime;
        data["Qty"] = task_data->Qty;
        data["Turnover"] = task_data->Turnover;
        data["AvgPrice"] = task_data->AvgPrice;
        //data["Bid"] = task_data->Bid;
        //data["Ask"] = task_data->Ask;
        //data["BidQty"] = task_data->BidQty;
        //data["AskQty"] = task_data->AskQty;
        data["TradesCount"] = task_data->TradesCount;
        data["TickerStatus"] = task_data->TickerStatus;
        data["tickBid1"] = task_data->tickBid1;
        data["DataType"] = task_data->DataType;
        data["Stk"] = task_data->Stk;
        data["Opt"] = task_data->Opt;
        data["R4"] = task_data->R4;

        pybind11::list Ask;
        pybind11::list Bid;
        pybind11::list AskQty;
        pybind11::list BidQty;

        for (int i = 0; i < 10; i++)
        {
            Ask.append(task_data->Ask[i]);
            Bid.append(task_data->Bid[i]);
            AskQty.append(task_data->AskQty[i]);
            BidQty.append(task_data->BidQty[i]);
        }

        data["Ask"] = Ask;
        data["Bid"] = Bid;
        data["BidQty"] = BidQty;
        data["AskQty"] = AskQty;

        delete task_data;
    }
    this->onRtnDepthMarketData(data);
};

void MdApi::processRtnTickByTick(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CIStoneTickByTick *task_data = (CIStoneTickByTick*)task->task_data;
        data["ExchangeID"] = task_data->ExchangeID;
        data["Ticker"] = task_data->Ticker;
        data["Seq"] = task_data->Seq;
        data["DataTime"] = task_data->DataTime;
        data["Type"] = task_data->Type;
        data["Entrust"] = task_data->Entrust;
        data["Trade"] = task_data->Trade;
        delete task_data;
    }
    this->onRtnTickByTick(data);
};

void MdApi::processRtnOrderBook(Task *task)
{
    gil_scoped_acquire acquire;
    dict data;
    if (task->task_data)
    {
        CIStoneOrderBook *task_data = (CIStoneOrderBook*)task->task_data;
        data["ExchangeID"] = task_data->ExchangeID;
        data["Ticker"] = task_data->Ticker;
        data["LastPrice"] = task_data->LastPrice;
        data["Qty"] = task_data->Qty;
        data["Turnover"] = task_data->Turnover;
        data["TradesCount"] = task_data->TradesCount;
        data["Bid"] = task_data->Bid;
        data["Ask"] = task_data->Ask;
        data["BidQty"] = task_data->BidQty;
        data["AskQty"] = task_data->AskQty;
        data["DataTime"] = task_data->DataTime;
        data["bidSeq"] = task_data->bidSeq;
        data["askSeq"] = task_data->askSeq;
        delete task_data;
    }
    this->onRtnOrderBook(data);
};

void MdApi::processRspSubOrderBook(Task *task)
{
    gil_scoped_acquire acquire;
    this->onRspSubOrderBook(task->task_tickers, task->task_count, task->task_id, task->task_result);
};

void MdApi::processRspUnSubOrderBook(Task *task)
{
    gil_scoped_acquire acquire;
    this->onRspUnSubOrderBook(task->task_tickers, task->task_count, task->task_id, task->task_result);
};



///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::createMdUserApi(string pszFlowPath)
{
    this->api = IStoneMdApi::CreateMdUserApi(pszFlowPath.c_str());
    this->api->RegisterSpi(this);
};

void MdApi::release()
{
    this->api->Release();
};

void MdApi::init()
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

string MdApi::getTradingDay()
{
    string day = this->api->GetTradingDay();
    return day;
};

void MdApi::registerFront(string pszFrontAddress)
{
    this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

void MdApi::registerFpgaFront(string pMutilcastAddr)
{
    this->api->RegisterFpgaFront((char*)pMutilcastAddr.c_str());
};

void MdApi::registerTcpLocalAddr(string localTcpAddr)
{
    this->api->RegisterTcpLocalAddr((char*)localTcpAddr.c_str());
};


void MdApi::registerUdpLocalAddr(string localTcpAddr)
{
    this->api->RegisterUdpLocalAddr((char*)localTcpAddr.c_str());
};

void MdApi::registerEfviDevice(string localTcpAddr)
{
    this->api->RegisterEfviDevice((char*)localTcpAddr.c_str());
};

void MdApi::setHeartbeatTimeout(uint32_t timeout)
{
    this->api->SetHeartbeatTimeout(timeout);
};


int MdApi::reqUserLogin(const dict &req, int reqid)
{
    CIStoneReqUserLogin myreq = CIStoneReqUserLogin();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "TradingDay", myreq.TradingDay);
    getString(req, "UserID", myreq.UserID);
    getString(req, "Password", myreq.Password);
    getString(req, "UserProductInfo", myreq.UserProductInfo);
    getString(req, "IPAddress", myreq.IPAddress);
    getString(req, "MacAddress", myreq.MacAddress);
    int i = this->api->ReqUserLogin(&myreq, reqid);
    return i;
};

int MdApi::reqUserLogout(const dict &req, int reqid)
{
    CIStoneReqUserLogout myreq = CIStoneReqUserLogout();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UserID", myreq.UserID);
    int i = this->api->ReqUserLogout(&myreq, reqid);
    return i;
};


int MdApi::subAllMarketData(int tickType, int exchangeID, int nRequestID)
{
    int i = this->api->SubAllMarketData(tickType, exchangeID, nRequestID);
    return i;
};


int MdApi::unSubAllMarketData(int tickType, int exchangeID, int nRequestID)
{
    int i = this->api->UnSubAllMarketData(tickType, exchangeID, nRequestID);
    return i;
};

int MdApi::subAllTickByTick(int exchangeID, int nRequestID)
{
    int i = this->api->SubAllTickByTick(exchangeID, nRequestID);
    return i;
};

int MdApi::unSubAllTickByTick(int exchangeID, int nRequestID)
{
    int i = this->api->UnSubAllTickByTick(exchangeID, nRequestID);
    return i;
};

int MdApi::subMarketData(string ppInstrumentID, int nRequestID)
{

    char* buffer = (char*)ppInstrumentID.c_str();
    char* myreq[1] = { buffer };
    int i = this->api->SubMarketData(myreq, 1, nRequestID);
    return i;
};
int MdApi::unSubMarketData(string ppInstrumentID, int nRequestID)
{

    char* buffer = (char*)ppInstrumentID.c_str();
    char* myreq[1] = { buffer };
    int i = this->api->UnSubMarketData(myreq, 1, nRequestID);
    return i;
};

int MdApi::subTickByTick(string ppInstrumentID, int nRequestID)
{

    char* buffer = (char*)ppInstrumentID.c_str();
    char* myreq[1] = { buffer };
    int i = this->api->SubTickByTick(myreq, 1, nRequestID);
    return i;
};

int MdApi::unSubTickByTick(string ppInstrumentID, int nRequestID)
{

    char* buffer = (char*)ppInstrumentID.c_str();
    char* myreq[1] = { buffer };
    int i = this->api->UnSubTickByTick(myreq, 1, nRequestID);
    return i;
};

int MdApi::subAllOrderBook(int exchangeID, int nRequestID)
{
    int i = this->api->SubAllOrderBook(exchangeID, nRequestID);
    return i;
};

int MdApi::unSubAllOrderBook(int exchangeID, int nRequestID)
{
    int i = this->api->UnSubAllOrderBook(exchangeID, nRequestID);
    return i;
};

int MdApi::subOrderBook(string ppInstrumentID, int nRequestID)
{
    char* buffer = (char*)ppInstrumentID.c_str();
    char* myreq[1] = { buffer };
    int i = this->api->SubOrderBook(myreq, 1, nRequestID);
    return i;
};

int MdApi::unSubOrderBook(string ppInstrumentID,int nRequestID)
{
    char* buffer = (char*)ppInstrumentID.c_str();
    char* myreq[1] = { buffer };
    int i = this->api->UnSubOrderBook(myreq, 1, nRequestID);
    return i;
};



///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyMdApi: public MdApi
{
public:
    using MdApi::MdApi;

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

    void onFrontDisconnected(int extra) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onFrontDisconnected, extra);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onHeartBeatWarning(int extra) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onHeartBeatWarning, extra);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspError(const dict &error, int reqid, bool result) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspError, error, reqid, result);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUserLogin(const dict &data, const dict &error, int reqid, bool result) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspUserLogin, data, error, reqid, result);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUserLogout(const dict &data, const dict &error, int reqid, bool result) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspUserLogout, data, error, reqid, result);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspSubAllMarketData(int tick, int exchange, int reqid, bool result) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspSubAllMarketData, tick, exchange, reqid, result);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUnSubAllMarketData(int tick, int exchange, int reqid, bool result) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspUnSubAllMarketData, tick, exchange, reqid, result);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspSubAllTickByTick(int exchange, int reqid, bool result) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspSubAllTickByTick, exchange, reqid, result);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUnSubAllTickByTick(int exchange, int reqid, bool result) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspUnSubAllTickByTick, exchange, reqid, result);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspSubMarketData(string tickers, int count, int reqid, bool result) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspSubMarketData, tickers, count, reqid, result);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUnSubMarketData(string tickers, int count, int reqid, bool result) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspUnSubMarketData, tickers, count, reqid, result);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspSubTickByTick(string tickers, int count, int reqid, bool result) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspSubTickByTick, tickers, count, reqid, result);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUnSubTickByTick(string tickers, int count, int reqid, bool result) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspUnSubTickByTick, tickers, count, reqid, result);
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

    void onRtnTickByTick(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRtnTickByTick, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnOrderBook(const dict &data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRtnOrderBook, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspSubOrderBook(string tickers, int count, int reqid, bool result) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspSubOrderBook, tickers, count, reqid, result);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUnSubOrderBook(string tickers, int count, int reqid, bool result) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MdApi, onRspUnSubOrderBook, tickers, count, reqid, result);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };


};


PYBIND11_MODULE(vnihqmd, m)
{
    class_<MdApi, PyMdApi> mdapi(m, "MdApi", module_local());
    mdapi
        .def(init<>())
        .def("createMdUserApi", &MdApi::createMdUserApi)
        .def("release", &MdApi::release)
        .def("init", &MdApi::init)
        .def("join", &MdApi::join)
        .def("exit", &MdApi::exit)
        .def("getTradingDay", &MdApi::getTradingDay)
        .def("registerFront", &MdApi::registerFront)
        .def("registerFpgaFront", &MdApi::registerFpgaFront)
        .def("registerTcpLocalAddr", &MdApi::registerTcpLocalAddr)
        .def("registerUdpLocalAddr", &MdApi::registerUdpLocalAddr)
        .def("registerEfviDevice", &MdApi::registerEfviDevice)
        .def("setHeartbeatTimeout", &MdApi::setHeartbeatTimeout)

        .def("reqUserLogin", &MdApi::reqUserLogin)
        .def("reqUserLogout", &MdApi::reqUserLogout)

        .def("subAllMarketData", &MdApi::subAllMarketData)
        .def("unSubAllMarketData", &MdApi::unSubAllMarketData)
        .def("subAllTickByTick", &MdApi::subAllTickByTick)
        .def("unSubAllTickByTick", &MdApi::unSubAllTickByTick)
        .def("subMarketData", &MdApi::subMarketData)
        .def("unSubMarketData", &MdApi::unSubMarketData)
        .def("subTickByTick", &MdApi::subTickByTick)
        .def("unSubTickByTick", &MdApi::unSubTickByTick)
        .def("subAllOrderBook", &MdApi::subAllOrderBook)
        .def("unSubAllOrderBook", &MdApi::unSubAllOrderBook)
        .def("subOrderBook", &MdApi::subOrderBook)
        .def("unSubOrderBook", &MdApi::unSubOrderBook)

        .def("onFrontConnected", &MdApi::onFrontConnected)
        .def("onFrontDisconnected", &MdApi::onFrontDisconnected)
        .def("onHeartBeatWarning", &MdApi::onHeartBeatWarning)
        .def("onRspError", &MdApi::onRspError)
        .def("onRspUserLogin", &MdApi::onRspUserLogin)
        .def("onRspUserLogout", &MdApi::onRspUserLogout)
        .def("onRspSubAllMarketData", &MdApi::onRspSubAllMarketData)
        .def("onRspUnSubAllMarketData", &MdApi::onRspUnSubAllMarketData)
        .def("onRspSubAllTickByTick", &MdApi::onRspSubAllTickByTick)
        .def("onRspUnSubAllTickByTick", &MdApi::onRspUnSubAllTickByTick)
        .def("onRspSubMarketData", &MdApi::onRspSubMarketData)
        .def("onRspUnSubMarketData", &MdApi::onRspUnSubMarketData)
        .def("onRspSubTickByTick", &MdApi::onRspSubTickByTick)
        .def("onRspUnSubTickByTick", &MdApi::onRspUnSubTickByTick)
        .def("onRtnDepthMarketData", &MdApi::onRtnDepthMarketData)
        .def("onRtnTickByTick", &MdApi::onRtnTickByTick)
        .def("onRtnOrderBook", &MdApi::onRtnOrderBook)
        .def("onRspSubOrderBook", &MdApi::onRspSubOrderBook)
        .def("onRspUnSubOrderBook", &MdApi::onRspUnSubOrderBook)
        ;

}
