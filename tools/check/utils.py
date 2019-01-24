import logging
from typing import Callable

logger = logging.getLogger(__file__)


def check_and_warning(*args, fast_fail: bool = False):
    passed = True
    for i in args:
        if isinstance(i, Callable):
            print(f"check using {i}")
            if not i():
                passed = False
                logger.warning("check of %s failed!", i)
            if not passed and fast_fail:
                return False
    return passed
