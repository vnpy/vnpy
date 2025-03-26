from datetime import datetime
from enum import Enum
from typing import Union

import polars as pl


class DataProxy:
    """Feature data proxy"""

    def __init__(self, df: pl.DataFrame) -> None:
        """Constructor"""
        self.name: str = df.columns[-1]
        self.df: pl.DataFrame = df.rename({self.name: "data"})

        # Note that for numerical expressions, variables should be placed before numbers. e.g. a * 2

    def result(self, s: pl.Series) -> "DataProxy":
        """Convert series data to feature object"""
        result: pl.DataFrame = self.df[["datetime", "vt_symbol"]]
        result = result.with_columns(other=s)

        return DataProxy(result)

    def __add__(self, other: Union["DataProxy", int, float]) -> "DataProxy":
        """Addition operation"""
        if isinstance(other, DataProxy):
            s: pl.Series = self.df["data"] + other.df["data"]
        else:
            s = self.df["data"] + other
        return self.result(s)

    def __sub__(self, other: Union["DataProxy", int, float]) -> "DataProxy":
        """Subtraction operation"""
        if isinstance(other, DataProxy):
            s: pl.Series = self.df["data"] - other.df["data"]
        else:
            s = self.df["data"] - other
        return self.result(s)

    def __mul__(self, other: Union["DataProxy", int, float]) -> "DataProxy":
        """Multiplication operation"""
        if isinstance(other, DataProxy):
            s: pl.Series = self.df["data"] * other.df["data"]
        else:
            s = self.df["data"] * other
        return self.result(s)

    def __rmul__(self, other: Union["DataProxy", int, float]) -> "DataProxy":
        """Right multiplication operation"""
        if isinstance(other, DataProxy):
            s: pl.Series = self.df["data"] * other.df["data"]
        else:
            s = self.df["data"] * other
        return self.result(s)

    def __truediv__(self, other: Union["DataProxy", int, float]) -> "DataProxy":
        """Division operation"""
        if isinstance(other, DataProxy):
            s: pl.Series = self.df["data"] / other.df["data"]
        else:
            s = self.df["data"] / other
        return self.result(s)

    def __abs__(self) -> "DataProxy":
        """Get absolute value"""
        s: pl.Series = self.df["data"].abs()
        return self.result(s)

    def __gt__(self, other: Union["DataProxy", int, float]) -> "DataProxy":
        """Greater than comparison"""
        if isinstance(other, DataProxy):
            s: pl.Series = self.df["data"] > other.df["data"]
        else:
            s = self.df["data"] > other
        return self.result(s)

    def __ge__(self, other: Union["DataProxy", int, float]) -> "DataProxy":
        """Greater than or equal comparison"""
        if isinstance(other, DataProxy):
            s: pl.Series = self.df["data"] >= other.df["data"]
        else:
            s = self.df["data"] >= other
        return self.result(s)

    def __lt__(self, other: Union["DataProxy", int, float]) -> "DataProxy":
        """Less than comparison"""
        if isinstance(other, DataProxy):
            s: pl.Series = self.df["data"] < other.df["data"]
        else:
            s = self.df["data"] < other
        return self.result(s)

    def __le__(self, other: Union["DataProxy", int, float]) -> "DataProxy":
        """Less than or equal comparison"""
        if isinstance(other, DataProxy):
            s: pl.Series = self.df["data"] <= other.df["data"]
        else:
            s = self.df["data"] <= other
        return self.result(s)

    def __eq__(self, other: Union["DataProxy", int, float]) -> "DataProxy":    # type: ignore
        """Equal comparison"""
        if isinstance(other, DataProxy):
            s = self.df["data"] == other.df["data"]
        else:
            s = self.df["data"] == other
        return self.result(s)


def calculate_by_expression(df: pl.DataFrame, expression: str) -> pl.DataFrame:
    """Execute calculation based on expression"""
    # Import operators locally to avoid polluting global namespace
    from .ts_function import (              # noqa
        ts_delay,
        ts_min, ts_max,
        ts_argmax, ts_argmin,
        ts_rank,
        ts_sum,
        ref,
        mean, std,
        slope,
        rsquare, resi,
        max, min,
        quantile,
        idxmax, idxmin,
        log, corr,
        sum, abs,
        less, greater
    )
    from .cs_function import (              # noqa
        cs_rank, rank,
        cs_mean, cs_std
    )
    from .ta_function import rsi, atr       # noqa

    # Extract feature objects to local space
    d: dict = locals()

    for column in df.columns:
        # Filter index columns
        if column in {"datetime", "vt_symbol"}:
            continue

        # Cache feature df
        column_df = df[["datetime", "vt_symbol", column]]
        d[column] = DataProxy(column_df)

    # Use eval to execute calculation
    other: DataProxy = eval(expression, {}, d)

    # Return result DataFrame
    return other.df


def calculate_by_polars(df: pl.DataFrame, expression: pl.expr.expr.Expr) -> pl.DataFrame:
    """Execute calculation based on Polars expression"""
    return df.select([
        "datetime",
        "vt_symbol",
        expression.alias("data")
    ])


def to_datetime(arg: datetime | str) -> datetime:
    """Convert time data type"""
    if isinstance(arg, str):
        if "-" in arg:
            fmt: str = "%Y-%m-%d"
        else:
            fmt = "%Y%m%d"

        return datetime.strptime(arg, fmt)
    else:
        return arg


class Segment(Enum):
    """Data segment enumeration values"""

    TRAIN = 1
    VALID = 2
    TEST = 3
