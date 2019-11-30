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

import sys
import os
import pickle
import bz2
import traceback
from datetime import datetime, timedelta
from logging import ERROR, INFO
from pytdx.hq import TdxHq_API
from pandas import to_datetime

from vnpy.trader.object import BarData
from vnpy.data.tdx.tdx_common import PERIOD_MAPPING, get_tdx_market_code

# 每个周期包含多少分钟
NUM_MINUTE_MAPPING = {}
NUM_MINUTE_MAPPING['1min'] = 1
NUM_MINUTE_MAPPING['5min'] = 5
NUM_MINUTE_MAPPING['15min'] = 15
NUM_MINUTE_MAPPING['30min'] = 30
NUM_MINUTE_MAPPING['1hour'] = 60
NUM_MINUTE_MAPPING['1day'] = 60 * 5.5       # 股票，收盘时间是15：00，开盘是9：30

# 常量
QSIZE = 800


class TdxStockData(object):
    best_ip = None
    symbol_exchange_dict = {}  # tdx合约与vn交易所的字典
    symbol_market_dict = {}  # tdx合约与tdx市场的字典

    # ----------------------------------------------------------------------
    def __init__(self, strategy=None):
        """
        构造函数
        :param strategy: 上层策略，主要用与使用write_log（）
        """
        self.api = None

        self.connection_status = False  # 连接状态

        self.strategy = strategy

        self.connect()

    def write_log(self, content):
        if self.strategy:
            self.strategy.write_log(content)
        else:
            print(content)

    def write_error(self, content):
        if self.strategy:
            self.strategy.write_log(content, level=ERROR)
        else:
            print(content, file=sys.stderr)

    def connect(self):
        """
        连接API
        :return:
        """
        # 创建api连接对象实例
        try:
            if self.api is None or not self.connection_status:
                self.write_log(u'开始连接通达信股票行情服务器')
                self.api = TdxHq_API(heartbeat=True, auto_retry=True, raise_exception=True)

                # 选取最佳服务器
                if TdxStockData.best_ip is None:
                    from pytdx.util.best_ip import select_best_ip
                    TdxStockData.best_ip = select_best_ip()

                self.api.connect(self.best_ip.get('ip'), self.best_ip.get('port'))
                self.write_log(f'创建tdx连接, : {self.best_ip}')
                TdxStockData.connection_status = True

        except Exception as ex:
            self.write_log(u'连接服务器tdx异常:{},{}'.format(str(ex), traceback.format_exc()))
            return

    def disconnect(self):
        if self.api is not None:
            self.api = None

    # ----------------------------------------------------------------------
    def get_bars(self, symbol, period, callback, bar_is_completed=False, bar_freq=1, start_dt=None):
        """
        返回k线数据
        symbol：股票 000001.XG
        period: 周期: 1min,5min,15min,30min,1hour,1day,
        """
        if self.api is None:
            self.connect()

        # 新版一劳永逸偷懒写法zzz
        if '.' in symbol:
            tdx_code, market_str = symbol.split('.')
            market_code = 1 if market_str.upper() == 'XSHG' else 0
            self.symbol_exchange_dict.update({tdx_code: symbol})  # tdx合约与vn交易所的字典
            self.symbol_market_dict.update({tdx_code: market_code})  # tdx合约与tdx市场的字典
        else:
            market_code = get_tdx_market_code(symbol)
            tdx_code = symbol
            self.symbol_exchange_dict.update({symbol: symbol})  # tdx合约与vn交易所的字典
            self.symbol_market_dict.update({symbol: market_code})  # tdx合约与tdx市场的字典

        # https://github.com/rainx/pytdx/issues/33
        # 0 - 深圳， 1 - 上海

        ret_bars = []

        if period not in PERIOD_MAPPING.keys():
            self.write_error(u'{} 周期{}不在下载清单中: {}'
                             .format(datetime.now(), period, list(PERIOD_MAPPING.keys())))
            # print(u'{} 周期{}不在下载清单中: {}'.format(datetime.now(), period, list(PERIOD_MAPPING.keys())))
            return False, ret_bars

        if self.api is None:
            return False, ret_bars

        tdx_period = PERIOD_MAPPING.get(period)

        if start_dt is None:
            self.write_log(u'没有设置开始时间，缺省为10天前')
            qry_start_date = datetime.now() - timedelta(days=10)
            start_dt = qry_start_date
        else:
            qry_start_date = start_dt
        end_date = datetime.now()
        if qry_start_date > end_date:
            qry_start_date = end_date

        self.write_log('{}开始下载tdx股票:{} {}数据, {} to {}.'
                       .format(datetime.now(), tdx_code, tdx_period, qry_start_date, end_date))

        try:
            _start_date = end_date
            _bars = []
            _pos = 0
            while _start_date > qry_start_date:
                _res = self.api.get_security_bars(
                    category=PERIOD_MAPPING[period],
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
                    self.write_log(u'分段取数据开始:{}'.format(_start_date))
                else:
                    break
            if len(_bars) == 0:
                self.write_error('{} Handling {}, len1={}..., continue'.format(
                    str(datetime.now()), tdx_code, len(_bars)))
                return False, ret_bars

            current_datetime = datetime.now()
            data = self.api.to_df(_bars)
            data = data.assign(datetime=to_datetime(data['datetime']))
            data = data.assign(ticker=symbol)
            data['symbol'] = symbol
            data = data.drop(
                ['year', 'month', 'day', 'hour', 'minute', 'price', 'ticker'],
                errors='ignore',
                axis=1)
            data = data.rename(
                index=str,
                columns={'amount': 'volume'})
            if len(data) == 0:
                print('{} Handling {}, len2={}..., continue'.format(
                    str(datetime.now()), tdx_code, len(data)))
                return False, ret_bars

            # 通达信是以bar的结束时间标记的，vnpy是以bar开始时间标记的,所以要扣减bar本身的分钟数
            data['datetime'] = data['datetime'].apply(lambda x: x - timedelta(minutes=NUM_MINUTE_MAPPING.get(period, 1)))
            data['trading_date'] = data['datetime'].apply(lambda x: (x.strftime('%Y-%m-%d')))
            data['date'] = data['datetime'].apply(lambda x: (x.strftime('%Y-%m-%d')))
            data['time'] = data['datetime'].apply(lambda x: (x.strftime('%H:%M:%S')))
            data = data.set_index('datetime', drop=False)

            for index, row in data.iterrows():
                add_bar = BarData()
                try:
                    add_bar.symbol = symbol
                    add_bar.datetime = index
                    add_bar.date = row['date']
                    add_bar.time = row['time']
                    add_bar.trading_date = row['trading_date']
                    add_bar.open = float(row['open'])
                    add_bar.high = float(row['high'])
                    add_bar.low = float(row['low'])
                    add_bar.close = float(row['close'])
                    add_bar.volume = float(row['volume'])
                except Exception as ex:
                    self.write_error('error when convert bar:{},ex:{},t:{}'
                                     .format(row, str(ex), traceback.format_exc()))
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

            return True, ret_bars
        except Exception as ex:
            self.write_error('exception in get:{},{},{}'.format(tdx_code, str(ex), traceback.format_exc()))
            # print('exception in get:{},{},{}'.format(tdx_symbol,str(ex), traceback.format_exc()))
            self.write_log(u'重置连接')
            TdxStockData.api = None
            self.connect()
            return False, ret_bars

    def save_cache(self, cache_folder, cache_symbol, cache_date, data_list):
        """保存文件到缓存"""

        os.makedirs(cache_folder, exist_ok=True)

        if not os.path.exists(cache_folder):
            self.write_error('缓存目录不存在:{},不能保存'.format(cache_folder))
            return
        cache_folder_year_month = os.path.join(cache_folder, cache_date[:6])
        os.makedirs(cache_folder_year_month, exist_ok=True)

        save_file = os.path.join(cache_folder_year_month, '{}_{}.pkb2'.format(cache_symbol, cache_date))
        with bz2.BZ2File(save_file, 'wb') as f:
            pickle.dump(data_list, f)
            self.write_log(u'缓存成功:{}'.format(save_file))

    def load_cache(self, cache_folder, cache_symbol, cache_date):
        """加载缓存数据"""
        if not os.path.exists(cache_folder):
            self.write_error('缓存目录:{}不存在,不能读取'.format(cache_folder))
            return None
        cache_folder_year_month = os.path.join(cache_folder, cache_date[:6])
        if not os.path.exists(cache_folder_year_month):
            self.write_error('缓存目录:{}不存在,不能读取'.format(cache_folder_year_month))
            return None

        cache_file = os.path.join(cache_folder_year_month, '{}_{}.pkb2'.format(cache_symbol, cache_date))
        if not os.path.isfile(cache_file):
            self.write_error('缓存文件:{}不存在,不能读取'.format(cache_file))
            return None
        with bz2.BZ2File(cache_file, 'rb') as f:
            data = pickle.load(f)
            return data

        return None

    def get_history_transaction_data(self, symbol, date, cache_folder=None):
        """获取当某一交易日的历史成交记录"""
        ret_datas = []
        if isinstance(date, datetime):
            date = date.strftime('%Y%m%d')
        if isinstance(date, str):
            date = int(date)

        cache_symbol = symbol
        cache_date = str(date)

        max_data_size = sys.maxsize
        # symbol.exchange => tdx_code market_code
        if '.' in symbol:
            tdx_code, market_str = symbol.split('.')
            market_code = 1 if market_str.upper() == 'XSHG' else 0
            self.symbol_exchange_dict.update({tdx_code: symbol})  # tdx合约与vn交易所的字典
            self.symbol_market_dict.update({tdx_code: market_code})  # tdx合约与tdx市场的字典
        else:
            market_code = get_tdx_market_code(symbol)
            tdx_code = symbol
            self.symbol_exchange_dict.update({symbol: symbol})  # tdx合约与vn交易所的字典
            self.symbol_market_dict.update({symbol: market_code})  # tdx合约与tdx市场的字典

        q_size = QSIZE * 5
        # 每秒 2个， 10小时
        max_data_size = 1000000
        # 优先从缓存加载
        if cache_folder:
            buffer_data = self.load_cache(cache_folder, cache_symbol, cache_date)
            if buffer_data:
                return True, buffer_data

        self.write_log(u'开始下载{} 历史{}分笔数据'.format(date, symbol))

        is_today = False
        if date == int(datetime.now().strftime('%Y%m%d')):
            is_today = True

        try:
            _datas = []
            _pos = 0

            while(True):
                if is_today:
                    _res = self.api.get_transaction_data(
                        market=self.symbol_market_dict[symbol],
                        code=symbol,
                        start=_pos,
                        count=q_size)
                else:
                    _res = self.api.get_history_transaction_data(
                        market=self.symbol_market_dict[symbol],
                        date=date,
                        code=symbol,
                        start=_pos,
                        count=q_size)
                last_dt = None
                if _res is not None:
                    _datas = _res + _datas
                _pos += min(q_size, len(_res))

                if _res is not None and len(_res) > 0:
                    self.write_log(u'分段取{}分笔数据:{} ~{}, {}条,累计:{}条'
                                   .format(date, _res[0]['time'], _res[-1]['time'], len(_res), _pos))
                else:
                    break

                if len(_datas) >= max_data_size:
                    break

            if len(_datas) == 0:
                self.write_error(u'{}分笔成交数据获取为空'.format(date))
                return False, _datas

            for d in _datas:
                dt = datetime.strptime(str(date) + ' ' + d.get('time'), '%Y%m%d %H:%M')
                if last_dt is None or last_dt < dt:
                    last_dt = dt
                else:
                    if last_dt < dt + timedelta(seconds=59):
                        last_dt = last_dt + timedelta(seconds=1)
                d.update({'datetime': last_dt})
                d.update({'volume': d.pop('vol', 0)})
                d.update({'trading_date': last_dt.strftime('%Y-%m-%d')})

            _datas = sorted(_datas, key=lambda s: s['datetime'])

            # 缓存文件
            if cache_folder and not is_today:
                self.save_cache(cache_folder, cache_symbol, cache_date, _datas)

            return True, _datas

        except Exception as ex:
            self.write_error('exception in get_transaction_data:{},{},{}'.format(symbol, str(ex), traceback.format_exc()))
            return False, ret_datas


if __name__ == "__main__":
    class T(object):
        def write_log(self, content, level=INFO):
            if level == INFO:
                print(content)
            else:
                print(content, file=sys.stderr)

        def display_bar(self, bar, bar_is_completed=True, freq=1):
            print(u'{} {}'.format(bar.vtSymbol, bar.datetime))

    t1 = T()
    t2 = T()
    # 创建API对象
    api_01 = TdxStockData(t1)

    # 获取历史分钟线
    # api_01.get_bars('002024', period='1hour', callback=t1.display_bar)

    # api.get_bars(symbol, period='5min', callback=display_bar)
    # api.get_bars(symbol, period='1day', callback=display_bar)
    # api_02 = TdxData(t2)
    # api_02.get_bars('601390', period='1day', callback=t1.display_bar)

    # 获取历史分时数据
    # ret,result = api_01.get_history_transaction_data('RB99', '20190909')
    # for r in result[0:10] + result[-10:]:
    #    print(r)

    # 获取历史分时数据
    ret, result = api_01.get_history_transaction_data('600410', '20190925')
    for r in result[0:10] + result[-10:]:
        print(r)
