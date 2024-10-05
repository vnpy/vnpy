from typing import Any, Dict, Optional
import numpy as np
import polars as pl

from vnpy.app.factor_maker.backtesting import FactorBacktestingEngine
from vnpy.app.factor_maker.engine import FactorEngine
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.trader.object import TickData, BarData, FactorData
from vnpy.trader.constant import Exchange, Interval

class MACDFactor(FactorTemplate):
    """
    MACD Factor class that calculates the MACD histogram as a factor.
    """

    author = "Your Name"
    factor_name = "MACD_Factor"
    parameters = ["fast_period", "slow_period", "signal_period"]
    variables = []

    def __init__(self, engine: Optional[FactorEngine, FactorBacktestingEngine], setting: Dict[str, Any], **kwargs):
        """
        Initialize the MACD factor with the given engine and settings.

        Parameters:
            engine (Optional[FactorEngine, FactorBacktestingEngine]): The factor engine instance.
            setting (dict): Settings for the factor.
        """
        super().__init__(engine, setting, **kwargs)

        # Default MACD parameters
        self.fast_period: int = setting.get("fast_period", 12)
        self.slow_period: int = setting.get("slow_period", 26)
        self.signal_period: int = setting.get("signal_period", 9)

    def on_tick(self, tick: TickData) -> None:
        """
        Callback of new tick data update.
        Not implemented for this factor.
        """
        pass

    def on_bar(self, bar: BarData) -> None:
        """
        Callback of new bar data update.
        Not implemented for this factor.
        """
        pass

    def on_factor(self, factor: FactorData) -> None:
        """
        Callback of new factor data update (from dependencies).
        Not implemented for this factor.
        """
        pass

    def calculate_polars(self, close_df: pl.DataFrame, *args, **kwargs) -> pl.DataFrame:
        """
        Calculate MACD histogram using Polars DataFrame.

        Parameters:
            close_df (pl.DataFrame): DataFrame with 'datetime' as index and symbols as columns containing close prices.

        Returns:
            pl.DataFrame: DataFrame with 'datetime' as index and symbols as columns containing MACD histogram values.
        """
        # Ensure 'datetime' is a column (since Polars does not have index)
        if 'datetime' not in close_df.columns:
            raise ValueError("The 'close' DataFrame must contain a 'datetime' column.")

        # Sort data by 'datetime'
        close_df = close_df.sort("datetime")

        # Get the list of symbols (columns excluding 'datetime')
        symbols = [col for col in close_df.columns if col != 'datetime']

        # Initialize a dictionary to hold MACD histograms
        macd_hist_dict = {'datetime': close_df['datetime']}

        for symbol in symbols:
            # Extract close prices for the symbol
            close_prices: pl.Series = close_df[symbol]

            # Handle missing data
            if close_prices.null_count() == len(close_prices):
                # All values are null for this symbol; skip it
                continue

            # Calculate alpha values
            alpha_fast = 2 / (self.fast_period + 1)
            alpha_slow = 2 / (self.slow_period + 1)
            alpha_signal = 2 / (self.signal_period + 1)

            # Calculate EMAs using Polars ewm_mean
            ema_fast = close_prices.ewm_mean(alpha=alpha_fast, adjust=False, min_periods=1)
            ema_slow = close_prices.ewm_mean(alpha=alpha_slow, adjust=False, min_periods=1)
            macd_line = ema_fast - ema_slow
            signal_line = macd_line.ewm_mean(alpha=alpha_signal, adjust=False, min_periods=1)
            macd_histogram = macd_line - signal_line

            # Add to the dictionary
            macd_hist_dict[symbol] = macd_histogram

        # Create the result DataFrame
        result = pl.DataFrame(macd_hist_dict)

        # Sort by 'datetime'
        result = result.sort("datetime")

        return result

    def make_factor(self, bar_data_dict: Dict[str, pl.DataFrame]) -> pl.DataFrame:
        """
        Generate MACD factor values from historical bar data.

        Parameters:
            bar_data_dict (dict[str, pl.DataFrame]): Dictionary with keys 'open', 'high', 'low', 'close'.
                Each DataFrame has 'datetime' as index and symbols as columns.

        Returns:
            pl.DataFrame: DataFrame with 'datetime' as index and symbols as columns containing MACD histogram values.
        """
        # Extract close prices DataFrame
        close_df = bar_data_dict.get('close')
        if close_df is None:
            raise ValueError("bar_data_dict must contain a 'close' DataFrame.")

        # Ensure 'datetime' is a column
        if 'datetime' not in close_df.columns:
            raise ValueError("The 'close' DataFrame must contain a 'datetime' column.")

        # Calculate MACD histogram for all symbols
        factor_data = self.calculate_polars(close_df)

        return factor_data