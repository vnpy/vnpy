# encoding: utf-8

from vngate import Gate_DataApi , Gate_TradeApi

import time

'''
TradeApi
'''
def tradeApiTest():
	# 13738045524
	accessKey = ''
	secretKey = ''

	# 18304011249
	accessKey = ''
	secretKey = ''

	s = Gate_TradeApi()
	s.init(accessKey , secretKey )

	# s.get_market_info()
	#s.get_symbols()
	# 
	# s.get_balance()

	# {"result":"true","message":"Success","code":0,"orderNumber":485615069}
	# {"result":"false","message":"Your order size is too small. The minimum is 0.001 BTC","code":20}
	# s.spotBuy( "bcd_btc", 0.000200 , 6)
	# s.spotSell( "bcd_btc", 0.000600 , 2)


	# s.cancel_order("bcd_btc" , "489517160" )
	# s.cancel_order("bcd_btc" , "489533981" )
	'''
	{"result":"true","orders":
	[{"orderNumber":"485615832","type":"buy","rate":0.0002,"amount":"6","total":"0.0012","initialRate":0.0002,
	"initialAmount":"6","filledRate":0,"filledAmount":0,"currencyPair":"bcd_btc","timestamp":"1521430395","status":"open"},
	{"orderNumber":"485615840","type":"sell","rate":0.0006,"amount":"2","total":"0.0012","initialRate":0.0006,"initialAmount":"2",
	"filledRate":0,"filledAmount":0,"currencyPair":"bcd_btc","timestamp":"1521430396","status":"open"}],
	"message":"Success","code":0,"elapsed":"3.045ms"}

	{u'elapsed': u'3.207ms', u'message': u'Success', u'code': 0, u'result': u'true',
 u'orders': [{u'status': u'open', u'filledRate': 0, u'orderNumber': u'489517146'
, u'timestamp': u'1521682618', u'amount': u'6', u'filledAmount': 0, u'rate': 0.0
002, u'initialAmount': u'6', u'initialRate': 0.0002, u'total': u'0.0012', u'type
': u'buy', u'currencyPair': u'bcd_btc'}, {u'status': u'open', u'filledRate': 0,
u'orderNumber': u'489517169', u'timestamp': u'1521682619', u'amount': u'2', u'fi
lledAmount': 0, u'rate': 0.0006, u'initialAmount': u'2', u'initialRate': 0.0006,
 u'total': u'0.0012', u'type': u'sell', u'currencyPair': u'bcd_btc'}]}

 {u'elapsed': u'0.595ms', u'message': u'Success', u'code': 0, u'result': u'true',
 u'orders': []}
	'''
	# s.listOpenOrders()

	'''
	{u'elapsed': u'1.107ms', u'message': u'Success', u'code': 0, u'result': u'true',
 u'order': {u'status': u'cancelled', u'feeValue': u'0.00000000', u'filledRate':
0, u'orderNumber': u'489517146', u'timestamp': u'1521682618', u'feeCurrency': u'
BTC', u'amount': u'6', u'filledAmount': 0, u'rate': 0.0002, u'fee': u'0.00000000
 BTC', u'currencyPair': u'bcd_btc', u'initialRate': 0.0002, u'type': u'buy', u'f
eePercentage': 0.2, u'initialAmount': u'6'}}

	{u'message': u'Error: invalid order id or order cancelled.', u'code': 17, u'resu
lt': u'false'}

{u'elapsed': u'4.033ms', u'message': u'Success', u'code': 0, u'result': u'true',
 u'order': {u'status': u'open', u'feeValue': u'0.00000000', u'filledRate': 0, u'
orderNumber': u'489533981', u'timestamp': u'1521683681', u'feeCurrency': u'BCD',
 u'amount': u'2', u'filledAmount': 0, u'rate': 0.0006, u'fee': u'0.00000000 BCD'
, u'currencyPair': u'bcd_btc', u'initialRate': 0.0006, u'type': u'sell', u'feePe
rcentage': 0.2, u'initialAmount': u'2'}}


{u'elapsed': u'67.899ms', u'message': u'Success', u'code': 0, u'result': u'true'
, u'order': {u'status': u'closed', u'feeValue': u'0.00600000', u'filledRate': u'
0.000341', u'orderNumber': u'489598077', u'timestamp': u'1521687452', u'feeCurre
ncy': u'BCD', u'amount': u'0', u'filledAmount': 3, u'rate': 0.000341, u'fee': u'
0.00600000 BCD', u'currencyPair': u'bcd_btc', u'initialRate': 0.000341, u'type':
 u'sell', u'feePercentage': 0.2, u'initialAmount': u'3'}}
	'''


	s.getOrder("ae_btc", "700712022")
	# s.getOrder("ruff_eth" , "533574442")
	# s.getOrder("ruff_eth" , "533746370")

	# s.listTradeHistory( "ruff_eth" , "533574442")
	# s.listTradeHistory( "ruff_eth" )
	
	# s.getOrder("bcd_btc" , "489517160")

	'''
	{"result":true,"code":0,"message":"Success"}
	'''
	# s.cancel_order( "bcd_btc" , "485615832")
	# s.cancel_order( "bcd_btc" , "485615840")

	'''
	{"result":"true",
	"order":{"orderNumber":"485632415","status":"open","currencyPair":"bcd_btc","type":"buy","rate":0.0002,"amount":"6",
	"initialRate":0.0002,"initialAmount":"6","filledAmount":0,"filledRate":0,"feePercentage":0.2,"feeValue":"0.00000000",
	"feeCurrency":"BTC","fee":"0.00000000 BTC","timestamp":"1521431558"},"message":"Success","code":0,"elapsed":"4.837ms"}

	{"result":"true","order":{"orderNumber":"485632415","status":"cancelled","currencyPair":"bcd_btc","type":"buy",
	"rate":0.0002,"amount":"6","initialRate":0.0002,"initialAmount":"6","filledAmount":0,"filledRate":0,"feePercentage":0.2,
	"feeValue":"0.00000000","feeCurrency":"BTC","fee":"0.00000000 BTC","timestamp":"1521431558"},"message":"Success","code":0,
	"elapsed":"7.796ms"}
	'''
	# s.getOrder( "bcd_btc" , "485632415")


	'''
	{"result":"false","code":16,"message":"Error: invalid order id or order is already closed."}
	'''
	# s.cancel_order( "bcd_btc" , "485632417")
	# s.cancel_order( "bcd_btc" , "485632415")

	# s.cancel_order( "bcd_btc" , "485632415")

	# s.getOrder( "bcd_btc" , "485632415")



'''
DataApi
'''
def dataApiTest():
	s = Gate_DataApi()

	# symbol = "eth_usdt"
	# s.init(0.5 , 1)
	#s.subscribeTick(symbol)
	# s.subscribeOrderbooks(symbol)
	#s.subscribeTrades(symbol)


if __name__ == '__main__':
	# socketTest()
    tradeApiTest()
    # dataApiTest()
