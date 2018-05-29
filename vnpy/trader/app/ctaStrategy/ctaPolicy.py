# encoding: UTF-8

import os
import sys
import json
from datetime import datetime
from collections import OrderedDict

from vnpy.trader.app.ctaStrategy.ctaBase import *
from vnpy.trader.vtConstant import *


class CtaPolicy(object):
    """
    策略的持久化Policy
    """

    def __init__(self, strategy=None):
        """
        构造
        :param strategy:
        """
        self.strategy = strategy

        self.create_time = None
        self.save_time = None

    def writeCtaLog(self, log):
        """
        写入日志
        :param log:
        :return:
        """
        if self.strategy:
            self.strategy.writeCtaLog(log)

    def writeCtaError(self, log):
        """
        写入错误日志
        :param log:
        :return:
        """
        if self.strategy:
            self.strategy.writeCtaError(log)

    def toJson(self):
        """
        将数据转换成dict
        datetime =》 string
        object =》 string
        :return:
        """
        j = OrderedDict()
        j['create_time'] = self.create_time.strftime('%Y-%m-%d %H:%M:%S') if self.create_time is not None else EMPTY_STRING
        j['save_time'] = self.save_time.strftime('%Y-%m-%d %H:%M:%S') if self.save_time is not None else EMPTY_STRING

        return j

    def fromJson(self, json_data):
        """
        将数据从json_data中恢复
       :param json_data:
        :return:
        """
        self.writeCtaLog(u'将数据从json_data中恢复')

        if 'create_time' in json_data:
            try:
                self.create_time = datetime.strptime(json_data['create_time'], '%Y-%m-%d %H:%M:%S')
            except Exception as ex:
                self.writeCtaError(u'解释create_time异常:{}'.format(str(ex)))
                self.create_time = datetime.now()

        if 'save_time' in json_data:
            try:
                self.save_time = datetime.strptime(json_data['save_time'], '%Y-%m-%d %H:%M:%S')
            except Exception as ex:
                self.writeCtaError(u'解释save_time异常:{}'.format(str(ex)))
                self.save_time = datetime.now()

    def load(self):
        """
        从持久化文件中获取
        :return:
        """
        json_file = os.path.abspath(os.path.join(self.get_data_folder(), u'{}_Policy.json'.format(self.strategy.name)))

        json_data = {}
        if os.path.exists(json_file):
            try:
                with open(json_file, 'r', encoding='utf8') as f:
                    # 解析json文件
                    json_data = json.load(f)
            except IOError as ex:
                self.writeCtaError(u'读取Policy文件{}出错,ex:{}'.format(json_file,str(ex)))
                json_data = {}

        # 从持久化文件恢复数据
        self.fromJson(json_data)

    def save(self):
        """
        保存至持久化文件
        :return:
        """
        json_file = os.path.abspath(
            os.path.join(self.get_data_folder(), u'{}_Policy.json'.format(self.strategy.name)))

        try:
            json_data = self.toJson()

            if self.strategy and self.strategy.backtesting:
                json_data['save_time'] = self.strategy.curDateTime.strftime('%Y-%m-%d %H:%M:%S')
            else:
                json_data['save_time'] = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

            with open(json_file, 'w') as f:
                data = json.dumps(json_data, indent=4)
                f.write(data)
                #self.writeCtaLog(u'写入Policy文件:{}成功'.format(json_file))
        except IOError as ex:
            self.writeCtaError(u'写入Policy文件{}出错,ex:{}'.format(json_file, str(ex)))

    def export_history(self):
        """
        导出历史
        :return:
        """
        export_dir =  os.path.abspath(os.path.join(
            self.get_data_folder(),
             'export_csv',
             '{}'.format(self.strategy.curDateTime.strftime('%Y%m%d'))))
        if not os.path.exists(export_dir):
            try:
                os.mkdir(export_dir)
            except Exception as ex:
                self.writeCtaError(u'创建Policy切片目录{}出错,ex:{}'.format(export_dir, str(ex)))
                return

        json_file = os.path.abspath(os.path.join(
             export_dir,
             u'{}_Policy_{}.json'.format(self.strategy.name, self.strategy.curDateTime.strftime('%Y%m%d_%H%M'))))

        try:
            json_data = self.toJson()

            if self.strategy and self.strategy.backtesting:
                json_data['save_time'] = self.strategy.curDateTime.strftime('%Y-%m-%d %H:%M:%S')
            else:
                json_data['save_time'] = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

            with open(json_file, 'w') as f:
                data = json.dumps(json_data, indent=4)
                f.write(data)
                # self.writeCtaLog(u'写入Policy文件:{}成功'.format(json_file))
        except IOError as ex:
            self.writeCtaError(u'写入Policy文件{}出错,ex:{}'.format(json_file, str(ex)))

    def get_data_folder(self):
        """获取数据目录"""
        # 工作目录
        currentFolder = os.path.abspath(os.path.join(os.getcwd(), u'data'))
        if os.path.isdir(currentFolder):
            # 如果工作目录下，存在data子目录，就使用data子目录
            return currentFolder
        else:
            # 否则，使用缺省保存目录 vnpy/trader/app/ctaStrategy/data
            return os.path.abspath(os.path.join(os.path.dirname(__file__), u'data'))

class RenkoPolicy(CtaPolicy):
    """Renko CTA的策略规则类
    包括：
    1、风险评估
    2、最低止损位置
    3、保本止损位置
    4、跟随止损/止盈位置
    5、是否加仓等

    R1,Big Range/Renko
    R2,Small Range/Renko
    """

    def __init__(self, strategy):

        super(RenkoPolicy, self).__init__(strategy)

        self.openR1Period = None              # 开仓周期Mode
        self.openR2Period = None              # 开仓周期Mode

        self.entryPrice = EMPTY_FLOAT             # 开仓价格
        self.lastPeriodBasePrice = EMPTY_FLOAT    # 上一个周期内的最近高价/低价(看R2 Rsi的高点和低点）
        self.entryTime = None

        self.riskLevel = EMPTY_INT                # 风险评分,1、低；2、中；3、高

        self.cancelInNextBar = False

        self.addPos = False                       # 是否加仓
        self.addPosOnPips = EMPTY_INT             # 价格超过开仓价多少点时加仓
        self.addPosOnRtnPercent = EMPTY_FLOAT     # 价格回撤比例时加仓
        self.addPosOnRsiRtnWithPips = EMPTY_INT   # 价格超过开仓价，并且低位RSI反转（多：RSI低位折返，空：RSI高位折返）
        self.addPosOnKdjRtnWithPips = EMPTY_INT   # 价格超过开仓价，并且低位Kdj反转（多：Kdj低位折返，空：Kdj高位折返）

        self.exitOnStopPrice = EMPTY_FLOAT        # 固定止损价格。 这个规则最优先匹配，作为最大亏损线。
        self.exitOnWinPrice = EMPTY_FLOAT         # 固定止盈价格。

        self.exitOnProtectedPrice = EMPTY_FLOAT   # 保本价格。
        self.exitOnLastRtnPips = EMPTY_INT        # 盈利后，最后开仓价的回调点数。 使用时，pips* minDiff
        self.exitOnTopRtnPips = EMPTY_INT         # 盈利后，最高盈利的回撤点数。 使用时，pips * minDiff

        self.exitOnR2RsiRtn = False               # First RSI Return
        self.exitOnR2EmaCrossed = False           # EMA(inputEma1Len) Cross Above、 Under
        self.exitOnR2KamaCrossed = False          # AMA(inputAma1Len) Cross Above、 Under
        self.exitOnR2KamaRtn = False              # 盈利后，Kama[-1] vs Kama[-2]

        self.exitOnR1RsiRtn = False               # First RSI Return
        self.exitOnR1EmaCrossed = False           # EMA(inputEma1Len) Cross Above、 Under
        self.exitOnR1KamaCrossed = False          # AMA(inputAma1Len) Cross Above、 Under
        self.exitOnR1KamaRtn = False              # 盈利后，Kama[-1] vs Kama[-2]

        self.exitOnR1PeriodChanged = False        # R1 Period Changed, if True,openR1Period != periodMode
        self.exitOnR2PeriodChanged = False        # R2 Period Changed, if True,openR2Period != periodMode

        self.exitOnR1PeriodModes = []    # 可以与exitOnR1PeriodChanged ,指定的立场周期；进入后，激活 exitOnR2RsiRtn

        self.reducePosOnEmaRtn = False

    def set_r1Period(self,r1Period):
        self.openR1Period = r1Period

    def set_r2Period(self,r2Period):
        self.openR2Period = r2Period

class TurtlePolicy(CtaPolicy):
    """海龟策略事务"""

    def __init__(self, strategy):
        super(TurtlePolicy, self).__init__(strategy)

        self.tns_open_price = 0  # 首次开仓价格
        self.last_open_price = 0  # 最后一次加仓价格
        self.stop_price = 0  # 止损价
        self.high_price_in_long = 0  # 多趋势时，最高价
        self.low_price_in_short = 0  # 空趋势时，最低价
        self.last_under_open_price = 0  # 低于首次开仓价的补仓价格
        self.add_pos_count_under_first_price = 0  # 低于首次开仓价的补仓次数
        self.tns_direction = None  # 事务方向 DIRECTION_LONG 向上/ DIRECTION_SHORT向下
        self.tns_count = 0  # 当前事务开启后多少个bar，>0，做多方向，<0，做空方向
        self.max_pos = 0  # 事务中最大仓位
        self.tns_has_opened = False
        self.tns_open_date = ''  # 事务开启的交易日
        self.last_risk_level = 0  # 上一次风控评估的级别

    def toJson(self):
        """
        将数据转换成dict
        :return:
        """
        j = OrderedDict()
        j['create_time'] = self.create_time.strftime(
            '%Y-%m-%d %H:%M:%S') if self.create_time is not None else EMPTY_STRING
        j['save_time'] = self.save_time.strftime('%Y-%m-%d %H:%M:%S') if self.save_time is not None else EMPTY_STRING
        j['tns_open_date'] = self.tns_open_date
        j['tns_open_price'] = self.tns_open_price if self.tns_open_price is not None else 0

        j['last_open_price'] = self.last_open_price if self.last_open_price is not None else 0
        j['stop_price'] = self.stop_price if self.stop_price is not None else 0
        j['high_price_in_long'] = self.high_price_in_long if self.high_price_in_long is not None else 0
        j['low_price_in_short'] = self.low_price_in_short if self.low_price_in_short is not None else 0
        j[
            'add_pos_count_under_first_price'] = self.add_pos_count_under_first_price if self.add_pos_count_under_first_price is not None else 0
        j['last_under_open_price'] = self.last_under_open_price if self.last_under_open_price is not None else 0

        j['max_pos'] = self.max_pos if self.max_pos is not None else 0
        j['tns_direction'] = self.tns_direction if self.tns_direction is not None else EMPTY_STRING
        j['tns_count'] = self.tns_count if self.tns_count is not None else 0

        j['tns_has_opened'] = self.tns_has_opened
        j['last_risk_level'] = self.last_risk_level

        return j

    def fromJson(self, json_data):
        """
        将dict转化为属性
        :param json_data:
        :return:
        """
        if 'create_time' in json_data:
            try:
                self.create_time = datetime.strptime(json_data['create_time'], '%Y-%m-%d %H:%M:%S')
            except Exception as ex:
                self.writeCtaError(u'解释create_time异常:{}'.format(str(ex)))
                self.create_time = datetime.now()

        if 'save_time' in json_data:
            try:
                self.save_time = datetime.strptime(json_data['save_time'], '%Y-%m-%d %H:%M:%S')
            except Exception as ex:
                self.writeCtaError(u'解释save_time异常:{}'.format(str(ex)))
                self.save_time = datetime.now()

        if 'tns_open_price' in json_data:
            try:
                self.tns_open_price = json_data['tns_open_price']
            except Exception as ex:
                self.writeCtaError(u'解释tns_open_price异常:{}'.format(str(ex)))
                self.tns_open_price = 0

        if 'tns_open_date' in json_data:
            try:
                self.tns_open_date = json_data['tns_open_date']
            except Exception as ex:
                self.writeCtaError(u'解释tns_open_date异常:{}'.format(str(ex)))
                self.tns_open_date = ''

        if 'last_under_open_price' in json_data:
            try:
                self.last_under_open_price = json_data['last_under_open_price']
            except Exception as ex:
                self.writeCtaError(u'解释last_under_open_price异常:{}'.format(str(ex)))
                self.last_under_open_price = 0

        if 'last_open_price' in json_data:
            try:
                self.last_open_price = json_data['last_open_price']
            except Exception as ex:
                self.writeCtaError(u'解释last_open_price异常:{}'.format(str(ex)))
                self.last_open_price = 0

        if 'stop_price' in json_data:
            try:
                self.stop_price = json_data['stop_price']
            except Exception as ex:
                self.writeCtaError(u'解释stop_price异常:{}'.format(str(ex)))
                self.stop_price = 0

        if 'high_price_in_long' in json_data:
            try:
                self.high_price_in_long = json_data['high_price_in_long']
            except Exception as ex:
                self.writeCtaError(u'解释high_price_in_long异常:{}'.format(str(ex)))
                self.high_price_in_long = 0

        if 'low_price_in_short' in json_data:
            try:
                self.low_price_in_short = json_data['low_price_in_short']
            except Exception as ex:
                self.writeCtaError(u'解释low_price_in_short异常:{}'.format(str(ex)))
                self.low_price_in_short = 0

        if 'max_pos' in json_data:
            try:
                self.max_pos = json_data['max_pos']
            except Exception as ex:
                self.writeCtaError(u'解释max_pos异常:{}'.format(str(ex)))
                self.max_pos = 0

        if 'add_pos_count_under_first_price' in json_data:
            try:
                self.add_pos_count_under_first_price = json_data['add_pos_count_under_first_price']
            except Exception as ex:
                self.writeCtaError(u'解释add_pos_count_under_first_price异常:{}'.format(str(ex)))
                self.add_pos_count_under_first_price = 0

        if 'tns_direction' in json_data:
            try:
                self.tns_direction = json_data['tns_direction']
            except Exception as ex:
                self.writeCtaError(u'解释tns_direction异常:{}'.format(str(ex)))
                self.tns_direction = EMPTY_STRING

        if 'tns_count' in json_data:
            try:
                self.tns_count = json_data['tns_count']
            except Exception as ex:
                self.writeCtaError(u'解释tns_count异常:{}'.format(str(ex)))
                self.tns_count = EMPTY_STRING

        if 'tns_has_opened' in json_data:
            try:
                self.tns_has_opened = json_data['tns_has_opened']
            except Exception as ex:
                self.writeCtaError(u'解释tns_has_opened异常:{}'.format(str(ex)))
                self.tns_has_opened = False

        if 'last_risk_level' in json_data:
            try:
                self.last_risk_level = json_data['last_risk_level']
            except Exception as ex:
                self.writeCtaError(u'解释last_risk_level异常:{}'.format(str(ex)))
                self.last_risk_level = 0


    def clean(self):
        """
        清空数据
        :return:
        """
        self.writeCtaLog(u'清空policy数据')
        self.tns_open_price = 0
        self.tns_open_date = ''
        self.last_open_price = 0
        self.last_under_open_price = 0
        self.stop_price = 0
        self.high_price_in_long = 0
        self.low_price_in_short = 0
        self.max_pos = 0
        self.add_pos_count_under_first_price = 0
        self.tns_direction = None
        self.tns_has_opened = False
        self.last_risk_level = 0
        self.tns_count = 0

class TrendPolicy(CtaPolicy):
    """
    趋势策略规则
    每次趋势交易，看作一个事务
    """

    def __init__(self, strategy):
        super(TrendPolicy, self).__init__(strategy)

        self.tns_open_price = 0          # 首次开仓价格
        self.last_open_price = 0         # 最后一次加仓价格
        self.stop_price = 0              # 止损价
        self.high_price_in_long = 0      # 多趋势时，最高价
        self.low_price_in_short = 0      # 空趋势时，最低价
        self.last_under_open_price = 0   # 低于首次开仓价的补仓价格
        self.add_pos_count_under_first_price = 0  # 低于首次开仓价的补仓次数
        self.tns_direction = None        # 日线方向 DIRECTION_LONG 向上/ DIRECTION_SHORT向下
        self.tns_count = 0               # 日线事务，>0，做多方向，<0，做空方向
        self.max_pos = 0                 # 事务中最大仓位
        self.pos_to_add = []             # 开仓/加仓得仓位数量分布列表
        self.pos_reduced = {}            # 减仓记录
        self.last_reduce_price = 0       # 最近一次减仓记录

        self.tns_has_opened = False
        self.tns_open_date = ''          # 事务开启的交易日
        self.last_balance_level = 0      # 上一次平衡的级别
        self.last_risk = EMPTY_STRING          # 上一次risk评估类别
        self.cur_risk = EMPTY_STRING          # 当前risk评估类别

        # 加仓记录
        self.dtosc_add_pos = {}         # DTOSC 加仓

    def toJson(self):
        """
        将数据转换成dict
        :return:
        """
        j = OrderedDict()
        j['create_time'] = self.create_time.strftime('%Y-%m-%d %H:%M:%S') if self.create_time is not None else EMPTY_STRING
        j['save_time'] = self.save_time.strftime('%Y-%m-%d %H:%M:%S') if self.save_time is not None else EMPTY_STRING
        j['tns_open_date'] = self.tns_open_date
        j['tns_open_price'] = self.tns_open_price if self.tns_open_price is not None else 0

        j['last_open_price'] = self.last_open_price if self.last_open_price is not None else 0
        j['stop_price'] = self.stop_price if self.stop_price is not None else 0
        j['high_price_in_long'] = self.high_price_in_long if self.high_price_in_long is not None else 0
        j['low_price_in_short'] = self.low_price_in_short if self.low_price_in_short is not None else 0
        j['add_pos_count_under_first_price'] = self.add_pos_count_under_first_price if self.add_pos_count_under_first_price is not None else 0
        j['last_under_open_price'] = self.last_under_open_price if self.last_under_open_price is not None else 0

        j['max_pos'] = self.max_pos if self.max_pos is not None else 0
        j['tns_direction'] = self.tns_direction if self.tns_direction is not None else EMPTY_STRING
        j['tns_count'] = self.tns_count if self.tns_count is not None else 0
        j['pos_to_add'] = self.pos_to_add
        j['pos_reduced'] = self.pos_reduced
        j['tns_has_opened'] = self.tns_has_opened
        j['last_balance_level'] = self.last_balance_level
        j['last_reduce_price'] = self.last_reduce_price
        j['dtosc_add_pos'] = self.dtosc_add_pos
        return j

    def fromJson(self, json_data):
        """
        将dict转化为属性
        :param json_data:
        :return:
        """
        if 'create_time' in json_data:
            try:
                self.create_time = datetime.strptime(json_data['create_time'], '%Y-%m-%d %H:%M:%S')
            except Exception as ex:
                self.writeCtaError(u'解释create_time异常:{}'.format(str(ex)))
                self.create_time = datetime.now()

        if 'save_time' in json_data:
            try:
                self.save_time = datetime.strptime(json_data['save_time'], '%Y-%m-%d %H:%M:%S')
            except Exception as ex:
                self.writeCtaError(u'解释save_time异常:{}'.format(str(ex)))
                self.save_time = datetime.now()

        if 'tns_open_price' in json_data:
            try:
                self.tns_open_price = json_data['tns_open_price']
            except Exception as ex:
                self.writeCtaError(u'解释tns_open_price异常:{}'.format(str(ex)))
                self.tns_open_price = 0

        if 'tns_open_date' in json_data:
            try:
                self.tns_open_date = json_data['tns_open_date']
            except Exception as ex:
                self.writeCtaError(u'解释tns_open_date异常:{}'.format(str(ex)))
                self.tns_open_date = ''

        if 'last_under_open_price' in json_data:
            try:
                self.last_under_open_price = json_data['last_under_open_price']
            except Exception as ex:
                self.writeCtaError(u'解释last_under_open_price异常:{}'.format(str(ex)))
                self.last_under_open_price = 0

        if 'last_open_price' in json_data:
            try:
                self.last_open_price = json_data['last_open_price']
            except Exception as ex:
                self.writeCtaError(u'解释last_open_price异常:{}'.format(str(ex)))
                self.last_open_price = 0

        if 'last_reduce_price' in json_data:
            try:
                self.last_reduce_price = json_data['last_reduce_price']
            except Exception as ex:
                self.writeCtaError(u'解释last_reduce_price异常:{}'.format(str(ex)))
                self.last_reduce_price = 0

        if 'stop_price' in json_data:
            try:
                self.stop_price = json_data['stop_price']
            except Exception as ex:
                self.writeCtaError(u'解释stop_price异常:{}'.format(str(ex)))
                self.stop_price = 0

        if 'high_price_in_long' in json_data:
            try:
                self.high_price_in_long = json_data['high_price_in_long']
            except Exception as ex:
                self.writeCtaError(u'解释high_price_in_long异常:{}'.format(str(ex)))
                self.high_price_in_long = 0

        if 'low_price_in_short' in json_data:
            try:
                self.low_price_in_short = json_data['low_price_in_short']
            except Exception as ex:
                self.writeCtaError(u'解释low_price_in_short异常:{}'.format(str(ex)))
                self.low_price_in_short = 0

        if 'max_pos' in json_data:
            try:
                self.max_pos = json_data['max_pos']
            except Exception as ex:
                self.writeCtaError(u'解释max_pos异常:{}'.format(str(ex)))
                self.max_pos = 0

        if 'add_pos_count_under_first_price' in json_data:
            try:
                self.add_pos_count_under_first_price = json_data['add_pos_count_under_first_price']
            except Exception as ex:
                self.writeCtaError(u'解释add_pos_count_under_first_price异常:{}'.format(str(ex)))
                self.add_pos_count_under_first_price = 0

        if 'tns_direction' in json_data:
            try:
                self.tns_direction = json_data['tns_direction']
            except Exception as ex:
                self.writeCtaError(u'解释tns_direction异常:{}'.format(str(ex)))
                self.tns_direction = EMPTY_STRING

        if 'tns_count' in json_data:
            try:
                self.tns_count = json_data['tns_count']
            except Exception as ex:
                self.writeCtaError(u'解释tns_count异常:{}'.format(str(ex)))
                self.tns_count = EMPTY_STRING

        if 'pos_to_add' in json_data:
            try:
                self.pos_to_add = json_data['pos_to_add']
            except Exception as ex:
                self.writeCtaError(u'解释pos_to_add异常:{}'.format(str(ex)))
                self.pos_to_add = []

        if 'pos_reduced' in json_data:
            try:
                self.pos_reduced = json_data['pos_reduced']
            except Exception as ex:
                self.writeCtaError(u'解释pos_reduced异常:{}'.format(str(ex)))
                self.pos_reduced = {}

        if 'tns_has_opened' in json_data:
            try:
                self.tns_has_opened = json_data['tns_has_opened']
            except Exception as ex:
                self.writeCtaError(u'解释tns_has_opened异常:{}'.format(str(ex)))
                self.tns_has_opened = False

        if 'last_balance_level' in json_data:
            try:
                self.last_balance_level = json_data['last_balance_level']
            except Exception as ex:
                self.writeCtaError(u'解释last_balance_level异常:{}'.format(str(ex)))
                self.last_balance_level = 0

        if 'dtosc_add_pos' in json_data:
            try:
                self.dtosc_add_pos = json_data['dtosc_add_pos']
            except Exception as ex:
                self.writeCtaError(u'解释dtosc_add_pos异常:{}'.format(str(ex)))
                self.dtosc_add_pos = {}

    def clean(self):
        """
        清空数据
        :return:
        """
        self.writeCtaLog(u'清空policy数据')
        self.tns_open_price = 0
        self.tns_open_date = ''
        self.last_open_price = 0
        self.last_under_open_price = 0
        self.stop_price = 0
        self.high_price_in_long = 0
        self.low_price_in_short = 0
        self.max_pos = 0
        self.add_pos_count_under_first_price = 0
        self.tns_direction = None
        self.pos_to_add = []
        self.pos_reduced = {}
        self.last_reduce_price = 0
        self.tns_has_opened = False
        self.last_balance_level = 0
        self.dtosc_add_pos = {}

    def get_last_reduced_pos(self, reduce_type):
        """
        获取最后得减仓数量
        :param reduce_type:
        :return:
        """
        reduce_list = self.pos_reduced.get(reduce_type,[])
        if len(reduce_list):
            last_pos = reduce_list.pop(-1)
            return last_pos
        return 0

    def get_all_reduced_pos(self, reduce_type):
        """
        获取该类型得所有减仓数量
        :param reduce_type:
        :return:
        """
        reduce_list = self.pos_reduced.get(reduce_type, [])
        return sum(reduce_list)

    def add_reduced_pos(self, reduce_type, reduce_volume):
        """
        添加减仓数量
        :param reduce_type:
        :param reduce_volume:
        :return:
        """
        reduce_list = self.pos_reduced.get(reduce_type, [])
        reduce_list.append(reduce_volume)
        self.pos_reduced[reduce_type] = reduce_list

    def calculatePosToAdd(self, total_pos, add_count):
        """
        计算可供加仓得仓位
        仓位 M%
        加仓次数限定为：N次（N不超过16次）
        则平均每次加仓手数为M%/N
        那么第一次加仓手数为M%/N*(1+(N/2)/10) 
        第二次加仓手数为M%/N*(1+(N/2-1)/10)
        ……
        第N/2次加仓手数为M%/N*1.1
        第N/2+1次加仓手数为M%/N*0.9
        ……
        第N次加仓手数为M%/N*(1-(N/2)/10)
        :param direction:
        :return:
        """
        max_pos = total_pos

        if len(self.pos_to_add) > 0:
            self.writeCtaLog(u'加仓参考清单已存在,不重新分配：{}'.format(self.pos_to_add))
            return

        avg_pos = max_pos / add_count

        for i in range(0, add_count):
            if max_pos <= 0:
                self.writeCtaLog(u'分配完毕')
                break
            add_pos = avg_pos * (1+(add_count/2-i)/10)
            add_pos = int(add_pos) if add_pos >= 1 else 1
            if max_pos <= add_pos:
                add_pos = max_pos
                max_pos = 0
            else:
                max_pos -= add_pos

            self.pos_to_add.append(add_pos)

        if max_pos > 0:
            self.pos_to_add.append(max_pos)

        self.writeCtaLog(u'总数量{},计划:{}'.format(total_pos,self.pos_to_add))

    def getPosToAdd(self, max_pos):
        if len(self.pos_to_add) == 0:
            if max_pos > self.max_pos:
                self.writeCtaLog(u'最大允许仓位{}>现最大加仓{}'.format(max_pos,self.max_pos))
                self.pos_to_add.append(max_pos - self.max_pos)
                return max_pos - self.max_pos
            else:
                self.writeCtaError(u'没有仓位可加')
                return 0
        else:
            return self.pos_to_add[0]

    def removePosToAdd(self, remove_pos):

        if len(self.pos_to_add) == 0:
            self.writeCtaError(u'可加仓清单列表为空，不能删除')
            return

        pos = self.pos_to_add.pop(0)
        if pos > remove_pos:
            self.writeCtaLog(u'不全移除，剩余：{}补充到最后'.format(pos-remove_pos))
            self.pos_to_add.append(pos - remove_pos)
        else:
            self.writeCtaLog(u'移除:{},剩余:{}'.format(pos,self.pos_to_add))


