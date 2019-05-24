# encoding: UTF-8

import sys,os

vnpy_root = os.path.abspath(os.path.join(os.path.dirname(__file__),'..','..','..','..','..'))
if vnpy_root not in sys.path:
    print(u'append {}'.format(vnpy_root))
    sys.path.append(vnpy_root)


from time import sleep

#from qtpy import QtGui

from vnpy.api.ctp_se.vnctptd import *
from threading import Thread


# 长江
md_addr = "tcp://124.74.10.62:47213"
td_addr = "tcp://124.74.10.62:43205"
# 银河联通:
#md_addr = "tcp://114.255.82.175:31213"
#td_addr = "tcp://114.255.82.175:31205"
# 银河电信
#md_addr = "tcp://106.39.36.72:31213"
#td_addr = "tcp://106.39.36.72:31205"

user_id = "xxx"
user_pass = "xx@123"
app_id = "clientxxx_2.0.0"
auth_code = "xxxxx"
broker_id = '4300'

#----------------------------------------------------------------------
def print_dict(d):
    """按照键值打印一个字典"""
    for key,value in d.items():
        print (key + ':' + str(value))
        
        
#----------------------------------------------------------------------
def simple_log(func):
    """简单装饰器用于输出函数名"""
    def wrapper(*args, **kw):
        print ("")
        print (str(func.__name__))
        return func(*args, **kw)
    return wrapper


########################################################################
class TestTdApi(TdApi):
    """测试用实例"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(TestTdApi, self).__init__()
        self.req_id = 1
    #----------------------------------------------------------------------
    @simple_log    
    def onFrontConnected(self):
        """服务器连接"""
        print(u'tdtest：服务器连接成功')
        self.reqAuth()

    def reqAuth(self):
        print('td test:start auth')
        authReq = {}
        authReq['UserID'] = user_id
        authReq['BrokerID'] = broker_id
        authReq['AppID'] = app_id
        authReq['AuthCode'] = auth_code
        self.req_id = self.req_id + 1
        i = self.reqAuthenticate(authReq, self.req_id)

    #----------------------------------------------------------------------
    @simple_log    
    def onFrontDisconnected(self, n):
        """服务器断开"""
        print(u'服务器断开')
        
    #----------------------------------------------------------------------
    @simple_log    
    def onHeartBeatWarning(self, n):
        """心跳报警"""
        print (n)
    
    #----------------------------------------------------------------------
    @simple_log    
    def onRspError(self, error, n, last):
        """错误"""
        print_dict(error)
    
    #----------------------------------------------------------------------
    @simple_log  
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        print_dict(data)
        print_dict(error)

        if error.get('ErrorID',0) > 0:
            print('u登录失败')
            return
        print('tdtest:onRespUserLogin success')
        self.brokerID = data['BrokerID']
        self.userID = data['UserID']
        self.frontID = data['FrontID']
        self.sessionID = data['SessionID']

    def onRspAuthenticate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not error['ErrorID']:
            self.authStatus = True
            print("交易授权验证成功")
            # 登陆，测试通过
            print('start login')
            loginReq = {}  # 创建一个空字典
            loginReq['UserID'] = user_id  # 参数作为字典键值的方式传入
            loginReq['Password'] = user_pass  # 键名和C++中的结构体成员名对应
            loginReq['BrokerID'] = broker_id
            #loginReq['UserProductInfo'] = 'client_huafu_2.0.0'
            self.req_id = self.req_id + 1  # 请求数必须保持唯一性
            i = self.reqUserLogin(loginReq, self.req_id)
        else:
            print("交易授权验证失败:{}".format(error))
            print_dict(data)

    #----------------------------------------------------------------------
    @simple_log    
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        print_dict(data)
        print_dict(error)
        
    #----------------------------------------------------------------------
    @simple_log
    def onRspQrySettlementInfo(self, data, error, n, last):
        """查询结算信息回报"""
        print_dict(data)
        print_dict(error)

    #----------------------------------------------------------------------
    @simple_log
    def onRspSettlementInfoConfirm(self, data, error, n, last):
        """确认结算信息回报"""
        print_dict(data)
        print_dict(error)
        
    #----------------------------------------------------------------------
    @simple_log
    def onRspQryInstrument(self, data, error, n, last):
        """查询合约回报"""
        print_dict(data)
        print_dict(error)
        print (n)
        print (last)
        
        
#----------------------------------------------------------------------
def main():
    """主测试函数，出现堵塞时可以考虑使用sleep"""

    try:
        # 创建Qt应用对象，用于事件循环
        #app = QtGui.QApplication(sys.argv)

        # 创建API对象，测试通过
        api = TestTdApi()

        # 在C++环境中创建MdApi对象，传入参数是希望用来保存.con文件的地址，测试通过

        api.createFtdcTraderApi('')

        # 设置数据流重传方式，测试通过
        api.subscribePrivateTopic(1)
        api.subscribePublicTopic(1)

        # 注册前置机地址，测试通过

        # 长江
        #td_addr = "tcp://124.74.10.62:43205"
        # 银河生产(主席)
        td_addr = "tcp://101.230.198.41:56205"   # no connect
        #td_addr = "tcp://180.166.103.21:55205"   # no connect
        #td_addr = "tcp://180.166.103.21:57205"   # no connect
        #td_addr = "tcp://58.247.171.151:57205"    # no connect
        #td_addr = "tcp://58.247.171.151:55205"    # no connect
        #td_addr = "tcp://27.115.78.41:56205"    # no connect
        # 银河生产(二席）
        #td_addr = "tcp://180.166.103.22:42206"  # no connect
        #td_addr = "tcp://101.230.198.42:42206"

        #api.registerFront("tcp://124.89.33.126:51217")

        print('tdtest:register front:{}'.format(td_addr))
        api.registerFront(td_addr)
        # 初始化api，连接前置机，测试通过
        print('tdtest:init')
        api.init()
        sleep(0.5)

        print('tdtest:waiting for Connect and Authenticate')
        count = 1
        while(1):
            if hasattr(api, 'brokerID'):
                break
            sleep(0.5)
            count +=1

            if count > 10:
                print('tdtest: time expired, not pass Authenticate')
                exit(0)

        ## 查询合约, 测试通过
        print(u'tdtest:查询合约')
        api.req_id = api.req_id + 1
        i = api.reqQryInstrument({}, api.req_id)

        ## 查询结算, 测试通过
        print(u'tdtest:查询结算')
        req = {}
        req['BrokerID'] = api.brokerID
        req['InvestorID'] = api.userID
        api.req_id = api.req_id + 1
        i = api.reqQrySettlementInfo(req, api.req_id)
        sleep(0.5)

        ## 确认结算, 测试通过
        req = {}
        print(u'tdtest:确认结算')
        req['BrokerID'] = api.brokerID
        req['InvestorID'] = api.userID
        api.req_id = api.req_id + 1
        i = api.reqSettlementInfoConfirm(req, api.req_id)
        sleep(0.5)


        # 连续运行
        #app.exec_()
    except Exception as ex:
        print(str(ex))
    
    
if __name__ == '__main__':
    # 主程序
    thread = Thread(target=main, args=())
    thread.start()
