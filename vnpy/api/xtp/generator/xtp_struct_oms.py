XTPOrderInsertInfo = {
    "order_xtp_id": "int",
    "order_client_id": "int",
    "ticker": "string",
    "market": "enum",
    "price": "float",
    "stop_price": "float",
    "quantity": "int",
    "price_type": "enum",
    "side": "int",
    "position_effect": "int",
    "business_type": "enum",
}

XTPOrderCancelInfo = {
    "order_cancel_xtp_id": "int",
    "order_xtp_id": "int",
}

XTPOrderInfo = {
    "order_xtp_id": "int",
    "order_client_id": "int",
    "order_cancel_client_id": "int",
    "order_cancel_xtp_id": "int",
    "ticker": "string",
    "market": "enum",
    "price": "float",
    "quantity": "int",
    "price_type": "enum",
    "side": "int",
    "position_effect": "int",
    "business_type": "enum",
    "qty_traded": "int",
    "qty_left": "int",
    "insert_time": "int",
    "update_time": "int",
    "cancel_time": "int",
    "trade_amount": "float",
    "order_local_id": "string",
    "order_status": "enum",
    "order_submit_status": "enum",
    "order_type": "string",
}

XTPTradeReport = {
    "order_xtp_id": "int",
    "order_client_id": "int",
    "ticker": "string",
    "market": "enum",
    "local_order_id": "int",
    "exec_id": "string",
    "price": "float",
    "quantity": "int",
    "trade_time": "int",
    "trade_amount": "float",
    "report_index": "int",
    "order_exch_id": "string",
    "trade_type": "string",
    "side": "int",
    "position_effect": "int",
    "business_type": "enum",
    "branch_pbu": "string",
}

XTPQueryOrderReq = {
    "ticker": "string",
    "begin_time": "int",
    "end_time": "int",
}

XTPQueryReportByExecIdReq = {
    "order_xtp_id": "int",
    "exec_id": "string",
}

XTPQueryTraderReq = {
    "ticker": "string",
    "begin_time": "int",
    "end_time": "int",
}

XTPQueryAssetRsp = {
    "total_asset": "float",
    "buying_power": "float",
    "security_asset": "float",
    "fund_buy_amount": "float",
    "fund_buy_fee": "float",
    "fund_sell_amount": "float",
    "fund_sell_fee": "float",
    "withholding_amount": "float",
    "account_type": "enum",
    "frozen_margin": "float",
    "frozen_exec_cash": "float",
    "frozen_exec_fee": "float",
    "pay_later": "float",
    "preadva_pay": "float",
    "orig_banlance": "float",
    "banlance": "float",
    "deposit_withdraw": "float",
    "trade_netting": "float",
    "captial_asset": "float",
    "force_freeze_amount": "float",
    "preferred_amount": "float",
    "repay_stock_aval_banlance": "float",
    "unknown": "int",
}

XTPQueryStkPositionRsp = {
    "ticker": "string",
    "ticker_name": "string",
    "market": "enum",
    "total_qty": "int",
    "sellable_qty": "int",
    "avg_price": "float",
    "unrealized_pnl": "float",
    "yesterday_position": "int",
    "purchase_redeemable_qty": "int",
    "position_direction": "enum",
    "reserved1": "int",
    "executable_option": "int",
    "lockable_position": "int",
    "executable_underlying": "int",
    "locked_position": "int",
    "usable_locked_position": "int",
    "unknown": "int",
}

XTPFundTransferNotice = {
    "serial_id": "int",
    "transfer_type": "enum",
    "amount": "float",
    "oper_status": "enum",
    "transfer_time": "int",
}

XTPQueryFundTransferLogReq = {
    "serial_id": "int",
}

XTPQueryStructuredFundInfoReq = {
    "exchange_id": "enum",
    "sf_ticker": "string",
}

XTPStructuredFundInfo = {
    "exchange_id": "enum",
    "sf_ticker": "string",
    "sf_ticker_name": "string",
    "ticker": "string",
    "ticker_name": "string",
    "split_merge_status": "enum",
    "ratio": "int",
    "min_split_qty": "int",
    "min_merge_qty": "int",
    "net_price": "float",
}

XTPQueryETFBaseReq = {
    "market": "enum",
    "ticker": "string",
}

XTPQueryETFBaseRsp = {
    "market": "enum",
    "etf": "string",
    "subscribe_redemption_ticker": "string",
    "unit": "int",
    "subscribe_status": "int",
    "redemption_status": "int",
    "max_cash_ratio": "float",
    "estimate_amount": "float",
    "cash_component": "float",
    "net_value": "float",
    "total_amount": "float",
}

XTPQueryETFComponentReq = {
    "market": "enum",
    "ticker": "string",
}

XTPQueryETFComponentRsp = {
    "market": "enum",
    "ticker": "string",
    "component_ticker": "string",
    "component_name": "string",
    "quantity": "int",
    "component_market": "enum",
    "replace_type": "enum",
    "premium_ratio": "float",
    "amount": "float",
}

XTPQueryIPOTickerRsp = {
    "market": "enum",
    "ticker": "string",
    "ticker_name": "string",
    "price": "float",
    "unit": "int",
    "qty_upper_limit": "int",
}

XTPQueryIPOQuotaRsp = {
    "market": "enum",
    "quantity": "int",
}

XTPQueryOptionAuctionInfoReq = {
    "market": "enum",
    "ticker": "string",
}

XTPQueryOptionAuctionInfoRsp = {
    "ticker": "string",
    "security_id_source": "enum",
    "symbol": "string",
    "contract_id": "string",
    "underlying_security_id": "string",
    "underlying_security_id_source": "enum",
    "list_date": "int",
    "last_trade_date": "int",
    "ticker_type": "enum",
    "day_trading": "int",
    "call_or_put": "enum",
    "delivery_day": "int",
    "delivery_month": "int",
    "exercise_type": "enum",
    "exercise_begin_date": "int",
    "exercise_end_date": "int",
    "exercise_price": "float",
    "qty_unit": "int",
    "contract_unit": "int",
    "contract_position": "int",
    "prev_close_price": "float",
    "prev_clearing_price": "float",
    "lmt_buy_max_qty": "int",
    "lmt_buy_min_qty": "int",
    "lmt_sell_max_qty": "int",
    "lmt_sell_min_qty": "int",
    "mkt_buy_max_qty": "int",
    "mkt_buy_min_qty": "int",
    "mkt_sell_max_qty": "int",
    "mkt_sell_min_qty": "int",
    "price_tick": "float",
    "upper_limit_price": "float",
    "lower_limit_price": "float",
    "sell_margin": "float",
    "margin_ratio_param1": "float",
    "margin_ratio_param2": "float",
    "unknown": "int",
}

XTPCrdCashRepayRsp = {
    "xtp_id": "int",
    "request_amount": "float",
    "cash_repay_amount": "float",
}

XTPCrdCashRepayDebtInterestFeeRsp = {
    "xtp_id": "int",
    "request_amount": "float",
    "cash_repay_amount": "float",
    "debt_compact_id": "string",
    "unknow": "string",
}

XTPCrdCashRepayInfo = {
    "xtp_id": "int",
    "status": "enum",
    "request_amount": "float",
    "cash_repay_amount": "float",
    "position_effect": "int",
    "error_info": "enum",
}

XTPCrdDebtInfo = {
    "debt_type": "int",
    "debt_id": "string",
    "position_id": "int",
    "order_xtp_id": "int",
    "debt_status": "int",
    "market": "enum",
    "ticker": "string",
    "order_date": "int",
    "end_date": "int",
    "orig_end_date": "int",
    "is_extended": "bool",
    "remain_amt": "float",
    "remain_qty": "int",
    "remain_principal": "float",
    "due_right_qty": "int",
    "unknown": "int",
}

XTPCrdFundInfo = {
    "maintenance_ratio": "float",
    "all_asset": "float",
    "all_debt": "float",
    "line_of_credit": "float",
    "guaranty": "float",
    "position_amount": "float",
}

XTPClientQueryCrdDebtStockReq = {
    "market": "enum",
    "ticker": "string",
}

XTPCrdDebtStockInfo = {
    "market": "enum",
    "ticker": "string",
    "remain_quantity": "int",
    "order_withhold_quantity": "int",
}

XTPClientQueryCrdPositionStockReq = {
    "market": "enum",
    "ticker": "string",
}

XTPClientQueryCrdPositionStkInfo = {
    "market": "enum",
    "ticker": "string",
    "limit_qty": "int",
    "yesterday_qty": "int",
    "left_qty": "int",
    "frozen_qty": "int",
}

XTPClientQueryCrdSurplusStkReqInfo = {
    "market": "enum",
    "ticker": "string",
}

XTPClientQueryCrdSurplusStkRspInfo = {
    "market": "enum",
    "ticker": "string",
    "transferable_quantity": "int",
    "transferred_quantity": "int",
}

XTPClientCrdExtendDebtInfo = {
    "xtp_id": "int",
    "debt_id": "string",
}

XTPQueryOrderRsp = XTPOrderInfo
XTPQueryTradeRsp = XTPTradeReport
XTPFundTransferLog = XTPFundTransferNotice
