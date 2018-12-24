# encoding: UTF-8

'''
vnpy.api.chaince的gateway接入
'''
from __future__ import print_function

import json

from vnpy.api.chaince import ChainceRestApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath

# 委托状态类型映射
statusMapReverse = {}
statusMapReverse['queued'] = STATUS_NOTTRADED
statusMapReverse['active'] = STATUS_NOTTRADED
statusMapReverse['filled'] = STATUS_ALLTRADED
statusMapReverse['cancelled'] = STATUS_CANCELLED

# 方向映射
directionMap = {}
directionMap[DIRECTION_LONG] = 'bid'
directionMap[DIRECTION_SHORT] = 'ask'
directionMapReverse = {v: k for k, v in directionMap.items()}

########################################################################
class ChainceGateway(VtGateway):
    """Chaince接口"""

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName=''):
        """Constructor"""
        super(ChainceGateway, self).__init__(eventEngine, gatewayName)

        self.restApi = RestApi(self)
        self.qryEnabled = False  # 是否要启动循环查询
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)
        self.exchange = constant.EXCHANGE_CHAINCE

    # ----------------------------------------------------------------------
    def connect(self):
        """连接"""
        try:
            f = open(self.filePath)
        except IOError:
            self.restApi.writeLog(u'读取连接配置出错，请检查')
            return

        # 解析json文件
        setting = json.load(f)
        f.close()

        try:
            apiKey = str(setting['apiKey'])
            secretKey = str(setting['secretKey'])
            symbols = setting['symbols']
        except KeyError:
            self.restApi.writeLog(u'连接配置缺少字段，请检查')
            return

        self.restApi.connect(apiKey, secretKey, symbols)

        # 初始化并启动查询
        self.initQuery()

    # ----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.restApi.sendOrder(orderReq)

    # ----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        return self.restApi.cancelOrder(cancelOrderReq)

    # ----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        return self.restApi.queryAccount()

    # ----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.restApi.close()

    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [
                self.restApi.queryAccount,
                self.restApi.queryOrder,
                self.restApi.queryTickers,
                self.restApi.queryDepth
            ]

            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 1         # 查询触发点
            self.qryNextFunction = 0    # 上次运行的查询函数索引

            self.startQuery()

    #----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        self.qryCount += 1

        if self.qryCount > self.qryTrigger:
            # 清空倒计时
            self.qryCount = 0

            # 执行查询函数
            function = self.qryFunctionList[self.qryNextFunction]
            function()

            # 计算下次查询函数的索引，如果超过了列表长度，则重新设为0
            self.qryNextFunction += 1
            if self.qryNextFunction == len(self.qryFunctionList):
                self.qryNextFunction = 0

    #----------------------------------------------------------------------
    def startQuery(self):
        """启动连续查询"""
        self.eventEngine.register(EVENT_TIMER, self.query)

    #----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qryEnabled


class RestApi(ChainceRestApi):
    """API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(RestApi, self).__init__()

        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        self.date = datetime.now().strftime('%y%m%d%H%M%S')

        self.localID = 0
        self.tradeID = 0

        self.orderDict = {}
        self.tickDict = {}
        self.reqOrderDict = {}
        self.cancelDict = {}
        self.localSysDict = {}

    #----------------------------------------------------------------------
    def connect(self, apiKey, secretKey, symbols):
        """连接服务器"""
        self.init(apiKey, secretKey)
        self.start()

        self.symbols = [symbol.upper() for symbol in symbols]
        self.writeLog(u'REST API启动成功')

    #----------------------------------------------------------------------
    def queryAccount(self):
        """"""
        for symbol in self.symbols:
            self.addReq('GET', '/accounts/pair/%s' % symbol.lower(), self.onQueryAccount)

    #----------------------------------------------------------------------
    def queryOrder(self):
        """"""
        for symbol in self.symbols:
            self.addReq('GET', '/orders/%s/today' % symbol.lower(), self.onQueryOrder)

    #----------------------------------------------------------------------
    def queryTickers(self):
        """"""
        self.addReq('GET', '/tickers', self.onQueryTickers)

    #----------------------------------------------------------------------
    def queryDepth(self):
        """"""
        for symbol in self.symbols:
            self.addReq('GET', '/pairs/%s/depth' % symbol.lower(), self.onQueryDepth)

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """"""
        self.orderID += 1
        orderID = self.date + str(self.orderID).rjust(6, '0')
        vtOrderID = '.'.join([self.gatewayName, orderID])

        req = {
            'direction': directionMap[orderReq.direction],
            'type': 'limit',
            'price': orderReq.price,
            'quantity': orderReq.volume
        }

        reqid = self.addReq('POST', '/orders/%s' % orderReq.symbol.lower(), self.onSendOrder, postdict=req)

        # 缓存委托数据对象
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = orderReq.symbol
        order.exchange = self.gateway.exchange
        order.vtSymbol = '.'.join([order.symbol, order.exchange])
        order.orderID = orderID
        order.vtOrderID = vtOrderID
        order.price = orderReq.price
        order.totalVolume = orderReq.volume
        order.direction = orderReq.direction
        order.status = STATUS_UNKNOWN

        self.reqOrderDict[reqid] = order

        return vtOrderID

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """"""
        localID = cancelOrderReq.orderID

        if localID in self.localSysDict:
            req = {'order_id': self.localSysDict[localID]}
            return self.addReq('PUT', '/orders/%s/cancel' % cancelOrderReq.symbol.lower(), self.onData, postdict=req)
        else:
            self.cancelDict[localID] = cancelOrderReq

    #----------------------------------------------------------------------
    def onQueryAccount(self, data, req):
        """"""
        for asset_id in data:
            account = VtAccountData()
            account.gatewayName = self.gatewayName

            account.accountID = asset_id
            account.vtAccountID = '.'.join([account.gatewayName, account.accountID])
            account.balance = float(data[asset_id]['balance'])
            account.available = float(data[asset_id]['available'])

            self.gateway.onAccount(account)

    #----------------------------------------------------------------------
    def onQueryOrder(self, data, req):
        """"""
        symbol = req[1].split("/")[2]

        for o in data:
            orderUpdated = False
            tradeUpdated = False
            sysID = o['id']

            if sysID in self.orderDict:
                order = self.orderDict[sysID]
            else:
                order = VtOrderData()
                order.gatewayName = self.gatewayName
                order.symbol = symbol
                order.exchange = self.gateway.exchange
                order.vtSymbol = '.'.join([order.symbol, order.exchange])

                self.localID += 1
                localID = str(self.localID)
                self.localSysDict[localID] = sysID

                order.orderID = localID
                order.vtOrderID = '.'.join([order.gatewayName, order.orderID])

                order.direction = directionMapReverse[o['direction']]
                order.price = float(o['price'])
                order.totalVolume = float(o['quantity'])

                orderUpdated = True
                self.orderDict[sysID] = order

            newtradedVolume = float(o['volume'])
            newStatus = statusMapReverse[o['state']]

            if newtradedVolume != float(order.tradedVolume) or newStatus != order.status:
                orderUpdated = True

            if newtradedVolume != float(order.tradedVolume):
                tradeUpdated = True
                newVolume = newtradedVolume - order.tradedVolume

            order.tradedVolume = newtradedVolume
            order.status = newStatus

            # 推送订单
            if orderUpdated:
                self.gateway.onOrder(order)

            # 推送成交
            if tradeUpdated:
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
                trade.volume = newVolume
                trade.tradeTime = datetime.now().strftime('%H:%M:%S')

                self.gateway.onTrade(trade)

    #----------------------------------------------------------------------
    def onQueryTickers(self, data, req):
        """"""
        dt = datetime.now()
        date = dt.strftime('%Y%m%d')
        time = dt.strftime('%H:%M:%S')

        for symbol in data:
            if symbol.upper() not in self.symbols:
                continue

            t = data[symbol]
            tick = self.getTick(symbol)
            tick.lastPrice = float(t['price'])
            tick.volume = float(t['volume'])
            tick.highPrice = float(t['high'])
            tick.lowPrice = float(t['low'])
            tick.datetime = datetime
            tick.date = date
            tick.time = time

            self.gateway.onTick(tick)

    #----------------------------------------------------------------------
    def onQueryDepth(self, data, req):
        """"""
        symbol = req[1].split("/")[2]

        tick = self.getTick(symbol)

        for n, bid in enumerate(data['bids'][:5]):
            tick.__setattr__('bidPrice%s' %(n+1), float(bid[0]))
            tick.__setattr__('bidVolume%s' %(n+1), float(bid[1]))

        for n, ask in enumerate(data['asks'][:5]):
            tick.__setattr__('askPrice%s' %(n+1), float(ask[0]))
            tick.__setattr__('askVolume%s' %(n+1), float(ask[1]))

        tick.datetime = datetime.now()
        tick.date = tick.datetime.strftime('%Y%m%d')
        tick.time = tick.datetime.strftime('%H:%M:%S')

        if tick.lastPrice:
            self.gateway.onTick(tick)

    #----------------------------------------------------------------------
    def onSendOrder(self, data, req):
        """"""
        order = self.reqOrderDict[reqid]
        localID = order.orderID
        sysID = data['id']

        self.localSysDict[localID] = sysID
        self.orderDict[sysID] = order

        self.gateway.onOrder(order)

        # 发出等待的撤单委托
        if localID in self.cancelDict:
            req = self.cancelDict[localID]
            self.cancelOrder(req)
            del self.cancelDict[localID]

    #----------------------------------------------------------------------
    def getTick(self, symbol):
        """"""
        tick = self.tickDict.get(symbol, None)

        if not tick:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName
            tick.symbol = symbol
            tick.exchange = self.gateway.exchange
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            self.tickDict[symbol] = tick

        return tick

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """快速记录日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

