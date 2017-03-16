# encoding: UTF-8

import sys
from time import sleep

from PyQt4 import QtGui

from vnksotptd import *

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
class TestTdApi(TdApi):
    """测试用实例"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(TestTdApi, self).__init__()
        
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
    def onRspError(self, error, n, last):
        """错误"""
        print_dict(error)
    
    #----------------------------------------------------------------------
    @simple_log  
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        print_dict(data)
        print_dict(error)
        self.brokerID = data['BrokerID']
        self.userID = data['UserID']
        self.frontID = data['FrontID']
        self.sessionID = data['SessionID']
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        print_dict(data)
        print_dict(error)
        
    #----------------------------------------------------------------------
    @simple_log
    def onRspQrySettlementInfo(self, data, error, n, last):
        """查询结算信息回报"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRspSettlementInfoConfirm(self, data, error, n, last):
        """确认结算信息回报"""
        print_dict(data)
        print_dict(error)
        
    #----------------------------------------------------------------------
    @simple_log
    def onRspQryInstrument(self, data, error, n, last):
        """查询合约回报"""
        print_dict(data)
        print_dict(error)
        print n
        print last
        
        
#----------------------------------------------------------------------
def main():
    """主测试函数，出现堵塞时可以考虑使用sleep"""
    reqid = 0
    
    # 创建Qt应用对象，用于事件循环
    app = QtGui.QApplication(sys.argv)

    # 创建API对象，测试通过
    api = TestTdApi()
    
    # 在C++环境中创建MdApi对象，传入参数是希望用来保存.con文件的地址，测试通过
    api.createOTPTraderApi('')
    
    # 设置数据流重传方式，测试通过
    api.subscribePrivateTopic(1)
    api.subscribePublicTopic(1)
    
    # 注册前置机地址，测试通过
    api.registerFront("tcp://115.238.106.253:18993")
    
    # 初始化api，连接前置机
    api.init()
    sleep(8)
    
    # 登陆
    loginReq = {}                           # 创建一个空字典
    loginReq['UserID'] = ''                 # 参数作为字典键值的方式传入
    loginReq['Password'] = ''               # 键名和C++中的结构体成员名对应
    loginReq['BrokerID'] = ''    
    reqid = reqid + 1                       # 请求数必须保持唯一性
    i = api.reqUserLogin(loginReq, 1)
    sleep(3)
    
    # 查询合约, 测试通过
    reqid = reqid + 1
    i = api.reqQryInstrument({}, reqid)
    
    ## 查询结算, 测试通过
    #req = {}
    #req['BrokerID'] = api.brokerID
    #req['InvestorID'] = api.userID
    #reqid = reqid + 1
    #i = api.reqQrySettlementInfo(req, reqid)
    #sleep(0.5)
    
    ## 确认结算, 测试通过
    #req = {}
    #req['BrokerID'] = api.brokerID
    #req['InvestorID'] = api.userID    
    #reqid = reqid + 1
    #i = api.reqSettlementInfoConfirm(req, reqid)
    #sleep(0.5)
    
    
    # 连续运行
    app.exec_()
    
    
    
if __name__ == '__main__':
    main()
