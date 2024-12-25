import itertools
from typing import Dict, List, Any

import dask
import pandas as pd
import polars as pl

from vnpy.app.factor_maker.backtesting import FactorBacktester
from vnpy.app.factor_maker.template import FactorTemplate


class FactorOptimizer:
    """
    A class to optimize factor parameters using backtesting.
    """

    def __init__(self, backtester: FactorBacktester, data: Dict[str, pd.DataFrame]):
        """
        Initialize the optimizer.

        Parameters:
            backtester: The backtester class to use for evaluation.
            data: Historical data dictionary with keys ('open', 'high', 'low', 'close', 'volume').
        """
        self.dependency_factor = {}
        self.factor = None

        self.backtester = backtester
        self.data = data

    def add_factor(self, factor: type[FactorTemplate]):
        self.factor = factor
        dependency_factor = {f.factor_key: f for f in factor.dependencies_factor}

        self.tasks = build_computational_graph(dependency_factor, self.data)

        self.prepare_data()

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
            metrics = self.backtester.run_backtesting_pandas(factor_values, if_plot=False)

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

        self.factor.set_params(best_params)
        self.factor.to_dict()

        return {"best_params": best_params, "best_score": best_score}



def complete_factor_tree(factors: Dict[str, Any]) -> Dict[str, Any]:
    """
    Recursively complete the dependency tree for all factors.

    Parameters:
        factors (Dict[str, Any]): Dictionary of factors keyed by factor_key.

    Returns:
        Dict[str, Any]: Complete dependency tree including all dependent factors.
    """
    def traverse_dependencies(factor: Any, resolved_factors: Dict[str, Any]) -> None:
        """
        Recursively traverse and add dependencies of the given factor.

        Parameters:
            factor (Any): Current factor to traverse.
            resolved_factors (Dict[str, Any]): Dictionary to store all resolved dependencies.
        """
        if factor.factor_key in resolved_factors:
            return  # Skip if already resolved

        # Add the current factor
        resolved_factors[factor.factor_key] = factor

        # Traverse dependencies recursively
        for dependency in factor.dependencies_factor:
            traverse_dependencies(dependency, resolved_factors)

    resolved_factors = {}
    for factor_key, factor in factors.items():
        traverse_dependencies(factor, resolved_factors)

    return resolved_factors


def create_task(
    factor_key: str,
    factors: Dict[str, Any],
    data: Dict[str, Any],
    tasks: Dict[str, dask.delayed]
) -> dask.delayed:
    """
    Recursively create a Dask task for a given factor and its dependencies.

    Parameters:
        factor_key (str): The key of the factor to create a task for.
        factors (Dict[str, Any]): Dictionary of all factors keyed by factor_key.
        data (Dict[str, Any]): Historical OHLCV or other input data.
        tasks (Dict[str, dask.delayed]): Dictionary to store the created tasks.

    Returns:
        dask.delayed: The Dask task for the factor calculation.
    """
    if factor_key in tasks:
        return tasks[factor_key]  # Return cached task if already created

    factor = factors[factor_key]

    # Handle dependencies
    if not factor.dependencies_factor:  # No dependencies
        memory_dict = {key: dask.delayed(lambda df=df: df.clone())() for key, df in data.items()}
        tasks[factor_key] = dask.delayed(factor.calculate)(input_data=memory_dict)
    else:  # Resolve dependencies recursively
        dep_tasks = {
            dep_factor.factor_key: create_task(dep_factor.factor_key, factors, data, tasks)
            for dep_factor in factor.dependencies_factor
        }
        tasks[factor_key] = dask.delayed(factor.calculate)(input_data=dep_tasks)

    return tasks[factor_key]


def build_computational_graph(factors: Dict[str, Any], data: Dict[str, Any]) -> Dict[str, dask.delayed]:
    """
    Build a Dask computational graph for factors with dependencies.

    Parameters:
        factors (Dict[str, Any]): Dictionary of factors keyed by their unique `factor_key`.
        data (Dict[str, pl.DataFrame]): Historical OHLCV or other input data.

    Returns:
        Dict[str, dask.delayed]: Dask tasks for each factor keyed by `factor_key`.
    """
    # Step 1: Complete the dependency tree
    full_factor_tree = complete_factor_tree(factors)

    # Step 2: Create tasks for all factors
    tasks = {}
    for factor_key in full_factor_tree.keys():
        create_task(factor_key, full_factor_tree, data, tasks)

    return tasks


