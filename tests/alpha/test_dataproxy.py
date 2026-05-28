from datetime import datetime, timedelta

import numpy as np
import polars as pl

from vnpy.alpha.dataset.utility import DataProxy


def make_test_df() -> pl.DataFrame:
    """Create a compact deterministic dataset for DataProxy tests."""
    dates = [datetime(2024, 1, 1) + timedelta(days=i) for i in range(4)]
    return pl.DataFrame(
        {
            "datetime": dates,
            "vt_symbol": ["TEST"] * 4,
            "x": [1, 3, 2, 4],
            "y": [2, 2, 3, 1],
        }
    )


def make_proxy(df: pl.DataFrame, column: str) -> DataProxy:
    """Build a DataProxy from a single value column."""
    return DataProxy(df.select(["datetime", "vt_symbol", column]))


def assert_data(proxy: DataProxy, expected: list[float | int]) -> None:
    """Assert that a proxy keeps the index columns and expected values."""
    assert proxy.df.columns == ["datetime", "vt_symbol", "data"]
    np.testing.assert_allclose(proxy.df["data"].to_numpy(), np.asarray(expected, dtype=float))


def assert_int_data(proxy: DataProxy, expected: list[int]) -> None:
    """Assert that a proxy comparison returns Int32 data with expected values."""
    assert proxy.df.columns == ["datetime", "vt_symbol", "data"]
    assert proxy.df["data"].dtype == pl.Int32
    assert proxy.df["data"].to_list() == expected


def test_dataproxy_scalar_and_reverse_operations() -> None:
    """Test DataProxy operations with scalars on both sides."""
    df = make_test_df()
    x = make_proxy(df, "x")

    assert_data(x + 2, [3, 5, 4, 6])
    assert_data(2 + x, [3, 5, 4, 6])
    assert_data(x - 2, [-1, 1, 0, 2])
    assert_data(10 - x, [9, 7, 8, 6])
    assert_data(x * 2, [2, 6, 4, 8])
    assert_data(2 * x, [2, 6, 4, 8])
    assert_data(x / 2, [0.5, 1.5, 1, 2])
    assert_data(8 / x, [8, 8 / 3, 4, 2])
    assert_data(x // 2, [0, 1, 1, 2])
    assert_data(x % 2, [1, 1, 0, 0])
    assert_data(x**2, [1, 9, 4, 16])


def test_dataproxy_between_proxy_operations() -> None:
    """Test DataProxy operations between two proxies."""
    df = make_test_df()
    x = make_proxy(df, "x")
    y = make_proxy(df, "y")

    assert_data(x + y, [3, 5, 5, 5])
    assert_data(x - y, [-1, 1, -1, 3])
    assert_data(x * y, [2, 6, 6, 4])
    assert_data(x / y, [0.5, 1.5, 2 / 3, 4])
    assert_data(x // y, [0, 1, 0, 4])
    assert_data(x % y, [1, 1, 2, 0])
    assert_data(x**y, [1, 9, 8, 4])


def test_dataproxy_unary_operations() -> None:
    """Test unary DataProxy operations."""
    df = make_test_df()
    x = make_proxy(df, "x")

    assert_data(-x, [-1, -3, -2, -4])
    assert_data(abs(-x), [1, 3, 2, 4])


def test_dataproxy_scalar_comparisons() -> None:
    """Test DataProxy comparisons with scalars."""
    df = make_test_df()
    x = make_proxy(df, "x")

    assert_int_data(x > 2, [0, 1, 0, 1])
    assert_int_data(x >= 2, [0, 1, 1, 1])
    assert_int_data(x < 3, [1, 0, 1, 0])
    assert_int_data(x <= 3, [1, 1, 1, 0])
    assert_int_data(x == 2, [0, 0, 1, 0])
    assert_int_data(x != 2, [1, 1, 0, 1])


def test_dataproxy_between_proxy_comparisons() -> None:
    """Test DataProxy comparisons between two proxies."""
    df = make_test_df()
    x = make_proxy(df, "x")
    y = make_proxy(df, "y")

    assert_int_data(x > y, [0, 1, 0, 1])
    assert_int_data(x >= y, [0, 1, 0, 1])
    assert_int_data(x < y, [1, 0, 1, 0])
    assert_int_data(x <= y, [1, 0, 1, 0])
    assert_int_data(x == y, [0, 0, 0, 0])
    assert_int_data(x != y, [1, 1, 1, 1])
