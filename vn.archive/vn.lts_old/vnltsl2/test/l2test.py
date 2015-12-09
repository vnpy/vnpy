# encoding: UTF-8

import sys
from time import sleep

from PyQt4 import QtGui

from vnltsl2 import *


#----------------------------------------------------------------------
def print_dict(d):
    """按照键值打印一个字典"""
    for key,value in d.items():
        print key + ':' + str(value)
        
        
#----------------------------------------------------------------------
def simple_log(func):
    """简单装饰器用于输出函数名"""
    def wrapper(*args, **kw):
        print ""
        print str(func.__name__)
        return func(*args, **kw)
    return wrapper


########################################################################
class TestL2MdApi(L2MdApi):
    """测试用实例"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(TestL2MdApi, self).__init__()
        self.brokerID = None
        self.userID = None
        
    #----------------------------------------------------------------------
    @simple_log    
    def onFrontConnected(self):
        """服务器连接"""
        pass
    
    #----------------------------------------------------------------------
    @simple_log    
    def onFrontDisconnected(self, n):
        """服务器断开"""
        print n
        
    #----------------------------------------------------------------------
    @simple_log    
    def onHeartBeatWarning(self, n):
        """心跳报警"""
        print n
    
    #----------------------------------------------------------------------
    @simple_log    
    def onRspError(self, error, n, last):
        """错误"""
        print_dict(error)
    
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        self.brokerID = data['BrokerID']
        self.userID = data['UserID']
        print_dict(data)
        print_dict(error)
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        print_dict(data)
        print_dict(error)
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRspSubL2MarketData(self, data, error, n, last):
        """订阅L2合约回报"""
        print_dict(data)
        print_dict(error)
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRspUnSubL2MarketData(self, data, error, n, last):
        """退订L2合约回报"""
        print_dict(data)
        print_dict(error)    
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRspSubL2Index(self, data, error, n, last):
        """订阅L2指数回报"""
        print_dict(data)
        print_dict(error)
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRspUnSubL2Index(self, data, error, n, last):
        """退订L2指数回报"""
        print_dict(data)
        print_dict(error)       
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRtnL2MarketData(self, data):
        """L2行情推送"""
        print_dict(data)
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRtnL2Index(self, data):
        """L2指数行情推送"""
        print_dict(data)    
    
    #----------------------------------------------------------------------
    @simple_log    
    def onRtnL2Order(self, data):
        """L2订单推送"""
        print_dict(data)
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRtnL2Trade(self, data):
        """L2成交推送"""
        print_dict(data)        

    #----------------------------------------------------------------------
    @simple_log    
    def onRspSubL2OrderAndTrade(self, error, n, last):
        """订阅L2订单、成交回报"""
        print_dict(error)    
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRspUnSubL2OrderAndTrade(self, error, n, last):
        """退订L2订单、成交回报"""
        print_dict(error)    
        
    #----------------------------------------------------------------------
    @simple_log    
    def onNtfCheckOrderList(self, instrumentID, functionID):
        """通知清理SSE买卖一队列中数量为0的报单"""
        print 'instrumentID: %s' % instrumentID
        print 'functionID: %s' % functionID

#----------------------------------------------------------------------
def main():
    """主测试函数，出现堵塞时可以考虑使用sleep"""
    reqid = 0
    
    # 创建Qt应用对象，用于事件循环
    app = QtGui.QApplication(sys.argv)

    # 创建API对象
    api = TestL2MdApi()
    
    # 在C++环境中创建MdApi对象，传入参数是希望用来保存.con文件的地址
    api.createFtdcL2MDUserApi('')
    
    # 注册前置机地址
    api.registerFront("tcp://101.231.210.2:8900")   # 另一个地址tcp://222.66.55.171:8900
    
    # 初始化api，连接前置机
    api.init()
    sleep(0.5)
    
    # 登陆，测试通过
    loginReq = {}                           # 创建一个空字典
    loginReq['UserID'] = ''                 # 参数作为字典键值的方式传入
    loginReq['Password'] = ''               # 键名和C++中的结构体成员名对应
    loginReq['BrokerID'] = '2011'    
    loginReq['DataLevel'] = '1'             # '0'全量行情  '1'10档  '2'5档
    reqid = reqid + 1                       # 请求数必须保持唯一性
    i = api.reqUserLogin(loginReq, 1)
    sleep(0.5)
    
    ## 登出，测试失败
    #reqid = reqid + 1
    #logoutReq = {}
    #logoutReq['UserID'] = api.userID
    #loginReq['BrokerID'] = api.brokerID
    #i = api.reqUserLogout(logoutReq, 1)
    #sleep(0.5)
    
    ## 安全退出，测试通过
    #i = api.exit()
    
    # 获取交易日，测试通过
    #day = api.getTradingDay()
    #print 'Trading Day is:' + str(day)
    #sleep(0.5)
    
    # 订阅L2合约，测试通过
    subReq = {}
    subReq['InstrumentID'] = '510050'
    subReq['ExchangeID'] = 'SSE'
    i = api.subscribeL2MarketData(subReq)
    
    ## 退订L2合约，测试通过
    #i = api.unSubscribeL2MarketData(subReq)
    
    ## 订阅L2指数，测试通过
    #subReq = {}
    #subReq['InstrumentID'] = '000300'
    #subReq['ExchangeID'] = 'SSE'
    #i = api.subscribeL2Index(subReq)
    
    ## 退订L2合约，测试通过
    #i = api.unSubscribeL2Index(subReq)    
    
    # 订阅L2报单和成交，测试提示无此权限
    i = api.subscribeL2OrderAndTrade()
    
    # 退订L2报单和成交，测试通过
    i = api.unSubscribeL2OrderAndTrade()
    
    # 连续运行，用于输出行情
    app.exec_()
    
    
    
if __name__ == '__main__':
    main()
