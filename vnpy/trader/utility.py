"""
General utility functions.
"""

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
            cls._instances[cls] = super(VtSingleton, cls).__call__(*args, **kwargs)
            
        return cls._instances[cls]


def get_temp_path(filename):
    """
    Get path for temp file with filename.
    """
    home_path = Path.home()
    temp_path = home_path.joinpath('.vntrader')

    if not temp_path.exists():
        temp_path.mkdir()
        
    return temp_path.joinpath(filename)