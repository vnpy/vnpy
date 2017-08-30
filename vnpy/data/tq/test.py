# encoding: UTF-8


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
    api = TqApi()
    
    api.connect()
    
    api.subscribe_quote(["RM801"], onQuote)
    api.subscribe_chart("RM801", 0, 100, onChart)
    
    raw_input()
    
    
    
    