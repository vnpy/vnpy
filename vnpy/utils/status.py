# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/vnpy/utils
# @File     : status.py
# @Time     : 2025/2/2 00:09
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:

import enum

class VnpyStatus(enum.Enum):
    """
    Enum for vnpy status
    """
    # VVVVVVVVV by hyf VVVVVVVVV
    # function return status for vnpy
    SUCCESS = "success"
    FAILED = "failed"

    # VVVVVVVVV by chatgpt, requires review VVVVVVVVV
    # status for vnpy
    INIT = "init"
    RUNNING = "running"
    STOPPED = "stopped"
    ERROR = "error"
    PAUSED = "paused"
    FINISHED = "finished"
    # status for vnpy components
    GATEWAY = "gateway"
    ENGINE = "engine"
    STRATEGY = "strategy"
    DATAFEED = "datafeed"
    FACTOR = "factor"
    DATABASE = "database"
    # status for vnpy data
    BAR = "bar"
    TICK = "tick"
    FACTOR_DATA = "factor_data"
    # status for vnpy datafeed
    DATAFEED_BAR = "datafeed_bar"
    DATAFEED_TICK = "datafeed_tick"
    DATAFEED_FACTOR = "datafeed_factor"
    # status for vnpy factor
    FACTOR_ENGINE = "factor_engine"
    FACTOR_MAKER = "factor_maker"
    # status for vnpy database
    DATABASE_CLICKHOUSE = "clickhouse"
    DATABASE_MYSQL = "mysql"
    DATABASE_MONGODB = "mongodb"
    DATABASE_REDIS = "redis"
    DATABASE_SQLITE = "sqlite"
    DATABASE_POSTGRESQL = "postgresql"
    DATABASE_SQLSERVER = "sqlserver"
    # status for vnpy strategy
    STRATEGY_TREND = "trend"
    STRATEGY_MEAN_REVERSION = "mean_reversion"
    STRATEGY_ARBITRAGE = "arbitrage"
    STRATEGY_STATISTICAL = "statistical"
    STRATEGY_NEURAL_NETWORK = "neural_network"
    STRATEGY_REINFORCEMENT_LEARNING = "reinforcement_learning"
    STRATEGY_GENETIC_ALGORITHM = "genetic_algorithm"
    # status for vnpy engine
    ENGINE_MAIN = "main"
    ENGINE_EVENT = "event"
    ENGINE_ALGO = "algo"
    ENGINE_RISK = "risk"
    ENGINE_PORTFOLIO = "portfolio"
    ENGINE_TRADING = "trading"
    ENGINE_EXECUTION = "execution"
    ENGINE_MATCHING = "matching"
    ENGINE_ACCOUNT = "account"
    ENGINE_POSITION = "position"
    ENGINE_ORDER = "order"
    ENGINE_TRADE = "trade"
    ENGINE_LOG = "log"
    ENGINE_ERROR = "error"
    ENGINE_WARNING = "warning"
    ENGINE_INFO = ""
    # ^^^^^^^^^^ by chatgpt ^^^^^^^^^^