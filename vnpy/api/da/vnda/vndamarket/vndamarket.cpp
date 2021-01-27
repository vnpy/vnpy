// vndamarket.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vndamarket.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void MarketApi::OnFrontConnected()
{
    gil_scoped_acquire acquire;
    this->onFrontConnected();
};

void MarketApi::OnFrontDisconnected(int iReason)
{
    gil_scoped_acquire acquire;
    this->onFrontDisconnected(iReason);
};

void MarketApi::OnHeartBeatWarning(int iTimeLapse)
{
    gil_scoped_acquire acquire;
    this->onHeartBeatWarning(iTimeLapse);
};

void MarketApi::OnRspRawData(const char* rawData)
{
    gil_scoped_acquire acquire;
    this->onRspRawData(string(rawData));
};

void MarketApi::OnRspUserLogin(CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspUserLogin(error, iRequestID, bIsLast);
};

void MarketApi::OnRspTradeDate(CMarketRspTradeDateField *pRspTradeDate, CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspTradeDate)
    {
        data["TradeDate"] = toUtf(pRspTradeDate->TradeDate);
        data["TradeProduct"] = toUtf(pRspTradeDate->TradeProduct);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspTradeDate(data, error, iRequestID, bIsLast);
};

void MarketApi::OnRspBrokerData(CMarketRspBrokerDataField *pRspBrokerData, CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspBrokerData)
    {
        data["BrokerData"] = toUtf(pRspBrokerData->BrokerData);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspBrokerData(data, error, iRequestID, bIsLast);
};

void MarketApi::OnRspMarketData(CMarketRspMarketDataField *pRspMarketData, CMarketRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspMarketData)
    {
        data["ExchangeCode"] = toUtf(pRspMarketData->ExchangeCode);
        data["TreatyCode"] = toUtf(pRspMarketData->TreatyCode);
        data["BuyPrice"] = toUtf(pRspMarketData->BuyPrice);
        data["BuyNumber"] = toUtf(pRspMarketData->BuyNumber);
        data["SalePrice"] = toUtf(pRspMarketData->SalePrice);
        data["SaleNumber"] = toUtf(pRspMarketData->SaleNumber);
        data["CurrPrice"] = toUtf(pRspMarketData->CurrPrice);
        data["CurrNumber"] = toUtf(pRspMarketData->CurrNumber);
        data["High"] = toUtf(pRspMarketData->High);
        data["Low"] = toUtf(pRspMarketData->Low);
        data["Open"] = toUtf(pRspMarketData->Open);
        data["IntradaySettlePrice"] = toUtf(pRspMarketData->IntradaySettlePrice);
        data["Close"] = toUtf(pRspMarketData->Close);
        data["Time"] = toUtf(pRspMarketData->Time);
        data["FilledNum"] = toUtf(pRspMarketData->FilledNum);
        data["HoldNum"] = toUtf(pRspMarketData->HoldNum);
        data["BuyPrice2"] = toUtf(pRspMarketData->BuyPrice2);
        data["BuyPrice3"] = toUtf(pRspMarketData->BuyPrice3);
        data["BuyPrice4"] = toUtf(pRspMarketData->BuyPrice4);
        data["BuyPrice5"] = toUtf(pRspMarketData->BuyPrice5);
        data["BuyNumber2"] = toUtf(pRspMarketData->BuyNumber2);
        data["BuyNumber3"] = toUtf(pRspMarketData->BuyNumber3);
        data["BuyNumber4"] = toUtf(pRspMarketData->BuyNumber4);
        data["BuyNumber5"] = toUtf(pRspMarketData->BuyNumber5);
        data["SalePrice2"] = toUtf(pRspMarketData->SalePrice2);
        data["SalePrice3"] = toUtf(pRspMarketData->SalePrice3);
        data["SalePrice4"] = toUtf(pRspMarketData->SalePrice4);
        data["SalePrice5"] = toUtf(pRspMarketData->SalePrice5);
        data["SaleNumber2"] = toUtf(pRspMarketData->SaleNumber2);
        data["SaleNumber3"] = toUtf(pRspMarketData->SaleNumber3);
        data["SaleNumber4"] = toUtf(pRspMarketData->SaleNumber4);
        data["SaleNumber5"] = toUtf(pRspMarketData->SaleNumber5);
        data["HideBuyPrice"] = toUtf(pRspMarketData->HideBuyPrice);
        data["HideBuyNumber"] = toUtf(pRspMarketData->HideBuyNumber);
        data["HideSalePrice"] = toUtf(pRspMarketData->HideSalePrice);
        data["HideSaleNumber"] = toUtf(pRspMarketData->HideSaleNumber);
        data["LimitDownPrice"] = toUtf(pRspMarketData->LimitDownPrice);
        data["LimitUpPrice"] = toUtf(pRspMarketData->LimitUpPrice);
        data["TradeDay"] = toUtf(pRspMarketData->TradeDay);
        data["BuyPrice6"] = toUtf(pRspMarketData->BuyPrice6);
        data["BuyPrice7"] = toUtf(pRspMarketData->BuyPrice7);
        data["BuyPrice8"] = toUtf(pRspMarketData->BuyPrice8);
        data["BuyPrice9"] = toUtf(pRspMarketData->BuyPrice9);
        data["BuyPrice10"] = toUtf(pRspMarketData->BuyPrice10);
        data["BuyNumber6"] = toUtf(pRspMarketData->BuyNumber6);
        data["BuyNumber7"] = toUtf(pRspMarketData->BuyNumber7);
        data["BuyNumber8"] = toUtf(pRspMarketData->BuyNumber8);
        data["BuyNumber9"] = toUtf(pRspMarketData->BuyNumber9);
        data["BuyNumber10"] = toUtf(pRspMarketData->BuyNumber10);
        data["SalePrice6"] = toUtf(pRspMarketData->SalePrice6);
        data["SalePrice7"] = toUtf(pRspMarketData->SalePrice7);
        data["SalePrice8"] = toUtf(pRspMarketData->SalePrice8);
        data["SalePrice9"] = toUtf(pRspMarketData->SalePrice9);
        data["SalePrice10"] = toUtf(pRspMarketData->SalePrice10);
        data["SaleNumber6"] = toUtf(pRspMarketData->SaleNumber6);
        data["SaleNumber7"] = toUtf(pRspMarketData->SaleNumber7);
        data["SaleNumber8"] = toUtf(pRspMarketData->SaleNumber8);
        data["SaleNumber9"] = toUtf(pRspMarketData->SaleNumber9);
        data["SaleNumber10"] = toUtf(pRspMarketData->SaleNumber10);
        data["TradeFlag"] = toUtf(pRspMarketData->TradeFlag);
        data["DataTimestamp"] = toUtf(pRspMarketData->DataTimestamp);
        data["DataSourceId"] = toUtf(pRspMarketData->DataSourceId);
        data["CanSellVol"] = toUtf(pRspMarketData->CanSellVol);
        data["QuoteType"] = toUtf(pRspMarketData->QuoteType);
        data["AggressorSide"] = toUtf(pRspMarketData->AggressorSide);
        data["PreSettlementPrice"] = toUtf(pRspMarketData->PreSettlementPrice);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspMarketData(data, error, iRequestID, bIsLast);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

string MarketApi::getVersion()
{
    string version = this->api->GetVersion();
    return version;
};

void MarketApi::createMarketApi(bool recordLog, string logFileName)
{
    this->api = CMarketApi::CreateMarketApi(recordLog, logFileName.c_str());
    this->api->RegisterSpi(this);
};

void MarketApi::init()
{
    this->api->Init();
};

void MarketApi::release()
{
    this->api->Release();
};

int MarketApi::exit()
{
    this->api->RegisterSpi(NULL);
    this->api->Release();
    this->api = NULL;
    return 1;
};

void MarketApi::setHeartbeatTimeout(int timeout)
{
    this->api->SetHeartbeatTimeout(timeout);
};

void MarketApi::registerNameServer(string address)
{
    this->api->RegisterNameServer(address.c_str());
};

int MarketApi::reqUserLogin(const dict &req, int reqid)
{
    CMarketReqUserLoginField myreq = CMarketReqUserLoginField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UserId", myreq.UserId);
    getString(req, "UserPwd", myreq.UserPwd);
    getString(req, "UserType", myreq.UserType);
    getString(req, "MacAddress", myreq.MacAddress);
    getString(req, "ComputerName", myreq.ComputerName);
    getString(req, "SoftwareName", myreq.SoftwareName);
    getString(req, "SoftwareVersion", myreq.SoftwareVersion);
    getString(req, "AuthorCode", myreq.AuthorCode);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqUserLogin(&myreq, reqid);
    return i;
};

int MarketApi::reqBrokerData(const dict &req, int reqid)
{
    CMarketReqBrokerDataField myreq = CMarketReqBrokerDataField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ContCode", myreq.ContCode);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqBrokerData(&myreq, reqid);
    return i;
};

int MarketApi::reqMarketData(const dict &req, int reqid)
{
    CMarketReqMarketDataField myreq = CMarketReqMarketDataField();
    memset(&myreq, 0, sizeof(myreq));
    getChar(req, "MarketType", &myreq.MarketType);
    getChar(req, "SubscMode", &myreq.SubscMode);
    getInt(req, "MarketCount", &myreq.MarketCount);
    getString(req, "MarketTrcode", myreq.MarketTrcode[0]);
    int i = this->api->ReqMarketData(&myreq, reqid);
    return i;
};


///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyMarketApi : public MarketApi
{
public:
    using MarketApi::MarketApi;

    void onFrontConnected() override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MarketApi, onFrontConnected);
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
            PYBIND11_OVERLOAD(void, MarketApi, onFrontDisconnected, reqid);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onHeartBeatWarning(int reqid) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MarketApi, onHeartBeatWarning, reqid);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspRawData(string data) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MarketApi, onRspRawData, data);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUserLogin(const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MarketApi, onRspUserLogin, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspTradeDate(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MarketApi, onRspTradeDate, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspBrokerData(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MarketApi, onRspBrokerData, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspMarketData(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, MarketApi, onRspMarketData, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };
};


PYBIND11_MODULE(vndamarket, m)
{
    class_<MarketApi, PyMarketApi> MarketApi(m, "MarketApi", module_local());
    MarketApi
        .def(init<>())
        .def("getVersion", &MarketApi::getVersion)
        .def("createMarketApi", &MarketApi::createMarketApi)
        .def("init", &MarketApi::init)
        .def("release", &MarketApi::release)
        .def("exit", &MarketApi::exit)
        .def("setHeartbeatTimeout", &MarketApi::setHeartbeatTimeout)
        .def("registerNameServer", &MarketApi::registerNameServer)
        .def("reqUserLogin", &MarketApi::reqUserLogin)
        .def("reqBrokerData", &MarketApi::reqBrokerData)
        .def("reqMarketData", &MarketApi::reqMarketData)

        .def("onFrontConnected", &MarketApi::onFrontConnected)
        .def("onFrontDisconnected", &MarketApi::onFrontDisconnected)
        .def("onHeartBeatWarning", &MarketApi::onHeartBeatWarning)
        .def("onRspRawData", &MarketApi::onRspRawData)
        .def("onRspUserLogin", &MarketApi::onRspUserLogin)
        .def("onRspTradeDate", &MarketApi::onRspTradeDate)
        .def("onRspBrokerData", &MarketApi::onRspBrokerData)
        .def("onRspMarketData", &MarketApi::onRspMarketData)
        ;

}
