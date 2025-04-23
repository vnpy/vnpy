# portfolio_manager/base.py
import logging
from typing import Dict, List, Optional, Union, Any, TYPE_CHECKING
from decimal import Decimal
import numpy as np
import pandas as pd
from datetime import datetime, date, timezone # Added timezone

from vnpy.trader.object import TickData, TradeData, ContractData
from vnpy.trader.constant import Direction

# Define constants for dictionary keys used in persistence and other literals
DATE_KEY = "date"
DATA_KEY = "data"
OPEN_POS_KEY = "open_pos"
LAST_POS_KEY = "last_pos"
TIMER_INTERVAL_KEY = "timer_interval"
TIMESTAMP_FORMAT = "%Y-%m-%d %H:%M:%S.%f" # Include microseconds for stats precision

# Set up logger for the application
# This assumes vnpy's logging is configured elsewhere or basicConfig is called.
# Using __name__.split('.')[0] gets the root package name if called from within the package.
logger = logging.getLogger("PortfolioManagerApp") # Use a specific name


class ContractResult:
    """
    Calculates and stores position, PnL, and cost basis for a specific contract
    within a portfolio. Includes daily rollover logic based on UTC time.
    """

    def __init__(
        self,
        reference: str,
        vt_symbol: str,
        open_pos: float = 0.0  # Use float consistently
    ) -> None:
        """
        Initialize ContractResult.

        Parameters
        ----------
        reference : str
            Portfolio reference identifier.
        vt_symbol : str
            Virtual trading symbol for contract identification.
        open_pos : float, optional
            Initial position at the start of the period (e.g., day), defaults to 0.0.
        """
        # Input validation
        if not isinstance(reference, str) or not reference:
            raise ValueError("reference must be a non-empty string")
        if not isinstance(vt_symbol, str) or not vt_symbol:
            raise ValueError("vt_symbol must be a non-empty string")
        if not isinstance(open_pos, (float, int)):
            raise ValueError("open_pos must be a number")

        self.reference: str = reference
        self.vt_symbol: str = vt_symbol

        # Positions
        self.open_pos: float = float(open_pos)  # Position at the start of the current UTC day
        self.last_pos: float = float(open_pos)  # Current position after trades

        # PnL Metrics
        self.trading_pnl: float = 0.0    # Realized PnL from trades intra-day (since last UTC rollover)
        self.holding_pnl: float = 0.0    # Unrealized PnL based on open_pos vs open_price_basis
        self.total_pnl: float = 0.0      # Sum of trading and holding PnL for the day
        self.value: float = 0.0          # Market value of the current position

        # Pricing Basis
        self.open_price_basis: float = 0.0 # Price used as basis for current day's holding PnL
                                           # Set during rollover_day using previous UTC day's close.
        self.last_known_price: float = 0.0 # Store the last price used in PnL calc

        # Trade Tracking
        self.trades: Dict[str, TradeData] = {}  # All trades processed {vt_tradeid: TradeData}
        self.new_trades: List[TradeData] = []   # Trades received since last PnL calculation

        # Intra-day Cost Basis Tracking (Reset daily via rollover)
        self.long_volume_traded: float = 0.0
        self.short_volume_traded: float = 0.0
        self.long_cost_traded: float = 0.0
        self.short_cost_traded: float = 0.0

    def update_trade(self, trade: TradeData) -> None:
        """
        Process a new trade, update position, and add to new_trades buffer.
        Filters duplicate trades based on vt_tradeid.
        """
        if trade.vt_tradeid in self.trades:
            return
        self.trades[trade.vt_tradeid] = trade
        self.new_trades.append(trade)

        # Update last known position
        if trade.direction == Direction.LONG:
            self.last_pos += trade.volume
        else:
            self.last_pos -= trade.volume

    def rollover_day(self, previous_close_price: float) -> None:
        """
        Perform daily rollover (triggered by engine at UTC midnight):
        - Update open position to yesterday's closing position.
        - Set new price basis using yesterday's closing price.
        - Reset all intra-day counters (PnL, costs, volumes).
        """
        logger.info(f"[{self.reference}|{self.vt_symbol}] Rolling over UTC day. Last Pos: {self.last_pos}, Prev Close (New Basis): {previous_close_price}")

        # Update open position to yesterday's closing position
        self.open_pos = self.last_pos

        # Set the price basis for the new day's holding PnL calculation
        self.open_price_basis = previous_close_price

        # Reset intra-day accumulators
        self.trading_pnl = 0.0
        self.holding_pnl = 0.0  # Will be recalculated based on new basis
        self.total_pnl = 0.0
        self.value = 0.0        # Will be recalculated

        self.long_volume_traded = 0.0
        self.short_volume_traded = 0.0
        self.long_cost_traded = 0.0
        self.short_cost_traded = 0.0

        # Optional: Clear new_trades buffer. Should be empty if PnL calc ran before rollover.
        self.new_trades.clear()

    def calculate_pnl(
        self,
        tick: Optional[TickData],
        contract: Optional[ContractData]
    ) -> bool:
        """
        Calculate PnL metrics based on market data and processed trades.
        Uses open_price_basis for holding PnL calculation.

        Parameters
        ----------
        tick : Optional[TickData]
            Latest tick data for the contract.
        contract : Optional[ContractData]
            Contract details (especially size).

        Returns
        -------
        bool
            True if PnL calculation was successful, False otherwise.
        """
        # --- Initial Data Validation ---
        if not contract:
            # Logged by the engine before calling usually, but double-check
            # logger.error(f"[{self.reference}|{self.vt_symbol}] Cannot calculate PnL: Contract data missing.")
            return False
        if not tick:
            # logger.debug(f"[{self.reference}|{self.vt_symbol}] Cannot calculate PnL: Tick data missing.")
            return False
        if not tick.last_price or not isinstance(tick.last_price, (float, int)):
             logger.warning(f"[{self.reference}|{self.vt_symbol}] Cannot calculate PnL: Invalid or missing last_price in tick.")
             return False

        # Store last known price
        last_price: float = tick.last_price
        self.last_known_price = last_price
        size: float = contract.size

        # Determine the effective basis for holding PnL
        effective_open_basis = self.open_price_basis
        # If open_price_basis hasn't been set by rollover yet (e.g., first run), use pre_close
        if effective_open_basis == 0.0:
            if tick.open_price and isinstance(tick.open_price, (float, int)):
                logger.info(f"[{self.reference}|{self.vt_symbol}] Using tick.pre_close ({tick.open_price}) as initial open basis for Holding PnL.")
                effective_open_basis = tick.open_price
            else:
                logger.warning(f"[{self.reference}|{self.vt_symbol}] open_price_basis is 0, and tick.pre_close is unavailable. Using current last_price ({last_price}) as Holding PnL basis until rollover.")
                effective_open_basis = last_price # Fallback to current price

        # --- Process New Trades ---
        # Calculate cost impact of trades occurred since last calculation
        for trade in self.new_trades:
            trade_value: float = trade.price * trade.volume * size
            if trade.direction == Direction.LONG:
                self.long_volume_traded += trade.volume
                self.long_cost_traded += trade_value
            else:
                self.short_volume_traded += trade.volume
                self.short_cost_traded += trade_value
        self.new_trades.clear() # Clear buffer after processing

        # --- Calculate Trading PnL ---
        # PnL realized from trades executed during the current UTC day
        long_value_now = self.long_volume_traded * last_price * size
        short_value_now = self.short_volume_traded * last_price * size
        long_pnl = long_value_now - self.long_cost_traded
        short_pnl = self.short_cost_traded - short_value_now # (Proceeds - Current Value of sold qty)
        self.trading_pnl = long_pnl + short_pnl

        # --- Calculate Holding PnL ---
        # PnL from the position held since the start of the current UTC day (open_pos)
        # Based on change from the established open_price_basis
        self.holding_pnl = (last_price - effective_open_basis) * self.open_pos * size

        # --- Calculate Total PnL & Value ---
        self.total_pnl = self.trading_pnl + self.holding_pnl
        self.value = self.last_pos * last_price * size # Market value of current position

        return True

    def get_data(self) -> dict:
        """Get the current state of the contract result as a dictionary."""
        data: dict = {
            "reference": self.reference,
            "vt_symbol": self.vt_symbol,
            OPEN_POS_KEY: self.open_pos,
            LAST_POS_KEY: self.last_pos,
            "trading_pnl": self.trading_pnl,
            "holding_pnl": self.holding_pnl,
            "total_pnl": self.total_pnl,
            "value": self.value,
            "long_volume_traded": self.long_volume_traded,
            "short_volume_traded": self.short_volume_traded,
            "long_cost_traded": self.long_cost_traded,
            "short_cost_traded": self.short_cost_traded,
            "open_price_basis": self.open_price_basis, # Add for visibility/debugging
            "last_known_price": self.last_known_price, # Add for visibility/debugging
        }
        return data


class PortfolioResult:
    """
    Aggregates PnL and value for all contracts within a specific portfolio
    for the current UTC day.
    """

    def __init__(self, reference: str) -> None:
        """Initialize PortfolioResult."""
        if not isinstance(reference, str) or not reference:
            raise ValueError("reference must be a non-empty string")

        self.reference: str = reference
        self.trading_pnl: float = 0.0  # Aggregated intra-day trading PnL
        self.holding_pnl: float = 0.0  # Aggregated holding PnL for the day
        self.total_pnl: float = 0.0    # Aggregated total PnL for the day
        self.value: float = 0.0        # Aggregated current market value

    def clear_pnl_and_value(self) -> None:
        """Reset all aggregated PnL values and total value to zero (called before recalculation)."""
        self.trading_pnl = 0.0
        self.holding_pnl = 0.0
        self.total_pnl = 0.0
        self.value = 0.0

    def get_total_value(self) -> float:
        """Get the aggregated total market value of the portfolio."""
        return self.value

    def get_data(self) -> dict:
        """Get the current aggregated state of the portfolio result."""
        data: dict = {
            "reference": self.reference,
            "trading_pnl": self.trading_pnl,
            "holding_pnl": self.holding_pnl,
            "total_pnl": self.total_pnl,
            "value": self.value,
        }
        return data


class PortfolioStatistics:
    """
    Calculates and stores time-series statistics for a portfolio value.
    Uses precise timestamps for recording values and pandas for calculations.
    """

    TIMESTAMP_FORMAT = "%Y-%m-%d %H:%M:%S.%f"  # Include microseconds for precision

    def __init__(self, reference: str) -> None:
        """Initialize PortfolioStatistics."""
        if not isinstance(reference, str) or not reference:
            raise ValueError("reference must be a non-empty string")
        self.reference: str = reference
        # Store values with datetime objects as keys for easier manipulation
        self.values_over_time: Dict[datetime, float] = {}

    def record_value(self, timestamp: datetime, value: float) -> None:
        """
        Record the portfolio value at a specific point in time.

        Parameters
        ----------
        timestamp : datetime
            Precise timestamp of the value record (ideally timezone-aware).
        value : float
            Portfolio value at the given timestamp.
        """
        if not isinstance(timestamp, datetime):
            # Ensure timestamp is datetime object
            logger.warning(f"[{self.reference}] Invalid timestamp type for record_value: {type(timestamp)}. Expected datetime.")
            # Attempt conversion or raise error? For now, log and potentially skip.
            # Or try basic conversion if possible:
            # if isinstance(timestamp, str): try timestamp = datetime.fromisoformat(timestamp) ...
            return # Skip if not datetime
        if not isinstance(value, (float, int)):
             logger.warning(f"[{self.reference}] Invalid value type for record_value: {type(value)}. Expected number.")
             return # Skip if not number

        # Use UTC for internal storage consistency? Or keep local time?
        # Let's assume the timestamp passed in is the one desired (e.g., local time from engine).
        self.values_over_time[timestamp] = value

    def get_values_as_series(self) -> pd.Series:
        """Convert the recorded values dictionary to a pandas Series, sorted by time."""
        if not self.values_over_time:
            return pd.Series(dtype=float)

        # Create Series from dict items, explicitly set index and sort
        try:
            s = pd.Series(list(self.values_over_time.values()), index=list(self.values_over_time.keys()), dtype=float)
            s = s.sort_index()
            # Ensure index is DatetimeIndex
            if not isinstance(s.index, pd.DatetimeIndex):
                s.index = pd.to_datetime(s.index)
            return s
        except Exception as e:
            logger.error(f"[{self.reference}] Error converting values to pandas Series: {e}")
            return pd.Series(dtype=float)

    def resample_values(self, frequency: str = "D") -> pd.Series:
        """
        Resample the recorded portfolio values to a specified frequency.
        Uses last value in the period and forward fills missing data.
        """
        value_series = self.get_values_as_series()
        if value_series.empty:
            # logger.warning(f"[{self.reference}] No data available for resampling.") # Too noisy maybe
            return pd.Series(dtype=float)

        try:
            # Resample using 'last' and forward fill
            resampled_data = value_series.resample(frequency).last()
            resampled_data = resampled_data.ffill()
            return resampled_data
        except ValueError as e:
             logger.error(f"[{self.reference}] Invalid frequency '{frequency}' for resampling: {e}")
             return pd.Series(dtype=float)
        except Exception as e:
            logger.error(f"[{self.reference}] Error during resampling with frequency '{frequency}': {e}")
            return pd.Series(dtype=float)


    def calculate_sharpe_ratio(self, risk_free_rate: float = 0.0, frequency: str = "D", periods_per_year: int = 252) -> Optional[float]:
        """
        Calculate the annualized Sharpe Ratio based on resampled returns.
        """
        resampled_data = self.resample_values(frequency)
        if len(resampled_data) < 2:
            # logger.warning(f"[{self.reference}] Not enough data points ({len(resampled_data)}) to calculate Sharpe Ratio.")
            return None

        try:
            returns = resampled_data.pct_change().dropna()
            if returns.empty:
                 # logger.warning(f"[{self.reference}] No returns calculated after resampling/dropping NaNs for Sharpe Ratio.")
                 return None

            std_dev = returns.std()
            if std_dev == 0 or np.isnan(std_dev) or std_dev < 1e-10: # Check for effectively zero std dev
                # logger.warning(f"[{self.reference}] Standard deviation of returns is zero or invalid ({std_dev}), cannot calculate Sharpe Ratio.")
                return 0.0 if returns.mean() == 0 else np.inf if returns.mean() > 0 else -np.inf # Or return None? Sharpe is ill-defined. Let's return None.
                # return None

            # Calculate excess returns per period
            excess_returns = returns - (risk_free_rate / periods_per_year)
            sharpe_ratio = excess_returns.mean() / std_dev

            # Annualize the Sharpe Ratio
            annualized_sharpe = sharpe_ratio * np.sqrt(periods_per_year)
            return annualized_sharpe
        except Exception as e:
            logger.error(f"[{self.reference}] Error calculating Sharpe Ratio: {e}")
            return None

    def calculate_max_drawdown(self, frequency: str = "D") -> Optional[float]:
        """
        Calculate the maximum drawdown based on resampled portfolio values.
        """
        resampled_data = self.resample_values(frequency)
        if len(resampled_data) < 2:
            # logger.warning(f"[{self.reference}] Not enough data points ({len(resampled_data)}) to calculate Max Drawdown.")
            return None

        try:
            values = resampled_data.values
            if len(values) == 0 or np.all(np.isnan(values)):
                return None
            if np.all(values == 0): # Avoid division by zero if all values are 0
                return 0.0

            cumulative_max = np.maximum.accumulate(values)
            # Handle potential zero values in cumulative_max to avoid division by zero
            # Use np.fmax to avoid replacing valid small peaks with 1
            valid_peak = np.fmax(cumulative_max, 1e-10) # Use a small number instead of 1

            drawdown = (values - cumulative_max) / valid_peak
            max_drawdown = np.min(drawdown[~np.isnan(drawdown)]) # Ignore NaNs if any from division

            if np.isnan(max_drawdown): return None # If all drawdowns were NaN

            return float(max_drawdown) # Ensure return type is float

        except Exception as e:
            logger.error(f"[{self.reference}] Error calculating Max Drawdown: {e}")
            return None


    def get_statistics(self, frequency: str = "D", periods_per_year: int = 252) -> dict:
        """
        Get all calculated statistics based on resampled values.
        """
        return {
            "reference": self.reference,
            "sharpe_ratio": self.calculate_sharpe_ratio(frequency=frequency, periods_per_year=periods_per_year),
            "max_drawdown": self.calculate_max_drawdown(frequency=frequency),
            # Add other statistics here if needed
        }

    def get_data_for_save(self) -> Dict[str, float]:
        """Return statistics value data suitable for saving (e.g., to JSON). Converts datetime keys to strings."""
        return {dt.strftime(TIMESTAMP_FORMAT): val for dt, val in self.values_over_time.items()}

    @classmethod
    def from_saved_data(cls, reference: str, saved_data: Dict[str, Any]) -> "PortfolioStatistics":
        """Create an instance from saved data (dict with string timestamps). Handles potential non-float values."""
        instance = cls(reference)
        loaded_values = {}
        for ts_str, val in saved_data.items():
            try:
                # Ensure value is float, skip if not convertible
                float_val = float(val)
                dt = datetime.strptime(ts_str, cls.TIMESTAMP_FORMAT)
                loaded_values[dt] = float_val
            except (ValueError, TypeError) as e:
                 logger.warning(f"[{reference}] Skipping invalid data point during statistics load: timestamp='{ts_str}', value='{val}'. Error: {e}")
            except Exception as e:
                 logger.error(f"[{reference}] Unexpected error loading statistics data point: timestamp='{ts_str}', value='{val}'. Error: {e}")

        instance.values_over_time = loaded_values
        return instance