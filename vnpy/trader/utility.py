"""
General utility functions.
"""

from pathlib import Path

from .constant import (STATUS_NOTTRADED, STATUS_PARTTRADED, STATUS_SUBMITTING)


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
            cls._instances[cls] = super(VtSingleton,
                                        cls).__call__(*args,
                                                      **kwargs)

        return cls._instances[cls]


def get_temp_path(filename: str):
    """
    Get path for temp file with filename.
    """
    home_path = Path.home()
    temp_path = home_path.joinpath('.vntrader')

    if not temp_path.exists():
        temp_path.mkdir()

    return temp_path.joinpath(filename)


ACTIVE_STATUSES = set([STATUS_SUBMITTING, STATUS_NOTTRADED, STATUS_PARTTRADED])


def check_order_active(status: str):
    """
    Check if order is active by status.
    """
    if status in ACTIVE_STATUSES:
        return True
    else:
        return False
