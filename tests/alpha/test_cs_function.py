from datetime import datetime

import numpy as np
import pandas as pd
import polars as pl

from vnpy.alpha.dataset.cs_function import cs_rank
from vnpy.alpha.dataset.utility import DataProxy


def make_cross_section_df(values: list[float | None]) -> pl.DataFrame:
    """Create a single-datetime cross-sectional dataset."""
    dt = datetime(2025, 1, 1)
    symbols = [f"s{i}" for i in range(len(values))]
    return pl.DataFrame(
        {
            "datetime": [dt] * len(values),
            "vt_symbol": symbols,
            "data": values,
        }
    )


def make_proxy(df: pl.DataFrame) -> DataProxy:
    """Build a DataProxy from a cross-sectional value column."""
    return DataProxy(df.select(["datetime", "vt_symbol", "data"]))


def expected_wq_rank(values: list[float | None]) -> np.ndarray:
    """WorldQuant reference: rank(method='min', pct=True)."""
    ranked: pd.Series = pd.Series(values, dtype="Float64").rank(method="min", pct=True)
    return ranked.to_numpy(dtype=float)


def assert_cs_rank(values: list[float | None]) -> None:
    """Assert cs_rank matches WorldQuant rank on one cross section."""
    df = make_cross_section_df(values)
    actual = cs_rank(make_proxy(df)).df.sort("vt_symbol")["data"].to_numpy()
    expected = expected_wq_rank(values)
    np.testing.assert_allclose(actual, expected, equal_nan=True)


def test_cs_rank_matches_worldquant() -> None:
    """Test cs_rank matches WorldQuant rank across representative cases."""
    assert_cs_rank([1.0, 2.0, 3.0, 4.0, 5.0])
    assert_cs_rank([10.0, 2.0, 7.0, 7.0, 1.0])
    assert_cs_rank([10.0, None, 7.0, None, 1.0])
    assert_cs_rank([10.0, np.nan, 7.0, np.nan, 1.0])
    assert_cs_rank([42.0])
