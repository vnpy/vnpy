# encoding: UTF-8

from collections import defaultdict

from vnpy.event import Event
from vnpy.rpc import RpcClient, RpcServer
from vnpy.trader.vtEvent import (EVENT_POSITION, EVENT_TRADE, 
                                 EVENT_TIMER, EVENT_ORDER)
from vnpy.trader.vtConstant import (DIRECTION_LONG, DIRECTION_SHORT,
                                    OFFSET_OPEN, OFFSET_CLOSE, PRICETYPE_LIMITPRICE,
                                    OFFSET_CLOSEYESTERDAY, OFFSET_CLOSETODAY,
                                    STATUS_REJECTED)
from vnpy.trader.vtObject import VtOrderReq, VtCancelOrderReq, VtLogData, VtSubscribeReq


EVENT_TC_LOG = 'eTcLog'


########################################################################
class TcEngine(object):
    """交易复制引擎"""
    MODE_PROVIDER = 1
    MODE_SUBSCRIBER = 2
    
    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        self.mode = None                    # Subscriber/Provider
        self.posDict = defaultdict(int)     # vtPositionName:int
        self.targetDict = defaultdict(int)  # vtPositionName:int
        self.copyRatio = 1
        self.interval = 1
        self.subscribeSet = set()
        
        self.count = 0
        self.server = None                  # RPC Server
        self.client = None                  # RPC Client
        
        self.registerEvent()
    
    #----------------------------------------------------------------------
    def startProvider(self, repAddress, pubAddress, interval):
        """"""
        self.mode = self.MODE_PROVIDER
        self.interval = interval
        
        self.server = RpcServer(repAddress, pubAddress)
        self.server.usePickle()
        self.server.register(self.getPos)
        self.server.start()
        
        self.writeLog(u'启动发布者模式')
    
    #----------------------------------------------------------------------
    def startSubscriber(self, reqAddress, subAddress, copyRatio):
        """"""
        self.mode = self.MODE_SUBSCRIBER
        self.copyRatio = copyRatio
        
        self.client = TcClient(self, reqAddress, subAddress)
        self.client.usePickle()
        self.client.subscribeTopic('')
        self.client.start()
        
        self.writeLog(u'启动订阅者模式，运行时请不要执行其他交易操作')
        
        self.initTarget()
    
    #----------------------------------------------------------------------
    def stop(self):
        """"""
        if self.client:
            self.client.stop()
            self.writeLog(u'订阅者模式已停止')
        
        if self.server:
            self.server.stop()
            self.writeLog(u'发布者模式已停止')
        
        self.mode = None
        
    #----------------------------------------------------------------------
    def registerEvent(self):
        """"""
        self.eventEngine.register(EVENT_POSITION, self.processPositionEvent)
        self.eventEngine.register(EVENT_TRADE, self.processTradeEvent)
        self.eventEngine.register(EVENT_TIMER, self.processTimerEvent)
        self.eventEngine.register(EVENT_ORDER, self.processOrderEvent)
    
    #----------------------------------------------------------------------
    def checkAndTrade(self, vtSymbol):
        """"""
        if self.checkNoWorkingOrder(vtSymbol):
            self.newOrder(vtSymbol)
        else:
            self.cancelOrder(vtSymbol)        
    
    #----------------------------------------------------------------------
    def processTimerEvent(self, event):
        """"""
        if self.mode != self.MODE_PROVIDER:
            return
            
        self.count += 1
        if self.count < self.interval:
            return
        self.count = 0
        
        for vtPositionName in self.posDict.keys():
            self.publishPos(vtPositionName)
        
    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """"""
        trade = event.dict_['data']
        
        vtPositionName = '.'.join([trade.vtSymbol, trade.direction])
        
        if trade.offset == OFFSET_OPEN:
            self.posDict[vtPositionName] += trade.volume
        else:
            self.posDict[vtPositionName] -= trade.volume
        
        if self.mode == self.MODE_PROVIDER:
            self.publishPos(vtPositionName)
    
    #----------------------------------------------------------------------
    def processPositionEvent(self, event):
        """"""
        position = event.dict_['data']
        self.posDict[position.vtPositionName] = position.position        
    
    #----------------------------------------------------------------------
    def processOrderEvent(self, event):
        """"""
        order = event.dict_['data']
        if order.status == STATUS_REJECTED:
            self.writeLog(u'监控到委托拒单，停止运行')
            self.stop()
    
    #----------------------------------------------------------------------
    def publishPos(self, vtPositionName):
        """"""
        l = vtPositionName.split('.')
        direction = l[-1]
        vtSymbol = vtPositionName.replace('.' + direction, '')        
        
        data = {
            'vtSymbol': vtSymbol,
            'vtPositionName': vtPositionName,
            'pos': self.posDict[vtPositionName]
        }
        self.server.publish('', data)
    
    #----------------------------------------------------------------------
    def updatePos(self, data):
        """"""
        vtSymbol = data['vtSymbol']
        if vtSymbol not in self.subscribeSet:
            contract = self.mainEngine.getContract(vtSymbol)
            
            req = VtSubscribeReq()
            req.symbol = contract.symbol
            req.exchange = contract.exchange
            self.mainEngine.subscribe(req, contract.gatewayName)
        
        vtPositionName = data['vtPositionName']
        target = int(data['pos'] * self.copyRatio)
        self.targetDict[vtPositionName] = target
        
        self.checkAndTrade(vtSymbol)
    
    #----------------------------------------------------------------------
    def newOrder(self, vtSymbol):
        """"""
        for vtPositionName in self.targetDict.keys():
            if vtSymbol not in vtPositionName:
                continue
            
            pos = self.posDict[vtPositionName]
            target = self.targetDict[vtPositionName]            
            if pos == target:
                continue
            
            contract = self.mainEngine.getContract(vtSymbol)
            tick = self.mainEngine.getTick(vtSymbol)
            if not tick:
                return
            
            req = VtOrderReq()
            req.symbol = contract.symbol
            req.exchange = contract.exchange
            req.priceType = PRICETYPE_LIMITPRICE            
            req.volume = abs(target - pos)
            
            # Open position
            if target > pos:
                req.offset = OFFSET_OPEN
                
                if DIRECTION_LONG in vtPositionName:
                    req.direction = DIRECTION_LONG
                    if tick.upperLimit:
                        req.price = tick.upperLimit
                    else:
                        req.price = tick.askPrice1
                elif DIRECTION_SHORT in vtPositionName:
                    req.direction = DIRECTION_SHORT
                    if tick.lowerLimit:
                        req.price = tick.lowerLimit
                    else:
                        req.price = tick.bidPrice1
                
                self.mainEngine.sendOrder(req, contract.gatewayName)
            
            # Close position
            elif target < pos:
                req.offset = OFFSET_CLOSE
                
                if DIRECTION_LONG in vtPositionName:
                    req.direction = DIRECTION_SHORT
                    if tick.upperLimit:
                        req.price = tick.upperLimit
                    else:
                        req.price = tick.askPrice1
                
                elif DIRECTION_SHORT in vtPositionName:
                    req.direction = DIRECTION_LONG
                    if tick.lowerLimit:
                        req.price = tick.lowerLimit
                    else:
                        req.price = tick.bidPrice1
                    
                # Use auto-convert for solving today/yesterday position problem
                reqList = self.mainEngine.convertOrderReq(req)
                for convertedReq in reqList:
                    self.mainEngine.sendOrder(convertedReq, contract.gatewayName)
            
            # Write log
            msg = u'发出%s委托 %s%s %s@%s' %(vtSymbol, req.direction, req.offset,
                                            req.price, req.volume)
            self.writeLog(msg)

    #----------------------------------------------------------------------
    def cancelOrder(self, vtSymbol):
        """
        Cancel all orders of a certain vtSymbol
        """
        l = self.mainEngine.getAllWorkingOrders()
        for order in l:
            if order.vtSymbol == vtSymbol:
                req = VtCancelOrderReq()
                req.orderID = order.orderID
                req.frontID = order.frontID
                req.sessionID = order.sessionID
                req.symbol = order.symbol
                req.exchange = order.exchange
                self.mainEngine.cancelOrder(req, order.gatewayName)
        
        self.writeLog(u'撤销%s全部活动中委托' %vtSymbol)
    
    #----------------------------------------------------------------------
    def checkNoWorkingOrder(self, vtSymbol):
        """
        Check if there is still any working orders of a certain vtSymbol
        """
        l = self.mainEngine.getAllWorkingOrders()
        for order in l:
            if order.vtSymbol == vtSymbol:
                return False
        
        return True

    #----------------------------------------------------------------------
    def writeLog(self, msg):
        """"""
        log = VtLogData()
        log.logContent = msg
        
        event = Event(EVENT_TC_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def getPos(self):
        """
        Get currenct position data of provider
        """
        return dict(self.posDict)
    
    #----------------------------------------------------------------------
    def initTarget(self):
        """
        Init target data of subscriber based on position data from provider
        """
        d = self.client.getPos()
        for vtPositionName, pos in d.items():
            l = vtPositionName.split('.')
            direction = l[-1]
            vtSymbol = vtPositionName.replace('.' + direction, '')
            
            data = {
                'vtPositionName': vtPositionName,
                'vtSymbol': vtSymbol,
                'pos': pos
            }
            self.updatePos(data)
        
        self.writeLog(u'目标仓位初始化完成')


########################################################################
class TcClient(RpcClient):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, engine, reqAddress, subAddress):
        """Constructor"""
        super(TcClient, self).__init__(reqAddress, subAddress)
        
        self.engine = engine
    
    #----------------------------------------------------------------------
    def callback(self, topic, data):
        """"""
        self.engine.updatePos(data)
    
    