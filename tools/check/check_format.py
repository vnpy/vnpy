import logging
import os
import subprocess

from tools.check.utils import check_and_warning

logger = logging.Logger(__file__)


def check_by_yapf():
    from yapf.yapflib.yapf_api import FormatFile

    passed = True
    for root, dir, filenames in os.walk("vnpy"):
        for filename in filenames:
            basename, ext = os.path.splitext(filename)
            if ext == ".py":
                path = os.path.join(root, filename)
                reformatted_code, encoding, changed = FormatFile(
                    filename=path,
                    style_config=".style.yapf",
                    print_diff=True,
                    verify=False,
                    in_place=False,
                    logger=None,
                )
                if changed:
                    passed = False
                    logger.warning("File {} not formatted!".format(path))
                else:
                    logger.info("File {} is formatted!".format(path))
    return passed


def check_black():
    passed = True
    try:
        subprocess.check_call(["black", "--check", "./"])
    except subprocess.SubprocessError:
        passed = False
    return passed


def check_format():
    return check_and_warning(check_black)


if __name__ == "__main__":
    if not check_format():
        exit(1)
    exit(0)
