from typing import Sequence

from vnpy.chart.base import (
    AdvancedChartWidget,
    CandleChartDrawer,
    CandleDataSource,
    ChartWidget,
    HistogramDrawer,
    CandleAxisX, ValueAxisY)
from vnpy.chart.base.advanced_chart import SubChartWrapper
from vnpy.chart.base.data_source import HistogramDataSource
from vnpy.trader.object import BarData


class CandleChart(AdvancedChartWidget):
    """"""

    def __init__(self, parent=None):
        """"""
        super().__init__(parent)
        self.__init_ui()

    def __init_ui(self):

        # main chart: candle chart
        candle_ds = CandleDataSource()
        candle_drawer = CandleChartDrawer(candle_ds)
        candle_chart = ChartWidget(self)
        candle_chart.add_drawer(candle_drawer)
        candle_chart.add_axis(CandleAxisX(candle_ds), ValueAxisY())

        # volume chart: His
        volume_ds = HistogramDataSource()
        volume_drawer = HistogramDrawer(volume_ds)
        volume_chart = ChartWidget(self)
        volume_chart.add_drawer(volume_drawer)
        volume_chart.add_axis(CandleAxisX(candle_ds), ValueAxisY())

        candle_wrapper = self.add_chart(candle_chart, 4)
        volume_wrapper = self.add_chart(volume_chart, 1)

        # create cross hair
        ch1 = candle_wrapper.create_cross_hair()
        ch2 = volume_wrapper.create_cross_hair()

        # link vertical line of cross hair
        ch1.link_x_to(ch2)
        ch2.link_x_to(ch1)

        self.candle_ds: "CandleDataSource" = candle_ds
        self.volume_ds: "HistogramDataSource" = volume_ds
        self.candle_chart: "SubChartWrapper" = candle_wrapper
        self.volume_chart: "SubChartWrapper" = volume_wrapper
        self.setMouseTracking(True)

    def update_bar(self, bar: BarData):
        """
        Update one bar data into the chart.

        The bar data may be a new one or an existing one.
        """
        self.candle_ds.append(bar)
        self.volume_ds.append(bar.volume)
        begin, end = self.get_x_range()
        self.set_x_range(begin, end+1)

    def update_bars(self, bars: Sequence[BarData]):
        """
        Update a list of bar data into the chart.
        """
        self.candle_ds.extend(bars)
        self.volume_ds.extend([i.volume for i in bars])
        begin, end = self.get_x_range()
        self.set_x_range(begin, end+len(bars))
        pass

    def clear(self):
        """
        Clear all data displayed in the chart.
        """
        self.candle_ds.clear()
        self.volume_ds.clear()
        pass

    def set_volume_visible(self, visible: bool):
        """
        Set if the volume data visible on the chart.
        """
        self.volume_chart.set_chart_visible(visible)

    def set_cursor_visible(self, visible: bool):
        """
        Set if the cross cursor visible on the chart.
        """
        self.candle_chart.set_crosshair_visible(visible)
        self.volume_chart.set_crosshair_visible(visible)

    def to_left_end(self):
        """
        Scroll chart to the left end.
        """
        begin, end = self.get_x_range()
        new_end = len(self.candle_ds)
        self.scroll_x(new_end - end)

    def to_right_end(self):
        """
        Scroll chart to the right end.
        """
        begin, end = self.get_x_range()
        self.scroll_x(0-begin)
