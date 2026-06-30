from datetime import datetime

import polars as pl
import pytest

from vnpy.alpha.dataset.template import AlphaDataset


def test_show_feature_performance_rejects_empty_factor_data() -> None:
    """Feature analysis should fail with a clear message before calling alphalens on empty data."""
    dt = datetime(2025, 1, 2)
    result_df = pl.DataFrame(
        {
            "datetime": [dt],
            "vt_symbol": ["300866.SZSE"],
            "close": [1.0],
        }
    )
    learn_df = pl.DataFrame(
        {
            "datetime": [dt],
            "vt_symbol": ["300866.SZSE"],
            "alpha36": [None],
        }
    )

    dataset = AlphaDataset(
        df=result_df,
        train_period=("2025-01-01", "2025-01-31"),
        valid_period=("2025-02-01", "2025-02-28"),
        test_period=("2025-03-01", "2025-03-31"),
    )
    dataset.result_df = result_df
    dataset.learn_df = learn_df

    with pytest.raises(
        ValueError,
        match="No valid rows available for feature performance analysis: alpha36",
    ):
        dataset.show_feature_performance("alpha36")
