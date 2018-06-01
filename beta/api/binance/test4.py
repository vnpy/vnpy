# encoding: UTF-8

from vnbinance import *

apiKey = ""
secretKey = ""

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
# ap.subcribeSymbol( "bnb_btc")


# ap.spotListAllOrders("ETCBTC")

print "ap.subscribeSpotTicker"
# ap.subscribeSpotTicker("bnb_btc")

price_f = "0.00000325"
# ap.spotTrade( symbol_pair = "ETCBTC" , type_ = "sell" , price = 0.1 , amount = 0.01)

ap.spotTrade( symbol_pair = "TNBBTC" , type_ = "buy" , price = price_f , amount = 400)

# ap.spotListAllOrdesrs("TNBBTC")

# ap.spotCancelOrder( "TNBBTC" , "5047104" )
# ap.spotListAllOrders("ETCBTC")

#input()
