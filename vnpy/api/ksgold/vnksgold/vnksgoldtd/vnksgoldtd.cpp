// vnuftmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnksgoldtd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------
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
	if (pETFBindgingStatus)
	{
		CThostFtdcETFBindingStatusField *task_data = new CThostFtdcETFBindingStatusField();
		*task_data = *pETFBindgingStatus;
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

void TdApi::OnRspQryClientStorage(CThostFtdcStorageField *pStorage, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void TdApi::OnRspQryCostMarginFeeRate(CThostFtdcRspCostMarginFeeField *pCostMarginFee, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void TdApi::OnRspConditionOrderInsert(CThostFtdcRspConditionOrderField *pConditionOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void TdApi::OnRspConditionOrderAction(CThostFtdcRspConditionActionOrderField *pConditionActionOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void TdApi::OnRspQryConditionOrder(CThostFtdcRspConditionOrderQryField *pConditionOrderQry, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void TdApi::OnRspQryConditionOrderTrade(CThostFtdcRspConditionOrderMatchField *pConditionOrderMatch, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void TdApi::OnRspQryClientSessionInfo(CThostFtdcRspClientSessionField *pClientSessionField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void TdApi::OnRspModifyPassword(CThostFtdcModifyPasswordRsqField *pRsqModifyPassword, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void TdApi::OnRspB0CMoneyIO(CThostFtdcBOCMoneyIORspField *pRspBOCMoneyIO, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

			case ONFRONTDISCONNECTED:
			{
				this->processFrontDisconnected(&task);
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

			case ONNTYMKTSTATUS:
			{
				this->processNtyMktStatus(&task);
				break;
			}

			case ONRTNINSTRUMENTSTATUS:
			{
				this->processRtnInstrumentStatus(&task);
				break;
			}

			case ONRSPQRYINSTRUMENT:
			{
				this->processRspQryInstrument(&task);
				break;
			}

			case ONRSPREQQRYVARIETYCODE:
			{
				this->processRspReqQryVarietyCode(&task);
				break;
			}

			case ONRSPORDERINSERT:
			{
				this->processRspOrderInsert(&task);
				break;
			}

			case ONRSPETFSUBSCRIPTIONORDERINSERT:
			{
				this->processRspETFSubscriptionOrderInsert(&task);
				break;
			}

			case ONRSPETFPURCHASEORDERINSERT:
			{
				this->processRspETFPurchaseOrderInsert(&task);
				break;
			}

			case ONRSPETFREDEEMINSERT:
			{
				this->processRspETFRedeemInsert(&task);
				break;
			}

			case ONRSPETFACCOUNTBINDING:
			{
				this->processRspETFAccountBinding(&task);
				break;
			}

			case ONRSPETFACCOUNTUNBINDING:
			{
				this->processRspETFAccountUnbinding(&task);
				break;
			}

			case ONRTNORDER:
			{
				this->processRtnOrder(&task);
				break;
			}

			case ONFORCELOGOUT:
			{
				this->processForceLogout(&task);
				break;
			}

			case ONRTNETFACCOUNTBINDINGSTATUS:
			{
				this->processRtnETFAccountBindingStatus(&task);
				break;
			}

			case ONRTNETFORDER:
			{
				this->processRtnETFOrder(&task);
				break;
			}

			case ONRSPORDERACTION:
			{
				this->processRspOrderAction(&task);
				break;
			}

			case ONRSPERROR:
			{
				this->processRspError(&task);
				break;
			}

			case ONRTNTRADE:
			{
				this->processRtnTrade(&task);
				break;
			}

			case ONRSPQRYTRADINGACCOUNT:
			{
				this->processRspQryTradingAccount(&task);
				break;
			}

			case ONRSPQRYHISCAPITAL:
			{
				this->processRspQryHisCapital(&task);
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

			case ONRSPQRYCLIENTSTORAGE:
			{
				this->processRspQryClientStorage(&task);
				break;
			}

			case ONRSPQRYCOSTMARGINFEERATE:
			{
				this->processRspQryCostMarginFeeRate(&task);
				break;
			}

			case ONRSPCONDITIONORDERINSERT:
			{
				this->processRspConditionOrderInsert(&task);
				break;
			}

			case ONRSPCONDITIONORDERACTION:
			{
				this->processRspConditionOrderAction(&task);
				break;
			}

			case ONRSPQRYCONDITIONORDER:
			{
				this->processRspQryConditionOrder(&task);
				break;
			}

			case ONRSPQRYCONDITIONORDERTRADE:
			{
				this->processRspQryConditionOrderTrade(&task);
				break;
			}

			case ONRSPQRYCLIENTSESSIONINFO:
			{
				this->processRspQryClientSessionInfo(&task);
				break;
			}

			case ONRSPQRYQUOTATION:
			{
				this->processRspQryQuotation(&task);
				break;
			}

			case ONRSPQRYINVESTORPOSITIONDETAIL:
			{
				this->processRspQryInvestorPositionDetail(&task);
				break;
			}

			case ONRSPQRYETFRADEDETAIL:
			{
				this->processRspQryETFradeDetail(&task);
				break;
			}

			case ONRSPQRYETFPCFDETAIL:
			{
				this->processRspQryETFPcfDetail(&task);
				break;
			}

			case ONRSPMODIFYPASSWORD:
			{
				this->processRspModifyPassword(&task);
				break;
			}

			case ONRSPB0CMONEYIO:
			{
				this->processRspB0CMoneyIO(&task);
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
	gil_scoped_acquire acquire;
	this->onFrontConnected(task->task_id);
};

void TdApi::processFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisconnected(task->task_id);
};

void TdApi::processRspUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspUserLoginField *task_data = (CThostFtdcRspUserLoginField*)task->task_data;
		data["TradeDate"] = toUtf(task_data->TradeDate);
		data["SessionID"] = task_data->SessionID;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["clientName"] = toUtf(task_data->clientName);
		data["TradeCode"] = toUtf(task_data->TradeCode);
		data["SeatNo"] = toUtf(task_data->SeatNo);
		data["lastLoginIp"] = toUtf(task_data->lastLoginIp);
		data["lastLoginDate"] = toUtf(task_data->lastLoginDate);
		data["lastLoginTime"] = toUtf(task_data->lastLoginTime);
		data["AccountID"] = toUtf(task_data->AccountID);
		data["LoginType"] = task_data->LoginType;
		data["Password"] = toUtf(task_data->Password);
		data["MacAddress"] = toUtf(task_data->MacAddress);
		data["LoginIp"] = toUtf(task_data->LoginIp);
		data["UserProductionInfo"] = toUtf(task_data->UserProductionInfo);
		data["ProtocolInfo"] = toUtf(task_data->ProtocolInfo);
		data["SystemName"] = toUtf(task_data->SystemName);
		data["FrontID"] = task_data->FrontID;
		data["MaxOrderRef"] = toUtf(task_data->MaxOrderRef);
		data["SgeTime"] = toUtf(task_data->SgeTime);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserLogin(data, error, task->task_id, task->task_last);
};

void TdApi::processRspUserLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcUserLogoutField *task_data = (CThostFtdcUserLogoutField*)task->task_data;
		data["LoginIp"] = toUtf(task_data->LoginIp);
		data["MacAddress"] = toUtf(task_data->MacAddress);
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspUserLogout(data, error, task->task_id, task->task_last);
};

void TdApi::processNtyMktStatus(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcMarketStatusField *task_data = (CThostFtdcMarketStatusField*)task->task_data;
		data["MktStatus"] = toUtf(task_data->MktStatus);
		data["marketID"] = toUtf(task_data->marketID);
		data["ExchCode"] = toUtf(task_data->ExchCode);
		delete task_data;
	}
	this->onNtyMktStatus(data);
};

void TdApi::processRtnInstrumentStatus(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcInstrumentStatusField *task_data = (CThostFtdcInstrumentStatusField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstrumentID"] = toUtf(task_data->InstrumentID);
		data["InstrumentStatus"] = task_data->InstrumentStatus;
		delete task_data;
	}
	this->onRtnInstrumentStatus(data);
};

void TdApi::processRspQryInstrument(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcInstrumentField *task_data = (CThostFtdcInstrumentField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["InstID"] = toUtf(task_data->InstID);
		data["LowerLimit"] = task_data->LowerLimit;
		data["MarketID"] = toUtf(task_data->MarketID);
		data["MaxHand"] = task_data->MaxHand;
		data["MinHand"] = task_data->MinHand;
		data["Name"] = toUtf(task_data->Name);
		data["OpenFlag"] = task_data->OpenFlag;
		data["Tick"] = task_data->Tick;
		data["TradeState"] = task_data->TradeState;
		data["Unit"] = task_data->Unit;
		data["UpperLimit"] = task_data->UpperLimit;
		data["VarietyID"] = toUtf(task_data->VarietyID);
		data["VarietyType"] = task_data->VarietyType;
		data["MarketType"] = task_data->MarketType;
		data["ProductID"] = toUtf(task_data->ProductID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryInstrument(data, error, task->task_id, task->task_last);
};

void TdApi::processRspReqQryVarietyCode(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspVarietyCodeField *task_data = (CThostFtdcRspVarietyCodeField*)task->task_data;
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["VarietyShortName"] = toUtf(task_data->VarietyShortName);
		data["VarietyFullName"] = toUtf(task_data->VarietyFullName);
		data["VarietyCode"] = toUtf(task_data->VarietyCode);
		data["VarietyType"] = toUtf(task_data->VarietyType);
		data["WeightUnit"] = toUtf(task_data->WeightUnit);
		data["Status"] = task_data->Status;
		data["MinTakeVolumn"] = task_data->MinTakeVolumn;
		data["TakeUnit"] = task_data->TakeUnit;
		data["Weight"] = task_data->Weight;
		data["ProductID"] = toUtf(task_data->ProductID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspReqQryVarietyCode(data, error, task->task_id, task->task_last);
};

void TdApi::processRspOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspInputOrderField *task_data = (CThostFtdcRspInputOrderField*)task->task_data;
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["Status"] = task_data->Status;
		data["SeatID"] = toUtf(task_data->SeatID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["TradeCode"] = toUtf(task_data->TradeCode);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["Amount"] = task_data->Amount;
		data["Price"] = task_data->Price;
		data["MarketID"] = toUtf(task_data->MarketID);
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["SessionID"] = task_data->SessionID;
		data["RequestID"] = task_data->RequestID;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["CmdType"] = toUtf(task_data->CmdType);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspETFSubscriptionOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFTradeDetailField *task_data = (CThostFtdcETFTradeDetailField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["RequestDate"] = toUtf(task_data->RequestDate);
		data["RequestTime"] = toUtf(task_data->RequestTime);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["InstrumentID1"] = toUtf(task_data->InstrumentID1);
		data["weight1"] = task_data->weight1;
		data["InstrumentID2"] = toUtf(task_data->InstrumentID2);
		data["weight2"] = task_data->weight2;
		data["InstrumentID3"] = toUtf(task_data->InstrumentID3);
		data["weight3"] = task_data->weight3;
		data["InstrumentID4"] = toUtf(task_data->InstrumentID4);
		data["weight4"] = task_data->weight4;
		data["InstrumentID5"] = toUtf(task_data->InstrumentID5);
		data["weight5"] = task_data->weight5;
		data["Totalweight"] = task_data->Totalweight;
		data["fundunit"] = task_data->fundunit;
		data["confirmDate"] = toUtf(task_data->confirmDate);
		data["tradestatus"] = toUtf(task_data->tradestatus);
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspETFSubscriptionOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspETFPurchaseOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFTradeDetailField *task_data = (CThostFtdcETFTradeDetailField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["RequestDate"] = toUtf(task_data->RequestDate);
		data["RequestTime"] = toUtf(task_data->RequestTime);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["InstrumentID1"] = toUtf(task_data->InstrumentID1);
		data["weight1"] = task_data->weight1;
		data["InstrumentID2"] = toUtf(task_data->InstrumentID2);
		data["weight2"] = task_data->weight2;
		data["InstrumentID3"] = toUtf(task_data->InstrumentID3);
		data["weight3"] = task_data->weight3;
		data["InstrumentID4"] = toUtf(task_data->InstrumentID4);
		data["weight4"] = task_data->weight4;
		data["InstrumentID5"] = toUtf(task_data->InstrumentID5);
		data["weight5"] = task_data->weight5;
		data["Totalweight"] = task_data->Totalweight;
		data["fundunit"] = task_data->fundunit;
		data["confirmDate"] = toUtf(task_data->confirmDate);
		data["tradestatus"] = toUtf(task_data->tradestatus);
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspETFPurchaseOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspETFRedeemInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFTradeDetailField *task_data = (CThostFtdcETFTradeDetailField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["RequestDate"] = toUtf(task_data->RequestDate);
		data["RequestTime"] = toUtf(task_data->RequestTime);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["InstrumentID1"] = toUtf(task_data->InstrumentID1);
		data["weight1"] = task_data->weight1;
		data["InstrumentID2"] = toUtf(task_data->InstrumentID2);
		data["weight2"] = task_data->weight2;
		data["InstrumentID3"] = toUtf(task_data->InstrumentID3);
		data["weight3"] = task_data->weight3;
		data["InstrumentID4"] = toUtf(task_data->InstrumentID4);
		data["weight4"] = task_data->weight4;
		data["InstrumentID5"] = toUtf(task_data->InstrumentID5);
		data["weight5"] = task_data->weight5;
		data["Totalweight"] = task_data->Totalweight;
		data["fundunit"] = task_data->fundunit;
		data["confirmDate"] = toUtf(task_data->confirmDate);
		data["tradestatus"] = toUtf(task_data->tradestatus);
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspETFRedeemInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspETFAccountBinding(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFBindingStatusField *task_data = (CThostFtdcETFBindingStatusField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["StockTradeCode"] = toUtf(task_data->StockTradeCode);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["BindingStatus"] = toUtf(task_data->BindingStatus);
		data["BindingDate"] = toUtf(task_data->BindingDate);
		data["BindingLocalOrderNo"] = toUtf(task_data->BindingLocalOrderNo);
		data["BindingEtfrevsn"] = toUtf(task_data->BindingEtfrevsn);
		data["UnBindingDate"] = toUtf(task_data->UnBindingDate);
		data["UnBindingLocalOrderNo"] = toUtf(task_data->UnBindingLocalOrderNo);
		data["UnBindingEtfrevsn"] = toUtf(task_data->UnBindingEtfrevsn);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspETFAccountBinding(data, error, task->task_id, task->task_last);
};

void TdApi::processRspETFAccountUnbinding(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFBindingStatusField *task_data = (CThostFtdcETFBindingStatusField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["StockTradeCode"] = toUtf(task_data->StockTradeCode);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["BindingStatus"] = toUtf(task_data->BindingStatus);
		data["BindingDate"] = toUtf(task_data->BindingDate);
		data["BindingLocalOrderNo"] = toUtf(task_data->BindingLocalOrderNo);
		data["BindingEtfrevsn"] = toUtf(task_data->BindingEtfrevsn);
		data["UnBindingDate"] = toUtf(task_data->UnBindingDate);
		data["UnBindingLocalOrderNo"] = toUtf(task_data->UnBindingLocalOrderNo);
		data["UnBindingEtfrevsn"] = toUtf(task_data->UnBindingEtfrevsn);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspETFAccountUnbinding(data, error, task->task_id, task->task_last);
};

void TdApi::processRtnOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcOrderField *task_data = (CThostFtdcOrderField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["MarketID"] = toUtf(task_data->MarketID);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["Amount"] = task_data->Amount;
		data["Price"] = task_data->Price;
		data["MatchQty"] = task_data->MatchQty;
		data["Status"] = task_data->Status;
		data["EntrustTime"] = toUtf(task_data->EntrustTime);
		data["Forceoffset_flag"] = task_data->Forceoffset_flag;
		data["CancelQty"] = task_data->CancelQty;
		data["CancelTime"] = toUtf(task_data->CancelTime);
		data["TradeWay"] = task_data->TradeWay;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["CmdType"] = toUtf(task_data->CmdType);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	this->onRtnOrder(data);
};

void TdApi::processForceLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcUserLogoutField *task_data = (CThostFtdcUserLogoutField*)task->task_data;
		data["LoginIp"] = toUtf(task_data->LoginIp);
		data["MacAddress"] = toUtf(task_data->MacAddress);
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task_data;
	}
	this->onForceLogout(data);
};

void TdApi::processRtnETFAccountBindingStatus(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFBindingStatusField *task_data = (CThostFtdcETFBindingStatusField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["StockTradeCode"] = toUtf(task_data->StockTradeCode);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["BindingStatus"] = toUtf(task_data->BindingStatus);
		data["BindingDate"] = toUtf(task_data->BindingDate);
		data["BindingLocalOrderNo"] = toUtf(task_data->BindingLocalOrderNo);
		data["BindingEtfrevsn"] = toUtf(task_data->BindingEtfrevsn);
		data["UnBindingDate"] = toUtf(task_data->UnBindingDate);
		data["UnBindingLocalOrderNo"] = toUtf(task_data->UnBindingLocalOrderNo);
		data["UnBindingEtfrevsn"] = toUtf(task_data->UnBindingEtfrevsn);
		delete task_data;
	}
	this->onRtnETFAccountBindingStatus(data);
};

void TdApi::processRtnETFOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFTradeDetailField *task_data = (CThostFtdcETFTradeDetailField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["RequestDate"] = toUtf(task_data->RequestDate);
		data["RequestTime"] = toUtf(task_data->RequestTime);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["InstrumentID1"] = toUtf(task_data->InstrumentID1);
		data["weight1"] = task_data->weight1;
		data["InstrumentID2"] = toUtf(task_data->InstrumentID2);
		data["weight2"] = task_data->weight2;
		data["InstrumentID3"] = toUtf(task_data->InstrumentID3);
		data["weight3"] = task_data->weight3;
		data["InstrumentID4"] = toUtf(task_data->InstrumentID4);
		data["weight4"] = task_data->weight4;
		data["InstrumentID5"] = toUtf(task_data->InstrumentID5);
		data["weight5"] = task_data->weight5;
		data["Totalweight"] = task_data->Totalweight;
		data["fundunit"] = task_data->fundunit;
		data["confirmDate"] = toUtf(task_data->confirmDate);
		data["tradestatus"] = toUtf(task_data->tradestatus);
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	this->onRtnETFOrder(data);
};

void TdApi::processRspOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspInputOrderActionField *task_data = (CThostFtdcRspInputOrderActionField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["localOrderNo"] = toUtf(task_data->localOrderNo);
		data["Status"] = task_data->Status;
		data["marketID"] = toUtf(task_data->marketID);
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["SessionID"] = task_data->SessionID;
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspOrderAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspError(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspError(error, task->task_id, task->task_last);
};

void TdApi::processRtnTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcTradeField *task_data = (CThostFtdcTradeField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffSetFlag"] = task_data->OffSetFlag;
		data["Price"] = task_data->Price;
		data["Volume"] = task_data->Volume;
		data["Amount"] = task_data->Amount;
		data["Order_flag"] = task_data->Order_flag;
		data["MatchDate"] = toUtf(task_data->MatchDate);
		data["MatchTime"] = toUtf(task_data->MatchTime);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["MarketID"] = toUtf(task_data->MarketID);
		data["Trade_fee"] = task_data->Trade_fee;
		data["Forceoffset_flag"] = task_data->Forceoffset_flag;
		data["Forcebatchnum"] = task_data->Forcebatchnum;
		data["TradeWay"] = task_data->TradeWay;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		delete task_data;
	}
	this->onRtnTrade(data);
};

void TdApi::processRspQryTradingAccount(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcTradingAccountField *task_data = (CThostFtdcTradingAccountField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["AvailCap"] = task_data->AvailCap;
		data["Available"] = task_data->Available;
		data["PosiMargin"] = task_data->PosiMargin;
		data["BuyPosiMargin"] = task_data->BuyPosiMargin;
		data["SellPosiMargin"] = task_data->SellPosiMargin;
		data["StorageMargin"] = task_data->StorageMargin;
		data["TotalFee"] = task_data->TotalFee;
		data["TotalFrozen"] = task_data->TotalFrozen;
		data["OrderFrozen"] = task_data->OrderFrozen;
		data["SpotSellFrozen"] = task_data->SpotSellFrozen;
		data["TodayIn"] = task_data->TodayIn;
		data["TodayOut"] = task_data->TodayOut;
		data["LastFrozen"] = task_data->LastFrozen;
		data["TotalFrozenFee"] = task_data->TotalFrozenFee;
		data["PickUpMargin"] = task_data->PickUpMargin;
		data["MiddleMargin"] = task_data->MiddleMargin;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryTradingAccount(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryHisCapital(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspHisCapitalField *task_data = (CThostFtdcRspHisCapitalField*)task->task_data;
		data["TradeDate"] = toUtf(task_data->TradeDate);
		data["AvailCap"] = task_data->AvailCap;
		data["Todayprofit"] = task_data->Todayprofit;
		data["PosiMargin"] = task_data->PosiMargin;
		data["PickUpMargin"] = task_data->PickUpMargin;
		data["StorageMargin"] = task_data->StorageMargin;
		data["TradeFee"] = task_data->TradeFee;
		data["TodayInOut"] = task_data->TodayInOut;
		data["EtfTransferFee"] = task_data->EtfTransferFee;
		data["EtfTransferFeeFrzn"] = task_data->EtfTransferFeeFrzn;
		data["EtfCashBalance"] = task_data->EtfCashBalance;
		data["EtfCashBalanceFrzn"] = task_data->EtfCashBalanceFrzn;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryHisCapital(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcOrderField *task_data = (CThostFtdcOrderField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["MarketID"] = toUtf(task_data->MarketID);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["Amount"] = task_data->Amount;
		data["Price"] = task_data->Price;
		data["MatchQty"] = task_data->MatchQty;
		data["Status"] = task_data->Status;
		data["EntrustTime"] = toUtf(task_data->EntrustTime);
		data["Forceoffset_flag"] = task_data->Forceoffset_flag;
		data["CancelQty"] = task_data->CancelQty;
		data["CancelTime"] = toUtf(task_data->CancelTime);
		data["TradeWay"] = task_data->TradeWay;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["CmdType"] = toUtf(task_data->CmdType);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryOrder(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcTradeField *task_data = (CThostFtdcTradeField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffSetFlag"] = task_data->OffSetFlag;
		data["Price"] = task_data->Price;
		data["Volume"] = task_data->Volume;
		data["Amount"] = task_data->Amount;
		data["Order_flag"] = task_data->Order_flag;
		data["MatchDate"] = toUtf(task_data->MatchDate);
		data["MatchTime"] = toUtf(task_data->MatchTime);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["MarketID"] = toUtf(task_data->MarketID);
		data["Trade_fee"] = task_data->Trade_fee;
		data["Forceoffset_flag"] = task_data->Forceoffset_flag;
		data["Forcebatchnum"] = task_data->Forcebatchnum;
		data["TradeWay"] = task_data->TradeWay;
		data["HedgeFlag"] = task_data->HedgeFlag;
		data["SessionID"] = task_data->SessionID;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryTrade(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcInvestorPositionField *task_data = (CThostFtdcInvestorPositionField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["InstID"] = toUtf(task_data->InstID);
		data["MarketID"] = toUtf(task_data->MarketID);
		data["LongPosi"] = task_data->LongPosi;
		data["LongPosiAvgPrice"] = task_data->LongPosiAvgPrice;
		data["ShortPosi"] = task_data->ShortPosi;
		data["ShortPosiAvgPrice"] = task_data->ShortPosiAvgPrice;
		data["LongOpenAvgPrice"] = task_data->LongOpenAvgPrice;
		data["ShortOpenAvgPrice"] = task_data->ShortOpenAvgPrice;
		data["LongPosiFrozen"] = task_data->LongPosiFrozen;
		data["ShortPosiFrozen"] = task_data->ShortPosiFrozen;
		data["LongPosiVol"] = task_data->LongPosiVol;
		data["ShortPosiVol"] = task_data->ShortPosiVol;
		data["TodayLong"] = task_data->TodayLong;
		data["TodayShort"] = task_data->TodayShort;
		data["TodayOffsetShort"] = task_data->TodayOffsetShort;
		data["TodayOffsetLong"] = task_data->TodayOffsetLong;
		data["LastLong"] = task_data->LastLong;
		data["LastShort"] = task_data->LastShort;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryInvestorPosition(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryClientStorage(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcStorageField *task_data = (CThostFtdcStorageField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["VarietyID"] = toUtf(task_data->VarietyID);
		data["totalStorage"] = task_data->totalStorage;
		data["availableStorage"] = task_data->availableStorage;
		data["frozenStorage"] = task_data->frozenStorage;
		data["pendStorage"] = task_data->pendStorage;
		data["todayBuy"] = task_data->todayBuy;
		data["todaySell"] = task_data->todaySell;
		data["todayDeposit"] = task_data->todayDeposit;
		data["todayDraw"] = task_data->todayDraw;
		data["todayBorrow"] = task_data->todayBorrow;
		data["todayLend"] = task_data->todayLend;
		data["impawnStorage"] = task_data->impawnStorage;
		data["lawFrozen"] = task_data->lawFrozen;
		data["bankFrozen"] = task_data->bankFrozen;
		data["customType"] = task_data->customType;
		data["storageCost"] = task_data->storageCost;
		data["impawnFrozen"] = task_data->impawnFrozen;
		data["transFrozen"] = task_data->transFrozen;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryClientStorage(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryCostMarginFeeRate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspCostMarginFeeField *task_data = (CThostFtdcRspCostMarginFeeField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOpenHandFee"] = task_data->BuyOpenHandFee;
		data["BuyOffsetHandFee"] = task_data->BuyOffsetHandFee;
		data["SellOpenHandFee"] = task_data->SellOpenHandFee;
		data["SellOffsetHandFee"] = task_data->SellOffsetHandFee;
		data["BuyMarginFee"] = task_data->BuyMarginFee;
		data["SellMarginFee"] = task_data->SellMarginFee;
		data["SeatBuyMarginFee"] = task_data->SeatBuyMarginFee;
		data["SeatSellMarginFee"] = task_data->SeatSellMarginFee;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryCostMarginFeeRate(data, error, task->task_id, task->task_last);
};

void TdApi::processRspConditionOrderInsert(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspConditionOrderField *task_data = (CThostFtdcRspConditionOrderField*)task->task_data;
		data["SeatID"] = toUtf(task_data->SeatID);
		data["ClientID"] = toUtf(task_data->ClientID);
		data["TradeCode"] = toUtf(task_data->TradeCode);
		data["ExchangeID"] = toUtf(task_data->ExchangeID);
		data["ConditionOrderNo"] = toUtf(task_data->ConditionOrderNo);
		data["EntrustDate"] = toUtf(task_data->EntrustDate);
		data["TradeDate"] = toUtf(task_data->TradeDate);
		data["EntrustTime"] = toUtf(task_data->EntrustTime);
		data["Status"] = task_data->Status;
		data["MarketID"] = toUtf(task_data->MarketID);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffsetFlag"] = task_data->OffsetFlag;
		data["Amount"] = task_data->Amount;
		data["OrderType"] = task_data->OrderType;
		data["MiddleFlag"] = task_data->MiddleFlag;
		data["PriceFlag"] = task_data->PriceFlag;
		data["Price"] = task_data->Price;
		data["TrigPrice"] = task_data->TrigPrice;
		data["ValidDay"] = task_data->ValidDay;
		data["VolumnCheck"] = task_data->VolumnCheck;
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["SessionID"] = task_data->SessionID;
		data["CmdType"] = toUtf(task_data->CmdType);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspConditionOrderInsert(data, error, task->task_id, task->task_last);
};

void TdApi::processRspConditionOrderAction(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspConditionActionOrderField *task_data = (CThostFtdcRspConditionActionOrderField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["ConditionOrderNo"] = toUtf(task_data->ConditionOrderNo);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspConditionOrderAction(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryConditionOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspConditionOrderQryField *task_data = (CThostFtdcRspConditionOrderQryField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["StartDate"] = toUtf(task_data->StartDate);
		data["EndDate"] = toUtf(task_data->EndDate);
		data["ConditionOrderNo"] = toUtf(task_data->ConditionOrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["OrderType"] = task_data->OrderType;
		data["EntrustTypeName"] = toUtf(task_data->EntrustTypeName);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffSetFlag"] = task_data->OffSetFlag;
		data["Status"] = task_data->Status;
		data["Amount"] = task_data->Amount;
		data["Price"] = task_data->Price;
		data["TriggerPrice"] = task_data->TriggerPrice;
		data["EntrustTime"] = toUtf(task_data->EntrustTime);
		data["TriggerTime"] = toUtf(task_data->TriggerTime);
		data["ReasonDesc"] = toUtf(task_data->ReasonDesc);
		data["EntrustDate"] = toUtf(task_data->EntrustDate);
		data["ExpireDate"] = toUtf(task_data->ExpireDate);
		data["TriggerDate"] = toUtf(task_data->TriggerDate);
		data["OrderRef"] = toUtf(task_data->OrderRef);
		data["SessionID"] = task_data->SessionID;
		data["CmdType"] = toUtf(task_data->CmdType);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryConditionOrder(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryConditionOrderTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspConditionOrderMatchField *task_data = (CThostFtdcRspConditionOrderMatchField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		data["ConditionOrderNo"] = toUtf(task_data->ConditionOrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["EntrustType"] = task_data->EntrustType;
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["OffSetFlag"] = task_data->OffSetFlag;
		data["Amount"] = task_data->Amount;
		data["Price"] = task_data->Price;
		data["MatchVolumn"] = task_data->MatchVolumn;
		data["MatchPrice"] = task_data->MatchPrice;
		data["MatchTime"] = toUtf(task_data->MatchTime);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryConditionOrderTrade(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryClientSessionInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcRspClientSessionField *task_data = (CThostFtdcRspClientSessionField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["SessionID"] = task_data->SessionID;
		data["IdDiffCode"] = toUtf(task_data->IdDiffCode);
		data["CurLoginIp"] = toUtf(task_data->CurLoginIp);
		data["CurMacAddress"] = toUtf(task_data->CurMacAddress);
		data["Status"] = toUtf(task_data->Status);
		data["LoginTime"] = toUtf(task_data->LoginTime);
		data["LoginDate"] = toUtf(task_data->LoginDate);
		data["LogoutTime"] = toUtf(task_data->LogoutTime);
		data["LogoutDate"] = toUtf(task_data->LogoutDate);
		data["FailNumber"] = task_data->FailNumber;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryClientSessionInfo(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryQuotation(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcDepthMarketDataField *task_data = (CThostFtdcDepthMarketDataField*)task->task_data;
		data["InstID"] = toUtf(task_data->InstID);
		data["Name"] = toUtf(task_data->Name);
		data["MarketName"] = toUtf(task_data->MarketName);
		data["PreSettle"] = task_data->PreSettle;
		data["PreClose"] = task_data->PreClose;
		data["Open"] = task_data->Open;
		data["High"] = task_data->High;
		data["Low"] = task_data->Low;
		data["Last"] = task_data->Last;
		data["Close"] = task_data->Close;
		data["Bid1"] = task_data->Bid1;
		data["BidLot1"] = task_data->BidLot1;
		data["Ask1"] = task_data->Ask1;
		data["AskLot1"] = task_data->AskLot1;
		data["Bid2"] = task_data->Bid2;
		data["BidLot2"] = task_data->BidLot2;
		data["Ask2"] = task_data->Ask2;
		data["AskLot2"] = task_data->AskLot2;
		data["Bid3"] = task_data->Bid3;
		data["BidLot3"] = task_data->BidLot3;
		data["Ask3"] = task_data->Ask3;
		data["AskLot3"] = task_data->AskLot3;
		data["Bid4"] = task_data->Bid4;
		data["BidLot4"] = task_data->BidLot4;
		data["Ask4"] = task_data->Ask4;
		data["AskLot4"] = task_data->AskLot4;
		data["Bid5"] = task_data->Bid5;
		data["BidLot5"] = task_data->BidLot5;
		data["Ask5"] = task_data->Ask5;
		data["AskLot5"] = task_data->AskLot5;
		data["Bid6"] = task_data->Bid6;
		data["BidLot6"] = task_data->BidLot6;
		data["Ask6"] = task_data->Ask6;
		data["AskLot6"] = task_data->AskLot6;
		data["Bid7"] = task_data->Bid7;
		data["BidLot7"] = task_data->BidLot7;
		data["Ask7"] = task_data->Ask7;
		data["AskLot7"] = task_data->AskLot7;
		data["Bid8"] = task_data->Bid8;
		data["BidLot8"] = task_data->BidLot8;
		data["Ask8"] = task_data->Ask8;
		data["AskLot8"] = task_data->AskLot8;
		data["Bid9"] = task_data->Bid9;
		data["BidLot9"] = task_data->BidLot9;
		data["Ask9"] = task_data->Ask9;
		data["AskLot9"] = task_data->AskLot9;
		data["Bid10"] = task_data->Bid10;
		data["BidLot10"] = task_data->BidLot10;
		data["Ask10"] = task_data->Ask10;
		data["AskLot10"] = task_data->AskLot10;
		data["Volume"] = task_data->Volume;
		data["OpenInt"] = task_data->OpenInt;
		data["UpDown"] = task_data->UpDown;
		data["Turnover"] = task_data->Turnover;
		data["Settle"] = task_data->Settle;
		data["Average"] = task_data->Average;
		data["QuoteDate"] = toUtf(task_data->QuoteDate);
		data["QuoteTime"] = toUtf(task_data->QuoteTime);
		data["weight"] = task_data->weight;
		data["highLimit"] = task_data->highLimit;
		data["lowLimit"] = task_data->lowLimit;
		data["UpDownRate"] = task_data->UpDownRate;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryQuotation(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryInvestorPositionDetail(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcInvestorPositionDetailField *task_data = (CThostFtdcInvestorPositionDetailField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["ClientShortName"] = toUtf(task_data->ClientShortName);
		data["Data"] = toUtf(task_data->Data);
		data["InstID"] = toUtf(task_data->InstID);
		data["BuyOrSell"] = task_data->BuyOrSell;
		data["Volumn"] = task_data->Volumn;
		data["Settle"] = task_data->Settle;
		data["OpenFlagData"] = toUtf(task_data->OpenFlagData);
		data["MatchNo"] = toUtf(task_data->MatchNo);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryInvestorPositionDetail(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryETFradeDetail(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFTradeDetailField *task_data = (CThostFtdcETFTradeDetailField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		data["OrderNo"] = toUtf(task_data->OrderNo);
		data["LocalOrderNo"] = toUtf(task_data->LocalOrderNo);
		data["RequestDate"] = toUtf(task_data->RequestDate);
		data["RequestTime"] = toUtf(task_data->RequestTime);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["InstrumentID1"] = toUtf(task_data->InstrumentID1);
		data["weight1"] = task_data->weight1;
		data["InstrumentID2"] = toUtf(task_data->InstrumentID2);
		data["weight2"] = task_data->weight2;
		data["InstrumentID3"] = toUtf(task_data->InstrumentID3);
		data["weight3"] = task_data->weight3;
		data["InstrumentID4"] = toUtf(task_data->InstrumentID4);
		data["weight4"] = task_data->weight4;
		data["InstrumentID5"] = toUtf(task_data->InstrumentID5);
		data["weight5"] = task_data->weight5;
		data["Totalweight"] = task_data->Totalweight;
		data["fundunit"] = task_data->fundunit;
		data["confirmDate"] = toUtf(task_data->confirmDate);
		data["tradestatus"] = toUtf(task_data->tradestatus);
		data["ErrorMsg"] = toUtf(task_data->ErrorMsg);
		data["RequestID"] = task_data->RequestID;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryETFradeDetail(data, error, task->task_id, task->task_last);
};

void TdApi::processRspQryETFPcfDetail(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcETFPcfDetailField *task_data = (CThostFtdcETFPcfDetailField*)task->task_data;
		data["TradeDate"] = toUtf(task_data->TradeDate);
		data["EtfCode"] = toUtf(task_data->EtfCode);
		data["InstrumentID1"] = toUtf(task_data->InstrumentID1);
		data["TMoneydiff1"] = task_data->TMoneydiff1;
		data["TPreMoneydiff1"] = task_data->TPreMoneydiff1;
		data["InstrumentID2"] = toUtf(task_data->InstrumentID2);
		data["TMoneydiff2"] = task_data->TMoneydiff2;
		data["TPreMoneydiff2"] = task_data->TPreMoneydiff2;
		data["InstrumentID3"] = toUtf(task_data->InstrumentID3);
		data["TMoneydiff3"] = task_data->TMoneydiff3;
		data["TPreMoneydiff3"] = task_data->TPreMoneydiff3;
		data["InstrumentID4"] = toUtf(task_data->InstrumentID4);
		data["TMoneydiff4"] = task_data->TMoneydiff4;
		data["TPreMoneydiff4"] = task_data->TPreMoneydiff4;
		data["InstrumentID5"] = toUtf(task_data->InstrumentID5);
		data["TMoneydiff5"] = task_data->TMoneydiff5;
		data["TPreMoneydiff5"] = task_data->TPreMoneydiff5;
		data["minTradeWeight"] = task_data->minTradeWeight;
		data["TodayPurchaseMaxLimit"] = task_data->TodayPurchaseMaxLimit;
		data["TodayRedeemMaxLimit"] = task_data->TodayRedeemMaxLimit;
		data["TodayAllow"] = task_data->TodayAllow;
		data["PreETFWeight"] = task_data->PreETFWeight;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspQryETFPcfDetail(data, error, task->task_id, task->task_last);
};

void TdApi::processRspModifyPassword(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcModifyPasswordRsqField *task_data = (CThostFtdcModifyPasswordRsqField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspModifyPassword(data, error, task->task_id, task->task_last);
};

void TdApi::processRspB0CMoneyIO(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		CThostFtdcBOCMoneyIORspField *task_data = (CThostFtdcBOCMoneyIORspField*)task->task_data;
		data["ClientID"] = toUtf(task_data->ClientID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		CThostFtdcRspInfoField *task_error = (CThostFtdcRspInfoField*)task->task_error;
		error["ErrorID"] = task_error->ErrorID;
		error["ErrorMsg"] = toUtf(task_error->ErrorMsg);
		delete task_error;
	}
	this->onRspB0CMoneyIO(data, error, task->task_id, task->task_last);
};



///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::createGoldTraderApi(string pszFlowPath)
{
	this->api = CKSGoldTraderApi::CreateGoldTraderApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};


void TdApi::release()
{
	this->api->Release();
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

bool TdApi::init()
{
	this->active = true;
	this->task_thread = thread(&TdApi::processTask, this);
	this->api->Init();
};

void TdApi::registerFront(string pszFrontAddress)
{
	this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

void TdApi::subscribePrivateTopic(int nResumeType)
{
	this->api->SubscribePrivateTopic((KS_TE_RESUME_TYPE) nResumeType);
};

void TdApi::subscribePublicTopic(int nResumeType)
{
	this->api->SubscribePublicTopic((KS_TE_RESUME_TYPE) nResumeType);
};


int TdApi::join()
{
	int i = this->api->Join();
	return i;
};

int TdApi::reqUserLogin(const dict &req, int reqid)
{
	CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "Td AccountID", myreq.AccountID);
	cout << "myreq.AccountID=" << myreq.AccountID << endl;
	getInt(req, "LoginType", &myreq.LoginType);
	cout << "LoginType=" << &myreq.LoginType << endl;

	getString(req, "Password", myreq.Password);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	getString(req, "UserProductionInfo", myreq.UserProductionInfo);
	getString(req, "ProtocolInfo", myreq.ProtocolInfo);
	cout << "&myreq=" << &myreq << endl;
	int i = this->api->ReqUserLogin(&myreq, reqid);
	cout << "TD   reqUserLogin result=" << i << endl;
	return i;
};

int TdApi::reqUserLogout(const dict &req, int reqid)
{
	CThostFtdcUserLogoutField myreq = CThostFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqUserLogout(&myreq, reqid);
	return i;
};

int TdApi::reqQryInstrument(const dict &req, int reqid)
{
	CThostFtdcQryInstrumentField myreq = CThostFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "ContractID", myreq.ContractID);
	getString(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInstrument(&myreq, reqid);
	return i;
};

int TdApi::reqQryVarietyCode(const dict &req, int reqid)
{
	CThostFtdcQryVarietyCodeField myreq = CThostFtdcQryVarietyCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "VarietyID", myreq.VarietyID);
	getString(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryVarietyCode(&myreq, reqid);
	return i;
};

int TdApi::reqOrderInsert(const dict &req, int reqid)
{
	CThostFtdcInputOrderField myreq = CThostFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "SeatID", myreq.SeatID);
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "TradeCode", myreq.TradeCode);
	getString(req, "InstID", myreq.InstID);
	getUnsignedChar(req, "BuyOrSell", &myreq.BuyOrSell);
	getUnsignedChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getInt(req, "Amount", &myreq.Amount);
	getDouble(req, "Price", &myreq.Price);
	getString(req, "MarketID", myreq.MarketID);
	getString(req, "OrderRef", myreq.OrderRef);
	getInt(req, "SessionID", &myreq.SessionID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getString(req, "CmdType", myreq.CmdType);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqOrderInsert(&myreq, reqid);
	return i;
};

int TdApi::reqOrderAction(const dict &req, int reqid)
{
	CThostFtdcInputOrderActionField myreq = CThostFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "LocalOrderNo", myreq.LocalOrderNo);
	getString(req, "MarketID", myreq.MarketID);
	getString(req, "OrderRef", myreq.OrderRef);
	getInt(req, "SessionID", &myreq.SessionID);
	getInt(req, "RequestID", &myreq.RequestID);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqOrderAction(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorPosition(const dict &req, int reqid)
{
	CThostFtdcQryInvestorPositionField myreq = CThostFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "MarketID", myreq.MarketID);
	getString(req, "InstID", myreq.InstID);
	int i = this->api->ReqQryInvestorPosition(&myreq, reqid);
	return i;
};

int TdApi::reqQryTradingAccount(const dict &req, int reqid)
{
	CThostFtdcQryTradingAccountField myreq = CThostFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryTradingAccount(&myreq, reqid);
	return i;
};

int TdApi::reqQryTrade(const dict &req, int reqid)
{
	CThostFtdcQryTradeField myreq = CThostFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "MarketID", myreq.MarketID);
	getString(req, "InstID", myreq.InstID);
	getString(req, "LocalOrderNo", myreq.LocalOrderNo);
	int i = this->api->ReqQryTrade(&myreq, reqid);
	return i;
};

int TdApi::reqQryOrder(const dict &req, int reqid)
{
	CThostFtdcQryOrderField myreq = CThostFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "MarketID", myreq.MarketID);
	getString(req, "LocalOrderNo", myreq.LocalOrderNo);
	getString(req, "InstID", myreq.InstID);
	getChar(req, "HedgeFlag", &myreq.HedgeFlag);
	getString(req, "CmdType", myreq.CmdType);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "OrderRef", myreq.OrderRef);
	int i = this->api->ReqQryOrder(&myreq, reqid);
	return i;
};

int TdApi::reqQryStorage(const dict &req, int reqid)
{
	CThostFtdcQryStorageField myreq = CThostFtdcQryStorageField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "VarietyID", myreq.VarietyID);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryStorage(&myreq, reqid);
	return i;
};

int TdApi::reqQryCostMarginFeeRate(const dict &req, int reqid)
{
	CThostFtdcQryCostMarginFeeField myreq = CThostFtdcQryCostMarginFeeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "InstID", myreq.InstID);
	int i = this->api->ReqQryCostMarginFeeRate(&myreq, reqid);
	return i;
};

int TdApi::reqConditionOrderInsert(const dict &req, int reqid)
{
	CThostFtdcConditionOrderField myreq = CThostFtdcConditionOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ExchangeID", myreq.ExchangeID);
	getString(req, "SeatID", myreq.SeatID);
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "TradeCode", myreq.TradeCode);
	getString(req, "MarketID", myreq.MarketID);
	getString(req, "InstID", myreq.InstID);
	getUnsignedChar(req, "BuyOrSell", &myreq.BuyOrSell);
	getUnsignedChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getInt(req, "Amount", &myreq.Amount);
	getUnsignedChar(req, "OrderType", &myreq.OrderType);
	getUnsignedChar(req, "MiddleFlag", &myreq.MiddleFlag);
	getUnsignedChar(req, "PriceFlag", &myreq.PriceFlag);
	getDouble(req, "Price", &myreq.Price);
	getDouble(req, "TrigPrice", &myreq.TrigPrice);
	getInt(req, "ValidDay", &myreq.ValidDay);
	getInt(req, "VolumnCheck", &myreq.VolumnCheck);
	getString(req, "OrderRef", myreq.OrderRef);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "CmdType", myreq.CmdType);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqConditionOrderInsert(&myreq, reqid);
	return i;
};

int TdApi::reqConditionOrderAction(const dict &req, int reqid)
{
	CThostFtdcConditionActionOrderField myreq = CThostFtdcConditionActionOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "ConditionOrderNo", myreq.ConditionOrderNo);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqConditionOrderAction(&myreq, reqid);
	return i;
};

int TdApi::reqQryConditionOrder(const dict &req, int reqid)
{
	CThostFtdcConditionOrderQryField myreq = CThostFtdcConditionOrderQryField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "ConditionOrderNo", myreq.ConditionOrderNo);
	getUnsignedChar(req, "Status", &myreq.Status);
	getString(req, "InstID", myreq.InstID);
	getString(req, "StartDate", myreq.StartDate);
	getString(req, "EndDate", myreq.EndDate);
	getString(req, "OrderRef", myreq.OrderRef);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "CmdType", myreq.CmdType);
	int i = this->api->ReqQryConditionOrder(&myreq, reqid);
	return i;
};

int TdApi::reqQryConditionOrderTrade(const dict &req, int reqid)
{
	CThostFtdcConditionOrderMatchField myreq = CThostFtdcConditionOrderMatchField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "InstID", myreq.InstID);
	getString(req, "ConditionOrderNo", myreq.ConditionOrderNo);
	getString(req, "LocalOrderNo", myreq.LocalOrderNo);
	int i = this->api->ReqQryConditionOrderTrade(&myreq, reqid);
	return i;
};

int TdApi::reqQryClientSessionInfo(const dict &req, int reqid)
{
	CThostFtdcQryClientSessionField myreq = CThostFtdcQryClientSessionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryClientSessionInfo(&myreq, reqid);
	return i;
};

int TdApi::reqQryQuotation(const dict &req, int reqid)
{
	CThostFtdcQryQuotationField myreq = CThostFtdcQryQuotationField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "marketID", myreq.marketID);
	getString(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryQuotation(&myreq, reqid);
	return i;
};

int TdApi::reqQryInvestorPositionDetail(const dict &req, int reqid)
{
	CThostFtdcQryInvestorPositionDetailField myreq = CThostFtdcQryInvestorPositionDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "QueryData", myreq.QueryData);
	int i = this->api->ReqQryInvestorPositionDetail(&myreq, reqid);
	return i;
};

int TdApi::reqModifyPassword(const dict &req, int reqid)
{
	CThostFtdcModifyPasswordField myreq = CThostFtdcModifyPasswordField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "OldPassword", myreq.OldPassword);
	getString(req, "NewPassword", myreq.NewPassword);
	int i = this->api->ReqModifyPassword(&myreq, reqid);
	return i;
};

int TdApi::reqQryHisCapital(const dict &req, int reqid)
{
	CThostFtdcQryHisCapitalField myreq = CThostFtdcQryHisCapitalField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "StartDate", myreq.StartDate);
	getString(req, "EndDate", myreq.EndDate);
	int i = this->api->ReqQryHisCapital(&myreq, reqid);
	return i;
};

int TdApi::reqETFSubScription(const dict &req, int reqid)
{
	CThostFtdcSubScriptionField myreq = CThostFtdcSubScriptionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "SeatNo", myreq.SeatNo);
	getString(req, "EtfCode", myreq.EtfCode);
	getString(req, "InstrumentID1", myreq.InstrumentID1);
	getDouble(req, "weight1", &myreq.weight1);
	getString(req, "InstrumentID2", myreq.InstrumentID2);
	getDouble(req, "weight2", &myreq.weight2);
	getString(req, "InstrumentID3", myreq.InstrumentID3);
	getDouble(req, "weight3", &myreq.weight3);
	getString(req, "InstrumentID4", myreq.InstrumentID4);
	getDouble(req, "weight4", &myreq.weight4);
	getString(req, "InstrumentID5", myreq.InstrumentID5);
	getDouble(req, "weight5", &myreq.weight5);
	getDouble(req, "Totalweight", &myreq.Totalweight);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqETFSubScription(&myreq, reqid);
	return i;
};

int TdApi::reqETFApplyForPurchase(const dict &req, int reqid)
{
	CThostFtdcApplyForPurchaseField myreq = CThostFtdcApplyForPurchaseField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "SeatNo", myreq.SeatNo);
	getString(req, "EtfCode", myreq.EtfCode);
	getString(req, "InstrumentID1", myreq.InstrumentID1);
	getDouble(req, "weight1", &myreq.weight1);
	getString(req, "InstrumentID2", myreq.InstrumentID2);
	getDouble(req, "weight2", &myreq.weight2);
	getString(req, "InstrumentID3", myreq.InstrumentID3);
	getDouble(req, "weight3", &myreq.weight3);
	getString(req, "InstrumentID4", myreq.InstrumentID4);
	getDouble(req, "weight4", &myreq.weight4);
	getString(req, "InstrumentID5", myreq.InstrumentID5);
	getDouble(req, "weight5", &myreq.weight5);
	getDouble(req, "Totalweight", &myreq.Totalweight);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqETFApplyForPurchase(&myreq, reqid);
	return i;
};

int TdApi::reqETFRedeem(const dict &req, int reqid)
{
	CThostFtdcRedeemField myreq = CThostFtdcRedeemField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "SeatNo", myreq.SeatNo);
	getString(req, "EtfCode", myreq.EtfCode);
	getInt(req, "SessionID", &myreq.SessionID);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqETFRedeem(&myreq, reqid);
	return i;
};

int TdApi::reqETFAccountBinding(const dict &req, int reqid)
{
	CThostFtdcETFBingingField myreq = CThostFtdcETFBingingField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "StockTradeCode", myreq.StockTradeCode);
	getString(req, "EtfCode", myreq.EtfCode);
	getString(req, "EtfManagedUnit", myreq.EtfManagedUnit);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqETFAccountBinding(&myreq, reqid);
	return i;
};

int TdApi::reqETFAccountUnbinding(const dict &req, int reqid)
{
	CThostFtdcETFUnBingingField myreq = CThostFtdcETFUnBingingField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	getString(req, "StockTradeCode", myreq.StockTradeCode);
	getString(req, "EtfCode", myreq.EtfCode);
	getString(req, "LoginIp", myreq.LoginIp);
	getString(req, "MacAddress", myreq.MacAddress);
	int i = this->api->ReqETFAccountUnbinding(&myreq, reqid);
	return i;
};

int TdApi::reqETFTradeDetail(const dict &req, int reqid)
{
	CThostFtdcQryETFTradeDetailField myreq = CThostFtdcQryETFTradeDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqETFTradeDetail(&myreq, reqid);
	return i;
};

int TdApi::reqETFPcfDetail(const dict &req, int reqid)
{
	CThostFtdcQryETFPcfDetailField myreq = CThostFtdcQryETFPcfDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "StartDate", myreq.StartDate);
	getString(req, "EndDate", myreq.EndDate);
	getString(req, "EtfCode", myreq.EtfCode);
	int i = this->api->ReqETFPcfDetail(&myreq, reqid);
	return i;
};

int TdApi::reqBOCMoneyIO(const dict &req, int reqid)
{
	CThostFtdcBOCMoneyIOField myreq = CThostFtdcBOCMoneyIOField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "TransFerType", myreq.TransFerType);
	getDouble(req, "TransFerAmount", &myreq.TransFerAmount);
	getString(req, "TradePassword", myreq.TradePassword);
	getString(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqBOCMoneyIO(&myreq, reqid);
	return i;
};




///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyTdApi : public TdApi
{
public:
    using TdApi::TdApi;
    
	void onFrontConnected(int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onFrontConnected, reqid);
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
			PYBIND11_OVERLOAD(void, TdApi, onFrontDisconnected, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspUserLogin(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspUserLogin, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspUserLogout(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspUserLogout, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onNtyMktStatus(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onNtyMktStatus, data);
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

	void onRspQryInstrument(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryInstrument, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspReqQryVarietyCode(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspReqQryVarietyCode, data, error, reqid, last);
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
			PYBIND11_OVERLOAD(void, TdApi, onRspOrderInsert, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspETFSubscriptionOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspETFSubscriptionOrderInsert, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspETFPurchaseOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspETFPurchaseOrderInsert, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspETFRedeemInsert(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspETFRedeemInsert, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspETFAccountBinding(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspETFAccountBinding, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspETFAccountUnbinding(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspETFAccountUnbinding, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnOrder(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnOrder, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onForceLogout(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onForceLogout, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnETFAccountBindingStatus(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnETFAccountBindingStatus, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnETFOrder(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnETFOrder, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspOrderAction(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspOrderAction, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspError(const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspError, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRtnTrade(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRtnTrade, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryTradingAccount(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryTradingAccount, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryHisCapital(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryHisCapital, data, error, reqid, last);
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
			PYBIND11_OVERLOAD(void, TdApi, onRspQryOrder, data, error, reqid, last);
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
			PYBIND11_OVERLOAD(void, TdApi, onRspQryTrade, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryInvestorPosition(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryInvestorPosition, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryClientStorage(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryClientStorage, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryCostMarginFeeRate(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryCostMarginFeeRate, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspConditionOrderInsert(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspConditionOrderInsert, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspConditionOrderAction(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspConditionOrderAction, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryConditionOrder(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryConditionOrder, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryConditionOrderTrade(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryConditionOrderTrade, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryClientSessionInfo(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryClientSessionInfo, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryQuotation(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryQuotation, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryInvestorPositionDetail(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryInvestorPositionDetail, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryETFradeDetail(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryETFradeDetail, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspQryETFPcfDetail(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspQryETFPcfDetail, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspModifyPassword(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspModifyPassword, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRspB0CMoneyIO(const dict &data, const dict &error, int reqid, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRspB0CMoneyIO, data, error, reqid, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};



};


PYBIND11_MODULE(vnksgoldtd, m)
{
    class_<TdApi, PyTdApi> TdApi(m, "TdApi", module_local());
	TdApi
		.def(init<>())
		.def("createGoldTraderApi", &TdApi::createGoldTraderApi)
		.def("exit", &TdApi::exit)
		.def("release", &TdApi::release)
		.def("init", &TdApi::init)
		.def("registerFront", &TdApi::registerFront)
		.def("subscribePrivateTopic", &TdApi::subscribePrivateTopic)
		.def("subscribePublicTopic", &TdApi::subscribePublicTopic)
		.def("join", &TdApi::join)
		.def("reqUserLogin", &TdApi::reqUserLogin)
		.def("reqUserLogout", &TdApi::reqUserLogout)
		.def("reqQryInstrument", &TdApi::reqQryInstrument)
		.def("reqQryVarietyCode", &TdApi::reqQryVarietyCode)
		.def("reqOrderInsert", &TdApi::reqOrderInsert)
		.def("reqOrderAction", &TdApi::reqOrderAction)
		.def("reqQryInvestorPosition", &TdApi::reqQryInvestorPosition)
		.def("reqQryTradingAccount", &TdApi::reqQryTradingAccount)
		.def("reqQryTrade", &TdApi::reqQryTrade)
		.def("reqQryOrder", &TdApi::reqQryOrder)
		.def("reqQryStorage", &TdApi::reqQryStorage)
		.def("reqQryCostMarginFeeRate", &TdApi::reqQryCostMarginFeeRate)
		.def("reqConditionOrderInsert", &TdApi::reqConditionOrderInsert)
		.def("reqConditionOrderAction", &TdApi::reqConditionOrderAction)
		.def("reqQryConditionOrder", &TdApi::reqQryConditionOrder)
		.def("reqQryConditionOrderTrade", &TdApi::reqQryConditionOrderTrade)
		.def("reqQryClientSessionInfo", &TdApi::reqQryClientSessionInfo)
		.def("reqQryQuotation", &TdApi::reqQryQuotation)
		.def("reqQryInvestorPositionDetail", &TdApi::reqQryInvestorPositionDetail)
		.def("reqModifyPassword", &TdApi::reqModifyPassword)
		.def("reqQryHisCapital", &TdApi::reqQryHisCapital)
		.def("reqETFSubScription", &TdApi::reqETFSubScription)
		.def("reqETFApplyForPurchase", &TdApi::reqETFApplyForPurchase)
		.def("reqETFRedeem", &TdApi::reqETFRedeem)
		.def("reqETFAccountBinding", &TdApi::reqETFAccountBinding)
		.def("reqETFAccountUnbinding", &TdApi::reqETFAccountUnbinding)
		.def("reqETFTradeDetail", &TdApi::reqETFTradeDetail)
		.def("reqETFPcfDetail", &TdApi::reqETFPcfDetail)
		.def("reqBOCMoneyIO", &TdApi::reqBOCMoneyIO)

		.def("onFrontConnected", &TdApi::onFrontConnected)
		.def("onFrontDisconnected", &TdApi::onFrontDisconnected)
		.def("onRspUserLogin", &TdApi::onRspUserLogin)
		.def("onRspUserLogout", &TdApi::onRspUserLogout)
		.def("onNtyMktStatus", &TdApi::onNtyMktStatus)
		.def("onRtnInstrumentStatus", &TdApi::onRtnInstrumentStatus)
		.def("onRspQryInstrument", &TdApi::onRspQryInstrument)
		.def("onRspReqQryVarietyCode", &TdApi::onRspReqQryVarietyCode)
		.def("onRspOrderInsert", &TdApi::onRspOrderInsert)
		.def("onRspETFSubscriptionOrderInsert", &TdApi::onRspETFSubscriptionOrderInsert)
		.def("onRspETFPurchaseOrderInsert", &TdApi::onRspETFPurchaseOrderInsert)
		.def("onRspETFRedeemInsert", &TdApi::onRspETFRedeemInsert)
		.def("onRspETFAccountBinding", &TdApi::onRspETFAccountBinding)
		.def("onRspETFAccountUnbinding", &TdApi::onRspETFAccountUnbinding)
		.def("onRtnOrder", &TdApi::onRtnOrder)
		.def("onForceLogout", &TdApi::onForceLogout)
		.def("onRtnETFAccountBindingStatus", &TdApi::onRtnETFAccountBindingStatus)
		.def("onRtnETFOrder", &TdApi::onRtnETFOrder)
		.def("onRspOrderAction", &TdApi::onRspOrderAction)
		.def("onRspError", &TdApi::onRspError)
		.def("onRtnTrade", &TdApi::onRtnTrade)
		.def("onRspQryTradingAccount", &TdApi::onRspQryTradingAccount)
		.def("onRspQryHisCapital", &TdApi::onRspQryHisCapital)
		.def("onRspQryOrder", &TdApi::onRspQryOrder)
		.def("onRspQryTrade", &TdApi::onRspQryTrade)
		.def("onRspQryInvestorPosition", &TdApi::onRspQryInvestorPosition)
		.def("onRspQryClientStorage", &TdApi::onRspQryClientStorage)
		.def("onRspQryCostMarginFeeRate", &TdApi::onRspQryCostMarginFeeRate)
		.def("onRspConditionOrderInsert", &TdApi::onRspConditionOrderInsert)
		.def("onRspConditionOrderAction", &TdApi::onRspConditionOrderAction)
		.def("onRspQryConditionOrder", &TdApi::onRspQryConditionOrder)
		.def("onRspQryConditionOrderTrade", &TdApi::onRspQryConditionOrderTrade)
		.def("onRspQryClientSessionInfo", &TdApi::onRspQryClientSessionInfo)
		.def("onRspQryQuotation", &TdApi::onRspQryQuotation)
		.def("onRspQryInvestorPositionDetail", &TdApi::onRspQryInvestorPositionDetail)
		.def("onRspQryETFradeDetail", &TdApi::onRspQryETFradeDetail)
		.def("onRspQryETFPcfDetail", &TdApi::onRspQryETFPcfDetail)
		.def("onRspModifyPassword", &TdApi::onRspModifyPassword)
		.def("onRspB0CMoneyIO", &TdApi::onRspB0CMoneyIO)
		;


}
