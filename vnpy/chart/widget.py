from typing import List, Dict, Type
from collections import deque
import pyqtgraph as pg

from vnpy.trader.ui import QtGui, QtWidgets, QtCore
from vnpy.trader.object import BarData

from .manager import BarManager
from .base import (
    GREY_COLOR, WHITE_COLOR, CURSOR_COLOR, BLACK_COLOR,
    to_int, NORMAL_FONT
)
from .axis import DatetimeAxis
from .item import ChartItem, CandleItem, VolumeItem

pg.setConfigOptions(antialias=True)


class ChartWidget(pg.PlotWidget):
    """"""
    MIN_BAR_COUNT = 100

    def __init__(self, parent: QtWidgets.QWidget = None, title: str = "ChartWidget of vn.py"):
        """"""
        super().__init__(parent)
        self.title = title
        self._manager: BarManager = BarManager()

        self._plots: Dict[str, pg.PlotItem] = {}
        self._items: Dict[str, ChartItem] = {}
        self._item_plot_map: Dict[ChartItem, pg.PlotItem] = {}

        self._first_plot: pg.PlotItem = None
        self._cursor: ChartCursor = None

        self._right_ix: int = 0  # Index of most right data
        self._bar_count: int = self.MIN_BAR_COUNT  # Total bar visible in chart

        self._init_ui()

    def _init_ui(self) -> None:
        """"""
        self.setWindowTitle(self.title)

        self._layout = pg.GraphicsLayout()
        self._layout.setContentsMargins(10, 10, 10, 10)
        self._layout.setSpacing(0)
        self._layout.setBorder(color=GREY_COLOR, width=0.8)
        self._layout.setZValue(0)
        self.setCentralItem(self._layout)

        self._x_axis = DatetimeAxis(self._manager, orientation='bottom')

    def add_cursor(self) -> None:
        """"""
        if not self._cursor:
            self._cursor = ChartCursor(
                self, self._manager, self._plots, self._item_plot_map)

    def add_plot(
            self,
            plot_name: str,
            minimum_height: int = 80,
            maximum_height: int = None,
            hide_x_axis: bool = False
    ) -> None:
        """
        Add plot area.
        """
        # Create plot object
        plot = pg.PlotItem(axisItems={'bottom': self._x_axis})
        plot.setMenuEnabled(False)
        plot.setClipToView(True)
        plot.hideAxis('left')
        plot.showAxis('right')
        plot.setDownsampling(mode='peak')
        plot.setRange(xRange=(0, 1), yRange=(0, 1))
        plot.hideButtons()
        plot.setMinimumHeight(minimum_height)

        if maximum_height:
            plot.setMaximumHeight(maximum_height)

        if hide_x_axis:
            plot.hideAxis("bottom")

        if not self._first_plot:
            self._first_plot = plot

        # Connect view change signal to update y range function
        view = plot.getViewBox()
        view.sigXRangeChanged.connect(self._update_y_range)
        view.setMouseEnabled(x=True, y=False)

        # Set right axis
        right_axis = plot.getAxis('right')
        right_axis.setWidth(60)
        right_axis.tickFont = NORMAL_FONT

        # Connect x-axis link
        if self._plots:
            first_plot = list(self._plots.values())[0]
            plot.setXLink(first_plot)

        # Store plot object in dict
        self._plots[plot_name] = plot

        # Add plot onto the layout
        self._layout.nextRow()
        self._layout.addItem(plot)

    def add_item(
            self,
            item_class: Type[ChartItem],
            item_name: str,
            plot_name: str
    ):
        """
        Add chart item.
        """
        # 创建显示的对象，蜡烛图，bar图，散点，线等
        item = item_class(self._manager)
        self._items[item_name] = item

        # 获取设置的显示区域，例如主图/volume/附图等
        plot = self._plots.get(plot_name)
        plot.addItem(item)

        # 绑定显示对象与显示区域关系
        self._item_plot_map[item] = plot

    def get_plot(self, plot_name: str) -> pg.PlotItem:
        """
        Get specific plot with its name.
        """
        return self._plots.get(plot_name, None)

    def get_all_plots(self) -> List[pg.PlotItem]:
        """
        Get all plot objects.
        """
        return self._plots.values()

    def clear_all(self) -> None:
        """
        Clear all data.
        """
        self._manager.clear_all()

        for item in self._items.values():
            item.clear_all()

        if self._cursor:
            self._cursor.clear_all()

    def update_history(self, history: List[BarData]) -> None:
        """
        Update a list of bar data.
        """
        self._manager.update_history(history)

        for item in self._items.values():
            item.update_history(history)

        self._update_plot_limits()

        self.move_to_right()

    def update_bar(self, bar: BarData) -> None:
        """
        Update single bar data.
        """
        self._manager.update_bar(bar)

        for item in self._items.values():
            item.update_bar(bar)

        # 刷新显示区域的最高/最低值
        self._update_plot_limits()

        if self._right_ix >= (self._manager.get_count() - self._bar_count / 2):
            self.move_to_right()

    def _update_plot_limits(self) -> None:
        """
        Update the limit of plots.
        """
        for item, plot in self._item_plot_map.items():
            min_value, max_value = item.get_y_range()

            plot.setLimits(
                xMin=-1,
                xMax=self._manager.get_count(),
                yMin=min_value,
                yMax=max_value
            )

    def _update_x_range(self) -> None:
        """
        Update the x-axis range of plots.
        """
        max_ix = self._right_ix
        min_ix = self._right_ix - self._bar_count

        for plot in self._plots.values():
            plot.setRange(xRange=(min_ix, max_ix), padding=0)

    def _update_y_range(self) -> None:
        """
        Update the y-axis range of plots.
        """
        view = self._first_plot.getViewBox()
        view_range = view.viewRange()

        min_ix = max(0, int(view_range[0][0]))
        max_ix = min(self._manager.get_count(), int(view_range[0][1]))

        # Update limit for y-axis
        for item, plot in self._item_plot_map.items():
            y_range = item.get_y_range(min_ix, max_ix)
            plot.setRange(yRange=y_range)

    def paintEvent(self, event: QtGui.QPaintEvent) -> None:
        """
        Reimplement this method of parent to update current max_ix value.
        """
        view = self._first_plot.getViewBox()
        view_range = view.viewRange()
        self._right_ix = max(0, view_range[0][1])

        super().paintEvent(event)

    def keyPressEvent(self, event: QtGui.QKeyEvent) -> None:
        """
        Reimplement this method of parent to move chart horizontally and zoom in/out.
        """
        if event.key() == QtCore.Qt.Key_Left:
            self._on_key_left()
        elif event.key() == QtCore.Qt.Key_Right:
            self._on_key_right()
        elif event.key() == QtCore.Qt.Key_Up:
            self._on_key_up()
        elif event.key() == QtCore.Qt.Key_Down:
            self._on_key_down()

    def wheelEvent(self, event: QtGui.QWheelEvent) -> None:
        """
        Reimplement this method of parent to zoom in/out.
        """
        delta = event.angleDelta()

        if delta.y() > 0:
            self._on_key_up()
        elif delta.y() < 0:
            self._on_key_down()

    def _on_key_left(self) -> None:
        """
        Move chart to left.
        """
        self._right_ix -= 1
        self._right_ix = max(self._right_ix, self._bar_count)

        self._update_x_range()
        self._cursor.move_left()
        self._cursor.update_info()

    def _on_key_right(self) -> None:
        """
        Move chart to right.
        """
        self._right_ix += 1
        self._right_ix = min(self._right_ix, self._manager.get_count())

        self._update_x_range()
        self._cursor.move_right()
        self._cursor.update_info()

    def _on_key_down(self) -> None:
        """
        Zoom out the chart.
        """
        self._bar_count *= 1.2
        self._bar_count = min(int(self._bar_count), self._manager.get_count())

        self._update_x_range()
        self._cursor.update_info()

    def _on_key_up(self) -> None:
        """
        Zoom in the chart.
        """
        self._bar_count /= 1.2
        self._bar_count = max(int(self._bar_count), self.MIN_BAR_COUNT)

        self._update_x_range()
        self._cursor.update_info()

    def move_to_right(self) -> None:
        """
        Move chart to the most right.
        """
        self._right_ix = self._manager.get_count()
        self._update_x_range()
        self._cursor.update_info()


class ChartCursor(QtCore.QObject):
    """"""

    def __init__(
            self,
            widget: ChartWidget,
            manager: BarManager,
            plots: Dict[str, pg.GraphicsObject],
            item_plot_map: Dict[ChartItem, pg.GraphicsObject]
    ):
        """"""
        super().__init__()

        self._widget: ChartWidget = widget
        self._manager: BarManager = manager
        self._plots: Dict[str, pg.GraphicsObject] = plots
        self._item_plot_map: Dict[ChartItem, pg.GraphicsObject] = item_plot_map

        self._x: int = 0
        self._y: int = 0
        self._plot_name: str = ""

        self._init_ui()
        self._connect_signal()

    def _init_ui(self):
        """"""
        self._init_line()
        self._init_label()
        self._init_info()

    def _init_line(self) -> None:
        """
        Create line objects.
        """
        self._v_lines: Dict[str, pg.InfiniteLine] = {}
        self._h_lines: Dict[str, pg.InfiniteLine] = {}
        self._views: Dict[str, pg.ViewBox] = {}

        pen = pg.mkPen(WHITE_COLOR)

        for plot_name, plot in self._plots.items():
            v_line = pg.InfiniteLine(angle=90, movable=False, pen=pen)
            h_line = pg.InfiniteLine(angle=0, movable=False, pen=pen)
            view = plot.getViewBox()

            for line in [v_line, h_line]:
                line.setZValue(0)
                line.hide()
                view.addItem(line)

            self._v_lines[plot_name] = v_line
            self._h_lines[plot_name] = h_line
            self._views[plot_name] = view

    def _init_label(self) -> None:
        """
        Create label objects on axis.
        """
        self._y_labels: Dict[str, pg.TextItem] = {}
        for plot_name, plot in self._plots.items():
            label = pg.TextItem(
                plot_name, fill=CURSOR_COLOR, color=BLACK_COLOR)
            label.hide()
            label.setZValue(2)
            label.setFont(NORMAL_FONT)
            plot.addItem(label, ignoreBounds=True)
            self._y_labels[plot_name] = label

        self._x_label: pg.TextItem = pg.TextItem(
            "datetime", fill=CURSOR_COLOR, color=BLACK_COLOR)
        self._x_label.hide()
        self._x_label.setZValue(2)
        self._x_label.setFont(NORMAL_FONT)
        plot.addItem(self._x_label, ignoreBounds=True)

    def _init_info(self) -> None:
        """
        """
        self._infos: Dict[str, pg.TextItem] = {}
        for plot_name, plot in self._plots.items():
            info = pg.TextItem(
                "info",
                color=CURSOR_COLOR,
                border=CURSOR_COLOR,
                fill=BLACK_COLOR
            )
            info.hide()
            info.setZValue(2)
            info.setFont(NORMAL_FONT)
            plot.addItem(info)  # , ignoreBounds=True)
            self._infos[plot_name] = info

    def _connect_signal(self) -> None:
        """
        Connect mouse move signal to update function.
        """
        self._widget.scene().sigMouseMoved.connect(self._mouse_moved)

    def _mouse_moved(self, evt: tuple) -> None:
        """
        Callback function when mouse is moved.
        """
        if not self._manager.get_count():
            return

        # First get current mouse point
        pos = evt

        for plot_name, view in self._views.items():
            rect = view.sceneBoundingRect()

            if rect.contains(pos):
                mouse_point = view.mapSceneToView(pos)
                self._x = to_int(mouse_point.x())
                self._y = mouse_point.y()
                self._plot_name = plot_name
                break

        # Then update cursor component
        self._update_line()
        self._update_label()
        self.update_info()

    def _update_line(self) -> None:
        """"""
        for v_line in self._v_lines.values():
            v_line.setPos(self._x)
            v_line.show()

        for plot_name, h_line in self._h_lines.items():
            if plot_name == self._plot_name:
                h_line.setPos(self._y)
                h_line.show()
            else:
                h_line.hide()

    def _update_label(self) -> None:
        """"""
        bottom_plot = list(self._plots.values())[-1]
        axis_width = bottom_plot.getAxis("right").width()
        axis_height = bottom_plot.getAxis("bottom").height()
        axis_offset = QtCore.QPointF(axis_width, axis_height)

        bottom_view = list(self._views.values())[-1]
        bottom_right = bottom_view.mapSceneToView(
            bottom_view.sceneBoundingRect().bottomRight() - axis_offset
        )

        for plot_name, label in self._y_labels.items():
            if plot_name == self._plot_name:
                label.setText(str(self._y))
                label.show()
                label.setPos(bottom_right.x(), self._y)
            else:
                label.hide()

        dt = self._manager.get_datetime(self._x)
        if dt:
            self._x_label.setText(dt.strftime("%Y-%m-%d %H:%M:%S"))
            self._x_label.show()
            self._x_label.setPos(self._x, bottom_right.y())
            self._x_label.setAnchor((0, 0))

    def update_info(self) -> None:
        """"""
        buf = {}

        for item, plot in self._item_plot_map.items():
            item_info_text = item.get_info_text(self._x)

            if plot not in buf:
                buf[plot] = item_info_text
            else:
                if item_info_text:
                    buf[plot] += ("\n\n" + item_info_text)

        for plot_name, plot in self._plots.items():
            plot_info_text = buf.get(plot, None)
            if not plot_info_text:
                continue
            info = self._infos[plot_name]
            info.setText(plot_info_text)
            info.show()

            view = self._views[plot_name]
            top_left = view.mapSceneToView(view.sceneBoundingRect().topLeft())
            info.setPos(top_left)

    def move_right(self) -> None:
        """
        Move cursor index to right by 1.
        """
        if self._x == self._manager.get_count() - 1:
            return
        self._x += 1

        self._update_after_move()

    def move_left(self) -> None:
        """
        Move cursor index to left by 1.
        """
        if self._x == 0:
            return
        self._x -= 1

        self._update_after_move()

    def _update_after_move(self) -> None:
        """
        Update cursor after moved by left/right.
        """
        bar = self._manager.get_bar(self._x)
        self._y = bar.close_price

        self._update_line()
        self._update_label()

    def clear_all(self) -> None:
        """
        Clear all data.
        """
        self._x = 0
        self._y = 0
        self._plot_name = ""

        for line in list(self._v_lines.values()) + list(self._h_lines.values()):
            line.hide()

        for label in list(self._y_labels.values()) + [self._x_label]:
            label.hide()


class KlineWidget(ChartWidget):
    """ k线widget，支持多widget；主图/volume/附图"""
    clsId = 0

    def __init__(self, parent: QtWidgets.QWidget = None,
                 title: str = "kline",
                 display_volume: bool = False,
                 display_sub: bool = False):

        super().__init__(parent, title)

        KlineWidget.clsId += 1
        self.windowId = str(KlineWidget.clsId)

        # 所有K线上指标
        self.main_color_pool = deque(['red', 'green', 'yellow', 'white'])
        self.main_indicator_data = {}  # 主图指标数据（字典，key是指标，value是list）
        self.main_indicator_colors = {}  # 主图指标颜色（字典，key是指标，value是list
        self.main_indicator_plots = {}  # 主图指标的所有画布（字典，key是指标，value是plot)

        self.display_volume = display_volume
        self.display_sub = display_sub

        # 所有副图上指标
        self.sub_color_pool = deque(['red', 'green', 'yellow', 'white'])
        self.sub_indicator_data = {}
        self.sub_indicator_colors = {}
        self.sub_indicator_plots = {}

        self.main_plot_name = f'{self.windowId}_main'
        self.volume_plot_name = f'{self.windowId}_volume'
        self.sub_plot_name = f'{self.windowId}_sub'

        self.main_plot = None
        self.volume_plot = None
        self.sub_plot = None
        if self.display_volume or self.display_sub:
            self.add_plot(self.main_plot_name, hide_x_axis=True)  # 主图
            self.add_item(CandleItem, "candle", self.main_plot_name)  # 往主图区域，加入
            if self.display_volume:
                self.add_plot(self.volume_plot_name, maximum_height=60)  # volume 附图
                self.add_item(VolumeItem, "volume", self.volume_plot_name)
                self.volume_plot = self.get_plot(self.volume_plot_name)
            if self.display_sub:
                self.add_plot(self.sub_plot_name, maximum_height=180)  # 附图
                self.sub_plot = self.get_plot(self.sub_plot_name)

        else:
            self.add_plot(self.main_plot_name, hide_x_axis=False)  # 主图
            self.add_item(CandleItem, "candle", self.main_plot_name)  # 往主图区域，加入
        self.add_cursor()
        self.main_plot = self.get_plot(self.main_plot_name)

    def add_indicator(self, indicator: str, is_main: bool = True):
        """
        新增指标信号图
        :param indicator: 指标/信号的名称，如ma10，
        :param is_main: 是否为主图
        :return:
        """
        if is_main:

            if indicator in self.main_indicator_plots:
                self.main_plot.removeItem(self.main_indicator_plots[indicator])  # 存在该指标/信号，先移除原有画布

            self.main_indicator_plots[indicator] = self.main_plot.plot()  # 为该指标/信号，创建新的主图画布，登记字典
            self.main_indicator_colors[indicator] = self.main_color_pool[0]  # 登记该指标/信号使用的颜色
            self.main_color_pool.append(self.main_color_pool.popleft())  # 调整剩余颜色
            if indicator not in self.main_indicator_data:
                self.main_indicator_data[indicator] = []
        else:
            if indicator in self.sub_indicator_plots:
                self.sub_plot.removeItem(self.sub_indicator_plots[indicator])  # 若存在该指标/信号，先移除原有的附图画布
            self.sub_indicator_plots[indicator] = self.sub_plot.plot()  # 为该指标/信号，创建新的主图画布，登记字典
            self.sub_indicator_colors[indicator] = self.sub_color_pool[0]  # 登记该指标/信号使用的颜色
            self.sub_color_pool.append(self.sub_color_pool.popleft())  # 调整剩余颜色
            if indicator not in self.sub_indicator_data:
                self.sub_indicator_data[indicator] = []

    def clear_indicator(self, main=True):
        """清空指标图形"""
        # 清空信号图
        if main:
            for indicator in self.main_indicator_plots:
                self.main_plot.removeItem(self.main_indicator_plots[indicator])
            self.main_indicator_data = {}
            self.main_indicator_plots = {}
        else:
            for indicator in self.sub_indicator_plots:
                self.sub_plot.removeItem(self.sub_indicator_plots[indicator])
            self.sub_indicator_data = {}
            self.sub_indicator_plots = {}

    def plot_indicator(self, datas: dict, is_main=True, clear=False):
        """
        刷新指标/信号图( 新数据）
        :param datas: 所有数据
        :param is_main: 是否为主图
        :param clear: 是否要清除旧数据
        :return:
        """
        if clear:
            self.clear_indicator(is_main)  # 清除主图/副图

        if is_main:
            for indicator in datas:
                self.add_indicator(indicator, is_main)  # 逐一添加主图信号/指标
                self.main_indicator_data[indicator] = datas[indicator]  # 更新组件数据字典
                # 调用该信号/指标画布(plotDataItem.setData())，更新数据，更新画笔颜色，更新名称
                self.main_indicator_plots[indicator].setData(datas[indicator],
                                                             pen=self.main_indicator_colors[indicator][0],
                                                             name=indicator)
        else:
            for indicator in datas:
                self.add_indicator(indicator, is_main)  # 逐一增加子图指标/信号
                self.sub_indicator_data[indicator] = datas[indicator]  # 更新组件数据字典
                # 调用该信号/指标画布(plotDataItem.setData())，更新数据，更新画笔颜色，更新名称
                self.sub_indicator_plots[indicator].setData(datas[indicator],
                                                            pen=self.sub_indicator_colors[indicator][0], name=indicator)
