from __future__ import print_function
from __future__ import absolute_import
from time import sleep, time

from vnpy.rpc import RpcServer


class TestServer(RpcServer):
    """
    Test RpcServer
    """

    def __init__(self):
        """
        Constructor
        """
        super(TestServer, self).__init__()

        self.register(self.add)

    def add(self, a, b):
        """
        Test function
        """
        print(f"receiving:{a} {b}")
        return a + b


if __name__ == "__main__":
    rep_address = "tcp://*:2014"
    pub_address = "tcp://*:4102"

    ts = TestServer()
    ts.start(
        rep_address,
        pub_address,
        "./certificates/server.key_secret"
    )

    while 1:
        content = f"current server time is {time()}"
        print(content)
        ts.publish("test", content)
        sleep(2)
