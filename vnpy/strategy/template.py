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
from typing import TYPE_CHECKING, Callable, List, Optional, Dict, Any, Set, Union, TYPE_CHECKING
from collections import defaultdict
import pandas as pd

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
        "vt_symbols", "required_factors", "model_config", "trading_config", "retrain_interval_days"
    ]
    variables: List[str] = [  # List of state variables to expose (optional)
        "inited", "trading", "latest_factor_update_time", "last_retrain_time"
    ]

    # --- Default Settings (Can be overridden in subclasses or settings file) ---
    required_vt_symbols: List[str] = []  # List of symbols required by the strategy
    required_factors: List[str] = []  # List of factor names required from factor events
    # Default exchange - override if needed or get from contract data
    exchange: Exchange = Exchange.BINANCE
    # Default interval - primarily informational, actual data depends on subscriptions
    interval: Interval = Interval.MINUTE

    def __init__(
            self,
            strategy_engine: "BaseStrategyEngine",
            strategy_name: str,
            vt_symbols: List[str],  # Initial symbols from settings
            setting: dict  # Initial parameters from settings
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
        self.vt_symbols: List[str] = list(vt_symbols)  # Ensure it's a mutable list

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
        # Stores the latest factor data received (as a pandas DataFrame)
        self.latest_factor_data: Optional[pd.DataFrame] = None
        self.latest_factor_update_time: Optional[datetime] = None

        # --- Model Related Attributes ---
        self.model: Any = None
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
        self.update_setting(setting)
        # Note: restore_state might be called by engine if loading persisted state

        self.write_log("Strategy instance initialized.", level=DEBUG)

    # --------------------------------
    # Abstract Core Logic Methods (Implement in Subclass)
    # --------------------------------

    @virtual
    def calculate(self, df: pd.DataFrame) -> pd.Series:
        """
        Calculate raw trading signals based on input data.
        This method can be overridden if a strategy uses a simpler, non-model-based calculation.
        For model-based strategies, `predict_from_model` will be the primary method.
        """
        pass

    @abstractmethod
    def train_model(self, data: pd.DataFrame) -> None:
        """
        Train the strategy's underlying model.

        Args:
            data: Pandas DataFrame containing historical features (factors) and potentially targets
                  for training the model. Structure depends on the specific model implementation.
        """
        pass

    @abstractmethod
    def predict_from_model(self, data: pd.DataFrame) -> pd.Series:
        """
        Generate trading signals from the trained model using new input data.

        Args:
            df: Pandas DataFrame containing relevant data (e.g., factors, market data)
                indexed by vt_symbol, with columns for each factor/data point.

        Returns:
            Pandas Series containing the calculated signal strength for each vt_symbol.
            Index should be vt_symbol, values are the signals (e.g., -1 to 1).
        """
        pass

    @abstractmethod
    def project_signals_to_weights(self, signals: pd.Series) -> pd.Series:
        """
        Convert calculated signals into target portfolio weights.

        This method implements the portfolio construction logic (e.g., ranking,
        optimization, risk management constraints).

        Args:
            signals: Pandas Series of raw signals indexed by vt_symbol.

        Returns:
            Pandas Series of target portfolio weights indexed by vt_symbol.
            Weights should typically sum to 1 (or less for cash holding).
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
        self.latest_factor_update_time = self.strategy_engine.get_current_datetime()

        # --- Data Preparation for Model ---
        data_for_model: Dict[str, pd.DataFrame] = {}
        missing_factors = False
        for factor_name in self.required_factors:
            if factor_name in factor_memories:
                factor_memory = factor_memories[factor_name]
                # Get latest row(s) of factor data
                # For now, N=1, meaning the most recent snapshot for each symbol.
                # If model needs sequence, N > 1.
                polars_df = factor_memory.get_latest_rows(N=1)

                if polars_df is None or polars_df.is_empty():
                    self.write_log(f"Factor {factor_name} provided empty data from get_latest_rows(1).", level=WARNING)
                    missing_factors = True
                    break 
                
                pandas_df = polars_df.to_pandas()
                # Store the pandas DataFrame, assuming it's correctly structured by FactorMemory
                # (e.g., has 'vt_symbol' and value columns)
                data_for_model[factor_name] = pandas_df
            else:
                self.write_log(f"Required factor {factor_name} not found in received factor_memories.", level=WARNING)
                missing_factors = True
                break  # Skip this cycle if a required factor is missing

        if missing_factors or not data_for_model:
            self.write_log("Skipping prediction due to missing or incomplete factor data.", level=WARNING)
            return None

        # --- Combine Factor DataFrames ---
        combined_dfs = []
        for factor_name, pandas_df in data_for_model.items():
            if 'vt_symbol' not in pandas_df.columns:
                self.write_log(f"Factor {factor_name} DataFrame missing 'vt_symbol' column. Schema: {pandas_df.columns}", level=WARNING)
                continue # Skip this factor

            # Assuming the primary value column is named 'value' or the factor_name itself
            # This needs to be robust based on FactorMemory's output structure
            value_col_found = False
            if 'value' in pandas_df.columns:
                renamed_df = pandas_df.rename(columns={'value': factor_name})
                value_col_found = True
            elif factor_name in pandas_df.columns:
                renamed_df = pandas_df # Already has factor_name as a column
                value_col_found = True
            else:
                # Attempt to find a suitable value column if only 'vt_symbol', 'datetime' and one other exist
                potential_value_cols = [col for col in pandas_df.columns if col not in ['vt_symbol', 'datetime']]
                if len(potential_value_cols) == 1:
                    self.write_log(f"Factor {factor_name}: Assuming '{potential_value_cols[0]}' is the value column.", level=DEBUG)
                    renamed_df = pandas_df.rename(columns={potential_value_cols[0]: factor_name})
                    value_col_found = True
                else:
                    self.write_log(f"Factor {factor_name} DataFrame missing a clear value column (expected 'value', '{factor_name}', or single other). Schema: {pandas_df.columns}", level=WARNING)
                    continue

            if value_col_found:
                # Ensure vt_symbol is index, select only the factor column
                processed_df = renamed_df.set_index('vt_symbol')[[factor_name]]
                combined_dfs.append(processed_df)

        if not combined_dfs:
            self.write_log("No factor data successfully processed and combined for model input.", level=WARNING)
            return None

        try:
            model_input_df = pd.concat(combined_dfs, axis=1)
        except Exception as e:
            self.write_log(f"Error concatenating factor DataFrames: {e}", level=ERROR)
            return None
            
        # Filter for symbols relevant to this strategy
        model_input_df = model_input_df[model_input_df.index.isin(self.vt_symbols)]
        if model_input_df.empty:
            self.write_log("Model input DataFrame is empty after filtering for strategy symbols.", level=DEBUG)
            return None
            
        # Check for NaNs after merging and handle if necessary (e.g., fill or drop)
        if model_input_df.isnull().values.any():
            self.write_log(f"NaNs found in model_input_df. Shape: {model_input_df.shape}. NaNs per column:\n{model_input_df.isnull().sum()}", level=WARNING)
            # Option: fillna or dropna based on strategy requirements
            # For now, let's try filling with a common value like 0, or ffill/bfill if appropriate
            # This is a placeholder; proper NaN handling is crucial.
            model_input_df = model_input_df.fillna(0) # Example: fill with 0
            # self.write_log(f"Filled NaNs with 0. Resulting df:\n{model_input_df.head()}", level=DEBUG)


        self.latest_factor_data = model_input_df # Cache the processed data for inspection

        # --- Core Logic ---
        try:
            # 1. Check Retraining Schedule (Placeholder - actual training call might be elsewhere or asynchronous)
            current_dt = self.get_current_datetime()
            if self.check_retraining_schedule(current_dt):
                self.write_log("Retraining condition met. Triggering model training (actual training TBD).", level=INFO)
                # Placeholder: In a real system, you might fetch more historical data here.
                # For now, assume train_model can use available historical factor data or self.latest_factor_data
                # if designed for online updates. The `data` arg for train_model needs careful consideration.
                # self.train_model(historical_data_df) # This would need data beyond current factors
                # For now, we'll log and skip actual training in on_factor to avoid blocking.
                # Training should ideally be handled by a separate process or scheduled task.
                # If train_model updates self.model, it will be used by predict_from_model.
                pass # Actual training call is complex; for now, focus on prediction path.

            if self.model is None:
                self.write_log("Model is not trained. Cannot generate predictions.", level=WARNING)
                return None

            # 2. Generate Signals using the Model
            signals: pd.Series = self.predict_from_model(model_input_df)
            if not isinstance(signals, pd.Series) or signals.empty:
                self.write_log("Prediction from model returned empty or invalid result.", level=WARNING)
                return None

            # 3. Project Signals to Target Weights
            target_weights: pd.Series = self.project_signals_to_weights(signals)
            if not isinstance(target_weights, pd.Series) or target_weights.empty:
                self.write_log("Weight projection returned empty or invalid result.", level=WARNING)
                return None

            # Ensure weights are aligned with available factor symbols (index of model_input_df)
            target_weights = target_weights.reindex(model_input_df.index).fillna(0.0)

            # 3. Calculate Target Positions in Quote Currency (e.g., USD)
            if not self.portfolio_result:
                self.write_log("Cannot calculate target positions: PortfolioResult not available.", level=ERROR)
                return None

            total_portfolio_value = self.portfolio_result.get_total_value()
            if total_portfolio_value <= 0:
                self.write_log(
                    f"Cannot calculate target positions: Total portfolio value is {total_portfolio_value:.2f}",
                    level=WARNING)
                return None

            target_positions_quote = target_weights * total_portfolio_value

            # 4. Generate Orders
            order_reqs = self.generate_orders_from_targets(target_positions_quote)
            self.write_log(f"Generated {len(order_reqs)} order requests based on factor update.", level=DEBUG)
            return order_reqs

        except Exception as e:
            self.write_log(f"Error during factor processing pipeline: {e}\n{traceback.format_exc()}", level=ERROR)
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
    # Model and Retraining
    # --------------------------------

    def check_retraining_schedule(self, current_datetime: datetime) -> bool:
        """
        Check if the model should be retrained based on the schedule.
        """
        if self.model is None:
            self.write_log("Retraining check: Model is None, retraining required.", level=INFO)
            return True
        
        if self.last_retrain_time is None:
            self.write_log("Retraining check: Last retrain time is None, retraining required.", level=INFO)
            return True

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
    # Portfolio and Order Generation
    # --------------------------------

    def generate_orders_from_targets(self, target_positions_quote: pd.Series) -> List[OrderRequest]:
        """
        Generate buy/sell orders to adjust current positions towards target positions.

        Args:
            target_positions_quote: Pandas Series indexed by vt_symbol, where values
                                     are the target position value in quote currency (e.g., USD).

        Returns:
            List of OrderRequest objects.
        """
        order_reqs: List[OrderRequest] = []
        min_order_volume = getattr(self.trading_config, 'min_order_volume', 1e-8)

        for vt_symbol in target_positions_quote.index:
            if vt_symbol not in self.vt_symbols:
                self.write_log(f"Symbol {vt_symbol} from target weights not in strategy's vt_symbols list. Skipping.",
                               level=WARNING)
                continue

            # Get necessary data
            tick = self.get_tick(vt_symbol)
            contract = self.get_contract(vt_symbol)

            if not tick or not tick.last_price or tick.last_price <= 0:
                self.write_log(
                    f"Skipping order generation for {vt_symbol}: Missing or invalid last price in tick data.",
                    level=WARNING)
                continue
            if not contract:
                self.write_log(f"Skipping order generation for {vt_symbol}: Contract details not found.", level=WARNING)
                continue

            last_price = tick.last_price
            price_tick = contract.pricetick or 0.00000001  # Use small default if not available
            size = contract.size or 1  # Contract multiplier

            # Get current position (in base currency units)
            current_pos_base = self.strategy_engine.get_portfolio_position(self.strategy_name, vt_symbol)

            # Calculate target position in base currency units
            target_pos_quote = target_positions_quote.get(vt_symbol, 0.0)
            target_pos_base = target_pos_quote / (last_price * size)  # Adjust for contract size

            # Calculate position difference
            pos_diff_base = target_pos_base - current_pos_base

            # Determine order direction and volume
            direction: Optional[Direction] = None
            volume: float = abs(pos_diff_base)

            if pos_diff_base > min_order_volume:
                direction = Direction.LONG
            elif pos_diff_base < -min_order_volume:
                direction = Direction.SHORT
                # Ensure volume reflects selling the absolute difference
            else:
                continue  # Difference is too small, no order needed

            # Round volume to contract's volume step (if available, otherwise use reasonable precision)
            volume_tick = getattr(contract, 'volumetick', None)  # Check if volumetick exists
            if volume_tick and volume_tick > 0:
                volume = round_to(volume, volume_tick)
            else:
                # Default rounding if volumetick is not available
                volume = round(volume, 8)  # Adjust precision as needed

            # Skip if rounded volume becomes too small
            if volume < min_order_volume:
                continue

            # --- Create Order Request ---
            # Use LIMIT orders slightly away from last price for better execution chance?
            # Or use MARKET orders (requires gateway support and careful consideration)
            # Example: Limit order at last price (can be adjusted)
            order_price = last_price
            # Ensure price is rounded to price tick
            order_price = round_to(order_price, price_tick)

            # Use LIMIT order type as a default, adjust if needed
            order_type = OrderType.LIMIT

            req = OrderRequest(
                symbol=contract.symbol,
                exchange=contract.exchange,
                direction=direction,
                offset=Offset.NONE,  # Assuming no offset needed for portfolio adjustments
                type=order_type,
                price=order_price,
                volume=volume,
                reference=self.strategy_name  # Engine will set this, but good practice
            )
            order_reqs.append(req)
            self.write_log(f"Generated Order: {req.vt_symbol} {req.direction} {req.volume:.6f} @ {req.price:.6f}",
                           level=DEBUG)

        return order_reqs

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
            self.vt_symbols = list(setting["vt_symbols"])  # Update symbol list

        if "required_factors" in setting and isinstance(setting["required_factors"], list):
            self.required_factors = list(setting["required_factors"])

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
