int queryOrderByXTPID(int order_xtp_id, int session_id, int request_id);

int queryOrders(const dict &req, int session_id, int request_id);

int queryTradesByXTPID(int order_xtp_id, int session_id, int request_id);

int queryTrades(const dict &req, int session_id, int request_id);

int queryPosition(string ticker, int session_id, int request_id);

int queryAsset(int session_id, int request_id);

int queryStructuredFund(const dict &req, int session_id, int request_id);

int queryFundTransfer(const dict &req, int session_id, int request_id);

int queryETF(const dict &req, int session_id, int request_id);

int queryETFTickerBasket(const dict &req, int session_id, int request_id);

int queryIPOInfoList(int session_id, int request_id);

int queryIPOQuotaInfo(int session_id, int request_id);

int queryOptionAuctionInfo(const dict &req, int session_id, int request_id);

int queryCreditCashRepayInfo(int session_id, int request_id);

int queryCreditFundInfo(int session_id, int request_id);

int queryCreditDebtInfo(int session_id, int request_id);

int queryCreditTickerDebtInfo(const dict &req, int session_id, int request_id);

int queryCreditAssetDebtInfo(int session_id, int request_id);

int queryCreditTickerAssignInfo(const dict &req, int session_id, int request_id);

int queryCreditExcessStock(const dict &req, int session_id, int request_id);

