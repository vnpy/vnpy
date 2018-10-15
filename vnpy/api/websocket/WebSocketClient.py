# encoding: UTF-8


########################################################################
import json
import ssl
import sys
import time
from abc import abstractmethod
from threading import Thread, Lock

import websocket


class WebsocketClient(object):
    """Websocket API"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.host = None  # type: str
        
        self._ws_lock = Lock()
        self._ws = None  # type: websocket.WebSocket
        
        self._workerThread = None  # type: Thread
        self._pingThread = None  # type: Thread
        self._active = False

    #----------------------------------------------------------------------
    def init(self, host):
        self.host = host
    
    #----------------------------------------------------------------------
    def start(self):
        """启动"""
        self._connect()
        
        self._active = True
        self._workerThread = Thread(target=self._run)
        self._workerThread.start()
        
        self._pingThread = Thread(target=self._runPing)
        self._pingThread.start()
        
        self.onConnected()
        
    #----------------------------------------------------------------------
    def stop(self):
        """
        关闭
        @note 不能从工作线程，也就是websocket的回调中调用
        """
        self._active = False
        self._disconnect()

    #----------------------------------------------------------------------
    def sendRequest(self, dictObj):  # type: (dict)->None
        """发出请求:相当于sendText(json.dumps(dictObj))"""
        return self._get_ws().send(json.dumps(dictObj), opcode=websocket.ABNF.OPCODE_TEXT)
    
    #----------------------------------------------------------------------
    def sendText(self, text):  # type: (str)->None
        """发送文本数据"""
        return self._get_ws().send(text, opcode=websocket.ABNF.OPCODE_TEXT)
    
    #----------------------------------------------------------------------
    def sendData(self, data):  # type: (bytes)->None
        """发送字节数据"""
        return self._get_ws().send_binary(data)
    
    #----------------------------------------------------------------------
    def _reconnect(self):
        """重连"""
        self._disconnect()
        self._connect()
    
    #----------------------------------------------------------------------
    def _connect(self):
        """"""
        self._ws = websocket.create_connection(self.host, sslopt={'cert_reqs': ssl.CERT_NONE})
        self.onConnected()
    
    #----------------------------------------------------------------------
    def _disconnect(self):
        """
        断开连接
        """
        with self._ws_lock:
            if self._ws:
                self._ws.close()
                self._ws = None

    #----------------------------------------------------------------------
    def _get_ws(self):
        with self._ws_lock:
            return self._ws
    
    #----------------------------------------------------------------------
    def _run(self):
        """运行"""
        ws = self._get_ws()
        while self._active:
            try:
                stream = ws.recv()
                if not stream:
                    self.onDisconnected()
                    if self._active:
                        self._reconnect()
                    continue
                    
                data = json.loads(stream)
                self.onPacket(data)
            except:
                et, ev, tb = sys.exc_info()
                self.onError(et, ev, tb)
    
    #----------------------------------------------------------------------
    def _runPing(self):
        while self._active:
            self._ping()
            for i in range(60):
                if not self._active:
                    break
                time.sleep(1)
    
    #----------------------------------------------------------------------
    def _ping(self):
        return self._get_ws().send('ping', websocket.ABNF.OPCODE_PING)
    
    #----------------------------------------------------------------------
    def onConnected(self):
        """
        连接成功回调
        """
        pass
    
    #----------------------------------------------------------------------
    def onDisconnected(self):
        """
        连接断开回调
        """
        pass
    
    #----------------------------------------------------------------------
    @abstractmethod
    def onPacket(self, packet):
        """
        数据回调。
        只有在数据为json包的时候才会触发这个回调
        @:param data: dict
        @:return:
        """
        pass
    
    #----------------------------------------------------------------------
    @abstractmethod
    def onError(self, exceptionType, exceptionValue, tb):
        """Python错误回调"""
        pass
