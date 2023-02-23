# -*- encoding:utf-8 -*-
import sys
args = sys.argv
try:
    work_dir = args[1]
except IndexError:
    work_dir = ''
from vnpy import set_work_dir
set_work_dir(work_dir)

import ssl
from vnpy_jg.gateway.jg_gateway import JGGateway
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp
from vnpy.gateway.uft import UftGateway
from vnpy_ctastrategy import CtaStrategyApp
from vnpy_ctabacktester import CtaBacktesterApp
from vnpy_spreadtrading import SpreadTradingApp
from vnpy_qmt import QmtGateway
from vnpy_ctp import CtpGateway
from vnpy_tap import TapGateway
from vnpy.gateway.sopttest import SopttestGateway
from vnpy_optionmaster import OptionMasterApp
from vnpy_scripttrader import ScriptTraderApp
from vnpy_sopt.gateway.sopt_gateway import SoptGateway

def main():
    """Start VN Trader"""
    qapp = create_qapp()

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)

    main_engine.add_gateway(CtpGateway)
    main_engine.add_gateway(QmtGateway)
    main_engine.add_gateway(SoptGateway)
    main_engine.add_gateway(SopttestGateway)
    main_engine.add_gateway(JGGateway)
    main_engine.add_gateway(UftGateway)
    main_engine.add_app(CtaStrategyApp)
    main_engine.add_app(CtaBacktesterApp)
    main_engine.add_app(SpreadTradingApp)
    main_engine.add_app(OptionMasterApp)
    main_engine.add_app(ScriptTraderApp)

    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()


if __name__ == "__main__":
    main()