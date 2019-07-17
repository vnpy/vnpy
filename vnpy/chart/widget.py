from typing import List

import pyqtgraph as pg

from vnpy.trader.ui import QtGui, QtWidgets
from vnpy.trader.object import BarData

from .manager import BarManager
from .base import GREY_COLOR
from .axis import DatetimeAxis, AXIS_FONT
from .item import CandleItem, VolumeItem, ChartItem


class ChartWidget(pg.PlotWidget):
    """"""
    MIN_BAR_COUNT = 100

    def __init__(self, parent: QtWidgets.QWidget = None):
        """"""
        super().__init__(parent)

        self._manager: BarManager = BarManager()

        self._plots: List[ChartItem] = []
        self._items: List[pg.GraphicsObject] = []

        self._max_ix: int = 0
        self._bar_count: int = 0

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self._layout = pg.GraphicsLayout()
        self._layout.setContentsMargins(10, 10, 10, 10)
        self._layout.setSpacing(0)
        self._layout.setBorder(color=GREY_COLOR, width=0.8)
        self._layout.setZValue(0)

        self.setCentralItem(self._layout)

        self._x_axis = DatetimeAxis(self._manager, orientation='bottom')

        self.init_candle()
        self.init_volume()
        self._volume_plot.setXLink(self._candle_plot)

    def new_plot(self) -> None:
        """"""
        plot = pg.PlotItem(axisItems={'bottom': self._x_axis})
        plot.setMenuEnabled(False)
        plot.setClipToView(True)
        plot.hideAxis('left')
        plot.showAxis('right')
        plot.setDownsampling(mode='peak')
        plot.setRange(xRange=(0, 1), yRange=(0, 1))
        plot.hideButtons()

        view = plot.getViewBox()
        view.sigXRangeChanged.connect(self._change_plot_y_range)
        view.setMouseEnabled(x=True, y=False)

        right_axis = plot.getAxis('right')
        right_axis.setWidth(60)
        right_axis.setStyle(tickFont=AXIS_FONT)

        return plot

    def init_candle(self) -> None:
        """
        Initialize candle plot.
        """
        self._candle_item = CandleItem(self._manager)
        self._items.append(self._candle_item)

        self._candle_plot = self.new_plot()
        self._candle_plot.addItem(self._candle_item)
        self._candle_plot.setMinimumHeight(80)
        self._candle_plot.hideAxis('bottom')
        self._plots.append(self._candle_plot)

        self._layout.nextRow()
        self._layout.addItem(self._candle_plot)

    def init_volume(self) -> None:
        """
        Initialize bar plot.
        """
        self._volume_item = VolumeItem(self._manager)
        self._items.append(self._volume_item)

        self._volume_plot = self.new_plot()
        self._volume_plot.addItem(self._volume_item)
        self._volume_plot.setMinimumHeight(80)
        self._plots.append(self._volume_plot)

        self._layout.nextRow()
        self._layout.addItem(self._volume_plot)

    def clear_all(self) -> None:
        """
        Clear all data.
        """
        self._manager.clear_all()

        for item in self._items:
            item.clear_all()

    def update_history(self, history: List[BarData]) -> None:
        """
        Update a list of bar data.
        """
        self._manager.update_history(history)

        for item in self._items:
            item.update_history(history)

        self._update_plot_range()

    def update_bar(self, bar: BarData) -> None:
        """
        Update single bar data.
        """
        self._manager.update_bar(bar)

        for item in self.items:
            item.update_bar(bar)

        self._update_plot_range()

    def _update_plot_range(self) -> None:
        """
        Update the range of plots.
        """
        max_ix = self._max_ix
        min_ix = self._max_ix - self._bar_count

        # Update limit and range for x-axis
        for plot in self._plots:
            plot.setLimits(
                xMin=-self.MIN_BAR_COUNT,
                xMax=self._manager.get_count()
            )
            plot.setRange(
                xRange=(min_ix, max_ix),
                padding=0
            )

        # Update limit for y-axis
        min_price, max_price = self._manager.get_price_range()
        self._candle_plot.setLimits(yMin=min_price, yMax=max_price)

        min_volume, max_volume = self._manager.get_volume_range()
        self._volume_plot.setLimits(yMin=min_volume, yMax=max_volume)

    def _change_plot_y_range(self) -> None:
        """
        Reset the y-axis range of plots.
        """
        view = self._candle_plot.getViewBox()
        view_range = view.viewRange()
        min_ix = max(0, int(view_range[0][0]))
        max_ix = min(self._manager.get_count(), int(view_range[0][1]))

        price_range = self._manager.get_price_range(min_ix, max_ix)
        self._candle_plot.setRange(yRange=price_range)

        volume_range = self._manager.get_volume_range(min_ix, max_ix)
        self._volume_plot.setRange(yRange=volume_range)

    def paintEvent(self, event: QtGui.QPaintEvent) -> None:
        """
        Reimplement this method of parent to update current max_ix value.
        """
        view = self._candle_plot.getViewBox()
        view_range = view.viewRange()
        self._max_ix = max(0, view_range[0][1])

        super().paintEvent(event)
