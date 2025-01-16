# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/tests/utils
# @File     : test_datetimes.py
# @Time     : 2025/1/6 20:36
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:

import unittest
from datetime import datetime

import polars as pl

from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.object import HistoryRequest
# from vnpy_datafeed.vnpy_datafeed.binance_datafeed import BinanceDatafeed
from vnpy.utils.datetimes import DatetimeUtils, TimeFreq


class TestDatetimeUtils(unittest.TestCase):
    def test_TimeFreq(self):
        self.assertEqual(TimeFreq.ms.value, 1)
        self.assertEqual(TimeFreq.s.value, 1000)
        self.assertEqual(TimeFreq.m.value, 60000)
        self.assertEqual(TimeFreq.h.value, 3600000)
        self.assertEqual(TimeFreq.d.value, 86400000)
        self.assertEqual(TimeFreq.W.value, 604800000)
        self.assertEqual(TimeFreq.Y.value, 86400000 * 365)

    def test_normalize_time_str_converts_min_to_m(self):
        self.assertEqual(DatetimeUtils.normalize_time_str('min'), 'm')

    def test_normalize_time_str_keeps_other_values(self):
        self.assertEqual(DatetimeUtils.normalize_time_str('1s'), '1s')
        self.assertEqual(DatetimeUtils.normalize_time_str('1ms'), '1ms')
        print(DatetimeUtils.normalize_time_str('1s'), '1s')
        print(DatetimeUtils.normalize_time_str('1ms'), '1ms')

    def test_normalize_unix_converts_to_seconds(self):
        self.assertEqual(DatetimeUtils.normalize_unix(1609459200000, 's'), 1609459200)

    def test_normalize_unix_converts_to_milliseconds(self):
        self.assertEqual(DatetimeUtils.normalize_unix(1609459200, 'ms'), 1609459200000)

    def test_split_time_str_parses_correctly(self):
        self.assertEqual(DatetimeUtils.split_time_str('1m'), (1, TimeFreq.m))
        self.assertEqual(DatetimeUtils.split_time_str('1ms'), (1, TimeFreq.ms))
        print(DatetimeUtils.split_time_str('1m'), (1, TimeFreq.m))
        print(DatetimeUtils.split_time_str('1ms'), (1, TimeFreq.ms))
        self.assertEqual(TimeFreq.ms.factor_name, 'ms')
        self.assertEqual(TimeFreq.ms.value, 1)
        self.assertEqual(TimeFreq.s.factor_name, 's')
        self.assertEqual(TimeFreq.s.value, 1000)

    def test_str2freq_converts_correctly(self):
        self.assertEqual(DatetimeUtils.str2freq('1m'), 60000)
        self.assertEqual(DatetimeUtils.str2freq('1s'), 1000)

    def test_unix2datetime_converts_correctly(self):
        self.assertEqual(DatetimeUtils.unix2datetime(1609459200), datetime(2021, 1, 1))

    def test_datetime2unix_converts_correctly(self):
        self.assertEqual(DatetimeUtils.datetime2unix(datetime(2021, 1, 1)), 1609459200000)

    def test_unix2ymd_converts_correctly(self):
        self.assertEqual(DatetimeUtils.unix2ymd(1609459200), '2021-01-01')

    def test_unix2datetime_polars_converts_correctly(self):
        df = pl.DataFrame({'datetime': [1609459200]})
        result = DatetimeUtils.unix2datetime_polars(df)
        self.assertEqual(result['datetime'][0], datetime(2021, 1, 1))

    def test_datetime2unix_polars_converts_correctly(self):
        df = pl.DataFrame({'datetime': [datetime(2021, 1, 1)]})
        result = DatetimeUtils.datetime2unix_polars(df, 'datetime')
        self.assertEqual(result['datetime'][0], 1609459200000)


if __name__ == '__main__':
    unittest.main()
