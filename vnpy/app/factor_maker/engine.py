import importlib
import traceback
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime, timedelta
from logging import getLogger
from typing import Type, Optional, Callable

from vnpy.app.factor_maker.base import APP_NAME, EVENT_FACTOR_LOG, EVENT_FACTOR_MAKER
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.event import EventEngine, Event
from vnpy.trader.constant import Interval
from vnpy.trader.database import BaseDatabase, get_database, DB_TZ
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import EVENT_TICK, EVENT_BAR
from vnpy.trader.object import LogData, ContractData, SubscribeRequest, TickData, BarData, HistoryRequest
from vnpy.trader.utility import load_json, save_json, extract_vt_symbol

import polars as pl

factor_module_name = 'vnpy.app.factor_maker.factors'


class FactorEngine(BaseEngine):
    setting_filename: str = "factor_maker_setting.json"
    data_filename: str = "factor_maker_data.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.factor_data: dict[str, dict] = {}

        self.classes: dict[str, Type[FactorTemplate]] = {}
        self.factors: dict[str, FactorTemplate] = {}

        self.symbol_factor_map: dict[str, list[FactorTemplate]] = {}

        self.init_executor: ThreadPoolExecutor = ThreadPoolExecutor(max_workers=1)

        self.memory_dict: dict[str, pl.Series] = {}
        self.max_memory_length: int = 10

        # 数据库和数据服务
        self.database: BaseDatabase = get_database()

    def init_engine(self) -> None:
        """"""
        self.load_factor_class()
        self.load_factor_setting()
        self.load_factor_data()
        self.register_event()
        self.init_all_factors()
        self.start_all_factors()
        self.write_log("因子计算引擎初始化成功")

    def register_event(self) -> None:
        """注册事件引擎"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_BAR, self.process_bar_event)

    def load_bars(self, factor: FactorTemplate, days: int, interval: Interval) -> None:
        """Load historical data"""
        vt_symbols: list = factor.vt_symbols
        dts: set[datetime] = set()
        history_data: dict[tuple, BarData] = {}

        # Fetch historical data from the database, data service, or API
        for vt_symbol in vt_symbols:
            data: list[BarData] = self.load_bar(vt_symbol, days, interval)

            for bar in data:
                dts.add(bar.datetime)
                history_data[(bar.datetime, vt_symbol)] = bar

        dts: list = list(dts)
        dts.sort()

        bars: dict = {}

        for dt in dts:
            for vt_symbol in vt_symbols:
                bar: Optional[BarData] = history_data.get((dt, vt_symbol), None)

                # If historical data for the specific contract and time is available, store it in the bars dictionary
                if bar:
                    bars[vt_symbol] = bar
                # If data is unavailable, use previous data in the bars dictionary to fill in
                elif vt_symbol in bars:
                    old_bar: BarData = bars[vt_symbol]

                    bar = BarData(
                        symbol=old_bar.symbol,
                        exchange=old_bar.exchange,
                        datetime=dt,
                        open_price=old_bar.close_price,
                        high_price=old_bar.close_price,
                        low_price=old_bar.close_price,
                        close_price=old_bar.close_price,
                        gateway_name=old_bar.gateway_name
                    )
                    bars[vt_symbol] = bar

            self.call_factor_func(factor, factor.on_bars, bars)

    def load_bar(self, vt_symbol: str, days: int, interval: Interval) -> list[BarData]:
        """Load historical data for a single contract"""
        symbol, exchange = extract_vt_symbol(vt_symbol)
        end: datetime = datetime.now(DB_TZ)
        start: datetime = end - timedelta(days)
        contract: Optional[ContractData] = self.main_engine.get_contract(vt_symbol)
        data: list[BarData]

        # Fetch historical data from the database first
        data = self.database.load_bar_data(
            symbol=symbol,
            exchange=exchange,
            interval=interval,
            start=start,
            end=end,
        )

        # If no data from the database, fetch via API or data service
        if not data:
            if contract and contract.history_data:
                req: HistoryRequest = HistoryRequest(
                    symbol=symbol,
                    exchange=exchange,
                    interval=interval,
                    start=start,
                    end=end
                )
                data = self.main_engine.query_history(req, contract.gateway_name)

            else:
                msg = f"Failed to load historical data for {vt_symbol}"
                self.write_log(msg)

        return data

    def load_factor_class(self):
        """Load a factor class from a specified module."""
        try:
            # Import the module
            self.module = importlib.import_module(factor_module_name)

        except Exception as e:
            logger = getLogger(__name__)
            logger.error(
                f"Failed to import factor module from {factor_module_name}, triggered exception:\n{traceback.format_exc()}")

    def load_factor_data(self) -> None:
        """加载策略数据"""
        self.factor_data = load_json(self.data_filename)

    def load_factor_setting(self) -> None:
        """加载策略配置"""
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
                "ticker": factor.ticker,
                "setting": factor.get_parameters(),
                "dependencies": factor.dependencies
            }

        save_json(self.setting_filename, factor_setting)

    def sync_factor_data(self, factor: FactorTemplate) -> None:
        """保存因子数据到文件"""
        data: dict = factor.get_variables()
        data.pop("inited")  # 不保存策略状态信息
        data.pop("trading")

        self.factor_data[factor.factor_name] = data
        save_json(self.data_filename, self.factor_data)

    def get_all_factor_class_names(self) -> list:
        """获取所有加载因子类名"""
        return list(self.classes.keys())

    def get_factor_class_parameters(self, class_name: str) -> dict:
        """获取策略类参数"""
        factor_class: FactorTemplate = getattr(self.module, class_name)

        parameters: dict = {}
        for name in factor_class.parameters:
            parameters[name] = getattr(factor_class, name)

        return parameters

    def get_factor_parameters(self, factor_name) -> dict:
        """获取策略参数"""
        factor: FactorTemplate = self.factors[factor_name]
        return factor.get_parameters()

    def init_all_factors(self) -> None:
        """初始化所有策略"""
        for factor_name in self.factors.keys():
            self.init_factor(factor_name)

    def init_factor(self, factor_name: str) -> None:
        """Initialize factor"""
        self.init_executor.submit(self._init_factor, factor_name)

    def _init_factor(self, factor_name: str) -> None:
        """Initialize factor"""
        factor: FactorTemplate = self.factors[factor_name]

        if factor.inited:
            self.write_log(f"Factor {factor_name} has already been initialized, duplicate operation is not allowed")
            return

        self.write_log(f"Factor {factor_name} is starting initialization")

        # Call the factor's on_init function
        self.call_factor_func(factor, factor.on_init)

        # Restore factor state
        data: Optional[dict] = self.factor_data.get(factor_name, None)
        if data:
            for name in factor.variables:
                value: Optional[object] = data.get(name, None)
                if value is None:
                    continue

                setattr(factor, name, value)

        # Subscribe to market data
        vt_symbol = f'{factor.ticker}.{factor.exchange.value}'
        contract: Optional[ContractData] = self.main_engine.get_contract(vt_symbol)
        if contract:
            req: SubscribeRequest = SubscribeRequest(
                symbol=contract.symbol, exchange=contract.exchange)
            self.main_engine.subscribe(req, contract.gateway_name)
        else:
            self.write_log(f"Market data subscription failed, contract {vt_symbol} not found", factor.factor_name)

        # Notify that the factor initialization is complete
        factor.inited = True
        self.max_memory_length = max(self.max_memory_length, factor.lookback_period)
        self.memory_dict[factor.factor_name] = pl.Series(name=factor.factor_name, data=[None] * self.max_memory_length)
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

        # Call the factor's on_start function
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

        # 调用因子on_stop函数
        self.call_factor_func(factor, factor.on_stop)

        # 同步数据状态
        self.write_log(f"因子{factor_name}同步数据状态")
        self.sync_factor_data(factor)

        # 推送因子事件通知停止完成状态
        self.put_factor_event(factor)

    def close(self) -> None:
        """关闭"""
        self.stop_all_factors()

    def add_factor(self, class_name: str, factor_name: str, ticker: str, setting: dict) -> None:

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

        factor: FactorTemplate = factor_class(self, ticker, setting)
        # factor_name should equal to factor.factor_name
        self.factors[factor_name] = factor

        vt_symbol = f'{factor.ticker}.{factor.exchange.value}'

        if vt_symbol not in self.symbol_factor_map:
            self.symbol_factor_map[vt_symbol] = []
        self.symbol_factor_map[vt_symbol].append(factor)

    def edit_factor(self, factor_name: str, setting: dict) -> None:
        """编辑因子参数"""
        factor: FactorTemplate = self.factors[factor_name]
        # update factor parameters
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

        vt_symbol = f'{factor.ticker}.{factor.exchange.value}'

        factors: list = self.symbol_factor_map[vt_symbol]
        factors.remove(factor)

        self.factors.pop(factor_name)
        self.save_factor_setting()

        self.factor_data.pop(factor_name, None)
        save_json(self.data_filename, self.factor_data)

        return True

    def write_log(self, msg: str, factor: FactorTemplate = None) -> None:
        """输出日志"""
        if factor:
            msg: str = f"{factor.factor_name}: {msg}"

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
        if factor:
            subject: str = f"{factor.factor_name}"
        else:
            subject: str = "Factor Maker Engine"

        self.main_engine.send_email(subject, msg)

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

    def process_tick_event(self, event: Event) -> None:
        """Market data tick push"""
        tick: TickData = event.data

        factors: list = self.symbol_factor_map[tick.vt_symbol]
        if not factors:
            return

        for factor in factors:
            if factor.inited:
                self.call_factor_func(factor, factor.on_tick, tick)

    def process_bar_event(self, event: Event) -> None:
        """K-line (bar) data push"""
        bar: BarData = event.data

        self.update_memory(bar)

        factors: list = self.symbol_factor_map[bar.vt_symbol]
        if not factors:
            return

        for factor in factors:
            if factor.inited:
                self.call_factor_func(factor, factor.on_bar, bar)
