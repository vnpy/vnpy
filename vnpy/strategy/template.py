# -*- coding: utf-8 -*-
"""
Provides a base template for portfolio-level trading strategies, designed to
work with the BaseStrategyEngine and optionally the PortfolioEngine.
"""

from abc import ABC, abstractmethod
from datetime import datetime, timezone # Added timezone
from logging import DEBUG, ERROR, INFO, WARNING
from pathlib import Path
import traceback
from typing import TYPE_CHECKING, Callable, List, Optional, Dict, Any, Set, Union, Tuple # Removed duplicate TYPE_CHECKING
from collections import defaultdict
import pandas as pd
import polars as pl
import joblib # For model persistence
# import pickle # joblib is generally preferred for scikit-learn models

# --- VnTrader Imports ---
from vnpy.trader.constant import (
    Interval, Direction, Offset, Exchange, OrderType, EngineType, Status
)
from vnpy.trader.object import (
    BarData, ContractData, TickData, CancelRequest, OrderData, FactorData, OrderRequest, TradeData
)
from vnpy.trader.utility import virtual, round_to # Removed convert_dict_to_dataframe as it's not used here
from vnpy.factor.memory import FactorMemory

# --- Settings and Config Model Imports ---
# Attempt to import MODEL_PATH, DATA_PATH for context or default path construction
try:
    from vnpy.strategy.setting import MODEL_PATH, DATA_PATH
except ImportError:
    print("Warning: [StrategyTemplate] Could not import MODEL_PATH or DATA_PATH from vnpy.strategy.setting. Strategies may need absolute paths for models/data.")
    MODEL_PATH = Path("./models") # type: ignore 
    DATA_PATH = Path("./data")   # type: ignore
    MODEL_PATH.mkdir(parents=True, exist_ok=True)
    DATA_PATH.mkdir(parents=True, exist_ok=True)


# Assuming these config models exist in the specified path relative to the template
# For a cleaner structure, these might be defined elsewhere (e.g., vnpy.strategy.config_models)
# or passed as generic dicts and validated by the strategy.
try:
    # If these are part of your strategy app, use relative import:
    # from .config.models.config import ModelConfig 
    # from .config.trading.config import TradingConfig
    # For now, assume they might be globally accessible or defined as stubs if not found
    # This part is highly dependent on your project structure.
    # If they are in, for example, vnpy.strategy.configs:
    # from vnpy.strategy.configs import ModelConfig, TradingConfig

    # Using placeholder stubs if specific config classes are not found.
    # In a real application, these should be properly defined and imported.
    class ModelConfig:
        """Placeholder for strategy's model configuration."""
        def __init__(self, **kwargs):
            for key, value in kwargs.items():
                setattr(self, key, value)
        def __repr__(self):
            return f"ModelConfig({self.__dict__})"

    class TradingConfig:
        """Placeholder for strategy's trading parameters."""
        min_order_volume: float = 1e-8 # Default minimum order volume
        def __init__(self, **kwargs):
            self.min_order_volume = kwargs.get("min_order_volume", 1e-8)
            for key, value in kwargs.items():
                if key == "min_order_volume" and value is None: # Ensure it has a float value
                    continue
                setattr(self, key, value)
        def validate(self): pass # Placeholder
        def __repr__(self):
            return f"TradingConfig({self.__dict__})"

except ImportError:
    print("Warning: [StrategyTemplate] Could not import ModelConfig or TradingConfig. Using dummy classes.")
    class ModelConfig: # type: ignore
        def __init__(self, **kwargs):
            for k, v in kwargs.items():
                setattr(self, k, v)
    class TradingConfig: # type: ignore
        min_order_volume: float = 1e-8
        def __init__(self, **kwargs):
            self.min_order_volume = kwargs.get("min_order_volume", 1e-8)
            for k, v in kwargs.items():
                if k == "min_order_volume" and v is None: # Already handled by getattr default
                    continue
                setattr(self, k, v)
        def validate(self): pass


# Type hint for the engine, resolved during type checking
if TYPE_CHECKING:
    from vnpy.strategy.engine import StrategyEngine # Adjusted import path if engine is in vnpy.strategy.engine


class StrategyTemplate(ABC):
    """
    Abstract base class for portfolio trading strategies.
    """
    author: str = "Unknown"
    # Parameters that are configurable via settings and managed by get_parameters/update_setting
    parameters: List[str] = [
        "vt_symbols", "required_factor_keys",
        "model_config", "trading_config",
        "model_load_path", "model_save_path",
        "retraining_config" # Contains retrain_interval_days, lookback_days etc.
    ]
    # State variables that can be saved/loaded via get_data/load_data
    variables: List[str] = [
        "inited", "trading",
        "latest_factor_update_time_iso", # Store as ISO string for JSON
        "last_retrain_time_iso",       # Store as ISO string
        # "active_order_ids" is handled separately in get_data/load_data
    ]

    required_factor_keys: List[str] = [] # Default empty list
    exchange: Optional[Exchange] = None  # Can be set from contract or settings
    interval: Optional[Interval] = None  # Informational

    def __init__(
            self,
            engine_interface: "StrategyEngine",
            settings: Dict[str, Any], # All config now comes from this single dict
    ) -> None:
        self.strategy_engine: "StrategyEngine" = engine_interface
        
        # --- Extract Core Settings ---
        # strategy_name is crucial and should be in settings (validated by engine)
        self.strategy_name: str = settings.get("strategy_name", "UnnamedStrategy")
        
        # vt_symbols can be updated later via settings
        self.vt_symbols: List[str] = list(settings.get("vt_symbols", []))

        # Factor dependencies
        self.required_factor_keys: List[str] = list(settings.get("required_factor_keys", []))

        # Model persistence paths
        self.model_load_path = self._resolve_model_path(settings.get("model_load_path"))
        self.model_save_path = self._resolve_model_path(settings.get("model_save_path"))

        # Retraining configuration
        self.retraining_config: Dict[str, Any] = settings.get("retraining_config", {})
        self.retrain_interval_days: int = self.retraining_config.get("frequency_days", 30) # Example

        # --- Engine Access ---
        self.get_tick: Callable[[str], Optional[TickData]] = self.strategy_engine.get_tick
        self.get_contract: Callable[[str], Optional[ContractData]] = self.strategy_engine.get_contract

        # --- Configuration Objects ---
        # Initialize from nested dicts within 'settings'
        model_config_dict = settings.get("model_config", {})
        # todo -- fix model and trading config classes to accept dicts
        # todo -- check setting have model and trading config
        self.model_config = ModelConfig(**model_config_dict) if isinstance(model_config_dict, dict) else ModelConfig()

        trading_config_dict = settings.get("trading_config", {})
        self.trading_config = TradingConfig(**trading_config_dict) if isinstance(trading_config_dict, dict) else TradingConfig()
        if hasattr(self.trading_config, 'validate') and callable(self.trading_config.validate):
            try: self.trading_config.validate()
            except Exception as e: self.write_log(f"TradingConfig validation failed: {e}", ERROR)


        # --- Strategy State ---
        self.inited: bool = False
        self.trading: bool = False

        # --- Market Data Cache ---
        self.latest_factor_data: Optional[pl.DataFrame] = None # Stores Polars DataFrame
        self.latest_factor_update_time: Optional[datetime] = None

        # --- Model Related Attributes ---
        self.model: Any = None
        self.last_retrain_time: Optional[datetime] = None # Set after successful retraining or loading metadata

        # --- Order Management ---
        self.active_order_ids: Set[str] = set()

        # --- Portfolio Interaction (Optional) ---
        self.portfolio_result = None
        if self.strategy_engine.portfolio_engine:
            try:
                self.portfolio_result = self.strategy_engine.portfolio_engine.get_portfolio_result(
                    reference=self.strategy_name
                )
            except Exception as e: self.write_log(f"Error linking with PortfolioResult: {e}", ERROR)
        
        # Load model if path is specified
        self.load_model()
        # Runtime data (like last_retrain_time, active_order_ids) is loaded by engine via self.load_data()

        self.write_log(f"Strategy instance '{self.strategy_name}' initialized with settings.", level=DEBUG)

    # --------------------------------
    # Abstract Core Logic Methods (Implement in Subclass)
    # --------------------------------

    @abstractmethod
    def _transform_latest_factors(self, latest_factor_data_map: Dict[str, pl.DataFrame]) -> pl.DataFrame:
        """
        Transforms latest factor data (Polars) into a single Polars DataFrame
        for model prediction (rows=vt_symbol, cols=factor_features).
        """
        pass

    @abstractmethod
    def predict_from_model(self, data: pd.DataFrame) -> Any: # Expects Pandas for sklearn
        """Generates raw predictions from the model using new (Pandas) input data."""
        pass

    @abstractmethod
    def generate_signals_from_prediction(
        self, model_output: Any, symbol_feature_df: pd.DataFrame
    ) -> List[OrderRequest]:
        """Converts raw model output into OrderRequests."""
        pass

    @abstractmethod
    def prepare_training_data(
        self, historical_factor_data_map: Dict[str, pl.DataFrame]
    ) -> Tuple[pd.DataFrame, pd.Series]: # Returns Pandas for sklearn
        """Prepares features (X) and labels (y) for training from historical Polars factor data."""
        pass

    # --------------------------------
    # Lifecycle Methods (Called by Engine)
    # --------------------------------
    @virtual
    def on_init(self) -> None:
        self.write_log("Strategy initializing...")
        self.inited = True
        self.write_log("Strategy initialized.")
        self.put_event()

    @virtual
    def on_start(self) -> None:
        self.write_log("Strategy starting...")
        self.trading = True
        self.write_log("Strategy started.")
        self.put_event()

    @virtual
    def on_stop(self) -> None:
        self.write_log("Strategy stopping...")
        # self.trading is set to False by the engine *before* calling on_stop
        self.active_order_ids.clear() # Clear tracked orders
        self.write_log("Strategy stopped.")
        self.put_event()

    # --------------------------------
    # Event Processing Methods (Called by Engine)
    # --------------------------------

    @virtual
    def on_factor_update(self, factor_memories: Dict[str, FactorMemory]) -> Optional[List[OrderRequest]]:
        """Callback when new factor data is received via FactorMemory instances."""
        if not self.trading or not self.inited:
            return None

        current_dt = self.strategy_engine.get_current_datetime()
        self.latest_factor_update_time = current_dt
        self.write_log(f"Processing factor update event for {len(factor_memories)} factors at {current_dt}", level=DEBUG)

        latest_polars_data_map: Dict[str, pl.DataFrame] = {}
        for factor_key in self.required_factor_keys:
            factor_memory = factor_memories.get(factor_key)
            if not factor_memory:
                self.write_log(f"Required factor key '{factor_key}' not found in received factor_memories.", WARNING); return None
            
            latest_rows_df = factor_memory.get_latest_rows(N=1) # Expecting Polars DataFrame
            if latest_rows_df is None or latest_rows_df.is_empty():
                self.write_log(f"Factor '{factor_key}' provided empty data for latest row. Skipping prediction cycle.", WARNING); return None
            latest_polars_data_map[factor_key] = latest_rows_df
        
        if not latest_polars_data_map:
            self.write_log("No required factor data available after fetching latest rows.", WARNING); return None

        try:
            if self.model is None: self.write_log("Model not loaded. Cannot predict.", WARNING); return None

            transformed_pl_df = self._transform_latest_factors(latest_polars_data_map)
            if transformed_pl_df is None or transformed_pl_df.is_empty():
                self.write_log("Factor transformation resulted in empty data.", WARNING); return None
            
            self.latest_factor_data = transformed_pl_df # Cache the Polars DF

            # Convert to Pandas for scikit-learn, assuming 'vt_symbol' is a column to become index
            if 'vt_symbol' not in transformed_pl_df.columns:
                # _transform_latest_factors should ensure vt_symbol is present if needed for indexing
                self.write_log("Transformed Polars DataFrame missing 'vt_symbol' column for Pandas index.", ERROR); return None
            
            # It's cleaner if _transform_latest_factors returns a DF with vt_symbol as a regular column,
            # and conversion to pandas with set_index happens just before predict_from_model.
            try:
                pandas_features_df = transformed_pl_df.to_pandas().set_index('vt_symbol')
            except Exception as e_pd:
                 self.write_log(f"Error converting transformed Polars DF to Pandas or setting index: {e_pd}", ERROR); return None

            if pandas_features_df.empty:
                self.write_log("Pandas DataFrame for model input is empty.", DEBUG); return None

            model_prediction_output = self.predict_from_model(pandas_features_df)
            if model_prediction_output is None:
                self.write_log("Prediction from model returned None.", WARNING); return None

            order_reqs = self.generate_signals_from_prediction(model_prediction_output, pandas_features_df)
            if order_reqs: self.write_log(f"Generated {len(order_reqs)} order requests.", DEBUG)
            return order_reqs
        except Exception as e:
            self.write_log(f"Error during on_factor_update pipeline: {e}\n{traceback.format_exc()}", ERROR)
            return None

    @virtual
    def on_order(self, order: OrderData) -> None:
        self.write_log(f"Order Update: {order.vt_orderid} Status: {order.status} Filled: {order.traded}/{order.volume}", DEBUG)
        if order.is_active(): self.active_order_ids.add(order.vt_orderid)
        else: self.active_order_ids.discard(order.vt_orderid)

    @virtual
    def on_trade(self, trade: TradeData) -> None:
        self.write_log(f"Trade Update: {trade.vt_orderid} Dir: {trade.direction} Px: {trade.price} Vol: {trade.volume}", DEBUG)

    @virtual
    def on_timer(self) -> None:
        """Optional timer callback, can be used for periodic checks by the strategy."""
        # self.write_log(f"on_timer called at {self.get_current_datetime()}", level=DEBUG) # Removed: Can be too noisy
        # Example: Check if model needs reloading if file changed, or other periodic tasks
        # self.check_and_reload_model_if_updated()


    # --------------------------------
    # Model Persistence and Retraining
    # --------------------------------
    def load_model(self) -> None:
        if not self.model_load_path:
            self.write_log("No model_load_path specified. Skipping model loading.", DEBUG); return
        load_path = Path(self.model_load_path)
        if not load_path.is_absolute(): load_path = MODEL_PATH / self.model_load_path # Use global MODEL_PATH as base
        
        self.write_log(f"Attempting to load model from: {load_path}", INFO)
        if not load_path.exists():
            self.write_log(f"Model file not found at {load_path}. No model loaded.", WARNING); return
        try:
            with open(load_path, 'rb') as f: self.model = joblib.load(f)
            self.write_log(f"Model loaded successfully from {load_path}", INFO)
            # Optionally, load last_retrain_time if saved alongside model
            # metadata_path = load_path.with_suffix(".meta.json")
            # if metadata_path.exists(): ... self.last_retrain_time = ...
        except Exception as e:
            self.write_log(f"Failed to load model from {load_path}: {e}\n{traceback.format_exc()}", ERROR)

    def save_model(self) -> None:
        if not self.model_save_path or self.model is None:
            self.write_log(f"Skipping model saving: No save path ('{self.model_save_path}') or model is None.", DEBUG); return
        save_path = Path(self.model_save_path)
        if not save_path.is_absolute(): save_path = MODEL_PATH / self.model_save_path # Use global MODEL_PATH as base
        
        self.write_log(f"Attempting to save model to: {save_path}", INFO)
        try:
            save_path.parent.mkdir(parents=True, exist_ok=True) # Ensure directory exists
            with open(save_path, 'wb') as f: joblib.dump(self.model, f)
            self.write_log(f"Model saved successfully to {save_path}", INFO)
            # Optionally, save metadata like last_retrain_time
            # metadata_path = save_path.with_suffix(".meta.json")
            # with open(metadata_path, "w") as f_meta: json.dump({"last_retrain_time": self.last_retrain_time.isoformat()}, f_meta)
        except Exception as e:
            self.write_log(f"Failed to save model to {save_path}: {e}\n{traceback.format_exc()}", ERROR)

    def _fetch_historical_training_factors(self, factor_memories: Dict[str, FactorMemory]) -> Dict[str, pl.DataFrame]:
        historical_data_map: Dict[str, pl.DataFrame] = {}
        for key in self.required_factor_keys:
            fm = factor_memories.get(key)
            if fm: data = fm.get_data(); historical_data_map[key] = data if data is not None and not data.is_empty() else pl.DataFrame()
            else: self.write_log(f"FactorMemory not found for '{key}' during historical fetch.", WARNING)
        return historical_data_map

    @virtual
    def retrain_model(self, factor_memories_for_training: Dict[str, FactorMemory]) -> None:
        """Orchestrates model retraining using provided FactorMemory instances for historical data."""
        self.write_log("Starting model retraining process...", INFO)
        try:
            historical_polars_map = self._fetch_historical_training_factors(factor_memories_for_training)
            if not historical_polars_map or all(df.is_empty() for df in historical_polars_map.values()):
                self.write_log("No historical factor data fetched or all empty. Aborting retraining.", WARNING); return

            features_df, labels_series = self.prepare_training_data(historical_polars_map) # Returns Pandas
            if features_df is None or features_df.empty or labels_series is None or labels_series.empty:
                self.write_log("Training data prep resulted in empty features/labels. Aborting.", WARNING); return
            
            if self.model is None: self.write_log("self.model is None. Cannot fit. Ensure model is initialized.", ERROR); return
            if not hasattr(self.model, 'fit'): self.write_log("self.model has no 'fit' method.", ERROR); return

            self.write_log(f"Training model with {features_df.shape[0]} samples, {features_df.shape[1]} features.", INFO)
            self.model.fit(features_df, labels_series)
            self.write_log("Model training completed.", INFO)
            self.save_model()
            self.last_retrain_time = self.get_current_datetime()
            self.write_log(f"Model retraining finished. Last retrain: {self.last_retrain_time}", INFO)
            self.put_event()
        except Exception as e:
            self.write_log(f"Error during model retraining: {e}\n{traceback.format_exc()}", ERROR)

    def check_retraining_schedule(self, current_datetime: datetime) -> bool:
        # Ensure self.retrain_interval_days is correctly parsed from self.retraining_config
        self.retrain_interval_days = self.retraining_config.get("frequency_days", 30)

        if self.model is None and not self.model_load_path:
            self.write_log("Retraining check: Initial training required (no model, no load path).", INFO); return True
        if self.last_retrain_time is None:
            self.write_log("Retraining check: Last retrain time is None. Retraining might be due based on interval.", INFO)
            # If a model was loaded, we might want to wait for the first interval to pass.
            # Or, if no last_retrain_time, assume it's due if interval is positive.
            return self.retrain_interval_days > 0 # Retrain if interval is set and no prior retrain by this instance
            
        if self.retrain_interval_days <= 0: return False # Disabled
        days_since = (current_datetime.replace(tzinfo=None) - self.last_retrain_time.replace(tzinfo=None)).days # Naive comparison
        if days_since >= self.retrain_interval_days:
            self.write_log(f"Retraining check: {days_since} days since last retrain (interval: {self.retrain_interval_days}). Required.", INFO); return True
        return False

    # --------------------------------
    # Portfolio and Order Generation
    # --------------------------------
    def close_all_positions(self) -> List[OrderRequest]:
        self.write_log("Generating orders to close all positions...", INFO); reqs = []
        min_vol = getattr(self.trading_config, 'min_order_volume', 1e-8)
        for sym in self.vt_symbols:
            pos = self.strategy_engine.get_portfolio_position(self.strategy_name, sym)
            if abs(pos) > min_vol:
                ct = self.get_contract(sym)
                if not ct: self.write_log(f"Cannot close for {sym}: Contract not found.", WARNING); continue
                direction = Direction.SHORT if pos > 0 else Direction.LONG
                vol = round_to(abs(pos), getattr(ct, 'volumetick', 1e-8))
                if vol < getattr(ct, 'min_volume', 1e-8): continue
                reqs.append(OrderRequest(symbol=ct.symbol,exchange=ct.exchange,direction=direction,offset=Offset.NONE,type=OrderType.MARKET,price=0,volume=vol,reference=self.strategy_name))
        return reqs


    def get_portfolio_state(self) -> Optional[dict]:
        if self.portfolio_result and hasattr(self.portfolio_result, 'get_data'): return self.portfolio_result.get_data()
        return None

    # --------------------------------
    # Order Management Actions (send_order, cancel_order, etc.)
    # --------------------------------
    def send_order(self, vt_symbol: str, direction: Direction, order_type: OrderType, price: float, volume: float, offset: Offset = Offset.NONE, lock: bool = False, net: bool = False) -> List[str]:
        if not self.trading:
            self.write_log("Order rejected: Not trading.", WARNING)
            return []
        
        ct = self.get_contract(vt_symbol)
        if not ct:
            self.write_log(f"Order rejected: Contract not found for {vt_symbol}.", ERROR)
            return []
        
        r_price = round_to(price, ct.pricetick or 1e-8)
        r_vol = round_to(volume, ct.volumetick or 1e-8)
        
        if r_vol < (ct.min_volume or 1e-8):
            self.write_log(f"Order rejected: Vol {volume} < min_vol {ct.min_volume} for {vt_symbol}", WARNING)
            return []
            
        req = OrderRequest(
            symbol=ct.symbol,
            exchange=ct.exchange,
            direction=direction,
            offset=offset,
            type=order_type,
            price=r_price,
            volume=r_vol,
            reference=self.strategy_name
        )
        return self.strategy_engine.send_order(strategy_name=self.strategy_name, req=req, lock=lock, net=net)

    def cancel_order(self, vt_orderid: str) -> None:
        if not self.trading: self.write_log("Cancel ignored: Not trading.", WARNING); return
        if vt_orderid not in self.active_order_ids: self.write_log(f"Cancel ignored: Order {vt_orderid} not in active set.", WARNING); # return # Or allow general cancel
        order=self.strategy_engine.main_engine.get_order(vt_orderid)
        if order:
            if order.is_active(): self.strategy_engine.cancel_order(order)
            else: self.write_log(f"Cancel ignored: Order {vt_orderid} inactive (Status: {order.status}).", DEBUG); self.active_order_ids.discard(vt_orderid)
        else: self.write_log(f"Cancel failed: Order {vt_orderid} not found in MainEngine.", WARNING); self.active_order_ids.discard(vt_orderid)

    def cancel_all_active_orders(self) -> None:
        if not self.trading: self.write_log("Cancel all ignored: Not trading.", WARNING); return
        if not self.active_order_ids: self.write_log("No active orders to cancel.", DEBUG); return
        self.write_log(f"Cancelling all {len(self.active_order_ids)} active orders...", INFO)
        for oid in list(self.active_order_ids): self.cancel_order(oid)

    def get_active_order_ids(self) -> List[str]: return list(self.active_order_ids)

    # --------------------------------
    # State Management (Persistence)
    # --------------------------------
    def get_parameters(self) -> dict:
        params = {"strategy_name": self.strategy_name, "class_name": self.__class__.__name__} # Core identifiers
        for name in self.parameters: # self.parameters is list of attribute names
            value = getattr(self, name, None)
            if isinstance(value, (ModelConfig, TradingConfig)): params[name] = value.__dict__
            elif isinstance(value, list): params[name] = list(value) # Ensure lists are copied if mutable
            elif isinstance(value, set): params[name] = list(value) # For JSON serializability
            elif isinstance(value, Path): params[name] = str(value) # Paths as strings
            else: params[name] = value
        # self.vt_symbols and self.required_factor_keys are initialized as lists in __init__.
        # If they could be None on self, a more robust getattr(self, name, []) would be needed.
        # Current init ensures they are lists.
        return params

    def get_settings(self) -> dict: return self.get_parameters() # Alias for settings compatibility

    def get_data(self) -> dict: # For runtime state saving
        data = {"active_order_ids": list(self.active_order_ids)}
        for name in self.variables: # self.variables lists attributes to save
            value = getattr(self, name, None)
            if isinstance(value, datetime): data[name] = value.isoformat()
            elif name.endswith("_iso") and isinstance(value, str): data[name] = value # Already iso
            elif isinstance(value, (bool,int,float,str,list,dict,type(None))): data[name] = value
        # Ensure specific time fields are correctly formatted if not in self.variables
        if self.latest_factor_update_time and "latest_factor_update_time_iso" not in data: data["latest_factor_update_time_iso"] = self.latest_factor_update_time.isoformat()
        if self.last_retrain_time and "last_retrain_time_iso" not in data: data["last_retrain_time_iso"] = self.last_retrain_time.isoformat()
        return data

    def load_data(self, data: dict) -> None: # For runtime state loading
        self.write_log("Loading runtime data into strategy...", DEBUG)
        self.active_order_ids = set(data.get("active_order_ids", []))
        
        time_fields_map = { # Maps data key to attribute name
            "latest_factor_update_time_iso": "latest_factor_update_time",
            "last_retrain_time_iso": "last_retrain_time"
        }
        for data_key, attr_name in time_fields_map.items():
            time_str = data.get(data_key)
            if time_str:
                try: setattr(self, attr_name, datetime.fromisoformat(time_str).replace(tzinfo=timezone.utc if "Z" in time_str or "+" in time_str else None))
                except: self.write_log(f"Could not parse saved time for {attr_name}: {time_str}", WARNING)

        for name in self.variables: # Load other variables
            if name in data and name not in time_fields_map.values(): # Avoid re-processing time fields
                setattr(self, name, data[name])
        self.write_log("Runtime data loaded.", DEBUG)


    def update_setting(self, settings: dict) -> None:
        """Update strategy parameters from a dictionary (typically from engine)."""
        self.write_log(f"Updating strategy settings for '{self.strategy_name}'...", DEBUG)

        # Update core attributes if present in settings
        self.vt_symbols = list(settings.get("vt_symbols", self.vt_symbols))
        self.required_factor_keys = list(settings.get("required_factor_keys", self.required_factor_keys))

        # Use the helper for model paths, allowing current value as default if not in new settings
        mlp_setting = settings.get("model_load_path") 
        if mlp_setting is not None or "model_load_path" in settings: # Check if key was explicitly in settings (even if None)
            self.model_load_path = self._resolve_model_path(mlp_setting)
        # Else, self.model_load_path remains unchanged if key not in settings at all.

        msp_setting = settings.get("model_save_path")
        if msp_setting is not None or "model_save_path" in settings:
            self.model_save_path = self._resolve_model_path(msp_setting)
        # Else, self.model_save_path remains unchanged.
            
        if "retraining_config" in settings and isinstance(settings["retraining_config"], dict):
            self.retraining_config.update(settings["retraining_config"])
            self.retrain_interval_days = self.retraining_config.get("frequency_days", self.retrain_interval_days)


        # Update ModelConfig and TradingConfig objects
        model_cfg_dict = settings.get("model_config")
        if isinstance(model_cfg_dict, dict):
            try: self.model_config = ModelConfig(**model_cfg_dict)
            except Exception as e: self.write_log(f"Error updating ModelConfig: {e}", ERROR)
        
        trading_cfg_dict = settings.get("trading_config")
        if isinstance(trading_cfg_dict, dict):
            try: 
                self.trading_config = TradingConfig(**trading_cfg_dict)
                if hasattr(self.trading_config, 'validate'): self.trading_config.validate()
            except Exception as e: self.write_log(f"Error updating TradingConfig: {e}", ERROR)

        # Update other custom parameters listed in self.parameters
        for param_name in self.parameters:
            if param_name in settings and param_name not in [
                "vt_symbols", "required_factor_keys", "model_load_path", 
                "model_save_path", "retraining_config", "model_config", "trading_config"
            ]: # Avoid re-assigning already handled standard fields
                setattr(self, param_name, settings[param_name])
        
        # After updating settings, especially model_load_path, attempt to reload the model
        self.load_model()
        self.write_log("Strategy settings updated.", INFO)
        self.put_event()


    # --------------------------------
    # Utility Methods
    # --------------------------------
    def _resolve_model_path(self, path_setting: Optional[str]) -> Optional[str]:
        """Helper to resolve model paths relative to MODEL_PATH if not absolute."""
        if not path_setting:
            return None
        
        path_obj = Path(path_setting)
        if path_obj.is_absolute():
            return str(path_obj)
        else:
            # Ensure MODEL_PATH is a Path object
            return str(Path(MODEL_PATH) / path_obj)

    def write_log(self, msg: str, level: int = INFO) -> None:
        self.strategy_engine.write_log(msg, self, level=level)

    def put_event(self) -> None:
        self.strategy_engine.put_strategy_update_event(self)

    def send_email(self, subject: str, msg: str) -> None:
        self.strategy_engine.send_email(subject, msg, self)

    def get_engine_type(self) -> EngineType:
        return self.strategy_engine.get_engine_type()

    def get_current_datetime(self) -> datetime:
        return self.strategy_engine.get_current_datetime()

