
from vnpy.event import EventEngine

from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp

from vnpy.gateway.bitmex import BitmexGateway
from vnpy.gateway.futu import FutuGateway
from vnpy.gateway.ib import IbGateway
from vnpy.gateway.ctp import CtpGateway
from vnpy.gateway.tiger import TigerGateway
from vnpy.gateway.oes import OesGateway
from vnpy.gateway.okex import OkexGateway

from vnpy.app.cta_strategy import CtaStrategyApp
from vnpy.app.csv_loader import CsvLoaderApp


def main():
    """"""
    qapp = create_qapp()

    event_engine = EventEngine()

    main_engine = MainEngine(event_engine)
    # main_engine.add_gateway(CtpGateway)
    # main_engine.add_gateway(IbGateway)
    # main_engine.add_gateway(FutuGateway)
    # main_engine.add_gateway(BitmexGateway)
    # main_engine.add_gateway(TigerGateway)
    # main_engine.add_gateway(OesGateway)
    main_engine.add_gateway(OkexGateway)

    main_engine.add_app(CtaStrategyApp)
    main_engine.add_app(CsvLoaderApp)

    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()


if __name__ == "__main__":
    main()
