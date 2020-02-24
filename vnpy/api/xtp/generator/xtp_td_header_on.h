virtual void onDisconnected(int reqid, int reqid) {};

virtual void onError(const dict &error) {};

virtual void onOrderEvent(const dict &data, const dict &error, int reqid) {};

virtual void onTradeEvent(const dict &data, int reqid) {};

virtual void onCancelOrderError(const dict &data, const dict &error, int reqid) {};

virtual void onQueryOrder(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onQueryTrade(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onQueryPosition(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onQueryAsset(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onQueryStructuredFund(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onQueryFundTransfer(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onFundTransfer(const dict &data, const dict &error, int reqid) {};

virtual void onQueryETF(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onQueryETFBasket(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onQueryIPOInfoList(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onQueryIPOQuotaInfo(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onQueryOptionAuctionInfo(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onCreditCashRepay(const dict &data, const dict &error, int reqid) {};

virtual void onQueryCreditCashRepayInfo(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onQueryCreditFundInfo(const dict &data, const dict &error, int reqid, int reqid) {};

virtual void onQueryCreditDebtInfo(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onQueryCreditTickerDebtInfo(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onQueryCreditAssetDebtInfo(const dict &data, const dict &error, int reqid, int reqid) {};

virtual void onQueryCreditTickerAssignInfo(const dict &data, const dict &error, int reqid, bool last, int reqid) {};

virtual void onQueryCreditExcessStock(const dict &data, const dict &error, int reqid, int reqid) {};

