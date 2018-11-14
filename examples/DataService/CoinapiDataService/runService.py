# encoding: UTF-8

"""
定时服务，可无人值守运行，实现每日自动下载更新历史行情数据到数据库中。
"""
from __future__ import print_function

from dataService import *


if __name__ == '__main__':
    taskCompletedDate = None
    
    taskTime = datetime.time(hour=22, minute=0)
    
    # 进入主循环
    while True:
        t = datetime.datetime.now()
        
        # 每天到达任务下载时间后，执行数据下载的操作
        if t.time() > taskTime and (taskCompletedDate is None or t.date() != taskCompletedDate):
            end = t.strftime('%Y%m%d')
            start = (t - datetime.timedelta(1)).strftime('%Y%m%d')
            
            # 下载过去24小时的K线数据
            downloadAllMinuteBar(start, end)
            
            # 更新任务完成的日期
            taskCompletedDate = t.date()
        else:
            print(u'当前时间%s，任务定时%s' %(t, taskTime))
    
        time.sleep(60)