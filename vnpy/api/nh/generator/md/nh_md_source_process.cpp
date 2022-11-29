void MdApi::processFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontConnected();
};

void MdApi::processFrontDisConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisConnected();
};

void MdApi::processHeartBeatWarning(Task *task)
{
	gil_scoped_acquire acquire;
	this->onHeartBeatWarning(task->task_id);
};

void MdApi::processRspError(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		ERRORMSGINFO_t *task_data = (ERRORMSGINFO_t*)task->task_data;
		data["error_code"] = task_data->error_code;
		data["error_message"] = toUtf(task_data->error_message);
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["utp_server_id"] = task_data->utp_server_id;
		data["oms_server_id"] = task_data->oms_server_id;
		delete task_data;
	}
	this->onRspError(data, task->task_id);
};

void MdApi::processRtnMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		STKMarketData_t *task_data = (STKMarketData_t*)task->task_data;
		data["trading_day"] = toUtf(task_data->trading_day);
		data["update_time"] = toUtf(task_data->update_time);
		data["update_millisec"] = task_data->update_millisec;
		data["update_sequence"] = task_data->update_sequence;
		data["instrument_id"] = toUtf(task_data->instrument_id);
		data["exchange_id"] = toUtf(task_data->exchange_id);
		data["exchange_inst_id"] = toUtf(task_data->exchange_inst_id);
		data["instrument_status"] = task_data->instrument_status;
		data["last_price"] = task_data->last_price;
		data["volume"] = task_data->volume;
		data["last_volume"] = task_data->last_volume;
		data["turnover"] = task_data->turnover;
		data["open_interest"] = task_data->open_interest;
		data["open_price"] = task_data->open_price;
		data["highest_price"] = task_data->highest_price;
		data["lowest_price"] = task_data->lowest_price;
		data["close_price"] = task_data->close_price;
		data["settlement_price"] = task_data->settlement_price;
		data["average_price"] = task_data->average_price;
		data["change_price"] = task_data->change_price;
		data["change_markup"] = task_data->change_markup;
		data["change_swing"] = task_data->change_swing;
		data["upper_limit_price"] = task_data->upper_limit_price;
		data["lower_limit_price"] = task_data->lower_limit_price;
		data["pre_settlement_price"] = task_data->pre_settlement_price;
		data["pre_close_price"] = task_data->pre_close_price;
		data["pre_open_interest"] = task_data->pre_open_interest;
		data["pre_delta"] = task_data->pre_delta;
		data["curr_delta"] = task_data->curr_delta;
		data["best_ask_price"] = task_data->best_ask_price;
		data["best_ask_volume"] = task_data->best_ask_volume;
		data["best_bid_price"] = task_data->best_bid_price;
		data["best_bid_volume"] = task_data->best_bid_volume;
		data["ask_price1"] = task_data->ask_price1;
		data["ask_volume1"] = task_data->ask_volume1;
		data["bid_price1"] = task_data->bid_price1;
		data["bid_volume1"] = task_data->bid_volume1;
		data["ask_price2"] = task_data->ask_price2;
		data["ask_volume2"] = task_data->ask_volume2;
		data["bid_price2"] = task_data->bid_price2;
		data["bid_volume2"] = task_data->bid_volume2;
		data["ask_price3"] = task_data->ask_price3;
		data["ask_volume3"] = task_data->ask_volume3;
		data["bid_price3"] = task_data->bid_price3;
		data["bid_volume3"] = task_data->bid_volume3;
		data["ask_price4"] = task_data->ask_price4;
		data["ask_volume4"] = task_data->ask_volume4;
		data["bid_price4"] = task_data->bid_price4;
		data["bid_volume4"] = task_data->bid_volume4;
		data["ask_price5"] = task_data->ask_price5;
		data["ask_volume5"] = task_data->ask_volume5;
		data["bid_price5"] = task_data->bid_price5;
		data["bid_volume5"] = task_data->bid_volume5;
		data["ask_price6"] = task_data->ask_price6;
		data["ask_volume6"] = task_data->ask_volume6;
		data["bid_price6"] = task_data->bid_price6;
		data["bid_volume6"] = task_data->bid_volume6;
		data["ask_price7"] = task_data->ask_price7;
		data["ask_volume7"] = task_data->ask_volume7;
		data["bid_price7"] = task_data->bid_price7;
		data["bid_volume7"] = task_data->bid_volume7;
		data["ask_price8"] = task_data->ask_price8;
		data["ask_volume8"] = task_data->ask_volume8;
		data["bid_price8"] = task_data->bid_price8;
		data["bid_volume8"] = task_data->bid_volume8;
		data["ask_price9"] = task_data->ask_price9;
		data["ask_volume9"] = task_data->ask_volume9;
		data["bid_price9"] = task_data->bid_price9;
		data["bid_volume9"] = task_data->bid_volume9;
		data["ask_price10"] = task_data->ask_price10;
		data["ask_volume10"] = task_data->ask_volume10;
		data["bid_price10"] = task_data->bid_price10;
		data["bid_volume10"] = task_data->bid_volume10;
		data["md_source"] = toUtf(task_data->md_source);
		delete task_data;
	}
	this->onRtnMarketData(data);
};

void MdApi::processRspUtpLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		RspUtpLoginField_t *task_data = (RspUtpLoginField_t*)task->task_data;
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["session_public_key"] = toUtf(task_data->session_public_key);
		data["utp_checking_server_id"] = toUtf(task_data->utp_checking_server_id);
		data["utp_checking_server_time"] = task_data->utp_checking_server_time;
		data["last_login_ip_address"] = toUtf(task_data->last_login_ip_address);
		data["last_login_time"] = task_data->last_login_time;
		data["session_encrypted"] = task_data->session_encrypted;
		delete task_data;
	}
	this->onRspUtpLogin(data, task->task_id);
};

void MdApi::processRspUtpLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		RspUtpLogoutField_t *task_data = (RspUtpLogoutField_t*)task->task_data;
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["utp_server_id"] = task_data->utp_server_id;
		delete task_data;
	}
	this->onRspUtpLogout(data, task->task_id);
};

void MdApi::processRspSubscribe(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		RspSubscribeField_t *task_data = (RspSubscribeField_t*)task->task_data;
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["routing_key"] = toUtf(task_data->routing_key);
		delete task_data;
	}
	this->onRspSubscribe(data, task->task_id);
};

void MdApi::processRspUnSubscribe(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		RspUnSubscribeField_t *task_data = (RspUnSubscribeField_t*)task->task_data;
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["routing_key"] = toUtf(task_data->routing_key);
		delete task_data;
	}
	this->onRspUnSubscribe(data, task->task_id);
};

void MdApi::processRspQryExchange(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		RspQryExchangeField_t *task_data = (RspQryExchangeField_t*)task->task_data;
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["utp_server_id"] = task_data->utp_server_id;
		data["oms_server_id"] = task_data->oms_server_id;
		data["exchange_id"] = toUtf(task_data->exchange_id);
		data["exchange_name"] = toUtf(task_data->exchange_name);
		data["exchange_status"] = task_data->exchange_status;
		delete task_data;
	}
	this->onRspQryExchange(data, task->task_id);
};

void MdApi::processRspQryInstrument(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		RspQryInstrumentField_t *task_data = (RspQryInstrumentField_t*)task->task_data;
		data["response_code"] = task_data->response_code;
		data["response_string"] = toUtf(task_data->response_string);
		data["utp_server_id"] = task_data->utp_server_id;
		data["oms_server_id"] = task_data->oms_server_id;
		data["product_id"] = toUtf(task_data->product_id);
		data["product_name"] = toUtf(task_data->product_name);
		data["exchange_id"] = toUtf(task_data->exchange_id);
		data["product_class"] = task_data->product_class;
		data["instrument_id"] = toUtf(task_data->instrument_id);
		data["instrument_name"] = toUtf(task_data->instrument_name);
		data["instrument_class"] = task_data->instrument_class;
		data["instrument_status"] = task_data->instrument_status;
		data["delivery_year"] = task_data->delivery_year;
		data["delivery_month"] = task_data->delivery_month;
		data["volume_multiple"] = task_data->volume_multiple;
		data["price_tick"] = task_data->price_tick;
		data["price_tick_dividend"] = task_data->price_tick_dividend;
		data["max_marketorder_volume"] = task_data->max_marketorder_volume;
		data["min_marketorder_volume"] = task_data->min_marketorder_volume;
		data["max_limitorder_volume"] = task_data->max_limitorder_volume;
		data["min_limitorder_volume"] = task_data->min_limitorder_volume;
		data["create_date"] = toUtf(task_data->create_date);
		data["open_date"] = toUtf(task_data->open_date);
		data["expire_date"] = toUtf(task_data->expire_date);
		data["last_trading_date"] = toUtf(task_data->last_trading_date);
		data["start_delivery_date"] = toUtf(task_data->start_delivery_date);
		data["end_delivery_date"] = toUtf(task_data->end_delivery_date);
		data["first_notice_date"] = toUtf(task_data->first_notice_date);
		delete task_data;
	}
	this->onRspQryInstrument(data, task->task_id);
};

