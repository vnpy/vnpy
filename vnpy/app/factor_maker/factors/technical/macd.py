from typing import Any, Dict, Optional, List, Type, Union
import numpy as np
import polars as pl

from vnpy.trader.object import TickData, BarData, FactorData
from vnpy.trader.constant import Exchange, Interval

from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.factors.technical.ma import MA
from typing import Optional, Union, Dict, Any

import polars as pl

from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.trader.constant import Interval
from vnpy.app.factor_maker.base import FactorMode


class MACD(FactorTemplate):
    factor_name = 'macd'
    dependencies_factor = []
    freq = Interval.MINUTE
    factor_mode = FactorMode.Backtest

    def __init__(self, setting, fast_period: int = None, slow_period: int = None, signal_period: int = None, **kwargs):
        """
        Initialize the MACD factor with settings and periods.
        """
        super().__init__(setting=setting, fast_period=fast_period, slow_period=slow_period, signal_period=signal_period, **kwargs)

    def __init_dependencies__(self):
        """
        Define dependencies for the MACD factor.
        """
        super().__init_dependencies__()
        # fixme: here we should bind the dependencies_factor with the variables by their classes and params
        # old version: specifically write down the class, with dynamic params
        # self.ma_fast = MA({}, self.params.get_parameter('fast_period'))
        # self.ma_slow = MA({}, self.params.get_parameter('slow_period'))
        # self.ma_fast.factor_mode = self.factor_mode
        # self.ma_slow.factor_mode = self.factor_mode
        # setattr(self, 'dependencies_factor', [self.ma_fast, self.ma_slow])

        # todo: new version: bind initialized factors with variables with some logic
        self.ma_fast = self.dependencies_factor[0]
        self.ma_slow = self.dependencies_factor[1]
        if not isinstance(self.ma_fast, MA) or not isinstance(self.ma_slow, MA):
            raise ValueError("Dependencies must be MA factors.")
        if self.ma_fast.params.get_parameter('window') > self.ma_slow.params.get_parameter('window'):
            self.ma_fast, self.ma_slow = self.ma_slow, self.ma_fast
        self.dependencies_factor = [self.ma_fast, self.ma_slow]

    def calculate(self, input_data: Optional[Dict[str, pl.DataFrame]], memory: Optional[pl.DataFrame] = None, *args,
                  **kwargs) -> pl.DataFrame:
        """
        Calculate MACD histogram for Live Trading or Backtesting.

        Parameters:
            input_data (Optional[Dict[str, pl.DataFrame]]): Input data containing pre-calculated MA fast and MA slow.
            memory (Optional[pl.DataFrame]): Memory for Live Trading mode.
            factor_mode (str): The mode of calculation ('Backtest' or 'Live').

        Returns:
            pl.DataFrame: Updated MACD histogram DataFrame with datetime column preserved.
        """
        # Validate factor_mode
        if self.factor_mode not in [FactorMode.Backtest, FactorMode.Live]:
            raise ValueError("Invalid factor_mode. Must be 'Backtest' or 'Live'.")

        # Retrieve pre-calculated moving averages
        ma_fast = input_data.get(self.ma_fast.factor_key)
        ma_slow = input_data.get(self.ma_slow.factor_key)

        if ma_fast is None or ma_slow is None:
            raise ValueError("Missing required moving averages (ma_fast or ma_slow) in input_data.")

        # Ensure moving averages are Polars DataFrames
        if not isinstance(ma_fast, pl.DataFrame) or not isinstance(ma_slow, pl.DataFrame):
            raise ValueError("ma_fast and ma_slow must be Polars DataFrames.")

        if self.factor_mode == FactorMode.Live:
            # Live Mode: Ensure memory is provided
            if memory is None:
                raise ValueError("Memory must be provided in 'Live' mode.")

            # Get tail(signal_period) of input data
            ma_fast_tail = ma_fast.tail(self.params.get_parameter('signal_period'))
            ma_slow_tail = ma_slow.tail(self.params.get_parameter('signal_period'))

            # Drop datetime column for calculation
            datetime_col = ma_fast_tail["datetime"].tail(1)  # Latest datetime
            ma_fast_tail = ma_fast_tail.drop("datetime")
            ma_slow_tail = ma_slow_tail.drop("datetime")

            # Calculate MACD line and signal line
            macd_line = ma_fast_tail - ma_slow_tail
            signal_line = macd_line.mean(axis=0)  # Use the mean of macd_line as signal line

            # Calculate histogram using the last row of macd_line - signal_line
            last_histogram = (macd_line.tail(1) - signal_line).to_dict(as_series=False)

            # Append the latest histogram to memory
            new_row = pl.DataFrame({
                "datetime": datetime_col,
                **{col: [last_histogram[col]] for col in macd_line.columns},
            })
            memory = pl.concat([memory, new_row], how="vertical")
            return memory

        elif self.factor_mode == FactorMode.Backtest:
            # Backtesting Mode: Perform calculations on the entire dataset
            # Preserve datetime column
            datetime_col = None
            if "datetime" in ma_fast.columns and "datetime" in ma_slow.columns:
                datetime_col = ma_fast["datetime"]
                ma_fast = ma_fast.drop("datetime")
                ma_slow = ma_slow.drop("datetime")

            # Calculate MACD line
            macd_line = ma_fast - ma_slow

            # Calculate Signal line using rolling mean of the MACD line
            signal_line = macd_line.select([
                pl.col(col).rolling_mean(self.params.get_parameter('signal_period')).alias(col)
                for col in macd_line.columns
            ])

            # Calculate Histogram (MACD line - Signal line)
            histogram = macd_line - signal_line

            # Add datetime column back to the histogram
            if datetime_col is not None:
                histogram = histogram.insert_column(0, datetime_col)

            return histogram
