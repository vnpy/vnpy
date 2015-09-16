# encoding: UTF-8

"""
该文件中包含的是交易平台的底层接口相关的部分，
主要对API进行了一定程度的简化封装，方便开发。
"""

import os

from vnctpmd import MdApi
from vnctptd import TdApi
from eventEngine import *
from ctp_data_type import defineDict

#----------------------------------------------------------------------
def print_dict(d):
    """打印API收到的字典，该函数主要用于开发时的debug"""
    print '-'*60
    l = d.keys()
    l.sort()
    for key in l:
        print key, ':', d[key]
    

########################################################################
class DemoMdApi(MdApi):
    """
    Demo中的行情API封装
    封装后所有数据自动推送到事件驱动引擎中，由其负责推送到各个监听该事件的回调函数上
    
    对用户暴露的主动函数包括:
    登陆 login
    订阅合约 subscribe
    """

    #----------------------------------------------------------------------
    def __init__(self, eventEngine):
        """
        API对象的初始化函数
        """
        print u'DemoApi.py DemoMdApi.__init__() begin'     

        super(DemoMdApi, self).__init__()
        print u'DemoApi.py DemoMdApi.__init__() super success'
        
        # 事件引擎，所有数据都推送到其中，再由事件引擎进行分发
        self.__eventEngine = eventEngine  
        
        # 请求编号，由api负责管理
        self.__reqid = 0
        
        # 以下变量用于实现连接和重连后的自动登陆
        self.__userid = ''
        self.__password = ''
        self.__brokerid = ''
        
        # 以下集合用于重连后自动订阅之前已订阅的合约，使用集合为了防止重复
        self.__setSubscribed = set()   
        # 初始化.con文件的保存目录为\mdconnection，注意这个目录必须已存在，否则会报错
        self.createFtdcMdApi(os.getcwd() + '\\mdconnection\\')  
        print u'DemoApi.py DemoMdApi.__init__() createFtdcMdApi success'
             
        print u'DemoApi.py DemoMdApi.__init__() end'       
        
    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
        print u'DemoApi.py DemoMdApi.onFrontConnected() begin.'
        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = u'行情服务器连接成功'
        self.__eventEngine.put(event)
        
        # 如果用户已经填入了用户名等等，则自动尝试连接
        if self.__userid:
            req = {}
            req['UserID'] = self.__userid
            req['Password'] = self.__password
            req['BrokerID'] = self.__brokerid
            self.__reqid = self.__reqid + 1
            self.reqUserLogin(req, self.__reqid)

        print u'DemoApi.py DemoMdApi.onFrontConnected() end.'
            
    #----------------------------------------------------------------------  
    def onFrontDisconnected(self, n):
        """服务器断开"""
        print u'DemoApi.py DemoMdApi.onFrontDisconnected() begin.'
        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = u'行情服务器连接断开'
        self.__eventEngine.put(event)
        print u'DemoApi.py DemoMdApi.onFrontDisconnected() end.'
        
    #---------------------------------------------------------------------- 
    def onHeartBeatWarning(self, n):
        """心跳报警"""
        # 因为API的心跳报警比较常被触发，且与API工作关系不大，因此选择忽略
        print u'DemoApi.py DemoMdApi.onHeartBeatWarning()'
        pass
    
    #----------------------------------------------------------------------   
    def onRspError(self, error, n, last):
        """错误回报"""
        print u'DemoApi.py DemoMdApi.onRspError() begin'
        event = Event(type_=EVENT_LOG)
        log = u'行情错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        print u'DemoApi.py DemoMdApi.onRspError() end'
    
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""

        print u'DemoApi.py DemoMdApi.onRspUserLogin() begin'

        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'行情服务器登陆成功'
        else:
            log = u'登陆回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log

        self.__eventEngine.put(event)
        
        ## 重连后自动订阅之前已经订阅过的合约
        #if self.__setSubscribed:
            #for instrument in self.__setSubscribed:
                #self.subscribe(instrument[0], instrument[1])

        onRspUserLogin
        
        print u'DemoApi.py DemoMdApi.onRspUserLogin() end'     
           
    #---------------------------------------------------------------------- 
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""

        print u'DemoApi.py DemoMdApi.onRspUserLogout() begin'

        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'行情服务器登出成功'
        else:
            log = u'登出回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log

        self.__eventEngine.put(event)

        print u'DemoApi.py DemoMdApi.onRspUserLogout() end'
        
    #----------------------------------------------------------------------  
    def onRspSubMarketData(self, data, error, n, last):
        """订阅合约回报"""
        # 通常不在乎订阅错误，选择忽略
        print u'DemoApi.py DemoMdApi.onRspSubMarketData()'
        pass
        
    #----------------------------------------------------------------------  
    def onRspUnSubMarketData(self, data, error, n, last):
        """退订合约回报"""

        onRspUnSubMarketData

        # 同上
        pass  
        
    #----------------------------------------------------------------------  
    def onRtnDepthMarketData(self, data):
        """行情推送"""
        # 行情推送收到后，同时触发常规行情事件，以及特定合约行情事件，用于满足不同类型的监听
        print u'DemoApi.py DemoMdApi.onRtnDepthMarketData() begin'

        # 常规行情事件
        event1 = Event(type_=EVENT_MARKETDATA)
        event1.dict_['data'] = data
        self.__eventEngine.put(event1)
        
        # 特定合约行情事件
        event2 = Event(type_=(EVENT_MARKETDATA_CONTRACT+data['InstrumentID']))
        event2.dict_['data'] = data
        self.__eventEngine.put(event2)
        
        print u'DemoApi.py DemoMdApi.onRtnDepthMarketData() end'

    #---------------------------------------------------------------------- 
    def onRspSubForQuoteRsp(self, data, error, n, last):
        """订阅期权询价"""
        pass
        
    #----------------------------------------------------------------------
    def onRspUnSubForQuoteRsp(self, data, error, n, last):
        """退订期权询价"""
        print u'DemoApi.py DemoMdApi.onRspUnSubForQuoteRsp()'
        pass 
        
    #---------------------------------------------------------------------- 
    def onRtnForQuoteRsp(self, data):
        """期权询价推送"""
        print u'DemoApi.py DemoMdApi.onRtnForQuoteRsp()'
        pass        
        
    #----------------------------------------------------------------------
    def login(self, address, userid, password, brokerid):
        """连接服务器"""

        print u'DemoApi.py DemoMdApi.login() begin'

        self.__userid = userid
        self.__password = password
        self.__brokerid = brokerid
        
        # 注册服务器地址
        self.registerFront(address)
        print u'DemoApi.py DemoMdApi.login() registerFront success'
        
        # 初始化连接，成功会调用onFrontConnected
        self.init()
        print u'DemoApi.py DemoMdApi.login() init() success'

        print u'DemoApi.py DemoMdApi.login() end'   
             
    #----------------------------------------------------------------------
    def subscribe(self, instrumentid, exchangeid):
        """订阅合约"""
        self.subscribeMarketData(instrumentid)
        
        instrument = (instrumentid, exchangeid)
        self.__setSubscribed.add(instrument)


########################################################################
class DemoTdApi(TdApi):
    """
    Demo中的交易API封装
    主动函数包括：
    login 登陆
    getInstrument 查询合约信息
    getAccount 查询账号资金
    getInvestor 查询投资者
    getPosition 查询持仓
    sendOrder 发单
    cancelOrder 撤单
    """

    #----------------------------------------------------------------------
    def __init__(self, eventEngine):
        """API对象的初始化函数"""

        print u'DemoApi.py DemoTdApi.__init__() begin'

        super(DemoTdApi, self).__init__()

        print u'DemoApi.py DemoTdApi.__init__() call super() success'
        
        # 事件引擎，所有数据都推送到其中，再由事件引擎进行分发
        self.__eventEngine = eventEngine
        
        # 请求编号，由api负责管理
        self.__reqid = 0
        
        # 报单编号，由api负责管理
        self.__orderref = 0
        
        # 以下变量用于实现连接和重连后的自动登陆
        self.__userid = ''
        self.__password = ''
        self.__brokerid = ''   
        
        # 合约字典（保存合约查询数据）
        self.__dictInstrument = {}
        
        # 初始化.con文件的保存目录为\tdconnection
        self.createFtdcTraderApi(os.getcwd() + '\\tdconnection\\')    

        print u'DemoApi.py DemoTdApi.__init__() createFtdcTraderApi() success.'
        
        print u'DemoApi.py DemoTdApi.__init__() end.'

        
        
    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""

        print u'DemoApi.py DemoTdApi.onFrontConnected() begin.'

        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = u'交易服务器连接成功'
        self.__eventEngine.put(event)
        
        # 如果用户已经填入了用户名等等，则自动尝试连接
        if self.__userid:
            req = {}
            req['UserID'] = self.__userid
            req['Password'] = self.__password
            req['BrokerID'] = self.__brokerid
            self.__reqid = self.__reqid + 1
            self.reqUserLogin(req, self.__reqid)

        print u'DemoApi.py DemoTdApi.onFrontConnected() begin.'
    
    #----------------------------------------------------------------------
    def onFrontDisconnected(self, n):
        """服务器断开"""

        print u'DemoApi.py DemoTdApi.onFrontDisconnected() begin.'

        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = u'交易服务器连接断开'
        self.__eventEngine.put(event)

        print u'DemoApi.py DemoTdApi.onFrontDisconnected() end.'
    
    #----------------------------------------------------------------------
    def onHeartBeatWarning(self, n):
        """心跳"""
        print u'DemoApi.py DemoTdApi.onHeartBeatWarning().'
        pass
    
    #----------------------------------------------------------------------
    def onRspAuthenticate(self, data, error, n, last):
        """鉴权"""
        print u'DemoApi.py DemoTdApi.onRspAuthenticate().'
        pass
    
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""

        print u'DemoApi.py DemoTdApi.onRspUserLogin() begin.'

        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'交易服务器登陆成功'
        else:
            log = u'登陆回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
        self.getSettlement()    # 登录完成后立即查询结算信息
        print u'DemoApi.py DemoTdApi.onRspUserLogin() getSettlement success.'

        print u'DemoApi.py DemoTdApi.onRspUserLogin() end.'
    
    #----------------------------------------------------------------------
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""

        print u'DemoApi.py DemoTdApi.onRspUserLogout() begin.'

        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'交易服务器登出成功'
        else:
            log = u'登出回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log
        self.__eventEngine.put(event)

        print u'DemoApi.py DemoTdApi.onRspUserLogout() end.'
    
    #----------------------------------------------------------------------
    def onRspUserPasswordUpdate(self, data, error, n, last):
        """用户登录密码更新事件"""
        print u'DemoApi.py DemoTdApi.onRspUserPasswordUpdate().'
        pass
    
    #----------------------------------------------------------------------
    def onRspTradingAccountPasswordUpdate(self, data, error, n, last):
        """用户交易密码更新事件"""
        print u'DemoApi.py DemoTdApi.onRspTradingAccountPasswordUpdate().'
        pass
    
    #----------------------------------------------------------------------
    def onRspOrderInsert(self, data, error, n, last):
        """发单错误（柜台）"""

        print u'DemoApi.py DemoTdApi.onRspOrderInsert() begin.'
        event = Event(type_=EVENT_LOG)
        log = u' 发单错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)   

        print u'DemoApi.py DemoTdApi.onRspOrderInsert() end.'
    
    #----------------------------------------------------------------------
    def onRspParkedOrderInsert(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspParkedOrderInsert().'
        pass
    
    #----------------------------------------------------------------------
    def onRspParkedOrderAction(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspParkedOrderInsert().'
        pass
    
    #----------------------------------------------------------------------
    def onRspOrderAction(self, data, error, n, last):
        """撤单错误（柜台）"""

        print u'DemoApi.py DemoTdApi.onRspOrderAction() begin.'
        event = Event(type_=EVENT_LOG)
        log = u'撤单错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)

        print u'DemoApi.py DemoTdApi.onRspOrderAction() end.'
    
    #----------------------------------------------------------------------
    def onRspQueryMaxOrderVolume(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQueryMaxOrderVolume().'
        pass
    
    #----------------------------------------------------------------------
    def onRspSettlementInfoConfirm(self, data, error, n, last):
        """确认结算信息回报"""

        print u'DemoApi.py DemoTdApi.onRspSettlementInfoConfirm() begin.'
        event = Event(type_=EVENT_LOG)
        log = u'结算信息确认完成'
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
        event = Event(type_=EVENT_TDLOGIN)
        self.__eventEngine.put(event)
        print u'DemoApi.py DemoTdApi.onRspSettlementInfoConfirm() end.'    
    
    #----------------------------------------------------------------------
    def onRspRemoveParkedOrder(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspRemoveParkedOrder().'
        pass
    
    #----------------------------------------------------------------------
    def onRspRemoveParkedOrderAction(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspRemoveParkedOrderAction().'
        pass
    
    #----------------------------------------------------------------------
    def onRspExecOrderInsert(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspExecOrderInsert().'
        pass
    
    #----------------------------------------------------------------------
    def onRspExecOrderAction(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspExecOrderAction().'
        pass
    
    #----------------------------------------------------------------------
    def onRspForQuoteInsert(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspForQuoteInsert().'
        pass
    
    #----------------------------------------------------------------------
    def onRspQuoteInsert(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQuoteInsert().'
        pass
    
    #----------------------------------------------------------------------
    def onRspQuoteAction(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQuoteAction().'
        pass
    
    #----------------------------------------------------------------------
    def onRspQryOrder(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryOrder().'
        pass
    
    #----------------------------------------------------------------------
    def onRspQryTrade(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryTrade().'
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInvestorPosition(self, data, error, n, last):
        """持仓查询回报"""

        print u'DemoApi.py DemoTdApi.onRspQryInvestorPosition() begin.'

        if error['ErrorID'] == 0:
            event = Event(type_=EVENT_POSITION)
            event.dict_['data'] = data
            self.__eventEngine.put(event)
        else:
            event = Event(type_=EVENT_LOG)
            log = u'持仓查询回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
            event.dict_['log'] = log
            self.__eventEngine.put(event)

        print u'DemoApi.py DemoTdApi.onRspQryInvestorPosition() end.'
    
    #----------------------------------------------------------------------
    def onRspQryTradingAccount(self, data, error, n, last):
        """资金账户查询回报"""

        print u'DemoApi.py DemoTdApi.onRspQryTradingAccount() begin.'
        if error['ErrorID'] == 0:
            event = Event(type_=EVENT_ACCOUNT)
            event.dict_['data'] = data
            self.__eventEngine.put(event)
        else:
            event = Event(type_=EVENT_LOG)
            log = u'账户查询回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
            event.dict_['log'] = log
            self.__eventEngine.put(event)

        print u'DemoApi.py DemoTdApi.onRspQryTradingAccount() end.'
    
    #----------------------------------------------------------------------
    def onRspQryInvestor(self, data, error, n, last):
        """投资者查询回报"""

        print u'DemoApi.py DemoTdApi.onRspQryInvestor() begin.'
        if error['ErrorID'] == 0:
            event = Event(type_=EVENT_INVESTOR)
            event.dict_['data'] = data
            self.__eventEngine.put(event)
        else:
            event = Event(type_=EVENT_LOG)
            log = u'合约投资者回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
            event.dict_['log'] = log
            self.__eventEngine.put(event)
        print u'DemoApi.py DemoTdApi.onRspQryInvestor() end.'


    #----------------------------------------------------------------------
    def onRspQryTradingCode(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryTradingCode() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInstrumentMarginRate(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryInstrumentMarginRate() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInstrumentCommissionRate(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryInstrumentCommissionRate() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryExchange(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryExchange() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryProduct(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryProduct() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInstrument(self, data, error, n, last):
        """
        合约查询回报
        由于该回报的推送速度极快，因此不适合全部存入队列中处理，
        选择先储存在一个本地字典中，全部收集完毕后再推送到队列中
        （由于耗时过长目前使用其他进程读取）
        """

        print u'DemoApi.py DemoTdApi.onRspQryInstrument() begin.'
        if error['ErrorID'] == 0:
            event = Event(type_=EVENT_INSTRUMENT)
            event.dict_['data'] = data
            event.dict_['last'] = last
            self.__eventEngine.put(event)
        else:
            event = Event(type_=EVENT_LOG)
            log = u'合约投资者回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
            event.dict_['log'] = log
            self.__eventEngine.put(event)   
    
        print u'DemoApi.py DemoTdApi.onRspQryInstrument() end.'

    #----------------------------------------------------------------------
    def onRspQryDepthMarketData(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryDepthMarketData().'
        pass
    
    #----------------------------------------------------------------------
    def onRspQrySettlementInfo(self, data, error, n, last):
        """查询结算信息回报"""

        print u'DemoApi.py DemoTdApi.onRspQrySettlementInfo() begin.'
        if last:
            event = Event(type_=EVENT_LOG)
            log = u'结算信息查询完成'
            event.dict_['log'] = log
            self.__eventEngine.put(event)
            
            self.confirmSettlement()    # 查询完成后立即确认结算信息

        print u'DemoApi.py DemoTdApi.onRspQrySettlementInfo() end.'
    
    #----------------------------------------------------------------------
    def onRspQryTransferBank(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryTransferBank() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInvestorPositionDetail(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryInvestorPositionDetail() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryNotice(self, data, error, n, last):
        print u'DemoApi.py DemoTdApi.onRspQryNotice() '
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQrySettlementInfoConfirm(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQrySettlementInfoConfirm() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInvestorPositionCombineDetail(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryInvestorPositionCombineDetail() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryCFMMCTradingAccountKey(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryCFMMCTradingAccountKey() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryEWarrantOffset(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryEWarrantOffset() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInvestorProductGroupMargin(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryInvestorProductGroupMargin() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryExchangeMarginRate(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryExchangeMarginRate() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryExchangeMarginRateAdjust(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryExchangeMarginRateAdjust() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryExchangeRate(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryExchangeRate() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQrySecAgentACIDMap(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQrySecAgentACIDMap() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryOptionInstrTradeCost(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryOptionInstrTradeCost() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryOptionInstrCommRate(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryOptionInstrCommRate() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryExecOrder(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryExecOrder() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryForQuote(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryForQuote() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryQuote(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryQuote() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryTransferSerial(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryTransferSerial() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryAccountregister(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryAccountregister() '
        pass
    
    #----------------------------------------------------------------------
    def onRspError(self, error, n, last):
        """错误回报"""

        print u'DemoApi.py DemoTdApi.onRspError() begin.'

        event = Event(type_=EVENT_LOG)
        log = u'交易错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)

        print u'DemoApi.py DemoTdApi.onRspError() end.'
    
    #----------------------------------------------------------------------
    def onRtnOrder(self, data):
        """报单回报"""
        print u'DemoApi.py DemoTdApi.onRtnOrder() begin.'
        # 更新最大报单编号
        newref = data['OrderRef']
        self.__orderref = max(self.__orderref, int(newref))
        
        # 常规报单事件
        event1 = Event(type_=EVENT_ORDER)
        event1.dict_['data'] = data
        self.__eventEngine.put(event1)
        
        # 特定合约行情事件
        event2 = Event(type_=(EVENT_ORDER_ORDERREF+data['OrderRef']))
        event2.dict_['data'] = data
        self.__eventEngine.put(event2)
        print u'DemoApi.py DemoTdApi.onRtnOrder() end.'
    
    #----------------------------------------------------------------------
    def onRtnTrade(self, data):
        """成交回报"""

        print u'DemoApi.py DemoTdApi.onRtnTrade() begin.'
        # 常规成交事件
        event1 = Event(type_=EVENT_TRADE)
        event1.dict_['data'] = data
        self.__eventEngine.put(event1)
        
        # 特定合约成交事件
        event2 = Event(type_=(EVENT_TRADE_CONTRACT+data['InstrumentID']))
        event2.dict_['data'] = data
        self.__eventEngine.put(event2)

        print u'DemoApi.py DemoTdApi.onRtnTrade() end.'
    
    #----------------------------------------------------------------------
    def onErrRtnOrderInsert(self, data, error):
        """发单错误回报（交易所）"""
        print u'DemoApi.py DemoTdApi.onErrRtnOrderInsert() begin.'

        event = Event(type_=EVENT_LOG)
        log = u'发单错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)

        print u'DemoApi.py DemoTdApi.onErrRtnOrderInsert() end.'
    
    #----------------------------------------------------------------------
    def onErrRtnOrderAction(self, data, error):
        """撤单错误回报（交易所）"""

        print u'DemoApi.py DemoTdApi.onErrRtnOrderAction() begin.'
        event = Event(type_=EVENT_LOG)
        log = u'撤单错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)

        print u'DemoApi.py DemoTdApi.onErrRtnOrderAction() end.'
    
    #----------------------------------------------------------------------
    def onRtnInstrumentStatus(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnInstrumentStatus() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnTradingNotice(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnTradingNotice() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnErrorConditionalOrder(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnErrorConditionalOrder() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnExecOrder(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnExecOrder() '
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnExecOrderInsert(self, data, error):
        """"""
        print u'DemoApi.py DemoTdApi.onErrRtnExecOrderInsert() '
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnExecOrderAction(self, data, error):
        """"""
        print u'DemoApi.py DemoTdApi.onErrRtnExecOrderAction() '
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnForQuoteInsert(self, data, error):
        """"""
        print u'DemoApi.py DemoTdApi.onErrRtnForQuoteInsert() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnQuote(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnQuote() '
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnQuoteInsert(self, data, error):
        """"""
        print u'DemoApi.py DemoTdApi.onErrRtnQuoteInsert() '
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnQuoteAction(self, data, error):
        """"""
        print u'DemoApi.py DemoTdApi.onErrRtnQuoteAction() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnForQuoteRsp(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnForQuoteRsp() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryContractBank(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryContractBank() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryParkedOrder(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryParkedOrder() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryParkedOrderAction(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryParkedOrderAction() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryTradingNotice(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryTradingNotice() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryBrokerTradingParams(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryBrokerTradingParams() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQryBrokerTradingAlgos(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQryBrokerTradingAlgos() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnFromBankToFutureByBank(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnFromBankToFutureByBank() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnFromFutureToBankByBank(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnFromFutureToBankByBank() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnRepealFromBankToFutureByBank(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnRepealFromBankToFutureByBank() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnRepealFromFutureToBankByBank(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnRepealFromFutureToBankByBank() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnFromBankToFutureByFuture(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnFromBankToFutureByFuture() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnFromFutureToBankByFuture(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnFromFutureToBankByFuture() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnRepealFromBankToFutureByFutureManual(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnRepealFromBankToFutureByFutureManual() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnRepealFromFutureToBankByFutureManual(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnRepealFromFutureToBankByFutureManual() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnQueryBankBalanceByFuture(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnQueryBankBalanceByFuture() '
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnBankToFutureByFuture(self, data, error):
        """"""
        print u'DemoApi.py DemoTdApi.onErrRtnBankToFutureByFuture() '
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnFutureToBankByFuture(self, data, error):
        """"""
        print u'DemoApi.py DemoTdApi.onErrRtnFutureToBankByFuture() '
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnRepealBankToFutureByFutureManual(self, data, error):
        """"""
        print u'DemoApi.py DemoTdApi.onErrRtnRepealBankToFutureByFutureManual() '
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnRepealFutureToBankByFutureManual(self, data, error):
        """"""
        print u'DemoApi.py DemoTdApi.onErrRtnRepealFutureToBankByFutureManual() '
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnQueryBankBalanceByFuture(self, data, error):
        """"""
        print u'DemoApi.py DemoTdApi.onErrRtnQueryBankBalanceByFuture() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnRepealFromBankToFutureByFuture(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnRepealFromBankToFutureByFuture() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnRepealFromFutureToBankByFuture(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnRepealFromFutureToBankByFuture() '
        pass
    
    #----------------------------------------------------------------------
    def onRspFromBankToFutureByFuture(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspFromBankToFutureByFuture() '
        pass
    
    #----------------------------------------------------------------------
    def onRspFromFutureToBankByFuture(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspFromFutureToBankByFuture() '
        pass
    
    #----------------------------------------------------------------------
    def onRspQueryBankAccountMoneyByFuture(self, data, error, n, last):
        """"""
        print u'DemoApi.py DemoTdApi.onRspQueryBankAccountMoneyByFuture() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnOpenAccountByBank(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnOpenAccountByBank() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnCancelAccountByBank(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnCancelAccountByBank() '
        pass
    
    #----------------------------------------------------------------------
    def onRtnChangeAccountByBank(self, data):
        """"""
        print u'DemoApi.py DemoTdApi.onRtnChangeAccountByBank() '
        pass
    
    #----------------------------------------------------------------------
    def login(self, address, userid, password, brokerid):
        """连接服务器"""

        print u'DemoApi.py DemoTdApi.login() begin.'
        self.__userid = userid
        self.__password = password
        self.__brokerid = brokerid
        
        # 数据重传模式设为从本日开始
        self.subscribePrivateTopic(0)       
        self.subscribePublicTopic(0)            
        
        # 注册服务器地址
        self.registerFront(address)
        
        # 初始化连接，成功会调用onFrontConnected
        self.init()    

        print u'DemoApi.py DemoTdApi.login() end.'
        
    #----------------------------------------------------------------------
    def getInstrument(self):
        """查询合约"""
        print u'DemoApi.py DemoTdApi.getInstrument() begin.'
        self.__reqid = self.__reqid + 1
        self.reqQryInstrument({}, self.__reqid)
        print u'DemoApi.py DemoTdApi.getInstrument() end.'
        
    #----------------------------------------------------------------------
    def getAccount(self):
        """查询账户"""
        print u'DemoApi.py DemoTdApi.getAccount() begin.'
        self.__reqid = self.__reqid + 1
        self.reqQryTradingAccount({}, self.__reqid)
        print u'DemoApi.py DemoTdApi.getAccount() end.'
        
    #----------------------------------------------------------------------
    def getInvestor(self):
        """查询投资者"""
        print u'DemoApi.py DemoTdApi.getInvestor() begin.'
        self.__reqid = self.__reqid + 1
        self.reqQryInvestor({}, self.__reqid)
        print u'DemoApi.py DemoTdApi.getInvestor() end.'
        
    #----------------------------------------------------------------------
    def getPosition(self):
        """查询持仓"""
        print u'DemoApi.py DemoTdApi.getPosition() begin.'
        self.__reqid = self.__reqid + 1
        req = {}
        req['BrokerID'] = self.__brokerid
        req['InvestorID'] = self.__userid
        self.reqQryInvestorPosition(req, self.__reqid)
        print u'DemoApi.py DemoTdApi.getPosition() end.'
        
    #----------------------------------------------------------------------
    def sendOrder(self, instrumentid, exchangeid, price, pricetype, volume, direction, offset):
        """发单"""
        print u'DemoApi.py DemoTdApi.sendOrder() begin.'
        self.__reqid = self.__reqid + 1
        req = {}
        
        req['InstrumentID'] = instrumentid
        req['OrderPriceType'] = pricetype
        req['LimitPrice'] = price
        req['VolumeTotalOriginal'] = volume
        req['Direction'] = direction
        req['CombOffsetFlag'] = offset
        
        self.__orderref = self.__orderref + 1
        req['OrderRef'] = str(self.__orderref)
        
        req['InvestorID'] = self.__userid
        req['UserID'] = self.__userid
        req['BrokerID'] = self.__brokerid
        req['CombHedgeFlag'] = defineDict['THOST_FTDC_HF_Speculation']       # 投机单
        req['ContingentCondition'] = defineDict['THOST_FTDC_CC_Immediately'] # 立即发单
        req['ForceCloseReason'] = defineDict['THOST_FTDC_FCC_NotForceClose'] # 非强平
        req['IsAutoSuspend'] = 0                                             # 非自动挂起
        req['TimeCondition'] = defineDict['THOST_FTDC_TC_GFD']               # 今日有效
        req['VolumeCondition'] = defineDict['THOST_FTDC_VC_AV']              # 任意成交量
        req['MinVolume'] = 1                                                 # 最小成交量为1
        
        self.reqOrderInsert(req, self.__reqid)
        
        print u'DemoApi.py DemoTdApi.sendOrder() end.'

        # 返回订单号，便于某些算法进行动态管理
        return self.__orderref
           
    
    #----------------------------------------------------------------------
    def cancelOrder(self, instrumentid, exchangeid, orderref, frontid, sessionid):
        """撤单"""

        print u'DemoApi.py DemoTdApi.cancelOrder() begin. '
        self.__reqid = self.__reqid + 1
        req = {}
        
        req['InstrumentID'] = instrumentid
        req['ExchangeID'] = exchangeid
        req['OrderRef'] = orderref
        req['FrontID'] = frontid
        req['SessionID'] = sessionid   
        
        req['ActionFlag'] = defineDict['THOST_FTDC_AF_Delete']
        req['BrokerID'] = self.__brokerid
        req['InvestorID'] = self.__userid
        
        self.reqOrderAction(req, self.__reqid)

        print u'DemoApi.py DemoTdApi.cancelOrder() end.'
    
    #----------------------------------------------------------------------
    def getSettlement(self):
        """查询结算信息"""

        print u'DemoApi.py DemoTdApi.getSettlement() begin '
        self.__reqid = self.__reqid + 1
        req = {}
        
        req['BrokerID'] = self.__brokerid
        req['InvestorID'] = self.__userid
        
        self.reqQrySettlementInfo(req, self.__reqid)

        print u'DemoApi.py DemoTdApi.getSettlement() end.'
        
    #----------------------------------------------------------------------
    def confirmSettlement(self):
        """确认结算信息"""

        print u'DemoApi.py DemoTdApi.confirmSettlement() begin.'
        self.__reqid = self.__reqid + 1
        req = {}
        
        req['BrokerID'] = self.__brokerid
        req['InvestorID'] = self.__userid
        
        self.reqSettlementInfoConfirm(req, self.__reqid)    
        print u'DemoApi.py DemoTdApi.confirmSettlement() end.'