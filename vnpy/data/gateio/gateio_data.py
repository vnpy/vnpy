# encoding: UTF-8

# 从gateio下载数据
# https://gate.io/api2#kline
from datetime import datetime, timezone

import requests
import execjs
import traceback
from vnpy.trader.app.ctaStrategy.ctaBase import CtaBarData

period_list = ['1min','3min','5min','15min','30min','1day','1week','1hour','2hour','4hour','6hour','12hour']
symbol_list = ['ltc_btc','eth_btc','etc_btc','bch_btc','btc_usdt','eth_usdt','ltc_usdt','etc_usdt','bch_usdt',
              'etc_eth','bt1_btc','bt2_btc','btg_btc','qtum_btc','hsr_btc','neo_btc','gas_btc',
              'qtum_usdt','hsr_usdt','neo_usdt','gas_usdt']


class GateioData(object):

    # ----------------------------------------------------------------------
    def __init__(self, strategy):
        """
        构造函数
        :param strategy: 上层策略，主要用与使用strategy.writeCtaLog（）
        """
        self.strategy = strategy

        # 设置HTTP请求的尝试次数，建立连接session

        self.session = requests.session()
        self.session.keep_alive = False

    def get_sec_hours(self,period):
        if 'min' in period:
            minutes = int(period.replace('min',''))
            get_hours = int(2000 * minutes / 60)
            return 60 * minutes, get_hours

        if 'hour' in period:
            hours = int(period.replace('hour',''))
            return 60 * 60 * hours, 2000 * hours

        if 'day' in period:
            days = int(period.replace('day',''))
            hours = 2000 * days * 24
            return 60 * 60 * 24 * days, hours

        if 'week' in period:
            weeks = int(period.replace('week',''))
            hours = 2000 * weeks * 7 * 24
            return 60 * 60 * 24 * 7 * weeks, hours

        return 60,10

    def get_bars(self, symbol, period, callback, bar_is_completed=False,bar_freq=1, start_dt=None):
        """
        返回k线数据
        symbol：合约
        period: 周期: 1min,3min,5min,15min,30min,1day,3day,1hour,2hour,4hour,6hour,12hour
        """
        ret_bars = []
        if symbol not in symbol_list:
            self.strategy.writeCtaError(u'{} {}不在下载清单中'.format(datetime.now(), symbol))
            return False,ret_bars

        group_sec, range_hour = self.get_sec_hours(period)

        url = u'https://data.gateio.io/api2/1/candlestick2/{}?group_sec={}&range_hour={}'.format(symbol, group_sec,range_hour)
        self.strategy.writeCtaLog('{}开始下载:{} {}数据.URL:{}'.format(datetime.now(), symbol, period, url))

        content = None
        try:
            content = self.session.get(url).content.decode('gbk')
        except Exception as ex:
            self.strategy.writeCtaError('exception in get:{},{},{}'.format(url,str(ex), traceback.format_exc()))
            return False,ret_bars

        content = execjs.eval(content)
        if not isinstance(content,dict):
            self.strategy.writeCtaError(u'content is not dict format:{}'.format(content))
            return False,ret_bars

        bars = content.get('data',[])

        for i, bar in enumerate(bars):
            if len(bar) < 6:
                self.strategy.writeCtaError('error when import bar:{}'.format(bar))
                return False,ret_bars
            add_bar = CtaBarData()
            try:
                add_bar.vtSymbol = symbol
                add_bar.symbol = symbol
                add_bar.datetime = datetime.fromtimestamp(int(bar[0]) / 1000)
                add_bar.date = add_bar.datetime.strftime('%Y-%m-%d')
                add_bar.time = add_bar.datetime.strftime('%H:%M:%S')
                add_bar.tradingDay = add_bar.date
                add_bar.volume = float(bar[1])
                add_bar.close = float(bar[2])
                add_bar.high = float(bar[3])
                add_bar.low = float(bar[4])
                add_bar.open = float(bar[5])

            except Exception as ex:
                self.strategy.writeCtaError('error when convert bar:{},ex:{},t:{}'.format(bar, str(ex), traceback.format_exc()))
                return False,ret_bars

            if start_dt is not None and bar.datetime < start_dt:
                continue

            ret_bars.append(add_bar)
            if callback is not None:
                callback(add_bar, bar_is_completed, bar_freq)

        return True, ret_bars




