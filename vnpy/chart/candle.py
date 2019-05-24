from typing import Sequence

from vnpy.trader.object import BarData


class CandleChart:
    """"""

    def __init__(self):
        """"""
        pass

    def update_bar(self, bar: BarData):
        """
        Update one bar data into the chart.

        The bar data may be a new one or an existing one.
        """
        pass

    def update_bars(self, bars: Sequence[BarData]):
        """
        Update a list of bar data into the chart.
        """
        pass

    def clear(self):
        """
        Clear all data displayed in the chart.
        """
        pass

    def set_volume_visible(self, visible: bool):
        """
        Set if the volume data visible on the chart.
        """
        pass

    def set_cursor_visible(self, visible: bool):
        """
        Set if the cross cursor visible on the chart.
        """
        pass

    def to_left_end(self):
        """
        Scroll chart to the left end.
        """
        pass

    def to_right_end(self):
        """
        Scroll chart to the right end.
        """
        pass
