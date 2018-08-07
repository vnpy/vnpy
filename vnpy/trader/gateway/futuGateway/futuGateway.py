# encoding: UTF-8

'''
富途证券的gateway接入
'''

import json
from collections import OrderedDict
from threading import Thread
from time import sleep
from datetime import datetime
from copy import copy

from futuquant import (OpenQuoteContext, OpenHKTradeContext, OpenUSTradeContext,
                       RET_ERROR, RET_OK, 
                       TrdEnv, TrdSide, OrderType, OrderStatus, ModifyOrderOp,
                       StockQuoteHandlerBase, OrderBookHandlerBase,
                       TradeOrderHandlerBase, TradeDealHandlerBase)

from vnpy.trader.vtGateway import *
from vnpy.trader.vtConstant import GATEWAYTYPE_INTERNATIONAL
from vnpy.trader.vtFunction import getJsonPath


# 调用一次datetime，保证初始化
tmp = datetime.strptime('20171123', '%Y%m%d')

# 常量数据映射
productMap = OrderedDict()
productMap[PRODUCT_EQUITY] = 'STOCK'
productMap[PRODUCT_INDEX] = 'IDX'
productMap[PRODUCT_ETF] = 'ETF'
productMap[PRODUCT_WARRANT] = 'WARRANT'
productMap[PRODUCT_BOND] = 'BOND'

directionMap = {}
directionMap[DIRECTION_LONG] = TrdSide.BUY
directionMap[DIRECTION_SHORT] = TrdSide.SELL
directionMapReverse = {v:k for k,v in directionMap.items()}

statusMapReverse = {}
statusMapReverse[OrderStatus.NONE] = STATUS_UNKNOWN
statusMapReverse[OrderStatus.SUBMITTED] = STATUS_NOTTRADED
statusMapReverse[OrderStatus.FILLED_PART] = STATUS_PARTTRADED
statusMapReverse[OrderStatus.FILLED_ALL] = STATUS_ALLTRADED
statusMapReverse[OrderStatus.CANCELLED_ALL] = STATUS_CANCELLED
statusMapReverse[OrderStatus.CANCELLED_PART] = STATUS_CANCELLED
statusMapReverse[OrderStatus.SUBMIT_FAILED] = STATUS_REJECTED
statusMapReverse[OrderStatus.FAILED] = STATUS_REJECTED
statusMapReverse[OrderStatus.DISABLED] = STATUS_CANCELLED



########################################################################
class FutuGateway(VtGateway):
    """富途接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='FUTU'):
        """Constructor"""
        super(FutuGateway, self).__init__(eventEngine, gatewayName)
        
        self.quoteCtx = None
        self.tradeCtx = None
        
        self.host = ''
        self.ip = 0
        self.market = ''
        self.password = ''
        self.env = TrdEnv.SIMULATE  # 默认仿真交易
        
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)
        
        self.tickDict = {}
        self.tradeSet = set()       # 保存成交编号的集合，防止重复推送
        
        self.qryEnabled = True
        self.qryThread = Thread(target=self.qryData)
        
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """输出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.onLog(log)
        
    #----------------------------------------------------------------------
    def writeError(self, code, msg):
        """输出错误"""
        error = VtErrorData()
        error.gatewayName = self.gatewayName
        error.errorID = code
        error.errorMsg = msg
        self.onError(error)
        
    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入配置
        try:
            f = open(self.filePath)
            setting = json.load(f)
            self.host = setting['host']
            self.port = setting['port']
            self.market = setting['market']
            self.password = setting['password']
            self.env = setting['env']
        except:
            self.writeLog(u'载入配置文件出错')
            return
        
        self.connectQuote()
        self.connectTrade()
        
        self.qryThread.start()
        
    #----------------------------------------------------------------------
    def qryData(self):
        """初始化时查询数据"""
        # 等待2秒保证行情和交易接口启动完成
        sleep(2.0)
        
        # 查询合约、成交、委托、持仓、账户
        self.qryContract()
        self.qryTrade()
        self.qryOrder()
        self.qryPosition()
        self.qryAccount()
        
        # 启动循环查询
        self.initQuery()
        
    #----------------------------------------------------------------------
    def connectQuote(self):
        """连接行情功能"""
        self.quoteCtx = OpenQuoteContext(self.host, self.port)
        
        # 继承实现处理器类
        class QuoteHandler(StockQuoteHandlerBase):
            """报价处理器"""
            gateway = self  # 缓存Gateway对象
            
            def on_recv_rsp(self, rsp_str):
                ret_code, content = super(QuoteHandler, self).on_recv_rsp(rsp_str)
                if ret_code != RET_OK:
                    return RET_ERROR, content
                self.gateway.processQuote(content)
                return RET_OK, content            
            
        class OrderBookHandler(OrderBookHandlerBase):
            """订单簿处理器"""
            gateway = self
            
            def on_recv_rsp(self, rsp_str):
                ret_code, content = super(OrderBookHandler, self).on_recv_rsp(rsp_str)
                if ret_code != RET_OK:
                    return RET_ERROR, content
                self.gateway.processOrderBook(content)
                return RET_OK, content
        
        # 设置回调处理对象
        self.quoteCtx.set_handler(QuoteHandler())
        self.quoteCtx.set_handler(OrderBookHandler())
        
        # 启动行情
        self.quoteCtx.start()
        
        self.writeLog(u'行情接口连接成功')
        
    #----------------------------------------------------------------------
    def connectTrade(self):
        """连接交易功能"""
        # 连接交易接口
        if self.market == 'US':
            self.tradeCtx = OpenUSTradeContext(self.host, self.port)
        else:
            self.tradeCtx = OpenHKTradeContext(self.host, self.port)
            
        # 继承实现处理器类
        class OrderHandler(TradeOrderHandlerBase):
            """委托处理器"""
            gateway = self  # 缓存Gateway对象
            
            def on_recv_rsp(self, rsp_str):
                ret_code, content = super(OrderHandler, self).on_recv_rsp(rsp_str)
                if ret_code != RET_OK:
                    return RET_ERROR, content
                self.gateway.processOrder(content)
                return RET_OK, content            
            
        class DealHandler(TradeDealHandlerBase):
            """订单簿处理器"""
            gateway = self
            
            def on_recv_rsp(self, rsp_str):
                ret_code, content = super(DealHandler, self).on_recv_rsp(rsp_str)
                if ret_code != RET_OK:
                    return RET_ERROR, content
                self.gateway.processDeal(content)
                return RET_OK, content  

        # 只有港股实盘交易才需要解锁
        code, data = self.tradeCtx.unlock_trade(self.password)
        if code == RET_OK:
            self.writeLog(u'交易接口解锁成功')
        else:
            self.writeLog(u'交易接口解锁失败，原因：%s' %data)
        
        # 设置回调处理对象
        self.tradeCtx.set_handler(OrderHandler())
        self.tradeCtx.set_handler(DealHandler())        
        
        # 启动交易接口
        self.tradeCtx.start()
        
        self.writeLog(u'交易接口连接成功')
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        for data_type in ['QUOTE', 'ORDER_BOOK']:
            code, data = self.quoteCtx.subscribe(subscribeReq.symbol, data_type, True)
            
            if code:
                self.writeError(code, u'订阅行情失败：%s' %data)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        side = directionMap[orderReq.direction]
        priceType = OrderType.NORMAL        # 只支持限价单
        
        # 设置价格调整模式为向内调整（即买入调整后价格比原始价格低）
        if orderReq.direction ==  DIRECTION_LONG:
            adjustLimit = 0.05
        else:
            adjustLimit = -0.05
            
        code, data = self.tradeCtx.place_order(orderReq.price, orderReq.volume, 
                                               orderReq.symbol, side, priceType, 
                                               trd_env=self.env,
                                               adjust_limit=adjustLimit)
        
        if code:
            self.writeError(code, u'委托失败：%s' %data)
            return ''
        
        for ix, row in data.iterrows():
            orderID = str(row['order_id'])
        
        vtOrderID = '.'.join([self.gatewayName, orderID])
        
        return vtOrderID
        
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        code, data = self.tradeCtx.modify_order(ModifyOrderOp.CANCEL, cancelOrderReq.orderID, 
                                                0, 0, trd_env=self.env) 
        
        if code:
            self.writeError(code, u'撤单失败：%s' %data)
            return
    
    #----------------------------------------------------------------------
    def qryContract(self):
        """查询合约"""
        for vtProductClass, product in productMap.items():
            code, data = self.quoteCtx.get_stock_basicinfo(self.market, product)
            
            if code:
                self.writeError(code, u'查询合约信息失败：%s' %data)
                return
            
            for ix, row in data.iterrows():
                contract = VtContractData()
                contract.gatewayName = self.gatewayName
                
                contract.symbol = row['code']
                contract.vtSymbol = contract.symbol
                contract.name = row['name']
                contract.productClass = vtProductClass
                contract.size = int(row['lot_size'])
                contract.priceTick = 0.001
                
                self.onContract(contract)
        
        self.writeLog(u'合约信息查询成功')
    
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        code, data = self.tradeCtx.accinfo_query(trd_env=self.env, acc_id=0)
        
        if code:
            self.writeError(code, u'查询账户资金失败：%s' %data)
            return
        
        for ix, row in data.iterrows():
            account = VtAccountData()
            account.gatewayName = self.gatewayName
            
            account.accountID = '%s_%s' %(self.gatewayName, self.market)
            account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
            account.balance = float(row['total_assets'])
            account.available = float(row['avl_withdrawal_cash'])
            
            self.onAccount(account)
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        code, data = self.tradeCtx.position_list_query(trd_env=self.env, acc_id=0)
        
        if code:
            self.writeError(code, u'查询持仓失败：%s' %data)
            return
            
        for ix, row in data.iterrows():
            pos = VtPositionData()
            pos.gatewayName = self.gatewayName
            
            pos.symbol = row['code']
            pos.vtSymbol = pos.symbol
            
            pos.direction = DIRECTION_LONG
            pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
            
            pos.position = float(row['qty'])
            pos.price = float(row['cost_price'])
            pos.positionProfit = float(row['pl_val'])
            pos.frozen = float(row['qty']) - float(row['can_sell_qty'])
            
            if pos.price < 0: pos.price = 0 
            if pos.positionProfit > 100000000: pos.positionProfit = 0 
            
            self.onPosition(pos)
            
    #----------------------------------------------------------------------
    def qryOrder(self):
        """查询委托"""
        code, data = self.tradeCtx.order_list_query("", trd_env=self.env)
        
        if code:
            self.writeError(code, u'查询委托失败：%s' %data)
            return
        
        self.processOrder(data)
        self.writeLog(u'委托查询成功')
    
    #----------------------------------------------------------------------
    def qryTrade(self):
        """查询成交"""
        code, data = self.tradeCtx.deal_list_query(self.env)
        
        if code:
            self.writeError(code, u'查询成交失败：%s' %data)
            return
        
        self.processDeal(data)
        self.writeLog(u'成交查询成功')
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        if self.quoteCtx:
            self.quoteCtx.close()
        if self.tradeCtx:
            self.tradeCtx.close()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.qryAccount, self.qryPosition]
            
            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 2         # 查询触发点
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
        
    #----------------------------------------------------------------------
    def processQuote(self, data):
        """报价推送"""
        for ix, row in data.iterrows():
            symbol = row['code']
    
            tick = self.tickDict.get(symbol, None)
            if not tick:
                tick = VtTickData()
                tick.symbol = symbol
                tick.vtSymbol = tick.symbol
                tick.gatewayName = self.gatewayName
                self.tickDict[symbol] = tick
                
            tick.date = row['data_date'].replace('-', '')
            tick.time = row['data_time']
            tick.datetime = datetime.strptime(' '.join([tick.date, tick.time]), '%Y%m%d %H:%M:%S')
            tick.openPrice = row['open_price']
            tick.highPrice = row['high_price']
            tick.lowPrice = row['low_price']
            tick.preClosePrice = row['prev_close_price']
            
            tick.lastPrice = row['last_price']
            tick.volume = row['volume']
            
            if 'price_spread' in row:
                spread = row['price_spread']
                tick.upperLimit = tick.lastPrice + spread * 10
                tick.lowerLimit = tick.lastPrice - spread * 10
            
            newTick = copy(tick)
            self.onTick(newTick)
    
    #----------------------------------------------------------------------
    def processOrderBook(self, data):
        """订单簿推送"""
        symbol = data['code']
    
        tick = self.tickDict.get(symbol, None)
        if not tick:
            tick = VtTickData()
            tick.symbol = symbol
            tick.vtSymbol = tick.symbol
            tick.gatewayName = self.gatewayName
            self.tickDict[symbol] = tick
        
        d = tick.__dict__
        for i in range(5):
            bidData = data['Bid'][i]
            askData = data['Ask'][i]
            n = i + 1
            
            d['bidPrice%s' %n] = bidData[0]
            d['bidVolume%s' %n] = bidData[1]
            d['askPrice%s' %n] = askData[0]
            d['askVolume%s' %n] = askData[1]
        
        if tick.datetime:
            newTick = copy(tick)
            self.onTick(newTick)
    
    #----------------------------------------------------------------------
    def processOrder(self, data):
        """处理委托推送"""
        for ix, row in data.iterrows():
            # 如果状态是已经删除，则直接忽略
            if row['order_status'] == OrderStatus.DELETED:
                continue
            
            print(row['order_status'])
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            
            order.symbol = row['code']
            order.vtSymbol = order.symbol
            
            order.orderID = str(row['order_id'])
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.price = float(row['price'])
            order.totalVolume = float(row['qty'])
            order.tradedVolume = float(row['dealt_qty'])
            order.orderTime = row['create_time'].split(' ')[-1]      

            order.status = statusMapReverse.get(row['order_status'], STATUS_UNKNOWN)
            order.direction = directionMapReverse[row['trd_side']]
            
            self.onOrder(order)        
    
    #----------------------------------------------------------------------
    def processDeal(self, data):
        """处理成交推送"""
        for ix, row in data.iterrows():
            tradeID = str(row['deal_id'])
            if tradeID in self.tradeSet:
                continue
            self.tradeSet.add(tradeID)
            
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            
            trade.symbol = row['code']
            trade.vtSymbol = trade.symbol
            
            trade.tradeID = tradeID
            trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
            
            trade.orderID = row['order_id']
            trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
            
            trade.price = float(row['price'])
            trade.volume = float(row['qty'])
            trade.direction = directionMapReverse[row['trd_side']]
            
            trade.tradeTime = row['create_time'].split(' ')[-1]
            
            self.onTrade(trade)