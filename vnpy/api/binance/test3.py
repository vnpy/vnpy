# encoding: UTF-8

from vnbinance import *


apiKey = '你的apiKey'
secretKey = '你的secretkey'

aa = BinanceSpotApi()
aa.connect_Subpot( apiKey , secretKey)

# aa.subcribeSymbol( "bnb_btc")

input()