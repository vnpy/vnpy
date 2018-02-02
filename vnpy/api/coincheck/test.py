# encoding: utf-8

from vncoincheck import *

def testTrade():
    """测试交易"""
    accessKey = '你的accessKey'
    secretKey = '你的secretKey'
    
    # 创建API对象并初始化
    api = TradeApi()
    api.DEBUG = True
    api.init(accessKey, secretKey)
    
    # 查询账户，测试通过
    #api.get_info()

    # api.get_info()
    #api.get_balance()
    # api.get_balance()
    
    #api.buy_btc_jpy(rate = 200 , amount = 0.005)

    #api.cancel_orders("439397799")

    for i in range(10):
        api.buy_btc_jpy(rate = 200 , amount = 0.005)
        #api.sell_btc_jpy(rate = 200000 , amount = 0.005)
        
        #orders = api.list_orders()

        #sleep(3)
        # for d in orders:
        #     api.cancel_orders( d["id"])

        #sleep(0.3)

    # 查询委托，测试通过
    #api.active_orders( currency_pair = SYMBOL_BTCJPY )
    
    # 阻塞
    input()    


def testData():
    """测试行情接口"""
    api = DataApi()
    
    api.init(0.5 , 1)
    
    # 订阅成交推送，测试通过
    # api.subscribeTick(SYMBOL_BTCJPY)
    # 订阅成交记录
    # api.subscribeTrades(SYMBOL_BTCJPY)
    # # 订阅十档行情
    api.subscribeOrderbooks(SYMBOL_BTCJPY)

    
    input()
    
    
if __name__ == '__main__':
    testTrade()
    #testTrade()
    #testData()