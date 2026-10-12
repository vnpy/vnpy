from datetime import datetime

import polars as pl

from vnpy.alpha.dataset.math_function import quesval2
from vnpy.alpha.dataset.utility import DataProxy


def test_quesval2_uses_threshold_less_than_feature_condition() -> None:
    index = {
        "datetime": [datetime(2024, 1, 2)] * 3,
        "vt_symbol": ["A", "B", "C"],
    }
    threshold = DataProxy(pl.DataFrame({**index, "value": [2.0, 4.0, 3.0]}))
    feature = DataProxy(pl.DataFrame({**index, "value": [3.0, 3.0, 3.0]}))

    result = quesval2(threshold, feature, 10, -10)

    assert result.df["data"].to_list() == [10, -10, -10]
