void TdApi::OnConnect()
{
	Task task = Task();
	task.task_name = ONCONNECT;
	this->task_queue.push(task);
};

void TdApi::OnRspLogin(int errorCode, TapAPITradeLoginRspInfo *loginRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPLOGIN;
	task.task_int = errorCode;
	if (loginRspInfo)
	{
		TapAPITradeLoginRspInfo *task_data = new TapAPITradeLoginRspInfo();
		*task_data = *loginRspInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnContactInfo(int errorCode, char isLast, string ContactInfo)
{
	Task task = Task();
	task.task_name = ONRTNCONTACTINFO;
	task.task_int = errorCode;
	task.task_last = isLast;
	task.task_string = ContactInfo;
	this->task_queue.push(task);
};

void TdApi::OnRspRequestVertificateCode(unsigned int sessionID, int errorCode, TapAPIRequestVertificateCodeRsp *rsp)
{
	Task task = Task();
	task.task_name = ONRSPREQUESTVERTIFICATECODE;
	task.task_id = sessionID;
	task.task_int = errorCode;
	if (rsp)
	{
		TapAPIRequestVertificateCodeRsp *task_data = new TapAPIRequestVertificateCodeRsp();
		*task_data = *rsp;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnExpriationDate(string date, int days)
{
	Task task = Task();
	task.task_name = ONEXPRIATIONDATE;
	task.task_string = date;
	task.task_int = days;
	this->task_queue.push(task);
};

void TdApi::OnAPIReady(int errorCode)
{
	Task task = Task();
	task.task_name = ONAPIREADY;
	task.task_int = errorCode;
	this->task_queue.push(task);
};

void TdApi::OnDisconnect(int reasonCode)
{
	Task task = Task();
	task.task_name = ONDISCONNECT;
	task.task_int = reasonCode;
	this->task_queue.push(task);
};

void TdApi::OnRspChangePassword(unsigned int sessionID, int errorCode)
{
	Task task = Task();
	task.task_name = ONRSPCHANGEPASSWORD;
	task.task_id = sessionID;
	task.task_int = errorCode;
	this->task_queue.push(task);
};

void TdApi::OnRspAuthPassword(unsigned int sessionID, int errorCode)
{
	Task task = Task();
	task.task_name = ONRSPAUTHPASSWORD;
	task.task_id = sessionID;
	task.task_int = errorCode;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradingDate(unsigned int sessionID, int errorCode, TapAPITradingCalendarQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGDATE;
	task.task_id = sessionID;
	task.task_int = errorCode;
	if (info)
	{
		TapAPITradingCalendarQryRsp *task_data = new TapAPITradingCalendarQryRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspSetReservedInfo(unsigned int sessionID, int errorCode, string info)
{
	Task task = Task();
	task.task_name = ONRSPSETRESERVEDINFO;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_string = info;
	this->task_queue.push(task);
};

void TdApi::OnRspQryAccount(unsigned int sessionID, unsigned int errorCode, char isLast, TapAPIAccountInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYACCOUNT;
	task.task_id = sessionID;
	task.task_id = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIAccountInfo *task_data = new TapAPIAccountInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryFund(unsigned int sessionID, int errorCode, char isLast, TapAPIFundData *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYFUND;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIFundData *task_data = new TapAPIFundData();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnFund(TapAPIFundData *info)
{
	Task task = Task();
	task.task_name = ONRTNFUND;
	if (info)
	{
		TapAPIFundData *task_data = new TapAPIFundData();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryExchange(unsigned int sessionID, int errorCode, char isLast, TapAPIExchangeInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGE;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIExchangeInfo *task_data = new TapAPIExchangeInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryCommodity(unsigned int sessionID, int errorCode, char isLast, TapAPICommodityInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYCOMMODITY;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPICommodityInfo *task_data = new TapAPICommodityInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryContract(unsigned int sessionID, int errorCode, char isLast, TapAPITradeContractInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYCONTRACT;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPITradeContractInfo *task_data = new TapAPITradeContractInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnContract(TapAPITradeContractInfo *info)
{
	Task task = Task();
	task.task_name = ONRTNCONTRACT;
	if (info)
	{
		TapAPITradeContractInfo *task_data = new TapAPITradeContractInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderAction(unsigned int sessionID, int errorCode, TapAPIOrderActionRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPORDERACTION;
	task.task_id = sessionID;
	task.task_int = errorCode;
	if (info)
	{
		TapAPIOrderActionRsp *task_data = new TapAPIOrderActionRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnOrder(TapAPIOrderInfoNotice *info)
{
	Task task = Task();
	task.task_name = ONRTNORDER;
	if (info)
	{
		TapAPIOrderInfoNotice *task_data = new TapAPIOrderInfoNotice();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryOrder(unsigned int sessionID, int errorCode, char isLast, TapAPIOrderInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIOrderInfo *task_data = new TapAPIOrderInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryOrderProcess(unsigned int sessionID, int errorCode, char isLast, TapAPIOrderInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYORDERPROCESS;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIOrderInfo *task_data = new TapAPIOrderInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryFill(unsigned int sessionID, int errorCode, char isLast, TapAPIFillInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYFILL;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIFillInfo *task_data = new TapAPIFillInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnFill(TapAPIFillInfo *info)
{
	Task task = Task();
	task.task_name = ONRTNFILL;
	if (info)
	{
		TapAPIFillInfo *task_data = new TapAPIFillInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryPosition(unsigned int sessionID, int errorCode, char isLast, TapAPIPositionInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYPOSITION;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIPositionInfo *task_data = new TapAPIPositionInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnPosition(TapAPIPositionInfo *info)
{
	Task task = Task();
	task.task_name = ONRTNPOSITION;
	if (info)
	{
		TapAPIPositionInfo *task_data = new TapAPIPositionInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryPositionSummary(unsigned int sessionID, int errorCode, char isLast, TapAPIPositionSummary *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYPOSITIONSUMMARY;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIPositionSummary *task_data = new TapAPIPositionSummary();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnPositionSummary(TapAPIPositionSummary *info)
{
	Task task = Task();
	task.task_name = ONRTNPOSITIONSUMMARY;
	if (info)
	{
		TapAPIPositionSummary *task_data = new TapAPIPositionSummary();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnPositionProfit(TapAPIPositionProfitNotice *info)
{
	Task task = Task();
	task.task_name = ONRTNPOSITIONPROFIT;
	if (info)
	{
		TapAPIPositionProfitNotice *task_data = new TapAPIPositionProfitNotice();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryCurrency(unsigned int sessionID, int errorCode, char isLast, TapAPICurrencyInfo *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYCURRENCY;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPICurrencyInfo *task_data = new TapAPICurrencyInfo();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradeMessage(unsigned int sessionID, int errorCode, char isLast, TapAPITradeMessage *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADEMESSAGE;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPITradeMessage *task_data = new TapAPITradeMessage();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnTradeMessage(TapAPITradeMessage *info)
{
	Task task = Task();
	task.task_name = ONRTNTRADEMESSAGE;
	if (info)
	{
		TapAPITradeMessage *task_data = new TapAPITradeMessage();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryHisOrder(unsigned int sessionID, int errorCode, char isLast, TapAPIHisOrderQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISORDER;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIHisOrderQryRsp *task_data = new TapAPIHisOrderQryRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryHisOrderProcess(unsigned int sessionID, int errorCode, char isLast, TapAPIHisOrderProcessQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISORDERPROCESS;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIHisOrderProcessQryRsp *task_data = new TapAPIHisOrderProcessQryRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryHisMatch(unsigned int sessionID, int errorCode, char isLast, TapAPIHisMatchQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISMATCH;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIHisMatchQryRsp *task_data = new TapAPIHisMatchQryRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryHisPosition(unsigned int sessionID, int errorCode, char isLast, TapAPIHisPositionQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISPOSITION;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIHisPositionQryRsp *task_data = new TapAPIHisPositionQryRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryHisDelivery(unsigned int sessionID, int errorCode, char isLast, TapAPIHisDeliveryQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISDELIVERY;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIHisDeliveryQryRsp *task_data = new TapAPIHisDeliveryQryRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryAccountCashAdjust(unsigned int sessionID, int errorCode, char isLast, TapAPIAccountCashAdjustQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYACCOUNTCASHADJUST;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIAccountCashAdjustQryRsp *task_data = new TapAPIAccountCashAdjustQryRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryBill(unsigned int sessionID, int errorCode, char isLast, TapAPIBillQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYBILL;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIBillQryRsp *task_data = new TapAPIBillQryRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryAccountFeeRent(unsigned int sessionID, int errorCode, char isLast, TapAPIAccountFeeRentQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYACCOUNTFEERENT;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIAccountFeeRentQryRsp *task_data = new TapAPIAccountFeeRentQryRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryAccountMarginRent(unsigned int sessionID, int errorCode, char isLast, TapAPIAccountMarginRentQryRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPQRYACCOUNTMARGINRENT;
	task.task_id = sessionID;
	task.task_int = errorCode;
	task.task_last = isLast;
	if (info)
	{
		TapAPIAccountMarginRentQryRsp *task_data = new TapAPIAccountMarginRentQryRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspHKMarketOrderInsert(unsigned int sessionID, int errorCode, TapAPIOrderMarketInsertRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPHKMARKETORDERINSERT;
	task.task_id = sessionID;
	task.task_int = errorCode;
	if (info)
	{
		TapAPIOrderMarketInsertRsp *task_data = new TapAPIOrderMarketInsertRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspHKMarketOrderDelete(unsigned int sessionID, int errorCode, TapAPIOrderMarketDeleteRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPHKMARKETORDERDELETE;
	task.task_id = sessionID;
	task.task_int = errorCode;
	if (info)
	{
		TapAPIOrderMarketDeleteRsp *task_data = new TapAPIOrderMarketDeleteRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnHKMarketQuoteNotice(TapAPIOrderQuoteMarketNotice *info)
{
	Task task = Task();
	task.task_name = ONHKMARKETQUOTENOTICE;
	if (info)
	{
		TapAPIOrderQuoteMarketNotice *task_data = new TapAPIOrderQuoteMarketNotice();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderLocalRemove(unsigned int sessionID, int errorCode, TapAPIOrderLocalRemoveRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPORDERLOCALREMOVE;
	task.task_id = sessionID;
	task.task_int = errorCode;
	if (info)
	{
		TapAPIOrderLocalRemoveRsp *task_data = new TapAPIOrderLocalRemoveRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderLocalInput(unsigned int sessionID, int errorCode, TapAPIOrderLocalInputRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPORDERLOCALINPUT;
	task.task_id = sessionID;
	task.task_int = errorCode;
	if (info)
	{
		TapAPIOrderLocalInputRsp *task_data = new TapAPIOrderLocalInputRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderLocalModify(unsigned int sessionID, int errorCode, TapAPIOrderLocalModifyRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPORDERLOCALMODIFY;
	task.task_id = sessionID;
	task.task_int = errorCode;
	if (info)
	{
		TapAPIOrderLocalModifyRsp *task_data = new TapAPIOrderLocalModifyRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderLocalTransfer(unsigned int sessionID, int errorCode, TapAPIOrderLocalTransferRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPORDERLOCALTRANSFER;
	task.task_id = sessionID;
	task.task_int = errorCode;
	if (info)
	{
		TapAPIOrderLocalTransferRsp *task_data = new TapAPIOrderLocalTransferRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspFillLocalInput(unsigned int sessionID, int errorCode, TapAPIFillLocalInputRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPFILLLOCALINPUT;
	task.task_id = sessionID;
	task.task_int = errorCode;
	if (info)
	{
		TapAPIFillLocalInputRsp *task_data = new TapAPIFillLocalInputRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspFillLocalRemove(unsigned int sessionID, int errorCode, TapAPIFillLocalRemoveRsp *info)
{
	Task task = Task();
	task.task_name = ONRSPFILLLOCALREMOVE;
	task.task_id = sessionID;
	task.task_int = errorCode;
	if (info)
	{
		TapAPIFillLocalRemoveRsp *task_data = new TapAPIFillLocalRemoveRsp();
		*task_data = *info;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

