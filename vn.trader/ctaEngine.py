# encoding: UTF-8

from datetime import datetime
import json
from collections import OrderedDict

from eventEngine import *
from vtConstant import *
<<<<<<< HEAD
<<<<<<< HEAD
from vtGateway import VtOrderReq, VtCancelOrderReq
=======
from vtGateway import VtSubscribeReq, VtOrderReq, VtCancelOrderReq, VtLogData
>>>>>>> refs/remotes/vnpy/master
=======
from vtGateway import VtSubscribeReq, VtOrderReq, VtCancelOrderReq, VtLogData
>>>>>>> refs/remotes/vnpy/master

from ctaConstant import *
from ctaStrategies import strategyClassDict


########################################################################
class StopOrder(object):
    """本地停止单"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.vtSymbol = EMPTY_STRING
        self.orderType = EMPTY_UNICODE
        self.price = EMPTY_FLOAT
        self.volume = EMPTY_INT
        
        self.strategy = None             # 下停止单的策略对象
        self.stopOrderID = EMPTY_STRING  # 停止单的本地编号 
        self.status = EMPTY_STRING       # 停止单状态


########################################################################
class CtaBarData(object):
    """K线数据"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.vtSymbol = EMPTY_STRING        # vt系统代码
        self.symbol = EMPTY_STRING          # 代码
        self.exchange = EMPTY_STRING        # 交易所
    
        self.open = EMPTY_FLOAT             # OHLC
        self.high = EMPTY_FLOAT
        self.low = EMPTY_FLOAT
        self.close = EMPTY_FLOAT
        
        self.date = EMPTY_STRING            # bar开始的时间，日期
        self.time = EMPTY_STRING            # 时间
        self.datetime = None                # python的datetime时间对象
        
        self.volume = EMPTY_INT             # 成交量
        self.openInterest = EMPTY_INT       # 持仓量


########################################################################
class CtaTickData(object):
    """Tick数据"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""       
        self.vtSymbol = EMPTY_STRING            # vt系统代码
        self.symbol = EMPTY_STRING              # 合约代码
        self.exchange = EMPTY_STRING            # 交易所代码

        # 成交数据
        self.lastPrice = EMPTY_FLOAT            # 最新成交价
        self.volume = EMPTY_INT                 # 最新成交量
        self.openInterest = EMPTY_INT           # 持仓量
        
        self.upperLimit = EMPTY_FLOAT           # 涨停价
        self.lowerLimit = EMPTY_FLOAT           # 跌停价
        
        # tick的时间
        self.date = EMPTY_STRING            # 日期
        self.time = EMPTY_STRING            # 时间
        self.datetime = None                # python的datetime时间对象
        
        # 五档行情
        self.bidPrice1 = EMPTY_FLOAT
        self.bidPrice2 = EMPTY_FLOAT
        self.bidPrice3 = EMPTY_FLOAT
        self.bidPrice4 = EMPTY_FLOAT
        self.bidPrice5 = EMPTY_FLOAT
        
        self.askPrice1 = EMPTY_FLOAT
        self.askPrice2 = EMPTY_FLOAT
        self.askPrice3 = EMPTY_FLOAT
        self.askPrice4 = EMPTY_FLOAT
        self.askPrice5 = EMPTY_FLOAT        
        
        self.bidVolume1 = EMPTY_INT
        self.bidVolume2 = EMPTY_INT
        self.bidVolume3 = EMPTY_INT
        self.bidVolume4 = EMPTY_INT
        self.bidVolume5 = EMPTY_INT
        
        self.askVolume1 = EMPTY_INT
        self.askVolume2 = EMPTY_INT
        self.askVolume3 = EMPTY_INT
        self.askVolume4 = EMPTY_INT
        self.askVolume5 = EMPTY_INT    


########################################################################
class CtaEngine(object):
    """CTA策略引擎"""
    settingFileName = 'CTA_setting.json'

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, dataEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        self.dataEngine = dataEngine
        
        # 保存策略对象的字典
        # key为策略名称，value为策略对象，注意策略名称不允许重复
        self.strategyDict = {}
        
        # 保存vtSymbol和策略对象映射的字典（用于推送tick数据）
        # 由于可能多个strategy交易同一个vtSymbol，因此key为vtSymbol
        # value为包含所有相关strategy对象的list
        self.tickStrategyDict = {}
        
        # 保存vtOrderID和strategy对象映射的字典（用于推送order和trade数据）
        # key为vtOrderID，value为strategy对象
        self.orderStrategyDict = {}     
        
        # 本地停止单编号计数
        self.stopOrderCount = 0
        # stopOrderID = STOPORDERPREFIX + str(stopOrderCount)
        
        # 本地停止单字典
        # key为stopOrderID，value为stopOrder对象
        self.stopOrderDict = {}             # 停止单撤销后不会从本字典中删除
        self.workingStopOrderDict = {}      # 停止单撤销后会从本字典中删除
        
<<<<<<< HEAD
<<<<<<< HEAD
=======
        # 注册事件监听
        self.registerEvent()
        
>>>>>>> refs/remotes/vnpy/master
=======
        # 注册事件监听
        self.registerEvent()
        
>>>>>>> refs/remotes/vnpy/master
    #----------------------------------------------------------------------
    def sendOrder(self, vtSymbol, orderType, price, volume, strategy):
        """发单"""
        contract = self.dataEngine.getContract(vtSymbol)
        
        req = VtOrderReq()
        req.symbol = contract.symbol
        req.exchange = contract.exchange
        req.price = price
        req.volume = volume
        
        # 设计为CTA引擎发出的委托只允许使用限价单
        req.priceType = PRICETYPE_LIMITPRICE    
        
        # CTA委托类型映射
        if orderType == CTAORDER_BUY:
            req.direction = DIRECTION_LONG
            req.offset = OFFSET_OPEN
        elif orderType == CTAORDER_SELL:
            req.direction = DIRECTION_SHORT
            req.offset = OFFSET_CLOSE
        elif orderType == CTAORDER_SHORT:
            req.direction = DIRECTION_SHORT
            req.offset = OFFSET_OPEN
        elif orderType == CTAORDER_COVER:
            req.direction = DIRECTION_LONG
            req.offset = OFFSET_CLOSE
        
        vtOrderID = self.mainEngine.sendOrder(req)  # 发单
        self.orderDict[vtOrderID] = strategy        # 保存vtOrderID和策略的映射关系
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, vtOrderID):
        """撤单"""
        # 查询报单对象
        order = self.dataEngine.getOrder(vtOrderID)
        
        # 如果查询成功
        if order:
            # 检查是否报单还有效，只有有效时才发出撤单指令
            orderFinished = (order.status==STATUS_ALLTRADED or order.status==STATUS_CANCELLED)
            if not orderFinished:
                req = VtCancelOrderReq()
                req.symbol = order.symbol
                req.exchange = order.exchange
                req.frontID = order.frontID
                req.sessionID = order.sessionID
                req.orderID = order.orderID
                self.mainEngine.cancelOrder(req, order.gatewayName)    
        
    #----------------------------------------------------------------------
    def sendStopOrder(self, vtSymbol, orderType, price, volume, strategy):
        """发停止单（本地实现）"""
        self.stopOrderCount += 1
        stopOrderID = STOPORDERPREFIX + str(self.stopOrderCount)
        
        so = StopOrder()
        so.vtSymbol = vtSymbol
        so.orderType = orderType
        so.price = price
        so.volume = volume
        so.strategy = strategy
        so.stopOrderID = stopOrderID
        so.status = STOPORDER_WAITING
        
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
    def processStopOrder(self, tick):
        """收到行情后处理本地停止单（检查是否要立即发出）"""
        vtSymbol = tick.vtSymbol
        
        # 首先检查是否有策略交易该合约
        if vtSymbol in self.tickStrategyDict:
            # 遍历等待中的停止单，检查是否会被触发
            for so in self.workingStopOrderDict.values():
                if so.vtSymbol == vtSymbol:
                    longTriggered = so.direction==DIRECTION_LONG and tick.lastPrice>=so.price        # 多头停止单被触发
                    shortTriggered = so.direction==DIRECTION_SHORT and tick.lasatPrice<=so.price     # 空头停止单被触发
                    
                    if longTriggered or shortTriggered:
                        # 买入和卖出分别以涨停跌停价发单（模拟市价单）
                        if so.direction==DIRECTION_LONG:
                            price = tick.upperLimit
                        else:
                            price = tick.lowerLimit
                        
                        so.status = STOPORDER_TRIGGERED
                        self.sendOrder(so.vtSymbol, so.orderType, price, so.volume, so.strategy)
                        del self.workingStopOrderDict[so.stopOrderID]
        
    #----------------------------------------------------------------------
<<<<<<< HEAD
<<<<<<< HEAD
    def procecssTick(self, tick):
        """处理行情推送"""
=======
    def procecssTickEvent(self, event):
        """处理行情推送"""
        tick = event.dict_['data']
>>>>>>> refs/remotes/vnpy/master
=======
    def procecssTickEvent(self, event):
        """处理行情推送"""
        tick = event.dict_['data']
>>>>>>> refs/remotes/vnpy/master
        # 收到tick行情后，先处理本地停止单（检查是否要立即发出）
        self.processStopOrder(tick)
        
        # 推送tick到对应的策略对象进行处理
        if tick.vtSymbol in self.tickStrategyDict:
            # 将vtTickData数据转化为ctaTickData
            ctaTick = CtaTickData()
            d = ctaTick.__dict__
            for key in d.keys():
<<<<<<< HEAD
<<<<<<< HEAD
                d[key] = tick.__getattribute__(key)
=======
                if key != 'datetime':
                    d[key] = tick.__getattribute__(key)
>>>>>>> refs/remotes/vnpy/master
=======
                if key != 'datetime':
                    d[key] = tick.__getattribute__(key)
>>>>>>> refs/remotes/vnpy/master
            # 添加datetime字段
            ctaTick.datetime = datetime.strptime(' '.join([tick.date, tick.time]), '%Y%m%d %H:%M:%S.%f')
            
            # 逐个推送到策略对象中
            l = self.tickStrategyDict[tick.vtSymbol]
            for strategy in l:
                strategy.onTick(tick)
    
    #----------------------------------------------------------------------
<<<<<<< HEAD
<<<<<<< HEAD
    def processOrder(self, order):
        """处理委托推送"""
=======
=======
>>>>>>> refs/remotes/vnpy/master
    def processOrderEvent(self, event):
        """处理委托推送"""
        order = event.dict_['data']
        
<<<<<<< HEAD
>>>>>>> refs/remotes/vnpy/master
=======
>>>>>>> refs/remotes/vnpy/master
        if order.vtOrderID in self.orderStrategyDict:
            strategy = self.orderStrategyDict[order.vtOrderID]            
            strategy.onOrder(order)
    
    #----------------------------------------------------------------------
<<<<<<< HEAD
<<<<<<< HEAD
    def processTrade(self, trade):
        """处理成交推送"""
=======
=======
>>>>>>> refs/remotes/vnpy/master
    def processTradeEvent(self, event):
        """处理成交推送"""
        trade = event.dict_['data']
        
<<<<<<< HEAD
>>>>>>> refs/remotes/vnpy/master
=======
>>>>>>> refs/remotes/vnpy/master
        if trade.vtOrderID in self.orderStrategyDict:
            strategy = self.orderStrategyDict[order.vtOrderID]
            strategy.onTrade(trade)
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
<<<<<<< HEAD
<<<<<<< HEAD
        self.eventEngine.register(EVENT_TICK, self.procecssTick)
        self.eventEngine.register(EVENT_ORDER, self.processOrder)
        self.eventEngine.register(EVENT_TRADE, self.processTrade)
=======
        self.eventEngine.register(EVENT_TICK, self.procecssTickEvent)
        self.eventEngine.register(EVENT_ORDER, self.processOrderEvent)
        self.eventEngine.register(EVENT_TRADE, self.processTradeEvent)
>>>>>>> refs/remotes/vnpy/master
=======
        self.eventEngine.register(EVENT_TICK, self.procecssTickEvent)
        self.eventEngine.register(EVENT_ORDER, self.processOrderEvent)
        self.eventEngine.register(EVENT_TRADE, self.processTradeEvent)
>>>>>>> refs/remotes/vnpy/master
        
    #----------------------------------------------------------------------
    def insertData(self, dbName, collectionName, data):
        """插入数据到数据库（这里的data可以是CtaTickData或者CtaBarData）"""
        self.mainEngine.dbInsert(dbName, collectionName, data.__dict__)
    
    #----------------------------------------------------------------------
    def loadBar(self, dbName, collectionName, startDate):
        """从数据库中读取Bar数据，startDate是datetime对象"""
        d = {'datetime':{'$gte':startDate}}
        cursor = self.mainEngine.dbQuery(dbName, collectionName, d)
        
        l = []
        for d in cursor:
            bar = CtaBarData()
            bar.__dict__ = d
            l.append(bar)
            
        return l
    
    #----------------------------------------------------------------------
    def loadTick(self, dbName, collectionName, startDate):
        """从数据库中读取Tick数据，startDate是datetime对象"""
        d = {'datetime':{'$gte':startDate}}
        cursor = self.mainEngine.dbQuery(dbName, collectionName, d)
        
        l = []
        for d in cursor:
            tick = CtaTickData()
            tick.__dict__ = d
            l.append(tick)
        
        return l    
    
    #----------------------------------------------------------------------
    def getToday(self):
        """获取代表今日的datetime对象"""
        today = datetime.today()
        today = today.replace(hour=0, minute=0, second=0, microsecond=0)
        return today
    
    #----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """快速发出CTA模块日志事件"""
        log = VtLogData()
        log.logContent = content
        event = Event(type_=EVENT_CTA_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)   
    
    #----------------------------------------------------------------------
    def initStrategy(self, name, strategyClass, paramDict=None):
        """初始化策略"""
        # 防止策略重名
        if name not in self.strategyDict:
<<<<<<< HEAD
<<<<<<< HEAD
            self.strategyDict[name] = strategyClass(self, paramDict)  # 创建策略对象
=======
=======
>>>>>>> refs/remotes/vnpy/master
            # 创建策略对象
            strategy = strategyClass(self, name, paramDict)  
            self.strategyDict[name] = strategy
            
            # 保存Tick映射关系
            if strategy.vtSymbol in self.tickStrategyDict:
                l = self.tickStrategyDict[strategy.vtSymbol]
            else:
                l = []
                self.tickStrategyDict[strategy.vtSymbol] = l
            l.append(strategy)
            
            # 订阅合约
            contract = self.dataEngine.getContract(strategy.vtSymbol)
            if contract:
                req = VtSubscribeReq()
                req.symbol = contract.symbol
                req.exchange = contract.exchange
                self.mainEngine.subscribe(req, contract.gatewayName)
<<<<<<< HEAD
>>>>>>> refs/remotes/vnpy/master
=======
>>>>>>> refs/remotes/vnpy/master
        else:
            self.writeCtaLog(u'存在策略对象重名：' + name)

    #---------------------------------------------------------------------
    def startStrategy(self, name):
        """启动策略"""
        if name in self.strategyDict:
            strategy = self.strategyDict[name]
            
            if not strategy.trading:
                strategy.trading = True
                strategy.start()
        else:
            self.writeCtaLog(u'策略对象不存在：' + name)
    
    #----------------------------------------------------------------------
    def stopStrategy(self, name):
        """停止策略"""
        if name in self.strategyDict:
            strategy = self.strategyDict[name]
            
            if strategy.trading:
                strategy.trading = False
                strategy.stop()
                
                # 对该策略发出的所有限价单进行撤单
                for vtOrderID, s in self.orderStrategyDict.items():
                    if s is strategy:
                        self.cancelOrder(vtOrderID)
                
                # 对该策略发出的所有本地停止单撤单
                for stopOrderID, so in self.workingStopOrderDict.items():
                    if so.strategy is strategy:
                        self.cancelStopOrder(stopOrderID)   
        else:
            self.writeCtaLog(u'策略对象不存在：' + name)        
    
    #----------------------------------------------------------------------
    def saveStrategySetting(self):
        """保存引擎中的策略配置"""
        with open(self.settingFileName, 'w') as f:
            d = {}
            
            for name, strategy in self.strategyDict.items():
                setting = {}
                setting['strategyClassName'] = strategy.strategyClassName
                for param in strategy.paramList:
                    setting[param] = strategy.__getattribute__(param)
                d[name] = setting
            
            jsonD = json.dumps(d, indent=4)
            f.write(jsonD)
    
    #----------------------------------------------------------------------
    def loadStrategySetting(self):
        """读取引擎中的策略配置"""
        with open(self.settingFileName) as f:
            d = json.load(f)
            
            for name, setting in d.items():
                strategyClassName = setting['strategyClassName']
                
                if strategyClassName in strategyClassDict:
                    strategyClass = strategyClassDict[strategyClassName]
                    self.initStrategy(name, strategyClass, setting)
                else:
                    self.writeCtaLog(u'无法找到策略类：' + strategyClassName)
                    break
    
    #----------------------------------------------------------------------
<<<<<<< HEAD
<<<<<<< HEAD
    def getStrategyVarialbe(self, name):
=======
    def getStrategyVar(self, name):
>>>>>>> refs/remotes/vnpy/master
=======
    def getStrategyVar(self, name):
>>>>>>> refs/remotes/vnpy/master
        """获取策略当前的变量字典"""
        if name in self.strategyDict:
            strategy = self.strategyDict[name]
            d = strategy.__dict__
            varDict = OrderedDict()
            
            for key in strategy.varList:
                if key in d:
                    varDict[key] = d[key]
            
            return varDict
        else:
            self.writeCtaLog(u'策略对象不存在：' + name)    
            return None
    
    #----------------------------------------------------------------------
<<<<<<< HEAD
<<<<<<< HEAD
    def getStrategyParameter(self, name):
=======
    def getStrategyParam(self, name):
>>>>>>> refs/remotes/vnpy/master
=======
    def getStrategyParam(self, name):
>>>>>>> refs/remotes/vnpy/master
        """获取策略的参数字典"""
        if name in self.strategyDict:
            strategy = self.strategyDict[name]
            d = strategy.__dict__
<<<<<<< HEAD
<<<<<<< HEAD
            varDict = OrderedDict()
            
            for key in strategy.paramList:
                if key in d:
                    varDict[key] = d[key]
            
            return varDict
=======
=======
>>>>>>> refs/remotes/vnpy/master
            paramDict = OrderedDict()
            
            for key in strategy.paramList:
                if key in d:
                    paramDict[key] = d[key]
            
            return paramDict
<<<<<<< HEAD
>>>>>>> refs/remotes/vnpy/master
=======
>>>>>>> refs/remotes/vnpy/master
        else:
            self.writeCtaLog(u'策略对象不存在：' + name)    
            return None        


