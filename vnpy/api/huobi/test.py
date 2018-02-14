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
	accessKey = '你的accessKey'
	secretKey = '你的secretKey'

	s = Huobi_TradeApi()
	s.init(accessKey, secretKey)
	# s.get_symbols()
	s.get_accounts()
	time.sleep(5)
	# s.get_balance()

	s.spotTrade(symbol = "etcbtc" , price = 1.0 , amount = 0.8 , _type = "sell-limit" , source = "api")

	#s.order_info("575944654")
	# s.orders_list(symbol = "etcbtc" )
	# s.cancel_order("575944654")


	input()


if __name__ == '__main__':
	# socketTest()
    tradeApiTest()