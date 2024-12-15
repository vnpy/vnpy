"""
General utility functions.
"""

import json
import logging
import sys
from datetime import datetime, time
from pathlib import Path
from typing import Callable, Dict, Tuple, Union, Optional
from decimal import Decimal
from math import floor, ceil

import numpy as np
import talib

from .object import BarData, TickData
from .constant import Exchange, Interval
from .locale import _

if sys.version_info >= (3, 9):
    from zoneinfo import ZoneInfo, available_timezones              # noqa
else:
    from backports.zoneinfo import ZoneInfo, available_timezones    # noqa


log_formatter: logging.Formatter = logging.Formatter("[%(asctime)s] %(message)s")


def extract_vt_symbol(vt_symbol: str) -> Tuple[str, Exchange]:
    """
    :return: (symbol, exchange)
    """
    symbol, exchange_str = vt_symbol.rsplit(".", 1)
    return symbol, Exchange(exchange_str)


def generate_vt_symbol(symbol: str, exchange: Exchange) -> str:
    """
    return vt_symbol
    """
    return f"{symbol}.{exchange.value}"


def _get_trader_dir(temp_name: str) -> Tuple[Path, Path]:
    """
    Get path where trader is running in.
    """
    cwd: Path = Path.cwd()
    temp_path: Path = cwd.joinpath(temp_name)

    # If .vntrader folder exists in current working directory,
    # then use it as trader running path.
    if temp_path.exists():
        return cwd, temp_path

    # Otherwise use home path of system.
    home_path: Path = Path.home()
    temp_path: Path = home_path.joinpath(temp_name)

    # Create .vntrader folder under home path if not exist.
    if not temp_path.exists():
        temp_path.mkdir()

    return home_path, temp_path


TRADER_DIR, TEMP_DIR = _get_trader_dir(".vntrader")
sys.path.append(str(TRADER_DIR))


def get_file_path(filename: str) -> Path:
    """
    Get path for temp file with filename.
    """
    return TEMP_DIR.joinpath(filename)


def get_folder_path(folder_name: str) -> Path:
    """
    Get path for temp folder with folder name.
    """
    folder_path: Path = TEMP_DIR.joinpath(folder_name)
    if not folder_path.exists():
        folder_path.mkdir()
    return folder_path


def get_icon_path(filepath: str, ico_name: str) -> str:
    """
    Get path for icon file with ico name.
    """
    ui_path: Path = Path(filepath).parent
    icon_path: Path = ui_path.joinpath("ico", ico_name)
    return str(icon_path)


def load_json(filename: str) -> dict:
    """
    Load data from json file in temp path.
    """
    filepath: Path = get_file_path(filename)

    if filepath.exists():
        with open(filepath, mode="r", encoding="UTF-8") as f:
            data: dict = json.load(f)
        return data
    else:
        save_json(filename, {})
        return {}


def save_json(filename: str, data: dict) -> None:
    """
    Save data into json file in temp path.
    """
    filepath: Path = get_file_path(filename)
    with open(filepath, mode="w+", encoding="UTF-8") as f:
        json.dump(
            data,
            f,
            indent=4,
            ensure_ascii=False
        )


def round_to(value: float, target: float) -> float:
    """
    Round price to price tick value.
    """
    value: Decimal = Decimal(str(value))
    target: Decimal = Decimal(str(target))
    rounded: float = float(int(round(value / target)) * target)
    return rounded


def floor_to(value: float, target: float) -> float:
    """
    Similar to math.floor function, but to target float number.
    """
    value: Decimal = Decimal(str(value))
    target: Decimal = Decimal(str(target))
    result: float = float(int(floor(value / target)) * target)
    return result


def ceil_to(value: float, target: float) -> float:
    """
    Similar to math.ceil function, but to target float number.
    """
    value: Decimal = Decimal(str(value))
    target: Decimal = Decimal(str(target))
    result: float = float(int(ceil(value / target)) * target)
    return result


def get_digits(value: float) -> int:
    """
    Get number of digits after decimal point.
    """
    value_str: str = str(value)

    if "e-" in value_str:
        _, buf = value_str.split("e-")
        return int(buf)
    elif "." in value_str:
        _, buf = value_str.split(".")
        return len(buf)
    else:
        return 0


class BarGenerator:
    """
    For:
    1. generating 1 minute bar data from tick data
    2. generating x minute bar/x hour bar data from 1 minute data
    Notice:
    1. for x minute bar, x must be able to divide 60: 2, 3, 5, 6, 10, 15, 20, 30
    2. for x hour bar, x can be any number
    """

    def __init__(
        self,
        on_bar: Callable,
        window: int = 0,
        on_window_bar: Callable = None,
        interval: Interval = Interval.MINUTE,
        daily_end: time = None
    ) -> None:
        """Constructor"""
        self.bar: BarData = None
        self.on_bar: Callable = on_bar

        self.interval: Interval = interval
        self.interval_count: int = 0

        self.hour_bar: BarData = None
        self.daily_bar: BarData = None

        self.window: int = window
        self.window_bar: BarData = None
        self.on_window_bar: Callable = on_window_bar

        self.last_tick: TickData = None

        self.daily_end: time = daily_end
        if self.interval == Interval.DAILY and not self.daily_end:
            raise RuntimeError(_("合成日K线必须传入每日收盘时间"))

    def update_tick(self, tick: TickData) -> None:
        """
        Update new tick data into generator.
        """
        new_minute: bool = False

        # Filter tick data with 0 last price
        if not tick.last_price:
            return

        if not self.bar:
            new_minute = True
        elif (
            (self.bar.datetime.minute != tick.datetime.minute)
            or (self.bar.datetime.hour != tick.datetime.hour)
        ):
            self.bar.datetime = self.bar.datetime.replace(
                second=0, microsecond=0
            )
            self.on_bar(self.bar)

            new_minute = True

        if new_minute:
            self.bar = BarData(
                symbol=tick.symbol,
                exchange=tick.exchange,
                interval=Interval.MINUTE,
                datetime=tick.datetime,
                gateway_name=tick.gateway_name,
                open_price=tick.last_price,
                high_price=tick.last_price,
                low_price=tick.last_price,
                close_price=tick.last_price,
                open_interest=tick.open_interest
            )
        else:
            self.bar.high_price = max(self.bar.high_price, tick.last_price)
            if tick.high_price > self.last_tick.high_price:
                self.bar.high_price = max(self.bar.high_price, tick.high_price)

            self.bar.low_price = min(self.bar.low_price, tick.last_price)
            if tick.low_price < self.last_tick.low_price:
                self.bar.low_price = min(self.bar.low_price, tick.low_price)

            self.bar.close_price = tick.last_price
            self.bar.open_interest = tick.open_interest
            self.bar.datetime = tick.datetime

        if self.last_tick:
            volume_change: float = tick.volume - self.last_tick.volume
            self.bar.volume += max(volume_change, 0)

            turnover_change: float = tick.turnover - self.last_tick.turnover
            self.bar.turnover += max(turnover_change, 0)

        self.last_tick = tick

    def update_bar(self, bar: BarData) -> None:
        """
        Update 1 minute bar into generator
        """
        if self.interval == Interval.MINUTE:
            self.update_bar_minute_window(bar)
        elif self.interval == Interval.HOUR:
            self.update_bar_hour_window(bar)
        else:
            self.update_bar_daily_window(bar)

    def update_bar_minute_window(self, bar: BarData) -> None:
        """"""
        # If not inited, create window bar object
        if not self.window_bar:
            dt: datetime = bar.datetime.replace(second=0, microsecond=0)
            self.window_bar = BarData(
                symbol=bar.symbol,
                exchange=bar.exchange,
                datetime=dt,
                gateway_name=bar.gateway_name,
                open_price=bar.open_price,
                high_price=bar.high_price,
                low_price=bar.low_price
            )
        # Otherwise, update high/low price into window bar
        else:
            self.window_bar.high_price = max(
                self.window_bar.high_price,
                bar.high_price
            )
            self.window_bar.low_price = min(
                self.window_bar.low_price,
                bar.low_price
            )

        # Update close price/volume/turnover into window bar
        self.window_bar.close_price = bar.close_price
        self.window_bar.volume += bar.volume
        self.window_bar.turnover += bar.turnover
        self.window_bar.open_interest = bar.open_interest

        # Check if window bar completed
        if not (bar.datetime.minute + 1) % self.window:
            self.on_window_bar(self.window_bar)
            self.window_bar = None

    def update_bar_hour_window(self, bar: BarData) -> None:
        """"""
        # If not inited, create window bar object
        if not self.hour_bar:
            dt: datetime = bar.datetime.replace(minute=0, second=0, microsecond=0)
            self.hour_bar = BarData(
                symbol=bar.symbol,
                exchange=bar.exchange,
                datetime=dt,
                gateway_name=bar.gateway_name,
                open_price=bar.open_price,
                high_price=bar.high_price,
                low_price=bar.low_price,
                close_price=bar.close_price,
                volume=bar.volume,
                turnover=bar.turnover,
                open_interest=bar.open_interest
            )
            return

        finished_bar: BarData = None

        # If minute is 59, update minute bar into window bar and push
        if bar.datetime.minute == 59:
            self.hour_bar.high_price = max(
                self.hour_bar.high_price,
                bar.high_price
            )
            self.hour_bar.low_price = min(
                self.hour_bar.low_price,
                bar.low_price
            )

            self.hour_bar.close_price = bar.close_price
            self.hour_bar.volume += bar.volume
            self.hour_bar.turnover += bar.turnover
            self.hour_bar.open_interest = bar.open_interest

            finished_bar = self.hour_bar
            self.hour_bar = None

        # If minute bar of new hour, then push existing window bar
        elif bar.datetime.hour != self.hour_bar.datetime.hour:
            finished_bar = self.hour_bar

            dt: datetime = bar.datetime.replace(minute=0, second=0, microsecond=0)
            self.hour_bar = BarData(
                symbol=bar.symbol,
                exchange=bar.exchange,
                datetime=dt,
                gateway_name=bar.gateway_name,
                open_price=bar.open_price,
                high_price=bar.high_price,
                low_price=bar.low_price,
                close_price=bar.close_price,
                volume=bar.volume,
                turnover=bar.turnover,
                open_interest=bar.open_interest
            )
        # Otherwise only update minute bar
        else:
            self.hour_bar.high_price = max(
                self.hour_bar.high_price,
                bar.high_price
            )
            self.hour_bar.low_price = min(
                self.hour_bar.low_price,
                bar.low_price
            )

            self.hour_bar.close_price = bar.close_price
            self.hour_bar.volume += bar.volume
            self.hour_bar.turnover += bar.turnover
            self.hour_bar.open_interest = bar.open_interest

        # Push finished window bar
        if finished_bar:
            self.on_hour_bar(finished_bar)

    def on_hour_bar(self, bar: BarData) -> None:
        """"""
        if self.window == 1:
            self.on_window_bar(bar)
        else:
            if not self.window_bar:
                self.window_bar = BarData(
                    symbol=bar.symbol,
                    exchange=bar.exchange,
                    datetime=bar.datetime,
                    gateway_name=bar.gateway_name,
                    open_price=bar.open_price,
                    high_price=bar.high_price,
                    low_price=bar.low_price
                )
            else:
                self.window_bar.high_price = max(
                    self.window_bar.high_price,
                    bar.high_price
                )
                self.window_bar.low_price = min(
                    self.window_bar.low_price,
                    bar.low_price
                )

            self.window_bar.close_price = bar.close_price
            self.window_bar.volume += bar.volume
            self.window_bar.turnover += bar.turnover
            self.window_bar.open_interest = bar.open_interest

            self.interval_count += 1
            if not self.interval_count % self.window:
                self.interval_count = 0
                self.on_window_bar(self.window_bar)
                self.window_bar = None

    def update_bar_daily_window(self, bar: BarData) -> None:
        """"""
        # If not inited, create daily bar object
        if not self.daily_bar:
            self.daily_bar = BarData(
                symbol=bar.symbol,
                exchange=bar.exchange,
                datetime=bar.datetime,
                gateway_name=bar.gateway_name,
                open_price=bar.open_price,
                high_price=bar.high_price,
                low_price=bar.low_price
            )
        # Otherwise, update high/low price into daily bar
        else:
            self.daily_bar.high_price = max(
                self.daily_bar.high_price,
                bar.high_price
            )
            self.daily_bar.low_price = min(
                self.daily_bar.low_price,
                bar.low_price
            )

        # Update close price/volume/turnover into daily bar
        self.daily_bar.close_price = bar.close_price
        self.daily_bar.volume += bar.volume
        self.daily_bar.turnover += bar.turnover
        self.daily_bar.open_interest = bar.open_interest

        # Check if daily bar completed
        if bar.datetime.time() == self.daily_end:
            self.daily_bar.datetime = bar.datetime.replace(
                hour=0,
                minute=0,
                second=0,
                microsecond=0
            )
            self.on_window_bar(self.daily_bar)

            self.daily_bar = None

    def generate(self) -> Optional[BarData]:
        """
        Generate the bar data and call callback immediately.
        """
        bar: BarData = self.bar

        if self.bar:
            bar.datetime = bar.datetime.replace(second=0, microsecond=0)
            self.on_bar(bar)

        self.bar = None
        return bar


class ArrayManager(object):
    """
    For:
    1. time series container of bar data
    2. calculating technical indicator value
    """

    def __init__(self, size: int = 100) -> None:
        """Constructor"""
        self.count: int = 0
        self.size: int = size
        self.inited: bool = False

        self.open_array: np.ndarray = np.zeros(size)
        self.high_array: np.ndarray = np.zeros(size)
        self.low_array: np.ndarray = np.zeros(size)
        self.close_array: np.ndarray = np.zeros(size)
        self.volume_array: np.ndarray = np.zeros(size)
        self.turnover_array: np.ndarray = np.zeros(size)
        self.open_interest_array: np.ndarray = np.zeros(size)

    def update_bar(self, bar: BarData) -> None:
        """
        Update new bar data into array manager.
        """
        self.count += 1
        if not self.inited and self.count >= self.size:
            self.inited = True

        self.open_array[:-1] = self.open_array[1:]
        self.high_array[:-1] = self.high_array[1:]
        self.low_array[:-1] = self.low_array[1:]
        self.close_array[:-1] = self.close_array[1:]
        self.volume_array[:-1] = self.volume_array[1:]
        self.turnover_array[:-1] = self.turnover_array[1:]
        self.open_interest_array[:-1] = self.open_interest_array[1:]

        self.open_array[-1] = bar.open_price
        self.high_array[-1] = bar.high_price
        self.low_array[-1] = bar.low_price
        self.close_array[-1] = bar.close_price
        self.volume_array[-1] = bar.volume
        self.turnover_array[-1] = bar.turnover
        self.open_interest_array[-1] = bar.open_interest

    @property
    def open(self) -> np.ndarray:
        """
        Get open price time series.
        """
        return self.open_array

    @property
    def high(self) -> np.ndarray:
        """
        Get high price time series.
        """
        return self.high_array

    @property
    def low(self) -> np.ndarray:
        """
        Get low price time series.
        """
        return self.low_array

    @property
    def close(self) -> np.ndarray:
        """
        Get close price time series.
        """
        return self.close_array

    @property
    def volume(self) -> np.ndarray:
        """
        Get trading volume time series.
        """
        return self.volume_array

    @property
    def turnover(self) -> np.ndarray:
        """
        Get trading turnover time series.
        """
        return self.turnover_array

    @property
    def open_interest(self) -> np.ndarray:
        """
        Get trading volume time series.
        """
        return self.open_interest_array

    def sma(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        Simple moving average.
        """
        result: np.ndarray = talib.SMA(self.close, n)
        if array:
            return result
        return result[-1]

    def ema(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        Exponential moving average.
        """
        result: np.ndarray = talib.EMA(self.close, n)
        if array:
            return result
        return result[-1]

    def kama(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        KAMA.
        """
        result: np.ndarray = talib.KAMA(self.close, n)
        if array:
            return result
        return result[-1]

    def wma(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        WMA.
        """
        result: np.ndarray = talib.WMA(self.close, n)
        if array:
            return result
        return result[-1]

    def apo(
        self,
        fast_period: int,
        slow_period: int,
        matype: int = 0,
        array: bool = False
    ) -> Union[float, np.ndarray]:
        """
        APO.
        """
        result: np.ndarray = talib.APO(self.close, fast_period, slow_period, matype)
        if array:
            return result
        return result[-1]

    def cmo(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        CMO.
        """
        result: np.ndarray = talib.CMO(self.close, n)
        if array:
            return result
        return result[-1]

    def mom(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        MOM.
        """
        result: np.ndarray = talib.MOM(self.close, n)
        if array:
            return result
        return result[-1]

    def ppo(
        self,
        fast_period: int,
        slow_period: int,
        matype: int = 0,
        array: bool = False
    ) -> Union[float, np.ndarray]:
        """
        PPO.
        """
        result: np.ndarray = talib.PPO(self.close, fast_period, slow_period, matype)
        if array:
            return result
        return result[-1]

    def roc(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        ROC.
        """
        result: np.ndarray = talib.ROC(self.close, n)
        if array:
            return result
        return result[-1]

    def rocr(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        ROCR.
        """
        result: np.ndarray = talib.ROCR(self.close, n)
        if array:
            return result
        return result[-1]

    def rocp(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        ROCP.
        """
        result: np.ndarray = talib.ROCP(self.close, n)
        if array:
            return result
        return result[-1]

    def rocr_100(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        ROCR100.
        """
        result: np.ndarray = talib.ROCR100(self.close, n)
        if array:
            return result
        return result[-1]

    def trix(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        TRIX.
        """
        result: np.ndarray = talib.TRIX(self.close, n)
        if array:
            return result
        return result[-1]

    def std(self, n: int, nbdev: int = 1, array: bool = False) -> Union[float, np.ndarray]:
        """
        Standard deviation.
        """
        result: np.ndarray = talib.STDDEV(self.close, n, nbdev)
        if array:
            return result
        return result[-1]

    def obv(self, array: bool = False) -> Union[float, np.ndarray]:
        """
        OBV.
        """
        result: np.ndarray = talib.OBV(self.close, self.volume)
        if array:
            return result
        return result[-1]

    def cci(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        Commodity Channel Index (CCI).
        """
        result: np.ndarray = talib.CCI(self.high, self.low, self.close, n)
        if array:
            return result
        return result[-1]

    def atr(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        Average True Range (ATR).
        """
        result: np.ndarray = talib.ATR(self.high, self.low, self.close, n)
        if array:
            return result
        return result[-1]

    def natr(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        NATR.
        """
        result: np.ndarray = talib.NATR(self.high, self.low, self.close, n)
        if array:
            return result
        return result[-1]

    def rsi(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        Relative Strenght Index (RSI).
        """
        result: np.ndarray = talib.RSI(self.close, n)
        if array:
            return result
        return result[-1]

    def macd(
        self,
        fast_period: int,
        slow_period: int,
        signal_period: int,
        array: bool = False
    ) -> Union[
        Tuple[np.ndarray, np.ndarray, np.ndarray],
        Tuple[float, float, float]
    ]:
        """
        MACD.
        """
        macd, signal, hist = talib.MACD(
            self.close, fast_period, slow_period, signal_period
        )
        if array:
            return macd, signal, hist
        return macd[-1], signal[-1], hist[-1]

    def adx(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        ADX.
        """
        result: np.ndarray = talib.ADX(self.high, self.low, self.close, n)
        if array:
            return result
        return result[-1]

    def adxr(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        ADXR.
        """
        result: np.ndarray = talib.ADXR(self.high, self.low, self.close, n)
        if array:
            return result
        return result[-1]

    def dx(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        DX.
        """
        result: np.ndarray = talib.DX(self.high, self.low, self.close, n)
        if array:
            return result
        return result[-1]

    def minus_di(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        MINUS_DI.
        """
        result: np.ndarray = talib.MINUS_DI(self.high, self.low, self.close, n)
        if array:
            return result
        return result[-1]

    def plus_di(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        PLUS_DI.
        """
        result: np.ndarray = talib.PLUS_DI(self.high, self.low, self.close, n)
        if array:
            return result
        return result[-1]

    def willr(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        WILLR.
        """
        result: np.ndarray = talib.WILLR(self.high, self.low, self.close, n)
        if array:
            return result
        return result[-1]

    def ultosc(
        self,
        time_period1: int = 7,
        time_period2: int = 14,
        time_period3: int = 28,
        array: bool = False
    ) -> Union[float, np.ndarray]:
        """
        Ultimate Oscillator.
        """
        result: np.ndarray = talib.ULTOSC(self.high, self.low, self.close, time_period1, time_period2, time_period3)
        if array:
            return result
        return result[-1]

    def trange(self, array: bool = False) -> Union[float, np.ndarray]:
        """
        TRANGE.
        """
        result: np.ndarray = talib.TRANGE(self.high, self.low, self.close)
        if array:
            return result
        return result[-1]

    def boll(
        self,
        n: int,
        dev: float,
        array: bool = False
    ) -> Union[
        Tuple[np.ndarray, np.ndarray],
        Tuple[float, float]
    ]:
        """
        Bollinger Channel.
        """
        mid: Union[float, np.ndarray] = self.sma(n, array)
        std: Union[float, np.ndarray] = self.std(n, 1, array)

        up: Union[float, np.ndarray] = mid + std * dev
        down: Union[float, np.ndarray] = mid - std * dev

        return up, down

    def keltner(
        self,
        n: int,
        dev: float,
        array: bool = False
    ) -> Union[
        Tuple[np.ndarray, np.ndarray],
        Tuple[float, float]
    ]:
        """
        Keltner Channel.
        """
        mid: Union[float, np.ndarray] = self.sma(n, array)
        atr: Union[float, np.ndarray] = self.atr(n, array)

        up: Union[float, np.ndarray] = mid + atr * dev
        down: Union[float, np.ndarray] = mid - atr * dev

        return up, down

    def donchian(
        self, n: int, array: bool = False
    ) -> Union[
        Tuple[np.ndarray, np.ndarray],
        Tuple[float, float]
    ]:
        """
        Donchian Channel.
        """
        up: np.ndarray = talib.MAX(self.high, n)
        down: np.ndarray = talib.MIN(self.low, n)

        if array:
            return up, down
        return up[-1], down[-1]

    def aroon(
        self,
        n: int,
        array: bool = False
    ) -> Union[
        Tuple[np.ndarray, np.ndarray],
        Tuple[float, float]
    ]:
        """
        Aroon indicator.
        """
        aroon_down, aroon_up = talib.AROON(self.high, self.low, n)

        if array:
            return aroon_up, aroon_down
        return aroon_up[-1], aroon_down[-1]

    def aroonosc(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        Aroon Oscillator.
        """
        result: np.ndarray = talib.AROONOSC(self.high, self.low, n)

        if array:
            return result
        return result[-1]

    def minus_dm(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        MINUS_DM.
        """
        result: np.ndarray = talib.MINUS_DM(self.high, self.low, n)

        if array:
            return result
        return result[-1]

    def plus_dm(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        PLUS_DM.
        """
        result: np.ndarray = talib.PLUS_DM(self.high, self.low, n)

        if array:
            return result
        return result[-1]

    def mfi(self, n: int, array: bool = False) -> Union[float, np.ndarray]:
        """
        Money Flow Index.
        """
        result: np.ndarray = talib.MFI(self.high, self.low, self.close, self.volume, n)
        if array:
            return result
        return result[-1]

    def ad(self, array: bool = False) -> Union[float, np.ndarray]:
        """
        AD.
        """
        result: np.ndarray = talib.AD(self.high, self.low, self.close, self.volume)
        if array:
            return result
        return result[-1]

    def adosc(
        self,
        fast_period: int,
        slow_period: int,
        array: bool = False
    ) -> Union[float, np.ndarray]:
        """
        ADOSC.
        """
        result: np.ndarray = talib.ADOSC(self.high, self.low, self.close, self.volume, fast_period, slow_period)
        if array:
            return result
        return result[-1]

    def bop(self, array: bool = False) -> Union[float, np.ndarray]:
        """
        BOP.
        """
        result: np.ndarray = talib.BOP(self.open, self.high, self.low, self.close)

        if array:
            return result
        return result[-1]

    def stoch(
        self,
        fastk_period: int,
        slowk_period: int,
        slowk_matype: int,
        slowd_period: int,
        slowd_matype: int,
        array: bool = False
    ) -> Union[
        Tuple[float, float],
        Tuple[np.ndarray, np.ndarray]
    ]:
        """
        Stochastic Indicator
        """
        k, d = talib.STOCH(
            self.high,
            self.low,
            self.close,
            fastk_period,
            slowk_period,
            slowk_matype,
            slowd_period,
            slowd_matype
        )
        if array:
            return k, d
        return k[-1], d[-1]

    # TalibK线形态识别
    def cdl2crows(self, array: bool = False):
        """Two Crows"""
        result = talib.CDL2CROWS(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdl3blackcrows(self, array: bool = False):
        """Three Black Crows"""
        result = talib.CDL3BLACKCROWS(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdl3inside(self, array: bool = False):
        """Three Inside Up/Down"""
        result = talib.CDL3INSIDE(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdl3linestrike(self, array: bool = False):
        """Three-Line Strike"""
        result = talib.CDL3LINESTRIKE(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdl3outside(self, array: bool = False):
        """Three Outside Up/Down"""
        result = talib.CDL3OUTSIDE(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdl3starsinsouth(self, array: bool = False):
        """Three Stars In The South"""
        result = talib.CDL3STARSINSOUTH(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdl3whitesoldiers(self, array: bool = False):
        """Three Advancing White Soldiers"""
        result = talib.CDL3WHITESOLDIERS(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlabandonedbaby(self, array: bool = False):
        """Abandoned Baby"""
        result = talib.CDLABANDONEDBABY(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdladvanceblock(self, array: bool = False):
        """Advance Block"""
        result = talib.CDLADVANCEBLOCK(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlbelthold(self, array: bool = False):
        """Belt-hold"""
        result = talib.CDLBELTHOLD(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlbreakaway(self, array: bool = False):
        """Breakaway"""
        result = talib.CDLBREAKAWAY(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlclosingmarubozu(self, array: bool = False):
        """Closing Marubozu"""
        result = talib.CDLCLOSINGMARUBOZU(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlconcealbabyswall(self, array: bool = False):
        """Concealing Baby Swallow"""
        result = talib.CDLCONCEALBABYSWALL(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlcounterattack(self, array: bool = False):
        """Counterattack"""
        result = talib.CDLCOUNTERATTACK(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdldarkcloudcover(self, array: bool = False):
        """Dark Cloud Cover"""
        result = talib.CDLDARKCLOUDCOVER(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdldoji(self, array: bool = False):
        """Doji"""
        result = talib.CDLDOJI(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdldojistar(self, array: bool = False):
        """Doji Star"""
        result = talib.CDLDOJISTAR(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdldragonflydoji(self, array: bool = False):
        """Dragonfly Doji"""
        result = talib.CDLDRAGONFLYDOJI(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlengulfing(self, array: bool = False):
        """Engulfing Pattern"""
        result = talib.CDLENGULFING(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdleveningdojistar(self, array: bool = False):
        """Evening Doji Star"""
        result = talib.CDLEVENINGDOJISTAR(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdleveningstar(self, array: bool = False):
        """Evening Star"""
        result = talib.CDLEVENINGSTAR(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlgapsidesidewhite(self, array: bool = False):
        """Up/Down-gap side-by-side white lines"""
        result = talib.CDLGAPSIDESIDEWHITE(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlgravestonedoji(self, array: bool = False):
        """Gravestone Doji"""
        result = talib.CDLGRAVESTONEDOJI(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlhammer(self, array: bool = False):
        """Hammer"""
        result = talib.CDLHAMMER(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlhangingman(self, array: bool = False):
        """Hanging Man"""
        result = talib.CDLHANGINGMAN(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlharami(self, array: bool = False):
        """Harami Pattern"""
        result = talib.CDLHARAMI(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlharamicross(self, array: bool = False):
        """Harami Cross Pattern"""
        result = talib.CDLHARAMICROSS(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlhighwave(self, array: bool = False):
        """High-Wave Candle"""
        result = talib.CDLHIGHWAVE(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlhikkake(self, array: bool = False):
        """Hikkake Pattern"""
        result = talib.CDLHIKKAKE(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlhikkakemod(self, array: bool = False):
        """Modified Hikkake Pattern"""
        result = talib.CDLHIKKAKEMOD(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlhomingpigeon(self, array: bool = False):
        """Homing Pigeon"""
        result = talib.CDLHOMINGPIGEON(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlidentical3crows(self, array: bool = False):
        """Identical Three Crows"""
        result = talib.CDLIDENTICAL3CROWS(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlinneck(self, array: bool = False):
        """In-Neck Pattern"""
        result = talib.CDLINNECK(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlinvertedhammer(self, array: bool = False):
        """Inverted Hammer"""
        result = talib.CDLINVERTEDHAMMER(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlkicking(self, array: bool = False):
        """Kicking"""
        result = talib.CDLKICKING(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlkickingbylength(self, array: bool = False):
        """Kicking - bull/bear determined by the longer marubozu"""
        result = talib.CDLKICKINGBYLENGTH(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlladderbottom(self, array: bool = False):
        """Ladder Bottom"""
        result = talib.CDLLADDERBOTTOM(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdllongleggeddoji(self, array: bool = False):
        """Long Legged Doji"""
        result = talib.CDLLONGLEGGEDDOJI(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdllongline(self, array: bool = False):
        """Long Line Candle"""
        result = talib.CDLLONGLINE(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlmarubozu(self, array: bool = False):
        """Marubozu"""
        result = talib.CDLMARUBOZU(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlmatchinglow(self, array: bool = False):
        """Matching Low"""
        result = talib.CDLMATCHINGLOW(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlmathold(self, array: bool = False):
        """Mat Hold"""
        result = talib.CDLMATHOLD(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlmorningdojistar(self, array: bool = False):
        """Morning Doji Star"""
        result = talib.CDLMORNINGDOJISTAR(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlmorningstar(self, array: bool = False):
        """Morning Star"""
        result = talib.CDLMORNINGSTAR(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlonneck(self, array: bool = False):
        """On-Neck Pattern"""
        result = talib.CDLONNECK(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlpiercing(self, array: bool = False):
        """Piercing Pattern"""
        result = talib.CDLPIERCING(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlrickshawman(self, array: bool = False):
        """Rickshaw Man"""
        result = talib.CDLRICKSHAWMAN(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlrisefall3methods(self, array: bool = False):
        """Rising/Falling Three Methods"""
        result = talib.CDLRISEFALL3METHODS(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlseparatinglines(self, array: bool = False):
        """Separating Lines"""
        result = talib.CDLSEPARATINGLINES(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlshootingstar(self, array: bool = False):
        """Shooting Star"""
        result = talib.CDLSHOOTINGSTAR(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlshortline(self, array: bool = False):
        """Short Line Candle"""
        result = talib.CDLSHORTLINE(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlspinningtop(self, array: bool = False):
        """Spinning Top"""
        result = talib.CDLSPINNINGTOP(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlstalledpattern(self, array: bool = False):
        """Stalled Pattern"""
        result = talib.CDLSTALLEDPATTERN(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlsticksandwich(self, array: bool = False):
        """Stick Sandwich"""
        result = talib.CDLSTICKSANDWICH(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdltakuri(self, array: bool = False):
        """Takuri (Dragonfly Doji with very long lower shadow)"""
        result = talib.CDLTAKURI(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdltasukigap(self, array: bool = False):
        """Tasuki Gap"""
        result = talib.CDLTASUKIGAP(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlthrusting(self, array: bool = False):
        """Thrusting Pattern"""
        result = talib.CDLTHRUSTING(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdltristar(self, array: bool = False):
        """Tristar Pattern"""
        result = talib.CDLTRISTAR(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlunique3river(self, array: bool = False):
        """Unique 3 River"""
        result = talib.CDLUNIQUE3RIVER(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlupsidegap2crows(self, array: bool = False):
        """Upside Gap Two Crows"""
        result = talib.CDLUPSIDEGAP2CROWS(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]
    
    def cdlxsidegap3methods(self, array: bool = False):
        """Upside/Downside Gap Three Methods"""
        result = talib.CDLXSIDEGAP3METHODS(
            self.open,
            self.high,
            self.low,
            self.close,
        )
        if array:
            return result
        return result[-1]


def virtual(func: Callable) -> Callable:
    """
    mark a function as "virtual", which means that this function can be override.
    any base class should use this or @abstractmethod to decorate all functions
    that can be (re)implemented by subclasses.
    """
    return func


file_handlers: Dict[str, logging.FileHandler] = {}


def _get_file_logger_handler(filename: str) -> logging.FileHandler:
    handler: logging.FileHandler = file_handlers.get(filename, None)
    if handler is None:
        handler = logging.FileHandler(filename)
        file_handlers[filename] = handler  # Am i need a lock?
    return handler


def get_file_logger(filename: str) -> logging.Logger:
    """
    return a logger that writes records into a file.
    """
    logger: logging.Logger = logging.getLogger(filename)
    handler: logging.FileHandler = _get_file_logger_handler(filename)  # get singleton handler.
    handler.setFormatter(log_formatter)
    logger.addHandler(handler)  # each handler will be added only once.
    return logger
