# encoding: UTF-8

from time import sleep

from vntq import TqApi


# 接口对象
api = None


#----------------------------------------------------------------------
def onQuote(symbol):
    """Tick更新"""
    print '-' * 30
    print 'onQuote'
    quote = api.get_quote(symbol)
    print quote

#----------------------------------------------------------------------
def onChart(symbol, seconds):
    """K线更新"""
    print '-' * 30
    print 'onChart'
    
    if seconds == 0:
        serial = api.get_tick_serial(symbol)
    else:
        serial = api.get_kline_serial(symbol, seconds)
        
    print serial
    

if __name__ == "__main__":
    symbol = 'IF1710'
    
    api = TqApi()
    
    api.connect()
    
    # 订阅Tick推送
    #api.subscribe_quote([symbol], onQuote)
    
    # 订阅Tick图表
    #api.subscribe_chart(symbol, 0, 100, onChart)
    
    # 订阅K线图表
    api.subscribe_chart(symbol, 60, 1000, onChart)
    
    raw_input()
    
    
    
    