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
from vnpy.trader.app.ctaStrategy.ctaBase import EVENT_CTA_LOG, EVENT_CTA_STRATEGY

reqAddress = 'tcp://localhost:6688'
subAddress = 'tcp://localhost:8866'    

ee = EventEngine2()
me = MainEngineProxy(ee)
me.init(reqAddress, subAddress)

#----------------------------------------------------------------------
def printLog(event):
    """打印日志"""
    log = event.dict_['data']
    print log.logTime, log.logContent
    
ee.register(EVENT_LOG, printLog)
    

# 载入Web密码
import json
import base64
import datetime

TODAY = str(datetime.datetime.now().date())

with open("WEB_setting.json") as f:
    setting = json.load(f)
    USERNAME = setting['username']
    PASSWORD = setting['password']
    TOKEN = base64.encodestring(TODAY+PASSWORD).replace('\n','')


# 创建Flask对象
from flask import Flask, send_file
from flask.ext.restful import Api, Resource, reqparse
from flask.ext.socketio import SocketIO
from flask_cors import *

app = Flask(__name__)
CORS(app, supports_credentials=True)
api = Api(app)
socketio = SocketIO(app)

# 创建资源
########################################################################
class Token(Resource):
    """登录验证"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('username')
        self.parser.add_argument('password')
        super(Token, self).__init__()
    
    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        args = self.parser.parse_args()
        username = args['username']
        password = args['password']
        
        if username == USERNAME and password == PASSWORD:
            return {'result_code':'success','data':TOKEN}
        else:
            return {'result_code':'error','message':'wrong username or password'}


########################################################################
class Gateway(Resource):
    """接口"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('gatewayName')
        self.parser.add_argument('token')
        
        super(Gateway, self).__init__()
    
    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        args = self.parser.parse_args()
        token = args['token']
        print token
        print TOKEN
        if token != TOKEN:
            print 'token error'
            return {'result_code':'error','message':'token error'}
        
        l = me.getAllGatewayDetails()
        return {'result_code':'success','data':l}
    
    #----------------------------------------------------------------------
    def post(self):
        """连接"""
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            print 'token error'
            return {'result_code':'error','message':'token error'}
                
        gatewayName = args['gatewayName']
        me.connect(gatewayName)
        return {'result_code':'success','data':''}


########################################################################
class Order(Resource):
    """委托"""

    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.getParser = reqparse.RequestParser()    
        self.getParser.add_argument('token')
        
        self.postParser = reqparse.RequestParser()
        self.postParser.add_argument('vtSymbol')
        self.postParser.add_argument('price')
        self.postParser.add_argument('volume')
        self.postParser.add_argument('priceType')
        self.postParser.add_argument('direction')
        self.postParser.add_argument('offset')
        self.postParser.add_argument('token')
        
        self.deleteParser = reqparse.RequestParser()
        self.deleteParser.add_argument('vtOrderID')        
        self.deleteParser.add_argument('token')
        
        super(Order, self).__init__()
    
    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        args = self.getParser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        data = me.getAllOrders()
        l = [o.__dict__ for o in data]
        return {'result_code':'success','data':l}
    
    #----------------------------------------------------------------------
    def post(self):
        """发单"""
        args = self.postParser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        print args
        vtSymbol = args['vtSymbol']        
        price = args['price']        
        volume = args['volume']        
        priceType = args['priceType']        
        direction = args['direction']        
        offset = args['offset']      
        
        contract = me.getContract(vtSymbol)
        if not contract:
            return {'result_code':'error','message':'contract error'}
        
        priceType_map = {'PRICETYPE_LIMITPRICE' : u'限价','PRICETYPE_MARKETPRICE' : u'市价','PRICETYPE_FAK' : u'FAK','PRICETYPE_FOK' : u'FOK'}
        direction_map = {'DIRECTION_LONG' : u'多','DIRECTION_SHORT' : u'空'}
        offset_map    = {'OFFSET_OPEN' : u'开仓',  'OFFSET_CLOSE' : u'平仓','OFFSET_CLOSETODAY' : u'平今','OFFSET_CLOSEYESTERDAY' : u'平昨'}
        
        req = VtOrderReq()
        req.symbol    = contract.symbol
        req.exchange  = contract.exchange
        req.price     = float(price)
        req.volume    = int(volume)
        req.priceType = priceType_map[ priceType ]
        req.direction = direction_map[ direction ]
        req.offset    = offset_map[ offset ]
        vtOrderID     = me.sendOrder(req, contract.gatewayName)
        return {'result_code':'success','data':vtOrderID}
    
    #----------------------------------------------------------------------
    def delete(self):
        """撤单"""
        args = self.deleteParser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        vtOrderID = args['vtOrderID']
        
        # 撤单某一委托
        if vtOrderID:
            order = me.getOrder(vtOrderID)
            if not order:
                return {'result_code':'error','message':'vtOrderID error'}
            
            self.cancel(order)
        # 全撤
        else:
            l = me.getAllWorkingOrders()
            
            for order in l:
                self.cancel(order)
            
        return {'result_code':'success','data':""}
    
    #----------------------------------------------------------------------
    def cancel(self, order):
        """撤单"""
        req = VtCancelOrderReq()
        req.orderID = order.orderID
        req.exchange = order.exchange
        req.symbol = order.symbol
        req.frontID = order.frontID
        req.sessionID = order.sessionID
        me.cancelOrder(req, order.gatewayName)                


########################################################################
class Trade(Resource):
    """成交"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('token')
        
        super(Trade, self).__init__()    

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        data = me.getAllTrades()
        l = [o.__dict__ for o in data]
        return {'result_code':'success','data':l}
    

########################################################################
class Account(Resource):
    """账户"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('token')
        
        super(Account, self).__init__()    

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        data = me.getAllAccounts()
        l = [o.__dict__ for o in data]
        return {'result_code':'success','data':l}        


########################################################################
class Position(Resource):
    """持仓"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('token')
        
        super(Position, self).__init__()    
    
    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        data = me.getAllPositions()
        print 'position',data
        l = [o.__dict__ for o in data]
        return {'result_code':'success','data':l}


########################################################################
class Contract(Resource):
    """合约"""

    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('token')
        
        super(Contract, self).__init__()    
    

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        data = me.getAllContracts()
        print 'Contract',data
        l = [o.__dict__ for o in data]
        return {'result_code':'success','data':l}        


########################################################################
class Log(Resource):
    """日志"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('token')
        
        super(Log, self).__init__()    

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        data = me.getLog()
        l = [o.__dict__ for o in data]
        return {'result_code':'success','data':l}   


########################################################################
class Error(Resource):
    """错误"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('token')
        
        super(Error, self).__init__()    

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        data = me.getError()
        l = [o.__dict__ for o in data]
        return {'result_code':'success','data':l}


########################################################################
class Tick(Resource):
    """行情"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('vtSymbol')
        self.parser.add_argument('token')
        super(Tick, self).__init__()    

    #----------------------------------------------------------------------
    def post(self):
        """订阅"""
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}

        vtSymbol = args['vtSymbol']

        contract = me.getContract(vtSymbol)
        if not contract:
            return {'result_code':'error','message':'contract error'}

        req = VtSubscribeReq()
        req.symbol = contract.symbol
        req.exchange = contract.exchange
        req.vtSymbol = contract.vtSymbol
        
        me.subscribe(req, contract.gatewayName)
        return {'result_code':'success','data':''}
    

########################################################################
class CtaStrategyInit(Resource):
    """初始化策略"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('name')
        self.parser.add_argument('token')
        super(CtaStrategyInit, self).__init__()    

    #----------------------------------------------------------------------
    def post(self):
        """订阅"""
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        name = args['name']
        
        engine = me.getApp('CtaStrategy')
        if not name:
            engine.initAll()
        else:
            engine.initStrategy(name)
        return {'result_code':'success','data':''}


########################################################################
class CtaStrategyStart(Resource):
    """启动策略"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('name')
        self.parser.add_argument('token')
        super(CtaStrategyStart, self).__init__()    

    #----------------------------------------------------------------------
    def post(self):
        """订阅"""
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        name = args['name']
        
        engine = me.getApp('CtaStrategy')
        if not name:
            engine.startAll()
        else:
            engine.startStrategy(name)
        return {'result_code':'success','data':''}


########################################################################
class CtaStrategyStop(Resource):
    """停止策略"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('name')
        self.parser.add_argument('token')
        super(CtaStrategyStop, self).__init__()    

    #----------------------------------------------------------------------
    def post(self):
        """订阅"""
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        name = args['name']
        
        engine = me.getApp('CtaStrategy')
        if not name:
            engine.stopAll()
        else:
            engine.stopStrategy(name)
        return {'result_code':'success','data':''}

########################################################################
class CtaStrategyName(Resource):
    """»ñÈ¡²ßÂÔÃû"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """³õÊ¼»¯"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('token')
        super(CtaStrategyName, self).__init__()        
    
    #----------------------------------------------------------------------
    def get(self):
        """»ñÈ¡²ßÂÔÃû""" 
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        engine = me.getApp('CtaStrategy')
        l = engine.getStrategyNames()
        return {'result_code':'success','data':l}

########################################################################
class CtaStrategyLoad(Resource):
    """加载策略"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('token')
        super(CtaStrategyLoad, self).__init__()        
    
    #----------------------------------------------------------------------
    def post(self):
        """订阅""" 
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        engine = me.getApp('CtaStrategy')
        engine.loadSetting()
        l = engine.getStrategyNames()
        return {'result_code':'success','data':l}


########################################################################
class CtaStrategyParam(Resource):
    """查询策略参数"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('name')
        self.parser.add_argument('token')
        super(CtaStrategyParam, self).__init__()    

    #----------------------------------------------------------------------
    def get(self):
        """订阅"""
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        name = args['name']
        
        engine = me.getApp('CtaStrategy')
        l = engine.getStrategyParam(name)
        return {'result_code':'success','data':l}


########################################################################
class CtaStrategyVar(Resource):
    """查询策略变量"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('name')
        self.parser.add_argument('token')
        super(CtaStrategyVar, self).__init__()    

    #----------------------------------------------------------------------
    def get(self):
        """订阅"""
        args = self.parser.parse_args()
        token = args['token']
        if token != TOKEN:
            return {'result_code':'error','message':'token error'}
        
        name = args['name']
        
        engine = me.getApp('CtaStrategy')
        l = engine.getStrategyVar(name)
        return {'result_code':'success','data':l}

      
########################################################################
@app.route('/')
def index_html():
    """首页"""
    return send_file('./templates/index.html')


# 注册资源
api.add_resource(Token, '/token')
api.add_resource(Gateway, '/gateway')
api.add_resource(Order, '/order')
api.add_resource(Trade, '/trades')
api.add_resource(Account, '/account')
api.add_resource(Position, '/position')
api.add_resource(Contract, '/contract')
api.add_resource(Log, '/log')
api.add_resource(Error, '/error')
api.add_resource(Tick, '/tick')

api.add_resource(CtaStrategyLoad, '/ctastrategy/load')
api.add_resource(CtaStrategyInit, '/ctastrategy/init')
api.add_resource(CtaStrategyStart, '/ctastrategy/start')
api.add_resource(CtaStrategyStop, '/ctastrategy/stop')
api.add_resource(CtaStrategyParam, '/ctastrategy/param')
api.add_resource(CtaStrategyVar, '/ctastrategy/var')
api.add_resource(CtaStrategyName, '/ctastrategy/name')


# SocketIO
#----------------------------------------------------------------------
def handleEvent(event):
    """处理事件"""
    eventType = event.type_

    eventData = event.dict_['data']

    if not isinstance(eventData, dict):
        eventData = eventData.__dict__

    if eventType == 'eTick.':
        del eventData['datetime']

    socketio.emit(eventType, eventData)


ee.register(EVENT_TICK, handleEvent)
ee.register(EVENT_ORDER, handleEvent)
ee.register(EVENT_TRADE, handleEvent)
ee.register(EVENT_ACCOUNT, handleEvent)
ee.register(EVENT_POSITION, handleEvent)
ee.register(EVENT_CONTRACT, handleEvent)
ee.register(EVENT_LOG, handleEvent)
ee.register(EVENT_ERROR, handleEvent)
ee.register(EVENT_CTA_LOG, handleEvent)
ee.register(EVENT_CTA_STRATEGY, handleEvent)
    

if __name__ == '__main__':
    socketio.run(app,debug=True,host='0.0.0.0',port=5000)
