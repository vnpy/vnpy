from datetime import datetime, timedelta

import numpy as np
import polars as pl
import talib

from vnpy.alpha.dataset.ta_function import ta_atr, ta_rsi
from vnpy.alpha.dataset.utility import DataProxy


def make_market_data() -> pl.DataFrame:
    """Create interleaved rows for two contracts with distinct price scales."""
    dates = [datetime(2024, 1, 1) + timedelta(days=i) for i in range(6)]
    prices = {
        "A.LOCAL": [10, 11, 12, 11, 13, 14],
        "B.LOCAL": [100, 98, 99, 97, 96, 101],
    }
    rows = []
    for index, date in enumerate(dates):
        for symbol, values in prices.items():
            close = values[index]
            rows.append(
                {
                    "datetime": date,
                    "vt_symbol": symbol,
                    "high": close + 2,
                    "low": close - 2,
                    "close": close,
                }
            )
    return pl.DataFrame(rows)


def make_proxy(df: pl.DataFrame, column: str) -> DataProxy:
    return DataProxy(df.select("datetime", "vt_symbol", column))


def expected_by_contract(df: pl.DataFrame, function, *columns: str) -> np.ndarray:
    values = np.full(df.height, np.nan)
    pandas_df = df.to_pandas()
    for positions in pandas_df.groupby("vt_symbol", sort=False).indices.values():
        inputs = [
            pandas_df.iloc[positions][column].to_numpy(dtype=float)
            for column in columns
        ]
        values[positions] = function(*inputs, timeperiod=2)
    return values


def test_ta_rsi_resets_warmup_for_each_contract() -> None:
    df = make_market_data()

    result = ta_rsi(make_proxy(df, "close"), window=2)
    expected = expected_by_contract(df, talib.RSI, "close")

    np.testing.assert_allclose(result.df["data"].to_numpy(), expected, equal_nan=True)


def test_ta_atr_does_not_cross_contract_boundaries() -> None:
    df = make_market_data()

    result = ta_atr(
        make_proxy(df, "high"), make_proxy(df, "low"), make_proxy(df, "close"), window=2
    )
    expected = expected_by_contract(df, talib.ATR, "high", "low", "close")

    np.testing.assert_allclose(result.df["data"].to_numpy(), expected, equal_nan=True)
