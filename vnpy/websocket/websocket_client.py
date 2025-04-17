import json
import ssl
import traceback
from threading import Thread
from typing import Optional

import websocket


class WebsocketClient:
    """
    Websocket API

    After creating the client object, use start() to run worker thread.
    The worker thread connects websocket automatically.

    Use stop to stop threads and disconnect websocket before destroying the client
    object (especially when exiting the programme).

    Default serialization format is json.

    Callbacks to overrides:
    * on_connected
    * on_disconnected
    * on_packet
    * on_error

    If you want to send anything other than JSON, override send_packet.
    """

    def __init__(self) -> None:
        """Constructor"""
        self.active: bool = False
        self.host: str = ""

        self.wsapp: websocket.WebSocketApp = None
        self.thread: Thread = None

        self.proxy_host: Optional[str] = None
        self.proxy_port: Optional[int] = None
        self.header: Optional[dict] = None
        self.ping_interval: int = 0
        self.receive_timeout: int = 0

        self.trace: bool = False

    def init(
        self,
        host: str,
        proxy_host: str = "",
        proxy_port: int = 0,
        ping_interval: int = 10,
        receive_timeout: int = 60,
        header: dict = None,
        trace: bool = False
    ) -> None:
        """
        :param host:
        :param proxy_host:
        :param proxy_port:
        :param header:
        :param ping_interval: unit: seconds, type: int
        """
        self.host = host
        self.ping_interval = ping_interval  # seconds
        self.receive_timeout = receive_timeout

        if header:
            self.header = header

        if proxy_host and proxy_port:
            self.proxy_host = proxy_host
            self.proxy_port = proxy_port

        websocket.enableTrace(trace)
        websocket.setdefaulttimeout(receive_timeout)

    def start(self) -> None:
        """
        Start the client and on_connected function is called after webscoket
        is connected succesfully.

        Please don't send packet untill on_connected fucntion is called.
        """
        self.active = True
        self.thread = Thread(target=self.run)
        self.thread.start()

    def stop(self) -> None:
        """
        Stop the client.
        """
        if not self.active:
            return

        self.active = False
        self.wsapp.close()

    def join(self) -> None:
        """
        Wait till all threads finish.

        This function cannot be called from worker thread or callback function.
        """
        self.thread.join()

    def send_packet(self, packet: dict) -> None:
        """
        Send a packet (dict data) to server

        override this if you want to send non-json packet
        """
        text: str = json.dumps(packet)
        self.wsapp.send(text)

    def run(self) -> None:
        """
        Keep running till stop is called.
        """
        def on_open(wsapp: websocket.WebSocketApp) -> None:
            self.on_connected()

        def on_close(wsapp: websocket.WebSocketApp, status_code: int, msg: str) -> None:
            self.on_disconnected(status_code, msg)

        def on_error(wsapp: websocket.WebSocketApp, e: Exception) -> None:
            self.on_error(e)

        def on_message(wsapp: websocket.WebSocketApp, message: str) -> None:
            self.on_message(message)

        self.wsapp = websocket.WebSocketApp(
            url=self.host,
            header=self.header,
            on_open=on_open,
            on_close=on_close,
            on_error=on_error,
            on_message=on_message
        )

        proxy_type: Optional[str] = None
        if self.proxy_host:
            proxy_type = "http"

        self.wsapp.run_forever(
            sslopt={"cert_reqs": ssl.CERT_NONE},
            ping_interval=self.ping_interval,
            http_proxy_host=self.proxy_host,
            http_proxy_port=self.proxy_port,
            proxy_type=proxy_type,
            reconnect=1
        )

    def on_message(self, message: str) -> None:
        """
        Callback when weboscket app receives new message
        """
        self.on_packet(json.loads(message))

    def on_connected(self) -> None:
        """
        Callback when websocket is connected successfully.
        """
        pass

    def on_disconnected(self, status_code: int, msg: str) -> None:
        """
        Callback when websocket connection is closed.
        """
        pass

    def on_packet(packet: dict) -> None:
        """
        Callback when receiving data from server.
        """
        pass

    def on_error(self, e: Exception) -> None:
        """
        Callback when exception raised.
        """
        try:
            print("WebsocketClient on error" + "-" * 10)
            print(e)
        except Exception:
            traceback.print_exc()
