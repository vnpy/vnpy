# encoding: UTF-8

from __future__ import print_function

import json

from typing import Dict

from vnpy.api.okexfutures.OkexFuturesApi import *
from vnpy.trader.vtFunction import getJsonPath
from vnpy.trader.vtGateway import *


########################################################################
class _Order(object):
    _lastLocalId = 0
    
    #----------------------------------------------------------------------
    def __init__(self):
        _Order._lastLocalId += 1
        self.localId = str(_Order._lastLocalId)
        self.remoteId = None
        self.vtOrder = None # type: VtOrderData


########################################################################
class OkexFuturesGateway(VtGateway):
    """OKEX期货交易接口"""
    
    #----------------------------------------------------------------------
    def __init__(self, eventEngine, *_, **__):  # args, kwargs is needed for compatibility
        """Constructor"""
        super(OkexFuturesGateway, self).__init__(eventEngine, 'OkexFuturesGateway')
        self.exchange = constant.EXCHANGE_OKEXFUTURE
        self.apiKey = None  # type: str
        self.apiSecret = None  # type: str
        self.apiPassphrase = None  # type: str

        self.restApi = OkexFuturesRestClientV3()

        self.webSocket = OkexFuturesWebSocketClient()
        self.webSocket.onTick = self._onTick
        self.webSocket.onUserTrade = self._onUserTrade
        
        self.leverRate = 1
        self.symbols = []

        self.tradeID = 0
        self._orders = {}  # type: Dict[str, _Order]
        self._remoteIds = {}  # type: Dict[str, _Order]

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
            return None
    
    #----------------------------------------------------------------------
    def loadSetting(self):
        """载入设置"""
        setting = self.readConfig()
        if setting:
            """连接"""
            # 载入json文件
            try:
                # todo: check by predefined settings names and types
                # or check by validator
                self.apiKey = str(setting['apiKey'])
                self.apiSecret = str(setting['secretKey'])
                self.apiPassphrase = str(setting['passphrase'])
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
        """连接"""
        self.loadSetting()
        self.restApi.init(self.apiKey, self.apiSecret, self.apiPassphrase)
        self.webSocket.init(self.apiKey, self.apiSecret, self.apiPassphrase)
        self.restApi.start()
        self.webSocket.start()
        
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq): # type: (VtSubscribeReq)->None
        """订阅行情"""
        remoteSymbol, remoteContractType = localSymbolToRemote(subscribeReq.symbol)
        return self.webSocket.subscribe(remoteSymbol, remoteContractType)

    #----------------------------------------------------------------------
    def _getOrderByLocalId(self, localId):
        """从本地Id获取对应的内部Order对象"""
        if localId in self._orders:
            return self._orders[localId]
        return None

    #----------------------------------------------------------------------
    def _getOrderByRemoteId(self, remoteId):
        """从Api的OrderId获取对应的内部Order对象"""
        if remoteId in self._remoteIds:
            return self._remoteIds[remoteId]
        return None

    #----------------------------------------------------------------------
    def _saveRemoteId(self, remoteId, myorder):
        """将remoteId和队友的"""
        myorder.remoteId = remoteId
        self._remoteIds[remoteId] = myorder

    #----------------------------------------------------------------------
    def _generateLocalOrder(self, symbol, price, volume, direction, offset):
        myorder = _Order()
        localId = myorder.localId
        self._orders[localId] = myorder
        myorder.vtOrder = VtOrderData.createFromGateway(self,
                                                        self.exchange,
                                                        localId,
                                                        symbol,
                                                        price,
                                                        volume,
                                                        direction,
                                                        offset)
        return myorder
    
    #----------------------------------------------------------------------
    def sendOrder(self, vtRequest): # type: (VtOrderReq)->str
        """发单"""
        myorder = self._generateLocalOrder(vtRequest.symbol,
                                           vtRequest.price,
                                           vtRequest.volume,
                                           vtRequest.direction,
                                           vtRequest.offset)

        orderType = _orderTypeMap[(vtRequest.direction, vtRequest.offset)]  # 开多、开空、平多、平空
        userMarketPrice = False
        
        if vtRequest.priceType == constant.PRICETYPE_MARKETPRICE:
            userMarketPrice = True

        self.restApi.sendOrder(symbol=vtRequest.symbol,
                               orderType=orderType,
                               volume=vtRequest.volume,
                               price=vtRequest.price,
                               matchPrice=userMarketPrice,
                               leverRate=self.leverRate,
                               onSuccess=self._onOrderSent,
                               onFailed=self._onSendOrderFailed,
                               extra=myorder,
                               )
        return myorder.localId

    #----------------------------------------------------------------------
    def cancelOrder(self, vtCancel):  # type: (VtCancelOrderReq)->None
        """撤单"""
        myorder = self._getOrderByLocalId(vtCancel.orderID)
        assert myorder is not None, u"理论上是无法取消一个不存在的本地单的"
        
        self.restApi.cancelOrder(vtCancel.symbol,
                                 myorder.remoteId,
                                 onSuccess=self._onOrderCanceled,
                                 extra=myorder
                                 )
    
    #----------------------------------------------------------------------
    def queryContracts(self):
        self.restApi.queryContracts(onSuccess=self._onQueryContracts)
    
    #----------------------------------------------------------------------
    def queryOrders(self, symbol, status):  # type: (str, OkexFuturesOrderStatus)->None
        """
        :param symbol:
        :param status: OkexFuturesOrderStatus
        :return:
        """
        
        self.restApi.queryOrders(symbol=symbol,
                                 status=status,
                                 onSuccess=self._onQueryOrders,
                                 )
    
    #----------------------------------------------------------------------
    def qryAccount(self):
        self.restApi.queryAccount(onSuccess=self._onQueryAccount)
        """查询账户资金"""
        pass
    
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.restApi.queryPositions(onSuccess=self._onQueryPosition)
    
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.restApi.stop()
        self.webSocket.stop()

    #----------------------------------------------------------------------
    def _onOrderSent(self, order, myorder):  #type: (OkexFuturesOrderSentInfoV3, _Order)->None
        myorder.remoteId = order.orderId
        myorder.vtOrder.status = constant.STATUS_NOTTRADED
        self._saveRemoteId(myorder.remoteId, myorder)
        self.onOrder(myorder.vtOrder)

    #----------------------------------------------------------------------
    @staticmethod
    def _onSendOrderFailed(order, myorder):  #type: (OkexFuturesOrderSentInfoV3, _Order)->None
        myorder.vtOrder.status = constant.STATUS_REJECTED
    
    #----------------------------------------------------------------------
    @staticmethod
    def _onOrderCanceled(myorder): # type: (_Order)->Any
        myorder.vtOrder.status = constant.STATUS_CANCELLED
        
    #----------------------------------------------------------------------
    def _onQueryContracts(self, contracts, extra): # type: (List[OkexFuturesContractsInfoV3], Any)->None
        for contract in contracts:
            vtContract = VtContractData.createFromGateway(
                gateway=self,
                exchange=self.exchange,
                symbol=contract.symbol,
                productClass=constant.PRODUCT_FUTURES,
                priceTick=contract.tickSize,
                size=contract.quoteIncrement,
                name=contract.symbol,
                expiryDate=contract.delivery,
                underlyingSymbol=contract.underlyingIndex
            )
            self.onContract(vtContract)

    #----------------------------------------------------------------------
    def _onQueryOrders(self, orders, extra):  # type: (List[OkexFuturesOrderDetailV3], Any)->None
        localContractType = extra
        for order in orders:
            remoteId = order.remoteId

            myorder = self._getOrderByRemoteId(remoteId)
            if myorder:
                # 如果订单已经缓存在本地，则尝试更新订单状态
            
                # 有新交易才推送更新
                if order.tradedVolume != myorder.vtOrder.tradedVolume:
                    myorder.vtOrder.tradedVolume = order.tradedVolume
                    myorder.vtOrder.status = constant.STATUS_PARTTRADED
                    self.onOrder(myorder.vtOrder)
            else:
                # 本地无此订单的缓存（例如，用其他工具的下单）
                # 缓存该订单，并推送
                symbol = remoteSymbolToLocal(order.symbol, localContractType)
                direction, offset = remoteOrderTypeToLocal(order.orderType)
                myorder = self._generateLocalOrder(symbol, order.price, order.volume, direction, offset)
                myorder.vtOrder.tradedVolume = order.tradedVolume
                myorder.remoteId = order.remoteId
                self._saveRemoteId(myorder.remoteId, myorder)
                self.onOrder(myorder.vtOrder)
                
    #----------------------------------------------------------------------
    def _onQueryAccount(self, infos, _):  # type: (List[OkexFuturesAccountInfoV3], Any)->None
        for info in infos:
            vtAccount = VtAccountData()
            vtAccount.accountID = info.currency
            vtAccount.vtAccountID = self.gatewayName + '.' + vtAccount.accountID
            vtAccount.balance = info.balance
            vtAccount.available = info.available
            vtAccount.margin = info.hold  # todo: is this right?
            self.onAccount(vtAccount)

    #----------------------------------------------------------------------
    def _onQueryPosition(self, posex, extra):  # type: (List[OkexFuturesPositionInfoV3], Any)->None
        localContractType = extra
        for pos in posex:
            # 多头持仓
            posex = VtPositionData.createFromGateway(
                gateway=self,
                exchange=self.exchange,
                symbol=remoteSymbolToLocal(pos.symbol, localContractType),
                direction=constant.DIRECTION_NET,
                position=float(pos.longQty),
                price=pos.longAvgCost,
            )
        
            self.onPosition(posex)
        
            # 空头持仓
            posex = VtPositionData.createFromGateway(
                gateway=self,
                exchange=self.exchange,
                symbol=remoteSymbolToLocal(pos.symbol, localContractType),
                direction=constant.DIRECTION_SHORT,
                position=float(pos.shortQty),
                price=pos.shortAvgCost,
            )
        
            self.onPosition(posex)

    #----------------------------------------------------------------------
    def _onTick(self, info):  # type: (OkexFuturesTickInfo)->None
        uiSymbol = remoteSymbolToLocal(info.symbol, remoteContractTypeToLocal(info.remoteContractType))
        self.onTick(VtTickData.createFromGateway(
            gateway=self,
            symbol=uiSymbol,
            exchange=self.exchange,
            lastPrice=info.last,
            lastVolume=info.vol,
            highPrice=info.high,
            lowPrice=info.low,
            openInterest=info.holdAmount,
            lowerLimit=info.limitLow,
            upperLimit=info.limitHigh,
        ))

    def _onUserTrade(self, info):  # type: (OkexFuturesUserTradeInfo)->None
        tradeID = str(self.tradeID)
        self.tradeID += 1
        order = self._getOrderByRemoteId(info.remoteId)
        if order:
            self.onTrade(VtTradeData.createFromOrderData(
                order=order.vtOrder,
                tradeID=tradeID,
                tradePrice=info.price,
                tradeVolume=info.dealAmount  # todo: 这里应该填写的到底是order总共成交了的数量，还是该次trade成交的数量
            ))
        else:
            # todo: 与order无关联的trade该如何处理？
            # uiSymbol = remoteSymbolToLocal(info.symbol, remoteContractTypeToLocal(info.remoteContractType))
            pass
        return
        

#----------------------------------------------------------------------
def localOrderTypeToRemote(direction, offset):  # type: (str, str)->str
    return _orderTypeMap[(direction, offset)]


#----------------------------------------------------------------------
def remoteOrderTypeToLocal(orderType):  # type: (str)->(str, str)
    """
    :param orderType:
    :return: direction, offset
    """
    return _orderTypeMapReverse[orderType]


#----------------------------------------------------------------------
def localContractTypeToRemote(localContractType):
    return _contractTypeMap[localContractType]


#----------------------------------------------------------------------
def remoteContractTypeToLocal(remoteContractType):
    return _contractTypeMapReverse[remoteContractType]


#----------------------------------------------------------------------
def localSymbolToRemote(symbol):  # type: (str)->(OkexFuturesSymbol, OkexFuturesContractType)
    """
    :return: remoteSymbol, remoteContractType
    """
    return _symbolsForUi[symbol]


#----------------------------------------------------------------------
def remoteSymbolToLocal(remoteSymbol, localContractType):
    return remoteSymbol.upper() + '_' + localContractType


_orderTypeMap = {
    (constant.DIRECTION_LONG, constant.OFFSET_OPEN): OkexFuturesOrderType.OpenLong,
    (constant.DIRECTION_SHORT, constant.OFFSET_OPEN): OkexFuturesOrderType.OpenShort,
    (constant.DIRECTION_LONG, constant.OFFSET_CLOSE): OkexFuturesOrderType.CloseLong,
    (constant.DIRECTION_SHORT, constant.OFFSET_CLOSE): OkexFuturesOrderType.CloseShort,
}
_orderTypeMapReverse = {v: k for k, v in _orderTypeMap.items()}

_contractTypeMap = {
    k.upper(): v for k, v in OkexFuturesContractType.__dict__.items() if not k.startswith('_')
}
_contractTypeMapReverse = {v: k for k, v in _contractTypeMap.items()}

_easySymbols = {
    v for k, v in OkexFuturesEasySymbol.__dict__.items() if not k.startswith('_')
}

_remoteSymbols = {
    v for k, v in OkexFuturesSymbol.__dict__.items() if not k.startswith('_')
}

# symbols for ui,
# keys:给用户看的symbols : f"{internalSymbol}_{contractType}"
# values: API接口使用的symbol和contractType字段
_symbolsForUi = {(remoteSymbol.upper() + '_' + upperContractType.upper()): (remoteSymbol, remoteContractType)
                 for remoteSymbol in _remoteSymbols
                 for upperContractType, remoteContractType in
                 _contractTypeMap.items()}  # type: Dict[str, List[str, str]]
_symbolsForUiReverse = {v: k for k, v in _symbolsForUi.items()}

_channel_for_subscribe = {
    'ok_sub_futureusd_' + easySymbol + '_ticker_' + remoteContractType: (easySymbol, remoteContractType)
    for easySymbol in _easySymbols
    for remoteContractType in _contractTypeMap.values()
}
