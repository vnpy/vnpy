# flake8: noqa

# 测试 app.cta_strategy_pro.CtaLineBar组件
# 从通达信获取历史交易记录，模拟tick。推送至line_bar

import os
import sys
import json
import traceback
from datetime import datetime, timedelta

vnpy_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..'))
if vnpy_root not in sys.path:
    print(f'sys.path apppend:{vnpy_root}')
    sys.path.append(vnpy_root)

os.environ["VNPY_TESTING"] = "1"

from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.object import BarData
from vnpy.app.cta_strategy_pro.cta_line_bar import (
 CtaLineBar,
 CtaMinuteBar,
 CtaHourBar,
 CtaDayBar,
 CtaWeekBar)
from vnpy.trader.utility import round_to

class test_strategy(object):

    def __init__(self):

        self.price_tick = 1
        self.underlying_symbol = 'I'
        self.vt_symbol = 'I99'

        self.lineM5 = None
        self.lineM30 = None
        self.lineH1 = None
        self.lineH2 = None
        self.lineD = None
        self.lineW = None

        self.TMinuteInterval = 1

        self.save_m30_bars = []
        self.save_h1_bars = []
        self.save_h2_bars = []
        self.save_d_bars = []

        self.save_w_bars = []

    def createM5(self):
        """使用ctalinbar，创建5分钟K线"""
        lineM5Setting = {}
        lineM5Setting['name'] = u'M5'
        lineM5Setting['interval'] = Interval.MINUTE
        lineM5Setting['bar_interval'] = 5
        lineM5Setting['mode'] = CtaLineBar.TICK_MODE
        lineM5Setting['price_tick'] = self.price_tick
        lineM5Setting['underlying_symbol'] = self.underlying_symbol
        self.lineM5 = CtaLineBar(self, self.onBarM5, lineM5Setting)

    def onBarM5(self, bar):
        self.write_log(self.lineM5.get_last_bar_str())

    def createlineM30_with_macd(self):
        """使用CtaLineBar，创建30分钟时间"""
        # 创建M30 K线
        lineM30Setting = {}
        lineM30Setting['name'] = u'M30'
        lineM30Setting['interval'] = Interval.MINUTE
        lineM30Setting['bar_interval'] = 30
        lineM30Setting['para_macd_fast_len'] = 26
        lineM30Setting['para_macd_slow_len'] = 12
        lineM30Setting['para_macd_signal_len'] = 9
        lineM30Setting['price_tick'] = self.price_tick
        lineM30Setting['underlying_symbol'] = self.underlying_symbol
        self.lineM30 = CtaLineBar(self, self.onBarM30MACD, lineM30Setting)

    def onBarM30MACD(self, bar):
        self.write_log(self.lineM30.get_last_bar_str())

    def createLineM30(self):
        """使用ctaMinuteBar, 测试内部自动写入csv文件"""
        # 创建M30 K线
        lineM30Setting = {}
        lineM30Setting['name'] = u'M30'
        lineM30Setting['interval'] = Interval.MINUTE
        lineM30Setting['bar_interval'] = 30
        lineM30Setting['para_pre_len'] = 10
        lineM30Setting['para_ma1_len'] = 5
        lineM30Setting['para_ma2_len'] = 10
        lineM30Setting['para_ma3_len'] = 60
        lineM30Setting['para_active_yb'] = True
        lineM30Setting['para_active_skd'] = True
        lineM30Setting['price_tick'] = self.price_tick
        lineM30Setting['underlying_symbol'] = self.underlying_symbol
        self.lineM30 = CtaMinuteBar(self, self.onBarM30, lineM30Setting)

        # 写入文件
        self.lineM30.export_filename = os.path.abspath(
            os.path.join(os.getcwd(),
                         u'export_{}_{}.csv'.format(self.vt_symbol, self.lineM30.name)))

        self.lineM30.export_fields = [
            {'name': 'datetime', 'source': 'bar', 'attr': 'datetime', 'type_': 'datetime'},
            {'name': 'open', 'source': 'bar', 'attr': 'open_price', 'type_': 'float'},
            {'name': 'high', 'source': 'bar', 'attr': 'high_price', 'type_': 'float'},
            {'name': 'low', 'source': 'bar', 'attr': 'low_price', 'type_': 'float'},
            {'name': 'close', 'source': 'bar', 'attr': 'close_price', 'type_': 'float'},
            {'name': 'turnover', 'source': 'bar', 'attr': 'turnover', 'type_': 'float'},
            {'name': 'volume', 'source': 'bar', 'attr': 'volume', 'type_': 'float'},
            {'name': 'open_interest', 'source': 'bar', 'attr': 'open_interest', 'type_': 'float'},
            {'name': 'kf', 'source': 'line_bar', 'attr': 'line_statemean', 'type_': 'list'}
        ]

    def createLineH1(self):
        # 创建2小时K线
        lineH1Setting = {}
        lineH1Setting['name'] = u'H1'
        lineH1Setting['interval'] = Interval.HOUR
        lineH1Setting['bar_interval'] = 1
        lineH1Setting['para_pre_len'] = 10
        lineH1Setting['para_ema1_len'] = 5
        lineH1Setting['para_ema2_len'] = 10
        lineH1Setting['para_ema3_len'] = 60
        lineH1Setting['para_active_yb'] = True
        lineH1Setting['para_active_skd'] = True
        lineH1Setting['price_tick'] = self.price_tick
        lineH1Setting['underlying_symbol'] = self.underlying_symbol
        self.lineH1 = CtaLineBar(self, self.onBarH1, lineH1Setting)

    def createLineH2(self):
        # 创建2小时K线
        lineH2Setting = {}
        lineH2Setting['name'] = u'H2'
        lineH2Setting['interval'] = Interval.HOUR
        lineH2Setting['bar_interval'] = 2
        lineH2Setting['para_pre_len'] = 5
        lineH2Setting['para_ma1_len'] = 5
        lineH2Setting['para_ma2_len'] = 10
        lineH2Setting['para_ma3_len'] = 18
        lineH2Setting['para_active_yb'] = True
        lineH2Setting['para_active_skd'] = True
        lineH2Setting['mode'] = CtaLineBar.TICK_MODE
        lineH2Setting['price_tick'] = self.price_tick
        lineH2Setting['underlying_symbol'] = self.underlying_symbol
        self.lineH2 = CtaHourBar(self, self.onBarH2, lineH2Setting)

    def createLineD(self):
        # 创建的日K线
        lineDaySetting = {}
        lineDaySetting['name'] = u'D1'
        lineDaySetting['bar_interval'] = 1
        lineDaySetting['para_pre_len'] = 5
        lineDaySetting['para_art1_len'] = 26
        lineDaySetting['para_ma1_len'] = 5
        lineDaySetting['para_ma2_len'] = 10
        lineDaySetting['para_ma3_len'] = 18
        lineDaySetting['para_active_yb'] = True
        lineDaySetting['para_active_skd'] = True
        lineDaySetting['price_tick'] = self.price_tick
        lineDaySetting['underlying_symbol'] = self.underlying_symbol
        self.lineD = CtaDayBar(self, self.onBarD, lineDaySetting)

    def createLineW(self):
        """创建周线"""
        lineWeekSetting = {}
        lineWeekSetting['name'] = u'W1'
        lineWeekSetting['para_pre_len'] = 5
        lineWeekSetting['para_art1_len'] = 26
        lineWeekSetting['para_ma1_len'] = 5
        lineWeekSetting['para_ma2_len'] = 10
        lineWeekSetting['para_ma3_len'] = 18
        lineWeekSetting['para_active_yb'] = True
        lineWeekSetting['para_active_skd'] = True
        lineWeekSetting['mode'] = CtaDayBar.TICK_MODE
        lineWeekSetting['price_tick'] = self.price_tick
        lineWeekSetting['underlying_symbol'] = self.underlying_symbol
        self.lineW = CtaWeekBar(self, self.onBarW, lineWeekSetting)

    def onBar(self, bar):
        # print(u'tradingDay:{},dt:{},o:{},h:{},l:{},c:{},v:{}'.format(bar.trading_day,bar.datetime, bar.open, bar.high, bar.low_price, bar.close_price, bar.volume))
        if self.lineW:
            self.lineW.add_bar(bar, bar_freq=self.TMinuteInterval)
        if self.lineD:
            self.lineD.add_bar(bar, bar_freq=self.TMinuteInterval)
        if self.lineH2:
            self.lineH2.add_bar(bar, bar_freq=self.TMinuteInterval)

        if self.lineH1:
            self.lineH1.add_bar(bar, bar_freq=self.TMinuteInterval)

        if self.lineM30:
            self.lineM30.add_bar(bar, bar_freq=self.TMinuteInterval)

        if self.lineM5:
            self.lineM5.add_bar(bar, bar_freq=self.TMinuteInterval)

        # if self.lineH2:
        #    self.lineH2.skd_is_high_dead_cross(runtime=True, high_skd=30)
        #    self.lineH2.skd_is_low_golden_cross(runtime=True, low_skd=70)

    def onBarM30(self, bar):
        self.write_log(self.lineM30.get_last_bar_str())

        self.save_m30_bars.append({
            'datetime': bar.datetime,
            'open': bar.open_price,
            'high': bar.high_price,
            'low': bar.low_price,
            'close': bar.close_price,
            'turnover': 0,
            'volume': bar.volume,
            'open_interest': 0,
            'ma5': self.lineM30.line_ma1[-1] if len(self.lineM30.line_ma1) > 0 else bar.close_price,
            'ma10': self.lineM30.line_ma2[-1] if len(self.lineM30.line_ma2) > 0 else bar.close_price,
            'ma60': self.lineM30.line_ma3[-1] if len(self.lineM30.line_ma3) > 0 else bar.close_price,
            'sk': self.lineM30.line_sk[-1] if len(self.lineM30.line_sk) > 0 else 0,
            'sd': self.lineM30.line_sd[-1] if len(self.lineM30.line_sd) > 0 else 0
        })

    def onBarH1(self, bar):
        self.write_log(self.lineH1.get_last_bar_str())

        self.save_h1_bars.append({
            'datetime': bar.datetime,
            'open': bar.open_price,
            'high': bar.high_price,
            'low': bar.low_price,
            'close': bar.close_price,
            'turnover': 0,
            'volume': bar.volume,
            'open_interest': 0,
            'ema5': self.lineH1.line_ema1[-1] if len(self.lineH1.line_ema1) > 0 else bar.close_price,
            'ema10': self.lineH1.line_ema2[-1] if len(self.lineH1.line_ema2) > 0 else bar.close_price,
            'ema60': self.lineH1.line_ema3[-1] if len(self.lineH1.line_ema3) > 0 else bar.close_price,
            'sk': self.lineH1.line_sk[-1] if len(self.lineH1.line_sk) > 0 else 0,
            'sd': self.lineH1.line_sd[-1] if len(self.lineH1.line_sd) > 0 else 0
        })

    def onBarH2(self, bar):
        self.write_log(self.lineH2.get_last_bar_str())

        self.save_h2_bars.append({
            'datetime': bar.datetime,
            'open': bar.open_price,
            'high': bar.high_price,
            'low': bar.low_price,
            'close': bar.close_price,
            'turnover': 0,
            'volume': bar.volume,
            'open_interest': 0,
            'ma5': self.lineH2.line_ma1[-1] if len(self.lineH2.line_ma1) > 0 else bar.close_price,
            'ma10': self.lineH2.line_ma2[-1] if len(self.lineH2.line_ma2) > 0 else bar.close_price,
            'ma18': self.lineH2.line_ma3[-1] if len(self.lineH2.line_ma3) > 0 else bar.close_price,
            'sk': self.lineH2.line_sk[-1] if len(self.lineH2.line_sk) > 0 else 0,
            'sd': self.lineH2.line_sd[-1] if len(self.lineH2.line_sd) > 0 else 0
        })

    def onBarD(self, bar):
        self.write_log(self.lineD.get_last_bar_str())
        self.save_d_bars.append({
            'datetime': bar.datetime,
            'open': bar.open_price,
            'high': bar.high_price,
            'low': bar.low_price,
            'close': bar.close_price,
            'turnover': 0,
            'volume': bar.volume,
            'open_interest': 0,
            'ma5': self.lineD.line_ma1[-1] if len(self.lineD.line_ma1) > 0 else bar.close_price,
            'ma10': self.lineD.line_ma2[-1] if len(self.lineD.line_ma2) > 0 else bar.close_price,
            'ma18': self.lineD.line_ma3[-1] if len(self.lineD.line_ma3) > 0 else bar.close_price,
            'sk': self.lineD.line_sk[-1] if len(self.lineD.line_sk) > 0 else 0,
            'sd': self.lineD.line_sd[-1] if len(self.lineD.line_sd) > 0 else 0
        })

    def onBarW(self, bar):
        self.write_log(self.lineW.get_last_bar_str())
        self.save_w_bars.append({
            'datetime': bar.datetime,
            'open': bar.open_price,
            'high': bar.high_price,
            'low': bar.low_price,
            'close': bar.close_price,
            'turnover': 0,
            'volume': bar.volume,
            'open_interest': 0,
            'ma5': self.lineW.line_ma1[-1] if len(self.lineW.line_ma1) > 0 else bar.close_price,
            'ma10': self.lineW.line_ma2[-1] if len(self.lineW.line_ma2) > 0 else bar.close_price,
            'ma18': self.lineW.line_ma3[-1] if len(self.lineW.line_ma3) > 0 else bar.close_price,
            'sk': self.lineW.line_sk[-1] if len(self.lineW.line_sk) > 0 else 0,
            'sd': self.lineW.line_sd[-1] if len(self.lineW.line_sd) > 0 else 0
        })

    def on_tick(self, tick):
        print(u'{0},{1},ap:{2},av:{3},bp:{4},bv:{5}'.format(tick.datetime, tick.last_price, tick.ask_price_1,
                                                            tick.ask_volume_1, tick.bid_price_1, tick.bid_volume_1))

    def write_log(self, content):
        print(content)

    def saveData(self):

        if len(self.save_m30_bars) > 0:
            outputFile = '{}_m30.csv'.format(self.vt_symbol)
            with open(outputFile, 'w', encoding='utf8', newline='') as f:
                fieldnames = ['datetime', 'open', 'high', 'low', 'close', 'turnover', 'volume', 'open_interest',
                              'ma5', 'ma10', 'ma60', 'sk', 'sd']
                writer = csv.DictWriter(f=f, fieldnames=fieldnames, dialect='excel')
                writer.writeheader()
                for row in self.save_m30_bars:
                    writer.writerow(row)

        if len(self.save_h1_bars) > 0:
            outputFile = '{}_h1.csv'.format(self.vt_symbol)
            with open(outputFile, 'w', encoding='utf8', newline='') as f:
                fieldnames = ['datetime', 'open', 'high', 'low', 'close', 'turnover', 'volume', 'open_interest',
                              'ema5', 'ema10', 'ema60', 'sk', 'sd']
                writer = csv.DictWriter(f=f, fieldnames=fieldnames, dialect='excel')
                writer.writeheader()
                for row in self.save_h1_bars:
                    writer.writerow(row)

        if len(self.save_h2_bars) > 0:
            outputFile = '{}_h2.csv'.format(self.vt_symbol)
            with open(outputFile, 'w', encoding='utf8', newline='') as f:
                fieldnames = ['datetime', 'open', 'high', 'low', 'close', 'turnover', 'volume', 'open_interest',
                              'ma5', 'ma10', 'ma18', 'sk', 'sd']
                writer = csv.DictWriter(f=f, fieldnames=fieldnames, dialect='excel')
                writer.writeheader()
                for row in self.save_h2_bars:
                    writer.writerow(row)

        if len(self.save_d_bars) > 0:
            outputFile = '{}_d.csv'.format(self.vt_symbol)
            with open(outputFile, 'w', encoding='utf8', newline='') as f:
                fieldnames = ['datetime', 'open', 'high', 'low', 'close', 'turnover', 'volume', 'open_interest',
                              'ma5', 'ma10', 'ma18', 'sk', 'sd']
                writer = csv.DictWriter(f=f, fieldnames=fieldnames, dialect='excel')
                writer.writeheader()
                for row in self.save_d_bars:
                    writer.writerow(row)

        if len(self.save_w_bars) > 0:
            outputFile = '{}_w.csv'.format(self.vt_symbol)
            with open(outputFile, 'w', encoding='utf8', newline='') as f:
                fieldnames = ['datetime', 'open', 'high', 'low', 'close', 'turnover', 'volume', 'open_interest',
                              'ma5', 'ma10', 'ma18', 'sk', 'sd']
                writer = csv.DictWriter(f=f, fieldnames=fieldnames, dialect='excel')
                writer.writeheader()
                for row in self.save_w_bars:
                    writer.writerow(row)


if __name__ == '__main__':
    t = test_strategy()
    t.price_tick = 0.5
    t.underlying_symbol = 'J'
    t.vt_symbol = 'J99'

    # t.createM5()
    # t.createLineW()

    # t.createlineM30_with_macd()

    # 创建M30线
    # t.createLineM30()

    # 回测1小时线
    # t.createLineH1()

    # 回测2小时线
    # t.createLineH2()

    # 回测日线
    # t.createLineD()

    # 测试周线
    t.createLineW()

    # vnpy/app/cta_strategy_pro/
    vnpy_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..'))

    filename = os.path.abspath(os.path.join(vnpy_root, 'bar_data/{}_20160101_1m.csv'.format(t.vt_symbol)))
    csv_bar_seconds = 60  # csv 文件内，bar的时间间隔60秒

    import csv

    csvfile = open(filename, 'r', encoding='utf8')
    reader = csv.DictReader((line.replace('\0', '') for line in csvfile), delimiter=",")
    last_tradingDay = None
    for row in reader:
        try:
            dt = datetime.strptime(row['datetime'], '%Y-%m-%d %H:%M:%S') - timedelta(seconds=csv_bar_seconds)

            bar = BarData(
                gateway_name='',
                symbol=t.vt_symbol,
                exchange=Exchange.LOCAL,
                datetime=dt,
                interval=Interval.MINUTE,
                open_price=round_to(float(row['open']), t.price_tick),
                high_price=round_to(float(row['high']), t.price_tick),
                low_price=round_to(float(row['low']), t.price_tick),
                close_price=round_to(float(row['close']), t.price_tick),
                volume=float(row['volume'])
            )

            if 'trading_date' in row:
                bar.trading_day = row['trading_date']
                if len(bar.trading_day) == 8 and '-' not in bar.trading_day:
                    bar.trading_day = bar.trading_day[0:4] + '-' + bar.trading_day[4:6] + '-' + bar.trading_day[6:8]
            else:
                if bar.datetime.hour >= 21:
                    if bar.datetime.isoweekday() == 5:
                        # 星期五=》星期一
                        bar.trading_day = (dt + timedelta(days=3)).strftime('%Y-%m-%d')
                    else:
                        # 第二天
                        bar.trading_day = (dt + timedelta(days=1)).strftime('%Y-%m-%d')
                elif bar.datetime.hour < 8 and bar.datetime.isoweekday() == 6:
                    # 星期六=>星期一
                    bar.trading_day = (dt + timedelta(days=2)).strftime('%Y-%m-%d')
                else:
                    bar.trading_day = bar.datetime.strftime('%Y-%m-%d')

            t.onBar(bar)
            # 测试 实时计算值
            # sk, sd = t.lineM30.getRuntimeSKD()

            # 测试实时计算值
            # if bar.datetime.minute==1:
            #    print('rt_Dif:{}'.format(t.lineM30.rt_Dif))
        except Exception as ex:
            t.write_log(u'{0}:{1}'.format(Exception, ex))
            traceback.print_exc()
            break

    t.saveData()
