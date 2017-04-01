# encoding: UTF-8

from __future__ import print_function

'''一个简单的SINA数据客户端，主要使用requests开发'''
import requests
from time import sleep
import execjs
from datetime import datetime,timedelta
from ctaBase import CtaBarData,CtaTickData

class SinaClient(object):

    # ----------------------------------------------------------------------
    def __init__(self, strategy):

        self.strategy = strategy

        requests.adapters.DEFAULT_RETRIES = 5
        self.session = requests.session()
        self.session.keep_alive = False

    def getTicks(self, symbol, callback):

        # 从sina加载最新的M1数据
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


    def getMinBars(self, symbol, minute, callback):
        """# 从sina加载最新的M5,M15,M30,M60数据"""

        if minute not in {5, 15, 30, 60}:
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

    def getDayBars(self, symbol, callback):
        """# 从sina加载最新的Day数据"""

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

    sina = SinaClient(t)

    #rt=sina.getDayBars(symbol='RB1705', callback=t.addBar)

    #rt = sina.getMinBars(symbol='RB1705',minute = 5, callback=t.addBar)

    rt = sina.getTicks(symbol='RB1705', callback=t.addTick)

