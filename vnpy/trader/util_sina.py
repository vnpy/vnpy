# encoding: UTF-8

from __future__ import print_function

import requests
import execjs
from datetime import datetime, timedelta
from vnpy.trader.app.ctaStrategy.ctaBase import CtaBarData, CtaTickData

class UtilSinaClient(object):
    """
    SINA数据客户端，主要使用requests开发
    v1.1 增加start_dt参数，在这个时间点之前的bar全部忽略
    """
    # ----------------------------------------------------------------------
    def __init__(self, strategy):
        """
        构造函数
        :param strategy: 上层策略，主要用与使用strategy.writeCtaLog（）
        """
        self.strategy = strategy

        # 设置HTTP请求的尝试次数，建立连接session
        requests.adapters.DEFAULT_RETRIES = 5
        self.session = requests.session()
        self.session.keep_alive = False

    def getTicks(self, symbol, callback,start_dt=None):
        """
        从sina加载最新的分时数据（Min1)数据
        :param symbol: 合约代码（全路径得合约名称,先使用ctaTemplate.getFullSymbol()
        :param callback: 回调函数
        :param start_dt: 开始时间，缺省为None
        :return: 
        """
        try:
            url = u'http://stock2.finance.sina.com.cn/futures/api/json.php/InnerFuturesService.getInnerFutures5MLine?symbol={0}'.format(
                symbol)
            self.strategy.writeCtaLog(u'从sina下载{0}Tick数据 {1}'.format(symbol, url))
            responses = execjs.eval(self.session.get(url).content.decode('gbk').split('\n')[-1])

            datevalue = datetime.now().strftime('%Y-%m-%d')

            for j, day_item in enumerate(responses[str(symbol).upper()]):
                for i, item in enumerate(day_item):

                    tick = CtaTickData()
                    tick.vtSymbol = symbol
                    tick.symbol = symbol

                    if len(item) >= 6:
                        datevalue = item[6]

                    tick.date = datevalue
                    tick.time = item[4] + u':00'
                    tick.datetime = datetime.strptime(tick.date + ' ' + tick.time, '%Y-%m-%d %H:%M:%S')

                    if start_dt is not None:
                        # 丢弃约定开始时间之前的
                        if tick.datetime < start_dt:
                            continue

                    tick.lastPrice = float(item[0])
                    tick.volume = int(item[2])

                    if type(item[3]) == type(None):
                        tick.openInterest = 0
                    else:
                        tick.openInterest = int(item[3])

                    callback(tick)

            return True

        except Exception as e:
            self.strategy.writeCtaLog(u'加载sina历史Tick数据失败：' + str(e))
            return False

    def getTicks2(self, symbol, callback,start_dt=None):
        """
        # 从sina加载最新的M1数据(针对中金所）
        :param symbol:  合约代码（全路径得合约名称,先使用ctaTemplate.getFullSymbol()
        :param callback: 回调函数
        :param start_dt: 开始时间，缺省为None
        :return: 成功/失败
        """
        try:
            url = u'http://stock2.finance.sina.com.cn/futures/api/jsonp.php/var%20t1nf_{0}=/InnerFuturesNewService.getMinLine?symbol={0}'.format(symbol)
            self.strategy.writeCtaLog(u'从sina下载{0}Tick数据 {1}'.format(symbol, url))

            response_data= self.session.get(url).content
            response_data = response_data.decode('gbk').split('=')[-1]
            response_data = response_data.replace('(', '')
            response_data = response_data.replace(');', '')
            responses= execjs.eval(response_data)
            datevalue = datetime.now().strftime('%Y-%m-%d')

            for i, item in enumerate(responses):

                tick = CtaTickData()
                tick.vtSymbol = symbol
                tick.symbol = symbol

                if len(item) >= 6:
                    datevalue = item[6]

                tick.date = datevalue
                tick.time = item[0] + u':00'
                tick.datetime = datetime.strptime(tick.date + ' ' + tick.time, '%Y-%m-%d %H:%M:%S')

                if start_dt is not None:
                    if tick.datetime < start_dt:
                        continue

                tick.lastPrice = float(item[1])
                tick.volume = int(item[3])

                if type(item[4]) == type(None):
                    tick.openInterest = 0
                else:
                    tick.openInterest = int(item[4])

                callback(tick)

            return True

        except Exception as e:
            self.strategy.writeCtaLog(u'加载sina历史Tick数据失败：' + str(e))
            return False

    def getMinInternal(self, minute):
        """
        获取合适得分钟周期
        :param minute: 输入分钟
        :return: 合适的分钟周期
        """
        if minute < 15:
            return 5

        if minute < 30:
            return 15

        return 30

    def getMinBars(self, symbol, minute, callback,start_dt=None):
        """
        从sina加载最新的M5,M15,M30,M60数据
        :param symbol: （全路径得合约名称,先使用ctaTemplate.getFullSymbol()
        :param minute: 5，15，30，60
        :param callback: 回调函数
        :param start_dt: 开始时间，缺省为None
        :return: 成功/失败
        """
        if minute not in [5, 15, 30, 60]:
            return False

        sinaBars = []
        try:
            url = u'http://stock2.finance.sina.com.cn/futures/api/json.php/InnerFuturesService.getInnerFutures{0}MinKLine?symbol={1}'.format(minute,symbol)
            self.strategy.writeCtaLog(u'从sina下载{0}的{1}分钟数据 {2}'.format(symbol,minute, url))
            responses = execjs.eval(self.session.get(url).content.decode('gbk').split('\n')[-1])
            dayVolume = 0

            for item in responses:
                bar = CtaBarData()

                bar.vtSymbol = symbol
                bar.symbol = symbol
                # bar的close time
                sinaDt = datetime.strptime(item[0], '%Y-%m-%d %H:%M:00')

                if minute in {5, 15} and sinaDt.hour == 10 and sinaDt.minute == 30:
                    # 这个是sina的bug，它把10:15 ~10:30也包含进来了
                    continue

                if minute == 60 and sinaDt.hour in {11,23,1,2} and sinaDt.minute == 30:
                    bar.datetime = sinaDt - timedelta(seconds=(minute /2)* 60)
                else:
                    bar.datetime = sinaDt - timedelta(seconds=minute * 60)

                if start_dt is not None:
                    if bar.datetime < start_dt:
                        continue
                bar.date = bar.datetime.strftime('%Y%m%d')
                bar.tradingDay = bar.date       # todo: 需要修改，晚上21点后，修改为next workingday
                bar.time = bar.datetime.strftime('%H:%M:00')

                bar.open = float(item[1])
                bar.high = float(item[2])
                bar.low = float(item[3])
                bar.close = float(item[4])
                bar.volume = int(item[5])

                # 计算dayvolume
                if not sinaBars:
                    dayVolume = bar.volume
                else:
                    if sinaBars[-1].datetime.hour == 14 and bar.datetime.hour !=14:
                        dayVolume = bar.volume
                    else:
                        dayVolume += bar.volume

                bar.dayVolume = dayVolume

                sinaBars.append(bar)

            if len(sinaBars)>0:
                self.strategy.writeCtaLog(u'从sina读取了{0}条{1}分钟数据'.format(len(sinaBars),minute))

                # 把sina的bar灌入回调函数
                for bar in sinaBars:
                    callback(bar)

                # 处理完毕，清空
                sinaBars = []

                return True
            else:
                self.strategy.writeCtaLog(u'从sina读取{0}分钟数据失败'.format(minute))
                return False

        except Exception as e:
            self.strategy.writeCtaLog(u'加载Sina历史分钟数据失败：'+str(e))
            return False

    def getMinBars2(self, symbol, minute, callback,start_dt=None):
        """
        从sina加载最新的M5,M15,M30,M60数据(针对中金所）
        :param symbol: （全路径得合约名称,先使用ctaTemplate.getFullSymbol()
        :param minute: 5，15，30，60
        :param callback: 回调函数
        :param start_dt: 开始时间，缺省为None
        :return: 成功/失败
        """
        if minute not in {5, 15, 30, 60}:
            return False

        sinaBars = []
        try:
            timestamp = (datetime.utcnow() - datetime(1970, 1, 1)).total_seconds()
            url=u'http://stock2.finance.sina.com.cn/futures/api/jsonp.php/var%20_{1}_{0}_{2}=/InnerFuturesNewService.getFewMinLine?symbol={1}&type={0}'.format(minute,symbol,timestamp)
            #url = u'http://stock2.finance.sina.com.cn/futures/api/json.php/InnerFuturesService.getInnerFutures{0}MinKLine?symbol={1}'.format(minute,symbol)
            self.strategy.writeCtaLog(u'从sina下载{0}的{1}分钟数据 {2}'.format(symbol,minute, url))
            response_data = self.session.get(url).content
            response_data = response_data.decode('gbk').split('=')[-1]
            response_data = response_data.replace('(', '')
            response_data = response_data.replace(');', '')
            responses = execjs.eval(response_data)

            dayVolume = 0

            for item in responses:
                bar = CtaBarData()

                bar.vtSymbol = symbol
                bar.symbol = symbol
                # bar的close time
                sinaDt = datetime.strptime(item['d'], '%Y-%m-%d %H:%M:00')

                if minute in {5, 15} and sinaDt.hour == 10 and sinaDt.minute == 30:
                    # 这个是sina的bug，它把10:15 ~10:30也包含进来了
                    continue

                if minute == 60 and sinaDt.hour in {11,23,1,2} and sinaDt.minute == 30:
                    bar.datetime = sinaDt - timedelta(seconds=(minute /2)* 60)
                else:
                    bar.datetime = sinaDt - timedelta(seconds=minute * 60)
                if start_dt is not None:
                    if bar.datetime < start_dt:
                        continue
                bar.date = bar.datetime.strftime('%Y%m%d')
                bar.tradingDay = bar.date       # todo: 需要修改，晚上21点后，修改为next workingday
                bar.time = bar.datetime.strftime('%H:%M:00')

                bar.open = float(item['o'])
                bar.high = float(item['h'])
                bar.low = float(item['l'])
                bar.close = float(item['c'])
                bar.volume = int(item['v'])

                # 计算dayvolume
                if not sinaBars:
                    dayVolume = bar.volume
                else:
                    if sinaBars[-1].datetime.hour == 14 and bar.datetime.hour !=14:
                        dayVolume = bar.volume
                    else:
                        dayVolume += bar.volume

                bar.dayVolume = dayVolume

                sinaBars.append(bar)

            if len(sinaBars)>0:
                self.strategy.writeCtaLog(u'从sina读取了{0}条{1}分钟数据'.format(len(sinaBars),minute))

                # 把sina的bar灌入回调函数
                for bar in sinaBars:
                    callback(bar)

                # 处理完毕，清空
                sinaBars = []

                return True
            else:
                self.strategy.writeCtaLog(u'从sina读取{0}分钟数据失败'.format(minute))
                return False

        except Exception as e:
            self.strategy.writeCtaLog(u'加载Sina历史分钟数据失败：'+str(e))
            return False

    def getDayBars(self, symbol, callback,start_dt=None):
        """
        从sina加载最新的Day数据
        :param symbol: （全路径得合约名称,先使用ctaTemplate.getFullSymbol()
        :param callback: 回调函数
        :param start_dt: 开始时间，缺省为None
        :return: 成功/失败
        """
        sinaBars = []

        try:
            url = u'http://stock.finance.sina.com.cn/futures/api/json.php/InnerFuturesService.getInnerFuturesDailyKLine?symbol={0}'.format(symbol)
            self.strategy.writeCtaLog(u'从sina下载{0}的日K数据 {1}'.format(symbol, url))
            responses = execjs.eval(self.session.get(url).content.decode('gbk'))
            dayVolume = 0

            for item in responses:
                bar = CtaBarData()

                bar.vtSymbol = symbol
                bar.symbol = symbol
                # bar的close time
                bar.datetime = datetime.strptime(item['date'], '%Y-%m-%d')
                if start_dt is not None:
                    if bar.datetime < start_dt:
                        continue

                bar.date = bar.datetime.strftime('%Y%m%d')
                bar.tradingDay = bar.date       # todo: 需要修改，晚上21点后，修改为next workingday
                bar.time = bar.datetime.strftime('%H:%M:00')

                bar.open = float(item['open'])
                bar.high = float(item['high'])
                bar.low = float(item['low'])
                bar.close = float(item['close'])
                bar.volume = int(item['volume'])
                bar.dayVolume = bar.volume

                sinaBars.append(bar)

            if len(sinaBars)>0:
                self.strategy.writeCtaLog(u'从sina读取了{0}条日线K数据'.format(len(sinaBars)))

                # 把sina的bar灌入回调函数
                for bar in sinaBars:
                    callback(bar)

                # 处理完毕，清空
                sinaBars = []

                return True
            else:
                self.strategy.writeCtaLog(u'从sina读取日线K数据失败')
                return False

        except Exception as e:
            self.strategy.writeCtaLog(u'加载Sina历史日线数据失败：'+str(e))
            return False


class TestStrategy(object):

    def __init__(self):
        pass

    def addBar(self, bar):
        print(u'{0},o:{1},h:{2},l:{3},c:{4},v:{5}'.format(bar.datetime, bar.open, bar.high, bar.low, bar.close, bar.volume))

    def addTick(self, tick):
        print(u'{0},{1},ap:{2},av:{3},bp:{4},bv:{5}'.format(tick.datetime, tick.lastPrice, tick.askPrice1, tick.askVolume1, tick.bidPrice1, tick.bidVolume1))

    def writeCtaLog(self, content):
        print(content)

if __name__ == '__main__':
    t = TestStrategy()

    sina = UtilSinaClient(t)

    rt=sina.getDayBars(symbol='RB1810', callback=t.addBar)

    rt = sina.getMinBars(symbol='RB1810',minute = 60, callback=t.addBar)

    #rt = sina.getTicks(symbol='RB1705', callback=t.addTick)

    #rt = sina.getTicks2(symbol='TF1706', callback=t.addTick)
    #rt = sina.getTicks3(symbol='TF1709', callback=t.addTick)

    #rt = sina.getMinBars2(symbol='TF1709',minute=60, callback=t.addBar)