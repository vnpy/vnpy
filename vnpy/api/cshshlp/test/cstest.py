# encoding: UTF-8

import sys
from time import sleep


from vncshshlp import *
import vncshshlp

branch_no = ''


#----------------------------------------------------------------------
def print_list(l):
    """"""
    for d in l:
        print d

#----------------------------------------------------------------------
def print_dict(d):
    """按照键值打印一个字典"""
    for key,value in d.items():
        print key + ':' + str(value)
        
        
#----------------------------------------------------------------------
def simple_log(func):
    """简单装饰器用于输出函数名"""
    def wrapper(*args, **kw):
        print '-' * 20
        print str(func.__name__)
        return func(*args, **kw)
    return wrapper


class TestHlp(CsHsHlp):
    #----------------------------------------------------------------------
    def __init__(self):
        """"""
        super(TestHlp, self).__init__()
        self.data = []
        self.password = ''
        self.password_type = ''
        self.client_id = ''
        self.sysnode_id = ''
        self.branch_no = ''
        self.op_branch_no = ''
        self.fund_account = ''
        self.option_fund_account = ''
        self.user_token = ''
        self.asset_prop = ''
        self.identity_type = ''
        self.op_entrust_way = ''
        self.request_num = ''
        self.op_station = ''
        self.order = {}  # {entrust:data}

    #----------------------------------------------------------------------
    @simple_log
    def onMsg(self, type_, data, reqNo, errorNo, errorInfo):
        """"""
        print 'type:', type_
        # print_list(data)
        print 'reqNo:', reqNo
        print 'errorNo:', errorNo
        print 'errorInfo:', errorInfo
        '''
        for i in data[0].keys():
            print "key=%s,value=%s"%(i,data[0][i])
        '''
        
        for dd in data:
            print dd        
        
        self.data = data

    
    def setNessaryParam(self):
        '''
        设置必要的参数
        '''
        self.beginParam()
        self.setValue("fund_account",self.fund_account)
        self.setValue("option_fund_account",self.option_fund_account)
        self.setValue("password",self.password)
        self.setValue("password_type",self.password_type)
        self.setValue("identity_type",self.identity_type)
        self.setValue("op_entrust_way",self.op_entrust_way)
        self.setValue("op_station",self.op_station)
        self.setValue('client_id',self.client_id)
        self.setValue('sysnode_id',self.sysnode_id)
        self.setValue('asset_prop',self.asset_prop)
        self.setValue('branch_no',self.branch_no)
        self.setValue('op_branch_n',self.op_branch_no)
        self.setValue('user_token',self.user_token)
        self.setValue('request_num',self.request_num)

    def init_api(self):
        '''
        初始化端口
        '''
        i = self.loadConfig("Hsconfig.ini")
        if i:
            print u'加载配置失败：', i
            return i            
        print u'加载配置成功'
        
        # 初始化
        i = self.init()
        if i:
            print u'初始化失败：', i
            return i
        print u'初始化成功'

        # 连接服务器
        i = self.connectServer()
        if i:
            print u'服务器连接失败：', i
            return i
        print u'服务器连接成功'

        return int(0)



#----------------------------------------------------------------------
def test():
    """测试用"""
    # 测试账户
    # account = {'id':'9008067077', 'psw':'123123'}
    account ={'id':'9899012708','psw':'111111'}
    # account ={'id':'9899012971','psw':'111111'}
    api = TestHlp()

    # 初始化端口
    i = api.init_api()
    if i:
        print u'初始化端口失败，请检查clog文件', i
        return
    # 登录
    print u'尝试登录'
    i = api.beginParam()
    api.setValue("identity_type", "2")
    api.setValue("password_type", "2")
    api.setValue("input_content", "1")
    api.setValue("op_entrust_way", "5")
    api.setValue("password", account['psw'])
    api.setValue("account_content", account['id'])
    api.setValue("fund_account", account['id'])
    api.setValue('option_fund_account', account['id'])
    api.setValue('op_station', '<yangxs><vnpy><test>')
    i = api.bizCallAndCommit(331100)
    print u'尝试登录返回', i
    sleep(3)
    #---------------------------------------------------------
    # 配置self的变量
    if(len(api.data)):
        api.fund_account = account['id']
        api.option_fund_account = account['id']
        api.password = account['psw']
        api.identity_type = '2'
        api.password_type = '2'
        api.client_id = api.data[0]['client_id']
        api.branch_no = api.data[0]['branch_no']
        api.op_branch_no = api.data[0]['branch_no']
        api.sysnode_id = api.data[0]['sysnode_id']
        api.asset_prop = api.data[0]['asset_prop']
        api.user_token = api.data[0]['user_token']
        api.op_entrust_way = '5'
        api.request_num = '500'
        api.op_station = '<yangxs><vnpy><test>'
    else:
        print 'error in set the value'

    
    #------------------------------------------
    # 订阅  620001  成交回报  33011
    # 订阅  620001  委托回写  33012
    # api.setNessaryParam()
    print u'订阅 33011'
    api.beginParam()
    acc_info = '~' .join([api.branch_no, api.fund_account])
    api.setValue('issue_type', "33011")
    api.setValue('acc_info', acc_info)
    i = api.subscribeData(620001)
    print i
    sleep(1)


    print u'订阅 33012'
    api.beginParam()
    acc_info = '~' .join([api.branch_no, api.fund_account])
    api.setValue('issue_type', "33012")
    api.setValue('acc_info', acc_info)
    i = api.subscribeData(620001)
    print i
    sleep(1)

    
    print u'配置参数，进行下单'
    # 配置
    api.setNessaryParam()
    # 下单参数 338011
    api.setValue('exchange_type','1')
    api.setValue('option_code','10000844')
    api.setValue('entrust_amount','1')
    api.setValue('opt_entrust_price','0.08')
    api.setValue('entrust_bs','1')
    api.setValue("entrust_oc", "O")
    api.setValue("batch_no", "0")
    api.setValue('entrust_prop', '0')
    api.setValue('covered_flag', '')
    i = api.bizCallAndCommit(338011)
    print u'尝试下单返回', i
    sleep(3)
    
    
    print u'查询持仓'
     # 查询持仓
    # api.beginParam()
    api.setNessaryParam()
    i = api.bizCallAndCommit(338023)
    sleep(3)
    print u'查询持仓返回',i
    if(len(api.data)):
        for dd in api.data:
            print "-----------------------"
            for i in dd.keys():
                print "key=%s,value=%s"%(i,api.data[0][i])

    # --------------------------------------------------------------------------   
    # 测试撤单 338012,先下单，间隔后撤单
    api.setNessaryParam()
    api.setValue('exchange_type','1')
    api.setValue('option_code','10000844')
    api.setValue('entrust_amount','1')
    api.setValue('opt_entrust_price','0.09')
    api.setValue('entrust_bs','1')
    api.setValue("entrust_oc", "O")
    api.setValue("batch_no", "0")
    api.setValue('entrust_prop', '0')
    api.setValue('covered_flag', '')
    i = api.bizCallAndCommit(338011)
    print u'尝试下单返回', i
    sleep(3)
    # print api.data

    if(len(api.data)):
        # get batch no
        for tt in api.data:
            e_no = tt['entrust_no']
            api.order[e_no] = tt
        
    print api.order
    api.setNessaryParam()
    api.setValue('exchange_type','1')
    for kk in api.order.keys():
        api.setValue('entrust_no', kk)
        i = api.bizCallAndCommit(338012)
        print u'尝试撤单', kk
        sleep(1)
        #pop or del
    print api.data

    
    #-----------------------------------
    # 期权委托查询   1.查询指定委托   2.查询所有可撤订单
    api.setNessaryParam()
    
    for kk in api.order.keys():

        api.setValue('locate_entrust_no', kk)
        i = api.bizCallAndCommit(338020)
        print u'查询指定订单', kk
        sleep(1)
    print api.data
    
    api.setNessaryParam()
    api.setValue('query_kind', '1')
    i = api.bizCallAndCommit(338020)
    sleep(1)
    print api.data
    

    
    raw_input()

if __name__ == '__main__':
    test()

