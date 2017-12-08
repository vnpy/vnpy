# encoding: UTF-8

import sys

from vnsecmd import MdApi


#----------------------------------------------------------------------
def print_dict(d):
    """输出字典"""
    for k, v in d.items():
        print '%s:%s' %(k, v)
    

########################################################################
class TestMdApi(MdApi):
    """测试用例"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(TestMdApi, self).__init__()
    
    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onFrontDisconnected(self, reason):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRtnNotice(self, data):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspError(self, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
        print dict(error)
    
    #----------------------------------------------------------------------
    def onRspStockUserLogin(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockUserLogout(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPUserLogin(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
        print_dict(data)
        print_dict(error)
    
    #----------------------------------------------------------------------
    def onRspSOPUserLogout(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLUserLogin(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLUserLogout(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockSubMarketData(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockUnSubMarketData(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPSubMarketData(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPUnSubMarketData(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onStockMarketData(self, data):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onSOPMarketData(self, data):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockAvailableQuot(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSopAvailableQuot(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspUserMDPasswordUpdate(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()


if __name__ == '__main__':
    SERVER_ADDRESS = 'tcp://203.86.95.187:10915'
    ACCOUNT = '110100001088'
    PASSWORD = '123456'
    
    api = TestMdApi()
    api.createDFITCMdApi('')
    api.init('tcp://203.86.95.187:10915')
    
    # 登录
    req_id = 1
    req = {
        'accountID': ACCOUNT,
        'password': PASSWORD,
        'requestID': req_id
    }
    
    api.reqSOPUserLogin(req)
    
    raw_input()