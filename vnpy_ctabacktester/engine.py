import importlib
import traceback
from datetime import datetime
from threading import Thread, Event as ThreadEvent
from pathlib import Path
from inspect import getfile
from glob import glob
from types import ModuleType
from pandas import DataFrame

from vnpy.event import Event, EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.utility import extract_vt_symbol
from vnpy.trader.object import HistoryRequest, TickData, BarData, ContractData
from vnpy.trader.datafeed import BaseDatafeed, get_datafeed
from vnpy.trader.database import BaseDatabase, BarOverview, TickOverview, get_database
import vnpy_ctastrategy

from vnpy_ctastrategy import CtaTemplate, TargetPosTemplate
from vnpy_ctastrategy.backtesting import (
    BacktestingEngine,
    OptimizationSetting,
    BacktestingMode
)
from .locale import _

APP_NAME = "CtaBacktester"

EVENT_BACKTESTER_LOG = "eBacktesterLog"
EVENT_BACKTESTER_BACKTESTING_FINISHED = "eBacktesterBacktestingFinished"
EVENT_BACKTESTER_OPTIMIZATION_FINISHED = "eBacktesterOptimizationFinished"
EVENT_BACKTESTER_DOWNLOADING_FINISHED = "eBacktesterDownloadingFinished"


def _get_missing_history_range(
    overviews: list[BarOverview],
    symbol: str,
    exchange: Exchange,
    interval: Interval,
    start: datetime,
    end: datetime
) -> tuple[datetime, datetime] | None:
    """
    Return missing range for bar history if coverage is incomplete.
    """
    for overview in overviews:
        if (
            overview.symbol == symbol
            and overview.exchange == exchange
            and overview.interval == interval
            and overview.start
            and overview.end
        ):
            if overview.start <= start and overview.end >= end:
                return None
            break

    return (start, end)


def _get_missing_tick_range(
    overviews: list[TickOverview],
    symbol: str,
    exchange: Exchange,
    start: datetime,
    end: datetime
) -> tuple[datetime, datetime] | None:
    """
    Return missing range for tick history if coverage is incomplete.
    """
    for overview in overviews:
        if overview.symbol == symbol and overview.exchange == exchange:
            if overview.start and overview.end:
                if overview.start <= start and overview.end >= end:
                    return None
            break

    return (start, end)


class BacktesterEngine(BaseEngine):
    """
    For running CTA strategy backtesting.
    """

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.classes: dict = {}
        self.backtesting_engine: BacktestingEngine = None
        self.thread: Thread | None = None
        self.download_cancel_event: ThreadEvent = ThreadEvent()

        self.datafeed: BaseDatafeed = get_datafeed()
        self.database: BaseDatabase = get_database()

        # Backtesting reuslt
        self.result_df: DataFrame | None = None
        self.result_statistics: dict | None = None

        # Optimization result
        self.result_values: list | None = None

        self._pending_backtest: dict | None = None

    def _set_pending_backtest(self, data: dict) -> None:
        self._pending_backtest = data

    def _pop_pending_backtest(self) -> dict | None:
        data = self._pending_backtest
        self._pending_backtest = None
        return data

    def has_pending_backtest(self) -> bool:
        return self._pending_backtest is not None

    def init_engine(self) -> None:
        """"""
        self.write_log(_("初始化CTA回测引擎"))

        self.backtesting_engine = BacktestingEngine()
        # Redirect log from backtesting engine outside.
        self.backtesting_engine.output = self.write_log

        self.load_strategy_class()
        self.write_log(_("策略文件加载完成"))

        self.init_datafeed()

    def init_datafeed(self) -> None:
        """
        Init datafeed client.
        """
        result: bool = self.datafeed.init(self.write_log)
        if result:
            self.write_log(_("数据服务初始化成功"))

    def is_downloading(self) -> bool:
        """"""
        return self.thread is not None and self.thread.is_alive()

    def stop_downloading(self) -> None:
        """"""
        self.download_cancel_event.set()
        if hasattr(self.datafeed, "cancel"):
            try:
                self.datafeed.cancel()
            except Exception:
                self.write_log(_("数据下载中断失败，触发异常：\n{}").format(traceback.format_exc()))

    def write_log(self, msg: str) -> None:
        """"""
        event: Event = Event(EVENT_BACKTESTER_LOG)
        event.data = msg
        self.event_engine.put(event)

    def load_strategy_class(self) -> None:
        """
        Load strategy class from source code.
        """
        app_path: Path = Path(vnpy_ctastrategy.__file__).parent
        path1: Path = app_path.joinpath("strategies")
        self.load_strategy_class_from_folder(path1, "vnpy_ctastrategy.strategies")

        path2: Path = Path.cwd().joinpath("strategies")
        self.load_strategy_class_from_folder(path2, "strategies")

    def load_strategy_class_from_folder(self, path: Path, module_name: str = "") -> None:
        """
        Load strategy class from certain folder.
        """
        for suffix in ["py", "pyd", "so"]:
            pathname: str = str(path.joinpath(f"*.{suffix}"))
            for filepath in glob(pathname):
                filename: str = Path(filepath).stem
                name: str = f"{module_name}.{filename}"
                self.load_strategy_class_from_module(name)

    def load_strategy_class_from_module(self, module_name: str) -> None:
        """
        Load strategy class from module file.
        """
        try:
            module: ModuleType = importlib.import_module(module_name)

            # 重载模块，确保如果策略文件中有任何修改，能够立即生效。
            importlib.reload(module)

            for name in dir(module):
                value = getattr(module, name)
                if (
                    isinstance(value, type)
                    and issubclass(value, CtaTemplate)
                    and value not in {CtaTemplate, TargetPosTemplate}
                ):
                    self.classes[value.__name__] = value
        except:  # noqa
            msg: str = _("策略文件{}加载失败，触发异常：\n{}").format(
                module_name, traceback.format_exc()
            )
            self.write_log(msg)

    def reload_strategy_class(self) -> None:
        """"""
        self.classes.clear()
        self.load_strategy_class()
        self.write_log(_("策略文件重载刷新完成"))

    def get_strategy_class_names(self) -> list:
        """"""
        return list(self.classes.keys())

    def run_backtesting(
        self,
        class_name: str,
        vt_symbol: str,
        interval: str,
        start: datetime,
        end: datetime,
        rate: float,
        slippage: float,
        size: int,
        pricetick: float,
        capital: int,
        setting: dict
    ) -> None:
        """"""
        self.result_df = None
        self.result_statistics = None

        engine: BacktestingEngine = self.backtesting_engine
        engine.clear_data()

        if interval == Interval.TICK.value:
            mode: BacktestingMode = BacktestingMode.TICK
        else:
            mode = BacktestingMode.BAR

        engine.set_parameters(
            vt_symbol=vt_symbol,
            interval=interval,
            start=start,
            end=end,
            rate=rate,
            slippage=slippage,
            size=size,
            pricetick=pricetick,
            capital=capital,
            mode=mode
        )

        strategy_class: type[CtaTemplate] = self.classes[class_name]
        engine.add_strategy(
            strategy_class,
            setting
        )

        engine.load_data()
        if not engine.history_data:
            self.write_log(_("策略回测失败，历史数据为空"))
            self.thread = None
            return

        try:
            engine.run_backtesting()
        except Exception:
            msg: str = _("策略回测失败，触发异常：\n{}").format(traceback.format_exc())
            self.write_log(msg)

            self.thread = None
            return

        self.result_df = engine.calculate_result()
        self.result_statistics = engine.calculate_statistics(output=False)

        # Clear thread object handler.
        self.thread = None

        # Put backtesting done event
        event: Event = Event(EVENT_BACKTESTER_BACKTESTING_FINISHED)
        self.event_engine.put(event)

    def start_backtesting(
        self,
        class_name: str,
        vt_symbol: str,
        interval: str,
        start: datetime,
        end: datetime,
        rate: float,
        slippage: float,
        size: float,
        pricetick: float,
        capital: float,
        setting: dict
    ) -> bool:
        if self.thread:
            self.write_log(_("已有任务在运行中，请等待完成"))
            return False

        self.write_log("-" * 40)
        self.thread = Thread(
            target=self.run_backtesting,
            args=(
                class_name,
                vt_symbol,
                interval,
                start,
                end,
                rate,
                slippage,
                size,
                pricetick,
                capital,
                setting
            )
        )
        self.thread.start()

        return True

    def ensure_backtesting_data(
        self,
        vt_symbol: str,
        interval: str,
        start: datetime,
        end: datetime,
        pending_backtest: dict
    ) -> bool:
        """
        Ensure required history data exists before backtesting.
        Return True to proceed immediately, False if download started.
        """
        try:
            symbol, exchange = extract_vt_symbol(vt_symbol)
        except ValueError:
            self.write_log(_("{}解析失败，请检查交易所后缀").format(vt_symbol))
            return True

        if interval == Interval.TICK.value:
            overviews: list[TickOverview] = self.database.get_tick_overview()
            missing = _get_missing_tick_range(overviews, symbol, exchange, start, end)
        else:
            overviews: list[BarOverview] = self.database.get_bar_overview()
            missing = _get_missing_history_range(
                overviews,
                symbol=symbol,
                exchange=exchange,
                interval=Interval(interval),
                start=start,
                end=end
            )

        if not missing:
            return True

        missing_start, missing_end = missing
        self.write_log(_("历史数据缺失，开始自动下载区间：{} - {}").format(missing_start, missing_end))
        if self.start_downloading(vt_symbol, interval, missing_start, missing_end):
            self._set_pending_backtest(pending_backtest)
            return False

        self.write_log(_("自动下载启动失败，继续直接回测"))
        return True

    def get_result_df(self) -> DataFrame | None:
        """"""
        return self.result_df

    def get_result_statistics(self) -> dict | None:
        """"""
        return self.result_statistics

    def get_result_values(self) -> list | None:
        """"""
        return self.result_values

    def get_default_setting(self, class_name: str) -> dict:
        """"""
        strategy_class: type[CtaTemplate] = self.classes[class_name]
        setting: dict = strategy_class.get_class_parameters()
        return setting

    def run_optimization(
        self,
        class_name: str,
        vt_symbol: str,
        interval: str,
        start: datetime,
        end: datetime,
        rate: float,
        slippage: float,
        size: int,
        pricetick: float,
        capital: int,
        optimization_setting: OptimizationSetting,
        use_ga: bool,
        max_workers: int | None = None
    ) -> None:
        """"""
        self.result_values = None

        engine: BacktestingEngine = self.backtesting_engine
        engine.clear_data()

        if interval == Interval.TICK.value:
            mode: BacktestingMode = BacktestingMode.TICK
        else:
            mode = BacktestingMode.BAR

        engine.set_parameters(
            vt_symbol=vt_symbol,
            interval=interval,
            start=start,
            end=end,
            rate=rate,
            slippage=slippage,
            size=size,
            pricetick=pricetick,
            capital=capital,
            mode=mode
        )

        strategy_class: type[CtaTemplate] = self.classes[class_name]
        engine.add_strategy(
            strategy_class,
            {}
        )

        # 0则代表不限制
        if max_workers == 0:
            max_workers = None

        if use_ga:
            self.result_values = engine.run_ga_optimization(
                optimization_setting,
                output=False,
                max_workers=max_workers
            )
        else:
            self.result_values = engine.run_bf_optimization(
                optimization_setting,
                output=False,
                max_workers=max_workers
            )

        # Clear thread object handler.
        self.thread = None
        self.write_log(_("多进程参数优化完成"))

        # Put optimization done event
        event: Event = Event(EVENT_BACKTESTER_OPTIMIZATION_FINISHED)
        self.event_engine.put(event)

    def start_optimization(
        self,
        class_name: str,
        vt_symbol: str,
        interval: str,
        start: datetime,
        end: datetime,
        rate: float,
        slippage: float,
        size: float,
        pricetick: float,
        capital: float,
        optimization_setting: OptimizationSetting,
        use_ga: bool,
        max_workers: int
    ) -> bool:
        if self.thread:
            self.write_log(_("已有任务在运行中，请等待完成"))
            return False

        self.write_log("-" * 40)
        self.thread = Thread(
            target=self.run_optimization,
            args=(
                class_name,
                vt_symbol,
                interval,
                start,
                end,
                rate,
                slippage,
                size,
                pricetick,
                capital,
                optimization_setting,
                use_ga,
                max_workers
            )
        )
        self.thread.start()

        return True

    def run_downloading(
        self,
        vt_symbol: str,
        interval: str,
        start: datetime,
        end: datetime
    ) -> None:
        """
        执行下载任务
        """
        self.write_log(_("{}-{}开始下载历史数据").format(vt_symbol, interval))

        try:
            symbol, exchange = extract_vt_symbol(vt_symbol)
        except ValueError:
            self.write_log(_("{}解析失败，请检查交易所后缀").format(vt_symbol))
            self.thread = None
            return

        req: HistoryRequest = HistoryRequest(
            symbol=symbol,
            exchange=exchange,
            interval=Interval(interval),
            start=start,
            end=end
        )

        cancelled: bool = False
        download_range: tuple[datetime, datetime] | None = None
        try:
            if interval == "tick":
                tick_data: list[TickData] = self.datafeed.query_tick_history(req, self.write_log)
                if self.download_cancel_event.is_set():
                    cancelled = True
                if tick_data:
                    self.database.save_tick_data(tick_data)
                    min_dt: datetime = min(td.datetime for td in tick_data)
                    max_dt: datetime = max(td.datetime for td in tick_data)
                    download_range = (min_dt, max_dt)
                if cancelled:
                    pass
                elif not tick_data:
                    self.write_log(_("数据下载失败，无法获取{}的历史数据").format(vt_symbol))
                else:
                    self.write_log(_("{}-{}历史数据下载完成").format(vt_symbol, interval))
            else:
                contract: ContractData | None = self.main_engine.get_contract(vt_symbol)

                # If history data provided in gateway, then query
                if contract and contract.history_data:
                    bar_data: list[BarData] = self.main_engine.query_history(
                        req, contract.gateway_name
                    )
                # Otherwise use RQData to query data
                else:
                    bar_data = self.datafeed.query_bar_history(req, self.write_log)

                if self.download_cancel_event.is_set():
                    cancelled = True
                if bar_data:
                    self.database.save_bar_data(bar_data)
                    min_dt = min(b.datetime for b in bar_data)
                    max_dt = max(b.datetime for b in bar_data)
                    download_range = (min_dt, max_dt)
                if cancelled:
                    pass
                elif not bar_data:
                    self.write_log(_("数据下载失败，无法获取{}的历史数据").format(vt_symbol))
                else:
                    self.write_log(_("{}-{}历史数据下载完成").format(vt_symbol, interval))
        except Exception:
            msg: str = _("数据下载失败，触发异常：\n{}").format(traceback.format_exc())
            self.write_log(msg)

        if cancelled:
            if download_range:
                start_dt, end_dt = download_range
                self.write_log(_("已保存下载区间：{} - {}").format(start_dt, end_dt))
            self.write_log(_("数据下载已中断，已保存已有数据"))

        # Clear thread object handler.
        self.thread = None
        self.event_engine.put(Event(EVENT_BACKTESTER_DOWNLOADING_FINISHED))

    def start_downloading(
        self,
        vt_symbol: str,
        interval: str,
        start: datetime,
        end: datetime
    ) -> bool:
        if self.thread and self.thread.is_alive():
            self.write_log(_("已有任务在运行中，请等待完成"))
            return False
        self.thread = None

        self.write_log("-" * 40)
        self.download_cancel_event.clear()
        if hasattr(self.datafeed, "reset"):
            try:
                self.datafeed.reset()
            except Exception:
                self.write_log(_("数据服务重置失败，触发异常：\n{}").format(traceback.format_exc()))
        self.thread = Thread(
            target=self.run_downloading,
            args=(
                vt_symbol,
                interval,
                start,
                end
            )
        )
        self.thread.start()

        return True

    def get_all_trades(self) -> list:
        """"""
        trades: list = self.backtesting_engine.get_all_trades()
        return trades

    def get_all_orders(self) -> list:
        """"""
        orders: list = self.backtesting_engine.get_all_orders()
        return orders

    def get_all_daily_results(self) -> list:
        """"""
        results: list = self.backtesting_engine.get_all_daily_results()
        return results

    def get_history_data(self) -> list:
        """"""
        history_data: list = self.backtesting_engine.history_data
        return history_data

    def get_strategy_class_file(self, class_name: str) -> str:
        """"""
        strategy_class: type[CtaTemplate] = self.classes[class_name]
        file_path: str = getfile(strategy_class)
        return file_path
