# -*- coding=utf-8 -*-
# @FilePath : utils
# @File     : datetimes.py
# @Time     : 2024/3/12 13:22
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
from typing import Union, Optional, Tuple

from enum import Enum as EEnum
import datetime
import polars as pl
import os

from vnpy.trader.constant import Exchange, Interval

# from aenum import Enum as AEnum, NoAlias
# class TimeFreq(AEnum):
#     """Deprecated because of the inconvenience of using aenum
#     用于表示时间频率，最小频率为ms. The values are in milliseconds and just are indicators, not the true values. Because something like months and years are not fixed in milliseconds.
# 
#     References
#     ----------
#     - https://pandas.pydata.org/pandas-docs/stable/user_guide/timeseries.html#offset-aliases
#     """
#     _settings_ = NoAlias
# 
#     unknown = 0
#     ms = 1
#     s = 1000
#     m = s * 60  # minutes
#     min = s * 60  # minutes
#     h = m * 60  # hours
#     d = h * 24  # days
#     W = d * 7  # weeks
#     M = d * 30  # months
#     Y = d * 365  # years

class TimeFreq(EEnum):
    """用于表示时间频率，最小频率为ms. 
    The values are in milliseconds and just are indicators, not the true values. 
    Because something like months and years are not fixed in milliseconds.
    """
    unknown = 0
    ms = 1  # milliseconds
    s = ms * 1000  # seconds
    m = s * 60  # minutes
    h = m * 60  # hours
    d = h * 24  # days
    W = d * 7  # weeks
    M = d * 30  # months
    Y = d * 365  # years


class DatetimeUtils:
    # todo: replace all functions in this project with the static methods in this class
    @classmethod
    def set_tz(cls, tz: str = 'UTC'):
        os.environ['TZ'] = tz

    @classmethod
    def normalize_time_str(cls, time_str: str) -> str:
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

    @classmethod
    def normalize_unix(cls, unix: Union[int, float], to_precision: str = 's') -> Union[float, int]:
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

    @classmethod
    def split_time_str(cls, time_str: str) -> Tuple[Union[int, float], TimeFreq]:
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
        time_str = cls.normalize_time_str(time_str)
        if time_str.endswith(TimeFreq.ms.name):
            time_number = float(time_str[:-2])
            if time_number.is_integer():
                time_number = int(time_number)
            return time_number, TimeFreq.ms
        elif time_str.endswith(TimeFreq.s.name):
            time_number = float(time_str[:-1])
            if time_number.is_integer():
                time_number = int(time_number)
            return time_number, TimeFreq.s
        elif time_str.endswith(TimeFreq.m.name):
            time_number = float(time_str[:-1])
            if time_number.is_integer():
                time_number = int(time_number)
            return time_number, TimeFreq.m
        elif time_str.endswith(TimeFreq.d.name):
            time_number = float(time_str[:-1])
            if time_number.is_integer():
                time_number = int(time_number)
            return time_number, TimeFreq.d
        else:
            raise NotImplementedError("invalid time_str, please check the input string.")

    @classmethod
    def str2freq(cls, time_str: str, ret_unit: Union[TimeFreq, str]) -> Tuple[int, TimeFreq]:
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
        Union[int, TimeFreq]
        """
        if isinstance(ret_unit, str):
            ret_unit = TimeFreq[ret_unit]

        time_str = cls.normalize_time_str(time_str)
        number, freq = cls.split_time_str(time_str)
        number = number * freq.value / ret_unit.value
        if not number.is_integer():
            raise ValueError(f"{time_str} cannot be converted to {ret_unit}")
        number = int(number)
        return number, ret_unit

    @classmethod
    def freq2str(cls, freq: TimeFreq, ret_unit: Optional[Union[TimeFreq, str]] = TimeFreq.m) -> str:
        """
        将freq转换为时间字符串
        Parameters
        ----------
        freq : TimeFreq,
            时间频率
        ret_unit : TimeFreq,
            返回的时间单位

        Returns
        -------
        str
        """
        # raise NotImplementedError("尚未想好单位怎么正确表示")
        if isinstance(ret_unit, str):
            ret_unit = cls.normalize_time_str(ret_unit)
            ret_unit = TimeFreq[ret_unit]
        if ret_unit is None:
            ret_unit = TimeFreq.ms

        pre = freq.value / (TimeFreq.ms.value * ret_unit.value)  # the number part of freq string
        assert pre.is_integer(), f"freq {freq} cannot be converted to {ret_unit}"
        pre = int(pre)
        return f"{pre}{ret_unit.name}"

    @classmethod
    def unix2datetime(cls, unix: Union[int, float], tz='UTC') -> datetime.datetime:
        """
        将unix时间戳转换为datetime对象
        Parameters
        ----------
        unix : int,
            unix时间戳
        tz : str,
            时区
        Returns
        -------
        datetime.datetime
        """
        cls.set_tz(tz)
        unix = cls.normalize_unix(unix, to_precision='s')
        return datetime.datetime.fromtimestamp(unix)

    @classmethod
    def datetime2unix(cls, dt: datetime.datetime, tz='UTC') -> int:
        """
        将datetime对象转换为unix时间戳
        Parameters
        ----------
        dt : datetime.datetime
        tz : str,
            时区
        Returns
        -------
        int
        """
        cls.set_tz(tz)

        return int(dt.timestamp() * 1000)

    @classmethod
    def unix2ymd(cls, unix: int, tz='UTC') -> str:
        """
        将unix时间戳转换为年月日字符串
        Parameters
        ----------
        unix : int,
            unix时间戳
        tz : str,
            时区

        Returns
        -------
        str
        """
        cls.set_tz(tz)

        return cls.unix2datetime(unix).strftime('%Y-%m-%d')

    @classmethod
    def unix2datetime_polars(cls, df: pl.DataFrame, col: str = 'datetime', tz='UTC'):
        """
        将unix时间戳转换为datetime对象
        Parameters
        ----------
        df : polars.DataFrame
        col : str,
            时间戳所在列名
        tz : str,
            时区
        Returns
        -------
        """

        cls.set_tz(tz)

        if df[col][0] < 9999999999:  # unixtime是s级
            df = df.with_columns(
                pl.from_epoch(col, time_unit='s')
            )
        else:
            df = df.with_columns(
                pl.from_epoch(col, time_unit='ms')
            )
        return df

    @classmethod
    def datetime2unix_polars(cls, df: pl.DataFrame, col: str, time_unit='ms', tz='UTC') -> pl.DataFrame:
        """
        将datetime对象转换为unix时间戳
        Parameters
        ----------
        df : polars.DataFrame
        col : str,
            时间戳所在列名
        tz : str,
            时区
        time_unit : str,
            时间单位，'s'表示秒，'ms'表示毫秒
        Returns
        -------
        pl.DataFrame
        """
        cls.set_tz(tz)

        return df.with_columns(pl.col(col).dt.epoch(time_unit=time_unit))

    @classmethod
    def interval2unix(cls, interval: Interval,
                      ret_unit: Optional[Union[TimeFreq, str]] = TimeFreq.ms) -> Union[int, float]:
        """
        Get the timedelta for a given interval.

        Parameters:
            interval (Interval): Candlestick interval (e.g., 1m, 1h, 1d).

        Returns:
            timedelta: Time delta corresponding to the interval.
        """
        if isinstance(ret_unit, str):
            ret_unit = cls.normalize_time_str(ret_unit)
        ret_unit = TimeFreq[ret_unit]

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

    @classmethod
    def interval2freq(cls, interval: Interval) -> TimeFreq:
        """
        Convert an interval to a TimeFreq enum.

        Parameters:
            interval (Interval): Candlestick interval (e.g., 1m, 1h, 1d).

        Returns:
            TimeFreq: Time frequency corresponding to the interval.
        """

        return TimeFreq(cls.interval2unix(interval, ret_unit='ms'))

    @classmethod
    def interval2str(cls, interval: Interval) -> str:
        """
        Convert an interval to a TimeFreq enum.

        Parameters:
            interval (Interval): Candlestick interval (e.g., 1m, 1h, 1d).

        Returns:
            TimeFreq: Time frequency corresponding to the interval.
        """
        mapper = {
            "MINUTE": "m",
            "HOUR": "h",
            "DAILY": "d",
            "WEEKLY": "W",
            "TICK": "s",
        }

        return cls.freq2str(cls.interval2freq(interval), ret_unit=mapper[interval.name])
