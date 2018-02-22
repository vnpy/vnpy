# encoding: utf-8

from private_api import *

api = PrivateAPI('FssV9Jw0aZVCOYbu9YlqVNc2Rhgmh1QpruNgSVhvVmFP1iw1aPfc3APbfz0ZM', 'lSMc1TT2AZYX5pyEm01SFqx7PgMjNB18eXWpi8DQKHf0rcYhLiaiRVzJwaVZR')

print api.create_token_directly('xiaoshuang8921@naver.com', 'Wxiaoshuang8921')

# print api.view_exchange_orders( 0 , 10 , "btc_krw")
#api.limit_bid_order(coin_amount = 0.01 , price = 1000 , currency_pair="btc_krw")
api.limit_ask_order(coin_amount = 0.01 , price = 10000000 , currency_pair = "bch_krw")