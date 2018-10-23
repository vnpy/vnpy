# encoding: UTF-8
"""
# Okex Futures API V3 坑记：
* https://www.okex.com/api/futures/v3/instruments   返回值中的trade_increment有时候会变成quote_increment
* /api/futures/v3/order                             如果下单时不提供client_id，返回值将不会有client_id字段
* websocket居然还没升级好就把API放出来了？！

"""

from enum import Enum
from typing import Any, Callable, List, Union

from vnpy.api.okexfutures.OkexFuturesBase import OkexFuturesRestBaseV1, OkexFuturesRestBaseV3, \
    OkexFuturesWebSocketBase
from vnpy.api.rest import Request


########################################################################
class _OkexFuturesCustomExtra(object):
    
    #----------------------------------------------------------------------
    def __init__(self, onSuccess, onFailed, extra):
        self.onFailed = onFailed
        self.onSuccess = onSuccess
        self.extra = extra


########################################################################
class OkexFuturesEasySymbol(object):
    BTC = 'btc'
    LTC = 'ltc'
    ETH = 'eth'
    ETC = 'etc'
    BCH = 'bch'
    EOS = 'eos'
    XRP = 'xrp'
    BTG = 'btg'

    
########################################################################
class OkexFuturesSymbol(object):
    BTC = 'btc_usd'
    LTC = 'ltc_usd'
    ETH = 'eth_usd'
    ETC = 'etc_usd'
    BCH = 'bch_usd'


########################################################################
class OkexFuturesPriceType(object):
    Buy = 'buy'
    Sell = 'sell'


########################################################################
class OkexFuturesContractType(object):
    ThisWeek = 'this_week'
    NextWeek = 'next_week'
    Quarter = 'quarter'


########################################################################
class OkexFuturesOrderType(object):
    OpenLong = '1'
    OpenShort = '2'
    CloseLong = '3'
    CloseShort = '4'


########################################################################
class OkexFuturesOrderStatus(object):
    NotFinished = '1'
    Finished = '2'


########################################################################
class OkexFuturesOrder(object):
    
    #----------------------------------------------------------------------
    def __init__(self):
        self.volume = None
        self.contractName = None
        self.createDate = None
        self.tradedVolume = None
        self.fee = None
        self.leverRate = None
        self.remoteId = None
        self.price = None
        self.priceAvg = None
        self.status = None
        self.symbol = None
        self.orderType = None
        self.unitAmount = None


########################################################################
class OkexFuturesUserInfo(object):
    
    #----------------------------------------------------------------------
    def __init__(self):
        self.easySymbol = None # 'etc', 'btc', 'eth', etc.
        self.accountRights = None
        self.keepDeposit = None
        self.profitReal = None
        self.profitUnreal = None
        self.riskRate = None


########################################################################
class OkexFuturesPosition(object):
    
    #----------------------------------------------------------------------
    def __init__(self, ):
        self.forceLiquidatePrice = None
        self.holding = []  # type: List[OkexFuturesPositionDetail]


########################################################################
class OkexFuturesPositionDetail(object):
    
    #----------------------------------------------------------------------
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
class OkexFuturesTickInfo(object):
    
    #----------------------------------------------------------------------
    def __init__(self, symbol, remoteContractType, last, limitHigh, limitLow, vol, sell, buy,
                 unitAmount, holdAmount,
                 contractId, high, low):
        self.symbol = symbol
        self.remoteContractType = remoteContractType
        self.last = last
        self.limitHigh = limitHigh  # type: str  # 最高买入限制价格
        self.limitLow = limitLow  # type: str  # 最低卖出限制价格
        self.vol = vol  # type: float  # 24 小时成交量
        self.sell = sell  # type: float  # 卖一价格
        self.buy = buy  # type: float  #  买一价格
        self.unitAmount = unitAmount  # type: float  # 合约价值
        self.holdAmount = holdAmount  # type: float  # 当前持仓量
        self.contractId = contractId  # type: long  # 合约ID
        self.high = high  # type: float  # 24 小时最高价格
        self.low = low  # type: float  # 24 小时最低价格


########################################################################
class OkexFuturesTradeInfo(object):
    
    #----------------------------------------------------------------------
    def __init__(self, symbol, remoteContractType, index, price, volume, time, direction, coinVolume):
        self.symbol = symbol
        self.remoteContractType = remoteContractType
        self.index = index
        self.price = price
        self.volume = volume
        self.time = time
        self.direction = direction
        self.coinVolume = coinVolume


########################################################################
class OkexFuturesUserTradeInfo(object):
    
    #----------------------------------------------------------------------
    def __init__(self, symbol, remoteContractType, amount,
                 contractName, createdDate, createDateStr, dealAmount, fee,
                 orderId, price, priceAvg, status, type, unitAmount, leverRate, systemType
                 ):
        self.symbol = symbol  # type: str  #  btcUsd   ltcUsd   ethUsd   etcUsd   bchUsd
        self.remoteContractType = remoteContractType
        self.amount = amount  # type: float  #  委托数量
        self.contractName = contractName  # type: str  #  合约名称
        self.createdDate = createdDate  # type: long  #  委托时间
        self.createDateStr = createDateStr  # type: str  # 委托时间字符串
        self.dealAmount = dealAmount  # type: float  #  成交数量
        self.fee = fee  # type: float  #  手续费
        self.remoteId = orderId  # type: long  #  订单ID
        self.price = price  # type: float  #  订单价格
        self.priceAvg = priceAvg  # type: float  #  平均价格
        self.status = status  # type: int  #  订单状态(0等待成交 1部分成交 2全部成交 -1撤单 4撤单处理中)
        self.type = type  # type: int  #  订单类型 1：开多 2：开空 3：平多 4：平空
        self.unitAmount = unitAmount  # type: float  # 合约面值
        self.leverRate = leverRate  # type: float  # 杠杆倍数  value:10/20  默认10
        self.systemType = systemType  # type: int  # 订单类型 0:普通 1:交割 2:强平 4:全平 5:系统反单


########################################################################
class OkexFuturesContractsInfoV3(object):
    
    #----------------------------------------------------------------------
    def __init__(self,
                 instrumentId,
                 underlyingIndex,
                 quoteCurrency,
                 quote_increment,
                 contractVal,
                 listing,
                 delivery,
                 tickSize,
                 ):
        self.symbol = instrumentId              # String    # 合约ID，如BTC-USD-180213
        self.underlyingIndex = underlyingIndex  # String    # 交易货币币种，如：btc-usdt中的btc
        self.quoteCurrency = quoteCurrency      # String    # 计价货币币种，如：btc-usdt中的usdt
        self.quoteIncrement = quote_increment    # Number    # 下单数量精度
        self.contractVal = contractVal          # Number    # 合约面值(美元)
        self.listing = listing                  # Date      # 上线日期
        self.delivery = delivery                # Date      # 交割日期
        self.tickSize = tickSize                # Number    # 下单价格精度


########################################################################
class OkexFuturesAccountInfoV3(object):
    
    #----------------------------------------------------------------------
    def __init__(self, currency, balance, hold, available):
        self.currency = currency                # String    # 币种
        self.balance = balance                  # number    # 余额
        self.hold = hold                        # number    # 冻结(不可用)
        self.available = available              # number    # 可用于提现或资金划转的数量
        

########################################################################
class OkexFuturesPositionInfoV3(object):
    
    #----------------------------------------------------------------------
    def __init__(self, marginMode, liquidationPrice, longQty, longAvailQty, longAvgCost,
                 longSettlementPrice,
                 realizedPnl, shortQty, shortAvailQty, shortAvgCost, shortSettlementPrice,
                 instrumentId,
                 leverage, createAt, updatAt,
                 ):
        self.marginMode = marginMode                        # String    # 账户类型：全仓 crossed
        self.liquidationPrice = liquidationPrice            # Price     # 预估爆仓价
        self.longQty = longQty                              # Number    # 多仓数量
        self.longAvailQty = longAvailQty                    # Number    # 多仓可平仓数量
        self.longAvgCost = longAvgCost                      # Price     # 开仓平均价
        self.longSettlementPrice = longSettlementPrice      # Price     # 多仓结算基准价
        self.realizedPnl = realizedPnl                      # Number    # 已实现盈余
        self.shortQty = shortQty                            # Number    # 空仓数量
        self.shortAvailQty = shortAvailQty                  # Number    # 空仓可平仓数量
        self.shortAvgCost = shortAvgCost                    # Price     # 开仓平均价
        self.shortSettlementPrice = shortSettlementPrice    # String    # 空仓结算基准价
        self.symbol = instrumentId                          # Number    # 合约ID，如BTC-USD-180213
        self.leverage = leverage                            # Date      # 杠杆倍数
        self.createAt = createAt                            # Date      # 创建时间
        self.updatAt = updatAt                              # Date      # 更新时间


########################################################################
class OkexFuturesOrderSentInfoV3(object):
    
    #----------------------------------------------------------------------
    def __init__(self, orderId, clientOid, errorCode, errorMessage):
        self.orderId = orderId                # String   # 订单ID，下单失败时，此字段值为-1
        self.clientOid = clientOid            # String   # 由您设置的订单ID来识别您的订单
        self.errorCode = errorCode            # Number   # 错误码，下单成功时为0，下单失败时会显示相应错误码
        self.errorMessage = errorMessage      # String   # 错误信息，下单成功时为空，下单失败时会显示错误信息


########################################################################
class OkexFuturesOrderDetailV3(object):
    
    #----------------------------------------------------------------------
    def __init__(self, instrumentId, size, timestamp, filledQty, fee, orderId, price, priceAvg,
                 status, orderType, contractVal, leverage, ):
        self.symbol = instrumentId          # String    # 合约ID，如BTC-USD-180213
        self.volume = size                  # Number    # 数量
        self.timestamp = timestamp          # Date      # 委托时间
        self.tradedVolume = filledQty       # Number    # 成交数量
        self.fee = fee                      # Price     # 手续费
        self.remoteId = orderId             # String    # 订单ID
        self.price = price                  # Price     # 订单价格
        self.priceAvg = priceAvg            # Price     # 平均价格
        self.status = status                # Number    # 订单状态(0:等待成交 1:部分成交 2:已完成）
        self.orderType = orderType          # Number    # 订单类型(1:开多 2:开空 3:开多 4:平空)
        self.contractVal = contractVal      # Price     # 合约面值
        self.leverage = leverage            # Number    # 杠杆倍数 value:10/20 默认10
        
    
########################################################################
class OkexFuturesRestClientV3(OkexFuturesRestBaseV3):
    """
    Okex新出了V3版本的API，这里用的是V3的版本
    """
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(OkexFuturesRestClientV3, self).__init__()

    #----------------------------------------------------------------------
    def sendOrder(self,
                  symbol,
                  orderType,
                  price,
                  volume,
                  leverRate,        # type: int     # 档杆倍数，10或者20
                  onSuccess,        # type: Callable[[OkexFuturesOrderSentInfoV3, Any], Any]
                  onFailed=None,    # type: Callable[[OkexFuturesOrderSentInfoV3, Any], Any]
                  matchPrice=False, # type: bool    # 是否为市价单
                  clientOid=None,    # type: str     # OkexAPI提供的的用户自定义字段
                  extra=None
                  ):
        """ 下单 """
        data = {
            'client_oid': clientOid,
            'instrument_id': symbol,
            'type': orderType,
            'size': volume,
            'leverage': leverRate,
            
            'price': price,
            'match_price': '0'
        }
        # if matchPrice:
        #     data['match_price'] = '1'
        # else:
        #     data['price'] = price
        
        return self.addRequest('POST', '/api/futures/v3/order',
                               callback=self._onOrderSent,
                               data=data,
                               extra=_OkexFuturesCustomExtra(onSuccess, onFailed, extra)
                               )
    
    #----------------------------------------------------------------------
    def cancelOrder(self,
                    symbol,         # type: str
                    remoteId,       # type: str
                    onSuccess,      # type: Callable[[Any], Any]
                    onFailed=None,  # type: Callable[[Any], Any]
                    extra=None
                    ):              # type: (...)->Request
        """撤单"""
        path = '/api/futures/v3/cancel_order/' + symbol + '/' + remoteId
        return self.addRequest('POST', path,
                               callback=self._onOrderCanceled,
                               data={
                                   'instrument_id' : symbol,
                                   'order_id': remoteId
                               },
                               extra=_OkexFuturesCustomExtra(onSuccess, onFailed, extra)
                               )
    
    #----------------------------------------------------------------------
    def queryAccount(self,
                     onSuccess, # type: Callable[[List[OkexFuturesAccountInfoV3], Any], Any]
                     extra=None
                     ):         # type: (...)->Request
        """
        查询全部账户资金
        """
        return self.addRequest('GET', '/api/account/v3/wallet',
                               callback=self._onAccounts,
                               extra=_OkexFuturesCustomExtra(onSuccess, None, extra)
                               )

    #----------------------------------------------------------------------
    def queryOrders(self,
                    symbol,
                    status,             # type: OkexFuturesOrderStatus
                    onSuccess,          # type: Callable[[List[OkexFuturesOrderDetailV3], Any], Any]
                    onFailed=None,      # type: Callable[[Any], Any]
                    startPage=0,        # type: int  # 取回的页数区间为：(start, end)
                    endPage=2,          # type: int  # 取回的页数区间为：(start, end)
                    numberPerPage=100,  # type: int
                    extra=None
                    ):                  # type: (...)->Request
        """查询账户订单"""
        path = '/api/futures/v3/orders/' + symbol
        return self.addRequest("POST", path,
                               data={
                                   'status': status,
                                   'instrument_id': symbol,
                                   'from': startPage,
                                   'to': endPage,
                                   'limit': numberPerPage,
                               },
                               callback=self._onOrders,
                               extra=_OkexFuturesCustomExtra(onSuccess, onFailed, extra)
                               )
    
    #----------------------------------------------------------------------
    def queryPositions(self,
                       onSuccess,
                       extra=None):
        """ 获取全部持仓 """
        return self.addRequest('GET', '/api/account/v3/position',
                               callback=self._onPositions,
                               extra=_OkexFuturesCustomExtra(onSuccess, None, extra)
                               )

    #----------------------------------------------------------------------
    def queryContracts(self,
                       onSuccess,   # type: Callable[[List[OkexFuturesContractsInfoV3], Any], Any]
                       extra=None):
        """ 获取全部合约信息 """
        return self.addRequest('GET', '/api/futures/v3/instruments',
                               callback=self._onContracts,
                               extra=_OkexFuturesCustomExtra(onSuccess, None, extra)
                               )
    
    #----------------------------------------------------------------------
    @staticmethod
    def _onOrderSent(data, request):  #type: (dict, Request)->None
        """下单回调"""
        extra = request.extra  # type: _OkexFuturesCustomExtra
        order = OkexFuturesOrderSentInfoV3(
            data['order_id'],
            data['client_oid'] if 'client_oid' in data else None,
            data['error_code'],
            data['error_message'],
        )
        if order.orderId != '-1':
            extra.onSuccess(order, extra.extra)
        else:
            if extra.onFailed:
                extra.onFailed(order, extra.extra)

    #----------------------------------------------------------------------
    def _onOrderCanceled(self, data, request):  #type: (dict, Request)->None
        """撤单回调"""
        extra = request.extra  # type: _OkexFuturesCustomExtra
        result = data['result']
        if result is True:
            extra.onSuccess(extra.extra)
        else:
            if extra.onFailed:
                extra.onFailed(extra.extra)
            
    #----------------------------------------------------------------------
    @staticmethod
    def _onAccounts(data, request):  #type: (dict, Request)->None
        """账户资金回调"""
        extra = request.extra  # type: _OkexFuturesCustomExtra
        accs = []
        for acc in data:
            accs.append(OkexFuturesAccountInfoV3(
                acc['currency'],
                acc['balance'],
                acc['hold'],
                acc['available'],
            ))
        extra.onSuccess(accs, extra.extra)
        
    #----------------------------------------------------------------------
    @staticmethod
    def _onOrders(data, request):  #type: (dict, Request)->None
        """
        查询订单回调
        https://www.okex.com/docs/zh/#futures-list
        """
        extra = request.extra  # type: _OkexFuturesCustomExtra
        if data['result'] is True:
            os = []
            for info in data['orders']:
                os.append(OkexFuturesOrderDetailV3(
                    info['instrument_id'],
                    info['size'],
                    info['timestamp'],
                    info['filled_qty'],
                    info['fee'],
                    info['order_id'],
                    info['price'],
                    info['price_avg'],
                    info['status'],
                    info['type'],
                    info['contract_val'],
                    info['leverage'],
                ))
            extra.onSuccess(os, extra.extra)
        else:
            if extra.onFailed:
                extra.onFailed(extra.extra)
                
        
    #----------------------------------------------------------------------
    @staticmethod
    def _onPositions(data, request):  #type: (dict, Request)->None
        extra = request.extra  # type: _OkexFuturesCustomExtra
        accs = []
        for acc in data:
            accs.append(OkexFuturesPositionInfoV3(
                acc['margin_mode'],
                acc['liquidation_price'],
                acc['long_qty'],
                acc['long_avail_qty'],
                acc['long_avg_cost'],
                acc['long_settlement_price'],
                acc['realized_pnl'],
                acc['short_qty'],
                acc['short_avail_qty'],
                acc['short_avg_cost'],
                acc['short_settlement_price'],
                acc['instrument_id'],
                acc['leverage'],
                acc['create_at'],
                acc['updat_at'],
            ))
        extra.onSuccess(accs, extra.extra)

    #----------------------------------------------------------------------
    @staticmethod
    def _onContracts(data, request):  #type: (dict, Request)->None
        """
        合约信息回调
        https://www.okex.com/docs/zh/#futures-contract_information
        """
        extra = request.extra  # type: _OkexFuturesCustomExtra
        ins = []
        for instrument in data:
            ins.append(OkexFuturesContractsInfoV3(
                instrument['instrument_id'],
                instrument['underlying_index'],
                instrument['quote_currency'],
                instrument['quote_increment'] if 'quote_increment' in instrument else instrument['trade_increment'],
                instrument['contract_val'],
                instrument['listing'],
                instrument['delivery'],
                instrument['tick_size'],
            ))
        extra.onSuccess(ins, extra.extra)
    

########################################################################
class OkexFuturesRestClientV1(OkexFuturesRestBaseV1):
    """
    这里用的是旧的v1版本的OkexAPI
    """
    
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(OkexFuturesRestClientV1, self).__init__()
    
    #----------------------------------------------------------------------
    def sendOrder(self, symbol, contractType, orderType, volume,
                  onSuccess, onFailed=None,
                  price=None, useMarketPrice=False, leverRate=None,
                  extra=None):  # type:(str, OkexFuturesContractType, OkexFuturesOrderType, float, Callable[[str, Any], Any], Callable[[int, Any], Any], float, bool, Union[int, None], Any)->Request
        """
        :param symbol: str
        :param contractType: OkexFuturesContractType
        :param orderType: OkexFuturesOrderType
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
        
        request = self.addRequest('POST',
                              '/future_trade.do',
                                  callback=self.onOrderSent,
                                  data=data,
                                  extra=_OkexFuturesCustomExtra(onSuccess, onFailed, extra))
        return request
    
    #----------------------------------------------------------------------
    def cancelOrder(self, symbol, contractType, orderId, onSuccess, onFailed=None,
                    extra=None):  # type: (str, OkexFuturesContractType, str, Callable[[object], Any], Callable[[int, Any], Any], Any)->Request
        """
        :param symbol: str
        :param contractType: OkexFuturesContractType
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
        return self.addRequest('POST',
                           '/future_cancel.do',
                               callback=self.onOrderCanceled,
                               data=data,
                               extra=_OkexFuturesCustomExtra(onSuccess, onFailed, extra))
    
    #----------------------------------------------------------------------
    def queryOrder(self, symbol, contractType, orderId, onSuccess, onFailed=None,
                   extra=None):  # type: (str, OkexFuturesContractType, str, Callable[[List[OkexFuturesOrder], Any], Any], Callable[[int, Any], Any], Any)->Request
        """
        @note onSuccess接收的第一个参数是列表，并且有可能为空
        
        :param symbol: str
        :param contractType: OkexFuturesContractType
        :param orderId: str
        :param onSuccess: (orders: List[OkexFuturesOrder], extra:Any)->Any
        :param onFailed: (extra: Any)->Any
        :param extra: Any
        :return: Request
        """
        data = {
            'symbol': symbol,
            'contractType': contractType,
            'order_id': orderId
        }
        return self.addRequest('POST',
                           '/future_order_info.do',
                               callback=self.onOrder,
                               data=data,
                               extra=_OkexFuturesCustomExtra(onSuccess, onFailed, extra))

    #----------------------------------------------------------------------
    def queryOrders(self, symbol, contractType, status,
                    onSuccess, onFailed=None,
                    pageIndex=0, pageLength=50,
                    extra=None):  # type: (str, OkexFuturesContractType, OkexFuturesOrderStatus, Callable[[List[OkexFuturesOrder], Any], Any], Callable[[int, Any], Any], int, int, Any)->Request
        """
        @note onSuccess接收的第一个参数是列表，并且有可能为空
        
        :param symbol: str
        :param contractType: OkexFuturesContractType
        :param onSuccess: (List[OkexFuturesOrder], extra:Any)->Any
        :param onFailed: (extra: Any)->Any
        :param pageIndex: 页码
        :param pageLength: 最大显示数量（最大值50）
        :param extra: Any
        :return: Request
        """
        data = {
            'symbol': symbol,
            'contract_type': contractType,
            'status': status,
            'order_id': -1,
            'current_page': pageIndex,
            'page_length': pageLength
        }

        return self.addRequest('POST',
                           '/future_order_info.do',
                               callback=self.onOrder,
                               data=data,
                               extra=_OkexFuturesCustomExtra(onSuccess, onFailed, extra))
    
    #----------------------------------------------------------------------
    def queryUserInfo(self, onSuccess, onFailed=None,
                      extra=None):  # type: (Callable[[List[OkexFuturesUserInfo], Any], Any], Callable[[int, Any], Any], Any)->Request
        """
        查询用户信息
        :param onSuccess: (userInfos: List[OkexFuturesUserInfo], extra: Any)->Any
        :param onFailed: (extra: Any)->Any
        :param extra: Any
        :return: Request
        """
        return self.addRequest('POST',
                           '/future_userinfo.do',
                               callback=self.onOrder,
                               extra=_OkexFuturesCustomExtra(onSuccess, onFailed, extra))
    
    #----------------------------------------------------------------------
    def queryPosition(self, symbol, contractType,
                      onSuccess, onFailed=None,
                      extra=None):  # type: (str, OkexFuturesContractType, Callable[[OkexFuturesPosition, Any], Any], Callable[[int, Any], Any], Any)->Request
        """
        :param symbol: OkexFuturesSymbol
        :param contractType: OkexFuturesContractType
        :param onSuccess: (pos:OkexFuturesPosition, extra: any)->Any
        :param onFailed: (errorCode: int, extra: any)->Any
        :param extra:
        :return:
        """
        data = {
            'symbol': symbol,
            'contractType': contractType
        }
        return self.addRequest('POST',
                           '/future_position.do',
                               data=data,
                               callback=self.onPosition,
                               extra=_OkexFuturesCustomExtra(onSuccess, onFailed, extra))
    
    #----------------------------------------------------------------------
    @staticmethod
    def onOrderSent(data, request):  # type: (dict, Request)->None
        """
        下单回执，一般用来保存sysId
        """
        extra = request.extra  # type: _OkexFuturesCustomExtra
        if data['result'] is True:
            remoteId = data['order_id']
            extra.onSuccess(remoteId, extra.extra)
        else:
            if extra.onFailed:
                code = 0
                if 'error_code' in data:
                    code = data['error_code']
                extra.onFailed(code, extra.extra)
    
    #----------------------------------------------------------------------
    @staticmethod
    def onOrderCanceled(data, request):  # type: (dict, Request)->None
        """
        取消订单回执
        """
        success = data['result']
        extra = request.extra  # type: _OkexFuturesCustomExtra
        if success:
            extra.onSuccess(extra.extra)
        else:
            if extra.onFailed:
                code = 0
                if 'error_code' in data:
                    code = data['error_code']
                extra.onFailed(code, extra.extra)
    
    #----------------------------------------------------------------------
    @staticmethod
    def onOrder(data, request):  # type: (dict, Request)->None
        success = data['result']
        extra = request.extra  # type: _OkexFuturesCustomExtra
        if success:
            orders = []
            for order in data['orders']:
                okexOrder = OkexFuturesOrder()
        
                okexOrder.volume = order['amount']
                okexOrder.contractName = order['contract_name']
                okexOrder.createDate = order['create_date']
                okexOrder.tradedVolume = order['deal_amount']
                okexOrder.fee = order['fee']
                okexOrder.leverRate = order['lever_rate']
                okexOrder.remoteId = str(order['orderId'])
                okexOrder.price = order['price']
                okexOrder.priceAvg = order['price_avg']
                okexOrder.status = order['status']
                okexOrder.orderType = order['type']
                okexOrder.unitAmount = order['unit_amount']
                okexOrder.symbol = order['symbol']
                orders.append(okexOrder)
            extra.onSuccess(orders, extra.extra)
        else:
            if extra.onFailed:
                code = 0
                if 'error_code' in data:
                    code = data['error_code']
                extra.onFailed(code, extra.extra)
    
    #----------------------------------------------------------------------
    @staticmethod
    def onUserInfo(data, request):  # type: (dict, Request)->None
        success = data['result']
        extra = request.extra  # type: _OkexFuturesCustomExtra
        if success:
            infos = data['info']
            uis = []
            for easySymbol, info in infos.items():  # type: str, dict
                ui = OkexFuturesUserInfo()
                ui.easySymbol = easySymbol
                ui.accountRights = info['account_rights']
                ui.keepDeposit = info['keep_deposit']
                ui.profitReal = info['profit_real']
                ui.profitUnreal = info['profit_unreal']
                ui.riskRate = info['risk_rate']
                uis.append(ui)
            extra.onSuccess(uis, extra.extra)
        else:
            if extra.onFailed:
                code = 0
                if 'error_code' in data:
                    code = data['error_code']
                extra.onFailed(code, extra.extra)
    
    #----------------------------------------------------------------------
    @staticmethod
    def onPosition(data, request):  # type: (dict, Request)->None
        success = data['result']
        extra = request.extra  # type: _OkexFuturesCustomExtra
        if success:
            pos = OkexFuturesPosition()
            pos.forceLiquidatePrice = data['force_liqu_price']
            for item in data['holding']:
                posDetail = OkexFuturesPositionDetail()
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
                code = 0
                if 'error_code' in data:
                    code = data['error_code']
                extra.onFailed(code, extra.extra)

    #---------------------------------------------------------------------
    @staticmethod
    def errorCodeToString(code):
        assert code in restErrorCodeMap
        return restErrorCodeMap[code]


########################################################################
class OkexFuturesWebSocketClient(OkexFuturesWebSocketBase):

    #----------------------------------------------------------------------
    def __init__(self):
        super(OkexFuturesWebSocketClient, self).__init__()
        self.onTick = self.defaultOnTick
        self.onUserTrade = self.defaultOnUserTrade

    #----------------------------------------------------------------------
    def subscribe(self, easySymbol, contractType):  # type: (OkexFuturesEasySymbol, OkexFuturesContractType)->None
        self.sendPacket({
            'event': 'addChannel',
            'channel': 'ok_sub_futureusd_' + easySymbol + '_ticker_' + contractType
        })
    
    #----------------------------------------------------------------------
    def subscribeUserTrade(self):
        self.sendPacket({
            'event': 'addChannel',
            'channel': 'ok_sub_futureusd_trades'
        })
    
    #----------------------------------------------------------------------
    def onPacket(self, packets):
        
        for packet in packets:
            channelName = None
            if 'channel' in packet:
                channelName = packet['channel']
            if not channelName or channelName == 'addChannel':
                return
            
            packet = packet['data']
            channel = parseChannel(channelName)  # type: ExtraSymbolChannel
            
            if channel.type == ChannelType.Tick:
                self.onTick(OkexFuturesTickInfo(
                    symbol=channel.symbol,
                    remoteContractType=channel.remoteContractType,
                    last=packet['last'],
                    limitHigh=packet['limitHigh'],
                    limitLow=packet['limitLow'],
                    vol=packet['vol'],
                    sell=packet['sell'],
                    buy=packet['buy'],
                    unitAmount=packet['unitAmount'],
                    holdAmount=packet['hold_amount'],
                    contractId=packet['contractId'],
                    high=packet['high'],
                    low=packet['low'],
                ))
            # elif channel.type == ChannelType.Trade:
            #     trades = []
            #     for tradeInfo in packet:
            #         trades.append(OkexFuturesTradeInfo(
            #             channel.symbol, channel.remoteContractType, *tradeInfo
            #         ))
            #     self.onTrades(trades)
            
            elif channel.type == ChannelType.UserTrade:
                self.onUserTrade(OkexFuturesUserTradeInfo(
                    symbol=packet['symbol'],
                    remoteContractType=packet['contract_type'],
                    amount=packet['amount'],
                    contractName=packet['contract_name'],
                    createdDate=packet['created_date'],
                    createDateStr=packet['create_date_str'],
                    dealAmount=packet['deal_amount'],
                    fee=packet['fee'],
                    orderId=packet['order_id'],
                    price=packet['price'],
                    priceAvg=packet['price_avg'],
                    status=packet['status'],
                    type=packet['type'],
                    unitAmount=packet['unit_amount'],
                    leverRate=packet['lever_rate'],
                    systemType=packet['system_type'],
                ))
    
    #----------------------------------------------------------------------
    def defaultOnTick(self, tick):  # type: (OkexFuturesTickInfo)->None
        pass
    
    #----------------------------------------------------------------------
    def defaultOnUserTrade(self, tick):  # type: (OkexFuturesUserTradeInfo)->None
        pass


restErrorCodeMap = {
    0: '远程服务器并未给出错误代码',
    
    20001: '用户不存在',
    20002: '用户被冻结',
    20003: '用户被爆仓冻结',
    20004: '合约账户被冻结',
    20005: '用户合约账户不存在',
    20006: '必填参数为空',
    20007: '参数错误',
    20008: '合约账户余额为空',
    20009: '虚拟合约状态错误',
    20010: '合约风险率信息不存在',
    20011: '10倍/20倍杠杆开BTC前保证金率低于90%/80%，10倍/20倍杠杆开LTC前保证金率低于80%/60%',
    20012: '10倍/20倍杠杆开BTC后保证金率低于90%/80%，10倍/20倍杠杆开LTC后保证金率低于80%/60%',
    20013: '暂无对手价',
    20014: '系统错误',
    20015: '订单信息不存在',
    20016: '平仓数量是否大于同方向可用持仓数量',
    20017: '非本人操作',
    20018: '下单价格高于前一分钟的103%或低于97%',
    20019: '该IP限制不能请求该资源',
    20020: '密钥不存在',
    20021: '指数信息不存在',
    20022: '接口调用错误（全仓模式调用全仓接口，逐仓模式调用逐仓接口）',
    20023: '逐仓用户',
    20024: 'sign签名不匹配',
    20025: '杠杆比率错误',
    20026: 'API鉴权错误',
    20027: '无交易记录',
    20028: '合约不存在',
    20029: '转出金额大于可转金额',
    20030: '账户存在借款',
    20038: '根据相关法律，您所在的国家或地区不能使用该功能。',
    20049: '用户请求接口过于频繁',
    20061: '合约相同方向只支持一个杠杆，若有10倍多单，就不能再下20倍多单',
    21005: '请求接口失败，请您重试',
    21020: '合约交割中，无法下单',
    21021: '合约清算中，无法下单',
    21023: '当前全仓方向仓位已超过最大可开张数',
    21024: '当前逐仓方向仓位已超过最大可开张数',
    21025: '下单后保证金率小于对应档位要求的最低保证金率',
    21026: '您的账户已被限制开仓操作',
    20119: '接口已下线或无法使用',
}

webSocketErrorCodeMap = {
    10000: '必填参数为空',
    10001: '参数错误',
    10002: '验证失败',
    10003: '该连接已经请求了其他用户的实时交易数据',
    10004: '该连接没有请求此用户的实时交易数据',
    10005: 'api_key或者sign不合法',
    10008: '非法参数',
    10009: '订单不存在',
    10010: '余额不足',
    10011: '卖的数量小于BTC/LTC最小买卖额度',
    10012: '当前网站暂时只支持btc_usd ltc_usd',
    10014: '下单价格不得≤0或≥1000000',
    10015: '暂不支持此channel订阅',
    10016: '币数量不足',
    10017: 'WebSocket鉴权失败',
    10100: '用户被冻结',
    10049: '小额委托（<0.15BTC)的未成交委托数量不得大于50个',
    10216: '非开放API',
    20001: '用户不存在',
    20002: '用户被冻结',
    20003: '用户被爆仓冻结',
    20004: '合约账户被冻结',
    20005: '用户合约账户不存在',
    20006: '必填参数为空',
    20007: '参数错误',
    20008: '合约账户余额为空',
    20009: '虚拟合约状态错误',
    20010: '合约风险率信息不存在',
    20011: '开仓前保证金率超过90%',
    20012: '开仓后保证金率超过90%',
    20013: '暂无对手价',
    20014: '系统错误',
    20015: '订单信息不存在',
    20016: '平仓数量是否大于同方向可用持仓数量',
    20017: '非本人操作',
    20018: '下单价格高于前一分钟的105%或低于95%',
    20019: '该IP限制不能请求该资源',
    20020: '密钥不存在',
    20021: '指数信息不存在',
    20022: '接口调用错误',
    20023: '逐仓用户',
    20024: 'sign签名不匹配',
    20025: '杠杆比率错误',
    20100: '请求超时',
    20101: '数据格式无效',
    20102: '登录无效',
    20103: '数据事件类型无效',
    20104: '数据订阅类型无效',
    20107: 'JSON格式错误',
    20115: 'quote参数未匹配到',
    20116: '参数不匹配',
    1002: '交易金额大于余额',
    1003: '交易金额小于最小交易值',
    1004: '交易金额小于0',
    1007: '没有交易市场信息',
    1008: '没有最新行情信息',
    1009: '没有订单',
    1010: '撤销订单与原订单用户不一致',
    1011: '没有查询到该用户',
    1013: '没有订单类型',
    1014: '没有登录',
    1015: '没有获取到行情深度信息',
    1017: '日期参数错误',
    1018: '下单失败',
    1019: '撤销订单失败',
    1024: '币种不存在',
    1025: '没有K线类型',
    1026: '没有基准币数量',
    1027: '参数不合法可能超出限制',
    1028: '保留小数位失败',
    1029: '正在准备中',
    1030: '有融资融币无法进行交易',
    1031: '转账余额不足',
    1032: '该币种不能转账',
    1035: '密码不合法',
    1036: '谷歌验证码不合法',
    1037: '谷歌验证码不正确',
    1038: '谷歌验证码重复使用',
    1039: '短信验证码输错限制',
    1040: '短信验证码不合法',
    1041: '短信验证码不正确',
    1042: '谷歌验证码输错限制',
    1043: '登陆密码不允许与交易密码一致',
    1044: '原密码错误',
    1045: '未设置二次验证',
    1046: '原密码未输入',
    1048: '用户被冻结',
    1050: '订单已撤销或者撤销中',
    1051: '订单已完成交易',
    1201: '账号零时删除',
    1202: '账号不存在',
    1203: '转账金额大于余额',
    1204: '不同种币种不能转账',
    1205: '账号不存在主从关系',
    1206: '提现用户被冻结',
    1207: '不支持转账',
    1208: '没有该转账用户',
    1209: '当前api不可用',
}


########################################################################
class ChannelType(Enum):
    Login = 1
    ForecastPrice = 2
    Tick = 3
    Depth = 4
    Trade = 5
    Index = 6
    UserTrade = 7
    UserInfo = 8


########################################################################
class Channel(object):
    
    #----------------------------------------------------------------------
    def __init__(self, type):
        self.type = type


########################################################################
class SymbolChannel(Channel):
    
    #----------------------------------------------------------------------
    def __init__(self, type, symbol):
        super(SymbolChannel, self).__init__(type)
        self.symbol = symbol


########################################################################
class FutureSymbolChannel(SymbolChannel):
    
    #----------------------------------------------------------------------
    def __init__(self, type, symbol, remoteContractType):
        super(FutureSymbolChannel, self).__init__(type, symbol)
        self.remoteContractType = remoteContractType


########################################################################
class ExtraSymbolChannel(FutureSymbolChannel):
    
    #----------------------------------------------------------------------
    def __init__(self, type, symbol, remoteContractType, extra):
        super(ExtraSymbolChannel, self).__init__(type, symbol, remoteContractType)
        self.extra = extra


#----------------------------------------------------------------------
def parseChannel(channel):  # type: (str)->Channel
    if channel == 'login':
        return Channel(ChannelType.Login)
    
    # 还未提供订阅的channel都注释掉
    # elif channel[4:12] == 'forecast':  # eg: 'btc_forecast_price'
    #     return SymbolChannel(ChannelType.ForecastPrice, channel[:3])
    
    sp = channel.split('_')
    if sp[-1] == 'trades':  # eg: 'ok_sub_futureusd_trades'
        return Channel(ChannelType.UserTrade)
    # if sp[-1] == 'userinfo':  # eg: 'ok_sub_futureusd_btc_userinfo'
    #     return Channel(ChannelType.UserInfo)
    # if sp[-1] == 'index':  # eg: 'ok_sub_futureusd_btc_index'
    #     return SymbolChannel(ChannelType.Index, channel[17:20])
    
    # if len(sp) == 9:
    #     _, _, _, easySymbol, crash, typeName, contractTypePrefix, _, depth = sp
    #     return ExtraSymbolChannel(ChannelType.Depth, easySymbol + '_' + crash,
    #                               remotePrefixToRemoteContractType(contractTypePrefix),
    #                               depth)
    _, _, _, easySymbol, crash, typeName, contractTypePrefix, _ = sp
    return FutureSymbolChannel(ChannelType.Tick, easySymbol + '_' + crash,
                               remotePrefixToRemoteContractType(contractTypePrefix))


#----------------------------------------------------------------------
def remotePrefixToRemoteContractType(prefix):
    return _prefixForRemoteContractType[prefix]


_prefixForRemoteContractType = {v.split('_')[0]: v for k, v in OkexFuturesContractType.__dict__.items() if
                                not k.startswith('_')}
