# encoding: UTF-8

import sys
from time import sleep

from PyQt4 import QtGui

from vncshshlp import *


branch_no = ''


#----------------------------------------------------------------------
def print_list(l):
    """"""
    for d in l:
        print d

#----------------------------------------------------------------------
def print_dict(d):
    """按照键值打印一个字典"""
    for key,value in d.items():
        print key + ':' + str(value)
        
        
#----------------------------------------------------------------------
def simple_log(func):
    """简单装饰器用于输出函数名"""
    def wrapper(*args, **kw):
        print '-' * 20
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
    def onMsg(self, type_, data, reqNo, errorNo, errorInfo):
        """"""
        print 'type:', type_
        print_list(data)
        print 'reqNo:', reqNo
        print 'errorNo:', errorNo
        print 'errorInfo:', errorInfo

#----------------------------------------------------------------------
def test():
    """测试用"""
    api = TestHlp()
    
    # 读取配置文件 
    i = api.loadConfig("Hsconfig.ini")
    if i:
        print u'加载配置失败：', i
    print u'加载配置成功'
    
    # 初始化
    i = api.init()
    if i:
        print u'初始化失败：', i
    print u'初始化成功'

    # 连接服务器
    i = api.connectServer()
    if i:
        print u'服务器连接失败：', i
    print u'服务器连接成功'
    
    # 登录
    print u'尝试登录'
    i = api.beginParam()
    api.setValue("identity_type", "2")
    api.setValue("password_type", "2")
    api.setValue("input_content", "1")
    api.setValue("op_entrust_way", "5")
    api.setValue("password", "")
    api.setValue("account_content", "")
    i = api.bizCallAndCommit(331100)
    print '登录reqNo:', i  
    
    print 'done'
    
    raw_input()
        
        
if __name__ == '__main__':
    test()