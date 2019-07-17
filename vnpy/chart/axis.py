from typing import List

import pyqtgraph as pg

from vnpy.trader.ui import QtGui

from .manager import BarManager


AXIS_WIDTH = 0.8
AXIS_FONT = QtGui.QFont("Arial", 10, QtGui.QFont.Bold)


class DatetimeAxis(pg.AxisItem):
    """"""

    def __init__(self, manager: BarManager, *args, **kwargs):
        """"""
        super().__init__(*args, **kwargs)

        self._manager: BarManager = manager

        self.setPen(width=AXIS_WIDTH)
        self.setStyle(tickFont=AXIS_FONT, autoExpandTextSpace=True)

    def tickStrings(self, values: List[int], scale: float, spacing: int):
        """
        Convert original index to datetime string.
        """
        strings = []

        for ix in values:
            dt = self._manager.get_datetime(ix)

            if not dt:
                s = ""
            elif dt.hour:
                s = dt.strftime("%Y-%m-%d\n%H:%M:%S")
            else:
                s = dt.strftime("%Y-%m-%d")

            strings.append(s)

        return strings
