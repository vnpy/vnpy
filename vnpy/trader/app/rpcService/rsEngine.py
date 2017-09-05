# encoding: UTF-8

import json

from vnpy.trader.vtConstant import EMPTY_STRING

from vnpy.rpc import RpcServer
from vnpy.trader.vtFunction import getJsonPath


########################################################################
class RsEngine(object):
    """RPC服务引擎"""
    
    settingFileName = 'RS_setting.json'
    settingFilePath = getJsonPath(settingFileName, __file__)    
    
    name = u'RPC服务'

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        self.server = None                  # RPC服务对象
        self.repAddress = EMPTY_STRING      # REP地址
        self.pubAddress = EMPTY_STRING      # PUB地址
        
        self.functionDict = {}              # 调用过的函数对象缓存字典
        
        self.loadSetting()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def loadSetting(self):
        """读取配置"""
        with open(self.settingFilePath) as f:
            d = json.load(f)
            
            self.repAddress = d['repAddress']
            self.pubAddress = d['pubAddress']
            
            self.server = RpcServer(self.repAddress, self.pubAddress)
            self.server.usePickle()
            self.server.register(self.call)
            self.server.start()
            
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.registerGeneralHandler(self.processEvent)
        
    #----------------------------------------------------------------------
    def call(self, d):
        """调用函数"""
        nameList = d['nameList']        # 对象属性列表
        nameTuple = tuple(nameList)     # 转化为元组
        args = d['args']                # 调用参数
        kwargs = d['kwargs']
        
        # 如果已经有缓存，则直接调用
        if nameTuple in self.functionDict:
            function = self.functionDict[nameTuple]
            result = function(*args, **kwargs)
            return result
        # 逐层寻找函数对象
        else:
            # 根对象为主引擎
            obj = self.mainEngine
            
            # 逐层寻找对象属性
            for name in nameTuple:
                obj = obj.__getattribute__(name)
            
            # 缓存结果
            self.functionDict[nameTuple] = obj
            
            # 调用最终对象
            result = obj(*args, **kwargs)
            return result
        
    #----------------------------------------------------------------------
    def processEvent(self, event):
        """处理事件推送"""
        self.server.publish('', event)
    
    #----------------------------------------------------------------------
    def stop(self):
        """停止"""
        self.server.stop()
        
    