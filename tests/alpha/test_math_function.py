from datetime import datetime

import polars as pl

from vnpy.alpha.dataset.math_function import quesval2
from vnpy.alpha.dataset.utility import DataProxy


def make_proxy(values: list[float]) -> DataProxy:
    """Create a single-datetime cross-sectional dataset."""
    dt = datetime(2025, 1, 1)
    symbols = [f"s{i}" for i in range(len(values))]
    df = pl.DataFrame(
        {
            "datetime": [dt] * len(values),
            "vt_symbol": symbols,
            "data": values,
        }
    )
    return DataProxy(df)


def test_quesval2_returns_feature2_when_threshold_below_feature1() -> None:
    """Test quesval2 returns feature2 when threshold < feature1"""
    threshold = make_proxy([2.0])
    feature1 = make_proxy([3.0])

    actual = quesval2(threshold, feature1, 10, -10).df["data"].to_list()

    assert actual == [10]


def test_quesval2_returns_feature3_when_threshold_above_feature1() -> None:
    """Test quesval2 returns feature3 when threshold > feature1"""
    threshold = make_proxy([4.0])
    feature1 = make_proxy([3.0])

    actual = quesval2(threshold, feature1, 10, -10).df["data"].to_list()

    assert actual == [-10]


def test_quesval2_returns_feature3_when_threshold_equals_feature1() -> None:
    """Test quesval2 returns feature3 when threshold == feature1"""
    threshold = make_proxy([3.0])
    feature1 = make_proxy([3.0])

    actual = quesval2(threshold, feature1, 10, -10).df["data"].to_list()

    assert actual == [-10]
