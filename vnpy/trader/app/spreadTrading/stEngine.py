# encoding: UTF-8

import json
import traceback
from copy import copy

from vnpy.event import Event
from vnpy.trader.vtFunction import getJsonPath
from vnpy.trader.vtEvent import EVENT_TICK, EVENT_TRADE, EVENT_POSITION
from vnpy.trader.vtObject import VtSubscribeReq, VtLogData
from vnpy.trader.vtConstant import (DIRECTION_LONG, DIRECTION_SHORT, 
                                    OFFSET_OPEN, OFFSET_CLOSE)

from .stBase import (StLeg, StSpread, EVENT_SPREADTRADING_TICK,
                     EVENT_SPREADTRADING_POS, EVENT_SPREADTRADING_LOG)


########################################################################
class StEngine(object):
    """"""
    settingFileName = 'ST_setting.json'
    settingFilePath = getJsonPath(settingFileName, __file__)

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        # 腿、价差相关字典
        self.legDict = {}                   # vtSymbol:StLeg
        self.spreadDict = {}                # name:StSpread
        self.vtSymbolSpreadDict = {}        # vtSymbol:StSpread
        
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def loadSetting(self):
        """加载配置"""
        try:
            with open(self.settingFilePath) as f:
                l = json.load(f)
                
                for setting in l:
                    result, msg = self.createSpread(setting)
                    self.writeLog(msg)
                    
                self.writeLog(u'价差配置加载完成')
        except:
            content = u'价差配置加载出错，原因：' + traceback.format_exc()
            self.writeLog(content)
    
    #----------------------------------------------------------------------
    def saveSetting(self):
        """保存配置"""
        with open(self.settingFilePath) as f:
            pass
        
    #----------------------------------------------------------------------
    def createSpread(self, setting):
        """创建价差"""
        result = False
        msg = ''
        
        # 检查价差重名
        if setting['name'] in self.spreadDict:
            msg = u'%s价差存在重名' %setting['name']
            return result, msg
        
        # 检查腿是否已使用
        l = []
        l.append(setting['activeLeg']['vtSymbol'])
        for d in setting['passiveLegs']:
            l.append(d['vtSymbol'])
            
        for vtSymbol in l:
            if vtSymbol in self.vtSymbolSpreadDict:
                existingSpread = self.vtSymbolSpreadDict[vtSymbol]
                msg = u'%s合约已经存在于%s价差中' %(vtSymbol, existingSpread.name)
                return result, msg
    
        # 创建价差
        spread = StSpread()
        spread.name = setting['name']        
        self.spreadDict[spread.name] = spread
        
        # 创建主动腿
        activeSetting = setting['activeLeg']
        
        activeLeg = StLeg()
        activeLeg.vtSymbol = activeSetting['vtSymbol']
        activeLeg.ratio = activeSetting['ratio']
        activeLeg.multiplier = activeSetting['multiplier']
        activeLeg.payup = activeSetting['payup']
        
        spread.addActiveLeg(activeLeg)
        self.legDict[activeLeg.vtSymbol] = activeLeg
        self.vtSymbolSpreadDict[activeLeg.vtSymbol] = spread
        
        self.subscribeMarketData(activeLeg.vtSymbol)
        
        # 创建被动腿
        passiveSettingList = setting['passiveLegs']
        passiveLegList = []
        
        for d in passiveSettingList:
            passiveLeg = StLeg()
            passiveLeg.vtSymbol = d['vtSymbol']
            passiveLeg.ratio = d['ratio']
            passiveLeg.multiplier = d['multiplier']
            passiveLeg.payup = d['payup']
            
            spread.addPassiveLeg(passiveLeg)
            self.legDict[passiveLeg.vtSymbol] = passiveLeg
            self.vtSymbolSpreadDict[passiveLeg.vtSymbol] = spread
            
            self.subscribeMarketData(passiveLeg.vtSymbol)  

        # 初始化价差
        spread.initSpread()
        
        # 返回结果
        result = True
        msg = u'%s价差创建成功' %spread.name
        return result, msg
    
    #----------------------------------------------------------------------
    def processTickEvent(self, event):
        """处理行情推送"""
        # 检查行情是否需要处理
        tick = event.dict_['data']
        if tick.vtSymbol not in self.legDict:
            return
        
        # 更新腿价格
        leg = self.legDict[tick.vtSymbol]
        leg.bidPrice = tick.bidPrice1
        leg.askPrice = tick.askPrice1
        leg.bidVolume = tick.bidVolume1
        leg.askVolume = tick.askVolume1
        
        # 更新价差价格
        spread = self.vtSymbolSpreadDict[tick.vtSymbol]
        spread.calculatePrice()
        
        # 推送价差行情更新
        newSpread = copy(spread)
        
        event1 = Event(EVENT_SPREADTRADING_TICK+spread.name)
        event1.dict_['data'] = newSpread
        self.eventEngine.put(event1)
        
        event2 = Event(EVENT_SPREADTRADING_TICK)
        event2.dict_['data'] = newSpread
        self.eventEngine.put(event2)        
    
    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """处理成交推送"""
        # 检查成交是否需要处理
        trade = event.dict_['data']
        if trade.vtSymbol not in self.legDict:
            return
        
        # 更新腿持仓
        leg = self.legDict[trade.vtSymbol]
        direction = trade.direction
        offset = trade.offst
        
        if direction == DIRECTION_LONG:
            if offset == OFFSET_OPEN:
                leg.longPos += trade.volume
            else:
                leg.shortPos -= trade.volume
        else:
            if offset == OFFSET_OPEN:
                leg.shortPos += trade.volume
            else:
                leg.longPos -= trade.volume
        leg.netPos = leg.longPos - leg.shortPos
                
        # 更新价差持仓
        spread = self.vtSymbolSpreadDict[trade.vtSymbol]
        spread.calculatePos()
        
        # 推送价差持仓更新
        newSpread = copy(spread)
        
        event1 = Event(EVENT_SPREADTRADING_POS+spread.name)
        event1.dict_['data'] = newSpread
        self.eventEngine.put(event1)
        
        event2 = Event(EVENT_SPREADTRADING_POS)
        event2.dict_['data'] = newSpread
        self.eventEngine.put(event2)
    
    #----------------------------------------------------------------------
    def processPositionEvent(self, event):
        """处理持仓推送"""
        # 检查持仓是否需要处理
        pos = event.dict_['data']
        if pos.vtSymbol not in self.legDict:
            return
        
        # 更新腿持仓
        leg = self.legDict[trade.vtSymbol]
        direction = pos.direction
        
        if direction == DIRECTION_LONG:
            leg.longPos = pos.position
        else:
            leg.shortPos = pos.position
        leg.netPos = leg.longPos - leg.shortPos
        
        # 更新价差持仓
        spread = self.vtSymbolSpreadDict[trade.vtSymbol]
        spread.calculatePos()
        
        # 推送价差持仓更新
        newSpread = copy(spread)
        
        event1 = Event(EVENT_SPREADTRADING_POS+spread.name)
        event1.dict_['data'] = newSpread
        self.eventEngine.put(event1)
        
        event2 = Event(EVENT_SPREADTRADING_POS)
        event2.dict_['data'] = newSpread
        self.eventEngine.put(event2)        
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """"""
        self.eventEngine.register(EVENT_TICK, self.processTickEvent)
        self.eventEngine.register(EVENT_TRADE, self.processTradeEvent)
        self.eventEngine.register(EVENT_POSITION, self.processPositionEvent)
        
    #----------------------------------------------------------------------
    def subscribeMarketData(self, vtSymbol):
        """订阅行情"""
        contract = self.mainEngine.getContract(vtSymbol)
        if not contract:
            self.writeLog(u'订阅行情失败，找不到该合约%s' %vtSymbol)
        
        req = VtSubscribeReq()
        req.symbol = contract.symbol
        req.exchange = contract.exchange
        
        self.mainEngine.subscribe(req, contract.gatewayName)
        
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.logContent = content
        
        event = Event(EVENT_SPREADTRADING_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)
        
    #----------------------------------------------------------------------
    def stop(self):
        """停止"""
        pass

    