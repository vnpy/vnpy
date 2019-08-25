# encoding: UTF-8

# 从tdx下载股票数据.
# 收盘后的数据基本正确, 但盘中实时拿数据时:
# 1. 1Min的Bar可能不是最新的, 会缺几分钟.
# 2. 当周期>1Min时, 最后一根Bar可能不是完整的, 强制修改后
#    - 5min修改后freq基本正确
#    - 1day在VNPY合成时不关心已经收到多少Bar, 所以影响也不大
#    - 但其它分钟周期因为不好精确到每个品种, 修改后的freq可能有错
#   https://rainx.gitbooks.io/pytdx/content/pytdx_hq.html
# 华富资产

from datetime import datetime, timezone, timedelta, time
import sys
import requests
import execjs
import traceback
from vnpy.trader.app.ctaStrategy.ctaBase import CtaBarData
from pytdx.hq import TdxHq_API
from pytdx.params import TDXParams
from vnpy.trader.vtFunction import getJsonPath
from vnpy.trader.vtGlobal import globalSetting
from vnpy.trader.vtObject import VtErrorData
import json
import pandas as pd

IP_LIST = [{'ip': '112.74.214.43', 'port': 7709},
           {'ip': '59.175.238.38', 'port': 7709},
           {'ip': '124.74.236.94', 'port': 7709},
           {'ip': '218.80.248.229', 'port': 7709},
           {'ip': '124.74.236.94', 'port': 7709},
           {'ip': '58.246.109.27', 'port': 7709},
            {'ip': '101.227.73.20', 'port': 7709}
           ]

# 通达信 K 线种类
# 0 -   5 分钟K 线
# 1 -   15 分钟K 线
# 2 -   30 分钟K 线
# 3 -   1 小时K 线
# 4 -   日K 线
# 5 -   周K 线
# 6 -   月K 线
# 7 -   1 分钟
# 8 -   1 分钟K 线
# 9 -   日K 线
# 10 -  季K 线
# 11 -  年K 线

PERIOD_MAPPING = {}
PERIOD_MAPPING['1min']   = 8
PERIOD_MAPPING['5min']   = 0
PERIOD_MAPPING['15min']  = 1
PERIOD_MAPPING['30min']  = 2
PERIOD_MAPPING['1hour']  = 3
PERIOD_MAPPING['1day']   = 4


# 每个周期包含多少分钟
NUM_MINUTE_MAPPING = {}
NUM_MINUTE_MAPPING['1min']   = 1
NUM_MINUTE_MAPPING['5min']   = 5
NUM_MINUTE_MAPPING['15min']  = 15
NUM_MINUTE_MAPPING['30min']  = 30
NUM_MINUTE_MAPPING['1hour']  = 60
NUM_MINUTE_MAPPING['1day']   = 60*5.5       # 股票，收盘时间是15：00，开盘是9：30

# 常量
QSIZE = 800

class TdxData(object):
    best_ip = None
    symbol_exchange_dict = {}  # tdx合约与vn交易所的字典
    symbol_market_dict = {}  # tdx合约与tdx市场的字典

    # ----------------------------------------------------------------------
    def __init__(self, strategy):
        """
        构造函数
        :param strategy: 上层策略，主要用与使用strategy.writeCtaLog（）
        """
        self.api = None
        self.connection_status = False  # 连接状态

        self.strategy = strategy

        self.connect()

    def connect(self):
        """
        连接API
        :return:
        """

        # 创建api连接对象实例
        try:
            if self.api is None or self.connection_status == False:
                self.strategy.writeCtaLog(u'开始连接通达信股票行情服务器')
                self.api = TdxHq_API(heartbeat=True, auto_retry=True, raise_exception=True)

                # 选取最佳服务器
                if TdxData.best_ip is None:
                    from pytdx.util.best_ip import select_best_ip
                    TdxData.best_ip = select_best_ip()

                self.api.connect(self.best_ip, 7709)
                self.strategy.writeCtaLog(u'创建tdx连接, IP: {}/{}'.format(self.best_ip, 7709))
                TdxData.connection_status = True

        except Exception as ex:
            self.strategy.writeCtaLog(u'连接服务器tdx异常:{},{}'.format(str(ex), traceback.format_exc()))
            return

    def disconnect(self):
        if self.api is not None:
            self.api= None

    # ----------------------------------------------------------------------
    def get_bars(self, symbol, period, callback, bar_is_completed=False, bar_freq=1, start_dt=None):
        """
        返回k线数据
        symbol：股票 000001.XG
        period: 周期: 1min,5min,15min,30min,1hour,1day,
        """
        if self.api is None:
            self.connect()

        def __select_market_code(code):
            code = str(code)
            if code[0] in ['5', '6', '9'] or code[:3] in ["009", "126", "110", "201", "202", "203", "204"]:
                return 1
            return 0
            # 新版一劳永逸偷懒写法zzz
        if '.' in symbol:
            tdx_code,market_str = symbol.split('.')
            market_code = 1 if market_str.upper()== 'XSHG' else 0
            self.symbol_exchange_dict.update({tdx_code:symbol})  # tdx合约与vn交易所的字典
            self.symbol_market_dict.update({tdx_code:market_code})  # tdx合约与tdx市场的字典
        else:
            market_code = __select_market_code(symbol)
            tdx_code = symbol
            self.symbol_exchange_dict.update({symbol: symbol})  # tdx合约与vn交易所的字典
            self.symbol_market_dict.update({symbol: market_code})  # tdx合约与tdx市场的字典

        # https://github.com/rainx/pytdx/issues/33
        # 0 - 深圳， 1 - 上海

        ret_bars = []

        if period not in PERIOD_MAPPING.keys():
            self.strategy.writeCtaError(u'{} 周期{}不在下载清单中: {}'.format(datetime.now(), period, list(PERIOD_MAPPING.keys())))
            # print(u'{} 周期{}不在下载清单中: {}'.format(datetime.now(), period, list(PERIOD_MAPPING.keys())))
            return False,ret_bars

        if self.api is None:
            return False,ret_bars

        tdx_period = PERIOD_MAPPING.get(period)

        if start_dt is None:
            self.strategy.writeCtaLog(u'没有设置开始时间，缺省为10天前')
            qry_start_date = datetime.now() - timedelta(days=10)
            start_dt = qry_start_date
        else:
            qry_start_date = start_dt
        end_date = datetime.now()
        if qry_start_date > end_date:
            qry_start_date = end_date

        self.strategy.writeCtaLog('{}开始下载tdx股票:{} {}数据, {} to {}.'.format(datetime.now(), tdx_code, tdx_period, qry_start_date, end_date))

        try:
            _start_date = end_date
            _bars = []
            _pos = 0
            while _start_date > qry_start_date:
                _res = self.api.get_security_bars(category=PERIOD_MAPPING[period],
                    market=market_code,
                    code=tdx_code,
                    start=_pos,
                    count=QSIZE)
                if _res is not None:
                    _bars = _res + _bars
                _pos += QSIZE
                if _res is not None and len(_res) > 0:
                    _start_date = _res[0]['datetime']
                    _start_date = datetime.strptime(_start_date, '%Y-%m-%d %H:%M')
                    self.strategy.writeCtaLog(u'分段取数据开始:{}'.format(_start_date))
                else:
                    break
            if len(_bars) == 0:
                self.strategy.writeCtaError('{} Handling {}, len1={}..., continue'.format(
                    str(datetime.now()), tdx_code, len(_bars)))
                return False, ret_bars

            current_datetime = datetime.now()
            data = self.api.to_df(_bars)
            data = data.assign(datetime=pd.to_datetime(data['datetime']))
            data = data.assign(ticker=symbol)
            data['symbol'] = symbol
            data = data.drop(
                ['year', 'month', 'day', 'hour', 'minute', 'price',  'ticker'],
                errors='ignore',
                axis=1)
            data = data.rename(
                index=str,
                columns={'amount': 'volume',
                })
            if len(data) == 0:
                print('{} Handling {}, len2={}..., continue'.format(
                    str(datetime.now()), tdx_code, len(data)))
                return False, ret_bars

            # 通达信是以bar的结束时间标记的，vnpy是以bar开始时间标记的,所以要扣减bar本身的分钟数
            data['datetime'] = data['datetime'].apply(lambda x:x-timedelta(minutes=NUM_MINUTE_MAPPING.get(period,1)))
            data['trading_date'] = data['datetime'].apply(lambda x: (x.strftime('%Y-%m-%d')))
            data['date'] = data['datetime'].apply(lambda x: (x.strftime('%Y-%m-%d')))
            data['time'] = data['datetime'].apply(lambda x: (x.strftime('%H:%M:%S')))
            data = data.set_index('datetime', drop=False)

            for index, row in data.iterrows():
                add_bar = CtaBarData()
                try:
                    add_bar.vtSymbol = symbol
                    add_bar.symbol = symbol
                    add_bar.datetime = index
                    add_bar.date = row['date']
                    add_bar.time = row['time']
                    add_bar.tradingDay = row['trading_date']
                    add_bar.open = float(row['open'])
                    add_bar.high = float(row['high'])
                    add_bar.low = float(row['low'])
                    add_bar.close = float(row['close'])
                    add_bar.volume = float(row['volume'])
                except Exception as ex:
                    self.strategy.writeCtaError('error when convert bar:{},ex:{},t:{}'.format(row, str(ex), traceback.format_exc()))
                    # print('error when convert bar:{},ex:{},t:{}'.format(row, str(ex), traceback.format_exc()))
                    return False

                if start_dt is not None and index < start_dt:
                    continue
                ret_bars.append(add_bar)

                if callback is not None:
                    freq = bar_freq
                    bar_is_completed = True
                    if period != '1min' and index == data['datetime'][-1]:
                        # 最后一个bar，可能是不完整的，强制修改
                        # - 5min修改后freq基本正确
                        # - 1day在VNPY合成时不关心已经收到多少Bar, 所以影响也不大
                        # - 但其它分钟周期因为不好精确到每个品种, 修改后的freq可能有错
                        if index > current_datetime:
                            bar_is_completed = False
                            # 根据秒数算的话，要+1，例如13:31,freq=31，第31根bar
                            freq = NUM_MINUTE_MAPPING[period] - int((index - current_datetime).total_seconds() / 60)
                    callback(add_bar, bar_is_completed, freq)

            return True,ret_bars
        except Exception as ex:
            self.strategy.writeCtaError('exception in get:{},{},{}'.format(tdx_code,str(ex), traceback.format_exc()))
            # print('exception in get:{},{},{}'.format(tdx_symbol,str(ex), traceback.format_exc()))
            self.strategy.writeCtaLog(u'重置连接')
            TdxData.api = None
            self.connect()
            return False,ret_bars

if __name__ == "__main__":
    class T(object):

        def writeCtaError(self,content):
            print(content,file=sys.stderr)

        def writeCtaLog(self,content):
            print(content)

        def display_bar(self,bar, bar_is_completed=True, freq=1):
            print(u'{} {}'.format(bar.vtSymbol,bar.datetime))

    t1 = T()
    t2 = T()
    # 创建API对象
    api_01 = TdxData(t1)

    # 获取历史分钟线
    api_01.get_bars('002024', period='1hour', callback=t1.display_bar)
    # api.get_bars(symbol, period='5min', callback=display_bar)
    # api.get_bars(symbol, period='1day', callback=display_bar)
    api_02 = TdxData(t2)
    api_02.get_bars('601390', period='1day', callback=t1.display_bar)