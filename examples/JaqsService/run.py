# encoding: UTF-8

# 重载sys模块，设置默认字符串编码方式为utf8
import sys
reload(sys)
sys.setdefaultencoding('utf8')

from time import sleep

# vn.trader模块
from vnpy.event import EventEngine
from vnpy.trader.vtEngine import MainEngine, LogEngine
from vnpy.trader.uiQt import createQApp
from vnpy.trader.uiMainWindow import MainWindow
from vnpy.trader.vtEvent import EVENT_LOG

# 加载底层接口
from vnpy.trader.gateway import ctpGateway

# 加载上层应用
from vnpy.trader.app import jaqsService
from vnpy.trader.app.jaqsService.jsEngine import EVENT_JS_LOG

#----------------------------------------------------------------------
def main():
    """主程序入口"""
    le = LogEngine()
    le.setLogLevel(le.LEVEL_INFO)
    le.addConsoleHandler()
    le.addFileHandler()
    
    le.info(u'启动JAQS服务进程')
    
    ee = EventEngine()
    le.info(u'事件引擎创建成功')
    
    me = MainEngine(ee)
    me.addGateway(ctpGateway)
    me.addApp(jaqsService)
    le.info(u'主引擎创建成功')
    
    ee.register(EVENT_LOG, le.processLogEvent)
    ee.register(EVENT_JS_LOG, le.processLogEvent)
    le.info(u'注册日志事件监听')    
    
    me.connect('CTP')
    le.info(u'连接CTP接口')    
    
    while True:
        sleep(1)


if __name__ == '__main__':
    main()
