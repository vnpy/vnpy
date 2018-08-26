# encoding: UTF-8

# 重载sys模块，设置默认字符串编码方式为utf8
try:
    reload         # Python 2
except NameError:  # Python 3
    from importlib import reload
import sys
reload(sys)
sys.setdefaultencoding('utf8')

# 判断操作系统
import platform
system = platform.system()

# vn.trader模块
from vnpy.event import EventEngine
from vnpy.trader.vtEngine import MainEngine
from vnpy.trader.uiQt import createQApp

# 加载底层接口
from vnpy.trader.gateway import (huobiGateway, okexGateway,
                                 binanceGateway, bitfinexGateway,
                                 bitmexGateway, fcoinGateway,
                                 bigoneGateway, lbankGateway,
                                 coinbaseGateway, ccxtGateway)

# 加载上层应用
from vnpy.trader.app import (algoTrading)

# 当前目录组件
from uiCryptoWindow import MainWindow

#----------------------------------------------------------------------
def main():
    """主程序入口"""
    # 创建Qt应用对象
    qApp = createQApp()

    # 创建事件引擎
    ee = EventEngine()

    # 创建主引擎
    me = MainEngine(ee)

    # 添加交易接口
    me.addGateway(ccxtGateway)
    me.addGateway(coinbaseGateway)
    me.addGateway(lbankGateway)
    me.addGateway(bigoneGateway)
    me.addGateway(fcoinGateway)
    me.addGateway(bitmexGateway)
    me.addGateway(huobiGateway)
    me.addGateway(okexGateway)
    me.addGateway(binanceGateway)
    me.addGateway(bitfinexGateway)
    
    # 添加上层应用
    me.addApp(algoTrading)
    
    # 创建主窗口
    mw = MainWindow(me, ee)
    mw.showMaximized()

    # 在主线程中启动Qt事件循环
    sys.exit(qApp.exec_())


if __name__ == '__main__':
    main()
