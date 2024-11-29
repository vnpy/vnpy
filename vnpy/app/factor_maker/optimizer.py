import itertools
from typing import Dict, List, Any

import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.backtesting import FactorBacktesting


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
