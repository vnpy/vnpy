#include "vnestd.h"

// test

//用户名密码
#define DEFAULT_USERNAME	("Q497525430")
#define DEFAULT_PASSWORD	("797878")

//下单
#define DEFAULT_ACCOUNT_NO		(DEFAULT_USERNAME)
#define DEFAULT_EXCHANGE_NO		("SHFE")
#define DEFAULT_COMMODITY_TYPE	(TAPI_COMMODITY_TYPE_FUTURES)
#define DEFAULT_COMMODITY_NO	("AG")
#define DEFAULT_CONTRACT_NO		("2012")
#define DEFAULT_ORDER_TYPE		(TAPI_ORDER_TYPE_MARKET)
#define DEFAULT_ORDER_SIDE		(TAPI_SIDE_BUY)
#define DEFAULT_ORDER_PRICE		(0)
#define DEFAULT_ORDER_QTY		(1)	

///-------------------------------------------------------------------------------------------
///C++的回调函数将数据保存队列中
///-------------------------------------------------------------------------------------------


void TdApi::OnConnect(const TAPISTR_20 UserNo) 
{
	Task task = Task();
	task.task_name = ONCONNECT;
	task.task_string = UserNo;
	this->task_queue.push(task);
};

void TdApi::OnRspLogin(const TAPISTR_20 UserNo, TAPIINT32 nErrorCode, const TapAPITradeLoginRspInfo *pLoginRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPLOGIN;

	task.task_string = UserNo;
	task.task_int = nErrorCode;
	if (pLoginRspInfo)
	{
		TapAPITradeLoginRspInfo *task_data = new TapAPITradeLoginRspInfo();
		*task_data = *pLoginRspInfo;
		task.task_data = task_data;
	}

	this->task_queue.push(task);

};

void TdApi::OnRtnContactInfo(const TAPISTR_20 UserNo, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPISecondInfo* pInfo)
{
};

void TdApi::OnRspRequestVertificateCode(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIVertificateCode *pInfo)
{
};

void TdApi::OnRtnErrorMsg(const TAPISTR_20 UserNo, const TAPISTR_500 ErrorMsg)
{
	Task task = Task();
	task.task_name = ONRTNERRORMSG;
	task.task_string = UserNo;
	task.task_string = ErrorMsg;
	this->task_queue.push(task);
};

void TdApi::OnAPIReady(const TAPISTR_20 UserNo)
{
	Task task = Task();
	task.task_name = ONAPIREADY;

	task.task_string = UserNo;
	this->task_queue.push(task);
};

void TdApi::OnDisconnect(const TAPISTR_20 UserNo, TAPIINT32 nReasonCode)
{
	Task task = Task();
	task.task_name = ONDISCONNECT;
	task.task_string = UserNo;
	task.task_int = nReasonCode;
	this->task_queue.push(task);
};


void TdApi::OnRspSubmitUserLoginInfo(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, const TapAPISubmitUserLoginInfoRsp *pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPSUBMITUSERLOGININFO;
	task.task_string = UserNo;
	task.task_id = nSessionID;
	if (pRspInfo)
	{
		TapAPISubmitUserLoginInfoRsp *task_data = new TapAPISubmitUserLoginInfoRsp();
		*task_data = *pRspInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};


void TdApi::OnRspChangePassword(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, TAPIINT32 nErrorCode)
{
	Task task = Task();
	task.task_name = ONRSPCHANGEPASSWORD;
	task.task_string = UserNo;
	task.task_id = nSessionID;
	task.task_int = nErrorCode;
	this->task_queue.push(task);
};
void TdApi::OnRspSetReservedInfo(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, TAPIINT32 nErrorCode, const TAPISTR_50 info)
{
	Task task = Task();
	task.task_name = ONRSPSETRESERVEDINFO;
	task.task_string = UserNo;
	task.task_id = nSessionID;
	task.task_int = nErrorCode;
	task.task_string = info;
	this->task_queue.push(task);
};
void TdApi::OnRtnContract(const TAPISTR_20 UserNo, const TapAPITradeContractInfo *pRtnInfo) 
{
	Task task = Task();
	task.task_name = ONRTNCONTRACT;
	task.task_string = UserNo;
	if (pRtnInfo)
	{
		TapAPITradeContractInfo *task_data = new TapAPITradeContractInfo();
		*task_data = *pRtnInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};
void TdApi::OnRtnFund(const TAPISTR_20 UserNo, const TapAPIFundData *pRtnInfo) 
{
	Task task = Task();
	task.task_name = ONRTNFUND;
	task.task_string = UserNo;
	if (pRtnInfo)
	{
		TapAPIFundData *task_data = new TapAPIFundData();
		*task_data = *pRtnInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};
void TdApi::OnRtnOrder(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIOrderInfo *pRtnInfo) 
{
	Task task = Task();
	task.task_name = ONRTNORDER;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	if (pRtnInfo)
	{
		TapAPIOrderInfo *task_data = new TapAPIOrderInfo();
		*task_data = *pRtnInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};
void TdApi::OnRspQryOrderProcess(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *pRspInfo) 

{
	Task task = Task();
	task.task_name = ONRSPQRYORDERPROCESS;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pRspInfo)
	{
		TapAPIOrderInfo *task_data = new TapAPIOrderInfo();
		*task_data = *pRspInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};
void TdApi::OnRtnFill(const TAPISTR_20 UserNo, const TapAPIFillInfo *pRtnInfo)
{
	Task task = Task();
	task.task_name = ONRTNFILL;
	task.task_string = UserNo;
	if (pRtnInfo)
	{
		TapAPIFillInfo *task_data = new TapAPIFillInfo();
		*task_data = *pRtnInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};


void TdApi::OnRtnPosition(const TAPISTR_20 UserNo, const TapAPIPositionInfo *pRtnInfo) 
{
	Task task = Task();
	task.task_name = ONRTNPOSITION;
	task.task_string = UserNo;
	if (pRtnInfo)
	{
		TapAPIPositionInfo *task_data = new TapAPIPositionInfo();
		*task_data = *pRtnInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnClose(const TAPISTR_20 UserNo, const TapAPICloseInfo *pRtnInfo) 
{
	Task task = Task();
	task.task_name = ONRTNCLOSE;
	task.task_string = UserNo;
	if (pRtnInfo)
	{
		TapAPICloseInfo *task_data = new TapAPICloseInfo();
		*task_data = *pRtnInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);

};
//python test会退出
void TdApi::OnRtnPositionProfit(const TAPISTR_20 UserNo, const TapAPIPositionProfitNotice *pRtnInfo) 
{
	//Task task = Task();
	//task.task_name = ONRTNPOSITIONPROFIT;
	//task.task_string = UserNo;
	//if (pRtnInfo)
	//{
	//	TapAPIPositionProfitNotice *task_data = new TapAPIPositionProfitNotice();
	//	*task_data = *pRtnInfo;
	//	task.task_data = task_data;
	//}
	//this->task_queue.push(task);
};

void TdApi::OnRspQryDeepQuote(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIDeepQuoteQryRsp *pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPQRYDEEPQUOTE;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pRspInfo)
	{
		TapAPIDeepQuoteQryRsp *task_data = new TapAPIDeepQuoteQryRsp();
		*task_data = *pRspInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

//python test会退出
void TdApi::OnRtnExchangeStateInfo(const TAPISTR_20 UserNo, const TapAPIExchangeStateInfoNotice *pRtnInfo) 
{
	//Task task = Task();
	//task.task_name = ONRTNEXCHANGESTATEINFO;
	//task.task_string = UserNo;
	//if (pRtnInfo)
	//{
	//	TapAPIExchangeStateInfoNotice *task_data = new TapAPIExchangeStateInfoNotice();
	//	*task_data = *pRtnInfo;
	//	task.task_data = task_data;
	//}
	//this->task_queue.push(task);
};

void TdApi::OnRtnReqQuoteNotice(const TAPISTR_20 UserNo, const TapAPIReqQuoteNotice *pRtnInfo) 
{
	Task task = Task();
	task.task_name = ONRTNREQQUOTENOTICE;
	task.task_string = UserNo;
	if (pRtnInfo)
	{
		TapAPIReqQuoteNotice *task_data = new TapAPIReqQuoteNotice();
		*task_data = *pRtnInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};
void TdApi::OnRspAccountRentInfo(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIAccountRentInfo *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPACCOUNTRENTINFO;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pRspInfo)
	{
		TapAPIAccountRentInfo *task_data = new TapAPIAccountRentInfo();
		*task_data = *pRspInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};
void TdApi::OnRspTradeMessage(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPITradeMessage *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPTRADEMESSAGE;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pRspInfo)
	{
		TapAPITradeMessage *task_data = new TapAPITradeMessage();
		*task_data = *pRspInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};
void TdApi::OnRtnTradeMessage(const TAPISTR_20 UserNo, const TapAPITradeMessage *pRtnInfo) 
{
	Task task = Task();
	task.task_name = ONRTNTRADEMESSAGE;
	task.task_string = UserNo;
	if (pRtnInfo)
	{
		TapAPITradeMessage *task_data = new TapAPITradeMessage();
		*task_data = *pRtnInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

//北斗星专用
void TdApi::OnRspQryHisOrder(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisOrderQryRsp *pInfo) {};
void TdApi::OnRspQryHisOrderProcess(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisOrderProcessQryRsp *pInfo) {};
void TdApi::OnRspQryHisFill(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisFillQryRsp *pInfo) {};
void TdApi::OnRspQryHisPosition(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisPositionQryRsp *pInfo) {};
void TdApi::OnRspQryHisDelivery(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisDeliveryQryRsp *pInfo) {};
void TdApi::OnRspQryAccountCashAdjust(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIAccountCashAdjustQryRsp *pInfo) {};
void TdApi::OnRspQryBill(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIBillQryRsp *pInfo) {};
void TdApi::OnRspAccountFeeRent(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIAccountFeeRentQryRsp *pInfo) {};
void TdApi::OnRspAccountMarginRent(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIAccountMarginRentQryRsp *pInfo) {};
void TdApi::OnRspAddMobileDevice(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIMobileDeviceAddRsp *pInfo) {};
void TdApi::OnRspQryManageInfoForEStar(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIManageInfo *pInfo) {};
void TdApi::OnRspQrySystemParameter(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPISystemParameterInfo *pInfo) {};
void TdApi::OnRspQryTradeCenterFrontAddress(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPITradeCenterFrontAddressInfo *pInfo) {};
void TdApi::OnRtnCommodityInfo(const TAPISTR_20 UserNo, const TapAPICommodityInfo *pInfo) {};
void TdApi::OnRtnCurrencyInfo(const TAPISTR_20 UserNo, const TapAPICurrencyInfo *pInfo) {};




///-------------------------------------------------------------------------------------------
///工作线程从队列中取出数据,转化为python对象后,进行推送
///-------------------------------------------------------------------------------------------

void TdApi::processTask()
{
	try
	{
		while (this->active)
		{
			Task task = this->task_queue.pop();
			switch (task.task_name)
			{
			case ONCONNECT:
			{
				this->processConnect(&task);
				break;
			}

			case ONRSPLOGIN:
			{
				this->processRspLogin(&task);
				break;
			}
			
			case ONRTNCONTACTINFO:      //北斗星专用
			{
				this->processRtnContactInfo(&task);
				break;
			}

			case ONRSPREQUESTVERTIFICATECODE:    //北斗星专用
			{
				this->processRspRequestVertificateCode(&task);
				break;
			}
			
			case ONRTNERRORMSG:
			{
				this->processRtnErrorMsg(&task);
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
			
			case ONRSPSUBMITUSERLOGININFO:
			{
				this->processRspSubmitUserLoginInfo(&task);
				break;
			}
			
			case ONRSPCHANGEPASSWORD:
			{
				this->processRspChangePassword(&task);
				break;
			}

			case ONRSPSETRESERVEDINFO:
			{
				this->processRspSetReservedInfo(&task);
				break;
			}

			case ONRTNCONTRACT:
			{
				this->processRtnContract(&task);
				break;
			}

			case ONRTNFUND:
			{
				this->processRtnFund(&task);
				break;
			}

			case ONRTNORDER:
			{
				this->processRtnOrder(&task);
				break;
			}
			
			case ONRSPQRYORDERPROCESS:
			{
				this->processRspQryOrderProcess(&task);
				break;
			}
			
			case ONRTNFILL:
			{
				this->processRtnFill(&task);
				break;
			}

			case ONRTNPOSITION:
			{
				this->processRtnPosition(&task);
				break;
			}

			case ONRTNCLOSE:
			{
				this->processRtnClose(&task);
				break;
			}

			case ONRTNPOSITIONPROFIT:
			{
				this->processRtnPositionProfit(&task);
				break;
			}
			
			case ONRSPQRYDEEPQUOTE:
			{
				this->processRspQryDeepQuote(&task);
				break;
			}
			
			case ONRTNEXCHANGESTATEINFO:
			{
				this->processRtnExchangeStateInfo(&task);
				break;
			}
			
			case ONRTNREQQUOTENOTICE:
			{
				this->processRtnReqQuoteNotice(&task);
				break;
			}

			case ONRSPACCOUNTRENTINFO:
			{
				this->processRspAccountRentInfo(&task);
				break;
			}

			case ONRSPTRADEMESSAGE:
			{
				this->processRspTradeMessage(&task);
				break;
			}

			case ONRTNTRADEMESSAGE:
			{
				this->processRtnTradeMessage(&task);
				break;
			}

			case ONRSPQRYHISORDER:
			{
				this->processRspQryHisOrder(&task);
				break;
			}

			case ONRSPQRYHISORDERPROCESS:
			{
				this->processRspQryHisOrderProcess(&task);
				break;
			}

			case ONRSPQRYHISFILL:
			{
				this->processRspQryHisFill(&task);
				break;
			}

			case ONRSPQRYHISPOSITION:
			{
				this->processRspQryHisPosition(&task);
				break;
			}

			case ONRSPQRYHISDELIVERY:
			{
				this->processRspQryHisDelivery(&task);
				break;
			}

			case ONRSPQRYACCOUNTCASHADJUST:
			{
				this->processRspQryAccountCashAdjust(&task);
				break;
			}

			case ONRSPQRYBILL:
			{
				this->processRspQryBill(&task);
				break;
			}

			case ONRSPACCOUNTFEERENT:
			{
				this->processRspAccountFeeRent(&task);
				break;
			}

			case ONRSPACCOUNTMARGINRENT:
			{
				this->processRspAccountMarginRent(&task);
				break;
			}

			case ONRSPADDMOBILEDEVICE:
			{
				this->processRspAddMobileDevice(&task);
				break;
			}

			case ONRSPQRYMANAGEINFOFORESTAR:
			{
				this->processRspQryManageInfoForEStar(&task);
				break;
			}

			case ONRSPQRYSYSTEMPARAMETER:
			{
				this->processRspQrySystemParameter(&task);
				break;
			}

			case ONRSPQRYTRADECENTERFRONTADDRESS:
			{
				this->processRspQryTradeCenterFrontAddress(&task);
				break;
			}

			case ONRTNCOMMODITYINFO:
			{
				this->processRtnCommodityInfo(&task);
				break;
			}

			case ONRTNCURRENCYINFO:
			{
				this->processRtnCurrencyInfo(&task);
				break;
			}
			



			};
		}
	}
	catch (const TerminatedError&)
	{
	}
};

void TdApi::processConnect(Task *task)
{
	gil_scoped_acquire acquire;
	this->onConnect(task->task_string);
};

void TdApi::processRspLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPITradeLoginRspInfo *task_data = (TapAPITradeLoginRspInfo*)task->task_data;
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
		data["AuthType"] = task_data->AuthType;
		data["AuthDate"] = toUtf(task_data->AuthDate);
		delete task_data;
	}
	this->onRspLogin(task->task_string, task->task_int, data);
};

void TdApi::processRtnContactInfo(Task *task)     //(北斗星专用)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPISecondInfo *task_data = (TapAPISecondInfo*)task->task_data;
		data["SendType"] = task_data->SendType;
		data["SendAccount"] = toUtf(task_data->SendAccount);
		delete task_data;
	}
	this->onRtnContactInfo(task->task_string, task->task_int, task->task_last, data);
};

void TdApi::processRspRequestVertificateCode(Task *task)   //(北斗星专用)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIVertificateCode *task_data = (TapAPIVertificateCode*)task->task_data;
		data["SecondSerialID"] = toUtf(task_data->SecondSerialID);
		data["Effective"] = task_data->Effective;
		delete task_data;
	}
	this->onRspRequestVertificateCode(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRtnErrorMsg(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRtnErrorMsg(task->task_string, task->task_strextra);
};

void TdApi::processAPIReady(Task *task)
{
	gil_scoped_acquire acquire;
	this->onAPIReady(task->task_string);
};

void TdApi::processDisconnect(Task *task)
{
	gil_scoped_acquire acquire;
	this->onDisconnect(task->task_string, task->task_int);
};

void TdApi::processRspSubmitUserLoginInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPISubmitUserLoginInfoRsp *task_data = (TapAPISubmitUserLoginInfoRsp*)task->task_data;
		data["UserNo"] = toUtf(task_data->UserNo);
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		delete task_data;
	}
	this->onRspSubmitUserLoginInfo(task->task_string, task->task_id, data);
};

void TdApi::processRspChangePassword(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspChangePassword(task->task_string, task->task_id, task->task_int);
};

void TdApi::processRspSetReservedInfo(Task *task)
{
	gil_scoped_acquire acquire;
	this->onRspSetReservedInfo(task->task_string, task->task_id, task->task_int, task->task_string);
};

void TdApi::processRtnContract(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPITradeContractInfo *task_data = (TapAPITradeContractInfo*)task->task_data;
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo1"] = toUtf(task_data->ContractNo1);
		data["StrikePrice1"] = toUtf(task_data->StrikePrice1);
		data["CallOrPutFlag1"] = task_data->CallOrPutFlag1;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		data["ContractName"] = toUtf(task_data->ContractName);
		data["ContractExpDate"] = toUtf(task_data->ContractExpDate);
		data["LastTradeDate"] = toUtf(task_data->LastTradeDate);
		data["FirstNoticeDate"] = toUtf(task_data->FirstNoticeDate);
		data["FutureContractNo"] = toUtf(task_data->FutureContractNo);
		delete task_data;
	}
	this->onRtnContract(task->task_string, data);
};

void TdApi::processRtnFund(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIFundData *task_data = (TapAPIFundData*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["CurrencyGroupNo"] = toUtf(task_data->CurrencyGroupNo);
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["TradeRate"] = task_data->TradeRate;
		data["FutureAlg"] = task_data->FutureAlg;
		data["OptionAlg"] = task_data->OptionAlg;
		data["PreBalance"] = task_data->PreBalance;
		data["PreUnExpProfit"] = task_data->PreUnExpProfit;
		data["PreLMEPositionProfit"] = task_data->PreLMEPositionProfit;
		data["PreEquity"] = task_data->PreEquity;
		data["PreAvailable1"] = task_data->PreAvailable1;
		data["PreMarketEquity"] = task_data->PreMarketEquity;
		data["CashInValue"] = task_data->CashInValue;
		data["CashOutValue"] = task_data->CashOutValue;
		data["CashAdjustValue"] = task_data->CashAdjustValue;
		data["CashPledged"] = task_data->CashPledged;
		data["FrozenFee"] = task_data->FrozenFee;
		data["FrozenDeposit"] = task_data->FrozenDeposit;
		data["AccountFee"] = task_data->AccountFee;
		data["ExchangeFee"] = task_data->ExchangeFee;
		data["AccountDeliveryFee"] = task_data->AccountDeliveryFee;
		data["PremiumIncome"] = task_data->PremiumIncome;
		data["PremiumPay"] = task_data->PremiumPay;
		data["CloseProfit"] = task_data->CloseProfit;
		data["DeliveryProfit"] = task_data->DeliveryProfit;
		data["UnExpProfit"] = task_data->UnExpProfit;
		data["ExpProfit"] = task_data->ExpProfit;
		data["PositionProfit"] = task_data->PositionProfit;
		data["LmePositionProfit"] = task_data->LmePositionProfit;
		data["OptionMarketValue"] = task_data->OptionMarketValue;
		data["AccountInitialMargin"] = task_data->AccountInitialMargin;
		data["AccountMaintenanceMargin"] = task_data->AccountMaintenanceMargin;
		data["UpperInitialMargin"] = task_data->UpperInitialMargin;
		data["UpperMaintenanceMargin"] = task_data->UpperMaintenanceMargin;
		data["Discount"] = task_data->Discount;
		data["Balance"] = task_data->Balance;
		data["Equity"] = task_data->Equity;
		data["Available"] = task_data->Available;
		data["CanDraw"] = task_data->CanDraw;
		data["MarketEquity"] = task_data->MarketEquity;
		data["AuthMoney"] = task_data->AuthMoney;
		data["OriginalCashInOut"] = task_data->OriginalCashInOut;
		data["FloatingPL"] = task_data->FloatingPL;
		data["FrozenRiskFundValue"] = task_data->FrozenRiskFundValue;
		data["ClosePL"] = task_data->ClosePL;
		data["NoCurrencyPledgeValue"] = task_data->NoCurrencyPledgeValue;
		data["PrePledgeValue"] = task_data->PrePledgeValue;
		data["PledgeIn"] = task_data->PledgeIn;
		data["PledgeOut"] = task_data->PledgeOut;
		data["PledgeValue"] = task_data->PledgeValue;
		data["BorrowValue"] = task_data->BorrowValue;
		data["SpecialAccountFrozenMargin"] = task_data->SpecialAccountFrozenMargin;
		data["SpecialAccountMargin"] = task_data->SpecialAccountMargin;
		data["SpecialAccountFrozenFee"] = task_data->SpecialAccountFrozenFee;
		data["SpecialAccountFee"] = task_data->SpecialAccountFee;
		data["SpecialFloatProfit"] = task_data->SpecialFloatProfit;
		data["SpecialCloseProfit"] = task_data->SpecialCloseProfit;
		data["SpecialFloatPL"] = task_data->SpecialFloatPL;
		data["SpecialClosePL"] = task_data->SpecialClosePL;
		data["RiskRate"] = task_data->RiskRate;
		delete task_data;
	}
	this->onRtnFund(task->task_string, data);
};

void TdApi::processRtnOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIOrderInfo *task_data = (TapAPIOrderInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		data["OrderType"] = task_data->OrderType;
		data["OrderSource"] = task_data->OrderSource;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["IsRiskOrder"] = task_data->IsRiskOrder;
		data["OrderSide"] = task_data->OrderSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["PositionEffect2"] = task_data->PositionEffect2;
		data["InquiryNo"] = toUtf(task_data->InquiryNo);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["HedgeFlag2"] = task_data->HedgeFlag2;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderPrice2"] = task_data->OrderPrice2;
		data["StopPrice"] = task_data->StopPrice;
		data["OrderQty"] = task_data->OrderQty;
		data["OrderQty2"] = task_data->OrderQty2;
		data["OrderMinQty"] = task_data->OrderMinQty;
		data["MinClipSize"] = task_data->MinClipSize;
		data["MaxClipSize"] = task_data->MaxClipSize;
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["TacticsType"] = task_data->TacticsType;
		data["TriggerCondition"] = task_data->TriggerCondition;
		data["TriggerPriceType"] = task_data->TriggerPriceType;
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["MarketLevel"] = task_data->MarketLevel;
		data["FutureAutoCloseFlag"] = task_data->FutureAutoCloseFlag;
		data["OrderCanceledQty"] = task_data->OrderCanceledQty;
		data["LicenseNo"] = toUtf(task_data->LicenseNo);
		data["ParentAccountNo"] = toUtf(task_data->ParentAccountNo);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["ClientOrderNo"] = toUtf(task_data->ClientOrderNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["OrderExchangeSystemNo"] = toUtf(task_data->OrderExchangeSystemNo);

		data["TradeNo"] = toUtf(task_data->TradeNo);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["UpperSettleNo"] = toUtf(task_data->UpperSettleNo);
		data["UpperUserNo"] = toUtf(task_data->UpperUserNo);
		data["OrderInsertUserNo"] = toUtf(task_data->OrderInsertUserNo);
		data["OrderInsertTime"] = toUtf(task_data->OrderInsertTime);
		data["OrderCommandUserNo"] = toUtf(task_data->OrderCommandUserNo);
		data["OrderUpdateUserNo"] = toUtf(task_data->OrderUpdateUserNo);
		data["OrderUpdateTime"] = toUtf(task_data->OrderUpdateTime);
		data["OrderState"] = task_data->OrderState;
		data["OrderMatchPrice"] = task_data->OrderMatchPrice;
		data["OrderMatchPrice2"] = task_data->OrderMatchPrice2;
		data["OrderMatchQty"] = task_data->OrderMatchQty;
		data["OrderMatchQty2"] = task_data->OrderMatchQty2;
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		data["OrderStreamID"] = task_data->OrderStreamID;

		data["FeeValue"] = task_data->FeeValue;
		data["MarginValue"] = task_data->MarginValue;
		data["OrderDeleteByDisConnFlag"] = task_data->OrderDeleteByDisConnFlag;
		delete task_data;
	}
	this->onRtnOrder(task->task_string, task->task_id, data);
};

void TdApi::processRspQryOrderProcess(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIOrderInfo *task_data = (TapAPIOrderInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		data["OrderType"] = task_data->OrderType;
		data["OrderSource"] = task_data->OrderSource;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["IsRiskOrder"] = task_data->IsRiskOrder;
		data["OrderSide"] = task_data->OrderSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["PositionEffect2"] = task_data->PositionEffect2;
		data["InquiryNo"] = toUtf(task_data->InquiryNo);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["HedgeFlag2"] = task_data->HedgeFlag2;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderPrice2"] = task_data->OrderPrice2;
		data["StopPrice"] = task_data->StopPrice;
		data["OrderQty"] = task_data->OrderQty;
		data["OrderQty2"] = task_data->OrderQty2;
		data["OrderMinQty"] = task_data->OrderMinQty;
		data["MinClipSize"] = task_data->MinClipSize;
		data["MaxClipSize"] = task_data->MaxClipSize;
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["TacticsType"] = task_data->TacticsType;
		data["TriggerCondition"] = task_data->TriggerCondition;
		data["TriggerPriceType"] = task_data->TriggerPriceType;
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["MarketLevel"] = task_data->MarketLevel;
		data["FutureAutoCloseFlag"] = task_data->FutureAutoCloseFlag;
		data["OrderCanceledQty"] = task_data->OrderCanceledQty;
		data["LicenseNo"] = toUtf(task_data->LicenseNo);
		data["ParentAccountNo"] = toUtf(task_data->ParentAccountNo);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["ClientOrderNo"] = toUtf(task_data->ClientOrderNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["OrderExchangeSystemNo"] = toUtf(task_data->OrderExchangeSystemNo);
		//data["OrderParentNo"] = task_data->OrderParentNo;
		//data["OrderParentSystemNo"] = task_data->OrderParentSystemNo;
		data["TradeNo"] = toUtf(task_data->TradeNo);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["UpperSettleNo"] = toUtf(task_data->UpperSettleNo);
		data["UpperUserNo"] = toUtf(task_data->UpperUserNo);
		data["OrderInsertUserNo"] = toUtf(task_data->OrderInsertUserNo);
		data["OrderInsertTime"] = toUtf(task_data->OrderInsertTime);
		data["OrderCommandUserNo"] = toUtf(task_data->OrderCommandUserNo);
		data["OrderUpdateUserNo"] = toUtf(task_data->OrderUpdateUserNo);
		data["OrderUpdateTime"] = toUtf(task_data->OrderUpdateTime);
		data["OrderState"] = task_data->OrderState;
		data["OrderMatchPrice"] = task_data->OrderMatchPrice;
		data["OrderMatchPrice2"] = task_data->OrderMatchPrice2;
		data["OrderMatchQty"] = task_data->OrderMatchQty;
		data["OrderMatchQty2"] = task_data->OrderMatchQty2;
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		data["OrderStreamID"] = task_data->OrderStreamID;
		
		data["FeeValue"] = task_data->FeeValue;
		data["MarginValue"] = task_data->MarginValue;
		data["OrderDeleteByDisConnFlag"] = task_data->OrderDeleteByDisConnFlag;
		delete task_data;
	}
	this->onRspQryOrderProcess(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRtnFill(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIFillInfo *task_data = (TapAPIFillInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);

		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		//data["ExchangeNoRef"] = task_data->ExchangeNoRef;
		//data["CommodityTypeRef"] = task_data->CommodityTypeRef;
		//data["CommodityNoRef"] = task_data->CommodityNoRef;
		//data["ContractNoRef"] = task_data->ContractNoRef;
		//data["StrikePriceRef"] = task_data->StrikePriceRef;
		//data["CallOrPutFlagRef"] = task_data->CallOrPutFlagRef;
		//data["OrderExchangeNo"] = task_data->OrderExchangeNo;
		//data["OrderCommodityType"] = task_data->OrderCommodityType;
		//data["OrderCommodityNo"] = task_data->OrderCommodityNo;
		data["OrderType"] = task_data->OrderType;
		data["MatchSource"] = task_data->MatchSource;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["IsRiskOrder"] = task_data->IsRiskOrder;
		data["MatchSide"] = task_data->MatchSide;
		data["PositionEffect"] = task_data->PositionEffect;

		data["HedgeFlag"] = task_data->HedgeFlag;
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["ExchangeMatchNo"] = toUtf(task_data->ExchangeMatchNo);
		data["MatchDateTime"] = toUtf(task_data->MatchDateTime);
		data["UpperMatchDateTime"] = toUtf(task_data->UpperMatchDateTime);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["UpperSettleNo"] = toUtf(task_data->UpperSettleNo);
		data["UpperUserNo"] = toUtf(task_data->UpperUserNo);
		data["TradeNo"] = toUtf(task_data->TradeNo);
		data["MatchPrice"] = task_data->MatchPrice;
		data["MatchQty"] = task_data->MatchQty;
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		data["MatchStreamID"] = task_data->MatchStreamID;
		data["OpenCloseMode"] = task_data->OpenCloseMode;
		data["ContractSize"] = task_data->ContractSize;
		data["CommodityCurrencyGroup"] = toUtf(task_data->CommodityCurrencyGroup);
		data["CommodityCurrency"] = toUtf(task_data->CommodityCurrency);

		data["FeeCurrencyGroup"] = toUtf(task_data->FeeCurrencyGroup);
		data["FeeCurrency"] = toUtf(task_data->FeeCurrency);
		data["PreSettlePrice"] = task_data->PreSettlePrice;
		data["FeeValue"] = task_data->FeeValue;
		data["IsManualFee"] = task_data->IsManualFee;

		data["PremiumIncome"] = task_data->PremiumIncome;
		data["PremiumPay"] = task_data->PremiumPay;

		data["CloseProfit"] = task_data->CloseProfit;
		data["UnExpProfit"] = task_data->UnExpProfit;

		data["ClosePL"] = task_data->ClosePL;
		delete task_data;
	}
	this->onRtnFill(task->task_string, data);
};

void TdApi::processRtnPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIPositionInfo *task_data = (TapAPIPositionInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSide"] = task_data->MatchSide;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["PositionNo"] = toUtf(task_data->PositionNo);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["ExchangeMatchNo"] = toUtf(task_data->ExchangeMatchNo);
		data["MatchSource"] = task_data->MatchSource;
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperSettleNo"] = toUtf(task_data->UpperSettleNo);
		data["UpperUserNo"] = toUtf(task_data->UpperUserNo);
		data["TradeNo"] = toUtf(task_data->TradeNo);
		data["PositionPrice"] = task_data->PositionPrice;
		data["PositionQty"] = task_data->PositionQty;
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsAddOne"] = task_data->IsAddOne;
		data["MatchStreamID"] = task_data->MatchStreamID;
		data["PositionStreamId"] = task_data->PositionStreamId;
		data["ContractSize"] = task_data->ContractSize;
		data["CommodityCurrencyGroup"] = toUtf(task_data->CommodityCurrencyGroup);
		data["CommodityCurrency"] = toUtf(task_data->CommodityCurrency);
		data["PreSettlePrice"] = task_data->PreSettlePrice;
		data["Turnover"] = task_data->Turnover;
		data["AccountMarginMode"] = task_data->AccountMarginMode;
		data["AccountMarginParam"] = task_data->AccountMarginParam;

		data["AccountInitialMargin"] = task_data->AccountInitialMargin;
		data["AccountMaintenanceMargin"] = task_data->AccountMaintenanceMargin;
		data["PositionProfit"] = task_data->PositionProfit;
		data["LMEPositionProfit"] = task_data->LMEPositionProfit;
		data["OptionMarketValue"] = task_data->OptionMarketValue;
		data["MatchCmbNo"] = toUtf(task_data->MatchCmbNo);
		data["IsHistory"] = task_data->IsHistory;
		data["FloatingPL"] = task_data->FloatingPL;
		data["CalculatePrice"] = task_data->CalculatePrice;
		delete task_data;
	}
	this->onRtnPosition(task->task_string, data);
};

void TdApi::processRtnClose(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPICloseInfo *task_data = (TapAPICloseInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		//data["ParentAccountNo"] = task_data->ParentAccountNo;
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;

		data["OpenMatchSource"] = task_data->OpenMatchSource;
		data["CloseMatchSource"] = task_data->CloseMatchSource;
		data["CloseSide"] = task_data->CloseSide;
		data["CloseQty"] = task_data->CloseQty;
		data["OpenPrice"] = task_data->OpenPrice;
		data["ClosePrice"] = task_data->ClosePrice;
		data["OpenServerFlag"] = task_data->OpenServerFlag;
		data["OpenOrderNo"] = toUtf(task_data->OpenOrderNo);
		data["OpenMatchNo"] = toUtf(task_data->OpenMatchNo);
		data["OpenExchangeMatchNo"] = toUtf(task_data->OpenExchangeMatchNo);
		data["OpenMatchDateTime"] = toUtf(task_data->OpenMatchDateTime);
		data["CloseServerFlag"] = task_data->CloseServerFlag;
		data["CloseOrderNo"] = toUtf(task_data->CloseOrderNo);
		data["CloseMatchNo"] = toUtf(task_data->CloseMatchNo);
		data["CloseExchangeMatchNo"] = toUtf(task_data->CloseExchangeMatchNo);
		data["CloseMatchDateTime"] = toUtf(task_data->CloseMatchDateTime);
		data["CloseStreamId"] = task_data->CloseStreamId;

		data["ContractSize"] = task_data->ContractSize;

		data["PreSettlePrice"] = task_data->PreSettlePrice;
		data["CloseProfit"] = task_data->CloseProfit;
		data["UnExpProfit"] = task_data->UnExpProfit;
		data["ClosePL"] = task_data->ClosePL;
		delete task_data;
	}
	this->onRtnClose(task->task_string, data);
};

void TdApi::processRtnPositionProfit(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIPositionProfitNotice *task_data = (TapAPIPositionProfitNotice*)task->task_data;
		data["IsLast"] = task_data->IsLast;
		data["Data"] = task_data->Data;
		delete task_data;
	}
	this->onRtnPositionProfit(task->task_string, data);
};

void TdApi::processRspQryDeepQuote(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIDeepQuoteQryRsp *task_data = (TapAPIDeepQuoteQryRsp*)task->task_data;
		data["Contract"] = task_data->Contract;
		data["DeepQuote"] = task_data->DeepQuote;
		delete task_data;
	}
	this->onRspQryDeepQuote(task->task_string, task->task_id, task->task_int, task->task_last, data);
};


void TdApi::processRtnExchangeStateInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIExchangeStateInfoNotice *task_data = (TapAPIExchangeStateInfoNotice*)task->task_data;
		data["IsLast"] = task_data->IsLast;
		data["ExchangeStateInfo"] = task_data->ExchangeStateInfo;
		delete task_data;
	}
	this->onRtnExchangeStateInfo(task->task_string, data);
};


void TdApi::processRtnReqQuoteNotice(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIReqQuoteNotice *task_data = (TapAPIReqQuoteNotice*)task->task_data;
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["InquiryNo"] = toUtf(task_data->InquiryNo);
		data["UpdateTime"] = toUtf(task_data->UpdateTime);
		delete task_data;
	}
	this->onRtnReqQuoteNotice(task->task_string, data);
};

void TdApi::processRspAccountRentInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIAccountRentInfo *task_data = (TapAPIAccountRentInfo*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["MatchSource"] = task_data->MatchSource;
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["FeeMode"] = task_data->FeeMode;
		data["OpenTurnover"] = task_data->OpenTurnover;
		data["ClosedTurnover"] = task_data->ClosedTurnover;
		data["CloseNewTurnover"] = task_data->CloseNewTurnover;
		data["OpenVolume"] = task_data->OpenVolume;
		data["ClosedVolume"] = task_data->ClosedVolume;
		data["CloseNewVolume"] = task_data->CloseNewVolume;
		data["MarginMode"] = task_data->MarginMode;
		data["BuyTInitMargin"] = task_data->BuyTInitMargin;
		data["SellTInitMargin"] = task_data->SellTInitMargin;
		data["BuyBInitMargin"] = task_data->BuyBInitMargin;
		data["SellBInitMargin"] = task_data->SellBInitMargin;
		data["BuyLInitMargin"] = task_data->BuyLInitMargin;
		data["SellLInitMargin"] = task_data->SellLInitMargin;
		data["BuyMInitMargin"] = task_data->BuyMInitMargin;
		data["SellMInitMargin"] = task_data->SellMInitMargin;
		data["BuyTMaintMargin"] = task_data->BuyTMaintMargin;
		data["SellTMaintMargin"] = task_data->SellTMaintMargin;
		data["BuyBMaintMargin"] = task_data->BuyBMaintMargin;
		data["SellBMaintMargin"] = task_data->SellBMaintMargin;
		data["BuyLMaintMargin"] = task_data->BuyLMaintMargin;
		data["SellLMaintMargin"] = task_data->SellLMaintMargin;
		data["BuyMMaintMargin"] = task_data->BuyMMaintMargin;
		data["SellMMaintMargin"] = task_data->SellMMaintMargin;
		delete task_data;
	}
	this->onRspAccountRentInfo(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspTradeMessage(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPITradeMessage *task_data = (TapAPITradeMessage*)task->task_data;
		data["SerialID"] = task_data->SerialID;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["TMsgValidDateTime"] = toUtf(task_data->TMsgValidDateTime);
		data["TMsgTitle"] = toUtf(task_data->TMsgTitle);
		data["TMsgContent"] = toUtf(task_data->TMsgContent);
		data["TMsgType"] = task_data->TMsgType;
		data["TMsgLevel"] = task_data->TMsgLevel;
		data["IsSendBySMS"] = task_data->IsSendBySMS;
		data["IsSendByEMail"] = task_data->IsSendByEMail;
		data["Sender"] = toUtf(task_data->Sender);
		data["SendDateTime"] = toUtf(task_data->SendDateTime);
		delete task_data;
	}
	this->onRspTradeMessage(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRtnTradeMessage(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPITradeMessage *task_data = (TapAPITradeMessage*)task->task_data;
		data["SerialID"] = task_data->SerialID;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["TMsgValidDateTime"] = toUtf(task_data->TMsgValidDateTime);
		data["TMsgTitle"] = toUtf(task_data->TMsgTitle);
		data["TMsgContent"] = toUtf(task_data->TMsgContent);
		data["TMsgType"] = task_data->TMsgType;
		data["TMsgLevel"] = task_data->TMsgLevel;
		data["IsSendBySMS"] = task_data->IsSendBySMS;
		data["IsSendByEMail"] = task_data->IsSendByEMail;
		data["Sender"] = toUtf(task_data->Sender);
		data["SendDateTime"] = toUtf(task_data->SendDateTime);
		delete task_data;
	}
	this->onRtnTradeMessage(task->task_string, data);
};

void TdApi::processRspQryHisOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIHisOrderQryRsp *task_data = (TapAPIHisOrderQryRsp*)task->task_data;
		data["Date"] = toUtf(task_data->Date);
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		data["OrderType"] = task_data->OrderType;
		data["OrderSource"] = task_data->OrderSource;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["IsRiskOrder"] = task_data->IsRiskOrder;
		data["OrderSide"] = task_data->OrderSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["PositionEffect2"] = task_data->PositionEffect2;
		data["InquiryNo"] = toUtf(task_data->InquiryNo);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderPrice2"] = task_data->OrderPrice2;
		data["StopPrice"] = task_data->StopPrice;
		data["OrderQty"] = task_data->OrderQty;
		data["OrderMinQty"] = task_data->OrderMinQty;
		data["OrderCanceledQty"] = task_data->OrderCanceledQty;
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["OrderStreamID"] = task_data->OrderStreamID;
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["UpperStreamID"] = task_data->UpperStreamID;
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["OrderExchangeSystemNo"] = toUtf(task_data->OrderExchangeSystemNo);
		data["OrderParentSystemNo"] = toUtf(task_data->OrderParentSystemNo);
		data["OrderInsertUserNo"] = toUtf(task_data->OrderInsertUserNo);
		data["OrderInsertTime"] = toUtf(task_data->OrderInsertTime);
		data["OrderCommandUserNo"] = toUtf(task_data->OrderCommandUserNo);
		data["OrderUpdateUserNo"] = toUtf(task_data->OrderUpdateUserNo);
		data["OrderUpdateTime"] = toUtf(task_data->OrderUpdateTime);
		data["OrderState"] = task_data->OrderState;
		data["OrderMatchPrice"] = task_data->OrderMatchPrice;
		data["OrderMatchPrice2"] = task_data->OrderMatchPrice2;
		data["OrderMatchQty"] = task_data->OrderMatchQty;
		data["OrderMatchQty2"] = task_data->OrderMatchQty2;
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["MinClipSize"] = task_data->MinClipSize;
		data["MaxClipSize"] = task_data->MaxClipSize;
		data["LicenseNo"] = toUtf(task_data->LicenseNo);
		data["TacticsType"] = task_data->TacticsType;
		data["TriggerCondition"] = task_data->TriggerCondition;
		data["TriggerPriceType"] = task_data->TriggerPriceType;
		delete task_data;
	}
	this->onRspQryHisOrder(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryHisOrderProcess(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIHisOrderProcessQryRsp *task_data = (TapAPIHisOrderProcessQryRsp*)task->task_data;
		data["Date"] = toUtf(task_data->Date);
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["ContractNo2"] = toUtf(task_data->ContractNo2);
		data["StrikePrice2"] = toUtf(task_data->StrikePrice2);
		data["CallOrPutFlag2"] = task_data->CallOrPutFlag2;
		data["OrderType"] = task_data->OrderType;
		data["OrderSource"] = task_data->OrderSource;
		data["TimeInForce"] = task_data->TimeInForce;
		data["ExpireTime"] = toUtf(task_data->ExpireTime);
		data["IsRiskOrder"] = task_data->IsRiskOrder;
		data["OrderSide"] = task_data->OrderSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["PositionEffect2"] = task_data->PositionEffect2;
		data["InquiryNo"] = toUtf(task_data->InquiryNo);
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["OrderPrice"] = task_data->OrderPrice;
		data["OrderPrice2"] = task_data->OrderPrice2;
		data["StopPrice"] = task_data->StopPrice;
		data["OrderQty"] = task_data->OrderQty;
		data["OrderMinQty"] = task_data->OrderMinQty;
		data["OrderCanceledQty"] = task_data->OrderCanceledQty;
		data["RefInt"] = task_data->RefInt;
		data["RefDouble"] = task_data->RefDouble;
		data["RefString"] = toUtf(task_data->RefString);
		data["ServerFlag"] = task_data->ServerFlag;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["OrderStreamID"] = task_data->OrderStreamID;
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["UpperChannelNo"] = toUtf(task_data->UpperChannelNo);
		data["OrderLocalNo"] = toUtf(task_data->OrderLocalNo);
		data["UpperStreamID"] = task_data->UpperStreamID;
		data["OrderSystemNo"] = toUtf(task_data->OrderSystemNo);
		data["OrderExchangeSystemNo"] = toUtf(task_data->OrderExchangeSystemNo);
		data["OrderParentSystemNo"] = toUtf(task_data->OrderParentSystemNo);
		data["OrderInsertUserNo"] = toUtf(task_data->OrderInsertUserNo);
		data["OrderInsertTime"] = toUtf(task_data->OrderInsertTime);
		data["OrderCommandUserNo"] = toUtf(task_data->OrderCommandUserNo);
		data["OrderUpdateUserNo"] = toUtf(task_data->OrderUpdateUserNo);
		data["OrderUpdateTime"] = toUtf(task_data->OrderUpdateTime);
		data["OrderState"] = task_data->OrderState;
		data["OrderMatchPrice"] = task_data->OrderMatchPrice;
		data["OrderMatchPrice2"] = task_data->OrderMatchPrice2;
		data["OrderMatchQty"] = task_data->OrderMatchQty;
		data["OrderMatchQty2"] = task_data->OrderMatchQty2;
		data["ErrorCode"] = task_data->ErrorCode;
		data["ErrorText"] = toUtf(task_data->ErrorText);
		data["IsBackInput"] = task_data->IsBackInput;
		data["IsDeleted"] = task_data->IsDeleted;
		data["IsAddOne"] = task_data->IsAddOne;
		data["AddOneIsValid"] = task_data->AddOneIsValid;
		data["MinClipSize"] = task_data->MinClipSize;
		data["MaxClipSize"] = task_data->MaxClipSize;
		data["LicenseNo"] = toUtf(task_data->LicenseNo);
		data["TacticsType"] = task_data->TacticsType;
		data["TriggerCondition"] = task_data->TriggerCondition;
		data["TriggerPriceType"] = task_data->TriggerPriceType;
		delete task_data;
	}
	this->onRspQryHisOrderProcess(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryHisFill(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIHisFillQryRsp *task_data = (TapAPIHisFillQryRsp*)task->task_data;
		data["SettleDate"] = toUtf(task_data->SettleDate);
		data["TradeDate"] = toUtf(task_data->TradeDate);
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSource"] = task_data->MatchSource;
		data["MatchSide"] = task_data->MatchSide;
		data["PositionEffect"] = task_data->PositionEffect;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["MatchPrice"] = task_data->MatchPrice;
		data["MatchQty"] = task_data->MatchQty;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["MatchStreamID"] = task_data->MatchStreamID;
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["MatchCmbNo"] = toUtf(task_data->MatchCmbNo);
		data["ExchangeMatchNo"] = toUtf(task_data->ExchangeMatchNo);
		data["MatchUpperStreamID"] = task_data->MatchUpperStreamID;
		data["CommodityCurrencyGroup"] = toUtf(task_data->CommodityCurrencyGroup);
		data["CommodityCurrency"] = toUtf(task_data->CommodityCurrency);
		data["Turnover"] = task_data->Turnover;
		data["PremiumIncome"] = task_data->PremiumIncome;
		data["PremiumPay"] = task_data->PremiumPay;
		data["AccountFee"] = task_data->AccountFee;
		data["AccountFeeCurrencyGroup"] = toUtf(task_data->AccountFeeCurrencyGroup);
		data["AccountFeeCurrency"] = toUtf(task_data->AccountFeeCurrency);
		data["IsManualFee"] = task_data->IsManualFee;
		data["AccountOtherFee"] = task_data->AccountOtherFee;
		data["UpperFee"] = task_data->UpperFee;
		data["UpperFeeCurrencyGroup"] = toUtf(task_data->UpperFeeCurrencyGroup);
		data["UpperFeeCurrency"] = toUtf(task_data->UpperFeeCurrency);
		data["IsUpperManualFee"] = task_data->IsUpperManualFee;
		data["UpperOtherFee"] = task_data->UpperOtherFee;
		data["MatchDateTime"] = toUtf(task_data->MatchDateTime);
		data["UpperMatchDateTime"] = toUtf(task_data->UpperMatchDateTime);
		data["CloseProfit"] = task_data->CloseProfit;
		data["ClosePrice"] = task_data->ClosePrice;
		data["CloseQty"] = task_data->CloseQty;
		data["SettleGroupNo"] = toUtf(task_data->SettleGroupNo);
		data["OperatorNo"] = toUtf(task_data->OperatorNo);
		data["OperateTime"] = toUtf(task_data->OperateTime);
		delete task_data;
	}
	this->onRspQryHisFill(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryHisPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIHisPositionQryRsp *task_data = (TapAPIHisPositionQryRsp*)task->task_data;
		data["SettleDate"] = toUtf(task_data->SettleDate);
		data["OpenDate"] = toUtf(task_data->OpenDate);
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSide"] = task_data->MatchSide;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["PositionPrice"] = task_data->PositionPrice;
		data["PositionQty"] = task_data->PositionQty;
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["PositionNo"] = toUtf(task_data->PositionNo);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["CurrencyGroup"] = toUtf(task_data->CurrencyGroup);
		data["Currency"] = toUtf(task_data->Currency);
		data["PreSettlePrice"] = task_data->PreSettlePrice;
		data["SettlePrice"] = task_data->SettlePrice;
		data["PositionDProfit"] = task_data->PositionDProfit;
		data["LMEPositionProfit"] = task_data->LMEPositionProfit;
		data["OptionMarketValue"] = task_data->OptionMarketValue;
		data["AccountInitialMargin"] = task_data->AccountInitialMargin;
		data["AccountMaintenanceMargin"] = task_data->AccountMaintenanceMargin;
		data["UpperInitialMargin"] = task_data->UpperInitialMargin;
		data["UpperMaintenanceMargin"] = task_data->UpperMaintenanceMargin;
		data["SettleGroupNo"] = toUtf(task_data->SettleGroupNo);
		delete task_data;
	}
	this->onRspQryHisPosition(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryHisDelivery(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIHisDeliveryQryRsp *task_data = (TapAPIHisDeliveryQryRsp*)task->task_data;
		data["DeliveryDate"] = toUtf(task_data->DeliveryDate);
		data["OpenDate"] = toUtf(task_data->OpenDate);
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["MatchSource"] = task_data->MatchSource;
		data["OpenSide"] = task_data->OpenSide;
		data["OpenPrice"] = task_data->OpenPrice;
		data["DeliveryPrice"] = task_data->DeliveryPrice;
		data["DeliveryQty"] = task_data->DeliveryQty;
		data["FrozenQty"] = task_data->FrozenQty;
		data["OpenNo"] = toUtf(task_data->OpenNo);
		data["UpperNo"] = toUtf(task_data->UpperNo);
		data["CommodityCurrencyGroupy"] = toUtf(task_data->CommodityCurrencyGroupy);
		data["CommodityCurrency"] = toUtf(task_data->CommodityCurrency);
		data["PreSettlePrice"] = task_data->PreSettlePrice;
		data["DeliveryProfit"] = task_data->DeliveryProfit;
		data["AccountFrozenInitialMargin"] = task_data->AccountFrozenInitialMargin;
		data["AccountFrozenMaintenanceMargin"] = task_data->AccountFrozenMaintenanceMargin;
		data["UpperFrozenInitialMargin"] = task_data->UpperFrozenInitialMargin;
		data["UpperFrozenMaintenanceMargin"] = task_data->UpperFrozenMaintenanceMargin;
		data["AccountFeeCurrencyGroup"] = toUtf(task_data->AccountFeeCurrencyGroup);
		data["AccountFeeCurrency"] = toUtf(task_data->AccountFeeCurrency);
		data["AccountDeliveryFee"] = task_data->AccountDeliveryFee;
		data["UpperFeeCurrencyGroup"] = toUtf(task_data->UpperFeeCurrencyGroup);
		data["UpperFeeCurrency"] = toUtf(task_data->UpperFeeCurrency);
		data["UpperDeliveryFee"] = task_data->UpperDeliveryFee;
		data["DeliveryMode"] = task_data->DeliveryMode;
		data["OperatorNo"] = toUtf(task_data->OperatorNo);
		data["OperateTime"] = toUtf(task_data->OperateTime);
		data["SettleGourpNo"] = toUtf(task_data->SettleGourpNo);
		delete task_data;
	}
	this->onRspQryHisDelivery(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryAccountCashAdjust(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIAccountCashAdjustQryRsp *task_data = (TapAPIAccountCashAdjustQryRsp*)task->task_data;
		data["Date"] = toUtf(task_data->Date);
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["CashAdjustType"] = task_data->CashAdjustType;
		data["CurrencyGroupNo"] = toUtf(task_data->CurrencyGroupNo);
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["CashAdjustValue"] = task_data->CashAdjustValue;
		data["CashAdjustRemark"] = toUtf(task_data->CashAdjustRemark);
		data["OperateTime"] = toUtf(task_data->OperateTime);
		data["OperatorNo"] = toUtf(task_data->OperatorNo);
		data["AccountBank"] = toUtf(task_data->AccountBank);
		data["BankAccount"] = toUtf(task_data->BankAccount);
		data["AccountLWFlag"] = task_data->AccountLWFlag;
		data["CompanyBank"] = toUtf(task_data->CompanyBank);
		data["InternalBankAccount"] = toUtf(task_data->InternalBankAccount);
		data["CompanyLWFlag"] = task_data->CompanyLWFlag;
		delete task_data;
	}
	this->onRspQryAccountCashAdjust(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryBill(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIBillQryRsp *task_data = (TapAPIBillQryRsp*)task->task_data;
		data["Reqdata"] = task_data->Reqdata;
		data["BillLen"] = task_data->BillLen;
		data["BillText"] = task_data->BillText;
		delete task_data;
	}
	this->onRspQryBill(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspAccountFeeRent(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIAccountFeeRentQryRsp *task_data = (TapAPIAccountFeeRentQryRsp*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["MatchSource"] = task_data->MatchSource;
		data["CalculateMode"] = task_data->CalculateMode;
		data["CurrencyGroupNo"] = toUtf(task_data->CurrencyGroupNo);
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["OpenCloseFee"] = task_data->OpenCloseFee;
		data["CloseTodayFee"] = task_data->CloseTodayFee;
		delete task_data;
	}
	this->onRspAccountFeeRent(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspAccountMarginRent(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIAccountMarginRentQryRsp *task_data = (TapAPIAccountMarginRentQryRsp*)task->task_data;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["ContractNo"] = toUtf(task_data->ContractNo);
		data["StrikePrice"] = toUtf(task_data->StrikePrice);
		data["CallOrPutFlag"] = task_data->CallOrPutFlag;
		data["CalculateMode"] = task_data->CalculateMode;
		data["CurrencyGroupNo"] = toUtf(task_data->CurrencyGroupNo);
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["InitialMargin"] = task_data->InitialMargin;
		data["MaintenanceMargin"] = task_data->MaintenanceMargin;
		data["SellInitialMargin"] = task_data->SellInitialMargin;
		data["SellMaintenanceMargin"] = task_data->SellMaintenanceMargin;
		data["LockMargin"] = task_data->LockMargin;
		delete task_data;
	}
	this->onRspAccountMarginRent(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspAddMobileDevice(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIMobileDeviceAddRsp *task_data = (TapAPIMobileDeviceAddRsp*)task->task_data;
		data["UserNo"] = toUtf(task_data->UserNo);
		data["AppKey"] = toUtf(task_data->AppKey);
		data["AppID"] = toUtf(task_data->AppID);
		data["MasterSecret"] = toUtf(task_data->MasterSecret);
		data["Cid"] = toUtf(task_data->Cid);
		data["CompanyNo"] = toUtf(task_data->CompanyNo);
		data["CompanyAddressNo"] = toUtf(task_data->CompanyAddressNo);
		data["DeviceType"] = task_data->DeviceType;
		delete task_data;
	}
	this->onRspAddMobileDevice(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryManageInfoForEStar(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPIManageInfo *task_data = (TapAPIManageInfo*)task->task_data;
		data["MsgID"] = task_data->MsgID;
		data["SendFrom"] = toUtf(task_data->SendFrom);
		data["SendManageType"] = task_data->SendManageType;
		data["AccountNo"] = toUtf(task_data->AccountNo);
		data["SendAccount"] = toUtf(task_data->SendAccount);
		data["Title"] = toUtf(task_data->Title);
		data["Content"] = toUtf(task_data->Content);
		data["Attachment"] = toUtf(task_data->Attachment);
		data["SendStatus"] = task_data->SendStatus;
		data["Remark"] = toUtf(task_data->Remark);
		data["GUID"] = toUtf(task_data->GUID);
		data["OperatorNo"] = toUtf(task_data->OperatorNo);
		data["OperateTime"] = toUtf(task_data->OperateTime);
		delete task_data;
	}
	this->onRspQryManageInfoForEStar(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQrySystemParameter(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPISystemParameterInfo *task_data = (TapAPISystemParameterInfo*)task->task_data;
		data["ItemNo"] = toUtf(task_data->ItemNo);
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["CommodityType"] = task_data->CommodityType;
		data["ItemValue"] = task_data->ItemValue;
		data["ItemValueStr"] = toUtf(task_data->ItemValueStr);
		data["ItemValueDouble"] = task_data->ItemValueDouble;
		delete task_data;
	}
	this->onRspQrySystemParameter(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRspQryTradeCenterFrontAddress(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPITradeCenterFrontAddressInfo *task_data = (TapAPITradeCenterFrontAddressInfo*)task->task_data;
		data["FrontName"] = toUtf(task_data->FrontName);
		data["FrontAddress"] = toUtf(task_data->FrontAddress);
		data["FrontPort"] = toUtf(task_data->FrontPort);
		data["TradeCenter"] = task_data->TradeCenter;
		data["IsEnable"] = task_data->IsEnable;
		data["IsSSL"] = task_data->IsSSL;
		delete task_data;
	}
	this->onRspQryTradeCenterFrontAddress(task->task_string, task->task_id, task->task_int, task->task_last, data);
};

void TdApi::processRtnCommodityInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPICommodityInfo *task_data = (TapAPICommodityInfo*)task->task_data;
		data["ExchangeNo"] = toUtf(task_data->ExchangeNo);
		data["CommodityType"] = task_data->CommodityType;
		data["CommodityNo"] = toUtf(task_data->CommodityNo);
		data["CommodityName"] = toUtf(task_data->CommodityName);
		data["CommodityEngName"] = toUtf(task_data->CommodityEngName);
		data["RelateExchangeNo"] = toUtf(task_data->RelateExchangeNo);
		data["RelateCommodityType"] = task_data->RelateCommodityType;
		data["RelateCommodityNo"] = toUtf(task_data->RelateCommodityNo);
		data["RelateExchangeNo2"] = toUtf(task_data->RelateExchangeNo2);
		data["RelateCommodityType2"] = task_data->RelateCommodityType2;
		data["RelateCommodityNo2"] = toUtf(task_data->RelateCommodityNo2);
		data["TradeCurrency"] = toUtf(task_data->TradeCurrency);
		data["ContractSize"] = task_data->ContractSize;
		data["OpenCloseMode"] = task_data->OpenCloseMode;
		data["StrikePriceTimes"] = task_data->StrikePriceTimes;
		data["CommodityTickSize"] = task_data->CommodityTickSize;
		data["CommodityDenominator"] = task_data->CommodityDenominator;
		data["CmbDirect"] = task_data->CmbDirect;
		data["OnlyCanCloseDays"] = task_data->OnlyCanCloseDays;
		data["DeliveryMode"] = task_data->DeliveryMode;
		data["DeliveryDays"] = task_data->DeliveryDays;
		data["AddOneTime"] = toUtf(task_data->AddOneTime);
		data["CommodityTimeZone"] = task_data->CommodityTimeZone;
		data["IsAddOne"] = task_data->IsAddOne;
		delete task_data;
	}
	this->onRtnCommodityInfo(task->task_string, data);
};

void TdApi::processRtnCurrencyInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		TapAPICurrencyInfo *task_data = (TapAPICurrencyInfo*)task->task_data;
		data["CurrencyNo"] = toUtf(task_data->CurrencyNo);
		data["CurrencyGroupNo"] = toUtf(task_data->CurrencyGroupNo);
		data["TradeRate"] = task_data->TradeRate;
		data["TradeRate2"] = task_data->TradeRate2;
		data["FutureAlg"] = task_data->FutureAlg;
		data["OptionAlg"] = task_data->OptionAlg;
		delete task_data;
	}
	this->onRtnCurrencyInfo(task->task_string, data);
};



///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------
void TdApi::createEsTradeAPI()      // 改变了返回值
{
	int nResult;
	this->api = (IEsTradeAPI*)CreateEsTradeAPI(nResult); // 创建API接口对象
	this->api->SetAPINotify(this);  //注册回调函数对象

};

void TdApi::release()
{
	FreeEsTradeAPI(this->api);
};

void TdApi::init()
{
	this->active = true;
	this->task_thread = thread(&TdApi::processTask, this);
};


int TdApi::exit()
{
	this->active = false;
	this->task_queue.terminate();
	this->task_thread.join();

	this->api->SetAPINotify(NULL);
	FreeEsTradeAPI(this->api);
	this->api = NULL;
	return 1;
};

string TdApi::getEsTradeAPIVersion() //2
{
	char pVer[128] = { 0 };
	GetEsTradeAPIVersion(pVer, sizeof(pVer));
	return pVer;
};

int TdApi::setEsTradeAPIDataPath(string path)
{
	int i = this->api->SetEsTradeAPIDataPath(path.c_str());
	return i;
};



int TdApi::setEsTradeAPILogLevel(string level)
{
	int i = this->api->SetEsTradeAPILogLevel((char)level.c_str());
	return i;
};

int TdApi::setUserInfo(const dict &req)
{
	TapAPITradeUserInfo myreq = TapAPITradeUserInfo();
	memset(&myreq, 0, sizeof(myreq));
	getUnsignedInt(req, "SystemType", &myreq.SystemType);
	getString(req, "UserNo", myreq.UserNo);
	getString(req, "LoginIP", myreq.LoginIP);
	getUnsignedInt(req, "LoginProt", &myreq.LoginProt);
	getUnsignedInt(req, "LoginType", &myreq.LoginType);
	
	int i = this->api->SetUserInfo(&myreq);
	return i;
};

int TdApi::startUser(string userNo,  const dict &req)
{
	TapAPITradeLoginAuth myreq = TapAPITradeLoginAuth();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserNo", myreq.UserNo);
	getInt(req, "UserType", &myreq.UserType);
	getString(req, "AuthCode", myreq.AuthCode);
	getString(req, "AppID", myreq.AppID);
	getChar(req, "ISModifyPassword", &myreq.ISModifyPassword);
	getString(req, "Password", myreq.Password);
	getString(req, "NewPassword", myreq.NewPassword);
	getString(req, "DDASerialNo", myreq.DDASerialNo);
	getUnsignedInt(req, "NoticeIgnoreFlag", &myreq.NoticeIgnoreFlag);
	getString(req, "LoginInfo", myreq.LoginInfo);
	
	int i = this->api->StartUser((char*)userNo.c_str(), &myreq);
	
	return i;

};

int TdApi::stopUser(string userNo)
{

	int i = this->api->StopUser((char*)userNo.c_str()); 
	return i;

};
/*int TdApi::requestVertificateCode(string userNo, unsigned int nSessionID, const dict &req) // 请求发送二次认证认证码(北斗星专用)
{
	TapAPISecondInfo myreq = TapAPISecondInfo();
	memset(&myreq, 0, sizeof(myreq));

	getChar(req, "SendType", &myreq.SendType);
	getString(req, "SendAccount", myreq.SendAccount);
	int i = this->api->RequestVertificateCode((char*)userNo.c_str(), nSessionID, &myreq);
	return i;

};

int TdApi::setVertificateCode(string userNo, unsigned int nSessionID,string const VertificateCode) // 设置二次认证信息。(北斗星专用)
{
	int i = this->api->SetVertificateCode((char*)userNo.c_str(), nSessionID, (char*)VertificateCode.c_str());
	return i;

};
*/

int TdApi::getAccount(string userNo)//, TAPIUINT32 nDataSeqID, TapAPIAccountInfo *pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG &isLast)
{
	int n = 0, nDataSeqID = 1, nOutLen = 5, nCurr = 0;
	TAPIYNFLAG flag = APIYNFLAG_NO;
	TapAPIAccountInfo* pOutInfo[30];

	while (flag == APIYNFLAG_NO)
	{
		n = this->api->GetAccount((char*)userNo.c_str(), nDataSeqID, pOutInfo, nOutLen, flag);

		nCurr = (n > nOutLen) ? nOutLen : n;

		for (int i = 0; i < nCurr; i++)
		{
			cout << pOutInfo[i]->AccountNo << "," << pOutInfo[i]->AccountType << ","
				<< pOutInfo[i]->AccountState << "," << pOutInfo[i]->AccountShortName << ","
				<< pOutInfo[i]->IsMarketMaker << endl;
		}

		nDataSeqID = nDataSeqID + nCurr;
	}
	cout << "GetAccount done," << nDataSeqID - 1 << endl;
	return n;
};


int TdApi::getExchange(string userNo)
{
	int n = 0, nDataSeqID = 1, nOutLen = 4, nCurr = 0;
	TAPIYNFLAG flag = APIYNFLAG_NO;
	TapAPIExchangeInfo* pOutInfo[30];

	while (flag == APIYNFLAG_NO)
	{
		n = this->api->GetExchange((char*)userNo.c_str(), nDataSeqID, pOutInfo, nOutLen, flag);

		nCurr = (n > nOutLen) ? nOutLen : n;

		for (int i = 0; i < nCurr; i++)
			cout << pOutInfo[i]->ExchangeNo << "," << pOutInfo[i]->ExchangeName << endl;

		nDataSeqID += nCurr;
	}
	cout << "GetExchange done," << nDataSeqID - 1 << endl;
	return n;
}

int TdApi::getCommodity(string userNo)
{
	int n = 0, nDataSeqID = 1, nOutLen = 30, nCurr = 0;
	TAPIYNFLAG flag = APIYNFLAG_NO;
	TapAPICommodityInfo* pOutInfo[31];

	while (flag == APIYNFLAG_NO)
	{
		n = this->api->GetCommodity((char*)userNo.c_str(), nDataSeqID, pOutInfo, nOutLen, flag);

		nCurr = (n > nOutLen) ? nOutLen : n;

		if (flag == APIYNFLAG_YES)
			for (int i = 0; i < nCurr; i++)
				cout << pOutInfo[i]->ExchangeNo << "," << pOutInfo[i]->CommodityType << "," << pOutInfo[i]->CommodityNo << ","
				<< pOutInfo[i]->CommodityName << "," << pOutInfo[i]->CommodityEngName << ","
				<< pOutInfo[i]->RelateExchangeNo << "," << pOutInfo[i]->RelateCommodityType << "," << pOutInfo[i]->RelateCommodityNo << ","
				<< pOutInfo[i]->RelateExchangeNo2 << "," << pOutInfo[i]->RelateCommodityType2 << "," << pOutInfo[i]->RelateCommodityNo2 << ","
				<< pOutInfo[i]->TradeCurrency << "," << pOutInfo[i]->ContractSize << "," << pOutInfo[i]->OpenCloseMode << ","
				<< pOutInfo[i]->StrikePriceTimes << "," << pOutInfo[i]->CommodityTickSize << "," << pOutInfo[i]->CommodityDenominator << ","
				<< pOutInfo[i]->CmbDirect << "," << pOutInfo[i]->OnlyCanCloseDays << "," << pOutInfo[i]->DeliveryMode << ","
				<< pOutInfo[i]->DeliveryDays << "," << pOutInfo[i]->AddOneTime << "," << pOutInfo[i]->CommodityTimeZone << ","
				<< pOutInfo[i]->IsAddOne << endl;

		nDataSeqID += nCurr;
	}
	cout << "GetCommodity done," << nDataSeqID - 1 << endl;
	return n;
};
int TdApi::getContract(string userNo) 
{
	int n = 0, nDataSeqID = 1, nOutLen = 30, nCurr = 0;
	TAPIYNFLAG flag = APIYNFLAG_NO;
	TapAPITradeContractInfo* pOutInfo[31];
	TapAPICommodity APICommodity;
	memset(&APICommodity, 0, sizeof(APICommodity));

	while (flag == APIYNFLAG_NO)
	{
		n = this->api->GetContract((char*)userNo.c_str(), &APICommodity, nDataSeqID, pOutInfo, nOutLen, flag);

		nCurr = (n > nOutLen) ? nOutLen : n;

		if (flag == APIYNFLAG_YES)
			for (int i = 0; i < nCurr; i++)
				cout << pOutInfo[i]->ExchangeNo << "," << pOutInfo[i]->CommodityType << "," << pOutInfo[i]->CommodityNo << ","
				<< pOutInfo[i]->ContractNo1 << "," << pOutInfo[i]->StrikePrice1 << "," << pOutInfo[i]->CallOrPutFlag1 << ","
				<< pOutInfo[i]->ContractNo1 << "," << pOutInfo[i]->StrikePrice2 << "," << pOutInfo[i]->CallOrPutFlag2 << ","
				<< pOutInfo[i]->ContractName << "," << pOutInfo[i]->ContractExpDate << "," << pOutInfo[i]->LastTradeDate << ","
				<< pOutInfo[i]->FirstNoticeDate << "," << pOutInfo[i]->FutureContractNo
				<< endl;

		nDataSeqID += nCurr;
	}
	cout << "GetContract done," << nDataSeqID - 1 << endl;
	return n;

};
int TdApi::getFund(string userNo) 
{
	int n = 0, nOutLen = 4, nCurr = 0;
	TAPIYNFLAG flag = APIYNFLAG_NO;
	TapAPIFundData* pOutInfo[30];

	TapAPIFundReq APIFundReq;
	memset(&APIFundReq, 0, sizeof(APIFundReq));
	APIFundReq.DataSeqID = 1;

	while (flag == APIYNFLAG_NO)
	{
		n = this->api->GetFund((char*)userNo.c_str(), &APIFundReq, pOutInfo, nOutLen, flag);

		nCurr = (n > nOutLen) ? nOutLen : n;

		for (int i = 0; i < nCurr; i++)
			cout << pOutInfo[i]->AccountNo << "," << pOutInfo[i]->Available << "," << pOutInfo[i]->FrozenDeposit << endl;

		APIFundReq.DataSeqID += nCurr;
	}

	cout << "GetFund done," << APIFundReq.DataSeqID - 1 << endl;
	return n;
};
int TdApi::getOrder(string userNo)
{
	int n = 0, nOutLen = 4, nCurr = 0;
	TAPIYNFLAG flag = APIYNFLAG_NO;
	TapAPIOrderInfo pOutInfo[30];

	TapAPIOrderQryReq APIReq;
	memset(&APIReq, 0, sizeof(APIReq));
	APIReq.DataSeqID = 1;
	APIReq.OrderQryType = TAPI_ORDER_QRY_TYPE_ALL;

	while (flag == APIYNFLAG_NO)
	{
		n = this->api->GetOrder((char*)userNo.c_str(), &APIReq, pOutInfo, nOutLen, flag);

		nCurr = (n > nOutLen) ? nOutLen : n;

		if (flag == APIYNFLAG_YES)
			for (int i = 0; i < nCurr; i++)
				cout << pOutInfo[i].AccountNo << "," << pOutInfo[i].OrderNo << "," << pOutInfo[i].CommodityNo << "," << pOutInfo[i].ContractNo<<"ServerFlag:"<< pOutInfo[i].ServerFlag<< endl;

		APIReq.DataSeqID += nCurr;
	}

	cout << "GetOrder done," << APIReq.DataSeqID - 1 << endl;
	return n;
};
int TdApi::getFill(string userNo)
{
	int n = 0, nOutLen = 4, nCurr = 0;
	TAPIYNFLAG flag = APIYNFLAG_NO;
	TapAPIFillInfo pOutInfo[30];

	TapAPIFillQryReq APIReq;
	memset(&APIReq, 0, sizeof(APIReq));
	APIReq.DataSeqID = 1;

	while (flag == APIYNFLAG_NO)
	{
		n = this->api->GetFill((char*)userNo.c_str(), &APIReq, pOutInfo, nOutLen, flag);

		nCurr = (n > nOutLen) ? nOutLen : n;

		if (flag == APIYNFLAG_YES)
			for (int i = 0; i < nCurr; i++)
				cout << pOutInfo[i].AccountNo << "," << pOutInfo[i].OrderNo << endl;

		APIReq.DataSeqID += nCurr;

	}

	cout << "GetFill done," << APIReq.DataSeqID - 1 << endl;
	return n;

};

int TdApi::getClose(string userNo) 
{

	int n = 0, nOutLen = 4, nCurr = 0;
	TAPIYNFLAG flag = APIYNFLAG_NO;
	TapAPICloseInfo pOutInfo[30];

	TapAPICloseQryReq APIReq;
	memset(&APIReq, 0, sizeof(APIReq));
	APIReq.DataSeqID = 1;

	while (flag == APIYNFLAG_NO)
	{
		n = this->api->GetClose((char*)userNo.c_str(), &APIReq, pOutInfo, nOutLen, flag);

		if (n < 0)
		{
			cout << "GetClose done " << n << endl;
			return n;
		}

		nCurr = (n > nOutLen) ? nOutLen : n;

		if (flag == APIYNFLAG_YES)
			for (int i = 0; i < nCurr; i++)
				cout << pOutInfo[i].AccountNo << "," << pOutInfo[i].CommodityNo << "," << pOutInfo[i].ContractNo << "," << pOutInfo[i].OpenMatchNo << endl;

		APIReq.DataSeqID += nCurr;
	}

	cout << "GetClose done," << APIReq.DataSeqID - 1 << endl;
	return n;

};
int TdApi::getPosition(string userNo)
{
	int n = 0, nOutLen = 4, nCurr = 0;
	TAPIYNFLAG flag = APIYNFLAG_NO;
	TapAPIPositionInfo pOutInfo[30];

	TapAPIPositionQryReq APIReq;
	memset(&APIReq, 0, sizeof(APIReq));
	APIReq.DataSeqID = 1;

	while (flag == APIYNFLAG_NO)
	{
		n = this->api->GetPosition((char*)userNo.c_str(), &APIReq, pOutInfo, nOutLen, flag);

		nCurr = (n > nOutLen) ? nOutLen : n;

		if (flag == APIYNFLAG_YES)
			for (int i = 0; i < nCurr; i++)
				cout << pOutInfo[i].AccountNo << "," << pOutInfo[i].PositionNo << "," << pOutInfo[i].PositionQty << ","<< pOutInfo[i].CommodityNo << "," << pOutInfo[i].ContractNo << "," << pOutInfo[i].HedgeFlag << "," << pOutInfo[i].HedgeFlag<< endl;

		APIReq.DataSeqID += nCurr;
	}

	cout << "GetPosition done," << APIReq.DataSeqID - 1 << endl;
	return n;
}



int TdApi::changePassword(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIChangePasswordReq myreq = TapAPIChangePasswordReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "NewPassword", myreq.NewPassword);
	getString(req, "OldPassword", myreq.OldPassword);
	int i = this->api->ChangePassword((char*)userNo.c_str(), nRequestID, &myreq);
	return i;

};
int TdApi::haveCertainRight(string userNo, int nRightID)
{
	int i = this->api->HaveCertainRight((char*)userNo.c_str(), nRightID);
	return i;
};
int TdApi::setReservedInfo(string userNo, unsigned int nRequestID, string info)
{
	int i = this->api->SetReservedInfo((char*)userNo.c_str(), nRequestID, (char*)info.c_str());
	return i;
};
int TdApi::getExchangeStateInfo(string userNo, unsigned int nDataSeqID, unsigned int nOutLen, char flag)
{
	//TapAPIExchangeStateInfo myreq = TapAPIExchangeStateInfo();
	//memset(&myreq, 0, sizeof(myreq));
	//getString(req, "CommodityNo", myreq.CommodityNo);
	//getString(req, "ExchangeNo", myreq.ExchangeNo);
	//getChar(req, "CommodityType", &myreq.CommodityType);
	//getString(req, "ExchangeNo", myreq.ExchangeNo);
	//getString(req, "ExchangeNo", myreq.ExchangeNo);

	//int i = this->api->GetExchangeStateInfo((char*)userNo.c_str(), nDataSeqID, &myreq, nOutLen, last);
	//return i;
	int n = 0,  nCurr = 0;
	
	TapAPIExchangeStateInfo* pOutInfo[30];

	while (flag == APIYNFLAG_NO)
	{
		n = this->api->GetExchangeStateInfo((char*)userNo.c_str(), nDataSeqID, pOutInfo, nOutLen, flag);

		nCurr = (n > nOutLen) ? nOutLen : n;

		for (int i = 0; i < nCurr; i++)
			cout << pOutInfo[i]->UpperChannelNo << "," << pOutInfo[i]->ExchangeNo << ","
			<< pOutInfo[i]->CommodityType << "," << pOutInfo[i]->CommodityNo << ","
			<< pOutInfo[i]->TradingState << "," << pOutInfo[i]->ExchangeTime << ","
			<< endl;

		nDataSeqID += nCurr;
	}
	cout << "GetExchangeStateInfo done," << nDataSeqID - 1 << endl;
	return n;
};
int TdApi::getUpperChannel(string userNo, unsigned int nDataSeqID,  unsigned int nOutLen, char flag)
{
	int n = 0, nCurr = 0;

	TapAPIUpperChannelInfo* pOutInfo[30];

	while (flag == APIYNFLAG_NO)
	{
		n = this->api->GetUpperChannel((char*)userNo.c_str(), nDataSeqID, pOutInfo, nOutLen, flag);

		nCurr = (n > nOutLen) ? nOutLen : n;

		for (int i = 0; i < nCurr; i++)
			cout << pOutInfo[i]->UpperChannelNo << "," << pOutInfo[i]->UpperChannelName << ","
			<< pOutInfo[i]->UpperNo << "," << pOutInfo[i]->UpperUserNo << ","
			<< endl;

		nDataSeqID += nCurr;
	}
	cout << "GetUpperChannel done," << nDataSeqID - 1 << endl;
	return n;
};
int TdApi::getCurrency(string userNo, unsigned int nDataSeqID, unsigned int nOutLen, char flag)
{
	int n = 0, nCurr = 0;
	
	TapAPICurrencyInfo* pOutInfo[30];

	while (flag == APIYNFLAG_NO)
	{
		n = this->api->GetCurrency((char*)userNo.c_str(), nDataSeqID, pOutInfo, nOutLen, flag);

		nCurr = (n > nOutLen) ? nOutLen : n;

		for (int i = 0; i < nCurr; i++)
			cout << pOutInfo[i]->CurrencyNo << "," << pOutInfo[i]->CurrencyGroupNo << ","
			<< pOutInfo[i]->TradeRate << "," << pOutInfo[i]->TradeRate2 << ","
			<< pOutInfo[i]->FutureAlg << "," << pOutInfo[i]->OptionAlg << ","
			<< endl;

		nDataSeqID += nCurr;
	}
	cout << "GetCurrency done," << nDataSeqID - 1 << endl;
	return n;
};

int TdApi::qryAccountRent(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIAccountRentQryReq myreq = TapAPIAccountRentQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getChar(req, "CommodityType", &myreq.CommodityType);
	getString(req, "CommodityNo", myreq.CommodityNo);
	getString(req, "ContractNo", myreq.ContractNo);
	int i = this->api->QryAccountRent((char*)userNo.c_str(), nRequestID, &myreq);
	return i;
};
//-------------------------------------------qry
int TdApi::qryOrderProcess(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIOrderProcessQryReq myreq = TapAPIOrderProcessQryReq();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ServerFlag", &myreq.ServerFlag);
	getString(req, "OrderNo", myreq.OrderNo);
	int i = this->api->QryOrderProcess((char*)userNo.c_str(), nRequestID,  &myreq);
	return i;
	 
};

int TdApi::qryDeepQuote(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIContract myreq = TapAPIContract();
	TapAPICommodity info = TapAPICommodity();

	memset(&myreq, 0, sizeof(myreq));
	memset(&info, 0, sizeof(info));

	getString(req, "ExchangeNo", info.ExchangeNo);
	getChar(req, "CommodityType", &info.CommodityType);
	getString(req, "CommodityNo", info.CommodityNo);
	myreq.Commodity = info;

	getString(req, "ContractNo1", myreq.ContractNo1);
	getString(req, "StrikePrice1", myreq.StrikePrice1);
	getChar(req, "CallOrPutFlag1", &myreq.CallOrPutFlag1);
	getString(req, "ContractNo2", myreq.ContractNo2);
	getString(req, "StrikePrice2", myreq.StrikePrice2);
	getChar(req, "CallOrPutFlag2", &myreq.CallOrPutFlag2);
	int i = this->api->QryDeepQuote((char*)userNo.c_str(), nRequestID, &myreq);
	return i;
};

//----------
pybind11::tuple TdApi::insertOrder(string userNo, unsigned int nRequestID, const dict &req) //string UserNo, unsigned int nRequestID,
{
	TapAPINewOrder myreq = TapAPINewOrder();

	getString(req, "AccountNo", myreq.AccountNo);
	getString(req, "ExchangeNo", myreq.ExchangeNo);
	getChar(req, "CommodityType", &myreq.CommodityType);
	getString(req, "CommodityNo", myreq.CommodityNo);
	getString(req, "ContractNo", myreq.ContractNo);

	getString(req, "StrikePrice", myreq.StrikePrice);
	getChar(req, "CallOrPutFlag", &myreq.CallOrPutFlag);
	getString(req, "ContractNo2", myreq.ContractNo2);
	getString(req, "StrikePrice2", myreq.StrikePrice2);
	getChar(req, "CallOrPutFlag2", &myreq.CallOrPutFlag2);

	getChar(req, "OrderType", &myreq.OrderType);
	getChar(req, "OrderSource", &myreq.OrderSource);
	getChar(req, "TimeInForce", &myreq.TimeInForce);
	getString(req, "ExpireTime", myreq.ExpireTime);

	getChar(req, "IsRiskOrder", &myreq.IsRiskOrder);
	getChar(req, "OrderSide", &myreq.OrderSide);
	getChar(req, "PositionEffect", &myreq.PositionEffect);
	getChar(req, "PositionEffect2", &myreq.PositionEffect2);
	getString(req, "InquiryNo", myreq.InquiryNo);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);

	getDouble(req, "OrderPrice", &myreq.OrderPrice);
	getDouble(req, "OrderPrice2", &myreq.OrderPrice2);
	getDouble(req, "StopPrice", &myreq.StopPrice);
	getUnsignedInt(req, "OrderQty", &myreq.OrderQty);
	getUnsignedInt(req, "OrderMinQty", &myreq.OrderMinQty);

	getUnsignedInt(req, "MinClipSize", &myreq.MinClipSize);
	getUnsignedInt(req, "MaxClipSize", &myreq.MaxClipSize);

	getInt(req, "RefInt", &myreq.RefInt);
	//getDouble(req, "RefDouble", &myreq.RefDouble);
	getString(req, "RefString", myreq.RefString);

	
	getChar(req, "TacticsType", &myreq.TacticsType);
	getChar(req, "TriggerCondition", &myreq.TriggerCondition);
	getChar(req, "TriggerPriceType", &myreq.TriggerPriceType);
	getChar(req, "AddOneIsValid", &myreq.AddOneIsValid);

	int i = this->api->InsertOrder((char*)userNo.c_str(), nRequestID, &myreq);
	

	pybind11::tuple result = pybind11::make_tuple(i, (char*)userNo.c_str(), nRequestID);

	return result;

};

int TdApi::cancelOrder(string userNo,unsigned int nRequestID,  const dict &req)
{
	TapAPIOrderCancelReq myreq = TapAPIOrderCancelReq();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "RefInt", &myreq.RefInt);
	getString(req, "RefString", myreq.RefString);
	getChar(req, "ServerFlag", &myreq.ServerFlag);
	getString(req, "OrderNo", myreq.OrderNo);
	int i = this->api->CancelOrder((char*)userNo.c_str(), nRequestID, &myreq);
	return i;

};

int TdApi::activateOrder(string userNo, unsigned int nRequestID, const dict &req)
{
	TapAPIOrderActivateReq myreq = TapAPIOrderActivateReq();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "RefInt", &myreq.RefInt);
	getString(req, "RefString", myreq.RefString);
	getChar(req, "ServerFlag", &myreq.ServerFlag);
	getString(req, "OrderNo", myreq.OrderNo);
	int i = this->api->ActivateOrder((char*)userNo.c_str(), nRequestID, &myreq);
	return i;
};

///-------------------------------------------------------------------------------------
///Pybindll封装
///-------------------------------------------------------------------------------------

class PyTdApi : public TdApi
{
public:
	using TdApi::TdApi;

	void onConnect(string userNo) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onConnect, userNo);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspLogin(string userNo, int error, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspLogin, userNo, error, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
	/*
	void onRtnContactInfo(string userNo, int error, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnContactInfo, userNo, error, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspRequestVertificateCode(string userNo, unsigned int request, int error, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspRequestVertificateCode, userNo, request, error, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
	*/
	void onRtnErrorMsg(string userNo, string ErrorMsg) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnErrorMsg, userNo, ErrorMsg);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
	
	void onAPIReady(string userNo) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onAPIReady, userNo);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	
	void onDisconnect(string userNo, int nReasonCode) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onDisconnect, userNo, nReasonCode);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
	
	void onRspSubmitUserLoginInfo(string userNo, unsigned int nSessionID, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspSubmitUserLoginInfo, userNo, nSessionID, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
	
	void onRspChangePassword(string userNo, unsigned int nSessionID, int nErrorCode) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspChangePassword, userNo, nSessionID, nErrorCode);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspSetReservedInfo(string userNo, unsigned int nSessionID, int nErrorCode, string info) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspSetReservedInfo, userNo, nSessionID, nErrorCode, info);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnContract(string userNo, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnContract, userNo, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnFund(string userNo, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnFund, userNo, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnOrder(string userNo, unsigned int nRequestID, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnOrder, userNo, nRequestID, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
	
	void onRspQryOrderProcess(string userNo, unsigned int nnRequestIDID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryOrderProcess, userNo, nnRequestIDID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
	
	void onRtnFill(string userNo, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnFill, userNo, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	}
	void onRtnPosition(string userNo, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnPosition, userNo, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
	
	void onRtnClose(string userNo, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnClose, userNo, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnPositionProfit(string userNo, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnPositionProfit, userNo, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
	
	void onRspQryDeepQuote(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryDeepQuote, userNo, nErrorCode, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
	

	
	void onRtnExchangeStateInfo(string userNo, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnExchangeStateInfo, userNo, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
	
	void onRtnReqQuoteNotice(string userNo, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnReqQuoteNotice, userNo, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspAccountRentInfo(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspAccountRentInfo, userNo, nRequestID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspTradeMessage(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspTradeMessage, userNo, nRequestID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnTradeMessage(string userNo, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnTradeMessage, userNo, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
	/*北斗星专用
	void onRspQryHisOrder(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryHisOrder, userNo, nRequestID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryHisOrderProcess(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryHisOrderProcess, userNo, nRequestID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryHisFill(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryHisFill, userNo, nRequestID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryHisPosition(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryHisPosition, userNo, nRequestID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryHisDelivery(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryHisDelivery, userNo, nRequestID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryAccountCashAdjust(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryAccountCashAdjust, userNo, nRequestID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryBill(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryBill, userNo, nRequestID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspAccountFeeRent(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspAccountFeeRent, userNo, nRequestID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspAccountMarginRent(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspAccountMarginRent, userNo, nRequestID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspAddMobileDevice(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspAddMobileDevice, userNo, nRequestID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryManageInfoForEStar(string userNo, unsigned int nRequestID, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryManageInfoForEStar, userNo, nRequestID, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQrySystemParameter(string userNo, unsigned int request, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQrySystemParameter, userNo, request, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryTradeCenterFrontAddress(string userNo, unsigned int request, int nErrorCode, char last, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryTradeCenterFrontAddress, userNo, request, nErrorCode, last, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnCommodityInfo(string userNo, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnCommodityInfo, userNo, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnCurrencyInfo(string userNo, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnCurrencyInfo, userNo, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

*/


};






PYBIND11_MODULE(vnestd, m) 
{
	class_<TdApi, PyTdApi> tdapi(m, "TdApi", module_local());
	tdapi
		.def(init<>())
		.def("createEsTradeAPI", &TdApi::createEsTradeAPI)
		.def("release", &TdApi::release)
		.def("init", &TdApi::init)
		.def("exit", &TdApi::exit)
		.def("getEsTradeAPIVersion", &TdApi::getEsTradeAPIVersion)
		.def("setEsTradeAPIDataPath", &TdApi::setEsTradeAPIDataPath)
		.def("setEsTradeAPILogLevel", &TdApi::setEsTradeAPILogLevel)
		.def("setUserInfo", &TdApi::setUserInfo)
		.def("startUser", &TdApi::startUser)
		.def("stopUser", &TdApi::stopUser)
		.def("qryOrderProcess", &TdApi::qryOrderProcess)
		.def("getAccount", &TdApi::getAccount)
		.def("getExchange", &TdApi::getExchange)
		.def("getPosition", &TdApi::getPosition)
		.def("qryDeepQuote", &TdApi::qryDeepQuote)
		.def("getCommodity", &TdApi::getCommodity)
		.def("getContract", &TdApi::getContract)
		.def("getFund", &TdApi::getFund)
		.def("getOrder", &TdApi::getOrder)
		.def("getFill", &TdApi::getFill)
		.def("getPosition", &TdApi::getPosition)
		.def("getClose", &TdApi::getClose)
		.def("getExchangeStateInfo", &TdApi::getExchangeStateInfo)
		.def("getUpperChannel", &TdApi::getUpperChannel)
		.def("getCurrency", &TdApi::getCurrency)
		.def("qryAccountRent", &TdApi::qryAccountRent)

		.def("insertOrder", &TdApi::insertOrder)
		.def("cancelOrder", &TdApi::cancelOrder)


		.def("onConnect", &TdApi::onConnect)
		.def("onRspLogin", &TdApi::onRspLogin)
		.def("onRtnContactInfo", &TdApi::onRtnContactInfo)
		//.def("onRspRequestVertificateCode", &TdApi::onRspRequestVertificateCode)    //北斗星专用    
		.def("onRtnErrorMsg", &TdApi::onRtnErrorMsg)
		.def("onAPIReady", &TdApi::onAPIReady)

		
		.def("onDisconnect", &TdApi::onDisconnect)
		.def("onRspSubmitUserLoginInfo", &TdApi::onRspSubmitUserLoginInfo)
		.def("onRspQryOrderProcess", &TdApi::onRspQryOrderProcess)
		.def("onRtnExchangeStateInfo", &TdApi::onRtnExchangeStateInfo)
		.def("onRspQryDeepQuote", &TdApi::onRspQryDeepQuote)


		.def("onRtnPosition", &TdApi::onRtnPosition)
		
		.def("onRspChangePassword", &TdApi::onRspChangePassword)
		.def("onRspSetReservedInfo", &TdApi::onRspSetReservedInfo)
		.def("onRtnContract", &TdApi::onRtnContract)
		.def("onRtnFund", &TdApi::onRtnFund)
		.def("onRtnOrder", &TdApi::onRtnOrder)
		.def("onRspQryOrderProcess", &TdApi::onRspQryOrderProcess)
		.def("onRtnFill", &TdApi::onRtnFill)
		.def("onRtnPosition", &TdApi::onRtnPosition)
		.def("onRtnClose", &TdApi::onRtnClose)
		//.def("onRtnPositionProfit", &TdApi::onRtnPositionProfit)
		.def("onRspQryDeepQuote", &TdApi::onRspQryDeepQuote)
		
		//.def("onRtnExchangeStateInfo", &TdApi::onRtnExchangeStateInfo)
		
		.def("onRtnReqQuoteNotice", &TdApi::onRtnReqQuoteNotice)
		.def("onRspAccountRentInfo", &TdApi::onRspAccountRentInfo)
		.def("onRspTradeMessage", &TdApi::onRspTradeMessage)
		.def("onRtnTradeMessage", &TdApi::onRtnTradeMessage)

		//北斗专用
		/*.def("onRspQryHisOrder", &TdApi::onRspQryHisOrder)    
		.def("onRspQryHisOrderProcess", &TdApi::onRspQryHisOrderProcess)
		.def("onRspQryHisFill", &TdApi::onRspQryHisFill)
		.def("onRspQryHisPosition", &TdApi::onRspQryHisPosition)
		.def("onRspQryHisDelivery", &TdApi::onRspQryHisDelivery)
		.def("onRspQryAccountCashAdjust", &TdApi::onRspQryAccountCashAdjust)
		.def("onRspQryBill", &TdApi::onRspQryBill)
		.def("onRspAccountFeeRent", &TdApi::onRspAccountFeeRent)
		.def("onRspAccountMarginRent", &TdApi::onRspAccountMarginRent)
		.def("onRspAddMobileDevice", &TdApi::onRspAddMobileDevice)
		.def("onRspQryManageInfoForEStar", &TdApi::onRspQryManageInfoForEStar)
		.def("onRspQrySystemParameter", &TdApi::onRspQrySystemParameter)
		.def("onRspQryTradeCenterFrontAddress", &TdApi::onRspQryTradeCenterFrontAddress)
		.def("onRtnCommodityInfo", &TdApi::onRtnCommodityInfo)
		.def("onRtnCurrencyInfo", &TdApi::onRtnCurrencyInfo)*/
		
		;

}