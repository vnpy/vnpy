# encoding: UTF-8

from __future__ import print_function
import sys
from time import sleep
import datetime

from PyQt4 import QtGui

from vnxspeedmd import *


#----------------------------------------------------------------------
def print_dict(d):
    """按照键值打印一个字典"""
    for key,value in d.items():
        print(key + ':' + str(value))


def parseDateTime(date,time,milli):

    year = int(date[0:4])
    month = int(date[4:6])
    day = int(date[6:8])
    hour = int(time[0:2])
    minute = int(time[3:5])
    second = int(time[6:8])
    micro = int(milli)
    return datetime.datetime(year,month,day,hour,minute,second,micro)


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
    def onRspError(self, error):
        """错误"""
        print_dict(error)

    @simple_log
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error):
        """登陆回报"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRspUserLogout(self, data, error):
        """登出回报"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRspSubMarketData(self, data, error):
        """订阅合约回报"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRspUnSubMarketData(self, data, error):
        """退订合约回报"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onMarketData(self, data):
        """行情推送"""
        print_dict(data)

    #----------------------------------------------------------------------
    @simple_log
    def onRspSubForQuoteRsp(self, data, error):
        """订阅合约回报"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRspUnSubForQuoteRsp(self, data, error):
        """退订合约回报"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRtnForQuoteRsp(self, data):
        """行情推送"""
        print_dict(data)


#----------------------------------------------------------------------
def main():
    """主测试函数，出现堵塞时可以考虑使用sleep"""
    reqid = 0

    # 创建Qt应用对象，用于事件循环
    app = QtGui.QApplication(sys.argv)

    # encoding: UTF-8# 创建API对象
    api = TestMdApi()

    # 在C++环境中创建MdApi对象，传入参数是希望用来保存.con文件的地址
    api.createDFITCMdApi() #此API包含获取行情相关的指令

    # 初始化api，连接前置机
    api.init("tcp://203.187.171.250:10915")
    sleep(0.5)

    # 登陆，测试通过
    loginReq = {}
    reqid += 1
    loginReq['lRequestID'] = reqid            # 参数作为字典键值的方式传入
    loginReq['passwd'] = '123'                # 键名和C++中的结构体成员名对应
    loginReq['accountID'] = '000200002874'    # 请求数必须保持唯一性
    i = api.reqUserLogin(loginReq)
    sleep(0.5)

    # 订阅合约，测试通过
    reqid += 1
    i = api.subscribeMarketData('i1605', reqid)

    ## 退订合约，测试通过
    #reqid += 1
    #i = api.unSubscribeMarketData('i1605', reqid)

    input()

    # 连续运行，用于输出行情
    #app.exec_()



if __name__ == '__main__':
    main()
