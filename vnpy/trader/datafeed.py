from abc import ABC
from types import ModuleType
from typing import Optional, Callable
from importlib import import_module

from .object import HistoryRequest, TickData, BarData
from .setting import SETTINGS
from .locale import _


class BaseDatafeed(ABC):
    """
    Abstract datafeed class for connecting to different datafeed.
    """

    def init(self, output: Callable = print) -> bool:
        """
        Initialize datafeed service connection.
        """
        pass

    def query_bar_history(self, req: HistoryRequest, output: Callable = print) -> Optional[list[BarData]]:
        """
        Query history bar data.
        """
        output(_("查询K线数据失败：没有正确配置数据服务"))

    def query_tick_history(self, req: HistoryRequest, output: Callable = print) -> Optional[list[TickData]]:
        """
        Query history tick data.
        """
        output(_("查询Tick数据失败：没有正确配置数据服务"))


datafeed: BaseDatafeed = None


def get_datafeed() -> BaseDatafeed:
    """"""
    # Return datafeed object if already inited
    global datafeed
    if datafeed:
        return datafeed

    # Read datafeed related global setting
    datafeed_name: str = SETTINGS["datafeed.name"]

    if not datafeed_name:
        datafeed = BaseDatafeed()

        print(_("没有配置要使用的数据服务，请修改全局配置中的datafeed相关内容"))
    else:
        module_name: str = f"vnpy_{datafeed_name}"

        # Try to import datafeed module
        try:
            module: ModuleType = import_module(module_name)

            # Create datafeed object from module
            datafeed = module.Datafeed()
        # Use base class if failed
        except ModuleNotFoundError:
            datafeed = BaseDatafeed()

            print(_("无法加载数据服务模块，请运行 pip install {} 尝试安装").format(module_name))

    return datafeed
