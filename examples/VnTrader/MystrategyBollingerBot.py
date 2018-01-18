# encoding: UTF-8

"""
仅在知乎Live中分享，请勿外传。

基于布林通道通道的交易策略，适合用在股指上5分钟线上。
"""

from __future__ import division

import talib
import numpy as np

from vnpy.trader.vtObject import VtBarData
from vnpy.trader.vtConstant import EMPTY_STRING
from vnpy.trader.app.ctaStrategy.ctaTemplate import CtaTemplate, BarGenerator, ArrayManager

import csv
from vnpy.trader.vtConstant import (EMPTY_STRING, EMPTY_UNICODE, 
                                    EMPTY_FLOAT, EMPTY_INT)

from vnpy.event import Event
from vnpy.trader.vtGlobal import globalSetting
from vnpy.trader.vtEvent import *
from vnpy.trader.vtGateway import *
from vnpy.trader.language import text
from vnpy.trader.vtFunction import getTempPath
########################################################################
class MyBollingerBotStrategy(CtaTemplate):
    """基于布林通道的交易策略"""
    className = 'MyBollingerBotStrategy'
    author = 'yuanhui'

    # 策略参数
    bollWindow = 26         # 通道窗口数
    entryDev = 2          # 开仓偏差
    exitDev = 1.2           # 平仓偏差
    trailingPrcnt = 0.4     # 移动止损百分比
    maWindow = 10           # 过滤用均线窗口
    initDays = 10           # 初始化数据所用的天数
    fixedSize = 1           # 每次交易的数量
    priceTick = 0.2         # 价格最小变动 
    
    DayTrendStatus='duotou'  #DuoTou, KongTou,Panzheng
    OnehourTrendstatus='panzhen'
    FifteenMinTrendStatus='panzhen'
    FiveMinTrendStatus='panzhen'

    # 5Min策略变量    
    bollMid = 0                         # 布林带中轨
    BeforebollMid=0                     #上一根K线的布林线中轨
    bollStd = 0                         # 布林带宽度
    bollUp = 0                          # 开仓上轨
    Beforebollup=0                      #上一根K线的布林线上轨
    bollDown = 0                        # 平仓下轨    
    beforebooldown=0                    #上一根K线的布林线下轨
    
    # 15Min策略变量    
    bollMid15 = 0                         # 布林带中轨
    BeforebollMid15=0                     #上一根K线的布林线中轨
    bollStd15 = 0                         # 布林带宽度
    bollUp15 = 0                          # 开仓上轨
    Beforebollup15=0                      #上一根K线的布林线上轨
    bollDown15 = 0                        # 平仓下轨    
    beforebolldown15=0                    #上一根K线的布林线下轨    
    
    maFilter = 0                        # 均线过滤
    maFilter1 = 0                       # 上一期均线                   
    
    intraTradeHigh = 0                  # 持仓期内的最高点  
    longEntry = 0                       # 多头开仓
    longExit = 0                        # 多头平仓   
    shortEntry=0
    shortExit=0
    
    deal=0
    dealopen=0
    
    
    orderList = []                      # 保存委托代码的列表

    # 参数列表，保存了参数的名称
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbol',
                 'bollWindow',
                 'entryDev',
                 'exitDev',
                 'trailingPrcnt',
                 'maWindow',
                 'initDays',
                 'fixedSize',
                 'DayTrendStatus']    

    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading',
               'pos',
               'bollUp',
               'bollDown',
               'bollUp15',
               'bollDown15',
               'FifteenMinTrendStatus',
               'FiveMinTrendStatus']
    
    # 同步列表
    syncList = ['pos',
                'intraTradeHigh']

    #----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        super(MyBollingerBotStrategy, self).__init__(ctaEngine, setting)
        
        self.bm = BarGenerator(self.onBar, 5, self.onFiveBar)
        self.am = ArrayManager()
        
        self.bm15 = BarGenerator(self.onBar, 15, self.on15MinBar)
        self.am15 = ArrayManager()        
        with open("datasig.csv","wb+") as csvfile: 
            writer = csv.writer(csvfile)
            writer.writerow(["datetime","open","close","high","low","openInterest","volume","deal","pDown","pUp","dealOpen"])
        with open("datasig15.csv","wb+") as csvfile: 
            writer = csv.writer(csvfile)
            writer.writerow(["datetime","open","close","high","low","openInterest","volume","deal","pDown","pUp","dealOpen"])              
        
    #----------------------------------------------------------------------
    def onInit(self):
        """初始化策略（必须由用户继承实现）"""
        self.writeCtaLog(u'%s策略初始化' %self.name)
        
        # 载入历史数据，并采用回放计算的方式初始化策略数值
        initData = self.loadBar(self.initDays)
        for bar in initData:
            self.onBar(bar)

        self.putEvent()

    #----------------------------------------------------------------------
    def onStart(self):
        """启动策略（必须由用户继承实现）"""
        self.writeCtaLog(u'%s策略启动' %self.name)
        self.putEvent()

    #----------------------------------------------------------------------
    def onStop(self):
        """停止策略（必须由用户继承实现）"""
        self.writeCtaLog(u'%s策略停止' %self.name)
        self.putEvent()

    #----------------------------------------------------------------------
    def onTick(self, tick):
        """收到行情TICK推送（必须由用户继承实现）"""
        self.bm.updateTick(tick)

    #----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送（必须由用户继承实现）"""
        #self.bm.updateBar(bar)
        # 基于15分钟判断趋势过滤，因此先更新
        self.bm15.updateBar(bar)
    
        # 基于5分钟判断
        self.bm.updateBar(bar)        
        print u"策略:",self.__dict__["name"]
        print u"时间：%s,1分钟刷新，趋势状态,5分钟趋势%s,15分钟趋势%s,日趋势%s"%(bar.time,self.FiveMinTrendStatus,self.FifteenMinTrendStatus,self.DayTrendStatus)  
    
    #----------------------------------------------------------------------
    def onFiveBar(self, bar):
        """收到5分钟K线"""        
        #计算上一个k线的布林中轨，上轨，下轨
        self.BeforebollMid=self.am.sma(self.bollWindow)
        self.Beforebollup,self.beforebooldown=self.am.boll(self.bollWindow,self.entryDev)
        # 保存K线数据
        self.am.updateBar(bar)
        if not self.am.inited:
            return        

        # 撤销之前发出的尚未成交的委托（包括限价单和停止单）
        self.cancelAll()
        orderList=[]
    
        # 计算指标数值
        self.bollMid = self.am.sma(self.bollWindow)
        #self.bollStd = self.am.std(self.bollWindow)
        self.bollUp,self.bollDown = self.am.boll(self.bollWindow,self.entryDev)
        #self.boolDown = self.bollMid - self.bollStd * self.entryDev
        
        #maArray = self.am.sma(self.maWindow, True)
        #self.maFilter = maArray[-1]
        #self.maFilter1 = maArray[-2]
        #判断当前5Min布林线趋势状态
        if bar.high > self.Beforebollup:
            self.FiveMinTrendStatus='duotou'
        elif bar.low < self.beforebooldown:
            self.FiveMinTrendStatus='kongtou'
        elif bar.low < self.BeforebollMid and self.FiveMinTrendStatus=='duotou':
            self.FiveMinTrendStatus='panzhen'
        elif bar.high > self.BeforebollMid and self.FiveMinTrendStatus=='kongtou':
            self.FiveMinTrendStatus='panzhen'
        
        if self.DayTrendStatus=='kongtou' and bar.high > self.bollMid15 and self.FifteenMinTrendStatus == 'kongtou':
            self.FifteenMinTrendStatus=='panzhen'
        if self.DayTrendStatus=='duotou' and bar.low < self.bollMid15 and self.FifteenMinTrendStatus == 'duotou':
            
            self.FifteenMinTrendStatus=='panzhen'        
        # 判断是否要进行交易
        print u"5分钟刷新，趋势状态,5分钟趋势%s,15分钟趋势%s"%(self.FiveMinTrendStatus,self.FifteenMinTrendStatus)        
        # 当前无仓位，发送OCO开仓委托
        if self.pos == 0:
            #self.intraTradeHigh = bar.high
            
            if self.DayTrendStatus=='duotou' and (self.FifteenMinTrendStatus=='panzhen' or self.FifteenMinTrendStatus=='kongtou'):
                orderList=self.buy(self.bollUp15+self.priceTick, self.fixedSize, True)
                print u"委托多单，15分钟上轨开仓"
            elif self.DayTrendStatus=='duotou' and self.FifteenMinTrendStatus=='duotou' and self.FiveMinTrendStatus=='duotou':
                self.longEntry = bar.close
                orderList=self.buy(self.longEntry+self.priceTick, self.fixedSize, True)        
                print u"委托多单，5分钟收盘价开仓"
            elif self.DayTrendStatus=='duotou' and self.FifteenMinTrendStatus=='duotou' and (self.FiveMinTrendStatus=='panzhen' or self.FiveMinTrendStatus=='kongtou'):
                self.longEntry=self.bollUp
                orderList=self.buy(self.longEntry+self.priceTick, self.fixedSize, True)    
                print u"委托多单，5分钟上轨开仓"
            elif  self.DayTrendStatus=='kongtou' and (self.FifteenMinTrendStatus=='panzhen' or self.FifteenMinTrendStatus=='duotou') :
                self.orderList=self.short(self.bollDown15-self.priceTick, self.fixedSize, True)
                print u"委托空单，15分钟下轨开仓"
            elif self.DayTrendStatus=='kongtou' and self.FifteenMinTrendStatus=='kongtou' and self.FiveMinTrendStatus=='kongtou':
                self.shortEntry = bar.close
                orderList=self.short(self.shortEntry-self.priceTick, self.fixedSize, True)   
                print u"委托空单，5分钟收盘价开仓"
            elif self.DayTrendStatus=='kongtou' and self.FifteenMinTrendStatus=='kongtou' and (self.FiveMinTrendStatus=='panzhen' or self.FiveMinTrendStatus=='duotou'):
                self.shortEntry=self.bollDown
                orderList=self.short(self.shortEntry-self.priceTick, self.fixedSize, True)  
                print u"委托空单，5分钟下轨开仓"
                     

        # 持有多头仓位
        elif self.pos > 0:
            #self.intraTradeHigh = max(self.intraTradeHigh, bar.high)
            #self.longExit = self.intraTradeHigh * (1 - self.trailingPrcnt/100)
            #self.longExit = min(self.longExit, self.exitUp)
            #self.longExit=self.boolDown
            
            orderList=self.sell(self.bollDown-self.priceTick, abs(self.pos), True)
            print u"委托止损单，5分钟下轨平仓"
        # 持有空头仓位
        elif self.pos < 0:
            orderList=self.cover(self.bollUp+self.priceTick, abs(self.pos), True)
            print u"委托止损单，5分钟上轨平仓"
    
        with open("datasig.csv","ab+",) as csvfile: 
            writer = csv.writer(csvfile)
            writer.writerow([bar.datetime,bar.open, bar.close, bar.high, bar.low,bar.openInterest,bar.volume,self.deal,0,0,self.dealopen])
        self.deal=0
        self.dealopen=0
        

        if orderList:
            print u"委托单成功单号",orderList
        else:
            print u"委托单失败"             
        # 发出状态更新事件
        self.putEvent()        


    def on15MinBar(self, bar):
        """15分钟K线推送"""
    
        #计算上一个k线的布林中轨，上轨，下轨
        self.BeforebollMid15=self.am15.sma(self.bollWindow)
        self.Beforebollup15,self.beforebolldown15=self.am15.boll(self.bollWindow,self.entryDev)   
        
        self.am15.updateBar(bar)
        
        if not self.am15.inited:
            return
        
        # 计算指标数值
        self.bollMid15 = self.am.sma(self.bollWindow)
        self.bollUp15,self.bollDown15 = self.am.boll(self.bollWindow,self.entryDev)

    
        #判断当前15Min布林线趋势状态
        if bar.high > self.Beforebollup15 and bar.low > self.BeforebollMid15:
            self.FifteenMinTrendStatus='duotou'
        elif bar.low < self.beforebolldown15 and bar.high < self.Beforebollup15:
            self.FifteenMinTrendStatus='kongtou'
        elif bar.low < self.BeforebollMid15 and self.FifteenMinTrendStatus=='duotou':
            self.FifteenMinTrendStatus='panzhen'
        elif bar.high > self.BeforebollMid15 and self.FifteenMinTrendStatus=='kongtou':
            self.FifteenMinTrendStatus='panzhen'
   
        with open("datasig15.csv","ab+",) as csvfile: 
            writer = csv.writer(csvfile)
            writer.writerow([bar.datetime,bar.open, bar.close, bar.high, bar.low,bar.openInterest,bar.volume,self.deal,0,0,self.dealopen])
        
        print u"15分钟刷新，趋势状态,5分钟趋势%s,15分钟趋势%s"%(self.FiveMinTrendStatus,self.FifteenMinTrendStatus)
        # 当前无仓位，发送OCO开仓委托
        '''
        if self.pos == 0:
            self.intraTradeHigh = bar.high
            
            if self.FifteenMinTrendStatus=='panzhen':
                self.longEntry = self.bollUp15
                self.shortEntry=self.booldown15
                self.buy(self.longEntry, self.fixedSize, True)
                self.short(self.shortEntry,self.fixedSize,True)
        '''
    #----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        pass

    #----------------------------------------------------------------------
    def onTrade(self, trade):
        #打印信息
        print u"委托单成交"
        print trade.direction
        print trade.offset
        print "15min:",self.FifteenMinTrendStatus
        print "5min:",self.FiveMinTrendStatus
    
        # 发出状态更新事件
        orderList=[]
        if self.pos > 0 :
            orderList=self.sell(self.bollDown-self.priceTick, abs(self.pos), True)
            print u"委托止损单，5分钟下轨平仓"
        elif self.pos < 0 :
            orderList=self.cover(self.bollUp+self.priceTick, abs(self.pos), True)
            print u"委托止损单，5分钟上轨平仓"
        
        #打印信息    
        if orderList:
            print u"委托单成功单号",orderList
        else:
            print u"委托单失败"            

            
        if trade.offset==OFFSET_OPEN:
            if trade.direction==DIRECTION_LONG:
                self.dealopen=1
                self.FifteenMinTrendStatus='duotou'
                self.FiveMinTrendStatus='duotou'
            else:
                self.dealopen=-1
                self.FifteenMinTrendStatus='kongtou'
                self.FiveMinTrendStatus='kongtou'
                
        if trade.offset==OFFSET_CLOSE:
            if trade.direction==DIRECTION_LONG:
                self.deal=1
            else:
                self.deal=-1
                

        self.putEvent()

    #----------------------------------------------------------------------
    def onStopOrder(self, so):
        """停止单推送"""
        pass