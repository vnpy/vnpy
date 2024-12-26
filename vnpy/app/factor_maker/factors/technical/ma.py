import polars as pl
from typing import Any, Dict

from vnpy.trader.object import TickData, BarData, Exchange, Interval, FactorData
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.factors.bar import *
from typing import Optional, Union, Dict, Any

import polars as pl

from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.trader.constant import Interval
from vnpy.app.factor_maker.base import FactorMode
from vnpy.app.factor_maker.factors.technical.vwap import VWAP


#
# class MA_BASE(FactorTemplate):
#     factor_name = "ma"
#     author: str = "EvanHong"
#
#     def __init_dependencies__(self):
#         pass
#
#     def __init__(self, setting, window=None):
#         super().__init__(setting, window=window)


class MA(FactorTemplate):
    factor_name = 'ma'
    dependencies_factor = []
    freq = Interval.MINUTE
    factor_mode = FactorMode.Backtest

    def __init__(self, setting, window: int = None, **kwargs):
        """
        Initialize the MA factor with its settings and rolling window size.
        """
        super().__init__(setting, window=window, **kwargs)

    def __init_dependencies__(self):
        super().__init_dependencies__()

        self.target = self.dependencies_factor[0]

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, pl.DataFrame]]],
                  memory: Optional[pl.DataFrame] = None, *args, **kwargs) -> Any:
        """
        Calculate the rolling mean for all columns in the input data for Live Trading or Backtesting.

        Parameters:
            input_data (Optional[Union[pl.DataFrame, Dict[str, pl.DataFrame]]]): Input data with symbols as columns.
            memory (Optional[pl.DataFrame]): Current factor memory (used in Live Trading mode).

        Returns:
            pl.DataFrame: DataFrame with the rolling mean for each symbol.
        """
        # Validate factor_mode
        if self.factor_mode not in [FactorMode.Backtest, FactorMode.Live]:
            raise ValueError("Invalid factor_mode. Must be 'Backtest' or 'Live'.")

        # Retrieve input data
        if isinstance(input_data, dict):
            df = input_data.get(self.target.factor_key)
        elif isinstance(input_data, pl.DataFrame):
            df = input_data
        else:
            raise ValueError("Invalid input_data format. Expected pl.DataFrame or Dict[str, pl.DataFrame].")

        # Ensure the input data is a Polars DataFrame
        if not isinstance(df, pl.DataFrame):
            raise ValueError("Input data must be a Polars DataFrame.")

        # Get the rolling window size
        window = self.params.get_parameter('window')
        if window is None:
            raise ValueError("The rolling window size (window) is not set.")

        if self.factor_mode == FactorMode.Live:
            # Live Mode: Ensure memory is provided
            if memory is None:
                raise ValueError("Memory must be provided in 'Live' mode.")

            # Get tail(window) of the input data
            latest_data = df.tail(window)

            # Drop the datetime column for calculation
            datetime_col = latest_data["datetime"].tail(1)  # Latest datetime
            latest_data = latest_data.drop("datetime")

            # Calculate rolling mean for the latest row
            rolling_means = latest_data.mean(axis=0)

            # Create a new row for the memory update
            new_row = pl.DataFrame({
                "datetime": datetime_col,
                **{col: [rolling_means[col]] for col in latest_data.columns}
            })

            # Update memory
            memory = pl.concat([memory, new_row], how="vertical")
            return memory

        elif self.factor_mode == FactorMode.Backtest:
            # Backtesting Mode: Perform calculations on the entire dataset
            # Preserve datetime column
            datetime_col = None
            if "datetime" in df.columns:
                datetime_col = df["datetime"]
                df = df.drop("datetime")

            # Calculate rolling mean for all columns except datetime
            columns_to_aggregate = [col for col in df.columns if col != 'datetime']
            rolling_means = df.select([
                pl.col(col).rolling_mean(window).alias(col) for col in columns_to_aggregate
            ])

            # Add datetime column back to the result if it exists
            if datetime_col is not None:
                rolling_means = rolling_means.insert_column(0, datetime_col)

            return rolling_means
