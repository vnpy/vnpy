# encoding: UTF-8
from enum import Enum
from typing import Any, Callable, List, Union

from vnpy.api.okexfuture.vnokexFuture import OkexFutureRestBase
from vnpy.network.RestClient import Request


class _OkexFutureCustomExtra(object):
    
    def __init__(self, onSuccess, onFailed, extra):
        self.onFailed = onFailed
        self.onSuccess = onSuccess
        self.extra = extra


class OkexFuturePriceType(Enum):
    Buy = 'buy'
    Sell = 'sell'


class OkexFutureContractType(Enum):
    ThisWeek = 'this_week'
    NextWeek = 'next_week'
    Quarter = 'quarter'


class OkexFutureStatus(Enum):
    NoTraded = '0'
    PartialTraded = '1'
    AllTraded = '2'
    Canceled = '-1'
    CancelProcessing = '4'
    Canceling = '5'


class OkexFutureOrderType(Enum):
    OpenLong = '1'
    OpenShort = '2'
    CloseLong = '3'
    CloseShort = '4'


class OkexFutureOrder(object):
    
    def __init__(self):
        self.symbol = None
        self.volume = None
        self.price = None
        self.priceAvg = None
        self.status = None
        self.orderType = None
        self.unitAmount = None
        self.leverRate = None
        self.remoteId = None
        self.fee = None
        self.tradedVolume = None
        self.createDate = None


class OkexFutureUserInfo(object):
    
    def __init__(self):
        self.accountRights = None
        self.keepDeposit = None
        self.profitReal = None
        self.profitUnreal = None
        self.riskRate = None


class OkexFuturePosition(object):
    
    def __init__(self, ):
        self.forceLiquidatePrice = None
        self.holding = []  # type: List[OkexFuturePositionDetail]


class OkexFuturePositionDetail(object):
    
    def __init__(self, ):
        self.buyAmount = None
        self.buyAvailable = None
        self.buyPriceAvg = None
        self.buyPriceCost = None
        self.buyProfitReal = None
        self.contractId = None
        self.createDate = None
        self.leverRate = None
        self.sellAmount = None
        self.sellAvailable = None
        self.sellPriceAvg = None
        self.sellPriceCost = None
        self.sellProfitReal = None
        self.symbol = None
        self.contractType = None


########################################################################
class OkexFutureRestClient(OkexFutureRestBase):
    
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(OkexFutureRestClient, self).__init__()
        
        self.client = ()
        
        self._redirectedOnError = None  # type: Callable[[object, object, object, Request], Any]
    
    #----------------------------------------------------------------------
    def setOnError(self, callback):  # type: (Callable[[object, object, object, Request], Any])->None
        self._redirectedOnError = callback
    
    #----------------------------------------------------------------------
    def onError(self, exceptionType, exceptionValue, tb, req):
        if self._redirectedOnError:
            self._redirectedOnError(exceptionType, exceptionValue, tb, req)
    
    #----------------------------------------------------------------------
    def onFailed(self, httpStatusCode, req):
        super(OkexFutureRestClient, self).onFailed(httpStatusCode, req)
    
    #----------------------------------------------------------------------
    def sendOrder(self, symbol, contractType, orderType, volume,
                  onSuccess, onFailed=None,
                  price=None, useMarketPrice=False, leverRate=None,
                  extra=None):  # type:(str, OkexFutureContractType, OkexFutureOrderType, float, Callable[[int, Any], Any], Callable[[Any], Any], float, bool, Union[int, None], Any)->Request
        """
        :param symbol: str
        :param contractType: OkexFutureContractType
        :param orderType: OkexFutureOrderType
        :param volume: float
        :param onSuccess: (orderId: int)->Any
        :param onFailed: ()->Any
        :param price: float
        :param useMarketPrice: bool
        :param leverRate: int | None
        :param extra: Any
        :return: Request
        """
        
        data = {}
        if useMarketPrice:
            data['match_price'] = 1
        else:
            data['price'] = price
        data.update({
            'symbol': symbol,
            'contract_typ': contractType,  # 合约类型：当周/下周/季度
            'amount': volume,
            'type': orderType,
        })
        if leverRate:
            data['lever_rate'] = leverRate  # 杠杆倍数
        
        request = self.addReq('POST',
                              '/future_trade.do',
                              callback=self.onOrderSent,
                              data=data,
                              extra=_OkexFutureCustomExtra(onSuccess, onFailed, extra))
        return request
    
    #----------------------------------------------------------------------
    def cancelOrder(self, symbol, contractType, orderId, onSuccess, onFailed=None,
                    extra=None):  # type: (str, OkexFutureContractType, str, Callable[[object], Any], Callable[[Any], Any], Any)->Request
        """
        :param symbol: str
        :param contractType: OkexFutureContractType
        :param orderId: str
        :param onSuccess: ()->Any
        :param onFailed: ()->Any
        :param extra: Any
        :return: Request
        """
        data = {
            'symbol': symbol,
            'contractType': contractType,
            'order_id': orderId
        }
        return self.addReq('POST',
                           '/future_cancel.do',
                           callback=self.onOrderCanceled,
                           data=data,
                           extra=_OkexFutureCustomExtra(onSuccess, onFailed, extra))
    
    #----------------------------------------------------------------------
    def queryOrder(self, symbol, contractType, orderId, onSuccess, onFailed=None,
                   extra=None):  # type: (str, OkexFutureContractType, str, Callable[[OkexFutureOrder, Any], Any], Callable[[Any], Any], Any)->Request
        """
        :param symbol: str
        :param contractType: OkexFutureContractType
        :param orderId: str
        :param onSuccess: (OkexFutureOrder, extra:Any)->Any
        :param onFailed: (extra: Any)->Any
        :param extra: Any
        :return: Request
        """
        data = {
            'symbol': symbol,
            'contractType': contractType,
            'order_id': orderId
        }
        return self.addReq('POST',
                           '/future_order_info.do',
                           callback=self.onOrder,
                           data=data,
                           extra=_OkexFutureCustomExtra(onSuccess, onFailed, extra))
    
    #----------------------------------------------------------------------
    def queryUserInfo(self, onSuccess, onFailed=None,
                      extra=None):  # type: (Callable[[List[OkexFutureUserInfo], Any], Any], Callable[[Any], Any], Any)->Request
        """
        查询用户信息
        :param onSuccess: (userInfos: List[OkexFutureUserInfo], extra: Any)->Any
        :param onFailed: (extra: Any)->Any
        :param extra: Any
        :return: Request
        """
        return self.addReq('POST',
                           '/future_userinfo.do',
                           callback=self.onOrder,
                           extra=_OkexFutureCustomExtra(onSuccess, onFailed, extra))
    
    #----------------------------------------------------------------------
    def queryPosition(self, symbol, contractType,
                      onSuccess, onFailed=None,
                      extra=None):  # type: (str, OkexFutureContractType, Callable[[OkexFuturePosition, Any], Any], Callable[[Any], Any], Any)->Request
        data = {
            'symbol': symbol,
            'contractType': contractType
        }
        return self.addReq('POST',
                           '/future_position.do',
                           data=data,
                           callback=self.onPosition,
                           extra=_OkexFutureCustomExtra(onSuccess, onFailed, extra))
    
    #----------------------------------------------------------------------
    @staticmethod
    def onOrderSent(data, req):  # type: (dict, Request)->None
        """
        下单回执，一般用来保存sysId
        """
        extra = req.extra  # type: _OkexFutureCustomExtra
        if data['result'] is True:
            remoteId = data['order_id']
            extra.onSuccess(remoteId, extra.extra)
        else:
            if extra.onFailed:
                extra.onFailed(extra.extra)
    
    #----------------------------------------------------------------------
    @staticmethod
    def onOrderCanceled(data, req):  # type: (dict, Request)->None
        """
        取消订单回执
        """
        success = data['result']
        extra = req.extra  # type: _OkexFutureCustomExtra
        if success:
            extra.onSuccess(extra.extra)
        else:
            if extra.onFailed:
                extra.onFailed(extra.extra)
    
    #----------------------------------------------------------------------
    @staticmethod
    def onOrder(data, req):  # type: (dict, Request)->None
        success = data['result']
        extra = req.extra  # type: _OkexFutureCustomExtra
        if success:
            order = data['orders'][0]
            okexOrder = OkexFutureOrder()
            
            okexOrder.symbol = order['symbol']
            okexOrder.volume = order['amount']
            okexOrder.price = order['price']
            okexOrder.priceAvg = order['price_avg']
            okexOrder.status = order['status']
            okexOrder.orderType = order['type']
            okexOrder.unitAmount = order['unit_amount']
            okexOrder.leverRate = order['lever_rate']
            okexOrder.remoteId = order['order_id']
            okexOrder.fee = order['fee']
            okexOrder.tradedVolume = order['deal_amount']
            okexOrder.createDate = order['create_date']
            
            extra.onSuccess(okexOrder, extra.extra)
        else:
            if extra.onFailed:
                extra.onFailed(extra.extra)
    
    #----------------------------------------------------------------------
    @staticmethod
    def onUserInfo(data, req):  # type: (dict, Request)->None
        success = data['result']
        extra = req.extra  # type: _OkexFutureCustomExtra
        if success:
            infos = data['info']
            uis = []
            for symbol, info in infos.items():  # type: str, dict
                ui = OkexFutureUserInfo()
                ui.accountRights = info['account_rights']
                ui.keepDeposit = info['keep_deposit']
                ui.profitReal = info['profit_real']
                ui.profitUnreal = info['profit_unreal']
                ui.riskRate = info['risk_rate']
                uis.append(ui)
            extra.onSuccess(uis, extra.extra)
        else:
            if extra.onFailed:
                extra.onFailed(extra.extra)
    
    #----------------------------------------------------------------------
    @staticmethod
    def onPosition(data, req):  # type: (dict, Request)->None
        success = data['result']
        extra = req.extra  # type: _OkexFutureCustomExtra
        if success:
            pos = OkexFuturePosition()
            pos.forceLiquidatePrice = data['force_liqu_price']
            for item in data['holding']:
                posDetail = OkexFuturePositionDetail()
                posDetail.buyAmount = item['buy_amount']
                posDetail.buyAvailable = item['buy_available']
                posDetail.buyPriceAvg = item['buy_price_avg']
                posDetail.buyPriceCost = item['buy_price_cost']
                posDetail.buyProfitReal = item['buy_profit_real']
                posDetail.contractId = item['contract_id']
                posDetail.contractType = item['contract_type']
                posDetail.createDate = item['create_date']
                posDetail.leverRate = item['lever_rate']
                posDetail.sellAmount = item['sell_amount']
                posDetail.sellAvailable = item['sell_available']
                posDetail.sellPriceAvg = item['sell_price_avg']
                posDetail.sellPriceCost = item['sell_price_cost']
                posDetail.sellProfitReal = item['sell_profit_real']
                posDetail.symbol = item['symbol']
                pos.holding.append(posDetail)
            extra.onSuccess(pos, extra.extra)
        else:
            if extra.onFailed:
                extra.onFailed(extra.extra)
