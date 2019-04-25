from typing import Any, Sequence

from vnpy.api.xtp.vnxtp import (
    OrderBookStruct,
    XTP,
    XTPMarketDataStruct,
    XTPQuoteStaticInfo,
    XTPRspInfoStruct,
    XTPSpecificTickerStruct,
    XTPTickByTickStruct,
    XTPTickerPriceInfo,
    XTP_EXCHANGE_TYPE,
    XTP_LOG_LEVEL,
    XTP_PROTOCOL_TYPE,
    XTP_TICKER_TYPE_STOCK,
    XTP_TICKER_TYPE_INDEX,
    XTP_TICKER_TYPE_FUND,
    XTP_TICKER_TYPE_BOND,
    XTP_TICKER_TYPE_OPTION,
    XTP_PROTOCOL_TCP,
    XTP_PROTOCOL_UDP
)

from vnpy.event import EventEngine
from vnpy.trader.constant import Exchange, Product
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

PRODUCT_XTP2VT = {
    XTP_TICKER_TYPE_STOCK: Product.EQUITY,
    XTP_TICKER_TYPE_INDEX: Product.INDEX,
    XTP_TICKER_TYPE_FUND: Product.FUND,
    XTP_TICKER_TYPE_BOND: Product.BOND,
    XTP_TICKER_TYPE_OPTION: Product.OPTION
}


symbol_name_map = {}


class XtpGateway(BaseGateway):

    default_setting = {
        "账号": "",
        "密码": "",
        "客户号": 1,
        "行情地址": "",
        "行情端口": 0,
        "交易地址": "",
        "交易端口": 0,
        "行情协议": ["TCP", "UDP"]
    }

    def __init__(self, event_engine: EventEngine):
        """"""
        super().__init__(event_engine, "XTP")

        self.quote_api = XtpQuoteApi(self)

    def connect(self, setting: dict):
        """"""
        userid = setting['账号']
        password = setting['密码']
        client_id = setting['客户号']
        quote_ip = setting['行情地址']
        quote_port = setting['行情端口']
        trade_ip = setting['交易地址']
        trade_port = setting['交易端口']
        quote_protocol = setting["行情协议"]

        self.quote_api.connect(userid, password, client_id,
                               quote_ip, quote_port, quote_protocol)

    def close(self):
        """"""
        pass

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.quote_api.subscrbie(req)

    def send_order(self, req: OrderRequest) -> str:
        pass

    def cancel_order(self, req: CancelRequest):
        pass

    def query_account(self):
        pass

    def query_position(self):
        pass


class XtpQuoteApi(API.QuoteSpi):

    def __init__(self, gateway: BaseGateway):
        """"""
        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.userid = ""
        self.password = ""
        self.client_id = ""
        self.server_ip = ""
        self.server_port = ""
        self.server_protocol = ""

        self.api = None

    def connect(
        self,
        userid: str,
        password: str,
        client_id: str,
        server_ip: str,
        server_port: str,
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
            self.quote_protocol = XTP_PROTOCOL_TCP
        else:
            self.quote_protocol = XTP_PROTOCOL_UDP

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
        if error_info.error_id:
            msg = f"{func_name}发生错误, 代码：{error_info.error_id}，信息：{error_info.error_msg}"
            self.gateway.write_log(msg)
            return True
        else:
            return False

    def OnDisconnected(self, reason: int) -> Any:
        """"""
        self.gateway.write_log("行情服务器连接断开")

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
        timestamp = market_data.date_time

        tick = TickData(
            symbol=market_data.ticker,
            exchange=EXCHANGE_XTP2VT[market_data.exchange_id],
            datetime=timestamp,
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
        return
        # if self.check_error("查询合约", error_info):
        #     return

        # contract = ContractData(
        #     symbol=ticker_info.ticker,
        #     exchange=EXCHANGE_XTP2VT[ticker_info.exchange_id],
        #     name=ticker_info.ticker_name,
        #     product=PRODUCT_XTP2VT[ticker_info.ticker_type],
        #     size=1,
        #     pricetick=ticker_info.pricetick,
        #     min_volume=ticker_info.buy_qty_unit,
        #     gateway_name=self.gateway_name
        # )
        # self.gateway.on_contract(contract)

        # symbol_name_map[contract.vt_symbol] = contract.name

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
