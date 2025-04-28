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
from typing import TYPE_CHECKING, Callable, List, Optional, Dict, Any, Set, Union
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

# --- Local Imports ---
# Assuming these config models exist in the specified path relative to the template
try:
    from .config.models.config import ModelConfig
    from .config.trading.config import TradingConfig
except ImportError:
    print("Warning: Could not import ModelConfig or TradingConfig. Using dummy classes.")
    # Define dummy classes if the real ones are not found
    class ModelConfig: pass
    class TradingConfig:
        min_order_volume: float = 0.0 # Example attribute
        def validate(self): pass

# Type hint for the engine, resolved during type checking
if TYPE_CHECKING:
    from .engine import BaseStrategyEngine # Use relative import if in same package


class StrategyTemplate(ABC):
    """
    Abstract base class for portfolio trading strategies.

    Provides a framework for handling market data (factors), generating target
    positions, managing orders, and interacting with the Strategy Engine and
    Portfolio Engine.
    """

    # --- Strategy Metadata (Override in subclasses) ---
    author: str = "Unknown"             # Strategy author name
    parameters: List[str] = [           # List of configurable parameter names
        "vt_symbols", "required_factors", "model_config", "trading_config"
    ]
    variables: List[str] = [            # List of state variables to expose (optional)
        "inited", "trading", "latest_factor_update_time"
    ]

    # --- Default Settings (Can be overridden in subclasses or settings file) ---
    required_vt_symbols: List[str] = [] # List of symbols required by the strategy
    required_factors: List[str] = []    # List of factor names required from factor events
    # Default exchange - override if needed or get from contract data
    exchange: Exchange = Exchange.BINANCE
    # Default interval - primarily informational, actual data depends on subscriptions
    interval: Interval = Interval.MINUTE

    def __init__(
        self,
        strategy_engine: "BaseStrategyEngine",
        strategy_name: str,
        vt_symbols: List[str], # Initial symbols from settings
        setting: dict            # Initial parameters from settings
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
        self.vt_symbols: List[str] = list(vt_symbols) # Ensure it's a mutable list

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
             self.trading_config.min_order_volume = 1e-8 # Small default tolerance

        # --- Strategy State ---
        self.inited: bool = False       # True after on_init completes successfully
        self.trading: bool = False      # True after on_start completes and strategy is active

        # --- Market Data Cache ---
        # Stores the last known bar for each symbol (optional usage)
        self.bars: Dict[str, BarData] = defaultdict(BarData)
        # Stores the latest factor data received (as a pandas DataFrame)
        self.latest_factor_data: Optional[pd.DataFrame] = None
        self.latest_factor_update_time: Optional[datetime] = None

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

    @abstractmethod
    def calculate(self, df: pd.DataFrame) -> pd.Series:
        """
        Calculate raw trading signals based on input data.

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

        self.inited = True # Mark as initialized
        self.write_log("Strategy initialized.")
        self.put_event() # Notify engine/UI about state change

    @virtual
    def on_start(self) -> None:
        """
        Callback when strategy is starting trading.
        Set `self.trading = True` upon successful completion.
        """
        self.write_log("Strategy starting...")
        self.trading = True # Mark as trading
        self.write_log("Strategy started.")
        self.put_event() # Notify engine/UI

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
        self.put_event() # Notify engine/UI

    # --------------------------------
    # Event Processing Methods (Called by Engine)
    # --------------------------------

    @virtual
    def on_factor(self, factor_data: Dict[str, Any]) -> Optional[List[OrderRequest]]:
        """
        Callback when new factor data is received.

        Args:
            factor_data: Dictionary containing the latest factor values.
                         Format might vary, assuming {factor_name: value} or
                         nested dict {vt_symbol: {factor_name: value}}.
                         Needs adaptation based on actual factor event structure.

        Returns:
            A list of OrderRequest objects to be executed, or None/empty list.
        """
        if not self.trading:
            return None # Do nothing if not trading

        self.write_log(f"Received factor update: {list(factor_data.keys())}", level=DEBUG)
        self.latest_factor_update_time = self.strategy_engine.get_current_datetime()

        # --- Data Preparation ---
        # Adapt this section based on the actual structure of factor_data
        # Example: Assuming factor_data is {vt_symbol: {factor_name: value}}
        try:
            # Convert to DataFrame, indexed by vt_symbol, columns are factors
            df = pd.DataFrame.from_dict(factor_data, orient="index")
            if df.empty:
                 self.write_log("Factor data is empty after conversion.", level=DEBUG)
                 return None
        except Exception as e:
             self.write_log(f"Error converting factor data to DataFrame: {e}", level=ERROR)
             return None

        # Filter for symbols relevant to this strategy
        relevant_symbols = [sym for sym in df.index if sym in self.vt_symbols]
        if not relevant_symbols:
             self.write_log("No relevant symbols found in factor data.", level=DEBUG)
             return None
        df = df.loc[relevant_symbols]

        # Filter for required factors if specified
        if self.required_factors:
            available_factors = [f for f in self.required_factors if f in df.columns]
            if not available_factors:
                 self.write_log(f"None of the required factors {self.required_factors} found in data.", level=WARNING)
                 return None
            df = df[available_factors]

        if df.empty:
            self.write_log("Factor DataFrame is empty after filtering.", level=DEBUG)
            return None

        self.latest_factor_data = df # Cache the processed data

        # --- Core Logic ---
        try:
            # 1. Calculate Signals
            signals: pd.Series = self.calculate(df)
            if not isinstance(signals, pd.Series) or signals.empty:
                 self.write_log("Signal calculation returned empty or invalid result.", level=WARNING)
                 return None

            # 2. Project Signals to Target Weights
            target_weights: pd.Series = self.project_signals_to_weights(signals)
            if not isinstance(target_weights, pd.Series) or target_weights.empty:
                 self.write_log("Weight projection returned empty or invalid result.", level=WARNING)
                 return None

            # Ensure weights are aligned with available factor symbols
            target_weights = target_weights.reindex(df.index).fillna(0.0)

            # 3. Calculate Target Positions in Quote Currency (e.g., USD)
            if not self.portfolio_result:
                 self.write_log("Cannot calculate target positions: PortfolioResult not available.", level=ERROR)
                 return None

            total_portfolio_value = self.portfolio_result.get_total_value()
            if total_portfolio_value <= 0:
                 self.write_log(f"Cannot calculate target positions: Total portfolio value is {total_portfolio_value:.2f}", level=WARNING)
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
                 self.write_log(f"Symbol {vt_symbol} from target weights not in strategy's vt_symbols list. Skipping.", level=WARNING)
                 continue

            # Get necessary data
            tick = self.get_tick(vt_symbol)
            contract = self.get_contract(vt_symbol)

            if not tick or not tick.last_price or tick.last_price <= 0:
                self.write_log(f"Skipping order generation for {vt_symbol}: Missing or invalid last price in tick data.", level=WARNING)
                continue
            if not contract:
                self.write_log(f"Skipping order generation for {vt_symbol}: Contract details not found.", level=WARNING)
                continue

            last_price = tick.last_price
            price_tick = contract.pricetick or 0.00000001 # Use small default if not available
            size = contract.size or 1 # Contract multiplier

            # Get current position (in base currency units)
            current_pos_base = self.strategy_engine.get_portfolio_position(self.strategy_name, vt_symbol)

            # Calculate target position in base currency units
            target_pos_quote = target_positions_quote.get(vt_symbol, 0.0)
            target_pos_base = target_pos_quote / (last_price * size) # Adjust for contract size

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
                continue # Difference is too small, no order needed

            # Round volume to contract's volume step (if available, otherwise use reasonable precision)
            volume_tick = getattr(contract, 'volumetick', None) # Check if volumetick exists
            if volume_tick and volume_tick > 0:
                 volume = round_to(volume, volume_tick)
            else:
                 # Default rounding if volumetick is not available
                 volume = round(volume, 8) # Adjust precision as needed

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
                offset=Offset.NONE, # Assuming no offset needed for portfolio adjustments
                type=order_type,
                price=order_price,
                volume=volume,
                reference=self.strategy_name # Engine will set this, but good practice
            )
            order_reqs.append(req)
            self.write_log(f"Generated Order: {req.vt_symbol} {req.direction} {req.volume:.6f} @ {req.price:.6f}", level=DEBUG)

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

            if abs(current_pos) > min_order_volume: # Check if position is significant
                contract = self.get_contract(vt_symbol)
                if not contract:
                     self.write_log(f"Cannot close position for {vt_symbol}: Contract not found.", level=WARNING)
                     continue

                direction: Direction
                if current_pos > 0: # Long position, need to sell
                    direction = Direction.SHORT
                else: # Short position, need to buy back
                    direction = Direction.LONG

                # Round volume (absolute value)
                volume = abs(current_pos)
                volume_tick = getattr(contract, 'volumetick', None)
                if volume_tick and volume_tick > 0:
                    volume = round_to(volume, volume_tick)
                else:
                    volume = round(volume, 8)

                if volume < min_order_volume: continue # Skip if rounded volume is too small

                # Use MARKET order for closing positions quickly
                req = OrderRequest(
                    symbol=contract.symbol,
                    exchange=contract.exchange,
                    direction=direction,
                    offset=Offset.NONE, # Or Offset.CLOSE if required by exchange/gateway
                    type=OrderType.MARKET,
                    price=0, # Market orders don't need price
                    volume=volume,
                    reference=self.strategy_name
                )
                order_reqs.append(req)
                self.write_log(f"Generated Close Order: {req.vt_symbol} {req.direction} {req.volume:.6f} (Current Pos: {current_pos:.6f})", level=INFO)

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
        offset: Offset = Offset.NONE, # Default to OPEN/NONE
        lock: bool = False, # Pass through lock/net if needed by engine/agent
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
        volume_tick = contract.volumetick or 0.00000001 # Use small default if not specified
        min_volume = contract.min_volume or volume_tick # Minimum order size

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
            reference=self.strategy_name # Engine will ensure this is set
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
             self.write_log(f"Cancel request ignored: Order ID {vt_orderid} not found in this strategy's active orders.", level=WARNING)
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
                  self.write_log(f"Cancel request ignored: Order {vt_orderid} is already inactive (Status: {order.status}).", level=DEBUG)
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

        self.write_log(f"Cancelling all {len(self.active_order_ids)} active orders tracked by this strategy...", level=INFO)
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
                 params[name] = value.__dict__ # Convert config object to dict
             elif isinstance(value, list):
                 params[name] = list(value) # Ensure lists are copied
             elif isinstance(value, set):
                  params[name] = list(value) # Convert sets to lists for JSON
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
            "active_order_ids": list(self.active_order_ids), # Save active orders
            "latest_factor_update_time": self.latest_factor_update_time.isoformat() if self.latest_factor_update_time else None,
            # Optionally save latest factor data (can be large!)
            # "latest_factor_data": self.latest_factor_data.to_dict() if self.latest_factor_data is not None else None,
        }
        # Add variables defined in the 'variables' list
        for name in self.variables:
             if name not in data: # Avoid overwriting core state
                  value = getattr(self, name, None)
                  # Ensure value is serializable (basic types, lists, dicts)
                  if isinstance(value, (bool, int, float, str, list, dict, type(None))):
                       data[name] = value
                  elif isinstance(value, datetime):
                       data[name] = value.isoformat()
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

        # Restore latest factor time
        time_str = data.get("latest_factor_update_time")
        if time_str:
             try:
                  self.latest_factor_update_time = datetime.fromisoformat(time_str)
             except (TypeError, ValueError):
                  self.write_log(f"Could not parse saved factor update time: {time_str}", level=WARNING)

        # Restore other variables defined in the 'variables' list
        for name in self.variables:
             if name in data:
                  value = data[name]
                  # Handle potential type conversions (e.g., ISO string back to datetime)
                  if "time" in name.lower() and isinstance(value, str):
                       try:
                            setattr(self, name, datetime.fromisoformat(value))
                       except (TypeError, ValueError):
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
            self.vt_symbols = list(setting["vt_symbols"]) # Update symbol list

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

