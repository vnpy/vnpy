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

void QuoteApi::OnMarketData(XTPMD *market_data) 
{
    Task* task = new Task();
    task->task_name = ONMARKETDATA;

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

void QuoteApi::OnQueryAllTickers(XTPQSI* ticker_info, XTPRI *error_info, bool is_last) 
{
    Task* task = new Task();
    task->task_name = ONQUERYALLTICKERS;

    if (icker_info)
    {
        XTPQSI* *task_data = new XTPQSI*();
        *task_data = ticker_info;
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

