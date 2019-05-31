from dataclasses import dataclass
from datetime import datetime
from typing import Generic, Iterable, List, TYPE_CHECKING, TypeVar

from PyQt5.QtCore import QObject, pyqtSignal

if TYPE_CHECKING:
    from .base import Alignment

T = TypeVar("T")


class DataSourceQObject(QObject):
    data_removed = pyqtSignal(int, int)  # (start: int, end: int)


class DataSource(Generic[T]):
    """
    DataSource for a Drawer.
    A DataSource is just like a list, but not all the operation is supported in list.
    Supported operations are:
    append(), clear(), __len__(), __getitem__(),
    """

    def __init__(self, parent=None):
        super().__init__()
        self.data_list: List[T] = []
        self.qobject = DataSourceQObject(parent)

    def extend(self, seq: Iterable[T]) -> None:
        self.data_list.extend(seq)

    def append(self, object: T) -> None:
        self.data_list.append(object)

    def clear(self) -> None:
        self.qobject.data_removed.emit(0, len(self.data_list))
        self.data_list.clear()

    def append_by_sequence(self, xs: List[float], align: "Alignment", item: List[T]):
        raise NotImplementedError()

    def __getitem__(self, item):
        return self.data_list[item]

    def __len__(self):
        return len(self.data_list)

    def __str__(self):
        return str(self.data_list)

    def __repr__(self):
        return repr(self.data_list)


@dataclass
class CandleData:
    """
    Represent a single record in DataSource for CandleChartDrawer
    """

    open_price: float
    low_price: float
    high_price: float
    close_price: float
    datetime: datetime


CandleDataSource = DataSource["CandleData"]
HistogramDataSource = DataSource[float]
