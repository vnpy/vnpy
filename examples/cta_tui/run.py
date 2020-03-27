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
import pickle
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

FRAME_NO = "mainwindows"
TICK_LAYOUT = {
    "name": "行情信息",
    "monitor": TickMonitor,
    "titles": TickMonitor.headers.keys(),
    "data_key": "ticks",
    "height": 6,
    "columns": [
        "<20",
        "<15",
        "<30",
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
    ],
}
ACTIVE_ORDERS_LAYOUT = {
    "name": "活动委托信息",
    "monitor": ActiveOrderMonitor,
    "titles": ActiveOrderMonitor.headers.keys(),
    "data_key": "active_orders",
    "height": 6,
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
    "name": "委托信息",
    "monitor": OrderMonitor,
    "titles": OrderMonitor.headers.keys(),
    "data_key": "orders",
    "height": 6,
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
    "name": "交易信息",
    "monitor": TradeMonitor,
    "titles": TradeMonitor.headers.keys(),
    "data_key": "trades",
    "height": 6,
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
    "name": "日志信息",
    "monitor": LogMonitor,
    "titles": LogMonitor.headers.keys(),
    "data_key": "logs",
    "height": 20,
    "columns": ["<30", "<40", "<30"],
}
POSITION_LAYOUT = {
    "name": "持仓信息",
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
    "name": "账户信息",
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


class MainView(Frame):
    def __init__(self, screen, data, logs_data):
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

        self.update_options(data)
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

    def draw_header_layouts(self):
        """"""
        pass

    def draw_footer_layouts(self):
        """"""
        footer_configs = [LOG_LAYOUT, ACCOUNT_LAYOUT, POSITION_LAYOUT]
        layout = Layout([1, 1, 1])
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
                titles=[d["display"] for d in config["monitor"].headers.values()],
                name=config["name"],
                add_scroll_bar=True,
            )
            layout.add_widget(box, index)

    def update_options(self, data):
        if data:
            self.ticks = self.get_options(
                pickle.loads(data["ticks"]), TICK_LAYOUT["titles"]
            )
            self.active_orders = self.get_options(
                pickle.loads(data["active_orders"]), ACTIVE_ORDERS_LAYOUT["titles"]
            )
            self.orders = self.get_options(
                pickle.loads(data["orders"]), ORDERS_LAYOUT["titles"]
            )
            self.trades = self.get_options(
                pickle.loads(data["trades"]), TRADE_LAYOUT["titles"]
            )
            self.positions = self.get_options(
                pickle.loads(data["positions"]), POSITION_LAYOUT["titles"]
            )
            self.accounts = self.get_options(
                pickle.loads(data["accounts"]), ACCOUNT_LAYOUT["titles"]
            )
            logs = []
            for index, log in enumerate(logs_data):
                log_time, log_data = pickle.loads(log)
                logs.append(([log_time, log_data.msg, log_data.gateway_name], index))
            self.logs = logs
        self.save()

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
            titles=[d["display"] for d in config["monitor"].headers.values()],
            name=config["name"],
            add_scroll_bar=True,
        )
        layout.add_widget(box)
        return layout

    def _load_data(self, new_value=None):
        self.update_options(new_value)

    @staticmethod
    def _quit():
        raise StopApplication("User pressed quit")


def run_child(tui_data, logs_data):
    """
    Running in the child process.
    """

    def save_logs(event):
        logs_data.append(
            pickle.dumps((datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f"), event.data,))
        )

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
    oms_engine = main_engine.engines["oms"]
    while True:
        tui_data["ticks"] = pickle.dumps(oms_engine.ticks)
        tui_data["active_orders"] = pickle.dumps(oms_engine.active_orders)
        tui_data["orders"] = pickle.dumps(oms_engine.orders)
        tui_data["trades"] = pickle.dumps(oms_engine.trades)
        tui_data["positions"] = pickle.dumps(oms_engine.positions)
        tui_data["accounts"] = pickle.dumps(oms_engine.accounts)
        sleep(0.5)


def run_parent(tui_data, logs_data):
    """
    Running in the parent process.
    """
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
            child_process = multiprocessing.Process(
                target=run_child, args=(tui_data, logs_data)
            )
            child_process.start()
            print("子进程启动成功")

        # 非记录时间则退出子进程
        if not trading and child_process is not None:
            print("关闭子进程")
            child_process.terminate()
            child_process.join()
            child_process = None
            print("子进程关闭成功")
        sleep(1)


def terminal_ui(screen, scene, tui_data, logs_data):
    main_scene = MainView(screen, data=tui_data, logs_data=logs_data)
    scenes = [
        Scene([main_scene], -1, name="Main", clear=False),
    ]
    screen.play(
        scenes, stop_on_resize=True, start_scene=scene, allow_int=True, repeat=True
    )


if __name__ == "__main__":
    with multiprocessing.Manager() as manager:
        print("启动CTA策略守护父进程")
        tui_data = manager.dict()
        logs_data = manager.list()
        main_scene = None
        last_scene = None
        print("启动守护主进程")
        parent_process = multiprocessing.Process(
            target=run_parent, args=(tui_data, logs_data)
        )
        parent_process.start()
        print("子进程启动成功")
        print("启动界面")
        while True:
            if tui_data:
                try:
                    main_scene = Screen.wrapper(
                        terminal_ui,
                        catch_interrupt=True,
                        arguments=[last_scene, tui_data, logs_data],
                    )
                    sys.exit(0)
                except ResizeScreenError as e:
                    last_scene = e.scene
            if main_scene:
                main_scene.data = tui_data
            sleep(1)
