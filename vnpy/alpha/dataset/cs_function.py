"""
Cross Section Operators
"""

import polars as pl

from .utility import DataProxy


def cs_rank(feature: DataProxy) -> DataProxy:
    """Perform cross-sectional ranking"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").rank().over("datetime")
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
