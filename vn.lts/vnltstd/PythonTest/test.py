# encoding = UTF-8

from PyQt4 import QtGui
import sys
from time import sleep

from vnltstd import *

def printdict(error):
    for key, value in error.items():
        print key + ':' + str(value)

class MyTdApi(TdApi):
    def __init__(self):
        super(MyTdApi, self).__init__()

    def onFrontConnected(self):
        print 'connected'

    def onFrontDisconnected(self, i):
        print 'disconnected'

    def onHeartBeatWarning(self, i):
        print 'heartbeat'

    def onRspError(self, data, id_, last):
        print 'error'
        print data

    def onRspUserLogin(self, data, error, id_, last) :
        print 'login'
        printdict(data)
        printdict(error)
        

    def onRspUserLogout(self, data, error, id_, last):
        print 'logout'
        printdict(data)
        printdict(error)

    #----------------------------------------------------------------------
    def onRspQryInstrument(self, data, error, id_, last):
        """"""
        printdict(data)
    
    #----------------------------------------------------------------------
    def onRspQryInvestor(self, data, error, id_, last):
        """"""
        printdict(data)        

def main():
    
    app = QtGui.QApplication(sys.argv)

    api = MyTdApi()
    api.createFtdcTraderApi('')

    api.registerFront("tcp://101.231.210.1:24505")
    api.init()
    sleep(1.0)

    lgreq = {}
    lgreq['UserID'] = '010000058678'
    lgreq['Password'] = '0656032'
    lgreq['BrokerID'] = '2011'
    i = api.reqUserLogin(lgreq, 1)
    print i
    sleep(1.0)

    #req2 = {}
    #req2['InstrumentID'] = '600600'
    #req2['ExchangeID'] = 'SSE'
    #api.subscribeMarketData(req2)
    
    ireq = {}
    #a = api.reqQryInstrument(ireq, 3)
    b = api.reqQryInvestor(ireq, 3)
    #print 'a is:'+ str(a)

    app.exec_()
    
if __name__ == '__main__':
    main()
