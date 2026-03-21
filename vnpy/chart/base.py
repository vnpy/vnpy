import os
import platform

from vnpy.trader.ui import QtGui


WHITE_COLOR = (255, 255, 255)
BLACK_COLOR = (0, 0, 0)
GREY_COLOR = (100, 100, 100)

UP_COLOR = (255, 75, 75)
DOWN_COLOR = (0, 255, 255)
CURSOR_COLOR = (255, 245, 162)

PEN_WIDTH = 1
BAR_WIDTH = 0.3

AXIS_WIDTH = 0.8
NORMAL_FONT = QtGui.QFont("微软雅黑", 9)


def _flag_enabled(name: str, default: bool) -> bool:
    value = os.environ.get(name)
    if value is None:
        return default
    return value not in {"0", "false", "False"}


# Safe rendering mode for macOS to mitigate occasional Qt text drawing crashes.
SAFE_CHART_RENDER = _flag_enabled(
    "VNPY_SAFE_CHART_RENDER",
    platform.system() == "Darwin"
)


def to_int(value: float) -> int:
    """"""
    return int(round(value, 0))
