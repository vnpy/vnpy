import threading
import traceback
import signal
import zmq
from typing import Any, Callable


# Achieve Ctrl-c interrupt recv
signal.signal(signal.SIGINT, signal.SIG_DFL)


class RemoteException(Exception):
    """
    RPC remote exception
    """

    def __init__(self, value):
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
        self.__functions = {}

        # Zmq port related
        self.__context = zmq.Context()

        # Reply socket (Request–reply pattern)
        self.__socket_rep = self.__context.socket(zmq.REP)

        # Publish socket (Publish–subscribe pattern)
        self.__socket_pub = self.__context.socket(zmq.PUB)

        # Worker thread related
        self.__active = False                               # RpcServer status
        self.__thread = None                                # RpcServer thread

    def is_active(self):
        """"""
        return self.__active

    def start(self, rep_address: str, pub_address: str):
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

    def stop(self):
        """
        Stop RpcServer
        """
        if not self.__active:
            return

        # Stop RpcServer status
        self.__active = False

        # Wait for RpcServer thread to exit
        if self.__thread.isAlive():
            self.__thread.join()
        self.__thread = None

        # Unbind socket address
        self.__socket_pub.unbind(self.__socket_pub.LAST_ENDPOINT)
        self.__socket_rep.unbind(self.__socket_rep.LAST_ENDPOINT)

    def run(self):
        """
        Run RpcServer functions
        """
        while self.__active:
            # Use poll to wait event arrival, waiting time is 1 second (1000 milliseconds)
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

    def publish(self, topic: str, data: Any):
        """
        Publish data
        """
        self.__socket_pub.send_pyobj([topic, data])

    def register(self, func: Callable):
        """
        Register function
        """
        self.__functions[func.__name__] = func


class RpcClient:
    """"""

    def __init__(self):
        """Constructor"""
        # zmq port related
        self.__context = zmq.Context()

        # Request socket (Request–reply pattern)
        self.__socket_req = self.__context.socket(zmq.REQ)

        # Subscribe socket (Publish–subscribe pattern)
        self.__socket_sub = self.__context.socket(zmq.SUB)

        # Worker thread relate, used to process data pushed from server
        self.__active = False   # RpcClient status
        self.__thread = None    # RpcClient thread

    def __getattr__(self, name: str):
        """
        Realize remote call function
        """
        # Perform remote call task
        def dorpc(*args, **kwargs):
            # Generate request
            req = [name, args, kwargs]

            # Send request and wait for response
            self.__socket_req.send_pyobj(req)
            rep = self.__socket_req.recv_pyobj()

            # Return response if successed; Trigger exception if failed
            if rep[0]:
                return rep[1]
            else:
                raise RemoteException(rep[1])

        return dorpc

    def start(self, req_address: str, sub_address: str):
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

    def stop(self):
        """
        Stop RpcClient
        """
        if not self.__active:
            return

        # Stop RpcClient status
        self.__active = False

        # Wait for RpcClient thread to exit
        if self.__thread.isAlive():
            self.__thread.join()
        self.__thread = None

        # Close socket
        self.__socket_req.close()
        self.__socket_sub.close()

    def run(self):
        """
        Run RpcClient function
        """
        while self.__active:
            # Use poll to wait event arrival, waiting time is 1 second (1000 milliseconds)
            if not self.__socket_sub.poll(1000):
                continue

            # Receive data from subscribe socket
            topic, data = self.__socket_sub.recv_pyobj()

            # Process data by callable function
            self.callback(topic, data)

    def callback(self, topic: str, data: Any):
        """
        Callable function
        """
        raise NotImplementedError

    def subscribe_topic(self, topic: str):
        """
        Subscribe data
        """
        self.__socket_sub.setsockopt_string(zmq.SUBSCRIBE, topic)
