"""
Technical Analysis Operators
"""

from collections.abc import Callable

import talib
import polars as pl
import numpy as np

from .utility import DataProxy


def to_feature_df(
    df: pl.DataFrame,
    window: int,
    func: Callable[..., np.ndarray],
    *names: str,
) -> pl.DataFrame:
    """Convert to feature DataFrame"""
    # TA-Lib only accepts 1D arrays and cannot group by vt_symbol itself
    indexed_df: pl.DataFrame = df.with_row_index("row_id")
    result: np.ndarray = np.empty(df.height, dtype=np.float64)

    # Split by contract so each symbol is calculated independently
    for group_df in indexed_df.partition_by("vt_symbol", maintain_order=True):
        row_id: np.ndarray = group_df["row_id"].to_numpy()
        arrays: list[np.ndarray] = [
            group_df[name].cast(pl.Float64).to_numpy() for name in names
        ]
        if len(arrays) == 1:
            result[row_id] = func(arrays[0], timeperiod=window)
        else:
            result[row_id] = func(*arrays, timeperiod=window)

    # Write indicator values back in the original row order
    df = df.select(["datetime", "vt_symbol"]).with_columns(
        pl.Series("data", result, nan_to_null=True)
    )
    return df


def ta_rsi(close: DataProxy, window: int) -> DataProxy:
    """Calculate RSI indicator by contract"""
    df: pl.DataFrame = to_feature_df(close.df, window, talib.RSI, "data")
    return DataProxy(df)


def ta_atr(high: DataProxy, low: DataProxy, close: DataProxy, window: int) -> DataProxy:
    """Calculate ATR indicator by contract"""
    df: pl.DataFrame = (
        high.df.rename({"data": "high"})
        .join(low.df.rename({"data": "low"}), on=["datetime", "vt_symbol"])
        .join(close.df.rename({"data": "close"}), on=["datetime", "vt_symbol"])
    )
    df = to_feature_df(df, window, talib.ATR, "high", "low", "close")
    return DataProxy(df)
