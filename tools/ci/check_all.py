from tools.check.check_format import check_format
from tools.check.check_linter import check_linter
from tools.check.utils import check_and_warning


def check_all():
    return check_and_warning(check_format, check_linter)


if __name__ == "__main__":
    if not check_all():
        exit(1)
    exit(0)
