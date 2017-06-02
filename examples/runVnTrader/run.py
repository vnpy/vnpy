# encoding: UTF-8

# 重载sys模块，设置默认字符串编码方式为utf8
import sys
reload(sys)
sys.setdefaultencoding('utf8')

# vn.trader模块
from vnpy.event import EventEngine2
from vnpy.trader.vtGlobal import globalSetting
from vnpy.trader.vtEngine import MainEngine
from vnpy.trader.uiQt import qApp
from vnpy.trader.uiMainWindow import MainWindow

# 加载底层接口
from vnpy.trader.gateway import (ctpGateway, femasGateway, xspeedGateway, 
                                 sgitGateway, oandaGateway, ibGateway, 
                                 shzdGateway, huobiGateway, okcoinGateway)

# 加载上层应用
from vnpy.trader.app import (riskManager, dataRecorder,
                             ctaStrategy)


#----------------------------------------------------------------------
def main():
    """主程序入口"""
    # 创建事件引擎
    ee = EventEngine2()
    
    # 创建主引擎
    me = MainEngine(ee)
    
    # 添加交易接口
    me.addGateway(ctpGateway)
    me.addGateway(femasGateway)
    me.addGateway(xspeedGateway)
    me.addGateway(sgitGateway)
    me.addGateway(oandaGateway)
    me.addGateway(ibGateway)
    me.addGateway(shzdGateway)
    me.addGateway(huobiGateway)
    me.addGateway(okcoinGateway)
    
    # 添加上层应用
    me.addApp(riskManager)
    me.addApp(dataRecorder)
    me.addApp(ctaStrategy)
    
    # 创建主窗口
    mw = MainWindow(me, ee)
    mw.showMaximized()
    
    # 在主线程中启动Qt事件循环
    sys.exit(qApp.exec_())


if __name__ == '__main__':
    main()
