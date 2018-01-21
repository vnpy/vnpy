# encoding: UTF-8

# 修改编码
import sys
reload(sys)
sys.setdefaultencoding('utf8')

# 创建主引擎代理对象
from vnpy.event import EventEngine2
from vnpy.trader.vtEvent import EVENT_LOG
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

app = Flask(__name__)
api = Api(app)

# 创建资源
########################################################################
class Gateways(Resource):
    """接口"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('name')
        super(Gateways, self).__init__()
    
    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        l = me.getAllGatewayDetails()
        return l
    
    #----------------------------------------------------------------------
    def post(self):
        """连接"""
        args = self.parser.parse_args()
        name = args['name']
        me.connect(name)


########################################################################
class Orders(Resource):
    """委托"""

    #----------------------------------------------------------------------
    def __init__(self):
        """初始化"""
        self.parser = reqparse.RequestParser()
        self.parser.add_argument('name')
        super(Gateways, self).__init__()
    
    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        data = me.getAllOrders()
        l = {o.__dict__ for o in data}
        return l
    
    #----------------------------------------------------------------------
    def post(self):
        """发单"""
        pass
    
    #----------------------------------------------------------------------
    def delete(self):
        """撤单"""
        pass


########################################################################
class Trades(Resource):
    """成交"""

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        data = me.getAllTrades()
        l = {o.__dict__ for o in data}
        return l
    

########################################################################
class Accounts(Resource):
    """账户"""

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        pass


########################################################################
class Positions(Resource):
    """持仓"""

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        pass


########################################################################
class Contracts(Resource):
    """合约"""

    #----------------------------------------------------------------------
    def get(self):
        """查询"""
        pass




# 注册资源
api.add_resource(Gateways, '/gateways')
api.add_resource(Orders, '/orders')
api.add_resource(Trades, '/trades')
api.add_resource(Accounts, '/accounts')
api.add_resource(Positions, '/positions')
api.add_resource(Contracts, '/contracts')



if __name__ == '__main__':
    app.run(debug=True)