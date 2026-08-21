import polars as pl
from datetime import datetime

from vnpy.alpha.dataset.cs_function import cs_rank
from vnpy.alpha.dataset.utility import DataProxy


def make_proxy(data: list) -> DataProxy:
    """Build a DataProxy with one datetime column of cross-sectional rows."""
    df: pl.DataFrame = pl.DataFrame(
        {"datetime": datetime(2023, 1, 1), "vt_symbol": [f"s{i}" for i in range(len(data))], "data": data}
    )
    return DataProxy(df)


class TestCsRank:
    """Test cross-sectional percentile ranking"""

    def test_rank_is_percentile_in_unit_interval(self) -> None:
        """Rank output must be in [0, 1], not absolute ranks like 1..N"""
        proxy = make_proxy([10.0, 2.0, 7.0, 7.0, 1.0])
        result = cs_rank(proxy).df["data"].to_list()

        # Highest value ranks 1.0, lowest ranks 0.0
        assert result[0] == 1.0
        assert result[4] == 0.0

        # Everything within [0, 1]
        assert all(0.0 <= v <= 1.0 for v in result)

        # Tied values get the same rank
        assert result[2] == result[3]

    def test_rank_maximum_is_one(self) -> None:
        """The largest cross-sectional value must rank exactly 1.0"""
        proxy = make_proxy([1.0, 2.0, 3.0, 4.0, 5.0])
        result = cs_rank(proxy).df["data"].to_list()
        assert result[-1] == 1.0
        assert result[0] == 0.0

    def test_rank_minimum_is_zero(self) -> None:
        """The smallest cross-sectional value must rank exactly 0.0"""
        proxy = make_proxy([5.0, 4.0, 3.0, 2.0, 1.0])
        result = cs_rank(proxy).df["data"].to_list()
        assert result[0] == 1.0
        assert result[-1] == 0.0

    def test_single_observation_ranks_midpoint(self) -> None:
        """A lone observation (no cross-section) ranks 0.5 instead of NaN"""
        proxy = make_proxy([42.0])
        result = cs_rank(proxy).df["data"].to_list()
        assert result == [0.5]

    def test_all_null_remains_null(self) -> None:
        """A fully null cross-section stays null, not a fabricated value"""
        proxy = make_proxy([None, None, None])
        result = cs_rank(proxy).df["data"].to_list()
        assert all(v is None for v in result)

    def test_null_values_are_skipped_in_ranking(self) -> None:
        """Nulls are excluded from ranking; rank is over non-null count"""
        proxy = make_proxy([10.0, None, 7.0, None, 1.0])
        result = cs_rank(proxy).df["data"].to_list()

        # Non-null values ranked among 3: 10->1.0, 7->0.5, 1->0.0
        assert result[0] == 1.0
        assert result[2] == 0.5
        assert result[4] == 0.0
        assert result[1] is None
        assert result[3] is None
