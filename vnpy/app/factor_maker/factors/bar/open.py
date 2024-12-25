import polars as pl

from vnpy.app.factor_maker.factors.bar.bar_base import BarFactor
from vnpy.trader.object import TickData, BarData, Exchange, Interval, FactorData
from typing import Optional, Any, Union, Dict
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.base import FactorMode


class OPEN(FactorTemplate):
    factor_name = 'open'
    dependencies_factor = []
    freq = Interval.MINUTE
    factor_mode = FactorMode.Backtest

    def __init__(self, setting, **kwargs):
        """
        Initialize the OPEN factor with its settings.
        """
        super().__init__(setting, **kwargs)

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, Any]]], memory: Optional[pl.DataFrame] = None, *args, **kwargs) -> Any:
        """
        Return the 'open' data for Live Trading or Backtesting.

        Parameters:
            input_data (Optional[Union[pl.DataFrame, Dict[str, Any]]]): Input data containing 'open'.
            memory (Optional[pl.DataFrame]): Unused for this factor but kept for uniformity.

        Returns:
            pl.DataFrame: Open price data.
        """
        # Validate factor_mode
        if self.factor_mode not in [FactorMode.Backtest, FactorMode.Live]:
            raise ValueError("Invalid factor_mode. Must be 'Backtest' or 'Live'.")

        # Retrieve the 'open' data
        if isinstance(input_data, dict):
            open_data = input_data.get('open')
        elif isinstance(input_data, pl.DataFrame):
            open_data = input_data
        else:
            raise ValueError("Invalid input_data format. Expected pl.DataFrame or Dict[str, pl.DataFrame].")

        # Ensure the data is a Polars DataFrame
        if not isinstance(open_data, pl.DataFrame):
            raise ValueError("'open' data must be a Polars DataFrame.")

        return open_data
    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        pass