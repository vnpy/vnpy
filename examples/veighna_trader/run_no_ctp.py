"""
VeighNa Trader 启动脚本（不依赖 CTP，适合 macOS）

由于 vnpy_ctp 在 macOS 上编译存在问题，此版本使用 PaperAccount（本地仿真账户）
进行测试，无需连接真实的交易接口。
"""

from vnpy.event import EventEngine

from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp

# 注释掉 CTP（macOS 上编译有问题）
# from vnpy_ctp import CtpGateway

# 使用本地仿真账户（不需要编译，纯 Python 实现）
from vnpy_paperaccount import PaperAccountApp

from vnpy_ctastrategy import CtaStrategyApp
from vnpy_ctabacktester import CtaBacktesterApp
from vnpy_datamanager import DataManagerApp


def main():
    """Start VeighNa Trader"""
    qapp = create_qapp()

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    
    # 不添加 CTP Gateway（macOS 编译问题）
    # main_engine.add_gateway(CtpGateway)
    
    # 添加本地仿真账户（用于测试，无需真实交易接口）
    main_engine.add_app(PaperAccountApp)
    
    # 添加功能模块
    main_engine.add_app(CtaStrategyApp)
    main_engine.add_app(CtaBacktesterApp)
    main_engine.add_app(DataManagerApp)

    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()


if __name__ == "__main__":
    main()
