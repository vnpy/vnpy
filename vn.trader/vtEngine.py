# encoding: UTF-8


from eventEngine import *
from ctpGateway import CtpGateway


########################################################################
class MainEngine(object):
    """主引擎"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        # 创建事件引擎
        self.eventEngine = EventEngine()
        self.eventEngine.start()
        
        # 用来保存接口对象的字典
        self.gatewayDict = {}
        
        # 创建我们想要接入的接口对象
        self.addGateway(CtpGateway, 'CTP')
        
    #----------------------------------------------------------------------
    def addGateway(self, gateway, gatewayName=None):
        """创建接口"""
        self.gatewayDict[gatewayName] = gateway(self.eventEngine, gatewayName)
        
    #----------------------------------------------------------------------
    def connect(self, gatewayName):
        """连接特定名称的接口"""
        gateway = self.gatewayDict[gatewayName]
        gateway.connect()
        
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq, gatewayName):
        """订阅特定接口的行情"""
        gateway = self.gatewayDict[gatewayName]
        gateway.subscribe(subscribeReq)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq, gatewayName):
        """对特定接口发单"""
        gateway = self.gatewayDict[gatewayName]
        return gateway.sendOrder(orderReq)
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq, gatewayName):
        """对特定接口撤单"""
        gateway = self.gatewayDict[gatewayName]
        gateway.cancelOrder(cancelOrderReq)
        
    #----------------------------------------------------------------------
    def getAccont(self, gatewayName):
        """查询特定接口的账户"""
        gateway = self.gatewayDict[gatewayName]
        gateway.getAccount()
        
    #----------------------------------------------------------------------
    def getPosition(self, gatewayName):
        """查询特定接口的持仓"""
        gateway = self.gatewayDict[gatewayName]
        gateway.getPosition()
        
    #----------------------------------------------------------------------
    def exit(self):
        """退出程序前调用，保证正常退出"""
        # 停止事件引擎
        self.eventEngine.stop()
        
        # 安全关闭所有接口
        for gateway in self.gatewayDict.values():
            gateway.close()