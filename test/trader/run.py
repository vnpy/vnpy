from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp

from vnpy.trader.ui.widget import TickMonitor

if __name__ == "__main__":
    qapp = create_qapp()

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)

    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    monitor = TickMonitor(main_engine, event_engine)
    monitor.show()

    qapp.exec()