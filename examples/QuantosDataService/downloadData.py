# encoding: UTF-8

"""
立即下载数据到数据库中，用于手动执行更新操作。
"""
from __future__ import print_function

import json

from vnpy.trader.gateway.tkproGateway.DataApi import DataApi
from dataService import *


if __name__ == '__main__':
    # 创建API对象
    api = DataApi(DATA_SERVER)
    info, msg = api.login(USERNAME, TOKEN)
    
    if not info:
        print(u'数据服务器登录失败，原因：%s' %msg)    

    # 下载数据
    downloadAllMinuteBar(api, 100)