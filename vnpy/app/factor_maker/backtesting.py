# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/vnpy/app/factor_maker
# @File     : backtesting.py
# @Time     : 2024/11/29 21:57
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
import itertools
from typing import Dict, List, Any

import numpy as np
import pandas as pd
from matplotlib import pyplot as plt


class FactorBacktesting:
    """
    A backtesting engine for evaluating factors with DataFrame-based factor values.
    """

    def __init__(self, factor_values: pd.DataFrame, commission_rate: float = 0.001, slippage: float = 0.001):
        """
        Initialize the backtesting engine.

        Parameters:
            factor_values (pd.DataFrame): Factor values with datetime as row index and symbols as columns.
            commission_rate (float): Commission rate per trade.
            slippage (float): Slippage per trade.
        """
        self.factor_values = factor_values
        self.commission_rate = commission_rate
        self.slippage = slippage
        self.portfolio_values = None
        self.performance_metrics = None

    def run_backtesting(self, data: Dict[str, pd.DataFrame], if_plot: bool = True) -> Dict[str, float]:
        """
        Run the backtesting process.

        Parameters:
            data (dict): Historical data dictionary with keys ('open', 'high', 'low', 'close', 'volume').
            if_plot (bool): Whether to plot the portfolio performance.

        Returns:
            dict: Performance metrics including Sharpe ratio, cumulative return, etc.
        """
        # Extract close prices
        close_prices = data["close"]

        # Calculate daily returns
        daily_returns = close_prices.pct_change()

        # Normalize factor values
        weights = self.factor_values.div(self.factor_values.abs().sum(axis=1), axis=0)

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
        annualized_return = portfolio_returns.mean() * 252
        annualized_volatility = portfolio_returns.std() * np.sqrt(252)
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
            self.plot_portfolio_performance(portfolio_values)

        return self.performance_metrics

    def plot_portfolio_performance(self, portfolio_values: pd.Series) -> None:
        """
        Plot portfolio performance.

        Parameters:
            portfolio_values (pd.Series): Portfolio values over time.
        """
        portfolio_values.plot(title="Portfolio Performance", ylabel="Portfolio Value", xlabel="Date", figsize=(12, 6))
        plt.grid()
        plt.show()
