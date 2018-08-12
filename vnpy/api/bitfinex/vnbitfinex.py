# encoding: UTF-8

from __future__ import print_function
import json
import requests
import traceback
import ssl
from threading import Thread
from queue import Queue, Empty

import websocket

from six.moves import input


WEBSOCKET_V2_URL = 'wss://api.bitfinex.com/ws/2'
RESTFUL_V1_URL = 'https://api.bitfinex.com/v1'


########################################################################
class BitfinexApi(object):
    """"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.ws = None
        self.thread = None
        self.active = False
        
        self.restQueue = Queue()
        self.restThread = None
    
    #----------------------------------------------------------------------
    def start(self):
        """"""
        self.ws = websocket.create_connection(WEBSOCKET_V2_URL,
                                              sslopt={'cert_reqs': ssl.CERT_NONE})
        
        self.active = True
        self.thread = Thread(target=self.run)
        self.thread.start()
        
        self.restThread = Thread(target=self.runRest)
        self.restThread.start()
        
        self.onConnect()
    
    #----------------------------------------------------------------------
    def reconnect(self):
        """"""
        self.ws = websocket.create_connection(WEBSOCKET_V2_URL,
                                              sslopt={'cert_reqs': ssl.CERT_NONE})   
        
        self.onConnect()
        
    #----------------------------------------------------------------------
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
    
    #----------------------------------------------------------------------
    def close(self):
        """"""
        self.active = False
        
        if self.thread:
            self.thread.join()
        
        if self.restThread:
            self.thread.join()
    
    #----------------------------------------------------------------------
    def onConnect(self):
        """"""
        print('connected')
    
    #----------------------------------------------------------------------
    def onData(self, data):
        """"""
        print(data)
    
    #----------------------------------------------------------------------
    def onError(self, msg):
        """"""
        print(msg)
    
    #----------------------------------------------------------------------
    def sendReq(self, req):
        """"""
        self.ws.send(json.dumps(req))  
        
    #----------------------------------------------------------------------
    def sendRestReq(self, path, callback):
        """"""
        self.restQueue.put((path, callback))
    
    #----------------------------------------------------------------------
    def runRest(self):
        """"""
        while self.active:
            try:
                path, callback = self.restQueue.get(timeout=1)
                self.httpGet(path, callback)
            except Empty:
                pass
    
    #----------------------------------------------------------------------
    def httpGet(self, path, callback):
        """"""
        url = RESTFUL_V1_URL + path
        resp = requests.get(url)
        callback(resp.json())



if __name__ == '__main__':
    api = BitfinexApi()
    api.start()
    
    d = {
        'event': 'subscribe',
        'channel': 'book',
        'symbol': 'BTCUSD'
    }
    api.sendReq(d)
    
    input()
