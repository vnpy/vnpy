// vnctpmd.cpp 
//
#include "stdafx.h"
#include "vnxtptrader.h"
 
///-------------------------------------------------------------------------------------
///
///-------------------------------------------------------------------------------------

void getInt(dict d, string key, int *value)
{
	if (d.has_key(key))		
	{
		object o = d[key];	
		extract<int> x(o);	
		if (x.check())		
		{
			*value = x();	
		}
	}
};

void getUint64(dict d, string key, uint64_t *value)
{
	if (d.has_key(key))		
	{
		object o = d[key];	
		extract<int> x(o);	
		if (x.check())		
		{
			*value = x();	
		}
	}
};

void getUint32(dict d, string key, uint32_t *value)
{
	if (d.has_key(key))		
	{
		object o = d[key];	
		extract<int> x(o);	
		if (x.check())		
		{
			*value = x();	
		}
	}
};

void getInt64(dict d, string key, int64_t *value)
{
	if (d.has_key(key))		
	{
		object o = d[key];	
		extract<int> x(o);	
		if (x.check())		
		{
			*value = x();	
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

void getStr(dict d, string key, char *value)
{
	if (d.has_key(key))
	{
		object o = d[key];
		extract<string> x(o);
		if (x.check())
		{
			string s = x();
			const char *buffer = s.c_str();
			
#ifdef _MSC_VER //WIN32
			strcpy_s(value, strlen(buffer) + 1, buffer);
#elif __GNUC__
			strncpy(value, buffer, strlen(buffer) + 1);
#endif
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


///-------------------------------------------------------------------------------------
///
///-------------------------------------------------------------------------------------

void TraderApi::OnDisconnected(uint64_t session_id, int reason)
{
	Task* task = new Task();
	task->task_name = ONDISCONNECTED;
	task->addtional_int = session_id;	
	task->task_id = reason;
	this->task_queue.push(task);
};

void TraderApi::OnError(XTPRI *error_info)
{
	Task* task = new Task();
	task->task_name = ONERROR;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void TraderApi::OnOrderEvent(XTPOrderInfo *order_info, XTPRI *error_info, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONORDEREVENT;

	if (order_info)
	{
		XTPOrderInfo *task_data = new XTPOrderInfo();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;

	this->task_queue.push(task);
};

void TraderApi::OnTradeEvent(XTPTradeReport *trade_info, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONTRADEEVENT;

	if (trade_info)
	{
		XTPTradeReport *task_data = new XTPTradeReport();
		*task_data = *trade_info;
		task->task_data = task_data;
	}

	task->addtional_int = session_id;

	this->task_queue.push(task);
};

void TraderApi::OnCancelOrderError(XTPOrderCancelInfo *cancel_info, XTPRI *error_info, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONCANCELORDERERROR;

	if (cancel_info)
	{
		XTPOrderCancelInfo *task_data = new XTPOrderCancelInfo();
		*task_data = *cancel_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
		
	this->task_queue.push(task);
};

void TraderApi::OnQueryOrder(XTPQueryOrderRsp *order_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYORDER;

	if (order_info)
	{
		XTPQueryOrderRsp *task_data = new XTPQueryOrderRsp();
		*task_data = *order_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryTrade(XTPQueryTradeRsp *trade_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYTRADE;

	if (trade_info)
	{
		XTPQueryTradeRsp *task_data = new XTPQueryTradeRsp();
		*task_data = *trade_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryPosition(XTPQueryStkPositionRsp *position, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYPOSITION;

	if (position)
	{
		XTPQueryStkPositionRsp *task_data = new XTPQueryStkPositionRsp();
		*task_data = *position;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryAsset(XTPQueryAssetRsp *asset, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYASSET;

	if (asset)
	{
		XTPQueryAssetRsp *task_data = new XTPQueryAssetRsp();
		*task_data = *asset;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryStructuredFund(XTPStructuredFundInfo *fund_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYSTRUCTUREDFUND;

	if (fund_info)
	{
		XTPStructuredFundInfo *task_data = new XTPStructuredFundInfo();
		*task_data = *fund_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryFundTransfer(XTPFundTransferNotice *fund_transfer_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYFUNDTRANSFER;

	if (fund_transfer_info)
	{
		XTPFundTransferNotice *task_data = new XTPFundTransferNotice();
		*task_data = *fund_transfer_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnFundTransfer(XTPFundTransferNotice *fund_transfer_info, XTPRI *error_info, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONFUNDTRANSFER;

	if (fund_transfer_info)
	{
		XTPFundTransferNotice *task_data = new XTPFundTransferNotice();
		*task_data = *fund_transfer_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryETF(XTPQueryETFBaseRsp *etf_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYETF;

	if (etf_info)
	{
		XTPQueryETFBaseRsp *task_data = new XTPQueryETFBaseRsp();
		*task_data = *etf_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryETFBasket(XTPQueryETFComponentRsp *etf_component_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYETFBASKET;

	if (etf_component_info)
	{
		XTPQueryETFComponentRsp *task_data = new XTPQueryETFComponentRsp();
		*task_data = *etf_component_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryIPOInfoList(XTPQueryIPOTickerRsp *ipo_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYIPOINFOLIST;

	if (ipo_info)
	{
		XTPQueryIPOTickerRsp *task_data = new XTPQueryIPOTickerRsp();
		*task_data = *ipo_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};

void TraderApi::OnQueryIPOQuotaInfo(XTPQueryIPOQuotaRsp *quota_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYIPOQUOTAINFO;

	if (quota_info)
	{
		XTPQueryIPOQuotaRsp *task_data = new XTPQueryIPOQuotaRsp();
		*task_data = *quota_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
};


void TraderApi::OnQueryOptionAuctionInfo(XTPQueryOptionAuctionInfoRsp *option_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
{
	Task* task = new Task();
	task->task_name = ONQUERYOPTIONAUCTIONINFO;

	if (option_info)
	{
		XTPQueryOptionAuctionInfoRsp *task_data = new XTPQueryOptionAuctionInfoRsp();
		*task_data = *option_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_id = request_id;
	task->task_last = is_last;
	task->addtional_int = session_id;
	this->task_queue.push(task);
}
///-------------------------------------------------------------------------------------
///�����̴߳Ӷ�����ȡ�����ݣ�ת��Ϊpython����󣬽�������
///-------------------------------------------------------------------------------------

void TraderApi::processTask()
{
	while (1)
	{
		Task* task = this->task_queue.wait_and_pop();

		switch (task->task_name)
		{
			case ONDISCONNECTED:
			{
				this->processDisconnected(task);
				break;
			}

			case ONERROR:
			{
				this->processError(task);
				break;
			}

			case ONORDEREVENT:
			{
				this->processOrderEvent(task);
				break;
			}

			case ONTRADEEVENT:
			{
				this->processTradeEvent(task);
				break;
			}

			case ONCANCELORDERERROR:
			{
				this->processCancelOrderError(task);
				break;
			}

			case ONQUERYORDER:
			{
				this->processQueryOrder(task);
				break;
			}

			case ONQUERYTRADE:
			{
				this->processQueryTrade(task);
				break;
			}

			case ONQUERYPOSITION:
			{
				this->processQueryPosition(task);
				break;
			}

			case ONQUERYASSET:
			{
				this->processQueryAsset(task);
				break;
			}


			case ONQUERYSTRUCTUREDFUND:
			{
				this->processQueryStructuredFund(task);
				break;
			}

			case ONQUERYFUNDTRANSFER:
			{
				this->processQueryFundTransfer(task);
				break;
			}

			case ONFUNDTRANSFER:
			{
				this->processFundTransfer(task);
				break;
			}

			case ONQUERYETF:
			{
				this->processQueryETF(task);
				break;
			}

			case ONQUERYETFBASKET:
			{
				this->processQueryETFBasket(task);
				break;
			}

			case ONQUERYIPOINFOLIST:
			{
				this->processQueryIPOInfoList(task);
				break;
			}

			case ONQUERYIPOQUOTAINFO:
			{
				this->processQueryIPOQuotaInfo(task);
				break;
			}


			case ONQUERYOPTIONAUCTIONINFO:
			{
				this->processQueryOptionAuctionInfo(task);
				break;
			}
		};
	}
};

void TraderApi::processDisconnected(Task *task)
{
	PyLock lock;
	this->onDisconnected(task->addtional_int, task->task_id);
	delete task;
};

void TraderApi::processError(Task *task)
{
	PyLock lock;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onError(error);
	delete task;
};

void TraderApi::processOrderEvent(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPOrderInfo *task_data = (XTPOrderInfo*)task->task_data;
		data["cancel_time"] = task_data->cancel_time;
		data["update_time"] = task_data->update_time;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["trade_amount"] = task_data->trade_amount;
		data["price_type"] = (int)task_data->price_type;
		data["order_type"] = task_data->order_type;
		data["price"] = task_data->price;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["order_local_id"] = task_data->order_local_id;
		data["side"] = (int)task_data->side;
		data["position_effect"] = (int)task_data->position_effect;
		data["reserved1"] = (int)task_data->reserved1;
		data["reserved2"] = (int)task_data->reserved2;
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["insert_time"] = task_data->insert_time;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_status"] = (int)task_data->order_status;
		data["ticker"] = task_data->ticker;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
		data["market"] = (int)task_data->market;
		data["quantity"] = task_data->quantity;
		data["business_type"] = int(task_data->business_type);
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onOrderEvent(data, error, task->addtional_int);
	delete task;
};

void TraderApi::processTradeEvent(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPTradeReport *task_data = (XTPTradeReport*)task->task_data;
		data["branch_pbu"] = task_data->branch_pbu;
		data["trade_amount"] = task_data->trade_amount;
		data["exec_id"] = task_data->exec_id;
		data["trade_type"] = task_data->trade_type;
		data["order_client_id"] = task_data->order_client_id;
		data["order_exch_id"] = task_data->order_exch_id;
		data["price"] = task_data->price;
		data["report_index"] = task_data->report_index;
		data["local_order_id"] = task_data->local_order_id;
		data["trade_time"] = task_data->trade_time;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["ticker"] = task_data->ticker;
		data["side"] = (int)task_data->side;
		data["position_effect"] = (int)task_data->position_effect;
		data["reserved1"] = (int)task_data->reserved1;
		data["reserved2"] = (int)task_data->reserved2;
		data["market"] = (int)task_data->market;
		data["quantity"] = task_data->quantity;
		data["business_type"] = int(task_data->business_type);
		delete task->task_data;
	}

	this->onTradeEvent(data, task->addtional_int);
	delete task;
};

void TraderApi::processCancelOrderError(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPOrderCancelInfo *task_data = (XTPOrderCancelInfo*)task->task_data;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["order_xtp_id"] = task_data->order_xtp_id;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onCancelOrderError(data, error, task->addtional_int);
	delete task;
};

void TraderApi::processQueryOrder(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryOrderRsp *task_data = (XTPQueryOrderRsp*)task->task_data;
		data["cancel_time"] = task_data->cancel_time;
		data["update_time"] = task_data->update_time;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["trade_amount"] = task_data->trade_amount;
		data["price_type"] = (int)task_data->price_type;
		data["order_type"] = task_data->order_type;
		data["price"] = task_data->price;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["order_local_id"] = task_data->order_local_id;
		data["side"] = (int)task_data->side;
		data["position_effect"] = (int)task_data->position_effect;
		data["reserved1"] = (int)task_data->reserved1;
		data["reserved2"] = (int)task_data->reserved2;
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["insert_time"] = task_data->insert_time;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_status"] = (int)task_data->order_status;
		data["ticker"] = task_data->ticker;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
		data["market"] = (int)task_data->market;
		data["quantity"] = task_data->quantity;
		data["business_type"] = int(task_data->business_type);
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onQueryOrder(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryTrade(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryTradeRsp *task_data = (XTPQueryTradeRsp*)task->task_data;
		data["branch_pbu"] = task_data->branch_pbu;
		data["trade_amount"] = task_data->trade_amount;
		data["exec_id"] = task_data->exec_id;
		data["trade_type"] = task_data->trade_type;
		data["order_client_id"] = task_data->order_client_id;
		data["order_exch_id"] = task_data->order_exch_id;
		data["price"] = task_data->price;
		data["report_index"] = task_data->report_index;
		data["local_order_id"] = task_data->local_order_id;
		data["trade_time"] = task_data->trade_time;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["ticker"] = task_data->ticker;
		data["side"] = (int)task_data->side;
		data["position_effect"] = (int)task_data->position_effect;
		data["reserved1"] = (int)task_data->reserved1;
		data["reserved2"] = (int)task_data->reserved2;
		data["market"] = (int)task_data->market;
		data["quantity"] = task_data->quantity;
		data["business_type"] = int(task_data->business_type);
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onQueryTrade(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryStkPositionRsp *task_data = (XTPQueryStkPositionRsp*)task->task_data;
		data["ticker"] = task_data->ticker;
		data["ticker_name"] = task_data->ticker_name;
		data["market"] = int(task_data->market);	//�ֶ��޸�
		data["total_qty"] = task_data->total_qty;
		data["sellable_qty"] = task_data->sellable_qty;
		data["avg_price"] = task_data->avg_price;
		data["unrealized_pnl"] = task_data->unrealized_pnl;
		data["yesterday_position"] = task_data->yesterday_position;
		data["purchase_redeemable_qty"] = task_data->purchase_redeemable_qty;	

		data["position_direction"] = (int)task_data->position_direction;
		data["reserved1"] = task_data->reserved1;
		data["executable_option"] = task_data->executable_option;
		data["lockable_position"] = task_data->lockable_position;
		data["executable_underlying"] = task_data->executable_underlying;
		data["locked_position"] = task_data->locked_position;
		data["usable_locked_position"] = task_data->usable_locked_position;

		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onQueryPosition(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryAsset(Task *task)
{
	PyLock lock;
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
		data["account_type"] = (int)task_data->account_type;

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
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onQueryAsset(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryStructuredFund(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPStructuredFundInfo *task_data = (XTPStructuredFundInfo*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["sf_ticker"] = task_data->sf_ticker;
		data["sf_ticker_name"] = task_data->sf_ticker_name;
		data["ticker"] = task_data->ticker;
		data["ticker_name"] = task_data->ticker_name;
		data["split_merge_status"] = (int)task_data->split_merge_status;
		data["ratio"] = task_data->ratio;
		data["min_split_qty"] = task_data->min_split_qty;
		data["min_merge_qty"] = task_data->min_merge_qty;
		data["net_price"] = task_data->net_price;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onQueryStructuredFund(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryFundTransfer(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPFundTransferNotice *task_data = (XTPFundTransferNotice*)task->task_data;
		data["serial_id"] = task_data->serial_id;
		data["transfer_type"] = (int)task_data->transfer_type;
		data["amount"] = task_data->amount;
		data["oper_status"] = (int)task_data->oper_status;
		data["transfer_time"] = task_data->transfer_time;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onQueryFundTransfer(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processFundTransfer(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPFundTransferNotice *task_data = (XTPFundTransferNotice*)task->task_data;
		data["serial_id"] = task_data->serial_id;
		data["transfer_type"] = (int)task_data->transfer_type;
		data["amount"] = task_data->amount;
		data["oper_status"] = (int)task_data->oper_status;
		data["transfer_time"] = task_data->transfer_time;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onFundTransfer(data, error, task->addtional_int);
	delete task;
};

void TraderApi::processQueryETF(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryETFBaseRsp *task_data = (XTPQueryETFBaseRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["etf"] = task_data->etf;
		data["subscribe_redemption_ticker"] = task_data->subscribe_redemption_ticker;
		data["unit"] = task_data->unit;
		data["subscribe_status"] = task_data->subscribe_status;
		data["redemption_status"] = task_data->redemption_status;
		data["max_cash_ratio"] = task_data->max_cash_ratio;
		data["estimate_amount"] = task_data->estimate_amount;
		data["cash_component"] = task_data->cash_component;
		data["net_value"] = task_data->net_value;
		data["total_amount"] = task_data->total_amount;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onQueryETF(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryETFBasket(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryETFComponentRsp *task_data = (XTPQueryETFComponentRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["ticker"] = task_data->ticker;
		data["component_ticker"] = task_data->component_ticker;
		data["component_name"] = task_data->component_name;
		data["quantity"] = task_data->quantity;
		data["component_market"] = (int)task_data->component_market;
		data["replace_type"] = (int)task_data->replace_type;
		data["premium_ratio"] = task_data->premium_ratio;
		data["amount"] = task_data->amount;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onQueryETFBasket(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryIPOInfoList(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryIPOTickerRsp *task_data = (XTPQueryIPOTickerRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["ticker"] = task_data->ticker;
		data["ticker_name"] = task_data->ticker_name;
		data["price"] = task_data->price;
		data["unit"] = task_data->unit;
		data["qty_upper_limit"] = task_data->qty_upper_limit;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onQueryIPOInfoList(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryIPOQuotaInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryIPOQuotaRsp *task_data = (XTPQueryIPOQuotaRsp*)task->task_data;
		data["market"] = (int)task_data->market;
		data["quantity"] = task_data->quantity;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onQueryIPOQuotaInfo(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};



void TraderApi::processQueryOptionAuctionInfo(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryOptionAuctionInfoRsp *task_data = (XTPQueryOptionAuctionInfoRsp*)task->task_data;
		data["ticker"] = task_data->ticker;
		data["security_id_source"] = (int)task_data->security_id_source;
		data["symbol"] = task_data->symbol;
		data["contract_id"] = task_data->contract_id;
		data["underlying_security_id"] = task_data->underlying_security_id;
		data["underlying_security_id_source"] = (int)task_data->underlying_security_id_source;

		data["list_date"] = task_data->list_date;
		data["last_trade_date"] = task_data->last_trade_date;
		data["ticker_type"] = (int)task_data->ticker_type;
		data["day_trading"] = task_data->day_trading;

		data["call_or_put"] = (int)task_data->call_or_put;
		data["delivery_day"] = task_data->delivery_day;
		data["delivery_month"] = task_data->delivery_month;

		data["exercise_type"] = (int)task_data->exercise_type;
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

		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = task_error->error_msg;
		delete task->task_error;
	}

	this->onQueryOptionAuctionInfo(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

///-------------------------------------------------------------------------------------
///��������
///-------------------------------------------------------------------------------------

void TraderApi::createTraderApi(uint8_t clientid, string path)
{
	this->api = XTP::API::TraderApi::CreateTraderApi(clientid, path.c_str());
	this->api->RegisterSpi(this);
};

void TraderApi::release()
{
	this->api->Release();
};

int TraderApi::exit()
{
	//�ú�����ԭ��API��û�У����ڰ�ȫ�˳�API�ã�ԭ����join�ƺ���̫�ȶ�
	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	return 1;
};

string TraderApi::getTradingDay()
{
	string day = this->api->GetTradingDay();
	return day;
};

dict TraderApi::getApiLastError()
{
	dict d;
	XTPRI *error = this->api->GetApiLastError();

	d["error_id"] = error->error_id;
	d["error_msg"] = error->error_msg;

	return d;
}

string TraderApi::getApiVersion()
{
	string version = this->api->GetApiVersion();
	return version;
}

uint8_t TraderApi::getClientIDByXTPID(uint64_t orderid)
{
	return this->api->GetClientIDByXTPID(orderid);
}

string TraderApi::getAccountByXTPID(uint64_t orderid)
{
	string account = this->api->GetAccountByXTPID(orderid);
	return account;
}

void TraderApi::subscribePublicTopic(int type)
{
	this->api->SubscribePublicTopic((XTP_TE_RESUME_TYPE)type);
}

void TraderApi::setSoftwareKey(string key)
{
	this->api->SetSoftwareKey(key.c_str());
}

void TraderApi::setSoftwareVersion(string version)
{
	this->api->SetSoftwareVersion(version.c_str());
}

void TraderApi::setHeartBeatInterval(uint32_t interval)
{
	this->api->SetHeartBeatInterval(interval);
};

uint64_t TraderApi::login(string ip, int port, string user, string password, int socktype)
{
	return this->api->Login(ip.c_str(), port, user.c_str(), password.c_str(), (XTP_PROTOCOL_TYPE)socktype);
};

int TraderApi::logout(uint64_t sessionid)
{
	return this->api->Logout(sessionid);
};


uint64_t TraderApi::insertOrder(dict req, uint64_t sessionid)
{
	XTPOrderInsertInfo myreq = XTPOrderInsertInfo();
	memset(&myreq, 0, sizeof(myreq));
	getDouble(req, "stop_price", &myreq.stop_price);
	getDouble(req, "price", &myreq.price);
	getStr(req, "ticker", myreq.ticker);

	getUint32(req, "order_client_id", &myreq.order_client_id);
	getUint64(req, "order_xtp_id", &myreq.order_xtp_id);
	getInt64(req, "quantity", &myreq.quantity);

	int price_type;
	int side;
	int position_effect;
	int reserved1;
	int reserved2;
	int market;
	int business_type;
	getInt(req, "price_type", &price_type);
	getInt(req, "side", &side);
	getInt(req, "position_effect", &position_effect);
	getInt(req, "reserved1", &reserved1);
	getInt(req, "reserved2", &reserved2);
	getInt(req, "market", &market);
	getInt(req, "business_type", &business_type);
	myreq.price_type = (XTP_PRICE_TYPE)price_type;
	myreq.side = (XTP_SIDE_TYPE)side;
	myreq.position_effect = (XTP_POSITION_EFFECT_TYPE)position_effect;
	myreq.reserved1 = reserved1;
	myreq.reserved2 = reserved2;
	myreq.market = (XTP_MARKET_TYPE)market;
	myreq.business_type = (XTP_BUSINESS_TYPE)business_type;

	return this->api->InsertOrder(&myreq, sessionid);
};

uint64_t TraderApi::cancelOrder(uint64_t orderid, uint64_t sessionid)
{
	return this->api->CancelOrder(orderid, sessionid);
}

int TraderApi::queryOrderByXTPID(uint64_t orderid, uint64_t sessionid, int reqid)
{
	return this->api->QueryOrderByXTPID(orderid, sessionid, reqid);
};

int TraderApi::queryOrders(dict req, uint64_t sessionid, int reqid)
{
	XTPQueryOrderReq myreq = XTPQueryOrderReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);
	getInt64(req, "end_time", &myreq.end_time);
	getInt64(req, "begin_time", &myreq.begin_time);
	return this->api->QueryOrders(&myreq, sessionid, reqid);
};

int TraderApi::queryTradesByXTPID(uint64_t orderid, uint64_t sessionid, int reqid)
{
	return this->api->QueryTradesByXTPID(orderid, sessionid, reqid);
};

int TraderApi::queryTrades(dict req, uint64_t sessionid, int reqid)
{
	XTPQueryTraderReq myreq = XTPQueryTraderReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);
	getInt64(req, "end_time", &myreq.end_time);
	getInt64(req, "begin_time", &myreq.begin_time);
	return this->api->QueryTrades(&myreq, sessionid, reqid);
};

int TraderApi::queryPosition(string ticker, uint64_t sessionid, int reqid)
{
	return this->api->QueryPosition(ticker.c_str(), sessionid, reqid);
};

int TraderApi::queryAsset(uint64_t sessionid, int reqid)
{
	return this->api->QueryAsset(sessionid, reqid);
};

int TraderApi::queryStructuredFund(dict req, uint64_t sessionid, int reqid)
{
	XTPQueryStructuredFundInfoReq myreq = XTPQueryStructuredFundInfoReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "sf_ticker", myreq.sf_ticker);

	int exchange_id;
	getInt(req, "exchange_id", &exchange_id);
	myreq.exchange_id = (XTP_EXCHANGE_TYPE)exchange_id;

	return this->api->QueryStructuredFund(&myreq, sessionid, reqid);

};

uint64_t TraderApi::fundTransfer(dict req, uint64_t sessionid)
{
	XTPFundTransferReq myreq = XTPFundTransferReq();
	memset(&myreq, 0, sizeof(myreq));
	getUint64(req, "serial_id", &myreq.serial_id);
	getStr(req, "fund_account", myreq.fund_account);
	getStr(req, "password", myreq.password);
	getDouble(req, "amount", &myreq.amount);

	int transfer_type;
	getInt(req, "transfer_type", &transfer_type);
	myreq.transfer_type = (XTP_FUND_TRANSFER_TYPE)transfer_type;

	return this->api->FundTransfer(&myreq, sessionid);
};

int TraderApi::queryFundTransfer(dict req, uint64_t sessionid, int reqid)
{
	XTPQueryFundTransferLogReq myreq = XTPQueryFundTransferLogReq();
	memset(&myreq, 0, sizeof(myreq));
	getUint64(req, "serial_id", &myreq.serial_id);
	return this->api->QueryFundTransfer(&myreq, sessionid, reqid);
};

int TraderApi::queryETF(dict req, uint64_t sessionid, int reqid)
{
	XTPQueryETFBaseReq myreq = XTPQueryETFBaseReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);

	int market;
	getInt(req, "market", &market);
	myreq.market = (XTP_MARKET_TYPE)market;

	return this->api->QueryETF(&myreq, sessionid, reqid);
};

int TraderApi::queryETFTickerBasket(dict req, uint64_t sessionid, int reqid)
{
	XTPQueryETFComponentReq myreq = XTPQueryETFComponentReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);

	int market;
	getInt(req, "market", &market);
	myreq.market = (XTP_MARKET_TYPE)market;

	return this->api->QueryETFTickerBasket(&myreq, sessionid, reqid);
};

int TraderApi::queryIPOInfoList(uint64_t sessionid, int reqid)
{
	return this->api->QueryIPOInfoList(sessionid, reqid);
};

int TraderApi::queryIPOQuotaInfo(uint64_t sessionid, int reqid)
{
	return this->api->QueryIPOQuotaInfo(sessionid, reqid);
};

int TraderApi::queryOptionAuctionInfo(dict req,uint64_t sessionid, int reqid)
{
	XTPQueryOptionAuctionInfoReq myreq = XTPQueryOptionAuctionInfoReq();
	memset(&myreq, 0, sizeof(myreq));
	getStr(req, "ticker", myreq.ticker);

	int market;
	getInt(req, "market", &market);
	myreq.market = (XTP_MARKET_TYPE)market;
	return this->api->QueryOptionAuctionInfo(&myreq,sessionid, reqid);
};


///-------------------------------------------------------------------------------------
///Boost.Python��װ
///-------------------------------------------------------------------------------------

struct TraderApiWrap : TraderApi, wrapper < TraderApi >
{
	virtual void onDisconnected(uint64_t session, int reason)
	{
		try
		{
			this->get_override("onDisconnected")(session, reason);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onError(dict data)
	{
		try
		{
			this->get_override("onError")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onOrderEvent(dict data, dict error, uint64_t session)
	{
		try
		{
			this->get_override("onOrderEvent")(data, error, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onTradeEvent(dict data, uint64_t session)
	{
		try
		{
			this->get_override("onTradeEvent")(data, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onCancelOrderError(dict data, dict error, uint64_t session)
	{
		try
		{
			this->get_override("onCancelOrderError")(data, error, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryOrder(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryOrder")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryTrade(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryTrade")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryPosition(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryPosition")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryAsset(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryAsset")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryStructuredFund(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryStructuredFund")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryFundTransfer(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryFundTransfer")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onFundTransfer(dict data, dict error, uint64_t session)
	{
		try
		{
			this->get_override("onFundTransfer")(data, error, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryETF(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryETF")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryETFBasket(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryETFBasket")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryIPOInfoList(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryIPOInfoList")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryIPOQuotaInfo(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryIPOQuotaInfo")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};


	virtual void onQueryOptionAuctionInfo(dict data, dict error, int id, bool last, uint64_t session)
	{
		try
		{
			this->get_override("onQueryOptionAuctionInfo")(data, error, id, last, session);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

};


BOOST_PYTHON_MODULE(vnxtptrader)
{
	PyEval_InitThreads();	//����ʱ���У���֤�ȴ���GIL

	class_<TraderApiWrap, boost::noncopyable>("TraderApi")
		.def("createTraderApi", &TraderApiWrap::createTraderApi)
		.def("release", &TraderApiWrap::release)
		.def("exit", &TraderApiWrap::exit)
		.def("getTradingDay", &TraderApiWrap::getTradingDay)
		.def("getApiLastError", &TraderApiWrap::getApiLastError)
		.def("getApiVersion", &TraderApiWrap::getApiVersion)
		.def("getClientIDByXTPID", &TraderApiWrap::getClientIDByXTPID)
		.def("getAccountByXTPID", &TraderApiWrap::getAccountByXTPID)
		.def("subscribePublicTopic", &TraderApiWrap::subscribePublicTopic)
		.def("setSoftwareKey", &TraderApiWrap::setSoftwareKey)
		.def("setSoftwareVersion", &TraderApiWrap::setSoftwareVersion)
		.def("setHeartBeatInterval", &TraderApiWrap::setHeartBeatInterval)
		.def("login", &TraderApiWrap::login)
		.def("logout", &TraderApiWrap::logout)
		.def("insertOrder", &TraderApiWrap::insertOrder)
		.def("cancelOrder", &TraderApiWrap::cancelOrder)
		.def("queryOrderByXTPID", &TraderApiWrap::queryOrderByXTPID)
		.def("queryOrders", &TraderApiWrap::queryOrders)
		.def("queryTradesByXTPID", &TraderApiWrap::queryTradesByXTPID)
		.def("queryTrades", &TraderApiWrap::queryTrades)
		.def("queryPosition", &TraderApiWrap::queryPosition)
		.def("queryAsset", &TraderApiWrap::queryAsset)
		.def("queryStructuredFund", &TraderApiWrap::queryStructuredFund)
		.def("fundTransfer", &TraderApiWrap::fundTransfer)
		.def("queryFundTransfer", &TraderApiWrap::queryFundTransfer)
		.def("queryETF", &TraderApiWrap::queryETF)
		.def("queryETFTickerBasket", &TraderApiWrap::queryETFTickerBasket)
		.def("queryIPOInfoList", &TraderApiWrap::queryIPOInfoList)
		.def("queryIPOQuotaInfo", &TraderApiWrap::queryIPOQuotaInfo)

		.def("queryOptionAuctionInfo", &TraderApiWrap::queryOptionAuctionInfo)

		.def("onDisconnected", pure_virtual(&TraderApiWrap::onDisconnected))
		.def("onError", pure_virtual(&TraderApiWrap::onError))
		.def("onOrderEvent", pure_virtual(&TraderApiWrap::onOrderEvent))
		.def("onTradeEvent", pure_virtual(&TraderApiWrap::onTradeEvent))
		.def("onCancelOrderError", pure_virtual(&TraderApiWrap::onCancelOrderError))
		.def("onQueryOrder", pure_virtual(&TraderApiWrap::onQueryOrder))
		.def("onQueryTrade", pure_virtual(&TraderApiWrap::onQueryTrade))
		.def("onQueryPosition", pure_virtual(&TraderApiWrap::onQueryPosition))
		.def("onQueryAsset", pure_virtual(&TraderApiWrap::onQueryAsset))
		.def("onQueryStructuredFund", pure_virtual(&TraderApiWrap::onQueryStructuredFund))
		.def("onQueryFundTransfer", pure_virtual(&TraderApiWrap::onQueryFundTransfer))
		.def("onFundTransfer", pure_virtual(&TraderApiWrap::onFundTransfer))
		.def("onQueryETF", pure_virtual(&TraderApiWrap::onQueryETF))
		.def("onQueryETFBasket", pure_virtual(&TraderApiWrap::onQueryETFBasket))
		.def("onQueryIPOInfoList", pure_virtual(&TraderApiWrap::onQueryIPOInfoList))
		.def("onQueryIPOQuotaInfo", pure_virtual(&TraderApiWrap::onQueryIPOQuotaInfo))

		.def("onQueryOptionAuctionInfo", pure_virtual(&TraderApiWrap::onQueryOptionAuctionInfo))
		;
};
