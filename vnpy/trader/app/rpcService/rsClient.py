# encoding: UTF-8

import copy

from vnpy.rpc import RpcClient


########################################################################
class AttributeProxy(object):
    """属性代理"""

    #----------------------------------------------------------------------
    def __init__(self, nameList, client):
        """Constructor"""
        self.nameList = nameList    # 属性名称关系列表
        self.client = client        # RPC客户端
        
    #----------------------------------------------------------------------
    def __getattr__(self, name):
        """获取某个不存在的属性"""
        # 生成属性层级列表
        newNameList = copy.copy(self.nameList)
        newNameList.append(name)
        
        # 创建代理对象
        proxy = AttributeProxy(newNameList, self.client)
        
        # 缓存代理对象
        self.__dict__[name] = proxy
        
        # 返回
        return proxy
        
    #----------------------------------------------------------------------
    def __call__(self, *args, **kwargs):
        """被当做函数调用时"""
        d = {}
        d['nameList'] = self.nameList
        d['args'] = args
        d['kwargs'] = kwargs
        return self.client.call(d)    
    

########################################################################
class RsClient(RpcClient):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, reqAddress, subAddress):
        """Constructor"""
        super(RsClient, self).__init__(reqAddress, subAddress)
        
        self.eventEngine = None
        
    #----------------------------------------------------------------------
    def callback(self, topic, data):
        """"""
        self.eventEngine.put(data)
    
    #----------------------------------------------------------------------
    def init(self, eventEngine):
        """"""
        self.eventEngine = eventEngine
        
        self.usePickle()
        self.subscribeTopic('')
        self.start()


########################################################################
class MainEngineProxy(object):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine):
        """Constructor"""
        self.eventEngine = eventEngine
        self.eventEngine.start(timer=False)
        
        self.client = None
        
    #----------------------------------------------------------------------
    def init(self, reqAddress, subAddress):
        """"""
        self.client = RsClient(reqAddress, subAddress)
        self.client.init(self.eventEngine)

    #----------------------------------------------------------------------
    def __getattr__(self, name):
        """"""
        # 生成属性名称层级列表
        nameList = [name]
        
        # 生成属性代理对象
        proxy = AttributeProxy(nameList, self.client)
        
        # 缓存属性代理对象，使得后续调用无需新建
        self.__dict__[name] = proxy
        
        # 返回属性代理
        return proxy
    