// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//

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

void TraderApi::OnOrderEvent(XTPOrderInfo *order_info, XTPRI *error_info)
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

	this->task_queue.push(task);
};

void TraderApi::OnTradeEvent(XTPTradeReport *trade_info)
{
	Task* task = new Task();
	task->task_name = ONTRADEEVENT;

	if (trade_info)
	{
		XTPTradeReport *task_data = new XTPTradeReport();
		*task_data = *trade_info;
		task->task_data = task_data;
	}
	this->task_queue.push(task);
};

void TraderApi::OnCancelOrderError(XTPOrderCancelInfo *cancel_info, XTPRI *error_info)
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

	this->task_queue.push(task);
};

void TraderApi::OnQueryOrder(XTPQueryOrderRsp *order_info, XTPRI *error_info, int request_id, bool is_last)
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
	this->task_queue.push(task);
};

void TraderApi::OnQueryTrade(XTPQueryTradeRsp *trade_info, XTPRI *error_info, int request_id, bool is_last)
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
	this->task_queue.push(task);
};

void TraderApi::OnQueryPosition(XTPQueryStkPositionRsp *position, XTPRI *error_info, int request_id, bool is_last)
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
	this->task_queue.push(task);
};

void TraderApi::OnQueryAsset(XTPQueryAssetRsp *asset, XTPRI *error_info, int request_id, bool is_last)
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

	this->onOrderEvent(data, error);
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

	this->onTradeEvent(data);
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

	this->onCancelOrderError(data, error);
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

	this->onQueryOrder(data, error, task->task_id, task->task_last);
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

	this->onQueryTrade(data, error, task->task_id, task->task_last);
	delete task;
};

void TraderApi::processQueryPosition(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryStkPositionRsp *task_data = (XTPQueryStkPositionRsp*)task->task_data;
		data["ticker_name"] = task_data->ticker_name;
		data["sellable_qty"] = task_data->sellable_qty;
		data["unrealized_pnl"] = task_data->unrealized_pnl;
		data["avg_price"] = task_data->avg_price;
		data["total_qty"] = task_data->total_qty;
		data["ticker"] = task_data->ticker;
		data["market"] = int(task_data->market);	//手动修改
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

	this->onQueryPosition(data, error, task->task_id, task->task_last);
	delete task;
};

void TraderApi::processQueryAsset(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPQueryAssetRsp *task_data = (XTPQueryAssetRsp*)task->task_data;
		data["fund_sell_fee"] = task_data->fund_sell_fee;
		data["security_asset"] = task_data->security_asset;
		data["buying_power"] = task_data->buying_power;
		data["fund_buy_amount"] = task_data->fund_buy_amount;
		data["fund_buy_fee"] = task_data->fund_buy_fee;
		data["fund_sell_amount"] = task_data->fund_sell_amount;
		data["total_asset"] = task_data->total_asset;
		data['withholding_amount'] = task_data->withholding_amount;
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

	this->onQueryAsset(data, error, task->task_id, task->task_last);
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
}

int TraderApi::queryAsset(uint64_t sessionid, int reqid)
{
	return this->api->QueryAsset(sessionid, reqid);
}


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

	virtual void onOrderEvent(dict data, dict error)
	{
		try
		{
			this->get_override("onOrderEvent")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onTradeEvent(dict data)
	{
		try
		{
			this->get_override("onTradeEvent")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onCancelOrderError(dict data, dict error)
	{
		try
		{
			this->get_override("onCancelOrderError")(data, error);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryOrder(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onQueryOrder")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryTrade(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onQueryTrade")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryPosition(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onQueryPosition")(data, error, id, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryAsset(dict data, dict error, int id, bool last)
	{
		try
		{
			this->get_override("onQueryAsset")(data, error, id, last);
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

		.def("onDisconnected", pure_virtual(&TraderApiWrap::onDisconnected))
		.def("onError", pure_virtual(&TraderApiWrap::onError))
		.def("onOrderEvent", pure_virtual(&TraderApiWrap::onOrderEvent))
		.def("onTradeEvent", pure_virtual(&TraderApiWrap::onTradeEvent))
		.def("onCancelOrderError", pure_virtual(&TraderApiWrap::onCancelOrderError))
		.def("onQueryOrder", pure_virtual(&TraderApiWrap::onQueryOrder))
		.def("onQueryTrade", pure_virtual(&TraderApiWrap::onQueryTrade))
		.def("onQueryPosition", pure_virtual(&TraderApiWrap::onQueryPosition))
		.def("onQueryAsset", pure_virtual(&TraderApiWrap::onQueryAsset))
		;
};
