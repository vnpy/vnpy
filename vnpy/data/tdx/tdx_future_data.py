# encoding: UTF-8

# 从tdx下载期货数据.
# 收盘后的数据基本正确, 但盘中实时拿数据时:
# 1. 1Min的Bar可能不是最新的, 会缺几分钟.
# 2. 当周期>1Min时, 最后一根Bar可能不是完整的, 强制修改后
#    - 5min修改后freq基本正确
#    - 1day在VNPY合成时不关心已经收到多少Bar, 所以影响也不大
#    - 但其它分钟周期因为不好精确到每个品种, 修改后的freq可能有错

import sys
import os
import pickle
import bz2
import copy
import traceback

from datetime import datetime, timedelta, time
from logging import ERROR
from typing import Dict, Callable

from pandas import to_datetime
from pytdx.exhq import TdxExHq_API

from vnpy.trader.constant import Exchange
from vnpy.trader.object import BarData
from vnpy.trader.utility import (
    get_underlying_symbol,
    get_full_symbol,
    get_trading_date,
    get_real_symbol_by_exchange)
from vnpy.data.tdx.tdx_common import (
    lru_cache,
    TDX_FUTURE_HOSTS,
    PERIOD_MAPPING,
    get_future_contracts,
    save_future_contracts,
    get_cache_json,
    save_cache_json,
    TDX_FUTURE_CONFIG)

# 每个周期包含多少分钟 (估算值, 没考虑夜盘和10:15的影响)
NUM_MINUTE_MAPPING: Dict[str, int] = {}
NUM_MINUTE_MAPPING['1min'] = 1
NUM_MINUTE_MAPPING['5min'] = 5
NUM_MINUTE_MAPPING['15min'] = 15
NUM_MINUTE_MAPPING['30min'] = 30
NUM_MINUTE_MAPPING['1hour'] = 60
NUM_MINUTE_MAPPING['1day'] = 60 * 24
NUM_MINUTE_MAPPING['1week'] = 60 * 24 * 7
NUM_MINUTE_MAPPING['1month'] = 60 * 24 * 7 * 30

Tdx_Vn_Exchange_Map = {}
Tdx_Vn_Exchange_Map['47'] = Exchange.CFFEX
Tdx_Vn_Exchange_Map['28'] = Exchange.CZCE
Tdx_Vn_Exchange_Map['29'] = Exchange.DCE
Tdx_Vn_Exchange_Map['30'] = Exchange.SHFE

Vn_Tdx_Exchange_Map = {v: k for k, v in Tdx_Vn_Exchange_Map.items()}
# 能源所与上期所，都归纳到 30
Vn_Tdx_Exchange_Map[Exchange.INE] = '30'
INIT_TDX_MARKET_MAP = {
    'URL9': 28, 'WHL9': 28, 'ZCL9': 28, 'AL9': 29, 'BBL9': 29, 'BL9': 29,
    'CL9': 29, 'CSL9': 29, 'EBL9': 29, 'EGL9': 29, 'FBL9': 29, 'IL9': 29,
    'JDL9': 29, 'JL9': 29, 'JML9': 29, 'LL9': 29, 'ML9': 29, 'PL9': 29,
    'PPL9': 29, 'RRL9': 29, 'VL9': 29, 'YL9': 29, 'AGL9': 30, 'ALL9': 30,
    'AUL9': 30, 'BUL9': 30, 'CUL9': 30, 'FUL9': 30, 'HCL9': 30, 'NIL9': 30,
    'NRL9': 30, 'PBL9': 30, 'RBL9': 30, 'RUL9': 30, 'SCL9': 30, 'SNL9': 30,
    'SPL9': 30, 'SSL9': 30, 'WRL9': 30, 'ZNL9': 30, 'APL9': 28, 'CFL9': 28,
    'CJL9': 28, 'CYL9': 28, 'FGL9': 28, 'JRL9': 28, 'LRL9': 28, 'MAL9': 28,
    'OIL9': 28, 'PML9': 28, 'RIL9': 28, 'RML9': 28, 'RSL9': 28, 'SFL9': 28,
    'SML9': 28, 'SRL9': 28, 'TAL9': 28, 'ICL9': 47, 'IFL9': 47, 'IHL9': 47,
    'TFL9': 47, 'TL9': 47, 'TSL9': 47}
# 常量
QSIZE = 500
ALL_MARKET_BEGIN_HOUR = 8
ALL_MARKET_END_HOUR = 16


@lru_cache()
def get_tdx_marketid(symbol):
    """普通合约/指数合约=》tdx合约所在市场id"""
    underlying_symbol = get_underlying_symbol(symbol)
    tdx_index_symbol = underlying_symbol.upper() + 'L9'
    market_id = INIT_TDX_MARKET_MAP.get(tdx_index_symbol, None)
    if market_id is None:
        raise KeyError(f'{tdx_index_symbol}不存在INIT_TDX_MARKET_MAP中')
    return market_id


class TdxFutureData(object):

    # ----------------------------------------------------------------------
    def __init__(self, strategy=None, best_ip={}):
        """
        构造函数
        :param strategy: 上层策略，主要用与使用write_log（）
        """
        self.api = None
        self.connection_status = False  # 连接状态
        self.best_ip = best_ip
        self.symbol_exchange_dict = {}  # tdx合约与vn交易所的字典
        self.symbol_market_dict = copy.copy(INIT_TDX_MARKET_MAP)  # tdx合约与tdx市场的字典
        self.strategy = strategy
        self.future_contracts = get_future_contracts()

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

    def connect(self, is_reconnect=False):
        """
        连接API
        :return:
        """

        # 创建api连接对象实例
        try:
            if self.api is None or not self.connection_status:
                self.write_log(u'开始连接通达信行情服务器')
                self.api = TdxExHq_API(heartbeat=True, auto_retry=True, raise_exception=True)

                # 选取最佳服务器
                if is_reconnect or len(self.best_ip) == 0:
                    self.best_ip = get_cache_json(TDX_FUTURE_CONFIG)
                    last_datetime_str = self.best_ip.get('datetime', None)
                    if last_datetime_str:
                        try:
                            last_datetime = datetime.strptime(last_datetime_str, '%Y-%m-%d %H:%M:%S')
                            if (datetime.now() - last_datetime).total_seconds() > 60 * 60 * 2:
                                self.best_ip = {}
                        except Exception as ex: # noqa
                            self.best_ip = {}
                    else:
                        self.best_ip = {}

                if len(self.best_ip) == 0:
                    self.best_ip = self.select_best_ip()

                self.api.connect(self.best_ip['ip'], self.best_ip['port'])
                # 尝试获取市场合约统计
                c = self.api.get_instrument_count()
                if c < 10:
                    err_msg = u'该服务器IP {}/{}无响应'.format(self.best_ip['ip'], self.best_ip['port'])
                    self.write_error(err_msg)
                else:
                    self.write_log(u'创建tdx连接, IP: {}/{}'.format(self.best_ip['ip'], self.best_ip['port']))
                    # print(u'创建tdx连接, IP: {}/{}'.format(self.best_ip['ip'], self.best_ip['port']))
                    self.connection_status = True
                    # if not is_reconnect:
                    # 更新 symbol_exchange_dict , symbol_market_dict
                    #    self.qryInstrument()
        except Exception as ex:
            self.write_log(u'连接服务器tdx异常:{},{}'.format(str(ex), traceback.format_exc()))
            return

    # ----------------------------------------------------------------------
    def ping(self,
             ip: str,
             port: int = 7709):
        """
        ping行情服务器
        :param ip:
        :param port:
        :param type_:
        :return:
        """
        apix = TdxExHq_API()
        __time1 = datetime.now()
        try:
            with apix.connect(ip, port):
                if apix.get_instrument_count() > 10000:
                    _timestamp = datetime.now() - __time1
                    self.write_log(f'服务器{ip}:{port},耗时:{_timestamp}')
                    return _timestamp
                else:
                    self.write_log(f'该服务器IP {ip}无响应')
                    return timedelta(9, 9, 0)
        except Exception:
            self.write_error(f'tdx ping服务器，异常的响应{ip}')
            return timedelta(9, 9, 0)

    # ----------------------------------------------------------------------
    def select_best_ip(self):
        """
        选择行情服务器
        :return:
        """
        self.write_log(u'选择通达信行情服务器')

        data_future = [self.ping(x['ip'], x['port']) for x in TDX_FUTURE_HOSTS]

        best_future_ip = TDX_FUTURE_HOSTS[data_future.index(min(data_future))]

        self.write_log(u'选取 {}:{}'.format(best_future_ip['ip'], best_future_ip['port']))
        # print(u'选取 {}:{}'.format(best_future_ip['ip'], best_future_ip['port']))
        best_future_ip.update({'datetime': datetime.now().strftime('%Y-%m-%d %H:%M:%S')})
        save_cache_json(best_future_ip, TDX_FUTURE_CONFIG)
        return best_future_ip

    def _get_vn_exchange(self, symbol):
        """获取"""
        underlying_symbol = get_underlying_symbol(symbol).upper()
        info = self.future_contracts.get(underlying_symbol, None)
        if info:
            return Exchange(info.get('exchange'))
        else:
            market_id = get_tdx_marketid(symbol)
            return Tdx_Vn_Exchange_Map.get(str(market_id), Exchange.INE)

    def qry_instrument(self):
        """
        查询/更新合约信息
        :return:
        """

        # 取得所有的合约信息
        num = self.api.get_instrument_count()
        if not isinstance(num, int):
            return

        all_contacts = sum(
            [self.api.get_instrument_info((int(num / 500) - i) * 500, 500) for i in range(int(num / 500) + 1)], [])
        # [{"category":category,"market": int,"code":sting,"name":string,"desc":string},{}]

        # 对所有合约处理，更新字典 指数合约-tdx市场，指数合约-交易所
        for tdx_contract in all_contacts:
            tdx_symbol = tdx_contract.get('code', None)
            if tdx_symbol is None:
                continue
            tdx_market_id = tdx_contract.get('market')
            if str(tdx_market_id) in Tdx_Vn_Exchange_Map:
                self.symbol_exchange_dict.update({tdx_symbol: Tdx_Vn_Exchange_Map.get(str(tdx_market_id))})
                self.symbol_market_dict.update({tdx_symbol: tdx_market_id})

    # ----------------------------------------------------------------------
    def get_bars(self,
                 symbol: str,
                 period: str,
                 callback: Callable = None,
                 bar_freq: int = 1,
                 start_dt: datetime = None,
                 end_dt: datetime = None,
                 return_bar=True):
        """
        返回k线数据
        symbol：合约
        period: 周期: 1min,3min,5min,15min,30min,1day,3day,1hour,2hour,4hour,6hour,12hour
        callback: 逐一bar去驱动回调函数, 只有 return_bar = True时才回调
        bar_freq: 回调时的参数
        start_dt: 取数据的开始时间
        end_dt: 取数据的结束时间
        return_bar: 返回 第二个数据内容，True:BarData, False:dict
        """

        ret_bars = []
        if '.' in symbol:
            symbol = symbol.split('.')[0]
        tdx_symbol = symbol.upper().replace('_', '')
        tdx_symbol = tdx_symbol.replace('99', 'L9')
        underlying_symbol = get_underlying_symbol(symbol).upper()
        tdx_index_symbol = underlying_symbol + 'L9'
        vn_exchange = self._get_vn_exchange(underlying_symbol)

        self.connect()
        if self.api is None:
            return False, ret_bars

        if period not in PERIOD_MAPPING.keys():
            self.write_error(u'{} 周期{}不在下载清单中: {}'.format(datetime.now(), period, list(PERIOD_MAPPING.keys())))
            return False, ret_bars

        tdx_period = PERIOD_MAPPING.get(period)

        if start_dt is None:
            self.write_log(u'没有设置开始时间，缺省为10天前')
            qry_start_date = datetime.now() - timedelta(days=10)
        else:
            qry_start_date = start_dt
        if end_dt is None:
            self.write_log(u'没有设置结束时间，缺省为当日')
            end_date = datetime.combine(datetime.now() + timedelta(days=1), time(ALL_MARKET_END_HOUR, 0))
        else:
            end_date = end_dt
        if qry_start_date > end_date:
            qry_start_date = end_date
        self.write_log('{}开始下载tdx:{} {}数据, {} to {}.'
                       .format(datetime.now(), tdx_symbol, period, qry_start_date, end_date))
        # print('{}开始下载tdx:{} {}数据, {} to {}.'.format(datetime.now(), tdx_symbol, tdx_period, last_date, end_date))

        try:
            _start_date = end_date
            _bars = []
            _pos = 0
            while _start_date > qry_start_date:
                _res = self.api.get_instrument_bars(
                    tdx_period,
                    self.symbol_market_dict.get(tdx_index_symbol, 0),
                    tdx_symbol,
                    _pos,
                    QSIZE)
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
                    str(datetime.now()), tdx_symbol, len(_bars)))
                return False, ret_bars

            current_datetime = datetime.now()
            data = self.api.to_df(_bars)
            data = data.assign(datetime=to_datetime(data['datetime']))
            data = data.assign(ticker=symbol)
            data['instrument_id'] = data['ticker']
            data['symbol'] = symbol
            data = data.drop(
                ['year', 'month', 'day', 'hour', 'minute', 'price', 'amount', 'ticker'],
                errors='ignore',
                axis=1)
            data = data.rename(
                index=str,
                columns={
                    'position': 'open_interest',
                    'trade': 'volume',
                })
            if len(data) == 0:
                print('{} Handling {}, len2={}..., continue'.format(
                    str(datetime.now()), tdx_symbol, len(data)))
                return False, ret_bars

            data['total_turnover'] = data['volume'] * data['close']
            data["limit_down"] = 0
            data["limit_up"] = 999999
            data['trading_day'] = data['datetime']
            data['trading_day'] = data['trading_day'].apply(lambda x: (x.strftime('%Y-%m-%d')))
            monday_ts = data['datetime'].dt.weekday == 0  # 星期一
            night_ts1 = data['datetime'].dt.hour > ALL_MARKET_END_HOUR
            night_ts2 = data['datetime'].dt.hour < ALL_MARKET_BEGIN_HOUR
            data.loc[night_ts1, 'datetime'] -= timedelta(days=1)  # 所有日期的夜盘(21:00~24:00), 减一天
            monday_ts1 = monday_ts & night_ts1  # 星期一的夜盘(21:00~24:00), 再减两天
            data.loc[monday_ts1, 'datetime'] -= timedelta(days=2)
            monday_ts2 = monday_ts & night_ts2  # 星期一的夜盘(00:00~04:00), 再减两天
            data.loc[monday_ts2, 'datetime'] -= timedelta(days=2)
            # data['datetime'] -= timedelta(minutes=1) # 直接给Strategy使用, RiceQuant格式, 不需要减1分钟
            # data['dt_datetime'] = data['datetime']
            data['date'] = data['datetime'].apply(lambda x: (x.strftime('%Y-%m-%d')))
            data['time'] = data['datetime'].apply(lambda x: (x.strftime('%H:%M:%S')))
            # data['datetime'] = data['datetime'].apply(lambda x: float(x.strftime('%Y%m%d%H%M%S')))
            data = data.set_index('datetime', drop=False)
            if return_bar:
                self.write_log('dataframe => [bars]')
                for index, row in data.iterrows():
                    add_bar = BarData(gateway_name='tdx',
                                      symbol=symbol,
                                      exchange=vn_exchange,
                                      datetime=index)
                    try:
                        add_bar.date = row['date']
                        add_bar.time = row['time']
                        add_bar.trading_day = row['trading_day']
                        add_bar.open_price = float(row['open'])
                        add_bar.high_price = float(row['high'])
                        add_bar.low_price = float(row['low'])
                        add_bar.close_price = float(row['close'])
                        add_bar.volume = float(row['volume'])
                        add_bar.openInterest = float(row['open_interest'])
                    except Exception as ex:
                        self.write_error(
                            'error when convert bar:{},ex:{},t:{}'.format(row, str(ex), traceback.format_exc()))
                        # print('error when convert bar:{},ex:{},t:{}'.format(row, str(ex), traceback.format_exc()))
                        return False, ret_bars

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
            else:
                self.write_log('dataframe => [ dict ]')
                ret_bars = list(data.T.to_dict().values())
            return True, ret_bars
        except Exception as ex:
            self.write_error('exception in get:{},{},{}'.format(tdx_symbol, str(ex), traceback.format_exc()))
            # print('exception in get:{},{},{}'.format(tdx_symbol,str(ex), traceback.format_exc()))
            self.write_log(u'重置连接')
            self.api = None
            self.connect(is_reconnect=True)
            return False, ret_bars

    def get_price(self, symbol: str):
        """获取最新价格"""
        tdx_symbol = symbol.upper().replace('_', '')

        short_symbol = get_underlying_symbol(tdx_symbol).upper()
        if tdx_symbol.endswith('99'):
            query_symbol = tdx_symbol.replace('99', 'L9')
        else:
            query_symbol = get_full_symbol(tdx_symbol)

        if query_symbol != tdx_symbol:
            self.write_log('转换合约:{}=>{}'.format(tdx_symbol, query_symbol))

        tdx_index_symbol = short_symbol + 'L9'
        self.connect()
        if self.api is None:
            return 0
        market_id = self.symbol_market_dict.get(tdx_index_symbol, 0)

        _res = self.api.get_instrument_quote(market_id, query_symbol)
        if not isinstance(_res, list):
            return 0
        if len(_res) == 0:
            return 0

        return float(_res[0].get('price', 0))

    def get_99_contracts(self):
        """
        获取指数合约
        :return: dict list
        """
        self.connect()
        result = self.api.get_instrument_quote_list(42, 3, 0, 100)
        return result

    def get_mi_contracts(self):
        """
        获取主力合约
        :return: dict list
        """
        self.connect()
        result = self.api.get_instrument_quote_list(60, 3, 0, 100)
        return result

    def get_contracts(self, exchange):
        self.connect()
        market_id = Vn_Tdx_Exchange_Map.get(exchange, None)
        if market_id is None:
            print(u'市场:{}配置不在Vn_Tdx_Exchange_Map:{}中，不能取市场下所有合约'.format(exchange, Vn_Tdx_Exchange_Map))
            return []

        index = 0
        count = 100
        results = []
        while (True):
            print(u'查询{}下：{}~{}个合约'.format(exchange, index, index + count))
            result = self.api.get_instrument_quote_list(int(market_id), 3, index, count)
            results.extend(result)
            index += count
            if len(result) < count:
                break
        return results

    def get_mi_contracts2(self):
        """ 获取主力合约"""
        self.connect()
        contracts = []
        for exchange in Vn_Tdx_Exchange_Map.keys():
            contracts.extend(self.get_mi_contracts_from_exchange(exchange))

        return contracts

    def get_mi_contracts_from_exchange(self, exchange):
        contracts = self.get_contracts(exchange)

        if len(contracts) == 0:
            print(u'异常，未能获取{}下合约信息'.format(exchange))
            return []

        mi_contracts = []

        short_contract_dict = {}

        for contract in contracts:
            # 排除指数合约
            code = contract.get('code')
            if code[-2:] in ['L9', 'L8', 'L0', 'L1', 'L2', 'L3', '50'] or \
                    (exchange == Exchange.CFFEX and code[-3:] in ['300', '500']):
                continue
            short_symbol = get_underlying_symbol(code).upper()
            contract_list = short_contract_dict.get(short_symbol, [])
            contract_list.append(contract)
            short_contract_dict.update({short_symbol: contract_list})

        for k, v in short_contract_dict.items():
            sorted_list = sorted(v, key=lambda c: c['ZongLiang'])

            mi_contracts.append(sorted_list[-1])

        return mi_contracts

    def get_markets(self):
        """
        获取市场代码
        :return:
        """
        self.connect()
        result = self.api.get_markets()
        return result

    def get_transaction_data(self, symbol):
        """获取当前交易日的历史成交记录"""
        ret_datas = []
        max_data_size = sys.maxsize
        symbol = symbol.upper()
        if '99' in symbol:
            # 查询的是指数合约
            symbol = symbol.replace('99', 'L9')
            tdx_index_symbol = symbol
        else:
            # 查询的是普通合约
            tdx_index_symbol = get_underlying_symbol(symbol).upper() + 'L9'

        self.connect()

        q_size = QSIZE * 5
        # 每秒 2个， 10小时
        max_data_size = 1000000

        self.write_log(u'开始下载{}当日分笔数据'.format(symbol))

        try:
            _datas = []
            _pos = 0

            while True:
                _res = self.api.get_transaction_data(
                    market=self.symbol_market_dict.get(tdx_index_symbol, 0),
                    code=symbol,
                    start=_pos,
                    count=q_size)
                if _res is not None:
                    for d in _res:
                        dt = d.pop('date')
                        # 星期1~星期6
                        if dt.hour >= 20 and 1 < dt.isoweekday() <= 6:
                            dt = dt - timedelta(days=1)
                        elif dt.hour >= 20 and dt.isoweekday() == 1:
                            # 星期一取得20点后数据
                            dt = dt - timedelta(days=3)
                        elif dt.hour < 8 and dt.isoweekday() == 1:
                            # 星期一取得8点前数据
                            dt = dt - timedelta(days=3)
                        elif dt.hour >= 20 and dt.isoweekday() == 7:
                            # 星期天取得20点后数据，肯定是星期五夜盘
                            dt = dt - timedelta(days=2)
                        elif dt.isoweekday() == 7:
                            # 星期日取得其他时间，必然是　星期六凌晨的数据
                            dt = dt - timedelta(days=1)

                        d.update({'datetime': dt})
                        # 接口有bug，返回价格*1000，所以要除以1000
                        d.update({'price': d.get('price', 0) / 1000})
                    _datas = sorted(_res, key=lambda s: s['datetime']) + _datas
                _pos += min(q_size, len(_res))

                if _res is not None and len(_res) > 0:
                    self.write_log(u'分段取分笔数据:{} ~{}, {}条,累计:{}条'
                                   .format(_res[0]['datetime'], _res[-1]['datetime'], len(_res), _pos))
                else:
                    break

                if len(_datas) >= max_data_size:
                    break

            if len(_datas) == 0:
                self.write_error(u'{}分笔成交数据获取为空')

            return True, _datas

        except Exception as ex:
            self.write_error(
                'exception in get_transaction_data:{},{},{}'.format(symbol, str(ex), traceback.format_exc()))
            self.write_error(u'当前异常服务器信息:{}'.format(self.best_ip))
            self.write_log(u'重置连接')
            self.api = None
            self.connect(is_reconnect=True)
            return False, ret_datas

    def save_cache(self, cache_folder, cache_symbol, cache_date, data_list):
        """保存文件到缓存"""

        os.makedirs(cache_folder, exist_ok=True)

        if not os.path.exists(cache_folder):
            self.write_error('缓存目录不存在:{},不能保存'.format(cache_folder))
            return
        cache_folder_year_month = os.path.join(cache_folder, cache_date[:6])
        os.makedirs(cache_folder_year_month, exist_ok=True)

        save_file = os.path.join(cache_folder_year_month, '{}_{}.pkz2'.format(cache_symbol, cache_date))
        try:
            with bz2.BZ2File(save_file, 'wb') as f:
                pickle.dump(data_list, f)
                self.write_log(u'缓存成功:{}'.format(save_file))
        except Exception as ex:
            self.write_error(u'缓存写入异常:{}'.format(str(ex)))

    def load_cache(self, cache_folder, cache_symbol, cache_date):
        """加载缓存数据"""
        if not os.path.exists(cache_folder):
            self.write_error('缓存目录:{}不存在,不能读取'.format(cache_folder))
            return None
        cache_folder_year_month = os.path.join(cache_folder, cache_date[:6])
        if not os.path.exists(cache_folder_year_month):
            self.write_error('缓存目录:{}不存在,不能读取'.format(cache_folder_year_month))
            return None

        cache_file = os.path.join(cache_folder_year_month, '{}_{}.pkz2'.format(cache_symbol, cache_date))
        if not os.path.isfile(cache_file):
            self.write_error('缓存文件:{}不存在,不能读取'.format(cache_file))
            return None

        with bz2.BZ2File(cache_file, 'rb') as f:
            data = pickle.load(f)
            return data

        return None

    def get_history_transaction_data(self,
                                     symbol: str,
                                     trading_date,
                                     cache_folder: str = None):
        """获取当某一交易日的历史成交记录"""
        ret_datas = []
        # trading_date, 转换为数字类型得日期
        if isinstance(trading_date, datetime):
            trading_date = trading_date.strftime('%Y%m%d')
        if isinstance(trading_date, str):
            trading_date = int(trading_date.replace('-', ''))

        self.connect()

        cache_symbol = symbol
        cache_date = str(trading_date)

        max_data_size = sys.maxsize
        symbol = symbol.upper()
        if '99' in symbol:
            # 查询的是指数合约
            symbol = symbol.replace('99', 'L9')
            tdx_index_symbol = symbol
        else:
            # 查询的是普通合约
            tdx_index_symbol = get_underlying_symbol(symbol).upper() + 'L9'
        q_size = QSIZE * 5
        # 每秒 2个， 10小时
        max_data_size = 1000000

        # 优先从缓存加载
        if cache_folder:
            buffer_data = self.load_cache(cache_folder, cache_symbol, cache_date)
            if buffer_data:
                self.write_log(u'使用缓存文件')
                return True, buffer_data

        self.write_log(u'开始下载{} 历史{}分笔数据'.format(trading_date, symbol))
        cur_trading_date = get_trading_date()
        if trading_date == int(cur_trading_date.replace('-', '')):
            return self.get_transaction_data(symbol)
        try:
            _datas = []
            _pos = 0

            while True:
                _res = self.api.get_history_transaction_data(
                    market=self.symbol_market_dict.get(tdx_index_symbol, 0),
                    date=trading_date,
                    code=symbol,
                    start=_pos,
                    count=q_size)
                if _res is not None:
                    for d in _res:
                        dt = d.pop('date')
                        # 星期1~星期6
                        if dt.hour >= 20 and 1 < dt.isoweekday() <= 6:
                            dt = dt - timedelta(days=1)
                            d.update({'datetime': dt})
                        elif dt.hour >= 20 and dt.isoweekday() == 1:
                            # 星期一取得20点后数据
                            dt = dt - timedelta(days=3)
                            d.update({'datetime': dt})
                        elif dt.hour < 8 and dt.isoweekday() == 1:
                            # 星期一取得8点前数据
                            dt = dt - timedelta(days=3)
                            d.update({'datetime': dt})
                        elif dt.hour >= 20 and dt.isoweekday() == 7:
                            # 星期天取得20点后数据，肯定是星期五夜盘
                            dt = dt - timedelta(days=2)
                            d.update({'datetime': dt})
                        elif dt.isoweekday() == 7:
                            # 星期日取得其他时间，必然是　星期六凌晨的数据
                            dt = dt - timedelta(days=1)
                            d.update({'datetime': dt})
                        else:
                            d.update({'datetime': dt})
                        # 接口有bug，返回价格*1000，所以要除以1000
                        d.update({'price': d.get('price', 0) / 1000})
                    _datas = sorted(_res, key=lambda s: s['datetime']) + _datas
                _pos += min(q_size, len(_res))

                if _res is not None and len(_res) > 0:
                    self.write_log(u'分段取分笔数据:{} ~{}, {}条,累计:{}条'
                                   .format(_res[0]['datetime'], _res[-1]['datetime'], len(_res), _pos))
                else:
                    break

                if len(_datas) >= max_data_size:
                    break

            if len(_datas) == 0:
                self.write_error(u'{}分笔成交数据获取为空'.format(trading_date))
                return False, _datas

            # 缓存文件
            if cache_folder:
                self.save_cache(cache_folder, cache_symbol, cache_date, _datas)

            return True, _datas

        except Exception as ex:
            self.write_error('exception in get_transaction_data:{},{},{}'
                             .format(symbol, str(ex), traceback.format_exc()))
            self.write_error(u'当前异常服务器信息:{}'.format(self.best_ip))
            self.write_log(u'重置连接')
            self.api = None
            self.connect(is_reconnect=True)
            return False, ret_datas

    def update_mi_contracts(self):
        # 连接通达信，获取主力合约
        if not self.api:
            self.connect()

        mi_contract_quote_list = self.get_mi_contracts2()

        self.write_log(
            u'一共获取:{}个主力合约:{}'.format(len(mi_contract_quote_list), [c.get('code') for c in mi_contract_quote_list]))
        should_save = False
        # 逐一更新主力合约数据
        for mi_contract in mi_contract_quote_list:
            tdx_market_id = mi_contract.get('market')
            full_symbol = mi_contract.get('code')
            underlying_symbol = get_underlying_symbol(full_symbol).upper()
            if underlying_symbol in ['SC', 'NR']:
                vn_exchange = Exchange.INE
            else:
                vn_exchange = Tdx_Vn_Exchange_Map.get(str(tdx_market_id))
            mi_symbol = get_real_symbol_by_exchange(full_symbol, vn_exchange)

            # 更新登记 短合约：真实主力合约
            self.write_log(
                '{},{},{},{},{}'.format(tdx_market_id, full_symbol, underlying_symbol, mi_symbol, vn_exchange))
            if underlying_symbol in self.future_contracts:
                info = self.future_contracts.get(underlying_symbol)
                if mi_symbol > info.get('mi_symbol'):
                    self.write_log(u'主力合约变化:{} =>{}'.format(info.get('mi_symbol'), mi_symbol))
                    info.update({'mi_symbol': mi_symbol, 'full_symbol': full_symbol})
                    self.future_contracts.update({underlying_symbol: info})
                    should_save = True
            else:
                # 添加到新合约中
                # 这里缺少size和price_tick, margin_rate，当ctp_gateway启动时，会自动补充和修正完毕
                info = {
                    "underlying_symbol": underlying_symbol,
                    "mi_symbol": mi_symbol,
                    "full_symbol": full_symbol,
                    "exchange": vn_exchange.value
                }
                self.write_log(u'新合约:{}, 需要待ctp连接后更新合约的size/price_tick/margin_rate'.format(info))
                self.future_contracts.update({underlying_symbol: info})
                should_save = True

        if should_save:
            save_future_contracts(self.future_contracts)
