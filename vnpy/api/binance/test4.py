# encoding: UTF-8

from vnbinance import *

apiKey = '你的apiKey'
secretKey = '你的secretkey'

ap = BinanceSpotApi()

ap.connect_Subpot( apiKey , secretKey)

# ap.subscribeSpotDepth( "BNBBTC" ) 

# ap.spotListAllOrders("ETCBTC")

# id 5509642

# ap.spotListOpenOrders()
# ap.spotAccountInfo()

# ap.subscribeAllTicker()

# print "ap.spotExchangeInfo()"
# ap.spotExchangeInfo()

# print ap.spotCancelOrder( "ETCBTC" , "5509642" )

ap.spotListAllOrders("ETCBTC")

# ap.spotTrade( symbol_pair = "ETCBTC" , type_ = "sell" , price = 0.1 , amount = 0.01)

# ap.spotListAllOrders("ETCBTC")

# input()

