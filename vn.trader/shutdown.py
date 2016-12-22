# encoding: UTF-8

import threading


def autoShutdown(mainEngine):
    waitSecond = 20  # 秒
    print(u"shutdown after %s sec  ..." % waitSecond)
    print(u'use "--no-shutdown" parameter to ban this func.')

    def shutdonw():
        print(u"time to close vnpy ...")
        mainEngine.exit()

    threading.Timer(waitSecond, autoShutdown).start()



