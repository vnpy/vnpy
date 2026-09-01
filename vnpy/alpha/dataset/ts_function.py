"""Time Series Operators"""

from collections.abc import Callable
from typing import cast

from scipy import stats    # type: ignore[import-untyped]
from numpy.lib.stride_tricks import sliding_window_view
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
    return _rolling_full_window_by_symbol(
        feature=feature,
        window=window,
        reduce_slice=_reduce_argmax_slice,
    )


def ts_argmin(feature: DataProxy, window: int) -> DataProxy:
    """Return the index of the minimum value over a rolling window"""
    return _rolling_full_window_by_symbol(
        feature=feature,
        window=window,
        reduce_slice=_reduce_argmin_slice,
    )


def ts_rank(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the percentile rank of the current value within the window"""
    return _rolling_full_window_by_symbol(
        feature=feature,
        window=window,
        reduce_slice=_reduce_rank_slice,
        reduce_axis=_reduce_rank_axis,
    )


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
    return _rolling_by_symbol(
        feature=feature,
        window=window,
        reduce_slice=_reduce_mean_slice,
        reduce_axis=_reduce_mean_axis,
    )


def ts_std(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the standard deviation over a rolling window"""
    return _rolling_by_symbol(
        feature=feature,
        window=window,
        reduce_slice=_reduce_std_slice,
        reduce_axis=_reduce_std_axis,
    )


def ts_slope(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the slope of linear regression over a rolling window (optimized)"""
    # 预计算 x 相关的常数 (x = 0, 1, 2, ..., window-1)
    n = window
    sum_x = n * (n - 1) / 2  # 等差数列求和
    sum_x2 = (n - 1) * n * (2 * n - 1) / 6  # 平方和公式
    denominator = n * sum_x2 - sum_x * sum_x

    # 计算 sum(i * y[t-window+1+i]) for i in 0..window-1
    # 等价于 sum((window-1-j) * y[t-j]) for j in 0..window-1
    sum_xy_expr: pl.Expr = pl.sum_horizontal([
        (window - 1 - j) * pl.col("data").shift(j)
        for j in range(window)
    ])

    df: pl.DataFrame = feature.df.with_columns([
        pl.col("data").rolling_sum(window, min_samples=window).over("vt_symbol").alias("sum_y"),
        sum_xy_expr.over("vt_symbol").alias("sum_xy")
    ])

    df = df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        ((n * pl.col("sum_xy") - sum_x * pl.col("sum_y")) / denominator).alias("data")
    )
    return DataProxy(df)


def ts_quantile(feature: DataProxy, window: int, quantile: float) -> DataProxy:
    """Calculate the quantile value over a rolling window"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data")
        .rolling_quantile(
            quantile=quantile,
            interpolation="linear",
            window_size=window,
        )
        .over("vt_symbol")
        .cast(pl.Float64),
    )
    return DataProxy(df)


def ts_rsquare(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the R-squared value of linear regression over a rolling window (optimized)"""
    # 预计算 x 相关的常数 (x = 0, 1, 2, ..., window-1)
    n = window
    sum_x2 = (n - 1) * n * (2 * n - 1) / 6  # 平方和公式
    mean_x = (n - 1) / 2
    var_x = sum_x2 / n - mean_x * mean_x  # 总体方差

    # 计算 sum(i * y[t-window+1+i]) for i in 0..window-1
    sum_xy_expr: pl.Expr = pl.sum_horizontal([
        (window - 1 - j) * pl.col("data").shift(j)
        for j in range(window)
    ])

    df: pl.DataFrame = feature.df.with_columns([
        pl.col("data").rolling_sum(window, min_samples=window).over("vt_symbol").alias("sum_y"),
        pl.col("data").rolling_var(window, min_samples=window, ddof=0).over("vt_symbol").alias("var_y"),
        sum_xy_expr.over("vt_symbol").alias("sum_xy")
    ])

    # mean_y 和 cov(x, y) = E(xy) - E(x)E(y)
    df = df.with_columns([
        (pl.col("sum_y") / n).alias("mean_y"),
    ])

    df = df.with_columns([
        (pl.col("sum_xy") / n - mean_x * pl.col("mean_y")).alias("cov_xy")
    ])

    # r = cov(x,y) / (std_x * std_y), r^2 = cov(x,y)^2 / (var_x * var_y)
    df = df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        (pl.col("cov_xy").pow(2) / (var_x * pl.col("var_y"))).alias("data")
    )

    df = df.with_columns(
        pl.when(pl.col("data").is_infinite() | pl.col("data").is_nan())
        .then(None)
        .otherwise(pl.col("data"))
        .alias("data")
    )

    return DataProxy(df)


def ts_resi(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the residual of linear regression over a rolling window (optimized)"""
    # 预计算 x 相关的常数 (x = 0, 1, 2, ..., window-1)
    n = window
    sum_x = n * (n - 1) / 2  # 等差数列求和
    sum_x2 = (n - 1) * n * (2 * n - 1) / 6  # 平方和公式
    mean_x = (n - 1) / 2
    denominator = n * sum_x2 - sum_x * sum_x

    # 计算 sum(i * y[t-window+1+i]) for i in 0..window-1
    sum_xy_expr: pl.Expr = pl.sum_horizontal([
        (window - 1 - j) * pl.col("data").shift(j)
        for j in range(window)
    ])

    df: pl.DataFrame = feature.df.with_columns([
        pl.col("data").rolling_sum(window, min_samples=window).over("vt_symbol").alias("sum_y"),
        sum_xy_expr.over("vt_symbol").alias("sum_xy")
    ])

    # 计算 slope 和 intercept
    df = df.with_columns([
        ((n * pl.col("sum_xy") - sum_x * pl.col("sum_y")) / denominator).alias("slope"),
        (pl.col("sum_y") / n).alias("mean_y"),
    ])

    df = df.with_columns([
        (pl.col("mean_y") - pl.col("slope") * mean_x).alias("intercept")
    ])

    # residual = y - (slope * (n-1) + intercept)，最后一个点的 x = n-1
    df = df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        (pl.col("data") - (pl.col("slope") * (n - 1) + pl.col("intercept"))).alias("data")
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


def ts_less(feature1: DataProxy, feature2: DataProxy | float) -> DataProxy:
    """Return the minimum value between two features"""
    if isinstance(feature2, DataProxy):
        df_merged: pl.DataFrame = feature1.df.join(feature2.df, on=["datetime", "vt_symbol"])
    else:
        df_merged = feature1.df.with_columns(pl.lit(feature2).alias("data_right"))

    df: pl.DataFrame = df_merged.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.min_horizontal("data", "data_right").over("vt_symbol").alias("data")
    )

    return DataProxy(df)


def ts_greater(feature1: DataProxy, feature2: DataProxy | float) -> DataProxy:
    """Return the maximum value between two features"""
    if isinstance(feature2, DataProxy):
        df_merged: pl.DataFrame = feature1.df.join(feature2.df, on=["datetime", "vt_symbol"])

    else:
        df_merged = feature1.df.with_columns(pl.lit(feature2).alias("data_right"))

    df: pl.DataFrame = df_merged.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.max_horizontal("data", "data_right").over("vt_symbol").alias("data")
    )

    return DataProxy(df)


def ts_log(feature: DataProxy) -> DataProxy:
    """Calculate the natural logarithm of the feature"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").log().over("vt_symbol")
    )
    return DataProxy(df)


def ts_abs(feature: DataProxy) -> DataProxy:
    """Calculate the absolute value of the feature"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").abs().over("vt_symbol")
    )
    return DataProxy(df)


def ts_delta(feature: DataProxy, window: int) -> DataProxy:
    """Calculate difference between current value and value from window periods ago"""
    return feature - ts_delay(feature, window)


def ts_cov(feature1: DataProxy, feature2: DataProxy, window: int) -> DataProxy:
    """Calculate covariance between two features over a rolling window"""
    return ts_corr(feature1, feature2, window) * ts_std(feature1, window) * ts_std(feature2, window)


def ts_decay_linear(feature: DataProxy, window: int) -> DataProxy:
    """Calculate linear decay weighted average"""
    def decay_func(s: pl.Series) -> float:
        """Calculate linear decay weighted average for a series"""
        weights = pl.Series(range(window, 0, -1))
        denominator: int = window * (window + 1) // 2
        return float((s * weights).sum() / denominator)

    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data")
        .cast(pl.Float64)
        .rolling_map(lambda s: decay_func(s), window)
        .over("vt_symbol"),
    )
    return DataProxy(df)


def ts_product(feature: DataProxy, window: int) -> DataProxy:
    """Calculate the product over a rolling window"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rolling_map(lambda s: s.product(), window).over("vt_symbol")
    )
    return DataProxy(df)


def _rolling_by_symbol(
    feature: DataProxy,
    window: int,
    reduce_slice: Callable[[object], float],
    reduce_axis: Callable[[np.ndarray], np.ndarray],
) -> DataProxy:
    """
    Shared rolling helper for ts_mean / ts_std.

    Per-symbol NumPy windows with min_samples=1.
    Unsupported dtypes fall back to `_rolling_map_fallback(min_samples=1)`.
    """
    source_df: pl.DataFrame = feature.df
    if source_df.height == 0:
        return DataProxy(source_df.select(["datetime", "vt_symbol", "data"]))

    data_dtype: pl.DataType = source_df["data"].dtype
    # Fall back to rolling_map when the dtype is unsupported
    if not _is_fast_rolling_dtype(data_dtype):
        return _rolling_map_fallback(
            feature=feature,
            window=window,
            reducer=reduce_slice,
            min_samples=1,
        )

    # Add row_id so results can be written back in order
    indexed_df: pl.DataFrame = source_df.with_row_index("row_id")
    result_values: np.ndarray = np.empty(source_df.height, dtype=np.float64)
    result_null: np.ndarray = np.zeros(source_df.height, dtype=np.bool_)

    # Split by vt_symbol so windows stay within one symbol
    group_frames: list[pl.DataFrame] = indexed_df.partition_by(
        "vt_symbol",
        maintain_order=True,
    )
    for group_df in group_frames:
        row_index: np.ndarray = group_df["row_id"].to_numpy()
        data_series: pl.Series = group_df["data"]
        null_mask: np.ndarray = data_series.is_null().to_numpy()
        # Convert to float64 and use NaN as the null placeholder
        float_values: np.ndarray = (
            data_series.cast(pl.Float64)
            .fill_null(np.nan)
            .to_numpy()
            .astype(np.float64, copy=False)
        )

        length: int = int(float_values.shape[0])
        local_values: np.ndarray = np.empty(length, dtype=np.float64)
        local_null: np.ndarray = np.zeros(length, dtype=np.bool_)

        partial_end: int = window - 1
        if partial_end > length:
            partial_end = length

        # Call reduce_slice on short leading windows
        for i in range(partial_end):
            end: int = i + 1
            window_null: np.ndarray = null_mask[0:end]
            # Leave the result null when every value in the window is null
            if bool(np.all(window_null)):
                local_null[i] = True
                local_values[i] = np.nan
            else:
                local_values[i] = reduce_slice(float_values[0:end])

        if length >= window:
            # Build sliding windows and call reduce_axis once
            value_windows: np.ndarray = sliding_window_view(
                float_values,
                window_shape=window,
            )
            null_windows: np.ndarray = sliding_window_view(
                null_mask.astype(np.uint8, copy=False),
                window_shape=window,
            )
            all_null: np.ndarray = np.asarray(
                null_windows.all(axis=-1),
                dtype=np.bool_,
            )
            reduced: np.ndarray = reduce_axis(value_windows)
            local_values[window - 1:] = reduced
            # Set null when every value in the window was null
            local_null[window - 1:] = all_null

        # Scatter local results into the global arrays
        result_values[row_index] = local_values
        result_null[row_index] = local_null

    value_expr: pl.Expr = (
        pl.when(pl.col("roll_null"))
        .then(pl.lit(None, dtype=pl.Float64))
        .otherwise(pl.col("roll_value"))
    )

    result_df: pl.DataFrame = source_df.select(["datetime", "vt_symbol"]).with_columns(
        pl.Series("roll_value", result_values),
        pl.Series("roll_null", result_null),
    ).select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        value_expr.alias("data"),
    )
    return DataProxy(result_df)


def _rolling_full_window_by_symbol(
    feature: DataProxy,
    window: int,
    reduce_slice: Callable[[pl.Series], float],
    reduce_axis: Callable[[np.ndarray], np.ndarray] | None = None,
) -> DataProxy:
    """
    Full-window per-symbol helper for rank / argmax / argmin.

    First window-1 rows are null. Any Polars null in a full window yields null.
    Does not change mean/std helper semantics.
    """
    source_df: pl.DataFrame = feature.df
    if source_df.height == 0:
        return DataProxy(source_df.select(["datetime", "vt_symbol", "data"]))

    data_dtype: pl.DataType = source_df["data"].dtype
    # Fall back to rolling_map when the dtype is unsupported
    if not _is_fast_rolling_dtype(data_dtype):
        return _rolling_map_fallback(
            feature=feature,
            window=window,
            reducer=reduce_slice,
        )

    # Add row_id so results can be written back in order
    indexed_df: pl.DataFrame = source_df.with_row_index("row_id")
    result_values: np.ndarray = np.empty(source_df.height, dtype=np.float64)
    result_null: np.ndarray = np.zeros(source_df.height, dtype=np.bool_)

    # Split by vt_symbol so windows stay within one symbol
    group_frames: list[pl.DataFrame] = indexed_df.partition_by(
        "vt_symbol",
        maintain_order=True,
    )
    for group_df in group_frames:
        row_index: np.ndarray = group_df["row_id"].to_numpy()
        data_series: pl.Series = group_df["data"]
        length: int = int(data_series.len())
        local_values: np.ndarray = np.empty(length, dtype=np.float64)
        # Start with all null for the leading short windows
        local_null: np.ndarray = np.ones(length, dtype=np.bool_)

        if length >= window:
            if reduce_axis is None:
                # Call reduce_slice once per full window
                for i in range(window - 1, length):
                    start: int = i + 1 - window
                    window_series: pl.Series = data_series.slice(start, window)
                    # Leave the result null when the window has any null
                    if window_series.null_count() > 0:
                        local_null[i] = True
                        local_values[i] = np.nan
                    else:
                        local_null[i] = False
                        local_values[i] = reduce_slice(window_series)
            else:
                # Build sliding windows and call reduce_axis once
                null_mask: np.ndarray = data_series.is_null().to_numpy()
                # Fill null with 0 only to allow to_numpy
                values: np.ndarray = data_series.fill_null(0).to_numpy()
                value_windows: np.ndarray = sliding_window_view(values, window)
                null_windows: np.ndarray = sliding_window_view(null_mask, window)
                local_values[window - 1:] = reduce_axis(value_windows)
                # Set null where any value in the window was null
                local_null[window - 1:] = null_windows.any(axis=-1)

        # Scatter local results into the global arrays
        result_values[row_index] = local_values
        result_null[row_index] = local_null

    value_expr: pl.Expr = (
        pl.when(pl.col("roll_null"))
        .then(pl.lit(None, dtype=pl.Float64))
        .otherwise(pl.col("roll_value"))
    )
    result_df: pl.DataFrame = source_df.select(["datetime", "vt_symbol"]).with_columns(
        pl.Series("roll_value", result_values),
        pl.Series("roll_null", result_null),
    ).select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        value_expr.alias("data"),
    )
    return DataProxy(result_df)


def _rolling_map_fallback(
    feature: DataProxy,
    window: int,
    reducer: Callable[..., float],
    min_samples: int | None = None,
) -> DataProxy:
    """Fallback to Polars rolling_map for unsupported dtypes."""
    data_col: pl.Expr = pl.col("data").cast(pl.Float64)
    if min_samples is None:
        data_expr: pl.Expr = data_col.rolling_map(reducer, window).over("vt_symbol")
    else:
        data_expr = data_col.rolling_map(
            reducer,
            window,
            min_samples=min_samples,
        ).over("vt_symbol")
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        data_expr,
    )
    return DataProxy(df)


def _reduce_argmax_slice(series: pl.Series) -> float:
    """1-based argmax position using Polars Series semantics."""
    return float(cast(int, series.arg_max()) + 1)


def _reduce_argmin_slice(series: pl.Series) -> float:
    """1-based argmin position using Polars Series semantics."""
    return float(cast(int, series.arg_min()) + 1)


def _reduce_rank_slice(series: pl.Series) -> float:
    """SciPy percentile rank of the last value in the window."""
    return float(stats.percentileofscore(series, series[-1]) / 100)


def _reduce_rank_axis(windows: np.ndarray) -> np.ndarray:
    """Vectorized SciPy rank-percentile semantics over the last axis."""
    scores: np.ndarray = windows[:, -1:]
    left: np.ndarray = np.count_nonzero(windows < scores, axis=-1)
    right: np.ndarray = np.count_nonzero(windows <= scores, axis=-1)
    plus_one: np.ndarray = left < right
    window_size: int = int(windows.shape[-1])
    result: np.ndarray = (left + right + plus_one) * (50.0 / window_size) / 100

    nan_windows: np.ndarray = np.isnan(windows).any(axis=-1)
    result = np.asarray(result, dtype=np.float64)
    result[nan_windows] = np.nan
    return result


def _reduce_mean_axis(windows: np.ndarray) -> np.ndarray:
    """Vectorized nanmean over the last axis."""
    with np.errstate(all="ignore"):
        result: np.ndarray = np.asarray(np.nanmean(windows, axis=-1), dtype=np.float64)
    return result


def _reduce_std_axis(windows: np.ndarray) -> np.ndarray:
    """Vectorized nanstd over the last axis, sample std (ddof=1)."""
    with np.errstate(all="ignore"):
        result: np.ndarray = np.asarray(
            np.nanstd(windows, axis=-1, ddof=1),
            dtype=np.float64,
        )
    return result


def _reduce_mean_slice(values: object) -> float:
    """nanmean for one window slice."""
    array: np.ndarray = np.asarray(values, dtype=np.float64)
    with np.errstate(all="ignore"):
        return float(np.nanmean(array))


def _reduce_std_slice(values: object) -> float:
    """nanstd for one window slice, sample std (ddof=1)."""
    array: np.ndarray = np.asarray(values, dtype=np.float64)
    with np.errstate(all="ignore"):
        return float(np.nanstd(array, ddof=1))


def _is_fast_rolling_dtype(dtype: pl.DataType) -> bool:
    """Return whether dtype uses the vectorized rolling path."""
    return dtype in {
        pl.Float32,
        pl.Float64,
        pl.Int32,
        pl.Int64,
        pl.UInt32,
        pl.UInt64,
    }
