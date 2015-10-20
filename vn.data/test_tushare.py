# encoding: UTF-8
import tushare as ts
import pandas as pd
import ipdb

data = ts.get_hist_data('600848', start='2015-04-01', end='2015-10-20') #一次性获取全部日k线数据

#print data.tail(10)

data.plot()

data.high.plot()

with pd.plot_params.use('x_compat',True):
    data.open.plot(color = 'g')
    data.close.plot(color = 'y')
    data.high.plot(color = 'r')
    data.low.plot(color = 'b')


with pd.plot_params.use('x_compat',True):
    data.high.plot(color ='r', figsize = (10,4), grid ='on')
    data.low.plot(color ='b', figsize = (10,4), grid ='on')

#ipdb.set_trace()
