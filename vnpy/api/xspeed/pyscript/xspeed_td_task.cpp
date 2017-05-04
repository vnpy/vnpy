void TdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void TdApi::OnFrontDisconnected(int nReason)
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;
	task.task_id = nReason;
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogin(struct DFITCUserLoginInfoRtnField * pUserLoginInfoRtn, struct DFITCErrorRtnField * pErrorInfo)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;

	if (pUserLoginInfoRtn)
	{
		task.task_data = *pUserLoginInfoRtn;
	}
	else
	{
		DFITCUserLoginInfoRtnField empty_data = DFITCUserLoginInfoRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspUserLogout(struct DFITCUserLogoutInfoRtnField * pUserLogoutInfoRtn, struct DFITCErrorRtnField * pErrorInfo)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;

	if (pUserLogoutInfoRtn)
	{
		task.task_data = *pUserLogoutInfoRtn;
	}
	else
	{
		DFITCUserLogoutInfoRtnField empty_data = DFITCUserLogoutInfoRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspInsertOrder(struct DFITCOrderRspDataRtnField * pOrderRtn, struct DFITCErrorRtnField * pErrorInfo)
{
	Task task = Task();
	task.task_name = ONRSPINSERTORDER;

	if (pOrderRtn)
	{
		task.task_data = *pOrderRtn;
	}
	else
	{
		DFITCOrderRspDataRtnField empty_data = DFITCOrderRspDataRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspCancelOrder(struct DFITCOrderRspDataRtnField * pOrderCanceledRtn, struct DFITCErrorRtnField * pErrorInfo)
{
	Task task = Task();
	task.task_name = ONRSPCANCELORDER;

	if (pOrderCanceledRtn)
	{
		task.task_data = *pOrderCanceledRtn;
	}
	else
	{
		DFITCOrderRspDataRtnField empty_data = DFITCOrderRspDataRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnErrorMsg(struct DFITCErrorRtnField * pErrorInfo)
{
	Task task = Task();
	task.task_name = ONRTNERRORMSG;

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnMatchedInfo(struct DFITCMatchRtnField * pRtnMatchData)
{
	Task task = Task();
	task.task_name = ONRTNMATCHEDINFO;

	if (pRtnMatchData)
	{
		task.task_data = *pRtnMatchData;
	}
	else
	{
		DFITCMatchRtnField empty_data = DFITCMatchRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnOrder(struct DFITCOrderRtnField * pRtnOrderData)
{
	Task task = Task();
	task.task_name = ONRTNORDER;

	if (pRtnOrderData)
	{
		task.task_data = *pRtnOrderData;
	}
	else
	{
		DFITCOrderRtnField empty_data = DFITCOrderRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnCancelOrder(struct DFITCOrderCanceledRtnField * pCancelOrderData)
{
	Task task = Task();
	task.task_name = ONRTNCANCELORDER;

	if (pCancelOrderData)
	{
		task.task_data = *pCancelOrderData;
	}
	else
	{
		DFITCOrderCanceledRtnField empty_data = DFITCOrderCanceledRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryOrderInfo(struct DFITCOrderCommRtnField * pRtnOrderData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYORDERINFO;

	if (pRtnOrderData)
	{
		task.task_data = *pRtnOrderData;
	}
	else
	{
		DFITCOrderCommRtnField empty_data = DFITCOrderCommRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryMatchInfo(struct DFITCMatchedRtnField * pRtnMatchData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYMATCHINFO;

	if (pRtnMatchData)
	{
		task.task_data = *pRtnMatchData;
	}
	else
	{
		DFITCMatchedRtnField empty_data = DFITCMatchedRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryPosition(struct DFITCPositionInfoRtnField * pPositionInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYPOSITION;

	if (pPositionInfoRtn)
	{
		task.task_data = *pPositionInfoRtn;
	}
	else
	{
		DFITCPositionInfoRtnField empty_data = DFITCPositionInfoRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspCustomerCapital(struct DFITCCapitalInfoRtnField * pCapitalInfoRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPCUSTOMERCAPITAL;

	if (pCapitalInfoRtn)
	{
		task.task_data = *pCapitalInfoRtn;
	}
	else
	{
		DFITCCapitalInfoRtnField empty_data = DFITCCapitalInfoRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryExchangeInstrument(struct DFITCExchangeInstrumentRtnField * pInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGEINSTRUMENT;

	if (pInstrumentData)
	{
		task.task_data = *pInstrumentData;
	}
	else
	{
		DFITCExchangeInstrumentRtnField empty_data = DFITCExchangeInstrumentRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspArbitrageInstrument(struct DFITCAbiInstrumentRtnField * pAbiInstrumentData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPARBITRAGEINSTRUMENT;

	if (pAbiInstrumentData)
	{
		task.task_data = *pAbiInstrumentData;
	}
	else
	{
		DFITCAbiInstrumentRtnField empty_data = DFITCAbiInstrumentRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQrySpecifyInstrument(struct DFITCInstrumentRtnField * pInstrument, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYSPECIFYINSTRUMENT;

	if (pInstrument)
	{
		task.task_data = *pInstrument;
	}
	else
	{
		DFITCInstrumentRtnField empty_data = DFITCInstrumentRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryPositionDetail(struct DFITCPositionDetailRtnField * pPositionDetailRtn, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYPOSITIONDETAIL;

	if (pPositionDetailRtn)
	{
		task.task_data = *pPositionDetailRtn;
	}
	else
	{
		DFITCPositionDetailRtnField empty_data = DFITCPositionDetailRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRtnTradingNotice(struct DFITCTradingNoticeInfoField * pTradingNoticeInfo)
{
	Task task = Task();
	task.task_name = ONRTNTRADINGNOTICE;

	if (pTradingNoticeInfo)
	{
		task.task_data = *pTradingNoticeInfo;
	}
	else
	{
		DFITCTradingNoticeInfoField empty_data = DFITCTradingNoticeInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspResetPassword(struct DFITCResetPwdRspField * pResetPassword, struct DFITCErrorRtnField * pErrorInfo)
{
	Task task = Task();
	task.task_name = ONRSPRESETPASSWORD;

	if (pResetPassword)
	{
		task.task_data = *pResetPassword;
	}
	else
	{
		DFITCResetPwdRspField empty_data = DFITCResetPwdRspField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryTradeCode(struct DFITCQryTradeCodeRtnField * pTradeCode, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADECODE;

	if (pTradeCode)
	{
		task.task_data = *pTradeCode;
	}
	else
	{
		DFITCQryTradeCodeRtnField empty_data = DFITCQryTradeCodeRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspBillConfirm(struct DFITCBillConfirmRspField * pBillConfirm, struct DFITCErrorRtnField * pErrorInfo)
{
	Task task = Task();
	task.task_name = ONRSPBILLCONFIRM;

	if (pBillConfirm)
	{
		task.task_data = *pBillConfirm;
	}
	else
	{
		DFITCBillConfirmRspField empty_data = DFITCBillConfirmRspField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspEquityComputMode(struct DFITCEquityComputModeRtnField * pEquityComputMode)
{
	Task task = Task();
	task.task_name = ONRSPEQUITYCOMPUTMODE;

	if (pEquityComputMode)
	{
		task.task_data = *pEquityComputMode;
	}
	else
	{
		DFITCEquityComputModeRtnField empty_data = DFITCEquityComputModeRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryBill(struct DFITCQryBillRtnField * pQryBill, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYBILL;

	if (pQryBill)
	{
		task.task_data = *pQryBill;
	}
	else
	{
		DFITCQryBillRtnField empty_data = DFITCQryBillRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspConfirmProductInfo(struct DFITCProductRtnField * pProductRtnData)
{
	Task task = Task();
	task.task_name = ONRSPCONFIRMPRODUCTINFO;

	if (pProductRtnData)
	{
		task.task_data = *pProductRtnData;
	}
	else
	{
		DFITCProductRtnField empty_data = DFITCProductRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspTradingDay(struct DFITCTradingDayRtnField * pTradingDayRtnData)
{
	Task task = Task();
	task.task_name = ONRSPTRADINGDAY;

	if (pTradingDayRtnData)
	{
		task.task_data = *pTradingDayRtnData;
	}
	else
	{
		DFITCTradingDayRtnField empty_data = DFITCTradingDayRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQuoteInsert(struct DFITCQuoteRspField * pRspQuoteData, struct DFITCErrorRtnField * pErrorInfo) 
{
	Task task = Task();
	task.task_name = ONRSPQUOTEINSERT;

	if (pRspQuoteData)
	{
		task.task_data = *pRspQuoteData;
	}
	else
	{
		DFITCQuoteRspField empty_data = DFITCQuoteRspField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnQuoteInsert(struct DFITCQuoteRtnField * pRtnQuoteData)
{
	Task task = Task();
	task.task_name = ONRTNQUOTEINSERT;

	if (pRtnQuoteData)
	{
		task.task_data = *pRtnQuoteData;
	}
	else
	{
		DFITCQuoteRtnField empty_data = DFITCQuoteRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQuoteCancel(struct DFITCQuoteRspField * pRspQuoteCanceledData,struct DFITCErrorRtnField * pErrorInfo)  
{
	Task task = Task();
	task.task_name = ONRSPQUOTECANCEL;

	if (pRspQuoteCanceledData,struct)
	{
		task.task_data = *pRspQuoteCanceledData,struct;
	}
	else
	{
		DFITCQuoteRspField empty_data = DFITCQuoteRspField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnQuoteCancel(struct DFITCQuoteCanceledRtnField * pRtnQuoteCanceledData)    
{
	Task task = Task();
	task.task_name = ONRTNQUOTECANCEL;

	if (pRtnQuoteCanceledData)
	{
		task.task_data = *pRtnQuoteCanceledData;
	}
	else
	{
		DFITCQuoteCanceledRtnField empty_data = DFITCQuoteCanceledRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnQuoteMatchedInfo(struct DFITCQuoteMatchRtnField * pRtnQuoteMatchedData) 
{
	Task task = Task();
	task.task_name = ONRTNQUOTEMATCHEDINFO;

	if (pRtnQuoteMatchedData)
	{
		task.task_data = *pRtnQuoteMatchedData;
	}
	else
	{
		DFITCQuoteMatchRtnField empty_data = DFITCQuoteMatchRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspCancelAllOrder(struct DFITCCancelAllOrderRspField * pRspCancelAllOrderData, struct DFITCErrorRtnField * pErrorInfo)
{
	Task task = Task();
	task.task_name = ONRSPCANCELALLORDER;

	if (pRspCancelAllOrderData)
	{
		task.task_data = *pRspCancelAllOrderData;
	}
	else
	{
		DFITCCancelAllOrderRspField empty_data = DFITCCancelAllOrderRspField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryQuoteNotice(struct DFITCQryQuoteNoticeRtnField * pRtnQryQuoteNoticeData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYQUOTENOTICE;

	if (pRtnQryQuoteNoticeData)
	{
		task.task_data = *pRtnQryQuoteNoticeData;
	}
	else
	{
		DFITCQryQuoteNoticeRtnField empty_data = DFITCQryQuoteNoticeRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspForQuote(struct DFITCForQuoteRspField * pRspForQuoteData, struct DFITCErrorRtnField * pErrorInfo)
{
	Task task = Task();
	task.task_name = ONRSPFORQUOTE;

	if (pRspForQuoteData)
	{
		task.task_data = *pRspForQuoteData;
	}
	else
	{
		DFITCForQuoteRspField empty_data = DFITCForQuoteRspField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnForQuote(struct DFITCForQuoteRtnField * pRtnForQuoteData)
{
	Task task = Task();
	task.task_name = ONRTNFORQUOTE;

	if (pRtnForQuoteData)
	{
		task.task_data = *pRtnForQuoteData;
	}
	else
	{
		DFITCForQuoteRtnField empty_data = DFITCForQuoteRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryQuoteOrderInfo(struct DFITCQuoteOrderRtnField * pRtnQuoteOrderData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYQUOTEORDERINFO;

	if (pRtnQuoteOrderData)
	{
		task.task_data = *pRtnQuoteOrderData;
	}
	else
	{
		DFITCQuoteOrderRtnField empty_data = DFITCQuoteOrderRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryForQuote(struct DFITCQryForQuoteRtnField * pRtnQryForQuoteData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYFORQUOTE;

	if (pRtnQryForQuoteData)
	{
		task.task_data = *pRtnQryForQuoteData;
	}
	else
	{
		DFITCQryForQuoteRtnField empty_data = DFITCQryForQuoteRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTransferBank(struct DFITCTransferBankRspField * pTransferBank, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTRANSFERBANK;

	if (pTransferBank)
	{
		task.task_data = *pTransferBank;
	}
	else
	{
		DFITCTransferBankRspField empty_data = DFITCTransferBankRspField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspQryTransferSerial(struct DFITCTransferSerialRspField * pTransferSerial, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast) 
{
	Task task = Task();
	task.task_name = ONRSPQRYTRANSFERSERIAL;

	if (pTransferSerial)
	{
		task.task_data = *pTransferSerial;
	}
	else
	{
		DFITCTransferSerialRspField empty_data = DFITCTransferSerialRspField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFromBankToFutureByFuture(struct DFITCTransferRspField * pRspTransfer, struct DFITCErrorRtnField * pErrorInfo) 
{
	Task task = Task();
	task.task_name = ONRSPFROMBANKTOFUTUREBYFUTURE;

	if (pRspTransfer)
	{
		task.task_data = *pRspTransfer;
	}
	else
	{
		DFITCTransferRspField empty_data = DFITCTransferRspField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspFromFutureToBankByFuture(struct DFITCTransferRspField * pRspTransfer, struct DFITCErrorRtnField * pErrorInfo) 
{
	Task task = Task();
	task.task_name = ONRSPFROMFUTURETOBANKBYFUTURE;

	if (pRspTransfer)
	{
		task.task_data = *pRspTransfer;
	}
	else
	{
		DFITCTransferRspField empty_data = DFITCTransferRspField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnFromBankToFutureByFuture(struct DFITCTransferRtnField * pRtnTransfer, struct DFITCErrorRtnField * pErrorInfo) 
{
	Task task = Task();
	task.task_name = ONRTNFROMBANKTOFUTUREBYFUTURE;

	if (pRtnTransfer)
	{
		task.task_data = *pRtnTransfer;
	}
	else
	{
		DFITCTransferRtnField empty_data = DFITCTransferRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnFromFutureToBankByFuture(struct DFITCTransferRtnField * pRtnTransfer, struct DFITCErrorRtnField * pErrorInfo) 
{
	Task task = Task();
	task.task_name = ONRTNFROMFUTURETOBANKBYFUTURE;

	if (pRtnTransfer)
	{
		task.task_data = *pRtnTransfer;
	}
	else
	{
		DFITCTransferRtnField empty_data = DFITCTransferRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnRepealFromFutureToBankByBank(struct DFITCRepealRtnField * pRspRepeal) 
{
	Task task = Task();
	task.task_name = ONRTNREPEALFROMFUTURETOBANKBYBANK;

	if (pRspRepeal)
	{
		task.task_data = *pRspRepeal;
	}
	else
	{
		DFITCRepealRtnField empty_data = DFITCRepealRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryExchangeStatus(struct DFITCExchangeStatusRspField * pRspExchangeStatusData)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGESTATUS;

	if (pRspExchangeStatusData)
	{
		task.task_data = *pRspExchangeStatusData;
	}
	else
	{
		DFITCExchangeStatusRspField empty_data = DFITCExchangeStatusRspField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnExchangeStatus(struct DFITCExchangeStatusRtnField * pRtnExchangeStatusData)
{
	Task task = Task();
	task.task_name = ONRTNEXCHANGESTATUS;

	if (pRtnExchangeStatusData)
	{
		task.task_data = *pRtnExchangeStatusData;
	}
	else
	{
		DFITCExchangeStatusRtnField empty_data = DFITCExchangeStatusRtnField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspQryDepthMarketData(struct DFITCDepthMarketDataField * pDepthMarketData, struct DFITCErrorRtnField * pErrorInfo, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYDEPTHMARKETDATA;

	if (pDepthMarketData)
	{
		task.task_data = *pDepthMarketData;
	}
	else
	{
		DFITCDepthMarketDataField empty_data = DFITCDepthMarketDataField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pErrorInfo)
	{
		task.task_error = *pErrorInfo;
	}
	else
	{
		DFITCErrorRtnField empty_error = DFITCErrorRtnField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

