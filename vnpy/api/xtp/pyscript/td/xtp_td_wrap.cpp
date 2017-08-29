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

