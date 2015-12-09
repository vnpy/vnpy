# encoding: UTF-8

from datetime import datetime, timedelta
import json
from collections import OrderedDict

import pymongo

from vtConstant import *
from vtGateway import VtOrderData, VtTradeData

from ctaConstant import *
from ctaObject import *
from ctaStrategies import strategyClassDict

from ctaStrategyTemplate import TestStrategy
from ctaHistoryData import MINUTE_DB_NAME



########################################################################
class BacktestingEngine(object):
    """
    CTA回测引擎
    函数接口和策略引擎保持一样，
    从而实现同一套代码从回测到实盘。
    """
    
    TICK_MODE = 'tick'
    BAR_MODE = 'bar'

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        # 本地停止单编号计数
        self.stopOrderCount = 0
        # stopOrderID = STOPORDERPREFIX + str(stopOrderCount)
        
        # 本地停止单字典
        # key为stopOrderID，value为stopOrder对象
        self.stopOrderDict = {}             # 停止单撤销后不会从本字典中删除
        self.workingStopOrderDict = {}      # 停止单撤销后会从本字典中删除
        
        # 回测相关
        self.strategy = None        # 回测策略
        self.mode = self.BAR_MODE   # 回测模式，默认为K线
        
        self.dbClient = None    # 数据库客户端
        self.dbCursor = None    # 数据库指针
        
        self.historyData = []   # 历史数据的列表，回测用
        self.initData = []      # 初始化用的数据
        self.backtestingData = []   # 回测用的数据
        
        self.dataStartDate = None       # 回测数据开始日期，datetime对象
        self.strategyStartDate = None   # 策略启动日期（即前面的数据用于初始化），同上
        
        self.limitOrderDict = {}        # 限价单字典
        self.workingLimitOrderDict = {} # 活动限价单字典，用于进行撮合用
        self.limitOrderCount = 0        # 限价单编号
        
        self.tradeCount = 0         # 成交编号
        self.tradeDict = {}         # 成交字典
        
        # 当前最新数据，用于模拟成交用
        self.tick = None
        self.bar = None
        self.dt = None      # 最新的时间
        
    #----------------------------------------------------------------------
    def setStartDate(self, startDate='20100416', initDays=30):
        """设置回测的启动日期"""
        self.dataStartDate = datetime.strptime(startDate, '%Y%m%d')
        
        initTimeDelta = timedelta(initDays)
        self.strategyStartDate = self.dataStartDate + initTimeDelta
        
    #----------------------------------------------------------------------
    def setBacktestingMode(self, mode):
        """设置回测模式"""
        self.mode = mode
        
    #----------------------------------------------------------------------
    def loadHistoryData(self, dbName, symbol):
        """载入历史数据"""
        self.output(u'开始载入数据')
        
        # 首先根据回测模式，确认要使用的数据类
        if self.mode == self.BAR_MODE:
            dataClass = CtaBarData
        else:
            dataClass = CtaTickData
        
        # 从数据库进行查询
        self.dbClient = pymongo.MongoClient()
        collection = self.dbClient[dbName][symbol]
        
        flt = {'datetime':{'$gte':self.dataStartDate}}   # 数据过滤条件
        self.dbCursor = collection.find(flt)
        
        # 将数据从查询指针中读取出，并生成列表
        for d in self.dbCursor:
            data = dataClass()
            data.__dict__ = d
            if data.datetime < self.strategyStartDate:
                self.initData.append(data)
            else:
                self.backtestingData.append(data)
        
        self.output(u'载入完成，数据量%s' %len(self.backtestingData))
    
    #----------------------------------------------------------------------
    def runBacktesting(self):
        """运行回测"""
        self.strategy.start()
        
        if self.mode == self.BAR_MODE:
            for data in self.backtestingData:
                self.newBar(data)
        else:
            for data in self.backtestingData:
                self.newTick(data)
        
    #----------------------------------------------------------------------
    def newBar(self, bar):
        """新的K线"""
        self.bar = bar
        self.crossLimitOrder()  # 先撮合限价单
        self.crossStopOrder()   # 再撮合停止单
        self.strategy.onBar(bar)
    
    #----------------------------------------------------------------------
    def newTick(self, tick):
        """新的Tick"""
        self.tick = tick
        self.crossLimitOrder()
        self.crossStopOrder()
        self.strategy.onTick(tick)
        
    #----------------------------------------------------------------------
    def initStrategy(self, name, strategyClass, paramDict=None):
        """初始化策略"""
        self.strategy = strategyClass(self, name, paramDict)
        
    #----------------------------------------------------------------------
    def sendOrder(self, vtSymbol, orderType, price, volume, strategy):
        """发单"""
        self.limitOrderCount += 1
        orderID = str(self.limitOrderCount)
        
        order = VtOrderData()
        order.vtSymbol = vtSymbol
        order.price = price
        order.totalVolume = volume
        order.status = STATUS_NOTTRADED     # 刚提交尚未成交
        order.orderID = orderID
        order.vtOrderID = orderID
        order.orderTime = str(self.dt)
        
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
        
        # 保存到限价单字典中
        self.workingLimitOrderDict[orderID] = order
        self.limitOrderDict[orderID] = order
        
        return orderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, vtOrderID):
        """撤单"""
        if vtOrderID in self.workingLimitOrderDict:
            order = self.workingLimitOrderDict[vtOrderID]
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
        so.price = price
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
            buyCrossPrice = self.bar.low    # 若买入方向限价单价格高于该价格，则会成交
            sellCrossPrice = self.bar.high  # 若卖出方向限价单价格低于该价格，则会成交
        else:
            buyCrossPrice = self.tick.lastPrice
            sellCrossPrice = self.tick.lastPrice
        
        # 遍历限价单字典中的所有限价单
        for orderID, order in self.workingLimitOrderDict.items():
            # 判断是否会成交
            buyCross = order.direction==DIRECTION_LONG and order.price>=buyCrossPrice
            sellCross = order.direction==DIRECTION_SHORT and order.price<=sellCrossPrice
            
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
                trade.price = order.price
                trade.volume = order.totalVolume
                trade.tradeTime = str(self.dt)
                self.strategy.onTrade(trade)
                
                self.tradeDict[tradeID] = trade
                
                # 推送委托数据
                order.tradedVolume = order.totalVolume
                order.status = STATUS_ALLTRADED
                self.strategy.onOrder(order)
                
                # 从字典中删除该限价单
                del self.workingLimitOrderDict[orderID]
                
    #----------------------------------------------------------------------
    def crossStopOrder(self):
        """基于最新数据撮合停止单"""
        # 先确定会撮合成交的价格，这里和限价单规则相反
        if self.mode == self.BAR_MODE:
            buyCrossPrice = self.bar.high    # 若买入方向停止单价格低于该价格，则会成交
            sellCrossPrice = self.bar.low    # 若卖出方向限价单价格高于该价格，则会成交
        else:
            buyCrossPrice = self.tick.lastPrice
            sellCrossPrice = self.tick.lastPrice
        
        # 遍历限价单字典中的所有限价单
        for stopOrderID, so in self.workingStopOrderDict.items():
            # 判断是否会成交
            buyCross = so.direction==DIRECTION_LONG and so.price<=buyCrossPrice
            sellCross = so.direction==DIRECTION_SHORT and so.price>=sellCrossPrice
            
            # 如果发生了成交
            if buyCross or sellCross:
                # 推送成交数据
                self.tradeCount += 1            # 成交编号自增1
                tradeID = str(self.tradeCount)
                trade = VtTradeData()
                trade.vtSymbol = so.vtSymbol
                trade.tradeID = tradeID
                trade.vtTradeID = tradeID
                
                self.limitOrderCount += 1
                orderID = str(self.limitOrderCount)
                trade.orderID = orderID
                trade.vtOrderID = orderID
                
                trade.direction = so.direction
                trade.offset = so.offset
                trade.price = so.price
                trade.volume = so.volume
                trade.tradeTime = str(self.dt)
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
                
                # 从字典中删除该限价单
                del self.workingStopOrderDict[stopOrderID]        

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
    def getToday(self):
        """获取代表今日的datetime对象"""
        # 这个方法本身主要用于在每日初始化时确定日期，从而知道该读取之前从某日起的数据
        # 这里选择策略启动的日期
        return self.strategyStartDate
    
    #----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """记录日志"""
        print content
        
    #----------------------------------------------------------------------
    def output(self, content):
        """输出内容"""
        print content
        


#----------------------------------------------------------------------
def test():
    """"""
    engine = BacktestingEngine()
    engine.setBacktestingMode(engine.BAR_MODE)
    engine.initStrategy(u'测试', TestStrategy)
    engine.setStartDate()
    engine.loadHistoryData(MINUTE_DB_NAME, 'IF0000')
    engine.runBacktesting()
    
    