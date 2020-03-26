"""
Author: Aaron Qiu
"""
from vnpy.trader.ui.widget import (
    TickMonitor,
    LogMonitor,
    TradeMonitor,
    OrderMonitor,
    ActiveOrderMonitor,
    PositionMonitor,
    AccountMonitor,
)
from asciimatics.widgets import (
    Frame,
    MultiColumnListBox,
    Layout,
    Divider,
    Text,
    Label,
    Button,
    TextBox,
    Widget,
    VerticalDivider,
)
from enum import Enum
from asciimatics.scene import Scene
from asciimatics.screen import Screen
from asciimatics.exceptions import ResizeScreenError, NextScene, StopApplication
import sys

import multiprocessing
from time import sleep
from datetime import datetime, time
from logging import INFO

from vnpy.event import EventEngine
from vnpy.trader.setting import SETTINGS
from vnpy.trader.engine import MainEngine

from vnpy.gateway.ctp import CtpGateway
from vnpy.app.cta_strategy import CtaStrategyApp
from vnpy.app.cta_strategy.base import EVENT_CTA_LOG

from vnpy.trader.utility import load_json

CTP_SETTING = load_json("connect_ctp.json")

SETTINGS["log.active"] = True
SETTINGS["log.level"] = INFO
SETTINGS["log.console"] = True
log_datas = []


FRAME_NO = "mainwindows"
TICK_LAYOUT = {
    "name": "Quotes",
    "monitor": TickMonitor,
    "titles": [
        "symbol",
        "exchange",
        "last_price",
        "volume",
        "open_price",
        "high_price",
        "low_price",
        "bid_price_1",
        "bid_volume_1",
        "ask_price_1",
        "ask_volume_1",
        "datetime",
        "gateway_name",
        # "name",
    ],
    "data_key": "ticks",
    "height": 10,
    "columns": [
        "<20",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<30",
        "<15",
        "<30",
    ],
}
ACTIVE_ORDERS_LAYOUT = {
    "name": "Active Orders",
    "monitor": ActiveOrderMonitor,
    "titles": ActiveOrderMonitor.headers.keys(),
    "data_key": "active_orders",
    "height": 10,
    "columns": [
        "<20",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<30",
        "<15",
        "<15",
        "<15",
        "<30",
        "<15",
    ],
}
ORDERS_LAYOUT = {
    "name": "Orders",
    "monitor": OrderMonitor,
    "titles": OrderMonitor.headers.keys(),
    "data_key": "orders",
    "height": 10,
    "columns": [
        "<20",
        "<15",
        "<15",
        "<30",
        "<30",
        "<30",
        "<15",
        "<15",
        "<15",
        "<30",
        "<15",
        "<30",
        "<15",
    ],
}
TRADE_LAYOUT = {
    "name": "Trade",
    "monitor": TradeMonitor,
    "titles": TradeMonitor.headers.keys(),
    "data_key": "trades",
    "height": 10,
    "columns": [
        "<20",
        "<15",
        "<15",
        "<15",
        "<30",
        "<30",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<30",
        "<15",
    ],
}
LOG_LAYOUT = {
    "name": "Log",
    "monitor": LogMonitor,
    "titles": ["time", "gateway_name", "msg"],
    "data_key": "logs",
    "height": 20,
    "columns": [
        "<30",
        "<30",
        "<60",
    ],
}
POSITION_LAYOUT = {
    "name": "Position",
    "monitor": PositionMonitor,
    "titles": PositionMonitor.headers.keys(),
    "data_key": "positions",
    "height": 20,
    "columns": [
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
    ],
}
ACCOUNT_LAYOUT = {
    "name": "Account",
    "monitor": AccountMonitor,
    "titles": AccountMonitor.headers.keys(),
    "data_key": "accounts",
    "height": 20,
    "columns": [
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
        "<15",
    ],
}

def save_logs(event):
    log_datas.append((datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f"), event.data,))


class MainView(Frame):
    def __init__(self, screen, main_engine):
        super(MainView, self).__init__(
            screen,
            screen.height,
            screen.width,
            on_load=self._load_data,
            hover_focus=True,
            can_scroll=True,
            title="VNPY Terminal UI",
            name=FRAME_NO,
        )
        self.set_theme("bright")
        self.ticks = []
        self.active_orders = []
        self.orders = []
        self.trades = []
        self.logs = []
        self.positions = []
        self.accounts = []

        self.oms_engine = main_engine.engines["oms"]
        self.update_options()
        self.draw_header_layouts()
        self.draw_content_layouts()
        self.draw_footer_layouts()
        self.fix()

    def draw_content_layouts(self):
        """"""
        self.create_layout(TICK_LAYOUT)
        self.create_layout(ACTIVE_ORDERS_LAYOUT,)
        self.create_layout(ORDERS_LAYOUT)
        self.create_layout(TRADE_LAYOUT)
        # self.create_layout(LOG_LAYOUT)

    def draw_header_layouts(self):
        """"""
        pass

    def draw_footer_layouts(self):
        """"""
        footer_configs = [ACCOUNT_LAYOUT, POSITION_LAYOUT]
        layout = Layout([1, 1])
        self.add_layout(layout)

        for index, config in enumerate(footer_configs):
            layout.add_widget(VerticalDivider(), index)
            layout.add_widget(Divider(), index)
            layout.add_widget(Label(config["name"], align="^"), index)
            layout.add_widget(Divider(), index)
            box = MultiColumnListBox(
                config["height"],
                columns=config["columns"],
                options=self.__dict__[config["data_key"]],
                titles=config["titles"],
                name=config["name"],
                add_scroll_bar=True,
            )
            layout.add_widget(box, index)

    def update_options(self):
        self.ticks = self.get_options(self.oms_engine.ticks, TICK_LAYOUT["titles"])
        self.active_orders = self.get_options(
            self.oms_engine.active_orders, ACTIVE_ORDERS_LAYOUT["titles"]
        )
        self.orders = self.get_options(self.oms_engine.orders, ORDERS_LAYOUT["titles"])
        self.trades = self.get_options(self.oms_engine.trades, TRADE_LAYOUT["titles"])
        self.positions = self.get_options(
            self.oms_engine.positions, POSITION_LAYOUT["titles"]
        )
        self.accounts = self.get_options(
            self.oms_engine.accounts, ACCOUNT_LAYOUT["titles"]
        )
        # logs
        self.logs = [
            ([log_time, log_data.gateway_name, log_data.msg], index)
            for index, (log_time, log_data) in enumerate(log_datas)
        ]

    def get_options(self, data, titles):
        options = []
        if len(data.values()) != 0:
            for index, tick in enumerate(data.values()):
                row = []
                for x in titles:
                    node = tick.__dict__[x]
                    if isinstance(node, Enum):
                        row.append(node.value)
                    elif isinstance(node, datetime):
                        row.append(node.strftime("%Y-%m-%d %H:%M:%S.%f"))
                    else:
                        row.append(str(node))

                options.append((row, index))
        return options

    def create_layout(self, config, fill_frame=False):
        """
        生成layout
        """
        layout = Layout([100], fill_frame)
        self.add_layout(layout)
        layout.add_widget(Divider())
        layout.add_widget(Label(config["name"], align="^"))
        layout.add_widget(Divider())
        box = MultiColumnListBox(
            config["height"],
            columns=config["columns"],
            options=self.__dict__[config["data_key"]],
            titles=config["titles"],
            name=config["name"],
            add_scroll_bar=True,
        )
        layout.add_widget(box)
        return layout

    def _load_data(self, new_value=None):
        pass

    @staticmethod
    def _quit():
        raise StopApplication("User pressed quit")


def vnpy_tui(screen, scene, main_engine):
    main_scene = MainView(screen, main_engine)
    scenes = [
        Scene([main_scene], -1, name="Main", clear=False),
    ]
    screen.play(scenes, stop_on_resize=True, start_scene=scene, allow_int=True)


def run_child():
    """
    Running in the child process.
    """
    SETTINGS["log.file"] = True

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    main_engine.add_gateway(CtpGateway)
    cta_engine = main_engine.add_app(CtaStrategyApp)
    main_engine.write_log("主引擎创建成功")

    log_engine = main_engine.get_engine("log")
    event_engine.register(EVENT_CTA_LOG, log_engine.process_log_event)
    event_engine.register(EVENT_CTA_LOG, save_logs)
    main_engine.write_log("注册日志事件监听")

    main_engine.connect(CTP_SETTING, "CTP")
    main_engine.write_log("连接CTP接口")

    sleep(5)

    cta_engine.init_engine()
    main_engine.write_log("CTA策略初始化完成")

    cta_engine.init_all_strategies()
    sleep(5)  # Leave enough time to complete strategy initialization
    main_engine.write_log("CTA策略全部初始化")
    cta_engine.start_all_strategies()

    main_engine.write_log("CTA策略全部启动")
    last_scene = None
    while True:
        try:
            Screen.wrapper(
                vnpy_tui, catch_interrupt=True, arguments=[last_scene, main_engine],
            )
            sys.exit(0)
        except ResizeScreenError as e:
            last_scene = e.scene
        sleep(0.1)


def run_parent():
    """
    Running in the parent process.
    """
    print("启动CTA策略守护父进程")

    # Chinese futures market trading period (day/night)
    DAY_START = time(8, 45)
    DAY_END = time(15, 30)

    NIGHT_START = time(20, 45)
    NIGHT_END = time(2, 45)

    child_process = None
    while True:
        # run cta child process
        current_time = datetime.now().time()
        trading = False

        # Check whether in trading period
        if (
            (current_time >= DAY_START and current_time <= DAY_END)
            or (current_time >= NIGHT_START)
            or (current_time <= NIGHT_END)
        ):
            trading = True

        # Start child process in trading period
        if trading and child_process is None:
            print("启动子进程")
            child_process = multiprocessing.Process(target=run_child)
            child_process.start()
            print("子进程启动成功")

        # 非记录时间则退出子进程
        if not trading and child_process is not None:
            print("关闭子进程")
            child_process.terminate()
            child_process.join()
            child_process = None
            print("子进程关闭成功")

        sleep(5)


if __name__ == "__main__":

    run_parent()
