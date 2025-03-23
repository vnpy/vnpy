from typing import Dict
from typing import Tuple, Union

import vnpy.app.factor_maker.factors as factors
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.utility import load_json, save_json


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
    js = load_json(setting_path)
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