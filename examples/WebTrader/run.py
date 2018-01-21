# encoding: UTF-8

# 修改编码
import sys
reload(sys)
sys.setdefaultencoding('utf8')

# 创建主引擎代理对象
from vnpy.event import EventEngine2
from vnpy.trader.vtEvent import (EVENT_TICK, EVENT_ORDER, EVENT_TRADE,
                                 EVENT_ACCOUNT, EVENT_POSITION, EVENT_LOG,
                                 EVENT_ERROR, EVENT_CONTRACT)
from vnpy.trader.vtObject import VtSubscribeReq, VtOrderReq, VtCancelOrderReq
from vnpy.trader.app.rpcService.rsClient import MainEngineProxy

reqAddress = 'tcp://localhost:2014'
subAddress = 'tcp://localhost:0602'    

ee = EventEngine2()
me = MainEngineProxy(ee)
me.init(reqAddress, subAddress)

#----------------------------------------------------------------------
def printLog(event):
    """打印日志"""
    log = event.dict_['data']
    print log.logTime, log.logContent
    
ee.register(EVENT_LOG, printLog)
    

# 创建Flask对象
from flask import Flask
from flask.ext.restful import Api, Resource, reqparse
from flask.ext.socketio import SocketIO

app = Flask(__name__)
api = Api(app)
socketio = SocketIO(app)


# 创建资源
########################################################################
class Gateway(Resource):
    """接口"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('gatewayName')
        super(Gateway, self).__init__()
    
    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        l = me.getAllGatewayDetails()
        return l
    
    #----------------------------------------------------------------------
    def post(self):
        """连接"""
        args = self.parser.parse_args()
        gatewayName = args['gatewayName']
        me.connect(gatewayName)


########################################################################
class Order(Resource):
    """委托"""

    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.postParser = reqparse.RequestParser()
        self.postParser.add_argument('vtSymbol')
        self.postParser.add_argument('price')
        self.postParser.add_argument('volume')
        self.postParser.add_argument('priceType')
        self.postParser.add_argument('direction')
        self.postParser.add_argument('offset')
        
        self.deleteParser = reqparse.RequestParser()
        self.deletaParser.add_argument('vtOrderID')        
        
        super(Order, self).__init__()
    
    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        data = me.getAllOrders()
        l = {o.__dict__ for o in data}
        return l
    
    #----------------------------------------------------------------------
    def post(self):
        """发单"""
        args = self.deleteParser.parse_args()
        vtSymbol = args['vtSymbol']        
        price = args['price']        
        volume = args['volume']        
        priceType = args['priceType']        
        direction = args['direction']        
        offset = args['offset']      
        
        contract = me.getContract(vtSymbol)
        if not contract:
            return ''
        
        req = VtOrderReq()
        req.symbol = contract.symbol
        req.exchange = contract.exchange
        req.price = float(price)
        req.volume = int(symbol)
        req.priceType = priceType
        req.direction = direction
        req.offset = offset
        vtOrderID = me.sendOrder(req, contract.gatewayName)
        return vtOrderID
    
    #----------------------------------------------------------------------
    def delete(self):
        """撤单"""
        args = self.deleteParser.parse_args()
        vtOrderID = args['vtOrderID']
        
        order = me.getOrder(vtOrderID)
        if not order:
            return False
        
        req = VtCancelOrderReq()
        req.orderID = order.orderID
        req.exchange = order.exchange
        req.symbol = order.symbol
        me.cancelOrder(req, order.gatewayName)


########################################################################
class Trade(Resource):
    """成交"""

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        data = me.getAllTrades()
        l = {o.__dict__ for o in data}
        return l
    

########################################################################
class Account(Resource):
    """账户"""

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        data = me.getAllAccounts()
        l = {o.__dict__ for o in data}
        return l        


########################################################################
class Position(Resource):
    """持仓"""

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        data = me.getAllPositions()
        l = {o.__dict__ for o in data}
        return l


########################################################################
class Contract(Resource):
    """合约"""

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        data = me.getAllContracts()
        l = {o.__dict__ for o in data}
        return l        


########################################################################
class Log(Resource):
    """日志"""

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        data = me.getLog()
        l = {o.__dict__ for o in data}
        return l   


########################################################################
class Error(Resource):
    """错误"""

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        data = me.getError()
        l = {o.__dict__ for o in data}
        return l


########################################################################
class Tick(Resource):
    """行情"""
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('vtSymbol')
        super(Tick, self).__init__()    

    #----------------------------------------------------------------------
    def post(self):
        """订阅"""
        args = self.parser.parse_args()
        vtSymbol = args['vtSymbol']
        
        contract = me.getContract(vtSymbol)
        if not contract:
            return False
        
        req = VtSubscribeReq()
        req.symbol = contract.symbol
        req.exchange = contract.exchange
        req.vtSymbol = contract.vtSymbol
        me.subscribe(req, contract.gatewayName)
        return True
    

# 注册资源
api.add_resource(Gateway, '/gateway')
api.add_resource(Order, '/order')
api.add_resource(Trade, '/trades')
api.add_resource(Account, '/account')
api.add_resource(Position, '/position')
api.add_resource(Contract, '/contract')
api.add_resource(Log, '/log')
api.add_resource(Error, '/error')
api.add_resource(Tick, '/tick')


# SocketIO
#----------------------------------------------------------------------
def handleEvent(event):
    """处理事件"""
    eventType = event.type_
    eventData = event.dict_['data'].__dict__
    #socketio.emit(eventType, eventData, broadcast=True)
    socketio.emit('test', eventData, broadcast=True)
    
    print eventData


ee.register(EVENT_TICK, handleEvent)
ee.register(EVENT_ORDER, handleEvent)
ee.register(EVENT_TRADE, handleEvent)
ee.register(EVENT_ACCOUNT, handleEvent)
ee.register(EVENT_POSITION, handleEvent)
ee.register(EVENT_CONTRACT, handleEvent)
ee.register(EVENT_LOG, handleEvent)
ee.register(EVENT_ERROR, handleEvent)
    



if __name__ == '__main__':
    app.run(debug=True)
    #socketio.run(app)