"""
Check code quality for vn.py project.
"""

import logging
import os
import subprocess
from typing import Callable

logger = logging.Logger(__file__)


def check_and_warning(*args: list, fast_fail: bool = False):
    """
    Run check and show related warning
    """
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


def check_flake8():
    """
    Check code with flake8.
    """
    passed = True
    try:
        subprocess.check_call(["flake8", "./"])
    except subprocess.SubprocessError:
        passed = False
    return passed


def check_all():
    """
    Run check with all tools (only flake8 for now).
    """
    return check_and_warning(check_flake8)


if __name__ == "__main__":
    if not check_all():
        exit(1)
    exit(0)
