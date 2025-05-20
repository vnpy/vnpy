from types import ModuleType
from collections.abc import Callable
from importlib import import_module

from .object import HistoryRequest, TickData, BarData
from .setting import SETTINGS


class BaseDatafeed:
    """
    Abstract datafeed class for connecting to different datafeed.
    """

    def init(self, output: Callable = print) -> bool:
        """
        Initialize datafeed service connection.
        """
        return False

    def query_bar_history(self, req: HistoryRequest, output: Callable = print) -> list[BarData]:
        """
        Query history bar data.
        """
        output("K-line data query failed: Data service not properly configured")
        return []

    def query_tick_history(self, req: HistoryRequest, output: Callable = print) -> list[TickData]:
        """
        Query history tick data.
        """
        output("Tick data query failed: Data service not properly configured")
        return []


datafeed: BaseDatafeed | None = None


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

        print("No data service configured, please modify datafeed settings in global configuration")
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

            print(f"Cannot load data service module, please try installing with: pip install {module_name}")

    return datafeed     # type: ignore
