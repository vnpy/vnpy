import time
from datetime import datetime
from typing import cast
from collections.abc import Callable
from multiprocessing import get_context
from multiprocessing.context import BaseContext

import polars as pl
import pandas as pd
from tqdm import tqdm
from alphalens.utils import get_clean_factor_and_forward_returns    # type: ignore
from alphalens.tears import create_full_tear_sheet                  # type: ignore

from ..logger import logger
from .utility import (
    to_datetime,
    Segment,
    calculate_by_expression,
    calculate_by_polars
)


class AlphaDataset:
    """Alpha dataset template class"""

    def __init__(
        self,
        df: pl.DataFrame,
        train_period: tuple[str, str],
        valid_period: tuple[str, str],
        test_period: tuple[str, str],
        process_type: str = "append"
    ) -> None:
        """Constructor"""
        self.df: pl.DataFrame = df

        # DataFrames for processed data
        self.result_df: pl.DataFrame
        self.raw_df: pl.DataFrame
        self.infer_df: pl.DataFrame
        self.learn_df: pl.DataFrame

        # New version
        self.data_periods: dict[Segment, tuple[str, str]] = {
            Segment.TRAIN: train_period,
            Segment.VALID: valid_period,
            Segment.TEST: test_period
        }

        self.feature_expressions: dict[str, str | pl.expr.expr.Expr] = {}
        self.feature_results: dict[str, pl.DataFrame] = {}
        self.label_expression: str = ""

        self.process_type: str = process_type
        self.infer_processors: list = []
        self.learn_processors: list = []

    def add_feature(
        self,
        name: str,
        expression: str | pl.expr.expr.Expr | None = None,
        result: pl.DataFrame | None = None
    ) -> None:
        """
        Add a feature expression
        """
        if expression is not None and result is not None:
            raise ValueError("Only one of 'expression' or 'result' can be provided")

        if expression is not None:
            self.feature_expressions[name] = expression
        elif result is not None:
            self.feature_results[name] = result

    def set_label(self, expression: str) -> None:
        """
        Set the label expression
        """
        self.label_expression = expression

    def add_processor(self, task: str, processor: Callable[[pl.DataFrame], None]) -> None:
        """
        Add a feature preprocessor
        """
        if task == "infer":
            self.infer_processors.append(processor)
        else:
            self.learn_processors.append(processor)

    def prepare_data(self, filters: dict | None = None, max_workers: int | None = None) -> None:
        """
        Generate required data
        """
        # List for feature data results
        results: list = []

        # Iterate through expressions for calculation
        expressions: list[tuple[str, str | pl.expr.expr.Expr]] = list(self.feature_expressions.items())

        if self.label_expression:
            expressions.append(("label", self.label_expression))

        # Create process pool
        logger.info("开始计算表达式因子特征")

        args: list[tuple] = [(self.df, name, expression) for name, expression in expressions]

        context: BaseContext = get_context("spawn")

        with context.Pool(processes=max_workers) as pool:
            # Calculate all expressions in parallel
            it = pool.imap(calculate_feature, args)

            # Collect results
            for result in tqdm(it, total=len(args)):
                results.append(result)

        self.result_df = self.df.with_columns(results)

        # Merge result data factor features
        logger.info("开始合并结果数据因子特征")

        label_exist: bool = "label" in self.result_df
        for name, feature_result in tqdm(self.feature_results.items()):
            feature_result = feature_result.rename({"data": name})
            self.result_df = self.result_df.join(feature_result, on=["datetime", "vt_symbol"], how="left")

        if label_exist:
            # Put label at the last column
            cols: list = [col for col in self.result_df.columns if col != "label"] + ["label"]
            self.result_df = self.result_df.select(cols).sort(["datetime", "vt_symbol"])

        # Generate raw data
        raw_df = self.result_df.fill_null(float("nan"))

        if filters:
            logger.info("开始筛选成分股数据")

            dfs: list[pl.DataFrame] = []

            for vt_symbol, ranges in tqdm(filters.items(), total=len(filters)):
                for start, end in ranges:
                    temp_df = raw_df.filter(
                        (pl.col("vt_symbol") == vt_symbol)
                        & (pl.col("datetime") >= pl.lit(start))
                        & (pl.col("datetime") <= pl.lit(end))
                    )
                    dfs.append(temp_df)

            raw_df = pl.concat(dfs)

        # Only keep feature columns
        select_columns: list[str] = ["datetime", "vt_symbol"] + raw_df.columns[self.df.width:]
        self.raw_df = raw_df.select(select_columns).sort(["datetime", "vt_symbol"])

        self.infer_df = self.raw_df
        self.learn_df = self.raw_df

    def process_data(self) -> None:
        """
        Process data
        """
        # Generate inference data
        for processor in self.infer_processors:
            self.infer_df = processor(df=self.infer_df)

        # Generate learning data
        if self.process_type == "append":
            self.learn_df = self.infer_df

        for processor in self.learn_processors:
            self.learn_df = processor(df=self.learn_df)

    def fetch_raw(self, segment: Segment) -> pl.DataFrame:
        """
        Get raw data for a specific segment
        """
        start, end = self.data_periods[segment]
        return query_by_time(self.raw_df, start, end)

    def fetch_infer(self, segment: Segment) -> pl.DataFrame:
        """
        Get inference data for a specific segment
        """
        start, end = self.data_periods[segment]
        return query_by_time(self.infer_df, start, end)

    def fetch_learn(self, segment: Segment) -> pl.DataFrame:
        """
        Get learning data for a specific segment
        """
        start, end = self.data_periods[segment]
        return query_by_time(self.learn_df, start, end)

    def show_feature_performance(self, name: str) -> None:
        """
        Perform performance analysis for a feature
        """
        starts: list[datetime] = []
        ends: list[datetime] = []

        for period in self.data_periods.values():
            starts.append(to_datetime(period[0]))
            ends.append(to_datetime(period[1]))

        start: datetime = min(starts)
        end: datetime = max(ends)

        # Select range
        result_df: pl.DataFrame = query_by_time(self.result_df, start, end)
        learn_df: pl.DataFrame = query_by_time(self.learn_df, start, end)

        merged_df = (
            result_df
            .select(["datetime", "vt_symbol", "close"])
            .join(
                learn_df.select(["datetime", "vt_symbol", name]),
                on=["datetime", "vt_symbol"],
                how="inner"
            )
        )

        # Fill NaN and drop nulls
        merged_df = merged_df.fill_nan(None).drop_nulls()

        # Extract feature
        feature_df: pd.DataFrame = merged_df.select(["datetime", "vt_symbol", name]).to_pandas()
        feature_df.set_index(["datetime", "vt_symbol"], inplace=True)

        feature_s: pd.Series = feature_df[name]

        # Extract price
        price_df: pd.DataFrame = merged_df.select(["datetime", "vt_symbol", "close"]).to_pandas()
        price_df = price_df.pivot(index="datetime", columns="vt_symbol", values="close")

        # Merge data
        clean_data: pd.DataFrame = get_clean_factor_and_forward_returns(feature_s, price_df, quantiles=10)

        # Perform analysis
        create_full_tear_sheet(clean_data)

    def show_signal_performance(self, signal: pl.DataFrame) -> None:
        """
        Perform performance analysis for prediction signals
        """
        # Get signal start and end times
        start: datetime = cast(datetime, signal["datetime"].min())
        end: datetime = cast(datetime, signal["datetime"].max())

        # Select range
        df: pl.DataFrame = query_by_time(self.result_df, start, end)

        # Extract feature
        signal_df: pd.DataFrame = signal.to_pandas()
        signal_df.set_index(["datetime", "vt_symbol"], inplace=True)
        signal_s: pd.Series = signal_df["signal"]

        # Extract price
        price_df: pd.DataFrame = df.select(["datetime", "vt_symbol", "close"]).to_pandas()
        price_df = price_df.pivot(index="datetime", columns="vt_symbol", values="close")

        # Merge data
        clean_data: pd.DataFrame = get_clean_factor_and_forward_returns(
            signal_s,
            price_df,
            max_loss=1.0,
            quantiles=10
        )

        # Perform analysis
        create_full_tear_sheet(clean_data)


def query_by_time(df: pl.DataFrame, start: datetime | str = "", end: datetime | str = "") -> pl.DataFrame:
    """
    Filter DataFrame based on time range
    """
    if start:
        start = to_datetime(start)
        df = df.filter(pl.col("datetime") >= start)

    if end:
        end = to_datetime(end)
        df = df.filter(pl.col("datetime") <= end)

    return df.sort(["datetime", "vt_symbol"])


def calculate_feature(args: tuple[pl.DataFrame, str, str | pl.expr.expr.Expr]) -> pl.Series:
    """
    Calculate feature by expression
    """
    start = time.time()

    df, name, expression = args

    if isinstance(expression, pl.expr.expr.Expr):
        result = calculate_by_polars(df, expression)["data"].alias(name)
    else:
        result = calculate_by_expression(df, expression)["data"].alias(name)

    end = time.time()
    print(f"Feature calculation {name} took: {end - start} seconds | {expression}")

    return result
