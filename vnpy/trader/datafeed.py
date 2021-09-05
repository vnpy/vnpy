from abc import ABC
from typing import Optional, List
from importlib import import_module
from vnpy.trader.database import BaseDatabase

from .object import HistoryRequest, TickData, BarData
from .setting import SETTINGS


class BaseDatafeed(ABC):
    """
    Abstract datafeed class for connecting to different datafeed.
    """

    def init(self) -> bool:
        """
        Initialize datafeed service connection.
        """
        pass

    def query_bar_history(self, req: HistoryRequest) -> Optional[List[BarData]]:
        """
        Query history bar data.
        """
        pass

    def query_tick_history(self, req: HistoryRequest) -> Optional[List[TickData]]:
        """
        Query history tick data.
        """
        pass


datafeed: BaseDatafeed = None


def get_datafeed() -> BaseDatafeed:
    """获取数据服务接口对象"""
    global datafeed
    if datafeed:
        return datafeed

    datafeed_name: str = SETTINGS["datafeed.name"]
    module_name: str = f"vnpy_{datafeed_name}"

    try:
        datafeed = import_module(module_name).datafeed
    except ModuleNotFoundError:
        print(f"找不到数据服务驱动{module_name}，使用默认的RQData数据服务")
        datafeed = import_module("vnpy_rqdata").datafeed

    return datafeed
