import signal
import threading
import traceback
from datetime import datetime, timedelta
from typing import Any, Callable, Dict, Optional

import zmq
import zmq.auth

from vnpy.event import EventEngine, Event, EVENT_TIMER


# Achieve Ctrl-c interrupt recv
signal.signal(signal.SIGINT, signal.SIG_DFL)


KEEP_ALIVE_TOPIC: str = "_keep_alive"
KEEP_ALIVE_TOLERANCE: timedelta = timedelta(seconds=30)


class RpcServer:
    """"""

    def __init__(self, event_engine: Optional[EventEngine] = None):
        """
        Constructor
        """
        # Initialize event engine if not passed as argument
        if not event_engine:
            event_engine = EventEngine()
            event_engine.start()

        self._event_engine: EventEngine = event_engine

        # Save functions dict: key is function name, value is function object
        self._functions: Dict[str, Any] = {}

        # Zmq port related
        self._context: zmq.Context = zmq.Context()

        # Reply socket (Request–reply pattern)
        self._socket_rep: zmq.Socket = self._context.socket(zmq.REP)

        # Publish socket (Publish–subscribe pattern)
        self._socket_pub: zmq.Socket = self._context.socket(zmq.PUB)

        # Worker thread related
        self._active: bool = False                      # RpcServer status
        self._thread: threading.Thread = None           # RpcServer thread
        self._lock: threading.Lock = threading.Lock()

    def is_active(self) -> bool:
        """"""
        return self._active

    def start(
        self,
        rep_address: str,
        pub_address: str,
    ) -> None:
        """
        Start RpcServer
        """
        if self._active:
            return

        # Bind socket address
        self._socket_rep.bind(rep_address)
        self._socket_pub.bind(pub_address)

        # Start RpcServer status
        self._active = True

        # Start RpcServer thread
        self._thread = threading.Thread(target=self.run)
        self._thread.start()

        # Register timer event
        self._event_engine.register(EVENT_TIMER, self.process_timer_event)

    def stop(self) -> None:
        """
        Stop RpcServer
        """
        if not self._active:
            return

        # Stop RpcServer status
        self._active = False

    def join(self) -> None:
        # Wait for RpcServer thread to exit
        if self._thread and self._thread.is_alive():
            self._thread.join()
        self._thread = None

    def run(self) -> None:
        """
        Run RpcServer functions
        """
        while self._active:
            if not self._socket_rep.poll(1000):
                continue

            # Receive request data from Reply socket
            req = self._socket_rep.recv_pyobj()

            # Get function name and parameters
            name, args, kwargs = req

            # Try to get and execute callable function object; capture exception information if it fails
            try:
                func = self._functions[name]
                r = func(*args, **kwargs)
                rep = [True, r]
            except Exception as e:  # noqa
                rep = [False, traceback.format_exc()]

            # send callable response by Reply socket
            self._socket_rep.send_pyobj(rep)

        # Unbind socket address
        self._socket_pub.unbind(self._socket_pub.LAST_ENDPOINT)
        self._socket_rep.unbind(self._socket_rep.LAST_ENDPOINT)

    def publish(self, topic: str, data: Any) -> None:
        """
        Publish data
        """
        with self._lock:
            self._socket_pub.send_pyobj([topic, data])

    def register(self, func: Callable) -> None:
        """
        Register function
        """
        self._functions[func.__name__] = func

    def process_timer_event(self, event: Event) -> None:
        """
        Publish heartbeat.
        """
        if self._active:
            self.publish(KEEP_ALIVE_TOPIC, datetime.utcnow())
