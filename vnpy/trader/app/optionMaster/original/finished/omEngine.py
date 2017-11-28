# encoding: UTF-8

from __future__ import division
import json
import os
import traceback

from eventType import *
from eventEngine import Event
from omBase import *
from omPricing import calculatePrice, calculateGreeks, calculateImpv
from omHedging import HedgingEngine
from omAlgo import AlgoEngine
from omAnalysis import AnalysisEngine


path = os.path.abspath(os.path.dirname(__file__))


########################################################################
class OmEngine(object):
    """期权主引擎"""
    impvFileName = 'PricingImpv.vt'
    IMPVSETTING_FILENAME = os.path.join(path, IMPVSETTING_FILENAME)

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        self.riskEngine = RiskEngine(self.eventEngine)
        self.hedgingEngine = HedgingEngine(self)
        self.algoEngine = AlgoEngine(self)
        self.analysisEngine = AnalysisEngine(self)
        
        self.portfolio = None
        
        self.contractDict = {}      # symbol:contract
        
        self.registerEvent()
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_CONTRACT, self.processContractEvent)
        self.eventEngine.register(EVENT_TIMER, self.processTimerEvent)
    
    #----------------------------------------------------------------------
    def processTickEvent(self, event):
        """行情事件"""
        if not self.portfolio:
            return
        
        tick = event.dict_['data']
        self.portfolio.newTick(tick)
    
    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """成交事件"""
        if not self.portfolio:
            return
        
        trade = event.dict_['data']
        self.portfolio.newTrade(trade)

    #----------------------------------------------------------------------
    def processPositionEvent(self, event):
        """持仓事件"""
        if not self.portfolio:
            return
        
        pos = event.dict_['data']
        self.portfolio.newPos(pos)
    
    #----------------------------------------------------------------------
    def processTimerEvent(self, event):
        """定时事件"""
        if not self.portfolio:
            return
        
    #----------------------------------------------------------------------
    def processContractEvent(self, event):
        """合约事件"""
        contract = event.dict_['data']
        if contract.symbol:
            self.contractDict[contract.symbol] = contract
    
    #----------------------------------------------------------------------
    def initEngine(self, fileName):
        """初始化引擎"""
        if self.portfolio:
            return False
        
        f = file(fileName)
        setting = json.load(f)
            
        # 创建期货和股票标的对象
        equityDict = OrderedDict([(symbol, OmEquity(symbol)) for symbol in setting['equity']])
        futuresDict = OrderedDict([(symbol, OmFutures(symbol)) for symbol in setting['futures']])
        
        # 创建期权链对象并初始化
        chainDict = OrderedDict()
        
        for d in setting['chain']:
            interestRate = d['interestRate']
            
            # 锁定标的对象，若无则创建
            if d['underlyingType'] == 'futures':
                if d['underlyingSymbol'] not in futuresDict:
                    underlying = OmFutures(d['underlyingSymbol'])
                    futuresDict[underlying.symbol] = underlying
                else:
                    underlying = futuresDict[d['underlyingSymbol']]
            elif d['underlyingType'] == 'equity':
                if d['underlyingSymbol'] not in equityDict:
                    underlying = OmEquity(d['underlyingSymbol'])
                    equityDict[underlying.symbol] = underlying
                else:
                    underlying = equityDict[d['underlyingSymbol']]                    
            
            # 创建期权对象并初始化
            callList = []
            putList = []
            
            for symbol, contract in self.contractDict.items():
                if contract.optionType and contract.underlyingSymbol == d['chainSymbol']:
                    option = OmOption(symbol)
                    option.init(contract, underlying, interestRate)
                    self.subscribeEvent(option.symbol)              # 订阅事件
                    
                    if contract.optionType is OPTION_CALL:
                        callList.append(option)
                    else:
                        putList.append(option)

            chain = OmChain(d['chainSymbol'])
            chain.init(underlying, callList, putList)
            chainDict[chain.symbol] = chain
        
        # 初始化标的对象
        for underlying in (equityDict.values() + futuresDict.values()):
            l = []
            for chain in chainDict.values():
                if chain.underlying is underlying:
                    l.append(chain)
            contract = self.contractDict[underlying.symbol]
            underlying.init(contract, l)
            self.subscribeEvent(underlying.symbol)                  # 订阅事件
        
        # 创建持仓组合对象并初始化
        self.portfolio = OmPortfolio(setting['name'])
        self.portfolio.init(futuresDict, equityDict, chainDict)
        
        # 载入波动率配置
        self.loadImpvSetting()
        
        # 初始子引擎
        self.hedgingEngine.init()
        self.analysisEngine.init()
        
        # 载入成功返回
        return True
        
    #----------------------------------------------------------------------
    def subscribeEvent(self, symbol):
        """订阅对应合约的事件"""
        contract = self.contractDict[symbol]
        vtSymbol = contract.vtSymbol
        
        # 订阅行情
        req = VtSubscribeReq()
        req.symbol = symbol
        req.exchange = contract.exchange
        self.mainEngine.subscribe(req, contract.gatewayName)
        
        # 订阅事件
        self.eventEngine.register(EVENT_TICK + vtSymbol, self.processTickEvent)
        self.eventEngine.register(EVENT_TRADE + vtSymbol, self.processTradeEvent)
        self.eventEngine.register(EVENT_POSITION + vtSymbol, self.processPositionEvent)
    
    #----------------------------------------------------------------------
    def sendOrder(self, req, name):
        """发送委托"""
        result, msg = self.riskEngine.checkRisk(req)
        
        if result:
            vtOrderID = self.mainEngine.sendOrder(req, name)
            return vtOrderID
        else:
            self.writeLog(msg)
            return None
        
    #----------------------------------------------------------------------
    def loadImpvSetting(self):
        """载入波动率配置"""
        try:
            with open(self.IMPVSETTING_FILENAME, 'r') as f:
                d = json.load(f)
                
                for chain in self.portfolio.chainList:
                    for option in chain.optionList:
                        if option.symbol in d:
                            option.pricingImpv = d[option.symbol]
        except:
            msg = traceback.format_exc()
            self.writeLog(msg)
    
    #----------------------------------------------------------------------
    def saveImpvSetting(self):
        """保存波动率配置"""
        if not self.portfolio:
            return
        
        with open(self.IMPVSETTING_FILENAME, 'w') as f:
            d = {}
            for chain in self.portfolio.chainList:
                for option in chain.optionList:
                    d[option.symbol] = option.pricingImpv
                    
            text = json.dumps(d, indent=4)
            f.write(text)
            
    #----------------------------------------------------------------------
    def close(self):
        """"""
        self.saveImpvSetting()
        self.algoEngine.saveSetting()
        self.hedgingEngine.saveSetting()
        
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """"""
        event = Event(EVENT_OM_LOG)
        event.dict_['data'] = content
        self.eventEngine.put(event)         


########################################################################
class RiskEngine(object):
    """事前风控引擎"""
    SETTING_FILENAME = 'risk_setting.json'
    SETTING_FILENAME = os.path.join(path, SETTING_FILENAME)

    #----------------------------------------------------------------------
    def __init__(self, eventEngine):
        """Constructor"""
        self.eventEngine = eventEngine
        
        # 总委托量
        self.orderSet = set()              # 委托号集合
        self.totalOrderCount = 0
        self.totalOrderLimit = 10000
        
        # 委托流量
        self.orderFlowCount = 0
        self.orderFlowLimit = 30
        self.orderFlowClearCount = 0
        self.orderFlowClearTrigger = 1
        
        # 合约撤单量
        self.symbolCancelDict = {}
        self.symbolCancelLimit = 450
        
        # 活动委托量
        self.activeOrderSet = set()
        self.activeOrderCount = 0
        self.activeOrderLimit = 100
        
        self.loadSetting()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_TRADE, self.processTradeEvent)
        self.eventEngine.register(EVENT_ORDER, self.processOrderEvent)
        self.eventEngine.register(EVENT_TIMER, self.processTimerEvent)
    
    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """成交事件"""
        pass
    
    #----------------------------------------------------------------------
    def processOrderEvent(self, event):
        """委托事件"""
        order = event.dict_['data']
        vtOrderID = order.vtOrderID
        
        # 总委托
        if vtOrderID not in self.orderSet:
            self.orderSet.add(vtOrderID)
            self.totalOrderCount += 1
            
        # 撤单
        if order.status is STATUS_CANCELLED:
            symbol = order.symbol
            if symbol not in self.symbolCancelDict:
                self.symbolCancelDict[symbol] = 1
            else:
                self.symbolCancelDict[symbol] += 1
        
        # 活动委托
        if vtOrderID not in self.activeOrderSet:
            if (order.status is not STATUS_CANCELLED and 
                order.status is not STATUS_ALLTRADED):
                self.activeOrderSet.add(vtOrderID)
                self.activeOrderCount += 1
        else:
            if (order.status is STATUS_CANCELLED or 
                order.status is STATUS_ALLTRADED):
                self.activeOrderSet.remove(vtOrderID)   
                self.activeOrderCount -= 1
    
    #----------------------------------------------------------------------
    def processTimerEvent(self, event):
        """定时事件"""
        # 定时清空委托流量统计
        self.orderFlowClearCount += 1
        
        if self.orderFlowClearCount >= self.orderFlowClearTrigger:
            self.orderFlowClearCount = 0
            self.orderFlowCount = 0
    
    #----------------------------------------------------------------------
    def checkRisk(self, req):
        """风控检查"""
        result = True
        msg = ''
        
        if self.totalOrderCount >= self.totalOrderLimit:
            return False, (u'总委托量%s，达到限制%s' %(self.totalOrderCount, self.totalOrderLimit))
        
        if (req.symbol in self.symbolCancelDict and 
            self.symbolCancelDict[req.symbol] >= self.symbolCancelLimit):
            return False, (u'合约%s撤单总量%s，达到限制%s' %(req.symbol, self.symbolCancelDict[req.symbol], self.symbolCancelLimit))
        
        if self.activeOrderCount >= self.activeOrderLimit:
            return False, (u'活动委托量%s，达到限制%s' %(self.activeOrderCount, self.activeOrderLimit))
        
        if self.orderFlowCount >= self.orderFlowLimit:
            return False, (u'委托流量%s，达到限制%s' %(self.orderFlowCount, self.orderFlowLimit))
        self.orderFlowCount += 1
        
        return result, msg
    
    #----------------------------------------------------------------------
    def loadSetting(self):
        """载入配置"""
        f = file(self.SETTING_FILENAME, 'r')
        d = json.load(f)
        
        self.totalOrderLimit = d['totalOrderLimit']
        self.orderFlowLimit = d['orderFlowLimit']
        self.orderFlowClearTrigger = d['orderFlowClearTrigger']
        self.symbolCancelLimit = d['symbolCancelLimit']
        self.activeOrderLimit = d['activeOrderLimit']
        
        f.close()

    #----------------------------------------------------------------------
    def getCancelTimes(self, symbol):
        """查询撤单次数"""
        if symbol in self.symbolCancelDict:
            return self.symbolCancelDict[symbol]
        return 0
    

#----------------------------------------------------------------------
def generateRiskSettingJson():
    """生成风控配置json"""
    d = {}
    d['totalOrderLimit'] = 10
    d['orderFlowLimit'] = 1
    d['orderFlowClearTrigger'] = 10
    d['symbolCancelLimit'] = 2
    d['activeOrderLimit'] = 2
    text = json.dumps(d, indent=4)
    
    with open(RiskEngine.SETTING_FILENAME, 'w') as f:
        f.write(text)
    