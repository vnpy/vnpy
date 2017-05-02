# encoding: utf-8

import sys
try:
    # python2 需要设置编码
    reload(sys)
    sys.setdefaultencoding('utf-8')
except:
    # python3 不需要
    pass
import vtGlobal
import json
import os
from argparse import ArgumentParser

from datetime import datetime

from vtFunction import autoshutdown
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
    print("%s\t%s" % (datetime.now().strftime("%H:%M:%S"), content))


#----------------------------------------------------------------------
def runServer():
    """运行服务器"""
    VT_setting = vtGlobal.VT_setting

    repAddress = 'tcp://*:2014'
    pubAddress = 'tcp://*:0602'

    # 创建并启动服务器
    server = VtServer(repAddress, pubAddress)
    server.start()

    printLog('-'*50)
    printLog(u'vn.trader服务器已启动')

    if VT_setting.get('automongodb'):
        # 自动建立MongoDB数据库
        printLog(u'MongoDB connect... ')
        server.engine.dbConnect()

    if VT_setting.get('autoctp'):
        # 自动建立CTP链接
        printLog(u"CTP connect... ")
        server.engine.connect("CTP")

    if VT_setting.get('autoshutdown'):
        # 自动关闭 线程阻塞
        wait2shutdown = autoshutdown()
        printLog(u"time to shutdown %s" % wait2shutdown.closeTime)
        wait2shutdown.join()
    else:
        # 进入主循环
        while True:
            printLog(u'input "exit" to exit')
            if raw_input() != 'exit':
                continue

            printLog(u'confirm？yes|no')
            if raw_input() == 'yes':
                break

    server.stopServer()


if __name__ == '__main__':
    opt = ArgumentParser(
        prog="vnpy",
        description="Args of vnpy.",
    )

    # VT_setting.json 文件路径
    opt.add_argument("--VT_setting", default=None, help="重新指定VT_setting.json的绝对路径")

    # 生成参数实例
    cmdArgs = opt.parse_args()

    if cmdArgs.VT_setting is None:
        fileName = 'VT_setting.json'
        path = os.path.abspath(os.path.dirname(__file__))
        fileName = os.path.join(path, fileName)
    else:
        fileName = cmdArgs.VT_setting

    with open(fileName) as f:
        vtGlobal.VT_setting = json.load(f)

    runServer()
