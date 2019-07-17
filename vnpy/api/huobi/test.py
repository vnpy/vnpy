# encoding: utf-8

from vnhuobi import *
from time import sleep
#----------------------------------------------------------------------
def testTrade():
    """测试交易"""
    accessKey = 'dbd1c2e7-74bd66ce-e9e35409-qv2d5ctgbn'
    secretKey = '6d92f24c-f6029b0e-062b02fe-dcd78'
    
    # 创建API对象并初始化
    api = TradeApi()
    api.DEBUG = True
    api.init(HUOBI_API_HOST,accessKey, secretKey)
    api.start()
    # 查询账户，测试通过
    api.getAccounts()
    
    # 查询委托，测试通过
    #api.getOrders()
    
    # 买入，测试通过
    #api.buy(7100, 0.0095)
    
    # 卖出，测试通过
    #api.sell(7120, 0.0095)
    
    # 撤单，测试通过
    #api.cancelOrder(3915047376L)
    
    # 查询杠杆额度，测试通过
    #api.getLoanAvailable()
    
    # 查询杠杆列表，测试通过
    #api.getLoans()

    # 查询成交记录
    api.getMatchResults(symbol='ltcusdt')
    # 阻塞
    while(1):
        sleep(1)


#----------------------------------------------------------------------
def testData():
    """测试行情接口"""
    api = DataApi()
    
    api.connect(url = 'wss://api.huobi.pro/ws')
    
    # 订阅成交推送，测试通过
    #api.subscribeTick(SYMBOL_BTCCNY)
    
    # 订阅报价推送，测试通过
    #api.subscribeQuote(SYMBOL_BTCCNY)

    # 订阅深度推送，测试通过
    api.subscribeMarketDepth('btcusdt')

    # 查询K线数据，测试通过
    #data = api.getKline(SYMBOL_BTCCNY, PERIOD_1MIN, 100)
    #print(data)
    
    while(1):
        sleep(1)
    
    
if __name__ == '__main__':
    testTrade()
    
    #testData()