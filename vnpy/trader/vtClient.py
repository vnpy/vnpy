# encoding: utf-8

print 'load vtClient.py'
import ctypes
import platform
import sys

from vnpy.rpc import RpcClient
from vnpy.trader.app.ctaStrategy.ctaEngine import CtaEngine
from vnpy.trader.app.dataRecorder.drEngine import DrEngine
from vnpy.trader.app.riskManager.rmEngine import RmEngine
from uiMainWindow import *

# 文件路径名
path = os.path.abspath(os.path.dirname(__file__))    
ICON_FILENAME = 'vnpy.ico'
ICON_FILENAME = os.path.join(path, ICON_FILENAME)  

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
class ClientEngine(object):
    """客户端引擎，提供和MainEngine完全相同的API接口"""

    #----------------------------------------------------------------------
    def __init__(self, client, eventEngine):
        """Constructor"""
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

    # ----------------------------------------------------------------------
    def disconnect(self, gatewayName):
        """连接特定名称的接口"""
        self.client.disconnect(gatewayName)

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq, gatewayName):
        """订阅特定接口的行情"""
        self.client.subscribe(subscribeReq, gatewayName)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq, gatewayName):
        """对特定接口发单"""
        self.client.sendOrder(orderReq, gatewayName)    
    
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
    def getAllGatewayNames(self):
        """查询所有的接口名称"""
        return self.client.getAllGatewayNames()

    def getAccountInfo(self):
        """读取风控的账号与仓位数据
        # Added by IncenseLee
        仅支持一个账号。不支持多账号
        以后支持跨市场套利才更新吧。
        """
        return self.rmEngine.getAccountInfo()

    def clearData(self):
        """清空数据引擎的数据"""
        self.dataEngine.clearData()
        self.ctaEngine.clearData()

    def saveData(self):
        self.ctaEngine.saveStrategyData()

#----------------------------------------------------------------------
def main():
    """客户端主程序入口"""
    # 重载sys模块，设置默认字符串编码方式为utf8
    reload(sys)
    sys.setdefaultencoding('utf8')    
    
    # 设置Windows底部任务栏图标
    if 'Windows' in platform.uname() :
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID('vn.trader')    
    
    # 创建事件引擎
    eventEngine = EventEngine()
    eventEngine.start(timer=False)

    # 创建客户端
    reqAddress = 'tcp://localhost:2014'
    subAddress = 'tcp://localhost:2016'
    client = VtClient(reqAddress, subAddress, eventEngine)

    # 这里是订阅所有的publish event，也可以指定。
    client.subscribeTopic('')
    client.start()

    # 初始化Qt应用对象
    app = QtGui.QApplication(sys.argv)
    app.setWindowIcon(QtGui.QIcon(ICON_FILENAME))
    app.setFont(BASIC_FONT)
    
    # 设置Qt的皮肤
    try:
        from vnpy.trader.vtGlobal import globalSetting

        if globalSetting['darkStyle']:
            import qdarkstyle
            app.setStyleSheet(qdarkstyle.load_stylesheet(pyside=False))
    except:
        pass    
    
    # 初始化主引擎和主窗口对象
    mainEngine = ClientEngine(client, eventEngine)
    mainWindow = MainWindow(mainEngine, mainEngine.eventEngine)
    mainWindow.showMaximized()
    
    # 在主线程中启动Qt事件循环
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()    
    
    