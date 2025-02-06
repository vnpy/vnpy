# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/tests
# @File     : real_test.py
# @Time     : 2025/1/21 19:25
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:

# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : ${DIR_PATH}
# @File     : ${FILE_NAME}
# @Time     : 2024/9/28 21:00
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
import multiprocessing
from datetime import datetime, time
from logging import INFO
from time import sleep
from typing import Dict, Optional, Union, List
from unittest import TestCase

import numpy as np
import pandas as pd
import polars as pl

from vnpy.adapters.overview import OverviewHandler
from vnpy.app.factor_maker import FactorEngine
from vnpy.app.factor_maker import FactorMakerApp
from vnpy.app.data_recorder import DataRecorderApp
from vnpy.event import Event
from vnpy.event import EventEngine
from vnpy.gateway.binance import BinanceSpotGateway
from vnpy.trader.constant import Exchange,Interval
from vnpy.trader.datafeed import get_datafeed
from vnpy.trader.engine import MainEngine
from vnpy.trader.object import SubscribeRequest, BarData
from vnpy.trader.setting import SETTINGS


def run_child():
    """
    1. start gateway
    2. feed data to factor engine
    3. push bar and factors into database
    """

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    main_engine.write_log("主引擎创建成功")

    # connect to exchange
    main_engine.add_gateway(BinanceSpotGateway, "BINANCE_SPOT")
    binance_gateway_setting = {
        "key": SETTINGS.get("gateway.api_key", ""),
        "secret": SETTINGS.get("gateway.api_secret", ""),
        "server": "REAL"
    }
    main_engine.connect(binance_gateway_setting, "BINANCE_SPOT")
    main_engine.write_log("连接币安接口")
    main_engine.subscribe_all(gateway_name='BINANCE_SPOT')
    # main_engine.subscribe(SubscribeRequest(symbol='btcusdt', exchange=Exchange.BINANCE,interval=Interval.MINUTE), gateway_name='BINANCE_SPOT')

    # # todo zc: vnpy.app.vnpy_datamanager + datafeed(vnpy_datafeed) ->vnpy.app.data_recorder = overview(vnpy.adapters.overview) + database(vnpy_clickhouse)  补历史数据
    # # fixme: implement below in vnpy.app.vnpy_datamanager
    # datafeed = get_datafeed()
    # overview_handler = OverviewHandler(SETTINGS.get("overview_jsonpath", ""))
    # overview_handler.load_overview()
    # for req in overview_handler.check_missing_data():
    #     bars: Optional[Union[List[BarData], List[Dict]]] = datafeed.query_bar_history(req)
    #     bars.to_database()  # fixme: implement this step with vnpy.app.data_recorder, and maintain overview in vnpy.app.data_recorder
    #
    # for req in overview_handler.check_subscribe_stream():
    #     main_engine.subscribe(req=req, gateway_name='BINANCE_SPOT')  #第63行放到这操作

    # start data recorder
    data_recorder_engine = main_engine.add_app(DataRecorderApp)
    main_engine.write_log(f"启动[{data_recorder_engine.__class__.__name__}]")

    factor_maker_engine: FactorEngine = main_engine.add_app(FactorMakerApp)
    factor_maker_engine.init_engine(fake=True)
    main_engine.write_log(f"启动[{factor_maker_engine.__class__.__name__}]")

    # log_engine = main_engine.get_engine("log")
    # event_engine.register(EVENT_CTA_LOG, log_engine.process_log_event)
    # main_engine.write_log("注册日志事件监听")
    #
    # main_engine.connect(ctp_setting, "CTP")
    # main_engine.write_log("连接CTP接口")
    #
    # sleep(10)
    #
    # cta_engine.init_engine()
    # main_engine.write_log("CTA策略初始化完成")
    #
    # cta_engine.init_all_strategies()
    # sleep(60)   # Leave enough time to complete strategy initialization
    # main_engine.write_log("CTA策略全部初始化")
    #
    # cta_engine.start_all_strategies()
    # main_engine.write_log("CTA策略全部启动")

    while True:
        # print(main_engine.event_engine._queue.get())
        # print(main_engine.event_engine._queue.get().type)
        # print(type(main_engine.event_engine._queue.get()))
        sleep(1)


def run_parent():
    """
    Running in the parent process.
    """
    print("启动父进程")

    # Chinese futures market trading period (day/night)
    DAY_START = time(8, 45)
    DAY_END = time(15, 30)

    NIGHT_START = time(20, 45)
    NIGHT_END = time(2, 45)

    child_process = None

    while True:
        current_time = datetime.now().time()
        trading = False

        # Check whether in trading period
        if (
                (current_time >= DAY_START and current_time <= DAY_END)
                or (current_time >= NIGHT_START)
                or (current_time <= NIGHT_END)
        ) or True:
            trading = True

        # Start child process in trading period
        if trading and child_process is None:
            print("启动子进程")
            child_process = multiprocessing.Process(target=run_child)
            child_process.start()
            print("子进程启动成功")

        # 非记录时间则退出子进程
        if not trading and child_process is not None:
            print("关闭子进程")
            child_process.terminate()
            child_process.join()
            child_process = None
            print("子进程关闭成功")

        sleep(5)


class TestFactorEngine(TestCase):
    def init(self):
        event_engine = EventEngine()
        main_engine = MainEngine(event_engine)
        self.factor_engine = FactorEngine(main_engine, event_engine)
        self.factor_engine.init_engine()
        # print(self.factor_engine.memory_bar)
        # print(self.factor_engine.memory_factor)

        data = {'datetime': pd.date_range("2024-01-01", periods=200, freq="1min")}
        schema = {'datetime': datetime}
        for symbol in self.factor_engine.main_engine.vt_symbols:
            data[symbol] = np.random.random(200)
            schema[symbol] = pl.Float64

        for b in ["open", "high", "low", "close", "volume"]:
            self.factor_engine.memory_bar[b] = pl.concat(
                [self.factor_engine.memory_bar[b], pl.DataFrame(data=data, schema=schema)], how='vertical')
        for f in self.factor_engine.stacked_factors.keys():
            self.factor_engine.memory_factor[f] = pl.concat(
                [self.factor_engine.memory_factor[f], pl.DataFrame(data=data, schema=schema)], how='vertical')

        # print(self.factor_engine.memory_bar)
        # print(self.factor_engine.memory_factor)

    def test_sth(self):
        a = pl.DataFrame(
            data={'datetime': [], 'symbol': [], 'open': [], 'high': [], 'low': [], 'close': [], 'volume': []},
            schema={'datetime': datetime, 'symbol': pl.Utf8, 'open': pl.Float64, 'high': pl.Float64, 'low': pl.Float64,
                    'close': np.float16, 'volume': float})
        print(a)

    def test_init(self):
        self.init()

    def test_pipeline(self):
        """测试因子从数据源到因子计算和最终入库的整个流程

        Returns
        -------

        """

        self.init()

        # res = self.factor_engine.process_bar_event()
        # print(res)

        buffer = []
        while not self.factor_engine.event_engine._queue.empty():
            res: Event = self.factor_engine.event_engine._queue.get(block=True, timeout=1)
            buffer.append(res)
            # sleep(10)
        print(buffer)

        # pprint.pprint(self.factor_engine.__dict__)

    def test_real_run(self):
        run_parent()
