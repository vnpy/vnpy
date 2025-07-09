"""
Technical Analysis Operators
"""

import talib
import polars as pl
import pandas as pd

from .utility import DataProxy


def to_pd_series(feature: DataProxy) -> pd.Series:
    """Convert to pandas.Series data structure"""
    return feature.df.to_pandas().set_index(["datetime", "vt_symbol"])["data"]


def to_pl_dataframe(series: pd.Series) -> pl.DataFrame:
    """Convert to polars.DataFrame data structure"""
    return pl.from_pandas(series.reset_index().rename(columns={0: "data"}))


def ta_rsi(close: DataProxy, window: int) -> DataProxy:
    """Calculate RSI indicator by contract"""
    close_: pd.Series = to_pd_series(close)

    result: pd.Series = talib.RSI(close_, timeperiod=window)   # type: ignore

    df: pl.DataFrame = to_pl_dataframe(result)
    return DataProxy(df)


def ta_atr(high: DataProxy, low: DataProxy, close: DataProxy, window: int) -> DataProxy:
    """Calculate ATR indicator by contract"""
    high_: pd.Series = to_pd_series(high)
    low_: pd.Series = to_pd_series(low)
    close_: pd.Series = to_pd_series(close)

    result: pd.Series = talib.ATR(high_, low_, close_, timeperiod=window)   # type: ignore

    df: pl.DataFrame = to_pl_dataframe(result)
    return DataProxy(df)
