
// vntapmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vntapmd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void MdApi::OnRspLogin(int errorCode, TapAPIQuotLoginRspInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPLOGIN;
	task.task_int = errorCode;
	if (info)
	{
		TapAPIQuotLoginRspInfo *task_data = new TapAPIQuotLoginRspInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnAPIReady()
{
	Task task = Task();
	task.task_name = ONAPIREADY;
	this->task_queue.push(task);
};

void MdApi::OnDisconnect(int reasonCode)
{
	Task task = Task();
	task.task_name = ONDISCONNECT;
	task.task_int = reasonCode;
	this->task_queue.push(task);
};

void MdApi::OnRspQryCommodity(unsigned int sessionID, int errorCode, char isLast, TapAPIQuoteCommodityInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYCOMMODITY;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIQuoteCommodityInfo *task_data = new TapAPIQuoteCommodityInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspQryContract(unsigned int sessionID, int errorCode, char isLast, TapAPIQuoteContractInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYCONTRACT;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIQuoteContractInfo *task_data = new TapAPIQuoteContractInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspSubscribeQuote(unsigned int sessionID, int errorCode, char isLast, TapAPIQuoteWhole *info)
{
	Task task = Task();
	task.task_name = ONRSPSUBSCRIBEQUOTE;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIQuoteWhole *task_data = new TapAPIQuoteWhole();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRspUnSubscribeQuote(unsigned int sessionID, int errorCode, char isLast, TapAPIContract *info)
{
	Task task = Task();
	task.task_name = ONRSPUNSUBSCRIBEQUOTE;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIContract *task_data = new TapAPIContract();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnRtnQuote(TapAPIQuoteWhole *info)
{
	Task task = Task();
	task.task_name = ONRTNQUOTE;
	if (info)
	{
		TapAPIQuoteWhole *task_data = new TapAPIQuoteWhole();
		*task_data = *info;
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
			case ONRSPLOGIN:
			{
				this->processRspLogin(&task);
				break;
			}

			case ONAPIREADY:
			{
				this->processAPIReady(&task);
				break;
			}

			case ONDISCONNECT:
			{
				this->processDisconnect(&task);
				break;
			}

			case ONRSPQRYCOMMODITY:
			{
				this->processRspQryCommodity(&task);
				break;
			}

			case ONRSPQRYCONTRACT:
			{
				this->processRspQryContract(&task);
				break;
			}

			case ONRSPSUBSCRIBEQUOTE:
			{
				this->processRspSubscribeQuote(&task);
				break;
			}

			case ONRSPUNSUBSCRIBEQUOTE:
			{
				this->processRspUnSubscribeQuote(&task);
				break;
			}

			case ONRTNQUOTE:
			{
				this->processRtnQuote(&task);
				break;
			}


			};
		}
	}
	catch (const TerminatedError&)
	{
	}
};

void MdApi::processRspLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIQuotLoginRspInfo *task_data = (TapAPIQuotLoginRspInfo*)task->task_data;
		data["UserNo"] = toUtf(task_data->UserNo);
		data["UserType"] = task_data->UserType;
		data["UserName"] = toUtf(task_data->UserName);
		data["QuoteTempPassword"] = toUtf(task_data->QuoteTempPassword);
		data["ReservedInfo"] = toUtf(task_data->ReservedInfo);
		data["LastLoginIP"] = toUtf(task_data->LastLoginIP);
		data["LastLoginProt"] = task_data->LastLoginProt;
		data["LastLoginTime"] = toUtf(task_data->LastLoginTime);
		data["LastLogoutTime"] = toUtf(task_data->LastLogoutTime);
		data["TradeDate"] = toUtf(task_data->TradeDate);
		data["LastSettleTime"] = toUtf(task_data->LastSettleTime);
		data["StartTime"] = toUtf(task_data->StartTime);
		data["InitTime"] = toUtf(task_data->InitTime);
		delete task_data;
	}
	this->onRspLogin(task->task_int, data);
};

void MdApi::processAPIReady(Task *task)
{
	this->onAPIReady();
};

void MdApi::processDisconnect(Task *task)
{
	gil_scoped_acquire acquire;
	this->onDisconnect(task->task_int);
};

void MdApi::processRspQryCommodity(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIQuoteCommodityInfo *task_data = (TapAPIQuoteCommodityInfo*)task->task_data;
		data["Commodity"] = task_data->Commodity;
		data["CommodityName"] = toUtf(task_data->CommodityName);
		data["CommodityEngName"] = toUtf(task_data->CommodityEngName);
		data["ContractSize"] = task_data->ContractSize;
		data["CommodityTickSize"] = task_data->CommodityTickSize;
		data["CommodityDenominator"] = task_data->CommodityDenominator;
		data["CmbDirect"] = task_data->CmbDirect;
		data["CommodityContractLen"] = task_data->CommodityContractLen;
		data["IsDST"] = task_data->IsDST;
		data["RelateCommodity1"] = task_data->RelateCommodity1;
		data["RelateCommodity2"] = task_data->RelateCommodity2;
		delete task_data;
	}
	this->onRspQryCommodity(task->task_id, task->task_int, task->task_last, data);
};

void MdApi::processRspQryContract(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIQuoteContractInfo *task_data = (TapAPIQuoteContractInfo*)task->task_data;
		data["Contract"] = task_data->Contract;
		data["ContractType"] = task_data->ContractType;
		data["QuoteUnderlyingContract"] = toUtf(task_data->QuoteUnderlyingContract);
		data["ContractName"] = toUtf(task_data->ContractName);
		data["ContractExpDate"] = toUtf(task_data->ContractExpDate);
		data["LastTradeDate"] = toUtf(task_data->LastTradeDate);
		data["FirstNoticeDate"] = toUtf(task_data->FirstNoticeDate);
		delete task_data;
	}
	this->onRspQryContract(task->task_id, task->task_int, task->task_last, data);
};

void MdApi::processRspSubscribeQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIQuoteWhole *task_data = (TapAPIQuoteWhole*)task->task_data;
		data["Contract"] = task_data->Contract;
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["TradingState"] = task_data->TradingState;
		data["DateTimeStamp"] = toUtf(task_data->DateTimeStamp);
		data["QPreClosingPrice"] = task_data->QPreClosingPrice;
		data["QPreSettlePrice"] = task_data->QPreSettlePrice;
		data["QPrePositionQty"] = task_data->QPrePositionQty;
		data["QOpeningPrice"] = task_data->QOpeningPrice;
		data["QLastPrice"] = task_data->QLastPrice;
		data["QHighPrice"] = task_data->QHighPrice;
		data["QLowPrice"] = task_data->QLowPrice;
		data["QHisHighPrice"] = task_data->QHisHighPrice;
		data["QHisLowPrice"] = task_data->QHisLowPrice;
		data["QLimitUpPrice"] = task_data->QLimitUpPrice;
		data["QLimitDownPrice"] = task_data->QLimitDownPrice;
		data["QTotalQty"] = task_data->QTotalQty;
		data["QTotalTurnover"] = task_data->QTotalTurnover;
		data["QPositionQty"] = task_data->QPositionQty;
		data["QAveragePrice"] = task_data->QAveragePrice;
		data["QClosingPrice"] = task_data->QClosingPrice;
		data["QSettlePrice"] = task_data->QSettlePrice;
		data["QLastQty"] = task_data->QLastQty;
		data["QBidPrice"] = task_data->QBidPrice;
		data["QBidQty"] = task_data->QBidQty;
		data["QAskPrice"] = task_data->QAskPrice;
		data["QAskQty"] = task_data->QAskQty;
		data["QImpliedBidPrice"] = task_data->QImpliedBidPrice;
		data["QImpliedBidQty"] = task_data->QImpliedBidQty;
		data["QImpliedAskPrice"] = task_data->QImpliedAskPrice;
		data["QImpliedAskQty"] = task_data->QImpliedAskQty;
		data["QPreDelta"] = task_data->QPreDelta;
		data["QCurrDelta"] = task_data->QCurrDelta;
		data["QInsideQty"] = task_data->QInsideQty;
		data["QOutsideQty"] = task_data->QOutsideQty;
		data["QTurnoverRate"] = task_data->QTurnoverRate;
		data["Q5DAvgQty"] = task_data->Q5DAvgQty;
		data["QPERatio"] = task_data->QPERatio;
		data["QTotalValue"] = task_data->QTotalValue;
		data["QNegotiableValue"] = task_data->QNegotiableValue;
		data["QPositionTrend"] = task_data->QPositionTrend;
		data["QChangeSpeed"] = task_data->QChangeSpeed;
		data["QChangeRate"] = task_data->QChangeRate;
		data["QChangeValue"] = task_data->QChangeValue;
		data["QSwing"] = task_data->QSwing;
		data["QTotalBidQty"] = task_data->QTotalBidQty;
		data["QTotalAskQty"] = task_data->QTotalAskQty;
		data["UnderlyContract"] = task_data->UnderlyContract;
		delete task_data;
	}
	this->onRspSubscribeQuote(task->task_id, task->task_int, task->task_last, data);
};

void MdApi::processRspUnSubscribeQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIContract *task_data = (TapAPIContract*)task->task_data;
		data["Commodity"] = task_data->Commodity;
		data["ContractNo1"] = toUtf(task_data->ContractNo1);
		data["StrikePrice1"] = toUtf(task_data->StrikePrice1);
		data["CallOrPutFlag1"] = task_data->CallOrPutFlag1;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		delete task_data;
	}
	this->onRspUnSubscribeQuote(task->task_id, task->task_int, task->task_last, data);
};

void MdApi::processRtnQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIQuoteWhole *task_data = (TapAPIQuoteWhole*)task->task_data;
		data["Contract"] = task_data->Contract;
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["TradingState"] = task_data->TradingState;
		data["DateTimeStamp"] = toUtf(task_data->DateTimeStamp);
		data["QPreClosingPrice"] = task_data->QPreClosingPrice;
		data["QPreSettlePrice"] = task_data->QPreSettlePrice;
		data["QPrePositionQty"] = task_data->QPrePositionQty;
		data["QOpeningPrice"] = task_data->QOpeningPrice;
		data["QLastPrice"] = task_data->QLastPrice;
		data["QHighPrice"] = task_data->QHighPrice;
		data["QLowPrice"] = task_data->QLowPrice;
		data["QHisHighPrice"] = task_data->QHisHighPrice;
		data["QHisLowPrice"] = task_data->QHisLowPrice;
		data["QLimitUpPrice"] = task_data->QLimitUpPrice;
		data["QLimitDownPrice"] = task_data->QLimitDownPrice;
		data["QTotalQty"] = task_data->QTotalQty;
		data["QTotalTurnover"] = task_data->QTotalTurnover;
		data["QPositionQty"] = task_data->QPositionQty;
		data["QAveragePrice"] = task_data->QAveragePrice;
		data["QClosingPrice"] = task_data->QClosingPrice;
		data["QSettlePrice"] = task_data->QSettlePrice;
		data["QLastQty"] = task_data->QLastQty;
		data["QBidPrice"] = task_data->QBidPrice;
		data["QBidQty"] = task_data->QBidQty;
		data["QAskPrice"] = task_data->QAskPrice;
		data["QAskQty"] = task_data->QAskQty;
		data["QImpliedBidPrice"] = task_data->QImpliedBidPrice;
		data["QImpliedBidQty"] = task_data->QImpliedBidQty;
		data["QImpliedAskPrice"] = task_data->QImpliedAskPrice;
		data["QImpliedAskQty"] = task_data->QImpliedAskQty;
		data["QPreDelta"] = task_data->QPreDelta;
		data["QCurrDelta"] = task_data->QCurrDelta;
		data["QInsideQty"] = task_data->QInsideQty;
		data["QOutsideQty"] = task_data->QOutsideQty;
		data["QTurnoverRate"] = task_data->QTurnoverRate;
		data["Q5DAvgQty"] = task_data->Q5DAvgQty;
		data["QPERatio"] = task_data->QPERatio;
		data["QTotalValue"] = task_data->QTotalValue;
		data["QNegotiableValue"] = task_data->QNegotiableValue;
		data["QPositionTrend"] = task_data->QPositionTrend;
		data["QChangeSpeed"] = task_data->QChangeSpeed;
		data["QChangeRate"] = task_data->QChangeRate;
		data["QChangeValue"] = task_data->QChangeValue;
		data["QSwing"] = task_data->QSwing;
		data["QTotalBidQty"] = task_data->QTotalBidQty;
		data["QTotalAskQty"] = task_data->QTotalAskQty;
		data["UnderlyContract"] = task_data->UnderlyContract;
		delete task_data;
	}
	this->onRtnQuote(data);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::createTapQuoteAPI(const dict &req, int &iResult)
{
	TapAPIApplicationInfo myreq = TapAPIApplicationInfo();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AuthCode", myreq.AuthCode);
	getString(req, "KeyOperationLogPath", myreq.KeyOperationLogPath);
	this->api->CreateTapQuoteAPI(&myreq, iResult);
};

void MdApi::release()
{
	this->api->FreeTapQuoteAPI(NULL);
};

void MdApi::init()
{
	this->active = true;
	this->task_thread = thread(&MdApi::processTask, this);
};


void MdApi::exit()
{
	this->active = false;
	this->task_queue.terminate();
	this->task_thread.join();
};


int MdApi::qryCommodity(unsigned int *session)
{
	int i = this->api->QryCommodity(session);
	return i;
};

int MdApi::qryContract(unsigned int *session, const dict &req)
{
	TapAPICommodity myreq = TapAPICommodity();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getChar(req, "CommodityType", &myreq.CommodityType);
	getString(req, "CommodityNo", myreq.CommodityNo);
	int i = this->api->QryContract(session, &myreq);
	return i;
};

///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyMdApi : public MdApi
{
public:
	using MdApi::MdApi;

	void onRspLogin(int error, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspLogin, error, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onAPIReady() override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onAPIReady);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onDisconnect(int reasonCode) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onDisconnect, reasonCode);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryCommodity(int session, int error, bool last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspQryCommodity, session, error, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryContract(int session, int error, bool last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspQryContract, session, error, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspSubscribeQuote(int session, int error, bool last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspSubscribeQuote, session, error, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspUnSubscribeQuote(int session, int error, bool last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRspUnSubscribeQuote, session, error, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnQuote(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onRtnQuote, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
};


PYBIND11_MODULE(vntapmd, m)
{
	class_<MdApi, PyMdApi> mdapi(m, "MdApi", module_local());
	mdapi
		.def(init<>())
		.def("createTapQuoteAPI", &MdApi::createTapQuoteAPI)
		.def("release", &MdApi::release)
		.def("setAPINotify", &MdApi::setAPINotify)
		.def("init", &MdApi::init)
		.def("exit", &MdApi::exit)
		.def("setHostAddress", &MdApi::setHostAddress)
		.def("login", &MdApi::login)
		.def("disconnect", &MdApi::disconnect)
		.def("subscribeQuote", &MdApi::subscribeQuote)
		.def("subscribeQuote", &MdApi::subscribeQuote)

		.def("qryCommodity", &MdApi::qryCommodity)
		.def("qryContract", &MdApi::qryContract)

		.def("onRspLogin", &MdApi::onRspLogin)
		.def("onAPIReady", &MdApi::onAPIReady)
		.def("onDisconnect", &MdApi::onDisconnect)
		.def("onRspQryCommodity", &MdApi::onRspQryCommodity)
		.def("onRspQryContract", &MdApi::onRspQryContract)
		.def("onRspSubscribeQuote", &MdApi::onRspSubscribeQuote)
		.def("onRspUnSubscribeQuote", &MdApi::onRspUnSubscribeQuote)
		.def("onRtnQuote", &MdApi::onRtnQuote)
		;

}

