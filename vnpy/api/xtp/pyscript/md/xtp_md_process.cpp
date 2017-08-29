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

void QuoteApi::processMarketData(Task *task)
{
    PyLock lock;
    dict data;
    if (task->task_data)
    {
        XTPMD *task_data = (XTPMD*) task->task_data;
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
        data["bid_qty"] = task_data->bid_qty;
        data["ma_bond_bid_price"] = task_data->ma_bond_bid_price;
        data["num_bid_orders"] = task_data->num_bid_orders;
        data["etf_sell_qty"] = task_data->etf_sell_qty;
        data["high_price"] = task_data->high_price;
        data["pre_settlement_price"] = task_data->pre_settlement_price;
        data["etf_buy_count"] = task_data->etf_buy_count;
        data["ma_bond_ask_price"] = task_data->ma_bond_ask_price;
        data["cancel_sell_qty"] = task_data->cancel_sell_qty;
        data["lower_limit_price"] = task_data->lower_limit_price;
        data["bid"] = task_data->bid;
        data["ma_bid_price"] = task_data->ma_bid_price;
        data["warrant_upper_price"] = task_data->warrant_upper_price;
        data["ask_qty"] = task_data->ask_qty;
        data["open_price"] = task_data->open_price;
        data["pe_ratio2"] = task_data->pe_ratio2;
        data["avg_price"] = task_data->avg_price;
        data["ask"] = task_data->ask;
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
        delete task->task_data;
    }

    this->onMarketData(data);
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
        data["data_time"] = task_data->data_time;
        data["bid"] = task_data->bid;
        data["ask_qty"] = task_data->ask_qty;
        data["exchange_id"] = (int)task_data->exchange_id;
        data["bid_qty"] = task_data->bid_qty;
        data["ask"] = task_data->ask;
        data["ticker"] = task_data->ticker;
        delete task->task_data;
    }

    this->onOrderBook(data);
    delete task;
};

void QuoteApi::processQueryAllTickers(Task *task)
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

    this->onQueryAllTickers(error, task->task_last);
    delete task;
};

