# encoding: UTF-8

"""
该文件中包含的是交易平台的中间层，
将API和事件引擎包装到一个主引擎类中，便于管理。

当客户想采用服务器-客户机模式，实现交易功能放在托管机房，
而图形控制功能在本地电脑时，该主引擎负责实现远程通讯。
"""

import sys
from datetime import date
from time import sleep
import shelve

from PyQt4 import QtCore

from demoApi import *
from eventEngine import EventEngine


########################################################################
class MainEngine:
    """主引擎，负责对API的调度"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.ee = EventEngine()         # 创建事件驱动引擎
        
        self.md = DemoMdApi(self.ee)    # 创建API接口
        self.td = DemoTdApi(self.ee)
        
        self.ee.start()                 # 启动事件驱动引擎
        
        # 循环查询持仓和账户相关
        self.countGet = 0               # 查询延时计数
        self.lastGet = 'Account'        # 上次查询的性质
        self.ee.register(EVENT_TDLOGIN, self.initGet)  # 登录成功后开始初始化查询
        
        # 合约储存相关
        self.dictInstrument = {}        # 字典（保存合约查询数据）
        self.ee.register(EVENT_INSTRUMENT, self.insertInstrument)
        
    #----------------------------------------------------------------------
    def login(self, userid, password, brokerid, mdAddress, tdAddress):
        """登陆"""
        self.md.login(mdAddress, userid, password, brokerid)
        self.td.login(tdAddress, userid, password, brokerid)
    
    #----------------------------------------------------------------------
    def subscribe(self, instrumentid, exchangeid):
        """订阅合约"""
        self.md.subscribe(instrumentid, exchangeid)
        
    #----------------------------------------------------------------------
    def getAccount(self):
        """查询账户"""
        self.td.getAccount()
        
    #----------------------------------------------------------------------
    def getInvestor(self):
        """查询投资者"""
        self.td.getInvestor()
        
    #----------------------------------------------------------------------
    def getPosition(self):
        """查询持仓"""
        self.td.getPosition()
    
    #----------------------------------------------------------------------
    def getInstrument(self):
        """获取合约"""
        event = Event(type_=EVENT_LOG)
        log = u'查询合约信息'
        event.dict_['log'] = log
        self.ee.put(event)          
        
        self.td.getInstrument()
        
    #----------------------------------------------------------------------
    def sendOrder(self, instrumentid, exchangeid, price, pricetype, volume, direction, offset):
        """发单"""
        self.td.sendOrder(instrumentid, exchangeid, price, pricetype, volume, direction, offset)
        
    #----------------------------------------------------------------------
    def cancelOrder(self, instrumentid, exchangeid, orderref, frontid, sessionid):
        """撤单"""
        self.td.cancelOrder(instrumentid, exchangeid, orderref, frontid, sessionid)
        
    #----------------------------------------------------------------------
    def getAccountPosition(self, event):
        """循环查询账户和持仓"""
        self.countGet = self.countGet + 1
        
        # 每5秒发一次查询
        if self.countGet > 5:
            self.countGet = 0   # 清空计数
            
            if self.lastGet == 'Account':
                self.getPosition()
                self.lastGet = 'Position'
            else:
                self.getAccount()
                self.lastGet = 'Account'
    
    #----------------------------------------------------------------------
    def initGet(self, event):
        """在交易服务器登录成功后，开始初始化查询"""
        # 打开设定文件setting.vn
        f = shelve.open('setting.vn')
        
        # 尝试读取设定字典，若该字典不存在，则发出查询请求
        try:
            d = f['instrument']
            
            # 如果本地保存的合约数据是今日的，则载入，否则发出查询请求
            today = date.today()
            if d['date'] == today:
                self.dictInstrument = d['dictInstrument']
                
                event = Event(type_=EVENT_LOG)
                log = u'合约信息读取完成'
                event.dict_['log'] = log
                self.ee.put(event)            
    
                self.getInvestor()
                
                # 开始循环查询
                self.ee.register(EVENT_TIMER, self.getAccountPosition)                 
            else:
                self.getInstrument()
        except KeyError:
            self.getInstrument()
            
        f.close()
 
    #----------------------------------------------------------------------
    def insertInstrument(self, event):
        """插入合约对象"""
        data = event.dict_['data']
        last = event.dict_['last']
        
        self.dictInstrument[data['InstrumentID']] = data
        
        # 合约对象查询完成后，查询投资者信息并开始循环查询
        if last:
            # 将查询完成的合约信息保存到本地文件，今日登录可直接使用不再查询
            self.saveInstrument()
            
            event = Event(type_=EVENT_LOG)
            log = u'合约信息查询完成'
            event.dict_['log'] = log
            self.ee.put(event)            

            self.getInvestor()
            
            # 开始循环查询
            self.ee.register(EVENT_TIMER, self.getAccountPosition)              
        
    #----------------------------------------------------------------------
    def selectInstrument(self, instrumentid):
        """获取合约信息对象"""
        try:
            instrument = self.dictInstrument[instrumentid]
        except KeyError:
            instrument = None
        return instrument
    
    #----------------------------------------------------------------------
    def exit(self):
        """退出"""
        # 销毁API对象
        self.td = None
        self.md = None
        
        # 停止事件驱动引擎
        self.ee.stop()
        
    #----------------------------------------------------------------------
    def saveInstrument(self):
        """保存合约属性数据"""
        f = shelve.open('setting.vn')
        d = {}
        d['dictInstrument'] = self.dictInstrument
        d['date'] = date.today()
        f['instrument'] = d
        f.close()