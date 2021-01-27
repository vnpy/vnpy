#include "stdafx.h"
#include "vndafuture.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void FutureApi::OnFrontConnected()
{
    gil_scoped_acquire acquire;
    this->onFrontConnected();
};

void FutureApi::OnFrontDisconnected(int iReason)
{
    gil_scoped_acquire acquire;
    this->onFrontDisconnected(iReason);
};

void FutureApi::OnHeartBeatWarning(int iTimeLapse)
{
    gil_scoped_acquire acquire;
    this->onHeartBeatWarning(iTimeLapse);
};

void FutureApi::OnRspNeedVerify(bool bFirstLogin, bool bHasSetQA)
{
    gil_scoped_acquire acquire;
    this->onRspNeedVerify(bFirstLogin, bHasSetQA);
};

void FutureApi::OnRspUserLogin(CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
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

void FutureApi::OnRspUserLogout(CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspUserLogout(error, iRequestID, bIsLast);
};

void FutureApi::OnRspVerifyCode(CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspVerifyCode(error, iRequestID, bIsLast);
};

void FutureApi::OnRspSafeVerify(CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspSafeVerify(error, iRequestID, bIsLast);
};

void FutureApi::OnRspSetVerifyQA(CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspSetVerifyQA(error, iRequestID, bIsLast);
};

void FutureApi::OnRspAccount(CFutureRspAccountField *pRspAccount, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspAccount)
    {
        data["UserId"] = toUtf(pRspAccount->UserId);
        data["UserName"] = toUtf(pRspAccount->UserName);
        data["UserType"] = toUtf(pRspAccount->UserType);
        data["LoginPwd"] = toUtf(pRspAccount->LoginPwd);
        data["AccountNo"] = toUtf(pRspAccount->AccountNo);
        data["TradePwd"] = toUtf(pRspAccount->TradePwd);
        data["IsSimulation"] = toUtf(pRspAccount->IsSimulation);
        data["FrontendIp"] = toUtf(pRspAccount->FrontendIp);
        data["FrontendPort"] = toUtf(pRspAccount->FrontendPort);
        data["CurrencyNo"] = toUtf(pRspAccount->CurrencyNo);
        data["UserState"] = toUtf(pRspAccount->UserState);
        data["SelAll"] = toUtf(pRspAccount->SelAll);
        data["Strategy"] = toUtf(pRspAccount->Strategy);
        data["Inner"] = toUtf(pRspAccount->Inner);
        data["YingSun"] = toUtf(pRspAccount->YingSun);
        data["ChaoDan"] = toUtf(pRspAccount->ChaoDan);
        data["Option"] = toUtf(pRspAccount->Option);
        data["CmeMarket"] = toUtf(pRspAccount->CmeMarket);
        data["CmeCOMEXMarket"] = toUtf(pRspAccount->CmeCOMEXMarket);
        data["CmeNYMEXMarket"] = toUtf(pRspAccount->CmeNYMEXMarket);
        data["CmeCBTMarket"] = toUtf(pRspAccount->CmeCBTMarket);
        data["IceUSMarket"] = toUtf(pRspAccount->IceUSMarket);
        data["IceECMarket"] = toUtf(pRspAccount->IceECMarket);
        data["IceEFMarket"] = toUtf(pRspAccount->IceEFMarket);
        data["CanTradeStockHK"] = toUtf(pRspAccount->CanTradeStockHK);
        data["CanTradeStockAM"] = toUtf(pRspAccount->CanTradeStockAM);
        data["MultiLogin"] = toUtf(pRspAccount->MultiLogin);
        data["SellStockHK"] = toUtf(pRspAccount->SellStockHK);
        data["SellStockAM"] = toUtf(pRspAccount->SellStockAM);
        data["CanTradeStockKRX"] = toUtf(pRspAccount->CanTradeStockKRX);
        data["HkexMarket"] = toUtf(pRspAccount->HkexMarket);
        data["IdNumber"] = toUtf(pRspAccount->IdNumber);
        data["HkexMarketFee"] = toUtf(pRspAccount->HkexMarketFee);
        data["IsProfessional"] = toUtf(pRspAccount->IsProfessional);
        data["IsOverSea"] = toUtf(pRspAccount->IsOverSea);
        data["IsFirstLogin"] = toUtf(pRspAccount->IsFirstLogin);
        data["UserMobile"] = toUtf(pRspAccount->UserMobile);
        data["HasSetQA"] = toUtf(pRspAccount->HasSetQA);
        data["CanTradeStockSGXQ"] = toUtf(pRspAccount->CanTradeStockSGXQ);
        data["ExistMac"] = toUtf(pRspAccount->ExistMac);
        data["RatioINE"] = toUtf(pRspAccount->RatioINE);
        data["EurexMarket"] = toUtf(pRspAccount->EurexMarket);
        data["HkexIsOverMaxTerminal"] = toUtf(pRspAccount->HkexIsOverMaxTerminal);
        data["HkexOverMoney"] = toUtf(pRspAccount->HkexOverMoney);
        data["CanTradeStockAU"] = toUtf(pRspAccount->CanTradeStockAU);
        data["NyFlag"] = toUtf(pRspAccount->NyFlag);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspAccount(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQuestion(CFutureRspQuestionField *pRspVersion, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspVersion)
    {
        data["QuestionType"] = toUtf(pRspVersion->QuestionType);
        data["QuestionId"] = toUtf(pRspVersion->QuestionId);
        data["QuestionCN"] = toUtf(pRspVersion->QuestionCN);
        data["QuestionEN"] = toUtf(pRspVersion->QuestionEN);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQuestion(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspOrderInsert(CFutureRspOrderInsertField *pRspOrderInsert, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspOrderInsert)
    {
        data["UserId"] = toUtf(pRspOrderInsert->UserId);
        data["AccountNo"] = toUtf(pRspOrderInsert->AccountNo);
        data["SystemNo"] = toUtf(pRspOrderInsert->SystemNo);
        data["LocalNo"] = toUtf(pRspOrderInsert->LocalNo);
        data["OrderNo"] = toUtf(pRspOrderInsert->OrderNo);
        data["OrigOrderNo"] = toUtf(pRspOrderInsert->OrigOrderNo);
        data["OrderMethod"] = toUtf(pRspOrderInsert->OrderMethod);
        data["AcceptType"] = toUtf(pRspOrderInsert->AcceptType);
        data["ExchangeCode"] = toUtf(pRspOrderInsert->ExchangeCode);
        data["TreatyCode"] = toUtf(pRspOrderInsert->TreatyCode);
        data["BuySale"] = toUtf(pRspOrderInsert->BuySale);
        data["OrderNumber"] = toUtf(pRspOrderInsert->OrderNumber);
        data["OrderPrice"] = toUtf(pRspOrderInsert->OrderPrice);
        data["FilledNumber"] = toUtf(pRspOrderInsert->FilledNumber);
        data["FilledPrice"] = toUtf(pRspOrderInsert->FilledPrice);
        data["TradeType"] = toUtf(pRspOrderInsert->TradeType);
        data["PriceType"] = toUtf(pRspOrderInsert->PriceType);
        data["HtsType"] = toUtf(pRspOrderInsert->HtsType);
        data["OrderDate"] = toUtf(pRspOrderInsert->OrderDate);
        data["OrderTime"] = toUtf(pRspOrderInsert->OrderTime);
        data["ErrorCode"] = toUtf(pRspOrderInsert->ErrorCode);
        data["OrderState"] = toUtf(pRspOrderInsert->OrderState);
        data["IsRiskOrder"] = toUtf(pRspOrderInsert->IsRiskOrder);
        data["CancelUserId"] = toUtf(pRspOrderInsert->CancelUserId);
        data["TriggerPrice"] = toUtf(pRspOrderInsert->TriggerPrice);
        data["ValidDate"] = toUtf(pRspOrderInsert->ValidDate);
        data["AddReduce"] = toUtf(pRspOrderInsert->AddReduce);
        data["StrategyId"] = toUtf(pRspOrderInsert->StrategyId);
        data["MaxShow"] = toUtf(pRspOrderInsert->MaxShow);
        data["MinQty"] = toUtf(pRspOrderInsert->MinQty);
        data["ExchangeTime"] = toUtf(pRspOrderInsert->ExchangeTime);
        data["CancelTime"] = toUtf(pRspOrderInsert->CancelTime);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspOrderInsert(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspOrderModify(CFutureRspOrderModifyField *pRspOrderModify, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspOrderModify)
    {
        data["UserId"] = toUtf(pRspOrderModify->UserId);
        data["AccountNo"] = toUtf(pRspOrderModify->AccountNo);
        data["SystemNo"] = toUtf(pRspOrderModify->SystemNo);
        data["LocalNo"] = toUtf(pRspOrderModify->LocalNo);
        data["OrderNo"] = toUtf(pRspOrderModify->OrderNo);
        data["OrigOrderNo"] = toUtf(pRspOrderModify->OrigOrderNo);
        data["OrderMethod"] = toUtf(pRspOrderModify->OrderMethod);
        data["AcceptType"] = toUtf(pRspOrderModify->AcceptType);
        data["ExchangeCode"] = toUtf(pRspOrderModify->ExchangeCode);
        data["TreatyCode"] = toUtf(pRspOrderModify->TreatyCode);
        data["BuySale"] = toUtf(pRspOrderModify->BuySale);
        data["OrderNumber"] = toUtf(pRspOrderModify->OrderNumber);
        data["OrderPrice"] = toUtf(pRspOrderModify->OrderPrice);
        data["FilledNumber"] = toUtf(pRspOrderModify->FilledNumber);
        data["FilledPrice"] = toUtf(pRspOrderModify->FilledPrice);
        data["TradeType"] = toUtf(pRspOrderModify->TradeType);
        data["PriceType"] = toUtf(pRspOrderModify->PriceType);
        data["HtsType"] = toUtf(pRspOrderModify->HtsType);
        data["OrderDate"] = toUtf(pRspOrderModify->OrderDate);
        data["OrderTime"] = toUtf(pRspOrderModify->OrderTime);
        data["ErrorCode"] = toUtf(pRspOrderModify->ErrorCode);
        data["OrderState"] = toUtf(pRspOrderModify->OrderState);
        data["IsRiskOrder"] = toUtf(pRspOrderModify->IsRiskOrder);
        data["CancelUserId"] = toUtf(pRspOrderModify->CancelUserId);
        data["TriggerPrice"] = toUtf(pRspOrderModify->TriggerPrice);
        data["ValidDate"] = toUtf(pRspOrderModify->ValidDate);
        data["AddReduce"] = toUtf(pRspOrderModify->AddReduce);
        data["StrategyId"] = toUtf(pRspOrderModify->StrategyId);
        data["MaxShow"] = toUtf(pRspOrderModify->MaxShow);
        data["MinQty"] = toUtf(pRspOrderModify->MinQty);
        data["ExchangeTime"] = toUtf(pRspOrderModify->ExchangeTime);
        data["CancelTime"] = toUtf(pRspOrderModify->CancelTime);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspOrderModify(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspOrderCancel(CFutureRspOrderCancelField *pRspOrderCancel, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspOrderCancel)
    {
        data["UserId"] = toUtf(pRspOrderCancel->UserId);
        data["AccountNo"] = toUtf(pRspOrderCancel->AccountNo);
        data["SystemNo"] = toUtf(pRspOrderCancel->SystemNo);
        data["LocalNo"] = toUtf(pRspOrderCancel->LocalNo);
        data["OrderNo"] = toUtf(pRspOrderCancel->OrderNo);
        data["CancelNo"] = toUtf(pRspOrderCancel->CancelNo);
        data["ExchangeCode"] = toUtf(pRspOrderCancel->ExchangeCode);
        data["TreatyCode"] = toUtf(pRspOrderCancel->TreatyCode);
        data["BuySale"] = toUtf(pRspOrderCancel->BuySale);
        data["OrderNumber"] = toUtf(pRspOrderCancel->OrderNumber);
        data["OrderPrice"] = toUtf(pRspOrderCancel->OrderPrice);
        data["FilledNumber"] = toUtf(pRspOrderCancel->FilledNumber);
        data["CancelNumber"] = toUtf(pRspOrderCancel->CancelNumber);
        data["TradeType"] = toUtf(pRspOrderCancel->TradeType);
        data["PriceType"] = toUtf(pRspOrderCancel->PriceType);
        data["HtsType"] = toUtf(pRspOrderCancel->HtsType);
        data["CancelDate"] = toUtf(pRspOrderCancel->CancelDate);
        data["CancelTime"] = toUtf(pRspOrderCancel->CancelTime);
        data["ErrorCode"] = toUtf(pRspOrderCancel->ErrorCode);
        data["IsRiskOrder"] = toUtf(pRspOrderCancel->IsRiskOrder);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspOrderCancel(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspPasswordUpdate(CFutureRspPasswordUpdateField *pRspPasswordUpdate, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspPasswordUpdate)
    {
        data["UserId"] = toUtf(pRspPasswordUpdate->UserId);
        data["OldPassword"] = toUtf(pRspPasswordUpdate->OldPassword);
        data["NewPassword"] = toUtf(pRspPasswordUpdate->NewPassword);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspPasswordUpdate(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRtnTrade(CFutureRtnTradeField *pRtnTrade, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRtnTrade)
    {
        data["UserId"] = toUtf(pRtnTrade->UserId);
        data["AccountNo"] = toUtf(pRtnTrade->AccountNo);
        data["FilledNo"] = toUtf(pRtnTrade->FilledNo);
        data["OrderNo"] = toUtf(pRtnTrade->OrderNo);
        data["SystemNo"] = toUtf(pRtnTrade->SystemNo);
        data["LocalNo"] = toUtf(pRtnTrade->LocalNo);
        data["ExchangeCode"] = toUtf(pRtnTrade->ExchangeCode);
        data["TreatyCode"] = toUtf(pRtnTrade->TreatyCode);
        data["BuySale"] = toUtf(pRtnTrade->BuySale);
        data["FilledNumber"] = toUtf(pRtnTrade->FilledNumber);
        data["FilledPrice"] = toUtf(pRtnTrade->FilledPrice);
        data["FilledDate"] = toUtf(pRtnTrade->FilledDate);
        data["FilledTime"] = toUtf(pRtnTrade->FilledTime);
        data["Commsion"] = toUtf(pRtnTrade->Commsion);
        data["OrderNumber"] = toUtf(pRtnTrade->OrderNumber);
        data["OrderPrice"] = toUtf(pRtnTrade->OrderPrice);
        data["DeliveryDate"] = toUtf(pRtnTrade->DeliveryDate);
        data["FilledType"] = toUtf(pRtnTrade->FilledType);
        data["OrderType"] = toUtf(pRtnTrade->OrderType);
        data["ValidDate"] = toUtf(pRtnTrade->ValidDate);
        data["AddReduce"] = toUtf(pRtnTrade->AddReduce);
        data["ErrorDescription"] = toUtf(pRtnTrade->ErrorDescription);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRtnTrade(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRtnOrder(CFutureRtnOrderField *pRtnOrder, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRtnOrder)
    {
        data["LocalOrderNo"] = toUtf(pRtnOrder->LocalOrderNo);
        data["ExchangeNo"] = toUtf(pRtnOrder->ExchangeNo);
        data["TreatyCode"] = toUtf(pRtnOrder->TreatyCode);
        data["OrderNo"] = toUtf(pRtnOrder->OrderNo);
        data["OrderNumber"] = pRtnOrder->OrderNumber;
        data["FilledNumber"] = pRtnOrder->FilledNumber;
        data["FilledAdvPrice"] = pRtnOrder->FilledAdvPrice;
        data["BuyHoldNumber"] = pRtnOrder->BuyHoldNumber;
        data["BuyHoldOpenPrice"] = pRtnOrder->BuyHoldOpenPrice;
        data["BuyHoldPrice"] = pRtnOrder->BuyHoldPrice;
        data["SaleHoldNumber"] = pRtnOrder->SaleHoldNumber;
        data["SaleHoldOpenPrice"] = pRtnOrder->SaleHoldOpenPrice;
        data["SaleHoldPrice"] = pRtnOrder->SaleHoldPrice;
        data["IsCanceled"] = toUtf(pRtnOrder->IsCanceled);
        data["FilledTotalFee"] = pRtnOrder->FilledTotalFee;
        data["Status"] = pRtnOrder->Status;
        data["AccountNo"] = toUtf(pRtnOrder->AccountNo);
        data["HoldType"] = toUtf(pRtnOrder->HoldType);
        data["HoldMarginBuy"] = pRtnOrder->HoldMarginBuy;
        data["HoldMarginSale"] = pRtnOrder->HoldMarginSale;
        data["CurrPrice"] = pRtnOrder->CurrPrice;
        data["FloatProfit"] = pRtnOrder->FloatProfit;
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRtnOrder(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRtnCapital(CFutureRtnCapitalField *pRtnCapital, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRtnCapital)
    {
        data["ClientNo"] = toUtf(pRtnCapital->ClientNo);
        data["AccountNo"] = toUtf(pRtnCapital->AccountNo);
        data["CurrencyNo"] = toUtf(pRtnCapital->CurrencyNo);
        data["Available"] = pRtnCapital->Available;
        data["YAvailable"] = pRtnCapital->YAvailable;
        data["CanCashOut"] = pRtnCapital->CanCashOut;
        data["Money"] = pRtnCapital->Money;
        data["ExpiredProfit"] = pRtnCapital->ExpiredProfit;
        data["FrozenDeposit"] = pRtnCapital->FrozenDeposit;
        data["Fee"] = pRtnCapital->Fee;
        data["Deposit"] = pRtnCapital->Deposit;
        data["KeepDeposit"] = pRtnCapital->KeepDeposit;
        data["Status"] = pRtnCapital->Status;
        data["InMoney"] = pRtnCapital->InMoney;
        data["OutMoney"] = pRtnCapital->OutMoney;
        data["UnexpiredProfit"] = pRtnCapital->UnexpiredProfit;
        data["TodayTotal"] = pRtnCapital->TodayTotal;
        data["UnaccountProfit"] = pRtnCapital->UnaccountProfit;
        data["Royalty"] = pRtnCapital->Royalty;
        data["ExchangeNo"] = toUtf(pRtnCapital->ExchangeNo);
        data["TreatyCode"] = toUtf(pRtnCapital->TreatyCode);
        data["OrderNo"] = toUtf(pRtnCapital->OrderNo);
        data["OrderNumber"] = pRtnCapital->OrderNumber;
        data["FilledNumber"] = pRtnCapital->FilledNumber;
        data["FilledAdvPrice"] = pRtnCapital->FilledAdvPrice;
        data["BuyHoldNumber"] = pRtnCapital->BuyHoldNumber;
        data["BuyHoldOpenPrice"] = pRtnCapital->BuyHoldOpenPrice;
        data["BuyHoldPrice"] = pRtnCapital->BuyHoldPrice;
        data["SaleHoldNumber"] = pRtnCapital->SaleHoldNumber;
        data["SaleHoldOpenPrice"] = pRtnCapital->SaleHoldOpenPrice;
        data["SaleHoldPrice"] = pRtnCapital->SaleHoldPrice;
        data["IsCanceled"] = toUtf(pRtnCapital->IsCanceled);
        data["FilledTotalFee"] = pRtnCapital->FilledTotalFee;
        data["Credit"] = pRtnCapital->Credit;
        data["MarginLimit"] = pRtnCapital->MarginLimit;
        data["BorrowValue"] = pRtnCapital->BorrowValue;
        data["MortgageMoney"] = pRtnCapital->MortgageMoney;
        data["T1"] = pRtnCapital->T1;
        data["T2"] = pRtnCapital->T2;
        data["T3"] = pRtnCapital->T3;
        data["TN"] = pRtnCapital->TN;
        data["TradeLimit"] = pRtnCapital->TradeLimit;
        data["FCrossMax"] = pRtnCapital->FCrossMax;
        data["SellFreezenMoney"] = pRtnCapital->SellFreezenMoney;
        data["SellInterest"] = pRtnCapital->SellInterest;
        data["SellNeedAddMargin"] = pRtnCapital->SellNeedAddMargin;
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRtnCapital(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRtnPosition(CFutureRtnPositionField *pRtnPosition, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRtnPosition)
    {
        data["LocalOrderNo"] = toUtf(pRtnPosition->LocalOrderNo);
        data["ExchangeNo"] = toUtf(pRtnPosition->ExchangeNo);
        data["TreatyCode"] = toUtf(pRtnPosition->TreatyCode);
        data["OrderNo"] = toUtf(pRtnPosition->OrderNo);
        data["OrderNumber"] = pRtnPosition->OrderNumber;
        data["FilledNumber"] = pRtnPosition->FilledNumber;
        data["FilledAdvPrice"] = pRtnPosition->FilledAdvPrice;
        data["BuyHoldNumber"] = pRtnPosition->BuyHoldNumber;
        data["BuyHoldOpenPrice"] = pRtnPosition->BuyHoldOpenPrice;
        data["BuyHoldPrice"] = pRtnPosition->BuyHoldPrice;
        data["SaleHoldNumber"] = pRtnPosition->SaleHoldNumber;
        data["SaleHoldOpenPrice"] = pRtnPosition->SaleHoldOpenPrice;
        data["SaleHoldPrice"] = pRtnPosition->SaleHoldPrice;
        data["IsCanceled"] = toUtf(pRtnPosition->IsCanceled);
        data["FilledTotalFee"] = pRtnPosition->FilledTotalFee;
        data["Status"] = pRtnPosition->Status;
        data["AccountNo"] = toUtf(pRtnPosition->AccountNo);
        data["HoldType"] = toUtf(pRtnPosition->HoldType);
        data["HoldMarginBuy"] = pRtnPosition->HoldMarginBuy;
        data["HoldMarginSale"] = pRtnPosition->HoldMarginSale;
        data["CurrPrice"] = pRtnPosition->CurrPrice;
        data["FloatProfit"] = pRtnPosition->FloatProfit;
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRtnPosition(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryOrder(CFutureRspOrderField *pRspOrder, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspOrder)
    {
        data["UserId"] = toUtf(pRspOrder->UserId);
        data["AccountNo"] = toUtf(pRspOrder->AccountNo);
        data["SystemNo"] = toUtf(pRspOrder->SystemNo);
        data["LocalNo"] = toUtf(pRspOrder->LocalNo);
        data["OrderNo"] = toUtf(pRspOrder->OrderNo);
        data["OrigOrderNo"] = toUtf(pRspOrder->OrigOrderNo);
        data["OrderMethod"] = toUtf(pRspOrder->OrderMethod);
        data["AcceptType"] = toUtf(pRspOrder->AcceptType);
        data["ExchangeCode"] = toUtf(pRspOrder->ExchangeCode);
        data["TreatyCode"] = toUtf(pRspOrder->TreatyCode);
        data["BuySale"] = toUtf(pRspOrder->BuySale);
        data["OrderNumber"] = toUtf(pRspOrder->OrderNumber);
        data["OrderPrice"] = toUtf(pRspOrder->OrderPrice);
        data["FilledNumber"] = toUtf(pRspOrder->FilledNumber);
        data["FilledPrice"] = toUtf(pRspOrder->FilledPrice);
        data["TradeType"] = toUtf(pRspOrder->TradeType);
        data["PriceType"] = toUtf(pRspOrder->PriceType);
        data["HtsType"] = toUtf(pRspOrder->HtsType);
        data["OrderDate"] = toUtf(pRspOrder->OrderDate);
        data["OrderTime"] = toUtf(pRspOrder->OrderTime);
        data["ErrorCode"] = toUtf(pRspOrder->ErrorCode);
        data["OrderState"] = toUtf(pRspOrder->OrderState);
        data["IsRiskOrder"] = toUtf(pRspOrder->IsRiskOrder);
        data["CancelUserId"] = toUtf(pRspOrder->CancelUserId);
        data["TriggerPrice"] = toUtf(pRspOrder->TriggerPrice);
        data["ValidDate"] = toUtf(pRspOrder->ValidDate);
        data["AddReduce"] = toUtf(pRspOrder->AddReduce);
        data["StrategyId"] = toUtf(pRspOrder->StrategyId);
        data["MaxShow"] = toUtf(pRspOrder->MaxShow);
        data["MinQty"] = toUtf(pRspOrder->MinQty);
        data["ExchangeTime"] = toUtf(pRspOrder->ExchangeTime);
        data["CancelTime"] = toUtf(pRspOrder->CancelTime);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryOrder(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryTrade(CFutureRspTradeField *pRspTrade, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspTrade)
    {
        data["UserId"] = toUtf(pRspTrade->UserId);
        data["AccountNo"] = toUtf(pRspTrade->AccountNo);
        data["FilledNo"] = toUtf(pRspTrade->FilledNo);
        data["OrderNo"] = toUtf(pRspTrade->OrderNo);
        data["SystemNo"] = toUtf(pRspTrade->SystemNo);
        data["LocalNo"] = toUtf(pRspTrade->LocalNo);
        data["ExchangeCode"] = toUtf(pRspTrade->ExchangeCode);
        data["TreatyCode"] = toUtf(pRspTrade->TreatyCode);
        data["BuySale"] = toUtf(pRspTrade->BuySale);
        data["FilledNumber"] = toUtf(pRspTrade->FilledNumber);
        data["FilledPrice"] = toUtf(pRspTrade->FilledPrice);
        data["FilledDate"] = toUtf(pRspTrade->FilledDate);
        data["FilledTime"] = toUtf(pRspTrade->FilledTime);
        data["Commsion"] = toUtf(pRspTrade->Commsion);
        data["OrderNumber"] = toUtf(pRspTrade->OrderNumber);
        data["OrderPrice"] = toUtf(pRspTrade->OrderPrice);
        data["DeliveryDate"] = toUtf(pRspTrade->DeliveryDate);
        data["FilledType"] = toUtf(pRspTrade->FilledType);
        data["OrderType"] = toUtf(pRspTrade->OrderType);
        data["ValidDate"] = toUtf(pRspTrade->ValidDate);
        data["AddReduce"] = toUtf(pRspTrade->AddReduce);
        data["ErrorDescription"] = toUtf(pRspTrade->ErrorDescription);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryTrade(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryCapital(CFutureRspCapitalField *pRspCapital, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspCapital)
    {
        data["UserId"] = toUtf(pRspCapital->UserId);
        data["InMoney"] = toUtf(pRspCapital->InMoney);
        data["OutMoney"] = toUtf(pRspCapital->OutMoney);
        data["TodayCanUse"] = toUtf(pRspCapital->TodayCanUse);
        data["TodayAmount"] = toUtf(pRspCapital->TodayAmount);
        data["TodayBalance"] = toUtf(pRspCapital->TodayBalance);
        data["FreezenMoney"] = toUtf(pRspCapital->FreezenMoney);
        data["Commission"] = toUtf(pRspCapital->Commission);
        data["Margin"] = toUtf(pRspCapital->Margin);
        data["OldCanUse"] = toUtf(pRspCapital->OldCanUse);
        data["OldAmount"] = toUtf(pRspCapital->OldAmount);
        data["OldBalance"] = toUtf(pRspCapital->OldBalance);
        data["FloatingProfit"] = toUtf(pRspCapital->FloatingProfit);
        data["CurrencyNo"] = toUtf(pRspCapital->CurrencyNo);
        data["CurrencyRate"] = pRspCapital->CurrencyRate;
        data["UnexpiredProfit"] = pRspCapital->UnexpiredProfit;
        data["UnaccountProfit"] = pRspCapital->UnaccountProfit;
        data["KeepDeposit"] = pRspCapital->KeepDeposit;
        data["Royalty"] = pRspCapital->Royalty;
        data["Credit"] = pRspCapital->Credit;
        data["AddCapital"] = pRspCapital->AddCapital;
        data["IniEquity"] = pRspCapital->IniEquity;
        data["AccountNo"] = toUtf(pRspCapital->AccountNo);
        data["MortgageMoney"] = pRspCapital->MortgageMoney;
        data["MarginLimit"] = pRspCapital->MarginLimit;
        data["BorrowValue"] = pRspCapital->BorrowValue;
        data["T1"] = pRspCapital->T1;
        data["T2"] = pRspCapital->T2;
        data["T3"] = pRspCapital->T3;
        data["TN"] = pRspCapital->TN;
        data["TradeLimit"] = pRspCapital->TradeLimit;
        data["CanCashOut"] = pRspCapital->CanCashOut;
        data["AccruedCrInt"] = pRspCapital->AccruedCrInt;
        data["AccruedDrInt"] = pRspCapital->AccruedDrInt;
        data["CrossMax"] = pRspCapital->CrossMax;
        data["SellFreezenMoney"] = pRspCapital->SellFreezenMoney;
        data["SellInterest"] = pRspCapital->SellInterest;
        data["SellNeedAddMargin"] = pRspCapital->SellNeedAddMargin;
        data["NetProfit"] = toUtf(pRspCapital->NetProfit);
        data["ProfitRate"] = toUtf(pRspCapital->ProfitRate);
        data["RiskRate"] = toUtf(pRspCapital->RiskRate);
        data["ErrorDescription"] = toUtf(pRspCapital->ErrorDescription);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryCapital(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryVersion(CFutureRspVersionField *pRspVersion, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspVersion)
    {
        data["Version"] = toUtf(pRspVersion->Version);
        data["MustUpdate"] = toUtf(pRspVersion->MustUpdate);
        data["MustVersion"] = toUtf(pRspVersion->MustVersion);
        data["VersionContent_CN"] = toUtf(pRspVersion->VersionContent_CN);
        data["VersionContent_US"] = toUtf(pRspVersion->VersionContent_US);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryVersion(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryPosition(CFutureRspPositionField *pRspPosition, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspPosition)
    {
        data["MatchDate"] = toUtf(pRspPosition->MatchDate);
        data["MatchNo"] = toUtf(pRspPosition->MatchNo);
        data["ClientNo"] = toUtf(pRspPosition->ClientNo);
        data["ExchangeNo"] = toUtf(pRspPosition->ExchangeNo);
        data["CommodityNo"] = toUtf(pRspPosition->CommodityNo);
        data["ContractNo"] = toUtf(pRspPosition->ContractNo);
        data["Direct"] = toUtf(pRspPosition->Direct);
        data["HoldVol"] = pRspPosition->HoldVol;
        data["HoldPrice"] = pRspPosition->HoldPrice;
        data["CurrencyNo"] = toUtf(pRspPosition->CurrencyNo);
        data["ForciblyPrice"] = pRspPosition->ForciblyPrice;
        data["Account"] = toUtf(pRspPosition->Account);
        data["HoldType"] = toUtf(pRspPosition->HoldType);
        data["DeliveryDate"] = toUtf(pRspPosition->DeliveryDate);
        data["ExchangeName"] = toUtf(pRspPosition->ExchangeName);
        data["CurrencyName"] = toUtf(pRspPosition->CurrencyName);
        data["ContCode"] = toUtf(pRspPosition->ContCode);
        data["HoldMargin"] = pRspPosition->HoldMargin;
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryPosition(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryCurrency(CFutureRspCurrencyField *pRspCurrency, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspCurrency)
    {
        data["CurrencyNo"] = toUtf(pRspCurrency->CurrencyNo);
        data["IsBase"] = pRspCurrency->IsBase;
        data["ChangeRate"] = pRspCurrency->ChangeRate;
        data["CurrencyName"] = toUtf(pRspCurrency->CurrencyName);
        data["CurrencyNameEN"] = toUtf(pRspCurrency->CurrencyNameEN);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryCurrency(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryExchange(CFutureRspExchangeField *pRspExchange, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspExchange)
    {
        data["ExchangeNo"] = toUtf(pRspExchange->ExchangeNo);
        data["ExchangeName"] = toUtf(pRspExchange->ExchangeName);
        data["SettleType"] = toUtf(pRspExchange->SettleType);
        data["NameEN"] = toUtf(pRspExchange->NameEN);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryExchange(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryStrategy(CFutureRspStrategyField *pRspStrategy, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspStrategy)
    {
        data["UserId"] = toUtf(pRspStrategy->UserId);
        data["KeyId"] = toUtf(pRspStrategy->KeyId);
        data["Name"] = toUtf(pRspStrategy->Name);
        data["Code"] = toUtf(pRspStrategy->Code);
        data["PriceType"] = pRspStrategy->PriceType;
        data["PriceTypeDetailType"] = pRspStrategy->PriceTypeDetailType;
        data["PriceFormula"] = toUtf(pRspStrategy->PriceFormula);
        data["TriggerMethod"] = pRspStrategy->TriggerMethod;
        data["InnerProtect"] = pRspStrategy->InnerProtect;
        data["PassiveFailCloseMainLeg"] = pRspStrategy->PassiveFailCloseMainLeg;
        data["SlipPoint"] = pRspStrategy->SlipPoint;
        data["RecoverPriceMethod"] = pRspStrategy->RecoverPriceMethod;
        data["RecoverPriceSeconds"] = pRspStrategy->RecoverPriceSeconds;
        data["SetType"] = toUtf(pRspStrategy->SetType);
        data["MinChangePrice"] = pRspStrategy->MinChangePrice;
        data["MaxNum"] = pRspStrategy->MaxNum;
        data["SuportQuantity"] = pRspStrategy->SuportQuantity;
        data["SafeDeep"] = pRspStrategy->SafeDeep;
        data["MainRange"] = pRspStrategy->MainRange;
        data["ManualZhuiDanBeyondNum"] = toUtf(pRspStrategy->ManualZhuiDanBeyondNum);
        data["ManualPingZhuDongBeyondNum"] = toUtf(pRspStrategy->ManualPingZhuDongBeyondNum);
        data["AutoGuaDanSeconds"] = pRspStrategy->AutoGuaDanSeconds;
        data["AutoZhuiBeiDongDots"] = pRspStrategy->AutoZhuiBeiDongDots;
        data["AutoPingZhuDongDots"] = pRspStrategy->AutoPingZhuDongDots;
        data["AutoZhiSunDot"] = pRspStrategy->AutoZhiSunDot;
        data["AutoZhiSunZhuiBeiDongDots"] = pRspStrategy->AutoZhiSunZhuiBeiDongDots;
        data["AutoZhiSunPingZhuDongDots"] = pRspStrategy->AutoZhiSunPingZhuDongDots;
        data["DotLen"] = pRspStrategy->DotLen;
        data["TradeTime"] = toUtf(pRspStrategy->TradeTime);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryStrategy(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryCommodity(CFutureRspCommodityField *pRspCommodity, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspCommodity)
    {
        data["CommodityNo"] = toUtf(pRspCommodity->CommodityNo);
        data["ExchangeNo"] = toUtf(pRspCommodity->ExchangeNo);
        data["CommodityType"] = toUtf(pRspCommodity->CommodityType);
        data["Name"] = toUtf(pRspCommodity->Name);
        data["Enabled"] = toUtf(pRspCommodity->Enabled);
        data["RegDate"] = toUtf(pRspCommodity->RegDate);
        data["CurrencyNo"] = toUtf(pRspCommodity->CurrencyNo);
        data["ProductDot"] = pRspCommodity->ProductDot;
        data["LowerTick"] = pRspCommodity->LowerTick;
        data["UpperTick"] = pRspCommodity->UpperTick;
        data["DotNum"] = pRspCommodity->DotNum;
        data["StrikeCommodityId"] = pRspCommodity->StrikeCommodityId;
        data["OptionStyle"] = toUtf(pRspCommodity->OptionStyle);
        data["ExchangeNo2"] = toUtf(pRspCommodity->ExchangeNo2);
        data["IsSFuture"] = toUtf(pRspCommodity->IsSFuture);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryCommodity(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryInstrument(CFutureRspInstrumentField *pRspInstrument, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspInstrument)
    {
        data["CommodityCode"] = toUtf(pRspInstrument->CommodityCode);
        data["ExchangeNo"] = toUtf(pRspInstrument->ExchangeNo);
        data["ContractNo"] = toUtf(pRspInstrument->ContractNo);
        data["ContractFName"] = toUtf(pRspInstrument->ContractFName);
        data["CommodityNo"] = toUtf(pRspInstrument->CommodityNo);
        data["CommodityFName"] = toUtf(pRspInstrument->CommodityFName);
        data["CommodityType"] = toUtf(pRspInstrument->CommodityType);
        data["CommodityFCurrencyNo"] = toUtf(pRspInstrument->CommodityFCurrencyNo);
        data["CurrencyFName"] = toUtf(pRspInstrument->CurrencyFName);
        data["ProductDot"] = pRspInstrument->ProductDot;
        data["UpperTick"] = pRspInstrument->UpperTick;
        data["ExchangeName"] = toUtf(pRspInstrument->ExchangeName);
        data["LastSettlePrice"] = pRspInstrument->LastSettlePrice;
        data["TradeMonth"] = toUtf(pRspInstrument->TradeMonth);
        data["DotNum"] = pRspInstrument->DotNum;
        data["LowerTick"] = pRspInstrument->LowerTick;
        data["DotNumCarry"] = pRspInstrument->DotNumCarry;
        data["UpperTickCarry"] = pRspInstrument->UpperTickCarry;
        data["FirstNoticeDay"] = toUtf(pRspInstrument->FirstNoticeDay);
        data["FreezenPercent"] = pRspInstrument->FreezenPercent;
        data["FreezenMoney"] = pRspInstrument->FreezenMoney;
        data["FeeMoney"] = pRspInstrument->FeeMoney;
        data["FeePercent"] = pRspInstrument->FeePercent;
        data["PriceStrike"] = pRspInstrument->PriceStrike;
        data["ProductDotStrike"] = pRspInstrument->ProductDotStrike;
        data["UpperTickStrike"] = pRspInstrument->UpperTickStrike;
        data["LastTradeDay"] = toUtf(pRspInstrument->LastTradeDay);
        data["LastUpdateDay"] = toUtf(pRspInstrument->LastUpdateDay);
        data["CriticalPrice"] = pRspInstrument->CriticalPrice;
        data["CriticalMinChangedPrice"] = pRspInstrument->CriticalMinChangedPrice;
        data["ExchangeSub"] = toUtf(pRspInstrument->ExchangeSub);
        data["OptionType"] = toUtf(pRspInstrument->OptionType);
        data["OptionMonth"] = toUtf(pRspInstrument->OptionMonth);
        data["OptionStrikePrice"] = toUtf(pRspInstrument->OptionStrikePrice);
        data["OptionCommodityNo"] = toUtf(pRspInstrument->OptionCommodityNo);
        data["OptionContractNo"] = toUtf(pRspInstrument->OptionContractNo);
        data["ContractFNameEN"] = toUtf(pRspInstrument->ContractFNameEN);
        data["CommodityFNameEN"] = toUtf(pRspInstrument->CommodityFNameEN);
        data["OptionStyle"] = toUtf(pRspInstrument->OptionStyle);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryInstrument(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryExchangeTime(CFutureRspExchangeTimeField *pRspExchangeTime, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspExchangeTime)
    {
        data["Year"] = toUtf(pRspExchangeTime->Year);
        data["SummerBegin"] = toUtf(pRspExchangeTime->SummerBegin);
        data["WinterBegin"] = toUtf(pRspExchangeTime->WinterBegin);
        data["ExchangeNo"] = toUtf(pRspExchangeTime->ExchangeNo);
        data["Name"] = toUtf(pRspExchangeTime->Name);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryExchangeTime(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryCommodityTime(CFutureRspCommodityTimeField *pRspCommodityTime, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspCommodityTime)
    {
        data["CrossTrade"] = toUtf(pRspCommodityTime->CrossTrade);
        data["Stage"] = toUtf(pRspCommodityTime->Stage);
        data["Summer"] = toUtf(pRspCommodityTime->Summer);
        data["Opendate"] = toUtf(pRspCommodityTime->Opendate);
        data["Closingdate"] = toUtf(pRspCommodityTime->Closingdate);
        data["CommodityNo"] = toUtf(pRspCommodityTime->CommodityNo);
        data["ComName"] = toUtf(pRspCommodityTime->ComName);
        data["ExchangeNo"] = toUtf(pRspCommodityTime->ExchangeNo);
        data["ExName"] = toUtf(pRspCommodityTime->ExName);
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryCommodityTime(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryTotalPosition(CFutureRspTotalPositionField *pRspTotalPosition, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspTotalPosition)
    {
        data["LocalOrderNo"] = toUtf(pRspTotalPosition->LocalOrderNo);
        data["ExchangeNo"] = toUtf(pRspTotalPosition->ExchangeNo);
        data["TreatyCode"] = toUtf(pRspTotalPosition->TreatyCode);
        data["OrderNo"] = toUtf(pRspTotalPosition->OrderNo);
        data["OrderNumber"] = pRspTotalPosition->OrderNumber;
        data["FilledNumber"] = pRspTotalPosition->FilledNumber;
        data["FilledAdvPrice"] = pRspTotalPosition->FilledAdvPrice;
        data["BuyHoldNumber"] = pRspTotalPosition->BuyHoldNumber;
        data["BuyHoldOpenPrice"] = pRspTotalPosition->BuyHoldOpenPrice;
        data["BuyHoldPrice"] = pRspTotalPosition->BuyHoldPrice;
        data["SaleHoldNumber"] = pRspTotalPosition->SaleHoldNumber;
        data["SaleHoldOpenPrice"] = pRspTotalPosition->SaleHoldOpenPrice;
        data["SaleHoldPrice"] = pRspTotalPosition->SaleHoldPrice;
        data["IsCanceled"] = toUtf(pRspTotalPosition->IsCanceled);
        data["FilledTotalFee"] = pRspTotalPosition->FilledTotalFee;
        data["Status"] = pRspTotalPosition->Status;
        data["AccountNo"] = toUtf(pRspTotalPosition->AccountNo);
        data["HoldType"] = toUtf(pRspTotalPosition->HoldType);
        data["HoldMarginBuy"] = pRspTotalPosition->HoldMarginBuy;
        data["HoldMarginSale"] = pRspTotalPosition->HoldMarginSale;
        data["CurrPrice"] = pRspTotalPosition->CurrPrice;
        data["FloatProfit"] = pRspTotalPosition->FloatProfit;
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryTotalPosition(data, error, iRequestID, bIsLast);
};

void FutureApi::OnRspQryStrategyDetail(CFutureRspStrategyDetailField *pRspStrategyDetail, CFutureRspInfoField *pRspInfo, int iRequestID, bool bIsLast)
{
    gil_scoped_acquire acquire;
    dict data;
    if (pRspStrategyDetail)
    {
        data["StartegyCommodityNo"] = toUtf(pRspStrategyDetail->StartegyCommodityNo);
        data["StartegyContractNo"] = toUtf(pRspStrategyDetail->StartegyContractNo);
        data["Price"] = toUtf(pRspStrategyDetail->Price);
        data["LegNum"] = pRspStrategyDetail->LegNum;
        data["LastTradeDate"] = toUtf(pRspStrategyDetail->LastTradeDate);
        data["SeqId"] = pRspStrategyDetail->SeqId;
        data["CommodityNo"] = toUtf(pRspStrategyDetail->CommodityNo);
        data["ContractNo"] = toUtf(pRspStrategyDetail->ContractNo);
        data["Direct"] = toUtf(pRspStrategyDetail->Direct);
        data["Quantity"] = pRspStrategyDetail->Quantity;
        data["Model"] = toUtf(pRspStrategyDetail->Model);
        data["ModifyDate"] = toUtf(pRspStrategyDetail->ModifyDate);
        data["OrderMethod"] = toUtf(pRspStrategyDetail->OrderMethod);
        data["PriceTolerance"] = pRspStrategyDetail->PriceTolerance;
        data["PriceParam"] = pRspStrategyDetail->PriceParam;
        data["SuportQuantity"] = pRspStrategyDetail->SuportQuantity;
        data["MinMove"] = pRspStrategyDetail->MinMove;
        data["TimerOrder"] = pRspStrategyDetail->TimerOrder;
        data["TimerOrderBeyondNum"] = toUtf(pRspStrategyDetail->TimerOrderBeyondNum);
        data["TimerOrderPrice"] = pRspStrategyDetail->TimerOrderPrice;
        data["TimerOrderPriceBeyondNum"] = toUtf(pRspStrategyDetail->TimerOrderPriceBeyondNum);
        data["TimerOrderPriceTriggerNum"] = toUtf(pRspStrategyDetail->TimerOrderPriceTriggerNum);
        data["ZhiSunOrder"] = pRspStrategyDetail->ZhiSunOrder;
        data["ZhiSunOrderBeyondNum"] = toUtf(pRspStrategyDetail->ZhiSunOrderBeyondNum);
        data["TimerPingCang"] = pRspStrategyDetail->TimerPingCang;
        data["TimerPingCangBeyondNum"] = toUtf(pRspStrategyDetail->TimerPingCangBeyondNum);
        data["SafeDeep"] = pRspStrategyDetail->SafeDeep;
        data["MainRange"] = pRspStrategyDetail->MainRange;
    }
    dict error;
    if (pRspInfo)
    {
        error["ErrorID"] = pRspInfo->ErrorID;
        error["ErrorMsg"] = toUtf(pRspInfo->ErrorMsg);
    }
    this->onRspQryStrategyDetail(data, error, iRequestID, bIsLast);
};

///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

string FutureApi::getVersion()
{
    string version = this->api->GetVersion();
    return version;
};

void FutureApi::createFutureApi(bool recordLog, string logFileName)
{
    this->api = CFutureApi::CreateFutureApi(recordLog, logFileName.c_str());
    this->api->RegisterSpi(this);
};

void FutureApi::init()
{
    this->api->Init();
};

void FutureApi::release()
{
    this->api->Release();
};

int FutureApi::exit()
{
    this->api->RegisterSpi(NULL);
    this->api->Release();
    this->api = NULL;
    return 1;
};

void FutureApi::setHeartbeatTimeout(int timeout)
{
    this->api->SetHeartbeatTimeout(timeout);
};

void FutureApi::registerNameServer(string address)
{
    this->api->RegisterNameServer(address.c_str());
};

int FutureApi::reqUserLogin(const dict &req, int reqid)
{
    CFutureReqUserLoginField myreq = CFutureReqUserLoginField();
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

int FutureApi::reqUserLogout(const dict &req, int reqid)
{
    CFutureReqUserLogoutField myreq = CFutureReqUserLogoutField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UserId", myreq.UserId);
    getString(req, "AccountNo", myreq.AccountNo);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqUserLogout(&myreq, reqid);
    return i;
};

int FutureApi::reqSafeVerify(const dict &req, int reqid)
{
    CFutureReqSafeVerifyField myreq = CFutureReqSafeVerifyField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UserId", myreq.UserId);
    getString(req, "UserPwd", myreq.UserPwd);
    getString(req, "Type", myreq.Type);
    getString(req, "Question", myreq.Question);
    getString(req, "Answer", myreq.Answer);
    getString(req, "MobileNumber", myreq.MobileNumber);
    getString(req, "VerifyCode", myreq.VerifyCode);
    getString(req, "SaveMac", myreq.SaveMac);
    getString(req, "MacAddress", myreq.MacAddress);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqSafeVerify(&myreq, reqid);
    return i;
};

int FutureApi::reqVerifyCode(const dict &req, int reqid)
{
    CFutureReqVerifyCodeField myreq = CFutureReqVerifyCodeField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UserId", myreq.UserId);
    getString(req, "UserPwd", myreq.UserPwd);
    getString(req, "Type", myreq.Type);
    getString(req, "Question", myreq.Question);
    getString(req, "Answer", myreq.Answer);
    getString(req, "MobileNumber", myreq.MobileNumber);
    getString(req, "VerifyCode", myreq.VerifyCode);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqVerifyCode(&myreq, reqid);
    return i;
};

int FutureApi::reqSetVerifyQA(const dict &req, int reqid)
{
    CFutureReqSetVerifyQAField myreq = CFutureReqSetVerifyQAField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UserId", myreq.UserId);
    getString(req, "UserPwd", myreq.UserPwd);
    getString(req, "Type", myreq.Type);
    getString(req, "Question", myreq.Question);
    getString(req, "Answer", myreq.Answer);
    getString(req, "MobileNumber", myreq.MobileNumber);
    getString(req, "VerifyCode", myreq.VerifyCode);
    getString(req, "SaveMac", myreq.SaveMac);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqSetVerifyQA(&myreq, reqid);
    return i;
};

int FutureApi::reqGetQuestion(const dict &req, int reqid)
{
    CFutureReqGetQuestionField myreq = CFutureReqGetQuestionField();
    memset(&myreq, 0, sizeof(myreq));
    getInt(req, "Unused", &myreq.Unused);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqGetQuestion(&myreq, reqid);
    return i;
};

int FutureApi::reqOrderInsert(const dict &req, int reqid)
{
    CFutureReqOrderInsertField myreq = CFutureReqOrderInsertField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UserId", myreq.UserId);
    getString(req, "UserType", myreq.UserType);
    getString(req, "AccountNo", myreq.AccountNo);
    getString(req, "LocalNo", myreq.LocalNo);
    getString(req, "TradePwd", myreq.TradePwd);
    getString(req, "IsRiskOrder", myreq.IsRiskOrder);
    getString(req, "ExchangeCode", myreq.ExchangeCode);
    getString(req, "TreatyCode", myreq.TreatyCode);
    getString(req, "BuySale", myreq.BuySale);
    getString(req, "AddReduce", myreq.AddReduce);
    getString(req, "OrderNumber", myreq.OrderNumber);
    getString(req, "OrderPrice", myreq.OrderPrice);
    getString(req, "TradeType", myreq.TradeType);
    getString(req, "PriceType", myreq.PriceType);
    getString(req, "HtsType", myreq.HtsType);
    getString(req, "ForceID", myreq.ForceID);
    getString(req, "TriggerPrice", myreq.TriggerPrice);
    getString(req, "ValidDate", myreq.ValidDate);
    getString(req, "StrategyId", myreq.StrategyId);
    getString(req, "MaxShow", myreq.MaxShow);
    getString(req, "MinQty", myreq.MinQty);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqOrderInsert(&myreq, reqid);
    return i;
};

int FutureApi::reqOrderModify(const dict &req, int reqid)
{
    CFutureReqOrderModifyField myreq = CFutureReqOrderModifyField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "SystemNo", myreq.SystemNo);
    getString(req, "UserId", myreq.UserId);
    getString(req, "UserType", myreq.UserType);
    getString(req, "LocalNo", myreq.LocalNo);
    getString(req, "AccountNo", myreq.AccountNo);
    getString(req, "TradePwd", myreq.TradePwd);
    getString(req, "OrderNo", myreq.OrderNo);
    getString(req, "ExchangeCode", myreq.ExchangeCode);
    getString(req, "TreatyCode", myreq.TreatyCode);
    getString(req, "BuySale", myreq.BuySale);
    getString(req, "OrderNumber", myreq.OrderNumber);
    getString(req, "OrderPrice", myreq.OrderPrice);
    getString(req, "FilledNumber", myreq.FilledNumber);
    getString(req, "ModifyNumber", myreq.ModifyNumber);
    getString(req, "ModifyPrice", myreq.ModifyPrice);
    getString(req, "TradeType", myreq.TradeType);
    getString(req, "PriceType", myreq.PriceType);
    getString(req, "IsRiskOrder", myreq.IsRiskOrder);
    getString(req, "TriggerPrice", myreq.TriggerPrice);
    getString(req, "ModifyTriggerPrice", myreq.ModifyTriggerPrice);
    getString(req, "ValidDate", myreq.ValidDate);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqOrderModify(&myreq, reqid);
    return i;
};

int FutureApi::reqOrderCancel(const dict &req, int reqid)
{
    CFutureReqOrderCancelField myreq = CFutureReqOrderCancelField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UserId", myreq.UserId);
    getString(req, "UserType", myreq.UserType);
    getString(req, "LocalNo", myreq.LocalNo);
    getString(req, "AccountNo", myreq.AccountNo);
    getString(req, "TradePwd", myreq.TradePwd);
    getString(req, "IsSimulation", myreq.IsSimulation);
    getString(req, "SystemNo", myreq.SystemNo);
    getString(req, "OrderNo", myreq.OrderNo);
    getString(req, "ExchangeCode", myreq.ExchangeCode);
    getString(req, "TreatyCode", myreq.TreatyCode);
    getString(req, "BuySale", myreq.BuySale);
    getString(req, "OrderNumber", myreq.OrderNumber);
    getString(req, "OrderPrice", myreq.OrderPrice);
    getString(req, "FilledNumber", myreq.FilledNumber);
    getString(req, "TradeType", myreq.TradeType);
    getString(req, "PriceType", myreq.PriceType);
    getString(req, "HtsType", myreq.HtsType);
    getString(req, "IsRiskOrder", myreq.IsRiskOrder);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqOrderCancel(&myreq, reqid);
    return i;
};

int FutureApi::reqPasswordUpdate(const dict &req, int reqid)
{
    CFutureReqPasswordUpdateField myreq = CFutureReqPasswordUpdateField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UserId", myreq.UserId);
    getString(req, "OldPassword", myreq.OldPassword);
    getString(req, "NewPassword", myreq.NewPassword);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqPasswordUpdate(&myreq, reqid);
    return i;
};

int FutureApi::reqQryOrder(const dict &req, int reqid)
{
    CFutureQryOrderField myreq = CFutureQryOrderField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UserId", myreq.UserId);
    getString(req, "UserType", myreq.UserType);
    getString(req, "AccountNo", myreq.AccountNo);
    getString(req, "TradePwd", myreq.TradePwd);
    getString(req, "IsSimulation", myreq.IsSimulation);
    getString(req, "OrderNo", myreq.OrderNo);
    getString(req, "OrderDateTime", myreq.OrderDateTime);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryOrder(&myreq, reqid);
    return i;
};

int FutureApi::reqQryTrade(const dict &req, int reqid)
{
    CFutureQryTradeField myreq = CFutureQryTradeField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UserId", myreq.UserId);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryTrade(&myreq, reqid);
    return i;
};

int FutureApi::reqQryCapital(const dict &req, int reqid)
{
    CFutureQryCapitalField myreq = CFutureQryCapitalField();
    memset(&myreq, 0, sizeof(myreq));
    getChar(req, "Unused", &myreq.Unused);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryCapital(&myreq, reqid);
    return i;
};

int FutureApi::reqQryVersion(const dict &req, int reqid)
{
    CFutureQryVersionField myreq = CFutureQryVersionField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UserId", myreq.UserId);
    getString(req, "UserPwd", myreq.UserPwd);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryVersion(&myreq, reqid);
    return i;
};

int FutureApi::reqQryCurrency(const dict &req, int reqid)
{
    CFutureQryCurrencyField myreq = CFutureQryCurrencyField();
    memset(&myreq, 0, sizeof(myreq));
    getChar(req, "Unused", &myreq.Unused);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryCurrency(&myreq, reqid);
    return i;
};

int FutureApi::reqQryExchange(const dict &req, int reqid)
{
    CFutureQryExchangeField myreq = CFutureQryExchangeField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ProductGroupID", myreq.ProductGroupID);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryExchange(&myreq, reqid);
    return i;
};

int FutureApi::reqQryPosition(const dict &req, int reqid)
{
    CFutureQryPositionField myreq = CFutureQryPositionField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryPosition(&myreq, reqid);
    return i;
};

int FutureApi::reqQryStrategy(const dict &req, int reqid)
{
    CFutureQryStrategyField myreq = CFutureQryStrategyField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeNo", myreq.ExchangeNo);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryStrategy(&myreq, reqid);
    return i;
};

int FutureApi::reqQryCommodity(const dict &req, int reqid)
{
    CFutureQryCommodityField myreq = CFutureQryCommodityField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "UpdateDate", myreq.UpdateDate);
    getString(req, "ExchangeNo", myreq.ExchangeNo);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryCommodity(&myreq, reqid);
    return i;
};

int FutureApi::reqQryInstrument(const dict &req, int reqid)
{
    CFutureQryInstrumentField myreq = CFutureQryInstrumentField();
    memset(&myreq, 0, sizeof(myreq));
    getInt(req, "PageIndex", &myreq.PageIndex);
    getString(req, "ExchangeNo", myreq.ExchangeNo);
    getString(req, "CommodityNo", myreq.CommodityNo);
    getString(req, "CommodityType", myreq.CommodityType);
    getString(req, "ContractNo", myreq.ContractNo);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryInstrument(&myreq, reqid);
    return i;
};

int FutureApi::reqQryExchangeTime(const dict &req, int reqid)
{
    CFutureQryExchangeTimeField myreq = CFutureQryExchangeTimeField();
    memset(&myreq, 0, sizeof(myreq));
    getChar(req, "Unused", &myreq.Unused);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryExchangeTime(&myreq, reqid);
    return i;
};

int FutureApi::reqQryCommodityTime(const dict &req, int reqid)
{
    CFutureQryCommodityTimeField myreq = CFutureQryCommodityTimeField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "ExchangeNo", myreq.ExchangeNo);
    getString(req, "CommodityNo", myreq.CommodityNo);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryCommodityTime(&myreq, reqid);
    return i;
};

int FutureApi::reqQryTotalPosition(const dict &req, int reqid)
{
    CFutureQryTotalPositionField myreq = CFutureQryTotalPositionField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "AccountNo", myreq.AccountNo);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryTotalPosition(&myreq, reqid);
    return i;
};

int FutureApi::reqQryStrategyDetail(const dict &req, int reqid)
{
    CFutureQryStrategyDetailField myreq = CFutureQryStrategyDetailField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "StartegyCommodityNo", myreq.StartegyCommodityNo);
    getString(req, "ErrorDescription", myreq.ErrorDescription);
    int i = this->api->ReqQryStrategyDetail(&myreq, reqid);
    return i;
};

///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyFutureApi : public FutureApi
{
public:
    using FutureApi::FutureApi;

    void onFrontConnected() override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onFrontConnected);
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
            PYBIND11_OVERLOAD(void, FutureApi, onFrontDisconnected, reqid);
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
            PYBIND11_OVERLOAD(void, FutureApi, onHeartBeatWarning, reqid);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspNeedVerify(bool firstLogin, bool hasSetQA) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspNeedVerify, firstLogin, hasSetQA);
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
            PYBIND11_OVERLOAD(void, FutureApi, onRspUserLogin, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspUserLogout(const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspUserLogout, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspVerifyCode(const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspVerifyCode, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspSafeVerify(const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspSafeVerify, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspSetVerifyQA(const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspSetVerifyQA, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspAccount(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspAccount, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQuestion(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQuestion, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspOrderInsert, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspOrderModify(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspOrderModify, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspOrderCancel(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspOrderCancel, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspPasswordUpdate(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspPasswordUpdate, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnTrade(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRtnTrade, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnOrder(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRtnOrder, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnCapital(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRtnCapital, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRtnPosition(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRtnPosition, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryOrder(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryOrder, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryTrade(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryTrade, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryCapital(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryCapital, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryVersion(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryVersion, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryPosition(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryPosition, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryCurrency(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryCurrency, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryExchange(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryExchange, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryStrategy(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryStrategy, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryCommodity(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryCommodity, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryInstrument(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryInstrument, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryExchangeTime(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryExchangeTime, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryCommodityTime(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryCommodityTime, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryTotalPosition(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryTotalPosition, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };

    void onRspQryStrategyDetail(const dict &data, const dict &error, int reqid, bool last) override
    {
        try
        {
            PYBIND11_OVERLOAD(void, FutureApi, onRspQryStrategyDetail, data, error, reqid, last);
        }
        catch (const error_already_set &e)
        {
            cout << e.what() << endl;
        }
    };
};


PYBIND11_MODULE(vndafuture, m)
{
    class_<FutureApi, PyFutureApi> FutureApi(m, "FutureApi", module_local());
    FutureApi
        .def(init<>())
        .def("getVersion", &FutureApi::getVersion)
        .def("createFutureApi", &FutureApi::createFutureApi)
        .def("init", &FutureApi::init)
        .def("release", &FutureApi::release)
        .def("exit", &FutureApi::exit)
        .def("setHeartbeatTimeout", &FutureApi::setHeartbeatTimeout)
        .def("registerNameServer", &FutureApi::registerNameServer)
        .def("reqUserLogin", &FutureApi::reqUserLogin)
        .def("reqUserLogout", &FutureApi::reqUserLogout)
        .def("reqSafeVerify", &FutureApi::reqSafeVerify)
        .def("reqVerifyCode", &FutureApi::reqVerifyCode)
        .def("reqSetVerifyQA", &FutureApi::reqSetVerifyQA)
        .def("reqGetQuestion", &FutureApi::reqGetQuestion)
        .def("reqOrderInsert", &FutureApi::reqOrderInsert)
        .def("reqOrderModify", &FutureApi::reqOrderModify)
        .def("reqOrderCancel", &FutureApi::reqOrderCancel)
        .def("reqPasswordUpdate", &FutureApi::reqPasswordUpdate)
        .def("reqQryOrder", &FutureApi::reqQryOrder)
        .def("reqQryTrade", &FutureApi::reqQryTrade)
        .def("reqQryCapital", &FutureApi::reqQryCapital)
        .def("reqQryVersion", &FutureApi::reqQryVersion)
        .def("reqQryCurrency", &FutureApi::reqQryCurrency)
        .def("reqQryExchange", &FutureApi::reqQryExchange)
        .def("reqQryPosition", &FutureApi::reqQryPosition)
        .def("reqQryStrategy", &FutureApi::reqQryStrategy)
        .def("reqQryCommodity", &FutureApi::reqQryCommodity)
        .def("reqQryInstrument", &FutureApi::reqQryInstrument)
        .def("reqQryExchangeTime", &FutureApi::reqQryExchangeTime)
        .def("reqQryCommodityTime", &FutureApi::reqQryCommodityTime)
        .def("reqQryTotalPosition", &FutureApi::reqQryTotalPosition)
        .def("reqQryStrategyDetail", &FutureApi::reqQryStrategyDetail)

        .def("onFrontConnected", &FutureApi::onFrontConnected)
        .def("onFrontDisconnected", &FutureApi::onFrontDisconnected)
        .def("onHeartBeatWarning", &FutureApi::onHeartBeatWarning)
        .def("onRspNeedVerify", &FutureApi::onRspNeedVerify)
        .def("onRspUserLogin", &FutureApi::onRspUserLogin)
        .def("onRspUserLogout", &FutureApi::onRspUserLogout)
        .def("onRspVerifyCode", &FutureApi::onRspVerifyCode)
        .def("onRspSafeVerify", &FutureApi::onRspSafeVerify)
        .def("onRspSetVerifyQA", &FutureApi::onRspSetVerifyQA)
        .def("onRspAccount", &FutureApi::onRspAccount)
        .def("onRspQuestion", &FutureApi::onRspQuestion)
        .def("onRspOrderInsert", &FutureApi::onRspOrderInsert)
        .def("onRspOrderModify", &FutureApi::onRspOrderModify)
        .def("onRspOrderCancel", &FutureApi::onRspOrderCancel)
        .def("onRspPasswordUpdate", &FutureApi::onRspPasswordUpdate)
        .def("onRtnTrade", &FutureApi::onRtnTrade)
        .def("onRtnOrder", &FutureApi::onRtnOrder)
        .def("onRtnCapital", &FutureApi::onRtnCapital)
        .def("onRtnPosition", &FutureApi::onRtnPosition)
        .def("onRspQryOrder", &FutureApi::onRspQryOrder)
        .def("onRspQryTrade", &FutureApi::onRspQryTrade)
        .def("onRspQryCapital", &FutureApi::onRspQryCapital)
        .def("onRspQryVersion", &FutureApi::onRspQryVersion)
        .def("onRspQryPosition", &FutureApi::onRspQryPosition)
        .def("onRspQryCurrency", &FutureApi::onRspQryCurrency)
        .def("onRspQryExchange", &FutureApi::onRspQryExchange)
        .def("onRspQryStrategy", &FutureApi::onRspQryStrategy)
        .def("onRspQryCommodity", &FutureApi::onRspQryCommodity)
        .def("onRspQryInstrument", &FutureApi::onRspQryInstrument)
        .def("onRspQryExchangeTime", &FutureApi::onRspQryExchangeTime)
        .def("onRspQryCommodityTime", &FutureApi::onRspQryCommodityTime)
        .def("onRspQryTotalPosition", &FutureApi::onRspQryTotalPosition)
        .def("onRspQryStrategyDetail", &FutureApi::onRspQryStrategyDetail)
        ;

}
