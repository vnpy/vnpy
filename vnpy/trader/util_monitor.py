# encoding: UTF-8

from collections import OrderedDict

from .vtGateway import *
from .setup_logger import setup_logger

########################################################################
class BasicMonitor(object):
    """
    基础监控

    headerDict中的值对应的字典格式如下
    {'chinese': u'中文名', 'cellType': ""}

    """

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine=None, parent=None):
        self.eventEngine = eventEngine

        # 保存表头标签用
        self.headerDict = OrderedDict()  # 有序字典，key是英文名，value是对应的配置字典
        self.headerList = []             # 对应self.headerDict.keys()

        # 保存相关数据用
        self.dataDict = {}  # 字典，key是字段对应的数据，value是保存相关单元格的字典
        self.dataKey = ''   # 字典键对应的数据字段

        # 监控的事件类型
        self.eventType = ''

        # 保存数据对象到单元格
        self.saveData = False

        self.logger = None

    # ----------------------------------------------------------------------
    def setHeaderDict(self, headerDict):
        """设置表头有序字典"""
        self.headerDict = headerDict
        self.headerList = headerDict.keys()

    # ----------------------------------------------------------------------
    def setDataKey(self, dataKey):
        """设置数据字典的键"""
        self.dataKey = dataKey

    # ----------------------------------------------------------------------
    def setEventType(self, eventType):
        """设置监控的事件类型"""
        self.eventType = eventType

    # ----------------------------------------------------------------------
    def setSaveData(self, saveData):
        """设置是否要保存数据到单元格"""
        self.saveData = saveData

    # ----------------------------------------------------------------------
    def registerEvent(self):
        self.eventEngine.register(self.eventType, self.updateEvent)

    # ----------------------------------------------------------------------
    def updateEvent(self, event):
        """收到事件更新"""
        data = event.dict_['data']
        self.updateData(data)

    # ----------------------------------------------------------------------
    def updateData(self, data):
        """将数据更新到表格中"""
        s = []
        for header, value in self.headerDict.items():
            v = getattr(data, header)
            #if isinstance(v, basestring) and not isinstance(v, unicode):
            #    try:
            #        v = v.decode('gbk')
            #    except:
            #        v = v.decode('utf8')
            s.append('%s: %s' % (value['chinese'], str(v)))
        if self.logger is not None:
           self.logger.info(' '.join(s))

    def createLogger(self, monitor_name):

        currentFolder = os.path.abspath(os.path.join(os.getcwd(), 'logs'))
        if os.path.isdir(currentFolder):
            # 如果工作目录下，存在data子目录，就使用data子目录
            path = currentFolder
        else:
            # 否则，使用缺省保存目录 vnpy/trader/app/ctaStrategy/data
            path = os.path.abspath(os.path.join(os.path.dirname(__file__),'logs'))

        filename = os.path.abspath(os.path.join(path, monitor_name))
        print( u'create logger:{}'.format(filename))
        self.logger = setup_logger(filename=filename, name=monitor_name,debug=True)

########################################################################
class MarketMonitor(BasicMonitor):
    """市场监控组件"""

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(MarketMonitor, self).__init__(eventEngine, parent)

        # 设置表头有序字典
        d = OrderedDict()
        d['symbol'] = {'chinese': u'合约代码', 'cellType': ""}
        d['vtSymbol'] = {'chinese': u'名称', 'cellType': ""}
        d['lastPrice'] = {'chinese': u'最新价', 'cellType': ""}
        d['volume'] = {'chinese': u'成交量', 'cellType': ""}
        d['openInterest'] = {'chinese': u'持仓量', 'cellType': ""}
        d['openPrice'] = {'chinese': u'开盘价', 'cellType': ""}
        d['highPrice'] = {'chinese': u'最高价', 'cellType': ""}
        d['lowPrice'] = {'chinese': u'最低价', 'cellType': ""}
        d['bidPrice1'] = {'chinese': u'买一价', 'cellType': ""}
        d['bidVolume1'] = {'chinese': u'买一量', 'cellType': ""}
        d['askPrice1'] = {'chinese': u'卖一价', 'cellType': ""}
        d['askVolume1'] = {'chinese': u'卖一量', 'cellType': ""}
        d['time'] = {'chinese': u'时间', 'cellType': ""}
        d['gatewayName'] = {'chinese': u'接口', 'cellType': ""}
        self.setHeaderDict(d)

        # 设置数据键
        self.setDataKey('vtSymbol')

        # 设置监控事件类型
        self.setEventType(EVENT_TICK)

        # 注册事件监听
        self.registerEvent()


########################################################################
class LogMonitor(BasicMonitor):
    """日志监控"""

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(LogMonitor, self).__init__(eventEngine, parent)

        d = OrderedDict()
        d['logTime'] = {'chinese': u'时间', 'cellType': ""}
        d['logContent'] = {'chinese': u'内容', 'cellType': ""}
        d['gatewayName'] = {'chinese': u'接口', 'cellType': ""}
        self.setHeaderDict(d)

        self.setEventType(EVENT_LOG)
        self.registerEvent()


########################################################################
class CtaLogMonitor(BasicMonitor):
    """日志监控"""

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(CtaLogMonitor, self).__init__(eventEngine, parent)

        d = OrderedDict()
        d['logTime'] = {'chinese': u'时间', 'cellType': ""}
        d['logContent'] = {'chinese': u'内容', 'cellType': ""}
        # d['gatewayName'] = {'chinese': u'接口', 'cellType': ""}
        self.setHeaderDict(d)

        self.setEventType(EVENT_CTA_LOG)
        self.registerEvent()

########################################################################
class ErrorMonitor(BasicMonitor):
    """错误监控"""

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(ErrorMonitor, self).__init__(eventEngine, parent)

        d = OrderedDict()
        d['errorID'] = {'chinese': u'错误代码', 'cellType': ""}
        d['errorMsg'] = {'chinese': u'错误信息', 'cellType': ""}
        d['additionalInfo'] = {'chinese': u'补充信息', 'cellType': ""}
        d['gatewayName'] = {'chinese': u'接口', 'cellType': ""}
        self.setHeaderDict(d)

        self.createLogger(EVENT_ERROR)

        self.setEventType(EVENT_ERROR)
        self.registerEvent()



########################################################################
class TradeMonitor(BasicMonitor):
    """成交监控"""

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(TradeMonitor, self).__init__(eventEngine, parent)

        d = OrderedDict()
        d['tradeID'] = {'chinese': u'成交编号', 'cellType': ""}
        d['orderID'] = {'chinese': u'委托编号', 'cellType': ""}
        d['symbol'] = {'chinese': u'合约代码', 'cellType': ""}
        d['vtSymbol'] = {'chinese': u'名称', 'cellType': ""}
        d['direction'] = {'chinese': u'方向', 'cellType': ""}
        d['offset'] = {'chinese': u'开平', 'cellType': ""}
        d['price'] = {'chinese': u'价格', 'cellType': ""}
        d['volume'] = {'chinese': u'数量', 'cellType': ""}
        d['tradeTime'] = {'chinese': u'成交时间', 'cellType': ""}
        d['gatewayName'] = {'chinese': u'接口', 'cellType': ""}
        self.setHeaderDict(d)

        self.createLogger(EVENT_TRADE)

        self.setEventType(EVENT_TRADE)
        self.registerEvent()


########################################################################
class OrderMonitor(BasicMonitor):
    """委托监控"""

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine, mainEngine, parent=None):
        """Constructor"""
        super(OrderMonitor, self).__init__(eventEngine, parent)

        self.mainEngine = mainEngine

        d = OrderedDict()
        d['orderID'] = {'chinese': u'委托编号', 'cellType': ""}
        d['symbol'] = {'chinese': u'合约代码', 'cellType': ""}
        d['vtSymbol'] = {'chinese': u'名称', 'cellType': ""}
        d['direction'] = {'chinese': u'方向', 'cellType': ""}
        d['offset'] = {'chinese': u'开平', 'cellType': ""}
        d['price'] = {'chinese': u'价格', 'cellType': ""}
        d['totalVolume'] = {'chinese': u'委托数量', 'cellType': ""}
        d['tradedVolume'] = {'chinese': u'成交数量', 'cellType': ""}
        d['status'] = {'chinese': u'状态', 'cellType': ""}
        d['orderTime'] = {'chinese': u'委托时间', 'cellType': ""}
        d['cancelTime'] = {'chinese': u'撤销时间', 'cellType': ""}
        d['frontID'] = {'chinese': u'前置编号', 'cellType': ""}
        d['sessionID'] = {'chinese': u'会话编号', 'cellType': ""}
        d['gatewayName'] = {'chinese': u'接口', 'cellType': ""}
        self.setHeaderDict(d)

        self.createLogger(EVENT_ORDER)

        self.setDataKey('vtOrderID')
        self.setEventType(EVENT_ORDER)
        self.setSaveData(True)

        self.registerEvent()


########################################################################
class PositionMonitor(BasicMonitor):
    """持仓监控"""

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(PositionMonitor, self).__init__(eventEngine, parent)

        d = OrderedDict()
        d['symbol'] = {'chinese': u'合约代码', 'cellType': ""}
        d['vtSymbol'] = {'chinese': u'名称', 'cellType': ""}
        d['direction'] = {'chinese': u'方向', 'cellType': ""}
        d['position'] = {'chinese': u'持仓量', 'cellType': ""}
        d['ydPosition'] = {'chinese': u'昨持仓', 'cellType': ""}
        d['frozen'] = {'chinese': u'冻结量', 'cellType': ""}
        d['price'] = {'chinese': u'价格', 'cellType': ""}
        d['gatewayName'] = {'chinese': u'接口', 'cellType': ""}
        self.setHeaderDict(d)
        self.createLogger(EVENT_POSITION)
        self.setDataKey('vtPositionName')
        self.setEventType(EVENT_POSITION)
        self.registerEvent()

########################################################################
class AccountMonitor(BasicMonitor):
    """账户监控"""

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(AccountMonitor, self).__init__(eventEngine, parent)

        d = OrderedDict()
        d['accountID'] = {'chinese': u'账户', 'cellType': ""}
        d['preBalance'] = {'chinese': u'昨结', 'cellType': ""}
        d['balance'] = {'chinese': u'净值', 'cellType': ""}
        d['available'] = {'chinese': u'可用', 'cellType': ""}
        d['commission'] = {'chinese': u'手续费', 'cellType': ""}
        d['margin'] = {'chinese': u'保证金', 'cellType': ""}
        d['closeProfit'] = {'chinese': u'平仓盈亏', 'cellType': ""}
        d['positionProfit'] = {'chinese': u'持仓盈亏', 'cellType': ""}
        d['gatewayName'] = {'chinese': u'接口', 'cellType': ""}
        self.setHeaderDict(d)
        self.createLogger(EVENT_ACCOUNT)
        self.setDataKey('vtAccountID')
        self.setEventType(EVENT_ACCOUNT)
        self.registerEvent()
