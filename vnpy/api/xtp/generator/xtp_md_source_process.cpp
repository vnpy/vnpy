void MdApi::processDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onDisconnected(task->task_extra);
};

void MdApi::processError(Task *task)
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

void MdApi::processSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
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
	this->onSubMarketData(data, error, task->task_last);
};

void MdApi::processUnSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
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
	this->onUnSubMarketData(data, error, task->task_last);
};

void MdApi::processDepthMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPMD *task_data = (XTPMD*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["last_price"] = task_data->last_price;
		data["pre_close_price"] = task_data->pre_close_price;
		data["open_price"] = task_data->open_price;
		data["high_price"] = task_data->high_price;
		data["low_price"] = task_data->low_price;
		data["close_price"] = task_data->close_price;
		data["pre_total_long_positon"] = task_data->pre_total_long_positon;
		data["total_long_positon"] = task_data->total_long_positon;
		data["pre_settl_price"] = task_data->pre_settl_price;
		data["settl_price"] = task_data->settl_price;
		data["upper_limit_price"] = task_data->upper_limit_price;
		data["lower_limit_price"] = task_data->lower_limit_price;
		data["pre_delta"] = task_data->pre_delta;
		data["curr_delta"] = task_data->curr_delta;
		data["data_time"] = task_data->data_time;
		data["qty"] = task_data->qty;
		data["turnover"] = task_data->turnover;
		data["avg_price"] = task_data->avg_price;
		data["bid"] = task_data->bid;
		data["ask"] = task_data->ask;
		data["bid_qty"] = task_data->bid_qty;
		data["ask_qty"] = task_data->ask_qty;
		data["trades_count"] = task_data->trades_count;
		data["ticker_status"] = toUtf(task_data->ticker_status);
		data["data_type"] = task_data->data_type;
		data["r4"] = task_data->r4;
		delete task_data;
	}
	this->onDepthMarketData(data, task->task_extra, task->task_extra, task->task_extra, task->task_extra, task->task_extra, task->task_extra);
};

void MdApi::processSubOrderBook(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
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
	this->onSubOrderBook(data, error, task->task_last);
};

void MdApi::processUnSubOrderBook(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
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
	this->onUnSubOrderBook(data, error, task->task_last);
};

void MdApi::processOrderBook(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPOB *task_data = (XTPOB*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["last_price"] = task_data->last_price;
		data["qty"] = task_data->qty;
		data["turnover"] = task_data->turnover;
		data["trades_count"] = task_data->trades_count;
		data["bid"] = task_data->bid;
		data["ask"] = task_data->ask;
		data["bid_qty"] = task_data->bid_qty;
		data["ask_qty"] = task_data->ask_qty;
		data["data_time"] = task_data->data_time;
		delete task_data;
	}
	this->onOrderBook(data);
};

void MdApi::processSubTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
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
	this->onSubTickByTick(data, error, task->task_last);
};

void MdApi::processUnSubTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
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
	this->onUnSubTickByTick(data, error, task->task_last);
};

void MdApi::processTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPTBT *task_data = (XTPTBT*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["seq"] = task_data->seq;
		data["data_time"] = task_data->data_time;
		data["type"] = task_data->type;
		delete task_data;
	}
	this->onTickByTick(data);
};

void MdApi::processSubscribeAllMarketData(Task *task)
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
	this->onSubscribeAllMarketData(task->task_extra, error);
};

void MdApi::processUnSubscribeAllMarketData(Task *task)
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
	this->onUnSubscribeAllMarketData(task->task_extra, error);
};

void MdApi::processSubscribeAllOrderBook(Task *task)
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
	this->onSubscribeAllOrderBook(task->task_extra, error);
};

void MdApi::processUnSubscribeAllOrderBook(Task *task)
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
	this->onUnSubscribeAllOrderBook(task->task_extra, error);
};

void MdApi::processSubscribeAllTickByTick(Task *task)
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
	this->onSubscribeAllTickByTick(task->task_extra, error);
};

void MdApi::processUnSubscribeAllTickByTick(Task *task)
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
	this->onUnSubscribeAllTickByTick(task->task_extra, error);
};

void MdApi::processQueryAllTickers(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQSI *task_data = (XTPQSI*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["ticker_name"] = toUtf(task_data->ticker_name);
		data["ticker_type"] = task_data->ticker_type;
		data["pre_close_price"] = task_data->pre_close_price;
		data["upper_limit_price"] = task_data->upper_limit_price;
		data["lower_limit_price"] = task_data->lower_limit_price;
		data["price_tick"] = task_data->price_tick;
		data["buy_qty_unit"] = task_data->buy_qty_unit;
		data["sell_qty_unit"] = task_data->sell_qty_unit;
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
	this->onQueryAllTickers(data, error, task->task_last);
};

void MdApi::processQueryTickersPriceInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPTPI *task_data = (XTPTPI*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["last_price"] = task_data->last_price;
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
	this->onQueryTickersPriceInfo(data, error, task->task_last);
};

void MdApi::processSubscribeAllOptionMarketData(Task *task)
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
	this->onSubscribeAllOptionMarketData(task->task_extra, error);
};

void MdApi::processUnSubscribeAllOptionMarketData(Task *task)
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
	this->onUnSubscribeAllOptionMarketData(task->task_extra, error);
};

void MdApi::processSubscribeAllOptionOrderBook(Task *task)
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
	this->onSubscribeAllOptionOrderBook(task->task_extra, error);
};

void MdApi::processUnSubscribeAllOptionOrderBook(Task *task)
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
	this->onUnSubscribeAllOptionOrderBook(task->task_extra, error);
};

void MdApi::processSubscribeAllOptionTickByTick(Task *task)
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
	this->onSubscribeAllOptionTickByTick(task->task_extra, error);
};

void MdApi::processUnSubscribeAllOptionTickByTick(Task *task)
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
	this->onUnSubscribeAllOptionTickByTick(task->task_extra, error);
};

