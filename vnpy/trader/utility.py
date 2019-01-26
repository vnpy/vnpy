"""
General utility functions.
"""

import shelve
from pathlib import Path


class Singleton(type):
    """
    Singleton metaclass, 
    
    class A:
        __metaclass__ = Singleton
        
    """

    _instances = {}

    def __call__(cls, *args, **kwargs):
        """"""
        if cls not in cls._instances:
            cls._instances[cls] = super(Singleton, cls).__call__(*args, **kwargs)

        return cls._instances[cls]


def get_trader_path():
    """
    Get path where trader is running in.
    """
    home_path = Path.home()
    return home_path


def get_temp_path(filename: str):
    """
    Get path for temp file with filename.
    """
    trader_path = get_trader_path()
    temp_path = trader_path.joinpath(".vntrader")

    if not temp_path.exists():
        temp_path.mkdir()

    return temp_path.joinpath(filename)


def get_icon_path(filepath: str, ico_name: str):
    """
    Get path for icon file with ico name.
    """
    ui_path = Path(filepath).parent
    icon_path = ui_path.joinpath("ico", ico_name)
    return str(icon_path)


def load_setting(filename: str):
    """
    Load setting from shelve file in temp path.
    """
    filepath = get_temp_path(filename)
    f = shelve.open(str(filepath))
    setting = dict(f)
    f.close()
    return setting


def save_setting(filename: str, setting: dict):
    """
    Save setting into shelve file in temp path.
    """
    filepath = get_temp_path(filename)
    f = shelve.open(str(filepath))
    for k, v in setting.items():
        f[k] = v
    f.close()


def round_to_pricetick(price: float, pricetick: float):
    """
    Round price to price tick value.
    """
    rounded = round(price / pricetick, 0) * pricetick
    return rounded
