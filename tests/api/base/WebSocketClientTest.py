# encoding: UTF-8
import sys
import unittest
import uuid

from Promise import Promise
from vnpy.api.websocket import WebsocketClient


class TestWebsocketClient(WebsocketClient):
    
    def __init__(self):
        host = 'wss://echo.websocket.org'
        super(TestWebsocketClient, self).__init__()
        self.init(host)
        self.p = Promise()
        self.cp = Promise()
    
    def onPacket(self, packet):
        self.p.set_result(packet)
        pass
    
    def onConnected(self):
        self.cp.set_result(True)
        pass
    
    def onError(self, exceptionType, exceptionValue, tb):
        self.p.set_exception(exceptionValue)
        pass


class WebsocketClientTest(unittest.TestCase):
    
    def setUp(self):
        self.c = TestWebsocketClient()
        self.c.start()
        self.c.cp.get(3) # wait for connected
    
    def tearDown(self):
        self.c.stop()
    
    def test_sendReq(self):
        req = {
            'name': 'val'
        }
        self.c.sendPacket(req)
        res = self.c.p.get(3)
        
        self.assertEqual(res, req)

    def test_parseError(self):
        class CustomException(Exception): pass
    
        def onPacket(packet):
            raise CustomException("Just a exception")
    
        self.c.onPacket = onPacket
        req = {
            'name': 'val'
        }
        self.c.sendPacket(req)
    
        with self.assertRaises(CustomException):
            self.c.p.get(3)


class WebsocketClientErrorHandleTest(unittest.TestCase):
    
    def setUp(self):
        
        self.c = TestWebsocketClient()
        self.c.start()
        self.c.cp.get(3) # wait for connected

        self.org_sys_hook = sys.excepthook
        self.org_sys_stderr_write = sys.stderr.write
        
        sys.excepthook = self.nop
        sys.stderr.write = self.nop

    @staticmethod
    def nop(*args, **kwargs):
        pass
    
    def tearDown(self):
        self.c.stop()
        sys.excepthook = self.org_sys_hook
        sys.stderr.write = self.org_sys_stderr_write
    
    def test_onError(self):
        target= uuid.uuid4()
        """这个测试保证onError内不会再抛Exception"""
        class CustomException(Exception):
            pass
        
        def onPacket(packet):
            raise CustomException("Just a exception")
        
        def onError(*args, **kwargs):
            try:
                super(TestWebsocketClient, self.c).onError(*args, **kwargs)
                self.c.p.set_result(target)
            except:
                self.c.p.set_result(False)
                
        self.c.onPacket = onPacket
        self.c.onError = onError
        
        req = {
            'name': 'val'
        }
        self.c.sendPacket(req)
    
        res = self.c.p.get(3)
        self.assertEqual(target, res)


if __name__ == '__main__':
    unittest.main()
