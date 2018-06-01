# encoding: utf-8

from vnhuobi import Huobi_DataApiSocket , Huobi_TradeApi, Huobi_DataApi

import time

'''
socketTest
'''
def socketTest():
    s = Huobi_DataApiSocket()

    s.connect("wss://api.huobipro.com/ws")

    # s.sendTickerRequest("eth_usdt")

    s.sendOrderbookRequest("eth_btc")


'''
DataApi
'''
def dataApiTest():
    s = Huobi_DataApi()

    symbol = "eth_usdt"
    s.init(0.5 , 1)
    s.subscribeTick(symbol)
    s.subscribeOrderbooks(symbol)
    s.subscribeTrades(symbol)

'''
TradeApi
'''
def tradeApiTest():
    accessKey = ''
    secretKey = ''

    s = Huobi_TradeApi()
    s.init(accessKey, secretKey)
    # s.get_symbols()
    # s.get_accounts()
    time.sleep(5)
    # s.get_balance()

    # s.spotTrade(symbol = "etcbtc" , price = 0 , amount = 1 , _type = "buy-limit" , source = "api")

    # s.order_info("2940698220")
    # s.orders_list(symbol = "etcbtc" )
    s.cancel_order("2940698221")


    input()


if __name__ == '__main__':
    # socketTest()
    # dataApiTest()
    tradeApiTest()
    input()