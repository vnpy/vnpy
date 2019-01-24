import logging
import subprocess

from tools.check.utils import check_and_warning

logger = logging.Logger(__file__)


def check_flake8():
    passed = True
    try:
        subprocess.check_call(["flake8", "./"])
    except subprocess.SubprocessError:
        passed = False
    return passed


def check_pylint():
    passed = True
    try:
        subprocess.check_call(["pylint", "-j", "0", "vnpy", "binding", "tests"])
    except subprocess.SubprocessError:
        passed = False
    return passed


def check_linter():
    return check_and_warning(check_pylint, check_flake8)


if __name__ == "__main__":
    if not check_linter():
        exit(1)
    exit(0)
