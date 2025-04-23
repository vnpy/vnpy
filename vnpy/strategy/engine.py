import importlib
import traceback
import os
from typing import Type, Callable, Dict, List, TYPE_CHECKING, Optional
from datetime import datetime
from concurrent.futures import ThreadPoolExecutor
from logging import INFO, ERROR, DEBUG
from pathlib import Path
from types import ModuleType
import glob

from vnpy.event import Event, EventEngine
from vnpy.strategy.base import (
    APP_NAME,
    EVENT_PORTFOLIO_LOG,
    EVENT_PORTFOLIO_STRATEGY,

)
from vnpy.trader.constant import EngineType
from vnpy.trader.database import BaseDatabase, get_database
from vnpy.trader.datafeed import BaseDatafeed, get_datafeed
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import (
    EVENT_FACTOR,
    EVENT_ORDER,
    EVENT_TRADE
)
from vnpy.trader.object import (
    OrderRequest,
    SubscribeRequest,
    LogData,
    TickData,
    OrderData,
    BarData,
    ContractData
)
from vnpy.trader.utility import load_json, save_json, virtual
from .execution_agent import ExecutionAgent
from .base import StrategyState, AlgoStatus

if TYPE_CHECKING:
    from vnpy.strategy.template import StrategyTemplate


class BaseStrategyEngine(BaseEngine):
    """A Base Strategy Engine for defining generic functions and abstractmethods"""

    engine_type: EngineType = EngineType.LIVE
    setting_filename: str = "strategy_setting.json"

    # requirements
    required_factors = set()
    required_vt_symbols = set()

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine, engine_name: str = APP_NAME) -> None:
        """Initialize the strategy engine"""
        super().__init__(main_engine, event_engine, engine_name=engine_name)
        self.module = None
        self.setting_filename = f"{self.engine_name}_setting.json"

        # Core state management
        self.settings: dict[str, dict] = {}  # Strategy settings storage
        self.classes: dict[str, Type[StrategyTemplate]] = {}
        self.strategies: dict[str, StrategyTemplate] = {}
        self.orderid_strategy_map: dict[str, StrategyTemplate] = {}

        # Factor data caching
        self.latest_factors: Dict[str, Dict] = {}
        self.factor_update_time: datetime = datetime.utcnow()
        self.database: BaseDatabase = get_database()
        self.datafeed: BaseDatafeed = get_datafeed()

        # Thread and external resources
        self.init_executor: ThreadPoolExecutor = ThreadPoolExecutor(max_workers=1)
        self.vt_tradeids: set[str] = set()

        # Configure execution agent
        self.execution_agent = ExecutionAgent(
            main_engine=self.main_engine,
            gateway_name="BINANCE"  # Configurable gateway todo: if this is the expected name
        )

    # --------------------------------
    # Engine Core Methods
    # --------------------------------
    def init_engine(self) -> None:
        """Initialize the engine"""
        # Step 0: Initialize data sources
        self.init_datafeed()

        # Step 1: Load strategy classes
        self.load_strategy_class()

        # Step 2: Load strategy settings
        self.load_strategy_setting()

        # Step 3: Load strategy data
        self.load_strategy_data()

        self.register_event()
        self.write_log(f"{self.engine_name} initialized")

    def init_datafeed(self) -> None:
        """Initialize data feed"""
        result: bool = self.datafeed.init(self.write_log)
        if result:
            self.write_log("Data feed initialized successfully")

    def register_event(self) -> None:
        """Register event handlers"""
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_FACTOR, self.process_factor_event)

    def close(self) -> None:
        """Close the engine"""
        self.stop_all_strategies()

    # --------------------------------
    # Settings Management
    # --------------------------------

    def load_strategy_class(self) -> None:
        """"""
        # todo: check whether we need this or not
        # path1: Path = Path(__file__).parent.joinpath("strategies")
        # self.load_strategy_class_from_folder(path1, "strategy.strategies")

        path2: Path = Path.cwd().joinpath("strategies")
        self.load_strategy_class_from_folder(path2, "strategies")

    def load_strategy_class_from_folder(self, path: Path, module_name: str = "") -> None:
        """"""
        for suffix in ["py", "pyd", "so"]:
            pathname: str = str(path.joinpath(f"*.{suffix}"))
            for filepath in glob.glob(pathname):
                stem: str = Path(filepath).stem
                strategy_module_name: str = f"{module_name}.{stem}"
                self.load_strategy_class_from_module(strategy_module_name)

    def load_strategy_class_from_module(self, module_name: str) -> None:
        """"""
        try:
            self.module: ModuleType = importlib.import_module(module_name)

            for name in dir(self.module):
                value = getattr(self.module, name)
                if (isinstance(value, type) and issubclass(value, StrategyTemplate) and value is not StrategyTemplate):
                    self.classes[value.__name__] = value
            self.write_log(f"Successfully loaded {len(self.classes)} strategy classes", level=INFO)

        except:  # noqa
            self.write_log(
                f"Failed to import strategy module from {module_name}, triggered exception:\n{traceback.format_exc()}",
                level=ERROR)

    def load_strategy_setting(self) -> None:
        """Load strategy settings and create instances"""
        self.settings = load_json(self.setting_filename)  # create new file if not exists

        # Create strategy instances from settings
        for strategy_name, setting in self.settings.items():
            self.add_strategy(
                class_name=setting["class_name"],
                strategy_name=strategy_name,
                vt_symbols=setting["vt_symbols"],
                setting=setting["setting"]
            )

    def save_strategy_setting(self) -> None:
        """"""
        strategy_setting: dict = {}

        for name, strategy in self.strategies.items():
            strategy_setting[name] = {
                "class_name": strategy.__class__.__name__,
                "vt_symbols": strategy.vt_symbols,
                "setting": strategy.get_parameters(),
                "factors": strategy.factors
            }

        save_json(self.setting_filename, strategy_setting)

    def update_strategy_setting(self, strategy: StrategyTemplate) -> None:
        """Update single strategy setting"""
        self.settings[strategy.strategy_name] = strategy.get_settings()
        # save_json(self.setting_filename, self.settings)
        self.write_log(f"Updated settings for strategy: {strategy.strategy_name}", level=INFO)

    def remove_strategy_setting(self, strategy_name: str) -> None:
        """
        Update setting file.
        """
        if strategy_name not in self.settings:
            return

        self.settings.pop(strategy_name, None)

    # def save_strategy_state(self, strategy_name: str) -> None:
    #     """Save both settings and data for a strategy"""
    #     strategy = self.strategies[strategy_name]
    #
    #     # Save settings
    #     self.update_strategy_setting(strategy)
    #
    #     # Save data
    #     self.sync_strategy_data(strategy)
    #
    #     self.write_log(f"Saved complete state for strategy: {strategy_name}")

    # def sync_strategy_data(self, strategy: StrategyTemplate) -> None:
    #     """Sync strategy runtime data"""
    #     data_filename = f"portfolio_strategy_{strategy.strategy_name}_data.json"
    #     save_json(data_filename, strategy.get_data())
    #     self.write_log(f"Synced data for strategy: {strategy.strategy_name}")

    # --------------------------------
    # Strategy Management
    # --------------------------------
    def add_strategy(self, class_name: str, strategy_name: str, vt_symbols: list, setting: dict) -> None:
        """Add a new strategy instance"""
        if strategy_name in self.strategies:
            self.write_log(f"Creation failed, strategy {strategy_name} already exists", level=ERROR)
            return

        strategy_class: Optional[Type[StrategyTemplate]] = getattr(self.module, class_name)
        if not strategy_class:
            self.write_log(f"Creation failed, strategy class {class_name} not found", level=ERROR)
            return

        if strategy_class.__name__ not in self.classes:
            self.classes[strategy_class.__name__] = strategy_class

        strategy = strategy_class(self, strategy_name, vt_symbols, setting)

        # Validate strategy requirements
        if not self._validate_requirements(strategy):
            return

        # pass validation, add strategy
        self.strategies[strategy_name] = strategy
        self.update_strategy_setting(strategy)

    def edit_strategy(self, strategy_name: str, setting: dict) -> None:
        """Edit strategy state"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        strategy.update_setting(setting)
        self.update_strategy_setting(strategy)
        self.save_strategy_setting()

    def remove_strategy(self, strategy_name: str) -> bool:
        """Remove a strategy instance"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        if strategy.trading:
            self.write_log(f"Strategy {strategy_name} removal failed - please stop first", strategy, level=ERROR)
            return False

        # Remove strategy instance
        self.strategies.pop(strategy_name)

        # Remove setting
        self.remove_strategy_setting(strategy_name)
        self.save_strategy_setting()

        return True

    def _validate_requirements(self, strategy: StrategyTemplate) -> bool:
        """Validate strategy requirements"""
        missing_symbols = set(strategy.required_vt_symbols) - set(self.required_vt_symbols)
        if missing_symbols:
            self.write_log(f"Missing required symbols: {missing_symbols}", level=ERROR)
            return False

        missing_factors = set(strategy.required_factors) - set(self.required_factors)
        if missing_factors:
            self.write_log(f"Missing required factors: {missing_factors}", level=ERROR)
            return False

        return True

    # --------------------------------
    # Strategy data Management
    # --------------------------------
    @virtual
    def load_strategy_data(self) -> None:
        """Load runtime data for each strategy"""
        # fixme: load data from database and datafeed. just like factor maker
        pass

    # --------------------------------
    # Strategy Lifecycle Management
    # --------------------------------
    # def init_strategy(self, strategy_name: str) -> None:
    #     """Initialize a strategy"""
    #     self.init_executor.submit(self._init_strategy, strategy_name)

    def init_strategy(self, strategy_name: str) -> None:
        """Initialize strategy with saved state"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        if strategy.inited:
            self.write_log(f"{strategy_name} already initialized", level=DEBUG)
            return

        self.write_log(f"Initializing {strategy_name}", level=DEBUG)

        # Subscribe market data
        for vt_symbol in strategy.vt_symbols:
            contract = self.main_engine.get_contract(vt_symbol)
            if contract:
                req = SubscribeRequest(
                    symbol=contract.symbol,
                    exchange=contract.exchange,
                    interval=contract.interval,
                )
                self.main_engine.subscribe(req, contract.gateway_name)
            else:
                self.write_log(f"Contract not found: {vt_symbol}", strategy)
                return

        strategy.inited = True
        self.put_strategy_event(strategy)
        self.write_log(f"{strategy_name} initialized")

    @virtual
    def start_strategy(self, strategy_name: str) -> None:
        """Start a strategy"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        if not strategy.inited:
            self.write_log(f"Strategy {strategy_name} start failed, please initialize first")
            return
        if strategy.trading:
            self.write_log(f"{strategy_name} already started, do not repeat operation")
            return
        # self.call_strategy_func(strategy, strategy.on_start) # useless yet
        strategy.trading = True
        # self.put_strategy_event(strategy) # useless yet

    @virtual
    def stop_strategy(self, strategy_name: str) -> None:
        """Stop running strategy"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        if not strategy.trading:
            return

        strategy.trading = False

        # Cancel all active orders and close positions
        cancel_reqs = self.call_strategy_func(strategy, strategy.cancel_all_active_orders)
        if cancel_reqs:
            for req in cancel_reqs:
                self.cancel_order(req)
                self.write_log(f"Cancelled order: {req}")

        close_order_reqs = self.call_strategy_func(strategy, strategy.close_all_positions)
        if close_order_reqs:
            for req in close_order_reqs:
                self.send_order(
                    strategy.strategy_name,
                    req,
                    lock=False,
                    net=False
                )
                self.write_log(f"Closed position: {req}")

        # Save complete strategy state
        self.save_strategy_state(strategy_name)

        self.write_log(f"Strategy {strategy_name} stopped and state saved")

    def save_strategy_state(self, strategy_name):
        """Save strategy state"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        self.update_strategy_setting(strategy)
        # self.sync_strategy_data(strategy) # commented out in original code

    @virtual
    def init_all_strategies(self) -> None:
        """Initialize all strategies"""
        for strategy_name in self.strategies.keys():
            self.init_strategy(strategy_name)

    @virtual
    def start_all_strategies(self) -> None:
        """Start all strategies"""
        for strategy_name in self.strategies.keys():
            self.start_strategy(strategy_name)

    @virtual
    def stop_all_strategies(self) -> None:
        """Stop all strategies"""
        for strategy_name in self.strategies.keys():
            self.stop_strategy(strategy_name)

    # --------------------------------
    # Event Processing
    # --------------------------------
    def process_order_event(self, event: Event) -> None:
        """Process order updates"""
        order = event.data

        strategy = self.strategies.get(order.reference)
        if strategy:
            self.call_strategy_func(strategy, strategy.on_order, order)

    def process_trade_event(self, event: Event) -> None:
        """Process trade updates"""
        trade = event.data

        strategy = self.strategies.get(trade.reference)
        if strategy:
            self.call_strategy_func(strategy, strategy.on_trade, trade)

    def process_factor_event(self, event: Event) -> None:
        """Process factor updates"""
        try:
            factor_dict = event.data
            self.latest_factors.update(factor_dict)
            self.factor_update_time = datetime.now()

            for strategy in self.strategies.values():
                if strategy.inited and strategy.trading:
                    order_reqs: List[OrderRequest] = self.call_strategy_func(strategy, strategy.on_factor,
                                                                             self.latest_factors)

                    if order_reqs:
                        for req in order_reqs:
                            self.send_order(
                                strategy.strategy_name,
                                req=req,
                                lock=False,
                                net=False
                            )
                            self.write_log(f"Sent order for {strategy.strategy_name}: {req}")

        except Exception as e:
            self.write_log(f"Error processing factor event: {str(e)}")

    # --------------------------------
    # Order Management
    # --------------------------------
    @virtual
    def send_order(
            self,
            strategy: StrategyTemplate,
            req: OrderRequest,
            lock: bool = False,
            net: bool = False
    ) -> List[str]:
        """Send order via execution agent"""
        return self.execution_agent.send_order(
            req=req,
            lock=False,
            net=False
        )

    @virtual
    def cancel_order(self, req) -> None:
        """Cancel order via execution agent"""
        self.execution_agent.cancel_order(req)

    # --------------------------------
    # Utility Methods
    # --------------------------------
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

    def get_engine_type(self) -> EngineType:
        """Get engine type"""
        return self.engine_type

    def get_tick(self, vt_symbol) -> TickData:
        """Get tick data"""
        return self.main_engine.get_tick(vt_symbol)

    def get_bar(self, vt_symbol) -> BarData:
        """Get bar data"""
        return self.main_engine.get_bar(vt_symbol)

    def get_all_strategy_class_names(self) -> list:
        """获取所有加载策略类名"""
        return list(self.classes.keys())

    def get_strategy_class_parameters(self, class_name: str) -> dict:
        """获取策略类参数"""
        strategy_class: Type[StrategyTemplate] = self.classes[class_name]

        parameters: dict = {}
        for name in strategy_class.parameters:
            parameters[name] = getattr(strategy_class, name)

        return parameters

    def get_strategy_parameters(self, strategy_name) -> dict:
        """获取策略参数"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        return strategy.get_parameters()

    def call_strategy_func(self, strategy: StrategyTemplate, func: Callable, params: object = None):
        """Safely call strategy function"""
        try:
            if params:
                return func(params)
            else:
                return func()
        except Exception:
            strategy.trading = False
            strategy.inited = False
            msg: str = f"Exception triggered, stopped\n{traceback.format_exc()}"
            self.write_log(msg, strategy)

    def put_strategy_event(self, strategy: StrategyTemplate) -> None:
        """Push event to update strategy interface"""
        data: dict = strategy.get_data()
        event: Event = Event(EVENT_PORTFOLIO_STRATEGY, data)
        self.event_engine.put(event)

    @virtual
    def write_log(self, msg: str, strategy: StrategyTemplate = None, level=INFO) -> None:
        """Write log"""
        if strategy:
            msg: str = f"{strategy.strategy_name}: {msg}"
        else:
            msg: str = f"{self.engine_name}: {msg}"
        log: LogData = LogData(msg=msg, gateway_name=APP_NAME, level=level)
        event: Event = Event(type=EVENT_PORTFOLIO_LOG, data=log)
        self.event_engine.put(event)

    def send_email(self, msg: str, strategy: StrategyTemplate = None) -> None:
        """Send email"""
        subject: str = f"{strategy.strategy_name}" if strategy else "Portfolio Strategy Engine"
        self.main_engine.send_email(subject, msg)
