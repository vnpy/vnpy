# encoding: UTF-8
from typing import Any, Callable, List, Union

from vnpy.api.okexfuture.vnokexFuture import OkexFutureRestBase, OkexFutureWebSocketBase
from vnpy.api.rest import Request


########################################################################
class _OkexFutureCustomExtra(object):
    
    def __init__(self, onSuccess, onFailed, extra):
        self.onFailed = onFailed
        self.onSuccess = onSuccess
        self.extra = extra


########################################################################
class OkexFutureEasySymbol(object):
    BTC = 'btc'
    LTC = 'ltc'
    ETH = 'eth'
    ETC = 'etc'
    BCH = 'bch'
    EOS = 'eos'
    XRP = 'xrp'
    BTG = 'btg'

    
########################################################################
class OkexFutureSymbol(object):
    BTC = 'btc_usd'
    LTC = 'ltc_usd'
    ETH = 'eth_usd'
    ETC = 'etc_usd'
    BCH = 'bch_usd'


########################################################################
class OkexFuturePriceType(object):
    Buy = 'buy'
    Sell = 'sell'


########################################################################
class OkexFutureContractType(object):
    ThisWeek = 'this_week'
    NextWeek = 'next_week'
    Quarter = 'quarter'


########################################################################
class OkexFutureOrderType(object):
    OpenLong = '1'
    OpenShort = '2'
    CloseLong = '3'
    CloseShort = '4'


########################################################################
class OkexFutureOrderStatus(object):
    NotFinished = '1'
    Finished = '2'


########################################################################
class OkexFutureOrder(object):
    
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
class OkexFutureUserInfo(object):
    
    #----------------------------------------------------------------------
    def __init__(self):
        self.easySymbol = None # 'etc', 'btc', 'eth', etc.
        self.accountRights = None
        self.keepDeposit = None
        self.profitReal = None
        self.profitUnreal = None
        self.riskRate = None


########################################################################
class OkexFuturePosition(object):
    
    #----------------------------------------------------------------------
    def __init__(self, ):
        self.forceLiquidatePrice = None
        self.holding = []  # type: List[OkexFuturePositionDetail]


########################################################################
class OkexFuturePositionDetail(object):
    
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
                  extra=None):  # type:(str, OkexFutureContractType, OkexFutureOrderType, float, Callable[[str, Any], Any], Callable[[int, Any], Any], float, bool, Union[int, None], Any)->Request
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
        
        request = self.addRequest('POST',
                              '/future_trade.do',
                                  callback=self.onOrderSent,
                                  data=data,
                                  extra=_OkexFutureCustomExtra(onSuccess, onFailed, extra))
        return request
    
    #----------------------------------------------------------------------
    def cancelOrder(self, symbol, contractType, orderId, onSuccess, onFailed=None,
                    extra=None):  # type: (str, OkexFutureContractType, str, Callable[[object], Any], Callable[[int, Any], Any], Any)->Request
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
        return self.addRequest('POST',
                           '/future_cancel.do',
                               callback=self.onOrderCanceled,
                               data=data,
                               extra=_OkexFutureCustomExtra(onSuccess, onFailed, extra))
    
    #----------------------------------------------------------------------
    def queryOrder(self, symbol, contractType, orderId, onSuccess, onFailed=None,
                   extra=None):  # type: (str, OkexFutureContractType, str, Callable[[List[OkexFutureOrder], Any], Any], Callable[[int, Any], Any], Any)->Request
        """
        @note onSuccess接收的第一个参数是列表，并且有可能为空
        
        :param symbol: str
        :param contractType: OkexFutureContractType
        :param orderId: str
        :param onSuccess: (orders: List[OkexFutureOrder], extra:Any)->Any
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
                               extra=_OkexFutureCustomExtra(onSuccess, onFailed, extra))

    #----------------------------------------------------------------------
    def queryOrders(self, symbol, contractType, status,
                    onSuccess, onFailed=None,
                    pageIndex=0, pageLength=50,
                    extra=None):  # type: (str, OkexFutureContractType, OkexFutureOrderStatus, Callable[[List[OkexFutureOrder], Any], Any], Callable[[int, Any], Any], int, int, Any)->Request
        """
        @note onSuccess接收的第一个参数是列表，并且有可能为空
        
        :param symbol: str
        :param contractType: OkexFutureContractType
        :param onSuccess: (List[OkexFutureOrder], extra:Any)->Any
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
                               extra=_OkexFutureCustomExtra(onSuccess, onFailed, extra))
    
    #----------------------------------------------------------------------
    def queryUserInfo(self, onSuccess, onFailed=None,
                      extra=None):  # type: (Callable[[List[OkexFutureUserInfo], Any], Any], Callable[[int, Any], Any], Any)->Request
        """
        查询用户信息
        :param onSuccess: (userInfos: List[OkexFutureUserInfo], extra: Any)->Any
        :param onFailed: (extra: Any)->Any
        :param extra: Any
        :return: Request
        """
        return self.addRequest('POST',
                           '/future_userinfo.do',
                               callback=self.onOrder,
                               extra=_OkexFutureCustomExtra(onSuccess, onFailed, extra))
    
    #----------------------------------------------------------------------
    def queryPosition(self, symbol, contractType,
                      onSuccess, onFailed=None,
                      extra=None):  # type: (str, OkexFutureContractType, Callable[[OkexFuturePosition, Any], Any], Callable[[int, Any], Any], Any)->Request
        """
        :param symbol: OkexFutureSymbol
        :param contractType: OkexFutureContractType
        :param onSuccess: (pos:OkexFuturePosition, extra: any)->Any
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
                code = 0
                if 'error_code' in data:
                    code = data['error_code']
                extra.onFailed(code, extra.extra)
    
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
                code = 0
                if 'error_code' in data:
                    code = data['error_code']
                extra.onFailed(code, extra.extra)
    
    #----------------------------------------------------------------------
    @staticmethod
    def onOrder(data, req):  # type: (dict, Request)->None
        success = data['result']
        extra = req.extra  # type: _OkexFutureCustomExtra
        if success:
            orders = []
            for order in data['orders']:
                okexOrder = OkexFutureOrder()
        
                okexOrder.volume = order['amount']
                okexOrder.contractName = order['contract_name']
                okexOrder.createDate = order['create_date']
                okexOrder.tradedVolume = order['deal_amount']
                okexOrder.fee = order['fee']
                okexOrder.leverRate = order['lever_rate']
                okexOrder.remoteId = order['order_id']
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
    def onUserInfo(data, req):  # type: (dict, Request)->None
        success = data['result']
        extra = req.extra  # type: _OkexFutureCustomExtra
        if success:
            infos = data['info']
            uis = []
            for easySymbol, info in infos.items():  # type: str, dict
                ui = OkexFutureUserInfo()
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
class OkexFutureWebSocketClient(OkexFutureWebSocketBase):
    
    #----------------------------------------------------------------------
    def subscribe(self, easySymbol, contractType):  # type: (OkexFutureEasySymbol, OkexFutureContractType)->None
        self.sendPacket({
            'event': 'addChannel',
            'channel': 'ok_sub_futureusd_' + easySymbol + '_ticker_' + contractType
        })
    

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
