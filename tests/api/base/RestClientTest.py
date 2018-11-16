# encoding: UTF-8

import json
import sys
import unittest
import uuid

from simplejson import JSONDecodeError

from Promise import Promise
from vnpy.api.rest.RestClient import Request, RestClient


class FailedError(RuntimeError):
    pass


class TestRestClient(RestClient):

    def __init__(self):
        urlBase = 'https://httpbin.org'
        super(TestRestClient, self).__init__()
        self.init(urlBase)

        self.p = Promise()

    def sign(self, req):  #type: (Request)->Request
        req.data = json.dumps(req.data)
        req.headers = {'Content-Type': 'application/json'}
        return req

    def onError(self, exceptionType, exceptionValue, tb, req):
        self.p.set_exception(exceptionType, exceptionValue, tb)

    def onFailed(self, httpStatusCode, req):
        with self.p.catch():
            raise FailedError("request failed")


class RestfulClientTest(unittest.TestCase):

    def setUp(self):
        self.c = TestRestClient()
        self.c.start()

    def tearDown(self):
        self.c.stop()

    def test_addReq_get(self):
        args = {'user': 'username',
                'pw': 'password'}

        def callback(data, req):
            self.c.p.set_result(data['args'])

        self.c.addRequest('GET', '/get', callback, params=args)
        res = self.c.p.get(3)

        self.assertEqual(args, res)

    def test_addReq_post(self):
        body = {'user': 'username',
                'pw': 'password'}

        def callback(data, req):
            self.c.p.set_result(data['json'])

        self.c.addRequest('POST', '/post', callback, data=body)
        res = self.c.p.get(3)

        self.assertEqual(body, res)

    def test_addReq_onFailed(self):
        def callback(data, req):
            pass

        self.c.addRequest('POST', '/status/401', callback)
        with self.assertRaises(FailedError):
            self.c.p.get(3)

    def test_addReq_jsonParseError(self):
        def callback(data, req):
            pass

        self.c.addRequest('GET', '/image/svg', callback)
        with self.assertRaises(JSONDecodeError):
            self.c.p.get(3)


class RestfulClientErrorHandleTest(unittest.TestCase):

    def setUp(self):
        self.c = TestRestClient()
        self.c.start()

        self.org_sys_hook = sys.excepthook
        self.org_sys_stderr_write = sys.stderr.write

        sys.excepthook = self.nop
        sys.stderr.write = self.nop

    def tearDown(self):
        self.c.stop()

    @staticmethod
    def nop(*args, **kwargs):
        pass

    def test_onError(self):
        """这个测试保证onError内不会再抛异常"""
        target = uuid.uuid4()

        def callback(data, req):
            pass

        def onError(*args, **kwargs):
            try:
                super(TestRestClient, self.c).onError(*args, **kwargs)
                self.c.p.set_result(target)
            except:
                self.c.p.set_result(False)
        self.c.onError = onError

        self.c.addRequest('GET', '/image/svg', callback)

        res = self.c.p.get(3)
        self.assertEqual(target, res)


if __name__ == '__main__':
    unittest.main()
