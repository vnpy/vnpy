# encoding: UTF-8

# 从okex下载数据
from datetime import datetime, timezone

import requests
import execjs
import traceback
from vnpy.trader.app.ctaStrategy.ctaBase import CtaBarData, CtaTickData

period_list = ['1min','3min','5min','15min','30min','1day','1week','1hour','2hour','4hour','6hour','12hour']
symbol_list = ['btc_usd','eth_usd','etc_usd','bch_usd','xrp_usd','eos_usd','btg_usd']


class OkexFutureData(object):

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

    def get_bars(self, symbol, period, callback, bar_is_completed=False,bar_freq=1, start_dt=None):
        """
        返回k线数据
        symbol：合约b tc:next_week:10
        period: 周期: 1min,3min,5min,15min,30min,1day,3day,1hour,2hour,4hour,6hour,12hour
        """
        ret_bars = []
        if ':' not in symbol:
            self.strategy.writeCtaError(u'{} {}格式需要包含合约类型,如:btc:next_week:10'.format(datetime.now(), symbol))
            return False, ret_bars
        s = symbol.split(':')
        symbol_pair, contract_type = s[0],s[1]
        if not symbol_pair.endswith('_usd'):
            symbol_pair += '_usd'

        if symbol_pair not in symbol_list:
            self.strategy.writeCtaError(u'{} {}不在下载清单中'.format(datetime.now(), symbol_pair))
            return False, ret_bars

        url = u'https://www.okex.com/api/v1/future_kline.do?symbol={}&type={}&contract_type={}'.format(symbol_pair, period,contract_type)
        self.strategy.writeCtaLog('{}开始下载:{} {}数据.URL:{}'.format(datetime.now(), symbol, period, url))
        bars = []
        content = None
        try:
            content = self.session.get(url).content.decode('gbk')
            bars = execjs.eval(content)
        except Exception as ex:
            self.strategy.writeCtaError('exception in get:{},{},{}'.format(url,str(ex), traceback.format_exc()))
            return False, ret_bars

        for i, bar in enumerate(bars):
            if len(bar) < 5:
                self.strategy.writeCtaError('error when import bar:{}'.format(bar))
                return False

            add_bar = CtaBarData()
            try:
                add_bar.vtSymbol = symbol
                add_bar.symbol = symbol
                add_bar.datetime = datetime.fromtimestamp(bar[0] / 1000)
                add_bar.date = add_bar.datetime.strftime('%Y-%m-%d')
                add_bar.time = add_bar.datetime.strftime('%H:%M:%S')
                add_bar.tradingDay = add_bar.date
                add_bar.open = float(bar[1])
                add_bar.high = float(bar[2])
                add_bar.low = float(bar[3])
                add_bar.close = float(bar[4])
                add_bar.volume = float(bar[6])    # 这里：5 是交易量，6是交易量转化BTC或LTC数量
            except Exception as ex:
                self.strategy.writeCtaError('error when convert bar:{},ex:{},t:{}'.format(bar, str(ex), traceback.format_exc()))
                return False, ret_bars

            if start_dt is not None and bar.datetime < start_dt:
                continue
            ret_bars.append(add_bar)
            if callback is not None:
                callback(add_bar, bar_is_completed, bar_freq)

        return True, ret_bars



class TestStrategy(object):

    def __init__(self):

        self.minDiff = 1
        self.shortSymbol = 'I'
        self.vtSymbol = 'I99'

        self.TMinuteInterval = 1
    def addBar(self,bar,bar_is_completed, bar_freq):
        print(u'tradingDay:{},dt:{},{} o:{},h:{},l:{},c:{},v:{}'.format(bar.tradingDay, bar.datetime,bar.vtSymbol, bar.open, bar.high,
                                                                     bar.low, bar.close, bar.volume))
    def onBar(self, bar):
        print(u'tradingDay:{},dt:{},{} o:{},h:{},l:{},c:{},v:{}'.format(bar.tradingDay,bar.datetime,bar.vtSymbol, bar.open, bar.high, bar.low, bar.close, bar.volume))

    def writeCtaLog(self, content):
        print(content)

    def writeCtaError(self, content):
        print(content)

if __name__ == '__main__':

    t = TestStrategy()
    of = OkexFutureData(t)
    of.get_bars(symbol='btc:next_week:10', period='1min', callback=t.addBar)

