import itertools
from typing import Dict, List, Any

import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

from vnpy.app.factor_maker.template import FactorTemplate


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

class FactorOptimizer:
    """
    A class to optimize factor parameters using backtesting.
    """

    def __init__(self, backtester_class, data: Dict[str, pd.DataFrame]):
        """
        Initialize the optimizer.

        Parameters:
            backtester_class: The backtester class to use for evaluation.
            data: Historical data dictionary with keys ('open', 'high', 'low', 'close', 'volume').
        """
        self.backtester_class = backtester_class
        self.data = data

    def optimize(
        self,
        param_grid: Dict[str, List[Any]],
        factor_class: type[FactorTemplate],
        metric: str = "Sharpe Ratio",
    ) -> Dict[str, Any]:
        """
        Optimize the factor parameters.

        Parameters:
            param_grid: Dictionary of parameter names and lists of possible values.
            factor_class: The factor class (inheriting from FactorTemplate) to optimize.
            metric: The metric to optimize. Default is "Sharpe Ratio".

        Returns:
            dict: Best parameters and corresponding performance metrics.
        """
        best_params = None
        best_score = -np.inf
        best_metrics = {}

        # Generate all combinations of parameter values
        param_combinations = list(itertools.product(*param_grid.values()))
        param_names = list(param_grid.keys())

        for param_values in param_combinations:
            # Create a parameter dictionary for this combination
            params = dict(zip(param_names, param_values))

            # Initialize factor with current parameters
            factor = factor_class(**params)

            # Calculate factor values (DataFrame: datetime x symbols)
            factor_values = factor.calculate(self.data["close"])

            # Run backtesting
            backtester = self.backtester_class(factor_values)
            metrics = backtester.run_backtesting(self.data, if_plot=False)

            # Evaluate the chosen metric
            score = metrics.get(metric, -np.inf)
            if score > best_score:
                best_score = score
                best_params = params
                best_metrics = metrics

        print(f"Best parameters: {best_params}")
        print(f"Best {metric}: {best_score}")
        return {"best_params": best_params, "best_metrics": best_metrics}


class MomentumFactor(FactorTemplate):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.add_params(["window"], auto_property=True)

    def calculate(self, input_data: pd.DataFrame, *args, **kwargs) -> pd.DataFrame:
        """
        Calculate the momentum factor value.

        Parameters:
            input_data (pd.DataFrame): Input price data with columns as symbols and index as datetime.

        Returns:
            pd.DataFrame: Factor values with datetime as row index and symbols as columns.
        """
        window = self.window
        return input_data.diff(window)


if __name__ == "__main__":
    # Load historical data
    def load_data() -> Dict[str, pd.DataFrame]:
        dates = pd.date_range(start="2020-01-01", end="2023-12-31", freq="B")
        symbols = ["AAPL", "MSFT", "GOOGL", "AMZN"]
        close_prices = pd.DataFrame(
            data=np.random.uniform(100, 200, size=(len(dates), len(symbols))),
            index=dates,
            columns=symbols,
        )
        return {"close": close_prices}

    data = load_data()

    # Define parameter grid
    param_grid = {
        "window": [5, 10, 20],
    }

    # Initialize optimizer
    optimizer = FactorOptimizer(FactorBacktesting, data)
    results = optimizer.optimize(param_grid, MomentumFactor)

    print("Optimization Results:")
    print(results)