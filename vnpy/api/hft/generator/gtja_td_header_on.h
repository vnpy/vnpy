virtual void onDisconnect() {};

virtual void onError(const dict &error, int request_id) {};

virtual void onRiskNotify(const dict &data) {};

virtual void onLogin(const dict &data, const dict &error) {};

virtual void onTradeReport(const dict &data) {};

virtual void onOrderStatus(const dict &data) {};

virtual void onOrderRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onCancelRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onQueryOrderRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

virtual void onQueryTradeRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

virtual void onQueryPositionRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

virtual void onQueryCashRsp(const dict &data, const dict &error, int request_id) {};

virtual void onQueryJZJYAvailFundRsp(int avail_balance, const dict &error, int request_id) {};

virtual void onTransferFundInAndOutRsp(int transfer_value, const dict &error, int request_id) {};

virtual void onTransferFundBetweenSecuidRsp(int transfer_value, const dict &error, int request_id) {};

virtual void onQueryETFRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onQueryETFStockRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onQueryMaxOrderQtyRsp(const dict &data, const dict &error, int request_id) {};

virtual void onQueryIPOMaxPurchaseRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onQueryIPOStockRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onQueryIPODistributionRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

virtual void onQueryIPOLotteryRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

virtual void onQuerySecurityBaseInfoRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onCreditMortgageInOutRsp(const dict &data, const dict &error, int request_id) {};

virtual void onCreditStockBackRsp(const dict &data, const dict &error, int request_id) {};

virtual void onCreditPayBackRsp(const dict &data, const dict &error, int request_id) {};

virtual void onCreditPayBackByOrderRsp(const dict &data, const dict &error, int request_id) {};

virtual void onQueryCreditStockRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

virtual void onQueryCreditMortgageHoldRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

virtual void onQueryCreditAssetsRsp(const dict &data, const dict &error, int request_id) {};

virtual void onQueryCreditFinanceRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

virtual void onQueryCreditShortsellRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

virtual void onQueryCreditRepayAmountRsp(const dict &data, const dict &error, int request_id) {};

virtual void onQueryCreditRepayStockRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

virtual void onQueryCreditSecuritySellQtyRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onQuerySecuidRightRsp(string market, int secuid_right, const dict &error, bool last, int request_id) {};

virtual void onQueryHKRateRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onQueryHKStockRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onQueryHKFundRsp(const dict &data, const dict &error, int request_id) {};

virtual void onQueryHKMinPriceUnitRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onQueryHKTradeCalendarRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onQueryLockSecurityDetailRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onExtendLockSecurityRsp(int apply_sno, int apply_date, const dict &error, int request_id) {};

virtual void onQueryLockSecurityExtensionRsp(const dict &data, const dict &error, int request_id, bool last) {};

virtual void onCancelExtendLockSecurityRsp(int apply_date, string apply_sno, string cancel_sno, const dict &error, int request_id) {};

virtual void onQueryTransferFundHistoryRsp(const dict &data, const dict &error, int request_id, bool last) {};

