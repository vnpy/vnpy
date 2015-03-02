// MdApi.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnltstd.h"



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
			strcpy_s(value, strlen(buffer) + 1, buffer);
		}
	}
}



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

void TdApi::OnHeartBeatWarning(int nTimeLapse)
{
	Task task = Task();
	task.task_name = ONHEARTBEATWARNING;
	task.task_id = nTimeLapse;
	this->task_queue.push(task);
};

void TdApi::OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

void TdApi::OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGIN;
	task.task_data = *pRspUserLogin;
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

void TdApi::OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERLOGOUT;
	task.task_data = *pUserLogout;
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

void TdApi::OnRspOrderInsert(CSecurityFtdcInputOrderField *pInputOrder, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPORDERINSERT;
	task.task_data = *pInputOrder;
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

void TdApi::OnRspOrderAction(CSecurityFtdcInputOrderActionField *pInputOrderAction, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPORDERACTION;
	task.task_data = *pInputOrderAction;
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

void TdApi::OnRspUserPasswordUpdate(CSecurityFtdcUserPasswordUpdateField *pUserPasswordUpdate, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPUSERPASSWORDUPDATE;
	task.task_data = *pUserPasswordUpdate;
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

void TdApi::OnRspTradingAccountPasswordUpdate(CSecurityFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPTRADINGACCOUNTPASSWORDUPDATE;
	task.task_data = *pTradingAccountPasswordUpdate;
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

void TdApi::OnRspQryExchange(CSecurityFtdcExchangeField *pExchange, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYEXCHANGE;
	task.task_data = *pExchange;
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

void TdApi::OnRspQryInstrument(CSecurityFtdcInstrumentField *pInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENT;
	task.task_data = *pInstrument;
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

void TdApi::OnRspQryInvestor(CSecurityFtdcInvestorField *pInvestor, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTOR;
	task.task_data = *pInvestor;
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

void TdApi::OnRspQryTradingCode(CSecurityFtdcTradingCodeField *pTradingCode, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGCODE;
	task.task_data = *pTradingCode;
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

void TdApi::OnRspQryTradingAccount(CSecurityFtdcTradingAccountField *pTradingAccount, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADINGACCOUNT;
	task.task_data = *pTradingAccount;
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

void TdApi::OnRspQryDepthMarketData(CSecurityFtdcDepthMarketDataField *pDepthMarketData, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYDEPTHMARKETDATA;
	task.task_data = *pDepthMarketData;
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

void TdApi::OnRspQryBondInterest(CSecurityFtdcBondInterestField *pBondInterest, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYBONDINTEREST;
	task.task_data = *pBondInterest;
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

void TdApi::OnRspQryMarketRationInfo(CSecurityFtdcMarketRationInfoField *pMarketRationInfo, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYMARKETRATIONINFO;
	task.task_data = *pMarketRationInfo;
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

void TdApi::OnRspQryInstrumentCommissionRate(CSecurityFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINSTRUMENTCOMMISSIONRATE;
	task.task_data = *pInstrumentCommissionRate;
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

void TdApi::OnRspQryETFInstrument(CSecurityFtdcETFInstrumentField *pETFInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYETFINSTRUMENT;
	task.task_data = *pETFInstrument;
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

void TdApi::OnRspQryETFBasket(CSecurityFtdcETFBasketField *pETFBasket, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYETFBASKET;
	task.task_data = *pETFBasket;
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

void TdApi::OnRspQryOFInstrument(CSecurityFtdcOFInstrumentField *pOFInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYOFINSTRUMENT;
	task.task_data = *pOFInstrument;
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

void TdApi::OnRspQrySFInstrument(CSecurityFtdcSFInstrumentField *pSFInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYSFINSTRUMENT;
	task.task_data = *pSFInstrument;
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

void TdApi::OnRspQryOrder(CSecurityFtdcOrderField *pOrder, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYORDER;
	task.task_data = *pOrder;
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

void TdApi::OnRspQryTrade(CSecurityFtdcTradeField *pTrade, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYTRADE;
	task.task_data = *pTrade;
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

void TdApi::OnRspQryInvestorPosition(CSecurityFtdcInvestorPositionField *pInvestorPosition, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYINVESTORPOSITION;
	task.task_data = *pInvestorPosition;
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

void TdApi::OnRtnOrder(CSecurityFtdcOrderField *pOrder)
{
	Task task = Task();
	task.task_name = ONRTNORDER;
	task.task_data = *pOrder;
	this->task_queue.push(task);
};

void TdApi::OnRtnTrade(CSecurityFtdcTradeField *pTrade)
{
	Task task = Task();
	task.task_name = ONRTNTRADE;
	task.task_data = *pTrade;
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderInsert(CSecurityFtdcInputOrderField *pInputOrder, CSecurityFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNORDERINSERT;
	task.task_data = *pInputOrder;
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
	this->task_queue.push(task);
};

void TdApi::OnErrRtnOrderAction(CSecurityFtdcOrderActionField *pOrderAction, CSecurityFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNORDERACTION;
	task.task_data = *pOrderAction;
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
	this->task_queue.push(task);
};

void TdApi::OnRspFundOutByLiber(CSecurityFtdcInputFundTransferField *pInputFundTransfer, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFUNDOUTBYLIBER;
	task.task_data = *pInputFundTransfer;
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

void TdApi::OnRtnFundOutByLiber(CSecurityFtdcFundTransferField *pFundTransfer)
{
	Task task = Task();
	task.task_name = ONRTNFUNDOUTBYLIBER;
	task.task_data = *pFundTransfer;
	this->task_queue.push(task);
};

void TdApi::OnErrRtnFundOutByLiber(CSecurityFtdcInputFundTransferField *pInputFundTransfer, CSecurityFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNFUNDOUTBYLIBER;
	task.task_data = *pInputFundTransfer;
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
	this->task_queue.push(task);
};

void TdApi::OnRtnFundInByBank(CSecurityFtdcFundTransferField *pFundTransfer)
{
	Task task = Task();
	task.task_name = ONRTNFUNDINBYBANK;
	task.task_data = *pFundTransfer;
	this->task_queue.push(task);
};

void TdApi::OnRspQryFundTransferSerial(CSecurityFtdcFundTransferField *pFundTransfer, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYFUNDTRANSFERSERIAL;
	task.task_data = *pFundTransfer;
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

void TdApi::OnRspFundInterTransfer(CSecurityFtdcFundInterTransferField *pFundInterTransfer, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPFUNDINTERTRANSFER;
	task.task_data = *pFundInterTransfer;
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

void TdApi::OnRspQryFundInterTransferSerial(CSecurityFtdcFundInterTransferSerialField *pFundInterTransferSerial, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	Task task = Task();
	task.task_name = ONRSPQRYFUNDINTERTRANSFERSERIAL;
	task.task_data = *pFundInterTransferSerial;
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

void TdApi::OnRtnFundInterTransferSerial(CSecurityFtdcFundInterTransferSerialField *pFundInterTransferSerial)
{
	Task task = Task();
	task.task_name = ONRTNFUNDINTERTRANSFERSERIAL;
	task.task_data = *pFundInterTransferSerial;
	this->task_queue.push(task);
};

void TdApi::OnErrRtnFundInterTransfer(CSecurityFtdcFundInterTransferField *pFundInterTransfer, CSecurityFtdcRspInfoField *pRspInfo)
{
	Task task = Task();
	task.task_name = ONERRRTNFUNDINTERTRANSFER;
	task.task_data = *pFundInterTransfer;
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

			case ONRSPORDERINSERT:
			{
				this->processRspOrderInsert(task);
				break;
			}

			case ONRSPORDERACTION:
			{
				this->processRspOrderAction(task);
				break;
			}

			case ONRSPUSERPASSWORDUPDATE:
			{
				this->processRspUserPasswordUpdate(task);
				break;
			}

			case ONRSPTRADINGACCOUNTPASSWORDUPDATE:
			{
				this->processRspTradingAccountPasswordUpdate(task);
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

			case ONRSPQRYDEPTHMARKETDATA:
			{
				this->processRspQryDepthMarketData(task);
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

			case ONRTNORDER:
			{
				this->processRtnOrder(task);
				break;
			}

			case ONRTNTRADE:
			{
				this->processRtnTrade(task);
				break;
			}

			case ONERRRTNORDERINSERT:
			{
				this->processErrRtnOrderInsert(task);
				break;
			}

			case ONERRRTNORDERACTION:
			{
				this->processErrRtnOrderAction(task);
				break;
			}

			case ONRSPFUNDOUTBYLIBER:
			{
				this->processRspFundOutByLiber(task);
				break;
			}

			case ONRTNFUNDOUTBYLIBER:
			{
				this->processRtnFundOutByLiber(task);
				break;
			}

			case ONERRRTNFUNDOUTBYLIBER:
			{
				this->processErrRtnFundOutByLiber(task);
				break;
			}

			case ONRTNFUNDINBYBANK:
			{
				this->processRtnFundInByBank(task);
				break;
			}

			case ONRSPQRYFUNDTRANSFERSERIAL:
			{
				this->processRspQryFundTransferSerial(task);
				break;
			}

			case ONRSPFUNDINTERTRANSFER:
			{
				this->processRspFundInterTransfer(task);
				break;
			}

			case ONRSPQRYFUNDINTERTRANSFERSERIAL:
			{
				this->processRspQryFundInterTransferSerial(task);
				break;
			}

			case ONRTNFUNDINTERTRANSFERSERIAL:
			{
				this->processRtnFundInterTransferSerial(task);
				break;
			}

			case ONERRRTNFUNDINTERTRANSFER:
			{
				this->processErrRtnFundInterTransfer(task);
				break;
			}
		}
	}
}

void TdApi::processFrontConnected(Task task)
{
	this->onFrontConnected();
};

void TdApi::processFrontDisconnected(Task task)
{
	this->onFrontDisconnected(task.task_id);
};

void TdApi::processHeartBeatWarning(Task task)
{
	this->onHeartBeatWarning(task.task_id);
};

void TdApi::processRspError(Task task)
{
	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspError(error, task.task_id, task.task_last);
};

void TdApi::processRspUserLogin(Task task)
{
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

void TdApi::processRspUserLogout(Task task)
{
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

void TdApi::processRspOrderInsert(Task task)
{
	CSecurityFtdcInputOrderField task_data = any_cast<CSecurityFtdcInputOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Direction"] = task_data.Direction;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["BrokerID"] = task_data.BrokerID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderInsert(data, error, task.task_id, task.task_last);
};

void TdApi::processRspOrderAction(Task task)
{
	CSecurityFtdcInputOrderActionField task_data = any_cast<CSecurityFtdcInputOrderActionField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["SessionID"] = task_data.SessionID;
	data["VolumeChange"] = task_data.VolumeChange;
	data["BrokerID"] = task_data.BrokerID;
	data["RequestID"] = task_data.RequestID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["FrontID"] = task_data.FrontID;
	data["BranchPBU"] = task_data.BranchPBU;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspOrderAction(data, error, task.task_id, task.task_last);
};

void TdApi::processRspUserPasswordUpdate(Task task)
{
	CSecurityFtdcUserPasswordUpdateField task_data = any_cast<CSecurityFtdcUserPasswordUpdateField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspUserPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspTradingAccountPasswordUpdate(Task task)
{
	CSecurityFtdcTradingAccountPasswordUpdateField task_data = any_cast<CSecurityFtdcTradingAccountPasswordUpdateField>(task.task_data);
	dict data;
	data["NewPassword"] = task_data.NewPassword;
	data["OldPassword"] = task_data.OldPassword;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspTradingAccountPasswordUpdate(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryExchange(Task task)
{
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

void TdApi::processRspQryInstrument(Task task)
{
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

void TdApi::processRspQryInvestor(Task task)
{
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

void TdApi::processRspQryTradingCode(Task task)
{
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

void TdApi::processRspQryTradingAccount(Task task)
{
	CSecurityFtdcTradingAccountField task_data = any_cast<CSecurityFtdcTradingAccountField>(task.task_data);
	dict data;
	data["MarginTradeAmount"] = task_data.MarginTradeAmount;
	data["FrozenTransferFee"] = task_data.FrozenTransferFee;
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
	data["TradingDay"] = task_data.TradingDay;
	data["BrokerID"] = task_data.BrokerID;
	data["FrozenCash"] = task_data.FrozenCash;
	data["Withdraw"] = task_data.Withdraw;
	data["ReverseRepurchaseAmount"] = task_data.ReverseRepurchaseAmount;
	data["StampTax"] = task_data.StampTax;
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

void TdApi::processRspQryDepthMarketData(Task task)
{
	CSecurityFtdcDepthMarketDataField task_data = any_cast<CSecurityFtdcDepthMarketDataField>(task.task_data);
	dict data;
	data["HighestPrice"] = task_data.HighestPrice;
	data["BidPrice5"] = task_data.BidPrice5;
	data["BidPrice4"] = task_data.BidPrice4;
	data["BidPrice1"] = task_data.BidPrice1;
	data["BidPrice3"] = task_data.BidPrice3;
	data["BidPrice2"] = task_data.BidPrice2;
	data["LowerLimitPrice"] = task_data.LowerLimitPrice;
	data["OpenPrice"] = task_data.OpenPrice;
	data["AskPrice5"] = task_data.AskPrice5;
	data["AskPrice4"] = task_data.AskPrice4;
	data["AskPrice3"] = task_data.AskPrice3;
	data["PreClosePrice"] = task_data.PreClosePrice;
	data["AskPrice1"] = task_data.AskPrice1;
	data["PreSettlementPrice"] = task_data.PreSettlementPrice;
	data["AskVolume1"] = task_data.AskVolume1;
	data["UpdateTime"] = task_data.UpdateTime;
	data["UpdateMillisec"] = task_data.UpdateMillisec;
	data["AveragePrice"] = task_data.AveragePrice;
	data["BidVolume5"] = task_data.BidVolume5;
	data["BidVolume4"] = task_data.BidVolume4;
	data["BidVolume3"] = task_data.BidVolume3;
	data["BidVolume2"] = task_data.BidVolume2;
	data["PreOpenInterest"] = task_data.PreOpenInterest;
	data["AskPrice2"] = task_data.AskPrice2;
	data["Volume"] = task_data.Volume;
	data["AskVolume3"] = task_data.AskVolume3;
	data["AskVolume2"] = task_data.AskVolume2;
	data["AskVolume5"] = task_data.AskVolume5;
	data["AskVolume4"] = task_data.AskVolume4;
	data["UpperLimitPrice"] = task_data.UpperLimitPrice;
	data["BidVolume1"] = task_data.BidVolume1;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ClosePrice"] = task_data.ClosePrice;
	data["ExchangeID"] = task_data.ExchangeID;
	data["TradingDay"] = task_data.TradingDay;
	data["PreDelta"] = task_data.PreDelta;
	data["OpenInterest"] = task_data.OpenInterest;
	data["CurrDelta"] = task_data.CurrDelta;
	data["Turnover"] = task_data.Turnover;
	data["LastPrice"] = task_data.LastPrice;
	data["SettlementPrice"] = task_data.SettlementPrice;
	data["ExchangeInstID"] = task_data.ExchangeInstID;
	data["LowestPrice"] = task_data.LowestPrice;
	data["ActionDay"] = task_data.ActionDay;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryDepthMarketData(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryBondInterest(Task task)
{
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

void TdApi::processRspQryMarketRationInfo(Task task)
{
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

void TdApi::processRspQryInstrumentCommissionRate(Task task)
{
	CSecurityFtdcInstrumentCommissionRateField task_data = any_cast<CSecurityFtdcInstrumentCommissionRateField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
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

void TdApi::processRspQryETFInstrument(Task task)
{
	CSecurityFtdcETFInstrumentField task_data = any_cast<CSecurityFtdcETFInstrumentField>(task.task_data);
	dict data;
	data["ETFInstrumentID"] = task_data.ETFInstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["ETFPurRedInstrumentID"] = task_data.ETFPurRedInstrumentID;
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

void TdApi::processRspQryETFBasket(Task task)
{
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

void TdApi::processRspQryOFInstrument(Task task)
{
	CSecurityFtdcOFInstrumentField task_data = any_cast<CSecurityFtdcOFInstrumentField>(task.task_data);
	dict data;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["NetPrice"] = task_data.NetPrice;
	data["Creationredemption"] = task_data.Creationredemption;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspQryOFInstrument(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQrySFInstrument(Task task)
{
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

void TdApi::processRspQryOrder(Task task)
{
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

void TdApi::processRspQryTrade(Task task)
{
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

void TdApi::processRspQryInvestorPosition(Task task)
{
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

void TdApi::processRtnOrder(Task task)
{
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

	this->onRtnOrder(data);
};

void TdApi::processRtnTrade(Task task)
{
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

	this->onRtnTrade(data);
};

void TdApi::processErrRtnOrderInsert(Task task)
{
	CSecurityFtdcInputOrderField task_data = any_cast<CSecurityFtdcInputOrderField>(task.task_data);
	dict data;
	data["ContingentCondition"] = task_data.ContingentCondition;
	data["CombOffsetFlag"] = task_data.CombOffsetFlag;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["UserForceClose"] = task_data.UserForceClose;
	data["Direction"] = task_data.Direction;
	data["VolumeTotalOriginal"] = task_data.VolumeTotalOriginal;
	data["OrderPriceType"] = task_data.OrderPriceType;
	data["TimeCondition"] = task_data.TimeCondition;
	data["IsAutoSuspend"] = task_data.IsAutoSuspend;
	data["StopPrice"] = task_data.StopPrice;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["MinVolume"] = task_data.MinVolume;
	data["ForceCloseReason"] = task_data.ForceCloseReason;
	data["BrokerID"] = task_data.BrokerID;
	data["CombHedgeFlag"] = task_data.CombHedgeFlag;
	data["GTDDate"] = task_data.GTDDate;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["OrderRef"] = task_data.OrderRef;
	data["InvestorID"] = task_data.InvestorID;
	data["VolumeCondition"] = task_data.VolumeCondition;
	data["RequestID"] = task_data.RequestID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderInsert(data, error);
};

void TdApi::processErrRtnOrderAction(Task task)
{
	CSecurityFtdcOrderActionField task_data = any_cast<CSecurityFtdcOrderActionField>(task.task_data);
	dict data;
	data["ActionTime"] = task_data.ActionTime;
	data["InvestorID"] = task_data.InvestorID;
	data["UserID"] = task_data.UserID;
	data["LimitPrice"] = task_data.LimitPrice;
	data["ClientID"] = task_data.ClientID;
	data["InstallID"] = task_data.InstallID;
	data["ParticipantID"] = task_data.ParticipantID;
	data["OrderActionRef"] = task_data.OrderActionRef;
	data["VolumeChange"] = task_data.VolumeChange;
	data["SessionID"] = task_data.SessionID;
	data["ActionFlag"] = task_data.ActionFlag;
	data["InstrumentID"] = task_data.InstrumentID;
	data["ExchangeID"] = task_data.ExchangeID;
	data["StatusMsg"] = task_data.StatusMsg;
	data["BrokerID"] = task_data.BrokerID;
	data["InstrumentType"] = task_data.InstrumentType;
	data["ActionDate"] = task_data.ActionDate;
	data["OrderLocalID"] = task_data.OrderLocalID;
	data["BranchID"] = task_data.BranchID;
	data["BusinessUnit"] = task_data.BusinessUnit;
	data["OrderRef"] = task_data.OrderRef;
	data["ActionLocalID"] = task_data.ActionLocalID;
	data["RequestID"] = task_data.RequestID;
	data["FrontID"] = task_data.FrontID;
	data["BranchPBU"] = task_data.BranchPBU;
	data["OrderActionStatus"] = task_data.OrderActionStatus;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnOrderAction(data, error);
};

void TdApi::processRspFundOutByLiber(Task task)
{
	CSecurityFtdcInputFundTransferField task_data = any_cast<CSecurityFtdcInputFundTransferField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountType"] = task_data.AccountType;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFundOutByLiber(data, error, task.task_id, task.task_last);
};

void TdApi::processRtnFundOutByLiber(Task task)
{
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

	this->onRtnFundOutByLiber(data);
};

void TdApi::processErrRtnFundOutByLiber(Task task)
{
	CSecurityFtdcInputFundTransferField task_data = any_cast<CSecurityFtdcInputFundTransferField>(task.task_data);
	dict data;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["AccountType"] = task_data.AccountType;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["Digest"] = task_data.Digest;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnFundOutByLiber(data, error);
};

void TdApi::processRtnFundInByBank(Task task)
{
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

	this->onRtnFundInByBank(data);
};

void TdApi::processRspQryFundTransferSerial(Task task)
{
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

void TdApi::processRspFundInterTransfer(Task task)
{
	CSecurityFtdcFundInterTransferField task_data = any_cast<CSecurityFtdcFundInterTransferField>(task.task_data);
	dict data;
	data["SerialID"] = task_data.SerialID;
	data["TransferType"] = task_data.TransferType;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onRspFundInterTransfer(data, error, task.task_id, task.task_last);
};

void TdApi::processRspQryFundInterTransferSerial(Task task)
{
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

void TdApi::processRtnFundInterTransferSerial(Task task)
{
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

	this->onRtnFundInterTransferSerial(data);
};

void TdApi::processErrRtnFundInterTransfer(Task task)
{
	CSecurityFtdcFundInterTransferField task_data = any_cast<CSecurityFtdcFundInterTransferField>(task.task_data);
	dict data;
	data["SerialID"] = task_data.SerialID;
	data["TransferType"] = task_data.TransferType;
	data["UserID"] = task_data.UserID;
	data["InvestorID"] = task_data.InvestorID;
	data["BrokerID"] = task_data.BrokerID;
	data["Password"] = task_data.Password;
	data["TradeAmount"] = task_data.TradeAmount;
	data["AccountID"] = task_data.AccountID;

	CSecurityFtdcRspInfoField task_error = any_cast<CSecurityFtdcRspInfoField>(task.task_error);
	dict error;
	error["ErrorMsg"] = task_error.ErrorMsg;
	error["ErrorID"] = task_error.ErrorID;

	this->onErrRtnFundInterTransfer(data, error);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::createFtdcTraderApi(string pszFlowPath)
{
	this->api = CSecurityFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};

void TdApi::release()
{
	this->api->Release();
};

void TdApi::init()
{
	this->api->Init();
};

int TdApi::join()
{
	int i = this->api->Join();
	return i;
};

string TdApi::getTradingDay()
{
	string day = this->api->GetTradingDay();
	return day;
};

void TdApi::registerFront(string pszFrontAddress)
{
	this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

void TdApi::subscribePrivateTopic(int nType)
{
	//该函数为手动编写
	SECURITY_TE_RESUME_TYPE type;

	switch (nType)
	{
		case 0:
		{
			type = SECURITY_TERT_RESTART;
			break;
		};

		case 1:
		{
			type = SECURITY_TERT_RESUME;
			break;
		};

		case 2:
		{
			type = SECURITY_TERT_QUICK;
			break;
		};
	}

	this->api->SubscribePrivateTopic(type);


};

void TdApi::subscribePublicTopic(int nType)
{
	//该函数为手动编写
	SECURITY_TE_RESUME_TYPE type;

	switch (nType)
	{
		case 0:
		{
			type = SECURITY_TERT_RESTART;
			break;
		};

		case 1:
		{
			type = SECURITY_TERT_RESUME;
			break;
		};

		case 2:
		{
			type = SECURITY_TERT_QUICK;
			break;
		};
	}

	this->api->SubscribePublicTopic(type);
};

int TdApi::reqUserLogin(dict req, int nRequestID)
{
	CSecurityFtdcReqUserLoginField myreq = CSecurityFtdcReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "MacAddress", myreq.MacAddress);
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
	int i = this->api->ReqUserLogin(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserLogout(dict req, int nRequestID)
{
	CSecurityFtdcUserLogoutField myreq = CSecurityFtdcUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserLogout(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderInsert(dict req, int nRequestID)
{
	CSecurityFtdcInputOrderField myreq = CSecurityFtdcInputOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ContingentCondition", &myreq.ContingentCondition);
	getChar(req, "CombOffsetFlag", myreq.CombOffsetFlag);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "LimitPrice", myreq.LimitPrice);
	getInt(req, "UserForceClose", &myreq.UserForceClose);
	getChar(req, "Direction", &myreq.Direction);
	getInt(req, "VolumeTotalOriginal", &myreq.VolumeTotalOriginal);
	getChar(req, "OrderPriceType", &myreq.OrderPriceType);
	getChar(req, "TimeCondition", &myreq.TimeCondition);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getInt(req, "IsAutoSuspend", &myreq.IsAutoSuspend);
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getInt(req, "MinVolume", &myreq.MinVolume);
	getChar(req, "ForceCloseReason", &myreq.ForceCloseReason);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "CombHedgeFlag", myreq.CombHedgeFlag);
	getChar(req, "GTDDate", myreq.GTDDate);
	getChar(req, "BusinessUnit", myreq.BusinessUnit);
	getChar(req, "OrderRef", myreq.OrderRef);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "VolumeCondition", &myreq.VolumeCondition);
	getInt(req, "RequestID", &myreq.RequestID);
	int i = this->api->ReqOrderInsert(&myreq, nRequestID);
	return i;
};

int TdApi::reqOrderAction(dict req, int nRequestID)
{
	CSecurityFtdcInputOrderActionField myreq = CSecurityFtdcInputOrderActionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "OrderLocalID", myreq.OrderLocalID);
	getInt(req, "OrderActionRef", &myreq.OrderActionRef);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "OrderRef", myreq.OrderRef);
	getChar(req, "InvestorID", myreq.InvestorID);
	getInt(req, "SessionID", &myreq.SessionID);
	getInt(req, "VolumeChange", &myreq.VolumeChange);
	getChar(req, "BrokerID", myreq.BrokerID);
	getInt(req, "RequestID", &myreq.RequestID);
	getChar(req, "ActionFlag", &myreq.ActionFlag);
	getInt(req, "FrontID", &myreq.FrontID);
	getChar(req, "BranchPBU", myreq.BranchPBU);
	int i = this->api->ReqOrderAction(&myreq, nRequestID);
	return i;
};

int TdApi::reqUserPasswordUpdate(dict req, int nRequestID)
{
	CSecurityFtdcUserPasswordUpdateField myreq = CSecurityFtdcUserPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "NewPassword", myreq.NewPassword);
	getChar(req, "OldPassword", myreq.OldPassword);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqUserPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqTradingAccountPasswordUpdate(dict req, int nRequestID)
{
	CSecurityFtdcTradingAccountPasswordUpdateField myreq = CSecurityFtdcTradingAccountPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "NewPassword", myreq.NewPassword);
	getChar(req, "OldPassword", myreq.OldPassword);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqTradingAccountPasswordUpdate(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryExchange(dict req, int nRequestID)
{
	CSecurityFtdcQryExchangeField myreq = CSecurityFtdcQryExchangeField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryExchange(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrument(dict req, int nRequestID)
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

int TdApi::reqQryInvestor(dict req, int nRequestID)
{
	CSecurityFtdcQryInvestorField myreq = CSecurityFtdcQryInvestorField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestor(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryTradingCode(dict req, int nRequestID)
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

int TdApi::reqQryTradingAccount(dict req, int nRequestID)
{
	CSecurityFtdcQryTradingAccountField myreq = CSecurityFtdcQryTradingAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryTradingAccount(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryDepthMarketData(dict req, int nRequestID)
{
	CSecurityFtdcQryDepthMarketDataField myreq = CSecurityFtdcQryDepthMarketDataField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	int i = this->api->ReqQryDepthMarketData(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryBondInterest(dict req, int nRequestID)
{
	CSecurityFtdcQryBondInterestField myreq = CSecurityFtdcQryBondInterestField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryBondInterest(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryMarketRationInfo(dict req, int nRequestID)
{
	CSecurityFtdcQryMarketRationInfoField myreq = CSecurityFtdcQryMarketRationInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryMarketRationInfo(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryInstrumentCommissionRate(dict req, int nRequestID)
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

int TdApi::reqQryETFInstrument(dict req, int nRequestID)
{
	CSecurityFtdcQryETFInstrumentField myreq = CSecurityFtdcQryETFInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ETFInstrumentID", myreq.ETFInstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryETFInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryETFBasket(dict req, int nRequestID)
{
	CSecurityFtdcQryETFBasketField myreq = CSecurityFtdcQryETFBasketField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ETFInstrumentID", myreq.ETFInstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQryETFBasket(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOFInstrument(dict req, int nRequestID)
{
	CSecurityFtdcQryOFInstrumentField myreq = CSecurityFtdcQryOFInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "ExchangeID", myreq.ExchangeID);
	getChar(req, "OFInstrumentID", myreq.OFInstrumentID);
	int i = this->api->ReqQryOFInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQrySFInstrument(dict req, int nRequestID)
{
	CSecurityFtdcQrySFInstrumentField myreq = CSecurityFtdcQrySFInstrumentField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "SFInstrumentID", myreq.SFInstrumentID);
	getChar(req, "ExchangeID", myreq.ExchangeID);
	int i = this->api->ReqQrySFInstrument(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryOrder(dict req, int nRequestID)
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

int TdApi::reqQryTrade(dict req, int nRequestID)
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

int TdApi::reqQryInvestorPosition(dict req, int nRequestID)
{
	CSecurityFtdcQryInvestorPositionField myreq = CSecurityFtdcQryInvestorPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "InstrumentID", myreq.InstrumentID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	int i = this->api->ReqQryInvestorPosition(&myreq, nRequestID);
	return i;
};

int TdApi::reqFundOutByLiber(dict req, int nRequestID)
{
	CSecurityFtdcInputFundTransferField myreq = CSecurityFtdcInputFundTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "AccountType", &myreq.AccountType);
	getChar(req, "Password", myreq.Password);
	getChar(req, "Password", myreq.Password);
	getChar(req, "Digest", myreq.Digest);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqFundOutByLiber(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryFundTransferSerial(dict req, int nRequestID)
{
	CSecurityFtdcQryFundTransferSerialField myreq = CSecurityFtdcQryFundTransferSerialField();
	memset(&myreq, 0, sizeof(myreq));
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "AccountType", &myreq.AccountType);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqQryFundTransferSerial(&myreq, nRequestID);
	return i;
};

int TdApi::reqFundInterTransfer(dict req, int nRequestID)
{
	CSecurityFtdcFundInterTransferField myreq = CSecurityFtdcFundInterTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "SerialID", &myreq.SerialID);
	getChar(req, "TransferType", &myreq.TransferType);
	getChar(req, "UserID", myreq.UserID);
	getChar(req, "InvestorID", myreq.InvestorID);
	getChar(req, "BrokerID", myreq.BrokerID);
	getChar(req, "Password", myreq.Password);
	getChar(req, "Password", myreq.Password);
	getChar(req, "AccountID", myreq.AccountID);
	int i = this->api->ReqFundInterTransfer(&myreq, nRequestID);
	return i;
};

int TdApi::reqQryFundInterTransferSerial(dict req, int nRequestID)
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

struct TdApiWrap : TdApi, wrapper < TdApi >
{
	virtual void onFrontConnected()
	{
		PyLock lock;
		this->get_override("onFrontConnected")();
	};

	virtual void onFrontDisconnected(int i)
	{
		PyLock lock;
		this->get_override("onFrontDisconnected")(i);
	};

	virtual void onHeartBeatWarning(int i)
	{
		PyLock lock;
		this->get_override("onHeartBeatWarning")(i);
	};

	virtual void onRspError(dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspError")(error, id, last);
	};

	virtual void onRspUserLogin(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspUserLogin")(data, error, id, last);
	};

	virtual void onRspUserLogout(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspUserLogout")(data, error, id, last);
	};

	virtual void onRspOrderInsert(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspOrderInsert")(data, error, id, last);
	};

	virtual void onRspOrderAction(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspOrderAction")(data, error, id, last);
	};

	virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspUserPasswordUpdate")(data, error, id, last);
	};

	virtual void onRspTradingAccountPasswordUpdate(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspTradingAccountPasswordUpdate")(data, error, id, last);
	};

	virtual void onRspQryExchange(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspQryExchange")(data, error, id, last);
	};

	virtual void onRspQryInstrument(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspQryInstrument")(data, error, id, last);
	};

	virtual void onRspQryInvestor(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspQryInvestor")(data, error, id, last);
	};

	virtual void onRspQryTradingCode(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspQryTradingCode")(data, error, id, last);
	};

	virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspQryTradingAccount")(data, error, id, last);
	};

	virtual void onRspQryDepthMarketData(dict data, dict error, int id, bool last) 
	{
		PyLock lock;
		this->get_override("onRspQryDepthMarketData")(data, error, id, last);
	};

	virtual void onRspQryBondInterest(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspQryBondInterest")(data, error, id, last);
	};

	virtual void onRspQryMarketRationInfo(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspQryMarketRationInfo")(data, error, id, last);
	};

	virtual void onRspQryInstrumentCommissionRate(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspQryInstrumentCommissionRate")(data, error, id, last);
	};

	virtual void onRspQryETFInstrument(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspQryETFInstrument")(data, error, id, last);
	};

	virtual void onRspQryETFBasket(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspQryETFBasket")(data, error, id, last);
	};

	virtual void onRspQryOFInstrument(dict data, dict error, int id, bool last) 
	{
		PyLock lock;
		this->get_override("onRspQryOFInstrument")(data, error, id, last);
	};

	virtual void onRspQrySFInstrument(dict data, dict error, int id, bool last) 
	{
		PyLock lock;
		this->get_override("onRspQrySFInstrument")(data, error, id, last);
	};

	virtual void onRspQryOrder(dict data, dict error, int id, bool last) 
	{
		PyLock lock;
		this->get_override("onRspQryOrder")(data, error, id, last);
	};

	virtual void onRspQryTrade(dict data, dict error, int id, bool last) 
	{
		PyLock lock;
		this->get_override("onRspQryTrade")(data, error, id, last);
	};

	virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last) 
	{
		PyLock lock;
		this->get_override("onRspQryInvestorPosition")(data, error, id, last);
	};

	virtual void onRtnOrder(dict data) 
	{
		PyLock lock;
		this->get_override("onRtnOrder")(data);
	};

	virtual void onRtnTrade(dict data) 
	{
		PyLock lock;
		this->get_override("onRtnTrade")(data);
	};

	virtual void onErrRtnOrderInsert(dict data, dict error) 
	{
		PyLock lock;
		this->get_override("onErrRtnOrderInsert")(data, error);
	};

	virtual void onErrRtnOrderAction(dict data, dict error) 
	{
		PyLock lock;
		this->get_override("onErrRtnOrderAction")(data, error);
	};

	virtual void onRspFundOutByLiber(dict data, dict error, int id, bool last)
	{
		PyLock lock;
		this->get_override("onRspFundOutByLiber")(data, error, id, last);
	};

	virtual void onRtnFundOutByLiber(dict data)
	{
		PyLock lock;
		this->get_override("onRtnFundOutByLiber")(data);
	};

	virtual void onErrRtnFundOutByLiber(dict data, dict error) 
	{
		PyLock lock;
		this->get_override("onErrRtnFundOutByLiber")(data, error);
	};

	virtual void onRtnFundInByBank(dict data) 
	{
		PyLock lock;
		this->get_override("onRtnFundInByBank")(data);
	};

	virtual void onRspQryFundTransferSerial(dict data, dict error, int id, bool last) 
	{
		PyLock lock;
		this->get_override("onRspQryFundTransferSerial")(data, error, id, last);
	};

	virtual void onRspFundInterTransfer(dict data, dict error, int id, bool last) 
	{
		PyLock lock;
		this->get_override("onRspFundInterTransfer")(data, error, id, last);
	};

	virtual void onRspQryFundInterTransferSerial(dict data, dict error, int id, bool last) 
	{
		PyLock lock;
		this->get_override("onRspQryFundInterTransferSerial")(data, error, id, last);
	};

	virtual void onRtnFundInterTransferSerial(dict data) 
	{
		PyLock lock;
		this->get_override("onRtnFundInterTransferSerial")(data);
	};

	virtual void onErrRtnFundInterTransfer(dict data, dict error) 
	{
		PyLock lock;
		this->get_override("onErrRtnFundInterTransfer")(data, error);
	};
};


BOOST_PYTHON_MODULE(vnltstd)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<TdApiWrap, boost::noncopyable>("TdApi")
		.def("createFtdcTraderApi", &TdApiWrap::createFtdcTraderApi)
		.def("release", &TdApiWrap::release)
		.def("init", &TdApiWrap::init)
		.def("join", &TdApiWrap::join)
		.def("getTradingDay", &TdApiWrap::getTradingDay)
		.def("registerFront", &TdApiWrap::registerFront)
		.def("subscribePrivateTopic", &TdApiWrap::subscribePrivateTopic)
		.def("subscribePublicTopic", &TdApiWrap::subscribePublicTopic)
		.def("reqUserLogin", &TdApiWrap::reqUserLogin)
		.def("reqUserLogout", &TdApiWrap::reqUserLogout)
		.def("reqOrderInsert", &TdApiWrap::reqOrderInsert)
		.def("reqOrderAction", &TdApiWrap::reqOrderAction)
		.def("reqUserPasswordUpdate", &TdApiWrap::reqUserPasswordUpdate)
		.def("reqTradingAccountPasswordUpdate", &TdApiWrap::reqTradingAccountPasswordUpdate)
		.def("reqQryExchange", &TdApiWrap::reqQryExchange)
		.def("reqQryInstrument", &TdApiWrap::reqQryInstrument)
		.def("reqQryInvestor", &TdApiWrap::reqQryInvestor)
		.def("reqQryTradingCode", &TdApiWrap::reqQryTradingCode)
		.def("reqQryTradingAccount", &TdApiWrap::reqQryTradingAccount)
		.def("reqQryDepthMarketData", &TdApiWrap::reqQryDepthMarketData)
		.def("reqQryBondInterest", &TdApiWrap::reqQryBondInterest)
		.def("reqQryMarketRationInfo", &TdApiWrap::reqQryMarketRationInfo)
		.def("reqQryInstrumentCommissionRate", &TdApiWrap::reqQryInstrumentCommissionRate)
		.def("reqQryETFInstrument", &TdApiWrap::reqQryETFInstrument)
		.def("reqQryETFBasket", &TdApiWrap::reqQryETFBasket)
		.def("reqQryOFInstrument", &TdApiWrap::reqQryOFInstrument)
		.def("reqQrySFInstrument", &TdApiWrap::reqQrySFInstrument)
		.def("reqQryOrder", &TdApiWrap::reqQryOrder)
		.def("reqQryTrade", &TdApiWrap::reqQryTrade)
		.def("reqQryInvestorPosition", &TdApiWrap::reqQryInvestorPosition)
		.def("reqFundOutByLiber", &TdApiWrap::reqFundOutByLiber)
		.def("reqQryFundTransferSerial", &TdApiWrap::reqQryFundTransferSerial)
		.def("reqFundInterTransfer", &TdApiWrap::reqFundInterTransfer)
		.def("reqQryFundInterTransferSerial", &TdApiWrap::reqQryFundInterTransferSerial)

		.def("onFrontConnected", pure_virtual(&TdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&TdApiWrap::onFrontDisconnected))
		.def("onHeartBeatWarning", pure_virtual(&TdApiWrap::onHeartBeatWarning))
		.def("onRspError", pure_virtual(&TdApiWrap::onRspError))
		.def("onRspUserLogin", pure_virtual(&TdApiWrap::onRspUserLogin))
		.def("onRspUserLogout", pure_virtual(&TdApiWrap::onRspUserLogout))
		.def("onRspOrderInsert", pure_virtual(&TdApiWrap::onRspOrderInsert))
		.def("onRspOrderAction", pure_virtual(&TdApiWrap::onRspOrderAction))
		.def("onRspUserPasswordUpdate", pure_virtual(&TdApiWrap::onRspUserPasswordUpdate))
		.def("onRspTradingAccountPasswordUpdate", pure_virtual(&TdApiWrap::onRspTradingAccountPasswordUpdate))
		.def("onRspQryExchange", pure_virtual(&TdApiWrap::onRspQryExchange))
		.def("onRspQryInstrument", pure_virtual(&TdApiWrap::onRspQryInstrument))
		.def("onRspQryInvestor", pure_virtual(&TdApiWrap::onRspQryInvestor))
		.def("onRspQryTradingCode", pure_virtual(&TdApiWrap::onRspQryTradingCode))
		.def("onRspQryTradingAccount", pure_virtual(&TdApiWrap::onRspQryTradingAccount))
		.def("onRspQryDepthMarketData", pure_virtual(&TdApiWrap::onRspQryDepthMarketData))
		.def("onRspQryBondInterest", pure_virtual(&TdApiWrap::onRspQryBondInterest))
		.def("onRspQryMarketRationInfo", pure_virtual(&TdApiWrap::onRspQryMarketRationInfo))
		.def("onRspQryInstrumentCommissionRate", pure_virtual(&TdApiWrap::onRspQryInstrumentCommissionRate))
		.def("onRspQryETFInstrument", pure_virtual(&TdApiWrap::onRspQryETFInstrument))
		.def("onRspQryETFBasket", pure_virtual(&TdApiWrap::onRspQryETFBasket))
		.def("onRspQryOFInstrument", pure_virtual(&TdApiWrap::onRspQryOFInstrument))
		.def("onRspQrySFInstrument", pure_virtual(&TdApiWrap::onRspQrySFInstrument))
		.def("onRspQryOrder", pure_virtual(&TdApiWrap::onRspQryOrder))
		.def("onRspQryTrade", pure_virtual(&TdApiWrap::onRspQryTrade))
		.def("onRspQryInvestorPosition", pure_virtual(&TdApiWrap::onRspQryInvestorPosition))
		.def("onRtnOrder", pure_virtual(&TdApiWrap::onRtnOrder))
		.def("onRtnTrade", pure_virtual(&TdApiWrap::onRtnTrade))
		.def("onErrRtnOrderInsert", pure_virtual(&TdApiWrap::onErrRtnOrderInsert))
		.def("onErrRtnOrderAction", pure_virtual(&TdApiWrap::onErrRtnOrderAction))
		.def("onRspFundOutByLiber", pure_virtual(&TdApiWrap::onRspFundOutByLiber))
		.def("onRtnFundOutByLiber", pure_virtual(&TdApiWrap::onRtnFundOutByLiber))
		.def("onErrRtnFundOutByLiber", pure_virtual(&TdApiWrap::onErrRtnFundOutByLiber))
		.def("onRtnFundInByBank", pure_virtual(&TdApiWrap::onRtnFundInByBank))
		.def("onRspQryFundTransferSerial", pure_virtual(&TdApiWrap::onRspQryFundTransferSerial))
		.def("onRspFundInterTransfer", pure_virtual(&TdApiWrap::onRspFundInterTransfer))
		.def("onRspQryFundInterTransferSerial", pure_virtual(&TdApiWrap::onRspQryFundInterTransferSerial))
		.def("onRtnFundInterTransferSerial", pure_virtual(&TdApiWrap::onRtnFundInterTransferSerial))
		.def("onErrRtnFundInterTransfer", pure_virtual(&TdApiWrap::onErrRtnFundInterTransfer))
		;
}