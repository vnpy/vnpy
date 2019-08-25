from vnpy.amqp.consumer import rpc_server

def test_func01(p1,p2,p3):
    print('test_func01:', p1, p2, p3)
    return p1+p2+p3

def test_func02(p1, p2=0):
    print('test_func02:', p1, p2)
    return str(p1 + p2)

if __name__ == '__main__':

    import sys

    from time import sleep
    s = rpc_server(host='localhost', user='admin', password='admin')
    s.register_method('test_01', test_func01)
    s.register_method('test_02', test_func02)
    s.start()
    while True:
        sleep(1)
