#!/usr/bin/python
# encoding: UTF-8
import urllib,json
import pandas as pd
import numpy as np


class hist():
    def __init__(self):
        self.data = None

    def get_K_data(self, symbol, period='1d'):
        if period == '1d':
            url = 'http://stock2.finance.sina.com.cn/futures/api/json.php/IndexService.getInnerFuturesDailyKLine?symbol=%s' % symbol
            fp = urllib.urlopen(url)
            jsonData = json.loads(fp.read())
            self.data = pd.DataFrame(jsonData, columns=['date', 'open', 'high', 'low', 'close', 'volume'], dtype=float)
        elif period == '5m' or period == '15m' or period == '30m' or period == '60m':
            url = 'http://stock2.finance.sina.com.cn/futures/api/json.php/IndexService.getInnerFuturesMiniKLine%s?symbol=%s' % (period, symbol)
            fp = urllib.urlopen(url)
            jsonData = json.loads(fp.read())
            jsonData.reverse()
            self.data = pd.DataFrame(jsonData, columns=['date', 'open', 'high', 'low', 'close', 'volume'], dtype=float)
        else:
            pass

    def get_ma(self, maList):
        for ma in maList:
            self.data['ma' + str(ma)] = self.data['close'].rolling(window=ma,center=False).mean()

    def get_ema(self, maList):
        for ma in maList:
            self.data['ema' + str(ma)] = self.data['close'].ewm(ignore_na=False,span=ma,min_periods=0,adjust=True).mean()

    def get_adx(self, n=14, m=6):

        df = self.data.copy()

        # 计算HD和LD值
        df['hd'] = df['high'] - df['high'].shift(1)
        df['ld'] = df['low'].shift(1) - df['low']

        # 计算TR值
        df['t1'] = df['high'] - df['low']
        df['t2'] = abs(df['high'] - df['close'].shift(1))
        df.ix[df['t1'] >= df['t2'], 'temp1'] = df['t1']
        df.ix[df['t1'] < df['t2'], 'temp1'] = df['t2']

        df['temp2'] = abs(df['low'] - df['close'].shift(1))

        df.ix[df['temp1'] >= df['temp2'], 'temp'] = df['temp1']
        df.ix[df['temp1'] < df['temp2'], 'temp'] = df['temp2']

        df.dropna(inplace=True)

        df['tr'] = df['temp'].rolling(window=n,center=False).sum()

        df.ix[(df['hd'] > 0) & (df['hd'] > df['ld']), 'hd1'] = df['hd']
        df['hd1'].fillna(0, inplace=True)

        df.ix[(df['ld'] > 0) & (df['ld'] > df['hd']), 'ld1'] = df['ld']
        df['ld1'].fillna(0, inplace=True)

        df['dmp'] = df['hd1'].rolling(window=n,center=False).sum()
        df['dmm'] = df['ld1'].rolling(window=n,center=False).sum()

        df['pdi'] = df['dmp'] / df['tr'] * 100
        df['mdi'] = df['dmm'] / df['tr'] * 100
        df['adx'] = (abs(df['mdi'] - df['pdi']) / (df['mdi'] + df['pdi']) *  100).rolling(window=m,center=False).mean()

        self.data['pdi'] = df['pdi'].copy()
        self.data['mdi'] = df['mdi'].copy()
        self.data['adx'] = df['adx'].copy()

    def get_macd(self, s=12, l=26, m=9):
        ema12 = self.data['close'].ewm(ignore_na=False, span=s, min_periods=0, adjust=True).mean()
        ema26 = self.data['close'].ewm(ignore_na=False, span=l, min_periods=0, adjust=True).mean()
        self.data['diff'] = ema12 - ema26
        self.data['dea'] = self.data['diff'].ewm(ignore_na=False, span=m, min_periods=0, adjust=True).mean()
        self.data['macd'] = (self.data['diff'] - self.data['dea']) * 2

    def getMode(self, symbol):
        self.get_K_data(symbol)
        self.get_macd()
        self.data.ix[self.data['macd'] >= self.data['macd'].shift(1), 'mode'] = 1
        self.data.ix[self.data['macd'] < self.data['macd'].shift(1), 'mode'] = 0
        return list(self.data['mode'])[-1]