# encoding: UTF-8

# 重载sys模块，设置默认字符串编码方式为utf8
import sys
reload(sys)
sys.setdefaultencoding('utf8')

import signal
from time import sleep

# vn.trader模块
from vnpy.event import EventEngine2
from vnpy.trader.vtEngine import MainEngine, LogEngine

# 加载底层接口
from vnpy.trader.gateway import ctpGateway

# 加载上层应用
from vnpy.trader.app import ctaStrategy, rpcService


#----------------------------------------------------------------------
def main():
    """主程序入口"""    
    le = LogEngine()
    le.setLogLevel(le.LEVEL_INFO)
    le.addConsoleHandler()
    le.addFileHandler()

    le.info(u'服务器进程启动')
    
    # 创建事件引擎
    ee = EventEngine2()
    le.info(u'事件引擎创建成功')
    
    # 创建主引擎
    me = MainEngine(ee)
    
    # 安全退出机制
    def shutdown(signal, frame):
        le.info(u'安全关闭进程')
        me.exit()
        sys.exit()
    
    for sig in [signal.SIGINT, signal.SIGTERM]:
        signal.signal(sig, shutdown)
    
    # 添加交易接口
    me.addGateway(ctpGateway)
    
    # 添加上层应用
    me.addApp(ctaStrategy)
    me.addApp(rpcService)
    
    le.info(u'主引擎创建成功')
    
    # 阻塞运行
    le.info(u'服务器启动成功')
    while 1:
        sleep(1)

if __name__ == '__main__':
    main()
