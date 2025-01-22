# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/tests/trader
# @File     : test_object.py
# @Time     : 2025/1/21 21:59
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
import datetime
from unittest import TestCase
from vnpy.trader.object import FactorData, BarData,Exchange,Interval


class TestFactorData(TestCase):
    def test_factor_data(self):
        factor_data = FactorData(
            symbol='btcusdt',
            exchange=Exchange('BINANCE'),
            datetime=datetime.datetime.strptime('2025-01-21 21:59:00', '%Y-%m-%d %H:%M:%S'),
            interval=Interval('1m'),
            factor_name='factor_name',
            value=0.5
        )
        assert factor_data.symbol == 'btcusdt'
        assert factor_data.exchange.value == 'BINANCE'
        assert factor_data.datetime == datetime.datetime.strptime('2025-01-21 21:59:00', '%Y-%m-%d %H:%M:%S')
        assert factor_data.interval.value == '1m'
        assert factor_data.factor_name == 'factor_name'
        assert factor_data.value == 0.5
