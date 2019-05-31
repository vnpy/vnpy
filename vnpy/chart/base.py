from dataclasses import dataclass
from enum import Enum
from typing import Optional, TYPE_CHECKING, TypeVar, Union

from PyQt5.QtCore import QPointF, QRectF
from PyQt5.QtGui import QColor, QTransform

if TYPE_CHECKING:
    pass

T = TypeVar("T")

ColorType = Union[
    str,  # "red", "#RGB", "#RRGGBB", "#AARRGGBB", "#RRRGGGBBB", "#RRRRGGGGBBBB"
    int,  # Qt.GlobalColor
    QColor,  # QtCore.QColor
    None,  # Don't draw
]


class Orientation(Enum):
    HORIZONTAL = 1
    VERTICAL = 2


class Alignment(Enum):
    BEFORE = 0
    MID = 1
    AFTER = 2


@dataclass()
class DrawingCache:
    # intermediate variables to speed up calculation
    drawer_transform: Optional["QTransform"] = None  # 坐标转化矩阵(UI->drawer)
    ui_transform: Optional["QTransform"] = None  # 坐标转化矩阵(drawer->UI)
    drawer_area: Optional["QRectF"] = None  # drawer坐标的世界大小
    drawer_area_width: Optional["float"] = None
    # self.drawer_area_height: Optional['float'] = None
    plot_area: Optional["QRectF"] = None  # UI坐标中属于绘制区域的部分
    # self.plot_area_width: Optional['float'] = None
    # self.plot_area_height: Optional['float'] = None
    p2d_w: Optional[float] = None  # drawer_area.width / plot_area.width
    p2d_h: Optional[float] = None  # drawer_area.height / plot_area.height

    def drawer_to_ui(self, value: T) -> T:
        """
        将drawer坐标系中的值（点或者矩形）转化为UI坐标系
        """
        return self.drawer_transform.map(value)

    def drawer_x_to_ui(self, value: float) -> float:
        """
        将drawer坐标系中的x值转化为UI坐标系中的x值
        """
        return self.drawer_transform.map(QPointF(value, value)).x()

    def drawer_y_to_ui(self, value: float) -> float:
        """
        将drawer坐标系中的y值转化为UI坐标系中的y值
        """
        return self.drawer_transform.map(QPointF(value, value)).y()

    def ui_width_to_drawer(self, value: float) -> float:
        return value * self.p2d_w

    def ui_height_to_drawer(self, value: float) -> float:
        return value * self.p2d_h

    def ui_to_drawer(self, value: T) -> T:
        return self.ui_transform.map(value)

    def ui_x_to_drawer(self, value: float) -> float:
        return self.ui_transform.map(QPointF(value, value)).x()

    def ui_y_to_drawer(self, value: float) -> float:
        return self.ui_transform.map(QPointF(value, value)).y()


@dataclass()
class DrawConfig:
    begin: int = 0  # 第一个绘制的元素
    end: int = 0  # 最后一个绘制的元素+1：也就是说绘制元素的范围为[begin, end)
    y_low: float = 0  # 图表顶端所代表的y值
    y_high: float = 1  # 图表底端所代表的y值

    drawing_cache: Optional["DrawingCache"] = None
