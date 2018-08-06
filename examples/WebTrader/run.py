# encoding: UTF-8

"""
无人值守运行服务
"""
from __future__ import print_function

from time import sleep
from datetime import datetime, time
from multiprocessing import Process

import webbrowser

from webServer import run as runWebServer
from tradingServer import main as runTradingServer
from vnpy.trader.vtEngine import LogEngine


START_TIME = time(20, 45)
CLOSE_TIME = time(15, 30)


if __name__ == '__main__':
    # 创建日志引擎
    le = LogEngine()
    le.setLogLevel(le.LEVEL_INFO)
    le.addConsoleHandler()
    
    # 进入循环
    pWeb = None
    pTrading = None
    
    import os
    print(os.getpid())
    
    while True:  
        le.info('-'*30)
        
        dt = datetime.now()
        le.info(u'当前时间：%s' %dt)
        
        currentTime = dt.time()
        
        if currentTime >= START_TIME or currentTime <= CLOSE_TIME:
            le.info(u'当前处于交易时间段')
            
            if not pTrading:
                pTrading = Process(target=runTradingServer)
                pTrading.start()
                le.info(u'启动交易服务器进程')
                
            if not pWeb:
                pWeb = Process(target=runWebServer)
                pWeb.start()
                le.info(u'启动WEB服务器进程')
                
                webbrowser.open('http://127.0.0.1:5000')
        
        else:
            le.info(u'当前处于非交易时间段')
            
            if pTrading:
                pTrading.terminate()
                pTrading.join()
                pTrading = None
                le.info(u'关闭交易服务器进程')
            
            if pWeb:
                pWeb.terminate()
                pWeb.join()
                pWeb = None
                le.info(u'关闭WEB服务器进程')
        
        sleep(60)
        