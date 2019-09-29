""""""
from dataclasses import dataclass
from datetime import datetime
from typing import Any, Dict, List, Tuple

from vnpy.event import Event
from vnpy.gateway.bybit.rest_api import BybitRestApi, HistoryDataNextInfo
from vnpy.gateway.bybit.websocket_api import BybitWebsocketApi
from vnpy.trader.constant import (Exchange, Interval, OrderType)
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (BarData, CancelRequest, HistoryRequest, OrderData, OrderRequest,
                                PositionData, SubscribeRequest, TickData)
from .common import (DIRECTION_BYBIT2VT, INTERVAL_VT2BYBIT_INT, OPPOSITE_DIRECTION,
                     ORDER_TYPE_BYBIT2VT, STATUS_BYBIT2VT, STOP_ORDER_STATUS_BYBIT2VT, local_tz,
                     parse_datetime, utc_tz)


@dataclass()
class HistoryDataInfo:
    bars: List[BarData]
    extra: Any


class BybitGateway(BaseGateway):
    """
    VN Trader Gateway for BitMEX connection.
    """

    default_setting = {
        "APIKey": "",
        "PrivateKey": "",
        "会话数": 3,
        "服务器": ["REAL", "TESTNET"],
        "代理地址": "",
        "代理端口": "",
    }
    HISTORY_RECORD_PER_REQUEST = 200  # # of records per history request

    exchanges = [Exchange.BYBIT]

    def __init__(self, event_engine):
        """Constructor"""
        super(BybitGateway, self).__init__(event_engine, "BYBIT")

        self.rest_api = BybitRestApi(self)
        self.ws_api = BybitWebsocketApi(self)

        self.ticks: Dict[str, TickData] = {}
        self.orders: Dict[str, OrderData] = {}
        self.local2sys_map: Dict[str, str] = {}
        event_engine.register(EVENT_TIMER, self.process_timer_event)

    def connect(self, setting: dict):
        """"""
        key = setting["ID"]
        secret = setting["Secret"]
        session_number = setting["会话数"]
        server = setting["服务器"]
        proxy_host = setting["代理地址"]
        proxy_port = setting["代理端口"]

        if proxy_port.isdigit():
            proxy_port = int(proxy_port)
        else:
            proxy_port = 0

        self.rest_api.connect(key, secret, session_number,
                              server, proxy_host, proxy_port)

        self.ws_api.connect(key, secret, server, proxy_host, proxy_port)
        self.rest_api.query_orders()
        self.query_contracts()
        self.query_account()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.ws_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.rest_api.cancel_order(req)

    def query_contracts(self):
        self.rest_api.query_contracts()

    def query_account(self):
        """"""
        self.rest_api.query_position()

    def query_position(self):
        """"""
        self.rest_api.query_position()

    def query_first_history(self,
                            symbol: str,
                            interval: Interval,
                            start: datetime,
                            ) -> Tuple[List[BarData], "HistoryDataNextInfo"]:

        # datetime for a bar is close_time
        # we got open_time from API.
        adjustment = INTERVAL_VT2BYBIT_INT[interval]

        utc_time = start.replace(tzinfo=local_tz).astimezone(tz=utc_tz)
        return self.rest_api.query_history(
            symbol=symbol,
            interval=interval,

            # todo: vnpy: shall all datetime object use tzinfo?
            start=int(utc_time.timestamp()) - adjustment,
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
        # todo: this function: test rate limit
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
        while True:
            bars, next_info = self.query_next_history(next_info)

            msg = f"获取历史数据成功，{req.symbol} - {req.interval.value}，{bars[0].datetime} - {bars[-1].datetime}"
            self.write_log(msg)

            # Break if total data count less than <count> (latest date collected)
            if len(bars) < self.HISTORY_RECORD_PER_REQUEST:
                break
            history.extend(bars)
        return history

    def close(self):
        """"""
        self.rest_api.stop()
        self.ws_api.stop()

    def process_timer_event(self, event: Event):
        """"""
        self.rest_api.increase_rate_limit()
        if self.rest_api.alive:
            self.query_account()
            self.rest_api.query_stop_orders()

    def write_log(self, msg: str):
        return super().write_log(msg)

    def parse_order_data(self, data: dict, time_key: str = 'updated_at'):
        """
        Parse order data from json dict.
        todo: gateway: put this function to another place.
        :note: this method will not fill 'time' record. Fill it by yourself.
        """
        # prefer local_id as order_id
        order_id = data["order_link_id"]
        sys_id = data['order_id']
        if not order_id:
            order_id = sys_id

        # saving mapping from order_id to sys_id
        self.local2sys_map[order_id] = sys_id

        order = self.orders.get(order_id, None)
        time = parse_datetime(data[time_key])

        # filter outdated order
        if order is not None and time < order.time:  # string cmp is ok here.
            return None

        # if order not exist(created outside this client)
        # create it.
        if order is None:
            order = OrderData(
                symbol=data["symbol"],
                exchange=Exchange.BYBIT,
                type=ORDER_TYPE_BYBIT2VT[data["order_type"]],
                orderid=order_id,
                direction=DIRECTION_BYBIT2VT[data["side"]],
                price=data["price"],
                volume=data["qty"],
                time=time,
                gateway_name=self.gateway_name,
            )
            self.orders[order.orderid] = order
        order.traded = data.get("cum_exec_qty", order.traded)
        if 'order_status' in data:
            order.status = STATUS_BYBIT2VT[data["order_status"]]
        return order

    def parse_stop_order_data(self, data):
        """
        Parse order data from json dict.
        todo: put this function to another place.
        :note: this method will not fill 'time' record. Fill it by yourself.
        """
        # prefer local_id as order_id
        order_id = data["order_link_id"]
        sys_id = data['stop_order_id']
        if not order_id:
            order_id = sys_id

        # saving mapping from order_id to sys_id
        self.local2sys_map[order_id] = sys_id

        order = self.orders.get(order_id, None)

        # if order not exist(created outside this client)
        # create it.
        if not order:
            order = OrderData(
                symbol=data["symbol"],
                exchange=Exchange.BYBIT,
                type=OrderType.STOP,
                orderid=order_id,
                direction=DIRECTION_BYBIT2VT[data["side"]],
                price=data["price"],
                volume=data["qty"],
                time=parse_datetime(data['updated_at']),  # this should be filled manually
                gateway_name=self.gateway_name,
            )
            self.orders[order.orderid] = order
            if 'stop_order_status' in data:
                # status = STATUS_BYBIT2VT.get(data["order_status"], None)
                # if status is None:
                #     status = STOP_ORDER_STATUS_BYBIT2VT[data["order_status"]]
                # order.status = status
                order.status = STOP_ORDER_STATUS_BYBIT2VT[data["stop_order_status"]]
        return order

    def orderid2sys(self, order_id: str):
        """
        Convert order_id to sys_id
        """
        return self.local2sys_map[order_id]

    def parse_position_data(self, data):
        position = PositionData(
            gateway_name=self.gateway_name,
            symbol=data["symbol"],
            exchange=Exchange.BYBIT,
            direction=DIRECTION_BYBIT2VT[data['side']],
            volume=data['size'],
            price=data['entry_price']
        )

        # clear opposite direction if necessary
        if position.volume:
            pos2 = PositionData(
                gateway_name=position.gateway_name,
                symbol=position.symbol,
                exchange=Exchange.BYBIT,
                direction=OPPOSITE_DIRECTION[position.direction],
                volume=0,
                price=0,
            )
            return position, pos2
        return position, None

    def on_order(self, order: OrderData):
        """
        Since WebSocket and RestClient will push the same orders asynchronously and separately
        outdated orders should be filtered.
        Outdated orders is filtered by parse_xxx_order_data(), returning None.
        """
        if order is not None:
            super().on_order(order)
