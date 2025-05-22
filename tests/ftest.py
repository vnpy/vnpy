# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/tests
# @File     : real_test.py
# @Time     : 2025/1/21 19:25
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:

import multiprocessing
from datetime import datetime, time
from logging import DEBUG
from time import sleep

from vnpy.app.data_recorder import DataRecorderApp
from vnpy.factor.engine import FactorEngine
#from vnpy.app.factor_maker import FactorMakerApp
from vnpy.event import EventEngine
from vnpy.gateway.binance import BinanceSpotGateway
from vnpy.trader.engine import MainEngine
from vnpy.trader.setting import SETTINGS
from vnpy.strategy.engine import BaseStrategyEngine
#from vnpy.strategy.examples.test_strategy_template import TestStrategyTemplate


if __name__ == '__main__':
    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    main_engine.write_log("Main engine created successfully")
    main_engine.vt_symbols = ['btcusdt.BINANCE', 'ethusdt.BINANCE']

    # start factor engine
    factor_maker_engine: FactorEngine = main_engine.add_engine(FactorEngine)
    factor_maker_engine.init_engine()
    factor_maker_engine.init_memory(True)
    factor_maker_engine.execute_calculation(dt=datetime.now())
    factor_maker_engine.close()