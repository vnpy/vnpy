// TdApi.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnsectd.h"


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
	Task *task = new Task();
	task->task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

void TdApi::OnFrontDisconnected(int nReason)
{
	Task *task = new Task();
	task->task_name = ONFRONTDISCONNECTED;

	if (nReason)
	{
		task->task_id = nReason;
	}
	this->task_queue.push(task);
};

void TdApi::OnRtnNotice(DFITCSECRspNoticeField *pNotice)
{
	Task *task = new Task();
	task->task_name = ONRTNNOTICE;

	if (pNotice)
	{
		DFITCSECRspNoticeField *task_data = new DFITCSECRspNoticeField();
		*task_data = *pNotice;
		task->task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspError(DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPERROR;

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspStockUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKUSERLOGIN;

	if (pData)
	{
		DFITCSECRspUserLoginField *task_data = new DFITCSECRspUserLoginField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspStockUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKUSERLOGOUT;

	if (pData)
	{
		DFITCSECRspUserLogoutField *task_data = new DFITCSECRspUserLogoutField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspStockUserPasswordUpdate(DFITCSECRspPasswordUpdateField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKUSERPASSWORDUPDATE;

	if (pData)
	{
		DFITCSECRspPasswordUpdateField *task_data = new DFITCSECRspPasswordUpdateField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspStockEntrustOrder(DFITCStockRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKENTRUSTORDER;

	if (pData)
	{
		DFITCStockRspEntrustOrderField *task_data = new DFITCStockRspEntrustOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspStockWithdrawOrder(DFITCSECRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKWITHDRAWORDER;

	if (pData)
	{
		DFITCSECRspWithdrawOrderField *task_data = new DFITCSECRspWithdrawOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspStockQryEntrustOrder(DFITCStockRspQryEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYENTRUSTORDER;

	if (pData)
	{
		DFITCStockRspQryEntrustOrderField *task_data = new DFITCStockRspQryEntrustOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspStockQryRealTimeTrade(DFITCStockRspQryRealTimeTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYREALTIMETRADE;

	if (pData)
	{
		DFITCStockRspQryRealTimeTradeField *task_data = new DFITCStockRspQryRealTimeTradeField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspStockQrySerialTrade(DFITCStockRspQrySerialTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYSERIALTRADE;

	if (pData)
	{
		DFITCStockRspQrySerialTradeField *task_data = new DFITCStockRspQrySerialTradeField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspStockQryPosition(DFITCStockRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYPOSITION;

	if (pData)
	{
		DFITCStockRspQryPositionField *task_data = new DFITCStockRspQryPositionField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspStockQryCapitalAccountInfo(DFITCStockRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYCAPITALACCOUNTINFO;

	if (pData)
	{
		DFITCStockRspQryCapitalAccountField *task_data = new DFITCStockRspQryCapitalAccountField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspStockQryAccountInfo(DFITCStockRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYACCOUNTINFO;

	if (pData)
	{
		DFITCStockRspQryAccountField *task_data = new DFITCStockRspQryAccountField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspStockQryShareholderInfo(DFITCStockRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYSHAREHOLDERINFO;

	if (pData)
	{
		DFITCStockRspQryShareholderField *task_data = new DFITCStockRspQryShareholderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspStockTransferFunds(DFITCStockRspTransferFundsField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKTRANSFERFUNDS;

	if (pData)
	{
		DFITCStockRspTransferFundsField *task_data = new DFITCStockRspTransferFundsField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspStockEntrustBatchOrder(DFITCStockRspEntrustBatchOrderField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKENTRUSTBATCHORDER;

	if (pData)
	{
		DFITCStockRspEntrustBatchOrderField *task_data = new DFITCStockRspEntrustBatchOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspStockWithdrawBatchOrder(DFITCStockRspWithdrawBatchOrderField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKWITHDRAWBATCHORDER;

	if (pData)
	{
		DFITCStockRspWithdrawBatchOrderField *task_data = new DFITCStockRspWithdrawBatchOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspStockCalcAbleEntrustQty(DFITCStockRspCalcAbleEntrustQtyField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKCALCABLEENTRUSTQTY;

	if (pData)
	{
		DFITCStockRspCalcAbleEntrustQtyField *task_data = new DFITCStockRspCalcAbleEntrustQtyField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspStockCalcAblePurchaseETFQty(DFITCStockRspCalcAblePurchaseETFQtyField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKCALCABLEPURCHASEETFQTY;

	if (pData)
	{
		DFITCStockRspCalcAblePurchaseETFQtyField *task_data = new DFITCStockRspCalcAblePurchaseETFQtyField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspStockQryFreezeFundsDetail(DFITCStockRspQryFreezeFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYFREEZEFUNDSDETAIL;

	if (pData)
	{
		DFITCStockRspQryFreezeFundsDetailField *task_data = new DFITCStockRspQryFreezeFundsDetailField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspStockQryFreezeStockDetail(DFITCStockRspQryFreezeStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYFREEZESTOCKDETAIL;

	if (pData)
	{
		DFITCStockRspQryFreezeStockDetailField *task_data = new DFITCStockRspQryFreezeStockDetailField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspStockQryTransferStockDetail(DFITCStockRspQryTransferStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYTRANSFERSTOCKDETAIL;

	if (pData)
	{
		DFITCStockRspQryTransferStockDetailField *task_data = new DFITCStockRspQryTransferStockDetailField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspStockQryTransferFundsDetail(DFITCStockRspQryTransferFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYTRANSFERFUNDSDETAIL;

	if (pData)
	{
		DFITCStockRspQryTransferFundsDetailField *task_data = new DFITCStockRspQryTransferFundsDetailField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspStockQryStockInfo(DFITCStockRspQryStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYSTOCKINFO;

	if (pData)
	{
		DFITCStockRspQryStockField *task_data = new DFITCStockRspQryStockField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspStockQryStockStaticInfo(DFITCStockRspQryStockStaticField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYSTOCKSTATICINFO;

	if (pData)
	{
		DFITCStockRspQryStockStaticField *task_data = new DFITCStockRspQryStockStaticField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspStockQryTradeTime(DFITCStockRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSTOCKQRYTRADETIME;

	if (pData)
	{
		DFITCStockRspQryTradeTimeField *task_data = new DFITCStockRspQryTradeTimeField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnStockEntrustOrderRtn(DFITCStockEntrustOrderRtnField * pData)
{
	Task *task = new Task();
	task->task_name = ONSTOCKENTRUSTORDERRTN;

	if (pData)
	{
		DFITCStockEntrustOrderRtnField *task_data = new DFITCStockEntrustOrderRtnField();
		*task_data = *pData;
		task->task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnStockTradeRtn(DFITCStockTradeRtnField * pData)
{
	Task *task = new Task();
	task->task_name = ONSTOCKTRADERTN;

	if (pData)
	{
		DFITCStockTradeRtnField *task_data = new DFITCStockTradeRtnField();
		*task_data = *pData;
		task->task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnStockWithdrawOrderRtn(DFITCStockWithdrawOrderRtnField * pData)
{
	Task *task = new Task();
	task->task_name = ONSTOCKWITHDRAWORDERRTN;

	if (pData)
	{
		DFITCStockWithdrawOrderRtnField *task_data = new DFITCStockWithdrawOrderRtnField();
		*task_data = *pData;
		task->task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspSOPUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPUSERLOGIN;

	if (pData)
	{
		DFITCSECRspUserLoginField *task_data = new DFITCSECRspUserLoginField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspSOPUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPUSERLOGOUT;

	if (pData)
	{
		DFITCSECRspUserLogoutField *task_data = new DFITCSECRspUserLogoutField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspSOPUserPasswordUpdate(DFITCSECRspPasswordUpdateField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPUSERPASSWORDUPDATE;

	if (pData)
	{
		DFITCSECRspPasswordUpdateField *task_data = new DFITCSECRspPasswordUpdateField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspSOPEntrustOrder(DFITCSOPRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPENTRUSTORDER;

	if (pData)
	{
		DFITCSOPRspEntrustOrderField *task_data = new DFITCSOPRspEntrustOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspSOPGroupSplit(DFITCSOPRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPGROUPSPLIT;

	if (pData)
	{
		DFITCSOPRspEntrustOrderField *task_data = new DFITCSOPRspEntrustOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryGroupPosition(DFITCSOPRspQryGroupPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYGROUPPOSITION;

	if (pData)
	{
		DFITCSOPRspQryGroupPositionField *task_data = new DFITCSOPRspQryGroupPositionField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSOPLockOUnLockStock(DFITCSOPRspLockOUnLockStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPLOCKOUNLOCKSTOCK;

	if (pData)
	{
		DFITCSOPRspLockOUnLockStockField *task_data = new DFITCSOPRspLockOUnLockStockField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSOPWithdrawOrder(DFITCSECRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPWITHDRAWORDER;

	if (pData)
	{
		DFITCSECRspWithdrawOrderField *task_data = new DFITCSECRspWithdrawOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryEntrustOrder(DFITCSOPRspQryEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYENTRUSTORDER;

	if (pData)
	{
		DFITCSOPRspQryEntrustOrderField *task_data = new DFITCSOPRspQryEntrustOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSOPQrySerialTrade(DFITCSOPRspQrySerialTradeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYSERIALTRADE;

	if (pData)
	{
		DFITCSOPRspQrySerialTradeField *task_data = new DFITCSOPRspQrySerialTradeField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryPosition(DFITCSOPRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYPOSITION;

	if (pData)
	{
		DFITCSOPRspQryPositionField *task_data = new DFITCSOPRspQryPositionField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryCollateralPosition(DFITCSOPRspQryCollateralPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYCOLLATERALPOSITION;

	if (pData)
	{
		DFITCSOPRspQryCollateralPositionField *task_data = new DFITCSOPRspQryCollateralPositionField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryCapitalAccountInfo(DFITCSOPRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYCAPITALACCOUNTINFO;

	if (pData)
	{
		DFITCSOPRspQryCapitalAccountField *task_data = new DFITCSOPRspQryCapitalAccountField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryAccountInfo(DFITCSOPRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYACCOUNTINFO;

	if (pData)
	{
		DFITCSOPRspQryAccountField *task_data = new DFITCSOPRspQryAccountField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryShareholderInfo(DFITCSOPRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYSHAREHOLDERINFO;

	if (pData)
	{
		DFITCSOPRspQryShareholderField *task_data = new DFITCSOPRspQryShareholderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspSOPCalcAbleEntrustQty(DFITCSOPRspCalcAbleEntrustQtyField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPCALCABLEENTRUSTQTY;

	if (pData)
	{
		DFITCSOPRspCalcAbleEntrustQtyField *task_data = new DFITCSOPRspCalcAbleEntrustQtyField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryAbleLockStock(DFITCSOPRspQryAbleLockStockField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYABLELOCKSTOCK;

	if (pData)
	{
		DFITCSOPRspQryAbleLockStockField *task_data = new DFITCSOPRspQryAbleLockStockField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryContactInfo(DFITCSOPRspQryContactField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYCONTACTINFO;

	if (pData)
	{
		DFITCSOPRspQryContactField *task_data = new DFITCSOPRspQryContactField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSOPExectueOrder(DFITCSOPRspExectueOrderField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPEXECTUEORDER;

	if (pData)
	{
		DFITCSOPRspExectueOrderField *task_data = new DFITCSOPRspExectueOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryExecAssiInfo(DFITCSOPRspQryExecAssiInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYEXECASSIINFO;

	if (pData)
	{
		DFITCSOPRspQryExecAssiInfoField *task_data = new DFITCSOPRspQryExecAssiInfoField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryTradeTime(DFITCSOPRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYTRADETIME;

	if (pData)
	{
		DFITCSOPRspQryTradeTimeField *task_data = new DFITCSOPRspQryTradeTimeField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryExchangeInfo(DFITCSOPRspQryExchangeInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYEXCHANGEINFO;

	if (pData)
	{
		DFITCSOPRspQryExchangeInfoField *task_data = new DFITCSOPRspQryExchangeInfoField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryCommission(DFITCSOPRspQryCommissionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYCOMMISSION;

	if (pData)
	{
		DFITCSOPRspQryCommissionField *task_data = new DFITCSOPRspQryCommissionField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryDeposit(DFITCSOPRspQryDepositField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYDEPOSIT;

	if (pData)
	{
		DFITCSOPRspQryDepositField *task_data = new DFITCSOPRspQryDepositField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspSOPQryContractObjectInfo(DFITCSOPRspQryContractObjectField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPSOPQRYCONTRACTOBJECTINFO;

	if (pData)
	{
		DFITCSOPRspQryContractObjectField *task_data = new DFITCSOPRspQryContractObjectField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnSOPEntrustOrderRtn(DFITCSOPEntrustOrderRtnField * pData)
{
	Task *task = new Task();
	task->task_name = ONSOPENTRUSTORDERRTN;

	if (pData)
	{
		DFITCSOPEntrustOrderRtnField *task_data = new DFITCSOPEntrustOrderRtnField();
		*task_data = *pData;
		task->task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnSOPTradeRtn(DFITCSOPTradeRtnField * pData)
{
	Task *task = new Task();
	task->task_name = ONSOPTRADERTN;

	if (pData)
	{
		DFITCSOPTradeRtnField *task_data = new DFITCSOPTradeRtnField();
		*task_data = *pData;
		task->task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnSOPWithdrawOrderRtn(DFITCSOPWithdrawOrderRtnField * pData)
{
	Task *task = new Task();
	task->task_name = ONSOPWITHDRAWORDERRTN;

	if (pData)
	{
		DFITCSOPWithdrawOrderRtnField *task_data = new DFITCSOPWithdrawOrderRtnField();
		*task_data = *pData;
		task->task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnRspFASLUserLogin(DFITCSECRspUserLoginField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLUSERLOGIN;

	if (pData)
	{
		DFITCSECRspUserLoginField *task_data = new DFITCSECRspUserLoginField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLUserLogout(DFITCSECRspUserLogoutField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLUSERLOGOUT;

	if (pData)
	{
		DFITCSECRspUserLogoutField *task_data = new DFITCSECRspUserLogoutField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryAbleFinInfo(DFITCFASLRspAbleFinInfoField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYABLEFININFO;

	if (pData)
	{
		DFITCFASLRspAbleFinInfoField *task_data = new DFITCFASLRspAbleFinInfoField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryAbleSloInfo(DFITCFASLRspAbleSloInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYABLESLOINFO;

	if (pData)
	{
		DFITCFASLRspAbleSloInfoField *task_data = new DFITCFASLRspAbleSloInfoField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLTransferCollateral(DFITCFASLRspTransferCollateralField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLTRANSFERCOLLATERAL;

	if (pData)
	{
		DFITCFASLRspTransferCollateralField *task_data = new DFITCFASLRspTransferCollateralField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLDirectRepayment(DFITCFASLRspDirectRepaymentField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLDIRECTREPAYMENT;

	if (pData)
	{
		DFITCFASLRspDirectRepaymentField *task_data = new DFITCFASLRspDirectRepaymentField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLRepayStockTransfer(DFITCFASLRspRepayStockTransferField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLREPAYSTOCKTRANSFER;

	if (pData)
	{
		DFITCFASLRspRepayStockTransferField *task_data = new DFITCFASLRspRepayStockTransferField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLEntrustCrdtOrder(DFITCFASLRspEntrustCrdtOrderField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLENTRUSTCRDTORDER;

	if (pData)
	{
		DFITCFASLRspEntrustCrdtOrderField *task_data = new DFITCFASLRspEntrustCrdtOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLEntrustOrder(DFITCFASLRspEntrustOrderField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLENTRUSTORDER;

	if (pData)
	{
		DFITCFASLRspEntrustOrderField *task_data = new DFITCFASLRspEntrustOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLCalcAbleEntrustCrdtQty(DFITCFASLRspCalcAbleEntrustCrdtQtyField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLCALCABLEENTRUSTCRDTQTY;

	if (pData)
	{
		DFITCFASLRspCalcAbleEntrustCrdtQtyField *task_data = new DFITCFASLRspCalcAbleEntrustCrdtQtyField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryCrdtFunds(DFITCFASLRspQryCrdtFundsField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYCRDTFUNDS;

	if (pData)
	{
		DFITCFASLRspQryCrdtFundsField *task_data = new DFITCFASLRspQryCrdtFundsField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryCrdtContract(DFITCFASLRspQryCrdtContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLat)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYCRDTCONTRACT;

	if (pData)
	{
		DFITCFASLRspQryCrdtContractField *task_data = new DFITCFASLRspQryCrdtContractField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLat;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryCrdtConChangeInfo(DFITCFASLRspQryCrdtConChangeInfoField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYCRDTCONCHANGEINFO;

	if (pData)
	{
		DFITCFASLRspQryCrdtConChangeInfoField *task_data = new DFITCFASLRspQryCrdtConChangeInfoField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLTransferFunds(DFITCStockRspTransferFundsField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLTRANSFERFUNDS;

	if (pData)
	{
		DFITCStockRspTransferFundsField *task_data = new DFITCStockRspTransferFundsField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryAccountInfo(DFITCStockRspQryAccountField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYACCOUNTINFO;

	if (pData)
	{
		DFITCStockRspQryAccountField *task_data = new DFITCStockRspQryAccountField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryCapitalAccountInfo(DFITCStockRspQryCapitalAccountField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYCAPITALACCOUNTINFO;

	if (pData)
	{
		DFITCStockRspQryCapitalAccountField *task_data = new DFITCStockRspQryCapitalAccountField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryShareholderInfo(DFITCStockRspQryShareholderField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYSHAREHOLDERINFO;

	if (pData)
	{
		DFITCStockRspQryShareholderField *task_data = new DFITCStockRspQryShareholderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryPosition(DFITCStockRspQryPositionField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYPOSITION;

	if (pData)
	{
		DFITCStockRspQryPositionField *task_data = new DFITCStockRspQryPositionField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryEntrustOrder(DFITCStockRspQryEntrustOrderField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYENTRUSTORDER;

	if (pData)
	{
		DFITCStockRspQryEntrustOrderField *task_data = new DFITCStockRspQryEntrustOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLQrySerialTrade(DFITCStockRspQrySerialTradeField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYSERIALTRADE;

	if (pData)
	{
		DFITCStockRspQrySerialTradeField *task_data = new DFITCStockRspQrySerialTradeField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryRealTimeTrade(DFITCStockRspQryRealTimeTradeField * pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYREALTIMETRADE;

	if (pData)
	{
		DFITCStockRspQryRealTimeTradeField *task_data = new DFITCStockRspQryRealTimeTradeField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryFreezeFundsDetail(DFITCStockRspQryFreezeFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYFREEZEFUNDSDETAIL;

	if (pData)
	{
		DFITCStockRspQryFreezeFundsDetailField *task_data = new DFITCStockRspQryFreezeFundsDetailField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryFreezeStockDetail(DFITCStockRspQryFreezeStockDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYFREEZESTOCKDETAIL;

	if (pData)
	{
		DFITCStockRspQryFreezeStockDetailField *task_data = new DFITCStockRspQryFreezeStockDetailField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryTransferFundsDetail(DFITCStockRspQryTransferFundsDetailField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYTRANSFERFUNDSDETAIL;

	if (pData)
	{
		DFITCStockRspQryTransferFundsDetailField *task_data = new DFITCStockRspQryTransferFundsDetailField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLWithdrawOrder(DFITCFASLRspWithdrawOrderField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLWITHDRAWORDER;

	if (pData)
	{
		DFITCFASLRspWithdrawOrderField *task_data = new DFITCFASLRspWithdrawOrderField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLQrySystemTime(DFITCFASLRspQryTradeTimeField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYSYSTEMTIME;

	if (pData)
	{
		DFITCFASLRspQryTradeTimeField *task_data = new DFITCFASLRspQryTradeTimeField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryTransferredContract(DFITCFASLRspQryTransferredContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYTRANSFERREDCONTRACT;

	if (pData)
	{
		DFITCFASLRspQryTransferredContractField *task_data = new DFITCFASLRspQryTransferredContractField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLDesirableFundsOut(DFITCFASLRspDesirableFundsOutField *pData, DFITCSECRspInfoField *pRspInfo)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLDESIRABLEFUNDSOUT;

	if (pData)
	{
		DFITCFASLRspDesirableFundsOutField *task_data = new DFITCFASLRspDesirableFundsOutField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryGuaranteedContract(DFITCFASLRspQryGuaranteedContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYGUARANTEEDCONTRACT;

	if (pData)
	{
		DFITCFASLRspQryGuaranteedContractField *task_data = new DFITCFASLRspQryGuaranteedContractField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnRspFASLQryUnderlyingContract(DFITCFASLRspQryUnderlyingContractField *pData, DFITCSECRspInfoField *pRspInfo, bool bIsLast)
{
	Task *task = new Task();
	task->task_name = ONRSPFASLQRYUNDERLYINGCONTRACT;

	if (pData)
	{
		DFITCFASLRspQryUnderlyingContractField *task_data = new DFITCFASLRspQryUnderlyingContractField();
		*task_data = *pData;
		task->task_data = task_data;
	}

	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task->task_error = task_error;
	}

	task->task_last = bIsLast;
	this->task_queue.push(task);
};

void TdApi::OnFASLEntrustOrderRtn(DFITCStockEntrustOrderRtnField *pData)
{
	Task *task = new Task();
	task->task_name = ONFASLENTRUSTORDERRTN;

	if (pData)
	{
		DFITCStockEntrustOrderRtnField *task_data = new DFITCStockEntrustOrderRtnField();
		*task_data = *pData;
		task->task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnFASLTradeRtn(DFITCStockTradeRtnField *pData)
{
	Task *task = new Task();
	task->task_name = ONFASLTRADERTN;

	if (pData)
	{
		DFITCStockTradeRtnField *task_data = new DFITCStockTradeRtnField();
		*task_data = *pData;
		task->task_data = task_data;
	}
	this->task_queue.push(task);
};

void TdApi::OnFASLWithdrawOrderRtn(DFITCStockWithdrawOrderRtnField *pData)
{
	Task *task = new Task();
	task->task_name = ONFASLWITHDRAWORDERRTN;

	if (pData)
	{
		DFITCStockWithdrawOrderRtnField *task_data = new DFITCStockWithdrawOrderRtnField();
		*task_data = *pData;
		task->task_data = task_data;
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
		Task *task = this->task_queue.wait_and_pop();

		switch (task->task_name)
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

		case ONRTNNOTICE:
		{
			this->processRtnNotice(task);
			break;
		}

		case ONRSPERROR:
		{
			this->processRspError(task);
			break;
		}

		case ONRSPSTOCKUSERLOGIN:
		{
			this->processRspStockUserLogin(task);
			break;
		}

		case ONRSPSTOCKUSERLOGOUT:
		{
			this->processRspStockUserLogout(task);
			break;
		}

		case ONRSPSTOCKUSERPASSWORDUPDATE:
		{
			this->processRspStockUserPasswordUpdate(task);
			break;
		}

		case ONRSPSTOCKENTRUSTORDER:
		{
			this->processRspStockEntrustOrder(task);
			break;
		}

		case ONRSPSTOCKWITHDRAWORDER:
		{
			this->processRspStockWithdrawOrder(task);
			break;
		}

		case ONRSPSTOCKQRYENTRUSTORDER:
		{
			this->processRspStockQryEntrustOrder(task);
			break;
		}

		case ONRSPSTOCKQRYREALTIMETRADE:
		{
			this->processRspStockQryRealTimeTrade(task);
			break;
		}

		case ONRSPSTOCKQRYSERIALTRADE:
		{
			this->processRspStockQrySerialTrade(task);
			break;
		}

		case ONRSPSTOCKQRYPOSITION:
		{
			this->processRspStockQryPosition(task);
			break;
		}

		case ONRSPSTOCKQRYCAPITALACCOUNTINFO:
		{
			this->processRspStockQryCapitalAccountInfo(task);
			break;
		}

		case ONRSPSTOCKQRYACCOUNTINFO:
		{
			this->processRspStockQryAccountInfo(task);
			break;
		}

		case ONRSPSTOCKQRYSHAREHOLDERINFO:
		{
			this->processRspStockQryShareholderInfo(task);
			break;
		}

		case ONRSPSTOCKTRANSFERFUNDS:
		{
			this->processRspStockTransferFunds(task);
			break;
		}

		case ONRSPSTOCKENTRUSTBATCHORDER:
		{
			this->processRspStockEntrustBatchOrder(task);
			break;
		}

		case ONRSPSTOCKWITHDRAWBATCHORDER:
		{
			this->processRspStockWithdrawBatchOrder(task);
			break;
		}

		case ONRSPSTOCKCALCABLEENTRUSTQTY:
		{
			this->processRspStockCalcAbleEntrustQty(task);
			break;
		}

		case ONRSPSTOCKCALCABLEPURCHASEETFQTY:
		{
			this->processRspStockCalcAblePurchaseETFQty(task);
			break;
		}

		case ONRSPSTOCKQRYFREEZEFUNDSDETAIL:
		{
			this->processRspStockQryFreezeFundsDetail(task);
			break;
		}

		case ONRSPSTOCKQRYFREEZESTOCKDETAIL:
		{
			this->processRspStockQryFreezeStockDetail(task);
			break;
		}

		case ONRSPSTOCKQRYTRANSFERSTOCKDETAIL:
		{
			this->processRspStockQryTransferStockDetail(task);
			break;
		}

		case ONRSPSTOCKQRYTRANSFERFUNDSDETAIL:
		{
			this->processRspStockQryTransferFundsDetail(task);
			break;
		}

		case ONRSPSTOCKQRYSTOCKINFO:
		{
			this->processRspStockQryStockInfo(task);
			break;
		}

		case ONRSPSTOCKQRYSTOCKSTATICINFO:
		{
			this->processRspStockQryStockStaticInfo(task);
			break;
		}

		case ONRSPSTOCKQRYTRADETIME:
		{
			this->processRspStockQryTradeTime(task);
			break;
		}

		case ONSTOCKENTRUSTORDERRTN:
		{
			this->processStockEntrustOrderRtn(task);
			break;
		}

		case ONSTOCKTRADERTN:
		{
			this->processStockTradeRtn(task);
			break;
		}

		case ONSTOCKWITHDRAWORDERRTN:
		{
			this->processStockWithdrawOrderRtn(task);
			break;
		}

		case ONRSPSOPUSERLOGIN:
		{
			this->processRspSOPUserLogin(task);
			break;
		}

		case ONRSPSOPUSERLOGOUT:
		{
			this->processRspSOPUserLogout(task);
			break;
		}

		case ONRSPSOPUSERPASSWORDUPDATE:
		{
			this->processRspSOPUserPasswordUpdate(task);
			break;
		}

		case ONRSPSOPENTRUSTORDER:
		{
			this->processRspSOPEntrustOrder(task);
			break;
		}

		case ONRSPSOPGROUPSPLIT:
		{
			this->processRspSOPGroupSplit(task);
			break;
		}

		case ONRSPSOPQRYGROUPPOSITION:
		{
			this->processRspSOPQryGroupPosition(task);
			break;
		}

		case ONRSPSOPLOCKOUNLOCKSTOCK:
		{
			this->processRspSOPLockOUnLockStock(task);
			break;
		}

		case ONRSPSOPWITHDRAWORDER:
		{
			this->processRspSOPWithdrawOrder(task);
			break;
		}

		case ONRSPSOPQRYENTRUSTORDER:
		{
			this->processRspSOPQryEntrustOrder(task);
			break;
		}

		case ONRSPSOPQRYSERIALTRADE:
		{
			this->processRspSOPQrySerialTrade(task);
			break;
		}

		case ONRSPSOPQRYPOSITION:
		{
			this->processRspSOPQryPosition(task);
			break;
		}

		case ONRSPSOPQRYCOLLATERALPOSITION:
		{
			this->processRspSOPQryCollateralPosition(task);
			break;
		}

		case ONRSPSOPQRYCAPITALACCOUNTINFO:
		{
			this->processRspSOPQryCapitalAccountInfo(task);
			break;
		}

		case ONRSPSOPQRYACCOUNTINFO:
		{
			this->processRspSOPQryAccountInfo(task);
			break;
		}

		case ONRSPSOPQRYSHAREHOLDERINFO:
		{
			this->processRspSOPQryShareholderInfo(task);
			break;
		}

		case ONRSPSOPCALCABLEENTRUSTQTY:
		{
			this->processRspSOPCalcAbleEntrustQty(task);
			break;
		}

		case ONRSPSOPQRYABLELOCKSTOCK:
		{
			this->processRspSOPQryAbleLockStock(task);
			break;
		}

		case ONRSPSOPQRYCONTACTINFO:
		{
			this->processRspSOPQryContactInfo(task);
			break;
		}

		case ONRSPSOPEXECTUEORDER:
		{
			this->processRspSOPExectueOrder(task);
			break;
		}

		case ONRSPSOPQRYEXECASSIINFO:
		{
			this->processRspSOPQryExecAssiInfo(task);
			break;
		}

		case ONRSPSOPQRYTRADETIME:
		{
			this->processRspSOPQryTradeTime(task);
			break;
		}

		case ONRSPSOPQRYEXCHANGEINFO:
		{
			this->processRspSOPQryExchangeInfo(task);
			break;
		}

		case ONRSPSOPQRYCOMMISSION:
		{
			this->processRspSOPQryCommission(task);
			break;
		}

		case ONRSPSOPQRYDEPOSIT:
		{
			this->processRspSOPQryDeposit(task);
			break;
		}

		case ONRSPSOPQRYCONTRACTOBJECTINFO:
		{
			this->processRspSOPQryContractObjectInfo(task);
			break;
		}

		case ONSOPENTRUSTORDERRTN:
		{
			this->processSOPEntrustOrderRtn(task);
			break;
		}

		case ONSOPTRADERTN:
		{
			this->processSOPTradeRtn(task);
			break;
		}

		case ONSOPWITHDRAWORDERRTN:
		{
			this->processSOPWithdrawOrderRtn(task);
			break;
		}

		case ONRSPFASLUSERLOGIN:
		{
			this->processRspFASLUserLogin(task);
			break;
		}

		case ONRSPFASLUSERLOGOUT:
		{
			this->processRspFASLUserLogout(task);
			break;
		}

		case ONRSPFASLQRYABLEFININFO:
		{
			this->processRspFASLQryAbleFinInfo(task);
			break;
		}

		case ONRSPFASLQRYABLESLOINFO:
		{
			this->processRspFASLQryAbleSloInfo(task);
			break;
		}

		case ONRSPFASLTRANSFERCOLLATERAL:
		{
			this->processRspFASLTransferCollateral(task);
			break;
		}

		case ONRSPFASLDIRECTREPAYMENT:
		{
			this->processRspFASLDirectRepayment(task);
			break;
		}

		case ONRSPFASLREPAYSTOCKTRANSFER:
		{
			this->processRspFASLRepayStockTransfer(task);
			break;
		}

		case ONRSPFASLENTRUSTCRDTORDER:
		{
			this->processRspFASLEntrustCrdtOrder(task);
			break;
		}

		case ONRSPFASLENTRUSTORDER:
		{
			this->processRspFASLEntrustOrder(task);
			break;
		}

		case ONRSPFASLCALCABLEENTRUSTCRDTQTY:
		{
			this->processRspFASLCalcAbleEntrustCrdtQty(task);
			break;
		}

		case ONRSPFASLQRYCRDTFUNDS:
		{
			this->processRspFASLQryCrdtFunds(task);
			break;
		}

		case ONRSPFASLQRYCRDTCONTRACT:
		{
			this->processRspFASLQryCrdtContract(task);
			break;
		}

		case ONRSPFASLQRYCRDTCONCHANGEINFO:
		{
			this->processRspFASLQryCrdtConChangeInfo(task);
			break;
		}

		case ONRSPFASLTRANSFERFUNDS:
		{
			this->processRspFASLTransferFunds(task);
			break;
		}

		case ONRSPFASLQRYACCOUNTINFO:
		{
			this->processRspFASLQryAccountInfo(task);
			break;
		}

		case ONRSPFASLQRYCAPITALACCOUNTINFO:
		{
			this->processRspFASLQryCapitalAccountInfo(task);
			break;
		}

		case ONRSPFASLQRYSHAREHOLDERINFO:
		{
			this->processRspFASLQryShareholderInfo(task);
			break;
		}

		case ONRSPFASLQRYPOSITION:
		{
			this->processRspFASLQryPosition(task);
			break;
		}

		case ONRSPFASLQRYENTRUSTORDER:
		{
			this->processRspFASLQryEntrustOrder(task);
			break;
		}

		case ONRSPFASLQRYSERIALTRADE:
		{
			this->processRspFASLQrySerialTrade(task);
			break;
		}

		case ONRSPFASLQRYREALTIMETRADE:
		{
			this->processRspFASLQryRealTimeTrade(task);
			break;
		}

		case ONRSPFASLQRYFREEZEFUNDSDETAIL:
		{
			this->processRspFASLQryFreezeFundsDetail(task);
			break;
		}

		case ONRSPFASLQRYFREEZESTOCKDETAIL:
		{
			this->processRspFASLQryFreezeStockDetail(task);
			break;
		}

		case ONRSPFASLQRYTRANSFERFUNDSDETAIL:
		{
			this->processRspFASLQryTransferFundsDetail(task);
			break;
		}

		case ONRSPFASLWITHDRAWORDER:
		{
			this->processRspFASLWithdrawOrder(task);
			break;
		}

		case ONRSPFASLQRYSYSTEMTIME:
		{
			this->processRspFASLQrySystemTime(task);
			break;
		}

		case ONRSPFASLQRYTRANSFERREDCONTRACT:
		{
			this->processRspFASLQryTransferredContract(task);
			break;
		}

		case ONRSPFASLDESIRABLEFUNDSOUT:
		{
			this->processRspFASLDesirableFundsOut(task);
			break;
		}

		case ONRSPFASLQRYGUARANTEEDCONTRACT:
		{
			this->processRspFASLQryGuaranteedContract(task);
			break;
		}

		case ONRSPFASLQRYUNDERLYINGCONTRACT:
		{
			this->processRspFASLQryUnderlyingContract(task);
			break;
		}

		case ONFASLENTRUSTORDERRTN:
		{
			this->processFASLEntrustOrderRtn(task);
			break;
		}

		case ONFASLTRADERTN:
		{
			this->processFASLTradeRtn(task);
			break;
		}

		case ONFASLWITHDRAWORDERRTN:
		{
			this->processFASLWithdrawOrderRtn(task);
			break;
		}

		};
	}
};

void TdApi::processFrontConnected(Task *task)
{
	PyLock lock;
	this->onFrontConnected();
	delete task;
};

void TdApi::processFrontDisconnected(Task *task)
{
	PyLock lock;
	this->onFrontDisconnected(task->task_id);
	delete task;
};

void TdApi::processRtnNotice(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspNoticeField *task_data = (DFITCSECRspNoticeField*)task->task_data;
		data["noticeMsg"] = task_data->noticeMsg;
		delete task->task_data;
	}

	this->onRtnNotice(data);
	delete task;
};

void TdApi::processRspError(Task *task)
{
	PyLock lock;
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspError(error);
	delete task;
};

void TdApi::processRspStockUserLogin(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = task_data->loginTime;
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockUserLogin(data, error);
	delete task;
};

void TdApi::processRspStockUserLogout(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockUserLogout(data, error);
	delete task;
};

void TdApi::processRspStockUserPasswordUpdate(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspPasswordUpdateField *task_data = (DFITCSECRspPasswordUpdateField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["passwordType"] = task_data->passwordType;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockUserPasswordUpdate(data, error);
	delete task;
};

void TdApi::processRspStockEntrustOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspEntrustOrderField *task_data = (DFITCStockRspEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["entrustMsg"] = task_data->entrustMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockEntrustOrder(data, error);
	delete task;
};

void TdApi::processRspStockWithdrawOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspWithdrawOrderField *task_data = (DFITCSECRspWithdrawOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustTime"] = task_data->entrustTime;
		data["cancelMsg"] = task_data->cancelMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockWithdrawOrder(data, error);
	delete task;
};

void TdApi::processRspStockQryEntrustOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryEntrustOrderField *task_data = (DFITCStockRspQryEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["offerShareholderID"] = task_data->offerShareholderID;
		data["currency"] = task_data->currency;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeTime"] = task_data->tradeTime;
		data["tradeQty"] = task_data->tradeQty;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["clearFunds"] = task_data->clearFunds;
		data["entrustType"] = task_data->entrustType;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustPrice"] = task_data->entrustPrice;
		data["entrustDirection"] = task_data->entrustDirection;
		data["entrustQty"] = task_data->entrustQty;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["entrustTime"] = task_data->entrustTime;
		data["declareTime"] = task_data->declareTime;
		data["declareResult"] = task_data->declareResult;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["freezeFunds"] = task_data->freezeFunds;
		data["accountID"] = task_data->accountID;
		data["noteMsg"] = task_data->noteMsg;
		data["withdrawQty"] = task_data->withdrawQty;
		data["declareOrderID"] = task_data->declareOrderID;
		data["orderType"] = task_data->orderType;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["freezeFundsSerialID"] = task_data->freezeFundsSerialID;
		data["freezeStockSerialID"] = task_data->freezeStockSerialID;
		data["declareDate"] = task_data->declareDate;
		data["declareSerialID"] = task_data->declareSerialID;
		data["entrustDate"] = task_data->entrustDate;
		data["incQryIndex"] = task_data->incQryIndex;
		data["ipAddr"] = task_data->ipAddr;
		data["macAddr"] = task_data->macAddr;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryEntrustOrder(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryRealTimeTrade(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryRealTimeTradeField *task_data = (DFITCStockRspQryRealTimeTradeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["declareOrderID"] = task_data->declareOrderID;
		data["exchangeID"] = task_data->exchangeID;
		data["shareholderID"] = task_data->shareholderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["entrustQty"] = task_data->entrustQty;
		data["entrustPrice"] = task_data->entrustPrice;
		data["withdrawQty"] = task_data->withdrawQty;
		data["tradeQty"] = task_data->tradeQty;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeTime"] = task_data->tradeTime;
		data["currency"] = task_data->currency;
		data["clearFunds"] = task_data->clearFunds;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["orderType"] = task_data->orderType;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryRealTimeTrade(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQrySerialTrade(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQrySerialTradeField *task_data = (DFITCStockRspQrySerialTradeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["tradeID"] = task_data->tradeID;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeQty"] = task_data->tradeQty;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["clearFunds"] = task_data->clearFunds;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["commission"] = task_data->commission;
		data["rtnSerialID"] = task_data->rtnSerialID;
		data["interestQuote"] = task_data->interestQuote;
		data["declareOrderID"] = task_data->declareOrderID;
		data["incQryIndex"] = task_data->incQryIndex;
		data["interest"] = task_data->interest;
		data["tradeTime"] = task_data->tradeTime;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQrySerialTrade(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryPositionField *task_data = (DFITCStockRspQryPositionField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["sellTurnover"] = task_data->sellTurnover;
		data["sellTradeQty"] = task_data->sellTradeQty;
		data["sellEntrustQty"] = task_data->sellEntrustQty;
		data["buyTurnover"] = task_data->buyTurnover;
		data["buyTradeQty"] = task_data->buyTradeQty;
		data["buyEntrustQty"] = task_data->buyEntrustQty;
		data["nonCirculateQty"] = task_data->nonCirculateQty;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["openDate"] = task_data->openDate;
		data["ableSellQty"] = task_data->ableSellQty;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["securityQty"] = task_data->securityQty;
		data["position"] = task_data->position;
		data["unSettleQty"] = task_data->unSettleQty;
		data["changeDate"] = task_data->changeDate;
		data["ablePurchaseQty"] = task_data->ablePurchaseQty;
		data["ableRedemptionQty"] = task_data->ableRedemptionQty;
		data["freezeQty"] = task_data->freezeQty;
		data["offsetSQty"] = task_data->offsetSQty;
		data["offsetBQty"] = task_data->offsetBQty;
		data["purchaseTradeQty"] = task_data->purchaseTradeQty;
		data["redemptionTradeQty"] = task_data->redemptionTradeQty;
		data["tradeUnit"] = task_data->tradeUnit;
		data["totalSellQty"] = task_data->totalSellQty;
		data["totalBuyQty"] = task_data->totalBuyQty;
		data["rationedSharesQty"] = task_data->rationedSharesQty;
		data["purchaseQty"] = task_data->purchaseQty;
		data["dilutedFloatProfitLoss"] = task_data->dilutedFloatProfitLoss;
		data["dilutedBreakevenPrice"] = task_data->dilutedBreakevenPrice;
		data["dilutedCost"] = task_data->dilutedCost;
		data["avgPositionPrice"] = task_data->avgPositionPrice;
		data["floatProfitLoss"] = task_data->floatProfitLoss;
		data["dividend"] = task_data->dividend;
		data["totalFloatProfitLoss"] = task_data->totalFloatProfitLoss;
		data["sellAmount"] = task_data->sellAmount;
		data["buyAmount"] = task_data->buyAmount;
		data["buyAvgPrice"] = task_data->buyAvgPrice;
		data["rationedSharesAmount"] = task_data->rationedSharesAmount;
		data["latestMarket"] = task_data->latestMarket;
		data["breakevenPrice"] = task_data->breakevenPrice;
		data["latestPrice"] = task_data->latestPrice;
		data["nonCirculateMarket"] = task_data->nonCirculateMarket;
		data["interestQuote"] = task_data->interestQuote;
		data["preClosePrice"] = task_data->preClosePrice;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryPosition(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryCapitalAccountInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryCapitalAccountField *task_data = (DFITCStockRspQryCapitalAccountField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["currency"] = task_data->currency;
		data["availableFunds"] = task_data->availableFunds;
		data["t2AvailableFunds"] = task_data->t2AvailableFunds;
		data["anticipatedInterest"] = task_data->anticipatedInterest;
		data["accountBalance"] = task_data->accountBalance;
		data["accountStatus"] = task_data->accountStatus;
		data["accountID"] = task_data->accountID;
		data["freezeFunds"] = task_data->freezeFunds;
		data["t2FreezeFunds"] = task_data->t2FreezeFunds;
		data["branchID"] = task_data->branchID;
		data["totalFunds"] = task_data->totalFunds;
		data["totalMarket"] = task_data->totalMarket;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryCapitalAccountInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryAccountInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryAccountField *task_data = (DFITCStockRspQryAccountField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["tel"] = task_data->tel;
		data["accountID"] = task_data->accountID;
		data["accountName"] = task_data->accountName;
		data["accountIdentityID"] = task_data->accountIdentityID;
		data["accountIdentityType"] = task_data->accountIdentityType;
		data["branchID"] = task_data->branchID;
		data["branchType"] = task_data->branchType;
		data["mobile"] = task_data->mobile;
		data["entrustType"] = task_data->entrustType;
		data["accountStatus"] = task_data->accountStatus;
		data["pwdSynFlag"] = task_data->pwdSynFlag;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryAccountInfo(data, error);
	delete task;
};

void TdApi::processRspStockQryShareholderInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryShareholderField *task_data = (DFITCStockRspQryShareholderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["account"] = task_data->account;
		data["shareholderID"] = task_data->shareholderID;
		data["shareholderSpecProp"] = task_data->shareholderSpecProp;
		data["tradePermissions"] = task_data->tradePermissions;
		data["exchangeID"] = task_data->exchangeID;
		data["shareholderStatus"] = task_data->shareholderStatus;
		data["mainAccountFlag"] = task_data->mainAccountFlag;
		data["shareholderCtlProp"] = task_data->shareholderCtlProp;
		data["branchID"] = task_data->branchID;
		data["shareholderType"] = task_data->shareholderType;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryShareholderInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockTransferFunds(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspTransferFundsField *task_data = (DFITCStockRspTransferFundsField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["serialID"] = task_data->serialID;
		data["accountBanlance"] = task_data->accountBanlance;
		data["availableFunds"] = task_data->availableFunds;
		data["t2AvailableFunds"] = task_data->t2AvailableFunds;
		data["fundsTransFlag"] = task_data->fundsTransFlag;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockTransferFunds(data, error);
	delete task;
};

void TdApi::processRspStockEntrustBatchOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspEntrustBatchOrderField *task_data = (DFITCStockRspEntrustBatchOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["orderRangeID"] = task_data->orderRangeID;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["sucEntrustCount"] = task_data->sucEntrustCount;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockEntrustBatchOrder(data, error);
	delete task;
};

void TdApi::processRspStockWithdrawBatchOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspWithdrawBatchOrderField *task_data = (DFITCStockRspWithdrawBatchOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockWithdrawBatchOrder(data, error);
	delete task;
};

void TdApi::processRspStockCalcAbleEntrustQty(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspCalcAbleEntrustQtyField *task_data = (DFITCStockRspCalcAbleEntrustQtyField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["ableEntrustQty"] = task_data->ableEntrustQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockCalcAbleEntrustQty(data, error);
	delete task;
};

void TdApi::processRspStockCalcAblePurchaseETFQty(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspCalcAblePurchaseETFQtyField *task_data = (DFITCStockRspCalcAblePurchaseETFQtyField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["ablePurchaseETFQty"] = task_data->ablePurchaseETFQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockCalcAblePurchaseETFQty(data, error);
	delete task;
};

void TdApi::processRspStockQryFreezeFundsDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryFreezeFundsDetailField *task_data = (DFITCStockRspQryFreezeFundsDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["fundsFreezeType"] = task_data->fundsFreezeType;
		data["accountName"] = task_data->accountName;
		data["summaryMsg"] = task_data->summaryMsg;
		data["serialID"] = task_data->serialID;
		data["operatorFunds"] = task_data->operatorFunds;
		data["operatorTime"] = task_data->operatorTime;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryFreezeFundsDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryFreezeStockDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryFreezeStockDetailField *task_data = (DFITCStockRspQryFreezeStockDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["stockFreezeType"] = task_data->stockFreezeType;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["accountName"] = task_data->accountName;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["summaryMsg"] = task_data->summaryMsg;
		data["serialID"] = task_data->serialID;
		data["operatorTime"] = task_data->operatorTime;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		data["operatorQty"] = task_data->operatorQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryFreezeStockDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryTransferStockDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryTransferStockDetailField *task_data = (DFITCStockRspQryTransferStockDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["accountName"] = task_data->accountName;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		data["exchangeID"] = task_data->exchangeID;
		data["stockFreezeType"] = task_data->stockFreezeType;
		data["securityID"] = task_data->securityID;
		data["serialID"] = task_data->serialID;
		data["shareholderID"] = task_data->shareholderID;
		data["summaryMsg"] = task_data->summaryMsg;
		data["operatorTime"] = task_data->operatorTime;
		data["operatorQty"] = task_data->operatorQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryTransferStockDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryTransferFundsDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryTransferFundsDetailField *task_data = (DFITCStockRspQryTransferFundsDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["fundsFreezeType"] = task_data->fundsFreezeType;
		data["accountName"] = task_data->accountName;
		data["summaryMsg"] = task_data->summaryMsg;
		data["serialID"] = task_data->serialID;
		data["operatorFunds"] = task_data->operatorFunds;
		data["operatorTime"] = task_data->operatorTime;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryTransferFundsDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryStockInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryStockField *task_data = (DFITCStockRspQryStockField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["stopFlag"] = task_data->stopFlag;
		data["latestPrice"] = task_data->latestPrice;
		data["preClosePrice"] = task_data->preClosePrice;
		data["openPrice"] = task_data->openPrice;
		data["tradeQty"] = task_data->tradeQty;
		data["turnover"] = task_data->turnover;
		data["priceHigher"] = task_data->priceHigher;
		data["priceLower"] = task_data->priceLower;
		data["bidPrice1"] = task_data->bidPrice1;
		data["bidQty1"] = task_data->bidQty1;
		data["askPrice1"] = task_data->askPrice1;
		data["askQty1"] = task_data->askQty1;
		data["bidPrice2"] = task_data->bidPrice2;
		data["bidQty2"] = task_data->bidQty2;
		data["askPrice2"] = task_data->askPrice2;
		data["askQty2"] = task_data->askQty2;
		data["bidPrice3"] = task_data->bidPrice3;
		data["bidQty3"] = task_data->bidQty3;
		data["askPrice3"] = task_data->askPrice3;
		data["askQty3"] = task_data->askQty3;
		data["bidPrice4"] = task_data->bidPrice4;
		data["bidQty4"] = task_data->bidQty4;
		data["askPrice4"] = task_data->askPrice4;
		data["askQty4"] = task_data->askQty4;
		data["bidPrice5"] = task_data->bidPrice5;
		data["bidQty5"] = task_data->bidQty5;
		data["askPrice5"] = task_data->askPrice5;
		data["askQty5"] = task_data->askQty5;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["interestQuote"] = task_data->interestQuote;
		data["securityFaceValue"] = task_data->securityFaceValue;
		data["bidTradeFlag"] = task_data->bidTradeFlag;
		data["tradeUnit"] = task_data->tradeUnit;
		data["businessLimit"] = task_data->businessLimit;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["upperLimitPrice"] = task_data->upperLimitPrice;
		data["lowerLimitPrice"] = task_data->lowerLimitPrice;
		data["currency"] = task_data->currency;
		data["orderLimits"] = task_data->orderLimits;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryStockInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryStockStaticInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryStockStaticField *task_data = (DFITCStockRspQryStockStaticField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["stopFlag"] = task_data->stopFlag;
		data["preClosePrice"] = task_data->preClosePrice;
		data["openPrice"] = task_data->openPrice;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["interestQuote"] = task_data->interestQuote;
		data["securityFaceValue"] = task_data->securityFaceValue;
		data["bidTradeFlag"] = task_data->bidTradeFlag;
		data["tradeUnit"] = task_data->tradeUnit;
		data["businessLimit"] = task_data->businessLimit;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["upperLimitPrice"] = task_data->upperLimitPrice;
		data["lowerLimitPrice"] = task_data->lowerLimitPrice;
		data["currency"] = task_data->currency;
		data["orderLimits"] = task_data->orderLimits;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryStockStaticInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspStockQryTradeTime(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryTradeTimeField *task_data = (DFITCStockRspQryTradeTimeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sysTradingDay"] = task_data->sysTradingDay;
		data["sysTime"] = task_data->sysTime;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockQryTradeTime(data, error);
	delete task;
};

void TdApi::processStockEntrustOrderRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockEntrustOrderRtnField *task_data = (DFITCStockEntrustOrderRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["withdrawQty"] = task_data->withdrawQty;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["freezeFunds"] = task_data->freezeFunds;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		data["entrustQty"] = task_data->entrustQty;
		data["orderConfirmFlag"] = task_data->orderConfirmFlag;
		data["entrustTime"] = task_data->entrustTime;
		data["entrustPrice"] = task_data->entrustPrice;
		data["orderType"] = task_data->orderType;
		delete task->task_data;
	}

	this->onStockEntrustOrderRtn(data);
	delete task;
};

void TdApi::processStockTradeRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockTradeRtnField *task_data = (DFITCStockTradeRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["tradeID"] = task_data->tradeID;
		data["tradeTime"] = task_data->tradeTime;
		data["withdrawQty"] = task_data->withdrawQty;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["clearFunds"] = task_data->clearFunds;
		data["totalTradeQty"] = task_data->totalTradeQty;
		data["totalTurnover"] = task_data->totalTurnover;
		data["tradeQty"] = task_data->tradeQty;
		data["tradePrice"] = task_data->tradePrice;
		data["turnover"] = task_data->turnover;
		data["entrustQty"] = task_data->entrustQty;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		delete task->task_data;
	}

	this->onStockTradeRtn(data);
	delete task;
};

void TdApi::processStockWithdrawOrderRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockWithdrawOrderRtnField *task_data = (DFITCStockWithdrawOrderRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["withdrawQty"] = task_data->withdrawQty;
		data["tradeQty"] = task_data->tradeQty;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["freezeFunds"] = task_data->freezeFunds;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["entrustQty"] = task_data->entrustQty;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		delete task->task_data;
	}

	this->onStockWithdrawOrderRtn(data);
	delete task;
};

void TdApi::processRspSOPUserLogin(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = task_data->loginTime;
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPUserLogin(data, error);
	delete task;
};

void TdApi::processRspSOPUserLogout(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPUserLogout(data, error);
	delete task;
};

void TdApi::processRspSOPUserPasswordUpdate(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspPasswordUpdateField *task_data = (DFITCSECRspPasswordUpdateField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["passwordType"] = task_data->passwordType;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPUserPasswordUpdate(data, error);
	delete task;
};

void TdApi::processRspSOPEntrustOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspEntrustOrderField *task_data = (DFITCSOPRspEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustTime"] = task_data->entrustTime;
		data["freezeFunds"] = task_data->freezeFunds;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPEntrustOrder(data, error);
	delete task;
};

void TdApi::processRspSOPGroupSplit(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspEntrustOrderField *task_data = (DFITCSOPRspEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustTime"] = task_data->entrustTime;
		data["freezeFunds"] = task_data->freezeFunds;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPGroupSplit(data, error);
	delete task;
};

void TdApi::processRspSOPQryGroupPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryGroupPositionField *task_data = (DFITCSOPRspQryGroupPositionField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["shareholderID"] = task_data->shareholderID;
		data["subAccountID"] = task_data->subAccountID;
		data["currency"] = task_data->currency;
		data["capitalID"] = task_data->capitalID;
		data["groupType"] = task_data->groupType;
		data["groupCode"] = task_data->groupCode;
		data["groupQty"] = task_data->groupQty;
		data["enableSplitQty"] = task_data->enableSplitQty;
		data["splitEntrustQty"] = task_data->splitEntrustQty;
		data["splitTradeQty"] = task_data->splitTradeQty;
		data["groupDeposit"] = task_data->groupDeposit;
		data["securityOptionID1"] = task_data->securityOptionID1;
		data["securityOptionID2"] = task_data->securityOptionID2;
		data["securityOptionID3"] = task_data->securityOptionID3;
		data["securityOptionID4"] = task_data->securityOptionID4;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryGroupPosition(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPLockOUnLockStock(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspLockOUnLockStockField *task_data = (DFITCSOPRspLockOUnLockStockField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustTime"] = task_data->entrustTime;
		data["freezeFunds"] = task_data->freezeFunds;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPLockOUnLockStock(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPWithdrawOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspWithdrawOrderField *task_data = (DFITCSECRspWithdrawOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustTime"] = task_data->entrustTime;
		data["cancelMsg"] = task_data->cancelMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPWithdrawOrder(data, error);
	delete task;
};

void TdApi::processRspSOPQryEntrustOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryEntrustOrderField *task_data = (DFITCSOPRspQryEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["withdrawOrderID"] = task_data->withdrawOrderID;
		data["declareOrderID"] = task_data->declareOrderID;
		data["exchangeID"] = task_data->exchangeID;
		data["shareholderID"] = task_data->shareholderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["securityOptionID"] = task_data->securityOptionID;
		data["optType"] = task_data->optType;
		data["openCloseFlag"] = task_data->openCloseFlag;
		data["coveredFlag"] = task_data->coveredFlag;
		data["entrustQty"] = task_data->entrustQty;
		data["entrustPrice"] = task_data->entrustPrice;
		data["entrustDate"] = task_data->entrustDate;
		data["entrustTime"] = task_data->entrustTime;
		data["offerShareholderID"] = task_data->offerShareholderID;
		data["declareDate"] = task_data->declareDate;
		data["declareTime"] = task_data->declareTime;
		data["declareSerialID"] = task_data->declareSerialID;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		data["withdrawQty"] = task_data->withdrawQty;
		data["tradeQty"] = task_data->tradeQty;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["currency"] = task_data->currency;
		data["freezeFunds"] = task_data->freezeFunds;
		data["clearFunds"] = task_data->clearFunds;
		data["entrustType"] = task_data->entrustType;
		data["macAddr"] = task_data->macAddr;
		data["ipAddr"] = task_data->ipAddr;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["orderType"] = task_data->orderType;
		data["incQryIndex"] = task_data->incQryIndex;
		data["capitalID"] = task_data->capitalID;
		data["orderExpiryDate"] = task_data->orderExpiryDate;
		data["devID"] = task_data->devID;
		data["devDecInfo"] = task_data->devDecInfo;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryEntrustOrder(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQrySerialTrade(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQrySerialTradeField *task_data = (DFITCSOPRspQrySerialTradeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["rtnSerialID"] = task_data->rtnSerialID;
		data["securityID"] = task_data->securityID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["declareOrderID"] = task_data->declareOrderID;
		data["currency"] = task_data->currency;
		data["tradeID"] = task_data->tradeID;
		data["tradeTime"] = task_data->tradeTime;
		data["tradeQty"] = task_data->tradeQty;
		data["openCloseFlag"] = task_data->openCloseFlag;
		data["coveredFlag"] = task_data->coveredFlag;
		data["spdOrderID"] = task_data->spdOrderID;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["clearFunds"] = task_data->clearFunds;
		data["rotationTime"] = task_data->rotationTime;
		data["incQryIndex"] = task_data->incQryIndex;
		data["shareholderID"] = task_data->shareholderID;
		data["capitalID"] = task_data->capitalID;
		data["devID"] = task_data->devID;
		data["devDecInfo"] = task_data->devDecInfo;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQrySerialTrade(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryPositionField *task_data = (DFITCSOPRspQryPositionField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["subAccountID"] = task_data->subAccountID;
		data["securityOptionID"] = task_data->securityOptionID;
		data["contractID"] = task_data->contractID;
		data["contractName"] = task_data->contractName;
		data["entrustDirection"] = task_data->entrustDirection;
		data["coveredFlag"] = task_data->coveredFlag;
		data["executeDate"] = task_data->executeDate;
		data["totalQty"] = task_data->totalQty;
		data["availableQty"] = task_data->availableQty;
		data["latestPrice"] = task_data->latestPrice;
		data["optionMarket"] = task_data->optionMarket;
		data["freezeQty"] = task_data->freezeQty;
		data["executeQty"] = task_data->executeQty;
		data["openEntrustQty"] = task_data->openEntrustQty;
		data["openTradeQty"] = task_data->openTradeQty;
		data["prePosition"] = task_data->prePosition;
		data["closeEntrustQty"] = task_data->closeEntrustQty;
		data["closeTradeQty"] = task_data->closeTradeQty;
		data["deposit"] = task_data->deposit;
		data["openDeposit"] = task_data->openDeposit;
		data["closeDeposit"] = task_data->closeDeposit;
		data["exchangeDeposit"] = task_data->exchangeDeposit;
		data["exchangeOpenDeposit"] = task_data->exchangeOpenDeposit;
		data["exchangeCloseDeposit"] = task_data->exchangeCloseDeposit;
		data["openAvgPrice"] = task_data->openAvgPrice;
		data["optType"] = task_data->optType;
		data["contractObjectType"] = task_data->contractObjectType;
		data["contractUnit"] = task_data->contractUnit;
		data["currency"] = task_data->currency;
		data["totalTradeCost"] = task_data->totalTradeCost;
		data["tradeCost"] = task_data->tradeCost;
		data["realizeProfitLoss"] = task_data->realizeProfitLoss;
		data["profitLoss"] = task_data->profitLoss;
		data["adjustRemind"] = task_data->adjustRemind;
		data["expireRemind"] = task_data->expireRemind;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryPosition(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryCollateralPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryCollateralPositionField *task_data = (DFITCSOPRspQryCollateralPositionField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["exchangeID"] = task_data->exchangeID;
		data["accountID"] = task_data->accountID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["availableQty"] = task_data->availableQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryCollateralPosition(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryCapitalAccountInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryCapitalAccountField *task_data = (DFITCSOPRspQryCapitalAccountField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["branchID"] = task_data->branchID;
		data["currency"] = task_data->currency;
		data["accountBanlance"] = task_data->accountBanlance;
		data["availableFunds"] = task_data->availableFunds;
		data["freezeFunds"] = task_data->freezeFunds;
		data["anticipatedInterest"] = task_data->anticipatedInterest;
		data["usedDeposit"] = task_data->usedDeposit;
		data["accountStatus"] = task_data->accountStatus;
		data["totalFunds"] = task_data->totalFunds;
		data["totalMarket"] = task_data->totalMarket;
		data["cashAssets"] = task_data->cashAssets;
		data["execGuaranteeRatio"] = task_data->execGuaranteeRatio;
		data["buyLimits"] = task_data->buyLimits;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryCapitalAccountInfo(data, error);
	delete task;
};

void TdApi::processRspSOPQryAccountInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryAccountField *task_data = (DFITCSOPRspQryAccountField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["accountName"] = task_data->accountName;
		data["accountFullName"] = task_data->accountFullName;
		data["branchID"] = task_data->branchID;
		data["identityType"] = task_data->identityType;
		data["accountIdentityID"] = task_data->accountIdentityID;
		data["tel"] = task_data->tel;
		data["mobile"] = task_data->mobile;
		data["accountType"] = task_data->accountType;
		data["accountProp"] = task_data->accountProp;
		data["tradePermissions"] = task_data->tradePermissions;
		data["entrustType"] = task_data->entrustType;
		data["accountStatus"] = task_data->accountStatus;
		data["pwdSynFlag"] = task_data->pwdSynFlag;
		data["accountNodeID"] = task_data->accountNodeID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryAccountInfo(data, error);
	delete task;
};

void TdApi::processRspSOPQryShareholderInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryShareholderField *task_data = (DFITCSOPRspQryShareholderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["branchID"] = task_data->branchID;
		data["currency"] = task_data->currency;
		data["shareholderID"] = task_data->shareholderID;
		data["tradePermissions"] = task_data->tradePermissions;
		data["shareholderSpecProp"] = task_data->shareholderSpecProp;
		data["shareholderCtlProp"] = task_data->shareholderCtlProp;
		data["shareholderStatus"] = task_data->shareholderStatus;
		data["mainAccountFlag"] = task_data->mainAccountFlag;
		data["exchangeID"] = task_data->exchangeID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryShareholderInfo(data, error);
	delete task;
};

void TdApi::processRspSOPCalcAbleEntrustQty(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspCalcAbleEntrustQtyField *task_data = (DFITCSOPRspCalcAbleEntrustQtyField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityOptionID"] = task_data->securityOptionID;
		data["entrustQty"] = task_data->entrustQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPCalcAbleEntrustQty(data, error);
	delete task;
};

void TdApi::processRspSOPQryAbleLockStock(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryAbleLockStockField *task_data = (DFITCSOPRspQryAbleLockStockField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["securityQty"] = task_data->securityQty;
		data["position"] = task_data->position;
		data["avgPositionPrice"] = task_data->avgPositionPrice;
		data["dilutedCost"] = task_data->dilutedCost;
		data["breakevenPrice"] = task_data->breakevenPrice;
		data["dilutedBreakevenPrice"] = task_data->dilutedBreakevenPrice;
		data["ableSellQty"] = task_data->ableSellQty;
		data["latestMarket"] = task_data->latestMarket;
		data["latestPrice"] = task_data->latestPrice;
		data["floatProfitLoss"] = task_data->floatProfitLoss;
		data["dilutedFloatProfitLoss"] = task_data->dilutedFloatProfitLoss;
		data["tradeUnit"] = task_data->tradeUnit;
		data["openBuyQty"] = task_data->openBuyQty;
		data["openSellQty"] = task_data->openSellQty;
		data["buyUnSettleQty"] = task_data->buyUnSettleQty;
		data["sellUnSettleQty"] = task_data->sellUnSettleQty;
		data["openEntrustSellQty"] = task_data->openEntrustSellQty;
		data["ableLockQty"] = task_data->ableLockQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryAbleLockStock(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryContactInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryContactField *task_data = (DFITCSOPRspQryContactField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityOptionID"] = task_data->securityOptionID;
		data["contractID"] = task_data->contractID;
		data["contractName"] = task_data->contractName;
		data["securityID"] = task_data->securityID;
		data["contractObjectType"] = task_data->contractObjectType;
		data["execType"] = task_data->execType;
		data["deliType"] = task_data->deliType;
		data["optType"] = task_data->optType;
		data["contactUnit"] = task_data->contactUnit;
		data["latestPrice"] = task_data->latestPrice;
		data["beginTradingDay"] = task_data->beginTradingDay;
		data["endTradingDay"] = task_data->endTradingDay;
		data["execDate"] = task_data->execDate;
		data["endDate"] = task_data->endDate;
		data["positionUpLimit"] = task_data->positionUpLimit;
		data["priceUpLimit"] = task_data->priceUpLimit;
		data["priceDownLimit"] = task_data->priceDownLimit;
		data["priceHigher"] = task_data->priceHigher;
		data["priceLower"] = task_data->priceLower;
		data["entrustUpLimit"] = task_data->entrustUpLimit;
		data["entrustDownLimit"] = task_data->entrustDownLimit;
		data["entrustUpLimitMarketPri"] = task_data->entrustUpLimitMarketPri;
		data["entrustDownLimitMarketPri"] = task_data->entrustDownLimitMarketPri;
		data["openLimit"] = task_data->openLimit;
		data["stockTradeFlag"] = task_data->stockTradeFlag;
		data["depositUnit"] = task_data->depositUnit;
		data["depositRatioC"] = task_data->depositRatioC;
		data["depositRatioE"] = task_data->depositRatioE;
		data["preClosePrice"] = task_data->preClosePrice;
		data["closePrice"] = task_data->closePrice;
		data["preSettlePrice"] = task_data->preSettlePrice;
		data["openPrice"] = task_data->openPrice;
		data["tradeQty"] = task_data->tradeQty;
		data["turnover"] = task_data->turnover;
		data["settlePrice"] = task_data->settlePrice;
		data["endCashSettlePrice"] = task_data->endCashSettlePrice;
		data["handQty"] = task_data->handQty;
		data["unClosePositionQty"] = task_data->unClosePositionQty;
		data["approachExpireFlag"] = task_data->approachExpireFlag;
		data["tempAdjustFlag"] = task_data->tempAdjustFlag;
		data["stockListFlag"] = task_data->stockListFlag;
		data["execPrice"] = task_data->execPrice;
		data["bidPrice1"] = task_data->bidPrice1;
		data["bidQty1"] = task_data->bidQty1;
		data["bidPrice2"] = task_data->bidPrice2;
		data["bidQty2"] = task_data->bidQty2;
		data["bidPrice3"] = task_data->bidPrice3;
		data["bidQty3"] = task_data->bidQty3;
		data["bidPrice4"] = task_data->bidPrice4;
		data["bidQty4"] = task_data->bidQty4;
		data["bidPrice5"] = task_data->bidPrice5;
		data["bidQty5"] = task_data->bidQty5;
		data["askPrice1"] = task_data->askPrice1;
		data["askQty1"] = task_data->askQty1;
		data["askPrice2"] = task_data->askPrice2;
		data["askQty2"] = task_data->askQty2;
		data["askPrice3"] = task_data->askPrice3;
		data["askQty3"] = task_data->askQty3;
		data["askPrice4"] = task_data->askPrice4;
		data["askQty4"] = task_data->askQty4;
		data["askPrice5"] = task_data->askPrice5;
		data["askQty5"] = task_data->askQty5;
		data["optionIndex"] = task_data->optionIndex;
		data["miniPriceChange"] = task_data->miniPriceChange;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryContactInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPExectueOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspExectueOrderField *task_data = (DFITCSOPRspExectueOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustTime"] = task_data->entrustTime;
		data["freezeFunds"] = task_data->freezeFunds;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPExectueOrder(data, error);
	delete task;
};

void TdApi::processRspSOPQryExecAssiInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryExecAssiInfoField *task_data = (DFITCSOPRspQryExecAssiInfoField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["tradeDate"] = task_data->tradeDate;
		data["branchID"] = task_data->branchID;
		data["shareholderID"] = task_data->shareholderID;
		data["subAccountID"] = task_data->subAccountID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["optType"] = task_data->optType;
		data["contractObjectType"] = task_data->contractObjectType;
		data["coveredFlag"] = task_data->coveredFlag;
		data["securityOptionID"] = task_data->securityOptionID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["securityID"] = task_data->securityID;
		data["seatID"] = task_data->seatID;
		data["execPrice"] = task_data->execPrice;
		data["execQty"] = task_data->execQty;
		data["tradeQty"] = task_data->tradeQty;
		data["clearFunds"] = task_data->clearFunds;
		data["settleFunds"] = task_data->settleFunds;
		data["commission"] = task_data->commission;
		data["stampTax"] = task_data->stampTax;
		data["transferFee"] = task_data->transferFee;
		data["fee3"] = task_data->fee3;
		data["fee4"] = task_data->fee4;
		data["summaryMsg"] = task_data->summaryMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryExecAssiInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryTradeTime(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryTradeTimeField *task_data = (DFITCSOPRspQryTradeTimeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sysTradingDay"] = task_data->sysTradingDay;
		data["sysTime"] = task_data->sysTime;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryTradeTime(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryExchangeInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryExchangeInfoField *task_data = (DFITCSOPRspQryExchangeInfoField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["exchangeID"] = task_data->exchangeID;
		data["exchangeName"] = task_data->exchangeName;
		data["callauctionBegining"] = task_data->callauctionBegining;
		data["callauctionEnding"] = task_data->callauctionEnding;
		data["morningOpening"] = task_data->morningOpening;
		data["morningClosing"] = task_data->morningClosing;
		data["afternoonOpening"] = task_data->afternoonOpening;
		data["afternoonClosing"] = task_data->afternoonClosing;
		data["execOpening"] = task_data->execOpening;
		data["execClosing"] = task_data->execClosing;
		data["nightTradeFlag"] = task_data->nightTradeFlag;
		data["nightOpening"] = task_data->nightOpening;
		data["nightClosing"] = task_data->nightClosing;
		data["stockTradeStatus"] = task_data->stockTradeStatus;
		data["currency"] = task_data->currency;
		data["tradingDayFlag"] = task_data->tradingDayFlag;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryExchangeInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryCommission(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryCommissionField *task_data = (DFITCSOPRspQryCommissionField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["refType"] = task_data->refType;
		data["contractObjectType"] = task_data->contractObjectType;
		data["securityID"] = task_data->securityID;
		data["openCloseFlag"] = task_data->openCloseFlag;
		data["entrustDirection"] = task_data->entrustDirection;
		data["level"] = task_data->level;
		data["costRatio1"] = task_data->costRatio1;
		data["unitCost1"] = task_data->unitCost1;
		data["costUpLimit1"] = task_data->costUpLimit1;
		data["costDonwLimit1"] = task_data->costDonwLimit1;
		data["costRatio2"] = task_data->costRatio2;
		data["unitCost2"] = task_data->unitCost2;
		data["costUpLimit2"] = task_data->costUpLimit2;
		data["costDonwLimit2"] = task_data->costDonwLimit2;
		data["costRatio3"] = task_data->costRatio3;
		data["unitCost3"] = task_data->unitCost3;
		data["costRatio4"] = task_data->costRatio4;
		data["unitCost4"] = task_data->unitCost4;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryCommission(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryDeposit(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryDepositField *task_data = (DFITCSOPRspQryDepositField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["refType"] = task_data->refType;
		data["securityObjectType"] = task_data->securityObjectType;
		data["securityID"] = task_data->securityID;
		data["depositRateC"] = task_data->depositRateC;
		data["depositRateE"] = task_data->depositRateE;
		data["depositUnit"] = task_data->depositUnit;
		data["calcType"] = task_data->calcType;
		data["level"] = task_data->level;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryDeposit(data, error, task->task_last);
	delete task;
};

void TdApi::processRspSOPQryContractObjectInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPRspQryContractObjectField *task_data = (DFITCSOPRspQryContractObjectField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityName"] = task_data->securityName;
		data["securityID"] = task_data->securityID;
		data["contractObjectType"] = task_data->contractObjectType;
		data["contractObjectStatus"] = task_data->contractObjectStatus;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPQryContractObjectInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processSOPEntrustOrderRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPEntrustOrderRtnField *task_data = (DFITCSOPEntrustOrderRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["branchID"] = task_data->branchID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["currency"] = task_data->currency;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["openCloseFlag"] = task_data->openCloseFlag;
		data["entrustPrice"] = task_data->entrustPrice;
		data["entrustQty"] = task_data->entrustQty;
		data["entrustTime"] = task_data->entrustTime;
		data["coveredFlag"] = task_data->coveredFlag;
		data["orderType"] = task_data->orderType;
		data["orderExpiryDate"] = task_data->orderExpiryDate;
		data["orderCategory"] = task_data->orderCategory;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		data["devID"] = task_data->devID;
		data["devDecInfo"] = task_data->devDecInfo;
		delete task->task_data;
	}

	this->onSOPEntrustOrderRtn(data);
	delete task;
};

void TdApi::processSOPTradeRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPTradeRtnField *task_data = (DFITCSOPTradeRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["currency"] = task_data->currency;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["openCloseFlag"] = task_data->openCloseFlag;
		data["coveredFlag"] = task_data->coveredFlag;
		data["orderCategory"] = task_data->orderCategory;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeQty"] = task_data->tradeQty;
		data["tradeID"] = task_data->tradeID;
		data["rtnSerialID"] = task_data->rtnSerialID;
		data["declareOrderID"] = task_data->declareOrderID;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		data["devID"] = task_data->devID;
		data["devDecInfo"] = task_data->devDecInfo;
		data["tradeTime"] = task_data->tradeTime;
		delete task->task_data;
	}

	this->onSOPTradeRtn(data);
	delete task;
};

void TdApi::processSOPWithdrawOrderRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPWithdrawOrderRtnField *task_data = (DFITCSOPWithdrawOrderRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["currency"] = task_data->currency;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["openCloseFlag"] = task_data->openCloseFlag;
		data["withdrawQty"] = task_data->withdrawQty;
		data["tradeQty"] = task_data->tradeQty;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		data["wdUnFreezeFunds"] = task_data->wdUnFreezeFunds;
		data["devID"] = task_data->devID;
		data["devDecInfo"] = task_data->devDecInfo;
		delete task->task_data;
	}

	this->onSOPWithdrawOrderRtn(data);
	delete task;
};

void TdApi::processRspFASLUserLogin(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = task_data->loginTime;
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLUserLogin(data, error);
	delete task;
};

void TdApi::processRspFASLUserLogout(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLUserLogout(data, error);
	delete task;
};

void TdApi::processRspFASLQryAbleFinInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspAbleFinInfoField *task_data = (DFITCFASLRspAbleFinInfoField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["accountBanlance"] = task_data->accountBanlance;
		data["ableFinFunds"] = task_data->ableFinFunds;
		data["turnover"] = task_data->turnover;
		data["entrustFreezeFunds"] = task_data->entrustFreezeFunds;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryAbleFinInfo(data, error);
	delete task;
};

void TdApi::processRspFASLQryAbleSloInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspAbleSloInfoField *task_data = (DFITCFASLRspAbleSloInfoField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["securityID"] = task_data->securityID;
		data["exchangeID"] = task_data->exchangeID;
		data["ableSloQty"] = task_data->ableSloQty;
		data["securityName"] = task_data->securityName;
		data["entrustQty"] = task_data->entrustQty;
		data["tradeQty"] = task_data->tradeQty;
		data["status"] = task_data->status;
		data["sloDepositRatio"] = task_data->sloDepositRatio;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryAbleSloInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLTransferCollateral(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspTransferCollateralField *task_data = (DFITCFASLRspTransferCollateralField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["localOrderID"] = task_data->localOrderID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLTransferCollateral(data, error);
	delete task;
};

void TdApi::processRspFASLDirectRepayment(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspDirectRepaymentField *task_data = (DFITCFASLRspDirectRepaymentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["realRepayFunds"] = task_data->realRepayFunds;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLDirectRepayment(data, error);
	delete task;
};

void TdApi::processRspFASLRepayStockTransfer(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspRepayStockTransferField *task_data = (DFITCFASLRspRepayStockTransferField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["localOrderID"] = task_data->localOrderID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLRepayStockTransfer(data, error);
	delete task;
};

void TdApi::processRspFASLEntrustCrdtOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspEntrustCrdtOrderField *task_data = (DFITCFASLRspEntrustCrdtOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["localOrderID"] = task_data->localOrderID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLEntrustCrdtOrder(data, error);
	delete task;
};

void TdApi::processRspFASLEntrustOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspEntrustOrderField *task_data = (DFITCFASLRspEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLEntrustOrder(data, error);
	delete task;
};

void TdApi::processRspFASLCalcAbleEntrustCrdtQty(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspCalcAbleEntrustCrdtQtyField *task_data = (DFITCFASLRspCalcAbleEntrustCrdtQtyField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["totalRepayQty"] = task_data->totalRepayQty;
		data["entrustQty"] = task_data->entrustQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLCalcAbleEntrustCrdtQty(data, error);
	delete task;
};

void TdApi::processRspFASLQryCrdtFunds(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryCrdtFundsField *task_data = (DFITCFASLRspQryCrdtFundsField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["availableDeposit"] = task_data->availableDeposit;
		data["maintGuaranteeRatio"] = task_data->maintGuaranteeRatio;
		data["antiMaintGuaranteeRatio"] = task_data->antiMaintGuaranteeRatio;
		data["accountBanlance"] = task_data->accountBanlance;
		data["availableFunds"] = task_data->availableFunds;
		data["clearFunds"] = task_data->clearFunds;
		data["stockMarket"] = task_data->stockMarket;
		data["guaranteeStockSubMarket"] = task_data->guaranteeStockSubMarket;
		data["guaranteeStockMarket"] = task_data->guaranteeStockMarket;
		data["tradeFinLiabilities"] = task_data->tradeFinLiabilities;
		data["tradeSloLiabilities"] = task_data->tradeSloLiabilities;
		data["orderFinLiabilities"] = task_data->orderFinLiabilities;
		data["orderSloLiabilities"] = task_data->orderSloLiabilities;
		data["sloOrderRepay"] = task_data->sloOrderRepay;
		data["fundsBalance"] = task_data->fundsBalance;
		data["closeFunds"] = task_data->closeFunds;
		data["activeCloseFunds"] = task_data->activeCloseFunds;
		data["ableWithdrawalAssetsStand"] = task_data->ableWithdrawalAssetsStand;
		data["withdrawalFunds"] = task_data->withdrawalFunds;
		data["totalAssets"] = task_data->totalAssets;
		data["unTransferStockMarket"] = task_data->unTransferStockMarket;
		data["totalLiabilities"] = task_data->totalLiabilities;
		data["netAssets"] = task_data->netAssets;
		data["sellRepayFunds"] = task_data->sellRepayFunds;
		data["anticipatedInterest"] = task_data->anticipatedInterest;
		data["finProfitLoss"] = task_data->finProfitLoss;
		data["sloProfitLoss"] = task_data->sloProfitLoss;
		data["sloFunds"] = task_data->sloFunds;
		data["finCost"] = task_data->finCost;
		data["sloCost"] = task_data->sloCost;
		data["finCurMarket"] = task_data->finCurMarket;
		data["finUsedDeposit"] = task_data->finUsedDeposit;
		data["sloUsedDeposit"] = task_data->sloUsedDeposit;
		data["finAntiInterest"] = task_data->finAntiInterest;
		data["sloAntiInterest"] = task_data->sloAntiInterest;
		data["shGuaranteeStockMarket"] = task_data->shGuaranteeStockMarket;
		data["szGuaranteeStockMarket"] = task_data->szGuaranteeStockMarket;
		data["finFloatProfit"] = task_data->finFloatProfit;
		data["finFloatLoss"] = task_data->finFloatLoss;
		data["sloFloatProfit"] = task_data->sloFloatProfit;
		data["sloFloatLoss"] = task_data->sloFloatLoss;
		data["finRatio"] = task_data->finRatio;
		data["sloRatio"] = task_data->sloRatio;
		data["contractEndDate"] = task_data->contractEndDate;
		data["finUsedLimits"] = task_data->finUsedLimits;
		data["sloUsedLimits"] = task_data->sloUsedLimits;
		data["finCreditLimits"] = task_data->finCreditLimits;
		data["sloCreditLimits"] = task_data->sloCreditLimits;
		data["ableBuyCollateralFunds"] = task_data->ableBuyCollateralFunds;
		data["ableRepayFunds"] = task_data->ableRepayFunds;
		data["sloAvailableFunds"] = task_data->sloAvailableFunds;
		data["cashAssets"] = task_data->cashAssets;
		data["totalStockMarket"] = task_data->totalStockMarket;
		data["finContractFunds"] = task_data->finContractFunds;
		data["contractObjectMarket"] = task_data->contractObjectMarket;
		data["otherCharges"] = task_data->otherCharges;
		data["sloCurMarket"] = task_data->sloCurMarket;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryCrdtFunds(data, error);
	delete task;
};

void TdApi::processRspFASLQryCrdtContract(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryCrdtContractField *task_data = (DFITCFASLRspQryCrdtContractField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["conSerialNO"] = task_data->conSerialNO;
		data["contractNO"] = task_data->contractNO;
		data["operatorDate"] = task_data->operatorDate;
		data["endDate"] = task_data->endDate;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["currency"] = task_data->currency;
		data["finQty"] = task_data->finQty;
		data["finFunds"] = task_data->finFunds;
		data["sloQty"] = task_data->sloQty;
		data["sloFunds"] = task_data->sloFunds;
		data["finEntrustQty"] = task_data->finEntrustQty;
		data["finEntrustFunds"] = task_data->finEntrustFunds;
		data["sloEntrustQty"] = task_data->sloEntrustQty;
		data["sloEntrustFunds"] = task_data->sloEntrustFunds;
		data["finTradeQty"] = task_data->finTradeQty;
		data["finTradeFunds"] = task_data->finTradeFunds;
		data["sloTradeQty"] = task_data->sloTradeQty;
		data["sloTradeFunds"] = task_data->sloTradeFunds;
		data["debtPrincipal"] = task_data->debtPrincipal;
		data["repayFunds"] = task_data->repayFunds;
		data["debtQty"] = task_data->debtQty;
		data["repayQty"] = task_data->repayQty;
		data["sellStockRepayFunds"] = task_data->sellStockRepayFunds;
		data["buyStockForRepayEntrustQty"] = task_data->buyStockForRepayEntrustQty;
		data["buyStockForRepayTradeQty"] = task_data->buyStockForRepayTradeQty;
		data["finCost"] = task_data->finCost;
		data["sloCost"] = task_data->sloCost;
		data["totalInterest"] = task_data->totalInterest;
		data["repaidInterest"] = task_data->repaidInterest;
		data["crdtConStatus"] = task_data->crdtConStatus;
		data["leftInterest"] = task_data->leftInterest;
		data["sloLeftFunds"] = task_data->sloLeftFunds;
		data["buyStockFreezeFunds"] = task_data->buyStockFreezeFunds;
		data["buyStockClearFunds"] = task_data->buyStockClearFunds;
		data["sloLeftAvaiFunds"] = task_data->sloLeftAvaiFunds;
		data["debtQtyEntrustMarket"] = task_data->debtQtyEntrustMarket;
		data["debtQtyTradeMarket"] = task_data->debtQtyTradeMarket;
		data["debtFundsMarket"] = task_data->debtFundsMarket;
		data["finProfitLoss"] = task_data->finProfitLoss;
		data["sloProfitLoss"] = task_data->sloProfitLoss;
		data["entrustQty"] = task_data->entrustQty;
		data["conOpenQty"] = task_data->conOpenQty;
		data["conOpenFunds"] = task_data->conOpenFunds;
		data["conOpenCost"] = task_data->conOpenCost;
		data["conInitQty"] = task_data->conInitQty;
		data["conInitFunds"] = task_data->conInitFunds;
		data["conInitCost"] = task_data->conInitCost;
		data["unRepayConFunds"] = task_data->unRepayConFunds;
		data["unRepayConQty"] = task_data->unRepayConQty;
		data["unRepayConCost"] = task_data->unRepayConCost;
		data["positionNO"] = task_data->positionNO;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryCrdtContract(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryCrdtConChangeInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryCrdtConChangeInfoField *task_data = (DFITCFASLRspQryCrdtConChangeInfoField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["serialNO"] = task_data->serialNO;
		data["conChangeNO"] = task_data->conChangeNO;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["securityID"] = task_data->securityID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["operatorFunds"] = task_data->operatorFunds;
		data["operatorTime"] = task_data->operatorTime;
		data["operatorQty"] = task_data->operatorQty;
		data["operatorDate"] = task_data->operatorDate;
		data["clearFlag"] = task_data->clearFlag;
		data["commission"] = task_data->commission;
		data["operatorFunds2"] = task_data->operatorFunds2;
		data["postFunds"] = task_data->postFunds;
		data["postQty"] = task_data->postQty;
		data["exchangeID"] = task_data->exchangeID;
		data["operatorCost"] = task_data->operatorCost;
		data["postCost"] = task_data->postCost;
		data["operatorInterest"] = task_data->operatorInterest;
		data["postInterest"] = task_data->postInterest;
		data["changeNote"] = task_data->changeNote;
		data["shareholderID"] = task_data->shareholderID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryCrdtConChangeInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLTransferFunds(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspTransferFundsField *task_data = (DFITCStockRspTransferFundsField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["serialID"] = task_data->serialID;
		data["accountBanlance"] = task_data->accountBanlance;
		data["availableFunds"] = task_data->availableFunds;
		data["t2AvailableFunds"] = task_data->t2AvailableFunds;
		data["fundsTransFlag"] = task_data->fundsTransFlag;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLTransferFunds(data, error);
	delete task;
};

void TdApi::processRspFASLQryAccountInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryAccountField *task_data = (DFITCStockRspQryAccountField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["tel"] = task_data->tel;
		data["accountID"] = task_data->accountID;
		data["accountName"] = task_data->accountName;
		data["accountIdentityID"] = task_data->accountIdentityID;
		data["accountIdentityType"] = task_data->accountIdentityType;
		data["branchID"] = task_data->branchID;
		data["branchType"] = task_data->branchType;
		data["mobile"] = task_data->mobile;
		data["entrustType"] = task_data->entrustType;
		data["accountStatus"] = task_data->accountStatus;
		data["pwdSynFlag"] = task_data->pwdSynFlag;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryAccountInfo(data, error);
	delete task;
};

void TdApi::processRspFASLQryCapitalAccountInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryCapitalAccountField *task_data = (DFITCStockRspQryCapitalAccountField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["currency"] = task_data->currency;
		data["availableFunds"] = task_data->availableFunds;
		data["t2AvailableFunds"] = task_data->t2AvailableFunds;
		data["anticipatedInterest"] = task_data->anticipatedInterest;
		data["accountBalance"] = task_data->accountBalance;
		data["accountStatus"] = task_data->accountStatus;
		data["accountID"] = task_data->accountID;
		data["freezeFunds"] = task_data->freezeFunds;
		data["t2FreezeFunds"] = task_data->t2FreezeFunds;
		data["branchID"] = task_data->branchID;
		data["totalFunds"] = task_data->totalFunds;
		data["totalMarket"] = task_data->totalMarket;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryCapitalAccountInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryShareholderInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryShareholderField *task_data = (DFITCStockRspQryShareholderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["account"] = task_data->account;
		data["shareholderID"] = task_data->shareholderID;
		data["shareholderSpecProp"] = task_data->shareholderSpecProp;
		data["tradePermissions"] = task_data->tradePermissions;
		data["exchangeID"] = task_data->exchangeID;
		data["shareholderStatus"] = task_data->shareholderStatus;
		data["mainAccountFlag"] = task_data->mainAccountFlag;
		data["shareholderCtlProp"] = task_data->shareholderCtlProp;
		data["branchID"] = task_data->branchID;
		data["shareholderType"] = task_data->shareholderType;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryShareholderInfo(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryPositionField *task_data = (DFITCStockRspQryPositionField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["sellTurnover"] = task_data->sellTurnover;
		data["sellTradeQty"] = task_data->sellTradeQty;
		data["sellEntrustQty"] = task_data->sellEntrustQty;
		data["buyTurnover"] = task_data->buyTurnover;
		data["buyTradeQty"] = task_data->buyTradeQty;
		data["buyEntrustQty"] = task_data->buyEntrustQty;
		data["nonCirculateQty"] = task_data->nonCirculateQty;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["openDate"] = task_data->openDate;
		data["ableSellQty"] = task_data->ableSellQty;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["securityQty"] = task_data->securityQty;
		data["position"] = task_data->position;
		data["unSettleQty"] = task_data->unSettleQty;
		data["changeDate"] = task_data->changeDate;
		data["ablePurchaseQty"] = task_data->ablePurchaseQty;
		data["ableRedemptionQty"] = task_data->ableRedemptionQty;
		data["freezeQty"] = task_data->freezeQty;
		data["offsetSQty"] = task_data->offsetSQty;
		data["offsetBQty"] = task_data->offsetBQty;
		data["purchaseTradeQty"] = task_data->purchaseTradeQty;
		data["redemptionTradeQty"] = task_data->redemptionTradeQty;
		data["tradeUnit"] = task_data->tradeUnit;
		data["totalSellQty"] = task_data->totalSellQty;
		data["totalBuyQty"] = task_data->totalBuyQty;
		data["rationedSharesQty"] = task_data->rationedSharesQty;
		data["purchaseQty"] = task_data->purchaseQty;
		data["dilutedFloatProfitLoss"] = task_data->dilutedFloatProfitLoss;
		data["dilutedBreakevenPrice"] = task_data->dilutedBreakevenPrice;
		data["dilutedCost"] = task_data->dilutedCost;
		data["avgPositionPrice"] = task_data->avgPositionPrice;
		data["floatProfitLoss"] = task_data->floatProfitLoss;
		data["dividend"] = task_data->dividend;
		data["totalFloatProfitLoss"] = task_data->totalFloatProfitLoss;
		data["sellAmount"] = task_data->sellAmount;
		data["buyAmount"] = task_data->buyAmount;
		data["buyAvgPrice"] = task_data->buyAvgPrice;
		data["rationedSharesAmount"] = task_data->rationedSharesAmount;
		data["latestMarket"] = task_data->latestMarket;
		data["breakevenPrice"] = task_data->breakevenPrice;
		data["latestPrice"] = task_data->latestPrice;
		data["nonCirculateMarket"] = task_data->nonCirculateMarket;
		data["interestQuote"] = task_data->interestQuote;
		data["preClosePrice"] = task_data->preClosePrice;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryPosition(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryEntrustOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryEntrustOrderField *task_data = (DFITCStockRspQryEntrustOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["offerShareholderID"] = task_data->offerShareholderID;
		data["currency"] = task_data->currency;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeTime"] = task_data->tradeTime;
		data["tradeQty"] = task_data->tradeQty;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["clearFunds"] = task_data->clearFunds;
		data["entrustType"] = task_data->entrustType;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustPrice"] = task_data->entrustPrice;
		data["entrustDirection"] = task_data->entrustDirection;
		data["entrustQty"] = task_data->entrustQty;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["entrustTime"] = task_data->entrustTime;
		data["declareTime"] = task_data->declareTime;
		data["declareResult"] = task_data->declareResult;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["freezeFunds"] = task_data->freezeFunds;
		data["accountID"] = task_data->accountID;
		data["noteMsg"] = task_data->noteMsg;
		data["withdrawQty"] = task_data->withdrawQty;
		data["declareOrderID"] = task_data->declareOrderID;
		data["orderType"] = task_data->orderType;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["freezeFundsSerialID"] = task_data->freezeFundsSerialID;
		data["freezeStockSerialID"] = task_data->freezeStockSerialID;
		data["declareDate"] = task_data->declareDate;
		data["declareSerialID"] = task_data->declareSerialID;
		data["entrustDate"] = task_data->entrustDate;
		data["incQryIndex"] = task_data->incQryIndex;
		data["ipAddr"] = task_data->ipAddr;
		data["macAddr"] = task_data->macAddr;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryEntrustOrder(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQrySerialTrade(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQrySerialTradeField *task_data = (DFITCStockRspQrySerialTradeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["tradeID"] = task_data->tradeID;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeQty"] = task_data->tradeQty;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["clearFunds"] = task_data->clearFunds;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["commission"] = task_data->commission;
		data["rtnSerialID"] = task_data->rtnSerialID;
		data["interestQuote"] = task_data->interestQuote;
		data["declareOrderID"] = task_data->declareOrderID;
		data["incQryIndex"] = task_data->incQryIndex;
		data["interest"] = task_data->interest;
		data["tradeTime"] = task_data->tradeTime;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQrySerialTrade(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryRealTimeTrade(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryRealTimeTradeField *task_data = (DFITCStockRspQryRealTimeTradeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["spdOrderID"] = task_data->spdOrderID;
		data["declareOrderID"] = task_data->declareOrderID;
		data["exchangeID"] = task_data->exchangeID;
		data["shareholderID"] = task_data->shareholderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["entrustQty"] = task_data->entrustQty;
		data["entrustPrice"] = task_data->entrustPrice;
		data["withdrawQty"] = task_data->withdrawQty;
		data["tradeQty"] = task_data->tradeQty;
		data["turnover"] = task_data->turnover;
		data["tradePrice"] = task_data->tradePrice;
		data["tradeTime"] = task_data->tradeTime;
		data["currency"] = task_data->currency;
		data["clearFunds"] = task_data->clearFunds;
		data["entrustBatchID"] = task_data->entrustBatchID;
		data["orderType"] = task_data->orderType;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryRealTimeTrade(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryFreezeFundsDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryFreezeFundsDetailField *task_data = (DFITCStockRspQryFreezeFundsDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["fundsFreezeType"] = task_data->fundsFreezeType;
		data["accountName"] = task_data->accountName;
		data["summaryMsg"] = task_data->summaryMsg;
		data["serialID"] = task_data->serialID;
		data["operatorFunds"] = task_data->operatorFunds;
		data["operatorTime"] = task_data->operatorTime;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryFreezeFundsDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryFreezeStockDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryFreezeStockDetailField *task_data = (DFITCStockRspQryFreezeStockDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["stockFreezeType"] = task_data->stockFreezeType;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["accountName"] = task_data->accountName;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["securityName"] = task_data->securityName;
		data["summaryMsg"] = task_data->summaryMsg;
		data["serialID"] = task_data->serialID;
		data["operatorTime"] = task_data->operatorTime;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		data["operatorQty"] = task_data->operatorQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryFreezeStockDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryTransferFundsDetail(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockRspQryTransferFundsDetailField *task_data = (DFITCStockRspQryTransferFundsDetailField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["currency"] = task_data->currency;
		data["fundsFreezeType"] = task_data->fundsFreezeType;
		data["accountName"] = task_data->accountName;
		data["summaryMsg"] = task_data->summaryMsg;
		data["serialID"] = task_data->serialID;
		data["operatorFunds"] = task_data->operatorFunds;
		data["operatorTime"] = task_data->operatorTime;
		data["branchID"] = task_data->branchID;
		data["operatorDate"] = task_data->operatorDate;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryTransferFundsDetail(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLWithdrawOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspWithdrawOrderField *task_data = (DFITCFASLRspWithdrawOrderField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["localOrderID"] = task_data->localOrderID;
		data["spdOrderID"] = task_data->spdOrderID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLWithdrawOrder(data, error);
	delete task;
};

void TdApi::processRspFASLQrySystemTime(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryTradeTimeField *task_data = (DFITCFASLRspQryTradeTimeField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sysTradingDay"] = task_data->sysTradingDay;
		data["sysTime"] = task_data->sysTime;
		data["sysWeek"] = task_data->sysWeek;
		data["sysMillisecond"] = task_data->sysMillisecond;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQrySystemTime(data, error);
	delete task;
};

void TdApi::processRspFASLQryTransferredContract(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryTransferredContractField *task_data = (DFITCFASLRspQryTransferredContractField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["capitalID"] = task_data->capitalID;
		data["securityID"] = task_data->securityID;
		data["exchangeID"] = task_data->exchangeID;
		data["ableSellQty"] = task_data->ableSellQty;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryTransferredContract(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLDesirableFundsOut(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspDesirableFundsOutField *task_data = (DFITCFASLRspDesirableFundsOutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["serialID"] = task_data->serialID;
		data["accountBanlance"] = task_data->accountBanlance;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLDesirableFundsOut(data, error);
	delete task;
};

void TdApi::processRspFASLQryGuaranteedContract(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryGuaranteedContractField *task_data = (DFITCFASLRspQryGuaranteedContractField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["exchangRate"] = task_data->exchangRate;
		data["status"] = task_data->status;
		data["accountType"] = task_data->accountType;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryGuaranteedContract(data, error, task->task_last);
	delete task;
};

void TdApi::processRspFASLQryUnderlyingContract(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCFASLRspQryUnderlyingContractField *task_data = (DFITCFASLRspQryUnderlyingContractField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		data["financeDepositRatio"] = task_data->financeDepositRatio;
		data["securityDepositRatio"] = task_data->securityDepositRatio;
		data["status"] = task_data->status;
		data["accountType"] = task_data->accountType;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLQryUnderlyingContract(data, error, task->task_last);
	delete task;
};

void TdApi::processFASLEntrustOrderRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockEntrustOrderRtnField *task_data = (DFITCStockEntrustOrderRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["withdrawQty"] = task_data->withdrawQty;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["freezeFunds"] = task_data->freezeFunds;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		data["entrustQty"] = task_data->entrustQty;
		data["orderConfirmFlag"] = task_data->orderConfirmFlag;
		data["entrustTime"] = task_data->entrustTime;
		data["entrustPrice"] = task_data->entrustPrice;
		data["orderType"] = task_data->orderType;
		delete task->task_data;
	}

	this->onFASLEntrustOrderRtn(data);
	delete task;
};

void TdApi::processFASLTradeRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockTradeRtnField *task_data = (DFITCStockTradeRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["tradeID"] = task_data->tradeID;
		data["tradeTime"] = task_data->tradeTime;
		data["withdrawQty"] = task_data->withdrawQty;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["clearFunds"] = task_data->clearFunds;
		data["totalTradeQty"] = task_data->totalTradeQty;
		data["totalTurnover"] = task_data->totalTurnover;
		data["tradeQty"] = task_data->tradeQty;
		data["tradePrice"] = task_data->tradePrice;
		data["turnover"] = task_data->turnover;
		data["entrustQty"] = task_data->entrustQty;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		delete task->task_data;
	}

	this->onFASLTradeRtn(data);
	delete task;
};

void TdApi::processFASLWithdrawOrderRtn(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockWithdrawOrderRtnField *task_data = (DFITCStockWithdrawOrderRtnField*)task->task_data;
		data["localOrderID"] = task_data->localOrderID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["shareholderID"] = task_data->shareholderID;
		data["exchangeID"] = task_data->exchangeID;
		data["currency"] = task_data->currency;
		data["securityID"] = task_data->securityID;
		data["securityType"] = task_data->securityType;
		data["withdrawQty"] = task_data->withdrawQty;
		data["tradeQty"] = task_data->tradeQty;
		data["withdrawFlag"] = task_data->withdrawFlag;
		data["freezeFunds"] = task_data->freezeFunds;
		data["spdOrderID"] = task_data->spdOrderID;
		data["entrustDirection"] = task_data->entrustDirection;
		data["entrustQty"] = task_data->entrustQty;
		data["declareResult"] = task_data->declareResult;
		data["noteMsg"] = task_data->noteMsg;
		delete task->task_data;
	}

	this->onFASLWithdrawOrderRtn(data);
	delete task;
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::createDFITCSECTraderApi(string logAddr)
{
	this->api = DFITCSECTraderApi::CreateDFITCSECTraderApi(logAddr.c_str());
};

void TdApi::init(string pszSvrAddr)
{
	this->api->Init(pszSvrAddr.c_str(), this);
};

void TdApi::release()
{
	this->api->Release();
};

int TdApi::exit()
{
	this->api->Release();
	this->api = NULL;
	return 1;
};

int TdApi::subscribePrivateTopic(int type)
{
	int i = this->api->SubscribePrivateTopic((RESUME_TYPE)type);
	return i;
};

int TdApi::reqStockUserLogin(dict req)
{
	DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "password", myreq.password);
	getInt(req, "compressflag", &myreq.compressflag);
	int i = this->api->ReqStockUserLogin(&myreq);
	return i;
};

int TdApi::reqStockUserLogout(dict req)
{
	DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqStockUserLogout(&myreq);
	return i;
};

int TdApi::reqStockUserPasswordUpdate(dict req)
{
	DFITCSECReqPasswordUpdateField myreq = DFITCSECReqPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "oldPassword", myreq.oldPassword);
	getString(req, "newPassword", myreq.newPassword);
	getInt(req, "passwordType", &myreq.passwordType);
	int i = this->api->ReqStockUserPasswordUpdate(&myreq);
	return i;
};

int TdApi::reqStockEntrustOrder(dict req)
{
	DFITCStockReqEntrustOrderField myreq = DFITCStockReqEntrustOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getDouble(req, "entrustPrice", &myreq.entrustPrice);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "orderType", &myreq.orderType);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getString(req, "eachSeatID", myreq.eachSeatID);
	getInt(req, "hkEntrustLimit", &myreq.hkEntrustLimit);
	getInt(req, "hkOrderType", &myreq.hkOrderType);
	int i = this->api->ReqStockEntrustOrder(&myreq);
	return i;
};

int TdApi::reqStockWithdrawOrder(dict req)
{
	DFITCSECReqWithdrawOrderField myreq = DFITCSECReqWithdrawOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	int i = this->api->ReqStockWithdrawOrder(&myreq);
	return i;
};

int TdApi::reqStockQryEntrustOrder(dict req)
{
	DFITCStockReqQryEntrustOrderField myreq = DFITCStockReqQryEntrustOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "entrustQryFlag", &myreq.entrustQryFlag);
	getString(req, "withdrawFlag", myreq.withdrawFlag);
	getString(req, "incQryIndex", myreq.incQryIndex);
	int i = this->api->ReqStockQryEntrustOrder(&myreq);
	return i;
};

int TdApi::reqStockQryRealTimeTrade(dict req)
{
	DFITCStockReqQryRealTimeTradeField myreq = DFITCStockReqQryRealTimeTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "queryFlag", &myreq.queryFlag);
	int i = this->api->ReqStockQryRealTimeTrade(&myreq);
	return i;
};

int TdApi::reqStockQrySerialTrade(dict req)
{
	DFITCStockReqQrySerialTradeField myreq = DFITCStockReqQrySerialTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "tradeQryFlag", &myreq.tradeQryFlag);
	getString(req, "incQryIndex", myreq.incQryIndex);
	int i = this->api->ReqStockQrySerialTrade(&myreq);
	return i;
};

int TdApi::reqStockQryPosition(dict req)
{
	DFITCStockReqQryPositionField myreq = DFITCStockReqQryPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "posiQryFlag", &myreq.posiQryFlag);
	int i = this->api->ReqStockQryPosition(&myreq);
	return i;
};

int TdApi::reqStockQryCapitalAccountInfo(dict req)
{
	DFITCStockReqQryCapitalAccountField myreq = DFITCStockReqQryCapitalAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "FundsQryFlag", &myreq.FundsQryFlag);
	int i = this->api->ReqStockQryCapitalAccountInfo(&myreq);
	return i;
};

int TdApi::reqStockQryAccountInfo(dict req)
{
	DFITCStockReqQryAccountField myreq = DFITCStockReqQryAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqStockQryAccountInfo(&myreq);
	return i;
};

int TdApi::reqStockQryShareholderInfo(dict req)
{
	DFITCStockReqQryShareholderField myreq = DFITCStockReqQryShareholderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqStockQryShareholderInfo(&myreq);
	return i;
};

int TdApi::reqStockTransferFunds(dict req)
{
	DFITCStockReqTransferFundsField myreq = DFITCStockReqTransferFundsField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "currency", myreq.currency);
	getString(req, "summaryMsg", myreq.summaryMsg);
	getString(req, "summaryMsg", myreq.summaryMsg);
	getInt(req, "fundsTransFlag", &myreq.fundsTransFlag);
	int i = this->api->ReqStockTransferFunds(&myreq);
	return i;
};

int TdApi::reqStockEntrustBatchOrder(dict req)
{
	DFITCStockReqEntrustBatchOrderField myreq = DFITCStockReqEntrustBatchOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "entrustCount", &myreq.entrustCount);
	getString(req, "entrustDetail", myreq.entrustDetail);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	int i = this->api->ReqStockEntrustBatchOrder(&myreq);
	return i;
};

int TdApi::reqStockWithdrawBatchOrder(dict req)
{
	DFITCStockReqWithdrawBatchOrderField myreq = DFITCStockReqWithdrawBatchOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "orderRangeID", myreq.orderRangeID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	int i = this->api->ReqStockWithdrawBatchOrder(&myreq);
	return i;
};

int TdApi::reqStockCalcAbleEntrustQty(dict req)
{
	DFITCStockReqCalcAbleEntrustQtyField myreq = DFITCStockReqCalcAbleEntrustQtyField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "orderType", &myreq.orderType);
	int i = this->api->ReqStockCalcAbleEntrustQty(&myreq);
	return i;
};

int TdApi::reqStockCalcAblePurchaseETFQty(dict req)
{
	DFITCStockReqCalcAblePurchaseETFQtyField myreq = DFITCStockReqCalcAblePurchaseETFQtyField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	int i = this->api->ReqStockCalcAblePurchaseETFQty(&myreq);
	return i;
};

int TdApi::reqStockQryFreezeFundsDetail(dict req)
{
	DFITCStockReqQryFreezeFundsDetailField myreq = DFITCStockReqQryFreezeFundsDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "currency", myreq.currency);
	getInt(req, "fundsFreezeType", &myreq.fundsFreezeType);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->ReqStockQryFreezeFundsDetail(&myreq);
	return i;
};

int TdApi::reqStockQryFreezeStockDetail(dict req)
{
	DFITCStockReqQryFreezeStockDetailField myreq = DFITCStockReqQryFreezeStockDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getInt(req, "stockFreezeType", &myreq.stockFreezeType);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->ReqStockQryFreezeStockDetail(&myreq);
	return i;
};

int TdApi::reqStockQryTransferFundsDetail(dict req)
{
	DFITCStockReqQryTransferFundsDetailField myreq = DFITCStockReqQryTransferFundsDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "currency", myreq.currency);
	getInt(req, "fundsFreezeType", &myreq.fundsFreezeType);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->ReqStockQryTransferFundsDetail(&myreq);
	return i;
};

int TdApi::reqStockQryTransferStockDetail(dict req)
{
	DFITCStockReqQryTransferStockDetailField myreq = DFITCStockReqQryTransferStockDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getInt(req, "stockFreezeType", &myreq.stockFreezeType);
	getString(req, "incQryIndex", myreq.incQryIndex);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->ReqStockQryTransferStockDetail(&myreq);
	return i;
};

int TdApi::reqStockQryStockInfo(dict req)
{
	DFITCStockReqQryStockField myreq = DFITCStockReqQryStockField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	int i = this->api->ReqStockQryStockInfo(&myreq);
	return i;
};

int TdApi::reqStockQryStockStaticInfo(dict req)
{
	DFITCStockReqQryStockStaticField myreq = DFITCStockReqQryStockStaticField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqStockQryStockStaticInfo(&myreq);
	return i;
};

int TdApi::reqStockQryTradeTime(dict req)
{
	DFITCStockReqQryTradeTimeField myreq = DFITCStockReqQryTradeTimeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqStockQryTradeTime(&myreq);
	return i;
};

int TdApi::reqSOPUserLogin(dict req)
{
	DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "password", myreq.password);
	getInt(req, "compressflag", &myreq.compressflag);
	int i = this->api->ReqSOPUserLogin(&myreq);
	return i;
};

int TdApi::reqSOPUserLogout(dict req)
{
	DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqSOPUserLogout(&myreq);
	return i;
};

int TdApi::reqSOPUserPasswordUpdate(dict req)
{
	DFITCSECReqPasswordUpdateField myreq = DFITCSECReqPasswordUpdateField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "oldPassword", myreq.oldPassword);
	getString(req, "newPassword", myreq.newPassword);
	getInt(req, "passwordType", &myreq.passwordType);
	int i = this->api->ReqSOPUserPasswordUpdate(&myreq);
	return i;
};

int TdApi::reqSOPEntrustOrder(dict req)
{
	DFITCSOPReqEntrustOrderField myreq = DFITCSOPReqEntrustOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	getString(req, "subAccountID", myreq.subAccountID);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getDouble(req, "entrustPrice", &myreq.entrustPrice);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "openCloseFlag", &myreq.openCloseFlag);
	getInt(req, "coveredFlag", &myreq.coveredFlag);
	getInt(req, "orderType", &myreq.orderType);
	getInt(req, "orderExpiryDate", &myreq.orderExpiryDate);
	getInt(req, "orderCategory", &myreq.orderCategory);
	getInt(req, "serialID", &myreq.serialID);
	getString(req, "devID", myreq.devID);
	getString(req, "devDecInfo", myreq.devDecInfo);
	int i = this->api->ReqSOPEntrustOrder(&myreq);
	return i;
};

int TdApi::reqSOPGroupSplit(dict req)
{
	DFITCSOPReqGroupSplitField myreq = DFITCSOPReqGroupSplitField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getString(req, "subAccountID", myreq.subAccountID);
	getInt(req, "openCloseFlag", &myreq.openCloseFlag);
	getInt(req, "groupType", &myreq.groupType);
	getString(req, "groupCode", myreq.groupCode);
	getString(req, "securityOptionID1", myreq.securityOptionID1);
	getString(req, "securityOptionID2", myreq.securityOptionID2);
	getString(req, "securityOptionID3", myreq.securityOptionID3);
	getString(req, "securityOptionID4", myreq.securityOptionID4);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getString(req, "devID", myreq.devID);
	getString(req, "devDecInfo", myreq.devDecInfo);
	int i = this->api->ReqSOPGroupSplit(&myreq);
	return i;
};

int TdApi::reqSOPQryGroupPosition(dict req)
{
	DFITCSOPReqQryGroupPositionField myreq = DFITCSOPReqQryGroupPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqSOPQryGroupPosition(&myreq);
	return i;
};

int TdApi::reqSOPLockOUnLockStock(dict req)
{
	DFITCSOPReqLockOUnLockStockField myreq = DFITCSOPReqLockOUnLockStockField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "subAccountID", myreq.subAccountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getInt(req, "openCloseFlag", &myreq.openCloseFlag);
	getString(req, "devID", myreq.devID);
	getString(req, "devDecInfo", myreq.devDecInfo);
	int i = this->api->ReqSOPLockOUnLockStock(&myreq);
	return i;
};

int TdApi::reqSOPWithdrawOrder(dict req)
{
	DFITCSECReqWithdrawOrderField myreq = DFITCSECReqWithdrawOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	int i = this->api->ReqSOPWithdrawOrder(&myreq);
	return i;
};

int TdApi::reqSOPQryEntrustOrder(dict req)
{
	DFITCSOPReqQryEntrustOrderField myreq = DFITCSOPReqQryEntrustOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getString(req, "withdrawFlag", myreq.withdrawFlag);
	getInt(req, "exSerialID", &myreq.exSerialID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "entrustQryFlag", &myreq.entrustQryFlag);
	getInt(req, "rowIndex", &myreq.rowIndex);
	getInt(req, "rowCount", &myreq.rowCount);
	int i = this->api->ReqSOPQryEntrustOrder(&myreq);
	return i;
};

int TdApi::reqSOPQrySerialTrade(dict req)
{
	DFITCSOPReqQrySerialTradeField myreq = DFITCSOPReqQrySerialTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getString(req, "incQryIndex", myreq.incQryIndex);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "tradeQryFlag", &myreq.tradeQryFlag);
	getString(req, "currency", myreq.currency);
	getInt(req, "rowIndex", &myreq.rowIndex);
	getInt(req, "rowCount", &myreq.rowCount);
	int i = this->api->ReqSOPQrySerialTrade(&myreq);
	return i;
};

int TdApi::reqSOPQryPosition(dict req)
{
	DFITCSOPReqQryPositionField myreq = DFITCSOPReqQryPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getInt(req, "rowIndex", &myreq.rowIndex);
	getInt(req, "rowCount", &myreq.rowCount);
	int i = this->api->ReqSOPQryPosition(&myreq);
	return i;
};

int TdApi::reqSOPQryCollateralPosition(dict req)
{
	DFITCSOPReqQryCollateralPositionField myreq = DFITCSOPReqQryCollateralPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	int i = this->api->ReqSOPQryCollateralPosition(&myreq);
	return i;
};

int TdApi::reqSOPQryCapitalAccountInfo(dict req)
{
	DFITCSOPReqQryCapitalAccountField myreq = DFITCSOPReqQryCapitalAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "currency", myreq.currency);
	getInt(req, "FundsQryFlag", &myreq.FundsQryFlag);
	int i = this->api->ReqSOPQryCapitalAccountInfo(&myreq);
	return i;
};

int TdApi::reqSOPQryAccountInfo(dict req)
{
	DFITCSOPReqQryAccountField myreq = DFITCSOPReqQryAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqSOPQryAccountInfo(&myreq);
	return i;
};

int TdApi::reqSOPQryShareholderInfo(dict req)
{
	DFITCSOPReqQryShareholderField myreq = DFITCSOPReqQryShareholderField();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "accountID", myreq.accountID);
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqSOPQryShareholderInfo(&myreq);
	return i;
};

int TdApi::reqSOPCalcAbleEntrustQty(dict req)
{
	DFITCSOPReqCalcAbleEntrustQtyField myreq = DFITCSOPReqCalcAbleEntrustQtyField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "subAccountID", myreq.subAccountID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "openCloseFlag", &myreq.openCloseFlag);
	getInt(req, "coveredFlag", &myreq.coveredFlag);
	getInt(req, "coveredFlag", &myreq.coveredFlag);
	getInt(req, "checkUpLimit", &myreq.checkUpLimit);
	getString(req, "devID", myreq.devID);
	getString(req, "devDecInfo", myreq.devDecInfo);
	int i = this->api->ReqSOPCalcAbleEntrustQty(&myreq);
	return i;
};

int TdApi::reqSOPQryAbleLockStock(dict req)
{
	DFITCSOPReqQryAbleLockStockField myreq = DFITCSOPReqQryAbleLockStockField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	int i = this->api->ReqSOPQryAbleLockStock(&myreq);
	return i;
};

int TdApi::reqSOPQryContactInfo(dict req)
{
	DFITCSOPReqQryContactField myreq = DFITCSOPReqQryContactField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "contractObjectType", &myreq.contractObjectType);
	getInt(req, "optType", &myreq.optType);
	getString(req, "rowIndex", myreq.rowIndex);
	getInt(req, "rowCount", &myreq.rowCount);
	int i = this->api->ReqSOPQryContactInfo(&myreq);
	return i;
};

int TdApi::reqSOPExectueOrder(dict req)
{
	DFITCSOPReqExectueOrderField myreq = DFITCSOPReqExectueOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getString(req, "subAccountID", myreq.subAccountID);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "openCloseFlag", &myreq.openCloseFlag);
	getString(req, "devID", myreq.devID);
	getString(req, "devDecInfo", myreq.devDecInfo);
	int i = this->api->ReqSOPExectueOrder(&myreq);
	return i;
};

int TdApi::reqSOPQryExecAssiInfo(dict req)
{
	DFITCSOPReqQryExecAssiInfoField myreq = DFITCSOPReqQryExecAssiInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityOptionID", myreq.securityOptionID);
	getInt(req, "tradeDate", &myreq.tradeDate);
	int i = this->api->ReqSOPQryExecAssiInfo(&myreq);
	return i;
};

int TdApi::reqSOPQryTradeTime(dict req)
{
	DFITCSOPReqQryTradeTimeField myreq = DFITCSOPReqQryTradeTimeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqSOPQryTradeTime(&myreq);
	return i;
};

int TdApi::reqSOPQryExchangeInfo(dict req)
{
	DFITCSOPReqQryExchangeInfoField myreq = DFITCSOPReqQryExchangeInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqSOPQryExchangeInfo(&myreq);
	return i;
};

int TdApi::reqSOPQryCommission(dict req)
{
	DFITCSOPReqQryCommissionField myreq = DFITCSOPReqQryCommissionField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getInt(req, "refType", &myreq.refType);
	getInt(req, "contractObjectType", &myreq.contractObjectType);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "openCloseFlag", &myreq.openCloseFlag);
	getInt(req, "level", &myreq.level);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	int i = this->api->ReqSOPQryCommission(&myreq);
	return i;
};

int TdApi::reqSOPQryDeposit(dict req)
{
	DFITCSOPReqQryDepositField myreq = DFITCSOPReqQryDepositField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getInt(req, "refType", &myreq.refType);
	getInt(req, "securityObjectType", &myreq.securityObjectType);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "level", &myreq.level);
	int i = this->api->ReqSOPQryDeposit(&myreq);
	return i;
};

int TdApi::reqSOPQryContractObjectInfo(dict req)
{
	DFITCSOPReqQryContractObjectField myreq = DFITCSOPReqQryContractObjectField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "securityObjectType", &myreq.securityObjectType);
	int i = this->api->ReqSOPQryContractObjectInfo(&myreq);
	return i;
};

int TdApi::reqFASLUserLogin(dict req)
{
	DFITCSECReqUserLoginField myreq = DFITCSECReqUserLoginField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "password", myreq.password);
	getInt(req, "compressflag", &myreq.compressflag);
	int i = this->api->ReqFASLUserLogin(&myreq);
	return i;
};

int TdApi::reqFASLUserLogout(dict req)
{
	DFITCSECReqUserLogoutField myreq = DFITCSECReqUserLogoutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFASLUserLogout(&myreq);
	return i;
};

int TdApi::reqFASLQryAbleFinInfo(dict req)
{
	DFITCFASLReqAbleFinInfoField myreq = DFITCFASLReqAbleFinInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFASLQryAbleFinInfo(&myreq);
	return i;
};

int TdApi::reqFASLQryAbleSloInfo(dict req)
{
	DFITCFASLReqAbleSloInfoField myreq = DFITCFASLReqAbleSloInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFASLQryAbleSloInfo(&myreq);
	return i;
};

int TdApi::reqFASLTransferCollateral(dict req)
{
	DFITCFASLReqTransferCollateralField myreq = DFITCFASLReqTransferCollateralField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "transferQty", &myreq.transferQty);
	int i = this->api->ReqFASLTransferCollateral(&myreq);
	return i;
};

int TdApi::reqFASLDirectRepayment(dict req)
{
	DFITCFASLReqDirectRepaymentField myreq = DFITCFASLReqDirectRepaymentField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "contractNO", myreq.contractNO);
	getString(req, "contractNO", myreq.contractNO);
	int i = this->api->ReqFASLDirectRepayment(&myreq);
	return i;
};

int TdApi::reqFASLRepayStockTransfer(dict req)
{
	DFITCFASLReqRepayStockTransferField myreq = DFITCFASLReqRepayStockTransferField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "exchangeID", myreq.exchangeID);
	getInt(req, "repayQty", &myreq.repayQty);
	getString(req, "securityID", myreq.securityID);
	getString(req, "contractNO", myreq.contractNO);
	int i = this->api->ReqFASLRepayStockTransfer(&myreq);
	return i;
};

int TdApi::reqFASLEntrustCrdtOrder(dict req)
{
	DFITCFASLReqEntrustCrdtOrderField myreq = DFITCFASLReqEntrustCrdtOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "contractNO", myreq.contractNO);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "orderType", &myreq.orderType);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getInt(req, "entrustQty", &myreq.entrustQty);
	int i = this->api->ReqFASLEntrustCrdtOrder(&myreq);
	return i;
};

int TdApi::reqFASLEntrsuctOrder(dict req)
{
	DFITCFASLReqEntrustOrderField myreq = DFITCFASLReqEntrustOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "orderType", &myreq.orderType);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getInt(req, "entrustQty", &myreq.entrustQty);
	getInt(req, "positionSource", &myreq.positionSource);
	int i = this->api->ReqFASLEntrsuctOrder(&myreq);
	return i;
};

int TdApi::reqFASLWithdrawOrder(dict req)
{
	DFITCFASLReqWithdrawOrderField myreq = DFITCFASLReqWithdrawOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getLong(req, "localOrderID", &myreq.localOrderID);
	int i = this->api->ReqFASLWithdrawOrder(&myreq);
	return i;
};

int TdApi::reqFASLCalcAbleEntrustCrdtQty(dict req)
{
	DFITCFASLReqCalcAbleEntrustCrdtQtyField myreq = DFITCFASLReqCalcAbleEntrustCrdtQtyField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "contractNO", myreq.contractNO);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "orderType", &myreq.orderType);
	getInt(req, "orderType", &myreq.orderType);
	getInt(req, "positionSource", &myreq.positionSource);
	int i = this->api->ReqFASLCalcAbleEntrustCrdtQty(&myreq);
	return i;
};

int TdApi::reqFASLQryCrdtFunds(dict req)
{
	DFITCFASLReqQryCrdtFundsField myreq = DFITCFASLReqQryCrdtFundsField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFASLQryCrdtFunds(&myreq);
	return i;
};

int TdApi::reqFASLQryCrdtContract(dict req)
{
	DFITCFASLReqQryCrdtContractField myreq = DFITCFASLReqQryCrdtContractField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "openBeginDate", &myreq.openBeginDate);
	getInt(req, "openEndDate", &myreq.openEndDate);
	getInt(req, "crdtConQryFlag", &myreq.crdtConQryFlag);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "contractNO", myreq.contractNO);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "conSerialID", &myreq.conSerialID);
	int i = this->api->ReqFASLQryCrdtContract(&myreq);
	return i;
};

int TdApi::reqFASLQryCrdtConChangeInfo(dict req)
{
	DFITCFASLReqQryCrdtConChangeInfoField myreq = DFITCFASLReqQryCrdtConChangeInfoField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "withdrawFlag", myreq.withdrawFlag);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "conSerialNO", &myreq.conSerialNO);
	int i = this->api->ReqFASLQryCrdtConChangeInfo(&myreq);
	return i;
};

int TdApi::reqFASLTransferFunds(dict req)
{
	DFITCStockReqTransferFundsField myreq = DFITCStockReqTransferFundsField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "currency", myreq.currency);
	getString(req, "summaryMsg", myreq.summaryMsg);
	getString(req, "summaryMsg", myreq.summaryMsg);
	getInt(req, "fundsTransFlag", &myreq.fundsTransFlag);
	int i = this->api->ReqFASLTransferFunds(&myreq);
	return i;
};

int TdApi::reqFASLQryAccountInfo(dict req)
{
	DFITCStockReqQryAccountField myreq = DFITCStockReqQryAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFASLQryAccountInfo(&myreq);
	return i;
};

int TdApi::reqFASLQryCapitalAccountInfo(dict req)
{
	DFITCStockReqQryCapitalAccountField myreq = DFITCStockReqQryCapitalAccountField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "FundsQryFlag", &myreq.FundsQryFlag);
	int i = this->api->ReqFASLQryCapitalAccountInfo(&myreq);
	return i;
};

int TdApi::reqFASLQryShareholderInfo(dict req)
{
	DFITCStockReqQryShareholderField myreq = DFITCStockReqQryShareholderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqFASLQryShareholderInfo(&myreq);
	return i;
};

int TdApi::reqFASLQryPosition(dict req)
{
	DFITCStockReqQryPositionField myreq = DFITCStockReqQryPositionField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "posiQryFlag", &myreq.posiQryFlag);
	int i = this->api->ReqFASLQryPosition(&myreq);
	return i;
};

int TdApi::reqFASLQryEntrustOrder(dict req)
{
	DFITCStockReqQryEntrustOrderField myreq = DFITCStockReqQryEntrustOrderField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "entrustQryFlag", &myreq.entrustQryFlag);
	getString(req, "withdrawFlag", myreq.withdrawFlag);
	getString(req, "incQryIndex", myreq.incQryIndex);
	int i = this->api->ReqFASLQryEntrustOrder(&myreq);
	return i;
};

int TdApi::reqFASLQrySerialTrade(dict req)
{
	DFITCStockReqQrySerialTradeField myreq = DFITCStockReqQrySerialTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "tradeQryFlag", &myreq.tradeQryFlag);
	getString(req, "incQryIndex", myreq.incQryIndex);
	int i = this->api->ReqFASLQrySerialTrade(&myreq);
	return i;
};

int TdApi::reqFASLQryRealTimeTrade(dict req)
{
	DFITCStockReqQryRealTimeTradeField myreq = DFITCStockReqQryRealTimeTradeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "entrustBatchID", &myreq.entrustBatchID);
	getInt(req, "entrustDirection", &myreq.entrustDirection);
	getInt(req, "spdOrderID", &myreq.spdOrderID);
	getInt(req, "queryFlag", &myreq.queryFlag);
	int i = this->api->ReqFASLQryRealTimeTrade(&myreq);
	return i;
};

int TdApi::reqFASLQryFreezeFundsDetail(dict req)
{
	DFITCStockReqQryFreezeFundsDetailField myreq = DFITCStockReqQryFreezeFundsDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "currency", myreq.currency);
	getInt(req, "fundsFreezeType", &myreq.fundsFreezeType);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->ReqFASLQryFreezeFundsDetail(&myreq);
	return i;
};

int TdApi::reqFASLQryFreezeStockDetail(dict req)
{
	DFITCStockReqQryFreezeStockDetailField myreq = DFITCStockReqQryFreezeStockDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getInt(req, "stockFreezeType", &myreq.stockFreezeType);
	getString(req, "exchangeID", myreq.exchangeID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->ReqFASLQryFreezeStockDetail(&myreq);
	return i;
};

int TdApi::reqFASLQryTransferFundsDetail(dict req)
{
	DFITCStockReqQryTransferFundsDetailField myreq = DFITCStockReqQryTransferFundsDetailField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "currency", myreq.currency);
	getInt(req, "fundsFreezeType", &myreq.fundsFreezeType);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "serialID", &myreq.serialID);
	int i = this->api->ReqFASLQryTransferFundsDetail(&myreq);
	return i;
};

int TdApi::reqFASLQrySystemTime(dict req)
{
	DFITCFASLReqQryTradeTimeField myreq = DFITCFASLReqQryTradeTimeField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getInt(req, "flag", &myreq.flag);
	int i = this->api->ReqFASLQrySystemTime(&myreq);
	return i;
};

int TdApi::reqFASLQryTransferredContract(dict req)
{
	DFITCFASLReqQryTransferredContractField myreq = DFITCFASLReqQryTransferredContractField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "securityID", myreq.securityID);
	getString(req, "exchangeID", myreq.exchangeID);
	int i = this->api->ReqFASLQryTransferredContract(&myreq);
	return i;
};

int TdApi::reqFASLDesirableFundsOut(dict req)
{
	DFITCFASLReqDesirableFundsOutField myreq = DFITCFASLReqDesirableFundsOutField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	getString(req, "currency", myreq.currency);
	getString(req, "currency", myreq.currency);
	getString(req, "summaryMsg", myreq.summaryMsg);
	int i = this->api->ReqFASLDesirableFundsOut(&myreq);
	return i;
};

int TdApi::reqFASLQryGuaranteedContract(dict req)
{
	DFITCFASLReqQryGuaranteedContractField myreq = DFITCFASLReqQryGuaranteedContractField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFASLQryGuaranteedContract(&myreq);
	return i;
};

int TdApi::reqFASLQryUnderlyingContract(dict req)
{
	DFITCFASLReqQryUnderlyingContractField myreq = DFITCFASLReqQryUnderlyingContractField();
	memset(&myreq, 0, sizeof(myreq));
	getLong(req, "requestID", &myreq.requestID);
	getString(req, "accountID", myreq.accountID);
	int i = this->api->ReqFASLQryUnderlyingContract(&myreq);
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

	virtual void onFrontDisconnected(int reason)
	{
		try
		{
			this->get_override("onFrontDisconnected")(reason);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRtnNotice(dict data)
	{
		try
		{
			this->get_override("onRtnNotice")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspError(dict error)
	{
		try
		{
			this->get_override("onRspError")(error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockUserLogin(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockUserLogin")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockUserLogout(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockUserLogout")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockUserPasswordUpdate(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockUserPasswordUpdate")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockEntrustOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockEntrustOrder")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockWithdrawOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockWithdrawOrder")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQryEntrustOrder(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspStockQryEntrustOrder")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQryRealTimeTrade(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspStockQryRealTimeTrade")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQrySerialTrade(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspStockQrySerialTrade")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQryPosition(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspStockQryPosition")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQryCapitalAccountInfo(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspStockQryCapitalAccountInfo")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQryAccountInfo(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockQryAccountInfo")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQryShareholderInfo(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspStockQryShareholderInfo")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockTransferFunds(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockTransferFunds")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockEntrustBatchOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockEntrustBatchOrder")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockWithdrawBatchOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockWithdrawBatchOrder")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockCalcAbleEntrustQty(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockCalcAbleEntrustQty")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockCalcAblePurchaseETFQty(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockCalcAblePurchaseETFQty")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQryFreezeFundsDetail(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspStockQryFreezeFundsDetail")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQryFreezeStockDetail(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspStockQryFreezeStockDetail")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQryTransferStockDetail(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspStockQryTransferStockDetail")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQryTransferFundsDetail(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspStockQryTransferFundsDetail")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQryStockInfo(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspStockQryStockInfo")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQryStockStaticInfo(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspStockQryStockStaticInfo")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspStockQryTradeTime(dict data, dict error)
	{
		try
		{
			this->get_override("onRspStockQryTradeTime")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onStockEntrustOrderRtn(dict data)
	{
		try
		{
			this->get_override("onStockEntrustOrderRtn")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onStockTradeRtn(dict data)
	{
		try
		{
			this->get_override("onStockTradeRtn")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onStockWithdrawOrderRtn(dict data)
	{
		try
		{
			this->get_override("onStockWithdrawOrderRtn")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPUserLogin(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPUserLogin")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPUserLogout(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPUserLogout")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPUserPasswordUpdate(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPUserPasswordUpdate")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPEntrustOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPEntrustOrder")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPGroupSplit(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPGroupSplit")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryGroupPosition(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPQryGroupPosition")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPLockOUnLockStock(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPLockOUnLockStock")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPWithdrawOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPWithdrawOrder")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryEntrustOrder(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPQryEntrustOrder")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQrySerialTrade(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPQrySerialTrade")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryPosition(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPQryPosition")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryCollateralPosition(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPQryCollateralPosition")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryCapitalAccountInfo(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPQryCapitalAccountInfo")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryAccountInfo(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPQryAccountInfo")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryShareholderInfo(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPQryShareholderInfo")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPCalcAbleEntrustQty(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPCalcAbleEntrustQty")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryAbleLockStock(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPQryAbleLockStock")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryContactInfo(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPQryContactInfo")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPExectueOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRspSOPExectueOrder")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryExecAssiInfo(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPQryExecAssiInfo")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryTradeTime(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPQryTradeTime")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryExchangeInfo(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPQryExchangeInfo")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryCommission(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPQryCommission")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryDeposit(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPQryDeposit")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspSOPQryContractObjectInfo(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspSOPQryContractObjectInfo")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onSOPEntrustOrderRtn(dict data)
	{
		try
		{
			this->get_override("onSOPEntrustOrderRtn")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onSOPTradeRtn(dict data)
	{
		try
		{
			this->get_override("onSOPTradeRtn")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onSOPWithdrawOrderRtn(dict data)
	{
		try
		{
			this->get_override("onSOPWithdrawOrderRtn")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLUserLogin(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLUserLogin")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLUserLogout(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLUserLogout")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryAbleFinInfo(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLQryAbleFinInfo")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryAbleSloInfo(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryAbleSloInfo")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLTransferCollateral(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLTransferCollateral")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLDirectRepayment(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLDirectRepayment")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLRepayStockTransfer(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLRepayStockTransfer")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLEntrustCrdtOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLEntrustCrdtOrder")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLEntrustOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLEntrustOrder")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLCalcAbleEntrustCrdtQty(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLCalcAbleEntrustCrdtQty")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryCrdtFunds(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLQryCrdtFunds")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryCrdtContract(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryCrdtContract")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryCrdtConChangeInfo(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryCrdtConChangeInfo")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLTransferFunds(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLTransferFunds")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryAccountInfo(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLQryAccountInfo")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryCapitalAccountInfo(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryCapitalAccountInfo")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryShareholderInfo(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryShareholderInfo")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryPosition(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryPosition")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryEntrustOrder(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryEntrustOrder")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQrySerialTrade(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQrySerialTrade")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryRealTimeTrade(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryRealTimeTrade")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryFreezeFundsDetail(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryFreezeFundsDetail")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryFreezeStockDetail(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryFreezeStockDetail")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryTransferFundsDetail(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryTransferFundsDetail")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLWithdrawOrder(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLWithdrawOrder")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQrySystemTime(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLQrySystemTime")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryTransferredContract(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryTransferredContract")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLDesirableFundsOut(dict data, dict error)
	{
		try
		{
			this->get_override("onRspFASLDesirableFundsOut")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryGuaranteedContract(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryGuaranteedContract")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onRspFASLQryUnderlyingContract(dict data, dict error, bool flag)
	{
		try
		{
			this->get_override("onRspFASLQryUnderlyingContract")(data, error, flag);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onFASLEntrustOrderRtn(dict data)
	{
		try
		{
			this->get_override("onFASLEntrustOrderRtn")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onFASLTradeRtn(dict data)
	{
		try
		{
			this->get_override("onFASLTradeRtn")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onFASLWithdrawOrderRtn(dict data)
	{
		try
		{
			this->get_override("onFASLWithdrawOrderRtn")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};


};


BOOST_PYTHON_MODULE(vnsectd)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<TdApiWrap, boost::noncopyable>("TdApi")
		.def("createDFITCSECTraderApi", &TdApiWrap::createDFITCSECTraderApi)
		.def("init", &TdApiWrap::init)
		.def("release", &TdApiWrap::release)
		.def("exit", &TdApiWrap::exit)
		.def("subscribePrivateTopic", &TdApiWrap::subscribePrivateTopic)
		.def("reqStockUserLogin", &TdApiWrap::reqStockUserLogin)
		.def("reqStockUserLogout", &TdApiWrap::reqStockUserLogout)
		.def("reqStockUserPasswordUpdate", &TdApiWrap::reqStockUserPasswordUpdate)
		.def("reqStockEntrustOrder", &TdApiWrap::reqStockEntrustOrder)
		.def("reqStockWithdrawOrder", &TdApiWrap::reqStockWithdrawOrder)
		.def("reqStockQryEntrustOrder", &TdApiWrap::reqStockQryEntrustOrder)
		.def("reqStockQryRealTimeTrade", &TdApiWrap::reqStockQryRealTimeTrade)
		.def("reqStockQrySerialTrade", &TdApiWrap::reqStockQrySerialTrade)
		.def("reqStockQryPosition", &TdApiWrap::reqStockQryPosition)
		.def("reqStockQryCapitalAccountInfo", &TdApiWrap::reqStockQryCapitalAccountInfo)
		.def("reqStockQryAccountInfo", &TdApiWrap::reqStockQryAccountInfo)
		.def("reqStockQryShareholderInfo", &TdApiWrap::reqStockQryShareholderInfo)
		.def("reqStockTransferFunds", &TdApiWrap::reqStockTransferFunds)
		.def("reqStockEntrustBatchOrder", &TdApiWrap::reqStockEntrustBatchOrder)
		.def("reqStockWithdrawBatchOrder", &TdApiWrap::reqStockWithdrawBatchOrder)
		.def("reqStockCalcAbleEntrustQty", &TdApiWrap::reqStockCalcAbleEntrustQty)
		.def("reqStockCalcAblePurchaseETFQty", &TdApiWrap::reqStockCalcAblePurchaseETFQty)
		.def("reqStockQryFreezeFundsDetail", &TdApiWrap::reqStockQryFreezeFundsDetail)
		.def("reqStockQryFreezeStockDetail", &TdApiWrap::reqStockQryFreezeStockDetail)
		.def("reqStockQryTransferFundsDetail", &TdApiWrap::reqStockQryTransferFundsDetail)
		.def("reqStockQryTransferStockDetail", &TdApiWrap::reqStockQryTransferStockDetail)
		.def("reqStockQryStockInfo", &TdApiWrap::reqStockQryStockInfo)
		.def("reqStockQryStockStaticInfo", &TdApiWrap::reqStockQryStockStaticInfo)
		.def("reqStockQryTradeTime", &TdApiWrap::reqStockQryTradeTime)
		.def("reqSOPUserLogin", &TdApiWrap::reqSOPUserLogin)
		.def("reqSOPUserLogout", &TdApiWrap::reqSOPUserLogout)
		.def("reqSOPUserPasswordUpdate", &TdApiWrap::reqSOPUserPasswordUpdate)
		.def("reqSOPEntrustOrder", &TdApiWrap::reqSOPEntrustOrder)
		.def("reqSOPGroupSplit", &TdApiWrap::reqSOPGroupSplit)
		.def("reqSOPQryGroupPosition", &TdApiWrap::reqSOPQryGroupPosition)
		.def("reqSOPLockOUnLockStock", &TdApiWrap::reqSOPLockOUnLockStock)
		.def("reqSOPWithdrawOrder", &TdApiWrap::reqSOPWithdrawOrder)
		.def("reqSOPQryEntrustOrder", &TdApiWrap::reqSOPQryEntrustOrder)
		.def("reqSOPQrySerialTrade", &TdApiWrap::reqSOPQrySerialTrade)
		.def("reqSOPQryPosition", &TdApiWrap::reqSOPQryPosition)
		.def("reqSOPQryCollateralPosition", &TdApiWrap::reqSOPQryCollateralPosition)
		.def("reqSOPQryCapitalAccountInfo", &TdApiWrap::reqSOPQryCapitalAccountInfo)
		.def("reqSOPQryAccountInfo", &TdApiWrap::reqSOPQryAccountInfo)
		.def("reqSOPQryShareholderInfo", &TdApiWrap::reqSOPQryShareholderInfo)
		.def("reqSOPCalcAbleEntrustQty", &TdApiWrap::reqSOPCalcAbleEntrustQty)
		.def("reqSOPQryAbleLockStock", &TdApiWrap::reqSOPQryAbleLockStock)
		.def("reqSOPQryContactInfo", &TdApiWrap::reqSOPQryContactInfo)
		.def("reqSOPExectueOrder", &TdApiWrap::reqSOPExectueOrder)
		.def("reqSOPQryExecAssiInfo", &TdApiWrap::reqSOPQryExecAssiInfo)
		.def("reqSOPQryTradeTime", &TdApiWrap::reqSOPQryTradeTime)
		.def("reqSOPQryExchangeInfo", &TdApiWrap::reqSOPQryExchangeInfo)
		.def("reqSOPQryCommission", &TdApiWrap::reqSOPQryCommission)
		.def("reqSOPQryDeposit", &TdApiWrap::reqSOPQryDeposit)
		.def("reqSOPQryContractObjectInfo", &TdApiWrap::reqSOPQryContractObjectInfo)
		.def("reqFASLUserLogin", &TdApiWrap::reqFASLUserLogin)
		.def("reqFASLUserLogout", &TdApiWrap::reqFASLUserLogout)
		.def("reqFASLQryAbleFinInfo", &TdApiWrap::reqFASLQryAbleFinInfo)
		.def("reqFASLQryAbleSloInfo", &TdApiWrap::reqFASLQryAbleSloInfo)
		.def("reqFASLTransferCollateral", &TdApiWrap::reqFASLTransferCollateral)
		.def("reqFASLDirectRepayment", &TdApiWrap::reqFASLDirectRepayment)
		.def("reqFASLRepayStockTransfer", &TdApiWrap::reqFASLRepayStockTransfer)
		.def("reqFASLEntrustCrdtOrder", &TdApiWrap::reqFASLEntrustCrdtOrder)
		.def("reqFASLEntrsuctOrder", &TdApiWrap::reqFASLEntrsuctOrder)
		.def("reqFASLWithdrawOrder", &TdApiWrap::reqFASLWithdrawOrder)
		.def("reqFASLCalcAbleEntrustCrdtQty", &TdApiWrap::reqFASLCalcAbleEntrustCrdtQty)
		.def("reqFASLQryCrdtFunds", &TdApiWrap::reqFASLQryCrdtFunds)
		.def("reqFASLQryCrdtContract", &TdApiWrap::reqFASLQryCrdtContract)
		.def("reqFASLQryCrdtConChangeInfo", &TdApiWrap::reqFASLQryCrdtConChangeInfo)
		.def("reqFASLTransferFunds", &TdApiWrap::reqFASLTransferFunds)
		.def("reqFASLQryAccountInfo", &TdApiWrap::reqFASLQryAccountInfo)
		.def("reqFASLQryCapitalAccountInfo", &TdApiWrap::reqFASLQryCapitalAccountInfo)
		.def("reqFASLQryShareholderInfo", &TdApiWrap::reqFASLQryShareholderInfo)
		.def("reqFASLQryPosition", &TdApiWrap::reqFASLQryPosition)
		.def("reqFASLQryEntrustOrder", &TdApiWrap::reqFASLQryEntrustOrder)
		.def("reqFASLQrySerialTrade", &TdApiWrap::reqFASLQrySerialTrade)
		.def("reqFASLQryRealTimeTrade", &TdApiWrap::reqFASLQryRealTimeTrade)
		.def("reqFASLQryFreezeFundsDetail", &TdApiWrap::reqFASLQryFreezeFundsDetail)
		.def("reqFASLQryFreezeStockDetail", &TdApiWrap::reqFASLQryFreezeStockDetail)
		.def("reqFASLQryTransferFundsDetail", &TdApiWrap::reqFASLQryTransferFundsDetail)
		.def("reqFASLQrySystemTime", &TdApiWrap::reqFASLQrySystemTime)
		.def("reqFASLQryTransferredContract", &TdApiWrap::reqFASLQryTransferredContract)
		.def("reqFASLDesirableFundsOut", &TdApiWrap::reqFASLDesirableFundsOut)
		.def("reqFASLQryGuaranteedContract", &TdApiWrap::reqFASLQryGuaranteedContract)
		.def("reqFASLQryUnderlyingContract", &TdApiWrap::reqFASLQryUnderlyingContract)

		.def("onFrontConnected", pure_virtual(&TdApiWrap::onFrontConnected))
		.def("onFrontDisconnected", pure_virtual(&TdApiWrap::onFrontDisconnected))
		.def("onRtnNotice", pure_virtual(&TdApiWrap::onRtnNotice))
		.def("onRspError", pure_virtual(&TdApiWrap::onRspError))
		.def("onRspStockUserLogin", pure_virtual(&TdApiWrap::onRspStockUserLogin))
		.def("onRspStockUserLogout", pure_virtual(&TdApiWrap::onRspStockUserLogout))
		.def("onRspStockUserPasswordUpdate", pure_virtual(&TdApiWrap::onRspStockUserPasswordUpdate))
		.def("onRspStockEntrustOrder", pure_virtual(&TdApiWrap::onRspStockEntrustOrder))
		.def("onRspStockWithdrawOrder", pure_virtual(&TdApiWrap::onRspStockWithdrawOrder))
		.def("onRspStockQryEntrustOrder", pure_virtual(&TdApiWrap::onRspStockQryEntrustOrder))
		.def("onRspStockQryRealTimeTrade", pure_virtual(&TdApiWrap::onRspStockQryRealTimeTrade))
		.def("onRspStockQrySerialTrade", pure_virtual(&TdApiWrap::onRspStockQrySerialTrade))
		.def("onRspStockQryPosition", pure_virtual(&TdApiWrap::onRspStockQryPosition))
		.def("onRspStockQryCapitalAccountInfo", pure_virtual(&TdApiWrap::onRspStockQryCapitalAccountInfo))
		.def("onRspStockQryAccountInfo", pure_virtual(&TdApiWrap::onRspStockQryAccountInfo))
		.def("onRspStockQryShareholderInfo", pure_virtual(&TdApiWrap::onRspStockQryShareholderInfo))
		.def("onRspStockTransferFunds", pure_virtual(&TdApiWrap::onRspStockTransferFunds))
		.def("onRspStockEntrustBatchOrder", pure_virtual(&TdApiWrap::onRspStockEntrustBatchOrder))
		.def("onRspStockWithdrawBatchOrder", pure_virtual(&TdApiWrap::onRspStockWithdrawBatchOrder))
		.def("onRspStockCalcAbleEntrustQty", pure_virtual(&TdApiWrap::onRspStockCalcAbleEntrustQty))
		.def("onRspStockCalcAblePurchaseETFQty", pure_virtual(&TdApiWrap::onRspStockCalcAblePurchaseETFQty))
		.def("onRspStockQryFreezeFundsDetail", pure_virtual(&TdApiWrap::onRspStockQryFreezeFundsDetail))
		.def("onRspStockQryFreezeStockDetail", pure_virtual(&TdApiWrap::onRspStockQryFreezeStockDetail))
		.def("onRspStockQryTransferStockDetail", pure_virtual(&TdApiWrap::onRspStockQryTransferStockDetail))
		.def("onRspStockQryTransferFundsDetail", pure_virtual(&TdApiWrap::onRspStockQryTransferFundsDetail))
		.def("onRspStockQryStockInfo", pure_virtual(&TdApiWrap::onRspStockQryStockInfo))
		.def("onRspStockQryStockStaticInfo", pure_virtual(&TdApiWrap::onRspStockQryStockStaticInfo))
		.def("onRspStockQryTradeTime", pure_virtual(&TdApiWrap::onRspStockQryTradeTime))
		.def("onStockEntrustOrderRtn", pure_virtual(&TdApiWrap::onStockEntrustOrderRtn))
		.def("onStockTradeRtn", pure_virtual(&TdApiWrap::onStockTradeRtn))
		.def("onStockWithdrawOrderRtn", pure_virtual(&TdApiWrap::onStockWithdrawOrderRtn))
		.def("onRspSOPUserLogin", pure_virtual(&TdApiWrap::onRspSOPUserLogin))
		.def("onRspSOPUserLogout", pure_virtual(&TdApiWrap::onRspSOPUserLogout))
		.def("onRspSOPUserPasswordUpdate", pure_virtual(&TdApiWrap::onRspSOPUserPasswordUpdate))
		.def("onRspSOPEntrustOrder", pure_virtual(&TdApiWrap::onRspSOPEntrustOrder))
		.def("onRspSOPGroupSplit", pure_virtual(&TdApiWrap::onRspSOPGroupSplit))
		.def("onRspSOPQryGroupPosition", pure_virtual(&TdApiWrap::onRspSOPQryGroupPosition))
		.def("onRspSOPLockOUnLockStock", pure_virtual(&TdApiWrap::onRspSOPLockOUnLockStock))
		.def("onRspSOPWithdrawOrder", pure_virtual(&TdApiWrap::onRspSOPWithdrawOrder))
		.def("onRspSOPQryEntrustOrder", pure_virtual(&TdApiWrap::onRspSOPQryEntrustOrder))
		.def("onRspSOPQrySerialTrade", pure_virtual(&TdApiWrap::onRspSOPQrySerialTrade))
		.def("onRspSOPQryPosition", pure_virtual(&TdApiWrap::onRspSOPQryPosition))
		.def("onRspSOPQryCollateralPosition", pure_virtual(&TdApiWrap::onRspSOPQryCollateralPosition))
		.def("onRspSOPQryCapitalAccountInfo", pure_virtual(&TdApiWrap::onRspSOPQryCapitalAccountInfo))
		.def("onRspSOPQryAccountInfo", pure_virtual(&TdApiWrap::onRspSOPQryAccountInfo))
		.def("onRspSOPQryShareholderInfo", pure_virtual(&TdApiWrap::onRspSOPQryShareholderInfo))
		.def("onRspSOPCalcAbleEntrustQty", pure_virtual(&TdApiWrap::onRspSOPCalcAbleEntrustQty))
		.def("onRspSOPQryAbleLockStock", pure_virtual(&TdApiWrap::onRspSOPQryAbleLockStock))
		.def("onRspSOPQryContactInfo", pure_virtual(&TdApiWrap::onRspSOPQryContactInfo))
		.def("onRspSOPExectueOrder", pure_virtual(&TdApiWrap::onRspSOPExectueOrder))
		.def("onRspSOPQryExecAssiInfo", pure_virtual(&TdApiWrap::onRspSOPQryExecAssiInfo))
		.def("onRspSOPQryTradeTime", pure_virtual(&TdApiWrap::onRspSOPQryTradeTime))
		.def("onRspSOPQryExchangeInfo", pure_virtual(&TdApiWrap::onRspSOPQryExchangeInfo))
		.def("onRspSOPQryCommission", pure_virtual(&TdApiWrap::onRspSOPQryCommission))
		.def("onRspSOPQryDeposit", pure_virtual(&TdApiWrap::onRspSOPQryDeposit))
		.def("onRspSOPQryContractObjectInfo", pure_virtual(&TdApiWrap::onRspSOPQryContractObjectInfo))
		.def("onSOPEntrustOrderRtn", pure_virtual(&TdApiWrap::onSOPEntrustOrderRtn))
		.def("onSOPTradeRtn", pure_virtual(&TdApiWrap::onSOPTradeRtn))
		.def("onSOPWithdrawOrderRtn", pure_virtual(&TdApiWrap::onSOPWithdrawOrderRtn))
		.def("onRspFASLUserLogin", pure_virtual(&TdApiWrap::onRspFASLUserLogin))
		.def("onRspFASLUserLogout", pure_virtual(&TdApiWrap::onRspFASLUserLogout))
		.def("onRspFASLQryAbleFinInfo", pure_virtual(&TdApiWrap::onRspFASLQryAbleFinInfo))
		.def("onRspFASLQryAbleSloInfo", pure_virtual(&TdApiWrap::onRspFASLQryAbleSloInfo))
		.def("onRspFASLTransferCollateral", pure_virtual(&TdApiWrap::onRspFASLTransferCollateral))
		.def("onRspFASLDirectRepayment", pure_virtual(&TdApiWrap::onRspFASLDirectRepayment))
		.def("onRspFASLRepayStockTransfer", pure_virtual(&TdApiWrap::onRspFASLRepayStockTransfer))
		.def("onRspFASLEntrustCrdtOrder", pure_virtual(&TdApiWrap::onRspFASLEntrustCrdtOrder))
		.def("onRspFASLEntrustOrder", pure_virtual(&TdApiWrap::onRspFASLEntrustOrder))
		.def("onRspFASLCalcAbleEntrustCrdtQty", pure_virtual(&TdApiWrap::onRspFASLCalcAbleEntrustCrdtQty))
		.def("onRspFASLQryCrdtFunds", pure_virtual(&TdApiWrap::onRspFASLQryCrdtFunds))
		.def("onRspFASLQryCrdtContract", pure_virtual(&TdApiWrap::onRspFASLQryCrdtContract))
		.def("onRspFASLQryCrdtConChangeInfo", pure_virtual(&TdApiWrap::onRspFASLQryCrdtConChangeInfo))
		.def("onRspFASLTransferFunds", pure_virtual(&TdApiWrap::onRspFASLTransferFunds))
		.def("onRspFASLQryAccountInfo", pure_virtual(&TdApiWrap::onRspFASLQryAccountInfo))
		.def("onRspFASLQryCapitalAccountInfo", pure_virtual(&TdApiWrap::onRspFASLQryCapitalAccountInfo))
		.def("onRspFASLQryShareholderInfo", pure_virtual(&TdApiWrap::onRspFASLQryShareholderInfo))
		.def("onRspFASLQryPosition", pure_virtual(&TdApiWrap::onRspFASLQryPosition))
		.def("onRspFASLQryEntrustOrder", pure_virtual(&TdApiWrap::onRspFASLQryEntrustOrder))
		.def("onRspFASLQrySerialTrade", pure_virtual(&TdApiWrap::onRspFASLQrySerialTrade))
		.def("onRspFASLQryRealTimeTrade", pure_virtual(&TdApiWrap::onRspFASLQryRealTimeTrade))
		.def("onRspFASLQryFreezeFundsDetail", pure_virtual(&TdApiWrap::onRspFASLQryFreezeFundsDetail))
		.def("onRspFASLQryFreezeStockDetail", pure_virtual(&TdApiWrap::onRspFASLQryFreezeStockDetail))
		.def("onRspFASLQryTransferFundsDetail", pure_virtual(&TdApiWrap::onRspFASLQryTransferFundsDetail))
		.def("onRspFASLWithdrawOrder", pure_virtual(&TdApiWrap::onRspFASLWithdrawOrder))
		.def("onRspFASLQrySystemTime", pure_virtual(&TdApiWrap::onRspFASLQrySystemTime))
		.def("onRspFASLQryTransferredContract", pure_virtual(&TdApiWrap::onRspFASLQryTransferredContract))
		.def("onRspFASLDesirableFundsOut", pure_virtual(&TdApiWrap::onRspFASLDesirableFundsOut))
		.def("onRspFASLQryGuaranteedContract", pure_virtual(&TdApiWrap::onRspFASLQryGuaranteedContract))
		.def("onRspFASLQryUnderlyingContract", pure_virtual(&TdApiWrap::onRspFASLQryUnderlyingContract))
		.def("onFASLEntrustOrderRtn", pure_virtual(&TdApiWrap::onFASLEntrustOrderRtn))
		.def("onFASLTradeRtn", pure_virtual(&TdApiWrap::onFASLTradeRtn))
		.def("onFASLWithdrawOrderRtn", pure_virtual(&TdApiWrap::onFASLWithdrawOrderRtn))
		;
};