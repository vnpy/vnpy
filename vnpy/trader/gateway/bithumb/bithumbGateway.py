# encoding: UTF-8

'''
vnpy.api.bithumb的gateway接入
'''
import json
from collections import defaultdict
from datetime import datetime

from vnpy.api.bithumb import BithumbRestApi
from vnpy.trader.vtFunction import getJsonPath
from vnpy.trader.vtGateway import *

# 方向映射
directionMap = {
    constant.DIRECTION_LONG: 'bid',
    constant.DIRECTION_SHORT: 'ask'
}
directionMapReverse = {v: k for k, v in directionMap.items()}

# 从https://www.bithumb.com/u1/US127中https://api.bithumb.com/trade/place的API说明中得到
minimum_ticks = {
    'BTC': 0.001,
    'ETH': 0.01,
    'DASH': 0.01,
    'LTC': 0.01,
    'ETC': 0.1,
    'XRP': 10,
    'BCH': 0.001,
    'XMR': 0.01,
    'ZEC': 0.01,
    'QTUM': 0.1,
    'BTG': 0.1,
    'EOS': 0.1,
    'ICX': 1,
    'VEN': 1,
    'TRX': 100,
    'ELF': 10,
    'MITH': 10,
    'MCO': 10,
    'OMG': 0.1,
    'KNC': 1,
    'GNT': 10,
    'HSR': 1,
    'ZIL': 100,
    'ETHOS': 1,
    'PAY': 1,
    'WAX': 10,
    'POWR': 10,
    'LRC': 10,
    'GTO': 10,
    'STEEM': 10,
    'STRAT': 1,
    'ZRX': 1,
    'REP': 0.1,
    'AE': 1,
    'XEM': 10,
    'SNT': 10,
    'ADA': 10
}


########################################################################
class BithumbGateway(VtGateway):

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='BithumbGateway'):
        super(BithumbGateway, self).__init__(eventEngine, gatewayName)

        self.restApi = RestApi(self)  # type: RestApi

        self.qryEnabled = False

        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)

    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        try:
            f = file(self.filePath)
        except IOError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'读取连接配置出错，请检查'
            self.onLog(log)
            return

        # 解析json文件
        setting = json.load(f)
        try:
            apiKey = str(setting['apiKey'])
            apiSecret = str(setting['apiSecret'])
            # symbols = setting['symbols']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return

        # 创建行情和交易接口对象
        self.restApi.connect(apiKey, apiSecret)

        # 初始化并启动查询
        self.initQuery()

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        pass

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.restApi.sendOrder(orderReq)

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.restApi.cancelOrder(cancelOrderReq)

    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.restApi.close()

    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        # if self.qryEnabled:
        #     需要循环的查询函数列表
        #     self.qryFunctionList = [self.restApi.qryTickers,
        #                             self.restApi.qryDepth,
        #                             self.restApi.qryPosition,
        #                             self.restApi.qryOrder]
        #
        #     self.qryCount = 0  # 查询触发倒计时
        #     self.qryTrigger = 1  # 查询触发点
        #     self.qryNextFunction = 0  # 上次运行的查询函数索引
        #
        #     self.startQuery()
        pass

    #----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        # self.qryCount += 1
        #
        # if self.qryCount > self.qryTrigger:
        #     # 清空倒计时
        #     self.qryCount = 0
        #
        #     # 执行查询函数
        #     function = self.qryFunctionList[self.qryNextFunction]
        #     function()
        #
        #     # 计算下次查询函数的索引，如果超过了列表长度，则重新设为0
        #     self.qryNextFunction += 1
        #     if self.qryNextFunction == len(self.qryFunctionList):
        #         self.qryNextFunction = 0
        pass

    #----------------------------------------------------------------------
    def startQuery(self):
        """启动连续查询"""
        self.eventEngine.register(EVENT_TIMER, self.query)

    #----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qryEnabled


########################################################################
# noinspection PyUnusedLocal
class RestApi(BithumbRestApi):
    """REST API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(RestApi, self).__init__()

        self.gateway = gateway  # type: BithumbGateway  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        self.localID = 0
        self.tradeID = 0

        self.orders = {}  # type: dict[str, VtOrderData]  # localID:order
        self.sysLocalDict = {}  # type: dict[str, str]  # sysID: localID
        self.localSysDict = {}  # type: dict[str, str]  # localID: sysID
        self.reqOrderDict = {}  # type: dict[int, VtOrderData]  # reqID:order
        self.cancelDict = {}  # type: dict[str, VtCancelOrderReq] # localID:req

        self.tickDict = {}

    #----------------------------------------------------------------------
    def connect(self, apiKey, apiSecret):
        """连接服务器"""
        self.init(apiKey, apiSecret)
        self.start()

        # self.symbols = symbols
        self.writeLog(u'REST API启动成功')

        self.qryContract()

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

    #----------------------------------------------------------------------
    def generateLocalOrder(self, ):
        self.localID += 1
        localID = str(self.localID)
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.status = constant.STATUS_UNKNOWN
        order.exchange = constant.EXCHANGE_BITHUMB
        order.orderID = localID
        order.vtOrderID = '.'.join([self.gatewayName, localID])
        self.orders[localID] = order
        return order

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """下单"""
        req = {
            'order_currency': orderReq.symbol,
            'Payment_currency': orderReq.currency,  # todo: 无论如何服务器都会以KRW作为单位
            'type': directionMap[orderReq.direction],
            'price': int(orderReq.price),
            'units': orderReq.volume
        }

        reqid = self.addReq('POST', '/trade/place', self.onSendOrder, postdict=req)

        # 缓存委托数据对象
        order = self.generateLocalOrder()
        self.fillLocalOrder(order,
                            orderReq.symbol,
                            orderReq.price,
                            orderReq.volume,
                            orderReq.direction)

        self.reqOrderDict[reqid] = order
        return order.vtOrderID

    #----------------------------------------------------------------------
    def onSendOrder(self, data, reqid):  # type: (dict, int)->None
        """下单回执"""
        if self.checkError(u'委托', data):
            return

        order = self.reqOrderDict[reqid]
        localID = order.orderID
        sysID = data['order_id']

        self.saveSysIDForOrder(order, sysID)

        self.gateway.onOrder(order)

        # 发出等待的撤单委托
        if localID in self.cancelDict:
            req = self.cancelDict[localID]
            self.cancelOrder(req)
            del self.cancelDict[localID]

    #----------------------------------------------------------------------
    @staticmethod
    def fillLocalOrder(order, symbol, price, totalVolume, direction):
        order.symbol = symbol
        order.vtSymbol = '.'.join([order.symbol, order.exchange])
        order.price = price
        order.totalVolume = totalVolume
        order.direction = direction

    #----------------------------------------------------------------------
    def saveSysIDForOrder(self, order, sysID):  # type: (VtOrderData, str)->None
        self.sysLocalDict[sysID] = order.orderID
        self.localSysDict[order.orderID] = sysID

    #----------------------------------------------------------------------
    def qryOrder(self, order):  # type: (VtOrderData)->None
        sysID = self.getSysIDForOrder(order)
        req = {
            'currency': order.symbol,
            'order_id': sysID
        }
        self.addReq('POST', '/info/orders', self.onQryOrders, postdict=req)

    #----------------------------------------------------------------------
    def qryOrders(self, currency='XML'):  # type: (VtOrderData)->None
        sysID = self.getSysIDForOrder(order)
        req = {
            'currency': order.symbol,
        }
        self.addReq('POST', '/info/orders', self.onQryOrders, postdict=req)

    #----------------------------------------------------------------------
    def onQryOrders(self, data, reqid):
        if self.checkError(u'订单查询', data):
            return
        orders = data['data']
        for detail in orders:
            sysID = detail['order_id']
            order = self.getOrderBySysID(sysID)
            if not order:
                # 查询到了新的order(以前的order)
                order = self.generateLocalOrder()
                self.fillLocalOrder(order,
                                    detail['order_currency'],
                                    detail['price'],
                                    detail['units'],
                                    directionMapReverse[detail['type']])
                order.tradedVolume = order.totalVolume - detail['units_remaining']
                # todo: payment_currency
                # payment_currency = detail['payment_currency']
                self.saveSysIDForOrder(order, sysID)

                # 推送
                self.gateway.onOrder(order)
                continue

            originalTradeVolume = order.tradedVolume
            order.tradedVolume = newTradeVolume = order.totalVolume - detail['units_remaining']

            if newTradeVolume != originalTradeVolume:
                # 推送更新
                self.gateway.onOrder(order)

            # 尝试更新状态
            # todo: 这一句还未测试，不知道成交之后date_completed是不是就会有值
            order.status = constant.STATUS_ALLTRADED if detail['date_completed'] else order.status
            if order.status == constant.STATUS_ALLTRADED:
                # 推送成交
                self.pushOrderAsTraded(order)

    #----------------------------------------------------------------------
    def pushOrderAsTraded(self, order):
        trade = VtTradeData()
        trade.gatewayName = order.gatewayName
        trade.symbol = order.symbol
        trade.vtSymbol = order.vtSymbol
        trade.orderID = order.orderID
        trade.vtOrderID = order.vtOrderID
        self.tradeID += 1
        trade.tradeID = str(self.tradeID)
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
        trade.direction = order.direction
        trade.price = order.price
        trade.volume = order.tradedVolume
        trade.tradeTime = datetime.now().strftime('%H:%M:%S')
        self.gateway.onTrade(trade)

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):  # type: (self, VtCancelOrderReq)->None
        """"""
        localID = cancelOrderReq.orderID
        order = self.getOrderByLocalID(localID)

        if self.isOrderPosted(order):
            sysID = self.getSysIDForOrder(order)
            req = {
                'type': directionMap[order.direction],
                'order_id': sysID,
                'currency': cancelOrderReq.symbol
            }
            self.addReq('POST',
                        '/trade/cancel',
                        callback=lambda data, reqid: self.onCancelOrder(localID, data, reqid),
                        postdict=req)
        else:
            self.cancelDict[localID] = cancelOrderReq

    #----------------------------------------------------------------------
    def onCancelOrder(self, localID, data, reqid):
        if self.checkError(u'撤单', data):
            return
        order = self.getOrderByLocalID(localID)
        order.status = constant.STATUS_CANCELLED

    #----------------------------------------------------------------------
    def qryContract(self):
        """"""
        contract = VtContractData()
        contract.gatewayName = self.gatewayName

        for symbol, tick in minimum_ticks.items():
            contract.symbol = symbol
            contract.exchange = constant.EXCHANGE_BITHUMB
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = contract.vtSymbol
            contract.productClass = constant.PRODUCT_SPOT
            contract.priceTick = tick
            contract.size = 1
            self.gateway.onContract(contract)

    #----------------------------------------------------------------------
    def qryPublicTick(self, symbol='ALL'):
        """ symbol 可以是'BTC', 'ETC'等等电子货币符号；也可以使用'ALL'，表示要获取所有货币的行情"""
        url = '/public/ticker/' + symbol
        if symbol.upper() == 'ALL':
            self.addReq('GET', url, self.onQryMultiPublicTicker)
        else:
            self.addReq('GET', url,
                        callback=lambda data, reqid: self.onQrySinglePublicTicker(symbol, data, id))

    #----------------------------------------------------------------------
    def qryPublicOrderBook(self, symbol='ALL'):
        """ symbol 可以是'BTC', 'ETC'等等电子货币符号；也可以使用'ALL'，表示要获取所有货币的行情"""
        url = '/public/orderbook/' + symbol
        if symbol.upper() == 'ALL':
            self.addReq('GET', url, self.onQryMultiPublicOrderBook)
        else:
            self.addReq('GET', url,
                        callback=lambda data, reqid: self.onQrySinglePublicOrderBook(symbol, data, id))

    #----------------------------------------------------------------------
    def qryPrivateTick(self, symbol, currency='CNY'):
        """"""
        req = {
            'order_currency': symbol,
            'payment_currency': currency,
        }
        self.addReq('POST', '/info/ticker', self.onQryPrivateTicker, postdict=req)

    #----------------------------------------------------------------------
    def qryPosition(self, symbol='ALL'):
        """"""
        req = {
            'currency': symbol,
        }
        self.addReq('POST', '/info/balance', self.onQryPosition, postdict=req)

        pass

    #----------------------------------------------------------------------
    def onQryPosition(self, data, reqid):  # type: (self, dict, int)->None
        """"""
        if self.checkError(u'查询持仓', data):
            return

        datas = data['data']  # type: dict

        # 先分类一下
        infos = defaultdict(dict)  # type: dict[str, dict[str, str]]
        for key, val in datas.items():  # type: str, str
            split_position = key.rfind('_')
            infoType, symbol = key[:split_position], key[split_position+1:]
            infos[symbol.upper()][infoType] = val

        for symbol in infos.keys():
            info = infos[symbol]
            if symbol == u'LAST':  # 过滤掉xcoin_last，这个值表示的是最后一次交易量
                continue
            if symbol == u'KRW':
                accountData = VtAccountData()
                # todo: accountID必须从另一个API获取
                # accountData.accountID =
                accountData.balance = info['total']
                accountData.available = info['available']
                self.gateway.onAccount(accountData)
                pass
            else:
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName

                pos.symbol = symbol
                pos.exchange = constant.EXCHANGE_BITHUMB
                pos.vtSymbol = '.'.join([pos.symbol, pos.exchange])
                pos.direction = constant.DIRECTION_NET
                pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
                pos.position = float(info['total'])
                pos.frozen = float(info['in_use'])

                self.gateway.onPosition(pos)

    #----------------------------------------------------------------------
    def parsePublicTickerData(self, symbol, info):
        dt = datetime.now()
        date = dt.strftime('%Y%m%d')
        time = dt.strftime('%H:%M:%S')

        tick = self.getTick(symbol)

        tick.openPrice = float(info['opening_price'])
        tick.highPrice = float(info['max_price'])
        tick.lowPrice = float(info['min_price'])
        tick.lastPrice = float(info['closing_price'])  # todo: 也许应该是'buy_price'?
        tick.volume = float(info['volume_1day'])
        tick.datetime = datetime
        tick.date = date
        tick.time = time

        # 只有订阅了深度行情才推送
        if tick.bidPrice1:
            self.gateway.onTick(tick)

    #----------------------------------------------------------------------
    def onQrySinglePublicTicker(self, symbol, data, reqid):
        if self.checkError(u'查询行情', data):
            return

        info = data['data']
        self.parsePublicTickerData(symbol=symbol, info=info)

    #----------------------------------------------------------------------
    def onQryMultiPublicTicker(self, data, reqid):
        if self.checkError(u'查询行情', data):
            return

        for symbol, info in data['data'].items():
            # 里面可能会出现一对：date: int这样的值，所以要过滤掉
            if isinstance(info, dict):
                self.parsePublicTickerData(symbol=symbol, info=info)
        pass

    #----------------------------------------------------------------------
    def parsePublicOrderBookData(self, symbol, info):
        dt = datetime.now()
        date = dt.strftime('%Y%m%d')
        time = dt.strftime('%H:%M:%S')

        tick = self.getTick(symbol)

        for i in range(5):
            tick.__setattr__('askPrice' + str(i + 1), float(info['asks'][i]['price']))
            tick.__setattr__('askVolume' + str(i + 1), float(info['asks'][i]['quantity']))

        for i in range(5):
            tick.__setattr__('bidPrice' + str(i + 1), float(info['bids'][i]['price']))
            tick.__setattr__('bidVolume' + str(i + 1), float(info['bids'][i]['quantity']))

        tick.datetime = datetime
        tick.date = date
        tick.time = time

        # 只有订阅了深度行情才推送
        if tick.bidPrice1:
            self.gateway.onTick(tick)

    #----------------------------------------------------------------------
    def onQrySinglePublicOrderBook(self, symbol, data, reqid):
        if self.checkError(u'五档行情', data):
            return

        info = data['data']
        self.parsePublicTickerData(symbol=symbol, info=info)
        pass

    #----------------------------------------------------------------------
    def onQryMultiPublicOrderBook(self, data, reqid):
        if self.checkError(u'五档行情', data):
            return

        for symbol, info in data['data'].items():
            self.parsePublicTickerData(symbol=symbol, info=info)
        pass

    #----------------------------------------------------------------------
    def onQryPrivateTicker(self, data, reqid):
        pass

    #----------------------------------------------------------------------
    def getTick(self, symbol):
        """"""
        tick = self.tickDict.get(symbol, None)  # type: VtTickData

        if not tick:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName
            tick.symbol = symbol
            tick.exchange = constant.EXCHANGE_BITHUMB
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            self.tickDict[symbol] = tick

        return tick

    #----------------------------------------------------------------------
    def checkError(self, name, data):
        """"""
        status = data.get('status', None)
        if status == u'0000':
            return False
        elif not status:
            self.writeLog(u'%s触发错误：%s' % (name, u"未知的响应报文 : %s".format(data)))
            return True

        msg = data.get('message', u'unknown')
        self.writeLog(u'%s触发错误：%s' % (name, msg))
        return True

    #----------------------------------------------------------------------
    def getOrderByLocalID(self, localID):  # type: (str)->VtOrderData
        """如果没有该订单，这个函数会出错"""
        return self.orders[localID]

    #----------------------------------------------------------------------
    def getOrderByVtOrderID(self, vtOrderId):  # type: (str)->VtOrderData
        """如果没有该订单，这个函数会出错"""
        localID = vtOrderId[vtOrderId.rfind('.') + 1:]
        return self.getOrderByLocalID(localID)

    #----------------------------------------------------------------------
    def getOrderBySysID(self, sysID):  # type: (str)->VtOrderData
        return self.getOrderByLocalID(self.getLocalIDBySysID(sysID))

    #----------------------------------------------------------------------
    def getLocalIDBySysID(self, sysID):  # type: (str)->str
        return self.sysLocalDict[sysID]

    #----------------------------------------------------------------------
    def isOrderPosted(self, order):  # type: (VtOrderData)->bool
        """检查服务器是否响应了一个下单请求，如果已经响应了返回True，否则False"""
        return order.orderID in self.localSysDict

    #----------------------------------------------------------------------
    def getSysIDForOrder(self, order):  # type: (VtOrderData)->str
        return self.localSysDict[order.orderID]

    #----------------------------------------------------------------------
    def hasSysID(self, sysID):
        return sysID in self.sysLocalDict



if __name__ == '__main__':
    # default test secret:
    API_KEY = '0c2f5621ac18d26d51ce640b25eb44f9'
    API_SECRET = '62bb8b4e263476f443f8d3dbf0aad6bc'

    api = BithumbRestApi()
    api.init(apiKey=API_KEY, apiSecret=API_SECRET)
    api.start(1)

    eventEngine = EventEngine2()
    rest = RestApi(BithumbGateway(eventEngine=eventEngine))
    rest.connect(API_KEY, API_SECRET)

    translateDict = {
        u'\uac70\ub798 \uccb4\uacb0\ub0b4\uc5ed\uc774 '
        u'\uc874\uc7ac\ud558\uc9c0 \uc54a\uc2b5\ub2c8\ub2e4.': "交易记录不存在",

        u'\uac70\ub798 \uc9c4\ud589\uc911\uc778 \ub0b4\uc5ed\uc774 '
        u'\uc874\uc7ac\ud558\uc9c0 \uc54a\uc2b5\ub2c8\ub2e4.': "没有正在进行的交易",

        u'\ub9e4\uc218\uae08\uc561\uc774 \uc0ac\uc6a9\uac00\ub2a5 KRW'
        u' \ub97c \ucd08\uacfc\ud558\uc600\uc2b5\ub2c8\ub2e4.': "购买金额超过可用KRW",

        u'\ub9e4\uc218\uac74\uc758 \uc0c1\ud0dc\uac00 \uc9c4\ud589\uc911\uc774 \uc544\ub2d9\ub2c8\ub2e4. '
        u'\ucde8\uc18c\ud560 \uc218 \uc5c6\uc2b5\ub2c8\ub2e4.': "购买查询的状态未在进行中。 它无法取消。",

        u'\uc9c0\uc6d0\ud558\uc9c0 \uc54a\ub294 \ud654\ud3d0\uc785\ub2c8\ub2e4. [347]': "不支持该货币单位。[347]",
    }

    def printError(jsonObj):
        if rest.checkError('', data=jsonObj):
            print('error : ')
            msg = jsonObj['message']
            print(translateDict.get(msg, msg))

    def manualCancelOrder(sysID):
        def onTradeCancel(jsonObj, reqid):
            print('onTradeCancel : \n{}'.format(jsonObj))
            printError(jsonObj)

        rest.addReq('POST', '/trade/cancel', onTradeCancel,
                    postdict={'type': 'bid', 'order_id': sysID, 'currency': 'XMR'})

    def apiCancelOrder(localId):
        cancelReq = VtCancelOrderReq()
        cancelReq.symbol = order.symbol
        cancelReq.orderID = localId
        rest.cancelOrder(cancelReq)

    # query tick
    rest.qryPublicTick('BTC')
    rest.qryPublicTick('ALL')
    rest.qryPosition('BTC')
    rest.qryPosition('ALL')

    # send order
    sendOrderReq = VtOrderReq()
    sendOrderReq.symbol = 'XMR'
    sendOrderReq.direction = constant.DIRECTION_LONG
    sendOrderReq.volume = minimum_ticks['XMR']
    # sendOrderReq.price = 700
    # sendOrderReq.currency = 'CNY'  # 不可用
    # sendOrderReq.price = 16.6461
    # sendOrderReq.currency = 'USD'  # 不可用
    sendOrderReq.price = 17500
    sendOrderReq.currency = 'KRW'

    vtOrderId = rest.sendOrder(sendOrderReq)
    order = rest.getOrderByVtOrderID(vtOrderId)

    # todo: order的状态表示不够清晰
    while not rest.isOrderPosted(order):
        time.sleep(0.1)

    sysID = rest.getSysIDForOrder(order)
    print("sysID : ")
    print(sysID)

    def onOrders(jsonObj, reqid):
        print('on_orders : \n{}'.format(jsonObj))
        printError(jsonObj)

        for detail in jsonObj['data']:
            sysID = detail['order_id']
            if rest.hasSysID(sysID):
                apiCancelOrder(rest.getLocalIDBySysID(sysID))
            else:
                manualCancelOrder(sysID)

    after = '1531926544794'  # 2018-07-18T15:09:04.794Z
    # rest.addReq('POST', '/info/orders', on_orders,
    #             postdict={'order_id': sysID, 'type': 'bid', 'after': after, 'currency': 'XMR'})  # got
    #
    # rest.addReq('POST', '/info/orders', on_orders,
    #             postdict={'order_id': sysID, 'type': 'bid', 'currency': 'XMR'})  # got
    #
    # rest.addReq('POST', '/info/orders', on_orders,
    #             postdict={'after': after, 'currency': 'XMR'})  # got
    rest.addReq('POST', '/info/orders', onOrders, postdict={'currency': 'XMR'})  # got

    # rest.addReq('POST', '/info/orders', on_orders,
    #             postdict={'order_id': sysID, 'type': 'bid', 'after': after})  # 没有正在进行的交易
    #
    # rest.addReq('POST', '/info/orders', on_orders, postdict={'after': after})  # 没有正在进行的交易
    # rest.addReq('POST', '/info/orders', on_orders, postdict={})  # 没有正在进行的交易
    # rest.addReq('POST', '/info/orders', on_orders, postdict={'currency': 'ALL'})  # 不支持该货币单位

    raw_input()
