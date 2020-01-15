from zmq.backend.cython.constants import NOBLOCK
import signal
import threading
import traceback
from datetime import datetime, timedelta
from functools import lru_cache
from typing import Any, Callable, Dict

import zmq


def _(x): return x

# Achieve Ctrl-c interrupt recv


signal.signal(signal.SIGINT, signal.SIG_DFL)

KEEP_ALIVE_TOPIC: str = "_keep_alive"
KEEP_ALIVE_INTERVAL: timedelta = timedelta(seconds=1)
KEEP_ALIVE_TOLERANCE: timedelta = timedelta(seconds=3)


class RemoteException(Exception):
    """
    RPC remote exception
    """

    def __init__(self, value: Any):
        """
        Constructor
        """
        self.__value = value

    def __str__(self):
        """
        Output error message
        """
        return self.__value


class RpcServer:
    """"""

    def __init__(self):
        """
        Constructor
        """
        # Save functions dict: key is fuction name, value is fuction object
        self.__functions: Dict[str, Any] = {}

        # Zmq port related
        self.__context: zmq.Context = zmq.Context()

        # Reply socket (Request–reply pattern)
        self.__socket_rep: zmq.Socket = self.__context.socket(zmq.REP)

        # Publish socket (Publish–subscribe pattern)
        self.__socket_pub: zmq.Socket = self.__context.socket(zmq.PUB)

        # Worker thread related
        self.__active: bool = False                     # RpcServer status
        self.__thread: threading.Thread = None          # RpcServer thread

        self._register(KEEP_ALIVE_TOPIC, lambda n: n)

    def is_active(self) -> bool:
        """"""
        return self.__active

    def start(self, rep_address: str, pub_address: str) -> None:
        """
        Start RpcServer
        """
        if self.__active:
            return

        # Bind socket address
        self.__socket_rep.bind(rep_address)
        self.__socket_pub.bind(pub_address)

        # Start RpcServer status
        self.__active = True

        # Start RpcServer thread
        self.__thread = threading.Thread(target=self.run)
        self.__thread.start()

    def stop(self) -> None:
        """
        Stop RpcServer
        """
        if not self.__active:
            return

        # Stop RpcServer status
        self.__active = False

    def join(self) -> None:
        # Wait for RpcServer thread to exit
        if self.__thread and self.__thread.is_alive():
            self.__thread.join()
        self.__thread = None

    def run(self) -> None:
        """
        Run RpcServer functions
        """
        start = datetime.utcnow()

        while self.__active:
            # Use poll to wait event arrival, waiting time is 1 second (1000 milliseconds)
            cur = datetime.utcnow()
            delta = cur - start

            if delta >= KEEP_ALIVE_INTERVAL:
                self.publish(KEEP_ALIVE_TOPIC, cur)

            if not self.__socket_rep.poll(1000):
                continue

            # Receive request data from Reply socket
            req = self.__socket_rep.recv_pyobj()

            # Get function name and parameters
            name, args, kwargs = req

            # Try to get and execute callable function object; capture exception information if it fails
            try:
                func = self.__functions[name]
                r = func(*args, **kwargs)
                rep = [True, r]
            except Exception as e:  # noqa
                rep = [False, traceback.format_exc()]

            # send callable response by Reply socket
            self.__socket_rep.send_pyobj(rep)

        # Unbind socket address
        self.__socket_pub.unbind(self.__socket_pub.LAST_ENDPOINT)
        self.__socket_rep.unbind(self.__socket_rep.LAST_ENDPOINT)

    def publish(self, topic: str, data: Any) -> None:
        """
        Publish data
        """
        self.__socket_pub.send_pyobj([topic, data])

    def register(self, func: Callable) -> None:
        """
        Register function
        """
        return self._register(func.__name__, func)

    def _register(self, name: str, func: Callable) -> None:
        """
        Register function
        """
        self.__functions[name] = func


class RpcClient:
    """"""

    def __init__(self):
        """Constructor"""
        # zmq port related
        self.__context: zmq.Context = zmq.Context()

        # Request socket (Request–reply pattern)
        self.__socket_req: zmq.Socket = self.__context.socket(zmq.REQ)

        # Subscribe socket (Publish–subscribe pattern)
        self.__socket_sub: zmq.Socket = self.__context.socket(zmq.SUB)

        # Worker thread relate, used to process data pushed from server
        self.__active: bool = False                 # RpcClient status
        self.__thread: threading.Thread = None      # RpcClient thread
        self.__lock: threading.Lock = threading.Lock()

        self._last_received_ping: datetime = datetime.utcnow()

    @lru_cache(100)
    def __getattr__(self, name: str):
        """
        Realize remote call function
        """

        # Perform remote call task
        def dorpc(*args, **kwargs):
            # Generate request
            req = [name, args, kwargs]

            # Send request and wait for response
            with self.__lock:
                self.__socket_req.send_pyobj(req)
                rep = self.__socket_req.recv_pyobj()

            # Return response if successed; Trigger exception if failed
            if rep[0]:
                return rep[1]
            else:
                raise RemoteException(rep[1])

        return dorpc

    def start(self, req_address: str, sub_address: str) -> None:
        """
        Start RpcClient
        """
        if self.__active:
            return

        # Connect zmq port
        self.__socket_req.connect(req_address)
        self.__socket_sub.connect(sub_address)

        # Start RpcClient status
        self.__active = True

        # Start RpcClient thread
        self.__thread = threading.Thread(target=self.run)
        self.__thread.start()

        self._last_received_ping = datetime.utcnow()

    def stop(self) -> None:
        """
        Stop RpcClient
        """
        if not self.__active:
            return

        # Stop RpcClient status
        self.__active = False

    def join(self) -> None:
        # Wait for RpcClient thread to exit
        if self.__thread and self.__thread.is_alive():
            self.__thread.join()
        self.__thread = None

    def run(self) -> None:
        """
        Run RpcClient function
        """
        pull_tolerance = int(KEEP_ALIVE_TOLERANCE.total_seconds() * 1000)

        while self.__active:
            if not self.__socket_sub.poll(pull_tolerance):
                self._on_unexpected_disconnected()
                continue

            # Receive data from subscribe socket
            topic, data = self.__socket_sub.recv_pyobj(flags=NOBLOCK)

            if topic == KEEP_ALIVE_TOPIC:
                self._last_received_ping = data
            else:
                # Process data by callable function
                self.callback(topic, data)

        # Close socket
        self.__socket_req.close()
        self.__socket_sub.close()

    @staticmethod
    def _on_unexpected_disconnected():
        print(_("RpcServer has no response over {tolerance} seconds, please check you connection."
                .format(tolerance=KEEP_ALIVE_TOLERANCE.total_seconds())))

    def callback(self, topic: str, data: Any) -> None:
        """
        Callable function
        """
        raise NotImplementedError

    def subscribe_topic(self, topic: str) -> None:
        """
        Subscribe data
        """
        self.__socket_sub.setsockopt_string(zmq.SUBSCRIBE, topic)
