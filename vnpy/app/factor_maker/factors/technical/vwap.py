from typing import Any, Dict, Optional

import polars as pl

from vnpy.trader.constant import Interval
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.factors.bar.open import OPEN
from vnpy.app.factor_maker.factors.bar.volume import VOLUME


class VWAP(FactorTemplate):
    factor_name = 'vwap'
    dependencies_factor = []
    freq = Interval.MINUTE

    def __init__(self, setting, window: int = None):
        super().__init__(setting, window=window)

    def __init_dependencies__(self):
        self.open = OPEN({})
        self.volume = VOLUME({})
        setattr(self, 'dependencies_factor', [self.open, self.volume])

    def calculate(self, input_data: Dict[str, Any], memory: Optional[pl.DataFrame] = None, *args,
                  **kwargs) -> pl.DataFrame:
        """
        Calculate the rolling VWAP (Volume Weighted Average Price) for Live Trading or Backtesting.

        Parameters:
            input_data (Dict[str, Any]): Input bar_data with keys for 'open' and 'volume' from dependent factors.
            memory (Optional[pl.DataFrame]): Current factor memory (used in Live Trading mode).

        Returns:
            pl.DataFrame: Updated VWAP DataFrame.
        """
        # Retrieve open and volume data
        open_prices = input_data.get(self.open.factor_key)
        volumes = input_data.get(self.volume.factor_key)

        # Ensure both are Polars DataFrames
        if not isinstance(open_prices, pl.DataFrame) or not isinstance(volumes, pl.DataFrame):
            raise ValueError("Both open and volume bar_data must be Polars DataFrames.")

        # Check for rolling window
        window = self.params.get_parameter('window')
        if window is None:
            raise ValueError("The rolling window size (window) is not set.")

        if memory is not None:
            # Live Trading Mode
            # Get tail(window) of the input data
            open_tail = open_prices.tail(window)
            volume_tail = volumes.tail(window)

            # Drop the datetime column for calculation
            datetime_col = open_tail["datetime"].tail(1)  # Latest datetime
            open_tail = open_tail.drop("datetime")
            volume_tail = volume_tail.drop("datetime")

            # Calculate VWAP for the latest row
            weighted_prices = open_tail * volume_tail
            sum_weighted = weighted_prices.sum(axis=0)
            sum_volume = volume_tail.sum(axis=0)
            latest_vwap = sum_weighted / sum_volume

            # Append the latest VWAP to memory
            new_row = pl.DataFrame({
                "datetime": datetime_col,
                **{col: [latest_vwap[col]] for col in latest_vwap.columns}
            })
            memory = pl.concat([memory, new_row], how="vertical")  # Keep memory within window size
            return memory
        else:
            # Backtesting Mode
            # Preserve the datetime column
            datetime_col = None
            if "datetime" in open_prices.columns and "datetime" in volumes.columns:
                datetime_col = open_prices["datetime"]
                open_prices = open_prices.drop("datetime")
                volumes = volumes.drop("datetime")

            # Calculate VWAP: rolling sum(open * volume) / rolling sum(volume)
            weighted_prices = open_prices * volumes
            rolling_sum_weighted = weighted_prices.select([
                pl.col(col).rolling_sum(window).alias(col) for col in weighted_prices.columns
            ])
            rolling_sum_volume = volumes.select([
                pl.col(col).rolling_sum(window).alias(col) for col in volumes.columns
            ])
            vwap = rolling_sum_weighted / rolling_sum_volume

            # Add the datetime column back to the result if it exists
            if datetime_col is not None:
                vwap = vwap.insert_column(0, datetime_col)

            return vwap

    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        pass
