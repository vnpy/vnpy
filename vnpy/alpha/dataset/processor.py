from datetime import datetime

import numpy as np
import polars as pl

from .utility import to_datetime


def process_drop_na(df: pl.DataFrame, names: list[str] | None = None) -> pl.DataFrame:
    """Remove rows with missing values"""
    if names is None:
        names = df.columns[2:-1]

    for name in names:
        df = df.with_columns(
            pl.col(name).fill_nan(None)
        )
    df = df.drop_nulls(subset=names)
    return df


def process_fill_na(df: pl.DataFrame, fill_value: float, fill_label: bool = True) -> pl.DataFrame:
    """Fill missing values"""
    if fill_label:
        df = df.fill_null(fill_value)
        df = df.fill_nan(fill_value)
    else:
        df = df.with_columns(
            [pl.col(col).fill_null(fill_value).fill_nan(fill_value) for col in df.columns[2:-1]]
        )
    return df


def process_cs_norm(
    df: pl.DataFrame,
    method: str,         # robust/zscore
    names: list[str] | None = None
) -> pl.DataFrame:
    """Cross-sectional normalization"""
    if names is None:
        names = df.columns[2:-1]

    _df: pl.DataFrame = df.fill_nan(None)

    # Median method
    if method == "robust":
        for col in names:
            df = df.with_columns(
                _df.select(
                    (pl.col(col) - pl.col(col).median()).over("datetime").alias(col),
                )
            )

            df = df.with_columns(
                df.select(
                    pl.col(col).abs().median().over("datetime").alias("mad"),
                )
            )

            df = df.with_columns(
                (pl.col(col) / pl.col("mad") / 1.4826).clip(-3, 3).alias(col)
            ).drop(["mad"])
    # Z-Score method
    else:
        for col in names:
            df = df.with_columns(
                _df.select(
                    pl.col(col).mean().over("datetime").alias("mean"),
                    pl.col(col).std().over("datetime").alias("std"),
                )
            )

            df = df.with_columns(
                ((pl.col(col) - pl.col("mean")) / pl.col("std")).alias(col)
            ).drop(["mean", "std"])

    return df


def process_replace_inf(df: pl.DataFrame) -> pl.DataFrame:
    """Replace infinite values with per-symbol means"""
    _df: pl.DataFrame = df.fill_nan(None)

    for name in df.columns[2:]:
        mean_values: pl.DataFrame = (
            _df.filter(~pl.col(name).is_infinite()).group_by("vt_symbol").agg(
                [pl.col(name).mean().alias("mean")]
            )
        )

        df_with_mean: pl.DataFrame = df.join(mean_values, on="vt_symbol", how="left")
        df = df_with_mean.with_columns(
            pl.when(pl.col(name).is_infinite())
            .then(pl.col("mean"))
            .otherwise(pl.col(name))
            .alias(name)
        ).drop("mean")

    return df


def process_ts_norm(
    df: pl.DataFrame,
    fit_start_time: datetime | str | None = None,
    fit_end_time: datetime | str | None = None
) -> pl.DataFrame:
    """Time-series normalization"""
    _df: pl.DataFrame = df.fill_nan(None)

    if fit_start_time and fit_end_time:
        fit_start_time = to_datetime(fit_start_time)
        fit_end_time = to_datetime(fit_end_time)
        _df = _df.filter((pl.col("datetime") >= fit_start_time) & (pl.col("datetime") <= fit_end_time))

    for name in df.columns[2:]:
        df = df.with_columns(
            pl.lit(np.nanmean(_df[name])).alias("mean"),
            pl.lit(np.nanstd(_df[name])).alias("std"),
        )

        df = df.with_columns(
            pl.when(pl.col("std") == 0)
            .then(pl.col(name))
            .otherwise(((pl.col(name) - pl.col("mean")) / pl.col("std")).cast(pl.Float64))
            .alias(name)
        ).drop(["mean", "std"])

    return df


def process_drop_feature(df: pl.DataFrame, names: list[str]) -> pl.DataFrame:
    """Drop feature columns"""
    return df.drop(names)


def process_cs_fill_na(df: pl.DataFrame, names: list[str] | None = None) -> pl.DataFrame:
    """Fill missing values with cross-sectional means"""
    _df: pl.DataFrame = df.fill_nan(None)

    if names is None:
        names = _df.columns[2:-1]

    for col in names:
        df = df.with_columns(
            _df.select(
                pl.col(col).fill_null(pl.col(col).mean().over("datetime")).alias(col)
            )
        )

    return df


def process_robust_zscore_norm(
    df: pl.DataFrame,
    fit_start_time: datetime | str | None = None,
    fit_end_time: datetime | str | None = None,
    clip_outlier: bool = True
) -> pl.DataFrame:
    """Robust Z-Score normalization"""
    _df: pl.DataFrame = df.fill_nan(None)

    if fit_start_time and fit_end_time:
        fit_start_time = to_datetime(fit_start_time)
        fit_end_time = to_datetime(fit_end_time)
        _df = _df.filter((pl.col("datetime") >= fit_start_time) & (pl.col("datetime") <= fit_end_time))

    cols = df.columns[2:-1]
    X = _df.select(cols).to_numpy()

    mean_train = np.nanmedian(X, axis=0)
    std_train = np.nanmedian(np.abs(X - mean_train), axis=0)
    std_train += 1e-12
    std_train *= 1.4826

    for name in cols:
        normalized_col = (
            (pl.col(name) - mean_train[cols.index(name)]) / std_train[cols.index(name)]
        ).cast(pl.Float64)

        if clip_outlier:
            normalized_col = normalized_col.clip(-3, 3)

        df = df.with_columns(normalized_col.alias(name))

    return df


def process_cs_rank_norm(df: pl.DataFrame, names: list[str]) -> pl.DataFrame:
    """Cross-sectional rank normalization"""
    _df: pl.DataFrame = df.fill_nan(None)

    _df = _df.with_columns([
        ((pl.col(col).rank("average").over("datetime") / pl.col("datetime").count().over("datetime")) - 0.5) * 3.46
        for col in names
    ])

    df = df.with_columns([
        _df[col].alias(col) for col in names
    ])

    return df
