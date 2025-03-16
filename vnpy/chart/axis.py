from datetime import datetime

import pyqtgraph as pg

from .manager import BarManager
from .base import AXIS_WIDTH, NORMAL_FONT, QtGui


class DatetimeAxis(pg.AxisItem):
    """"""

    def __init__(self, manager: BarManager, *args, **kwargs) -> None:
        """"""
        super().__init__(*args, **kwargs)

        self._manager: BarManager = manager

        self.setPen(width=AXIS_WIDTH)
        self.tickFont: QtGui.QFont = NORMAL_FONT

    def tickStrings(self, values: list[int], scale: float, spacing: int) -> list:
        """
        Convert original index to datetime string.
        """
        # Show no axis string if spacing smaller than 1
        if spacing < 1:
            return ["" for i in values]

        strings: list = []

        for ix in values:
            dt: datetime = self._manager.get_datetime(ix)

            if not dt:
                s: str = ""
            elif dt.hour:
                s: str = dt.strftime("%Y-%m-%d\n%H:%M:%S")
            else:
                s: str = dt.strftime("%Y-%m-%d")

            strings.append(s)

        return strings
