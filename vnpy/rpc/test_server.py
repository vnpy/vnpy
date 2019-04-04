from __future__ import print_function
from __future__ import absolute_import
from time import sleep, time

from vnpy.rpc import RpcServer


class TestServer(RpcServer):
    """
    Test RpcServer
    """

    def __init__(self, rep_address, pub_address):
        """
        Constructor
        """
        super(TestServer, self).__init__(rep_address, pub_address)

        self.register(self.add)

    def add(self, a, b):
        """
        Test function
        """
        print('receiving: %s, %s' % (a, b))
        return a + b


if __name__ == '__main__':
    rep_address = 'tcp://*:2014'
    pub_address = 'tcp://*:0602'

    ts = TestServer(rep_address, pub_address)
    ts.start()

    while 1:
        content = 'current server time is %s' % time()
        print(content)
        ts.publish('test', content)
        sleep(2)
