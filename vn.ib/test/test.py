# encoding: UTF-8

from time import sleep

from vnib import IbApi


########################################################################
class TestApi(IbApi):
    """"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(TestApi, self).__init__()
        
    #----------------------------------------------------------------------
    def nextValidId(self, orderId):
        """"""
        print 'next valid id:', orderId
        
    #----------------------------------------------------------------------
    def currentTime(self, time):
        """"""
        print 'current time is:', time
        
    #----------------------------------------------------------------------
    def connectAck(self):
        """"""
        print 'connection established'
        
    #----------------------------------------------------------------------
    def error(self, i, errorCode, errorString):
        """"""
        print 'error', i, errorCode, errorString
    
    #----------------------------------------------------------------------
    def accountSummary(self, reqId, account, tag, value, curency):
        """"""
        print 'account summary', reqId, account, tag, value, curency
        
    #----------------------------------------------------------------------
    def accountSummaryEnd(self, reqId):
        """"""
        print 'account summary end', reqId
        

if __name__ == '__main__':
    api = TestApi()
    
    n = api.eConnect('127.0.0.1', 7497, 123, False)
    print n
    
    #t = api.TwsConnectionTime()
    #print t
    
    #
    sleep(1)
    print 'req time'
    api.reqCurrentTime()
    
    #
    sleep(1)
    api.reqAccountSummary(9001, "All", "AccountType")
    
    #print 'disconnect'
    #api.eDisconnect()
    
    raw_input()
    
    