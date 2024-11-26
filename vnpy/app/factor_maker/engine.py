import importlib
import traceback
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime, timedelta
from logging import getLogger
from typing import Type, Optional, Callable

from vnpy.app.factor_maker.base import APP_NAME, EVENT_FACTOR_LOG, EVENT_FACTOR_MAKER, EVENT_FACTOR_RECORD, \
    RollingDataFrame
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.event import EventEngine, Event
from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.database import BaseDatabase, get_database, DB_TZ
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import EVENT_TICK, EVENT_BAR, EVENT_BAR_FACTOR, EVENT_FACTOR
from vnpy.trader.object import LogData, ContractData, SubscribeRequest, TickData, BarData, HistoryRequest, FactorData
from vnpy.trader.utility import load_json, save_json, extract_vt_symbol

factor_module_name = 'vnpy.app.factor_maker.factors'


# factor maker engine


class FactorEngine(BaseEngine):
    setting_filename: str = "factor_maker_setting.json"
    data_filename: str = "factor_maker_data.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.factor_data: dict[str, dict] = {}
        self.classes: dict[str, Type[FactorTemplate]] = {}
        self.factors: dict[str, FactorTemplate] = {}
        self.init_executor: ThreadPoolExecutor = ThreadPoolExecutor(max_workers=1)
        self.memory: dict[str, RollingDataFrame] = {}
        self.max_memory_length: int = 10
        self.database: BaseDatabase = get_database()
        self.vt_symbols = self.main_engine.vt_symbols
        self.dt = None
        self.bars = {}

    def init_engine(self) -> None:
        """"""
        self.load_factor_class()
        self.load_factor_setting()
        self.load_factor_data()
        self.register_event()
        self.initialize_factors()
        self.start_factors()
        self.write_log("因子计算引擎初始化成功")

    def register_event(self) -> None:
        """注册事件引擎"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_BAR, self.process_bar_event)

    # Loading and Saving Data
    def load_factor_class(self):
        """Load a factor class from a specified module."""
        try:
            self.module = importlib.import_module(factor_module_name)
        except Exception as e:
            logger = getLogger(__name__)
            logger.error(
                f"Failed to import factor module from {factor_module_name}, triggered exception:\n{traceback.format_exc()}")

    def load_factor_setting(self) -> None:
        """加载因子计算策略配置"""
        factor_setting: dict = load_json(self.setting_filename)
        for factor_name, factor_config in factor_setting.items():
            self.add_factor(
                factor_config["class_name"],
                factor_name,
                factor_config["ticker"],
                factor_config["setting"]
            )

    def save_factor_setting(self) -> None:
        """保存因子配置"""
        factor_setting: dict = {}
        for name, factor in self.factors.items():
            factor_setting[name] = {
                "class_name": factor.__class__.__name__,
                "ticker": factor.symbol,
                "setting": factor.get_parameters(),
                "dependencies": factor.dependencies
            }
        save_json(self.setting_filename, factor_setting)

    def load_factor_data(self) -> None:
        """加载策略数据"""
        self.factor_data = load_json(self.data_filename)

    def sync_factor_data(self, factor: FactorTemplate) -> None:
        """保存因子数据到文件"""
        data: dict = factor.get_variables()
        data.pop("inited")
        data.pop("trading")
        self.factor_data[factor.factor_key] = data
        save_json(self.data_filename, self.factor_data)

    # Factor Management
    def add_factor(self, class_name: str, factor_name: str, settings: dict) -> None:
        if factor_name in self.factors:
            self.write_log(f"Factor {factor_name} already exists.")
            return

        try:
            factor_class = getattr(self.module, class_name)
        except AttributeError:
            self.write_log(f"Factor class {class_name} not found.")
            return

        if factor_class.__name__ not in self.classes:
            self.classes[factor_class.__name__] = factor_class

        factor = factor_class(engine=self, settings=settings)
        self.factors[factor_name] = factor

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
        self.factor_data.pop(factor_name, None)
        save_json(self.data_filename, self.factor_data)
        return True

    def get_all_factor_class_names(self) -> list:
        """获取所有加载因子类名"""
        return list(self.classes.keys())

    def get_factor_class_parameters(self, class_name: str) -> dict:
        """获取策略类参数"""
        factor_class: FactorTemplate = getattr(self.module, class_name)
        parameters: dict = {name: getattr(factor_class, name) for name in factor_class.parameters}
        return parameters

    def get_factor_parameters(self, factor_name) -> dict:
        """获取策略参数"""
        factor: FactorTemplate = self.factors[factor_name]
        return factor.get_parameters()

    # Factor Lifecycle

    def initialize_factors(self) -> None:
        for name in self.factors:
            self.executor.submit(self.initialize_factor, name)

        self.memory["open"] = RollingDataFrame(self.vt_symbols, self.max_memory_length)
        self.memory["high"] = RollingDataFrame(self.vt_symbols, self.max_memory_length)
        self.memory["low"] = RollingDataFrame(self.vt_symbols, self.max_memory_length)
        self.memory["close"] = RollingDataFrame(self.vt_symbols, self.max_memory_length)
        self.memory["volume"] = RollingDataFrame(self.vt_symbols, self.max_memory_length)

    def initialize_factor(self, factor_name: str) -> None:
        factor = self.factors[factor_name]
        if factor.inited:
            self.write_log(f"Factor {factor_name} is already initialized.")
            return

        self.write_log(f"Initializing factor {factor_name}.")
        self.safely_call(factor, factor.on_init)
        factor.inited = True

        self.max_memory_length = max(self.max_memory_length, factor.lookback_period)
        self.write_log(f"Factor {factor_name} initialized.")

    def start_factors(self) -> None:
        for name in self.factors:
            self.start_factor(name)

    def start_factor(self, factor_name: str) -> None:
        factor = self.factors[factor_name]
        if not factor.inited:
            self.write_log(f"Cannot start factor {factor_name}, it is not initialized.")
            return
        if factor.trading:
            self.write_log(f"Factor {factor_name} is already running.")
            return

        self.safely_call(factor, factor.on_start)
        factor.trading = True
        self.write_log(f"Factor {factor_name} started.")

    def stop_factors(self) -> None:
        for name in self.factors:
            self.stop_factor(name)

    def stop_factor(self, factor_name: str) -> None:
        factor = self.factors[factor_name]
        if not factor.trading:
            self.write_log(f"Factor {factor_name} is not running.")
            return

        self.safely_call(factor, factor.on_stop)
        factor.trading = False
        self.sync_data(factor)
        self.write_log(f"Factor {factor_name} stopped.")

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

        self.on_calculation()

    def on_calculation(self):
        pass

    # Event Processing
    def process_tick_event(self, event: Event) -> None:
        """Market data tick push"""
        tick: TickData = event.data
        if not self.factors:
            return
        pass

    def process_bar_event(self, event: Event) -> None:
        """Process incoming bar data."""
        bar = event.data
        if not self.dt or bar.datetime > self.dt:
            if self.dt:
                self.on_bars(self.dt, self.bars)
            self.dt = bar.datetime
            self.bars = {}
        self.bars[bar.vt_symbol] = bar

    # Utilities
    def safely_call(self, factor: FactorTemplate, func: Callable, *args) -> None:
        try:
            func(*args)
        except Exception:
            factor.trading = False
            self.write_log(f"Error in factor {factor.factor_key}:\n{traceback.format_exc()}")

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
