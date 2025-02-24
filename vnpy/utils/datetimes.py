# -*- coding=utf-8 -*-
# @FilePath : utils
# @File     : datetimes.py
# @Time     : 2024/3/12 13:22
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
from typing import Union, Optional, Tuple

from enum import Enum as EEnum
from aenum import Enum as AEnum, NoAlias
import datetime
import polars as pl
import os

from vnpy.trader.constant import Exchange, Interval

class TimeFreq_Enum(EEnum):
    """用于表示时间频率，最小频率为ms. The values are in milliseconds and just are indicators, not the true values. Because something like months and years are not fixed in milliseconds.
    """
    # fixme: error here
    def __new__(cls, value):
        obj = object.__new__(cls)
        obj._value_ = value
        return obj

    unknown = 0
    ms = 1
    s = 1000
    m = s * 60  # minutes
    min = s * 60  # minutes
    h = m * 60  # hours
    d = h * 24  # days
    W = d * 7  # weeks
    M = d * 30  # months
    Y = d * 365  # years

class TimeFreq(AEnum):
    """用于表示时间频率，最小频率为ms. The values are in milliseconds and just are indicators, not the true values. Because something like months and years are not fixed in milliseconds.

    References
    ----------
    - https://pandas.pydata.org/pandas-docs/stable/user_guide/timeseries.html#offset-aliases
    """
    _settings_ = NoAlias

    unknown = 0
    ms = 1
    s = 1000
    m = s * 60  # minutes
    min = s * 60  # minutes
    h = m * 60  # hours
    d = h * 24  # days
    W = d * 7  # weeks
    M = d * 30  # months
    Y = d * 365  # years


class DatetimeUtils:
    @staticmethod
    def set_tz(tz: str = 'UTC'):
        os.environ['TZ'] = tz

    @staticmethod
    def normalize_time_str(time_str: str) -> str:
        """
        ``min`` will be converted into ``m``

        Parameters
        ----------
        time_str : str,
            something like '1m', '1s', '1ms'

        Returns
        -------
        str
        """
        if time_str == 'min':
            time_str = 'm'
        return time_str

    @staticmethod
    def normalize_unix(unix: Union[int, float], to_precision: str = 's') -> Union[float, int]:
        """
        将unix时间戳转换为指定精度
        Parameters
        ----------
        unix : int,
            unix时间戳
        to_precision : str
            's'表示转换为秒，'ms'表示转换为毫秒

        Returns
        -------
        int
        """
        if to_precision == 's':
            if unix > 9999999999:
                unix /= 1000
        elif to_precision == 'ms':
            if unix < 9999999999:
                unix *= 1000
        else:
            raise NotImplementedError("invalid to_precision, please check the input string.")

        return unix

    @staticmethod
    def split_time_str(time_str: str) -> tuple:
        """
        从时间字符串中提取数字和freq单位
        Parameters
        ----------
        time_str : str,
            something like '1m', '1s', '1ms'

        Returns
        -------
        tuple, (int, TimeFreq)
        """

        # note that the order of if-elif-else is important, the longer the freq string is, the higher priority it has to be
        if time_str.endswith(TimeFreq.min.name):
            return int(time_str[:-3]), TimeFreq.m
        elif time_str.endswith(TimeFreq.ms.name):
            return int(time_str[:-2]), TimeFreq.ms
        elif time_str.endswith(TimeFreq.s.name):
            return int(time_str[:-1]), TimeFreq.s
        elif time_str.endswith(TimeFreq.m.name):
            return int(time_str[:-1]), TimeFreq.m
        elif time_str.endswith(TimeFreq.d.name):
            return int(time_str[:-1]), TimeFreq.d
        else:
            raise NotImplementedError("invalid time_str, please check the input string.")

    @staticmethod
    def str2freq(time_str: str, ret_unit: Optional[Union[TimeFreq, str]] = TimeFreq.ms) -> int:
        """
        将time_str转换为最小单位freq的int倍数
        Parameters
        ----------
        time_str : str,
            something like '1m', '1s', '1ms'
        ret_unit : TimeFreq,
            返回的时间单位


        Notes
        -----
        ``min`` will be converted into ``m``

        Returns
        -------
        int
        """
        if isinstance(ret_unit, str):
            ret_unit = TimeFreq[ret_unit]
        if ret_unit is None:
            ret_unit = TimeFreq.ms
        time_str = normalize_time_str(time_str)
        split = split_time_str(time_str)
        return int(split[0] * split[1].value / ret_unit.value)

    @staticmethod
    def freq2str(freq: int, ret_unit: Optional[Union[TimeFreq, str]] = TimeFreq.ms) -> str:
        """
        将freq转换为时间字符串
        Parameters
        ----------
        freq : int,
            时间频率
        ret_unit : TimeFreq,
            返回的时间单位

        Returns
        -------
        str
        """
        raise NotImplementedError("尚未想好单位怎么正确表示")
        if isinstance(ret_unit, str):
            ret_unit = TimeFreq(ret_unit)
        if ret_unit is None:
            ret_unit = TimeFreq.ms
        return f"{freq / (TimeFreq.ms.value * ret_unit.value)}{ret_unit.name}"

    @staticmethod
    def unix2datetime(unix: Union[int, float], tz='UTC') -> datetime.datetime:
        """
        将unix时间戳转换为datetime对象
        Parameters
        ----------
        unix : int,
            unix时间戳

        Returns
        -------
        datetime.datetime
        """
        set_tz(tz)
        unix = normalize_unix(unix, to_precision='s')
        return datetime.datetime.fromtimestamp(unix)

    @staticmethod
    def datetime2unix(dt: datetime.datetime, tz='UTC') -> int:
        """
        将datetime对象转换为unix时间戳
        Parameters
        ----------
        dt : datetime.datetime

        Returns
        -------
        int
        """
        set_tz(tz)

        return int(dt.timestamp() * 1000)

    @staticmethod
    def unix2ymd(unix: int, tz='UTC') -> str:
        """
        将unix时间戳转换为年月日字符串
        Parameters
        ----------
        unix : int,
            unix时间戳

        Returns
        -------
        str
        """
        set_tz(tz)

        return unix2datetime(unix).strftime('%Y-%m-%d')

    @staticmethod
    def unix2datetime_polars(df: pl.DataFrame, col: str = 'datetime', tz='UTC'):
        """
        将unix时间戳转换为datetime对象
        Parameters
        ----------
        df : polars.DataFrame
        col : str,
            时间戳所在列名

        Returns
        -------
        """

        set_tz(tz)

        if df[col][0] < 9999999999:  # unixtime是s级
            df = df.with_columns(
                pl.from_epoch(col, time_unit='s')
            )
        else:
            df = df.with_columns(
                pl.from_epoch(col, time_unit='ms')
            )
        return df

    @staticmethod
    def datetime2unix_polars(df: pl.DataFrame, col: str, time_unit='ms', tz='UTC') -> pl.DataFrame:
        """
        将datetime对象转换为unix时间戳
        Parameters
        ----------
        df : polars.DataFrame
        col : str,
            时间戳所在列名

        Returns
        -------
        int
        """
        set_tz(tz)

        return df.with_columns(pl.col(col).dt.epoch(time_unit=time_unit))


def set_tz(tz: str = 'UTC'):
    os.environ['TZ'] = tz


def normalize_time_str(time_str: str) -> str:
    """
    ``min`` will be converted into ``m``

    Parameters
    ----------
    time_str : str,
        something like '1m', '1s', '1ms'

    Returns
    -------
    str
    """
    if time_str == 'min':
        time_str = 'm'
    return time_str


def normalize_unix(unix: Union[int, float], to_precision: str = 's') -> Union[float, int]:
    """
    将unix时间戳转换为指定精度
    Parameters
    ----------
    unix : int,
        unix时间戳
    to_precision : str
        's'表示转换为秒，'ms'表示转换为毫秒

    Returns
    -------
    int
    """
    if to_precision == 's':
        if unix > 9999999999:
            unix /= 1000
    elif to_precision == 'ms':
        if unix < 9999999999:
            unix *= 1000
    else:
        raise NotImplementedError("invalid to_precision, please check the input string.")

    return unix


def split_time_str(time_str: str) -> Tuple[int, int]:
    """
    从时间字符串中提取数字和freq单位
    Parameters
    ----------
    time_str : str,
        something like '1m', '1s', '1ms'

    Returns
    -------
    tuple: (int, int)
        first part and second part of the time string represented in ms
    """

    # note that the order of if-elif-else is important, the longer the freq string is, the higher priority it has to be
    if time_str.endswith(TimeFreq.min.name):
        return int(time_str[:-3]), TimeFreq.m
    elif time_str.endswith(TimeFreq.ms.name):
        return int(time_str[:-2]), TimeFreq.ms
    elif time_str.endswith(TimeFreq.s.name):
        return int(time_str[:-1]), TimeFreq.s
    elif time_str.endswith(TimeFreq.m.name):
        return int(time_str[:-1]), TimeFreq.m
    elif time_str.endswith(TimeFreq.d.name):
        return int(time_str[:-1]), TimeFreq.d
    else:
        raise NotImplementedError("invalid time_str, please check the input string.")


def str2freq(time_str: str, ret_unit: Optional[Union[TimeFreq, str]] = TimeFreq.ms) -> int:
    """
    将time_str转换为最小单位freq的int倍数
    Parameters
    ----------
    time_str : str,
        something like '1m', '1s', '1ms'
    ret_unit : TimeFreq,
        返回的时间单位


    Notes
    -----
    ``min`` will be converted into ``m``

    Returns
    -------
    int
    """
    if isinstance(ret_unit, str):
        ret_unit = TimeFreq[ret_unit]
    if ret_unit is None:
        ret_unit = TimeFreq.ms
    time_str = normalize_time_str(time_str)
    split = split_time_str(time_str)
    return int(split[0] * split[1].value / ret_unit.value)


def freq2str(freq: int, ret_unit: Optional[Union[TimeFreq, str]] = TimeFreq.ms) -> str:
    """
    将freq转换为时间字符串
    Parameters
    ----------
    freq : int,
        时间频率
    ret_unit : TimeFreq,
        返回的时间单位

    Returns
    -------
    str
    """
    raise NotImplementedError("尚未想好单位怎么正确表示")
    if isinstance(ret_unit, str):
        ret_unit = TimeFreq(ret_unit)
    if ret_unit is None:
        ret_unit = TimeFreq.ms
    return f"{freq / (TimeFreq.ms.value * ret_unit.value)}{ret_unit.name}"


def unix2datetime(unix: Union[int, float], tz='UTC') -> datetime.datetime:
    """
    将unix时间戳转换为datetime对象
    Parameters
    ----------
    unix : int,
        unix时间戳

    Returns
    -------
    datetime.datetime
    """
    set_tz(tz)
    unix = normalize_unix(unix, to_precision='s')
    return datetime.datetime.fromtimestamp(unix)


def datetime2unix(dt: datetime.datetime, tz='UTC') -> int:
    """
    将datetime对象转换为unix时间戳
    Parameters
    ----------
    dt : datetime.datetime

    Returns
    -------
    int
    """
    set_tz(tz)

    return int(dt.timestamp() * 1000)


def unix2ymd(unix: int, tz='UTC') -> str:
    """
    将unix时间戳转换为年月日字符串
    Parameters
    ----------
    unix : int,
        unix时间戳

    Returns
    -------
    str
    """
    set_tz(tz)

    return unix2datetime(unix).strftime('%Y-%m-%d')


def unix2datetime_polars(df: pl.DataFrame, col: str = 'datetime', tz='UTC'):
    """
    将unix时间戳转换为datetime对象
    Parameters
    ----------
    df : polars.DataFrame
    col : str,
        时间戳所在列名

    Returns
    -------
    """

    set_tz(tz)

    if df[col][0] < 9999999999:  # unixtime是s级
        df = df.with_columns(
            pl.from_epoch(col, time_unit='s')
        )
    else:
        df = df.with_columns(
            pl.from_epoch(col, time_unit='ms')
        )
    return df


def datetime2unix_polars(df: pl.DataFrame, col: str, time_unit='ms', tz='UTC') -> pl.DataFrame:
    """
    将datetime对象转换为unix时间戳
    Parameters
    ----------
    df : polars.DataFrame
    col : str,
        时间戳所在列名

    Returns
    -------
    int
    """
    set_tz(tz)

    return df.with_columns(pl.col(col).dt.epoch(time_unit=time_unit))


def interval2unix(interval: Interval,
                  ret_unit: Optional[Union[TimeFreq, str]] = TimeFreq.ms) -> Union[int, float]:
    """
    Get the timedelta for a given interval.

    Parameters:
        interval (Interval): Candlestick interval (e.g., 1m, 1h, 1d).

    Returns:
        timedelta: Time delta corresponding to the interval.
    """
    if isinstance(ret_unit, str):
        ret_unit = TimeFreq(ret_unit)

    interval_map = {
        Interval.MINUTE: datetime.timedelta(minutes=1),
        Interval.HOUR: datetime.timedelta(hours=1),
        Interval.DAILY: datetime.timedelta(days=1),
        Interval.WEEKLY: datetime.timedelta(weeks=1)
    }
    delta = interval_map.get(interval)
    if ret_unit == TimeFreq.ms:
        delta = delta.total_seconds() * 1000
    elif ret_unit == TimeFreq.s:
        delta = delta.total_seconds()
    else:
        raise NotImplementedError("not supported yet")
    return delta


def interval2timefreq(interval: Interval) -> TimeFreq:
    """
    Convert an interval to a TimeFreq enum.

    Parameters:
        interval (Interval): Candlestick interval (e.g., 1m, 1h, 1d).

    Returns:
        TimeFreq: Time frequency corresponding to the interval.
    """

    return TimeFreq(interval2unix(interval, ret_unit='ms'))
