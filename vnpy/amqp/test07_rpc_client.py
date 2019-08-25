from vnpy.amqp.producer import rpc_client
from uuid import uuid1
import json
import random

def cb_function(*args):
    print('resp call back')
    for arg in args:
        if isinstance(arg,bytes):
            print(u'{}'.format(arg.decode('utf-8')))
        else:
            print(u'{}'.format(arg))

from vnpy.trader.vtConstant import *
if __name__ == '__main__':
    import datetime
    import time
    c = rpc_client(host='localhost', user='admin', password='admin',routing_key='HUA_AN')

    counter = 0
    while True:
        time.sleep(10)
        mission = {'method': 'get_strategy_names'}
        params = {}
        mission.update({'params': params})
        msg = json.dumps(mission)
        print(u'[x] rpc call :{}'.format(msg))
        c.call(msg, str(uuid1()), cb_function)
        counter += 1

        if counter > 1:
            break

    print('exit')
    c.exit()
