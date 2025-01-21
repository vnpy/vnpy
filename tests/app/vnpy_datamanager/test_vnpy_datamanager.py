import unittest
from unittest.mock import patch, MagicMock
from datetime import datetime
from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.object import HistoryRequest, BarData
from vnpy_datafeed.binance_datafeed import BinanceDatafeed

import multiprocessing
from datetime import datetime, time
from logging import INFO
from time import sleep
from unittest import TestCase

import numpy as np
import pandas as pd
import polars as pl

from vnpy.app.factor_maker import FactorEngine, FactorMakerApp
from vnpy.app.data_recorder import DataRecorderApp
from vnpy.app.vnpy_datamanager import DataManagerEngine
from vnpy.event import Event
from vnpy.event import EventEngine
from vnpy.gateway.binance import BinanceSpotGateway
from vnpy.trader.constant import Exchange
from vnpy.trader.engine import MainEngine
from vnpy.trader.object import SubscribeRequest
from vnpy.trader.setting import SETTINGS


def gen_requests():
    # Create a HistoryRequest object with test data
    for symbol in ["BTCUSDT", "ETHUSDT"]:
        for interval in [Interval.MINUTE]:
            req = HistoryRequest(
                symbol=symbol,
                exchange=Exchange.BINANCE,
                interval=interval,
                start=datetime(2025, 1, 3),
                end=datetime(2025, 1, 5)
            )
            yield req


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

    # start data manager
    manager_engine: DataManagerEngine = main_engine.add_engine(DataManagerEngine)
    main_engine.write_log("启动数据管理程序")

    # Initialize the BinanceDatafeed object
    for req in gen_requests():
        print("=" * 50, req.symbol, req.interval, "=" * 50)
        records = manager_engine.download_bar_data(symbol=req.symbol, exchange=req.exchange,
                                                   interval=req.interval.value,
                                                   start=req.start, end=req.end, save=True,
                                                   save_dir=f"./vnpy_data")
        print(records)

    # # start data recorder
    # data_recorder_engine=main_engine.add_app(DataRecorderApp)
    # main_engine.write_log("启动数据记录程序")
    #
    # factor_maker_engine:FactorEngine = main_engine.add_app(FactorMakerApp)
    # factor_maker_engine.init_engine(fake=True)
    # main_engine.write_log("启动因子计算程序")

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


class TestBinanceDatafeed(unittest.TestCase):

    @patch('vnpy_datafeed.vnpy_datafeed.binance_datafeed.BinanceDataDumper')
    def test_query_bar_history_binance_historical_data(self, MockBinanceDataDumper):
        # Mock the BinanceDataDumper and its dump_data method
        mock_dumper = MockBinanceDataDumper.return_value
        mock_dumper.dump_data = MagicMock()

        # Create a HistoryRequest object with test data
        req = HistoryRequest(
            symbol="BTCUSDT",
            exchange=Exchange.BINANCE,
            interval=Interval.MINUTE,
            start=datetime(2023, 1, 1),
            end=datetime(2023, 1, 2)
        )

        # Initialize the BinanceDatafeed object
        datafeed = BinanceDatafeed()

        # Call the _query_bar_history_binance_historical_data_ method
        bars = datafeed._query_bar_history_binance_historical_data_(req=req, save_path=datafeed.save_path)

        # Assert that the dump_data method was called with the correct parameters
        mock_dumper.dump_data.assert_called_once_with(
            tickers=["BTCUSDT"],
            date_start=req.start.date(),
            date_end=req.end.date(),
            is_to_update_existing=False
        )

        # Assert that the method returns an empty list (as no actual data is processed in this test)
        self.assertEqual(bars, [])

    def test_real_run(self):
        run_parent()


if __name__ == '__main__':
    print(gen_requests())
