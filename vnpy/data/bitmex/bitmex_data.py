# encoding: UTF-8

# 从bitmex下载数据
from datetime import datetime, timezone,timedelta
from time import time
import sys
import requests
import execjs
import traceback
import hashlib
import hmac
from urllib.parse import urlencode
from collections import  OrderedDict
from vnpy.trader.app.ctaStrategy.ctaBase import CtaBarData, CtaTickData

period_list = ['1min','5min','1day','1hour']

class BitmexData(object):
    # ----------------------------------------------------------------------
    def __init__(self, strategy=None,apiKey=None,apiSecret=None):
        """
        构造函数
        :param strategy: 上层策略，主要用与使用strategy.writeCtaLog（）
        """
        self.strategy = strategy
        self.apiKey = apiKey
        self.apiSecret = apiSecret

        # 设置HTTP请求的尝试次数，建立连接session
        self.session = requests.session()
        self.session.keep_alive = False

    # ----------------------------------------------------------------------
    def generateSignature(self, method, path, expires, params=None, body=None):
        """生成签名"""
        # 对params在HTTP报文路径中，以请求字段方式序列化
        if params:
            query = urlencode(sorted(params.items()))
            path = path + '?' + query

        if body is None:
            body = ''

        msg = method + '/api/v1' + path + str(expires) + body
        signature = hmac.new(self.apiSecret.encode('utf-8'), msg.encode('utf-8'),
                             digestmod=hashlib.sha256).hexdigest()

        return signature

    def writeLog(self,content):
        if self.strategy and hasattr(self.strategy,'writeCtaLog'):
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
        if period not in period_list:
            self.strategy.writeCtaError('{} not in {}'.format(period,period_list))
            return False,ret_bars

        period = period.replace('min','m').replace('hour','h').replace('day','d')
        count = 750
        if start_dt is None:
            if period=='1d':
                start_dt = datetime.utcnow() - timedelta(days=count-1)
            elif period=='1h':
                print(u'utc now():{}'.format(datetime.utcnow()))
                start_dt = datetime.utcnow() - timedelta(hours=count-1)
                print(u'start_dt():{}'.format(start_dt))
            elif period == '5m':
                start_dt = datetime.utcnow() - timedelta(minutes=(count-1) * 5)
            else:
                start_dt = datetime.utcnow() - timedelta(minutes=count-1)

        path = '/trade/bucketed'
        url = u'https://www.bitmex.com/api/v1'+path
        params = {'binSize':period,'partial':True,'symbol':symbol,'startTime':start_dt.strftime('%Y-%m-%d %H:%M'),'count':count}

        params = OrderedDict(sorted(params.items()))

        expires = int(time() + 5)
        rq = requests.Request(url=url)
        p = rq.prepare()

        header = {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Accept': 'application/json',
            'api-expires': str(expires),
            'api-key':self.apiKey,
            'api-signature': self.generateSignature('GET', path, expires, params, body=p.body)
        }
        print(header)

        session = requests.Session()
        resp = session.request('GET', url, headers=header, params=params,data=None)

        self.writeLog('{}开始下载:{} {}数据.开始时间:{} URL:{}'.format(datetime.now(), symbol, period,start_dt,url))

        bars = None
        code = resp.status_code
        bars = resp.json()
        if code != 200:
            self.strategy.writeCtaError('get_bars {},{}'.format(code, bars))
            return False, ret_bars

        bar_len = len(bars)
        self.writeLog(u'共下载:{}条'.format(bar_len))
        for i, bar in enumerate(bars):
            add_bar = CtaBarData()
            try:
                add_bar.vtSymbol = symbol
                add_bar.symbol = symbol

                utc_str_time = bar.get('timestamp').replace('T',' ').replace('Z','')
                utc_datetime = datetime.strptime(utc_str_time,'%Y-%m-%d %H:%M:%S.%f')

                add_bar.datetime = utc_datetime + timedelta(hours=8)
                # 时区得调整 +8
                if period == '1h':
                    add_bar.datetime = add_bar.datetime - timedelta(hours=1)
                elif period == '5m':
                    add_bar.datetime = add_bar.datetime - timedelta(minutes=5)
                elif period == '1m':
                    add_bar.datetime = add_bar.datetime - timedelta(minutes=1)

                # bitmex是以bar得结束时间，作为bar得datetime，vnpy是以bar得开始时间作为datetime

                add_bar.date = add_bar.datetime.strftime('%Y-%m-%d')
                add_bar.time = add_bar.datetime.strftime('%H:%M:%S')
                add_bar.tradingDay = add_bar.date
                add_bar.open = float(bar.get('open', 0.0))
                add_bar.high = float(bar.get('high', 0.0))
                add_bar.low = float(bar.get('low', 0.0))
                add_bar.close = float(bar.get('close', 0.0))
                add_bar.volume = float(bar.get('volume', 0.0))
                ret_bars.append(add_bar)
            except Exception as ex:
                self.strategy.writeCtaError('error when convert bar:{},ex:{},t:{}'.format(bar, str(ex), traceback.format_exc()))
                return False,ret_bars

            if start_dt is not None and add_bar.datetime < start_dt:
                continue

            if callback is not None:
                # 最后一个bar，可能是不完整的，强制修改
                if i == bar_len -1 and bar_is_completed:
                    # 根据秒数算的话，要+1，例如13:31,freq=31，第31根bar
                    freq = int((datetime.now() - add_bar.datetime).total_seconds()/60)+1
                    callback(add_bar,False,freq)
                else:
                    callback(add_bar, bar_is_completed, bar_freq)

        return True,ret_bars

    def download_bars(self, symbol, period, size_=None, start_dt=None):
        """
        返回k线数据
        symbol：合约
        period: 周期: 1min,3min,5min,15min,30min,1day,3day,1hour,2hour,4hour,6hour,12hour
        """
        ret_bars = []

        url = u'https://www.okex.com/api/v1/kline.do?symbol={}&type={}'.format(symbol, period)
        if isinstance(size_,int):
            url = url + u'&size={}'.format(size_)
        if start_dt is not None and isinstance(start_dt,datetime):
            url = url + u'&since={}'.format(int(start_dt.timestamp()*1000))
        self.writeLog('{}开始下载:{} {}数据.URL:{}'.format(datetime.now(), symbol, period,url))

        content = None
        try:
            content = self.session.get(url).content.decode('gbk')
        except Exception as ex:
            self.writeError('exception in get:{},{},{}'.format(url,str(ex), traceback.format_exc()))
            return ret_bars

        bars = execjs.eval(content)

        if not isinstance(bars,list):
            self.writeError('返回数据不是list:{}'.format(content))
            return ret_bars

        for i, bar in enumerate(bars):
            if len(bar) < 5:
                self.writeError('error when get bar:{}'.format(bar))
                return ret_bars
            if i == 0:
                continue
            add_bar = {}
            try:

                bar_datetime= datetime.fromtimestamp(bar[0] / 1000)
                add_bar['datetime'] = bar_datetime.strftime('%Y-%m-%d %H:%M:%S')
                add_bar['date'] = bar_datetime.strftime('%Y-%m-%d')
                add_bar['time'] = bar_datetime.strftime('%H:%M:%S')
                add_bar['open'] = float(bar[1])
                add_bar['high'] = float(bar[2])
                add_bar['low'] = float(bar[3])
                add_bar['close'] = float(bar[4])
                add_bar['volume'] = float(bar[5])
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
    # 这里要用生产系统的API，不要用testnet的API, 生产和testnet的行情不一样的。
    API_KEY = 'xx'
    API_SECRET = 'xxx-xxx-xx'

    bitmex_data = BitmexData(t,API_KEY,API_SECRET)

    #bitmex_data.get_bars(symbol='XBTUSD',period='1hour',callback=t.addBar,bar_is_completed=True,bar_freq=60)
    bitmex_data.get_bars(symbol='XBTUSD',period='5min',callback=t.addBar,bar_is_completed=True,bar_freq=60)



