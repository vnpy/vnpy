""""""
from collections import defaultdict
from threading import Thread
from queue import Queue, Empty
from copy import copy

from vnpy.event import Event, EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine, OmsEngine
from vnpy.trader.object import (
    SubscribeRequest,
    TickData,
    BarData,
    ContractData
)
from vnpy.trader.event import EVENT_TICK, EVENT_CONTRACT, EVENT_BAR
from vnpy.trader.utility import load_json, save_json, BarGenerator
from vnpy_clickhouse.clickhouse_database import ClickhouseDatabase

APP_NAME = "DataRecorder"

EVENT_RECORDER_LOG = "eRecorderLog"
EVENT_RECORDER_UPDATE = "eRecorderUpdate"


class RecorderEngine(BaseEngine):
    """用于将从binance等exchange拿到的数据入库, 不负责计算因子"""

    def __init__(self,
                 main_engine: MainEngine,
                 # main_engine: OmsEngine,
                 event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.queue = Queue()
        self.thread = Thread(target=self.run)
        self.active = False

        self.tick_recordings = {}
        self.bar_recordings = {}
        self.bar_generators = {}

        # self.load_setting()
        self.register_event()
        self.start()
        self.put_event()

        # 用clickhouse数据库
        self.database_manager = ClickhouseDatabase()
        self.buffer = defaultdict(list)
        self.buffer_size = 4

    # def load_setting(self):
    #     """"""
    #     setting = load_json(self.setting_filename)
    #     self.tick_recordings = setting.get("tick", {})
    #     self.bar_recordings = setting.get("bar", {})

    # def save_setting(self):
    #     """"""
    #     setting = {
    #         "tick": self.tick_recordings,
    #         "bar": self.bar_recordings
    #     }
    #     save_json(self.setting_filename, setting)

    def run(self):
        """"""
        while self.active:
            try:
                task = self.queue.get(timeout=1)
                task_type, data = task

                if task_type == "tick":
                    self.database_manager.save_tick_data([data])
                elif task_type == "bar":
                    assert isinstance(data, BarData)
                    self.buffer[data.vt_symbol].append(data)
                    to_remove = []
                    for k, v in self.buffer.items():
                        if len(v) > self.buffer_size:
                            to_remove.append(k)
                            self.database_manager.save_bar_data(self.buffer[data.vt_symbol])
                    for k in to_remove:
                        self.buffer.pop(k)

            except Empty:
                continue

    def close(self):
        """"""
        self.active = False

        if self.thread.isAlive():
            self.thread.join()

    def start(self):
        """"""
        self.active = True
        self.thread.start()

    def add_bar_recording(self, vt_symbol: str):
        """"""
        if vt_symbol in self.bar_recordings:
            self.write_log(f"已在K线记录列表中：{vt_symbol}")
            return

        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            self.write_log(f"找不到合约：{vt_symbol}")
            return

        self.bar_recordings[vt_symbol] = {
            "symbol": contract.symbol,
            "exchange": contract.exchange.value,
            "gateway_name": contract.gateway_name
        }

        self.subscribe(contract)
        # self.save_setting()
        self.put_event()

        self.write_log(f"添加K线记录成功：{vt_symbol}")

    def add_tick_recording(self, vt_symbol: str):
        """"""
        if vt_symbol in self.tick_recordings:
            self.write_log(f"已在Tick记录列表中：{vt_symbol}")
            return

        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            self.write_log(f"找不到合约：{vt_symbol}")
            return

        self.tick_recordings[vt_symbol] = {
            "symbol": contract.symbol,
            "exchange": contract.exchange.value,
            "gateway_name": contract.gateway_name
        }

        self.subscribe(contract)
        # self.save_setting()
        self.put_event()

        self.write_log(f"添加Tick记录成功：{vt_symbol}")

    def remove_bar_recording(self, vt_symbol: str):
        """"""
        if vt_symbol not in self.bar_recordings:
            self.write_log(f"不在K线记录列表中：{vt_symbol}")
            return

        self.bar_recordings.pop(vt_symbol)
        # self.save_setting()
        self.put_event()

        self.write_log(f"移除K线记录成功：{vt_symbol}")

    def remove_tick_recording(self, vt_symbol: str):
        """"""
        if vt_symbol not in self.tick_recordings:
            self.write_log(f"不在Tick记录列表中：{vt_symbol}")
            return

        self.tick_recordings.pop(vt_symbol)
        # self.save_setting()
        self.put_event()

        self.write_log(f"移除Tick记录成功：{vt_symbol}")

    def register_event(self):
        """"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_BAR, self.process_bar_event)
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)

    def process_bar_event(self, event: Event):
        """"""
        bar = event.data
        self.add_bar_recording(vt_symbol=bar.vt_symbol)
        if bar.vt_symbol in self.bar_recordings:
            self.record_bar(bar)

    def process_tick_event(self, event: Event):
        """"""
        tick = event.data

        if tick.vt_symbol in self.tick_recordings:
            self.record_tick(tick)

        if tick.vt_symbol in self.bar_recordings:
            bg = self.get_bar_generator(tick.vt_symbol)
            bg.update_tick(tick)

    def process_contract_event(self, event: Event):
        """"""
        contract = event.data
        vt_symbol = contract.vt_symbol

        if (vt_symbol in self.tick_recordings or vt_symbol in self.bar_recordings):
            self.subscribe(contract)

    def write_log(self, msg: str):
        """"""
        event = Event(
            EVENT_RECORDER_LOG,
            msg
        )
        self.event_engine.put(event)

    def put_event(self):
        """"""
        tick_symbols = list(self.tick_recordings.keys())
        tick_symbols.sort()

        bar_symbols = list(self.bar_recordings.keys())
        bar_symbols.sort()

        data = {
            "tick": tick_symbols,
            "bar": bar_symbols
        }

        event = Event(
            EVENT_RECORDER_UPDATE,
            data
        )
        self.event_engine.put(event)

    def record_tick(self, tick: TickData):
        """"""
        task = ("tick", copy(tick))
        self.queue.put(task)

    def record_bar(self, bar: BarData):
        """"""
        task = ("bar", copy(bar))
        self.queue.put(task)

    def get_bar_generator(self, vt_symbol: str):
        """"""
        bg = self.bar_generators.get(vt_symbol, None)

        if not bg:
            bg = BarGenerator(self.record_bar)
            self.bar_generators[vt_symbol] = bg

        return bg

    def subscribe(self, contract: ContractData):
        """"""
        req = SubscribeRequest(
            symbol=contract.symbol,
            exchange=contract.exchange
        )
        self.main_engine.subscribe(req, contract.gateway_name)
