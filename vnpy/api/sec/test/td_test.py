# encoding: UTF-8

import sys

from vnsectd import TdApi


#----------------------------------------------------------------------
def print_dict(d):
    """输出字典"""
    for k, v in d.items():
        print '%s:%s' %(k, v)
    

########################################################################
class TestTdApi(TdApi):
    """测试用例"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(TestTdApi, self).__init__()
    
    #----------------------------------------------------------------------
    def onFrontConnected(self, ):
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
    def onRspStockUserPasswordUpdate(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockEntrustOrder(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockWithdrawOrder(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQryEntrustOrder(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQryRealTimeTrade(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQrySerialTrade(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQryPosition(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQryCapitalAccountInfo(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQryAccountInfo(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQryShareholderInfo(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockTransferFunds(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockEntrustBatchOrder(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockWithdrawBatchOrder(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockCalcAbleEntrustQty(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockCalcAblePurchaseETFQty(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQryFreezeFundsDetail(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQryFreezeStockDetail(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQryTransferStockDetail(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQryTransferFundsDetail(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQryStockInfo(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQryStockStaticInfo(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspStockQryTradeTime(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onStockEntrustOrderRtn(self, data):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onStockTradeRtn(self, data):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onStockWithdrawOrderRtn(self, data):
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
    def onRspSOPUserPasswordUpdate(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPEntrustOrder(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPGroupSplit(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryGroupPosition(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPLockOUnLockStock(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPWithdrawOrder(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryEntrustOrder(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQrySerialTrade(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryPosition(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryCollateralPosition(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryCapitalAccountInfo(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryAccountInfo(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryShareholderInfo(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPCalcAbleEntrustQty(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryAbleLockStock(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryContactInfo(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPExectueOrder(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryExecAssiInfo(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryTradeTime(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryExchangeInfo(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryCommission(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryDeposit(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspSOPQryContractObjectInfo(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onSOPEntrustOrderRtn(self, data):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onSOPTradeRtn(self, data):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onSOPWithdrawOrderRtn(self, data):
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
    def onRspFASLQryAbleFinInfo(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryAbleSloInfo(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLTransferCollateral(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLDirectRepayment(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLRepayStockTransfer(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLEntrustCrdtOrder(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLEntrustOrder(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLCalcAbleEntrustCrdtQty(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryCrdtFunds(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryCrdtContract(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryCrdtConChangeInfo(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLTransferFunds(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryAccountInfo(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryCapitalAccountInfo(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryShareholderInfo(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryPosition(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryEntrustOrder(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQrySerialTrade(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryRealTimeTrade(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryFreezeFundsDetail(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryFreezeStockDetail(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryTransferFundsDetail(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLWithdrawOrder(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQrySystemTime(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryTransferredContract(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLDesirableFundsOut(self, data, error):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryGuaranteedContract(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onRspFASLQryUnderlyingContract(self, data, error, flag):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onFASLEntrustOrderRtn(self, data):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onFASLTradeRtn(self, data):
        """"""
        print sys._getframe().f_code.co_name
        print locals()
    
    #----------------------------------------------------------------------
    def onFASLWithdrawOrderRtn(self, data):
        """"""
        print sys._getframe().f_code.co_name
        print locals()



if __name__ == '__main__':
    SERVER_ADDRESS = 'tcp://203.86.95.187:10910'
    ACCOUNT = '110100001088'
    PASSWORD = '123456'
    
    api = TestTdApi()
    api.createDFITCSECTraderApi('')
    api.init(SERVER_ADDRESS)
    
    # 登录
    req_id = 1
    req = {
        'accountID': ACCOUNT,
        'password': PASSWORD,
        'requestID': req_id
    }
    
    api.reqSOPUserLogin(req)
    
    raw_input()