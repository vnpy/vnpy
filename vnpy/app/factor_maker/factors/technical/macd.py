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
        super().__init_dependencies__()
        fast_period = self.params.get_parameter("fast_period")
        slow_period = self.params.get_parameter("slow_period")
        signal_period = self.params.get_parameter("signal_period")
        for factor in self.dependencies_factor:
            if factor.get_param('window') == fast_period:
                self.ma_fast = factor
            elif factor.get_param('window') == slow_period:
                self.ma_slow = factor
        self.ma_signal = signal_period
        setattr(self, "dependencies_factor", [self.ma_fast, self.ma_slow])  # ���¸���attribute

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
        # self.add_params(["fast_period", "slow_period", "signal_period"])  # ��ôȥ��ʶ����ma
        super().__init__(setting=setting,
                         fast_period=fast_period,
                         slow_period=slow_period,
                         signal_period=signal_period,
                         )
        # Default MACD parameters

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, Any]]], memory, *args,
                  **kwargs) -> pl.DataFrame:
        """
        Calculate MACD histogram values from input data.

        Parameters:
            input_data (pl.DataFrame): DataFrame with 'datetime' as index and symbols as columns containing close prices.

        Returns:
            pl.DataFrame: DataFrame with 'datetime' as index and symbols as columns containing MACD histogram values.
        """
        if isinstance(input_data, dict):
            datetime_index = input_data.get(self.ma_fast.factor_key)['datetime']
            fast = input_data.get(self.ma_fast.factor_key)
            slow = input_data.get(self.ma_slow.factor_key)
            # compute macd
            macd = (fast - slow).tail(1)
            last_row = macd.select(
                [pl.lit(datetime_index[-1]).alias("datetime")] +
                [pl.col(col) for col in macd.columns if col != "datetime"]
            )
            res = pl.concat([memory, last_row], how='vertical')
            return res
        else:
            raise ValueError("The input_data must be a dictionary.")
