from vnpy.app.factor_maker.factors.bar.bar_base import BarFactor
from vnpy.trader.object import TickData, BarData, Exchange, Interval, FactorData
from typing import Optional
from typing import Optional, Union, Dict, Any

import polars as pl

from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.trader.constant import Interval
from vnpy.app.factor_maker.base import FactorMode

class VOLUME(FactorTemplate):
    factor_name = 'volume'
    dependencies_factor = []
    freq = Interval.MINUTE
    factor_mode = FactorMode.Backtest

    def __init__(self, setting, **kwargs):
        """
        Initialize the VOLUME factor with its settings.
        """
        super().__init__(setting, **kwargs)

    def __init_dependencies__(self):
        """
        Define dependencies for the VOLUME factor (none in this case).
        """
        pass

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, Any]]],
                  memory: Optional[pl.DataFrame] = None, *args, **kwargs) -> Any:
        """
        Return the 'volume' data for Live Trading or Backtesting.

        Parameters:
            input_data (Optional[Union[pl.DataFrame, Dict[str, Any]]]): Input data containing 'volume'.
            memory (Optional[pl.DataFrame]): Unused for this factor but kept for uniformity.

        Returns:
            pl.DataFrame: Volume data.
        """
        # Validate factor_mode
        if self.factor_mode not in [FactorMode.Backtest, FactorMode.Live]:
            raise ValueError("Invalid factor_mode. Must be 'Backtest' or 'Live'.")

        # Retrieve the 'volume' data
        if isinstance(input_data, dict):
            volume_data = input_data.get('volume')
        elif isinstance(input_data, pl.DataFrame):
            volume_data = input_data
        else:
            raise ValueError("Invalid input_data format. Expected pl.DataFrame or Dict[str, pl.DataFrame].")

        # Ensure the data is a Polars DataFrame
        if not isinstance(volume_data, pl.DataFrame):
            raise ValueError("'volume' data must be a Polars DataFrame.")

        return volume_data

    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        pass