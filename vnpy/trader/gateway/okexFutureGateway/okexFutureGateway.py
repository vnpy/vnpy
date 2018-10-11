# encoding: UTF-8

from __future__ import print_function

import json
from abc import abstractmethod, abstractproperty

from vnpy.api.okexfuture.OkexFutureApi import *
from vnpy.trader.vtFunction import getJsonPath
from vnpy.trader.vtGateway import *

orderTypeMap = {
    (constant.DIRECTION_LONG, constant.OFFSET_OPEN): OkexFutureOrderType.OpenLong,
    (constant.DIRECTION_SHORT, constant.OFFSET_OPEN): OkexFutureOrderType.OpenShort,
    (constant.DIRECTION_LONG, constant.OFFSET_CLOSE): OkexFutureOrderType.CloseLong,
    (constant.DIRECTION_SHORT, constant.OFFSET_CLOSE): OkexFutureOrderType.CloseShort,
}
orderTypeMapReverse = {v: k for k, v in orderTypeMap.items()}

contracts = (
    'btc_usd', 'ltc_usd', 'eth_usd', 'etc_usd', 'bch_usd',
)

contractTypeMap = {
    'THISWEEK': OkexFutureContractType.ThisWeek,
    'NEXTWEEK': OkexFutureContractType.NextWeek,
    'QUARTER': OkexFutureContractType.Quarter,
}

# symbols for ui,
# keys:给用户看的symbols
# values: API接口使用的symbol和contractType字段
symbolsForUi = {}  # type: dict[str, [str, str]]
for s in contracts:
    for vtContractType, contractType_ in contractTypeMap.items():
        vtSymbol = s + '_' + vtContractType
        symbolsForUi[vtSymbol] = (s, contractType_)


########################################################################
class VnpyGateway(VtGateway):
    """
    每个gateway有太多重复代码，难以拓展和维护。
    于是我设计了这个类，将重复代码抽取出来，简化gateway的实现
    """
    
    #----------------------------------------------------------------------
    def __init__(self, eventEngine):
        super(VnpyGateway, self).__init__(eventEngine, self.gatewayName)
    
    #----------------------------------------------------------------------
    @abstractproperty
    def gatewayName(self):  # type: ()->str
        return 'VnpyGateway'
    
    #----------------------------------------------------------------------
    @abstractproperty
    def exchange(self):  # type: ()->str
        return constant.EXCHANGE_UNKNOWN
    
    #----------------------------------------------------------------------
    def readConfig(self):
        """
        从json文件中读取设置，并将其内容返回为一个dict
        :一个一个return:
        """
        fileName = self.gatewayName + '_connect.json'
        filePath = getJsonPath(fileName, __file__)
        
        try:
            with open(filePath, 'rt') as f:
                return json.load(f)
        except IOError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'读取连接配置出错，请检查'
            # todo: pop a message box is better
            self.onLog(log)
            return
    
    #----------------------------------------------------------------------
    @abstractmethod
    def loadSetting(self):
        """
        载入设置，在connect的时候会被调用到。
        """
        pass

class _Order(object):
    _lastLocalId = 0
    def __init__(self):
        _Order._lastLocalId += 1
        self.localId = str(_Order._lastLocalId)
        self.remoteId = None
        self.vtOrder = None # type: VtOrderData

########################################################################
class OkexFutureGateway(VnpyGateway):
    """OKEX期货交易接口"""
    
    #----------------------------------------------------------------------
    def __init__(self, eventEngine, *args, **kwargs):  # args, kwargs is needed for compatibility
        """Constructor"""
        super(OkexFutureGateway, self).__init__(eventEngine)
        self.apiKey = None  # type: str
        self.apiSecret = None  # type: str
        self.api = OkexFutureRestClient()
        self.leverRate = 1
        self.symbols = []
    
        self.orders =
    #----------------------------------------------------------------------
    @property
    def gatewayName(self):
        return 'OkexFutureGateway'
    
    #----------------------------------------------------------------------
    @abstractproperty
    def exchange(self):  # type: ()->str
        return constant.EXCHANGE_OKEXFUTURE
    
    #----------------------------------------------------------------------
    def loadSetting(self):
        setting = self.readConfig()
        if setting:
            """连接"""
            # 载入json文件
            try:
                # todo: check by predefined settings names and types
                # or check by validator
                self.apiKey = str(setting['apiKey'])
                self.apiSecret = str(setting['secretKey'])
                self.leverRate = setting['leverRate']
                self.symbols = setting['symbols']
            except KeyError:
                log = VtLogData()
                log.gatewayName = self.gatewayName
                log.logContent = u'连接配置缺少字段，请检查'
                self.onLog(log)
                return
    
    #----------------------------------------------------------------------
    def connect(self):
        self.loadSetting()
        self.api.init(self.apiKey, self.apiSecret)
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        pass
    
    #----------------------------------------------------------------------
    def sendOrder(self, vtRequest): # type: (VtOrderReq)->str
        """发单"""
        myorder = _Order()
        localId = myorder.localId
        
        vtOrder = VtOrderData()
        vtOrder.orderID = localId
        vtOrder.vtOrderID = ".".join([self.gatewayName, localId])
        vtOrder.exchange = self.exchange
        
        vtOrder.symbol = vtRequest.symbol
        vtOrder.vtSymbol = '.'.join([vtOrder.symbol, vtOrder.exchange])
        vtOrder.price = vtRequest.price
        vtOrder.totalVolume = vtRequest.volume
        vtOrder.direction = vtRequest.direction
        
        myorder.vtOrder = vtOrder
        
        symbol, contractType = symbolsForUi[vtRequest.symbol]
        orderType = orderTypeMap[(vtRequest.priceType, vtRequest.offset)]  # 开多、开空、平多、平空
        userMarketPrice = False
        
        if vtRequest.priceType == constant.PRICETYPE_MARKETPRICE:
            userMarketPrice = True
            
        self.api.sendOrder(symbol=symbol,
                           contractType=contractType,
                           orderType=orderType,
                           volume=vtRequest.volume,
                           price=vtRequest.price,
                           useMarketPrice=userMarketPrice,
                           leverRate=self.leverRate,
                           onSuccess=self.onOrderSent,
                           extra=None)
        
        return myorder.localId
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.api.cancelOrder(cancelOrderReq)
    
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        pass
    
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.api.spotUserInfo()
    
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.api.close()

    def onOrderSent(self, remoteId, myorder): #type: (int, _Order)->None
        myorder.remoteId = remoteId
        myorder.vtOrder.status = constant.STATUS_NOTTRADED
        self.onOrder(myorder.vtOrder)
        