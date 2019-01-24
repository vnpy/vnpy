import logging
import subprocess


logger = logging.Logger(__file__)


def format_by_black():
    subprocess.check_call(["black", "vnpy"])


if __name__ == "__main__":
    if not format_by_black():
        exit(1)
    exit(0)
