# encoding: UTF-8

from __future__ import print_function
import json
import requests
import traceback
import ssl
from threading import Thread
from queue import Queue, Empty
import time
import hmac
import base64
import hashlib
import websocket

from six.moves import input

WEBSOCKET_V2_URL = 'wss://api.bitfinex.com/ws/2'
RESTFUL_V1_URL = 'https://api.bitfinex.com/v1'
RESTFUL_V1_DOMAIN = 'https://api.bitfinex.com'


########################################################################
class BitfinexApi(object):
    """"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.ws = None
        self.thread = None

        self.active = False  # 初始化策略的启动状态为

        self.restQueue = Queue()
        self.restThread = None

        self.apiKey = "AmvX7LQ6YT"
        self.secretKey = "UspYAXbIBzoReEPFl"

    # ----------------------------------------------------------------------
    def start(self):
        """"""
        self.ws = websocket.create_connection(WEBSOCKET_V2_URL,
                                              sslopt={'cert_reqs': ssl.CERT_NONE})

        self.active = True

        self.thread = Thread(target=self.run)  # wes 线程启动
        self.thread.start()

        self.restThread = Thread(target=self.runRest)  # rest 线程启动
        self.restThread.start()

        self.onConnect()

    # ----------------------------------------------------------------------
    def reconnect(self):
        """"""
        self.ws = websocket.create_connection(WEBSOCKET_V2_URL,
                                              sslopt={'cert_reqs': ssl.CERT_NONE})

        self.onConnect()

    # ----------------------------------------------------------------------
    def run(self):
        """"""
        while self.active:
            try:
                stream = self.ws.recv()
                data = json.loads(stream)
                self.onData(data)
            except:
                msg = traceback.format_exc()
                self.onError(msg)
                self.reconnect()

    # ----------------------------------------------------------------------
    def runRest(self):
        """"""
        while self.active:
            try:
                path, callback, post = self.restQueue.get(timeout=1)
                if post:
                    self.httpPost(path, callback)
                else:
                    self.httpGet(path, callback)
            except Empty:
                pass
            except Exception as e:
                print(traceback.format_exc())

    # ----------------------------------------------------------------------
    def close(self):
        """"""
        self.active = False

        if self.thread:
            self.thread.join()

        if self.restThread:
            self.thread.join()

    # ----------------------------------------------------------------------
    def onConnect(self):
        """"""
        print('connected')

    # ----------------------------------------------------------------------
    def onData(self, data):
        """"""
        print(data)

    # ----------------------------------------------------------------------
    def onError(self, msg):
        """"""
        print(msg)

    # ----------------------------------------------------------------------
    def sendReq(self, req):
        """"""
        self.ws.send(json.dumps(req))

        # ----------------------------------------------------------------------

    def sendRestReq(self, path, callback, post):
        """"""
        self.restQueue.put((path, callback, post))

    # ----------------------------------------------------------------------
    def httpGet(self, path, callback):
        """"""
        url = RESTFUL_V1_URL + path
        resp = requests.get(url)
        callback(resp.json())

    def __signature(self, payload):
        j = json.dumps(payload)
        data = base64.standard_b64encode(j.encode('utf8'))

        h = hmac.new(self.secretKey.encode('utf8'), data, hashlib.sha384)
        signature = h.hexdigest()
        return {
            "X-BFX-APIKEY": self.apiKey,
            "X-BFX-SIGNATURE": signature,
            "X-BFX-PAYLOAD": data
        }

    def _post(self, path, params):
        body = params
        rawBody = json.dumps(body)
        headers = self.__signature(body)
        url = RESTFUL_V1_DOMAIN + path
        resp = requests.post(url, headers=headers, data=rawBody, verify=True)

        return resp

    def httpPost(self, path, callback):
        """"""
        if path.startswith("/"):
            v1_path = "/v1" + path
        else:
            v1_path = '/v1/' + path

        payload = {
            'request': v1_path,
            'nonce': str(int(time.time() * 1000000))  # nonce
        }
        resp = self._post(v1_path, payload)
        callback(resp.json())



                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  'You will find the correct ones under margin_limits, for each pair. Please update your code as soon as possible.'}]]