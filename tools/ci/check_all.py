"""
check code quality for project
run this file under project root
"""

import logging
import os
import subprocess

from typing import Callable

logger = logging.Logger(__file__)


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


def check_black():
    passed = True
    try:
        subprocess.check_call(["python", "-m", "black", "--check", "./"])
    except subprocess.SubprocessError:
        passed = False
    return passed


def check_format():
    return check_and_warning(check_black)


def check_all():
    return check_and_warning(check_format, check_linter)


def check_flake8():
    passed = True
    try:
        subprocess.check_call(["python", "-m", "flake8", "./"])
    except subprocess.SubprocessError:
        passed = False
    return passed


def check_pylint():
    passed = True
    try:
        subprocess.check_call(
            ["python", "-m", "pylint", "-j", "0", "vnpy", "binding", "tests"]
        )
    except subprocess.SubprocessError:
        passed = False
    return passed


def check_linter():
    return check_and_warning(check_pylint, check_flake8)


if __name__ == "__main__":
    if not check_all():
        exit(1)
    exit(0)