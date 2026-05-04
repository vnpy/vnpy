from vnpy.event import EventEngine, create_engine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp

from vnpy_rpcservice import RpcGateway
from vnpy_ctastrategy import CtaStrategyApp


def main():
    """"""
    qapp = create_qapp()

    event_engine = create_engine()

    main_engine = MainEngine(event_engine)

    main_engine.add_gateway(RpcGateway)
    main_engine.add_app(CtaStrategyApp)

    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()


if __name__ == "__main__":
    main()
