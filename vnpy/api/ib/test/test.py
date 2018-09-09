# encoding: UTF-8

from __future__ import print_function
import sys

from time import sleep

from six.moves import input

from vnib import IbApi


########################################################################
class TestApi(IbApi):
    print(sys._getframe().f_code.co_name)

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(TestApi, self).__init__()
        
    #----------------------------------------------------------------------
    def nextValidId(self, orderId):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def currentTime(self, time):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def connectAck(self):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def error(self, id_, errorCode, errorString):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def accountSummary(self, reqId, account, tag, value, curency):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def accountSummaryEnd(self, reqId):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def tickPrice(self, tickerId, field, price, canAutoExecute):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def tickSize(self, tickerId, field, size):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def tickOptionComputation(self, tickerId, tickType, impliedVol, delta, optPrice, pvDividend, gamma, vega, theta, undPrice):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def tickGeneric(self, tickerId, tickType, value):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def tickString(self, tickerId, tickType, value):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def tickEFP(self, tickerId, tickType, basisPoints, formattedBasisPoints, totalDividends, holdDays, futureLastTradeDate, dividendImpact, dividendsToLastTradeDate):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def orderStatus(self, orderId, status, filled, remaining, avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def openOrder(self, orderId, contract, order, orderState):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def openOrderEnd(self):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def winError(self, str_, lastError):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def connectionClosed(self):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def updateAccountValue(self, key, val, currency, accountName):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def updatePortfolio(self, contract, position, marketPrice, marketValue, averageCost, unrealizedPNL, realizedPNL, accountName):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def updateAccountTime(self, timeStamp):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def accountDownloadEnd(self, accountName):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def contractDetails(self, reqId, contractDetails):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def bondContractDetails(self, reqId, contractDetails):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def contractDetailsEnd(self, reqId):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def execDetails(self, reqId, contract, execution):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def execDetailsEnd(self, reqId):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def updateMktDepth(self, id_, position, operation, side, price, size):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def updateMktDepthL2(self, id_, position, marketMaker, operation, side, price, size):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def updateNewsBulletin(self, msgId, msgType, newsMessage, originExch):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def managedAccounts(self, accountsList):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def receiveFA(self, pFaDataType, cxml):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def historicalData(self, reqId, date, open_, high, low, close, volume, barCount, WAP, hasGaps):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def scannerParameters(self, xml):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def scannerData(self, reqId, rank, contractDetails, distance, benchmark, projection, legsStr):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def scannerDataEnd(self, reqId):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def realtimeBar(self, reqId, time, open_, high, low, close, volume, wap, count):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def fundamentalData(self, reqId, data):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def deltaNeutralValidation(self, reqId, underComp):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def tickSnapshotEnd(self, reqId):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def marketDataType(self, reqId, marketDataType):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def commissionReport(self, commissionReport):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def position(self, account, contract, position, avgCost):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def positionEnd(self):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def verifyMessageAPI(self, apiData):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def verifyCompleted(self, isSuccessful, errorText):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def displayGroupList(self, reqId, groups):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def displayGroupUpdated(self, reqId, contractInfo):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def verifyAndAuthMessageAPI(self, apiData, xyzChallange):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def verifyAndAuthCompleted(self, isSuccessful, errorText):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def positionMulti(self, reqId, account, modelCode, contract, pos, avgCost):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def positionMultiEnd(self, reqId):	
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def accountUpdateMulti(self, reqId, account, modelCode, key, value, currency):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def accountUpdateMultiEnd(self, reqId):	
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def securityDefinitionOptionalParameter(self, reqId, exchange, underlyingConId, tradingClass, multiplier, expirations, strikes):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
    #----------------------------------------------------------------------
    def securityDefinitionOptionalParameterEnd(self, reqId):
        print(sys._getframe().f_code.co_name)
        print(locals())
    
    #----------------------------------------------------------------------
    def softDollarTiers(self, reqId, tiers):
        print(sys._getframe().f_code.co_name)
        print(locals())
        
        

if __name__ == '__main__':
    api = TestApi()
    
    n = api.eConnect('127.0.0.1', 7497, 123, False)
    print(n)
    
    #t = api.TwsConnectionTime()
    #print t
    
    #
    sleep(1)
    print('req time')
    api.reqCurrentTime()
    
    #
    sleep(1)
    api.reqAccountSummary(9001, "All", "AccountType")
    
    #print 'disconnect'
    #api.eDisconnect()
    
    input()
    
    
