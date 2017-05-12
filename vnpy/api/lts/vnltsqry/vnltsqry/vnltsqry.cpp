// MdApi.cpp : 定义 DLL 应用程序的导出函数。
//

#ifdef WIN32
#include "stdafx.h"
#endif
#include "vnltsqry.h"



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
}

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
}

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
			//对字符串指针赋值必须使用strcpy_s, vs2013使用strcpy编译通不过
			//+1应该是因为C++字符串的结尾符号？不是特别确定，不加这个1会出错
        #ifdef WIN32
			strcpy_s(value, strlen(buffer) + 1, buffer);
        #else
			strncpy(value, buffer, strlen(buffer) + 1);
        #endif
		}
	}
}



///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void QryApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void QryApi::OnFrontDisconnected(int nReason)
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;
	task.task_id = nReason;
	this->task_queue.push(task);
};

void QryApi::OnHeartBeatWarning(int nTimeLapse)
{
	Task task = Task();
	task.task_name = ONHEARTBEATWARNING;
	task.task_id = nTimeLapse;
	;
	this->task_queue.push(task);
};

void QryApi::OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPERROR;

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;

	if (pRspUserLogin)
	{
		task.task_data = *pRspUserLogin;
	}
	else
	{
		CSecurityFtdcRspUserLoginField empty_data = CSecurityFtdcRspUserLoginField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;

	if (pUserLogout)
	{
		task.task_data = *pUserLogout;
	}
	else
	{
		CSecurityFtdcUserLogoutField empty_data = CSecurityFtdcUserLogoutField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspFetchAuthRandCode(CSecurityFtdcAuthRandCodeField *pAuthRandCode, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFETCHAUTHRANDCODE;

	if (pAuthRandCode)
	{
		task.task_data = *pAuthRandCode;
	}
	else
	{
		CSecurityFtdcAuthRandCodeField empty_data = CSecurityFtdcAuthRandCodeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryExchange(CSecurityFtdcExchangeField *pExchange, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGE;

	if (pExchange)
	{
		task.task_data = *pExchange;
	}
	else
	{
		CSecurityFtdcExchangeField empty_data = CSecurityFtdcExchangeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryInstrument(CSecurityFtdcInstrumentField *pInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENT;

	if (pInstrument)
	{
		task.task_data = *pInstrument;
	}
	else
	{
		CSecurityFtdcInstrumentField empty_data = CSecurityFtdcInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryInvestor(CSecurityFtdcInvestorField *pInvestor, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTOR;

	if (pInvestor)
	{
		task.task_data = *pInvestor;
	}
	else
	{
		CSecurityFtdcInvestorField empty_data = CSecurityFtdcInvestorField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryTradingCode(CSecurityFtdcTradingCodeField *pTradingCode, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGCODE;

	if (pTradingCode)
	{
		task.task_data = *pTradingCode;
	}
	else
	{
		CSecurityFtdcTradingCodeField empty_data = CSecurityFtdcTradingCodeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryTradingAccount(CSecurityFtdcTradingAccountField *pTradingAccount, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGACCOUNT;

	if (pTradingAccount)
	{
		task.task_data = *pTradingAccount;
	}
	else
	{
		CSecurityFtdcTradingAccountField empty_data = CSecurityFtdcTradingAccountField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryBondInterest(CSecurityFtdcBondInterestField *pBondInterest, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYBONDINTEREST;

	if (pBondInterest)
	{
		task.task_data = *pBondInterest;
	}
	else
	{
		CSecurityFtdcBondInterestField empty_data = CSecurityFtdcBondInterestField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryMarketRationInfo(CSecurityFtdcMarketRationInfoField *pMarketRationInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYMARKETRATIONINFO;

	if (pMarketRationInfo)
	{
		task.task_data = *pMarketRationInfo;
	}
	else
	{
		CSecurityFtdcMarketRationInfoField empty_data = CSecurityFtdcMarketRationInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryInstrumentCommissionRate(CSecurityFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENTCOMMISSIONRATE;

	if (pInstrumentCommissionRate)
	{
		task.task_data = *pInstrumentCommissionRate;
	}
	else
	{
		CSecurityFtdcInstrumentCommissionRateField empty_data = CSecurityFtdcInstrumentCommissionRateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryETFInstrument(CSecurityFtdcETFInstrumentField *pETFInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYETFINSTRUMENT;

	if (pETFInstrument)
	{
		task.task_data = *pETFInstrument;
	}
	else
	{
		CSecurityFtdcETFInstrumentField empty_data = CSecurityFtdcETFInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryETFBasket(CSecurityFtdcETFBasketField *pETFBasket, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYETFBASKET;

	if (pETFBasket)
	{
		task.task_data = *pETFBasket;
	}
	else
	{
		CSecurityFtdcETFBasketField empty_data = CSecurityFtdcETFBasketField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryOFInstrument(CSecurityFtdcOFInstrumentField *pOFInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYOFINSTRUMENT;

	if (pOFInstrument)
	{
		task.task_data = *pOFInstrument;
	}
	else
	{
		CSecurityFtdcOFInstrumentField empty_data = CSecurityFtdcOFInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQrySFInstrument(CSecurityFtdcSFInstrumentField *pSFInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYSFINSTRUMENT;

	if (pSFInstrument)
	{
		task.task_data = *pSFInstrument;
	}
	else
	{
		CSecurityFtdcSFInstrumentField empty_data = CSecurityFtdcSFInstrumentField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryInstrumentUnitMargin(CSecurityFtdcInstrumentUnitMarginField *pInstrumentUnitMargin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENTUNITMARGIN;

	if (pInstrumentUnitMargin)
	{
		task.task_data = *pInstrumentUnitMargin;
	}
	else
	{
		CSecurityFtdcInstrumentUnitMarginField empty_data = CSecurityFtdcInstrumentUnitMarginField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryPreDelivInfo(CSecurityFtdcPreDelivInfoField *pPreDelivInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYPREDELIVINFO;

	if (pPreDelivInfo)
	{
		task.task_data = *pPreDelivInfo;
	}
	else
	{
		CSecurityFtdcPreDelivInfoField empty_data = CSecurityFtdcPreDelivInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryCreditStockAssignInfo(CSecurityFtdcCreditStockAssignInfoField *pCreditStockAssignInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCREDITSTOCKASSIGNINFO;

	if (pCreditStockAssignInfo)
	{
		task.task_data = *pCreditStockAssignInfo;
	}
	else
	{
		CSecurityFtdcCreditStockAssignInfoField empty_data = CSecurityFtdcCreditStockAssignInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryCreditCashAssignInfo(CSecurityFtdcCreditCashAssignInfoField *pCreditCashAssignInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCREDITCASHASSIGNINFO;

	if (pCreditCashAssignInfo)
	{
		task.task_data = *pCreditCashAssignInfo;
	}
	else
	{
		CSecurityFtdcCreditCashAssignInfoField empty_data = CSecurityFtdcCreditCashAssignInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryConversionRate(CSecurityFtdcConversionRateField *pConversionRate, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYCONVERSIONRATE;

	if (pConversionRate)
	{
		task.task_data = *pConversionRate;
	}
	else
	{
		CSecurityFtdcConversionRateField empty_data = CSecurityFtdcConversionRateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryHisCreditDebtInfo(CSecurityFtdcHisCreditDebtInfoField *pHisCreditDebtInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYHISCREDITDEBTINFO;

	if (pHisCreditDebtInfo)
	{
		task.task_data = *pHisCreditDebtInfo;
	}
	else
	{
		CSecurityFtdcHisCreditDebtInfoField empty_data = CSecurityFtdcHisCreditDebtInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryMarketDataStaticInfo(CSecurityFtdcMarketDataStaticInfoField *pMarketDataStaticInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYMARKETDATASTATICINFO;

	if (pMarketDataStaticInfo)
	{
		task.task_data = *pMarketDataStaticInfo;
	}
	else
	{
		CSecurityFtdcMarketDataStaticInfoField empty_data = CSecurityFtdcMarketDataStaticInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryExpireRepurchInfo(CSecurityFtdcExpireRepurchInfoField *pExpireRepurchInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXPIREREPURCHINFO;

	if (pExpireRepurchInfo)
	{
		task.task_data = *pExpireRepurchInfo;
	}
	else
	{
		CSecurityFtdcExpireRepurchInfoField empty_data = CSecurityFtdcExpireRepurchInfoField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryBondPledgeRate(CSecurityFtdcBondPledgeRateField *pBondPledgeRate, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYBONDPLEDGERATE;

	if (pBondPledgeRate)
	{
		task.task_data = *pBondPledgeRate;
	}
	else
	{
		CSecurityFtdcBondPledgeRateField empty_data = CSecurityFtdcBondPledgeRateField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryPledgeBond(CSecurityFtdcPledgeBondField *pPledgeBond, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYPLEDGEBOND;

	if (pPledgeBond)
	{
		task.task_data = *pPledgeBond;
	}
	else
	{
		CSecurityFtdcPledgeBondField empty_data = CSecurityFtdcPledgeBondField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryOrder(CSecurityFtdcOrderField *pOrder, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;

	if (pOrder)
	{
		task.task_data = *pOrder;
	}
	else
	{
		CSecurityFtdcOrderField empty_data = CSecurityFtdcOrderField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryTrade(CSecurityFtdcTradeField *pTrade, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADE;

	if (pTrade)
	{
		task.task_data = *pTrade;
	}
	else
	{
		CSecurityFtdcTradeField empty_data = CSecurityFtdcTradeField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryInvestorPosition(CSecurityFtdcInvestorPositionField *pInvestorPosition, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITION;

	if (pInvestorPosition)
	{
		task.task_data = *pInvestorPosition;
	}
	else
	{
		CSecurityFtdcInvestorPositionField empty_data = CSecurityFtdcInvestorPositionField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryFundTransferSerial(CSecurityFtdcFundTransferField *pFundTransfer, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYFUNDTRANSFERSERIAL;

	if (pFundTransfer)
	{
		task.task_data = *pFundTransfer;
	}
	else
	{
		CSecurityFtdcFundTransferField empty_data = CSecurityFtdcFundTransferField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};

void QryApi::OnRspQryFundInterTransferSerial(CSecurityFtdcFundInterTransferSerialField *pFundInterTransferSerial, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYFUNDINTERTRANSFERSERIAL;

	if (pFundInterTransferSerial)
	{
		task.task_data = *pFundInterTransferSerial;
	}
	else
	{
		CSecurityFtdcFundInterTransferSerialField empty_data = CSecurityFtdcFundInterTransferSerialField();
		memset(&empty_data, 0, sizeof(empty_data));
		task.task_data = empty_data;
	}

	if (pRspInfo)
	{
		task.task_error = *pRspInfo;
	}
	else
	{
		CSecurityFtdcRspInfoField empty_error = CSecurityFtdcRspInfoField();
		memset(&empty_error, 0, sizeof(empty_error));
		task.task_error = empty_error;
	}
	task.task_id = nRequestID;
	task.task_last = bIsLast;
	this->task_queue.push(task);
};


///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void QryApi::processTask()
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

			case ONHEARTBEATWARNING:
			{
				this->processHeartBeatWarning(task);
				break;
			}

			case ONRSPERROR:
			{
				this->processRspError(task);
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

			case ONRSPFETCHAUTHRANDCODE:
			{
				this->processRspFetchAuthRandCode(task);
				break;
			}

			case ONRSPQRYEXCHANGE:
			{
				this->processRspQryExchange(task);
				break;
			}

			case ONRSPQRYINSTRUMENT:
			{
				this->processRspQryInstrument(task);
				break;
			}

			case ONRSPQRYINVESTOR:
			{
				this->processRspQryInvestor(task);
				break;
			}

			case ONRSPQRYTRADINGCODE:
			{
				this->processRspQryTradingCode(task);
				break;
			}

			case ONRSPQRYTRADINGACCOUNT:
			{
				this->processRspQryTradingAccount(task);
				break;
			}

			case ONRSPQRYBONDINTEREST:
			{
				this->processRspQryBondInterest(task);
				break;
			}

			case ONRSPQRYMARKETRATIONINFO:
			{
				this->processRspQryMarketRationInfo(task);
				break;
			}

			case ONRSPQRYINSTRUMENTCOMMISSIONRATE:
			{
				this->processRspQryInstrumentCommissionRate(task);
				break;
			}

			case ONRSPQRYETFINSTRUMENT:
			{
				this->processRspQryETFInstrument(task);
				break;
			}

			case ONRSPQRYETFBASKET:
			{
				this->processRspQryETFBasket(task);
				break;
			}

			case ONRSPQRYOFINSTRUMENT:
			{
				this->processRspQryOFInstrument(task);
				break;
			}

			case ONRSPQRYSFINSTRUMENT:
			{
				this->processRspQrySFInstrument(task);
				break;
			}

			case ONRSPQRYINSTRUMENTUNITMARGIN:
			{
				this->processRspQryInstrumentUnitMargin(task);
				break;
			}

			case ONRSPQRYPREDELIVINFO:
			{
				this->processRspQryPreDelivInfo(task);
				break;
			}

			case ONRSPQRYCREDITSTOCKASSIGNINFO:
			{
				this->processRspQryCreditStockAssignInfo(task);
				break;
			}

			case ONRSPQRYCREDITCASHASSIGNINFO:
			{
				this->processRspQryCreditCashAssignInfo(task);
				break;
			}

			case ONRSPQRYCONVERSIONRATE:
			{
				this->processRspQryConversionRate(task);
				break;
			}

			case ONRSPQRYHISCREDITDEBTINFO:
			{
				this->processRspQryHisCreditDebtInfo(task);
				break;
			}

			case ONRSPQRYMARKETDATASTATICINFO:
			{
				this->processRspQryMarketDataStaticInfo(task);
				break;
			}

			case ONRSPQRYEXPIREREPURCHINFO:
			{
				this->processRspQryExpireRepurchInfo(task);
				break;
			}

			case ONRSPQRYBONDPLEDGERATE:
			{
				this->processRspQryBondPledgeRate(task);
				break;
			}

			case ONRSPQRYPLEDGEBOND:
			{
				this->processRspQryPledgeBond(task);
				break;
			}

			case ONRSPQRYORDER:
			{
				this->processRspQryOrder(task);
				break;
			}

			case ONRSPQRYTRADE:
			{
				this->processRspQryTrade(task);
				break;
			}

			case ONRSPQRYINVESTORPOSITION:
			{
				this->processRspQryInvestorPosition(task);
				break;
			}

			case ONRSPQRYFUNDTRANSFERSERIAL:
			{
				this->processRspQryFundTransferSerial(task);
				break;
			}

			case ONRSPQRYFUNDINTERTRANSFERSERIAL:
			{
				this->processRspQryFundInterTransferSerial(task);
				break;
			}
		}
	}
}

void QryApi::processFrontConnected(Task task)
{
	PyLock lock;
	this->onFrontConnected();
};

void QryApi::processFrontDisconnected(Task task)
{
	PyLock lock;
	this->onFrontDisconnected(task.task_id);
};

void QryApi::processHeartBeatWarning(Task task)
{
	PyLock lock;
	this->onHeartBeatWarning(task.task_id);
};

void QryApi::processRspError(Task task)
{
	PyLock lock;
	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void QryApi::processRspUserLogin(Task task)
{
	PyLock lock;
	CSecurityFtdcRspUserLoginField task_data = any_cast<CSecurityFtdcRspUserLoginField>(task.task_data);
	dict data;
	data["MaxOrderRef"] = task_data.MaxOrderRef;
	data["UserID"] = task_data.UserID;
	data["TradingDay"] = task_data.TradingDay;
	data["SessionID"] = task_data.SessionID;
	data["SystemName"] = task_data.SystemName;
	data["FrontID"] = task_data.FrontID;
	data["BrokerID"] = task_data.BrokerID;
	data["LoginTime"] = task_data.LoginTime;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogin(data, error, task.task_id, task.task_last);
};

void QryApi::processRspUserLogout(Task task)
{
	PyLock lock;
	CSecurityFtdcUserLogoutField task_data = any_cast<CSecurityFtdcUserLogoutField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["BrokerID"] = task_data.BrokerID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserLogout(data, error, task.task_id, task.task_last);
};

void QryApi::processRspFetchAuthRandCode(Task task)
{
	PyLock lock;
	CSecurityFtdcAuthRandCodeField task_data = any_cast<CSecurityFtdcAuthRandCodeField>(task.task_data);
	dict data;
	data["RandCode"] = task_data.RandCode;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFetchAuthRandCode(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryExchange(Task task)
{
	PyLock lock;
	CSecurityFtdcExchangeField task_data = any_cast<CSecurityFtdcExchangeField>(task.task_data);
	dict data;
	data["ExchangeProperty"] = task_data.ExchangeProperty;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ExchangeName"] = task_data.ExchangeName;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExchange(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryInstrument(Task task)
{
	PyLock lock;
	CSecurityFtdcInstrumentField task_data = any_cast<CSecurityFtdcInstrumentField>(task.task_data);
	dict data;
	data["IsTrading"] = task_data.IsTrading;
	data["ExpireDate"] = task_data.ExpireDate;
	data["UnitMargin"] = task_data.UnitMargin;
	data["OrderCanBeWithdraw"] = task_data.OrderCanBeWithdraw;
	data["PositionType"] = task_data.PositionType;
	data["ProductClass"] = task_data.ProductClass;
	data["MinSellVolume"] = task_data.MinSellVolume;
	data["InstrumentName"] = task_data.InstrumentName;
	data["ExecPrice"] = task_data.ExecPrice;
	data["RightModelID"] = task_data.RightModelID;
	data["VolumeMultiple"] = task_data.VolumeMultiple;
	data["DeliveryYear"] = task_data.DeliveryYear;
	data["OptionsMarginParam2"] = task_data.OptionsMarginParam2;
	data["OptionsMarginParam1"] = task_data.OptionsMarginParam1;
	data["PosTradeType"] = task_data.PosTradeType;
	data["CreateDate"] = task_data.CreateDate;
	data["InstrumentID"] = task_data.InstrumentID;
	data["MaxLimitOrderVolume"] = task_data.MaxLimitOrderVolume;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinLimitOrderVolume"] = task_data.MinLimitOrderVolume;
	data["MaxMarketOrderVolume"] = task_data.MaxMarketOrderVolume;
	data["StartDelivDate"] = task_data.StartDelivDate;
	data["InstrumentType"] = task_data.InstrumentType;
	data["DeliveryMonth"] = task_data.DeliveryMonth;
	data["MinBuyVolume"] = task_data.MinBuyVolume;
	data["PriceTick"] = task_data.PriceTick;
	data["InstLifePhase"] = task_data.InstLifePhase;
	data["MarketID"] = task_data.MarketID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["MinMarketOrderVolume"] = task_data.MinMarketOrderVolume;
	data["EndDelivDate"] = task_data.EndDelivDate;
	data["OpenDate"] = task_data.OpenDate;
	data["ProductID"] = task_data.ProductID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrument(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryInvestor(Task task)
{
	PyLock lock;
	CSecurityFtdcInvestorField task_data = any_cast<CSecurityFtdcInvestorField>(task.task_data);
	dict data;
	data["SZBranchID"] = task_data.SZBranchID;
	data["InvestorName"] = task_data.InvestorName;
	data["SHBranchID"] = task_data.SHBranchID;
	data["IdentifiedCardNo"] = task_data.IdentifiedCardNo;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorGroupID"] = task_data.InvestorGroupID;
	data["SettleSystemType"] = task_data.SettleSystemType;
	data["InvestorLevel"] = task_data.InvestorLevel;
	data["IsActive"] = task_data.IsActive;
	data["IdentifiedCardType"] = task_data.IdentifiedCardType;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestor(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryTradingCode(Task task)
{
	PyLock lock;
	CSecurityFtdcTradingCodeField task_data = any_cast<CSecurityFtdcTradingCodeField>(task.task_data);
	dict data;
	data["PBU"] = task_data.PBU;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ClientType"] = task_data.ClientType;
	data["ClientID"] = task_data.ClientID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["IsActive"] = task_data.IsActive;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingCode(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryTradingAccount(Task task)
{
	PyLock lock;
	CSecurityFtdcTradingAccountField task_data = any_cast<CSecurityFtdcTradingAccountField>(task.task_data);
	dict data;
	data["MarginTradeAmount"] = task_data.MarginTradeAmount;
	data["FrozenTransferFee"] = task_data.FrozenTransferFee;
	data["SSEOptionsBuyFrozenAmount"] = task_data.SSEOptionsBuyFrozenAmount;
	data["Mortgage"] = task_data.Mortgage;
	data["ExchangeDeliveryMargin"] = task_data.ExchangeDeliveryMargin;
	data["FrozenMargin"] = task_data.FrozenMargin;
	data["WithdrawQuota"] = task_data.WithdrawQuota;
	data["TransferFee"] = task_data.TransferFee;
	data["Commission"] = task_data.Commission;
	data["Interest"] = task_data.Interest;
	data["ShortSellProfit"] = task_data.ShortSellProfit;
	data["FrozenExecCash"] = task_data.FrozenExecCash;
	data["CashIn"] = task_data.CashIn;
	data["AccountID"] = task_data.AccountID;
	data["Available"] = task_data.Available;
	data["PreCredit"] = task_data.PreCredit;
	data["PreMortgage"] = task_data.PreMortgage;
	data["CreditRatio"] = task_data.CreditRatio;
	data["CreditAmount"] = task_data.CreditAmount;
	data["InterestBase"] = task_data.InterestBase;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["ConversionAmount"] = task_data.ConversionAmount;
	data["SSStockValue"] = task_data.SSStockValue;
	data["ShortSellAmount"] = task_data.ShortSellAmount;
	data["PreMargin"] = task_data.PreMargin;
	data["CurrencyCode"] = task_data.CurrencyCode;
	data["DeliveryMargin"] = task_data.DeliveryMargin;
	data["BondRepurchaseAmount"] = task_data.BondRepurchaseAmount;
	data["SettleMargin"] = task_data.SettleMargin;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenCash"] = task_data.FrozenCash;
	data["Withdraw"] = task_data.Withdraw;
	data["ReverseRepurchaseAmount"] = task_data.ReverseRepurchaseAmount;
	data["StampTax"] = task_data.StampTax;
	data["SSEOptionsBuyAmount"] = task_data.SSEOptionsBuyAmount;
	data["Balance"] = task_data.Balance;
	data["FrozenStampTax"] = task_data.FrozenStampTax;
	data["Reserve"] = task_data.Reserve;
	data["PreDeposit"] = task_data.PreDeposit;
	data["MarginTradeProfit"] = task_data.MarginTradeProfit;
	data["Credit"] = task_data.Credit;
	data["PreBalance"] = task_data.PreBalance;
	data["CurrMargin"] = task_data.CurrMargin;
	data["FrozenCommission"] = task_data.FrozenCommission;
	data["AccountType"] = task_data.AccountType;
	data["StockValue"] = task_data.StockValue;
	data["Deposit"] = task_data.Deposit;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTradingAccount(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryBondInterest(Task task)
{
	PyLock lock;
	CSecurityFtdcBondInterestField task_data = any_cast<CSecurityFtdcBondInterestField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["TradingDay"] = task_data.TradingDay;
	data["ExchangeID"] = task_data.ExchangeID;
	data["Interest"] = task_data.Interest;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryBondInterest(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryMarketRationInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcMarketRationInfoField task_data = any_cast<CSecurityFtdcMarketRationInfoField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["BrokerID"] = task_data.BrokerID;
	data["RationVolume"] = task_data.RationVolume;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryMarketRationInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryInstrumentCommissionRate(Task task)
{
	PyLock lock;
	CSecurityFtdcInstrumentCommissionRateField task_data = any_cast<CSecurityFtdcInstrumentCommissionRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinTransferFee"] = task_data.MinTransferFee;
	data["TradeFeeByMoney"] = task_data.TradeFeeByMoney;
	data["Direction"] = task_data.Direction;
	data["MinTradeFee"] = task_data.MinTradeFee;
	data["StampTaxRateByMoney"] = task_data.StampTaxRateByMoney;
	data["InvestorID"] = task_data.InvestorID;
	data["MarginByMoney"] = task_data.MarginByMoney;
	data["StampTaxRateByVolume"] = task_data.StampTaxRateByVolume;
	data["BrokerID"] = task_data.BrokerID;
	data["InvestorRange"] = task_data.InvestorRange;
	data["TransferFeeRateByVolume"] = task_data.TransferFeeRateByVolume;
	data["TransferFeeRateByMoney"] = task_data.TransferFeeRateByMoney;
	data["TradeFeeByVolume"] = task_data.TradeFeeByVolume;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrumentCommissionRate(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryETFInstrument(Task task)
{
	PyLock lock;
	CSecurityFtdcETFInstrumentField task_data = any_cast<CSecurityFtdcETFInstrumentField>(task.task_data);
	dict data;
	data["ETFInstrumentID"] = task_data.ETFInstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ETFPurRedInstrumentID"] = task_data.ETFPurRedInstrumentID;
	data["ETFNetValue"] = task_data.ETFNetValue;
	data["FundClass"] = task_data.FundClass;
	data["EstimateCashComponent"] = task_data.EstimateCashComponent;
	data["CreationRedemptionUnit"] = task_data.CreationRedemptionUnit;
	data["Maxcashratio"] = task_data.Maxcashratio;
	data["Creationredemption"] = task_data.Creationredemption;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryETFInstrument(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryETFBasket(Task task)
{
	PyLock lock;
	CSecurityFtdcETFBasketField task_data = any_cast<CSecurityFtdcETFBasketField>(task.task_data);
	dict data;
	data["ETFInstrumentID"] = task_data.ETFInstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["Premium"] = task_data.Premium;
	data["StockInstrumentName"] = task_data.StockInstrumentName;
	data["CurrenceReplaceStatus"] = task_data.CurrenceReplaceStatus;
	data["Volume"] = task_data.Volume;
	data["Amount"] = task_data.Amount;
	data["StockInstrumentID"] = task_data.StockInstrumentID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryETFBasket(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryOFInstrument(Task task)
{
	PyLock lock;
	CSecurityFtdcOFInstrumentField task_data = any_cast<CSecurityFtdcOFInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["NetPrice"] = task_data.NetPrice;
	data["FundClass"] = task_data.FundClass;
	data["Creationredemption"] = task_data.Creationredemption;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOFInstrument(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQrySFInstrument(Task task)
{
	PyLock lock;
	CSecurityFtdcSFInstrumentField task_data = any_cast<CSecurityFtdcSFInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["NetPrice"] = task_data.NetPrice;
	data["MinMergeVolume"] = task_data.MinMergeVolume;
	data["SFInstrumentID"] = task_data.SFInstrumentID;
	data["MinSplitVolume"] = task_data.MinSplitVolume;
	data["VolumeRatio"] = task_data.VolumeRatio;
	data["SplitMergeStatus"] = task_data.SplitMergeStatus;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQrySFInstrument(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryInstrumentUnitMargin(Task task)
{
	PyLock lock;
	CSecurityFtdcInstrumentUnitMarginField task_data = any_cast<CSecurityFtdcInstrumentUnitMarginField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["BrokerID"] = task_data.BrokerID;
	data["UnitMargin"] = task_data.UnitMargin;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInstrumentUnitMargin(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryPreDelivInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcPreDelivInfoField task_data = any_cast<CSecurityFtdcPreDelivInfoField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["DelivVolume"] = task_data.DelivVolume;
	data["DelivAmount"] = task_data.DelivAmount;
	data["DelivType"] = task_data.DelivType;
	data["Direction"] = task_data.Direction;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["ExecVolume"] = task_data.ExecVolume;
	data["UnderlyingInstrumentID"] = task_data.UnderlyingInstrumentID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryPreDelivInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryCreditStockAssignInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcCreditStockAssignInfoField task_data = any_cast<CSecurityFtdcCreditStockAssignInfoField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["FrozenVolume"] = task_data.FrozenVolume;
	data["InvestorID"] = task_data.InvestorID;
	data["LeftVolume"] = task_data.LeftVolume;
	data["BrokerID"] = task_data.BrokerID;
	data["YDVolume"] = task_data.YDVolume;
	data["LimitVolume"] = task_data.LimitVolume;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryCreditStockAssignInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryCreditCashAssignInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcCreditCashAssignInfoField task_data = any_cast<CSecurityFtdcCreditCashAssignInfoField>(task.task_data);
	dict data;
	data["InvestorID"] = task_data.InvestorID;
	data["YDAmount"] = task_data.YDAmount;
	data["BrokerID"] = task_data.BrokerID;
	data["LimitAmount"] = task_data.LimitAmount;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryCreditCashAssignInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryConversionRate(Task task)
{
	PyLock lock;
	CSecurityFtdcConversionRateField task_data = any_cast<CSecurityFtdcConversionRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ConversionRate"] = task_data.ConversionRate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["IsTradingForShort"] = task_data.IsTradingForShort;
	data["IsTradingForMargin"] = task_data.IsTradingForMargin;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryConversionRate(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryHisCreditDebtInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcHisCreditDebtInfoField task_data = any_cast<CSecurityFtdcHisCreditDebtInfoField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["Direction"] = task_data.Direction;
	data["OpenPrice"] = task_data.OpenPrice;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["Amount"] = task_data.Amount;
	data["BrokerID"] = task_data.BrokerID;
	data["OpenDate"] = task_data.OpenDate;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryHisCreditDebtInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryMarketDataStaticInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcMarketDataStaticInfoField task_data = any_cast<CSecurityFtdcMarketDataStaticInfoField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["PreIOPV"] = task_data.PreIOPV;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["IsNotTrade"] = task_data.IsNotTrade;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryMarketDataStaticInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryExpireRepurchInfo(Task task)
{
	PyLock lock;
	CSecurityFtdcExpireRepurchInfoField task_data = any_cast<CSecurityFtdcExpireRepurchInfoField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ExpireType"] = task_data.ExpireType;
	data["Volume"] = task_data.Volume;
	data["InvestorID"] = task_data.InvestorID;
	data["Amount"] = task_data.Amount;
	data["BrokerID"] = task_data.BrokerID;
	data["Interest"] = task_data.Interest;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryExpireRepurchInfo(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryBondPledgeRate(Task task)
{
	PyLock lock;
	CSecurityFtdcBondPledgeRateField task_data = any_cast<CSecurityFtdcBondPledgeRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["Ratio"] = task_data.Ratio;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryBondPledgeRate(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryPledgeBond(Task task)
{
	PyLock lock;
	CSecurityFtdcPledgeBondField task_data = any_cast<CSecurityFtdcPledgeBondField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["PledgeID"] = task_data.PledgeID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryPledgeBond(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryOrder(Task task)
{
	PyLock lock;
	CSecurityFtdcOrderField task_data = any_cast<CSecurityFtdcOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["NotifySequence"] = task_data.NotifySequence;
	data["ActiveUserID"] = task_data.ActiveUserID;
	data["VolumeTraded"] = task_data.VolumeTraded;
	data["UserProductInfo"] = task_data.UserProductInfo;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["RelativeOrderSysID"] = task_data.RelativeOrderSysID;
	data["AccountID"] = task_data.AccountID;
	data["Direction"] = task_data.Direction;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["ClientID"] = task_data.ClientID;
	data["VolumeTotal"] = task_data.VolumeTotal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["SessionID"] = task_data.SessionID;
	data["TimeCondition"] = task_data.TimeCondition;
	data["OrderStatus"] = task_data.OrderStatus;
	data["OrderSysID"] = task_data.OrderSysID;
	data["OrderSubmitStatus"] = task_data.OrderSubmitStatus;
	data["IsETF"] = task_data.IsETF;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["StatusMsg"] = task_data.StatusMsg;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["OrderType"] = task_data.OrderType;
	data["UpdateTime"] = task_data.UpdateTime;
	data["TradingDay"] = task_data.TradingDay;
	data["ActiveTime"] = task_data.ActiveTime;
	data["BrokerID"] = task_data.BrokerID;
	data["InsertTime"] = task_data.InsertTime;
	data["FrontID"] = task_data.FrontID;
	data["SuspendTime"] = task_data.SuspendTime;
	data["InstrumentType"] = task_data.InstrumentType;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["CancelTime"] = task_data.CancelTime;
	data["GTDDate"] = task_data.GTDDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["InsertDate"] = task_data.InsertDate;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;
	data["OrderSource"] = task_data.OrderSource;
	data["BranchPBU"] = task_data.BranchPBU;
	data["TradeAmount"] = task_data.TradeAmount;
	data["ActiveTraderID"] = task_data.ActiveTraderID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOrder(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryTrade(Task task)
{
	PyLock lock;
	CSecurityFtdcTradeField task_data = any_cast<CSecurityFtdcTradeField>(task.task_data);
	dict data;
	data["TradeType"] = task_data.TradeType;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["TradeTime"] = task_data.TradeTime;
	data["Direction"] = task_data.Direction;
	data["ParticipantID"] = task_data.ParticipantID;
	data["Price"] = task_data.Price;
	data["ClientID"] = task_data.ClientID;
	data["Volume"] = task_data.Volume;
	data["OrderSysID"] = task_data.OrderSysID;
	data["ClearingPartID"] = task_data.ClearingPartID;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["UserID"] = task_data.UserID;
	data["TradeIndex"] = task_data.TradeIndex;
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["TradeSource"] = task_data.TradeSource;
	data["OffsetFlag"] = task_data.OffsetFlag;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["TradeID"] = task_data.TradeID;
	data["TradeDate"] = task_data.TradeDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["SequenceNo"] = task_data.SequenceNo;
	data["OrderRef"] = task_data.OrderRef;
	data["BrokerOrderSeq"] = task_data.BrokerOrderSeq;
	data["InvestorID"] = task_data.InvestorID;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["BranchPBU"] = task_data.BranchPBU;
	data["PriceSource"] = task_data.PriceSource;
	data["TradingRole"] = task_data.TradingRole;
	data["TradeAmount"] = task_data.TradeAmount;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryTrade(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryInvestorPosition(Task task)
{
	PyLock lock;
	CSecurityFtdcInvestorPositionField task_data = any_cast<CSecurityFtdcInvestorPositionField>(task.task_data);
	dict data;
	data["LockPosition"] = task_data.LockPosition;
	data["MarginTradeAmount"] = task_data.MarginTradeAmount;
	data["ShortFrozenAmount"] = task_data.ShortFrozenAmount;
	data["ShortSellAmount"] = task_data.ShortSellAmount;
	data["TodaySSPosition"] = task_data.TodaySSPosition;
	data["HedgeFlag"] = task_data.HedgeFlag;
	data["TransferFee"] = task_data.TransferFee;
	data["Commission"] = task_data.Commission;
	data["ShortSellVolume"] = task_data.ShortSellVolume;
	data["CoverFrozenPosition"] = task_data.CoverFrozenPosition;
	data["TodayPurRedVolume"] = task_data.TodayPurRedVolume;
	data["PurRedShortFrozen"] = task_data.PurRedShortFrozen;
	data["CashIn"] = task_data.CashIn;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["ShortSellFrozenAmount"] = task_data.ShortSellFrozenAmount;
	data["CloseAmount"] = task_data.CloseAmount;
	data["PosiDirection"] = task_data.PosiDirection;
	data["LockFrozenPosition"] = task_data.LockFrozenPosition;
	data["RepurchasePosition"] = task_data.RepurchasePosition;
	data["MarginTradeVolume"] = task_data.MarginTradeVolume;
	data["YdPosition"] = task_data.YdPosition;
	data["MarginTradeFrozenVolume"] = task_data.MarginTradeFrozenVolume;
	data["ConversionRate"] = task_data.ConversionRate;
	data["YDCoverPosition"] = task_data.YDCoverPosition;
	data["ShortSellFrozenVolume"] = task_data.ShortSellFrozenVolume;
	data["OpenVolume"] = task_data.OpenVolume;
	data["TodayMTPosition"] = task_data.TodayMTPosition;
	data["CoverPosition"] = task_data.CoverPosition;
	data["CloseVolume"] = task_data.CloseVolume;
	data["AccountID"] = task_data.AccountID;
	data["ConversionAmount"] = task_data.ConversionAmount;
	data["ShortSellConversionProfit"] = task_data.ShortSellConversionProfit;
	data["InstrumentID"] = task_data.InstrumentID;
	data["PositionDate"] = task_data.PositionDate;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MarginTradeFrozenAmount"] = task_data.MarginTradeFrozenAmount;
	data["ShortFrozen"] = task_data.ShortFrozen;
	data["LongFrozen"] = task_data.LongFrozen;
	data["TodayPosition"] = task_data.TodayPosition;
	data["TradingDay"] = task_data.TradingDay;
	data["PositionCost"] = task_data.PositionCost;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenCash"] = task_data.FrozenCash;
	data["OpenAmount"] = task_data.OpenAmount;
	data["OpenCost"] = task_data.OpenCost;
	data["StampTax"] = task_data.StampTax;
	data["Position"] = task_data.Position;
	data["ExecFrozenPosition"] = task_data.ExecFrozenPosition;
	data["ExchangeMargin"] = task_data.ExchangeMargin;
	data["PledgeInPosition"] = task_data.PledgeInPosition;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["LongFrozenAmount"] = task_data.LongFrozenAmount;
	data["InvestorID"] = task_data.InvestorID;
	data["UnlockFrozenPosition"] = task_data.UnlockFrozenPosition;
	data["YdOpenCost"] = task_data.YdOpenCost;
	data["MarginTradeConversionProfit"] = task_data.MarginTradeConversionProfit;
	data["SSStockValue"] = task_data.SSStockValue;
	data["StockValue"] = task_data.StockValue;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryInvestorPosition(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryFundTransferSerial(Task task)
{
	PyLock lock;
	CSecurityFtdcFundTransferField task_data = any_cast<CSecurityFtdcFundTransferField>(task.task_data);
	dict data;
	data["PlateSerial"] = task_data.PlateSerial;
	data["TradingDay"] = task_data.TradingDay;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["ErrorID"] = task_data.ErrorID;
	data["UserID"] = task_data.UserID;
	data["TransferSerial"] = task_data.TransferSerial;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["LiberSerial"] = task_data.LiberSerial;
	data["BrokerID"] = task_data.BrokerID;
	data["FundDirection"] = task_data.FundDirection;
	data["TradeTime"] = task_data.TradeTime;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryFundTransferSerial(data, error, task.task_id, task.task_last);
};

void QryApi::processRspQryFundInterTransferSerial(Task task)
{
	PyLock lock;
	CSecurityFtdcFundInterTransferSerialField task_data = any_cast<CSecurityFtdcFundInterTransferSerialField>(task.task_data);
	dict data;
	data["SerialID"] = task_data.SerialID;
	data["TransferType"] = task_data.TransferType;
	data["ErrorMsg"] = task_data.ErrorMsg;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["TransferTime"] = task_data.TransferTime;
	data["BrokerID"] = task_data.BrokerID;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["ErrorID"] = task_data.ErrorID;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryFundInterTransferSerial(data, error, task.task_id, task.task_last);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void QryApi::createFtdcQueryApi(string pszFlowPath)
{
	this->api = CSecurityFtdcQueryApi::CreateFtdcQueryApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};

void QryApi::release()
{
	this->api->Release();
};

void QryApi::init()
{
	this->api->Init();
};

int QryApi::join()
{
	int i = this->api->Join();
	return i;
};

int QryApi::exit()
{
	//该函数在原生API里没有，用于安全退出API用，原生的join似乎不太稳定
	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	return 1;
};

string QryApi::getTradingDay()
{
	string day = this->api->GetTradingDay();
	return day;
};

void QryApi::registerFront(string pszFrontAddress)
{
	this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

int QryApi::reqUserLogin(dict req, int nRequestID)
{
	CSecurityFtdcReqUserLoginField myreq = CSecurityFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "MacAddress", myreq.MacAddress);
	getChar(req, "RandCode", myreq.RandCode);
	getChar(req, "UserProductInfo", myreq.UserProductInfo);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "AuthCode", myreq.AuthCode);
	getChar(req, "TradingDay", myreq.TradingDay);
	getChar(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ClientIPAddress", myreq.ClientIPAddress);
	getChar(req, "OneTimePassword", myreq.OneTimePassword);
	getChar(req, "ProtocolInfo", myreq.ProtocolInfo);
	getChar(req, "Password", myreq.Password);
	getChar(req, "HDSerialNumber", myreq.HDSerialNumber);
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int QryApi::reqUserLogout(dict req, int nRequestID)
{
	CSecurityFtdcUserLogoutField myreq = CSecurityFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int QryApi::reqFetchAuthRandCode(dict req, int nRequestID)
{
	CSecurityFtdcAuthRandCodeField myreq = CSecurityFtdcAuthRandCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "RandCode", myreq.RandCode);
	int i = this->api->ReqFetchAuthRandCode(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryExchange(dict req, int nRequestID)
{
	CSecurityFtdcQryExchangeField myreq = CSecurityFtdcQryExchangeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchange(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryInstrument(dict req, int nRequestID)
{
	CSecurityFtdcQryInstrumentField myreq = CSecurityFtdcQryInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "ExchangeInstID", myreq.ExchangeInstID);
	getChar(req, "ProductID", myreq.ProductID);
	int i = this->api->ReqQryInstrument(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryInvestor(dict req, int nRequestID)
{
	CSecurityFtdcQryInvestorField myreq = CSecurityFtdcQryInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestor(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryTradingCode(dict req, int nRequestID)
{
	CSecurityFtdcQryTradingCodeField myreq = CSecurityFtdcQryTradingCodeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "ClientID", myreq.ClientID);
	int i = this->api->ReqQryTradingCode(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryTradingAccount(dict req, int nRequestID)
{
	CSecurityFtdcQryTradingAccountField myreq = CSecurityFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTradingAccount(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryBondInterest(dict req, int nRequestID)
{
	CSecurityFtdcQryBondInterestField myreq = CSecurityFtdcQryBondInterestField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryBondInterest(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryMarketRationInfo(dict req, int nRequestID)
{
	CSecurityFtdcQryMarketRationInfoField myreq = CSecurityFtdcQryMarketRationInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryMarketRationInfo(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryInstrumentCommissionRate(dict req, int nRequestID)
{
	CSecurityFtdcQryInstrumentCommissionRateField myreq = CSecurityFtdcQryInstrumentCommissionRateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "OffsetFlag", &myreq.OffsetFlag);
	getChar(req, "Direction", &myreq.Direction);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInstrumentCommissionRate(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryETFInstrument(dict req, int nRequestID)
{
	CSecurityFtdcQryETFInstrumentField myreq = CSecurityFtdcQryETFInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ETFInstrumentID", myreq.ETFInstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryETFInstrument(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryETFBasket(dict req, int nRequestID)
{
	CSecurityFtdcQryETFBasketField myreq = CSecurityFtdcQryETFBasketField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ETFInstrumentID", myreq.ETFInstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryETFBasket(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryOFInstrument(dict req, int nRequestID)
{
	CSecurityFtdcQryOFInstrumentField myreq = CSecurityFtdcQryOFInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "OFInstrumentID", myreq.OFInstrumentID);
	int i = this->api->ReqQryOFInstrument(&myreq, nRequestID);
	return i;
};

int QryApi::reqQrySFInstrument(dict req, int nRequestID)
{
	CSecurityFtdcQrySFInstrumentField myreq = CSecurityFtdcQrySFInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "SFInstrumentID", myreq.SFInstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQrySFInstrument(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryInstrumentUnitMargin(dict req, int nRequestID)
{
	CSecurityFtdcQryInstrumentUnitMarginField myreq = CSecurityFtdcQryInstrumentUnitMarginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInstrumentUnitMargin(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryPreDelivInfo(dict req, int nRequestID)
{
	CSecurityFtdcQryPreDelivInfoField myreq = CSecurityFtdcQryPreDelivInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryPreDelivInfo(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryCreditStockAssignInfo(dict req, int nRequestID)
{
	CSecurityFtdcQryCreditStockAssignInfoField myreq = CSecurityFtdcQryCreditStockAssignInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryCreditStockAssignInfo(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryCreditCashAssignInfo(dict req, int nRequestID)
{
	CSecurityFtdcQryCreditCashAssignInfoField myreq = CSecurityFtdcQryCreditCashAssignInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryCreditCashAssignInfo(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryConversionRate(dict req, int nRequestID)
{
	CSecurityFtdcQryConversionRateField myreq = CSecurityFtdcQryConversionRateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryConversionRate(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryHisCreditDebtInfo(dict req, int nRequestID)
{
	CSecurityFtdcQryHisCreditDebtInfoField myreq = CSecurityFtdcQryHisCreditDebtInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryHisCreditDebtInfo(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryMarketDataStaticInfo(dict req, int nRequestID)
{
	CSecurityFtdcQryMarketDataStaticInfoField myreq = CSecurityFtdcQryMarketDataStaticInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryMarketDataStaticInfo(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryExpireRepurchInfo(dict req, int nRequestID)
{
	CSecurityFtdcQryExpireRepurchInfoField myreq = CSecurityFtdcQryExpireRepurchInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryExpireRepurchInfo(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryBondPledgeRate(dict req, int nRequestID)
{
	CSecurityFtdcQryBondPledgeRateField myreq = CSecurityFtdcQryBondPledgeRateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryBondPledgeRate(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryPledgeBond(dict req, int nRequestID)
{
	CSecurityFtdcQryPledgeBondField myreq = CSecurityFtdcQryPledgeBondField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryPledgeBond(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryOrder(dict req, int nRequestID)
{
	CSecurityFtdcQryOrderField myreq = CSecurityFtdcQryOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "InsertTimeStart", myreq.InsertTimeStart);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "OrderSysID", myreq.OrderSysID);
	getChar(req, "InsertTimeEnd", myreq.InsertTimeEnd);
	int i = this->api->ReqQryOrder(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryTrade(dict req, int nRequestID)
{
	CSecurityFtdcQryTradeField myreq = CSecurityFtdcQryTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "TradeTimeStart", myreq.TradeTimeStart);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "TradeID", myreq.TradeID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "TradeTimeEnd", myreq.TradeTimeEnd);
	int i = this->api->ReqQryTrade(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CSecurityFtdcQryInvestorPositionField myreq = CSecurityFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryFundTransferSerial(dict req, int nRequestID)
{
	CSecurityFtdcQryFundTransferSerialField myreq = CSecurityFtdcQryFundTransferSerialField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "AccountType", &myreq.AccountType);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQryFundTransferSerial(&myreq, nRequestID);
	return i;
};

int QryApi::reqQryFundInterTransferSerial(dict req, int nRequestID)
{
	CSecurityFtdcQryFundInterTransferSerialField myreq = CSecurityFtdcQryFundInterTransferSerialField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryFundInterTransferSerial(&myreq, nRequestID);
	return i;
};


///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

struct QryApiWrap : QryApi, wrapper < QryApi >
{
	virtual void onFrontConnected()
	{
		//在向python环境中调用回调函数推送数据前，需要先获取全局锁GIL，防止解释器崩溃
		PyLock lock;
		
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
		PyLock lock;

		try
		{
			this->get_override("onFrontDisconnected")(i);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onHeartBeatWarning(int i)
	{
		PyLock lock;
		
		try
		{
			this->get_override("onHeartBeatWarning")(i);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspError(dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspError")(error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUserLogin(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspUserLogin")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspUserLogout(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspUserLogout")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFetchAuthRandCode(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspFetchAuthRandCode")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryExchange(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryExchange")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInstrument(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInstrument")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInvestor(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestor")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryTradingCode(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryTradingCode")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryTradingAccount")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryBondInterest(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryBondInterest")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryMarketRationInfo(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryMarketRationInfo")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInstrumentCommissionRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInstrumentCommissionRate")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryETFInstrument(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryETFInstrument")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryETFBasket(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryETFBasket")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryOFInstrument(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryOFInstrument")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQrySFInstrument(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQrySFInstrument")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInstrumentUnitMargin(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInstrumentUnitMargin")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryPreDelivInfo(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryPreDelivInfo")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryCreditStockAssignInfo(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryCreditStockAssignInfo")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryCreditCashAssignInfo(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryCreditCashAssignInfo")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryConversionRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryConversionRate")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryHisCreditDebtInfo(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryHisCreditDebtInfo")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryMarketDataStaticInfo(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryMarketDataStaticInfo")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryExpireRepurchInfo(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryExpireRepurchInfo")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryBondPledgeRate(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryBondPledgeRate")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryPledgeBond(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryPledgeBond")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryOrder(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryOrder")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryTrade(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryTrade")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryInvestorPosition")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryFundTransferSerial(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryFundTransferSerial")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspQryFundInterTransferSerial(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onRspQryFundInterTransferSerial")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};
};


BOOST_PYTHON_MODULE(vnltsqry)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<QryApiWrap, boost::noncopyable>("QryApi")
		.def("createFtdcQueryApi", &QryApiWrap::createFtdcQueryApi)
		.def("release", &QryApiWrap::release)
		.def("init", &QryApiWrap::init)
		.def("join", &QryApiWrap::join)
		.def("exit", &QryApiWrap::exit)
		.def("getTradingDay", &QryApiWrap::getTradingDay)
		.def("registerFront", &QryApiWrap::registerFront)
		.def("reqUserLogin", &QryApiWrap::reqUserLogin)
		.def("reqUserLogout", &QryApiWrap::reqUserLogout)
		.def("reqFetchAuthRandCode", &QryApiWrap::reqFetchAuthRandCode)
		.def("reqQryExchange", &QryApiWrap::reqQryExchange)
		.def("reqQryInstrument", &QryApiWrap::reqQryInstrument)
		.def("reqQryInvestor", &QryApiWrap::reqQryInvestor)
		.def("reqQryTradingCode", &QryApiWrap::reqQryTradingCode)
		.def("reqQryTradingAccount", &QryApiWrap::reqQryTradingAccount)
		.def("reqQryBondInterest", &QryApiWrap::reqQryBondInterest)
		.def("reqQryMarketRationInfo", &QryApiWrap::reqQryMarketRationInfo)
		.def("reqQryInstrumentCommissionRate", &QryApiWrap::reqQryInstrumentCommissionRate)
		.def("reqQryETFInstrument", &QryApiWrap::reqQryETFInstrument)
		.def("reqQryETFBasket", &QryApiWrap::reqQryETFBasket)
		.def("reqQryOFInstrument", &QryApiWrap::reqQryOFInstrument)
		.def("reqQrySFInstrument", &QryApiWrap::reqQrySFInstrument)
		.def("reqQryOrder", &QryApiWrap::reqQryOrder)
		.def("reqQryTrade", &QryApiWrap::reqQryTrade)
		.def("reqQryInvestorPosition", &QryApiWrap::reqQryInvestorPosition)
		.def("reqQryFundTransferSerial", &QryApiWrap::reqQryFundTransferSerial)
		.def("reqQryFundInterTransferSerial", &QryApiWrap::reqQryFundInterTransferSerial)

		.def("onFrontConnected", pure_virtual(&QryApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&QryApiWrap::onFrontDisconnected))
		.def("onHeartBeatWarning", pure_virtual(&QryApiWrap::onHeartBeatWarning))
		.def("onRspError", pure_virtual(&QryApiWrap::onRspError))
		.def("onRspUserLogin", pure_virtual(&QryApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&QryApiWrap::onRspUserLogout))
		.def("onRspFetchAuthRandCode", pure_virtual(&QryApiWrap::onRspFetchAuthRandCode))
		.def("onRspQryExchange", pure_virtual(&QryApiWrap::onRspQryExchange))
		.def("onRspQryInstrument", pure_virtual(&QryApiWrap::onRspQryInstrument))
		.def("onRspQryInvestor", pure_virtual(&QryApiWrap::onRspQryInvestor))
		.def("onRspQryTradingCode", pure_virtual(&QryApiWrap::onRspQryTradingCode))
		.def("onRspQryTradingAccount", pure_virtual(&QryApiWrap::onRspQryTradingAccount))
		.def("onRspQryBondInterest", pure_virtual(&QryApiWrap::onRspQryBondInterest))
		.def("onRspQryMarketRationInfo", pure_virtual(&QryApiWrap::onRspQryMarketRationInfo))
		.def("onRspQryInstrumentCommissionRate", pure_virtual(&QryApiWrap::onRspQryInstrumentCommissionRate))
		.def("onRspQryETFInstrument", pure_virtual(&QryApiWrap::onRspQryETFInstrument))
		.def("onRspQryETFBasket", pure_virtual(&QryApiWrap::onRspQryETFBasket))
		.def("onRspQryOFInstrument", pure_virtual(&QryApiWrap::onRspQryOFInstrument))
		.def("onRspQrySFInstrument", pure_virtual(&QryApiWrap::onRspQrySFInstrument))
		.def("onRspQryOrder", pure_virtual(&QryApiWrap::onRspQryOrder))
		.def("onRspQryTrade", pure_virtual(&QryApiWrap::onRspQryTrade))
		.def("onRspQryInvestorPosition", pure_virtual(&QryApiWrap::onRspQryInvestorPosition))
		.def("onRspQryFundTransferSerial", pure_virtual(&QryApiWrap::onRspQryFundTransferSerial))
		.def("onRspQryFundInterTransferSerial", pure_virtual(&QryApiWrap::onRspQryFundInterTransferSerial))
		;
}
