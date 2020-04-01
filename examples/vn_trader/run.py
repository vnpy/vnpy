# flake8: noqa
from vnpy.event import EventEngine

from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp

# from vnpy.gateway.binance import BinanceGateway
# from vnpy.gateway.bitmex import BitmexGateway
# from vnpy.gateway.futu import FutuGateway
# from vnpy.gateway.ib import IbGateway
# from vnpy.gateway.ctp import CtpGateway
# from vnpy.gateway.ctptest import CtptestGateway
# from vnpy.gateway.mini import MiniGateway
# from vnpy.gateway.sopt import SoptGateway
# from vnpy.gateway.minitest import MinitestGateway
# from vnpy.gateway.femas import FemasGateway
# from vnpy.gateway.tiger import TigerGateway
# from vnpy.gateway.oes import OesGateway
# from vnpy.gateway.okex import OkexGateway
# from vnpy.gateway.huobi import HuobiGateway
# from vnpy.gateway.bitfinex import BitfinexGateway
# from vnpy.gateway.onetoken import OnetokenGateway
# from vnpy.gateway.okexf import OkexfGateway
# from vnpy.gateway.okexs import OkexsGateway
from vnpy.gateway.xtp import XtpGateway
# from vnpy.gateway.hbdm import HbdmGateway
# from vnpy.gateway.tap import TapGateway
# from vnpy.gateway.tora import ToraGateway
# from vnpy.gateway.alpaca import AlpacaGateway
# from vnpy.gateway.da import DaGateway
# from vnpy.gateway.coinbase import CoinbaseGateway
# from vnpy.gateway.bitstamp import BitstampGateway
# from vnpy.gateway.gateios import GateiosGateway
# from vnpy.gateway.bybit import BybitGateway
# from vnpy.gateway.deribit import DeribitGateway
from vnpy.gateway.uft import UftGateway
# from vnpy.gateway.okexo import OkexoGateway
# from vnpy.gateway.binancef import BinancefGateway

# from vnpy.app.cta_strategy import CtaStrategyApp
# from vnpy.app.csv_loader import CsvLoaderApp
# from vnpy.app.algo_trading import AlgoTradingApp
# from vnpy.app.cta_backtester import CtaBacktesterApp
# from vnpy.app.data_recorder import DataRecorderApp
# from vnpy.app.risk_manager import RiskManagerApp
# from vnpy.app.script_trader import ScriptTraderApp
# from vnpy.app.rpc_service import RpcServiceApp
# from vnpy.app.spread_trading import SpreadTradingApp
# from vnpy.app.portfolio_manager import PortfolioManagerApp
# from vnpy.app.option_master import OptionMasterApp
# from vnpy.app.chart_wizard import ChartWizardApp
# from vnpy.app.excel_rtd import ExcelRtdApp
# from vnpy.app.data_manager import DataManagerApp
from vnpy.app.portfolio_strategy import PortfolioStrategyApp


def main():
    """"""
    qapp = create_qapp()

    event_engine = EventEngine()

    main_engine = MainEngine(event_engine)

    # main_engine.add_gateway(BinanceGateway)
    # main_engine.add_gateway(CtpGateway)
    # main_engine.add_gateway(CtptestGateway)
    # main_engine.add_gateway(MiniGateway)
    # main_engine.add_gateway(SoptGateway)
    # main_engine.add_gateway(MinitestGateway)
    # main_engine.add_gateway(FemasGateway)
    main_engine.add_gateway(UftGateway)
    # main_engine.add_gateway(IbGateway)
    # main_engine.add_gateway(FutuGateway)
    # main_engine.add_gateway(BitmexGateway)
    # main_engine.add_gateway(TigerGateway)
    # main_engine.add_gateway(OesGateway)
    # main_engine.add_gateway(OkexGateway)
    # main_engine.add_gateway(HuobiGateway)
    # main_engine.add_gateway(BitfinexGateway)
    # main_engine.add_gateway(OnetokenGateway)
    # main_engine.add_gateway(OkexfGateway)
    # main_engine.add_gateway(HbdmGateway)
    main_engine.add_gateway(XtpGateway)
    # main_engine.add_gateway(TapGateway)
    # main_engine.add_gateway(ToraGateway)
    # main_engine.add_gateway(AlpacaGateway)
    # main_engine.add_gateway(OkexsGateway)
    # main_engine.add_gateway(DaGateway)
    # main_engine.add_gateway(CoinbaseGateway)
    # main_engine.add_gateway(BitstampGateway)
    # main_engine.add_gateway(GateiosGateway)
    # main_engine.add_gateway(BybitGateway)
    # main_engine.add_gateway(DeribitGateway)
    # main_engine.add_gateway(OkexoGateway)
    # main_engine.add_gateway(BinancefGateway)

    # main_engine.add_app(CtaStrategyApp)
    # main_engine.add_app(CtaBacktesterApp)
    # main_engine.add_app(CsvLoaderApp)
    # main_engine.add_app(AlgoTradingApp)
    # main_engine.add_app(DataRecorderApp)
    # main_engine.add_app(RiskManagerApp)
    # main_engine.add_app(ScriptTraderApp)
    # main_engine.add_app(RpcServiceApp)
    # main_engine.add_app(SpreadTradingApp)
    # main_engine.add_app(PortfolioManagerApp)
    # main_engine.add_app(OptionMasterApp)
    # main_engine.add_app(ChartWizardApp)
    # main_engine.add_app(ExcelRtdApp)
    # main_engine.add_app(DataManagerApp)
    main_engine.add_app(PortfolioStrategyApp)
    
    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()


if __name__ == "__main__":
    main()