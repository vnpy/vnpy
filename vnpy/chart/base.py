"""
Shared colors, fonts, and helpers for charts.
"""

from vnpy.trader.ui import QtGui


WHITE_COLOR: tuple[int, int, int] = (255, 255, 255)
BLACK_COLOR: tuple[int, int, int] = (0, 0, 0)
GREY_COLOR: tuple[int, int, int] = (100, 100, 100)

UP_COLOR: tuple[int, int, int] = (255, 75, 75)
DOWN_COLOR: tuple[int, int, int] = (0, 255, 255)
CURSOR_COLOR: tuple[int, int, int] = (255, 245, 162)

PEN_WIDTH: int = 1
BAR_WIDTH: float = 0.3

AXIS_WIDTH: float = 0.8
NORMAL_FONT: QtGui.QFont = QtGui.QFont("Arial", 9)


def to_int(value: float) -> int:
    """
    Round a value to the nearest integer.
    """
    return int(round(value, 0))
