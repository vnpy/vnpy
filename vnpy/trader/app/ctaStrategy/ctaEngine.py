# encoding: UTF-8

'''
本文件中实现了CTA策略引擎，针对CTA类型的策略，抽象简化了部分底层接口的功能。

关于平今和平昨规则：
1. 普通的平仓OFFSET_CLOSET等于平昨OFFSET_CLOSEYESTERDAY
2. 只有上期所的品种需要考虑平今和平昨的区别
3. 当上期所的期货有今仓时，调用Sell和Cover会使用OFFSET_CLOSETODAY，否则
   会使用OFFSET_CLOSE
4. 以上设计意味着如果Sell和Cover的数量超过今日持仓量时，会导致出错（即用户
   希望通过一个指令同时平今和平昨）
5. 采用以上设计的原因是考虑到vn.trader的用户主要是对TB、MC和金字塔类的平台
   感到功能不足的用户（即希望更高频的交易），交易策略不应该出现4中所述的情况
6. 对于想要实现4中所述情况的用户，需要实现一个策略信号引擎和交易委托引擎分开
   的定制化统结构（没错，得自己写）

 Modified by IncenseLee（李来佳）
 1、增加单一策略里，多个vtSymbol的配置。

'''

import json
import os
import traceback
from collections import OrderedDict
from datetime import datetime, timedelta
import logging
import re


from ctaBase import *
from strategy import STRATEGY_CLASS
from vnpy.trader.vtEvent import *
from vnpy.trader.vtConstant import *
from vnpy.trader.vtGateway import VtSubscribeReq, VtOrderReq, VtCancelOrderReq, VtLogData
from vnpy.trader.vtFunction import todayDate


########################################################################
class CtaEngine(object):
    """CTA策略引擎"""

    # 策略配置文件
    settingFileName = 'CTA_setting.json'
    path = os.path.abspath(os.path.dirname(__file__))
    settingFileName = os.path.join(path, settingFileName)

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        # 当前日期
        self.today = todayDate()
        
        # 保存策略实例的字典
        # key为策略名称，value为策略实例，注意策略名称不允许重复
        self.strategyDict = {}
        
        # 保存vtSymbol和策略实例映射的字典（用于推送tick数据）
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
        
        # 持仓缓存字典
        # key为vtSymbol，value为PositionBuffer对象
        self.posBufferDict = {}
        
        # 成交号集合，用来过滤已经收到过的成交推送
        self.tradeSet = set()

        # 引擎类型为实盘
        self.engineType = ENGINETYPE_TRADING

        # tick缓存
        self.tickDict = {}

        # 未能订阅的symbols
        self.pendingSubcribeSymbols = {}

        # 注册事件监听
        self.registerEvent()

    # ----------------------------------------------------------------------
    def sendOrder(self, vtSymbol, orderType, price, volume, strategy):
        """发单"""
        contract = self.mainEngine.getContract(vtSymbol)
        
        req = VtOrderReq()
        req.symbol = contract.symbol        # 合约代码
        req.exchange = contract.exchange    # 交易所
        req.price = self.roundToPriceTick(contract.priceTick, price)         # 价格
        req.volume = volume                 # 数量

        if strategy:
            req.productClass = strategy.productClass
            req.currency = strategy.currency
        else:
            req.productClass = ''
            req.currency = ''


        # 设计为CTA引擎发出的委托只允许使用限价单
        req.priceType = PRICETYPE_LIMITPRICE     # 价格类型
        
        # CTA委托类型映射
        if orderType == CTAORDER_BUY:
            req.direction = DIRECTION_LONG      # 合约方向
            req.offset = OFFSET_OPEN            # 开/平
        elif orderType == CTAORDER_SELL:
            req.direction = DIRECTION_SHORT
            
            # 只有上期所才要考虑平今平昨
            if contract.exchange != EXCHANGE_SHFE:
                req.offset = OFFSET_CLOSE
            else:
                # 获取持仓缓存数据
                posBuffer = self.posBufferDict.get(vtSymbol, None)
                # 如果获取持仓缓存失败，则默认平昨
                if not posBuffer:
                    req.offset = OFFSET_CLOSE

                # modified by IncenseLee 2016/11/08，改为优先平昨仓
                elif posBuffer.longYd :
                    req.offset = OFFSET_CLOSE
                else:
                    req.offset = OFFSET_CLOSETODAY

                # 否则如果有多头今仓，则使用平今
                #elif posBuffer.longToday:
                #    req.offset= OFFSET_CLOSETODAY
                # 其他情况使用平昨
                #else:
                #    req.offset = OFFSET_CLOSE
                
        elif orderType == CTAORDER_SHORT:
            req.direction = DIRECTION_SHORT
            req.offset = OFFSET_OPEN
            
        elif orderType == CTAORDER_COVER:
            req.direction = DIRECTION_LONG
            
            # 只有上期所才要考虑平今平昨
            if contract.exchange != EXCHANGE_SHFE:
                req.offset = OFFSET_CLOSE
            else:
                # 获取持仓缓存数据
                posBuffer = self.posBufferDict.get(vtSymbol, None)
                # 如果获取持仓缓存失败，则默认平昨
                if not posBuffer:
                    req.offset = OFFSET_CLOSE

                #modified by IncenseLee 2016/11/08，改为优先平昨仓
                elif posBuffer.shortYd:
                    req.offset = OFFSET_CLOSE
                else:
                    req.offset = OFFSET_CLOSETODAY

                # 否则如果有空头今仓，则使用平今
                #elif posBuffer.shortToday:
                #    req.offset= OFFSET_CLOSETODAY
                # 其他情况使用平昨
                #else:
                #    req.offset = OFFSET_CLOSE
        
        vtOrderID = self.mainEngine.sendOrder(req, contract.gatewayName)    # 发单

        if strategy:
            self.orderStrategyDict[vtOrderID] = strategy        # 保存vtOrderID和策略的映射关系

            self.writeCtaLog(u'策略%s发送委托，%s, %s，%s，%s@%s'
                         %(strategy.name, vtSymbol, req.offset, req.direction, volume, price))
        else:
            self.writeCtaLog(u'%s发送委托，%s, %s，%s，%s@%s'
                             % ('CtaEngine', vtSymbol, req.offset, req.direction, volume, price))
        return vtOrderID
    
    # ----------------------------------------------------------------------
    def cancelOrder(self, vtOrderID):
        """撤单"""
        # 查询报单对象
        # 1.调用主引擎接口，查询委托单对象
        order = self.mainEngine.getOrder(vtOrderID)
        
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
    def cancelOrders(self, symbol, offset=EMPTY_STRING):
        """撤销所有单"""
        # Symbol参数:指定合约的撤单；
        # OFFSET参数:指定Offset的撤单,缺省不填写时，为所有

        l = self.mainEngine.getAllWorkingOrders()

        self.writeCtaLog(u'从所有订单{0}中撤销{1}'.format(len(l), symbol))

        for order in l:

            if symbol == EMPTY_STRING:
                symbolCond = True
            else:
                symbolCond = order.symbol == symbol

            if offset == EMPTY_STRING:
                offsetCond = True
            else:
                offsetCond = order.offset == offset

            if symbolCond and offsetCond:
                req = VtCancelOrderReq()
                req.symbol = order.symbol
                req.exchange = order.exchange
                req.frontID = order.frontID
                req.sessionID = order.sessionID
                req.orderID = order.orderID
                self.writeCtaLog(u'撤单:{0}/{1},{2}{3}手'
                                 .format(order.symbol, order.orderID, order.offset, order.totalVolume-order.tradedVolume))
                self.mainEngine.cancelOrder(req, order.gatewayName)

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
        self.stopOrderDict[stopOrderID] = so            # 字典中不会删除
        self.workingStopOrderDict[stopOrderID] = so     # 字典中会删除

        self.writeCtaLog(u'发停止单成功，'
                         u'Id:{0},Symbol:{1},Type:{2},Price:{3},Volume:{4}'
                         u'.'.format(stopOrderID, vtSymbol, orderType, price, volume))
        
        return stopOrderID
    
    # ----------------------------------------------------------------------
    def cancelStopOrder(self, stopOrderID):
        """撤销停止单
        Incense Li modified 20160124：
        增加返回True 和 False
        """
        # 1.检查停止单是否存在
        if stopOrderID in self.workingStopOrderDict:
            so = self.workingStopOrderDict[stopOrderID]
            so.status = STOPORDER_CANCELLED                 # STOPORDER_WAITING =》STOPORDER_CANCELLED
            del self.workingStopOrderDict[stopOrderID]      # 删除
            self.writeCtaLog(u'撤销停止单:{0}成功.'.format(stopOrderID))
            return True
        else:
            self.writeCtaLog(u'撤销停止单:{0}失败，不存在Id.'.format(stopOrderID))
            return False

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
                    shortTriggered = so.direction == DIRECTION_SHORT and tick.lastPrice <= so.price     # 空头停止单被触发

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

        # 移除待订阅的合约清单
        if tick.vtSymbol in self.pendingSubcribeSymbols:
            self.writeCtaLog(u'已成功订阅{0}，从待订阅清单中移除'.format(tick.vtSymbol))
            del self.pendingSubcribeSymbols[tick.vtSymbol]

        # 缓存最新tick
        self.tickDict[tick.vtSymbol] = tick

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
            # 添加datetime字段
            ctaTick.datetime = datetime.strptime(' '.join([tick.date, tick.time]), '%Y%m%d %H:%M:%S.%f')

            # 5.添加datetime字段
            if ctaTick.datetime.hour >= 20:
                dt = datetime.now()
                today = dt.strftime('%Y%m%d')
                ctaTick.datetime = datetime.strptime(' '.join([today, tick.time]), '%Y%m%d %H:%M:%S.%f')
                ctaTick.date = today

            # 逐个推送到策略实例中
            l = self.tickStrategyDict[tick.vtSymbol]
            for strategy in l:
                self.callStrategyFunc(strategy, strategy.onTick, ctaTick)
    
    # ----------------------------------------------------------------------
    def processOrderEvent(self, event):
        """处理委托推送事件"""
        # 1.获取事件的Order数据
        order = event.dict_['data']

        # order.vtOrderID 在gateway中，已经格式化为 gatewayName.vtOrderID

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

        # 过滤已经收到过的成交回报
        if trade.vtTradeID in self.tradeSet:
            return
        self.tradeSet.add(trade.vtTradeID)

        # 将成交推送到策略对象中
        if trade.vtOrderID in self.orderStrategyDict:

            # 3.提取对应的策略
            strategy = self.orderStrategyDict[trade.vtOrderID]
            
            # 计算策略持仓 ( canceled by IncenseLee )
            #if trade.direction == DIRECTION_LONG:
            #    strategy.pos += trade.volume
            #else:
            #    strategy.pos -= trade.volume

            self.callStrategyFunc(strategy, strategy.onTrade, trade)
            
        # 更新持仓缓存数据
        if trade.vtSymbol in self.tickStrategyDict:
            posBuffer = self.posBufferDict.get(trade.vtSymbol, None)
            if not posBuffer:
                posBuffer = PositionBuffer()
                posBuffer.vtSymbol = trade.vtSymbol
                self.posBufferDict[trade.vtSymbol] = posBuffer
            posBuffer.updateTradeData(trade)            
            
    #----------------------------------------------------------------------
    def processPositionEvent(self, event):
        """处理持仓推送"""
        pos = event.dict_['data']
        
        # 更新持仓缓存数据
        if pos.vtSymbol in self.tickStrategyDict:
            posBuffer = self.posBufferDict.get(pos.vtSymbol, None)
            if not posBuffer:
                posBuffer = PositionBuffer()
                posBuffer.vtSymbol = pos.vtSymbol
                self.posBufferDict[pos.vtSymbol] = posBuffer
            posBuffer.updatePositionData(pos)
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""

        # 注册行情数据推送（Tick数据到达）的响应事件
        self.eventEngine.register(EVENT_TICK, self.procecssTickEvent)

        # 注册订单推送的响应事件
        self.eventEngine.register(EVENT_ORDER, self.processOrderEvent)

        # 注册成交推送（交易）的响应时间
        self.eventEngine.register(EVENT_TRADE, self.processTradeEvent)

        # 注册持仓更新事件
        self.eventEngine.register(EVENT_POSITION, self.processPositionEvent)

        # 账号更新事件（借用账号更新事件，来检查是否有未订阅的合约信息）
        self.eventEngine.register(EVENT_ACCOUNT, self.checkUnsubscribedSymbols)

        # 注册定时器事件
        self.eventEngine.register(EVENT_TIMER, self.processTimerEvent)

        # 注册强制止损事件
        self.eventEngine.register(EVENT_ACCOUNT_LOSS, self.processAccoutLossEvent)

    def processAccoutLossEvent(self,event):
        """处理止损时间"""
        balance = event.dict_['data']
        self.writeCtaLog(u'净值{0}低于止损线，执行强制止损'.format(balance))
        self.mainEngine.writeLog(u'净值{0}低于止损线，执行强制止损'.format(balance))

        self.cancelOrders(symbol=EMPTY_STRING)

        for posBuffer in self.posBufferDict.values():

            if posBuffer.shortYd > 0:
                self.writeCtaLog(u'{0}合约持有昨空单{1}手，强平'.format(posBuffer.vtSymbol,posBuffer.shortYd))
                tick = self.tickDict.get(posBuffer.vtSymbol, None)

                if not tick:
                    self.writeCtaLog(u'找不对{0}的最新Tick数据'.format(posBuffer.vtSymbol))
                    continue

                self.sendOrder(posBuffer.vtSymbol, orderType=CTAORDER_COVER, price=tick.upperLimit, volume=posBuffer.shortYd,strategy=None)

            if posBuffer.shortToday > 0:
                self.writeCtaLog(u'{0}合约持有今空单{1}手，强平'.format(posBuffer.vtSymbol,posBuffer.shortToday))
                tick = self.tickDict.get(posBuffer.vtSymbol, None)

                if not tick:
                    self.writeCtaLog(u'找不对{0}的最新Tick数据'.format(posBuffer.vtSymbol))
                    continue

                self.sendOrder(posBuffer.vtSymbol, orderType=CTAORDER_COVER, price=tick.upperLimit, volume=posBuffer.shortToday,strategy=None)

            if posBuffer.longYd > 0:
                self.writeCtaLog(u'{0}合约持有昨多单{1}手，强平'.format(posBuffer.vtSymbol,posBuffer.longYd))
                tick = self.tickDict.get(posBuffer.vtSymbol, None)

                if not tick:
                    self.writeCtaLog(u'找不对{0}的最新Tick数据'.format(posBuffer.vtSymbol))
                    continue

                self.sendOrder(posBuffer.vtSymbol, orderType=CTAORDER_SELL, price=tick.lowerLimit, volume=posBuffer.longYd,strategy=None)

            if posBuffer.longToday > 0:
                self.writeCtaLog(u'{0}合约持有今多单{1}手，强平'.format(posBuffer.vtSymbol,posBuffer.longToday))
                tick = self.tickDict.get(posBuffer.vtSymbol, None)

                if not tick:
                    self.writeCtaLog(u'找不对{0}的最新Tick数据'.format(posBuffer.vtSymbol))
                    continue

                self.sendOrder(posBuffer.vtSymbol, orderType=CTAORDER_SELL, price=tick.lowerLimit, volume=posBuffer.longToday,strategy=None)


    def processTimerEvent(self, event):
        """定时器事件"""

        # 触发每个策略的定时接口
        for strategy in self.strategyDict.values():
            strategy.onTimer()
 
    # ----------------------------------------------------------------------
    def insertData(self, dbName, collectionName, data):
        """插入数据到数据库（这里的data可以是CtaTickData或者CtaBarData）"""
        self.mainEngine.dbInsert(dbName, collectionName, data.__dict__)
    
    # ----------------------------------------------------------------------
    def loadBar(self, dbName, collectionName, days):
        """从数据库中读取Bar数据，startDate是datetime对象"""
        startDate = self.today - timedelta(days)
        
        d = {'datetime':{'$gte':startDate}}
        barData = self.mainEngine.dbQuery(dbName, collectionName, d)
        
        l = []
        for d in barData:
                bar = CtaBarData()
                bar.__dict__ = d
                l.append(bar)
            
        return l
    
    # ----------------------------------------------------------------------
    def loadTick(self, dbName, collectionName, days):
        """从数据库中读取Tick数据，startDate是datetime对象"""
        startDate = self.today - timedelta(days)
        
        d = {'datetime':{'$gte':startDate}}
        tickData = self.mainEngine.dbQuery(dbName, collectionName, d)
        
        l = []
        for d in tickData:
                tick = CtaTickData()
                tick.__dict__ = d
                l.append(tick)
        
        return l    

    # ----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """快速发出CTA模块日志事件"""
        log = VtLogData()
        log.logContent = content
        event = Event(type_=EVENT_CTA_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)

        # 写入本地log日志
        logging.info(content)
    
    # ----------------------------------------------------------------------
    def loadStrategy(self, setting):
        """载入策略"""
        try:
            name = setting['name']
            className = setting['className']
        except Exception as e:
            self.writeCtaLog(u'载入策略出错：%s' %e)
            return
        
        # 获取策略类
        strategyClass = STRATEGY_CLASS.get(className, None)
        if not strategyClass:
            self.writeCtaLog(u'找不到策略类：%s' %className)
            return
        
        # 防止策略重名
        if name in self.strategyDict:
            self.writeCtaLog(u'策略实例重名：%s' %name)
        else:
            # 1.创建策略对象
            strategy = strategyClass(self, setting)  
            self.strategyDict[name] = strategy
            
            # 2.保存Tick映射关系（symbol <==> Strategy[] )
            # modifid by Incenselee 支持多个Symbol的订阅
            symbols = strategy.vtSymbol.split(';')

            # 判断是否有Leg1Symbol,Leg2Symbol 两个合约属性
            if hasattr(strategy, 'Leg1Symbol'):
                if strategy.Leg1Symbol not in symbols:
                    symbols.append(strategy.Leg1Symbol)
            if hasattr(strategy, 'Leg2Symbol'):
                if strategy.Leg2Symbol not in symbols:
                    symbols.append(strategy.Leg2Symbol)

            for symbol in symbols:
                self.writeCtaLog(u'添加合约{0}与策略的匹配目录'.format(symbol))
                if symbol in self.tickStrategyDict:
                    l = self.tickStrategyDict[symbol]
                else:
                    l = []
                    self.tickStrategyDict[symbol] = l
                l.append(strategy)
            
                # 3.订阅合约
                self.writeCtaLog(u'向gateway订阅合约{0}'.format(symbol))
                self.subscribe(strategy=strategy, symbol=symbol)

    def subscribe(self, strategy, symbol):
        """订阅合约，不成功时，加入到待订阅列表"""
        contract = self.mainEngine.getContract(symbol)

        if contract:
            # 4.构造订阅请求包
            req = VtSubscribeReq()
            req.symbol = contract.symbol
            req.exchange = contract.exchange

            # 对于IB接口订阅行情时所需的货币和产品类型，从策略属性中获取
            req.currency = strategy.currency
            req.productClass = strategy.productClass

            # 5.调用主引擎的订阅接口
            self.mainEngine.subscribe(req, contract.gatewayName)
        else:
            print u'Warning, can not find {0} in contracts'.format(symbol)
            self.writeCtaLog(u'交易合约{}无法找到，添加到待订阅列表'.format (symbol))
            self.pendingSubcribeSymbols[symbol]=strategy

    def checkUnsubscribedSymbols(self, event):
        """持仓更新信息时，检查未提交的合约"""
        for symbol in self.pendingSubcribeSymbols.keys():
            contract = self.mainEngine.getContract(symbol)
            if contract:
                # 获取合约的缩写号
                s = self.getShortSymbol(symbol)
                #if s == symbol:    # 合约缩写提取失败
                #    continue
                dt = datetime.now()
                # 若为中金所的合约，白天才提交订阅请求
                if s in MARKET_ZJ and not(9 < dt.hour < 16):
                    continue

                self.writeCtaLog(u'重新提交合约{0}订阅请求'.format(symbol))
                strategy = self.pendingSubcribeSymbols[symbol]
                self.subscribe(strategy=strategy, symbol=symbol)

    #----------------------------------------------------------------------
    def initStrategy(self, name, force = False):
        """初始化策略"""
        if name in self.strategyDict:
            strategy = self.strategyDict[name]
            
            if not strategy.inited or force == True:
                self.callStrategyFunc(strategy, strategy.onInit,force)
                #strategy.onInit(force=force)
                #strategy.inited = True
            else:
                self.writeCtaLog(u'请勿重复初始化策略实例：%s' %name)
        else:
            self.writeCtaLog(u'策略实例不存在：%s' %name)        

    # ---------------------------------------------------------------------
    def startStrategy(self, name):
        """启动策略"""

        # 1.判断策略名称是否存在字典中
        if name in self.strategyDict:

            # 2.提取策略
            strategy = self.strategyDict[name]

            # 3.判断策略是否运行
            if strategy.inited and not strategy.trading:
                # 4.设置运行状态
                strategy.trading = True
                # 5.启动策略
                self.callStrategyFunc(strategy, strategy.onStart)
        else:
            self.writeCtaLog(u'策略实例不存在：%s' %name)
    
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
                self.callStrategyFunc(strategy, strategy.onStop)
                
                # 6.对该策略发出的所有限价单进行撤单
                for vtOrderID, s in self.orderStrategyDict.items():
                    if s is strategy:
                        self.cancelOrder(vtOrderID)
                
                # 7.对该策略发出的所有本地停止单撤单
                for stopOrderID, so in self.workingStopOrderDict.items():
                    if so.strategy is strategy:
                        self.cancelStopOrder(stopOrderID)   
        else:
            self.writeCtaLog(u'策略实例不存在：%s' %name)        
    
    # ----------------------------------------------------------------------
    def saveSetting(self):
        """保存策略配置"""
        with open(self.settingFileName, 'w') as f:
            l = []
            # 逐一循环：name，策略实例名称，strategy，策略
            for strategy in self.strategyDict.values():
                # 配置串
                setting = {}
                for param in strategy.paramList:
                    setting[param] = strategy.__getattribute__(param)
                l.append(setting)
            
            jsonL = json.dumps(l, indent=4)
            f.write(jsonL)
    
    # ----------------------------------------------------------------------
    def loadSetting(self):
        """读取策略配置"""
        with open(self.settingFileName) as f:
            l = json.load(f)
            
            for setting in l:
                self.loadStrategy(setting)
    
        self.loadPosition()

    # ----------------------------------------------------------------------
    def getStrategyVar(self, name):
        """获取策略当前的变量字典"""
        if name in self.strategyDict:
            # 获取策略实例
            strategy = self.strategyDict[name]
            varDict = OrderedDict()
            
            for key in strategy.varList:
                if hasattr(strategy,key):
                    varDict[key] = strategy.__getattribute__(key)
            
            return varDict
        else:
            self.writeCtaLog(u'策略实例不存在：' + name)    
            return None
    
    # ----------------------------------------------------------------------
    def getStrategyParam(self, name):
        """获取策略的参数字典"""
        if name in self.strategyDict:
            # 获取策略实例
            strategy = self.strategyDict[name]
            paramDict = OrderedDict()
            
            for key in strategy.paramList:
                if hasattr(strategy, key):
                    paramDict[key] = strategy.__getattribute__(key)
            
            return paramDict
        else:
            self.writeCtaLog(u'策略实例不存在：' + name)    
            return None   
        
    # ----------------------------------------------------------------------
    def putStrategyEvent(self, name):
        """触发策略状态变化事件（通常用于通知GUI更新）"""
        event = Event(EVENT_CTA_STRATEGY+name)
        self.eventEngine.put(event)

    # ----------------------------------------------------------------------
    def callStrategyFunc(self, strategy, func, params=None):
        """调用策略的函数，若触发异常则捕捉"""
        try:
            if params:
                func(params)
            else:
                func()
        except Exception:
            # 停止策略，修改状态为未初始化
            strategy.trading = False
            strategy.inited = False

            # 发出日志
            content = '\n'.join([u'策略%s触发异常已停止' % strategy.name,
                                 traceback.format_exc()])
            self.writeCtaLog(content)

    # ----------------------------------------------------------------------
    def savePosition(self):
        """保存所有策略的持仓情况到数据库"""
        for strategy in self.strategyDict.values():
            flt = {'name': strategy.name,
                   'vtSymbol': strategy.vtSymbol}

            d = {'name': strategy.name,
                 'vtSymbol': strategy.vtSymbol,
                 'pos': strategy.pos}

            self.mainEngine.dbUpdate(POSITION_DB_NAME, strategy.className,
                                     d, flt, True)

            content = '策略%s持仓保存成功' % strategy.name
            self.writeCtaLog(content)

    # ----------------------------------------------------------------------
    def loadPosition(self):
        """从数据库载入策略的持仓情况"""
        try:
            for strategy in self.strategyDict.values():
                flt = {'name': strategy.name,
                       'vtSymbol': strategy.vtSymbol}
                posData = self.mainEngine.dbQuery(POSITION_DB_NAME, strategy.className, flt)

                for d in posData:
                    strategy.pos = d['pos']
        except:
            self.writeCtaLog(u'loadPosition Exception from Mongodb')
    # ----------------------------------------------------------------------
    def roundToPriceTick(self, priceTick, price):
        """取整价格到合约最小价格变动"""
        if not priceTick:
            return price

        newPrice = round(price / priceTick, 0) * priceTick
        return newPrice

    # ----------------------------------------------------------------------
    def getAccountInfo(self):
        """获取账号的实时权益、可用资金、仓位比例
        Added by Incenselee
        暂不支持多接口同时运行哦
        """
        return self.mainEngine.getAccountInfo()

     # ---------------------------------------------------------------------
    def saveStrategyData(self):
        """保存策略的数据"""

        # 1.判断策略名称是否存在字典中
        for key in self.strategyDict.keys():

            # 2.提取策略
            strategy = self.strategyDict[key]

            if strategy is None:
                continue

            # 3.判断策略是否运行
            if strategy.inited and strategy.trading:

                # 5.保存策略数据
                strategy.saveBar()

    def clearData(self):
        """清空运行数据"""
        self.orderStrategyDict = {}
        self.workingStopOrderDict = {}
        self.posBufferDict = {}
        self.stopOrderDict = {}

    def getShortSymbol(self, symbol):
        """取得合约的短号"""
        # 套利合约
        if symbol.find(' ') != -1:
            # 排除SP SPC SPD
            s = symbol.split(' ')
            if len(s) < 2:
                return symbol
            symbol = s[1]

            # 只提取leg1合约
            if symbol.find('&') != -1:
                s = symbol.split('&')
                if len(s) < 2:
                    return symbol
                symbol = s[0]

        p = re.compile(r"([A-Z]+)[0-9]+", re.I)
        shortSymbol = p.match(symbol)

        if shortSymbol is None:
            self.writeCtaLog(u'{0}不能正则分解'.format(symbol))
            return symbol

        return shortSymbol.group(1)


########################################################################
class PositionBuffer(object):
    """持仓缓存信息（本地维护的持仓数据）"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.vtSymbol = EMPTY_STRING
        
        # 多头
        self.longPosition = EMPTY_INT
        self.longToday = EMPTY_INT
        self.longYd = EMPTY_INT
        
        # 空头
        self.shortPosition = EMPTY_INT
        self.shortToday = EMPTY_INT
        self.shortYd = EMPTY_INT
        
    #----------------------------------------------------------------------
    def updatePositionData(self, pos):
        """更新持仓数据"""
        if pos.direction == DIRECTION_LONG:
            self.longPosition = pos.position
            self.longYd = pos.ydPosition
            self.longToday = self.longPosition - self.longYd
        else:
            self.shortPosition = pos.position
            self.shortYd = pos.ydPosition
            self.shortToday = self.shortPosition - self.shortYd
    
    #----------------------------------------------------------------------
    def updateTradeData(self, trade):
        """更新成交数据"""
        if trade.direction == DIRECTION_LONG:
            # 多方开仓，则对应多头的持仓和今仓增加
            if trade.offset == OFFSET_OPEN:
                self.longPosition += trade.volume
                self.longToday += trade.volume
            # 多方平今，对应空头的持仓和今仓减少
            elif trade.offset == OFFSET_CLOSETODAY:
                self.shortPosition -= trade.volume
                self.shortToday -= trade.volume
            # 多方平昨，对应空头的持仓和昨仓减少
            else:
                self.shortPosition -= trade.volume
                self.shortYd -= trade.volume
        else:
            # 空头和多头相同
            if trade.offset == OFFSET_OPEN:
                self.shortPosition += trade.volume
                self.shortToday += trade.volume
            elif trade.offset == OFFSET_CLOSETODAY:
                self.longPosition -= trade.volume
                self.longToday -= trade.volume
            else:
                self.longPosition -= trade.volume
                self.longYd -= trade.volume
