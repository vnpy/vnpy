// vnuftmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnnsttd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------
void TdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogin(CUftRspUserLoginField* pRspUserLogin, CUftRspInfoField* pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;
	if (pRspUserLogin)
	{
		CUftRspUserLoginField *task_data = new CUftRspUserLoginField();
		*task_data = *pRspUserLogin;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		CUftRspInfoField *task_error = new CUftRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnAnsOrderInsert(CUftAnsOrderInsertField *pOrderRsp, CUftRspErrorField* pError)
{
	Task task = Task();
	task.task_name = ONANSORDERINSERT;
	if (pOrderRsp)
	{
		CUftAnsOrderInsertField *task_data = new CUftAnsOrderInsertField();
		*task_data = *pOrderRsp;
		task.task_data = task_data;
	}
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderInsert(CUftRspnOrderInsertField *pOrderRsp, CUftRspErrorField* pError)
{
	Task task = Task();
	task.task_name = ONRSPORDERINSERT;
	if (pOrderRsp)
	{
		CUftRspnOrderInsertField *task_data = new CUftRspnOrderInsertField();
		*task_data = *pOrderRsp;
		task.task_data = task_data;
	}
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnAnsOrderAction(CUftAnsOrderActionField *pOrderAction, CUftRspErrorField* pError)
{
	Task task = Task();
	task.task_name = ONANSORDERACTION;
	if (pOrderAction)
	{
		CUftAnsOrderActionField *task_data = new CUftAnsOrderActionField();
		*task_data = *pOrderAction;
		task.task_data = task_data;
	}
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderAction(CUftRspnOrderActionField *pOrderAction, CUftRspErrorField* pError)
{
	Task task = Task();
	task.task_name = ONRSPORDERACTION;
	if (pOrderAction)
	{
		CUftRspnOrderActionField *task_data = new CUftRspnOrderActionField();
		*task_data = *pOrderAction;
		task.task_data = task_data;
	}
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnOrderRtn(CUftRtnnOrderField* pOrder)
{
	Task task = Task();
	task.task_name = ONORDERRTN;
	if (pOrder)
	{
		CUftRtnnOrderField *task_data = new CUftRtnnOrderField();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnTradeRtn(CUftRtnnTradeField* pOrder)
{
	Task task = Task();
	task.task_name = ONTRADERTN;
	if (pOrder)
	{
		CUftRtnnTradeField *task_data = new CUftRtnnTradeField();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspTradingAccount(CUftAnsQueryFundField *pRspFund)
{
	Task task = Task();
	task.task_name = ONRSPTRADINGACCOUNT;
	if (pRspFund)
	{
		CUftAnsQueryFundField *task_data = new CUftAnsQueryFundField();
		*task_data = *pRspFund;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspError(CUftRspErrorField* pError)
{
	Task task = Task();
	task.task_name = ONRSPERROR;
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryOrder(CUftAnsQueryOrderField *pEntrust, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;
	if (pEntrust)
	{
		CUftAnsQueryOrderField *task_data = new CUftAnsQueryOrderField();
		*task_data = *pEntrust;
		task.task_data = task_data;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTrade(CUftAnsQueryTradeField *pTrade, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADE;
	if (pTrade)
	{
		CUftAnsQueryTradeField *task_data = new CUftAnsQueryTradeField();
		*task_data = *pTrade;
		task.task_data = task_data;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryInvestorPosition(CUftAnsQueryPositionField *pInvestorPosition, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITION;
	if (pInvestorPosition)
	{
		CUftAnsQueryPositionField *task_data = new CUftAnsQueryPositionField();
		*task_data = *pInvestorPosition;
		task.task_data = task_data;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryChangePwd()
{
	Task task = Task();
	task.task_name = ONRSPQRYCHANGEPWD;
	this->task_queue.push(task);
};

void TdApi::OnRspLogout(const char* szMsg)
{
	Task task = Task();
	task.task_name = ONRSPLOGOUT;
	if (szMsg)
	{
		char *task_data = new char();
		*task_data = *szMsg;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnInstrumentStatus(CUftRtnInstrumentStatusField *pInstStatus)
{
	Task task = Task();
	task.task_name = ONRTNINSTRUMENTSTATUS;
	if (pInstStatus)
	{
		CUftRtnInstrumentStatusField *task_data = new CUftRtnInstrumentStatusField();
		*task_data = *pInstStatus;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspTest(CUftRspTest *pTest)
{
	Task task = Task();
	task.task_name = ONRSPTEST;
	if (pTest)
	{
		CUftRspTest *task_data = new CUftRspTest();
		*task_data = *pTest;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderInsert(CUftRspErrorField* pError)
{
	Task task = Task();
	task.task_name = ONERRRTNORDERINSERT;
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderAction(CUftRspErrorField* pError)
{
	Task task = Task();
	task.task_name = ONERRRTNORDERACTION;
	if (pError)
	{
		CUftRspErrorField *task_error = new CUftRspErrorField();
		*task_error = *pError;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};




///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void TdApi::processTask()
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

			case ONRSPUSERLOGIN:
			{
				this->processRspUserLogin(&task);
				break;
			}

			case ONANSORDERINSERT:
			{
				this->processAnsOrderInsert(&task);
				break;
			}

			case ONRSPORDERINSERT:
			{
				this->processRspOrderInsert(&task);
				break;
			}

			case ONANSORDERACTION:
			{
				this->processAnsOrderAction(&task);
				break;
			}

			case ONRSPORDERACTION:
			{
				this->processRspOrderAction(&task);
				break;
			}

			case ONORDERRTN:
			{
				this->processOrderRtn(&task);
				break;
			}

			case ONTRADERTN:
			{
				this->processTradeRtn(&task);
				break;
			}

			case ONRSPTRADINGACCOUNT:
			{
				this->processRspTradingAccount(&task);
				break;
			}

			case ONRSPERROR:
			{
				this->processRspError(&task);
				break;
			}

			case ONRSPQRYORDER:
			{
				this->processRspQryOrder(&task);
				break;
			}

			case ONRSPQRYTRADE:
			{
				this->processRspQryTrade(&task);
				break;
			}

			case ONRSPQRYINVESTORPOSITION:
			{
				this->processRspQryInvestorPosition(&task);
				break;
			}

			case ONRSPQRYCHANGEPWD:
			{
				this->processRspQryChangePwd(&task);
				break;
			}

			case ONRSPLOGOUT:
			{
				this->processRspLogout(&task);
				break;
			}

			case ONRTNINSTRUMENTSTATUS:
			{
				this->processRtnInstrumentStatus(&task);
				break;
			}

			case ONRSPTEST:
			{
				this->processRspTest(&task);
				break;
			}

			case ONERRRTNORDERINSERT:
			{
				this->processErrRtnOrderInsert(&task);
				break;
			}

			case ONERRRTNORDERACTION:
			{
				this->processErrRtnOrderAction(&task);
				break;
			}



			};
        }
    }
    catch (const TerminatedError&)
    {
    }
};

void TdApi::processFrontConnected(Task *task)
{
	this->onFrontConnected();
};

void TdApi::processRspUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRspUserLoginField *task_data = (CUftRspUserLoginField*)task->task_data;
		data["MaxOrderRef"] = task_data->MaxOrderRef;
		data["TradeDate"] = task_data->TradeDate;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUftRspInfoField *task_error = (CUftRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserLogin(data, error);
};

void TdApi::processAnsOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftAnsOrderInsertField *task_data = (CUftAnsOrderInsertField*)task->task_data;
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		data["ProcessTime"] = task_data->ProcessTime;
		data["TotalTime"] = task_data->TotalTime;
		data["ExchangeTime"] = task_data->ExchangeTime;
		data["SenderID"] = task_data->SenderID;
		data["LocalTimeDelay"] = task_data->LocalTimeDelay;
		data["StockCode"] = toUtf(task_data->StockCode);
		data["Direction"] = task_data->Direction;
		data["EntrustType"] = task_data->EntrustType;
		data["Price"] = task_data->Price;
		data["Amount"] = task_data->Amount;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onAnsOrderInsert(data, error);
};

void TdApi::processRspOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRspnOrderInsertField *task_data = (CUftRspnOrderInsertField*)task->task_data;
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		data["ProcessTime"] = task_data->ProcessTime;
		data["TotalTime"] = task_data->TotalTime;
		data["ExchangeTime"] = task_data->ExchangeTime;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["OrderStatus"] = task_data->OrderStatus;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onRspOrderInsert(data, error);
};

void TdApi::processAnsOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftAnsOrderActionField *task_data = (CUftAnsOrderActionField*)task->task_data;
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["OrderLocalID"] = toUtf(task_data->OrderLocalID);
		data["SenderID"] = task_data->SenderID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onAnsOrderAction(data, error);
};

void TdApi::processRspOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRspnOrderActionField *task_data = (CUftRspnOrderActionField*)task->task_data;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["OrderLocalID"] = toUtf(task_data->OrderLocalID);
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onRspOrderAction(data, error);
};

void TdApi::processOrderRtn(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRtnnOrderField *task_data = (CUftRtnnOrderField*)task->task_data;
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		data["ProcessTime"] = task_data->ProcessTime;
		data["TotalTime"] = task_data->TotalTime;
		data["ExchangeTime"] = task_data->ExchangeTime;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["VolumeTotal"] = task_data->VolumeTotal;
		data["OrderStatus"] = task_data->OrderStatus;
		data["StockCode"] = toUtf(task_data->StockCode);
		data["EntrustType"] = task_data->EntrustType;
		data["Direction"] = task_data->Direction;
		data["Price"] = task_data->Price;
		data["Amount"] = task_data->Amount;
		delete task_data;
	}
	this->onOrderRtn(data);
};

void TdApi::processTradeRtn(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRtnnTradeField *task_data = (CUftRtnnTradeField*)task->task_data;
		data["BusinessPrice"] = task_data->BusinessPrice;
		data["BusinessTime"] = task_data->BusinessTime;
		data["BusinessAmount"] = task_data->BusinessAmount;
		data["fare"] = task_data->fare;
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		data["BusinessId"] = toUtf(task_data->BusinessId);
		data["OrderSysID"] = task_data->OrderSysID;
		data["session_id"] = task_data->session_id;
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["reserve"] = task_data->reserve;
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["StockCode"] = toUtf(task_data->StockCode);
		delete task_data;
	}
	this->onTradeRtn(data);
};

void TdApi::processRspTradingAccount(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftAnsQueryFundField *task_data = (CUftAnsQueryFundField*)task->task_data;
		data["EnabledBalance"] = task_data->EnabledBalance;
		data["Deposit"] = task_data->Deposit;
		data["BeginBalance"] = task_data->BeginBalance;
		data["Margin"] = task_data->Margin;
		data["Profit"] = task_data->Profit;
		data["TotalFare"] = task_data->TotalFare;
		data["CurrBalance"] = task_data->CurrBalance;
		data["floating_gain_loss"] = task_data->floating_gain_loss;
		data["FrozenBalance"] = task_data->FrozenBalance;
		data["SenderID"] = task_data->SenderID;
		data["EnablePurQuota"] = task_data->EnablePurQuota;
		delete task_data;
	}
	this->onRspTradingAccount(data);
};

void TdApi::processRspError(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onRspError(error);
};

void TdApi::processRspQryOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftAnsQueryOrderField *task_data = (CUftAnsQueryOrderField*)task->task_data;
		data["Order"] = task_data->Order;
		data["OrderRef"] = task_data->OrderRef;
		data["MaginCheck"] = task_data->MaginCheck;
		data["VolumeTotal"] = task_data->VolumeTotal;
		data["OrderStatus"] = task_data->OrderStatus;
		data["session_id"] = task_data->session_id;
		data["reserve"] = task_data->reserve;
		data["OrderTime"] = task_data->OrderTime;
		data["SenderID"] = task_data->SenderID;
		data["ErrorID"] = task_data->ErrorID;
		data["OrderIndex"] = task_data->OrderIndex;
		data["StockCode"] = toUtf(task_data->StockCode);
		data["Direction"] = task_data->Direction;
		data["EntrustType"] = task_data->EntrustType;
		data["CashMargin"] = task_data->CashMargin;
		data["TGWNo"] = task_data->TGWNo;
		data["Price"] = task_data->Price;
		data["Amount"] = task_data->Amount;
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["ClOrdID"] = toUtf(task_data->ClOrdID);
		delete task_data;
	}
	this->onRspQryOrder(data, task->task_last);
};

void TdApi::processRspQryTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftAnsQueryTradeField *task_data = (CUftAnsQueryTradeField*)task->task_data;
		data["BusinessPrice"] = task_data->BusinessPrice;
		data["BusinessTime"] = task_data->BusinessTime;
		data["BusinessAmount"] = task_data->BusinessAmount;
		data["fare"] = task_data->fare;
		data["OrderRef"] = task_data->OrderRef;
		data["OrderIndex"] = task_data->OrderIndex;
		data["BusinessId"] = toUtf(task_data->BusinessId);
		data["OrderSysID"] = toUtf(task_data->OrderSysID);
		data["session_id"] = task_data->session_id;
		data["Direction"] = task_data->Direction;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["StockCode"] = toUtf(task_data->StockCode);
		delete task_data;
	}
	this->onRspQryTrade(data, task->task_last);
};

void TdApi::processRspQryInvestorPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftAnsQueryPositionField *task_data = (CUftAnsQueryPositionField*)task->task_data;
		data["futu_code"] = toUtf(task_data->futu_code);
		data["entrust_bs"] = task_data->entrust_bs;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["reserve"] = toUtf(task_data->reserve);
		data["OldEnableAmount"] = task_data->OldEnableAmount;
		data["OldCurrentAmount"] = task_data->OldCurrentAmount;
		data["TodayEnableAmount"] = task_data->TodayEnableAmount;
		data["TodayCurrentAmount"] = task_data->TodayCurrentAmount;
		data["OldOpenBalance"] = task_data->OldOpenBalance;
		data["TodayOpenBalance"] = task_data->TodayOpenBalance;
		data["HoldMargin"] = task_data->HoldMargin;
		data["StockCode"] = toUtf(task_data->StockCode);
		data["EnableAmount"] = task_data->EnableAmount;
		data["CurrentAmount"] = task_data->CurrentAmount;
		delete task_data;
	}
	this->onRspQryInvestorPosition(data, task->task_last);
};

void TdApi::processRspQryChangePwd(Task *task)
{
	this->onRspQryChangePwd();
};

void TdApi::processRspLogout(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspLogout(task->task_str);
};

void TdApi::processRtnInstrumentStatus(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRtnInstrumentStatusField *task_data = (CUftRtnInstrumentStatusField*)task->task_data;
		data["SettlementGroupID"] = toUtf(task_data->SettlementGroupID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["Status"] = task_data->Status;
		data["TradingSegmentSN"] = task_data->TradingSegmentSN;
		data["EnterTime"] = toUtf(task_data->EnterTime);
		data["EnterReason"] = task_data->EnterReason;
		data["PlatformID"] = task_data->PlatformID;
		data["PlatformState"] = task_data->PlatformState;
		delete task_data;
	}
	this->onRtnInstrumentStatus(data);
};

void TdApi::processRspTest(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CUftRspTest *task_data = (CUftRspTest*)task->task_data;
		data["TimeDelay"] = task_data->TimeDelay;
		delete task_data;
	}
	this->onRspTest(data);
};

void TdApi::processErrRtnOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onErrRtnOrderInsert(error);
};

void TdApi::processErrRtnOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CUftRspErrorField *task_error = (CUftRspErrorField*)task->task_error;
		error["ErrorNo"] = task_error->ErrorNo;
		error["OrderIndex"] = task_error->OrderIndex;
		error["OrderRef"] = task_error->OrderRef;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		error["SendID"] = task_error->SendID;
		delete task_error;
	}
	this->onErrRtnOrderAction(error);
};



///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::newTradeApi(int nCnnMode)
{
	this->api = CreateUft4Shfe_TraderApi(nCnnMode);
	this->api->RegisterSpi(this);
};

int TdApi::init(string szAccount, string szPwd)
{
	this->active = true;
	this->task_thread = thread(&TdApi::processTask, this);

	int i = this->api->Init((char*)szAccount.c_str(), (char*)szPwd.c_str());
	return i;
};

int TdApi::join()
{
	int i = this->api->Join();
	return i;
};

int TdApi::exit()
{
	this->active = false;
	this->task_queue.terminate();
	this->task_thread.join();

	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	return 1;
};

int TdApi::reqUserLogin()
{
	int i = this->api->ReqUserLogin();
	return i;
};

int TdApi::reqUserLogout()
{
	int i = this->api->ReqUserLogout();
	return i;
};

int TdApi::reqOrderInsert(string szCode, char bs, char kp, int dbPrice, int nVolume, int nOrderRef)
{
	int i = this->api->ReqOrderInsert((char*)szCode.c_str(), (T_UFT_FtdcOrderBs) bs, kp, dbPrice, nVolume, nOrderRef);
	return i;
}


int TdApi::reqOrderAction(int nOrderIndex, int nOrderRef)
{

	int i = this->api->ReqOrderAction(nOrderIndex, nOrderRef);
	return i;
};

int TdApi::reqTradingAccount()
{
	int i = this->api->ReqTradingAccount();
	return i;
};

int TdApi::reqQryOrder(string szInstrumentID, int nStartTime, int nEndTime, string szOrderSysID, int nOrderRef, int nOrderIndex)
{
	int i = this->api->ReqQryOrder((char*)szInstrumentID.c_str(), nStartTime, nEndTime, (char*)szOrderSysID.c_str(), nOrderRef, nOrderIndex);
	return i;
};

int TdApi::reqQryTrade(string szInstrumentID, int nStartTime, int nEndTime, string szOrderSysID, int nOrderIndex, int nOrderRef)
{

	int i = this->api->ReqQryTrade((char*)szInstrumentID.c_str(), nStartTime, nEndTime, (char*)szOrderSysID.c_str(), nOrderIndex, nOrderRef);
	return i;
};

int TdApi::reqQryInvestorPosition(string szInstrumentID)
{

	int i = this->api->ReqQryInvestorPosition((char*)szInstrumentID.c_str());
	return i;
};

int TdApi::reqChangePwd(string szNewPwd, string szOldPwd)
{

	int i = this->api->ReqChangePwd((char*)szNewPwd.c_str(), (char*)szOldPwd.c_str());
	return i;
};

int TdApi::reqQryTest()
{
	int i = this->api->ReqQryTest();
	return i;
};


uint64_t TdApi::getToken()
{
	int i = this->api->GetToken();
	return i;
};

int TdApi::getReqPort()
{
	int i = this->api->GetReqPort();
	return i;
};


///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyTdApi : public TdApi
{
public:
    using TdApi::TdApi;
    

	void onFrontConnected() override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onFrontConnected);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspUserLogin(const dict &data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspUserLogin, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onAnsOrderInsert(const dict &data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onAnsOrderInsert, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspOrderInsert(const dict &data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspOrderInsert, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onAnsOrderAction(const dict &data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onAnsOrderAction, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspOrderAction(const dict &data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspOrderAction, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onOrderRtn(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onOrderRtn, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onTradeRtn(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onTradeRtn, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspTradingAccount(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspTradingAccount, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspError(const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspError, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryOrder(const dict &data, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryOrder, data, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryTrade(const dict &data, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryTrade, data, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryInvestorPosition(const dict &data, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryInvestorPosition, data, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryChangePwd() override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryChangePwd);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspLogout(string msg) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspLogout, msg);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnInstrumentStatus(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnInstrumentStatus, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspTest(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspTest, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onErrRtnOrderInsert(const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onErrRtnOrderInsert, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onErrRtnOrderAction(const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onErrRtnOrderAction, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

};


PYBIND11_MODULE(vnnsttd, m)
{
    class_<TdApi, PyTdApi> TdApi(m, "TdApi", module_local());
	TdApi
		.def(init<>())
		.def("newTradeApi", &TdApi::newTradeApi)
		.def("init", &TdApi::init)
		.def("join", &TdApi::join)
		.def("exit", &TdApi::exit)

		.def("reqUserLogin", &TdApi::reqUserLogin)
		.def("reqUserLogout", &TdApi::reqUserLogout)
		.def("reqOrderInsert", &TdApi::reqOrderInsert)
		.def("reqOrderAction", &TdApi::reqOrderAction)
		.def("reqTradingAccount", &TdApi::reqTradingAccount)
		.def("reqQryOrder", &TdApi::reqQryOrder)
		.def("reqQryTrade", &TdApi::reqQryTrade)
		.def("reqQryInvestorPosition", &TdApi::reqQryInvestorPosition)
		.def("reqChangePwd", &TdApi::reqChangePwd)
		.def("reqQryTest", &TdApi::reqQryTest)
		.def("getToken", &TdApi::getToken)
		.def("getReqPort", &TdApi::getReqPort)

		.def("onFrontConnected", &TdApi::onFrontConnected)
		.def("onRspUserLogin", &TdApi::onRspUserLogin)
		.def("onAnsOrderInsert", &TdApi::onAnsOrderInsert)
		.def("onRspOrderInsert", &TdApi::onRspOrderInsert)
		.def("onAnsOrderAction", &TdApi::onAnsOrderAction)
		.def("onRspOrderAction", &TdApi::onRspOrderAction)
		.def("onOrderRtn", &TdApi::onOrderRtn)
		.def("onTradeRtn", &TdApi::onTradeRtn)
		.def("onRspTradingAccount", &TdApi::onRspTradingAccount)
		.def("onRspError", &TdApi::onRspError)
		.def("onRspQryOrder", &TdApi::onRspQryOrder)
		.def("onRspQryTrade", &TdApi::onRspQryTrade)
		.def("onRspQryInvestorPosition", &TdApi::onRspQryInvestorPosition)
		.def("onRspQryChangePwd", &TdApi::onRspQryChangePwd)
		.def("onRspLogout", &TdApi::onRspLogout)
		.def("onRtnInstrumentStatus", &TdApi::onRtnInstrumentStatus)
		.def("onRspTest", &TdApi::onRspTest)
		.def("onErrRtnOrderInsert", &TdApi::onErrRtnOrderInsert)
		.def("onErrRtnOrderAction", &TdApi::onErrRtnOrderAction)
		;



}
