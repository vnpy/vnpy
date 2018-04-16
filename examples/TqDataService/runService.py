# encoding: UTF-8

"""
定时服务，可无人值守运行，实现每日自动下载更新历史行情数据到数据库中。

注意: 请确保本程序运行时, 本机天勤终端 (0.8.0 以上版本)正在运行中
"""
from __future__ import print_function

import time
import datetime

from dataService import downloadAllMinuteBar


if __name__ == '__main__':
    taskCompletedDate = None
    
    # 生成一个随机的任务下载时间，用于避免所有用户在同一时间访问数据服务器
    taskTime = datetime.time(hour=17, minute=0)

    symbols = ["CFFEX.IF1710", "CFFEX.IF1711", "CFFEX.IF1712", "CFFEX.IF1803",
                "CFFEX.IH1710", "CFFEX.IH1711", "CFFEX.IH1712", "CFFEX.IH1803",
                "CFFEX.IC1710", "CFFEX.IC1711", "CFFEX.IC1712", "CFFEX.IC1803"]

    # 进入主循环
    while True:
        t = datetime.datetime.now()
        
        # 每天到达任务下载时间后，执行数据下载的操作
        if t.time() > taskTime and (taskCompletedDate is None or t.date() != taskCompletedDate):
            # 下载1000根分钟线数据，足以覆盖过去两天的行情
            downloadAllMinuteBar(1000, symbols)
            
            # 更新任务完成的日期
            taskCompletedDate = t.date()
        else:
            print(u'当前时间%s，任务定时%s' %(t, taskTime))
    
        time.sleep(60)