# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/vnpy/app/factor_maker
# @File     : backtesting.py
# @Time     : 2024/11/29 21:57
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
import re
from typing import Dict, Union, Any

import pandas as pd
import polars as pl
import quantstats as qs
import statsmodels.api as sm
import numpy as np

import warnings

from matplotlib import pyplot as plt

warnings.simplefilter(action='ignore', category=FutureWarning)


class FactorBacktester:
    """
    A backtesting engine for evaluating factors with DataFrame-based factor values.
    """

    def __init__(self, memory_bar: Dict[str, Union[pl.DataFrame, pd.DataFrame]],
                 commission_rate: float = 0.001, slippage: float = 0.001, trading_freq: str = '1h'):
        """
        Initialize the backtesting engine with fixed memory_bar.

        Parameters:
            memory_bar (dict): Historical memory_bar dictionary with keys ('open', 'high', 'low', 'close', 'volume').
            commission_rate (float): Commission rate per trade.
            slippage (float): Slippage per trade.
            trading_freq (str): Trading frequency (e.g., '1D').
        """
        # Convert all Polars DataFrames in memory_bar to Pandas
        self.memory_bar = {key: convert_to_pandas(df) for key, df in memory_bar.items()}
        self.commission_rate = commission_rate
        self.slippage = slippage
        self.trading_freq = trading_freq
        self.trading_periods_per_year = self.calculate_trading_periods_per_year(trading_freq)
        self.factor_processor = FactorProcessor(window=30)
        self.weight_processor = WeightProcessor(smooth_coef=0.7)

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

    def run_backtesting(self, factor_values: Union[pl.DataFrame, pd.DataFrame],
                        if_report: bool = True, benchmark: str = None) -> Any:
        """
        Run the backtesting process.

        Parameters:
            factor_values (Union[pl.DataFrame, pd.DataFrame]): Factor values with datetime as index and tickers as columns.
            if_report (bool): Whether to generate reports.
            benchmark (str): The ticker symbol to use as a benchmark. If None, no benchmark is used.

        Returns:
            None: All performance analysis is delegated to QuantStats.
        """
        # Convert factor_values to Pandas
        factor_values = convert_to_pandas(factor_values)

        scaled_factors = self.factor_processor.process(factor_values, method=None)

        # Resample memory_bar and factor_values to match the trading frequency
        resampled_memory_bar = resample_bar_pandas(self.memory_bar, self.trading_freq)
        close_prices = resampled_memory_bar["close"]
        resampled_scaled_factors = resample_factor_pandas(scaled_factors, self.trading_freq, method="mean")

        # Calculate daily (or resampled period) returns
        period_returns = close_prices.pct_change()

        """fama_res = fama_macbeth_regression(factor_values=resampled_scaled_factors, returns=period_returns, rolling_window=120)

        print(fama_res)"""

        # Calculate portfolio weights using normalized (min-max scaled) factors
        weights = self.weight_processor.process(resampled_scaled_factors)

        weights.plot()
        plt.show()

        # Calculate portfolio returns
        portfolio_returns = (weights.shift(1) * period_returns).sum(axis=1)

        # Adjust for transaction costs
        turnover = weights.diff().abs().sum(axis=1)  # Portfolio turnover
        transaction_cost = turnover * (self.commission_rate + self.slippage)
        portfolio_returns -= transaction_cost
        portfolio_returns.name = "strategy_return"

        # Extract benchmark returns if specified
        benchmark_returns = extract_benchmark_returns(resampled_memory_bar, ticker=benchmark)

        if if_report:
            report = qs.reports.metrics(
                returns=portfolio_returns,
                benchmark=benchmark_returns,
                rf=0.1 / self.trading_periods_per_year,
                periods_per_year=self.trading_periods_per_year
            )

            qs.plots.returns(returns=portfolio_returns, benchmark=benchmark_returns)

            print(report)

        sharpe_ratio = qs.stats.sharpe(
            returns=portfolio_returns,
            rf=0.1 / self.trading_periods_per_year,
            periods=self.trading_periods_per_year
        )

        return sharpe_ratio


# utils
def extract_benchmark_returns(memory_bar: Dict[str, pd.DataFrame], ticker: str = None) -> pd.Series:
    """
    Extract benchmark returns from memory_bar. If `ticker` is None, use the mean of all columns.

    Parameters:
        memory_bar (dict): Historical memory_bar with 'close' key containing a DataFrame of close prices.
        ticker (str): Specific column name (ticker) to extract returns. If None, calculate mean returns across all columns.

    Returns:
        pd.Series: Benchmark returns, resampled to the specified trading frequency.
    """
    if "close" not in memory_bar:
        raise ValueError("memory_bar must contain 'close' prices")

    close_prices = memory_bar["close"]

    if ticker is not None:
        if ticker not in close_prices.columns:
            raise ValueError(f"Ticker '{ticker}' not found in memory_bar['close'] columns")
        benchmark_close = close_prices[ticker]
    else:
        # Take the mean across all columns
        benchmark_close = close_prices.mean(axis=1)

    # Calculate benchmark returns (percentage change)
    benchmark_returns = benchmark_close.pct_change().dropna()
    benchmark_returns.name = "benchmark_return"

    return benchmark_returns


def convert_to_pandas(data):
    """
    Convert Polars DataFrame or Series to Pandas equivalents, ensuring datetime columns are handled properly.

    Parameters:
        data: Input data, can be Polars DataFrame, Polars Series, or already Pandas.

    Returns:
        pd.DataFrame or pd.Series: Converted Pandas DataFrame or Series with datetime index if applicable.
    """
    if isinstance(data, pl.DataFrame):
        # Convert to Pandas DataFrame
        data = data.to_pandas()

        # Check if 'datetime' column exists and set it as the index
        if "datetime" in data.columns:
            data["datetime"] = pd.to_datetime(data["datetime"])
            data.set_index("datetime", inplace=True)

        return data

    elif isinstance(data, pl.Series):
        # Convert Polars Series to Pandas Series
        return data.to_pandas()

    elif isinstance(data, (pd.DataFrame, pd.Series)):
        # Return as-is if already a Pandas object
        return data

    else:
        raise TypeError("Input data must be Polars DataFrame, Polars Series, Pandas DataFrame, or Pandas Series.")


def resample_factor_pandas(df: pd.DataFrame, trading_freq: str, method: str = "mean") -> pd.DataFrame:
    """
    Resample factor data to match the specified trading frequency.

    Parameters:
        df (pd.DataFrame): Factor data with datetime as index.
        trading_freq (str): Desired trading frequency (e.g., '1H').
        method (str): Aggregation method for resampling. Options: 'mean', 'sum', 'max', 'min'.

    Returns:
        pd.DataFrame: Resampled factor data with left-closed intervals and right-labeled time.
    """
    if method not in ["mean", "sum", "max", "min"]:
        raise ValueError("Invalid method. Supported methods: 'mean', 'sum', 'max', 'min'.")

    try:
        # Use resample with label='right' and closed='left'
        if method == "mean":
            resampled_data = df.resample(trading_freq, label='right', closed='left').mean()
        elif method == "sum":
            resampled_data = df.resample(trading_freq, label='right', closed='left').sum()
        elif method == "max":
            resampled_data = df.resample(trading_freq, label='right', closed='left').max()
        elif method == "min":
            resampled_data = df.resample(trading_freq, label='right', closed='left').min()
        else:
            raise ValueError(f"Unsupported resampling method: {method}")
    except Exception as e:
        raise ValueError(f"Error occurred during factor resampling: {e}")

    return resampled_data


def resample_bar_pandas(memory_bar: Dict[str, pd.DataFrame], trading_freq: str) -> Dict[str, pd.DataFrame]:
    """
    Resample the OHLCV memory_bar to match the specified trading frequency.

    Parameters:
        memory_bar (dict): Original memory_bar with keys ('open', 'high', 'low', 'close', 'volume').
                     Each value is a DataFrame indexed by datetime.
        trading_freq (str): Desired trading frequency (e.g., '1H' for hourly, '1D' for daily).

    Returns:
        dict: Resampled memory_bar with the same keys.
    """
    if not all(key in memory_bar for key in ['open', 'high', 'low', 'close', 'volume']):
        raise ValueError("Data must include 'open', 'high', 'low', 'close', and 'volume' keys.")

    resampled_data = {}
    try:
        resampled_data = {
            'open': memory_bar['open'].resample(trading_freq, label='right', closed='left').first(),
            'high': memory_bar['high'].resample(trading_freq, label='right', closed='left').max(),
            'low': memory_bar['low'].resample(trading_freq, label='right', closed='left').min(),
            'close': memory_bar['close'].resample(trading_freq, label='right', closed='left').last(),
            'volume': memory_bar['volume'].resample(trading_freq, label='right', closed='left').sum()
        }
    except Exception as e:
        raise ValueError(f"Error occurred during resampling: {e}")

    return resampled_data


class FactorProcessor:
    """
    A class to preprocess factor values using cross-sectional rank or rolling Z-score.
    """

    def __init__(self, window: int = 20):
        """
        Initialize the FactorProcessor class.

        Parameters:
            window (int): Rolling window size for rolling Z-score. Default is 20.
        """
        self.window = window

    def rank_in_cross_section(self, factor_values: pd.DataFrame) -> pd.DataFrame:
        """
        Assign -1, 0, or 1 to each asset based on cross-sectional ranks.

        Parameters:
            factor_values (pd.DataFrame): Factor values with datetime as index.

        Returns:
            pd.DataFrame: Factor values with -1 (short), 0 (neutral), and 1 (long).
        """
        # Rank factors in cross-section for each row (datetime)
        ranks = factor_values.rank(axis=1, method="first")  # Rank starting from 1
        n_assets = factor_values.shape[1]  # Number of assets (columns)

        # Determine the cutoff for long and short positions
        midpoint = (n_assets + (n_assets % 2 == 0)) // 2

        # Assign -1, 0, 1 based on rank
        factor_signals = pd.DataFrame(0, index=factor_values.index, columns=factor_values.columns)
        factor_signals[ranks > midpoint] = 1  # Long positions (top half)
        factor_signals[ranks <= midpoint] = -1  # Short positions (bottom half)
        return factor_signals

    def rolling_z_score(self, factor_values: pd.DataFrame) -> pd.DataFrame:
        """
        Apply rolling Z-score normalization independently for each ticker.

        Parameters:
            factor_values (pd.DataFrame): Factor values with datetime as index.

        Returns:
            pd.DataFrame: Rolling Z-score normalized factor values.
        """
        rolling_mean = factor_values.rolling(window=self.window, min_periods=1).mean()
        # Avoid division by zero
        rolling_std = factor_values.rolling(window=self.window, min_periods=1).std().replace(0, 1)
        z_scores = (factor_values - rolling_mean) / rolling_std
        return z_scores

    def process(self, factor_values: pd.DataFrame, method: str = None) -> pd.DataFrame:
        """
        Process factor values using the specified method.

        Parameters:
            factor_values (pd.DataFrame): Factor values with datetime as index.
            method (str): Preprocessing method. Options are 'rank', 'rolling_z', or None (no preprocessing).

        Returns:
            pd.DataFrame: Processed factor values.
        """
        if method == "rank":
            return self.rank_in_cross_section(factor_values)
        elif method == "rolling_z":
            return self.rolling_z_score(factor_values)
        elif method is None:
            return factor_values  # No preprocessing
        else:
            raise ValueError(f"Unsupported method: {method}. Supported methods are 'rank', 'rolling_z', or None.")


class WeightProcessor:
    """
    A class to process portfolio weights, including normalization and sequential smoothing.
    """

    def __init__(self, smooth_coef: float = 0.3):
        self.smooth_coef = smooth_coef

    @staticmethod
    def to_weights(factor_signals: pd.DataFrame) -> pd.DataFrame:
        """
        Convert factor signals into portfolio weights by normalizing the factors.

        Parameters:
            factor_signals (pd.DataFrame): Factor signals with datetime as index and assets as columns.

        Returns:
            pd.DataFrame: Portfolio weights normalized by the sum of absolute factor values.
        """
        # Normalize factors by dividing each factor by the sum of absolute values for the row
        weights = factor_signals.div(factor_signals.abs().sum(axis=1), axis=0)

        # Replace NaN values with 0 in target_weights
        weights = weights.fillna(0)

        return weights

    @staticmethod
    def smooth_weights(target_weights: pd.DataFrame, coef: float = 0.9) -> pd.DataFrame:
        """
        Sequentially smooth portfolio weights starting from an initial weight of zero.

        Parameters:
            target_weights (pd.DataFrame): Target portfolio weights with datetime as index and assets as columns.
            coef (float): Smoothing coefficient. Controls the weight of the previous weights (0 <= coef <= 1).

        Returns:
            pd.DataFrame: Smoothed portfolio weights.
        """
        if not (0 <= coef <= 1):
            raise ValueError("Smoothing coefficient 'coef' must be between 0 and 1.")

        # Initialize smoothed weights with all zeros
        smoothed_weights = pd.DataFrame(0, index=target_weights.index, columns=target_weights.columns)

        # Set the first row of smoothed weights based on the first target weights
        smoothed_weights.iloc[0,:] = target_weights.iloc[0,:] * (1 - coef) + 1/len(target_weights.columns) * coef

        # Sequentially smooth weights row by row
        for i in range(1, len(target_weights)):
            smoothed_weights.iloc[i,:] = (
                    smoothed_weights.iloc[i - 1,:] * coef + target_weights.iloc[i,:] * (1 - coef)
            )

        return smoothed_weights

    def process(self, factor_signals: pd.DataFrame):

        weight = self.to_weights(factor_signals=factor_signals)
        smooth_weight = self.smooth_weights(weight, coef=self.smooth_coef)

        return smooth_weight

def fama_macbeth_regression(factor_values: pd.DataFrame, returns: pd.DataFrame,
                            rolling_window: int = 60) -> pd.DataFrame:
    """
    Perform Fama-MacBeth regression in two steps with dynamic betas (rolling time-series regression).

    Parameters:
        factor_values (pd.DataFrame): Factor values with datetime as index and tickers as columns.
        returns (pd.DataFrame): Asset returns with datetime as index and tickers as columns.
        rolling_window (int): Rolling window size for time-series regression.

    Returns:
        pd.DataFrame: DataFrame containing the factor returns and their t-stats.
    """

    # Ensure no NaNs in input data
    factor_values = factor_values.dropna(how="any", axis=0)
    returns = returns.dropna(how="any", axis=0)

    # Align factor values and returns
    factor_values, returns = factor_values.align(returns, join="inner", axis=0)

    # Step 1: Rolling time-series regression for dynamic betas
    dynamic_betas = pd.DataFrame(index=factor_values.index, columns=factor_values.columns)

    for ticker_idx in range(len(factor_values.columns)):
        ticker = factor_values.columns[ticker_idx]
        # Prepare rolling data
        y = returns[ticker]  # Ticker's returns
        X = factor_values[ticker]  # Ticker's factor values

        # Perform rolling regression to estimate beta
        for end in range(rolling_window, len(factor_values)):
            # Define rolling window
            y_window = y.iloc[end - rolling_window:end].astype(float)
            X_window = X.iloc[end - rolling_window:end].astype(float)

            # Add a constant for the intercept term
            X_window = sm.add_constant(X_window)

            # Perform OLS regression
            model = sm.OLS(y_window, X_window)
            results = model.fit()

            # Store the beta for the end period
            dynamic_betas.iloc[end, ticker_idx] = results.params[1]  # Coefficient of the factor

    # Step 2: Cross-sectional regression to estimate factor returns
    factor_returns = []
    for time in factor_values.index[rolling_window:]:  # Skip periods without beta data
        # Get cross-sectional returns and risk exposures (betas)
        y = returns.loc[time]
        X = dynamic_betas.loc[time]

        # Drop NaNs to handle missing betas
        valid_indices = X.notna()
        y = y[valid_indices].astype(float)
        X = X[valid_indices].astype(float)

        # Add a constant for the intercept term
        X = sm.add_constant(X)

        # Perform cross-sectional OLS regression
        model = sm.OLS(y, X)
        results = model.fit()

        # Store the factor return (coefficient of beta) at this time
        factor_returns.append(results.params[1])

    # Convert factor returns to a DataFrame
    factor_returns_df = pd.DataFrame({
        "Factor_Return": factor_returns
    }, index=factor_values.index[rolling_window:])

    # Calculate the mean and t-stat of the factor returns
    mean_return = factor_returns_df["Factor_Return"].mean()
    t_stat = mean_return / (factor_returns_df["Factor_Return"].std() / np.sqrt(len(factor_returns_df)))

    # Combine results
    results = pd.DataFrame({
        "Factor_Return": [mean_return],
        "t_stat": [t_stat]
    })

    return results
