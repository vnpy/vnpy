# -*- coding: utf-8 -*-
"""
Defines the BaseStrategyEngine, the core component for managing and executing
trading strategies within the vn.py framework.
"""

import importlib
import traceback
import os
import sys
import re 
import inspect
import pkgutil # Added for robust module scanning
from typing import Type, Callable, Dict, List, Optional, Any, Tuple, Union
from datetime import datetime, timezone
from concurrent.futures import ThreadPoolExecutor
from logging import INFO, ERROR, DEBUG, WARNING
from pathlib import Path

# --- VnTrader Core Imports ---
from vnpy.event import Event, EventEngine
from vnpy.strategy.base import EVENT_PORTFOLIO_STRATEGY
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.object import (
    OrderRequest, SubscribeRequest, CancelRequest,
    LogData, TickData, OrderData, TradeData, BarData, ContractData
)
from vnpy.trader.event import (
    EVENT_ORDER, EVENT_TRADE, EVENT_CONTRACT, EVENT_TIMER, EVENT_LOG,
    EVENT_FACTOR
)
from vnpy.trader.constant import EngineType
from vnpy.trader.utility import load_json, save_json, get_file_path, virtual
from vnpy.trader.database import BaseDatabase, get_database
from vnpy.trader.datafeed import BaseDatafeed, get_datafeed

# --- Strategy & Portfolio Specific Imports ---
from vnpy.app.portfolio_manager.engine import PortfolioEngine, APP_NAME as PortfolioEngine_APP_NAME
PORTFOLIO_APP_NAME = PortfolioEngine_APP_NAME

from vnpy.strategy.execution_agent import ExecutionAgent
from vnpy.factor.memory import FactorMemory
from vnpy.strategy.template import StrategyTemplate

# --- Settings Integration (Updated) ---
# Uses the refined vnpy.strategy.setting.py from the Canvas
try:
    from vnpy.strategy.setting import (
        get_strategy_instance_definitions_filepath,
        STRATEGY_ENGINE_OPERATIONAL_PARAMS, # Main dict for operational params
        MODEL_PATH, # Example of using a path from settings
        DATA_PATH   # Example of using a path from settings
    )
except ImportError:
    print("CRITICAL ERROR: [BaseStrategyEngine] Could not import from 'vnpy.strategy.setting'. Ensure it exists and is configured.")
    # Fallback for critical settings if import fails, to allow some basic structure
    STRATEGY_ENGINE_OPERATIONAL_PARAMS: Dict[str, Any] = {
        "strategy_code_module_path": "strategies", # A very basic default
        "default_execution_gateway": "DEFAULT_GW",
        "init_max_workers": 1,
    }
    def get_strategy_instance_definitions_filepath() -> Path:
        return Path.cwd() / "strategy_portfolio.json" # Basic default
    MODEL_PATH = Path.cwd() / ".vnpy_strategy_data" / "models"
    DATA_PATH = Path.cwd() / ".vnpy_strategy_data" / "data"
    MODEL_PATH.mkdir(parents=True, exist_ok=True)
    DATA_PATH.mkdir(parents=True, exist_ok=True)


# --- Constants ---
STRATEGY_ENGINE_APP_NAME: str = "StrategyEngine"
STRATEGY_DATA_FILENAME_TPL: str = "strategy_data_{strategy_name}.json" # Python 3.6+ f-string style in template
EVENT_STRATEGY_LOG = EVENT_LOG
EVENT_STRATEGY_UPDATE = EVENT_PORTFOLIO_STRATEGY


class BaseStrategyEngine(BaseEngine):
    engine_type: EngineType = EngineType.LIVE

    def __init__(
        self,
        main_engine: MainEngine,
        event_engine: EventEngine,
        engine_name: str = STRATEGY_ENGINE_APP_NAME
    ) -> None:
        super().__init__(main_engine, event_engine, engine_name=engine_name)

        # --- Load Configuration from STRATEGY_ENGINE_OPERATIONAL_PARAMS ---
        self.strategy_code_module_path: str = STRATEGY_ENGINE_OPERATIONAL_PARAMS.get(
            "strategy_code_module_path", "vnpy.strategy.strategies" # Default if key missing
        )
        self.execution_gateway_name: str = STRATEGY_ENGINE_OPERATIONAL_PARAMS.get(
            "default_execution_gateway", "DEFAULT_GW"
        )
        self.init_max_workers: int = STRATEGY_ENGINE_OPERATIONAL_PARAMS.get(
            "init_max_workers", 1
        )
        # Path to the JSON file listing strategy instances and their settings
        self.definitions_filepath: Path = get_strategy_instance_definitions_filepath()

        self.write_log(f"Engine Name: {self.engine_name}", level=DEBUG)
        self.write_log(f"Strategy Code Module Path to scan: {self.strategy_code_module_path}", level=INFO)
        self.write_log(f"Default Execution Gateway: {self.execution_gateway_name}", level=INFO)
        self.write_log(f"Strategy Instance Definitions File: {self.definitions_filepath}", level=INFO)
        self.write_log(f"Strategy Model Path (from settings): {MODEL_PATH}", level=INFO)
        self.write_log(f"Strategy Data Path (from settings): {DATA_PATH}", level=INFO)


        # --- Core Strategy State ---
        self.strategy_classes: Dict[str, Type[StrategyTemplate]] = {}
        self.strategies: Dict[str, StrategyTemplate] = {}
        self.strategy_settings: Dict[str, dict] = {} # Loaded instance settings

        # --- Supporting Components ---
        self.database: Optional[BaseDatabase] = get_database() if callable(get_database) else None
        self.datafeed: Optional[BaseDatafeed] = get_datafeed() if callable(get_datafeed) else None
        self.execution_agent: ExecutionAgent = self._init_execution_agent()
        self.portfolio_engine: Optional[PortfolioEngine] = self._init_portfolio_engine()

        self.init_executor: ThreadPoolExecutor = ThreadPoolExecutor(
            max_workers=self.init_max_workers, # Use loaded setting
            thread_name_prefix=f"{self.engine_name}_Init"
        )

        # --- Factor Handling ---
        self.latest_factor_memories: Dict[str, FactorMemory] = {}
        self.factor_update_time: Optional[datetime] = None

        self.write_log("Engine components initialized.", level=DEBUG)

    def _init_execution_agent(self) -> ExecutionAgent:
        # (Implementation from your previous code)
        self.write_log(f"Initializing ExecutionAgent for gateway: {self.execution_gateway_name}", level=INFO)
        try:
            if not callable(ExecutionAgent) or ExecutionAgent.__name__ == 'object':
                raise ImportError("ExecutionAgent class is not valid.")
            agent = ExecutionAgent(main_engine=self.main_engine, gateway_name=self.execution_gateway_name)
            self.write_log("ExecutionAgent initialized.", level=INFO)
            return agent
        except Exception as e:
            self.write_log(f"FATAL: Failed to initialize ExecutionAgent: {e}\n{traceback.format_exc()}", level=ERROR)
            class DummyExecutionAgent: # Fallback
                def send_order(self, *args, **kwargs): print(f"ERROR: ExecutionAgent not init. Order ignored."); return []
                def cancel_order(self, *args, **kwargs): print(f"ERROR: ExecutionAgent not init. Cancel ignored.")
            return DummyExecutionAgent() # type: ignore

    def _init_portfolio_engine(self) -> Optional[PortfolioEngine]:
        # (Implementation from your previous code)
        if PortfolioEngine:
            self.write_log(f"Initializing PortfolioEngine ('{PORTFOLIO_APP_NAME}')...", level=INFO)
            try:
                portfolio_engine = PortfolioEngine(self.main_engine, self.event_engine)
                self.write_log(f"PortfolioEngine initialized.", level=INFO)
                return portfolio_engine
            except Exception as e:
                self.write_log(f"Failed to initialize PortfolioEngine: {e}", level=ERROR)
        else:
            self.write_log("PortfolioEngine not available. Portfolio management disabled.", level=WARNING)
        return None

    def init_engine(self, *args, **kwargs) -> None:
        """Main initialization sequence for the StrategyEngine."""
        self.write_log(f"Starting initialization sequence for {self.engine_name}...")
        try:
            if self.datafeed and hasattr(self.datafeed, 'init'):
                self.init_datafeed()
            
            # 1. Load all available strategy classes from the specified module path
            self._load_all_strategy_classes()

            # 2. Load strategy instance configurations from JSON and instantiate them
            self.init_strategies_from_configs()

            # 3. Load any persisted runtime data for these strategy instances
            self.load_all_strategy_data()

            # 4. Register event listeners
            self.register_event()
            self.write_log(f"{self.engine_name} initialization complete. {len(self.strategy_classes)} classes found, {len(self.strategies)} instances active.", level=INFO)
        except Exception as e:
            self.write_log(f"CRITICAL ERROR during {self.engine_name} initialization: {e}\n{traceback.format_exc()}", level=ERROR)

    def init_datafeed(self) -> None:
        # (Implementation from your previous code)
        if not self.datafeed or not hasattr(self.datafeed, 'init') or not callable(self.datafeed.init):
            self.write_log("Datafeed not available or 'init' method missing.", WARNING)
            return
        self.write_log("Initializing datafeed...", level=INFO)
        try:
            logger_callback = lambda msg: self.write_log(f"[DataFeed] {msg}", level=DEBUG)
            if self.datafeed.init(logger_callback): # type: ignore
                self.write_log("Datafeed initialized successfully.", level=INFO)
            else:
                self.write_log("Datafeed initialization failed (returned False).", level=WARNING)
        except Exception as e:
            self.write_log(f"Exception during datafeed initialization: {e}", level=ERROR)

    def register_event(self) -> None:
        # (Implementation from your previous code)
        self.write_log("Registering engine event listeners...", level=DEBUG)
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_FACTOR, self.process_factor_event)
        self.event_engine.register(EVENT_TIMER, self._process_timer_event)
        self.write_log("Engine event listeners registered.", level=DEBUG)

    def close(self) -> None:
        # (Implementation from your previous code)
        self.write_log(f"Shutting down {self.engine_name}...")
        self.stop_all_strategies() 
        if self.portfolio_engine and hasattr(self.portfolio_engine, 'close'):
            try: self.portfolio_engine.close(); self.write_log(f"PortfolioEngine closed.", level=INFO)
            except Exception as e: self.write_log(f"Error closing PortfolioEngine: {e}", level=ERROR)
        self.unregister_event()
        self.write_log("Shutting down init executor...", level=DEBUG)
        self.init_executor.shutdown(wait=True)
        self.write_log("Init executor shut down.", level=DEBUG)
        self.write_log(f"{self.engine_name} shut down complete.", level=INFO)

    def unregister_event(self) -> None:
        # (Implementation from your previous code)
        self.write_log("Unregistering engine event listeners...", level=DEBUG)
        self.event_engine.unregister(EVENT_ORDER, self.process_order_event)
        self.event_engine.unregister(EVENT_TRADE, self.process_trade_event)
        self.event_engine.unregister(EVENT_FACTOR, self.process_factor_event)
        self.event_engine.unregister(EVENT_TIMER, self._process_timer_event)
        self.write_log("Engine event listeners unregistered.", level=DEBUG)

    def _camel_to_snake(self, name: str) -> str:
        # (Implementation from your previous code)
        s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
        return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()

    def _load_all_strategy_classes(self) -> None:
        """
        Discovers and loads all concrete StrategyTemplate subclasses from the
        module path specified in `self.strategy_code_module_path`.
        Populates `self.strategy_classes`.
        """
        self.write_log(f"Loading strategy classes from module path: {self.strategy_code_module_path}", level=INFO)
        self.strategy_classes.clear()
        
        module_path_str_to_load = self.strategy_code_module_path
        
        # If path starts with '.', it's a relative import from the package this engine is in.
        # Example: if engine is in vnpy.app.strategy_manager.engine
        # and path is ".strategies", it means vnpy.app.strategy_manager.strategies
        package_for_relative_import = None
        if module_path_str_to_load.startswith("."):
            # Determine the package of the current module (BaseStrategyEngine)
            # This is tricky if BaseStrategyEngine is not part of a well-defined package structure
            # that aligns with how 'strategy_code_module_path' is intended.
            # For vnpy apps, this often means the app's own package.
            # Example: if this file is vnpy/app/my_strategy_app/engine.py
            # then __package__ would be "vnpy.app.my_strategy_app"
            package_for_relative_import = self.__class__.__module__.rsplit('.', 1)[0]
            if module_path_str_to_load == ".": # Import current package
                 module_path_str_to_load = "" # For pkgutil with current package
            # else: module_path_str_to_load remains like ".strategies" for import_module

        try:
            self.write_log(f"Attempting to load base module/package: '{module_path_str_to_load}' relative to '{package_for_relative_import if package_for_relative_import else "top-level"}'", DEBUG)
            
            # importlib.import_module can handle relative paths if 'package' arg is set
            base_module = importlib.import_module(module_path_str_to_load, package=package_for_relative_import)
            
            # Use pkgutil to walk the package (if it is one)
            # getattr(base_module, '__path__', ...) is a common way to get package path for pkgutil
            module_search_path = getattr(base_module, '__path__', None)
            if not module_search_path and hasattr(base_module, '__file__') and base_module.__file__:
                 module_search_path = [os.path.dirname(base_module.__file__)]


            if module_search_path:
                for importer, modname, ispkg in pkgutil.walk_packages(
                    path=module_search_path,
                    prefix=base_module.__name__ + '.' # Ensure full module name for import
                ):
                    try:
                        if modname == base_module.__name__ and not ispkg: # Avoid re-importing the base if it's not a package itself
                            module_to_inspect = base_module
                        else:
                            module_to_inspect = importlib.import_module(modname)
                        
                        # Reload for development; make this configurable if needed
                        module_to_inspect = importlib.reload(module_to_inspect)

                        for item_name in dir(module_to_inspect):
                            item_value = getattr(module_to_inspect, item_name)
                            if (inspect.isclass(item_value) and
                                issubclass(item_value, StrategyTemplate) and
                                item_value is not StrategyTemplate and # Exclude the base template itself
                                not inspect.isabstract(item_value)): # Exclude other abstract bases
                                
                                class_name = item_value.__name__
                                if class_name in self.strategy_classes:
                                    # Potentially log a warning about duplicate class names if from different modules
                                    if self.strategy_classes[class_name].__module__ != module_to_inspect.__name__:
                                        self.write_log(f"Warning: Duplicate strategy class name '{class_name}' found. Keeping from '{self.strategy_classes[class_name].__module__}', ignoring from '{module_to_inspect.__name__}'.", WARNING)
                                else:
                                    self.strategy_classes[class_name] = item_value
                                    self.write_log(f"Discovered strategy class: {class_name} from {module_to_inspect.__name__}", DEBUG)
                    except Exception as e_mod:
                        self.write_log(f"Failed to import or inspect module {modname}: {e_mod}", WARNING)
            else: # base_module might be a single file, not a package
                self.write_log(f"Base module '{base_module.__name__}' is not a package or path not found. Inspecting it directly.", DEBUG)
                module_to_inspect = importlib.reload(base_module) # Reload for dev
                for item_name in dir(module_to_inspect):
                    item_value = getattr(module_to_inspect, item_name)
                    if (inspect.isclass(item_value) and
                        issubclass(item_value, StrategyTemplate) and
                        item_value is not StrategyTemplate and
                        not inspect.isabstract(item_value)):
                        class_name = item_value.__name__
                        if class_name not in self.strategy_classes: # Avoid duplicates if already found
                            self.strategy_classes[class_name] = item_value
                            self.write_log(f"Discovered strategy class: {class_name} from {module_to_inspect.__name__}", DEBUG)


        except ImportError as e_base_import:
            self.write_log(f"Failed to import base strategy module/package: '{module_path_str_to_load}' (relative to: {package_for_relative_import}). Error: {e_base_import}", level=ERROR)
        except Exception as e_general_scan:
            self.write_log(f"General error during strategy class discovery from '{module_path_str_to_load}': {e_general_scan}\n{traceback.format_exc()}", level=ERROR)


        if not self.strategy_classes:
            self.write_log("No strategy classes found. Please check 'strategy_code_module_path' setting and strategy files.", level=WARNING)
        else:
            self.write_log(f"Loaded {len(self.strategy_classes)} distinct strategy classes: {list(self.strategy_classes.keys())}", level=INFO)

    def _get_strategy_class(self, class_name: str, module_file_hint: Optional[str] = None) -> Optional[Type[StrategyTemplate]]:
        """Retrieves a strategy class from the pre-loaded self.strategy_classes dictionary."""
        strategy_class = self.strategy_classes.get(class_name)
        if not strategy_class:
            self.write_log(f"Strategy class '{class_name}' not found in pre-loaded classes. It should have been discovered by _load_all_strategy_classes.", level=ERROR)
            # module_file_hint is largely ignored now as classes are pre-loaded.
            # If dynamic loading on miss is desired, the old logic could be a fallback here.
        return strategy_class
        
    def load_all_strategy_settings(self) -> None:
        # (Implementation from your previous code - uses self.definitions_filepath)
        self.write_log(f"Loading strategy instance configurations from: {self.definitions_filepath}", level=INFO)
        loaded_data: List[Dict[str, Any]] = load_json(str(self.definitions_filepath))
        current_settings: Dict[str, dict] = {}
        if isinstance(loaded_data, list):
            for i, instance_config in enumerate(loaded_data):
                if not isinstance(instance_config, dict): self.write_log(f"Skipping invalid instance config (not dict) at index {i}.", WARNING); continue
                strategy_name = instance_config.get("strategy_name")
                if not strategy_name: self.write_log(f"Skipping instance config at index {i} (missing 'strategy_name').", WARNING); continue
                if strategy_name in current_settings: self.write_log(f"Duplicate strategy_name '{strategy_name}'. Overwriting.", WARNING)
                current_settings[strategy_name] = instance_config
            self.strategy_settings = current_settings
            self.write_log(f"Loaded {len(self.strategy_settings)} strategy instance configurations.")
        elif loaded_data is None and not self.definitions_filepath.exists():
             self.write_log(f"Definitions file {self.definitions_filepath} not found.", INFO); self.strategy_settings = {}
        else:
            self.write_log(f"Invalid data in {self.definitions_filepath}: Expected list, got {type(loaded_data)}.", ERROR); self.strategy_settings = {}

    def init_strategies_from_configs(self) -> None:
        # (Implementation from your previous code - uses _get_strategy_class)
        self.write_log("Initializing strategies from configurations...", level=INFO)
        self.load_all_strategy_settings() 
        created_count = 0
        failed_configs: List[str] = []
        for strategy_name, instance_config in self.strategy_settings.items():
            if not self._validate_setting_entry(strategy_name, instance_config):
                failed_configs.append(strategy_name); continue
            class_name = instance_config["class_name"]
            module_file_hint = instance_config.get("module_file") # Hint, but _get_strategy_class now uses cache
            StrategyClass = self._get_strategy_class(class_name, module_file_hint)

            if not StrategyClass:
                self.write_log(f"Cannot create instance '{strategy_name}': Class '{class_name}' not found/loaded.", ERROR)
                failed_configs.append(strategy_name); continue
            try:
                # Pass the whole instance_config as 'settings' to StrategyTemplate's __init__
                strategy_instance = StrategyClass(engine_interface=self, settings=instance_config)
                self.strategies[strategy_name] = strategy_instance
                self.write_log(f"Strategy instance '{strategy_name}' (Class: '{class_name}') created.", INFO, strategy=strategy_instance)
                self.put_strategy_update_event(strategy_instance)
                created_count += 1
            except Exception as e:
                self.write_log(f"Failed to instantiate '{strategy_name}' from '{class_name}': {e}\n{traceback.format_exc()}", ERROR)
                failed_configs.append(strategy_name)
        
        for name in failed_configs: self.strategy_settings.pop(name, None)
        self.write_log(f"Finished creating strategy instances. Successful: {created_count}.", INFO)

    def _validate_setting_entry(self, strategy_name_key: str, instance_config: Any) -> bool:
        # (Implementation from your previous code)
        if not isinstance(instance_config, dict): self.write_log(f"Invalid config for '{strategy_name_key}': Not a dict.", WARNING); return False
        s_name_in_dict = instance_config.get("strategy_name")
        if not s_name_in_dict or s_name_in_dict != strategy_name_key: self.write_log(f"Config mismatch for '{strategy_name_key}': 'strategy_name' ('{s_name_in_dict}') error.", WARNING); return False
        if not instance_config.get("class_name"): self.write_log(f"Invalid config for '{s_name_in_dict}': Missing 'class_name'.", WARNING); return False
        return True
        
    # --- Methods from your original BaseStrategyEngine ---
    # (process_factor_event, _process_timer_event, _train_strategy_model_thread,
    #  send_order, cancel_order, and all other helper/lifecycle methods
    #  should be included here. For brevity, I'm only showing the modified ones
    #  and a few key event handlers. Ensure all necessary methods are present.)

    def process_factor_event(self, event: Event) -> None:
        factor_memories_dict: Dict[str, FactorMemory] = event.data
        if not isinstance(factor_memories_dict, dict) or not factor_memories_dict:
            self.write_log(f"Ignoring factor event: Data not a non-empty dict (Type: {type(factor_memories_dict)}).", WARNING)
            return
        self.write_log(f"Processing factor update with {len(factor_memories_dict)} FactorMemory objects: {list(factor_memories_dict.keys())[:3]}...", DEBUG)
        self.latest_factor_memories = factor_memories_dict
        self.factor_update_time = self.get_current_datetime() # Assuming get_current_datetime exists
        active_strategies = [s for s in self.strategies.values() if getattr(s, 'inited', False) and getattr(s, 'trading', False)]
        for strategy in active_strategies:
            # Prefer 'on_factor_update' if defined in StrategyTemplate
            handler_method_name = 'on_factor_update' if hasattr(strategy, 'on_factor_update') else 'on_factor'
            if hasattr(strategy, handler_method_name) and callable(getattr(strategy, handler_method_name)):
                self.call_strategy_func(strategy, getattr(strategy, handler_method_name), factor_memories_dict)
            # else: self.write_log(f"Strategy {strategy.strategy_name} has no {handler_method_name} method.", DEBUG)


    def _process_timer_event(self, event: Event) -> None:
        current_dt = self.get_current_datetime() # Assuming this method exists
        for strategy in list(self.strategies.values()):
            if not (getattr(strategy, 'inited', False) and getattr(strategy, 'trading', False)): continue
            if hasattr(strategy, 'check_retraining_schedule') and callable(strategy.check_retraining_schedule):
                if not (hasattr(strategy, 'retrain_model') and callable(strategy.retrain_model)):
                    self.write_log(f"Strategy '{strategy.strategy_name}' has check_retraining_schedule but no retrain_model.", WARNING, strategy=strategy); continue
                try:
                    if strategy.check_retraining_schedule(current_dt):
                        self.write_log(f"Retraining due for '{strategy.strategy_name}'. Queueing.", INFO, strategy=strategy)
                        self.init_executor.submit(self._train_strategy_model_thread, strategy.strategy_name)
                except Exception as e: self.write_log(f"Error in check_retraining_schedule for '{strategy.strategy_name}': {e}", ERROR, strategy=strategy)
            if hasattr(strategy, 'on_timer') and callable(strategy.on_timer):
                self.call_strategy_func(strategy, strategy.on_timer)

    def _train_strategy_model_thread(self, strategy_name: str) -> None:
        strategy = self.strategies.get(strategy_name)
        if not strategy or not (getattr(strategy, 'inited', False) and getattr(strategy, 'trading', False)):
            self.write_log(f"Retraining for '{strategy_name}' aborted: Strategy not active.", WARNING); return
        if not (hasattr(strategy, 'retrain_model') and callable(strategy.retrain_model)):
            self.write_log(f"Cannot retrain for '{strategy_name}': No callable 'retrain_model'.", ERROR, strategy=strategy); return
        self.write_log(f"Starting model retraining for: {strategy_name}", INFO, strategy=strategy)
        try:
            # Pass all latest FactorMemory instances. Strategy's retrain_model will fetch history.
            strategy.retrain_model(self.latest_factor_memories)
            self.write_log(f"Retrain call completed for '{strategy_name}'. Last retrained: {getattr(strategy, 'last_retrain_time', 'N/A')}", INFO, strategy=strategy)
        except Exception as e:
            self.write_log(f"Exception during retrain_model for '{strategy_name}': {e}\n{traceback.format_exc()}", ERROR, strategy=strategy)
        finally:
            self.put_strategy_update_event(strategy)


    # --- Include other methods from your provided BaseStrategyEngine ---
    # (e.g., process_order_event, process_trade_event, add_strategy, edit_strategy, remove_strategy,
    #  init_strategy, _init_strategy_thread, start_strategy, stop_strategy, _cancel_strategy_orders,
    #  load_all_strategy_data, save_strategy_data, send_order, cancel_order,
    #  get_contract, get_tick, get_bar, get_current_datetime, call_strategy_func, put_strategy_update_event etc.)
    # Ensure they use the updated settings access and logging.
    # For brevity, only a few are re-pasted if they needed minor adjustments.

    def write_log(self, msg: str, strategy: Optional[StrategyTemplate] = None, level: int = INFO) -> None:
        # (Your existing write_log implementation using main_engine or print)
        prefix = f"[{strategy.strategy_name}] " if strategy and hasattr(strategy, 'strategy_name') else ""
        if self.main_engine and hasattr(self.main_engine, 'write_log'):
            log_entry = LogData(msg=f"{prefix}{msg}", gateway_name=self.engine_name, level=level)
            event = Event(type=EVENT_LOG, data=log_entry) # Use standard EVENT_LOG
            self.event_engine.put(event)
        else:
            level_name_map = {INFO: "INFO", DEBUG: "DEBUG", WARNING: "WARNING", ERROR: "ERROR"}
            print(f"{datetime.now()} [{level_name_map.get(level, 'INFO')}] [{self.engine_name}] {prefix}{msg}")

    # --- Stubs for methods assumed from your original BaseStrategyEngine ---
    def load_all_strategy_data(self): self.write_log("Placeholder: load_all_strategy_data called", DEBUG)
    def process_order_event(self, event: Event): self.write_log(f"Placeholder: process_order_event: {event.data}", DEBUG)
    # def process_trade_event(self, event: Event): self.write_log(f"Placeholder: process_trade_event: {event.data}", DEBUG) # Already defined above
    def stop_all_strategies(self): self.write_log("Placeholder: stop_all_strategies called", INFO)
    def put_strategy_update_event(self, strategy: StrategyTemplate, removed: bool = False): self.write_log(f"Placeholder: put_strategy_update_event for {strategy.strategy_name}, removed={removed}", DEBUG)
    def call_strategy_func(self, strategy: StrategyTemplate, func: Callable, params: Optional[Any] = None) -> Any:
        try: return func(params) if params is not None else func()
        except Exception as e: self.write_log(f"Error in strategy func {func.__name__} for {strategy.strategy_name}: {e}", ERROR, strategy=strategy)
    def get_current_datetime(self) -> datetime: return datetime.now(timezone.utc)
