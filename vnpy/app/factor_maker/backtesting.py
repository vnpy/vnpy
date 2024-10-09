from datetime import timedelta, datetime

import numpy as np
from matplotlib import pyplot as plt

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


class FactorBacktestingEngine:
    """因子回测引擎"""

    engine_type: EngineType = EngineType.BACKTESTING
    gateway_name: str = "BACKTESTING"

    def __init__(self) -> None:
        self.vt_symbols: list[str] = []
        self.start: datetime = None
        self.end: datetime = None

        self.interval: Interval = Interval.MINUTE
        self.period_per_year = timedelta(days=365) / INTERVAL_DELTA_MAP[self.interval]

        self.factor_name: str = ""

        self.commission_rate: float = 0
        self.slippage: float = 0
        self.size: int = 1
        self.price_tick: float = 0
        self.dts: set[datetime] = set()

        self.logs: list = []

        self.database: BaseDatabase = get_database()
        self.factor: FactoeTemplate = None

        self.bar_data = None
        self.factor_data = None

    def clear_data(self) -> None:
        """清空数据"""
        self.logs = []
        self.clear_bar()
        self.clear_factor()

    def clear_bar(self) -> None:
        self.bar_data = None

    def clear_factor(self) -> None:
        self.factor_data=None

    def set_parameters(
            self,
            vt_symbols: list[str],
            start: datetime,
            end: datetime,
            interval: Interval,
            factor_name: str,
            commission_rate: float,
            slippage: float,
            size: int,
            price_tick: float
    ) -> None:
        """设置回测参数"""
        self.vt_symbols = vt_symbols
        self.start = start
        self.end = end
        self.interval = interval
        self.factor_name = factor_name
        self.commission_rate = commission_rate
        self.slippage = slippage
        self.size = size
        self.price_tick = price_tick

    def load_data(self) -> None:
        """加载数据"""
        self.clear_data()
        self.load_bars()
        self.load_factor()
        # align bar data and factor data
        self.bar_data, self.factor_data = pl.align_frames(
            self.bar_data, self.factor_data, on="datetime", how="inner"
        )

    def load_bars(self):
        """加载K线数据"""
        self.output("开始加载历史数据")

        if not self.end:
            self.end = datetime.now()

        if self.start >= self.end:
            self.output(f"起始日期必须小于结束日期")
            return

        # 清理上次加载的历史数据
        bar_dict = {}
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
                        bar_dict[(bar.datetime, vt_symbol)] = (
                                                                                  bar.open_price + bar.high_price + bar.low_price + bar.close_price) / 4
                        data_count += 1

                    progress += progress_delta / total_delta
                    progress = min(progress, 1)
                    self.output(
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
                    bar_dict[(bar.datetime, vt_symbol)] = (
                                                                              bar.open_price + bar.high_price + bar.low_price + bar.close_price) / 4

                data_count = len(data)

            self.output("{}历史数据加载完成，数据量：{}".format(vt_symbol, data_count))

        self.bar_data: pl.DataFrame = convert_dict_to_dataframe(data=bar_dict, is_polars=True)

        self.output("所有历史数据加载完成")

    def load_factor(self):

        self.output("开始加载因子数据")
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

        self.output("因子数据加载完成")

    def calculate_factor(self, setting) -> pl.DataFrame:
        factor_data = self.factor.make_factor(setting)
        return factor_data

    def run_backtesting_groups(self, n_groups: int, if_plot: bool = False):
        """运行回测"""
        self.output("开始回测")
        datetimes = self.bar_data['datetime'].to_numpy()

        # Convert to numpy arrays
        close_prices_np = self.bar_data.drop('datetime').to_numpy()
        factor_values_np = self.factor_data.drop('datetime').to_numpy()

        num_dates = len(datetimes)

        # Initialize portfolio values and daily returns
        portfolio_values = np.ones((n_groups, num_dates))
        daily_returns = np.zeros((n_groups, num_dates))

        # Initialize IC series
        ic_series = []

        # Iterate over each day
        for i in range(1, num_dates):
            current_factor = factor_values_np[i - 1]
            future_returns = (close_prices_np[i] / close_prices_np[i - 1]) - 1

            # Handle missing data
            valid = (~np.isnan(current_factor) &
                     ~np.isnan(future_returns))
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
            sharpe_ratio = (np.mean(daily_returns[j]) / np.std(daily_returns[j])) * np.sqrt(self.period_per_year)
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
            self.plot_portfolio_performance(portfolio_values, datetimes, n_groups)
            # plot_ic_series(ic_series, datetimes)

        return portfolio_values, performance_metrics, ic_series, ir

    def run_backtesting_positions(self, if_plot: bool = False):
        """
            Backtest a strategy where factor values represent positions in tickers,
            normalized so that the sum of absolute positions equals 1.

            Parameters:
                bar_data (pl.DataFrame): Close prices indexed by datetime, columns as tickers.
                factor_data (pl.DataFrame): Factor values indexed by datetime, columns as tickers.
                commission_rate (float): Commission rate per trade.
                slippage_rate (float): Slippage rate per trade.

            Returns:
                portfolio_values (np.ndarray): Portfolio value over time.
                performance_metrics (dict): Performance metrics of the portfolio.
            """
        datetimes = self.bar_data['datetime'].to_numpy()
        tickers = self.bar_data.columns[1:]

        # Convert to numpy arrays
        close_prices_np = self.bar_data.drop('datetime').to_numpy()
        factor_values_np = self.factor_data.drop('datetime').to_numpy()

        num_dates = len(datetimes)
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
            factor_values = factor_values[valid]
            current_close = current_close[valid]
            previous_close = previous_close[valid]

            # Normalize factor values to get positions
            abs_sum = np.sum(np.abs(factor_values))
            if abs_sum == 0:
                normalized_positions = np.zeros_like(factor_values)
            else:
                normalized_positions = factor_values / abs_sum

            # Store positions (for valid tickers only)
            positions_i = np.zeros(num_tickers)
            positions_i[valid] = normalized_positions
            positions[i] = positions_i

            # Calculate portfolio turnover (sum of absolute changes in positions)
            if i == 1:
                turnover[i] = np.sum(np.abs(positions[i] - 0))  # From zero initial positions
            else:
                turnover[i] = np.sum(np.abs(positions[i] - positions[i - 1]))

            # Calculate gross returns
            returns = (current_close - previous_close) / previous_close

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
        sharpe_ratio = annualized_return / annualized_volatility if annualized_volatility != 0 else np.nan

        performance_metrics = {
            'Total Return': total_return,
            'Annualized Return': annualized_return,
            'Annualized Volatility': annualized_volatility,
            'Sharpe Ratio': sharpe_ratio
        }

        if if_plot:
            # Plot portfolio performance
            self.plot_portfolio_performance_position(portfolio_values, datetimes)

        return portfolio_values, performance_metrics

    def output(self, msg) -> None:
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


