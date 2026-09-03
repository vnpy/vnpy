"""
Technical Analysis Operators
"""

from collections.abc import Callable

import numpy as np
import talib
import polars as pl
import pandas as pd

from .utility import DataProxy


def to_pd_series(feature: DataProxy) -> pd.Series:
    """Convert to pandas.Series data structure"""
    series: pd.Series = feature.df.to_pandas().set_index(["datetime", "vt_symbol"])["data"]
    return series


def to_pl_dataframe(series: pd.Series) -> pl.DataFrame:
    """Convert to polars.DataFrame data structure"""
    df: pl.DataFrame = pl.from_pandas(series.reset_index().rename(columns={0: "data"}))
    return df


def apply_by_contract(
    func: Callable[..., np.ndarray],
    *series: pd.Series,
) -> pd.Series:
    """Apply a TA-Lib function independently within each vt_symbol.

    TA-Lib only accepts one-dimensional arrays and ignores the MultiIndex, so
    passing an interleaved (datetime, vt_symbol) series directly would mix
    values from different contracts into one indicator sequence. Grouping by
    vt_symbol keeps every contract's warm-up period and computation isolated,
    and preserves the original row order and index.
    """
    if not series:
        raise ValueError("at least one series is required")

    index = series[0].index
    for s in series[1:]:
        if not s.index.equals(index):
            raise ValueError("input series must share the same index")

    result = pd.Series(np.full(len(index), np.nan), index=index)

    # A plain datetime index (single contract) skips grouping entirely.
    if not isinstance(index, pd.MultiIndex):
        result[:] = func(*[s.to_numpy(dtype=np.float64) for s in series])
        return result

    codes = index.get_level_values("vt_symbol")
    for symbol in codes.unique():
        positions = np.flatnonzero(codes == symbol)
        result.iloc[positions] = func(*[s.to_numpy(dtype=np.float64)[positions] for s in series])

    return result


def ta_rsi(close: DataProxy, window: int) -> DataProxy:
    """Calculate RSI indicator by contract"""
    close_: pd.Series = to_pd_series(close)

    result: pd.Series = apply_by_contract(lambda x: talib.RSI(x, timeperiod=window), close_)   # type: ignore

    df: pl.DataFrame = to_pl_dataframe(result)
    return DataProxy(df)


def ta_atr(high: DataProxy, low: DataProxy, close: DataProxy, window: int) -> DataProxy:
    """Calculate ATR indicator by contract"""
    high_: pd.Series = to_pd_series(high)
    low_: pd.Series = to_pd_series(low)
    close_: pd.Series = to_pd_series(close)

    result: pd.Series = apply_by_contract(
        lambda h, l, c: talib.ATR(h, l, c, timeperiod=window), high_, low_, close_,   # type: ignore
    )

    df: pl.DataFrame = to_pl_dataframe(result)
    return DataProxy(df)
