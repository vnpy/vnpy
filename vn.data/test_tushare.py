# encoding: UTF-8
import tushare as ts
import pandas as pd
#import ipdb
import datetime

#data = ts.get_hist_data('600848', start='2015-04-01', end='2015-10-20') #一次性获取全部日k线数据
#
#print data.tail(10)
#
#data.plot()
#
#data.high.plot()
#
#with pd.plot_params.use('x_compat',True):
#    data.open.plot(color = 'g')
#    data.close.plot(color = 'y')
#    data.high.plot(color = 'r')
#    data.low.plot(color = 'b')
#
#
#with pd.plot_params.use('x_compat',True):
#    data.high.plot(color ='r', figsize = (10,4), grid ='on')
#    data.low.plot(color ='b', figsize = (10,4), grid ='on')
#
#ipdb.set_trace()
#

ts.set_token('21768410ff5c2acb686264fa97635fa917a2ba1ae5122fa187b45849d92cfc70')

md = ts.Market()

#data = md.MktFutd(ticker='au1512',beginDate='20151008', endDate='20151028',
#                  field='tradeDate,ticker,openPrice,highestPrice,lowestPrice,closePrice,preClosePrice,CHG,CHG1,CHGPct')

data = md.MktFutd(tradeDate='20140201',
                  field='tradeDate,ticker,openPrice,highestPrice,lowestPrice,closePrice,preClosePrice,CHG,CHG1,CHGPct')


#data['TR'] = abs(data['closePrice']-data['openPrice'])

#atr = data.tail(10)['TR'].sum()/10

tradeDate= str(data.tail(1)['tradeDate'].values[0])

predate = datetime.datetime.strptime(tradeDate, '%Y-%m-%d')

preOpen = float(data.tail(1)['openPrice'])
preHigh = float(data.tail(1)['highestPrice'])
preLow = float(data.tail(1)['lowestPrice'])
preClose = float(data.tail(1)['closePrice'])

print data

#print atr

print predate
print preOpen
print preHigh
print preLow
print preClose

print data.columns


