# encoding: UTF-8

# 首先写系统内置模块
import sys
print u'demoStrategy.py import sys success'
from datetime import datetime, timedelta, time, date
print u'demoStrategy.py import datetime.datetime/timedelta/time success'
from time import sleep
print u'demoStrategy.py import time.sleep success'


# 然后是自己编写的模块
from demoEngine import MainEngine
print u'demoStrategy.py import demoEngine.MainEngine success'
from strategyEngine import *
import vtConstant

import tushare as ts
import pandas as pd
import talib as ta

import MySQLdb

import os
import sys
import cPickle


########################################################################
class StrategyProduceBar(StrategyTemplate):
    """生成Bar线策略

    """
#----------------------------------------------------------------------
    def __init__(self, name, symbol, engine):
        """Constructor"""

        super(StrategyProduceBar, self).__init__(name, symbol, engine)

        # 主连标签
        if len(symbol) > 4:
            self.symbolMi = symbol[:-4]
        else:
            self.symbolMi = symbol


        # 最新TICK数据（市场报价）
        self.currentTick = None

        # M1 K线缓存对象
        self.barOpen = EMPTY_FLOAT
        self.barHigh = EMPTY_FLOAT
        self.barLow = EMPTY_FLOAT
        self.barClose = EMPTY_FLOAT
        self.barVolume = EMPTY_INT
        self.barTime = None

        # M5 K线 计算数据

        self.barM5Open = EMPTY_FLOAT
        self.barM5High = EMPTY_FLOAT
        self.barM5Low = EMPTY_FLOAT
        self.barM5Close = EMPTY_FLOAT
        self.barM5Volume = EMPTY_INT
        self.barM5Time = None

        # 当前交易日日期
        self.curDate = None

        # 仓位状态
        self.pos = 0                # 0表示没有仓位，1表示持有多头， -1表示持有空头

        # 报单代码列表
        self.listOrderRef = []      # 报单号列表
        self.listStopOrder = []     # 停止单对象列表

        # 是否完成了初始化
        self.initCompleted = False

        # 初始化时读取的历史数据的起始日期(可以选择外部设置)
        self.startDate = None


        self.lineM1Bar = []           # M1 K线数据
        self.lineM5Bar = []           # M5 K线数据

    #----------------------------------------------------------------------
    def loadSetting(self, setting):
        """读取参数设定"""
        try:
            if setting['orderVolume']:
                self.orderVolume = setting['orderVolume']

            if setting['refDays']:
                self.refDays = setting['refDays']

            self.engine.writeLog(self.name + u'读取参数成功')
        except KeyError:
            self.engine.writeLog(self.name + u'读取参数设定出错，请检查参数字典')

        try:
            self.initStrategy(setting['startDate'])
        except KeyError:
            self.initStrategy()

    #----------------------------------------------------------------------
    def initStrategy(self, startDate=None):
        """初始化"""

        # 获取 InputP个周期的5分钟Bar线数据，初始化加载入M5Bar

        self.initCompleted = True

        self.engine.writeLog(self.name + u'初始化完成')

    def __initNewDate(self, symbol, endDate=datetime.today()):
        """初始化新的一天
        1、清除多余的M1Bar＆　M5Bar
        2、如果隔夜持仓，需要继续清除。

        """

    #----------------------------------------------------------------------
    def onTick(self, tick):
        """行情更新
        :type tick: object
        """
        # 保存最新的TICK
        self.currentTick = tick

        # 首先生成datetime.time格式的时间（便于比较）
        # ticktime = self.strToTime(tick.time, tick.ms)
        ticktime = tick.time

        tickDate = date(ticktime.year, ticktime.month, ticktime.day)

        if tickDate != self.curDate:

            # 更新为新的一天
            self.curDate = tickDate

            # 初始化交易日数据
            self.__initNewDate(self.symbol, self.curDate)



        # 假设是收到的第一个TICK
        if self.barOpen == 0:
            # 初始化新的K线数据
            self.barOpen = tick.lastPrice
            self.barHigh = tick.lastPrice
            self.barLow = tick.lastPrice
            self.barClose = tick.lastPrice
            self.barVolume = tick.volume
            self.barTime = ticktime
        else:
            # 如果是当前一分钟内的数据
            if ticktime.minute == self.barTime.minute and ticktime.hour == self.barTime.hour:
                # 汇总TICK生成K线
                self.barHigh = max(self.barHigh, tick.lastPrice)
                self.barLow = min(self.barLow, tick.lastPrice)
                self.barClose = tick.lastPrice
                self.barVolume = self.barVolume + tick.volume
                self.barTime = ticktime

            # 如果是新一分钟的数据
            else:
                # 首先推送K线数据
                self.onBar(self.barOpen, self.barHigh, self.barLow, self.barClose,
                           self.barVolume, self.barTime)

                # 初始化新的K线数据
                self.barOpen = tick.lastPrice
                self.barHigh = tick.lastPrice
                self.barLow = tick.lastPrice
                self.barClose = tick.lastPrice
                self.barVolume = tick.volume
                self.barTime = ticktime

    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """交易更新"""

        log = self.name + u'当前持仓：' + str(self.pos)

        print log
        self.engine.writeLog(log)

    #----------------------------------------------------------------------
    def onOrder(self, order):
        """报单更新"""
        pass

    #----------------------------------------------------------------------
    def onStopOrder(self, orderRef):
        """停止单更新"""
        pass

    #----------------------------------------------------------------------
    def onBar(self, o, h, l, c, volume, t):
        """K线数据更新，同时进行策略的买入、卖出逻辑计算"""

        bartime = datetime(t.year, t.month, t.day, t.hour, t.minute)                 # 秒可以去除

        # 保存M1-K线数据
        bar = Bar()
        bar.symbol = self.symbol
        bar.open = o
        bar.high = h
        bar.low = l
        bar.close = c
        bar.volume = volume
        bar.date = bartime.strftime('%Y-%m-%d')
        bar.time = bartime.strftime('%H:%M:%S')
        bar.datetime = bartime
        self.lineM1Bar.append(bar)

        # 保存M5-K线数据，更新前置条件值
        self.onM5Bar(o, h, l, c, volume, t)

        # 交易逻辑
        if self.initCompleted:      # 首先检查是否是实盘运行还是数据预处理阶段
            pass

        # 记录日志
        log = self.name + u'，K线时间：' + str(t) + '\n'
        self.engine.writeLog(log)

    #----------------------------------------------------------------------
    def onM5Bar(self, o, h, l, c, volume, t):
        """更新5分钟K线
        此方法有两个入口，一个是OnBar推送的每分钟K线，
        另一个是initStrategy推送的初始化前若干周期的M5 K线"""
        minute = t.minute - t.minute % 5
        bartime = datetime(t.year,t.month,t.day,t.hour,minute)

        # 如果 M5为空，创建一个M5
        if len(self.lineM5Bar) == 0:
            m5bar = Bar()

            m5bar.symbol = self.symbol
            m5bar.open = o
            m5bar.high = h
            m5bar.low = l
            m5bar.close = c
            m5bar.volume = volume
            m5bar.date = bartime.strftime('%Y-%m-%d')
            m5bar.time = bartime.strftime('%H:%M:%S')
            m5bar.datetime = bartime

            self.lineM5Bar.append(m5bar)

        else:
            lastM5Bar = self.lineM5Bar[-1]

            if(t-lastM5Bar.datetime).seconds < 300:
                # 如果 新Bar数据的时间为同一个M5周期，更新M5数据
                lastM5Bar.high = max(lastM5Bar.high, h)
                lastM5Bar.low = min(lastM5Bar.low, l)
                lastM5Bar.close = c
                lastM5Bar.volume = lastM5Bar.volume + volume
            else:
                # 如果 新Bar数据的周期为下一个M5周期，重新计算PreM5系列值，创建新的M5
                m5bar = Bar()

                m5bar.symbol = self.symbol
                m5bar.open = o
                m5bar.high = h
                m5bar.low = l
                m5bar.close = c
                m5bar.volume = volume
                m5bar.date = bartime.strftime('%Y-%m-%d')
                m5bar.time = bartime.strftime('%H:%M:%S')
                m5bar.datetime = bartime

                self.lineM5Bar.append(m5bar)


    #----------------------------------------------------------------------
    def strToTime(self, t, ms):
        """从字符串时间转化为time格式的时间"""
        hh, mm, ss = t.split(':')
        tt = time(int(hh), int(mm), int(ss), microsecond=ms)
        return tt

     #----------------------------------------------------------------------
    def saveData(self, id):
        """保存过程数据"""
        # 保存K线
        print u'{0}保存K线'.format(self.name)
        self.__saveBarToMysql('M1', self.lineM1Bar)
        self.__saveBarToMysql('M5', self.lineM5Bar)


    def __saveBarToMysql(self,barType, barList):
        """
        保存K线数据到数据库
        id， 回测ID
        barList， 对象为Bar的列表
        """

        # 保存本地pickle文件
        resultPath=os.getcwd()+'/result'

        if not os.path.isdir(resultPath):
            os.mkdir(resultPath)

        resultFile = u'{0}/{1}_{2}Bar.pickle'.format(resultPath,self.symbolMi, barType)

        cache= open(resultFile, mode='w')

        cPickle.dump(barList,cache)

        cache.close()

        # 保存数据库

        self.__connectMysql()

        if self.__mysqlConnected:
            sql = 'insert ignore into stockcn.TB_{0}{1} ' \
                  '( open,high, low,close,date,time,datetime,volume) ' \
                  'values '.format(self.symbolMi,barType)

            values = ''

            print u'共{0}条{1}Bar记录.'.format(len(barList),barType)

            if len(barList) == 0:
                return

            counts = 0

            for bar in barList:

                if len(values) > 0:
                    values = values + ','

                values = values + '({0},{1},{2},{3},\'{4}\',\'{5}\',\'{6}\',{7})'.format(
                    bar.open,
                    bar.high,
                    bar.low,
                    bar.close,
                    bar.date,
                    bar.time,
                    bar.datetime.strftime('%Y-%m-%d %H:%M:%S'),
                    bar.volume
                    )

                if counts >= 3600:

                    self.__executeMysql(sql+values)

                    print u'写入{0}条{1}Bar记录'.format(counts,barType)

                    counts = 0
                    values = ''

                else:
                    counts = counts + 1

            if counts > 0:

                self.__executeMysql(sql+values)
                print u'写入{0}条{1}Bar记录'.format(counts,barType)


#----------------------------------------------------------------------
    def __connectMysql(self):
        """连接MysqlDB"""
        try:
            self.__mysqlConnection = MySQLdb.connect(host='vnpy.cloudapp.net', user='stockcn', passwd='7uhb*IJN', db='stockcn', port=3306)
            self.__mysqlConnected = True
            print u'策略连接MysqlDB成功'
        except ConnectionFailure:
            print u'策略连接MysqlDB失败'

    #----------------------------------------------------------------------
    def __executeMysql(self, sql):
        """执行mysql语句"""
        if not self.__mysqlConnected:
            self.__connectMysql()

        cur = self.__mysqlConnection.cursor(MySQLdb.cursors.DictCursor)

        try:
            cur.execute(sql)
            self.__mysqlConnection.commit()

        except Exception, e:
            print e
            print sql

            self.__connectMysql()
            cur = self.__mysqlConnection.cursor(MySQLdb.cursors.DictCursor)
            cur.execute(sql)
            self.__mysqlConnection.commit()