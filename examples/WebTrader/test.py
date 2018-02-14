# encoding: UTF-8

from socketIO_client import SocketIO, BaseNamespace
from time import sleep
from threading import Thread
import logging


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


########################################################################
class TestNamespace(BaseNamespace):
    """"""

    #----------------------------------------------------------------------
    def on_connect(self):
        """连接"""
        print 'on connect'
    
    #----------------------------------------------------------------------
    def on_disconnect(self):
        """断开"""
        print 'disconnect'
    
    #----------------------------------------------------------------------
    def on_reconnect(self):
        """重连"""
        print 'reconnect'
    
    #----------------------------------------------------------------------
    def on_message(self, *args):
        """测试"""
        print 'on_message', args
    
    


if __name__ == '__main__':
    #logging.getLogger('socketIO-client').setLevel(logging.DEBUG)
    #logging.basicConfig()    

    sio = SocketIO('127.0.0.1', 5000, TestNamespace, transports='websocket')
    sio.wait()
    