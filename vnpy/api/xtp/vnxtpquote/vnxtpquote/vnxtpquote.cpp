// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//
#ifdef WIN32
	#include "stdafx.h"
#endif
#include "vnxtpquote.h"

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

void QuoteApi::OnDisconnected(int reason)
{
    Task* task = new Task();
    task->task_name = ONDISCONNECTED;
    task->task_id = reason;
    this->task_queue.push(task);
};

void QuoteApi::OnError(XTPRI *error_info)
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

void QuoteApi::OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    Task* task = new Task();
    task->task_name = ONSUBMARKETDATA;

    if (ticker)
    {
        XTPST *task_data = new XTPST();
        *task_data = *ticker;
        task->task_data = task_data;
    }

    if (error_info)
    {
        XTPRI *task_error = new XTPRI();
        *task_error = *error_info;
        task->task_error = task_error;
    }

    task->task_last = is_last;
    this->task_queue.push(task);
};

void QuoteApi::OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    Task* task = new Task();
    task->task_name = ONUNSUBMARKETDATA;

    if (ticker)
    {
        XTPST *task_data = new XTPST();
        *task_data = *ticker;
        task->task_data = task_data;
    }

    if (error_info)
    {
        XTPRI *task_error = new XTPRI();
        *task_error = *error_info;
        task->task_error = task_error;
    }

    task->task_last = is_last;
    this->task_queue.push(task);
};

void QuoteApi::OnDepthMarketData(XTPMD *market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count)
{
    Task* task = new Task();
    task->task_name = ONDEPTHMARKETDATA;

    if (market_data)
    {
        XTPMD *task_data = new XTPMD();
        *task_data = *market_data;
        task->task_data = task_data;
    }

    this->task_queue.push(task);
};

void QuoteApi::OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    Task* task = new Task();
    task->task_name = ONSUBORDERBOOK;

    if (ticker)
    {
        XTPST *task_data = new XTPST();
        *task_data = *ticker;
        task->task_data = task_data;
    }

    if (error_info)
    {
        XTPRI *task_error = new XTPRI();
        *task_error = *error_info;
        task->task_error = task_error;
    }

    task->task_last = is_last;
    this->task_queue.push(task);
};

void QuoteApi::OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    Task* task = new Task();
    task->task_name = ONUNSUBORDERBOOK;

    if (ticker)
    {
        XTPST *task_data = new XTPST();
        *task_data = *ticker;
        task->task_data = task_data;
    }

    if (error_info)
    {
        XTPRI *task_error = new XTPRI();
        *task_error = *error_info;
        task->task_error = task_error;
    }

    task->task_last = is_last;
    this->task_queue.push(task);
};

void QuoteApi::OnOrderBook(XTPOB *order_book)
{
    Task* task = new Task();
    task->task_name = ONORDERBOOK;

    if (order_book)
    {
        XTPOB *task_data = new XTPOB();
        *task_data = *order_book;
        task->task_data = task_data;
    }
    this->task_queue.push(task);
};

void QuoteApi::OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last) 
{
	Task* task = new Task();
	task->task_name = ONSUBTICKBYTICK;

	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	this->task_queue.push(task);
};

void QuoteApi::OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task* task = new Task();
	task->task_name = ONUNSUBTICKBYTICK;

	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	this->task_queue.push(task);
};

void QuoteApi::OnTickByTick(XTPTBT *tbt_data)
{
	Task* task = new Task();
	task->task_name = ONTICKBYTICK;

	if (tbt_data)
	{
		XTPTBT *task_data = new XTPTBT();
		*task_data = *tbt_data;
		task->task_data = task_data;
	}

	this->task_queue.push(task);
};

void QuoteApi::OnSubscribeAllMarketData(XTPRI *error_info)
{
	Task* task = new Task();
	task->task_name = ONSUBSCRIBEALLMARKETDATA;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void QuoteApi::OnUnSubscribeAllMarketData(XTPRI *error_info)
{
	Task* task = new Task();
	task->task_name = ONUNSUBSCRIBEALLMARKETDATA;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void QuoteApi::OnSubscribeAllOrderBook(XTPRI *error_info)
{
	Task* task = new Task();
	task->task_name = ONSUBSCRIBEALLORDERBOOK;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};


void QuoteApi::OnUnSubscribeAllOrderBook(XTPRI *error_info)
{
	Task* task = new Task();
	task->task_name = ONUNSUBSCRIBEALLMARKETDATA;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};


void QuoteApi::OnSubscribeAllTickByTick(XTPRI *error_info)
{
	Task* task = new Task();
	task->task_name = ONSUBSCRIBEALLTICKBYTICK;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void QuoteApi::OnUnSubscribeAllTickByTick(XTPRI *error_info)
{
	Task* task = new Task();
	task->task_name = ONUNSUBSCRIBEALLTICKBYTICK;

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	this->task_queue.push(task);
};

void QuoteApi::OnQueryAllTickers(XTPQSI* ticker_info, XTPRI *error_info, bool is_last)
{
    Task* task = new Task();
    task->task_name = ONQUERYALLTICKERS;

    if (ticker_info)
    {
        XTPQSI *task_data = new XTPQSI();
        *task_data = *ticker_info;
        task->task_data = task_data;
    }

    if (error_info)
    {
        XTPRI *task_error = new XTPRI();
        *task_error = *error_info;
        task->task_error = task_error;
    }

    task->task_last = is_last;
    this->task_queue.push(task);
};

void QuoteApi::OnQueryTickersPriceInfo(XTPTPI* ticker_info, XTPRI *error_info, bool is_last)
{
	Task* task = new Task();
	task->task_name = ONQUERYTICKERSPRICEINFO;

	if (ticker_info)
	{
		XTPTPI *task_data = new XTPTPI();
		*task_data = *ticker_info;
		task->task_data = task_data;
	}

	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task->task_error = task_error;
	}

	task->task_last = is_last;
	this->task_queue.push(task);
};


///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void QuoteApi::processTask()
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

			case ONSUBMARKETDATA:
			{
			    this->processSubMarketData(task);
			    break;
			}

			case ONUNSUBMARKETDATA:
			{
			    this->processUnSubMarketData(task);
			    break;
			}

			case ONDEPTHMARKETDATA:
			{
			    this->processDepthMarketData(task);
			    break;
			}

			case ONSUBORDERBOOK:
			{
			    this->processSubOrderBook(task);
			    break;
			}

			case ONUNSUBORDERBOOK:
			{
			    this->processUnSubOrderBook(task);
			    break;
			}

			case ONORDERBOOK:
			{
			    this->processOrderBook(task);
			    break;
			}

			case ONSUBTICKBYTICK:
			{
				this->processSubTickByTick(task);
				break;
			}

			case ONUNSUBTICKBYTICK:
			{
				this->processUnSubTickByTick(task);
				break;
			}

			case ONTICKBYTICK:
			{
				this->processTickByTick(task);
				break;
			}

			case ONSUBSCRIBEALLMARKETDATA:
			{
				this->processSubscribeAllMarketData(task);
				break;
			}

			case ONUNSUBSCRIBEALLMARKETDATA:
			{
				this->processUnSubscribeAllMarketData(task);
				break;
			}

			case ONSUBSCRIBEALLORDERBOOK:
			{
				this->processSubscribeAllOrderBook(task);
				break;
			}

			case ONUNSUBSCRIBEALLORDERBOOK:
			{
				this->processUnSubscribeAllOrderBook(task);
				break;
			}

			case ONSUBSCRIBEALLTICKBYTICK:
			{
				this->processSubscribeAllTickByTick(task);
				break;
			}

			case ONUNSUBSCRIBEALLTICKBYTICK:
			{
				this->processUnSubscribeAllTickByTick(task);
				break;
			}

			case ONQUERYALLTICKERS:
			{
			    this->processQueryAllTickers(task);
			    break;
			}

			case ONQUERYTICKERSPRICEINFO:
			{
				this->processQueryTickersPriceInfo(task);
				break;
			}
		};
	}
};



void QuoteApi::processDisconnected(Task *task)
{
    PyLock lock;
    this->onDisconnected(task->task_id);
    delete task;
};

void QuoteApi::processError(Task *task)
{
    PyLock lock;
    dict error;
    if (task->task_error)
    {
        XTPRI *task_error = (XTPRI*) task->task_error;
        error["error_id"] = task_error->error_id;
        error["error_msg"] = task_error->error_msg;
        delete task->task_error;
    }

    this->onError(error);
    delete task;
};

void QuoteApi::processSubMarketData(Task *task)
{
    PyLock lock;
    dict data;
    if (task->task_data)
    {
        XTPST *task_data = (XTPST*) task->task_data;
        data["exchange_id"] = (int)task_data->exchange_id;
        data["ticker"] = task_data->ticker;
        delete task->task_data;
    }

    dict error;
    if (task->task_error)
    {
        XTPRI *task_error = (XTPRI*) task->task_error;
        error["error_id"] = task_error->error_id;
        error["error_msg"] = task_error->error_msg;
        delete task->task_error;
    }

    this->onSubMarketData(data, error, task->task_last);
    delete task;
};

void QuoteApi::processUnSubMarketData(Task *task)
{
    PyLock lock;
    dict data;
    if (task->task_data)
    {
        XTPST *task_data = (XTPST*) task->task_data;
        data["exchange_id"] = (int)task_data->exchange_id;
        data["ticker"] = task_data->ticker;
        delete task->task_data;
    }

    dict error;
    if (task->task_error)
    {
        XTPRI *task_error = (XTPRI*) task->task_error;
        error["error_id"] = task_error->error_id;
        error["error_msg"] = task_error->error_msg;
        delete task->task_error;
    }

    this->onUnSubMarketData(data, error, task->task_last);
    delete task;
};

void QuoteApi::processDepthMarketData(Task *task)
{
    PyLock lock;
    dict data;
    if (task->task_data)
    {
			XTPMD *task_data = (XTPMD*)task->task_data;
			data["etf_sell_count"] = task_data->etf_sell_count;
			data["trades_count"] = task_data->trades_count;
			data["ma_ask_price"] = task_data->ma_ask_price;
			data["warrant_lower_price"] = task_data->warrant_lower_price;
			data["pre_delta"] = task_data->pre_delta;
			data["etf_buy_money"] = task_data->etf_buy_money;
			data["cancel_buy_count"] = task_data->cancel_buy_count;
			data["low_price"] = task_data->low_price;
			data["ticker_status"] = task_data->ticker_status;
			data["pre_close_price"] = task_data->pre_close_price;
			data["last_price"] = task_data->last_price;
			data["is_market_closed"] = task_data->is_market_closed;
			data["upper_limit_price"] = task_data->upper_limit_price;
			data["cancel_sell_count"] = task_data->cancel_sell_count;
			data["exchange_id"] = (int)task_data->exchange_id;
			data["iopv"] = task_data->iopv;
			data["yield_to_maturity"] = task_data->yield_to_maturity;
			data["curr_delta"] = task_data->curr_delta;
			data["pre_open_interest"] = task_data->pre_open_interest;
			data["pe_ratio1"] = task_data->pe_ratio1;
			data["open_interest"] = task_data->open_interest;
			data["cancel_buy_money"] = task_data->cancel_buy_money;
			data["total_buy_count"] = task_data->total_buy_count;
			data["duration_after_buy"] = task_data->duration_after_buy;
			data["total_position"] = task_data->total_position;
			data["total_warrant_exec_qty"] = task_data->total_warrant_exec_qty;
			data["exec_time"] = task_data->exec_time;
			data["etf_buy_qty"] = task_data->etf_buy_qty;

			data["ma_bond_bid_price"] = task_data->ma_bond_bid_price;
			data["num_bid_orders"] = task_data->num_bid_orders;
			data["etf_sell_qty"] = task_data->etf_sell_qty;
			data["high_price"] = task_data->high_price;
			data["pre_settlement_price"] = task_data->pre_settlement_price;
			data["etf_buy_count"] = task_data->etf_buy_count;
			data["ma_bond_ask_price"] = task_data->ma_bond_ask_price;
			data["cancel_sell_qty"] = task_data->cancel_sell_qty;
			data["lower_limit_price"] = task_data->lower_limit_price;

			data["ma_bid_price"] = task_data->ma_bid_price;
			data["warrant_upper_price"] = task_data->warrant_upper_price;

			data["open_price"] = task_data->open_price;
			data["pe_ratio2"] = task_data->pe_ratio2;
			data["avg_price"] = task_data->avg_price;

			data["total_sell_count"] = task_data->total_sell_count;
			data["qty"] = task_data->qty;
			data["ticker"] = task_data->ticker;
			data["etf_sell_money"] = task_data->etf_sell_money;
			data["total_ask_qty"] = task_data->total_ask_qty;
			data["data_time"] = task_data->data_time;
			data["settlement_price"] = task_data->settlement_price;
			data["num_ask_orders"] = task_data->num_ask_orders;
			data["total_bid_qty"] = task_data->total_bid_qty;
			data["cancel_sell_money"] = task_data->cancel_sell_money;
			data["cancel_buy_qty"] = task_data->cancel_buy_qty;
			data["close_price"] = task_data->close_price;
			data["duration_after_sell"] = task_data->duration_after_sell;
			data["turnover"] = task_data->turnover;

			boost::python::list ask;
			boost::python::list bid;
			boost::python::list ask_qty;
			boost::python::list bid_qty;

			for (int i = 0; i < 10; i++)
			{
				ask.append(task_data->ask[i]);
				bid.append(task_data->bid[i]);
				ask_qty.append(task_data->ask_qty[i]);
				bid_qty.append(task_data->bid_qty[i]);
			}

			data["ask"] = ask;
			data["bid"] = bid;
			data["bid_qty"] = bid_qty;
			data["ask_qty"] = ask_qty;

			delete task->task_data;
    }

    this->onDepthMarketData(data);
    delete task;
};

void QuoteApi::processSubOrderBook(Task *task)
{
    PyLock lock;
    dict data;
    if (task->task_data)
    {
        XTPST *task_data = (XTPST*) task->task_data;
        data["exchange_id"] = (int)task_data->exchange_id;
        data["ticker"] = task_data->ticker;
        delete task->task_data;
    }

    dict error;
    if (task->task_error)
    {
        XTPRI *task_error = (XTPRI*) task->task_error;
        error["error_id"] = task_error->error_id;
        error["error_msg"] = task_error->error_msg;
        delete task->task_error;
    }

    this->onSubOrderBook(data, error, task->task_last);
    delete task;
};

void QuoteApi::processUnSubOrderBook(Task *task)
{
    PyLock lock;
    dict data;
    if (task->task_data)
    {
        XTPST *task_data = (XTPST*) task->task_data;
        data["exchange_id"] = (int)task_data->exchange_id;
        data["ticker"] = task_data->ticker;
        delete task->task_data;
    }

    dict error;
    if (task->task_error)
    {
        XTPRI *task_error = (XTPRI*) task->task_error;
        error["error_id"] = task_error->error_id;
        error["error_msg"] = task_error->error_msg;
        delete task->task_error;
    }

    this->onUnSubOrderBook(data, error, task->task_last);
    delete task;
};

void QuoteApi::processOrderBook(Task *task)
{
    PyLock lock;
    dict data;
    if (task->task_data)
    {
        XTPOB *task_data = (XTPOB*) task->task_data;
				data["exchange_id"] = (int)task_data->exchange_id;
				data["ticker"] = task_data->ticker;
				data["data_time"] = task_data->data_time;

				boost::python::list ask;
				boost::python::list bid;
				boost::python::list ask_qty;
				boost::python::list bid_qty;

				for (int i = 0; i < 10; i++)
				{
					ask.append(task_data->ask[i]);
					bid.append(task_data->bid[i]);
					ask_qty.append(task_data->ask_qty[i]);
					bid_qty.append(task_data->bid_qty[i]);
				}

				data["ask"] = ask;
				data["bid"] = bid;
				data["bid_qty"] = bid_qty;
				data["ask_qty"] = ask_qty;
        delete task->task_data;
    }

    this->onOrderBook(data);
    delete task;
};

void QuoteApi::processSubTickByTick(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["ticker"] = task_data->ticker;
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

	this->onSubTickByTick(data, error, task->task_last);
	delete task;
};

void QuoteApi::processUnSubTickByTick(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["ticker"] = task_data->ticker;
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

	this->onUnSubTickByTick(data, error, task->task_last);
	delete task;
};

void QuoteApi::processTickByTick(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		XTPTBT *task_data = (XTPTBT*)task->task_data;


		data["exchange_id"] = (int)task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		//data["seq"] = task_data->seq;
		data["data_time"] = task_data->data_time;
		data["type"] = (int)task_data->type;

		if (task_data->type == XTP_TBT_ENTRUST)
		{
			data["channel_no"] = task_data->entrust.channel_no;
			data["seq"] = task_data->entrust.seq;
			data["price"] = task_data->entrust.price;
			data["qty"] = task_data->entrust.qty;
			data["side"] = task_data->entrust.side;
			data["ord_type"] = task_data->entrust.ord_type;
		}
		else
		{
			data["channel_no"] = task_data->trade.channel_no;
			data["seq"] = task_data->trade.seq;
			data["price"] = task_data->trade.price;
			data["qty"] = task_data->trade.qty;
			data["money"] = task_data->trade.money;
			data["bid_no"] = task_data->trade.bid_no;
			data["ask_no"] = task_data->trade.ask_no;
			data["trade_flag"] = task_data->trade.trade_flag;
		}

		delete task->task_data;
	}

	this->onTickByTick(data);
	delete task;
};

void QuoteApi::processSubscribeAllMarketData(Task *task)
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

	this->onSubscribeAllMarketData(error);
	delete task;
};

void QuoteApi::processUnSubscribeAllMarketData(Task *task)
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

	this->onUnSubscribeAllMarketData(error);
	delete task;
};

void QuoteApi::processSubscribeAllOrderBook(Task *task)
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

	this->onSubscribeAllOrderBook(error);
	delete task;
};

void QuoteApi::processUnSubscribeAllOrderBook(Task *task)
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

	this->onUnSubscribeAllOrderBook(error);
	delete task;
};

void QuoteApi::processSubscribeAllTickByTick(Task *task)
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

	this->onSubscribeAllTickByTick(error);
	delete task;
};

void QuoteApi::processUnSubscribeAllTickByTick(Task *task)
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

	this->onUnSubscribeAllTickByTick(error);
	delete task;
};

void QuoteApi::processQueryAllTickers(Task *task)
{
    PyLock lock;

		//手动修改
		dict data;
		if (task->task_data)
		{
			XTPQSI *task_data = (XTPQSI*)task->task_data;
			data["exchange_id"] = (int)task_data->exchange_id;
			data["ticker"] = task_data->ticker;
			data["ticker_name"] = task_data->ticker_name;
			data["ticker_type"] = (int)task_data->ticker_type;
			data["pre_close_price"] = task_data->pre_close_price;
			data["upper_limit_price"] = task_data->upper_limit_price;
			data["lower_limit_price"] = task_data->lower_limit_price;
			data["price_tick"] = task_data->price_tick;
			data["buy_qty_unit"] = task_data->buy_qty_unit;
			data["sell_qty_unit"] = task_data->sell_qty_unit;

			delete task->task_data;
		}

    dict error;
    if (task->task_error)
    {
        XTPRI *task_error = (XTPRI*) task->task_error;
        error["error_id"] = task_error->error_id;
        error["error_msg"] = task_error->error_msg;
        delete task->task_error;
    }

    this->onQueryAllTickers(data, error, task->task_last);
    delete task;
};

void QuoteApi::processQueryTickersPriceInfo(Task *task)
{
	PyLock lock;

	//手动修改
	dict data;
	if (task->task_data)
	{
		XTPTPI *task_data = (XTPTPI*)task->task_data;
		data["exchange_id"] = (int)task_data->exchange_id;
		data["ticker"] = task_data->ticker;
		data["last_price"] = task_data->last_price;

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

	this->onQueryTickersPriceInfo(data, error, task->task_last);
	delete task;
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void QuoteApi::createQuoteApi(int clientid, string path)
{
	this->api = XTP::API::QuoteApi::CreateQuoteApi(clientid, path.c_str());
	this->api->RegisterSpi(this);
};

void QuoteApi::release()
{
	this->api->Release();
};

int QuoteApi::exit()
{
	//该函数在原生API里没有，用于安全退出API用，原生的join似乎不太稳定
	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	return 1;
};

string QuoteApi::getTradingDay()
{
	string day = this->api->GetTradingDay();
	return day;
};

string QuoteApi::getApiVersion()
{
	string version = this->api->GetApiVersion();
	return version;
};

dict QuoteApi::getApiLastError()
{
	XTPRI *error = this->api->GetApiLastError();
	dict err;

	err["error_id"] = error->error_id;
	err["error_msg"] = error->error_msg;

	return err;
};

void QuoteApi::setUDPBufferSize(int size)
{
	this->api->SetUDPBufferSize(size);
};

void QuoteApi::setHeartBeatInterval(int interval)
{
	this->api->SetHeartBeatInterval(interval);
};

int QuoteApi::subscribeMarketData(string ticker, int exchange)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeMarketData(myreq, 1, (XTP_EXCHANGE_TYPE) exchange);
	return i;
};

int QuoteApi::unSubscribeMarketData(string ticker, int exchange)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };;
	int i = this->api->UnSubscribeMarketData(myreq, 1, (XTP_EXCHANGE_TYPE) exchange);
	return i;
};

int QuoteApi::subscribeOrderBook(string ticker, int exchange)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeOrderBook(myreq, 1, (XTP_EXCHANGE_TYPE) exchange);
	return i;
};

int QuoteApi::unSubscribeOrderBook(string ticker, int exchange)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };;
	int i = this->api->UnSubscribeOrderBook(myreq, 1, (XTP_EXCHANGE_TYPE) exchange);
	return i;
};

int QuoteApi::subscribeTickByTick(string ticker, int exchange)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };;
	int i = this->api->SubscribeTickByTick(myreq, 1, (XTP_EXCHANGE_TYPE)exchange);
	return i;
};

int QuoteApi::unSubscribeTickByTick(string ticker, int exchange)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };;
	int i = this->api->UnSubscribeTickByTick(myreq, 1, (XTP_EXCHANGE_TYPE)exchange);
	return i;
};

void QuoteApi::subscribeAllMarketData()
{
	this->api->SubscribeAllMarketData();
};

void QuoteApi::unSubscribeAllMarketData()
{
	this->api->UnSubscribeAllMarketData();
};

void QuoteApi::subscribeAllOrderBook()
{
	this->api->SubscribeAllOrderBook();
};

void QuoteApi::unSubscribeAllOrderBook()
{
	this->api->UnSubscribeAllOrderBook();
};

void QuoteApi::subscribeAllTickByTick()
{
	this->api->SubscribeAllTickByTick();
};

void QuoteApi::unSubscribeAllTickByTick()
{
	this->api->UnSubscribeAllTickByTick();
};

int QuoteApi::login(string ip, int port, string user, string password, int socktype)
{
	int i = this->api->Login(ip.c_str(), port, user.c_str(), password.c_str(), (XTP_PROTOCOL_TYPE)socktype);
	return i;
};

int QuoteApi::logout()
{
	int i = this->api->Logout();
	return i;
};

int QuoteApi::queryAllTickers(int exchange)
{
	int i = this->api->QueryAllTickers((XTP_EXCHANGE_TYPE)exchange);
	return i;
};

int QuoteApi::queryTickersPriceInfo(string ticker, int exchange)
{
	char* buffer = (char*)ticker.c_str();
	char* myreq[1] = { buffer };;
	int i = this->api->QueryTickersPriceInfo(myreq, 1, (XTP_EXCHANGE_TYPE)exchange);
	return i;
}

int QuoteApi::queryAllTickersPriceInfo()
{
	int i = this->api->QueryAllTickersPriceInfo();
	return i;
}

///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

struct QuoteApiWrap : QuoteApi, wrapper < QuoteApi >
{
	virtual void onDisconnected(int reason)
	{
	    try
	    {
	        this->get_override("onDisconnected")(reason);
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

	virtual void onSubMarketData(dict data, dict error, bool last)
	{
	    try
	    {
	        this->get_override("onSubMarketData")(data, error, last);
	    }
	    catch (error_already_set const &)
	    {
	        PyErr_Print();
	    }
	};

	virtual void onUnSubMarketData(dict data, dict error, bool last)
	{
	    try
	    {
	        this->get_override("onUnSubMarketData")(data, error, last);
	    }
	    catch (error_already_set const &)
	    {
	        PyErr_Print();
	    }
	};

	virtual void onDepthMarketData(dict data)
	{
	    try
	    {
	        this->get_override("onDepthMarketData")(data);
	    }
	    catch (error_already_set const &)
	    {
	        PyErr_Print();
	    }
	};

	virtual void onSubOrderBook(dict data, dict error, bool last)
	{
	    try
	    {
	        this->get_override("onSubOrderBook")(data, error, last);
	    }
	    catch (error_already_set const &)
	    {
	        PyErr_Print();
	    }
	};

	virtual void onUnSubOrderBook(dict data, dict error, bool last)
	{
	    try
	    {
	        this->get_override("onUnSubOrderBook")(data, error, last);
	    }
	    catch (error_already_set const &)
	    {
	        PyErr_Print();
	    }
	};

	virtual void onOrderBook(dict data)
	{
	    try
	    {
	        this->get_override("onOrderBook")(data);
	    }
	    catch (error_already_set const &)
	    {
	        PyErr_Print();
	    }
	};

	virtual void onSubTickByTick(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onSubTickByTick")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onUnSubTickByTick(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onUnSubTickByTick")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onTickByTick(dict data)
	{
		try
		{
			this->get_override("onTickByTick")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onSubscribeAllMarketData(dict data)
	{
		try
		{
			this->get_override("onSubscribeAllMarketData")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onUnSubscribeAllMarketData(dict data)
	{
		try
		{
			this->get_override("onUnSubscribeAllMarketData")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onSubscribeAllOrderBook(dict data)
	{
		try
		{
			this->get_override("onSubscribeAllOrderBook")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onUnSubscribeAllOrderBook(dict data)
	{
		try
		{
			this->get_override("onUnSubscribeAllOrderBook")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onSubscribeAllTickByTick(dict data)
	{
		try
		{
			this->get_override("onSubscribeAllTickByTick")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onUnSubscribeAllTickByTick(dict data)
	{
		try
		{
			this->get_override("onUnSubscribeAllTickByTick")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onQueryAllTickers(dict data, dict error, bool last)
	{
	    try
	    {
	        this->get_override("onQueryAllTickers")(data, error, last);
	    }
	    catch (error_already_set const &)
	    {
	        PyErr_Print();
	    }
	};

	virtual void onQueryTickersPriceInfo(dict data, dict error, bool last)
	{
		try
		{
			this->get_override("onQueryTickersPriceInfo")(data, error, last);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};
};


BOOST_PYTHON_MODULE(vnxtpquote)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<QuoteApiWrap, boost::noncopyable>("QuoteApi")
		.def("createQuoteApi", &QuoteApiWrap::createQuoteApi)
		.def("release", &QuoteApiWrap::release)
		.def("exit", &QuoteApiWrap::exit)
		.def("getTradingDay", &QuoteApiWrap::getTradingDay)
		.def("getApiVersion", &QuoteApiWrap::getApiVersion)
		.def("getApiLastError", &QuoteApiWrap::getApiLastError)
		.def("setUDPBufferSize", &QuoteApiWrap::setUDPBufferSize)
		.def("setHeartBeatInterval", &QuoteApiWrap::setHeartBeatInterval)
		.def("subscribeMarketData", &QuoteApiWrap::subscribeMarketData)
		.def("unSubscribeMarketData", &QuoteApiWrap::unSubscribeMarketData)
		.def("subscribeOrderBook", &QuoteApiWrap::subscribeOrderBook)
		.def("unSubscribeOrderBook", &QuoteApiWrap::unSubscribeOrderBook)
		.def("subscribeTickByTick", &QuoteApiWrap::subscribeTickByTick)
		.def("unSubscribeTickByTick", &QuoteApiWrap::unSubscribeTickByTick)
		.def("subscribeAllMarketData", &QuoteApiWrap::subscribeAllMarketData)
		.def("unSubscribeAllMarketData", &QuoteApiWrap::unSubscribeAllMarketData)
		.def("subscribeAllOrderBook", &QuoteApiWrap::subscribeAllOrderBook)
		.def("unSubscribeAllOrderBook", &QuoteApiWrap::unSubscribeAllOrderBook)
		.def("subscribeAllTickByTick", &QuoteApiWrap::subscribeAllTickByTick)
		.def("unSubscribeAllTickByTick", &QuoteApiWrap::unSubscribeAllTickByTick)
		.def("login", &QuoteApiWrap::login)
		.def("logout", &QuoteApiWrap::logout)
		.def("queryAllTickers", &QuoteApiWrap::queryAllTickers)
		.def("queryTickersPriceInfo", &QuoteApiWrap::queryTickersPriceInfo)
		.def("queryAllTickersPriceInfo", &QuoteApiWrap::queryAllTickersPriceInfo)

		.def("onDisconnected", pure_virtual(&QuoteApiWrap::onDisconnected))
		.def("onError", pure_virtual(&QuoteApiWrap::onError))
		.def("onSubMarketData", pure_virtual(&QuoteApiWrap::onSubMarketData))
		.def("onUnSubMarketData", pure_virtual(&QuoteApiWrap::onUnSubMarketData))
		.def("onDepthMarketData", pure_virtual(&QuoteApiWrap::onDepthMarketData))
		.def("onSubOrderBook", pure_virtual(&QuoteApiWrap::onSubOrderBook))
		.def("onUnSubOrderBook", pure_virtual(&QuoteApiWrap::onUnSubOrderBook))
		.def("onOrderBook", pure_virtual(&QuoteApiWrap::onOrderBook))
		.def("onSubTickByTick", pure_virtual(&QuoteApiWrap::onSubTickByTick))
		.def("onUnSubTickByTick", pure_virtual(&QuoteApiWrap::onUnSubTickByTick))
		.def("onTickByTick", pure_virtual(&QuoteApiWrap::onTickByTick))
		.def("onSubscribeAllMarketData", pure_virtual(&QuoteApiWrap::onSubscribeAllMarketData))
		.def("onUnSubscribeAllMarketData", pure_virtual(&QuoteApiWrap::onUnSubscribeAllMarketData))
		.def("onSubscribeAllOrderBook", pure_virtual(&QuoteApiWrap::onSubscribeAllOrderBook))
		.def("onUnSubscribeAllOrderBook", pure_virtual(&QuoteApiWrap::onUnSubscribeAllOrderBook))
		.def("onSubscribeAllTickByTick", pure_virtual(&QuoteApiWrap::onSubscribeAllTickByTick))
		.def("onUnSubscribeAllTickByTick", pure_virtual(&QuoteApiWrap::onUnSubscribeAllTickByTick))
		.def("onQueryAllTickers", pure_virtual(&QuoteApiWrap::onQueryAllTickers))
		.def("onQueryTickersPriceInfo", pure_virtual(&QuoteApiWrap::onQueryTickersPriceInfo))
		;
};
