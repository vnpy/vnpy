from datetime import timedelta, datetime
from typing import List, Optional

import numpy as np
from matplotlib import pyplot as plt

from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.portfolio_strategy.base import EngineType
from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.database import BaseDatabase, get_database
from vnpy.trader.object import BarData, FactorData
import polars as pl

from vnpy.trader.utility import extract_vt_symbol, convert_dict_to_dataframe

INTERVAL_DELTA_MAP: dict[Interval, timedelta] = {
    Interval.MINUTE: timedelta(minutes=1),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta(days=1),
}


from bayes_opt import BayesianOptimization

class FactorOptimizer:
    """Optimizer class for factor parameters."""

    def __init__(self, engine: "FactorBacktestingEngine"):
        """
        Initialize the optimizer with the backtesting engine.

        Parameters:
            engine (FactorBacktestingEngine): The backtesting engine instance.
        """
        self.engine = engine
        self.optimizer = None  # Placeholder for the optimizer instance
        self.best_params = None  # To store the best parameters found
        self.best_sharpe_ratio = None  # To store the best Sharpe ratio on test data

    def objective_function(self, **factor_params):
        """
        Objective function for optimization.
        Returns the negative Sharpe ratio on the training data.

        Parameters:
            **factor_params: Arbitrary keyword arguments representing factor parameters.

        Returns:
            float: Negative Sharpe ratio on training data.
        """
        # Recalculate factor data with new parameters
        self.engine.calculate_factor(factor_params)

        # Run backtesting on training data
        _, performance_metrics = self.engine.run_backtesting_positions(
            bar_data=self.engine.bar_data_train,
            factor_data=self.engine.factor_data_train
        )

        # Extract the Sharpe ratio
        sharpe_ratio = performance_metrics.get('Sharpe Ratio', np.nan)

        # Handle cases where Sharpe Ratio is NaN
        if np.isnan(sharpe_ratio):
            self.engine.write_log("Sharpe Ratio is NaN on training data. Returning a large negative value.")
            return -np.inf

        # Since we want to maximize Sharpe ratio, return its negative
        return -sharpe_ratio

    def optimize(self, param_bounds: dict, init_points: int = 5, n_iter: int = 25, sharpe_threshold: float = 5.0):
        """
        Run the optimization process using training data and validate on test data.

        Parameters:
            param_bounds (dict): Parameter bounds for optimization.
            init_points (int): Number of initial random evaluations.
            n_iter (int): Number of iterations.
            sharpe_threshold (float): Sharpe ratio threshold for test data.

        Returns:
            dict or None: Best parameters if Sharpe ratio on test data exceeds threshold, else None.
        """
        # Create the optimizer
        self.optimizer = BayesianOptimization(
            f=self.objective_function,
            pbounds=param_bounds,
            random_state=42
        )

        # Run the optimizer
        self.optimizer.maximize(
            init_points=init_points,
            n_iter=n_iter,
        )

        # Get the best parameters from optimization
        best_params = self.optimizer.max['params']
        self.engine.write_log(f"Best parameters on training data: {best_params}")

        # Recalculate factor data with best parameters
        self.engine.calculate_factor(best_params)

        # Run backtesting on test data
        _, performance_metrics = self.engine.run_backtesting_positions(
            bar_data=self.engine.bar_data_test,
            factor_data=self.engine.factor_data_test
        )

        # Extract the Sharpe ratio on test data
        test_sharpe_ratio = performance_metrics.get('Annualized Sharpe Ratio', np.nan)
        self.engine.write_log(f"Sharpe Ratio on test data: {test_sharpe_ratio}")

        # Check if Sharpe ratio on test data exceeds the threshold
        if test_sharpe_ratio > sharpe_threshold:
            self.engine.write_log(f"Sharpe Ratio on test data exceeds threshold of {sharpe_threshold}.")
            self.best_params = best_params
            self.best_sharpe_ratio = test_sharpe_ratio
            return {
                'params': best_params,
                'sharpe_ratio': test_sharpe_ratio
            }
        else:
            self.engine.write_log(f"Sharpe Ratio on test data does not exceed threshold of {sharpe_threshold}.")
            return None


class FactorBacktestingEngine:
    """Factor Backtesting Engine."""

    engine_type: EngineType = EngineType.BACKTESTING
    gateway_name: str = "BACKTESTING"

    def __init__(self) -> None:
        self.vt_symbols: List[str] = []
        self.start: datetime = None
        self.end: datetime = None

        self.interval: Interval = Interval.MINUTE
        self.period_per_year = timedelta(days=365) / INTERVAL_DELTA_MAP[self.interval]

        self.factor_name: str = ""
        self.factor_source: str = "database"

        self.commission_rate: float = 0.0
        self.slippage: float = 0.0
        self.size: int = 1
        self.price_tick: float = 0.0

        self.logs: List[str] = []

        self.database: BaseDatabase = get_database()
        self.factor: Optional[FactorTemplate] = None

        self.dts = set()
        self.bar_data_dict: dict[str, pl.DataFrame] = None
        self.bar_data: pl.DataFrame = None
        self.factor_data: pl.DataFrame = None

        # Data splits
        self.bar_data_train: pl.DataFrame = None
        self.bar_data_test: pl.DataFrame = None
        self.factor_data_train: pl.DataFrame = None
        self.factor_data_test: pl.DataFrame = None

    def clear_data(self) -> None:
        """Clear data."""
        self.logs.clear()
        self.clear_bar()
        self.clear_factor()

    def clear_bar(self) -> None:
        """Clear bar data."""
        self.bar_data = None

    def clear_factor(self) -> None:
        """Clear factor data."""
        self.factor_data = None

    def set_parameters(
            self,
            vt_symbols: List[str],
            start: datetime,
            end: datetime,
            interval: Interval,
            commission_rate: float,
            slippage: float,
            size: int,
            price_tick: float
    ) -> None:
        """
        Set backtesting parameters.

        Parameters:
            vt_symbols (list[str]): List of symbols.
            start (datetime): Start date.
            end (datetime): End date.
            interval (Interval): Data interval.
            commission_rate (float): Commission rate per trade.
            slippage (float): Slippage per trade.
            size (int): Contract size.
            price_tick (float): Minimum price movement.
        """
        self.vt_symbols = vt_symbols
        self.start = start
        self.end = end
        self.interval = interval
        self.commission_rate = commission_rate
        self.slippage = slippage
        self.size = size
        self.price_tick = price_tick

        # Determine factor source and name based on self.factor
        if self.factor is not None:
            self.factor_source = "calculation"
            self.factor_name = self.factor.factor_name
        else:
            self.factor_source = "database"
            # self.factor_name should be set separately if loading from database

    def load_data(self) -> None:
        """Load data."""
        self.clear_data()
        self.load_bars()

        # Decide how to load factor data based on factor_source
        if self.factor_source == "database":
            if not self.factor_name:
                raise ValueError("Factor name must be set when loading from database.")
            self.load_factor()
        elif self.factor_source == "calculation":
            if self.factor is None:
                raise ValueError("Factor template must be set when calculating factors.")
            # Calculate factor with default parameters
            self.calculate_factor({})
        else:
            raise ValueError(f"Unknown factor source: {self.factor_source}")

        # Align bar data and factor data
        self.bar_data, self.factor_data = pl.align_frames(
            self.bar_data, self.factor_data, on="datetime", how="inner"
        )

        # Split bar data and factor data into train and test sets
        self.bar_data_train, self.bar_data_test = self.bar_data.split_in_two(frac=0.8)
        self.factor_data_train, self.factor_data_test = self.factor_data.split_in_two(frac=0.8)

    def load_bars_csv(self, file_path: str) -> None:
        pass

    def load_bars(self):
        """加载K线数据"""
        self.write_log("开始加载历史数据")

        if not self.end:
            self.end = datetime.now()

        if self.start >= self.end:
            self.write_log(f"起始日期必须小于结束日期")
            return

        # 清理上次加载的历史数据
        bar_dict_open = {}
        bar_dict_high = {}
        bar_dict_low = {}
        bar_dict_close = {}
        self.dts.clear()

        # 每次加载30天历史数据
        progress_delta: timedelta = timedelta(days=30)
        total_delta: timedelta = self.end - self.start
        interval_delta: timedelta = INTERVAL_DELTA_MAP[self.interval]

        for vt_symbol in self.vt_symbols:
            symbol, exchange = extract_vt_symbol(vt_symbol)
            if self.interval == Interval.MINUTE:
                start: datetime = self.start
                end: datetime = self.start + progress_delta
                progress = 0

                data_count = 0
                while start < self.end:
                    end = min(end, self.end)

                    data: list[BarData] = self.database.load_bar_data(
                        symbol=symbol,
                        exchange=exchange,
                        interval=self.interval,
                        start=start,
                        end=end
                    )

                    for bar in data:
                        self.dts.add(bar.datetime)
                        bar_dict_open[(bar.datetime, vt_symbol)] = bar.open_price
                        bar_dict_high[(bar.datetime, vt_symbol)] = bar.high_price
                        bar_dict_low[(bar.datetime, vt_symbol)] = bar.low_price
                        bar_dict_close[(bar.datetime, vt_symbol)] = bar.close_price
                        data_count += 1

                    progress += progress_delta / total_delta
                    progress = min(progress, 1)
                    self.write_log(
                        "{}加载进度：[{:.0%}]".format(
                            vt_symbol, progress
                        )
                    )

                    start = end + interval_delta
                    end += (progress_delta + interval_delta)
            else:
                data: list[BarData] = self.database.load_bar_data(
                    symbol=symbol,
                    exchange=exchange,
                    interval=self.interval,
                    start=self.start,
                    end=self.end
                )

                for bar in data:
                    self.dts.add(bar.datetime)
                    bar_dict_open[(bar.datetime, vt_symbol)] = bar.open_price
                    bar_dict_high[(bar.datetime, vt_symbol)] = bar.high_price
                    bar_dict_low[(bar.datetime, vt_symbol)] = bar.low_price
                    bar_dict_close[(bar.datetime, vt_symbol)] = bar.close_price

                data_count = len(data)

            self.write_log("{}历史数据加载完成，数据量：{}".format(vt_symbol, data_count))

        self.bar_data_dict['open'] = convert_dict_to_dataframe(data=bar_dict_open, is_polars=True)
        self.bar_data_dict['high'] = convert_dict_to_dataframe(data=bar_dict_high, is_polars=True)
        self.bar_data_dict['low'] = convert_dict_to_dataframe(data=bar_dict_low, is_polars=True)
        self.bar_data_dict['close'] = convert_dict_to_dataframe(data=bar_dict_close, is_polars=True)

        self.bar_data = compose_bar(self.bar_data_dict)

        self.write_log("所有历史数据加载完成")

    def load_factor(self):

        self.write_log("开始加载因子数据")
        factor_dict = {}
        for vt_symbol in self.vt_symbols:
            symbol, exchange = extract_vt_symbol(vt_symbol)
            data: list[FactorData] = self.database.load_factor_data(
                symbol=symbol,
                factor_name=self.factor_name,
                start=self.start,
                end=self.end,
                interval=self.interval
            )
            for factor_data in data:
                factor_dict[(factor_data.datetime, symbol)] = factor_data.value
        self.factor_data: pl.DataFrame = convert_dict_to_dataframe(data=factor_dict, is_polars=True)
        # row index: datetime, column index: symbol:btcusdt

        self.write_log("因子数据加载完成")

    def calculate_factor(self, factor_params: dict) -> None:
        """Calculate factor data using provided parameters"""
        self.write_log("Calculating factor data with new parameters")
        self.factor.set_params(factor_params)
        self.factor_data = self.factor.make_factor(self.bar_data_dict)

        # Align bar data and factor data
        self.bar_data, self.factor_data = pl.align_frames(
            self.bar_data, self.factor_data, on="datetime", how="inner"
        )

        # Split factor data into train and test sets
        self.factor_data_train, self.factor_data_test = self.factor_data.split_in_two(frac=0.8)

        self.write_log("Factor data calculation completed")

    def run_backtesting_groups(
        self,
        bar_data: pl.DataFrame,
        factor_data: pl.DataFrame,
        n_groups: int,
        if_plot: bool = False
    ):
        """
        Run backtesting by grouping securities based on factor quantiles.

        Parameters:
            bar_data (pl.DataFrame): Bar data.
            factor_data (pl.DataFrame): Factor data.
            n_groups (int): Number of groups to divide securities into.
            if_plot (bool): Whether to plot the results.

        Returns:
            tuple: (portfolio_values, performance_metrics, ic_series, ir)
        """
        self.write_log("Starting backtesting with groups.")
        dates = bar_data['datetime'].to_numpy()

        # Convert to numpy arrays
        close_prices_np = bar_data.drop('datetime').to_numpy()
        factor_values_np = factor_data.drop('datetime').to_numpy()

        num_dates = len(dates)

        # Initialize portfolio values and daily returns
        portfolio_values = np.ones((n_groups, num_dates))
        daily_returns = np.zeros((n_groups, num_dates))

        # Initialize IC series
        ic_series = []

        for i in range(1, num_dates):
            current_factor = factor_values_np[i - 1]
            future_returns = (close_prices_np[i] / close_prices_np[i - 1]) - 1

            # Handle missing data
            valid = (~np.isnan(current_factor) & ~np.isnan(future_returns))
            if valid.sum() < n_groups:
                ic_series.append(np.nan)
                continue  # Skip if not enough data

            current_factor = current_factor[valid]
            future_returns = future_returns[valid]

            # Calculate IC
            ic = np.corrcoef(current_factor, future_returns)[0, 1]
            ic_series.append(ic)

            # Rank tickers based on factor values
            ranks = np.argsort(current_factor)
            group_size = len(ranks) // n_groups

            groups = []
            for j in range(n_groups):
                if j == n_groups - 1:
                    groups.append(ranks[j * group_size:])
                else:
                    groups.append(ranks[j * group_size: (j + 1) * group_size])

            # Calculate returns and update portfolios
            for j, group in enumerate(groups):
                returns = future_returns[group]
                returns -= self.slippage
                returns *= (1 - self.commission_rate)
                mean_return = np.mean(returns)
                daily_returns[j, i] = mean_return
                portfolio_values[j, i] = portfolio_values[j, i - 1] * (1 + mean_return)

        # Calculate performance metrics
        performance_metrics = {}
        for j in range(n_groups):
            cumulative_return = portfolio_values[j, -1] - 1
            sharpe_ratio = (
                np.mean(daily_returns[j]) / np.std(daily_returns[j])
            ) * np.sqrt(self.period_per_year)
            performance_metrics[f'Group {j + 1}'] = {
                'Cumulative Return': cumulative_return,
                'Annualized Sharpe Ratio': sharpe_ratio
            }

        # Calculate IR
        ic_series = np.array(ic_series)
        valid_ic = ic_series[~np.isnan(ic_series)]
        mean_ic = np.mean(valid_ic)
        std_ic = np.std(valid_ic)
        ir = mean_ic / std_ic if std_ic != 0 else np.nan

        if if_plot:
            # Plot performance and IC series
            self.plot_portfolio_performance(portfolio_values, dates, n_groups)
            # Implement plot_ic_series if needed

        return portfolio_values, performance_metrics, ic_series, ir

    def run_backtesting_positions(
        self,
        bar_data: pl.DataFrame,
        factor_data: pl.DataFrame,
        if_plot: bool = False
    ):
        """
        Backtest a strategy where factor values represent positions in tickers,
        normalized so that the sum of absolute positions equals 1.

        Parameters:
            bar_data (pl.DataFrame): Close prices indexed by datetime, columns as tickers.
            factor_data (pl.DataFrame): Factor values indexed by datetime, columns as tickers.
            if_plot (bool): Whether to plot the portfolio performance.

        Returns:
            tuple: (portfolio_values, performance_metrics)
        """
        self.write_log("Starting backtesting with positions.")
        dates = bar_data['datetime'].to_numpy()
        tickers = bar_data.columns[1:]

        # Convert to numpy arrays
        close_prices_np = bar_data.drop('datetime').to_numpy()
        factor_values_np = factor_data.drop('datetime').to_numpy()

        num_dates = len(dates)
        num_tickers = len(tickers)

        # Initialize portfolio value and positions
        portfolio_values = np.ones(num_dates)
        positions = np.zeros((num_dates, num_tickers))  # Store positions over time
        turnover = np.zeros(num_dates)  # Track portfolio turnover

        for i in range(1, num_dates):
            # Get current factor values and close prices
            factor_values = factor_values_np[i]
            current_close = close_prices_np[i]
            previous_close = close_prices_np[i - 1]

            # Handle missing data
            valid = (~np.isnan(factor_values) &
                     ~np.isnan(current_close) &
                     ~np.isnan(previous_close))
            if valid.sum() == 0:
                portfolio_values[i] = portfolio_values[i - 1]
                continue  # Skip if no valid data

            # Select valid data
            factor_values_valid = factor_values[valid]
            current_close_valid = current_close[valid]
            previous_close_valid = previous_close[valid]

            # Normalize factor values to get positions
            abs_sum = np.sum(np.abs(factor_values_valid))
            if abs_sum == 0:
                normalized_positions = np.zeros_like(factor_values_valid)
            else:
                normalized_positions = factor_values_valid / abs_sum

            # Store positions (for valid tickers only)
            positions_i = np.zeros(num_tickers)
            positions_i[valid] = normalized_positions
            positions[i] = positions_i

            # Calculate portfolio turnover (sum of absolute changes in positions)
            if i == 1:
                turnover[i] = np.sum(np.abs(positions[i]))
            else:
                turnover[i] = np.sum(np.abs(positions[i] - positions[i - 1]))

            # Calculate gross returns
            returns = (current_close_valid - previous_close_valid) / previous_close_valid

            # Calculate portfolio return
            portfolio_return = np.sum(normalized_positions * returns)

            # Adjust for transaction costs on turnover
            transaction_cost = turnover[i] * (self.commission_rate + self.slippage)

            # Update portfolio value
            portfolio_values[i] = portfolio_values[i - 1] * (1 + portfolio_return - transaction_cost)

        # Calculate performance metrics
        total_return = portfolio_values[-1] / portfolio_values[0] - 1
        daily_returns = np.diff(portfolio_values) / portfolio_values[:-1]
        annualized_return = np.mean(daily_returns) * self.period_per_year
        annualized_volatility = np.std(daily_returns) * np.sqrt(self.period_per_year)
        sharpe_ratio = (
            annualized_return / annualized_volatility if annualized_volatility != 0 else np.nan
        )

        performance_metrics = {
            'Cumulative Return': total_return,
            'Annualized Return': annualized_return,
            'Annualized Volatility': annualized_volatility,
            'Annualized Sharpe Ratio': sharpe_ratio
        }

        if if_plot:
            # Plot portfolio performance
            self.plot_portfolio_performance_position(portfolio_values, dates)

        return portfolio_values, performance_metrics

    def write_log(self, msg) -> None:
        """输出回测引擎信息"""
        print(f"{datetime.now()}\t{msg}")

    def plot_portfolio_performance_position(self, portfolio_values, dates):
        """
            Plot the portfolio value over time.

            Parameters:
                portfolio_values (np.ndarray): Portfolio value over time.
                dates (np.ndarray): Array of dates.
            """
        plt.figure(figsize=(14, 7))
        plt.plot(dates, portfolio_values, label='Portfolio Value')
        plt.title('Portfolio Performance Over Time')
        plt.xlabel('Date')
        plt.ylabel('Portfolio Value')
        plt.legend()
        plt.xticks(rotation=45)
        plt.grid(True)
        plt.tight_layout()
        plt.show()

    def plot_portfolio_performance(self, portfolio_values, dates, n_groups):
        """
            Plot the cumulative portfolio values over time.

            Parameters:
                portfolio_values (np.ndarray): Portfolio values for each group.
                dates (np.ndarray): Array of dates.
                n_groups (int): Number of groups.
            """
        plt.figure(figsize=(14, 7))
        for i in range(n_groups):
            plt.plot(dates, portfolio_values[i], label=f'Group {i + 1}')
        plt.title('Portfolio Performance by Group')
        plt.xlabel('Date')
        plt.ylabel('Cumulative Portfolio Value')
        plt.legend()
        plt.xticks(rotation=45)
        plt.grid(True)
        plt.tight_layout()
        plt.show()


def compose_bar(bar_dict: dict[str, pl.DataFrame]) -> pl.DataFrame:
    """
    Compose bar data from open, high, low, close data into mean of OHLC.

    Parameters:
        bar_dict (dict[str, pl.DataFrame]): Dictionary containing 'open', 'high', 'low', 'close' DataFrames.
            Each DataFrame has 'datetime' as the first column and symbols as subsequent columns.

    Returns:
        pl.DataFrame: DataFrame with mean OHLC values, rows are 'datetime', columns are symbols.
    """
    # Extract DataFrames from the dictionary
    open_df = bar_dict.get('open')
    high_df = bar_dict.get('high')
    low_df = bar_dict.get('low')
    close_df = bar_dict.get('close')

    # Check that all DataFrames are present
    if any(df is None for df in [open_df, high_df, low_df, close_df]):
        raise ValueError("bar_dict must contain 'open', 'high', 'low', and 'close' DataFrames.")

    # Align DataFrames on 'datetime' column
    aligned_dfs = pl.align_frames(open_df, high_df, low_df, close_df, on='datetime', how='inner')

    # Unpack the aligned DataFrames
    open_df_aligned, high_df_aligned, low_df_aligned, close_df_aligned = aligned_dfs

    # Extract 'datetime' column
    datetime_col = open_df_aligned['datetime']

    # Drop 'datetime' column from each DataFrame to perform arithmetic operations
    open_values = open_df_aligned.drop('datetime')
    high_values = high_df_aligned.drop('datetime')
    low_values = low_df_aligned.drop('datetime')
    close_values = close_df_aligned.drop('datetime')

    # Compute the mean of OHLC for each cell
    mean_values = (open_values + high_values + low_values + close_values) / 4

    # Concatenate 'datetime' column back with the mean values
    mean_df = pl.concat([datetime_col, mean_values], how='horizontal')

    # Return the resulting DataFrame with mean OHLC values
    return mean_df

