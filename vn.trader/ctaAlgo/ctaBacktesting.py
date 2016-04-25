# encoding: UTF-8

'''
本文件中包含的是CTA模块的回测引擎，回测引擎的API和CTA引擎一致，
可以使用和实盘相同的代码进行回测。
'''

from datetime import datetime, timedelta
from collections import OrderedDict
from pymongo import MongoClient
from pymongo.errors import ConnectionFailure
import os
from ctaBase import *
from ctaSetting import *

from vtConstant import *
from vtGateway import VtOrderData, VtTradeData
from vtFunction import loadMongoSetting


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
        
        self.slippage = 0           # 回测时假设的滑点
        self.rate = 0               # 回测时假设的佣金比例（适用于百分比佣金）
        self.size = 1               # 合约大小，默认为1        
        
        self.dbClient = None        # 数据库客户端
        self.dbCursor = None        # 数据库指针
        
        #self.historyData = []       # 历史数据的列表，回测用
        self.initData = []          # 初始化用的数据
        #self.backtestingData = []   # 回测用的数据
        
        self.dataStartDate = None       # 回测数据开始日期，datetime对象
        self.dataEndDate = None         # 回测数据结束日期，datetime对象
        self.strategyStartDate = None   # 策略启动日期（即前面的数据用于初始化），datetime对象
        
        self.limitOrderDict = OrderedDict()         # 限价单字典
        self.workingLimitOrderDict = OrderedDict()  # 活动限价单字典，用于进行撮合用
        self.limitOrderCount = 0                    # 限价单编号
        
        self.tradeCount = 0             # 成交编号
        self.tradeDict = OrderedDict()  # 成交字典
        
        self.logList = []               # 日志记录
        
        # 当前最新数据，用于模拟成交用
        self.tick = None
        self.bar = None
        self.dt = None      # 最新的时间

    #----------------------------------------------------------------------
    def dbConnect(self):
        """连接MongoDB数据库"""

        # 读取数据库配置的方法，已转移至vtFunction

        if not self.dbClient:
            # 读取MongoDB的设置
            fileName = os.path.dirname(os.getcwd()) + "\\VT_setting.json"
            host, port, replicaset, readPreference, database, userID, password = loadMongoSetting(fileName)
            try:
                self.dbClient = MongoClient(host+':'+str(port), replicaset=replicaset,readPreference=readPreference)
                db = self.dbClient[database]
                db.authenticate(userID, password)
                # self.dbClient = MongoClient(host, port)
                print u'MongoDB连接成功'
            except ConnectionFailure:
                print u'MongoDB连接失败'
            except ValueError:
                print u'MongoDB连接配置字段错误，请检查'
    #----------------------------------------------------------------------
    def setStartDate(self, startDate='20100416', initDays=10):
        """设置回测的启动日期"""
        self.dataStartDate = datetime.strptime(startDate, '%Y%m%d')
        
        initTimeDelta = timedelta(initDays)
        self.strategyStartDate = self.dataStartDate + initTimeDelta
        
    #----------------------------------------------------------------------
    def setEndDate(self, endDate=''):
        """设置回测的结束日期"""
        if endDate:
            self.dataEndDate= datetime.strptime(endDate, '%Y%m%d')
        
    #----------------------------------------------------------------------
    def setBacktestingMode(self, mode):
        """设置回测模式"""
        self.mode = mode
        
    #----------------------------------------------------------------------
    def loadHistoryData(self, dbName, symbol):
        """载入历史数据"""
        # host, port = loadMongoSetting()
        #
        # self.dbClient = pymongo.MongoClient(host, port)

        self.dbConnect()

        collection = self.dbClient[dbName][symbol]          

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
    def runBacktesting(self):
        """运行回测"""
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
        
    #----------------------------------------------------------------------
    def newBar(self, bar):
        """新的K线"""
        self.bar = bar
        self.dt = bar.datetime
        self.crossLimitOrder()      # 先撮合限价单
        self.crossStopOrder()       # 再撮合停止单
        self.strategy.onBar(bar)    # 推送K线到策略中
    
    #----------------------------------------------------------------------
    def newTick(self, tick):
        """新的Tick"""
        self.tick = tick
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
        self.strategy.name = self.strategy.className
        
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
            bestCrossPrice = self.bar.open  # 在当前时间点前发出的委托可能的最优成交价
        else:
            # self.tick.lastPrice = self.tick.close
            buyCrossPrice = self.tick.lastPrice
            sellCrossPrice = self.tick.lastPrice
            bestCrossPrice = self.tick.lastPrice
        
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
                
                # 以买入为例：
                # 1. 假设当根K线的OHLC分别为：100, 125, 90, 110
                # 2. 假设在上一根K线结束(也是当前K线开始)的时刻，策略发出的委托为限价105
                # 3. 则在实际中的成交价会是100而不是105，因为委托发出时市场的最优价格是100
                if buyCross:
                    trade.price = min(order.price, bestCrossPrice)
                    self.strategy.pos += order.totalVolume
                else:
                    trade.price = max(order.price, bestCrossPrice)
                    self.strategy.pos -= order.totalVolume
                
                trade.volume = order.totalVolume
                trade.tradeTime = str(self.dt)
                trade.dt = self.dt
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
            bestCrossPrice = self.bar.open   # 最优成交价，买入停止单不能低于，卖出停止单不能高于
        else:
            buyCrossPrice = self.tick.lastPrice
            sellCrossPrice = self.tick.lastPrice
            bestCrossPrice = self.tick.lastPrice
        
        # 遍历停止单字典中的所有停止单
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
    def writeCtaLog(self, content):
        """记录日志"""
        log = str(self.dt) + ' ' + content 
        self.logList.append(log)
        
    #----------------------------------------------------------------------
    def output(self, content):
        """输出内容"""
        print content
        
    #----------------------------------------------------------------------
    def showBacktestingResult(self):
        """
        显示回测结果
        """
        self.output(u'显示回测结果')
        
        # 首先基于回测后的成交记录，计算每笔交易的盈亏
        pnlDict = OrderedDict()     # 每笔盈亏的记录 
        longTrade = []              # 未平仓的多头交易
        shortTrade = []             # 未平仓的空头交易
        
        # 计算滑点，一个来回包括两次
        totalSlippage = self.slippage * 2 
        
        for trade in self.tradeDict.values():
            # 多头交易
            if trade.direction == DIRECTION_LONG:
                # 如果尚无空头交易
                if not shortTrade:
                    longTrade.append(trade)
                # 当前多头交易为平空
                else:
                    entryTrade = shortTrade.pop(0)
                    # 计算比例佣金
                    commission = (trade.price+entryTrade.price) * self.rate
                    # 计算盈亏
                    pnl = ((trade.price - entryTrade.price)*(-1) - totalSlippage - commission) \
                        * trade.volume * self.size
                    pnlDict[trade.dt] = pnl
            # 空头交易        
            else:
                # 如果尚无多头交易
                if not longTrade:
                    shortTrade.append(trade)
                # 当前空头交易为平多
                else:
                    entryTrade = longTrade.pop(0)
                    # 计算比例佣金
                    commission = (trade.price+entryTrade.price) * self.rate    
                    # 计算盈亏
                    pnl = ((trade.price - entryTrade.price) - totalSlippage - commission) \
                        * trade.volume * self.size
                    pnlDict[trade.dt] = pnl
        
        # 然后基于每笔交易的结果，我们可以计算具体的盈亏曲线和最大回撤等
        timeList = pnlDict.keys()
        pnlList = pnlDict.values()
        
        capital = 0
        maxCapital = 0
        drawdown = 0
        
        capitalList = []        # 盈亏汇总的时间序列
        maxCapitalList = []     # 最高盈利的时间序列
        drawdownList = []       # 回撤的时间序列
        
        for pnl in pnlList:
            capital += pnl
            maxCapital = max(capital, maxCapital)
            drawdown = capital - maxCapital
            
            capitalList.append(capital)
            maxCapitalList.append(maxCapital)
            drawdownList.append(drawdown)
            
        # 输出
        self.output('-' * 50)
        self.output(u'第一笔交易时间：%s' % timeList[0])
        self.output(u'最后一笔交易时间：%s' % timeList[-1])
        self.output(u'总交易次数：%s' % len(pnlList))
        self.output(u'总盈亏：%s' % capitalList[-1])
        self.output(u'最大回撤: %s' % min(drawdownList))        
            
        # 绘图
        import matplotlib.pyplot as plt
        
        pCapital = plt.subplot(3, 1, 1)
        pCapital.set_ylabel("capital")
        pCapital.plot(capitalList)

        pDD = plt.subplot(3, 1, 2)
        pDD.set_ylabel("DD")
        pDD.bar(range(len(drawdownList)), drawdownList)         
        
        pPnl = plt.subplot(3, 1, 3)
        pPnl.set_ylabel("pnl")
        pPnl.hist(pnlList, bins=20)
        
        plt.show()
    
    #----------------------------------------------------------------------
    def putStrategyEvent(self, name):
        """发送策略更新事件，回测中忽略"""
        pass

    #----------------------------------------------------------------------
    def setSlippage(self, slippage):
        """设置滑点"""
        self.slippage = slippage
        
    #----------------------------------------------------------------------
    def setSize(self, size):
        """设置合约大小"""
        self.size = size
        
    #----------------------------------------------------------------------
    def setRate(self, rate):
        """设置佣金比例"""
        self.rate = rate



if __name__ == '__main__':
    # 以下内容是一段回测脚本的演示，用户可以根据自己的需求修改
    # 建议使用ipython notebook或者spyder来做回测
    # 同样可以在命令模式下进行回测（一行一行输入运行）
    # from ctaDemo import *
    #
    # # 创建回测引擎
    # engine = BacktestingEngine()
    #
    # # 设置引擎的回测模式为K线
    # engine.setBacktestingMode(engine.BAR_MODE)
    #
    # # 设置滑点
    # engine.setSlippage(0.2)     # 股指1跳
    #
    # # 设置回测用的数据起始日期
    # engine.setStartDate('20100416')
    #
    # # 载入历史数据到引擎中
    # engine.loadHistoryData(MINUTE_DB_NAME, 'IF0000')
    #
    # # 在引擎中创建策略对象
    # engine.initStrategy(DoubleEmaDemo, {})
    #
    # # 开始跑回测
    # engine.runBacktesting()
    #
    # # 显示回测结果
    # # spyder或者ipython notebook中运行时，会弹出盈亏曲线图
    # # 直接在cmd中回测则只会打印一些回测数值
    # engine.showBacktestingResult()

    from talibDemo import *
    # 创建回测引擎
    engine = BacktestingEngine()

    # 设置引擎的回测模式为K线

    engine.setBacktestingMode(engine.BAR_MODE)

    # 设置回测用的数据起始日期
    engine.setStartDate('20110101')
    
    # 载入历史数据到引擎中
    engine.loadHistoryData(MINUTE_DB_NAME, 'IF0000')
    
    # 设置产品相关参数
    engine.setSlippage(0.2)     # 股指1跳
    engine.setRate(0.3/10000)   # 万0.3
    engine.setSize(300)         # 股指合约大小    
    
    # 在引擎中创建策略对象
    engine.initStrategy(TalibDoubleSmaDemo, {})

    # 开始跑回测
    engine.runBacktesting()

    # 显示回测结果
    # spyder或者ipython notebook中运行时，会弹出盈亏曲线图
    # 直接在cmd中回测则只会打印一些回测数值
    engine.showBacktestingResult()
