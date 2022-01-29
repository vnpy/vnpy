import signal
import threading
import traceback
from datetime import datetime, timedelta
from functools import lru_cache
from typing import Any, Callable, Dict

import zmq
import zmq.auth
from zmq.backend.cython.constants import NOBLOCK


# Achieve Ctrl-c interrupt recv
signal.signal(signal.SIGINT, signal.SIG_DFL)


KEEP_ALIVE_TOPIC: str = "_keep_alive"
KEEP_ALIVE_INTERVAL: timedelta = timedelta(seconds=1)
KEEP_ALIVE_TOLERANCE: timedelta = timedelta(seconds=30)


class RemoteException(Exception):
    """
    RPC remote exception
    """

    def __init__(self, value: Any):
        """
        Constructor
        """
        self._value = value

    def __str__(self):
        """
        Output error message
        """
        return self._value


class RpcServer:
    """"""

    def __init__(self):
        """
        Constructor
        """
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
        start = datetime.utcnow()

        while self._active:
            # Use poll to wait event arrival, waiting time is 1 second (1000 milliseconds)
            cur = datetime.utcnow()
            delta = cur - start

            if delta >= KEEP_ALIVE_INTERVAL:
                self.publish(KEEP_ALIVE_TOPIC, cur)

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


class RpcClient:
    """"""

    def __init__(self):
        """Constructor"""
        # zmq port related
        self._context: zmq.Context = zmq.Context()

        # Request socket (Request–reply pattern)
        self._socket_req: zmq.Socket = self._context.socket(zmq.REQ)

        # Subscribe socket (Publish–subscribe pattern)
        self._socket_sub: zmq.Socket = self._context.socket(zmq.SUB)

        # Worker thread relate, used to process data pushed from server
        self._active: bool = False                 # RpcClient status
        self._thread: threading.Thread = None      # RpcClient thread
        self._lock: threading.Lock = threading.Lock()

        self._last_received_ping: datetime = datetime.utcnow()

    @lru_cache(100)
    def __getattr__(self, name: str):
        """
        Realize remote call function
        """

        # Perform remote call task
        def dorpc(*args, **kwargs):
            # Get timeout value from kwargs, default value is 30 seconds
            if "timeout" in kwargs:
                timeout = kwargs.pop("timeout")
            else:
                timeout = 30000

            # Generate request
            req = [name, args, kwargs]

            # Send request and wait for response
            with self._lock:
                self._socket_req.send_pyobj(req)
                
                # Timeout reached without any data
                n = self._socket_req.poll(timeout)
                if not n:
                    msg = f"Timeout of {timeout}ms reached for {req}"
                    raise RemoteException(msg)
                
                rep = self._socket_req.recv_pyobj()

            # Return response if successed; Trigger exception if failed
            if rep[0]:
                return rep[1]
            else:
                raise RemoteException(rep[1])

        return dorpc

    def start(
        self, 
        req_address: str, 
        sub_address: str
    ) -> None:
        """
        Start RpcClient
        """
        if self._active:
            return
            
        # Connect zmq port
        self._socket_req.connect(req_address)
        self._socket_sub.connect(sub_address)

        # Start RpcClient status
        self._active = True

        # Start RpcClient thread
        self._thread = threading.Thread(target=self.run)
        self._thread.start()

        self._last_received_ping = datetime.utcnow()

    def stop(self) -> None:
        """
        Stop RpcClient
        """
        if not self._active:
            return

        # Stop RpcClient status
        self._active = False

    def join(self) -> None:
        # Wait for RpcClient thread to exit
        if self._thread and self._thread.is_alive():
            self._thread.join()
        self._thread = None

    def run(self) -> None:
        """
        Run RpcClient function
        """
        pull_tolerance = int(KEEP_ALIVE_TOLERANCE.total_seconds() * 1000)

        while self._active:
            if not self._socket_sub.poll(pull_tolerance):
                self.on_disconnected()
                continue

            # Receive data from subscribe socket
            topic, data = self._socket_sub.recv_pyobj(flags=NOBLOCK)

            if topic == KEEP_ALIVE_TOPIC:
                self._last_received_ping = data
            else:
                # Process data by callable function
                self.callback(topic, data)

        # Close socket
        self._socket_req.close()
        self._socket_sub.close()

    def callback(self, topic: str, data: Any) -> None:
        """
        Callable function
        """
        raise NotImplementedError

    def subscribe_topic(self, topic: str) -> None:
        """
        Subscribe data
        """
        self._socket_sub.setsockopt_string(zmq.SUBSCRIBE, topic)

    def on_disconnected(self):
        """
        Callback when heartbeat is lost.
        """
        print("RpcServer has no response over {tolerance} seconds, please check you connection."
                .format(tolerance=KEEP_ALIVE_TOLERANCE.total_seconds()))
