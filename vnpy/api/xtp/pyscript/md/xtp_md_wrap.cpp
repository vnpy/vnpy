virtual void onDisconnected()
{
    try
    {
        this->get_override("onDisconnected")();
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

virtual void onMarketData(dict data)
{
    try
    {
        this->get_override("onMarketData")(data);
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

