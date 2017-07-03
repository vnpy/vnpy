# encoding: UTF-8

'''
本文件中实现了行情数据记录引擎，用于汇总TICK数据，并生成K线插入数据库。

使用DR_setting.json来配置需要收集的合约，以及主力合约代码。
'''

#import json
import csv
import os
import copy
from collections import OrderedDict
from datetime import datetime, timedelta
from Queue import Queue, Empty
from threading import Thread

from vnpy.event import Event
from vnpy.trader.vtEvent import *
from vnpy.trader.vtFunction import todayDate
from vnpy.trader.vtObject import VtSubscribeReq, VtLogData, VtBarData, VtTickData

from vnpy.trader.app.dataRecorder.drBase import *
from vnpy.trader.app.dataRecorder.language import text


########################################################################
class DrEngine(object):
    """数据记录引擎"""
    
    settingFileName = 'DR_setting.csv'
    path = os.path.abspath(os.path.dirname(__file__))
    settingFileName = os.path.join(path, settingFileName)    

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        # 当前日期
        self.today = todayDate()
        
        # 主力合约代码映射字典，key为具体的合约代码（如IF1604），value为主力合约代码（如IF0000）
        self.activeSymbolDict = {}
        
        # Tick对象字典
        self.tickDict = {}
        
        # K线对象字典
        self.barDict = {}
        
        # 配置字典
        self.settingDict = OrderedDict()
        
        # 负责执行数据库插入的单独线程相关
        self.active = False                     # 工作状态
        self.queue = Queue()                    # 队列
        self.thread = Thread(target=self.run)   # 线程
        
        # 载入设置，订阅行情
        self.loadSetting()
        
        # 启动数据插入线程
        self.start()
    
        # 注册事件监听
        self.registerEvent()  
        
    #----------------------------------------------------------------------
    def loadSetting(self):
        """加载配置"""
        with open(self.settingFileName) as f:
            drSetting = csv.DictReader(f)
            
            for d in drSetting:
                # 读取配置
                gatewayName = d['gateway']
                symbol = d['symbol']
                exchange = d['exchange']
                currency = d['currency']
                productClass = d['product']
                recordTick = d['tick']
                recordBar = d['bar']
                activeSymbol = d['active']
                
                if exchange:
                    vtSymbol = '.'.join([symbol, exchange])
                else:
                    vtSymbol = symbol
                
                # 订阅行情
                req = VtSubscribeReq()
                req.symbol = symbol
                req.exchange = exchange
                req.currency = currency
                req.productClass = productClass
                self.mainEngine.subscribe(req, gatewayName)
                
                # 设置需要记录的数据
                if recordTick:
                    tick = VtTickData()
                    self.tickDict[vtSymbol] = VtTickData()
                    
                if recordBar:
                    self.barDict[vtSymbol] = VtBarData()
                    
                if activeSymbol:
                    self.activeSymbolDict[vtSymbol] = activeSymbol
                    
                # 保存配置到缓存中
                self.settingDict[vtSymbol] = d
                
    #----------------------------------------------------------------------
    def getSetting(self):
        """获取配置"""
        return self.settingDict

    #----------------------------------------------------------------------
    def procecssTickEvent(self, event):
        """处理行情推送"""
        tick = event.dict_['data']
        vtSymbol = tick.vtSymbol
        
        # 转化Tick格式
        if not tick.datetime:
            tick.datetime = datetime.strptime(' '.join([tick.date, tick.time]), '%Y%m%d %H:%M:%S.%f')            
        
        # 更新Tick数据
        if vtSymbol in self.tickDict:
            self.insertData(TICK_DB_NAME, vtSymbol, tick)
            
            if vtSymbol in self.activeSymbolDict:
                activeSymbol = self.activeSymbolDict[vtSymbol]
                self.insertData(TICK_DB_NAME, activeSymbol, tick)
            
            # 发出日志
            self.writeDrLog(text.TICK_LOGGING_MESSAGE.format(symbol=tick.vtSymbol,
                                                             time=tick.time, 
                                                             last=tick.lastPrice, 
                                                             bid=tick.bidPrice1, 
                                                             ask=tick.askPrice1))
            
        # 更新分钟线数据
        if vtSymbol in self.barDict:
            bar = self.barDict[vtSymbol]
            
            # 如果第一个TICK或者新的一分钟
            if not bar.datetime or bar.datetime.minute != tick.datetime.minute:    
                if bar.vtSymbol:
                    newBar = copy.copy(bar)
                    self.insertData(MINUTE_DB_NAME, vtSymbol, newBar)
                    
                    if vtSymbol in self.activeSymbolDict:
                        activeSymbol = self.activeSymbolDict[vtSymbol]
                        self.insertData(MINUTE_DB_NAME, activeSymbol, newBar)                    
                    
                    self.writeDrLog(text.BAR_LOGGING_MESSAGE.format(symbol=bar.vtSymbol, 
                                                                    time=bar.time, 
                                                                    open=bar.open, 
                                                                    high=bar.high, 
                                                                    low=bar.low, 
                                                                    close=bar.close))
                         
                bar.vtSymbol = tick.vtSymbol
                bar.symbol = tick.symbol
                bar.exchange = tick.exchange
                
                bar.open = tick.lastPrice
                bar.high = tick.lastPrice
                bar.low = tick.lastPrice
                bar.close = tick.lastPrice
                
                bar.date = tick.date
                bar.time = tick.time
                bar.datetime = tick.datetime
                bar.volume = tick.volume
                bar.openInterest = tick.openInterest        
            # 否则继续累加新的K线
            else:                               
                bar.high = max(bar.high, tick.lastPrice)
                bar.low = min(bar.low, tick.lastPrice)
                bar.close = tick.lastPrice            

    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_TICK, self.procecssTickEvent)
 
    #----------------------------------------------------------------------
    def insertData(self, dbName, collectionName, data):
        """插入数据到数据库（这里的data可以是VtTickData或者VtBarData）"""
        self.queue.put((dbName, collectionName, data.__dict__))
        
    #----------------------------------------------------------------------
    def run(self):
        """运行插入线程"""
        while self.active:
            try:
                dbName, collectionName, d = self.queue.get(block=True, timeout=1)
                self.mainEngine.dbInsert(dbName, collectionName, d)
            except Empty:
                pass
            
    #----------------------------------------------------------------------
    def start(self):
        """启动"""
        self.active = True
        self.thread.start()
        
    #----------------------------------------------------------------------
    def stop(self):
        """退出"""
        if self.active:
            self.active = False
            self.thread.join()
        
    #----------------------------------------------------------------------
    def writeDrLog(self, content):
        """快速发出日志事件"""
        log = VtLogData()
        log.logContent = content
        event = Event(type_=EVENT_DATARECORDER_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)   
    