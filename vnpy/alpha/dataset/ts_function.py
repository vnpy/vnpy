"""
Time Series Operators
"""

from typing import cast

from scipy import stats     # type: ignore
import polars as pl
import numpy as np
from .cs_function import cs_sum
from .math_function import abs
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


def quesval(threshold: float, condition: DataProxy, true_value: DataProxy, false_value: DataProxy) -> DataProxy:
    """全DataProxy版"""
    return DataProxy(
        condition.df.join(true_value.df, on=["datetime", "vt_symbol"], suffix="_true")
          .join(false_value.df, on=["datetime", "vt_symbol"], suffix="_false")
          .with_columns(
              pl.when(pl.col("data") < threshold)
              .then(pl.col("data_true"))
              .otherwise(pl.col("data_false"))
              .alias("data")
          ).select(["datetime", "vt_symbol", "data"])
    )


def quesval2(threshold: DataProxy, condition: DataProxy, true_value: DataProxy, false_value: DataProxy) -> DataProxy:
    """支持 DataProxy 输入的 quesval"""
    return DataProxy(
        threshold.df.join(condition.df, on=["datetime", "vt_symbol"], suffix="_cond")
        .join(true_value.df, on=["datetime", "vt_symbol"], suffix="_true")
        .join(false_value.df, on=["datetime", "vt_symbol"], suffix="_false")
        .with_columns(
            pl.when(pl.col("data_cond") < pl.col("data"))
            .then(pl.col("data_true"))
            .otherwise(pl.col("data_false"))
            .alias("data")
        )
        .select(["datetime", "vt_symbol", "data"])
    )


def pow1(base: DataProxy, exponent: float) -> DataProxy:
    """
    DataProxy安全幂运算函数
    参数:
        base: 底数 (DataProxy)
        exponent: 指数 (float)
    返回:
        DataProxy: base^exponent
    """
    return DataProxy(
        base.df.with_columns(
            pl.when(pl.col("data") > 0)  # 处理正数
            .then(pl.col("data").pow(exponent))
            .when(pl.col("data") < 0)  # 处理负数
            .then(pl.lit(-1) * pl.col("data").abs().pow(exponent))
            .otherwise(0)  # 处理零值
            .alias("data")
        )
    )


def delta(price: DataProxy, periods: int = 1) -> DataProxy:
    """
    计算时间序列差分 (price_t - price_{t-periods})
    参数:
        price: 价格序列 (DataProxy)
        periods: 差分周期 (默认1)
    返回:
        DataProxy: 差分序列 (保持原始datetime和vt_symbol)
    """
    return DataProxy(
        price.df.select(
            pl.col("datetime"),
            pl.col("vt_symbol"),
            (pl.col("data") - pl.col("data").shift(periods).over("vt_symbol"))
            .fill_null(0)  # 初始periods个值为Null，填充为0
            .alias("data")
        )
    )


def cov(X, Y, w):
    return ts_corr(X, Y, w) * ts_std(X, w) * ts_std(Y, w)


def scale(feature: DataProxy) -> DataProxy:
    """Scale the feature by the sum of absolute values in the cross section"""
    # 计算因子值的绝对值
    abs_feature = abs(feature)

    # 计算横截面上所有因子值的绝对值之和
    sum_abs = cs_sum(abs_feature)

    # 合并原始因子和绝对值之和
    merged = feature.df.join(sum_abs.df, on=["datetime", "vt_symbol"], suffix="_sum")

    # 计算缩放后的值：原始值 / 绝对值之和
    # 处理除数为0的情况（将无穷大和NaN替换为0）
    df: pl.DataFrame = merged.select(
        pl.col("datetime"),
        pl.col("vt_symbol"),
        (pl.col("data") / pl.col("data_sum")).alias("data")
    ).with_columns(
        pl.when(pl.col("data").is_infinite() | pl.col("data").is_nan())
        .then(0)
        .otherwise(pl.col("data"))
        .alias("data")
    )

    return DataProxy(df)


def decay_linear(feature: DataProxy, d: int) -> DataProxy:
    df = feature.df.with_columns(
        pl.col("data").rolling_map(lambda s: (s * pl.Series(range(d, 0, -1))).sum() / (d * (d + 1) / 2), window_size=d, min_samples=d).over("vt_symbol")
    )
    return DataProxy(df)



def cap(vwap, volume):
    return vwap * ts_mean(volume, 20)


def cast_to_int(data: DataProxy) -> DataProxy:
    """DataProxy专用布尔转整数"""
    return DataProxy(
        data.df.with_columns(
            pl.col("data").cast(pl.Int8).alias("data")  # 使用Polars原生cast
        )
    )


def pow2(base: DataProxy, exponent: DataProxy) -> DataProxy:
    """
    DataProxy幂运算函数 (base^exponent)
    严格实现：
    1. 列名自动去重
    2. 支持负底数条件运算
    3. 时间序列完美对齐
    参数:
        base: 底数 (DataProxy)
        exponent: 指数 (DataProxy)
    返回:
        DataProxy: 包含幂运算结果的新DataProxy
    """
    # 安全重命名列（防止join冲突）
    base_renamed = base.df.rename({"data": "base_data"})
    exp_renamed = exponent.df.rename({"data": "exp_data"})

    # 合并数据并计算
    result_df = (
        base_renamed.join(
            exp_renamed,
            on=["datetime", "vt_symbol"],  # 按时间和标的对齐
            how="left"
        )
        .with_columns(
            # 正底数分支
            pl.when(pl.col("base_data") > 0)
            .then(pl.col("base_data").pow(pl.col("exp_data")))

            # 负底数且整数指数分支
            .when(
                (pl.col("base_data") < 0) &
                (pl.col("exp_data").cast(pl.Int64) == pl.col("exp_data"))
            )
            .then((-1) * pl.col("base_data").abs().pow(pl.col("exp_data")))

            # 非法操作处理
            .otherwise(pl.lit(None))
            .fill_nan(None)  # 捕获数学异常
            .fill_null(0)    # 填充空值
            .alias("data")    # 统一输出列名
        )
        .select(["datetime", "vt_symbol", "data"])  # 精选输出列
    )

    return DataProxy(result_df)
