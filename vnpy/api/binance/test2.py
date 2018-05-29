# encoding: UTF-8
import hashlib
import zlib
import json
from time import sleep
from threading import Thread

from autobahn.twisted.websocket import WebSocketClientFactory, \
    WebSocketClientProtocol, \
    connectWS
from twisted.internet import reactor, ssl
from twisted.internet.protocol import ReconnectingClientFactory
from twisted.internet.error import ReactorAlreadyRunning
import threading


import websocket    

def onMessage(ws, data):
	print(ws ,data)

BINANCE_STREAM_URL = 'wss://stream.binance.com:9443/ws/bnbbtc@ticker'

ss = websocket.WebSocketApp(BINANCE_STREAM_URL, 
                                         on_message=onMessage)        
    
reactor.run(installSignalHandlers=False)
input()