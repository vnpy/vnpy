XTPSpecificTickerStruct = {
    "exchange_id": "enum",
    "ticker": "string",
}

XTPMarketDataStockExData = {
    "total_bid_qty": "int",
    "total_ask_qty": "int",
    "ma_bid_price": "float",
    "ma_ask_price": "float",
    "ma_bond_bid_price": "float",
    "ma_bond_ask_price": "float",
    "yield_to_maturity": "float",
    "iopv": "float",
    "etf_buy_count": "int",
    "etf_sell_count": "int",
    "etf_buy_qty": "float",
    "etf_buy_money": "float",
    "etf_sell_qty": "float",
    "etf_sell_money": "float",
    "total_warrant_exec_qty": "float",
    "warrant_lower_price": "float",
    "warrant_upper_price": "float",
    "cancel_buy_count": "int",
    "cancel_sell_count": "int",
    "cancel_buy_qty": "float",
    "cancel_sell_qty": "float",
    "cancel_buy_money": "float",
    "cancel_sell_money": "float",
    "total_buy_count": "int",
    "total_sell_count": "int",
    "duration_after_buy": "int",
    "duration_after_sell": "int",
    "num_bid_orders": "int",
    "num_ask_orders": "int",
    "pre_iopv": "float",
    "r1": "int",
    "r2": "int",
}

XTPMarketDataOptionExData = {
    "auction_price": "float",
    "auction_qty": "int",
    "last_enquiry_time": "int",
}

XTP_MARKETDATA_TYPE = {
}

XTPMarketDataStruct = {
    "exchange_id": "enum",
    "ticker": "string",
    "last_price": "float",
    "pre_close_price": "float",
    "open_price": "float",
    "high_price": "float",
    "low_price": "float",
    "close_price": "float",
    "pre_total_long_positon": "int",
    "total_long_positon": "int",
    "pre_settl_price": "float",
    "settl_price": "float",
    "upper_limit_price": "float",
    "lower_limit_price": "float",
    "pre_delta": "float",
    "curr_delta": "float",
    "data_time": "int",
    "qty": "int",
    "turnover": "float",
    "avg_price": "float",
    "bid": "float",
    "ask": "float",
    "bid_qty": "int",
    "ask_qty": "int",
    "trades_count": "int",
    "ticker_status": "string",
    "data_type": "enum",
    "r4": "int",
}

XTPQuoteStaticInfo = {
    "exchange_id": "enum",
    "ticker": "string",
    "ticker_name": "string",
    "ticker_type": "enum",
    "pre_close_price": "float",
    "upper_limit_price": "float",
    "lower_limit_price": "float",
    "price_tick": "float",
    "buy_qty_unit": "int",
    "sell_qty_unit": "int",
}

OrderBookStruct = {
    "exchange_id": "enum",
    "ticker": "string",
    "last_price": "float",
    "qty": "int",
    "turnover": "float",
    "trades_count": "int",
    "bid": "float",
    "ask": "float",
    "bid_qty": "int",
    "ask_qty": "int",
    "data_time": "int",
}

XTPTickByTickEntrust = {
    "channel_no": "int",
    "seq": "int",
    "price": "float",
    "qty": "int",
    "side": "string",
    "ord_type": "string",
}

XTPTickByTickTrade = {
    "channel_no": "int",
    "seq": "int",
    "price": "float",
    "qty": "int",
    "money": "float",
    "bid_no": "int",
    "ask_no": "int",
    "trade_flag": "string",
}

XTPTickByTickStruct = {
    "exchange_id": "enum",
    "ticker": "string",
    "seq": "int",
    "data_time": "int",
    "type": "enum",
}

XTPTickerPriceInfo = {
    "exchange_id": "enum",
    "ticker": "string",
    "last_price": "float",
}

XTPST = XTPSpecificTickerStruct

XTPMD = XTPMarketDataStruct

XTPQSI = XTPQuoteStaticInfo

XTPOB = OrderBookStruct

XTPTBT = XTPTickByTickStruct
