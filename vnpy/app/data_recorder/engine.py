""""""
import time
from collections import defaultdict
from threading import Thread
from queue import Queue, Empty
from copy import deepcopy
from typing import Literal, Optional, Union
from logging import ERROR, INFO, DEBUG, NOTSET, WARNING

import polars as pl

from vnpy.event.engine import Event
from vnpy.trader.event import EVENT_LOG, EVENT_CONTRACT, EVENT_BAR, EVENT_FACTOR, EVENT_RECORDER_UPDATE
from vnpy.trader.engine import BaseEngine, MainEngine, EventEngine
from vnpy.trader.object import (SubscribeRequest, TickData, BarData, FactorData, ContractData, LogData)
from vnpy.trader.utility import BarGenerator
from vnpy.adapters.overview import OverviewHandler
from vnpy.trader.utility import (
    generate_vt_symbol,
    extract_vt_symbol,
    get_file_path,
    extract_factor_key
)
from vnpy.trader.database import (BarOverview, TickOverview, FactorOverview, TV_BaseOverview)

from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.setting import SETTINGS
from vnpy_clickhouse.clickhouse_database import ClickhouseDatabase

APP_NAME = "DataRecorder"
SYSTEM_MODE = SETTINGS.get("system.mode", "LIVE")


class RecorderEngine(BaseEngine):
    """用于将从binance等exchange拿到的数据入库, 不负责计算因子"""

    def __init__(self,
                 main_engine: MainEngine,
                 event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, engine_name=APP_NAME)

        self.queue = Queue()
        self.thread = Thread(target=self.run)
        self.active = False

        # zc
        self.tick_recordings = {}  # list of symbols to record tick data
        self.bar_recordings = {}  # list of symbols to record bar data
        self.factor_recordings = {}  # list of symbols to record bar data
        self.bar_generators = {}

        # zc
        # self.load_setting()
        self.register_event()
        self.start()
        self.put_event()

        # database settings
        self.database_manager = ClickhouseDatabase(event_engine=event_engine)
        self.buffer_bar = defaultdict(list)
        self.buffer_factor = defaultdict(list)
        self.buffer_size = 1  # todo: 调大该数字

        # overview. DO NOT USE IT FOR UPDATING OVERVIEW!
        self.overview_handler_for_result_check = OverviewHandler()  # only used for check data consistency.

    def register_event(self):
        """"""
        # self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_BAR, self.process_bar_event)
        self.event_engine.register(EVENT_FACTOR, self.process_factor_event)
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)

        # self.main_engine.register_log_event(EVENT_RECORDER_LOG)

    def save_data(self,
                  task_type: Optional[Literal["bar", "factor", "tick"]] = None,
                  data=None,
                  force_save: bool = False,
                  stream: bool = False,
                  ):
        """The actual implementation of the core functions that put the data into the database
        
        Parameters
        ----------
        stream : bool
            true when the data is streamed
        task_type :
        data :
        force_save : bool
            Ignore buffer_size and force all current data to be saved

        Returns
        -------

        """
        if task_type == "tick":
            self.database_manager.save_tick_data([data])
        elif task_type == "bar":
            assert isinstance(data, BarData)
            self.buffer_bar[data.vt_symbol].append(data)
            to_remove = []  # 保存完数据后, 将其从buffer中删除
            for k, v in self.buffer_bar.items():
                # do insertion
                if len(v) >= self.buffer_size or force_save:
                    # get info for the data list
                    sample_data = v[0]
                    vt_symbol: str = sample_data.vt_symbol
                    interval: Interval = sample_data.interval
                    symbol, exchange = extract_vt_symbol(vt_symbol, is_factor=False)

                    status = self.database_manager.save_bar_data(v, interval=interval, exchange=exchange)
                    # todo: use status
                    to_remove.append(k)  # to remove the key from buffer

                    # check consistency
                    overview = self.overview_handler_for_result_check.bar_overview.get(vt_symbol, {})
                    ret = self.database_manager.client_bar.select(freq=str(interval.value), ticker_list=symbol,
                                                                  start_time=overview.start,
                                                                  end_time=overview.end, ret='rows')
                    assert self.overview_handler_for_result_check.bar_overview[vt_symbol].count == len(
                        ret) if not SYSTEM_MODE == 'TEST' else True
            for k in to_remove:
                self.buffer_bar[k] = []
        elif task_type == 'factor':
            self.write_log(f"识别到factor", level=DEBUG)
            if isinstance(data, FactorData):
                self.write_log(f"识别到FactorData", level=DEBUG)
                self.buffer_factor[data.vt_symbol].append(data)  # todo: 这里用vt_symbol可以吗???
                to_remove = []
                for k, v in self.buffer_factor.items():
                    if len(v) >= self.buffer_size or force_save:
                        # get info for the data list
                        sample_data: FactorData = v[0]
                        vt_symbol: str = sample_data.vt_symbol
                        interval: Interval = sample_data.interval
                        interval_, symbol, factor_name, exchange = extract_vt_symbol(vt_symbol, is_factor=True)

                        status = self.database_manager.save_factor_data(name=data.factor_name, data=v)
                        to_remove.append(k)

                for k in to_remove:
                    self.buffer_factor[k] = []
            elif isinstance(data, pl.DataFrame):
                self.write_log(f"识别到polars dataframe")
                self.write_log(f"data {data}")
                time.sleep(0.1)
                self.database_manager.save_factor_data(name=data.columns[-1], data=data)
            elif isinstance(data, dict) and isinstance(list(data.values())[0], pl.DataFrame):
                self.write_log(f"识别到dict")
                df_list = []
                checked_interval = None
                for factor_key, factor_df in data.items():
                    self.write_log(f"factor_key: {factor_key}")
                    self.write_log(f"factor_df: {factor_df}")
                    interval, factor_name = extract_factor_key(factor_key)
                    # check all the data have the same interval
                    if checked_interval is None:
                        checked_interval = interval
                    else:
                        assert interval == checked_interval
                    # stacking the DataFrame (make column_names into one column called ticker)
                    """
                    2025-03-05 15:48:00,489  INFO: factor_df: shape: (1, 3)
                    ┌─────────────────────┬─────────────────┬─────────────────┐
                    │ datetime            ┆ btcusdt.BINANCE ┆ ethusdt.BINANCE │
                    │ ---                 ┆ ---             ┆ ---             │
                    │ datetime[μs]        ┆ f64             ┆ f64             │
                    ╞═════════════════════╪═════════════════╪═════════════════╡
                    │ 2025-03-05 15:47:00 ┆ 88620.0         ┆ 2190.79         │
                    └─────────────────────┴─────────────────┴─────────────────┘
                    ->
                    2025-03-05 15:48:00,489  INFO: df_long: shape: (2, 3)
                    ┌─────────────────────┬─────────────────┬─────────────────────────┐
                    │ datetime            ┆ ticker          ┆ factor_1m_open@noparams │
                    │ ---                 ┆ ---             ┆ ---                     │
                    │ datetime[μs]        ┆ str             ┆ f64                     │
                    ╞═════════════════════╪═════════════════╪═════════════════════════╡
                    │ 2025-03-05 15:47:00 ┆ btcusdt.BINANCE ┆ 88620.0                 │
                    │ 2025-03-05 15:47:00 ┆ ethusdt.BINANCE ┆ 2190.79                 │
                    └─────────────────────┴─────────────────┴─────────────────────────┘
                    """
                    df_pivoted = factor_df.melt(
                        id_vars=["datetime"],
                        value_vars=list(sorted(set(factor_df.columns) - {'datetime'})),
                        variable_name="ticker",
                        value_name=factor_key
                    )
                    df_list.append(df_pivoted)
                df_pivoted = pl.concat(df_list, how='align')
                self.write_log(f"df_pivoted: {df_pivoted}", level=DEBUG)
                status = self.database_manager.save_factor_data(data=df_pivoted, interval=checked_interval)

            else:
                raise TypeError(f"Unsupported data type: {type(data)}")

        elif task_type is None and data is None:
            # 强制保存当前所有的数据
            for k, v in self.buffer_bar.items():
                if len(v) == 0:
                    continue
                self.database_manager.save_bar_data(v)
            for k, v in self.buffer_factor.items():
                if len(v) == 0:
                    continue
                self.database_manager.save_factor_data(name=v[0].factor_name, data=v)
            self.buffer_bar = defaultdict(list)
            self.buffer_factor = defaultdict(list)

    def run(self):
        """"""
        while self.active:
            # try:
            #     task = self.queue.get(timeout=1)
            #     task_type, data = task
            #     self.save_data(task_type, data)
            # except Empty as e:
            #     self.write_log(f"数据记录引擎处理队列为空 {self.queue.qsize()}", level=WARNING)
            # except Exception as e:
            #     self.write_log(f"{str(e)}", level=ERROR)
            if self.queue.qsize() > 0:
                task = self.queue.get(timeout=1)
                task_type, data = task
                self.save_data(task_type, data)
            else:
                time.sleep(1)

    def close(self):
        """"""
        self.save_data(None, None)  # 保存所有buffer中残留的数据
        self.active = False
        if self.thread.isAlive():
            self.thread.join()

    def start(self):
        """"""
        self.write_log("启动数据拉取引擎")
        self.active = True
        self.thread.start()

    def add_bar_recording(self, vt_symbol: str):
        """add a symbol to the bar recording list, which means that the bar data of this symbol will be recorded"""
        if vt_symbol in self.bar_recordings:
            self.write_log(f"已在K线记录列表中：{vt_symbol}", level=NOTSET)
            return

        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            self.write_log(f"找不到合约：{vt_symbol}", level=ERROR)
            return

        self.bar_recordings[vt_symbol] = {
            "symbol": contract.symbol,
            "exchange": contract.exchange.value,
            "gateway_name": contract.gateway_name
        }

        self.subscribe(contract)
        # self.save_setting()
        self.put_event()

        self.write_log(f"添加K线记录成功：{vt_symbol}", level=DEBUG)

    def add_factor_recording(self, vt_symbol: str):
        """add a symbol to the factor recording list, which means that the factor data of this symbol will be recorded"""
        if vt_symbol in self.factor_recordings:
            self.write_log(f"已在因子记录列表中：{vt_symbol}", level=NOTSET)
            return

        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            self.write_log(f"找不到合约：{vt_symbol}", level=ERROR)
            return

        self.factor_recordings[vt_symbol] = {
            "symbol": contract.symbol,
            "exchange": contract.exchange.value,
            "gateway_name": contract.gateway_name
        }

        self.subscribe(contract)
        # self.save_setting()
        self.put_event()

        self.write_log(f"添加因子记录成功：{vt_symbol}", level=DEBUG)

    def add_tick_recording(self, vt_symbol: str):
        """add a symbol to the tick recording list, which means that the tick data of this symbol will be recorded"""
        if vt_symbol in self.tick_recordings:
            self.write_log(f"已在Tick记录列表中：{vt_symbol}", level=NOTSET)
            return

        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            self.write_log(f"找不到合约：{vt_symbol}", level=ERROR)
            return

        self.tick_recordings[vt_symbol] = {
            "symbol": contract.symbol,
            "exchange": contract.exchange.value,
            "gateway_name": contract.gateway_name
        }

        self.subscribe(contract)
        # self.save_setting()
        self.put_event()

        self.write_log(f"添加Tick记录成功：{vt_symbol}", level=DEBUG)

    def remove_bar_recording(self, vt_symbol: str):
        """remove a symbol from the bar recording list"""
        if vt_symbol not in self.bar_recordings:
            self.write_log(f"不在K线记录列表中：{vt_symbol}", level=DEBUG)
            return

        self.bar_recordings.pop(vt_symbol)
        # self.save_setting()
        self.put_event()

        self.write_log(f"移除K线记录成功：{vt_symbol}")

    def remove_tick_recording(self, vt_symbol: str):
        """remove a symbol from the tick recording list"""
        if vt_symbol not in self.tick_recordings:
            self.write_log(f"不在Tick记录列表中：{vt_symbol}", level=DEBUG)
            return

        self.tick_recordings.pop(vt_symbol)
        # self.save_setting()
        self.put_event()

        self.write_log(f"移除Tick记录成功：{vt_symbol}")

    def process_bar_event(self, event: Event):
        """"""
        bar = event.data
        # self.add_bar_recording(vt_symbol=bar.vt_symbol)
        # if bar.vt_symbol in self.bar_recordings:
        self.record_bar(bar)

    def process_factor_event(self, event: Event):
        """"""
        factor_dict: dict = event.data
        # for factor_key, factor_df in factor_dict.items():
        #     # self.add_factor_recording(vt_symbol=factor_name)
        #     self.record_factor({factor_key: factor_df})
        self.write_log(f"factor_dict: {factor_dict}", level=DEBUG)
        self.record_factor(factor_dict)

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

    def record_tick(self, tick: TickData):
        """"""
        self.write_log(f"record_tick", level=DEBUG)
        task = ("tick", deepcopy(tick))
        self.queue.put(task)

    def record_bar(self, bar: BarData):
        """"""
        self.write_log(f"record_bar", level=DEBUG)
        task = ("bar", deepcopy(bar))
        self.queue.put(task)

    def record_factor(self, factor: Union[FactorData, pl.DataFrame, dict]):
        """"""
        self.write_log(f"record_factor", level=DEBUG)
        task = ("factor", deepcopy(factor))
        self.queue.put(task)

    def write_log(self, msg: str, level: int = INFO) -> None:
        """"""
        log: LogData = LogData(msg=msg, gateway_name=APP_NAME, level=level)
        event: Event = Event(EVENT_LOG, log)
        self.event_engine.put(event)

    def put_event(self):
        """ this function is apply on widget.py """
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
            exchange=contract.exchange,
            interval=contract.interval
        )
        self.main_engine.subscribe(req, contract.gateway_name)
