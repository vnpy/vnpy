# encoding: UTF-8

import json
import traceback
import unittest

from Promise import Promise
from vnpy.restful.RestfulClient import RestfulClient, requestsSessionProvider


class TestRestfulClient(RestfulClient):
    
    def __init__(self):
        urlBase = 'https://httpbin.org'
        super(TestRestfulClient, self).__init__(urlBase, requestsSessionProvider)
        
        self.p = Promise()
    
    def beforeRequest(self, method, path, params, data):
        data = json.dumps(data)
        return method, path, params, data, {'Content-Type': 'application/json'}
    
    def onError(self, exceptionType, exceptionValue, tb, req):
        traceback.print_exception(exceptionType, exceptionValue, tb)
        self.p.set_exception(exceptionValue)


class RestfulClientTest(unittest.TestCase):
    
    def setUp(self):
        self.c = TestRestfulClient()
        self.c.start()
    
    def tearDown(self):
        self.c.stop()
    
    def test_addReq_get(self):
        args = {'user': 'username',
                'pw': 'password'}
        
        def callback(code, data, req):
            if code == 200:
                self.c.p.set_result(data['args'])
                return
            self.c.p.set_result(False)
        
        self.c.addReq('GET', '/get', callback, params=args)
        res = self.c.p.get(3)
        
        self.assertEqual(args, res)
    
    def test_addReq_post(self):
        body = {'user': 'username',
                'pw': 'password'}
        
        def callback(code, data, req):
            if code == 200:
                self.c.p.set_result(data['json'])
                return
            self.c.p.set_result(False)
        
        self.c.addReq('POST', '/post', callback, data=body)
        res = self.c.p.get(3)
        
        self.assertEqual(body, res)
