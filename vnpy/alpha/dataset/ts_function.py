"""
Time Series Operators
"""

from typing import cast

from scipy import stats     # type: ignore
import polars as pl
import numpy as np
from .utility import DataProxy


def ts_delay(feature: DataProxy, window: int) -> DataProxy:
    """Get the value from a fixed time in the past"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").shift(window).over("vt_symbol")
    )
    return DataProxy(df)


def ts_delta(feature: DataProxy, window: int) -> DataProxy:
    """Calculate difference between current value and value from window periods ago"""
    return feature - ts_delay(feature, window)


def ts_min(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the minimum value over a rolling window"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rolling_min(window, min_samples=1).over("vt_symbol")
    )
    return DataProxy(df)


def ts_max(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the maximum value over a rolling window"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rolling_max(window, min_samples=1).over("vt_symbol")
    )
    return DataProxy(df)


def ts_argmax(feature: DataProxy, window: int) -> DataProxy:
    """Return the index of the maximum value over a rolling window"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rolling_map(lambda s: cast(int, s.arg_max()) + 1, window).over("vt_symbol")
    )
    return DataProxy(df)


def ts_argmin(feature: DataProxy, window: int) -> DataProxy:
    """Return the index of the minimum value over a rolling window"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rolling_map(lambda s: cast(int, s.arg_min()) + 1, window).over("vt_symbol")
    )
    return DataProxy(df)


def ts_rank(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the percentile rank of the current value within the window"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rolling_map(lambda s: stats.percentileofscore(s, s[-1]) / 100, window).over("vt_symbol")
    )
    return DataProxy(df)


def ts_sum(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the sum over a rolling window"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rolling_sum(window).over("vt_symbol")
    )
    return DataProxy(df)


def ts_mean(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the mean over a rolling window"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").cast(pl.Float32).rolling_map(lambda s: np.nanmean(s), window, min_samples=1).over("vt_symbol")
    )
    return DataProxy(df)


def ts_cap(feature1: DataProxy, feature2: DataProxy) -> DataProxy:
    """Calculate the market capitalization"""
    return feature1 * ts_mean(feature2, 20)


def ts_std(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the standard deviation over a rolling window"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rolling_map(lambda s: np.nanstd(s, ddof=0), window, min_samples=1).over("vt_symbol")
    )
    return DataProxy(df)


def ts_slope(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the slope of linear regression over a rolling window"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rolling_map(lambda s: np.polyfit(np.arange(len(s)), s, 1)[0], window).over("vt_symbol")
    )
    return DataProxy(df)


def ts_quantile(feature: DataProxy, window: int, quantile: float) -> DataProxy:
    """Calculate the quantile value over a rolling window"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rolling_map(lambda s: s.quantile(quantile=quantile, interpolation="linear"), window).over("vt_symbol")
    )
    return DataProxy(df)


def ts_rsquare(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the R-squared value of linear regression over a rolling window"""
    def rsquare(s: pl.Series) -> float:
        """Calculate R-squared value for a series"""
        if s.std():
            return float(stats.linregress(np.arange(len(s)), s).rvalue ** 2)
        else:
            return float("nan")

    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rolling_map(lambda s: rsquare(s), window).over("vt_symbol"))
    return DataProxy(df)


def ts_resi(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the residual of linear regression over a rolling window"""
    def resi(s: pl.Series) -> float:
        """Calculate residual for a series"""
        x: np.ndarray = np.arange(len(s))
        y: np.ndarray = s.to_numpy()
        coefficients: np.ndarray = np.polyfit(x, y, 1)
        predictions: np.ndarray = coefficients[0] * x + coefficients[1]
        resi: np.ndarray = y - predictions
        return float(resi[-1])

    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rolling_map(lambda s: resi(s), window).over("vt_symbol")
    )
    return DataProxy(df)


def ts_corr(feature1: DataProxy, feature2: DataProxy, window: int) -> DataProxy:
    """Calculate the correlation between two features over a rolling window"""
    df_merged: pl.DataFrame = feature1.df.join(feature2.df, on=["datetime", "vt_symbol"])

    df: pl.DataFrame = df_merged.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.rolling_corr("data", "data_right", window_size=window, min_samples=1).over("vt_symbol").alias("data")
    )

    df = df.with_columns(
        pl.when(pl.col("data").is_infinite()).then(None).otherwise(pl.col("data")).alias("data")
    )

    return DataProxy(df)


def ts_cov(feature1: DataProxy, feature2: DataProxy, window: int) -> DataProxy:
    """Calculate covariance between two features over a rolling window"""
    return ts_corr(feature1, feature2, window) * ts_std(feature1, window) * ts_std(feature2, window)


def ts_decay_linear(feature: DataProxy, window: int) -> DataProxy:
    """Calculate linear decay weighted average"""
    def decay_func(s: pl.Series) -> float:
        """Calculate linear decay weighted average for a series"""
        weights = pl.Series(range(window, 0, -1))
        return float((s * weights).sum() / (window * (window + 1) / 2))

    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rolling_map(lambda s: decay_func(s), window).over("vt_symbol")
    )
    return DataProxy(df)
