# encoding: UTF-8

from __future__ import absolute_import
from .vnkorbit import Korbit_TradeApi , Korbit_DataApi

apiKey = 'FssV9Jw0aZVCOYbu9YlqVNc2Rhgmh1QpruNgSVhvVmFP1iw1aPfc3APbfz0ZM'
secretKey = 'lSMc1TT2AZYX5pyEm01SFqx7PgMjNB18eXWpi8DQKHf0rcYhLiaiRVzJwaVZR'


def testData():
	d = Korbit_DataApi()

	d.init(0.5 , 1)
	d.subscribeTick("btc_krw")

	# d.subscribeTrades("btc_krw")

	# d.subscribeOrderbooks("btc_krw")


def testTrade():
	global apiKey , secretKey
	d = Korbit_TradeApi()
	d.init(apiKey , secretKey , "xiaoshuang8921@naver.com" , "Wxiaoshuang8921")

	# print d.headers
	d.list_market_orders(currency_pair = 'bch_krw' , offset = 0 , limit = 10)
	#print d.buy_currency( coin_amount = 0.01 , price = 10000 , currency_pair = 'bch_krw')

	#print d.sell_currency( coin_amount = 0.01 , price = 10000000 , currency_pair = 'bch_krw')
	# 4441418
	#print d.cancel_orders( order_id = 4441418 , currency_pair = 'bch_krw')

# testData()
testTrade()