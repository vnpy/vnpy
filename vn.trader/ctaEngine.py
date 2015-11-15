# encoding: UTF-8

from datetime import datetime
import json
from collections import OrderedDict

from eventEngine import *
from vtConstant import *

from vtGateway import VtSubscribeReq, VtOrderReq, VtCancelOrderReq, VtLogData

from ctaConstant import *
from ctaStrategies import strategyClassDict


########################################################################
class StopOrder(object):
    """本地停止单"""

    # ----------------------------------------------------------------------
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

    # ----------------------------------------------------------------------
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

    # ----------------------------------------------------------------------
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

    # 策略配置文件
    settingFileName = 'CTA_setting.json'

    # ----------------------------------------------------------------------
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

        # 注册事件监听
        self.registerEvent()

    # ----------------------------------------------------------------------
    def sendOrder(self, vtSymbol, orderType, price, volume, strategy):
        """发单"""

        # 1.查询合约对象
        contract = self.dataEngine.getContract(vtSymbol)

        # 2. 创建发单传入对象
        req = VtOrderReq()
        req.symbol = contract.symbol        # 合约代码
        req.exchange = contract.exchange    # 交易所
        req.price = price                   # 价格
        req.volume = volume                 # 数量
        
        # 设计为CTA引擎发出的委托只允许使用限价单
        req.priceType = PRICETYPE_LIMITPRICE     # 价格类型
        
        # CTA委托类型映射
        if orderType == CTAORDER_BUY:
            req.direction = DIRECTION_LONG      # 合约方向
            req.offset = OFFSET_OPEN            # 开/平
        elif orderType == CTAORDER_SELL:
            req.direction = DIRECTION_SHORT
            req.offset = OFFSET_CLOSE
        elif orderType == CTAORDER_SHORT:
            req.direction = DIRECTION_SHORT
            req.offset = OFFSET_OPEN
        elif orderType == CTAORDER_COVER:
            req.direction = DIRECTION_LONG
            req.offset = OFFSET_CLOSE

        # 3.调用主引擎的发单接口进行发单，保存OrderID与策略映射关系
        vtOrderID = self.mainEngine.sendOrder(req)  # 发单
        self.orderDict[vtOrderID] = strategy        # 保存vtOrderID和策略的映射关系

        return vtOrderID
    
    # ----------------------------------------------------------------------
    def cancelOrder(self, vtOrderID):
        """撤单"""

        # 1.调用主引擎接口，查询委托单对象
        order = self.dataEngine.getOrder(vtOrderID)
        
        # 如果查询成功
        if order:
            # 2.检查是否报单（委托单）还有效，只有有效时才发出撤单指令
            orderFinished = (order.status == STATUS_ALLTRADED or order.status == STATUS_CANCELLED)
            if not orderFinished:
                req = VtCancelOrderReq()
                req.symbol = order.symbol
                req.exchange = order.exchange
                req.frontID = order.frontID
                req.sessionID = order.sessionID
                req.orderID = order.orderID
                self.mainEngine.cancelOrder(req, order.gatewayName)
            else:
                if order.status == STATUS_ALLTRADED:
                    self.writeCtaLog(u'委托单({0}已执行，无法撤销'.format(vtOrderID))
                if order.status == STATUS_CANCELLED:
                    self.writeCtaLog(u'委托单({0}已撤销，无法再次撤销'.format(vtOrderID))
        # 查询不成功
        else:
            self.writeCtaLog(u'委托单({0}不存在'.format(vtOrderID))

    # ----------------------------------------------------------------------
    def sendStopOrder(self, vtSymbol, orderType, price, volume, strategy):
        """发停止单（本地实现）"""

        # 1.生成本地停止单ID
        self.stopOrderCount += 1
        stopOrderID = STOPORDERPREFIX + str(self.stopOrderCount)

        # 2.创建停止单对象
        so = StopOrder()
        so.vtSymbol = vtSymbol          # 代码
        so.orderType = orderType        # 停止单类型
        so.price = price                # 价格
        so.volume = volume              # 数量
        so.strategy = strategy          # 来源策略
        so.stopOrderID = stopOrderID    # Id
        so.status = STOPORDER_WAITING   # 状态
        
        # 3.保存stopOrder对象到字典中
        self.stopOrderDict[stopOrderID] = so            # 字典中不会删除
        self.workingStopOrderDict[stopOrderID] = so     # 字典中会删除

        self.writeCtaLog(u'发停止单成功，'
                         u'Id:{0},Symbol:{1},Type:{2},Price:{3},Volume:{4}'
                         u'.'.format(stopOrderID, vtSymbol, orderType, price, volume))

        return stopOrderID
    
    # ----------------------------------------------------------------------
    def cancelStopOrder(self, stopOrderID):
        """撤销停止单"""
        # 1.检查停止单是否存在
        if stopOrderID in self.workingStopOrderDict:
            so = self.workingStopOrderDict[stopOrderID]
            so.status = STOPORDER_CANCELLED                 # STOPORDER_WAITING =》STOPORDER_CANCELLED
            del self.workingStopOrderDict[stopOrderID]      # 删除
            self.writeCtaLog(u'撤销停止单:{0}成功.'.format(stopOrderID))
        else:
            self.writeCtaLog(u'撤销停止单:{0}失败，不存在Id.'.format(stopOrderID))
            
    # ----------------------------------------------------------------------
    def processStopOrder(self, tick):
        """收到行情后处理本地停止单（检查是否要立即发出）"""
        vtSymbol = tick.vtSymbol
        
        # 1.首先检查是否有策略交易该合约
        if vtSymbol in self.tickStrategyDict:
            # 2.遍历等待中的停止单，检查是否会被触发
            for so in self.workingStopOrderDict.values():

                if so.vtSymbol == vtSymbol:
                    # 3. 触发标识判断
                    longTriggered = so.direction == DIRECTION_LONG and tick.lastPrice >= so.price        # 多头停止单被触发
                    shortTriggered = so.direction == DIRECTION_SHORT and tick.lasatPrice <= so.price     # 空头停止单被触发

                    # 4.触发处理
                    if longTriggered or shortTriggered:

                        # 5.设定价格，买入和卖出分别以涨停跌停价发单（模拟市价单）
                        if so.direction == DIRECTION_LONG:
                            price = tick.upperLimit
                        else:
                            price = tick.lowerLimit

                        # 6.更新停止单状态，触发
                        so.status = STOPORDER_TRIGGERED

                        # 7.发单
                        self.sendOrder(so.vtSymbol, so.orderType, price, so.volume, so.strategy)

                        # 8.删除停止单
                        del self.workingStopOrderDict[so.stopOrderID]
        
    # ----------------------------------------------------------------------

    def procecssTickEvent(self, event):
        """处理行情推送事件"""

        # 1. 获取事件的Tick数据
        tick = event.dict_['data']

        # 2.收到tick行情后，优先处理本地停止单（检查是否要立即发出）
        self.processStopOrder(tick)
        
        # 3.推送tick到对应的策略对象进行处理
        if tick.vtSymbol in self.tickStrategyDict:

            # 4.将vtTickData数据转化为ctaTickData
            ctaTick = CtaTickData()
            d = ctaTick.__dict__
            for key in d.keys():

                if key != 'datetime':
                    d[key] = tick.__getattribute__(key)

            # 5.添加datetime字段
            ctaTick.datetime = datetime.strptime(' '.join([tick.date, tick.time]), '%Y%m%d %H:%M:%S.%f')
            
            l = self.tickStrategyDict[tick.vtSymbol]
            for strategy in l:
                strategy.onTick(tick)
    
    # ----------------------------------------------------------------------

    def processOrderEvent(self, event):
        """处理委托推送事件"""
        # 1.获取事件的Order数据
        order = event.dict_['data']

        # 2.判断order是否在映射字典中
        if order.vtOrderID in self.orderStrategyDict:

            # 3.提取对应的策略
            strategy = self.orderStrategyDict[order.vtOrderID]

            # 4.触发策略的委托推送事件方法
            strategy.onOrder(order)
    
    # ----------------------------------------------------------------------

    def processTradeEvent(self, event):
        """处理成交推送事件"""

        # 1.获取事件的Trade数据
        trade = event.dict_['data']

        # 2.判断Trade是否在映射字典中
        if trade.vtOrderID in self.orderStrategyDict:

            # 3.提取对应的策略
            strategy = self.orderStrategyDict[trade.vtOrderID]

            # 4.触发策略的成交推送事件。
            strategy.onTrade(trade)
    
    # ----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""

        # 注册行情数据推送（Tick数据到达）的响应事件
        self.eventEngine.register(EVENT_TICK, self.procecssTickEvent)

        # 注册订单推送的响应事件
        self.eventEngine.register(EVENT_ORDER, self.processOrderEvent)

        # 注册成交推送（交易）的响应时间
        self.eventEngine.register(EVENT_TRADE, self.processTradeEvent)

    # ----------------------------------------------------------------------
    def insertData(self, dbName, collectionName, data):
        """插入数据到数据库（这里的data可以是CtaTickData或者CtaBarData）"""
        self.mainEngine.dbInsert(dbName, collectionName, data.__dict__)
    
    # ----------------------------------------------------------------------
    def loadBar(self, dbName, collectionName, startDate):
        """从数据库中读取Bar数据
        startDate是datetime对象"""
        d = {'datetime':{'$gte':startDate}}
        cursor = self.mainEngine.dbQuery(dbName, collectionName, d)
        
        l = []
        for d in cursor:
            bar = CtaBarData()
            bar.__dict__ = d
            l.append(bar)
            
        return l
    
    # ----------------------------------------------------------------------
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
    
    # ----------------------------------------------------------------------
    def getToday(self):
        """获取代表今日的datetime对象"""
        today = datetime.today()
        today = today.replace(hour=0, minute=0, second=0, microsecond=0)
        return today
    
    # ----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """快速发出CTA模块日志事件"""
        log = VtLogData()
        log.logContent = content
        event = Event(type_=EVENT_CTA_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)   
    
    # ----------------------------------------------------------------------
    def initStrategy(self, name, strategyClass, paramDict=None):
        """初始化策略"""
        # 防止策略重名
        if name not in self.strategyDict:

            # 1.创建策略对象
            strategy = strategyClass(self, name, paramDict)  
            self.strategyDict[name] = strategy
            
            # 2.保存Tick映射关系（symbol <==> Strategy[] )
            if strategy.vtSymbol in self.tickStrategyDict:
                l = self.tickStrategyDict[strategy.vtSymbol]
            else:
                l = []
                self.tickStrategyDict[strategy.vtSymbol] = l
            l.append(strategy)
            
            # 3.订阅合约
            contract = self.dataEngine.getContract(strategy.vtSymbol)
            if contract:
                # 4.构造订阅请求包
                req = VtSubscribeReq()
                req.symbol = contract.symbol
                req.exchange = contract.exchange

                # 5.调用主引擎的订阅接口
                self.mainEngine.subscribe(req, contract.gatewayName)

        else:
            self.writeCtaLog(u'存在策略对象重名：' + name)

    # ---------------------------------------------------------------------
    def startStrategy(self, name):
        """启动策略"""

        # 1.判断策略名称是否存在字典中
        if name in self.strategyDict:

            # 2.提取策略
            strategy = self.strategyDict[name]

            # 3.判断策略是否运行
            if not strategy.trading:
                # 4.设置运行状态
                strategy.trading = True
                # 5.启动策略
                strategy.start()
        else:
            self.writeCtaLog(u'策略对象不存在：' + name)
    
    # ----------------------------------------------------------------------
    def stopStrategy(self, name):
        """停止策略运行"""

        # 1.判断策略名称是否存在字典中
        if name in self.strategyDict:
            # 2.提取策略
            strategy = self.strategyDict[name]

            # 3.停止交易
            if strategy.trading:

                # 4.设置交易状态为False
                strategy.trading = False

                # 5.调用策略的停止方法
                strategy.stop()
                
                # 6.对该策略发出的所有限价单进行撤单
                for vtOrderID, s in self.orderStrategyDict.items():
                    if s is strategy:
                        self.cancelOrder(vtOrderID)
                
                # 7.对该策略发出的所有本地停止单撤单
                for stopOrderID, so in self.workingStopOrderDict.items():
                    if so.strategy is strategy:
                        self.cancelStopOrder(stopOrderID)   
        else:
            self.writeCtaLog(u'策略对象不存在：' + name)        
    
    # ----------------------------------------------------------------------
    def saveStrategySetting(self):
        """保存引擎中的策略配置"""
        with open(self.settingFileName, 'w') as f:
            d = {}

            # 逐一循环：name，策略实例名称，strategy，策略
            for name, strategy in self.strategyDict.items():
                # 配置串
                setting = {}

                # 策略的类名称
                setting['strategyClassName'] = strategy.strategyClassName

                # 策略的参数
                for param in strategy.paramList:
                    setting[param] = strategy.__getattribute__(param)

                # 策略实例名，保存配置
                d[name] = setting

            # Json对象=》Json字符串
            jsonD = json.dumps(d, indent=4)

            # 保存文件
            f.write(jsonD)
    
    # ----------------------------------------------------------------------
    def loadStrategySetting(self):
        """读取引擎中的策略配置"""
        with open(self.settingFileName) as f:
            # 读取文件内容串=》Json对象
            d = json.load(f)

            # 策略实例名称，配置内容
            for name, setting in d.items():

                # 策略的类名称
                strategyClassName = setting['strategyClassName']

                if strategyClassName in strategyClassDict:
                    # 透过策略类字典，反射获取策略
                    strategyClass = strategyClassDict[strategyClassName]

                    # 初始化策略的设置
                    self.initStrategy(name, strategyClass, setting)
                else:
                    self.writeCtaLog(u'无法找到策略类：' + strategyClassName)
                    break
    
    # ----------------------------------------------------------------------
    def getStrategyVar(self, name):
        """获取策略当前的变量字典"""
        if name in self.strategyDict:
            # 获取策略实例
            strategy = self.strategyDict[name]

            # 策略实例的所有属性
            d = strategy.__dict__

            # 变量字典
            varDict = OrderedDict()

            # 策略中的变量名称列表
            for key in strategy.varList:

                # 如果匹配就增加
                if key in d:
                    varDict[key] = d[key]
            
            return varDict
        else:
            self.writeCtaLog(u'策略对象不存在：' + name)    
            return None
    
    # ----------------------------------------------------------------------
    def getStrategyParam(self, name):
        """获取策略的参数字典"""
        if name in self.strategyDict:
            # 获取策略实例
            strategy = self.strategyDict[name]

            # 策略实例的所有属性
            d = strategy.__dict__

            # 参数字典
            paramDict = OrderedDict()

            # 策略内的参数名称列表
            for key in strategy.paramList:

                # 匹配的就添加
                if key in d:
                    paramDict[key] = d[key]
            
            return paramDict

        else:
            self.writeCtaLog(u'策略对象不存在：' + name)    
            return None        


