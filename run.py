from vnpy_jg.gateway.jg_gateway import JGGateway
from vnpy_riskmanager import RiskManagerApp
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp
from vnpy.gateway.uft import UftGateway
from vnpy_ctastrategy import CtaStrategyApp
from vnpy_ctabacktester import CtaBacktesterApp
from vnpy_spreadtrading import SpreadTradingApp
from vnpy_xtp import XtpGateway
from vnpy_okex import OkexGateway
from vnpy_esunny import EsunnyGateway
from vnpy_ctptest import CtptestGateway


def main():
    """Start VN Trader"""
    qapp = create_qapp()

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)

    main_engine.add_gateway(CtptestGateway)
    main_engine.add_gateway(JGGateway)
    main_engine.add_gateway(UftGateway)
    main_engine.add_gateway(XtpGateway)
    main_engine.add_gateway(OkexGateway)
    main_engine.add_app(CtaStrategyApp)
    main_engine.add_app(CtaBacktesterApp)
    main_engine.add_app(SpreadTradingApp)
    main_engine.add_app(RiskManagerApp)


    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()


if __name__ == "__main__":
    main()