# encoding: utf-8

from time import time, sleep

from vnlbank import LbankApi


if __name__ == '__main__':
    apiKey = ''
    secretKey = ''
    
    # 创建API对象并初始化
    api = LbankApi()
    api.DEBUG = True
    api.init(apiKey, secretKey, 2)
    
    # 查询行情
    api.getTicker('btc_cny')

    # 查询深度
    api.getDepth('btc_cny', '60', '1')

    # 查询历史成交
    #api.getTrades('btc_cny', '1', str(int(time())))

    # 查询Ｋ线
    #t = int(time())
    #sleep(300)
    #api.getKline('btc_cny', '20', 'minute1', str(t))

    # 查询账户
    #api.getUserInfo()

    # 发送委托
    #api.createOrder('btc_cny', 'sell', '8000', '0.001')

    # 撤单
    #api.cancelOrder('btc_cny', '725bd2da-73aa-419f-8090-f68488074e8f')

    # 查询委托
    #api.getOrdersInfo('btc_cny', '725bd2da-73aa-419f-8090-f68488074e8f')

    # 查询委托历史
    #api.getOrdersInfoHistory('btc_cny', '0', '1', '100')

    # 阻塞
    raw_input()    
