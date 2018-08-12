# encoding: UTF-8

from __future__ import absolute_import
import json
from collections import defaultdict

from . import jrpc_server

from vnpy.event import Event
from vnpy.trader.vtFunction import getJsonPath
from vnpy.trader.vtObject import VtLogData, VtOrderReq, VtCancelOrderReq
from vnpy.trader.vtConstant import *
from vnpy.trader.vtEvent import EVENT_ACCOUNT


EVENT_JS_LOG = 'eJsLog'

ACTION_MAP = {}
ACTION_MAP['Buy'] = (DIRECTION_LONG, OFFSET_OPEN)
ACTION_MAP['Sell'] = (DIRECTION_SHORT, OFFSET_CLOSE)
ACTION_MAP['Short'] = (DIRECTION_SHORT, OFFSET_OPEN)
ACTION_MAP['Cover'] = (DIRECTION_LONG, OFFSET_CLOSE)
ACTION_MAP['CoverYesterday'] = (DIRECTION_LONG, OFFSET_CLOSEYESTERDAY)
ACTION_MAP['SellYesterday'] = (DIRECTION_SHORT, OFFSET_CLOSEYESTERDAY)
ACTION_MAP_REVERSE = {v:k for k,v in ACTION_MAP.items()}

STATUS_MAP_REVERSE = {}
STATUS_MAP_REVERSE[STATUS_NOTTRADED] = 'Accepted'
STATUS_MAP_REVERSE[STATUS_PARTTRADED] = 'Accepted'
STATUS_MAP_REVERSE[STATUS_ALLTRADED] = 'Filled'
STATUS_MAP_REVERSE[STATUS_CANCELLED] = 'Cancelled'
STATUS_MAP_REVERSE[STATUS_REJECTED] = 'Rejected'
STATUS_MAP_REVERSE[STATUS_UNKNOWN] = 'New'


EXCHANGE_MAP = {}
EXCHANGE_MAP['SH'] = EXCHANGE_SSE
EXCHANGE_MAP['SZ'] = EXCHANGE_SZSE
EXCHANGE_MAP['CFE'] = EXCHANGE_CFFEX
EXCHANGE_MAP['SHF'] = EXCHANGE_SHFE
EXCHANGE_MAP['DCE'] = EXCHANGE_DCE
EXCHANGE_MAP['CZC'] = EXCHANGE_CZCE
EXCHANGE_MAP_REVERSE = {v:k for k, v in EXCHANGE_MAP.items()}


########################################################################
class JsEngine(object):
    """JAQS服务引擎"""
    settingFileName = 'JS_setting.json'
    settingfilePath = getJsonPath(settingFileName, __file__)    

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        self.server = None      # RPC服务器
        self.cbDict = {}        # 回调函数字典
        self.account = None     # 账户对象
        
        # 注册日志事件类型
        self.mainEngine.registerLogEvent(EVENT_JS_LOG)
        
        # 初始化
        self.initCallback()
        self.initServer()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_ACCOUNT, self.processAccountEvent)
        
    #----------------------------------------------------------------------
    def initCallback(self):
        """初始化回调函数映射"""
        self.cbDict['.sys.heartbeat'] = self.onHeartbeat
        self.cbDict['auth.login'] = self.onLogin
        self.cbDict['auth.use_strategy'] = self.onUseStrategy
        self.cbDict['oms.query_position'] = self.onQueryPosition
        self.cbDict['oms.query_order'] = self.onQueryOrder
        self.cbDict['oms.place_order'] = self.onPlaceOrder
        self.cbDict['oms.cancel_order'] = self.onCancelOrder
        self.cbDict['oms.query_account'] = self.onQueryAccount
        self.cbDict['oms.query_universe'] = self.onQueryUniverse
        
    #----------------------------------------------------------------------
    def initServer(self):
        """初始化"""
        with open(self.settingfilePath) as f:
            setting = json.load(f)
            host = setting['host']
            port = setting['port']
            addr = "tcp://%s:%s" %(host, port)
            
            # 初始化RPC服务器
            self.server = jrpc_server.JRpcServer()
            self.server.on_call = self.onCall
            self.server.listen(addr)
            
            self.writeLog(u'Jaqs服务器启动成功')
            
    #----------------------------------------------------------------------
    def onCall(self, clientId, req):
        """RPC服务回调函数"""
        method = req['method']
        cb = self.cbDict.get(method, None)
        if not cb:
            self.writeLog(u'无法找到方法%s对应的回调函数' %method)
            return
        
        self.writeLog(u'收到请求：%s' %req)
        
        cb(clientId, req)
    
    #----------------------------------------------------------------------
    def onHeartbeat(self, clientId, req):
        """心跳"""
        pass
    
    #----------------------------------------------------------------------
    def onLogin(self, clientId, req):
        """登录"""
        params = req['params']
        
        result = {
            'username': params['username'],
            'name': params['username'],
            'strategies': [1],
            'broker_strategies': [1]
        }
        
        error = [0, '']
        
        self.server.send_rsp(clientId, req, result, error)
        
        self.writeLog(u'发出响应：%s' %result)
    
    #----------------------------------------------------------------------
    def onUseStrategy(self, clientId, req):
        """使用策略"""
        result = req['params']['account_id']
        error = [0, '']
        self.server.send_rsp(clientId, req, result, error)
        
        self.writeLog(u'发出响应：%s' %result)
    
    #----------------------------------------------------------------------
    def onQueryPosition(self, clientId, req):
        """查询持仓"""
        l = self.mainEngine.getAllPositionDetails()
        
        result = defaultdict(list)
        for detail in l:
            security = self.converSymbol(detail.vtSymbol)
            
            # 多头
            if detail.longPos:
                result['security'].append(security)
                result['side'].append('Long')
                
                result['cost_price'].append(0)
                result['float_pnl'].append(0)
                result['close_pnl'].append(0)
                result['trading_pnl'].append(0)
                result['holding_pnl'].append(0)
                result['commission'].append(0)
                result['init_size'].append(0)
                result['current_size'].append(detail.longPos)
                result['enable_size'].append(detail.longPos-detail.longPosFrozen)
                result['frozen_size'].append(detail.longPosFrozen)
                result['uncome_size'].append(0)
                result['pre_size'].append(detail.longYd)
                result['today_size'].append(detail.longTd)
                
            # 空头
            if detail.shortPos:
                result['security'].append(security)
                result['side'].append('Short')
                
                result['cost_price'].append(0)
                result['float_pnl'].append(0)
                result['close_pnl'].append(0)
                result['trading_pnl'].append(0)
                result['holding_pnl'].append(0)
                result['commission'].append(0)
                result['init_size'].append(0)
                result['current_size'].append(detail.shortPos)
                result['enable_size'].append(detail.shortPos-detail.shortPosFrozen)
                result['frozen_size'].append(detail.shortPosFrozen)
                result['uncome_size'].append(0)
                result['pre_size'].append(detail.shortYd)
                result['today_size'].append(detail.shortTd)                
                
        error = [0, '']
        
        self.server.send_rsp(clientId, req, result, error)
        
        self.writeLog(u'发出响应：%s' %result)
    
    #----------------------------------------------------------------------
    def onQueryOrder(self, clientId, req):
        """查询委托"""
        l = self.mainEngine.getAllOrders()
        
        result = defaultdict(list)
        for order in l:
            result['task_id'].append(order.vtOrderID)
            result['entrust_no'].append(order.vtOrderID)
            
            result['entrust_price'].append(order.price)
            result['entrust_size'].append(order.totalVolume)
            result['sub_seq'].append(0)
            result['sub_total'].append(0)
            result['batch_no'].append(0)
            
            result['fill_price'].append(order.price)
            result['fill_size'].append(order.tradedVolume)
            result['algo'].append('')
            result['entrust_action'].append(ACTION_MAP_REVERSE[(order.direction, order.offset)])
            result['order_status'].append(STATUS_MAP_REVERSE[order.status])
            result['security'].append(self.converSymbol(order.vtSymbol))
            
            hh, mm, ss = order.orderTime.split(':')
            result['entrust_time'].append(int(hh)*10000000+
                                          int(mm)*100000+
                                          int(ss)*1000)
            
        error = [0, '']
        
        self.server.send_rsp(clientId, req, result, error)
        
        self.writeLog(u'发出响应：%s' %result)
    
    #----------------------------------------------------------------------
    def onPlaceOrder(self, clientId, req):
        """委托"""
        params = req['params']
        s, e = params['security'].split('.')
        
        contract = self.mainEngine.getContract(s)        

        if not contract:
            vtOrderID = ''
            error = [-1, u'委托失败，找不到合约%s' %params['security']]
        else:
            vor = VtOrderReq()
            vor.symbol = s
            vor.exchange = EXCHANGE_MAP[e]
            vor.direction, vor.offset = ACTION_MAP[params['action']]
            vor.price = float(params['price'])
            vor.volume = int(params['size'])
            vor.priceType = PRICETYPE_LIMITPRICE
            
            vtOrderID = self.mainEngine.sendOrder(vor, contract.gatewayName)
            error = [0, '']
        
        self.server.send_rsp(clientId, req, vtOrderID, error)
        
        self.writeLog(u'发出响应：%s' %vtOrderID)
    
    #----------------------------------------------------------------------
    def onCancelOrder(self, clientId, req):
        """撤单"""
        params = req['params']
        vtOrderID = params['task_id']
        gatewayName, orderID = vtOrderID.split('.')
        
        vcor = VtCancelOrderReq()
        vcor.orderID = vtOrderID
        self.mainEngine.cancelOrder(vcor, gatewayName)
        
        error = [0, '']
        self.server.send_rsp(clientId, req, 'successful', error)
        
        self.writeLog(u'发出响应：%s' %result)

    #----------------------------------------------------------------------
    def onQueryAccount(self, clientId, req):
        """查询账户"""
        params = req['params']
        
        account = self.account
        
        result = defaultdict(list)
        result['id'].append(account.accountID)
        result['init_balance'].append(account.preBalance)
        result['enable_balance'].append(account.available)
        result['margin'].append(account.margin)
        result['float_pnl'].append(0.0)
        result['close_pnl'].append(account.closeProfit)
        result['holding_pnl'].append(0.0)
        result['trading_pnl'].append(0.0)
        result['type'].append('BA')
        
        error = [0, '']
        self.server.send_rsp(clientId, req, result, error)
        
        self.writeLog(u'发出响应：%s' %result)
     
    #----------------------------------------------------------------------
    def onQueryUniverse(self, clientId, req):
        """查询账户"""
        params = req['params']
        
        l = self.mainEngine.getAllContracts()
        
        result = defaultdict(list)
        for contract in l:        
            result['ba_id'].append(1000)
            result['security'].append(self.converSymbol(contract.vtSymbol))
        
        error = [0, '']
        self.server.send_rsp(clientId, req, result, error)
        
        self.writeLog(u'发出响应：%s' %result)
          
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志事件"""
        log = VtLogData()
        log.logContent = content
        log.gatewayName = 'JAQS_SERVICE'
        event = Event(type_=EVENT_JS_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)         
    
    #----------------------------------------------------------------------
    def converSymbol(self, vtSymbol):
        """转换合约代码"""
        contract = self.mainEngine.getContract(vtSymbol)
        if not contract:
            return ''
        
        e = EXCHANGE_MAP_REVERSE.get(contract.exchange, contract.exchange)
        return '.'.join([contract.symbol, e])
        
    #----------------------------------------------------------------------
    def processAccountEvent(self, event):
        """账户资金更新"""
        self.account = event.dict_['data']
    