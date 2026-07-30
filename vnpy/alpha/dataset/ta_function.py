"""
Technical Analysis Operators
"""

from collections.abc import Callable

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


def _apply_by_symbol(
    dataframe: pd.DataFrame,
    function: Callable[[pd.DataFrame], pd.Series],
) -> pd.Series:
    """Apply a TA-Lib function to each symbol while preserving row order."""
    result = pd.Series(index=dataframe.index, dtype=float, name="data")
    groups = dataframe.groupby(level="vt_symbol", sort=False, dropna=False)

    for positions in groups.indices.values():
        group: pd.DataFrame = dataframe.iloc[positions, :]
        values: pd.Series = function(group)
        result.iloc[positions] = values.to_numpy()

    return result


def _align_atr_inputs(
    high: pd.Series,
    low: pd.Series,
    close: pd.Series,
) -> pd.DataFrame:
    """Align ATR inputs by key, using high row order as the output order."""
    inputs: dict[str, pd.Series] = {
        "high": high,
        "low": low,
        "close": close,
    }
    reference_index: pd.Index = high.index

    for name, series in inputs.items():
        if not series.index.is_unique:
            raise ValueError(f"ATR input keys must be unique: {name}")

        if len(series.index) != len(reference_index) or not reference_index.isin(series.index).all():
            raise ValueError("ATR inputs must contain the same keys")

    aligned: pd.DataFrame = pd.concat(
        [series.reindex(reference_index).rename(name) for name, series in inputs.items()],
        axis="columns",
    )
    return aligned


def ta_rsi(close: DataProxy, window: int) -> DataProxy:
    """Calculate RSI indicator by contract"""
    close_: pd.Series = to_pd_series(close)

    result: pd.Series = _apply_by_symbol(
        close_.rename("close").to_frame(),
        lambda group: talib.RSI(group["close"], timeperiod=window),
    )

    df: pl.DataFrame = to_pl_dataframe(result)
    return DataProxy(df)


def ta_atr(high: DataProxy, low: DataProxy, close: DataProxy, window: int) -> DataProxy:
    """Calculate ATR indicator by contract"""
    high_: pd.Series = to_pd_series(high)
    low_: pd.Series = to_pd_series(low)
    close_: pd.Series = to_pd_series(close)

    inputs: pd.DataFrame = _align_atr_inputs(high_, low_, close_)
    result: pd.Series = _apply_by_symbol(
        inputs,
        lambda group: talib.ATR(
            group["high"],
            group["low"],
            group["close"],
            timeperiod=window,
        ),
    )

    df: pl.DataFrame = to_pl_dataframe(result)
    return DataProxy(df)
