self.callbacks 
{
    'OnDisconnected': {'reason': 'int'}, 
    'OnError': {'error_info': 'XTPRI'}, 
    'OnSubMarketData': {'ticker': 'XTPST', 'error_info': 'XTPRI', 'is_last': 'bool'}, 
    'OnUnSubMarketData': {'ticker': 'XTPST', 'error_info': 'XTPRI', 'is_last': 'bool'}, 
    'OnDepthMarketData': {'market_data': 'XTPMD', 'bid1_qty[]': 'int64_t', 'bid1_count': 'int32_t', 'max_bid1_count': 'int32_t', 'ask1_qty[]': 'int64_t', 'ask1_count': 'int32_t', 'max_ask1_count': 'int32_t'}, 
    'OnSubOrderBook': {'ticker': 'XTPST', 'error_info': 'XTPRI', 'is_last': 'bool'}, 
    'OnUnSubOrderBook': {'ticker': 'XTPST', 'error_info': 'XTPRI', 'is_last': 'bool'}, 
    'OnOrderBook': {'order_book': 'XTPOB'}, 
    'OnSubTickByTick': {'ticker': 'XTPST', 'error_info': 'XTPRI', 'is_last': 'bool'}, 
    'OnUnSubTickByTick': {'ticker': 'XTPST', 'error_info': 'XTPRI', 'is_last': 'bool'}, 
    'OnTickByTick': {'tbt_data': 'XTPTBT'}, 
    'OnSubscribeAllMarketData': {'exchange_id': 'XTP_EXCHANGE_TYPE', 'error_info': 'XTPRI'}, 
    'OnUnSubscribeAllMarketData': {'exchange_id': 'XTP_EXCHANGE_TYPE', 'error_info': 'XTPRI'}, 
    'OnSubscribeAllOrderBook': {'exchange_id': 'XTP_EXCHANGE_TYPE', 'error_info': 'XTPRI'}, 
    'OnUnSubscribeAllOrderBook': {'exchange_id': 'XTP_EXCHANGE_TYPE', 'error_info': 'XTPRI'}, 
    'OnSubscribeAllTickByTick': {'exchange_id': 'XTP_EXCHANGE_TYPE', 'error_info': 'XTPRI'}, 
    'OnUnSubscribeAllTickByTick': {'exchange_id': 'XTP_EXCHANGE_TYPE', 'error_info': 'XTPRI'}, 
    'OnQueryAllTickers': {'ticker_info': 'XTPQSI*', 'error_info': 'XTPRI', 'is_last': 'bool'}, 
    'OnQueryTickersPriceInfo': {'ticker_info': 'XTPTPI*', 'error_info': 'XTPRI', 'is_last': 'bool'}, 
    'OnSubscribeAllOptionMarketData': {'exchange_id': 'XTP_EXCHANGE_TYPE', 'error_info': 'XTPRI'}, 
    'OnUnSubscribeAllOptionMarketData': {'exchange_id': 'XTP_EXCHANGE_TYPE', 'error_info': 'XTPRI'}, 
    'OnSubscribeAllOptionOrderBook': {'exchange_id': 'XTP_EXCHANGE_TYPE', 'error_info': 'XTPRI'}, 
    'OnUnSubscribeAllOptionOrderBook': {'exchange_id': 'XTP_EXCHANGE_TYPE', 'error_info': 'XTPRI'}, 
    'OnSubscribeAllOptionTickByTick': {'exchange_id': 'XTP_EXCHANGE_TYPE', 'error_info': 'XTPRI'}, 
    'OnUnSubscribeAllOptionTickByTick': {'exchange_id': 'XTP_EXCHANGE_TYPE', 'error_info': 'XTPRI'}}


#----------------------------
self.structs {
    'XTPRI': {'error_id': 'int32_t', 'error_msg[XTP_ERR_MSG_LEN]': 'string'}, 
    'XTPRspInfoStruct': {'error_id': 'int32_t', 'error_msg[XTP_ERR_MSG_LEN]': 'string'}, 
    'XTPClientCrdExtendDebtInfo': {'xtp_id': 'uint64_t', 'debt_id': 'string'}, 
    'XTPClientQueryCrdDebtStockReq': {'market': 'enum', 'ticker': 'string'}, 
    'XTPClientQueryCrdPositionStkInfo': {'market': 'enum', 'ticker': 'string', 'limit_qty': 'int64_t', 'yesterday_qty': 'int64_t', 'left_qty': 'int64_t', 'frozen_qty': 'int64_t'}, 
    'XTPClientQueryCrdPositionStockReq': {'market': 'enum', 'ticker': 'string'}, 
    'XTPClientQueryCrdSurplusStkReqInfo': {'market': 'enum', 'ticker': 'string'}, 
    'XTPClientQueryCrdSurplusStkRspInfo': {'market': 'enum', 'ticker': 'string', 'transferable_quantity': 'int64_t', 'transferred_quantity': 'int64_t'}, 
    'XTPCrdCashRepayDebtInterestFeeRsp': {'xtp_id': 'int64_t', 'request_amount': 'float', 'cash_repay_amount': 'float', 'debt_compact_id': 'string', 'unknow': 'string'}, 
    'XTPCrdCashRepayInfo': {'xtp_id': 'int64_t', 'status': 'enum', 'request_amount': 'float', 'cash_repay_amount': 'float', 'position_effect': 'int', 'error_info': 'enum'}, 
    'XTPCrdCashRepayRsp': {'xtp_id': 'int64_t', 'request_amount': 'float', 'cash_repay_amount': 'float'}, 
    'XTPCrdDebtInfo': {'debt_type': 'int32_t', 'debt_id': 'string', 'position_id': 'int64_t', 'order_xtp_id': 'uint64_t', 'debt_status': 'int32_t', 'market': 'enum', 'ticker': 'string', 'order_date': 'uint64_t', 'end_date': 'uint64_t', 'orig_end_date': 'uint64_t', 'is_extended': 'bool', 'remain_amt': 'float', 'remain_qty': 'int64_t', 'remain_principal': 'float', 'due_right_qty': 'int64_t', 'unknown': 'int64_t'}, 
    'XTPCrdDebtStockInfo': {'market': 'enum', 'ticker': 'string', 'remain_quantity': 'int64_t', 'order_withhold_quantity': 'int64_t'}, 
    'XTPCrdFundInfo': {'maintenance_ratio': 'float', 'all_asset': 'float', 'all_debt': 'float', 'line_of_credit': 'float', 'guaranty': 'float', 'position_amount': 'float'}, 
    'XTPFundTransferNotice': {'serial_id': 'uint64_t', 'transfer_type': 'enum', 'amount': 'float', 'oper_status': 'enum', 'transfer_time': 'uint64_t'}, 
    'XTPOrderCancelInfo': {'order_cancel_xtp_id': 'uint64_t', 'order_xtp_id': 'uint64_t'}, 
    'XTPOrderInfo': {'order_xtp_id': 'uint64_t', 'order_client_id': 'uint32_t', 'order_cancel_client_id': 'uint32_t', 'order_cancel_xtp_id': 'uint64_t', 'ticker': 'string', 'market': 'enum', 'price': 'float', 'quantity': 'int64_t', 'price_type': 'enum', 'side': 'int', 'position_effect': 'int', 'business_type': 'enum', 'qty_traded': 'int64_t', 'qty_left': 'int64_t', 'insert_time': 'int64_t', 'update_time': 'int64_t', 'cancel_time': 'int64_t', 'trade_amount': 'float', 'order_local_id': 'string', 'order_status': 'enum', 'order_submit_status': 'enum', 'order_type': 'char'}, 
    'XTPOrderInsertInfo': {'order_xtp_id': 'uint64_t', 'order_client_id': 'uint32_t', 'ticker': 'string', 'market': 'enum', 'price': 'float', 'stop_price': 'float', 'quantity': 'int64_t', 'price_type': 'enum', 'side': 'int', 'position_effect': 'int', 'business_type': 'enum'}, 
    'XTPQueryAssetRsp': {'total_asset': 'float', 'buying_power': 'float', 'security_asset': 'float', 'fund_buy_amount': 'float', 'fund_buy_fee': 'float', 'fund_sell_amount': 'float', 'fund_sell_fee': 'float', 'withholding_amount': 'float', 'account_type': 'enum', 'frozen_margin': 'float', 'frozen_exec_cash': 'float', 'frozen_exec_fee': 'float', 'pay_later': 'float', 'preadva_pay': 'float', 'orig_banlance': 'float', 'banlance': 'float', 'deposit_withdraw': 'float', 'trade_netting': 'float', 'captial_asset': 'float', 'force_freeze_amount': 'float', 'preferred_amount': 'float', 'repay_stock_aval_banlance': 'float', 'unknown': 'uint64_t'}, 
    'XTPQueryETFBaseReq': {'market': 'enum', 'ticker': 'string'}, 
    'XTPQueryETFBaseRsp': {'market': 'enum', 'etf': 'string', 'subscribe_redemption_ticker': 'string', 'unit': 'int32_t', 'subscribe_status': 'int32_t', 'redemption_status': 'int32_t', 'max_cash_ratio': 'float', 'estimate_amount': 'float', 'cash_component': 'float', 'net_value': 'float', 'total_amount': 'float'}, 
    'XTPQueryETFComponentReq': {'market': 'enum', 'ticker': 'string'}, 
    'XTPQueryETFComponentRsp': {'market': 'enum', 'ticker': 'string', 'component_ticker': 'string', 'component_name': 'string', 'quantity': 'int64_t', 'component_market': 'enum', 'replace_type': 'enum', 'premium_ratio': 'float', 'amount': 'float'}, 
    'XTPQueryFundTransferLogReq': {'serial_id': 'uint64_t'}, 
    'XTPQueryIPOQuotaRsp': {'market': 'enum', 'quantity': 'int32_t'}, 
    'XTPQueryIPOTickerRsp': {'market': 'enum', 'ticker': 'string', 'ticker_name': 'string', 'price': 'float', 'unit': 'int32_t', 'qty_upper_limit': 'int32_t'}, 
    'XTPQueryOptionAuctionInfoReq': {'market': 'enum', 'ticker': 'string'}, 
    'XTPQueryOptionAuctionInfoRsp': {'ticker': 'string', 'security_id_source': 'enum', 'symbol': 'string', 'contract_id': 'string', 'underlying_security_id': 'string', 'underlying_security_id_source': 'enum', 'list_date': 'uint32_t', 'last_trade_date': 'uint32_t', 'ticker_type': 'enum', 'day_trading': 'int32_t', 'call_or_put': 'enum', 'delivery_day': 'uint32_t', 'delivery_month': 'uint32_t', 'exercise_type': 'enum', 'exercise_begin_date': 'uint32_t', 'exercise_end_date': 'uint32_t', 'exercise_price': 'float', 'qty_unit': 'int64_t', 'contract_unit': 'int64_t', 'contract_position': 'int64_t', 'prev_close_price': 'float', 'prev_clearing_price': 'float', 'lmt_buy_max_qty': 'int64_t', 'lmt_buy_min_qty': 'int64_t', 'lmt_sell_max_qty': 'int64_t', 'lmt_sell_min_qty': 'int64_t', 'mkt_buy_max_qty': 'int64_t', 'mkt_buy_min_qty': 'int64_t', 'mkt_sell_max_qty': 'int64_t', 'mkt_sell_min_qty': 'int64_t', 'price_tick': 'float', 'upper_limit_price': 'float', 'lower_limit_price': 'float', 'sell_margin': 'float', 'margin_ratio_param1': 'float', 'margin_ratio_param2': 'float', 'unknown': 'uint64_t'}, 
    'XTPQueryOrderReq': {'ticker': 'string', 'begin_time': 'int64_t', 'end_time': 'int64_t'}, 
    'XTPQueryReportByExecIdReq': {'order_xtp_id': 'uint64_t', 'exec_id': 'string'}, 
    'XTPQueryStkPositionRsp': {'ticker': 'string', 'ticker_name': 'string', 'market': 'enum', 'total_qty': 'int64_t', 'sellable_qty': 'int64_t', 'avg_price': 'float', 'unrealized_pnl': 'float', 'yesterday_position': 'int64_t', 'purchase_redeemable_qty': 'int64_t', 'position_direction': 'enum', 'reserved1': 'uint32_t', 'executable_option': 'int64_t', 'lockable_position': 'int64_t', 'executable_underlying': 'int64_t', 'locked_position': 'int64_t', 'usable_locked_position': 'int64_t', 'unknown': 'uint64_t'}, 
    'XTPQueryStructuredFundInfoReq': {'exchange_id': 'enum', 'sf_ticker': 'string'}, 
    'XTPQueryTraderReq': {'ticker': 'string', 'begin_time': 'int64_t', 'end_time': 'int64_t'}, 
    'XTPStructuredFundInfo': {'exchange_id': 'enum', 'sf_ticker': 'string', 'sf_ticker_name': 'string', 'ticker': 'string', 'ticker_name': 'string', 'split_merge_status': 'enum', 'ratio': 'uint32_t', 'min_split_qty': 'uint32_t', 'min_merge_qty': 'uint32_t', 'net_price': 'float'}, 
    'XTPTradeReport': {'order_xtp_id': 'uint64_t', 'order_client_id': 'uint32_t', 'ticker': 'string', 'market': 'enum', 'local_order_id': 'uint64_t', 'exec_id': 'string', 'price': 'float', 'quantity': 'int64_t', 'trade_time': 'int64_t', 'trade_amount': 'float', 'report_index': 'uint64_t', 'order_exch_id': 'string', 'trade_type': 'char', 'side': 'int', 'position_effect': 'int', 'business_type': 'enum', 'branch_pbu': 'string'}, 
    'OrderBookStruct': {'exchange_id': 'enum', 'ticker': 'string', 'last_price': 'float', 'qty': 'int64_t', 'turnover': 'float', 'trades_count': 'int64_t', 'bid': 'float', 'ask': 'float', 'bid_qty': 'int64_t', 'ask_qty': 'int64_t', 'data_time': 'int64_t'}, 
    'XTPMarketDataOptionExData': {'auction_price': 'float', 'auction_qty': 'int64_t', 'last_enquiry_time': 'int64_t'}, 
    'XTPMarketDataStockExData': {'total_bid_qty': 'int64_t', 'total_ask_qty': 'int64_t', 'ma_bid_price': 'float', 'ma_ask_price': 'float', 'ma_bond_bid_price': 'float', 'ma_bond_ask_price': 'float', 'yield_to_maturity': 'float', 'iopv': 'float', 'etf_buy_count': 'int32_t', 'etf_sell_count': 'int32_t', 'etf_buy_qty': 'float', 'etf_buy_money': 'float', 'etf_sell_qty': 'float', 'etf_sell_money': 'float', 'total_warrant_exec_qty': 'float', 'warrant_lower_price': 'float', 'warrant_upper_price': 'float', 'cancel_buy_count': 'int32_t', 'cancel_sell_count': 'int32_t', 'cancel_buy_qty': 'float', 'cancel_sell_qty': 'float', 'cancel_buy_money': 'float', 'cancel_sell_money': 'float', 'total_buy_count': 'int64_t', 'total_sell_count': 'int64_t', 'duration_after_buy': 'int32_t', 'duration_after_sell': 'int32_t', 'num_bid_orders': 'int32_t', 'num_ask_orders': 'int32_t', 'pre_iopv': 'float', 'r1': 'int64_t', 'r2': 'int64_t'}, 
    'XTPMarketDataStruct': {'exchange_id': 'enum', 'ticker': 'string', 'last_price': 'float', 'pre_close_price': 'float', 'open_price': 'float', 'high_price': 'float', 'low_price': 'float', 'close_price': 'float', 'pre_total_long_positon': 'int64_t', 'total_long_positon': 'int64_t', 'pre_settl_price': 'float', 'settl_price': 'float', 'upper_limit_price': 'float', 'lower_limit_price': 'float', 'pre_delta': 'float', 'curr_delta': 'float', 'data_time': 'int64_t', 'qty': 'int64_t', 'turnover': 'float', 'avg_price': 'float', 'bid': 'float', 'ask': 'float', 'bid_qty': 'int64_t', 'ask_qty': 'int64_t', 'trades_count': 'int64_t', 'ticker_status': 'string', 'data_type': 'enum', 'r4': 'int32_t'}, 
    'XTPQuoteStaticInfo': {'exchange_id': 'enum', 'ticker': 'string', 'ticker_name': 'string', 'ticker_type': 'enum', 'pre_close_price': 'float', 'upper_limit_price': 'float', 'lower_limit_price': 'float', 'price_tick': 'float', 'buy_qty_unit': 'int32_t', 'sell_qty_unit': 'int32_t'}, 
    'XTPSpecificTickerStruct': {'exchange_id': 'enum', 'ticker': 'string'}, 
    'XTPTickByTickEntrust': {'channel_no': 'int32_t', 'seq': 'int64_t', 'price': 'float', 'qty': 'int64_t', 'side': 'string', 'ord_type': 'string'}, 
    'XTPTickByTickStruct': {'exchange_id': 'enum', 'ticker': 'string', 'seq': 'int64_t', 'data_time': 'int64_t', 'type': 'enum'}, 
    'XTPTickByTickTrade': {'channel_no': 'int32_t', 'seq': 'int64_t', 'price': 'float', 'qty': 'int64_t', 'money': 'float', 'bid_no': 'int64_t', 'ask_no': 'int64_t', 'trade_flag': 'string'}, 
    'XTPTickerPriceInfo': {'exchange_id': 'enum', 'ticker': 'string', 'last_price': 'float'}, 
    'XTP_MARKETDATA_TYPE': {}
}


#---------------------------
self.functions {
    'QueryAllTickers': {'exchange_id': 'XTP_EXCHANGE_TYPE'}, 
    'QueryTickersPriceInfo': {'ticker[]': 'char', 'count': 'int', 'exchange_id': 'XTP_EXCHANGE_TYPE'}, 
    'QueryAllTickersPriceInfo': {}
}


