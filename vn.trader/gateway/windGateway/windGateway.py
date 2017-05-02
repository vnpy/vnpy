# encoding: UTF-8

'''
Wind Python API的gateway接入
'''

from copy import copy

try:
    from WindPy import w
except ImportError:
    print u'请先安装WindPy接口'

from vtGateway import *

# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_SSE] = 'SH'
exchangeMap[EXCHANGE_SZSE] = 'SZ'
exchangeMap[EXCHANGE_CFFEX] = 'CFE'
exchangeMap[EXCHANGE_SHFE] = 'SHF'
exchangeMap[EXCHANGE_DCE] = 'DCE'
exchangeMap[EXCHANGE_CZCE] = 'CZC'
exchangeMap[EXCHANGE_UNKNOWN] = ''
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}


########################################################################
class WindGateway(VtGateway):
    """Wind接口"""
    # 订阅wsq时传入的字段列表
    wsqParamMap = {}
    wsqParamMap['rt_last'] = 'lastPrice'
    wsqParamMap['rt_last_vol'] = 'volume'
    wsqParamMap['rt_oi'] = 'openInterest'

    wsqParamMap['rt_open'] = 'openPrice'
    wsqParamMap['rt_high'] = 'highPrice'
    wsqParamMap['rt_low'] = 'lowPrice'
    wsqParamMap['rt_pre_close'] = 'preClosePrice'
                    
    wsqParamMap['rt_high_limit'] = 'upperLimit'
    wsqParamMap['rt_low_limit'] = 'lowerLimit'

    wsqParamMap['rt_bid1'] = 'bidPrice1'
    wsqParamMap['rt_bid2'] = 'bidPrice2'
    wsqParamMap['rt_bid3'] = 'bidPrice3'
    wsqParamMap['rt_bid4'] = 'bidPrice4'
    wsqParamMap['rt_bid5'] = 'bidPrice5'
                    
    wsqParamMap['rt_ask1'] = 'askPrice1'
    wsqParamMap['rt_ask2'] = 'askPrice2'
    wsqParamMap['rt_ask3'] = 'askPrice3'
    wsqParamMap['rt_ask4'] = 'askPrice4'
    wsqParamMap['rt_ask5'] = 'askPrice5'     
                    
    wsqParamMap['rt_bsize1'] = 'bidVolume1'
    wsqParamMap['rt_bsize2'] = 'bidVolume2'
    wsqParamMap['rt_bsize3'] = 'bidVolume3'
    wsqParamMap['rt_bsize4'] = 'bidVolume4'
    wsqParamMap['rt_bsize5'] = 'bidVolume5'
                    
    wsqParamMap['rt_asize1'] = 'askVolume1'
    wsqParamMap['rt_asize2'] = 'askVolume2'
    wsqParamMap['rt_asize3'] = 'askVolume3'
    wsqParamMap['rt_asize4'] = 'askVolume4'
    wsqParamMap['rt_asize5'] = 'askVolume5'
    
    wsqParam = ','.join(wsqParamMap.keys())

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='Wind'):
        """Constructor"""
        super(WindGateway, self).__init__(eventEngine, gatewayName)
        
        self.w = w                  # Wind API对象
        self.connected = False      # 连接状态
        
        # Wind的wsq更新采用的是增量更新模式，每次推送只会更新发生变化的字段
        # 而vt中的tick是完整更新，因此需要本地维护一个所有字段的快照
        self.tickDict = {}
        
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 由于w.start方法会阻塞较长时间
        # 因此设计为异步模式，交给事件处理线程去处理
        # 另外w.start和WingIDE的debug模块有冲突，会导致异常退出
        event = Event(type_=EVENT_WIND_CONNECTREQ)
        self.eventEngine.put(event)
        
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        windSymbol = '.'.join([subscribeReq.symbol, exchangeMap[subscribeReq.exchange]])
        data = self.w.wsq(windSymbol, self.wsqParam, func=self.wsqCallBack)
    
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        log = VtLogData()
        log.gatewayName = self.gatewayName        
        log.logContent = u'Wind接口未实现发单功能'
        self.onLog(log) 
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        log = VtLogData()
        log.gatewayName = self.gatewayName        
        log.logContent = u'Wind接口未实现撤单功能'
        self.onLog(log) 
    
    #----------------------------------------------------------------------
    def getAccount(self):
        """查询账户资金"""
        log = VtLogData()
        log.gatewayName = self.gatewayName        
        log.logContent = u'Wind接口未实现查询账户功能'
        self.onLog(log) 
    
    #----------------------------------------------------------------------
    def getPosition(self):
        """查询持仓"""
        log = VtLogData()
        log.gatewayName = self.gatewayName        
        log.logContent = u'Wind接口未实现查询持仓功能'
        self.onLog(log) 
    
    #----------------------------------------------------------------------
    def close(self):
        self.w.stop()
     
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_WIND_CONNECTREQ, self.wConnect)
        
    #----------------------------------------------------------------------
    def wsqCallBack(self, data):
        """收到wsq推送"""
        windSymbol = data.Codes[0]
        if windSymbol in self.tickDict:
            tick = self.tickDict[windSymbol]
        else:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName
            symbolSplit = windSymbol.split('.')
            tick.symbol = symbolSplit[0]
            tick.exchange = exchangeMapReverse[symbolSplit[1]]  
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            self.tickDict[windSymbol] = tick

        dt = data.Times[0]
        tick.time = dt.strftime('%H:%M:%S')
        tick.date = dt.strftime('%Y%m%d')
        
        # 采用遍历的形式读取数值
        fields = data.Fields
        values = data.Data
        d = tick.__dict__
        for n, field in enumerate(fields):
            field = field.lower()
            key = self.wsqParamMap[field]
            value = values[n][0]
            d[key] = value
        
        newtick = copy(tick)
        self.onTick(newtick)
    
    #----------------------------------------------------------------------
    def wConnect(self, event):
        """利用事件处理线程去异步连接Wind接口"""
        result = self.w.start()
        
        log = VtLogData()
        log.gatewayName = self.gatewayName        
        
        if not result.ErrorCode:
            log.logContent = u'Wind接口连接成功'
        else:
            log.logContent = u'Wind接口连接失败，错误代码%d' %result.ErrorCode
        self.onLog(log) 