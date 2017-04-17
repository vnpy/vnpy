# encoding: UTF-8

import sys
from time import sleep

from PyQt4 import QtGui

from vncshshlp import *

#----------------------------------------------------------------------
def print_dict(d):
    """按照键值打印一个字典"""
    for key,value in d.items():
        print key + ':' + str(value)
        
        
#----------------------------------------------------------------------
def simple_log(func):
    """简单装饰器用于输出函数名"""
    def wrapper(*args, **kw):
        print ""
        print str(func.__name__)
        return func(*args, **kw)
    return wrapper


class TestHlp(CsHsHlp):
    #----------------------------------------------------------------------
    def __init__(self):
        """"""
        super(TestHlp, self).__init__()
        
    #----------------------------------------------------------------------
    @simple_log
    def onMsg(self, data):
        """"""
        print_dict(data)
        

#----------------------------------------------------------------------
def test():
    """测试用"""
    api = TestHlp()
    
    # 读取配置文件
    print api.loadConfig("Hsconfig.ini")
    
    # 初始化
    print api.init()
    
    # 连接服务器
    print api.connectServer()
        
        
if __name__ == '__main__':
    test()