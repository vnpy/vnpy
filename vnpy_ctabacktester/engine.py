import importlib
import traceback
from datetime import datetime
from threading import Thread, Event as ThreadEvent
from pathlib import Path
from inspect import getfile
from glob import glob
from types import ModuleType
from concurrent.futures import ThreadPoolExecutor
from pandas import DataFrame

from vnpy.event import Event, EventEngine
from vnpy.trader.event import EVENT_CONTRACT
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.utility import extract_vt_symbol, load_json, save_json
from vnpy.trader.object import HistoryRequest, TickData, BarData, ContractData
from vnpy.trader.datafeed import BaseDatafeed, get_datafeed
from vnpy.trader.database import (
    BaseDatabase,
    BarOverview,
    TickOverview,
    get_database,
    DB_TZ
)
import vnpy_ctastrategy

from vnpy_ctastrategy import CtaTemplate, TargetPosTemplate
from vnpy_ctastrategy.backtesting import (
    BacktestingEngine,
    OptimizationSetting,
    BacktestingMode,
    load_bar_data
)
from .portfolio_engine import PortfolioBacktestingEngine, PortfolioConfig
from .portfolio_template import PortfolioTemplate
from .locale import _

APP_NAME = "CtaBacktester"

EVENT_BACKTESTER_LOG = "eBacktesterLog"
EVENT_BACKTESTER_BACKTESTING_FINISHED = "eBacktesterBacktestingFinished"
EVENT_BACKTESTER_OPTIMIZATION_FINISHED = "eBacktesterOptimizationFinished"
EVENT_BACKTESTER_DOWNLOADING_FINISHED = "eBacktesterDownloadingFinished"
EVENT_BACKTESTER_PORTFOLIO_FINISHED = "eBacktesterPortfolioFinished"


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


def _to_naive(dt: datetime) -> datetime:
    if dt.tzinfo is None:
        return dt
    return dt.astimezone(DB_TZ).replace(tzinfo=None)


def _get_existing_history_range(
    database: BaseDatabase,
    symbol: str,
    exchange: Exchange,
    interval: Interval,
    start: datetime,
    end: datetime
) -> tuple[datetime, datetime] | None:
    """
    Return existing bar range from database when overview is missing/inaccurate.
    """
    try:
        bars: list[BarData] = database.load_bar_data(
            symbol=symbol,
            exchange=exchange,
            interval=interval,
            start=start,
            end=end
        )
    except Exception:
        return None

    if not bars:
        return None

    min_dt: datetime = min(bar.datetime for bar in bars)
    max_dt: datetime = max(bar.datetime for bar in bars)
    min_dt = _to_naive(min_dt)
    max_dt = _to_naive(max_dt)
    return (min_dt, max_dt)


def _get_existing_tick_range(
    database: BaseDatabase,
    symbol: str,
    exchange: Exchange,
    start: datetime,
    end: datetime
) -> tuple[datetime, datetime] | None:
    """
    Return existing tick range from database when overview is missing/inaccurate.
    """
    try:
        ticks: list[TickData] = database.load_tick_data(
            symbol=symbol,
            exchange=exchange,
            start=start,
            end=end
        )
    except Exception:
        return None

    if not ticks:
        return None

    min_dt: datetime = min(tick.datetime for tick in ticks)
    max_dt: datetime = max(tick.datetime for tick in ticks)
    min_dt = _to_naive(min_dt)
    max_dt = _to_naive(max_dt)
    return (min_dt, max_dt)


def _get_missing_range_with_existing(
    start: datetime,
    end: datetime,
    existing_start: datetime,
    existing_end: datetime
) -> tuple[datetime, datetime] | None:
    start = _to_naive(start)
    end = _to_naive(end)
    existing_start = _to_naive(existing_start)
    existing_end = _to_naive(existing_end)
    if existing_start <= start and existing_end >= end:
        return None
    if existing_end < start or existing_start > end:
        return (start, end)
    if existing_start > start and existing_end >= end:
        return (start, existing_start)
    if existing_start <= start and existing_end < end:
        return (existing_end, end)
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

    channel_profile_filename: str = "cta_backtester_channel_profiles.json"
    contract_profile_filename: str = "cta_backtester_contract_profiles.json"
    default_channel_profile: dict[str, float] = {
        "rate": 0.0,
        "slippage": 0.0,
        "size": 1.0,
        "pricetick": 0.01,
    }

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.classes: dict = {}
        self.portfolio_classes: dict = {}
        self.backtesting_engine: BacktestingEngine = None
        self.thread: Thread | None = None
        self.download_cancel_event: ThreadEvent = ThreadEvent()

        self.datafeed: BaseDatafeed = get_datafeed()
        self.database: BaseDatabase = get_database()

        # Backtesting reuslt
        self.result_df: DataFrame | None = None
        self.result_statistics: dict | None = None
        self.portfolio_result_df: DataFrame | None = None
        self.portfolio_latest_weights: dict[str, float] = {}
        self.portfolio_history: dict[str, list[BarData]] = {}

        # Optimization result
        self.result_values: list | None = None

        self._pending_backtest: dict | None = None
        self._channel_profiles: dict[str, dict[str, float]] = {}
        self._contract_profiles: dict[str, dict[str, float | str]] = {}

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
        self.load_portfolio_strategy_class()
        self.write_log(_("策略文件加载完成"))

        self.init_datafeed()
        self.load_channel_profiles()
        self.load_contract_profiles()
        self.sync_contract_profiles_from_main_engine()
        self.register_event()

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

    def load_portfolio_strategy_class(self) -> None:
        """
        Load portfolio strategy classes.
        """
        self.portfolio_classes.clear()

        app_path: Path = Path(__file__).parent
        path1: Path = app_path.joinpath("portfolio_strategies")
        self.load_portfolio_strategy_class_from_folder(path1, "vnpy_ctabacktester.portfolio_strategies")

        path2: Path = Path.cwd().joinpath("portfolio_strategies")
        self.load_portfolio_strategy_class_from_folder(path2, "portfolio_strategies")

    def load_portfolio_strategy_class_from_folder(self, path: Path, module_name: str = "") -> None:
        """
        Load portfolio strategy classes from certain folder.
        """
        for suffix in ["py", "pyd", "so"]:
            pathname: str = str(path.joinpath(f"*.{suffix}"))
            for filepath in glob(pathname):
                filename: str = Path(filepath).stem
                if filename == "__init__":
                    continue
                name: str = f"{module_name}.{filename}"
                self.load_portfolio_strategy_class_from_module(name)

    def load_portfolio_strategy_class_from_module(self, module_name: str) -> None:
        """
        Load portfolio strategy class from module file.
        """
        try:
            module: ModuleType = importlib.import_module(module_name)
            importlib.reload(module)

            for name in dir(module):
                value = getattr(module, name)
                if (
                    isinstance(value, type)
                    and issubclass(value, PortfolioTemplate)
                    and value is not PortfolioTemplate
                ):
                    self.portfolio_classes[value.__name__] = value
        except:  # noqa
            msg: str = _("组合策略文件{}加载失败，触发异常：\n{}").format(
                module_name, traceback.format_exc()
            )
            self.write_log(msg)

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
        self.load_portfolio_strategy_class()
        self.write_log(_("策略文件重载刷新完成"))

    def get_strategy_class_names(self) -> list:
        """"""
        return list(self.classes.keys())

    def get_portfolio_strategy_class_names(self) -> list:
        """
        Return portfolio strategy class names.
        """
        names: list[str] = list(self.portfolio_classes.keys())
        names.sort()
        return names

    def get_portfolio_default_setting(self, class_name: str) -> dict:
        """
        Return default parameter settings of portfolio strategy class.
        """
        strategy_class: type[PortfolioTemplate] = self.portfolio_classes[class_name]
        return strategy_class.get_class_parameters()

    def load_channel_profiles(self) -> None:
        """
        Load per-gateway default trading cost profile from json.
        """
        raw: dict = load_json(self.channel_profile_filename)
        profiles: dict[str, dict[str, float]] = {}

        if isinstance(raw, dict):
            for gateway_name, values in raw.items():
                if not isinstance(values, dict):
                    continue
                profiles[gateway_name] = {
                    "rate": float(values.get("rate", self.default_channel_profile["rate"])),
                    "slippage": float(values.get("slippage", self.default_channel_profile["slippage"])),
                    "size": float(values.get("size", self.default_channel_profile["size"])),
                    "pricetick": float(values.get("pricetick", self.default_channel_profile["pricetick"])),
                }

        self._channel_profiles = profiles

    def load_contract_profiles(self) -> None:
        """
        Load per-contract trading profile from json.
        """
        raw: dict = load_json(self.contract_profile_filename)
        profiles: dict[str, dict[str, float | str]] = {}
        if isinstance(raw, dict):
            for vt_symbol, values in raw.items():
                if not isinstance(vt_symbol, str):
                    continue
                if not isinstance(values, dict):
                    continue
                profiles[vt_symbol] = {
                    "rate": float(values.get("rate", self.default_channel_profile["rate"])),
                    "slippage": float(values.get("slippage", self.default_channel_profile["slippage"])),
                    "size": float(values.get("size", self.default_channel_profile["size"])),
                    "pricetick": float(values.get("pricetick", self.default_channel_profile["pricetick"])),
                    "min_volume": float(values.get("min_volume", 1)),
                    "gateway_name": str(values.get("gateway_name", "")),
                }
        self._contract_profiles = profiles

    def register_event(self) -> None:
        """
        Register event handlers for runtime contract sync.
        """
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)

    def process_contract_event(self, event: Event) -> None:
        """
        Keep contract profile cache up to date whenever gateway pushes contract.
        """
        contract: ContractData = event.data
        self.upsert_contract_profile(contract)

    def upsert_contract_profile(self, contract: ContractData, persist: bool = True) -> None:
        """
        Merge contract metadata into per-symbol profile cache.
        """
        existing: dict[str, float | str] = self._contract_profiles.get(contract.vt_symbol, {})
        channel_profile: dict[str, float] = self.get_channel_profile(contract.gateway_name)
        rate_value: float | str | None = existing.get("rate")
        slippage_value: float | str | None = existing.get("slippage")
        size_value: float | str | None = existing.get("size")
        pricetick_value: float | str | None = existing.get("pricetick")
        min_volume_value: float | str | None = existing.get("min_volume")
        profile: dict[str, float | str] = {
            "rate": float(channel_profile["rate"]) if rate_value is None else float(rate_value),
            "slippage": float(channel_profile["slippage"]) if slippage_value is None else float(slippage_value),
            "size": float(channel_profile["size"]) if size_value is None else float(size_value),
            "pricetick": float(channel_profile["pricetick"]) if pricetick_value is None else float(pricetick_value),
            "min_volume": 1.0 if min_volume_value is None else float(min_volume_value),
            "gateway_name": contract.gateway_name,
        }

        if contract.size and contract.size > 0:
            profile["size"] = float(contract.size)
        if contract.pricetick and contract.pricetick > 0:
            profile["pricetick"] = float(contract.pricetick)
        if contract.min_volume and contract.min_volume > 0:
            profile["min_volume"] = float(contract.min_volume)

        self._contract_profiles[contract.vt_symbol] = profile
        if persist:
            save_json(self.contract_profile_filename, self._contract_profiles)

    def sync_contract_profiles_from_main_engine(self) -> None:
        """
        Bootstrap contract profile cache from currently loaded contracts.
        """
        contracts: list[ContractData] = self.main_engine.get_all_contracts()
        if not contracts:
            return

        for contract in contracts:
            self.upsert_contract_profile(contract, persist=False)
        save_json(self.contract_profile_filename, self._contract_profiles)

    def get_channel_profile(self, gateway_name: str) -> dict[str, float]:
        """
        Get channel profile with global fallback defaults.
        """
        profile: dict[str, float] = dict(self.default_channel_profile)
        profile.update(self._channel_profiles.get(gateway_name, {}))
        return profile

    def set_channel_profile(self, gateway_name: str, profile: dict[str, float]) -> None:
        """
        Persist channel profile for gateway.
        """
        self._channel_profiles[gateway_name] = {
            "rate": float(profile.get("rate", self.default_channel_profile["rate"])),
            "slippage": float(profile.get("slippage", self.default_channel_profile["slippage"])),
            "size": float(profile.get("size", self.default_channel_profile["size"])),
            "pricetick": float(profile.get("pricetick", self.default_channel_profile["pricetick"])),
        }
        save_json(self.channel_profile_filename, self._channel_profiles)

    def get_available_gateways(self) -> list[str]:
        """
        Return gateway names for channel selection.
        """
        gateways: list[str] = self.main_engine.get_all_gateway_names()
        gateways = sorted(set(gateways))
        return gateways

    def get_contract_candidates(self, gateway_name: str = "", keyword: str = "") -> list[str]:
        """
        Return vt_symbol candidates filtered by gateway and keyword.
        """
        keyword = keyword.strip().lower()
        contracts: list[ContractData] = self.main_engine.get_all_contracts()
        vt_symbols: list[str] = []

        for contract in contracts:
            if gateway_name and contract.gateway_name != gateway_name:
                continue

            vt_symbol: str = contract.vt_symbol
            if keyword:
                name: str = (contract.name or "").lower()
                if keyword not in vt_symbol.lower() and keyword not in name:
                    continue
            vt_symbols.append(vt_symbol)

        vt_symbols.sort()
        return vt_symbols

    def resolve_contract_profile(self, vt_symbol: str, gateway_name: str = "") -> dict[str, float | str]:
        """
        Resolve backtesting profile with fallback chain:
        ContractData(size/pricetick/min_volume) -> contract profile -> channel profile(rate/slippage) -> defaults.
        """
        profile: dict[str, float | str] = dict(self.default_channel_profile)
        profile["min_volume"] = 1.0
        profile["source"] = "default"

        channel_profile: dict[str, float] = self.get_channel_profile(gateway_name)
        profile["rate"] = channel_profile["rate"]
        profile["slippage"] = channel_profile["slippage"]

        contract_profile: dict[str, float | str] | None = self._contract_profiles.get(vt_symbol)
        if contract_profile:
            rate_value: float | str | None = contract_profile.get("rate")
            slippage_value: float | str | None = contract_profile.get("slippage")
            size_value: float | str | None = contract_profile.get("size")
            pricetick_value: float | str | None = contract_profile.get("pricetick")
            min_volume_value: float | str | None = contract_profile.get("min_volume")
            if rate_value is not None:
                profile["rate"] = float(rate_value)
            if slippage_value is not None:
                profile["slippage"] = float(slippage_value)
            if size_value is not None:
                profile["size"] = float(size_value)
            if pricetick_value is not None:
                profile["pricetick"] = float(pricetick_value)
            if min_volume_value is not None:
                profile["min_volume"] = float(min_volume_value)
            profile["source"] = "profile"

        contract: ContractData | None = self.main_engine.get_contract(vt_symbol)
        if contract:
            if contract.size and contract.size > 0:
                profile["size"] = float(contract.size)
            if contract.pricetick and contract.pricetick > 0:
                profile["pricetick"] = float(contract.pricetick)
            if contract.min_volume and contract.min_volume > 0:
                profile["min_volume"] = float(contract.min_volume)
            profile["source"] = "contract+channel"
        elif profile["source"] != "profile" and gateway_name and gateway_name in self._channel_profiles:
            profile["source"] = "channel"

        return profile

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

        start = _to_naive(start)
        end = _to_naive(end)

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

        if interval == Interval.TICK.value:
            existing = _get_existing_tick_range(
                self.database, symbol, exchange, start, end
            )
        else:
            existing = _get_existing_history_range(
                self.database,
                symbol=symbol,
                exchange=exchange,
                interval=Interval(interval),
                start=start,
                end=end
            )

        if existing:
            missing = _get_missing_range_with_existing(start, end, *existing)
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

    def run_portfolio_backtesting(
        self,
        vt_symbols: list[str],
        interval: str,
        start: datetime,
        end: datetime,
        capital: float,
        top_n: int,
        class_name: str,
        setting: dict,
        max_workers: int = 1
    ) -> None:
        """
        Run portfolio backtesting by score ranking and normalized allocation.
        """
        self.portfolio_result_df = None
        self.portfolio_latest_weights = {}
        self.portfolio_history = {}

        if not vt_symbols:
            self.write_log(_("组合回测失败，标的列表为空"))
            self.thread = None
            return

        try:
            bar_interval: Interval = Interval(interval)
        except ValueError:
            self.write_log(_("组合回测失败，K线周期不支持：{}").format(interval))
            self.thread = None
            return

        # Load bar data by symbol
        def load_symbol_history(vt_symbol: str) -> tuple[str, list[BarData]]:
            try:
                symbol, exchange = extract_vt_symbol(vt_symbol)
            except ValueError:
                return (vt_symbol, [])

            bars: list[BarData] = load_bar_data(symbol, exchange, bar_interval, start, end)
            return (vt_symbol, bars)

        tasks: list[tuple[str, list[BarData]]] = []
        if max_workers and max_workers > 1:
            workers: int = min(max_workers, len(vt_symbols))
            with ThreadPoolExecutor(max_workers=workers) as executor:
                tasks = list(executor.map(load_symbol_history, vt_symbols))
        else:
            tasks = [load_symbol_history(vt_symbol) for vt_symbol in vt_symbols]

        for vt_symbol, bars in tasks:
            if bars:
                self.portfolio_history[vt_symbol] = bars

        if not self.portfolio_history:
            self.write_log(_("组合回测失败，历史数据为空"))
            self.thread = None
            return

        close_map: dict[datetime, dict[str, float]] = {}
        bars_map: dict[datetime, dict[str, BarData]] = {}
        for vt_symbol, bars in self.portfolio_history.items():
            for bar in bars:
                symbol_prices: dict[str, float] = close_map.setdefault(bar.datetime, {})
                symbol_prices[vt_symbol] = bar.close_price
                symbol_bars: dict[str, BarData] = bars_map.setdefault(bar.datetime, {})
                symbol_bars[vt_symbol] = bar

        dts: list[datetime] = sorted(close_map.keys())
        if len(dts) < 2:
            self.write_log(_("组合回测失败，历史数据不足"))
            self.thread = None
            return

        strategy_class: type[PortfolioTemplate] | None = self.portfolio_classes.get(class_name)
        if not strategy_class:
            self.write_log(_("组合回测失败，找不到组合策略：{}").format(class_name))
            self.thread = None
            return

        strategy: PortfolioTemplate = strategy_class(
            self,
            class_name,
            list(self.portfolio_history.keys()),
            setting
        )
        strategy.on_init()
        strategy.inited = True

        alloc_engine: PortfolioBacktestingEngine = PortfolioBacktestingEngine(
            PortfolioConfig(top_n=top_n, long_only=True)
        )

        balance: float = capital
        prev_weights: dict[str, float] = {}
        records: list[dict] = []

        profile_map: dict[str, dict[str, float | str]] = {}
        for vt_symbol in self.portfolio_history:
            contract: ContractData | None = self.main_engine.get_contract(vt_symbol)
            gateway_name: str = contract.gateway_name if contract else ""
            try:
                profile_map[vt_symbol] = self.resolve_contract_profile(vt_symbol, gateway_name)
            except Exception:
                profile_map[vt_symbol] = {
                    "rate": 0.0,
                    "slippage": 0.0,
                    "size": 1.0,
                    "pricetick": 0.0,
                    "min_volume": 1.0,
                    "source": "default",
                }

        for i in range(1, len(dts)):
            prev_dt: datetime = dts[i - 1]
            dt: datetime = dts[i]

            prev_prices: dict[str, float] = close_map.get(prev_dt, {})
            curr_prices: dict[str, float] = close_map.get(dt, {})

            bars_prev: dict[str, BarData] = bars_map.get(prev_dt, {})

            scores: dict[str, float] = {}
            try:
                scores = strategy.on_bars(bars_prev) or {}
            except Exception:
                self.write_log(_("组合策略评分失败：\n{}").format(traceback.format_exc()))
                self.thread = None
                return

            target_weights: dict[str, float] = alloc_engine.generate_target_weights(scores)
            if target_weights:
                self.portfolio_latest_weights = target_weights

            # Estimate rebalance transaction cost from weight turnover
            turnover: float = 0
            commission: float = 0
            slippage_cost: float = 0
            all_symbols: set[str] = set(prev_weights.keys()) | set(target_weights.keys())
            for vt_symbol in all_symbols:
                old_weight: float = prev_weights.get(vt_symbol, 0)
                new_weight: float = target_weights.get(vt_symbol, 0)
                delta_weight: float = abs(new_weight - old_weight)
                if delta_weight <= 0:
                    continue

                symbol_turnover: float = balance * delta_weight
                profile: dict[str, float | str] = profile_map.get(vt_symbol, {})
                rate: float = float(profile.get("rate", 0) or 0)
                slippage: float = float(profile.get("slippage", 0) or 0)

                turnover += symbol_turnover
                commission += symbol_turnover * rate
                prev_price: float = prev_prices.get(vt_symbol, 0)
                if prev_price > 0:
                    slippage_cost += symbol_turnover / prev_price * slippage

            portfolio_return: float = 0
            for vt_symbol, weight in target_weights.items():
                prev_price: float = prev_prices.get(vt_symbol, 0)
                curr_price: float = curr_prices.get(vt_symbol, 0)
                if prev_price <= 0 or curr_price <= 0:
                    continue
                symbol_return: float = curr_price / prev_price - 1
                portfolio_return += weight * symbol_return

            trading_pnl: float = balance * portfolio_return
            net_pnl: float = trading_pnl - commission - slippage_cost
            balance += net_pnl

            records.append({
                "date": dt.date(),
                "turnover": turnover,
                "commission": commission,
                "slippage": slippage_cost,
                "trading_pnl": trading_pnl,
                "net_pnl": net_pnl,
            })
            prev_weights = target_weights

        if not records:
            self.write_log(_("组合回测失败，无有效收益记录"))
            self.thread = None
            return

        df: DataFrame = DataFrame(records)
        df = df.groupby("date", as_index=True).sum(numeric_only=True)
        df["balance"] = df["net_pnl"].cumsum() + capital
        df["highlevel"] = df["balance"].cummax()
        df["drawdown"] = df["balance"] - df["highlevel"]
        df["ddpercent"] = (df["balance"] / df["highlevel"] - 1) * 100
        self.portfolio_result_df = df

        self.thread = None
        self.write_log(_("组合回测完成"))
        self.event_engine.put(Event(EVENT_BACKTESTER_PORTFOLIO_FINISHED))

    def start_portfolio_backtesting(
        self,
        vt_symbols: list[str],
        interval: str,
        start: datetime,
        end: datetime,
        capital: float,
        top_n: int,
        class_name: str,
        setting: dict,
        max_workers: int = 1
    ) -> bool:
        """
        Start async portfolio backtesting task.
        """
        if self.thread:
            self.write_log(_("已有任务在运行中，请等待完成"))
            return False

        self.write_log("-" * 40)
        self.thread = Thread(
            target=self.run_portfolio_backtesting,
            args=(vt_symbols, interval, start, end, capital, top_n, class_name, setting, max_workers)
        )
        self.thread.start()
        return True

    def get_portfolio_result_df(self) -> DataFrame | None:
        return self.portfolio_result_df

    def get_portfolio_latest_weights(self) -> dict[str, float]:
        return self.portfolio_latest_weights

    def get_portfolio_history(self, vt_symbol: str) -> list[BarData]:
        return self.portfolio_history.get(vt_symbol, [])

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
