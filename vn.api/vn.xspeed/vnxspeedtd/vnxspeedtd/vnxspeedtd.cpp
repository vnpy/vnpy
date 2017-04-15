// TdApi.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnxspeedtd.h"



///-------------------------------------------------------------------------------------
///从Python对象到C++类型转换用的函数
///-------------------------------------------------------------------------------------

void getInt(dict d, string key, int *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getLong(dict d, string key, long *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getShort(dict d, string key, short *value)
{
	if (d.has_key(key))		//检查字典中是否存在该键值
	{
		object o = d[key];	//获取该键值
		extract<int> x(o);	//创建提取器
		if (x.check())		//如果可以提取
		{
			*value = x();	//对目标整数指针赋值
		}
	}
};

void getDouble(dict d, string key, double *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<double> x(o);
		if (x.check())
		{
			*value = x();
		}
	}
};

void getChar(dict d, string key, char *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<string> x(o);
		if (x.check())
		{
			string s = x();
			const char *buffer = s.c_str();
			*value = *buffer;
		}
	}
};

void getString(dict d, string key, char *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<string> x(o);
		if (x.check())
		{
			string s = x();
			const char *buffer = s.c_str();
			//对字符串指针赋值必须使用strcpy_s, vs2013使用strcpy编译通不过
			//+1应该是因为C++字符串的结尾符号？不是特别确定，不加这个1会出错
			strcpy_s(value, strlen(buffer) + 1, buffer);
		}
	}
};



///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

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

void TdApi::OnRspQuoteCancel(struct DFITCQuoteRspField * pRspQuoteCanceledData, struct DFITCErrorRtnField * pErrorInfo)
{
	Task task = Task();
	task.task_name = ONRSPQUOTECANCEL;

	if (pRspQuoteCanceledData)
	{
		task.task_data = *pRspQuoteCanceledData;
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

void TdApi::OnRspCancelAllOrder(struct DFITCCancelAllOrderRspField *pRspCancelAllOrderData, struct DFITCErrorRtnField * pErrorInfo)
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


///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void TdApi::processTask()
{
	while (1)
	{
		Task task = this->task_queue.wait_and_pop();

		switch (task.task_name)
		{
		case ONFRONTCONNECTED:
		{
			this->processFrontConnected(task);
			break;
		}

		case ONFRONTDISCONNECTED:
		{
			this->processFrontDisconnected(task);
			break;
		}

		case ONRSPUSERLOGIN:
		{
			this->processRspUserLogin(task);
			break;
		}

		case ONRSPUSERLOGOUT:
		{
			this->processRspUserLogout(task);
			break;
		}

		case ONRSPINSERTORDER:
		{
			this->processRspInsertOrder(task);
			break;
		}

		case ONRSPCANCELORDER:
		{
			this->processRspCancelOrder(task);
			break;
		}

		case ONRTNERRORMSG:
		{
			this->processRtnErrorMsg(task);
			break;
		}

		case ONRTNMATCHEDINFO:
		{
			this->processRtnMatchedInfo(task);
			break;
		}

		case ONRTNORDER:
		{
			this->processRtnOrder(task);
			break;
		}

		case ONRTNCANCELORDER:
		{
			this->processRtnCancelOrder(task);
			break;
		}

		case ONRSPQRYORDERINFO:
		{
			this->processRspQryOrderInfo(task);
			break;
		}

		case ONRSPQRYMATCHINFO:
		{
			this->processRspQryMatchInfo(task);
			break;
		}

		case ONRSPQRYPOSITION:
		{
			this->processRspQryPosition(task);
			break;
		}

		case ONRSPCUSTOMERCAPITAL:
		{
			this->processRspCustomerCapital(task);
			break;
		}

		case ONRSPQRYEXCHANGEINSTRUMENT:
		{
			this->processRspQryExchangeInstrument(task);
			break;
		}

		case ONRSPARBITRAGEINSTRUMENT:
		{
			this->processRspArbitrageInstrument(task);
			break;
		}

		case ONRSPQRYSPECIFYINSTRUMENT:
		{
			this->processRspQrySpecifyInstrument(task);
			break;
		}

		case ONRSPQRYPOSITIONDETAIL:
		{
			this->processRspQryPositionDetail(task);
			break;
		}

		case ONRTNTRADINGNOTICE:
		{
			this->processRtnTradingNotice(task);
			break;
		}

		case ONRSPRESETPASSWORD:
		{
			this->processRspResetPassword(task);
			break;
		}

		case ONRSPQRYTRADECODE:
		{
			this->processRspQryTradeCode(task);
			break;
		}

		case ONRSPBILLCONFIRM:
		{
			this->processRspBillConfirm(task);
			break;
		}

		case ONRSPEQUITYCOMPUTMODE:
		{
			this->processRspEquityComputMode(task);
			break;
		}

		case ONRSPQRYBILL:
		{
			this->processRspQryBill(task);
			break;
		}

		case ONRSPCONFIRMPRODUCTINFO:
		{
			this->processRspConfirmProductInfo(task);
			break;
		}

		case ONRSPTRADINGDAY:
		{
			this->processRspTradingDay(task);
			break;
		}

		case ONRSPQUOTEINSERT:
		{
			this->processRspQuoteInsert(task);
			break;
		}

		case ONRTNQUOTEINSERT:
		{
			this->processRtnQuoteInsert(task);
			break;
		}

		case ONRSPQUOTECANCEL:
		{
			this->processRspQuoteCancel(task);
			break;
		}

		case ONRTNQUOTECANCEL:
		{
			this->processRtnQuoteCancel(task);
			break;
		}

		case ONRTNQUOTEMATCHEDINFO:
		{
			this->processRtnQuoteMatchedInfo(task);
			break;
		}

		case ONRSPCANCELALLORDER:
		{
			this->processRspCancelAllOrder(task);
			break;
		}

		case ONRSPQRYQUOTENOTICE:
		{
			this->processRspQryQuoteNotice(task);
			break;
		}

		case ONRSPFORQUOTE:
		{
			this->processRspForQuote(task);
			break;
		}

		case ONRTNFORQUOTE:
		{
			this->processRtnForQuote(task);
			break;
		}

		case ONRSPQRYQUOTEORDERINFO:
		{
			this->processRspQryQuoteOrderInfo(task);
			break;
		}

		case ONRSPQRYFORQUOTE:
		{
			this->processRspQryForQuote(task);
			break;
		}

		case ONRSPQRYTRANSFERBANK:
		{
			this->processRspQryTransferBank(task);
			break;
		}

		case ONRSPQRYTRANSFERSERIAL:
		{
			this->processRspQryTransferSerial(task);
			break;
		}

		case ONRSPFROMBANKTOFUTUREBYFUTURE:
		{
			this->processRspFromBankToFutureByFuture(task);
			break;
		}

		case ONRSPFROMFUTURETOBANKBYFUTURE:
		{
			this->processRspFromFutureToBankByFuture(task);
			break;
		}

		case ONRTNFROMBANKTOFUTUREBYFUTURE:
		{
			this->processRtnFromBankToFutureByFuture(task);
			break;
		}

		case ONRTNFROMFUTURETOBANKBYFUTURE:
		{
			this->processRtnFromFutureToBankByFuture(task);
			break;
		}

		case ONRTNREPEALFROMFUTURETOBANKBYBANK:
		{
			this->processRtnRepealFromFutureToBankByBank(task);
			break;
		}

		case ONRSPQRYEXCHANGESTATUS:
		{
			this->processRspQryExchangeStatus(task);
			break;
		}

		case ONRTNEXCHANGESTATUS:
		{
			this->processRtnExchangeStatus(task);
			break;
		}

		case ONRSPQRYDEPTHMARKETDATA:
		{
			this->processRspQryDepthMarketData(task);
			break;
		}
		};
	}
};

void TdApi::processFrontConnected(Task task)
{
	PyLock lock;
	this->onFrontConnected();
};

void TdApi::processFrontDisconnected(Task task)
{
	PyLock lock;
	this->onFrontDisconnected(task.task_id);
};

void TdApi::processRspUserLogin(Task task)
{
	PyLock lock;
	DFITCUserLoginInfoRtnField task_data = any_cast<DFITCUserLoginInfoRtnField>(task.task_data);
	dict data;
	data["CZCETime"] = task_data.CZCETime;
	data["initLocalOrderID"] = task_data.initLocalOrderID;
	data["SHFETime"] = task_data.SHFETime;
	data["errorMsg"] = task_data.errorMsg;
	data["INETime"] = task_data.INETime;
	data["lRequestID"] = task_data.lRequestID;
	data["loginResult"] = task_data.loginResult;
	data["sessionID"] = task_data.sessionID;
	data["nErrorID"] = task_data.nErrorID;
	data["CFFEXTime"] = task_data.CFFEXTime;
	data["DCEtime"] = task_data.DCEtime;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspUserLogin(data, error);
};

void TdApi::processRspUserLogout(Task task)
{
	PyLock lock;
	DFITCUserLogoutInfoRtnField task_data = any_cast<DFITCUserLogoutInfoRtnField>(task.task_data);
	dict data;
	data["logoutResult"] = task_data.logoutResult;
	data["lRequestID"] = task_data.lRequestID;
	data["nErrorID"] = task_data.nErrorID;
	data["errorMsg"] = task_data.errorMsg;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspUserLogout(data, error);
};

void TdApi::processRspInsertOrder(Task task)
{
	PyLock lock;
	DFITCOrderRspDataRtnField task_data = any_cast<DFITCOrderRspDataRtnField>(task.task_data);
	dict data;
	data["minMatchAmount"] = task_data.minMatchAmount;
	data["insertType"] = task_data.insertType;
	data["customCategory"] = task_data.customCategory;
	data["openCloseType"] = task_data.openCloseType;
	data["fee"] = task_data.fee;
	data["insertPrice"] = task_data.insertPrice;
	data["profitLossPrice"] = task_data.profitLossPrice;
	data["instrumentType"] = task_data.instrumentType;
	data["accountID"] = task_data.accountID;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["clientID"] = task_data.clientID;
	data["sessionID"] = task_data.sessionID;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["orderProperty"] = task_data.orderProperty;
	data["spdOrderID"] = task_data.spdOrderID;
	data["lRequestID"] = task_data.lRequestID;
	data["speculator"] = task_data.speculator;
	data["orderType"] = task_data.orderType;
	data["margin"] = task_data.margin;
	data["orderStatus"] = task_data.orderStatus;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspInsertOrder(data, error);
};

void TdApi::processRspCancelOrder(Task task)
{
	PyLock lock;
	DFITCOrderRspDataRtnField task_data = any_cast<DFITCOrderRspDataRtnField>(task.task_data);
	dict data;
	data["minMatchAmount"] = task_data.minMatchAmount;
	data["insertType"] = task_data.insertType;
	data["customCategory"] = task_data.customCategory;
	data["openCloseType"] = task_data.openCloseType;
	data["fee"] = task_data.fee;
	data["insertPrice"] = task_data.insertPrice;
	data["profitLossPrice"] = task_data.profitLossPrice;
	data["instrumentType"] = task_data.instrumentType;
	data["accountID"] = task_data.accountID;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["clientID"] = task_data.clientID;
	data["sessionID"] = task_data.sessionID;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["orderProperty"] = task_data.orderProperty;
	data["spdOrderID"] = task_data.spdOrderID;
	data["lRequestID"] = task_data.lRequestID;
	data["speculator"] = task_data.speculator;
	data["orderType"] = task_data.orderType;
	data["margin"] = task_data.margin;
	data["orderStatus"] = task_data.orderStatus;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspCancelOrder(data, error);
};

void TdApi::processRtnErrorMsg(Task task)
{
	PyLock lock;
	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRtnErrorMsg(error);
};

void TdApi::processRtnMatchedInfo(Task task)
{
	PyLock lock;
	DFITCMatchRtnField task_data = any_cast<DFITCMatchRtnField>(task.task_data);
	dict data;
	data["insertType"] = task_data.insertType;
	data["adjustmentInfo"] = task_data.adjustmentInfo;
	data["orderStatus"] = task_data.orderStatus;
	data["customCategory"] = task_data.customCategory;
	data["openCloseType"] = task_data.openCloseType;
	data["fee"] = task_data.fee;
	data["insertPrice"] = task_data.insertPrice;
	data["orderType"] = task_data.orderType;
	data["OrderSysID"] = task_data.OrderSysID;
	data["matchType"] = task_data.matchType;
	data["instrumentType"] = task_data.instrumentType;
	data["accountID"] = task_data.accountID;
	data["matchedTime"] = task_data.matchedTime;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["matchedPrice"] = task_data.matchedPrice;
	data["clientID"] = task_data.clientID;
	data["sessionID"] = task_data.sessionID;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["spdOrderID"] = task_data.spdOrderID;
	data["frozenCapita"] = task_data.frozenCapita;
	data["matchID"] = task_data.matchID;
	data["speculator"] = task_data.speculator;
	data["matchedAmount"] = task_data.matchedAmount;
	data["margin"] = task_data.margin;
	data["turnover"] = task_data.turnover;

	this->onRtnMatchedInfo(data);
};

void TdApi::processRtnOrder(Task task)
{
	PyLock lock;
	DFITCOrderRtnField task_data = any_cast<DFITCOrderRtnField>(task.task_data);
	dict data;
	data["minMatchAmount"] = task_data.minMatchAmount;
	data["insertType"] = task_data.insertType;
	data["customCategory"] = task_data.customCategory;
	data["openCloseType"] = task_data.openCloseType;
	data["statusMsg"] = task_data.statusMsg;
	data["insertPrice"] = task_data.insertPrice;
	data["profitLossPrice"] = task_data.profitLossPrice;
	data["OrderSysID"] = task_data.OrderSysID;
	data["instrumentType"] = task_data.instrumentType;
	data["cancelAmount"] = task_data.cancelAmount;
	data["accountID"] = task_data.accountID;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["extSpdOrderID"] = task_data.extSpdOrderID;
	data["sessionID"] = task_data.sessionID;
	data["clientID"] = task_data.clientID;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["orderProperty"] = task_data.orderProperty;
	data["speculator"] = task_data.speculator;
	data["reservedType2"] = task_data.reservedType2;
	data["orderType"] = task_data.orderType;
	data["spdOrderID"] = task_data.spdOrderID;
	data["orderStatus"] = task_data.orderStatus;

	this->onRtnOrder(data);
};

void TdApi::processRtnCancelOrder(Task task)
{
	PyLock lock;
	DFITCOrderCanceledRtnField task_data = any_cast<DFITCOrderCanceledRtnField>(task.task_data);
	dict data;
	data["minMatchAmount"] = task_data.minMatchAmount;
	data["insertType"] = task_data.insertType;
	data["customCategory"] = task_data.customCategory;
	data["openCloseType"] = task_data.openCloseType;
	data["fee"] = task_data.fee;
	data["statusMsg"] = task_data.statusMsg;
	data["insertPrice"] = task_data.insertPrice;
	data["profitLossPrice"] = task_data.profitLossPrice;
	data["OrderSysID"] = task_data.OrderSysID;
	data["instrumentType"] = task_data.instrumentType;
	data["cancelAmount"] = task_data.cancelAmount;
	data["accountID"] = task_data.accountID;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["clientID"] = task_data.clientID;
	data["sessionID"] = task_data.sessionID;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["orderProperty"] = task_data.orderProperty;
	data["spdOrderID"] = task_data.spdOrderID;
	data["speculator"] = task_data.speculator;
	data["canceledTime"] = task_data.canceledTime;
	data["margin"] = task_data.margin;
	data["orderStatus"] = task_data.orderStatus;

	this->onRtnCancelOrder(data);
};

void TdApi::processRspQryOrderInfo(Task task)
{
	PyLock lock;
	DFITCOrderCommRtnField task_data = any_cast<DFITCOrderCommRtnField>(task.task_data);
	dict data;
	data["commTime"] = task_data.commTime;
	data["orderStatus"] = task_data.orderStatus;
	data["customCategory"] = task_data.customCategory;
	data["fee"] = task_data.fee;
	data["insertPrice"] = task_data.insertPrice;
	data["profitLossPrice"] = task_data.profitLossPrice;
	data["OrderSysID"] = task_data.OrderSysID;
	data["instrumentType"] = task_data.instrumentType;
	data["cancelAmount"] = task_data.cancelAmount;
	data["accountID"] = task_data.accountID;
	data["operStation"] = task_data.operStation;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["matchedPrice"] = task_data.matchedPrice;
	data["clientID"] = task_data.clientID;
	data["submitTime"] = task_data.submitTime;
	data["lRequestID"] = task_data.lRequestID;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["orderProperty"] = task_data.orderProperty;
	data["margin"] = task_data.margin;
	data["openClose"] = task_data.openClose;
	data["speculator"] = task_data.speculator;
	data["matchedAmount"] = task_data.matchedAmount;
	data["sessionId"] = task_data.sessionId;
	data["reservedType2"] = task_data.reservedType2;
	data["orderType"] = task_data.orderType;
	data["spdOrderID"] = task_data.spdOrderID;
	data["insertType"] = task_data.insertType;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryOrderInfo(data, error, task.task_last);
};

void TdApi::processRspQryMatchInfo(Task task)
{
	PyLock lock;
	DFITCMatchedRtnField task_data = any_cast<DFITCMatchedRtnField>(task.task_data);
	dict data;
	data["matchedMort"] = task_data.matchedMort;
	data["customCategory"] = task_data.customCategory;
	data["fee"] = task_data.fee;
	data["orderType"] = task_data.orderType;
	data["OrderSysID"] = task_data.OrderSysID;
	data["matchType"] = task_data.matchType;
	data["instrumentType"] = task_data.instrumentType;
	data["accountID"] = task_data.accountID;
	data["matchedTime"] = task_data.matchedTime;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["matchedPrice"] = task_data.matchedPrice;
	data["matchedID"] = task_data.matchedID;
	data["lRequestID"] = task_data.lRequestID;
	data["clientID"] = task_data.clientID;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["openClose"] = task_data.openClose;
	data["speculator"] = task_data.speculator;
	data["matchedAmount"] = task_data.matchedAmount;
	data["sessionId"] = task_data.sessionId;
	data["reservedType2"] = task_data.reservedType2;
	data["spdOrderID"] = task_data.spdOrderID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryMatchInfo(data, error, task.task_last);
};

void TdApi::processRspQryPosition(Task task)
{
	PyLock lock;
	DFITCPositionInfoRtnField task_data = any_cast<DFITCPositionInfoRtnField>(task.task_data);
	dict data;
	data["openAvgPrice"] = task_data.openAvgPrice;
	data["dPremium"] = task_data.dPremium;
	data["dMargin"] = task_data.dMargin;
	data["lastAvaiAmount"] = task_data.lastAvaiAmount;
	data["positionAmount"] = task_data.positionAmount;
	data["todayAmount"] = task_data.todayAmount;
	data["datePositionProfitLoss"] = task_data.datePositionProfitLoss;
	data["floatProfitLoss"] = task_data.floatProfitLoss;
	data["instrumentType"] = task_data.instrumentType;
	data["positionAvgPrice"] = task_data.positionAvgPrice;
	data["preSettlementPrice"] = task_data.preSettlementPrice;
	data["buySellType"] = task_data.buySellType;
	data["tradingAmount"] = task_data.tradingAmount;
	data["clientID"] = task_data.clientID;
	data["lRequestID"] = task_data.lRequestID;
	data["totalAvaiAmount"] = task_data.totalAvaiAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["todayAvaiAmount"] = task_data.todayAvaiAmount;
	data["yesterdayTradingAmount"] = task_data.yesterdayTradingAmount;
	data["speculator"] = task_data.speculator;
	data["dateCloseProfitLoss"] = task_data.dateCloseProfitLoss;
	data["accountID"] = task_data.accountID;
	data["lastAmount"] = task_data.lastAmount;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryPosition(data, error, task.task_last);
};

void TdApi::processRspCustomerCapital(Task task)
{
	PyLock lock;
	DFITCCapitalInfoRtnField task_data = any_cast<DFITCCapitalInfoRtnField>(task.task_data);
	dict data;
	data["available"] = task_data.available;
	data["todayPremiumIncome"] = task_data.todayPremiumIncome;
	data["todayPremiumPay"] = task_data.todayPremiumPay;
	data["preEquity"] = task_data.preEquity;
	data["totFundOut"] = task_data.totFundOut;
	data["frozenMargin"] = task_data.frozenMargin;
	data["todayEquity"] = task_data.todayEquity;
	data["totFundIn"] = task_data.totFundIn;
	data["closeProfitLoss"] = task_data.closeProfitLoss;
	data["riskDegree"] = task_data.riskDegree;
	data["optMarketValue"] = task_data.optMarketValue;
	data["fee"] = task_data.fee;
	data["requestID"] = task_data.requestID;
	data["withdraw"] = task_data.withdraw;
	data["positionProfitLoss"] = task_data.positionProfitLoss;
	data["floatProfitLoss"] = task_data.floatProfitLoss;
	data["yesterdayPremium"] = task_data.yesterdayPremium;
	data["margin"] = task_data.margin;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspCustomerCapital(data, error, task.task_last);
};

void TdApi::processRspQryExchangeInstrument(Task task)
{
	PyLock lock;
	DFITCExchangeInstrumentRtnField task_data = any_cast<DFITCExchangeInstrumentRtnField>(task.task_data);
	dict data;
	data["optionType"] = task_data.optionType;
	data["underlying"] = task_data.underlying;
	data["instrumentType"] = task_data.instrumentType;
	data["minMargin"] = task_data.minMargin;
	data["tradeSize"] = task_data.tradeSize;
	data["lowerLimitPrice"] = task_data.lowerLimitPrice;
	data["VarietyName"] = task_data.VarietyName;
	data["preSettlementPrice"] = task_data.preSettlementPrice;
	data["contractMultiplier"] = task_data.contractMultiplier;
	data["orderTopLimit"] = task_data.orderTopLimit;
	data["mktOrderTopLimit"] = task_data.mktOrderTopLimit;
	data["settlementPrice"] = task_data.settlementPrice;
	data["exchangeRiskDegree"] = task_data.exchangeRiskDegree;
	data["strikePrice"] = task_data.strikePrice;
	data["preOpenInterest"] = task_data.preOpenInterest;
	data["lRequestID"] = task_data.lRequestID;
	data["upperLimitPrice"] = task_data.upperLimitPrice;
	data["instrumentMaturity"] = task_data.instrumentMaturity;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["instrumentPrefix"] = task_data.instrumentPrefix;
	data["preClosePrice"] = task_data.preClosePrice;
	data["instrumentExpiration"] = task_data.instrumentExpiration;
	data["minPriceFluctuation"] = task_data.minPriceFluctuation;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryExchangeInstrument(data, error, task.task_last);
};

void TdApi::processRspArbitrageInstrument(Task task)
{
	PyLock lock;
	DFITCAbiInstrumentRtnField task_data = any_cast<DFITCAbiInstrumentRtnField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["instrumentName"] = task_data.instrumentName;
	data["lRequestID"] = task_data.lRequestID;
	data["exchangeID"] = task_data.exchangeID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspArbitrageInstrument(data, error, task.task_last);
};

void TdApi::processRspQrySpecifyInstrument(Task task)
{
	PyLock lock;
	DFITCInstrumentRtnField task_data = any_cast<DFITCInstrumentRtnField>(task.task_data);
	dict data;
	data["optExecRatioPerVol"] = task_data.optExecRatioPerVol;
	data["closeFeeVolRatio"] = task_data.closeFeeVolRatio;
	data["contractMultiplier"] = task_data.contractMultiplier;
	data["openFeeAmtRatio"] = task_data.openFeeAmtRatio;
	data["longMarginRatio"] = task_data.longMarginRatio;
	data["computeMode"] = task_data.computeMode;
	data["lowerLimitPrice"] = task_data.lowerLimitPrice;
	data["preClosePrice"] = task_data.preClosePrice;
	data["preSettlementPrice"] = task_data.preSettlementPrice;
	data["shortMarginRatio"] = task_data.shortMarginRatio;
	data["orderTopLimit"] = task_data.orderTopLimit;
	data["settlementPrice"] = task_data.settlementPrice;
	data["preOpenInterest"] = task_data.preOpenInterest;
	data["openFeeVolRatio"] = task_data.openFeeVolRatio;
	data["lRequestID"] = task_data.lRequestID;
	data["atMoneyNorm"] = task_data.atMoneyNorm;
	data["upperLimitPrice"] = task_data.upperLimitPrice;
	data["instrumentMaturity"] = task_data.instrumentMaturity;
	data["optExecRatio"] = task_data.optExecRatio;
	data["longMarginRatioByVolume"] = task_data.longMarginRatioByVolume;
	data["instrumentID"] = task_data.instrumentID;
	data["minimumPriceChange"] = task_data.minimumPriceChange;
	data["closeTodayFeeAmtRatio"] = task_data.closeTodayFeeAmtRatio;
	data["instrumentType"] = task_data.instrumentType;
	data["closeTodayFeeVolRatio"] = task_data.closeTodayFeeVolRatio;
	data["shortMarginRatioByVolume"] = task_data.shortMarginRatioByVolume;
	data["closeFeeAmtRatio"] = task_data.closeFeeAmtRatio;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQrySpecifyInstrument(data, error, task.task_last);
};

void TdApi::processRspQryPositionDetail(Task task)
{
	PyLock lock;
	DFITCPositionDetailRtnField task_data = any_cast<DFITCPositionDetailRtnField>(task.task_data);
	dict data;
	data["closeMatchVol"] = task_data.closeMatchVol;
	data["openPrice"] = task_data.openPrice;
	data["customCategory"] = task_data.customCategory;
	data["matchedDate"] = task_data.matchedDate;
	data["dMargin"] = task_data.dMargin;
	data["positionDateType"] = task_data.positionDateType;
	data["datePositionProfitLoss"] = task_data.datePositionProfitLoss;
	data["floatProfitLoss"] = task_data.floatProfitLoss;
	data["instrumentType"] = task_data.instrumentType;
	data["preSettlementPrice"] = task_data.preSettlementPrice;
	data["buySellType"] = task_data.buySellType;
	data["clientID"] = task_data.clientID;
	data["volume"] = task_data.volume;
	data["lRequestID"] = task_data.lRequestID;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["matchID"] = task_data.matchID;
	data["speculator"] = task_data.speculator;
	data["closeOrderVol"] = task_data.closeOrderVol;
	data["dateCloseProfitLoss"] = task_data.dateCloseProfitLoss;
	data["accountID"] = task_data.accountID;
	data["spdOrderID"] = task_data.spdOrderID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryPositionDetail(data, error, task.task_last);
};

void TdApi::processRtnTradingNotice(Task task)
{
	PyLock lock;
	DFITCTradingNoticeInfoField task_data = any_cast<DFITCTradingNoticeInfoField>(task.task_data);
	dict data;
	data["FieldContent"] = task_data.FieldContent;
	data["SendTime"] = task_data.SendTime;
	data["noticeType"] = task_data.noticeType;
	data["accountID"] = task_data.accountID;

	this->onRtnTradingNotice(data);
};

void TdApi::processRspResetPassword(Task task)
{
	PyLock lock;
	DFITCResetPwdRspField task_data = any_cast<DFITCResetPwdRspField>(task.task_data);
	dict data;
	data["lRequestID"] = task_data.lRequestID;
	data["execState"] = task_data.execState;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspResetPassword(data, error);
};

void TdApi::processRspQryTradeCode(Task task)
{
	PyLock lock;
	DFITCQryTradeCodeRtnField task_data = any_cast<DFITCQryTradeCodeRtnField>(task.task_data);
	dict data;
	data["exchangeCode"] = task_data.exchangeCode;
	data["clientID"] = task_data.clientID;
	data["lRequestID"] = task_data.lRequestID;
	data["clientIDType"] = task_data.clientIDType;
	data["accountID"] = task_data.accountID;
	data["clientStatus"] = task_data.clientStatus;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryTradeCode(data, error, task.task_last);
};

void TdApi::processRspBillConfirm(Task task)
{
	PyLock lock;
	DFITCBillConfirmRspField task_data = any_cast<DFITCBillConfirmRspField>(task.task_data);
	dict data;
	data["lRequestID"] = task_data.lRequestID;
	data["execState"] = task_data.execState;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspBillConfirm(data, error);
};

void TdApi::processRspEquityComputMode(Task task)
{
	PyLock lock;
	DFITCEquityComputModeRtnField task_data = any_cast<DFITCEquityComputModeRtnField>(task.task_data);
	dict data;
	data["priceNote"] = task_data.priceNote;
	data["capConMode"] = task_data.capConMode;

	this->onRspEquityComputMode(data);
};

void TdApi::processRspQryBill(Task task)
{
	PyLock lock;
	DFITCQryBillRtnField task_data = any_cast<DFITCQryBillRtnField>(task.task_data);
	dict data;
	data["lRequestID"] = task_data.lRequestID;
	data["message"] = task_data.message;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryBill(data, error, task.task_last);
};

void TdApi::processRspConfirmProductInfo(Task task)
{
	PyLock lock;
	DFITCProductRtnField task_data = any_cast<DFITCProductRtnField>(task.task_data);
	dict data;
	data["brokerInfoName"] = task_data.brokerInfoName;
	data["vendorID"] = task_data.vendorID;
	data["productOnlineCount"] = task_data.productOnlineCount;
	data["frontID"] = task_data.frontID;
	data["productID"] = task_data.productID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspConfirmProductInfo(data, error);
};

void TdApi::processRspTradingDay(Task task)
{
	PyLock lock;
	DFITCTradingDayRtnField task_data = any_cast<DFITCTradingDayRtnField>(task.task_data);
	dict data;
	data["date"] = task_data.date;
	data["lRequestID"] = task_data.lRequestID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspTradingDay(data, error);
};

void TdApi::processRspQuoteInsert(Task task)
{
	PyLock lock;
	DFITCQuoteRspField task_data = any_cast<DFITCQuoteRspField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["orderTime"] = task_data.orderTime;
	data["fee"] = task_data.fee;
	data["localOrderID"] = task_data.localOrderID;
	data["margin"] = task_data.margin;
	data["sessionID"] = task_data.sessionID;
	data["clientID"] = task_data.clientID;
	data["lRequestID"] = task_data.lRequestID;
	data["orderStatus"] = task_data.orderStatus;
	data["quoteID"] = task_data.quoteID;
	data["customCategory"] = task_data.customCategory;
	data["spdOrderID"] = task_data.spdOrderID;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQuoteInsert(data, error);
};

void TdApi::processRtnQuoteInsert(Task task)
{
	PyLock lock;
	DFITCQuoteRtnField task_data = any_cast<DFITCQuoteRtnField>(task.task_data);
	dict data;
	data["quoteID"] = task_data.quoteID;
	data["sOpenCloseType"] = task_data.sOpenCloseType;
	data["seatCode"] = task_data.seatCode;
	data["orderStatus"] = task_data.orderStatus;
	data["orderSysID"] = task_data.orderSysID;
	data["bOpenCloseType"] = task_data.bOpenCloseType;
	data["suspendTime"] = task_data.suspendTime;
	data["customCategory"] = task_data.customCategory;
	data["entrusTeller"] = task_data.entrusTeller;
	data["bInsertPrice"] = task_data.bInsertPrice;
	data["instrumentType"] = task_data.instrumentType;
	data["accountID"] = task_data.accountID;
	data["localOrderID"] = task_data.localOrderID;
	data["errorMsg"] = task_data.errorMsg;
	data["bOrderAmount"] = task_data.bOrderAmount;
	data["sInsertPrice"] = task_data.sInsertPrice;
	data["clientID"] = task_data.clientID;
	data["sessionID"] = task_data.sessionID;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["speculator"] = task_data.speculator;
	data["sOrderAmount"] = task_data.sOrderAmount;
	data["spdOrderID"] = task_data.spdOrderID;

	this->onRtnQuoteInsert(data);
};

void TdApi::processRspQuoteCancel(Task task)
{
	PyLock lock;

	DFITCQuoteRspField task_data = any_cast<DFITCQuoteRspField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["orderTime"] = task_data.orderTime;
	data["fee"] = task_data.fee;
	data["localOrderID"] = task_data.localOrderID;
	data["margin"] = task_data.margin;
	data["sessionID"] = task_data.sessionID;
	data["clientID"] = task_data.clientID;
	data["lRequestID"] = task_data.lRequestID;
	data["orderStatus"] = task_data.orderStatus;
	data["quoteID"] = task_data.quoteID;
	data["customCategory"] = task_data.customCategory;
	data["spdOrderID"] = task_data.spdOrderID;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQuoteCancel(data, error);
};

void TdApi::processRtnQuoteCancel(Task task)
{
	PyLock lock;
	DFITCQuoteCanceledRtnField task_data = any_cast<DFITCQuoteCanceledRtnField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["speculator"] = task_data.speculator;
	data["exchangeID"] = task_data.exchangeID;
	data["fee"] = task_data.fee;
	data["localOrderID"] = task_data.localOrderID;
	data["sOpenCloseType"] = task_data.sOpenCloseType;
	data["margin"] = task_data.margin;
	data["buySellType"] = task_data.buySellType;
	data["clientID"] = task_data.clientID;
	data["seatCode"] = task_data.seatCode;
	data["sessionID"] = task_data.sessionID;
	data["orderStatus"] = task_data.orderStatus;
	data["orderSysID"] = task_data.orderSysID;
	data["entrusTeller"] = task_data.entrusTeller;
	data["bOpenCloseType"] = task_data.bOpenCloseType;
	data["quoteID"] = task_data.quoteID;
	data["canceledTime"] = task_data.canceledTime;
	data["customCategory"] = task_data.customCategory;
	data["spdOrderID"] = task_data.spdOrderID;
	data["cancelAmount"] = task_data.cancelAmount;
	data["accountID"] = task_data.accountID;

	this->onRtnQuoteCancel(data);
};

void TdApi::processRtnQuoteMatchedInfo(Task task)
{
	PyLock lock;
	DFITCQuoteMatchRtnField task_data = any_cast<DFITCQuoteMatchRtnField>(task.task_data);
	dict data;
	data["quoteID"] = task_data.quoteID;
	data["seatCode"] = task_data.seatCode;
	data["closeTodayPrice"] = task_data.closeTodayPrice;
	data["adjustmentInfo"] = task_data.adjustmentInfo;
	data["orderStatus"] = task_data.orderStatus;
	data["customCategory"] = task_data.customCategory;
	data["openCloseType"] = task_data.openCloseType;
	data["fee"] = task_data.fee;
	data["insertPrice"] = task_data.insertPrice;
	data["largeMarginDirect"] = task_data.largeMarginDirect;
	data["OrderSysID"] = task_data.OrderSysID;
	data["entrusTeller"] = task_data.entrusTeller;
	data["instrumentType"] = task_data.instrumentType;
	data["accountID"] = task_data.accountID;
	data["matchedTime"] = task_data.matchedTime;
	data["localOrderID"] = task_data.localOrderID;
	data["buySellType"] = task_data.buySellType;
	data["matchedPrice"] = task_data.matchedPrice;
	data["clientID"] = task_data.clientID;
	data["sessionID"] = task_data.sessionID;
	data["closeTodayAmount"] = task_data.closeTodayAmount;
	data["orderAmount"] = task_data.orderAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["spdOrderID"] = task_data.spdOrderID;
	data["frozenCapita"] = task_data.frozenCapita;
	data["matchID"] = task_data.matchID;
	data["speculator"] = task_data.speculator;
	data["matchedAmount"] = task_data.matchedAmount;
	data["dateCloseProfitLoss"] = task_data.dateCloseProfitLoss;
	data["closePrice"] = task_data.closePrice;
	data["margin"] = task_data.margin;
	data["turnover"] = task_data.turnover;

	this->onRtnQuoteMatchedInfo(data);
};

void TdApi::processRspCancelAllOrder(Task task)
{
	PyLock lock;
	DFITCCancelAllOrderRspField task_data = any_cast<DFITCCancelAllOrderRspField>(task.task_data);
	dict data;
	data["lRequestID"] = task_data.lRequestID;
	data["orderStatus"] = task_data.orderStatus;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspCancelAllOrder(data, error);
};

void TdApi::processRspQryQuoteNotice(Task task)
{
	PyLock lock;
	DFITCQryQuoteNoticeRtnField task_data = any_cast<DFITCQryQuoteNoticeRtnField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["quoteID"] = task_data.quoteID;
	data["source"] = task_data.source;
	data["lRequestID"] = task_data.lRequestID;
	data["quoteTime"] = task_data.quoteTime;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryQuoteNotice(data, error, task.task_last);
};

void TdApi::processRspForQuote(Task task)
{
	PyLock lock;
	DFITCForQuoteRspField task_data = any_cast<DFITCForQuoteRspField>(task.task_data);
	dict data;
	data["lRequestID"] = task_data.lRequestID;
	data["commTime"] = task_data.commTime;
	data["spdOrderID"] = task_data.spdOrderID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspForQuote(data, error);
};

void TdApi::processRtnForQuote(Task task)
{
	PyLock lock;
	DFITCForQuoteRtnField task_data = any_cast<DFITCForQuoteRtnField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["sessionID"] = task_data.sessionID;
	data["orderStatus"] = task_data.orderStatus;
	data["spdOrderID"] = task_data.spdOrderID;
	data["accountID"] = task_data.accountID;

	this->onRtnForQuote(data);
};

void TdApi::processRspQryQuoteOrderInfo(Task task)
{
	PyLock lock;
	DFITCQuoteOrderRtnField task_data = any_cast<DFITCQuoteOrderRtnField>(task.task_data);
	dict data;
	data["quoteID"] = task_data.quoteID;
	data["sOpenCloseType"] = task_data.sOpenCloseType;
	data["commTime"] = task_data.commTime;
	data["margin"] = task_data.margin;
	data["orderStatus"] = task_data.orderStatus;
	data["bOpenCloseType"] = task_data.bOpenCloseType;
	data["customCategory"] = task_data.customCategory;
	data["fee"] = task_data.fee;
	data["bMatchedPrice"] = task_data.bMatchedPrice;
	data["sMatchedPrice"] = task_data.sMatchedPrice;
	data["sInsertPrice"] = task_data.sInsertPrice;
	data["bInsertPrice"] = task_data.bInsertPrice;
	data["accountID"] = task_data.accountID;
	data["localOrderID"] = task_data.localOrderID;
	data["bOrderAmount"] = task_data.bOrderAmount;
	data["operStation"] = task_data.operStation;
	data["submitTime"] = task_data.submitTime;
	data["lRequestID"] = task_data.lRequestID;
	data["bMatchedAmount"] = task_data.bMatchedAmount;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["sCancelAmount"] = task_data.sCancelAmount;
	data["sessionID"] = task_data.sessionID;
	data["sMatchedAmount"] = task_data.sMatchedAmount;
	data["sOrderAmount"] = task_data.sOrderAmount;
	data["spdOrderID"] = task_data.spdOrderID;
	data["bCancelAmount"] = task_data.bCancelAmount;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryQuoteOrderInfo(data, error, task.task_last);
};

void TdApi::processRspQryForQuote(Task task)
{
	PyLock lock;
	DFITCQryForQuoteRtnField task_data = any_cast<DFITCQryForQuoteRtnField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["lRequestID"] = task_data.lRequestID;
	data["orderStatus"] = task_data.orderStatus;
	data["spdOrderID"] = task_data.spdOrderID;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryForQuote(data, error, task.task_last);
};

void TdApi::processRspQryTransferBank(Task task)
{
	PyLock lock;
	DFITCTransferBankRspField task_data = any_cast<DFITCTransferBankRspField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["registDate"] = task_data.registDate;
	data["currency"] = task_data.currency;
	data["lRequestID"] = task_data.lRequestID;
	data["bankID"] = task_data.bankID;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryTransferBank(data, error, task.task_last);
};

void TdApi::processRspQryTransferSerial(Task task)
{
	PyLock lock;
	DFITCTransferSerialRspField task_data = any_cast<DFITCTransferSerialRspField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["curFutAccountFund"] = task_data.curFutAccountFund;
	data["bankSerialNum"] = task_data.bankSerialNum;
	data["procResult"] = task_data.procResult;
	data["currency"] = task_data.currency;
	data["lRequestID"] = task_data.lRequestID;
	data["applyNum"] = task_data.applyNum;
	data["dealTransferTime"] = task_data.dealTransferTime;
	data["bankID"] = task_data.bankID;
	data["reqTransferTime"] = task_data.reqTransferTime;
	data["type"] = task_data.type;
	data["tradeAmount"] = task_data.tradeAmount;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryTransferSerial(data, error, task.task_last);
};

void TdApi::processRspFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	DFITCTransferRspField task_data = any_cast<DFITCTransferRspField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["applyNumber"] = task_data.applyNumber;
	data["lRequestID"] = task_data.lRequestID;
	data["bankID"] = task_data.bankID;
	data["tradeAmount"] = task_data.tradeAmount;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspFromBankToFutureByFuture(data, error);
};

void TdApi::processRspFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	DFITCTransferRspField task_data = any_cast<DFITCTransferRspField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["applyNumber"] = task_data.applyNumber;
	data["lRequestID"] = task_data.lRequestID;
	data["bankID"] = task_data.bankID;
	data["tradeAmount"] = task_data.tradeAmount;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspFromFutureToBankByFuture(data, error);
};

void TdApi::processRtnFromBankToFutureByFuture(Task task)
{
	PyLock lock;
	DFITCTransferRtnField task_data = any_cast<DFITCTransferRtnField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["bankSerialNum"] = task_data.bankSerialNum;
	data["applyNumber"] = task_data.applyNumber;
	data["sessionID"] = task_data.sessionID;
	data["bankID"] = task_data.bankID;
	data["type"] = task_data.type;
	data["tradeAmount"] = task_data.tradeAmount;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRtnFromBankToFutureByFuture(data, error);
};

void TdApi::processRtnFromFutureToBankByFuture(Task task)
{
	PyLock lock;
	DFITCTransferRtnField task_data = any_cast<DFITCTransferRtnField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["bankSerialNum"] = task_data.bankSerialNum;
	data["applyNumber"] = task_data.applyNumber;
	data["sessionID"] = task_data.sessionID;
	data["bankID"] = task_data.bankID;
	data["type"] = task_data.type;
	data["tradeAmount"] = task_data.tradeAmount;
	data["accountID"] = task_data.accountID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRtnFromFutureToBankByFuture(data, error);
};

void TdApi::processRtnRepealFromFutureToBankByBank(Task task)
{
	PyLock lock;
	DFITCRepealRtnField task_data = any_cast<DFITCRepealRtnField>(task.task_data);
	dict data;
	data["bankAccount"] = task_data.bankAccount;
	data["bankSerialNum"] = task_data.bankSerialNum;
	data["repealSerial"] = task_data.repealSerial;
	data["bankID"] = task_data.bankID;
	data["type"] = task_data.type;
	data["tradeAmount"] = task_data.tradeAmount;
	data["accountID"] = task_data.accountID;

	this->onRtnRepealFromFutureToBankByBank(data);
};

void TdApi::processRspQryExchangeStatus(Task task)
{
	PyLock lock;
	DFITCExchangeStatusRspField task_data = any_cast<DFITCExchangeStatusRspField>(task.task_data);
	dict data;
	data["lRequestID"] = task_data.lRequestID;
	data["exchangeStatus"] = task_data.exchangeStatus;
	data["exchangeID"] = task_data.exchangeID;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryExchangeStatus(data, error, task.task_last);
};

void TdApi::processRtnExchangeStatus(Task task)
{
	PyLock lock;
	DFITCExchangeStatusRtnField task_data = any_cast<DFITCExchangeStatusRtnField>(task.task_data);
	dict data;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["exchangeStatus"] = task_data.exchangeStatus;

	this->onRtnExchangeStatus(data);
};

void TdApi::processRspQryDepthMarketData(Task task)
{
	PyLock lock;
	DFITCDepthMarketDataField task_data = any_cast<DFITCDepthMarketDataField>(task.task_data);
	dict data;
	data["BidPrice5"] = task_data.BidPrice5;
	data["BidPrice4"] = task_data.BidPrice4;
	data["BidPrice1"] = task_data.BidPrice1;
	data["openPrice"] = task_data.openPrice;
	data["BidPrice2"] = task_data.BidPrice2;
	data["AskPrice5"] = task_data.AskPrice5;
	data["AskPrice4"] = task_data.AskPrice4;
	data["AskPrice3"] = task_data.AskPrice3;
	data["AskPrice2"] = task_data.AskPrice2;
	data["AskPrice1"] = task_data.AskPrice1;
	data["closePrice"] = task_data.closePrice;
	data["UpdateTime"] = task_data.UpdateTime;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["AveragePrice"] = task_data.AveragePrice;
	data["BidVolume5"] = task_data.BidVolume5;
	data["BidVolume4"] = task_data.BidVolume4;
	data["BidVolume3"] = task_data.BidVolume3;
	data["BidVolume2"] = task_data.BidVolume2;
	data["BidVolume1"] = task_data.BidVolume1;
	data["Volume"] = task_data.Volume;
	data["tradingDay"] = task_data.tradingDay;
	data["AskVolume3"] = task_data.AskVolume3;
	data["AskVolume2"] = task_data.AskVolume2;
	data["lowerLimitPrice"] = task_data.lowerLimitPrice;
	data["AskVolume4"] = task_data.AskVolume4;
	data["preDelta"] = task_data.preDelta;
	data["AskVolume5"] = task_data.AskVolume5;
	data["openInterest"] = task_data.openInterest;
	data["currDelta"] = task_data.currDelta;
	data["preClosePrice"] = task_data.preClosePrice;
	data["preSettlementPrice"] = task_data.preSettlementPrice;
	data["lastPrice"] = task_data.lastPrice;
	data["AskVolume1"] = task_data.AskVolume1;
	data["settlementPrice"] = task_data.settlementPrice;
	data["preOpenInterest"] = task_data.preOpenInterest;
	data["exchangeInstID"] = task_data.exchangeInstID;
	data["XSpeedTime"] = task_data.XSpeedTime;
	data["BidPrice3"] = task_data.BidPrice3;
	data["upperLimitPrice"] = task_data.upperLimitPrice;
	data["lowestPrice"] = task_data.lowestPrice;
	data["instrumentID"] = task_data.instrumentID;
	data["exchangeID"] = task_data.exchangeID;
	data["highestPrice"] = task_data.highestPrice;
	data["turnover"] = task_data.turnover;

	DFITCErrorRtnField task_error = any_cast<DFITCErrorRtnField>(task.task_error);
	dict error;
	error["instrumentID"] = task_error.instrumentID;
	error["localOrderID"] = task_error.localOrderID;
	error["errorMsg"] = task_error.errorMsg;
	error["sessionID"] = task_error.sessionID;
	error["nErrorID"] = task_error.nErrorID;
	error["requestID"] = task_error.requestID;
	error["spdOrderID"] = task_error.spdOrderID;
	error["accountID"] = task_error.accountID;

	this->onRspQryDepthMarketData(data, error, task.task_last);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::createDFITCTraderApi()
{
	this->api = DFITCTraderApi::CreateDFITCTraderApi();
};

void TdApi::release()
{
	this->api->Release();
};

void TdApi::init(string pszSvrAddr)
{
	this->api->Init((char*)pszSvrAddr.c_str(), this);
};

int TdApi::exit()
{
	this->api->Release();
	this->api = NULL;
	return 1;
};

int TdApi::reqEquityComputMode()
{
	return this->api->ReqEquityComputMode();
}

int TdApi::reqUserLogin(dict req)
{
	DFITCUserLoginField myreq = DFITCUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "passwd", myreq.passwd);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getShort(req, "companyID", &myreq.companyID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqUserLogin(&myreq);
	return i;
};

int TdApi::reqUserLogout(dict req)
{
	DFITCUserLogoutField myreq = DFITCUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getLong(req, "sessionID", &myreq.sessionID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqUserLogout(&myreq);
	return i;
};

int TdApi::reqInsertOrder(dict req)
{
	DFITCInsertOrderField myreq = DFITCInsertOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getInt(req, "openCloseType", &myreq.openCloseType);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getDouble(req, "insertPrice", &myreq.insertPrice);
	getChar(req, "orderProperty", &myreq.orderProperty);
	getShort(req, "buySellType", &myreq.buySellType);
	getInt(req, "orderType", &myreq.orderType);
	getLong(req, "minMatchAmount", &myreq.minMatchAmount);
	getInt(req, "speculator", &myreq.speculator);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getInt(req, "reservedType2", &myreq.reservedType2);
	getInt(req, "insertType", &myreq.insertType);
	getLong(req, "orderAmount", &myreq.orderAmount);
	getDouble(req, "profitLossPrice", &myreq.profitLossPrice);
	getString(req, "customCategory", myreq.customCategory);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqInsertOrder(&myreq);
	return i;
};

int TdApi::reqCancelOrder(dict req)
{
	DFITCCancelOrderField myreq = DFITCCancelOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getLong(req, "spdOrderID", &myreq.spdOrderID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqCancelOrder(&myreq);
	return i;
};

int TdApi::reqQryPosition(dict req)
{
	DFITCPositionField myreq = DFITCPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryPosition(&myreq);
	return i;
};

int TdApi::reqQryCustomerCapital(dict req)
{
	DFITCCapitalField myreq = DFITCCapitalField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryCustomerCapital(&myreq);
	return i;
};

int TdApi::reqQryExchangeInstrument(dict req)
{
	DFITCExchangeInstrumentField myreq = DFITCExchangeInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "instrumentType", &myreq.instrumentType);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryExchangeInstrument(&myreq);
	return i;
};

int TdApi::reqQryArbitrageInstrument(dict req)
{
	DFITCAbiInstrumentField myreq = DFITCAbiInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryArbitrageInstrument(&myreq);
	return i;
};

int TdApi::reqQryOrderInfo(dict req)
{
	DFITCOrderField myreq = DFITCOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getInt(req, "orderType", &myreq.orderType);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getShort(req, "orderStatus", &myreq.orderStatus);
	getString(req, "customCategory", myreq.customCategory);
	getLong(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryOrderInfo(&myreq);
	return i;
};

int TdApi::reqQryMatchInfo(dict req)
{
	DFITCMatchField myreq = DFITCMatchField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getInt(req, "orderType", &myreq.orderType);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "customCategory", myreq.customCategory);
	getLong(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryMatchInfo(&myreq);
	return i;
};

int TdApi::reqQrySpecifyInstrument(dict req)
{
	DFITCSpecificInstrumentField myreq = DFITCSpecificInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "InstrumentID", myreq.InstrumentID);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQrySpecifyInstrument(&myreq);
	return i;
};

int TdApi::reqQryPositionDetail(dict req)
{
	DFITCPositionDetailField myreq = DFITCPositionDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryPositionDetail(&myreq);
	return i;
};

int TdApi::reqConfirmProductInfo(dict req)
{
	DFITCProductField myreq = DFITCProductField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "vendorID", myreq.vendorID);
	getString(req, "productID", myreq.productID);
	int i = this->api->ReqConfirmProductInfo(&myreq);
	return i;
};

int TdApi::reqResetPassword(dict req)
{
	DFITCResetPwdField myreq = DFITCResetPwdField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "oldpasswd", myreq.oldpasswd);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "newpasswd", myreq.newpasswd);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqResetPassword(&myreq);
	return i;
};

int TdApi::reqBillConfirm(dict req)
{
	DFITCBillConfirmField myreq = DFITCBillConfirmField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "date", myreq.date);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getInt(req, "confirmFlag", &myreq.confirmFlag);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqBillConfirm(&myreq);
	return i;
};

int TdApi::reqQryTradeCode(dict req)
{
	DFITCQryTradeCodeField myreq = DFITCQryTradeCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryTradeCode(&myreq);
	return i;
};

int TdApi::reqQryBill(dict req)
{
	DFITCQryBillField myreq = DFITCQryBillField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "date", myreq.date);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryBill(&myreq);
	return i;
};

int TdApi::reqTradingDay(dict req)
{
	DFITCTradingDayField myreq = DFITCTradingDayField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	int i = this->api->ReqTradingDay(&myreq);
	return i;
};

int TdApi::reqQryQuoteNotice(dict req)
{
	DFITCQryQuoteNoticeField myreq = DFITCQryQuoteNoticeField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryQuoteNotice(&myreq);
	return i;
};

int TdApi::reqQuoteInsert(dict req)
{
	DFITCQuoteInsertField myreq = DFITCQuoteInsertField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getInt(req, "stayTime", &myreq.stayTime);
	getInt(req, "sSpeculator", &myreq.sSpeculator);
	getString(req, "quoteID", myreq.quoteID);
	getInt(req, "sOpenCloseType", &myreq.sOpenCloseType);
	getLong(req, "bOrderAmount", &myreq.bOrderAmount);
	getDouble(req, "sInsertPrice", &myreq.sInsertPrice);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getInt(req, "insertType", &myreq.insertType);
	getLong(req, "sOrderAmount", &myreq.sOrderAmount);
	getInt(req, "bOpenCloseType", &myreq.bOpenCloseType);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getInt(req, "bSpeculator", &myreq.bSpeculator);
	getString(req, "customCategory", myreq.customCategory);
	getDouble(req, "bInsertPrice", &myreq.bInsertPrice);
	getInt(req, "instrumentType", &myreq.instrumentType);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQuoteInsert(&myreq);
	return i;
};

int TdApi::reqQuoteCancel(dict req)
{
	DFITCCancelOrderField myreq = DFITCCancelOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getLong(req, "spdOrderID", &myreq.spdOrderID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQuoteCancel(&myreq);
	return i;
};

int TdApi::reqCancelAllOrder(dict req)
{
	DFITCCancelAllOrderField myreq = DFITCCancelAllOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqCancelAllOrder(&myreq);
	return i;
};

int TdApi::reqForQuote(dict req)
{
	DFITCForQuoteField myreq = DFITCForQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqForQuote(&myreq);
	return i;
};

int TdApi::reqQryForQuote(dict req)
{
	DFITCQryForQuoteField myreq = DFITCQryForQuoteField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryForQuote(&myreq);
	return i;
};

int TdApi::reqQryQuoteOrderInfo(dict req)
{
	DFITCQuoteOrderField myreq = DFITCQuoteOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getString(req, "exchangeID", myreq.exchangeID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getShort(req, "orderStatus", &myreq.orderStatus);
	getLong(req, "spdOrderID", &myreq.spdOrderID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryQuoteOrderInfo(&myreq);
	return i;
};

int TdApi::reqQryTransferBank(dict req)
{
	DFITCQryTransferBankField myreq = DFITCQryTransferBankField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "bankID", myreq.bankID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryTransferBank(&myreq);
	return i;
};

int TdApi::reqQryTransferSerial(dict req)
{
	DFITCQryTransferSerialField myreq = DFITCQryTransferSerialField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "bankAccount", myreq.bankAccount);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "bankID", myreq.bankID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqQryTransferSerial(&myreq);
	return i;
};

int TdApi::reqFromBankToFutureByFuture(dict req)
{
	DFITCReqTransferField myreq = DFITCReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "bankAccount", myreq.bankAccount);
	getString(req, "bankPassword", myreq.bankPassword);
	getString(req, "currency", myreq.currency);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "bankID", myreq.bankID);
	getString(req, "password", myreq.password);
	getDouble(req, "tradeAmount", &myreq.tradeAmount);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFromBankToFutureByFuture(&myreq);
	return i;
};

int TdApi::reqFromFutureToBankByFuture(dict req)
{
	DFITCReqTransferField myreq = DFITCReqTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "bankAccount", myreq.bankAccount);
	getString(req, "bankPassword", myreq.bankPassword);
	getString(req, "currency", myreq.currency);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "bankID", myreq.bankID);
	getString(req, "password", myreq.password);
	getDouble(req, "tradeAmount", &myreq.tradeAmount);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFromFutureToBankByFuture(&myreq);
	return i;
};

int TdApi::reqQryExchangeStatus(dict req)
{
	DFITCQryExchangeStatusField myreq = DFITCQryExchangeStatusField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqQryExchangeStatus(&myreq);
	return i;
};

int TdApi::reqQryDepthMarketData(dict req)
{
	DFITCQryDepthMarketDataField myreq = DFITCQryDepthMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "instrumentID", myreq.instrumentID);
	getLong(req, "lRequestID", &myreq.lRequestID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqQryDepthMarketData(&myreq);
	return i;
};


///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

struct TdApiWrap : TdApi, wrapper < TdApi >
{
	virtual void onFrontConnected()
	{
		//以下的try...catch...可以实现捕捉python环境中错误的功能，防止C++直接出现原因未知的崩溃
		try
		{
			this->get_override("onFrontConnected")();
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onFrontDisconnected(int i)
	{
		try
		{
			this->get_override("onFrontDisconnected")(i);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUserLogin(dict data, dict error)
	{
		try
		{
			this->get_override("onRspUserLogin")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUserLogout(dict data, dict error)
	{
		try
		{
			this->get_override("onRspUserLogout")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspInsertOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRspInsertOrder")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspCancelOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRspCancelOrder")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnErrorMsg(dict data)
	{
		try
		{
			this->get_override("onRtnErrorMsg")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnMatchedInfo(dict data)
	{
		try
		{
			this->get_override("onRtnMatchedInfo")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnOrder(dict data)
	{
		try
		{
			this->get_override("onRtnOrder")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnCancelOrder(dict data)
	{
		try
		{
			this->get_override("onRtnCancelOrder")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryOrderInfo(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryOrderInfo")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryMatchInfo(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryMatchInfo")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryPosition(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryPosition")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspCustomerCapital(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspCustomerCapital")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryExchangeInstrument(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryExchangeInstrument")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspArbitrageInstrument(dict data, dict error)
	{
		try
		{
			this->get_override("onRspArbitrageInstrument")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQrySpecifyInstrument(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQrySpecifyInstrument")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryPositionDetail(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryPositionDetail")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnTradingNotice(dict data)
	{
		try
		{
			this->get_override("onRtnTradingNotice")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspResetPassword(dict data, dict error)
	{
		try
		{
			this->get_override("onRspResetPassword")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryTradeCode(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryTradeCode")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspBillConfirm(dict data, dict error)
	{
		try
		{
			this->get_override("onRspBillConfirm")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspEquityComputMode(dict data, dict error)
	{
		try
		{
			this->get_override("onRspEquityComputMode")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryBill(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryBill")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspConfirmProductInfo(dict data, dict error)
	{
		try
		{
			this->get_override("onRspConfirmProductInfo")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspTradingDay(dict data, dict error)
	{
		try
		{
			this->get_override("onRspTradingDay")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQuoteInsert(dict data, dict error)
	{
		try
		{
			this->get_override("onRspQuoteInsert")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnQuoteInsert(dict data)
	{
		try
		{
			this->get_override("onRtnQuoteInsert")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQuoteCancel(dict data, dict error)
	{
		try
		{
			this->get_override("onRspQuoteCancel")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnQuoteCancel(dict data)
	{
		try
		{
			this->get_override("onRtnQuoteCancel")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnQuoteMatchedInfo(dict data)
	{
		try
		{
			this->get_override("onRtnQuoteMatchedInfo")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspCancelAllOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRspCancelAllOrder")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryQuoteNotice(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryQuoteNotice")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspForQuote(dict data, dict error)
	{
		try
		{
			this->get_override("onRspForQuote")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnForQuote(dict data)
	{
		try
		{
			this->get_override("onRtnForQuote")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryQuoteOrderInfo(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryQuoteOrderInfo")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryForQuote(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryForQuote")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryTransferBank(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryTransferBank")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryTransferSerial(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryTransferSerial")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFromBankToFutureByFuture(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFromBankToFutureByFuture")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFromFutureToBankByFuture(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFromFutureToBankByFuture")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnFromBankToFutureByFuture(dict data)
	{
		try
		{
			this->get_override("onRtnFromBankToFutureByFuture")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnFromFutureToBankByFuture(dict data)
	{
		try
		{
			this->get_override("onRtnFromFutureToBankByFuture")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnRepealFromFutureToBankByBank(dict data)
	{
		try
		{
			this->get_override("onRtnRepealFromFutureToBankByBank")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryExchangeStatus(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryExchangeStatus")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnExchangeStatus(dict data)
	{
		try
		{
			this->get_override("onRtnExchangeStatus")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryDepthMarketData(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onRspQryDepthMarketData")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};
};


BOOST_PYTHON_MODULE(vnxspeedtd)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<TdApiWrap, boost::noncopyable>("TdApi")
		.def("createDFITCTraderApi", &TdApiWrap::createDFITCTraderApi)
		.def("release", &TdApiWrap::release)
		.def("init", &TdApiWrap::init)
		.def("exit", &TdApiWrap::exit)
		.def("reqUserLogin", &TdApiWrap::reqUserLogin)
		.def("reqUserLogout", &TdApiWrap::reqUserLogout)
		.def("reqInsertOrder", &TdApiWrap::reqInsertOrder)
		.def("reqCancelOrder", &TdApiWrap::reqCancelOrder)
		.def("reqQryPosition", &TdApiWrap::reqQryPosition)
		.def("reqQryCustomerCapital", &TdApiWrap::reqQryCustomerCapital)
		.def("reqQryExchangeInstrument", &TdApiWrap::reqQryExchangeInstrument)
		.def("reqQryArbitrageInstrument", &TdApiWrap::reqQryArbitrageInstrument)
		.def("reqQryOrderInfo", &TdApiWrap::reqQryOrderInfo)
		.def("reqQryMatchInfo", &TdApiWrap::reqQryMatchInfo)
		.def("reqQrySpecifyInstrument", &TdApiWrap::reqQrySpecifyInstrument)
		.def("reqQryPositionDetail", &TdApiWrap::reqQryPositionDetail)
		.def("reqConfirmProductInfo", &TdApiWrap::reqConfirmProductInfo)
		.def("reqResetPassword", &TdApiWrap::reqResetPassword)
		.def("reqBillConfirm", &TdApiWrap::reqBillConfirm)
		.def("reqQryTradeCode", &TdApiWrap::reqQryTradeCode)
		.def("reqEquityComputMode", &TdApiWrap::reqEquityComputMode)
		.def("reqQryBill", &TdApiWrap::reqQryBill)
		.def("reqTradingDay", &TdApiWrap::reqTradingDay)
		.def("reqQryQuoteNotice", &TdApiWrap::reqQryQuoteNotice)
		.def("reqQuoteInsert", &TdApiWrap::reqQuoteInsert)
		.def("reqQuoteCancel", &TdApiWrap::reqQuoteCancel)
		.def("reqCancelAllOrder", &TdApiWrap::reqCancelAllOrder)
		.def("reqForQuote", &TdApiWrap::reqForQuote)
		.def("reqQryForQuote", &TdApiWrap::reqQryForQuote)
		.def("reqQryQuoteOrderInfo", &TdApiWrap::reqQryQuoteOrderInfo)
		.def("reqQryTransferBank", &TdApiWrap::reqQryTransferBank)
		.def("reqQryTransferSerial", &TdApiWrap::reqQryTransferSerial)
		.def("reqFromBankToFutureByFuture", &TdApiWrap::reqFromBankToFutureByFuture)
		.def("reqFromFutureToBankByFuture", &TdApiWrap::reqFromFutureToBankByFuture)
		.def("reqQryExchangeStatus", &TdApiWrap::reqQryExchangeStatus)
		.def("reqQryDepthMarketData", &TdApiWrap::reqQryDepthMarketData)

		.def("onFrontConnected", pure_virtual(&TdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&TdApiWrap::onFrontDisconnected))
		.def("onRspUserLogin", pure_virtual(&TdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&TdApiWrap::onRspUserLogout))
		.def("onRspInsertOrder", pure_virtual(&TdApiWrap::onRspInsertOrder))
		.def("onRspCancelOrder", pure_virtual(&TdApiWrap::onRspCancelOrder))
		.def("onRtnErrorMsg", pure_virtual(&TdApiWrap::onRtnErrorMsg))
		.def("onRtnMatchedInfo", pure_virtual(&TdApiWrap::onRtnMatchedInfo))
		.def("onRtnOrder", pure_virtual(&TdApiWrap::onRtnOrder))
		.def("onRtnCancelOrder", pure_virtual(&TdApiWrap::onRtnCancelOrder))
		.def("onRspQryOrderInfo", pure_virtual(&TdApiWrap::onRspQryOrderInfo))
		.def("onRspQryMatchInfo", pure_virtual(&TdApiWrap::onRspQryMatchInfo))
		.def("onRspQryPosition", pure_virtual(&TdApiWrap::onRspQryPosition))
		.def("onRspCustomerCapital", pure_virtual(&TdApiWrap::onRspCustomerCapital))
		.def("onRspQryExchangeInstrument", pure_virtual(&TdApiWrap::onRspQryExchangeInstrument))
		.def("onRspArbitrageInstrument", pure_virtual(&TdApiWrap::onRspArbitrageInstrument))
		.def("onRspQrySpecifyInstrument", pure_virtual(&TdApiWrap::onRspQrySpecifyInstrument))
		.def("onRspQryPositionDetail", pure_virtual(&TdApiWrap::onRspQryPositionDetail))
		.def("onRtnTradingNotice", pure_virtual(&TdApiWrap::onRtnTradingNotice))
		.def("onRspResetPassword", pure_virtual(&TdApiWrap::onRspResetPassword))
		.def("onnRspQryTradeCode", pure_virtual(&TdApiWrap::onnRspQryTradeCode))
		.def("onRspBillConfirm", pure_virtual(&TdApiWrap::onRspBillConfirm))
		.def("onnRspEquityComputMode", pure_virtual(&TdApiWrap::onnRspEquityComputMode))
		.def("onRspQryBill", pure_virtual(&TdApiWrap::onRspQryBill))
		.def("onRspConfirmProductInfo", pure_virtual(&TdApiWrap::onRspConfirmProductInfo))
		.def("onRspTradingDay", pure_virtual(&TdApiWrap::onRspTradingDay))
		.def("onRspQuoteInsert", pure_virtual(&TdApiWrap::onRspQuoteInsert))
		.def("onRtnQuoteInsert", pure_virtual(&TdApiWrap::onRtnQuoteInsert))
		.def("onRspQuoteCancel", pure_virtual(&TdApiWrap::onRspQuoteCancel))
		.def("onRtnQuoteCancel", pure_virtual(&TdApiWrap::onRtnQuoteCancel))
		.def("onRtnQuoteMatchedInfo", pure_virtual(&TdApiWrap::onRtnQuoteMatchedInfo))
		.def("onRspCancelAllOrder", pure_virtual(&TdApiWrap::onRspCancelAllOrder))
		.def("onRspQryQuoteNotice", pure_virtual(&TdApiWrap::onRspQryQuoteNotice))
		.def("onRspForQuote", pure_virtual(&TdApiWrap::onRspForQuote))
		.def("onRtnForQuote", pure_virtual(&TdApiWrap::onRtnForQuote))
		.def("onRspQryQuoteOrderInfo", pure_virtual(&TdApiWrap::onRspQryQuoteOrderInfo))
		.def("onRspQryForQuote", pure_virtual(&TdApiWrap::onRspQryForQuote))
		.def("onRspQryTransferBank", pure_virtual(&TdApiWrap::onRspQryTransferBank))
		.def("onRspQryTransferSerial", pure_virtual(&TdApiWrap::onRspQryTransferSerial))
		.def("onRspFromBankToFutureByFuture", pure_virtual(&TdApiWrap::onRspFromBankToFutureByFuture))
		.def("onRspFromFutureToBankByFuture", pure_virtual(&TdApiWrap::onRspFromFutureToBankByFuture))
		.def("onRtnFromBankToFutureByFuture", pure_virtual(&TdApiWrap::onRtnFromBankToFutureByFuture))
		.def("onRtnFromFutureToBankByFuture", pure_virtual(&TdApiWrap::onRtnFromFutureToBankByFuture))
		.def("onRtnRepealFromFutureToBankByBank", pure_virtual(&TdApiWrap::onRtnRepealFromFutureToBankByBank))
		.def("onRspQryExchangeStatus", pure_virtual(&TdApiWrap::onRspQryExchangeStatus))
		.def("onRtnExchangeStatus", pure_virtual(&TdApiWrap::onRtnExchangeStatus))
		.def("onRspQryDepthMarketData", pure_virtual(&TdApiWrap::onRspQryDepthMarketData))
		.def("onRspQryTradeCode", pure_virtual(&TdApiWrap::onRspQryTradeCode))
		.def("onRspEquityComputMode", pure_virtual(&TdApiWrap::onRspEquityComputMode))
		;
};