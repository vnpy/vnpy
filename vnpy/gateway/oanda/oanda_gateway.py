"""
author: nanoric
todo:
    * query history
"""
from dataclasses import dataclass
from datetime import datetime
from typing import Any, Dict, List, Optional, Tuple

from vnpy.event import Event
from vnpy.trader.constant import (Direction, Exchange, Interval, Offset, OrderType, Status)
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (BarData, CancelRequest, HistoryRequest, OrderData, OrderRequest,
                                SubscribeRequest)
from .oanda_common import INTERVAL_VT2OANDA_DELTA, ORDER_TYPE_OANDA2VT, local_tz, parse_time, utc_tz
from .oanda_rest_api import HistoryDataNextInfo, OandaRestApi
from .oanda_stream_api import OandaStreamApi

_ = lambda x: x  # noqa


@dataclass()
class HistoryDataInfo:
    bars: List[BarData]
    extra: Any


class OandaGateway(BaseGateway):
    """
    VN Trader Gateway for BitMEX connection.
    """

    default_setting = {
        "APIKey": "",
        "会话数": 3,
        "服务器": ["REAL", "TESTNET"],
        "代理地址": "",
        "代理端口": "",
    }
    HISTORY_RECORD_PER_REQUEST = 5000  # # of records per history request

    exchanges = [Exchange.OANDA]

    def __init__(self, event_engine):
        """Constructor"""
        super(OandaGateway, self).__init__(event_engine, "OANDA")

        self.rest_api = OandaRestApi(self)
        self.stream_api = OandaStreamApi(self)

        self.account_id: Optional[str] = None

        self.orders: Dict[str, OrderData] = {}
        self.local2sys_map: Dict[str, str] = {}
        event_engine.register(EVENT_TIMER, self.process_timer_event)

    def connect(self, setting: dict):
        """"""
        key = setting["APIKey"]
        session_number = setting["会话数"]
        server = setting["服务器"]
        proxy_host = setting["代理地址"]
        proxy_port = setting["代理端口"]

        if proxy_port.isdigit():
            proxy_port = int(proxy_port)
        else:
            proxy_port = 0

        self.stream_api.connect(key, session_number,
                                server, proxy_host, proxy_port)
        self.rest_api.connect(key, session_number,
                              server, proxy_host, proxy_port)
        self.query_account()

    def subscribe(self, req: SubscribeRequest):
        """"""
        assert self.account_id is not None, _("请先初始化并连接RestAPI")
        self.stream_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.rest_api.cancel_order(req)

    def query_account(self):
        """"""
        self.rest_api.query_accounts()

    def query_position(self):
        """"""
        self.rest_api.query_positions()

    def query_first_history(self,
                            symbol: str,
                            interval: Interval,
                            start: datetime,
                            ) -> Tuple[List[BarData], "HistoryDataNextInfo"]:

        # datetime for a bar is close_time
        # we got open_time from API.
        adjustment = INTERVAL_VT2OANDA_DELTA[interval]

        utc_time = start.replace(tzinfo=local_tz).astimezone(tz=utc_tz)
        return self.rest_api.query_history(
            symbol=symbol,
            interval=interval,

            # todo: vnpy: shall all datetime object use tzinfo?
            start=utc_time - adjustment,
        )

    def query_next_history(self,
                           next_info: Any,
                           ):
        data: "HistoryDataNextInfo" = next_info
        return self.rest_api.query_history(
            symbol=data.symbol,
            interval=data.interval,
            start=data.end,
        )

    def query_history(self, req: HistoryRequest):
        """
        todo: vnpy: download in parallel
        todo: vnpy: use yield to simplify logic
        :raises RequestFailedException: if server reply an error.
                Any Exception might be raised from requests.request: network error.
        """
        history = []

        symbol = req.symbol
        interval = req.interval
        start = req.start

        bars, next_info = self.query_first_history(
            symbol=symbol,
            interval=interval,
            start=start,
        )
        msg = f"获取历史数据成功，{req.symbol} - {req.interval.value}，{bars[0].datetime} - {bars[-1].datetime}"
        self.write_log(msg)
        history.extend(bars)

        end = req.end
        if end is None:
            end = datetime.now()
        if bars[-1].datetime >= end or len(bars) < self.HISTORY_RECORD_PER_REQUEST:
            return history
        while True:
            bars, next_info = self.query_next_history(next_info)
            history.extend(bars)

            msg = f"获取历史数据成功，{req.symbol} - {req.interval.value}，{bars[0].datetime} - {bars[-1].datetime}"
            self.write_log(msg)

            # Break if total data count less than <count> (latest date collected)
            if bars[-1].datetime >= end or len(bars) < self.HISTORY_RECORD_PER_REQUEST:
                break
        return history

    def close(self):
        """"""
        self.rest_api.stop()
        self.stream_api.stop()

    def process_timer_event(self, event: Event):
        """"""
        if self.rest_api.fully_initialized:
            self.rest_api.query_account_changes()

    def write_log(self, msg: str):
        print(msg)
        return super().write_log(msg)

    def parse_order_data(self, data, status: Status, time_key: str):
        client_extension = data.get('clientExtensions', None)
        if client_extension is None:
            order_id = data['id']
        else:
            order_id = client_extension['id']
        vol = int(data['units'])
        type_ = ORDER_TYPE_OANDA2VT[data['type']]

        order = OrderData(
            gateway_name=self.gateway_name,
            symbol=data['instrument'],
            exchange=Exchange.OANDA,
            orderid=order_id,
            type=type_,
            direction=Direction.LONG if vol > 0 else Direction.SHORT,
            offset=Offset.NONE,
            price=float(data['price']) if type_ is not OrderType.MARKET else 0.0,
            volume=abs(vol),
            # status=STATUS_OANDA2VT[data['state']],
            status=status,
            time=parse_time(data[time_key]),
        )
        self.orders[order_id] = order
        return order
