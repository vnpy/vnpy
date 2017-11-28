# encoding: UTF-8

from __future__ import division
import json
import shelve
import os
import traceback

from vnpy.event import Event
from vnpy.trader.vtEvent import EVENT_TICK, EVENT_TRADE, EVENT_CONTRACT
from vnpy.trader.vtFunction import getTempPath, getJsonPath
from vnpy.trader.vtObject import VtLogData

from .omBase import (OmOption, OmUnderlying, OmChain, OmPortfolio,
                     EVENT_OM_LOG)


########################################################################
class OmEngine(object):
    """期权主引擎"""
    impvFileName = 'PricingImpv.vt'
    impvFilePath = getTempPath(impvFileName)
    
    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        self.portfolio = None
        self.contractDict = {}      # symbol:contract
        
        self.registerEvent()
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_CONTRACT, self.processContractEvent)
    
    #----------------------------------------------------------------------
    def processTickEvent(self, event):
        """行情事件"""
        tick = event.dict_['data']
        self.portfolio.newTick(tick)
    
    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """成交事件"""
        trade = event.dict_['data']
        self.portfolio.newTrade(trade)
    
    #----------------------------------------------------------------------
    def processContractEvent(self, event):
        """合约事件"""
        contract = event.dict_['data']
        if contract.symbol:
            self.contractDict[contract.symbol] = contract
    
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
        
        # 载入成功返回
        return True
        
    #----------------------------------------------------------------------
    def loadImpvSetting(self):
        """载入波动率配置"""
        f = shelve.open(self.impvFilePath)
        
        for chain in self.portfolio.chainDict.values():
            for option in chain.optionDict.values():
                option.pricingImpv = f.get(option.symbol, 0)
        
        f.close()
    
    #----------------------------------------------------------------------
    def saveImpvSetting(self):
        """保存波动率配置"""
        if not self.portfolio:
            return
        
        f = shelve.open(self.impvFilePath)
        
        for chain in self.portfolio.chainDict.values():
            for option in chain.optionDict.values():
                f[option.symbol] = option.pricingImpv
        
        f.close()
            
    #----------------------------------------------------------------------
    def close(self):
        """关闭函数"""
        self.saveImpvSetting()
        
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志 """
        log = VtLogData()
        log.logContent = content
        
        event = Event(EVENT_OM_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)         
