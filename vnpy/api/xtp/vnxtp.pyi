# noinspection PyUnresolvedReferences
import typing
if typing.TYPE_CHECKING:
    from typing import *
    # noinspection PyUnresolvedReferences
    from enum import Enum
    from .vnxtp import *


def set_async_callback_exception_handler(handler: Callable[[Exception, object, str], bool]):
    """
    set a customize exception handler for async callback in this module(pyd)
    \a handler should return True if it handles that exception,
    If the return value of \a handler is not True, exception will be re-thrown.
    """
    ...


class AsyncDispatchException:
    what: str
    instance: object
    function_name: str


from . import vnxtp_XTP as XTP
class XTPRspInfoStruct():
    
    
    error_id: int
    error_msg: str
    
    
class XTPSpecificTickerStruct():
    
    
    exchange_id: XTP_EXCHANGE_TYPE
    ticker: str
    
    
class XTPMarketDataStockExData():
    
    
    total_bid_qty: int
    total_ask_qty: int
    ma_bid_price: float
    ma_ask_price: float
    ma_bond_bid_price: float
    ma_bond_ask_price: float
    yield_to_maturity: float
    iopv: float
    etf_buy_count: int
    etf_sell_count: int
    etf_buy_qty: float
    etf_buy_money: float
    etf_sell_qty: float
    etf_sell_money: float
    total_warrant_exec_qty: float
    warrant_lower_price: float
    warrant_upper_price: float
    cancel_buy_count: int
    cancel_sell_count: int
    cancel_buy_qty: float
    cancel_sell_qty: float
    cancel_buy_money: float
    cancel_sell_money: float
    total_buy_count: int
    total_sell_count: int
    duration_after_buy: int
    duration_after_sell: int
    num_bid_orders: int
    num_ask_orders: int
    pre_iopv: float
    r1: int
    r2: int
    
    
class XTPMarketDataOptionExData():
    
    
    auction_price: float
    auction_qty: int
    last_enquiry_time: int
    
    
class XTPMarketDataStruct():
    
    
    exchange_id: XTP_EXCHANGE_TYPE
    ticker: str
    last_price: float
    pre_close_price: float
    open_price: float
    high_price: float
    low_price: float
    close_price: float
    pre_total_long_positon: int
    total_long_positon: int
    pre_settl_price: float
    settl_price: float
    upper_limit_price: float
    lower_limit_price: float
    pre_delta: float
    curr_delta: float
    data_time: int
    qty: int
    turnover: float
    avg_price: float
    bid: List[float]
    ask: List[float]
    bid_qty: List[int]
    ask_qty: List[int]
    trades_count: int
    ticker_status: str
    stk: XTPMarketDataStockExData
    opt: XTPMarketDataOptionExData
    data_type: XTP_MARKETDATA_TYPE
    r4: int
    
    
class XTPQuoteStaticInfo():
    
    
    exchange_id: XTP_EXCHANGE_TYPE
    ticker: str
    ticker_name: str
    ticker_type: XTP_TICKER_TYPE
    pre_close_price: float
    upper_limit_price: float
    lower_limit_price: float
    price_tick: float
    buy_qty_unit: int
    sell_qty_unit: int
    
    
class OrderBookStruct():
    
    
    exchange_id: XTP_EXCHANGE_TYPE
    ticker: str
    last_price: float
    qty: int
    turnover: float
    trades_count: int
    bid: List[float]
    ask: List[float]
    bid_qty: List[int]
    ask_qty: List[int]
    data_time: int
    
    
class XTPTickByTickEntrust():
    
    
    channel_no: int
    seq: int
    price: float
    qty: int
    side: int
    ord_type: int
    
    
class XTPTickByTickTrade():
    
    
    channel_no: int
    seq: int
    price: float
    qty: int
    money: float
    bid_no: int
    ask_no: int
    trade_flag: int
    
    
class XTPTickByTickStruct():
    
    
    exchange_id: XTP_EXCHANGE_TYPE
    ticker: str
    seq: int
    data_time: int
    type: XTP_TBT_TYPE
    entrust: XTPTickByTickEntrust
    trade: XTPTickByTickTrade
    
    
class XTPTickerPriceInfo():
    
    
    exchange_id: XTP_EXCHANGE_TYPE
    ticker: str
    last_price: float
    
    
class XTPOrderInsertInfo():
    
    
    order_xtp_id: int
    order_client_id: int
    ticker: str
    market: XTP_MARKET_TYPE
    price: float
    stop_price: float
    quantity: int
    price_type: XTP_PRICE_TYPE
    u32: int
    side: int
    position_effect: int
    reserved1: int
    reserved2: int
    business_type: XTP_BUSINESS_TYPE
    
    
class XTPOrderCancelInfo():
    
    
    order_cancel_xtp_id: int
    order_xtp_id: int
    
    
class XTPOrderInfo():
    
    
    order_xtp_id: int
    order_client_id: int
    order_cancel_client_id: int
    order_cancel_xtp_id: int
    ticker: str
    market: XTP_MARKET_TYPE
    price: float
    quantity: int
    price_type: XTP_PRICE_TYPE
    u32: int
    side: int
    position_effect: int
    reserved1: int
    reserved2: int
    business_type: XTP_BUSINESS_TYPE
    qty_traded: int
    qty_left: int
    insert_time: int
    update_time: int
    cancel_time: int
    trade_amount: float
    order_local_id: str
    order_status: XTP_ORDER_STATUS_TYPE
    order_submit_status: XTP_ORDER_SUBMIT_STATUS_TYPE
    order_type: int
    
    
class XTPTradeReport():
    
    
    order_xtp_id: int
    order_client_id: int
    ticker: str
    market: XTP_MARKET_TYPE
    local_order_id: int
    exec_id: str
    price: float
    quantity: int
    trade_time: int
    trade_amount: float
    report_index: int
    order_exch_id: str
    trade_type: int
    u32: int
    side: int
    position_effect: int
    reserved1: int
    reserved2: int
    business_type: XTP_BUSINESS_TYPE
    branch_pbu: str
    
    
class XTPQueryOrderReq():
    
    
    ticker: str
    begin_time: int
    end_time: int
    
    
class XTPQueryReportByExecIdReq():
    
    
    order_xtp_id: int
    exec_id: str
    
    
class XTPQueryTraderReq():
    
    
    ticker: str
    begin_time: int
    end_time: int
    
    
class XTPQueryAssetRsp():
    
    
    total_asset: float
    buying_power: float
    security_asset: float
    fund_buy_amount: float
    fund_buy_fee: float
    fund_sell_amount: float
    fund_sell_fee: float
    withholding_amount: float
    account_type: XTP_ACCOUNT_TYPE
    frozen_margin: float
    frozen_exec_cash: float
    frozen_exec_fee: float
    pay_later: float
    preadva_pay: float
    orig_banlance: float
    banlance: float
    deposit_withdraw: float
    trade_netting: float
    captial_asset: float
    force_freeze_amount: float
    preferred_amount: float
    unknown: List[int]
    
    
class XTPQueryStkPositionRsp():
    
    
    ticker: str
    ticker_name: str
    market: XTP_MARKET_TYPE
    total_qty: int
    sellable_qty: int
    avg_price: float
    unrealized_pnl: float
    yesterday_position: int
    purchase_redeemable_qty: int
    position_direction: XTP_POSITION_DIRECTION_TYPE
    reserved1: int
    executable_option: int
    lockable_position: int
    executable_underlying: int
    locked_position: int
    usable_locked_position: int
    unknown: List[int]
    
    
class XTPFundTransferNotice():
    
    
    serial_id: int
    transfer_type: XTP_FUND_TRANSFER_TYPE
    amount: float
    oper_status: XTP_FUND_OPER_STATUS
    transfer_time: int
    
    
class XTPQueryFundTransferLogReq():
    
    
    serial_id: int
    
    
class XTPQueryStructuredFundInfoReq():
    
    
    exchange_id: XTP_EXCHANGE_TYPE
    sf_ticker: str
    
    
class XTPStructuredFundInfo():
    
    
    exchange_id: XTP_EXCHANGE_TYPE
    sf_ticker: str
    sf_ticker_name: str
    ticker: str
    ticker_name: str
    split_merge_status: XTP_SPLIT_MERGE_STATUS
    ratio: int
    min_split_qty: int
    min_merge_qty: int
    net_price: float
    
    
class XTPQueryETFBaseReq():
    
    
    market: XTP_MARKET_TYPE
    ticker: str
    
    
class XTPQueryETFBaseRsp():
    
    
    market: XTP_MARKET_TYPE
    etf: str
    subscribe_redemption_ticker: str
    unit: int
    subscribe_status: int
    redemption_status: int
    max_cash_ratio: float
    estimate_amount: float
    cash_component: float
    net_value: float
    total_amount: float
    
    
class XTPQueryETFComponentReq():
    
    
    market: XTP_MARKET_TYPE
    ticker: str
    
    
class XTPQueryETFComponentRsp():
    
    
    market: XTP_MARKET_TYPE
    ticker: str
    component_ticker: str
    component_name: str
    quantity: int
    component_market: XTP_MARKET_TYPE
    replace_type: ETF_REPLACE_TYPE
    premium_ratio: float
    amount: float
    
    
class XTPQueryIPOTickerRsp():
    
    
    market: XTP_MARKET_TYPE
    ticker: str
    ticker_name: str
    price: float
    unit: int
    qty_upper_limit: int
    
    
class XTPQueryIPOQuotaRsp():
    
    
    market: XTP_MARKET_TYPE
    quantity: int
    
    
class XTPQueryOptionAuctionInfoReq():
    
    
    market: XTP_MARKET_TYPE
    ticker: str
    
    
class XTPQueryOptionAuctionInfoRsp():
    
    
    ticker: str
    security_id_source: XTP_MARKET_TYPE
    symbol: str
    contract_id: str
    underlying_security_id: str
    underlying_security_id_source: XTP_MARKET_TYPE
    list_date: int
    last_trade_date: int
    ticker_type: XTP_TICKER_TYPE
    day_trading: int
    call_or_put: XTP_OPT_CALL_OR_PUT_TYPE
    delivery_day: int
    delivery_month: int
    exercise_type: XTP_OPT_EXERCISE_TYPE_TYPE
    exercise_begin_date: int
    exercise_end_date: int
    exercise_price: float
    qty_unit: int
    contract_unit: int
    contract_position: int
    prev_close_price: float
    prev_clearing_price: float
    lmt_buy_max_qty: int
    lmt_buy_min_qty: int
    lmt_sell_max_qty: int
    lmt_sell_min_qty: int
    mkt_buy_max_qty: int
    mkt_buy_min_qty: int
    mkt_sell_max_qty: int
    mkt_sell_min_qty: int
    price_tick: float
    upper_limit_price: float
    lower_limit_price: float
    sell_margin: float
    margin_ratio_param1: float
    margin_ratio_param2: float
    unknown: List[int]
    
    
class XTPFundTransferReq():
    
    
    serial_id: int
    fund_account: str
    password: str
    amount: float
    transfer_type: XTP_FUND_TRANSFER_TYPE
    
    
class XTP_LOG_LEVEL(Enum):
    XTP_LOG_LEVEL_FATAL: XTP_LOG_LEVEL
    XTP_LOG_LEVEL_ERROR: XTP_LOG_LEVEL
    XTP_LOG_LEVEL_WARNING: XTP_LOG_LEVEL
    XTP_LOG_LEVEL_INFO: XTP_LOG_LEVEL
    XTP_LOG_LEVEL_DEBUG: XTP_LOG_LEVEL
    XTP_LOG_LEVEL_TRACE: XTP_LOG_LEVEL
class XTP_PROTOCOL_TYPE(Enum):
    XTP_PROTOCOL_TCP: XTP_PROTOCOL_TYPE
    XTP_PROTOCOL_UDP: XTP_PROTOCOL_TYPE
class XTP_EXCHANGE_TYPE(Enum):
    XTP_EXCHANGE_SH: XTP_EXCHANGE_TYPE
    XTP_EXCHANGE_SZ: XTP_EXCHANGE_TYPE
    XTP_EXCHANGE_UNKNOWN: XTP_EXCHANGE_TYPE
class XTP_MARKET_TYPE(Enum):
    XTP_MKT_INIT: XTP_MARKET_TYPE
    XTP_MKT_SZ_A: XTP_MARKET_TYPE
    XTP_MKT_SH_A: XTP_MARKET_TYPE
    XTP_MKT_UNKNOWN: XTP_MARKET_TYPE
class XTP_PRICE_TYPE(Enum):
    XTP_PRICE_LIMIT: XTP_PRICE_TYPE
    XTP_PRICE_BEST_OR_CANCEL: XTP_PRICE_TYPE
    XTP_PRICE_BEST5_OR_LIMIT: XTP_PRICE_TYPE
    XTP_PRICE_BEST5_OR_CANCEL: XTP_PRICE_TYPE
    XTP_PRICE_ALL_OR_CANCEL: XTP_PRICE_TYPE
    XTP_PRICE_FORWARD_BEST: XTP_PRICE_TYPE
    XTP_PRICE_REVERSE_BEST_LIMIT: XTP_PRICE_TYPE
    XTP_PRICE_LIMIT_OR_CANCEL: XTP_PRICE_TYPE
    XTP_PRICE_TYPE_UNKNOWN: XTP_PRICE_TYPE
class XTP_ORDER_ACTION_STATUS_TYPE(Enum):
    XTP_ORDER_ACTION_STATUS_SUBMITTED: XTP_ORDER_ACTION_STATUS_TYPE
    XTP_ORDER_ACTION_STATUS_ACCEPTED: XTP_ORDER_ACTION_STATUS_TYPE
    XTP_ORDER_ACTION_STATUS_REJECTED: XTP_ORDER_ACTION_STATUS_TYPE
class XTP_ORDER_STATUS_TYPE(Enum):
    XTP_ORDER_STATUS_INIT: XTP_ORDER_STATUS_TYPE
    XTP_ORDER_STATUS_ALLTRADED: XTP_ORDER_STATUS_TYPE
    XTP_ORDER_STATUS_PARTTRADEDQUEUEING: XTP_ORDER_STATUS_TYPE
    XTP_ORDER_STATUS_PARTTRADEDNOTQUEUEING: XTP_ORDER_STATUS_TYPE
    XTP_ORDER_STATUS_NOTRADEQUEUEING: XTP_ORDER_STATUS_TYPE
    XTP_ORDER_STATUS_CANCELED: XTP_ORDER_STATUS_TYPE
    XTP_ORDER_STATUS_REJECTED: XTP_ORDER_STATUS_TYPE
    XTP_ORDER_STATUS_UNKNOWN: XTP_ORDER_STATUS_TYPE
class XTP_ORDER_SUBMIT_STATUS_TYPE(Enum):
    XTP_ORDER_SUBMIT_STATUS_INSERT_SUBMITTED: XTP_ORDER_SUBMIT_STATUS_TYPE
    XTP_ORDER_SUBMIT_STATUS_INSERT_ACCEPTED: XTP_ORDER_SUBMIT_STATUS_TYPE
    XTP_ORDER_SUBMIT_STATUS_INSERT_REJECTED: XTP_ORDER_SUBMIT_STATUS_TYPE
    XTP_ORDER_SUBMIT_STATUS_CANCEL_SUBMITTED: XTP_ORDER_SUBMIT_STATUS_TYPE
    XTP_ORDER_SUBMIT_STATUS_CANCEL_REJECTED: XTP_ORDER_SUBMIT_STATUS_TYPE
    XTP_ORDER_SUBMIT_STATUS_CANCEL_ACCEPTED: XTP_ORDER_SUBMIT_STATUS_TYPE
class XTP_TE_RESUME_TYPE(Enum):
    XTP_TERT_RESTART: XTP_TE_RESUME_TYPE
    XTP_TERT_RESUME: XTP_TE_RESUME_TYPE
    XTP_TERT_QUICK: XTP_TE_RESUME_TYPE
class ETF_REPLACE_TYPE(Enum):
    ERT_CASH_FORBIDDEN: ETF_REPLACE_TYPE
    ERT_CASH_OPTIONAL: ETF_REPLACE_TYPE
    ERT_CASH_MUST: ETF_REPLACE_TYPE
    ERT_CASH_RECOMPUTE_INTER_SZ: ETF_REPLACE_TYPE
    ERT_CASH_MUST_INTER_SZ: ETF_REPLACE_TYPE
    ERT_CASH_RECOMPUTE_INTER_OTHER: ETF_REPLACE_TYPE
    ERT_CASH_MUST_INTER_OTHER: ETF_REPLACE_TYPE
    EPT_INVALID: ETF_REPLACE_TYPE
class XTP_TICKER_TYPE(Enum):
    XTP_TICKER_TYPE_STOCK: XTP_TICKER_TYPE
    XTP_TICKER_TYPE_INDEX: XTP_TICKER_TYPE
    XTP_TICKER_TYPE_FUND: XTP_TICKER_TYPE
    XTP_TICKER_TYPE_BOND: XTP_TICKER_TYPE
    XTP_TICKER_TYPE_OPTION: XTP_TICKER_TYPE
    XTP_TICKER_TYPE_UNKNOWN: XTP_TICKER_TYPE
class XTP_BUSINESS_TYPE(Enum):
    XTP_BUSINESS_TYPE_CASH: XTP_BUSINESS_TYPE
    XTP_BUSINESS_TYPE_IPOS: XTP_BUSINESS_TYPE
    XTP_BUSINESS_TYPE_REPO: XTP_BUSINESS_TYPE
    XTP_BUSINESS_TYPE_ETF: XTP_BUSINESS_TYPE
    XTP_BUSINESS_TYPE_MARGIN: XTP_BUSINESS_TYPE
    XTP_BUSINESS_TYPE_DESIGNATION: XTP_BUSINESS_TYPE
    XTP_BUSINESS_TYPE_ALLOTMENT: XTP_BUSINESS_TYPE
    XTP_BUSINESS_TYPE_STRUCTURED_FUND_PURCHASE_REDEMPTION: XTP_BUSINESS_TYPE
    XTP_BUSINESS_TYPE_STRUCTURED_FUND_SPLIT_MERGE: XTP_BUSINESS_TYPE
    XTP_BUSINESS_TYPE_MONEY_FUND: XTP_BUSINESS_TYPE
    XTP_BUSINESS_TYPE_OPTION: XTP_BUSINESS_TYPE
    XTP_BUSINESS_TYPE_EXECUTE: XTP_BUSINESS_TYPE
    XTP_BUSINESS_TYPE_FREEZE: XTP_BUSINESS_TYPE
    XTP_BUSINESS_TYPE_UNKNOWN: XTP_BUSINESS_TYPE
class XTP_ACCOUNT_TYPE(Enum):
    XTP_ACCOUNT_NORMAL: XTP_ACCOUNT_TYPE
    XTP_ACCOUNT_CREDIT: XTP_ACCOUNT_TYPE
    XTP_ACCOUNT_DERIVE: XTP_ACCOUNT_TYPE
    XTP_ACCOUNT_UNKNOWN: XTP_ACCOUNT_TYPE
class XTP_FUND_TRANSFER_TYPE(Enum):
    XTP_FUND_TRANSFER_OUT: XTP_FUND_TRANSFER_TYPE
    XTP_FUND_TRANSFER_IN: XTP_FUND_TRANSFER_TYPE
    XTP_FUND_TRANSFER_UNKNOWN: XTP_FUND_TRANSFER_TYPE
class XTP_FUND_OPER_STATUS(Enum):
    XTP_FUND_OPER_PROCESSING: XTP_FUND_OPER_STATUS
    XTP_FUND_OPER_SUCCESS: XTP_FUND_OPER_STATUS
    XTP_FUND_OPER_FAILED: XTP_FUND_OPER_STATUS
    XTP_FUND_OPER_SUBMITTED: XTP_FUND_OPER_STATUS
    XTP_FUND_OPER_UNKNOWN: XTP_FUND_OPER_STATUS
class XTP_SPLIT_MERGE_STATUS(Enum):
    XTP_SPLIT_MERGE_STATUS_ALLOW: XTP_SPLIT_MERGE_STATUS
    XTP_SPLIT_MERGE_STATUS_ONLY_SPLIT: XTP_SPLIT_MERGE_STATUS
    XTP_SPLIT_MERGE_STATUS_ONLY_MERGE: XTP_SPLIT_MERGE_STATUS
    XTP_SPLIT_MERGE_STATUS_FORBIDDEN: XTP_SPLIT_MERGE_STATUS
class XTP_TBT_TYPE(Enum):
    XTP_TBT_ENTRUST: XTP_TBT_TYPE
    XTP_TBT_TRADE: XTP_TBT_TYPE
class XTP_OPT_CALL_OR_PUT_TYPE(Enum):
    XTP_OPT_CALL: XTP_OPT_CALL_OR_PUT_TYPE
    XTP_OPT_PUT: XTP_OPT_CALL_OR_PUT_TYPE
class XTP_OPT_EXERCISE_TYPE_TYPE(Enum):
    XTP_OPT_EXERCISE_TYPE_EUR: XTP_OPT_EXERCISE_TYPE_TYPE
    XTP_OPT_EXERCISE_TYPE_AME: XTP_OPT_EXERCISE_TYPE_TYPE
class XTP_POSITION_DIRECTION_TYPE(Enum):
    XTP_POSITION_DIRECTION_NET: XTP_POSITION_DIRECTION_TYPE
    XTP_POSITION_DIRECTION_LONG: XTP_POSITION_DIRECTION_TYPE
    XTP_POSITION_DIRECTION_SHORT: XTP_POSITION_DIRECTION_TYPE
    XTP_POSITION_DIRECTION_COVERED: XTP_POSITION_DIRECTION_TYPE
class XTP_MARKETDATA_TYPE(Enum):
    XTP_MARKETDATA_ACTUAL: XTP_MARKETDATA_TYPE
    XTP_MARKETDATA_OPTION: XTP_MARKETDATA_TYPE
XTPVersionType = str
XTP_LOG_LEVEL = XTP_LOG_LEVEL
XTP_PROTOCOL_TYPE = XTP_PROTOCOL_TYPE
XTP_EXCHANGE_TYPE = XTP_EXCHANGE_TYPE
XTP_MARKET_TYPE = XTP_MARKET_TYPE
XTP_PRICE_TYPE = XTP_PRICE_TYPE
XTP_SIDE_TYPE = int
XTP_POSITION_EFFECT_TYPE = int
XTP_ORDER_ACTION_STATUS_TYPE = XTP_ORDER_ACTION_STATUS_TYPE
XTP_ORDER_STATUS_TYPE = XTP_ORDER_STATUS_TYPE
XTP_ORDER_SUBMIT_STATUS_TYPE = XTP_ORDER_SUBMIT_STATUS_TYPE
XTP_TE_RESUME_TYPE = XTP_TE_RESUME_TYPE
ETF_REPLACE_TYPE = ETF_REPLACE_TYPE
XTP_TICKER_TYPE = XTP_TICKER_TYPE
XTP_BUSINESS_TYPE = XTP_BUSINESS_TYPE
XTP_ACCOUNT_TYPE = XTP_ACCOUNT_TYPE
XTP_FUND_TRANSFER_TYPE = XTP_FUND_TRANSFER_TYPE
XTP_FUND_OPER_STATUS = XTP_FUND_OPER_STATUS
XTP_SPLIT_MERGE_STATUS = XTP_SPLIT_MERGE_STATUS
XTP_TBT_TYPE = XTP_TBT_TYPE
XTP_OPT_CALL_OR_PUT_TYPE = XTP_OPT_CALL_OR_PUT_TYPE
XTP_OPT_EXERCISE_TYPE_TYPE = XTP_OPT_EXERCISE_TYPE_TYPE
XTP_POSITION_DIRECTION_TYPE = XTP_POSITION_DIRECTION_TYPE
TXTPTradeTypeType = int
TXTPOrderTypeType = int
XTPRI = XTPRspInfoStruct
XTPST = XTPSpecificTickerStruct
XTPMD = XTPMarketDataStruct
XTPQSI = XTPQuoteStaticInfo
XTPOB = OrderBookStruct
XTPTBT = XTPTickByTickStruct
XTPTPI = XTPTickerPriceInfo
XTPQueryOrderRsp = XTPOrderInfo
XTPQueryTradeRsp = XTPTradeReport
XTPFundTransferLog = XTPFundTransferNotice
XTPQueryETFBaseRsp = XTPQueryETFBaseRsp
XTPQueryETFComponentReq = XTPQueryETFComponentReq
XTPFundTransferAck = XTPFundTransferNotice
XTP_VERSION_LEN: int
XTP_TRADING_DAY_LEN: int
XTP_TICKER_LEN: int
XTP_TICKER_NAME_LEN: int
XTP_LOCAL_ORDER_LEN: int
XTP_ORDER_EXCH_LEN: int
XTP_EXEC_ID_LEN: int
XTP_BRANCH_PBU_LEN: int
XTP_ACCOUNT_NAME_LEN: int
XTP_SIDE_BUY: int
XTP_SIDE_SELL: int
XTP_SIDE_PURCHASE: int
XTP_SIDE_REDEMPTION: int
XTP_SIDE_SPLIT: int
XTP_SIDE_MERGE: int
XTP_SIDE_COVER: int
XTP_SIDE_FREEZE: int
XTP_SIDE_MARGIN_TRADE: int
XTP_SIDE_SHORT_SELL: int
XTP_SIDE_REPAY_MARGIN: int
XTP_SIDE_REPAY_STOCK: int
XTP_SIDE_CASH_REPAY_MARGIN: int
XTP_SIDE_STOCK_REPAY_STOCK: int
XTP_SIDE_UNKNOWN: int
XTP_POSITION_EFFECT_INIT: int
XTP_POSITION_EFFECT_OPEN: int
XTP_POSITION_EFFECT_CLOSE: int
XTP_POSITION_EFFECT_FORCECLOSE: int
XTP_POSITION_EFFECT_CLOSETODAY: int
XTP_POSITION_EFFECT_CLOSEYESTERDAY: int
XTP_POSITION_EFFECT_FORCEOFF: int
XTP_POSITION_EFFECT_LOCALFORCECLOSE: int
XTP_POSITION_EFFECT_UNKNOWN: int
XTP_TRDT_COMMON: int
XTP_TRDT_CASH: int
XTP_TRDT_PRIMARY: int
XTP_ORDT_Normal: int
XTP_ORDT_DeriveFromQuote: int
XTP_ORDT_DeriveFromCombination: int
XTP_ORDT_Combination: int
XTP_ORDT_ConditionalOrder: int
XTP_ORDT_Swap: int
XTP_ERR_MSG_LEN: int
XTP_ACCOUNT_PASSWORD_LEN: int

