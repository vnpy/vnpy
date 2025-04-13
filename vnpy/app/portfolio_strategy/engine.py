import importlib
import traceback
import os
from typing import Type, Callable, Dict, List
from datetime import datetime
from concurrent.futures import ThreadPoolExecutor

from vnpy.event import Event, EventEngine
from vnpy.trader.event import EVENT_FACTOR
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.object import (
    OrderRequest,
    SubscribeRequest,
    LogData,
    TickData,
    OrderData,
    BarData
)
from vnpy.trader.event import (
    EVENT_ORDER,
    EVENT_TRADE
)
from vnpy.trader.utility import load_json, save_json

from vnpy.app.portfolio_strategy.base import (
    APP_NAME,
    EVENT_PORTFOLIO_LOG,
    EVENT_PORTFOLIO_STRATEGY,
    EngineType
)
from .locale import _
from vnpy.app.portfolio_strategy.template import StrategyTemplate
from execution_agent import ExecutionAgent

strategy_module_name = 'vnpy.app.portfolio_strategy.strategies'


class StrategyEngine(BaseEngine):
    """Portfolio Strategy Engine focused on factor processing"""
    
    engine_type: EngineType = EngineType.LIVE
    setting_filename: str = "portfolio_strategy_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """Initialize the strategy engine"""
        super().__init__(main_engine, event_engine, APP_NAME)

        # Core state management
        self.settings: dict[str, dict] = {}  # Strategy settings storage
        self.classes: dict[str, Type[StrategyTemplate]] = {}
        self.strategies: dict[str, StrategyTemplate] = {}
        self.orderid_strategy_map: dict[str, StrategyTemplate] = {}
        
        # Factor data caching 
        self.latest_factors: Dict[str, Dict] = {}
        self.factor_update_time: datetime = datetime.now(tz=datetime.utc)
        
        # Thread and external resources
        self.init_executor: ThreadPoolExecutor = ThreadPoolExecutor(max_workers=1)
        self.vt_tradeids: set[str] = set()
        
        # Configure execution agent
        self.execution_agent = ExecutionAgent(
            main_engine=self.main_engine,
            gateway_name="BINANCE"  # Configurable gateway
        )

    # --------------------------------
    # Engine Core Methods
    # --------------------------------
    def init_engine(self) -> None:
        """Initialize the engine"""
        # Step 1: Load strategy classes
        self.load_strategy_class()
        
        # Step 2: Load strategy settings
        self.load_settings()
        
        # Step 3: Load strategy data
        self.load_strategy_data()
        
        self.register_event()
        self.write_log("Portfolio strategy engine initialized")

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
            self.write_log(f"Failed to import strategy module from {strategy_module_name}, triggered exception:\n{traceback.format_exc()}")

    def load_settings(self) -> None:
        """Load strategy settings and create instances"""
        try:
            # Load setting file
            if not os.path.exists(self.setting_filename):
                self.write_log("Strategy settings file not found, creating new file")
                save_json(self.setting_filename, {})
                return
            
            self.settings = load_json(self.setting_filename)
            
            # Create strategy instances from settings
            for strategy_name, setting in self.settings.items():
                self.add_strategy(
                    class_name=setting["class_name"],
                    strategy_name=strategy_name,
                    vt_symbols=setting["vt_symbols"],
                    state={"settings": setting}  # Only restore settings here
                )
                
        except Exception as e:
            self.write_log(f"Failed to load strategy settings: {e}")
            self.settings = {}

    def load_strategy_data(self) -> None:
        """Load runtime data for each strategy"""
        for strategy_name, strategy in self.strategies.items():
            data_filename = f"portfolio_strategy_{strategy_name}_data.json"
            
            if os.path.exists(data_filename):
                try:
                    # Load and restore strategy data
                    data = load_json(data_filename)
                    strategy.restore_data(data)
                    self.write_log(f"Loaded data for strategy: {strategy_name}")
                except Exception as e:
                    self.write_log(f"Failed to load data for strategy {strategy_name}: {e}")
            else:
                # Create new data file for strategy
                self.write_log(f"Creating new data file for strategy: {strategy_name}")
                save_json(data_filename, strategy.get_data())

    def save_strategy_state(self, strategy_name: str) -> None:
        """Save both settings and data for a strategy"""
        strategy = self.strategies[strategy_name]
        
        # Save settings
        self.update_strategy_setting(strategy)
        
        # Save data
        self.sync_strategy_data(strategy)
        
        self.write_log(f"Saved complete state for strategy: {strategy_name}")

    def update_strategy_setting(self, strategy: StrategyTemplate) -> None:
        """Update single strategy setting"""
        self.settings[strategy.strategy_name] = strategy.get_settings()
        save_json(self.setting_filename, self.settings)
        self.write_log(f"Updated settings for strategy: {strategy.strategy_name}")

    def sync_strategy_data(self, strategy: StrategyTemplate) -> None:
        """Sync strategy runtime data"""
        data_filename = f"portfolio_strategy_{strategy.strategy_name}_data.json"
        save_json(data_filename, strategy.get_data())
        self.write_log(f"Synced data for strategy: {strategy.strategy_name}")

    # --------------------------------
    # Strategy Management
    # --------------------------------
    def add_strategy(self, class_name: str, strategy_name: str, vt_symbols: list, state: dict) -> None:
        """Add a new strategy instance"""
        if strategy_name in self.strategies:
            self.write_log(f"Creation failed, strategy {strategy_name} already exists")
            return

        strategy_class = getattr(self.module, class_name)
        if not strategy_class:
            self.write_log(f"Creation failed, strategy class {class_name} not found")
            return

        # Validate strategy requirements
        if not self._validate_requirements(strategy_class, vt_symbols):
            return
            
        if strategy_class.__name__ not in self.classes:
            self.classes[strategy_class.__name__] = strategy_class
            
        strategy = strategy_class(self, strategy_name, vt_symbols, state)
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

    def _validate_requirements(self, strategy_class: Type[StrategyTemplate], vt_symbols: List[str]) -> bool:
        """Validate strategy requirements"""
        if hasattr(strategy_class, "required_symbols"):
            missing_symbols = set(strategy_class.required_symbols) - set(vt_symbols)
            if missing_symbols:
                self.write_log(f"Missing required symbols: {missing_symbols}")
                return False

        if hasattr(strategy_class, "required_factors"):
            pass

        return True

    # --------------------------------
    # Strategy Lifecycle Management
    # --------------------------------
    def init_strategy(self, strategy_name: str) -> None:
        """Initialize a strategy"""
        self.init_executor.submit(self._init_strategy, strategy_name)

    def _init_strategy(self, strategy_name: str) -> None:
        """Initialize strategy with saved state"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        if strategy.inited:
            self.write_log(f"{strategy_name} already initialized")
            return

        self.write_log(f"Initializing {strategy_name}")
        
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

        if strategy_name in self.settings:
            strategy.restore_state(self.settings[strategy_name].get("state", {}))

        strategy.inited = True

        self.write_log(f"{strategy_name} initialized")

    def start_strategy(self, strategy_name: str) -> None:
        """Start a strategy"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        if not strategy.inited:
            self.write_log(f"Strategy {strategy_name} start failed, please initialize first")
            return
        if strategy.trading:
            self.write_log(f"{strategy_name} already started, do not repeat operation")
            return
        strategy.trading = True

    def stop_strategy(self, strategy_name: str) -> None:
        """Stop running strategy"""
        strategy: StrategyTemplate = self.strategies[strategy_name]
        if not strategy.trading:
            self.write_log(f"Strategy {strategy_name} not running", strategy)
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
                    order_reqs: List[OrderRequest] = self.call_strategy_func(strategy, strategy.on_factor, self.latest_factors)
                    
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
    def call_strategy_func(self, strategy: StrategyTemplate, func: Callable, params: object = None) -> None:
        """Safely call strategy function"""
        try:
            if params:
                func(params)
            else:
                func()
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

    def write_log(self, msg: str, strategy: StrategyTemplate = None) -> None:
        """Write log"""
        if strategy:
            msg: str = f"{strategy.strategy_name}: {msg}"
        log: LogData = LogData(msg=msg, gateway_name=APP_NAME)
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
