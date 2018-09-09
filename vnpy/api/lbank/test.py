# encoding: UTF-8

from six.moves import input
from time import time

from vnlbank import LbankRestApi, LbankWebsocketApi

API_KEY = '132a36ce-ad1c-409a-b48c-09b7877ae49b'
SECRET_KEY = '319320BF875297E7F4050E1195B880E8'


#----------------------------------------------------------------------
def restTest():
    """"""    
    # 创建API对象并初始化
    api = LbankRestApi()
    api.init(API_KEY, SECRET_KEY)
    api.start(1)
    
    # 测试
    #api.addReq('GET', '/currencyPairs.do', {}, api.onData)
    #api.addReq('GET', '/accuracy.do', {}, api.onData)

    #api.addReq('GET', '/ticker.do', {'symbol': 'eth_btc'}, api.onData)
    #api.addReq('GET', '/depth.do', {'symbol': 'eth_btc', 'size': '5'}, api.onData)
    
    #api.addReq('post', '/user_info.do', {}, api.onData)
    
    req = {
        'symbol': 'sc_btc',
        'current_page': '1',
        'page_length': '50'
    }
    api.addReq('POST', '/orders_info_no_deal.do', req, api.onData)
    
    # 阻塞
    input()    


#----------------------------------------------------------------------
def wsTest():
    """"""    
    ws = LbankWebsocketApi()
    ws.start()
    
    channels = [
        'lh_sub_spot_eth_btc_depth_20',
        'lh_sub_spot_eth_btc_trades',
        'lh_sub_spot_eth_btc_ticker'
    ]
    
    for channel in channels:
        req = {
            'event': 'addChannel',
            'channel': channel
        }
        ws.sendReq(req)
    
    
    # 阻塞
    input()   


if __name__ == '__main__':
    restTest()
    
    #wsTest()