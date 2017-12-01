# encoding: UTF-8

from __future__ import division
import json
import shelve
import os
import traceback
from collections import OrderedDict

from vnpy.event import Event
from vnpy.trader.vtEvent import EVENT_TICK, EVENT_TRADE, EVENT_CONTRACT
from vnpy.trader.vtFunction import getTempPath, getJsonPath
from vnpy.trader.vtObject import VtLogData, VtSubscribeReq
from vnpy.trader.vtConstant import PRODUCT_OPTION, OPTION_CALL, OPTION_PUT
from vnpy.pricing import black

from .omBase import (OmOption, OmUnderlying, OmChain, OmPortfolio,
                     EVENT_OM_LOG)



# 定价模型字典
MODEL_DICT = {}
MODEL_DICT['black'] = black



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
        self.optionContractDict = {}      # symbol:contract
        
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
        if contract.symbol and contract.productClass == PRODUCT_OPTION:
            self.optionContractDict[contract.symbol] = contract
    
    #----------------------------------------------------------------------
    def subscribeEvent(self, symbol):
        """订阅对应合约的事件"""
        contract = self.mainEngine.getContract(symbol)
        if not contract:
            self.writeLog(u'行情订阅失败，找不到合约：%s' %symbol)
            return
            
        vtSymbol = contract.vtSymbol
        
        # 订阅行情
        req = VtSubscribeReq()
        req.symbol = contract.symbol
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
        
        # 读取定价模型
        model = MODEL_DICT.get(setting['model'], None)
        if not model:
            self.writeLog(u'找不到定价模型%s' %setting['model'])
            return
            
        # 创建标的对象
        underlyingDict = OrderedDict()
        
        for underlyingSymbol in setting['underlying']:
            contract = self.mainEngine.getContract(underlyingSymbol)
            if not contract:
                self.writeLog(u'找不到标的物合约%s' %underlyingSymbol)
                continue
            
            detail = self.mainEngine.getPositionDetail(contract.vtSymbol)
            
            underlying = OmUnderlying(contract, detail)
            underlyingDict[underlyingSymbol] = underlying
        
        # 创建期权链对象并初始化
        chainList = []
        
        for d in setting['chain']:
            chainSymbol = d['chainSymbol']
            r = d['r']
            
            # 锁定标的对象
            underlying = underlyingDict.get(d['underlyingSymbol'], None)
            if not underlying:
                self.writeLog(u'%s期权链的标的合约%s尚未创建，请检查配置文件' %(chainSymbol, underlyingSymbol))
                continue
            
            # 创建期权对象并初始化
            callDict = {}
            putDict = {}
            
            for symbol, contract in self.optionContractDict.items():
                if contract.underlyingSymbol == d['chainSymbol']:
                    detail = self.mainEngine.getPositionDetail(contract.vtSymbol)
                    option = OmOption(contract, detail, underlying, model, r)
                    
                    if contract.optionType is OPTION_CALL:
                        callDict[option.k] = option
                    else:
                        putDict[option.k] = option
                        
            # 期权排序
            strikeList = callDict.keys()
            strikeList.sort()
            callList = [callDict[k] for k in strikeList]
            putList = [putDict[k] for k in strikeList]
            
            # 创建期权链
            chain = OmChain(chainSymbol, callList, putList)
            chainList.append(chain)
            
            # 添加标的映射关系
            underlying.addChain(chain)

        # 创建持仓组合对象并初始化
        self.portfolio = OmPortfolio(setting['name'], model, underlyingDict.values(), chainList)
        
        # 载入波动率配置
        self.loadImpvSetting()
        
        # 订阅行情和事件
        for underlying in underlyingDict.values():
            self.subscribeEvent(underlying.vtSymbol)
            
        for chain in chainList:
            for option in chain.optionDict.values():
                self.subscribeEvent(option.vtSymbol)
        
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
    def stop(self):
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
