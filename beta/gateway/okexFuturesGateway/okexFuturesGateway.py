# encoding: UTF-8

from __future__ import print_function

import json
import sys
import traceback
import zlib
from collections import defaultdict

from enum import Enum
from typing import Dict, List

from vnpy.api.rest import Request
from vnpy.trader.gateway.okexFuturesGateway.OkexFuturesBase import \
    OkexFuturesRestBaseV3, \
    OkexFuturesWebSocketBase
from vnpy.trader.vtFunction import getJsonPath
from vnpy.trader.vtGateway import *


########################################################################
class ApiError(Exception):
    """Okex的API常常变动，当API发生奇葩的变动的时候，会发升这个异常"""
    pass


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
    NotTraded = 0
    PartialTraded = 1
    Finished = 2


########################################################################
class Order(object):
    _lastLocalId = 0
    
    #----------------------------------------------------------------------
    def __init__(self):
        Order._lastLocalId += 1
        self.localId = str(Order._lastLocalId)
        self.remoteId = None
        self.vtOrder = None # type: VtOrderData


########################################################################
class Symbol(object):
    
    #----------------------------------------------------------------------
    def __init__(self):
        self.v3 = None  # type: str             # BTC_USD_1891201
        self.ui = None  # type: str             # BTC_USD_NEXTWEEK
        self.v1Symbol = None  # type: str       # btc_usd
        self.uiSymbol = None  # type: str       # btc_usd
        self.easySymbol = None  # type: str     # btc
        self.localContractTYpe = None  # type: str     # THISWEEK
        self.remoteContractType = None  # type: str    # this_week


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
    Position = 9
    Order = 10


########################################################################
class Channel(object):
    
    #----------------------------------------------------------------------
    def __init__(self, type_, symbol=None, remoteContractType=None, extra_=None):
        self.type = type_
        self.symbol = symbol
        self.remoteContractType = remoteContractType
        self.extra = extra_


########################################################################
class OkexFuturesGateway(VtGateway):
    """OKEX期货交易接口"""
    
    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='OKEXFUTURES'):
        """Constructor"""
        super(OkexFuturesGateway, self).__init__(eventEngine, gatewayName)
        self.exchange = constant.EXCHANGE_OKEXFUTURE
        self.apiKey = None  # type: str
        self.apiSecret = None  # type: str
        self.apiPassphrase = None  # type: str

        self.restClient = OkexFuturesRestBaseV3()

        self.webSocket = OkexFuturesWebSocketBase()
        self.webSocket.onPacket = self.onWebSocketPacket
        self.webSocket.unpackData = self.webSocketUnpackData
        
        self.leverRate = 1
        self.symbols = []

        self._symbolDict = {}  # type: Dict[str, Symbol]

        self.tradeID = 0
        self._orders = {}  # type: Dict[str, Order]
        self._remoteIds = {}  # type: Dict[str, Order]
        self._lastTicker = None  # type: VtTickData
        self._utcOffset = datetime.now() - datetime.utcnow()

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
        self.restClient.init(self.apiKey, self.apiSecret, self.apiPassphrase)
        self.webSocket.init(self.apiKey, self.apiSecret, self.apiPassphrase)
        self.restClient.start()
        self.webSocket.start()

        self.queryContracts()
        
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq): # type: (VtSubscribeReq)->None
        """订阅行情"""
        s = self.parseSymbol(subscribeReq.symbol)
        remoteSymbol = s.v1Symbol.lower()
        remoteContractType = s.remoteContractType

        # ticker
        self.webSocket.sendPacket({
            'event': 'addChannel',
            'channel':
                'ok_sub_futureusd_' + remoteSymbol.lower() + '_ticker_' + remoteContractType
        })

        # depth
        self.webSocket.sendPacket({
            'event': 'addChannel',
            'channel':
                'ok_sub_futureusd_' + remoteSymbol.lower() + '_depth' + remoteContractType + '_5'
        })

    #----------------------------------------------------------------------
    def subscribeUserTrade(self):
        self.webSocket.sendPacket({
            'event': 'addChannel',
            'channel': 'ok_sub_futureusd_trades'
        })

    #----------------------------------------------------------------------
    def _writeError(self, msg):  # type: (str)->None
        e = VtErrorData()
        e.gatewayName = self.gatewayName
        e.errorMsg = msg
        self.onError(e)

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
        myorder = Order()
        localId = myorder.localId
        self._orders[localId] = myorder
        myorder.vtOrder = VtOrderData.createFromGateway(self,
                                                        localId,
                                                        symbol,
                                                        self.exchange,
                                                        price,
                                                        volume,
                                                        direction,
                                                        offset)
        return myorder

    #----------------------------------------------------------------------
    def parseSymbol(self, symbol):
        return self._symbolDict[symbol]
    
    #----------------------------------------------------------------------
    def sendOrder(self, vtRequest): # type: (VtOrderReq)->str
        """发单"""
        symbol = self.parseSymbol(vtRequest.symbol).v3
        myorder = self._generateLocalOrder(symbol,
                                           vtRequest.price,
                                           vtRequest.volume,
                                           vtRequest.direction,
                                           vtRequest.offset)

        orderType = _orderTypeMap[(vtRequest.direction, vtRequest.offset)]  # 开多、开空、平多、平空

        data = {
            'client_oid': None,
            'instrument_id': symbol,
            'type': orderType,
            'size': vtRequest.volume,
            'leverage': self.leverRate,
        }
        if vtRequest.priceType == constant.PRICETYPE_MARKETPRICE:
            data['match_price'] = '1'
        else:
            data['price'] = vtRequest.price

        self.restClient.addRequest('POST', '/api/futures/v3/order',
                                   callback=self._onOrderSent,
                                   onFailed=self._onSendOrderFailed,
                                   data=data,
                                   extra=myorder
                                   )
        return myorder.vtOrder.vtOrderID

    #----------------------------------------------------------------------
    def cancelOrder(self, vtCancel):  # type: (VtCancelOrderReq)->None
        """撤单"""
        myorder = self._getOrderByLocalId(vtCancel.orderID)
        assert myorder is not None, u"理论上是无法取消一个不存在的本地单的"

        symbol = vtCancel.symbol
        remoteId = myorder.remoteId

        path = '/api/futures/v3/cancel_order/' + symbol + '/' + remoteId
        self.restClient.addRequest('POST', path,
                                   callback=self._onOrderCanceled,
                                   onFailed=self._onCancelOrderFailed,
                                   data={
                                       'instrument_id': symbol,
                                       'order_id': remoteId
                                   },
                                   extra=myorder
                                   )

    #----------------------------------------------------------------------
    def queryContracts(self):
        return self.restClient.addRequest('GET', '/api/futures/v3/instruments',
                                          callback=self._onQueryContracts,
                                          )
    
    #----------------------------------------------------------------------
    def queryOrders(self, symbol, status):  # type: (str, OkexFuturesOrderStatus)->None
        """
        :param symbol:
        :param status: OkexFuturesOrderStatus
        :return:
        """
        symbol = self.parseSymbol(symbol).v3
        path = '/api/futures/v3/orders/' + symbol
        self.restClient.addRequest("POST", path,
                                   data={
                                       'status': status,
                                       'instrument_id': symbol,
                                       # 'from': 0,
                                       # 'to': 2,
                                       # 'limit': 100,
                                   },
                                   callback=self._onQueryOrders,
                                   )
    
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金
        Okex 的API变化太大，不单独实现API了，所有东西都封装在这里面
        """
        return self.restClient.addRequest('GET', '/api/futures/v3/accounts',
                                          callback=self._onQryAccounts,
                                          )

    #----------------------------------------------------------------------
    def _onQryAccounts(self, data, _):
        if 'info' not in data:
            raise ApiError("unable to parse account data")
    
        for easySymbol, detail in data['info'].items():  # type: str, dict
            acc = VtAccountData()
            acc.gatewayName = self.gatewayName
            acc.accountID = easySymbol
            acc.vtAccountID = acc.gatewayName + '.' + acc.accountID
            
            acc.balance = detail.get('equity', 0)
            acc.available = detail['total_avail_balance']
            if 'contracts' in detail:
                keys = {'available_qty': 'available_qty',
                        'fixed_balance': 'fixed_balance',
                        'margin_for_unfilled': 'margin',
                        'margin_frozen': 'margin',
                        'realized_pnl': 'realized_pnl',
                        'unrealized_pnl': 'unrealized_pnl'}
                for v in keys.values():
                    detail[v] = 0.0
                for c in detail['contracts']:
                    for k, v in keys.items():
                        detail[v] += float(c[k])
            acc.margin = detail['margin']
            acc.positionProfit = data.get('unrealized_pnl', 0)
            acc.closeProfit = data.get('realized_pnl', 0)
            self.onAccount(acc)
    
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        return self.restClient.addRequest('GET', '/api/futures/v3/position',
                                          callback=self._onQueryPosition,
                                          )
    
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.restClient.stop()
        self.webSocket.stop()

    #----------------------------------------------------------------------
    def _onOrderSent(self, data, request):  #type: (dict, Request)->None
        """下单回调"""
        # errorCode = data['error_code'],
        # errorMessage = data['error_message'],
        myorder = request.extra  # type: Order
        remoteId = data['order_id']
        if remoteId != '-1':
            myorder.remoteId = remoteId
            myorder.vtOrder.status = constant.STATUS_NOTTRADED
            self._saveRemoteId(myorder.remoteId, myorder)
        else:
            myorder.vtOrder.status = constant.STATUS_REJECTED
        self.onOrder(myorder.vtOrder)

    #----------------------------------------------------------------------
    def _onSendOrderFailed(self, _, request):  # type:(int, Request)->None
        myorder = request.extra  # type: Order
        myorder.vtOrder.status = constant.STATUS_REJECTED
        self.onOrder(myorder.vtOrder)
    
    #----------------------------------------------------------------------
    def _onOrderCanceled(self, data, request):  #type: (dict, Request)->None
        myorder = request.extra  # type: Order
        result = data['result']
        if result is True:
            myorder.vtOrder.status = constant.STATUS_CANCELLED
            self.onOrder(myorder.vtOrder)
        else:
            # todo: more detail about error
            print('failed to cancel order: ' + json.dumps(data))
            self._writeError('Failed to cancel order {}'.format(myorder.localId))

    #----------------------------------------------------------------------
    def _onCancelOrderFailed(self, _, request):  # type:(int, Request)->None
        myorder = request.extra  # type: Order
        self._writeError(u'Failed to cancel order {}'.format(myorder.localId))
        
    #----------------------------------------------------------------------
    def _onQueryContracts(self, data, _):  #type: (dict, Request)->None
    
        # 首先建立THISWEEK, NEXTWEEK, QUARTER和相应Contract的映射
        symbols = set()
        for contract in data:
            symbol = contract['instrument_id']
            symbols.add(symbol)
    
        # 一般来说，一个币种对有三种到期日期不同的symbol。
        # 将这三种symbol按顺序排列，就能依次得到ThisWeek, NextWeek和Quarter三种symbol
        s2 = defaultdict(list)
        for symbol in sorted(symbols):
            easySymbol = symbol[:3]
            s2[easySymbol].append(symbol)
    
        # 按顺序取出排列好的symbols，对应上ThisWeek, NextWeek和Quarter
        # 然后记录下来他们的几种symbols形式和相应的一些常量：
        # v1Symbol: BTC_USD_THISWEEK
        # v3Symbol: BTC_USD_181222
        # easySymbol: btc, eth, ...
        # remoteContractType: this_week, next_week, ...
        # localContractType: THISWEEK, NEXTWEEK, ...
    
        symbolDict = {}
        for easySymbol, sortedSymbols in s2.items():
            if len(sortedSymbols) == 3:
                for contractType, v3symbol in zip(_contractTypeMap.keys(), sortedSymbols):
                    uiSymbol = '{}_USD_{}'.format(easySymbol, contractType)  # ETC_USD_THISWEEK
                    remoteContractName = '{}{}'.format(easySymbol, v3symbol[-4:])  # ETC1201
                
                    s = Symbol()
                    s.v1Symbol = '{}_{}'.format(easySymbol.lower(), "usd")
                    s.v3 = v3symbol
                    s.easySymbol = easySymbol
                    s.remoteContractType = _contractTypeMap[contractType]
                    s.localContractTYpe = contractType
                    s.uiSymbol = uiSymbol
                
                    # normal map
                    symbolDict[uiSymbol.upper()] = s
                    symbolDict[uiSymbol.lower()] = s
                    symbolDict[uiSymbol] = s
                    symbolDict[v3symbol] = s
                    
                    # switch between '-' and '_'
                    symbolDict[uiSymbol.upper().replace('_', '-')] = s
                    symbolDict[uiSymbol.lower().replace('_', '-')] = s
                    symbolDict[uiSymbol.replace('_', '-')] = s
                    symbolDict[v3symbol.replace('-', '_')] = s
                    
                    # BTCUSD181228 BTCUSDTHISWEEK, btcusdthisweek
                    symbolDict[v3symbol.upper().replace('-', '')] = s
                    symbolDict[uiSymbol.upper().replace('_', '')] = s
                    symbolDict[uiSymbol.lower().replace('_', '')] = s
                    
                    symbolDict[remoteContractName.upper()] = s
                    symbolDict[remoteContractName.lower()] = s
        
        # unicode and str
        for k, v in symbolDict.items():
            self._symbolDict[str(k)] = v
            self._symbolDict[unicode(k)] = v
    
        # 其次响应onContract，也是该函数的本职工作
        for contract in data:
            symbol = contract['instrument_id']
            size = contract['quote_increment'] if 'quote_increment' in contract else contract[
                'trade_increment'],
            vtContract = VtContractData.createFromGateway(
                gateway=self,
                exchange=self.exchange,
                symbol=symbol,
                productClass=constant.PRODUCT_FUTURES,
                priceTick=contract['tick_size'],
                size=size,
                name=symbol,
                expiryDate=contract['delivery'],
                underlyingSymbol=contract['underlying_index'],
            )
            self.onContract(vtContract)
    
        # 最后订阅symbols，还有查询其他东西
        for symbol in self.symbols:
            s = self.parseSymbol(symbol)
            # noinspection PyTypeChecker
            req = VtSubscribeReq()
            req.symbol = s.v3
            self.subscribe(req)
        
        # 查询账户啊，持仓啊，委托单啊之类的东西
        self.qryAccount()
        self.qryPosition()
        
        # 查询所有未成交的委托
        # v3 API尚未支持该操作
        # for symbol in symbols:
        #     # noinspection PyTypeChecker
        #     self.queryOrders(symbol, OkexFuturesOrderStatus.NotTraded)

    #----------------------------------------------------------------------
    def _onQueryOrders(self, data, _):  #type: (dict, Request)->None
        if data['result'] is True:
            for info in data['orders']:
                remoteId = info['order_id']
                tradedVolume = info['filled_qty']
            
                myorder = self._getOrderByRemoteId(remoteId)
                if myorder:
                    # 如果订单已经缓存在本地，则尝试更新订单状态
                
                    # 有新交易才推送更新
                    if tradedVolume != myorder.vtOrder.tradedVolume:
                        myorder.vtOrder.tradedVolume = tradedVolume
                        myorder.vtOrder.status = constant.STATUS_PARTTRADED
                        self.onOrder(myorder.vtOrder)
                else:
                    # 本地无此订单的缓存（例如，用其他工具的下单）
                    # 缓存该订单，并推送
                    symbol = info['instrument_id']
                    direction, offset = remoteOrderTypeToLocal(info['type'])
                    myorder = self._generateLocalOrder(symbol,
                                                       info['price'],
                                                       info['size'],
                                                       direction,
                                                       offset)
                    myorder.vtOrder.tradedVolume = tradedVolume
                    myorder.remoteId = remoteId
                    self._saveRemoteId(myorder.remoteId, myorder)
                    self.onOrder(myorder.vtOrder)
                
    #----------------------------------------------------------------------
    def _onQueryPosition(self, data, _):  #type: (dict, Request)->None
        if 'holding' in data:
            posex = data['holding']
        elif 'position' in data:
            posex = data['position']
        else:
            raise ApiError("Failed to parse position data")
        for pos in posex:
            symbol = self.parseSymbol(pos['instrument_id']).uiSymbol
            
            # 多头持仓
            vtPos = VtPositionData.createFromGateway(
                gateway=self,
                exchange=self.exchange,
                symbol=symbol,
                direction=constant.DIRECTION_NET,
                position=pos['long_qty'],
                price=pos['long_avg_cost'],
            )
            self.onPosition(vtPos)
    
            # 多头持仓
            vtPos = VtPositionData.createFromGateway(
                gateway=self,
                exchange=self.exchange,
                symbol=symbol,
                direction=constant.DIRECTION_NET,
                position=pos['short_qty'],
                price=pos['short_avg_cost'],
            )
            self.onPosition(vtPos)
            
    #----------------------------------------------------------------------
    @staticmethod
    def webSocketUnpackData(data):
        """重载websocket.unpackData"""
        return json.loads(zlib.decompress(data, -zlib.MAX_WBITS))
    
    #----------------------------------------------------------------------
    def onWebSocketPacket(self, packets):
        for packet in packets:
            channelName = None
            if 'channel' in packet:
                channelName = packet['channel']
            if not channelName or channelName == 'addChannel':
                return
        
            data = packet['data']
            channel = parseChannel(channelName)  # type: Channel
            if not channel:
                print("unknown websocket channel : ", json.dumps(packet, indent=2))
                return
            try:
                if channel.type == ChannelType.Tick:
                    uiSymbol = remoteSymbolToLocal(channel.symbol,
                                                   remoteContractTypeToLocal(
                                                       channel.remoteContractType))
                    if self._lastTicker is None:
                        self._lastTicker = VtTickData.createFromGateway(
                            gateway=self,
                            symbol=uiSymbol,
                            exchange=self.exchange,
                            lastPrice=float(data['last']),
                            lastVolume=float(data['vol']),
                            highPrice=float(data['high']),
                            lowPrice=float(data['low']),
                            openInterest=float(data['hold_amount']),
                            lowerLimit=float(data['limitLow']),
                            upperLimit=float(data['limitHigh']),
                        )
                    else:
                        self._lastTicker.lastPrice = float(data['last'])
                        self._lastTicker.lastVolume = float(data['vol'])
                        self._lastTicker.highPrice = float(data['high'])
                        self._lastTicker.lowPrice = float(data['low'])
                        self._lastTicker.openInterest = float(data['hold_amount'])
                        self._lastTicker.lowerLimit = float(data['limitLow'])
                        self._lastTicker.upperLimit = float(data['limitHigh'])
                        self._lastTicker.datetime = datetime.now()
                        self._lastTicker.date = self._lastTicker.datetime.strftime('%Y%m%d')
                        self._lastTicker.time = self._lastTicker.datetime.strftime('%H:%M:%S')
                        self.onTick(self._lastTicker)
                elif channel.type == ChannelType.Depth:
                    
                    asks = data['asks']
                    bids = data['bids']
                    if self._lastTicker is not None:
                        timestamp = float(data['timestamp'])
                        ts = datetime.utcfromtimestamp(timestamp/1000) + self._utcOffset
                        
                        self._lastTicker.askPrice1 = asks[0][0]
                        self._lastTicker.askPrice2 = asks[1][0]
                        self._lastTicker.askPrice3 = asks[2][0]
                        self._lastTicker.askPrice4 = asks[3][0]
                        self._lastTicker.askPrice5 = asks[4][0]
                        self._lastTicker.askVolume1 = asks[0][1]
                        self._lastTicker.askVolume2 = asks[1][1]
                        self._lastTicker.askVolume3 = asks[2][1]
                        self._lastTicker.askVolume4 = asks[3][1]
                        self._lastTicker.askVolume5 = asks[4][1]
        
                        self._lastTicker.bidPrice1 = bids[0][0]
                        self._lastTicker.bidPrice2 = bids[1][0]
                        self._lastTicker.bidPrice3 = bids[2][0]
                        self._lastTicker.bidPrice4 = bids[3][0]
                        self._lastTicker.bidPrice5 = bids[4][0]
                        self._lastTicker.bidVolume1 = bids[0][1]
                        self._lastTicker.bidVolume2 = bids[1][1]
                        self._lastTicker.bidVolume3 = bids[2][1]
                        self._lastTicker.bidVolume4 = bids[3][1]
                        self._lastTicker.bidVolume5 = bids[4][1]
                        self._lastTicker.datetime = ts
                        self._lastTicker.date = self._lastTicker.datetime.strftime('%Y%m%d')
                        self._lastTicker.time = self._lastTicker.datetime.strftime('%H:%M:%S')
                        self.onTick(self._lastTicker)
                elif channel.type == ChannelType.Position:
                    symbol = data['symbol']
                    positions = data['positions']
                    for pos in positions:
                        if pos['position'] == '1':
                            direction = constant.DIRECTION_LONG
                        else:
                            direction = constant.DIRECTION_SHORT
                        total = pos['hold_amount']
                        usable = pos['eveningup']
                        # margin = _tryGetValue(pos, 'margin', 'fixmargin')
                        profit = _tryGetValue(pos, 'profitreal', 'realized')
                        symbol = self.parseSymbol(pos['contract_name']).uiSymbol
                        self.onPosition(VtPositionData.createFromGateway(
                            gateway=self,
                            exchange=self.exchange,
                            symbol=symbol,
                            direction=direction,
                            position=total,
                            frozen=total - usable,
                            price=pos['avgprice'],
                            profit=profit,
                        ))
                elif channel.type == ChannelType.UserInfo:
                    # ws 的acc没有分货币，没法用
                    pass
                elif channel.type == ChannelType.UserTrade:
                    tradeID = str(self.tradeID)
                    self.tradeID += 1
                    order = self._getOrderByRemoteId(data['orderid'])
                    if order:
                        self.onTrade(VtTradeData.createFromOrderData(
                            order=order.vtOrder,
                            tradeID=tradeID,
                            tradePrice=data['price'],
                        
                            # todo: 这里应该填写的到底是order总共成交了的数量，还是该次trade成交的数量
                            tradeVolume=data['deal_amount'],
                        ))
                    else:
                        # todo: 与order无关联的trade该如何处理？
                        # uiSymbol = remoteSymbolToLocal(info.symbol,
                        # remoteContractTypeToLocal(info.remoteContractType))
                        pass
            except KeyError:
                print("WebSocket error: parsing {}:\n{}".format(channelName, data))
                traceback.print_exception(*sys.exc_info())

    #----------------------------------------------------------------------
    # noinspection PyUnusedLocal
    def onApiError(self, exceptionType, exceptionValue, tb,
                   request=None  # type: Request
                   ):
        msg = traceback.format_exception(exceptionType, exceptionValue, tb)
        self._writeError(msg)

    #----------------------------------------------------------------------
    def onApiFailed(self, _, request):  # type:(int, Request)->None
        self._writeError(str(request))
        pass

    #----------------------------------------------------------------------
    def setQryEnabled(self, _):
        """dummy function"""
        pass
    
    
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


#----------------------------------------------------------------------
def remotePrefixToRemoteContractType(prefix):
    return _prefixForRemoteContractType[prefix]


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
    if sp[-1] == 'positions':  # eg: 'ok_sub_futureusd_positions'
        return Channel(ChannelType.Position)
    
    if sp[-1] == 'userinfo':  # eg: 'ok_sub_futureusd_positions'
        return Channel(ChannelType.UserInfo)
    
    lsp = len(sp)
    if sp[-1] == 'quarter':
        if lsp == 7:
            _, _, _, easySymbol, crash, typeName, contractTypePrefix = sp
            return Channel(ChannelType.Tick,
                           easySymbol + '_' + crash,
                           remotePrefixToRemoteContractType(contractTypePrefix))
    elif sp[-1] == 'week':
        if lsp == 8:
            _, _, _, easySymbol, crash, typeName, contractTypePrefix, _ = sp
            return Channel(ChannelType.Tick,
                           easySymbol + '_' + crash,
                           remotePrefixToRemoteContractType(contractTypePrefix))
    if sp[-1] == '5':
        if lsp == 7:  # eg "ok_sub_futureusd_eth_usd_depthquarter_5"
            _, _, _, easySymbol, crash, typeName_contractTypePrefix, depth = sp
            return Channel(ChannelType.Depth, easySymbol + '_' + crash,
                           remotePrefixToRemoteContractType(typeName_contractTypePrefix[5:]),
                           depth)
        if lsp == 8:  # eg "ok_sub_futureusd_eth_usd_depthnext_week_5"
            _, _, _, easySymbol, crash, typeName_contractTypePrefix, _, depth = sp
            return Channel(ChannelType.Depth, easySymbol + '_' + crash,
                           remotePrefixToRemoteContractType(typeName_contractTypePrefix[5:]),
                           depth)
    
    
#----------------------------------------------------------------------
def _tryGetValue(dict, *keys):
    """尝试从字典中获取某些键中的一个"""
    for k in keys:
        if k in dict:
            return dict[k]
    return None


_prefixForRemoteContractType = {v.split('_')[0]: v for k, v in
                                OkexFuturesContractType.__dict__.items() if
                                not k.startswith('_')}

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
_symbolsForUi = {(remoteSymbol.upper() + '_' + upperContractType.upper())
                 : (remoteSymbol, remoteContractType)
                 for remoteSymbol in _remoteSymbols
                 for upperContractType, remoteContractType in
                 _contractTypeMap.items()
                 }  # type: Dict[str, List[str, str]]
_symbolsForUiReverse = {v: k for k, v in _symbolsForUi.items()}

_channel_for_subscribe = {
    'ok_sub_futureusd_' + easySymbol + '_ticker_' + remoteContractType
    : (easySymbol, remoteContractType)
    for easySymbol in _easySymbols
    for remoteContractType in _contractTypeMap.values()
}
