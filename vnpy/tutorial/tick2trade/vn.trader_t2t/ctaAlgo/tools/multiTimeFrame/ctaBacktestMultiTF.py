# encoding: UTF-8

'''
这个文件加入在CTA回测引擎的基础上加入了辅助品种信息, 保持接口的一致, 可以在原CTA引擎上执行的代码,
也可以在这个引擎上执行
This file add multi Time Frame functionalities to CTA backtesting engine, the APIs are the
same as CTA engine. Real trading code can be directly used for backtesting.
'''

from __future__ import division
from vtFunction import loadMongoSetting

from ctaBacktesting import *

class BacktestEngineMultiTF(BacktestingEngine):

    def __init__(self):
        """Constructor"""
        super(BacktestEngineMultiTF, self).__init__()

        self.info_symbols   = []        # List, 输入辅助品种的2值tuple, 左边为数据库名, 右边为collection名
        self.InfoCursor     = {}        # Dict, 放置回测用辅助品种数据库
        self.initInfoCursor = {}        # Dict, 放置初始化用辅助品种数据库
        self.infobar        = {}        # Dict, 放置辅助品种最新一个K线数据
        self.MultiOn        = False     # Boolean, 判断是否传入了辅助品种

    # ----------------------------------------------------------------------
    def setDatabase(self, dbName, symbol, **kwargs):
        """set database that provide historical data"""

        self.dbName = dbName

        # Set executed symbol and information symbols
        self.symbol = symbol
        if "info_symbol" in kwargs:
            self.info_symbols = kwargs["info_symbol"]

            # Turn on MultiTF switch
            if len(self.info_symbols) > 0:
                self.MultiOn = True

    # ----------------------------------------------------------------------
    def loadInitData(self, collection, **kwargs):
        """Load initializing data"""
        # 载入初始化需要用的数据
        # Load initialised data

        # $gte means "greater and equal to"
        # $lt means "less than"
        flt = {'datetime': {'$gte': self.dataStartDate,
                            '$lt': self.strategyStartDate}}
        self.initCursor = collection.find(flt)

        # 初始化辅助品种数据
        # Initializing information data
        if "inf" in kwargs:
            for name in kwargs["inf"]:
                DB = kwargs["inf"][name]
                self.initInfoCursor[name] = DB.find(flt)

        # 将数据从查询指针中读取出，并生成列表
        # Read data from cursor, generate a list
        self.initData = []

        for d in self.initCursor:
            data = self.dataClass()
            data.__dict__ = d
            self.initData.append(data)

    # ----------------------------------------------------------------------
    def loadHistoryData(self):
        """载入历史数据"""
        """load historical data"""

        host, port, logging = loadMongoSetting()

        self.dbClient = pymongo.MongoClient(host, port)
        collection = self.dbClient[self.dbName][self.symbol]

        # Load historical data of information symbols, construct a dictionary of Database
        # Values of dictionary are mongo.Client.
        info_collection = {}
        if self.MultiOn is True:
            for DBname, symbol in self.info_symbols:
                info_collection[DBname + " " + symbol] = self.dbClient[DBname][symbol]

        self.output("Start loading historical data")

        # 首先根据回测模式，确认要使用的数据类
        # Choose data type based on backtest mode
        if self.mode == self.BAR_MODE:
            self.dataClass = CtaBarData
            self.func      = self.newBar
        else:
            self.dataClass = CtaTickData
            self.func = self.newTick

        # Load initializing data
        self.loadInitData(collection, inf=info_collection)

        # 载入回测数据
        # Load backtest data (exclude initializing data)
        if not self.dataEndDate:
            # If "End Date" is not set, retreat data up to today
            flt = {'datetime': {'$gte': self.strategyStartDate}}
        else:
            flt = {'datetime': {'$gte': self.strategyStartDate,
                                '$lte': self.dataEndDate}}
        self.dbCursor = collection.find(flt)

        if self.MultiOn is True:
            for db in info_collection:
                self.InfoCursor[db] = info_collection[db].find(flt)
            self.output(
                "Data loading completed, data volumn: %s" % (self.initCursor.count() + self.dbCursor.count() + \
                                                             sum([i.count() for i in self.InfoCursor.values()])))
        else:
            self.output("Data loading completed, data volumn: %s" % (self.initCursor.count() + self.dbCursor.count()))

    # ----------------------------------------------------------------------
    def runBacktesting(self):
        """运行回测"""
        """Run backtesting"""

        # 载入历史数据
        # Load historical data
        self.loadHistoryData()

        self.output("Start backtesing!")

        self.strategy.inited = True
        self.strategy.onInit()
        self.output("Strategy initialsing complete")

        self.strategy.trading = True
        self.strategy.onStart()
        self.output("Strategy started")

        self.output("Processing historical data...")

        dataClass = self.dataClass
        func = self.func
        for d in self.dbCursor:
            data = dataClass()
            data.__dict__ = d
            func(data)

        self.output("No more historical data")

    # ----------------------------------------------------------------------
    def checkInformationData(self):
        """Update information symbols' data"""

        # If infobar is empty, which means it is the first time calling this method
        if self.infobar == {}:
            for info_symbol in self.InfoCursor:
                try:
                    self.infobar[info_symbol] = next(self.InfoCursor[info_symbol])
                except StopIteration:
                    print "Data of information symbols is empty! Input must be a list, not str."
                    raise

        temp = {}
        for info_symbol in self.infobar:

            data = self.infobar[info_symbol]

            # Update data only when Time Stamp is matched
            if (data is not None) and (data['datetime'] <= self.dt):

                try:
                    temp[info_symbol] = CtaBarData()
                    temp[info_symbol].__dict__ = data
                    self.infobar[info_symbol] = next(self.InfoCursor[info_symbol])
                except StopIteration:
                    self.infobar[info_symbol] = None
                    self.output("No more data in information database.")
            else:
                temp[info_symbol] = None

        return temp

    # ----------------------------------------------------------------------
    def newBar(self, bar):
        """新的K线"""
        """new ohlc Bar"""
        self.bar = bar
        self.dt = bar.datetime
        self.updatePosition()  # Update total position value based on new Bar
        self.crossLimitOrder()  # 先撮合限价单
        self.crossStopOrder()  # 再撮合停止单
        if self.MultiOn is True:
            self.strategy.onBar(bar, infobar=self.checkInformationData())  # 推送K线到策略中
        else:
            self.strategy.onBar(bar)  # 推送K线到策略中

    # ----------------------------------------------------------------------
    def newTick(self, tick):
        """新的Tick"""
        """new Tick"""
        self.tick = tick
        self.dt = tick.datetime
        self.crossLimitOrder()
        self.crossStopOrder()
        self.strategy.onTick(tick)

########################################################################

