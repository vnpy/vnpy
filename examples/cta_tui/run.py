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
from vnpy.trader.object import Exchange
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


SETTINGS["log.active"] = True
SETTINGS["log.level"] = INFO
SETTINGS["log.console"] = True

TICK_COLUMNS = ["<20", "<15", "30", "<15", "<15", "<15", "<15", "<15", "<15", "<15", "<15", "<15", "<30", "<15"]
ACTIVE_ORDERS_COLUMNS = ["<20", "<15", "<15", "<15", "<15", "<15", "<15", "<30", "<15", "<15", "<15", "<30", "<15"]
ORDERS_COLUMNS = ["<20", "<15", "<15", "<30", "<30", "<30", "<15", "<15", "<15", "<30", "<15", "<30", "<15"]
TRADE_COLUMNS = ["<20", "<15", "<15", "<15", "<30", "<30", "<15", "<15", "<15", "<15", "<15", "<30", "<15"]

from vnpy.trader.utility import load_json

CTP_SETTING = load_json("connect_ctp.json")


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
            reduce_cpu=True,
            name="mainwindows",
        )
        self.oms_engine = main_engine.engines["oms"]
        self.update_options()
        self.tables = []

        self.set_theme("bright")
        # 信息区域
        layout_tick = self.create_layout(
            "行情",
            TickMonitor,
            15,
            TICK_COLUMNS,
            options=self.ticks,
        )
        layout_active_orders = self.create_layout(
            "活动委托",
            ActiveOrderMonitor,
            5,
            ACTIVE_ORDERS_COLUMNS,
            options=self.active_orders,
        )
        layout_order = self.create_layout(
            "委托",
            OrderMonitor,
            15,
            ORDERS_COLUMNS,
            options=self.orders,
        )
        layout_trade = self.create_layout(
            "成交",
            TradeMonitor,
            15,
            TRADE_COLUMNS,
            options=self.trades,
            fill_frame=True,
        )
        self.fix()

    def update_options(self):
        self.ticks = self.get_options(self.oms_engine.ticks, TickMonitor)
        self.active_orders = self.get_options(self.oms_engine.active_orders, ActiveOrderMonitor)
        self.orders = self.get_options(self.oms_engine.orders, OrderMonitor)
        self.trades = self.get_options(self.oms_engine.trades, TradeMonitor)

    def get_options(self, data, monitor):
        options = []
        if len(data.values()) != 0:
            for index, tick in enumerate(data.values()):
                row = []
                for x in monitor.headers.keys():
                    node = tick.__dict__[x]
                    if type(node) == Exchange:
                        row.append(node.value)
                    elif type(node) == datetime:
                        row.append(node.strftime("%Y-%m-%d %H:%M:%S.%f"))
                    else:
                        row.append(str(node))

                options.append((row, index))
        return options

    def create_layout(
        self, title, monitor, rows, columns_length=[], options=[], fill_frame=False
    ):
        """
        生成layout
        """
        layout = Layout([100], fill_frame)
        self.add_layout(layout)
        layout.add_widget(Divider())
        layout.add_widget(Label(title, align="^"))
        layout.add_widget(Divider())

        titles = monitor.headers.keys()
        box = MultiColumnListBox(
            rows,
            columns=columns_length,
            options=options,
            titles=titles,
            name=title,
            add_scroll_bar=True,
        )
        self.tables.append(box)
        layout.add_widget(box)
        return Layout

    def _load_data(self, new_value=None):
        pass
    
    def _update(self, frame_no):
        """
        update data
        """
        self.update_options()
        for table in self.tables:
            table.update(frame_no)
        super(MainView, self)._update(frame_no)

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
