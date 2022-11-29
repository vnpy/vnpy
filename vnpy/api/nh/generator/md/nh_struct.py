STKMarketData_t = {
    "trading_day": "string",
    "update_time": "string",
    "update_millisec": "int",
    "update_sequence": "int",
    "instrument_id": "string",
    "exchange_id": "string",
    "exchange_inst_id": "string",
    "instrument_status": "int",
    "last_price": "double",
    "volume": "int",
    "last_volume": "int",
    "turnover": "double",
    "open_interest": "int",
    "open_price": "double",
    "highest_price": "double",
    "lowest_price": "double",
    "close_price": "double",
    "settlement_price": "double",
    "average_price": "double",
    "change_price": "double",
    "change_markup": "double",
    "change_swing": "double",
    "upper_limit_price": "double",
    "lower_limit_price": "double",
    "pre_settlement_price": "double",
    "pre_close_price": "double",
    "pre_open_interest": "int",
    "pre_delta": "double",
    "curr_delta": "double",
    "best_ask_price": "double",
    "best_ask_volume": "int",
    "best_bid_price": "double",
    "best_bid_volume": "int",
    "ask_price1": "double",
    "ask_volume1": "int",
    "bid_price1": "double",
    "bid_volume1": "int",
    "ask_price2": "double",
    "ask_volume2": "int",
    "bid_price2": "double",
    "bid_volume2": "int",
    "ask_price3": "double",
    "ask_volume3": "int",
    "bid_price3": "double",
    "bid_volume3": "int",
    "ask_price4": "double",
    "ask_volume4": "int",
    "bid_price4": "double",
    "bid_volume4": "int",
    "ask_price5": "double",
    "ask_volume5": "int",
    "bid_price5": "double",
    "bid_volume5": "int",
    "ask_price6": "double",
    "ask_volume6": "int",
    "bid_price6": "double",
    "bid_volume6": "int",
    "ask_price7": "double",
    "ask_volume7": "int",
    "bid_price7": "double",
    "bid_volume7": "int",
    "ask_price8": "double",
    "ask_volume8": "int",
    "bid_price8": "double",
    "bid_volume8": "int",
    "ask_price9": "double",
    "ask_volume9": "int",
    "bid_price9": "double",
    "bid_volume9": "int",
    "ask_price10": "double",
    "ask_volume10": "int",
    "bid_price10": "double",
    "bid_volume10": "int",
    "md_source": "string",
}

ERRORMSGINFO = {
    "error_code": "int",
    "error_message": "string",
    "response_code": "int",
    "response_string": "string",
    "utp_server_id": "int",
    "oms_server_id": "int",
}

ERRORMSGINFO_t = ERRORMSGINFO

ReqUtpLoginField = {
    "developer_code": "string",
    "developer_license": "string",
    "user_id": "string",
    "user_password": "string",
    "user_one_time_password": "string",
    "user_ca_info": "string",
}

ReqUtpLoginField_t = ReqUtpLoginField

RspUtpLoginField = {
    "response_code": "int",
    "response_string": "string",
    "session_public_key": "string",
    "utp_checking_server_id": "string",
    "utp_checking_server_time": "int",
    "last_login_ip_address": "string",
    "last_login_time": "int",
    "session_encrypted": "bool",
}

RspUtpLoginField_t = RspUtpLoginField

RspUtpLogoutField = {
    "response_code": "int",
    "response_string": "string",
    "utp_server_id": "int",
}

RspUtpLogoutField_t = RspUtpLogoutField

ReqSubscribeField = {
    "routing_key": "string",
}

ReqSubscribeField_t = ReqSubscribeField

RspSubscribeField = {
    "response_code": "int",
    "response_string": "string",
    "routing_key": "string",
}

RspSubscribeField_t = RspSubscribeField

ReqUnSubscribeField = {
    "routing_key": "string",
}

ReqUnSubscribeField_t = ReqUnSubscribeField

RspUnSubscribeField = {
    "response_code": "int",
    "response_string": "string",
    "routing_key": "string",
}

RspUnSubscribeField_t = RspUnSubscribeField

ReqAuthUserPassworField = {
    "user_id": "string",
    "password": "string",
    "save_int": "int",
    "save_double": "double",
    "save_string": "string",
}

ReqAuthUserPassworField_t = ReqAuthUserPassworField

RspAuthUserPassworField = {
    "response_code": "int",
    "response_string": "string",
}

RspAuthUserPassworField_t = RspAuthUserPassworField

ReqOrderInsertData = {
    "client_id": "string",
    "commodity_id": "string",
    "instrument_id": "string",
    "order_type": "char",
    "order_mode": "char",
    "order_way": "char",
    "valid_datetime": "string",
    "is_riskorder": "char",
    "direct": "char",
    "offset": "char",
    "hedge": "char",
    "order_price": "double",
    "trigger_price": "double",
    "order_vol": "int",
    "min_matchvol": "int",
    "save_int": "int",
    "save_double": "double",
    "save_string": "string",
}

ReqOrderInsertData_t = ReqOrderInsertData

ReqOrderInsertField = {
    "oms_server_id": "int",
    "exchange_id": "string",
}

ReqOrderInsertField_t = ReqOrderInsertField

RspOrderInsertField = {
    "response_code": "int",
    "response_string": "string",
    "utp_server_id": "int",
    "oms_server_id": "int",
    "order_stream_id": "int",
    "order_id": "int",
    "local_id": "string",
    "trade_id": "string",
    "insert_id": "string",
    "insert_datetime": "string",
    "order_state": "char",
}

RspOrderInsertField_t = RspOrderInsertField

ReqQryExchangeField = {
    "oms_server_id": "int",
}

ReqQryExchangeField_t = ReqQryExchangeField

RspQryExchangeField = {
    "response_code": "int",
    "response_string": "string",
    "utp_server_id": "int",
    "oms_server_id": "int",
    "exchange_id": "string",
    "exchange_name": "string",
    "exchange_status": "char",
}

RspQryExchangeField_t = RspQryExchangeField

ReqQryInstrumentField = {
    "oms_server_id": "int",
    "exchange_id": "string",
    "product_id": "string",
    "instrument_id": "string",
    "product_class": "char",
}

ReqQryInstrumentField_t = ReqQryInstrumentField

RspQryInstrumentField = {
    "response_code": "int",
    "response_string": "string",
    "utp_server_id": "int",
    "oms_server_id": "int",
    "product_id": "string",
    "product_name": "string",
    "exchange_id": "string",
    "product_class": "char",
    "instrument_id": "string",
    "instrument_name": "string",
    "instrument_class": "char",
    "instrument_status": "char",
    "delivery_year": "int",
    "delivery_month": "int",
    "volume_multiple": "double",
    "price_tick": "double",
    "price_tick_dividend": "int",
    "max_marketorder_volume": "int",
    "min_marketorder_volume": "int",
    "max_limitorder_volume": "int",
    "min_limitorder_volume": "int",
    "create_date": "string",
    "open_date": "string",
    "expire_date": "string",
    "last_trading_date": "string",
    "start_delivery_date": "string",
    "end_delivery_date": "string",
    "first_notice_date": "string",
}

RspQryInstrumentField_t = RspQryInstrumentField
