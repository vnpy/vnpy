from datetime import datetime, timedelta

import numpy as np
import polars as pl
import talib

from vnpy.alpha.dataset.ta_function import ta_atr, ta_rsi
from vnpy.alpha.dataset.utility import DataProxy


def make_interleaved_df() -> pl.DataFrame:
    """Two contracts interleaved by datetime (datetime, symbol) row order."""
    dates = [datetime(2025, 1, 1) + timedelta(days=i) for i in range(6)]
    close_values = {
        "A.LOCAL": [10.0, 11.0, 12.0, 11.0, 13.0, 14.0],
        "B.LOCAL": [100.0, 98.0, 99.0, 97.0, 96.0, 101.0],
    }
    rows = []
    for i, dt in enumerate(dates):
        for symbol, closes in close_values.items():
            close = closes[i]
            rows.append({
                "datetime": dt, "vt_symbol": symbol,
                "high": close + 2, "low": close - 2, "close": close,
            })
    return pl.DataFrame(rows)


def make_single_df(symbol: str = "A.LOCAL") -> pl.DataFrame:
    """One contract only: plain datetime index path."""
    df = make_interleaved_df()
    return df.filter(pl.col("vt_symbol") == symbol)


def make_proxy(df: pl.DataFrame, column: str) -> DataProxy:
    return DataProxy(df.select("datetime", "vt_symbol", column))


def expected_by_contract(df: pl.DataFrame, window: int) -> tuple[np.ndarray, np.ndarray]:
    """Reference values: run TA-Lib independently per contract."""
    pdf = df.to_pandas()
    expected_rsi = np.full(len(pdf), np.nan)
    expected_atr = np.full(len(pdf), np.nan)
    for positions in pdf.groupby("vt_symbol", sort=False).indices.values():
        group = pdf.iloc[positions]
        expected_rsi[positions] = np.asarray(talib.RSI(group["close"], timeperiod=window))
        expected_atr[positions] = np.asarray(talib.ATR(
            group["high"], group["low"], group["close"], timeperiod=window,
        ))
    return expected_rsi, expected_atr


def test_ta_rsi_multi_contract_interleaved():
    """RSI must be computed independently per vt_symbol (issue #3793)."""
    df = make_interleaved_df()
    actual = ta_rsi(make_proxy(df, "close"), 2).df["data"].to_numpy()
    expected_rsi, _ = expected_by_contract(df, 2)
    # Warm-up NaN per contract: 2 contracts x 2 bars, not 2 in total.
    assert np.isnan(actual).sum() == np.isnan(expected_rsi).sum() == 4
    np.testing.assert_allclose(actual, expected_rsi, equal_nan=True)


def test_ta_atr_multi_contract_interleaved():
    """ATR inputs (high/low/close) must stay aligned within each contract."""
    df = make_interleaved_df()
    actual = ta_atr(
        make_proxy(df, "high"), make_proxy(df, "low"), make_proxy(df, "close"), 2,
    ).df["data"].to_numpy()
    _, expected_atr = expected_by_contract(df, 2)
    assert np.isnan(actual).sum() == 4
    np.testing.assert_allclose(actual, expected_atr, equal_nan=True)


def test_ta_rsi_single_contract():
    """Single-contract input (no MultiIndex after filtering) still works."""
    df = make_single_df()
    actual = ta_rsi(make_proxy(df, "close"), 2).df["data"].to_numpy()
    expected = np.asarray(talib.RSI(df["close"].to_numpy(), timeperiod=2))
    assert np.isnan(actual).sum() == 2
    np.testing.assert_allclose(actual, expected, equal_nan=True)


def test_output_preserves_row_order():
    """Output rows must stay aligned with input rows (datetime, vt_symbol)."""
    df = make_interleaved_df()
    result = ta_rsi(make_proxy(df, "close"), 2).df
    assert result["vt_symbol"].to_list() == df["vt_symbol"].to_list()
    assert result["datetime"].to_list() == df["datetime"].to_list()
