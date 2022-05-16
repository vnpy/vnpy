import ssl
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
# from vnpy_ctptest import CtptestGateway
from vnpy_ctp import CtpGateway
from vnpy_tap import TapGateway
from vnpy.gateway.sopttest import SopttestGateway
from vnpy_portfoliomanager import PortfolioManagerApp, PortfolioEngine
from vnpy_datarecorder import DataRecorderApp
from vnpy_datamanager import DataManagerApp
from vnpy_optionmaster import OptionMasterApp
from vnpy_scripttrader import ScriptTraderApp
from vnpy.app.portfolio_strategy import PortfolioStrategyApp


def main():
    """Start VN Trader"""
    qapp = create_qapp()

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)

    main_engine.add_gateway(CtpGateway)
    main_engine.add_gateway(SopttestGateway)
    main_engine.add_gateway(JGGateway)
    main_engine.add_gateway(UftGateway)
    main_engine.add_gateway(XtpGateway)
    main_engine.add_gateway(OkexGateway)
    main_engine.add_gateway(TapGateway)
    main_engine.add_app(CtaStrategyApp)
    main_engine.add_app(CtaBacktesterApp)
    main_engine.add_app(SpreadTradingApp)
    main_engine.add_app(RiskManagerApp)
    main_engine.add_app(PortfolioManagerApp)
    main_engine.add_app(DataRecorderApp)
    main_engine.add_app(OptionMasterApp)
    main_engine.add_app(ScriptTraderApp)
    main_engine.add_app(PortfolioStrategyApp)
    main_engine.add_app(DataManagerApp)

    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()


if __name__ == "__main__":
    main()