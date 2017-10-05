# encoding: UTF-8

from time import sleep, time

from vnrpc import RpcServer


########################################################################
class TestServer(RpcServer):
    """测试服务器"""

    #----------------------------------------------------------------------
    def __init__(self, repAddress, pubAddress):
        """Constructor"""
        super(TestServer, self).__init__(repAddress, pubAddress)

        self.register(self.add)

    #----------------------------------------------------------------------
    def add(self, a, b):
        """测试函数"""
        print 'receiving: %s, %s' % (a,b)
        return a + b


if __name__ == '__main__':
    repAddress = 'tcp://*:2014'
    pubAddress = 'tcp://*:0602'
    
    ts = TestServer(repAddress, pubAddress)
    ts.start()
    
    while 1:
        content = 'current server time is %s' % time()
        print content
        ts.publish('test', content)
        sleep(2)