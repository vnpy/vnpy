"""
Cross Section Operators
"""

import polars as pl

from .utility import DataProxy


def cs_rank(feature: DataProxy) -> DataProxy:
    """Calculate WorldQuant cross-sectional rank (method=min, pct=True)."""
    df: pl.DataFrame = (
        feature.df
        .with_columns(pl.col("data").fill_nan(None).alias("data"))
        .select(
            pl.col("datetime"),
            pl.col("vt_symbol"),
            (
                pl.col("data").rank(method="min").over("datetime")
                / pl.col("data").count().over("datetime")
            ).alias("data"),
        )
    )
    return DataProxy(df)


def cs_mean(feature: DataProxy) -> DataProxy:
    """Calculate cross-sectional mean"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").mean().over("datetime")
    )
    return DataProxy(df)


def cs_std(feature: DataProxy) -> DataProxy:
    """Calculate cross-sectional standard deviation"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").std().over("datetime")
    )
    return DataProxy(df)


def cs_sum(feature: DataProxy) -> DataProxy:
    """Calculate cross-sectional sum"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").sum().over("datetime")
    )
    return DataProxy(df)


def cs_scale(feature: DataProxy) -> DataProxy:
    """Scale the feature by the sum of absolute values in the cross section"""
    abs_feature: DataProxy = abs(feature)
    sum_abs: DataProxy = cs_sum(abs_feature)

    df_merged: pl.DataFrame = feature.df.join(sum_abs.df, on=["datetime", "vt_symbol"], suffix="_sum")

    df: pl.DataFrame = df_merged.with_columns(
        pl.when(pl.col("data_sum") != 0)
        .then(pl.col("data") / pl.col("data_sum"))
        .otherwise(0)
        .alias("data")
    ).select(["datetime", "vt_symbol", "data"])

    return DataProxy(df)
