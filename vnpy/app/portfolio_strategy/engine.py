import importlib
import traceback
from collections import defaultdict
from logging import getLogger
from typing import Type, Callable, Optional
from datetime import datetime, timedelta
from concurrent.futures import ThreadPoolExecutor

from vnpy.event import Event, EventEngine
from vnpy.trader.event import EVENT_FACTOR
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.object import (
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest,
    LogData,
    TickData,
    OrderData,
    TradeData,
    BarData,
    ContractData, FactorData
)
from vnpy.trader.event import (
    EVENT_TICK,
    EVENT_ORDER,
    EVENT_TRADE
)
from vnpy.trader.constant import (
    Direction,
    OrderType,
    Interval,
    Exchange,
    Offset
)
from vnpy.trader.utility import load_json, save_json, extract_vt_symbol, round_to
from vnpy.trader.datafeed import BaseDatafeed, get_datafeed
from vnpy.trader.database import BaseDatabase, get_database, DB_TZ

from vnpy.app.portfolio_strategy.base import (
    APP_NAME,
    EVENT_PORTFOLIO_LOG,
    EVENT_PORTFOLIO_STRATEGY,
    EngineType
)
from .locale import _
from vnpy.app.portfolio_strategy.template import StrategyTemplate

strategy_module_name = 'vnpy.app.portfolio_strategy.strategies'


class StrategyEngine(BaseEngine):
    """组合策略引擎"""

    engine_type: EngineType = EngineType.LIVE

    setting_filename: str = "portfolio_strategy_setting.json"
    data_filename: str = "portfolio_strategy_data.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.strategy_data: dict[str, dict] = {}
        self.classes: dict[str, Type[StrategyTemplate]] = {}
        self.strategies: dict[str, StrategyTemplate] = {}
        self.symbol_strategy_map: dict[str, list[StrategyTemplate]] = defaultdict(list)
        self.factor_strategy_map: dict[str, list[StrategyTemplate]] = defaultdict(list)
        self.orderid_strategy_map: dict[str, StrategyTemplate] = {}
        self.init_executor: ThreadPoolExecutor = ThreadPoolExecutor(max_workers=1)
        self.vt_tradeids: set[str] = set()
        self.database: BaseDatabase = get_database()
        self.datafeed: BaseDatafeed = get_datafeed()

    def init_engine(self) -> None:
        """初始化引擎"""
        self.init_datafeed()
        self.load_strategy_class()
        self.load_strategy_setting()
        self.load_strategy_data()
        self.register_event()
        self.write_log("组合策略引擎初始化成功")

    def register_event(self) -> None:
        """注册事件引擎"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_FACTOR, self.process_factor_event)

    def init_datafeed(self) -> None:
        """初始化数据服务"""
        result: bool = self.datafeed.init(self.write_log)
        if result:
            self.write_log(_("数据服务初始化成功"))

    # Loading and Saving Data
    def load_strategy_class(self):
        """Load a strategy class from a specified module."""
        try:
            self.module = importlib.import_module(strategy_module_name)
        except Exception as e:
            logger = getLogger(__name__)
            logger.error(f"Failed to import strategy module from {strategy_module_name}, triggered exception:\n{traceback.format_exc()}")

    def load_strategy_setting(self) -> None:
        """加载策略配置"""
        strategy_setting: dict = load_json(self.setting_filename)
        for strategy_name, strategy_config in strategy_setting.items():
            self.add_strategy(
                strategy_config["class_name"],
                strategy_name,
                strategy_config["vt_symbols"],
                strategy_config["setting"]
            )

    def save_strategy_setting(self) -> None:
        """保存策略配置"""
        strategy_setting: dict = {}
        for name, strategy in self.strategies.items():
            strategy_setting[name] = {
                "class_name": strategy.__class__.__name__,
                "vt_symbols": strategy.vt_symbols,
                "setting": strategy.get_parameters(),
                "factors": strategy.factors
            }
        save_json(self.setting_filename, strategy_setting)

    def load_strategy_data(self) -> None:
        """加载策略数据"""
        self.strategy_data = load_json(self.data_filename)

    def sync_strategy_data(self, strategy: StrategyTemplate) -> None:
        """保存策略数据到文件"""
        data: dict = strategy.get_variables()
        data.pop("inited")
        data.pop("trading")
        self.strategy_data[strategy.strategy_name] = data
        save_json(self.data_filename, self.strategy_data)

    # Strategy Management
    def add_strategy(self, class_name: str, strategy_name: str, vt_symbols: list, setting: dict) -> None:
        """Add and load a strategy instance from a specified module."""
        if strategy_name in self.strategies:
            msg = f"Creation failed, strategy name {strategy_name} already exists."
            self.write_log(msg)
            return
        strategy_class = getattr(self.module, class_name)
        if not strategy_class:
            msg: str = f"创建策略失败，找不到策略类{class_name}"
            self.write_log(msg)
            return
        if strategy_class.__name__ not in self.classes:
            self.classes[strategy_class.__name__] = strategy_class
        strategy: StrategyTemplate = strategy_class(self, strategy_name, vt_symbols, setting)
        self.strategies[strategy_name] = strategy
        for vt_symbol in vt_symbols:
            strategies: list = self.symbol_strategy_map[vt_symbol]
            strategies.append(strategy)
        for key, factor_data in strategy.factor_dict.items():
            strategies: list = self.factor_strategy_map[factor_data.vt_symbol]
            strategies.append(strategy)
        self.save_strategy_setting()
        self.put_strategy_event(strategy)

    def edit_strategy(self, strategy_name: str, setting: dict) -> None:
        """编辑策略参数"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        strategy.update_setting(setting)
        self.save_strategy_setting()
        self.put_strategy_event(strategy)

    def remove_strategy(self, strategy_name: str) -> bool:
        """移除策略实例"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        if strategy.trading:
            msg: str = f"策略{strategy_name}移除失败，请先停止"
            self.write_log(msg, strategy)
            return False
        for vt_symbol in strategy.vt_symbols:
            strategies: list = self.symbol_strategy_map[vt_symbol]
            strategies.remove(strategy)
        for vt_orderid in strategy.active_orderids:
            if vt_orderid in self.orderid_strategy_map:
                self.orderid_strategy_map.pop(vt_orderid)
        for factor in strategy.factors:
            strategies: list = self.factor_strategy_map[factor]
            strategies.remove(strategy)
        self.strategies.pop(strategy_name)
        self.save_strategy_setting()
        self.strategy_data.pop(strategy_name, None)
        save_json(self.data_filename, self.strategy_data)
        return True

    def get_all_strategy_class_names(self) -> list:
        """获取所有加载策略类名"""
        return list(self.classes.keys())

    def get_strategy_class_parameters(self, class_name: str) -> dict:
        """获取策略类参数"""
        strategy_class: StrategyTemplate = self.classes[class_name]
        parameters: dict = {name: getattr(strategy_class, name) for name in strategy_class.parameters}
        return parameters

    def get_strategy_parameters(self, strategy_name) -> dict:
        """获取策略参数"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        return strategy.get_parameters()

    # Strategy Lifecycle
    def init_all_strategies(self) -> None:
        """初始化所有策略"""
        for strategy_name in self.strategies.keys():
            self.init_strategy(strategy_name)

    def init_strategy(self, strategy_name: str) -> None:
        """初始化策略"""
        self.init_executor.submit(self._init_strategy, strategy_name)

    def _init_strategy(self, strategy_name: str) -> None:
        """初始化策略"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        if strategy.inited:
            self.write_log(_("{}已经完成初始化，禁止重复操作").format(strategy_name))
            return
        self.write_log(_("{}开始执行初始化").format(strategy_name))
        self.call_strategy_func(strategy, strategy.on_init)
        data: Optional[dict] = self.strategy_data.get(strategy_name, None)
        if data:
            for name in strategy.variables:
                value: Optional[object] = data.get(name, None)
                if value is None:
                    continue
                if name in {"pos_data", "target_data"}:
                    strategy_data = getattr(strategy, name)
                    strategy_data.update(value)
                else:
                    setattr(strategy, name, value)
        for vt_symbol in strategy.vt_symbols:
            contract: Optional[ContractData] = self.main_engine.get_contract(vt_symbol)
            if contract:
                req: SubscribeRequest = SubscribeRequest(symbol=contract.symbol, exchange=contract.exchange)
                self.main_engine.subscribe(req, contract.gateway_name)
            else:
                self.write_log(_("行情订阅失败，找不到合约{}").format(vt_symbol), strategy)
        strategy.inited = True
        self.put_strategy_event(strategy)
        self.write_log(_("{}初始化完成").format(strategy_name))

    def start_all_strategies(self) -> None:
        """启动所有策略"""
        for strategy_name in self.strategies.keys():
            self.start_strategy(strategy_name)

    def start_strategy(self, strategy_name: str) -> None:
        """启动策略"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        if not strategy.inited:
            self.write_log(_("策略{}启动失败，请先初始化").format(strategy.strategy_name))
            return
        if strategy.trading:
            self.write_log(_("{}已经启动，请勿重复操作").format(strategy_name))
            return
        self.call_strategy_func(strategy, strategy.on_start)
        self.put_strategy_event(strategy)

    def stop_all_strategies(self) -> None:
        """停止所有策略"""
        for strategy_name in self.strategies.keys():
            self.stop_strategy(strategy_name)

    def stop_strategy(self, strategy_name: str) -> None:
        """停止策略"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        if not strategy.trading:
            msg: str = f"策略{strategy_name}未启动, 无须停止"
            self.write_log(msg, strategy)
            return
        self.call_strategy_func(strategy, strategy.on_stop)
        self.write_log(f"策略{strategy_name}撤销全部委托")
        self.cancel_all(strategy)
        self.write_log(f"策略{strategy_name}同步数据状态")
        self.sync_strategy_data(strategy)
        self.put_strategy_event(strategy)

    def close(self) -> None:
        """关闭"""
        self.stop_all_strategies()

    # Historical Data Handling
    def load_bars(self, strategy: StrategyTemplate, days: int, interval: Interval) -> None:
        """Load historical data"""
        vt_symbols: list = strategy.vt_symbols
        dts: set[datetime] = set()
        history_data: dict[tuple, BarData] = {}
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
                if bar:
                    bars[vt_symbol] = bar
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
            self.call_strategy_func(strategy, strategy.on_bars, bars)

    def load_bar(self, vt_symbol: str, days: int, interval: Interval) -> list[BarData]:
        """Load historical data for a single contract"""
        symbol, exchange = extract_vt_symbol(vt_symbol)
        end: datetime = datetime.now(DB_TZ)
        start: datetime = end - timedelta(days)
        contract: Optional[ContractData] = self.main_engine.get_contract(vt_symbol)
        data: list[BarData] = self.database.load_bar_data(
            symbol=symbol,
            exchange=exchange,
            interval=interval,
            start=start,
            end=end,
        )
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
                data = self.query_bar_from_datafeed(symbol, exchange, interval, start, end)
        return data

    def query_bar_from_datafeed(self, symbol: str, exchange: Exchange, interval: Interval, start: datetime, end: datetime) -> list[BarData]:
        """通过数据服务获取历史数据"""
        req: HistoryRequest = HistoryRequest(
            symbol=symbol,
            exchange=exchange,
            interval=interval,
            start=start,
            end=end
        )
        data: list[BarData] = self.datafeed.query_bar_history(req, self.write_log)
        return data

    # Event Processing
    def process_tick_event(self, event: Event) -> None:
        """行情数据推送"""
        tick: TickData = event.data
        strategies: list = self.symbol_strategy_map[tick.vt_symbol]
        if not strategies:
            return
        for strategy in strategies:
            if strategy.inited:
                self.call_strategy_func(strategy, strategy.on_tick, tick)

    def process_bar_event(self, event: Event) -> None:
        """K线数据推送"""
        bar: BarData = event.data
        strategies: list = self.symbol_strategy_map[bar.vt_symbol]
        if not strategies:
            return
        for strategy in strategies:
            if strategy.inited:
                self.call_strategy_func(strategy, strategy.on_bar, bar)

    def process_order_event(self, event: Event) -> None:
        """委托数据推送"""
        order: OrderData = event.data
        strategy: Optional[StrategyTemplate] = self.orderid_strategy_map.get(order.vt_orderid, None)
        if not strategy:
            return
        self.call_strategy_func(strategy, strategy.update_order, order)

    def process_trade_event(self, event: Event) -> None:
        """成交数据推送"""
        trade: TradeData = event.data
        if trade.vt_tradeid in self.vt_tradeids:
            return
        self.vt_tradeids.add(trade.vt_tradeid)
        strategy: Optional[StrategyTemplate] = self.orderid_strategy_map.get(trade.vt_orderid, None)
        if not strategy:
            return
        self.call_strategy_func(strategy, strategy.update_trade, trade)

    def process_factor_event(self, event: Event) -> None:
        """process factor data"""
        factor: FactorData = event.data
        factor_vt_symbol = factor.vt_symbol
        strategies: list = self.factor_strategy_map[factor_vt_symbol]
        if not strategies:
            return
        for strategy in strategies:
            if strategy.inited:
                self.call_strategy_func(strategy, strategy.on_factor, factor)

    # Order and Trade Operations
    def send_order(self, strategy: StrategyTemplate, vt_symbol: str, direction: Direction, offset: Offset, price: float, volume: float, lock: bool, net: bool) -> Optional[list]:
        """发送委托"""
        contract: Optional[ContractData] = self.main_engine.get_contract(vt_symbol)
        if not contract:
            msg: str = f"委托失败，找不到合约{vt_symbol}"
            self.write_log(msg, strategy)
            return
        price: float = round_to(price, contract.pricetick)
        volume: float = round_to(volume, contract.min_volume)
        original_req: OrderRequest = OrderRequest(
            symbol=contract.symbol,
            exchange=contract.exchange,
            direction=direction,
            offset=offset,
            type=OrderType.LIMIT,
            price=price,
            volume=volume,
            reference=f"{APP_NAME}_{strategy.strategy_name}"
        )
        req_list: list[OrderRequest] = self.main_engine.convert_order_request(original_req, contract.gateway_name, lock, net)
        vt_orderids: list = []
        for req in req_list:
            vt_orderid: str = self.main_engine.send_order(req, contract.gateway_name)
            if not vt_orderid:
                continue
            vt_orderids.append(vt_orderid)
            self.main_engine.update_order_request(req, vt_orderid, contract.gateway_name)
            self.orderid_strategy_map[vt_orderid] = strategy
        return vt_orderids

    def cancel_order(self, strategy: StrategyTemplate, vt_orderid: str) -> None:
        """委托撤单"""
        order: Optional[OrderData] = self.main_engine.get_order(vt_orderid)
        if not order:
            self.write_log(f"撤单失败，找不到订单{vt_orderid}", strategy)
            return
        req: CancelRequest = order.create_cancel_request()
        self.main_engine.cancel_order(req, order.gateway_name)

    def cancel_all(self, strategy: StrategyTemplate) -> None:
        """委托撤单"""
        for vt_orderid in list(strategy.active_orderids):
            self.cancel_order(strategy, vt_orderid)

    # Utility Functions
    def call_strategy_func(self, strategy: StrategyTemplate, func: Callable, params: object = None) -> None:
        """安全调用策略函数"""
        try:
            if params:
                func(params)
            else:
                func()
        except Exception:
            strategy.trading = False
            strategy.inited = False
            msg: str = f"触发异常已停止\n{traceback.format_exc()}"
            self.write_log(msg, strategy)

    def put_strategy_event(self, strategy: StrategyTemplate) -> None:
        """推送事件更新策略界面"""
        data: dict = strategy.get_data()
        event: Event = Event(EVENT_PORTFOLIO_STRATEGY, data)
        self.event_engine.put(event)

    def write_log(self, msg: str, strategy: StrategyTemplate = None) -> None:
        """输出日志"""
        if strategy:
            msg: str = f"{strategy.strategy_name}: {msg}"
        log: LogData = LogData(msg=msg, gateway_name=APP_NAME)
        event: Event = Event(type=EVENT_PORTFOLIO_LOG, data=log)
        self.event_engine.put(event)

    def send_email(self, msg: str, strategy: StrategyTemplate = None) -> None:
        """发送邮件"""
        subject: str = f"{strategy.strategy_name}" if strategy else "组合策略引擎"
        self.main_engine.send_email(subject, msg)

    def get_engine_type(self) -> EngineType:
        """获取引擎类型"""
        return self.engine_type

    def get_pricetick(self, strategy: StrategyTemplate, vt_symbol: str) -> Optional[float]:
        """获取合约价格跳动"""
        contract: Optional[ContractData] = self.main_engine.get_contract(vt_symbol)
        if contract:
            return contract.pricetick
        else:
            self.write_log(f"获取合约{vt_symbol}失败", strategy)
            return None

    def get_size(self, strategy: StrategyTemplate, vt_symbol: str) -> Optional[float]:
        """获取合约乘数"""
        contract: Optional[ContractData] = self.main_engine.get_contract(vt_symbol)
        if contract:
            return contract.size
        else:
            self.write_log(f"获取合约{vt_symbol}失败", strategy)
            return None

    def get_tick(self, vt_symbol) -> TickData:
        return self.main_engine.get_tick(vt_symbol)
