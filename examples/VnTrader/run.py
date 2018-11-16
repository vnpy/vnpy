# encoding: UTF-8

# 重载sys模块，设置默认字符串编码方式为utf8
import sys
from vnpy.trader.app import (riskManager, ctaStrategy,
                             spreadTrading, algoTrading)
from vnpy.trader.gateway import (ctpGateway, ibGateway)
from vnpy.trader.uiMainWindow import MainWindow
from vnpy.trader.uiQt import createQApp
from vnpy.trader.vtEngine import MainEngine
from vnpy.event import EventEngine
import platform

try:
    reload         # Python 2
except NameError:  # Python 3
    from importlib import reload

reload(sys)

try:
    sys.setdefaultencoding('utf8')
except AttributeError:
    pass

# 判断操作系统
system = platform.system()

# vn.trader模块

# 加载底层接口

if system == 'Linux':
    from vnpy.trader.gateway import xtpGateway
elif system == 'Windows':
    from vnpy.trader.gateway import (femasGateway, xspeedGateway,
                                     secGateway)

# 加载上层应用


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
    me.addGateway(ctpGateway)
    me.addGateway(ibGateway)

    if system == 'Windows':
        me.addGateway(femasGateway)
        me.addGateway(xspeedGateway)
        me.addGateway(secGateway)

    if system == 'Linux':
        me.addGateway(xtpGateway)

    # 添加上层应用
    me.addApp(riskManager)
    me.addApp(ctaStrategy)
    me.addApp(spreadTrading)
    me.addApp(algoTrading)

    # 创建主窗口
    mw = MainWindow(me, ee)
    mw.showMaximized()

    # 在主线程中启动Qt事件循环
    sys.exit(qApp.exec_())


if __name__ == '__main__':
    main()
