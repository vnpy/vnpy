from typing import Any, Dict, Optional, List, Type, Union
import numpy as np
import polars as pl

from vnpy.trader.object import TickData, BarData, FactorData
from vnpy.trader.constant import Exchange, Interval

from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.factors.technical.ma import MA


class MACD(FactorTemplate):
    """
    MACD Factor class that calculates the MACD histogram as a factor.
    """

    author = "Tester"
    factor_name = "macd"

    dependencies_factor: List[Type[FactorTemplate]] = [MA, MA]

    def __init_dependencies__(self):
        fast_period = self.params.get_parameter("fast_period")
        slow_period = self.params.get_parameter("slow_period")
        signal_period = self.params.get_parameter("signal_period")
        self.ma_fast = MA(setting={}, window=fast_period)
        self.ma_slow = MA(setting={}, window=slow_period)
        self.ma_signal = signal_period
        setattr(self, "dependencies_factor", [self.ma_fast, self.ma_slow])  # ÖØÐÂ¸²¸Çattribute

    def __init__(self, setting: Dict[str, Any],
                 fast_period: int = None,
                 slow_period: int = None,
                 signal_period: int = None,
                 ):
        """
        Initialize the MACD factor with the given engine and settings.

        Parameters:
            setting (dict): Settings for the factor.
        """
        super().__init__(setting=setting,
                         fast_period=fast_period,
                         slow_period=slow_period,
                         signal_period=signal_period,
                         )


    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, Any]]], *args, **kwargs) -> Any:
        """
        Calculate MACD histogram values from input data.

        Parameters:
            input_data (pl.DataFrame): DataFrame with 'datetime' as index and symbols as columns containing close prices.

        Returns:
            pl.DataFrame: DataFrame with 'datetime' as index and symbols as columns containing MACD histogram values.
        """
        if isinstance(input_data, dict):
            fast = input_data.get(self.ma_fast.factor_key)
            slow = input_data.get(self.ma_slow.factor_key)
            # compute macd
            macd = fast - slow

        else:
            raise ValueError("The input_data must be a dictionary.")

        return macd

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

    def calculate(self, input_data: Dict[str, pl.DataFrame], *args, **kwargs) -> Any:
        """
        Calculate MACD histogram values from input data.

        Parameters:
            input_data (pl.DataFrame): DataFrame with 'datetime' as index and symbols as columns containing close prices.

        Returns:
            pl.DataFrame: DataFrame with 'datetime' as index and symbols as columns containing MACD histogram values.
        """
        if isinstance(input_data, dict):
            fast = input_data.get(self.ma_fast.factor_key)
            slow = input_data.get(self.ma_slow.factor_key)
            # compute macd
            macd = fast - slow

        else:
            raise ValueError("The input_data must be a dictionary.")

        return macd