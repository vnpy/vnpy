# encoding: UTF-8

__author__ = 'lamter'


import traceback
import vtGlobal
import doctest
import threading
import datetime as dt
import json


def autoShutdown(mainEngine):
    # 设置自动关闭

    now, closeTime = _getShutdownTime()
    print(u"Auto shutdown at %s  ..." % closeTime)
    print(u'use "--no-shutdown" parameter to ban this func.')

    def shutdonw():
        print(u"time to shutdown vnpy ...")
        mainEngine.setTime2Shutdown()
        mainEngine.exit()

    closeRestSeconds = (closeTime - now).total_seconds()
    threading.Timer(closeRestSeconds, shutdonw).start()


def autoUIShutdown(mainEngine, mainWindow):
    """
    PyQT4 UI 模式下的自动关闭
    :param mainEngine:
    :param mainWindows:
    :return:
    """

    now, closeTime = _getShutdownTime()
    print(u"Auto shutdown at %s  ..." % closeTime)
    print(u'use "--no-shutdown" parameter to ban this func.')

    def shutdonw():
        print(u"time to shutdown vnpy ...")
        mainEngine.setTime2Shutdown()
        mainWindow.close()

    closeRestSeconds = (closeTime - now).total_seconds()
    threading.Timer(closeRestSeconds, shutdonw).start()


def _getShutdownTime():
    """
    定时关闭的时间点

    >>> import json
    >>> with open("VT_setting.json", 'r') as f:
    ...     setting = json.load(f)
    >>> shutdownTimeList = setting['shutdown']
    >>> sdt = [dt.time(*map(int, t.split(":"))) for t in shutdownTimeList]
    >>> sdt.sort()
    >>> sdt
    [datetime.time(3, 1), datetime.time(15, 31)]

    :return:
    """
    datetime = dt.datetime
    now = datetime.now()
    today = dt.date.today()
    tomorrow = today + dt.timedelta(days=1)


    # 从配置文件读取自动关闭时间
    f = file(vtGlobal.cmdArgs.VT_setting)
    setting = json.load(f)
    shutdownTimeList = setting['shutdown']

    if shutdownTimeList:

        # 分解读取关闭时间，并实例化
        sdt = [dt.time(*map(int, t.split(":"))) for t in shutdownTimeList]

        sdt.sort()
        for t in sdt:
            if now.time() < t:
                closeTime = datetime.combine(today, t)
                break
        else:
            # 次日第一个
            closeTime = datetime.combine(tomorrow, sdt[0])

    else:
        # 配置文件没有自动关闭时间，硬编码自动关闭时间
        if now.time() < dt.time(3, 10):
            # 凌晨，夜盘收市后关闭
            closeTime = datetime.combine(today, dt.time(3, 10))
        elif now.time() < dt.time(15, 40):
            # 下午，日盘收盘后关闭
            closeTime = datetime.combine(today, dt.time(15, 40))
        else:
            # 晚上，夜盘收盘后关闭
            closeTime = datetime.combine(tomorrow, dt.time(3, 10))

    return now, closeTime

if __name__ == "__main__":
    doctest.testmod()