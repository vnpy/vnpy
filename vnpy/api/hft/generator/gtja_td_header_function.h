int login(string svr_ip, int svr_port, const dict &req, string terminal_info);

int getCounterType();

int getSecuidInfo(const dict &req, int count);

int getApiLocalAddr(const dict &req);

int order(const dict &req, int request_id);

int batchOrder(const dict &req, int count, int request_id);

int cancelOrder(const dict &req, int request_id);

int batchCancelOrder(const dict &req, int count, int request_id);

int queryOrder(string order_id, int request_id, string market);

int queryOrderByCode(string symbol, int request_id);

int queryOrders(string pos_str, int query_num, int request_id, int query_flag, string market);

int queryTradeByOrderId(string order_id, int request_id, string market);

int queryTradeByCode(string symbol, int request_id);

int queryTrades(string pos_str, int query_num, int request_id, string market, bool filter_etf);

int queryETFTrades(string pos_str, int query_num, int request_id, string market);

int queryPosition(string symbol, int request_id);

int queryPositions(string pos_str, int query_num, int request_id, string market);

int queryCash(int request_id, string market);

int queryJZJYAvailFund(int request_id);

int transferFundInAndOut(int transfer_side, int transfer_value, int request_id, string market);

int transferFundBetweenSecuid(string fund_out_market, string fund_in_market, int transfer_value, int request_id);

int queryETFs(int request_id);

int queryETFStocks(string first_symbol, int request_id);

int queryMaxOrderQty(string symbol, int order_type, int side, int price, int request_id);

int queryIPOMaxPurchase(int request_id);

int queryIPOStock(int request_id, int query_flag);

int queryIPODistribution(int start_date, int end_date, string pos_str, int query_num, int request_id);

int queryIPOLottery(int start_date, int end_date, string pos_str, int query_num, int request_id);

int querySecurityBaseInfo(int request_id, string symbol);

int creditMortgageInOut(const dict &req, int request_id);

int creditStockBack(const dict &req, int request_id);

int creditPayBack(int back_amt, int request_id);

int creditPayBackByOrder(string order_id, int order_date, int back_amt, int request_id);

int queryCreditStock(string pos_str, int query_num, int request_id);

int queryCreditMortgageHold(string pos_str, int query_num, int request_id);

int queryCreditAssets(int request_id);

int queryCreditFinance(string pos_str, int query_num, int request_id);

int queryCreditShortsell(string pos_str, int query_num, int request_id);

int queryCreditRepayAmount(int request_id);

int queryCreditRepayStock(string market, string code, int request_id);

int queryCreditSecuritySellQty(string market, string code, int request_id);

int querySecuidRight(string market, int secuid_right, int request_id);

int queryHKRate(string market, int request_id);

int queryHKStock(string market, int request_id);

int queryHKFund(int request_id);

int queryHKMinPriceUnit(string market, int request_id);

int queryHKTradeCalendar(int start_date, int end_date, int request_id);

int queryLockSecurityDetail(int begin_date, int end_date, int request_id, string market, string code);

int extendLockSecurity(const dict &req, int request_id);

int queryLockSecurityExtension(int begin_date, int end_date, int request_id);

int cancelExtendLockSecurity(int apply_date, string apply_sno, int request_id);

int queryTransferFundHistory(int request_id);

