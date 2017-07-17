# encoding: utf-8

# 重载sys模块，设置默认字符串编码方式为utf8
import sys
reload(sys)
sys.setdefaultencoding('utf8')  

# vn.trader模块
from vnpy.event import EventEngine2
from vnpy.rpc import RpcClient

from vnpy.trader.vtGlobal import globalSetting
from vnpy.trader.vtEngine import MainEngine
from vnpy.trader.uiQt import qApp
from vnpy.trader.uiMainWindow import MainWindow



########################################################################
class VtClient(RpcClient):
    """vn.trader客户端"""

    #----------------------------------------------------------------------
    def __init__(self, reqAddress, subAddress, eventEngine):
        """Constructor"""
        super(VtClient, self).__init__(reqAddress, subAddress)
        
        self.eventEngine = eventEngine
        
        self.usePickle()
        
    #----------------------------------------------------------------------
    def callback(self, topic, data):
        """回调函数"""
        self.eventEngine.put(data)


########################################################################
class ClientEngine(MainEngine):
    """客户端引擎，提供和MainEngine完全相同的API接口"""

    #----------------------------------------------------------------------
    def __init__(self, client, eventEngine):
        """Constructor"""
        super(ClientEngine, self).__init__(eventEngine)
        
        self.client = client
        self.eventEngine = eventEngine
        
        # 扩展模块
        self.ctaEngine = CtaEngine(self, self.eventEngine)
        self.drEngine = DrEngine(self, self.eventEngine)
        self.rmEngine = RmEngine(self, self.eventEngine)
    
    #----------------------------------------------------------------------  
    def connect(self, gatewayName):
        """连接特定名称的接口"""
        self.client.connect(gatewayName)
        
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq, gatewayName):
        """订阅特定接口的行情"""
        self.client.subscribe(subscribeReq, gatewayName)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq, gatewayName):
        """对特定接口发单"""
        return self.client.sendOrder(orderReq, gatewayName)    
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq, gatewayName):
        """对特定接口撤单"""
        self.client.cancelOrder(cancelOrderReq, gatewayName)
        
    #----------------------------------------------------------------------
    def qryAccont(self, gatewayName):
        """查询特定接口的账户"""
        self.client.qryAccount(gatewayName)
        
    #----------------------------------------------------------------------
    def qryPosition(self, gatewayName):
        """查询特定接口的持仓"""
        self.client.qryPosition(gatewayName)
        
    #----------------------------------------------------------------------
    def exit(self):
        """退出程序前调用，保证正常退出"""  
        # 停止事件引擎
        self.eventEngine.stop()      
        
        # 关闭客户端的推送数据接收
        self.client.stop()        

        # 停止数据记录引擎
        self.drEngine.stop()
    
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """快速发出日志事件"""
        self.client.writeLog(content)      
    
    #----------------------------------------------------------------------
    def dbConnect(self):
        """连接MongoDB数据库"""
        self.client.dbConnect()
    
    #----------------------------------------------------------------------
    def dbInsert(self, dbName, collectionName, d):
        """向MongoDB中插入数据，d是具体数据"""
        self.client.dbInsert(dbName, collectionName, d)
    
    #----------------------------------------------------------------------
    def dbQuery(self, dbName, collectionName, d):
        """从MongoDB中读取数据，d是查询要求，返回的是数据库查询的数据列表"""
        return self.client.dbQuery(dbName, collectionName, d)
        
    #----------------------------------------------------------------------
    def dbUpdate(self, dbName, collectionName, d, flt, upsert=False):
        """向MongoDB中更新数据，d是具体数据，flt是过滤条件，upsert代表若无是否要插入"""
        self.client.dbUpdate(dbName, collectionName, d, flt, upsert)
    
    #----------------------------------------------------------------------
    def getContract(self, vtSymbol):
        """查询合约"""
        return self.client.getContract(vtSymbol)
    
    #----------------------------------------------------------------------
    def getAllContracts(self):
        """查询所有合约（返回列表）"""
        return self.client.getAllContracts()
    
    #----------------------------------------------------------------------
    def getOrder(self, vtOrderID):
        """查询委托"""
        return self.client.getOrder(vtOrderID)
    
    #----------------------------------------------------------------------
    def getAllWorkingOrders(self):
        """查询所有的活跃的委托（返回列表）"""
        return self.client.getAllWorkingOrders()
    
    #----------------------------------------------------------------------
    def getAllGatewayDetails(self):
        """查询所有的接口名称"""
        return self.client.getAllGatewayDetails()


#----------------------------------------------------------------------
def main():
    """客户端主程序入口"""
    # 创建事件引擎
    eventEngine = EventEngine2()
    eventEngine.start(timer=False)

    # 创建客户端
    reqAddress = 'tcp://localhost:2014'
    subAddress = 'tcp://localhost:0602'
    client = VtClient(reqAddress, subAddress, eventEngine)

    client.subscribeTopic('')
    client.start()
    
    # 初始化主引擎和主窗口对象
    mainEngine = ClientEngine(client, eventEngine)
    mainWindow = MainWindow(mainEngine, mainEngine.eventEngine)
    mainWindow.showMaximized()
    
    # 在主线程中启动Qt事件循环
    sys.exit(qApp.exec_())


if __name__ == '__main__':
    main()    
    
    