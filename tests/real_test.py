# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/tests
# @File     : real_test.py
# @Time     : 2025/1/21 19:25
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:

import multiprocessing
from datetime import datetime, time, timedelta
from logging import DEBUG
from time import sleep

from vnpy.app.data_recorder import DataRecorderApp
from vnpy.factor.engine import FactorEngine
#from vnpy.app.factor_maker import FactorMakerApp
from vnpy.event import EventEngine
from vnpy.gateway.binance import BinanceSpotGateway
from vnpy.trader.constant import Exchange
from vnpy.trader.engine import MainEngine
from vnpy.trader.event import EVENT_BAR
from vnpy.trader.object import BarData
from vnpy.trader.setting import SETTINGS
from vnpy.strategy.engine import StrategyEngine
#from vnpy.strategy.examples.test_strategy_template import TestStrategyTemplate

from vnpy.event import Event


def run_child():
    """
    1. start gateway
    2. feed data to factor engine
    3. push bar and factors into database
    """

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    main_engine.write_log("Main engine created successfully")


    # start factor engine
    factor_maker_engine: FactorEngine = main_engine.add_engine(FactorEngine)
    factor_maker_engine.init_engine(fake=True)
    factor_maker_engine.execute_calculation(dt=datetime.now())

    factor_maker_engine.bars = {}

    main_engine.write_log("Factor engine dask worker started successfully")

    dt = datetime.now()+timedelta(minutes=1)


    event1 = Event(
        type = EVENT_BAR,
        data=BarData(
            symbol="btcusdt",
            exchange=Exchange.BINANCE,
            datetime=dt,
            interval="1m",
            volume=687678,
            open_price=111111,
            high_price=1111459,
            low_price=111110,
            close_price=111118,
            gateway_name="BINANCE_SPOT"
        )
    )

    event2 = Event(
        type = EVENT_BAR,
        data=BarData(
            symbol="ethusdt",
            exchange=Exchange.BINANCE,
            datetime=dt,
            interval="1m",
            volume=288000,
            open_price=2000,
            high_price=3000,
            low_price=1980,
            close_price=2500,
            gateway_name="BINANCE_SPOT"
        )
    )

    event_engine.put(event1)
    event_engine.put(event2)
    main_engine.write_log("Bar Event broadcasted successfully")

    # connect to exchange
    """ main_engine.add_gateway(BinanceSpotGateway, "BINANCE_SPOT")
    binance_gateway_setting = {
        "key": SETTINGS.get("gateway.api_key", ""),
        "secret": SETTINGS.get("gateway.api_secret", ""),
        "server": "REAL"
    }
    main_engine.connect(binance_gateway_setting, "BINANCE_SPOT")
    main_engine.write_log("Connected to Binance interface")
    main_engine.subscribe_all(gateway_name='BINANCE_SPOT')"""
    # start data recorder

    """# # test engine
    strategy_engine: BaseStrategyEngine = main_engine.add_engine(BaseStrategyEngine)

    # init strategy template
    template_strategy = TestStrategyTemplate(strategy_engine=strategy_engine,
                                             strategy_name=TestStrategyTemplate.strategy_name,
                                             vt_symbols=['btcusdt.BINANCE'], setting={})

    strategy_engine.init_engine(strategies_path="vnpy/tests/strategy/strategies",
                                strategies={template_strategy.strategy_name: template_strategy})
    main_engine.write_log(f"启动[{strategy_engine.__class__.__name__}]")"""

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


def run_parent():
    """
    Running in the parent process.
    """
    print("Starting parent process")

    # Crypto markets trade 24/7
    child_process = None

    try:
        if child_process is None:
            print("Starting child process")
            child_process = multiprocessing.Process(target=run_child)
            child_process.start()
            print("Child process started successfully")
            
            # Keep the parent process running
            while True:
                sleep(5)
                if not child_process.is_alive():
                    print("Child process unexpectedly exited, restarting...")
                    child_process.join()
                    child_process = multiprocessing.Process(target=run_child)
                    child_process.start()
                    
    except KeyboardInterrupt:
        if child_process is not None:
            print("Shutting down child process")
            child_process.terminate()
            child_process.join()
            child_process = None
            print("Child process shutdown successful")


if __name__ == '__main__':
    run_child()
