import json

from vnpy.trader.utility import load_json, save_json
import factors

from typing import Dict, Any
import dask


def get_factor_class(class_name: str) -> None:
    """Load a factor class from a specified module."""
    return getattr(factors, class_name)


def save_factor_setting(self) -> None:
    """������������"""
    factor_setting: dict = {}
    for name, factor in self.factors.items():
        factor_setting[name] = factor.to_dict()
    save_json(self.setting_filename, factor_setting)


# mycode
def load_factor_setting(setting_path: str):
    """load_factor_setting from a json file, which is usually saved in `.vntrader/factor_maker_setting.json`

    Parameters
    ----------
    setting_path :

    Returns
    -------

    """
    with open(setting_path, 'r') as fr:
        js = json.load(fr)
    return js


def init_factors(f_setting: Dict):
    """initiate factors from the factor setting with a for loop, but the factor will init dependency factors recursively

    Parameters
    ----------
    f_setting : Dict
        factor settings saved in json file

    Returns
    -------

    """
    factors_list = []
    for module_name, module_setting in f_setting.items():
        f_class = getattr(factors, module_setting["class_name"])
        f_class = f_class({module_name: module_setting}, **module_setting["params"])  # recursion
        factors_list.append(f_class)
    return factors_list


def build_computational_graph(factors: Dict[str, Any], data: Dict[str, Any]) -> Dict[str, dask.delayed]:
    """
    Build a Dask computational graph for factors with dependencies.

    Parameters:
        factors (Dict[str, Any]): Dictionary of factors keyed by their unique `factor_key`.
                                  Each value is a factor instance with a `calculate` method and `dependencies_factor`.
        data (Dict[str, pl.DataFrame]): Historical OHLCV or other input data as Polars DataFrames.

    Returns:
        Dict[str, dask.delayed]: Dask tasks for each factor keyed by `factor_key`.
    """

    tasks = {}

    def complete_factor_tree(dependency_factor: Dict[str, Any]) -> Dict[str, Any]:
        """
        Expand the dependency tree to include all dependent factors recursively.

        Parameters:
            dependency_factor (Dict[str, Any]): A dictionary of factors keyed by factor_key.

        Returns:
            Dict[str, Any]: Updated dependency factor dictionary including all recursive dependencies.
        """
        updated_dependency_factor = dependency_factor.copy()
        for f_key, f in dependency_factor.items():
            for dep_f in f.dependencies_factor:
                if dep_f.factor_key not in updated_dependency_factor:
                    updated_dependency_factor[dep_f.factor_key] = dep_f
        return updated_dependency_factor

    def create_task(factor_key: str, dependency_factor: Dict[str, Any]) -> dask.delayed:
        """
        Recursively create a Dask task for a given factor and its dependencies.

        Parameters:
            factor_key (str): The key of the factor to create a task for.
            dependency_factor (Dict[str, Any]): Dictionary of factors keyed by their unique `factor_key`.

        Returns:
            dask.delayed: The Dask task for the factor calculation.
        """
        # Check if the task already exists
        if factor_key in tasks:
            return tasks[factor_key]

        # Retrieve the factor instance
        factor = dependency_factor[factor_key]

        # Handle dependencies recursively
        dep_tasks = {}
        if not factor.dependencies_factor:
            # No dependencies: use the input data directly
            memory_dict = {key: dask.delayed(lambda df=df: df.clone())() for key, df in data.items()}
            tasks[factor_key] = dask.delayed(factor.calculate)(input_data=memory_dict)
        else:
            # Resolve dependencies recursively
            for dep_f in factor.dependencies_factor:
                dep_key = dep_f.factor_key
                dep_tasks[dep_key] = create_task(dep_key, dependency_factor)

            # Create the task for the current factor
            tasks[factor_key] = dask.delayed(factor.calculate)(input_data=dep_tasks)

        return tasks[factor_key]

    # Step 1: Complete the factor tree
    dependency_factor = complete_factor_tree(factors)

    # Step 2: Build tasks for all factors
    for factor_key in dependency_factor.keys():
        create_task(factor_key, dependency_factor)

    return tasks


if __name__ == '__main__':
    setting = load_factor_setting(
        '/Users/hongyifan/Desktop/work/crypto/20240720/examples/no_ui/.vntrader/factor_maker_setting.json')
    factors_list = init_factors(setting)
    print(factors_list)
