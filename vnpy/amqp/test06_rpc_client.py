# encoding: UTF-8

from uuid import uuid1
import json
import random
from vnpy.amqp.producer import rpc_client

def cb_function(*args):
    print('resp call back')
    for arg in args:
        print(u'{}'.format(arg))

if __name__ == '__main__':
    import datetime
    import time
    c = rpc_client(host='localhost', user='admin', password='admin')

    counter = 0
    while True:
        time.sleep(0.1)
        mission = {'method': 'test_01'}
        params = {}
        params.update({'p2': random.random()})
        params.update({'p3': random.random()})
        params.update({'p1': counter})
        mission.update({'params': params})
        msg = json.dumps(mission)
        print(u'[x] rpc call :{}'.format(msg))

        c.call(msg,str(uuid1()), cb_function)
        counter += 1

        if counter > 100:
            break

    print('exit')
    c.exit()
