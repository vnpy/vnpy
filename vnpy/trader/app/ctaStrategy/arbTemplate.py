# encoding: UTF-8

'''
本文件包含了CTA引擎中的策略开发用模板，开发策略时需要继承arbTemplate类。
'''

from datetime import datetime,timedelta
import os,csv
from vnpy.trader.app.ctaStrategy.ctaBase import *
from vnpy.trader.vtConstant import *


########################################################################
class arbTemplate(object):
    """期现套利策略模板"""
    
    # 策略类的名称和作者
    className = 'arbTemplate'
    author = u'李来佳'

    # 策略的基本参数
    name        = 'StrategyName'        # 策略实例名称
    vtSymbol    = EMPTY_STRING          # 交易的合约vt系统代码
    symbol      = EMPTY_STRING          # 交易的合约代码

    base_symbol = EMPTY_STRING          # 交易主货币   btc
    quote_symbol = EMPTY_STRING         # 基准货币     usdt
    spot_symbol = EMPTY_STRING          # 现货交易所币对 btc_usdt
    future_symbol = EMPTY_STRING         # 期货合约 btc:next_week:10
    Leg1Symbol = EMPTY_STRING           # 带交易所信息的symbol，如： btc_usdt.OKEX
    Leg2Symbol = EMPTY_STRING           # 带交易所信息的symbol，如： btc:next_week:10.OKEX
    exchange = EMPTY_STRING
    gatewayName = EMPTY_STRING

    # 策略的基本变量，由引擎管理
    inited = False                 # 是否进行了初始化
    trading = False                # 是否启动交易，由引擎管理
    backtesting = False            # 是否回测

    # 参数列表，保存了参数的名称
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbol',
                 'base_symbol',
                 'quote_symbol',
                 'spot_symbol',
                 'future_symbol',
                 'Leg1Symbol',
                 'Leg2Symbol',
                 'exchange',
                 'gatewayName'
                 ]

    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading',
               'spot_entrust',
               'future_entrust']

    tradingOpen = True  # 允许开仓
    forceTradingClose = False  # 强制平仓标志
    delayMission = []  # 延迟的任务
    position = None  # 持仓

    is_7x24 = True  # 是否7x24运行

    # ----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        self.ctaEngine = ctaEngine

        # 委托单状态
        self.spot_entrust = 0            # 0 表示没有委托，1 表示存在多仓的委托，-1 表示存在空仓的委托
        self.future_entrust = 0             # 0 表示没有委托，1 表示存在多仓的委托，-1 表示存在空仓的委托

        # 保存委托单编号和相关委托单的字典
        # key为委托单编号
        # value为该合约相关的委托单
        self.uncompletedOrders = {}

        # 设置策略的参数
        if setting:
            self.writeCtaLog(u'基类设置参数')
            d = self.__dict__
            for key in self.paramList:
                if key in setting:
                    d[key] = setting[key]
    
    # ----------------------------------------------------------------------
    def onInit(self):
        """初始化策略（必须由用户继承实现）"""
        raise NotImplementedError
    
    # ----------------------------------------------------------------------
    def onStart(self):
        """启动策略（必须由用户继承实现）"""
        raise NotImplementedError
    
    # ----------------------------------------------------------------------
    def onStop(self):
        """停止策略（必须由用户继承实现）"""
        raise NotImplementedError

    # ----------------------------------------------------------------------
    def onTick(self, tick):
        """收到行情TICK推送（必须由用户继承实现）"""
        raise NotImplementedError

    # ----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        raise NotImplementedError
    
    # ----------------------------------------------------------------------
    def onTrade(self, trade):
        """收到成交推送（必须由用户继承实现）"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送（必须由用户继承实现）"""
        raise NotImplementedError

    #----------------------------------------------------------------------
    def cancelOrder(self, vtOrderID):
        """撤单"""

        # 如果发单号为空字符串，则不进行后续操作
        if not vtOrderID or vtOrderID == '':
            return

        self.ctaEngine.cancelOrder(vtOrderID)

    def saveData(self):
        """保持bar数据"""
        pass

    def onTimer(self):
        """定时执行任务
        由mainEngine驱动"""
        pass

    # ----------------------------------------------------------------------
    def setParam(self, setting):
        """设置参数"""
        self.writeCtaLog(u'使用参数:{}'.format(setting))
        d = self.__dict__
        for key in self.paramList:
            if key in setting:
                d[key] = setting[key]
    # ----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """记录CTA日志"""
        try:
            self.ctaEngine.writeCtaLog(content, strategy_name=self.name)
        except Exception as ex:
            content = self.name + ':' + content
            self.ctaEngine.writeCtaLog(content)

    # ----------------------------------------------------------------------
    def writeCtaError(self, content):
        """记录CTA出错日志"""
        try:
            self.ctaEngine.writeCtaError(content, strategy_name=self.name)
        except Exception as ex:
            content = self.name + ':' + content
            self.ctaEngine.writeCtaError(content)

    # ----------------------------------------------------------------------
    def writeCtaWarning(self, content):
        """记录CTA告警日志"""
        try:
            self.ctaEngine.writeCtaWarning(content, strategy_name=self.name)
        except Exception as ex:
            content = self.name + ':' + content
            self.ctaEngine.writeCtaWarning(content)

    # ----------------------------------------------------------------------
    def writeCtaNotification(self, content):
        """记录CTA通知日志"""
        content = self.name + ':' + content

        if not self.backtesting:
            self.ctaEngine.writeCtaNotification(content)
        else:
            self.ctaEngine.writeCtaLog(content)

    # ----------------------------------------------------------------------
    def writeCtaCritical(self, content):
        """记录CTA系统异常日志"""

        if not self.backtesting:
            try:
                self.ctaEngine.writeCtaCritical(content,strategy_name=self.name)
            except Exception as ex:
                content = self.name + ':' + content
                self.ctaEngine.writeCtaCritical(content)
        else:
            content = self.name + ':' + content
            self.ctaEngine.writeCtaError(content)

    def sendSignal(self,direction,price, level):
        """发送信号通知"""
        try:
            if not self.backtesting:
                self.ctaEngine.sendCtaSignal(source=self.name, symbol=self.vtSymbol, direction=direction, price=price, level=level)

        except Exception as ex:
            self.writeCtaError(u'sendSignal Exception:{0}'.format(str(ex)))

    #----------------------------------------------------------------------
    def putEvent(self):
        """发出策略状态变化事件"""
        self.ctaEngine.putStrategyEvent(self.name)

    #----------------------------------------------------------------------
    def getEngineType(self):
        """查询当前运行的环境"""
        return self.ctaEngine.engineType

    def append_data(self, file_name, dict_data, field_names=None):
        """
        添加数据到csv文件中
        :param file_name:  csv的文件全路径
        :param dict_data:  OrderedDict
        :return:
        """
        if not isinstance(dict_data, dict):
            self.writeCtaError(u'append_data，输入数据不是dict')
            return

        dict_fieldnames = list(dict_data.keys()) if field_names is None else field_names

        if not isinstance(dict_fieldnames, list):
            self.writeCtaError(u'append_data，输入字段不是list')
            return
        try:
            if not os.path.exists(file_name):
                self.writeCtaLog(u'create csv file:{}'.format(file_name))
                with open(file_name, 'a', encoding='utf8', newline='') as csvWriteFile:
                    writer = csv.DictWriter(f=csvWriteFile, fieldnames=dict_fieldnames, dialect='excel')
                    self.writeCtaLog(u'write csv header:{}'.format(dict_fieldnames))
                    writer.writeheader()
                    writer.writerow(dict_data)
            else:
                with open(file_name, 'a', encoding='utf8', newline='') as csvWriteFile:
                    writer = csv.DictWriter(f=csvWriteFile, fieldnames=dict_fieldnames, dialect='excel')
                    writer.writerow(dict_data)
        except Exception as ex:
            self.writeCtaError(u'append_data exception:{}'.format(str(ex)))


    def checkExistDelayMission(self, func):
        if len(self.delayMission) == 0:
            return False

        for mission in self.delayMission:
            if 'func' in mission and mission['func'] == func:
                return True
        return False

    def cancelForceClose(self):
        """
        取消强制平仓
        :return: 
        """
        pass

    def forceCloseAllPos(self):
        """
        策略实现上层调度，强制平所有仓位，不再开仓
        :return: 
        """
        pass

    def forceOpenPos(self, longPos, shortPos):
        """
        策略实现上层调度，强制开仓
        :param longPos: 对应开仓的多单[{"price": 2560, volume": 77, "symbol": "RB99", "margin": -953, "direction": "long" }]
        :param shortPos: 对应开仓的空单[{"price": 2560, volume": 77, "symbol": "RB99", "margin": -953, "direction": "short" }]
        :return: 
        """
        pass

    def cancelAllOrders(self):
        """
        撤销所有委托
        :return: 
        """
        pass

    def getPositions(self):
        """
        获取策略当前持仓
        :return: [{'vtSymbol':symbol,'direction':direction,'volume':volume]
        """
        return []

