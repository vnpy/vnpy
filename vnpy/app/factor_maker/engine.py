import importlib
import traceback
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime, timedelta
from logging import Logger, CRITICAL, FATAL, ERROR, WARNING, WARN, INFO, DEBUG, NOTSET
from typing import Type, Optional, Callable, Union, List, Tuple
import dask
import polars as pl
from copy import deepcopy, copy

from vnpy.event import EventEngine, Event
from vnpy.event.events import EVENT_BAR_FACTOR, EVENT_FACTOR, EVENT_FACTORMAKER
from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.database import BaseDatabase, get_database, DB_TZ
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import EVENT_TICK, EVENT_BAR
from vnpy.trader.object import LogData, ContractData, TickData, BarData, HistoryRequest, FactorData
from vnpy.trader.utility import load_json, save_json, extract_vt_symbol
from vnpy.app.factor_maker.base import APP_NAME, RollingDataFrame
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.utility import *

factor_module_name = 'vnpy.app.factor_maker.factors'


# factor maker engine
class FactorEngine(BaseEngine):
    setting_filename: str = "factor_maker_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.module_factors = importlib.import_module(factor_module_name)

        # factors written in the setting file at the 1st level, dependencies are not included
        self.top_level_factors: dict[str, FactorTemplate] = {}
        # put top level factors and their dependencies at the same level
        self.flattened_factors: dict[str, FactorTemplate] = {}

        self.memory_bar: Dict[str, pl.DataFrame] = {}
        self.memory_factor: Dict[str, pl.DataFrame] = {}
        self.max_memory_length = 10
        self.tasks = {}  # dask tasks

        self.database = get_database()
        self.dt = None
        self.bars = {}  # bar data containing all vt_symbols

        self.vt_symbols = main_engine.vt_symbols
        self.subscribed_symbols = main_engine.subscribed_symbols

    def init_engine(self) -> None:
        """"""
        self.register_event()
        self.init_all_factors() # stacked factors
        self.flattened_factors = self.complete_factor_tree(self.top_level_factors) # flatten the factor tree
        self.write_log(f"self.flattened_factors {list(self.flattened_factors.keys())}", level=DEBUG)
        self.init_memory()
        self.tasks = self.build_computational_graph()  # Build the graph after initializing factors
        self.write_log("因子计算引擎初始化成功")

    # def load_factor_setting(self) -> None:
    #     """加载因子计算策略配置"""
    #     factor_setting: dict = load_json(self.setting_filename)
    #     for factor_name, factor_config in factor_setting.items():
    #         self.add_factor(
    #             factor_config["class_name"],
    #             factor_name,
    #             factor_config
    #         )

    # def add_factor(self, class_name: str, factor_name: str, setting: dict) -> None:
    #     if factor_name in self.factors:
    #         msg = f"Creation failed, factor name {factor_name} already exists."
    #         self.write_log(msg)
    #         return
    #     factor_class = get_factor_class(class_name)
    #     if not factor_class:
    #         msg = f"Creation failed, factor class {class_name} not found."
    #         self.write_log(msg)
    #         return
    #     if factor_class.__name__ not in self.classes:
    #         self.classes[factor_class.__name__] = factor_class
    #     factor: FactorTemplate = factor_class(engine=self, setting=setting)
    #     self.factors[factor_name] = factor

    def register_event(self) -> None:
        """what to do when event is triggered"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_BAR, self.process_bar_event)
        self.event_engine.register(EVENT_BAR_FACTOR, self.process_bar_factor_event)
        self.event_engine.register(EVENT_FACTOR, self.process_factor_event)

        # self.main_engine.register_log_event(EVENT_FACTORMAKER_LOG)

    def get_factor_parameters(self, factor_key) -> dict:
        """获取策略参数"""
        factor: FactorTemplate = self.top_level_factors[factor_key]
        return factor.get_params()

    def init_memory(self) -> None:
        data = {'datetime': []}
        schema = {'datetime': datetime}
        for symbol in self.vt_symbols:
            data[symbol] = []
            schema[symbol] = pl.Float32
        for b in ["open", "high", "low", "close", "volume"]:
            self.memory_bar[b] = pl.DataFrame(data=data, schema=schema)
        for f in self.flattened_factors.keys():
            self.memory_factor[f] = pl.DataFrame(data=data, schema=schema)

    def init_all_factors(self) -> None:
        """初始化所有因子"""
        inited_factors = init_all_factors(load_factor_setting(self.setting_filename), factor_mode=FactorMode.Live)
        self.top_level_factors = {f.factor_key: f for f in inited_factors}

        # get max_memory_length from all potential attributes
        self.max_memory_length = max([self.max_memory_length] + [
            max(getattr(factor, "lookback_period", 0),
                getattr(factor, "window", 0),
                getattr(factor, "period", 0),
                getattr(factor, "fast_period", 0),
                getattr(factor, "slow_period", 0),
                getattr(factor, "signal_period", 0),
                getattr(factor, "len", 0),
                getattr(factor, "length", 0),
                ) for factor in self.top_level_factors.values()])
        self.write_log(f"max_memory_length: {self.max_memory_length}",level=DEBUG)
        self.write_log(f"self.top_level_factors {list(self.top_level_factors.keys())}", level=INFO)

    def start_factor(self, factor_key: str) -> None:
        """Start factor"""
        factor: FactorTemplate = self.top_level_factors[factor_key]
        if not factor.inited:
            self.write_log(f"Factor {factor_key} failed to start, please initialize it first")
            return
        if factor.trading:
            self.write_log(f"Factor {factor_key} is already running, please do not repeat the operation")
            return
        self.call_factor_func(factor, factor.on_start)
        self.put_factor_event(factor)

    def stop_all_factors(self) -> None:
        """启动所有策略"""
        for factor_name in self.top_level_factors.keys():
            self.stop_factor(factor_name)

    def stop_factor(self, factor_name: str) -> None:
        """停止因子"""
        factor: FactorTemplate = self.top_level_factors[factor_name]
        if not factor.trading:
            msg: str = f"因子{factor_name}未启动, 无须停止"
            self.write_log(msg, factor)
            return
        self.call_factor_func(factor, factor.on_stop)
        self.write_log(f"因子{factor_name}同步数据状态")
        self.put_factor_event(factor)

    def close(self) -> None:
        """关闭"""
        self.stop_all_factors()

    # Historical Data Management
    def load_bars(self, days: int, interval: Interval) -> None:
        """Load historical bar data for all contracts."""
        vt_symbols = self.main_engine.vt_symbols
        dts = set()
        history_data = {}

        for vt_symbol in vt_symbols:
            data = self.load_bar(vt_symbol, days, interval)
            for bar in data:
                dts.add(bar.datetime)
                history_data[(bar.datetime, vt_symbol)] = bar

        # Organize and process bars
        dts = sorted(dts)
        for dt in dts:
            bars = {}
            for vt_symbol in vt_symbols:
                bar = history_data.get((dt, vt_symbol))
                if bar:
                    bars[vt_symbol] = bar
                else:
                    # Handle missing data
                    bars[vt_symbol] = self.create_placeholder_bar(dt, vt_symbol, bars)
            self.on_bars(dt, bars)

    def load_bar(self, vt_symbol: str, days: int, interval: Interval) -> list[BarData]:
        """Load historical bar data for a specific contract."""
        symbol, exchange = extract_vt_symbol(vt_symbol)
        end = datetime.now(DB_TZ)
        start = end - timedelta(days)
        contract = self.main_engine.get_contract(vt_symbol)

        data = self.database.load_bar_data(symbol, exchange, interval, start, end)
        if not data and contract and contract.history_data:
            req = HistoryRequest(
                symbol=symbol,
                exchange=exchange,
                interval=interval,
                start=start,
                end=end
            )
            data = self.main_engine.query_history(req, contract.gateway_name)
        if not data:
            self.write_log(f"Failed to load data for {vt_symbol}.")
        return data or []

    def create_placeholder_bar(self, dt: datetime, vt_symbol: str, bars: dict) -> BarData:
        """Create a placeholder bar when data is missing."""
        symbol, exchange = extract_vt_symbol(vt_symbol)
        if vt_symbol in bars:
            previous_bar = bars[vt_symbol]
            return BarData(
                symbol=previous_bar.symbol,
                exchange=previous_bar.exchange,
                datetime=dt,
                open_price=previous_bar.close_price,
                high_price=previous_bar.close_price,
                low_price=previous_bar.close_price,
                close_price=previous_bar.close_price,
                gateway_name=previous_bar.gateway_name,
            )
        return BarData(
            symbol=symbol,
            exchange=exchange,
            datetime=dt,
            open_price=0,
            high_price=0,
            low_price=0,
            close_price=0,
            gateway_name=""
        )

    def _truncate_memory_bar(self) -> None:
        """Truncate the memory to the maximum length."""
        for key, df in self.memory_bar.items():
            if len(df) > self.max_memory_length:
                self.memory_bar[key] = df.tail(self.max_memory_length)

    def _truncate_memory_factor(self) -> None:
        """Truncate the memory to the maximum length."""
        for key, df in self.memory_factor.items():
            if len(df) > self.max_memory_length:
                self.memory_factor[key] = df.tail(self.max_memory_length)

    def complete_factor_tree(self, factors: Dict[str, Any]) -> Dict[str, Any]:
        """
        Recursively complete the dependency tree for all factors.

        Parameters:
            factors (Dict[str, Any]): Dictionary of factors keyed by factor_key.

        Returns:
            Dict[str, Any]: Complete dependency tree including all dependent factors.
        """

        def traverse_dependencies(factor: Any, resolved_factors: Dict[str, Any]) -> None:
            """
            Make the tree to a flat one. Recursively traverse and add dependencies of the given factor.

            Parameters:
                factor (Any): Current factor to traverse.
                resolved_factors (Dict[str, Any]): Dictionary to store all resolved dependencies.
            """
            if factor.factor_key in resolved_factors:
                return  # Skip if already resolved

            # Add the current factor
            resolved_factors[factor.factor_key] = factor

            # Traverse dependencies recursively
            for dependency in factor.dependencies_factor:
                traverse_dependencies(dependency, resolved_factors)

        resolved_factors = {}
        for factor_key, factor in factors.items():
            traverse_dependencies(factor, resolved_factors)

        return resolved_factors

    def build_computational_graph(self) -> Dict[str, dask.delayed]:
        """
        Build a Dask computational graph for factors with dependencies.

        Parameters:
            factors (Dict[str, Any]): Dictionary of factors keyed by their unique `factor_key`.
            data (Dict[str, pl.DataFrame]): Historical OHLCV or other input data.

        Returns:
            Dict[str, dask.delayed]: Dask tasks for each factor keyed by `factor_key`.
        """


        tasks = {}
        for factor_key in self.flattened_factors.keys():
            self.create_task(factor_key, self.flattened_factors, tasks)

        return tasks

    def create_task(self,
                    factor_key: str,
                    factors: Dict[str, Any],
                    tasks: Dict[str, dask.delayed]
                    ) -> dask.delayed:
        """
        Recursively create a Dask task for a given factor and its dependencies.

        Parameters:
            factor_key (str): The key of the factor to create a task for.
            factors (Dict[str, Any]): Dictionary of all factors keyed by factor_key.
            tasks (Dict[str, dask.delayed]): Dictionary to store the created tasks.

        Returns:
            dask.delayed: The Dask task for the factor calculation.
        """
        if factor_key in tasks:
            return tasks[factor_key]  # Return cached task if already created

        factor = factors[factor_key]

        # Handle dependencies
        if not factor.dependencies_factor:  # No dependencies
            # memory_dict = {key: dask.delayed(lambda df=df: df.clone())() for key, df in data.items()}
            memory_dict = {}
            for key, df in self.memory_bar.items():
                memory_dict[key] = dask.delayed(copy)(df)
            # for key, df in self.memory_factor.items():
            #     if key == factor_key:
            #         continue  # avoid saving historical data of this factor in memory, leave it to the historical_data
            #     memory_dict[key] = dask.delayed(copy)(df)
            # historical_data=dask.delayed(copy)(self.memory_factor[factor_key])
            tasks[factor_key] = dask.delayed(factor.calculate)(input_data=memory_dict,
                                                               historical_data=None)
        else:  # Resolve dependencies recursively
            dep_tasks = {
                dep_factor.factor_key: self.create_task(dep_factor.factor_key, factors, tasks)
                for dep_factor in factor.dependencies_factor
            }
            historical_data = dask.delayed(copy)(self.memory_factor[factor_key])
            tasks[factor_key] = dask.delayed(factor.calculate)(input_data=dep_tasks, historical_data=historical_data)

        return tasks[factor_key]

    def on_bars(self, dt: datetime, bars: dict) -> None:
        """Process a batch of bars."""
        print(f"on_bars: {dt}, {bars.keys()} {bars}", flush=True)

        # dict of dicts, {'open': {'datetime': dt, 'symbol1': symbol1, 'symbol2': symbol2, }, ...}
        data = {
            "open": {'datetime': dt},
            "high": {'datetime': dt},
            "low": {'datetime': dt},
            "close": {'datetime': dt},
            "volume": {'datetime': dt},
        }
        schema = {
            "open": {'datetime': datetime},
            "high": {'datetime': datetime},
            "low": {'datetime': datetime},
            "close": {'datetime': datetime},
            "volume": {'datetime': datetime},
        }

        for symbol, bar in bars.items():
            data["open"][symbol] = bar.open_price
            data["high"][symbol] = bar.high_price
            data["low"][symbol] = bar.low_price
            data["close"][symbol] = bar.close_price
            data["volume"][symbol] = bar.volume
            schema["open"][symbol] = pl.Float32
            schema["high"][symbol] = pl.Float32
            schema["low"][symbol] = pl.Float32
            schema["close"][symbol] = pl.Float32
            schema["volume"][symbol] = pl.Float32

        tmp = {}
        for key, dic, in data.items():
            tmp[key] = pl.DataFrame(data=dic, schema=schema[key])

        self.memory_bar["open"] = pl.concat([self.memory_bar["open"], tmp["open"]], how='vertical')
        self.memory_bar["high"] = pl.concat([self.memory_bar["high"], tmp["high"]], how='vertical')
        self.memory_bar["low"] = pl.concat([self.memory_bar["low"], tmp["low"]], how='vertical')
        self.memory_bar["close"] = pl.concat([self.memory_bar["close"], tmp["close"]], how='vertical')
        self.memory_bar["volume"] = pl.concat([self.memory_bar["volume"], tmp["volume"]], how='vertical')

        self._truncate_memory_bar()

        self.on_calculation(dt=dt)

    def on_calculation(self, dt: datetime) -> None:
        """
        Execute the pre-built computation graph with updated memory.

        The memory is dynamically updated before each calculation.

        todo: 1. historical data of the factor is being calculated 2. factor calculation 3. factor update
        """
        if not hasattr(self, "tasks"):
            raise RuntimeError("Computation graph has not been built. Please initialize the engine first.")

        # Execute the computation graph
        results = dask.compute(*self.tasks.values())

        # Update factor values with results
        for factor_name, result in zip(self.top_level_factors.keys(), results):
            self.memory_factor[factor_name] = result

        self._truncate_memory_factor()

        self.write_log("Factor calculations completed successfully.", level=DEBUG)
        self.write_log(f"self.memory_factor {self.memory_bar}", level=DEBUG)
        self.write_log(f"self.memory_factor {self.memory_factor}", level=DEBUG)

    # def build_computation_graph(self) -> None:
    #     """
    #     Build the computation graph for all factors and store it in self.tasks.
    #
    #     This method is called once after all factors are added to the engine.
    #     """
    #
    #     def complete_factor_tree():
    #         new_factors
    #         for f_key, f in self.factors.items():
    #             for dep_f in f.dependencies_factor:
    #                 if dep_f.factor_key in self.factors:
    #                     continue
    #                 self.factors[dep_f.factor_key] = dep_f
    #
    #     complete_factor_tree()
    #
    #     # Function to create a task for a factor
    #     def create_task(factor_key: str) -> dask.delayed:
    #         """
    #         Create a Dask task for a given factor dynamically.
    #
    #         Parameters:
    #             factor_key (str): The name of the factor to create the task for.
    #
    #         Returns:
    #             dask.delayed: The Dask task for the factor calculation.
    #         """
    #         # Check if the task has already been created
    #         if factor_key in self.tasks:
    #             return self.tasks[factor_key]
    #
    #         # Retrieve the factor instance
    #         factor = self.factors[factor_key]
    #
    #         # Resolve dependencies recursively
    #         dep_tasks = {}
    #         if not factor.dependencies_factor:
    #             # Create memory dict with delayed tasks for each key
    #             memory_dict = {key: dask.delayed(df.get_dataframe)() for key, df in self.memory.items()}
    #             # Pass the memory_dict as input to factor.calculate
    #             self.tasks[factor_key] = dask.delayed(factor.calculate)(input_data=memory_dict)
    #         else:
    #             # Resolve dependencies recursively
    #             for f in factor.dependencies_factor:
    #                 dep = f.factor_key
    #                 dep_tasks[dep] = create_task(dep)
    #
    #             # Create the task for the current factor using memory and resolved dependencies
    #             self.tasks[factor_key] = dask.delayed(factor.calculate)(input_data=dep_tasks)
    #
    #         return self.tasks[factor_key]
    #
    #     # Build tasks for all factors
    #     for factor_name in self.factors.keys():
    #         create_task(factor_name)
    #
    #     self.write_log("Computation graph built successfully.")

    # Event Processing
    def process_tick_event(self, event: Event) -> None:
        """Market data tick push"""
        tick: TickData = event.data
        if not self.top_level_factors:
            return
        for factor_name, factor in self.top_level_factors:
            if factor.inited:
                self.call_factor_func(factor, factor.on_tick, tick)

    def process_bar_event(self, event: Event) -> None:
        """Process incoming bar data."""
        bar: BarData = event.data
        if self.dt is None:
            self.dt = bar.datetime
            self.bars[bar.vt_symbol] = bar
        else:
            if bar.datetime == self.dt:
                self.bars[bar.vt_symbol] = bar
            elif bar.datetime > self.dt:
                self.on_bars(self.dt, self.bars)  # push data to factor calculation
                self.dt = bar.datetime
                self.bars = {bar.vt_symbol: bar}  # totally create a new self.bars and add the new bar

    def process_bar_factor_event(self, event: Event) -> None:
        """K-line (bar) data push"""
        bar: BarData = event.data
        for k, factor in self.top_level_factors.items():
            if factor.factor_name in ['open', 'high', 'low', 'close', 'volume']:
                self.call_factor_func(factor, factor.on_bar, bar)

    def process_factor_event(self, event: Event) -> None:
        """Process factor event"""
        data: FactorData = event.data

    # Utility Functions
    def call_factor_func(self, factor: FactorTemplate, func: Callable, params: object = None) -> None:
        """Safely call factor function"""
        try:
            if params:
                func(params)
            else:
                func()
        except Exception:
            factor.trading = False
            factor.inited = False
            msg: str = f"An exception occurred, factor has been stopped\n{traceback.format_exc()}"
            self.write_log(msg, factor)

    def write_log(self, msg: str, factor: FactorTemplate = None, level=INFO) -> None:
        """输出日志"""
        if factor:
            msg: str = f"{factor.factor_key}: {msg}"
        self.main_engine.write_log(msg, source=APP_NAME, level=level)

    def put_factor_event(self, factor: FactorTemplate) -> None:
        """推送事件更新策略界面"""
        data: dict = factor.get_data()
        event: Event = Event(EVENT_FACTORMAKER, data)
        self.event_engine.put(event)

    def send_email(self, msg: str, factor: FactorTemplate = None) -> None:
        """发送邮件"""
        subject: str = f"{factor.factor_key}" if factor else "Factor Maker Engine"
        self.main_engine.send_email(subject, msg)
