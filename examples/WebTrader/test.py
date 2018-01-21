# encoding: UTF-8

from socketIO_client import SocketIO, LoggingNamespace
from time import sleep
from threading import Thread

#----------------------------------------------------------------------
def on_connect():
    """连接"""
    print 'on connect'

#----------------------------------------------------------------------
def on_disconnect():
    """断开"""
    print 'disconnect'

#----------------------------------------------------------------------
def on_reconnect():
    """重连"""
    print 'reconnect'

#----------------------------------------------------------------------
def on_test(*args):
    """测试"""
    print 'on_test', args


if __name__ == '__main__':
    sio = SocketIO('127.0.0.1', 5000, LoggingNamespace)
    sio.on('connect', on_connect)
    sio.on('disconnect', on_disconnect)
    sio.on('reconnect', on_reconnect)
    sio.on('test', on_test)
    
    t = Thread(target=sio.wait)
    t.start()
    
    while True:
        sleep(1)
