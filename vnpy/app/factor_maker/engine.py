import importlib
import gc
import time
import traceback
from datetime import datetime, timedelta
from logging import INFO, DEBUG, WARNING, ERROR
from typing import Callable, Any, Dict, Optional, List
from functools import lru_cache
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass
from threading import Lock

import numpy as np
import pandas as pd
import polars as pl
import psutil
import dask
from dask.delayed import Delayed
import dask.diagnostics

from vnpy.event import EventEngine, Event
from vnpy.trader.event import EVENT_FACTOR, EVENT_TICK, EVENT_BAR
from vnpy.trader.constant import Interval
from vnpy.trader.database import get_database, DB_TZ
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.object import TickData, BarData, HistoryRequest
from vnpy.trader.utility import extract_vt_symbol
from vnpy.trader.setting import SETTINGS
from vnpy.app.factor_maker.base import APP_NAME
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.utils.factor_utils import *
from vnpy.app.factor_maker.utils.memory_utils import truncate_memory, create_placeholder_bar

FACTOR_MODULE_NAME = 'vnpy.app.factor_maker.factors'
SYSTEM_MODE = SETTINGS.get('system.mode', 'LIVE')


@dataclass
class CalculationMetrics:
    """Performance metrics for factor calculations"""
    calculation_time: float
    memory_usage: float
    cache_hits: int
    error_count: int


class FactorEngine(BaseEngine):
    """
    Engine for managing factor calculations with support for:
    - Parallel processing using Dask
    - Memory management and caching
    - Performance monitoring
    - Error handling and circuit breaking
    """
    setting_filename: str = "factor_maker_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """
        Initialize the FactorEngine.

        Parameters:
            main_engine (MainEngine): The main engine instance.
            event_engine (EventEngine): The event engine instance.
        """
        super().__init__(main_engine, event_engine, APP_NAME)

        # Core components
        self.module_factors = importlib.import_module(FACTOR_MODULE_NAME)
        self.database = get_database()  # mark it when running test
        self.vt_symbols = main_engine.vt_symbols

        # Factor management
        self.stacked_factors: dict[str, FactorTemplate] = {}
        self.flattened_factors: dict[str, FactorTemplate] = {}

        # Memory management
        self.memory_bar: Dict[str, pl.DataFrame] = {}
        self.memory_factor: Dict[str, pl.DataFrame] = {}
        self.max_memory_length = 10

        # State management
        self.dt = None
        self.bars = {}
        self.factors = {}
        self.tasks = {}
        self.receiving_status = {k: False for k in self.vt_symbols}  # when bar is received, set it to True

        # Performance monitoring
        self.metrics: Dict[str, CalculationMetrics] = {}
        self.calculation_lock = Lock()
        self.thread_pool = ThreadPoolExecutor(max_workers=4)
        self.cache_size = 1000
        self.error_threshold = 3
        self.consecutive_errors = 0

    def init_engine(self, fake: bool = False) -> None:
        """"""
        self.register_event()
        self.write_log("register event", level=DEBUG)
        self.init_all_factors()  # stacked factors
        self.flattened_factors = self.complete_factor_tree(self.stacked_factors)  # flatten the factor tree
        self.write_log(f"self.flattened_factors {list(self.flattened_factors.keys())}", level=INFO)

        self.init_memory(fake=fake)  # initialize memory
        self.tasks = self.build_computational_graph()  # Build the graph after initializing factors
        self.write_log("Successfully initialized all factors", level=INFO)

    def register_event(self) -> None:
        """what to do when event is triggered"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_BAR, self.process_bar_event)

    def get_factor_parameters(self, factor_key) -> dict:
        """get factor parameters"""
        if factor_key not in self.stacked_factors:
            msg: str = f"factor: {factor_key} not found"
            self.write_log(msg, level=ERROR)
            return {}
        if factor_key in self.flattened_factors:
            factor: FactorTemplate = self.flattened_factors[factor_key]
            msg: str = f"factor: {factor_key} is a flattened factor"
            self.write_log(msg, level=INFO)
            return factor.get_params()
        factor: FactorTemplate = self.stacked_factors[factor_key]
        return factor.get_params()

    def init_memory(self, fake: bool = False) -> None:
        """

        Parameters
        ----------
        fake : bool
            fake memory for testing

        Returns
        -------

        """
        data = {'datetime': []}
        schema = {'datetime': datetime}
        for symbol in self.vt_symbols:
            data[symbol] = []
            schema[symbol] = pl.Float64
        for b in ["open", "high", "low", "close", "volume"]:
            self.memory_bar[b] = pl.DataFrame(data=data, schema=schema)
        for f in self.flattened_factors.keys():
            self.memory_factor[f] = pl.DataFrame(data=data, schema=schema)

        if fake:  # concat fake data to memory
            for b in ["open", "high", "low", "close", "volume"]:
                # fake data
                data = {'datetime': pd.date_range("2024-01-01", periods=self.max_memory_length, freq="1min")}
                schema = {'datetime': datetime}
                for symbol in self.main_engine.vt_symbols:
                    data[symbol] = np.array(list(range(self.max_memory_length))) * np.random.rand()
                    schema[symbol] = pl.Float64
                self.memory_bar[b] = pl.concat(
                    [self.memory_bar[b], pl.DataFrame(data=data, schema=schema)], how='vertical')
            for f in self.flattened_factors.keys():
                # fake data
                data = {'datetime': pd.date_range("2024-01-01", periods=self.max_memory_length, freq="1min")}
                schema = {'datetime': datetime}
                for symbol in self.main_engine.vt_symbols:
                    data[symbol] = np.array(list(range(self.max_memory_length))) * np.random.rand()
                    schema[symbol] = pl.Float64
                self.memory_factor[f] = pl.concat(
                    [self.memory_factor[f], pl.DataFrame(data=data, schema=schema)], how='vertical')

    def init_all_factors(self) -> None:
        """Initialize all factors and determine maximum memory length needed"""
        inited_factors = init_factors(load_factor_setting(self.setting_filename))
        self.stacked_factors = {f.factor_key: f for f in inited_factors}

        # Calculate max memory length based on factor parameters
        lookback_attrs = ["lookback_period", "window", "period", "fast_period",
                          "slow_period", "signal_period", "len", "length"]

        self.max_memory_length = max(
            [self.max_memory_length] + [
                max(getattr(factor, attr, 20) for attr in lookback_attrs)
                for factor in self.stacked_factors.values()
            ]
        )
        self.write_log(f"Maximum memory length: {self.max_memory_length}", level=DEBUG)

    def stop_all_factors(self) -> None:
        """stop all factors"""
        if not self.stacked_factors:
            msg: str = "no factors to stop"
            self.write_log(msg, level=INFO)
            return
        for factor_name in self.stacked_factors.keys():
            self.stop_factor(factor_name)

    def stop_factor(self, factor_name: str) -> None:
        """stop a factor"""
        if factor_name not in self.stacked_factors:
            msg: str = f"factor: {factor_name} not found"
            self.write_log(msg, level=ERROR)
            return
        factor: FactorTemplate = self.stacked_factors[factor_name]
        if not factor.trading:
            msg: str = f"factor: {factor_name} is not trading, no need to stop"
            self.write_log(msg, factor, level=INFO)
            return
        self.call_factor_func(factor, factor.on_stop)
        self.write_log(f"factor: {factor_name} stopped", factor, level=INFO)

    def close(self) -> None:
        """close the engine"""
        self.write_log("Closing Factor Engine", level=INFO)
        self.stop_all_factors()
        save_factor_setting(self.stacked_factors, self.setting_filename)

    # Historical Data Management
    def load_bars(self, days: int, interval: Interval) -> None:
        """
        Load historical bar data for all contracts.

        Parameters:
            days (int): Number of days to load.
            interval (Interval): The interval of the bar data.
        """
        try:
            vt_symbols = self.main_engine.vt_symbols
            dts = set()
            history_data = {}

            for vt_symbol in vt_symbols:
                data = self.load_bar(vt_symbol, days, interval)
                for bar in data:
                    dts.add(bar.datetime)
                    history_data[(bar.datetime, vt_symbol)] = bar

            dts = sorted(dts)
            for dt in dts:
                bars = {}
                for vt_symbol in vt_symbols:
                    bar = history_data.get((dt, vt_symbol))
                    if bar:
                        bars[vt_symbol] = bar
                    else:
                        bars[vt_symbol] = self.create_placeholder_bar(dt, vt_symbol, bars)
                self.on_bars(dt, bars)

        except Exception as e:
            self.write_log(f"Error loading bars: {e}", level=ERROR)

    def load_bar(self, vt_symbol: str, days: int, interval: Interval) -> list[BarData]:
        """
        Load historical bar data for a specific contract.

        Parameters:
            vt_symbol (str): The vt_symbol of the contract.
            days (int): Number of days to load.
            interval (Interval): The interval of the bar data.

        Returns:
            list[BarData]: List of bar data.
        """
        try:
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
                self.write_log(f"Failed to load data for {vt_symbol}.", level=WARNING)
            return data or []

        except Exception as e:
            self.write_log(f"Error loading bar for {vt_symbol}: {e}", level=ERROR)
            return []

    def create_placeholder_bar(self, dt: datetime, vt_symbol: str, bars: dict) -> BarData:
        """
        Create a placeholder bar when data is missing.
        """
        return create_placeholder_bar(dt, vt_symbol, bars)

    def _truncate_memory_bar(self) -> None:
        """
        Truncate the memory_bar to the maximum length.
        """
        assert self.memory_bar, "memory_bar is not initialized."
        truncate_memory(self.memory_bar, self.max_memory_length)

    def _truncate_memory_factor(self) -> None:
        """
        Truncate the memory_factor to the maximum length.
        """
        assert self.memory_factor, "memory_factor is not initialized."
        truncate_memory(self.memory_factor, self.max_memory_length)

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

    def build_computational_graph(self) -> Dict[str, Delayed]:
        """
        Build a Dask computational graph with improved performance and error handling.
        """
        tasks = {}

        # Create a graph of dependencies first
        dependency_graph = {}
        for factor_key, factor in self.flattened_factors.items():
            dependency_graph[factor_key] = [d.factor_key for d in factor.dependencies_factor]

        # Topologically sort factors to ensure optimal execution order
        sorted_factors = self._topological_sort(dependency_graph)

        # Build tasks in dependency order
        for factor_key in sorted_factors:
            self.create_task(factor_key, self.flattened_factors, tasks)

        return tasks

    def _topological_sort(self, graph: Dict[str, list]) -> list:
        """
        Perform topological sort on factor dependencies.
        """
        visited = set()
        temp = set()
        order = []

        def visit(node: str):
            if node in temp:
                raise ValueError(f"Circular dependency detected involving {node}")
            if node in visited:
                return
            temp.add(node)
            for dep in graph.get(node, []):
                visit(dep)
            temp.remove(node)
            visited.add(node)
            order.append(node)

        for node in graph:
            if node not in visited:
                visit(node)

        return order[::-1]

    def __copy_memory_bar__(self):
        """used in create_task"""
        return self.memory_bar

    def __copy_memory_factor__(self, factor_key):
        """used in create_task"""
        return self.memory_factor[factor_key]

    def create_task(self,
                    factor_key: str,
                    factors: Dict[str, Any],
                    tasks: Dict[str, dask.delayed]
                    ) -> dask.delayed:
        """
        Recursively create a Dask task for a given factor and its dependencies.

        Notes:
            this method can not contain any class attributes, otherwise the data will be a fixed one.
            To fix this, you need to write a function (which is fixed) to load data dynamically

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
            memory_dict = dask.delayed(self.__copy_memory_bar__)()  # new style
            tasks[factor_key] = dask.delayed(factor.calculate)(input_data=memory_dict, memory=None)
        else:  # Resolve dependencies recursively
            dep_tasks = {
                dep_factor.factor_key: self.create_task(dep_factor.factor_key, factors, tasks)
                for dep_factor in factor.dependencies_factor
            }
            # historical_data = dask.delayed(copy)(self.memory_factor[factor_key])
            historical_data = dask.delayed(self.__copy_memory_factor__)(factor_key)
            tasks[factor_key] = dask.delayed(factor.calculate)(input_data=dep_tasks, memory=historical_data)

        return tasks[factor_key]

    def on_bars(self, dt: datetime, bars: dict) -> None:
        """update memory_bar. throw factor calculation event"""

        if len(bars) == 0:
            self.write_log(f"bars is empty, dt: {dt}", level=DEBUG)
            raise ValueError("bars cannot be empty")

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

        for vt_symbol, bar in bars.items():
            data["open"][vt_symbol] = bar.open_price
            data["high"][vt_symbol] = bar.high_price
            data["low"][vt_symbol] = bar.low_price
            data["close"][vt_symbol] = bar.close_price
            data["volume"][vt_symbol] = bar.volume
            schema["open"][vt_symbol] = pl.Float64
            schema["high"][vt_symbol] = pl.Float64
            schema["low"][vt_symbol] = pl.Float64
            schema["close"][vt_symbol] = pl.Float64
            schema["volume"][vt_symbol] = pl.Float64

        tmp = {}
        for key, dic, in data.items():
            tmp[key] = pl.DataFrame(data=dic, schema=schema[key])

        self.memory_bar["open"] = pl.concat([self.memory_bar["open"], tmp["open"]], how='vertical_relaxed')
        self.memory_bar["high"] = pl.concat([self.memory_bar["high"], tmp["high"]], how='vertical_relaxed')
        self.memory_bar["low"] = pl.concat([self.memory_bar["low"], tmp["low"]], how='vertical_relaxed')
        self.memory_bar["close"] = pl.concat([self.memory_bar["close"], tmp["close"]], how='vertical_relaxed')
        self.memory_bar["volume"] = pl.concat([self.memory_bar["volume"], tmp["volume"]], how='vertical_relaxed')

        # calculate. results are saved in self.memory_factor
        self.execute_calculation(dt=dt)  # calculate factor

        # broadcast result
        newest_memory_factor = {k: v.tail(1) for k, v in self.memory_factor.items()}
        self.event_engine.put(Event(EVENT_FACTOR, newest_memory_factor))  # factors are calculated

        # maintain memory length
        self._truncate_memory_bar()
        self._truncate_memory_factor()

    @lru_cache(maxsize=1000)
    def _cached_calculation(self, factor_key: str, input_data_hash: str) -> pl.DataFrame:
        """Cache calculation results for repeated queries"""
        factor = self.flattened_factors[factor_key]
        return factor.calculate(self.memory_bar, None)

    def _monitor_resources(self) -> Dict[str, float]:
        """Monitor system resources during calculation"""
        process = psutil.Process()
        return {
            "memory_percent": process.memory_percent(),
            "cpu_percent": process.cpu_percent(),
            "disk_io": psutil.disk_io_counters().read_bytes + psutil.disk_io_counters().write_bytes
        }

    def execute_calculation(self, dt: datetime) -> None:
        """Enhanced calculation execution with monitoring and error handling"""
        try:
            if not hasattr(self, "tasks"):
                raise RuntimeError("Computation graph not built")

            with self.calculation_lock:  # Prevent concurrent calculations
                start_time = time.time()
                initial_resources = self._monitor_resources()

                # Configure Dask with adaptive optimization
                chunk_size = max(1000, len(self.memory_bar["close"]) // psutil.cpu_count())
                dask.config.set({
                    'distributed.worker.memory.target': 0.6,
                    'distributed.worker.memory.spill': 0.7,
                    'distributed.worker.memory.pause': 0.8,
                    'distributed.worker.memory.terminate': 0.95,
                    'distributed.worker.memory.max': '4GB',
                    'distributed.worker.threads': psutil.cpu_count(),
                    'distributed.scheduler.work-stealing': True,
                    'array.chunk-size': chunk_size
                })

                # Progress monitoring
                with dask.diagnostics.ProgressBar(), dask.diagnostics.ResourceProfiler() as rprof:
                    results = dask.compute(*self.tasks.values(), optimize_graph=True)

                # Update metrics
                end_time = time.time()
                final_resources = self._monitor_resources()

                for factor_name, result in zip(self.tasks.keys(), results):
                    if result is not None:
                        self.memory_factor[factor_name] = result
                        self.metrics[factor_name] = CalculationMetrics(
                            calculation_time=end_time - start_time,
                            memory_usage=final_resources["memory_percent"] - initial_resources["memory_percent"],
                            cache_hits=self._cached_calculation.cache_info().hits,
                            error_count=0
                        )

                self.consecutive_errors = 0
                self.write_log(f"Calculations completed in {end_time - start_time:.2f}s", level=INFO)

                # Log resource usage
                self.write_log(
                    f"Resource usage - Memory: {final_resources['memory_percent']:.1f}%, "
                    f"CPU: {final_resources['cpu_percent']:.1f}%",
                    level=DEBUG
                )

        except Exception as e:
            self.consecutive_errors += 1
            self.write_log(f"Calculation error: {str(e)}\n{traceback.format_exc()}", level=ERROR)

            # Circuit breaker pattern
            if self.consecutive_errors >= self.error_threshold:
                self.write_log("Error threshold exceeded, stopping calculations", level=ERROR)
                self.stop_all_factors()
                raise RuntimeError("Critical error threshold exceeded")

            raise

    def _cleanup_memory(self):
        """Aggressive memory cleanup"""
        gc.collect()
        if psutil.Process().memory_percent() > 80:
            self.write_log("High memory usage detected, clearing caches", level=WARNING)
            self._cached_calculation.cache_clear()

    # Add performance monitoring capabilities
    def get_factor_metrics(self, factor_key: str) -> Optional[CalculationMetrics]:
        """Get performance metrics for a specific factor"""
        return self.metrics.get(factor_key)

    def get_slow_factors(self, threshold_seconds: float = 1.0) -> List[str]:
        """Identify slow-performing factors"""
        return [
            factor_key for factor_key, metrics in self.metrics.items()
            if metrics.calculation_time > threshold_seconds
        ]

    # Event Processing
    def process_tick_event(self, event: Event) -> None:
        """Market data tick push"""
        tick: TickData = event.data
        if not self.stacked_factors:
            return
        raise NotImplementedError("FactorMaker doesn't need to process tick event")

    def process_bar_event(self, event: Event) -> None:
        """Process incoming bar data."""
        bar: BarData = event.data
        self.dt = bar.datetime
        self.bars[bar.vt_symbol] = bar
        self.receiving_status[bar.vt_symbol] = True

        if all(self.receiving_status.values()):
            self.write_log(f"All bars received {self.dt}. start calculation", level=DEBUG)
            self.on_bars(self.dt, self.bars)  # push previous data to factor calculation
            self.receiving_status = {k: False for k in self.receiving_status.keys()}
            self.bars = {}

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
        """write log"""
        if factor:
            msg: str = f"{factor.factor_key}: {msg}"
        self.main_engine.write_log(msg, source=APP_NAME, level=level)

    def send_email(self, msg: str, factor: FactorTemplate = None) -> None:
        """send email"""
        subject: str = f"{factor.factor_key}" if factor else "Factor Maker Engine"
        self.main_engine.send_email(subject, msg, receiver=None)
