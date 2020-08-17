    void TdApi::OnConnect(string UserNo)
{
	Task task = Task();
	task.task_name = ONCONNECT;
	task.task_string = UserNo;
	this->task_queue.push(task);
};

    void TdApi::OnRspLogin(string UserNo, int nErrorCode, TapAPITradeLoginRspInfo *pLoginRspInfo)
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

    void TdApi::OnRtnContactInfo(string UserNo, int nErrorCode, char isLast, TapAPISecondInfo* pInfo)
{
	Task task = Task();
	task.task_name = ONRTNCONTACTINFO;
	task.task_string = UserNo;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPISecondInfo *task_data = new TapAPISecondInfo();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspRequestVertificateCode(string UserNo, unsigned int nSessionID, int nErrorCode, char isLast, TapAPIVertificateCode *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPREQUESTVERTIFICATECODE;
	task.task_string = UserNo;
	task.task_id = nSessionID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPIVertificateCode *task_data = new TapAPIVertificateCode();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRtnErrorMsg(string UserNo, string ErrorMsg)
{
	Task task = Task();
	task.task_name = ONRTNERRORMSG;
	task.task_string = UserNo;
	task.task_string = ErrorMsg;
	this->task_queue.push(task);
};

    void TdApi::OnAPIReady(string UserNo)
{
	Task task = Task();
	task.task_name = ONAPIREADY;
	task.task_string = UserNo;
	this->task_queue.push(task);
};

    void TdApi::OnDisconnect(string UserNo, int nReasonCode)
{
	Task task = Task();
	task.task_name = ONDISCONNECT;
	task.task_string = UserNo;
	task.task_int = nReasonCode;
	this->task_queue.push(task);
};

    void TdApi::OnRspSubmitUserLoginInfo(string UserNo, unsigned int nSessionID, TapAPISubmitUserLoginInfoRsp *pRspInfo)
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

    void TdApi::OnRspChangePassword(string UserNo, unsigned int nSessionID, int nErrorCode)
{
	Task task = Task();
	task.task_name = ONRSPCHANGEPASSWORD;
	task.task_string = UserNo;
	task.task_id = nSessionID;
	task.task_int = nErrorCode;
	this->task_queue.push(task);
};

    void TdApi::OnRspSetReservedInfo(string UserNo, unsigned int nSessionID, int nErrorCode, string info)
{
	Task task = Task();
	task.task_name = ONRSPSETRESERVEDINFO;
	task.task_string = UserNo;
	task.task_id = nSessionID;
	task.task_int = nErrorCode;
	task.task_string = info;
	this->task_queue.push(task);
};

    void TdApi::OnRtnContract(string UserNo, TapAPITradeContractInfo *pRtnInfo)
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

    void TdApi::OnRtnFund(string UserNo, TapAPIFundData *pRtnInfo)
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

    void TdApi::OnRtnOrder(string UserNo, unsigned int nRequestID, TapAPIOrderInfo *pRtnInfo)
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

    void TdApi::OnRspQryOrderProcess(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIOrderInfo *pRspInfo)
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

    void TdApi::OnRtnFill(string UserNo, TapAPIFillInfo *pRtnInfo)
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

    void TdApi::OnRtnPosition(string UserNo, TapAPIPositionInfo *pRtnInfo)
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

    void TdApi::OnRtnClose(string UserNo, TapAPICloseInfo *pRtnInfo)
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

    void TdApi::OnRtnPositionProfit(string UserNo, TapAPIPositionProfitNotice *pRtnInfo)
{
	Task task = Task();
	task.task_name = ONRTNPOSITIONPROFIT;
	task.task_string = UserNo;
	if (pRtnInfo)
	{
		TapAPIPositionProfitNotice *task_data = new TapAPIPositionProfitNotice();
		*task_data = *pRtnInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspQryDeepQuote(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIDeepQuoteQryRsp *pRspInfo)
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

    void TdApi::OnRtnExchangeStateInfo(string UserNo, TapAPIExchangeStateInfoNotice *pRtnInfo)
{
	Task task = Task();
	task.task_name = ONRTNEXCHANGESTATEINFO;
	task.task_string = UserNo;
	if (pRtnInfo)
	{
		TapAPIExchangeStateInfoNotice *task_data = new TapAPIExchangeStateInfoNotice();
		*task_data = *pRtnInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRtnReqQuoteNotice(string UserNo, TapAPIReqQuoteNotice *pRtnInfo)
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

    void TdApi::OnRspAccountRentInfo(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIAccountRentInfo *pRspInfo)
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

    void TdApi::OnRspTradeMessage(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPITradeMessage *pRspInfo)
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

    void TdApi::OnRtnTradeMessage(string UserNo, TapAPITradeMessage *pRtnInfo)
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

    void TdApi::OnRspQryHisOrder(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIHisOrderQryRsp *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISORDER;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPIHisOrderQryRsp *task_data = new TapAPIHisOrderQryRsp();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspQryHisOrderProcess(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIHisOrderProcessQryRsp *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISORDERPROCESS;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPIHisOrderProcessQryRsp *task_data = new TapAPIHisOrderProcessQryRsp();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspQryHisFill(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIHisFillQryRsp *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISFILL;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPIHisFillQryRsp *task_data = new TapAPIHisFillQryRsp();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspQryHisPosition(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIHisPositionQryRsp *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISPOSITION;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPIHisPositionQryRsp *task_data = new TapAPIHisPositionQryRsp();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspQryHisDelivery(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIHisDeliveryQryRsp *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISDELIVERY;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPIHisDeliveryQryRsp *task_data = new TapAPIHisDeliveryQryRsp();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspQryAccountCashAdjust(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIAccountCashAdjustQryRsp *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPQRYACCOUNTCASHADJUST;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPIAccountCashAdjustQryRsp *task_data = new TapAPIAccountCashAdjustQryRsp();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspQryBill(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIBillQryRsp *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPQRYBILL;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPIBillQryRsp *task_data = new TapAPIBillQryRsp();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspAccountFeeRent(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIAccountFeeRentQryRsp *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPACCOUNTFEERENT;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPIAccountFeeRentQryRsp *task_data = new TapAPIAccountFeeRentQryRsp();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspAccountMarginRent(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIAccountMarginRentQryRsp *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPACCOUNTMARGINRENT;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPIAccountMarginRentQryRsp *task_data = new TapAPIAccountMarginRentQryRsp();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspAddMobileDevice(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIMobileDeviceAddRsp *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPADDMOBILEDEVICE;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPIMobileDeviceAddRsp *task_data = new TapAPIMobileDeviceAddRsp();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspQryManageInfoForEStar(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPIManageInfo *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPQRYMANAGEINFOFORESTAR;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPIManageInfo *task_data = new TapAPIManageInfo();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspQrySystemParameter(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPISystemParameterInfo *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPQRYSYSTEMPARAMETER;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPISystemParameterInfo *task_data = new TapAPISystemParameterInfo();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRspQryTradeCenterFrontAddress(string UserNo, unsigned int nRequestID, int nErrorCode, char isLast, TapAPITradeCenterFrontAddressInfo *pInfo)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADECENTERFRONTADDRESS;
	task.task_string = UserNo;
	task.task_id = nRequestID;
	task.task_int = nErrorCode;
	task.task_last = isLast;
	if (pInfo)
	{
		TapAPITradeCenterFrontAddressInfo *task_data = new TapAPITradeCenterFrontAddressInfo();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRtnCommodityInfo(string UserNo, TapAPICommodityInfo *pInfo)
{
	Task task = Task();
	task.task_name = ONRTNCOMMODITYINFO;
	task.task_string = UserNo;
	if (pInfo)
	{
		TapAPICommodityInfo *task_data = new TapAPICommodityInfo();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

    void TdApi::OnRtnCurrencyInfo(string UserNo, TapAPICurrencyInfo *pInfo)
{
	Task task = Task();
	task.task_name = ONRTNCURRENCYINFO;
	task.task_string = UserNo;
	if (pInfo)
	{
		TapAPICurrencyInfo *task_data = new TapAPICurrencyInfo();
		*task_data = *pInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

