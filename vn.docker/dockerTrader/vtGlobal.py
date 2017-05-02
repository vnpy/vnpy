# encoding: UTF-8

"""
全局对象，请不要抢在 vtServer 或者 vtClient 模块之前 import
"""

from argparse import ArgumentParser

# 命令行启动的参数
cmdArgs = None  # argparse.ArgumentParser().parse_args()
VT_setting = None
