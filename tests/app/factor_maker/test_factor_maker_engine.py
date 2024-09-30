# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : ${DIR_PATH}
# @File     : ${FILE_NAME}
# @Time     : 2024/9/28 21:00
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
from unittest import TestCase
import multiprocessing
from time import sleep
from datetime import datetime, time
from logging import INFO
import pprint


from vnpy.event import EventEngine
from vnpy.trader.setting import SETTINGS
from vnpy.trader.engine import MainEngine
from vnpy.trader.object import SubscribeRequest,BarData
from vnpy.trader.constant import Exchange

from vnpy.gateway.binance import BinanceSpotGateway
from vnpy.app.data_recorder import DataRecorderApp
from vnpy.app.factor_maker import FactorEngine
from vnpy.app.factor_maker.factors import OPEN


class TestFactorEngine(TestCase):
    def setUp(self):
        event_engine = EventEngine()
        main_engine = MainEngine(event_engine)
        self.factor_engine = FactorEngine(main_engine,event_engine)
        self.factor_engine.init_engine()

    def test_sth(self):
        self.setUp()

        self.factor_engine.add_factor(str(OPEN),OPEN.factor_name,ticker='btcusdt',setting=None)

        pprint.pprint(self.factor_engine.__dict__)
        sleep(1)

    def test_init_engine(self):
        self.fail()

    def test_get_all_factor_class_names(self):
        self.fail()

    def test_load_factor_class(self):
        self.fail()

    def test_load_factor_setting(self):
        self.fail()

    def test_save_factor_setting(self):
        self.fail()

    def test_load_factor_data(self):
        self.fail()

    def test_sync_factor_data(self):
        self.fail()

    def test_start_all_factors(self):
        self.fail()

    def test_start_factor(self):
        self.fail()

    def test_load_bar(self):
        self.fail()

    def test_update_memory(self):
        self.fail()
