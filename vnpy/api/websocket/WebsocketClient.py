# encoding: UTF-8


########################################################################
import json
import ssl
import sys
import time
import traceback
from datetime import datetime
from threading import Lock, Thread

import websocket


class WebsocketClient(object):
    """
    Websocket API

    实例化之后，应调用start开始后台线程。调用start()函数会自动连接websocket。
    若要终止后台线程，请调用stop()。 stop()函数会顺便断开websocket。

    该类默认打包方式为json，若从服务器返回的数据不为json，则会触发onError。

    可以覆盖以下回调：
    onConnected
    onDisconnected
    onPacket        # 数据回调，只有在返回的数据帧为text并且内容为json时才会回调
    onError

    当然，为了不让用户随意自定义，用自己的init函数覆盖掉原本的init(host)也是个不错的选择。

    关于ping：
    在调用start()之后，该类每60s会自动发送一个ping帧至服务器。
    """

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.host = None  # type: str

        self._ws_lock = Lock()
        self._ws = None  # type: websocket.WebSocket

        self._workerThread = None  # type: Thread
        self._pingThread = None  # type: Thread
        self._active = False

        # for debugging:
        self._lastSentText = None
        self._lastReceivedText = None

    #----------------------------------------------------------------------
    def init(self, host):
        self.host = host

    #----------------------------------------------------------------------
    def start(self):
        """
        启动
        :note 注意：启动之后不能立即发包，需要等待websocket连接成功。
        websocket连接成功之后会响应onConnected函数
        """

        self._active = True
        self._workerThread = Thread(target=self._run)
        self._workerThread.start()

        self._pingThread = Thread(target=self._runPing)
        self._pingThread.start()

    #----------------------------------------------------------------------
    def stop(self):
        """
        关闭
        @note 不能从工作线程，也就是websocket的回调中调用
        """
        self._active = False
        self._disconnect()

    #----------------------------------------------------------------------
    def join(self):
        """
        等待所有工作线程退出
        正确调用方式：先stop()后join()
        """
        self._pingThread.join()
        self._workerThread.join()

    #----------------------------------------------------------------------
    def sendPacket(self, dictObj):  # type: (dict)->None
        """发出请求:相当于sendText(json.dumps(dictObj))"""
        text = json.dumps(dictObj)
        self._recordLastSentText(text)
        return self._getWs().send(text, opcode=websocket.ABNF.OPCODE_TEXT)

    #----------------------------------------------------------------------
    def sendText(self, text):  # type: (str)->None
        """发送文本数据"""
        return self._getWs().send(text, opcode=websocket.ABNF.OPCODE_TEXT)

    #----------------------------------------------------------------------
    def sendBinary(self, data):  # type: (bytes)->None
        """发送字节数据"""
        return self._getWs().send_binary(data)

    #----------------------------------------------------------------------
    def _reconnect(self):
        """重连"""
        if self._active:
            self._disconnect()
            self._connect()

    #----------------------------------------------------------------------
    def _createConnection(self, *args, **kwargs):
        return websocket.create_connection(*args, **kwargs)

    #----------------------------------------------------------------------
    def _connect(self):
        """"""
        self._ws = self._createConnection(self.host, sslopt={'cert_reqs': ssl.CERT_NONE})
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
    def _getWs(self):
        with self._ws_lock:
            return self._ws

    #----------------------------------------------------------------------
    def _run(self):
        """
        运行，直到stop()被调用
        """
        try:
            self._connect()

            # todo: onDisconnect
            while self._active:
                try:
                    ws = self._getWs()
                    if ws:
                        text = ws.recv()
                        if not text:  # recv在阻塞的时候ws被关闭
                            self._reconnect()
                            continue
                        self._recordLastReceivedText(text)
                        try:
                            data = self.unpackData(text)
                        except ValueError as e:
                            print('websocket unable to parse data: ' + text)
                            raise e
                        self.onPacket(data)
                except websocket.WebSocketConnectionClosedException:  # 在调用recv之前ws就被关闭了
                    self._reconnect()
                except BaseException:                                            # Python内部错误（onPacket内出错）
                    et, ev, tb = sys.exc_info()
                    self.onError(et, ev, tb)
                    self._reconnect()
        except BaseException:
            et, ev, tb = sys.exc_info()
            self.onError(et, ev, tb)
            self._reconnect()

    #----------------------------------------------------------------------
    @staticmethod
    def unpackData(data):
        """
        解密数据，默认使用json解密为dict
        解密后的数据将会传入onPacket
        如果需要使用不同的解密方式，就重载这个函数。
        :param data 收到的数据，可能是text frame，也可能是binary frame, 目前并没有区分这两者
        """
        return json.loads(data)

    #----------------------------------------------------------------------
    def _runPing(self):
        while self._active:
            try:
                self._ping()
            except BaseException:
                et, ev, tb = sys.exc_info()
                # todo: just log this, notifying user is not necessary
                self.onError(et, ev, tb)
                self._reconnect()
            for i in range(60):
                if not self._active:
                    break
                time.sleep(1)

    #----------------------------------------------------------------------
    def _ping(self):
        ws = self._getWs()
        if ws:
            ws.send('ping', websocket.ABNF.OPCODE_PING)

    #----------------------------------------------------------------------
    @staticmethod
    def onConnected():
        """
        连接成功回调
        """
        pass

    #----------------------------------------------------------------------
    @staticmethod
    def onDisconnected():
        """
        连接断开回调
        """
        pass

    #----------------------------------------------------------------------
    @staticmethod
    def onPacket(packet):
        """
        数据回调。
        只有在数据为json包的时候才会触发这个回调
        @:param data: dict
        @:return:
        """
        pass

    #----------------------------------------------------------------------
    def onError(self, exceptionType, exceptionValue, tb):
        """
        Python错误回调
        todo: 以后详细的错误信息最好记录在文件里，用uuid来联系/区分具体错误
        """
        sys.stderr.write(self.exceptionDetail(exceptionType, exceptionValue, tb))

        # 丢给默认的错误处理函数（所以如果不重载onError，一般的结果是程序会崩溃）
        return sys.excepthook(exceptionType, exceptionValue, tb)

    #----------------------------------------------------------------------
    def exceptionDetail(self, exceptionType, exceptionValue, tb):
        """打印详细的错误信息"""
        text = "[{}]: Unhandled WebSocket Error:{}\n".format(
            datetime.now().isoformat(),
            exceptionType
        )
        text += "LastSentText:\n{}\n".format(self._lastSentText)
        text += "LastReceivedText:\n{}\n".format(self._lastReceivedText)
        text += "Exception trace: \n"
        text += "".join(traceback.format_exception(
            exceptionType,
            exceptionValue,
            tb,
        ))
        return text

    #----------------------------------------------------------------------
    def _recordLastSentText(self, text):
        """
        用于Debug： 记录最后一次发送出去的text
        """
        self._lastSentText = text[:500]

    #----------------------------------------------------------------------
    def _recordLastReceivedText(self, text):
        """
        用于Debug： 记录最后一次发送出去的text
        """
        self._lastReceivedText = text[:500]
