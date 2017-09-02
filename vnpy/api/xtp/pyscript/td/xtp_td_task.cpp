void TraderApi::OnDisconnected(uint64_t session_id, int reason) 
{
    Task* task = new Task();
    task->task_name = ONDISCONNECTED;

    if (ession_id)
    {
        uint64_t *task_data = new uint64_t();
        *task_data = session_id;
        task->task_data = task_data;
    }
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

