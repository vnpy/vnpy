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
import numpy as np
import pandas as pd
import polars as pl

from vnpy.event import EventEngine,Event
from vnpy.trader.setting import SETTINGS
from vnpy.trader.engine import MainEngine
from vnpy.trader.object import SubscribeRequest, BarData
from vnpy.trader.constant import Exchange,Interval

from vnpy.gateway.binance import BinanceSpotGateway
from vnpy.app.data_recorder import DataRecorderApp
from vnpy.app.factor_maker import FactorEngine
from vnpy.app.factor_maker.factors import OPEN


class TestFactorEngine(TestCase):
    def init(self):
        event_engine = EventEngine()
        main_engine = MainEngine(event_engine)
        self.factor_engine = FactorEngine(main_engine, event_engine)
        self.factor_engine.init_engine()

        date_range = pd.date_range("2024-01-01", periods=200, freq="1min")
        memory = {
            "open": pl.DataFrame(data=np.random.random(200)),
            "high": pl.DataFrame(data=np.random.random(200)),
            "low": pl.DataFrame(data=np.random.random(200)),
            "close": pl.DataFrame(data=np.random.random(200)),
            "volume": pl.DataFrame(data=np.random.random(200)),
        }
        self.factor_engine.memory=memory

    def test_init(self):
        self.init()

    def test_pipeline(self):
        """测试因子从数据源到因子计算和最终入库的整个流程

        Returns
        -------

        """

        def run_child():
            """
            Running in the child process.
            """
            SETTINGS["log.file"] = True

            event_engine = EventEngine()
            main_engine = MainEngine(event_engine)
            # main_engine.add_gateway(CtpGateway)
            # cta_engine = main_engine.add_app(CtaStrategyApp)
            main_engine.write_log("主引擎创建成功")

            main_engine.add_gateway(BinanceSpotGateway, "BINANCE_SPOT")
            binance_gateway_setting = {
                "key": SETTINGS.get("gateway.api_key", ""),
                "secret": SETTINGS.get("gateway.api_secret", ""),
                "server": "REAL"
            }
            main_engine.connect(binance_gateway_setting, "BINANCE_SPOT")
            main_engine.write_log("连接币安接口")

            main_engine.subscribe(SubscribeRequest(symbol='btcusdt', exchange=Exchange.BINANCE),
                                  gateway_name='BINANCE_SPOT')


        self.init()

        res=self.factor_engine.start_calculation()
        print(res)

        buffer=[]
        while not self.factor_engine.event_engine._queue.empty():

            res: Event=self.factor_engine.event_engine._queue.get(block=True, timeout=1)
            buffer.append(res)
            # sleep(10)
        print(buffer)

        # pprint.pprint(self.factor_engine.__dict__)

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
