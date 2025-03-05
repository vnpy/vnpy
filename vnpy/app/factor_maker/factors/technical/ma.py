import polars as pl
from typing import Any, Optional, Union, Dict, List, Type

from vnpy.trader.object import TickData, BarData, Exchange, Interval, FactorData
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.factors.bar import *


class MA_BASE(FactorTemplate):
    factor_name = "ma"
    author: str = "EvanHong"

    # dependencies_factor: List[Type[FactorTemplate]] = [MA, MA]

    def __init_dependencies__(self):
        super().__init_dependencies__()

        self.underlying_factor: Type[FactorTemplate] = self.dependencies_factor[0]

    def __init__(self, setting, window=None):
        print(self.factor_name, setting, window)
        super().__init__(setting, window=window)


class MA(MA_BASE):

    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        df_last_window = input_data.tail(self.get_param('window'))
        last_row = df_last_window.select(
            [pl.lit(df_last_window[-1, "datetime"]).alias("datetime")] +  # Keep latest datetime
            [pl.col(col).mean().alias(col) for col in df_last_window.columns if col != "datetime"]
        )
        return last_row

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, Any]]], memory, *args,
                  **kwargs) -> pl.DataFrame:
        if isinstance(input_data, dict):
            last_row = self.calculate_polars(input_data[self.underlying_factor.factor_key])
            res = pl.concat([memory, last_row], how='vertical')
            return res
        elif isinstance(input_data, pl.DataFrame):
            return self.calculate_polars(input_data)
        else:
            raise ValueError("The input_data must be a dictionary.")
