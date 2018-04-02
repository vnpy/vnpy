# encoding: UTF-8

from vnpy.trader.app.optionMaster.omStrategy import OmStrategyTemplate


########################################################################
class DemoStrategy(OmStrategyTemplate):
    """演示策略"""
    className = 'DemoStrategy'
    author = u'用Python的交易员'
    
    temp = 123

    # 参数列表，保存了参数的名称
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbols',
                 'temp']

    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading']

    #----------------------------------------------------------------------
    def __init__(self, engine, setting):
        """Constructor"""
        super(DemoStrategy, self).__init__(engine, setting)

    #----------------------------------------------------------------------
    def onInit(self):
        """初始化"""
        self.writeLog(u'%s策略初始化' %self.name)
        self.putEvent()

    #----------------------------------------------------------------------
    def onStart(self):
        """启动"""
        self.writeLog(u'%s策略启动' %self.name)
        self.putEvent()

    #----------------------------------------------------------------------
    def onStop(self):
        """停止"""
        self.writeLog(u'%s策略停止' %self.name)
        self.putEvent()

    #----------------------------------------------------------------------
    def onTick(self, tick):
        """行情推送"""
        self.writeLog(u'%s策略收到行情推送' %self.name)
        self.putEvent()

    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """成交推送"""
        self.writeLog(u'%s策略收到成交推送' %self.name)
        self.putEvent()
        
    #----------------------------------------------------------------------
    def onOrder(self, order):
        """委托推送"""
        self.writeLog(u'%s策略收到委托推送' %self.name)
        self.putEvent()
    
    #----------------------------------------------------------------------
    def onTimer(self):
        """定时推送"""
        self.writeLog(u'%s策略收到定时推送，自定义参数%s' %(self.name, self.temp))    

    