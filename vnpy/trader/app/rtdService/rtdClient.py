# encoding: UTF-8

from pyxll import RTD, xl_func, xl_app

from vnpy.rpc import RpcClient


# key为topic.key
DATA_DICT = {}
RTD_DICT = {}


########################################################################
class RtdClient(RpcClient):
    """RTD客户端"""

    #----------------------------------------------------------------------
    def __init__(self, reqAddress, subAddress):
        """Constructor"""
        super(RtdClient, self).__init__(reqAddress, subAddress)
        
        self.useJson()
        
    #----------------------------------------------------------------------
    def callback(self, topic, data):
        """回调函数实现"""
        name = '_'.join([topic, data["key"]])
        DATA_DICT[name] = data
        
        # 检查存在的RTD对象
        rtdList = RTD_DICT.get(name, None)
        if rtdList:
            for rtd in rtdList:
                rtd.update()


########################################################################
class RtdData(RTD):
    """RTD数据"""

    #----------------------------------------------------------------------
    def __init__(self, name, field):
        """Constructor"""
        super(RtdData, self).__init__(value=0)
        
        self.name = name
        self.field = field

    #----------------------------------------------------------------------
    def connect(self):
        """连接成功"""
        l = RTD_DICT.setdefault(self.name, [])
        l.append(self)

    #----------------------------------------------------------------------
    def disconnect(self):
        """连接断开"""
        l = RTD_DICT.get(self.name, None)
        if not l:
            return
        
        if self in l:
            l.remove(self)

    #----------------------------------------------------------------------
    def update(self):
        """更新数据"""
        data = DATA_DICT.get(self.name, None)
        if not data:
            return
        
        newValue = data[self.field]
        if newValue != self.value:
            self.value = newValue


@xl_func("string name, string field: rtd")
#----------------------------------------------------------------------
def rtdData(name, field):
    """获取RTD数据"""
    return RtdData(name, field)


# 连接客户端
reqAddress = 'tcp://localhost:88888'
subAddress = 'tcp://localhost:66666'

c = RtdClient(reqAddress, subAddress)
c.subscribeTopic('')
c.start()
