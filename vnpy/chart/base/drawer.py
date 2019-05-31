from abc import ABC, abstractmethod
from threading import Lock
from typing import Optional, TYPE_CHECKING, TypeVar

from PyQt5.QtCore import QRectF
from PyQt5.QtGui import QBrush, QColor, QPainter

from .data_source import CandleData, DataSource

if TYPE_CHECKING:
    from .base import ColorType, DrawConfig

T = TypeVar("T")


class ChartDrawerBase(ABC):
    """
    数据序列
    有两个职责：
    1、管理自身的数据
    2、将数据绘制出来

    各个虚函数的调用顺序是这样的：
    ```
    for series in all_series:
        series.before_draw()
           for i in ...:
               series.draw_item()
        series.after_draw()
    ```
    """

    def __init__(self, data_source: Optional["DataSource"] = None):
        self._data_source: Optional["DataSource"] = None
        self._data_source_lock = Lock()
        self.set_data_source(data_source)

    def set_data_source(self, data_source: "DataSource"):
        with self._data_source_lock:
            if self._data_source is not data_source:
                if self._data_source is not None:
                    self._detach_data_source()
                self._data_source = data_source
                self._attach_data_source()

    def has_data(self):
        return self._data_source is not None and len(self._data_source)

    def on_data_source_data_removed(self, begin: int, end: int):
        pass

    def on_data_source_destroyed(self):
        with self._data_source_lock:
            self._data_source = None

    @abstractmethod
    def prepare_draw(self, config: "DrawConfig") -> "DrawConfig":
        """
        在准备绘制的时候会被调用，可能会被调用多次。
        这个函数应该根据config的值计算出自身所需的y值
        并且将[y_low, y_high]设置为自己绘制所有图像所覆盖的y值范围。
        绘图引擎会根据各个数据序列所覆盖的y值范围不断调整图表自身值的范围，直到刚好能显示所有数据序列为止

        注意：这里收到的config并不是draw_all时所使用的设置
        :return: "DrawConfig"
        """
        return config

    @abstractmethod
    def draw(self, config: "DrawConfig", painter: QPainter):
        """
        绘制数据，可以在整张图上任意绘制，但是该函数最好每次只绘制坐标属于x的图
        坐标系(以下称为drawer坐标系)使用和数据x-y值一致的坐标系:原点在左下角，x轴向右,y轴向上 => 坐下到右上
        整个图形的坐标范围为: (left, bottom, right, top) = (begin, y_low, end, y_high)
        因为图标并不知道数据的任何细节，所以draw_item函数应该自己检查x值是否越界
        """
        pass

    def _attach_data_source(self):
        self._data_source.qobject.data_removed.connect(self.on_data_source_data_removed)
        self._data_source.qobject.destroyed.connect(self.on_data_source_destroyed)

    def _detach_data_source(self):
        raise RuntimeError("Rest of DataSource is currently not implemented.")


class CandleChartDrawer(ChartDrawerBase):
    """
    Drawer to present candlestick chart

    if cache is enabled
    """

    def __init__(self, data_source: Optional["DataSource"] = None):
        super().__init__(data_source)
        self.body_width = 0.95
        self.line_width = 0.15
        self.minimum_box_height = 0.01
        self.growing_color: "ColorType" = "red"
        self.falling_color: "ColorType" = "green"
        self.use_cache = True

        # cached variables for draw
        self._cache_raising = []
        self._cache_falling = []
        self._cache_end = 0

    def on_data_source_data_removed(self, begin: int, end: int):
        # todo: fix cache, but not to rebuild it.
        self.clear_cache()

    def prepare_draw(self, config: "DrawConfig") -> "DrawConfig":
        showing_data = self._data_source[config.begin: config.end]
        if showing_data:
            low = min(showing_data, key=lambda c: c.low).low
            high = max(showing_data, key=lambda c: c.high).high
            config.y_low, config.y_high = low, high
        return config

    def draw(self, config: "DrawConfig", painter: "QPainter"):
        raising_brush = QBrush(QColor(self.growing_color))
        falling_brush = QBrush(QColor(self.falling_color))

        begin, end = config.begin, config.end

        # 如果不使用cache，简单的做法就是每次绘图之前清空一下cache
        if not self.use_cache:
            self.clear_cache()
        data_len = len(self._data_source)
        if data_len > self._cache_end:
            self._generate_cache(self._cache_end, data_len)

        painter.setBrush(raising_brush)
        painter.drawRects([i for i in self._cache_raising[begin * 2: end * 2] if i])
        painter.setBrush(falling_brush)
        painter.drawRects([i for i in self._cache_falling[begin * 2: end * 2] if i])

    def clear_cache(self):
        self._cache_end = 0
        self._cache_raising = []
        self._cache_falling = []

    def _generate_cache(self, begin, end):
        for i in range(begin, end):
            data: "CandleData" = self._data_source[i]

            if data.open <= data.close:
                push_cache = self._cache_raising
                nop_cache = self._cache_falling
            else:
                push_cache = self._cache_falling
                nop_cache = self._cache_raising

            # draw box
            box = self.get_rect(i, data.open, data.close, self.body_width)
            push_cache.append(box)
            nop_cache.append(None)

            # draw line
            line = self.get_rect(i, data.low, data.high, self.line_width)
            push_cache.append(line)
            nop_cache.append(None)

        self._cache_end = end

    def get_rect(self, i, start_y, end_y, width):
        left = i + 0.5 - 0.5 * width
        rect = QRectF(
            left,
            min(start_y, end_y),
            width,
            max(abs(start_y - end_y), self.minimum_box_height),
        )
        return rect


class BarChartDrawer(ChartDrawerBase):
    """
    Drawer to present Histogram.

    When use_cache is disable, BarChartDrawer supports any list like DataSource,
      including un-formal DataSource).
    When use_cache is enabled, BarChartDrawer supports only formal DataSource
    """

    def __init__(self, data_source: Optional["DataSource"] = None):
        super().__init__(data_source)
        self.body_width = 1
        self.positive_color: "ColorType" = "red"
        self.negative_color: "ColorType" = "green"

        self.use_cache = True

        # cached variables for draw
        self._cache_positive = []
        self._cache_negative = []
        self._cache_end = 0

    def on_data_source_data_removed(self, begin: int, end: int):
        self.clear_cache()

    def prepare_draw(self, config: "DrawConfig") -> "DrawConfig":
        showing_data = self._data_source[config.begin: config.end]
        if showing_data:
            low = min(showing_data)
            high = max(showing_data)
            config.y_low, config.y_high = low, high
        return config

    def draw(self, config: "DrawConfig", painter: "QPainter"):
        raising_brush = QBrush(QColor(self.positive_color))
        falling_brush = QBrush(QColor(self.negative_color))

        begin, end = config.begin, config.end

        if not self.use_cache:
            self.clear_cache()
        cache_end = self._cache_end

        data_len = len(self._data_source)
        if data_len > cache_end:
            self._generate_cache(cache_end, data_len)

        painter.setBrush(raising_brush)
        painter.drawRects([i for i in self._cache_positive[begin:end] if i])
        painter.setBrush(falling_brush)
        painter.drawRects([i for i in self._cache_negative[begin:end] if i])

    def clear_cache(self):
        self._cache_end = 0
        self._cache_positive = []
        self._cache_negative = []

    def _generate_cache(self, begin, end):
        for i in range(begin, end):
            data: "float" = self._data_source[i]

            if data > 0:
                push_cache = self._cache_positive
                nop_cache = self._cache_negative
            else:
                push_cache = self._cache_negative
                nop_cache = self._cache_positive

            # draw box
            box = self.get_rect(i, 0, data, self.body_width)
            push_cache.append(box)
            nop_cache.append(None)

        self._cache_end = end

    def get_rect(self, i, start_y, end_y, width):
        left = i + 0.5 - 0.5 * width
        rect = QRectF(left, min(start_y, end_y), width, abs(start_y - end_y))
        return rect


HistogramDrawer = BarChartDrawer
