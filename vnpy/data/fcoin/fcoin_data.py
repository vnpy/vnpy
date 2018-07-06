# encoding: UTF-8

# 从okex下载数据
from datetime import datetime, timezone

import requests
import execjs
import traceback
from vnpy.trader.app.ctaStrategy.ctaBase import CtaBarData, CtaTickData
from vnpy.api.fcoin.fcoin import Fcoin

PERIOD_MAPPING = {}
PERIOD_MAPPING['1min']   = 'M1'
PERIOD_MAPPING['3min']   = 'M3'
PERIOD_MAPPING['5min']   = 'M5'
PERIOD_MAPPING['15min']  = 'M15'
PERIOD_MAPPING['30min']  = 'M30'
PERIOD_MAPPING['1hour']  = 'H1'
PERIOD_MAPPING['2hour']  = 'H2'
PERIOD_MAPPING['4hour']  = 'H4'
PERIOD_MAPPING['6hour']  = 'H6'
PERIOD_MAPPING['8hour']  = 'H8'
PERIOD_MAPPING['12hour'] = 'H12'
PERIOD_MAPPING['1day']   = 'D1'
PERIOD_MAPPING['1week']  = 'W1'
PERIOD_MAPPING['1month'] = 'M1'

symbol_list = ['ltc_btc','eth_btc','etc_btc','bch_btc','btc_usdt','eth_usdt','ltc_usdt','etc_usdt','bch_usdt',
              'etc_eth','bt1_btc','bt2_btc','btg_btc','qtum_btc','hsr_btc','neo_btc','gas_btc',
              'qtum_usdt','hsr_usdt','neo_usdt','gas_usdt','ft_usdt']


class FcoinData(object):

    # ----------------------------------------------------------------------
    def __init__(self, strategy):
        """
        构造函数
        :param strategy: 上层策略，主要用与使用strategy.writeCtaLog（）
        """
        self.strategy = strategy
        self.fcoin = Fcoin()

    def get_bars(self, symbol, period, callback, bar_is_completed=False,bar_freq=1, start_dt=None):
        """
        返回k线数据
        symbol：合约
        period: 周期: 1min,3min,5min,15min,30min,1day,3day,1hour,2hour,4hour,6hour,12hour
        """
        ret_bars = []
        if symbol not in symbol_list:
            self.strategy.writeCtaError(u'{} {}不在下载清单中'.format(datetime.now(), symbol))
            return False, ret_bars
        if period not in PERIOD_MAPPING:
            self.strategy.writeCtaError(u'{} 周期{}不在下载清单中'.format(datetime.now(), period))
            return False, ret_bars

        self.strategy.writeCtaLog('{}开始下载:{} {}数据'.format(datetime.now(), symbol, period))

        fcoin_period = PERIOD_MAPPING.get(period)
        fcoin_symbol = symbol.lower().replace('_' , '')

        try:
            status,response = self.fcoin.get_candle(resolution=fcoin_period,symbol=fcoin_symbol,limit=200)
            if not status:
                return False, ret_bars
            bars = response.get('data')
            bars.reverse()
            #{'seq': 7636160700002, 'low': 6747.96, 'open': 6752.49, 'high': 6753.37, 'base_vol': 356.859787045,
            # 'quote_vol': 2409051.1568048545, 'id': 1529566740, 'close': 6750.72, 'count': 3673}
            for i, bar in enumerate(bars):

                add_bar = CtaBarData()
                try:
                    add_bar.vtSymbol = symbol
                    add_bar.symbol = symbol
                    add_bar.datetime = datetime.fromtimestamp(bar.get('id',datetime.now()) )
                    add_bar.date = add_bar.datetime.strftime('%Y-%m-%d')
                    add_bar.time = add_bar.datetime.strftime('%H:%M:%S')
                    add_bar.tradingDay = add_bar.date
                    add_bar.open = float(bar.get('open',0.0))
                    add_bar.high = float(bar.get('high',0.0))
                    add_bar.low = float(bar.get('low',0.0))
                    add_bar.close = float(bar.get('close',0.0))
                    add_bar.volume = float(bar.get('base_vol',0.0))
                except Exception as ex:
                    self.strategy.writeCtaError('error when convert bar:{},ex:{},t:{}'.format(bar, str(ex), traceback.format_exc()))
                    return False, ret_bars

                if start_dt is not None and bar.datetime < start_dt:
                    continue
                ret_bars.append(add_bar)
                if callback is not None:
                    callback(add_bar, bar_is_completed, bar_freq)

            return True, ret_bars

        except Exception as ex:
            self.strategy.writeCtaError('exception in get bar:{},{}'.format(str(ex), traceback.format_exc()))
            return False


class TestStrategy(object):

    def __init__(self):

        self.minDiff = 1
        self.shortSymbol = 'I'
        self.vtSymbol = 'I99'

        self.TMinuteInterval = 1
    def addBar(self,bar,bar_is_completed, bar_freq):
        print(u'tradingDay:{},dt:{},o:{},h:{},l:{},c:{},v:{}'.format(bar.tradingDay, bar.datetime, bar.open, bar.high,
                                                                     bar.low, bar.close, bar.volume))
    def onBar(self, bar):
        print(u'tradingDay:{},dt:{},o:{},h:{},l:{},c:{},v:{}'.format(bar.tradingDay,bar.datetime, bar.open, bar.high, bar.low, bar.close, bar.volume))

    def writeCtaLog(self, content):
        print(content)

    def writeCtaError(self, content):
        print(content)

if __name__ == '__main__':

    t = TestStrategy()
    fd = FcoinData(t)
    fd.get_bars(symbol='btc_usdt',period='1min',callback=t.addBar)
