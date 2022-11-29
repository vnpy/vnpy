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
NORMAL_FONT = QtGui.QFont("Arial", 9)


def to_int(value: float) -> int:
    """"""
    return int(round(value, 0))
