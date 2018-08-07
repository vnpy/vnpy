# encoding: UTF-8

'''
本文件中实现了CTA策略引擎，针对CTA类型的策略，抽象简化了部分底层接口的功能。
'''

from __future__ import division

import json
import os
import traceback
from collections import OrderedDict
from datetime import datetime, timedelta
from copy import copy

from vnpy.event import Event
from vnpy.trader.vtEvent import *
from vnpy.trader.vtConstant import *
from vnpy.trader.vtObject import VtTickData, VtBarData
from vnpy.trader.vtGateway import VtSubscribeReq, VtOrderReq, VtCancelOrderReq, VtLogData
from vnpy.trader.vtFunction import todayDate, getJsonPath
from vnpy.trader.app import AppEngine

from .ctaBase import *
from .strategy import STRATEGY_CLASS


########################################################################
class CtaEngine(AppEngine):
    """CTA策略引擎"""
    settingFileName = 'CTA_setting.json'
    settingfilePath = getJsonPath(settingFileName, __file__)
    
    STATUS_FINISHED = set([STATUS_REJECTED, STATUS_CANCELLED, STATUS_ALLTRADED])

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
        
        # 保存策略名称和委托号列表的字典
        # key为name，value为保存orderID（限价+本地停止）的集合
        self.strategyOrderDict = {}
        
        # 成交号集合，用来过滤已经收到过的成交推送
        self.tradeSet = set()
        
        # 引擎类型为实盘
        self.engineType = ENGINETYPE_TRADING
        
        # 注册日式事件类型
        self.mainEngine.registerLogEvent(EVENT_CTA_LOG)
        
        # 注册事件监听
        self.registerEvent()
 
    #----------------------------------------------------------------------
    def sendOrder(self, vtSymbol, orderType, price, volume, strategy):
        """发单"""
        contract = self.mainEngine.getContract(vtSymbol)
        
        req = VtOrderReq()
        req.symbol = contract.symbol
        req.exchange = contract.exchange
        req.vtSymbol = contract.vtSymbol
        req.price = self.roundToPriceTick(contract.priceTick, price)
        req.volume = volume
        
        req.productClass = strategy.productClass
        req.currency = strategy.currency        
        
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
            
        # 委托转换
        reqList = self.mainEngine.convertOrderReq(req)
        vtOrderIDList = []
        
        if not reqList:
            return vtOrderIDList
        
        for convertedReq in reqList:
            vtOrderID = self.mainEngine.sendOrder(convertedReq, contract.gatewayName)    # 发单
            self.orderStrategyDict[vtOrderID] = strategy                                 # 保存vtOrderID和策略的映射关系
            self.strategyOrderDict[strategy.name].add(vtOrderID)                         # 添加到策略委托号集合中
            vtOrderIDList.append(vtOrderID)
            
        self.writeCtaLog(u'策略%s发送委托，%s，%s，%s@%s' 
                         %(strategy.name, vtSymbol, req.direction, volume, price))
        
        return vtOrderIDList
    
    #----------------------------------------------------------------------
    def cancelOrder(self, vtOrderID):
        """撤单"""
        # 查询报单对象
        order = self.mainEngine.getOrder(vtOrderID)
        
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
        
        # 保存stopOrderID到策略委托号集合中
        self.strategyOrderDict[strategy.name].add(stopOrderID)
        
        # 推送停止单状态
        strategy.onStopOrder(so)
        
        return [stopOrderID]
    
    #----------------------------------------------------------------------
    def cancelStopOrder(self, stopOrderID):
        """撤销停止单"""
        # 检查停止单是否存在
        if stopOrderID in self.workingStopOrderDict:
            so = self.workingStopOrderDict[stopOrderID]
            strategy = so.strategy
            
            # 更改停止单状态为已撤销
            so.status = STOPORDER_CANCELLED
            
            # 从活动停止单字典中移除
            del self.workingStopOrderDict[stopOrderID]
            
            # 从策略委托号集合中移除
            s = self.strategyOrderDict[strategy.name]
            if stopOrderID in s:
                s.remove(stopOrderID)
            
            # 通知策略
            strategy.onStopOrder(so)

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
                    shortTriggered = so.direction==DIRECTION_SHORT and tick.lastPrice<=so.price     # 空头停止单被触发
                    
                    if longTriggered or shortTriggered:
                        # 买入和卖出分别以涨停跌停价发单（模拟市价单）
                        if so.direction==DIRECTION_LONG:
                            price = tick.upperLimit
                        else:
                            price = tick.lowerLimit
                        
                        # 发出市价委托
                        vtOrderID = self.sendOrder(so.vtSymbol, so.orderType, 
                                                   price, so.volume, so.strategy)
                        
                        # 检查因为风控流控等原因导致的委托失败（无委托号）
                        if vtOrderID:
                            # 从活动停止单字典中移除该停止单
                            del self.workingStopOrderDict[so.stopOrderID]
                            
                            # 从策略委托号集合中移除
                            s = self.strategyOrderDict[so.strategy.name]
                            if so.stopOrderID in s:
                                s.remove(so.stopOrderID)
                            
                            # 更新停止单状态，并通知策略
                            so.status = STOPORDER_TRIGGERED
                            so.strategy.onStopOrder(so)

    #----------------------------------------------------------------------
    def processTickEvent(self, event):
        """处理行情推送"""
        tick = event.dict_['data']
        
        tick = copy(tick)
        
        # 收到tick行情后，先处理本地停止单（检查是否要立即发出）
        self.processStopOrder(tick)
        
        # 推送tick到对应的策略实例进行处理
        if tick.vtSymbol in self.tickStrategyDict:
            # tick时间可能出现异常数据，使用try...except实现捕捉和过滤
            try:
                # 添加datetime字段
                if not tick.datetime:
                    tick.datetime = datetime.strptime(' '.join([tick.date, tick.time]), '%Y%m%d %H:%M:%S.%f')
            except ValueError:
                self.writeCtaLog(traceback.format_exc())
                return
                
            # 逐个推送到策略实例中
            l = self.tickStrategyDict[tick.vtSymbol]
            for strategy in l:
                self.callStrategyFunc(strategy, strategy.onTick, tick)
    
    #----------------------------------------------------------------------
    def processOrderEvent(self, event):
        """处理委托推送"""
        order = event.dict_['data']
        
        vtOrderID = order.vtOrderID
        
        if vtOrderID in self.orderStrategyDict:
            strategy = self.orderStrategyDict[vtOrderID]            
            
            # 如果委托已经完成（拒单、撤销、全成），则从活动委托集合中移除
            if order.status in self.STATUS_FINISHED:
                s = self.strategyOrderDict[strategy.name]
                if vtOrderID in s:
                    s.remove(vtOrderID)
            
            self.callStrategyFunc(strategy, strategy.onOrder, order)
    
    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """处理成交推送"""
        trade = event.dict_['data']
        
        # 过滤已经收到过的成交回报
        if trade.vtTradeID in self.tradeSet:
            return
        self.tradeSet.add(trade.vtTradeID)
        
        # 将成交推送到策略对象中
        if trade.vtOrderID in self.orderStrategyDict:
            strategy = self.orderStrategyDict[trade.vtOrderID]
            
            # 计算策略持仓
            if trade.direction == DIRECTION_LONG:
                strategy.pos += trade.volume
            else:
                strategy.pos -= trade.volume
            
            self.callStrategyFunc(strategy, strategy.onTrade, trade)
            
            # 保存策略持仓到数据库
            self.saveSyncData(strategy)              
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_TICK, self.processTickEvent)
        self.eventEngine.register(EVENT_ORDER, self.processOrderEvent)
        self.eventEngine.register(EVENT_TRADE, self.processTradeEvent)
 
    #----------------------------------------------------------------------
    def insertData(self, dbName, collectionName, data):
        """插入数据到数据库（这里的data可以是VtTickData或者VtBarData）"""
        self.mainEngine.dbInsert(dbName, collectionName, data.__dict__)
    
    #----------------------------------------------------------------------
    def loadBar(self, dbName, collectionName, days):
        """从数据库中读取Bar数据，startDate是datetime对象"""
        startDate = self.today - timedelta(days)
        
        d = {'datetime':{'$gte':startDate}}
        barData = self.mainEngine.dbQuery(dbName, collectionName, d, 'datetime')
        
        l = []
        for d in barData:
            bar = VtBarData()
            bar.__dict__ = d
            l.append(bar)
        return l
    
    #----------------------------------------------------------------------
    def loadTick(self, dbName, collectionName, days):
        """从数据库中读取Tick数据，startDate是datetime对象"""
        startDate = self.today - timedelta(days)
        
        d = {'datetime':{'$gte':startDate}}
        tickData = self.mainEngine.dbQuery(dbName, collectionName, d, 'datetime')
        
        l = []
        for d in tickData:
            tick = VtTickData()
            tick.__dict__ = d
            l.append(tick)
        return l    
    
    #----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """快速发出CTA模块日志事件"""
        log = VtLogData()
        log.logContent = content
        log.gatewayName = 'CTA_STRATEGY'
        event = Event(type_=EVENT_CTA_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)   
    
    #----------------------------------------------------------------------
    def loadStrategy(self, setting):
        """载入策略"""
        try:
            name = setting['name']
            className = setting['className']
        except Exception:
            msg = traceback.format_exc()
            self.writeCtaLog(u'载入策略出错：%s' %msg)
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
            # 创建策略实例
            strategy = strategyClass(self, setting)  
            self.strategyDict[name] = strategy
            
            # 创建委托号列表
            self.strategyOrderDict[name] = set()
            
            # 保存Tick映射关系
            if strategy.vtSymbol in self.tickStrategyDict:
                l = self.tickStrategyDict[strategy.vtSymbol]
            else:
                l = []
                self.tickStrategyDict[strategy.vtSymbol] = l
            l.append(strategy)
            
    #----------------------------------------------------------------------
    def subscribeMarketData(self, strategy):
        """订阅行情"""
        # 订阅合约
        contract = self.mainEngine.getContract(strategy.vtSymbol)
        if contract:
            req = VtSubscribeReq()
            req.symbol = contract.symbol
            req.exchange = contract.exchange
            
            # 对于IB接口订阅行情时所需的货币和产品类型，从策略属性中获取
            req.currency = strategy.currency
            req.productClass = strategy.productClass
            
            self.mainEngine.subscribe(req, contract.gatewayName)
        else:
            self.writeCtaLog(u'%s的交易合约%s无法找到' %(strategy.name, strategy.vtSymbol))

    #----------------------------------------------------------------------
    def initStrategy(self, name):
        """初始化策略"""
        if name in self.strategyDict:
            strategy = self.strategyDict[name]
            
            if not strategy.inited:
                self.callStrategyFunc(strategy, strategy.onInit)
                strategy.inited = True
                
                self.loadSyncData(strategy)                             # 初始化完成后加载同步数据
                self.subscribeMarketData(strategy)                      # 加载同步数据后再订阅行情
            else:
                self.writeCtaLog(u'请勿重复初始化策略实例：%s' %name)
        else:
            self.writeCtaLog(u'策略实例不存在：%s' %name)        

    #---------------------------------------------------------------------
    def startStrategy(self, name):
        """启动策略"""
        if name in self.strategyDict:
            strategy = self.strategyDict[name]
            
            if strategy.inited and not strategy.trading:
                strategy.trading = True
                self.callStrategyFunc(strategy, strategy.onStart)
        else:
            self.writeCtaLog(u'策略实例不存在：%s' %name)
    
    #----------------------------------------------------------------------
    def stopStrategy(self, name):
        """停止策略"""
        if name in self.strategyDict:
            strategy = self.strategyDict[name]
            
            if strategy.trading:
                strategy.trading = False
                self.callStrategyFunc(strategy, strategy.onStop)
                
                # 对该策略发出的所有限价单进行撤单
                for vtOrderID, s in self.orderStrategyDict.items():
                    if s is strategy:
                        self.cancelOrder(vtOrderID)
                
                # 对该策略发出的所有本地停止单撤单
                for stopOrderID, so in self.workingStopOrderDict.items():
                    if so.strategy is strategy:
                        self.cancelStopOrder(stopOrderID)   
        else:
            self.writeCtaLog(u'策略实例不存在：%s' %name)    
            
    #----------------------------------------------------------------------
    def initAll(self):
        """全部初始化"""
        for name in self.strategyDict.keys():
            self.initStrategy(name)    
            
    #----------------------------------------------------------------------
    def startAll(self):
        """全部启动"""
        for name in self.strategyDict.keys():
            self.startStrategy(name)
            
    #----------------------------------------------------------------------
    def stopAll(self):
        """全部停止"""
        for name in self.strategyDict.keys():
            self.stopStrategy(name)    
    
    #----------------------------------------------------------------------
    def saveSetting(self):
        """保存策略配置"""
        with open(self.settingfilePath, 'w') as f:
            l = []
            
            for strategy in self.strategyDict.values():
                setting = {}
                for param in strategy.paramList:
                    setting[param] = strategy.__getattribute__(param)
                l.append(setting)
            
            jsonL = json.dumps(l, indent=4)
            f.write(jsonL)
    
    #----------------------------------------------------------------------
    def loadSetting(self):
        """读取策略配置"""
        with open(self.settingfilePath) as f:
            l = json.load(f)
            
            for setting in l:
                self.loadStrategy(setting)
    
    #----------------------------------------------------------------------
    def getStrategyVar(self, name):
        """获取策略当前的变量字典"""
        if name in self.strategyDict:
            strategy = self.strategyDict[name]
            varDict = OrderedDict()
            
            for key in strategy.varList:
                varDict[key] = strategy.__getattribute__(key)
            
            return varDict
        else:
            self.writeCtaLog(u'策略实例不存在：' + name)    
            return None
    
    #----------------------------------------------------------------------
    def getStrategyParam(self, name):
        """获取策略的参数字典"""
        if name in self.strategyDict:
            strategy = self.strategyDict[name]
            paramDict = OrderedDict()
            
            for key in strategy.paramList:  
                paramDict[key] = strategy.__getattribute__(key)
            
            return paramDict
        else:
            self.writeCtaLog(u'策略实例不存在：' + name)    
            return None
    
    #----------------------------------------------------------------------
    def getStrategyNames(self):
        """查询所有策略名称"""
        return self.strategyDict.keys()        
        
    #----------------------------------------------------------------------
    def putStrategyEvent(self, name):
        """触发策略状态变化事件（通常用于通知GUI更新）"""
        strategy = self.strategyDict[name]
        d = {k:strategy.__getattribute__(k) for k in strategy.varList}
        
        event = Event(EVENT_CTA_STRATEGY+name)
        event.dict_['data'] = d
        self.eventEngine.put(event)
        
        d2 = {k:str(v) for k,v in d.items()}
        d2['name'] = name
        event2 = Event(EVENT_CTA_STRATEGY)
        event2.dict_['data'] = d2
        self.eventEngine.put(event2)        
        
    #----------------------------------------------------------------------
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
            content = '\n'.join([u'策略%s触发异常已停止' %strategy.name,
                                traceback.format_exc()])
            self.writeCtaLog(content)
            
    #----------------------------------------------------------------------
    def saveSyncData(self, strategy):
        """保存策略的持仓情况到数据库"""
        flt = {'name': strategy.name,
               'vtSymbol': strategy.vtSymbol}
        
        d = copy(flt)
        for key in strategy.syncList:
            d[key] = strategy.__getattribute__(key)
        
        self.mainEngine.dbUpdate(POSITION_DB_NAME, strategy.className,
                                 d, flt, True)
        
        content = u'策略%s同步数据保存成功，当前持仓%s' %(strategy.name, strategy.pos)
        self.writeCtaLog(content)
    
    #----------------------------------------------------------------------
    def loadSyncData(self, strategy):
        """从数据库载入策略的持仓情况"""
        flt = {'name': strategy.name,
               'vtSymbol': strategy.vtSymbol}
        syncData = self.mainEngine.dbQuery(POSITION_DB_NAME, strategy.className, flt)
        
        if not syncData:
            return
        
        d = syncData[0]
        
        for key in strategy.syncList:
            if key in d:
                strategy.__setattr__(key, d[key])
                
    #----------------------------------------------------------------------
    def roundToPriceTick(self, priceTick, price):
        """取整价格到合约最小价格变动"""
        if not priceTick:
            return price
        
        newPrice = round(price/priceTick, 0) * priceTick
        return newPrice    
    
    #----------------------------------------------------------------------
    def stop(self):
        """停止"""
        pass
    
    #----------------------------------------------------------------------
    def cancelAll(self, name):
        """全部撤单"""
        s = self.strategyOrderDict[name]
        
        # 遍历列表，全部撤单
        # 这里不能直接遍历集合s，因为撤单时会修改s中的内容，导致出错
        for orderID in list(s):
            if STOPORDERPREFIX in orderID:
                self.cancelStopOrder(orderID)
            else:
                self.cancelOrder(orderID)

    #----------------------------------------------------------------------
    def getPriceTick(self, strategy):
        """获取最小价格变动"""
        contract = self.mainEngine.getContract(strategy.vtSymbol)
        if contract:
            return contract.priceTick
        return 0
        
        