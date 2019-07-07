from time import sleep

from vnpy.event import EventEngine, Event
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp
from vnpy.trader.event import EVENT_LOG
from vnpy.gateway.ctp import CtpGateway
from vnpy.app.rpc_service import RpcServiceApp
from vnpy.app.rpc_service.engine import EVENT_RPC_LOG


def main_ui():
    """"""
    qapp = create_qapp()

    event_engine = EventEngine()

    main_engine = MainEngine(event_engine)

    main_engine.add_gateway(CtpGateway)
    main_engine.add_app(RpcServiceApp)

    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()


def process_log_event(event: Event):
    """"""
    log = event.data
    msg = f"{log.time}\t{log.msg}"
    print(msg)


def main_terminal():
    """"""
    event_engine = EventEngine()
    event_engine.register(EVENT_LOG, process_log_event)
    event_engine.register(EVENT_RPC_LOG, process_log_event)

    main_engine = MainEngine(event_engine)
    main_engine.add_gateway(CtpGateway)
    rpc_engine = main_engine.add_app(RpcServiceApp)

    setting = {
        "用户名": "25500029",
        "密码": "20140602",
        "经纪商代码": "6010",
        "交易服务器": "180.169.75.194:41305",
        "行情服务器": "180.166.1.17:41313",
        "产品名称": "vntech_vnpy_2.0",
        "授权编码": "0Y1J5UIMY79BFL7S",
        "产品信息": ""
    }
    main_engine.connect(setting, "CTP")
    sleep(10)

    rep_address = "tcp://127.0.0.1:2014"
    pub_address = "tcp://127.0.0.1:4102"
    rpc_engine.start(rep_address, pub_address)

    while True:
        sleep(1)


if __name__ == "__main__":
    # Run in GUI mode
    # main_ui()

    # Run in CLI mode
    main_terminal()
