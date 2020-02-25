// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnxtptd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void TdApi::OnDisconnected(int session_id, int reason)
{
	Task task = Task();
	task.task_name = ONDISCONNECTED;
	task.task_int = session_id;
	task.task_int = reason;
	this->task_queue.push(task);
};

void TdApi::OnError(XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONERROR;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void TdApi::OnOrderEvent(XTPOrderInfo *order_info, XTPRI *error_info, int session_id)
{
	Task task = Task();
	task.task_name = ONORDEREVENT;
	if (order_info)
	{
		XTPOrderInfo *task_data = new XTPOrderInfo();
		*task_data = *order_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnTradeEvent(XTPTradeReport *trade_info, int session_id)
{
	Task task = Task();
	task.task_name = ONTRADEEVENT;
	if (trade_info)
	{
		XTPTradeReport *task_data = new XTPTradeReport();
		*task_data = *trade_info;
		task.task_data = task_data;
	}
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnCancelOrderError(XTPOrderCancelInfo *cancel_info, XTPRI *error_info, int session_id)
{
	Task task = Task();
	task.task_name = ONCANCELORDERERROR;
	if (cancel_info)
	{
		XTPOrderCancelInfo *task_data = new XTPOrderCancelInfo();
		*task_data = *cancel_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryOrder(XTPQueryOrderRsp *order_info, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYORDER;
	if (order_info)
	{
		XTPQueryOrderRsp *task_data = new XTPQueryOrderRsp();
		*task_data = *order_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryTrade(XTPQueryTradeRsp *trade_info, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYTRADE;
	if (trade_info)
	{
		XTPQueryTradeRsp *task_data = new XTPQueryTradeRsp();
		*task_data = *trade_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryPosition(XTPQueryStkPositionRsp *position, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYPOSITION;
	if (position)
	{
		XTPQueryStkPositionRsp *task_data = new XTPQueryStkPositionRsp();
		*task_data = *position;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryAsset(XTPQueryAssetRsp *asset, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYASSET;
	if (asset)
	{
		XTPQueryAssetRsp *task_data = new XTPQueryAssetRsp();
		*task_data = *asset;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryStructuredFund(XTPStructuredFundInfo *fund_info, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYSTRUCTUREDFUND;
	if (fund_info)
	{
		XTPStructuredFundInfo *task_data = new XTPStructuredFundInfo();
		*task_data = *fund_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryFundTransfer(XTPFundTransferNotice *fund_transfer_info, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYFUNDTRANSFER;
	if (fund_transfer_info)
	{
		XTPFundTransferNotice *task_data = new XTPFundTransferNotice();
		*task_data = *fund_transfer_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnFundTransfer(XTPFundTransferNotice *fund_transfer_info, XTPRI *error_info, int session_id)
{
	Task task = Task();
	task.task_name = ONFUNDTRANSFER;
	if (fund_transfer_info)
	{
		XTPFundTransferNotice *task_data = new XTPFundTransferNotice();
		*task_data = *fund_transfer_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryETF(XTPQueryETFBaseRsp *etf_info, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYETF;
	if (etf_info)
	{
		XTPQueryETFBaseRsp *task_data = new XTPQueryETFBaseRsp();
		*task_data = *etf_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryETFBasket(XTPQueryETFComponentRsp *etf_component_info, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYETFBASKET;
	if (etf_component_info)
	{
		XTPQueryETFComponentRsp *task_data = new XTPQueryETFComponentRsp();
		*task_data = *etf_component_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryIPOInfoList(XTPQueryIPOTickerRsp *ipo_info, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYIPOINFOLIST;
	if (ipo_info)
	{
		XTPQueryIPOTickerRsp *task_data = new XTPQueryIPOTickerRsp();
		*task_data = *ipo_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryIPOQuotaInfo(XTPQueryIPOQuotaRsp *quota_info, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYIPOQUOTAINFO;
	if (quota_info)
	{
		XTPQueryIPOQuotaRsp *task_data = new XTPQueryIPOQuotaRsp();
		*task_data = *quota_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryOptionAuctionInfo(XTPQueryOptionAuctionInfoRsp *option_info, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYOPTIONAUCTIONINFO;
	if (option_info)
	{
		XTPQueryOptionAuctionInfoRsp *task_data = new XTPQueryOptionAuctionInfoRsp();
		*task_data = *option_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnCreditCashRepay(XTPCrdCashRepayRsp *cash_repay_info, XTPRI *error_info, int session_id)
{
	Task task = Task();
	task.task_name = ONCREDITCASHREPAY;
	if (cash_repay_info)
	{
		XTPCrdCashRepayRsp *task_data = new XTPCrdCashRepayRsp();
		*task_data = *cash_repay_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryCreditCashRepayInfo(XTPCrdCashRepayInfo *cash_repay_info, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYCREDITCASHREPAYINFO;
	if (cash_repay_info)
	{
		XTPCrdCashRepayInfo *task_data = new XTPCrdCashRepayInfo();
		*task_data = *cash_repay_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryCreditFundInfo(XTPCrdFundInfo *fund_info, XTPRI *error_info, int request_id, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYCREDITFUNDINFO;
	if (fund_info)
	{
		XTPCrdFundInfo *task_data = new XTPCrdFundInfo();
		*task_data = *fund_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryCreditDebtInfo(XTPCrdDebtInfo *debt_info, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYCREDITDEBTINFO;
	if (debt_info)
	{
		XTPCrdDebtInfo *task_data = new XTPCrdDebtInfo();
		*task_data = *debt_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryCreditTickerDebtInfo(XTPCrdDebtStockInfo *debt_info, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYCREDITTICKERDEBTINFO;
	if (debt_info)
	{
		XTPCrdDebtStockInfo *task_data = new XTPCrdDebtStockInfo();
		*task_data = *debt_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryCreditAssetDebtInfo(double remain_amount, XTPRI *error_info, int request_id, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYCREDITASSETDEBTINFO;
	if (remain_amount)
	{
		float *task_data = new float();
		*task_data = *remain_amount;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryCreditTickerAssignInfo(XTPClientQueryCrdPositionStkInfo *assign_info, XTPRI *error_info, int request_id, bool is_last, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYCREDITTICKERASSIGNINFO;
	if (assign_info)
	{
		XTPClientQueryCrdPositionStkInfo *task_data = new XTPClientQueryCrdPositionStkInfo();
		*task_data = *assign_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_last = is_last;
	task.task_int = session_id;
	this->task_queue.push(task);
};

void TdApi::OnQueryCreditExcessStock(XTPClientQueryCrdSurplusStkRspInfo* stock_info, XTPRI *error_info, int request_id, int session_id)
{
	Task task = Task();
	task.task_name = ONQUERYCREDITEXCESSSTOCK;
	if (stock_info)
	{
		XTPClientQueryCrdSurplusStkRspInfo *task_data = new XTPClientQueryCrdSurplusStkRspInfo();
		*task_data = *stock_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_id = request_id;
	task.task_int = session_id;
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
			case ONDISCONNECTED:
			{
				this->processDisconnected(&task);
				break;
			}

			case ONERROR:
			{
				this->processError(&task);
				break;
			}

			case ONORDEREVENT:
			{
				this->processOrderEvent(&task);
				break;
			}

			case ONTRADEEVENT:
			{
				this->processTradeEvent(&task);
				break;
			}

			case ONCANCELORDERERROR:
			{
				this->processCancelOrderError(&task);
				break;
			}

			case ONQUERYORDER:
			{
				this->processQueryOrder(&task);
				break;
			}

			case ONQUERYTRADE:
			{
				this->processQueryTrade(&task);
				break;
			}

			case ONQUERYPOSITION:
			{
				this->processQueryPosition(&task);
				break;
			}

			case ONQUERYASSET:
			{
				this->processQueryAsset(&task);
				break;
			}

			case ONQUERYSTRUCTUREDFUND:
			{
				this->processQueryStructuredFund(&task);
				break;
			}

			case ONQUERYFUNDTRANSFER:
			{
				this->processQueryFundTransfer(&task);
				break;
			}

			case ONFUNDTRANSFER:
			{
				this->processFundTransfer(&task);
				break;
			}

			case ONQUERYETF:
			{
				this->processQueryETF(&task);
				break;
			}

			case ONQUERYETFBASKET:
			{
				this->processQueryETFBasket(&task);
				break;
			}

			case ONQUERYIPOINFOLIST:
			{
				this->processQueryIPOInfoList(&task);
				break;
			}

			case ONQUERYIPOQUOTAINFO:
			{
				this->processQueryIPOQuotaInfo(&task);
				break;
			}

			case ONQUERYOPTIONAUCTIONINFO:
			{
				this->processQueryOptionAuctionInfo(&task);
				break;
			}

			case ONCREDITCASHREPAY:
			{
				this->processCreditCashRepay(&task);
				break;
			}

			case ONQUERYCREDITCASHREPAYINFO:
			{
				this->processQueryCreditCashRepayInfo(&task);
				break;
			}

			case ONQUERYCREDITFUNDINFO:
			{
				this->processQueryCreditFundInfo(&task);
				break;
			}

			case ONQUERYCREDITDEBTINFO:
			{
				this->processQueryCreditDebtInfo(&task);
				break;
			}

			case ONQUERYCREDITTICKERDEBTINFO:
			{
				this->processQueryCreditTickerDebtInfo(&task);
				break;
			}

			case ONQUERYCREDITASSETDEBTINFO:
			{
				this->processQueryCreditAssetDebtInfo(&task);
				break;
			}

			case ONQUERYCREDITTICKERASSIGNINFO:
			{
				this->processQueryCreditTickerAssignInfo(&task);
				break;
			}

			case ONQUERYCREDITEXCESSSTOCK:
			{
				this->processQueryCreditExcessStock(&task);
				break;
			}
			};

		}
	}
	catch (const TerminatedError&)
	{
	}
};

void TdApi::processDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onDisconnected(task->task_int, task->task_int);
};

void TdApi::processError(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onError(error);
};

void TdApi::processOrderEvent(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPOrderInfo *task_data = (XTPOrderInfo*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["market"] = task_data->market;
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["price_type"] = task_data->price_type;
		data["side"] = task_data->side;
		data["position_effect"] = task_data->position_effect;
		data["business_type"] = task_data->business_type;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["insert_time"] = task_data->insert_time;
		data["update_time"] = task_data->update_time;
		data["cancel_time"] = task_data->cancel_time;
		data["trade_amount"] = task_data->trade_amount;
		data["order_local_id"] = toUtf(task_data->order_local_id);
		data["order_status"] = task_data->order_status;
		data["order_submit_status"] = task_data->order_submit_status;
		data["order_type"] = toUtf(task_data->order_type);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onOrderEvent(data, error, task->task_int);
};

void TdApi::processTradeEvent(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPTradeReport *task_data = (XTPTradeReport*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["market"] = task_data->market;
		data["local_order_id"] = task_data->local_order_id;
		data["exec_id"] = toUtf(task_data->exec_id);
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["trade_time"] = task_data->trade_time;
		data["trade_amount"] = task_data->trade_amount;
		data["report_index"] = task_data->report_index;
		data["order_exch_id"] = toUtf(task_data->order_exch_id);
		data["trade_type"] = toUtf(task_data->trade_type);
		data["side"] = task_data->side;
		data["position_effect"] = task_data->position_effect;
		data["business_type"] = task_data->business_type;
		data["branch_pbu"] = toUtf(task_data->branch_pbu);
		delete task_data;
	}
	this->onTradeEvent(data, task->task_int);
};

void TdApi::processCancelOrderError(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPOrderCancelInfo *task_data = (XTPOrderCancelInfo*)task->task_data;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["order_xtp_id"] = task_data->order_xtp_id;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onCancelOrderError(data, error, task->task_int);
};

void TdApi::processQueryOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryOrderRsp *task_data = (XTPQueryOrderRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["market"] = task_data->market;
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["price_type"] = task_data->price_type;
		data["side"] = task_data->side;
		data["position_effect"] = task_data->position_effect;
		data["business_type"] = task_data->business_type;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["insert_time"] = task_data->insert_time;
		data["update_time"] = task_data->update_time;
		data["cancel_time"] = task_data->cancel_time;
		data["trade_amount"] = task_data->trade_amount;
		data["order_local_id"] = toUtf(task_data->order_local_id);
		data["order_status"] = task_data->order_status;
		data["order_submit_status"] = task_data->order_submit_status;
		data["order_type"] = toUtf(task_data->order_type);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryOrder(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processQueryTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryTradeRsp *task_data = (XTPQueryTradeRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["market"] = task_data->market;
		data["local_order_id"] = task_data->local_order_id;
		data["exec_id"] = toUtf(task_data->exec_id);
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["trade_time"] = task_data->trade_time;
		data["trade_amount"] = task_data->trade_amount;
		data["report_index"] = task_data->report_index;
		data["order_exch_id"] = toUtf(task_data->order_exch_id);
		data["trade_type"] = toUtf(task_data->trade_type);
		data["side"] = task_data->side;
		data["position_effect"] = task_data->position_effect;
		data["business_type"] = task_data->business_type;
		data["branch_pbu"] = toUtf(task_data->branch_pbu);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryTrade(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processQueryPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryStkPositionRsp *task_data = (XTPQueryStkPositionRsp*)task->task_data;
		data["ticker"] = toUtf(task_data->ticker);
		data["ticker_name"] = toUtf(task_data->ticker_name);
		data["market"] = task_data->market;
		data["total_qty"] = task_data->total_qty;
		data["sellable_qty"] = task_data->sellable_qty;
		data["avg_price"] = task_data->avg_price;
		data["unrealized_pnl"] = task_data->unrealized_pnl;
		data["yesterday_position"] = task_data->yesterday_position;
		data["purchase_redeemable_qty"] = task_data->purchase_redeemable_qty;
		data["position_direction"] = task_data->position_direction;
		data["reserved1"] = task_data->reserved1;
		data["executable_option"] = task_data->executable_option;
		data["lockable_position"] = task_data->lockable_position;
		data["executable_underlying"] = task_data->executable_underlying;
		data["locked_position"] = task_data->locked_position;
		data["usable_locked_position"] = task_data->usable_locked_position;
		data["unknown"] = task_data->unknown;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryPosition(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processQueryAsset(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryAssetRsp *task_data = (XTPQueryAssetRsp*)task->task_data;
		data["total_asset"] = task_data->total_asset;
		data["buying_power"] = task_data->buying_power;
		data["security_asset"] = task_data->security_asset;
		data["fund_buy_amount"] = task_data->fund_buy_amount;
		data["fund_buy_fee"] = task_data->fund_buy_fee;
		data["fund_sell_amount"] = task_data->fund_sell_amount;
		data["fund_sell_fee"] = task_data->fund_sell_fee;
		data["withholding_amount"] = task_data->withholding_amount;
		data["account_type"] = task_data->account_type;
		data["frozen_margin"] = task_data->frozen_margin;
		data["frozen_exec_cash"] = task_data->frozen_exec_cash;
		data["frozen_exec_fee"] = task_data->frozen_exec_fee;
		data["pay_later"] = task_data->pay_later;
		data["preadva_pay"] = task_data->preadva_pay;
		data["orig_banlance"] = task_data->orig_banlance;
		data["banlance"] = task_data->banlance;
		data["deposit_withdraw"] = task_data->deposit_withdraw;
		data["trade_netting"] = task_data->trade_netting;
		data["captial_asset"] = task_data->captial_asset;
		data["force_freeze_amount"] = task_data->force_freeze_amount;
		data["preferred_amount"] = task_data->preferred_amount;
		data["repay_stock_aval_banlance"] = task_data->repay_stock_aval_banlance;
		data["unknown"] = task_data->unknown;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryAsset(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processQueryStructuredFund(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPStructuredFundInfo *task_data = (XTPStructuredFundInfo*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["sf_ticker"] = toUtf(task_data->sf_ticker);
		data["sf_ticker_name"] = toUtf(task_data->sf_ticker_name);
		data["ticker"] = toUtf(task_data->ticker);
		data["ticker_name"] = toUtf(task_data->ticker_name);
		data["split_merge_status"] = task_data->split_merge_status;
		data["ratio"] = task_data->ratio;
		data["min_split_qty"] = task_data->min_split_qty;
		data["min_merge_qty"] = task_data->min_merge_qty;
		data["net_price"] = task_data->net_price;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryStructuredFund(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processQueryFundTransfer(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPFundTransferNotice *task_data = (XTPFundTransferNotice*)task->task_data;
		data["serial_id"] = task_data->serial_id;
		data["transfer_type"] = task_data->transfer_type;
		data["amount"] = task_data->amount;
		data["oper_status"] = task_data->oper_status;
		data["transfer_time"] = task_data->transfer_time;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryFundTransfer(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processFundTransfer(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPFundTransferNotice *task_data = (XTPFundTransferNotice*)task->task_data;
		data["serial_id"] = task_data->serial_id;
		data["transfer_type"] = task_data->transfer_type;
		data["amount"] = task_data->amount;
		data["oper_status"] = task_data->oper_status;
		data["transfer_time"] = task_data->transfer_time;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onFundTransfer(data, error, task->task_int);
};

void TdApi::processQueryETF(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryETFBaseRsp *task_data = (XTPQueryETFBaseRsp*)task->task_data;
		data["market"] = task_data->market;
		data["etf"] = toUtf(task_data->etf);
		data["subscribe_redemption_ticker"] = toUtf(task_data->subscribe_redemption_ticker);
		data["unit"] = task_data->unit;
		data["subscribe_status"] = task_data->subscribe_status;
		data["redemption_status"] = task_data->redemption_status;
		data["max_cash_ratio"] = task_data->max_cash_ratio;
		data["estimate_amount"] = task_data->estimate_amount;
		data["cash_component"] = task_data->cash_component;
		data["net_value"] = task_data->net_value;
		data["total_amount"] = task_data->total_amount;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryETF(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processQueryETFBasket(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryETFComponentRsp *task_data = (XTPQueryETFComponentRsp*)task->task_data;
		data["market"] = task_data->market;
		data["ticker"] = toUtf(task_data->ticker);
		data["component_ticker"] = toUtf(task_data->component_ticker);
		data["component_name"] = toUtf(task_data->component_name);
		data["quantity"] = task_data->quantity;
		data["component_market"] = task_data->component_market;
		data["replace_type"] = task_data->replace_type;
		data["premium_ratio"] = task_data->premium_ratio;
		data["amount"] = task_data->amount;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryETFBasket(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processQueryIPOInfoList(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryIPOTickerRsp *task_data = (XTPQueryIPOTickerRsp*)task->task_data;
		data["market"] = task_data->market;
		data["ticker"] = toUtf(task_data->ticker);
		data["ticker_name"] = toUtf(task_data->ticker_name);
		data["price"] = task_data->price;
		data["unit"] = task_data->unit;
		data["qty_upper_limit"] = task_data->qty_upper_limit;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryIPOInfoList(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processQueryIPOQuotaInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryIPOQuotaRsp *task_data = (XTPQueryIPOQuotaRsp*)task->task_data;
		data["market"] = task_data->market;
		data["quantity"] = task_data->quantity;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryIPOQuotaInfo(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processQueryOptionAuctionInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryOptionAuctionInfoRsp *task_data = (XTPQueryOptionAuctionInfoRsp*)task->task_data;
		data["ticker"] = toUtf(task_data->ticker);
		data["security_id_source"] = task_data->security_id_source;
		data["symbol"] = toUtf(task_data->symbol);
		data["contract_id"] = toUtf(task_data->contract_id);
		data["underlying_security_id"] = toUtf(task_data->underlying_security_id);
		data["underlying_security_id_source"] = task_data->underlying_security_id_source;
		data["list_date"] = task_data->list_date;
		data["last_trade_date"] = task_data->last_trade_date;
		data["ticker_type"] = task_data->ticker_type;
		data["day_trading"] = task_data->day_trading;
		data["call_or_put"] = task_data->call_or_put;
		data["delivery_day"] = task_data->delivery_day;
		data["delivery_month"] = task_data->delivery_month;
		data["exercise_type"] = task_data->exercise_type;
		data["exercise_begin_date"] = task_data->exercise_begin_date;
		data["exercise_end_date"] = task_data->exercise_end_date;
		data["exercise_price"] = task_data->exercise_price;
		data["qty_unit"] = task_data->qty_unit;
		data["contract_unit"] = task_data->contract_unit;
		data["contract_position"] = task_data->contract_position;
		data["prev_close_price"] = task_data->prev_close_price;
		data["prev_clearing_price"] = task_data->prev_clearing_price;
		data["lmt_buy_max_qty"] = task_data->lmt_buy_max_qty;
		data["lmt_buy_min_qty"] = task_data->lmt_buy_min_qty;
		data["lmt_sell_max_qty"] = task_data->lmt_sell_max_qty;
		data["lmt_sell_min_qty"] = task_data->lmt_sell_min_qty;
		data["mkt_buy_max_qty"] = task_data->mkt_buy_max_qty;
		data["mkt_buy_min_qty"] = task_data->mkt_buy_min_qty;
		data["mkt_sell_max_qty"] = task_data->mkt_sell_max_qty;
		data["mkt_sell_min_qty"] = task_data->mkt_sell_min_qty;
		data["price_tick"] = task_data->price_tick;
		data["upper_limit_price"] = task_data->upper_limit_price;
		data["lower_limit_price"] = task_data->lower_limit_price;
		data["sell_margin"] = task_data->sell_margin;
		data["margin_ratio_param1"] = task_data->margin_ratio_param1;
		data["margin_ratio_param2"] = task_data->margin_ratio_param2;
		data["unknown"] = task_data->unknown;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryOptionAuctionInfo(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processCreditCashRepay(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPCrdCashRepayRsp *task_data = (XTPCrdCashRepayRsp*)task->task_data;
		data["xtp_id"] = task_data->xtp_id;
		data["request_amount"] = task_data->request_amount;
		data["cash_repay_amount"] = task_data->cash_repay_amount;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onCreditCashRepay(data, error, task->task_int);
};

void TdApi::processQueryCreditCashRepayInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPCrdCashRepayInfo *task_data = (XTPCrdCashRepayInfo*)task->task_data;
		data["xtp_id"] = task_data->xtp_id;
		data["status"] = task_data->status;
		data["request_amount"] = task_data->request_amount;
		data["cash_repay_amount"] = task_data->cash_repay_amount;
		data["position_effect"] = task_data->position_effect;
		data["error_info"] = task_data->error_info;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditCashRepayInfo(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processQueryCreditFundInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPCrdFundInfo *task_data = (XTPCrdFundInfo*)task->task_data;
		data["maintenance_ratio"] = task_data->maintenance_ratio;
		data["all_asset"] = task_data->all_asset;
		data["all_debt"] = task_data->all_debt;
		data["line_of_credit"] = task_data->line_of_credit;
		data["guaranty"] = task_data->guaranty;
		data["position_amount"] = task_data->position_amount;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditFundInfo(data, error, task->task_id, task->task_int);
};

void TdApi::processQueryCreditDebtInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPCrdDebtInfo *task_data = (XTPCrdDebtInfo*)task->task_data;
		data["debt_type"] = task_data->debt_type;
		data["debt_id"] = toUtf(task_data->debt_id);
		data["position_id"] = task_data->position_id;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["debt_status"] = task_data->debt_status;
		data["market"] = task_data->market;
		data["ticker"] = toUtf(task_data->ticker);
		data["order_date"] = task_data->order_date;
		data["end_date"] = task_data->end_date;
		data["orig_end_date"] = task_data->orig_end_date;
		data["is_extended"] = task_data->is_extended;
		data["remain_amt"] = task_data->remain_amt;
		data["remain_qty"] = task_data->remain_qty;
		data["remain_principal"] = task_data->remain_principal;
		data["due_right_qty"] = task_data->due_right_qty;
		data["unknown"] = task_data->unknown;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditDebtInfo(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processQueryCreditTickerDebtInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPCrdDebtStockInfo *task_data = (XTPCrdDebtStockInfo*)task->task_data;
		data["market"] = task_data->market;
		data["ticker"] = toUtf(task_data->ticker);
		data["remain_quantity"] = task_data->remain_quantity;
		data["order_withhold_quantity"] = task_data->order_withhold_quantity;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditTickerDebtInfo(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processQueryCreditAssetDebtInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditAssetDebtInfo(task->task_float, error, task->task_id, task->task_int);
};

void TdApi::processQueryCreditTickerAssignInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPClientQueryCrdPositionStkInfo *task_data = (XTPClientQueryCrdPositionStkInfo*)task->task_data;
		data["market"] = task_data->market;
		data["ticker"] = toUtf(task_data->ticker);
		data["limit_qty"] = task_data->limit_qty;
		data["yesterday_qty"] = task_data->yesterday_qty;
		data["left_qty"] = task_data->left_qty;
		data["frozen_qty"] = task_data->frozen_qty;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditTickerAssignInfo(data, error, task->task_id, task->task_last, task->task_int);
};

void TdApi::processQueryCreditExcessStock(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPClientQueryCrdSurplusStkRspInfo *task_data = (XTPClientQueryCrdSurplusStkRspInfo*)task->task_data;
		data["market"] = task_data->market;
		data["ticker"] = toUtf(task_data->ticker);
		data["transferable_quantity"] = task_data->transferable_quantity;
		data["transferred_quantity"] = task_data->transferred_quantity;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditExcessStock(data, error, task->task_id, task->task_int);
};




///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::createFtdcTraderApi(string pszFlowPath)
{
	this->api = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};

void TdApi::release()
{
	this->api->Release();
};

void TdApi::init()
{
	this->active = true;
	this->task_thread = thread(&TdApi::processTask, this);

	this->api->Init();
};

int TdApi::join()
{
	int i = this->api->Join();
	return i;
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
	this->api->SubscribePrivateTopic((THOST_TE_RESUME_TYPE)nType);
};

void TdApi::subscribePublicTopic(int nType)
{
	this->api->SubscribePublicTopic((THOST_TE_RESUME_TYPE)nType);
};

int TdApi::queryOrderByXTPID(const dict &req, int session_id, int request_id)
{
	const myreq = const();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryOrderByXTPID(&myreq, reqid);
	return i;
};

int TdApi::queryOrders(const dict &req, int session_id, int request_id)
{
	const myreq = const();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryOrders(&myreq, reqid);
	return i;
};

int TdApi::queryTradesByXTPID(const dict &req, int session_id, int request_id)
{
	const myreq = const();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryTradesByXTPID(&myreq, reqid);
	return i;
};

int TdApi::queryTrades(const dict &req, int session_id, int request_id)
{
	XTPQueryTraderReq myreq = XTPQueryTraderReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ticker", myreq.ticker);
	getInt(req, "begin_time", &myreq.begin_time);
	getInt(req, "end_time", &myreq.end_time);
	int i = this->api->QueryTrades(&myreq, reqid);
	return i;
};

int TdApi::queryPosition(const dict &req, int session_id, int request_id)
{
	const myreq = const();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryPosition(&myreq, reqid);
	return i;
};

int TdApi::queryAsset(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryAsset(&myreq, reqid);
	return i;
};

int TdApi::queryStructuredFund(const dict &req, int session_id, int request_id)
{
	XTPQueryStructuredFundInfoReq myreq = XTPQueryStructuredFundInfoReq();
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "exchange_id", &myreq.exchange_id);
	getString(req, "sf_ticker", myreq.sf_ticker);
	int i = this->api->QueryStructuredFund(&myreq, reqid);
	return i;
};

int TdApi::queryFundTransfer(const dict &req, int session_id, int request_id)
{
	XTPQueryFundTransferLogReq myreq = XTPQueryFundTransferLogReq();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "serial_id", &myreq.serial_id);
	int i = this->api->QueryFundTransfer(&myreq, reqid);
	return i;
};

int TdApi::queryETF(const dict &req, int session_id, int request_id)
{
	XTPQueryETFBaseReq myreq = XTPQueryETFBaseReq();
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryETF(&myreq, reqid);
	return i;
};

int TdApi::queryETFTickerBasket(const dict &req, int session_id, int request_id)
{
	XTPQueryETFComponentReq myreq = XTPQueryETFComponentReq();
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryETFTickerBasket(&myreq, reqid);
	return i;
};

int TdApi::queryIPOInfoList(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryIPOInfoList(&myreq, reqid);
	return i;
};

int TdApi::queryIPOQuotaInfo(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryIPOQuotaInfo(&myreq, reqid);
	return i;
};

int TdApi::queryOptionAuctionInfo(const dict &req, int session_id, int request_id)
{
	XTPQueryOptionAuctionInfoReq myreq = XTPQueryOptionAuctionInfoReq();
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryOptionAuctionInfo(&myreq, reqid);
	return i;
};

int TdApi::queryCreditCashRepayInfo(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryCreditCashRepayInfo(&myreq, reqid);
	return i;
};

int TdApi::queryCreditFundInfo(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryCreditFundInfo(&myreq, reqid);
	return i;
};

int TdApi::queryCreditDebtInfo(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryCreditDebtInfo(&myreq, reqid);
	return i;
};

int TdApi::queryCreditTickerDebtInfo(const dict &req, int session_id, int request_id)
{
	XTPClientQueryCrdDebtStockReq myreq = XTPClientQueryCrdDebtStockReq();
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditTickerDebtInfo(&myreq, reqid);
	return i;
};

int TdApi::queryCreditAssetDebtInfo(int session_id, int request_id)
{
	int myreq = int();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryCreditAssetDebtInfo(&myreq, reqid);
	return i;
};

int TdApi::queryCreditTickerAssignInfo(const dict &req, int session_id, int request_id)
{
	XTPClientQueryCrdPositionStockReq myreq = XTPClientQueryCrdPositionStockReq();
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditTickerAssignInfo(&myreq, reqid);
	return i;
};

int TdApi::queryCreditExcessStock(const dict &req, int session_id, int request_id)
{
	XTPClientQueryCrdSurplusStkReqInfo myreq = XTPClientQueryCrdSurplusStkReqInfo();
	memset(&myreq, 0, sizeof(myreq));
	getEnum(req, "market", &myreq.market);
	getString(req, "ticker", myreq.ticker);
	int i = this->api->QueryCreditExcessStock(&myreq, reqid);
	return i;
};




///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyTdApi : public TdApi
{
public:
	using TdApi::TdApi;

	void onDisconnected(int reqid, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onDisconnected, reqid, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onError(const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onError, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onOrderEvent(const dict &data, const dict &error, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onOrderEvent, data, error, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onTradeEvent(const dict &data, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onTradeEvent, data, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onCancelOrderError(const dict &data, const dict &error, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCancelOrderError, data, error, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOrder(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOrder, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryTrade(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryTrade, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryPosition(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryPosition, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryAsset(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryAsset, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryStructuredFund(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryStructuredFund, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryFundTransfer(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryFundTransfer, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onFundTransfer(const dict &data, const dict &error, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onFundTransfer, data, error, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryETF(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryETF, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryETFBasket(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryETFBasket, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryIPOInfoList(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryIPOInfoList, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryIPOQuotaInfo(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryIPOQuotaInfo, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOptionAuctionInfo(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOptionAuctionInfo, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onCreditCashRepay(const dict &data, const dict &error, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCreditCashRepay, data, error, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditCashRepayInfo(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditCashRepayInfo, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditFundInfo(const dict &data, const dict &error, int reqid, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditFundInfo, data, error, reqid, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditDebtInfo(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditDebtInfo, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditTickerDebtInfo(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditTickerDebtInfo, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditAssetDebtInfo(const dict &data, const dict &error, int reqid, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditAssetDebtInfo, data, error, reqid, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditTickerAssignInfo(const dict &data, const dict &error, int reqid, bool last, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditTickerAssignInfo, data, error, reqid, last, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditExcessStock(const dict &data, const dict &error, int reqid, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditExcessStock, data, error, reqid, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};




};


PYBIND11_MODULE(vnctptd, m)
{
	class_<TdApi, PyTdApi> TdApi(m, "TdApi", module_local());
	TdApi
		.def(init<>())
		.def("createFtdcTraderApi", &TdApi::createFtdcTraderApi)
		.def("release", &TdApi::release)
		.def("init", &TdApi::init)
		.def("join", &TdApi::join)
		.def("exit", &TdApi::exit)
		.def("getTradingDay", &TdApi::getTradingDay)
		.def("registerFront", &TdApi::registerFront)
		.def("subscribePublicTopic", &TdApi::subscribePublicTopic)
		.def("subscribePrivateTopic", &TdApi::subscribePrivateTopic)

		.def("queryOrderByXTPID", &TdApi::queryOrderByXTPID)
		.def("queryOrders", &TdApi::queryOrders)
		.def("queryTradesByXTPID", &TdApi::queryTradesByXTPID)
		.def("queryTrades", &TdApi::queryTrades)
		.def("queryPosition", &TdApi::queryPosition)
		.def("queryAsset", &TdApi::queryAsset)
		.def("queryStructuredFund", &TdApi::queryStructuredFund)
		.def("queryFundTransfer", &TdApi::queryFundTransfer)
		.def("queryETF", &TdApi::queryETF)
		.def("queryETFTickerBasket", &TdApi::queryETFTickerBasket)
		.def("queryIPOInfoList", &TdApi::queryIPOInfoList)
		.def("queryIPOQuotaInfo", &TdApi::queryIPOQuotaInfo)
		.def("queryOptionAuctionInfo", &TdApi::queryOptionAuctionInfo)
		.def("queryCreditCashRepayInfo", &TdApi::queryCreditCashRepayInfo)
		.def("queryCreditFundInfo", &TdApi::queryCreditFundInfo)
		.def("queryCreditDebtInfo", &TdApi::queryCreditDebtInfo)
		.def("queryCreditTickerDebtInfo", &TdApi::queryCreditTickerDebtInfo)
		.def("queryCreditAssetDebtInfo", &TdApi::queryCreditAssetDebtInfo)
		.def("queryCreditTickerAssignInfo", &TdApi::queryCreditTickerAssignInfo)
		.def("queryCreditExcessStock", &TdApi::queryCreditExcessStock)

		.def("onDisconnected", &TdApi::onDisconnected)
		.def("onError", &TdApi::onError)
		.def("onOrderEvent", &TdApi::onOrderEvent)
		.def("onTradeEvent", &TdApi::onTradeEvent)
		.def("onCancelOrderError", &TdApi::onCancelOrderError)
		.def("onQueryOrder", &TdApi::onQueryOrder)
		.def("onQueryTrade", &TdApi::onQueryTrade)
		.def("onQueryPosition", &TdApi::onQueryPosition)
		.def("onQueryAsset", &TdApi::onQueryAsset)
		.def("onQueryStructuredFund", &TdApi::onQueryStructuredFund)
		.def("onQueryFundTransfer", &TdApi::onQueryFundTransfer)
		.def("onFundTransfer", &TdApi::onFundTransfer)
		.def("onQueryETF", &TdApi::onQueryETF)
		.def("onQueryETFBasket", &TdApi::onQueryETFBasket)
		.def("onQueryIPOInfoList", &TdApi::onQueryIPOInfoList)
		.def("onQueryIPOQuotaInfo", &TdApi::onQueryIPOQuotaInfo)
		.def("onQueryOptionAuctionInfo", &TdApi::onQueryOptionAuctionInfo)
		.def("onCreditCashRepay", &TdApi::onCreditCashRepay)
		.def("onQueryCreditCashRepayInfo", &TdApi::onQueryCreditCashRepayInfo)
		.def("onQueryCreditFundInfo", &TdApi::onQueryCreditFundInfo)
		.def("onQueryCreditDebtInfo", &TdApi::onQueryCreditDebtInfo)
		.def("onQueryCreditTickerDebtInfo", &TdApi::onQueryCreditTickerDebtInfo)
		.def("onQueryCreditAssetDebtInfo", &TdApi::onQueryCreditAssetDebtInfo)
		.def("onQueryCreditTickerAssignInfo", &TdApi::onQueryCreditTickerAssignInfo)
		.def("onQueryCreditExcessStock", &TdApi::onQueryCreditExcessStock)
		;

}


