# flake8: noqa
from vnpy.event import EventEngine

from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp

from vnpy_ctp import CtpGateway
# from vnpy_ctptest import CtptestGateway
# from vnpy_mini import MiniGateway
# from vnpy.gateway.minitest import MinitestGateway
# from vnpy.gateway.femas import FemasGateway
# from vnpy_sopt import SoptGateway
# from vnpy.gateway.sopttest import SopttestGateway
# from vnpy.gateway.sec import SecGateway
# from vnpy_uft import UftGateway
# from vnpy_esunny import EsunnyGateway
# from vnpy.gateway.hsoption import HsoptionGateway
# from vnpy_xtp import XtpGateway
# from vnpy.gateway.tora import ToraStockGateway
# from vnpy.gateway.tora import ToraOptionGateway
# from vnpy.gateway.comstar import ComstarGateway
# from vnpy.gateway.ib import IbGateway
# from vnpy.gateway.tap import TapGateway
# from vnpy.gateway.da import DaGateway
# from vnpy.gateway.mt5 import Mt5Gateway
# from vnpy_rohon import RohonGateway
# from vnpy_tts import TtsGateway

# from vnpy_ctastrategy import CtaStrategyApp
# from vnpy_ctabacktester import CtaBacktesterApp
# from vnpy_spreadtrading import SpreadTradingApp
# from vnpy.app.algo_trading import AlgoTradingApp
# from vnpy.app.option_master import OptionMasterApp
# from vnpy.app.portfolio_strategy import PortfolioStrategyApp
# from vnpy.app.script_trader import ScriptTraderApp
# from vnpy.app.market_radar import MarketRadarApp
# from vnpy_chartwizard import ChartWizardApp
# from vnpy.app.rpc_service import RpcServiceApp
# from vnpy.app.excel_rtd import ExcelRtdApp
# from vnpy_datamanager import DataManagerApp
# from vnpy_datarecorder import DataRecorderApp
# from vnpy_riskmanager import RiskManagerApp
# from vnpy_webtrader import WebTraderApp
# from vnpy.app.portfolio_manager import PortfolioManagerApp
# from vnpy.app.paper_account import PaperAccountApp


def main():
    """"""
    qapp = create_qapp()

    event_engine = EventEngine()

    main_engine = MainEngine(event_engine)

    main_engine.add_gateway(CtpGateway)
    # main_engine.add_gateway(CtptestGateway)
    # main_engine.add_gateway(MiniGateway)
    # main_engine.add_gateway(MinitestGateway)
    # main_engine.add_gateway(FemasGateway)
    # main_engine.add_gateway(SoptGateway)
    # main_engine.add_gateway(SopttestGateway)
    # main_engine.add_gateway(SecGateway)    
    # main_engine.add_gateway(UftGateway)
    # main_engine.add_gateway(EsunnyGateway)
    # main_engine.add_gateway(HsoptionGateway)
    # main_engine.add_gateway(XtpGateway)
    # main_engine.add_gateway(ToraStockGateway)
    # main_engine.add_gateway(ToraOptionGateway)
    # main_engine.add_gateway(OesGateway)
    # main_engine.add_gateway(ComstarGateway)
    # main_engine.add_gateway(IbGateway)
    # main_engine.add_gateway(TapGateway)
    # main_engine.add_gateway(DaGateway)
    # main_engine.add_gateway(Mt5Gateway)
    # main_engine.add_gateway(RohonGateway)
    # main_engine.add_gateway(XgjGateway)
    # main_engine.add_gateway(TtsGateway)
    
    # main_engine.add_app(CtaStrategyApp)
    # main_engine.add_app(CtaBacktesterApp)
    # main_engine.add_app(SpreadTradingApp)
    # main_engine.add_app(AlgoTradingApp)
    # main_engine.add_app(OptionMasterApp)
    # main_engine.add_app(PortfolioStrategyApp)
    # main_engine.add_app(ScriptTraderApp)
    # main_engine.add_app(MarketRadarApp)
    # main_engine.add_app(ChartWizardApp)
    # main_engine.add_app(RpcServiceApp)
    # main_engine.add_app(ExcelRtdApp)
    # main_engine.add_app(DataManagerApp)
    # main_engine.add_app(DataRecorderApp)
    # main_engine.add_app(RiskManagerApp)
    # main_engine.add_app(WebTraderApp)
    # main_engine.add_app(PortfolioManagerApp)
    # main_engine.add_app(PaperAccountApp)
    
    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()


if __name__ == "__main__":
    main()