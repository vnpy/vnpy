# encoding: UTF-8

# 内置模块
from __future__ import print_function
import sys
from time import sleep

# 测试模块
from vnltsmd import *

#----------------------------------------------------------------------
def print_dict(d):
    """按照键值打印一个字典"""
    for key,value in d.items():
        print(key + ':' + str(value))
        
        
#----------------------------------------------------------------------
def simple_log(func):
    """简单装饰器用于输出函数名"""
    def wrapper(*args, **kw):
        print("")
        print(str(func.__name__))
        return func(*args, **kw)
    return wrapper


########################################################################
class TestMdApi(MdApi):
    """测试用实例"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(TestMdApi, self).__init__()
        
    #----------------------------------------------------------------------
    @simple_log    
    def onFrontConnected(self):
        """服务器连接"""
        pass
    
    #----------------------------------------------------------------------
    @simple_log    
    def onFrontDisconnected(self, n):
        """服务器断开"""
        print(n)
        
    #----------------------------------------------------------------------
    @simple_log    
    def onHeartBeatWarning(self, n):
        """心跳报警"""
        print(n)
    
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
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        print_dict(data)
        print_dict(error)
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRspSubMarketData(self, data, error, n, last):
        """订阅合约回报"""
        print_dict(data)
        print_dict(error)
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRspUnSubMarketData(self, data, error, n, last):
        """退订合约回报"""
        print_dict(data)
        print_dict(error)    
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRtnDepthMarketData(self, data):
        """行情推送"""
        print_dict(data)


#----------------------------------------------------------------------
def main():
    """主测试函数，出现堵塞时可以考虑使用sleep"""
    reqid = 0

    # 创建API对象
    api = TestMdApi()
    
    # 在C++环境中创建MdApi对象，传入参数是希望用来保存.con文件的地址
    api.createFtdcMdApi('')
    
    # 注册前置机地址
    api.registerFront("tcp://211.144.195.163:34513")
    
    # 初始化api，连接前置机
    api.init()
    sleep(0.5)
    
    # 登陆
    loginReq = {}                           # 创建一个空字典
    loginReq['UserID'] = ''                 # 参数作为字典键值的方式传入
    loginReq['Password'] = ''               # 键名和C++中的结构体成员名对应
    loginReq['BrokerID'] = '2011'    
    reqid = reqid + 1                       # 请求数必须保持唯一性
    i = api.reqUserLogin(loginReq, 1)
    sleep(0.5)
    
    ## 安全退出，测试通过
    #i = api.exit()
    
    #获取交易日，测试通过
    day = api.getTradingDay()
    print('Trading Day is:' + str(day))
    sleep(0.5)
    
    # 订阅合约，测试通过
    subReq = {}
    subReq['InstrumentID'] = '510050'
    subReq['ExchangeID'] = 'SSE'
    i = api.subscribeMarketData(subReq)
    
    ## 退订合约，测试通过
    #i = api.unSubscribeMarketData(subReq)
    
    while 1:
        sleep(1)
    
if __name__ == '__main__':
    main()
