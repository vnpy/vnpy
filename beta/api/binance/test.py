# encoding: UTF-8

from vnbinance import *

# 在OkCoin网站申请这两个Key，分别对应用户名和密码
# apiKey = ''
# secretKey = ''

# api = BINANCE_Sub_Spot_Api()

# api.connect_Subpot(apiKey , secretKey)
# api.subscribeSpotTicker("BNBBTC".lower())

url = "wss://stream.binance.com:9443/ws/bnbbtc@kline_1m"

# print BINANCE_STREAM_URL
factory = BinanceClientFactory( url )
factory.protocol = BinanceClientProtocol
factory.callback = process_message
context_factory = ssl.ClientContextFactory()
connectWS(factory, context_factory)

reactor.run( installSignalHandlers=False )
input()

# bm = BinanceSocketManager(None)
# #bm.start_aggtrade_socket(symbol='BNBBTC' , callback=process_message)
# bm.start_symbol_ticker_socket("BNBBTC" , callback=process_message)
# bm.start()