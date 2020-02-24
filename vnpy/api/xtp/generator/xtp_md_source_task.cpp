void MdApi::OnDisconnected(int reason)
{
	Task task = Task();
	task.task_name = ONDISCONNECTED;
	task.task_int = reason;
	this->task_queue.push(task);
};

void MdApi::OnError(XTPRI *error_info)
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

void MdApi::OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONSUBMARKETDATA;
	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONUNSUBMARKETDATA;
	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnDepthMarketData(XTPMD *market_data, int bid1_qty int bid1_count, int max_bid1_count, int ask1_qty int ask1_count, int max_ask1_count)
{
	Task task = Task();
	task.task_name = ONDEPTHMARKETDATA;
	if (market_data)
	{
		XTPMD *task_data = new XTPMD();
		*task_data = *market_data;
		task.task_data = task_data;
	}
	task.task_int = bid1_qty;
	task.task_int = bid1_count;
	task.task_int = max_bid1_count;
	task.task_int = ask1_qty;
	task.task_int = ask1_count;
	task.task_int = max_ask1_count;
	this->task_queue.push(task);
};

void MdApi::OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONSUBORDERBOOK;
	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONUNSUBORDERBOOK;
	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnOrderBook(XTPOB *order_book)
{
	Task task = Task();
	task.task_name = ONORDERBOOK;
	if (order_book)
	{
		XTPOB *task_data = new XTPOB();
		*task_data = *order_book;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONSUBTICKBYTICK;
	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONUNSUBTICKBYTICK;
	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnTickByTick(XTPTBT *tbt_data)
{
	Task task = Task();
	task.task_name = ONTICKBYTICK;
	if (tbt_data)
	{
		XTPTBT *task_data = new XTPTBT();
		*task_data = *tbt_data;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnSubscribeAllMarketData(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONSUBSCRIBEALLMARKETDATA;
	task.task_int = (int) exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnUnSubscribeAllMarketData(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONUNSUBSCRIBEALLMARKETDATA;
	task.task_int = (int) exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnSubscribeAllOrderBook(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONSUBSCRIBEALLORDERBOOK;
	task.task_int = (int) exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnUnSubscribeAllOrderBook(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONUNSUBSCRIBEALLORDERBOOK;
	task.task_int = (int) exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnSubscribeAllTickByTick(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONSUBSCRIBEALLTICKBYTICK;
	task.task_int = (int) exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnUnSubscribeAllTickByTick(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONUNSUBSCRIBEALLTICKBYTICK;
	task.task_int = (int) exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnQueryAllTickers(XTPQSI* ticker_info, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONQUERYALLTICKERS;
	if (ticker_info)
	{
		XTPQSI *task_data = new XTPQSI();
		*task_data = *ticker_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnQueryTickersPriceInfo(XTPTPI* ticker_info, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONQUERYTICKERSPRICEINFO;
	if (ticker_info)
	{
		XTPTPI *task_data = new XTPTPI();
		*task_data = *ticker_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnSubscribeAllOptionMarketData(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONSUBSCRIBEALLOPTIONMARKETDATA;
	task.task_int = (int) exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnUnSubscribeAllOptionMarketData(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONUNSUBSCRIBEALLOPTIONMARKETDATA;
	task.task_int = (int) exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnSubscribeAllOptionOrderBook(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONSUBSCRIBEALLOPTIONORDERBOOK;
	task.task_int = (int) exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnUnSubscribeAllOptionOrderBook(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONUNSUBSCRIBEALLOPTIONORDERBOOK;
	task.task_int = (int) exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnSubscribeAllOptionTickByTick(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONSUBSCRIBEALLOPTIONTICKBYTICK;
	task.task_int = (int) exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnUnSubscribeAllOptionTickByTick(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONUNSUBSCRIBEALLOPTIONTICKBYTICK;
	task.task_int = (int) exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

