# encoding: UTF-8


import requests

HTTP_OK = 200

PERIOD_1MIN = '1m'
PERIOD_5MIN = '5m'
PERIOD_15MIN = '15m'
PERIOD_60MIN = '60m'
PERIOD_1DAY = '1d'


########################################################################
class ShcifcoApi(object):
    """数据接口"""

    #----------------------------------------------------------------------
    def __init__(self, ip, port, token):
        """Constructor"""
        self.ip = ip
        self.port = port
        self.token = token

        self.service = 'shcifco/dataapi'
        self.domain = 'http://' + ':'.join([self.ip, self.port])
    
    #----------------------------------------------------------------------
    def getData(self, path, params):
        """下载数据"""
        url = '/'.join([self.domain, self.service, path])
        params['token'] = self.token
        r = requests.get(url=url, params=params)
        
        if r.status_code != HTTP_OK:
            print u'http请求失败，状态代码%s' %r.status_code
            return None
        else:
            return r.text
    
    #----------------------------------------------------------------------
    def getLastTick(self, symbol):
        """获取最新Tick"""
        path = 'lasttick'
        params = {'ids': symbol}
        
        data = self.getData(path, params)
        if not data or data == ';':
            return None
        
        data = data.split(';')[0]
        l = data.split(',')
        d = {
            'symbol': l[0],
            'lastPrice': float(l[1]),
            'bidPrice': float(l[2]),
            'bidVolume': int(l[3]),
            'askPrice': float(l[4]),
            'askVolume': int(l[5]),
            'volume': int(l[6]),
            'openInterest': int(float(l[7]))
        }
        return d
    
    #----------------------------------------------------------------------
    def getLastPrice(self, symbol):
        """获取最新成交价"""
        path = 'lastprice'
        params = {'ids': symbol}
        
        data = self.getData(path, params)
        if not data:
            return None
        
        data = data.split(';')[0]
        price = float(data)
        return price
    
    #----------------------------------------------------------------------
    def getLastBar(self, symbol):
        """获取最新的一分钟K线数据"""
        path = 'lastbar'
        params = {'id': symbol}
        
        data = self.getData(path, params)
        if not data:
            return None
        
        data = data.split(';')[0]
        l = data.split(',')
        d = {
            'symbol': l[0],
            'time': l[1],
            'open': float(l[2]),
            'high': float(l[3]),
            'low': float(l[4]),
            'close': float(l[5]),
            'volume': int(l[6]),
            'openInterest': int(float(l[7]))
        }
        return d
    
    #----------------------------------------------------------------------
    def getHisBar(self, symbol, num, date='', period=''):
        """获取历史K线数据"""
        path = 'hisminbar'
        
        # 默认参数
        params = {
            'id': symbol,
            'num': num
        }
        # 可选参数
        if date:
            params['tradingday'] = date
        if period:
            params['period'] = period
        
        data = self.getData(path, params)
        if not data:
            return None
        
        barList = []        
        l = data.split(';')
        
        for barStr in l:
            # 过滤某些空数据
            if ',' not in barStr:
                continue
            
            barData = barStr.split(',')
            d = {
                'symbol': barData[0],
                # 'date': barData[1],   # trading day
                'time': barData[2],
                'open': float(barData[3]),
                'high': float(barData[4]),
                'low': float(barData[5]),
                'close': float(barData[6]),
                'volume': int(barData[7]),
                'openInterest': int(float(barData[8])),
                'date': barData[9]  # natural day
            }
            barList.append(d)
            
        return barList

