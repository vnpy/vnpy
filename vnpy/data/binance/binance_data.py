# encoding: UTF-8

# 从binance下载数据
from datetime import datetime, timezone
import sys
import requests
import execjs
import traceback
from vnpy.trader.app.ctaStrategy.ctaBase import CtaBarData
from vnpy.api.binance.client import Client
from vnpy.trader.vtFunction import getJsonPath
from vnpy.trader.vtGlobal import globalSetting
import json

PERIOD_MAPPING = {}
PERIOD_MAPPING['1min']   = '1m'
PERIOD_MAPPING['3min']   = '3m'
PERIOD_MAPPING['5min']   = '5m'
PERIOD_MAPPING['15min']  = '15m'
PERIOD_MAPPING['30min']  = '30m'
PERIOD_MAPPING['1hour']  = '1h'
PERIOD_MAPPING['2hour']  = '2h'
PERIOD_MAPPING['4hour']  = '4h'
PERIOD_MAPPING['6hour']  = '6h'
PERIOD_MAPPING['8hour']  = '8h'
PERIOD_MAPPING['12hour'] = '12h'
PERIOD_MAPPING['1day']   = '1d'
PERIOD_MAPPING['3day']   = '3d'
PERIOD_MAPPING['1week']  = '1w'
PERIOD_MAPPING['1month'] = '1M'

SYMBOL_LIST = ['ltc_btc', 'eth_btc', 'etc_btc', 'bch_btc', 'btc_usdt', 'eth_usdt', 'ltc_usdt', 'etc_usdt', 'bch_usdt',
              'etc_eth','bt1_btc','bt2_btc','btg_btc','qtum_btc','hsr_btc','neo_btc','gas_btc',
              'qtum_usdt','hsr_usdt','neo_usdt','gas_usdt','bnb_usdt','eos_usdt','xrp_usdt']

from vnpy.api.binance.vnbinance import symbolFromOtherExchangesToBinance
class BinanceData(object):

    # ----------------------------------------------------------------------
    def __init__(self, strategy=None):
        """
        构造函数
        :param strategy: 上层策略，主要用与使用writeLog（）
        """
        self.strategy = strategy
        self.client = Client('', '')

    def writeLog(self,content):
        if self.strategy and hasattr(self.strategy,'writeCtaLog'):
            self.strategy.writeCtaLog(content)
        else:
            print(content)

    def writeError(self,content):
        if self.strategy and hasattr(self.strategy,'writeCtaError'):
            self.strategy.writeCtaError(content)
        else:
            print(content,file=sys.stderr)
            
    def get_bars(self, symbol, period, callback, bar_is_completed=False,bar_freq=1, start_dt=None):
        """
        返回k线数据
        symbol：合约
        period: 周期: 1min,3min,5min,15min,30min,1day,3day,1hour,2hour,4hour,6hour,12hour
        """
        ret_bars = []
        if symbol not in SYMBOL_LIST:
            self.writeError(u'{} 合约{}不在下载清单中'.format(datetime.now(), symbol))
            return False,ret_bars
        if period not in PERIOD_MAPPING:
            self.writeError(u'{} 周期{}不在下载清单中'.format(datetime.now(), period))
            return False,ret_bars
        if self.client is None:
            return False,ret_bars

        binance_symbol = symbol.upper().replace('_' , '')
        #  转换一下
        binance_symbol = symbolFromOtherExchangesToBinance(binance_symbol)

        binance_period = PERIOD_MAPPING.get(period)

        self.writeLog('{}开始下载binance:{} {}数据.'.format(datetime.now(), binance_symbol, binance_period))

        bars = []
        try:
            bars = self.client.get_klines(symbol=binance_symbol, interval=binance_period)
            bar_len = len(bars)
            for i, bar in enumerate(bars):
                add_bar = CtaBarData()
                try:
                    add_bar.vtSymbol = symbol
                    add_bar.symbol = symbol
                    add_bar.datetime = datetime.fromtimestamp(bar[0] / 1000)
                    utcdatetime = datetime.utcfromtimestamp(bar[0] / 1e3)
                    add_bar.date = add_bar.datetime.strftime('%Y-%m-%d')
                    add_bar.time = add_bar.datetime.strftime('%H:%M:%S')
                    # 币安的交易日，是按照utc来计算的
                    add_bar.tradingDay = utcdatetime.strftime('%Y-%m-%d')
                    add_bar.open = float(bar[1])
                    add_bar.high = float(bar[2])
                    add_bar.low = float(bar[3])
                    add_bar.close = float(bar[4])
                    add_bar.volume = float(bar[5])
                    ret_bars.append(add_bar)
                except Exception as ex:
                    self.writeError(
                        'error when convert bar:{},ex:{},t:{}'.format(bar, str(ex), traceback.format_exc()))
                    return False,ret_bars

                if start_dt is not None and bar.datetime < start_dt:
                    continue

                if callback is not None:
                    # 最后一个bar，可能是不完整的，强制修改
                    if i == bar_len -1 and bar_is_completed:
                        # 根据秒数算的话，要+1，例如13:31,freq=31，第31根bar
                        freq = int((datetime.now() - add_bar.datetime).total_seconds() / 60) + 1
                        callback(add_bar, False, freq)
                    else:
                        callback(add_bar, bar_is_completed, bar_freq)

            return True,ret_bars
        except Exception as ex:
            self.writeError('exception in get:{},{},{}'.format(binance_symbol,str(ex), traceback.format_exc()))
            return False,ret_bars

    def download_bars(self, symbol, period, start_dt=None):
        """
        返回k线数据
        symbol：合约
        period: 周期: 1min,3min,5min,15min,30min,1day,3day,1hour,2hour,4hour,6hour,12hour
        """
        ret_bars = []

        if symbol not in SYMBOL_LIST:
            self.writeError(u'{} 合约{}不在下载清单中'.format(datetime.now(), symbol))
            return ret_bars
        if period not in PERIOD_MAPPING:
            self.writeError(u'{} 周期{}不在下载清单中'.format(datetime.now(), period))
            return ret_bars
        if self.client is None:
            return ret_bars

        binance_symbol = symbol.upper().replace('_', '')
        #  转换一下
        binance_symbol = symbolFromOtherExchangesToBinance(binance_symbol)

        binance_period = PERIOD_MAPPING.get(period)

        self.writeLog('{}开始下载binance:{} {}数据.'.format(datetime.now(), binance_symbol, binance_period))

        if isinstance(start_dt,datetime):
            start_timestamp = int(start_dt.timestamp()*1e3)
        else:
            start_timestamp = None
        try:
            bars = []
            if start_timestamp is not None:
                end_timestamp = int(datetime.now().timestamp()*1e3)
                while start_timestamp <= end_timestamp:
                    try:
                        self.writeLog(u'从{} ~{} 下载 {}数据'
                                      .format(datetime.fromtimestamp(start_timestamp/1e3),
                                              datetime.fromtimestamp(end_timestamp/1e3), binance_symbol))
                        bars_per_loop = self.client.get_klines(symbol=binance_symbol, interval=binance_period,
                                                               startTime=start_timestamp,endTime=end_timestamp,limit=1000)
                        if len(bars_per_loop)==0:
                            self.writeLog(u'数据长度为0，结束')
                            break

                        # 更新开始时间，为这次取得最后一个值
                        start_timestamp = bars_per_loop[-1][0]
                        if len(bars)> 0:
                            while bars[-1][0] >= bars_per_loop[0][0]:
                                if len(bars_per_loop)==1:
                                    bars_per_loop = []
                                    start_timestamp = end_timestamp + 1
                                    break
                                bars_per_loop = bars_per_loop[1:]

                        # 追加bars
                        bars.extend(bars_per_loop)

                    except Exception as ex:
                        self.writeError(u'下载数据{} {} 异常:{},{}'.format(binance_symbol,binance_period,str(ex),traceback.format_exc()))
                        break
            else:
                bars = self.client.get_klines(symbol=binance_symbol, interval=binance_period)

            for i, bar in enumerate(bars):
                add_bar = {}
                try:
                    bar_datetime = datetime.fromtimestamp(bar[0] / 1e3)
                    utc_datetime = datetime.utcfromtimestamp(bar[0] / 1e3)
                    add_bar['datetime'] = bar_datetime.strftime('%Y-%m-%d %H:%M:%S')
                    add_bar['date'] = bar_datetime.strftime('%Y-%m-%d')
                    add_bar['time'] = bar_datetime.strftime('%H:%M:%S')
                    add_bar['open'] = float(bar[1])
                    add_bar['high'] = float(bar[2])
                    add_bar['low'] = float(bar[3])
                    add_bar['close'] = float(bar[4])
                    add_bar['volume'] = float(bar[5])
                    add_bar['tradingDay'] = utc_datetime.strftime('%Y-%m-%d')
                    ret_bars.append(add_bar)
                except Exception as ex:
                    self.writeError(
                        'error when convert bar:{},ex:{},t:{}'.format(bar, str(ex), traceback.format_exc()))
                    return ret_bars

                if start_dt is not None and bar_datetime < start_dt:
                    continue

            return ret_bars
        except Exception as ex:
            self.writeError('exception in get:{},{},{}'.format(binance_symbol,str(ex), traceback.format_exc()))
            return ret_bars

if __name__ == '__main__':

    binance_data = BinanceData()

    # 下载最近500条日线数据
    #bars = binance_data.download_bars(symbol='btc_usdt', period='1day')

    #for bar in bars:
    #    print(bar['datetime'])

    # 导出到csv文件
    #import pandas as pd
    #df = pd.DataFrame(bars)
    #df.set_index('datetime')
    #df.to_csv('btc_usdt_1day.csv',index=True)

    start_date = datetime(year=2017,month=1,day=1)
    bars = binance_data.download_bars(symbol='btc_usdt',start_dt=start_date, period='1min')
    #for bar in bars:
    #    print('first bar time:{}'.format(bar['datetime']))
    #    break
    # 导出到csv文件
    import pandas as pd
    df = pd.DataFrame(bars)
    df = df.set_index('datetime')
    df.index.name = 'index'
    df.to_csv('binance_btc_usdt_{}_{}_1min.csv'.format(start_date.strftime('%Y%m%d'),datetime.now().strftime('%Y%m%d')),index=True)
