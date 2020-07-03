virtual void onConnected(const dict &data, const dict &data, const dict &data) {};

virtual void onDisconnected(const dict &data, const dict &data) {};

virtual void onBusinessReject(const dict &error, const dict &data) {};

virtual void onOrderInsert(const dict &error, const dict &data) {};

virtual void onOrderReport(const dict &error, const dict &data) {};

virtual void onTradeReport(const dict &error, const dict &data) {};

virtual void onCashAssetVariation(const dict &data) {};

virtual void onStockHoldingVariation(const dict &data) {};

virtual void onOptionHoldingVariation(const dict &data) {};

virtual void onOptionUnderlyingHoldingVariation(const dict &data) {};

virtual void onSettlementConfirmedRpt(const dict &error, const dict &data) {};

virtual void onFundTrsfReject(const dict &error, const dict &data) {};

virtual void onFundTrsfReport(const dict &error, const dict &data) {};

virtual void onMarketState(const dict &data) {};

virtual void onNotifyReport(const dict &data) {};

virtual void onReportSynchronizationRsp(const dict &data) {};

virtual void onQueryOrder(const dict &data, const dict &error, int reqid) {};

virtual void onQueryTrade(const dict &data, const dict &error, int reqid) {};

virtual void onQueryCashAsset(const dict &data, const dict &error, int reqid) {};

virtual void onQueryStkHolding(const dict &data, const dict &error, int reqid) {};

virtual void onQueryLotWinning(const dict &data, const dict &error, int reqid) {};

virtual void onQueryCustInfo(const dict &data, const dict &error, int reqid) {};

virtual void onQueryInvAcct(const dict &data, const dict &error, int reqid) {};

virtual void onQueryCommissionRate(const dict &data, const dict &error, int reqid) {};

virtual void onQueryFundTransferSerial(const dict &data, const dict &error, int reqid) {};

virtual void onQueryIssue(const dict &data, const dict &error, int reqid) {};

virtual void onQueryStock(const dict &data, const dict &error, int reqid) {};

virtual void onQueryEtf(const dict &data, const dict &error, int reqid) {};

virtual void onQueryEtfComponent(const dict &data, const dict &error, int reqid) {};

virtual void onQueryMarketState(const dict &data, const dict &error, int reqid) {};

virtual void onQueryOption(const dict &data, const dict &error, int reqid) {};

virtual void onQueryOptHolding(const dict &data, const dict &error, int reqid) {};

virtual void onQueryOptUnderlyingHolding(const dict &data, const dict &error, int reqid) {};

virtual void onQueryOptPositionLimit(const dict &data, const dict &error, int reqid) {};

virtual void onQueryOptPurchaseLimit(const dict &data, const dict &error, int reqid) {};

virtual void onQueryOptExerciseAssign(const dict &data, const dict &error, int reqid) {};

virtual void onQueryNotifyInfo(const dict &data, const dict &error, int reqid) {};

