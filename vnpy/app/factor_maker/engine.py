import importlib
import traceback
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime, timedelta
from logging import getLogger
from typing import Type, Optional, Callable, Union, List, Tuple
import dask

from vnpy.app.factor_maker.base import APP_NAME, EVENT_FACTOR_LOG, EVENT_FACTOR_MAKER, EVENT_FACTOR_RECORD, \
    RollingDataFrame
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.event import EventEngine, Event
from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.database import BaseDatabase, get_database, DB_TZ
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import EVENT_TICK, EVENT_BAR, EVENT_BAR_FACTOR, EVENT_FACTOR
from vnpy.trader.object import LogData, ContractData, TickData, BarData, HistoryRequest, FactorData
from vnpy.trader.utility import load_json, save_json, extract_vt_symbol

factor_module_name = 'vnpy.app.factor_maker.factors'


# factor maker engine


class FactorEngine(BaseEngine):
    setting_filename: str = "factor_maker_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.module = None

        self.factors: dict[str, FactorTemplate] = {}
        self.classes: dict[str, Type[FactorTemplate]] = {}

        self.memory: dict[str, RollingDataFrame] = {}
        self.max_memory_length = 10
        self.tasks = {}  # dask tasks

        self.executor = ThreadPoolExecutor(max_workers=1)
        self.database = get_database()
        self.dt = None
        self.bars = {}

        self.vt_symbols = main_engine.vt_symbols

    def init_engine(self) -> None:
        """"""
        self.load_factor_class()
        self.load_factor_setting()
        self.register_event()
        self.init_all_factors()
        self.build_computation_graph()  # Build the graph after initializing factors
        self.start_all_factors()
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

    def add_factor(self, class_name: str, factor_name: str, setting: dict) -> None:
        if factor_name in self.factors:
            msg = f"Creation failed, factor name {factor_name} already exists."
            self.write_log(msg)
            return
        factor_class = getattr(self.module, class_name)
        if not factor_class:
            msg = f"Creation failed, factor class {class_name} not found."
            self.write_log(msg)
            return
        if factor_class.__name__ not in self.classes:
            self.classes[factor_class.__name__] = factor_class
        factor: FactorTemplate = factor_class(engine=self, setting=setting)
        self.factors[factor_name] = factor

    def register_event(self) -> None:
        """注册事件引擎"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_BAR, self.process_bar_event)
        self.event_engine.register(EVENT_BAR_FACTOR, self.process_bar_factor_event)
        self.event_engine.register(EVENT_FACTOR, self.process_factor_event)





    def edit_factor(self, factor_name: str, setting: dict) -> None:
        """编辑因子参数"""
        factor: FactorTemplate = self.factors[factor_name]
        factor.update_setting(setting)
        self.save_factor_setting()
        self.put_factor_event(factor)

    def remove_factor(self, factor_name: str) -> bool:
        """移除因子实例"""
        factor: FactorTemplate = self.factors[factor_name]
        if factor.trading:
            msg: str = f"因子{factor_name}移除失败，请先停止"
            self.write_log(msg, factor)
            return False

        self.factors.pop(factor_name)
        self.save_factor_setting()

        return True

    def get_all_factor_class_names(self) -> list:
        """获取所有加载因子类名"""
        return list(self.classes.keys())

    def get_factor_class_parameters(self, class_name: str) -> dict:
        """获取策略类参数"""
        factor_class: FactorTemplate = getattr(self.module, class_name)
        parameters: dict = {name: getattr(factor_class, name) for name in factor_class.params}
        return parameters

    def get_factor_parameters(self, factor_name) -> dict:
        """获取策略参数"""
        factor: FactorTemplate = self.factors[factor_name]
        return factor.get_params()

    # Factor Lifecycle
    def init_all_factors(self) -> None:
        for name in self.factors:
            self.executor.submit(self.init_factor, name)

        self.memory["open"] = RollingDataFrame(self.vt_symbols, self.max_memory_length)
        self.memory["high"] = RollingDataFrame(self.vt_symbols, self.max_memory_length)
        self.memory["low"] = RollingDataFrame(self.vt_symbols, self.max_memory_length)
        self.memory["close"] = RollingDataFrame(self.vt_symbols, self.max_memory_length)
        self.memory["volume"] = RollingDataFrame(self.vt_symbols, self.max_memory_length)

    def init_factor(self, factor_name: str) -> None:
        factor = self.factors[factor_name]
        if factor.inited:
            self.write_log(f"Factor {factor_name} has already been initialized, duplicate operation is not allowed")
            return
        self.write_log(f"Factor {factor_name} is starting initialization")
        self.call_factor_func(factor, factor.on_init)

        factor.inited = True
        self.max_memory_length = max(self.max_memory_length, factor.lookback_period)
        self.put_factor_event(factor)
        self.write_log(f"Factor {factor_name} initialization complete")

    def start_all_factors(self) -> None:
        """启动所有策略"""
        for factor_name in self.factors.keys():
            self.start_factor(factor_name)

    def start_factor(self, factor_name: str) -> None:
        """Start factor"""
        factor: FactorTemplate = self.factors[factor_name]
        if not factor.inited:
            self.write_log(f"Factor {factor_name} failed to start, please initialize it first")
            return
        if factor.trading:
            self.write_log(f"Factor {factor_name} is already running, please do not repeat the operation")
            return
        self.call_factor_func(factor, factor.on_start)
        self.put_factor_event(factor)

    def stop_all_factors(self) -> None:
        """启动所有策略"""
        for factor_name in self.factors.keys():
            self.stop_factor(factor_name)

    def stop_factor(self, factor_name: str) -> None:
        """停止因子"""
        factor: FactorTemplate = self.factors[factor_name]
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

    def on_bars(self, dt: datetime, bars: dict) -> None:
        """Process a batch of bars."""
        open_prices = [bar.open_price for bar in bars.values()]
        high_prices = [bar.high_price for bar in bars.values()]
        low_prices = [bar.low_price for bar in bars.values()]
        close_prices = [bar.close_price for bar in bars.values()]
        volumes = [bar.volume for bar in bars.values()]

        self.memory["open"].append_row(dt, open_prices)
        self.memory["high"].append_row(dt, high_prices)
        self.memory["low"].append_row(dt, low_prices)
        self.memory["close"].append_row(dt, close_prices)
        self.memory["volume"].append_row(dt, volumes)

        memory = self.memory.copy()

        self.on_calculation()

    def on_calculation(self) -> None:
        """
        Execute the pre-built computation graph with updated memory.

        The memory is dynamically updated before each calculation.
        """
        if not hasattr(self, "tasks"):
            self.write_log("Computation graph has not been built. Please initialize the engine first.")
            return

        # Execute the computation graph
        results = dask.compute(*self.tasks.values())

        # Update factors with results
        for factor_name, result in zip(self.factors.keys(), results):
            self.factors[factor_name].update_results(result)  # fixme: store the result in the engine, not factors

        self.write_log("Factor calculations completed successfully.")

    def build_computation_graph(self) -> None:
        """
        Build the computation graph for all factors and store it in self.tasks.

        This method is called once after all factors are added to the engine.
        """

        def complete_factor_tree():
            for f_key, f in self.factors.items():
                for dep_f in f.dependencies_factor:
                    if dep_f.factor_key in self.factors:
                        continue
                    self.factors[dep_f.factor_key] = dep_f

        complete_factor_tree()

        # Function to create a task for a factor
        def create_task(factor_key: str) -> dask.delayed:
            """
            Create a Dask task for a given factor dynamically.

            Parameters:
                factor_key (str): The name of the factor to create the task for.

            Returns:
                dask.delayed: The Dask task for the factor calculation.
            """
            # Check if the task has already been created
            if factor_key in self.tasks:
                return self.tasks[factor_key]

            # Retrieve the factor instance
            factor = self.factors[factor_key]

            # Resolve dependencies recursively
            dep_tasks = {}
            if not factor.dependencies_factor:
                # Create memory dict with delayed tasks for each key
                memory_dict = {key: dask.delayed(df.get_dataframe)() for key, df in self.memory.items()}
                # Pass the memory_dict as input to factor.calculate
                self.tasks[factor_key] = dask.delayed(factor.calculate)(**memory_dict)
            else:
                # Resolve dependencies recursively
                for f in factor.dependencies_factor:
                    dep = f.factor_key
                    dep_tasks[dep] = create_task(dep)

                # Create the task for the current factor using memory and resolved dependencies
                self.tasks[factor_key] = dask.delayed(factor.calculate)(**dep_tasks)

            return self.tasks[factor_key]

        # Build tasks for all factors
        for factor_name in self.factors.keys():
            create_task(factor_name)

        self.write_log("Computation graph built successfully.")

    # Event Processing
    def process_tick_event(self, event: Event) -> None:
        """Market data tick push"""
        tick: TickData = event.data
        if not self.factors:
            return
        for factor_name, factor in self.factors:
            if factor.inited:
                self.call_factor_func(factor, factor.on_tick, tick)

    def process_bar_event(self, event: Event) -> None:
        """Process incoming bar data."""
        bar = event.data
        if not self.dt or bar.datetime > self.dt:
            if self.dt:
                self.on_bars(self.dt, self.bars)
            self.dt = bar.datetime
            self.bars = {}
        self.bars[bar.vt_symbol] = bar

    def process_bar_factor_event(self, event: Event) -> None:
        """K-line (bar) data push"""
        bar: BarData = event.data
        for k, factor in self.factors.items():
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

    def write_log(self, msg: str, factor: FactorTemplate = None) -> None:
        """输出日志"""
        if factor:
            msg: str = f"{factor.factor_key}: {msg}"
        log: LogData = LogData(msg=msg, gateway_name=APP_NAME)
        event: Event = Event(type=EVENT_FACTOR_LOG, data=log)
        self.event_engine.put(event)

    def put_factor_event(self, factor: FactorTemplate) -> None:
        """推送事件更新策略界面"""
        data: dict = factor.get_data()
        event: Event = Event(EVENT_FACTOR_MAKER, data)
        self.event_engine.put(event)

    def send_email(self, msg: str, factor: FactorTemplate = None) -> None:
        """发送邮件"""
        subject: str = f"{factor.factor_key}" if factor else "Factor Maker Engine"
        self.main_engine.send_email(subject, msg)
