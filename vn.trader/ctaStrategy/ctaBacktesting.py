# encoding: UTF-8

'''
本文件中包含的是CTA模块的回测引擎，回测引擎的API和CTA引擎一致，
可以使用和实盘相同的代码进行回测。
'''
from __future__ import division

from datetime import datetime, timedelta
from collections import OrderedDict
from itertools import product
import multiprocessing
import pymongo

from ctaBase import *
from vtConstant import *
from vtGateway import VtOrderData, VtTradeData
from vtFunction import loadMongoSetting

from eventEngine import *

import MySQLdb
import json
import os
import cPickle
import csv
import logging
import copy
import pandas as pd
import re

########################################################################
class BacktestingEngine(object):
    """
    CTA回测引擎
    函数接口和策略引擎保持一样，
    从而实现同一套代码从回测到实盘。
    # modified by IncenseLee：
    1.增加Mysql数据库的支持；
    2.修改装载数据为批量式后加载模式。
    3.增加csv 读取bar的回测模式
    4.增加csv 读取tick合并价差的回测模式
    5.增加EventEngine，并对newBar增加发送OnBar事件，供外部的回测主体显示Bar线。
    """
    
    TICK_MODE = 'tick'              # 数据模式，逐Tick回测
    BAR_MODE = 'bar'                # 数据模式，逐Bar回测

    REALTIME_MODE ='RealTime'       # 逐笔交易计算资金，供策略获取资金容量，计算开仓数量
    FINAL_MODE = 'Final'            # 最后才统计交易，不适合按照百分比等开仓数量计算

    #----------------------------------------------------------------------
    def __init__(self, eventEngine = None):
        """Constructor"""

        self.eventEngine = eventEngine

        # 本地停止单编号计数
        self.stopOrderCount = 0
        # stopOrderID = STOPORDERPREFIX + str(stopOrderCount)
        
        # 本地停止单字典
        # key为stopOrderID，value为stopOrder对象
        self.stopOrderDict = {}             # 停止单撤销后不会从本字典中删除
        self.workingStopOrderDict = {}      # 停止单撤销后会从本字典中删除

        # 引擎类型为回测
        self.engineType = ENGINETYPE_BACKTESTING

        # 回测相关
        self.strategy = None        # 回测策略
        self.mode = self.BAR_MODE   # 回测模式，默认为K线

        self.startDate = ''
        self.initDays = 0
        self.endDate = ''

        self.slippage = 0           # 回测时假设的滑点
        self.rate = 0               # 回测时假设的佣金比例（适用于百分比佣金）
        self.size = 1               # 合约大小，默认为1        
        self.priceTick = 0          # 价格最小变动

        self.dbClient = None        # 数据库客户端
        self.dbCursor = None        # 数据库指针
        
        self.historyData = []       # 历史数据的列表，回测用
        self.initData = []          # 初始化用的数据
        self.backtestingData = []   # 回测用的数据
        
        self.dbName = ''            # 回测数据库名
        self.symbol = ''            # 回测集合名
        self.margin_rate = 0.11     # 回测合约的保证金比率

        self.dataStartDate = None       # 回测数据开始日期，datetime对象
        self.dataEndDate = None         # 回测数据结束日期，datetime对象
        self.strategyStartDate = None   # 策略启动日期（即前面的数据用于初始化），datetime对象
        
        self.limitOrderDict = OrderedDict()         # 限价单字典
        self.workingLimitOrderDict = OrderedDict()  # 活动限价单字典，用于进行撮合用
        self.limitOrderCount = 0                    # 限价单编号

        # 持仓缓存字典
        # key为vtSymbol，value为PositionBuffer对象
        self.posBufferDict = {}

        self.tradeCount = 0                 # 成交编号
        self.tradeDict = OrderedDict()      # 成交字典
        
        self.logList = []                   # 日志记录
        
        # 当前最新数据，用于模拟成交用
        self.tick = None
        self.bar = None
        self.dt = None                      # 最新的时间
        self.gatewayName = u'BackTest'

        # csvFile相关
        self.barTimeInterval = 60          # csv文件，属于K线类型，K线的周期（秒数）,缺省是1分钟

        # 费用情况
        self.avaliable = EMPTY_FLOAT
        self.percent = EMPTY_FLOAT
        self.percentLimit = 30              # 投资仓位比例上限

        # 回测计算相关
        self.calculateMode = self.FINAL_MODE
        self.usageCompounding = False       # 是否使用简单复利 （只针对FINAL_MODE有效）

        self.initCapital = 10000            # 期初资金
        self.capital = self.initCapital     # 资金  （相当于Balance）
        self.maxCapital = self.initCapital          # 资金最高净值

        self.maxPnl = 0                     # 最高盈利
        self.minPnl = 0                     # 最大亏损
        self.maxVolume = 1                  # 最大仓位数
        self.winningResult = 0              # 盈利次数
        self.losingResult = 0              # 亏损次数

        self.totalResult = 0         # 总成交数量
        self.totalWinning = 0        # 总盈利
        self.totalLosing = 0        # 总亏损
        self.totalTurnover = 0       # 总成交金额（合约面值）
        self.totalCommission = 0     # 总手续费
        self.totalSlippage = 0       # 总滑点

        self.timeList = []           # 时间序列
        self.pnlList = []            # 每笔盈亏序列
        self.capitalList = []        # 盈亏汇总的时间序列
        self.drawdownList = []       # 回撤的时间序列
        self.drawdownRateList = []   # 最大回撤比例的时间序列

        self.dailyList = []
        self.exportTradeList = []    # 导出交易记录列表

        self.fixCommission = EMPTY_FLOAT    # 固定交易费用

    def getAccountInfo(self):
        """返回账号的实时权益，可用资金，仓位比例,投资仓位比例上限"""
        if self.capital == EMPTY_FLOAT:
            self.percent = EMPTY_FLOAT

        return self.capital, self.avaliable, self.percent, self.percentLimit

    #----------------------------------------------------------------------
    def setStartDate(self, startDate='20100416', initDays=10):
        """设置回测的启动日期"""
        self.startDate = startDate
        self.initDays = initDays

        self.dataStartDate = datetime.strptime(startDate, '%Y%m%d')

        # 初始化天数
        initTimeDelta = timedelta(initDays)

        self.strategyStartDate = self.dataStartDate + initTimeDelta
        
    #----------------------------------------------------------------------
    def setEndDate(self, endDate=''):
        """设置回测的结束日期"""
        self.endDate = endDate
        if endDate:
            self.dataEndDate = datetime.strptime(endDate, '%Y%m%d')
            # 若不修改时间则会导致不包含dataEndDate当天数据
            self.dataEndDate.replace(hour=23, minute=59)
        else:
            self.dataEndDate = datetime.now()

    def setMinDiff(self, minDiff):
        """设置回测品种的最小跳价，用于修正数据"""
        self.minDiff = minDiff
        self.priceTick = minDiff

    #----------------------------------------------------------------------
    def setBacktestingMode(self, mode):
        """设置回测模式"""
        self.mode = mode

    #----------------------------------------------------------------------
    def setDatabase(self, dbName, symbol):
        """设置历史数据所用的数据库"""
        self.dbName = dbName
        self.symbol = symbol

    def setMarginRate(self, margin_rate):

        if margin_rate!= EMPTY_FLOAT:
            self.margin_rate = margin_rate

    # ----------------------------------------------------------------------
    def setSlippage(self, slippage):
        """设置滑点点数"""
        self.slippage = slippage

    # ----------------------------------------------------------------------
    def setSize(self, size):
        """设置合约大小"""
        self.size = size

    # ----------------------------------------------------------------------
    def setRate(self, rate):
        """设置佣金比例"""
        self.rate = rate

    # ----------------------------------------------------------------------
    def setPriceTick(self, priceTick):
        """设置价格最小变动"""
        self.priceTick = priceTick
        self.minDiff = priceTick

    #----------------------------------------------------------------------
    def loadHistoryDataFromMongo(self):
        """载入历史数据"""
        host, port, log = loadMongoSetting()
        
        self.dbClient = pymongo.MongoClient(host, port)
        collection = self.dbClient[self.dbName][self.symbol]

        self.output(u'开始载入数据')
      
        # 首先根据回测模式，确认要使用的数据类
        if self.mode == self.BAR_MODE:
            dataClass = CtaBarData
            func = self.newBar
        else:
            dataClass = CtaTickData
            func = self.newTick

        # 载入初始化需要用的数据
        flt = {'datetime':{'$gte':self.dataStartDate,
                           '$lt':self.strategyStartDate}}        
        initCursor = collection.find(flt)
        
        # 将数据从查询指针中读取出，并生成列表
        self.initData = []              # 清空initData列表
        for d in initCursor:
            data = dataClass()
            data.__dict__ = d
            self.initData.append(data)      
        
        # 载入回测数据
        if not self.dataEndDate:
            flt = {'datetime':{'$gte':self.strategyStartDate}}   # 数据过滤条件
        else:
            flt = {'datetime':{'$gte':self.strategyStartDate,
                               '$lte':self.dataEndDate}}  
        self.dbCursor = collection.find(flt)
        
        self.output(u'载入完成，数据量：%s' %(initCursor.count() + self.dbCursor.count()))

    #----------------------------------------------------------------------
    def connectMysql(self):
        """连接MysqlDB"""

        # 载入json文件
        fileName = 'mysql_connect.json'
        try:
            f = file(fileName)
        except IOError:
            self.writeCtaLog(u'回测引擎读取Mysql_connect.json失败')
            return

        # 解析json文件
        setting = json.load(f)
        try:
            mysql_host = str(setting['host'])
            mysql_port = int(setting['port'])
            mysql_user = str(setting['user'])
            mysql_passwd = str(setting['passwd'])
            mysql_db = str(setting['db'])

        except IOError:
            self.writeCtaLog(u'回测引擎读取Mysql_connect.json,连接配置缺少字段，请检查')
            return

        try:
            self.__mysqlConnection = MySQLdb.connect(host=mysql_host, user=mysql_user,
                                                     passwd=mysql_passwd, db=mysql_db, port=mysql_port)
            self.__mysqlConnected = True
            self.writeCtaLog(u'回测引擎连接MysqlDB成功')
        except Exception:
            self.writeCtaLog(u'回测引擎连接MysqlDB失败')

     #----------------------------------------------------------------------
    def loadDataHistoryFromMysql(self, symbol, startDate, endDate):
        """载入历史TICK数据
        如果加载过多数据会导致加载失败,间隔不要超过半年
        """

        if not endDate:
            endDate = datetime.today()

        # 看本地缓存是否存在
        if self.__loadDataHistoryFromLocalCache(symbol, startDate, endDate):
            self.writeCtaLog(u'历史TICK数据从Cache载入')
            return

        # 每次获取日期周期
        intervalDays = 10

        for i in range (0,(endDate - startDate).days +1, intervalDays):
            d1 = startDate + timedelta(days = i )

            if (endDate - d1).days > 10:
                d2 = startDate + timedelta(days = i + intervalDays -1 )
            else:
                d2 = endDate

            # 从Mysql 提取数据
            self.__qryDataHistoryFromMysql(symbol, d1, d2)

        self.writeCtaLog(u'历史TICK数据共载入{0}条'.format(len(self.historyData)))

        # 保存本地cache文件
        self.__saveDataHistoryToLocalCache(symbol, startDate, endDate)


    def __loadDataHistoryFromLocalCache(self, symbol, startDate, endDate):
        """看本地缓存是否存在
        added by IncenseLee
        """

        # 运行路径下cache子目录
        cacheFolder = os.getcwd()+'/cache'

        # cache文件
        cacheFile = u'{0}/{1}_{2}_{3}.pickle'.\
                    format(cacheFolder, symbol, startDate.strftime('%Y-%m-%d'), endDate.strftime('%Y-%m-%d'))

        if not os.path.isfile(cacheFile):
            return False

        else:
            try:
                # 从cache文件加载
                cache = open(cacheFile,mode='r')
                self.historyData = cPickle.load(cache)
                cache.close()
                return True
            except Exception as e:
                self.writeCtaLog(u'读取文件{0}失败'.format(cacheFile))
                return False

    def __saveDataHistoryToLocalCache(self, symbol, startDate, endDate):
        """保存本地缓存
        added by IncenseLee
        """

        # 运行路径下cache子目录
        cacheFolder = os.getcwd()+'/cache'

        # 创建cache子目录
        if not os.path.isdir(cacheFolder):
            os.mkdir(cacheFolder)

        # cache 文件名
        cacheFile = u'{0}/{1}_{2}_{3}.pickle'.\
                    format(cacheFolder, symbol, startDate.strftime('%Y-%m-%d'), endDate.strftime('%Y-%m-%d'))

        # 重复存在 返回
        if os.path.isfile(cacheFile):
            return False

        else:
            # 写入cache文件
            cache = open(cacheFile, mode='w')
            cPickle.dump(self.historyData,cache)
            cache.close()
            return True

    #----------------------------------------------------------------------
    def __qryDataHistoryFromMysql(self, symbol, startDate, endDate):
        """从Mysql载入历史TICK数据
        added by IncenseLee
        """

        try:
            self.connectMysql()
            if self.__mysqlConnected:

                # 获取指针
                cur = self.__mysqlConnection.cursor(MySQLdb.cursors.DictCursor)

                if endDate:

                    # 开始日期 ~ 结束日期
                    sqlstring = ' select \'{0}\' as InstrumentID, str_to_date(concat(ndate,\' \', ntime),' \
                               '\'%Y-%m-%d %H:%i:%s\') as UpdateTime,price as LastPrice,vol as Volume, day_vol as DayVolume,' \
                               'position_vol as OpenInterest,bid1_price as BidPrice1,bid1_vol as BidVolume1, ' \
                               'sell1_price as AskPrice1, sell1_vol as AskVolume1 from TB_{0}MI ' \
                               'where ndate between cast(\'{1}\' as date) and cast(\'{2}\' as date) order by UpdateTime'.\
                               format(symbol,  startDate, endDate)

                elif startDate:

                    # 开始日期 - 当前
                    sqlstring = ' select \'{0}\' as InstrumentID,str_to_date(concat(ndate,\' \', ntime),' \
                               '\'%Y-%m-%d %H:%i:%s\') as UpdateTime,price as LastPrice,vol as Volume, day_vol as DayVolume,' \
                               'position_vol as OpenInterest,bid1_price as BidPrice1,bid1_vol as BidVolume1, ' \
                               'sell1_price as AskPrice1, sell1_vol as AskVolume1 from TB__{0}MI ' \
                               'where ndate > cast(\'{1}\' as date) order by UpdateTime'.\
                               format( symbol, startDate)

                else:

                    # 所有数据
                    sqlstring =' select \'{0}\' as InstrumentID,str_to_date(concat(ndate,\' \', ntime),' \
                              '\'%Y-%m-%d %H:%i:%s\') as UpdateTime,price as LastPrice,vol as Volume, day_vol as DayVolume,' \
                              'position_vol as OpenInterest,bid1_price as BidPrice1,bid1_vol as BidVolume1, ' \
                              'sell1_price as AskPrice1, sell1_vol as AskVolume1 from TB__{0}MI order by UpdateTime'.\
                              format(symbol)

                self.writeCtaLog(sqlstring)

                # 执行查询
                count = cur.execute(sqlstring)
                self.writeCtaLog(u'历史TICK数据共{0}条'.format(count))


                # 分批次读取
                fetch_counts = 0
                fetch_size = 1000

                while True:
                    results = cur.fetchmany(fetch_size)

                    if not results:
                        break

                    fetch_counts = fetch_counts + len(results)

                    if not self.historyData:
                        self.historyData =results

                    else:
                        self.historyData = self.historyData + results

                    self.writeCtaLog(u'{1}~{2}历史TICK数据载入共{0}条'.format(fetch_counts,startDate,endDate))


            else:
                self.writeCtaLog(u'MysqlDB未连接，请检查')

        except MySQLdb.Error as e:
            self.writeCtaLog(u'MysqlDB载入数据失败，请检查.Error {0}'.format(e))

    def __dataToTick(self, data):
        """
        数据库查询返回的data结构，转换为tick对象
        added by IncenseLee        """

        tick = CtaTickData()
        symbol = data['InstrumentID']
        tick.symbol = symbol

        # 创建TICK数据对象并更新数据
        tick.vtSymbol = symbol
        # tick.openPrice = data['OpenPrice']
        # tick.highPrice = data['HighestPrice']
        # tick.lowPrice = data['LowestPrice']
        tick.lastPrice = float(data['LastPrice'])

        # bug fix:
        # ctp日常传送的volume数据，是交易日日内累加值。数据库的volume，是数据商自行计算整理的
        # 因此，改为使用DayVolume，与CTP实盘一致
        #tick.volume = data['Volume']
        tick.volume = data['DayVolume']
        tick.openInterest = data['OpenInterest']

        #  tick.upperLimit = data['UpperLimitPrice']
        #  tick.lowerLimit = data['LowerLimitPrice']

        tick.datetime = data['UpdateTime']
        tick.date = tick.datetime.strftime('%Y-%m-%d')
        tick.time = tick.datetime.strftime('%H:%M:%S')
        # 数据库中并没有tradingDay的数据，回测时，暂时按照date授予。
        tick.tradingDay = tick.date

        tick.bidPrice1 = float(data['BidPrice1'])
        # tick.bidPrice2 = data['BidPrice2']
        # tick.bidPrice3 = data['BidPrice3']
        # tick.bidPrice4 = data['BidPrice4']
        # tick.bidPrice5 = data['BidPrice5']

        tick.askPrice1 = float(data['AskPrice1'])
        # tick.askPrice2 = data['AskPrice2']
        # tick.askPrice3 = data['AskPrice3']
        # tick.askPrice4 = data['AskPrice4']
        # tick.askPrice5 = data['AskPrice5']

        tick.bidVolume1 = data['BidVolume1']
        # tick.bidVolume2 = data['BidVolume2']
        # tick.bidVolume3 = data['BidVolume3']
        # tick.bidVolume4 = data['BidVolume4']
        # tick.bidVolume5 = data['BidVolume5']

        tick.askVolume1 = data['AskVolume1']
        # tick.askVolume2 = data['AskVolume2']
        # tick.askVolume3 = data['AskVolume3']
        # tick.askVolume4 = data['AskVolume4']
        # tick.askVolume5 = data['AskVolume5']

        return tick

    #----------------------------------------------------------------------
    def getMysqlDeltaDate(self,symbol, startDate, decreaseDays):
        """从mysql库中获取交易日前若干天
        added by IncenseLee
        """
        try:
            if self.__mysqlConnected:

                # 获取mysql指针
                cur = self.__mysqlConnection.cursor()

                sqlstring='select distinct ndate from TB_{0}MI where ndate < ' \
                          'cast(\'{1}\' as date) order by ndate desc limit {2},1'.format(symbol, startDate, decreaseDays-1)

                # self.writeCtaLog(sqlstring)

                count = cur.execute(sqlstring)

                if count > 0:

                    # 提取第一条记录
                    result = cur.fetchone()

                    return result[0]

                else:
                    self.writeCtaLog(u'MysqlDB没有查询结果，请检查日期')

            else:
                self.writeCtaLog(u'MysqlDB未连接，请检查')

        except MySQLdb.Error as e:
            self.writeCtaLog(u'MysqlDB载入数据失败，请检查.Error {0}: {1}'.format(e.arg[0],e.arg[1]))

        # 出错后缺省返回
        return startDate-timedelta(days=3)

    # ----------------------------------------------------------------------
    def runBackTestingWithArbTickFile(self,mainPath, arbSymbol):
        """运行套利回测（使用本地tickcsv数据)
        参数：套利代码 SP rb1610&rb1701
        added by IncenseLee
        原始的tick，分别存放在白天目录1和夜盘目录2中，每天都有各个合约的数据
        Z:\ticks\SHFE\201606\RB\0601\
                                     RB1610.txt
                                     RB1701.txt
                                     ....
        Z:\ticks\SHFE_night\201606\RB\0601
                                     RB1610.txt
                                     RB1701.txt
                                     ....

        夜盘目录为自然日，不是交易日。

        按照回测的开始日期，到结束日期，循环每一天。
        每天优先读取日盘数据，再读取夜盘数据。
        读取eg1（如RB1610），读取Leg2（如RB701），合并成价差tick，灌输到策略的onTick中。
        """
        self.capital = self.initCapital  # 更新设置期初资金

        if len(arbSymbol) < 1:
            self.writeCtaLog(u'套利合约为空')
            return

        if not (arbSymbol.upper().index("SP") == 0 and arbSymbol.index(" ") > 0 and arbSymbol.index("&") > 0):
            self.writeCtaLog(u'套利合约格式不符合')
            return

        # 获得Leg1，leg2
        legs = arbSymbol[arbSymbol.index(" "):]
        leg1 = legs[1:legs.index("&")]
        leg2 = legs[legs.index("&") + 1:]
        self.writeCtaLog(u'Leg1:{0},Leg2:{1}'.format(leg1, leg2))

        if not self.dataStartDate:
            self.writeCtaLog(u'回测开始日期未设置。')
            return
        # RB
        if len(self.symbol)<1:
            self.writeCtaLog(u'回测对象未设置。')
            return

        if not self.dataEndDate:
            self.dataEndDate = datetime.today()

        #首先根据回测模式，确认要使用的数据类
        if self.mode == self.BAR_MODE:
            self.writeCtaLog(u'本回测仅支持tick模式')
            return

        testdays = (self.dataEndDate - self.dataStartDate).days

        if testdays < 1:
            self.writeCtaLog(u'回测时间不足')
            return

        for i in range(0, testdays):

            testday = self.dataStartDate + timedelta(days = i)

            self.output(u'回测日期:{0}'.format(testday))

            # 白天数据
            self.__loadArbTicks(mainPath,testday,leg1,leg2)

            # 夜盘数据
            self.__loadArbTicks(mainPath+'_night', testday, leg1, leg2)


    def __loadArbTicks(self,mainPath,testday,leg1,leg2):

        self.writeCtaLog(u'加载回测日期:{0}\{1}的价差tick'.format(mainPath, testday))

        cachefilename = u'{0}_{1}_{2}_{3}_{4}'.format(self.symbol,leg1,leg2, mainPath, testday.strftime('%Y%m%d'))

        arbTicks = self.__loadArbTicksFromLocalCache(cachefilename)

        dt = None

        if len(arbTicks) < 1:

            leg1File = u'z:\\ticks\\{0}\\{1}\\{2}\\{3}\\{4}.txt' \
                .format(mainPath, testday.strftime('%Y%m'), self.symbol, testday.strftime('%m%d'), leg1)
            if not os.path.isfile(leg1File):
                self.writeCtaLog(u'{0}文件不存在'.format(leg1File))
                return

            leg2File = u'z:\\ticks\\{0}\\{1}\\{2}\\{3}\\{4}.txt' \
                .format(mainPath, testday.strftime('%Y%m'), self.symbol, testday.strftime('%m%d'), leg2)
            if not os.path.isfile(leg2File):
                self.writeCtaLog(u'{0}文件不存在'.format(leg2File))
                return

            # 先读取leg2的数据到目录，以日期时间为key
            leg2Ticks = {}

            leg2CsvReadFile = file(leg2File, 'rb')
            #reader = csv.DictReader((line.replace('\0',' ') for line in leg2CsvReadFile), delimiter=",")
            reader = csv.DictReader(leg2CsvReadFile, delimiter=",")
            self.writeCtaLog(u'加载{0}'.format(leg2File))
            for row in reader:
                tick = CtaTickData()

                tick.vtSymbol = self.symbol
                tick.symbol = self.symbol

                tick.date = testday.strftime('%Y%m%d')
                tick.tradingDay = tick.date
                tick.time = row['Time']

                try:
                    tick.datetime = datetime.strptime(tick.date + ' ' + tick.time, '%Y%m%d %H:%M:%S.%f')
                except Exception as ex:
                    self.writeCtaError(u'日期转换错误:{0},{1}:{2}'.format(tick.date + ' ' + tick.time, Exception, ex))
                    continue

                # 修正毫秒
                if tick.datetime.replace(microsecond = 0) == dt:
                    # 与上一个tick的时间（去除毫秒后）相同,修改为500毫秒
                    tick.datetime=tick.datetime.replace(microsecond = 500)
                    tick.time = tick.datetime.strftime('%H:%M:%S.%f')

                else:
                    tick.datetime = tick.datetime.replace(microsecond=0)
                    tick.time = tick.datetime.strftime('%H:%M:%S.%f')

                dt = tick.datetime

                tick.lastPrice = float(row['LastPrice'])
                tick.volume = int(float(row['LVolume']))
                tick.bidPrice1 = float(row['BidPrice'])  # 叫买价（价格低）
                tick.bidVolume1 = int(float(row['BidVolume']))
                tick.askPrice1 = float(row['AskPrice'])  # 叫卖价（价格高）
                tick.askVolume1 = int(float(row['AskVolume']))

                # 排除涨停/跌停的数据
                if (tick.bidPrice1 == float('1.79769E308') and tick.bidVolume1 == 0) \
                    or (tick.askPrice1 == float('1.79769E308') and tick.askVolume1 == 0):
                    continue

                dtStr = tick.date + ' ' + tick.time
                if dtStr in leg2Ticks:
                    self.writeCtaError(u'日内数据重复，异常,数据时间为:{0}'.format(dtStr))
                else:
                    leg2Ticks[dtStr] = tick

            leg1CsvReadFile = file(leg1File, 'rb')
            #reader = csv.DictReader((line.replace('\0',' ') for line in leg1CsvReadFile), delimiter=",")
            reader = csv.DictReader(leg1CsvReadFile, delimiter=",")
            self.writeCtaLog(u'加载{0}'.format(leg1File))

            dt = None
            for row in reader:

                arbTick = CtaTickData()

                arbTick.date = testday.strftime('%Y%m%d')
                arbTick.time = row['Time']
                try:
                    arbTick.datetime = datetime.strptime(arbTick.date + ' ' + arbTick.time, '%Y%m%d %H:%M:%S.%f')
                except Exception as ex:
                    self.writeCtaError(u'日期转换错误:{0},{1}:{2}'.format(arbTick.date + ' ' + arbTick.time, Exception, ex))
                    continue

                # 修正毫秒
                if arbTick.datetime.replace(microsecond=0) == dt:
                    # 与上一个tick的时间（去除毫秒后）相同,修改为500毫秒
                    arbTick.datetime = arbTick.datetime.replace(microsecond=500)
                    arbTick.time = arbTick.datetime.strftime('%H:%M:%S.%f')

                else:
                    arbTick.datetime = arbTick.datetime.replace(microsecond=0)
                    arbTick.time = arbTick.datetime.strftime('%H:%M:%S.%f')

                dt = arbTick.datetime
                dtStr = ' '.join([arbTick.date, arbTick.time])

                if dtStr in leg2Ticks:
                    leg2Tick = leg2Ticks[dtStr]

                    arbTick.vtSymbol = self.symbol
                    arbTick.symbol = self.symbol

                    arbTick.lastPrice = EMPTY_FLOAT
                    arbTick.volume = EMPTY_INT

                    leg1AskPrice1 = float(row['AskPrice'])
                    leg1AskVolume1 = int(float(row['AskVolume']))

                    leg1BidPrice1 = float(row['BidPrice'])
                    leg1BidVolume1 = int(float(row['BidVolume']))

                    # 排除涨停/跌停的数据
                    if ((leg1AskPrice1 == float('1.79769E308') or leg1AskPrice1 == 0) and leg1AskVolume1 == 0) \
                            or ((leg1BidPrice1 == float('1.79769E308') or leg1BidPrice1 == 0) and leg1BidVolume1 == 0):
                        continue

                    # 叫卖价差=leg1.askPrice1 - leg2.bidPrice1，volume为两者最小
                    arbTick.askPrice1 = leg1AskPrice1 - leg2Tick.bidPrice1
                    arbTick.askVolume1 = min(leg1AskVolume1, leg2Tick.bidVolume1)

                    # 叫买价差=leg1.bidPrice1 - leg2.askPrice1，volume为两者最小
                    arbTick.bidPrice1 = leg1BidPrice1 - leg2Tick.askPrice1
                    arbTick.bidVolume1 = min(leg1BidVolume1, leg2Tick.askVolume1)

                    arbTicks.append(arbTick)

                    del leg2Ticks[dtStr]

            # 保存到历史目录
            if len(arbTicks) > 0:
                self.__saveArbTicksToLocalCache(cachefilename, arbTicks)

        for t in arbTicks:
            # 推送到策略中
            self.newTick(t)

    def __loadArbTicksFromLocalCache(self, filename):
        """从本地缓存中，加载数据"""
        # 运行路径下cache子目录
        cacheFolder = os.getcwd() + '/cache'

        # cache文件
        cacheFile = u'{0}/{1}.pickle'. \
            format(cacheFolder, filename)

        if not os.path.isfile(cacheFile):
            return []
        else:
            # 从cache文件加载
            cache = open(cacheFile, mode='r')
            l = cPickle.load(cache)
            cache.close()
            return l

    def __saveArbTicksToLocalCache(self, filename, arbticks):
        """保存价差tick到本地缓存目录"""
        # 运行路径下cache子目录
        cacheFolder = os.getcwd() + '/cache'

        # 创建cache子目录
        if not os.path.isdir(cacheFolder):
            os.mkdir(cacheFolder)

        # cache 文件名
        cacheFile = u'{0}/{1}.pickle'. \
            format(cacheFolder, filename)

        # 重复存在 返回
        if os.path.isfile(cacheFile):
            return False

        else:
            # 写入cache文件
            cache = open(cacheFile, mode='w')
            cPickle.dump(arbticks, cache)
            cache.close()
            return True

    def runBackTestingWithNonStrArbTickFile(self, leg1MainPath, leg2MainPath, leg1Symbol,leg2Symbol):
        """运行套利回测（使用本地tickcsv数据)
        参数：
        leg1MainPath： leg1合约所在的市场路径
        leg2MainPath： leg2合约所在的市场路径
        leg1Symbol： leg1合约
        Leg2Symbol：leg2合约
        added by IncenseLee
        原始的tick，分别存放在白天目录1和夜盘目录2中，每天都有各个合约的数据
        Z:\ticks\SHFE\201606\RB\0601\
                                     RB1610.txt
                                     RB1701.txt
                                     ....
        Z:\ticks\SHFE_night\201606\RB\0601
                                     RB1610.txt
                                     RB1701.txt
                                     ....

        夜盘目录为自然日，不是交易日。

        按照回测的开始日期，到结束日期，循环每一天。
        每天优先读取日盘数据，再读取夜盘数据。
        读取eg1（如RB1610），读取Leg2（如RB701），根据两者tick的时间优先顺序，逐一tick灌输到策略的onTick中。
        """
        self.capital = self.initCapital  # 更新设置期初资金

        if not self.dataStartDate:
            self.writeCtaLog(u'回测开始日期未设置。')
            return
        # RB
        if len(self.symbol)<1:
            self.writeCtaLog(u'回测对象未设置。')
            return

        if not self.dataEndDate:
            self.dataEndDate = datetime.today()

        #首先根据回测模式，确认要使用的数据类
        if self.mode == self.BAR_MODE:
            self.writeCtaLog(u'本回测仅支持tick模式')
            return

        testdays = (self.dataEndDate - self.dataStartDate).days

        if testdays < 1:
            self.writeCtaLog(u'回测时间不足')
            return

        for i in range(0, testdays):
            testday = self.dataStartDate + timedelta(days = i)

            self.output(u'回测日期:{0}'.format(testday))

            # 加载运行白天数据
            self.__loadNotStdArbTicks(leg1MainPath, leg2MainPath, testday, leg1Symbol,leg2Symbol)

            self.savingDailyData(testday, self.capital, self.maxCapital)

            # 加载运行夜盘数据
            self.__loadNotStdArbTicks(leg1MainPath+'_night', leg2MainPath+'_night', testday, leg1Symbol, leg2Symbol)

        self.savingDailyData(self.dataEndDate, self.capital, self.maxCapital)

    def __loadTicksFromFile(self, filepath, tickDate, vtSymbol):
        """从文件中读取tick"""
        # 先读取数据到Dict，以日期时间为key
        ticks = OrderedDict()

        if not os.path.isfile(filepath):
            self.writeCtaLog(u'{0}文件不存在'.format(filepath))
            return ticks
        dt = None
        csvReadFile = file(filepath, 'rb')

        reader = csv.DictReader(csvReadFile, delimiter=",")
        self.writeCtaLog(u'加载{0}'.format(filepath))
        for row in reader:
            tick = CtaTickData()

            tick.vtSymbol = vtSymbol
            tick.symbol = vtSymbol

            tick.date = tickDate.strftime('%Y%m%d')
            tick.tradingDay = tick.date
            tick.time = row['Time']

            try:
                tick.datetime = datetime.strptime(tick.date + ' ' + tick.time, '%Y%m%d %H:%M:%S.%f')
            except Exception as ex:
                self.writeCtaError(u'日期转换错误:{0},{1}:{2}'.format(tick.date + ' ' + tick.time, Exception, ex))
                continue

            # 修正毫秒
            if tick.datetime.replace(microsecond=0) == dt:
                # 与上一个tick的时间（去除毫秒后）相同,修改为500毫秒
                tick.datetime = tick.datetime.replace(microsecond=500)
                tick.time = tick.datetime.strftime('%H:%M:%S.%f')

            else:
                tick.datetime = tick.datetime.replace(microsecond=0)
                tick.time = tick.datetime.strftime('%H:%M:%S.%f')

            dt = tick.datetime

            tick.lastPrice = float(row['LastPrice'])
            tick.volume = int(float(row['LVolume']))
            tick.bidPrice1 = float(row['BidPrice'])  # 叫买价（价格低）
            tick.bidVolume1 = int(float(row['BidVolume']))
            tick.askPrice1 = float(row['AskPrice'])  # 叫卖价（价格高）
            tick.askVolume1 = int(float(row['AskVolume']))

            # 排除涨停/跌停的数据
            if (tick.bidPrice1 == float('1.79769E308') and tick.bidVolume1 == 0) \
                    or (tick.askPrice1 == float('1.79769E308') and tick.askVolume1 == 0):
                continue

            dtStr = tick.date + ' ' + tick.time
            if dtStr in ticks:
                self.writeCtaError(u'日内数据重复，异常,数据时间为:{0}'.format(dtStr))
            else:
                ticks[dtStr] = tick

        return ticks

    def __loadNotStdArbTicks(self, leg1MainPath,leg2MainPath, testday, leg1Symbol, leg2Symbol):

        self.writeCtaLog(u'加载回测日期:{0}的价差tick'.format( testday))
        p = re.compile(r"([A-Z]+)[0-9]+", re.I)

        leg1_shortSymbol = p.match(leg1Symbol)
        leg2_shortSymbol = p.match(leg2Symbol)

        if leg1_shortSymbol is None or leg2_shortSymbol is None:
            self.writeCtaLog(u'{0},{1}不能正则分解'.format(leg1Symbol, leg2Symbol))
            return

        leg1_shortSymbol = leg1_shortSymbol.group(1)
        leg2_shortSymbol = leg2_shortSymbol.group(1)

        # E:\Ticks\ZJ\2015\201505\TF
        leg1File = u'{0}\\{1}\\{2}\\{3}\\{4}\\{5}.txt' \
            .format(leg1MainPath, testday.strftime('%Y'),testday.strftime('%Y%m'), leg1_shortSymbol, testday.strftime('%m%d'), leg1Symbol)
        if not os.path.isfile(leg1File):
            self.writeCtaLog(u'{0}文件不存在'.format(leg1File))
            return

        leg2File = u'{0}\\{1}\\{2}\\{3}\\{4}\\{5}.txt' \
            .format(leg2MainPath, testday.strftime('%Y'), testday.strftime('%Y%m'), leg2_shortSymbol, testday.strftime('%m%d'), leg2Symbol)
        if not os.path.isfile(leg2File):
            self.writeCtaLog(u'{0}文件不存在'.format(leg2File))
            return

        leg1Ticks = self.__loadTicksFromFile(filepath=leg1File,tickDate= testday, vtSymbol=leg1Symbol)
        if len(leg1Ticks) == 0:
            self.writeCtaLog(u'{0}读取tick数为空'.format(leg1File))
            return

        leg2Ticks = self.__loadTicksFromFile(filepath=leg2File, tickDate=testday, vtSymbol=leg2Symbol)
        if len(leg2Ticks) == 0:
            self.writeCtaLog(u'{0}读取tick数为空'.format(leg1File))
            return

        leg1_tick = None
        leg2_tick = None

        while not (len(leg1Ticks) == 0 or len(leg2Ticks) == 0):
            if leg1_tick is None and len(leg1Ticks) > 0:
                leg1_tick = leg1Ticks.popitem(last=False)
            if leg2_tick is None and len(leg2Ticks) > 0:
                leg2_tick = leg2Ticks.popitem(last=False)

            if leg1_tick is None and leg2_tick is not None:
                self.newTick(leg2_tick[1])
                leg2_tick = None
            elif leg1_tick is not None and leg2_tick is None:
                self.newTick(leg1_tick[1])
                leg1_tick = None
            elif leg1_tick is not None and leg2_tick is not None:
                leg1 = leg1_tick[1]
                leg2 = leg2_tick[1]
                if leg1.datetime <= leg2.datetime:
                    self.newTick(leg1)
                    leg1_tick = None
                else:
                    self.newTick(leg2)
                    leg2_tick = None

    def runBackTestingWithNonStrArbTickFile2(self, leg1MainPath, leg2MainPath, leg1Symbol, leg2Symbol):
        """运行套利回测（使用本地tickcsv数据，数据从taobao标普购买)
        参数：
        leg1MainPath： leg1合约所在的市场路径
        leg2MainPath： leg2合约所在的市场路径
        leg1Symbol： leg1合约
        Leg2Symbol：leg2合约
        added by IncenseLee
        原始的tick，存放在相应市场下每天的目录中，目录包含市场各个合约的数据
        E:\ticks\SQ\201606\20160601\
                                     RB10.csv
                                     RB01.csv
                                     ....

        目录为交易日。
        按照回测的开始日期，到结束日期，循环每一天。

        读取eg1（如RB1610），读取Leg2（如RB701），根据两者tick的时间优先顺序，逐一tick灌输到策略的onTick中。
        """
        self.capital = self.initCapital  # 更新设置期初资金

        if not self.dataStartDate:
            self.writeCtaLog(u'回测开始日期未设置。')
            return
        # RB
        if len(self.symbol) < 1:
            self.writeCtaLog(u'回测对象未设置。')
            return

        if not self.dataEndDate:
            self.dataEndDate = datetime.today()

        # 首先根据回测模式，确认要使用的数据类
        if self.mode == self.BAR_MODE:
            self.writeCtaLog(u'本回测仅支持tick模式')
            return

        testdays = (self.dataEndDate - self.dataStartDate).days

        if testdays < 1:
            self.writeCtaLog(u'回测时间不足')
            return

        for i in range(0, testdays):
            testday = self.dataStartDate + timedelta(days=i)

            self.output(u'回测日期:{0}'.format(testday))

            # 加载运行每天数据
            self.__loadNotStdArbTicks2(leg1MainPath, leg2MainPath, testday, leg1Symbol, leg2Symbol)

            self.savingDailyData(testday, self.capital, self.maxCapital)


    def __loadTicksFromFile2(self, filepath, tickDate, vtSymbol):
        """从csv文件中UnicodeDictReader读取tick"""
        # 先读取数据到Dict，以日期时间为key
        ticks = OrderedDict()

        if not os.path.isfile(filepath):
            self.writeCtaLog(u'{0}文件不存在'.format(filepath))
            return ticks
        dt = None
        csvReadFile = file(filepath, 'rb')
        df = pd.read_csv(filepath, encoding='gbk')
        df.columns = ['date', 'time', 'lastPrice', 'lastVolume', 'totalInterest', 'position',
                      'bidPrice1', 'bidVolume1', 'bidPrice2', 'bidVolume2', 'bidPrice3', 'bidVolume3',
                      'askPrice1', 'askVolume1', 'askPrice2', 'askVolume2', 'askPrice3', 'askVolume3','BS']
        self.writeCtaLog(u'加载{0}'.format(filepath))
        for i in range(0,len(df)):
            #日期, 时间, 成交价, 成交量, 总量, 属性(持仓增减), B1价, B1量, B2价, B2量, B3价, B3量, S1价, S1量, S2价, S2量, S3价, S3量, BS
            # 0    1      2      3       4      5               6     7    8     9     10     11    12    13    14   15    16   17    18
            row = df.iloc[i].to_dict()

            tick = CtaTickData()

            tick.vtSymbol = vtSymbol
            tick.symbol = vtSymbol

            tick.date = row['date']
            tick.tradingDay = tickDate.strftime('%Y%m%d')
            tick.time = row['time']

            try:
                tick.datetime = datetime.strptime(tick.date + ' ' + tick.time, '%Y-%m-%d %H:%M:%S')
            except Exception as ex:
                self.writeCtaError(u'日期转换错误:{0},{1}:{2}'.format(tick.date + ' ' + tick.time, Exception, ex))
                continue

            tick.date = tick.datetime.strftime('%Y%m%d')
            # 修正毫秒
            if tick.datetime.replace(microsecond=0) == dt:
                # 与上一个tick的时间（去除毫秒后）相同,修改为500毫秒
                tick.datetime = tick.datetime.replace(microsecond=500)
                tick.time = tick.datetime.strftime('%H:%M:%S.%f')

            else:
                tick.datetime = tick.datetime.replace(microsecond=0)
                tick.time = tick.datetime.strftime('%H:%M:%S.%f')

            dt = tick.datetime

            tick.lastPrice = float(row['lastPrice'])
            tick.volume = int(float(row['lastVolume']))
            tick.bidPrice1 = float(row['bidPrice1'])  # 叫买价（价格低）
            tick.bidVolume1 = int(float(row['bidVolume1']))
            tick.askPrice1 = float(row['askPrice1'])  # 叫卖价（价格高）
            tick.askVolume1 = int(float(row['askVolume1']))

            # 排除涨停/跌停的数据
            if (tick.bidPrice1 == float('1.79769E308') and tick.bidVolume1 == 0) \
                    or (tick.askPrice1 == float('1.79769E308') and tick.askVolume1 == 0):
                continue

            dtStr = tick.date + ' ' + tick.time
            if dtStr in ticks:
                self.writeCtaError(u'日内数据重复，异常,数据时间为:{0}'.format(dtStr))
            else:
                ticks[dtStr] = tick

        return ticks

    def __loadNotStdArbTicks2(self, leg1MainPath, leg2MainPath, testday,  leg1Symbol, leg2Symbol):

        self.writeCtaLog(u'加载回测日期:{0}的价差tick'.format(testday))
        p = re.compile(r"([A-Z]+)[0-9]+",re.I)
        leg1_shortSymbol = p.match(leg1Symbol)
        leg2_shortSymbol = p.match(leg2Symbol)

        if leg1_shortSymbol is None or leg2_shortSymbol is None:
            self.writeCtaLog(u'{0},{1}不能正则分解'.format(leg1Symbol, leg2Symbol))
            return

        leg1_shortSymbol = leg1_shortSymbol.group(1)
        leg2_shortSymbol = leg2_shortSymbol.group(1)


        # E:\Ticks\SQ\2014\201401\20140102\ag01_20140102.csv
        leg1File = u'e:\\ticks\\{0}\\{1}\\{2}\\{3}\\{4}{5}_{3}.csv' \
            .format(leg1MainPath, testday.strftime('%Y'), testday.strftime('%Y%m'), testday.strftime('%Y%m%d'), leg1_shortSymbol, leg1Symbol[-2:])
        if not os.path.isfile(leg1File):
            self.writeCtaLog(u'{0}文件不存在'.format(leg1File))
            return

        leg2File = u'e:\\ticks\\{0}\\{1}\\{2}\\{3}\\{4}{5}_{3}.csv' \
            .format(leg2MainPath,testday.strftime('%Y'), testday.strftime('%Y%m'),  testday.strftime('%Y%m%d'), leg2_shortSymbol, leg2Symbol[-2:])
        if not os.path.isfile(leg2File):
            self.writeCtaLog(u'{0}文件不存在'.format(leg2File))
            return

        leg1Ticks = self.__loadTicksFromFile2(filepath=leg1File, tickDate=testday, vtSymbol=leg1Symbol)
        if len(leg1Ticks) == 0:
            self.writeCtaLog(u'{0}读取tick数为空'.format(leg1File))
            return

        leg2Ticks = self.__loadTicksFromFile2(filepath=leg2File, tickDate=testday, vtSymbol=leg2Symbol)
        if len(leg2Ticks) == 0:
            self.writeCtaLog(u'{0}读取tick数为空'.format(leg1File))
            return

        leg1_tick = None
        leg2_tick = None

        while not (len(leg1Ticks) == 0 or len(leg2Ticks) == 0):
            if leg1_tick is None and len(leg1Ticks) > 0:
                leg1_tick = leg1Ticks.popitem(last=False)
            if leg2_tick is None and len(leg2Ticks) > 0:
                leg2_tick = leg2Ticks.popitem(last=False)

            if leg1_tick is None and leg2_tick is not None:
                self.newTick(leg2_tick[1])
                leg2_tick = None
            elif leg1_tick is not None and leg2_tick is None:
                self.newTick(leg1_tick[1])
                leg1_tick = None
            elif leg1_tick is not None and leg2_tick is not None:
                leg1 = leg1_tick[1]
                leg2 = leg2_tick[1]
                if leg1.datetime <= leg2.datetime:
                    self.newTick(leg1)
                    leg1_tick = None
                else:
                    self.newTick(leg2)
                    leg2_tick = None
    #----------------------------------------------------------------------
    def runBackTestingWithBarFile(self, filename):
        """运行回测（使用本地csv数据)
        added by IncenseLee
        """
        self.capital = self.initCapital      # 更新设置期初资金
        if not filename:
            self.writeCtaLog(u'请指定回测数据文件')
            return

        if not self.dataStartDate:
            self.writeCtaLog(u'回测开始日期未设置。')
            return

        if not self.dataEndDate:
            self.dataEndDate = datetime.today()

        import os
        if not os.path.isfile(filename):
            self.writeCtaLog(u'{0}文件不存在'.format(filename))

        if len(self.symbol) < 1:
            self.writeCtaLog(u'回测对象未设置。')
            return

        # 首先根据回测模式，确认要使用的数据类
        if not self.mode == self.BAR_MODE:
            self.writeCtaLog(u'文件仅支持bar模式，若扩展tick模式，需要修改本方法')
            return

        self.output(u'开始回测')

        #self.strategy.inited = True
        self.strategy.onInit()
        self.output(u'策略初始化完成')

        self.strategy.trading = True
        self.strategy.onStart()
        self.output(u'策略启动完成')

        self.output(u'开始回放数据')

        import csv

        csvfile = file(filename,'rb')

        reader = csv.DictReader((line.replace('\0', '') for line in csvfile), delimiter=",")

        for row in reader:

            try:

                bar = CtaBarData()
                bar.symbol = self.symbol
                bar.vtSymbol = self.symbol

                # 从tb导出的csv文件
                #bar.open = float(row['Open'])
                #bar.high = float(row['High'])
                #bar.low = float(row['Low'])
                #bar.close = float(row['Close'])
                #bar.volume = float(row['TotalVolume'])#
                #barEndTime = datetime.strptime(row['Date']+' ' + row['Time'], '%Y/%m/%d %H:%M:%S')

                # 从ricequant导出的csv文件
                bar.open = float(row['open'])
                bar.high = float(row['high'])
                bar.low = float(row['low'])
                bar.close = float(row['close'])
                bar.volume = float(row['volume'])
                barEndTime = datetime.strptime(row['index'], '%Y-%m-%d %H:%M:%S')
                bar.tradingDay = row['trading_date']

                # 使用Bar的开始时间作为datetime
                bar.datetime = barEndTime - timedelta(seconds=self.barTimeInterval)

                bar.date = bar.datetime.strftime('%Y-%m-%d')
                bar.time = bar.datetime.strftime('%H:%M:%S')

                if not (bar.datetime < self.dataStartDate or bar.datetime >= self.dataEndDate):
                    self.newBar(bar)

            except Exception as ex:
                self.writeCtaLog(u'{0}:{1}'.format(Exception, ex))
                continue

    #----------------------------------------------------------------------
    def runBacktestingWithMysql(self):
        """运行回测(使用Mysql数据）
        added by IncenseLee
        """
        self.capital = self.initCapital      # 更新设置期初资金

        if not self.dataStartDate:
            self.writeCtaLog(u'回测开始日期未设置。')
            return

        if not self.dataEndDate:
            self.dataEndDate = datetime.today()

        if len(self.symbol)<1:
            self.writeCtaLog(u'回测对象未设置。')
            return

        # 首先根据回测模式，确认要使用的数据类
        if self.mode == self.BAR_MODE:
            dataClass = CtaBarData
            func = self.newBar
        else:
            dataClass = CtaTickData
            func = self.newTick

        self.output(u'开始回测')

        #self.strategy.inited = True
        self.strategy.onInit()
        self.output(u'策略初始化完成')

        self.strategy.trading = True
        self.strategy.onStart()
        self.output(u'策略启动完成')

        self.output(u'开始回放数据')


        # 每次获取日期周期
        intervalDays = 10

        for i in range (0,(self.dataEndDate - self.dataStartDate).days +1, intervalDays):
            d1 = self.dataStartDate + timedelta(days = i )

            if (self.dataEndDate - d1).days > intervalDays:
                d2 = self.dataStartDate + timedelta(days = i + intervalDays -1 )
            else:
                d2 = self.dataEndDate

            # 提取历史数据
            self.loadDataHistoryFromMysql(self.symbol, d1, d2)

            self.output(u'数据日期:{0} => {1}'.format(d1,d2))
            # 将逐笔数据推送
            for data in self.historyData:

                # 记录最新的TICK数据
                self.tick = self.__dataToTick(data)
                self.dt = self.tick.datetime

                # 处理限价单
                self.crossLimitOrder()
                self.crossStopOrder()

                # 推送到策略引擎中
                self.strategy.onTick(self.tick)

            # 清空历史数据
            self.historyData = []

        self.output(u'数据回放结束')

    #----------------------------------------------------------------------
    def runBacktesting(self):
        """运行回测"""

        self.capital = self.initCapital      # 更新设置期初资金

        # 载入历史数据
        #self.loadHistoryData()
        self.loadHistoryDataFromMongo()

        # 首先根据回测模式，确认要使用的数据类
        if self.mode == self.BAR_MODE:
            dataClass = CtaBarData
            func = self.newBar
        else:
            dataClass = CtaTickData
            func = self.newTick

        self.output(u'开始回测')
        
        self.strategy.inited = True
        self.strategy.onInit()
        self.output(u'策略初始化完成')
        
        self.strategy.trading = True
        self.strategy.onStart()
        self.output(u'策略启动完成')
        
        self.output(u'开始回放数据')

        for d in self.dbCursor:
            data = dataClass()
            data.__dict__ = d
            func(data)     
            
        self.output(u'数据回放结束')

    def __sendOnBarEvent(self, bar):
        """发送Bar的事件"""
        if self.eventEngine is not None:
            eventType = EVENT_ON_BAR + '_' + self.symbol
            event = Event(type_= eventType)
            event.dict_['data'] = bar
            self.eventEngine.put(event)

    # ----------------------------------------------------------------------
    def newBar(self, bar):
        """新的K线"""
        self.bar = bar
        self.dt = bar.datetime
        self.crossLimitOrder()      # 先撮合限价单
        self.crossStopOrder()       # 再撮合停止单
        self.strategy.onBar(bar)    # 推送K线到策略中
        self.__sendOnBarEvent(bar)  # 推送K线到事件

    #----------------------------------------------------------------------
    def newTick(self, tick):
        """新的Tick"""
        self.tick = tick
        self.dt = tick.datetime
        self.crossLimitOrder()
        self.crossStopOrder()
        self.strategy.onTick(tick)
        
    #----------------------------------------------------------------------
    def initStrategy(self, strategyClass, setting=None):
        """
        初始化策略
        setting是策略的参数设置，如果使用类中写好的默认设置则可以不传该参数
        """
        self.strategy = strategyClass(self, setting)
        if not self.strategy.name:
            self.strategy.name = self.strategy.className

        self.strategy.onInit()
        self.strategy.onStart()
        
    #----------------------------------------------------------------------
    def sendOrder(self, vtSymbol, orderType, price, volume, strategy):
        """发单"""

        self.writeCtaLog(u'{0},{1},{2}@{3}'.format(vtSymbol, orderType, price, volume))
        self.limitOrderCount += 1
        orderID = str(self.limitOrderCount)
        
        order = VtOrderData()
        order.vtSymbol = vtSymbol
        order.price = self.roundToPriceTick(price)
        order.totalVolume = volume
        order.status = STATUS_NOTTRADED     # 刚提交尚未成交
        order.orderID = orderID
        order.vtOrderID = orderID
        order.orderTime = str(self.dt)

        # added by IncenseLee
        order.gatewayName = self.gatewayName
        
        # CTA委托类型映射
        if orderType == CTAORDER_BUY:
            order.direction = DIRECTION_LONG
            order.offset = OFFSET_OPEN
        elif orderType == CTAORDER_SELL:
            order.direction = DIRECTION_SHORT
            order.offset = OFFSET_CLOSE
        elif orderType == CTAORDER_SHORT:
            order.direction = DIRECTION_SHORT
            order.offset = OFFSET_OPEN
        elif orderType == CTAORDER_COVER:
            order.direction = DIRECTION_LONG
            order.offset = OFFSET_CLOSE     

        # modified by IncenseLee
        key = u'{0}.{1}'.format(order.gatewayName, orderID)
        # 保存到限价单字典中
        self.workingLimitOrderDict[key] = order
        self.limitOrderDict[key] = order
        return key
    
    #----------------------------------------------------------------------
    def cancelOrder(self, vtOrderID):
        """撤单"""
        if vtOrderID in self.workingLimitOrderDict:
            order = self.workingLimitOrderDict[vtOrderID]
            order.status = STATUS_CANCELLED
            order.cancelTime = str(self.dt)
            del self.workingLimitOrderDict[vtOrderID]

    def cancelOrders(self, symbol, offset=EMPTY_STRING):
        """撤销所有单"""
        # Symbol参数:指定合约的撤单；
        # OFFSET参数:指定Offset的撤单,缺省不填写时，为所有
        self.writeCtaLog(u'从所有订单中撤销{0}\{1}'.format(offset, symbol))
        for vtOrderID in self.workingLimitOrderDict.keys():
            order = self.workingLimitOrderDict[vtOrderID]

            if offset == EMPTY_STRING:
                offsetCond = True
            else:
                offsetCond = order.offset == offset

            if order.symbol == symbol and offsetCond:
                self.writeCtaLog(u'撤销订单:{0},{1} {2}@{3}'.format(vtOrderID, order.direction, order.price, order.totalVolume))
                order.status = STATUS_CANCELLED
                order.cancelTime = str(self.dt)
                del self.workingLimitOrderDict[vtOrderID]

    #----------------------------------------------------------------------
    def sendStopOrder(self, vtSymbol, orderType, price, volume, strategy):
        """发停止单（本地实现）"""

        self.stopOrderCount += 1
        stopOrderID = STOPORDERPREFIX + str(self.stopOrderCount)
        
        so = StopOrder()
        so.vtSymbol = vtSymbol
        so.price = self.roundToPriceTick(price)
        so.volume = volume
        so.strategy = strategy
        so.stopOrderID = stopOrderID
        so.status = STOPORDER_WAITING
        
        if orderType == CTAORDER_BUY:
            so.direction = DIRECTION_LONG
            so.offset = OFFSET_OPEN
        elif orderType == CTAORDER_SELL:
            so.direction = DIRECTION_SHORT
            so.offset = OFFSET_CLOSE
        elif orderType == CTAORDER_SHORT:
            so.direction = DIRECTION_SHORT
            so.offset = OFFSET_OPEN
        elif orderType == CTAORDER_COVER:
            so.direction = DIRECTION_LONG
            so.offset = OFFSET_CLOSE           
        
        # 保存stopOrder对象到字典中
        self.stopOrderDict[stopOrderID] = so
        self.workingStopOrderDict[stopOrderID] = so
        
        return stopOrderID
    
    #----------------------------------------------------------------------
    def cancelStopOrder(self, stopOrderID):
        """撤销停止单"""
        # 检查停止单是否存在
        if stopOrderID in self.workingStopOrderDict:
            so = self.workingStopOrderDict[stopOrderID]
            so.status = STOPORDER_CANCELLED
            del self.workingStopOrderDict[stopOrderID]
            
    #----------------------------------------------------------------------
    def crossLimitOrder(self):
        """基于最新数据撮合限价单"""
        # 先确定会撮合成交的价格
        if self.mode == self.BAR_MODE:
            buyCrossPrice = self.bar.low        # 若买入方向限价单价格高于该价格，则会成交
            sellCrossPrice = self.bar.high      # 若卖出方向限价单价格低于该价格，则会成交
            buyBestCrossPrice = self.bar.open   # 在当前时间点前发出的买入委托可能的最优成交价
            sellBestCrossPrice = self.bar.open  # 在当前时间点前发出的卖出委托可能的最优成交价
            vtSymbol = self.bar.vtSymbol
        else:
            buyCrossPrice = self.tick.askPrice1
            sellCrossPrice = self.tick.bidPrice1
            buyBestCrossPrice = self.tick.askPrice1
            sellBestCrossPrice = self.tick.bidPrice1
            vtSymbol = self.tick.vtSymbol
        
        # 遍历限价单字典中的所有限价单
        for orderID, order in self.workingLimitOrderDict.items():
            # 判断是否会成交
            buyCross = order.direction == DIRECTION_LONG and order.price >= buyCrossPrice and vtSymbol == order.vtSymbol
            sellCross = order.direction == DIRECTION_SHORT and order.price <= sellCrossPrice and vtSymbol == order.vtSymbol
            
            # 如果发生了成交
            if buyCross or sellCross:
                # 推送成交数据
                self.tradeCount += 1            # 成交编号自增1

                tradeID = str(self.tradeCount)
                trade = VtTradeData()
                trade.vtSymbol = order.vtSymbol
                trade.tradeID = tradeID
                trade.vtTradeID = tradeID
                trade.orderID = order.orderID
                trade.vtOrderID = order.orderID
                trade.direction = order.direction
                trade.offset = order.offset
                
                # 以买入为例：
                # 1. 假设当根K线的OHLC分别为：100, 125, 90, 110
                # 2. 假设在上一根K线结束(也是当前K线开始)的时刻，策略发出的委托为限价105
                # 3. 则在实际中的成交价会是100而不是105，因为委托发出时市场的最优价格是100
                if buyCross:
                    trade.price = min(order.price, buyBestCrossPrice)
                    self.strategy.pos += order.totalVolume
                else:
                    trade.price = max(order.price, sellBestCrossPrice)
                    self.strategy.pos -= order.totalVolume
                
                trade.volume = order.totalVolume
                trade.tradeTime = str(self.dt)
                trade.dt = self.dt
                self.strategy.onTrade(trade)
                
                self.tradeDict[tradeID] = trade
                self.writeCtaLog(u'TradeId:{0}'.format(tradeID))
                
                # 推送委托数据
                order.tradedVolume = order.totalVolume
                order.status = STATUS_ALLTRADED

                self.strategy.onOrder(order)
                
                # 从字典中删除该限价单
                try:
                    del self.workingLimitOrderDict[orderID]
                except Exception as ex:
                    self.writeCtaError(u'{0}:{1}'.format(Exception, ex))

                # 实时计算模式
                if self.calculateMode == self.REALTIME_MODE:
                    self.realtimeCalculate()
                
    #----------------------------------------------------------------------
    def crossStopOrder(self):
        """基于最新数据撮合停止单"""
        # 先确定会撮合成交的价格，这里和限价单规则相反
        if self.mode == self.BAR_MODE:
            buyCrossPrice = self.bar.high    # 若买入方向停止单价格低于该价格，则会成交
            sellCrossPrice = self.bar.low    # 若卖出方向限价单价格高于该价格，则会成交
            bestCrossPrice = self.bar.open   # 最优成交价，买入停止单不能低于，卖出停止单不能高于
            vtSymbol = self.bar.vtSymbol
        else:
            buyCrossPrice = self.tick.lastPrice
            sellCrossPrice = self.tick.lastPrice
            bestCrossPrice = self.tick.lastPrice
            vtSymbol = self.tick.vtSymbol
        
        # 遍历停止单字典中的所有停止单
        for stopOrderID, so in self.workingStopOrderDict.items():
            # 判断是否会成交
            buyCross = so.direction == DIRECTION_LONG and so.price <= buyCrossPrice and vtSymbol == so.vtSymbol
            sellCross = so.direction == DIRECTION_SHORT and so.price >= sellCrossPrice and vtSymbol == so.vtSymbol
            
            # 如果发生了成交
            if buyCross or sellCross:
                # 推送成交数据
                self.tradeCount += 1            # 成交编号自增1
                tradeID = str(self.tradeCount)
                trade = VtTradeData()
                trade.vtSymbol = so.vtSymbol
                trade.tradeID = tradeID
                trade.vtTradeID = tradeID
                
                if buyCross:
                    self.strategy.pos += so.volume
                    trade.price = max(bestCrossPrice, so.price)
                else:
                    self.strategy.pos -= so.volume
                    trade.price = min(bestCrossPrice, so.price)                
                
                self.limitOrderCount += 1
                orderID = str(self.limitOrderCount)
                trade.orderID = orderID
                trade.vtOrderID = orderID
                
                trade.direction = so.direction
                trade.offset = so.offset
                trade.volume = so.volume
                trade.tradeTime = str(self.dt)
                trade.dt = self.dt
                self.strategy.onTrade(trade)
                
                self.tradeDict[tradeID] = trade
                
                # 推送委托数据
                so.status = STOPORDER_TRIGGERED
                
                order = VtOrderData()
                order.vtSymbol = so.vtSymbol
                order.symbol = so.vtSymbol
                order.orderID = orderID
                order.vtOrderID = orderID
                order.direction = so.direction
                order.offset = so.offset
                order.price = so.price
                order.totalVolume = so.volume
                order.tradedVolume = so.volume
                order.status = STATUS_ALLTRADED
                order.orderTime = trade.tradeTime
                self.strategy.onOrder(order)
                
                self.limitOrderDict[orderID] = order
                
                # 从字典中删除该限价单
                if stopOrderID in self.workingStopOrderDict:
                    del self.workingStopOrderDict[stopOrderID]

                # 若采用实时计算净值
                if self.calculateMode == self.REALTIME_MODE:
                    self.realtimeCalculate()


    #----------------------------------------------------------------------
    def insertData(self, dbName, collectionName, data):
        """考虑到回测中不允许向数据库插入数据，防止实盘交易中的一些代码出错"""
        pass
    
    #----------------------------------------------------------------------
    def loadBar(self, dbName, collectionName, startDate):
        """直接返回初始化数据列表中的Bar"""
        return self.initData
    
    #----------------------------------------------------------------------
    def loadTick(self, dbName, collectionName, startDate):
        """直接返回初始化数据列表中的Tick"""
        return self.initData
    
    #----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """记录日志"""
        #log = str(self.dt) + ' ' + content
        #self.logList.append(log)

        # 写入本地log日志
        logging.info(content)

    def writeCtaError(self, content):
        """记录异常"""
        self.output(content)
        self.writeCtaLog(content)

    #----------------------------------------------------------------------
    def output(self, content):
        """输出内容"""
        print str(datetime.now()) + "\t" + content

    def realtimeCalculate(self):
        """实时计算交易结果"""

        resultDict = OrderedDict()  # 交易结果记录

        longTrade = []              # 未平仓的多头交易
        shortTrade = []             # 未平仓的空头交易
        longid = EMPTY_STRING
        shortid = EMPTY_STRING

        no_match_shortTrade = False
        no_match_longTrade = False

        # 对交易记录逐一处理
        for tradeid in self.tradeDict.keys():
            trade = self.tradeDict[tradeid]
            # 多头交易
            if trade.direction == DIRECTION_LONG:
                # 存在空单
                if len(shortTrade)>0:
                    # 检查是否存在与Symbol一致的空单
                    pop_indexs = [i for i, val in enumerate(shortTrade) if val.vtSymbol == trade.vtSymbol]
                    if len(pop_indexs) < 1:
                        #self.output(u'空头交易清单，没有{0}的空单'.format(trade.vtSymbol))
                        no_match_shortTrade = True

                # 如果尚无空单
                if len(shortTrade) == 0 or no_match_shortTrade:
                    #self.output(u'{0}多开:{1},{2}'.format(trade.vtSymbol, trade.volume, trade.price))
                    #self.writeCtaLog(u'{0}多开:{1},{2}'.format(trade.vtSymbol, trade.volume, trade.price))
                    longTrade.append(trade)
                    longid = tradeid
                    no_match_shortTrade = False

                # 当前多头交易为平空
                else:
                    gId = tradeid    # 交易组（多个平仓数为一组）
                    gr = None       # 组合的交易结果

                    coverVolume = trade.volume

                    while coverVolume > 0:
                        if len(shortTrade)==0:
                            self.writeCtaError(u'异常，没有开空仓的数据')
                            break
                        pop_indexs = [i for i, val in enumerate(shortTrade) if val.vtSymbol == trade.vtSymbol]
                        if len(pop_indexs) < 1:
                            self.writeCtaError(u'没有对应的symbol:{0}开空仓数据'.format(trade.vtSymbol))
                            break
                        pop_index = pop_indexs[0]
                        # 从未平仓的空头交易
                        entryTrade = shortTrade.pop(pop_index)

                        # 开空volume，不大于平仓volume
                        if coverVolume >= entryTrade.volume:
                            self.writeCtaLog(u'coverVolume:{0} >= entryTrade.volume:{1}'.format(coverVolume, entryTrade.volume))
                            coverVolume = coverVolume - entryTrade.volume

                            #self.output(u'{0}空平:{1},{2}'.format(entryTrade.vtSymbol, entryTrade.volume, trade.price))
                            #self.writeCtaLog(u'{0}空平:{1},{2}'.format(entryTrade.vtSymbol, entryTrade.volume, trade.price))

                            result = TradingResult(entryPrice=entryTrade.price,
                                                   entryDt=entryTrade.dt,
                                                   exitPrice=trade.price,
                                                   exitDt=trade.dt,
                                                   volume=-entryTrade.volume,
                                                   rate=self.rate,
                                                   slippage=self.slippage,
                                                   size=self.size,
                                                   groupId=gId,
                                                   fixcommission=self.fixCommission)

                            t = {}
                            t['vtSymbol'] = entryTrade.vtSymbol
                            t['OpenTime'] = entryTrade.tradeTime
                            t['OpenPrice'] = entryTrade.price
                            t['Direction'] = u'Short'
                            t['CloseTime'] = trade.tradeTime
                            t['ClosePrice'] = trade.price
                            t['Volume'] = entryTrade.volume
                            t['Profit'] = result.pnl
                            self.exportTradeList.append(t)

                            msg = u'Gid:{0} {1}[{2}:开空tid={3}:{4}]-[{5}.平空tid={6},{7},vol:{8}],净盈亏：{9}'\
                                .format(gId, entryTrade.vtSymbol, entryTrade.tradeTime, shortid, entryTrade.price,
                                                     trade.tradeTime, tradeid, trade.price,
                                                     entryTrade.volume, result.pnl)
                            self.output(msg)

                            self.writeCtaLog(msg)

                            if type(gr) == type(None):
                                if coverVolume > 0:
                                    # 属于组合
                                    gr = copy.deepcopy(result)

                                    # 删除开空交易单
                                    del self.tradeDict[entryTrade.tradeID]

                                else:
                                    # 不属于组合
                                    resultDict[entryTrade.dt] = result

                                    # 删除平空交易单，
                                    del self.tradeDict[trade.tradeID]
                                    # 删除开空交易单
                                    del self.tradeDict[entryTrade.tradeID]

                            else:
                                # 更新组合的数据
                                gr.turnover = gr.turnover + result.turnover
                                gr.commission = gr.commission + result.commission
                                gr.slippage = gr.slippage + result.slippage
                                gr.pnl = gr.pnl + result.pnl

                                # 删除开空交易单
                                del self.tradeDict[entryTrade.tradeID]

                                # 所有仓位平完
                                if coverVolume == 0:
                                    gr.volume = trade.volume
                                    resultDict[entryTrade.dt] = gr
                                    # 删除平空交易单，
                                    del self.tradeDict[trade.tradeID]

                        # 开空volume,大于平仓volume，需要更新减少tradeDict的数量。
                        else:
                            self.writeCtaLog(u'Short volume:{0} > Cover volume:{1}，需要更新减少tradeDict的数量。'.format(entryTrade.volume,coverVolume))
                            shortVolume = entryTrade.volume - coverVolume

                            result = TradingResult(entryPrice=entryTrade.price,
                                                   entryDt=entryTrade.dt,
                                                   exitPrice=trade.price,
                                                   exitDt=trade.dt,
                                                   volume=-coverVolume,
                                                   rate=self.rate,
                                                   slippage=self.slippage,
                                                   size=self.size,
                                                   groupId=gId,
                                                   fixcommission=self.fixCommission)

                            t = {}
                            t['vtSymbol'] = entryTrade.vtSymbol
                            t['OpenTime'] = entryTrade.tradeTime
                            t['OpenPrice'] = entryTrade.price
                            t['Direction'] = u'Short'
                            t['CloseTime'] = trade.tradeTime
                            t['ClosePrice'] = trade.price
                            t['Volume'] = coverVolume
                            t['Profit'] = result.pnl
                            self.exportTradeList.append(t)

                            msg = u'Gid:{0} {1}[{2}:开空tid={3}:{4}]-[{5}.平空tid={6},{7},vol:{8}],净盈亏：{9}'\
                                .format(gId, entryTrade.vtSymbol, entryTrade.tradeTime, shortid, entryTrade.price,
                                                     trade.tradeTime, tradeid, trade.price,
                                                     coverVolume, result.pnl)
                            self.output(msg)
                            self.writeCtaLog(msg)

                            # 更新（减少）开仓单的volume,重新推进开仓单列表中
                            entryTrade.volume = shortVolume
                            shortTrade.append(entryTrade)

                            coverVolume = 0

                            if type(gr) == type(None):
                                resultDict[entryTrade.dt] = result

                            else:
                                # 更新组合的数据
                                gr.turnover = gr.turnover + result.turnover
                                gr.commission = gr.commission + result.commission
                                gr.slippage = gr.slippage + result.slippage
                                gr.pnl = gr.pnl + result.pnl
                                gr.volume = trade.volume
                                resultDict[entryTrade.dt] = gr

                            # 删除平空交易单，
                            del self.tradeDict[trade.tradeID]

                    if type(gr) != type(None):
                        self.writeCtaLog(u'组合净盈亏:{0}'.format(gr.pnl))

                    self.writeCtaLog(u'-------------')

            # 空头交易
            else:
                if len(longTrade) > 0:
                    pop_indexs = [i for i, val in enumerate(longTrade) if val.vtSymbol == trade.vtSymbol]
                    if len(pop_indexs) < 1:
                        #self.output(u'多头交易清单，没有{0}的多单'.format(trade.vtSymbol))
                        no_match_longTrade = True

                # 如果尚无多单
                if len(longTrade) == 0 or no_match_longTrade:
                    #self.output(u'{0}空开:{1},{2}'.format(trade.vtSymbol, trade.volume, trade.price))
                    #self.writeCtaLog(u'{0}空开:{1},{2}'.format(trade.vtSymbol, trade.volume, trade.price))
                    shortTrade.append(trade)
                    shortid = tradeid
                    no_match_longTrade = False

                # 当前空头交易为平多
                else:
                    gId = tradeid       # 交易组（多个平仓数为一组）                                                                                                                                    s
                    gr = None           # 组合的交易结果

                    sellVolume = trade.volume

                    while sellVolume > 0:
                        if len(longTrade) == 0:
                            self.writeCtaError(u'异常，没有开多单')
                            break

                        pop_indexs = [i for i, val in enumerate(longTrade) if val.vtSymbol == trade.vtSymbol]
                        if len(pop_indexs) < 1:
                            self.writeCtaError(u'没有对应的symbol{0}开多仓数据,'.format(trade.vtSymbol))
                            break

                        pop_index = pop_indexs[0]

                        entryTrade = longTrade.pop(pop_index)

                         # 开多volume，不大于平仓volume
                        if sellVolume >= entryTrade.volume:
                            self.writeCtaLog(u'{0}Sell Volume:{1} >= Entry Volume:{2}'.format(entryTrade.vtSymbol, sellVolume, entryTrade.volume))
                            sellVolume = sellVolume - entryTrade.volume
                            #self.output(u'{0}多平:{1},{2}'.format(entryTrade.vtSymbol, entryTrade.volume, trade.price))
                            #self.writeCtaLog(u'{0}多平:{1},{2}'.format(entryTrade.vtSymbol, entryTrade.volume, trade.price))


                            result = TradingResult(entryPrice=entryTrade.price,
                                                   entryDt=entryTrade.dt,
                                                   exitPrice=trade.price,
                                                   exitDt=trade.dt,
                                                   volume=entryTrade.volume,
                                                   rate=self.rate,
                                                   slippage=self.slippage,
                                                   size=self.size,
                                                   groupId=gId,
                                                   fixcommission=self.fixCommission)

                            t = {}
                            t['vtSymbol'] = entryTrade.vtSymbol
                            t['OpenTime'] = entryTrade.tradeTime
                            t['OpenPrice'] = entryTrade.price
                            t['Direction'] = u'Long'
                            t['CloseTime'] = trade.tradeTime
                            t['ClosePrice'] = trade.price
                            t['Volume'] = entryTrade.volume
                            t['Profit'] = result.pnl
                            self.exportTradeList.append(t)

                            msg = u'Gid:{0} {1}[{2}:开多tid={3}:{4}]-[{5}.平多tid={6},{7},vol:{8}],净盈亏：{9}'\
                                .format(gId, entryTrade.vtSymbol,
                                            entryTrade.tradeTime, longid, entryTrade.price,
                                            trade.tradeTime, tradeid, trade.price,
                                            entryTrade.volume, result.pnl)
                            self.output(msg)
                            self.writeCtaLog(msg)

                            if type(gr) == type(None):
                                if sellVolume > 0:
                                    # 属于组合
                                    gr = copy.deepcopy(result)
                                    # 删除开多交易单
                                    del self.tradeDict[entryTrade.tradeID]

                                else:
                                    # 不属于组合
                                    resultDict[entryTrade.dt] = result

                                    # 删除平多交易单，
                                    del self.tradeDict[trade.tradeID]
                                    # 删除开多交易单
                                    del self.tradeDict[entryTrade.tradeID]

                            else:
                                # 更新组合的数据
                                gr.turnover = gr.turnover + result.turnover
                                gr.commission = gr.commission + result.commission
                                gr.slippage = gr.slippage + result.slippage
                                gr.pnl = gr.pnl + result.pnl

                                # 删除开多交易单
                                del self.tradeDict[entryTrade.tradeID]

                                if sellVolume == 0:
                                    gr.volume = trade.volume
                                    resultDict[entryTrade.dt] = gr
                                    # 删除平多交易单，
                                    del self.tradeDict[trade.tradeID]

                        # 开多volume,大于平仓volume，需要更新减少tradeDict的数量。
                        else:
                            longVolume = entryTrade.volume -sellVolume
                            self.writeCtaLog(u'Long Volume:{0} > sell Volume:{1}'.format(entryTrade.volume,sellVolume))

                            result = TradingResult(entryPrice=entryTrade.price,
                                                   entryDt=entryTrade.dt,
                                                   exitPrice=trade.price,
                                                   exitDt=trade.dt,
                                                   volume=sellVolume,
                                                   rate=self.rate,
                                                   slippage=self.slippage,
                                                   size=self.size,
                                                   groupId=gId,
                                                   fixcommission=self.fixCommission)

                            t = {}
                            t['vtSymbol'] = entryTrade.vtSymbol
                            t['OpenTime'] = entryTrade.tradeTime
                            t['OpenPrice'] = entryTrade.price
                            t['Direction'] = u'Long'
                            t['CloseTime'] = trade.tradeTime
                            t['ClosePrice'] = trade.price
                            t['Volume'] = sellVolume
                            t['Profit'] = result.pnl
                            self.exportTradeList.append(t)

                            self.writeCtaLog(u'Gid:{0} {1}[{2}:开多tid={3}:{4}]-[{5}.平多tid={6},{7},vol:{8}],净盈亏：{9}'
                                             .format(gId, entryTrade.vtSymbol,entryTrade.tradeTime, longid, entryTrade.price,
                                                     trade.tradeTime, tradeid, trade.price,
                                                     sellVolume, result.pnl))

                            # 减少开多volume,重新推进开多单列表中
                            entryTrade.volume = longVolume
                            longTrade.append(entryTrade)

                            sellVolume = 0

                            if type(gr) == type(None):
                                resultDict[entryTrade.dt] = result

                            else:
                                # 更新组合的数据
                                gr.turnover = gr.turnover + result.turnover
                                gr.commission = gr.commission + result.commission
                                gr.slippage = gr.slippage + result.slippage
                                gr.pnl = gr.pnl + result.pnl
                                gr.volume = trade.volume
                                resultDict[entryTrade.dt] = gr

                            # 删除平多交易单，
                            del self.tradeDict[trade.tradeID]

                    if type(gr) != type(None):
                        self.writeCtaLog(u'组合净盈亏:{0}'.format(gr.pnl))

                    self.writeCtaLog(u'-------------')

        # 计算仓位比例
        occupyMoney = EMPTY_FLOAT
        occupyLongVolume = EMPTY_INT
        occupyShortVolume = EMPTY_INT
        if len(longTrade) > 0:
            for t in longTrade:
                occupyMoney += t.price * abs(t.volume) * self.size * self.margin_rate
                occupyLongVolume += abs(t.volume)
        if len(shortTrade) > 0:
            for t in shortTrade:
                occupyMoney += t.price * abs(t.volume) * self.size * self.margin_rate
                occupyShortVolume += (t.volume)

        self.output(u'occupyLongVolume:{0},occupyShortVolume:{1}'.format(occupyLongVolume,occupyShortVolume))
        self.writeCtaLog(u'occupyLongVolume:{0},occupyShortVolume:{1}'.format(occupyLongVolume, occupyShortVolume))
        # 最大持仓
        self.maxVolume = max(self.maxVolume, occupyLongVolume + occupyShortVolume)

        self.avaliable = self.capital - occupyMoney
        self.percent = round(float(occupyMoney * 100 / self.capital), 2)

        # 检查是否有平交易
        if not resultDict:

            msg = u''
            if len(longTrade) > 0:
                msg += u'持多仓{0},'.format(occupyLongVolume)

            if len(shortTrade) > 0:
                msg += u'持空仓{0},'.format(occupyShortVolume)

            msg += u'资金占用:{0},仓位:{1}'.format(occupyMoney, self.percent)
            self.output(msg)
            self.writeCtaLog(msg)
            return

        # 对交易结果汇总统计
        for time, result in resultDict.items():

            if result.pnl > 0:
                self.winningResult += 1
                self.totalWinning += result.pnl
            else:
                self.losingResult += 1
                self.totalLosing += result.pnl
            self.capital += result.pnl
            self.maxCapital = max(self.capital, self.maxCapital)
            #self.maxVolume = max(self.maxVolume, result.volume)
            drawdown = self.capital - self.maxCapital
            drawdownRate = round(float(drawdown*100/self.maxCapital),4)

            self.pnlList.append(result.pnl)
            self.timeList.append(time)
            self.capitalList.append(self.capital)
            self.drawdownList.append(drawdown)
            self.drawdownRateList.append(drawdownRate)

            self.totalResult += 1
            self.totalTurnover += result.turnover
            self.totalCommission += result.commission
            self.totalSlippage += result.slippage

            self.output(u'[{5}],{6} Vol:{0},盈亏:{1},回撤:{2}/{3},权益:{4}'.
                        format(abs(result.volume), result.pnl, drawdown,
                               drawdownRate, self.capital, result.groupId, time))

        # 重新计算一次avaliable
        self.avaliable = self.capital - occupyMoney
        self.percent = round(float(occupyMoney * 100 / self.capital), 2)

    def savingDailyData(self, d, c, m):
        """保存每日数据"""
        dict = {}
        dict['date'] = d.strftime('%Y/%m/%d')
        dict['capital'] = c
        dict['maxCapital'] = m
        dict['rate'] = c / self.initCapital
        self.dailyList.append(dict)

    # ----------------------------------------------------------------------
    def calculateBacktestingResult(self):
        """
        计算回测结果
        Modified by Incense Lee
        增加了支持逐步加仓的计算：
        例如，前面共有6次开仓（1手开仓+5次加仓，每次1手），平仓只有1次（六手）。那么，交易次数是6次（开仓+平仓）。
        暂不支持每次加仓数目不一致的核对（因为比较复杂）

        增加组合的支持。（组合中，仍然按照1手逐步加仓和多手平仓的方法，即使启用了复利模式，也仍然按照这个规则，只是在计算收益时才乘以系数）

        增加期初权益，每次交易后的权益，可用资金，仓位比例。

        """
        self.output(u'计算回测结果')
        
        # 首先基于回测后的成交记录，计算每笔交易的盈亏
        resultDict = OrderedDict()  # 交易结果记录
        longTrade = []              # 未平仓的多头交易
        shortTrade = []             # 未平仓的空头交易

        i = 1

        tradeUnit = 1

        longid = EMPTY_STRING
        shortid = EMPTY_STRING

        for tradeid in self.tradeDict.keys():

            trade = self.tradeDict[tradeid]

            # 多头交易
            if trade.direction == DIRECTION_LONG:
                # 如果尚无空头交易
                if not shortTrade:
                    longTrade.append(trade)
                    longid = tradeid
                # 当前多头交易为平空
                else:
                    gId = i     # 交易组（多个平仓数为一组）
                    gt = 1      # 组合的交易次数
                    gr = None   # 组合的交易结果

                    if trade.volume >tradeUnit:
                        self.writeCtaLog(u'平仓数{0},组合编号:{1}'.format(trade.volume,gId))
                        gt = int(trade.volume/tradeUnit)

                    for tv in range(gt):

                        entryTrade = shortTrade.pop(0)

                        result = TradingResult(entryPrice=entryTrade.price,
                                               entryDt=entryTrade.dt,
                                               exitPrice=trade.price,
                                               exitDt=trade.dt,
                                               volume=-tradeUnit,
                                               rate=self.rate,
                                               slippage=self.slippage,
                                               size=self.size,
                                               groupId=gId,
                                               fixcommission=self.fixCommission)


                        if tv == 0:
                            if gt == 1:
                                resultDict[entryTrade.dt] = result
                            else:
                                gr = copy.deepcopy(result)
                        else:
                            gr.turnover = gr.turnover + result.turnover
                            gr.commission = gr.commission + result.commission
                            gr.slippage = gr.slippage + result.slippage
                            gr.pnl = gr.pnl + result.pnl

                            if tv == gt -1:
                                gr.volume = trade.volume
                                resultDict[entryTrade.dt] = gr

                        t = {}
                        t['OpenTime'] = entryTrade.tradeTime.strftime('%Y/%m/%d %H:%M:%S')
                        t['OpenPrice'] = entryTrade.price
                        t['Direction'] = u'Short'
                        t['CloseTime'] = trade.tradeTime.strftime('%Y/%m/%d %H:%M:%S')
                        t['ClosePrice'] = trade.price
                        t['Volume'] = tradeUnit
                        t['Profit'] = result.pnl
                        self.exportTradeList.append(t)

                        self.writeCtaLog(u'{9}@{6} [{7}:开空{0},short:{1}]-[{8}:平空{2},cover:{3},vol:{4}],净盈亏:{5}'
                                    .format(entryTrade.tradeTime, entryTrade.price,
                                            trade.tradeTime, trade.price, tradeUnit, result.pnl,
                                            i, shortid, tradeid, gId))
                        i = i+1

                    if type(gr) != type(None):
                        self.writeCtaLog(u'组合净盈亏:{0}'.format(gr.pnl))

                    self.writeCtaLog(u'-------------')

            # 空头交易        
            else:
                # 如果尚无多头交易
                if not longTrade:
                    shortTrade.append(trade)
                    shortid = tradeid
                # 当前空头交易为平多
                else:
                    gId = i     # 交易组（多个平仓数为一组）
                    gt = 1      # 组合的交易次数
                    gr = None   # 组合的交易结果

                    if trade.volume >tradeUnit:
                        self.writeCtaLog(u'平仓数{0},组合编号:{1}'.format(trade.volume,gId))
                        gt = int(trade.volume/tradeUnit)

                    for tv in range(gt):

                        entryTrade = longTrade.pop(0)

                        result = TradingResult(entryPrice=entryTrade.price,
                                               entryDt=entryTrade.dt,
                                               exitPrice=trade.price,
                                               exitDt=trade.dt,
                                               volume=tradeUnit,
                                               rate=self.rate,
                                               slippage=self.slippage,
                                               size=self.size,
                                               groupId=gId,
                                               fixcommission=self.fixCommission)
                        if tv == 0:
                            if gt==1:
                                resultDict[entryTrade.dt] = result
                            else:
                                gr = copy.deepcopy(result)
                        else:
                            gr.turnover = gr.turnover + result.turnover
                            gr.commission = gr.commission + result.commission
                            gr.slippage = gr.slippage + result.slippage
                            gr.pnl = gr.pnl + result.pnl

                            if tv == gt -1:
                                gr.volume = trade.volume
                                resultDict[entryTrade.dt] = gr

                        t = {}
                        t['OpenTime'] = entryTrade.tradeTime.strftime('%Y/%m/%d %H:%M:%S')
                        t['OpenPrice'] = entryTrade.price
                        t['Direction'] = u'Long'
                        t['CloseTime'] = trade.tradeTime.strftime('%Y/%m/%d %H:%M:%S')
                        t['ClosePrice'] = trade.price
                        t['Volume'] = tradeUnit
                        t['Profit'] = result.pnl
                        self.exportTradeList.append(t)


                        self.writeCtaLog(u'{9}@{6} [{7}:开多{0},buy:{1}]-[{8}.平多{2},sell:{3},vol:{4}],净盈亏：{5}'
                                    .format(entryTrade.tradeTime, entryTrade.price,
                                            trade.tradeTime,trade.price, tradeUnit, result.pnl,
                                            i, longid, tradeid, gId))
                        i = i+1

                    if type(gr) != type(None):
                        self.writeCtaLog(u'组合净盈亏:{0}'.format(gr.pnl))

                    self.writeCtaLog(u'-------------')

        # 检查是否有交易
        if not resultDict:
            self.output(u'无交易结果')
            return {}
        
        # 然后基于每笔交易的结果，我们可以计算具体的盈亏曲线和最大回撤等

        """
        initCapital = 40000     # 期初资金
        capital = initCapital   # 资金
        maxCapital = initCapital          # 资金最高净值

        maxPnl = 0              # 最高盈利
        minPnl = 0              # 最大亏损
        maxVolume = 1             # 最大仓位数

        wins = 0

        totalResult = 0         # 总成交数量
        totalTurnover = 0       # 总成交金额（合约面值）
        totalCommission = 0     # 总手续费
        totalSlippage = 0       # 总滑点

        timeList = []           # 时间序列
        pnlList = []            # 每笔盈亏序列
        capitalList = []        # 盈亏汇总的时间序列
        drawdownList = []       # 回撤的时间序列
        drawdownRateList = []   # 最大回撤比例的时间序列
        """
        drawdown = 0            # 回撤
        compounding = 1        # 简单的复利基数（如果资金是期初资金的x倍，就扩大开仓比例,例如3w开1手，6w开2手，12w开4手)

        for time, result in resultDict.items():

            # 是否使用简单复利
            if self.usageCompounding:
                compounding = int(self.capital/self.initCapital)

            if result.pnl > 0:
                self.winningResult += 1
                self.totalWinning += result.pnl
            else:
                self.losingResult += 1
                self.totalLosing += result.pnl

            self.capital += result.pnl*compounding
            self.maxCapital = max(self.capital, self.maxCapital)
            self.maxVolume = max(self.maxVolume, result.volume*compounding)
            drawdown = self.capital - self.maxCapital
            drawdownRate = round(float(drawdown*100/self.maxCapital),4)

            self.pnlList.append(result.pnl*compounding)
            self.timeList.append(time)
            self.capitalList.append(self.capningital)
            self.drawdownList.append(drawdown)
            self.drawdownRateList.append(drawdownRate)

            self.totalResult += 1
            self.totalTurnover += result.turnover*compounding
            self.totalCommission += result.commission*compounding
            self.totalSlippage += result.slippage*compounding

    # ---------------------------------------------------------------------
    def exportTradeResult(self):
        """到处回测结果表"""
        if not self.exportTradeList:
            return
        csvOutputFile = os.path.abspath(os.path.join(os.path.dirname(__file__), 'TestLogs',
                                                     'TradeList_{0}.csv'.format(datetime.now().strftime('%Y%m%d_%H%M'))))

        import csv
        csvWriteFile = file(csvOutputFile, 'wb')
        fieldnames = ['vtSymbol','OpenTime', 'OpenPrice', 'Direction', 'CloseTime', 'ClosePrice', 'Volume', 'Profit']
        writer = csv.DictWriter(f=csvWriteFile, fieldnames=fieldnames, dialect='excel')
        writer.writeheader()

        for row in self.exportTradeList:
            writer.writerow(row)

        if not self.dailyList:
            return

        csvOutputFile2 = os.path.abspath(os.path.join(os.path.dirname(__file__), 'TestLogs',
                                     'DailyList_{0}.csv'.format(datetime.now().strftime('%Y%m%d_%H%M'))))

        csvWriteFile2 = file(csvOutputFile2, 'wb')
        fieldnames = ['date','capital', 'maxCapital','rate']
        writer2 = csv.DictWriter(f=csvWriteFile2, fieldnames=fieldnames, dialect='excel')
        writer2.writeheader()

        for row in self.dailyList:
            writer2.writerow(row)


    def getResult(self):
        # 返回回测结果
        d = {}
        d['initCapital'] = self.initCapital
        d['capital'] = self.capital - self.initCapital
        d['maxCapital'] = self.maxCapital

        if len(self.pnlList)  == 0:
            return {}

        d['maxPnl'] = max(self.pnlList)
        d['minPnl'] = min(self.pnlList)

        d['maxVolume'] = self.maxVolume
        d['totalResult'] = self.totalResult
        d['totalTurnover'] = self.totalTurnover
        d['totalCommission'] = self.totalCommission
        d['totalSlippage'] = self.totalSlippage
        d['timeList'] = self.timeList
        d['pnlList'] = self.pnlList
        d['capitalList'] = self.capitalList
        d['drawdownList'] = self.drawdownList
        d['drawdownRateList'] = self.drawdownRateList
        d['winningRate'] = round(100 * self.winningResult / len(self.pnlList), 4)

        averageWinning = 0  # 这里把数据都初始化为0
        averageLosing = 0
        profitLossRatio = 0

        if self.winningResult:
            averageWinning = self.totalWinning / self.winningResult  # 平均每笔盈利
        if self.losingResult:
            averageLosing = self.totalLosing / self.losingResult  # 平均每笔亏损
        if averageLosing:
            profitLossRatio = -averageWinning / averageLosing  # 盈亏比

        d['averageWinning'] = averageWinning
        d['averageLosing'] = averageLosing
        d['profitLossRatio'] = profitLossRatio

        return d

    #----------------------------------------------------------------------
    def showBacktestingResult(self):
        """显示回测结果"""
        if self.calculateMode != self.REALTIME_MODE:
            self.calculateBacktestingResult()

        d = self.getResult()

        if len(d) == 0:
            self.output(u'无交易结果')
            return

        # 导出交易清单
        self.exportTradeResult()

        # 输出
        self.output('-' * 30)
        self.output(u'第一笔交易：\t%s' % d['timeList'][0])
        self.output(u'最后一笔交易：\t%s' % d['timeList'][-1])

        self.output(u'总交易次数：\t%s' % formatNumber(d['totalResult']))
        self.output(u'期初资金：\t%s' % formatNumber(d['initCapital']))
        self.output(u'总盈亏：\t%s' % formatNumber(d['capital']))
        self.output(u'资金最高净值：\t%s' % formatNumber(d['maxCapital']))

        self.output(u'每笔最大盈利：\t%s' % formatNumber(d['maxPnl']))
        self.output(u'每笔最大亏损：\t%s' % formatNumber(d['minPnl']))
        self.output(u'净值最大回撤: \t%s' % formatNumber(min(d['drawdownList'])))
        self.output(u'净值最大回撤率: \t%s' % formatNumber(min(d['drawdownRateList'])))
        self.output(u'胜率：\t%s' % formatNumber(d['winningRate']))

        self.output(u'盈利交易平均值\t%s' % formatNumber(d['averageWinning']))
        self.output(u'亏损交易平均值\t%s' % formatNumber(d['averageLosing']))
        self.output(u'盈亏比：\t%s' % formatNumber(d['profitLossRatio']))

        self.output(u'最大持仓：\t%s' % formatNumber(d['maxVolume']))

        self.output(u'平均每笔盈利：\t%s' %formatNumber(d['capital']/d['totalResult']))

        self.output(u'平均每笔滑点成本：\t%s' %formatNumber(d['totalSlippage']/d['totalResult']))
        self.output(u'平均每笔佣金：\t%s' %formatNumber(d['totalCommission']/d['totalResult']))
            
        # 绘图
        import matplotlib.pyplot as plt
        import numpy as np

        try:
            import seaborn as sns       # 如果安装了seaborn则设置为白色风格
            sns.set_style('whitegrid')
        except ImportError:
            pass

        pCapital = plt.subplot(4, 1, 1)
        pCapital.set_ylabel("capital")
        pCapital.plot(d['capitalList'], color='r', lw=0.8)
        
        pDD = plt.subplot(4, 1, 2)
        pDD.set_ylabel("DD")
        pDD.bar(range(len(d['drawdownList'])), d['drawdownList'], color='g')
        
        pPnl = plt.subplot(4, 1, 3)
        pPnl.set_ylabel("pnl")
        pPnl.hist(d['pnlList'], bins=50, color='c')

        """
        pPos = plt.subplot(4, 1, 4)
        pPos.set_ylabel("Position")
        if d['posList'][-1] == 0:
            del d['posList'][-1]
        tradeTimeIndex = [item.strftime("%m/%d %H:%M:%S") for item in d['tradeTimeList']]
        xindex = np.arange(0, len(tradeTimeIndex), np.int(len(tradeTimeIndex)/10))
        tradeTimeIndex = map(lambda i: tradeTimeIndex[i], xindex)
        pPos.plot(d['posList'], color='k', drawstyle='steps-pre')
        pPos.set_ylim(-1.2, 1.2)
        plt.sca(pPos)
        """
        plt.tight_layout()
        #plt.xticks(xindex, tradeTimeIndex, rotation=30)  # 旋转15
        
        plt.show()
    
    #----------------------------------------------------------------------
    def putStrategyEvent(self, name):
        """发送策略更新事件，回测中忽略"""
        pass

    #----------------------------------------------------------------------
    def runOptimization(self, strategyClass, optimizationSetting):
        """优化参数"""
        # 获取优化设置
        settingList = optimizationSetting.generateSetting()
        targetName = optimizationSetting.optimizeTarget

        # 检查参数设置问题
        if not settingList or not targetName:
            self.output(u'优化设置有问题，请检查')

        # 遍历优化
        resultList = []
        for setting in settingList:
            self.clearBacktestingResult()
            self.output('-' * 30)
            self.output('setting: %s' %str(setting))
            self.initStrategy(strategyClass, setting)
            self.runBacktesting()
            d = self.calculateBacktestingResult()
            try:
                targetValue = d[targetName]
            except KeyError:
                targetValue = 0
            resultList.append(([str(setting)], targetValue))

        # 显示结果
        resultList.sort(reverse=True, key=lambda result:result[1])
        self.output('-' * 30)
        self.output(u'优化结果：')
        for result in resultList:
            self.output(u'%s: %s' %(result[0], result[1]))
        return result

    #----------------------------------------------------------------------
    def clearBacktestingResult(self):
        """清空之前回测的结果"""
        # 清空限价单相关
        self.limitOrderCount = 0
        self.limitOrderDict.clear()
        self.workingLimitOrderDict.clear()

        # 清空停止单相关
        self.stopOrderCount = 0
        self.stopOrderDict.clear()
        self.workingStopOrderDict.clear()

        # 清空成交相关
        self.tradeCount = 0
        self.tradeDict.clear()

    #----------------------------------------------------------------------
    def runParallelOptimization(self, strategyClass, optimizationSetting):
        """并行优化参数"""
        # 获取优化设置
        settingList = optimizationSetting.generateSetting()
        targetName = optimizationSetting.optimizeTarget

        # 检查参数设置问题
        if not settingList or not targetName:
            self.output(u'优化设置有问题，请检查')

        # 多进程优化，启动一个对应CPU核心数量的进程池
        pool = multiprocessing.Pool(multiprocessing.cpu_count())
        l = []

        for setting in settingList:
            l.append(pool.apply_async(optimize, (strategyClass, setting,
                                                 targetName, self.mode,
                                                 self.startDate, self.initDays, self.endDate,
                                                 self.slippage, self.rate, self.size,
                                                 self.dbName, self.symbol)))
        pool.close()
        pool.join()

        # 显示结果
        resultList = [res.get() for res in l]
        resultList.sort(reverse=True, key=lambda result:result[1])
        self.output('-' * 30)
        self.output(u'优化结果：')
        for result in resultList:
            self.output(u'%s: %s' %(result[0], result[1]))

    #----------------------------------------------------------------------
    def roundToPriceTick(self, price):
        """取整价格到合约最小价格变动"""
        if not self.priceTick:
            return price

        newPrice = round(price/self.priceTick, 0) * self.priceTick
        return newPrice



########################################################################
class TradingResult(object):
    """每笔交易的结果"""

    #----------------------------------------------------------------------
    def __init__(self, entryPrice,entryDt, exitPrice,exitDt,volume, rate, slippage, size, groupId, fixcommission=EMPTY_FLOAT):
        """Constructor"""
        self.entryPrice = entryPrice    # 开仓价格
        self.exitPrice = exitPrice      # 平仓价格

        self.entryDt = entryDt          # 开仓时间datetime
        self.exitDt = exitDt            # 平仓时间

        self.volume = volume    # 交易数量（+/-代表方向）
        self.groupId = groupId  # 主交易ID（针对多手平仓）

        self.turnover = (self.entryPrice + self.exitPrice) * size * abs(volume)  # 成交金额
        if fixcommission:
            self.commission = fixcommission * self.volume
        else:
            self.commission = self.turnover * rate  # 手续费成本
        self.slippage = slippage * 2 * size * abs(volume)  # 滑点成本
        self.pnl = ((self.exitPrice - self.entryPrice) * volume * size
                    - self.commission - self.slippage)  # 净盈亏


########################################################################
class OptimizationSetting(object):
    """优化设置"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.paramDict = OrderedDict()

        self.optimizeTarget = ''        # 优化目标字段

    #----------------------------------------------------------------------
    def addParameter(self, name, start, end=None, step=None):
        """增加优化参数"""
        if end is None and step is None:
            self.paramDict[name] = [start]
            return

        if end < start:
            print u'参数起始点必须不大于终止点'
            return

        if step <= 0:
            print u'参数布进必须大于0'
            return

        l = []
        param = start

        while param <= end:
            l.append(param)
            param += step

        self.paramDict[name] = l

    #----------------------------------------------------------------------
    def generateSetting(self):
        """生成优化参数组合"""
        # 参数名的列表
        nameList = self.paramDict.keys()
        paramList = self.paramDict.values()

        # 使用迭代工具生产参数对组合
        productList = list(product(*paramList))

        # 把参数对组合打包到一个个字典组成的列表中
        settingList = []
        for p in productList:
            d = dict(zip(nameList, p))
            settingList.append(d)

        return settingList

    #----------------------------------------------------------------------
    def setOptimizeTarget(self, target):
        """设置优化目标字段"""
        self.optimizeTarget = target


#----------------------------------------------------------------------
def formatNumber(n):
    """格式化数字到字符串"""
    rn = round(n, 2)        # 保留两位小数
    return format(rn, ',')  # 加上千分符


#----------------------------------------------------------------------
def optimize(strategyClass, setting, targetName,
             mode, startDate, initDays, endDate,
             slippage, rate, size,
             dbName, symbol):
    """多进程优化时跑在每个进程中运行的函数"""
    engine = BacktestingEngine()
    engine.setBacktestingMode(mode)
    engine.setStartDate(startDate, initDays)
    engine.setEndDate(endDate)
    engine.setSlippage(slippage)
    engine.setRate(rate)
    engine.setSize(size)
    engine.setDatabase(dbName, symbol)

    engine.initStrategy(strategyClass, setting)
    engine.runBacktesting()
    d = engine.calculateBacktestingResult()
    try:
        targetValue = d[targetName]
    except KeyError:
        targetValue = 0
    return (str(setting), targetValue)


if __name__ == '__main__':
    # 以下内容是一段回测脚本的演示，用户可以根据自己的需求修改
    # 建议使用ipython notebook或者spyder来做回测
    # 同样可以在命令模式下进行回测（一行一行输入运行）
    from strategy.strategyEmaDemo import *
    
    # 创建回测引擎
    engine = BacktestingEngine()
    
    # 设置引擎的回测模式为K线
    engine.setBacktestingMode(engine.BAR_MODE)

    # 设置回测用的数据起始日期
    engine.setStartDate('20110101')
    
    # 载入历史数据到引擎中
    engine.setDatabase(MINUTE_DB_NAME, 'IF0000')
    
    # 设置产品相关参数
    engine.setSlippage(0.2)     # 股指1跳
    engine.setRate(0.3/10000)   # 万0.3
    engine.setSize(300)         # 股指合约大小    
    
    # 在引擎中创建策略对象
    engine.initStrategy(EmaDemoStrategy, {})
    
    # 开始跑回测
    engine.runBacktesting()
    
    # 显示回测结果
    # spyder或者ipython notebook中运行时，会弹出盈亏曲线图
    # 直接在cmd中回测则只会打印一些回测数值
    engine.showBacktestingResult()
    
    