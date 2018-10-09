# encoding: UTF-8

from __future__ import print_function

import json
from abc import abstractmethod, abstractproperty

from vnpy.api.okexfuture.vnokexFuture import OkexFutureHttpClient
from vnpy.network.HttpClient import Request
from vnpy.trader.vtFunction import getJsonPath
from vnpy.trader.vtGateway import *

orderTypeMap = {
    (constant.DIRECTION_LONG, constant.OFFSET_OPEN): 1,
    (constant.DIRECTION_SHORT, constant.OFFSET_OPEN): 2,
    (constant.DIRECTION_LONG, constant.OFFSET_CLOSE): 3,
    (constant.DIRECTION_SHORT, constant.OFFSET_CLOSE): 4,
}
orderTypeMapReverse = {v: k for k, v in orderTypeMap.items()}

contracts = (
    'btc_usd', 'ltc_usd', 'eth_usd', 'etc_usd', 'bch_usd',
)

contractTypeMap = {
    'THISWEEK': 'this_week',
    'NEXTWEEK': 'next_week',
    'QUARTER': 'quarter',
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


########################################################################
class OkexFutureGateway(VnpyGateway):
    """OKEX期货交易接口"""
    
    #----------------------------------------------------------------------
    def __init__(self, eventEngine, *args, **kwargs):  # args, kwargs is needed for compatibility
        """Constructor"""
        super(OkexFutureGateway, self).__init__(eventEngine)
        self.apiKey = None  # type: str
        self.apiSecret = None  # type: str
        self.api = OkexFutureApi(self)
        self.leverRate = 1.0
        self.symbols = []
    
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
    def sendOrder(self, orderReq):
        """发单"""
        return self.api.sendOrder(orderReq)
    
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


########################################################################
class VnpyOrder():
    
    def __init__(self):
        """
        这个东西将VtOrderReq和VtOrderData还有Request三者绑定起来，以便查询
        """
        self.vtRequest = None  # type: VtOrderReq  # 如果这个order是通过sendOrder产生的，则会有对应的vtRequest
        self.request = None  # type: Request  # 如果这个order是通过sendOrder产生的，request就是对应的网络请求
        self.order = None  # type: VtOrderData  # 对应的VtOrderData
        self.remoteId = None  # type: str   # 当确定了这个order在交易所内部的id的时候，这个值才会有效


########################################################################
class ApiBase(object):
    """
    每个Api实现发单等等操作的时候，有太多重复代码。
    于是我写了这个类，以期简化Api的实现。
    
    发单实现：
    重写_sendOrder函数。
    在_sendOrder的下单请求回执中获取API使用的orderId，并调用_processOrderSent函数即可
    
    例如：
    def _sendOrder(self, vtRequest):
       return self.httpClient.addReq(..., callback=self._onOrderSent)
    
    def _onOrderSent(self, data, req):
        remoteId = None
        if data['success'] is True:
            remoteId = data['order_id']
        self._processOrderSent(req, remoteId)
    
    撤单实现：
    重写_cancelOrder函数。
    """
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        self.gateway = gateway  # type: VnpyGateway
    
    #----------------------------------------------------------------------
    # todo: push this / make this standalone
    def generateVnpyOrder(self):
        order = VnpyOrder()
        order.order = VtOrderData()
        order.order.exchange = self.gateway.exchange
        return order
    
    #----------------------------------------------------------------------
    @staticmethod
    def fillVnpyOrder(order, symbol, price, totalVolume,
                      direction):  # type: (VnpyOrder, str, float, float, str)->None
        order.order.symbol = symbol
        order.order.vtSymbol = '.'.join([order.order.symbol, order.order.exchange])
        order.order.price = price
        order.order.totalVolume = totalVolume
        order.order.direction = direction
    
    #----------------------------------------------------------------------
    def sendOrder(self, vtRequest):  # type: (VtOrderReq)->str
        """发单"""
        
        # 内部状态相关
        order = self.generateVnpyOrder()
        self.fillVnpyOrder(order,
                           vtRequest.symbol,
                           vtRequest.price,
                           vtRequest.volume,
                           vtRequest.direction)
        order.vtRequest = vtRequest
        
        # 发送发单请求
        order.request = self._sendOrder(vtRequest)
        
        # 增加反向引用
        # 这个写法在逻辑上有漏洞：当请求返回特别快（理论上可能）的时候，返回回调中的extra仍为空
        # 但是这种情况几乎不可能出现，在Python中就更不可能会出现。所以就这样写把，美观一些
        order.request.extra = order
        
        return order.order.vtOrderID
    
    #----------------------------------------------------------------------
    def _processOrderSent(self, request, remoteId):
        """
        如果在_sendOrder中发送了HTTP请求，则应该在收到响应的时候调用该函数，
        并且将remoteId设置为交易所API使用的ID
        
        如果该下单请求失败，将remoteId设为None即可
        """
        if remoteId:
            order = request.extra  # type: VnpyOrder
            order.remoteId = remoteId  # None就是失败或者未返回
            self.gateway.onOrder(order.order)
            
            # todo: 撤单委托相关
    
    #----------------------------------------------------------------------
    @abstractmethod
    def _sendOrder(self, vtRequest): # type: (VtOrderReq)->Request
        """
        这个函数实现下单请求。
        :return: 如果发送了HTTP请求，就应该返回addReq的值。
        """
        pass

    #----------------------------------------------------------------------
    @abstractmethod
    def _cancelOrder(self, vtCancelRequest):  # type: (VtCancelOrderReq)->Request
        """
        这个函数实现下单请求。
        :return: 如果发送了HTTP请求，就应该返回addReq的值。
        """
        pass


########################################################################
class OkexFutureApi(ApiBase):
    """OKEX的API实现"""
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(OkexFutureApi, self).__init__()
        self.gateway = gateway  # type: OkexFutureGateway
        
        self.localID = 0
        self.client = OkexFutureHttpClient()
    
    #----------------------------------------------------------------------
    def onOrderSent(self, data, req):  # type: (dict, Request)->None
        """
        下单回执，一般用来保存sysId
        """
        remoteId = None
        if data['result'] is True:
            remoteId = data['order_id']
        super(OkexFutureApi, self)._processOrderSent(req, remoteId)

    #----------------------------------------------------------------------
    def _cancelOrder(self, vtCancelRequest):  # type: (VtCancelOrderReq)->Request
        localId = vtCancelRequest.orderID
        pass
    
    #----------------------------------------------------------------------
    def _sendOrder(self, vtRequest):  # type: (VtOrderReq)->Request
        """
        单纯的发单
        """
        symbol, contractType = symbolsForUi[vtRequest.symbol]
        orderType = orderTypeMap[(vtRequest.priceType, vtRequest.offset)]  # 开多、开空、平多、平空
        
        data = {}
        if vtRequest.priceType == constant.PRICETYPE_MARKETPRICE:
            data['match_price'] = 1
        else:
            data['price'] = vtRequest.price
        data.update({
            'symbol': symbol,
            'contract_typ': contractType,  # 合约类型：当周/下周/季度
            'amount': vtRequest.volume,
            'type': orderType,
            'lever_rate': self.gateway.leverRate  # 杠杆倍数
        })
        
        request = self.client.addReq('POST',
                                     '/future_trade.do',
                                     callback=self.onOrderSent,
                                     data=data)
        return request
