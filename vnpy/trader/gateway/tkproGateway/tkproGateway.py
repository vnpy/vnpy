# encoding: UTF-8

'''
quantOS的TkPro系统接入
'''

import sys
import os
import json
import traceback
from datetime import datetime

from vnpy.trader.vtConstant import *
from vnpy.trader.vtObject import *
from vnpy.trader.vtGateway import VtGateway
from vnpy.trader.vtFunction import getJsonPath
from vnpy.trader.vtEvent import EVENT_TIMER

from .DataApi import DataApi
from .TradeApi import TradeApi
from collections import namedtuple



# 以下为一些VT类型和TkPro类型的映射字典

# 动作印射
actionMap = {}
actionMap[(DIRECTION_LONG, OFFSET_OPEN)] = "Buy"
actionMap[(DIRECTION_SHORT, OFFSET_OPEN)] = "Short"
actionMap[(DIRECTION_LONG, OFFSET_CLOSE)] = "Cover"
actionMap[(DIRECTION_SHORT, OFFSET_CLOSE)] = "Sell"
actionMap[(DIRECTION_LONG, OFFSET_CLOSEYESTERDAY)] = "CoverYesterday"
actionMap[(DIRECTION_SHORT, OFFSET_CLOSEYESTERDAY)] = "SellYesterday"
actionMap[(DIRECTION_LONG, OFFSET_CLOSETODAY)] = "CoverToday"
actionMap[(DIRECTION_SHORT, OFFSET_CLOSETODAY)] = "SellToday"
actionMapReverse = {v: k for k, v in actionMap.items()}

# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_CFFEX] = 'CFE'
exchangeMap[EXCHANGE_SHFE] = 'SHF'
exchangeMap[EXCHANGE_CZCE] = 'CZC'
exchangeMap[EXCHANGE_DCE] = 'DCE'
exchangeMap[EXCHANGE_SSE] = 'SH'
exchangeMap[EXCHANGE_SZSE] = 'SZ'
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}


# 持仓类型映射
sideMap = {}
sideMap[DIRECTION_LONG] = 'Long'
sideMap[DIRECTION_SHORT] = 'Short'
sideMapReverse = {v:k for k,v in sideMap.items()}

# 产品类型映射
productClassMapReverse = {}
productClassMapReverse[1] = PRODUCT_EQUITY
productClassMapReverse[3] = PRODUCT_EQUITY
productClassMapReverse[4] = PRODUCT_EQUITY
productClassMapReverse[5] = PRODUCT_EQUITY
productClassMapReverse[8] = PRODUCT_BOND
productClassMapReverse[17] = PRODUCT_BOND
productClassMapReverse[101] = PRODUCT_FUTURES
productClassMapReverse[102] = PRODUCT_FUTURES
productClassMapReverse[103] = PRODUCT_FUTURES

# 委托状态映射
statusMapReverse = {}
statusMapReverse['New'] = STATUS_UNKNOWN
statusMapReverse['Accepted'] = STATUS_NOTTRADED
statusMapReverse['Cancelled'] = STATUS_CANCELLED
statusMapReverse['Filled'] = STATUS_ALLTRADED
statusMapReverse['Rejected'] = STATUS_REJECTED



########################################################################
class TkproGateway(VtGateway):
    """TkPro接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventengine, gatewayName='TKPRO'):
        """Constructor"""
        super(TkproGateway, self).__init__(eventengine, gatewayName)
        
        self.dataApi = TkproDataApi(self)      # 行情
        self.tradeApi = TkproTradeApi(self)    # 交易
        
        self.qryEnabled = False         # 是否要启动循环查询
        
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
            log.logContent = u'无法加载配置'
            self.onLog(log)
            return
        
        setting = json.load(f)
        try:
            username = str(setting['username'])
            token = str(setting['token'])
            strategy = int(setting['strategy'])
            tradeAddress = str(setting['tradeAddress'])
            dataAddress = str(setting['dataAddress'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return

        # 创建行情和交易接口对象
        self.dataApi.connect(dataAddress, username, token)
        self.tradeApi.connect(tradeAddress, username, token, strategy)
        
        # 初始化并启动查询
        self.initQuery()
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        self.dataApi.subscribe(subscribeReq)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        self.tradeApi.sendOrder(orderReq)
     
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.tradeApi.cancelOrder(cancelOrderReq)
 
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        self.tradeApi.qryAccount()
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.tradeApi.qryPosition()
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        pass
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.qryPosition, self.qryAccount]
            
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
    

########################################################################
class TkproTradeApi(object):
    """TkPro交易API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(TkproTradeApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.api = None
    
    #----------------------------------------------------------------------
    def onOrderStatus(self, data):
        """委托信息推送"""
        if isinstance(data, dict):
            data = namedtuple('Order', list(data.keys()))(*list(data.values()))
        
        order = VtOrderData()
        order.gatewayName = self.gatewayName
    
        symbol, exchange = data.security.split('.')
        order.symbol = symbol
        order.exchange = exchangeMapReverse[exchange]
        order.vtSymbol = '.'.join([order.symbol, order.exchange])
    
        order.orderID = str(data.entrust_no)
        order.taskID = str(data.task_id)
        order.vtOrderID = order.orderID
        
        order.direction, order.offset = actionMapReverse.get(data.entrust_action, (DIRECTION_UNKNOWN, OFFSET_UNKNOWN))
        order.totalVolume = data.entrust_size
        order.tradedVolume = data.fill_size
        order.price = data.entrust_price
        order.status = statusMapReverse.get(data.order_status)
        order.tradePrice = data.fill_price 

        t = str(data.entrust_time)
        t = t.rjust(6, '0')
        order.orderTime = '%s:%s:%s' %(t[0:2],t[2:4],t[4:])   
        
        self.gateway.onOrder(order)
    
    #----------------------------------------------------------------------
    def onTaskStatus(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onTrade(self, data):
        """成交信息推送"""
        if isinstance(data, dict):
            data = namedtuple('Trade', list(data.keys()))(*list(data.values()))
            
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        symbol, exchange = data.security.split('.')
        trade.symbol = symbol
        trade.exchange = exchangeMapReverse[exchange]
        trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
        
        trade.direction, trade.offset = actionMapReverse.get(data.entrust_action, (DIRECTION_UNKNOWN, OFFSET_UNKNOWN))
        
        trade.tradeID = str(data.fill_no)
        trade.vtTradeID = str(data.fill_no)
        
        trade.orderID = str(data.entrust_no)
        trade.vtOrderID = trade.orderID
        trade.taskID = str(data.task_id)
        
        trade.price = data.fill_price
        trade.volume = data.fill_size
        
        t = str(data.fill_time)
        t = t.rjust(6, '0')
        trade.tradeTime = '%s:%s:%s' %(t[0:2],t[2:4],t[4:])        
        
        self.gateway.onTrade(trade)
        
    #----------------------------------------------------------------------
    def onConnection(self, data):
        """"""
        self.writeLog(u'连接状态更新：%s' %data)
        
        if data:
            self.qryInstrument()
            self.qryOrder()
            self.qryTrade()        

    #----------------------------------------------------------------------
    def connect(self, tradeAddress, username, token, strategy):
        """初始化连接"""
        if self.api:
            self.writeLog(u'交易已经连接')
            return
        
        self.api = TradeApi(tradeAddress)
        self.api.set_data_format('obj')
        
        # 登录
        result, msg = self.api.login(username, token)
        
        if not result:
            self.writeLog(u'交易登录失败，错误信息：%s' %msg)
            return
        
        result, msg = self.api.use_strategy(strategy)
        
        if result:
            self.writeLog(u'选定策略号：%s' %strategy)
        else:
            self.writeLog(u'选定策略号失败')
        
        self.api.set_ordstatus_callback(self.onOrderStatus)
        self.api.set_trade_callback(self.onTrade)
        self.api.set_task_callback(self.onTaskStatus)
        self.api.set_connection_callback(self.onConnection)

    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        pass
            
    #----------------------------------------------------------------------
    def writeLog(self, logContent):
        """记录日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = logContent
        self.gateway.onLog(log)
    
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        if not self.api:
            return
        
        exchange = exchangeMap.get(orderReq.exchange, '')
        security = '.'.join([orderReq.symbol, exchange])        
        action = actionMap.get((orderReq.direction, orderReq.offset), '')
        
        taskid, msg = self.api.place_order(security, action, orderReq.price, int(orderReq.volume))
        
        if taskid is 0:
            self.writeLog(u'委托失败，错误信息：%s' %msg)
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        if not self.api:
            return

        result, msg = self.api.cancel_order(cancelOrderReq.orderID)
        if result is 0:
            self.writeLog(u'撤单失败，错误信息：%s' %msg)             
    
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        l, msg = self.api.query_position()
        
        if l is None:
            self.writeLog(u'查询持仓失败，错误信息：%s' %msg)  
            return False
        
        for data in l:
            position = VtPositionData()
            position.gatewayName = self.gatewayName
            
            symbol, exchange = data.security.split('.')
            position.symbol = symbol
            position.exchange = exchangeMapReverse[exchange]
            position.vtSymbol = '.'.join([position.symbol, position.exchange])
                        
            position.direction = sideMapReverse.get(data.side, DIRECTION_UNKNOWN)
            position.vtPositionName = '.'.join([position.vtSymbol, position.direction])
            
            position.price = data.cost_price
            position.ydPosition = data.pre_size
            position.tdPosition = data.today_size
            position.position = data.current_size
            position.frozen = data.frozen_size
            
            position.commission = data.commission
            position.enable = data.enable_size  
            position.want = data.want_size
            position.initPosition = data.init_size
            position.trading = data.trading_pnl
            position.holding = data.holding_pnl
            position.last = data.last_price
        
            self.gateway.onPosition(position)
        
        return True
    
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询资金"""
        l, msg = self.api.query_account()
        
        if l is None:
            self.writeLog(u'查询资金失败，错误信息：%s' %msg)  
            return False
        
        for data in l:
            account = VtAccountData()
            account.gatewayName = self.gatewayName
                
            account.accountID = '_'.join([str(data.id), data.type])
            account.vtAccountID = '.'.join([account.accountID, account.gatewayName])
            account.available = data.enable_balance
            account.balance = account.available + data.frozen_balance
            account.closeProfit = data.close_pnl
            account.commission = data.commission
            account.margin = data.margin
            account.positionProfit = data.holding_pnl
            account.preBalance = data.init_balance
            
            self.gateway.onAccount(account)
    
    #----------------------------------------------------------------------
    def qryOrder(self):
        """查询委托"""
        l, msg = self.api.query_order()
        
        if l is None:
            self.writeLog(u'查询委托失败，错误信息：%s' %msg)
        else:
            for data in l:
                self.onOrderStatus(data)
                
            self.writeLog(u'查询委托完成')
    
    #----------------------------------------------------------------------
    def qryTrade(self):
        """查询成交"""
        l, msg = self.api.query_trade()
        
        if l is None:
            self.writeLog(u'查询成交失败，错误信息：%s' %msg)
            return False
        
        for data in l:
            self.onTrade(data)
            
        self.writeLog(u'查询成交完成')
        return True
    
    #----------------------------------------------------------------------
    def qryInstrument(self):
        """查询合约"""
        # 通过DataAPI查询所有信息
        df, msg = self.gateway.dataApi.api.query(
            view='jz.instrumentInfo',
            fields='symbol,name,inst_type,buylot,pricetick,multiplier',
            filter='inst_type=1',
            data_format='pandas'
            )
        
        d = {}
        for n, row in df.iterrows():
            d[row.symbol] = row
        
        # 查询所有信息
        l, msg = self.api.query_universe()
        
        if l is None:
            self.writeLog(u'查询合约失败，错误信息：%s' %msg)
            return False
        
        for data in l:
            row = d[data.security]
            
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            
            symbol, exchange = data.security.split('.')
            contract.symbol = symbol
            contract.exchange = exchangeMapReverse[exchange]
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.productClass = PRODUCT_EQUITY
            contract.name = unicode(row['name'])
            contract.priceTick = float(row['pricetick'])
            contract.size = int(row['multiplier'])
            
            self.gateway.onContract(contract)
            
        self.writeLog(u'查询合约完成')
        return True
    
    
########################################################################
class TkproDataApi(object):
    """TkPro行情API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(TkproDataApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        
        self.api = None
        
        self.fields = "open,close,high,low,last,\
        volume,turnover,oi,preclose,time,date,\
        askprice1,askprice2,askprice3,askprice4,askprice5,\
        bidprice1,bidprice2,bidprice3,bidprice4,bidprice5,\
        askvolume1,askvolume2,askvolume3,askvolume4,askvolume5,\
        bidvolume1,bidvolume2,bidvolume3,bidvolume4,bidvolume5,\
        limit_up,limit_down"
        
    #----------------------------------------------------------------------
    def onMarketData(self, k, data):	
        """行情推送"""
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
        
        try:
            l = data['symbol'].split('.')
            tick.symbol = l[0]
            tick.exchange = exchangeMapReverse[l[1]]
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            
            tick.openPrice = data['open']
            tick.highPrice = data['high']
            tick.lowPrice = data['low']
            tick.volume = data['volume']
            tick.turnover = data['turnover']
            tick.lastPrice = data['last']
            
            tick.openInterest = data['oi']
            tick.preClosePrice = data['preclose']
            tick.date = str(data['date'])
            
            t = str(data['time'])
            t = t.rjust(9, '0')
            tick.time = '%s:%s:%s.%s' %(t[0:2],t[2:4],t[4:6],t[6:])
            
            tick.bidPrice1 = data['bidprice1']
            tick.askPrice1 = data['askprice1']
            tick.bidVolume1 = data['bidvolume1']
            tick.askVolume1 = data['askvolume1']
            
            if 'bidprice2' in data:
                tick.bidPrice2 = data['bidprice2']
                tick.bidPrice3 = data['bidprice3']
                tick.bidPrice4 = data['bidprice4']
                tick.bidPrice5 = data['bidprice5']
                
                tick.askPrice2 = data['askprice2']
                tick.askPrice3 = data['askprice3']
                tick.askPrice4 = data['askprice4']
                tick.askPrice5 = data['askprice5']
        
                tick.bidVolume2 = data['bidvolume2']
                tick.bidVolume3 = data['bidvolume3']
                tick.bidVolume4 = data['bidvolume4']
                tick.bidVolume5 = data['bidvolume5']
        
                tick.askVolume2 = data['askvolume2']
                tick.askVolume3 = data['askvolume3']
                tick.askVolume4 = data['askvolume4']
                tick.askVolume5 = data['askvolume5']
            
            tick.upperLimit = data['limit_up']
            tick.lowerLimit = data['limit_down']
    
            self.gateway.onTick(tick)
        except Exception as e:
            self.writeLog(u'行情更新失败，错误信息：%s' % str(e))

    #----------------------------------------------------------------------
    def connect(self, dataAddress, username, token):
        """连接"""
        if self.api:
            self.writeLog(u'行情已经连接')
            return
        
        self.api = DataApi(dataAddress)
        
        result, msg = self.api.login(username, token)
        
        if not result:
            self.writeLog(u'行情登录失败，错误信息：%sa' %str(msg))
            return
        
        self.writeLog(u'行情连接成功')

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        exchange = exchangeMap.get(subscribeReq.exchange, '')
        security = '.'.join([subscribeReq.symbol, exchange])
        
        subscribed, msg = self.api.subscribe(security, fields=self.fields, func=self.onMarketData)
        
        if not subscribed:
            self.writeLog(u'行情订阅失败，错误信息：%s' %str(msg))
    
    #----------------------------------------------------------------------
    def writeLog(self, logContent):
        """记录日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = logContent
        self.gateway.onLog(log)    
   
