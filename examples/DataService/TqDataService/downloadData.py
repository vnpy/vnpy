# encoding: UTF-8

"""
立即下载数据到数据库中，用于手动执行更新操作。

注意: 请先在本机启动天勤终端 (0.8.0 以上版本) 并保持运行, 再执行本程序
"""

from dataService import *



if __name__ == '__main__':
    symbols = ["CFFEX.IF1710", "CFFEX.IF1711", "CFFEX.IF1712", "CFFEX.IF1803",
                "CFFEX.IH1710", "CFFEX.IH1711", "CFFEX.IH1712", "CFFEX.IH1803",
                "CFFEX.IC1710", "CFFEX.IC1711", "CFFEX.IC1712", "CFFEX.IC1803"]
    downloadAllMinuteBar(1000, symbols)