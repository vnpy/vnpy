# encoding: UTF-8

from __future__ import print_function
import sys
from time import sleep

from PyQt4 import QtGui

from vnxspeedtd import *


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
        print(n)

    #----------------------------------------------------------------------
    @simple_log
    def onRspUserLogin(self, data, error):
        """登陆回报"""
        print_dict(data)
        print_dict(error)
        self.accountID = data['accountID']
        self.sessionID = data['sessionID']
        self.localOrderID = data['initLocalOrderID'] - 1

    #----------------------------------------------------------------------
    @simple_log
    def onRspUserLogout(self, data, error):
        """登出回报"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRspInsertOrder(self, data, error):
        """查询持仓"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRspCancelOrder(self, data, error):
        """查询持仓"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRspQryPosition(self, data, error, last):
        """查询持仓"""
        print_dict(data)
        print_dict(error)
        print(last)

    #----------------------------------------------------------------------
    @simple_log
    def onRspQryPositionDetail(self, data, error, last):
        """查询持仓"""
        print_dict(data)
        print_dict(error)
        print(last)

    #----------------------------------------------------------------------
    @simple_log
    def onRspCustomerCapital(self, data, error):
        """查询持仓"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRspQryExchangeInstrument(self, data, error, last):
        """查询持仓"""
        print_dict(data)
        print_dict(error)
        print(last)

    #----------------------------------------------------------------------
    @simple_log
    def onRspArbitrageInstrument(self, data, error, last):
        """查询持仓"""
        print_dict(data)
        print_dict(error)
        print(last)

    #----------------------------------------------------------------------
    @simple_log
    def onRtnErrorMsg(self, error):
        """查询持仓"""
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRtnMatchedInfo(self, data):
        """查询持仓"""
        print_dict(data)

    #----------------------------------------------------------------------
    @simple_log
    def onRtnOrder(self, data):
        """查询持仓"""
        print_dict(data)

    #----------------------------------------------------------------------
    @simple_log
    def onRtnCancelOrder(self, data):
        """查询持仓"""
        print_dict(data)

    #----------------------------------------------------------------------
    @simple_log
    def onRspQryOrderInfo(self, data, error, last):
        """查询持仓"""
        print_dict(data)
        print_dict(error)
        print(last)

    #----------------------------------------------------------------------
    @simple_log
    def onRspQryMatchOrder(self, data, error, last):
        """查询持仓"""
        print_dict(data)
        print_dict(error)
        print(last)

    #----------------------------------------------------------------------
    @simple_log
    def onRspQrySpecifyInstrument(self, data, error, last):
        """查询持仓"""
        print_dict(data)
        print_dict(error)
        print(last)

    #----------------------------------------------------------------------
    @simple_log
    def onRtnTradingNotice(self, data):
        """查询持仓"""
        print_dict(data)

    #----------------------------------------------------------------------
    @simple_log
    def onRspBillConfirm(self, data, error):
        """查询持仓"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRspEquityComputMode(self, data):
        """查询持仓"""
        print_dict(data)

    #----------------------------------------------------------------------
    @simple_log
    def onRspQryBill(self, data, error, last):
        """查询持仓"""
        print_dict(data)
        print_dict(error)
        print(last)

    #----------------------------------------------------------------------
    @simple_log
    def onRspForQuote(self, data, error):
        """查询持仓"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRspQryForQuote(self, data, error, last):
        """查询持仓"""
        print_dict(data)
        print_dict(error)
        print(last)

    #----------------------------------------------------------------------
    @simple_log
    def onRtnForQuote(self, data):
        """查询持仓"""
        print_dict(data)

    #----------------------------------------------------------------------
    @simple_log
    def onRspQryQuoteOrderInfo(self, data, error, last):
        """查询持仓"""
        print_dict(data)
        print_dict(error)
        print(last)

    #----------------------------------------------------------------------
    @simple_log
    def onRspQryQuoteNotice(self, data, error, last):
        """查询持仓"""
        print_dict(data)
        print_dict(error)
        print(last)

    #----------------------------------------------------------------------
    @simple_log
    def onRspQryDepthMarketData(self, data, error, last):
        """查询持仓"""
        print_dict(data)
        print_dict(error)
        print(last)


#----------------------------------------------------------------------
def main():
    """主测试函数，出现堵塞时可以考虑使用sleep"""
    reqid = 0

    # 创建Qt应用对象，用于事件循环
    app = QtGui.QApplication(sys.argv)

    # 创建API对象，测试通过
    api = TestTdApi()

    # 在C++环境中创建TdApi对象，传入参数是希望用来保存.con文件的地址，测试通过
    api.createDFITCTraderApi()

    # 注册前置机地址，初始化api
    api.init("tcp://203.187.171.250:10910")

    sleep(0.5)

    # 登陆，测试通过
    loginReq = {}
    reqid += 1
    loginReq['lRequestID'] = reqid            # 参数作为字典键值的方式传入
    loginReq['passwd'] = '123'                # 键名和C++中的结构体成员名对应
    loginReq['accountID'] = '000200002874'    # 请求数必须保持唯一性
    i = api.reqUserLogin(loginReq)
    sleep(0.5)


 #----------------------------------------------------------------------
    def sendOrder(api, symbol, price, volume, reqid):
        """发单"""

        req = {}
        req['accountID'] = api.accountID
        req['instrumentID'] = symbol
        req['buySellType'] = 1
        req['openCloseType'] = 1
        req['localOrderID'] = 1
        req['insertPrice'] = price
        req['orderAmount'] = volume
        req['speculator'] = 0
        req['orderProperty'] = '0'
        req['orderType'] = 1
        req['instrumentType'] = 0
        req['insertType'] = 0x0001

        i = api.reqInsertOrder(req)

        return i

    def cancelOrder(api, orderRef, reqid):
        """撤单"""

        req = {}

        req['accountID'] = api.accountID
        req['instrumentID'] = 'i1605'
        req['localOrderID'] = orderRef

        i = api.reqCancelOrder(req)
        return i

    # 发单测试， 测试通过
    reqid = reqid + 1
    sendOrder(api, 'i1605', 299, 1, reqid)
    sleep(3)
    # 撤单测试， 待测试
    reqid = reqid + 1
    cancelOrder(api, 1, reqid)

    input()

    # 连续运行
    #app.exec_()



if __name__ == '__main__':
    main()
