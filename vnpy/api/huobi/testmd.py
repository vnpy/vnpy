# encoding: UTF-8

#from websocket import create_connection
#import gzip
#import zlib
#import time

from __future__ import absolute_import
from .vnhuobi import DataApi

#if __name__ == '__main__':
    #while(1):
        #try:
            #ws = create_connection("wss://api.huobipro.com/ws")
            #break
        #except:
            #print('connect ws error,retry...')
            #time.sleep(5)

    ## 订阅 KLine 数据
    ##tradeStr="""{"sub": "market.ethusdt.kline.1min","id": "id10"}"""

    ## 请求 KLine 数据
    ## tradeStr="""{"req": "market.ethusdt.kline.1min","id": "id10", "from": 1513391453, "to": 1513392453}"""

    ##订阅 Market Depth 数据
    #tradeStr="""{"sub": "market.ethusdt.depth.step5", "id": "id10"}"""

    ##请求 Market Depth 数据
    ## tradeStr="""{"req": "market.ethusdt.depth.step5", "id": "id10"}"""

    ##订阅 Trade Detail 数据
    ## tradeStr="""{"sub": "market.ethusdt.trade.detail", "id": "id10"}"""

    ##请求 Trade Detail 数据
    ## tradeStr="""{"req": "market.ethusdt.trade.detail", "id": "id10"}"""

    ##请求 Market Detail 数据
    ## tradeStr="""{"req": "market.ethusdt.detail", "id": "id12"}"""

    #ws.send(tradeStr)
    #while(1):
        #compressData=ws.recv()
        ##print compressData
        #result=zlib.decompress(compressData, 15+32).decode('utf-8')
        #if result[:7] == '{"ping"':
            #ts=result[8:21]
            #pong='{"pong":'+ts+'}'
            #ws.send(pong)
            #ws.send(tradeStr)
        #else:
            #print(result)


api = DataApi()
api.connect("wss://api.huobipro.com/ws")
api.subscribeMarketDepth('ethusdt')
#api.subscribeTradeDetail('ethusdt')
#api.subscribeMarketDetail('ethusdt')
input()