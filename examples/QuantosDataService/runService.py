# encoding: UTF-8

"""
定时服务，可无人值守运行，实现每日自动下载更新历史行情数据到数据库中。
"""
from __future__ import print_function

import datetime as ddt

from dataService import *


if __name__ == '__main__':
    taskCompletedDate = None
    
    # 生成一个随机的任务下载时间，用于避免所有用户在同一时间访问数据服务器
    taskTime = ddt.time(hour=17, minute=0)
    
    # 进入主循环
    while True:
        t = ddt.datetime.now()
        
        # 每天到达任务下载时间后，执行数据下载的操作
        if t.time() > taskTime and (taskCompletedDate is None or t.date() != taskCompletedDate):
            # 创建API对象
            api = DataApi(DATA_SERVER)
            info, msg = api.login(USERNAME, TOKEN)
            
            if not info:
                print(u'数据服务器登录失败，原因：%s' %msg)    
        
            # 下载数据
            downloadAllMinuteBar(api)            
            
            # 更新任务完成的日期
            taskCompletedDate = t.date()
        else:
            print(u'当前时间%s，任务定时%s' %(t, taskTime))
    
        sleep(60)