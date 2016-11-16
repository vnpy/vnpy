# -*- coding: utf-8 -*-

"""
本文件中实现了行情数据记录引擎，用于汇总TICK数据，并生成K线插入数据库。

使用DR_setting.json来配置需要收集的合约，以及主力合约代码。
"""

import copy
import json

from datetime import datetime

from drBase import *
from vnpy.event.eventEngine import *
from vnpy.utils.vtFunction import todayDate, findConfPath
from vnpy.utils.vtGateway import VtSubscribeReq, VtLogData


########################################################################
class DrEngine(object):
    """数据记录引擎"""

    settingFileName = findConfPath('DR_setting.json')

    # ----------------------------------------------------------------------
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

        # 负责执行数据库插入的单独线程相关
        self.active = False  # 工作状态
        self.queue = Queue()  # 队列
        self.thread = Thread(target=self.run)  # 线程

        # 载入设置，订阅行情
        self.loadSetting()

    # ----------------------------------------------------------------------
    def loadSetting(self):
        """载入设置"""
        with open(self.settingFileName) as f:
            dr_setting = json.load(f)

            # 如果working设为False则不启动行情记录功能
            working = dr_setting['working']
            if not working:
                return

            if 'tick' in dr_setting:
                l = dr_setting['tick']

                for setting in l:
                    symbol = setting[0]
                    vt_symbol = symbol

                    req = VtSubscribeReq()
                    req.symbol = setting[0]

                    # 针对LTS和IB接口，订阅行情需要交易所代码
                    if len(setting) >= 3:
                        req.exchange = setting[2]
                        vt_symbol = '.'.join([symbol, req.exchange])

                    # 针对IB接口，订阅行情需要货币和产品类型
                    if len(setting) >= 5:
                        req.currency = setting[3]
                        req.productClass = setting[4]

                    self.mainEngine.subscribe(req, setting[1])

                    dr_tick = DrTickData()  # 该tick实例可以用于缓存部分数据（目前未使用）
                    self.tickDict[vt_symbol] = dr_tick

            if 'bar' in dr_setting:
                l = dr_setting['bar']

                for setting in l:
                    symbol = setting[0]
                    vt_symbol = symbol

                    req = VtSubscribeReq()
                    req.symbol = symbol

                    if len(setting) >= 3:
                        req.exchange = setting[2]
                        vt_symbol = '.'.join([symbol, req.exchange])

                    if len(setting) >= 5:
                        req.currency = setting[3]
                        req.productClass = setting[4]

                    self.mainEngine.subscribe(req, setting[1])

                    bar = DrBarData()
                    self.barDict[vt_symbol] = bar

            if 'active' in dr_setting:
                d = dr_setting['active']

                # 注意这里的vtSymbol对于IB和LTS接口，应该后缀.交易所
                for activeSymbol, vt_symbol in d.items():
                    self.activeSymbolDict[vt_symbol] = activeSymbol

            # 启动数据插入线程
            self.start()

            # 注册事件监听
            self.registerEvent()

            # ----------------------------------------------------------------------

    def procecssTickEvent(self, event):
        """处理行情推送"""
        tick = event.dict_['data']
        vt_symbol = tick.vtSymbol

        # 转化Tick格式
        dr_tick = DrTickData()
        d = dr_tick.__dict__
        for key in d.keys():
            if key != 'datetime':
                d[key] = tick.__getattribute__(key)
        dr_tick.datetime = datetime.strptime(' '.join([tick.date, tick.time]), '%Y%m%d %H:%M:%S.%f')

        # 更新Tick数据
        if vt_symbol in self.tickDict:
            self.insertData(TICK_DB_NAME, vt_symbol, dr_tick)

            if vt_symbol in self.activeSymbolDict:
                active_symbol = self.activeSymbolDict[vt_symbol]
                self.insertData(TICK_DB_NAME, active_symbol, dr_tick)

            # 发出日志
            self.writeDrLog(u'记录Tick数据%s，时间:%s, last:%s, bid:%s, ask:%s'
                            % (dr_tick.vtSymbol, dr_tick.time, dr_tick.lastPrice, dr_tick.bidPrice1, dr_tick.askPrice1))

        # 更新分钟线数据
        if vt_symbol in self.barDict:
            bar = self.barDict[vt_symbol]

            # 如果第一个TICK或者新的一分钟
            if not bar.datetime or bar.datetime.minute != dr_tick.datetime.minute:
                if bar.vtSymbol:
                    new_bar = copy.copy(bar)
                    self.insertData(MINUTE_DB_NAME, vt_symbol, new_bar)

                    if vt_symbol in self.activeSymbolDict:
                        active_symbol = self.activeSymbolDict[vt_symbol]
                        self.insertData(MINUTE_DB_NAME, active_symbol, new_bar)

                    self.writeDrLog(u'记录分钟线数据%s，时间:%s, O:%s, H:%s, L:%s, C:%s'
                                    % (bar.vtSymbol, bar.time, bar.open, bar.high,
                                       bar.low, bar.close))

                bar.vtSymbol = dr_tick.vtSymbol
                bar.symbol = dr_tick.symbol
                bar.exchange = dr_tick.exchange

                bar.open = dr_tick.lastPrice
                bar.high = dr_tick.lastPrice
                bar.low = dr_tick.lastPrice
                bar.close = dr_tick.lastPrice

                bar.date = dr_tick.date
                bar.time = dr_tick.time
                bar.datetime = dr_tick.datetime
                bar.volume = dr_tick.volume
                bar.openInterest = dr_tick.openInterest
                # 否则继续累加新的K线
            else:
                bar.high = max(bar.high, dr_tick.lastPrice)
                bar.low = min(bar.low, dr_tick.lastPrice)
                bar.close = dr_tick.lastPrice

    # ----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_TICK, self.procecssTickEvent)

    # ----------------------------------------------------------------------
    def insertData(self, dbName, collectionName, data):
        """插入数据到数据库（这里的data可以是CtaTickData或者CtaBarData）"""
        self.queue.put((dbName, collectionName, data.__dict__))

    # ----------------------------------------------------------------------
    def run(self):
        """运行插入线程"""
        while self.active:
            try:
                db_name, collection_name, d = self.queue.get(block=True, timeout=1)
                self.mainEngine.dbInsert(db_name, collection_name, d)
            except Empty:
                pass

    # ----------------------------------------------------------------------
    def start(self):
        """启动"""
        self.active = True
        self.thread.start()

    # ----------------------------------------------------------------------
    def stop(self):
        """退出"""
        if self.active:
            self.active = False
            self.thread.join()

    # ----------------------------------------------------------------------
    def writeDrLog(self, content):
        """快速发出日志事件"""
        log = VtLogData()
        log.logContent = content
        event = Event(type_=EVENT_DATARECORDER_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)
