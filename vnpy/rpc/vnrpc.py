import threading
import traceback
import signal

import zmq
from msgpack import packb, unpackb
from json import dumps, loads

import pickle
p_dumps = pickle.dumps
p_loads = pickle.loads


# Achieve Ctrl-c interrupt recv
signal.signal(signal.SIGINT, signal.SIG_DFL)


class RpcObject(object):
    """
    Referred to serialization of packing and unpacking, we offer 3 tools:
    1) maspack: higher performance, but usually requires the installation of msgpack related tools;
    2) jason: Slightly lower performance but versatility is better, most programming languages have built-in libraries;
    3) cPickle: Lower performance and only can be used in Python, but it is very convenient to transfer Python objects directly.

    Therefore, it is recommended to use msgpack.
    Use json, if you want to communicate with some languages without providing msgpack.
    Use cPickle, when the data being transferred contains many custom Python objects.
    """

    def __init__(self):
        """
        Constructor
        Use msgpack as default serialization tool
        """
        self.use_msgpack()

    def pack(self, data):
        """"""
        pass

    def unpack(self, data):
        """"""
        pass

    def __json_pack(self, data):
        """
        Pack with json
        """
        return dumps(data)

    def __json_unpack(self, data):
        """
        Unpack with json
        """
        return loads(data)

    def __msgpack_pack(self, data):
        """
        Pack with msgpack
        """
        return packb(data)

    def __msgpack_unpack(self, data):
        """
        Unpack with msgpack
        """
        return unpackb(data)

    def __pickle_pack(self, data):
        """
        Pack with cPickle
        """
        return p_dumps(data)

    def __pickle_unpack(self, data):
        """
        Unpack with cPickle
        """
        return p_loads(data)

    def use_json(self):
        """
        Use json as serialization tool
        """
        self.pack = self.__json_pack
        self.unpack = self.__json_unpack

    def use_msgpack(self):
        """
        Use msgpack as serialization tool
        """
        self.pack = self.__msgpack_pack
        self.unpack = self.__msgpack_unpack

    def use_pickle(self):
        """
        Use cPickle as serialization tool
        """
        self.pack = self.__pickle_pack
        self.unpack = self.__pickle_unpack


class RpcServer(RpcObject):
    """"""

    def __init__(self, rep_address, pub_address):
        """
        Constructor
        """
        super(RpcServer, self).__init__()

        # Save functions dict: key is fuction name, value is fuction object
        self.__functions = {}

        # Zmq port related
        self.__context = zmq.Context()

        self.__socket_rep = self.__context.socket(
            zmq.REP)   # Reply socket (Request–reply pattern)
        self.__socket_rep.bind(rep_address)

        # Publish socket (Publish–subscribe pattern)
        self.__socket_pub = self.__context.socket(zmq.PUB)
        self.__socket_pub.bind(pub_address)

        # Woker thread related
        self.__active = False                             # RpcServer status
        self.__thread = threading.Thread(target=self.run)  # RpcServer thread

    def start(self):
        """
        Start RpcServer
        """
        # Start RpcServer status
        self.__active = True

        # Start RpcServer thread
        if not self.__thread.isAlive():
            self.__thread.start()

    def stop(self, join=False):
        """
        Stop RpcServer
        """
        # Stop RpcServer status
        self.__active = False

        # Wait for RpcServer thread to exit
        if join and self.__thread.isAlive():
            self.__thread.join()

    def run(self):
        """
        Run RpcServer functions
        """
        while self.__active:
            # Use poll to wait event arrival, waiting time is 1 second (1000 milliseconds)
            if not self.__socket_rep.poll(1000):
                continue

            # Receive request data from Reply socket
            reqb = self.__socket_rep.recv()

            # Unpack request by deserialization
            req = self.unpack(reqb)

            # Get function name and parameters
            name, args, kwargs = req

            # Try to get and execute callable function object; capture exception information if it fails
            name = name.decode("UTF-8")

            try:
                func = self.__functions[name]
                r = func(*args, **kwargs)
                rep = [True, r]
            except Exception as e:  # noqa
                rep = [False, traceback.format_exc()]

            # Pack response by serialization
            repb = self.pack(rep)

            # send callable response by Reply socket
            self.__socket_rep.send(repb)

    def publish(self, topic, data):
        """
        Publish data
        """
        # Serialized data
        topic = bytes(topic, "UTF-8")
        datab = self.pack(data)

        # Send data by Publish socket
        # topci must be ascii encoding
        self.__socket_pub.send_multipart([topic, datab])

    def register(self, func):
        """
        Register function
        """
        self.__functions[func.__name__] = func


class RpcClient(RpcObject):
    """"""

    def __init__(self, req_address, sub_address):
        """Constructor"""
        super(RpcClient, self).__init__()

        # zmq port related
        self.__req_address = req_address
        self.__sub_address = sub_address

        self.__context = zmq.Context()
        # Request socket (Request–reply pattern)
        self.__socket_req = self.__context.socket(zmq.REQ)
        # Subscribe socket (Publish–subscribe pattern)
        self.__socket_sub = self.__context.socket(zmq.SUB)

        # Woker thread relate, used to process data pushed from server
        self.__active = False                                   # RpcClient status
        self.__thread = threading.Thread(
            target=self.run)       # RpcClient thread

    def __getattr__(self, name):
        """
        Realize remote call function
        """
        # Perform remote call task
        def dorpc(*args, **kwargs):
            # Generate request
            req = [name, args, kwargs]

            # Pack request by serialization
            reqb = self.pack(req)

            # Send request and wait for response
            self.__socket_req.send(reqb)
            repb = self.__socket_req.recv()

            # Unpack response by deserialization
            rep = self.unpack(repb)

            # Return response if successed; Trigger exception if failed
            if rep[0]:
                return rep[1]
            else:
                raise RemoteException(rep[1].decode("UTF-8"))

        return dorpc

    def start(self):
        """
        Start RpcClient
        """
        # Connect zmq port
        self.__socket_req.connect(self.__req_address)
        self.__socket_sub.connect(self.__sub_address)

        # Start RpcClient status
        self.__active = True

        # Start RpcClient thread
        if not self.__thread.isAlive():
            self.__thread.start()

    def stop(self):
        """
        Stop RpcClient 
        """
        # Stop RpcClient status
        self.__active = False

        # Wait for RpcClient thread to exit
        if self.__thread.isAlive():
            self.__thread.join()

    def run(self):
        """
        Run RpcClient function
        """
        while self.__active:
            # Use poll to wait event arrival, waiting time is 1 second (1000 milliseconds)
            if not self.__socket_sub.poll(1000):
                continue

            # Receive data from subscribe socket
            topic, datab = self.__socket_sub.recv_multipart()

            # Unpack data by deserialization
            data = self.unpack(datab)

            # Process data by callable function
            topic = topic.decode("UTF-8")

            self.callback(topic, data)

    def callback(self, topic, data):
        """
        Callable function
        """
        raise NotImplementedError

    def subscribeTopic(self, topic):
        """
        Subscribe data
        """
        topic = bytes(topic, "UTF-8")
        self.__socket_sub.setsockopt(zmq.SUBSCRIBE, topic)


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
