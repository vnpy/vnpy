# encoding: UTF-8

'''
本文件中实现了行情数据记录引擎，用于汇总TICK数据，并生成K线插入数据库。

使用DR_setting.json来配置需要收集的合约，以及主力合约代码。
'''

import json
import os
import copy
from collections import OrderedDict
from datetime import datetime, timedelta
from Queue import Queue
from threading import Thread

from eventEngine import *
from vtGateway import VtSubscribeReq, VtLogData
from drBase import *
from vtFunction import todayDate

import tushare as ts
ts.set_token('ced15aa738976abf2136cc9e197fbcd34776e0f8183c7660b7fdcd626a715b3b')    # paolo
import time

########################################################################
class DrEngine(object):
    """数据记录引擎"""
    
    settingFileName = 'DR_setting.json'
    settingFileName = os.getcwd() + '/dataRecorderAlone/' + settingFileName

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine

        # 是否登录CTP
        self.ctpConnected = False
        # 数据库客户端
        self.dbClient = None
        # 主力合约检查
        self.contractsOK = False

        # 期货账号
        self.userID = ''

        # 当前日期
        self.today = todayDate()
        
        # 主力合约代码映射字典，key为具体的合约代码（如IF1604），value为主力合约代码（如IF0000）
        self.activeSymbolDict = {}
        
        # Tick对象字典
        self.tickDict = {}
        
        # K线对象字典
        self.barDict = {}

        # 负责执行数据库插入的单独线程相关
        self.active = False                     # 工作状态
        self.queue = Queue()                    # 队列
        self.thread = Thread(target=self.run)   # 线程

        # # 载入设置，订阅行情
        # self.loadSetting()
        
    #----------------------------------------------------------------------
    def loadSetting(self):
        """载入设置"""
        with open(self.settingFileName) as f:
            drSetting = json.load(f)
            
            # 如果working设为False则不启动行情记录功能
            working = drSetting['working']
            if not working:
                return
            
            if 'tick' in drSetting:
                l = drSetting['tick']
                
                for setting in l:
                    symbol = setting[0]
                    vtSymbol = symbol

                    req = VtSubscribeReq()
                    req.symbol = setting[0]
                    
                    # 针对LTS和IB接口，订阅行情需要交易所代码
                    if len(setting)>=3:
                        req.exchange = setting[2]
                        vtSymbol = '.'.join([symbol, req.exchange])
                    
                    # 针对IB接口，订阅行情需要货币和产品类型
                    if len(setting)>=5:
                        req.currency = setting[3]
                        req.productClass = setting[4]
                    
                    self.mainEngine.subscribe(req, setting[1])
                    
                    drTick = DrTickData()           # 该tick实例可以用于缓存部分数据（目前未使用）
                    self.tickDict[vtSymbol] = drTick
                    
            if 'bar' in drSetting:
                l = drSetting['bar']
                
                for setting in l:
                    symbol = setting[0]
                    vtSymbol = symbol
                    
                    req = VtSubscribeReq()
                    req.symbol = symbol                    

                    if len(setting)>=3:
                        req.exchange = setting[2]
                        vtSymbol = '.'.join([symbol, req.exchange])

                    if len(setting)>=5:
                        req.currency = setting[3]
                        req.productClass = setting[4]                    
                    
                    self.mainEngine.subscribe(req, setting[1])  
                    
                    bar = DrBarData() 
                    self.barDict[vtSymbol] = bar
                    
            if 'active' in drSetting:
                d = drSetting['active']
                
                # 注意这里的vtSymbol对于IB和LTS接口，应该后缀.交易所
                for activeSymbol, vtSymbol in d.items():
                    self.activeSymbolDict[vtSymbol] = activeSymbol

            # 改为由widget中的按钮新建县成
            # # 启动数据插入线程
            # self.start()

            # 注册事件监听
            self.registerEvent()

    #----------------------------------------------------------------------
    def procecssTickEvent(self, event):
        """处理行情推送"""

        tick = event.dict_['data']
        vtSymbol = tick.vtSymbol

        # 过滤非交易时段tick（粗略过滤，不具体区分不同合约的不同交易时间）
        # http://99qh.fx168.com/cj/industry/1604/1861578.shtml
        if ('15:00:00' < tick.time < '21:00:00') or ('02:30:00' < tick.time < '09:00:00') or ('11:30:00' < tick.time < '13:00:00'):
            return
        # 非交易时段启动
        localtime = time.strftime('%H:%M:%S',time.localtime())
        if ('15:05:00' < localtime < '20:55:00') or ('02:35:00' < localtime < '08:55:00') or ('11:35:00' < localtime < '12:55:00'):
            return
        # 转化Tick格式
        drTick = DrTickData()
        d = drTick.__dict__
        for key in d.keys():
            if key != 'datetime':
                d[key] = tick.__getattribute__(key)
        drTick.datetime = datetime.strptime(' '.join([tick.date, tick.time]), '%Y%m%d %H:%M:%S.%f')            
        
        # 更新Tick数据
        if vtSymbol in self.tickDict:
            self.insertData(TICK_DB_NAME, vtSymbol, drTick)
            
            if vtSymbol in self.activeSymbolDict:
                activeSymbol = self.activeSymbolDict[vtSymbol]
                self.insertData(TICK_DB_NAME, activeSymbol, drTick)
            
            # 发出日志
            self.writeDrLog(u'记录Tick数据%s，时间:%s, last:%s, bid:%s, ask:%s' 
                            %(drTick.vtSymbol, drTick.time, drTick.lastPrice, drTick.bidPrice1, drTick.askPrice1))
            
        # 更新分钟线数据

        if vtSymbol in self.barDict:
            bar = self.barDict[vtSymbol]
            
            # 如果第一个TICK或者新的一分钟
            if not bar.datetime or bar.datetime.minute != drTick.datetime.minute:    
                if bar.vtSymbol:
                    newBar = copy.copy(bar)
                    self.insertData(MINUTE_DB_NAME, vtSymbol, newBar)
                    
                    if vtSymbol in self.activeSymbolDict:
                        activeSymbol = self.activeSymbolDict[vtSymbol]
                        self.insertData(MINUTE_DB_NAME, activeSymbol, newBar)                    
                    
                    self.writeDrLog(u'记录分钟线数据%s，时间:%s, O:%s, H:%s, L:%s, C:%s' 
                                    %(bar.vtSymbol, bar.time, bar.open, bar.high, 
                                      bar.low, bar.close))
                         
                bar.vtSymbol = drTick.vtSymbol
                bar.symbol = drTick.symbol
                bar.exchange = drTick.exchange
                
                bar.open = drTick.lastPrice
                bar.high = drTick.lastPrice
                bar.low = drTick.lastPrice
                bar.close = drTick.lastPrice
                
                bar.date = drTick.date
                bar.time = drTick.time
                bar.datetime = drTick.datetime
                bar.volume = drTick.volume
                bar.openInterest = drTick.openInterest

                bar.openPrice = drTick.openPrice            # 今日开盘价
                bar.highPrice = drTick.highPrice            # 今日最高价
                bar.lowPrice = drTick.lowPrice             # 今日最低价
                bar.preClosePrice = drTick.preClosePrice

            # 否则继续累加新的K线
            else:                               
                bar.high = max(bar.high, drTick.lastPrice)
                bar.low = min(bar.low, drTick.lastPrice)
                bar.close = drTick.lastPrice            

    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_TICK, self.procecssTickEvent)
 
    #----------------------------------------------------------------------
    def insertData(self, dbName, collectionName, data):
        """插入数据到数据库（这里的data可以是CtaTickData或者CtaBarData）"""
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
        self.writeDrLog(u'启动数据引擎成功')

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
    #----------------------------------------------------------------------
    def ctpConnect(self):
        # 登录CTP
        self.mainEngine.connect('CTP')
        # 需要等待1秒，否则会登录成功之前就执行完下述判断
        time.sleep(1)
        self.userID = self.mainEngine.gatewayDict['CTP'].mdApi.userID
        if self.mainEngine.gatewayDict['CTP'].tdConnected == True:
            self.ctpConnected = True
            self.writeDrLog(u'CTP登录成功。账号："%s"' % self.userID)
        else:
            self.writeDrLog(u'CTP登录失败。账号："%s"' % self.userID)
    #----------------------------------------------------------------------
    def startAll(self):
        if self.ctpConnected is False:
            self.writeDrLog(u'未登录CTP, 期货Tick 订阅失败')
            return
        if self.dbClient is None:
            self.writeDrLog(u'未连接数据库, 期货Tick 订阅失败')
            return
        if self.active == False:
            self.writeDrLog(u'未启动数据引擎, 期货Tick 订阅失败')
            return
        # 订阅合约
        self.loadSetting()
        self.writeDrLog(u'期货Tick 订阅成功')
    #----------------------------------------------------------------------
    def stopAll(self):
        # 取消订阅
        self.eventEngine.unregister(EVENT_TICK, self.procecssTickEvent)
        # 停止数据记录引擎
        self.writeDrLog(u'期货Tick 取消订阅')

    #----------------------------------------------------------------------
    def dbConnect(self):
        # 连接数据库
        self.mainEngine.dbConnect()
        self.dbClient = self.mainEngine.dbClient
        if self.dbClient:
            self.writeDrLog(u'MongoDB连接成功')
        else:
            self.writeDrLog(u'MongoDB连接失败')
    #----------------------------------------------------------------------
    def contractsInit(self):
        """判断期货主力合约"""

        # 获取上个交易日lastDate
        todayDate = time.strftime('%Y-%m-%d',time.localtime())
        mt = ts.Master()
        Cal = mt.TradeCal(exchangeCD='XSGE',beginDate=''.join(todayDate.split('-')),endDate=''.join(todayDate.split('-')),field='')
        lastDate = Cal.at[0, 'prevTradeDate']
        lastDate = ''.join(lastDate.split('-'))

        # 获取主力合约
        st = ts.Market()
        with open(self.settingFileName) as f:
            drSetting = json.load(f)

            self.contractsOK = True

            if 'tick' in drSetting:
                l = drSetting['tick']

                for setting in l:
                    if setting[1] != 'CTP':
                        continue
                    contract = filter(str.isalpha, str(setting[0]))

                    data = st.MktMFutd(tradeDate=lastDate,contractObject=contract,field='ticker,mainCon,turnoverVol')
                    # 通联持仓主力
                    ticker1 = data[data['mainCon'] == 1].iloc[0]['ticker']
                    # 昨日成交量主力
                    ticker2 = data.at[data['turnoverVol'].argmax(), 'ticker']
                    # print ticker1, ticker2
                    # continue
                    # 当成交量主力于持仓主力不一致时，输出信息
                    if setting[0] != ticker1 or setting[0] != ticker2:
                        self.contractsOK = False
                        self.writeDrLog(u'期货 %s: 请确认主力合约(默认使用成交量):\n                    %s -当前选定主力\n                    %s -通联持仓主力\n                    %s -昨日成交量主力' % (contract, setting[0], ticker1, ticker2))
                        print (u'期货 %s: 请确认主力合约(默认使用成交量):\n                    %s -当前选定主力\n                    %s -通联持仓主力\n                    %s -昨日成交量主力' % (contract, setting[0], ticker1, ticker2))
                        print data
        if self.contractsOK == False:
            self.writeDrLog(u'请检查主力合约是否正确!(非强制)')
        else:
            self.writeDrLog(u'合约初始化成功!')