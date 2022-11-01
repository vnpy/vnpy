int MdApi::reqUtpLogin(const dict &req, int reqid)
{
	ReqUtpLoginField_t myreq = ReqUtpLoginField_t();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "developer_code", myreq.developer_code);
	getString(req, "developer_license", myreq.developer_license);
	getString(req, "user_id", myreq.user_id);
	getString(req, "user_password", myreq.user_password);
	getString(req, "user_one_time_password", myreq.user_one_time_password);
	getString(req, "user_ca_info", myreq.user_ca_info);
	int i = this->api->ReqUtpLogin(myreq, reqid);
	return i;
};

int MdApi::reqSubscribe(const dict &req, int reqid)
{
	ReqSubscribeField_t myreq = ReqSubscribeField_t();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "routing_key", myreq.routing_key);
	int i = this->api->ReqSubscribe(myreq, reqid);
	return i;
};

int MdApi::reqUnSubscribe(const dict &req, int reqid)
{
	ReqUnSubscribeField_t myreq = ReqUnSubscribeField_t();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "routing_key", myreq.routing_key);
	int i = this->api->ReqUnSubscribe(myreq, reqid);
	return i;
};

int MdApi::reqAuthUserPasswor(const dict &req, int reqid)
{
	ReqAuthUserPassworField_t myreq = ReqAuthUserPassworField_t();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "user_id", myreq.user_id);
	getString(req, "password", myreq.password);
	getInt(req, "save_int", &myreq.save_int);
	getDouble(req, "save_double", &myreq.save_double);
	getString(req, "save_string", myreq.save_string);
	int i = this->api->ReqAuthUserPasswor(myreq, reqid);
	return i;
};

int MdApi::reqQryExchange(const dict &req, int reqid)
{
	ReqQryExchangeField_t myreq = ReqQryExchangeField_t();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "oms_server_id", &myreq.oms_server_id);
	int i = this->api->ReqQryExchange(myreq, reqid);
	return i;
};

int MdApi::reqQryInstrument(const dict &req, int reqid)
{
	ReqQryInstrumentField_t myreq = ReqQryInstrumentField_t();
	memset(&myreq, 0, sizeof(myreq));
	getInt(req, "oms_server_id", &myreq.oms_server_id);
	getString(req, "exchange_id", myreq.exchange_id);
	getString(req, "product_id", myreq.product_id);
	getString(req, "instrument_id", myreq.instrument_id);
	getChar(req, "product_class", &myreq.product_class);
	int i = this->api->ReqQryInstrument(myreq, reqid);
	return i;
};

