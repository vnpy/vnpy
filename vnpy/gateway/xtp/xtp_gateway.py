from typing import Any, Sequence
from datetime import datetime
from threading import Thread

from vnpy.api.xtp.vnxtp import (
    XTP,
    set_async_callback_exception_handler,
    AsyncDispatchException,
    OrderBookStruct,
    XTPMarketDataStruct,
    XTPQuoteStaticInfo,
    XTPRspInfoStruct,
    XTPSpecificTickerStruct,
    XTPTickByTickStruct,
    XTPTickerPriceInfo,
    XTPOrderInsertInfo,
    XTPOrderInfo,
    XTPTradeReport,
    XTPOrderCancelInfo,
    XTPCrdDebtInfo,
    XTPQueryStkPositionRsp,
    XTPQueryAssetRsp,
    XTPStructuredFundInfo,
    XTPFundTransferNotice,
    XTPQueryETFBaseRsp,
    XTPQueryETFComponentRsp,
    XTPQueryIPOTickerRsp,
    XTPQueryIPOQuotaRsp,
    XTPQueryOptionAuctionInfoRsp,
    XTP_EXCHANGE_TYPE,
    XTP_LOG_LEVEL,
    XTP_PROTOCOL_TYPE,
    XTP_TE_RESUME_TYPE,
    XTP_SIDE_BUY,
    XTP_SIDE_SELL,
    XTP_SIDE_MARGIN_TRADE,
    XTP_SIDE_SHORT_SELL,
    XTP_SIDE_REPAY_MARGIN,
    XTP_SIDE_REPAY_STOCK,
    XTP_ACCOUNT_TYPE,
    XTP_BUSINESS_TYPE,
    XTP_TICKER_TYPE,
    XTP_MARKET_TYPE,
    XTP_PRICE_TYPE,
    XTP_ORDER_STATUS_TYPE
)
from vnpy.event import EventEngine
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.constant import Exchange, Product, Direction, OrderType, Status, Offset
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (CancelRequest, OrderRequest, SubscribeRequest,
                                TickData, ContractData, OrderData, TradeData,
                                PositionData, AccountData)
from vnpy.trader.utility import get_folder_path


API = XTP.API


EXCHANGE_XTP2VT = {
    XTP_EXCHANGE_TYPE.XTP_EXCHANGE_SH: Exchange.SSE,
    XTP_EXCHANGE_TYPE.XTP_EXCHANGE_SZ: Exchange.SZSE,
}
EXCHANGE_VT2XTP = {v: k for k, v in EXCHANGE_XTP2VT.items()}

MARKET_XTP2VT = {
    XTP_MARKET_TYPE.XTP_MKT_SH_A: Exchange.SSE,
    XTP_MARKET_TYPE.XTP_MKT_SZ_A: Exchange.SZSE
}
MARKET_VT2XTP = {v: k for k, v in MARKET_XTP2VT.items()}

PRODUCT_XTP2VT = {
    XTP_TICKER_TYPE.XTP_TICKER_TYPE_STOCK: Product.EQUITY,
    XTP_TICKER_TYPE.XTP_TICKER_TYPE_INDEX: Product.INDEX,
    XTP_TICKER_TYPE.XTP_TICKER_TYPE_FUND: Product.FUND,
    XTP_TICKER_TYPE.XTP_TICKER_TYPE_BOND: Product.BOND,
    XTP_TICKER_TYPE.XTP_TICKER_TYPE_OPTION: Product.OPTION
}

# DIRECTION_VT2XTP = {
#     Direction.LONG: XTP_SIDE_BUY,
#     Direction.SHORT: XTP_SIDE_SELL
# }
DIRECTION_VT2XTP = {
    (Direction.LONG, Offset.OPEN): XTP_SIDE_MARGIN_TRADE,
    (Direction.SHORT, Offset.CLOSE): XTP_SIDE_REPAY_MARGIN,
    (Direction.SHORT, Offset.OPEN): XTP_SIDE_SHORT_SELL,
    (Direction.LONG, Offset.CLOSE): XTP_SIDE_REPAY_STOCK,
    (Direction.SHORT, Offset.NONE): XTP_SIDE_BUY,
    (Direction.LONG, Offset.NONE): XTP_SIDE_SELL,
}
DIRECTION_XTP2VT = {v: k for k, v in DIRECTION_VT2XTP.items()}

ORDERTYPE_VT2XTP = {
    OrderType.LIMIT: XTP_PRICE_TYPE.XTP_PRICE_LIMIT,
    OrderType.MARKET: XTP_PRICE_TYPE.XTP_PRICE_BEST5_OR_CANCEL
}
ORDERTYPE_XTP2VT = {v: k for k, v in ORDERTYPE_VT2XTP.items()}

STATUS_XTP2VT = {
    XTP_ORDER_STATUS_TYPE.XTP_ORDER_STATUS_INIT: Status.SUBMITTING,
    XTP_ORDER_STATUS_TYPE.XTP_ORDER_STATUS_ALLTRADED: Status.ALLTRADED,
    XTP_ORDER_STATUS_TYPE.XTP_ORDER_STATUS_PARTTRADEDQUEUEING: Status.PARTTRADED,
    XTP_ORDER_STATUS_TYPE.XTP_ORDER_STATUS_PARTTRADEDNOTQUEUEING: Status.CANCELLED,
    XTP_ORDER_STATUS_TYPE.XTP_ORDER_STATUS_NOTRADEQUEUEING: Status.NOTTRADED,
    XTP_ORDER_STATUS_TYPE.XTP_ORDER_STATUS_CANCELED: Status.CANCELLED,
    XTP_ORDER_STATUS_TYPE.XTP_ORDER_STATUS_REJECTED: Status.REJECTED,
}


symbol_name_map = {}
symbol_exchange_map = {}


class XtpGateway(BaseGateway):

    default_setting = {
        "账号": "",
        "密码": "",
        "客户号": 1,
        "行情地址": "",
        "行情端口": 0,
        "交易地址": "",
        "交易端口": 0,
        "行情协议": ["TCP", "UDP"],
        "授权码": ""
    }

    exchanges = list(EXCHANGE_VT2XTP.keys())

    def __init__(self, event_engine: EventEngine):
        """"""
        super().__init__(event_engine, "XTP")

        self.quote_api = XtpQuoteApi(self)
        self.trader_api = XtpTraderApi(self)

        set_async_callback_exception_handler(
            self._async_callback_exception_handler)

    def connect(self, setting: dict):
        """"""
        userid = setting['账号']
        password = setting['密码']
        client_id = int(setting['客户号'])
        quote_ip = setting['行情地址']
        quote_port = int(setting['行情端口'])
        trader_ip = setting['交易地址']
        trader_port = int(setting['交易端口'])
        quote_protocol = setting["行情协议"]
        software_key = setting["授权码"]

        self.quote_api.connect(userid, password, client_id,
                               quote_ip, quote_port, quote_protocol)
        self.trader_api.connect(userid, password, client_id,
                                trader_ip, trader_port, software_key)
        self.init_query()

    def close(self):
        """"""
        self.quote_api.close()
        self.trader_api.close()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.quote_api.subscrbie(req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        return self.trader_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.trader_api.cancel_order(req)

    def query_account(self):
        """"""
        self.trader_api.query_account()

    def query_position(self):
        """"""
        self.trader_api.query_position()

    def process_timer_event(self, event):
        """"""
        self.count += 1
        if self.count < 2:
            return
        self.count = 0

        func = self.query_functions.pop(0)
        func()
        self.query_functions.append(func)

    def init_query(self):
        """"""
        self.count = 0
        self.query_functions = [self.query_account, self.query_position]
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def _async_callback_exception_handler(self, e: AsyncDispatchException):
        error_str = f"发生内部错误：\n" f"位置：{e.instance}.{e.function_name}" f"详细信息：{e.what}"
        print(error_str)


class XtpQuoteApi(API.QuoteSpi):

    def __init__(self, gateway: BaseGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.userid = ""
        self.password = ""
        self.client_id: int = 0
        self.server_ip = ""
        self.server_port: int = 0
        self.server_protocol = ""

        self.api = None

    def connect(
        self,
        userid: str,
        password: str,
        client_id: int,
        server_ip: str,
        server_port: int,
        quote_protocol: str
    ):
        """"""
        if self.api:
            return

        self.userid = userid
        self.password = password
        self.client_id = client_id
        self.server_ip = server_ip
        self.server_port = server_port

        if quote_protocol == "CTP":
            self.quote_protocol = XTP_PROTOCOL_TYPE.XTP_PROTOCOL_TCP
        else:
            self.quote_protocol = XTP_PROTOCOL_TYPE.XTP_PROTOCOL_UDP

        # Create API object
        path = str(get_folder_path(self.gateway_name.lower()))

        self.api = API.QuoteApi.CreateQuoteApi(
            self.client_id,
            path,
            XTP_LOG_LEVEL.XTP_LOG_LEVEL_TRACE
        )

        self.api.RegisterSpi(self)
        self.gateway.write_log("行情接口初始化成功")

        # Login to server
        Thread(target=self.login).start()

    def login(self):
        """"""
        ret = self.api.Login(
            self.server_ip,
            self.server_port,
            self.userid,
            self.password,
            self.quote_protocol
        )

        if not ret:
            msg = "行情服务器登录成功"
            self.query_contract()
        else:
            msg = f"行情服务器登录失败，原因：{ret}"
        self.gateway.write_log(msg)

    def close(self):
        """"""
        if self.api:
            self.api.RegisterSpi(None)
            self.api.Release()

    def subscrbie(self, req: SubscribeRequest):
        """"""
        xtp_exchange = EXCHANGE_VT2XTP.get(req.exchange, "")
        self.api.SubscribeMarketData([req.symbol], xtp_exchange)

    def query_contract(self):
        """"""
        for exchange_id in EXCHANGE_XTP2VT.keys():
            self.api.QueryAllTickers(exchange_id)

    def check_error(self, func_name: str, error_info: XTPRspInfoStruct):
        """"""
        if error_info and error_info.error_id:
            msg = f"{func_name}发生错误, 代码：{error_info.error_id}，信息：{error_info.error_msg}"
            self.gateway.write_log(msg)
            return True
        else:
            return False

    def OnDisconnected(self, reason: int) -> Any:
        """"""
        self.gateway.write_log("行情服务器连接断开")

        self.login()

    def OnError(self, error_info: XTPRspInfoStruct) -> Any:
        """"""
        self.check_error("行情接口", error_info)

    def OnSubMarketData(self, ticker: XTPSpecificTickerStruct, error_info: XTPRspInfoStruct,
                        is_last: bool) -> Any:
        """"""
        self.check_error("订阅行情", error_info)

    def OnUnSubMarketData(self, ticker: XTPSpecificTickerStruct, error_info: XTPRspInfoStruct,
                          is_last: bool) -> Any:
        """"""
        pass

    def OnDepthMarketData(self, market_data: XTPMarketDataStruct, bid1_qty: Sequence[int],
                          bid1_count: int, max_bid1_count: int, ask1_qty: Sequence[int],
                          ask1_count: int, max_ask1_count: int) -> Any:
        """"""
        timestamp = str(market_data.data_time)
        dt = datetime.strptime(timestamp, "%Y%m%d%H%M%S%f")

        tick = TickData(
            symbol=market_data.ticker,
            exchange=EXCHANGE_XTP2VT[market_data.exchange_id],
            datetime=dt,
            volume=market_data.qty,
            last_price=market_data.last_price,
            limit_up=market_data.upper_limit_price,
            limit_down=market_data.lower_limit_price,
            open_price=market_data.open_price,
            high_price=market_data.high_price,
            low_price=market_data.low_price,
            pre_close=market_data.pre_close_price,
            bid_price_1=market_data.bid[0],
            bid_price_2=market_data.bid[1],
            bid_price_3=market_data.bid[2],
            bid_price_4=market_data.bid[3],
            bid_price_5=market_data.bid[4],
            ask_price_1=market_data.ask[0],
            ask_price_2=market_data.ask[1],
            ask_price_3=market_data.ask[2],
            ask_price_4=market_data.ask[3],
            ask_price_5=market_data.ask[4],
            bid_volume_1=market_data.bid_qty[0],
            bid_volume_2=market_data.bid_qty[1],
            bid_volume_3=market_data.bid_qty[2],
            bid_volume_4=market_data.bid_qty[3],
            bid_volume_5=market_data.bid_qty[4],
            ask_volume_1=market_data.ask_qty[0],
            ask_volume_2=market_data.ask_qty[1],
            ask_volume_3=market_data.ask_qty[2],
            ask_volume_4=market_data.ask_qty[3],
            ask_volume_5=market_data.ask_qty[4],
            gateway_name=self.gateway_name
        )
        tick.name = symbol_name_map.get(tick.vt_symbol, tick.symbol)

        self.gateway.on_tick(tick)

    def OnSubOrderBook(self, ticker: XTPSpecificTickerStruct, error_info: XTPRspInfoStruct,
                       is_last: bool) -> Any:
        """"""
        pass

    def OnUnSubOrderBook(self, ticker: XTPSpecificTickerStruct, error_info: XTPRspInfoStruct,
                         is_last: bool) -> Any:
        """"""
        pass

    def OnOrderBook(self, order_book: OrderBookStruct) -> Any:
        """"""
        pass

    def OnSubTickByTick(self, ticker: XTPSpecificTickerStruct, error_info: XTPRspInfoStruct,
                        is_last: bool) -> Any:
        """"""
        pass

    def OnUnSubTickByTick(self, ticker: XTPSpecificTickerStruct, error_info: XTPRspInfoStruct,
                          is_last: bool) -> Any:
        """"""
        pass

    def OnTickByTick(self, tbt_data: XTPTickByTickStruct) -> Any:
        """"""
        pass

    def OnSubscribeAllMarketData(self, exchange_id: XTP_EXCHANGE_TYPE,
                                 error_info: XTPRspInfoStruct) -> Any:
        """"""
        pass

    def OnUnSubscribeAllMarketData(self, exchange_id: XTP_EXCHANGE_TYPE,
                                   error_info: XTPRspInfoStruct) -> Any:
        """"""
        pass

    def OnSubscribeAllOrderBook(self, exchange_id: XTP_EXCHANGE_TYPE,
                                error_info: XTPRspInfoStruct) -> Any:
        """"""
        pass

    def OnUnSubscribeAllOrderBook(self, exchange_id: XTP_EXCHANGE_TYPE,
                                  error_info: XTPRspInfoStruct) -> Any:
        """"""
        pass

    def OnSubscribeAllTickByTick(self, exchange_id: XTP_EXCHANGE_TYPE,
                                 error_info: XTPRspInfoStruct) -> Any:
        """"""
        pass

    def OnUnSubscribeAllTickByTick(self, exchange_id: XTP_EXCHANGE_TYPE,
                                   error_info: XTPRspInfoStruct) -> Any:
        """"""
        pass

    def OnQueryAllTickers(self, ticker_info: XTPQuoteStaticInfo, error_info: XTPRspInfoStruct,
                          is_last: bool) -> Any:
        """"""
        if self.check_error("查询合约", error_info):
            return

        contract = ContractData(
            symbol=ticker_info.ticker,
            exchange=EXCHANGE_XTP2VT[ticker_info.exchange_id],
            name=ticker_info.ticker_name,
            product=PRODUCT_XTP2VT[ticker_info.ticker_type],
            size=1,
            pricetick=ticker_info.price_tick,
            min_volume=ticker_info.buy_qty_unit,
            gateway_name=self.gateway_name
        )
        self.gateway.on_contract(contract)

        symbol_name_map[contract.vt_symbol] = contract.name

        if contract.product != Product.INDEX:
            symbol_exchange_map[contract.symbol] = contract.exchange

        if is_last:
            self.gateway.write_log(f"{contract.exchange.value}合约信息查询成功")

    def OnQueryTickersPriceInfo(self, ticker_info: XTPTickerPriceInfo, error_info: XTPRspInfoStruct,
                                is_last: bool) -> Any:
        """"""
        pass

    def OnSubscribeAllOptionMarketData(self, exchange_id: XTP_EXCHANGE_TYPE,
                                       error_info: XTPRspInfoStruct) -> Any:
        """"""
        pass

    def OnUnSubscribeAllOptionMarketData(self, exchange_id: XTP_EXCHANGE_TYPE,
                                         error_info: XTPRspInfoStruct) -> Any:
        """"""
        pass

    def OnSubscribeAllOptionOrderBook(self, exchange_id: XTP_EXCHANGE_TYPE,
                                      error_info: XTPRspInfoStruct) -> Any:
        """"""
        pass

    def OnUnSubscribeAllOptionOrderBook(self, exchange_id: XTP_EXCHANGE_TYPE,
                                        error_info: XTPRspInfoStruct) -> Any:
        """"""
        pass

    def OnSubscribeAllOptionTickByTick(self, exchange_id: XTP_EXCHANGE_TYPE,
                                       error_info: XTPRspInfoStruct) -> Any:
        """"""
        pass

    def OnUnSubscribeAllOptionTickByTick(self, exchange_id: XTP_EXCHANGE_TYPE,
                                         error_info: XTPRspInfoStruct) -> Any:
        """"""
        pass


class XtpTraderApi(API.TraderSpi):

    def __init__(self, gateway: BaseGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.userid = ""
        self.password = ""
        self.client_id = ""
        self.server_ip = ""
        self.server_port = ""
        self.software_key = ""

        self.api = None
        self.session_id = 0
        self.reqid = 0

        # Whether current account supports margin or option
        self.margin_trading = False
        self.option_trading = False

        # 
        self.short_positions = {}

    def connect(
        self,
        userid: str,
        password: str,
        client_id: int,
        server_ip: str,
        server_port: int,
        software_key: str
    ):
        """"""
        if self.api:
            return

        self.userid = userid
        self.password = password
        self.client_id = client_id
        self.server_ip = server_ip
        self.server_port = server_port
        self.software_key = software_key

        # Create API object
        path = str(get_folder_path(self.gateway_name.lower()))

        self.api = API.TraderApi.CreateTraderApi(
            self.client_id,
            path,
            XTP_LOG_LEVEL.XTP_LOG_LEVEL_TRACE
        )

        self.api.RegisterSpi(self)
        self.api.SetSoftwareKey(self.software_key)
        self.api.SubscribePublicTopic(XTP_TE_RESUME_TYPE.XTP_TERT_RESTART)

        self.gateway.write_log("交易接口初始化成功")

        # Login to server
        Thread(target=self.login).start()

    def login(self):
        """"""
        self.session_id = self.api.Login(
            self.server_ip,
            self.server_port,
            self.userid,
            self.password,
            XTP_PROTOCOL_TYPE.XTP_PROTOCOL_TCP
        )

        if self.session_id:
            msg = "交易服务器登录成功"
        else:
            error = self.api.GetApiLastError()
            msg = f"交易服务器登录失败，原因：{error.error_msg}"

        self.gateway.write_log(msg)

    def close(self):
        """"""
        if self.api:
            self.api.RegisterSpi(None)
            self.api.Release()

    def send_order(self, req: OrderRequest) -> str:
        """"""
        if req.exchange not in MARKET_VT2XTP:
            self.gateway.write_log(f"委托失败，不支持的交易所{req.exchange.value}")
            return ""

        if req.type not in ORDERTYPE_VT2XTP:
            self.gateway.write_log(f"委托失败，不支持的委托类型{req.type.value}")
            return ""

        xtp_req = XTPOrderInsertInfo()
        xtp_req.ticker = req.symbol
        xtp_req.market = MARKET_VT2XTP[req.exchange]
        xtp_req.price = req.price
        xtp_req.quantity = int(req.volume)
        xtp_req.side = DIRECTION_VT2XTP.get((req.direction, req.offset), "")
        xtp_req.price_type = ORDERTYPE_VT2XTP[req.type]

        if req.offset == Offset.NONE:
            xtp_req.business_type = XTP_BUSINESS_TYPE.XTP_BUSINESS_TYPE_CASH
        else:
            xtp_req.business_type = XTP_BUSINESS_TYPE.XTP_BUSINESS_TYPE_MARGIN

        orderid = self.api.InsertOrder(xtp_req, self.session_id)

        order = req.create_order_data(str(orderid), self.gateway_name)
        self.gateway.on_order(order)

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        self.api.CancelOrder(int(req.orderid), self.session_id)

    def query_account(self):
        """"""
        if not self.api:
            return

        self.reqid += 1
        self.api.QueryAsset(self.session_id, self.reqid)

    def query_position(self):
        """"""
        if not self.api:
            return

        self.reqid += 1
        self.api.QueryPosition("", self.session_id, self.reqid)

        if self.margin_trading:
            self.reqid += 1
            self.api.QueryCreditDebtInfo(self.session_id, self.reqid)

    def check_error(self, func_name: str, error_info: XTPRspInfoStruct):
        """"""
        if error_info and error_info.error_id:
            msg = f"{func_name}发生错误, 代码：{error_info.error_id}，信息：{error_info.error_msg}"
            self.gateway.write_log(msg)
            return True
        else:
            return False

    def OnDisconnected(self, session_id: int, reason: int) -> Any:
        """"""
        self.gateway.write_log("交易服务器连接断开")

        self.login()

    def OnError(self, error_info: XTPRspInfoStruct) -> Any:
        """"""
        self.check_error("交易接口", error_info)

    def OnOrderEvent(self, order_info: XTPOrderInfo, error_info: XTPRspInfoStruct,
                     session_id: int) -> Any:
        """"""
        self.check_error("委托下单", error_info)

        direction, offset = DIRECTION_XTP2VT[order_info.side]

        order = OrderData(
            symbol=order_info.ticker,
            exchange=MARKET_XTP2VT[order_info.market],
            orderid=str(order_info.order_xtp_id),
            type=ORDERTYPE_XTP2VT[order_info.price_type],
            direction=direction,
            offset=offset,
            price=order_info.price,
            volume=order_info.quantity,
            traded=order_info.qty_traded,
            status=STATUS_XTP2VT[order_info.order_status],
            time=order_info.insert_time,
            gateway_name=self.gateway_name
        )

        self.gateway.on_order(order)

    def OnTradeEvent(self, trade_info: XTPTradeReport, session_id: int) -> Any:
        """"""
        direction, offset = DIRECTION_XTP2VT[trade_info.side]

        trade = TradeData(
            symbol=trade_info.ticker,
            exchange=MARKET_XTP2VT[trade_info.market],
            orderid=str(trade_info.order_xtp_id),
            tradeid=str(trade_info.exec_id),
            direction=direction,
            offset=offset,
            price=trade_info.price,
            volume=trade_info.quantity,
            time=trade_info.trade_time,
            gateway_name=self.gateway_name
        )

        self.gateway.on_trade(trade)

    def OnCancelOrderError(self, cancel_info: XTPOrderCancelInfo, error_info: XTPRspInfoStruct,
                           session_id: int) -> Any:
        """"""
        self.check_error("委托撤单", error_info)

    def OnQueryOrder(self, order_info: XTPOrderInfo, error_info: XTPRspInfoStruct,
                     is_last: bool, session_id: int) -> Any:
        """"""
        if self.check_error("查询委托", error_info):
            return

        self.updateOrder(order_info)

        if is_last:
            self.gateway.write_log("查询委托信息成功")

    def OnQueryTrade(self, trade_info: XTPTradeReport, error_info: XTPRspInfoStruct,
                     is_last: bool, session_id: int) -> Any:
        """"""
        if self.check_error("查询成交", error_info):
            return

        self.updateTrade(trade_info)

        if is_last:
            self.gateway.write_log("查询成交信息成功")

    def OnQueryPosition(self, xtp_position: XTPQueryStkPositionRsp, error_info: XTPRspInfoStruct,
                        request_id: int, is_last: bool, session_id: int) -> Any:
        """"""
        position = PositionData(
            symbol=xtp_position.ticker,
            exchange=MARKET_XTP2VT[xtp_position.market],
            direction=Direction.LONG,
            volume=xtp_position.total_qty,
            frozen=xtp_position.locked_position,
            price=xtp_position.avg_price,
            pnl=xtp_position.unrealized_pnl,
            yd_volume=xtp_position.yesterday_position,
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(position)

    def OnQueryAsset(self, asset: XTPQueryAssetRsp, error_info: XTPRspInfoStruct,
                     request_id: int, is_last: bool, session_id: int) -> Any:
        """"""
        account = AccountData(
            accountid=self.userid,
            balance=asset.buying_power,
            frozen=asset.withholding_amount,
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

        if asset.account_type == XTP_ACCOUNT_TYPE.XTP_ACCOUNT_CREDIT:
            self.margin_trading = True
        elif asset.account_type == XTP_ACCOUNT_TYPE.XTP_ACCOUNT_DERIVE:
            self.option_trading = True

    def OnQueryStructuredFund(self, fund_info: XTPStructuredFundInfo, error_info: XTPRspInfoStruct,
                              is_last: bool, session_id: int) -> Any:
        """"""
        pass

    def OnQueryFundTransfer(self, fund_transfer_info: XTPFundTransferNotice, error_info: XTPRspInfoStruct,
                            is_last: bool, session_id: int) -> Any:
        """"""
        pass

    def OnFundTransfer(self, fund_transfer_info: XTPFundTransferNotice, session_id: int) -> Any:
        """"""
        pass

    def OnQueryETF(self, etf_info: XTPQueryETFBaseRsp, error_info: XTPRspInfoStruct,
                   is_last: bool, session_id: int) -> Any:
        """"""
        pass

    def OnQueryETFBasket(self, etf_component_info: XTPQueryETFComponentRsp, error_info: XTPRspInfoStruct,
                         is_last: bool, session_id: int) -> Any:
        """"""
        pass

    def OnQueryIPOInfoList(self, ipo_info: XTPQueryIPOTickerRsp, error_info: XTPRspInfoStruct,
                           is_last: bool, session_id: int) -> Any:
        """"""
        pass

    def OnQueryIPOQuotaInfo(self, quota_info: XTPQueryIPOQuotaRsp, error_info: XTPRspInfoStruct,
                            is_last: bool, session_id: int) -> Any:
        """"""
        pass

    def OnQueryOptionAuctionInfo(self, option_info: XTPQueryOptionAuctionInfoRsp, error_info: XTPRspInfoStruct,
                                 is_last: bool, session_id: int) -> Any:
        """"""
        pass

    def OnQueryCreditDebtInfo(self, debt_info: XTPCrdDebtInfo, error_info: XTPRspInfoStruct, 
                              request_id: int, is_last: bool, session_id: int) -> Any:
        """"""
        if debt_info.debt_type == 1:
            symbol = debt_info.ticker
            exchange = MARKET_XTP2VT[debt_info.market]
            
            position = self.short_positions.get(symbol, None)
            if not position:
                position = PositionData(
                    symbol=symbol,
                    exchange=exchange,
                    direction=Direction.SHORT,
                    gateway_name=self.gateway_name
                )
                self.short_positions[symbol] = position

            position.volume += debt_info.remain_qty
        
        if is_last:
            for position in self.short_positions.values():
                self.gateway.on_position(position)

            self.short_positions.clear()
