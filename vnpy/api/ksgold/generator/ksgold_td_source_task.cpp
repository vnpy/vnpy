void TdApi::OnFrontConnected(int nResult) 
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	task.task_id = nResult;
	this->task_queue.push(task);
};

void TdApi::OnFrontDisconnected(int nReason) 
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;
	task.task_id = nReason;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
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

void TdApi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
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

void TdApi::OnNtyMktStatus(CThostFtdcMarketStatusField *pfldMktStatus)
{
	Task task = Task();
	task.task_name = ONNTYMKTSTATUS;
	if (pfldMktStatus)
	{
		CThostFtdcMarketStatusField *task_data = new CThostFtdcMarketStatusField();
		*task_data = *pfldMktStatus;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
	Task task = Task();
	task.task_name = ONRTNINSTRUMENTSTATUS;
	if (pInstrumentStatus)
	{
		CThostFtdcInstrumentStatusField *task_data = new CThostFtdcInstrumentStatusField();
		*task_data = *pInstrumentStatus;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENT;
	if (pInstrument)
	{
		CThostFtdcInstrumentField *task_data = new CThostFtdcInstrumentField();
		*task_data = *pInstrument;
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

void TdApi::OnRspReqQryVarietyCode(CThostFtdcRspVarietyCodeField *pVarietyCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPREQQRYVARIETYCODE;
	if (pVarietyCode)
	{
		CThostFtdcRspVarietyCodeField *task_data = new CThostFtdcRspVarietyCodeField();
		*task_data = *pVarietyCode;
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

void TdApi::OnRspOrderInsert(CThostFtdcRspInputOrderField *pRspInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPORDERINSERT;
	if (pRspInputOrder)
	{
		CThostFtdcRspInputOrderField *task_data = new CThostFtdcRspInputOrderField();
		*task_data = *pRspInputOrder;
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

void TdApi::OnRspETFSubscriptionOrderInsert(CThostFtdcETFTradeDetailField *pETFSubscriptionOrderInsert, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPETFSUBSCRIPTIONORDERINSERT;
	if (pETFSubscriptionOrderInsert)
	{
		CThostFtdcETFTradeDetailField *task_data = new CThostFtdcETFTradeDetailField();
		*task_data = *pETFSubscriptionOrderInsert;
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

void TdApi::OnRspETFPurchaseOrderInsert(CThostFtdcETFTradeDetailField *pETFSubscriptionOrderInsert, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPETFPURCHASEORDERINSERT;
	if (pETFSubscriptionOrderInsert)
	{
		CThostFtdcETFTradeDetailField *task_data = new CThostFtdcETFTradeDetailField();
		*task_data = *pETFSubscriptionOrderInsert;
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

void TdApi::OnRspETFRedeemInsert(CThostFtdcETFTradeDetailField *pETFSubscriptionOrderInsert, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPETFREDEEMINSERT;
	if (pETFSubscriptionOrderInsert)
	{
		CThostFtdcETFTradeDetailField *task_data = new CThostFtdcETFTradeDetailField();
		*task_data = *pETFSubscriptionOrderInsert;
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

void TdApi::OnRspETFAccountBinding(CThostFtdcETFBindingStatusField *pETFAccountBinding, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPETFACCOUNTBINDING;
	if (pETFAccountBinding)
	{
		CThostFtdcETFBindingStatusField *task_data = new CThostFtdcETFBindingStatusField();
		*task_data = *pETFAccountBinding;
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

void TdApi::OnRspETFAccountUnbinding(CThostFtdcETFBindingStatusField *pETFAccountUnbinding, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPETFACCOUNTUNBINDING;
	if (pETFAccountUnbinding)
	{
		CThostFtdcETFBindingStatusField *task_data = new CThostFtdcETFBindingStatusField();
		*task_data = *pETFAccountUnbinding;
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

void TdApi::OnRtnOrder(CThostFtdcOrderField *pOrder) 
{
	Task task = Task();
	task.task_name = ONRTNORDER;
	if (pOrder)
	{
		CThostFtdcOrderField *task_data = new CThostFtdcOrderField();
		*task_data = *pOrder;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnForceLogout(CThostFtdcUserLogoutField *pLogout) 
{
	Task task = Task();
	task.task_name = ONFORCELOGOUT;
	if (pLogout)
	{
		CThostFtdcUserLogoutField *task_data = new CThostFtdcUserLogoutField();
		*task_data = *pLogout;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnETFAccountBindingStatus(CThostFtdcETFBindingStatusField * pETFBindgingStatus) 
{
	Task task = Task();
	task.task_name = ONRTNETFACCOUNTBINDINGSTATUS;
	if ()
	{
		CThostFtdcETFBindingStatusField *task_data = new CThostFtdcETFBindingStatusField();
		*task_data = *;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnETFOrder(CThostFtdcETFTradeDetailField *pEtfTradeDetail)
{
	Task task = Task();
	task.task_name = ONRTNETFORDER;
	if (pEtfTradeDetail)
	{
		CThostFtdcETFTradeDetailField *task_data = new CThostFtdcETFTradeDetailField();
		*task_data = *pEtfTradeDetail;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspOrderAction(CThostFtdcRspInputOrderActionField *pRspInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPORDERACTION;
	if (pRspInputOrderAction)
	{
		CThostFtdcRspInputOrderActionField *task_data = new CThostFtdcRspInputOrderActionField();
		*task_data = *pRspInputOrderAction;
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

void TdApi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
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

void TdApi::OnRtnTrade(CThostFtdcTradeField *pTrade) 
{
	Task task = Task();
	task.task_name = ONRTNTRADE;
	if (pTrade)
	{
		CThostFtdcTradeField *task_data = new CThostFtdcTradeField();
		*task_data = *pTrade;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGACCOUNT;
	if (pTradingAccount)
	{
		CThostFtdcTradingAccountField *task_data = new CThostFtdcTradingAccountField();
		*task_data = *pTradingAccount;
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

void TdApi::OnRspQryHisCapital(CThostFtdcRspHisCapitalField *pHisCapital, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYHISCAPITAL;
	if (pHisCapital)
	{
		CThostFtdcRspHisCapitalField *task_data = new CThostFtdcRspHisCapitalField();
		*task_data = *pHisCapital;
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

void TdApi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;
	if (pOrder)
	{
		CThostFtdcOrderField *task_data = new CThostFtdcOrderField();
		*task_data = *pOrder;
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

void TdApi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADE;
	if (pTrade)
	{
		CThostFtdcTradeField *task_data = new CThostFtdcTradeField();
		*task_data = *pTrade;
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

void TdApi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITION;
	if (pInvestorPosition)
	{
		CThostFtdcInvestorPositionField *task_data = new CThostFtdcInvestorPositionField();
		*task_data = *pInvestorPosition;
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

void TdApi::OnRspQryClientStorage(CThostFtdcStorageField *pStorage, CThostFtdcRspInfoField *pRspInfo,int nRequestID,bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCLIENTSTORAGE;
	if (pStorage)
	{
		CThostFtdcStorageField *task_data = new CThostFtdcStorageField();
		*task_data = *pStorage;
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

void TdApi::OnRspQryCostMarginFeeRate(CThostFtdcRspCostMarginFeeField *pCostMarginFee, CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCOSTMARGINFEERATE;
	if (pCostMarginFee)
	{
		CThostFtdcRspCostMarginFeeField *task_data = new CThostFtdcRspCostMarginFeeField();
		*task_data = *pCostMarginFee;
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

void TdApi::OnRspConditionOrderInsert(CThostFtdcRspConditionOrderField *pConditionOrder, CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPCONDITIONORDERINSERT;
	if (pConditionOrder)
	{
		CThostFtdcRspConditionOrderField *task_data = new CThostFtdcRspConditionOrderField();
		*task_data = *pConditionOrder;
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

void TdApi::OnRspConditionOrderAction(CThostFtdcRspConditionActionOrderField *pConditionActionOrder, CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPCONDITIONORDERACTION;
	if (pConditionActionOrder)
	{
		CThostFtdcRspConditionActionOrderField *task_data = new CThostFtdcRspConditionActionOrderField();
		*task_data = *pConditionActionOrder;
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

void TdApi::OnRspQryConditionOrder(CThostFtdcRspConditionOrderQryField *pConditionOrderQry, CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCONDITIONORDER;
	if (pConditionOrderQry)
	{
		CThostFtdcRspConditionOrderQryField *task_data = new CThostFtdcRspConditionOrderQryField();
		*task_data = *pConditionOrderQry;
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

void TdApi::OnRspQryConditionOrderTrade(CThostFtdcRspConditionOrderMatchField *pConditionOrderMatch, CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCONDITIONORDERTRADE;
	if (pConditionOrderMatch)
	{
		CThostFtdcRspConditionOrderMatchField *task_data = new CThostFtdcRspConditionOrderMatchField();
		*task_data = *pConditionOrderMatch;
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

void TdApi::OnRspQryClientSessionInfo(CThostFtdcRspClientSessionField *pClientSessionField, CThostFtdcRspInfoField *pRspInfo,int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCLIENTSESSIONINFO;
	if (pClientSessionField)
	{
		CThostFtdcRspClientSessionField *task_data = new CThostFtdcRspClientSessionField();
		*task_data = *pClientSessionField;
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

void TdApi::OnRspQryQuotation(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYQUOTATION;
	if (pDepthMarketData)
	{
		CThostFtdcDepthMarketDataField *task_data = new CThostFtdcDepthMarketDataField();
		*task_data = *pDepthMarketData;
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

void TdApi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITIONDETAIL;
	if (pInvestorPositionDetail)
	{
		CThostFtdcInvestorPositionDetailField *task_data = new CThostFtdcInvestorPositionDetailField();
		*task_data = *pInvestorPositionDetail;
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

void TdApi::OnRspQryETFradeDetail(CThostFtdcETFTradeDetailField *pQryETFTradeDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYETFRADEDETAIL;
	if (pQryETFTradeDetail)
	{
		CThostFtdcETFTradeDetailField *task_data = new CThostFtdcETFTradeDetailField();
		*task_data = *pQryETFTradeDetail;
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

void TdApi::OnRspQryETFPcfDetail(CThostFtdcETFPcfDetailField *pQryETFpcfDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYETFPCFDETAIL;
	if (pQryETFpcfDetail)
	{
		CThostFtdcETFPcfDetailField *task_data = new CThostFtdcETFPcfDetailField();
		*task_data = *pQryETFpcfDetail;
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

void TdApi::OnRspModifyPassword(CThostFtdcModifyPasswordRsqField *pRsqModifyPassword,CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPMODIFYPASSWORD;
	if (pRsqModifyPassword)
	{
		CThostFtdcModifyPasswordRsqField *task_data = new CThostFtdcModifyPasswordRsqField();
		*task_data = *pRsqModifyPassword;
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

void TdApi::OnRspB0CMoneyIO(CThostFtdcBOCMoneyIORspField *pRspBOCMoneyIO,CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPB0CMONEYIO;
	if (pRspBOCMoneyIO)
	{
		CThostFtdcBOCMoneyIORspField *task_data = new CThostFtdcBOCMoneyIORspField();
		*task_data = *pRspBOCMoneyIO;
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

