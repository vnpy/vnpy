from datetime import datetime, timedelta

import numpy as np
import polars as pl
import talib

from vnpy.alpha.dataset.ta_function import ta_atr, ta_rsi
from vnpy.alpha.dataset.utility import DataProxy


def make_interleaved_df() -> pl.DataFrame:
    """Create interleaved multi-symbol OHLC data for TA function tests."""
    dates = [datetime(2025, 1, 1) + timedelta(days=i) for i in range(6)]
    close_values = {
        "A.LOCAL": [10, 11, 12, 11, 13, 14],
        "B.LOCAL": [100, 98, 99, 97, 96, 101],
    }
    rows = []
    for i, dt in enumerate(dates):
        for symbol, closes in close_values.items():
            close = closes[i]
            rows.append(
                {
                    "datetime": dt,
                    "vt_symbol": symbol,
                    "high": close + 2,
                    "low": close - 2,
                    "close": close,
                }
            )
    return pl.DataFrame(rows)


def make_proxy(df: pl.DataFrame, column: str) -> DataProxy:
    """Build a DataProxy from a single value column."""
    return DataProxy(df.select(["datetime", "vt_symbol", column]))


def assert_array(actual: np.ndarray, expected: np.ndarray) -> None:
    """Assert that two arrays match, treating NaN as equal."""
    np.testing.assert_allclose(actual, expected, equal_nan=True)


def test_ta_rsi_by_contract() -> None:
    """Test ta_rsi by contract"""
    df = make_interleaved_df()
    window = 2

    actual = ta_rsi(make_proxy(df, "close"), window).df["data"].to_numpy()

    pdf = df.to_pandas()
    expected = np.full(len(pdf), np.nan)
    for positions in pdf.groupby("vt_symbol", sort=False).indices.values():
        group = pdf.iloc[positions]
        expected[positions] = np.asarray(talib.RSI(group["close"], timeperiod=window))

    assert np.isnan(actual).sum() == 4
    assert_array(actual, expected)


def test_ta_atr_by_contract() -> None:
    """Test ta_atr by contract"""
    df = make_interleaved_df()
    window = 2

    actual = ta_atr(
        make_proxy(df, "high"),
        make_proxy(df, "low"),
        make_proxy(df, "close"),
        window,
    ).df["data"].to_numpy()

    pdf = df.to_pandas()
    expected = np.full(len(pdf), np.nan)
    for positions in pdf.groupby("vt_symbol", sort=False).indices.values():
        group = pdf.iloc[positions]
        expected[positions] = np.asarray(
            talib.ATR(
                group["high"],
                group["low"],
                group["close"],
                timeperiod=window,
            )
        )

    assert np.isnan(actual).sum() == 4
    assert_array(actual, expected)
