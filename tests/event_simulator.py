# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/tests
# @File     : real_test.py
# @Time     : 2025/1/21 19:25
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:

import multiprocessing
from time import sleep
import time

from vnpy.factor.engine import FactorEngine
#from vnpy.app.factor_maker import FactorMakerApp
from vnpy.event import EventEngine
from vnpy.gateway.mimicgateway.mimicgateway import MimicGateway
from vnpy.trader.engine import MainEngine
#from vnpy.strategy.examples.test_strategy_template import TestStrategyTemplate



def run_child():
    """
    1. start gateway
    2. feed data to factor engine
    3. push bar and factors into database
    """

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    main_engine.write_log("Main engine created successfully")

    time.sleep(10)


    # start factor engine
    factor_maker_engine: FactorEngine = main_engine.add_engine(FactorEngine)
    factor_maker_engine.init_engine(fake=False)

    time.sleep(10)

    gateway_settings = {
        "symbols": [],
        "simulation_interval_seconds": 60.0, # Bars every second for each symbol
        "open_price_range_min": 100,
        "open_price_range_max": 105,
        "price_change_range_min": -1,
        "price_change_range_max": 1,
        "volume_range_min": 50,
        "volume_range_max": 200
    }

    # connect to exchange
    main_engine.add_gateway(MimicGateway, "MIMIC")

    main_engine.connect(gateway_settings, "MIMIC")
    main_engine.write_log("Connected to MIMIC interface")
    main_engine.subscribe_all(gateway_name='MIMIC')


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
    run_parent()
