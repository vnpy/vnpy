# encoding: UTF-8

'''
vn.coincheck的gateway接入
'''
import os
import json
from datetime import datetime
from copy import copy
from threading import Condition
from Queue import Queue
from threading import Thread

import json
from vnpy.api.coincheck import vncoincheck
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath

from datetime import datetime , timedelta

SYMBOL_BTCJPY = 'btc_jpy'
COINCHECK_HOSTS = "wss://ws-api.coincheck.com"

class CoincheckGateway(VtGateway):
    """coincheck 接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='COINCHECK'):
        """Constructor"""
        super(CoincheckGateway, self).__init__(eventEngine, gatewayName)
        
        
        self.tradeApi = CoincheckTradeApi(self)
        #self.dataApi = CoincheckDataApi(self)
        self.dataApi = CoincheckSocketDataApi(self)
        
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)       

        self.total_count = 0
        self.delayTime = 3

    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json文件
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
            accessKey = str(setting['accessKey'])
            secretKey = str(setting['secretKey'])
            interval = setting['interval']
            debug = setting['debug']
            useAccountID = str(setting['accountID'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 设置账户ID
        self.tradeApi.setAccountID( useAccountID)

        # 初始化接口
        self.tradeApi.init(accessKey, secretKey)
        self.writeLog(u'交易接口初始化成功')
        
        #self.dataApi.connect(interval,  debug)
        self.dataApi.connect()
        self.writeLog(u'行情接口初始化成功')

        
        # 启动查询
        self.initQuery()
        self.startQuery()

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.onLog(log)        

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情，自动订阅全部行情，无需实现"""
        pass

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.tradeApi.sendOrder(orderReq)

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        return self.tradeApi.cancel(cancelOrderReq)

    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        pass
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        pass
    
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.tradeApi.exit()
        self.dataApi.exit()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""

        if self.qryEnabled:
            self.qryFunctionList = [self.tradeApi.get_balance , self.tradeApi.list_orders]
            #self.qryFunctionList = [self.tradeApi.queryWorkingOrders, self.tradeApi.queryAccount]

    #----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        self.total_count += 1
        if self.total_count % self.delayTime == 0:
            for function in self.qryFunctionList:
                function()
                
    #----------------------------------------------------------------------
    def startQuery(self):
        """启动连续查询"""
        self.eventEngine.register(EVENT_TIMER, self.query)

    #----------------------------------------------------------------------
    def onListOrder(self, data):
        print data
    
    #----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qryEnabled

class CoincheckTradeApi(vncoincheck.TradeApi):

    def __init__(self, gateway):
        super(CoincheckTradeApi , self).__init__()

        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        self.accountID = "COINCHECK"
        self.DEBUG = False

        self.localID = 0            # 本地委托号
        self.localSystemDict = {}   # key:localID, value:systemID
        self.systemLocalDict = {}   # key:systemID, value:localID
        self.workingOrderDict = {}  # key:localID, value:order
        self.reqLocalDict = {}      # key:reqID, value:localID
        self.cancelDict = {}        # key:localID, value:cancelOrderReq

        self.tradedVolumeDict = {}      # key:localID, value:volume ,已经交易成功的数量

        self.tradeID = 0            # 本地成交号

    #--------------
    def setAccountID(self, useAccountID):
        self.accountID = useAccountID

    #----------------------------------------------------------------------
    
    def onError(self, method ,data):
        print method , data 
    #
    '''
    "return" :
    {u'lending_leverage': u'5.0', u'success': True, u'maker_fee': u'0.0', u'email': u'liyi.riki.thomas@g
mail.com', u'bitcoin_address': u'1Q73J2e46TrBv9cRCtfgcszqEcwNDsei53', u'taker_fee': u'0.0', u'identi
ty_status': u'identity_verified', u'id': 1007549}
    '''
    def onGet_info(self, data, req, reqID):
        """用户信息"""
        print data
    '''
    {u'zec': u'0', u'rep_debt': u'0.0', u'xem': u'0', u'lsk': u'0', u'rep_lend_in_use': u'0.0', u'ltc_de
bt': u'0.0', u'xmr_reserved': u'0.0', u'cny': u'0', u'btc_reserved': u'0.0', u'dao_reserved': u'0.0'
, u'ltc_lent': u'0.0', u'dao_lend_in_use': u'0.0', u'xrp_reserved': u'0.0', u'zec_debt': u'0.0', u'b
ch_lent': u'0.0', u'dao_debt': u'0.0', u'xmr': u'0', u'rep_reserved': u'0.0', u'dao': u'0', u'xem_le
nd_in_use': u'0.0', u'fct_lent': u'0.0', u'jpy_reserved': u'0.0', u'success': True, u'fct_reserved':
 u'0.0', u'xem_lent': u'0.0', u'rep_lent': u'0.0', u'eth_lend_in_use': u'0.0', u'btc': u'0', u'usd_l
end_in_use': u'0.0', u'zec_lent': u'0.0', u'rep': u'0', u'xmr_debt': u'0.0', u'bch_lend_in_use': u'0
.0', u'xrp_debt': u'0.0', u'etc_lend_in_use': u'0.0', u'dash_reserved': u'0.0', u'dash_lent': u'0.0'
, u'dash_debt': u'0.0', u'jpy_lend_in_use': u'0.0', u'lsk_lend_in_use': u'0.0', u'eth_lent': u'0.0',
 u'ltc': u'0', u'etc': u'0', u'ltc_lend_in_use': u'0.0', u'eth': u'0', u'usd_debt': u'0.0', u'ltc_re
served': u'0.0', u'cny_reserved': u'0.0', u'xem_debt': u'0.0', u'eth_reserved': u'0.0', u'zec_reserv
ed': u'0.0', u'usd': u'0', u'cny_lend_in_use': u'0.0', u'lsk_debt': u'0.0', u'xmr_lend_in_use': u'0.
0', u'dash_lend_in_use': u'0.0', u'xrp_lent': u'0.0', u'bch_reserved': u'0.0', u'xmr_lent': u'0.0',
u'bch_debt': u'0.0', u'bch': u'0', u'jpy': u'0', u'fct_debt': u'0.0', u'btc_debt': u'0.0', u'usd_len
t': u'0.0', u'btc_lent': u'0.0', u'lsk_reserved': u'0.0', u'etc_debt': u'0.0', u'jpy_lent': u'0.0',
u'dash': u'0', u'cny_debt': u'0.0', u'xrp_lend_in_use': u'0.0', u'xem_reserved': u'0.0', u'dao_lent'
: u'0.0', u'lsk_lent': u'0.0', u'etc_lent': u'0.0', u'jpy_debt': u'0.0', u'xrp': u'0', u'fct': u'0',
 u'etc_reserved': u'0.0', u'usd_reserved': u'0.0', u'fct_lend_in_use': u'0.0', u'btc_lend_in_use': u
'0.0', u'zec_lend_in_use': u'0.0', u'eth_debt': u'0.0', u'cny_lent': u'0.0'}
    '''
    def onGet_balance(self, data, req, reqID):
        if data["success"] == 0:
            print "Error in onGet_balance"
            print data
        else:
            account = VtAccountData()
            account.gatewayName = self.gatewayName
            account.accountID = self.accountID
            account.vtAccountID = '.'.join([ self.gatewayName , self.accountID])
            account.balance = float(data['jpy'])
            account.available = float(data['jpy'])

            account.margin = 1.0
            account.closeProfit = 0.0
            account.positionProfit = 0.0
            account.commission = 0.0
            account.now_has_hands = float(data['jpy'])


            self.gateway.onAccount(account)

            for symbol in ['btc' , 'jpy']:
                posObj = VtPositionData()
                posObj.gatewayName = self.gatewayName
                posObj.symbol = symbol + "." + EXCHANGE_COINCHECK
                posObj.exchange = EXCHANGE_COINCHECK
                posObj.vtSymbol = posObj.symbol
                posObj.direction = DIRECTION_NET
                posObj.vtPositionName = '.'.join( [posObj.vtSymbol, posObj.direction])
                posObj.ydPosition = float(data[symbol])
                posObj.position = float(data[symbol]) + float(data[symbol + "_reserved"])
                posObj.frozen = float(data[symbol + "_reserved"])
                posObj.positionProfit = 0
                self.gateway.onPosition(posObj)

    '''
    发送系统委托
    '''
    def sendOrder(self, req):
        """发送委托"""
        # 检查是否填入了价格，禁止市价委托
        if req.priceType != PRICETYPE_LIMITPRICE:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorMsg = u'Coincheck接口仅支持限价单'
            err.errorTime = datetime.now().strftime('%H:%M:%S')
            self.gateway.onError(err)
            return None
        symbol = req.vtSymbol
        if req.direction == DIRECTION_LONG:
            reqID = self.buy_btc_jpy( rate = req.price , amount = req.volume )
        else:
            reqID = self.sell_btc_jpy( rate = req.price , amount = req.volume )

        self.localID += 1
        localID = str(self.localID)
        self.reqLocalDict[reqID] = localID

        # 推送委托信息
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = req.symbol
        order.exchange = EXCHANGE_COINCHECK
        order.vtSymbol = order.symbol

        order.orderID = localID
        order.vtOrderID = '.'.join([order.orderID, order.gatewayName])

        order.direction = req.direction
        if req.direction == DIRECTION_LONG:
            order.offset = OFFSET_OPEN
        else:
            order.offset = OFFSET_CLOSE
        order.price = req.price
        order.tradedVolume = 0
        order.totalVolume = req.volume
        order.orderTime = datetime.now().strftime('%H:%M:%S')
        order.status = STATUS_UNKNOWN

        self.workingOrderDict[localID] = order
        self.gateway.onOrder(order)

        # 返回委托号
        return order.vtOrderID


    '''
    {u'market_buy_amount': None, u'order_type': u'buy', u'success': True, u'created_at': u'2017-10-16T13
:53:01.678Z', u'rate': u'100.0', u'amount': u'0.005', u'pair': u'btc_jpy', u'stop_loss_rate': None,
u'id': 324141928}
    '''
    def onBuy_btc(self, data, req, reqID):
        # print "onBuy_btc"
        # print data
        if data["success"] == 0:
            print "Error in onBuy_btc"
            print data
        else:
            localID = self.reqLocalDict[reqID]
            systemID = data['id']
            self.localSystemDict[localID] = systemID
            self.systemLocalDict[systemID] = localID

            # 撤单
            if localID in self.cancelDict:
                req = self.cancelDict[localID]
                self.cancel(req)
                del self.cancelDict[localID]

            # 推送委托信息
            order = self.workingOrderDict[localID]
            if data['success'] != 0:
                order.status = STATUS_NOTTRADED

            self.tradedVolumeDict[localID] = 0.0
            self.gateway.onOrder(order)

    def onSell_btc(self, data, req, reqID):
        # print "onSell_btc"
        # print data
        """卖出回调"""
        if data["success"] == 0:
            print "Error in onSell_btc"
        else:
            localID = self.reqLocalDict[reqID]
            systemID = data['id']
            self.localSystemDict[localID] = systemID
            self.systemLocalDict[systemID] = localID

            # 撤单
            if localID in self.cancelDict:
                req = self.cancelDict[localID]
                self.cancel(req)
                del self.cancelDict[localID]

            # 推送委托信息
            order = self.workingOrderDict[localID]
            if data['success'] != 0:
                order.status = STATUS_NOTTRADED
            self.tradedVolumeDict[localID] = 0.0
            self.gateway.onOrder(order)

    '''
    {u'orders': [{u'order_type': u'buy', u'created_at': u'2017-10-16T13:51:41.000Z', u'pending_market_bu
y_amount': None, u'rate': u'200.0', u'pair': u'btc_jpy', u'stop_loss_rate': None, u'id': 324139122,
u'pending_amount': u'0.005'}, {u'order_type': u'buy', u'created_at': u'2017-10-16T13:53:01.000Z', u'
pending_market_buy_amount': None, u'rate': u'100.0', u'pair': u'btc_jpy', u'stop_loss_rate': None, u
'id': 324141928, u'pending_amount': u'0.005'}], u'success': True}
    只显示 未结算的 订单。  如果订单被结算了，说明已经成交了
    '''
    def onList_order(self, data, req, reqID):
        # print "onList_order"
        # self.gateway.onListOrder( data)
        if data["success"] == 0:
            pass
        else:
            orders = data["orders"]
            now_datetime = datetime.now()
            ten_seconds_before = now_datetime + timedelta(seconds=-10)
            ten_seconds_str = (ten_seconds_before.strftime("%Y-%m-%dT%H:%M:%S.%f"))[:-3] + "Z"

            stile_live_order_system_id = [ x["id"] for x in orders]
            #print "stile_live_order_system_id", stile_live_order_system_id
            local_system_dict_keys = self.systemLocalDict.keys()
            # 对系统中有的订单，进行
            for bef_system_id in local_system_dict_keys:
                if bef_system_id not in stile_live_order_system_id:
                    # 说明这个单子成交完毕了！ 
                    # 或者就是取消了
                    localID = self.systemLocalDict[bef_system_id]
                    order = self.workingOrderDict.get(localID, None)
                    if order != None:
                        bef_has_volume = self.tradedVolumeDict.get(localID , 0.0)
                        newTradeVolume = order.totalVolume - bef_has_volume

                        trade = VtTradeData()
                        trade.gatewayName = self.gatewayName
                        trade.symbol = order.symbol
                        trade.vtSymbol = order.vtSymbol

                        self.tradeID += 1
                        trade.tradeID = str(self.tradeID)
                        trade.vtTradeID = '.'.join([trade.tradeID, trade.gatewayName])
                        trade.orderID = order.orderID
                        trade.vtOrderID =  order.vtOrderID

                        trade.volume = newTradeVolume
                        trade.price = order.price
                        trade.direction = order.direction
                        trade.offset = order.offset
                        trade.exchange = order.exchange
                        trade.tradeTime = datetime.now().strftime('%H:%M:%S')

                        self.gateway.onTrade(trade)

                        order.status = STATUS_ALLTRADED
                        self.gateway.onOrder(order)

                        del self.tradedVolumeDict[localID]
                        del self.systemLocalDict[bef_system_id]
                        del self.workingOrderDict[localID]

            for d in orders:
                coinID = d["id"]
                if coinID in local_system_dict_keys:
                    localID = self.systemLocalDict[coinID]
                    order = self.workingOrderDict.get(localID, None)

                    if order != None:
                        bef_has_volume = self.tradedVolumeDict.get(localID , 0.0)
                        has_traded_volume = d["pending_market_buy_amount"]
                        if has_traded_volume == None:
                            has_traded_volume = 0.0
                        newTradeVolume = float(has_traded_volume) - float(bef_has_volume)

                        if newTradeVolume > 0.00000001:
                            trade = VtTradeData()
                            trade.gatewayName = self.gatewayName
                            trade.symbol = order.symbol
                            trade.vtSymbol = order.vtSymbol

                            self.tradeID += 1
                            trade.tradeID = str(self.tradeID)
                            trade.vtTradeID = '.'.join([trade.tradeID, trade.gatewayName])
                            trade.orderID = order.orderID
                            trade.vtOrderID = order.vtOrderID

                            trade.volume = newTradeVolume
                            trade.price = order.price
                            trade.direction = order.direction
                            trade.offset = order.offset
                            trade.exchange = order.exchange
                            trade.tradeTime = datetime.now().strftime('%H:%M:%S')

                            self.gateway.onTrade(trade)

                            order.tradedVolume = has_traded_volume
                            order.status = STATUS_PARTTRADED
                            self.gateway.onOrder(order)
                else:

                    # 说明这是一个 不知道 哪里来的订单
                    # 推送委托信息
                    # 订单有两种可能
                    # 1、人工发的单
                    # 2、前面取消失败的单   # 总有些订单是取消失败的 , 如果出现了，那么就取消掉这些交易
                    # 所以对于订单进行判断，如果订单时间超过10秒， 那么取消掉
                    
                    if order.orderTime < ten_seconds_str :
                        # 判断为需要取消的单子
                        self.cancel_orders( coinID )
                    else:
                        self.localID += 1
                        localID = str(self.localID)
                        
                        symbol_pair = d['pair']  #  btc_jpy
                        order = VtOrderData()
                        order.gatewayName = self.gatewayName
                        order.symbol = symbol_pair + "." + self.gatewayName
                        order.exchange = EXCHANGE_COINCHECK
                        order.vtSymbol = order.symbol

                        order.orderID = localID
                        order.vtOrderID = '.'.join(["mistake", order.gatewayName])

                        order.direction = DIRECTION_LONG
                        order.offset = OFFSET_OPEN

                        order.price = float(d["rate"])
                        order.totalVolume = float(d["pending_amount"])
                        order.orderTime = d["created_at"]
                        order.status = STATUS_MISTAKE

                        self.workingOrderDict[localID] = order
                        self.systemLocalDict[coinID] = localID
                        self.localSystemDict[localID] = coinID
                        self.gateway.onOrder(order)


    '''
    {
      "success": true,
      "id": 12345
    }
    '''
    def onCancel_orders(self, data, req, reqID):
        # self.gateway.onCancelOrder( data)
        if data['success'] != 0:
            systemID = data["id"]
            localID = self.systemLocalDict[systemID]

            order = self.workingOrderDict[localID]
            order.status = STATUS_CANCELLED

            del self.workingOrderDict[localID]
            del self.systemLocalDict[systemID]
            del self.localSystemDict[localID]
            self.gateway.onOrder(order)

    def onHistory_orders(self, data, req, reqID):
        print data

    def cancel(self, req):
        localID = req.orderID
        if localID in self.localSystemDict:
            systemID = self.localSystemDict[localID]
            self.cancel_orders( systemID )
        else:
            self.cancelDict[localID] = req


class CoincheckSocketDataApi(vncoincheck.DataApiSocket):
    """基于websocket的TICK数据获得对象"""
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        super(CoincheckSocketDataApi, self).__init__()

        self.market = 'jpy'
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName

        self.tickDict = {}      # key:symbol, value:tick

        self.period_flag = False


    def connect(self ):
        super(CoincheckSocketDataApi, self).connect( COINCHECK_HOSTS)

        contract = VtContractData()
        contract.gatewayName = self.gatewayName
        contract.symbol = SYMBOL_BTCJPY
        contract.exchange = EXCHANGE_COINCHECK
        contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
        contract.name = u'日元coincheck现货BTC'
        contract.size = 0.0001
        contract.priceTick = 0.0001
        contract.productClass = PRODUCT_SPOT
        self.gateway.onContract(contract)

    def onOrderbooks(self, data):
        symbol = SYMBOL_BTCJPY
        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName
            tick.exchange = EXCHANGE_COINCHECK
            tick.symbol = '.'.join([symbol, tick.exchange])
            tick.vtSymbol = '.'.join([symbol, tick.exchange])

            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]

        data = json.loads(data)
        load_symbol , dic = data
        if load_symbol == symbol:
            bids = dic["bids"]
            asks = dic["asks"]

            bids = [ (float(x[0]) , float(x[1])) for x in bids ]
            asks = [ (float(x[0]) , float(x[1])) for x in asks ]

            tick.bidPrice1, tick.bidVolume1 = [0 , 0]
            tick.bidPrice2, tick.bidVolume2 = [0 , 0]
            tick.bidPrice3, tick.bidVolume3 = [0 , 0]
            tick.bidPrice4, tick.bidVolume4 = [0 , 0]
            tick.bidPrice5, tick.bidVolume5 = [0 , 0]

            tick.askPrice1, tick.askVolume1 = [0 , 0]
            tick.askPrice2, tick.askVolume2 = [0 , 0]
            tick.askPrice3, tick.askVolume3 = [0 , 0]
            tick.askPrice4, tick.askVolume4 = [0 , 0]
            tick.askPrice5, tick.askVolume5 = [0 , 0]
            try:
                tick.bids = bids
                tick.asks = asks
                tick.bidPrice1, tick.bidVolume1 = bids[0]
                tick.bidPrice2, tick.bidVolume2 = bids[1]
                tick.bidPrice3, tick.bidVolume3 = bids[2]
                tick.bidPrice4, tick.bidVolume4 = bids[3]
                tick.bidPrice5, tick.bidVolume5 = bids[4]
            except Exception,ex:
                pass

            try:
                tick.askPrice1, tick.askVolume1 = asks[0]
                tick.askPrice2, tick.askVolume2 = asks[1]
                tick.askPrice3, tick.askVolume3 = asks[2]
                tick.askPrice4, tick.askVolume4 = asks[3]
                tick.askPrice5, tick.askVolume5 = asks[4]
            except Exception,ex:
                pass

            now = datetime.now()
            tick.time = now.strftime('%H:%M:%S')
            tick.date = now.strftime('%Y%m%d')
            tick.datetime = now

            self.gateway.onTick(tick)
            self.period_flag = False

    def onTrade(self , data):
        
        orderId, symbol , price , volume , direction = data

        price = float(price)
        volume = float(volume)

        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName
            tick.exchange = EXCHANGE_COINCHECK
            tick.symbol = '.'.join([symbol, tick.exchange])
            tick.vtSymbol = '.'.join([symbol, tick.exchange])
            tick.volume = 0

            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]

        if self.period_flag == False:
            self.period_flag = True

            tick.highPrice = price
            tick.lowPrice = price
            tick.lastPrice = price

        else:
            tick.highPrice = max(tick.highPrice , price)
            tick.lowPrice = min(tick.lowPrice , price)
            tick.lastPrice = price

        tick.volume += volume


    def onMessage(self, ws , evt):
        if evt:
            data = json.loads(evt)
            cclen = len(data)
            if cclen == 2:
                self.onOrderbooks( evt)
            elif cclen == 5:
                self.onTrade(data)


class CoincheckDataApi(vncoincheck.DataApi):
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(CoincheckDataApi, self).__init__()
        
        self.market = 'jpy'
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName

        self.tickDict = {}      # key:symbol, value:tick

    def connect(self, interval , market , debug = False):
        self.init(interval , debug)
        # 订阅行情并推送合约信息
        if self.market == 'jpy':
            self.subscribeTick(SYMBOL_BTCJPY)
            self.subscribeOrderbooks(SYMBOL_BTCJPY)

            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            contract.symbol = SYMBOL_BTCJPY
            contract.exchange = EXCHANGE_COINCHECK
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = u'日元coincheck现货BTC'
            contract.size = 0.0001
            contract.priceTick = 0.0001
            contract.productClass = PRODUCT_SPOT
            self.gateway.onContract(contract)
    
    #----------------------------------------------------------------------
    def onTick(self, data):
        """实时成交推送"""
        symbol = SYMBOL_BTCJPY
        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.exchange = EXCHANGE_COINCHECK
            tick.symbol = '.'.join([symbol, tick.exchange])
            tick.vtSymbol = '.'.join([symbol, tick.exchange])
            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]

        tick.highPrice = float(data['high'])
        tick.lowPrice = float(data['low'])
        tick.lastPrice = float(data['last'])
        tick.volume = float(data['volume'])

        now = datetime.now()
        tick.time = now.strftime('%H:%M:%S')
        tick.date = now.strftime('%Y%m%d')
        tick.datetime = now

    #----------------------------------------------------------------------
    def onTrades(self, data):
        """实时成交推送"""
        print data

    #----------------------------------------------------------------------
    def onOrderbooks(self, data):
        """实时成交推送"""
        symbol = SYMBOL_BTCJPY
        bids = data["bids"]
        asks = data["asks"]
        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.symbol = symbol
            tick.exchange = EXCHANGE_COINCHECK
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]

        bids = [ (float(x[0]) , float(x[1])) for x in bids ]
        asks = [ (float(x[0]) , float(x[1])) for x in asks ]
        tick.bidPrice1, tick.bidVolume1 = bids[0]
        tick.bidPrice2, tick.bidVolume2 = bids[1]
        tick.bidPrice3, tick.bidVolume3 = bids[2]
        tick.bidPrice4, tick.bidVolume4 = bids[3]
        tick.bidPrice5, tick.bidVolume5 = bids[4]

        tick.askPrice1, tick.askVolume1 = asks[0]
        tick.askPrice2, tick.askVolume2 = asks[1]
        tick.askPrice3, tick.askVolume3 = asks[2]
        tick.askPrice4, tick.askVolume4 = asks[3]
        tick.askPrice5, tick.askVolume5 = asks[4]


        now = datetime.now()
        tick.time = now.strftime('%H:%M:%S')
        tick.date = now.strftime('%Y%m%d')
        tick.datetime = now

        self.gateway.onTick(tick)

