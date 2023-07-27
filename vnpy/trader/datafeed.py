from abc import ABC
from types import ModuleType
from typing import Optional, List, Callable
from importlib import import_module

from .object import HistoryRequest, TickData, BarData
from .setting import SETTINGS


class BaseDatafeed(ABC):
    """
    Abstract datafeed class for connecting to different datafeed.
    """

    def init(self, output: Callable = print) -> bool:
        """
        Initialize datafeed service connection.
        """
        output("当前没有配置数据服务，无法进行查询，请在全局配置中修改datafeed相关信息")

    def query_bar_history(self, req: HistoryRequest, output: Callable = print) -> Optional[List[BarData]]:
        """
        Query history bar data.
        """
        output("当前没有配置数据服务，无法进行查询，请在全局配置中修改datafeed相关信息")

    def query_tick_history(self, req: HistoryRequest, output: Callable = print) -> Optional[List[TickData]]:
        """
        Query history tick data.
        """
        output("当前没有配置数据服务，无法进行查询，请在全局配置中修改datafeed相关信息")


datafeed: BaseDatafeed = None


def get_datafeed() -> BaseDatafeed:
    """"""
    # Return datafeed object if already inited
    global datafeed
    if datafeed:
        return datafeed

    # Read datafeed related global setting
    datafeed_name: str = SETTINGS["datafeed.name"]
    module_name: str = f"vnpy_{datafeed_name}"

    # Try to import datafeed module
    try:
        module: ModuleType = import_module(module_name)

        # Create datafeed object from module
        datafeed = module.Datafeed()

    except ModuleNotFoundError:
        if datafeed_name:
            print(f"找不到数据服务驱动{module_name}")

        datafeed = BaseDatafeed()

    return datafeed
