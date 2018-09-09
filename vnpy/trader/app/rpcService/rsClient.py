# encoding: UTF-8

import copy

from vnpy.rpc import RpcClient


########################################################################
class ObjectProxy(object):
    """对象代理"""

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
        proxy = ObjectProxy(newNameList, self.client)
        
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
    """RPC服务客户端"""

    #----------------------------------------------------------------------
    def __init__(self, reqAddress, subAddress):
        """Constructor"""
        super(RsClient, self).__init__(reqAddress, subAddress)
        
        self.eventEngine = None
        
    #----------------------------------------------------------------------
    def callback(self, topic, data):
        """事件推送回调函数"""
        self.eventEngine.put(data)      # 直接放入事件引擎中
    
    #----------------------------------------------------------------------
    def init(self, eventEngine):
        """初始化"""
        self.eventEngine = eventEngine  # 绑定事件引擎对象
        
        self.usePickle()                # 使用cPickle序列化
        self.subscribeTopic('')         # 订阅全部主题推送
        self.start()                    # 启动


########################################################################
class MainEngineProxy(object):
    """主引擎代理"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine):
        """Constructor"""
        self.eventEngine = eventEngine
        self.eventEngine.start(timer=False)     # 客户端不启动定时器
        
        self.client = None
        
    #----------------------------------------------------------------------
    def init(self, reqAddress, subAddress):
        """初始化"""
        self.client = RsClient(reqAddress, subAddress)
        self.client.init(self.eventEngine)

    #----------------------------------------------------------------------
    def __getattr__(self, name):
        """获取未知属性"""
        # 生成属性名称层级列表
        nameList = [name]
        
        # 生成属性代理对象
        proxy = ObjectProxy(nameList, self.client)
        
        # 缓存属性代理对象，使得后续调用无需新建
        self.__dict__[name] = proxy
        
        # 返回属性代理
        return proxy
    
    #----------------------------------------------------------------------
    def getApp(self, name):
        """获取应用引擎对象"""
        return self.__getattr__(name)
    
    #----------------------------------------------------------------------
    def exit(self):
        self.eventEngine.stop()
        
        if self.client:
            self.client.stop()  
