import itertools
from typing import Dict, List, Any, Type

import dask
import pandas as pd
import polars as pl

from vnpy.app.factor_maker.backtesting import FactorBacktester
from vnpy.app.factor_maker.template import FactorTemplate, FactorMode


class FactorOptimizer:
    """
    A class to optimize factor parameters using backtesting.
    """

    def __init__(self, backtester: FactorBacktester, memory_bar: Dict[str, pd.DataFrame]):
        """
        Initialize the optimizer.

        Parameters:
            backtester: The backtester class to use for evaluation.
            memory_bar: Historical data dictionary with keys ('open', 'high', 'low', 'close', 'volume').
        """
        self.memory_bar = memory_bar
        self.memory_factor = {}
        self.backtester = backtester
        self.factor = None
        self.tasks = {}

    def add_factor(self, factor: Type[FactorTemplate]):
        """
        Add a factor to the optimizer and build its computational graph.

        Parameters:
            factor: The factor to add (inherits from FactorTemplate).
        """
        self.factor = factor
        self.factor.factor_mode = FactorMode.Backtest

        # Collect dependencies and build the computational graph
        dependency_factors = {f.factor_key: f for f in factor.dependencies_factor}
        self.tasks = build_computational_graph(dependency_factors, self.memory_bar)

        # Prepare memory for the factor calculations
        self.prepare_memory_factor()

    def prepare_memory_factor(self):
        """
        Execute the Dask DAGs and extract outputs into memory_factor.
        """
        if not self.tasks:
            raise ValueError("Computation graph has not been built. Please add a factor first.")

        # Compute the Dask computation graph
        computed_results = dask.compute(*self.tasks.values())

        # Map computed results to corresponding factor keys
        self.memory_factor = {
            factor_key: result for factor_key, result in zip(self.tasks.keys(), computed_results)
        }

    def optimize(self, param_grid: Dict[str, List[Any]]) -> Dict[str, Any]:
        """
        Optimize the factor parameters using grid search and Dask.

        Parameters:
            param_grid (Dict[str, List[Any]]): Dictionary of parameter names and their grid values.
            metric (str): The performance metric to optimize (default is "Sharpe Ratio").

        Returns:
            Dict[str, Any]: Best parameters and their corresponding performance metrics.
        """
        param_combinations = list(itertools.product(*param_grid.values()))
        param_names = list(param_grid.keys())

        @dask.delayed
        def evaluate_params(params: Dict[str, Any]):
            """
            Evaluate the performance of the factor for a given set of parameters.
            """
            self.factor.set_params(params)
            factor_values = self.factor.calculate(self.memory_factor)
            sr = self.backtester.run_backtesting(factor_values, if_report=False)
            return sr, params

        # Create evaluation tasks for all parameter combinations
        tasks = [evaluate_params(dict(zip(param_names, param_values))) for param_values in param_combinations]

        # Compute all tasks and find the best parameter set
        results = dask.compute(*tasks)
        best_score, best_params = max(results, key=lambda x: x[0])

        # Update the factor with the best parameters
        self.factor.set_params(best_params)

        return {"best_params": best_params, "best_score": best_score}


def complete_factor_tree(factors: Dict[str, Type[FactorTemplate]]) -> Dict[str, Type[FactorTemplate]]:
    """
    Recursively complete the dependency tree for all factors.

    Parameters:
        factors (Dict[str, Type[FactorTemplate]]): Dictionary of factors keyed by their factor keys.

    Returns:
        Dict[str, Type[FactorTemplate]]: Complete dependency tree including all dependent factors.
    """
    def traverse_dependencies(factor: Type[FactorTemplate], resolved: Dict[str, Type[FactorTemplate]]):
        if factor.factor_key in resolved:
            return
        resolved[factor.factor_key] = factor
        for dependency in factor.dependencies_factor:
            traverse_dependencies(dependency, resolved)

    resolved_factors = {}
    for factor_key, factor in factors.items():
        traverse_dependencies(factor, resolved_factors)

    return resolved_factors


def create_task(
    factor_key: str,
    factors: Dict[str, Type[FactorTemplate]],
    memory_bar: Dict[str, Any],
    tasks: Dict[str, dask.delayed]
) -> dask.delayed:
    """
    Recursively create a Dask task for a given factor and its dependencies.

    Parameters:
        factor_key (str): The key of the factor to create a task for.
        factors (Dict[str, Type[FactorTemplate]]): Dictionary of all factors keyed by their factor_key.
        memory_bar (Dict[str, pl.DataFrame]): Historical OHLCV or other input data.
        tasks (Dict[str, dask.delayed]): Dictionary to store created tasks.

    Returns:
        dask.delayed: The Dask task for the factor calculation.
    """
    if factor_key in tasks:
        return tasks[factor_key]

    factor = factors[factor_key]

    if not factor.dependencies_factor:  # No dependencies
        memory_dict = {key: dask.delayed(lambda df=df: df.clone())() for key, df in memory_bar.items()}
        tasks[factor_key] = dask.delayed(factor.calculate)(input_data=memory_dict)
    else:  # Resolve dependencies recursively
        dep_tasks = {
            dep_factor.factor_key: create_task(dep_factor.factor_key, factors, memory_bar, tasks)
            for dep_factor in factor.dependencies_factor
        }
        tasks[factor_key] = dask.delayed(factor.calculate)(input_data=dep_tasks)

    return tasks[factor_key]


def build_computational_graph(factors: Dict[str, Type[FactorTemplate]], memory_bar: Dict[str, pl.DataFrame]) -> Dict[str, dask.delayed]:
    """
    Build a Dask computational graph for factors with dependencies.

    Parameters:
        factors (Dict[str, Type[FactorTemplate]]): Dictionary of factors keyed by their unique `factor_key`.
        memory_bar (Dict[str, pl.DataFrame]): Historical OHLCV or other input data.

    Returns:
        Dict[str, dask.delayed]: Dask tasks for each factor keyed by `factor_key`.
    """
    full_factor_tree = complete_factor_tree(factors)
    tasks = {}
    for factor_key in full_factor_tree.keys():
        create_task(factor_key, full_factor_tree, memory_bar, tasks)
    return tasks