// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//
#ifdef WIN32
	#include "stdafx.h"
#endif
#include "vnxtptrader.h"

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

void getUint64(dict d, string key, uint64_t *value)
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

void getUint32(dict d, string key, uint32_t *value)
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

void getInt64(dict d, string key, int64_t *value)
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
			//对字符串指针赋值必须使用strcpy_s, vs2013使用strcpy编译通不过
			//+1应该是因为C++字符串的结尾符号？不是特别确定，不加这个1会出错
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
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void TraderApi::OnDisconnected(uint64_t session_id, int reason)
{
	Task* task = new Task();
	task->task_name = ONDISCONNECTED;
	task->addtional_int = session_id;		//手动修改
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

///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
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
		data["order_submit_status"] = (int)task_data->order_submit_status;
		data["insert_time"] = task_data->insert_time;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_status"] = (int)task_data->order_status;
		data["ticker"] = task_data->ticker;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
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
		data["market"] = int(task_data->market);	//手动修改
		data["total_qty"] = task_data->total_qty;
		data["sellable_qty"] = task_data->sellable_qty;
		data["avg_price"] = task_data->avg_price;
		data["unrealized_pnl"] = task_data->unrealized_pnl;
		data["yesterday_position"] = task_data->yesterday_position;
		data["purchase_redeemable_qty"] = task_data->purchase_redeemable_qty;	
		
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
		data["sf_ticker"] = task_data->ratio;
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

	this->onQueryAsset(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};

void TraderApi::processQueryFundTransfer(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPFundTransferNotice *task_data = (XTPFundTransferNotice*)task->task_data;
		data["fund_sell_fee"] = task_data->serial_id;
		data["security_asset"] = (int)task_data->transfer_type;
		data["security_asset"] = task_data->amount;
		data["security_asset"] = (int)task_data->oper_status;
		data["security_asset"] = task_data->transfer_time;
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

void TraderApi::processFundTransfer(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPFundTransferNotice *task_data = (XTPFundTransferNotice*)task->task_data;
		data["fund_sell_fee"] = task_data->serial_id;
		data["security_asset"] = (int)task_data->transfer_type;
		data["security_asset"] = task_data->amount;
		data["security_asset"] = (int)task_data->oper_status;
		data["security_asset"] = task_data->transfer_time;
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

	this->onQueryAsset(data, error, task->task_id, task->task_last, task->addtional_int);
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

	this->onQueryAsset(data, error, task->task_id, task->task_last, task->addtional_int);
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

	this->onQueryAsset(data, error, task->task_id, task->task_last, task->addtional_int);
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

	this->onQueryAsset(data, error, task->task_id, task->task_last, task->addtional_int);
	delete task;
};


///-------------------------------------------------------------------------------------
///主动函数
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
	//该函数在原生API里没有，用于安全退出API用，原生的join似乎不太稳定
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
	int market;
	int business_type;
	getInt(req, "price_type", &price_type);
	getInt(req, "side", &side);
	getInt(req, "market", &market);
	getInt(req, "business_type", &business_type);
	myreq.price_type = (XTP_PRICE_TYPE)price_type;
	myreq.side = (XTP_SIDE_TYPE)side;
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


///-------------------------------------------------------------------------------------
///Boost.Python封装
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

};


BOOST_PYTHON_MODULE(vnxtptrader)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

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
		;
};
