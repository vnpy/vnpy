from typing import List

import pyqtgraph as pg

from .manager import BarManager
from .base import AXIS_WIDTH, NORMAL_FONT


class DatetimeAxis(pg.AxisItem):
    """"""

    def __init__(self, manager: BarManager, *args, **kwargs):
        """"""
        super().__init__(*args, **kwargs)

        self._manager: BarManager = manager

        self.setPen(width=AXIS_WIDTH)
        self.tickFont = NORMAL_FONT

    def tickStrings(self, values: List[int], scale: float, spacing: int):
        """
        Convert original index to datetime string.
        """
        # Show no axis string if spacing smaller than 1
        if spacing < 1:
            return ["" for i in values]

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
