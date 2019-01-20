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
from queue import Queue
from threading import Thread


from vnpy.trader.vtEvent import *
from vnpy.trader.vtObject import VtTickData
from vnpy.trader.vtGateway import VtSubscribeReq, VtLogData
from vnpy.trader.vtFunction import todayDate,getJsonPath,getShortSymbol
from vnpy.trader.app.ctaStrategy.ctaRenkoBar import CtaRenkoBar
from .drBase import *
from vnpy.trader.setup_logger import setup_logger
from vnpy.trader.data_source import DataSource
########################################################################
class DrEngine(object):
    """数据记录引擎"""
    
    settingFileName = 'DR_setting.json'
    settingFilePath = getJsonPath(settingFileName,__file__)

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

        # Renko K线对象字典
        self.renkoDict = {}

        # 负责执行数据库插入的单独线程相关
        self.active = False                     # 工作状态
        self.queue = Queue()                    # 队列
        self.thread = Thread(target=self.run)   # 线程

        self.logger = None
        self.createLogger()
        # 载入设置，订阅行情
        self.loadSetting()

    def createLogger(self):
        """
        创建日志记录
        :return:
        """
        currentFolder = os.path.abspath(os.path.join(os.getcwd(), 'logs'))
        if os.path.isdir(currentFolder):
            # 如果工作目录下，存在data子目录，就使用data子目录
            path = currentFolder
        else:
            # 否则，使用缺省保存目录 vnpy/trader/app/ctaStrategy/data
            path = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', 'logs'))

        if self.logger is None:
            filename = os.path.abspath(os.path.join(path, 'drEngine'))

            print(u'create logger:{}'.format(filename))
            self.logger = setup_logger(filename=filename, name='drEngine', debug=True)

    #----------------------------------------------------------------------
    def loadSetting(self):
        """载入设置"""
        with open(self.settingFilePath) as f:
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

            if 'renko' in drSetting:
                l = drSetting.get('renko')
                req_set = set()
                for setting in l:
                    # 获取合约，合约短号，renko的高度（多少个跳）
                    vtSymbol = setting.get('vtSymbol',None)
                    if vtSymbol is None:
                        continue
                    short_symbol = getShortSymbol(vtSymbol).upper()
                    height = setting.get('height',5)
                    minDiff = setting.get('minDiff',1)



                    # 获取vtSymbol的多个renkobar列表，添加新的CtaRenkoBar
                    renko_list = self.renkoDict.get(vtSymbol,[])

                    bar_setting = {'name':'{}_{}'.format(vtSymbol,height),
                                   'shortSymbol':short_symbol,
                                   'vtSymbol':vtSymbol,
                                   'minDiff':minDiff,
                                   'height':minDiff*height}
                    renko_bar = CtaRenkoBar(strategy=None,onBarFunc=self.onRenkoBar,setting=bar_setting)
                    renko_list.append(renko_bar)
                    self.renkoDict.update({vtSymbol:renko_list})

                    req = VtSubscribeReq()
                    req.symbol = vtSymbol
                    req_set.add((req,setting.get('gateway',None)))
                # 更新合约的历史数据
                self.add_gap_ticks()

                # 订阅行情
                for req,gw in req_set:
                    self.mainEngine.subscribe(req,gw)

            if 'active' in drSetting:
                d = drSetting['active']
                
                # 注意这里的vtSymbol对于IB和LTS接口，应该后缀.交易所
                for activeSymbol, vtSymbol in d.items():
                    self.activeSymbolDict[vtSymbol] = activeSymbol

            # 启动数据插入线程
            self.start()

            # 注册事件监听
            self.registerEvent()

    # ----------------------------------------------------------------------
    def procecssTickEvent(self, event):
        """处理行情推送"""
        tick = event.dict_['data']
        vtSymbol = tick.vtSymbol

        # 转化Tick格式
        drTick = DrTickData()
        d = drTick.__dict__
        for key in d.keys():
            if key != 'datetime':
                d[key] = tick.__getattribute__(key)
        drTick.datetime = datetime.strptime(' '.join([tick.date, tick.time]), '%Y-%m-%d %H:%M:%S.%f')
        
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
            # 否则继续累加新的K线
            else:                               
                bar.high = max(bar.high, drTick.lastPrice)
                bar.low = min(bar.low, drTick.lastPrice)
                bar.close = drTick.lastPrice            

    #----------------------------------------------------------------------

        # 更新Renko数据
        for renko_bar in self.renkoDict.get(vtSymbol,[]):
           renko_bar.onTick(copy.copy(tick))

    def add_gap_ticks(self):
        """
        补充缺失的分时数据
        :return:
        """
        ds = DataSource()
        for vtSymbol in self.renkoDict.keys():
            renkobar_list = self.renkoDict.get(vtSymbol,[])
            cache_bars = None
            cache_start_date = None
            cache_end_date = None
            for renko_bar in renkobar_list:
                # 通过mongo获取最新一个Renko bar的数据日期close时间
                last_renko_dt = self.get_last_datetime(renko_bar.name)

                # 根据日期+vtSymbol，像datasource获取分钟数据，以close价格，转化为tick，推送到renko_bar中
                if last_renko_dt is not None:
                    start_date =last_renko_dt.strftime('%Y-%m-%d')
                else:
                    start_date = (datetime.now() - timedelta(days=90)).strftime('%Y-%m-%d')

                end_date = (datetime.now() + timedelta(days=5)).strftime('%Y-%m-%d')
                self.writeDrLog(u'从datasource获取{}数据,开始日期:{}'.format(vtSymbol,start_date))
                if cache_bars is None or cache_start_date!=start_date or cache_end_date!=end_date:
                    fields = ['open', 'close', 'high', 'low', 'volume', 'open_interest', 'limit_up', 'limit_down',
                              'trading_date']
                    cache_bars = ds.get_price(order_book_id=vtSymbol,start_date=start_date,end_date=end_date,
                                              frequency='1m', fields=fields)
                    cache_start_date = start_date
                    cache_end_date = end_date
                    if cache_bars is not None:
                        total = len(cache_bars)
                        self.writeDrLog(u'一共获取{}条{} 1分钟数据'.format(total,vtSymbol))

                if cache_bars is not None:
                    self.writeDrLog(u'推送分时数据tick:{}到:{}'.format(vtSymbol,renko_bar.name))
                    for idx in cache_bars.index:
                        row = cache_bars.loc[idx]
                        tick = VtTickData()
                        tick.vtSymbol = vtSymbol
                        tick.symbol = vtSymbol
                        last_bar_dt = datetime.strptime(str(idx), '%Y-%m-%d %H:%M:00')
                        tick.datetime = last_bar_dt - timedelta(minutes=1)
                        tick.date = tick.datetime.strftime('%Y-%m-%d')
                        tick.time = tick.datetime.strftime('%H:%M:00')

                        if tick.datetime.hour >= 21:
                            if tick.datetime.isoweekday() == 5:
                                # 星期五=》星期一
                                tick.tradingDay = (tick.datetime + timedelta(days=3)).strftime('%Y-%m-%d')
                            else:
                                # 第二天
                                tick.tradingDay = (tick.datetime + timedelta(days=1)).strftime('%Y-%m-%d')
                        elif tick.datetime.hour < 8 and tick.datetime.isoweekday() == 6:
                            # 星期六=>星期一
                            tick.tradingDay = (tick.datetime + timedelta(days=2)).strftime('%Y-%m-%d')
                        else:
                            tick.tradingDay = tick.date
                        tick.upperLimit = float(row['limit_up'])
                        tick.lowerLimit = float(row['limit_down'])
                        tick.lastPrice = float(row['close'])
                        tick.askPrice1 = float(row['close'])
                        tick.bidPrice1 = float(row['close'])
                        tick.volume = int(row['volume'])
                        tick.askVolume1 = tick.volume
                        tick.bidVolume1 = tick.volume

                        if last_renko_dt is not None and tick.datetime <= last_renko_dt:
                            continue
                        renko_bar.onTick(tick)

    def get_last_datetime(self,renko_name):
        """
         通过mongo获取最新一个bar的数据日期
        :param renko_name:
        :return:
        """
        qryData = self.mainEngine.dbQueryBySort(dbName=RENKO_DB_NAME,
                                                collectionName=renko_name,
                                                d={},
                                                sortName='datetime',
                                                sortType=-1,
                                                limitNum=1)

        last_renko_open_dt =None
        last_renko_close_dt=None
        for d in qryData:
            last_renko_open_dt = d.get('datetime',None)
            if last_renko_open_dt is not None:
                last_renko_close_dt = last_renko_open_dt + timedelta(seconds=d.get('seconds',0))

            break
        return last_renko_close_dt

    def onRenkoBar(self,bar,bar_name):
        newBar = copy.copy(bar)
        self.insertData(RENKO_DB_NAME, bar_name, newBar)
        self.writeDrLog(u'new Renko Bar:{},dt:{},open:{},close:{},high:{},low:{}'
                        .format(bar_name,bar.datetime,bar.open,bar.close, bar.high, bar.low))

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
            except Exception as ex:
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

        if self.logger:
            self.logger.info(content)
