# -*- coding: utf-8 -*-
from api import *


#  查询最新价
print(get_ticker('btcusdt'))
# 查询结果:{'timestamp': 1529461186102, 'status': 'ok', 'ticker': 
#        [{'symbol': 'BTCUSDT', '24hrHigh': '6832.65', 'ask': '6603.77', '24hrVol': '5329.3321', '24hrLow': '6547.0', 'bid': '6598.89', 'last': '6598.90', '24hrAmt': '35754346.714095'}]}


#  查询挂单,需要传入参数symbol,depth默认为200
print(get_orderbook('btcusdt',5))
# 查询结果:{'status': 'ok', 
# 　　　　　　　　'orderbook': {
#        　　　　　　　　　　　　 'asks': [{'quantity': 0.0678, 'price': 6612.78}, 
# 　　　　　　　　　　　　　　　　　　　　　　　　　　　　　{'quantity': 0.16, 'price': 6629.01}, 
# 　　　　　　　　　　　　　　　　　　　　　　　　　　　　　{'quantity': 0.0559, 'price': 6644.22}, 
# 　　　　　　　　　　　　　　　　　　　　　　　　　　　　　{'quantity': 0.3679, 'price': 6660.9}, 
# 　　　　　　　　　　　　　　　　　　　　　　　　　　　　　{'quantity': 0.01, 'price': 6679.6}], 
#      　　　　　　　　　　　　   'bids': [{'quantity': 0.5475, 'price': 6580}, 
# 　　　　　　　　　　　　　　　　　　　　　　　　　　　　　{'quantity': 0.0146, 'price': 6579.16},
# 　　　　　　　　　　　　　　　　　　　　　　　　　　　　　{'quantity': 0.4093, 'price': 6579.11}, 
# 　　　　　　　　　　　　　　　　　　　　　　　　　　　　　{'quantity': 0.0071, 'price': 6563.46}, 
# 　　　　　　　　　　　　　　　　　　　　　　　　　　　　　{'quantity': 0.01, 'price': 6563.41}]}, 
#         'timestamp': 1529461342333, 
# 　　　　　　　　'symbol': 'BTCUSDT'}


#  查询成交记录,传参:symbol和size默认为300
print(get_trade('ethusdt',2))
# 查询结果:{'timestamp': 1529461627036, 
#         'trades': [{'tradeId': '201806201026349790017791201806201026316910017482', 
#                     'quantity': '0.24', 
#                     'time': 1529461595000, 
#                     'price': '520.18', 
#                     'take': 'buy'}, 
#                    {'tradeId': '201806201024559520019121201806201026316910017482',
#                     'quantity': '0.11', 
#                     'time': 1529461591000, 
#                     'price': '520.18', 
#                     'take': 'sell'}],
#         'status': 'ok', 
#         'symbol': 'ETHUSDT'}


# 查询余额,此处以字典形式传参
# dic = {"apiid":"xxx","secret":"xxx","timestamp":11223112231,"account":"exchange"}
print(post_balance(dic))
# 查询结果:{
#         "account":"exchange",
#         "balance":[
#         {
#             "asset":"ACT",
#             "available":"999999.0000000000000000",
#             "reserved":"0.0000000000000000",
#             "total":"999999.0000000000000000"
#         },
#         {
#             "asset":"AE",
#             "available":"999999.0000000000000000",
#             "reserved":"0.0000000000000000",
#             "total":"999999.0000000000000000"
#         }
#     ],
#         "status":"ok",
#         "timestamp":1517536673213
# }


# 下订单,以字典形式传参
# dic = {"apiid":"xxx","secret":"xxx","timestamp":1122311221131,"type":"buy-limit","price":0.003401,"quantity":1,"symbol":"swtcusdt"}
print(post_order_place(dic))
# 查询结果:{'status': 'ok', 'timestamp': 1529462625853, 'orderid': '201806201043458241111111'}


#　按订单号查询委托,以字典形式传参
# dic = {"apiid":"xxx","secret":"xxx","timestamp":1122311211231,"orderid":201806201043458241111111}
print(post_info(dic))
#  查询结果:{
#         'order': {'filledquantity': '0', 
#               'symbol': 'SWTCUSDT', 
#               'type': 'buy-limit', 
#               'filledamount': '0', 
#               'price': '0.003401', 
#               'orderquantity': '1', 
#               'orderstatus': 'unfilled', 
#               'orderid': '201806201043458241111111', 
#               'createtime': 1529491426000}, 
#         'status': 'ok', 
#         'timestamp': 1529463050492}

# 查询当前委托,以字典形式传参
# dic = {"apiid":"xxx","secret":"xxx","timestamp":1122311211231,"symbol":"swtcusdt"}
print(post_open_orders(dic))
#  查询结果:{
#     "orders":{
#         "page":1,
#         "pagesize":10000,
#         "result":[
#             {
#                 "createtime":"2018-03-14 00:00:00",
#                 "filledamount":"1.0010000000000000",
#                 "filledquantity":"1.00000000",
#                 "lastmodified":"2018-03-14 00:00:00",
#                 "orderid":"B180124163642823625172",
#                 "orderquantity":"1.00000000",
#                 "orderstatus":"partialfilled",
#                 "price":"1.00000000",
#                 "symbol":"btcusdt",
#                 "type":"buy-limit"
#             },
#             {
#                 "createtime":"2018-03-14 00:00:00",
#                 "filledamount":"0.0000000000000000",
#                 "filledquantity":"0.10000000",
#                 "lastmodified":"2018-03-14 00:00:00",
#                 "orderid":"S180123183111553329941",
#                 "orderquantity":"0.10000000",
#                 "orderstatus":"partialfilled",
#                 "price":"11000.00000000",
#                 "symbol":"btcusdt",
#                 "type":"sell-limit"
#             },
#         ],
#         "totalcount":3
#     },
#     "status":"ok",
#     "timestamp":1517536673213
# }

# 撤销订单,以字典形式传参
# dic = {"apiid":"xxx","secret":"xxx","timestamp":112231121111231,"orderid":201806201043458241111111}
print(post_cancel(dic))
#  查询结果:{'orderid': '201806201043458241111111', 
#           'timestamp': 1529463751589, 
#           'status': 'ok'}
