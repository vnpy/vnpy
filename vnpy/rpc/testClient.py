# encoding: UTF-8

from time import sleep

from vnrpc import RpcClient


########################################################################
class TestClient(RpcClient):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, reqAddress, subAddress):
        """Constructor"""
        super(TestClient, self).__init__(reqAddress, subAddress)
        
    #----------------------------------------------------------------------
    def callback(self, topic, data):
        """回调函数实现"""
        print 'client received topic:', topic, ', data:', data
    

if __name__ == '__main__':
    reqAddress = 'tcp://localhost:2014'
    subAddress = 'tcp://localhost:0602'
    
    tc = TestClient(reqAddress, subAddress)
    tc.subscribeTopic('')
    tc.start()
    
    while 1:
        print tc.add(1, 3)
        sleep(2)