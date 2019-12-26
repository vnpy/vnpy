"""
tick 文件记录
华富资产
"""
import os
import csv
from threading import Thread
from queue import Queue, Empty
from copy import copy
from collections import defaultdict
from datetime import datetime

from vnpy.event import Event, EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.constant import Exchange
from vnpy.trader.object import (
    SubscribeRequest,
    TickData,
    ContractData
)
from vnpy.trader.event import EVENT_TICK, EVENT_CONTRACT
from vnpy.trader.utility import load_json, save_json
from vnpy.app.spread_trading.base import EVENT_SPREAD_DATA, SpreadData


APP_NAME = "DataRecorder"

EVENT_RECORDER_LOG = "eRecorderLog"
EVENT_RECORDER_UPDATE = "eRecorderUpdate"


class TickFileRecorder(object):
    """ Tick 文件保存"""
    def __init__(self, tick_folder: str):

        self.tick_dict = defaultdict(list)   # symbol_hour_min: []

        self.tick_folder = tick_folder

        self.last_minute = 0

    def save_tick_data(self, tick_list: list = []):
        """接收外部的保存tick请求"""
        min = None
        for tick in tick_list:
            min = tick.datetime.minute
            key = f'{tick.vt_symbol}_{tick.datetime.hour}-{tick.datetime.minute}'
            save_list = self.tick_dict[key]
            save_list.append(tick)

        if min is not None and min != self.last_minute:
            self.last_minute = min
            self.save_expire_datas()

    def save_expire_datas(self):
        """保存超时得数据"""
        dt = datetime.now()
        for key in [key for key in self.tick_dict.keys() if not key.endswith(f'{dt.hour}-{dt.minute}')]:
            vt_symbol = key.split('_')[0]
            tick_list = self.tick_dict.pop(key)

            self.append_ticks_2_file(symbol=vt_symbol, tick_list=tick_list)

    def append_ticks_2_file(self, symbol: str, tick_list: list):
        """创建/追加tick list 到csv文件"""
        if len(tick_list) == 0:
            return

        trading_day = tick_list[0].trading_day

        file_folder = os.path.abspath(os.path.join(self.tick_folder, trading_day.replace('-', '/')))
        if not os.path.exists(file_folder):
            os.makedirs(file_folder)

        file_name = os.path.abspath(os.path.join(file_folder, f'{symbol}_{trading_day}.csv'))

        dict_fieldnames = sorted(list(tick_list[0].__dict__))

        dict_fieldnames.remove('datetime')

        dict_fieldnames.insert(0, 'datetime')

        if not os.path.exists(file_name):
            # 写入表头
            print(f'create and write data into {file_name}')
            with open(file_name, 'a', encoding='utf8', newline='') as csvWriteFile:
                writer = csv.DictWriter(f=csvWriteFile, fieldnames=dict_fieldnames, dialect='excel')
                writer.writeheader()
                for tick in tick_list:
                    d = tick.__dict__
                    d.update({'datetime': tick.datetime.strftime('%Y-%m-%d %H:%M:%S.%f')})
                    writer.writerow(d)
        else:
            # 写入数据
            print(f'write data into {file_name}')
            with open(file_name, 'a', encoding='utf8', newline='') as csvWriteFile:
                writer = csv.DictWriter(f=csvWriteFile, fieldnames=dict_fieldnames, dialect='excel', extrasaction='ignore')
                for tick in tick_list:
                    d = tick.__dict__
                    d.update({'datetime': tick.datetime.strftime('%Y-%m-%d %H:%M:%S.%f')})
                    writer.writerow(d)


class TickRecorderEngine(BaseEngine):
    """"""
    setting_filename = "data_recorder_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.queue = Queue()
        self.thread = Thread(target=self.run)
        self.active = False

        self.tick_recordings = {}
        self.tick_folder = ''

        self.load_setting()

        self.tick_recorder = TickFileRecorder(self.tick_folder)

        self.register_event()
        self.start()
        self.put_event()

    def load_setting(self):
        """"""
        setting = load_json(self.setting_filename)
        self.tick_recordings = setting.get("tick", {})
        self.tick_folder = setting.get('tick_folder', os.getcwd())

    def save_setting(self):
        """"""
        setting = {
            "tick": self.tick_recordings
        }
        save_json(self.setting_filename, setting)

    def run(self):
        """"""
        while self.active:
            try:
                task = self.queue.get(timeout=1)
                task_type, data = task

                if task_type == "tick":
                    self.tick_recorder.save_tick_data([data])

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
        self.event_engine.register(
            EVENT_SPREAD_DATA, self.process_spread_event)

    def update_tick(self, tick: TickData):
        """"""
        if tick.vt_symbol in self.tick_recordings:
            self.record_tick(tick)

    def process_tick_event(self, event: Event):
        """"""
        tick = event.data
        self.update_tick(tick)

    def process_contract_event(self, event: Event):
        """"""
        contract = event.data
        vt_symbol = contract.vt_symbol

        if vt_symbol in self.tick_recordings:
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
        print(msg)

    def put_event(self):
        """"""
        tick_symbols = list(self.tick_recordings.keys())
        tick_symbols.sort()

        data = {
            "tick": tick_symbols
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

    def subscribe(self, contract: ContractData):
        """"""
        req = SubscribeRequest(
            symbol=contract.symbol,
            exchange=contract.exchange
        )
        self.main_engine.subscribe(req, contract.gateway_name)
