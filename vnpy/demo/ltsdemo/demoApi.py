# encoding: UTF-8

"""
该文件中包含的是交易平台的底层接口相关的部分，
主要对API进行了一定程度的简化封装，方便开发。
"""

import os

from vnltsmd import MdApi
from vnltstd import *
from vnltsl2 import *
from eventEngine import *
from lts_data_type import defineDict

#----------------------------------------------------------------------
def print_dict(d):
    """打印API收到的字典，该函数主要用于开发时的debug"""
    print '-'*60
    for key, value in d.items():
        print key, ':', value
    

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
        super(DemoMdApi, self).__init__()
        
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
        
    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
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
            
    #----------------------------------------------------------------------  
    def onFrontDisconnected(self, n):
        """服务器断开"""
        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = u'行情服务器连接断开'
        self.__eventEngine.put(event)
        
    #---------------------------------------------------------------------- 
    def onHeartBeatWarning(self, n):
        """心跳报警"""
        # 因为API的心跳报警比较常被触发，且与API工作关系不大，因此选择忽略
        pass
    
    #----------------------------------------------------------------------   
    def onRspError(self, error, n, last):
        """错误回报"""
        event = Event(type_=EVENT_LOG)
        log = u'行情错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'行情服务器登陆成功'
        else:
            log = u'登陆回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
        # 重连后自动订阅之前已经订阅过的合约
        if self.__setSubscribed:
            for instrument in self.__setSubscribed:
                self.subscribe(instrument[0], instrument[1])
                
        self.subscribe('510050', 'SSE')
                
    #---------------------------------------------------------------------- 
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'行情服务器登出成功'
        else:
            log = u'登出回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
    #----------------------------------------------------------------------  
    def onRspSubMarketData(self, data, error, n, last):
        """订阅合约回报"""
        # 通常不在乎订阅错误，选择忽略
        pass
        
    #----------------------------------------------------------------------  
    def onRspUnSubMarketData(self, data, error, n, last):
        """退订合约回报"""
        # 同上
        pass  
        
    #----------------------------------------------------------------------  
    def onRtnDepthMarketData(self, data):
        """行情推送"""
        # 行情推送收到后，同时触发常规行情事件，以及特定合约行情事件，用于满足不同类型的监听
        
        # 常规行情事件
        event1 = Event(type_=EVENT_MARKETDATA)
        event1.dict_['data'] = data
        self.__eventEngine.put(event1)
        
        # 特定合约行情事件
        event2 = Event(type_=(EVENT_MARKETDATA_CONTRACT+data['InstrumentID']))
        event2.dict_['data'] = data
        self.__eventEngine.put(event2)
        
    #----------------------------------------------------------------------
    def login(self, address, userid, password, brokerid):
        """连接服务器"""
        self.__userid = userid
        self.__password = password
        self.__brokerid = brokerid
        
        # 注册服务器地址
        self.registerFront(address)
        
        # 初始化连接，成功会调用onFrontConnected
        self.init()
        
    #----------------------------------------------------------------------
    def subscribe(self, instrumentid, exchangeid):
        """订阅合约"""
        req = {}
        req['InstrumentID'] = instrumentid
        req['ExchangeID'] = exchangeid
        self.subscribeMarketData(req)
        
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
        super(DemoTdApi, self).__init__()
        
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
        
    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
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
            
    #----------------------------------------------------------------------  
    def onFrontDisconnected(self, n):
        """服务器断开"""
        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = u'交易服务器连接断开'
        self.__eventEngine.put(event)
        
    #----------------------------------------------------------------------  
    def onHeartBeatWarning(self, n):
        """心跳报警"""
        pass
    
    #----------------------------------------------------------------------
    def onRspError(self, error, n, last):
        """错误回报"""
        event = Event(type_=EVENT_LOG)
        log = u'交易错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'交易服务器登陆成功'
        else:
            log = u'登陆回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
        event2 = Event(type_=EVENT_TDLOGIN)
        self.__eventEngine.put(event2)
        
    #----------------------------------------------------------------------
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'交易服务器登出成功'
        else:
            log = u'登出回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log
        self.__eventEngine.put(event)
    
    #----------------------------------------------------------------------  
    def onRspOrderInsert(self, data, error, n, last):
        """发单错误（柜台）"""
        event = Event(type_=EVENT_LOG)
        log = u' 发单错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)   
        
    #----------------------------------------------------------------------
    def onRspOrderAction(self, data, error, n, last):
        """撤单错误（柜台）"""
        event = Event(type_=EVENT_LOG)
        log = u'撤单错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)

    #----------------------------------------------------------------------
    def onRspUserPasswordUpdate(self, data, error, n, last):
        """用户密码更新错误"""
        pass

    #---------------------------------------------------------------------- 
    def onRspTradingAccountPasswordUpdate(self, data, error, n, last):
        """交易账户密码更新错误"""
        pass

    #----------------------------------------------------------------------  
    def onRspQryExchange(self, data, error, n, last):
        """交易所查询回报"""
        pass

    #----------------------------------------------------------------------  
    def onRspQryInstrument(self, data, error, n, last):
        """
        合约查询回报
        由于该回报的推送速度极快，因此不适合全部存入队列中处理，
        选择先储存在一个本地字典中，全部收集完毕后再推送到队列中
        （由于耗时过长目前使用其他进程读取）
        """
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
        
    #----------------------------------------------------------------------
    def onRspQryInvestor(self, data, error, n, last):
        """投资者查询回报"""
        if error['ErrorID'] == 0:
            event = Event(type_=EVENT_INVESTOR)
            event.dict_['data'] = data
            self.__eventEngine.put(event)
        else:
            event = Event(type_=EVENT_LOG)
            log = u'合约投资者回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
            event.dict_['log'] = log
            self.__eventEngine.put(event)
    
    #----------------------------------------------------------------------    
    def onRspQryTradingCode(self, data, error, n, last):
        """交易编码查询回报"""
        pass
        
    #---------------------------------------------------------------------- 
    def onRspQryTradingAccount(self, data, error, n, last):
        """资金账户查询回报"""
        if error['ErrorID'] == 0:
            event = Event(type_=EVENT_ACCOUNT)
            event.dict_['data'] = data
            self.__eventEngine.put(event)
        else:
            event = Event(type_=EVENT_LOG)
            log = u'账户查询回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
            event.dict_['log'] = log
            self.__eventEngine.put(event)
        
    #----------------------------------------------------------------------
    def onRspQryDepthMarketData(self, data, error, n, last):
        """行情查询回报"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryBondInterest(self, data, error, n, last):
        """债券利息查询回报"""
        pass
        
    #----------------------------------------------------------------------   
    def onRspQryMarketRationInfo(self, data, error, n, last):
        """市值配售查询回报"""
        pass
        
    #----------------------------------------------------------------------  
    def onRspQryInstrumentCommissionRate(self, data, error, n, last):
        """合约手续费查询回报"""
        pass

    #----------------------------------------------------------------------
    def onRspQryETFInstrument(self, data, error, n, last):
        """ETF基金查询回报"""
        pass

    #---------------------------------------------------------------------- 
    def onRspQryETFBasket(self, data, error, n, last):
        """ETF股票篮查询回报"""
        pass

    #----------------------------------------------------------------------
    def onRspQryOFInstrument(self, data, error, n, last):
        """OF合约查询回报"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQrySFInstrument(self, data, error, n, last):
        """SF合约查询回报"""
        pass
        
    #----------------------------------------------------------------------  
    def onRspQryOrder(self, data, error, n, last):
        """报单查询回报"""
        pass   
    
    #----------------------------------------------------------------------
    def onRspQryTrade(self, data, error, n, last):
        """成交查询回报"""
        pass

    #----------------------------------------------------------------------  
    def onRspQryInvestorPosition(self, data, error, n, last):
        """持仓查询回报"""
        if error['ErrorID'] == 0:
            event = Event(type_=EVENT_POSITION)
            event.dict_['data'] = data
            self.__eventEngine.put(event)
        else:
            event = Event(type_=EVENT_LOG)
            log = u'持仓查询回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
            event.dict_['log'] = log
            self.__eventEngine.put(event)

    #---------------------------------------------------------------------- 
    def onRtnOrder(self, data):
        """报单回报"""
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
        
    #----------------------------------------------------------------------
    def onRtnTrade(self, data):
        """成交回报"""
        # 常规成交事件
        event1 = Event(type_=EVENT_TRADE)
        event1.dict_['data'] = data
        self.__eventEngine.put(event1)
        
        # 特定合约成交事件
        event2 = Event(type_=(EVENT_TRADE_CONTRACT+data['InstrumentID']))
        event2.dict_['data'] = data
        self.__eventEngine.put(event2)
        
    #----------------------------------------------------------------------  
    def onErrRtnOrderInsert(self, data, error):
        """发单错误回报（交易所）"""
        event = Event(type_=EVENT_LOG)
        log = u'发单错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
    #---------------------------------------------------------------------- 
    def onErrRtnOrderAction(self, data, error):
        """撤单错误回报（交易所）"""
        event = Event(type_=EVENT_LOG)
        log = u'撤单错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
    #---------------------------------------------------------------------- 
    def onRspFundOutByLiber(self, data, error, n, last):
        """LTS发起出金应答"""
        pass 
        
    #----------------------------------------------------------------------
    def onRtnFundOutByLiber(self, data):
        """LTS发起出金通知"""
        pass 
        
    #----------------------------------------------------------------------  
    def onErrRtnFundOutByLiber(self, data, error):
        """LTS发起出金错误回报"""
        pass
        
    #---------------------------------------------------------------------- 
    def onRtnFundInByBank(self, data):
        """银行发起入金通知"""
        pass 
        
    #----------------------------------------------------------------------   
    def onRspQryFundTransferSerial(self, data, error, n, last):
        """资金转账查询应答"""
        pass
    
    #----------------------------------------------------------------------   
    def onRspFundInterTransfer(self, data, error, n, last):
        """资金内转应答"""
        pass   
      
    #----------------------------------------------------------------------  
    def onRspQryFundInterTransferSerial(self, data, error, n, last):
        """资金内转流水查询应答"""
        pass    
        
    #----------------------------------------------------------------------
    def onRtnFundInterTransferSerial(self, data):
        """资金内转流水通知"""
        pass
        
    #----------------------------------------------------------------------  
    def onErrRtnFundInterTransfer(self, data, error):
        """资金内转错误回报"""
        pass        
    
    #----------------------------------------------------------------------
    def login(self, address, userid, password, brokerid):
        """连接服务器"""
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
        
    #----------------------------------------------------------------------
    def getInstrument(self):
        """查询合约"""
        self.__reqid = self.__reqid + 1
        self.reqQryInstrument({}, self.__reqid)
        
    #----------------------------------------------------------------------
    def getAccount(self):
        """查询账户"""
        self.__reqid = self.__reqid + 1
        self.reqQryTradingAccount({}, self.__reqid)
        
    #----------------------------------------------------------------------
    def getInvestor(self):
        """查询投资者"""
        self.__reqid = self.__reqid + 1
        self.reqQryInvestor({}, self.__reqid)
        
    #----------------------------------------------------------------------
    def getPosition(self):
        """查询持仓"""
        self.__reqid = self.__reqid + 1
        req = {}
        req['BrokerID'] = self.__brokerid
        req['InvestorID'] = self.__userid
        self.reqQryInvestorPosition(req, self.__reqid)
        
    #----------------------------------------------------------------------
    def sendOrder(self, instrumentid, exchangeid, price, pricetype, volume, direction, offset):
        """发单"""
        self.__reqid = self.__reqid + 1
        req = {}
        
        req['InstrumentID'] = instrumentid
        req['ExchangeID'] = exchangeid
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
        req['CombHedgeFlag'] = defineDict['SECURITY_FTDC_HF_Speculation']       # 投机单
        req['ContingentCondition'] = defineDict['SECURITY_FTDC_CC_Immediately'] # 立即发单
        req['ForceCloseReason'] = defineDict['SECURITY_FTDC_FCC_NotForceClose'] # 非强平
        req['IsAutoSuspend'] = 0                                                # 非自动挂起
        req['UserForceClose'] = 0                                               # 非强平
        req['TimeCondition'] = defineDict['SECURITY_FTDC_TC_GFD']               # 今日有效
        req['VolumeCondition'] = defineDict['SECURITY_FTDC_VC_AV']              # 任意成交量
        req['MinVolume'] = 1                                                    # 最小成交量为1
        
        self.reqOrderInsert(req, self.__reqid)
        
        # 返回订单号，便于某些算法进行动态管理
        return self.__orderref
    
    #----------------------------------------------------------------------
    def cancelOrder(self, instrumentid, exchangeid, orderref, frontid, sessionid):
        """撤单"""
        self.__reqid = self.__reqid + 1
        req = {}
        
        req['InstrumentID'] = instrumentid
        req['ExchangeID'] = exchangeid
        req['OrderRef'] = orderref
        req['FrontID'] = frontid
        req['SessionID'] = sessionid   
        
        req['ActionFlag'] = defineDict['SECURITY_FTDC_AF_Delete']
        req['BrokerID'] = self.__brokerid
        req['InvestorID'] = self.__userid
        
        self.reqOrderAction(req, self.__reqid)
        
        

########################################################################
class DemoL2Api(L2MdApi):
    """
    L2行情API
    """

    #----------------------------------------------------------------------
    def __init__(self, eventEngine):
        """API对象的初始化函数"""
        super(DemoL2Api, self).__init__()
        
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
        
        # 初始化.con文件的保存目录为/mdconnection
        self.createFtdcMdApi(os.getcwd() + '\\l2connection\\')             
        
    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = u'L2行情服务器连接成功'
        self.__eventEngine.put(event)
        
        # 如果用户已经填入了用户名等等，则自动尝试连接
        if self.__userid:
            req = {}
            req['UserID'] = self.__userid
            req['Password'] = self.__password
            req['BrokerID'] = self.__brokerid
            self.__reqid = self.__reqid + 1
            self.reqUserLogin(req, self.__reqid)
            
    #----------------------------------------------------------------------  
    def onFrontDisconnected(self, n):
        """服务器断开"""
        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = u'L2行情服务器连接断开'
        self.__eventEngine.put(event)
        
    #---------------------------------------------------------------------- 
    def onHeartBeatWarning(self, n):
        """心跳报警"""
        # 因为API的心跳报警比较常被触发，且与API工作关系不大，因此选择忽略
        pass
    
    #----------------------------------------------------------------------   
    def onRspError(self, error, n, last):
        """错误回报"""
        event = Event(type_=EVENT_LOG)
        log = u'L2行情错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'L2行情服务器登陆成功'
        else:
            log = u'登陆回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
        # 重连后自动订阅之前已经订阅过的合约
        if self.__setSubscribed:
            for instrument in self.__setSubscribed:
                self.subscribe(instrument[0], instrument[1])
                
    #---------------------------------------------------------------------- 
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'L2行情服务器登出成功'
        else:
            log = u'登出回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
    #----------------------------------------------------------------------  
    def onRspSubL2MarketData(self, data, error, n, last):
        """订阅L2合约回报"""
        # 通常不在乎订阅错误，选择忽略
        pass
        
    #----------------------------------------------------------------------  
    def onRspUnSubL2MarketData(self, data, error, n, last):
        """退订L2合约回报"""
        # 同上
        pass  
    
    #----------------------------------------------------------------------  
    def onRspSubL2Index(self, data, error, n, last):
        """订阅L2指数回报"""
        # 通常不在乎订阅错误，选择忽略
        pass
        
    #----------------------------------------------------------------------  
    def onRspUnSubL2Index(self, data, error, n, last):
        """退订L2指数回报"""
        # 同上
        pass      

    #----------------------------------------------------------------------   
    def onRtnL2MarketData(self, data):
        """L2行情推送"""
        # 常规行情事件
        event1 = Event(type_=EVENT_MARKETDATA)
        event1.dict_['data'] = data
        self.__eventEngine.put(event1)
        
        # 特定合约行情事件
        event2 = Event(type_=(EVENT_MARKETDATA_CONTRACT+data['InstrumentID']))
        event2.dict_['data'] = data
        self.__eventEngine.put(event2)
        
    #---------------------------------------------------------------------- 
    def onRtnL2Index(self, data):
        """L2指数行情推送"""
        pass           
    
    #----------------------------------------------------------------------  
    def onRtnL2Order(self, data):
        """L2订单推送"""
        pass
        
    #----------------------------------------------------------------------    
    def onRtnL2Trade(self, data):
        """L2成交推送"""
        pass

    #----------------------------------------------------------------------   
    def onRspSubL2OrderAndTrade(self, error, n, last):
        """订阅L2订单、成交回报"""
        pass
        
    #----------------------------------------------------------------------
    def onRspUnSubL2OrderAndTrade(self, error, n, last):
        """退订L2订单、成交回报"""
        pass
        
    #---------------------------------------------------------------------- 
    def onNtfCheckOrderList(self, instrumentID, functionID):
        """通知清理SSE买卖一队列中数量为0的报单"""
        pass 
        
    #----------------------------------------------------------------------
    def login(self, address, userid, password, brokerid):
        """连接服务器"""
        self.__userid = userid
        self.__password = password
        self.__brokerid = brokerid   
        
        # 注册服务器地址
        self.registerFront(address)
        
        # 初始化连接，成功会调用onFrontConnected
        self.init()
        
    #----------------------------------------------------------------------
    def subscribe(self, instrumentid, exchangeid):
        """订阅合约"""
        req = {}
        req['InstrumentID'] = instrumentid
        req['ExchangeID'] = exchangeid
        self.subscribeL2MarketData(req)
        
        instrument = (instrumentid, exchangeid)
        self.__setSubscribed.add(instrument)        

