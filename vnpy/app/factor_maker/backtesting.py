# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/vnpy/app/factor_maker
# @File     : backtesting.py
# @Time     : 2024/11/29 21:57
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
import re
from typing import Dict

import numpy as np
import pandas as pd
import polars as pl
from matplotlib import pyplot as plt


def resample_bar_polars(data: Dict[str, pl.DataFrame], trading_freq: str) -> Dict[str, pl.DataFrame]:
    """
    Resample the OHLCV data to match the specified trading frequency using Polars.

    Parameters:
        data (dict): Original data with keys ('open', 'high', 'low', 'close', 'volume').
                     Each value is a Polars DataFrame with a datetime column and multiple tickers as columns.
        trading_freq (str): Desired trading frequency (e.g., '1h' for hourly, '1d' for daily).

    Returns:
        dict: Resampled data with the same keys.
    """
    if not all(key in data for key in ['open', 'high', 'low', 'close', 'volume']):
        raise ValueError("Data must include 'open', 'high', 'low', 'close', and 'volume' keys.")

    resampled_data = {}

    for key in data:
        # Group by the datetime column dynamically for all tickers
        df = data[key]
        resampled_data[key] = df.group_by_dynamic(
            index_column="datetime",
            every=trading_freq,
            period=trading_freq,
            closed="left"
        ).agg([
            # Apply appropriate aggregation for each key dynamically for all tickers
            pl.col(col).first().alias(col) if key == "open" else
            pl.col(col).max().alias(col) if key == "high" else
            pl.col(col).min().alias(col) if key == "low" else
            pl.col(col).last().alias(col) if key == "close" else
            pl.col(col).sum().alias(col) for col in df.columns if col != "datetime"
        ])

    return resampled_data


def resample_factor_polars(df: pl.DataFrame, trading_freq: str, method: str = "mean") -> pl.DataFrame:
    """
    Resample factor data to match the specified trading frequency using Polars.

    Parameters:
        df (pl.DataFrame): Factor data with a 'datetime' column and multiple symbols as columns.
        trading_freq (str): Desired trading frequency (e.g., '1h' for hourly, '1d' for daily).
        method (str): Aggregation method for resampling. Options: 'mean', 'sum', 'max', 'min'.

    Returns:
        pl.DataFrame: Resampled factor data.
    """
    if method not in ["mean", "sum", "max", "min"]:
        raise ValueError("Invalid method. Supported methods: 'mean', 'sum', 'max', 'min'.")

    # Define the aggregation method dynamically
    agg_fn = {
        "mean": pl.col("*").mean,
        "sum": pl.col("*").sum,
        "max": pl.col("*").max,
        "min": pl.col("*").min,
    }[method]

    # Resample data using Polars' groupby_dynamic
    resampled_df = df.group_by_dynamic(
        index_column="datetime",
        every=trading_freq,
        period=trading_freq,
        closed="left"
    ).agg([agg_fn().exclude("datetime")])  # Apply aggregation, excluding 'datetime'

    return resampled_df


def resample_bar_pandas(data: Dict[str, pd.DataFrame], trading_freq: str) -> Dict[str, pd.DataFrame]:
    """
    Resample the OHLCV data to match the specified trading frequency.

    Parameters:
        data (dict): Original data with keys ('open', 'high', 'low', 'close', 'volume').
                     Each value is a DataFrame indexed by datetime.
        trading_freq (str): Desired trading frequency (e.g., '1H' for hourly, '1D' for daily).

    Returns:
        dict: Resampled data with the same keys.
    """
    if not all(key in data for key in ['open', 'high', 'low', 'close', 'volume']):
        raise ValueError("Data must include 'open', 'high', 'low', 'close', and 'volume' keys.")

    resampled_data = {}
    try:
        resampled_data = {
            'open': data['open'].resample(trading_freq).first(),
            'high': data['high'].resample(trading_freq).max(),
            'low': data['low'].resample(trading_freq).min(),
            'close': data['close'].resample(trading_freq).last(),
            'volume': data['volume'].resample(trading_freq).sum()
        }
    except Exception as e:
        raise ValueError(f"Error occurred during resampling: {e}")

    return resampled_data


def resample_factor_pandas(df: pd.DataFrame, trading_freq: str, method: str = "mean") -> pd.DataFrame:
    """
    Resample factor data to match the specified trading frequency.

    Parameters:
        df (pd.DataFrame): Factor data with datetime as index.
        trading_freq (str): Desired trading frequency (e.g., '1H').
        method (str): Aggregation method for resampling. Options: 'mean', 'sum', 'max', 'min'.

    Returns:
        pd.DataFrame: Resampled factor data.
    """
    if method not in ["mean", "sum", "max", "min"]:
        raise ValueError("Invalid method. Supported methods: 'mean', 'sum', 'max', 'min'.")

    try:
        if method == "mean":
            resampled_data = df.resample(trading_freq).mean()
        elif method == "sum":
            resampled_data = df.resample(trading_freq).sum()
        elif method == "max":
            resampled_data = df.resample(trading_freq).max()
        elif method == "min":
            resampled_data = df.resample(trading_freq).min()
        else:
            raise ValueError(f"Unsupported resampling method: {method}")
    except Exception as e:
        raise ValueError(f"Error occurred during factor resampling: {e}")

    return resampled_data


def plot_portfolio_performance_pandas(portfolio_values: pd.Series) -> None:
    """
    Plot portfolio performance.

    Parameters:
        portfolio_values (pd.Series): Portfolio values over time.
    """
    portfolio_values.plot(title="Portfolio Performance", ylabel="Portfolio Value", xlabel="Date", figsize=(12, 6))
    plt.grid()
    plt.show()


def plot_portfolio_performance_polars(portfolio_values: pl.DataFrame) -> None:
    """
    Plot portfolio performance using Polars DataFrame.

    Parameters:
        portfolio_values (pl.DataFrame): Portfolio values with 'datetime', 'adjusted_return', and 'portfolio_value' columns.
    """
    # Ensure the DataFrame contains necessary columns
    required_columns = {"datetime", "portfolio_value"}
    if not required_columns.issubset(set(portfolio_values.columns)):
        raise ValueError(f"Portfolio values must contain {required_columns} columns.")

    # Convert Polars DataFrame to Pandas for plotting
    portfolio_values_pd = portfolio_values.select(["datetime", "portfolio_value"]).to_pandas()

    # Set 'datetime' as the index for better plotting
    portfolio_values_pd.set_index("datetime", inplace=True)

    # Plot the portfolio performance
    portfolio_values_pd["portfolio_value"].plot(
        title="Portfolio Performance",
        ylabel="Portfolio Value",
        xlabel="Date",
        figsize=(12, 6),
        grid=True,
        color="blue",
    )

    plt.show()


class FactorBacktester:
    """
    A backtesting engine for evaluating factors with DataFrame-based factor values.
    """

    def __init__(self, data: Dict[str, pl.DataFrame], commission_rate: float = 0.001, slippage: float = 0.001,
                 trading_freq: str = '1h'):
        """
        Initialize the backtesting engine with fixed data.

        Parameters:
            data (dict): Historical data dictionary with keys ('open', 'high', 'low', 'close', 'volume').
            commission_rate (float): Commission rate per trade.
            slippage (float): Slippage per trade.
            trading_freq (str): trading frequency
        """
        self.data = resample_bar_polars(data, trading_freq)
        self.commission_rate = commission_rate
        self.slippage = slippage
        self.portfolio_values = None
        self.performance_metrics = None
        self.trading_freq = trading_freq

        # Calculate trading periods per year based on the trading frequency
        self.trading_periods_per_year = self.calculate_trading_periods_per_year(trading_freq)

    @staticmethod
    def calculate_trading_periods_per_year(trading_freq: str) -> int:
        """
        Calculate the number of trading periods per year for any custom trading frequency.

        Parameters:
            trading_freq (str): Trading frequency (e.g., '1min', '2H', '3D').

        Returns:
            int: Number of trading periods per year.
        """
        # Extract the numeric value and unit from the trading frequency
        match = re.match(r"(\d+)([a-zA-Z]+)", trading_freq)
        if not match:
            raise ValueError(f"Invalid trading frequency format: {trading_freq}")

        # Parse the numeric multiplier and the time unit
        multiplier = int(match.group(1))  # e.g., 2 in "2min"
        unit = match.group(2).lower()  # e.g., "min" in "2min"

        # Base periods per year for common time units
        base_periods_per_year = {
            "min": 365 * 24 * 60,  # Minutes in a year
            "h": 365 * 24,  # Hours in a year
            "d": 365,  # Days in a year
            "w": 52,  # Weeks in a year
            "m": 12,  # Months in a year
        }

        # Calculate the adjusted periods per year
        if unit not in base_periods_per_year:
            raise ValueError(f"Unsupported time unit in trading frequency: {unit}")

        periods_per_year = base_periods_per_year[unit] // multiplier
        return periods_per_year

    def run_backtesting_polars(self, factor_values: pl.DataFrame, if_plot: bool = True) -> Dict[str, float]:
        """
        Run the backtesting process with Polars DataFrames.

        Parameters:
            factor_values (pl.DataFrame): Factor values with datetime as row index and symbols as columns.
            if_plot (bool): Whether to plot the portfolio performance.

        Returns:
            dict: Performance metrics including Sharpe ratio, cumulative return, etc.
        """
        # Extract close prices as Polars DataFrame
        close_prices = self.data["close"]

        # Ensure factor_values are resampled to match the trading frequency
        factor_values = resample_factor_polars(factor_values, self.trading_freq, method="mean")

        # Calculate period returns (percentage change) for close prices
        returns = close_prices.select([
            pl.col("datetime"),
            *(pl.col(col).pct_change().alias(col) for col in close_prices.columns if col != "datetime")
        ])

        # Normalize factor values to calculate portfolio weights
        weights = factor_values.select([
            pl.col("datetime"),
            *(pl.col(col).truediv(
                pl.sum_horizontal([pl.col(c).abs() for c in factor_values.columns if c != "datetime"])).alias(col)
              for col in factor_values.columns if col != "datetime")
        ])

        # Shift weights to avoid lookahead bias
        shifted_weights = weights.select([
            pl.col("datetime"),
            *(pl.col(col).shift(1).alias(col) for col in weights.columns if col != "datetime")
        ])

        # Calculate portfolio returns
        portfolio_returns = shifted_weights.select([
            pl.col("datetime"),
            *(pl.col(col).mul(returns[col]).alias(col) for col in shifted_weights.columns if col != "datetime")
        ]).select([
            "datetime",
            pl.sum_horizontal([pl.col(col) for col in factor_values.columns if col != "datetime"]).alias(
                "portfolio_return")
        ])

        # Calculate transaction costs
        turnover = shifted_weights.select([
            pl.col("datetime"),
            pl.sum_horizontal([pl.col(col).diff().abs() for col in shifted_weights.columns if col != "datetime"]).alias(
                "turnover")
        ])
        transaction_costs = turnover.select([
            "datetime",
            (pl.col("turnover") * (self.commission_rate + self.slippage)).alias("transaction_cost")
        ])

        # Adjust portfolio returns for transaction costs
        portfolio_returns = portfolio_returns.join(transaction_costs, on="datetime").select([
            "datetime",
            (pl.col("portfolio_return") - pl.col("transaction_cost")).alias("adjusted_return")
        ])

        # Calculate cumulative portfolio value
        portfolio_values = portfolio_returns.select([
            "datetime",
            "adjusted_return",
            pl.fold(acc=pl.lit(1.0), function=lambda acc, x: acc * (1 + x),
                    exprs=pl.col("adjusted_return")).alias("portfolio_value")
        ])

        # Performance metrics
        cumulative_return = (portfolio_values["adjusted_return"].to_numpy()+1).cumprod()[-1] - 1
        annualized_return = portfolio_returns["adjusted_return"].mean() * self.trading_periods_per_year
        annualized_volatility = portfolio_returns["adjusted_return"].std() * (self.trading_periods_per_year ** 0.5)
        sharpe_ratio = (
            annualized_return / annualized_volatility if annualized_volatility != 0 else float("nan")
        )

        self.portfolio_values = portfolio_values
        self.performance_metrics = {
            "Cumulative Return": cumulative_return,
            "Annualized Return": annualized_return,
            "Annualized Volatility": annualized_volatility,
            "Sharpe Ratio": sharpe_ratio,
        }

        if if_plot:
            plot_portfolio_performance_polars(portfolio_values)

        return self.performance_metrics

    def run_backtesting_pandas(self, factor_values: pd.DataFrame, if_plot: bool = True) -> Dict[str, float]:
        """
        Run the backtesting process with new factor values.

        Parameters:
            factor_values (pd.DataFrame): Factor values with datetime as row index and symbols as columns.
            if_plot (bool): Whether to plot the portfolio performance.

        Returns:
            dict: Performance metrics including Sharpe ratio, cumulative return, etc.
        """
        # Extract close prices
        close_prices = self.data["close"]

        # resample data
        factor_values = resample_factor_polars(factor_values, self.trading_freq)

        # Calculate daily returns
        daily_returns = close_prices.pct_change()

        # Normalize factor values
        weights = factor_values.div(factor_values.abs().sum(axis=1), axis=0)

        # Calculate portfolio returns
        portfolio_returns = (weights.shift(1) * daily_returns).sum(axis=1)

        # Adjust for transaction costs
        turnover = weights.diff().abs().sum(axis=1)  # Portfolio turnover
        transaction_cost = turnover * (self.commission_rate + self.slippage)
        portfolio_returns -= transaction_cost

        # Calculate portfolio value
        portfolio_values = (1 + portfolio_returns).cumprod()

        # Performance metrics
        cumulative_return = portfolio_values.iloc[-1] - 1
        annualized_return = portfolio_returns.mean() * self.trading_periods_per_year
        annualized_volatility = portfolio_returns.std() * np.sqrt(self.trading_periods_per_year)
        sharpe_ratio = (
            annualized_return / annualized_volatility if annualized_volatility != 0 else np.nan
        )

        self.portfolio_values = portfolio_values
        self.performance_metrics = {
            "Cumulative Return": cumulative_return,
            "Annualized Return": annualized_return,
            "Annualized Volatility": annualized_volatility,
            "Sharpe Ratio": sharpe_ratio,
        }

        if if_plot:
            plot_portfolio_performance_pandas(portfolio_values)

        return self.performance_metrics
