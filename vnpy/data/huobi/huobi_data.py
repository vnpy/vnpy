# encoding: UTF-8

# 从huobi载数据
from datetime import datetime, timezone
import sys
import requests
import execjs
import traceback
from vnpy.trader.app.ctaStrategy.ctaBase import CtaBarData, CtaTickData
from vnpy.trader.vtFunction import systemSymbolToVnSymbol

period_list = ['1min','3min','5min','15min','30min','1day','1week','60min']
symbol_list = ['ltc_btc','eth_btc','etc_btc','bch_btc','btc_usdt','eth_usdt','ltc_usdt','etc_usdt','bch_usdt',
              'etc_eth','bt1_btc','bt2_btc','btg_btc','qtum_btc','hsr_btc','neo_btc','gas_btc',
              'qtum_usdt','hsr_usdt','neo_usdt','gas_usdt','eos_usdt','ada_usdt','xmr_usdt','zrx_usdt','ht_usdt']


class HuobiData(object):

    # ----------------------------------------------------------------------
    def __init__(self, strategy=None):
        """
        构造函数
        :param strategy: 上层策略，主要用与使用strategy.writeCtaLog（）
        """
        self.strategy = strategy

        # 设置HTTP请求的尝试次数，建立连接session
        requests.adapters.DEFAULT_RETRIES = 5
        self.session = requests.session()
        self.session.keep_alive = False

    def writeLog(self,content):
        if self.strategy:
            self.strategy.writeCtaLog(content)
        else:
            print(content)

    def writeError(self,content):
        if self.strategy:
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
        symbol_pair = systemSymbolToVnSymbol(symbol)

        if symbol_pair not in symbol_list:
            msg = u'{} {}不在下载清单中'.format(datetime.now(), symbol_pair)
            if self.strategy:
                self.strategy.writeCtaError(msg)
            else:
                print(msg)
            return False,ret_bars
        symbol = symbol_pair.replace('_', '')
        if period == '1hour':
            period = '60min'

        if period not in period_list:
            self.writeError(u'{}不在下载时间周期范围:{} 内'.format(period, period_list))
            return False,ret_bars

        url = u'https://api.huobipro.com/market/history/kline?symbol={}&period={}& size=2000&AccessKeyId=fff-xxx-ssss-kkk'.format(
            symbol, period)

        self.writeLog('{}开始下载:{} {}数据.URL:{}'.format(datetime.now(), symbol_pair, period, url))

        content = None
        try:
            content = self.session.get(url).content.decode('gbk')
        except Exception as ex:
            self.writeError('exception in get:{},{},{}'.format(url, str(ex), traceback.format_exc()))
            return False,ret_bars

        ret_dict = execjs.eval(content)
        bars = ret_dict.get('data', None)

        if not isinstance(bars, list):
            self.writeError('返回数据不是list:{}'.format(content))
            return False,ret_bars
        bars.reverse()

        for i, bar in enumerate(bars):
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
                add_bar.volume = float(bar[5])
            except Exception as ex:
                self.strategy.writeCtaError('error when convert bar:{},ex:{},t:{}'.format(bar, str(ex), traceback.format_exc()))
                return False,ret_bars

            if start_dt is not None and bar.datetime < start_dt:
                continue

            if callback is not None:
                callback(add_bar, bar_is_completed, bar_freq)

        return True,ret_bars


    def download_bars(self, symbol, period, size_=None, start_dt=None):
        """
        返回k线数据
        symbol：合约
        period: 周期: 1min, 5min, 15min, 30min, 60min, 1day, 1mon, 1week, 1year
        """
        ret_bars = []
        symbol_pair = systemSymbolToVnSymbol(symbol)

        if symbol_pair not in symbol_list:
            msg = u'{} {}不在下载清单中'.format(datetime.now(), symbol_pair)
            if self.strategy:
                self.strategy.writeCtaError(msg)
            else:
                print(msg)
            return ret_bars
        symbol = symbol_pair.replace('_','')
        if period =='1hour':
            period = '60min'

        if period not in period_list:
            self.writeError(u'{}不在下载时间周期范围:{} 内'.format(period,period_list))
            return ret_bars

        url = u'https://api.huobipro.com/market/history/kline?symbol={}&period={}&AccessKeyId=fff-xxx-ssss-kkk'.format(symbol, period)
        if not isinstance(size_,int):
            size_=2000

        url = url + u'&size={}'.format(size_)

        self.writeLog('{}开始下载:{} {}数据.URL:{}'.format(datetime.now(), symbol_pair, period,url))

        content = None
        try:
            content = self.session.get(url).content.decode('gbk')
        except Exception as ex:
            self.writeError('exception in get:{},{},{}'.format(url,str(ex), traceback.format_exc()))
            return ret_bars

        ret_dict = execjs.eval(content)
        bars = ret_dict.get('data',None)

        if not isinstance(bars,list):
            self.writeError('返回数据不是list:{}'.format(content))
            return ret_bars
        bars.reverse()

        for i, bar in enumerate(bars):
            add_bar = {}
            try:
                bar_datetime= datetime.fromtimestamp(bar.get('id'))
                add_bar['datetime'] = bar_datetime.strftime('%Y-%m-%d %H:%M:%S')
                add_bar['date'] = bar_datetime.strftime('%Y-%m-%d')
                add_bar['time'] = bar_datetime.strftime('%H:%M:%S')
                add_bar['open'] = float(bar.get('open',0.0))
                add_bar['high'] = float(bar.get('high',0.0))
                add_bar['low'] = float(bar.get('low',0.0))
                add_bar['close'] = float(bar.get('close',0.0))
                add_bar['volume'] = float(bar.get('vol',0.0))
            except Exception as ex:
                self.writeError('error when convert bar:{},ex:{},t:{}'.format(bar, str(ex), traceback.format_exc()))

            ret_bars.append(add_bar)

        return ret_bars


class TestStrategy(object):

    def __init__(self):

        self.minDiff = 1
        self.shortSymbol = 'btc'
        self.vtSymbol = 'btc'

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

    hb_data = HuobiData(t)

    bars = hb_data.download_bars(symbol='htusdt', period='1day')

    for bar in bars:
        print(bar['datetime'])