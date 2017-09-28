void TraderApi::processDisconnected(Task *task)
{
    PyLock lock;
    this->onDisconnected(task->task_id);
    delete task;
};

void TraderApi::processError(Task *task)
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

void TraderApi::processOrderEvent(Task *task)
{
    PyLock lock;
    dict data;
    if (task->task_data)
    {
        XTPOrderInfo *task_data = (XTPOrderInfo*) task->task_data;
        data["business_type"] = (int)task_data->business_type;
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
        data["business_type"] = (int)task_data->business_type;
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

    this->onOrderEvent(data, error);
    delete task;
};

void TraderApi::processTradeEvent(Task *task)
{
    PyLock lock;
    dict data;
    if (task->task_data)
    {
        XTPTradeReport *task_data = (XTPTradeReport*) task->task_data;
        data["business_type"] = (int)task_data->business_type;
        data["trade_amount"] = task_data->trade_amount;
        data["exec_id"] = task_data->exec_id;
        data["trade_type"] = task_data->trade_type;
        data["order_client_id"] = task_data->order_client_id;
        data["order_exch_id"] = task_data->order_exch_id;
        data["price"] = task_data->price;
        data["report_index"] = task_data->report_index;
        data["local_order_id"] = task_data->local_order_id;
        data["branch_pbu"] = task_data->branch_pbu;
        data["trade_time"] = task_data->trade_time;
        data["order_xtp_id"] = task_data->order_xtp_id;
        data["ticker"] = task_data->ticker;
        data["side"] = (int)task_data->side;
        data["market"] = (int)task_data->market;
        data["quantity"] = task_data->quantity;
        data["business_type"] = (int)task_data->business_type;
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
        XTPOrderCancelInfo *task_data = (XTPOrderCancelInfo*) task->task_data;
        data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
        data["order_xtp_id"] = task_data->order_xtp_id;
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

    this->onCancelOrderError(data, error);
    delete task;
};

void TraderApi::processQueryOrder(Task *task)
{
    PyLock lock;
    dict data;
    if (task->task_data)
    {
        XTPQueryOrderRsp *task_data = (XTPQueryOrderRsp*) task->task_data;
        data["business_type"] = (int)task_data->business_type;
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
        XTPRI *task_error = (XTPRI*) task->task_error;
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
        XTPQueryTradeRsp *task_data = (XTPQueryTradeRsp*) task->task_data;
        data["business_type"] = (int)task_data->business_type;
        data["trade_amount"] = task_data->trade_amount;
        data["exec_id"] = task_data->exec_id;
        data["trade_type"] = task_data->trade_type;
        data["order_client_id"] = task_data->order_client_id;
        data["order_exch_id"] = task_data->order_exch_id;
        data["price"] = task_data->price;
        data["report_index"] = task_data->report_index;
        data["local_order_id"] = task_data->local_order_id;
        data["branch_pbu"] = task_data->branch_pbu;
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
        XTPRI *task_error = (XTPRI*) task->task_error;
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
        XTPQueryStkPositionRsp *task_data = (XTPQueryStkPositionRsp*) task->task_data;
        data["ticker_name"] = task_data->ticker_name;
        data["sellable_qty"] = task_data->sellable_qty;
        data["unrealized_pnl"] = task_data->unrealized_pnl;
        data["avg_price"] = task_data->avg_price;
        data["total_qty"] = task_data->total_qty;
        data["ticker"] = task_data->ticker;
        data["market"] = (int)task_data->market;
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

    this->onQueryPosition(data, error, task->task_id, task->task_last);
    delete task;
};

void TraderApi::processQueryAsset(Task *task)
{
    PyLock lock;
    dict data;
    if (task->task_data)
    {
        XTPQueryAssetRsp *task_data = (XTPQueryAssetRsp*) task->task_data;
        data["fund_sell_fee"] = task_data->fund_sell_fee;
        data["security_asset"] = task_data->security_asset;
        data["buying_power"] = task_data->buying_power;
        data["withholding_amount"] = task_data->withholding_amount;
        data["fund_buy_amount"] = task_data->fund_buy_amount;
        data["fund_buy_fee"] = task_data->fund_buy_fee;
        data["fund_sell_amount"] = task_data->fund_sell_amount;
        data["total_asset"] = task_data->total_asset;
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

    this->onQueryAsset(data, error, task->task_id, task->task_last);
    delete task;
};
