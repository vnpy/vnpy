# encoding: UTF-8

import json
import unittest

from simplejson import JSONDecodeError

from Promise import Promise
from vnpy.network.HttpClient import HttpClient


class FailedError(RuntimeError):
    pass


class TestHttpClient(HttpClient):

    def __init__(self):
        urlBase = 'https://httpbin.org'
        super(TestHttpClient, self).__init__()
        self.init(urlBase)
        
        self.p = Promise()
    
    def beforeRequest(self, method, path, params, data):
        data = json.dumps(data)
        return method, path, params, data, {'Content-Type': 'application/json'}
    
    def onError(self, exceptionType, exceptionValue, tb, req):
        self.p.set_exception(exceptionValue)

    def onFailed(self, httpStatusCode, data, req):
        self.p.set_exception(FailedError("request failed"))


class RestfulClientTest(unittest.TestCase):
    
    def setUp(self):
        self.c = TestHttpClient()
        self.c.start()
    
    def tearDown(self):
        self.c.stop()
    
    def test_addReq_get(self):
        args = {'user': 'username',
                'pw': 'password'}

        def callback(data, req):
            self.c.p.set_result(data['args'])
        
        self.c.addReq('GET', '/get', callback, params=args)
        res = self.c.p.get(3)
        
        self.assertEqual(args, res)
    
    def test_addReq_post(self):
        body = {'user': 'username',
                'pw': 'password'}
        
        def callback(data, req):
            self.c.p.set_result(data['json'])
        
        self.c.addReq('POST', '/post', callback, data=body)
        res = self.c.p.get(3)
        
        self.assertEqual(body, res)
        
    def test_addReq_onFailed(self):
        def callback(data, req):
            pass
        
        self.c.addReq('POST', '/status/201', callback)
        with self.assertRaises(FailedError):
            self.c.p.get(3)

    def test_addReq_jsonParseError(self):
        def callback(data, req):
            pass
        
        self.c.addReq('GET', '/image/svg', callback)
        with self.assertRaises(JSONDecodeError):
            self.c.p.get(3)
    
