# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/tests
# @File     : event_simulator.py
# @Time     : 2024/12/19 21:52
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description: simulate sending event signals

from vnpy.event import EventEngine, Event
from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.object import BarData, TickData
from vnpy.trader.event import EVENT_BAR, EVENT_TICK
from vnpy.trader.utility import load_json
from vnpy.trader.engine import MainEngine
from vnpy.trader.setting import SETTINGS
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.app import BaseApp
from vnpy.trader.utility import extract_vt_symbol
from vnpy.trader.object import HistoryRequest


class EventSimulator:
    """
    Class for simulating sending event signals
    """

    def __init__(self):
        """"""
        self.event_engine = EventEngine()
        self.main_engine = MainEngine(self.event_engine)

        self.main_engine.add_gateway(MockGateway)
        self.main_engine.add_app(MockApp)

        self.main_engine.init_engine()

    def send_tick_event(self):
        """"""
        tick = TickData(
            symbol="btcusdt",
            exchange=Exchange.BINANCE,
            datetime="2024-12-19 12:00:00",
            name="BTCUSDT",
            volume=1.0,
            open_interest=0,
            last_price=10000,
            last_volume=1.0,
            limit_up=11000,
            limit_down=9000,
            open_price=10000,
            high_price=10000,
            low_price=10000,
            pre_close=10000,
            bid_price_1=9999,
            bid_volume_1=1.0,
            ask_price_1=10001,
            ask_volume_1=1.0,
            gateway_name="mock"
        )

        event = Event(EVENT_TICK, tick)
        self.event_engine.put(event)

    def send_bar_event(self):
        """"""
        bar = BarData(
            symbol="btcusdt",
            exchange=Exchange.BINANCE,
            datetime="2024-12-19 12:00:00",
            interval=Interval.MINUTE,
            volume=1.0,
            open_interest=0,
            open_price=10000,
            high_price=10000,
            low_price=10000,
            close_price=10000,
            gateway_name="mock"
        )

        event = Event(EVENT_BAR, bar)
        self.event_engine.put(event)

    def run(self):
        """"""
        self.send_tick_event()
        self.send_bar_event()
