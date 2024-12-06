import itertools
from typing import Dict, List, Any

import dask
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.backtesting import FactorBacktesting


class FactorOptimizer:
    """
    A class to optimize factor parameters using backtesting.
    """

    def __init__(self, backtester: FactorBacktesting, data: Dict[str, pd.DataFrame]):
        """
        Initialize the optimizer.

        Parameters:
            backtester: The backtester class to use for evaluation.
            data: Historical data dictionary with keys ('open', 'high', 'low', 'close', 'volume').
        """
        self.dependency_factor = None
        self.factor = None

        self.backtester = backtester
        self.backtester.data = data
        self.data = data

    def add_factor(self, factor: type[FactorTemplate]):
        self.factor = factor
        self.dependency_factor = {f.factor_key: f for f in factor.dependencies_factor}

        self.build_computational_graph()

        self.prepare_data()

    def build_computational_graph(self):
        def complete_factor_tree():
            for f in self.dependency_factor:
                for dep_f in f.dependencies_factor:
                    if dep_f.factor_key in self.dependency_factor:
                        continue
                    self.dependency_factor[dep_f.factor_key] = dep_f

        complete_factor_tree()

        self.tasks = {}

        # Function to create a task for a factor
        def create_task(factor_key: str) -> dask.delayed:
            """
            Create a Dask task for a given factor dynamically.

            Parameters:
                factor_key (str): The name of the factor to create the task for.

            Returns:
                dask.delayed: The Dask task for the factor calculation.
            """
            # Check if the task has already been created
            if factor_key in self.tasks:
                return self.tasks[factor_key]

            # Retrieve the factor instance
            factor = self.dependency_factor[factor_key]

            # Resolve dependencies recursively
            dep_tasks = {}
            if not factor.dependencies_factor:
                # Create memory dict with delayed tasks for each key
                memory_dict = {key: dask.delayed(lambda df=df: df.copy())() for key, df in self.data.items()}
                # Pass the memory_dict as input to factor.calculate
                self.tasks[factor_key] = dask.delayed(factor.calculate)(**memory_dict)
            else:
                # Resolve dependencies recursively
                for f in factor.dependencies_factor:
                    dep = f.factor_key
                    dep_tasks[dep] = create_task(dep)

                # Create the task for the current factor using memory and resolved dependencies
                self.tasks[factor_key] = dask.delayed(factor.calculate)(**dep_tasks)

            return self.tasks[factor_key]

        # Build tasks for all factors
        for factor_key in self.dependency_factor.keys():
            create_task(factor_key)

    def prepare_data(self):
        """
        Compute the results of the Dask DAGs and extract the outputs into a structured format.
        """
        if not hasattr(self, "tasks"):
            raise ValueError("Computation graph has not been built. Please run build_computational_graph first.")

        # Execute the Dask computation graph
        computed_results = dask.compute(*self.tasks.values())

        # Map computed results back to their corresponding factors
        self.factor_data = {
            factor_key: result for factor_key, result in zip(self.tasks.keys(), computed_results)
        }

        return self.factor_data

    def optimize(self, param_grid: Dict[str, List[Any]], metric: str = "Sharpe Ratio") -> Dict[str, Any]:
        """
        Optimize the params of the factor using grid search and Dask.

        Parameters:
            param_grid (Dict[str, List[Any]]): Dictionary of parameter names and their grid values.
            metric (str): The performance metric to optimize. Default is "Sharpe Ratio".

        Returns:
            Dict[str, Any]: Best params and their corresponding performance metrics.
        """

        # Generate all combinations of params
        param_combinations = list(itertools.product(*param_grid.values()))
        param_names = list(param_grid.keys())

        # Define evaluate_params outside the loop
        @dask.delayed
        def evaluate_params(params):
            # Set params for the factor
            self.factor.set_params(params)

            # Calculate factor values
            factor_values = self.factor.calculate(self.factor_data)

            # Run backtesting
            metrics = self.backtester.run_backtesting(factor_values, if_plot=False)

            # Return the chosen metric and params
            return metrics.get(metric, -float("inf")), params

        # Create tasks for all parameter combinations
        tasks = [evaluate_params(dict(zip(param_names, param_values))) for param_values in param_combinations]

        # Compute all tasks
        results = dask.compute(*tasks)

        # Find the best parameter set
        best_score = -float("inf")
        best_params = None
        for score, params in results:
            if score > best_score:
                best_score = score
                best_params = params

        return {"best_params": best_params, "best_score": best_score}


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
