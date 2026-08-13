"""
Technical Analysis Operators
"""

import talib
import polars as pl
import pandas as pd
from collections.abc import Callable

from .utility import DataProxy


def to_pd_series(feature: DataProxy) -> pd.Series:
    """Convert to pandas.Series data structure"""
    series: pd.Series = feature.df.to_pandas().set_index(["datetime", "vt_symbol"])[
        "data"
    ]
    return series


def to_pl_dataframe(series: pd.Series) -> pl.DataFrame:
    """Convert to polars.DataFrame data structure"""
    df: pl.DataFrame = pl.from_pandas(series.reset_index().rename(columns={0: "data"}))
    return df


def apply_by_contract(
    function: Callable,
    *series: pd.Series,
    **kwargs: int,
) -> pd.Series:
    """Apply a TA-Lib function independently to each contract.

    The dataset can interleave rows from multiple contracts.  TA-Lib only sees
    one-dimensional arrays, so passing the full series would make the last
    value of one contract become the previous close for the next contract.
    Compute each contract on its own rows, then place the results back into
    the original order expected by ``DataProxy``.
    """
    result = pd.Series(index=series[0].index, dtype=float)
    positions_by_contract = series[0].groupby(level="vt_symbol", sort=False).indices

    for positions in positions_by_contract.values():
        values = [item.iloc[positions].to_numpy(dtype=float) for item in series]
        result.iloc[positions] = function(*values, **kwargs)

    return result


def ta_rsi(close: DataProxy, window: int) -> DataProxy:
    """Calculate RSI indicator by contract"""
    close_: pd.Series = to_pd_series(close)

    result: pd.Series = apply_by_contract(talib.RSI, close_, timeperiod=window)

    df: pl.DataFrame = to_pl_dataframe(result)
    return DataProxy(df)


def ta_atr(high: DataProxy, low: DataProxy, close: DataProxy, window: int) -> DataProxy:
    """Calculate ATR indicator by contract"""
    high_: pd.Series = to_pd_series(high)
    low_: pd.Series = to_pd_series(low)
    close_: pd.Series = to_pd_series(close)

    result: pd.Series = apply_by_contract(
        talib.ATR, high_, low_, close_, timeperiod=window
    )

    df: pl.DataFrame = to_pl_dataframe(result)
    return DataProxy(df)
