import logging
import subprocess


logger = logging.Logger(__file__)


def format_black():
    subprocess.check_call(["python", "-m", "black", "."])


if __name__ == "__main__":
    if not format_black():
        exit(1)
    exit(0)
