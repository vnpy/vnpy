int TdApi::login(string svr_ip, int svr_port, const dict &req, string terminal_info)
{
	AccountInfo myreq = AccountInfo();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "account_id", myreq.account_id);
	getInt16_t(req, "account_type", &myreq.account_type);
	getString(req, "account_pwd", myreq.account_pwd);
	getString(req, "cust_orgid", myreq.cust_orgid);
	getString(req, "cust_branchid", myreq.cust_branchid);
	getString(req, "cl_system_id", myreq.cl_system_id);
	int i = this->api->Login(svr_ip.c_str(), svr_port, &myreq, terminal_info.c_str());
	return i;
};

	int i = this->api->getCounterType();
	return i;
};

int TdApi::getSecuidInfo(const dict &req, int count)
{
	SecuidInfo myreq = SecuidInfo();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "market", myreq.market);
	getString(req, "secuid", myreq.secuid);
	int i = this->api->GetSecuidInfo(&myreq, count);
	return i;
};

int TdApi::getApiLocalAddr(const dict &req)
{
	IpAddr myreq = IpAddr();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "ip", &myreq.ip);
	getInt(req, "port", &myreq.port);
	int i = this->api->GetApiLocalAddr(&myreq);
	return i;
};

int TdApi::order(const dict &req, int request_id)
{
	OrderReq myreq = OrderReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "cl_order_id", myreq.cl_order_id);
	getString(req, "symbol", myreq.symbol);
	getInt16_t(req, "order_type", &myreq.order_type);
	getInt16_t(req, "side", &myreq.side);
	getInt64_t(req, "volume", &myreq.volume);
	getInt64_t(req, "price", &myreq.price);
	getInt16_t(req, "order_flag", &myreq.order_flag);
	int i = this->api->Order(&myreq, request_id);
	return i;
};

int TdApi::batchOrder(const dict &req, int count, int request_id)
{
	OrderReq myreq = OrderReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "cl_order_id", myreq.cl_order_id);
	getString(req, "symbol", myreq.symbol);
	getInt16_t(req, "order_type", &myreq.order_type);
	getInt16_t(req, "side", &myreq.side);
	getInt64_t(req, "volume", &myreq.volume);
	getInt64_t(req, "price", &myreq.price);
	getInt16_t(req, "order_flag", &myreq.order_flag);
	int i = this->api->BatchOrder(&myreq, count, request_id);
	return i;
};

int TdApi::cancelOrder(const dict &req, int request_id)
{
	CancelReq myreq = CancelReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "order_id", myreq.order_id);
	getString(req, "cl_order_id", myreq.cl_order_id);
	getString(req, "cl_cancel_id", myreq.cl_cancel_id);
	int i = this->api->CancelOrder(&myreq, request_id);
	return i;
};

int TdApi::batchCancelOrder(const dict &req, int count, int request_id)
{
	CancelReq myreq = CancelReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "order_id", myreq.order_id);
	getString(req, "cl_order_id", myreq.cl_order_id);
	getString(req, "cl_cancel_id", myreq.cl_cancel_id);
	int i = this->api->BatchCancelOrder(&myreq, count, request_id);
	return i;
};

int TdApi::queryOrder(string order_id, int request_id, string market)
{
	int i = this->api->QueryOrder(order_id.c_str(), request_id, market.c_str());
	return i;
};

int TdApi::queryOrderByCode(string symbol, int request_id)
{
	int i = this->api->QueryOrderByCode(symbol.c_str(), request_id);
	return i;
};

int TdApi::queryOrders(string pos_str, int query_num, int request_id, int query_flag, string market)
{
	int i = this->api->QueryOrders(pos_str.c_str(), query_num, request_id, query_flag, market.c_str());
	return i;
};

int TdApi::queryTradeByOrderId(string order_id, int request_id, string market)
{
	int i = this->api->QueryTradeByOrderId(order_id.c_str(), request_id, market.c_str());
	return i;
};

int TdApi::queryTradeByCode(string symbol, int request_id)
{
	int i = this->api->QueryTradeByCode(symbol.c_str(), request_id);
	return i;
};

int TdApi::queryTrades(string pos_str, int query_num, int request_id, string market, bool filter_etf)
{
	int i = this->api->QueryTrades(pos_str.c_str(), query_num, request_id, market.c_str(), filter_etf);
	return i;
};

int TdApi::queryETFTrades(string pos_str, int query_num, int request_id, string market)
{
	int i = this->api->QueryETFTrades(pos_str.c_str(), query_num, request_id, market.c_str());
	return i;
};

int TdApi::queryPosition(string symbol, int request_id)
{
	int i = this->api->QueryPosition(symbol.c_str(), request_id);
	return i;
};

int TdApi::queryPositions(string pos_str, int query_num, int request_id, string market)
{
	int i = this->api->QueryPositions(pos_str.c_str(), query_num, request_id, market.c_str());
	return i;
};

int TdApi::queryCash(int request_id, string market)
{
	int i = this->api->QueryCash(request_id, market.c_str());
	return i;
};

int TdApi::queryJZJYAvailFund(int request_id)
{
	int i = this->api->QueryJZJYAvailFund(request_id);
	return i;
};

int TdApi::transferFundInAndOut(int transfer_side, int transfer_value, int request_id, string market)
{
	int i = this->api->TransferFundInAndOut(transfer_side, transfer_value, request_id, market.c_str());
	return i;
};

int TdApi::transferFundBetweenSecuid(string fund_out_market, string fund_in_market, int transfer_value, int request_id)
{
	int i = this->api->TransferFundBetweenSecuid(fund_out_market.c_str(), fund_in_market.c_str(), transfer_value, request_id);
	return i;
};

int TdApi::queryETFs(int request_id)
{
	int i = this->api->QueryETFs(request_id);
	return i;
};

int TdApi::queryETFStocks(string first_symbol, int request_id)
{
	int i = this->api->QueryETFStocks(first_symbol.c_str(), request_id);
	return i;
};

int TdApi::queryMaxOrderQty(string symbol, int order_type, int side, int price, int request_id)
{
	int i = this->api->QueryMaxOrderQty(symbol.c_str(), order_type, side, price, request_id);
	return i;
};

int TdApi::queryIPOMaxPurchase(int request_id)
{
	int i = this->api->QueryIPOMaxPurchase(request_id);
	return i;
};

int TdApi::queryIPOStock(int request_id, int query_flag)
{
	int i = this->api->QueryIPOStock(request_id, query_flag);
	return i;
};

int TdApi::queryIPODistribution(int start_date, int end_date, string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryIPODistribution(start_date, end_date, pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::queryIPOLottery(int start_date, int end_date, string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryIPOLottery(start_date, end_date, pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::querySecurityBaseInfo(int request_id, string symbol)
{
	int i = this->api->QuerySecurityBaseInfo(request_id, symbol.c_str());
	return i;
};

int TdApi::creditMortgageInOut(const dict &req, int request_id)
{
	CreditMortgageInOutReq myreq = CreditMortgageInOutReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "cl_order_id", myreq.cl_order_id);
	getString(req, "symbol", myreq.symbol);
	getInt16_t(req, "side", &myreq.side);
	getInt32_t(req, "volume", &myreq.volume);
	int i = this->api->CreditMortgageInOut(&myreq, request_id);
	return i;
};

int TdApi::creditStockBack(const dict &req, int request_id)
{
	CreditStockBackReq myreq = CreditStockBackReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "cl_order_id", myreq.cl_order_id);
	getString(req, "symbol", myreq.symbol);
	getInt32_t(req, "volume", &myreq.volume);
	int i = this->api->CreditStockBack(&myreq, request_id);
	return i;
};

int TdApi::creditPayBack(int back_amt, int request_id)
{
	int i = this->api->CreditPayBack(back_amt, request_id);
	return i;
};

int TdApi::creditPayBackByOrder(string order_id, int order_date, int back_amt, int request_id)
{
	int i = this->api->CreditPayBackByOrder(order_id.c_str(), order_date, back_amt, request_id);
	return i;
};

int TdApi::queryCreditStock(string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryCreditStock(pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::queryCreditMortgageHold(string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryCreditMortgageHold(pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::queryCreditAssets(int request_id)
{
	int i = this->api->QueryCreditAssets(request_id);
	return i;
};

int TdApi::queryCreditFinance(string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryCreditFinance(pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::queryCreditShortsell(string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryCreditShortsell(pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::queryCreditRepayAmount(int request_id)
{
	int i = this->api->QueryCreditRepayAmount(request_id);
	return i;
};

int TdApi::queryCreditRepayStock(string market, string code, int request_id)
{
	int i = this->api->QueryCreditRepayStock(market.c_str(), code.c_str(), request_id);
	return i;
};

int TdApi::queryCreditSecuritySellQty(string market, string code, int request_id)
{
	int i = this->api->QueryCreditSecuritySellQty(market.c_str(), code.c_str(), request_id);
	return i;
};

int TdApi::querySecuidRight(string market, int secuid_right, int request_id)
{
	int i = this->api->QuerySecuidRight(market.c_str(), secuid_right, request_id);
	return i;
};

int TdApi::queryHKRate(string market, int request_id)
{
	int i = this->api->QueryHKRate(market.c_str(), request_id);
	return i;
};

int TdApi::queryHKStock(string market, int request_id)
{
	int i = this->api->QueryHKStock(market.c_str(), request_id);
	return i;
};

int TdApi::queryHKFund(int request_id)
{
	int i = this->api->QueryHKFund(request_id);
	return i;
};

int TdApi::queryHKMinPriceUnit(string market, int request_id)
{
	int i = this->api->QueryHKMinPriceUnit(market.c_str(), request_id);
	return i;
};

int TdApi::queryHKTradeCalendar(int start_date, int end_date, int request_id)
{
	int i = this->api->QueryHKTradeCalendar(start_date, end_date, request_id);
	return i;
};

int TdApi::queryLockSecurityDetail(int begin_date, int end_date, int request_id, string market, string code)
{
	int i = this->api->QueryLockSecurityDetail(begin_date, end_date, request_id, market.c_str(), code.c_str());
	return i;
};

int TdApi::extendLockSecurity(const dict &req, int request_id)
{
	ExtendLockSecurityReq myreq = ExtendLockSecurityReq();
	memset(&myreq, 0, sizeof(myreq));
	getInt32_t(req, "sys_date", &myreq.sys_date);
	getString(req, "sno", myreq.sno);
	getInt32_t(req, "apply_delay_days", &myreq.apply_delay_days);
	getInt64_t(req, "apply_used_fee_rate", &myreq.apply_used_fee_rate);
	getInt64_t(req, "apply_unused_fee_rate", &myreq.apply_unused_fee_rate);
	getInt32_t(req, "apply_delay_qty", &myreq.apply_delay_qty);
	getString(req, "symbol", myreq.symbol);
	int i = this->api->ExtendLockSecurity(&myreq, request_id);
	return i;
};

int TdApi::queryLockSecurityExtension(int begin_date, int end_date, int request_id)
{
	int i = this->api->QueryLockSecurityExtension(begin_date, end_date, request_id);
	return i;
};

int TdApi::cancelExtendLockSecurity(int apply_date, string apply_sno, int request_id)
{
	int i = this->api->CancelExtendLockSecurity(apply_date, apply_sno.c_str(), request_id);
	return i;
};

int TdApi::queryTransferFundHistory(int request_id)
{
	int i = this->api->QueryTransferFundHistory(request_id);
	return i;
};

