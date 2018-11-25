# -*- coding: utf-8 -*-

import numpy as np
import talib
from datetime import datetime, time

from vnpy.trader.vtObject import VtBarData

########################################################################
class BarGenerator(object):
    """
    K线合成器

    How it works:

        Normally, a main task or class (such as a strategy or a data recorder) registers itself to receive tick events 
    from the event engine.  When a tick event happens, a function in the main task/class (for instance onTick in 
    CtaTemplate class, or procecssTickEvent in drEngine) is called.  That function in turn needs to call updateTick of this class.
    Function updateTick then calls all the registered onTick callbacks, then generates 1-second bars and/or 1-minute bars 
    from the tick data depending on requirement.  The update function in 1-second bar will generate x-second bars and/or
    1-minute bars based on requirement.  If both 1-second bars and 1-minute bars are required, then 1-minute bars are generated 
    from 1-second bars instead of from tick data.  The update function in 1-minute bar will generate x-minute bars and day bars 
    based on requirement.  All registered onBar callbacks are called within the respective time frame.

    How to use it:

        To instantiate the class, call the constructor BarGenerator(onMinBar=None, onTick=None, onSecBar=None, onDayBar=None).  
    The optional args are to specify a callback function at a certain time frame.  If it's called simply as BarGenerator(onBar),
    then by default, the the callback specified is on the 1-minute bars.  If a callback function is specified at the instatiation,
    then there is no need to call the additional functions to specify the callback.  Otherwise, operations will be redundant.

        To register your callback on the tick level, call addOnTickCallback to pass in the callback function.

        To require the generation of second bars or to register you callback on the second bars, call requireSecondBar 
    to pass in the callback function.  1-second bars are generated from tick data.

        To require the generation of x-second bars or to register you callback on the x-second bars, call requireXSecBar 
    to pass in the callback function.  This function also ensures the generation of 1-second bars, 
    as x-second bars are based on 1-second bars.

        To require the generation of minute bars or to register you callback on the minute bars, call requireMinBar to 
    pass in the callback function.  1-minute bars are generated from tick data, or from 1-second data if second bars are 
    also enabled.

        To require the generation of x-minute bars or to register you callback on the x-minute bars, call requireXMinBar 
    to pass in the callback function.  This function also ensures the generation of 1-minute bars, 
    as x-minute bars are based on 1-minute bars.

        To require the generation of day bars or to register you callback on the day bars, call requireDayBar to pass 
    in the callback function.  This function also ensures the generation of day bars, and 1-minute bars, as day bars are 
    based on 1-minute bars.  Day bars can be different for different markets.  To make sure to call setDayBarTimes to specify 
    startTime, endTime, auxStartTime, auxEndTime.  The default times are 21:00, 15:00, 9:00, 18:00 (not used).

        If you load data from DB at onInit, you can call fillSecondBars, fillMinuteBars, or fillDayBars with the data.  
    The arguments resampleMinDay or resampleDay are to ensure bars in the longer time-frame are resampled or not.
    It's necessary to set resampleDay to False, for instance, if you also plan to load day bars from DB.  If you set it to False,
    then you need to call setMinBarResample and/or setDayBarResample afterwards to turn resampling on for live execution.

        After registering all callbacks, you need to call an entry function in this class to get things going.  Generally, 
    tick data are the most fundamental data a trader deals with.  In that case, you need to call updateTick of this class 
    from one of your tick processing functions.  In cases where you are not dealing with tick data but with 1-minute bars
    (in backtesting for instance) as the most fundamental data, then instead of calling updateTick as the entry function, 
    you need to call updateWithMinuteBar as the entry function from your 1-minute-bar processing function, and make sure 
    that you do not register that function as a callback!  Likewise, if you are dealing with 1-second bars, the entry function 
    is updateWithSecondBar.  For day bars, the entry function is updateWithDayBar.  After one of the entry functions is called, 
    all the bar generations and callbacks will start from there.

        ** As a special note about a procedure change from the previous version, calling updateBar of this class is no longer needed
    for normal operations because all bars are automatically updated.  Calling it from an already registered callback function 
    will result in dead loops.  Otherwise, calling it results in redundant operations.

    """

    #----------------------------------------------------------------------
    def __init__(self, onMinBar=None, onTick=None, onSecBar=None, onDayBar=None) : 
        """Constructor"""

        self.secBar = None
        if onSecBar :
            self.secBar = SecondBar()  # have 1-second update also update x-second bars
            self.secBar._addResampleCB(self.updateSubMinBars)
            self.secBar.addCallback(onSecBar)

        self.minBar = None             # 1分钟K线对象
        if onMinBar :
            self.minBar = MinuteBar() # have 1-minute update also update x-minute bars
            self.minBar._addResampleCB(self.updateXMinDayBars)
            self.minBar.addCallback(onMinBar)

        if self.secBar and self.minBar :
            self.secBar._addResampleCB(self.minBar.updateFromSecond)

        self.onTickList = []
        if onTick :
            self.addOnTickCallback(onTick)

        self.xsecBarDict = {}
        self.xminBarDict = {}

        self.dayBar = None
        if onDayBar :
            if not self.minBar :
                self.minBar = MinuteBar()
                self.minBar._addResampleCB(self.updateXMinDayBars)
                if self.secBar :
                    self.secBar._addResampleCB(self.minBar.updateFromSecond)
            self.dayBar = DayBar(onDayBar)

    
    def addOnTickCallback(self, onTick) :
        self.onTickList.append(onTick)


    def _ensureSecondBar(self) :
        if not self.secBar :
            self.secBar = SecondBar()
            self.secBar._addResampleCB(self.updateSubMinBars)
            if self.minBar :
                self.secBar._addResampleCB(self.minBar.updateFromSecond)


    def requireSecondBar(self, onSecBar) :
        self._ensureSecondBar()
        self.secBar.addCallback(onSecBar)


    def requireXSecBar(self, xsec, onXSecBar) :
        self._ensureSecondBar()

        if xsec in self.xsecBarDict :
            self.xsecBarDict[xsec].addCallback(onXSecBar)
        else :
            self.xsecBarDict[xsec] = XSecondBar(xsec, onXSecBar)


    def _ensureMinuteBar(self) :
        if not self.minBar :
            self.minBar = MinuteBar()
            self.minBar._addResampleCB(self.updateXMinDayBars)
            if self.secBar :
                self.secBar._addResampleCB(self.minBar.updateFromSecond)

    def requireMinBar(self, onMinBar) :
        self._ensureMinuteBar()
        self.minBar.addCallback(onMinBar)


    def setMinBarResample(self, bol) :
        """ 
        if during onInit you want to load day bars from DB and don't want to resample them from 1-minute bars,
        call this to set bol = False.  Set bol = True to resample day bars from 1-minute bars.
        """
        if self.minBar :
            self.minBar.setResampling(bol)

    def requireXMinBar(self, xmin, onXMinBar) :
        self._ensureMinuteBar()
        
        if xmin in self.xminBarDict :
            self.xminBarDict[xmin].addCallback(onXMinBar)
        else :
            self.xminBarDict[xmin] = XMinuteBar(xmin, onXMinBar)


    def requireDayBar(self, onDayBar) :
        self._ensureMinuteBar()

        if not self.dayBar :
            self.dayBar = DayBar(onDayBar)
        else :
            self.dayBar.addCallback(onDayBar)


    def setDayBarTimes(self, startTime, endTime, auxStartTime, auxEndTime) :
        """
        startTime and endTime are the time of day bar start and end,
        auxStartTime and auxEndTime are needed so that some uncommon days such as holidays can be handled
        all time args should in the format of "HH:MM"
        """

        if self.dayBar :
            self.dayBar.setBarTimes(startTime, endTime, auxStartTime, auxEndTime)
        else :
            print("you must first call requireDayBar first")


    def setDayBarResample(self, bol) :
        """ 
        if during onInit you want to load day bars from DB and don't want to resample them from 1-minute bars,
        call this to set bol = False.  Set bol = True to resample day bars from 1-minute bars.
        """
        if self.dayBar :
            self.dayBar.setResampling(bol)
        
    
    def callAllTickCBs(self, tick) :
        for cb in self.onTickList :
            cb(tick)        


    #----------------------------------------------------------------------
    def updateTick(self, tick):
        """ TICK更新 """

        self.callAllTickCBs(tick)

        if self.secBar :
            # if second bars are required, then it sill also generate minute bars, if also required
            self.secBar.updateFromTick(tick)    
        else :
            if self.minBar :
                self.minBar.updateFromTick(tick)

    def updateWithSecondBar(self, bar) :
        if self.secBar :
            self.secBar.updateAllOnBar(bar)

    def updateWithMinuteBar(self, bar) :
        if self.minBar :
            self.minBar.updateAllOnBar(bar)

    def updateWithDayBar(self, bar) :
        if self.dayBar :
            self.dayBar.updateAllOnBar(bar)


    def updateSubMinBars(self, bar) :
        for xsecBar in self.xsecBarDict :
            self.xsecBarDict[xsecBar].update(bar)

    #----------------------------------------------------------------------
    def updateXMinDayBars(self, bar) :
        """ update xmin and day bars """
        for xminBar in self.xminBarDict :
            self.xminBarDict[xminBar].update(bar)

        if self.dayBar :
            self.dayBar.update(bar)


    def updateBar(self, bar) :
        """ update xsec, xmin and day bars """
        print("Warning: calling ctaBarsEngine:updateBar is only needed for special situations")
        self.updateSubMinBars(bar)
        self.updateXMinDayBars(bar)


    #----------------------------------------------------------------------
    def generate(self):
        """手动强制立即完成K线合成"""
        print("Force generate bars ", self.minBar.bar.time)
        # finalize 1-minute, x-minute, and day bars
        if self.minBar :
            self.minBar.finalizeBar()

    
    def fillSecondBars(self, bars, resampleMinDay=False) :
        self._ensureSecondBar()
        self.setMinBarResample(resampleMinDay)
        self.setDayBarResample(resampleMinDay)
        for bar in bars:
            self.secBar.updateAllOnBar(bar)


    def fillMinuteBars(self, bars, resampleDay=False) :
        self._ensureMinuteBar()
        self.setDayBarResample(resampleDay)
        for bar in bars:
            self.minBar.updateAllOnBar(bar)


    def fillDayBars(self, bars) :
        if not self.dayBar :
            self.dayBar = DayBar()
        for bar in bars:
            self.dayBar.callAllCBsOnBar(bar)



class XBar(object) :
    """ bar template class """

    def __init__(self, onBar) : 
        self.bar = None             # 1分钟K线对象
        self.resampleSelf = True
        self.resampleCBList = []
        self.onBarList = []
        if onBar :
            self.onBarList.append(onBar)          # 1分钟K线回调函数      

    def _addResampleCB(self, update) :
        self.resampleCBList.append(update)

    def addCallback(self, onBar) :
        self.onBarList.append(onBar)

    def resampleBars(self) :
        for update in self.resampleCBList :
            update(self.bar)

    def callAllCBs(self) :
        for cb in self.onBarList :
            cb(self.bar)

    def updateAll(self) :
        self.resampleBars()
        self.callAllCBs()

    def resampleBarsOnBar(self, bar) :
        for update in self.resampleCBList :
            update(bar)

    def callAllCBsOnBar(self, bar) :
        for cb in self.onBarList :
            cb(bar)

    def updateAllOnBar(self, bar) :
        self.resampleBarsOnBar(bar)
        self.callAllCBsOnBar(bar)

    def setResampling(self, bol=True) :
        self.resampleSelf = bol


class SecondBar(XBar) :
    """
    1-second bar generator based on ticks
    """

    def __init__(self, onBar=None) : 
        super(SecondBar, self).__init__(onBar)
        self.lastTick = None        # 上一TICK缓存对象

    #----------------------------------------------------------------------
    def updateFromTick(self, tick) :

        newMinute = False   # 默认不是新的second        
        # 尚未创建对象
        if not self.bar:
            self.bar = VtBarData()
            newMinute = True
        # 新的second
        elif self.bar.datetime.second != tick.datetime.second:
            # 生成上一分钟K线的时间戳
            self.bar.datetime = self.bar.datetime.replace(microsecond=0)  # 将微秒设为0
            self.bar.date = self.bar.datetime.strftime('%Y%m%d')
            self.bar.time = self.bar.datetime.strftime('%H:%M:%S.%f')
            
            # 推送已经结束的上1-second K线
            self.updateAll()
            
            # 创建新的K线对象
            self.bar = VtBarData()
            newMinute = True
            
        # 初始化新1-second的K线数据
        if newMinute:
            self.bar.vtSymbol = tick.vtSymbol
            self.bar.symbol = tick.symbol
            self.bar.exchange = tick.exchange

            self.bar.open = tick.lastPrice
            self.bar.high = tick.lastPrice
            self.bar.low = tick.lastPrice
        # 累加更新老1-second的K线数据
        else:                                   
            self.bar.high = max(self.bar.high, tick.lastPrice)
            self.bar.low = min(self.bar.low, tick.lastPrice)

        # 通用更新部分
        self.bar.close = tick.lastPrice        
        self.bar.datetime = tick.datetime  
        self.bar.openInterest = tick.openInterest
   
        if self.lastTick:
            volumeChange = tick.volume - self.lastTick.volume   # 当前K线内的成交量
            self.bar.volume += max(volumeChange, 0)             # 避免夜盘开盘lastTick.volume为昨日收盘数据，导致成交量变化为负的情况

        self.lastTick = tick


class XSecondBar(XBar) :
    """
    1. 基于1 second K线合成 X-second K线（X可以是 any number ）
    """

    def __init__(self, xsec, onXSecBar=None) :
        super(XSecondBar, self).__init__(onXSecBar)
        if xsec <= 1 :
            print("xsec should be above 1 and below 3600")
        self.xsec = xsec            # X的值

    def update(self, bar) :
        """x-second K线更新"""
        # 尚未创建对象
        if not self.bar:
            self.bar = VtBarData()
            
            self.bar.vtSymbol = bar.vtSymbol
            self.bar.symbol = bar.symbol
            self.bar.exchange = bar.exchange
        
            self.bar.open = bar.open
            self.bar.high = bar.high
            self.bar.low = bar.low            
            
            self.bar.datetime = bar.datetime    # 以第一根second K线的开始时间戳作为X-second线的时间戳
        # 累加老K线
        else:
            self.bar.high = max(self.bar.high, bar.high)
            self.bar.low = min(self.bar.low, bar.low)

        # 通用部分
        self.bar.close = bar.close        
        self.bar.openInterest = bar.openInterest
        self.bar.volume += int(bar.volume)                

        # X seconds 已经走完
        if not (bar.datetime.minute * 60 + bar.datetime.second + 1) % self.xsec:   # 可以用X整除
            # 生成上一Xsecond K线的时间戳
            self.bar.datetime = self.bar.datetime.replace(microsecond=0)  # 将秒和微秒设为0
            self.bar.date = self.bar.datetime.strftime('%Y%m%d')
            self.bar.time = self.bar.datetime.strftime('%H:%M:%S.%f')
            
            # 推送
            self.updateAll()
            
            # 清空老K线缓存对象
            self.bar = None


class MinuteBar(XBar) :
    """
    1-minute bar generator based on ticks or second bars
    """
    def __init__(self, onBar=None) : 
        super(MinuteBar, self).__init__(onBar)
        self.lastTick = None        # 上一TICK缓存对象

    def updateFromTick(self, tick) :

        newMinute = False   # 默认不是新的一分钟        
        # 尚未创建对象
        if not self.bar:
            self.bar = VtBarData()
            newMinute = True
        # 新的一分钟
        elif self.bar.datetime.minute != tick.datetime.minute:
            # 生成上一分钟K线的时间戳
            self.finalizeBar()
            
            # 创建新的K线对象
            self.bar = VtBarData()
            newMinute = True
            
        # 初始化新一分钟的K线数据
        if newMinute:
            self.bar.vtSymbol = tick.vtSymbol
            self.bar.symbol = tick.symbol
            self.bar.exchange = tick.exchange

            self.bar.open = tick.lastPrice
            self.bar.high = tick.lastPrice
            self.bar.low = tick.lastPrice
        # 累加更新老一分钟的K线数据
        else:                                   
            self.bar.high = max(self.bar.high, tick.lastPrice)
            self.bar.low = min(self.bar.low, tick.lastPrice)

        # 通用更新部分
        self.bar.close = tick.lastPrice        
        self.bar.datetime = tick.datetime  
        self.bar.openInterest = tick.openInterest
   
        if self.lastTick:
            volumeChange = tick.volume - self.lastTick.volume   # 当前K线内的成交量
            self.bar.volume += max(volumeChange, 0)             # 避免夜盘开盘lastTick.volume为昨日收盘数据，导致成交量变化为负的情况

        self.lastTick = tick


    def updateFromSecond(self, bar) :
        if self.resampleSelf :
            newMinute = False   # 默认不是新的一分钟        
            # 尚未创建对象
            if not self.bar:
                self.bar = VtBarData()
                newMinute = True
            # 新的一分钟
            elif self.bar.datetime.minute != bar.datetime.minute:
                # 生成上一分钟K线的时间戳
                self.finalizeBar()
                
                # 创建新的K线对象
                self.bar = VtBarData()
                newMinute = True
                
            # 初始化新一分钟的K线数据
            if newMinute:
                self.bar.vtSymbol = bar.vtSymbol
                self.bar.symbol = bar.symbol
                self.bar.exchange = bar.exchange

                self.bar.open = bar.open
                self.bar.high = bar.high
                self.bar.low = bar.low
            # 累加更新老一分钟的K线数据
            else:                                   
                self.bar.high = max(self.bar.high, bar.high)
                self.bar.low = min(self.bar.low, bar.low)

            # 通用更新部分
            self.bar.close = bar.close        
            self.bar.datetime = bar.datetime  
            self.bar.openInterest = bar.openInterest
            self.bar.volume += int(bar.volume)              


    def finalizeBar(self) :
        self.bar.datetime = self.bar.datetime.replace(second=0, microsecond=0)  # 将秒和微秒设为0
        self.bar.date = self.bar.datetime.strftime('%Y%m%d')
        self.bar.time = self.bar.datetime.strftime('%H:%M:%S.%f')
        self.updateAll()
        self.bar = None


class XMinuteBar(XBar) :
    """
    1. 基于1分钟K线合成X分钟K线（X可以是2、3、5、10、15、30	）
    """

    def __init__(self, xmin, onXMinBar=None) :
        super(XMinuteBar, self).__init__(onXMinBar)
        if xmin not in [2, 3, 5, 10, 15, 30] :
            print("xmin is recommended among 2, 3, 5, 10, 15, 30")
        self.xmin = xmin            # X的值

    def update(self, bar) :
        """x分钟K线更新"""
        # 尚未创建对象
        if not self.bar:
            self.bar = VtBarData()
            
            self.bar.vtSymbol = bar.vtSymbol
            self.bar.symbol = bar.symbol
            self.bar.exchange = bar.exchange
        
            self.bar.open = bar.open
            self.bar.high = bar.high
            self.bar.low = bar.low            
            
            self.bar.datetime = bar.datetime    # 以第一根分钟K线的开始时间戳作为X分钟线的时间戳
        # 累加老K线
        else:
            self.bar.high = max(self.bar.high, bar.high)
            self.bar.low = min(self.bar.low, bar.low)

        # 通用部分
        self.bar.close = bar.close        
        self.bar.openInterest = bar.openInterest
        self.bar.volume += int(bar.volume)                

        # X分钟已经走完
        if not (bar.datetime.minute + 1) % self.xmin:   # 可以用X整除
            # 生成上一X分钟K线的时间戳
            self.bar.datetime = self.bar.datetime.replace(second=0, microsecond=0)  # 将秒和微秒设为0
            self.bar.date = self.bar.datetime.strftime('%Y%m%d')
            self.bar.time = self.bar.datetime.strftime('%H:%M:%S.%f')
            
            # 推送
            self.updateAll()
            
            # 清空老K线缓存对象
            self.bar = None


class DayBar(XBar) :
    """
    DayBar: default startTime at 21:00, endTime at "15:00"
    default auxStartTime at 9:00, auxEndTime at 15:01 (meaningless now)
    """

    def __init__(self, onDayBar=None) :
        super(DayBar, self).__init__(onDayBar)

        self.startTime = time(21, 0)
        self.endTime = time(15, 0)
        self.auxStartTime = time(9, 0)
        self.auxEndTime = time(15, 1)

    def setBarTimes(self, startTime, endTime, auxStartTime, auxEndTime) :
        """
        startTime and endTime are the time of day bar start and end,
        auxStartTime and auxEndTime are needed so that some uncommon days such as holidays can be handled
        all time args should in the format of "HH:MM"
        """
        
        self.startTime = datetime.strptime(startTime, '%H:%M').time()
        self.endTime = datetime.strptime(endTime, '%H:%M').time()
        self.auxStartTime = datetime.strptime(auxStartTime, '%H:%M').time()
        self.auxEndTime = datetime.strptime(auxEndTime, '%H:%M').time()

    #----------------------------------------------------------------------
    def update(self, bar):
        """ update day bars """

        if self.resampleSelf :
            barTime = bar.datetime.replace(second=0, microsecond=0).time()
            if self.bar and barTime == self.startTime :
                    # 推送
                    print("DayBar update: force finish bar ", self.bar.datetime, self.bar.time, " at ", bar.datetime)
                    for onDayBar in self.onBarList :
                        onDayBar(self.bar)               
                    # 清空老K线缓存对象
                    self.bar = None

            if not self.bar :
                if (barTime == self.startTime or barTime == self.auxStartTime):
                    self.bar = VtBarData()
                    
                    print("A bar started ", bar.vtSymbol, " ", bar.datetime)
                    self.bar.vtSymbol = bar.vtSymbol
                    self.bar.symbol = bar.symbol
                    self.bar.exchange = bar.exchange
                
                    self.bar.open = bar.open
                    self.bar.high = bar.high
                    self.bar.low = bar.low            
                    
                    self.bar.datetime = bar.datetime.replace(second=0, microsecond=0)    # 以第一根分钟K线的开始时间戳作为day线的时间戳
                    self.bar.date = bar.datetime.strftime('%Y%m%d')
            # 累加老K线
            else:
                self.bar.high = max(self.bar.high, bar.high)
                self.bar.low = min(self.bar.low, bar.low)

            # print("In updateDayBar: ", self.bar, " ", barTime, " ", self.endTime)
            if self.bar :
                self.bar.time = bar.datetime.strftime('%H:%M:%S.%f')     # want to record end time
                self.bar.close = bar.close        
                self.bar.openInterest = bar.openInterest
                self.bar.volume += int(bar.volume)                

                # day 已经走完
                if barTime == self.endTime  or barTime == self.auxEndTime :   
                    print("DayBar update: finish bar ", bar.vtSymbol, bar.datetime)
                    # 推送
                    self.updateAll()               
                    
                    # 清空老K线缓存对象
                    self.bar = None



########################################################################
class ArrayManager(object):
    """
    K线序列管理工具，负责：
    1. K线时间序列的维护
    2. 常用技术指标的计算
    """

    #----------------------------------------------------------------------
    def __init__(self, size=100):
        """Constructor"""
        self.count = 0                      # 缓存计数
        self.size = size                    # 缓存大小
        self.inited = False                 # True if count>=size
        
        self.openArray = []     # OHLC
        self.highArray = []
        self.lowArray = []
        self.closeArray = []
        self.volumeArray = []

        if size>0 :
            self.openArray = np.zeros(size)     # OHLC
            self.highArray = np.zeros(size)
            self.lowArray = np.zeros(size)
            self.closeArray = np.zeros(size)
            self.volumeArray = np.zeros(size)


    def setSize(self, size) :
        if size>0 :
            self.openArray = np.zeros(size)     # OHLC
            self.highArray = np.zeros(size)
            self.lowArray = np.zeros(size)
            self.closeArray = np.zeros(size)
            self.volumeArray = np.zeros(size)
        else :
            print("array size should be > 0")
        

    #----------------------------------------------------------------------
    def updateBar(self, bar):
        """更新K线"""
        self.count += 1
        if not self.inited and self.count >= self.size:
            self.inited = True
        
        self.openArray[0:self.size-1] = self.openArray[1:self.size]
        self.highArray[0:self.size-1] = self.highArray[1:self.size]
        self.lowArray[0:self.size-1] = self.lowArray[1:self.size]
        self.closeArray[0:self.size-1] = self.closeArray[1:self.size]
        self.volumeArray[0:self.size-1] = self.volumeArray[1:self.size]
    
        self.openArray[-1] = bar.open
        self.highArray[-1] = bar.high
        self.lowArray[-1] = bar.low        
        self.closeArray[-1] = bar.close
        self.volumeArray[-1] = bar.volume
        
    #----------------------------------------------------------------------
    @property
    def open(self):
        """获取开盘价序列"""
        return self.openArray
        
    #----------------------------------------------------------------------
    @property
    def high(self):
        """获取最高价序列"""
        return self.highArray
    
    #----------------------------------------------------------------------
    @property
    def low(self):
        """获取最低价序列"""
        return self.lowArray
    
    #----------------------------------------------------------------------
    @property
    def close(self):
        """获取收盘价序列"""
        return self.closeArray
    
    #----------------------------------------------------------------------
    @property    
    def volume(self):
        """获取成交量序列"""
        return self.volumeArray
    
    #----------------------------------------------------------------------
    def sma(self, n, array=False):
        """简单均线"""
        result = talib.SMA(self.close, n)
        if array:
            return result
        return result[-1]
        
    #----------------------------------------------------------------------
    def std(self, n, array=False):
        """标准差"""
        result = talib.STDDEV(self.close, n)
        if array:
            return result
        return result[-1]
    
    #----------------------------------------------------------------------
    def cci(self, n, array=False):
        """CCI指标"""
        result = talib.CCI(self.high, self.low, self.close, n)
        if array:
            return result
        return result[-1]
        
    #----------------------------------------------------------------------
    def atr(self, n, array=False):
        """ATR指标"""
        result = talib.ATR(self.high, self.low, self.close, n)
        if array:
            return result
        return result[-1]
        
    #----------------------------------------------------------------------
    def rsi(self, n, array=False):
        """RSI指标"""
        result = talib.RSI(self.close, n)
        if array:
            return result
        return result[-1]
    
    #----------------------------------------------------------------------
    def macd(self, fastPeriod, slowPeriod, signalPeriod, array=False):
        """MACD指标"""
        macd, signal, hist = talib.MACD(self.close, fastPeriod,
                                        slowPeriod, signalPeriod)
        if array:
            return macd, signal, hist
        return macd[-1], signal[-1], hist[-1]
    
    #----------------------------------------------------------------------
    def adx(self, n, array=False):
        """ADX指标"""
        result = talib.ADX(self.high, self.low, self.close, n)
        if array:
            return result
        return result[-1]
    
    #----------------------------------------------------------------------
    def boll(self, n, dev, array=False):
        """布林通道"""
        mid = self.sma(n, array)
        std = self.std(n, array)
        
        up = mid + std * dev
        down = mid - std * dev
        
        return up, down    
    
    #----------------------------------------------------------------------
    def keltner(self, n, dev, array=False):
        """肯特纳通道"""
        mid = self.sma(n, array)
        atr = self.atr(n, array)
        
        up = mid + atr * dev
        down = mid - atr * dev
        
        return up, down
    
    #----------------------------------------------------------------------
    def donchian(self, n, array=False):
        """唐奇安通道"""
        up = talib.MAX(self.high, n)
        down = talib.MIN(self.low, n)
        
        if array:
            return up, down
        return up[-1], down[-1]

