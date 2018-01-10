# encoding: utf-8

from vncoincheck import *

import socket
import json
import websocket
from websocket import create_connection

ws = None
def open():
    global ws
    print "open"
    ws.send( json.dumps({"type": "subscribe", "channel": "btc_jpy-trades"}))

def testWebsocket():
    global ws

    while 1:
        ws = create_connection("wss://ws-api.coincheck.com/", on_open=open)
        if ws.connected:
            
            print ws.recv()

    sleep(5)

    # 阻塞
    input()

if __name__ == '__main__':
    testWebsocket()