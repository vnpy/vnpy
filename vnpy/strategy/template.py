# -*- coding: utf-8 -*-
"""
Provides a base template for portfolio-level trading strategies, designed to
work with the BaseStrategyEngine and optionally the PortfolioEngine.

Strategies inheriting from this template should implement the core logic in:
- `calculate`: To generate trading signals from input data (e.g., factors).
- `project_signals_to_weights`: To convert signals into target portfolio weights.
"""

from abc import ABC, abstractmethod
from datetime import datetime
from logging import DEBUG, ERROR, INFO, WARNING
import traceback
from typing import TYPE_CHECKING, Callable, List, Optional, Dict, Any, Set, Union, TYPE_CHECKING, Tuple
from collections import defaultdict
import pandas as pd
import polars as pl
import joblib
import pickle
# from sklearn.base import BaseEstimator # Example

# --- VnTrader Imports ---
from vnpy.trader.constant import (
    Interval, Direction, Offset, Exchange, OrderType, EngineType, Status
)
from vnpy.trader.object import (
    BarData, ContractData, TickData, CancelRequest, OrderData, FactorData, OrderRequest, TradeData
)
from vnpy.trader.utility import convert_dict_to_dataframe, virtual, round_to
from vnpy.factor.memory import FactorMemory


# --- Local Imports ---
# Assuming these config models exist in the specified path relative to the template
try:
    from .config.models.config import ModelConfig
    from .config.trading.config import TradingConfig
except ImportError:
    print("Warning: Could not import ModelConfig or TradingConfig. Using dummy classes.")

    # Define dummy classes if the real ones are not found
    class ModelConfig:
        pass

    class TradingConfig:
        min_order_volume: float = 0.0  # Example attribute

        def validate(self): pass

# Type hint for the engine, resolved during type checking
if TYPE_CHECKING:
    from .engine import BaseStrategyEngine  # Use relative import if in same package
    from vnpy.trader.object import OrderRequest
    from vnpy.factor.memory import FactorMemory # Though imported above, good for explicitness in hints


class StrategyTemplate(ABC):
    """
    Abstract base class for portfolio trading strategies.

    Provides a framework for handling market data (factors), generating target
    positions, managing orders, and interacting with the Strategy Engine and
    Portfolio Engine.
    """

    # --- Strategy Metadata (Override in subclasses) ---
    author: str = "Unknown"  # Strategy author name
    parameters: List[str] = [  # List of configurable parameter names
        "vt_symbols", "required_factor_keys", "model_config", "trading_config", "retrain_interval_days",
        "model_load_path", "model_save_path", "retraining_config"
    ]
    variables: List[str] = [  # List of state variables to expose (optional)
        "inited", "trading", "latest_factor_update_time", "last_retrain_time", "model_load_path", "model_save_path"
    ]

    # --- Default Settings (Can be overridden in subclasses or settings file) ---
    required_vt_symbols: List[str] = []  # List of symbols required by the strategy
    required_factor_keys: List[str] = []  # List of factor names required from factor events
    # Default exchange - override if needed or get from contract data
    exchange: Exchange = Exchange.BINANCE
    # Default interval - primarily informational, actual data depends on subscriptions
    interval: Interval = Interval.MINUTE

    def __init__(
            self,
            strategy_engine: "BaseStrategyEngine",
            strategy_name: str,
            vt_symbols: List[str],  # Initial symbols from settings
            setting: dict,  # Initial parameters from settings
            model_load_path: Optional[str] = None,
            model_save_path: Optional[str] = None,
            retraining_config: Optional[Dict[str, Any]] = None,
            required_factor_keys: Optional[List[str]] = None
    ) -> None:
        """
        Initialize the StrategyTemplate instance.

        Args:
            strategy_engine: The Strategy Engine managing this strategy.
            strategy_name: A unique name for this strategy instance.
            vt_symbols: Initial list of vt_symbols from configuration.
            setting: Dictionary of initial parameters from configuration.
        """
        self.strategy_engine: "BaseStrategyEngine" = strategy_engine
        self.strategy_name: str = strategy_name
        # vt_symbols can be updated later via settings
        self.vt_symbols: List[str] = list(vt_symbols) if vt_symbols else [] # Ensure it's a mutable list

        # --- Model Persistence and Configuration ---
        self.model_load_path: Optional[str] = model_load_path
        self.model_save_path: Optional[str] = model_save_path
        self.retraining_config: Dict[str, Any] = retraining_config if retraining_config is not None else {}
        self.required_factor_keys: List[str] = list(required_factor_keys) if required_factor_keys is not None else []


        # --- Engine Access ---
        # Convenience methods to access engine functionalities
        self.get_tick: Callable[[str], Optional[TickData]] = self.strategy_engine.get_tick
        self.get_bar: Callable[[str], Optional[BarData]] = self.strategy_engine.get_bar
        self.get_contract: Callable[[str], Optional[ContractData]] = self.strategy_engine.get_contract

        # --- Configuration Objects ---
        # Initialize with default or empty configs first
        self.model_config = ModelConfig()
        self.trading_config = TradingConfig()
        # Ensure default min_order_volume exists if TradingConfig is a dummy
        if not hasattr(self.trading_config, 'min_order_volume'):
            self.trading_config.min_order_volume = 1e-8  # Small default tolerance

        # --- Strategy State ---
        self.inited: bool = False  # True after on_init completes successfully
        self.trading: bool = False  # True after on_start completes and strategy is active

        # --- Market Data Cache ---
        # Stores the last known bar for each symbol (optional usage)
        self.bars: Dict[str, BarData] = defaultdict(BarData)
        # Stores the latest factor data received (as a Polars DataFrame or Pandas for model input)
        self.latest_factor_data: Optional[Union[pd.DataFrame, pl.DataFrame]] = None # Can store intermediate polars or final pandas
        self.latest_factor_update_time: Optional[datetime] = None

        # --- Model Related Attributes ---
        self.model: Any = None  # Model instance, e.g., scikit-learn estimator
        self.last_retrain_time: Optional[datetime] = None
        self.retrain_interval_days: int = 30  # Default retraining interval

        # --- Order Management ---
        # Stores vt_orderids of orders placed by this strategy that are still active
        self.active_order_ids: Set[str] = set()

        # --- Portfolio Interaction ---
        # Direct access to portfolio results (requires PortfolioEngine)
        self.portfolio_result = None
        if self.strategy_engine.portfolio_engine:
            try:
                # Get the specific PortfolioResult object for this strategy instance
                self.portfolio_result = self.strategy_engine.portfolio_engine.get_portfolio_result(
                    reference=self.strategy_name
                )
                self.write_log("Successfully linked with PortfolioResult.", level=DEBUG)
            except Exception as e:
                self.write_log(f"Error linking with PortfolioResult: {e}", level=ERROR)
        else:
            self.write_log("PortfolioEngine not available, portfolio results integration disabled.", level=WARNING)

        # --- Apply Initial Settings ---
        # Load parameters provided in the 'setting' dictionary
        if setting: # Ensure settings are passed
            self.update_setting(setting)
        
        # Attempt to load a pre-trained model if path is specified
        self.load_model() 
        # Note: restore_state might be called by engine if loading persisted state

        self.write_log("Strategy instance initialized.", level=DEBUG)

    # --------------------------------
    # Abstract Core Logic Methods (Implement in Subclass)
    # --------------------------------

    @abstractmethod
    def _transform_latest_factors(self, latest_factor_data_map: Dict[str, "pl.DataFrame"]) -> "pl.DataFrame":
        """
        Transforms and combines the latest snapshot of multiple factor DataFrames (Polars)
        into a single Polars DataFrame suitable for model prediction.
        This typically involves aligning symbols and creating a feature matrix where
        rows are vt_symbols and columns are factor features.

        Args:
            latest_factor_data_map: Dict mapping factor_key to a Polars DataFrame
                                     containing the latest data for that factor.
                                     Each DataFrame is expected to have at least 'vt_symbol'
                                     and factor value column(s).

        Returns:
            A Polars DataFrame where each row represents a vt_symbol and columns
            are the combined features from all relevant factors.
        """
        pass

    @abstractmethod
    def predict_from_model(self, data: pd.DataFrame) -> Any:
        """
        Generate raw predictions from the trained model using new input data.
        This method typically calls `self.model.predict()` or `self.model.predict_proba()`.

        Args:
            data: Pandas DataFrame containing the combined and transformed features,
                  ready for input into the model. Index should be vt_symbol.

        Returns:
            The raw output from the model (e.g., numpy array of predictions or probabilities).
        """
        pass

    @abstractmethod
    def generate_signals_from_prediction(
        self, model_output: Any, symbol_feature_df: pd.DataFrame
    ) -> List[OrderRequest]:
        """
        Convert the raw model output into trading signals or directly into OrderRequests.

        Args:
            model_output: The raw output from `predict_from_model`.
            symbol_feature_df: The Pandas DataFrame that was fed into the model,
                               indexed by vt_symbol. Useful for context (e.g., getting symbol list).

        Returns:
            A list of OrderRequest objects to be executed, or an empty list if no actions.
            Can also return other types of signals if the strategy uses a multi-step process.
        """
        pass

    @abstractmethod
    def prepare_training_data(
        self, historical_factor_data_map: Dict[str, "pl.DataFrame"]
    ) -> Tuple[pd.DataFrame, pd.Series]:
        """
        Prepares features (X) and labels (y) for model training from historical factor data.

        Args:
            historical_factor_data_map: Dict mapping factor_key to a Polars DataFrame
                                         containing historical data for that factor.

        Returns:
            A tuple (features_df, labels_series):
            - features_df: Pandas DataFrame of features for training (X).
            - labels_series: Pandas Series of labels for training (y).
        """
        pass


    # --------------------------------
    # Lifecycle Methods (Called by Engine)
    # --------------------------------
    @virtual
    def on_init(self) -> None:
        """
        Callback when strategy is initializing.
        Load historical data, initialize indicators, etc.
        Set `self.inited = True` upon successful completion.
        """
        self.write_log("Strategy initializing...")
        # --- Example: Load historical data ---
        # if self.get_engine_type() != EngineType.BACKTESTING:
        #     self.load_bar(10) # Load last 10 bars for initialization

        self.inited = True  # Mark as initialized
        self.write_log("Strategy initialized.")
        self.put_event()  # Notify engine/UI about state change

    @virtual
    def on_start(self) -> None:
        """
        Callback when strategy is starting trading.
        Set `self.trading = True` upon successful completion.
        """
        self.write_log("Strategy starting...")
        self.trading = True  # Mark as trading
        self.write_log("Strategy started.")
        self.put_event()  # Notify engine/UI

    @virtual
    def on_stop(self) -> None:
        """
        Callback when strategy is stopping trading.
        Perform cleanup, persist state if needed.
        Engine automatically sets `self.trading = False` before calling this.
        """
        self.write_log("Strategy stopping...")
        # Clear active orders tracked by the strategy
        self.active_order_ids.clear()
        self.write_log("Strategy stopped.")
        self.put_event()  # Notify engine/UI

    # --------------------------------
    # Event Processing Methods (Called by Engine)
    # --------------------------------

    @virtual
    def on_factor(self, factor_memories: Dict[str, "FactorMemory"]) -> Optional[List[OrderRequest]]:
        """
        Callback when new factor data is received.

        Args:
            factor_memories: Dictionary mapping factor names to FactorMemory objects.

        Returns:
            A list of OrderRequest objects to be executed, or None/empty list.
        """
        if not self.trading:
            return None

        self.write_log(f"Received factor memories update: {list(factor_memories.keys())}", level=DEBUG)
        current_dt = self.strategy_engine.get_current_datetime()
        self.latest_factor_update_time = current_dt

        # --- 1. Fetch Latest Polars Data for Each Factor ---
        latest_polars_data_map: Dict[str, pl.DataFrame] = {}
        missing_data = False
        for factor_key in self.required_factor_keys:
            factor_memory = factor_memories.get(factor_key)
            if not factor_memory:
                self.write_log(f"Required factor key {factor_key} not found in received factor_memories.", level=WARNING)
                missing_data = True
                break
            
            # Get latest row(s) - N=1 for snapshot
            polars_df = factor_memory.get_latest_rows(N=1)
            if polars_df is None or polars_df.is_empty():
                self.write_log(f"Factor {factor_key} provided empty data from get_latest_rows(1).", level=WARNING)
                # missing_data = True # Depending on strategy, one missing factor might be acceptable
                # break
                continue # Store empty or skip, depends on how _transform_latest_factors handles it

            latest_polars_data_map[factor_key] = polars_df
        
        if missing_data or not latest_polars_data_map:
            self.write_log("Skipping prediction due to missing required factor data.", level=WARNING)
            return None

        # --- Core Logic ---
        try:
            # 1. Check Retraining Schedule - This is usually handled by engine calling retrain_model separately
            # if self.check_retraining_schedule(current_dt):
            #     self.write_log("Retraining condition met. Consider triggering retrain_model.", level=INFO)
                # Actual retraining should be asynchronous or scheduled, not blocking on_factor.

            if self.model is None:
                self.write_log("Model is not loaded or trained. Cannot generate predictions.", level=WARNING)
                return None

            # 2. Transform latest factors into a single DataFrame for the model
            # This method is responsible for aligning symbols and creating a feature matrix.
            transformed_pl_df = self._transform_latest_factors(latest_polars_data_map)
            if transformed_pl_df is None or transformed_pl_df.is_empty():
                self.write_log("Factor transformation resulted in empty data.", level=WARNING)
                return None
            
            # Cache the Polars DataFrame (or convert to Pandas and cache)
            self.latest_factor_data = transformed_pl_df 

            # Filter for symbols relevant to this strategy, if not already done in _transform_latest_factors
            # transformed_pl_df = transformed_pl_df.filter(pl.col('vt_symbol').is_in(self.vt_symbols))
            # if transformed_pl_df.is_empty():
            #     self.write_log("Transformed DataFrame is empty after filtering for strategy symbols.", level=DEBUG)
            #     return None

            # 3. Convert to Pandas DataFrame for scikit-learn or other libraries
            # Assuming 'vt_symbol' is a column that should become the index
            if 'vt_symbol' not in transformed_pl_df.columns:
                self.write_log("Transformed Polars DataFrame missing 'vt_symbol' column for index.", level=ERROR)
                return None
            
            # It's often better to let predict_from_model and generate_signals_from_prediction
            # handle the conversion to pandas and indexing if they need it.
            # For now, provide the Polars DF, and let the abstract methods decide.
            # However, predict_from_model is typed to take pd.DataFrame.
            
            pandas_transformed_df = transformed_pl_df.to_pandas().set_index('vt_symbol')
            
            # Ensure all required factor keys are present as columns after transformation, if model expects them
            # This check depends on how _transform_latest_factors structures its output.
            # Example: for factor_key in self.required_factor_keys:
            # if factor_key not in pandas_transformed_df.columns:
            # self.write_log(f"Column for factor {factor_key} missing in pandas_transformed_df", ERROR)
            # return None
            
            if pandas_transformed_df.empty:
                self.write_log("Pandas DataFrame for model input is empty.", level=DEBUG)
                return None

            # 4. Get predictions from the model
            # predict_from_model is abstract, implementation will call self.model.predict() etc.
            model_prediction_output = self.predict_from_model(pandas_transformed_df)
            if model_prediction_output is None: # Could be empty list/array too
                self.write_log("Prediction from model returned None or empty result.", level=WARNING)
                return None

            # 5. Generate signals/OrderRequests from predictions
            # generate_signals_from_prediction is abstract.
            # It takes raw model output and the feature df (for context like symbol list).
            order_reqs: List[OrderRequest] = self.generate_signals_from_prediction(
                model_prediction_output,
                pandas_transformed_df # Pass the pandas DF used for prediction
            )

            if order_reqs:
                self.write_log(f"Generated {len(order_reqs)} order requests.", level=DEBUG)
            return order_reqs

        except Exception as e:
            self.write_log(f"Error during on_factor processing pipeline: {e}\n{traceback.format_exc()}", level=ERROR)
            return None

    @virtual
    def on_order(self, order: OrderData) -> None:
        """
        Callback when an order update is received from the engine.
        Use this to track the status of orders placed by this strategy.
        """
        self.write_log(f"Order Update: {order.vt_orderid} Status: {order.status} "
                       f"Filled: {order.traded}/{order.volume}", level=DEBUG)

        # Update internal tracking of active orders
        if order.is_active():
            self.active_order_ids.add(order.vt_orderid)
        else:
            if order.vt_orderid in self.active_order_ids:
                self.active_order_ids.remove(order.vt_orderid)

        # Custom strategy logic based on order status can be added here.
        # For example, handling rejected orders, partial fills, etc.

    @virtual
    def on_trade(self, trade: TradeData) -> None:
        """
        Callback when a trade update (fill) is received from the engine.
        Use this for monitoring or adjusting strategy state based on fills.
        Portfolio PnL/position updates are handled by the PortfolioEngine.
        """
        self.write_log(f"Trade Update: {trade.vt_orderid} Direction: {trade.direction} "
                       f"Price: {trade.price} Volume: {trade.volume}", level=DEBUG)

        # Custom strategy logic based on trade fills can be added here.

    # --------------------------------
    # Model Persistence and Retraining
    # --------------------------------

    def load_model(self) -> None:
        """
        Load the model from the path specified in `model_load_path`.
        """
        if self.model_load_path:
            self.write_log(f"Attempting to load model from: {self.model_load_path}", level=INFO)
            try:
                # Ensure the path exists
                import os
                if not os.path.exists(self.model_load_path):
                    self.write_log(f"Model file not found at {self.model_load_path}. No model loaded.", level=WARNING)
                    return

                with open(self.model_load_path, 'rb') as f:
                    self.model = joblib.load(f)
                self.write_log(f"Model loaded successfully from {self.model_load_path}", level=INFO)
                
                # If model loading implies it's "trained" for the purpose of retraining schedule:
                # self.last_retrain_time = self.get_current_datetime() # Or load from metadata if saved with model
            except FileNotFoundError:
                self.write_log(f"Model file not found at {self.model_load_path}. No model loaded.", level=WARNING)
            except pickle.UnpicklingError:
                self.write_log(f"Error unpickling model from {self.model_load_path}. Model may be corrupt or incompatible.", level=ERROR)
            except Exception as e:
                self.write_log(f"Failed to load model from {self.model_load_path}: {e}\n{traceback.format_exc()}", level=ERROR)
        else:
            self.write_log("No model_load_path specified. Skipping model loading.", level=DEBUG)

    def save_model(self) -> None:
        """
        Save the current model to the path specified in `model_save_path`.
        """
        if self.model_save_path and self.model is not None:
            self.write_log(f"Attempting to save model to: {self.model_save_path}", level=INFO)
            try:
                # Ensure directory exists
                import os
                os.makedirs(os.path.dirname(self.model_save_path), exist_ok=True)

                with open(self.model_save_path, 'wb') as f:
                    joblib.dump(self.model, f)
                self.write_log(f"Model saved successfully to {self.model_save_path}", level=INFO)
            except Exception as e:
                self.write_log(f"Failed to save model to {self.model_save_path}: {e}\n{traceback.format_exc()}", level=ERROR)
        elif self.model is None:
            self.write_log("No model instance to save.", level=WARNING)
        else: # No save path
            self.write_log("No model_save_path specified. Skipping model saving.", level=DEBUG)

    def _fetch_historical_training_factors(self, factor_memories: Dict[str, "FactorMemory"]) -> Dict[str, "pl.DataFrame"]:
        """
        Helper to fetch full historical data for required factors.
        """
        historical_data_map: Dict[str, pl.DataFrame] = {}
        for key in self.required_factor_keys:
            factor_memory = factor_memories.get(key)
            if factor_memory:
                # get_data() should return a Polars DataFrame
                data = factor_memory.get_data() 
                if data is not None and not data.is_empty():
                    historical_data_map[key] = data
                else:
                    self.write_log(f"No historical data retrieved for factor {key}.", level=WARNING)
            else:
                self.write_log(f"FactorMemory not found for key '{key}' during historical fetch.", level=WARNING)
        return historical_data_map

    @virtual # Keep virtual if subclasses might override the entire retraining orchestration
    def retrain_model(self) -> None:
        """
        Orchestrates the model retraining process.
        Fetches historical data, prepares it, trains the model, and saves it.
        This method is intended to be called by the StrategyEngine based on a schedule or trigger.
        """
        self.write_log("Starting model retraining process...", level=INFO)
        try:
            # 1. Fetch historical factor data (Polars DataFrames)
            # Access factor memories from the strategy engine
            if not hasattr(self.strategy_engine, 'latest_factor_memories'):
                self.write_log("StrategyEngine does not have 'latest_factor_memories'. Cannot fetch historical data.", level=ERROR)
                return
                
            historical_polars_map = self._fetch_historical_training_factors(
                self.strategy_engine.latest_factor_memories
            )

            if not historical_polars_map:
                self.write_log("No historical factor data fetched. Aborting retraining.", level=WARNING)
                return

            # 2. Prepare training data (features X, labels y) using the abstract method
            # This method is responsible for any complex transformations, feature engineering,
            # and conversion to Pandas DataFrames/Series suitable for scikit-learn.
            features_df, labels_series = self.prepare_training_data(historical_polars_map)

            if features_df is None or features_df.empty or labels_series is None or labels_series.empty:
                self.write_log("Training data preparation resulted in empty features or labels. Aborting retraining.", level=WARNING)
                return

            # 3. Train the model
            if self.model is None:
                # This implies the strategy needs to define how to instantiate its model
                # if it's not loaded. For now, we log an error.
                # A concrete strategy's __init__ or a specific method should create self.model.
                self.write_log("self.model is None. Cannot fit. Please ensure model is initialized.", level=ERROR)
                return
            
            # Assuming self.model is a scikit-learn compatible estimator
            if not hasattr(self.model, 'fit'):
                self.write_log("self.model does not have a 'fit' method. Cannot train.", level=ERROR)
                return

            self.write_log(f"Training model with {features_df.shape[0]} samples and {features_df.shape[1]} features.", level=INFO)
            self.model.fit(features_df, labels_series)
            self.write_log("Model training completed.", level=INFO)

            # 4. Save the retrained model
            self.save_model()

            # 5. Update last retrain time
            self.last_retrain_time = self.get_current_datetime()
            self.write_log(f"Model retraining finished. Last retrain time updated to {self.last_retrain_time}", level=INFO)
            self.put_event() # Notify state change

        except Exception as e:
            self.write_log(f"Error during model retraining: {e}\n{traceback.format_exc()}", level=ERROR)

    def check_retraining_schedule(self, current_datetime: datetime) -> bool:
        """
        Check if the model should be retrained based on the schedule.
        """
        if self.model is None and not self.model_load_path: # If no model and no path to load one, retrain.
            self.write_log("Retraining check: Model is None and no load path. Initial training required.", level=INFO)
            return True
        
        if self.last_retrain_time is None: # If model exists (loaded) but never retrained by this instance.
            # This could mean it was loaded and is considered "trained enough" until first interval passes.
            # Or, strategy might require retraining soon after loading if data is stale.
            # For now, if loaded, assume last_retrain_time should be set or it implies first cycle.
             self.write_log("Retraining check: Last retrain time is None. Consider if retraining is due.", level=INFO)
             # Defaulting to False if last_retrain_time is None but model exists, to let interval drive it.
             # If a model is loaded, and no last_retrain_time, it implies it hasn't been retrained by this instance yet.
             # The first scheduled retrain will then happen after retrain_interval_days.
             return False # Or True if immediate retrain post-load is desired without specific last_retrain_time.


        if self.retrain_interval_days <= 0: # Retraining is disabled or set to manual
            return False

        days_since_last_retrain = (current_datetime - self.last_retrain_time).days
        if days_since_last_retrain >= self.retrain_interval_days:
            self.write_log(
                f"Retraining check: {days_since_last_retrain} days since last retrain "
                f"(interval: {self.retrain_interval_days} days). Retraining required.", level=INFO
            )
            return True
        
        return False

    # --------------------------------
    # Portfolio and Order Generation (Order generation is now part of generate_signals_from_prediction)
    # --------------------------------
    # The method generate_orders_from_targets might still be useful if generate_signals_from_prediction
    # returns target weights/positions instead of direct OrderRequests.
    # For now, assuming generate_signals_from_prediction returns OrderRequests.
    # If not, that method or a similar one to convert signals/weights to orders would be needed here.
    # For example, if generate_signals_from_prediction returns target weights (pd.Series):
    # target_weights = self.generate_signals_from_prediction(...)
    # order_reqs = self.convert_weights_to_orders(target_weights)

    # This method is kept for utilities like closing all positions, not for main signal-to-order flow.
    def close_all_positions(self) -> List[OrderRequest]:
        """
        Generate orders to close all currently held positions for symbols
        managed by this strategy. Uses MARKET orders for quick closure.
        """
        self.write_log("Generating orders to close all positions...", level=INFO)
        order_reqs: List[OrderRequest] = []
        min_order_volume = getattr(self.trading_config, 'min_order_volume', 1e-8)

        for vt_symbol in self.vt_symbols:
            current_pos = self.strategy_engine.get_portfolio_position(self.strategy_name, vt_symbol)

            if abs(current_pos) > min_order_volume:  # Check if position is significant
                contract = self.get_contract(vt_symbol)
                if not contract:
                    self.write_log(f"Cannot close position for {vt_symbol}: Contract not found.", level=WARNING)
                    continue

                direction: Direction
                if current_pos > 0:  # Long position, need to sell
                    direction = Direction.SHORT
                else:  # Short position, need to buy back
                    direction = Direction.LONG

                # Round volume (absolute value)
                volume = abs(current_pos)
                volume_tick = getattr(contract, 'volumetick', None)
                if volume_tick and volume_tick > 0:
                    volume = round_to(volume, volume_tick)
                else:
                    volume = round(volume, 8)

                if volume < min_order_volume: continue  # Skip if rounded volume is too small

                # Use MARKET order for closing positions quickly
                req = OrderRequest(
                    symbol=contract.symbol,
                    exchange=contract.exchange,
                    direction=direction,
                    offset=Offset.NONE,  # Or Offset.CLOSE if required by exchange/gateway
                    type=OrderType.MARKET,
                    price=0,  # Market orders don't need price
                    volume=volume,
                    reference=self.strategy_name
                )
                order_reqs.append(req)
                self.write_log(
                    f"Generated Close Order: {req.vt_symbol} {req.direction} {req.volume:.6f} (Current Pos: {current_pos:.6f})",
                    level=INFO)

        return order_reqs

    def get_portfolio_state(self) -> Optional[dict]:
        """
        Get the current state data of the portfolio associated with this strategy.
        Requires PortfolioEngine to be active.
        """
        if self.portfolio_result and hasattr(self.portfolio_result, 'get_data'):
            return self.portfolio_result.get_data()
        elif self.strategy_engine.portfolio_engine:
            self.write_log("PortfolioResult object not available, cannot get portfolio state.", level=WARNING)
            return None
        else:
            # Portfolio engine not running, no state available
            return None

    # --------------------------------
    # Order Management Actions
    # --------------------------------

    def send_order(
            self,
            vt_symbol: str,
            direction: Direction,
            order_type: OrderType,
            price: float,
            volume: float,
            offset: Offset = Offset.NONE,  # Default to OPEN/NONE
            lock: bool = False,  # Pass through lock/net if needed by engine/agent
            net: bool = False
    ) -> List[str]:
        """
        Send an order request through the Strategy Engine.

        Args:
            vt_symbol: Target contract symbol.
            direction: Direction (LONG or SHORT).
            order_type: OrderType (LIMIT, MARKET, etc.).
            price: Order price (required for LIMIT orders).
            volume: Order volume.
            offset: Order offset (OPEN, CLOSE, etc.) - Defaults to NONE/OPEN.
            lock: Flag for position locking (used by ExecutionAgent).
            net: Net position flag (used by ExecutionAgent).

        Returns:
            List of vt_orderid strings generated for the order(s).
        """
        if not self.trading:
            self.write_log("Order rejected: Strategy is not currently trading.", level=WARNING)
            return []

        contract = self.get_contract(vt_symbol)
        if not contract:
            self.write_log(f"Order rejected: Contract not found for {vt_symbol}.", level=ERROR)
            return []

        # Round price and volume according to contract specifications
        price_tick = contract.pricetick or 0.00000001
        volume_tick = contract.volumetick or 0.00000001  # Use small default if not specified
        min_volume = contract.min_volume or volume_tick  # Minimum order size

        rounded_price = round_to(price, price_tick)
        rounded_volume = round_to(volume, volume_tick)

        # Validate volume against minimum
        if rounded_volume < min_volume:
            self.write_log(f"Order rejected: Volume {volume:.8f} (Rounded: {rounded_volume:.8f}) "
                           f"is less than minimum volume {min_volume:.8f} for {vt_symbol}", level=WARNING)
            return []

        req = OrderRequest(
            symbol=contract.symbol,
            exchange=contract.exchange,
            direction=direction,
            offset=offset,
            type=order_type,
            price=rounded_price,
            volume=rounded_volume,
            reference=self.strategy_name  # Engine will ensure this is set
        )

        # Delegate sending to the engine
        vt_orderids = self.strategy_engine.send_order(
            strategy_name=self.strategy_name,
            req=req,
            lock=lock,
            net=net
        )
        return vt_orderids

    def cancel_order(self, vt_orderid: str) -> None:
        """
        Request cancellation of a specific active order placed by this strategy.

        Args:
            vt_orderid: The unique order identifier (vt_orderid) to cancel.
        """
        if not self.trading:
            self.write_log(f"Cancel request ignored: Strategy not trading.", level=WARNING)
            return

        # Check if the order ID belongs to the set of active orders tracked by this strategy
        if vt_orderid not in self.active_order_ids:
            self.write_log(f"Cancel request ignored: Order ID {vt_orderid} not found in this strategy's active orders.",
                           level=WARNING)
            # Option: Allow cancelling any order via engine? Could be risky.
            # If allowed, remove the check above.
            # return # Strict check: only cancel own active orders

        # Get the full OrderData object to create a CancelRequest
        order = self.strategy_engine.main_engine.get_order(vt_orderid)
        if order:
            if order.is_active():
                # Delegate cancellation to the engine
                self.strategy_engine.cancel_order(order)
            else:
                self.write_log(
                    f"Cancel request ignored: Order {vt_orderid} is already inactive (Status: {order.status}).",
                    level=DEBUG)
                # Remove from active set if it's somehow still there
                self.active_order_ids.discard(vt_orderid)
        else:
            self.write_log(f"Cancel request failed: Order {vt_orderid} not found in MainEngine.", level=WARNING)
            # Remove from active set if it's somehow still there
            self.active_order_ids.discard(vt_orderid)

    def cancel_all_active_orders(self) -> None:
        """
        Cancel all orders currently tracked as active by this strategy instance.
        """
        if not self.trading:
            self.write_log("Cancel all request ignored: Strategy not trading.", level=WARNING)
            return

        if not self.active_order_ids:
            self.write_log("No active orders tracked by this strategy to cancel.", level=DEBUG)
            return

        self.write_log(f"Cancelling all {len(self.active_order_ids)} active orders tracked by this strategy...",
                       level=INFO)
        # Iterate over a copy of the set, as cancel_order might modify it via on_order callback
        for vt_orderid in list(self.active_order_ids):
            self.cancel_order(vt_orderid)

    def get_active_order_ids(self) -> List[str]:
        """
        Return a list of vt_orderids currently tracked as active by this strategy.
        Required by the BaseStrategyEngine for cleanup during stop/removal.
        """
        return list(self.active_order_ids)

    # --------------------------------
    # State Management (Persistence)
    # --------------------------------

    def get_parameters(self) -> dict:
        """
        Return the current strategy parameters as a dictionary.
        Used by the engine for saving settings.
        """
        # Collect parameters based on the 'parameters' list
        params = {}
        for name in self.parameters:
            value = getattr(self, name, None)
            # Serialize config objects
            if isinstance(value, (ModelConfig, TradingConfig)):
                params[name] = value.__dict__  # Convert config object to dict
            elif isinstance(value, list):
                params[name] = list(value)  # Ensure lists are copied
            elif isinstance(value, set):
                params[name] = list(value)  # Convert sets to lists for JSON
            else:
                params[name] = value
        return params

    def get_settings(self) -> dict:
        """
        Get strategy settings dictionary (equivalent to get_parameters).
        Kept for potential compatibility, prefer get_parameters.
        """
        return self.get_parameters()

    def get_data(self) -> dict:
        """
        Get the current runtime state of the strategy as a dictionary.
        Used by the engine for saving runtime data. Should be JSON serializable.
        """
        # Include basic state and any other relevant runtime variables
        data = {
            "inited": self.inited,
            "trading": self.trading,
            "active_order_ids": list(self.active_order_ids),
            "latest_factor_update_time": self.latest_factor_update_time.isoformat() if self.latest_factor_update_time else None,
            "last_retrain_time": self.last_retrain_time.isoformat() if self.last_retrain_time else None,
            # Model serialization placeholder
            "model_params": self.model.get_params() if hasattr(self.model, "get_params") else ("model_exists" if self.model is not None else None)
        }
        # Add variables defined in the 'variables' list (ensure 'last_retrain_time' is handled if it's in self.variables)
        for name in self.variables:
            if name not in data:  # Avoid overwriting core state or already added items
                value = getattr(self, name, None)
                if isinstance(value, datetime):
                    data[name] = value.isoformat()
                elif isinstance(value, (bool, int, float, str, list, dict, type(None))):
                    data[name] = value
                # Add other serializable types as needed
        return data

    def load_data(self, data: dict) -> None:
        """
        Restore the strategy's runtime state from a dictionary.
        Called by the engine during initialization (before on_init).
        """
        self.write_log("Loading runtime data into strategy...", level=DEBUG)
        # Restore basic state cautiously - engine manages init/trading flags mostly
        # self.inited = data.get("inited", self.inited)
        # self.trading = data.get("trading", self.trading)

        # Restore tracked active orders
        saved_order_ids = data.get("active_order_ids", [])
        if isinstance(saved_order_ids, list):
            self.active_order_ids = set(saved_order_ids)
            self.write_log(f"Restored {len(self.active_order_ids)} active order IDs.", level=DEBUG)

        # Restore time-related fields
        for time_field_name in ["latest_factor_update_time", "last_retrain_time"]:
            time_str = data.get(time_field_name)
            if time_str:
                try:
                    setattr(self, time_field_name, datetime.fromisoformat(time_str))
                except (TypeError, ValueError):
                    self.write_log(f"Could not parse saved time for {time_field_name}: {time_str}", level=WARNING)
        
        # Model restoration placeholder
        model_params_data = data.get("model_params")
        if model_params_data:
            if model_params_data == "model_exists" or isinstance(model_params_data, dict):
                self.model = "ModelLoadedPlaceholder" # Placeholder
                self.write_log("Model state found in saved data. Concrete strategy should handle re-instantiation.", level=INFO)
            # In a real scenario, you'd use model_params_data to re-initialize the model, e.g.
            # self.model = YourModelClass(**model_params_data) or joblib.load(...)

        # Restore other variables defined in the 'variables' list
        for name in self.variables:
            # Skip already handled variables to prevent double processing or errors
            if name in ["active_order_ids", "latest_factor_update_time", "last_retrain_time"]: 
                continue
            if name in data:
                value = data[name]
                # Handle potential type conversions (e.g., ISO string back to datetime)
                # Check if the attribute is annotated as Optional[datetime] or datetime
                # This is a simplified check; proper type handling might be more complex
                is_datetime_field = False
                if hasattr(self, '__annotations__'):
                    attr_type = self.__annotations__.get(name)
                    if attr_type == Optional[datetime] or attr_type == datetime:
                        is_datetime_field = True

                if (is_datetime_field or "time" in name.lower()) and isinstance(value, str):
                    try:
                        setattr(self, name, datetime.fromisoformat(value))
                    except (TypeError, ValueError):
                        self.write_log(f"Error parsing datetime string '{value}' for '{name}'. Setting as is.", level=WARNING)
                        setattr(self, name, value) # Keep original if parse fails
                else:
                    setattr(self, name, value)

        self.write_log("Runtime data loaded.", level=DEBUG)

    def update_setting(self, setting: dict) -> None:
        """
        Update strategy parameters from a dictionary.
        Called by the engine when editing strategy settings.
        """
        self.write_log("Updating strategy settings...", level=DEBUG)

        # Update standard parameters if present in the setting dict
        if "vt_symbols" in setting and isinstance(setting["vt_symbols"], list):
            self.vt_symbols = list(setting["vt_symbols"])

        # Update to required_factor_keys
        if "required_factor_keys" in setting and isinstance(setting["required_factor_keys"], list):
            self.required_factor_keys = list(setting["required_factor_keys"])
        elif "required_factors" in setting and isinstance(setting["required_factors"], list): # Legacy support
            self.write_log("Using legacy 'required_factors' setting, please update to 'required_factor_keys'.", WARNING)
            self.required_factor_keys = list(setting["required_factors"])
            
        # Update new parameters
        if "model_load_path" in setting:
            self.model_load_path = setting["model_load_path"]
        if "model_save_path" in setting:
            self.model_save_path = setting["model_save_path"]
        if "retraining_config" in setting and isinstance(setting["retraining_config"], dict):
            self.retraining_config.update(setting["retraining_config"]) # Merge dicts

        # Update config objects if present
        if "model_config" in setting and isinstance(setting["model_config"], dict):
            try:
                self.model_config = ModelConfig(**setting["model_config"])
                self.write_log("ModelConfig updated.", level=DEBUG)
            except Exception as e:
                self.write_log(f"Error updating ModelConfig: {e}", level=ERROR)

        if "trading_config" in setting and isinstance(setting["trading_config"], dict):
            try:
                self.trading_config = TradingConfig(**setting["trading_config"])
                # Re-validate after update
                if hasattr(self.trading_config, 'validate') and callable(self.trading_config.validate):
                    self.trading_config.validate()
                self.write_log("TradingConfig updated and validated.", level=DEBUG)
            except Exception as e:
                self.write_log(f"Error updating or validating TradingConfig: {e}", level=ERROR)

        # Update other parameters defined in the 'parameters' list
        for name in self.parameters:
            # Avoid re-updating the handled ones above
            if name not in ["vt_symbols", "required_factors", "model_config", "trading_config"]:
                if name in setting:
                    setattr(self, name, setting[name])

        self.write_log("Strategy settings updated.", level=INFO)

    # --------------------------------
    # Utility Methods
    # --------------------------------

    def write_log(self, msg: str, level: int = INFO) -> None:
        """Log a message through the Strategy Engine."""
        self.strategy_engine.write_log(msg, self, level=level)

    def put_event(self) -> None:
        """
        Publish an event to notify the engine (and potentially UI)
        about a change in the strategy's state.
        """
        # Engine usually handles putting events on init/start/stop/remove.
        # Call this if the strategy needs to signal an internal state change.
        self.strategy_engine.put_strategy_update_event(self)

    def send_email(self, subject: str, msg: str) -> None:
        """Send an email notification through the Strategy Engine."""
        self.strategy_engine.send_email(subject, msg, self)

    def get_engine_type(self) -> EngineType:
        """Get the type of the Strategy Engine (LIVE or BACKTESTING)."""
        return self.strategy_engine.get_engine_type()

    def get_current_datetime(self) -> datetime:
        """Get the current datetime from the Strategy Engine (handles backtesting time)."""
        return self.strategy_engine.get_current_datetime()
