# encoding: utf-8

from __future__ import print_function
from coincheck import order,market,account

ok = order.Order(access_key="你的accessKey", secret_key="你的secretKey")
print(ok.buy_btc_jpy(amount=0.01,rate=200))