# encoding: utf-8

import sys
import os

from datetime import datetime
from time import sleep
from threading import Thread

import vtPath
import eventType
from vnrpc import RpcServer
from vtEngine import MainEngine


########################################################################
class VtServer(RpcServer):
    """vn.trader服务器"""

    #----------------------------------------------------------------------
    def __init__(self, repAddress, pubAddress):
        """Constructor"""
        super(VtServer, self).__init__(repAddress, pubAddress)
        self.usePickle()
        
        # 创建主引擎对象
        self.engine = MainEngine()
        
        # 注册主引擎的方法到服务器的RPC函数
        self.register(self.engine.connect)
        self.register(self.engine.subscribe)
        self.register(self.engine.sendOrder)
        self.register(self.engine.cancelOrder)
        self.register(self.engine.qryAccount)
        self.register(self.engine.qryPosition)
        self.register(self.engine.exit)
        self.register(self.engine.writeLog)
        self.register(self.engine.dbConnect)
        self.register(self.engine.dbInsert)
        self.register(self.engine.dbQuery)
        self.register(self.engine.dbUpdate)
        self.register(self.engine.getContract)
        self.register(self.engine.getAllContracts)
        self.register(self.engine.getOrder)
        self.register(self.engine.getAllWorkingOrders)
        self.register(self.engine.getAllGatewayNames)
        self.register(self.engine.getGateway4sysMenu)

        # 注册事件引擎发送的事件处理监听
        self.engine.eventEngine.registerGeneralHandler(self.eventHandler)
        
    #----------------------------------------------------------------------
    def eventHandler(self, event):
        """事件处理"""
        self.publish(event.type_, event)
        
    #----------------------------------------------------------------------
    def stopServer(self):
        """停止服务器"""
        # 关闭引擎
        self.engine.exit()
        
        # 停止服务器线程
        self.stop()


#----------------------------------------------------------------------
def printLog(content):
    """打印日志"""
    print datetime.now().strftime("%H:%M:%S"), '\t', content


#----------------------------------------------------------------------
def runServer():
    """运行服务器"""
    repAddress = 'tcp://*:2014'
    pubAddress = 'tcp://*:0602'
    
    # 创建并启动服务器
    server = VtServer(repAddress, pubAddress)
    server.start()
    
    printLog('-'*50)
    printLog(u'vn.trader服务器已启动')
    
    # 进入主循环
    while True:
        printLog(u'请输入exit来关闭服务器')
        if raw_input() != 'exit':
            continue

        printLog(u'确认关闭服务器？yes|no')
        if raw_input() == 'yes':
            break
    
    server.stopServer()
    
if __name__ == '__main__':
    runServer()