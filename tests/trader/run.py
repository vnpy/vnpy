
from vnpy.event import EventEngine

from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp

from vnpy.gateway.bitmex import BitmexGateway
from vnpy.gateway.bitfinex import BitfinexGateway
#from vnpy.gateway.futu import FutuGateway
#from vnpy.gateway.ib import IbGateway
from vnpy.gateway.ctp import CtpGateway

from vnpy.app.cta_strategy import CtaStrategyApp


def main():
    """"""
    qapp = create_qapp()

    event_engine = EventEngine()

    main_engine = MainEngine(event_engine)
    main_engine.add_gateway(CtpGateway)
    #main_engine.add_gateway(IbGateway)
    #main_engine.add_gateway(FutuGateway)
    main_engine.add_gateway(BitmexGateway)
    main_engine.add_gateway(BitfinexGateway)

    main_engine.add_app(CtaStrategyApp)

    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()


if __name__ == "__main__":
    main()
