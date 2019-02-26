# encoding: UTF-8

"""
立即下载数据到数据库中，用于手动执行更新操作。

下载的日期范围在config.json中配置
"""

from dataService import *

if __name__ == '__main__':
    downloadAllMinuteBar(START_DATE, END_DATE)
