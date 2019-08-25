# encoding: UTF-8

from __future__ import division
from datetime import datetime
import os,csv

from vnpy.trader.vtConstant import STATUS_NOTTRADED, STATUS_PARTTRADED, STATUS_UNKNOWN, EMPTY_STRING


# 活动委托状态
STATUS_ACTIVE = [STATUS_NOTTRADED, STATUS_PARTTRADED, STATUS_UNKNOWN]

RUNNING_NORMAL = 'normal'
RUNNING_ACTIVE = 'active'
RUNNING_WRONG = 'wrong'
RUNNING_SUCCESS = 'success'

########################################################################
class AlgoTemplate(object):
    """算法模板"""
    templateName = 'AlgoTemplate'

    timestamp = ''
    count = 0           # 当前策略模板，在当前timestamp的执行实例记录器

    @classmethod
    #----------------------------------------------------------------------
    def new(cls, engine, setting):
        """创建新对象"""
        timestamp = datetime.now().strftime('%Y%m%d%H%M%S')
        if timestamp != cls.timestamp:
            cls.timestamp = timestamp
            cls.count = 0
        else:
            cls.count += 1

        algoName = '_'.join([cls.templateName, cls.timestamp, str(cls.count)])
        algo = cls(engine, setting, algoName)
        return algo

    # ----------------------------------------------------------------------
    def __init__(self, engine, setting, algoName):
        """Constructor"""
        self.engine = engine
        self.active = True
        self.algoName = algoName
        self.activeOrderDict = {}  # vtOrderID:order

        self.task_id = 1               # 上层执行任务ID
        self.paln_name = EMPTY_STRING  # 上层执行计划
        self.plan_id = EMPTY_STRING    # 执行计划的ID
        self.progress = 0   # 当前进度
        self.plan_start_time = EMPTY_STRING
        self.plan_stop_time = EMPTY_STRING
        self.start_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        self.plan_buy_price = 0
        self.plan_buy_volume = 0
        self.plan_sell_price = 0
        self.plan_sell_volume = 0
        self.buy_volume = 0
        self.buy_price = 0
        self.sell_volume = 0
        self.sell_price = 0
        self.status = RUNNING_NORMAL
        self.error_msg = EMPTY_STRING

    # ----------------------------------------------------------------------
    def updateTick(self, tick):
        """"""
        if not self.active:
            return

        self.onTick(tick)

    # ----------------------------------------------------------------------
    def updateTrade(self, trade):
        """"""
        if not self.active:
            return

        self.onTrade(trade)

    # ----------------------------------------------------------------------
    def updateOrder(self, order):
        """"""
        #if not self.active:
        #    return

        # 活动委托需要缓存
        if order.status in STATUS_ACTIVE:
            self.activeOrderDict[order.vtOrderID] = order
        # 结束委托需要移除
        elif order.vtOrderID in self.activeOrderDict:
            del self.activeOrderDict[order.vtOrderID]

        self.onOrder(order)

    # ----------------------------------------------------------------------
    def updateTimer(self):
        """"""
        # if not self.active:
        #    return

        self.onTimer()

    #----------------------------------------------------------------------
    def stop(self):
        """外部输入，停止运行算法"""
        # 更新状态
        self.active = False
        # 撤单
        self.cancelAll()
        # 停止事件
        self.onStop()

    #----------------------------------------------------------------------
    def onTick(self, tick):
        """"""
        pass

    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """"""
        pass

    #----------------------------------------------------------------------
    def onOrder(self, order):
        """"""
        pass

    #----------------------------------------------------------------------
    def onTimer(self):
        """"""
        pass

    #----------------------------------------------------------------------
    def onStop(self):
        """"""
        pass

    #----------------------------------------------------------------------
    def subscribe(self, vtSymbol):
        """"""
        self.engine.subscribe(self, vtSymbol)

    #----------------------------------------------------------------------
    def buy(self, vtSymbol, price, volume, priceType=None, offset=None):
        """"""
        return self.engine.buy(self, vtSymbol, price, volume, priceType, offset)

    #----------------------------------------------------------------------
    def sell(self, vtSymbol, price, volume, priceType=None, offset=None):
        """"""
        return self.engine.sell(self, vtSymbol, price, volume, priceType, offset)

    #----------------------------------------------------------------------
    def cancelOrder(self, vtOrderID):
        """"""
        self.engine.cancelOrder(self, vtOrderID)

    #----------------------------------------------------------------------
    def cancelAll(self):
        """"""
        if not self.activeOrderDict:
            return False

        for order in self.activeOrderDict.values():
            self.cancelOrder(order.vtOrderID)
        return True

    #----------------------------------------------------------------------
    def getTick(self, vtSymbol):
        """"""
        return self.engine.getTick(self, vtSymbol)

    #----------------------------------------------------------------------
    def getContract(self, vtSymbol):
        """"""
        return self.engine.getContract(self, vtSymbol)

    #----------------------------------------------------------------------
    def roundValue(self, value, change):
        """标准化价格或者数量"""
        if not change:
            return value

        n = value / change
        v = round(n, 0) * change
        return v

    #----------------------------------------------------------------------
    def putVarEvent(self, d):
        """更新变量"""
        d['active'] = self.active
        self.engine.putVarEvent(self, d)

    #----------------------------------------------------------------------
    def putParamEvent(self, d):
        """更新参数"""
        self.engine.putParamEvent(self, d)

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """输出日志"""
        self.engine.writeLog(content, self)

    def writeError(self,content):
        """输出错误日志"""
        self.engine.writeError(content,self)

    def append_data(self, file_name, dict_data, field_names=None):
        """
        添加数据到csv文件中
        :param file_name:  csv的文件全路径
        :param dict_data:  OrderedDict
        :return:
        """
        if not isinstance(dict_data, dict):
            self.writeLog(u'append_data，输入数据不是dict')
            return

        dict_fieldnames = list(dict_data.keys()) if field_names is None else field_names

        if not isinstance(dict_fieldnames, list):
            self.writeLog(u'append_data，输入字段不是list')
            return
        try:
            if not os.path.exists(file_name):
                # 写入表头
                self.writeLog(u'create csv file:{}'.format(file_name))
                with open(file_name, 'a', encoding='utf8', newline='') as csvWriteFile:
                    writer = csv.DictWriter(f=csvWriteFile, fieldnames=dict_fieldnames, dialect='excel')
                    self.writeLog(u'write csv header:{}'.format(dict_fieldnames))
                    writer.writeheader()
                    writer.writerow(dict_data)
            else:
                # 写入数据
                with open(file_name, 'a', encoding='utf8', newline='') as csvWriteFile:
                    writer = csv.DictWriter(f=csvWriteFile, fieldnames=dict_fieldnames, dialect='excel',extrasaction='ignore')
                    writer.writerow(dict_data)

        except Exception as ex:
            self.writeLog(u'append_data exception:{}'.format(str(ex)))
