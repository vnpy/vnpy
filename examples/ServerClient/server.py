# encoding: UTF-8

# 重载sys模块，设置默认字符串编码方式为utf8
import sys
reload(sys)
sys.setdefaultencoding('utf8')

# 判断操作系统
import platform
system = platform.system()

# vn.trader模块
from vnpy.event import EventEngine2
from vnpy.trader.vtEngine import MainEngine

# 加载底层接口
from vnpy.trader.gateway import ctpGateway

# 加载上层应用
from vnpy.trader.app import (riskManager, ctaStrategy, rpcService)


#----------------------------------------------------------------------
def main():
    """主程序入口"""    
    # 创建事件引擎
    ee = EventEngine2()
    
    # 创建主引擎
    me = MainEngine(ee)
    
    # 添加交易接口
    me.addGateway(ctpGateway)
    
    # 添加上层应用
    #me.addApp(riskManager)
    #me.addApp(ctaStrategy)
    #me.addApp(rpcService)
    
    # 阻塞运行
    cmd = ''
    while cmd != 'exit':
        cmd = raw_input()

if __name__ == '__main__':
    main()
