# encoding: UTF-8

from vnokcoin import *

# 在OkCoin网站申请这两个Key，分别对应用户名和密码
apiKey = ''
secretKey = ''

# 创建API对象
api = OkCoinApi()

# 连接服务器，并等待1秒
api.connect(OKCOIN_USD, apiKey, secretKey, True)

sleep(1)

# 测试现货行情API
#api.subscribeSpotTicker(SYMBOL_BTC)
#api.subscribeSpotTradeData(SYMBOL_BTC)
api.subscribeSpotDepth(SYMBOL_BTC, DEPTH_20)
#api.subscribeSpotKline(SYMBOL_BTC, INTERVAL_1M)

# 测试现货交易API
#api.subscribeSpotTrades()
#api.subscribeSpotUserInfo()
#api.spotUserInfo()
#api.spotTrade(symbol, type_, price, amount)
#api.spotCancelOrder(symbol, orderid)
#api.spotOrderInfo(symbol, orderid)

# 测试期货行情API
#api.subscribeFutureTicker(SYMBOL_BTC, FUTURE_EXPIRY_THIS_WEEK)
#api.subscribeFutureTradeData(SYMBOL_BTC, FUTURE_EXPIRY_THIS_WEEK)
#api.subscribeFutureDepth(SYMBOL_BTC, FUTURE_EXPIRY_THIS_WEEK, DEPTH_20)
#api.subscribeFutureKline(SYMBOL_BTC, FUTURE_EXPIRY_THIS_WEEK, INTERVAL_1M) 
#api.subscribeFutureIndex(SYMBOL_BTC)

# 测试期货交易API
#api.subscribeFutureTrades()
#api.subscribeFutureUserInfo()
#api.subscribeFuturePositions()
#api.futureUserInfo()
#api.futureTrade(symbol, expiry, type_, price, amount, order, leverage)
#api.futureCancelOrder(symbol, expiry, orderid)
#api.futureOrderInfo(symbol, expiry, orderid, status, page, length)

raw_input()