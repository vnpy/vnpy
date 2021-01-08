""""""

import sys
import time
from copy import copy
from queue import Queue, Empty
from threading import Thread

from vnpy.app.spread_trading.base import EVENT_SPREAD_DATA, SpreadData
from vnpy.event import Event, EventEngine
from vnpy.trader.constant import Exchange
from vnpy.trader.database import database_manager
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import EVENT_TICK, EVENT_CONTRACT
from vnpy.trader.object import (
    SubscribeRequest,
    TickData,
    BarData,
    ContractData
)
from vnpy.trader.utility import load_json, save_json, BarGenerator

APP_NAME = "DataRecorder"

EVENT_RECORDER_LOG = "eRecorderLog"
EVENT_RECORDER_UPDATE = "eRecorderUpdate"
EVENT_RECORDER_EXCEPTION = "eRecorderException"


class RecorderEngine(BaseEngine):
    """"""
    setting_filename = "data_recorder_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.queue = Queue()
        self.last_commit_time = None
        self.thread = Thread(target=self.run)
        self.active = False

        self.tick_recordings = {}
        self.bar_recordings = {}
        self.bar_generators = {}

        self.load_setting()
        self.register_event()
        self.start()
        self.put_event()

    def load_setting(self):
        """"""
        setting = load_json(self.setting_filename)
        self.tick_recordings = setting.get("tick", {})
        self.bar_recordings = setting.get("bar", {})
        self.batch_size = setting.get("batch_size", 1000)
        self.commit_delay = setting.get("commit_delay", 30)

    def save_setting(self):
        """"""
        setting = {
            "tick": self.tick_recordings,
            "bar": self.bar_recordings
        }
        save_json(self.setting_filename, setting)

    def run(self):
        """"""
        while self.active:

            try:
                items = []

                if self.last_commit_time is None:
                    elapse_time = None
                else:
                    elapse_time = self.last_commit_time + self.commit_delay

                while len(items) < self.batch_size:
                    # First, retrieve all pending items in the queue, up to `self.batch_size` items
                    for _ in range(len(items), self.batch_size):
                        try:
                            item = self.queue.get_nowait()
                            items.append(item)
                        except Empty:
                            break

                    if len(items) >= self.batch_size:
                        break

                    # Second, we wait until `self.__last_commit_time + self.commit_delay`
                    ts = time.time()

                    if elapse_time is None or ts >= elapse_time:
                        break

                    try:
                        item = self.queue.get(timeout=max(0., elapse_time - ts))

                        # We do get something, try to get more
                        items.append(item)
                        continue
                    except Empty:
                        # No more item until the commit time, let's continue to write them back to DB
                        break

                self.last_commit_time = time.time()

                ticks = [data for task_type, data in items if task_type == 'tick']
                bars = [data for task_type, data in items if task_type == 'bar']

                if len(ticks) > 0:
                    database_manager.save_tick_data(ticks)

                if len(bars) > 0:
                    database_manager.save_bar_data(bars)

            except:
                import traceback
                traceback.print_exc()

                self.active = False
                info = sys.exc_info()
                event = Event(EVENT_RECORDER_EXCEPTION, info)
                self.event_engine.put(event)

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

        if Exchange.LOCAL.value not in vt_symbol:
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
        else:
            self.tick_recordings[vt_symbol] = {}

        self.save_setting()
        self.put_event()

        self.write_log(f"添加K线记录成功：{vt_symbol}")

    def add_tick_recording(self, vt_symbol: str):
        """"""
        if vt_symbol in self.tick_recordings:
            self.write_log(f"已在Tick记录列表中：{vt_symbol}")
            return

        # For normal contract
        if Exchange.LOCAL.value not in vt_symbol:
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
        # No need to subscribe for spread data
        else:
            self.tick_recordings[vt_symbol] = {}

        self.save_setting()
        self.put_event()

        self.write_log(f"添加Tick记录成功：{vt_symbol}")

    def remove_bar_recording(self, vt_symbol: str):
        """"""
        if vt_symbol not in self.bar_recordings:
            self.write_log(f"不在K线记录列表中：{vt_symbol}")
            return

        self.bar_recordings.pop(vt_symbol)
        self.save_setting()
        self.put_event()

        self.write_log(f"移除K线记录成功：{vt_symbol}")

    def remove_tick_recording(self, vt_symbol: str):
        """"""
        if vt_symbol not in self.tick_recordings:
            self.write_log(f"不在Tick记录列表中：{vt_symbol}")
            return

        self.tick_recordings.pop(vt_symbol)
        self.save_setting()
        self.put_event()

        self.write_log(f"移除Tick记录成功：{vt_symbol}")

    def register_event(self):
        """"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)
        self.event_engine.register(EVENT_SPREAD_DATA, self.process_spread_event)

    def update_tick(self, tick: TickData):
        """"""
        if tick.vt_symbol in self.tick_recordings:
            self.record_tick(tick)

        if tick.vt_symbol in self.bar_recordings:
            bg = self.get_bar_generator(tick.vt_symbol)
            bg.update_tick(tick)

    def process_tick_event(self, event: Event):
        """"""
        tick = event.data
        self.update_tick(tick)

    def process_contract_event(self, event: Event):
        """"""
        contract = event.data
        vt_symbol = contract.vt_symbol

        if (vt_symbol in self.tick_recordings or vt_symbol in self.bar_recordings):
            self.subscribe(contract)

    def process_spread_event(self, event: Event):
        """"""
        spread: SpreadData = event.data
        tick = spread.to_tick()

        # Filter not inited spread data
        if tick.datetime:
            self.update_tick(tick)

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
