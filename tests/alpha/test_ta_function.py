from collections.abc import Callable
from datetime import datetime, timedelta

import numpy as np
import polars as pl
import pytest
import talib

from vnpy.alpha.dataset.ta_function import ta_atr, ta_rsi
from vnpy.alpha.dataset.utility import DataProxy


WINDOW = 2


def make_market_data() -> pl.DataFrame:
    """Create two interleaved symbols with clearly different price paths."""
    dates = [datetime(2025, 1, 1) + timedelta(days=i) for i in range(5)]
    a_close = [10.0, 11.0, 12.0, 13.0, 14.0]
    b_close = [100.0, 99.0, 98.0, 97.0, 96.0]

    rows: list[dict[str, datetime | str | float]] = []
    for i, dt in enumerate(dates):
        rows.extend([
            {
                "datetime": dt,
                "vt_symbol": "A.LOCAL",
                "high": a_close[i] + 1,
                "low": a_close[i] - 1,
                "close": a_close[i],
            },
            {
                "datetime": dt,
                "vt_symbol": "B.LOCAL",
                "high": b_close[i] + 4,
                "low": b_close[i] - 4,
                "close": b_close[i],
            },
        ])

    return pl.DataFrame(rows)


def make_proxy(df: pl.DataFrame, column: str) -> DataProxy:
    """Build a feature proxy without changing its row order."""
    return DataProxy(df.select(["datetime", "vt_symbol", column]))


def get_symbol_positions(df: pl.DataFrame) -> list[np.ndarray]:
    """Return row positions grouped by first-seen symbol order."""
    symbols = df["vt_symbol"].to_numpy()
    return [
        np.flatnonzero(symbols == symbol)
        for symbol in df["vt_symbol"].unique(maintain_order=True)
    ]


def calculate_by_symbol(
    df: pl.DataFrame,
    function: Callable[..., np.ndarray],
    columns: list[str],
) -> np.ndarray:
    """Calculate a TA-Lib oracle independently for every symbol."""
    result = np.full(df.height, np.nan)

    for positions in get_symbol_positions(df):
        arguments = [df[column].to_numpy()[positions] for column in columns]
        result[positions] = function(*arguments, timeperiod=WINDOW)

    return result


def assert_result(
    result: DataProxy,
    source: pl.DataFrame,
    expected: np.ndarray,
) -> None:
    """Assert values, key columns and original row order."""
    assert result.df.columns == ["datetime", "vt_symbol", "data"]
    assert result.df.select(["datetime", "vt_symbol"]).equals(
        source.select(["datetime", "vt_symbol"])
    )
    np.testing.assert_allclose(result.df["data"].to_numpy(), expected, equal_nan=True)


def assert_symbol_warmup(result: DataProxy, source: pl.DataFrame) -> None:
    """Assert that TA-Lib lookback is applied independently per symbol."""
    values = result.df["data"].to_numpy()

    for positions in get_symbol_positions(source):
        assert np.isnan(values[positions[:WINDOW]]).all()
        assert np.isfinite(values[positions[WINDOW:]]).all()


def test_ta_rsi_calculates_each_symbol_separately() -> None:
    """RSI should not mix interleaved observations from other symbols."""
    df = make_market_data()
    expected = calculate_by_symbol(df, talib.RSI, ["close"])

    result = ta_rsi(make_proxy(df, "close"), WINDOW)

    assert_result(result, df, expected)
    assert_symbol_warmup(result, df)


def test_ta_atr_calculates_each_symbol_separately() -> None:
    """ATR should use high, low and prior close from the same symbol."""
    df = make_market_data()
    expected = calculate_by_symbol(df, talib.ATR, ["high", "low", "close"])

    result = ta_atr(
        make_proxy(df, "high"),
        make_proxy(df, "low"),
        make_proxy(df, "close"),
        WINDOW,
    )

    assert_result(result, df, expected)
    assert_symbol_warmup(result, df)


def test_ta_atr_aligns_inputs_by_key() -> None:
    """ATR should align differently ordered inputs and keep high row order."""
    df = make_market_data()
    reversed_df = df.reverse()
    expected = calculate_by_symbol(df, talib.ATR, ["high", "low", "close"])

    result = ta_atr(
        make_proxy(df, "high"),
        make_proxy(reversed_df, "low"),
        make_proxy(reversed_df, "close"),
        WINDOW,
    )

    assert_result(result, df, expected)


def test_ta_atr_rejects_duplicate_keys() -> None:
    """Duplicate keys make one-to-one alignment ambiguous."""
    df = make_market_data()
    duplicate_high = pl.concat([df, df.head(1)])

    with pytest.raises(ValueError, match="unique"):
        ta_atr(
            make_proxy(duplicate_high, "high"),
            make_proxy(df, "low"),
            make_proxy(df, "close"),
            WINDOW,
        )


def test_ta_atr_rejects_mismatched_keys() -> None:
    """Missing or extra keys should fail instead of silently misaligning data."""
    df = make_market_data()
    mismatched_low = pl.concat([
        df.head(1).with_columns(pl.lit("OTHER.LOCAL").alias("vt_symbol")),
        df.slice(1),
    ])

    with pytest.raises(ValueError, match="same keys"):
        ta_atr(
            make_proxy(df, "high"),
            make_proxy(mismatched_low, "low"),
            make_proxy(df, "close"),
            WINDOW,
        )
