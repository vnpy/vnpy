"""
Math Functions
"""

import polars as pl

from .utility import DataProxy


def less(feature1: DataProxy, feature2: DataProxy | float) -> DataProxy:
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


def greater(feature1: DataProxy, feature2: DataProxy | float) -> DataProxy:
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


def log(feature: DataProxy) -> DataProxy:
    """Calculate the natural logarithm of the feature"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").log().over("vt_symbol")
    )
    return DataProxy(df)


def abs(feature: DataProxy) -> DataProxy:
    """Calculate the absolute value of the feature"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.col("data").abs().over("vt_symbol")
    )
    return DataProxy(df)


def sign(feature: DataProxy) -> DataProxy:
    """Calculate the sign of the feature"""
    df: pl.DataFrame = feature.df.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        pl.when(pl.col("data") > 0).then(1).when(pl.col("data") < 0).then(-1).otherwise(0).alias("data")
    )
    return DataProxy(df)


def quesval(threshold: float, feature1: DataProxy, feature2: DataProxy | float | int, feature3: DataProxy | float | int) -> DataProxy:
    """Return feature2 if threshold < feature1, otherwise feature3"""
    df_merged = feature1.df

    if isinstance(feature2, DataProxy):
        df_merged = df_merged.join(feature2.df, on=["datetime", "vt_symbol"], suffix="_true")
    else:
        df_merged = df_merged.with_columns(pl.lit(feature2).alias("data_true"))

    if isinstance(feature3, DataProxy):
        df_merged = df_merged.join(feature3.df, on=["datetime", "vt_symbol"], suffix="_false")
    else:
        df_merged = df_merged.with_columns(pl.lit(feature3).alias("data_false"))

    df: pl.DataFrame = df_merged.with_columns(
        pl.when(threshold < pl.col("data"))
        .then(pl.col("data_true"))
        .otherwise(pl.col("data_false"))
        .alias("data")
    ).select(["datetime", "vt_symbol", "data"])

    return DataProxy(df)


def quesval2(threshold: DataProxy, feature1: DataProxy, feature2: DataProxy | float | int, feature3: DataProxy | float | int) -> DataProxy:
    """Return feature2 if threshold < feature1, otherwise feature3 (DataProxy threshold version)"""
    df_merged: pl.DataFrame = threshold.df.join(feature1.df, on=["datetime", "vt_symbol"], suffix="_cond")

    if isinstance(feature2, DataProxy):
        df_merged = df_merged.join(feature2.df, on=["datetime", "vt_symbol"], suffix="_true")
    else:
        df_merged = df_merged.with_columns(pl.lit(feature2).alias("data_true"))

    if isinstance(feature3, DataProxy):
        df_merged = df_merged.join(feature3.df, on=["datetime", "vt_symbol"], suffix="_false")
    else:
        df_merged = df_merged.with_columns(pl.lit(feature3).alias("data_false"))

    df: pl.DataFrame = df_merged.with_columns(
        pl.when(pl.col("data_cond") < pl.col("data"))
        .then(pl.col("data_true"))
        .otherwise(pl.col("data_false"))
        .alias("data")
    ).select(["datetime", "vt_symbol", "data"])

    return DataProxy(df)


def pow1(base: DataProxy, exponent: float) -> DataProxy:
    """Safe power operation for DataProxy (handles negative base values)"""
    df: pl.DataFrame = base.df.with_columns(
        pl.when(pl.col("data") > 0)
        .then(pl.col("data").pow(exponent))
        .when(pl.col("data") < 0)
        .then(pl.lit(-1) * pl.col("data").abs().pow(exponent))
        .otherwise(0)
        .alias("data")
    )

    return DataProxy(df)


def pow2(base: DataProxy, exponent: DataProxy) -> DataProxy:
    """Power operation between two DataProxy objects (base^exponent)

    处理逻辑:
    - 底数>0: 直接计算 base^exponent
    - 底数<0且指数为整数: 计算 -1 * |base|^exponent
    - 其他情况(底数为0、指数为NaN、负数底数非整数指数): 返回0

    Note: 用floor判断整数而非cast(Int64)，因为NaN无法转换为整数会报错
    """
    base_renamed = base.df.rename({"data": "base_data"})
    exp_renamed = exponent.df.rename({"data": "exp_data"})

    df_merged: pl.DataFrame = base_renamed.join(exp_renamed, on=["datetime", "vt_symbol"], how="left")

    df: pl.DataFrame = df_merged.with_columns(
        pl.when(pl.col("base_data") > 0)
        .then(pl.col("base_data").pow(pl.col("exp_data")))
        .when(
            (pl.col("base_data") < 0) &
            (~pl.col("exp_data").is_nan()) &  # 先排除NaN，否则floor比较会出问题
            (pl.col("exp_data").floor() == pl.col("exp_data"))  # 判断是否为整数
        )
        .then((-1) * pl.col("base_data").abs().pow(pl.col("exp_data")))
        .otherwise(pl.lit(None))
        .fill_nan(None)
        .fill_null(0)
        .alias("data")
    ).select(["datetime", "vt_symbol", "data"])

    return DataProxy(df)


def cast_to_int(data: DataProxy) -> DataProxy:
    """Cast DataProxy values to integers"""
    df: pl.DataFrame = data.df.with_columns(
        pl.col("data").cast(pl.Int8).alias("data")
    )

    return DataProxy(df)
