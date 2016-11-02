# encoding: UTF-8

from time import sleep

from vnshzd import *

#----------------------------------------------------------------------
def printDict(d):
    """"""
    l = d.keys()
    l.sort()
    for key in l:
        print '%s:%s' %(key, d[key])


########################################################################
class TestApi(ShzdApi):
    """"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(TestApi, self).__init__()
        pass
    
    #----------------------------------------------------------------------
    def onReceiveErrorInfo(self, errcode, errmsg):
        """"""
        print '-' * 50
        print 'errorcode %s, error msg %s' %(errcode, errmsg)
    
    #----------------------------------------------------------------------
    def onReceiveMarketInfo(self, data):
        """"""
        print '-' * 50
        printDict(data)
    
    #----------------------------------------------------------------------
    def onReceiveTradeInfo(self, data):
        """"""
        print '-' * 50
        printDict(data)
        
if __name__ == '__main__':
    
    api = TestApi()
    
    # 初始化连接
    api.initShZdServer()
    
    # 注册前置机地址
    print api.registerFront('222.73.119.230', 7003)
    print api.registerMarket('222.73.119.230', 9003)
    
    # 登录
    sleep(1)
    data = {}
    data['msgtype'] = 'A'
    data['12'] = 'demo000604'
    data['16'] = '888888'
    api.shzdSendInfoToTrade(data)
    
    # 订阅行情
    sleep(1)
    data = {}
    data['msgtype'] = 'MA'
    data['11'] = '00010337'
    data['201'] = '+'
    #data['307'] = "CME,6J1609"
    data['307'] = 'ICE,WBS1611'
    print data
    api.shzdSendInfoToMarket(data)
    
    # # 查询合约
    # sleep(1)
    # data = {}
    # data['msgtype'] = 'HY'
    # data['11'] = '00010337'
    # api.shzdSendInfoToMarket(data)    
    
    raw_input()
    
    
    