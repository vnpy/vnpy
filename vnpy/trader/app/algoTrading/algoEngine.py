# encoding: UTF-8

'''
算法交易引擎
'''

from __future__ import division
import os
import importlib

from vnpy.event import Event
from vnpy.rpc import RpcServer
from vnpy.trader.vtEvent import EVENT_TIMER, EVENT_TICK, EVENT_ORDER, EVENT_TRADE
from vnpy.trader.vtConstant import (DIRECTION_LONG, DIRECTION_SHORT, 
                                    PRICETYPE_LIMITPRICE, PRICETYPE_MARKETPRICE,
                                    OFFSET_OPEN, OFFSET_CLOSE,
                                    OFFSET_CLOSETODAY, OFFSET_CLOSEYESTERDAY)
from vnpy.trader.vtObject import VtSubscribeReq, VtOrderReq, VtCancelOrderReq, VtLogData

from .algo import ALGO_DICT


EVENT_ALGO_LOG = 'eAlgoLog'         # 算法日志事件
EVENT_ALGO_PARAM = 'eAlgoParam'     # 算法参数事件
EVENT_ALGO_VAR = 'eAlgoVar'         # 算法变量事件
EVENT_ALGO_SETTING = 'eAlgoSetting' # 算法配置事件

ALGOTRADING_DB_NAME = 'VnTrader_AlgoTrading_Db'     # AlgoTrading数据库名

SETTING_COLLECTION_NAME = 'AlgoSetting'             # 算法配置集合名
HISTORY_COLLECTION_NAME = 'AlgoHistory'             # 算法历史集合名


########################################################################
class AlgoEngine(object):
    """算法交易引擎"""
    
    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        self.rpcServer = None
        
        self.algoDict = {}          # algoName:algo
        self.orderAlgoDict = {}     # vtOrderID:algo
        self.symbolAlgoDict = {}    # vtSymbol:algo set
        self.settingDict = {}       # settingName:setting
        self.historyDict = {}       # algoName:dict
        
        self.registerEvent()

    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_TICK, self.processTickEvent)
        self.eventEngine.register(EVENT_TIMER, self.processTimerEvent)
        self.eventEngine.register(EVENT_ORDER, self.processOrderEvent)
        self.eventEngine.register(EVENT_TRADE, self.processTradeEvent)
    
    #----------------------------------------------------------------------
    def stop(self):
        """停止"""
        if self.rpcServer:
            self.rpcServer.stop()
    
    #----------------------------------------------------------------------
    def processTickEvent(self, event):
        """行情事件"""
        tick = event.dict_['data']
        
        l = self.symbolAlgoDict.get(tick.vtSymbol, None)
        if l:    
            for algo in l:
                algo.updateTick(tick)
        
    #----------------------------------------------------------------------
    def processOrderEvent(self, event):
        """委托事件"""
        order = event.dict_['data']
        
        algo = self.orderAlgoDict.get(order.vtOrderID, None)
        if algo:
            algo.updateOrder(order)

    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """成交事件"""
        trade = event.dict_['data']
        
        algo = self.orderAlgoDict.get(trade.vtOrderID, None)
        if algo:
            algo.updateTrade(trade)
    
    #----------------------------------------------------------------------
    def processTimerEvent(self, event):
        """定时事件"""
        for algo in self.algoDict.values():
            algo.updateTimer()
    
    #----------------------------------------------------------------------
    def addAlgo(self, algoSetting):
        """新增算法"""
        templateName = algoSetting['templateName']
        algoClass = ALGO_DICT[templateName]
        algo = algoClass.new(self, algoSetting)
        
        self.algoDict[algo.algoName] = algo
        
        return algo.algoName
    
    #----------------------------------------------------------------------
    def stopAlgo(self, algoName):
        """停止算法"""
        if algoName in self.algoDict:
            self.algoDict[algoName].stop()
            del self.algoDict[algoName]
    
    #----------------------------------------------------------------------
    def stopAll(self):
        """全部停止"""
        l = self.algoDict.keys()
        for algoName in l:
            self.stopAlgo(algoName)
    
    #----------------------------------------------------------------------
    def subscribe(self, algo, vtSymbol):
        """"""
        contract = self.mainEngine.getContract(vtSymbol)
        if not contract:
            self.writeLog(u'%s订阅行情失败，找不到合约%s' %(algo.algoName, vtSymbol))
            return        

        # 如果vtSymbol已存在于字典，说明已经订阅过
        if vtSymbol in self.symbolAlgoDict:
            s = self.symbolAlgoDict[vtSymbol]
            s.add(algo)
            return
        # 否则需要添加到字典中并执行订阅
        else:
            s = set()
            self.symbolAlgoDict[vtSymbol] = s
            s.add(algo)
            
            req = VtSubscribeReq()
            req.symbol = contract.symbol
            req.exchange = contract.exchange
            self.mainEngine.subscribe(req, contract.gatewayName)

    #----------------------------------------------------------------------
    def sendOrder(self, algo, vtSymbol, direction, price, volume, 
                  priceType=None, offset=None):
        """发单"""
        contract = self.mainEngine.getContract(vtSymbol)
        if not contract:
            self.writeLog(u'%s委托下单失败，找不到合约：%s' %(algo.algoName, vtSymbol))

        req = VtOrderReq()
        req.vtSymbol = vtSymbol
        req.symbol = contract.symbol
        req.exchange = contract.exchange
        req.direction = direction        
        req.offset = OFFSET_CLOSETODAY
        req.price = price
        req.volume = volume
        
        if priceType:
            req.priceType = priceType
        else:
            req.priceType = PRICETYPE_LIMITPRICE
        
        if offset:
            req.offset = offset
        else:
            req.offset = OFFSET_OPEN
        
        vtOrderID = self.mainEngine.sendOrder(req, contract.gatewayName)
        self.orderAlgoDict[vtOrderID] = algo
        
        return vtOrderID

    #----------------------------------------------------------------------
    def buy(self, algo, vtSymbol, price, volume, priceType=None, offset=None):
        """买入"""
        return self.sendOrder(algo, vtSymbol, DIRECTION_LONG, price, volume, priceType, offset)

    #----------------------------------------------------------------------
    def sell(self, algo, vtSymbol, price, volume, priceType=None, offset=None):
        """卖出"""
        return self.sendOrder(algo, vtSymbol, DIRECTION_SHORT, price, volume, priceType, offset)

    #----------------------------------------------------------------------
    def cancelOrder(self, algo, vtOrderID):
        """撤单"""
        order = self.mainEngine.getOrder(vtOrderID)
        if not order:
            self.writeLog(u'%s委托撤单失败，找不到委托：%s' %(algo.algoName, vtOrderID))
            return

        req = VtCancelOrderReq()
        req.symbol = order.symbol
        req.exchange = order.exchange
        req.orderID = order.orderID
        req.frontID = order.frontID
        req.sessionID = order.sessionID
        self.mainEngine.cancelOrder(req, order.gatewayName)
        
    #----------------------------------------------------------------------
    def writeLog(self, content, algo=None):
        """输出日志"""
        log = VtLogData()
        log.logContent = content
        
        if algo:
            log.gatewayName = algo.algoName

        event = Event(EVENT_ALGO_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def putVarEvent(self, algo, d):
        """更新变量"""
        algoName = algo.algoName
        
        d['algoName'] = algoName
        event = Event(EVENT_ALGO_VAR)
        event.dict_['data'] = d
        self.eventEngine.put(event)
        
        # RPC推送
        if self.rpcServer:
            self.rpcServer.publish('AlgoTrading', event)
        
        # 保存数据到数据库
        history = self.historyDict.setdefault(algoName, {})
        history['algoName'] = algoName
        history['var'] = d
        
        self.mainEngine.dbUpdate(ALGOTRADING_DB_NAME,
                                 HISTORY_COLLECTION_NAME,
                                 history,
                                 {'algoName': algoName},
                                 True)
        
        
    #----------------------------------------------------------------------
    def putParamEvent(self, algo, d):
        """更新参数"""
        algoName = algo.algoName
        
        d['algoName'] = algoName
        event = Event(EVENT_ALGO_PARAM)
        event.dict_['data'] = d
        self.eventEngine.put(event)    
        
        # RPC推送
        if self.rpcServer:
            self.rpcServer.publish('AlgoTrading', event)        
        
        # 保存数据到数据库
        history = self.historyDict.setdefault(algoName, {})
        history['algoName'] = algoName
        history['param'] = d
        
        self.mainEngine.dbUpdate(ALGOTRADING_DB_NAME,
                                 HISTORY_COLLECTION_NAME,
                                 history,
                                 {'algoName': algoName},
                                 True)        
    
    #----------------------------------------------------------------------
    def getTick(self, algo, vtSymbol):
        """查询行情"""
        tick = self.mainEngine.getTick(vtSymbol)
        if not tick:
            self.writeLog(u'%s查询行情失败，找不到报价：%s' %(algo.algoName, vtSymbol))
            return            
            
        return tick
    
    #----------------------------------------------------------------------
    def getContract(self, algo, vtSymbol):
        """查询合约"""
        contract = self.mainEngine.getContract(vtSymbol)
        if not contract:
            self.writeLog(u'%s查询合约失败，找不到报价：%s' %(algo.algoName, vtSymbol))
            return            
        
        return contract
    
    #----------------------------------------------------------------------
    def saveAlgoSetting(self, algoSetting):
        """保存算法配置"""
        settingName = algoSetting['settingName']
        self.settingDict[settingName] = algoSetting
        
        self.mainEngine.dbUpdate(ALGOTRADING_DB_NAME, 
                                 SETTING_COLLECTION_NAME,
                                 algoSetting,
                                 {'settingName': settingName},
                                 True)
        
        self.putSettingEvent(settingName, algoSetting)
    
    #----------------------------------------------------------------------
    def loadAlgoSetting(self):
        """加载算法配置"""
        l = self.mainEngine.dbQuery(ALGOTRADING_DB_NAME,
                                    SETTING_COLLECTION_NAME,
                                    {},
                                    'templateName')
        for algoSetting in l:
            settingName = algoSetting['settingName']
            self.settingDict[settingName] = algoSetting
            self.putSettingEvent(settingName, algoSetting)
    
    #----------------------------------------------------------------------
    def deleteAlgoSetting(self, algoSetting):
        """删除算法配置"""
        settingName = algoSetting['settingName']
        
        del self.settingDict[settingName]
        self.mainEngine.dbDelete(ALGOTRADING_DB_NAME,
                                 SETTING_COLLECTION_NAME,
                                 {'settingName': settingName})
        
        self.putSettingEvent(settingName, {})
        
    #----------------------------------------------------------------------
    def putSettingEvent(self, settingName, algoSetting):
        """发出算法配置更新事件"""
        algoSetting['settingName'] = settingName
        
        event = Event(EVENT_ALGO_SETTING)
        event.dict_['data'] = algoSetting
        self.eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def startRpc(self, repPort, pubPort):
        """启动RPC服务"""
        if self.rpcServer:
            return
        
        self.rpcServer = AlgoRpcServer(self, repPort, pubPort)
        self.rpcServer.start()
        self.writeLog(u'算法交易RPC服务启动成功，REP端口:%s，PUB端口:%s' %(repPort, pubPort))


########################################################################
class AlgoRpcServer(RpcServer):
    """算法交易RPC服务器"""
    
    #----------------------------------------------------------------------
    def __init__(self, engine, repPort, pubPort):
        """Constructor"""
        self.engine = engine
        repAddress = 'tcp://*:%s' %repPort
        pubAddress = 'tcp://*:%s' %pubPort
        
        super(AlgoRpcServer, self).__init__(repAddress, pubAddress)
        
        self.register(self.engine.addAlgo)
        self.register(self.engine.stopAlgo)
        self.register(self.engine.stopAll)
    