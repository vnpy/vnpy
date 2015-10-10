# encoding: UTF-8

# 首先写系统内置模块
import sys
print u'demoStrategy.py import sys success'
from datetime import datetime, timedelta, time
print u'demoStrategy.py import datetime.datetime/timedelta/time success'
from time import sleep
print u'demoStrategy.py import time.sleep success'

# 然后是第三方库模块（如PyQt4等）
import sip
print u'demoStrategy.py import sip success'
from PyQt4 import QtCore
print u'demoStrategy.py import PyQt4.QtCore success'

# 然后是自己编写的模块
from demoEngine import MainEngine
print u'demoStrategy.py import demoEngine.MainEngine success'
from strategyEngine import *



########################################################################
class SimpleEmaStrategy(StrategyTemplate):
    """简单双指数移动均线EMA演示策略"""

    #----------------------------------------------------------------------
    def __init__(self, name, symbol, engine):
        """Constructor"""
        super(SimpleEmaStrategy, self).__init__(name, symbol, engine)
        
        # 策略在外部设置的参数
        #self.fastAlpha = 0.2    # 快速EMA的参数
        self.fastAlpha = 0.2
        #self.slowAlpha = 0.05   # 慢速EMA的参数
        self.fastAlpha = 0.05
        
        # 最新TICK数据（市场报价）
        self.currentTick = None
        
        # K线缓存对象
        self.barOpen = 0
        self.barHigh = 0
        self.barLow = 0
        self.barClose = 0
        self.barVolume = 0
        self.barTime = None
        
        # 保存K线数据的列表对象
        self.listOpen = []
        self.listHigh = []
        self.listLow = []
        self.listClose = []
        self.listVolume = []
        self.listTime = []
        
        # 持仓
        self.pos = 0
        
        # 报单代码列表
        self.listOrderRef = []  # 报单号列表
        self.listStopOrder = [] # 停止单对象列表
        
        # EMA均线
        self.fastEMA = 0        # 快速EMA的数值
        self.slowEMA = 0        # 慢速EMA的数值
        
        # 是否完成了初始化
        self.initCompleted = False
        
        # 初始化时读取的历史数据的起始日期(可以选择外部设置)
        self.startDate = None     
        
    #----------------------------------------------------------------------
    def loadSetting(self, setting):
        """读取参数设定"""
        try:
            self.fastAlpha = setting['fastAlpha']
            self.slowAlpha = setting['slowAlpha']
            self.engine.writeLog(self.name + u'读取参数成功')
        except KeyError:
            self.engine.writeLog(self.name + u'读取参数设定出错，请检查参数字典')
        
        try:
            self.initStrategy(setting['startDate'])
        except KeyError:
            self.initStrategy()
        
    #----------------------------------------------------------------------
    def initStrategy(self, startDate=None):
        """初始化"""
        self.engine.writeLog(u'读取3天的历史TICK数据')
        td = timedelta(days=1)

        
        if startDate:
            #读取历史Tick数据
            #cx = self.engine.loadTickFromMongo(self.symbol, startDate-td)
            historyStartDate=self.engine.getMysqlDeltaDate(self.symbol,startDate,3)
            cx = self.engine.loadTickFromMysql(self.symbol, historyStartDate, startDate-td)

        else:
            today = datetime.today().replace(hour=0, minute=0, second=0, microsecond=0)
            #cx = self.engine.loadTickFromMongo(self.symbol, today-td)
            historyStartDate=self.engine.getMysqlDeltaDate(self.symbol,today,3)
            cx = self.engine.loadTickFromMysql(self.symbol, historyStartDate,today-td)

        if cx:
            for data in cx:
                #InstrumentID, UpdateTime, LastPrice, Volume, OpenInterest, BidPrice1, BidVolume1, AskPrice1, AskVolume1 = data

                tick = Tick(data['InstrumentID'])
                #tick = Tick(InstrumentID)

                #tick.openPrice = data['OpenPrice']
                #tick.highPrice = data['HighestPrice']
                #tick.lowPrice = data['LowestPrice']
                tick.lastPrice = float(data['LastPrice'])
                #tick.lastPrice = LastPrice
                
                tick.volume = data['Volume']
                tick.openInterest = data['OpenInterest']
                #tick.volume = Volume
                #tick.openInterest = OpenInterest
                
                #tick.upperLimit = data['UpperLimitPrice']
                #tick.lowerLimit = data['LowerLimitPrice']

                tick.time = data['UpdateTime']
                #tick.ms = data['UpdateMillisec']
                #tick.time = UpdateTime
                
                tick.bidPrice1 =float(data['BidPrice1'])
                #tick.bidPrice2 = data['BidPrice2']
                #tick.bidPrice3 = data['BidPrice3']
                #tick.bidPrice4 = data['BidPrice4']
                #tick.bidPrice5 = data['BidPrice5']
                #tick.bidPrice1 = BidPrice1

                tick.askPrice1 = float(data['AskPrice1'])
                #tick.askPrice2 = data['AskPrice2']
                #tick.askPrice3 = data['AskPrice3']
                #tick.askPrice4 = data['AskPrice4']
                #tick.askPrice5 = data['AskPrice5']
                #tick.askPrice1 = AskPrice1
                
                tick.bidVolume1 = data['BidVolume1']
                #tick.bidVolume2 = data['BidVolume2']
                #tick.bidVolume3 = data['BidVolume3']
                #tick.bidVolume4 = data['BidVolume4']
                #tick.bidVolume5 = data['BidVolume5']
                #tick.bidVolume1 = BidVolume1

                tick.askVolume1 = data['AskVolume1']
                #tick.askVolume2 = data['AskVolume2']
                #tick.askVolume3 = data['AskVolume3']
                #tick.askVolume4 = data['AskVolume4']
                #tick.askVolume5 = data['AskVolume5']
                #tick.askVolume1 = AskVolume1

                self.onTick(tick)
                
        self.initCompleted = True
        
        self.engine.writeLog(self.name + u'初始化完成')
            
    #----------------------------------------------------------------------
    def onTick(self, tick):
        """行情更新"""
        # 保存最新的TICK
        self.currentTick = tick
        
        # 首先生成datetime.time格式的时间（便于比较）
        #ticktime = self.strToTime(tick.time, tick.ms)
        ticktime = tick.time

        # 假设是收到的第一个TICK
        if self.barOpen == 0:
            # 初始化新的K线数据
            self.barOpen = tick.lastPrice
            self.barHigh = tick.lastPrice
            self.barLow = tick.lastPrice
            self.barClose = tick.lastPrice
            self.barVolume = tick.volume
            self.barTime = ticktime
        else:
            # 如果是当前一分钟内的数据
            if ticktime.minute == self.barTime.minute:
                # 汇总TICK生成K线
                self.barHigh = max(self.barHigh, tick.lastPrice)
                self.barLow = min(self.barLow, tick.lastPrice)
                self.barClose = tick.lastPrice
                self.barVolume = self.barVolume + tick.volume
                self.barTime = ticktime                
            # 如果是新一分钟的数据
            else:
                # 首先推送K线数据
                self.onBar(self.barOpen, self.barHigh, self.barLow, self.barClose, 
                           self.barVolume, self.barTime)
                
                # 初始化新的K线数据
                self.barOpen = tick.lastPrice
                self.barHigh = tick.lastPrice
                self.barLow = tick.lastPrice
                self.barClose = tick.lastPrice
                self.barVolume = tick.volume
                self.barTime = ticktime     

    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """交易更新"""
        if trade.direction == DIRECTION_BUY:
            self.pos = self.pos + trade.volume
        else:
            self.pos = self.pos - trade.volume 
            
        log = self.name + u'当前持仓：' + str(self.pos)
        self.engine.writeLog(log)
        
    #----------------------------------------------------------------------
    def onOrder(self, order):
        """报单更新"""
        pass
    
    #----------------------------------------------------------------------
    def onStopOrder(self, orderRef):
        """停止单更新"""
        pass
    
    #----------------------------------------------------------------------
    def onBar(self, o, h, l, c, volume, time):
        """K线数据更新"""
        # 保存K线序列数据
        self.listOpen.append(o)
        self.listHigh.append(h)
        self.listLow.append(l)
        self.listClose.append(c)
        self.listVolume.append(volume)
        self.listTime.append(time)
        
        # 计算EMA
        if self.fastEMA:
            self.fastEMA = c*self.fastAlpha + self.fastEMA*(1-self.fastAlpha)
            self.slowEMA = c*self.slowAlpha + self.slowEMA*(1-self.slowAlpha)
        else:
            self.fastEMA = c
            self.slowEMA = c
        
        # 交易逻辑
        if self.initCompleted:      # 首先检查是否是实盘运行还是数据预处理阶段
            # 快速EMA在慢速EMA上方，做多
            if self.fastEMA > self.slowEMA:
                # 如果当前手头无仓位，则直接做多
                if self.pos == 0:
                    # 涨停价买入开仓
                    # Modified by Incense Lee ：回测时，Tick数据中没有涨停价，只能使用当前价
                    #self.buy(self.currentTick.upperLimit, 1)
                    self.buy(self.currentTick.lastPrice, 1)
                # 手头有空仓，则先平空，再开多
                elif self.pos < 0:
                    #self.cover(self.currentTick.upperLimit, 1)
                    self.cover(self.currentTick.lastPrice, 1)
                    #self.buy(self.currentTick.upperLimit, 1)
                    self.buy(self.currentTick.lastPrice, 1)
            
            # 反之，做空
            elif self.fastEMA < self.slowEMA:
                if self.pos == 0:
                    # Modified by Incense Lee ：回测时，Tick数据中没有最低价价，只能使用当前价
                    #self.short(self.currentTick.lowerLimit, 1)
                    self.short(self.currentTick.lastPrice, 1)
                elif self.pos > 0:
                    #self.sell(self.currentTick.lowerLimit, 1)
                    self.sell(self.currentTick.lastPrice, 1)

                    #self.short(self.currentTick.lowerLimit, 1)
                    self.short(self.currentTick.lastPrice, 1)
        
            # 记录日志
            log = self.name + u'，K线时间：' + str(time) + '\n' + \
                u'，快速EMA：' + str(self.fastEMA) + u'，慢速EMA：' + \
                str(self.slowEMA)
            self.engine.writeLog(log)
            
    #----------------------------------------------------------------------
    def strToTime(self, t, ms):
        """从字符串时间转化为time格式的时间"""
        hh, mm, ss = t.split(':')
        tt = time(int(hh), int(mm), int(ss), microsecond=ms)
        return tt

#----------------------------------------------------------------------
def print_log(event):
    """打印日志"""
    log = event.dict_['log']
    print str(datetime.now()), ':', log
    

#----------------------------------------------------------------------
def main():
    """运行在CMD中的演示程度"""
    # 创建PyQt4应用对象
    app = QtCore.QCoreApplication(sys.argv)
    print u'demoStrategy.py Main call QtCore.QCoreApplication(sys.argv) success'

    # 创建主引擎对象
    me = MainEngine()
    print u'demoStrategy.py Main call MainEngine() success'

    
    # 注册事件监听
    me.ee.register(EVENT_LOG, print_log)
    
    # 登录
    userid = '033513'
    password = 'jiajia'
    brokerid = '9999'
    mdAddress = 'tcp://180.168.146.187:10010'
    tdAddress = 'tcp://180.168.146.187:10000'
    
    me.login(userid, password, brokerid, mdAddress, tdAddress)
    
    # 等待10秒钟（初始化合约数据等）
    sleep(5)
    
    # 创建策略引擎对象
    se = StrategyEngine(me.ee, me)
    
    # 创建策略对象
    setting = {}
    setting['fastAlpha'] = 0.2
    setting['slowAlpha'] = 0.05
    #se.createStrategy(u'EMA演示策略', 'IF1506', SimpleEmaStrategy, setting)
    se.createStrategy(u'EMA演示策略', 'a', SimpleEmaStrategy, setting)
    
    # 启动所有策略
    se.startAll()
    
    # 让程序连续运行
    sys.exit(app.exec_())
    
    
if __name__ == '__main__':
    main()
    
    
    
    
    
    