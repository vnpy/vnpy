# encoding: utf-8
"""
@Author: Skeeterfly
@E-mail: 67806596@qq.com
@Wechat: 67806596
@site: http://www.dacaoshou.com/
@software: PyCharm
@file: algo_run.py.py
@time: 2020-02-26 下午 15:26 
"""
import multiprocessing
from datetime import time
from logging import INFO
from time import sleep

from vnpy.app.algo_trading import AlgoTradingApp
from vnpy.app.cta_strategy.base import EVENT_CTA_LOG
from vnpy.event import EventEngine
from vnpy.gateway.hbdm import HbdmGateway
from vnpy.trader.engine import MainEngine
from vnpy.trader.setting import SETTINGS

SETTINGS["log.active"] = True
SETTINGS["log.level"] = INFO
SETTINGS["log.console"] = True

default_setting = {
    "API Key": "",
    "Secret Key": "",
    "会话数": 5,
    "代理地址": "",
    "代理端口": "",
}


def run_child():
    """
    Running in the child process.
    """
    SETTINGS["log.file"] = True

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)

    # 使用火币交易所
    main_engine.add_gateway(HbdmGateway)
    algo_engine = main_engine.add_app(AlgoTradingApp)

    main_engine.write_log("主引擎创建成功")

    log_engine = main_engine.get_engine("log")
    event_engine.register(EVENT_CTA_LOG, log_engine.process_log_event)
    main_engine.write_log("注册日志事件监听")

    main_engine.connect(default_setting, "HBDM")
    main_engine.write_log("连接HBDM接口, 请稍等！")
    sleep(60)

    # 算法引擎
    algo_engine.init_engine()
    main_engine.write_log("算法策略初始化完成")
    algo_engine.start_all_strategy()

    while True:
        sleep(1)


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
        trading = True
        # # 以下检查程序的运行开启和关闭时间，如果交易时间在此范围内，则开启！
        # current_time = datetime.now().time()
        # if (
        #         (current_time >= DAY_START and current_time <= DAY_END)
        #         or (current_time >= NIGHT_START)
        #         or (current_time <= NIGHT_END)
        # ):
        #     trading = True

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
