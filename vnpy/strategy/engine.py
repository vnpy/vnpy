import importlib
import traceback
import os
from typing import Type, Callable, Dict, List, TYPE_CHECKING,Optional
from datetime import datetime
from concurrent.futures import ThreadPoolExecutor
from logging import INFO,ERROR,DEBUG

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
    BarData
)
from vnpy.trader.utility import load_json, save_json, virtual
from .execution_agent import ExecutionAgent
from .base import StrategyState, AlgoStatus

if TYPE_CHECKING:
    from vnpy.strategy.template import StrategyTemplate
strategy_module_name = 'vnpy.app.portfolio_strategy.strategies'

"""
Based on the provided files, here are the mutual member functions found across the strategy engines:

strategy control
- [x] start_strategy	Start a specific strategy
- [x] stop_strategy	Stop a specific strategy
- [x] init_strategy	Initialize a specific strategy

strategy management
- [ ] add_strategy	Add a new strategy instance
- [ ] edit_strategy	Edit strategy parameters
- [ ] remove_strategy	Remove a strategy instance

- [ ] write_log	Write log messages
- [ ] process_tick_event	Process incoming tick data
- [ ] process_order_event	Process order updates
- [ ] process_trade_event	Process trade updates
- [ ] send_order	Send trading orders
- [ ] cancel_order	Cancel existing orders
- [ ] get_pricetick	Get contract price tick size
- [ ] get_size	Get contract size
Common Batch Operations
- [ ] load_strategy_class	Load strategy classes from files
- [ ] start_all_strategies	Start all strategies
- [ ] stop_all_strategies	Stop all strategies
- [ ] init_all_strategies	Initialize all strategies
Common Settings Management
- [ ] get_strategy_class_parameters	Get strategy class default parameters
- [ ] get_strategy_parameters	Get strategy instance parameters
- [ ] get_all_strategy_class_names	Get names of all available strategy classes
- [ ] load_strategy_setting	Load strategy settings from file
These functions represent the core functionality needed for strategy management, execution, and monitoring across different types of strategy engines (CTA, Portfolio, Spread Trading, etc.).

The main differences between the engines are in their specific implementations and additional specialized functions for handling their respective strategy types. For example:

- [ ] CTA engine has specific functions for stop orders
- [ ] Spread engine has special handling for spread calculations
- [ ] Portfolio engine includes factor-related functionality
- [ ] Nova engine includes data table management


================
Let me analyze the differences between the common function list and the actual implementation in engine.py.

### Functions in engine.py but NOT in common list:

1. **Core Engine Methods**
- `init_engine()`
- `init_datafeed()`
- `register_event()`
- `close()`

2. **Strategy State Management** 
- `save_strategy_setting()`
- `update_strategy_setting()`
- `_validate_requirements()`
- `_init_strategy()` (internal implementation)

3. **Event Processing**
- `process_factor_event()`

4. **Utility Methods**
- `call_strategy_func()`
- `put_strategy_event()`
- `send_email()`
- `get_bar()`
- `get_engine_type()`

### Functions in common list but NOT in engine.py:

1. **Data Loading**
- `load_bars()`
- `load_tick()` 

2. **Contract Info**
- `get_pricetick()` - The common list has this but not implemented in current engine.py
- `get_size()` - The common list has this but not implemented in current engine.py

3. **Process Events**
- `process_tick_event()` - The common list has this but not registered/implemented in current engine.py

4. **Settings Management**
- `get_strategy_class_parameters()` - Listed but not implemented
- `get_strategy_parameters()` - Listed but not implemented
- `get_all_strategy_class_names()` - Listed but not implemented

5. **Strategy Data Management**
- `load_strategy_data()` - Commented out in current implementation
- `sync_strategy_data()` - Commented out in current implementation

The main differences show that the current engine.py:
1. Has more focus on factor event processing
2. Has more utility and helper methods
3. Missing some standard market data processing functions
4. Has contract info methods commented out or not implemented
5. Has data management functions commented out

This suggests the current implementation is more focused on factor-based portfolio strategy rather than general trading strategy management.
"""


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
        """Load strategy classes from module"""
        try:
            # Import strategy module
            self.module = importlib.import_module(strategy_module_name)

            # Get all strategy classes from module
            for name in dir(self.module):
                value = getattr(self.module, name)
                if (isinstance(value, type) and
                        issubclass(value, StrategyTemplate) and
                        value is not StrategyTemplate):
                    self.classes[value.__name__] = value

            self.write_log(f"Successfully loaded {len(self.classes)} strategy classes")
        except Exception as e:
            self.write_log(
                f"Failed to import strategy module from {strategy_module_name}, triggered exception:\n{traceback.format_exc()}")

    def load_strategy_setting(self) -> None:
        """Load strategy settings and create instances"""
        self.settings = load_json(self.setting_filename)  # create new file if not exists

        # Create strategy instances from settings
        for strategy_name, setting in self.settings.items():
            self.add_strategy(
                class_name=setting["class_name"],
                strategy_name=strategy_name,
                vt_symbols=setting["vt_symbols"],
                setting={"settings": setting}  # Only restore settings here
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
        save_json(self.setting_filename, self.settings)
        self.write_log(f"Updated settings for strategy: {strategy.strategy_name}")

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

    # def load_strategy_data(self) -> None:
    #     """Load runtime data for each strategy"""
    #     # fixme: load data from database and datafeed
    #     for strategy_name, strategy in self.strategies.items():
    #         data_filename = f"portfolio_strategy_{strategy_name}_data.json"
    #
    #         if os.path.exists(data_filename):
    #             try:
    #                 # Load and restore strategy data
    #                 data = load_json(data_filename)
    #                 strategy.restore_data(data)
    #                 self.write_log(f"Loaded data for strategy: {strategy_name}")
    #             except Exception as e:
    #                 self.write_log(f"Failed to load data for strategy {strategy_name}: {e}")
    #         else:
    #             # Create new data file for strategy
    #             self.write_log(f"Creating new data file for strategy: {strategy_name}")
    #             save_json(data_filename, strategy.get_data())

    # def sync_strategy_data(self, strategy: StrategyTemplate) -> None:
    #     """Sync strategy runtime data"""
    #     data_filename = f"portfolio_strategy_{strategy.strategy_name}_data.json"
    #     save_json(data_filename, strategy.get_data())
    #     self.write_log(f"Synced data for strategy: {strategy.strategy_name}")

    # --------------------------------
    # Strategy Management
    # --------------------------------
    def add_strategy(self, class_name: str, strategy_name: str, vt_symbols: list,setting: dict) -> None:
        """Add a new strategy instance"""
        if strategy_name in self.strategies:
            self.write_log(f"Creation failed, strategy {strategy_name} already exists",level=ERROR)
            return

        strategy_class: Optional[Type[StrategyTemplate]] = getattr(self.module, class_name)
        if not strategy_class:
            self.write_log(f"Creation failed, strategy class {class_name} not found",level=ERROR)
            return

        if strategy_class.__name__ not in self.classes:
            self.classes[strategy_class.__name__] = strategy_class

        strategy = strategy_class(self, strategy_name, vt_symbols, setting)

        # Validate strategy requirements
        if not self._validate_requirements(strategy_class, vt_symbols):
            return

        # pass validation, add strategy
        self.strategies[strategy_name] = strategy
        self.update_strategy_setting(strategy)

    def edit_strategy(self, strategy_name: str, state: dict) -> None:
        """Edit strategy state"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        strategy.restore_state(state)
        self.update_strategy_setting(strategy)

    def remove_strategy(self, strategy_name: str) -> bool:
        """Remove a strategy instance"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        if strategy.trading:
            self.write_log(f"Strategy {strategy_name} removal failed - please stop first", strategy)
            return False

        self.strategies.pop(strategy_name)
        self.settings.pop(strategy_name, None)
        self.save_settings()
        return True

    def _validate_requirements(self, strategy: StrategyTemplate, vt_symbols: List[str]) -> bool:
        """Validate strategy requirements"""
        if hasattr(strategy, "required_symbols"):
            missing_symbols = set(strategy.required_vt_symbols) - set(vt_symbols)
            if missing_symbols:
                self.write_log(f"Missing required symbols: {missing_symbols}")
                return False

        if hasattr(strategy, "required_factors"):
            pass

        return True

    # --------------------------------
    # Strategy Lifecycle Management
    # --------------------------------
    # def init_strategy(self, strategy_name: str) -> None:
    #     """Initialize a strategy"""
    #     self.init_executor.submit(self._init_strategy, strategy_name)

    def init_strategy(self, strategy_name: str) -> None:
        """Initialize strategy with saved state"""
        self.write_log(FutureWarning("I don't understand that why use multiprocessing for initialization instead of running. maybe _init_strategy will be deprecated, because we don't need parellel processing, use init_all_strategies instead"),level=ERROR)

        strategy: StrategyTemplate = self.strategies[strategy_name]
        if strategy.inited:
            self.write_log(f"{strategy_name} already initialized",level=DEBUG)
            return

        self.write_log(f"Initializing {strategy_name}",level=DEBUG)

        # Subscribe market data
        for vt_symbol in strategy.vt_symbols:
            contract = self.main_engine.get_contract(vt_symbol)
            if contract:
                req = SubscribeRequest(
                    symbol=contract.symbol,
                    exchange=contract.exchange
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
                self.execution_agent.cancel_order(req)
                self.write_log(f"Cancelled order: {req}")

        close_order_reqs = self.call_strategy_func(strategy, strategy.close_all_positions)
        if close_order_reqs:
            for req in close_order_reqs:
                self.execution_agent.send_order(
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

    def init_all_strategies(self) -> None:
        """Initialize all strategies"""
        for strategy_name in self.strategies.keys():
            self.init_strategy(strategy_name)

    def start_all_strategies(self) -> None:
        """Start all strategies"""
        for strategy_name in self.strategies.keys():
            self.start_strategy(strategy_name)

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
                            self.execution_agent.send_order(
                                strategy.strategy_name,
                                req,
                                lock=False,
                                net=False
                            )
                            self.write_log(f"Sent order for {strategy.strategy_name}: {req}")

        except Exception as e:
            self.write_log(f"Error processing factor event: {str(e)}")

    # --------------------------------
    # Order Management
    # --------------------------------
    def send_order(
            self,
            strategy: StrategyTemplate,
            req: OrderRequest,
            lock: bool = False,
            net: bool = False
    ) -> List[str]:
        """Send order via execution agent"""
        pass

    def cancel_order(self, strategy: StrategyTemplate, order: OrderData) -> None:
        """Cancel order via execution agent"""
        pass

    # --------------------------------
    # Utility Methods
    # --------------------------------
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
        log: LogData = LogData(msg=msg, gateway_name=APP_NAME,level=level)
        event: Event = Event(type=EVENT_PORTFOLIO_LOG, data=log)
        self.event_engine.put(event)

    def send_email(self, msg: str, strategy: StrategyTemplate = None) -> None:
        """Send email"""
        subject: str = f"{strategy.strategy_name}" if strategy else "Portfolio Strategy Engine"
        self.main_engine.send_email(subject, msg)

    def get_engine_type(self) -> EngineType:
        """Get engine type"""
        return self.engine_type

    def get_tick(self, vt_symbol) -> TickData:
        """Get tick data"""
        return self.main_engine.get_tick(vt_symbol)

    def get_bar(self, vt_symbol) -> BarData:
        """Get bar data"""
        return self.main_engine.get_bar(vt_symbol)
