from typing import Any, Sequence

from vnpy.api.xtp.vnxtp import (OrderBookStruct, XTP, XTPMarketDataStruct, XTPQuoteStaticInfo,
                                XTPRspInfoStruct, XTPSpecificTickerStruct, XTPTickByTickStruct,
                                XTPTickerPriceInfo, XTP_EXCHANGE_TYPE, XTP_LOG_LEVEL,
                                XTP_PROTOCOL_TYPE)

from vnpy.event import EventEngine
from vnpy.trader.constant import Exchange
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import CancelRequest, OrderRequest, SubscribeRequest

API = XTP.API
EXCHANGE_XTP2VT = {
    XTP_EXCHANGE_TYPE.XTP_EXCHANGE_SH: Exchange.SSE,
    XTP_EXCHANGE_TYPE.XTP_EXCHANGE_SZ: Exchange.SZSE,
}
EXCHANGE_VT2XTP = {v: k for k, v in EXCHANGE_XTP2VT.items()}


class QuoteSpi(API.QuoteSpi):

    def OnDisconnected(self, reason: int) -> Any:
        print("OnDisconnected")
        return super().OnDisconnected(reason)

    def OnError(self, error_info: XTPRspInfoStruct) -> Any:
        return super().OnError(error_info)

    def OnSubMarketData(self, ticker: XTPSpecificTickerStruct, error_info: XTPRspInfoStruct,
                        is_last: bool) -> Any:
        print("OnSubMarketData")
        return super().OnSubMarketData(ticker, error_info, is_last)

    def OnUnSubMarketData(self, ticker: XTPSpecificTickerStruct, error_info: XTPRspInfoStruct,
                          is_last: bool) -> Any:
        return super().OnUnSubMarketData(ticker, error_info, is_last)

    def OnDepthMarketData(self, market_data: XTPMarketDataStruct, bid1_qty: Sequence[int],
                          bid1_count: int, max_bid1_count: int, ask1_qty: Sequence[int],
                          ask1_count: int, max_ask1_count: int) -> Any:
        print("OnDepthMarketData")
        return super().OnDepthMarketData(market_data, bid1_qty, bid1_count, max_bid1_count,
                                         ask1_qty, ask1_count, max_ask1_count)

    def OnSubOrderBook(self, ticker: XTPSpecificTickerStruct, error_info: XTPRspInfoStruct,
                       is_last: bool) -> Any:
        return super().OnSubOrderBook(ticker, error_info, is_last)

    def OnUnSubOrderBook(self, ticker: XTPSpecificTickerStruct, error_info: XTPRspInfoStruct,
                         is_last: bool) -> Any:
        return super().OnUnSubOrderBook(ticker, error_info, is_last)

    def OnOrderBook(self, order_book: OrderBookStruct) -> Any:
        return super().OnOrderBook(order_book)

    def OnSubTickByTick(self, ticker: XTPSpecificTickerStruct, error_info: XTPRspInfoStruct,
                        is_last: bool) -> Any:
        return super().OnSubTickByTick(ticker, error_info, is_last)

    def OnUnSubTickByTick(self, ticker: XTPSpecificTickerStruct, error_info: XTPRspInfoStruct,
                          is_last: bool) -> Any:
        return super().OnUnSubTickByTick(ticker, error_info, is_last)

    def OnTickByTick(self, tbt_data: XTPTickByTickStruct) -> Any:
        return super().OnTickByTick(tbt_data)

    def OnSubscribeAllMarketData(self, exchange_id: XTP_EXCHANGE_TYPE,
                                 error_info: XTPRspInfoStruct) -> Any:
        return super().OnSubscribeAllMarketData(exchange_id, error_info)

    def OnUnSubscribeAllMarketData(self, exchange_id: XTP_EXCHANGE_TYPE,
                                   error_info: XTPRspInfoStruct) -> Any:
        return super().OnUnSubscribeAllMarketData(exchange_id, error_info)

    def OnSubscribeAllOrderBook(self, exchange_id: XTP_EXCHANGE_TYPE,
                                error_info: XTPRspInfoStruct) -> Any:
        return super().OnSubscribeAllOrderBook(exchange_id, error_info)

    def OnUnSubscribeAllOrderBook(self, exchange_id: XTP_EXCHANGE_TYPE,
                                  error_info: XTPRspInfoStruct) -> Any:
        return super().OnUnSubscribeAllOrderBook(exchange_id, error_info)

    def OnSubscribeAllTickByTick(self, exchange_id: XTP_EXCHANGE_TYPE,
                                 error_info: XTPRspInfoStruct) -> Any:
        return super().OnSubscribeAllTickByTick(exchange_id, error_info)

    def OnUnSubscribeAllTickByTick(self, exchange_id: XTP_EXCHANGE_TYPE,
                                   error_info: XTPRspInfoStruct) -> Any:
        return super().OnUnSubscribeAllTickByTick(exchange_id, error_info)

    def OnQueryAllTickers(self, ticker_info: XTPQuoteStaticInfo, error_info: XTPRspInfoStruct,
                          is_last: bool) -> Any:
        return super().OnQueryAllTickers(ticker_info, error_info, is_last)

    def OnQueryTickersPriceInfo(self, ticker_info: XTPTickerPriceInfo, error_info: XTPRspInfoStruct,
                                is_last: bool) -> Any:
        return super().OnQueryTickersPriceInfo(ticker_info, error_info, is_last)

    def OnSubscribeAllOptionMarketData(self, exchange_id: XTP_EXCHANGE_TYPE,
                                       error_info: XTPRspInfoStruct) -> Any:
        return super().OnSubscribeAllOptionMarketData(exchange_id, error_info)

    def OnUnSubscribeAllOptionMarketData(self, exchange_id: XTP_EXCHANGE_TYPE,
                                         error_info: XTPRspInfoStruct) -> Any:
        return super().OnUnSubscribeAllOptionMarketData(exchange_id, error_info)

    def OnSubscribeAllOptionOrderBook(self, exchange_id: XTP_EXCHANGE_TYPE,
                                      error_info: XTPRspInfoStruct) -> Any:
        return super().OnSubscribeAllOptionOrderBook(exchange_id, error_info)

    def OnUnSubscribeAllOptionOrderBook(self, exchange_id: XTP_EXCHANGE_TYPE,
                                        error_info: XTPRspInfoStruct) -> Any:
        return super().OnUnSubscribeAllOptionOrderBook(exchange_id, error_info)

    def OnSubscribeAllOptionTickByTick(self, exchange_id: XTP_EXCHANGE_TYPE,
                                       error_info: XTPRspInfoStruct) -> Any:
        return super().OnSubscribeAllOptionTickByTick(exchange_id, error_info)

    def OnUnSubscribeAllOptionTickByTick(self, exchange_id: XTP_EXCHANGE_TYPE,
                                         error_info: XTPRspInfoStruct) -> Any:
        return super().OnUnSubscribeAllOptionTickByTick(exchange_id, error_info)


class XtpGateway(BaseGateway):

    def __init__(self, event_engine: "EventEngine"):
        self.client_id: int = 1
        self.quote_api = API.QuoteApi.CreateQuoteApi(
            self.client_id,  # todo: change client id
            "log",  # todo: use vnpy temp path
            XTP_LOG_LEVEL.XTP_LOG_LEVEL_TRACE
        )
        self.quote_spi = QuoteSpi()
        super().__init__(event_engine, "XTP")

    default_setting = {
        "client_id": "0",
        "quote_server_ip": "",
        "quote_server_port": "",
        "quote_server_protocol": ["TCP", "UDP"],
        "quote_userid": "",
        "quote_password": "",
    }

    def connect(self, setting: dict):
        self.client_id = int(setting['client_id'])
        quote_server_ip = setting['quote_server_ip']
        quote_server_port = int(setting['quote_server_port'])
        quote_server_protocol = setting['quote_server_protocol']
        quote_userid = setting['quote_userid']
        quote_password = setting['quote_password']

        quote_protocol = XTP_PROTOCOL_TYPE.XTP_PROTOCOL_TCP if quote_server_protocol == 'TCP' else 'UDP'

        self.quote_api.RegisterSpi(self.quote_spi)
        # self.quote_api.SetHeartBeatInterval(60)

        ret = self.quote_api.Login(
            quote_server_ip,
            quote_server_port,
            quote_userid,
            quote_password,
            quote_protocol
        )
        if ret == 0:
            # login succeed
            self.write_log("Login succeed.")
        pass

    def close(self):
        pass

    def subscribe(self, req: SubscribeRequest):
        ret = self.quote_api.SubscribeMarketData(
            [req.symbol],
            EXCHANGE_VT2XTP[req.exchange],
        )
        if ret != 0:
            print("订阅行情失败")  # improve: return True or False, or raise with reason
        pass

    def send_order(self, req: OrderRequest) -> str:
        pass

    def cancel_order(self, req: CancelRequest):
        pass

    def query_account(self):
        pass

    def query_position(self):
        pass
