# encoding: UTF-8


import requests

HTTP_OK = 200


########################################################################
class ShcifcoApi(object):
    """数据接口"""

    #----------------------------------------------------------------------
    def __init__(self, ip, port, token):
        """Constructor"""
        self.ip = ip
        self.port = port
        self.token = token
        
        self.service = 'ShcifcoApi'
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
        
        l = data.split(',')
        d = {
            'symbol': l[0],
            'lastPrice': float(l[1]),
            'bidPrice': float(l[2]),
            'bidVolume': int(l[3]),
            'askPrice': float(l[4]),
            'askVolume': int(l[5]),
            'volume': int(l[6]),
            'openInterest': int(l[7])
        }
        return d
    
    #----------------------------------------------------------------------
    def getLastPrice(self, symbol):
        """获取最新成交价"""
        path = 'lastprice'
        params = {'ids': symbol}
        data = self.getData(path, params)
        
        price = float(data)
        return price
    
    #----------------------------------------------------------------------
    def getLastBar(self, symbol):
        """获取最新的一分钟K线数据"""
        path = 'lastbar'
        params = {'ids': symbol}
        data = self.getData(path, params)
        
        l = data.split(',')
        d = {
            'symbol': l[0],
            'time': l[1],
            'open': float(l[2]),
            'high': float(l[3]),
            'low': float(l[4]),
            'close': float(l[5]),
            'volume': int([6])
        }
        return d
    
    #----------------------------------------------------------------------
    def getHisBar(self, symbol, num, date='', period=''):
        """获取历史K线数据"""
        path = 'lastbar'
        
        # 默认参数
        params = {
            'ids': symbol,
            'num': num
        }
        # 可选参数
        if date:
            params[date] = date
        if period:
            params[period] = period
        
        data = self.getData(path, params)
        
        barList = []        
        l = data.split(';')
        
        for barStr in l:
            barData = barStr.split(',')
            d = {
                'symbol': barData[0],
                'time': barData[1],
                'open': float(barData[2]),
                'high': float(barData[3]),
                'low': float(barData[4]),
                'close': float(barData[5]),
                'volume': int([6])
            }
            barList.append(d)
            
        return barList
        
    
if __name__ == "__main__":
    ip = '101.231.179.199'
    port  = '10102'
    token = 'testd2cda34b2d317779e812eb84ee4224a6_123456'
    
    api = ShcifcoApi(ip, port, token)
    api.getData(path, params)
    
    print api.getLastTick('cu1709')
    
    print api.getLastPrice('cu1709')
    
    print api.getLastBar('cu1709')
    
    print api.getHisBar('cu1709', 50)
    
    