import asyncio
import json
import socket
import sys
import threading
import traceback
from datetime import datetime
from typing import Optional

import aiohttp
import websocket

from vnpy.api.asyncio.async_executor import create_async_task, loop, wrap_as_sync, start_asyncio, \
    stop_asyncio, wait_for_async_task


class WebsocketClient(object):
    """
    Websocket API

    After creating the client object, use start() to run worker and ping threads.
    The worker thread connects websocket automatically.

    Use stop to stop threads and disconnect websocket before destroying the client
    object (especially when exiting the programme).

    Default serialization format is json.

    Callbacks to overrides:
    * unpack_data
    * on_connected
    * on_disconnected
    * on_packet
    * on_error

    After start() is called, the ping thread will ping server every 60 seconds.

    If you want to send anything other than JSON, override send_packet.
    """

    def __init__(self):
        """Constructor"""
        self.host = None

        self._ws_lock = threading.Lock()
        self._ws: Optional[aiohttp.ClientWebSocketResponse] = None

        self._active = False

        self.proxy_host = None
        self.proxy_port = None
        self.ping_interval = 60  # seconds
        self.headers = {}

        self._stop_task : Optional[asyncio.Task] = None

        # For debugging
        self._last_sent_text = None
        self._last_received_text = None

    def init(self,
             host: str,
             proxy_host: str = "",
             proxy_port: int = 0,
             ping_interval: int = 60,
             headers: dict = None,
             ):
        """
        :param ping_interval: unit: seconds, type: int
        """
        self.host = host
        self.ping_interval = ping_interval  # seconds

        if headers:
            self.headers = headers

        if proxy_host and proxy_port:
            self.proxy_host = proxy_host
            self.proxy_port = proxy_port

    def start(self):
        """
        Start the client and on_connected function is called after webscoket
        is connected succesfully.

        Please don't send packet untill on_connected fucntion is called.
        """
        start_asyncio()
        self._active = True
        create_async_task(self._run())
        create_async_task(self._run_ping())

    def stop(self):
        """
        Stop the client.
        """
        self._active = False
        self._stop_task = create_async_task(self._disconnect())
        stop_asyncio()

    def join(self):
        """
        Wait until all worker exit.
        """
        if self._stop_task:
            wait_for_async_task(self._stop_task)

    def send_packet(self, packet: dict):
        """
        Send a packet (dict data) to server

        override this if you want to send non-json packet
        """
        text = json.dumps(packet)
        self._record_last_sent_text(text)
        return wrap_as_sync(self._send_text(text))()

    async def _send_text(self, text: str):
        """
        Send a text string to server.
        """
        ws = self._ws
        if ws:
            await ws.send_str(text)

    async def _send_binary(self, data: bytes):
        """
        Send bytes data to server.
        """
        ws = self._ws
        if ws:
            await ws.send_bytes(data)

    async def _ensure_connection(self):
        """"""
        triggered = False
        with self._ws_lock:
            if self._ws is None:
                self._session = aiohttp.ClientSession(loop=loop)
                # noinspection PyTypeChecker
                self._ws: aiohttp.ClientWebSocketResponse = await self._session.ws_connect(
                    self.host,
                    proxy=f'http://{self.proxy_host}:{self.proxy_port}',
                    headers=self.headers,
                )
                triggered = True
        if triggered:
            self.on_connected()

    async def _disconnect(self):
        """
        """
        triggered = False
        with self._ws_lock:
            if self._ws:
                session = self._session
                ws: websocket.WebSocket = self._ws
                self._ws = None

                triggered = True
        if triggered:
            await ws.close()
            await session.close()
            self.on_disconnected()

    async def _run(self):
        """
        Keep running till stop is called.
        """
        try:
            while self._active:
                try:
                    await self._ensure_connection()
                    ws = self._ws
                    if ws:
                        msg = await ws.receive()
                        type = msg.type
                        text = msg.data
                        if (type == aiohttp.WSMsgType.PING
                            or type == aiohttp.WSMsgType.PONG
                        ):
                            continue

                        # ws object is closed when recv function is blocking
                        if not text:
                            if text is None:
                                await self._disconnect()
                                continue
                            else:
                                raise Exception(f"Unknown ws packet({type}):{text}")

                        self._record_last_received_text(text)

                        try:
                            data = self.unpack_data(text)
                        except ValueError as e:
                            print("websocket unable to parse data: " + text)
                            raise e

                        self.on_packet(data)
                # ws is closed before recv function is called
                # For socket.error, see Issue #1608
                except (websocket.WebSocketConnectionClosedException, socket.error):
                    await self._disconnect()

                # other internal exception raised in on_packet
                except:  # noqa
                    et, ev, tb = sys.exc_info()
                    self.on_error(et, ev, tb)
                    await self._disconnect()
        except:  # noqa
            et, ev, tb = sys.exc_info()
            self.on_error(et, ev, tb)
        await self._disconnect()

    @staticmethod
    def unpack_data(data: str):
        """
        Default serialization format is json.

        override this method if you want to use other serialization format.
        """
        return json.loads(data)

    async def _run_ping(self):
        """"""
        while self._active:
            try:
                await self._ping()
            except:  # noqa
                et, ev, tb = sys.exc_info()
                self.on_error(et, ev, tb)

                # self._run() will reconnect websocket
                await asyncio.sleep(1)

            for i in range(self.ping_interval):
                if not self._active:
                    break
                await asyncio.sleep(1)

    async def _ping(self):
        """"""
        ws = self._ws
        if ws:
            await ws.ping(b"ping")

    @staticmethod
    def on_connected():
        """
        Callback when websocket is connected successfully.
        """
        pass

    @staticmethod
    def on_disconnected():
        """
        Callback when websocket connection is lost.
        """
        pass

    @staticmethod
    def on_packet(packet: dict):
        """
        Callback when receiving data from server.
        """
        pass

    def on_error(self, exception_type: type, exception_value: Exception, tb):
        """
        Callback when exception raised.
        """
        sys.stderr.write(
            self.exception_detail(exception_type, exception_value, tb)
        )
        return sys.excepthook(exception_type, exception_value, tb)

    def exception_detail(
        self, exception_type: type, exception_value: Exception, tb
    ):
        """
        Print detailed exception information.
        """
        text = "[{}]: Unhandled WebSocket Error:{}\n".format(
            datetime.now().isoformat(), exception_type
        )
        text += "LastSentText:\n{}\n".format(self._last_sent_text)
        text += "LastReceivedText:\n{}\n".format(self._last_received_text)
        text += "Exception trace: \n"
        text += "".join(
            traceback.format_exception(exception_type, exception_value, tb)
        )
        return text

    def _record_last_sent_text(self, text: str):
        """
        Record last sent text for debug purpose.
        """
        self._last_sent_text = text[:1000]

    def _record_last_received_text(self, text: str):
        """
        Record last received text for debug purpose.
        """
        self._last_received_text = text[:1000]
