import pytest
import numpy as np
import pandas as pd
import polars as pl

from vnpy.alpha.dataset.utility import DataProxy
from vnpy.alpha.dataset.ts_function import ts_cap, ts_cov, ts_decay_linear
from vnpy.alpha.dataset.math_function import (
    quesval, quesval2, pow1, pow2, cast_to_int
)
from vnpy.alpha.dataset.cs_function import cs_scale


def pd_quesval(
    threshold: float,
    condition: pd.DataFrame,
    true_val: pd.DataFrame,
    false_val: pd.DataFrame
) -> pd.DataFrame:
    """Pandas reference for quesval"""
    df = pd.merge(
        condition.rename(columns={"data": "cond"}),
        true_val.rename(columns={"data": "true"}),
        on=["datetime", "vt_symbol"]
    )
    df = pd.merge(
        df, false_val.rename(columns={"data": "false"}),
        on=["datetime", "vt_symbol"]
    )
    df["data"] = np.where(df["cond"] < threshold, df["true"], df["false"])
    return df[["datetime", "vt_symbol", "data"]]


def pd_quesval2(
    thresh: pd.DataFrame,
    condition: pd.DataFrame,
    true_val: pd.DataFrame,
    false_val: pd.DataFrame
) -> pd.DataFrame:
    """Pandas reference for quesval2"""
    df = pd.merge(
        thresh.rename(columns={"data": "thresh"}),
        condition.rename(columns={"data": "cond"}),
        on=["datetime", "vt_symbol"]
    )
    df = pd.merge(
        df, true_val.rename(columns={"data": "true"}),
        on=["datetime", "vt_symbol"]
    )
    df = pd.merge(
        df, false_val.rename(columns={"data": "false"}),
        on=["datetime", "vt_symbol"]
    )
    df["data"] = np.where(
        df["cond"] < df["thresh"], df["true"], df["false"]
    )
    return df[["datetime", "vt_symbol", "data"]]


def pd_pow1(base: pd.DataFrame, exponent: float) -> pd.DataFrame:
    """Pandas reference for pow1"""
    base = base.copy()
    base['data'] = np.where(
        base['data'] > 0,
        base['data'] ** exponent,
        np.where(
            base['data'] < 0,
            -1 * (np.abs(base['data']) ** exponent),
            0
        )
    )
    return base


def pd_corr(f1: pd.DataFrame, f2: pd.DataFrame, window: int) -> pd.DataFrame:
    """Pandas reference for ts_corr"""
    df = pd.merge(
        f1, f2, on=["datetime", "vt_symbol"], suffixes=("_1", "_2")
    )

    def calc_corr(group: pd.DataFrame) -> np.ndarray:
        return group[['data_1', 'data_2']].rolling(
            window, min_periods=1
        ).corr().iloc[0::2, 1].values

    results = []
    for _, group in df.groupby("vt_symbol"):
        g = group.copy()
        g["data"] = calc_corr(group)
        results.append(g[["datetime", "vt_symbol", "data"]])

    result = pd.concat(results, ignore_index=True)
    result["data"] = result["data"].replace([np.inf, -np.inf], np.nan)
    return result.sort_values(
        ["vt_symbol", "datetime"]
    ).reset_index(drop=True)


def pd_std(feature: pd.DataFrame, window: int) -> pd.DataFrame:
    """Pandas reference for ts_std"""
    feature = feature.copy()
    feature["data"] = feature.groupby("vt_symbol")["data"].rolling(
        window, min_periods=1
    ).std(ddof=0).reset_index(level=0, drop=True)
    return feature


def pd_mean(feature: pd.DataFrame, window: int) -> pd.DataFrame:
    """Pandas reference for ts_mean"""
    feature = feature.copy()
    feature["data"] = feature.groupby("vt_symbol")["data"].rolling(
        window, min_periods=1
    ).mean().reset_index(level=0, drop=True)
    return feature


def pd_cov(
    f1: pd.DataFrame, f2: pd.DataFrame, window: int
) -> pd.DataFrame:
    """Pandas reference for ts_cov"""
    corr = pd_corr(f1.copy(), f2.copy(), window)
    std1 = pd_std(f1.copy(), window)
    std2 = pd_std(f2.copy(), window)

    merged = pd.merge(
        corr, std1, on=["datetime", "vt_symbol"], 
        suffixes=("_corr", "_std1")
    )
    merged = pd.merge(
        merged, std2, on=["datetime", "vt_symbol"],
        suffixes=("", "_std2")
    )
    merged["data"] = (
        merged["data_corr"] * merged["data_std1"] * merged["data"]
    )
    return merged[["datetime", "vt_symbol", "data"]]


def pd_scale(feature: pd.DataFrame) -> pd.DataFrame:
    """Pandas reference for cs_scale"""
    feature = feature.copy()
    abs_sum = feature.groupby("datetime")["data"].transform(
        lambda x: np.abs(x).sum()
    )
    feature["data"] = np.where(abs_sum != 0, feature["data"] / abs_sum, 0)
    return feature


def pd_decay(feature: pd.DataFrame, window: int) -> pd.DataFrame:
    """Pandas reference for ts_decay_linear"""
    feature = feature.copy()
    weights = np.arange(window, 0, -1)
    denominator = (window * (window + 1) / 2)

    def weighted_avg(x: np.ndarray) -> float:
        if len(x) < window:
            return np.nan
        return (x * weights).sum() / denominator

    feature["data"] = feature.groupby("vt_symbol")["data"].rolling(
        window
    ).apply(weighted_avg, raw=True).reset_index(level=0, drop=True)
    return feature


def pd_cap(vwap: pd.DataFrame, volume: pd.DataFrame) -> pd.DataFrame:
    """Pandas reference for ts_cap"""
    adv20 = pd_mean(volume.copy(), 20)
    merged = pd.merge(
        vwap, adv20, on=["datetime", "vt_symbol"],
        suffixes=("_vwap", "_adv20")
    )
    merged["data"] = merged["data_vwap"] * merged["data_adv20"]
    return merged[["datetime", "vt_symbol", "data"]]


def pd_int(feature: pd.DataFrame) -> pd.DataFrame:
    """Pandas reference for cast_to_int"""
    feature = feature.copy()
    feature["data"] = feature["data"].astype(np.int8)
    return feature


def pd_pow2(base: pd.DataFrame, exponent: pd.DataFrame) -> pd.DataFrame:
    """Pandas reference for pow2"""
    merged = pd.merge(
        base, exponent, on=["datetime", "vt_symbol"],
        suffixes=("_base", "_exp")
    )

    result = np.full_like(merged["data_base"], np.nan, dtype=float)
    pos_mask = merged["data_base"] > 0
    result[pos_mask] = np.power(
        merged["data_base"][pos_mask], 
        merged["data_exp"][pos_mask]
    )

    neg_mask = merged["data_base"] < 0
    int_exp_mask = merged["data_exp"] % 1 == 0
    valid_neg_mask = neg_mask & int_exp_mask
    result[valid_neg_mask] = -1 * np.power(
        np.abs(merged["data_base"][valid_neg_mask]), 
        merged["data_exp"][valid_neg_mask]
    )

    merged["data"] = pd.Series(result).fillna(0)
    return merged[["datetime", "vt_symbol", "data"]]


@pytest.fixture
def sample_data() -> tuple[pl.DataFrame, pd.DataFrame]:
    """Create sample data for testing."""
    np.random.seed(42)
    dates = pd.date_range("2023-01-01", periods=20, freq="D")

    data = {
        "datetime": np.tile(dates, 2),
        "vt_symbol": np.repeat(["A", "B"], 20),
        "open": np.random.rand(40) * 10 + 100,
        "high": np.random.rand(40) * 10 + 110,
        "low": np.random.rand(40) * 5 + 95,
        "close": np.random.rand(40) * 10 + 100,
        "vwap": np.random.rand(40) * 10 + 100,
        "volume": np.random.rand(40) * 1000 + 500,
        "value1": np.random.randn(40),
        "value2": np.random.randn(40) * 5,
        "exponent_val": np.random.choice([1.0, 2.0, 2.5, 3.0], 40),
        "bool_val": np.random.choice([True, False], 40)
    }
    data["value1"][5:15] = -np.abs(data["value1"][5:15])

    pd_df = pd.DataFrame(data)
    pl_df = pl.from_pandas(pd_df)
    return pl_df, pd_df


def check_close(
    pl_result: pl.DataFrame, 
    pd_result: pd.DataFrame, 
    rtol: float = 1e-5
) -> None:
    """Compare polars and pandas results"""
    pd_sorted = pd_result.sort_values(
        ["vt_symbol", "datetime"]
    ).reset_index(drop=True)
    pl_sorted = pl_result.sort(["vt_symbol", "datetime"])

    np.testing.assert_allclose(
        pl_sorted["data"].to_numpy(), 
        pd_sorted["data"].to_numpy(), 
        rtol=rtol, equal_nan=True
    )


def test_quesval(sample_data: tuple[pl.DataFrame, pd.DataFrame]) -> None:
    """Test quesval function."""
    pl_df, pd_df = sample_data

    pl_cond = DataProxy(pl_df.select(["datetime", "vt_symbol", "value1"]))
    pl_true = DataProxy(pl_df.select(["datetime", "vt_symbol", "open"]))
    pl_false = DataProxy(pl_df.select(["datetime", "vt_symbol", "close"]))
    pl_result = quesval(0.5, pl_cond, pl_true, pl_false).df

    pd_cond = pd_df[["datetime", "vt_symbol", "value1"]].rename(
        columns={"value1": "data"}
    )
    pd_true = pd_df[["datetime", "vt_symbol", "open"]].rename(
        columns={"open": "data"}
    )
    pd_false = pd_df[["datetime", "vt_symbol", "close"]].rename(
        columns={"close": "data"}
    )
    pd_result = pd_quesval(0.5, pd_cond, pd_true, pd_false)

    check_close(pl_result, pd_result)


def test_quesval2(sample_data: tuple[pl.DataFrame, pd.DataFrame]) -> None:
    """Test quesval2 function."""
    pl_df, pd_df = sample_data

    pl_thresh = DataProxy(pl_df.select(["datetime", "vt_symbol", "value2"]))
    pl_cond = DataProxy(pl_df.select(["datetime", "vt_symbol", "value1"]))
    pl_true = DataProxy(pl_df.select(["datetime", "vt_symbol", "open"]))
    pl_false = DataProxy(pl_df.select(["datetime", "vt_symbol", "close"]))
    pl_result = quesval2(pl_thresh, pl_cond, pl_true, pl_false).df

    pd_thresh = pd_df[["datetime", "vt_symbol", "value2"]].rename(
        columns={"value2": "data"}
    )
    pd_cond = pd_df[["datetime", "vt_symbol", "value1"]].rename(
        columns={"value1": "data"}
    )
    pd_true = pd_df[["datetime", "vt_symbol", "open"]].rename(
        columns={"open": "data"}
    )
    pd_false = pd_df[["datetime", "vt_symbol", "close"]].rename(
        columns={"close": "data"}
    )
    pd_result = pd_quesval2(pd_thresh, pd_cond, pd_true, pd_false)

    check_close(pl_result, pd_result)


def test_pow1(sample_data: tuple[pl.DataFrame, pd.DataFrame]) -> None:
    """Test pow1 function."""
    pl_df, pd_df = sample_data

    pl_base = DataProxy(pl_df.select(["datetime", "vt_symbol", "value1"]))
    pl_result = pow1(pl_base, 2.5).df

    pd_base = pd_df[["datetime", "vt_symbol", "value1"]].rename(
        columns={"value1": "data"}
    )
    pd_result = pd_pow1(pd_base, 2.5)

    check_close(pl_result.fill_nan(0), pd_result.fillna(0))


def test_ts_cov(sample_data: tuple[pl.DataFrame, pd.DataFrame]) -> None:
    """Test ts_cov function."""
    pl_df, pd_df = sample_data

    pl_f1 = DataProxy(pl_df.select(["datetime", "vt_symbol", "high"]))
    pl_f2 = DataProxy(pl_df.select(["datetime", "vt_symbol", "low"]))
    pl_result = ts_cov(pl_f1, pl_f2, 5).df

    pd_f1 = pd_df[["datetime", "vt_symbol", "high"]].rename(
        columns={"high": "data"}
    )
    pd_f2 = pd_df[["datetime", "vt_symbol", "low"]].rename(
        columns={"low": "data"}
    )
    pd_result = pd_cov(pd_f1, pd_f2, 5)

    check_close(pl_result.fill_null(0).fill_nan(0), pd_result.fillna(0))


def test_cs_scale(sample_data: tuple[pl.DataFrame, pd.DataFrame]) -> None:
    """Test cs_scale function."""
    pl_df, pd_df = sample_data

    pl_feature = DataProxy(pl_df.select(["datetime", "vt_symbol", "value1"]))
    pl_result = cs_scale(pl_feature).df

    pd_feature = pd_df[["datetime", "vt_symbol", "value1"]].rename(
        columns={"value1": "data"}
    )
    pd_result = pd_scale(pd_feature)

    check_close(pl_result.fill_nan(0), pd_result.fillna(0))


def test_ts_decay_linear(
    sample_data: tuple[pl.DataFrame, pd.DataFrame]
) -> None:
    """Test ts_decay_linear function."""
    pl_df, pd_df = sample_data

    pl_feature = DataProxy(pl_df.select(["datetime", "vt_symbol", "close"]))
    pl_result = ts_decay_linear(pl_feature, 4).df

    pd_feature = pd_df[["datetime", "vt_symbol", "close"]].rename(
        columns={"close": "data"}
    )
    pd_result = pd_decay(pd_feature, 4)

    check_close(pl_result.drop_nulls(), pd_result.dropna())


def test_ts_cap(sample_data: tuple[pl.DataFrame, pd.DataFrame]) -> None:
    """Test ts_cap function."""
    pl_df, pd_df = sample_data

    pl_vwap = DataProxy(pl_df.select(["datetime", "vt_symbol", "vwap"]))
    pl_volume = DataProxy(pl_df.select(["datetime", "vt_symbol", "volume"]))
    pl_result = ts_cap(pl_vwap, pl_volume).df

    pd_vwap = pd_df[["datetime", "vt_symbol", "vwap"]].rename(
        columns={"vwap": "data"}
    )
    pd_volume = pd_df[["datetime", "vt_symbol", "volume"]].rename(
        columns={"volume": "data"}
    )
    pd_result = pd_cap(pd_vwap, pd_volume)

    check_close(pl_result.drop_nulls(), pd_result.dropna())


def test_cast_to_int(
    sample_data: tuple[pl.DataFrame, pd.DataFrame]
) -> None:
    """Test cast_to_int function."""
    pl_df, pd_df = sample_data

    pl_feature = DataProxy(pl_df.select(["datetime", "vt_symbol", "bool_val"]))
    pl_result = cast_to_int(pl_feature).df

    pd_feature = pd_df[["datetime", "vt_symbol", "bool_val"]].rename(
        columns={"bool_val": "data"}
    )
    pd_result = pd_int(pd_feature)

    check_close(pl_result, pd_result)


def test_pow2(sample_data: tuple[pl.DataFrame, pd.DataFrame]) -> None:
    """Test pow2 function."""
    pl_df, pd_df = sample_data

    pl_base = DataProxy(pl_df.select(["datetime", "vt_symbol", "value1"]))
    pl_exp = DataProxy(pl_df.select(["datetime", "vt_symbol", "exponent_val"]))
    pl_result = pow2(pl_base, pl_exp).df

    pd_base = pd_df[["datetime", "vt_symbol", "value1"]].rename(
        columns={"value1": "data"}
    )
    pd_exp = pd_df[["datetime", "vt_symbol", "exponent_val"]].rename(
        columns={"exponent_val": "data"}
    )
    pd_result = pd_pow2(pd_base, pd_exp)

    check_close(pl_result.fill_nan(0), pd_result.fillna(0), rtol=1e-4)
