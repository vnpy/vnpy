# encoding: UTF-8

import json

from vnpy.event import Event
from vnpy.rpc import RpcServer
from vnpy.trader.vtFunction import getJsonPath
from vnpy.trader.vtObject import VtLogData


EVENT_RTDSERVICE_LOG = 'eRtdServiceLog'


########################################################################
class RtdServer(RpcServer):
    """RTD服务器，直接继承RPC服务"""

    #----------------------------------------------------------------------
    def __init__(self, repAddress, pubAddress):
        """Constructor"""
        super(RtdServer, self).__init__(repAddress, pubAddress)    
        
        self.useJson()
    

#################################################5#######################
class RtdEngine(object):
    """RTD引擎"""
    ENGINE_NAME = 'RTD'
    
    settingFileName = 'RTD_setting.json'
    settingfilePath = getJsonPath(settingFileName, __file__) 

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        self.server = None
        self.eventTypeDict = {}     # key：事件类型，value：键
        
        self.loadSetting()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def loadSetting(self):
        """读取配置"""
        with open(self.settingfilePath) as f:
            d = json.load(f)
            
            repAddress = d['repAddress']
            pubAddress = d['pubAddress']
            
            self.server = RtdServer(repAddress, pubAddress)
            
            self.eventTypeDict = d['eventType']
        
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        for eventType in self.eventTypeDict.keys():
            self.eventEngine.register(eventType, self.processDataEvent)
        
    #----------------------------------------------------------------------
    def processDataEvent(self, event):
        """处理数据事件"""
        if not self.server:
            return
        
        data = event.dict_['data']
        d = data.__dict__
        keyname = self.eventTypeDict[event.type_]   # 获取数据标识用的名称
        d["key"] = d[keyname]
        
        self.server.publish(event.type_, d)
        
        self.writeLog(u'发布数据，类型%s，内容%s' %(event.type_, str(d)))
        
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """记录日志"""
        log = VtLogData()
        log.logContent = content
        log.gatewayName = self.ENGINE_NAME
        
        event = Event(EVENT_RTDSERVICE_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)
        
    #----------------------------------------------------------------------
    def stop(self):
        """停止"""
        pass
        

    
    