# encoding: UTF-8

# 从okex下载数据
from datetime import datetime, timedelta

import requests
import execjs
import traceback
import time as td
from vnpy.trader.app.ctaStrategy.ctaBase import CtaBarData, CtaTickData

period_list = {'1min': 60 ,'3min':180,'5min':300,'15min':900,'30min':1800,
              '1hour':3600,'2hour':7200,'4hour':14400,'6hour':21600,'12hour':43200}
symbol_list = ['btc_usd','eth_usd','etc_usd','bch_usd','xrp_usd','eos_usd','btg_usd']

period_limited = {"4hour":180, "2hour":94, "1hour":168, "30min":192, "15min":192, "5min":144}
# 4小时是间隔30天，2小时是间隔7天，1小时是间隔7天，30分钟是间隔4天，15分钟是间隔2天
# 15分钟以下，间隔1日拿一次


class OkexFutureData(object):

    def __init__(self, strategy):
        self.strategy = strategy
        # 设置HTTP请求的尝试次数，建立连接session
        self.session = requests.session()
        self.session.keep_alive = False


    def get_data(self, symbol, period, start_dt=None):
        """

        :param symbol:
        :param period:
        :param start_dt:
        :return:
        """
        ret_bars = []
        symbol_pair = symbol
        url_list = []
        if start_dt is None:
            if symbol_pair.endswith('SWAP'):
                url = u'https://www.okex.com/api/swap/v3/instruments/{}/candles?granularity={}'.format(symbol_pair,period_list[period])
            else:
                url = u'https://www.okex.com/api/futures/v3/instruments/{}/candles?granularity={}'.format(symbol_pair,period_list[period])
            url_list.append(url)
        else:
            if symbol_pair.endswith('SWAP'):
                url = u'https://www.okex.com/api/swap/v3/instruments/{}/candles?'.format(symbol_pair)
            else:
                url = u'https://www.okex.com/api/futures/v3/instruments/{}/candles?'.format(symbol_pair)
            datetime_now = datetime.now()
            datetime_start_dt = datetime.strptime(start_dt, "%Y-%m-%d %H:%M:%S")
            if '4h' in period:
                interval = period_list['4hour'] * period_limited['4hour']
                status = True
                start_time = datetime_start_dt
                while status:
                    end_time = start_time + timedelta(seconds=interval)
                    if end_time > datetime_now:
                        status = False
                        start = (start_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ','T') + '.000Z'
                        info = 'start={}&granularity={}'.format(start, period_list[period])
                        tmp_url = url + info
                        url_list.append(tmp_url)
                    else:
                        start = (start_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ','T') + '.000Z'
                        end = (end_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ','T') + '.000Z'
                        info = 'start={}&end={}&granularity={}'.format(start,end,period_list[period])
                        tmp_url = url + info
                        url_list.append(tmp_url)
                        start_time = end_time
            elif '2h' in period:
                interval = period_list['2hour'] * period_limited['2hour']
                status = True
                start_time = datetime_start_dt
                while status:
                    end_time = start_time + timedelta(seconds=interval)
                    if end_time > datetime_now:
                        status = False
                        start = (start_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ',
                                                                                                        'T') + '.000Z'
                        info = 'start={}&granularity={}'.format(start, period_list[period])
                        tmp_url = url + info
                        url_list.append(tmp_url)
                    else:
                        start = (start_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ',
                                                                                                        'T') + '.000Z'
                        end = (end_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ', 'T') + '.000Z'
                        info = 'start={}&end={}&granularity={}'.format(start, end, period_list[period])
                        tmp_url = url + info
                        url_list.append(tmp_url)
                        start_time = end_time
            elif '1h' in period:
                interval = period_list['1hour'] * period_limited['1hour']
                status = True
                start_time = datetime_start_dt
                while status:
                    end_time = start_time + timedelta(seconds=interval)
                    if end_time > datetime_now:
                        status = False
                        start = (start_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ',
                                                                                                        'T') + '.000Z'
                        info = 'start={}&granularity={}'.format(start, period_list[period])
                        tmp_url = url + info
                        url_list.append(tmp_url)
                    else:
                        start = (start_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ',
                                                                                                        'T') + '.000Z'
                        end = (end_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ', 'T') + '.000Z'
                        info = 'start={}&end={}&granularity={}'.format(start, end, period_list[period])
                        tmp_url = url + info
                        url_list.append(tmp_url)
                        start_time = end_time
            elif '30m' in period:
                interval = period_list['30min'] * period_limited['30min']
                status = True
                start_time = datetime_start_dt
                while status:
                    end_time = start_time + timedelta(seconds=interval)
                    if end_time > datetime_now:
                        status = False
                        start = (start_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ',
                                                                                                        'T') + '.000Z'
                        info = 'start={}&granularity={}'.format(start, period_list[period])
                        tmp_url = url + info
                        url_list.append(tmp_url)
                    else:
                        start = (start_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ',
                                                                                                        'T') + '.000Z'
                        end = (end_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ', 'T') + '.000Z'
                        info = 'start={}&end={}&granularity={}'.format(start, end, period_list[period])
                        tmp_url = url + info
                        url_list.append(tmp_url)
                        start_time = end_time
            elif '15m' in period:
                interval = period_list['15min'] * period_limited['15min']
                status = True
                start_time = datetime_start_dt
                while status:
                    end_time = start_time + timedelta(seconds=interval)
                    if end_time > datetime_now:
                        status = False
                        start = (start_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ','T') + '.000Z'
                        info = 'start={}&granularity={}'.format(start, period_list[period])
                        tmp_url = url + info
                        url_list.append(tmp_url)
                    else:
                        start = (start_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ','T') + '.000Z'
                        end = (end_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ', 'T') + '.000Z'
                        info = 'start={}&end={}&granularity={}'.format(start, end, period_list[period])
                        tmp_url = url + info
                        url_list.append(tmp_url)
                        start_time = end_time
            elif '5m' in period:
                interval = period_list['5min'] * period_limited['5min']
                status = True
                start_time = datetime_start_dt
                while status:
                    end_time = start_time + timedelta(seconds=interval)
                    if end_time > datetime_now:
                        status = False
                        start = (start_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ','T') + '.000Z'
                        info = 'start={}&granularity={}'.format(start, period_list[period])
                        tmp_url = url + info
                        url_list.append(tmp_url)
                    else:
                        start = (start_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ','T') + '.000Z'
                        end = (end_time - timedelta(hours=8)).strftime("%Y-%m-%d %H:%M:%S").replace(' ', 'T') + '.000Z'
                        info = 'start={}&end={}&granularity={}'.format(start, end, period_list[period])
                        tmp_url = url + info
                        url_list.append(tmp_url)
                        start_time = end_time

        self.strategy.writeCtaLog('{}开始下载:{} {}数据,第一日期{}'.format(datetime.now(), symbol, period, start_dt))
        total_bars = []
        try:
            while True:
                times = 1
                for url in url_list:
                    content = self.session.get(url).content.decode('gbk')
                    bars = execjs.eval(content)
                    if not isinstance(bars, list):
                        self.strategy.writeCtaLog('扑街了，bars不是list')
                        td.sleep(4)
                        break
                    if bars == []:
                        self.strategy.writeCtaLog('扑街了，bars为空')
                        td.sleep(4)
                        break
                    bars = bars[::-1]
                    if times == 1:
                        times -= 1
                    else:
                        bars = bars[1:]
                    total_bars.extend(bars)
                return True, total_bars
        except Exception as ex:
            self.strategy.writeCtaError('exception in get:{},{},{}'.format(url, str(ex), traceback.format_exc()))
            return False, total_bars


    def get_bars(self, symbol, period, callback, bar_is_completed=False, bar_freq=1, start_dt=None):
        """
        返回k线数据
        symbol：合约b tc:next_week:10
        period: 周期: 1min,3min,5min,15min,30min,1day,3day,1hour,2hour,4hour,6hour,12hour
        """
        ret_bars = []
        status, bars = self.get_data(symbol, period, start_dt)
        if not status:
            return False, bars
        for i, bar in enumerate(bars):
            if len(bar) < 5:
                self.strategy.writeCtaError('error when import bar:{}'.format(bar))
                return False
            add_bar = CtaBarData()
            try:
                time = bar[0].replace('T', ' ')[:-5]
                add_bar.vtSymbol = symbol
                add_bar.symbol = symbol
                add_bar.datetime = datetime.strptime(time, '%Y-%m-%d %H:%M:%S') + timedelta(hours=8)
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
    data = '2018-01-01 00:00:00'
    b = datetime.strptime(data,'%Y-%m-%d %H:%M:%S') + timedelta(hours=8)
    t = TestStrategy()
    of = OkexFutureData(t)
    a = of.get_bars(symbol='BTC-USD-190628', period='5min', start_dt='2019-03-17 00:00:00',callback=t.addBar)
    print(a)
    print('b')