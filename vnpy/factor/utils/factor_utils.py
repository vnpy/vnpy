# Utility functions for factor management

from typing import Dict
from vnpy.trader.utility import load_json, save_json
import vnpy.app.factor_maker.factors as factors

def get_factor_class(class_name: str):
    """
    Load a factor class from a specified module.

    Parameters:
        class_name (str): Name of the class to load.

    Returns:
        The factor class object.
    """
    return getattr(factors, class_name)

def save_factor_setting(factors: Dict, setting_filename: str) -> None:
    """
    Save factor settings to a JSON file.

    Parameters:
        factors (Dict): Dictionary of factors.
        setting_filename (str): Path to the JSON file.
    """
    factor_setting = {name: factor.to_dict() for name, factor in factors.items()}
    save_json(setting_filename, factor_setting)

def load_factor_setting(setting_path: str):
    """
    Load factor settings from a JSON file.

    Parameters:
        setting_path (str): Path to the JSON file.

    Returns:
        dict: Loaded factor settings.
    """
    return load_json(setting_path)

def init_factors(f_setting: Dict):
    """
    Initialize factors from the factor settings.

    Parameters:
        f_setting (Dict): Factor settings saved in a JSON file.

    Returns:
        list: List of initialized factors.
    """
    factors_list = []
    for module_name, module_setting in f_setting.items():
        f_class = getattr(factors, module_setting["class_name"])
        f_class = f_class(module_setting, **module_setting["params"])
        factors_list.append(f_class)
    return factors_list