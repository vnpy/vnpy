# encoding: UTF-8

__author__ = 'lamter'

import threading
import datetime as dt


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


def autoUIShutdown(mainEngine, mainWindows):
    """

    :param mainEngine:
    :param mainWindows:
    :return:
    """

def _getShutdownTime():
    datetime = dt.datetime
    now = datetime.now()
    today = dt.date.today()
    tomorrow = today + dt.timedelta(days=1)

    if now.time() < dt.time(3, 10):
        # 凌晨，夜盘收市后关闭
        closeTime = datetime.combine(today, dt.time(3, 10))
    elif now.time() < dt.time(15, 40):
        # 下午，日盘收盘后关闭
        closeTime = datetime.combine(today, dt.time(15, 40))
    else:
        # 晚上，夜盘收盘后关闭
        closeTime = datetime.combine(today, dt.time(16, 52))
        # closeTime = datetime.combine(tomorrow, dt.time(3, 10))

    return now, closeTime