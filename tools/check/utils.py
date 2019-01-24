import logging
import os
from typing import Callable

logger = logging.getLogger(__file__)


def check_and_warning(*args, fast_fail: bool = False):
    passed = True
    for i in args:
        if isinstance(i, Callable):
            print(f"check using {i}")
            cwd = os.getcwd()
            res = i()
            os.chdir(cwd)
            if not res:
                passed = False
                logger.warning("check of %s failed!", i)
            if not passed and fast_fail:
                return False
    return passed
