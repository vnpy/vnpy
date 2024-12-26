from typing import Optional, Union, Dict, Any

import polars as pl

from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.trader.constant import Interval
from vnpy.app.factor_maker.base import FactorMode


class OPEN(FactorTemplate):
    factor_name = 'open'
    dependencies_factor = []
    freq = Interval.MINUTE
    factor_mode = FactorMode.Backtest

    def __init__(self, setting, **kwargs):
        super().__init__(setting, **kwargs)

    def __init_dependencies__(self):
        pass

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, Any]]], memory: Optional[pl.DataFrame] = None, *args, **kwargs) -> Any:
        if self.factor_mode not in [FactorMode.Backtest, FactorMode.Live]:
            raise ValueError("Invalid factor_mode. Must be 'Backtest' or 'Live'.")

        if isinstance(input_data, dict):
            open_data = input_data.get('open')
        elif isinstance(input_data, pl.DataFrame):
            open_data = input_data
        else:
            raise ValueError("Invalid input_data format. Expected pl.DataFrame or Dict[str, pl.DataFrame].")

        if not isinstance(open_data, pl.DataFrame):
            raise ValueError("'open' data must be a Polars DataFrame.")

        return open_data

    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        pass


class VOLUME(FactorTemplate):
    factor_name = 'volume'
    dependencies_factor = []
    freq = Interval.MINUTE
    factor_mode = FactorMode.Backtest

    def __init__(self, setting, **kwargs):
        super().__init__(setting, **kwargs)

    def __init_dependencies__(self):
        pass

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, Any]]], memory: Optional[pl.DataFrame] = None, *args, **kwargs) -> Any:
        if self.factor_mode not in [FactorMode.Backtest, FactorMode.Live]:
            raise ValueError("Invalid factor_mode. Must be 'Backtest' or 'Live'.")

        if isinstance(input_data, dict):
            volume_data = input_data.get('volume')
        elif isinstance(input_data, pl.DataFrame):
            volume_data = input_data
        else:
            raise ValueError("Invalid input_data format. Expected pl.DataFrame or Dict[str, pl.DataFrame].")

        if not isinstance(volume_data, pl.DataFrame):
            raise ValueError("'volume' data must be a Polars DataFrame.")

        return volume_data

    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        pass

class VWAP(FactorTemplate):
    factor_name = 'vwap'
    dependencies_factor = []
    freq = Interval.MINUTE
    factor_mode = FactorMode.Backtest

    def __init__(self, setting, window: int = None):
        """
        Initialize VWAP with its settings and rolling window size.
        """
        super().__init__(setting, window=window)

    def __init_dependencies__(self):
        """
        Define dependencies for the VWAP factor.
        """
        self.open = OPEN({})
        self.volume = VOLUME({})
        self.open.factor_mode = self.factor_mode
        self.volume.factor_mode = self.factor_mode
        setattr(self, 'dependencies_factor', [self.open, self.volume])

    def calculate(self, input_data: Dict[str, Any], memory: Optional[pl.DataFrame] = None, *args, **kwargs) -> pl.DataFrame:
        """
        Calculate the rolling VWAP (Volume Weighted Average Price) for Live Trading or Backtesting.

        Parameters:
            input_data (Dict[str, Any]): Input bar_data with keys for 'open' and 'volume' from dependent factors.
            memory (Optional[pl.DataFrame]): Current factor memory (used in Live Trading mode).

        Returns:
            pl.DataFrame: Updated VWAP DataFrame.
        """
        # Validate factor_mode
        if self.factor_mode not in [FactorMode.Backtest, FactorMode.Live]:
            raise ValueError("Invalid factor_mode. Must be 'Backtest' or 'Live'.")

        # Retrieve open and volume data
        open_prices = input_data.get(self.open.factor_key)
        volumes = input_data.get(self.volume.factor_key)

        # Ensure both are Polars DataFrames
        if not isinstance(open_prices, pl.DataFrame) or not isinstance(volumes, pl.DataFrame):
            raise ValueError("Both open and volume bar_data must be Polars DataFrames.")

        # Check for rolling window
        window = self.params.get_parameter('window')
        if window is None:
            raise ValueError("The rolling window size (window) is not set.")

        if self.factor_mode == FactorMode.Live:
            # Live Mode: Ensure memory is provided
            if memory is None:
                raise ValueError("Memory must be provided in 'Live' mode.")

            # Get tail(window) of the input data
            open_tail = open_prices.tail(window)
            volume_tail = volumes.tail(window)

            # Drop the datetime column for calculation
            datetime_col = open_tail["datetime"].tail(1)  # Latest datetime
            open_tail = open_tail.drop("datetime")
            volume_tail = volume_tail.drop("datetime")

            # Calculate VWAP for the latest row
            weighted_prices = open_tail * volume_tail
            sum_weighted = weighted_prices.sum(axis=0)
            sum_volume = volume_tail.sum(axis=0)
            latest_vwap = sum_weighted / sum_volume

            # Append the latest VWAP to memory
            new_row = pl.DataFrame({
                "datetime": datetime_col,
                **{col: [latest_vwap[col]] for col in latest_vwap.columns}
            })
            memory = pl.concat([memory, new_row], how="vertical")
            return memory

        elif self.factor_mode == FactorMode.Backtest:
            # Backtesting Mode: Perform calculations on the entire dataset
            # Preserve the datetime column
            datetime_col = None
            if "datetime" in open_prices.columns and "datetime" in volumes.columns:
                datetime_col = open_prices["datetime"]
                open_prices = open_prices.drop("datetime")
                volumes = volumes.drop("datetime")

            # Calculate VWAP: rolling sum(open * volume) / rolling sum(volume)
            weighted_prices = open_prices * volumes
            rolling_sum_weighted = weighted_prices.select([
                pl.col(col).rolling_sum(window).alias(col) for col in weighted_prices.columns
            ])
            rolling_sum_volume = volumes.select([
                pl.col(col).rolling_sum(window).alias(col) for col in volumes.columns
            ])
            vwap = rolling_sum_weighted / rolling_sum_volume

            # Add the datetime column back to the result if it exists
            if datetime_col is not None:
                vwap = vwap.insert_column(0, datetime_col)

            return vwap
class MA(FactorTemplate):
    factor_name = 'ma'
    dependencies_factor = []
    freq = Interval.MINUTE
    factor_mode = FactorMode.Backtest

    def __init__(self, setting, window: int = None):
        """
        Initialize the MA factor with its settings and rolling window size.
        """
        super().__init__(setting, window=window)

    def __init_dependencies__(self):
        """
        Define dependencies for the MA factor.
        """
        self.vwap = VWAP({}, window=20)
        setattr(self, 'dependencies_factor', [self.vwap])

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, pl.DataFrame]]], memory: Optional[pl.DataFrame] = None, *args, **kwargs) -> Any:
        """
        Calculate the rolling mean for all columns in the input data for Live Trading or Backtesting.

        Parameters:
            input_data (Optional[Union[pl.DataFrame, Dict[str, pl.DataFrame]]]): Input data with symbols as columns.
            memory (Optional[pl.DataFrame]): Current factor memory (used in Live Trading mode).

        Returns:
            pl.DataFrame: DataFrame with the rolling mean for each symbol.
        """
        # Validate factor_mode
        if self.factor_mode not in [FactorMode.Backtest, FactorMode.Live]:
            raise ValueError("Invalid factor_mode. Must be 'Backtest' or 'Live'.")

        # Retrieve input data
        if isinstance(input_data, dict):
            df = input_data.get(self.vwap.factor_key)
        elif isinstance(input_data, pl.DataFrame):
            df = input_data
        else:
            raise ValueError("Invalid input_data format. Expected pl.DataFrame or Dict[str, pl.DataFrame].")

        # Ensure the input data is a Polars DataFrame
        if not isinstance(df, pl.DataFrame):
            raise ValueError("Input data must be a Polars DataFrame.")

        # Get the rolling window size
        window = self.params.get_parameter('window')
        if window is None:
            raise ValueError("The rolling window size (window) is not set.")

        if self.factor_mode == FactorMode.Live:
            # Live Mode: Ensure memory is provided
            if memory is None:
                raise ValueError("Memory must be provided in 'Live' mode.")

            # Get tail(window) of the input data
            latest_data = df.tail(window)

            # Drop the datetime column for calculation
            datetime_col = latest_data["datetime"].tail(1)  # Latest datetime
            latest_data = latest_data.drop("datetime")

            # Calculate rolling mean for the latest row
            rolling_means = latest_data.mean(axis=0)

            # Create a new row for the memory update
            new_row = pl.DataFrame({
                "datetime": datetime_col,
                **{col: [rolling_means[col]] for col in latest_data.columns}
            })

            # Update memory
            memory = pl.concat([memory, new_row], how="vertical")
            return memory

        elif self.factor_mode == FactorMode.Backtest:
            # Backtesting Mode: Perform calculations on the entire dataset
            # Preserve datetime column
            datetime_col = None
            if "datetime" in df.columns:
                datetime_col = df["datetime"]
                df = df.drop("datetime")

            # Calculate rolling mean for all columns except datetime
            columns_to_aggregate = [col for col in df.columns if col != 'datetime']
            rolling_means = df.select([
                pl.col(col).rolling_mean(window).alias(col) for col in columns_to_aggregate
            ])

            # Add datetime column back to the result if it exists
            if datetime_col is not None:
                rolling_means = rolling_means.insert_column(0, datetime_col)

            return rolling_means

class MACD(FactorTemplate):
    factor_name = 'macd'
    dependencies_factor = []
    freq = Interval.MINUTE
    factor_mode = FactorMode.Backtest

    def __init__(self, setting, fast_period: int = None, slow_period: int = None, signal_period: int = None):
        super().__init__(setting=setting, fast_period=fast_period, slow_period=slow_period, signal_period=signal_period)

    def __init_dependencies__(self):
        self.ma_fast = MA({}, self.params.get_parameter('fast_period'))
        self.ma_slow = MA({}, self.params.get_parameter('slow_period'))
        self.ma_fast.factor_mode = self.factor_mode
        self.ma_slow.factor_mode = self.factor_mode
        setattr(self, 'dependencies_factor', [self.ma_fast, self.ma_slow])

    def calculate(self, input_data: Optional[Dict[str, pl.DataFrame]], memory: Optional[pl.DataFrame] = None, *args, **kwargs) -> pl.DataFrame:
        if self.factor_mode not in [FactorMode.Backtest, FactorMode.Live]:
            raise ValueError("Invalid factor_mode. Must be 'Backtest' or 'Live'.")

        ma_fast = input_data.get(self.ma_fast.factor_key)
        ma_slow = input_data.get(self.ma_slow.factor_key)

        if ma_fast is None or ma_slow is None:
            raise ValueError("Missing required moving averages (ma_fast or ma_slow) in input_data.")

        if not isinstance(ma_fast, pl.DataFrame) or not isinstance(ma_slow, pl.DataFrame):
            raise ValueError("ma_fast and ma_slow must be Polars DataFrames.")

        if self.factor_mode == FactorMode.Live:
            if memory is None:
                raise ValueError("Memory must be provided in 'Live' mode.")

            ma_fast_tail = ma_fast.tail(self.params.get_parameter('signal_period'))
            ma_slow_tail = ma_slow.tail(self.params.get_parameter('signal_period'))

            datetime_col = ma_fast_tail["datetime"].tail(1)
            macd_line = ma_fast_tail - ma_slow_tail
            signal_line = macd_line.mean(axis=0)

            last_histogram = (macd_line.tail(1) - signal_line).to_dict(as_series=False)

            new_row = pl.DataFrame({
                "datetime": datetime_col,
                **{col: [last_histogram[col]] for col in macd_line.columns},
            })
            memory = pl.concat([memory, new_row], how="vertical")
            return memory

        elif self.factor_mode == FactorMode.Backtest:
            datetime_col = None
            if "datetime" in ma_fast.columns and "datetime" in ma_slow.columns:
                datetime_col = ma_fast["datetime"]
                ma_fast = ma_fast.drop("datetime")
                ma_slow = ma_slow.drop("datetime")

            macd_line = ma_fast - ma_slow
            signal_line = macd_line.select([
                pl.col(col).rolling_mean(self.params.get_parameter('signal_period')).alias(col)
                for col in macd_line.columns
            ])
            histogram = macd_line - signal_line

            if datetime_col is not None:
                histogram = histogram.insert_column(0, datetime_col)

            return histogram


# Example usage with synthetic data
import numpy as np
import pandas as pd
from datetime import datetime, timedelta

date_range = pd.date_range("2024-01-01", periods=200, freq="1min")
raw_data = {
    "open": pl.DataFrame({
        "datetime": date_range,
        "AAPL": np.random.uniform(150, 155, size=200),
        "MSFT": np.random.uniform(300, 305, size=200),
        "GOOG": np.random.uniform(2800, 2810, size=200),
    }),
    "high": pl.DataFrame({
        "datetime": date_range,
        "AAPL": np.random.uniform(155, 160, size=200),
        "MSFT": np.random.uniform(305, 310, size=200),
        "GOOG": np.random.uniform(2810, 2820, size=200),
    }),
    "low": pl.DataFrame({
        "datetime": date_range,
        "AAPL": np.random.uniform(145, 150, size=200),
        "MSFT": np.random.uniform(295, 300, size=200),
        "GOOG": np.random.uniform(2790, 2800, size=200),
    }),
    "close": pl.DataFrame({
        "datetime": date_range,
        "AAPL": np.random.uniform(150, 155, size=200),
        "MSFT": np.random.uniform(300, 305, size=200),
        "GOOG": np.random.uniform(2800, 2810, size=200),
    }),
    "volume": pl.DataFrame({
        "datetime": date_range,
        "AAPL": np.random.randint(1000, 2000, size=200),
        "MSFT": np.random.randint(1000, 2000, size=200),
        "GOOG": np.random.randint(1000, 2000, size=200),
    }),
}

# Add MACD factor example
macd = MACD({}, fast_period=5, slow_period=20, signal_period=5)
macd.factor_mode = FactorMode.Backtest
# Perform calculations or integrate with optimizer or backtester

from vnpy.app.factor_maker.backtesting import FactorBacktester
from vnpy.app.factor_maker.optimizer import FactorOptimizer

# Step 1: Create Backtester
backtester = FactorBacktester(
    data=raw_data,  # Use synthetic OHLCV data
    commission_rate=0.001,
    slippage=0.001,
    trading_freq="1h"
)

# Step 2: Initialize Optimizer
optimizer = FactorOptimizer(backtester=backtester, memory_bar=raw_data)

# Step 3: Add Factor to Optimizer
optimizer.add_factor(macd)

# Step 4: Define Parameter Grid for Optimization
param_grid = {
    "signal_period": [2, 3, 5, 8, 10]
}

# Step 5: Optimize Parameters
best_params = optimizer.optimize(param_grid, metric="Sharpe Ratio")

# Step 6: Display Optimization Results
print("Best Parameters:", best_params["best_params"])
print("Best Sharpe Ratio:", best_params["best_score"])

# Step 7: Perform Backtesting with Best Parameters
macd.set_params(best_params["best_params"])
factor_values = macd.calculate(optimizer.memory_factor)
performance_metrics = backtester.run_backtesting_polars(factor_values, if_plot=True)

# Step 8: Display Performance Metrics
print("\nPerformance Metrics:")
for metric, value in performance_metrics.items():
    print(f"{metric}: {value:.4f}")